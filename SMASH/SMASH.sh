#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/$USER/lbavinh/SMASH/
# Tell SGE that we will work in the woeking directory
#$ -cwd
# Specify job name
#$ -N SMASH_4.5
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=06:30:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=06:30:00
# Specify job array range (how many jobs will be created: 881 for 4.5 GeV, 953 for 7.7, 387 for 11.5
##$ -t 1-953
# Specify directory where output and error logs from SGE will be stored
#$ -o /dev/null
#$ -e /dev/null
#

#Main directory
energy=smash4.5gev
macro=FlowRun
export MAIN_DIR=/weekly/$USER/lbavinh/SMASH
export FILELIST=$MAIN_DIR/split/runlist_$energy.list
export IN_FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export OUT=${OUT_DIR}/${JOB_ID}
export OUT_LOG=${OUT}/log
export OUT_FILE=${OUT}/sum_${JOB_ID}_${SGE_TASK_ID}.root
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log

mkdir -p $OUT_LOG
touch $LOG

# Set correct environment variables (needed version of root)
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh

echo "Input arguments (Job Id = ${JOB_ID}, Task ID = ${SGE_TASK_ID}):" &>> $LOG
echo "Input file:    $IN_FILE"  &>> $LOG
echo "Output file:   $OUT_FILE" &>> $LOG
echo "---------------" &>> $LOG

root -l -b -q ${MAIN_DIR}/$macro.C'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG

echo "Job is done!" &>> $LOG
echo "=====================================" &>> $LOG
