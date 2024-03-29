#include "Global.h"

namespace structuralHorn {

    SHParams gParams;

    std::ostream& operator<<(std::ostream& out, const SHParams& p) {
        out << "STRUCTURAL HORN PARAMETERS\n"
            << "\tfName = " << p.fName << "\n"
            << "\tverbosity = " << p.verbosity << "\n"
            << "\tchc-solver = " << (p.chc_solver == 0 ? "Spacer" : "Eldarica") << "\n"
            << "\talgorithm = " << (p.chc_solver == 0 ? "StructuralHorn" : "underlying solver") << "\n"
            << "\thyperarc-sources = " << (p.hyperarc_sources_distance_measure == 0 ? "set" : "multiset") << "\n"
            << "\thyperarc-weight = " << (p.hyperarc_weight_distance_measure == 0 ? "number of sources" : "1") << "\n"
            << "\trandom_seed = " << p.random_seed << "\n"
            << "\tarray_theory = " << (p.array_theory == 0 ? "no" : "yes") << "\n"
            << "\tglobal_guidance = " << (p.global_guidance == 0 ? "no" : "yes") << "\n"
            << "\ttest_mode = " << (p.test_mode == 0 ? "off" : "on") << "\n"
            << "\tinc_mode = " << (p.inc_mode == false ? "off" : "on") << "\n"
            << "END";
        return out;
    }

}
