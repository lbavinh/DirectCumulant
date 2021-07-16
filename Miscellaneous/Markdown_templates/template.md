# Quick information with step-by-step instruction.
***

The following write up provides the detailed description of all programs used for the physics
performance studies for the reconstruction of directed (v1) and elliptic (v2) flow signals of identified
charged hadrons from Au+Au collisions at 4-11 GeV. The standard event plane method was used for
the present work. For a given event, the plane was reconstructed using the directed flow of spectators
detected in the Forward hadronic calorimeter (FHCAL).

## Table of content:
* 1. [MPD Simulation process](#Sim)
  * 1.1 [Setting environment variables](#Sim_1)
  * 1.2 [Generator for simulation](#Sim_2)
  * 1.3 [Monte Carlo part](#Sim_3)
  * 1.4 [Reconstruction](#Sim_4)
  * 1.5 [DCA correction](#Sim_5)
* 2. [The creation of the picoDST’s for the Flow Analysis](#Data)
  * 2.1 [DCA calibration file](#Data_1)
  * 2.2 [Centrality calibration file](#Data_2)
  * 2.3 [The source code for the picoDST’s production](#Data_3)
* 3. [Azimuthal Anisotropic Flow Analysis](Flow)
  * 3.1 [Event plane resolution factor](#Flow_1)
  * 3.2 [Azimuthal anisotropic flow signals v1 and v2.](#Flow_2)
* Appendix 1. [Installation of the correct FHCal     geometry in the MPDRoot framework and MPDRoot preparation](#App_1)
* Appendix 2. [Installation of the UrQMD generator](#App_2)


<a name="Sim"></a>
## 1. MPD Simulation process

Simulation contains 3 main parts:  
-- Particle generation (UrQMD);  
-- Monte Carlo simulation (GEANT4);  
-- Reconstruction procedure (Tracking, etc.).  
In order to start the MPD simulations one needs to install correct FHCal geometry (see Appendix 1), install generator (see Appendix 2) and run MPD simulation code.

<a name="Sim_1"></a>
### 1.1 Setting environment variables

First of all, one should set FairSoft and MPDRoot variables:  
```
    source MPDRoot/build/config.sh
```

or source it to the place where `config.sh` is stored.  

        export SIMPATH=<path to FairSoft>  
        export ROOTSYS=$SIMPATH  
        export PATH=$SIMPATH/bin:$PATH  
        export LD_LIBRARY_PATH=$SIMPATH/lib:$SIMPATH/lib/root:$LD_LIBRARY_PATH  
        source geant4.sh  
        platform=(root-config --arch)  

Note, that new versions of mpdroot and fairsoft requires one additional environment varable `Boost_INCLUDE_DIRS`:

        export Boost_INCLUDE_DIRS="<path_to_fairsoft>/include/"

where directory `boost/serialization/` is stored.

<a name="Sim_2"></a>
### 1.2 Generator part

In order to simulate particles using UrQMD generator ( as an example). Run `runqmd.bash` in urqmd-3.4 directory:  

        . runqmd.bash

Resulting file will be `test.f14`.  

<a name="Sim_3"></a>
### 1.3 Monte Carlo simulation

To start the simulation process with MPD detector, run `mpdroot/macro/mpd/runMC.C`:  

        root -b runMC.C(inFile, outFile, nStartEvent, nEvents, flag_store_FairRadLenPoint, FieldSwitcher)

Where the arguments are:  
`inFile` - input `test.f14` file from generator (`"./test.f14"` by the default).  
`outFile` - output file from GEANT4 (`"./evetest.root"` by the default).  
`nStartEvent` - starting GEANT4 from this event (`0` by default).  
`nEvents` - number of all events that was in `test.f14` (`250` by the default).  
`flag_store_FairRadLenPoint` should be set by the default (`kFALSE`).  
`FieldSwitcher` should be set by the default (`0`).  

If `test.f14` contains 250 events, the `runMC.C` macro can have only 1 argument:  

        root -b runMC.C("<path to test.f14>")

<a name="Sim_4"></a>
### 1.4 Reconstruction of MC events

Reconstruction procedure gives the final output with simulated data. Run `mpdroot/macro/mpd/reco.C`:

        root -b reco.C(inFile, outFile, nStartEvent, nEvents, run_type)

Where the arguments are:  
`inFile` - input `evetest.root` file from GEANT4 simulation (`"./evetest.root"` by the default).  
`outFile` - output file from the reconstruction procedure (`"./mpddst.root"` by the default).  
`nStartEvent` - starting reconstruction from this event (`0` by default).  
`nEvents` - number of all events that was in `evetest.root` (`250` by the default).  
`run_type` should be set by default (`"local"`).

<a name="Sim_5"></a>
### 1.5 DCA correction

In the present version of MPD ROOT the final reconstructed tracks include the information about the
distance of closest approach (DCA), which based on z-dependent calculations in the 2D transverse plain.
The values of DCA, obtained by this method, were found not robust enough for selection of primary
tracks. In order to solve this problem, we rewrite the values of DCA in the reconstructed mpdroot tree after reconstruction
by new values obtained by 3D helicity fitting method.
    <center><a href="https://git.jinr.ru/nica/mpdroot" target="_blank">https://git.jinr.ru/nica/mpdroot</a></center>  

It can be installed by

        git clone -b dev --recursive git@git.jinr.ru:nica/mpdroot.git

Use `mpdroot/macro/physical_analysis/restore_dca`:  

        root -b rootlogon.C  
        -------------------in root session---------------------  
        gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C")  
        mpdloadlibs(kTRUE,kTRUE)  
        .L restore_dca.c+  
        restore_dca("inFileName","outFileName")  
        -------------------root session end--------------------  
Where arguments:  
    `inFileName` - input mpdroot tree after reconstruction with uncorrect dca values.  
    `outFileName` - output mpdroot tree after reconstruction with correct dca values. Everything else is the same as it was in inFileName.  
Macro `restore_data.c` copies mpdroot files and replaces uncorrected dca values in the mpdroot tree after reconstructions.  

Resulting `mpddst.root` files contain results from both simulation via GEANT4 (generated data) and reconstruction procedure (reconstructed data).
***
<a name="Data"></a>
## 2.The creation of the picoDST’s for the Flow Analysis

In order to get a large sample of the reconstructed events for the physics performance study,
we converted all mpddst.root files into picoDST format by selecting only primary tracks
based on DCA cuts and writing only such variables, which one need for flow analysis. The
format for picoDST is the plain ROOT TREE which allows to use them on any system.

<a name="Data_1"></a>
### 2.1 DCA calibration file

For the further analysis one does need the information about dca distributions to distinguish primary particles from secondary ones. While the former carry the needed information about the initial geometry of the colliding system, the latter deteriorate this signal. Such process includes 3 main steps:  
    --Get dca distributions and store them into calibration file;  
    --Fit dca distributions via gaus function to make primary particles selection in terms of n-sigma;  
    --Fit pt dependence of the dca distributions via polynomial function to reduce pt efficiency loss due to the dca distributions are split into discrete pt bins.  

<u><big>2.1.1</big></u>  To get light calibration file containing only histograms with dca distributions `get_dca.cxx` is used in the mpdroot/macro/physical_analysis/get_dca/ directory:  

        root -b rootlogon.C  
        -------------------in root session---------------------  
        gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C")  
        mpdloadlibs(kTRUE,kTRUE)  
        .L get_dca.cxx+  
        get_dca("inFileName","outFileName")  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input mpdroot tree after reconstruction with corrected dca values (see `restore_dca.h`).  
    `outFileName` - output: standard root file with `TH1*` histograms needed for the further DCA cuts.  
Resulting file contains `TH1*` histograms of the dca distributions.  

<center> !!! If `get_dca()` was used for several files, use `hadd` to merge `outFileName` files into 1 merged file. !!! </center>

<u><big>2.1.2</big></u> Next, `get_fit.cxx` is used for 1-st iteration fitting procedure. It fits dca distributions with gaus functions:  

        root -b  
        -------------------in root session---------------------  
        .L get_fit.cxx+  
        get_fit("inFileName","outFileName")  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input: standard root file with `TH1*` histograms needed for the further DCA cuts (output file from `get_dca(...)`).  
    `outFileName` - output: standard root file with `TH1*` histograms and `TF1*` fitted function needed for the further DCA cuts.  

Resulting file contains `TH1*` histograms from the `get_dca.cxx` output file and their `TF1*` fitted functions.  

<u><big>2.1.3</big></u> Finaly, to be able to distinguish primary particles without pt efficiency loss due to pt-dependence of the dca distributions, 2-nd iteration of the fitting procedure is used:  

        root -b  
        -------------------in root session---------------------  
        .L MakeFitDCA.cxx+  
        MakeFitDCA("inFileName","outFileName")  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input: standard root file with `TH1*` histograms and `TF1*` fitted function needed for the further DCA cuts (output from `get_fit(...)`).  
    `outFileName` - output: standard root file with `TH1*` histograms and `TF1*` fitted function needed for the further DCA cuts (`pt_sigma_fit`) - for improving pt efficiency.  
The resulting file contains `sigma_pt_fit` - `TF1*` functions that will be using further.  

<a name="Data_2"></a>
### 2.2 Centrality calibration file

The next step is to get centrality classification. Thus, one should use calibration file with multiplicity along with dca fit files in the previous step. To get multiplicity calibration file, use `get_multiplicity.cxx` in mpdroot/macro/physical_analysis/get_centrality directory:  

        root -b rootlogon.C  
        -------------------in root session---------------------  
        gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C")  
        mpdloadlibs(kTRUE,kTRUE)  
        .L get_multiplicity.cxx+  
        get_multiplicity("inFileName","outFileName","dcaFileName")  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input mpdroot tree after reconstruction with corrected dca values (see `restore_dca.h`).  
    `outFileName` - output: standard root file with `TH1*` histograms needed for the further DCA cuts.  
    `dcaFileName` - Second iteration of the dca fitting containing `sigma_pt_fit TF1*` functions (output `MakeFitDCA(...)`).  

The resulting file contains `TH1*` histogram of multiplicity in TPC.  

<center>!!! If `get_multiplicity()` was used for several files, use hadd to merge `outFileName` files into 1 merged file. !!!</center>  

<a name="Data_3"></a>
### 2.3 The source code for the picoDST’s production

To convert mpdroot tree after reconstruction after reconstruction into picoDST files (which are standard TTrees) use `reducedTreeCreator.C` in mpdroot/macro/physical_analysis/create_reduced_tree directory:  

        root -b rootlogon.C  
        -------------------in root session---------------------  
        gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C")  
        mpdloadlibs(kTRUE,kTRUE)
        .L reducedTreeCreator.C+
        reducedTreeCreator rtc = reducedTreeCreator("inFileHistName", "inFileTreeName", "outFileName", "dcaFileName")  
        rtc.CreateReducedTree()  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileHistName` - input standard root file with `TH1*` histograms of multiplicity (output from `get_multiplicity(...)`).  
    `inFileTreeName` - input mpdroot tree after reconstruction with corrected dca values (output from `restore_dca(...)`).  
    `outFileName` - output standard root file with TTree picoDST for the further analysis.  
    `dcaFileName` - Second iteration of the dca fitting containing `sigma_pt_fit TF1*` functions (output from `MakeFitDCA(...)`).  


The resulting file contains standard TTree picoDST with all needed information. This TTrees works ~1000 times faster than mpdroot.  
***
<a name="Flow"></a>
## 3. Azimuthal anisotropic flow measurements

Azimuthal anisotropic flow measurements is implemented in Flow analysis framework (see <u><big>1.5</big></u>). It works with picoDST files (see <u><big>2</big></u>).

Before measuring direct and elliptic flow (v1 and v2), one should calculate the resolution correction factor.

<a name="Flow_1"></a>
### 3.1 Resolution correction factor

To calculate event plane resolution correction factor using 2 sub-event technique, use `MpdCalculator.cxx` in mpdroot/macro/physical_analysis/real-flow directory:  

        root -b  
        -------------------in root session---------------------  
        gSystem->Load("libMathMore")  
        .L ../Utilities/BinningData.cxx+  
        .L ../Utilities/utility.cxx+  
        .L MpdCalculator.cxx+  
        MpdCalculator mpd = MpdCalculator(inFileName,outFileName,dcaFileName)  
        mpd.CalculateResolutions(0)  
        mpd.Write()  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input standard root file with TTree picoDST for the further analysis (output from `reducedTreeCreator` class).  
    `outFileName` - output standard root file with TProfiles and histograms containing data for resolution correction factor.  
    `dcaFileName` - Second iteration of the dca fitting containing `sigma_pt_fit TF1*` functions (output from `MakeFitDCA(...)`).  
The resulting file contains TProfiles of cosine functions of the subevents angles.  

<center>!!! If `MpdCalculator::CalculateResolutions(0)` was used for several files, use hadd to merge `outFileName` files into 1 merged file. !!!</center>  

To calculate resolution correction factor for event plane from cosine of the difference between 2 subevent angles, averaged over events < cos(Psi_A-Psi_B) >, `get_res.cxx` is used:  

        root -b  
        -------------------in root session---------------------  
        gSystem->Load("libMathMore")  
        .L get_res.cxx+  
        get_res("inFileName","outFileName")  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input: standard root file with TProfiles and histograms containing data for resolution correction factor (output from `MpdCalculator::CalculateResolutions(0)`).  
    `outFileName` - output: standard root file with `TH1*` histograms and `TF1*` fitted function needed for the azimuthal flow calculation (`MpdCalculator::CalculateFlow(...)`).  
Resulting file contains `TH1*` histograms and `TF1*` functions of the resolution correction factor.  

<a name="Flow_2"></a>
### 3.2 Azimuthal anisotropic flow calculation

To calculate azimuthal flow use `MpdCalculator.cxx` again:  

        root -b  
        -------------------in root session---------------------  
        gSystem->Load("libMathMore")  
        .L ../Utilities/BinningData.cxx+  
        .L ../Utilities/utility.cxx+  
        .L MpdCalculator.cxx+  
        MpdCalculator mpd = MpdCalculator(inFileName,outFileName,dcaFileName)  
        mpd.CalculateFlow(0, resFitFile.Data())  
        mpd.Write()  
        -------------------root session end--------------------  
Where the arguments are:  
    `inFileName` - input standard root file with TTree picoDST for the further analysis (output from `reducedTreeCreator`).  
    `outFileName` - output standard root file with TProfiles and histograms containing data for resolution correction factor.  
    `dcaFileName` - Second iteration of the dca fitting containing `sigma_pt_fit TF1*` functions (output `MakeFitDCA(...)`).  
    `resFitFile` - input standard root file with `TH1*` histograms and `TF1*` fitted function of resolution (output from `get_res(...)`).  

### OUTPUT:  
Resulting file contains TProfiles of v1 and v2 as a function of:  
* centrality (reconstructed: p_flow_wrt_full_vs_centrality_divided, generated: p_flow_wrt_RP_vs_centrality),  
* transverse momentum (reconstructed: p_flow_wrt_full_vs_pt_divided, generated: p_flow_wrt_RP_vs_pt),  
* pseudorapidity (reconstructed: p_flow_wrt_full_vs_eta_divided, generated: p_flow_wrt_RP_vs_eta),  
* rapidity (reconstructed: p_flow_wrt_full_vs_rapidity_divided, generated: p_flow_wrt_RP_vs_rapidity).  

<center>!!! By the default, azimuthal flow is calculated for protons. !!!</center>

To change it to pions or kaons one should modify the line 700 in `MpdCalculator.cxx`:  
from  
    `Int_t sort = 0;` - proton  
to  
    `Int_t sort = 1;` - kaon  
or  
    `Int_t sort = 2;` - pion  
and recompile the `MpdCalculator.cxx`.  
***
<a name="App_1"></a>
## Appendix 1. Installation of the correct FHCal geometry in the MPDRoot framework and MPDRoot preparation

<u><big>1.1</big></u> Use branch marina_070417 in GIT repository:
<center><a href="https://git.jinr.ru/nica/mpdroot" target="_blank">https://git.jinr.ru/nica/mpdroot</a></center>  
One can download files from GIT using:

        git clone git@git.jinr.ru:nica/mpdroot.git
        git checkout marina_070417

<u><big>1.2</big></u> To create corresponding root file with correct FHCal geometry for reconstruction, run:

        root -b mpdroot/macro/mpd/geometry/create_rootgeom_zdc_oldnames_7sect_noSlots_v1.C

Such root file will be stored in the directory `mpdroot/geometry/zdc_oldnames_7sect_noSlots_v1.root`.

Then include root file name into mpd geometry file `mpdroot/macro/mpd/geometry_stage1.C` (line 51):

        Zdc->SetGeometryFileName("zdc_oldnames_7sect_noSlots_v1.root");

For the only PSD performance we keep information about hits in the way:
- FHCal number
- module number
- slice number (1 - 42)
- deposited energy in slice (in the event)

The number of hits in each event is not more than 2x45x42 which allows to
have rather small output root files.
In this case information about MC tracks is lost.

More details are stored here:
<center><a href="https://git.jinr.ru/nica/mpdroot/blob/marina_070417/zdc/README" target="_blank">https://git.jinr.ru/nica/mpdroot/blob/marina_070417/zdc/README</a></center>

<u><big>1.3</big></u> For the further analysis, information about MC tracks is needed. To have such information, one should do:

        cd mpdroot/zdc
        cp MpdZdc.cxx.ProcHitsTracks_newgeomZDC  MpdZdc.cxx

and recompile MPDRoot.

<u><big>1.4</big></u> One needs to change `mpdroot/macro/mpd/runMC.C`:
line 49:

        #define URQMD
Optionally, change `auau.09gev.mbias.98k.ftn14` to `test.f14` everywhere in the code since UrQMD will be used as a particle generator.

<u><big>1.5</big></u> Two tracking algorithms that can be used:
- Idealistic - hit producer (by default);
- Realistic - cluster finder.

To change from hit producer to cluster finder, find in `mpdroot/macro/mpd/reco.C` lines:

        MpdTpcHitProducer* hitPr = new MpdTpcHitProducer();
        hitPr->SetModular(0);
        fRun->AddTask(hitPr);
and change them into:

        MpdTpcDigitizerAZ* tpcDigitizer = new MpdTpcDigitizerAZ();
        tpcDigitizer->SetPersistence(kFALSE);
        fRun->AddTask(tpcDigitizer);

Also, emc tracking was not used, so lines

        FairTask *emcHP = new MpdEmcHitProducer();
        fRun->AddTask(emcHP);
can be deleted.

<u><big>1.6</big></u> In further MC simulation, event plane will be generated. Thus, it requires modification in `mpdroot/base/event/FairMCEventHeader.h` (in line 62):

         Double_t GetEP()    const { return fEP; }        /// Event plane

in line 66:

        void SetEP(Double_t phi)          { fEP = phi; }
in line 90:

        Double32_t fEP;          /// Event plane smearing


In `mpdroot/base/event/FairMCEventHeader.cxx`:  
line 22,43:

        fEP(0.),

line 90

        fX = fY = fZ = fT = fB = fPhi = fEP = 0.;

In new version of mpdroot such rotation procedure has been implemented already, so `mpdroot/generators/MpdUrqmdGenerator.cxx` requires only 1 modification:  
line 215 (after line `FairMCEventHeader* event = primGen->GetEvent();`):

        event->SetEP(phi);

<a name="App_2"></a>
## Appendix 2. Installation of the UrQMD generator

<u><big>2.1</big></u> Download urqmd.tar.gz:  
    <center><a href="http://urqmd.org/download/src/urqmd-3.4.tar.gz" target="_blank">http://urqmd.org/download/src/urqmd-3.4.tar.gz</a></center>  
and place it in the directory.

<u><big>2.2</big></u> Untar file  

        tar xzvvf urqmd-3.4.tar.gz  

<u><big>2.3</big></u> Compile UrQMD

        cd urqmd-3.4/  
        make  

<u><big>2.4</big></u> Set UrQMD to generate 250 events of Au-Au collision at 11 GeV energy for impact parameter range (0,20) fm. Change urqmd-3.4/inputfile into  

        pro 197 79  
        tar 197 79  

        nev 250  
        imp -20  

        ecm 11  
        tim 200 200  
        rsd randomnumber  

        f13  
        #f14  
        f15  
        f16  
        f19  
        f20  

        xxx  

In order to set unique set of a random number sequence, change `randomnumber` value every time the UrQMD generator is used. For example, one can do in bash:  

        sed -e "s|randomnumber|$RANDOM|" -i inputfile
***
