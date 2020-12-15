// Do not forget to source setPicoDst.sh script

#include <iostream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2F.h>
#include <TMath.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

// R__LOAD_LIBRARY(libPicoDst.so)

void readPicoDst(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Configure input information
  TChain *chain = new TChain("picodst");
  chain->Add(inputFileName.Data());

  PicoDstMCEvent *mcEvent = nullptr;
  PicoDstRecoEvent *recoEvent = nullptr;
  TClonesArray *recoTracks = nullptr;
  TClonesArray *mcTracks = nullptr;
  TClonesArray *fhcalmodules = nullptr;

  chain->SetBranchAddress("mcevent.", &mcEvent);
  chain->SetBranchAddress("recoevent.", &recoEvent);
  chain->SetBranchAddress("mctracks",&mcTracks);
  chain->SetBranchAddress("recotracks",&recoTracks);
  chain->SetBranchAddress("FHCalModules",&fhcalmodules);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(),"recreate");

  TH1F *h_mcevent_B = new TH1F("h_mcevent_B","MC event: impact parameter",100,0.,20.);
  TH1F *h_mcevent_Phi = new TH1F("h_mcevent_Phi","MC event: reaction plane angle",360,0.,2*TMath::Pi());
  TH1F *h_mcevent_VtxX = new TH1F("h_mcevent_VtxX","MC event: Vertex X-component",100,-2.,2.);
  TH1F *h_mcevent_VtxY = new TH1F("h_mcevent_VtxY","MC event: Vertex Y-component",100,-2.,2.);
  TH1F *h_mcevent_VtxZ = new TH1F("h_mcevent_VtxZ","MC event: Vertex Z-component",100,-20.,20.);
  TH1I *h_mcevent_Mult = new TH1I("h_mcevent_Mult","MC event: Multiplicity",1600,0.,1600.);

  TH1F *h_recoevent_VtxX = new TH1F("h_recoevent_VtxX","Reco event: Vertex X-component",100,-2.,2.);
  TH1F *h_recoevent_VtxY = new TH1F("h_recoevent_VtxY","Reco event: Vertex Y-component",100,-2.,2.);
  TH1F *h_recoevent_VtxZ = new TH1F("h_recoevent_VtxZ","Reco event: Vertex Z-component",100,-20.,20.);
  TH1I *h_recoevent_Mult = new TH1I("h_recoevent_Mult","Reco event: Multiplicity",1600,0.,1600.);

  TH1F *h_mctrack_Pt = new TH1F("h_mctrack_Pt","MC track: Pt", 500,0.,5.);
  TH1F *h_mctrack_Eta = new TH1F("h_mctrack_Eta","MC track: Eta", 100,-5.,5.);
  TH1F *h_mctrack_Phi = new TH1F("h_mctrack_Phi","MC track: Phi", 360,-TMath::Pi(),TMath::Pi());
  TH1F *h_mctrack_DCAx = new TH1F("h_mctrack_DCAx","MC track: DCA x-component", 200, -1.,1.);
  TH1F *h_mctrack_DCAy = new TH1F("h_mctrack_DCAy","MC track: DCA y-component", 200, -1.,1.);
  TH1F *h_mctrack_DCAz = new TH1F("h_mctrack_DCAz","MC track: DCA z-component", 200, -1.,1.);
  TH1F *h_mctrack_Pdg = new TH1F("h_mctrack_Pdg","MC track: Pdg codes", 3000, 200,3200);
  TH1F *h_mctrack_En = new TH1F("h_mctrack_En","MC track: Energy", 200, 0., 20.);

  TH1F *h_recotrack_Pt = new TH1F("h_recotrack_Pt","Reco track: Pt", 500,0.,5.);
  TH1F *h_recotrack_Eta = new TH1F("h_recotrack_Eta","Reco track: Eta", 100,-5.,5.);
  TH1F *h_recotrack_Phi = new TH1F("h_recotrack_Phi","Reco track: Phi", 360,-TMath::Pi(),TMath::Pi());
  TH1F *h_recotrack_DCAx = new TH1F("h_recotrack_DCAx","Reco track: DCA x-component", 200, -1.,1.);
  TH1F *h_recotrack_DCAy = new TH1F("h_recotrack_DCAy","Reco track: DCA y-component", 200, -1.,1.);
  TH1F *h_recotrack_DCAz = new TH1F("h_recotrack_DCAz","Reco track: DCA z-component", 200, -1.,1.);
  TH1F *h_recotrack_TofMass2 = new TH1F("h_recotrack_TofMass2","Reco track: Mass^{2} from TOF", 400, -1., 3.);
  TH2F *h_recotrack_TpcdEdxVsP = new TH2F("h_recotrack_TpcdEdxVsP","Reco track: dE/dx from TPC vs P", 3000, 0., 3., 1000, 0., 10000.);

  TH1F *h_fhcal_En = new TH1F("h_fhcal_En","FHCal: Energy in all modules", 1000,0.,100.);

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%1000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    // Read MC event
    h_mcevent_B->Fill(mcEvent->GetB());
    h_mcevent_Phi->Fill(mcEvent->GetPhiRP());
    h_mcevent_VtxX->Fill(mcEvent->GetVertexX());
    h_mcevent_VtxY->Fill(mcEvent->GetVertexY());
    h_mcevent_VtxZ->Fill(mcEvent->GetVertexZ());

    Int_t mc_num_particles = mcTracks->GetEntriesFast();

    // Read Reco event
    h_recoevent_VtxX->Fill(recoEvent->GetVertexX());
    h_recoevent_VtxY->Fill(recoEvent->GetVertexY());
    h_recoevent_VtxZ->Fill(recoEvent->GetVertexZ());

    Int_t reco_mult = recoTracks->GetEntriesFast();
    h_recoevent_Mult->Fill(reco_mult);

    // Read MC tracks
    Int_t mc_mult = 0;
    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(iTr);
      h_mctrack_Pt->Fill(mcTrack->GetPt());
      h_mctrack_Eta->Fill(mcTrack->GetEta());
      h_mctrack_Phi->Fill(mcTrack->GetPhi());
      h_mctrack_DCAx->Fill(mcTrack->GetDCAx());
      h_mctrack_DCAy->Fill(mcTrack->GetDCAy());
      h_mctrack_DCAz->Fill(mcTrack->GetDCAz());
      h_mctrack_Pdg->Fill(mcTrack->GetPdg());
      h_mctrack_En->Fill(mcTrack->GetEnergy());
      //if (TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg())->Charge() != 0) mc_mult++;
      if (TMath::Abs(mcTrack->GetPdg()) == 2212 ||
          TMath::Abs(mcTrack->GetPdg()) == 211 || 
          TMath::Abs(mcTrack->GetPdg()) == 321) 
        mc_mult++;
    }
    h_mcevent_Mult->Fill(mc_mult);

    // Read Reco tracks
    for (int iTr=0; iTr<reco_mult; iTr++)
    {
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      h_recotrack_Pt->Fill(recoTrack->GetPt());
      h_recotrack_Eta->Fill(recoTrack->GetEta());
      h_recotrack_Phi->Fill(recoTrack->GetPhi());
      h_recotrack_DCAx->Fill(recoTrack->GetDCAx());
      h_recotrack_DCAy->Fill(recoTrack->GetDCAy());
      h_recotrack_DCAz->Fill(recoTrack->GetDCAz());
      h_recotrack_TofMass2->Fill(recoTrack->GetTofMass2());
      h_recotrack_TpcdEdxVsP->Fill(recoTrack->GetP(),recoTrack->GetTpcdEdx());
    }

    // Read FHCal modules
    Float_t fhcal_totEn = 0.;
    for (int iMod=0; iMod<fhcalmodules->GetEntriesFast(); iMod++)
    {
      auto fhcalModule = (PicoDstFHCal*) fhcalmodules->UncheckedAt(iMod);
      fhcal_totEn += fhcalModule->GetEnergy();
    }
    h_fhcal_En->Fill(fhcal_totEn);

  } // end event loop

  //Writing output
  fo->cd();

  h_mcevent_B->Write();
  h_mcevent_Phi->Write();
  h_mcevent_VtxX->Write();
  h_mcevent_VtxY->Write();
  h_mcevent_VtxZ->Write();
  h_mcevent_Mult->Write();

  h_recoevent_VtxX->Write();
  h_recoevent_VtxY->Write();
  h_recoevent_VtxZ->Write();
  h_recoevent_Mult->Write();

  h_mctrack_Pt->Write();
  h_mctrack_Eta->Write();
  h_mctrack_Phi->Write();
  h_mctrack_DCAx->Write();
  h_mctrack_DCAy->Write();
  h_mctrack_DCAz->Write();
  h_mctrack_Pdg->Write();
  h_mctrack_En->Write();

  h_recotrack_Pt->Write();
  h_recotrack_Eta->Write();
  h_recotrack_Phi->Write();
  h_recotrack_DCAx->Write();
  h_recotrack_DCAy->Write();
  h_recotrack_DCAz->Write();
  h_recotrack_TofMass2->Write();
  h_recotrack_TpcdEdxVsP->Write();

  h_fhcal_En->Write();

  fo->Close();

  timer.Stop();
  timer.Print();
}