#!/bin/bash
for i in {1..400}
  do 
    echo "Creating $i-th tree"
    qsub GenerateV2.sh
  done
