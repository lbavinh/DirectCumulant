#!/bin/bash
# 47 23 4.5 11.5 980 992
export energy=Urqmd11.5
export working_dir=UrQMD
echo "Did they add something new?"
ls /weekly/dmitriev/$energy/*/ | wc -l
mkdir -p /weekly/$USER/lbavinh/$working_dir/split/$energy
find /weekly/dmitriev/$energy/*/ -type f -name "*.root" > /weekly/$USER/lbavinh/$working_dir/split/runlist_$energy.list

echo "Creating list for each job"
split -l23 -d /weekly/$USER/lbavinh/$working_dir/split/runlist_$energy.list /weekly/$USER/lbavinh/$working_dir/split/$energy/runlist_$energy_
echo "Number of needed job array is"
ls /weekly/$USER/lbavinh/$working_dir/split/$energy | wc -l
echo "Initializing runlist for SGE JOB"
ls /weekly/$USER/lbavinh/$working_dir/split/$energy/runlist_$energy_* > /weekly/$USER/lbavinh/$working_dir/split/runlistSGE_$energy.list