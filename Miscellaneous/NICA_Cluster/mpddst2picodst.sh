#!/bin/bash

#
#$ -wd /weekly/$USER/TMP/
#$ -cwd
#$ -N dst_converter
#$ -q all.q
#$ -l h_rt=0:20:00
#$ -l s_rt=0:20:00
#$ -t 1-20000
#
#$ -o /weekly/$USER/TMP/
#$ -e /weekly/$USER/TMP/
#

#export INPUT_LIST=/weekly/parfenov/mpd_winter2019/macro/mpddst_pwg3-prod9_7.7gev_auau.list
export INPUT_LIST=/weekly/parfenov/mpd_winter2019/macro/mpddst_pwg3-prod9_7.7gev_bibi.list
CURRENT_FILE=`sed "${SGE_TASK_ID}q;d" ${INPUT_LIST}`

export ecm=7.7
#export COLL_SYS=AuAu
export COLL_SYS=BiBi
export COMMIT=pwg3-prod9

export DATE=${JOB_ID} # or `date '+%Y%m%d_%H%M%S'`

export OUT=/weekly/$USER/mpd_data/${ecm}gev/picodst/$COLL_SYS/$COMMIT/$DATE
mkdir -p $OUT

export TMPALL=/weekly/$USER/TMP
export TMPDIR=${TMPALL}/TMP_${JOB_ID}_${SGE_TASK_ID}
mkdir -p $TMPDIR

export LOGDIR=$OUT/log
mkdir -p $LOGDIR
export LOG=$LOGDIR/JOB_${JOB_ID}_${SGE_TASK_ID}.log

_log() {

local format='+%Y/%m/%d-%H:%M:%S'
echo [`date $format`] "$@"

}

export START_DIR=$PWD

ROOTSYS_cvmfs=/opt/fairsoft/mpd/new
FAIRROOT=/opt/fairroot/mpd/new

export ROOTSYS=${ROOTSYS_cvmfs}

export PATH=${PATH}:${ROOTSYS}/bin:${FAIRROOT}/bin

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${ROOTSYS}/lib/root:${ROOTSYS}/lib:${FAIRROOT}/lib

export Root=${ROOTSYS}/bin/root



export MPDROOT_DIR=/weekly/parfenov/Soft/MPDROOT/mpdroot_140920/

export MACRO_DIR=$MPDROOT_DIR/macro/mpd

export BUILD_DIR=$MPDROOT_DIR/build

. ${BUILD_DIR}/config.sh


cd $TMPDIR

eos cp --streams=16 $CURRENT_FILE ${TMPDIR}/mpddst.root &>> $LOG

_log `ls ${TMPDIR}` &>> $LOG

_log ${ROOTSYS_cvmfs}

_log ${SIMPATH}

_log ${ROOTSYS}

_log ${VMCWORKDIR}

_log ${LD_LIBRARY_PATH}

_log ${PATH}

source /weekly/parfenov/Soft/PicoDst/build/setPicoDst.sh
PicoDstConverter --all -i $TMPDIR/mpddst.root -o ${TMPDIR}/picodst.root | tee &>> $LOG

#cd $TMPDIR
_log Moving to $OUT/mpddst_${JOB_ID}_${SGE_TASK_ID}.root
eos cp --streams=16 ${TMPDIR}/picodst.root $OUT/picodst_${JOB_ID}_${SGE_TASK_ID}.root

_log Remove $TMPDIR directory

rm -rf $TMPDIR
#mv  $TMPALL/slurm-${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.out $OUT/slurm-${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.out

cd $START_DIR

rm -f ${TMPALL}/*
