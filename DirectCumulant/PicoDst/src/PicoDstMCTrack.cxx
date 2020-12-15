#include "PicoDstMCTrack.h"

ClassImp(PicoDstMCTrack);

PicoDstMCTrack::PicoDstMCTrack()
{
}

PicoDstMCTrack::~PicoDstMCTrack()
{
  Clear();
}

void PicoDstMCTrack::Clear(Option_t *option)
{
  PicoDstBaseTrack::Clear(option);
  fMotherId = 0;
  fPdg = 0;
  fEnergy = 0.;
}
