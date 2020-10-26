#!/bin/bash

export energy=UrQMD_27
export working_dir=/weekly/$USER/lbavinh/UrQMD
# ls /weekly/demanov/UrQMD/new7.7gev/

# /weekly/dmitriev/Urqmd4.5/
# /weekly/dmitriev/Urqmd77/
# /weekly/dmitriev/Urqmd11.5/
# /weekly/dmitriev/Urqmd27/


echo "Initializing list of list (Inception)"
mkdir -p $working_dir/split/${energy}
echo "Listing all ROOT tree of $energy GeV (Inception - level 1)"
find /weekly/dmitriev/Urqmd27/ -type f -name "*.root" > $working_dir/split/runlist_${energy}.list
# find /weekly/demanov/UrQMD/new7.7gev/ -type f -name "*.root" >> $working_dir/split/runlist_${energy}.list

echo "Creating list for each job (Inception - level 2)"
split -l50 -d $working_dir/split/runlist_${energy}.list $working_dir/split/${energy}/runlist_${energy}_
for filename in $working_dir/split/${energy}/runlist_${energy}_*;do mv "$filename" "$filename.list"; done;
echo "Number of needed job array is:"
ls $working_dir/split/${energy} | wc -l
echo "Initializing runlist for SGE JOB (Inception - level 3)"
ls $working_dir/split/${energy}/runlist_${energy}_*.list > $working_dir/split/runlistSGE_${energy}.list
echo "Done. Wake up!"