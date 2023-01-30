#!/bin/bash

# StructuralHorn options:
# --chc-solver (0 - spacer, 1 - eldarica)
# --algorithm (0 - structural horn, 1 - underlying solver)
# --array-theory (0 - no, 1 - yes)
# --hyperarc-sources (0 - set, 1 - multiset)
# --hyperarc-weight (0 - number of sources, 1 - 1)
# --random-seed
# --test-mode (0 - off, 1 - on)

timeout=900
memout=8192
chcsolver=0
alg=0
arrayTheory=0
hyperarcSources=0
hyperarcWeight=0
seed=0
testMode=0

while getopts i:o:r:t:m:c:a:y:h:w:s:d: flag
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
    esac
done

outputsubdir=""
case ${chcsolver} in
    0)
        case ${alg} in
            0) outputsubdir=${outputdir}/sthorn_spacer_`date +%F_%T`_${seed};;
            1) outputsubdir=${outputdir}/spacer_`date +%F_%T`_${seed};;
        esac
        ;;
    1)
        case ${alg} in
            0) outputsubdir=${outputdir}/sthorn_eldarica_`date +%F_%T`_${seed};;
            1) outputsubdir=${outputdir}/eldarica_`date +%F_%T`_${seed};;
        esac
        ;;
esac

mkdir $outputsubdir
mkdir $outputsubdir/tool
mkdir $outputsubdir/slurm
mkdir $outputsubdir/stats
 
# get count of files in this directory
NUMFILES=$(ls -1 ${inputdir} | wc -l)

# subtract 1 as we have to use zero-based indexing (first element is 0)
ZBNUMFILES=$(($NUMFILES - 1))

# submit array of jobs to SLURM
if [ $ZBNUMFILES -ge 0 ]; then
  sbatch --array=0-$ZBNUMFILES --output=${outputsubdir}/slurm/slurm_%A_%a run_files.cmd -i ${inputdir} -o ${outputsubdir} -r ${repodir} -t ${timeout} -m ${memout} -c ${chcsolver} -a ${alg} -y ${arrayTheory} -h ${hyperarcSources} -w ${hyperarcWeight} -s ${seed} -d ${testMode}
else
  echo "No jobs to submit, since no input files in this directory."
fi