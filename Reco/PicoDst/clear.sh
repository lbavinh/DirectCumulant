#!/bin/bash
rm -f /weekly/$USER/lbavinh/PicoDst/OUT/*/log/*
rm -f /weekly/$USER/lbavinh/PicoDst/OUT/log/*
rm -rf /weekly/$USER/lbavinh/PicoDst/TMP/*
rm -f /weekly/$USER/lbavinh/PicoDst/OUT/*/sum_*_*.root
source /weekly/parfenov/Soft/PicoDst/build/setPicoDst.sh 