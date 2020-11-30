# QCumulant
A code for elliptic flow v2 measurements using Q-Cumulant proposed by Ante Bilandzic in https://arxiv.org/abs/1010.0233
Implemeted for PicoDst format: https://dev.ut.mephi.ru/PEParfenov/PicoDst
## Usage (for MEPhI HPC - Cherenkov cluster)
1. Clone repository
```bash
git clone https://github.com/lbavinh/QCumulant.git
cd QCumulant
```
2. Set environment variables for ROOT and PicoDst libraries
```bash
source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh
source /mnt/pool/2/lbavinh/Soft/PicoDst/build/setPicoDst.sh
```
3. Run `FlowQCumulant.C` in interative regime
```bash
root -l -b -q FlowQCumulant.C+'("runlist.list","test.root")'
```
or run job (need to change variable `MAIN_DIR` in `Job.sh` to one's working directory path) by SLURM Workload Manager
```bash
sbatch Job.sh
```
4. Use output ROOT file (`test.root` in this example) to draw graphics by `v2plot.C`. On one's local computer or cluster:
```bash
root -l -b -q v2plot.C'("test.root")'
```

