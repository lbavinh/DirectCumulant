#!/bin/bash
working_dir=/weekly/$USER/lbavinh/FlowANA/OUT
energy=11.5
model=Urqmd
JOB_ID=2094160
hadd -f -j 20 ${working_dir}/${model}_${energy}GeV_V2R1.root ${working_dir}/${JOB_ID}/sum_*_*.root
