#pragma once

#include <set>

namespace structuralHorn {
	enum class result {sat, unsat, unknown};

	class solver {
    protected:
        /**
        * The constructor of the class.
        *
        * After creating a class object all member functions can be invoked.
        * Therefore, the constructor should parse the input SMT file and initialize its internal fields.
        * Specifically, it should create:
        * - A bijection between predicate symbols and int IDs.
        *	If there are n predicate symbols, each predicate should be assigned an ID between 1 and n.
        *	Also, 0 is reserved for init, which denotes the body of facts, and n+1 is reserved for error, which denotes the head of queries.
        * - A bijection between clauses and int IDs.
        *	If there are m clauses, each clause should be assigned an ID between 1 and m.
        * - A predicate interpretation initialized to true for all predicates.
        *
        * @param file The SMT input file.
        */
        solver(std::string fileName) {}
	public:
		/**
		* @return the number of predicates.
		*/
		virtual int num_of_predicates() = 0;

		/**
		* @return the number of clauses.
		*/
		virtual int num_of_clauses() = 0;

		/**
		* Return the IDs of the body predicates in the given clause as a multiset.
		* If the given clause is a fact, {0} is returned.
		* 
		* @param clause_id The ID of the given clause.
		* @return the IDs of the body predicates in the given clause.
		*/
		virtual std::multiset<int> body_predicates(int clause_id) = 0;

		/**
		* Return the ID of the head predicate in the given clause.
		* If the given clause is a query, n+1 is returned (where n=num_of_predicates()).
		*
		* @param clause_id The ID of the clause.
		* @return the ID of the head predicate in the given clause.
		*/
		virtual int head_predicate(int clause_id) = 0;

		/**
		* Amends the interpretation so that it satisfies the given clause.
		* 
		* If the clause is not currently satisfied, the interpretation of the clause's head predicate is weakened.
		* 
		* @param clause_id The ID of the clause that should be checked.
		* @return true iff the interpretation of the head predicate had to be weakened.
		*/
		virtual bool amend_clause(int clause_id) = 0;

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
		virtual bool amend_clauses(const std::set<int>& clause_ids, int query_id, const std::set<int>& predicates_to_substitute) = 0;

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
		virtual result solve(const std::set<int>& clause_ids, bool print_res = false) = 0;
	};

}
