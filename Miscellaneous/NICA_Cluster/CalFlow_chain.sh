#!/bin/bash

#
# Specify working directory
#$ -wd /nica/mpd21/$USER/SimData/UrQMD/TMP
# Tell SGE that we will work in the woeking directory
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
#$ -o /weekly/nikolaev/lbavinh/EventPlane/OUT/log/
#$ -e /weekly/nikolaev/lbavinh/EventPlane/OUT/log/
#

# ${JOB_ID} - Id of the job array (one for all jobs)
# ${SGE_TASK_ID} - id of the element of the job array
# SGE option "-t 1-N" tells array range. It will create an array
#     of N jobs with ${JOB_ID}_1, ${JOB_ID}_2, ..., ${JOB_ID}_N

#Main directory
export MAIN_DIR=/weekly/nikolaev/lbavinh/EventPlane

source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT/
export TMP_DIR=${MAIN_DIR}/TMP
export OUT=${OUT_DIR}
export OUT_LOG=${OUT}/log
export TMP=${TMP_DIR}/TMP_${JOB_ID}
export LOG=${OUT_LOG}/JOB_${JOB_ID}.log
touch $LOG

mkdir -p $OUT_LOG
mkdir -p $TMP

cp $MAIN_DIR/calculateFlow.C $TMP

echo "Input arguments (Job Id = ${JOB_ID}):" &>> $LOG
echo "Main directory:           ${MAIN_DIR}" &>> $LOG

echo "---------------" &>> $LOG
echo "Run EP resolution calculation..." &>> $LOG
root -l -b -q $TMP/calculateFlow.C+ &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}

echo "Job is done!" &>> $LOG
