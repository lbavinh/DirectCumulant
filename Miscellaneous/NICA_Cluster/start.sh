#!/bin/bash

#
# Specify working directory
#$ -wd /nica/mpd21/$USER/SimData/UrQMD/TMP
# Tell SGE that we will work in the woeking directory
#$ -cwd
# Specify job name
#$ -N run_sim_urqmd
# Specify SGE queue
#$ -q all.q
# Set hard time limit. If it is exceeded, SGE shuts the job
#$ -l h_rt=8:00:00
# Set soft time limit - set up the same as a hard limit
#$ -l s_rt=8:00:00
# Specify job array range (how many jobs will be created
#$ -t 1-200
#
# Specify directory where output and error logs from SGE will be stored
#$ -o /nica/mpd21/$USER/SimData/UrQMD/TMP
#$ -e /nica/mpd21/$USER/SimData/UrQMD/TMP
#

# ${JOB_ID} - Id of the job array (one for all jobs)
# ${SGE_TASK_ID} - id of the element of the job array
# SGE option "-t 1-N" tells array range. It will create an array
#     of N jobs with ${JOB_ID}_1, ${JOB_ID}_2, ..., ${JOB_ID}_N

#Main directory
export MAIN_DIR=/nica/mpd21/${USER}/SimData/UrQMD

#Energy in cms
ecm=4.5
#Number of events
nev=5000

#Commit for output directory
export COMMIT=URQMD_MCPICO_${ecm}gev/${JOB_ID} #`date +%d%m%y_%H%M%S`

source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
export START_DIR=${PWD}
export OUT_DIR=${MAIN_DIR}/OUT/${COMMIT}
export TMP_DIR=${MAIN_DIR}/TMP
export OUT=${OUT_DIR}
export OUT_LOG=${OUT}/log
export OUT_FILE=${OUT}/files
export TMP=${TMP_DIR}/TMP_${JOB_ID}_${SGE_TASK_ID}
export INPUTFILE=${MAIN_DIR}/scripts/inputfile.template
export LOG=${OUT_LOG}/JOB_${JOB_ID}_${SGE_TASK_ID}.log
touch $LOG

mkdir -p $OUT_LOG
mkdir -p $OUT_FILE
mkdir -p $TMP

echo "Input arguments (Job Id = ${JOB_ID}):" &>> $LOG
echo "Main directory:           ${MAIN_DIR}" &>> $LOG
echo "Number of events per job: ${nev}"      &>> $LOG
echo "Energy (sNN):             ${ecm}"      &>> $LOG

export URQMD_DIR=/nica/mpd21/parfenov/Soft/urqmd-3.4
export MCINI_DIR=/nica/mpd21/parfenov/Soft/mcini
export CONVERTER_MACRO=${MCINI_DIR}/macro/convert.C

cd ${TMP}
cp ${URQMD_DIR}/runqmd.bash ${TMP}/
cp ${URQMD_DIR}/urqmd.x86_64 ${TMP}/
cp $INPUTFILE ${TMP}/inputfile

sed -e "s|energyincms|$ecm|" -i inputfile
sed -e "s|numberofevents|$nev|" -i inputfile
sed -e "s|randomrandom|`shuf -i 1-1000000 -n 1`|" -i inputfile

cat inputfile &>> $LOG
echo "---------------" &>> $LOG
echo "Running UrQMD..." &>> $LOG
. ${TMP}/runqmd.bash &>> $LOG

echo "---------------" &>> $LOG
echo "Run mcini converter..." &>> $LOG
. ${MCINI_DIR}/macro/config.sh &>> $LOG
root -l -q -b ${MCINI_DIR}/macro/convertUrQMD.C'("test.f20","'unigen.root'")' &>> $LOG

echo "---------------" &>> $LOG
echo "Run mcini2mcpico converter..." &>> $LOG
root -l -b -q $CONVERTER_MACRO'("'unigen.root'","'${OUT_FILE}/urqmd_${JOB_ID}_${SGE_TASK_ID}.mcpico.root'")' &>> $LOG

echo "---------------" &>> $LOG
echo "Cleaning temporary directory..." &>> $LOG
cd ${START_DIR}
rm -rf ${TMP}

echo "Job is done!" &>> $LOG
