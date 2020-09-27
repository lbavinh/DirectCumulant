#!/bin/bash

#export ecm=7.7
export MAIN_DIR=/nica/mpd21/${USER}/Soft/FlowANA
export FILELIST_DIR=${MAIN_DIR}/filelists/urqmd/7.7gev/split
export MACRO=${MAIN_DIR}/main_proc.C
export OUTDIR=${MAIN_DIR}/OUT/urqmd/7.7gev_test

export LIST=`ls ${FILELIST_DIR}/*`
export NJOBS=`ls ${FILELIST_DIR} | wc -l`

source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh

cd $MAIN_DIR
root -b -l << EOF
.L main_proc.C+
.q
EOF

qsub -t 1-$NJOBS exec_main.sh $OUTDIR $MAIN_DIR $FILELIST_DIR $MACRO
