//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul 26 19:38:13 2020 by ROOT version 6.21/01
// from TTree mctree/Hadrons tree from MC RHIC models
// found on file: /home/dim2/FLOW5/urqmd_1029930_469.mcpico.root
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

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
   Float_t         bimp;
   Float_t         phi2;
   Float_t         phi3;
   Float_t         ecc2;
   Float_t         ecc3;
   Int_t           npart;
   Int_t           nh;
   Float_t         momx[1690];   //[nh]
   Float_t         momy[1690];   //[nh]
   Float_t         momz[1690];   //[nh]
   Float_t         ene[1690];   //[nh]
   Int_t           hid[1690];   //[nh]
   Int_t           pdg[1690];   //[nh]
   Short_t         charge[1690];   //[nh]

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

   MyClass(TTree *tree=0);
   
   MyClass(const char *file_adress);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);//My func
void Book(void);
void SaveData(const char *outfile); 
bool Fm(double pt,double min,double max);
void add_file(const char *file);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(const char *file_adress) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file

TFile *f = TFile::Open(file_adress);
TTree *tree = (TTree*)f->Get("mctree");
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
