// StructHorn.cpp : Defines the entry point for the application.
//

#include "StructuralHorn.h"
#include "Hypergraph.h"
#include "Global.h"
#include <string>

#include "boost/program_options.hpp"
#include "z3++.h"

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
            cout << generic << "\n";
            std::exit(1);
        }

        if (vm.count("print-params")) {
            cout << gParams << "\n";
            std::exit(1);
        }

        if (vm.count("version")) {
            cout << "StructuralHorn (" << 0 << ")\n";
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
        cout << "Error: " << e.what() << "\n";
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

	cout << g;

	hyperarc_set optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	while (!optimal_hyperpath.empty()) {
		cout << "\nOptimal hyperpath: {";
		bool first_hyperarc = true;
		for (int hyperarc : optimal_hyperpath) {
			if (first_hyperarc) {
				first_hyperarc = false;
				cout << hyperarc;
			}
			else {
				cout << ", " << hyperarc;
			}
		}
		cout << "}\n";
		cout << g;
		optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	}

	int node = 1;
	hyperarc_set sources = g.get_out_hyperarcs(node);
	cout << "\nOutgoing hyperarcs of node " << node << ": {";
	bool first_hyperarc = true;
	for (int hyperarc : sources) {
		if (first_hyperarc) {
			first_hyperarc = false;
			cout << hyperarc;
		}
		else {
			cout << ", " << hyperarc;
		}
	}
	cout << "}\n";

	// sources = g.get_out_hyperarcs(13);

	int hyperarc = 6;
	cout << "\nTarget node of hyperarc " << hyperarc << ": " << g.get_target_node(hyperarc) << "\n\n";

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

int main(int argc, char** argv)
{
	std::string fileName = parseCmdLine(argc, argv);
	try {
		test_hypergraph();
		demorgan();
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	return 0;
}
