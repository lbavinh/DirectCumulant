#ifndef PICODST_MC_TRACK_H
#define PICODST_MC_TRACK_H

#include <TROOT.h>
#include "PicoDstBaseTrack.h"

class PicoDstMCTrack : public PicoDstBaseTrack
{
private:
  Int_t fMotherId;
  Int_t fPdg;
  Float_t fEnergy;
  Int_t  fInitialId;
public:
  PicoDstMCTrack();
  virtual ~PicoDstMCTrack();

  void Clear(Option_t *option = "");

  // Setters
  virtual void SetInitialId(Int_t _a) { fInitialId = _a; }
  virtual void SetMotherId(Int_t _a) { fMotherId = _a; }
  virtual void SetPdg(Int_t _a) { fPdg = _a; }
  virtual void SetEnergy(Float_t _a) { fEnergy = _a; }

  // Getters
  virtual Int_t GetInitialId() const { return fInitialId; }
  virtual Int_t GetMotherId() const { return fMotherId; }
  virtual Int_t GetPdg() const { return fPdg; }
  virtual Float_t GetEnergy() const { return fEnergy; }

  ClassDef(PicoDstMCTrack,1);
};

#endif
