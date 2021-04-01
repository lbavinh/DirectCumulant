// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TClonesArray.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TString.h>
#include <TEnv.h>

// PicoDst headers
#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

#include <IReader.h>
#include <PicoDstReader.h>

#include <QVector.h>
#include <FlowAnalysisWithEtaSubEventPlane.h>
#include <FlowAnalysisWithThreeEtaSubEventPlane.h>
#include <FlowAnalysisWithFHCalEventPlane.h>
#include <FlowAnalysisWithLeeYangZeros.h>
#include <FlowAnalysisWithScalarProduct.h>
#include <FlowAnalysisWithQCumulant.h>
#include <FlowAnalysisWithHighOrderQCumulant.h>
#include <FlowAnalysisWithLeeYangZerosEventPlane.h>
// #include "constants.C"
#include "utilities.C"

using std::cout;
using std::cerr;
using std::endl;

bool ETASUBEVENTPLANE_1 = 1;
bool ETASUBEVENTPLANE_2 = 0;
bool THREEETASUBEVENTPLANE_1 = 1;
bool THREEETASUBEVENTPLANE_2 = 0;
bool FHCALEVENTPLANE_1 = 1;
bool FHCALEVENTPLANE_2 = 0;
bool LYZ_SUM_1 = 0;
bool LYZ_SUM_2 = 0;
bool LYZ_SUM_PRODUCT_1 = 0;
bool LYZ_SUM_PRODUCT_2 = 0;
bool SCALARPRODUCT_1 = 1;
bool SCALARPRODUCT_2 = 0;
bool QCUMULANT = 1;
bool HIGHORDERQCUMULANT = 1;
bool LYZEP = 0;

Double_t maxpt = 3.6;   // max pt for differential flow
Double_t minpt = 0.;    // min pt for differential flow
Double_t maxptRF = 3.;  // max pt for reference flow
Double_t minptRF = 0.2; // min pt for reference flow
Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements 
Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
Int_t Nhits_cut = 16;   // minimum nhits of reconstructed tracks
Double_t DCAcut = 0.5;
Double_t pid_probability = 0.9;
Long64_t Nevents = -1;

Int_t debug = 1;

std::string format = "picodst";

void readConfig(const TString& _strFileName)
{
        if (_strFileName.Length() == 0)
        {
                return;
        }

        TEnv env(_strFileName);

        Nhits_cut = env.GetValue("Nhits_cut", 0);

        maxpt = env.GetValue("maxpt", 0.);
        minpt = env.GetValue("minpt", 0.);
        maxptRF = env.GetValue("maxptRF", 0.);
        minptRF = env.GetValue("minptRF", 0.);
        eta_cut = env.GetValue("eta_cut", 0.);
        eta_gap = env.GetValue("eta_gap", 0.);
        DCAcut = env.GetValue("DCAcut", 0.);
        pid_probability = env.GetValue("pid_probability", 0.);

        debug = env.GetValue("debug", 0);
        Nevents = env.GetValue("Nevents", 0);

        format = env.GetValue("format", "");
}

TChain* initChain(const TString &inputFileName, const char* chainName)
{
    TChain *chain = new TChain(chainName);
    std::ifstream file(inputFileName.Data());
    std::string line;
    while(std::getline(file, line))
    {
        chain->Add(line.c_str());
    }

    return chain;
}

// #include "FlowAnalysisWithQCumulant.C"

bool trackCut(PicoDstRecoTrack *recoTrack)
{
    if (!recoTrack)
    {
        return false;
    }

    Double_t pt = recoTrack->GetPt();
    Double_t eta = recoTrack->GetEta();

    if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
        return false;
    if (fabs(recoTrack->GetDCAx()) > DCAcut)
        return false; // DCAx cut
    if (fabs(recoTrack->GetDCAy()) > DCAcut)
        return false; // DCAy cut
    if (fabs(recoTrack->GetDCAz()) > DCAcut)
        return false; // DCAz cut
    if (recoTrack->GetNhits() < Nhits_cut)
        return false; // TPC hits cut    

    return true;                                   
}

Int_t findBin(Double_t pt)
{
    Int_t ipt = -1;
    
    for (Int_t j = 0; j < npt; j++)
    {
        if (pt >= pTBin[j] && pt < pTBin[j + 1])
        ipt = j;
    }
    
    return ipt;
}

Int_t findId(PicoDstRecoTrack *recoTrack)
{
    Int_t fId = -1;

    Double_t charge = recoTrack->GetCharge();
    if (recoTrack->GetTofFlag() != 0 && recoTrack->GetTofFlag() != 4)
    {
        if (recoTrack->GetPidProbPion() > pid_probability && charge > 0)
            fId = 1; // pion+
        if (recoTrack->GetPidProbKaon() > pid_probability && charge > 0)
            fId = 2; // kaon+
        if (recoTrack->GetPidProbProton() > pid_probability && charge > 0)
            fId = 3; // proton
        if (recoTrack->GetPidProbPion() > pid_probability && charge < 0)
            fId = 5; // pion-
        if (recoTrack->GetPidProbKaon() > pid_probability && charge < 0)
            fId = 6; // kaon-
        if (recoTrack->GetPidProbProton() > pid_probability && charge < 0)
            fId = 7; // antiproton
    }

    return fId;
}

void RunFlowAnalysis(TString inputFileName, TString outputFileName, TString configFileName = "")
{
  TStopwatch timer;
  timer.Start();

  if (configFileName.Length() > 0)
  {
    readConfig(configFileName);
  }

  if (debug)
  {
        cout << "Nevents = " << Nevents << endl;
        cout << "Nhits_cut = " << Nhits_cut << endl;

        cout << "maxpt = " << maxpt << endl;
        cout << "minpt = " << minpt << endl;
        cout << "maxptRF = " << maxptRF << endl;
        cout << "minptRF = " << minptRF << endl;
        cout << "eta_cut = " << eta_cut << endl;
        cout << "eta_gap = " << eta_gap << endl;
        cout << "DCAcut = " << DCAcut << endl;
        cout << "pid_probability = " << pid_probability << endl;
        cout << "format = " << format << endl;
  }

  if ((LYZ_SUM_1 && LYZ_SUM_PRODUCT_1) || (LYZ_SUM_2 && LYZ_SUM_PRODUCT_2))
  {
    cerr << "Both LYZ_SUM_1(2) and LYZ_SUM_PRODUCT_1(2) are TRUE. Set one of them to FASLE to run flow analysis." << endl;
    return;
  }

  // Configure input information
  TChain *chain = initChain(inputFileName, format.c_str());

  PicoDstMCEvent *mcEvent = nullptr;

  IReader* reader = nullptr;
  if (format == "picodst")
  {
    reader = new PicoDstReader();
  }
  if (!reader)
  {
    cerr << "No valid format is set!" << endl;
    return;
  }

  reader->Init(chain);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  FlowAnalysisWithEtaSubEventPlane  *flowEtaSub  = NULL; // Eta-sub Event Plane
  FlowAnalysisWithThreeEtaSubEventPlane *flowThreeEtaSub = NULL; // 3-Eta-sub Event Plane
  FlowAnalysisWithFHCalEventPlane   *flowFHCalEP = NULL; // FHCal Event Plane
  FlowAnalysisWithLeeYangZeros      *flowLYZ     = NULL; // Lee Yang Zeros
  FlowAnalysisWithScalarProduct     *flowSP      = NULL; // Scalar Product
  FlowAnalysisWithQCumulant         *flowQC      = NULL; // Q-Cumulant
  FlowAnalysisWithHighOrderQCumulant *flowHighQC = NULL;
  FlowAnalysisWithLeeYangZerosEventPlane *flowLYZEP = NULL;

  if (ETASUBEVENTPLANE_1) {
    flowEtaSub = new FlowAnalysisWithEtaSubEventPlane();
    flowEtaSub->SetFirstRun(true);
    flowEtaSub->SetEtaGap(eta_gap);
    flowEtaSub->Init();
  }
  if (ETASUBEVENTPLANE_2) {
    flowEtaSub = new FlowAnalysisWithEtaSubEventPlane();
    flowEtaSub->SetFirstRun(false);
    flowEtaSub->SetEtaGap(eta_gap);
    flowEtaSub->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowEtaSub->Init();
  }
  if (THREEETASUBEVENTPLANE_1) {
    flowThreeEtaSub = new FlowAnalysisWithThreeEtaSubEventPlane();
    flowThreeEtaSub->SetFirstRun(true);
    flowThreeEtaSub->SetEtaGap(eta_gap);
    flowThreeEtaSub->Init();
  }
  if (THREEETASUBEVENTPLANE_2) {
    flowThreeEtaSub = new FlowAnalysisWithThreeEtaSubEventPlane();
    flowThreeEtaSub->SetFirstRun(false);
    flowThreeEtaSub->SetEtaGap(eta_gap);
    flowThreeEtaSub->SetDebugFlag(debug);
    flowThreeEtaSub->SetInputFileFromFirstRun("FirstRun.root");
    flowThreeEtaSub->Init();
  }
  if (FHCALEVENTPLANE_1) {
    flowFHCalEP = new FlowAnalysisWithFHCalEventPlane();
    flowFHCalEP->SetFirstRun(true);
    flowFHCalEP->SetEtaGap(eta_gap);
    flowFHCalEP->Init();
  }
  if (FHCALEVENTPLANE_2) {
    flowFHCalEP = new FlowAnalysisWithFHCalEventPlane();
    flowFHCalEP->SetFirstRun(false);
    flowFHCalEP->SetEtaGap(eta_gap);
    flowFHCalEP->SetDebugFlag(debug);
    flowFHCalEP->SetInputFileFromFirstRun("FirstRun.root");
    flowFHCalEP->Init();
  }

  if (LYZ_SUM_1) {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    flowLYZ->SetFirstRun(true);
    flowLYZ->Init();
  }
  if (LYZ_SUM_2) {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    // flowLYZ->SetDebugFlag(true);
    flowLYZ->SetFirstRun(false);
    flowLYZ->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowLYZ->Init();
  }

  if (LYZ_SUM_PRODUCT_1) {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    flowLYZ->SetFirstRun(true);
    flowLYZ->SetUseProduct(true);
    flowLYZ->Init();
  }
  if (LYZ_SUM_PRODUCT_2) {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    flowLYZ->SetDebugFlag(debug);
    flowLYZ->SetFirstRun(false);
    flowLYZ->SetUseProduct(true);
    flowLYZ->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowLYZ->Init();
  }
  QVector *Q2 = new QVector(); // for LYZ only, need to be improve to be also feasible to QC.
  // Start event loop
  if (SCALARPRODUCT_1) {
    flowSP = new FlowAnalysisWithScalarProduct();
    flowSP->SetFirstRun(true);
    flowSP->SetEtaGap(eta_gap);
    flowSP->Init();
  }
  if (SCALARPRODUCT_2) {
    flowSP = new FlowAnalysisWithScalarProduct();
    flowSP->SetFirstRun(false);
    flowSP->SetEtaGap(eta_gap);
    flowSP->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowSP->Init();
  }
  if (QCUMULANT) {
    flowQC = new FlowAnalysisWithQCumulant();
    flowQC->SetEtaGap(eta_gap);
    flowQC->Init();
  }

  if (HIGHORDERQCUMULANT) {
    flowHighQC = new FlowAnalysisWithHighOrderQCumulant();
    flowHighQC->Init();
  }
  if (LYZEP) {
    // if (inputHistogramFileName=="" || inputHistFromLYZSecondRun=="")
    // {
    //   cerr << "Input files with needed histograms for Lee Yang Zeros Event Plane aren't set" << endl;
    //   return;
    // }
    flowLYZEP = new FlowAnalysisWithLeeYangZerosEventPlane();
    // flowLYZEP->SetInputFileFromFirstAndSecondRun(inputHistogramFileName, inputHistFromLYZSecondRun);
    flowLYZEP->SetInputFileFromFirstAndSecondRun("FirstRun.root", "SecondRun.root");
    flowLYZEP->Init();
  }
  Double_t pt, eta, phi, charge, energy;
  Long64_t chain_size = chain->GetEntries();
  Long64_t n_entries = (Nevents < chain_size && Nevents > 0) ? Nevents : chain_size;
  cout << "Hi Master, let's do some physics together..." << endl;
  for (Int_t iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    // chain->GetEntry(iEv);
    mcEvent = reader->ReadMcEvent(iEv);
    
    // Read MC event
    Double_t bimp = mcEvent->GetB();
    Double_t cent = CentB(bimp);
    if (cent == -1)
      continue;
    Int_t icent = GetCentBin(cent);
    // Int_t reco_mult = recoTracks->GetEntriesFast();
    Int_t reco_mult = reader->GetRecoTrackSize();
    
    if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->Zero();
    if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->Zero();
    if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->Zero();
    if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2) flowLYZ->Zero();
    if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->Zero();
    Q2->Zero();
    if (QCUMULANT) flowQC->Zero();
    if (HIGHORDERQCUMULANT) flowHighQC->Zero();
    if (LYZEP) flowLYZEP->Zero();
    Int_t Nmodules = reader->GetNFHCalModules();
    if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2 || THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2)
    {
      for (Int_t iModule = 0; iModule < Nmodules; iModule++)
      {
        auto module = (PicoDstFHCal *) reader->ReadFHCalModule(iModule);
        energy = module->GetEnergy();
        phi = GetFHCalPhi(iModule);
        eta = (iModule < 45) ? -3. : 3.; // Left & Right FHCal
        if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->ProcessFirstTrackLoop(eta, phi, energy);
        if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessFirstTrackLoopFHCal(eta, phi, energy);
      }
    }

    for (Int_t iTrk = 0; iTrk < reco_mult; iTrk++)
    { // Track loop

      auto recoTrack = (PicoDstRecoTrack *) reader->ReadRecoTrack(iTrk);
      if (!trackCut(recoTrack))
      {
        continue;
      }
      
      pt = recoTrack->GetPt();
      eta = recoTrack->GetEta();
      phi = recoTrack->GetPhi();
      charge = recoTrack->GetCharge();

      Int_t ipt = findBin(pt);
      Int_t fId = findId(recoTrack);

      if (pt > minptRF && pt < maxptRF)
      { // Reference Flow pt cut
        // 2,4-QC

        if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->ProcessFirstTrackLoop(eta, phi, pt);
        if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessFirstTrackLoopTPC(eta, phi, pt);
        if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->ProcessFirstTrackLoop(eta, phi);
        if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2) flowLYZ->ProcessFirstTrackLoop(phi, pt, icent);
        Q2->CalQVector(phi, 1.);
        if (QCUMULANT) flowQC->ProcessFirstTrackLoopRP(eta, phi);
        if (HIGHORDERQCUMULANT) flowHighQC->ProcessFirstTrackLoopRP(phi);
      }

      if (QCUMULANT) flowQC->ProcessFirstTrackLoopPOI(ipt, eta, phi, fId, charge);
    } // end of track loop

    if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->ProcessEventAfterFirstTrackLoop(cent);
    if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessEventAfterFirstTrackLoop(cent);    
    if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->ProcessEventAfterFirstTrackLoop(cent);
    if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->ProcessEventAfterFirstTrackLoop(cent);
    if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2) flowLYZ->ProcessEventAfterFirstTrackLoop(Q2, icent);
    if (QCUMULANT) flowQC->ProcessEventAfterFirstTrackLoop(icent);
    if (HIGHORDERQCUMULANT) flowHighQC->ProcessEventAfterFirstTrackLoop(icent);
    if (LYZEP) flowLYZEP->ProcessEventAfterFirstTrackLoop(Q2, icent);
    if (ETASUBEVENTPLANE_2 || FHCALEVENTPLANE_2 || THREEETASUBEVENTPLANE_2 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_2 || SCALARPRODUCT_2 || LYZEP)
    {
      for (Int_t iTrk = 0; iTrk < reco_mult; iTrk++)
      { // 2nd Track loop
        auto recoTrack = (PicoDstRecoTrack *) reader->ReadRecoTrack(iTrk);
        if (!trackCut(recoTrack))
        {
          continue;
        }

        pt = recoTrack->GetPt();
        eta = recoTrack->GetEta();
        phi = recoTrack->GetPhi();
        charge = recoTrack->GetCharge();

        if (ETASUBEVENTPLANE_2) flowEtaSub->ProcessSecondTrackLoop(eta, phi, pt, cent);
        if (THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessSecondTrackLoop(eta, phi, pt, cent);
        if (FHCALEVENTPLANE_2) flowFHCalEP->ProcessSecondTrackLoop(eta, phi, pt, cent);
        if (SCALARPRODUCT_2) flowSP->ProcessSecondTrackLoop(eta, phi, pt, cent);
        if (LYZ_SUM_2 || LYZ_SUM_PRODUCT_2) flowLYZ->ProcessSecondTrackLoop(phi, pt, icent);
        if (LYZEP) flowLYZEP->ProcessSecondTrackLoop(eta, phi, pt, cent);
      }
    }

  } // end event loop

  // Writing output
  fo->cd();
  // fo->Write();

  if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->SaveHist();
  if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->SaveHist();
  if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->SaveHist();
  if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->SaveHist();
  if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2) flowLYZ->SaveHist();
  if (QCUMULANT) flowQC->SaveHist();
  if (HIGHORDERQCUMULANT) flowHighQC->SaveHist();
  if (LYZEP) flowLYZEP->SaveHist();
  fo->Close();

  timer.Stop();
  timer.Print();
}