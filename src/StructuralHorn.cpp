// StructHorn.cpp : Defines the entry point for the application.

#include <string>

#include "boost/program_options.hpp"
#include "z3++.h"

#include "StructuralHorn.h"
#include "Hypergraph.h"
#include "Global.h"
#include "Stats.h"
#include "Spacer.h"
#include "Test.h"

using namespace std;
using namespace structuralHorn;
using namespace z3;

namespace po = boost::program_options;

std::string parseCmdLine(int argc, char** argv) {
    po::options_description generic("Options");
    generic.add_options()("help", "produce help message")
        ("print-params", "print current parameters")
        ("verbose,v", po::value<unsigned>(&gParams.verbosity)->default_value(0), "Verbosity level: 0 means silent")
        ("version", "Print version string")
        ("chc-solver", po::value<unsigned>(&gParams.chc_solver)->default_value(0),
            "Underlying chc solver: 0 - spacer, 1 - eldarica")
        ("algorithm", po::value<unsigned>(&gParams.algorithm)->default_value(0),
			"0 - structural horn, 1 - underlying solver")
        ("array-theory", po::value<unsigned>(&gParams.array_theory)->default_value(0),
            "0 - no, 1 - yes")
		("hyperarc-sources", po::value<unsigned>(&gParams.hyperarc_sources_distance_measure)->default_value(0),
			"Data structure of hyperarc sources when measuring hyperpaths: 0 - set, 1 - multiset")
		("hyperarc-weight", po::value<unsigned>(&gParams.hyperarc_weight_distance_measure)->default_value(0),
			"Weight of hyperarcs when measuring hyperpaths: 0 - number of sources, 1 - 1")
        ("random-seed", po::value<unsigned>(&gParams.random_seed)->default_value(0),
            "Random seed to be used by the SMT solver")
        ("test-mode", po::value<unsigned>(&gParams.test_mode)->default_value(0),
            "Test mode: 0 - off, 1 - on")
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

        if (!vm.count("input-file")) {
            cout << "Error: No SMT file specified\n";
            std::exit(1);
        }

        gParams.fName = vm["input-file"].as<string>();

        // VERBOSE(2, vout() << gParams << "\n";);

        return gParams.fName;
    }
    catch (std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
        std::exit(1);
    }
}

result run_structural_horn(std::string fileName) {
#ifdef __unix__
    SH_MEASURE_FN;
#endif
    structural_horn s(fileName.c_str());
    result res = s.solve();
    return res;
}

result run_spacer(std::string fileName) {
#ifdef __unix__
    SH_MEASURE_FN;
#endif
    context c;
    fixedpoint fp(c);
    fp.set(init_params(c));
    fp.from_file(fileName.c_str());
    
    expr_vector assertions = fp.assertions();
    int i = 0;
    expr query(c);

    for (expr assertion : assertions) {
        expr head_expr = assertion.body().arg(1);
        func_decl head_decl = head_expr.decl();
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
        }
    }
    check_result res = fp.query(query);
    if (res == z3::sat) {
        return result::sat;
    }
    else if (res == z3::unsat) {
        return result::unsat;
    }
    else {
        return result::unknown;
    }
}

result run_eldarica(std::string fileName) {
#ifdef __unix__
    SH_MEASURE_FN;
#endif
    return result::unknown;
}


int main(int argc, char** argv)
{
	std::string fileName = parseCmdLine(argc, argv);
    result res = result::unknown;

	try {
        if (gParams.test_mode == 0) {
            if (gParams.algorithm == 0) { // StructuralHorn
                res = run_structural_horn(fileName);
            }
            else { // Underlying solver
                if (gParams.chc_solver == 0) { // Spacer
                    res = run_spacer(fileName);
                }
                else { // Eldarica
                    res = run_eldarica(fileName);
                }
            }
        }
        else {
            test_main(fileName);
        }
	}
	catch (std::exception& ex) {
        vout() << ex.what() << "\n";
	}
    if (gParams.chc_solver == 0) { // Spacer
        Z3_finalize_memory();
    }

    if (res == result::sat) {
        std::cout << "\nSAT\n";
    }
    else if (res == result::unsat) {
        std::cout << "\nUNSAT\n";
    }
    else {
        std::cout << "\nUNKNOWN\n";
    }

#ifdef __unix__
    if (res == result::sat) {
        Stats::set("Result", "SAT");
    }
    else if (res == result::unsat) {
        Stats::set("Result", "UNSAT");
    }
    else {
        Stats::set("Result", "UNKNOWN");
    }
    VERBOSE(0, Stats::PrintBrunch(outs()););
#endif

	return 0;
}
