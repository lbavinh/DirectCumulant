#!/bin/bash
# hadd -f /weekly/$USER/lbavinh/UrQMD/OUT/UrQMD_4.5GeV.root /weekly/$USER/lbavinh/UrQMD/OUT/1937133/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/UrQMD/OUT/UrQMD_11.5GeV.root /weekly/$USER/lbavinh/UrQMD/OUT/1950553/sum_*_*.root