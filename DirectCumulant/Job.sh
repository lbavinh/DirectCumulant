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
export MAIN_DIR=/mnt/pool/2/${USER}/QCumulant/build
export OUT_DIR=${MAIN_DIR}/OUT
# export TMP_DIR=${MAIN_DIR}/TMP/TMP_${SLURM_JOB_ID}
export IN_FILE=${MAIN_DIR}/runlist.list
export OUT_FILE=${OUT_DIR}/FirstRun.root
export OUT_LOG=${OUT_DIR}/QCumulant_${SLURM_JOB_ID}.log
export CONFIG_FILE=${MAIN_DIR}/../.qcumulant.cfg

mkdir -p ${OUT_DIR}

cd ${MAIN_DIR}
./RunFlowAnalysis -i ${IN_FILE} -o ${OUT_FILE} -config ${CONFIG_FILE} &>> $LOG
# ./GetDCA -i ${IN_FILE} -o ${OUT_FILE} &>>$LOG
