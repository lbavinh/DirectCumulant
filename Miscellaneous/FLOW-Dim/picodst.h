//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 19 10:53:06 2020 by ROOT version 6.21/01
// from TTree picodst/Pico Dst for flow calculations at MPD
// found on file: /home/dim2/PICO/picodst_123087509_160.root
//////////////////////////////////////////////////////////

#ifndef picodst_h
#define picodst_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <TVector3.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"
#include "TClonesArray.h"

class picodst {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxmcevent = 1;
   static constexpr Int_t kMaxrecoevent = 1;
   static constexpr Int_t kMaxmctracks = 1852;
   static constexpr Int_t kMaxrecotracks = 1185;
   static constexpr Int_t kMaxFHCalModules = 90;

   // Declaration of leaf types
 //PicoDstMCEvent  *mcevent_;
   TVector3        mcevent_PicoDstBaseEvent_fVertex;
   UInt_t          mcevent_TObject_fUniqueID;
   UInt_t          mcevent_TObject_fBits;
   Float_t         mcevent_fB;
   Float_t         mcevent_fPhiRP;
 //PicoDstRecoEvent *recoevent_;
   TVector3        recoevent_PicoDstBaseEvent_fVertex;
   UInt_t          recoevent_TObject_fUniqueID;
   UInt_t          recoevent_TObject_fBits;
   Int_t           mctracks_;
   UInt_t          mctracks_fUniqueID[kMaxmctracks];   //[mctracks_]
   UInt_t          mctracks_fBits[kMaxmctracks];   //[mctracks_]
   TVector3        mctracks_fMom[kMaxmctracks];
   TVector3        mctracks_fDCA[kMaxmctracks];
   Int_t           mctracks_fMotherId[kMaxmctracks];   //[mctracks_]
   Int_t           mctracks_fPdg[kMaxmctracks];   //[mctracks_]
   Float_t         mctracks_fEnergy[kMaxmctracks];   //[mctracks_]
   Int_t           mctracks_fInitialId[kMaxmctracks];   //[mctracks_]
   Int_t           recotracks_;
   UInt_t          recotracks_fUniqueID[kMaxrecotracks];   //[recotracks_]
   UInt_t          recotracks_fBits[kMaxrecotracks];   //[recotracks_]
   TVector3        recotracks_fMom[kMaxrecotracks];
   TVector3        recotracks_fDCA[kMaxrecotracks];
   Int_t           recotracks_fId[kMaxrecotracks];   //[recotracks_]
   Int_t           recotracks_fInitialId[kMaxrecotracks];   //[recotracks_]
   Int_t           recotracks_fTofFlag[kMaxrecotracks];   //[recotracks_]
   Float_t         recotracks_fTpcdEdx[kMaxrecotracks];   //[recotracks_]
   Float_t         recotracks_fTofMass2[kMaxrecotracks];   //[recotracks_]
   Float_t         recotracks_fPidProbPion[kMaxrecotracks];   //[recotracks_]
   Float_t         recotracks_fPidProbKaon[kMaxrecotracks];   //[recotracks_]
   Float_t         recotracks_fPidProbProton[kMaxrecotracks];   //[recotracks_]
   Float_t         recotracks_fChi2[kMaxrecotracks];   //[recotracks_]
   Int_t           recotracks_fNhits[kMaxrecotracks];   //[recotracks_]
   Int_t           recotracks_fNhitsPoss[kMaxrecotracks];   //[recotracks_]
   Short_t         recotracks_fChargeSign[kMaxrecotracks];   //[recotracks_]
   Int_t           FHCalModules_;
   UInt_t          FHCalModules_fUniqueID[kMaxFHCalModules];   //[FHCalModules_]
   UInt_t          FHCalModules_fBits[kMaxFHCalModules];   //[FHCalModules_]
   Float_t         FHCalModules_fEnergy[kMaxFHCalModules];   //[FHCalModules_]

   // List of branches
   TBranch        *b_mcevent_PicoDstBaseEvent_fVertex;   //!
   TBranch        *b_mcevent_TObject_fUniqueID;   //!
   TBranch        *b_mcevent_TObject_fBits;   //!
   TBranch        *b_mcevent_fB;   //!
   TBranch        *b_mcevent_fPhiRP;   //!
   TBranch        *b_recoevent_PicoDstBaseEvent_fVertex;   //!
   TBranch        *b_recoevent_TObject_fUniqueID;   //!
   TBranch        *b_recoevent_TObject_fBits;   //!
   TBranch        *b_mctracks_;   //!
   TBranch        *b_mctracks_fUniqueID;   //!
   TBranch        *b_mctracks_fBits;   //!
   TBranch        *b_mctracks_fMom;   //!
   TBranch        *b_mctracks_fDCA;   //!
   TBranch        *b_mctracks_fMotherId;   //!
   TBranch        *b_mctracks_fPdg;   //!
   TBranch        *b_mctracks_fEnergy;   //!
   TBranch        *b_mctracks_fInitialId;   //!
   TBranch        *b_recotracks_;   //!
   TBranch        *b_recotracks_fUniqueID;   //!
   TBranch        *b_recotracks_fBits;   //!
   TBranch        *b_recotracks_fMom;   //!
   TBranch        *b_recotracks_fDCA;   //!
   TBranch        *b_recotracks_fId;   //!
   TBranch        *b_recotracks_fInitialId;   //!
   TBranch        *b_recotracks_fTofFlag;   //!
   TBranch        *b_recotracks_fTpcdEdx;   //!
   TBranch        *b_recotracks_fTofMass2;   //!
   TBranch        *b_recotracks_fPidProbPion;   //!
   TBranch        *b_recotracks_fPidProbKaon;   //!
   TBranch        *b_recotracks_fPidProbProton;   //!
   TBranch        *b_recotracks_fChi2;   //!
   TBranch        *b_recotracks_fNhits;   //!
   TBranch        *b_recotracks_fNhitsPoss;   //!
   TBranch        *b_recotracks_fChargeSign;   //!
   TBranch        *b_FHCalModules_;   //!
   TBranch        *b_FHCalModules_fUniqueID;   //!
   TBranch        *b_FHCalModules_fBits;   //!
   TBranch        *b_FHCalModules_fEnergy;   //!

   picodst(TTree *tree=0);
    picodst(const char *file_adress);
   virtual ~picodst();
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
};

#endif

#ifdef picodst_cxx
picodst::picodst(const char *file_adress) : fChain(0)
{
   // if parameter tree is not specified (or zero), connect the file

   TFile *f = TFile::Open(file_adress);
   TTree *tree = (TTree *)f->Get("picodst");
   Init(tree);
   if (tree == 0)
   {
      cout << "tree not found" << endl;
   }
}


picodst::~picodst()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t picodst::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t picodst::LoadTree(Long64_t entry)
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

void picodst::Init(TTree *tree)
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

   fChain->SetBranchAddress("mcevent.PicoDstBaseEvent.fVertex", &mcevent_PicoDstBaseEvent_fVertex, &b_mcevent_PicoDstBaseEvent_fVertex);
   fChain->SetBranchAddress("mcevent.TObject.fUniqueID", &mcevent_TObject_fUniqueID, &b_mcevent_TObject_fUniqueID);
   fChain->SetBranchAddress("mcevent.TObject.fBits", &mcevent_TObject_fBits, &b_mcevent_TObject_fBits);
   fChain->SetBranchAddress("mcevent.fB", &mcevent_fB, &b_mcevent_fB);
   fChain->SetBranchAddress("mcevent.fPhiRP", &mcevent_fPhiRP, &b_mcevent_fPhiRP);
   fChain->SetBranchAddress("recoevent.PicoDstBaseEvent.fVertex", &recoevent_PicoDstBaseEvent_fVertex, &b_recoevent_PicoDstBaseEvent_fVertex);
   fChain->SetBranchAddress("recoevent.TObject.fUniqueID", &recoevent_TObject_fUniqueID, &b_recoevent_TObject_fUniqueID);
   fChain->SetBranchAddress("recoevent.TObject.fBits", &recoevent_TObject_fBits, &b_recoevent_TObject_fBits);
   fChain->SetBranchAddress("mctracks", &mctracks_, &b_mctracks_);
   fChain->SetBranchAddress("mctracks.fUniqueID", mctracks_fUniqueID, &b_mctracks_fUniqueID);
   fChain->SetBranchAddress("mctracks.fBits", mctracks_fBits, &b_mctracks_fBits);
   fChain->SetBranchAddress("mctracks.fMom", mctracks_fMom, &b_mctracks_fMom);
   fChain->SetBranchAddress("mctracks.fDCA", mctracks_fDCA, &b_mctracks_fDCA);
   fChain->SetBranchAddress("mctracks.fMotherId", mctracks_fMotherId, &b_mctracks_fMotherId);
   fChain->SetBranchAddress("mctracks.fPdg", mctracks_fPdg, &b_mctracks_fPdg);
   fChain->SetBranchAddress("mctracks.fEnergy", mctracks_fEnergy, &b_mctracks_fEnergy);
   fChain->SetBranchAddress("mctracks.fInitialId", mctracks_fInitialId, &b_mctracks_fInitialId);
   fChain->SetBranchAddress("recotracks", &recotracks_, &b_recotracks_);
   fChain->SetBranchAddress("recotracks.fUniqueID", recotracks_fUniqueID, &b_recotracks_fUniqueID);
   fChain->SetBranchAddress("recotracks.fBits", recotracks_fBits, &b_recotracks_fBits);
   fChain->SetBranchAddress("recotracks.fMom", recotracks_fMom, &b_recotracks_fMom);
   fChain->SetBranchAddress("recotracks.fDCA", recotracks_fDCA, &b_recotracks_fDCA);
   fChain->SetBranchAddress("recotracks.fId", recotracks_fId, &b_recotracks_fId);
   fChain->SetBranchAddress("recotracks.fInitialId", recotracks_fInitialId, &b_recotracks_fInitialId);
   fChain->SetBranchAddress("recotracks.fTofFlag", recotracks_fTofFlag, &b_recotracks_fTofFlag);
   fChain->SetBranchAddress("recotracks.fTpcdEdx", recotracks_fTpcdEdx, &b_recotracks_fTpcdEdx);
   fChain->SetBranchAddress("recotracks.fTofMass2", recotracks_fTofMass2, &b_recotracks_fTofMass2);
   fChain->SetBranchAddress("recotracks.fPidProbPion", recotracks_fPidProbPion, &b_recotracks_fPidProbPion);
   fChain->SetBranchAddress("recotracks.fPidProbKaon", recotracks_fPidProbKaon, &b_recotracks_fPidProbKaon);
   fChain->SetBranchAddress("recotracks.fPidProbProton", recotracks_fPidProbProton, &b_recotracks_fPidProbProton);
   fChain->SetBranchAddress("recotracks.fChi2", recotracks_fChi2, &b_recotracks_fChi2);
   fChain->SetBranchAddress("recotracks.fNhits", recotracks_fNhits, &b_recotracks_fNhits);
   fChain->SetBranchAddress("recotracks.fNhitsPoss", recotracks_fNhitsPoss, &b_recotracks_fNhitsPoss);
   fChain->SetBranchAddress("recotracks.fChargeSign", recotracks_fChargeSign, &b_recotracks_fChargeSign);
   fChain->SetBranchAddress("FHCalModules", &FHCalModules_, &b_FHCalModules_);
   fChain->SetBranchAddress("FHCalModules.fUniqueID", FHCalModules_fUniqueID, &b_FHCalModules_fUniqueID);
   fChain->SetBranchAddress("FHCalModules.fBits", FHCalModules_fBits, &b_FHCalModules_fBits);
   fChain->SetBranchAddress("FHCalModules.fEnergy", FHCalModules_fEnergy, &b_FHCalModules_fEnergy);
   Notify();
}

Bool_t picodst::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void picodst::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t picodst::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef picodst_cxx
