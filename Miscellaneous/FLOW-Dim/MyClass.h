//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul  2 17:16:23 2020 by ROOT version 6.21/01
// from TTree tree/My Tree
// found on file: /home/dim2/FLOW/FILE.root
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

#include <TGraph.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <fstream>

// Header file for the classes stored in the TTree if any.

class MyClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EVENT;
   Int_t           Nch;
   Float_t         psiRP;
   Float_t         phi[1000];   //[Nch]
   Float_t         pt[1000];   //[Nch]
   Float_t         dPHI[1000];   //[Nch]

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_Nch;   //!
   TBranch        *b_psi_RP;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_dPHI;   //!

   MyClass(TTree *tree=0);
   MyClass(const char *file_adress);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

//My func
void Book(void);
void SaveData(const char *outfile); 
bool Fm(double pt,double min,double max);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(const char *file_adress) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   /*if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/dim2/FLOW/FILE.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/dim2/FLOW/FILE.root");
      }
      f->GetObject("tree",tree);

   }*/
TFile *f = TFile::Open(file_adress);
TTree *tree = (TTree*)f->Get("tree");
Init(tree);
if (tree == 0) {cout <<"tree found"<<endl;}
}

MyClass::~MyClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass::LoadTree(Long64_t entry)
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

void MyClass::Init(TTree *tree)
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

   fChain->SetBranchAddress("EVENT", &EVENT, &b_event);
   fChain->SetBranchAddress("Nch", &Nch, &b_Nch);
   fChain->SetBranchAddress("psiRP", &psiRP, &b_psi_RP);
   fChain->SetBranchAddress("phi", phi, &b_phi);
   fChain->SetBranchAddress("pt", pt, &b_pt);
   fChain->SetBranchAddress("dPHI", dPHI, &b_dPHI);
   Notify();
}

Bool_t MyClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyClass_cxx
