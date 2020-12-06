#!/bin/bash

# Main directory, where your tmp files will be during execution
#SBATCH -D /tmp
# Name of the job
#SBATCH -J QCumulant
# Name of the queue, where your job is going to be executed
#SBATCH -p compute
# Max time which job can take: Day-HOURS:MIN:SEC
#SBATCH --time=0-01:30:00
# Output from the job (-o - output -e - error log)
#SBATCH -o /mnt/pool/2/lbavinh/DirectCumulant/slurm/slurm-%A.out
#SBATCH -e /mnt/pool/2/lbavinh/DirectCumulant/slurm/slurm-%A.err

export MAIN_DIR=/mnt/pool/2/lbavinh/DirectCumulant
export OUT_DIR=${MAIN_DIR}/OUT
export TMP_DIR=${MAIN_DIR}/TMP/TMP_${SLURM_JOB_ID}
export OUT_FILE=${OUT_DIR}/v2QC.root
export OUT_LOG=${OUT_DIR}/v2QC_${SLURM_JOB_ID}.log

mkdir -p ${OUT_DIR}
mkdir -p ${TMP_DIR}

cp ${MAIN_DIR}/macro.C ${TMP_DIR}

cd

# Set correct environment variables (needed version of root)
source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh

root -l -b -q ${TMP_DIR}/macro.C+ &>> ${OUT_LOG}

rm -rf $TMP_DIR
