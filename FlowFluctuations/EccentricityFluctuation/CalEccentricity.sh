#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/${USER}/lbavinh/EccentricityFluctuation
# Tell SGE that we will work in the woeking directory
#$ -cwd
# Specify job name
#$ -N UrQMD45
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=00:30:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=00:30:00

# Specify job array range (how many jobs will be created: 
#$ -t 1-200
# Specify directory where output and error logs from SGE will be stored
#$ -o /dev/null
#$ -e /dev/null
#

#Main directory
model=UrQMD
energy=4.5
macro=initQA
export MAIN_DIR=/weekly/${USER}/lbavinh/EccentricityFluctuation
export FILELIST=$MAIN_DIR/runlist_${model}_${energy}.list
export IN_FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
# export START_DIR=${PWD}
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
eos cp --streams=16 $MAIN_DIR/utilities.C $TMP


source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
source /weekly/lbavinh/Soft/mcini/macro/config.sh
root -l -b -q $TMP/$macro.C+'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG
rm -rf ${TMP}
echo "=====================================" &>> $LOG
