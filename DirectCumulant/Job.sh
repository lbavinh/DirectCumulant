#!/bin/bash

# Main directory, where your tmp files will be during execution
#SBATCH -D /tmp
# Name of the job
#SBATCH -J QC
# Name of the queue, where your job is going to be executed
#SBATCH -p compute
# Max time which job can take: Day-HOURS:MIN:SEC
#SBATCH --time=0-02:30:00
# Output from the job (-o - output -e - error log)
#SBATCH -o /dev/null
#SBATCH -e /dev/null
export MAIN_DIR=/mnt/pool/2/${USER}/QCumulant
export OUT_DIR=${MAIN_DIR}/OUT
export TMP_DIR=${MAIN_DIR}/TMP/TMP_${SLURM_JOB_ID}
export IN_FILE=${MAIN_DIR}/runlist.list
export OUT_FILE=${OUT_DIR}/test.root
export OUT_LOG=${OUT_DIR}/QCumulant_${SLURM_JOB_ID}.log
export CONFIG_FILE=${MAIN_DIR}/.qcumulant.cfg

mkdir -p ${OUT_DIR}
mkdir -p ${TMP_DIR}

cp ${MAIN_DIR}/FlowQCumulant.C ${TMP_DIR}
cp ${MAIN_DIR}/utilities.C ${TMP_DIR}
cp ${MAIN_DIR}/constants.C ${TMP_DIR}

cd

# Set correct environment variables
source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh
source /mnt/pool/2/lbavinh/Soft/PicoDst/build/setPicoDst.sh
root -l -b -q ${TMP_DIR}/FlowQCumulant.C+'("'${IN_FILE}'","'${OUT_FILE}'","'${CONFIG_FILE}'")' &>> ${OUT_LOG}
# root -l -b -q FlowQCumulant.C+'("../runlist.list","test.root")'
rm -rf $TMP_DIR
