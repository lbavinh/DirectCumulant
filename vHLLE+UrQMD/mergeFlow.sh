#!/bin/bash
hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_11.5GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/1995863/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_7.7GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/1995864/sum_*_*.root
echo "Done!"