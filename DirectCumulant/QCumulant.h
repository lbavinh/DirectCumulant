#ifndef QCumulant_h
#define QCumulant_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

static const int max_nh = 5000;

class QCumulant {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Float_t         bimp;   // impact parameter 
  Float_t         phi2;   // v2 event plane from model 
  Float_t         phi3;   // v3 event plane from model
  Float_t         ecc2;   // eccentricity e2 
  Float_t         ecc3;   // eccrntricity e3
  Int_t           npart;  // number of participants
  Int_t           nh;     // number of particles in event
  Float_t         momx[max_nh];   //[nh] momentum px
  Float_t         momy[max_nh];   //[nh] momentum py
  Float_t         momz[max_nh];   //[nh] momentum pz
  Float_t         ene[max_nh];    //[nh] energy of particle
  Int_t           hid[max_nh];    //[nh] 
  Int_t           pdg[max_nh];    //[nh] particle ID
  Short_t         charge[max_nh]; //[nh] charge of particle

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

  QCumulant(TTree *tree=0);
  virtual ~QCumulant();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  // additional function
  void Booking(TString outFile);
  void Loop_a_file(TString file);
  void Loop_a_list_of_file(TString fileList);
  void Ana_end();
  void Ana_event();   
};

#endif

#ifdef QCumulant_cxx
QCumulant::QCumulant(TTree *tree) : fChain(0) 
{}

QCumulant::~QCumulant()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t QCumulant::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t QCumulant::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void QCumulant::Init(TTree *tree)
{
  // Set branch addresses and branch pointers
  if (!tree) return;
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

Bool_t QCumulant::Notify()
{
  return kTRUE;
}

void QCumulant::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t QCumulant::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif
