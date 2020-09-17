#!/bin/bash
#echo "source /afs/cern.ch/sw/lcg/contrib/gcc/4.9.2/x86_64-slc6/setup.sh"
#source /afs/cern.ch/sw/lcg/contrib/gcc/4.9.2/x86_64-slc6/setup.sh
export WORKDIR=$PWD
echo $WORKDIR
export MULTICUMUDIR="$WORKDIR/MultiCumulants"
echo $MULTICUMUDIR
export TOYMCDIR="$WORKDIR/ToyMC"
echo $TOYMCDIR
export BINDIR="$WORKDIR/bin"
echo $BINDIR
export DATADIR="$WORKDIR/data"
echo $DATADIR
export OUTPUTDIR="$WORKDIR/output"
echo $OUTPUTDIR
export TESTDIR="$WORKDIR/tests"
echo $TESTDIR
