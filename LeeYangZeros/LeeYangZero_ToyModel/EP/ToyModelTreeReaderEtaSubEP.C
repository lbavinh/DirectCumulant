#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile3D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
float CentB(float bimp);
int GetCentBin(float cent);
// using namespace std;
using std::cerr;
using std::cout;
using std::endl;

#define MAX_TRACKS 10000

// Constant declaration
// const int npid = 8;  // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
const int ncent = 9; // 0-80%
const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
const int npt = 12; // 0.2 - 3.5 GeV/c
const double pTBin[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
const double maxpt = 3.5; // max pt
const double minpt = 0.2; // min pt
const double maxptRF = 3.;
const double minptRF = 0.2;
const float eta_cut = 2.0;
const float eta_gap = 0;
const int neta = 2; // [eta-,eta+]

const int netaBin = 10;
const double etaBin[netaBin+1] = {-2.0, -1.5, -1.0, -0.5, -0.25, 0.0, 0.25, 0.5, 1.0, 1.5, 2.0};

// EtaSubEventPlane

const int npid = 1;
const double PIDBin[npid+1] = {0., 1.};
const int mult_EP_cut = 4; 

class CQVector
{
public:
  CQVector();
  virtual ~CQVector(){};
  void Zero();
  void CalQVector(const double &phi, const double &weight);
  void WeightQVector();
  double X() const { return this->fQx; }
  double Y() const { return this->fQy; }
  int GetMult() const { return this->fMult; }

private:
  double fQx;
  double fQy;
  double fWeight;
  int fMult;
};
CQVector::CQVector() : fQx(0), fQy(0), fMult(0), fWeight(0) {}
void CQVector::Zero()
{
  fQx = 0.;
  fQy = 0.;
  fMult = 0.;
  fWeight = 0.;
}
void CQVector::CalQVector(const double &phi, const double &weight)
{
  fQx += weight * TMath::Cos(2.0 * phi);
  fQy += weight * TMath::Sin(2.0 * phi);
  fWeight += weight;
  fMult++;
}
void CQVector::WeightQVector()
{
  if (fMult != 0)
  {
    fQx /= fWeight;
    fQy /= fWeight;
  }
}

class FlowAnalysisWithEtaSubEventPlane
{
public:
  FlowAnalysisWithEtaSubEventPlane(bool bFirstRun, TString inputFileFromFirstRun);
  virtual ~FlowAnalysisWithEtaSubEventPlane() {}
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const double &eta, const double &phi, const double &pt);
  void ProcessEventAfterFirstTrackLoop(const double &dCent);
  void ProcessSecondTrackLoop(const double &eta, const double &phi, const double &pt, const double &dCent);
  void GetRes(TString inputFileFromFirstRun);
  void SaveHist();
private:
  bool fFirstRun;
  bool fMultCut;
  double fPsi_L;
  double fPsi_R;
  CQVector Qvector_L;
  CQVector Qvector_R;
  double fRes2[ncent];

  TProfile *fPrRes;
  TProfile3D *fPrV2EtaSubEventPlane;

};
FlowAnalysisWithEtaSubEventPlane::FlowAnalysisWithEtaSubEventPlane(bool bFirstRun, TString inputFileFromFirstRun) :fFirstRun(bFirstRun)
{
  fPrRes = new TProfile("prRes", "EP resolution", ncent, &bin_cent[0]);
  if (!fFirstRun) 
  {
    fPrV2EtaSubEventPlane = new TProfile3D("prV2EtaSubEventPlane", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes(inputFileFromFirstRun);
  }
}

void FlowAnalysisWithEtaSubEventPlane::Zero()
{
  fPsi_L = 0.;
  fPsi_R = 0.;
  Qvector_L.Zero();
  Qvector_R.Zero();
}

void FlowAnalysisWithEtaSubEventPlane::ProcessFirstTrackLoop(const double &eta, const double &phi, const double &pt)
{
  if (eta < - eta_gap)
  {
    Qvector_L.CalQVector(phi, pt);
  }
  if (eta > eta_gap)
  {
    Qvector_R.CalQVector(phi, pt);
  }
}

void FlowAnalysisWithEtaSubEventPlane::ProcessEventAfterFirstTrackLoop(const double &dCent)
{
  if (Qvector_L.GetMult() > mult_EP_cut && Qvector_R.GetMult() > mult_EP_cut)
  {
    fMultCut = false;
    Qvector_L.WeightQVector();
    Qvector_R.WeightQVector();
    fPsi_L = 0.5 * TMath::ATan2(Qvector_L.Y(), Qvector_L.X());
    fPsi_R = 0.5 * TMath::ATan2(Qvector_R.Y(), Qvector_R.X());
    fPrRes->Fill(dCent, TMath::Cos( 2.0 * (fPsi_L - fPsi_R) ));
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithEtaSubEventPlane::GetRes(TString inputFileFromFirstRun)
{
  if (!fFirstRun)
  {
    if (!inputFileFromFirstRun) { cerr << "Warning: inputFileFromFirstRun=NULL" << endl;}
    TFile *fi = new TFile(inputFileFromFirstRun.Data(), "read");
    fPrRes = (TProfile*)fi->Get("prRes");
    for (int ic = 0; ic < ncent; ic++)
    {
      fRes2[ic] = TMath::Sqrt(fPrRes->GetBinContent(ic+1));
    }
  }
}

void FlowAnalysisWithEtaSubEventPlane::ProcessSecondTrackLoop(const double &eta, const double &phi, const double &pt, const double &dCent)
{
  if (!fMultCut && !fFirstRun)
  {
    double v2EtaSubEventPlane = -999.0;
    if (eta < - eta_gap)
    {
      v2EtaSubEventPlane = TMath::Cos( 2.0 * (phi - fPsi_R) );
    }
    else if (eta > eta_gap)
    {
      v2EtaSubEventPlane = TMath::Cos( 2.0 * (phi - fPsi_L) );
    }
    else { return; }
    int icent = fPrRes->FindBin(dCent) - 1;
    if (fRes2[icent] != 0)
    { 
      v2EtaSubEventPlane /= fRes2[icent];
      fPrV2EtaSubEventPlane->Fill(dCent, pt, eta, v2EtaSubEventPlane);
    }
  }
}

void FlowAnalysisWithEtaSubEventPlane::SaveHist()
{
  fPrRes->Write();
  if (!fFirstRun) fPrV2EtaSubEventPlane->Write();
}

void ToyModelTreeReaderEtaSubEP(TString inputFileName, TString outputFileName, TString inputFileHistFromFirstRun, Bool_t bFirstRun = 1)
{
  TStopwatch timer;
  timer.Start();

  TChain *chain = new TChain("tree");
  if (inputFileName.Contains(".root"))
  {
    chain->Add(inputFileName.Data());
  }
  else
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    while (std::getline(file, line))
    {
      chain->Add(line.c_str());
    }
  }

  if (!chain)
    return;

  // Declaration of leaf types
  Int_t nh;
  Float_t bimp;
  Float_t rp;
  Float_t phi0[MAX_TRACKS]; //[nh]
  Bool_t bFlow[MAX_TRACKS]; //[nh]
  Float_t eta0[MAX_TRACKS]; //[nh]
  Float_t pt0[MAX_TRACKS];  //[nh]

  // List of branches
  TBranch *b_nh;    //!
  TBranch *b_b;     //!
  TBranch *b_rp;    //!
  TBranch *b_phi0;  //!
  TBranch *b_bFlow; //!
  TBranch *b_eta;   //!
  TBranch *b_pt;    //!

  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("b", &bimp, &b_b);
  chain->SetBranchAddress("rp", &rp, &b_rp);
  chain->SetBranchAddress("phi0", phi0, &b_phi0);
  chain->SetBranchAddress("bFlow", bFlow, &b_bFlow);
  chain->SetBranchAddress("eta", eta0, &b_eta);
  chain->SetBranchAddress("pt", pt0, &b_pt);

  if (chain == 0)
    return;

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  TProfile *hv2MC = new TProfile("hv2MC", "MC flow", ncent, &bin_cent[0]);
  TProfile *hv2MCpt[ncent];

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2MCpt[icent] = new TProfile(Form("hv2MCpt_%i", icent), "", npt, &pTBin[0]);
  } // end of loop over centrality classes

  FlowAnalysisWithEtaSubEventPlane *flowEtaSub = new FlowAnalysisWithEtaSubEventPlane(bFirstRun, inputFileHistFromFirstRun);
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    // if (iEv == 10000)
    //   break;
    chain->GetEntry(iEv);

    // Get centrality
    double dCent = CentB(bimp);
    if (dCent == -1)
      continue;
    int icent = GetCentBin(dCent);
    flowEtaSub->Zero();

    for (int iTrk = 0; iTrk < nh; iTrk++)
    {
      float pt = pt0[iTrk];
      float eta = eta0[iTrk];
      float phi = phi0[iTrk];
      if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
        continue; // track selection

      flowEtaSub->ProcessFirstTrackLoop(eta, phi, pt);


      Double_t v2 = TMath::Cos(2 * (phi - rp));
      if (bFlow[iTrk])
      {
        hv2MC->Fill(dCent, v2);       // calculate reference v2 from MC toy
        hv2MCpt[icent]->Fill(pt, v2); // Calculate differential v2 from MC toy
      }


    } // end of track loop
    flowEtaSub->ProcessEventAfterFirstTrackLoop(dCent);

    if (!bFirstRun)
    {
      for (int iTrk = 0; iTrk < nh; iTrk++)
      {
        float pt = pt0[iTrk];
        float eta = eta0[iTrk];
        float phi = phi0[iTrk];
        if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
          continue; // track selection
        flowEtaSub->ProcessSecondTrackLoop(eta, phi, pt, dCent);

      } // end of track loop
    }
  } // end event loop

  // Writing output
  fo->cd();
  flowEtaSub->SaveHist();
  if (bFirstRun)
  {
    hv2MC->Write();
    for (int ic = 0; ic < ncent; ic++)
    {
      hv2MCpt[ic]->Write();
    }
  }

  fo->Close();

  timer.Stop();
  timer.Print();
}

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if (bimp < 2.91)
    fcent = 2.5; // 0-5%
  else if (bimp < 4.18)
    fcent = 7.5; // 5-10%
  else if (bimp < 6.01)
    fcent = 15.; // 10-20%
  else if (bimp < 7.37)
    fcent = 25.; // 20-30%
  else if (bimp < 8.52)
    fcent = 35.; // 30-40%
  else if (bimp < 9.57)
    fcent = 45.; // 40-50%
  else if (bimp < 10.55)
    fcent = 55.; // 50-60%
  else if (bimp < 11.46)
    fcent = 65.; // 60-70%
  else if (bimp < 12.31)
    fcent = 75.; // 70-80%
  else
    fcent = -1;
  return fcent;
}

int GetCentBin(float cent)
{
  if (cent == -1)
    return -1;
  if (cent == 2.5)
    return 0;
  if (cent == 7.5)
    return 1;
  if (cent == 15.)
    return 2;
  if (cent == 25.)
    return 3;
  if (cent == 35.)
    return 4;
  if (cent == 45.)
    return 5;
  if (cent == 55.)
    return 6;
  if (cent == 65.)
    return 7;
  if (cent == 75.)
    return 8;
  return -1;
}


// prReGthetaSum_mult0_theta0->Draw()