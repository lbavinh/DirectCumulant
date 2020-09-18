#!/bin/bash

#
#$ -wd /weekly/$USER/lbavinh/ToyModel
#$ -cwd
#$ -N Flow
#$ -q all.q
#$ -l h_rt=05:10:00
#$ -l s_rt=05:10:00
#$ -t 1-10
#$ -o /dev/null
#$ -e /dev/null
#

#Main directory
export MAIN_DIR=/weekly/$USER/lbavinh/ToyModel
export FILELIST=${MAIN_DIR}/runlist.list
export IN_FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export TMP_DIR=${MAIN_DIR}/TMP
export OUT=${OUT_DIR}
export OUT_LOG=${OUT}/log
export TMP=${TMP_DIR}/TMP_${JOB_ID}_${SGE_TASK_ID}
export OUT_FILE=${OUT}/sum_${JOB_ID}_${SGE_TASK_ID}.root
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log

mkdir -p $OUT_LOG
mkdir -p $TMP
touch $LOG

cp $MAIN_DIR/calculateFlow.C $TMP

# Set correct environment variables (needed version of root)
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh

echo "Input arguments (Job Id = ${JOB_ID}, Task ID = ${SGE_TASK_ID}):" &>> $LOG
echo "Main directory:           ${MAIN_DIR}" &>> $LOG
echo "Input file:    $IN_FILE"  &>> $LOG
echo "Output file:   $OUT_FILE" &>> $LOG
echo "---------------" &>> $LOG
echo "Run elliptic flow calculation..." &>> $LOG
root -l -b -q $TMP/calculateFlow.C+'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}
echo "Job is done!" &>> $LOG
echo "=====================================" &>> $LOG
