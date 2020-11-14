#!/bin/bash

# Specify job array range (how many jobs will be created: 
# UrQMD: 980 for 4.5 GeV, 584 for 7.7, 992 for 11.5, 438 for 27
# SMASH: 580 for 4.5 GeV, 881 for 7.7, 706 for 11.5
# 0.8mb: 821 for 7.7 ; 395 for 11.5 ; 326 for 27 ;
# 1.5mb: 474 for 7.7 ; 782 for 11.5 ; 367 for 27 ; 575 for 39
# vHLLE+UrQMD:  7.7 = 342 ; 11.5 = 379 ; 19.6 = 163 ; 27 = 252 ; 39 = 162

# MODEL=UrQMD
# ENERGY=7.7
# NJOBS=584
# qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY
# ENERGY=11.5
# NJOBS=992
# qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY

MODEL=SMASH
ENERGY=7.7
NJOBS=881
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY
ENERGY=11.5
NJOBS=706
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY

MODEL=AMPT08
ENERGY=7.7
NJOBS=821
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY
ENERGY=11.5
NJOBS=395
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY

MODEL=AMPT15
ENERGY=7.7
NJOBS=474
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY
ENERGY=11.5
NJOBS=782
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY

MODEL=vHLLEUrQMD
ENERGY=7.7
NJOBS=342
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY
ENERGY=11.5
NJOBS=379
qsub -t 1-$NJOBS -N ${MODEL}${ENERGY} run.sh $MODEL $ENERGY