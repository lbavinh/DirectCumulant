#!/bin/bash
qsub -t 1-1000 CalFlow.sh
qsub -t 1001-2000 CalFlow.sh
qsub -t 2001-3000 CalFlow.sh
qsub -t 3001-4000 CalFlow.sh
qsub -t 4001-5000 CalFlow.sh