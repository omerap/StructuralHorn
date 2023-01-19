#pragma once
#include <iostream>
#include <string>

/** Global variables */
namespace structuralHorn {

    struct SHParams {
        // std::string fName;

        /* Data structure of hyperarc sources when measuring hyperpaths
            0 - set, 1 - multiset*/
        unsigned hyperarc_sources_distance_measure;

        /* Weight of hyperarcs when measuring hyperpaths
            0 - number of sources, 1 - 1*/
        unsigned hyperarc_weight_distance_measure;
    };

    std::ostream& operator<<(std::ostream& out, const SHParams& p);

    extern SHParams gParams;

    /** Output streams */

    /// std out
    inline std::ostream& outs() { return std::cout; }
    /// std err
    inline std::ostream& errs() { return std::cerr; }
    /// log stream. use in LOG() macro.
    inline std::ostream& logs() { return std::cerr; }
    /// verbose
    inline std::ostream& vout() { return std::cout; }
} // namespace iterativeHorn

#define VERBOSE(LVL, CODE)                                                     \
  do {                                                                         \
    if (LVL <= ::iterativeHorn::gParams.verbosity) { CODE; }                             \
  } while (0)