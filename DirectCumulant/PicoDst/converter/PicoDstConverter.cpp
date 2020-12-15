#include <iostream>
#include <set>
#include <map>

#include <TROOT.h>
#include <TChain.h>
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom1.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TMath.h>
#include <TSystem.h>
#include <TVector3.h>
#include <TStopwatch.h>
#include "FairMCEventHeader.h"
#ifdef _OLD_MCSTACK_
#include "FairMCTrack.h"
#endif
#ifdef _NEW_MCSTACK_
#include "MpdMCTrack.h"
#endif
#include "MpdEvent.h"
#include "MpdZdcDigi.h"
#include "MpdPid.h"
#include "MpdTrack.h"
#include "MpdKalmanTrack.h"
#include "MpdVertex.h"

#include "PicoDstMCEvent.h"
#include "PicoDstRecoEvent.h"
#include "PicoDstMCTrack.h"
#include "PicoDstRecoTrack.h"
#include "PicoDstFHCal.h"

int main(int argc, char **argv)
{

  TString iFileName, oFileName;
  Bool_t writeAll = false;
  if (argc < 5)
  {
    std::cerr << "./PicoDstConverter -i inputfile -o outputfile [optional: --all. Writes all events (event with no reco tracks). False by default.]" << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
      std::string(argv[i]) != "-o" &&
      std::string(argv[i]) != "--all")
    {
            std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 1;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "--all")
      {
        writeAll = true;
        continue;
      }
    }
  }

  TStopwatch timer;
  timer.Start();

  ///////////////////////////////////////////
  //TChain *dstTree;
  TFile *fi = new TFile(iFileName.Data(),"read");
  if (!fi || fi->IsZombie())
  {
    std::cerr << "ERROR: Input file probably is empty. Exit the program." << std::endl;
    return 100;
  }

  TTree  *dstTree = (TTree*) fi->Get("mpdsim");

  TFile *outFile = new TFile(oFileName.Data(), "RECREATE");
  
  // TTree connfiguration
  TTree *outTree = new TTree("picodst","Pico Dst for flow calculations at MPD");

  const Double_t PIDsigM = 4.0;
  const Double_t PIDsigE = 4.0;
  const Double_t PIDenergy = 11.;
  const Double_t PIDkoeff = 1.;
  const TString PIDgenerator = "URQMD";
  const TString PIDtracking = "CF";
  const TString PIDparticles = "pikapr";
  const Int_t   Num_Of_Modules = 90;

  MpdPid *pid = new MpdPid(PIDsigM, PIDsigE, PIDenergy, PIDkoeff, PIDgenerator, PIDtracking, PIDparticles);

  // PicoDst-related variables
  PicoDstMCEvent *mcEvent = new PicoDstMCEvent();
  PicoDstRecoEvent *recoEvent = new PicoDstRecoEvent();
  TClonesArray *mcTracks = new TClonesArray("PicoDstMCTrack");
  TClonesArray *recoTracks = new TClonesArray("PicoDstRecoTrack");
  TClonesArray *fhcalModules = new TClonesArray("PicoDstFHCal");

  outTree->Branch("mcevent.",     &mcEvent,      32000,  99);
  outTree->Branch("recoevent.",   &recoEvent,    32000,  99);
  outTree->Branch("mctracks",     &mcTracks,     256000, 99);
  outTree->Branch("recotracks",   &recoTracks,   256000, 99);
  outTree->Branch("FHCalModules", &fhcalModules, 128000, 99);
  mcTracks->BypassStreamer();
  recoTracks->BypassStreamer();
  fhcalModules->BypassStreamer();

  FairMCEventHeader *MCHeader;
  TClonesArray *MCTracks;
  MpdEvent *MPDEvent;
  TClonesArray *FHCalHits;
  TClonesArray *MpdGlobalTracks;
  MpdZdcDigi *FHCalHit;
  //TClonesArray *mpdKalmanTracks;
  TClonesArray *vertexes;

  MCHeader = nullptr;
  MCTracks = nullptr;
  MPDEvent = nullptr;
  FHCalHits = nullptr;
  //mpdKalmanTracks = nullptr;
  vertexes = nullptr;

  dstTree->SetBranchAddress("MCEventHeader.", &MCHeader);
  dstTree->SetBranchAddress("MCTrack", &MCTracks);
  dstTree->SetBranchAddress("MPDEvent.", &MPDEvent);
  dstTree->SetBranchAddress("ZdcDigi", &FHCalHits);
  //dstTree->SetBranchAddress("TpcKalmanTrack", &mpdKalmanTracks);
  dstTree->SetBranchAddress("Vertex", &vertexes);

  // Starting event loop
  TVector3 primaryVertex;
  std::set <Int_t> UsedMCTracks;
  std::map <Int_t,Int_t> InitMcNewMcId; // map[old-mc-id] = new-mc-id
  Float_t FHCalSumEnergy[Num_Of_Modules];
  Int_t n_entries = dstTree->GetEntriesFast();
  Bool_t isGoodPID;
  Short_t charge_mpd;
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    std::cout << "EVENT N " << iEv << std::endl;
    dstTree->GetEntry(iEv);

    mcTracks->Clear();
    recoTracks->Clear();
    UsedMCTracks.clear();
    InitMcNewMcId.clear();
    for (int i=0; i<Num_Of_Modules; i++)
    {
      FHCalSumEnergy[i] = 0.;
    }

    // Read MC Event
    mcEvent->SetB(MCHeader->GetB());
    mcEvent->SetPhiRP(MCHeader->GetRotZ());
    mcEvent->SetVertex(MCHeader->GetX(), MCHeader->GetY(), MCHeader->GetZ());

    // Reading Reco Event
    MpdVertex *vertex = (MpdVertex *)vertexes->First();
    vertex->Position(primaryVertex);
    recoEvent->SetVertex(primaryVertex.X(), primaryVertex.Y(), primaryVertex.Z());

    // Read energy reconstructed in the FHCal modules
    Int_t number_of_FHCal_hits = FHCalHits->GetEntriesFast();
    for(int ihit=0; ihit<number_of_FHCal_hits; ihit++)
    {
      FHCalHit = (MpdZdcDigi*) FHCalHits->UncheckedAt(ihit);
      Int_t DetId = FHCalHit->GetDetectorID();
      FHCalSumEnergy[(FHCalHit->GetModuleID()-1)+(Num_Of_Modules/2)*(DetId-1)] += FHCalHit->GetELoss();
    }
    // Fill fDetectorID = 1 part
    for (int imodule=0; imodule<Num_Of_Modules; imodule++)
    {
      PicoDstFHCal *fhcalModule = (PicoDstFHCal*)fhcalModules->ConstructedAt(imodule);
      fhcalModule->SetEnergy(FHCalSumEnergy[imodule]);
    }
    
    // Reading Reco Tracks
    MpdGlobalTracks = (TClonesArray*)MPDEvent->GetGlobalTracks();
    for (int itrack=0; itrack<MpdGlobalTracks->GetEntriesFast(); itrack++)
    {
      MpdTrack* mpdtrack = (MpdTrack*) MpdGlobalTracks->UncheckedAt(itrack);
      UsedMCTracks.insert(mpdtrack->GetID());
      PicoDstRecoTrack *recoTrack = (PicoDstRecoTrack*)recoTracks->ConstructedAt(itrack);
      
      if (writeAll) recoTrack->SetInitialMcId(mpdtrack->GetID());
      recoTrack->SetPx(mpdtrack->GetPx());
      recoTrack->SetPy(mpdtrack->GetPy());
      recoTrack->SetPz(mpdtrack->GetPz());
      recoTrack->SetNhits(mpdtrack->GetNofHits());
      recoTrack->SetNhitsPoss(mpdtrack->GetNofHitsPossTpc());
      recoTrack->SetTofMass2(mpdtrack->GetTofMass2());
      recoTrack->SetTofFlag(mpdtrack->GetTofFlag());
      recoTrack->SetTpcdEdx(mpdtrack->GetdEdXTPC());
      recoTrack->SetChi2(mpdtrack->GetChi2());
      recoTrack->SetDCAx(mpdtrack->GetDCAX());
      recoTrack->SetDCAy(mpdtrack->GetDCAY());
      recoTrack->SetDCAz(mpdtrack->GetDCAZ());
      charge_mpd = (mpdtrack->GetPt() < 0) ? 1 : -1;
      recoTrack->SetCharge(charge_mpd);

      // PID
      if (mpdtrack->GetTofFlag() == 2 || mpdtrack->GetTofFlag() == 6)
      {
        isGoodPID = pid->FillProbs(TMath::Abs(mpdtrack->GetPt()) * TMath::CosH(mpdtrack->GetEta()),
                                   mpdtrack->GetdEdXTPC(), mpdtrack->GetTofMass2(), charge_mpd);
      }
      else
      {
        isGoodPID = pid->FillProbs(TMath::Abs(mpdtrack->GetPt()) * TMath::CosH(mpdtrack->GetEta()),
                                   mpdtrack->GetdEdXTPC(), charge_mpd);
      }

      if (isGoodPID)
      {
        recoTrack->SetPidProbPion(pid->GetProbPi());   //mpdtrack->GetTPCPidProbPion();
        recoTrack->SetPidProbKaon(pid->GetProbKa());   //mpdtrack->GetTPCPidProbKaon();
        recoTrack->SetPidProbProton(pid->GetProbPr()); //mpdtrack->GetTPCPidProbProton();
      }
      else
      {
        recoTrack->SetPidProbPion(-999.);
        recoTrack->SetPidProbKaon(-999.);
        recoTrack->SetPidProbProton(-999.);
      }
    }

    // Reading MC Tracks
    int mcTrackCounter = 0;
    for (int imctrack=0; imctrack<MCTracks->GetEntriesFast(); imctrack++)
    {
#ifdef _OLD_MCSTACK_
      FairMCTrack *mctrack = (FairMCTrack*) MCTracks->UncheckedAt(imctrack);
#endif
#ifdef _NEW_MCSTACK_
      MpdMCTrack *mctrack = (MpdMCTrack*) MCTracks->UncheckedAt(imctrack);
#endif
      bool isUsed = (UsedMCTracks.count(imctrack));

      // If motherId != 1 and mc track doesn't relate to any reco track - skip
      if (mctrack->GetMotherId() != -1 && !isUsed) continue;
      if (isUsed)
      {
        InitMcNewMcId[imctrack] = mcTrackCounter;
      }
      PicoDstMCTrack *mcPicoTrack = (PicoDstMCTrack*)mcTracks->ConstructedAt(mcTrackCounter);
      if (writeAll) mcPicoTrack->SetInitialId(imctrack);
      mcPicoTrack->SetPx(mctrack->GetPx());
      mcPicoTrack->SetPy(mctrack->GetPy());
      mcPicoTrack->SetPz(mctrack->GetPz());
      mcPicoTrack->SetMotherId(mctrack->GetMotherId());
      mcPicoTrack->SetPdg(mctrack->GetPdgCode());
      mcPicoTrack->SetEnergy(mctrack->GetEnergy());
      mcTrackCounter++;
    }

    for (int itrack=0; itrack<recoTracks->GetEntriesFast(); itrack++)
    {
      PicoDstRecoTrack *recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(itrack);
      MpdTrack* mpdtrack = (MpdTrack*) MpdGlobalTracks->UncheckedAt(itrack);
      recoTrack->SetMcId(InitMcNewMcId[mpdtrack->GetID()]);
    }

    // Skip if the event has no recontructed tracks
    if (recoTracks->GetEntriesFast() == 0 && !(writeAll)) continue;

    outTree->Fill();
  } // End of the Event loop

  outFile->cd();
  outTree->Print();
  outTree->Write();
  outFile->Close();

  timer.Stop();
  timer.Print();

  return 0;
}
