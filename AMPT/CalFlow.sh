#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/$USER/lbavinh/AMPT/
# Tell SGE that we will work in the woeking directory
#$ -cwd
# Specify job name
#$ -N AMPT15_39
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=07:30:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=07:30:00
# Specify job array range (how many jobs will be created):
# 1.5mb: 474 for 7.7 ; 782 for 11.5 ; 367 for 27 ; 575 for 39
# 0.8mb: 821 for 7.7 ; 395 for 11.5 ; 326 for 27 ;
#$ -t 1-575
# Specify directory where output and error logs from SGE will be stored
#$ -o /dev/null
#$ -e /dev/null
#

#Main directory
export macro=anaFlow
export energy=39
export model=AMPT15

export MAIN_DIR=/weekly/$USER/lbavinh/AMPT
export FILELIST=${MAIN_DIR}/split/runlistSGE_${model}_${energy}.list
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

eos cp --streams=16 $MAIN_DIR/$macro.C $TMP

# Set correct environment variables (needed version of root)
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh

# echo "Input arguments (Job Id = ${JOB_ID}, Task ID = ${SGE_TASK_ID}):" &>> $LOG
# echo "Input file:    $IN_FILE"  &>> $LOG
# echo "Output file:   $OUT_FILE" &>> $LOG
# echo "---------------" &>> $LOG
root -l -b -q $TMP/$macro.C+'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG

# echo "---------------" &>> $LOG
# echo "Cleaning temporary directory..." &>> $LOG

rm -rf ${TMP}
# echo "Job is done!" &>> $LOG
echo "============================================================" &>> $LOG
