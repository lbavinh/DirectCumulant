//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Dec  5 23:26:00 2020 by ROOT version 6.19/01
// from TTree events/event tree
// found on file: ./output/glissando.root
//////////////////////////////////////////////////////////

#ifndef Glissando_h
#define Glissando_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Glissando {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         nwA;
   Float_t         nwB;
   Float_t         nwAB;
   Float_t         nbin;
   Float_t         npa;
   Float_t         b;
   Float_t         size;
   Float_t         ep1s;
   Float_t         eps;
   Float_t         ep3s;
   Float_t         ep4s;
   Float_t         ep5s;
   Float_t         ep6s;
   Float_t         phir1;
   Float_t         phir;
   Float_t         phir3;
   Float_t         phir4;
   Float_t         phir5;
   Float_t         phir6;
   Float_t         xx;
   Float_t         yy;
   Float_t         wfqA;
   Float_t         wfqB;
   Float_t         wfq;

   // List of branches
   TBranch        *b_nwA;   //!
   TBranch        *b_nwB;   //!
   TBranch        *b_nwAB;   //!
   TBranch        *b_nbin;   //!
   TBranch        *b_npa;   //!
   TBranch        *b_b;   //!
   TBranch        *b_size;   //!
   TBranch        *b_ep1s;   //!
   TBranch        *b_eps;   //!
   TBranch        *b_ep3s;   //!
   TBranch        *b_ep4s;   //!
   TBranch        *b_ep5s;   //!
   TBranch        *b_ep6s;   //!
   TBranch        *b_phir1;   //!
   TBranch        *b_phir;   //!
   TBranch        *b_phir3;   //!
   TBranch        *b_phir4;   //!
   TBranch        *b_phir5;   //!
   TBranch        *b_phir6;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_wfqA;   //!
   TBranch        *b_wfqB;   //!
   TBranch        *b_wfq;   //!

   TString         outName;

   Glissando(TTree *tree=0);
   virtual ~Glissando();
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

#ifdef Glissando_cxx
Glissando::Glissando(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("./output/glissando.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("./output/glissando.root");
      }
      f->GetObject("events",tree);

   }
   Init(tree);
}

Glissando::~Glissando()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Glissando::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Glissando::LoadTree(Long64_t entry)
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

void Glissando::Init(TTree *tree)
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

   fChain->SetBranchAddress("nwA", &nwA, &b_nwA);
   fChain->SetBranchAddress("nwB", &nwB, &b_nwB);
   fChain->SetBranchAddress("nwAB", &nwAB, &b_nwAB);
   fChain->SetBranchAddress("nbin", &nbin, &b_nbin);
   fChain->SetBranchAddress("npa", &npa, &b_npa);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("size", &size, &b_size);
   fChain->SetBranchAddress("ep1s", &ep1s, &b_ep1s);
   fChain->SetBranchAddress("eps", &eps, &b_eps);
   fChain->SetBranchAddress("ep3s", &ep3s, &b_ep3s);
   fChain->SetBranchAddress("ep4s", &ep4s, &b_ep4s);
   fChain->SetBranchAddress("ep5s", &ep5s, &b_ep5s);
   fChain->SetBranchAddress("ep6s", &ep6s, &b_ep6s);
   fChain->SetBranchAddress("phir1", &phir1, &b_phir1);
   fChain->SetBranchAddress("phir", &phir, &b_phir);
   fChain->SetBranchAddress("phir3", &phir3, &b_phir3);
   fChain->SetBranchAddress("phir4", &phir4, &b_phir4);
   fChain->SetBranchAddress("phir5", &phir5, &b_phir5);
   fChain->SetBranchAddress("phir6", &phir6, &b_phir6);
   fChain->SetBranchAddress("xx", &xx, &b_x);
   fChain->SetBranchAddress("yy", &yy, &b_y);
   fChain->SetBranchAddress("wfqA", &wfqA, &b_wfqA);
   fChain->SetBranchAddress("wfqB", &wfqB, &b_wfqB);
   fChain->SetBranchAddress("wfq", &wfq, &b_wfq);
   Notify();
}

Bool_t Glissando::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Glissando::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Glissando::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Glissando_cxx
