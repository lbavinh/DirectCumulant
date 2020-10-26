#!/bin/bash
# 7.7 4.5 11.5 - 39 42 23 - 881 953 387
export energy=smash11.5gev
export working_dir=SMASH
echo "Did they add something new?"
# ls /weekly/seluzhen/smash/$energy/ | grep '.root'| wc -l
# ls /weekly/seluzhen/smash/smash11.5gev/ | grep '.root'| wc -l
# ls /weekly/seluzhen/smash/smash7.7gev/*/ | grep '.root'| wc -l
# ls /weekly/seluzhen/smash/smash4.5gev/*/ | grep '.root'| wc -l
mkdir -p /weekly/$USER/lbavinh/$working_dir/split/$energy
find /weekly/seluzhen/smash/$energy/ -type f -name "*.root" > /weekly/$USER/lbavinh/$working_dir/split/runlist_$energy.list

echo "Creating list for each job"
split -l42 -d /weekly/$USER/lbavinh/$working_dir/split/runlist_$energy.list /weekly/$USER/lbavinh/$working_dir/split/$energy/runlist_$energy_
echo "Number of needed job array is"
ls /weekly/$USER/lbavinh/$working_dir/split/$energy | wc -l
echo "Initializing runlist for SGE JOB"
ls /weekly/$USER/lbavinh/$working_dir/split/$energy/runlist_$energy_* > /weekly/$USER/lbavinh/$working_dir/split/runlistSGE_$energy.list