#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/nikolaev/lbavinh/Generator/
# Tell SGE that we will work in the working directory
#$ -cwd
# Specify job name
#$ -N run_sim_urqmd
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=1:00:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=1:00:00
# Specify directory where output and error logs from SGE will be stored
#$ -o /weekly/nikolaev/lbavinh/Generator/OUT/log/
#$ -e /weekly/nikolaev/lbavinh/Generator/OUT/log/
#

#Main directory
export MAIN_DIR=/weekly/nikolaev/lbavinh/Generator


export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export OUT=${OUT_DIR}/pure
export OUT_FILE=${OUT}/v2hadron_${JOB_ID}.root
export OUT_LOG=${OUT}/log
export LOG=${OUT_LOG}/JOB_${JOB_ID}.log
export TMP_DIR=${MAIN_DIR}/TMP
export TMP=${TMP_DIR}/TMP_${JOB_ID}

mkdir -p $OUT_LOG
mkdir -p $TMP
touch $LOG

cp $MAIN_DIR/GenerateV2.C $TMP
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
echo "Input arguments (Job Id = ${JOB_ID}):" &>> $LOG
echo "Output: ${OUT_FILE}" &>> $LOG

echo "---------------" &>> $LOG
echo "Run EP resolution calculation..." &>> $LOG

root -l -b -q $TMP/GenerateV2.C+'("'${OUT_FILE}'")' &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}

echo "Job is done!" &>> $LOG
