//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 26 20:23:30 2021 by ROOT version 6.12/06
// from TTree mctree/Hadrons tree from MC RHIC models
// found on file: /weekly/demanov/mchybrid/39GeVxpt500new/hybrid39GeV500Evrun022.root
//////////////////////////////////////////////////////////

#ifndef vHLLEUrQMD_h
#define vHLLEUrQMD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#define MAX_NH 10000
class vHLLEUrQMD
{
 public:
  TTree *fChain;  //!pointer to the analyzed TTree or TChain
  Int_t fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Float_t bimp;
  Float_t phi2;
  Float_t phi3;
  Float_t ecc2;
  Float_t ecc3;
  Int_t npart;
  Int_t nh;
  Float_t momx[MAX_NH];   //[nh]
  Float_t momy[MAX_NH];   //[nh]
  Float_t momz[MAX_NH];   //[nh]
  Float_t ene[MAX_NH];    //[nh]
  Int_t hid[MAX_NH];      //[nh]
  Int_t pdg[MAX_NH];      //[nh]
  Short_t charge[MAX_NH]; //[nh]

  // List of branches
  TBranch *b_bimp;   //!
  TBranch *b_phi2;   //!
  TBranch *b_phi3;   //!
  TBranch *b_ecc2;   //!
  TBranch *b_ecc3;   //!
  TBranch *b_npart;  //!
  TBranch *b_nh;     //!
  TBranch *b_momx;   //!
  TBranch *b_momy;   //!
  TBranch *b_momz;   //!
  TBranch *b_ene;    //!
  TBranch *b_hid;    //!
  TBranch *b_pdg;    //!
  TBranch *b_charge; //!

  vHLLEUrQMD(TTree *tree = 0);
  virtual ~vHLLEUrQMD();
  virtual Int_t GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void Loop();
  virtual Bool_t Notify();
  void FlowAnalysis();
};

#endif

#ifdef vHLLEUrQMD_cxx
vHLLEUrQMD::vHLLEUrQMD(TTree *tree) : fChain(0)
{
  if (!tree)
    return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("bimp", &bimp, &b_bimp);
  fChain->SetBranchAddress("phi2", &phi2, &b_phi2);
  fChain->SetBranchAddress("phi3", &phi3, &b_phi3);
  fChain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  fChain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  fChain->SetBranchAddress("npart", &npart, &b_npart);
  fChain->SetBranchAddress("nh", &nh, &b_nh);
  fChain->SetBranchAddress("momx", momx, &b_momx);
  fChain->SetBranchAddress("momy", momy, &b_momy);
  fChain->SetBranchAddress("momz", momz, &b_momz);
  fChain->SetBranchAddress("ene", ene, &b_ene);
  fChain->SetBranchAddress("hid", hid, &b_hid);
  fChain->SetBranchAddress("pdg", pdg, &b_pdg);
  fChain->SetBranchAddress("charge", charge, &b_charge);
  Notify();
}

vHLLEUrQMD::~vHLLEUrQMD()
{
  if (!fChain)
    return;
  delete fChain->GetCurrentFile();
}

Int_t vHLLEUrQMD::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain)
    return 0;
  return fChain->GetEntry(entry);
}
Long64_t vHLLEUrQMD::LoadTree(Long64_t entry)
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



Bool_t vHLLEUrQMD::Notify()
{
  return kTRUE;
}

void vHLLEUrQMD::Loop()
{
  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
  }
}

#endif // #ifdef vHLLEUrQMD_cxx
