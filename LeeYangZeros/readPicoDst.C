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

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>


float CentB(float bimp);
int GetCentBin(float cent);

using std::cout;
using std::endl;


void readPicoDst(TString inputFileName, TString outputFileName)
{
  TFile *inputDCAfile; // "/nica/mpd21/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_new_test_picodst/dca/dca_fit.root"
  // TF2 *fDCAx, *fDCAy, *fDCAz;

  TStopwatch timer;
  timer.Start();

  // inputDCAfile = new TFile("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_picodst/dca/dca_fit.root","read");
  
  // fDCAx = (TF2 *)inputDCAfile->Get("f_sigma0");
  // fDCAy = (TF2 *)inputDCAfile->Get("f_sigma1");
  // fDCAz = (TF2 *)inputDCAfile->Get("f_sigma2");

  static const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-

  static const int ncent = 9; // 0-80%
  // static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

  static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
  static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};

  static const double maxpt = 3.; // max pt
  static const double minpt = 0.2; // min pt

  static const float eta_cut =  1.5;
  static const float eta_gap = 0.05;
  static const int Nhits_cut = 16; // minimum nhits of reconstructed tracks
  static const float DCAcut = 0.5;
  static const int neta = 2; // [eta-,eta+]

  static const int max_nh = 1700;

  TFile *d_outfile; // out file with histograms and profiles
  TH1I *hEvt;        // Event number 
  TH1F *hRP;         // reaction plane distr
  TH1F *hPt;         // transverse momentum distr
  TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
  TH1F *hEta;        // pseudorapidity
  TH1F *hBimp;       // impact parameter
  TH1I *hMult;       // emitted multiplicity
  TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

  // Flow Analysis with Lee Yang Zeros Method
  const int rbins = 100;
  const int thetabins = 5;
  float theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    // float theta_width = TMath::Pi() / (2.0 * thetabins);
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
    // cout << theta[thetabin] << endl;
  }
  TProfile *LeeYangHistosS[ncent][thetabins];
  TH2F *hLeeYangHistosS[ncent][thetabins];
  TProfile *LeeYangHistosP[ncent][thetabins];
  TH2F *hLeeYangHistosP[ncent][thetabins];

  d_outfile = new TFile(outputFileName.Data(), "recreate");
  cout << outputFileName.Data() << " has been initialized" << endl;
  hEvt  = new TH1I("hEvt","Event number",1,0,1);
  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      LeeYangHistosS[i][j] = new TProfile(Form("LeeYangS_mult%d_theta%d", i, j), "", rbins, 0, 1, -1e10, 1e10);
      hLeeYangHistosS[i][j] = new TH2F(Form("hLeeYangS_mult%d_theta%d", i, j), "", rbins, 0, 1, 120, 0., 1.2);
      LeeYangHistosP[i][j] = new TProfile(Form("LeeYangP_mult%d_theta%d", i, j), "", rbins, 0, 1, -1e10, 1e10);
      hLeeYangHistosP[i][j] = new TH2F(Form("hLeeYangP_mult%d_theta%d", i, j), "", rbins, 0, 1, 120, 0., 1.2);
    }
  }

  cout << "Histograms have been initialized" << endl;

  // Configure input information
  // TChain *chain = new TChain("picodst");
  // chain->Add(inputFileName.Data());
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

  // chain->SetBranchAddress("mcevent.", &mcEvent);
  // chain->SetBranchAddress("recotracks",&recoTracks);
  tree->SetBranchAddress("mcevent.", &mcEvent);
  tree->SetBranchAddress("recotracks",&recoTracks);
  tree->SetBranchAddress("mctracks",&mcTracks);



  // TComplex Qtheta[thetabins];
  float Qtheta[thetabins];
  TComplex genfunS[rbins][thetabins]; // sum
  TComplex genfunP[rbins][thetabins]; // product
  TComplex cExpo;
  // const int multbins = 10; // we'll do just a few for now, may do more later



  float Q2x, Q2y;

  // Start event loop
  // int n_entries = chain->GetEntries();
  int n_entries = tree->GetEntriesFast();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%1000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    // chain->GetEntry(iEv);
    tree->GetEntry(iEv);
    hEvt -> Fill(1);
    // Read MC event
    float bimp = mcEvent->GetB();

    // Get centrality
    float cent = CentB(bimp);
    // if (cent == -1)
    if (cent != 25.)
      continue;
    int mult = 0;
    int fcent = GetCentBin(cent);

    hBimp -> Fill(bimp);

    for (int i = 0; i < thetabins; ++i)
    {
      // Qtheta[i] = TComplex(0.0, 0.0);
      Qtheta[i] = 0.;
    }
    for (int i = 0; i < rbins; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        genfunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
        genfunP[i][j] = TComplex(1.0, 0.0); // initialize to 1, calcualte via product
        // genfunP[i][j] = TComplex::One(); // initialize to 1, calcualte via product
      }
    }
    Q2x = 0.;
    Q2y = 0.;

    Int_t reco_mult = recoTracks->GetEntriesFast();
    for (int iTr=0; iTr<reco_mult; iTr++) { // track loop
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      if (!recoTrack) continue;
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      if (!mcTrack) continue;
      if (mcTrack->GetMotherId() != -1) continue;
      if (recoTrack->GetNhits() < Nhits_cut ) continue;
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      float phi = recoTrack->GetPhi();
      // if (abs(recoTrack->GetDCAx()) > DCAcut) continue; //трек не проходит по DCAx
      // if (abs(recoTrack->GetDCAy()) > DCAcut) continue; //трек не проходит по DCAy
      // if (abs(recoTrack->GetDCAz()) > DCAcut) continue; //трек не проходит по DCAz
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut) continue; // track selection
      // if (abs(eta)<eta_gap) continue;
      // if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      
      hPt->Fill(pt);
      hEta->Fill(eta);
      hPhi->Fill(phi);
      Q2x += TMath::Cos(2.0 * phi);
      Q2y += TMath::Sin(2.0 * phi);
      // ---------------------------------------------
      // --- calculate the product generating function
      // ---
      for (int rbin = 0; rbin < rbins; ++rbin)
      {
        double r = (double(rbin) / rbins);
        for (int thetabin = 0; thetabin < thetabins; ++thetabin)
        {
          // float angle = phi - theta[thetabin];
          genfunP[rbin][thetabin] *= TComplex(1.0, r * cos(2. * (phi - theta[thetabin])));
          
        }
      }
      mult++;


    } // end of track loop

    if (iEv % 10000 == 0) for (int thetabin = 0; thetabin < thetabins; ++thetabin) cout << genfunP[0][thetabin].Rho2() << endl;
    // -------------------------------------------
    // --- fill the generating function histograms
    // ---
    // Q2x /= mult;
    // Q2y /= mult;
    for (int thetabin = 0; thetabin < thetabins; ++thetabin)
    {

      Qtheta[thetabin] = Q2x * TMath::Cos(2.0 * theta[thetabin]) + Q2y * TMath::Sin(2.0 * theta[thetabin]);
    }

    for (int rbin = 0; rbin < rbins; ++rbin)
    {
      double r = (double(rbin) / rbins);
      for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      {
        cExpo = TComplex(0., r * Qtheta[thetabin]);
        genfunS[rbin][thetabin] = TComplex::Exp(cExpo); // generating function from Q-vectors
        LeeYangHistosS[fcent][thetabin]->Fill(r, genfunS[rbin][thetabin].Rho());
        hLeeYangHistosS[fcent][thetabin]->Fill(r, genfunS[rbin][thetabin].Rho());
        LeeYangHistosP[fcent][thetabin]->Fill(r, genfunP[rbin][thetabin].Rho2());
        hLeeYangHistosP[fcent][thetabin]->Fill(r, genfunP[rbin][thetabin].Rho2());
      }
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

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if (bimp < 2.91)
    fcent = 2.5; // 0-5%
  else if (bimp < 4.18)
    fcent = 7.5; // 5-10%
  else if (bimp < 6.01)
    fcent = 15.; // 10-20%
  else if (bimp < 7.37)
    fcent = 25.; // 20-30%
  else if (bimp < 8.52)
    fcent = 35.; // 30-40%
  else if (bimp < 9.57)
    fcent = 45.; // 40-50%
  else if (bimp < 10.55)
    fcent = 55.; // 50-60%
  else if (bimp < 11.46)
    fcent = 65.; // 60-70%
  else if (bimp < 12.31)
    fcent = 75.; // 70-80%
  else
    fcent = -1;
  return fcent;
}

int GetCentBin(float cent)
{
  if (cent == -1)
    return -1;
  if (cent == 2.5)
    return 0;
  if (cent == 7.5)
    return 1;
  if (cent == 15.)
    return 2;
  if (cent == 25.)
    return 3;
  if (cent == 35.)
    return 4;
  if (cent == 45.)
    return 5;
  if (cent == 55.)
    return 6;
  if (cent == 65.)
    return 7;
  if (cent == 75.)
    return 8;
  return -1;
}

// source /weekly/lbavinh/Soft/PicoDst/build/setPicoDst.sh 
// root -l -b -q readPicoDst.C+'("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/merged_new/picodst_merged_9.root","test.root")'