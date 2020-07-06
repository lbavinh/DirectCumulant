//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul  3 01:14:31 2020 by ROOT version 6.19/01
// from TTree htree/Hadron EMC + TOF tree
// found on file: v2hadron.root
//////////////////////////////////////////////////////////

#ifndef hVana_h
#define hVana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TProfile.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TPave.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TString.h"
#include "TLatex.h"
#include "TComplex.h"
#include "Riostream.h"

// Header file for the classes stored in the TTree if any.

class hVana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         rp; // reaction plane angle
   Int_t           nh; // number of hadrons
   Float_t         pt[543];   //[nh]
   Float_t         phi0[543];   //[nh]

   // List of branches
   TBranch        *b_rp;   //!
   TBranch        *b_nh;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_phi0;   //!

   hVana(TTree *tree=0);
   virtual ~hVana();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   // additional member functions
   void ana_event(int jevent, int ievent);
   void ana_init(char *outfile);
   void loop_a_file(char *file);
   void ana_end();
   void book_hist(char *outfile);
   void CalculateQvectors(Int_t nParticles, Float_t *angles);
   void GenericFormulas(Int_t nParticles, Float_t *angles);
   TComplex Q(Int_t n, Int_t p);
   TComplex Two(Int_t n1, Int_t n2);
   TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4);
   float TwoNestedLoops(Int_t n1,Int_t n2, Int_t nPOI, Int_t nRFP, float *anglePOI, float *angleRFP);
   float FourNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4, Int_t nPOI, Int_t nRFP, float *anglePOI, float *angleRFP);
};

#endif

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
   fChain->SetBranchAddress("pt", pt, &b_pt);
   fChain->SetBranchAddress("phi0", phi0, &b_phi0);
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
