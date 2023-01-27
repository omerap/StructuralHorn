#pragma once

#include <vector>
#include <map>
#include <set>
#include <assert.h>

#include "Solver.h"
#include "z3++.h"

using namespace z3;

namespace structuralHorn {

	params init_params(context& c) {
		set_param("verbose", 0);
		params params(c);
		params.set("engine", "spacer");
		params.set("fp.xform.slice", false);
		params.set("fp.xform.inline_linear", false);
		params.set("fp.xform.inline_eager", false);

		// params.set("fp.spacer.random_seed", gParams.random_seed);
		// params.set("print_statistics", true);

		// arrays
		/*if (gParams.array_theory == 1) {
			params.set("fp.spacer.ground_pobs", false);
			params.set("fp.spacer.q3.use_qgen", true);
		}*/
		return params;
	}
	
	class compare_func_decl {
	public:
		bool operator() (const func_decl& lhs, const func_decl& rhs) const {
			return lhs.id() < rhs.id();
		}
	};

	typedef std::set<func_decl, compare_func_decl> func_decl_set;

	class spacer : public solver {
	private:
		context c;
		expr_vector clauses;
				
		func_decl_vector head_predicate_vec; // clause id -> head predicate
		std::vector<func_decl_vector> body_predicates_vec; // clause id -> body predicates vector
		std::vector<func_decl_vector> body_predicates_set; // clause id -> body predicates set
		std::vector<expr_vector> bound_variables_vec; // clause id -> bound variables
		std::map<func_decl, int, compare_func_decl> predicate_id_map; // predicate -> id
		std::map<func_decl, expr, compare_func_decl> predicate_interpretation_map; // predicate -> interpretation

		void get_body_predicates(const expr& e, func_decl_vector& body_preds) {
			assert(e.is_app());

			// check if the current application expression is a predicate
			if (predicate_id_map.count(e.decl()) != 0 && !e.is_true() && !e.is_false()) {
				body_preds.push_back(e.decl());
				return;
			}

			// iterate recursively on the children
			for (int i = 0; i < e.num_args(); i++) {
				expr curr = e.arg(i);
				if (curr.is_app()) {
					get_body_predicates(curr, body_preds);
				}
			}
		}

		expr to_fact(const expr& clause, int clause_id) {
			assert(clause.is_forall());
			expr body = clause.body().arg(0);
			const func_decl_vector& predicates = body_predicates_set[clause_id];

			//std::cout << "clause " << clause_id << ":\n" << clause << "\n";
			if (predicates.size() == 1 && predicate_id_map[predicates[0]] == 0) {
				//std::cout << "\nclause is already a fact\n\n";
				return clause;
			}

			expr_vector interpretations(c);
			for (int i = 0; i < predicates.size(); i++) {
				const func_decl& pred = predicates[i];
				const expr& interp = predicate_interpretation_map.find(pred)->second;
				//expr interp = ((c.variable(0, c.int_sort()) == 1) && (c.variable(1, c.int_sort()) >= 1));
				interpretations.push_back(interp);
			}
			expr new_body = body.substitute(predicates, interpretations);
			
			const expr_vector& variables = bound_variables_vec[clause_id];
			expr fact = forall(variables, implies(new_body, clause.body().arg(1)));
			
			std::cout << "\nfact:\n" << fact << "\n\n";
			return fact;
		}

		expr to_query(const expr& clause, int clause_id) {
			assert(clause.is_forall());
			expr head = clause.body().arg(1);
			const func_decl& predicate = head_predicate_vec[clause_id];
			expr new_head = head;

			//std::cout << "clause " << clause_id << ":\n" << clause << "\n";
			if (!head.is_false()) { // clause is not already a query
				func_decl_vector predicate_vec(c);
				predicate_vec.push_back(predicate);
				expr_vector interpretation_vec(c);
				const expr& interp = predicate_interpretation_map.find(predicate)->second;
				interpretation_vec.push_back(interp);

				new_head = head.substitute(predicate_vec, interpretation_vec);
			}

			const expr_vector& variables = bound_variables_vec[clause_id];
			expr query(c);
			if (head.is_false()) {
				query = exists(variables, (clause.body().arg(0)));
			}
			else {
				query = exists(variables, (clause.body().arg(0) && (!(new_head))));
			}
			
			//std::cout << "query:\n" << query << "\n\n";
			return query;
		}

		expr to_query(const expr& clause, int clause_id, const expr& head_interp) {
			assert(clause.is_forall());
			expr head = clause.body().arg(1);
			const func_decl& predicate = head_predicate_vec[clause_id];
			expr new_head = head;

			//std::cout << "clause " << clause_id << ":\n" << clause << "\n";
			assert(!head.is_false()); // clause is not already a query
			func_decl_vector predicate_vec(c);
			predicate_vec.push_back(predicate);
			expr_vector interpretation_vec(c);
			interpretation_vec.push_back(head_interp);

			new_head = head.substitute(predicate_vec, interpretation_vec);

			const expr_vector& variables = bound_variables_vec[clause_id];
			expr query = exists(variables, (clause.body().arg(0) && (!(new_head))));
			
			//std::cout << "query:\n" << query << "\n\n";
			return query;
		}

		result solve_chcs(expr_vector& chcs, expr& query) {
			// initialize solver
			fixedpoint fp(c);
			fp.set(init_params(c));

			func_decl_set predicates;

			// add the clauses and create the query
			int i = 0;
			for (expr clause : chcs) {
				expr head_expr = clause.body().arg(1);
				func_decl head_decl = head_expr.decl();
				assert(!head_expr.is_false());
				fp.register_relation(head_decl);
				symbol name = c.str_symbol(("rule" + std::to_string(i)).c_str());
				fp.add_rule(clause, name);
				predicates.insert(head_decl);
				i++;
			}

			// inject interpretations
			for (func_decl predicate : predicates) {
				auto it = predicate_interpretation_map.find(predicate);
				assert(it != predicate_interpretation_map.end());
				expr interp = it->second;
				fp.add_cover(-1, predicate, interp);
			}

			// solve
			assert(query.is_exists());
			check_result spacer_res = fp.query(query);

			// if unsat update interpretations
			if (spacer_res == z3::unsat) {
				for (func_decl predicate : predicates) {
					expr interp = fp.get_cover_delta(-1, predicate);
					auto it = predicate_interpretation_map.find(predicate);
					assert(it != predicate_interpretation_map.end());
					it->second = interp;
				}
			}

			// TODO: if (print_res==true) then print the result and the interpretations/ground refutation to std::cout
			if (spacer_res == z3::sat) {
				return result::sat;
			}
			else if (spacer_res == z3::unsat) {

				return result::unsat;
			}
			return result::unknown;
		}

	public:
		spacer(char const* file) : c(), clauses(c), head_predicate_vec(c){
			fixedpoint fp(c);
			fp.set(init_params(c));
			fp.from_file(file);
			clauses = fp.assertions();
			
			for (int i = 0; i < clauses.size(); i++) {
				// initialize head_predicate_vec, predicate_id_map and predicate_interpretation_map
				assert(clauses[i].body().is_implies());
				expr head_expr = clauses[i].body().arg(1);
				func_decl head_decl = head_expr.decl();
				head_predicate_vec.push_back(head_decl); 
				if (!head_expr.is_false() && predicate_id_map.count(head_decl) == 0) {
					int size = predicate_id_map.size();
					predicate_id_map.emplace(head_decl, size + 1);
					predicate_interpretation_map.emplace(head_decl, c.bool_val(true));
				}

				// initialize bound_variables_vec
				expr_vector variables(c);
				for (int j = 0; j < Z3_get_quantifier_num_bound(c, clauses[i]); j++) {
					symbol sym = symbol(c, Z3_get_quantifier_bound_name(c, clauses[i], j));
					expr var = c.constant(sym, z3::sort(c, Z3_get_quantifier_bound_sort(c, clauses[i], j)));
					variables.push_back(var);
				}
				bound_variables_vec.push_back(variables);
			}
			predicate_id_map.emplace(c.bool_val(true).decl(), 0);
			predicate_id_map.emplace(c.bool_val(false).decl(), predicate_id_map.size());

			// initialize body_predicates_vec and body_predicates_set
			for (int i = 0; i < clauses.size(); i++) {
				func_decl_vector body_preds(c);
				get_body_predicates(clauses[i].body().arg(0), body_preds);
				if (body_preds.empty()) {
					body_preds.push_back(c.bool_val(true).decl());
				}
				
				func_decl_set body_preds_set;
				for (int j = 0; j < body_preds.size(); j++) {
					body_preds_set.insert(body_preds[j]);
				}
				func_decl_vector body_preds_set_vec(c);
				for (const func_decl& decl : body_preds_set) {
					body_preds_set_vec.push_back(decl);
				}

				body_predicates_vec.push_back(body_preds);
				body_predicates_set.push_back(body_preds_set_vec);
			}
		}

		int num_of_predicates() {
			return predicate_id_map.size() - 2;
		}

		int num_of_clauses() {
			return head_predicate_vec.size();
		}

		std::multiset<int> body_predicates(int clause_id) {
			assert(0 <= clause_id && clause_id < num_of_clauses());
			std::multiset<int> res;
			for (const func_decl& decl : body_predicates_vec[clause_id]) {
				res.insert(predicate_id_map[decl]);
			}
			return res;
		}

		int head_predicate(int clause_id) {
			assert(0 <= clause_id && clause_id < num_of_clauses());
			return predicate_id_map[head_predicate_vec[clause_id]];
		}

		bool amend_clause(int clause_id) {
			assert(0 <= clause_id && clause_id < num_of_clauses());

			expr clause = clauses[clause_id];
			// std::cout << "\nclause " << clause_id << ":\n" << clause << "\n";
			assert(!clause.body().arg(1).is_false()); // assert clause_id is not a query

			bool update = false;
			
			// substitute body predicates with their interpretations
			expr fact = to_fact(clause, clause_id);
			// std::cout << "\nfact:\n" << fact << "\n";

			// create conjuncts vector from the interpretation of the head predicate
			auto it = predicate_interpretation_map.find(head_predicate_vec[clause_id]);
			assert(it != predicate_interpretation_map.end());
			expr interp = it->second;
			//expr interp = ((c.variable(0, c.int_sort()) == 1) && (c.variable(1, c.int_sort()) >= 1));
			expr_vector conjuncts(c);
			if (interp.is_and()) {
				for (int i = 0; i < interp.num_args(); i++) {
					conjuncts.push_back(interp.arg(i));
				}
			}
			else {
				conjuncts.push_back(interp);
			}

			// check which conjuncts are implied
			expr new_interp = c.bool_val(true);
			for (int i = 0; i < conjuncts.size(); i++) {
				expr conjunct = conjuncts[i];
				expr query = to_query(fact, clause_id, conjunct);
				//std::cout << "\nquery "<< i <<":\n" << query << "\n";
				expr_vector empty_set(c);
				result res = solve_chcs(empty_set, query);
				if (res == result::unsat) { // conjunct is implied
					if (new_interp.is_true()) {
						new_interp = conjunct;
					}
					else {
						new_interp = (new_interp && conjunct);
					}
					//std::cout << "implied\n";
				}
				else {
					update = true;
					//std::cout << "not implied\n";
				}
			}
			//std::cout << "\nnew interp:\n" << new_interp << "\n";

			// update the interpretation of the head predicate if needed
			if (update) {
				it->second = new_interp.simplify();
			}

			return update;
		}

		bool amend_clauses(std::set<int> clause_ids, std::set<int> facts_ids, int query_id) {
			// assert all clauses have valid ids
			for (int clause_id : clause_ids) {
				assert(0 <= clause_id && clause_id < num_of_clauses());
			}
			for (int clause_id : facts_ids) {
				assert(0 <= clause_id && clause_id < num_of_clauses());
			}
			assert(0 <= query_id && query_id < num_of_clauses());

			expr query = clauses[query_id];
			assert(!query.body().arg(1).is_false()); // assert query_id is not already a query

			bool update = false;
			expr_vector chcs(c);

			// substitute body predicates of all clauses in facts_ids with their interpretations
			for (int fact_id : facts_ids) {
				chcs.push_back(to_fact(clauses[fact_id], fact_id));
			}

			// create clauses vector from clause_ids and new facts_ids
			for (int clause_id : clause_ids) {
				chcs.push_back(clauses[clause_id]);
			}

			// create conjuncts vector from the interpretation of the head predicate of query_id
			auto it = predicate_interpretation_map.find(head_predicate_vec[query_id]);
			assert(it != predicate_interpretation_map.end());
			expr interp = it->second;
			//expr interp = ((c.variable(0, c.int_sort()) == 1) && (c.variable(1, c.int_sort()) >= 1));
			expr_vector conjuncts(c);
			if (interp.is_and()) {
				for (int i = 0; i < interp.num_args(); i++) {
					conjuncts.push_back(interp.arg(i));
				}
			}
			else {
				conjuncts.push_back(interp);
			}

			// check incrementally which conjuncts are implied
			// update the interpretations of the head predicates of (facts_ids U clause_ids) accordingly
			expr new_interp = c.bool_val(true);
			for (int i = 0; i < conjuncts.size(); i++) {
				expr conjunct = conjuncts[i];
				expr query_i = to_query(query, query_id, (new_interp && conjunct));
				//std::cout << "\nquery "<< i <<":\n" << query_i << "\n";
				result res = solve_chcs(chcs, query_i);
				if (res == result::unsat) { // conjunct is implied
					if (new_interp.is_true()) {
						new_interp = conjunct;
					}
					else {
						new_interp = (new_interp && conjunct);
					}
					//std::cout << "implied\n";
				}
				else {
					update = true;
					//std::cout << "not implied\n";
				}
			}

			// update the interpretation of the head predicate of query_id if needed
			if (update) {
				it->second = new_interp.simplify();
			}

			return update;
		}
		
		// this method assumes there is exactly one query in clause_ids
		result solve(std::set<int> clause_ids, bool print_res = false) {
			// assert all clauses have valid ids
			for (int clause_id : clause_ids) {
				assert(0 <= clause_id && clause_id < num_of_clauses());
			}
			
			expr_vector chcs(c);
			expr query(c);
			
			for (int clause_id : clause_ids) {
				expr clause = clauses[clause_id];
				expr head_expr = clause.body().arg(1);
				if (head_expr.is_false()) {
					query = to_query(clause, clause_id);
				}
				else {
					chcs.push_back(clause);
				}
			}

			return solve_chcs(chcs, query);
		}

		const func_decl_vector& get_head_predicate_vec() {
			return head_predicate_vec;
		}

		const std::vector<func_decl_vector>& get_body_predicates_vec() {
			return body_predicates_vec;
		}

		const std::vector<func_decl_vector>& get_body_predicates_set() {
			return body_predicates_set;
		}

		const std::vector<expr_vector>& get_bound_variables_vec() {
			return bound_variables_vec;
		}

		const std::map<func_decl, int, compare_func_decl>& get_predicate_id_map() {
			return predicate_id_map;
		}

		const std::map<func_decl, expr, compare_func_decl>& get_predicate_interpretation_map() {
			return predicate_interpretation_map;
		}
	};
}