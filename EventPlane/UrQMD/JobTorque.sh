#!/bin/bash

#PBS -q medium
#PBS -l nodes=2:ppn=8,walltime=10:00:00


export MAIN_DIR=/mnt/pool/2/lbavinh/EventPlane
export OUT_DIR=${MAIN_DIR}/OUT
export OUT_FILE=${OUT_DIR}/sum_test_9.root
export IN_FILE=${MAIN_DIR}/../urqmd/chain/chain9.root
export OUT_LOG=${OUT_DIR}/sum_test_9_$PBS_JOBID.log


mkdir -p ${OUT_DIR}

root.exe -l -b -q ${MAIN_DIR}/macro.C'("'${IN_FILE}'","'${OUT_FILE}'")' &>> ${OUT_LOG}