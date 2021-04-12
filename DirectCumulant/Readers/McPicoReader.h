#ifndef MCPICO_READER_H
#define MCPICO_READER_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <IReader.h>
#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>
// Header file for the classes stored in the TTree if any.

class McPicoReader : virtual public IReader
{
public:
  TChain *fChain;  //!pointer to the analyzed TTree or TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Float_t bimp;
  Float_t phi2;
  Float_t phi3;
  Float_t ecc2;
  Float_t ecc3;
  Int_t npart;
  Int_t nh;
  Float_t momx[10000];   //[nh]
  Float_t momy[10000];   //[nh]
  Float_t momz[10000];   //[nh]
  Float_t ene[10000];    //[nh]
  Int_t hid[10000];      //[nh]
  Int_t pdg[10000];      //[nh]
  Short_t charge[10000]; //[nh]

  // List of branches
  TBranch *b_bimp;   //!
  TBranch *b_phi2;   //!
  TBranch *b_phi3;   //!
  TBranch *b_ecc2;   //!
  TBranch *b_ecc3;   //!
  TBranch *b_npart;  //!
  TBranch *b_nh;     //!
  TBranch *b_momx;   //!
  TBranch *b_momy;   //!
  TBranch *b_momz;   //!
  TBranch *b_ene;    //!
  TBranch *b_hid;    //!
  TBranch *b_pdg;    //!
  TBranch *b_charge; //!

  McPicoReader();
  virtual ~McPicoReader();

  virtual void Init(TChain *chain);
  virtual PicoDstMCEvent *ReadMcEvent(Int_t ev_num);
  virtual PicoDstRecoEvent* ReadRecoEvent(Int_t ev_num) { return nullptr; }
  virtual Int_t GetMcTrackSize();
  virtual Int_t GetRecoTrackSize() { return 0; }
  virtual Int_t GetNFHCalModules() { return 0; }
  virtual PicoDstMCTrack *ReadMcTrack(Int_t tr_num);
  virtual PicoDstRecoTrack* ReadRecoTrack(Int_t tr_num) { return nullptr; }
  virtual PicoDstFHCal* ReadFHCalModule(Int_t module_num) { return nullptr; }

  // ClassDef(McPicoReader,0);
};

#endif