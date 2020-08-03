#!/bin/bash
for i in {1..100}
  do 
    echo "Creating $i-th tree"
    qsub GenerateV2.sh
  done
