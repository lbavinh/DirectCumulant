#/bin/bash
# https://twiki.cern.ch/twiki/bin/view/Main/BatchJobs#JobSub

#jq=8nm
jq=8nh
#jq=1nd
#jq=2nd

debug=echo
for i in {000..099}; do
  bsub -R "pool>50000" -q $jq -J $i run.sh $i 10000 100 $1 $2 $3
  #sleep 0.1 
  sleep 1
done
