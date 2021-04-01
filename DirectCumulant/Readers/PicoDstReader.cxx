#include <PicoDstReader.h>

PicoDstReader::PicoDstReader(/* args */) : fChain(nullptr),
                                           mcEvent(nullptr),
                                           recoEvent(nullptr),
                                           mcTracks(nullptr),
                                           recoTracks(nullptr),
                                           fhcalmodules(nullptr)
{
}

PicoDstReader::~PicoDstReader()
{
    delete fChain;
    delete mcEvent;
    delete recoEvent;
    delete mcTracks;
    delete recoTracks;
    delete fhcalmodules;
}

void PicoDstReader::Init(TChain *chain)
{
    fChain = chain;

    mcEvent = nullptr;
    recoEvent = nullptr;
    recoTracks = nullptr;
    mcTracks = nullptr;
    fhcalmodules = nullptr;

    chain->SetBranchAddress("mcevent.", &mcEvent);
    chain->SetBranchAddress("recoevent.", &recoEvent);
    chain->SetBranchAddress("recotracks", &recoTracks);
    chain->SetBranchAddress("mctracks", &mcTracks);
    chain->SetBranchAddress("FHCalModules", &fhcalmodules);
}

PicoDstMCEvent *PicoDstReader::ReadMcEvent(Int_t ev_num)
{
    if (!fChain)
        return nullptr;
    fChain->GetEntry(ev_num);

    auto event = new PicoDstMCEvent();

    event->SetB(mcEvent->GetB());
    event->SetPhiRP(mcEvent->GetPhiRP());
    event->SetVertex(mcEvent->GetVertexX(), mcEvent->GetVertexY(), mcEvent->GetVertexZ());

    return event;
}

PicoDstRecoEvent *PicoDstReader::ReadRecoEvent(Int_t ev_num)
{
    if (!fChain)
        return nullptr;
    fChain->GetEntry(ev_num);

    auto event = new PicoDstRecoEvent();

    event->SetVertex(mcEvent->GetVertexX(), mcEvent->GetVertexY(), mcEvent->GetVertexZ());

    return event;
}

Int_t PicoDstReader::GetMcTrackSize()
{
    if (!mcTracks) return 0;
    return mcTracks->GetEntriesFast();
}

Int_t PicoDstReader::GetRecoTrackSize()
{
    if (!recoTracks) return 0;
    return recoTracks->GetEntriesFast();
}

Int_t PicoDstReader::GetNFHCalModules()
{
    if (!fhcalmodules) return 0;
    return fhcalmodules->GetEntriesFast();
}

PicoDstMCTrack *PicoDstReader::ReadMcTrack(Int_t tr_num)
{
    if (!fChain)
        return nullptr;
    auto track = (PicoDstMCTrack *)mcTracks->UncheckedAt(tr_num);
    if (!track)
        return nullptr;
    
    return track;
}

PicoDstRecoTrack *PicoDstReader::ReadRecoTrack(Int_t tr_num)
{
    if (!fChain)
        return nullptr;
    auto track = (PicoDstRecoTrack *)recoTracks->UncheckedAt(tr_num);
    if (!track)
        return nullptr;
    
    return track;
}

PicoDstFHCal *PicoDstReader::ReadFHCalModule(Int_t module_num)
{
    if (!fChain)
        return nullptr;
    auto module = (PicoDstFHCal *)fhcalmodules->UncheckedAt(module_num);
    if (!module)
        return nullptr;
    
    return module;  
}