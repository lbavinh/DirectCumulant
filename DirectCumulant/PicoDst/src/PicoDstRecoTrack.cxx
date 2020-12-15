#include "PicoDstRecoTrack.h"

ClassImp(PicoDstRecoTrack);

PicoDstRecoTrack::PicoDstRecoTrack()
{
}

PicoDstRecoTrack::~PicoDstRecoTrack()
{
  Clear();
}

void PicoDstRecoTrack::Clear(Option_t *option)
{
  PicoDstBaseTrack::Clear(option);
  fId = 0;
  fTofFlag = 0;
  fTpcdEdx = 0.;
  fTofMass2 = 0.;
  fPidProbPion = 0.;
  fPidProbKaon = 0.;
  fPidProbProton = 0.;
  fChi2 = 0.;
  fNhits = 0;
  fNhitsPoss = 0;
  fChargeSign = 0;
}
