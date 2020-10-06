#!/bin/bash
# 47 23 4.5 11.5 980 992
export energy=Urqmd7.7_part2
export working_dir=/weekly/$USER/lbavinh/UrQMD
# ls /weekly/demanov/UrQMD/new7.7gev/
# ls /weekly/dmitriev/$energy/*/ | wc -l

echo "Initializing list of list (Inception)"
mkdir -p $working_dir/split/${energy}
echo "Listing all ROOT tree of $energy GeV (Inception - level 1)"
find /weekly/dmitriev/Urqmd77/part2/ -type f -name "*.root" > $working_dir/split/runlist_${energy}.list

echo "Creating list for each job (Inception - level 2)"
split -l23 -d $working_dir/split/runlist_${energy}.list $working_dir/split/${energy}/runlist_${energy}_
for filename in $working_dir/split/${energy}/runlist_${energy}_*;do mv "$filename" "$filename.list"; done;
echo "Number of needed job array is:"
ls $working_dir/split/${energy} | wc -l
echo "Initializing runlist for SGE JOB (Inception - level 3)"
ls $working_dir/split/${energy}/runlist_${energy}_*.list > $working_dir/split/runlistSGE_${energy}.list
echo "Done. Wake up!"