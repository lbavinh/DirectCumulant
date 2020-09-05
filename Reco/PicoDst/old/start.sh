#!/bin/bash
qsub -t 1-1000 CalFlow.sh
qsub -t 1001-2000 CalFlow.sh
qsub -t 2001-3000 CalFlow.sh
qsub -t 3001-4000 CalFlow.sh
qsub -t 4001-5000 CalFlow.sh
qsub -t 5001-6000 CalFlow.sh
qsub -t 6001-7000 CalFlow.sh
qsub -t 7001-8000 CalFlow.sh
qsub -t 8001-9000 CalFlow.sh
qsub -t 9001-9487 CalFlow.sh