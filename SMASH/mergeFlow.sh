#!/bin/bash
#hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_7.7GeV.root /weekly/$USER/lbavinh/SMASH/OUT/1954128/sum_*_*.root
#hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_11.5GeV.root /weekly/$USER/lbavinh/SMASH/OUT/1956526/sum_*_*.root
#hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_4.5GeV.root /weekly/$USER/lbavinh/SMASH/OUT/1956968/sum_*_*.root
nohup hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_4.5GeV_fixed.root /weekly/$USER/lbavinh/SMASH/OUT/2018737/sum_*.root > merge_2018737.log &
nohup hadd -f -j 50 /weekly/$USER/lbavinh/SMASH/OUT/SMASH_7.7GeV_fixed.root /weekly/$USER/lbavinh/SMASH/OUT/2018747/sum_*_*.root > merge_2018747.log &