#ifndef INTERFACE_READER_H
#define INTERFACE_READER_H

#include <Rtypes.h>
#include <TChain.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

class IReader
{
public:
    virtual void Init(TChain *chain) = 0;
    virtual PicoDstMCEvent* ReadMcEvent(Int_t ev_num) = 0;
    virtual PicoDstRecoEvent* ReadRecoEvent(Int_t ev_num) = 0;
    virtual Int_t GetMcTrackSize() = 0;
    virtual Int_t GetRecoTrackSize() = 0;
    virtual PicoDstMCTrack* ReadMcTrack(Int_t tr_num) = 0;
    virtual PicoDstRecoTrack* ReadRecoTrack(Int_t tr_num) = 0;
    virtual ~IReader();

    ClassDef(IReader,0);
};

#endif