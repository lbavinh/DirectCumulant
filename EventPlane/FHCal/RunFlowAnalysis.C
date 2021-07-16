// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TString.h>
// #include "TROOT.h"
// R__LOAD_LIBRARY(libMathMore.so);
#include <Math/SpecFuncMathMore.h>

#include "constants.C"
#include "utilities.C"

using std::cerr;
using std::cout;
using std::endl;


class QVector
{
public:
  QVector();
  QVector(Double_t n);
  virtual ~QVector();
  void Zero();
  void CalQVector(const Double_t &phi, const Double_t &weight);
  void WeightQVector();
  Double_t X() const { return this->fQx; }
  Double_t Y() const { return this->fQy; }
  Int_t GetMult() const { return this->fMult; }

private:
  Double_t fNHarmonic;
  Double_t fQx;
  Double_t fQy;
  Double_t fWeight;
  Int_t fMult;
  // ClassDef(QVector,0);
};

// ClassImp(QVector);
QVector::QVector() : fNHarmonic(2), fQx(0), fQy(0), fWeight(0), fMult(0) {}
QVector::QVector(Double_t n) : fNHarmonic(n), fQx(0), fQy(0), fWeight(0), fMult(0) {}
QVector::~QVector() {}

void QVector::Zero()
{
  fQx = 0.;
  fQy = 0.;
  fMult = 0;
  fWeight = 0.;
}

void QVector::CalQVector(const Double_t &phi, const Double_t &weight)
{
  fQx += weight * TMath::Cos( fNHarmonic * phi );
  fQy += weight * TMath::Sin( fNHarmonic * phi );
  fWeight += weight;
  fMult++;
}

void QVector::WeightQVector()
{
  if (fMult == 0) { cout << "Warning! fMult==0!" << endl;}
  if (fMult != 0)
  {
    if (fWeight<0) fWeight *= -1.;
    fQx /= fWeight;
    fQy /= fWeight;
  }
  
}

class FlowAnalysisWithFHCalEventPlane
{
public:
  FlowAnalysisWithFHCalEventPlane();
  virtual ~FlowAnalysisWithFHCalEventPlane();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight);
  void ProcessEventAfterFirstTrackLoop(const Double_t &dCent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge);
  void SetFirstRun(Bool_t kt) { this->fFirstRun = kt; }
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SetDebugFlag(Bool_t kt) { this->fDebug = kt; }
  void SetHarmonic(Int_t i) { this->fHarmonic = i; }
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void GetRes();
  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);
  Double_t Res(Double_t chi, Double_t harmonic);
  Double_t GetChi(Double_t _res, Double_t _harm, Int_t accuracy);
private:
  Bool_t fFirstRun;
  Bool_t fMultCut;      // event multiplicity cut (if multiplicity < fMultCut then skip event)
  Bool_t fDebug;
  Int_t fHarmonic;
  Double_t fEtaGap;
  Double_t fPsi_L;
  Double_t fPsi_R;
  Double_t fPsi;
  QVector *fQvector_L;
  QVector *fQvector_R;
  Double_t fRes2[ncent];
  TString fstrInputFileFromFirstRun;
  TProfile *fPrRes;
  TProfile2D *fPrV2vsPt[npid];
  TProfile2D *fPrV2vsEta;
  TProfile3D *fPrV2FHCalEventPlane;
  // ClassDef(FlowAnalysisWithFHCalEventPlane,0);

};

// ClassImp(FlowAnalysisWithFHCalEventPlane);
FlowAnalysisWithFHCalEventPlane::FlowAnalysisWithFHCalEventPlane() :
  fFirstRun(kTRUE),
  fMultCut(kTRUE),
  fDebug(kFALSE),
  fHarmonic(2),
  fEtaGap(0.),
  fPsi_L(0.),
  fPsi_R(0.),
  fPsi(0.),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fRes2(),
  fstrInputFileFromFirstRun(""),
  fPrRes(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2FHCalEventPlane(nullptr)
{
}

FlowAnalysisWithFHCalEventPlane::~FlowAnalysisWithFHCalEventPlane()
{
}

void FlowAnalysisWithFHCalEventPlane::Init()
{
  fPrRes = new TProfile("prResFHCal", "FHCal, EP resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector(1.);
  fQvector_R = new QVector(1.);
  if (!fFirstRun) 
  {
    for (Int_t i=0; i < npid; i++)
    {
      fPrV2vsPt[i] = new TProfile2D(Form("prV2FHCalEPvsPt_pid%i",i), Form("v_{2}{FHCal EP}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
    }
    fPrV2vsEta = new TProfile2D("prV2FHCalEPvsEta", "v_{2}{FHCal EP}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
    fPrV2FHCalEventPlane = new TProfile3D("prV2FHCalEventPlane", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes();
  }  
}

void FlowAnalysisWithFHCalEventPlane::Zero()
{
  fPsi_L = 0.;
  fPsi_R = 0.;
  fPsi = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithFHCalEventPlane::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight)
{
  if (eta < -2.0 && eta > -5.0)
  {
    fQvector_L->CalQVector(phi, -weight);
  }
  if (eta > 2.0 && eta < 5.0)
  {
    fQvector_R->CalQVector(phi, weight);
  }
}

void FlowAnalysisWithFHCalEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = kFALSE;
    // fQvector_L->WeightQVector();
    // fQvector_R->WeightQVector();
    fPsi_L = TMath::ATan2(fQvector_L->Y(), fQvector_L->X());
    fPsi_R = TMath::ATan2(fQvector_R->Y(), fQvector_R->X());
    fPsi = TMath::ATan2(fQvector_L->Y()+fQvector_R->Y(),fQvector_L->X()+fQvector_R->X());
    if (fFirstRun) fPrRes->Fill(dCent, TMath::Cos( fPsi_L - fPsi_R ));
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithFHCalEventPlane::GetRes()
{
  if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
  TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  fPrRes = dynamic_cast<TProfile*> (fi->FindObjectAny("prResFHCal"));
  if (!fPrRes) cerr << "Cannot find histograms from first run for FHCAL EP method!" << endl;
  Double_t chi, res, res2, chiF, resF; 
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    res2 = fPrRes->GetBinContent(ic+1);
    res = (res2>0) ? TMath::Sqrt(res2) : 0.;
    chi = GetChi(res,1.,50);
    chiF = TMath::Sqrt(2.)*chi;
    resF = Res(chiF,2.);
    fRes2[ic]=(res!=0) ? resF : 0.;
  }
  if (fDebug)
  {
    cout << "FHCal Resolution:" << endl;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      cout << fRes2[ic] <<", ";
    }
    cout << endl;
    cout << "FHCal Chi:" << endl;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      res2 = fPrRes->GetBinContent(ic+1);
      res = (res2>0) ? TMath::Sqrt(res2) : 0.;
      chi = GetChi(res,1.,50);
      chiF = TMath::Sqrt(2.)*chi;
      cout << chiF <<", ";
    }
    cout << endl;
  }
  
}

void FlowAnalysisWithFHCalEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  if (!fMultCut && !fFirstRun) //  && fabs(eta)>=fEtaGap
  {
    Double_t v2FHCalEventPlane = TMath::Cos( 2.0 * (phi - fPsi) );
    Int_t icent = fPrRes->FindBin(dCent) - 1;
    if (fRes2[icent] != 0)
    { 
      v2FHCalEventPlane /= fRes2[icent];
      fPrV2FHCalEventPlane->Fill(dCent, pt, eta, v2FHCalEventPlane);
      fPrV2vsPt[8]->Fill(dCent, pt, v2FHCalEventPlane);
      if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, v2FHCalEventPlane); }
      if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, v2FHCalEventPlane); }      
    }
  }
}

void FlowAnalysisWithFHCalEventPlane::SaveHist()
{
  if (fFirstRun) fPrRes->Write();
  else
  {
    fPrV2FHCalEventPlane->Write();
    fPrV2vsEta->Write();
    for (Int_t i=0; i < npid; i++)
    {
      fPrV2vsPt[i]->Write();
    }
  }
}
void FlowAnalysisWithFHCalEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  if (fFirstRun) outputDir->Add(fPrRes);  
  else
  {
    outputDir->Add(fPrV2FHCalEventPlane);
    outputDir->Add(fPrV2vsEta);
    for (Int_t i=0; i < npid; i++)
    {
      outputDir->Add(fPrV2vsPt[i]);
    }
  }
  outputDir->Write();
}
Double_t FlowAnalysisWithFHCalEventPlane::Res(Double_t chi, Double_t harmonic)
{
  Double_t con = TMath::Sqrt(TMath::Pi() / 2) / 2;
  Double_t arg = chi * chi / 4.;
  Double_t order1 = (harmonic - 1) / 2.;
  Double_t order2 = (harmonic + 1) / 2.;
  Double_t res = con * chi * TMath::Exp(-arg) * (ROOT::Math::cyl_bessel_i(order1, arg) + ROOT::Math::cyl_bessel_i(order2, arg));
  return res;
}

Double_t FlowAnalysisWithFHCalEventPlane::GetChi(Double_t res, Double_t harmonic, Int_t accuracy)
{
  Double_t chi = 2.0;
  Double_t delta = 1.0;
  for (Int_t i = 0; i < accuracy; i++){
    if(Res(chi, harmonic) < res) chi = chi + delta;
    else chi = chi - delta;
    delta = delta / 2.;
  }
  return chi;
}

class FlowAnalysisWithMCEventPlane
{
public:
  FlowAnalysisWithMCEventPlane();
  virtual ~FlowAnalysisWithMCEventPlane();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight);
  void ProcessEventAfterFirstTrackLoop(const Double_t &dCent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge);  
  void SetDebugFlag(Bool_t kt) { this->fDebug = kt; }
  void SetHarmonic(Int_t i) { this->fHarmonic = i; }
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SetPsiRP(Double_t d) { this->fPsiRP = d; }
  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);
private:
  Bool_t fMultCut;
  Bool_t fDebug;
  Int_t fHarmonic;
  Double_t fEtaGap;
  Double_t fPsiRP;
  Double_t fPsiEP;
  QVector *fQvector_L;
  QVector *fQvector_R;
  TProfile *fPrRes;
  TProfile2D *fPrV2vsPt[npid];
  TProfile2D *fPrV2vsEta;
  TProfile3D *fPrV2MCEventPlane;
  // ClassDef(FlowAnalysisWithMCEventPlane,0);

};

FlowAnalysisWithMCEventPlane::FlowAnalysisWithMCEventPlane() :
  fMultCut(kTRUE),
  fDebug(kFALSE),
  fHarmonic(2),
  fEtaGap(0.),
  fPsiRP(0.),
  fPsiEP(0.),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fPrRes(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2MCEventPlane(nullptr)
{
}

FlowAnalysisWithMCEventPlane::~FlowAnalysisWithMCEventPlane()
{
}

void FlowAnalysisWithMCEventPlane::Init()
{
  fPrRes = new TProfile("prResMCEventPlane", "MC EP resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector(fHarmonic);
  fQvector_R = new QVector(fHarmonic);

  for (Int_t i = 0; i < npid; i++)
  {
    fPrV2vsPt[i] = new TProfile2D(Form("prV2MCvsPt_pid%i",i), Form("v_{2}{MC EP}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
  }
  fPrV2vsEta = new TProfile2D("prV2MCvsEta", "v_{2}{MC EP}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
  fPrV2MCEventPlane = new TProfile3D("prV2MCEventPlane", "Testing TProfile3D", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
  
}

void FlowAnalysisWithMCEventPlane::Zero()
{
  fPsiRP = 0.;
  fPsiEP = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithMCEventPlane::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight)
{
  if (eta < - fEtaGap)
  {
    fQvector_L->CalQVector(phi, weight);
  }
  if (eta > fEtaGap)
  {
    fQvector_R->CalQVector(phi, weight);
  }
}

void FlowAnalysisWithMCEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = kFALSE;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fPsiEP = TMath::ATan2(fQvector_L->Y()+fQvector_R->Y(), fQvector_L->X()+fQvector_R->X())/fHarmonic;
    fPrRes->Fill(dCent, TMath::Cos( fHarmonic * (fPsiEP - fPsiRP) ));
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithMCEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  // if (!fMultCut && TMath::Abs(eta) > fEtaGap)
  // {
    Double_t v2MCEventPlane = TMath::Cos( fHarmonic * (phi - fPsiRP) );
    fPrV2MCEventPlane->Fill(dCent, pt, eta, v2MCEventPlane);
    fPrV2vsPt[8]->Fill(dCent, pt, v2MCEventPlane);
    if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, v2MCEventPlane); }
    if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, v2MCEventPlane); }
    if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, v2MCEventPlane); }
  // }
}

void FlowAnalysisWithMCEventPlane::SaveHist()
{
  fPrRes->Write();
  fPrV2MCEventPlane->Write();
  fPrV2vsEta->Write();
  for (Int_t i = 0; i < npid; i++)
  {
    fPrV2vsPt[i]->Write();
  }
  
}

void FlowAnalysisWithMCEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  outputDir->Add(fPrRes); 
  outputDir->Add(fPrV2MCEventPlane);
  outputDir->Add(fPrV2vsEta);
  for (Int_t i = 0; i < npid; i++)
  {
    outputDir->Add(fPrV2vsPt[i]);
  }
  outputDir->Write();
}

bool FHCALEVENTPLANE_1 = 0;
bool FHCALEVENTPLANE_2 = 1;

Double_t maxpt = 3.0;    // max pt for differential flow
Double_t minpt = 0.;     // min pt for differential flow
Double_t maxptRF = 3.;   // max pt for reference flow
Double_t minptRF = 0.2;  // min pt for reference flow
Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
Double_t eta_gap = 0.0; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
Long64_t Nevents = -1;

Int_t debug = 1;

std::string format = "mctree";
#define MAX_TRACKS 10000

void RunFlowAnalysis(TString inputFileName, TString outputFileName, TString inputHistogramFileName)
{
  TStopwatch timer;
  timer.Start();

  // Configure input information
  TChain *chain = initChain(inputFileName, format.c_str());

  Float_t         bimp;
  Float_t         phi2;
  Float_t         phi3;
  Float_t         ecc2;
  Float_t         ecc3;
  Int_t           npart;
  Int_t           nh;
  Float_t         momx[MAX_TRACKS];   //[nh]
  Float_t         momy[MAX_TRACKS];   //[nh]
  Float_t         momz[MAX_TRACKS];   //[nh]
  Float_t         ene[MAX_TRACKS];   //[nh]
  Int_t           hid[MAX_TRACKS];   //[nh]
  Int_t           pdg[MAX_TRACKS];   //[nh]
  Short_t         charge0[MAX_TRACKS];   //[nh]

  // List of branches
  TBranch        *b_bimp;   //!
  TBranch        *b_phi2;   //!
  TBranch        *b_phi3;   //!
  TBranch        *b_ecc2;   //!
  TBranch        *b_ecc3;   //!
  TBranch        *b_npart;   //!
  TBranch        *b_nh;   //!
  TBranch        *b_momx;   //!
  TBranch        *b_momy;   //!
  TBranch        *b_momz;   //!
  TBranch        *b_ene;   //!
  TBranch        *b_hid;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_charge;   //!

  chain->SetBranchAddress("bimp", &bimp, &b_bimp);
  chain->SetBranchAddress("phi2", &phi2, &b_phi2);
  chain->SetBranchAddress("phi3", &phi3, &b_phi3);
  chain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  chain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  chain->SetBranchAddress("npart", &npart, &b_npart);
  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("momx", momx, &b_momx);
  chain->SetBranchAddress("momy", momy, &b_momy);
  chain->SetBranchAddress("momz", momz, &b_momz);
  chain->SetBranchAddress("ene", ene, &b_ene);
  chain->SetBranchAddress("hid", hid, &b_hid);
  chain->SetBranchAddress("pdg", pdg, &b_pdg);
  chain->SetBranchAddress("charge", charge0, &b_charge);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  FlowAnalysisWithFHCalEventPlane *flowFHCalEP = nullptr; // FHCal Event Plane
  FlowAnalysisWithMCEventPlane    *flowMCEP    = nullptr; // MC Event Plane
  flowFHCalEP = new FlowAnalysisWithFHCalEventPlane();
  flowFHCalEP->SetDebugFlag(debug);
  flowFHCalEP->SetEtaGap(0);

  if (FHCALEVENTPLANE_1) flowFHCalEP->SetFirstRun(true);
  
  if (FHCALEVENTPLANE_2)
  {
    flowFHCalEP->SetFirstRun(false);
    flowFHCalEP->SetInputFileFromFirstRun(inputHistogramFileName);
  }
  flowFHCalEP->Init();

  flowMCEP = new FlowAnalysisWithMCEventPlane();
  flowMCEP->SetDebugFlag(debug);
  flowMCEP->SetHarmonic(2.);
  flowMCEP->SetEtaGap(0.);
  flowMCEP->Init();

  Double_t pt, eta, phi, charge;
  Long64_t chain_size = chain->GetEntries();
  Long64_t n_entries = (Nevents < chain_size && Nevents > 0) ? Nevents : chain_size;
  cout << "Hi Master, let's do some physics together..." << endl;
  for (Int_t iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    if (!nh) continue;
    // Read MC event
    Double_t cent = CentB(bimp);
    if (cent == -1)
      continue;

    flowFHCalEP->Zero();
    flowMCEP->Zero();

    for (Int_t iTrk = 0; iTrk < nh; iTrk++)
    { // Track loop
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      pt  = vect.Pt();
      eta = vect.Eta();
      phi = vect.Phi();
      // auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      // if (!particle) continue;
      flowFHCalEP->ProcessFirstTrackLoop(eta, phi, pt);
    } // end of track loop
    flowFHCalEP->ProcessEventAfterFirstTrackLoop(cent);

    if (FHCALEVENTPLANE_2)
    {
      for (Int_t iTrk = 0; iTrk < nh; iTrk++)
      { // 2nd Track loop
        TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
        pt  = vect.Pt();
        eta = vect.Eta();
        phi = vect.Phi();
        if (pt < minpt || pt > maxpt || fabs(eta)>eta_cut) continue; // track selection
        // if (abs(eta)<eta_gap) continue;
        auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
        if (!particle) continue;
        charge = 1./3.*particle->Charge();
        if (charge == 0) continue;
        Int_t fId = findId(pdg[iTrk]);

        flowFHCalEP->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
        flowMCEP->ProcessSecondTrackLoop(eta, phi, pt, cent, fId, charge);
      }
    }
  } // end event loop

  // Writing output
  fo->cd();
  flowFHCalEP->SaveHist();
  flowMCEP->SaveHist();
  fo->Close();

  timer.Stop();
  timer.Print();
}

int main(int argc, char **argv)
{
  TString iFileName, oFileName, inputHistogram = "", inputHistogramFromLYZSecondRun = "";

  if (argc < 5)
  {
    std::cerr << "./FlowQCumulant -i INPUT -o OUTPUT [-inHist FirstRun.root -inHist2 SecondRun.root]" << std::endl;
    return 1;
  }
  for (Int_t i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" &&
        std::string(argv[i]) != "-inHist" &&
        std::string(argv[i]) != "-inHist2")
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
      if (std::string(argv[i]) == "-inHist" && i != argc - 1)
      {
        inputHistogram = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-inHist" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input histogram file name was not specified " << std::endl;
        return 1;
      }
    }
  }

  RunFlowAnalysis(iFileName, oFileName, inputHistogram);

  return 0;
}