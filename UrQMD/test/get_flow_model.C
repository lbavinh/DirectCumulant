#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>

#include "utilities.C"

#define MAX_TRACKS 10000


void get_flow_model(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration

  // Profile info - general
  const int nCentBins     = 8;
  const double centBinMin = 0.;
  const double centBinMax = 80.;
  const int nPtBins       = 300;
  const double ptBinMin   = 0.;
  const double ptBinMax   = 3.;
  const int nQvBins       = 240;
  const double QvBinMin   = -1.2;
  const double QvBinMax   = 1.2;
  const int nEta = 2; // Number of eta-subevent
  // Track cuts - general
  const float pt_min_cut = 0.2;
  const float pt_max_cut = 3.;
  const float eta_cut    = 1.5;
  const float eta_gap    = 0.05;
  const int   mult_EP_cut= 2;

  // Track cuts - mc tracks
  // const int motherId_cut = -1;

  // Track cuts - reco tracks
  // const int Nhits_cut    = 32;
  // const float dca_cut    = 0.5;
  
  // Method for flow measurements
  const int nMethod = 7; // 2QC,FHCal; 2QC,eta-gap; 2QC; 4QC; TPC,EP; TPC,SP; FHCal,EP
  const std::vector<TString> methodNames = {"2QC,eta-gap (FHCal)","2QC,eta-gap (TPC)","2QC","4QC","TPC,EP","TPC,SP","FHCal,EP"};

  // PID - general
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
  const int nPID = 8; //pidNames.size()

  // PID - mc/model tracks
  const std::vector<int> pdgCodes = {999, 211, 321, 2212, -999, -211, -321, -2212};

  // PID - reco tracks
  // const float PidProb_cut = 0.9;

  // const std::vector<float> vResTpc     = {6.27383, 8.52203, 7.73442, 5.99234, 4.13289, 2.57332, 1.55835, 1.06316}; // 7.7
  // const std::vector<float> vResTpc     = {8.57096, 10.8675, 9.73692, 7.45796, 5.10023, 3.16144, 1.87627, 1.22423}; // 11.5
  // Configure input information
  TChain *chain = new TChain("mctree");

  std::ifstream file(inputFileName.Data());
  std::string line;
  while(std::getline(file, line))
  {
      chain->Add(line.c_str());
  }

  Float_t         bimp;
  Float_t         phi2;
  Float_t         phi3;
  Float_t         ecc2;
  Float_t         ecc3;
  Int_t           npart;
  Int_t           nh;
  Float_t         momx[MAX_TRACKS];   //[nh]
  Float_t         momy[MAX_TRACKS];   //[nh]
  Float_t         momz[MAX_TRACKS];   //[nh]
  Float_t         ene[MAX_TRACKS];   //[nh]
  Int_t           hid[MAX_TRACKS];   //[nh]
  Int_t           pdg[MAX_TRACKS];   //[nh]
  Short_t         charge[MAX_TRACKS];   //[nh]

  // List of branches
  TBranch        *b_bimp;   //!
  TBranch        *b_phi2;   //!
  TBranch        *b_phi3;   //!
  TBranch        *b_ecc2;   //!
  TBranch        *b_ecc3;   //!
  TBranch        *b_npart;   //!
  TBranch        *b_nh;   //!
  TBranch        *b_momx;   //!
  TBranch        *b_momy;   //!
  TBranch        *b_momz;   //!
  TBranch        *b_ene;   //!
  TBranch        *b_hid;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_charge;   //!

  chain->SetBranchAddress("bimp", &bimp, &b_bimp);
  chain->SetBranchAddress("phi2", &phi2, &b_phi2);
  chain->SetBranchAddress("phi3", &phi3, &b_phi3);
  chain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  chain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  chain->SetBranchAddress("npart", &npart, &b_npart);
  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("momx", momx, &b_momx);
  chain->SetBranchAddress("momy", momy, &b_momy);
  chain->SetBranchAddress("momz", momz, &b_momz);
  chain->SetBranchAddress("ene", ene, &b_ene);
  chain->SetBranchAddress("hid", hid, &b_hid);
  chain->SetBranchAddress("pdg", pdg, &b_pdg);
  chain->SetBranchAddress("charge", charge, &b_charge);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(),"recreate");

  // QA histograms
  TH1I *hEvt  = new TH1I("hEvt","Event number",1,0,1);
  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 250, 0, 2500);
  TH2F *hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 250, 0, 2500, 200, 0., 20.);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr;#phi; dN/d#phi", 350, -3.5, 3.5);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);
  TH2F *hQx_L = new TH2F("hQx_L","Qx from Left TPC",  nCentBins, centBinMin, centBinMax, nQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_L = new TH2F("hQy_L","Qy from Left TPC",  nCentBins, centBinMin, centBinMax, nQvBins, QvBinMin, QvBinMax);
  TH2F *hQx_R = new TH2F("hQx_R","Qx from Right TPC", nCentBins, centBinMin, centBinMax, nQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_R = new TH2F("hQy_R","Qy from Right TPC", nCentBins, centBinMin, centBinMax, nQvBins, QvBinMin, QvBinMax);
  
  // Methods of flow measurement: QC2,FHCal; QC2,eta-gap; QC2; QC4; TPC,EP; TPC,SP; FHCal,EP
  TProfile *pCorrelator2EtaGap_FHCal = new TProfile("pCorrelator2EtaGap_FHCal","2nd order correlator with eta-gap, FHCal", nCentBins, centBinMin, centBinMax);
  TProfile *pCorrelator2EtaGap = new TProfile("pCorrelator2EtaGap","2nd order correlator with eta-gap, TPC", nCentBins, centBinMin, centBinMax);
  TProfile *pCorrelator2 = new TProfile("pCorrelator2","2nd order correlator", nCentBins, centBinMin, centBinMax);
  TProfile *pCorrelator4 = new TProfile("pCorrelator4","4th order correlator", nCentBins, centBinMin, centBinMax);
  
  TProfile *pResTPC_EP = new TProfile("pResTPC_EP","Resolution for TPC EP", nCentBins, centBinMin, centBinMax);  
  TProfile *pResTPC_SP = new TProfile("pResTPC_SP","Resolution for TPC SP", nCentBins, centBinMin, centBinMax);
  TProfile *pResFHCal_EP = new TProfile("pResFHCal_EP","Resolution for FHCal EP", nCentBins, centBinMin, centBinMax);
  
  TProfile2D *pReducedCorrelator2EtaGap_FHCal[nPID]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2EtaGap[nPID]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2[nPID]; // <<2'>>
  TProfile2D *pReducedCorrelator4[nPID]; // <<4'>>
  
  TProfile2D *pv2TPC_EP[nPID];
  TProfile2D *pv2TPC_SP[nPID];
  TProfile2D *pv2FHCal_EP[nPID];
  TProfile *pReducedCorrelator2_test[nPID][nCentBins];
  for (int i=0; i<nPID; i++)
  {
    pReducedCorrelator2EtaGap_FHCal[i] = new TProfile2D(Form("pReducedCorrelator2EtaGap_FHCal_pid%i", i), Form("Reduced 2nd order correlator with eta-gap of %s (FHCal)", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pReducedCorrelator2EtaGap_FHCal[i]->Sumw2();
    pReducedCorrelator2EtaGap[i] = new TProfile2D(Form("pReducedCorrelator2EtaGap_pid%i", i), Form("Reduced 2nd order correlator with eta-gap of %s (TPC", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pReducedCorrelator2EtaGap[i]->Sumw2();
    pReducedCorrelator2[i] = new TProfile2D(Form("pReducedCorrelator2_pid%i", i), Form("Reduced 2nd order correlator of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pReducedCorrelator2[i]->Sumw2();
    pReducedCorrelator4[i] = new TProfile2D(Form("pReducedCorrelator4_pid%i", i), Form("Reduced 4th order correlator of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pReducedCorrelator4[i]->Sumw2();
    pv2TPC_EP[i] = new TProfile2D(Form("pv2TPC_EP_pid%i", i), Form("v2(TPC EP) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pv2TPC_SP[i] = new TProfile2D(Form("pv2TPC_SP_pid%i", i), Form("v2(TPC SP) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pv2FHCal_EP[i] = new TProfile2D(Form("pv2FHCal_EP_pid%i", i), Form("v2(FHCal EP) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    for (int c=0; c<nCentBins; c++){
      pReducedCorrelator2_test[i][c] = new TProfile(Form("pReducedCorrelator2_test_pid%i_cent%i", i, c), Form("Reduced 2nd order correlator of %s, cent %i", pidNames.at(i).Data(), c), nPtBins, ptBinMin, ptBinMax);
    }
  }

  // Statistical errors of QC
  TProfile2D *pCov22RedEtaGap_FHCal[nPID];
  TProfile2D *pCov22RedEtaGap[nPID];
  TProfile *pCov24 = new TProfile("pCov24","Covariance(<2>,<4>)", nCentBins, centBinMin, centBinMax);
  TProfile2D *pCov22Red[nPID];
  TProfile2D *pCov24Red[nPID];
  TProfile2D *pCov42Red[nPID];
  TProfile2D *pCov44Red[nPID];
  TProfile2D *pCov2Red4Red[nPID];
  TProfile2D *pPt[nPID][nMethod];

  for (int i=0; i<nPID; i++)
  {
    pCov22RedEtaGap_FHCal[i] = new TProfile2D(Form("pCov22RedEtaGap_FHCal_pid%i", i), Form("Covariance(<2>,<2'>) with eta-gap of %s (FHCal)", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pCov22RedEtaGap[i] = new TProfile2D(Form("pCov22RedEtaGap_pid%i", i), Form("Covariance(<2>,<2'>) with eta-gap of %s (TPC)", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pCov22Red[i] = new TProfile2D(Form("pCov22Red_pid%i", i), Form("Covariance(<2>,<2'>) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pCov24Red[i] = new TProfile2D(Form("pCov24Red_pid%i", i), Form("Covariance(<2>,<4'>) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pCov42Red[i] = new TProfile2D(Form("pCov42Red_pid%i", i), Form("Covariance(<4>,<2'>) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pCov44Red[i] = new TProfile2D(Form("pCov44Red_pid%i", i), Form("Covariance(<4>,<4'>) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    pCov2Red4Red[i] = new TProfile2D(Form("pCov2Red4Red_pid%i", i), Form("Covariance(<4'>,<2'>) of %s", pidNames.at(i).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    for (int m=0; m<nMethod; m++)
    {
      pPt[i][m] = new TProfile2D(Form("pPt_pid%i_meth%i", i, m), Form("p_{T} distr. of %s, %s", pidNames.at(i).Data(),methodNames.at(m).Data()), nPtBins, ptBinMin, ptBinMax, nCentBins, centBinMin, centBinMax);
    }
  }

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%10000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    hEvt -> Fill(0);
    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1) continue;

    Int_t mc_num_particles = nh;
    
    // QA histograms
    hMult -> Fill(mc_num_particles);
    hBimp -> Fill(bimp);
    hBimpvsMult -> Fill(mc_num_particles,bimp);

    // (2QC, FHCal) event global variables
    double Qx2Gap_FHCal[nEta]={0.}, Qy2Gap_FHCal[nEta]={0.};
    double px2Gap_FHCal[nEta][nPtBins][nPID]={{{0.}}}, py2Gap_FHCal[nEta][nPtBins][nPID]={{{0.}}};
    TComplex Q2Gap_FHCal[nEta]={0.}, p2Gap_FHCal[nEta][nPtBins][nPID]={{{0.}}};
    double MGap_FHCal[nEta]={0};
    double mpGap_FHCal[nEta][nPtBins][nPID]={{{0.}}};
    double w2Gap_FHCal=0.;
    double wred2Gap_FHCal[nEta][nPtBins][nPID]={{{0.}}};
    double cor22Gap_FHCal=0.;
    double redCor22Gap_FHCal[nEta][nPtBins][nPID]={{{0.}}};

    // (2QC, eta-gap TPC) event global variables
    double Qx2Gap[nEta]={0.}, Qy2Gap[nEta]={0.};
    double px2Gap[nEta][nPtBins][nPID]={{{0.}}}, py2Gap[nEta][nPtBins][nPID]={{{0.}}};
    TComplex Q2Gap[nEta]={0.}, p2Gap[nEta][nPtBins][nPID]={{{0.}}};
    double MGap[nEta]={0};
    double mpGap[nEta][nPtBins][nPID]={{{0.}}};
    double w2Gap=0.;
    double wred2Gap[nEta][nPtBins][nPID]={{{0.}}};
    double cor22Gap=0.;
    double redCor22Gap[nEta][nPtBins][nPID]={{{0.}}};

    // (2QC; 4QC) event global variables
    double Qx2=0., Qy2=0., Qx4=0., Qy4=0.;
    TComplex Q2=0., Q4=0.;
    double px2[nPtBins][nPID]={{0.}}, py2[nPtBins][nPID]={{0.}};
    TComplex p2[nPtBins][nPID]={{0.}}, p4[nPtBins][nPID]={{0.}}, q2[nPtBins][nPID]={{0.}}, q4[nPtBins][nPID]={{0.}};
    double qx2[nPtBins][nPID]={{0.}}, qy2[nPtBins][nPID]={{0.}}, qx4[nPtBins][nPID]={{0.}}, qy4[nPtBins][nPID]={{0.}};
    double M = 0.;
    double mq[nPtBins][nPID]={{0.}},mp[nPtBins][nPID]={{0.}};
    double redCor22[nPtBins][nPID]={{0.}}, redCor24[nPtBins][nPID]={{0.}};
    double w2=0.,w4=0.;
    double wred2[nPtBins][nPID]={{0.}},wred4[nPtBins][nPID]={{0.}};
    double cor22 = 0., cor24 = 0.;

    // (TPC, EP & SP) event global variables
    float Qx_L_EP = 0., Qy_L_EP = 0., W_L_EP = 0.; // Left TPC, EP
    float Qx_R_EP = 0., Qy_R_EP = 0., W_R_EP = 0.; // Right TPC, EP
    float Qx_L_SP = 0., Qy_L_SP = 0.; // Left TPC, SP
    float Qx_R_SP = 0., Qy_R_SP = 0.; // Right TPC, SP
    int   Mult_L = 0, Mult_R = 0; // Multiplicity in each eta-subevent
    float PsiEP_L = 0., PsiEP_R = 0.;
    TComplex Qv2_L = 0., Qv2_R = 0.; // SP
    
    // FHCal, EP
    float Qx_L_FHCal = 0., Qy_L_FHCal = 0., W_L_FHCal = 0.; // Left FHCal
    float Qx_R_FHCal = 0., Qy_R_FHCal = 0., W_R_FHCal = 0.; // Right FHCal
    int   Mult_L_FHCal = 0, Mult_R_FHCal = 0; // Multiplicity in each eta-subevent
    float Psi_L_FHCal = 0., Psi_R_FHCal = 0.;
    float Psi_FHCal = 0.;
    ////////////////////////////////////////////////////////////////////
    //
    // 1ST TRACK LOOP: (RESOLUTION CALCULATIONS FOR SP,EP) + (MULTIPARTICLE CORRELATIONS)
    //
    ////////////////////////////////////////////////////////////////////

    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      
      TVector3 vect(momx[iTr], momy[iTr], momz[iTr]);

      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTr]);
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (pt >= pt_min_cut && pt <= pt_max_cut)
      { // Main track cuts for: 2QC, FHCal, Reference flow & FHCal, EP resolution
        if (eta > -5. && eta < -2.)
        { // Left FHCal
          Qx2Gap_FHCal[0]+=TMath::Cos(2.*phi);
          Qy2Gap_FHCal[0]+=TMath::Sin(2.*phi);
          MGap_FHCal[0]++;

          Qx_L_FHCal += -1.*pt*TMath::Cos(1.*phi);
          Qy_L_FHCal += -1.*pt*TMath::Cos(1.*phi);
          W_L_FHCal  += pt;
          Mult_L_FHCal++;
        }
        if (eta > 2. && eta < 5.)
        { // Right FHCal
          Qx2Gap_FHCal[1]+=TMath::Cos(2.*phi);
          Qy2Gap_FHCal[1]+=TMath::Sin(2.*phi);
          MGap_FHCal[1]++;

          Qx_R_FHCal += 1.*pt*TMath::Cos(1.*phi);
          Qy_R_FHCal += 1.*pt*TMath::Cos(1.*phi);
          W_R_FHCal  += pt;
          Mult_R_FHCal++;
        }
      }

      if (pt >= pt_min_cut && pt <= pt_max_cut && abs(eta) <= eta_cut && charge != 0)
      { // Main track cuts for TPC,EP resolution & TPC,QC Reference flow
        double cos4phi = TMath::Cos(4.*phi);
        double sin4phi = TMath::Sin(4.*phi);
        double cos2phi = TMath::Cos(2.*phi);
        double sin2phi = TMath::Sin(2.*phi);

        Qx2+=cos2phi;
        Qy2+=sin2phi;
        Qx4+=cos4phi;
        Qy4+=sin4phi;
        M++;

        // TPC Left
        if (eta < -eta_gap)
        {
          // 2QC, eta-gap
          Qx2Gap[0]+=cos2phi;
          Qy2Gap[0]+=sin2phi;
          MGap[0]++;
          // SP
          Qx_L_SP += 1. * cos2phi;
          Qy_L_SP += 1. * sin2phi;
          // EP
          Qx_L_EP += pt * cos2phi;
          Qy_L_EP += pt * sin2phi;
          W_L_EP  += pt;
          Mult_L++;
        }

        // TPC Right
        if (eta > eta_gap)
        {
          // 2QC, eta-gap
          Qx2Gap[1]+=cos2phi;
          Qy2Gap[1]+=sin2phi;
          MGap[1]++;
          // SP
          Qx_R_SP += 1. * cos2phi;
          Qy_R_SP += 1. * sin2phi;
          // EP
          Qx_R_EP += pt * cos2phi;
          Qy_R_EP += pt * sin2phi;
          W_R_EP  += pt;
          Mult_R++;
        }
      }
      if (pt >= ptBinMin && pt <= ptBinMax && abs(eta) <= eta_cut && charge != 0)
      { // Main track cuts for Differential flow of QC method
        int pidID = -1;
        for (int ipid=0; ipid < nPID; ipid++)
        {
          if (abs(pdgCodes.at(ipid)) == 999) continue;
          if (pdgCodes.at(ipid) == pdg[iTr]) pidID = ipid;
        }

        int ipt = -1;
        for(int j=0; j<nPtBins; j++)
        {
          if (pt >= (ptBinMax-ptBinMin)/nPtBins*j && pt < (ptBinMax-ptBinMin)/nPtBins*(j+1)) ipt = j;
        }

        double cos4phi = TMath::Cos(4.*phi);
        double sin4phi = TMath::Sin(4.*phi);
        double cos2phi = TMath::Cos(2.*phi);
        double sin2phi = TMath::Sin(2.*phi);

        // 2QC,FHCal
        if (eta < 0){ // Left FHCal
          if (charge>0){
            px2Gap_FHCal[1][ipt][0]+=cos2phi;
            py2Gap_FHCal[1][ipt][0]+=sin2phi;
            mpGap_FHCal[1][ipt][0]++;
            pPt[0][0] -> Fill(pt, cent, pt, 1.);
          }
          if (charge<0){
            px2Gap_FHCal[1][ipt][4]+=cos2phi;
            py2Gap_FHCal[1][ipt][4]+=sin2phi;
            mpGap_FHCal[1][ipt][4]++;
            pPt[4][0] -> Fill(pt, cent, pt, 1.);
          }
          if (pidID>0){
            px2Gap_FHCal[1][ipt][pidID]+=cos2phi;
            py2Gap_FHCal[1][ipt][pidID]+=sin2phi;
            mpGap_FHCal[1][ipt][pidID]++;
            pPt[pidID][0] -> Fill(pt, cent, pt, 1.);
          }
        }
        if (eta > 0){  // Right FHCal
          if (charge>0){
            px2Gap_FHCal[0][ipt][0]+=cos2phi;
            py2Gap_FHCal[0][ipt][0]+=sin2phi;
            mpGap_FHCal[0][ipt][0]++;
            pPt[0][0] -> Fill(pt, cent, pt, 1.);
          }
          if (charge<0){
            px2Gap_FHCal[0][ipt][4]+=cos2phi;
            py2Gap_FHCal[0][ipt][4]+=sin2phi;
            mpGap_FHCal[0][ipt][4]++;
            pPt[4][0] -> Fill(pt, cent, pt, 1.);
          }
          if (pidID>0){
            px2Gap_FHCal[0][ipt][pidID]+=cos2phi;
            py2Gap_FHCal[0][ipt][pidID]+=sin2phi;
            mpGap_FHCal[0][ipt][pidID]++;
            pPt[pidID][0] -> Fill(pt, cent, pt, 1.);
          }
        }
        // 2QC,eta-gap
        if (eta <-eta_gap){
          if (charge>0){
            px2Gap[1][ipt][0]+=cos2phi;
            py2Gap[1][ipt][0]+=sin2phi;
            mpGap[1][ipt][0]++;
            pPt[0][1] -> Fill(pt, cent, pt, 1.);
          }
          if (charge<0){
            px2Gap[1][ipt][4]+=cos2phi;
            py2Gap[1][ipt][4]+=sin2phi;
            mpGap[1][ipt][4]++;
            pPt[4][1] -> Fill(pt, cent, pt, 1.);
          }
          if (pidID>0){
            px2Gap[1][ipt][pidID]+=cos2phi;
            py2Gap[1][ipt][pidID]+=sin2phi;
            mpGap[1][ipt][pidID]++;
            pPt[pidID][1] -> Fill(pt, cent, pt, 1.);
          }
        }
        if (eta > eta_gap){
          if (charge>0){
            px2Gap[0][ipt][0]+=cos2phi;
            py2Gap[0][ipt][0]+=sin2phi;
            mpGap[0][ipt][0]++;
            pPt[0][1] -> Fill(pt, cent, pt, 1.);
          }
          if (charge<0){
            px2Gap[0][ipt][4]+=cos2phi;
            py2Gap[0][ipt][4]+=sin2phi;
            mpGap[0][ipt][4]++;
            pPt[4][1] -> Fill(pt, cent, pt, 1.);
          }
          if (pidID>0){
            px2Gap[0][ipt][pidID]+=cos2phi;
            py2Gap[0][ipt][pidID]+=sin2phi;
            mpGap[0][ipt][pidID]++;
            pPt[pidID][1] -> Fill(pt, cent, pt, 1.);
          }
        }

        // 2QC, 4QC
        if (charge>0){
          px2[ipt][0]+=cos2phi;
          py2[ipt][0]+=sin2phi;
          mp[ipt][0]++;
          
          qx2[ipt][0]+=cos2phi;
          qy2[ipt][0]+=sin2phi;
          qx4[ipt][0]+=cos4phi;
          qy4[ipt][0]+=sin4phi;
          mq[ipt][0]++;
          pPt[0][2] -> Fill(pt, cent, pt, 1.);
          pPt[0][3] -> Fill(pt, cent, pt, 1.);
        }
        if (charge<0){
          px2[ipt][4]+=cos2phi;
          py2[ipt][4]+=sin2phi;
          mp[ipt][4]++;

          qx2[ipt][4]+=cos2phi;
          qy2[ipt][4]+=sin2phi;
          qx4[ipt][4]+=cos4phi;
          qy4[ipt][4]+=sin4phi;
          mq[ipt][4]++;
          pPt[4][2] -> Fill(pt, cent, pt, 1.);
          pPt[4][3] -> Fill(pt, cent, pt, 1.);
        }
        if (pidID>0){
          px2[ipt][pidID]+=cos2phi;
          py2[ipt][pidID]+=sin2phi;
          mp[ipt][pidID]++;

          qx2[ipt][pidID]+=cos2phi;
          qy2[ipt][pidID]+=sin2phi;
          qx4[ipt][pidID]+=cos4phi;
          qy4[ipt][pidID]+=sin4phi;
          mq[ipt][pidID]++;
          pPt[pidID][2] -> Fill(pt, cent, pt, 1.);
          pPt[pidID][3] -> Fill(pt, cent, pt, 1.);
        }
      }
    } // end of 1st track loop

    // 2QC,eta-gap (FHCal)
    if (MGap_FHCal[0]!=0 && MGap_FHCal[1]!=0){
      for (int ieta=0;ieta<nEta;ieta++){
        Q2Gap_FHCal[ieta] = TComplex(Qx2Gap_FHCal[ieta], Qy2Gap_FHCal[ieta]);
      }
      w2Gap_FHCal = MGap_FHCal[0]*MGap_FHCal[1];
      cor22Gap_FHCal = CalRedCor22(Q2Gap_FHCal[0],Q2Gap_FHCal[1],MGap_FHCal[0],MGap_FHCal[1], 0.,w2Gap_FHCal);       // <2>
      // hv22Gap[fcent]->Fill(0.5, cor22Gap_FHCal, w2Gap_FHCal);
      pCorrelator2EtaGap_FHCal -> Fill(cent, cor22Gap_FHCal, w2Gap_FHCal);
    
      for (int ieta=0;ieta<nEta;ieta++){
        for (int ipt = 0; ipt < nPtBins; ipt++){ // <2'>
          for (int id=0;id<nPID;id++){
            if (mpGap_FHCal[ieta][ipt][id]==0) continue;
            // Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
            p2Gap_FHCal[ieta][ipt][id] = TComplex(px2Gap_FHCal[ieta][ipt][id], py2Gap_FHCal[ieta][ipt][id]);
            wred2Gap_FHCal[ieta][ipt][id] = mpGap_FHCal[ieta][ipt][id]*MGap_FHCal[ieta];
            redCor22Gap_FHCal[ieta][ipt][id] = CalRedCor22(Q2Gap_FHCal[ieta], p2Gap_FHCal[ieta][ipt][id], MGap_FHCal[ieta], mpGap_FHCal[ieta][ipt][id], 0., wred2Gap_FHCal[ieta][ipt][id]);   // <2'>
            // hv22ptGap[fcent][ipt][id]->Fill(0.5, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);                                                                      // <<2'>>
            // hcounter[fcent][ipt][id]->Fill(1.5,1,mpGap[ieta][ipt][id]);
            pReducedCorrelator2EtaGap_FHCal[id] -> Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, redCor22Gap_FHCal[ieta][ipt][id], wred2Gap_FHCal[ieta][ipt][id]);
            // TProfile for covariance calculation in statistic error
            // hcov22primeGap[fcent][ipt][id]->Fill(0.5, cor22Gap*redCor22Gap[ieta][ipt][id], w2Gap*wred2Gap[ieta][ipt][id]); // <2>*<2'>
            pCov22RedEtaGap_FHCal[id] -> Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, cor22Gap_FHCal*redCor22Gap_FHCal[ieta][ipt][id], w2Gap_FHCal*wred2Gap_FHCal[ieta][ipt][id]);
          }
        }
      }
    }

    // 2QC,eta-gap (TPC)
    if (MGap[0]!=0 && MGap[1]!=0){
      for (int ieta=0;ieta<nEta;ieta++){
        Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
      }
      w2Gap = MGap[0]*MGap[1];
      cor22Gap = CalRedCor22(Q2Gap[0],Q2Gap[1],MGap[0],MGap[1], 0.,w2Gap);       // <2>
      // hv22Gap[fcent]->Fill(0.5, cor22Gap, w2Gap);
      pCorrelator2EtaGap -> Fill(cent, cor22Gap, w2Gap);
    
      for (int ieta=0;ieta<nEta;ieta++){
        for (int ipt = 0; ipt < nPtBins; ipt++){ // <2'>
          for (int id=0;id<nPID;id++){
            if (mpGap[ieta][ipt][id]==0) continue;
            // Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
            p2Gap[ieta][ipt][id] = TComplex(px2Gap[ieta][ipt][id], py2Gap[ieta][ipt][id]);
            wred2Gap[ieta][ipt][id] = mpGap[ieta][ipt][id]*MGap[ieta];
            redCor22Gap[ieta][ipt][id] = CalRedCor22(Q2Gap[ieta], p2Gap[ieta][ipt][id], MGap[ieta], mpGap[ieta][ipt][id], 0., wred2Gap[ieta][ipt][id]);   // <2'>
            // hv22ptGap[fcent][ipt][id]->Fill(0.5, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);                                                                      // <<2'>>
            // hcounter[fcent][ipt][id]->Fill(1.5,1,mpGap[ieta][ipt][id]);
            pReducedCorrelator2EtaGap[id] -> Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);
            // TProfile for covariance calculation in statistic error
            // hcov22primeGap[fcent][ipt][id]->Fill(0.5, cor22Gap*redCor22Gap[ieta][ipt][id], w2Gap*wred2Gap[ieta][ipt][id]); // <2>*<2'>
            pCov22RedEtaGap[id] -> Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, cor22Gap*redCor22Gap[ieta][ipt][id], w2Gap*wred2Gap[ieta][ipt][id]);
          }
        }
      }
    }
    int icent = GetCentBin(cent);
    // 2QC, 4QC
    Q2 = TComplex(Qx2, Qy2);
    w2 = M*(M-1);                         // w(<2>)
    Q4 = TComplex(Qx4, Qy4);
    w4 = M*(M-1)*(M-2)*(M-3);             // w(<4>)
    if (w2 != 0 && w4 != 0){
      cor22 = CalCor22(Q2, M, w2);        // <2>
      cor24 = CalCor24(Q2, Q4, M, w4);    // <4>
      pCorrelator2->Fill(cent, cor22, w2);  // <<2>>
      pCorrelator4->Fill(cent, cor24, w4);  // <<4>>

      // TProfile for covariance calculation in statistic error
      pCov24->Fill(cent, cor22 * cor24, w2 * w4); // <2>*<4>
      for (int ipt = 0; ipt < nPtBins; ipt++){
        for (int id=0;id<nPID;id++){
          if (mp[ipt][id] == 0) continue;
          p2[ipt][id] = TComplex(px2[ipt][id], py2[ipt][id]);
          q2[ipt][id] = TComplex(qx2[ipt][id], qy2[ipt][id]);
          wred2[ipt][id] = mp[ipt][id]*M-mq[ipt][id];                                                                                   // w(<2'>)
          if (wred2[ipt][id]==0) continue;
          q4[ipt][id] = TComplex(qx4[ipt][id], qy4[ipt][id]);
          wred4[ipt][id] = (mp[ipt][id]*M-3*mq[ipt][id])*(M-1)*(M-2);                                                                   // w(<4'>)
          if (wred4[ipt][id]==0) continue;
          redCor22[ipt][id] = CalRedCor22(Q2, p2[ipt][id], M, mp[ipt][id], mq[ipt][id], wred2[ipt][id]);                                // <2'>
          pReducedCorrelator2[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, redCor22[ipt][id], wred2[ipt][id]);
          pReducedCorrelator2_test[id][icent]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, redCor22[ipt][id], 1.);
          redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]);  // <4'>
          // hv24pt[fcent][ipt][id]->Fill(0.5, redCor24[ipt][id], wred4[ipt][id]);
          pReducedCorrelator4[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, redCor24[ipt][id], wred4[ipt][id]);                                                      // <<4'>>

          // TProfile for covariance calculation in statistic error
          // hcov22prime[fcent][ipt][id]->Fill(0.5, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]);     // <2>*<2'>
          // hcov24prime[fcent][ipt][id]->Fill(0.5, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
          // hcov42prime[fcent][ipt][id]->Fill(0.5, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
          // hcov44prime[fcent][ipt][id]->Fill(0.5, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
          // hcov2prime4prime[fcent][ipt][id]->Fill(0.5, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
          // hcounter[fcent][ipt][id]->Fill(0.5,1,mp[ipt][id]);

          pCov22Red[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]);     // <2>*<2'>
          pCov24Red[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
          pCov42Red[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
          pCov44Red[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
          pCov2Red4Red[id]->Fill((ipt+0.5)*(ptBinMax-ptBinMin)/nPtBins, cent, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
        }
      }
    }

    

    if (Mult_L > mult_EP_cut && Mult_R > mult_EP_cut)
    {
      Qx_L_EP /= W_L_EP;
      Qy_L_EP /= W_L_EP;
      Qx_R_EP /= W_R_EP;
      Qy_R_EP /= W_R_EP;

      hQx_L->Fill(cent, Qx_L_EP);
      hQy_L->Fill(cent, Qy_L_EP);
      hQx_R->Fill(cent, Qx_R_EP);
      hQy_R->Fill(cent, Qy_R_EP);

      PsiEP_L = 0.5 * atan2(Qy_L_EP, Qx_L_EP);
      PsiEP_R = 0.5 * atan2(Qy_R_EP, Qx_R_EP);

      Qv2_L = TComplex(Qx_L_SP,Qy_L_SP);
      Qv2_R = TComplex(Qx_R_SP,Qy_R_SP);
      float res2_SP   = (float) (Qv2_L*Qstar(Qv2_R)).Re();
      float res2_EP   = cos(2. * (PsiEP_R - PsiEP_L) );
      pResTPC_SP->Fill(cent, res2_SP);
      pResTPC_EP->Fill(cent, res2_EP);
    }
    else
    { 
      PsiEP_L = -999.;
      PsiEP_R = -999.;
    }
    if (Mult_L_FHCal > mult_EP_cut && Mult_L_FHCal > mult_EP_cut)
    {
      // Qx_L_FHCal /= W_L_FHCal;
      // Qy_L_FHCal /= W_L_FHCal;
      // Qx_R_FHCal /= W_R_FHCal;
      // Qy_R_FHCal /= W_R_FHCal;

      Psi_L_FHCal = atan2(Qy_L_FHCal, Qx_L_FHCal);
      Psi_R_FHCal = atan2(Qy_R_FHCal, Qx_R_FHCal);

      Psi_L_FHCal = atan2(sin(1.*Psi_L_FHCal), cos(1.*Psi_L_FHCal));
      Psi_R_FHCal = atan2(sin(1.*Psi_R_FHCal), cos(1.*Psi_R_FHCal));

      Psi_FHCal   = atan2(Qy_L_FHCal + Qy_R_FHCal, Qx_L_FHCal + Qx_R_FHCal);

      float res1_FHCal   = cos(1. * (Psi_R_FHCal - Psi_L_FHCal) );
      pResFHCal_EP->Fill(cent, res1_FHCal);
    }
    else
    {
      Psi_FHCal = -999.;
    }
    

    ////////////////////////////////////////////////////////////////////
    //
    // FLOW CALCULATIONS FOR SP,EP
    //
    ////////////////////////////////////////////////////////////////////
    
    // float res_v2TPC = vResTpc.at(GetCentBin(cent));

    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      
      TVector3 vect(momx[iTr], momy[iTr], momz[iTr]);

      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();

      // // Main track cuts
      // if (pt < pt_min_cut) continue;
      // if (pt > pt_max_cut) continue;
      // if (abs(eta) > eta_cut) continue;
      // if (abs(eta) < eta_gap) continue;

      // PID-related cut
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTr]);
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (charge == 0) continue;
      int pidID = -1;
      for (int ipid=0; ipid < nPID; ipid++)
      {
        if (abs(pdgCodes.at(ipid)) == 999) continue;
        if (pdgCodes.at(ipid) == pdg[iTr]) pidID = ipid;
      }

      if (pt >= ptBinMin && pt <= ptBinMax && abs(eta) <= eta_cut && abs(eta) >= eta_gap && PsiEP_L != -999 && PsiEP_R != -999)
      { // Main track cuts for TPC, EP/SP   
        TComplex u2 = TComplex(cos(2.*phi),sin(2.*phi));

        float v2TPC_SP = 0.;
        float v2TPC_EP = 0.;
        if (eta < 0)
        {
          v2TPC_SP = (float) (u2*Qstar(Qv2_R)).Re();
          v2TPC_EP = cos( 2. * (phi - PsiEP_R) );
        }
        if (eta > 0)
        {
          v2TPC_SP = (float) (u2*Qstar(Qv2_L)).Re();
          v2TPC_EP = cos( 2. * (phi - PsiEP_L) );
        }
        // v2TPC_SP /= res_v2TPC;

        if (charge > 0)
        {
          pv2TPC_EP[0]->Fill(pt, cent, v2TPC_EP);
          pv2TPC_SP[0]->Fill(pt, cent, v2TPC_SP);
          pPt[0][4] -> Fill(pt, cent, pt, 1.);
          pPt[0][5] -> Fill(pt, cent, pt, 1.);
        }
        if (charge < 0)
        {
          pv2TPC_EP[4]->Fill(pt, cent, v2TPC_EP);
          pv2TPC_SP[4]->Fill(pt, cent, v2TPC_SP);
          pPt[4][4] -> Fill(pt, cent, pt, 1.);
          pPt[4][5] -> Fill(pt, cent, pt, 1.);
        }
        if (pidID != -1)
        {
          pv2TPC_EP[pidID]->Fill(pt, cent, v2TPC_EP);
          pv2TPC_SP[pidID]->Fill(pt, cent, v2TPC_SP);
          pPt[pidID][4] -> Fill(pt, cent, pt, 1.);
          pPt[pidID][5] -> Fill(pt, cent, pt, 1.);
        }
      }

      if (pt >= ptBinMin && pt <= ptBinMax && abs(eta) <= eta_cut && Psi_FHCal != -999.)
      { // Main track cuts for FHCal, EP

        float v2FHCal_EP = cos( 2. * (phi - Psi_FHCal) );
        if (charge > 0)
        {
          pv2FHCal_EP[0]->Fill(pt, cent, v2FHCal_EP);
          pPt[0][6] -> Fill(pt, cent, pt, 1.);
        }
        if (charge < 0)
        {
          pv2FHCal_EP[4]->Fill(pt, cent, v2FHCal_EP);
          pPt[4][6] -> Fill(pt, cent, pt, 1.);
        }
        if (pidID != -1)
        {
          pv2FHCal_EP[pidID]->Fill(pt, cent, v2FHCal_EP);
          pPt[pidID][6] -> Fill(pt, cent, pt, 1.);
        }
      }
    } // end tracks loop
  } // end event loop
  
  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}

// Event selection




// root -l -b -q get_flow_model.C+'("/weekly/lbavinh/lbavinh/ScalarProduct/split/UrQMD_7.7/runlist_UrQMD_7.7_9639.list","UrQMD_7.7GeV.root")'