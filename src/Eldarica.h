#pragma once

#include "Solver.h"

namespace structuralHorn {

	class eldarica : public solver {
	public:
		eldarica(char const* file) {}

		int num_of_predicates() {
			return -1;
		}

		int num_of_clauses() {
			return -1;
		}

		std::multiset<int> body_predicates(int clause_id) {
			std::multiset<int> res;
			return res;
		}

		int head_predicate(int clause_id) {
			return -1;
		}

		bool amend_clause(int clause_id) {
			return false;
		}

		bool amend_clauses(const std::set<int>& clause_ids, int query_id, const std::set<int>& predicates_to_substitute) {
			return false;
		}

		// this method assumes there is exactly one query in clause_ids
		result solve(const std::set<int>& clause_ids, bool print_res = false) {
			return result::unknown;
		}
	};
}