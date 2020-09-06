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

// #include <Utils.C>

// R__LOAD_LIBRARY(libPicoDst.so)

// Event selection
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
const int Nhits_cut    = 32;
const float dca_cut    = 0.5;

// PID - general
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
const int Npid = 8; //pidNames.size()

// PID - mc/model tracks
const std::vector<int> pdgCodes = {999, 211, 321, 2212, -999, -211, -321, -2212};

// PID - reco tracks
const float PidProb_cut = 0.9;

// const std::vector<float> vResMcTpc   = {0.226827, 0.347749, 0.369009, 0.336583, 0.281697, 0.224447, 0.18955, 0.186935}; // Peter's res
// const std::vector<float> vResRecoTpc = {0.211611, 0.329277, 0.350632, 0.319347, 0.269741, 0.21128, 0.181021, 0.176676}; // Peter's res
const std::vector<float> vResMcTpc   = {0.226443,0.348428,0.36861,0.337042,0.281881,0.225086,0.190239,0.187385}; // my res
const std::vector<float> vResRecoTpc = {0.212417,0.329986,0.349994,0.319957,0.270354,0.211854,0.181174,0.178446}; // my res 

static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};
static const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
static const int ncent = 8; // 0-80%
static const int max_nh = 1700;


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

  // TProfile *pResMcTPC = new TProfile("pResMcTPC","Resolution for TPC EP MC", NcentBins, centBinMin, centBinMax);
  // TProfile *pResRecoTPC = new TProfile("pResRecoTPC","Resolution for TPC EP RECO", NcentBins, centBinMin, centBinMax);
  // TProfile2D *pv2mcTPC[Npid];
  // TProfile2D *pv2recoTPC[Npid];
  // for (int i=0; i < Npid; i++)
  // {
  //   pv2mcTPC[i] = new TProfile2D(Form("pv2mcTPC_pid%i", i), Form("v2(TPC EP) MC of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  //   pv2recoTPC[i] = new TProfile2D(Form("pv2recoTPC_pid%i", i), Form("v2(TPC EP) RECO of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  // }

  // TH2F *hQx_L_mc = new TH2F("hQx_L_mc","Qx from Left TPC MC",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQy_L_mc = new TH2F("hQy_L_mc","Qy from Left TPC MC",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQx_R_mc = new TH2F("hQx_R_mc","Qx from Right TPC MC", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQy_R_mc = new TH2F("hQy_R_mc","Qy from Right TPC MC", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQx_L_reco = new TH2F("hQx_L_reco","Qx from Left TPC RECO",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQy_L_reco = new TH2F("hQy_L_reco","Qy from Left TPC RECO",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQx_R_reco = new TH2F("hQx_R_reco","Qx from Right TPC RECO", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  // TH2F *hQy_R_reco = new TH2F("hQy_R_reco","Qy from Right TPC RECO", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);

  TH1I *hEvt;        // Event number 
  TH1F *hRP;         // reaction plane distr
  TH1F *hPt;         // transverse momentum distr
  TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
  TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
  TH1F *hEta;        // pseudorapidity
  TH1F *hBimp;       // impact parameter
  TH1I *hMult;       // emitted multiplicity
  TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

  // TProfile for reference flow (RF)
  // TProfile *hv2MC[ncent][npid]; // profile for MC integrated v2
  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow (DF)
  TProfile *hPT[ncent][npt][npid];     // profile pt
  // TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
  TProfile *hv22pt[ncent][npt][npid];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];  // profile <<4'>> from 4th Q-Cumulants

  // TProfile for covariance calculation according to (C.12), Appendix C
  // in Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider.
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>

  TProfile *hv2EP[ncent][npt][npid];	// elliptic flow from EP method
  TProfile *hv2EPMC[ncent][npt][npid];	// elliptic flow from EP method
  TProfile *hv22EP[ncent][npid];      // integrated flow from EP method

  TProfile *HRes[ncent];		// resolution
  TProfile *HResMC[ncent];		// resolution
  TProfile *hcounter[ncent][npt][npid];

  char name[800];
  char title[800];
  // d_outfile = new TFile(outputFileName.Data(), "recreate");
  // cout << outputFileName.Data() << " has been initialized" << endl;
  hEvt  = new TH1I("hEvt","Event number",1,0,1);
  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);



  for (int icent=0;icent<ncent;icent++){ // loop over centrality classes
    HRes[icent] = new TProfile(Form("HRes_%i",icent),Form("HRes_%i",icent),1,0.,1.);
    HResMC[icent] = new TProfile(Form("HResMC_%i",icent),Form("HResMC_%i",icent),1,0.,1.);
    hv22[icent] = new TProfile(Form("hv22_%i",icent),Form("hv22_%i",icent),1,0.,1.);
    hv24[icent] = new TProfile(Form("hv24_%i",icent),Form("hv24_%i",icent),1,0.,1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i",icent),Form("hcov24_%i",icent),1,0.,1.);
    for (int id=0;id<npid;id++){
      // hv2MC[icent][id] = new TProfile(Form("hv2MC_%i_%i",icent,id),Form("hv2MC_%i_%i",icent,id),1,0.,1.);
      hv22EP[icent][id] = new TProfile(Form("hv22EP_%i_%i",icent,id),Form("hv22EP_%i_%i",icent,id),1,0.,1.);
      // hv22[icent][id] = new TProfile(Form("hv22_%i_%i",icent,id),Form("hv22_%i_%i",icent,id),1,0.,1.);
      // hv24[icent][id] = new TProfile(Form("hv24_%i_%i",icent,id),Form("hv24_%i_%i",icent,id),1,0.,1.);
      // hcov24[icent][id] = new TProfile(Form("hcov24_%i_%i",icent,id),Form("hcov24_%i_%i",icent,id),1,0.,1.);
      for (int ipt = 0; ipt < npt; ipt++){ // loop over pt bin
        // hv2MCpt[icent][ipt] = new TProfile(Form("hv2MCpt_%i_%i_%i",icent,ipt,id),Form("hv2MCpt_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv2EP[icent][ipt][id] = new TProfile(Form("hv2EP_%i_%i_%i",icent,ipt,id),Form("hv2EP_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv2EPMC[icent][ipt][id] = new TProfile(Form("hv2EPMC_%i_%i_%i",icent,ipt,id),Form("hv2EPMC_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hPT[icent][ipt][id] = new TProfile(Form("hPT_%i_%i_%i",icent,ipt,id),Form("hPT_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv22pt[icent][ipt][id] = new TProfile(Form("hv22pt_%i_%i_%i",icent,ipt,id),Form("hv22pt_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv24pt[icent][ipt][id] = new TProfile(Form("hv24pt_%i_%i_%i",icent,ipt,id),Form("hv24pt_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov22prime[icent][ipt][id] = new TProfile(Form("hcov22prime_%i_%i_%i",icent,ipt,id),Form("hcov22prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov24prime[icent][ipt][id] = new TProfile(Form("hcov24prime_%i_%i_%i",icent,ipt,id),Form("hcov24prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov42prime[icent][ipt][id] = new TProfile(Form("hcov42prime_%i_%i_%i",icent,ipt,id),Form("hcov42prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov44prime[icent][ipt][id] = new TProfile(Form("hcov44prime_%i_%i_%i",icent,ipt,id),Form("hcov44prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov2prime4prime[icent][ipt][id] = new TProfile(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id),Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcounter[icent][ipt][id] = new TProfile(Form("hcounter_%i_%i_%i",icent,ipt,id),Form("hcounter_%i_%i_%i",icent,ipt,id),3,0.,3.);
      } // end of loop over pt bin
    }
  } // end of loop over centrality classes

  cout << "Histograms have been initialized" << endl;

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%1000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    // Get centrality
    int cent = GetCentBin(CentB(mcEvent->GetB()));
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

      // PID-related cut (or to cut out neutral particles)
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (charge == 0) continue;

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

      // hQx_L_mc->Fill(cent, Qx_L_mc);
      // hQy_L_mc->Fill(cent, Qy_L_mc);
      // hQx_R_mc->Fill(cent, Qx_R_mc);
      // hQy_R_mc->Fill(cent, Qy_R_mc);

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

      // hQx_L_reco->Fill(cent, Qx_L_reco);
      // hQy_L_reco->Fill(cent, Qy_L_reco);
      // hQx_R_reco->Fill(cent, Qx_R_reco);
      // hQy_R_reco->Fill(cent, Qy_R_reco);

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
      HResMC[cent]->Fill(0.5, res_mc);
    }
    if (PsiEP_L_reco != -999. && PsiEP_R_reco != -999.)
    {
      HRes[cent]->Fill(0.5, res_reco);
    }

    ////////////////////////////////////////////////////////////////////
    //
    // FLOW CALCULATIONS
    //
    ////////////////////////////////////////////////////////////////////
    
    // float res_v2TPC_mc = vResMcTpc.at(GetCentBin(cent));
    // float res_v2TPC_reco = vResRecoTpc.at(GetCentBin(cent));
    float res_v2TPC_mc = vResMcTpc.at(cent);
    float res_v2TPC_reco = vResRecoTpc.at(cent);
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
      int ipt = -1;
      for(int j=0; j<npt;j++) {if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;}
      if (charge > 0)
        // pv2mcTPC[0]->Fill(pt, cent, v2TPC);
        hv2EPMC[cent][ipt][0]->Fill(0.5,v2TPC);

      if (charge < 0)
        // pv2mcTPC[4]->Fill(pt, cent, v2TPC);
        hv2EPMC[cent][ipt][4]->Fill(0.5,v2TPC);
      if (pidID == -1) continue;

      // pv2mcTPC[pidID]->Fill(pt, cent, v2TPC);
      hv2EPMC[cent][ipt][pidID]->Fill(0.5,v2TPC);

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

      int ipt = -1;
      for(int j=0; j<npt;j++) {if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;}
      if (charge > 0)
        // pv2mcTPC[0]->Fill(pt, cent, v2TPC);
        hPT[cent][ipt][0]->Fill(0.5,pt);
        hv2EP[cent][ipt][0]->Fill(0.5,v2TPC);
        hv22EP[cent][0]->Fill(0.5,v2TPC);

      if (charge < 0)
        // pv2mcTPC[4]->Fill(pt, cent, v2TPC);
        hPT[cent][ipt][4]->Fill(0.5,pt);
        hv2EP[cent][ipt][4]->Fill(0.5,v2TPC);
        hv22EP[cent][4]->Fill(0.5,v2TPC);
      if (pidID == -1) continue;

      // pv2mcTPC[pidID]->Fill(pt, cent, v2TPC);
      hPT[cent][ipt][pidID]->Fill(0.5,pt);
      hv2EP[cent][ipt][pidID]->Fill(0.5,v2TPC);
      hv22EP[cent][pidID]->Fill(0.5,v2TPC);

    } // end reco tracks loop

  } // end event loop

  //Writing output
  fo->cd();

  // pResMcTPC->Write();
  // pResRecoTPC->Write();

  // for (int ipid=0; ipid < Npid; ipid++)
  // {
  //   pv2mcTPC[ipid]->Write();
  // }
  // for (int ipid=0; ipid < Npid; ipid++)
  // {
  //   pv2recoTPC[ipid]->Write();
  // }
  
  // hQx_L_mc->Write();
  // hQy_L_mc->Write();
  // hQx_R_mc->Write();
  // hQy_R_mc->Write();
  // hQx_L_reco->Write();
  // hQy_L_reco->Write();
  // hQx_R_reco->Write();
  // hQy_R_reco->Write();

  hEvt->Write();
  hRP->Write();
  hPt->Write();
  hPhi->Write();
  hPhil->Write();
  hEta->Write();
  hBimp->Write();
  hMult->Write();
  hBimpvsMult->Write();

  for (int icent=0;icent<ncent;icent++){
    HRes[icent]->Write();
    HResMC[icent]->Write();
    
    hv22[icent]->Write();
    hv24[icent]->Write();
    hcov24[icent]->Write();
    for (int id=0;id<npid;id++){
      hv22EP[icent][id]->Write();
      for (int ipt=0;ipt<npt;ipt++){
      
        hv22pt[icent][ipt][id]->Write();
        hv24pt[icent][ipt][id]->Write();
        hcov22prime[icent][ipt][id]->Write();
        hcov24prime[icent][ipt][id]->Write();
        hcov42prime[icent][ipt][id]->Write();
        hcov44prime[icent][ipt][id]->Write();
        hcov2prime4prime[icent][ipt][id]->Write();
        hPT[icent][ipt][id]->Write();
        hv2EP[icent][ipt][id]->Write();
        hv2EPMC[icent][ipt][id]->Write();
        hcounter[icent][ipt][id]->Write();          
      }
    }
  }


  fo->Close();

  timer.Stop();
  timer.Print();
}
