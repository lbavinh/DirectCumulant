#!/bin/bash
export energy=39
export working_dir=vHLLE+UrQMD
echo "Initializing run list for $energy GeV of $working_dir model"
#/weekly/demanov/mchybrid/77xpt500new
#/weekly/demanov/mchybrid/115xpt500new
#/weekly/demanov/mchybrid/19.6GeVxpt500
#/weekly/demanov/mchybrid/27GeVxpt
#/weekly/demanov/mchybrid/39GeVxpt500new

# 77 = 342 ; 115 = 379 ; 196 = 163 ; 27 = 252 ; 39 = 162

find /weekly/demanov/mchybrid/39GeVxpt500new -type f -name "*.root" > /weekly/$USER/lbavinh/$working_dir/runlist_${energy}.list

wc -l /weekly/$USER/lbavinh/$working_dir/runlist_${energy}.list
echo "jobs are needed"