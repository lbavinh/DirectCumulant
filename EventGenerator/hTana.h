//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov  6 10:11:51 2010 by ROOT version 5.17/01
// from TTree htree/Hadron EMC + TOF tree
// found on file: /phenix/gh/data73/flow/arkadij/run4/v2AuAuMy_122223_0.root
//////////////////////////////////////////////////////////

#ifndef hTana_h
#define hTana_h
#include <TRandom2.h>
#include <time.h>
#include <stdio.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#define MAXNH 1500
class hTana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Float_t         rp;
   Int_t           nh;
   Float_t         b;
   Float_t         pt[MAXNH];   //[nh]
   Float_t         phi0[MAXNH];   //[nh]
   Float_t         eta[MAXNH];   //[nh]


   // List of branches
   TBranch        *b_rp;   //!
   TBranch        *b_nh;   //!
   TBranch        *b_b;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_phi0;   //!
   TBranch        *b_eta;   //!


   hTana(TTree *tree=0);
   virtual ~hTana();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);




   // additional member functions
   void ana_init(TString outfile);
   void v2gen(int nevent,double mult);
   void book_hist(TString outfile);
   void ana_end(void);

};

#endif

#ifdef hTana_cxx
hTana::hTana(TTree *tree)
{

   if(tree)  Init(tree);
}

hTana::~hTana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t hTana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t hTana::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void hTana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normaly not necessary to make changes to the generated
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

Bool_t hTana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void hTana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t hTana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef hTana_cxx
