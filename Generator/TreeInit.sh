#!/bin/bash
for i in {1..200}
  do 
    echo "Creating $i-th tree"
    qsub GenerateV2.sh
  done
