#!/bin/bash

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_7.7GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198794/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_11.5GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198795/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_7.7GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198796/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_11.5GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198797/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_7.7GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198798/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_11.5GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198799/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_7.7GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198800/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_11.5GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198801/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/vHLLEUrQMD_7.7GeV_samecutwithSTARBES.root  /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198802/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/vHLLEUrQMD_11.5GeV_samecutwithSTARBES.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2198803/sum_*_*.root