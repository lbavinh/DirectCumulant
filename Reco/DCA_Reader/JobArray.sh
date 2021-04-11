#!/bin/bash

# Main directory, where your tmp files will be during execution
#SBATCH -D /tmp
# Name of the job
#SBATCH -J Flow
# Name of the queue, where your job is going to be executed
#SBATCH -p compute
# Max time which job can take: Day-HOURS:MIN:SEC
#SBATCH --time=0-00:30:00
# Number of arrays (by default: 1-10)
#SBATCH -a 1-10
# Output from the job (-o - output -e - error log)
#SBATCH -o /dev/null
#SBATCH -e /dev/null

export MAIN_DIR=/mnt/pool/5/lbavinh/QCumulant/build
export FILELIST=${MAIN_DIR}/split/runlistSGE_UrQMD_7.7_Reco.list
export INFILE=`sed "${SLURM_ARRAY_TASK_ID}q;d" $FILELIST`
export OUT_DIR=${MAIN_DIR}/OUT
export OUT_FILE=${OUT_DIR}/sum_${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.root
export OUT_LOG=${OUT_DIR}/log/sum_${SLURM_ARRAY_JOB_ID}_${SLURM_ARRAY_TASK_ID}.log

echo "JobId: ${SLURM_ARRAY_JOB_ID}; TaskId: ${SLURM_ARRAY_TASK_ID};" &>>${OUT_LOG}
echo "Input file: ${INFILE}" &>> ${OUT_LOG}

#mkdir -p ${OUT_DIR}
mkdir -p ${OUT_DIR}/log
#mkdir -p ${TMP_DIR}

#cp ${MAIN_DIR}/macro.C ${TMP_DIR}

cd ${MAIN_DIR}

# Set correct environment variables (needed version of root)
#source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh
./GetDCA -i ${INFILE} -o ${OUT_FILE} &>>${OUT_LOG}
#root -l -b -q ${TMP_DIR}/macro.C+'("'${INFILE}'","'${OUT_FILE}'")' &>> ${OUT_LOG}

#rm -rf $TMP_DIR

