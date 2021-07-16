# Flow with multiple-particle correlations

This code provides anisotropic flow measurements in relativistic heavy-ion collisions using
[Q-Cumulant](http://arxiv.org/abs/1010.0233),
[Lee-Yang Zeros](http://arxiv.org/abs/nucl-th/0402053),
[event plane](http://arxiv.org/abs/nucl-ex/9805001), and
[scalar product](http://arxiv.org/abs/0809.2949) methods.

## Table of content:

I. [Installation](#Installation) \
II. [Event processing](#EventProcessing) \
III. [Result analysis](#ResultAnalysis) \
Appendix 1. [DCA correction](#Append1)

## I. Installation <a name="Installation"></a>

Requirement: 
- CMake (ver. 3.1 or higher)
- ROOT (should work with versions 5 and 6)
- [ROOT's MathMore library](https://root.cern/manual/math/#mathmore-library)

```bash
# On NICA cluster
cd /scratch2/${USER}
# Or on MEPhI's cluster
cd /mnt/pool/2/${USER}
git clone https://github.com/lbavinh/QCumulant.git
cd QCumulant
```
Remember to add the ROOT libraries to one's environment by sourcing `thisroot.sh` script. In NICA cluster terminal:
```sh
source /opt/fairsoft/bmn/may18p1/bin/thisroot.sh
```
Or, on MEPhI's Cherekov cluster:
```sh
source /mnt/pool/rhic/4/parfenovpeter/Soft/ROOT/build_v6_13/bin/thisroot.sh
```

One can install project via CMake:
```bash
mkdir build
cd build
cmake ..
make
```

## II. Event processing <a name="EventProcessing"></a>


```bash
./RunFlowAnalysis -i inFile -o outFile -config .qcumulant.cfg
```
The arguments are:

1. `inFile` can be a list or a ROOT file.

2. `outFile` is the output ROOT file. For Lee-Yang Zeros, event plane, and scalar product methods, which need more than one run over data, the output ROOT file from first run must be named as **FirstRun.root**, i.e., for the first run over the data:

    ```bash
    ./RunFlowAnalysis -i inFile -o FirstRun.root -config .qcumulant.cfg
    ```
    **FirstRun.root** must be placed in the same directory with the executable `RunFlowAnalysis` (in the same directory where `RunFlowAnalysis` is executed).

3. `.qcumulant.cfg` (configuration file) is an optional argument. In case of `.qcumulant.cfg` not being set, parameters are set by default value.

    | Parameter       | Description                                                                         | Default value 
    | --------------- | -----------                                                                         | -------------------- 
    | Nevents         | number of events in each ROOT tree to be read                                       | -1 (read all events)
    | harmonic        | order of flow harmonic                                                              | *n* = 2
    | maxpt           | higher pt limit of differential flow                                                | 3.0 GeV/*c*
    | minpt           | lower pt limit of differential flow                                                 | 0.0 GeV/*c* 
    | maxptRF         | higher pt limit of integrated (reference) flow                                      | 3.0 GeV/*c*
    | minptRF         | lower pt limit of integrated (reference) flow                                       | 0.2 GeV/*c*
    | eta_cut         | pseudorapidity cut                                                                  | \|*η*\| < 1.5
    | eta_gap         | pseudorapidity gap between two sub-event                                            | Δ*η* = ± 0.05
    | debug           | debug flag                                                                          | 1 (true)
    | format          | format of ROOT tree, which can be: `mctree`, `picodst`                              | picodst
    | | **Additional parameters for `picodst` data format** <sup>[†](#myfootnote1)</sup>|
    | Nhits_cut       | number of minimum TPC hits in `picodst`                                             | 16
    | pid_probability | probability of PID in `picodst`                                                     | 0.9
    | readMCTracks    | read MC events and corresponding MC tracks in `picodst`                             | 0 (false)
    | bMotherIDcut    | use *motherID* cut for primary track cut in `picodst`                               | 1 (true)
    | DCAcut          | number of sigma cut of 3-D DCA distribution used for primary track cut in `picodst` | *σ* < 2.0

    Other parameters (`METHOD_NAME_RUN_NUMBER`) indicate which methods are going to be used and their run order. For event-plane based methods, the first run over the data (`METHOD_NAME_1` = 1) calculates resolution factor, and the second one (`METHOD_NAME_2` = 1) calculates flow coefficient $v_n$.

    In order to use [Lee-Yang Zeros event plane](http://arxiv.org/abs/0801.3915) (`LYZEP`) method, one need to run `LYZ_SUM_1` and `LYZ_SUM_2` beforehand with strict output file name: **FirstRun.root** and **SecondRun.root**, respectively, then place them in the same directory with the executable.

    <a name="myfootnote1">†</a> If `format` parameter is chosen to be `mctree` (data from generator level without realistic reconstruction), the following parameter are automatically omitted: `Nhits_cut`, `DCAcut`, `pid_probability`, `readMCTracks`, and `bMotherIDcut`. Thus, one does not need to set these parameters when working with `mctree` data format.

As an example, *CalFlow.sh* is a bash script for submitting parallel jobs on NICA cluster. 
```sh
qsub ../CalFlow.sh
```
Also, *Job.sh* bash script is provided as an example for MEPhI's Cherenkov cluster:
```sh
sbatch Job.sh
```
After each run over the data, one need to merge all output files by `hadd`
```sh
hadd -j 4 outputFileName ./OUT/${JOB_ID}/sum_${JOB_ID}_*.root
```
where `outputFileName` - output file, should be named **FirstRun.root**, **SecondRun.root**, etc.
## III. Result analysis <a name="ResultAnalysis"></a>

Macros for result plotting are stored in **QCumulant/macros**
```sh
cd ../macros
cp ../build/*Run.root ./
```
1. Q-Cumulant method:

    Anisotropic flow measurements obtained by v_n{2} and v_n{4}$ are plotted by *PlotV2QCumulant.C* 
    ```sh
    root -l -b -q PlotV2QCumulant.C'("FirstRun.root")'
    ```
    Higher-order Q-Cumulants: v_n{6} and v_n{8} are plotted by *PlotV2HighOrderQCumulant.C*
    ```sh
    root -l -b -q PlotV2HighOrderQCumulant.C'("FirstRun.root")'
    ```
2. Event-plane (including `LYZEP`) and scalar product methods are plotted using *PlotV2EventPlane.C*:
    ```sh
    root -l -b -q PlotV2EventPlane.C'("SecondRun.root","METHOD_NAME")'
    ```
    `METHOD_NAME` can be EtaSub, SP, FHCalEP, LYZEP, Eta3Sub, MC.
3. Lee-Yang Zeros method is plotted by *PlotV2LYZ.C*
    ```sh
    root -l -b -q PlotV2LYZ.C'("FirstRun.root","SecondRun.root",bUseProduct)'
    ```
    The 3-rd argument: `bUseProduct` is set to be *true* for `LYZ_PRODUCT`, and *false* for `LYZ_SUM`.

## Appendix 1. DCA correction<a name="Append1"></a>

For the flow analysis of the `picodst` format one does need the information about DCA distributions to distinguish primary particles from secondary ones. While the former carry the needed information about the initial geometry of the colliding system, the latter deteriorate this signal. Such process includes 3 main steps:
- Get DCA distributions and store them into calibration file;
- Fit DCA distributions via gaus function to make primary particles selection in terms of n-sigma;
- Fit pt dependence of the DCA distributions via polynomial function to reduce pt efficiency loss due to the DCA distributions are split into discrete pt bins.

1. To get light calibration file containing only histograms with DCA distributions `GetDCA` executable is used:  
    ```sh
    cd CumulantFlow/build
    ./GetDCA -i inFile -o DCA_HIST.root
    ```
    Where the arguments are:
    - `inFile` - input file, can be either a picoDst tree or a list of picoDst trees.
    - **DCA_HIST.root** - output file: standard root file with `TH1*` histograms of the DCA distributions needed for the further DCA cuts.

2. Next, `FitDCA` is used for 2-iteration fitting procedure. The first iteration fits DCA distributions with gaus functions, while the second one aims to distinguish primary particles without *p*T, *η* efficiency loss due to $p_{T}$, $\eta$-dependence of the DCA distributions.
    ```sh
    ./FitDCA -i DCA_HIST.root -o DCA_FIT.root
    ``` 
    Where the arguments are:  
    - **DCA_HIST.root** - input file: standard root file with `TH1*` histograms needed for the further DCA cuts (output file from `GetDCA`).
    - **DCA_FIT.root** - output file: standard root file with `TH2*` histograms and `TF2*` fitted function needed for the further DCA cuts (`f_sigma`) - for improving *p*T, *η* efficiency.

The resulting file **DCA_FIT.root** contains `TF2*` functions used in flow analysis with `DCAcut` parameter. It should be placed in the same directory, where the `RunFlowAnalysis` will be executed.