#!/bin/bash

export energy=39
export model=AMPT15
export working_dir=/weekly/${USER}/lbavinh/AMPT

# /weekly/taranen/ampt15/77gev/part?/
# /weekly/taranen/ampt15/115gev/part?/
# /weekly/taranen/ampt15/27gev/part?/
# /weekly/taranen/ampt15/39gev/part?/

# /weekly/taranen/ampt08/77gev/part?/
# /weekly/taranen/ampt08/115gev/part?/
# /weekly/taranen/ampt08/27gev/part?/

echo "Initializing list of list (Inception)"
mkdir -p $working_dir/split/${model}_${energy}

echo "Listing all ROOT tree of $model at $energy GeV (Inception - level 1)"
find /weekly/taranen/ampt15/39gev/part?/ -type f -name "*.root" > $working_dir/split/runlist_${model}_${energy}.list

echo "Creating list for each job (Inception - level 2)"
split -l30 -d $working_dir/split/runlist_${model}_${energy}.list $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_
# Rename
for filename in $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_*;do mv "$filename" "$filename.list"; done;
echo "Number of needed job array is:"
ls $working_dir/split/${model}_${energy} | wc -l

echo "Initializing runlist for SGE JOB (Inception - level 3)"
ls $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_* > $working_dir/split/runlistSGE_${model}_${energy}.list

echo "Done. Wake up!"