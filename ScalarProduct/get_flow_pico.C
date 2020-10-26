// Do not forget to source setPicoDst.sh script

#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TMath.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

// Event selection

float CentB(float bimp);

int GetCentBin(float cent);

// R__LOAD_LIBRARY(libPicoDst.so)

void get_flow_pico(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration

  // Profile info - general
  const int NcentBins     = 8;
  const double centBinMin = 0.;
  const double centBinMax = 80.;
  const int NptBins       = 300;
  const double ptBinMin   = 0.;
  const double ptBinMax   = 3.;
  const int NQvBins       = 240;
  const double QvBinMin   = -1.2;
  const double QvBinMax   = 1.2;

  // Track cuts - general
  const float pt_min_cut = 0.2;
  const float pt_max_cut = 3.;
  const float eta_cut    = 1.5;
  const float eta_gap    = 0.05;
  const int   mult_EP_cut= 2;

  // Track cuts - mc tracks
  const int motherId_cut = -1;

  // Track cuts - reco tracks
  const int Nhits_cut    = 16;
  // const float dca_cut    = 0.5;

  // PID - general
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
  const int Npid = 8; //pidNames.size()

  // PID - mc/model tracks
  const std::vector<int> pdgCodes = {999, 211, 321, 2212, -999, -211, -321, -2212};

  // PID - reco tracks
  // const float PidProb_cut = 0.9;
  // const std::vector<float> vResTpc     = {3.27113, 4.49237, 4.1123, 3.19177, 2.20674, 1.36977, 0.806919, 0.535048}; // 7.7 pico
  const std::vector<float> vResTpc     = {4.62534, 5.86391, 5.28431, 4.07091, 2.76921, 1.69137, 0.99504, 0.654555}; // 11.5 pico

  // Configure input information
  TChain *chain = new TChain("picodst");

  std::ifstream file(inputFileName.Data());
  std::string line;
  while(std::getline(file, line))
  {
      chain->Add(line.c_str());
  }

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

  TProfile *pResTPC = new TProfile("pResTPC","Resolution for TPC EP MODEL", NcentBins, centBinMin, centBinMax);
  TProfile2D *pv2TPC[Npid];
  for (int i=0; i < Npid; i++)
  {
    pv2TPC[i] = new TProfile2D(Form("pv2TPC_pid%i", i), Form("v2(TPC EP) MODEL of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  }
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%1000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    // Get centrality
    float cent = CentB(mcEvent->GetB());
    if (cent == -1) continue;

    Int_t mc_num_particles = mcTracks->GetEntriesFast();

    // Read Reco event

    Int_t reco_mult = recoTracks->GetEntriesFast();


    // Read Reco tracks
    float Qx_L_reco = 0., Qy_L_reco = 0., W_L_reco = 0.;
    float Qx_R_reco = 0., Qy_R_reco = 0., W_R_reco = 0.;
    TComplex Qv2_L = 0., Qv2_R = 0.; // scalar product
    int   Mult_L_reco = 0, Mult_R_reco = 0;
    float PsiEP_L_reco = 0., PsiEP_R_reco = 0.;
    for (int iTr=0; iTr<reco_mult; iTr++)
    {
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      if (!recoTrack) continue;
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      if (!mcTrack) continue;

      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      float phi = recoTrack->GetPhi();

      // Main track cuts
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      if (abs(eta) < eta_gap) continue;
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (charge==0) continue;

      // Reco-specific track cuts
      if (recoTrack->GetNhits() < Nhits_cut) continue;
      //if (abs(recoTrack->GetDCAx()) > dca_cut) continue;
      //if (abs(recoTrack->GetDCAy()) > dca_cut) continue;
      //if (abs(recoTrack->GetDCAz()) > dca_cut) continue;
      if (mcTrack->GetMotherId() != motherId_cut) continue;

      // TPC Left EP
      if (eta < 0)
      {
        Qx_L_reco += 1. * cos(2.* phi);
        Qy_L_reco += 1. * sin(2.* phi);
        // W_L_reco  += 1.;
        Mult_L_reco++;
      }

      // TPC Right EP
      if (eta > 0)
      {
        Qx_R_reco += 1. * cos(2.* phi);
        Qy_R_reco += 1. * sin(2.* phi);
        // W_R_reco  += 1.;
        Mult_R_reco++;
      }
    } // end of reco track loop

    if (Mult_L_reco > mult_EP_cut && Mult_R_reco > mult_EP_cut)
    {
      Qv2_L = TComplex(Qx_L_reco,Qy_L_reco);
      Qv2_R = TComplex(Qx_R_reco,Qy_R_reco);
      float res_reco   = (float) (Qv2_L*TComplex::Conjugate(Qv2_R)).Re();
      pResTPC->Fill(cent, res_reco);
    }else{ continue;} 


    ////////////////////////////////////////////////////////////////////
    //
    // FLOW CALCULATIONS
    //
    ////////////////////////////////////////////////////////////////////
    
    float res_v2TPC_reco = vResTpc.at(GetCentBin(cent));
    // Read Reco tracks
    for (int iTr=0; iTr<reco_mult; iTr++)
    {
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      if (!recoTrack) continue;
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      if (!mcTrack) continue;

      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      float phi = recoTrack->GetPhi();

      // Main track cuts
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      if (abs(eta) < eta_gap) continue;

      // Reco-specific track cuts
      if (recoTrack->GetNhits() < Nhits_cut) continue;
      //if (abs(recoTrack->GetDCAx()) > dca_cut) continue;
      //if (abs(recoTrack->GetDCAy()) > dca_cut) continue;
      //if (abs(recoTrack->GetDCAz()) > dca_cut) continue;
      if (mcTrack->GetMotherId() != motherId_cut) continue;

      TComplex u2 = TComplex(cos(2.*phi),sin(2.*phi));
      
      float v2TPC = 0.;
      if (eta < 0)
      {
        v2TPC = (float) (u2*TComplex::Conjugate(Qv2_R)).Re();
      }
      if (eta > 0)
      {
        v2TPC = (float) (u2*TComplex::Conjugate(Qv2_L)).Re();
      }
      v2TPC /= res_v2TPC_reco;

      int pidID = -1;
      // PID-related cut
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();

      for (int ipid=0; ipid < Npid; ipid++)
      {
        if (abs(pdgCodes.at(ipid)) == 999) continue;
        if (pdgCodes.at(ipid) == mcTrack->GetPdg()) pidID = ipid;
      }
      //float charge = recoTrack->GetCharge();

      //if (recoTrack->GetPidProbPion() > PidProb_cut && charge > 0)   pidID = 1; 
      //if (recoTrack->GetPidProbKaon() > PidProb_cut && charge > 0)   pidID = 2; 
      //if (recoTrack->GetPidProbProton() > PidProb_cut && charge > 0) pidID = 3; 
      //if (recoTrack->GetPidProbPion() > PidProb_cut && charge < 0)   pidID = 5; 
      //if (recoTrack->GetPidProbKaon() > PidProb_cut && charge < 0)   pidID = 6; 
      //if (recoTrack->GetPidProbProton() > PidProb_cut && charge < 0) pidID = 7; 

      if (charge > 0)
        pv2TPC[0]->Fill(pt, cent, v2TPC);
      if (charge < 0)
        pv2TPC[4]->Fill(pt, cent, v2TPC);

      if (pidID == -1) continue;

      pv2TPC[pidID]->Fill(pt, cent, v2TPC);

    } // end reco tracks loop

  } // end event loop

  //Writing output
  fo->cd();

  pResTPC->Write();

  for (int ipid=0; ipid < Npid; ipid++)
  {
    pv2TPC[ipid]->Write();
  }

  fo->Close();

  timer.Stop();
  timer.Print();
}
float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
    float fcent;
  if (bimp < 4.18)
    fcent = 0; // 0-10%
  else if (bimp < 6.01)
    fcent = 10; //10-20%
  else if (bimp < 7.37)
    fcent = 20; //20-30%
  else if (bimp < 8.52)
    fcent = 30; //30-40%
  else if (bimp < 9.57)
    fcent = 40; //40-50%
  else if (bimp < 10.55)
    fcent = 50; //50-60%
  else if (bimp < 11.46)
    fcent = 60; //60-70%
  else if (bimp < 12.31)
    fcent = 70; //70-80%
  else
    fcent = -1;

  if (fcent != -1)
    return fcent + 5.;
  else
    return -1;
}

int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 5.) return 0;
  if (cent == 15.) return 1;
  if (cent == 25.) return 2;
  if (cent == 35.) return 3;
  if (cent == 45.) return 4;
  if (cent == 55.) return 5;
  if (cent == 65.) return 6;
  if (cent == 75.) return 7;
  return -1;
}
// root -l -b -q get_flow_pico.C+'("/weekly/lbavinh/lbavinh/ScalarProduct/split/Reco_UrQMD_7.7/runlist_Reco_UrQMD_7.7_31.list","test.root")'
// root -l -b -q get_flow_pico.C+'("/weekly/lbavinh/lbavinh/ScalarProduct/split/Reco_UrQMD_11.5/runlist_Reco_UrQMD_11.5_04.list","/weekly/lbavinh/lbavinh/ScalarProduct/OUT/2119086/sum_2119086_5.root")'