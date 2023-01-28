#pragma once

#include <iostream>
#include <set>

#include "Solver.h"
#include "Spacer.h"
#include "EldaricaSolver.h"
#include "Hypergraph.h"
#include "Global.h"
#include "Stats.h"

namespace structuralHorn {

	class structural_horn {
	private:
		solver* s;
		hypergraph g;
		std::set<int> delta;

		int init_id() {
			return 0;
		}

		int error_id() {
			return s->num_of_predicates() + 1;
		}

		bool mkRuleSat(const std::set<int>& rules, int sort_of_a_query, const std::set<int>& predicates_to_substitute) {
#ifdef __unix__
			SH_MEASURE_FN;
#endif
			bool weaken_interp = false;
			if (g.get_target_node(sort_of_a_query) == error_id()) { // sort_of_a_query is a query
				return false;
			}

			std::set<int> queue;
			bool update = false;

			if (rules.empty()) { // |small_delta| = 1
				queue.insert(sort_of_a_query);
			}
			else { // |small_delta| > 1
				update = s->amend_clauses(rules, sort_of_a_query, predicates_to_substitute);
				if (update) {
					weaken_interp = true;
					for (int out_rule : g.get_out_hyperarcs(g.get_target_node(sort_of_a_query))) {
						if ((delta.count(out_rule) > 0) && (g.get_target_node(out_rule) != error_id())) {
							// TODO: is it important to also require that the interpretation of g.get_target_node(out_rule) is not "true"?
							queue.insert(out_rule);
						}
					}
				}
				else { // in case spacer returns an incomplete model. This can happen if the problem is solved only by performing simplifications made by the frontend.
					for (int rule : rules) {
						queue.insert(rule);
					}
					queue.insert(sort_of_a_query);
				}
			}
			while (!queue.empty()) {
				int rule = *(queue.begin());
				queue.erase(queue.begin());
				update = s->amend_clause(rule);
				if (update) {
					weaken_interp = true;
					for (int out_rule : g.get_out_hyperarcs(g.get_target_node(rule))) {
						if ((delta.count(out_rule) > 0) && (g.get_target_node(out_rule) != error_id())) {
							// TODO: is it important to also require that the interpretation of g.get_target_node(out_rule) is not "true"?
							queue.insert(out_rule);
						}
					}
				}
			}
			return weaken_interp;
		}

	public:
		structural_horn(char const* file) {
#ifdef __unix__
			SH_MEASURE_FN;
#endif
			if (gParams.chc_solver == 0) {
				s = new spacer(file);
			}
			else {
				s = new EldaricaSolver(file);
			}

			// initialize hypergraph
			g.set_init_node(init_id());
			g.set_err_node(error_id());
			for (int i = 0; i < s->num_of_clauses(); i++) {
				g.insert_hyperarc(i, s->body_predicates(i), s->head_predicate(i));
			}
			//std::cout << "\n" << g << "\n";
		}

		~structural_horn() {
			delete s;
		}

		result solve() {
#ifdef __unix__
			SH_MEASURE_FN;
#endif
			// InitClauses
			std::set<int> rules;
			int sort_of_a_query = -1;
			std::set<int> predicates_to_substitute;
			g.shortest_hyperpath_gt0(rules, sort_of_a_query, predicates_to_substitute);
			delta.insert(sort_of_a_query);
			for (int rule : rules) {
				delta.insert(rule);
			}

			int iteration = 0;
			while (true) {
				//std::cout << "===============iteration " << iteration << "===============\n";
				result res = s->solve(delta); // invoke the underlying chc solver
				if (res == result::sat) { // the chc set is *not* satisfiable, there exists a ground refutation 
					return result::sat;
				}
				
				do {
					if (delta.size() == s->num_of_clauses()) { // the chc set is satisfiable (there exists a satisfying interpretation) or unknown
						return res;
					}
					iteration++;

					// NextClauses
					rules.clear();
					sort_of_a_query = -1;
					predicates_to_substitute.clear();
					g.shortest_hyperpath_gt0(rules, sort_of_a_query, predicates_to_substitute);

					delta.insert(sort_of_a_query);
					for (int rule : rules) {
						delta.insert(rule);
					}
#ifdef __unix__
						Stats::uset("Iterations", iteration);
						VERBOSE(1, Stats::PrintBrunch(vout()););
#endif

				} while (!mkRuleSat(rules, sort_of_a_query, predicates_to_substitute));

#ifdef __unix__
					Stats::uset("Iterations", iteration);
					VERBOSE(1, Stats::PrintBrunch(vout()););
#endif
			}
		}
	};
}
