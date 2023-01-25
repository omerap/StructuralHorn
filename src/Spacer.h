#pragma once

#include <vector>
#include <map>
#include <set>
#include <assert.h>

#include "Solver.h"
#include "z3++.h"

using namespace z3;

namespace structuralHorn {
	
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
		fixedpoint fp;
		
		func_decl_vector head_predicate_vec; // clause id -> head predicate
		std::vector<func_decl_vector> body_predicates_vec; // clause id -> body predicates vector
		std::vector<func_decl_vector> body_predicates_set; // clause id -> body predicates set
		std::map<func_decl, int, compare_func_decl> predicate_id_map; // predicate -> id
		std::map<func_decl, expr, compare_func_decl> predicate_interpretation_map; // predicate -> interpretation

		void get_body_predicates(const expr& e, func_decl_vector& body_preds) {
			assert(e.is_app());

			// check if the current application expression is a predicate
			if (predicate_id_map.count(e.decl()) != 0) {
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

		// TODO: implement
		expr to_fact(expr e, int clause_id) {
			assert(e.is_forall());
			expr body = e.body().arg(0);
			const func_decl_vector& predicates = body_predicates_set[clause_id];
			expr_vector interpretations(c);
			for (int i = 0; i < predicates.size(); i++) {
				const func_decl& pred = predicates[i];
				const expr& interp = predicate_interpretation_map.find(pred)->second;
				interpretations.push_back(interp);
			}
			expr new_body = body.substitute(predicates, interpretations);
			
			expr_vector body_vec(c);
			body_vec.push_back(body);
			expr_vector new_body_vec(c);
			new_body_vec.push_back(new_body);
			
			expr fact = e.substitute(body_vec, new_body_vec);
			std::cout << "\nto_fact:\ngiven expr:\n" << e << "\noutput:\n" << fact << "\n";
			std::cout << "\nnew_body:\n" << new_body << "\n";
			return fact;
		}

		// TODO: implement
		expr from_forall_to_exist(const expr& e) {
			assert(e.is_forall());
			
			expr res(c);
			return res;
		}

	public:
		spacer(char const* file) : fp(c), head_predicate_vec(c){
			fp.from_file(file);
			const expr_vector& assertions = fp.assertions();

			// initialize head_predicate_vec, predicate_id_map and predicate_interpretation_map
			for (int i = 0; i < assertions.size(); i++) {
				assert(assertions[i].body().is_implies());
				expr head_expr = assertions[i].body().arg(1);
				func_decl head_decl = head_expr.decl();
				head_predicate_vec.push_back(head_decl);
				if (!head_expr.is_false() && predicate_id_map.count(head_decl) == 0) {
					int size = predicate_id_map.size();
					predicate_id_map.emplace(head_decl, size + 1);
					predicate_interpretation_map.emplace(head_decl, c.bool_val(true));
				}
			}
			predicate_id_map.emplace(c.bool_val(true).decl(), 0);
			predicate_id_map.emplace(c.bool_val(false).decl(), predicate_id_map.size());

			// initialize body_predicates_vec and body_predicates_set
			for (int i = 0; i < assertions.size(); i++) {
				func_decl_vector body_preds(c);
				get_body_predicates(assertions[i].body().arg(0), body_preds);
				if (body_preds.empty()) {
					body_preds.push_back(c.bool_val(true).decl());
				}
				body_predicates_vec.push_back(body_preds);

				func_decl_set body_preds_set;
				for (int j = 0; j < body_preds.size(); j++) {
					body_preds_set.insert(body_preds[j]);
				}
				func_decl_vector body_preds_set_vec(c);
				for (const func_decl& decl : body_preds_set) {
					body_preds_set_vec.push_back(decl);
				}
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

		// TODO: implement
		bool amend_clause(int clause_id) {
			assert(0 <= clause_id && clause_id < num_of_clauses());
			to_fact(fp.assertions()[clause_id], clause_id);
			return false;
		}

		// TODO: implement
		bool amend_clauses(std::set<int> clause_ids, std::set<int> facts_ids, int query_id) {
			return false;
		}
		
		// TODO: implement
		result solve(std::set<int> clause_ids, bool print_res = false) {
			return result::unknown;
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

		const std::map<func_decl, int, compare_func_decl>& get_predicate_id_map() {
			return predicate_id_map;
		}

		const std::map<func_decl, expr, compare_func_decl>& get_predicate_interpretation_map() {
			return predicate_interpretation_map;
		}
	};
}