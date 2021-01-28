#!/bin/bash

#
#$ -wd /weekly/${USER}/lbavinh/ToyModel
#$ -cwd
#$ -N Flow
#$ -q all.q
#$ -l h_rt=06:30:00
#$ -l s_rt=06:30:00
#$ -t 1-500
#$ -o /dev/null
#$ -e /dev/null
#

#Main directory
macro=ToyModelTreeReader
export MODE=PureFlow
export MAIN_DIR=/weekly/${USER}/lbavinh/ToyModel
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export FILELIST=${OUT_DIR}/${MODE}/runlist_${MODE}.list
export IN_FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
export TMP_DIR=${MAIN_DIR}/TMP
export OUT=${OUT_DIR}/${JOB_ID}
export OUT_LOG=${OUT}/log
export TMP=${TMP_DIR}/TMP_${JOB_ID}_${SGE_TASK_ID}
export OUT_FILE=${OUT}/sum_${JOB_ID}_${SGE_TASK_ID}.root
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log

mkdir -p $OUT_LOG
mkdir -p $TMP
touch $LOG

eos cp --streams=16 $MAIN_DIR/$macro.C $TMP
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
root -l -b -q $TMP/$macro.C+'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}
# echo "Job is done!" &>> $LOG
echo "=====================================" &>> $LOG
