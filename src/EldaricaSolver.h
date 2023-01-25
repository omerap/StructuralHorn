//
// Created by Yakir Vizel on 1/25/23.
//
#pragma once

#include "Solver.h"
#include "jni.h"

namespace structuralHorn {

using namespace std;

class EldaricaSolver : public solver {

    JavaVM * m_jvm;
    JNIEnv * m_env;

public:
    EldaricaSolver(string fileName) : solver(fileName ){
        JavaVMInitArgs vm_args;                        // Initialization arguments
        JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
        //options[0].optionString = "-Djava.class.path=target/scala-2.11/classes/lazabs/;target/scala-2.11/classes/lazabs/ho>
        options[0].optionString = "-Djava.class.path=Eldarica/";   // where to find java .class
        vm_args.version = JNI_VERSION_1_6;             // minimum Java version
        vm_args.nOptions = 1;                          // number of options
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
        //=============== load and initialize Java VM and JNI interface =============
        jint rc = JNI_CreateJavaVM(&m_jvm, (void**)&m_env, (void*)&vm_args);  // YES !!
        delete options;    // we then no longer need the initialisation options.
        if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
        }
        //=============== Display JVM version =======================================
        cout << "JVM load succeeded: Version ";
        jint ver = m_env->GetVersion();
        cout << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << endl;

        // TO DO: add the code that will use JVM <============  (see next steps)

        jclass inc = m_env->FindClass("EldaricaAPI");
        if (inc == nullptr) {
            cout << "Could not find class\n";
        } else {
            cout << "Class found!\n";
        }
    }

    virtual int num_of_predicates() {return  0;}

    virtual int num_of_clauses() {return 0;}
    virtual std::multiset<int> body_predicates(int clause_id) { return multiset<int>(); }
    int head_predicate(int clause_id) {return 0;}

    virtual bool amend_clause(int clause_id) {return false;}
    virtual bool amend_clauses(std::set<int> clause_ids, std::set<int> facts_ids, int query_id) {return false;}

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
    virtual result solve(std::set<int> clause_ids, bool print_res = false) {return result::unknown;}
};

}