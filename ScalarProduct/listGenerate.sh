#!/bin/bash
# 47 23 4.5 11.5 980 992
export energy=7.7
export model=UrQMD

export working_dir=/weekly/${USER}/lbavinh/ScalarProduct
echo "Initializing list of list (Inception)"
mkdir -p $working_dir/split/${model}_${energy}

echo "Listing all ROOT tree of $model at $energy GeV (Inception - level 1)"
find /weekly/dmitriev/Urqmd77/ -type f -name "*.root" > $working_dir/split/runlist_${model}_${energy}.list
find /weekly/demanov/UrQMD/new7.7gev/ -type f -name "*.root" >> $working_dir/split/runlist_${model}_${energy}.list

echo "Creating list for each job (Inception - level 2)"
split -l40 -d $working_dir/split/runlist_${model}_${energy}.list $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_
for filename in $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_*;do mv "$filename" "$filename.list"; done;

echo "Number of needed job array is:"
ls $working_dir/split/${model}_${energy} | wc -l

echo "Initializing runlist for SGE JOB (Inception - level 3)"
ls $working_dir/split/${model}_${energy}/runlist_${model}_${energy}_* > $working_dir/split/runlistSGE_${model}_${energy}.list

echo "Done. Wake up!"