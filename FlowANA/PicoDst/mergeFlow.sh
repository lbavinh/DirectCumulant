#!/bin/bash
working_dir=/weekly/$USER/lbavinh/FlowANA/PicoDst/OUT
energy=7.7_20M
model=UrQMD
JOB_ID=2104717
hadd -f -j 20 ${working_dir}/${model}_${energy}GeV_V2R1.root ${working_dir}/${JOB_ID}/sum_*_*.root
JOB_ID2=2105770
energy2=11.5
hadd -f -j 20 ${working_dir}/${model}_${energy2}GeV_V2R1.root ${working_dir}/${JOB_ID2}/sum_*_*.root
