#!/bin/bash

#PBS -q medium
#PBS -l nodes=2:ppn=8,walltime=10:00:00
#PBS -o /mnt/pool/2/lbavinh/EventGenerator/${PBS_JOBID}.o
#PBS -e /mnt/pool/2/lbavinh/EventGenerator/${PBS_JOBID}.e

export MAIN_DIR=/mnt/pool/2/lbavinh/EventGenerator
export OUT_DIR=${MAIN_DIR}/OUT/Pure
export OUT_FILE=${OUT_DIR}/v2hadron_${PBS_JOBID}.root
export LOG_DIR=${OUT_DIR}/log
export OUT_LOG=${LOG_DIR}/v2hadron_${PBS_JOBID}.log

mkdir -p ${LOG_DIR}
touch ${OUT_LOG}

echo "Output file: ${OUT_FILE}" &>> ${OUT_LOG}
root.exe -l -b -q ${MAIN_DIR}/GenerateV2.C'("'${OUT_FILE}'")' &>> ${OUT_LOG}
echo "Complete." &>> ${OUT_LOG}
echo "-------------------------------" &>> ${OUT_LOG}


