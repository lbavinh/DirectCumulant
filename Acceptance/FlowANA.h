//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Aug  2 20:31:30 2020 by ROOT version 6.12/06
// from TTree htree/My Tree
// found on file: v2hadron_nonflow_test.root
//////////////////////////////////////////////////////////

#ifndef FlowANA_h
#define FlowANA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>
#include <TProfile.h>
#include <TProfile2D.h>
// Header file for the classes stored in the TTree if any.

const int ncent = 8; // 0-80%
const int bin_cent[ncent] = {5, 15, 25, 35, 45, 55, 65, 75};
const int max_nh = 5100;
const double maxpt = 3.5; // max pt
const double minpt = 0.2; // min pt
const int npt = 12;        // 0.2 - 3.5 GeV/c
const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2,
                                      1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
const int neta = 2; // [eta-,eta+]
const float eta_cut = 1.5;
const float eta_gap = 0.05;
const int nharm = 10; // v2,v3,...,v6


class FlowANA
{
public:
  TTree *fChain;  //!pointer to the analyzed TTree or TChain
  Int_t fCurrent; //!current Tree number in a TChain

  Int_t fRunNum;
  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Int_t nh;
  Float_t b;
  Float_t rp;
  Float_t phi0[6000]; //[nh]
  Bool_t bFlow[6000]; //[nh]
  Float_t eta0[6000];  //[nh]
  Float_t pt0[6000];   //[nh]

  // List of branches
  TBranch *b_nh;    //!
  TBranch *b_b;     //!
  TBranch *b_rp;    //!
  TBranch *b_phi0;  //!
  TBranch *b_bFlow; //!
  TBranch *b_eta;   //!
  TBranch *b_pt;    //!

  FlowANA(TTree *tree = 0);
  virtual ~FlowANA();
  virtual Int_t Cut(Long64_t entry);
  virtual Int_t GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void Init(TTree *tree);
  virtual Bool_t Notify();
  virtual void Show(Long64_t entry = -1);

  // additional function
  void Booking(TString outFile);
  void Loop_a_file(TString file);
  void Ana_end();
  void Ana_event();  
  void Recentering();
  void FinishRecentering();
  void Flattening();
  void FinishFlattening();
  void Resolution();
  void FinishResolution();
  void CalFlow();
  void SetRunNum(Int_t _i) { this->fRunNum = _i; }

  TFile *d_outfile; // out file with histograms and profiles

  // ================= Eta sub-event ================= //

  // Control histograms
  TH1F *hQvecRaw[ncent][neta];
  TH1F *hQMultRaw[ncent][neta];
  TH1F *hQvecRec[ncent][neta];
  TH1F *hPsiRaw[ncent][neta];				// raw event plane 
  TH1F *hPsiRecentered[ncent][neta];
  TH1F *hPsiFlattened[ncent][neta];
  TH1F *hPsiRawMB, *hPsiRecMB, *hPsiFlatMB; 
  Int_t centrality;

  Double_t sumQxy[neta][2];    // [eta-,eta+][x,y]
  Double_t multQv[neta];         // [eta+,eta-]

  // for recentering
  TProfile *pQx[neta];            // <Qx>
  TProfile *pQy[neta];            // <Qy>
  Double_t qxMean[ncent][neta];   // <Qx>
  Double_t qyMean[ncent][neta];   // <Qy>

  // for flattening
  TProfile *pCosNPsi[neta][nharm];
  TProfile *pSinNPsi[neta][nharm];
  Double_t qxRec, qyRec, psi2;
  Double_t cosNPhiMean[neta][nharm][ncent], sinNPhiMean[neta][nharm][ncent];
  Double_t dPsi;
  // for resolution
  TProfile *pRes;		          // resolution
  Double_t fPsiRaw[2];
  Double_t fPsiRec[2];
  Double_t fPsiFlat[2];
  Double_t fPsi[2];
  Double_t fQv[2];
  // for flow
  Double_t res2[ncent];  // Resolution Psi2
  TProfile2D *pV2etasub;	   // elliptic flow from EP method

  // ================= Direct cumulants ================= //

  // TProfile for reference flow (RF)
  TProfile2D *pV2MC; // profile for MC integrated v2
  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow (DF)
  TProfile *hPT[npt];     // profile pt
  TProfile *hv22pt[ncent][npt];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];  // profile <<4'>> from 4th Q-Cumulants

  // TProfile for covariance calculation according to (C.12), Appendix C
  // in Bilandzic, A. (2012)
  // Anisotropic flow measurements in ALICE at the large hadron collider.
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

  // non-uniform acceptance correction
  // Reference flow acceptance correction
  TProfile *hcos2phi1, *hsin2phi1, *hcos2phi12, *hsin2phi12, *hcos2phi123, *hsin2phi123;

  // Differential flow acceptance correction
  TProfile *hcos2psi1[npt], *hsin2psi1[npt], *hcos2psi1phi2[npt], *hsin2psi1phi2[npt];
  TProfile *hcos2psi1pphi23[npt], *hsin2psi1pphi23[npt], *hcos2psi1mphi23[npt], *hsin2psi1mphi23[npt];
  ClassDef(FlowANA,0);
};

#endif

#ifdef FlowANA_cxx
ClassImp(FlowANA);
FlowANA::FlowANA(TTree *tree) : fChain(0), fRunNum(0)
{
}

FlowANA::~FlowANA()
{
  if (!fChain)
    return;
  delete fChain->GetCurrentFile();
}

Int_t FlowANA::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain)
    return 0;
  return fChain->GetEntry(entry);
}
Long64_t FlowANA::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain)
    return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0)
    return centry;
  if (fChain->GetTreeNumber() != fCurrent)
  {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void FlowANA::Init(TTree *tree)
{
  // Set branch addresses and branch pointers
  if (!tree)
    return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("nh", &nh, &b_nh);
  fChain->SetBranchAddress("b", &b, &b_b);
  fChain->SetBranchAddress("rp", &rp, &b_rp);
  fChain->SetBranchAddress("phi0", phi0, &b_phi0);
  fChain->SetBranchAddress("bFlow", bFlow, &b_bFlow);
  fChain->SetBranchAddress("eta", eta0, &b_eta);
  fChain->SetBranchAddress("pt", pt0, &b_pt);
  Notify();
}

Bool_t FlowANA::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void FlowANA::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain)
    return;
  fChain->Show(entry);
}
Int_t FlowANA::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef FlowANA_cxx
