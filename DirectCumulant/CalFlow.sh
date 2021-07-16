#!/bin/bash

#
#$ -wd /scratch2/$USER/QCumulant/build
#$ -cwd
#$ -N Flow
# -q all.q
#$ -l h=(ncx112|ncx115|ncx117|ncx121|ncx124|ncx12[6-7]|ncx130|ncx132|ncx134|ncx136|ncx138|ncx141|ncx144|ncx150|ncx152|ncx159|ncx16[0-9]|ncx17[0-2]|ncx17[4-6]|ncx18[0-1]|ncx18[4-5]|ncx20[1-3]|ncx20[5-8]|ncx21[1-8]|ncx22[4-8]|ncx23[2-8])
#$ -l h_rt=01:30:00
#$ -l s_rt=01:30:00
#$ -t 1-356
#$ -o /dev/null
#$ -e /dev/null
#

# Main directory
export MAIN_DIR=/scratch2/$USER/QCumulant/build
# File list for Reconstructed UrQMD data at 7.7 GeV (reco data)
export FILELIST=/scratch2/lbavinh/QCumulant/build/split/runlistSGE_UrQMD_7.7_reco_full.list
# File list for UrQMD data at 7.7 GeV without reconstruction (generator level data)
# export FILELIST=/scratch1/lbavinh/lbavinh/UrQMD/split/runlistSGE_UrQMD_7.7.list

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

echo "INFILE: ${IN_FILE}" &>> $LOG
echo "OUTFILE: ${OUT_FILE}" &>> $LOG
cd ${MAIN_DIR}
./RunFlowAnalysis -i ${IN_FILE} -o ${OUT_FILE} -config ${CONFIG_FILE} &>> $LOG
# ./GetDCA -i ${IN_FILE} -o ${OUT_FILE} &>>$LOG
