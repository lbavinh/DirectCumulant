#!/bin/bash

#
# Specify working directory
#$ -wd /weekly/$USER/lbavinh/readPicoDst/
# Tell SGE that we will work in the working directory
#$ -cwd
# Specify job name
#$ -N Flow
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=01:30:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=01:30:00
# Specify job array range (how many jobs will be created
#$ -t 1-633
# Specify directory where output and error logs from SGE will be stored
#$ -o /weekly/$USER/lbavinh/readPicoDst/OUT/log/
#$ -e /weekly/$USER/lbavinh/readPicoDst/OUT/log/
#

# ${JOB_ID} - Id of the job array (one for all jobs)
# ${SGE_TASK_ID} - id of the element of the job array
# SGE option "-t 1-N" tells array range. It will create an array
#     of N jobs with ${JOB_ID}_1, ${JOB_ID}_2, ..., ${JOB_ID}_N

#Main directory
export MAIN_DIR=/weekly/$USER/lbavinh/readPicoDst
#export FILELIST=${MAIN_DIR}/runlist_PicoDst.list
export FILELIST=${MAIN_DIR}/runlist_PicoDst_merged.list
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

rsync -vuzP $MAIN_DIR/readPicoDst.C $TMP/readPicoDst.C &>> $LOG
rsync -vuzP $MAIN_DIR/function.C $TMP/function.C &>> $LOG

# Set correct environment variables (needed version of root)
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
source /weekly/lbavinh/lbavinh/PicoDst/build/setPicoDst.sh
echo "Input arguments (Job Id = ${JOB_ID}, Task ID = ${SGE_TASK_ID}):" &>> $LOG
echo "Main directory:           ${MAIN_DIR}" &>> $LOG
echo "Input file:    $IN_FILE"  &>> $LOG
echo "Output file:   $OUT_FILE" &>> $LOG
echo "---------------" &>> $LOG
echo "Run elliptic flow calculation..." &>> $LOG
cd $TMP
root -l -b -q readPicoDst.C+'("'${IN_FILE}'","'${OUT_FILE}'")' &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
pwd &>>$LOG
rm -rf ${TMP}
echo "Job is done!" &>> $LOG
echo "=====================================" &>> $LOG
