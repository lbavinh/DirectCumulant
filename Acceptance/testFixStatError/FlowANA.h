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

// Header file for the classes stored in the TTree if any.

class FlowANA
{
public:
  TTree *fChain;  //!pointer to the analyzed TTree or TChain
  Int_t fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Int_t nh;
  Float_t b;
  Float_t rp;
  Float_t phi0[6100]; //[nh]
  Bool_t bFlow[6100]; //[nh]
  Float_t eta[6100];  //[nh]
  Float_t pt[6100];   //[nh]

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

};

#endif

#ifdef FlowANA_cxx
FlowANA::FlowANA(TTree *tree) : fChain(0)
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
  fChain->SetBranchAddress("eta", eta, &b_eta);
  fChain->SetBranchAddress("pt", pt, &b_pt);
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
