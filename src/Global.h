#pragma once
#include <iostream>
#include <string>

/** Global variables */
namespace structuralHorn {

    struct SHParams {
        std::string fName;

        /* verbosity level */
        unsigned verbosity;

        /* Underlying chc solver
            0 - spacer, 1 - eldarica */
        unsigned chc_solver;

        /* Algorithm
            0 - structural horn, 1 - underlying solver */
        unsigned algorithm;

        /* Data structure of hyperarc sources when measuring hyperpaths
            0 - set, 1 - multiset */
        unsigned hyperarc_sources_distance_measure;

        /* Weight of hyperarcs when measuring hyperpaths
            0 - number of sources, 1 - 1 */
        unsigned hyperarc_weight_distance_measure;

        /* Random seed to be used by the SMT solver */
        unsigned random_seed;
        
        /* Theory of arrays
            0 - no, 1 - yes */
        unsigned array_theory;
        
        /* Spacer global guidance
            0 - no, 1 - yes */
        unsigned global_guidance;

        /* Test mode
            0 - off, 1 - on*/
        unsigned test_mode;
	
	/* Incremental mode - use the same solver object in different calls to solve
            0 - off, 1 - on*/
        bool inc_mode;
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
} 

#define VERBOSE(LVL, CODE)                                                     \
  do {                                                                         \
    if (LVL <= ::structuralHorn::gParams.verbosity) { CODE; }                  \
  } while (0)
  
