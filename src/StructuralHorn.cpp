// StructHorn.cpp : Defines the entry point for the application.
//

#include <string>

#include "boost/program_options.hpp"
#include "z3++.h"

#include "StructuralHorn.h"
#include "Hypergraph.h"
#include "Global.h"
#include "Spacer.h"

using namespace std;
using namespace structuralHorn;
namespace po = boost::program_options;
using namespace z3;

std::string parseCmdLine(int argc, char** argv) {
    po::options_description generic("Options");
    generic.add_options()("help", "produce help message")
        ("print-params", "print current parameters")
        //("alg", po::value<unsigned>(&gParams.alg)->default_value(0),"Solver: 0 - Z3, 1 - IH")
        // ("verbose,v", po::value<unsigned>(&gParams.verbosity)->default_value(0), "Verbosity level: 0 means silent")("version", "Print version string")
        ("hyperarc-sources", po::value<unsigned>(&gParams.hyperarc_sources_distance_measure)->default_value(0),
			"Data structure of hyperarc sources when measuring hyperpaths: 0 - set, 1 - multiset")
		("hyperarc-weight", po::value<unsigned>(&gParams.hyperarc_weight_distance_measure)->default_value(0),
			"Weight of hyperarcs when measuring hyperpaths: 0 - number of sources, 1 - 1")
		;

    po::options_description hidden("Hidden options");
    hidden.add_options()("input-file", po::value<string>(), "input file");

    po::options_description cmdline;
    cmdline.add(generic).add(hidden);

    po::positional_options_description p;
    p.add("input-file", -1);

    try {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
            .options(cmdline)
            .positional(p)
            .run(),
            vm);
        po::notify(vm);

        if (vm.count("help")) {
			std::cout << generic << "\n";
            std::exit(1);
        }

        if (vm.count("print-params")) {
			std::cout << gParams << "\n";
            std::exit(1);
        }

        if (vm.count("version")) {
			std::cout << "StructuralHorn (" << 0 << ")\n";
            std::exit(1);
        }

        /*if (!vm.count("input-file")) {
            cout << "Error: No SMT file specified\n";
            std::exit(1);
        }*/

        // gParams.fName = vm["input-file"].as<string>();

        // VERBOSE(2, vout() << gParams << "\n";);

        // return gParams.fName;
		return "";
    }
    catch (std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
        std::exit(1);
    }
}


void test_hypergraph() {
	hypergraph g(0,4);

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

	hyperarc_set optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	while (!optimal_hyperpath.empty()) {
		std::cout << "\nOptimal hyperpath: {";
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
		std::cout << g;
		optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
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
	hypergraph g(0, 2);

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

	hyperarc_set optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	while (!optimal_hyperpath.empty()) {
		std::cout << "\nOptimal hyperpath: {";
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
		std::cout << g;
		optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
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
			std::cout << "\n" << symbol(c, Z3_get_quantifier_bound_name(c, assertion ,0)) << "\n";
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


	//expr false_expr = c.bool_val(false);
	std::cout << "\nquery: " << fp.query(query);
	std::cout << "\nanswer: " << fp.get_answer();

	//for (func_decl decl : decl_vec) {
		//std::cout << decl << "\n";
	//}

	func_decl decl = decl_vec[0];
	std::cout << decl.name() << ":\n";
	for (int j = 0; j < fp.get_num_levels(decl); j++) {
		std::cout << "level " << j << ": \n" << fp.get_cover_delta(j, decl) << "\n\n";
	}
	std::cout << "level -1:\n" << fp.get_cover_delta(-1, decl) << "\n\n";

	decl = decl_vec[17];
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

void test_spacer_wrapper() {
	spacer s("C:\\Users\\omer.r\\source\\repos\\chc-comp22-benchmarks\\LIA\\chc-LIA_001.smt2");

	std::cout << "head predicates:\n";
	const func_decl_vector& head_predicate_vec = s.get_head_predicate_vec();
	for (int i = 0; i < head_predicate_vec.size(); i++) {
		std::cout << "clause " << i << ": " << head_predicate_vec[i].name() << "\n";
	}

	std::cout << "\nbody predicates:\n";
	const std::vector<func_decl_vector>& body_predicates_vec = s.get_body_predicates_vec();
	for (int i = 0; i < body_predicates_vec.size(); i++) {
		std::cout << "clause " << i << ": {";
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
	}

	std::cout << "\nbody predicates set:\n";
	const std::vector<func_decl_vector>& body_predicates_set = s.get_body_predicates_set();
	for (int i = 0; i < body_predicates_set.size(); i++) {
		std::cout << "clause " << i << ": {";
		const func_decl_vector& body_preds = body_predicates_set[i];
		for (int j = 0; j < body_preds.size(); j++) {
			if (j == 0) {
				std::cout << body_preds[j].name();
			}
			else {
				std::cout << ", " << body_preds[j].name();
			}
		}
		std::cout << "}\n";
	}

	std::cout << "\npredicate -> id:\n";
	const std::map<func_decl, int, compare_func_decl>& predicate_id_map = s.get_predicate_id_map();
	for (const auto& [predicate, id] : predicate_id_map) {
		std::cout << predicate.name() << " -> " << id << "\n";
	}

	std::cout << "\npredicate -> interpretation:\n";
	const std::map<func_decl, expr, compare_func_decl>& predicate_interpretation_map = s.get_predicate_interpretation_map();
	for (const auto& [predicate, interp] : predicate_interpretation_map) {
		std::cout << predicate.name() << " -> " << interp << "\n";
	}

	std::cout << "\nnumber of clauses: " << s.num_of_clauses() << "\n";
	std::cout << "number of predicates: " << s.num_of_predicates() << "\n\n";
	
	for (int clause_id = 0; clause_id < s.num_of_clauses(); clause_id++) {
		std::cout << "head predicate of clause " << clause_id << ": " << s.head_predicate(clause_id) << "\n";
	}

	std::cout << "\n";
	for (int clause_id = 0; clause_id < s.num_of_clauses(); clause_id++) {
		std::cout << "body predicates of clause " << clause_id << ": {";
		std::multiset<int> body_preds = s.body_predicates(clause_id);
		bool first_node = true;
		for (int pred : body_preds) {
			if (first_node) {
				first_node = false;
				std::cout << pred;
			}
			else {
				std::cout << ", " << pred;
			}
		}
		std::cout << "}\n";
		//<< s.head_predicate(clause_id) << "\n";
	}

	// s.amend_clause(17);
}

int main(int argc, char** argv)
{
	std::string fileName = parseCmdLine(argc, argv);
	try {
		//test_hypergraph();
		test_hypergraph2();
		// demorgan();
		// exists_expr_vector_example();
		// test_fixedpoint();
		// test_spacer_wrapper();
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	return 0;
}
