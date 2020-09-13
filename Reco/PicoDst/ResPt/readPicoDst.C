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
#include <TF2.h>
#include <TProfile.h>
#include <TComplex.h>
#include <TDatabasePDG.h>
#include <TProfile2D.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>


#include "function.C"
// R__LOAD_LIBRARY(libPicoDst.so)


void readPicoDst(TString inputFileName, TString outputFileName)
{
  // TFile *inputDCAfile; // "/nica/mpd21/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_new_test_picodst/dca/dca_fit.root"
  // TF2 *fDCAx, *fDCAy, *fDCAz;

  TStopwatch timer;
  timer.Start();

  // inputDCAfile = new TFile("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_picodst/dca/dca_fit.root","read");
  
  // fDCAx = (TF2 *)inputDCAfile->Get("f_sigma0");
  // fDCAy = (TF2 *)inputDCAfile->Get("f_sigma1");
  // fDCAz = (TF2 *)inputDCAfile->Get("f_sigma2");

  const int NcentBins     = 8;
  const double centBinMin = 0.;
  const double centBinMax = 80.;
  const int NptBins       = 300;
  const double ptBinMin   = 0.;
  const double ptBinMax   = 3.;

  static const double maxpt = 3.; // max pt
  static const double minpt = 0.; // min pt

  static const float eta_cut =  1.5; // min pt
  static const float eta_gap = 0.05; // min pt
  static const int Nhits = 16; // minimum nhits of reconstructed tracks
  // static const float DCAcut = 0.5;

  static const int max_nh = 2500;

  TFile *d_outfile; // out file with histograms and profiles
  TH1I *hEvt;        // Event number 
  TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
  TH1F *hPhil_MC;    // distr of particle azimuthal angle in the laboratory coordinate system
  TH1F *hEta;        // pseudorapidity
  TH1F *hEta_MC;        // pseudorapidity
  TH1F *hBimp;       // impact parameter
  TH1I *hMult;       // emitted multiplicity
  TH1I *hMult_MC;    // emitted multiplicity
  TH1F *hPt;         // transverse momentum distr
  TH1F *hPt_MC;         // transverse momentum distr
  TProfile2D *prResPt;
  char name[800];
  char title[800];
  d_outfile = new TFile(outputFileName.Data(),"recreate");
  cout << outputFileName.Data() << " has been initialized" << endl;
  hEvt  = new TH1I("hEvt","Event number",1,0,1);
  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hMult_MC = new TH1I("hMult_MC", "Multiplicity distr_MC;M;dN/dM", max_nh, 0, max_nh);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN_{reco}/dp_{T}", NptBins, ptBinMin, ptBinMax);
  hPt_MC = new TH1F("hPt_MC", "Pt-distr_MC;p_{T} (GeV/c); dN_{MC}/dp_{T}", NptBins, ptBinMin, ptBinMax);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hPhil_MC = new TH1F("hPhil_MC", "Azimuthal angle distr in laboratory coordinate system_MC; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 400,-2.,2.);
  hEta_MC = new TH1F("hEta_MC", "Pseudorapidity distr_MC; #eta; dN/d#eta", 400,-2.,2.);
  prResPt = new TProfile2D("prResPt","Pt resolution;p_{T} [GeV/c];cent [%]",NptBins,ptBinMin,ptBinMax,NcentBins,centBinMin,centBinMax);

  cout << "Histograms have been initialized" << endl;

  // Configure input information
  TFile *treefile = TFile::Open(inputFileName.Data());
  TTree *tree = (TTree *)treefile->Get("picodst");
  if (!tree){
    cout << "picodst is not found in " << inputFileName.Data() << endl;
    treefile->Close();
    return;
  }
  cout << inputFileName.Data() << " is opened" << endl;
  PicoDstMCEvent *mcEvent = nullptr;
  TClonesArray *recoTracks = nullptr;
  TClonesArray *mcTracks = nullptr;

  tree->SetBranchAddress("mcevent.", &mcEvent);
  tree->SetBranchAddress("recotracks",&recoTracks);
  tree->SetBranchAddress("mctracks",&mcTracks);

  // Start event loop
  // int n_entries = chain->GetEntries();
  int n_entries = tree->GetEntriesFast();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%1000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    tree->GetEntry(iEv);
    hEvt -> Fill(1);
    // Read MC event
    float bimp = mcEvent->GetB();
    float fcent = CentB(bimp);
    if (fcent < 0) continue;
    hBimp -> Fill(bimp);
    Int_t reco_mult = recoTracks->GetEntriesFast();
    Int_t mc_num_particles = mcTracks->GetEntriesFast();
    hMult -> Fill(reco_mult);
    hMult_MC -> Fill(mc_num_particles);
    // Read MC tracks
    for (int iTr=0; iTr<mc_num_particles; iTr++) { // track loop
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(iTr);
      if (mcTrack->GetMotherId() != -1) continue;
      float pt  = mcTrack->GetPt();
      float eta = mcTrack->GetEta();
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // Main track cuts
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      float charge = 1./3.*particle->Charge();
      if (charge == 0) continue;
      float phi = mcTrack->GetPhi();
      if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

      hPt_MC -> Fill(pt);
      hEta_MC -> Fill(eta);
      hPhil_MC -> Fill(phi);
    } // end of track loop
    // Read Reco tracks
    for (int iTr=0; iTr<reco_mult; iTr++)
    {
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      float phi = recoTrack->GetPhi();
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // Main track cuts
      // auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      // float charge = 1./3.*particle->Charge();
      // if (charge == 0) continue;
      // Reco-specific track cuts
      if (recoTrack->GetNhits() < Nhits) continue;
      if (mcTrack->GetMotherId() != -1) continue;
      if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */
      hPt -> Fill(pt);
      hEta -> Fill(eta);
      hPhil -> Fill(phi);
      float pt_MC  = mcTrack->GetPt();
      float resPt = (pt-pt_MC)/pt;
      prResPt->Fill(pt,fcent,resPt);
    }
  } // end event loop

  // Write histograms to out file
  d_outfile -> cd();
  d_outfile -> Write();
  d_outfile -> Close();
  cout << "Histfile has been written" << endl;

  timer.Stop();
  timer.Print();
}
// root -l -b -q readPicoDst.C+'("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/merged_new/picodst_merged_600.root","test.root")'
