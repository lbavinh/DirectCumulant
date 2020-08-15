//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul 26 00:23:21 2020 by ROOT version 5.34/19
// from TTree mctree/Hadrons tree from MC RHIC models
// found on file: urqmd_1033721_1.mcpico.root
//////////////////////////////////////////////////////////

#ifndef FlowANA_h
#define FlowANA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class FlowANA {
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
   Float_t         momx[1700];   //[nh] momentum px
   Float_t         momy[1700];   //[nh] momentum py
   Float_t         momz[1700];   //[nh] momentum pz
   Float_t         ene[1700];    //[nh] energy of particle
   Int_t           hid[1700];    //[nh] 
   Int_t           pdg[1700];    //[nh] particle ID
   Short_t         charge[1700]; //[nh] charge of particle

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

   FlowANA(TTree *tree=0);
   virtual ~FlowANA();
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
};

#endif

#ifdef FlowANA_cxx
FlowANA::FlowANA(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  //  if (tree == 0) {
  //     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("urqmd_1033721_1.mcpico.root");
  //     if (!f || !f->IsOpen()) {
  //        f = new TFile("urqmd_1033721_1.mcpico.root");
  //     }
  //     f->GetObject("mctree",tree);

  //  }
  //  Init(tree);
}

FlowANA::~FlowANA()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FlowANA::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FlowANA::LoadTree(Long64_t entry)
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

void FlowANA::Init(TTree *tree)
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
   if (!fChain) return;
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
