//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 19 14:30:39 2019 by ROOT version 6.18/02
// from TChain mctree/
//////////////////////////////////////////////////////////

#ifndef FlowANA_h
#define FlowANA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#define MAX_TRACKS 10000

// Header file for the classes stored in the TTree if any.

class FlowANA {
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
   Float_t         momx[MAX_TRACKS];   //[nh]
   Float_t         momy[MAX_TRACKS];   //[nh]
   Float_t         momz[MAX_TRACKS];   //[nh]
   Float_t         ene[MAX_TRACKS];   //[nh]
   Int_t           hid[MAX_TRACKS];   //[nh]
   Int_t           pdg[MAX_TRACKS];   //[nh]
   Short_t         charge[MAX_TRACKS];   //[nh]

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
   virtual void     ana_init(const char *outfile);
   virtual void     loop_a_file(const char *file);
   virtual void     ana_end();
   virtual void     book_hist(const char *outfile);
   virtual void     ana_event(int jentry, int ientry);
   virtual int      GetCentrality10_RefMult(double refMult);
   virtual int      GetCentrality10_RefMultPHENIX(double refMult);
   virtual int      GetCentrality10_Bimp(float bimp);
   virtual int      GetCentrality10_BimpExp(float bimp);
};

#endif

#ifdef FlowANA_cxx
FlowANA::FlowANA(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("mctree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("mctree","");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_1.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_10.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_100.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_101.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_102.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_103.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_104.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_105.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_106.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_107.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_108.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_109.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_11.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_110.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_111.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_112.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_113.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_114.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_115.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_116.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_117.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_118.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_119.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_12.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_120.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_121.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_122.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_123.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_124.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_125.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_126.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_127.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_128.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_129.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_13.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_130.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_131.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_132.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_133.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_134.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_135.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_136.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_137.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_138.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_139.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_14.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_140.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_141.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_142.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_143.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_144.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_145.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_146.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_147.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_148.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_149.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_15.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_150.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_151.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_152.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_153.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_154.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_155.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_156.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_157.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_158.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_159.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_16.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_160.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_161.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_162.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_163.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_164.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_165.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_166.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_167.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_168.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_169.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_17.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_170.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_171.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_172.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_173.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_174.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_175.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_176.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_177.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_178.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_179.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_18.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_180.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_181.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_182.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_183.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_184.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_185.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_186.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_187.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_188.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_189.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_19.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_190.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_191.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_192.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_193.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_194.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_195.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_196.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_197.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_198.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_199.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_2.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_20.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_200.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_201.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_202.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_203.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_204.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_205.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_206.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_207.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_208.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_209.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_21.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_210.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_211.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_212.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_213.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_214.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_215.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_216.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_217.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_218.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_219.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_22.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_220.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_221.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_222.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_223.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_224.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_225.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_226.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_227.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_228.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_229.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_23.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_230.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_231.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_232.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_233.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_234.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_235.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_236.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_237.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_238.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_239.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_24.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_240.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_241.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_242.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_243.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_244.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_245.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_246.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_247.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_248.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_249.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_25.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_250.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_251.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_252.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_253.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_254.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_255.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_256.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_257.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_258.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_259.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_26.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_260.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_261.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_262.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_263.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_264.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_265.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_266.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_267.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_268.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_269.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_27.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_270.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_271.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_272.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_273.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_274.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_275.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_276.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_277.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_278.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_279.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_28.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_280.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_281.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_282.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_283.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_284.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_285.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_286.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_287.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_288.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_289.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_29.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_290.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_291.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_292.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_293.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_294.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_295.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_296.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_297.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_3.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_30.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_309.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_31.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_310.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_311.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_312.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_313.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_314.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_315.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_316.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_317.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_318.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_319.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_32.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_320.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_321.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_322.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_323.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_324.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_325.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_326.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_327.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_328.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_329.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_33.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_330.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_331.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_332.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_333.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_334.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_335.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_336.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_337.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_338.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_339.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_34.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_340.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_341.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_342.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_343.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_344.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_345.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_346.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_347.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_348.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_349.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_35.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_350.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_351.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_352.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_353.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_354.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_355.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_356.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_357.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_358.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_359.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_36.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_360.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_361.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_362.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_363.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_364.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_365.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_366.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_367.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_368.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_369.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_37.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_370.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_371.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_372.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_373.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_374.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_375.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_376.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_377.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_378.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_379.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_38.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_380.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_381.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_382.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_383.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_384.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_385.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_386.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_387.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_388.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_389.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_39.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_390.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_391.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_392.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_393.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_394.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_395.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_396.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_397.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_398.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_399.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_4.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_40.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_400.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_401.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_402.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_403.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_404.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_405.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_406.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_407.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_408.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_409.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_41.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_410.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_411.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_412.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_413.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_414.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_415.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_416.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_417.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_418.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_419.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_42.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_420.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_421.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_422.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_423.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_424.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_425.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_426.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_427.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_428.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_429.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_43.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_430.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_431.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_432.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_433.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_434.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_435.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_436.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_437.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_438.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_439.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_44.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_440.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_441.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_442.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_443.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_444.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_445.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_446.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_447.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_448.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_449.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_45.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_450.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_451.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_452.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_453.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_454.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_455.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_456.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_457.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_458.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_459.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_46.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_460.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_461.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_462.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_463.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_464.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_465.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_466.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_467.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_468.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_469.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_47.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_470.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_471.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_472.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_473.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_474.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_475.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_476.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_477.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_478.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_479.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_48.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_480.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_481.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_482.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_483.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_484.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_485.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_486.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_487.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_488.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_489.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_49.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_490.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_491.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_492.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_493.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_494.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_495.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_496.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_497.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_498.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_499.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_5.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_50.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_500.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_51.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_52.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_53.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_54.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_55.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_56.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_57.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_58.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_59.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_6.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_60.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_61.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_62.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_63.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_64.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_65.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_66.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_67.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_68.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_69.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_7.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_70.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_71.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_72.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_73.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_74.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_75.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_76.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_77.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_78.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_79.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_8.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_80.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_81.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_82.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_83.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_84.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_85.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_86.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_87.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_88.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_89.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_9.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_90.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_91.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_92.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_93.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_94.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_95.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_96.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_97.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_98.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90259510_99.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_1000.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_501.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_502.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_503.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_504.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_505.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_506.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_507.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_508.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_509.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_510.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_511.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_512.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_513.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_514.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_515.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_516.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_517.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_518.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_519.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_520.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_521.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_522.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_523.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_524.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_525.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_526.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_527.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_528.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_529.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_530.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_531.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_532.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_533.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_534.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_535.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_536.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_537.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_538.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_539.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_540.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_541.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_542.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_543.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_544.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_545.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_546.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_547.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_548.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_549.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_550.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_551.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_552.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_553.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_554.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_555.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_556.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_557.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_558.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_559.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_560.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_561.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_562.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_563.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_564.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_565.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_566.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_567.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_568.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_569.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_570.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_571.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_572.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_573.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_574.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_575.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_576.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_577.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_578.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_579.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_580.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_581.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_582.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_583.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_584.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_585.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_586.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_587.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_588.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_589.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_590.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_591.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_592.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_593.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_594.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_595.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_596.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_597.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_598.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_599.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_600.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_601.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_602.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_603.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_604.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_605.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_606.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_607.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_608.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_609.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_610.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_611.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_612.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_613.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_614.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_615.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_616.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_617.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_618.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_619.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_620.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_621.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_622.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_623.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_624.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_625.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_626.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_627.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_628.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_629.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_630.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_631.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_632.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_633.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_634.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_635.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_636.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_637.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_638.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_639.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_640.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_641.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_642.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_643.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_644.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_645.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_646.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_647.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_648.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_649.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_650.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_651.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_652.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_653.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_654.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_655.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_656.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_657.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_658.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_659.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_660.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_661.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_662.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_663.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_664.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_665.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_666.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_667.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_668.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_669.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_670.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_671.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_672.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_673.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_674.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_675.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_676.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_677.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_678.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_679.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_680.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_681.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_682.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_683.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_684.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_685.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_686.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_687.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_688.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_689.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_690.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_691.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_692.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_693.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_694.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_695.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_696.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_697.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_698.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_699.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_700.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_701.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_702.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_703.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_704.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_705.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_706.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_707.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_708.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_709.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_710.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_711.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_712.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_713.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_714.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_715.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_716.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_717.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_718.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_719.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_720.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_721.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_722.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_723.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_724.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_725.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_726.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_727.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_728.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_729.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_730.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_731.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_732.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_733.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_734.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_735.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_736.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_737.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_738.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_739.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_740.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_741.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_742.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_743.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_744.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_745.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_746.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_747.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_748.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_749.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_750.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_751.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_752.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_753.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_754.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_755.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_756.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_757.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_758.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_759.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_761.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_762.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_763.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_764.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_765.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_766.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_767.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_768.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_769.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_770.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_771.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_772.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_773.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_774.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_775.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_776.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_777.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_778.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_779.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_780.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_781.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_782.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_783.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_784.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_785.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_786.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_787.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_788.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_789.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_790.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_791.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_792.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_793.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_794.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_795.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_796.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_797.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_798.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_799.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_800.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_801.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_802.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_803.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_804.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_805.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_806.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_807.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_808.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_809.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_810.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_811.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_812.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_813.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_814.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_815.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_816.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_817.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_818.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_819.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_820.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_821.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_822.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_823.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_824.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_825.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_826.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_827.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_828.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_829.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_830.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_831.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_832.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_833.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_834.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_835.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_836.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_837.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_838.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_839.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_840.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_841.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_842.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_843.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_844.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_845.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_846.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_847.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_848.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_849.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_850.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_851.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_852.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_853.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_854.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_855.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_856.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_857.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_858.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_859.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_860.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_861.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_862.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_863.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_864.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_865.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_866.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_867.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_868.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_869.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_870.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_871.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_872.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_873.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_874.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_875.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_876.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_877.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_878.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_879.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_880.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_881.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_882.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_883.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_884.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_885.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_886.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_887.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_888.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_889.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_890.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_891.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_892.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_893.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_894.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_895.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_896.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_897.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_898.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_899.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_900.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_901.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_902.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_903.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_904.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_905.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_906.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_907.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_908.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_909.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_910.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_911.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_912.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_913.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_914.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_915.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_916.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_917.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_918.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_919.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_920.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_921.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_922.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_923.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_924.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_925.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_926.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_927.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_928.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_929.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_930.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_931.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_932.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_933.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_934.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_935.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_936.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_937.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_938.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_939.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_940.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_941.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_942.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_943.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_944.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_945.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_946.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_947.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_948.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_949.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_950.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_951.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_952.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_953.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_954.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_955.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_956.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_957.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_958.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_959.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_960.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_961.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_966.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_971.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_974.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_975.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_976.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_977.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_978.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_979.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_980.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_981.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_982.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_983.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_984.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_985.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_986.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_987.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_988.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_989.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_990.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_991.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_992.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_993.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_994.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_995.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_996.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_997.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_998.mctree.root/mctree");
      chain->Add("/mnt/pool/nica/6/parfenovpeter/SimData/UrQMD/OUT/UrQMD_mcpico_11gev/gsi/urqmd_90272588_999.mctree.root/mctree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
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
