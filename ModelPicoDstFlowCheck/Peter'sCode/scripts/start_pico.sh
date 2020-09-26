#!/bin/bash

#
#$ -wd /weekly/$USER/TMP
#$ -cwd
#$ -N flow_model
#$ -q all.q
#$ -l h_rt=2:30:00
#$ -l s_rt=2:30:00
#$ -t 1-1
#
#$ -o /dev/null
#$ -e /dev/null
#

export MAIN_DIR=/weekly/povarov/lbavinh/ModelPicoDstFlowCheck
export FILELIST=${MAIN_DIR}/scripts/filelists/picodst/urqmd/7.7gev/full.list
export OUTDIR=${MAIN_DIR}/OUT/pico/urqmd/7.7gev
export FILE=`sed "${SGE_TASK_ID}q;d" $FILELIST`
export OUT_DIR=${OUTDIR} #/${JOB_ID}/
export LOG=${OUT_DIR}/log/flow_pico_${SGE_TASK_ID}.log #${JOB_ID}_${SGE_TASK_ID}.log
export OUT=${OUT_DIR}/files/flow_pico_${SGE_TASK_ID}.root #_${JOB_ID}_${SGE_TASK_ID}.root

mkdir -p `dirname $LOG`
mkdir -p `dirname $OUT`

export TMP_DIR=${MAIN_DIR}/TMP/TMP_${JOB_ID}_${SGE_TASK_ID}

mkdir -p $TMP_DIR

rsync -vuzP $MAIN_DIR/Utils.C $TMP_DIR/Utils.C &>> $LOG
rsync -vuzP $MAIN_DIR/get_flow_pico.C $TMP_DIR/get_flow_pico.C &>> $LOG

CURRENT_DIR=$PWD
cd $TMP_DIR

echo "Input file: ${FILE}" &>> $LOG

source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh &>> $LOG
source /weekly/parfenov/Soft/PicoDst/build/setPicoDst.sh &>> $LOG

root -l -b -q get_flow_pico.C+'("'$FILE'","'$OUT'")' &>> $LOG

cd $CURRENT_DIR
rm -rfv $TMP_DIR &>> $LOG

echo "Finished!" &>> $LOG
