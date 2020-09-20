//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Sep 19 02:34:45 2020 by ROOT version 6.12/06
// from TTree particles/particles
// found on file: /weekly/seluzhen/smash/smash11.5gev/particles_1653164_76.root
//////////////////////////////////////////////////////////

#ifndef smash_h
#define smash_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.
static const int max_nh = 2500;
class smash {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           npart;
   Double_t        impact_b;
   Bool_t          empty_event;
   Int_t           ev;
   Int_t           tcounter;
   Int_t           pdgcode[max_nh];   //[npart]
   Int_t           charge[max_nh];   //[npart]
   Double_t        p0[max_nh];   //[npart]
   Double_t        px[max_nh];   //[npart]
   Double_t        py[max_nh];   //[npart]
   Double_t        pz[max_nh];   //[npart]
   Double_t        t[max_nh];   //[npart]
   Double_t        x[max_nh];   //[npart]
   Double_t        y[max_nh];   //[npart]
   Double_t        z[max_nh];   //[npart]

   // List of branches
   TBranch        *b_npart;   //!
   TBranch        *b_impact_b;   //!
   TBranch        *b_empty_event;   //!
   TBranch        *b_ev;   //!
   TBranch        *b_tcounter;   //!
   TBranch        *b_pdgcode;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_p0;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_t;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!

   smash(TTree *tree=0);
   virtual ~smash();
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

#ifdef smash_cxx
smash::smash(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  //  if (tree == 0) {
  //     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/weekly/seluzhen/smash/smash11.5gev/particles_1653164_76.root");
  //     if (!f || !f->IsOpen()) {
  //        f = new TFile("/weekly/seluzhen/smash/smash11.5gev/particles_1653164_76.root");
  //     }
  //     f->GetObject("particles",tree);

  //  }
  //  Init(tree);
}

smash::~smash()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t smash::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t smash::LoadTree(Long64_t entry)
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

void smash::Init(TTree *tree)
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

   fChain->SetBranchAddress("npart", &npart, &b_npart);
   fChain->SetBranchAddress("impact_b", &impact_b, &b_impact_b);
   fChain->SetBranchAddress("empty_event", &empty_event, &b_empty_event);
   fChain->SetBranchAddress("ev", &ev, &b_ev);
   fChain->SetBranchAddress("tcounter", &tcounter, &b_tcounter);
   fChain->SetBranchAddress("pdgcode", pdgcode, &b_pdgcode);
   fChain->SetBranchAddress("charge", charge, &b_charge);
   fChain->SetBranchAddress("p0", p0, &b_p0);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   fChain->SetBranchAddress("t", t, &b_t);
   fChain->SetBranchAddress("x", x, &b_x);
   fChain->SetBranchAddress("y", y, &b_y);
   fChain->SetBranchAddress("z", z, &b_z);
   Notify();
}

Bool_t smash::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void smash::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t smash::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef smash_cxx
