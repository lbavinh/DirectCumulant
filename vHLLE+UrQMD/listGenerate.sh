#!/bin/bash
export energy=77
export working_dir=vHLLE+UrQMD
echo "Initializing run list for $energy GeV of $working_dir model"
#/weekly/demanov/mchybrid/77xpt500new
#/weekly/demanov/mchybrid/115xpt500new
ls /weekly/demanov/mchybrid/${energy}xpt500new | wc -l
echo "jobs are needed"
# 115 = 379 ; 77 = 342
find /weekly/demanov/mchybrid/${energy}xpt500new -type f -name "*.root" > /weekly/$USER/lbavinh/$working_dir/runlist_${energy}.list
