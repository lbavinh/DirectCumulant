#!/bin/bash
working_dir=/weekly/$USER/lbavinh/PicoDst/OUT
JOB_ID=2125546
hadd -f ${working_dir}/UrQMD_Reco_7.7GeV_10M.root ${working_dir}/${JOB_ID}/sum_*_*.root
