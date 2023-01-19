#include "Global.h"

namespace structuralHorn {

    SHParams gParams;

    std::ostream& operator<<(std::ostream& out, const SHParams& p) {
        out << "STRUCTURAL HORN PARAMETERS\n"
            //<< "\tfName = " << p.fName << "\n"
            //<< "\talg = " << (p.alg == 0 ? "Z3" : "Iterative Horn") << "\n"
            << "\thyperarc-sources = " << (p.hyperarc_sources_distance_measure == 0 ? "set" : "multiset") << "\n"
            << "\thyperarc-weight = " << (p.hyperarc_weight_distance_measure == 0 ? "number of sources" : "1") << "\n"
            << "END";
        return out;
    }

}