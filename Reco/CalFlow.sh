#!/bin/bash

#
#$ -wd /weekly/$USER/lbavinh/PicoDst/
#$ -cwd
#$ -N Flow
#$ -q all.q
#$ -l h_rt=01:30:00
#$ -l s_rt=01:30:00
#$ -t 1-633
#$ -o /dev/null
#$ -e /dev/null
#

#Main directory
export MAIN_DIR=/weekly/$USER/lbavinh/PicoDst
export FILELIST=${MAIN_DIR}/runlist_merged.list
export IN_FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export TMP_DIR=${MAIN_DIR}/TMP
export OUT=${OUT_DIR}/${JOB_ID}
export OUT_LOG=${OUT}/log
export TMP=${TMP_DIR}/TMP_${JOB_ID}_${SGE_TASK_ID}
export OUT_FILE=${OUT}/sum_${JOB_ID}_${SGE_TASK_ID}.root
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log

mkdir -p $OUT_LOG
mkdir -p $TMP
touch $LOG
eos cp --streams=16 $MAIN_DIR/FlowQCumulant.C $TMP
eos cp --streams=16 $MAIN_DIR/utilities.C $TMP


# Set correct environment variables (needed version of root)
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
source /weekly/lbavinh/Soft/PicoDst/build/setPicoDst.sh
# echo "Input arguments (Job Id = ${JOB_ID}, Task ID = ${SGE_TASK_ID}):" &>> $LOG
# echo "Main directory:           ${MAIN_DIR}" &>> $LOG
# echo "Input file:    $IN_FILE"  &>> $LOG
# echo "Output file:   $OUT_FILE" &>> $LOG
# echo "---------------" &>> $LOG
# echo "Run elliptic flow calculation..." &>> $LOG
cd $TMP
root -l -b -q FlowQCumulant.C+'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG

# echo "---------------" &>> $LOG
# echo "Cleaning temporary directory..." &>> $LOG
# cd ${START_DIR}
# pwd &>>$LOG
rm -rf ${TMP}
# echo "Job is done!" &>> $LOG
# echo "=====================================" &>> $LOG
