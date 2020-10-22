#!/bin/bash
working_dir=/weekly/$USER/lbavinh/GenericFramework/OUT
JOB_ID=2104048
hadd -f -j 20 ${working_dir}/UrQMD_7.7GeV.root ${working_dir}/${JOB_ID}/sum_*_*.root