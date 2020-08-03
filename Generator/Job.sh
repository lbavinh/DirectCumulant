#!/bin/bash

# Main directory, where your tmp files will be during execution
#SBATCH -D /tmp
# Name of the job
#SBATCH -J EvGen
# Name of the queue, where your job is going to be executed
#SBATCH -p compute
# Max time which job can take: Day-HOURS:MIN:SEC
#SBATCH --time=0-00:50:00
# Number of arrays (by default: 1-10)
#SBATCH -a 1-10
# Output from the job (-o - output -e - error log)
#SBATCH -o /mnt/pool/2/lbavinh/EventGenerator/slurm/slurm-%A.out
#SBATCH -e /mnt/pool/2/lbavinh/EventGenerator/slurm/slurm-%A.err


export MAIN_DIR=/mnt/pool/2/lbavinh/EventGenerator
export OUT_DIR=${MAIN_DIR}/OUT
export FILELIST=${OUT_DIR}/Non-flowPairWise/runlist.list
export INFILE=`sed "${SLURM_ARRAY_TASK_ID}q;d" $FILELIST`
export TMP_DIR=${MAIN_DIR}/TMP/TMP_${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}
export OUT_LOG=${OUT_DIR}/log/v2hadron_${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.log

echo "JobId: ${SLURM_ARRAY_JOB_ID}; TaskId: ${SLURM_ARRAY_TASK_ID};"
echo "Input file: ${INFILE}"

mkdir -p ${OUT_DIR}
mkdir -p ${OUT_DIR}/log
mkdir -p ${TMP_DIR}

cp ${MAIN_DIR}/v2hadron.C ${TMP_DIR}

cd

# Set correct environment variables (needed version of root)
source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh

root -l -b -q ${TMP_DIR}/v2hadron.C+'("'${INFILE}'")' &>> ${OUT_LOG}

rm -rf $TMP_DIR