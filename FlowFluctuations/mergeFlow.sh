#!/bin/bash

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_4.5GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184516/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_7.7GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184517/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_11.5GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184518/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_4.5GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184519/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_7.7GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184520/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_11.5GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184521/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_27GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184522/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_7.7GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184523/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_11.5GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184524/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_27GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184525/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_7.7GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184526/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_11.5GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184527/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_27GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184528/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_39GeV.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2184529/sum_*_*.root