#ifndef PICODST_RECO_EVENT_H
#define PICODST_RECO_EVENT_H

#include <TROOT.h>
#include "PicoDstBaseEvent.h"

class PicoDstRecoEvent : public PicoDstBaseEvent, public TObject
{
public:
  PicoDstRecoEvent();
  virtual ~PicoDstRecoEvent();

  ClassDef(PicoDstRecoEvent,1);
};

#endif
