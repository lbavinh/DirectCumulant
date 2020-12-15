# QCumulant
A code for elliptic flow v2 measurements using Q-Cumulant proposed by Ante Bilandzic in https://arxiv.org/abs/1010.0233
Implemeted for PicoDst format: https://dev.ut.mephi.ru/PEParfenov/PicoDst
## Usage (for MEPhI HPC - Cherenkov cluster)
Clone repository

```bash
git clone https://github.com/lbavinh/QCumulant.git
cd QCumulant
```

Install project via cmake

```bash
mkdir build
cd build
cmake ..
make
```

Execute `FlowQCumulant`

```bash
./FlowQCumulant -i runlist.list -o test.root
```

or run job (need to change variable `MAIN_DIR` in `Job.sh` to one's working directory path) by SLURM Workload Manager (not yet optimized)

```bash
sbatch Job.sh
```

Use output ROOT file (`test.root` in this example) to draw graphics by `v2plot.C`. On one's local computer or cluster:

```bash
root -l -b -q v2plot.C'("test.root")'
```

