//
// Created by Yakir Vizel on 1/25/23.
//
#pragma once

#include "Solver.h"
#include "jni.h"
#include <iostream>
#include <fstream>

#include "Stats.h"
#include "Global.h"

namespace structuralHorn {

using namespace std;

class EldaricaSolver : public solver {

    JavaVM * m_jvm;
    JNIEnv * m_env;

    jclass m_EldaricaClass;
    jobject m_EldaricaAPI;
    jmethodID m_amend_one;
    jmethodID m_amend;
    jmethodID m_num_clauses;
    jmethodID m_num_preds;
    jmethodID m_body_preds;
    jmethodID m_head_pred;
    jmethodID m_solve;
    jmethodID m_verbose;
    jmethodID m_num_of_conjs;

    jclass m_Integer;
    jmethodID m_intCtor;
    jmethodID m_intValue;

    jclass m_ArrayList;
    jmethodID m_listCtor;
    jmethodID m_listSize;
    jmethodID m_listGet;
    jmethodID m_listAdd;



public:
    EldaricaSolver(string fileName) : solver(fileName ) {
        string strEldaricaAPIPath = std::getenv("ELDARICA_API_JAR");
        if (!ifstream (strEldaricaAPIPath.c_str()).good()) {
            cerr << "Cannot find the eldarica_api.jar file - exiting" << endl;
            exit(EXIT_FAILURE);
        }
        if (!ifstream (fileName.c_str()).good()) {
            cerr << "Cannot find SMT2 file - exiting" << endl;
            exit(EXIT_FAILURE);
        }
        JavaVMInitArgs vm_args;              // Initialization arguments
        JavaVMOption options[1];             // JVM invocation options
        string strJarPathOption = "-Djava.class.path=";
        strJarPathOption += strEldaricaAPIPath;
        char *jarPath = const_cast<char*>(strJarPathOption.c_str());
        options[0].optionString = jarPath;   // where to find java .class
        vm_args.version = JNI_VERSION_1_6;   // minimum Java version
        vm_args.nOptions = 1;                // number of options
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
        //=============== load and initialize Java VM and JNI interface =============
        jint rc = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, (void*)&vm_args);  // YES !!
        if (rc != JNI_OK) {
            exit(EXIT_FAILURE);
        }
        //=============== Display JVM version =======================================
        cout << "JVM load succeeded: Version ";
        jint ver = m_env->GetVersion();
        cout << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << endl;

        // Initialize Java Integer class methods
        m_Integer = m_env->FindClass("java/lang/Integer");
        m_intCtor = m_env->GetMethodID(m_Integer, "<init>", "(I)V");
        m_intValue = m_env->GetMethodID(m_Integer, "intValue", "()I");

        // Initialize Java ArrayList class methods
        m_ArrayList = static_cast<jclass>(m_env->NewGlobalRef(m_env->FindClass("java/util/ArrayList")));
        m_listCtor = m_env->GetMethodID(m_ArrayList, "<init>", "(I)V");
        m_listSize = m_env->GetMethodID (m_ArrayList, "size", "()I");
        m_listGet = m_env->GetMethodID(m_ArrayList, "get", "(I)Ljava/lang/Object;");
        m_listAdd = m_env->GetMethodID(m_ArrayList, "add", "(Ljava/lang/Object;)Z");

        // Get the API we want!
        m_EldaricaClass = m_env->FindClass("EldaricaAPI");
        if (m_EldaricaClass == nullptr) {
            exit(EXIT_FAILURE);
        }

        jmethodID ctor = loadMethod("<init>", "(ZZ)V");
        if(ctor == nullptr) {
            exit(EXIT_FAILURE);
        }
        m_EldaricaAPI = m_env->NewObject(m_EldaricaClass, ctor, (gParams.array_theory == 1), gParams.inc_mode);
        // Load the SMT file
        jmethodID read = loadMethod("readFromSmtFile", "(Ljava/lang/String;)Z");
        jboolean res = m_env->CallBooleanMethod(m_EldaricaAPI, read, m_env->NewStringUTF(fileName.c_str()));
        if (!res) {
            cout << "Failed reasing SMT2 file!\n";
            exit(EXIT_FAILURE);
        }

        // Initialize all the methods needed for the API
        m_num_clauses = loadMethod("givemeNumOfClauses", "()I");
        m_num_preds = loadMethod("givemeNumOfPredicates", "()I");
        m_body_preds = loadMethod("givemeBodyPredIds", "(I)Ljava/util/List;");
        m_head_pred = loadMethod("givemeHeadPredId", "(I)I");
        if (gParams.inc_mode) {
            m_solve = loadMethod("solve", "(Ljava/util/List;Z)I");
            m_amend = loadMethod("amendProof", "(Ljava/util/List;Ljava/util/List;I)Z");
        }
        else {
            m_solve = loadMethod("solve2", "(Ljava/util/List;Z)I");
            m_amend = loadMethod("amendProof2", "(Ljava/util/List;Ljava/util/List;I)Z");
        }
        m_amend_one = loadMethod("amendCls", "(I)Z");

        m_verbose = loadMethod("setVerbosity", "(I)V");
        m_num_of_conjs = loadMethod("givemeNumberOfConjs", "(I)I");

        m_env->CallVoidMethod(m_EldaricaAPI, m_verbose, gParams.verbosity);

        cout << "EldaricaAPI successfully constructed !"<<endl;
    }

    ~EldaricaSolver() {
        m_jvm->DestroyJavaVM();
    }

    virtual void set_verbosity(int v) {
        m_env->CallVoidMethod(m_EldaricaAPI, m_verbose, v);
    }

    virtual int num_of_conjs(int id) {
        return m_env->CallIntMethod(m_EldaricaAPI, m_num_of_conjs, id);
    }

    virtual int num_of_predicates() {
        return m_env->CallIntMethod(m_EldaricaAPI, m_num_preds);
    }

    virtual int num_of_clauses() {
        return m_env->CallIntMethod(m_EldaricaAPI, m_num_clauses);
    }

    virtual std::multiset<int> body_predicates(int clause_id) {
        jint id = clause_id;
        jobject list = m_env->CallObjectMethod(m_EldaricaAPI, m_body_preds, id);
        multiset<int> bodyPreds;
        jint len = m_env->CallIntMethod(list, m_listSize);
        for (jint i=0; i<len; i++) {
            jobject element = m_env->CallObjectMethod(list, m_listGet, i);
            bodyPreds.insert(m_env->CallIntMethod(element, m_intValue));
        }

        return bodyPreds;
    }

    int head_predicate(int clause_id) {
        jint id = clause_id;
        return m_env->CallIntMethod(m_EldaricaAPI, m_head_pred, id);
    }

    /**
    * Amends the interpretation so that it satisfies the given clause.
    *
    * If the clause is not currently satisfied, the interpretation of the clause's head predicate is weakened.
    *
    * @param clause_id The ID of the clause that should be checked.
    * @return true iff the interpretation of the head predicate had to be weakened.
    */
    virtual bool amend_clause(int clause_id) {
        return m_env->CallBooleanMethod(m_EldaricaAPI, m_amend_one, clause_id);
    }

    /**
		* Amends the interpretation so that it satisfies the given set of clauses.
		*
		* Every predicate in predicates_to_substitute should be substitute with its interpretation in the bodies of clauses (including the query).
		* The clause query_id should be considered as a query by substituting its head predicate with its interpretations (unless it is a query in the first place).
		*
		* All other clauses (clauses in clause_ids) contain fresh predicates (i.e., predicates that were not solved previously and therefore have an interpretation of true).
		* It is necessary to update the interpretations of all fresh predicates if the interpretation of query_id is indeed implied.
		*
		* @param clause_ids The IDs of the clauses that should be checked.
		* @param query_id The ID of the clause that should be considered as a query.
		* @param predicates_to_substitute The IDs of the presicates that should be substituted with their interpretation.
		* @return true iff the interpretation of the head predicate of query_id had to be weakened.
		*/
    virtual bool amend_clauses(const std::set<int>& clause_ids, int query_id, const std::set<int>& preds_to_subst) {
        jobject clauses = m_env->NewObject(m_ArrayList, m_listCtor, clause_ids.size());
        for (int id : clause_ids) {
            jobject oId = m_env->NewObject(m_Integer, m_intCtor, id);
            m_env->CallBooleanMethod(clauses, m_listAdd, oId);
        }
        jobject preds = m_env->NewObject(m_ArrayList, m_listCtor, preds_to_subst.size());
        for (int id : preds_to_subst) {
            jobject oId = m_env->NewObject(m_Integer, m_intCtor, id);
            m_env->CallBooleanMethod(preds, m_listAdd, oId);
        }
        jint query = query_id;

        return m_env->CallBooleanMethod(m_EldaricaAPI, m_amend, clauses, preds, query);
    }

    /**
    * Solves the given clauses using the undelying CHC solver.
    * Injects the current interpretation to the CHC solver as a starting solution.
    *
    * If the set of clauses is satisfiable, the interpretation is updated accordingly.
    *
    * @param clause_ids The IDs of the clauses that should be solved.
    * @param print_res If true, then the satisfying interpretation/ground refutation should be printed to std::cout
    * @return the result of the CHC-SAT instance - sat, unsat or unknown
    */
    virtual result solve(const std::set<int>& clause_ids, bool print_res = false) {
        SH_MEASURE_FN;
        jobject clauses = m_env->NewObject(m_ArrayList, m_listCtor, clause_ids.size());
        cout << "Created clauses object " << clauses << endl;
        for (int id : clause_ids) {
            jobject oId = m_env->NewObject(m_Integer, m_intCtor, id);
            m_env->CallBooleanMethod(clauses, m_listAdd, oId);
        }
        int res = m_env->CallIntMethod(m_EldaricaAPI, m_solve, clauses, print_res);
        if (res == 0) return result::sat;
        else if (res == 1) return result::unsat;
        return result::unknown;
    }

private:
    jmethodID loadMethod(string name, string signature) {
        jmethodID id = m_env->GetMethodID(m_EldaricaClass, name.c_str(), signature.c_str());
        if(id == nullptr) {
            cerr << "ERROR: " << name << " not found !" << endl;
            cerr.flush();
            exit(EXIT_FAILURE);
        }
        return id;
    }
};

}