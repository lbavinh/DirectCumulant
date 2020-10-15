#!/bin/bash

export energy=11.5
export model=Urqmd
export working_dir=/weekly/${USER}/lbavinh/FlowANA
export tree_dir=/weekly/dmitriev
# /weekly/dmitriev/Urqmd11.5
echo "Initializing list of list (Inception)"
mkdir -p $working_dir/split/${model}_${energy}

echo "Listing all ROOT tree of $model at $energy GeV (Inception - level 1)"
find ${tree_dir}/${model}${energy}/ -type f -name "*.root" > $working_dir/split/runlist_${model}_${energy}.list

echo "Creating list for each job (Inception - level 2)"
split -l30 -d $working_dir/split/runlist_${model}_${energy}.list $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_
# Rename
for filename in $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_*;do mv "$filename" "$filename.list"; done;
echo "Number of needed job array is:"
ls $working_dir/split/${model}_${energy} | wc -l

echo "Initializing runlist for SGE JOB (Inception - level 3)"
ls $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_* > $working_dir/split/runlistSGE_${model}_${energy}.list

echo "Done. Wake up!"