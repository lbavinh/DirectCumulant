#!/bin/bash
# 47 23 4.5 11.5 980 992
export energy=4.5
export model=UrQMD
export working_dir=lbavinh/UrQMD/McDst
echo "Initializing list of list (Inception)"
mkdir -p /weekly/$USER/$working_dir/split/${model}_${energy}
echo "Listing all ROOT tree of $model at $energy GeV (Inception - level 1)"
find /eos/nica/mpd/users/batyuk/mcDst/UrQMD/AuAu/Hg/cms_${energy}GeV/ -type f -name "*.root" > /weekly/$USER/$working_dir/split/runlist_${model}_${energy}.list

echo "Creating list for each job (Inception - level 2)"
split -l62 -d /weekly/$USER/$working_dir/split/runlist_${model}_${energy}.list /weekly/$USER/$working_dir/split/${model}_${energy}/runlist_${model}_${energy}_
for filename in /weekly/$USER/$working_dir/split/${model}_${energy}/runlist_${model}_${energy}_*;do mv "$filename" "$filename.list"; done;
echo "Number of needed job array is:"
ls /weekly/$USER/$working_dir/split/${model}_${energy} | wc -l
echo "Initializing runlist for SGE JOB (Inception - level 3)"
ls /weekly/$USER/$working_dir/split/${model}_${energy}/runlist_${model}_${energy}_* > /weekly/$USER/$working_dir/split/runlistSGE_${model}_${energy}.list
echo "Done. Wake up!"