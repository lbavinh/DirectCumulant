#!/bin/bash
# hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_7.7GeV.root /weekly/$USER/lbavinh/SMASH/OUT/2163514/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_11.5GeV.root /weekly/$USER/lbavinh/SMASH/OUT/2164047/sum_*_*.root
# hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_4.5GeV.root /weekly/$USER/lbavinh/SMASH/OUT/2163513/sum_*_*.root



# nohup hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_7.7GeV_fixed.root /weekly/$USER/lbavinh/SMASH/OUT/2018747/sum_*_*.root > merge_2018747.log &