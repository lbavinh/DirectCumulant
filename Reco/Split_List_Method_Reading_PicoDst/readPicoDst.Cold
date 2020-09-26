// Do not forget to source setPicoDst.sh script

#include <iostream>
#include <fstream>

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

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>


#include "function.C"
// R__LOAD_LIBRARY(libPicoDst.so)


void readPicoDst(TString inputFileName, TString outputFileName)
{
  TFile *inputDCAfile; // "/nica/mpd21/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_new_test_picodst/dca/dca_fit.root"
  TF2 *fDCAx, *fDCAy, *fDCAz;

  TStopwatch timer;
  timer.Start();

  inputDCAfile = new TFile("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_picodst/dca/dca_fit.root","read");
  
  fDCAx = (TF2 *)inputDCAfile->Get("f_sigma0");
  fDCAy = (TF2 *)inputDCAfile->Get("f_sigma1");
  fDCAz = (TF2 *)inputDCAfile->Get("f_sigma2");


  static const int ncent = 8; // 0-80%
  static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

  static const int npt = 8; // 0.5 - 3.6 GeV/c - number of pT bins
  static const double bin_pT[npt+1]={0.1, 0.3, 0.6, 0.9, 1.2, 1.5, 1.9, 2.4, 3.};

  static const double maxpt = 3.0; // max pt
  static const double minpt = 0.1; // min pt

  static const float mineta = -1.8; // min pt
  static const float maxeta =  1.8; // min pt
  static const float etagap = 0.05; // min pt
  static const int nhitsmin = 16; // minimum nhits of reconstructed tracks


  static const int neta = 2; // [eta-,eta+]

  static const int max_nh = 1500;

  
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
  // TProfile *hv2MC[ncent]; // profile for MC integrated v2
  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow (DF)
  TProfile *hPT[ncent][npt];     // profile pt
  // TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
  TProfile *hv22pt[ncent][npt];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];  // profile <<4'>> from 4th Q-Cumulants

  // TProfile for covariance calculation according to (C.12), Appendix C
  // in Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider.
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

  TProfile *hv2EP[ncent][npt];	// elliptic flow from EP method
  TProfile *hv22EP[ncent];      // integrated elliptic flow from EP method

  TH1F *H_Qw[neta];     // sub-event multiplicity
  TH1F *H_EP[neta];		  // reaction plane
  TH1F *H_Qv[neta];     // sub-event <Q> - probably
  TProfile *HRes[ncent];		// resolution

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

  for( int ieta=0; ieta<neta; ieta++ ){
    (void)sprintf(name,"H_Qw_%d",ieta);
    H_Qw[ieta] = new TH1F(name,name, 100, 0, 1000 );    
    (void)sprintf(name,"H_EP_%d",ieta);
    H_EP[ieta] = new TH1F(name,name, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    (void)sprintf(name,"H_Qv_%d",ieta);
    H_Qv[ieta] = new TH1F(name,name, 100, 0, 10 );
  }

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    // sprintf(name, "hv2MC_%i", icent);
    // sprintf(title, "v_{2}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    // hv2MC[icent] = new TProfile(name, title, 1, 0., 1.);
    // hv2MC[icent]->Sumw2();

    sprintf(name, "hv22EP_%i", icent);
    hv22EP[icent] = new TProfile(name,name, 1,0.,1.);
    hv22EP[icent]->Sumw2();
    sprintf(name, "HRes_%i", icent);
    HRes[icent] = new TProfile(name,name, 1,0.,1.);
    HRes[icent]->Sumw2();

    sprintf(name, "hv22_%i", icent);
    sprintf(title, "v_{2}{2}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv22[icent] = new TProfile(name, title, 1, 0., 1.);
    hv22[icent]->Sumw2();

    sprintf(name, "hv24_%i", icent);
    sprintf(title, "v_{2}{4}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv24[icent] = new TProfile(name, title, 1, 0., 1.);
    hv24[icent]->Sumw2();

    sprintf(name, "hcov24_%i", icent);
    sprintf(title, "<2>#upoint<4> distr, cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hcov24[icent] = new TProfile(name, title, 1, 0., 1.);
    hcov24[icent]->Sumw2();

    for (int kpt = 0; kpt < npt; kpt++)
    { // loop over pt bin
    
      // sprintf(name, "hv2MCpt_%i_%i", icent, kpt);
      // sprintf(title, "v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      // hv2MCpt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      // hv2MCpt[icent][kpt]->Sumw2();

      sprintf(name,"hv2EP_%i_%i", icent, kpt);
      hv2EP[icent][kpt] = new TProfile(name,name, ncent,0.,ncent);
      hv2EP[icent][kpt]->Sumw2();
      sprintf(name, "hPT_%i_%i", icent, kpt);
      hPT[icent][kpt] = new TProfile(name, name, ncent,0.,ncent);
      hPT[icent][kpt]->Sumw2();

      sprintf(name, "hv22pt_%i_%i", icent, kpt);
      sprintf(title, "v_{2}{2,QC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv22pt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv22pt[icent][kpt]->Sumw2();

      sprintf(name, "hv24pt_%i_%i", icent, kpt);
      sprintf(title, "v_{2}{4,QC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv24pt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv24pt[icent][kpt]->Sumw2();

      sprintf(name, "hcov22prime_%i_%i", icent, kpt);
      sprintf(title, "<2>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov22prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov22prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov24prime_%i_%i", icent, kpt);
      sprintf(title, "<2>#upoint<4'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov24prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov24prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov42prime_%i_%i", icent, kpt);
      sprintf(title, "<4>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov42prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov42prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov44prime_%i_%i", icent, kpt);
      sprintf(title, "<4>#upoint<4'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov44prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov44prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov2prime4prime_%i_%i", icent, kpt);
      sprintf(title, "<4'>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov2prime4prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov2prime4prime[icent][kpt]->Sumw2();
    } // end of loop over pt bin
  } // end of loop over centrality classes

  cout << "Histograms have been initialized" << endl;



  // Configure input information
  TChain *chain = new TChain("picodst");

  std::ifstream file(inputFileName.Data());
  std::string line;
  while(std::getline(file, line))
  {
      chain->Add(line.c_str());
  }

  PicoDstMCEvent *mcEvent = nullptr;
  TClonesArray *recoTracks = nullptr;

  chain->SetBranchAddress("mcevent.", &mcEvent);
  chain->SetBranchAddress("recotracks",&recoTracks);

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%1000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    hEvt -> Fill(1);
    // Read MC event
    float bimp = mcEvent->GetB();
    int fcent = -1;
    for (int i = 0; i < ncent; i++) if (CentB(bimp) == bin_cent[i]) fcent = i;
    if (fcent < 0) continue;
    hBimp -> Fill(bimp);
    Int_t reco_mult = recoTracks->GetEntriesFast();

    
    // rp = gRandom->Uniform(0, 2.*TMath::Pi());

    hMult -> Fill(reco_mult);

    hBimpvsMult -> Fill(reco_mult,bimp);
    // notation as (26) in DOI:10.1103/PhysRevC.83.044913
    // Q-vector of RFP
    Double_t Qx2[neta]={0.}, Qy2[neta]={0.}, Qx4[neta]={0.}, Qy4[neta]={0.};
    TComplex Q2[neta]={0.}, Q4[neta]={0.};
    // p-vector of POI
    Double_t px2[neta][npt]={{0.}}, py2[neta][npt]={{0.}};
    TComplex p2[neta][npt]={{0.}}, p4[neta][npt]={{0.}}, q2[neta][npt]={{0.}}, q4[neta][npt]={{0.}};
    // q-vector of particles marked as POI and RFP, which is used for 
    // autocorrelation substraction
    Double_t qx2[neta][npt]={{0.}}, qy2[neta][npt]={{0.}}, qx4[neta][npt]={{0.}}, qy4[neta][npt]={{0.}};
    // Total number of RFP in given event
    Double_t M[neta] = {0.};
    // numbers of POI (mp) and particles marked both POI and RFP (mq)
    Double_t mq[neta][npt]={{0.}},mp[neta][npt]={{0.}};
    // average reduced single-event 2- and 4-particle correlations : <2'> & <4'>
    Double_t redCor22[neta][npt]={{0.}}, redCor24[neta][npt]={{0.}};
    // event weights for correlation calculation
    Double_t w2[neta]={0.},w4[neta]={0.};
    // event weights for reduced correlation calculation
    Double_t wred2[neta][npt]={{0.}},wred4[neta][npt]={{0.}};
    // Average single-event 2- and 4- particle correlations : <2> & <4>
    Double_t cor22[neta] = {0.}, cor24[neta] = {0.};

    Double_t sumQxy[neta][2]={{0}};  // [eta-,eta+][x,y]
    Double_t multQv[neta]={0};       // [eta+,eta-]

    // Read Reco tracks
    // for (int iTr=0; iTr<reco_mult; iTr++)
    // {
    //   auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
    //   //recoTrack->GetPt()
    //   //recoTrack->GetEta()
    //   //recoTrack->GetPhi()
    //   //recoTrack->GetDCAx()
    //   //recoTrack->GetDCAy()
    //   //recoTrack->GetDCAz()
    //   //recoTrack->GetNhits()
    // }

    for (int iTr=0; iTr<reco_mult; iTr++) { // track loop
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      if (recoTrack->GetNhits()<=nhitsmin ) continue;
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      // if (abs(recoTrack->GetDCAx()) > 0.2) continue; //трек не проходит по DCAx
      // if (abs(recoTrack->GetDCAy()) > 0.2) continue; //трек не проходит по DCAy
      // if (abs(recoTrack->GetDCAz()) > 0.2) continue; //трек не проходит по DCAz
      if (pt < minpt || pt > maxpt || eta>maxeta || eta<mineta || TMath::Abs(eta)<etagap) continue; // track selection
      float phi = recoTrack->GetPhi();
      if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

      hPhi -> Fill(phi);
      // float phil = phi+rp;
      // while (phil>2.*TMath::Pi()) phil-=2.*TMath::Pi(); /* To make sure that phil is between 0 and 2 Pi */
      // hPhil -> Fill(phil);
      hEta -> Fill(eta);
      Int_t ipt = 0;
      hPt -> Fill(pt);
      for(int j=0; j<npt;j++){
        if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
      }

      hPT[fcent][ipt]->Fill(0.5, pt, 1);
      // Double_t v2 = TMath::Cos(2.*phi);
      // hv2MC[fcent]->Fill(0.5, v2, 1);
      // hv2MCpt[fcent][ipt]->Fill(0.5, v2, 1);
      if(eta<-etagap){
        // RFP selection
        Qx2[0]+=TMath::Cos(2.*phi);
        Qy2[0]+=TMath::Sin(2.*phi);
        Qx4[0]+=TMath::Cos(4.*phi);
        Qy4[0]+=TMath::Sin(4.*phi);
        M[0]++;
        // POI selection
        px2[1][ipt]+=TMath::Cos(2.*phi);
        py2[1][ipt]+=TMath::Sin(2.*phi);
        mp[1][ipt]++;

      } // end of RFP selection

      if(eta>etagap){ 
        Qx2[1]+=TMath::Cos(2.*phi);
        Qy2[1]+=TMath::Sin(2.*phi);
        Qx4[1]+=TMath::Cos(4.*phi);
        Qy4[1]+=TMath::Sin(4.*phi);
        M[1]++;

        px2[0][ipt]+=TMath::Cos(2.*phi);
        py2[0][ipt]+=TMath::Sin(2.*phi);
        mp[0][ipt]++;
      } // end of POI selection

      // Sub eta event method, TPC plane
      int fEta = -1;
      if (eta > mineta && eta <-etagap) fEta = 0; // TPC East
      if (eta > etagap && eta < maxeta) fEta = 1; // TPC West

      if ( fEta>-1 ){
        sumQxy[fEta][0] += 1. * cos( (2.0) * phi );
        sumQxy[fEta][1] += 1. * sin( (2.0) * phi );
        multQv[fEta]++;
      } // end of eta selection
    } // end of track loop

    // ================================== Direct Cumulants ================================== //
    for (int ieta=0;ieta<neta;ieta++){ // reverse POI & RFP selection
      if (M[ieta] >= 2.){ // <2> definition condition
        Q2[ieta] = TComplex(Qx2[ieta], Qy2[ieta]);
        w2[ieta] = M[ieta]*(M[ieta]-1);                            // w(<2>)
        cor22[ieta] = CalCor22(Q2[ieta], M[ieta], w2[ieta]);       // <2>
        hv22[fcent]->Fill(0.5, cor22[ieta], w2[ieta]);             // <<2>>

      } // end of <2> definition condition
      for (int ipt = 0; ipt < npt; ipt++){
        if (mp[ieta][ipt] == 0 || M[ieta]<1) continue;
        Q2[ieta] = TComplex(Qx2[ieta], Qy2[ieta]);
        p2[ieta][ipt] = TComplex(px2[ieta][ipt], py2[ieta][ipt]);
        q2[ieta][ipt] = TComplex(qx2[ieta][ipt], qy2[ieta][ipt]);
        wred2[ieta][ipt] = mp[ieta][ipt]*M[ieta]-mq[ieta][ipt];                                        // w(<2'>)
        if (wred2[ieta][ipt]==0) continue;
        redCor22[ieta][ipt] = CalRedCor22(Q2[ieta], p2[ieta][ipt], M[ieta], mp[ieta][ipt], mq[ieta][ipt], wred2[ieta][ipt]); // <2'>
        hv22pt[fcent][ipt]->Fill(0.5, redCor22[ieta][ipt], wred2[ieta][ipt]);                  // <<2'>>

        // TProfile for covariance calculation in statistic error
        hcov22prime[fcent][ipt]->Fill(0.5, cor22[ieta] * redCor22[ieta][ipt], w2[ieta] * wred2[ieta][ipt]); // <2>*<2'>
      }

      if (M[ieta] >= 4.){ // <4> definition condition
        Q4[ieta] = TComplex(Qx4[ieta], Qy4[ieta]);
        w4[ieta] = M[ieta]*(M[ieta]-1)*(M[ieta]-2)*(M[ieta]-3); // w(<4>)
        cor24[ieta] = CalCor24(Q2[ieta], Q4[ieta], M[ieta], w4[ieta]);      // <4>
        hv24[fcent]->Fill(0.5, cor24[ieta], w4[ieta]);    // <<4>>

        // TProfile for covariance calculation in statistic error
        hcov24[fcent]->Fill(0.5, cor22[ieta] * cor24[ieta], w2[ieta] * w4[ieta]); // <2>*<4>
      } // end of <4> definition condition
      for (int ipt = 0; ipt < npt; ipt++){
        if (mp[ieta][ipt] == 0 || M[ieta]<3) continue;
        Q4[ieta] = TComplex(Qx4[ieta], Qy4[ieta]);   
        q4[ieta][ipt] = TComplex(qx4[ieta][ipt], qy4[ieta][ipt]);
        wred4[ieta][ipt] = (mp[ieta][ipt]*M[ieta]-3*mq[ieta][ipt])*(M[ieta]-1)*(M[ieta]-2);                                 // w(<4'>)
        if (wred4[ieta][ipt]==0) continue;
        redCor24[ieta][ipt] = CalRedCor24(Q2[ieta], Q4[ieta], p2[ieta][ipt], q2[ieta][ipt], q4[ieta][ipt], M[ieta], mp[ieta][ipt], mq[ieta][ipt], wred4[ieta][ipt]); // <4'>
        hv24pt[fcent][ipt]->Fill(0.5, redCor24[ieta][ipt], wred4[ieta][ipt]);                                        // <<4'>>

        // TProfile for covariance calculation in statistic error
        hcov24prime[fcent][ipt]->Fill(0.5, cor22[ieta] * redCor24[ieta][ipt], w2[ieta] * wred4[ieta][ipt]);
        hcov42prime[fcent][ipt]->Fill(0.5, cor24[ieta] * redCor22[ieta][ipt], w4[ieta] * wred2[ieta][ipt]);
        hcov44prime[fcent][ipt]->Fill(0.5, cor24[ieta] * redCor24[ieta][ipt], w4[ieta] * wred4[ieta][ipt]);
        hcov2prime4prime[fcent][ipt]->Fill(0.5, redCor22[ieta][ipt] * redCor24[ieta][ipt], wred2[ieta][ipt] * wred4[ieta][ipt]);
      }
    } // end of reverse selection


    // ==================================== Eta Sub-event ==================================== //

    Double_t fEP[2]; // [eta-,eta+]
    Double_t fQv[2];
    for (int ieta=0; ieta<neta; ieta++){
      if( multQv[ieta]>=4. ){ // multiplicity > 3
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
        fEP[ieta] = TMath::ATan2( sin( 2.0*fEP[ieta] ), cos( 2.0*fEP[ieta] ) ); // what for?
        fEP[ieta] /= 2.0;
        fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0],2.0)+TMath::Power( sumQxy[ieta][1],2.0))/TMath::Sqrt(multQv[ieta]);
        H_Qw[ieta]->Fill( multQv[ieta] );
        H_EP[ieta]->Fill( fEP[ieta] );
        H_Qv[ieta]->Fill( fQv[ieta] );
      }else{
        fEP[ieta] = -9999;
        fQv[ieta] = -9999;
      }
    }

    // Resolution
    Double_t psi1, psi2, fq1, fq2;
    psi1 = fEP[0];
    psi2 = fEP[1];
    fq1 = fQv[0];
    fq2 = fQv[1];
    if (psi1<-9000 || psi2<-9000) continue;
    if (fq1<0 || fq2<0) continue;
    Double_t dPsi = 2. *(psi1 - psi2);
    dPsi = TMath::ATan2( sin(dPsi) , cos(dPsi));
    HRes[fcent] -> Fill(0.5,cos(dPsi));

    for (int iTr=0; iTr<reco_mult; iTr++) { // track loop
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      if (recoTrack->GetNhits()<=nhitsmin ) continue;
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      // if (recoTrack->GetDCAx() > 2.*fDCAx->Eval(pt, eta)) continue; //трек не проходит по DCAx
      // if (recoTrack->GetDCAy() > 2.*fDCAy->Eval(pt, eta)) continue; //трек не проходит по DCAy
      // if (recoTrack->GetDCAz() > 2.*fDCAz->Eval(pt, eta)) continue; //трек не проходит по DCAz
      // if (abs(recoTrack->GetDCAx()) > 0.2) continue; //трек не проходит по DCAx
      // if (abs(recoTrack->GetDCAy()) > 0.2) continue; //трек не проходит по DCAy
      // if (abs(recoTrack->GetDCAz()) > 0.2) continue; //трек не проходит по DCAz
      if (pt < minpt || pt > maxpt || eta>maxeta || eta<mineta || TMath::Abs(eta)<etagap) continue; // track selection
      float phi = recoTrack->GetPhi();
      if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

      Int_t ipt = 0;
      for(int j=0; j<npt;j++){
        if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
      }
      // ==================================== Eta Sub-event ==================================== //
      float v2=-999.0;
      if(eta>etagap){ // eta+
        // v2 = cos(2.0 * (phi-psi1) )/res2[fcent];
        v2 = cos(2.0 * (phi-psi1) );
      }
      if(eta<-etagap){ // eta-
        // v2 = cos(2.0 * (phi-psi2) )/res2[fcent];
        v2 = cos(2.0 * (phi-psi2) );
      }
      hv2EP[fcent][ipt]->Fill(0.5,v2);
      // if (eta < -0.1) { // Reference flow
      hv22EP[fcent]->Fill(0.5,v2);
      // }
    } // end of track loop

  } // end event loop
  // Write histograms to out file
  TFile *d_outfile; // out file with histograms and profiles
  d_outfile = new TFile(outputFileName.Data(),"recreate");
  d_outfile -> cd();
  
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
    hv22EP[icent]->Write();
    hv22[icent]->Write();
    hv24[icent]->Write();
    hcov24[icent]->Write();
    for (int ipt=0;ipt<npt;ipt++){
      hv22pt[icent][ipt]->Write();
      hv24pt[icent][ipt]->Write();
      hcov22prime[icent][ipt]->Write();
      hcov24prime[icent][ipt]->Write();
      hcov42prime[icent][ipt]->Write();
      hcov44prime[icent][ipt]->Write();
      hcov2prime4prime[icent][ipt]->Write();
      hPT[icent][ipt]->Write();
      hv2EP[icent][ipt]->Write();  
    }
  }
  for (int ieta=0;ieta<neta;ieta++){
    H_Qw[ieta]->Write();
    H_EP[ieta]->Write();
    H_Qv[ieta]->Write();
  }
  
  // d_outfile -> Write();
  d_outfile -> Close();
  cout << "Histfile has been written" << endl;

  timer.Stop();
  timer.Print();
}
// compilation test
// source /weekly/parfenov/Soft/PicoDst/build/setPicoDst.sh 
// root -l -b -q readPicoDst.C+'("/weekly/povarov/lbavinh/Split_List_PicoDst/split/runlist_PicoDst_9305","test.root")'