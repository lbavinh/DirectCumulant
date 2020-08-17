#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/$USER/lbavinh/
# Tell SGE that we will work in the working directory
#$ -cwd
# Specify job name
#$ -N join_root_file
# Specify SGE queue
#$ -q all.q
# This specifies the parallel environment.
#$ -pe smp 5
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=0:30:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=0:30:00
# Specify directory where output and error logs from SGE will be stored
#$ -o /weekly/$USER/lbavinh/
#$ -e /weekly/$USER/lbavinh/
#

#Main directory
export MAIN_DIR=/weekly/$USER/lbavinh/
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export OUT=${OUT_DIR}
export OUT_FILE=${OUT}/sum_${JOB_ID}.root
export OUT_LOG=${OUT}/log
export LOG=${OUT_LOG}/Joining_${JOB_ID}.log


mkdir -p $OUT_LOG
touch $LOG

echo "Input arguments (Job Id = ${JOB_ID}):" &>> $LOG
echo "Output: ${OUT_FILE}" &>> $LOG
echo "---------------" &>> $LOG
echo "Run joining..." &>> $LOG

hadd -f ${OUT_FILE} /weekly/nikolaev/idrisov/UrQMD/OUT/flow/sum_1611978_*.root &>> $LOG

cd ${START_DIR}

echo "Job is done!" &>> $LOG
