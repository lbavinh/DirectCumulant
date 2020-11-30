//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Oct  6 17:06:44 2019 by ROOT version 6.19/01
// from TTree nt_Au3_Au3/Au3 + Au3 (x-sect = 31.2 mb) str gmc-Au3Au3-snn31.2-md0.4-nd-1.0-rc1-smax99.0
// found on file: merge_glaub_11gev.root
//////////////////////////////////////////////////////////

#ifndef GlauberEccReader_h
#define GlauberEccReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class GlauberEccReader {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Float_t         Npart;
  Float_t         Ncoll;
  Float_t         Nhard;
  Float_t         B;
  Float_t         BNN;
  Float_t         Ncollpp;
  Float_t         Ncollpn;
  Float_t         Ncollnn;
  Float_t         VarX;
  Float_t         VarY;
  Float_t         VarXY;
  Float_t         NpartA;
  Float_t         NpartB;
  Float_t         Npart0;
  Float_t         AreaW;
  Float_t         Psi1;
  Float_t         Ecc1;
  Float_t         Psi2;
  Float_t         Ecc2;
  Float_t         Psi3;
  Float_t         Ecc3;
  Float_t         Psi4;
  Float_t         Ecc4;
  Float_t         Psi5;
  Float_t         Ecc5;
  Float_t         AreaO;
  Float_t         AreaA;
  Float_t         X0;
  Float_t         Y0;
  Float_t         Phi0;
  Float_t         Length;
  Float_t         MeanX;
  Float_t         MeanY;
  Float_t         MeanX2;
  Float_t         MeanY2;
  Float_t         MeanXY;
  Float_t         MeanXSystem;
  Float_t         MeanYSystem;
  Float_t         MeanXA;
  Float_t         MeanYA;
  Float_t         MeanXB;
  Float_t         MeanYB;
  Float_t         PhiA;
  Float_t         ThetaA;
  Float_t         PhiB;
  Float_t         ThetaB;

  // List of branches
  TBranch        *b_Npart;   //!
  TBranch        *b_Ncoll;   //!
  TBranch        *b_Nhard;   //!
  TBranch        *b_B;   //!
  TBranch        *b_BNN;   //!
  TBranch        *b_Ncollpp;   //!
  TBranch        *b_Ncollpn;   //!
  TBranch        *b_Ncollnn;   //!
  TBranch        *b_VarX;   //!
  TBranch        *b_VarY;   //!
  TBranch        *b_VarXY;   //!
  TBranch        *b_NpartA;   //!
  TBranch        *b_NpartB;   //!
  TBranch        *b_Npart0;   //!
  TBranch        *b_AreaW;   //!
  TBranch        *b_Psi1;   //!
  TBranch        *b_Ecc1;   //!
  TBranch        *b_Psi2;   //!
  TBranch        *b_Ecc2;   //!
  TBranch        *b_Psi3;   //!
  TBranch        *b_Ecc3;   //!
  TBranch        *b_Psi4;   //!
  TBranch        *b_Ecc4;   //!
  TBranch        *b_Psi5;   //!
  TBranch        *b_Ecc5;   //!
  TBranch        *b_AreaO;   //!
  TBranch        *b_AreaA;   //!
  TBranch        *b_X0;   //!
  TBranch        *b_Y0;   //!
  TBranch        *b_Phi0;   //!
  TBranch        *b_Length;   //!
  TBranch        *b_MeanX;   //!
  TBranch        *b_MeanY;   //!
  TBranch        *b_MeanX2;   //!
  TBranch        *b_MeanY2;   //!
  TBranch        *b_MeanXY;   //!
  TBranch        *b_MeanXSystem;   //!
  TBranch        *b_MeanYSystem;   //!
  TBranch        *b_MeanXA;   //!
  TBranch        *b_MeanYA;   //!
  TBranch        *b_MeanXB;   //!
  TBranch        *b_MeanYB;   //!
  TBranch        *b_PhiA;   //!
  TBranch        *b_ThetaA;   //!
  TBranch        *b_PhiB;   //!
  TBranch        *b_ThetaB;   //!

  TString         outName;

  GlauberEccReader(TTree *tree=0);
  virtual ~GlauberEccReader();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual void     SetOutputName(TString str) { outName = str; }
};

#endif

#ifdef GlauberEccReader_cxx
GlauberEccReader::GlauberEccReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("merge_glaub_11gev.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("merge_glaub_11gev.root");
      }
      f->GetObject("nt_Au3_Au3",tree);

   }
   Init(tree);
}

GlauberEccReader::~GlauberEccReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GlauberEccReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GlauberEccReader::LoadTree(Long64_t entry)
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

void GlauberEccReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Npart", &Npart, &b_Npart);
   fChain->SetBranchAddress("Ncoll", &Ncoll, &b_Ncoll);
   fChain->SetBranchAddress("Nhard", &Nhard, &b_Nhard);
   fChain->SetBranchAddress("B", &B, &b_B);
   fChain->SetBranchAddress("BNN", &BNN, &b_BNN);
   fChain->SetBranchAddress("Ncollpp", &Ncollpp, &b_Ncollpp);
   fChain->SetBranchAddress("Ncollpn", &Ncollpn, &b_Ncollpn);
   fChain->SetBranchAddress("Ncollnn", &Ncollnn, &b_Ncollnn);
   fChain->SetBranchAddress("VarX", &VarX, &b_VarX);
   fChain->SetBranchAddress("VarY", &VarY, &b_VarY);
   fChain->SetBranchAddress("VarXY", &VarXY, &b_VarXY);
   fChain->SetBranchAddress("NpartA", &NpartA, &b_NpartA);
   fChain->SetBranchAddress("NpartB", &NpartB, &b_NpartB);
   fChain->SetBranchAddress("Npart0", &Npart0, &b_Npart0);
   fChain->SetBranchAddress("AreaW", &AreaW, &b_AreaW);
   fChain->SetBranchAddress("Psi1", &Psi1, &b_Psi1);
   fChain->SetBranchAddress("Ecc1", &Ecc1, &b_Ecc1);
   fChain->SetBranchAddress("Psi2", &Psi2, &b_Psi2);
   fChain->SetBranchAddress("Ecc2", &Ecc2, &b_Ecc2);
   fChain->SetBranchAddress("Psi3", &Psi3, &b_Psi3);
   fChain->SetBranchAddress("Ecc3", &Ecc3, &b_Ecc3);
   fChain->SetBranchAddress("Psi4", &Psi4, &b_Psi4);
   fChain->SetBranchAddress("Ecc4", &Ecc4, &b_Ecc4);
   fChain->SetBranchAddress("Psi5", &Psi5, &b_Psi5);
   fChain->SetBranchAddress("Ecc5", &Ecc5, &b_Ecc5);
   fChain->SetBranchAddress("AreaO", &AreaO, &b_AreaO);
   fChain->SetBranchAddress("AreaA", &AreaA, &b_AreaA);
   fChain->SetBranchAddress("X0", &X0, &b_X0);
   fChain->SetBranchAddress("Y0", &Y0, &b_Y0);
   fChain->SetBranchAddress("Phi0", &Phi0, &b_Phi0);
   fChain->SetBranchAddress("Length", &Length, &b_Length);
   fChain->SetBranchAddress("MeanX", &MeanX, &b_MeanX);
   fChain->SetBranchAddress("MeanY", &MeanY, &b_MeanY);
   fChain->SetBranchAddress("MeanX2", &MeanX2, &b_MeanX2);
   fChain->SetBranchAddress("MeanY2", &MeanY2, &b_MeanY2);
   fChain->SetBranchAddress("MeanXY", &MeanXY, &b_MeanXY);
   fChain->SetBranchAddress("MeanXSystem", &MeanXSystem, &b_MeanXSystem);
   fChain->SetBranchAddress("MeanYSystem", &MeanYSystem, &b_MeanYSystem);
   fChain->SetBranchAddress("MeanXA", &MeanXA, &b_MeanXA);
   fChain->SetBranchAddress("MeanYA", &MeanYA, &b_MeanYA);
   fChain->SetBranchAddress("MeanXB", &MeanXB, &b_MeanXB);
   fChain->SetBranchAddress("MeanYB", &MeanYB, &b_MeanYB);
   fChain->SetBranchAddress("PhiA", &PhiA, &b_PhiA);
   fChain->SetBranchAddress("ThetaA", &ThetaA, &b_ThetaA);
   fChain->SetBranchAddress("PhiB", &PhiB, &b_PhiB);
   fChain->SetBranchAddress("ThetaB", &ThetaB, &b_ThetaB);
   Notify();
}

Bool_t GlauberEccReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GlauberEccReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GlauberEccReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GlauberEccReader_cxx
