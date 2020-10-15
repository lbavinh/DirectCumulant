#!/bin/bash
working_dir=/weekly/$USER/lbavinh/AMPT/OUT
JOB_ID=2103634
energy=11.5
model=AMPT08
hadd -f -j 20 ${working_dir}/${model}_${energy}GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root
hadd -f -j 20 ${working_dir}/${model}_7.7GeV.root ${working_dir}/2103635/sum_*_*.root