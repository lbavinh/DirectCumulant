// Do not forget to source setPicoDst.sh script

#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
// #include <TH1F.h>
#include <TH1.h>
#include <TH2F.h>
#include <TMath.h>
#include <TDatabasePDG.h>
#include <TString.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

// R__LOAD_LIBRARY(libPicoDst.so)

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if      (bimp < 2.91)  fcent = 2.5; // 0-5%
  else if (bimp < 4.18)  fcent = 7.5; // 5-10%
  else if (bimp < 6.01)  fcent = 15.; // 10-20%
  else if (bimp < 7.37)  fcent = 25.; // 20-30%
  else if (bimp < 8.52)  fcent = 35.; // 30-40%
  else if (bimp < 9.57)  fcent = 45.; // 40-50%
  else if (bimp < 10.55) fcent = 55.; // 50-60%
  else if (bimp < 11.46) fcent = 65.; // 60-70%
  else if (bimp < 12.31) fcent = 75.; // 70-80%
  else                   fcent = -1;
  return fcent;
}


int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 2.5) return 0;
  if (cent == 7.5) return 1;
  if (cent == 15.) return 2;
  if (cent == 25.) return 3;
  if (cent == 35.) return 4;
  if (cent == 45.) return 5;
  if (cent == 55.) return 6;
  if (cent == 65.) return 7;
  if (cent == 75.) return 8;
  return -1;
}

void PicoDstReader(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Configure input information
  TChain *chain = new TChain("picodst");
  if (inputFileName.Contains(".root"))
  {
    chain->Add(inputFileName);
  }
  else
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    while(std::getline(file, line))
    {
      chain->Add(line.c_str());
    }
  }

  PicoDstMCEvent *mcEvent = nullptr;
  // PicoDstRecoEvent *recoEvent = nullptr;
  // TClonesArray *recoTracks = nullptr;
  TClonesArray *mcTracks = nullptr;
  TClonesArray *fhcalmodules = nullptr;

  chain->SetBranchAddress("mcevent.", &mcEvent);
  // chain->SetBranchAddress("recoevent.", &recoEvent);
  chain->SetBranchAddress("mctracks",&mcTracks);
  // chain->SetBranchAddress("recotracks",&recoTracks);
  chain->SetBranchAddress("FHCalModules",&fhcalmodules);
  const int ncent = 9; // 0-80%
  TString centrality[ncent+1] = {"0","5","10","20","30","40","50","60","70","80"};
  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(),"recreate");

  TH1F *h_mcevent_B = new TH1F("h_mcevent_B","MC event: impact parameter",100,0.,20.);
  TH1F *h_mcevent_Phi = new TH1F("h_mcevent_Phi","MC event: reaction plane angle",360,0.,2*TMath::Pi());
  TH1F *h_mcevent_VtxX = new TH1F("h_mcevent_VtxX","MC event: Vertex X-component",100,-2.,2.);
  TH1F *h_mcevent_VtxY = new TH1F("h_mcevent_VtxY","MC event: Vertex Y-component",100,-2.,2.);
  TH1F *h_mcevent_VtxZ = new TH1F("h_mcevent_VtxZ","MC event: Vertex Z-component",100,-20.,20.);
  TH1I *h_mcevent_Mult = new TH1I("h_mcevent_Mult","MC event: Multiplicity",1600,0.,1600.);

  // TH1F *h_recoevent_VtxX = new TH1F("h_recoevent_VtxX","Reco event: Vertex X-component",100,-2.,2.);
  // TH1F *h_recoevent_VtxY = new TH1F("h_recoevent_VtxY","Reco event: Vertex Y-component",100,-2.,2.);
  // TH1F *h_recoevent_VtxZ = new TH1F("h_recoevent_VtxZ","Reco event: Vertex Z-component",100,-20.,20.);
  // TH1I *h_recoevent_Mult = new TH1I("h_recoevent_Mult","Reco event: Multiplicity",1600,0.,1600.);

  TH1F *h_mctrack_Pt = new TH1F("h_mctrack_Pt","MC track: Pt", 500,0.,5.);
  TH1F *h_mctrack_Eta = new TH1F("h_mctrack_Eta","MC track: Eta", 100,-5.,5.);
  TH1F *h_mctrack_Phi = new TH1F("h_mctrack_Phi","MC track: Phi", 360,-TMath::Pi(),TMath::Pi());
  TH1F *h_mctrack_DCAx = new TH1F("h_mctrack_DCAx","MC track: DCA x-component", 200, -1.,1.);
  TH1F *h_mctrack_DCAy = new TH1F("h_mctrack_DCAy","MC track: DCA y-component", 200, -1.,1.);
  TH1F *h_mctrack_DCAz = new TH1F("h_mctrack_DCAz","MC track: DCA z-component", 200, -1.,1.);
  TH1F *h_mctrack_Pdg = new TH1F("h_mctrack_Pdg","MC track: Pdg codes", 3000, 200,3200);
  TH1F *h_mctrack_En = new TH1F("h_mctrack_En","MC track: Energy", 200, 0., 20.);
  TH1D *hEta[ncent];
  TH1I *hMult[ncent];
  TH1F *hPt[ncent];
  TH2F *hEtaPt[ncent];
  TH2F *hBimpMult = new TH2F("hBimpMult", Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, h^{#pm};N_{ch};b, fm"), 300, 0, 1000, 300, 0., 16.);
  TH1I *hPID[ncent];
  TH1F *h_fhcal_En[ncent];
  TH1F *h_fhcal_En_L[ncent];
  TH1F *h_fhcal_En_R[ncent];
  for (Int_t i = 0; i < ncent; i++)
  {
    hPt[i] = new TH1F(Form("hPt_%i",i),Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};p_{T} (GeV/c); dN/dP_{T}",centrality[i].Data(),centrality[i+1].Data()) , 300, 0., 3.);
    hEta[i] = new TH1D(Form("hEta_%i",i),Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};#eta;dN/d#eta",centrality[i].Data(),centrality[i+1].Data()), 300, -6, 6);
    hMult[i] = new TH1I(Form("hMult_%i",i), Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};M;dN/dM",centrality[i].Data(),centrality[i+1].Data()), 200, 0, 2000);
    hEtaPt[i] = new TH2F(Form("hEtaPt_%i",i), Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};p_{T} (GeV/c);#eta",centrality[i].Data(),centrality[i+1].Data()), 300, 0, 3., 300, -6., 6.);
    hPID[i] = new TH1I(Form("hPID_%i",i), Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};PID;Entries",centrality[i].Data(),centrality[i+1].Data()), 6000, -3000, 3000);
    h_fhcal_En[i] = new TH1F(Form("h_fhcal_En_%i",i),Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};E;dN/dE",centrality[i].Data(),centrality[i+1].Data()), 1000,0.,100.);  
    h_fhcal_En_L[i] = new TH1F(Form("h_fhcal_En_L_%i",i),Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};E;dN/dE",centrality[i].Data(),centrality[i+1].Data()), 1000,0.,100.);  
    h_fhcal_En_R[i] = new TH1F(Form("h_fhcal_En_R_%i",i),Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm};E;dN/dE",centrality[i].Data(),centrality[i+1].Data()), 1000,0.,100.);  

  }  
  // TH1F *h_recotrack_Pt = new TH1F("h_recotrack_Pt","Reco track: Pt", 500,0.,5.);
  // TH1F *h_recotrack_Eta = new TH1F("h_recotrack_Eta","Reco track: Eta", 100,-5.,5.);
  // TH1F *h_recotrack_Phi = new TH1F("h_recotrack_Phi","Reco track: Phi", 360,-TMath::Pi(),TMath::Pi());
  // TH1F *h_recotrack_DCAx = new TH1F("h_recotrack_DCAx","Reco track: DCA x-component", 200, -1.,1.);
  // TH1F *h_recotrack_DCAy = new TH1F("h_recotrack_DCAy","Reco track: DCA y-component", 200, -1.,1.);
  // TH1F *h_recotrack_DCAz = new TH1F("h_recotrack_DCAz","Reco track: DCA z-component", 200, -1.,1.);
  // TH1F *h_recotrack_TofMass2 = new TH1F("h_recotrack_TofMass2","Reco track: Mass^{2} from TOF", 400, -1., 3.);
  // TH2F *h_recotrack_TpcdEdxVsP = new TH2F("h_recotrack_TpcdEdxVsP","Reco track: dE/dx from TPC vs P", 3000, 0., 3., 1000, 0., 10000.);

  // TH1F *h_fhcal_En = new TH1F("h_fhcal_En","FHCal: Energy in all modules", 1000,0.,100.);

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

    // // Read Reco event
    // h_recoevent_VtxX->Fill(recoEvent->GetVertexX());
    // h_recoevent_VtxY->Fill(recoEvent->GetVertexY());
    // h_recoevent_VtxZ->Fill(recoEvent->GetVertexZ());

    // Int_t reco_mult = recoTracks->GetEntriesFast();
    // h_recoevent_Mult->Fill(reco_mult);

    // Read MC tracks
    Int_t mc_mult = 0;
    // Get centrality
    float cent = CentB(mcEvent->GetB());
    if (cent == -1) continue;
    int mult = 0;
    int icent = GetCentBin(cent);
    // if (mc_num_particles<50 && (mcEvent->GetB())<11.) continue;
    if (mc_num_particles<200) continue;
    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(iTr);
      if (!mcTrack) continue;
      if (mcTrack->GetMotherId() != -1) continue;
      float pt  = mcTrack->GetPt();
      float eta = mcTrack->GetEta();
      float phi = mcTrack->GetPhi();
      // if (pt<0.2 || pt>3.0 ) continue; // || fabs(eta)>1.5
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      if (particle->Charge() == 0) continue;

      hPt[icent] -> Fill(pt);
      hEta[icent] -> Fill(eta);
      hEtaPt[icent] -> Fill(pt,eta);
      hPID[icent] -> Fill(mcTrack->GetPdg());

      mult++;
      h_mctrack_Pt->Fill(mcTrack->GetPt());
      h_mctrack_Eta->Fill(mcTrack->GetEta());
      h_mctrack_Phi->Fill(mcTrack->GetPhi());
      h_mctrack_DCAx->Fill(mcTrack->GetDCAx());
      h_mctrack_DCAy->Fill(mcTrack->GetDCAy());
      h_mctrack_DCAz->Fill(mcTrack->GetDCAz());
      h_mctrack_Pdg->Fill(mcTrack->GetPdg());
      h_mctrack_En->Fill(mcTrack->GetEnergy());
      if (TMath::Abs(mcTrack->GetPdg()) == 2212 ||
          TMath::Abs(mcTrack->GetPdg()) == 211 || 
          TMath::Abs(mcTrack->GetPdg()) == 321) 
        mc_mult++;
    }
    h_mcevent_Mult->Fill(mc_mult);
    if (mult!=0) 
    {
      hMult[icent] -> Fill(mult);
      hBimpMult->Fill(mult,mcEvent->GetB());
    }
    // // Read Reco tracks
    // for (int iTr=0; iTr<reco_mult; iTr++)
    // {
    //   auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
    //   h_recotrack_Pt->Fill(recoTrack->GetPt());
    //   h_recotrack_Eta->Fill(recoTrack->GetEta());
    //   h_recotrack_Phi->Fill(recoTrack->GetPhi());
    //   h_recotrack_DCAx->Fill(recoTrack->GetDCAx());
    //   h_recotrack_DCAy->Fill(recoTrack->GetDCAy());
    //   h_recotrack_DCAz->Fill(recoTrack->GetDCAz());
    //   h_recotrack_TofMass2->Fill(recoTrack->GetTofMass2());
    //   h_recotrack_TpcdEdxVsP->Fill(recoTrack->GetP(),recoTrack->GetTpcdEdx());
    // }

    // Read FHCal modules
    Float_t fhcal_totEn = 0.;
    Float_t fhcal_totEn_L = 0.;
    Float_t fhcal_totEn_R = 0.;
    for (int iMod=0; iMod<fhcalmodules->GetEntriesFast(); iMod++)
    {
      auto fhcalModule = (PicoDstFHCal*) fhcalmodules->UncheckedAt(iMod);
      fhcal_totEn += fhcalModule->GetEnergy();
      if (iMod<45) fhcal_totEn_R+= fhcalModule->GetEnergy();
      else fhcal_totEn_L+= fhcalModule->GetEnergy();
    }
    h_fhcal_En[icent]->Fill(fhcal_totEn);
    h_fhcal_En_L[icent]->Fill(fhcal_totEn_L);
    h_fhcal_En_R[icent]->Fill(fhcal_totEn_R);

  } // end event loop

  //Writing output
  fo->cd();
  fo->Write();
  // h_mcevent_B->Write();
  // h_mcevent_Phi->Write();
  // h_mcevent_VtxX->Write();
  // h_mcevent_VtxY->Write();
  // h_mcevent_VtxZ->Write();
  // h_mcevent_Mult->Write();

  // h_recoevent_VtxX->Write();
  // h_recoevent_VtxY->Write();
  // h_recoevent_VtxZ->Write();
  // h_recoevent_Mult->Write();

  // h_mctrack_Pt->Write();
  // h_mctrack_Eta->Write();
  // h_mctrack_Phi->Write();
  // h_mctrack_DCAx->Write();
  // h_mctrack_DCAy->Write();
  // h_mctrack_DCAz->Write();
  // h_mctrack_Pdg->Write();
  // h_mctrack_En->Write();

  // h_recotrack_Pt->Write();
  // h_recotrack_Eta->Write();
  // h_recotrack_Phi->Write();
  // h_recotrack_DCAx->Write();
  // h_recotrack_DCAy->Write();
  // h_recotrack_DCAz->Write();
  // h_recotrack_TofMass2->Write();
  // h_recotrack_TpcdEdxVsP->Write();

  // h_fhcal_En->Write();

  fo->Close();

  timer.Stop();
  timer.Print();
}
// source /scratch1/lbavinh/Soft/PicoDst/build/setPicoDst.sh
// root -l -b -q PicoDstReader.C+'("/scratch1/lbavinh/lbavinh/QA/runlist_vHLLEUrQMD_11.5_reco.list","vHLLE_11.5_reco.root")'