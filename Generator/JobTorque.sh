#!/bin/bash

#PBS -q medium
#PBS -l nodes=2:ppn=8,walltime=10:00:00
#PBS -o /mnt/pool/2/lbavinh/EventGenerator/torque/${PBS_JOBID}.o
#PBS -e /mnt/pool/2/lbavinh/EventGenerator/torque/${PBS_JOBID}.e

export MAIN_DIR=/mnt/pool/2/lbavinh/EventGenerator
export OUT_DIR=${MAIN_DIR}/OUT/Non-flowPairWise
export OUT_LOG=${OUT_DIR}/log/v2hadron_${PBS_JOBID}.log
export TMP_DIR=${MAIN_DIR}/TMP/TMP_${PBS_JOBID}
mkdir -p ${MAIN_DIR}/torque
mkdir -p ${TMP_DIR}
mkdir -p ${OUT_DIR}
mkdir -p ${OUT_DIR}/log
cp ${MAIN_DIR}/v2hadron.C ${TMP_DIR}
cd ${TMP_DIR}
root.exe -l -b -q v2hadron.C+'("/mnt/pool/2/lbavinh/EventGenerator/OUT/Non-flowPairWise/v2hadron_11.root")'
