#ifndef PICODST_READER_H
#define PICODST_READER_H

#include <IReader.h>

#include <TClonesArray.h>
#include <TChain.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

class PicoDstReader : public IReader
{
private:
    TChain *fChain;
    PicoDstMCEvent *mcEvent;
    PicoDstRecoEvent *recoEvent;
    TClonesArray *recoTracks;
    TClonesArray *mcTracks;
    TClonesArray *fhcalmodules;

public:
    PicoDstReader(/* args */);
    virtual ~PicoDstReader();

    virtual void Init(TChain *chain);
    virtual PicoDstMCEvent *ReadMcEvent(Int_t ev_num);
    virtual PicoDstRecoEvent *ReadRecoEvent(Int_t ev_num);
    virtual Int_t GetMcTrackSize();
    virtual Int_t GetRecoTrackSize();
    virtual Int_t GetNFHCalModules();
    virtual PicoDstMCTrack* ReadMcTrack(Int_t tr_num);
    virtual PicoDstRecoTrack* ReadRecoTrack(Int_t tr_num);
    virtual PicoDstFHCal* ReadFHCalModule(Int_t module_num);
};

#endif