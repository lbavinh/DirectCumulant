#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/$USER/lbavinh/ToyModel
# Tell SGE that we will work in the working directory
#$ -cwd
# Specify job name
#$ -N run_toy_model
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=1:00:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=1:00:00
# Specify job array range (how many jobs will be created
#$ -t 1-500
# Specify directory where output and error logs from SGE will be stored
#$ -o /dev/null
#$ -e /dev/null
#

# Number of events in each ROOT tree to be generated
export NEVT=10000
# Mean multiplicity
export MEAN_MULT=1000

#Main directory
export MAIN_DIR=/weekly/$USER/lbavinh/ToyModel
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export OUT=${OUT_DIR}/PureFlow
export OUT_FILE=${OUT}/ToyModel_${JOB_ID}_${SGE_TASK_ID}.root
export OUT_LOG=${OUT}/log
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log
export TMP_DIR=${MAIN_DIR}/TMP
export TMP=${TMP_DIR}/TMP_${JOB_ID}_${SGE_TASK_ID}

mkdir -p $OUT_LOG
mkdir -p $TMP
touch $LOG

eos cp --streams=16 $MAIN_DIR/Generator.C $TMP
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
echo "Input arguments (Job Id = ${JOB_ID}):" &>> $LOG
echo "Output: ${OUT_FILE}" &>> $LOG

echo "---------------" &>> $LOG
echo "Run simulation..." &>> $LOG

root -l -b -q $TMP/Generator.C+'("'${OUT_FILE}'",'${NEVT}','${MEAN_MULT}')' &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}

echo "Job is done!" &>> $LOG
