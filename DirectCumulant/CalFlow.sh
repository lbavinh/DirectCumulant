#!/bin/bash

#
#$ -wd /weekly/$USER/lbavinh/QCumulant/QCumulant_debug/build
#$ -cwd
#$ -N Flow
#$ -q all.q
#$ -l h_rt=01:30:00
#$ -l s_rt=01:30:00
#$ -t 1-1
#$ -o /dev/null
#$ -e /dev/null
#

# Main directory
export MAIN_DIR=/weekly/$USER/lbavinh/QCumulant/QCumulant_debug/build
export FILELIST=/weekly/lbavinh/lbavinh/Runlist/runlistSGE_Reco_UrQMD_7.7.list
export IN_FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT
export OUT=${OUT_DIR}/${JOB_ID}
export OUT_LOG=${OUT}/log
export OUT_FILE=${OUT}/sum_${JOB_ID}_${SGE_TASK_ID}.root
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log
export CONFIG_FILE=${MAIN_DIR}/../.qcumulant.cfg
mkdir -p $OUT_LOG
touch $LOG

${MAIN_DIR}/RunFlowAnalysis -i ${IN_FILE} -config ${CONFIG_FILE} -o ${OUT_FILE} &>> $LOG
# ./RunFlowAnalysis -i /weekly/lbavinh/lbavinh/Runlist/split/runlist_Reco_UrQMD_7.7_9225 -config ../.qcumulant.cfg -o test.root
# export TMP_DIR=${MAIN_DIR}/TMP
# export TMP=${TMP_DIR}/TMP_${JOB_ID}_${SGE_TASK_ID}
# mkdir -p $TMP
# eos cp --streams=16 $MAIN_DIR/RunFlowAnalysis.C $TMP
# eos cp --streams=16 $MAIN_DIR/utilities.C $TMP
# eos cp --streams=16 $MAIN_DIR/constants.C $TMP
# source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
# source /weekly/lbavinh/Soft/PicoDst/build/setPicoDst.sh
# cd
# root -l -b -q $TMP/RunFlowAnalysis.C+'("'${IN_FILE}'", "'${OUT_FILE}'", "'${CONFIG_FILE}'")' &>> $LOG
# rm -rf ${TMP}

