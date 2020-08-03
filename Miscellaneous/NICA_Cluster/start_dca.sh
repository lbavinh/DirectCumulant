#!/bin/bash

#
# Specify working directory
#$ -wd /nica/mpd21/$USER/TMP
# Tell SGE that we will work in the woeking directory
#$ -cwd
# Specify job name
#$ -N run_dca
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=00:10:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=00:10:00
# Specify job array range (how many jobs will be created
#$ -t 1-200
#
#$ -o /nica/mpd21/$USER/TMP
#$ -e /nica/mpd21/$USER/TMP
#

ecm=7.7
COMMIT=IdealAcceptance

export INITIAL_FILELIST=/nica/mpd21/${USER}/mpd_winter2019/MpdFlowScripts/urqmd_7.7gev_picoDst1.list

# Let job element read corresponding line from the filelist, 
# i.e. job ${JOB_ID}_3 will read 3rd line from the filelist,
# and ${JOB_ID}_12 will read 12th line from it.
CURRENT_FILE=`sed "${SGE_TASK_ID}q;d" ${INITIAL_FILELIST}`

FILE_NAME=`basename ${CURRENT_FILE}`
FILE_NAME1=`echo ${FILE_NAME} | sed -e 's/picodst/dca/g'`
FILE_NAME2=`echo ${FILE_NAME1} | sed -e 's/.root/.log/g'`
OUTPUT_FILE=/nica/mpd21/${USER}/mpd_winter2019/mpd_prod/MpdFlowProd/${ecm}gev/${COMMIT}/dca/files/${FILE_NAME1}
LOG=/nica/mpd21/${USER}/mpd_winter2019/mpd_prod/MpdFlowProd/${ecm}gev/${COMMIT}/dca/logs/${FILE_NAME2}
OUTPUT_DIR=`dirname ${OUTPUT_FILE}`
LOG_DIR=`dirname ${LOG}`

mkdir -p ${OUTPUT_DIR}
mkdir -p ${LOG_DIR}

export CURRENT_DIR=$PWD

export MPDROOT_DIR=/nica/mpd21/parfenov/Soft/MPDROOT/mpdroot_181219
export MACRO_DIR=$MPDROOT_DIR/macro/mpd
export BUILD_DIR=$MPDROOT_DIR/build
export SCRIPT_DIR=/nica/mpd21/parfenov/mpd_winter2019/MpdFlowScripts
export MPDFLOW_DIR=/eos/nica/mpd/users/parfenov/Soft/MpdFlow
export MPDFLOW_BIN=${MPDFLOW_DIR}/build/bin
export RUN_EXE=${MPDFLOW_BIN}/get-dca

. ${MPDROOT_DIR}/SetEnv.sh &>> $LOG
. ${BUILD_DIR}/config.sh &>> $LOG

export Root=${ROOTSYS}/bin/root
#export TMPDIR=/nica/mpd21/$USER/TMP/TMP_${JOB_ID}_${SGE_TASK_ID}
#export TMPALL=/nica/mpd21/$USER/TMP

#mkdir -p $TMPDIR
#rsync -vazr ${SCRIPT_DIR}/* ${TMPDIR}/ &>> $LOG
if [ ! -e "${RUN_EXE}" ]; then
  echo "Error: No executable was found (${RUN_EXE}). Exit..." &>> $LOG
  exit 1 &>> $LOG
fi

$RUN_EXE -i $CURRENT_FILE -o $OUTPUT_FILE &>> $LOG

echo "Done!" &>> $LOG
