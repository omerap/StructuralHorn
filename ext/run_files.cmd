#!/bin/bash
#SBATCH --job-name array_run

# StructuralHorn options:
# --chc-solver (0 - spacer, 1 - eldarica)
# --algorithm (0 - structural horn, 1 - underlying solver)
# --hyperarc-sources (0 - set, 1 - multiset)
# --hyperarc-weight (0 - number of sources, 1 - 1)
# --random-seed
# --array-theory (0 - no, 1 - yes)
# --global-guidance (0 - no, 1 - yes)
# --test-mode (0 - off, 1 - on)
# --inc (false - off, true - on)
# --verbose (0 - print only final result, 1 - print the interpretation in each iteration)

while getopts i:o:r:t:m:c:a:y:h:w:s:d:g:l:v: flag
do
    case "${flag}" in
        i) inputdir=${OPTARG};;
        o) outputdir=${OPTARG};;
        r) repodir=${OPTARG};;
        t) timeout=${OPTARG};;
        m) memout=${OPTARG};;
        c) chcsolver=${OPTARG};;
        a) alg=${OPTARG};;
        y) arrayTheory=${OPTARG};;
        h) hyperarcSources=${OPTARG};;
        w) hyperarcWeight=${OPTARG};;
        s) seed=${OPTARG};;
        d) testMode=${OPTARG};;
        g) globalGuidance=${OPTARG};;
        l) incremental=${OPTARG};;
        v) verbosity=${OPTARG};;
    esac
done

echo "All jobs in this array have:"
echo "- SLURM_ARRAY_JOB_ID=${SLURM_ARRAY_JOB_ID}"
echo "- SLURM_ARRAY_TASK_COUNT=${SLURM_ARRAY_TASK_COUNT}"
echo "- SLURM_ARRAY_TASK_MIN=${SLURM_ARRAY_TASK_MIN}"
echo "- SLURM_ARRAY_TASK_MAX=${SLURM_ARRAY_TASK_MAX}"
 
echo "This job in the array has:"
echo "- SLURM_JOB_ID=${SLURM_JOB_ID}"
echo "- SLURM_ARRAY_TASK_ID=${SLURM_ARRAY_TASK_ID}"

# grab our filename from a directory listing
FILES=($(ls -1 ${inputdir}))
FILENAME=${FILES[$SLURM_ARRAY_TASK_ID]}
echo "My input file is ${FILENAME}"

case ${alg} in
    0)
        python3 ${repodir}/ext/brunch.py --out ${outputdir} --cpu ${timeout} --mem ${memout} --format base:Result:Cpu:Status:run_structural_horn:mkRuleSat:Iterations ${inputdir}/${FILENAME} -- ${repodir}/build/src/StructuralHorn --chc-solver=${chcsolver} --algorithm=${alg} --hyperarc-sources=${hyperarcSources} --hyperarc-weight=${hyperarcWeight} --random-seed=${seed} --array-theory=${arrayTheory} --global-guidance=${globalGuidance} --test-mode=${testMode} --inc=${incremental} --verbose=${verbosity} {f}
        ;;
    1)
        case ${chcsolver} in
            0) python3 ${repodir}/ext/brunch.py --out ${outputdir} --cpu ${timeout} --mem ${memout} --format base:Result:Cpu:Status:run_spacer ${inputdir}/${FILENAME} -- ${repodir}/build/src/StructuralHorn --chc-solver=${chcsolver} --algorithm=${alg} --hyperarc-sources=${hyperarcSources} --hyperarc-weight=${hyperarcWeight} --random-seed=${seed} --array-theory=${arrayTheory} --global-guidance=${globalGuidance} --test-mode=${testMode} --inc=${incremental} --verbose=${verbosity} {f};;
            1) python3 ${repodir}/ext/brunch.py --out ${outputdir} --cpu ${timeout} --mem ${memout} --format base:Result:Cpu:Status:run_eldarica ${inputdir}/${FILENAME} -- ${repodir}/build/src/StructuralHorn --chc-solver=${chcsolver} --algorithm=${alg} --hyperarc-sources=${hyperarcSources} --hyperarc-weight=${hyperarcWeight} --random-seed=${seed} --array-theory=${arrayTheory} --global-guidance=${globalGuidance} --test-mode=${testMode} --inc=${incremental} --verbose=${verbosity} {f};;
        esac
        ;;
esac
