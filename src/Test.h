#pragma once

namespace structuralHorn {

	void test_hypergraph() {
		hypergraph g;
		g.set_init_node(0);
		g.set_err_node(4);

		node_multiset sources1;
		sources1.insert(0);
		g.insert_hyperarc(1, sources1, 1);

		node_multiset sources2;
		sources2.insert(1);
		g.insert_hyperarc(2, sources2, 2);

		node_multiset sources3;
		sources3.insert(2);
		g.insert_hyperarc(3, sources3, 3);

		node_multiset sources4;
		sources4.insert(2);
		g.insert_hyperarc(4, sources4, 3);

		node_multiset sources5;
		sources5.insert(1);
		sources5.insert(3);
		g.insert_hyperarc(5, sources5, 2);

		node_multiset sources6;
		sources6.insert(1);
		sources6.insert(3);
		g.insert_hyperarc(6, sources6, 1);

		node_multiset sources7;
		sources7.insert(1);
		sources7.insert(3);
		sources7.insert(3);
		g.insert_hyperarc(7, sources7, 1);

		node_multiset sources8;
		sources8.insert(1);
		g.insert_hyperarc(8, sources8, 4);

		std::cout << g;

		hyperarc_set optimal_hyperpath;
		int optimal_hyperpath_last = -1;
		node_set predicates_to_substitute;
		g.shortest_hyperpath_gt0(optimal_hyperpath, optimal_hyperpath_last, predicates_to_substitute);
		while (optimal_hyperpath_last != -1) {
			std::cout << "\noptimal hyperpath:\t{";
			bool first_hyperarc = true;
			for (int hyperarc : optimal_hyperpath) {
				if (first_hyperarc) {
					first_hyperarc = false;
					std::cout << hyperarc;
				}
				else {
					std::cout << ", " << hyperarc;
				}
			}
			std::cout << "}\n";
			std::cout << "last hyperarc:\t" << optimal_hyperpath_last << "\n";
			std::cout << "reachable predicates:\t{";
			bool first_predicate = true;
			for (int pred : predicates_to_substitute) {
				if (first_predicate) {
					first_predicate = false;
					std::cout << pred;
				}
				else {
					std::cout << ", " << pred;
				}
			}
			std::cout << "}\n";
			//std::cout << g;
			optimal_hyperpath.clear();
			optimal_hyperpath_last = -1;
			predicates_to_substitute.clear();
			g.shortest_hyperpath_gt0(optimal_hyperpath, optimal_hyperpath_last, predicates_to_substitute);
		}

		int node = 1;
		hyperarc_set sources = g.get_out_hyperarcs(node);
		std::cout << "\nOutgoing hyperarcs of node " << node << ": {";
		bool first_hyperarc = true;
		for (int hyperarc : sources) {
			if (first_hyperarc) {
				first_hyperarc = false;
				std::cout << hyperarc;
			}
			else {
				std::cout << ", " << hyperarc;
			}
		}
		std::cout << "}\n";

		// sources = g.get_out_hyperarcs(13);

		int hyperarc = 6;
		std::cout << "\nTarget node of hyperarc " << hyperarc << ": " << g.get_target_node(hyperarc) << "\n\n";

		//hyperarc = -2;
		//cout << "\nTarget node of hyperarc " << hyperarc << ": " << g.get_target_node(hyperarc) << "\n";
	}

	void test_hypergraph2() {
		hypergraph g;
		g.set_init_node(0);
		g.set_err_node(2);

		node_multiset sources0;
		sources0.insert(0);
		g.insert_hyperarc(0, sources0, 1);

		node_multiset sources1;
		sources1.insert(0);
		g.insert_hyperarc(1, sources1, 1);

		node_multiset sources2;
		sources2.insert(0);
		g.insert_hyperarc(2, sources2, 1);

		node_multiset sources3;
		sources3.insert(0);
		g.insert_hyperarc(3, sources3, 1);

		node_multiset sources4;
		sources4.insert(0);
		g.insert_hyperarc(4, sources4, 1);

		node_multiset sources5;
		sources5.insert(1);
		sources5.insert(1);
		g.insert_hyperarc(5, sources5, 1);

		node_multiset sources6;
		sources6.insert(1);
		g.insert_hyperarc(6, sources6, 2);

		std::cout << g;

		hyperarc_set optimal_hyperpath;
		int optimal_hyperpath_last = -1;
		node_set predicates_to_substitute;
		g.shortest_hyperpath_gt0(optimal_hyperpath, optimal_hyperpath_last, predicates_to_substitute);
		while (optimal_hyperpath_last != -1) {
			std::cout << "\noptimal hyperpath:\t{";
			bool first_hyperarc = true;
			for (int hyperarc : optimal_hyperpath) {
				if (first_hyperarc) {
					first_hyperarc = false;
					std::cout << hyperarc;
				}
				else {
					std::cout << ", " << hyperarc;
				}
			}
			std::cout << "}\n";
			std::cout << "last hyperarc:\t" << optimal_hyperpath_last << "\n";
			std::cout << "reachable predicates:\t{";
			bool first_predicate = true;
			for (int pred : predicates_to_substitute) {
				if (first_predicate) {
					first_predicate = false;
					std::cout << pred;
				}
				else {
					std::cout << ", " << pred;
				}
			}
			std::cout << "}\n";
			//std::cout << g;
			optimal_hyperpath.clear();
			optimal_hyperpath_last = -1;
			predicates_to_substitute.clear();
			g.shortest_hyperpath_gt0(optimal_hyperpath, optimal_hyperpath_last, predicates_to_substitute);
		}

		int node = 1;
		hyperarc_set sources = g.get_out_hyperarcs(node);
		std::cout << "\nOutgoing hyperarcs of node " << node << ": {";
		bool first_hyperarc = true;
		for (int hyperarc : sources) {
			if (first_hyperarc) {
				first_hyperarc = false;
				std::cout << hyperarc;
			}
			else {
				std::cout << ", " << hyperarc;
			}
		}
		std::cout << "}\n";

		// sources = g.get_out_hyperarcs(13);

		int hyperarc = 6;
		std::cout << "\nTarget node of hyperarc " << hyperarc << ": " << g.get_target_node(hyperarc) << "\n\n";

		//hyperarc = -2;
		//cout << "\nTarget node of hyperarc " << hyperarc << ": " << g.get_target_node(hyperarc) << "\n";
	}

	void demorgan() {
		std::cout << "de-Morgan\n";

		context c;

		expr x = c.bool_const("x");
		expr y = c.bool_const("y");
		expr conjecture = (!(x && y)) == (!x || !y);

		z3::solver s(c);
		// adding the negation of the conjecture as a constraint.
		s.add(!conjecture);
		std::cout << s << "\n";
		std::cout << s.to_smt2() << "\n";
		switch (s.check()) {
		case unsat:   std::cout << "de-Morgan is valid\n"; break;
		case sat:     std::cout << "de-Morgan is not valid\n"; break;
		case unknown: std::cout << "unknown\n"; break;
		}
	}

	void exists_expr_vector_example() {
		std::cout << "exists expr_vector example\n";
		context c;
		const unsigned N = 10;

		expr_vector xs(c);
		expr x(c);
		expr b(c);
		b = c.bool_val(true);

		for (unsigned i = 0; i < N; i++) {
			std::stringstream x_name;
			x_name << "x_" << i;
			x = c.int_const(x_name.str().c_str());
			xs.push_back(x);
			b = b && x >= 0;
		}

		expr ex(c);
		ex = exists(xs, b);
		std::cout << ex << std::endl;
	}

	void test_fixedpoint() {
		context c;
		fixedpoint fp(c);
		expr_vector queries = fp.from_file("C:\\Users\\omer.r\\source\\repos\\chc-comp22-benchmarks\\LIA\\chc-LIA_001.smt2");
		for (const expr& query : queries) {
			std::cout << query << "\n";
		}
		expr_vector assertions = fp.assertions();
		// cout << "assertions:\n";
		int i = 0;
		expr query(c);
		func_decl_vector decl_vec(c);
		for (expr assertion : assertions) {
			// cout << assertion << "\n";
			expr head_expr = assertion.body().arg(1);
			func_decl head_decl = head_expr.decl();
			if (head_expr.is_false()) {
				std::cout << "\n" << assertion << "\n";
				std::cout << "\n" << assertion.body() << "\n";
				std::cout << "\n" << Z3_get_quantifier_num_bound(c, assertion) << "\n";
				std::cout << "\n" << symbol(c, Z3_get_quantifier_bound_name(c, assertion, 0)) << "\n";
				std::cout << "\n" << z3::sort(c, Z3_get_quantifier_bound_sort(c, assertion, 0)) << "\n";
				std::cout << "\n" << symbol(c, Z3_get_quantifier_bound_name(c, assertion, 1)) << "\n";
				std::cout << "\n" << z3::sort(c, Z3_get_quantifier_bound_sort(c, assertion, 1)) << "\n";

				expr_vector variables(c);
				for (int j = 0; j < Z3_get_quantifier_num_bound(c, assertion); j++) {
					symbol sym = symbol(c, Z3_get_quantifier_bound_name(c, assertion, j));
					expr var = c.constant(sym, z3::sort(c, Z3_get_quantifier_bound_sort(c, assertion, j)));
					variables.push_back(var);
					std::cout << "\n" << var << " " << var.get_sort() << "\n";
				}
				query = exists(variables, assertion.body().arg(0));
				std::cout << "\nthe query is: " << query;
			}
			else {
				fp.register_relation(head_decl);
				symbol name = c.str_symbol(("rule" + std::to_string(i)).c_str());
				fp.add_rule(assertion, name);
				i++;
				decl_vec.push_back(head_decl);
			}
		}

		std::cout << "\nquery: " << fp.query(query);
		std::cout << "\nanswer: " << fp.get_answer();

		//for (func_decl decl : decl_vec) {
			//std::cout << decl << "\n";
		//}

		func_decl decl = decl_vec[0];
		std::cout << "\n" << decl.name() << ":\n";
		for (int j = 0; j < fp.get_num_levels(decl); j++) {
			std::cout << "level " << j << ": \n" << fp.get_cover_delta(j, decl) << "\n\n";
		}
		std::cout << "level -1:\n" << fp.get_cover_delta(-1, decl) << "\n\n";

		decl = decl_vec[18];
		std::cout << decl.name() << ":\n";
		for (int j = 0; j < fp.get_num_levels(decl); j++) {
			std::cout << "level " << j << ": \n" << fp.get_cover_delta(j, decl) << "\n\n";
		}
		std::cout << "level -1:\n" << fp.get_cover_delta(-1, decl) << "\n\n";

		expr assertion = fp.assertions()[16];
		std::cout << "\n" << assertion << "\n";
		func_decl_vector funs(c);
		decl = decl_vec[0];
		funs.push_back(decl);
		expr_vector bodies(c);
		expr body = fp.get_cover_delta(-1, decl);
		bodies.push_back(body);
		std::cout << "\n" << assertion.substitute(funs, bodies) << "\n";
	}

	void test_add_cover() {
		context c;
		fixedpoint fp(c);
		fp.set(init_params(c));
		fp.from_file("C:\\Users\\omer.r\\source\\repos\\chc-comp22-benchmarks\\LIA\\chc-LIA_001.smt2");
		expr_vector assertions = fp.assertions();
		int i = 0;
		expr query(c);
		func_decl_vector decl_vec(c);
		for (expr assertion : assertions) {
			expr head_expr = assertion.body().arg(1);
			func_decl head_decl = head_expr.decl();
			// std::cout << "head pred of assertion " << i << ": " << head_decl.name() << "\n";
			if (head_expr.is_false()) {
				expr_vector variables(c);
				for (int j = 0; j < Z3_get_quantifier_num_bound(c, assertion); j++) {
					symbol sym = symbol(c, Z3_get_quantifier_bound_name(c, assertion, j));
					expr var = c.constant(sym, z3::sort(c, Z3_get_quantifier_bound_sort(c, assertion, j)));
					variables.push_back(var);
				}
				query = exists(variables, assertion.body().arg(0));
			}
			else {
				fp.register_relation(head_decl);
				symbol name = c.str_symbol(("rule" + std::to_string(i)).c_str());
				fp.add_rule(assertion, name);
				i++;
				decl_vec.push_back(head_decl);
			}
		}

		func_decl pred = decl_vec[0];
		expr interp = (c.variable(1, c.int_sort()) >= 1);
		expr cover(c);


		std::cout << "\n=====add interpretation before 1st query=====\n";
		fp.add_cover(-1, pred, interp);
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";


		std::cout << "\n=====1st query=====\n\nres: " << fp.query(query) << "\n";
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		expr false_expr = c.bool_val(false);
		std::cout << "\n=====false query=====\n\nres: " << fp.query(false_expr) << "\n";
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		std::cout << "\n=====add interpretation before 2nd query=====\n";
		fp.add_cover(-1, pred, interp);
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		std::cout << "\n=====2nd query=====\n\nres: " << fp.query(query) << "\n";
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		/*
		std::cout << "\n=====add interpretation before 3rd query=====\n";
		fp.add_cover(-1, pred, interp);
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		std::cout << "\n=====3rd query=====\n\nres: " << fp.query(query) << "\n";
		cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";
		*/
		fixedpoint fp1(c);
		fp1.set(init_params(c));
		i = 0;
		for (expr assertion : assertions) {
			expr head_expr = assertion.body().arg(1);
			func_decl head_decl = head_expr.decl();
			if (!head_expr.is_false()) {
				fp1.register_relation(head_decl);
				symbol name = c.str_symbol(("rule" + std::to_string(i)).c_str());
				fp1.add_rule(assertion, name);
				i++;
			}
		}

		/*
		std::cout << "\n=====new fixedpoint - add interpretation before 1st query=====\n";
		fp1.add_cover(-1, pred, interp);
		cover = fp1.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		std::cout << "\n=====new fixedpoint - 1st query=====\n\nres: " << fp1.query(query) << "\n";
		cover = fp1.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		std::cout << "\n=====new fixedpoint - add interpretation before 2nd query=====\n";
		fp1.add_cover(-1, pred, interp);
		cover = fp1.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";

		std::cout << "\n=====new fixedpoint - 2nd query=====\n\nres: " << fp1.query(query) << "\n";
		cover = fp1.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";
		*/
	}

	void test_to_fact_and_to_query() {
		context c;
		fixedpoint fp(c);
		fp.set(init_params(c));
		fp.from_file("C:\\Users\\omer.r\\source\\repos\\chc-comp22-benchmarks\\LIA\\chc-LIA_001.smt2");
		expr_vector assertions = fp.assertions();
		int i = 0;
		expr query(c);
		func_decl_vector decl_vec(c);
		for (expr assertion : assertions) {
			expr head_expr = assertion.body().arg(1);
			func_decl head_decl = head_expr.decl();
			// std::cout << "head pred of assertion " << i << ": " << head_decl.name() << "\n";
			if (head_expr.is_false()) {
				expr_vector variables(c);
				for (int j = 0; j < Z3_get_quantifier_num_bound(c, assertion); j++) {
					symbol sym = symbol(c, Z3_get_quantifier_bound_name(c, assertion, j));
					expr var = c.constant(sym, z3::sort(c, Z3_get_quantifier_bound_sort(c, assertion, j)));
					variables.push_back(var);
				}
				query = exists(variables, assertion.body().arg(0));
			}
			else {
				fp.register_relation(head_decl);
				symbol name = c.str_symbol(("rule" + std::to_string(i)).c_str());
				fp.add_rule(assertion, name);
				i++;
				decl_vec.push_back(head_decl);
			}
		}
		fp.query(query);

		expr assertion = assertions[17];
		std::cout << "assertion:\n" << assertion << "\n";
		func_decl pred = decl_vec[0];
		expr cover = fp.get_cover_delta(-1, pred);
		std::cout << "\nthe cover of " << pred.name() << ":\n" << cover << "\n";
		func_decl pred1 = decl_vec[18];
		expr cover1 = fp.get_cover_delta(-1, pred1);
		std::cout << "\nthe cover of " << pred1.name() << ":\n" << cover1 << "\n";

		func_decl_vector pred_vec(c);
		pred_vec.push_back(pred);
		pred_vec.push_back(pred1);
		expr_vector cover_vec(c);
		cover_vec.push_back(cover);
		cover_vec.push_back(cover1);
		expr body = assertion.body().arg(0);
		expr new_body = body.substitute(pred_vec, cover_vec);
		//std::cout << "\nthe body:\n" << body << "\n";
		//std::cout << "\nthe new body:\n" << new_body << "\n";

		expr_vector variables(c);
		for (int j = 0; j < Z3_get_quantifier_num_bound(c, assertion); j++) {
			symbol sym = symbol(c, Z3_get_quantifier_bound_name(c, assertion, j));
			expr var = c.constant(sym, z3::sort(c, Z3_get_quantifier_bound_sort(c, assertion, j)));
			variables.push_back(var);
		}

		expr fact = forall(variables, implies(new_body, assertion.body().arg(1)));
		std::cout << "\nthe new fact:\n" << fact << "\n";
		//std::cout << "\nthe new fact without the quantifier:\n" << fact.body() << "\n";

		func_decl_vector pred_vec1(c);
		pred_vec1.push_back(pred);
		expr_vector cover_vec1(c);
		cover_vec1.push_back(cover);
		expr head = assertion.body().arg(1);
		expr new_head = head.substitute(pred_vec1, cover_vec1);
		//std::cout << "\nthe head:\n" << head << "\n";
		//std::cout << "\nthe new head:\n" << new_head << "\n";

		//std::cout << "\nnew_head:\n" << new_head << "\n";
		//std::cout << "\n!(new_head):\n" << !(new_head) << "\n";
		//std::cout << "\n(new_body && (!(new_head))):\n" << (new_body && (!(new_head))) << "\n";
		//std::cout << "\nexists(new_body && (!(new_head))):\n" << exists(variables,(new_body && (!(new_head)))) << "\n";

		expr query1 = exists(variables, (new_body && (!(new_head))));
		std::cout << "\nthe new query:\n" << query1 << "\n";
		// std::cout << "\nthe new query is:" << fp.query(query1) << "\n";

		/*
		std::cout << "\nmk_and experiment:\n";
		std::cout << new_head << "\n";
		std::cout << (new_head && new_head) << "\n";
		std::cout << ((new_head && new_head) && new_head) << "\n";
		std::cout << ((new_head && new_head) && new_head).simplify() << "\n";
		*/
	}

	void test_spacer_wrapper() {
		spacer s("C:\\Users\\omer.r\\source\\repos\\chc-comp22-benchmarks\\LIA\\chc-LIA_001.smt2");

		const func_decl_vector& head_predicate_vec = s.get_head_predicate_vec();
		const std::vector<func_decl_vector>& body_predicates_vec = s.get_body_predicates_vec();
		const std::vector<func_decl_vector>& body_predicates_set = s.get_body_predicates_set();
		const std::map<func_decl, int, compare_func_decl>& predicate_id_map = s.get_predicate_id_map();
		const std::map<func_decl, expr, compare_func_decl>& predicate_interpretation_map = s.get_predicate_interpretation_map();
		const std::vector<expr_vector>& bound_variables_vec = s.get_bound_variables_vec();

		std::cout << "\n==========clauses==========\n";
		for (int i = 0; i < s.num_of_clauses(); i++) {
			std::cout << "\n=====clause " << i << "=====\n";
			std::cout << "head predicate:\t\t" << head_predicate_vec[i].name() << "\n";
			std::cout << "head predicate id:\t" << s.head_predicate(i) << "\n";

			std::cout << "body predicates:\t{";
			const func_decl_vector& body_preds = body_predicates_vec[i];
			for (int j = 0; j < body_preds.size(); j++) {
				if (j == 0) {
					std::cout << body_preds[j].name();
				}
				else {
					std::cout << ", " << body_preds[j].name();
				}
			}
			std::cout << "}\n";

			std::cout << "body predicates set:\t{";
			const func_decl_vector& body_preds_set = body_predicates_set[i];
			for (int j = 0; j < body_preds_set.size(); j++) {
				if (j == 0) {
					std::cout << body_preds_set[j].name();
				}
				else {
					std::cout << ", " << body_preds_set[j].name();
				}
			}
			std::cout << "}\n";

			std::cout << "body predicates ids:\t{";
			std::multiset<int> body_preds_ids = s.body_predicates(i);
			bool first_node = true;
			for (int pred : body_preds_ids) {
				if (first_node) {
					first_node = false;
					std::cout << pred;
				}
				else {
					std::cout << ", " << pred;
				}
			}
			std::cout << "}\n";

			std::cout << "bound variables:\t{";
			const expr_vector& variables = bound_variables_vec[i];
			for (int j = 0; j < variables.size(); j++) {
				if (j == 0) {
					std::cout << variables[j];
				}
				else {
					std::cout << ", " << variables[j];
				}
			}
			std::cout << "}\n";
		}

		std::cout << "\n==========predicates==========\n";
		for (const auto& [predicate, id] : predicate_id_map) {
			std::cout << "\n=====" << predicate.name() << "=====\n";
			std::cout << "id: " << id << "\n";
			for (const auto& [predicate1, interp] : predicate_interpretation_map) {
				if (predicate.id() == predicate1.id()) {
					std::cout << "interpretation: " << interp << "\n";
				}
			}
		}

		std::cout << "\nnumber of clauses: " << s.num_of_clauses() << "\n";
		std::cout << "number of predicates: " << s.num_of_predicates() << "\n";

		std::cout << "\n==========solve==========\n";
		std::set<int> clause_ids;
		for (int i = 0; i < s.num_of_clauses(); i++) {
			clause_ids.insert(i);
		}
		result res = s.solve(clause_ids);
		std::cout << "\nquery all clauses\nresult: ";
		if (res == result::sat) {
			std::cout << "sat\n";
		}
		else if (res == result::unsat) {
			std::cout << "unsat\n";
		}
		else {
			std::cout << "unknown\n";
		}
		std::cout << "\n==========predicates==========\n";
		for (const auto& [predicate, id] : predicate_id_map) {
			std::cout << "\n=====" << predicate.name() << "=====\n";
			std::cout << "id: " << id << "\n";
			for (const auto& [predicate1, interp] : predicate_interpretation_map) {
				if (predicate.id() == predicate1.id()) {
					std::cout << "interpretation: " << interp << "\n";
				}
			}
		}

		res = s.solve(clause_ids);
		std::cout << "\nquery all clauses again\nresult: ";
		if (res == result::sat) {
			std::cout << "sat\n";
		}
		else if (res == result::unsat) {
			std::cout << "unsat\n";
		}
		else {
			std::cout << "unknown\n";
		}

		/*
		std::cout << "\n==========to_fact and to_query==========\n";
		s.amend_clause(0);
		s.amend_clause(2);
		s.amend_clause(11);
		s.amend_clause(16);
		s.amend_clause(17);
		s.amend_clause(18);
		s.amend_clause(22);
		*/


		std::cout << "\n==========amend_clause==========\n";
		bool update = s.amend_clause(16);
		std::cout << "\n" << update << "\n";

		std::cout << "\n==========amend_clauses==========\n";
		clause_ids.clear();
		std::set<int> facts_ids;
		facts_ids.insert(15);
		int query_id = 16;
		// update = s.amend_clauses(clause_ids, facts_ids, query_id);
		std::cout << "\n" << update << "\n";

		std::cout << "\n==========predicates==========\n";
		for (const auto& [predicate, id] : predicate_id_map) {
			std::cout << "\n=====" << predicate.name() << "=====\n";
			std::cout << "id: " << id << "\n";
			for (const auto& [predicate1, interp] : predicate_interpretation_map) {
				if (predicate.id() == predicate1.id()) {
					std::cout << "interpretation: " << interp << "\n";
				}
			}
		}
	}

	void test_structural_horn(std::string fileName) {
		structural_horn s(fileName.c_str());
		result res = s.solve();
		if (res == result::sat) {
			std::cout << "\nthe set of chcs is not satisfiable\n";
		}
		else if (res == result::unsat) {
			std::cout << "\nthe set of chcs is satisfiable\n";
		}
		else {
			std::cout << "\nthe satisfiability of the set of chcs is unknown\n";
		}
	}
}