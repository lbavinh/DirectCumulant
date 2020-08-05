#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/nikolaev/lbavinh/Acceptance
# Tell SGE that we will work in the woeking directory
#$ -cwd
# Specify job name
#$ -N run_sim_urqmd
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=01:10:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=01:10:00
# Specify directory where output and error logs from SGE will be stored
#$ -o /weekly/nikolaev/lbavinh/Acceptance/OUT/log/
#$ -e /weekly/nikolaev/lbavinh/Acceptance/OUT/log/
#

#Main directory
export MAIN_DIR=/weekly/nikolaev/lbavinh/Acceptance

source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export TMP_DIR=${MAIN_DIR}/TMP
export OUT=${OUT_DIR}
export OUT_LOG=${OUT}/log
export TMP=${TMP_DIR}/TMP_${JOB_ID}
export LOG=${OUT_LOG}/JOB_${JOB_ID}.log
touch $LOG

mkdir -p $OUT_LOG
mkdir -p $TMP

cp $MAIN_DIR/calculateFlow_chain.C $TMP

echo "Input arguments (Job Id = ${JOB_ID}):" &>> $LOG
echo "Main directory:           ${MAIN_DIR}" &>> $LOG

echo "---------------" &>> $LOG
echo "Run EP resolution calculation..." &>> $LOG
root -l -b -q $TMP/calculateFlow_chain.C+ &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}

echo "Job is done!" &>> $LOG
