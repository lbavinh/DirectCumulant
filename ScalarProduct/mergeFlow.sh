#!/bin/bash
working_dir=/weekly/$USER/lbavinh/ScalarProduct/OUT
# JOB_ID=2104048
# hadd -f -j 20 ${working_dir}/UrQMD_7.7GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root
# JOB_ID=2119108
# hadd -f -j 20 ${working_dir}/UrQMD_11.5GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root
JOB_ID=2119763
hadd -f -j 20 ${working_dir}/Reco_UrQMD_7.7GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root
# JOB_ID=2119109
# hadd -f -j 20 ${working_dir}/Reco_UrQMD_11.5GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root
