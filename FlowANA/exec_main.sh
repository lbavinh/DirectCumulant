#!/bin/bash

# -wd /nica/mpd21/$USER/Soft/FlowANA/TMP
#$ -wd /weekly/$USER/lbavinh/FlowANA/TMP
#$ -cwd
#$ -N flowANA
#$ -q all.q
#$ -l h_rt=12:30:00
#$ -l s_rt=12:30:00
#$ -t 1-1
#
#$ -o /dev/null
#$ -e /dev/null
#

export OUTDIR=$1
export MAIN_DIR=$2
export FILELIST_DIR=$3
export MACRO=$4
export FILELIST=`ls $FILELIST_DIR/* | sed "${SGE_TASK_ID}q;d"`
export OUT_DIR=${OUTDIR}/${JOB_ID}/
export LOG=${OUT_DIR}/log/flowANA_${JOB_ID}_${SGE_TASK_ID}.log
export OUT=${OUT_DIR}/files/flowANA_${JOB_ID}_${SGE_TASK_ID}.root

mkdir -p `dirname $LOG`
mkdir -p `dirname $OUT`

echo "Input filelist: ${FILELIST}" &>> $LOG

source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh &>> $LOG

root -l -b -q $MACRO+'("'$FILELIST'","'$OUT'")' &>> $LOG

echo "Finished!" &>> $LOG
