// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TDirectoryFile.h>
#include <TMath.h>
#include <TF2.h>
#include <TDatabasePDG.h>
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
#include <McPicoReader.h>
// Flow method headers
#include <QVector.h>
#include <FlowAnalysisWithEtaSubEventPlane.h>
#include <FlowAnalysisWithThreeEtaSubEventPlane.h>
#include <FlowAnalysisWithFHCalEventPlane.h>
#include <FlowAnalysisWithLeeYangZeros.h>
#include <FlowAnalysisWithScalarProduct.h>
#include <FlowAnalysisWithQCumulant.h>
#include <FlowAnalysisWithHighOrderQCumulant.h>
#include <FlowAnalysisWithLeeYangZerosEventPlane.h>
#include <FlowAnalysisWithMCEventPlane.h>

#include "utilities.C"

using std::cout;
using std::cerr;
using std::endl;
// Flags for flow methods, where *_1 is the first run over the data and *_2 is the second run (need to move these flags to config file!!)
Bool_t ETASUBEVENTPLANE_1 = 1;        // Eta-sub EP (first run)
Bool_t ETASUBEVENTPLANE_2 = 0;        // Eta-sub EP (second run)
Bool_t THREEETASUBEVENTPLANE_1 = 0;   // 3 eta-sub method (first run)
Bool_t THREEETASUBEVENTPLANE_2 = 0;   // 3 eta-sub method (second run)
Bool_t FHCALEVENTPLANE_1 = 0;         // FHCal EP (w.r.t. 1-st order harmonic) (first run)
Bool_t FHCALEVENTPLANE_2 = 0;         // FHCal EP (w.r.t. 1-st order harmonic) (second run)
Bool_t LYZ_SUM_1 = 0;                 // Lee-Yang Zeros using sum generating function (first run)
Bool_t LYZ_SUM_2 = 0;                 // Lee-Yang Zeros using sum generating function (second run)
Bool_t LYZ_PRODUCT_1 = 0;             // Lee-Yang Zeros using product generating function (first run) (integrated with sum GF at the moment, will be separated soon)
Bool_t LYZ_PRODUCT_2 = 0;             // Lee-Yang Zeros using product generating function (second run) (integrated with sum GF at the moment, will be separated soon)
Bool_t SCALARPRODUCT_1 = 1;           // Scalar product using eta-sub method (first run)
Bool_t SCALARPRODUCT_2 = 0;           // Scalar product using eta-sub method (second run)
Bool_t QCUMULANT = 1;                 // Q-Cumulants: 2- and 4-particle cumulants obtained by both standard and subevent methods 
Bool_t HIGHORDERQCUMULANT = 0;        // Q-Cumulants: 2- up to 8-particle cumulants using recursive algorithm
Bool_t LYZEP = 0;                     // one needs to run LYZ_SUM_1 & 2 before set this flag to kTRUE
Bool_t MCEP = 1;                      // MC Event Plane
Bool_t readMCTracks = 0; // 0 - read reco tracks, 1 - read MC tracks
Int_t harmonic = 2; // set harmonic for eta-sub event plane, Q-Cumulants, and scalar product method
Bool_t bMotherIDcut = 1;
// Kinetic cuts by default if not using config file
Double_t maxpt = 3.0;     // max pt for differential flow
Double_t minpt = 0.;      // min pt for differential flow
Double_t maxptRF = 3.;    // max pt for reference flow
Double_t minptRF = 0.2;   // min pt for reference flow
Double_t eta_cut = 1.5;   // pseudorapidity acceptance window for flow measurements 
Double_t eta_gap = 0.05;  // +-0.05, eta-gap between 2 eta sub-event
Int_t Nhits_cut = 16;     // minimum nhits of reconstructed tracks
Double_t DCAcut = 2.0;    // 3*sigma of DCA distribution 
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

  ETASUBEVENTPLANE_1 = env.GetValue("ETASUBEVENTPLANE_1", 0);
  ETASUBEVENTPLANE_2 = env.GetValue("ETASUBEVENTPLANE_2", 0);
  THREEETASUBEVENTPLANE_1 = env.GetValue("THREEETASUBEVENTPLANE_1", 0);
  THREEETASUBEVENTPLANE_2 = env.GetValue("THREEETASUBEVENTPLANE_2", 0);
  FHCALEVENTPLANE_1 = env.GetValue("FHCALEVENTPLANE_1", 0);
  FHCALEVENTPLANE_2 = env.GetValue("FHCALEVENTPLANE_2", 0);
  LYZ_SUM_1 = env.GetValue("LYZ_SUM_1", 0);
  LYZ_SUM_2 = env.GetValue("LYZ_SUM_2", 0);
  LYZ_PRODUCT_1 = env.GetValue("LYZ_PRODUCT_1", 0);
  LYZ_PRODUCT_2 = env.GetValue("LYZ_PRODUCT_2", 0);
  SCALARPRODUCT_1 = env.GetValue("SCALARPRODUCT_1", 0);
  SCALARPRODUCT_2 = env.GetValue("SCALARPRODUCT_2", 0);
  QCUMULANT = env.GetValue("QCUMULANT", 0);
  HIGHORDERQCUMULANT = env.GetValue("HIGHORDERQCUMULANT", 0);
  LYZEP = env.GetValue("LYZEP", 0);
  MCEP = env.GetValue("MCEP", 0);
  
  readMCTracks = env.GetValue("readMCTracks", 0);
  harmonic = env.GetValue("harmonic", 0);
  bMotherIDcut = env.GetValue("bMotherIDcut", 0);

}

Bool_t trackCut(PicoDstRecoTrack *const &recoTrack, TF2 *const &fDCAx, TF2 *const &fDCAy, TF2 *const &fDCAz)
{
  if (!recoTrack) { return false; }
  Double_t pt = recoTrack->GetPt();
  Double_t eta = recoTrack->GetEta();
  if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)     return false;
  // if (fabs(recoTrack->GetDCAx()) > DCAcut)        return false; // static DCAx cut
  // if (fabs(recoTrack->GetDCAy()) > DCAcut)        return false; // static DCAy cut
  // if (fabs(recoTrack->GetDCAz()) > DCAcut)        return false; // static DCAz cut
  if (recoTrack->GetNhits() < Nhits_cut)          return false; // TPC hits cut    
  if (fabs(recoTrack->GetDCAx()) > fDCAx->Eval(recoTrack->GetPt(),recoTrack->GetEta())*DCAcut) return false; // DCAx cut
  if (fabs(recoTrack->GetDCAy()) > fDCAy->Eval(recoTrack->GetPt(),recoTrack->GetEta())*DCAcut) return false; // DCAy cut
  if (fabs(recoTrack->GetDCAz()) > fDCAz->Eval(recoTrack->GetPt(),recoTrack->GetEta())*DCAcut) return false; // DCAz cut
  return true;                                   
}

Bool_t trackCut(PicoDstMCTrack *const &mcTrack)
{
  if (!mcTrack) { return false; }
  if (format == "picodst" && mcTrack->GetMotherId() != -1) { return false; }
  Double_t pt = mcTrack->GetPt();
  Double_t eta = mcTrack->GetEta();
  auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
  if (!particle) { return false; }
  Double_t charge = 1./3.*particle->Charge();
  if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut || charge == 0) { return false; }
  return true;
}

Bool_t trackCutMotherID(PicoDstRecoTrack *const &recoTrack, PicoDstMCTrack *const &mcTrack)
{
  if (!recoTrack) { return false; }
  if (!mcTrack) { return false; }
  if (mcTrack->GetMotherId() != -1) { return false; }
  Double_t pt = recoTrack->GetPt();
  Double_t eta = recoTrack->GetEta();
  if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)     return false;
  if (recoTrack->GetNhits() < Nhits_cut)                   return false; // TPC hits cut    
  return true;                                   
}

Int_t findBin(const Double_t &pt)
{
  Int_t ipt = -1;
  for (Int_t j = 0; j < npt; j++) { if (pt >= pTBin[j] && pt < pTBin[j + 1]) ipt = j; }
  return ipt;
}

Int_t findId(const PicoDstRecoTrack *const &recoTrack)
{
  Int_t fId = -1;

  Double_t charge = recoTrack->GetCharge();
  if (recoTrack->GetTofFlag() != 0 && recoTrack->GetTofFlag() != 4)
  {
    if (recoTrack->GetPidProbPion() > pid_probability && charge > 0)   fId = 1;  // pion+
    if (recoTrack->GetPidProbKaon() > pid_probability && charge > 0)   fId = 2;  // kaon+
    if (recoTrack->GetPidProbProton() > pid_probability && charge > 0) fId = 3;  // proton
    if (recoTrack->GetPidProbPion() > pid_probability && charge < 0)   fId = 5;  // pion-
    if (recoTrack->GetPidProbKaon() > pid_probability && charge < 0)   fId = 6;  // kaon-
    if (recoTrack->GetPidProbProton() > pid_probability && charge < 0) fId = 7;  // antiproton
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

    cout << "ETASUBEVENTPLANE_1 = " << ETASUBEVENTPLANE_1 << endl;
    cout << "ETASUBEVENTPLANE_2 = " << ETASUBEVENTPLANE_2 << endl;
    cout << "THREEETASUBEVENTPLANE_1 = " << THREEETASUBEVENTPLANE_1 << endl;
    cout << "THREEETASUBEVENTPLANE_2 = " << THREEETASUBEVENTPLANE_2 << endl;
    cout << "FHCALEVENTPLANE_1 = " << FHCALEVENTPLANE_1 << endl;
    cout << "FHCALEVENTPLANE_2 = " << FHCALEVENTPLANE_2 << endl;
    cout << "LYZ_SUM_1 = " << LYZ_SUM_1 << endl;
    cout << "LYZ_SUM_2 = " << LYZ_SUM_2 << endl;
    cout << "LYZ_PRODUCT_1 = " << LYZ_PRODUCT_1 << endl;
    cout << "LYZ_PRODUCT_2 = " << LYZ_PRODUCT_2 << endl;
    cout << "SCALARPRODUCT_1 = " << SCALARPRODUCT_1 << endl;
    cout << "SCALARPRODUCT_2 = " << SCALARPRODUCT_2 << endl;
    cout << "QCUMULANT = " << QCUMULANT << endl;
    cout << "HIGHORDERQCUMULANT = " << HIGHORDERQCUMULANT << endl;
    cout << "LYZEP = " << LYZEP << endl;
    cout << "MCEP = " << MCEP << endl;
    cout << "readMCTracks = " << readMCTracks << endl;
    cout << "harmonic = " << harmonic << endl;       
    cout << "readMCTracks = " << readMCTracks << endl;
    cout << "harmonic = " << harmonic << endl;
    cout << "bMotherIDcut = " << bMotherIDcut << endl;
  }

  // Configure input information
  TChain *chain = initChain(inputFileName, format.c_str());

  PicoDstMCEvent *mcEvent = nullptr;

  IReader* reader = nullptr;
  if (format == "picodst")
  {
    reader = new PicoDstReader();
  }
  if (format == "mctree")
  {
    reader = new McPicoReader();
    readMCTracks = true;
  }
  if (!reader)
  {
    cerr << "No valid format is set!" << endl;
    return;
  }

  TFile *inputDCAfile;
  TF2 *fDCAx, *fDCAy, *fDCAz;
  if (!readMCTracks && !bMotherIDcut)
  { // using DCA cuts for primary track cut
    inputDCAfile = new TFile("DCA_FIT.root","read");
    if (!inputDCAfile) 
    {
      cerr << "Cannot find DCA_FIT.root file for DCA cut. Make sure you have run the DCA correction procedure and placed DCA_FIT.root in the executable directory." << endl;
      return;
    }
    fDCAx = dynamic_cast<TF2*> (inputDCAfile->Get("f_sigma0"));
    fDCAy = dynamic_cast<TF2*> (inputDCAfile->Get("f_sigma1"));
    fDCAz = dynamic_cast<TF2*> (inputDCAfile->Get("f_sigma2"));
    if (!fDCAx || !fDCAy || !fDCAz) { cerr << "Cannot find fit function for DCA primary track cuts!" << endl; return; }
    else{ cout << "Using " << DCAcut <<" sigma of DCA distr. cut." << endl; }
  }
  reader->Init(chain);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(), "recreate");
  
  FlowAnalysisWithEtaSubEventPlane       *flowEtaSub      = nullptr; // Eta-sub Event Plane
  FlowAnalysisWithThreeEtaSubEventPlane  *flowThreeEtaSub = nullptr; // 3-Eta-sub Event Plane
  FlowAnalysisWithFHCalEventPlane        *flowFHCalEP     = nullptr; // FHCal Event Plane w.r.t 1-st harmonic
  FlowAnalysisWithLeeYangZeros           *flowLYZSUM      = nullptr; // Lee-Yang Zeros using sum generating function
  FlowAnalysisWithLeeYangZeros           *flowLYZPROD     = nullptr; // Lee-Yang Zeros using product generating function
  FlowAnalysisWithScalarProduct          *flowSP          = nullptr; // Scalar Product
  FlowAnalysisWithQCumulant              *flowQC          = nullptr; // Q-Cumulant
  FlowAnalysisWithHighOrderQCumulant     *flowHighQC      = nullptr; // 2- to 8-particle correlations using recursive algorithm
  FlowAnalysisWithLeeYangZerosEventPlane *flowLYZEP       = nullptr; // Lee-Yang Zeros Event Plane
  FlowAnalysisWithMCEventPlane           *flowMCEP        = nullptr; // MC Event Plane

  if (ETASUBEVENTPLANE_1) {
    flowEtaSub = new FlowAnalysisWithEtaSubEventPlane();
    flowEtaSub->SetFirstRun(true);
    flowEtaSub->SetHarmonic(harmonic);
    flowEtaSub->SetEtaGap(eta_gap);
    flowEtaSub->Init();
  }
  if (ETASUBEVENTPLANE_2) {
    flowEtaSub = new FlowAnalysisWithEtaSubEventPlane();
    flowEtaSub->SetFirstRun(false);
    flowEtaSub->SetHarmonic(harmonic);
    flowEtaSub->SetEtaGap(eta_gap);
    flowEtaSub->SetDebugFlag(debug);
    flowEtaSub->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowEtaSub->Init();
  }
  if (THREEETASUBEVENTPLANE_1) {
    flowThreeEtaSub = new FlowAnalysisWithThreeEtaSubEventPlane();
    flowThreeEtaSub->SetFirstRun(true);
    flowThreeEtaSub->SetHarmonic(harmonic);
    flowThreeEtaSub->SetEtaGap(eta_gap);
    flowThreeEtaSub->Init();
  }
  if (THREEETASUBEVENTPLANE_2) {
    flowThreeEtaSub = new FlowAnalysisWithThreeEtaSubEventPlane();
    flowThreeEtaSub->SetFirstRun(false);
    flowThreeEtaSub->SetHarmonic(harmonic);
    flowThreeEtaSub->SetEtaGap(eta_gap);
    flowThreeEtaSub->SetDebugFlag(debug);
    flowThreeEtaSub->SetInputFileFromFirstRun("FirstRun.root");
    flowThreeEtaSub->Init();
  }
  if (FHCALEVENTPLANE_1) {
    flowFHCalEP = new FlowAnalysisWithFHCalEventPlane();
    flowFHCalEP->SetFirstRun(true);
    flowFHCalEP->SetHarmonic(harmonic);
    flowFHCalEP->SetEtaGap(eta_gap);
    flowFHCalEP->Init();
  }
  if (FHCALEVENTPLANE_2) {
    flowFHCalEP = new FlowAnalysisWithFHCalEventPlane();
    flowFHCalEP->SetFirstRun(false);
    flowFHCalEP->SetHarmonic(harmonic);
    flowFHCalEP->SetEtaGap(eta_gap);
    flowFHCalEP->SetDebugFlag(debug);
    flowFHCalEP->SetInputFileFromFirstRun("FirstRun.root");
    flowFHCalEP->Init();
  }

  if (LYZ_SUM_1) {
    flowLYZSUM = new FlowAnalysisWithLeeYangZeros();
    flowLYZSUM->SetDebugFlag(debug);
    flowLYZSUM->SetHarmonic(harmonic);
    flowLYZSUM->SetUseProduct(false);
    flowLYZSUM->SetFirstRun(true);
    // flowLYZSUM->SetUseMultiplicityWeight(false); // true by default
    flowLYZSUM->Init();
  }
  if (LYZ_SUM_2) {
    flowLYZSUM = new FlowAnalysisWithLeeYangZeros();
    flowLYZSUM->SetDebugFlag(debug);
    flowLYZSUM->SetHarmonic(harmonic);
    flowLYZSUM->SetUseProduct(false);
    flowLYZSUM->SetFirstRun(false);
    // flowLYZSUM->SetUseMultiplicityWeight(false); // true by default
    flowLYZSUM->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowLYZSUM->Init();
  }

  if (LYZ_PRODUCT_1) {
    flowLYZPROD = new FlowAnalysisWithLeeYangZeros();
    flowLYZPROD->SetDebugFlag(debug);
    flowLYZPROD->SetHarmonic(harmonic);
    flowLYZPROD->SetUseProduct(true);
    flowLYZPROD->SetFirstRun(true);
    // flowLYZPROD->SetUseMultiplicityWeight(false); // true by default
    flowLYZPROD->Init();
  }
  if (LYZ_PRODUCT_2) {
    flowLYZPROD = new FlowAnalysisWithLeeYangZeros();
    flowLYZPROD->SetDebugFlag(debug);
    flowLYZPROD->SetHarmonic(harmonic);
    flowLYZPROD->SetUseProduct(true);
    flowLYZPROD->SetFirstRun(false);
    // flowLYZPROD->SetUseMultiplicityWeight(false); // true by default
    flowLYZPROD->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowLYZPROD->Init();
  }
  if (SCALARPRODUCT_1) {
    flowSP = new FlowAnalysisWithScalarProduct();
    flowSP->SetFirstRun(true);
    flowSP->SetHarmonic(harmonic);
    flowSP->SetEtaGap(eta_gap);
    flowSP->Init();
  }
  if (SCALARPRODUCT_2) {
    flowSP = new FlowAnalysisWithScalarProduct();
    flowSP->SetFirstRun(false);
    flowSP->SetHarmonic(harmonic);
    flowSP->SetEtaGap(eta_gap);
    flowSP->SetInputFileFromFirstRun("FirstRun.root"); // need to be improve!!!
    flowSP->Init();
  }
  if (QCUMULANT) {
    flowQC = new FlowAnalysisWithQCumulant();
    flowQC->SetHarmonic(harmonic);
    flowQC->SetEtaGap(eta_gap);
    flowQC->Init();
  }
  if (HIGHORDERQCUMULANT) {
    flowHighQC = new FlowAnalysisWithHighOrderQCumulant();
    flowHighQC->Init();
  }
  if (LYZEP) {
    flowLYZEP = new FlowAnalysisWithLeeYangZerosEventPlane();
    flowLYZEP->SetInputFileFromFirstAndSecondRun("FirstRun.root", "SecondRun.root");
    flowLYZEP->Init();
  }
  if (MCEP) {
    flowMCEP = new FlowAnalysisWithMCEventPlane();
    flowMCEP->SetDebugFlag(debug);
    flowMCEP->SetHarmonic(harmonic);
    // flowMCEP->SetEtaGap(eta_gap);
    flowMCEP->SetEtaGap(0.);
    flowMCEP->Init();
  }

  Int_t icent, mult, ipt, fId;
  Double_t bimp, cent, pt, eta, phi, charge, energy;
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
    bimp = mcEvent->GetB();
    cent = CentB(bimp);
    if (cent == -1)
      continue;
    icent = GetCentBin(cent);
    
    if (readMCTracks) mult = reader->GetMcTrackSize();
    else mult = reader->GetRecoTrackSize();

    if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2)           flowEtaSub->Zero();
    if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->Zero();
    if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2)             flowFHCalEP->Zero();
    if (LYZ_SUM_1 || LYZ_SUM_2)                             flowLYZSUM->Zero();
    if (LYZ_PRODUCT_1 || LYZ_PRODUCT_2)                     flowLYZPROD->Zero();
    if (SCALARPRODUCT_1 || SCALARPRODUCT_2)                 flowSP->Zero();
    if (QCUMULANT)                                          flowQC->Zero();
    if (HIGHORDERQCUMULANT)                                 flowHighQC->Zero();
    if (LYZEP)                                              flowLYZEP->Zero();
    if (MCEP)                                             { flowMCEP->Zero(); flowMCEP->SetPsiRP(mcEvent->GetPhiRP()); }

    if ((FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2 || THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) && !readMCTracks)
    {
      Int_t Nmodules = reader->GetNFHCalModules();
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
    if ( (LYZ_PRODUCT_1 || LYZ_PRODUCT_2) && flowLYZPROD->GetUseMultiplicityWeight() )
    { // Zero Track loop for Product LYZ
      for (Int_t iTrk = 0; iTrk < mult; iTrk++)
      {
        if (readMCTracks)
        {
          auto mcTrack = (PicoDstMCTrack *) reader->ReadMcTrack(iTrk);
          if (!trackCut(mcTrack)) { continue; } // TPC cut
          pt = mcTrack->GetPt();
        }
        else
        { // Read reco tracks
          auto recoTrack = (PicoDstRecoTrack *) reader->ReadRecoTrack(iTrk);
          auto mcTrack = (PicoDstMCTrack *) reader->ReadMcTrack(recoTrack->GetMcId());
          if (bMotherIDcut) { if (!trackCutMotherID(recoTrack, mcTrack)) { continue; } }
          else { if (!trackCut(recoTrack,fDCAx,fDCAy,fDCAz)) { continue; } }
          pt = recoTrack->GetPt();
        }
        if (pt > minptRF && pt < maxptRF)
        {
          flowLYZPROD->ProcessZeroTrackLoopRP();
        }
      }
    }
    for (Int_t iTrk = 0; iTrk < mult; iTrk++)
    { // First Track loop
      if (readMCTracks)
      {
        auto mcTrack = (PicoDstMCTrack *) reader->ReadMcTrack(iTrk);
        
        if (!mcTrack) { cout << "skip mcTrack" << endl; continue;}
        pt = mcTrack->GetPt();
        eta = mcTrack->GetEta();
        phi = mcTrack->GetPhi();
        if ((FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2 || THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) && readMCTracks)
        {
          if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->ProcessFirstTrackLoop(eta, phi, 1.);
          if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessFirstTrackLoopFHCal(eta, phi, 1.);
        }
        if (!trackCut(mcTrack)) { continue; } // TPC cut
        auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());   
        charge = 1./3.*particle->Charge();
        fId = findId(mcTrack);
      }
      else
      { // Read reco tracks
        auto recoTrack = (PicoDstRecoTrack *) reader->ReadRecoTrack(iTrk);
        auto mcTrack = (PicoDstMCTrack *) reader->ReadMcTrack(recoTrack->GetMcId());
        if (bMotherIDcut) { if (!trackCutMotherID(recoTrack, mcTrack)) { continue; } }
        else { if (!trackCut(recoTrack,fDCAx,fDCAy,fDCAz)) { continue; } }
        pt = recoTrack->GetPt();
        eta = recoTrack->GetEta();
        phi = recoTrack->GetPhi();
        charge = recoTrack->GetCharge();
        if (bMotherIDcut) { fId = findId(mcTrack); }
        else { fId = findId(recoTrack); }
      }
      ipt = findBin(pt);
      if (pt > minptRF && pt < maxptRF)
      { // Reference Flow pt cut
        if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->ProcessFirstTrackLoop(eta, phi, pt);
        if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessFirstTrackLoopTPC(eta, phi, pt);
        if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->ProcessFirstTrackLoop(eta, phi, pt);
        if (LYZ_SUM_1 || LYZ_SUM_2) flowLYZSUM->ProcessFirstTrackLoopRP(phi, pt, icent);
        if (LYZ_PRODUCT_1 || LYZ_PRODUCT_2) flowLYZPROD->ProcessFirstTrackLoopRP(phi, pt, icent);
        if (QCUMULANT) flowQC->ProcessFirstTrackLoopRP(eta, phi);
        if (HIGHORDERQCUMULANT) flowHighQC->ProcessFirstTrackLoopRP(phi);
        if (MCEP) flowMCEP->ProcessFirstTrackLoop(eta, phi, 1.);
      }

      if (QCUMULANT) flowQC->ProcessFirstTrackLoopPOI(ipt, eta, phi, fId, charge);
      if (LYZ_SUM_1 || LYZ_SUM_2) flowLYZSUM->ProcessFirstTrackLoopPOI(pt);
      if (LYZ_PRODUCT_1 || LYZ_PRODUCT_2) flowLYZPROD->ProcessFirstTrackLoopPOI(pt);
    } // end of First Track loop
    
    if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->ProcessEventAfterFirstTrackLoop(cent);
    if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessEventAfterFirstTrackLoop(cent);    
    if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->ProcessEventAfterFirstTrackLoop(cent);
    if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->ProcessEventAfterFirstTrackLoop(cent);
    if (LYZ_SUM_1 || LYZ_SUM_2) flowLYZSUM->ProcessEventAfterFirstTrackLoop(icent);
    if (LYZ_PRODUCT_1 || LYZ_PRODUCT_2) flowLYZPROD->ProcessEventAfterFirstTrackLoop(icent);
    if (QCUMULANT) flowQC->ProcessEventAfterFirstTrackLoop(icent);
    if (HIGHORDERQCUMULANT) flowHighQC->ProcessEventAfterFirstTrackLoop(icent);
    if (LYZEP) flowLYZEP->ProcessEventAfterFirstTrackLoop(icent);
    if (MCEP) flowMCEP->ProcessEventAfterFirstTrackLoop(cent);
    if (ETASUBEVENTPLANE_2 || FHCALEVENTPLANE_2 || THREEETASUBEVENTPLANE_2 || LYZ_SUM_2 || LYZ_PRODUCT_2 || SCALARPRODUCT_2 || LYZEP || MCEP)
    {
      for (Int_t iTrk = 0; iTrk < mult; iTrk++)
      { // 2nd Track loop
        if (readMCTracks)
        {
          auto mcTrack = (PicoDstMCTrack *) reader->ReadMcTrack(iTrk);
          if (!trackCut(mcTrack)) { continue; }
          pt = mcTrack->GetPt();
          eta = mcTrack->GetEta();
          phi = mcTrack->GetPhi();
          auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());   
          charge = 1./3.*particle->Charge();
          fId = findId(mcTrack);
        }
        else 
        { // Read reco tracks
          auto recoTrack = (PicoDstRecoTrack *) reader->ReadRecoTrack(iTrk);
          auto mcTrack = (PicoDstMCTrack *) reader->ReadMcTrack(recoTrack->GetMcId());
          if (bMotherIDcut) { if (!trackCutMotherID(recoTrack, mcTrack)) { continue; } }
          else { if (!trackCut(recoTrack,fDCAx,fDCAy,fDCAz)) { continue; } }
          pt = recoTrack->GetPt();
          eta = recoTrack->GetEta();
          phi = recoTrack->GetPhi();
          charge = recoTrack->GetCharge();
          if (bMotherIDcut) { fId = findId(mcTrack); }
          else { fId = findId(recoTrack); }
        }
        if (ETASUBEVENTPLANE_2) flowEtaSub->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
        if (THREEETASUBEVENTPLANE_2) flowThreeEtaSub->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
        if (FHCALEVENTPLANE_2) flowFHCalEP->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
        if (SCALARPRODUCT_2) flowSP->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
        if (LYZ_SUM_2) flowLYZSUM->ProcessSecondTrackLoop(phi, pt, icent);
        if (LYZ_PRODUCT_2) flowLYZPROD->ProcessSecondTrackLoop(phi, pt, icent);
        if (LYZEP) flowLYZEP->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
        if (MCEP) flowMCEP->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
      } // end of 2nd Track loop
    }
    
  } // end event loop
  
  // Writing output
  const Int_t nMethods = 10;
  TString dirNameMethod[nMethods] = {"ETASUBEP","ETA3SUBEP","FHCALEP","SP","LYZSUM","LYZPROD","QC","HQC","LYZEP","MCEP"};
  fo->cd();
  TDirectoryFile *dirFileFinal[nMethods] = {nullptr};
  for(Int_t i=0;i<nMethods;i++)
  {
    dirFileFinal[i] = new TDirectoryFile(dirNameMethod[i].Data(),dirNameMethod[i].Data());
  }
  // if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2) flowEtaSub->SaveHist();
  // if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->SaveHist();
  // if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2) flowFHCalEP->SaveHist();
  // if (SCALARPRODUCT_1 || SCALARPRODUCT_2) flowSP->SaveHist();
  // if (LYZ_SUM_1 || LYZ_SUM_2) flowLYZSUM->SaveHist();
  // if (LYZ_PRODUCT_1 || LYZ_PRODUCT_2) flowLYZPROD->SaveHist();
  // if (QCUMULANT) flowQC->SaveHist();
  // if (HIGHORDERQCUMULANT) flowHighQC->SaveHist();
  // if (LYZEP) flowLYZEP->SaveHist();

  if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2)           flowEtaSub->SaveHist(dirFileFinal[0]);
  if (THREEETASUBEVENTPLANE_1 || THREEETASUBEVENTPLANE_2) flowThreeEtaSub->SaveHist(dirFileFinal[1]);
  if (FHCALEVENTPLANE_1 || FHCALEVENTPLANE_2)             flowFHCalEP->SaveHist(dirFileFinal[2]);
  if (SCALARPRODUCT_1 || SCALARPRODUCT_2)                 flowSP->SaveHist(dirFileFinal[3]);
  if (LYZ_SUM_1 || LYZ_SUM_2)                             flowLYZSUM->SaveHist(dirFileFinal[4]);
  if (LYZ_PRODUCT_1 || LYZ_PRODUCT_2)                     flowLYZPROD->SaveHist(dirFileFinal[5]);
  if (QCUMULANT)                                          flowQC->SaveHist(dirFileFinal[6]);
  if (HIGHORDERQCUMULANT)                                 flowHighQC->SaveHist(dirFileFinal[7]);
  if (LYZEP)                                              flowLYZEP->SaveHist(dirFileFinal[8]);
  if (MCEP)                                               flowMCEP->SaveHist(dirFileFinal[9]);
  
  fo->Close();

  timer.Stop();
  timer.Print();
}

int main(int argc, char **argv)
{
  TString iFileName, oFileName, configFileName = "";

  if (argc < 5)
  {
    std::cerr << "./FlowQCumulant -i INPUT -o OUTPUT [OPTIONAL: -config qcumulant.cfg]" << std::endl;
    return 1;
  }
  for (Int_t i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" &&
        std::string(argv[i]) != "-config")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 3;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 4;
      }
      if (std::string(argv[i]) == "-config" && i != argc - 1)
      {
        configFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-config" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
    }
  }
  RunFlowAnalysis(iFileName, oFileName, configFileName);

  return 0;
}