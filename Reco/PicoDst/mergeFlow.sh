#!/bin/bash
working_dir=/weekly/$USER/lbavinh/readPicoDst/OUT
JOB_ID=2086955
hadd -f -j 20 ${working_dir}/UrQMD_Reco_7.7GeV_new.root ${working_dir}/${JOB_ID}/sum_*_*.root