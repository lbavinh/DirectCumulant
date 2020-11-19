#!/bin/bash

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_7.7GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193344/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/UrQMD_11.5GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193345/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_7.7GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193346/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/SMASH_11.5GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193347/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_7.7GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193348/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT08_11.5GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193349/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_7.7GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193350/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/AMPT15_11.5GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193351/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/vHLLEUrQMD_7.7GeV_v26v28.root  /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193352/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/FlowFluctuations/OUT/vHLLEUrQMD_11.5GeV_v26v28.root /weekly/$USER/lbavinh/FlowFluctuations/OUT/2193353/sum_*_*.root