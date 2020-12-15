#ifndef PICODST_MC_EVENT_H
#define PICODST_MC_EVENT_H

#include <TROOT.h>
#include <TObject.h>
#include "PicoDstBaseEvent.h"

class PicoDstMCEvent : public PicoDstBaseEvent, public TObject
{
private:
  Float_t fB;
  Float_t fPhiRP;
public:
  PicoDstMCEvent();
  virtual ~PicoDstMCEvent();

  // Setters
  virtual void SetB(Float_t _a) { fB = _a; }
  virtual void SetPhiRP(Float_t _a) { fPhiRP = _a; }

  // Getters
  virtual Float_t GetB() const { return fB; }
  virtual Float_t GetPhiRP() const { return fPhiRP; }

  ClassDef(PicoDstMCEvent,1);
};

#endif
