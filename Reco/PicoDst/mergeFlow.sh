#!/bin/bash
working_dir=/weekly/$USER/lbavinh/PicoDst/OUT
JOB_ID=2091547
hadd -f -j 20 ${working_dir}/UrQMD_Reco_11.5GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root