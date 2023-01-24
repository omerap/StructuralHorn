#pragma once

#include <vector>
#include <map>
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

	class spacer : public solver {
	private:
		context c;
		fixedpoint fp;
		
		func_decl_vector head_predicate_vec; // clause id -> head predicate
		std::vector<func_decl_vector> body_predicates_vec; // clause id -> body predicates
		std::map<func_decl, int, compare_func_decl> predicate_id_map; // predicate -> id
		std::map<func_decl, expr, compare_func_decl> predicate_interpretation_map; // predicate -> interpretation

		void get_body_predicates(expr const& e, func_decl_vector& body_preds) {
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

			// initialize body_predicates_vec
			for (int i = 0; i < assertions.size(); i++) {
				func_decl_vector body_preds(c);
				get_body_predicates(assertions[i].body().arg(0), body_preds);
				if (body_preds.empty()) {
					body_preds.push_back(c.bool_val(true).decl());
				}
				body_predicates_vec.push_back(body_preds);			
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

		const std::map<func_decl, int, compare_func_decl>& get_predicate_id_map() {
			return predicate_id_map;
		}

		const std::map<func_decl, expr, compare_func_decl>& get_predicate_interpretation_map() {
			return predicate_interpretation_map;
		}
	};
}