# QCumulant
A code for elliptic flow v2 measurements using Q-Cumulant proposed by Ante Bilandzic in https://arxiv.org/abs/1010.0233
Implemeted for PicoDst format: https://dev.ut.mephi.ru/PEParfenov/PicoDst
## Usage (for NICA cluster)
Clone repository

```bash
git clone https://devel.mephi.ru/aatruttse/QCumulant.git
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
./FlowQCumulant -i [inputFileList] -o [outputFileName].root -config [configFileName]
```

```bash
root -l -b -q macros/PlotV2QCumulant.C'("[outputFileName].root")'
root -l -b -q macros/PlotV2EtaSubEventPlane.C'("[outputFileName].root")'
```
etc.

