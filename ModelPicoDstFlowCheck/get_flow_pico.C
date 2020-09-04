// Do not forget to source setPicoDst.sh script

#include <iostream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TMath.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

#include <Utils.C>

// R__LOAD_LIBRARY(libPicoDst.so)

const std::vector<float> vResMcTpc   = {0.295164, 0.450308, 0.470348, 0.432475, 0.366723, 0.298105, 0.260313, 0.266459};
const std::vector<float> vResRecoTpc = {0.211611, 0.329277, 0.350632, 0.319347, 0.269741, 0.21128, 0.181021, 0.176676};

void get_flow_pico(TString inputFileName, TString outputFileName)
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

  TProfile *pResMcTPC = new TProfile("pResMcTPC","Resolution for TPC EP MC", NcentBins, centBinMin, centBinMax);
  TProfile *pResRecoTPC = new TProfile("pResRecoTPC","Resolution for TPC EP RECO", NcentBins, centBinMin, centBinMax);
  TProfile2D *pv2mcTPC[Npid];
  TProfile2D *pv2recoTPC[Npid];
  for (int i=0; i < Npid; i++)
  {
    pv2mcTPC[i] = new TProfile2D(Form("pv2mcTPC_pid%i", i), Form("v2(TPC EP) MC of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
    pv2recoTPC[i] = new TProfile2D(Form("pv2recoTPC_pid%i", i), Form("v2(TPC EP) RECO of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  }

  TH2F *hQx_L_mc = new TH2F("hQx_L_mc","Qx from Left TPC MC",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_L_mc = new TH2F("hQy_L_mc","Qy from Left TPC MC",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQx_R_mc = new TH2F("hQx_R_mc","Qx from Right TPC MC", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_R_mc = new TH2F("hQy_R_mc","Qy from Right TPC MC", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQx_L_reco = new TH2F("hQx_L_reco","Qx from Left TPC RECO",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_L_reco = new TH2F("hQy_L_reco","Qy from Left TPC RECO",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQx_R_reco = new TH2F("hQx_R_reco","Qx from Right TPC RECO", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_R_reco = new TH2F("hQy_R_reco","Qy from Right TPC RECO", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);

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

    // Read MC tracks
    float Qx_L_mc = 0., Qy_L_mc = 0., W_L_mc = 0.;
    float Qx_R_mc = 0., Qy_R_mc = 0., W_R_mc = 0.;
    int   Mult_L_mc = 0, Mult_R_mc = 0;
    float PsiEP_L_mc = 0., PsiEP_R_mc = 0.;
    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(iTr);
      if (!mcTrack) continue;

      float pt  = mcTrack->GetPt();
      float eta = mcTrack->GetEta();
      float phi = mcTrack->GetPhi();

      // Main track cuts
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      if (abs(eta) < eta_gap) continue;

      // Mc-specific track cuts
      if (mcTrack->GetMotherId() != motherId_cut) continue;

      // TPC Left EP
      if (eta < 0)
      {
        Qx_L_mc += pt * cos(2.* phi);
        Qy_L_mc += pt * sin(2.* phi);
        W_L_mc  += pt;
        Mult_L_mc++;
      }

      // TPC Right EP
      if (eta > 0)
      {
        Qx_R_mc += pt * cos(2.* phi);
        Qy_R_mc += pt * sin(2.* phi);
        W_R_mc  += pt;
        Mult_R_mc++;
      }
    } // end of mc track loop

    if (Mult_L_mc > mult_EP_cut && Mult_R_mc > mult_EP_cut)
    {
      Qx_L_mc /= W_L_mc;
      Qy_L_mc /= W_L_mc;
      Qx_R_mc /= W_R_mc;
      Qy_R_mc /= W_R_mc;

      hQx_L_mc->Fill(cent, Qx_L_mc);
      hQy_L_mc->Fill(cent, Qy_L_mc);
      hQx_R_mc->Fill(cent, Qx_R_mc);
      hQy_R_mc->Fill(cent, Qy_R_mc);

      PsiEP_L_mc = 0.5 * atan2(Qy_L_mc, Qx_L_mc);
      PsiEP_R_mc = 0.5 * atan2(Qy_R_mc, Qx_R_mc);
    }
    else
    {
      PsiEP_L_mc = -999.;
      PsiEP_R_mc = -999.;
    } 

    // Read Reco tracks
    float Qx_L_reco = 0., Qy_L_reco = 0., W_L_reco = 0.;
    float Qx_R_reco = 0., Qy_R_reco = 0., W_R_reco = 0.;
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

      // Reco-specific track cuts
      if (recoTrack->GetNhits() < Nhits_cut) continue;
      //if (abs(recoTrack->GetDCAx()) > dca_cut) continue;
      //if (abs(recoTrack->GetDCAy()) > dca_cut) continue;
      //if (abs(recoTrack->GetDCAz()) > dca_cut) continue;
      if (mcTrack->GetMotherId() != motherId_cut) continue;

      // TPC Left EP
      if (eta < 0)
      {
        Qx_L_reco += pt * cos(2.* phi);
        Qy_L_reco += pt * sin(2.* phi);
        W_L_reco  += pt;
        Mult_L_reco++;
      }

      // TPC Right EP
      if (eta > 0)
      {
        Qx_R_reco += pt * cos(2.* phi);
        Qy_R_reco += pt * sin(2.* phi);
        W_R_reco  += pt;
        Mult_R_reco++;
      }
    } // end of reco track loop

    if (Mult_L_reco > mult_EP_cut && Mult_R_reco > mult_EP_cut)
    {
      Qx_L_reco /= W_L_reco;
      Qy_L_reco /= W_L_reco;
      Qx_R_reco /= W_R_reco;
      Qy_R_reco /= W_R_reco;

      hQx_L_reco->Fill(cent, Qx_L_reco);
      hQy_L_reco->Fill(cent, Qy_L_reco);
      hQx_R_reco->Fill(cent, Qx_R_reco);
      hQy_R_reco->Fill(cent, Qy_R_reco);

      PsiEP_L_reco = 0.5 * atan2(Qy_L_reco, Qx_L_reco);
      PsiEP_R_reco = 0.5 * atan2(Qy_R_reco, Qx_R_reco);
    }
    else
    {
      PsiEP_L_reco = -999.;
      PsiEP_R_reco = -999.;
    } 

    float res_mc   = cos(2. * (PsiEP_R_mc - PsiEP_L_mc) );
    float res_reco = cos(2. * (PsiEP_R_reco - PsiEP_L_reco) );

    if (PsiEP_L_mc != -999. && PsiEP_R_mc != -999.)
    {
      pResMcTPC->Fill(cent, res_mc);
    }
    if (PsiEP_L_reco != -999. && PsiEP_R_reco != -999.)
    {
      pResRecoTPC->Fill(cent, res_reco);
    }

    ////////////////////////////////////////////////////////////////////
    //
    // FLOW CALCULATIONS
    //
    ////////////////////////////////////////////////////////////////////
    
    float res_v2TPC_mc = vResMcTpc.at(GetCentBin(cent));
    float res_v2TPC_reco = vResRecoTpc.at(GetCentBin(cent));

    // Read MC tracks
    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(iTr);
      if (!mcTrack) continue;

      float pt  = mcTrack->GetPt();
      float eta = mcTrack->GetEta();
      float phi = mcTrack->GetPhi();

      // Main track cuts
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      if (abs(eta) < eta_gap) continue;

      // Mc-specific track cuts
      if (mcTrack->GetMotherId() != motherId_cut) continue;

      // EP-related cut
      if (PsiEP_L_mc == -999.) continue;
      if (PsiEP_R_mc == -999.) continue;

      // PID-related cut
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      
      float v2TPC = 0.;
      if (eta < 0)
      {
        v2TPC = cos( 2. * (phi - PsiEP_R_mc) );
      }
      if (eta > 0)
      {
        v2TPC = cos( 2. * (phi - PsiEP_L_mc) );
      }
      v2TPC /= res_v2TPC_mc;

      int pidID = -1;
      float charge = 1./3.*particle->Charge();

      for (int ipid=0; ipid < Npid; ipid++)
      {
        if (abs(pdgCodes.at(ipid)) == 999) continue;
        if (pdgCodes.at(ipid) == mcTrack->GetPdg()) pidID = ipid;
      }

      if (charge > 0)
        pv2mcTPC[0]->Fill(pt, cent, v2TPC);
      if (charge < 0)
        pv2mcTPC[4]->Fill(pt, cent, v2TPC);

      if (pidID == -1) continue;

      pv2mcTPC[pidID]->Fill(pt, cent, v2TPC);

    } // end mc tracks loop

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

      // EP-related cut
      if (PsiEP_L_reco == -999.) continue;
      if (PsiEP_R_reco == -999.) continue;
      
      float v2TPC = 0.;
      if (eta < 0)
      {
        v2TPC = cos( 2. * (phi - PsiEP_R_reco) );
      }
      if (eta > 0)
      {
        v2TPC = cos( 2. * (phi - PsiEP_L_reco) );
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
        pv2recoTPC[0]->Fill(pt, cent, v2TPC);
      if (charge < 0)
        pv2recoTPC[4]->Fill(pt, cent, v2TPC);

      if (pidID == -1) continue;

      pv2recoTPC[pidID]->Fill(pt, cent, v2TPC);

    } // end reco tracks loop

  } // end event loop

  //Writing output
  fo->cd();

  pResMcTPC->Write();
  pResRecoTPC->Write();

  for (int ipid=0; ipid < Npid; ipid++)
  {
    pv2mcTPC[ipid]->Write();
  }
  for (int ipid=0; ipid < Npid; ipid++)
  {
    pv2recoTPC[ipid]->Write();
  }
  
  hQx_L_mc->Write();
  hQy_L_mc->Write();
  hQx_R_mc->Write();
  hQy_R_mc->Write();
  hQx_L_reco->Write();
  hQy_L_reco->Write();
  hQx_R_reco->Write();
  hQy_R_reco->Write();

  fo->Close();

  timer.Stop();
  timer.Print();
}
