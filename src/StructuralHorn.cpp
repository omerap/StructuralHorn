// StructHorn.cpp : Defines the entry point for the application.
//

#include "StructuralHorn.h"
#include "Hypergraph.h"
#include "Global.h"
#include <string>

#include "boost/program_options.hpp"

using namespace std;
using namespace structuralHorn;
namespace po = boost::program_options;

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

	node_multiset sources0;
	sources0.insert(0);
	g.insert_hyperarc(0, sources0, 1);

	node_multiset sources1;
	sources1.insert(1);
	g.insert_hyperarc(1, sources1, 2);

	node_multiset sources2;
	sources2.insert(2);
	g.insert_hyperarc(2, sources2, 3);

	node_multiset sources3;
	sources3.insert(2);
	g.insert_hyperarc(3, sources3, 3);

	node_multiset sources4;
	sources4.insert(1);
	sources4.insert(3);
	g.insert_hyperarc(4, sources4, 2);

	node_multiset sources5;
	sources5.insert(1);
	sources5.insert(3);
	g.insert_hyperarc(5, sources5, 1);

	node_multiset sources6;
	sources6.insert(1);
	sources6.insert(3);
	sources6.insert(3);
	g.insert_hyperarc(6, sources6, 1);

	node_multiset sources7;
	sources7.insert(1);
	g.insert_hyperarc(7, sources7, 4);

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
		optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	}
}

int main(int argc, char** argv)
{
	std::string fileName = parseCmdLine(argc, argv);
	test_hypergraph();
	return 0;
}
