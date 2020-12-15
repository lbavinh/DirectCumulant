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
#define MAXNH 300
class hTana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           run;
   Float_t         bbcz;
   Float_t         centclock;
   Float_t         rp10;
   Float_t         rp11;
   Float_t         rp12;
   Float_t         bbcQY10;
   Float_t         bbcQY11;
   Float_t         bbcQY12;
   Float_t         bbcQX10;
   Float_t         bbcQX11;
   Float_t         bbcQX12;
   Int_t           nh;
   Float_t         p[MAXNH];   //[nh]
   Short_t         charge[MAXNH];   //[nh]
   Float_t         phi0[MAXNH];   //[nh]
   Float_t         the0[MAXNH];   //[nh]
   Short_t         dcarm[MAXNH];   //[nh]
   Short_t         sect[MAXNH];   //[nh]
   Short_t         inemc[MAXNH];   //[nh]
   Short_t         intof[MAXNH];   //[nh]
   Float_t         isPi[MAXNH];   //[nh]
   Float_t         isP[MAXNH];   //[nh]
   Float_t         isK[MAXNH];   //[nh]
   Float_t         m2tof[MAXNH];   //[nh]
   Float_t         temc[MAXNH];   //[nh]
   Float_t         plemc[MAXNH];   //[nh]
   Float_t         ecent[MAXNH];   //[nh]
   Short_t         twrid[MAXNH];   //[nh]
   Short_t         n0[MAXNH];   //[nh]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_bbcz;   //!
   TBranch        *b_centclock;   //!
   TBranch        *b_rp10;   //!
   TBranch        *b_rp11;   //!
   TBranch        *b_rp12;   //!
   TBranch        *b_bbcQY10;   //!
   TBranch        *b_bbcQY11;   //!
   TBranch        *b_bbcQY12;   //!
   TBranch        *b_bbcQX10;   //!
   TBranch        *b_bbcQX11;   //!
   TBranch        *b_bbcQX12;   //!
   TBranch        *b_nh;   //!
   TBranch        *b_p;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_phi0;   //!
   TBranch        *b_the0;   //!
   TBranch        *b_dcarm;   //!
   TBranch        *b_sect;   //!
   TBranch        *b_inemc;   //!
   TBranch        *b_intof;   //!
   TBranch        *b_isPi;   //!
   TBranch        *b_isP;   //!
   TBranch        *b_isK;   //!
   TBranch        *b_m2tof;   //!
   TBranch        *b_temc;   //!
   TBranch        *b_plemc;   //!
   TBranch        *b_ecent;   //!
   TBranch        *b_twrid;   //!
   TBranch        *b_n0;   //!

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
   void ana_init(char *outfile);
   void v2gen(int nevent,int mult,int dmult);
   void book_hist(char *outfile);
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

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("bbcz", &bbcz, &b_bbcz);
   fChain->SetBranchAddress("centclock", &centclock, &b_centclock);
   fChain->SetBranchAddress("rp10", &rp10, &b_rp10);
   fChain->SetBranchAddress("rp11", &rp11, &b_rp11);
   fChain->SetBranchAddress("rp12", &rp12, &b_rp12);
   fChain->SetBranchAddress("bbcQY10", &bbcQY10, &b_bbcQY10);
   fChain->SetBranchAddress("bbcQY11", &bbcQY11, &b_bbcQY11);
   fChain->SetBranchAddress("bbcQY12", &bbcQY12, &b_bbcQY12);
   fChain->SetBranchAddress("bbcQX10", &bbcQX10, &b_bbcQX10);
   fChain->SetBranchAddress("bbcQX11", &bbcQX11, &b_bbcQX11);
   fChain->SetBranchAddress("bbcQX12", &bbcQX12, &b_bbcQX12);
   fChain->SetBranchAddress("nh", &nh, &b_nh);
   fChain->SetBranchAddress("p", p, &b_p);
   fChain->SetBranchAddress("charge", charge, &b_charge);
   fChain->SetBranchAddress("phi0", phi0, &b_phi0);
   fChain->SetBranchAddress("the0", the0, &b_the0);
   fChain->SetBranchAddress("dcarm", dcarm, &b_dcarm);
   fChain->SetBranchAddress("sect", sect, &b_sect);
   fChain->SetBranchAddress("inemc", inemc, &b_inemc);
   fChain->SetBranchAddress("intof", intof, &b_intof);
   fChain->SetBranchAddress("isPi", isPi, &b_isPi);
   fChain->SetBranchAddress("isP", isP, &b_isP);
   fChain->SetBranchAddress("isK", isK, &b_isK);
   fChain->SetBranchAddress("m2tof", m2tof, &b_m2tof);
   fChain->SetBranchAddress("temc", temc, &b_temc);
   fChain->SetBranchAddress("plemc", plemc, &b_plemc);
   fChain->SetBranchAddress("ecent", ecent, &b_ecent);
   fChain->SetBranchAddress("twrid", twrid, &b_twrid);
   fChain->SetBranchAddress("n0", n0, &b_n0);
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
