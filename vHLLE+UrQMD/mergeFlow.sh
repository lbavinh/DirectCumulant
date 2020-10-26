#!/bin/bash

# hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_7.7GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/2164926/sum_*_*.root
# hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_11.5GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/2164927/sum_*_*.root

hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_19.6GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/2165628/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_27GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/2165663/sum_*_*.root
hadd -f -j 20 /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/vHLLE+UrQMD_39GeV.root /weekly/$USER/lbavinh/vHLLE+UrQMD/OUT/2165673/sum_*_*.root

echo "Done!"