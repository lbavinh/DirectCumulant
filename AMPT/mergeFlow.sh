#!/bin/bash
working_dir=/weekly/$USER/lbavinh/AMPT/OUT
JOB_ID=2092716
energy=11.5
model=AMPT15
hadd -f -j 20 ${working_dir}/${model}_${energy}GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root