#!/bin/bash
working_dir=/weekly/$USER/lbavinh/FlowANA/OUT/urqmd/7.7gev
LOG=${working_dir}/UrQMD_7.7GeV_V2R1.log
nohup hadd -f -j 20 ${working_dir}/UrQMD_7.7GeV_V2R1.root ${working_dir}/2012083/flowANA_*_*.root > $LOG &