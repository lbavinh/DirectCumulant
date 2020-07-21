//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul  7 13:08:48 2020 by ROOT version 6.19/01
// from TTree htree/Hadron EMC + TOF tree
// found on file: v2hadron.root
//////////////////////////////////////////////////////////

#ifndef hVana_h
#define hVana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.

class hVana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         rp;
   Int_t           nh;
   Float_t         b;
   Float_t         pt[1500];   //[nh]
   Float_t         phi0[1500];   //[nh]
   Float_t         eta[1500];   //[nh]

   // List of branches
   TBranch        *b_rp;   //!
   TBranch        *b_nh;   //!
   TBranch        *b_b;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_phi0;   //!
   TBranch        *b_eta;   //!

   hVana(TTree *tree=0);
   virtual ~hVana();
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
   void Ana_end();
   void Ana_event();
   TComplex Qstar(TComplex Q);
   Double_t CalCor22(TComplex Q2, Double_t M, Double_t w2);
   Double_t CalCor24(TComplex Q2, TComplex Q4, Double_t M, Double_t w4);
   Double_t CalRedCor22(TComplex Q2, TComplex p2, Double_t M, Double_t mp, 
                        Double_t mq, Double_t wred2);
   Double_t CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2,
                        TComplex q2, TComplex q4, Double_t M,
                        Double_t mp, Double_t mq, Double_t wred2);                  
};

#endif

// phần code kẹp giữa #ifdef hVana_cxx và #endif chỉ compile khi hVana_cxx
// được xác định (#define hVana_cxx trong hVana.C)

#ifdef hVana_cxx
hVana::hVana(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("v2hadron.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("v2hadron.root");
      }
      f->GetObject("htree",tree);

   }
   Init(tree);
}

hVana::~hVana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t hVana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t hVana::LoadTree(Long64_t entry)
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

void hVana::Init(TTree *tree)
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

   fChain->SetBranchAddress("rp", &rp, &b_rp);
   fChain->SetBranchAddress("nh", &nh, &b_nh);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("pt", pt, &b_pt);
   fChain->SetBranchAddress("phi0", phi0, &b_phi0);
   fChain->SetBranchAddress("eta", eta, &b_eta);
   Notify();
}

Bool_t hVana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void hVana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t hVana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef hVana_cxx
