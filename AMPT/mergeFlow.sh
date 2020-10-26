#!/bin/bash
working_dir=/weekly/$USER/lbavinh/AMPT/OUT

model=AMPT08

# hadd -f -j 20 ${working_dir}/${model}_11.5GeV.root ${working_dir}/2103634/sum_*_*.root
# hadd -f -j 20 ${working_dir}/${model}_7.7GeV.root ${working_dir}/2103635/sum_*_*.root
hadd -f -j 20 ${working_dir}/${model}_27GeV.root ${working_dir}/2165674/sum_*_*.root

model=AMPT15
hadd -f -j 20 ${working_dir}/${model}_27GeV.root ${working_dir}/2165722/sum_*_*.root
hadd -f -j 20 ${working_dir}/${model}_39GeV.root ${working_dir}/2165746/sum_*_*.root


