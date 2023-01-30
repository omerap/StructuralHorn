#pragma once

#include <iostream>
#include <set>
#include <vector>

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
#ifndef _WIN32
			SH_MEASURE_FN;
#endif
			bool weaken_query_interp = false;
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
					if (g.affects_the_query(sort_of_a_query)) {
						weaken_query_interp = true;
					}
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
					if (g.affects_the_query(rule)) {
						weaken_query_interp = true;
					}
					for (int out_rule : g.get_out_hyperarcs(g.get_target_node(rule))) {
						if ((delta.count(out_rule) > 0) && (g.get_target_node(out_rule) != error_id())) {
							// TODO: is it important to also require that the interpretation of g.get_target_node(out_rule) is not "true"?
							queue.insert(out_rule);
						}
					}
				}
			}
			if (!weaken_query_interp && (gParams.verbosity > 0)) {
				std::cout << "\nThe interpretation is satisfying after amend. No need to invoke the solver\n";
			}
			return weaken_query_interp;
		}

	public:
		structural_horn(char const* file) {
#ifndef _WIN32
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
#ifndef _WIN32
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
			bool weaken_query_interp = false;
			if (gParams.verbosity > 0) {
				std::cout << "===============iteration 0===============\n";
				std::cout << "\ndelta:\n{";
				bool first_chc = true;
				for (int chc : delta) {
					if (first_chc) {
						first_chc = false;
						std::cout << chc;
					}
					else {
						std::cout << ", " << chc;
					}
				}
				std::cout << "}\n";
			}
#ifndef _WIN32
			Stats::uset("Iterations", 1);
#endif
			while (true) {
				// invoke the underlying chc solver
				result res = result::unknown;
				if (gParams.verbosity > 0) {
					res = s->solve(delta,true);
				}
				else {
					res = s->solve(delta,false);
				}
				if (res == result::sat) { // the chc set is *not* satisfiable, there exists a ground refutation 
#ifndef _WIN32
					Stats::uset("Iterations", iteration+1);
#endif
					return result::sat;				
				}
				
				do {
					if (delta.size() == s->num_of_clauses()) { // the chc set is satisfiable (there exists a satisfying interpretation) or unknown
#ifndef _WIN32
						Stats::uset("Iterations", iteration+1);
#endif
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
					
					if (gParams.verbosity > 0) {
						std::cout << "\n===============iteration " << iteration << "===============\n";
						std::cout << "\ndelta:\n{";
						bool first_chc = true;
						for (int chc : delta) {
							if (first_chc) {
								first_chc = false;
								std::cout << chc;
							}
							else {
								std::cout << ", " << chc;
							}
						}
						std::cout << "}\n";
					}
					
					std::vector<double> preserved_conjs;
					if (gParams.verbosity > 0) {
						const node_set& reachable = g.get_reachable();
						for (auto pred_id : reachable) {
							preserved_conjs.push_back(s->num_of_conjs(pred_id));
						}
					}
										
					weaken_query_interp = mkRuleSat(rules, sort_of_a_query, predicates_to_substitute);
					
					if (gParams.verbosity > 0) {
						const node_set& reachable2 = g.get_reachable();
						int idx = 0;
						for (auto pred_id : reachable2) {
							if (preserved_conjs[idx] > 0) {
								preserved_conjs[idx] = (s->num_of_conjs(pred_id)/preserved_conjs[idx]);
							}
							else {
								preserved_conjs[idx] = 1;
							}
							idx++;
						}
						double sum = 0;
						for (int i = 0 ; i < preserved_conjs.size() ; i++) {
							sum += preserved_conjs[i];
						}
						sum /= preserved_conjs.size();
#ifndef _WIN32
						Stats::avg("Predicate_preservation_percentage",sum);
#endif
					}

				} while (!weaken_query_interp);
			}
		}
	};
}
