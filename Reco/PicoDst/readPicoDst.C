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

  static const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-

  static const int ncent = 8; // 0-80%
  static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

  static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
  static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};

  static const double maxpt = 3.; // max pt
  static const double minpt = 0.2; // min pt

  static const float eta_cut =  1.5; // min pt
  static const float eta_gap = 0.05; // min pt
  static const int Nhits_cut = 32; // minimum nhits of reconstructed tracks
  static const float DCAcut = 0.5;
  static const int neta = 2; // [eta-,eta+]

  static const int max_nh = 1700;


  TH1I *hEvt;        // Event number 
  TH1F *hRP;         // reaction plane distr
  TH1F *hPt;         // transverse momentum distr
  TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
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
  TProfile *hv22EP[ncent][npid];      // integrated flow from EP method

  TH1F *H_Qw[neta];     // sub-event multiplicity
  TH1F *H_EP[neta];		  // reaction plane
  TH1F *H_Qx[neta][ncent];     //
  TH1F *H_Qy[neta][ncent];
  TProfile *HRes[ncent];		// resolution
  TProfile *hcounter[ncent][npt][npid]; // for testing how different are particle entries of each method

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
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

  for( int ieta=0;ieta<neta;ieta++){
    H_Qw[ieta] = new TH1F(Form("H_Qw_%d",ieta),Form("H_Qw_%d",ieta), 300, 0, 300 );    
    H_EP[ieta] = new TH1F(Form("H_EP_%d",ieta),Form("H_EP_%d",ieta), 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    for (int icent=0;icent<ncent;icent++){
      H_Qx[ieta][icent] = new TH1F(Form("H_Qx_%i_%i",ieta,icent),Form("H_Qv_%i_%i",ieta,icent), 240, -1.2, 1.2);
      H_Qy[ieta][icent] = new TH1F(Form("H_Qy_%i_%i",ieta,icent),Form("H_Qv_%i_%i",ieta,icent), 240, -1.2, 1.2);
    }
  }
  for (int icent=0;icent<ncent;icent++){ // loop over centrality classes
    HRes[icent] = new TProfile(Form("HRes_%i",icent),Form("HRes_%i",icent),1,0.,1.);
    hv22[icent] = new TProfile(Form("hv22_%i",icent),Form("hv22_%i",icent),1,0.,1.);
    hv24[icent] = new TProfile(Form("hv24_%i",icent),Form("hv24_%i",icent),1,0.,1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i",icent),Form("hcov24_%i",icent),1,0.,1.);
    for (int id=0;id<npid;id++){
      hv22EP[icent][id] = new TProfile(Form("hv22EP_%i_%i",icent,id),Form("hv22EP_%i_%i",icent,id),1,0.,1.);
      for (int ipt = 0; ipt < npt; ipt++){ // loop over pt bin
        hv2EP[icent][ipt][id] = new TProfile(Form("hv2EP_%i_%i_%i",icent,ipt,id),Form("hv2EP_%i_%i_%i",icent,ipt,id),1,0.,1.);
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
    Double_t px2[neta][npt][npid]={{{0.}}}, py2[neta][npt][npid]={{{0.}}};
    TComplex p2[neta][npt][npid]={{{0.}}}, p4[neta][npt][npid]={{{0.}}}, q2[neta][npt][npid]={{{0.}}}, q4[neta][npt][npid]={{{0.}}};
    // q-vector of particles marked as POI and RFP, which is used for 
    // autocorrelation substraction
    Double_t qx2[neta][npt][npid]={{{0.}}}, qy2[neta][npt][npid]={{{0.}}}, qx4[neta][npt][npid]={{{0.}}}, qy4[neta][npt][npid]={{{0.}}};
    // Total number of RFP in given event
    Double_t M[neta] = {0.};
    // numbers of POI (mp) and particles marked both POI and RFP (mq)
    Double_t mq[neta][npt][npid]={{{0.}}},mp[neta][npt][npid]={{{0.}}};
    // average reduced single-event 2- and 4-particle correlations : <2'> & <4'>
    Double_t redCor22[neta][npt][npid]={{{0.}}}, redCor24[neta][npt][npid]={{{0.}}};
    // event weights for correlation calculation
    Double_t w2[neta]={0.},w4[neta]={0.};
    // event weights for reduced correlation calculation
    Double_t wred2[neta][npt][npid]={{{0.}}},wred4[neta][npt][npid]={{{0.}}};
    // Average single-event 2- and 4- particle correlations : <2> & <4>
    Double_t cor22[neta] = {0.}, cor24[neta] = {0.};

    float sumQxy[neta][2]={{0}};  // [eta-,eta+][x,y]
    float multQv[neta]={0};       // [eta+,eta-]
    float wQv[neta]={0};

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
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // track selection
      // if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

      hPt -> Fill(pt);
      hEta -> Fill(eta);
      hPhi -> Fill(phi);
      Int_t ipt = -1;
      for(int j=0; j<npt;j++){
        if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
      }
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      float charge = 1./3.*particle->Charge();
      int fId=-1;
      if(mcTrack->GetPdg()==211)  fId=1; // pion+
      if(mcTrack->GetPdg()==321)  fId=2; // kaon+
      if(mcTrack->GetPdg()==2212) fId=3; // proton
      if(mcTrack->GetPdg()==-211)  fId=5; // pion-
      if(mcTrack->GetPdg()==-321)  fId=6; // kaon-
      if(mcTrack->GetPdg()==-2212) fId=7; // anti-proton
      // if (recoTrack->GetTofFlag() != 0 && recoTrack->GetTofFlag() != 4){
      //   if(recoTrack->GetPidProbPion() > 0.9)  fId=1; // pion
      //   if(recoTrack->GetPidProbKaon() > 0.9)  fId=2; // kaon
      //   if(recoTrack->GetPidProbProton() > 0.9) fId=3; // proton
      // }
      if(eta<0){
        // RFP selection
        Qx2[0]+=TMath::Cos(2.*phi);
        Qy2[0]+=TMath::Sin(2.*phi);
        Qx4[0]+=TMath::Cos(4.*phi);
        Qy4[0]+=TMath::Sin(4.*phi);
        M[0]++;
        // POI selection
        if (charge>0){
          px2[1][ipt][0]+=TMath::Cos(2.*phi);
          py2[1][ipt][0]+=TMath::Sin(2.*phi);
          mp[1][ipt][0]++;
        }
        if (charge<0){
          px2[1][ipt][4]+=TMath::Cos(2.*phi);
          py2[1][ipt][4]+=TMath::Sin(2.*phi);
          mp[1][ipt][4]++;
        }
        if (fId>0){
          px2[1][ipt][fId]+=TMath::Cos(2.*phi);
          py2[1][ipt][fId]+=TMath::Sin(2.*phi);
          mp[1][ipt][fId]++;
        }
      }

      if(eta>0){ 
        Qx2[1]+=TMath::Cos(2.*phi);
        Qy2[1]+=TMath::Sin(2.*phi);
        Qx4[1]+=TMath::Cos(4.*phi);
        Qy4[1]+=TMath::Sin(4.*phi);
        M[1]++;

        // POI selection
        if (charge>0){
          px2[0][ipt][0]+=TMath::Cos(2.*phi);
          py2[0][ipt][0]+=TMath::Sin(2.*phi);
          mp[0][ipt][0]++;
        }
        if (charge<0){
          px2[0][ipt][4]+=TMath::Cos(2.*phi);
          py2[0][ipt][4]+=TMath::Sin(2.*phi);
          mp[0][ipt][4]++;
        }
        if (fId>0){
          px2[0][ipt][fId]+=TMath::Cos(2.*phi);
          py2[0][ipt][fId]+=TMath::Sin(2.*phi);
          mp[0][ipt][fId]++;
        }
      }

      // Sub eta event method, TPC plane
      int fEta = -1;
      if (eta < 0) fEta = 0; // TPC Left EP
      if (eta > 0) fEta = 1; // TPC Right EP

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pt * cos(2.*phi);
        sumQxy[fEta][1] += pt * sin(2.*phi);
        wQv[fEta]       += pt;
        multQv[fEta]++;
      } // end of eta selection
    } // end of track loop

    // ================================== Direct Cumulants ================================== //
    for (int ieta=0;ieta<neta;ieta++){ // reverse POI & RFP selection
      if (M[ieta] < 4) continue; // test
      if (M[ieta] >= 2.){ // <2> definition condition
        Q2[ieta] = TComplex(Qx2[ieta], Qy2[ieta]);
        w2[ieta] = M[ieta]*(M[ieta]-1);                            // w(<2>)
        cor22[ieta] = CalCor22(Q2[ieta], M[ieta], w2[ieta]);       // <2>
        hv22[fcent]->Fill(0.5, cor22[ieta], w2[ieta]);             // <<2>>

      } // end of <2> definition condition
      for (int ipt = 0; ipt < npt; ipt++){ // <2'>
        for (int id=0;id<npid;id++){
          if (mp[ieta][ipt] == 0 || M[ieta]<1) continue;
          Q2[ieta] = TComplex(Qx2[ieta], Qy2[ieta]);
          p2[ieta][ipt][id] = TComplex(px2[ieta][ipt][id], py2[ieta][ipt][id]);
          q2[ieta][ipt][id] = TComplex(qx2[ieta][ipt][id], qy2[ieta][ipt][id]);
          wred2[ieta][ipt][id] = mp[ieta][ipt][id]*M[ieta]-mq[ieta][ipt][id];                                                                        // w(<2'>)
          if (wred2[ieta][ipt][id]==0) continue;
          redCor22[ieta][ipt][id] = CalRedCor22(Q2[ieta], p2[ieta][ipt][id], M[ieta], mp[ieta][ipt][id], mq[ieta][ipt][id], wred2[ieta][ipt][id]);   // <2'>
          hv22pt[fcent][ipt][id]->Fill(0.5, redCor22[ieta][ipt][id], wred2[ieta][ipt][id]);                                                                      // <<2'>>
          hcounter[fcent][ipt][id]->Fill(0.5,1,mp[ieta][ipt][id]);
          // TProfile for covariance calculation in statistic error
          hcov22prime[fcent][ipt][id]->Fill(0.5, cor22[ieta]*redCor22[ieta][ipt][id], w2[ieta]*wred2[ieta][ipt][id]); // <2>*<2'>
        }
      }

      if (M[ieta] >= 4.){ // <4> definition condition
        Q4[ieta] = TComplex(Qx4[ieta], Qy4[ieta]);
        w4[ieta] = M[ieta]*(M[ieta]-1)*(M[ieta]-2)*(M[ieta]-3); // w(<4>)
        cor24[ieta] = CalCor24(Q2[ieta], Q4[ieta], M[ieta], w4[ieta]);      // <4>
        hv24[fcent]->Fill(0.5, cor24[ieta], w4[ieta]);    // <<4>>

        // TProfile for covariance calculation in statistic error
        hcov24[fcent]->Fill(0.5,cor22[ieta]*cor24[ieta],w2[ieta]*w4[ieta]); // <2>*<4>
      } // end of <4> definition condition
      for (int ipt = 0; ipt < npt; ipt++){ // <4'>
        for (int id=0;id<npid;id++){
          if (mp[ieta][ipt] == 0 || M[ieta]<3) continue;
          Q4[ieta] = TComplex(Qx4[ieta], Qy4[ieta]);   
          q4[ieta][ipt][id] = TComplex(qx4[ieta][ipt][id], qy4[ieta][ipt][id]);
          wred4[ieta][ipt][id] = (mp[ieta][ipt][id]*M[ieta]-3*mq[ieta][ipt][id])*(M[ieta]-1)*(M[ieta]-2);                                 // w(<4'>)
          if (wred4[ieta][ipt][id]==0) continue;
          redCor24[ieta][ipt][id] = CalRedCor24(Q2[ieta], Q4[ieta], p2[ieta][ipt][id], q2[ieta][ipt][id], q4[ieta][ipt][id], M[ieta], mp[ieta][ipt][id], mq[ieta][ipt][id], wred4[ieta][ipt][id]); // <4'>
          hv24pt[fcent][ipt][id]->Fill(0.5, redCor24[ieta][ipt][id], wred4[ieta][ipt][id]);                                        // <<4'>>
          hcounter[fcent][ipt][id]->Fill(1.5,1,mp[ieta][ipt][id]);
          // TProfile for covariance calculation in statistic error
          hcov24prime[fcent][ipt][id]->Fill(0.5, cor22[ieta] * redCor24[ieta][ipt][id], w2[ieta] * wred4[ieta][ipt][id]);
          hcov42prime[fcent][ipt][id]->Fill(0.5, cor24[ieta] * redCor22[ieta][ipt][id], w4[ieta] * wred2[ieta][ipt][id]);
          hcov44prime[fcent][ipt][id]->Fill(0.5, cor24[ieta] * redCor24[ieta][ipt][id], w4[ieta] * wred4[ieta][ipt][id]);
          hcov2prime4prime[fcent][ipt][id]->Fill(0.5, redCor22[ieta][ipt][id] * redCor24[ieta][ipt][id], wred2[ieta][ipt][id] * wred4[ieta][ipt][id]);
        }
      }
    } // end of reverse selection


    // ==================================== Eta Sub-event ==================================== //

    float fEP[2]; // [eta-,eta+]
    for (int ieta=0; ieta<neta; ieta++){
      if( multQv[ieta]>2 ){ // multiplicity > 2
        for (int i=0;i<2;i++){
          sumQxy[ieta][i] /= wQv[ieta];
        }
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
        H_Qw[ieta]->Fill( multQv[ieta] );
        H_EP[ieta]->Fill( fEP[ieta] );
        H_Qx[ieta][fcent]->Fill( sumQxy[ieta][0] );
        H_Qy[ieta][fcent]->Fill( sumQxy[ieta][1] );
      }else{
        fEP[ieta] = -9999;
      }
    }

    // Resolution
    float psiEP_L, psiEP_R;
    psiEP_L = fEP[0];
    psiEP_R = fEP[1];
    if (psiEP_L<-9000 || psiEP_R<-9000) continue;
    float dPsi = 2. *(psiEP_L - psiEP_R);
    // dPsi = TMath::ATan2( sin(dPsi) , cos(dPsi));
    HRes[fcent] -> Fill(0.5,cos(dPsi));

    for (int iTr=0; iTr<reco_mult; iTr++) { // track loop
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      if (!recoTrack) continue;
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      if (!mcTrack) continue;
      if (mcTrack->GetMotherId() != -1) continue;
      if (recoTrack->GetNhits()<Nhits_cut) continue;
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      float phi = recoTrack->GetPhi();
      // if (recoTrack->GetDCAx() > 2.*fDCAx->Eval(pt, eta)) continue; //трек не проходит по DCAx
      // if (recoTrack->GetDCAy() > 2.*fDCAy->Eval(pt, eta)) continue; //трек не проходит по DCAy
      // if (recoTrack->GetDCAz() > 2.*fDCAz->Eval(pt, eta)) continue; //трек не проходит по DCAz
      // if (abs(recoTrack->GetDCAx()) > DCAcut) continue; //трек не проходит по DCAx
      // if (abs(recoTrack->GetDCAy()) > DCAcut) continue; //трек не проходит по DCAy
      // if (abs(recoTrack->GetDCAz()) > DCAcut) continue; //трек не проходит по DCAz
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // track selection      
      
      // if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

      Int_t ipt = -1;
      for(int j=0; j<npt;j++){
        if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
      }
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      int fId=-1;
      if(mcTrack->GetPdg()==211)  fId=1; // pion+
      if(mcTrack->GetPdg()==321)  fId=2; // kaon+
      if(mcTrack->GetPdg()==2212) fId=3; // proton
      if(mcTrack->GetPdg()==-211)  fId=5; // pion-
      if(mcTrack->GetPdg()==-321)  fId=6; // kaon-
      if(mcTrack->GetPdg()==-2212) fId=7; // anti-proton
      // ==================================== Eta Sub-event ==================================== //
      float v2=-999.0;
      if(eta>0){ // eta+
        // v2 = cos(2.0 * (phi-psiEP_L) )/res2[fcent];
        v2 = cos(2.0 * (phi-psiEP_L) );
      }
      if(eta<0){ // eta-
        // v2 = cos(2.0 * (phi-psiEP_R) )/res2[fcent];
        v2 = cos(2.0 * (phi-psiEP_R) );
      }
      if (charge>0){
        hPT[fcent][ipt][0]->Fill(0.5, pt, 1);
        hv2EP[fcent][ipt][0]->Fill(0.5,v2);
        hv22EP[fcent][0]->Fill(0.5,v2);
        hcounter[fcent][ipt][0]->Fill(2.5,1);
      }
      if (charge<0){
        hPT[fcent][ipt][4]->Fill(0.5, pt, 1);
        hv2EP[fcent][ipt][4]->Fill(0.5,v2);
        hv22EP[fcent][4]->Fill(0.5,v2);
        hcounter[fcent][ipt][4]->Fill(2.5,1);
      }
      
      if (fId>0) {
        hPT[fcent][ipt][fId]->Fill(0.5, pt, 1);
        hv2EP[fcent][ipt][fId]->Fill(0.5,v2);
        hv22EP[fcent][fId]->Fill(0.5,v2);
        hcounter[fcent][ipt][fId]->Fill(2.5,1);
      }
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
  hEta->Write();
  hBimp->Write();
  hMult->Write();
  hBimpvsMult->Write();

  for (int icent=0;icent<ncent;icent++){
    HRes[icent]->Write();
    
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
        hcounter[icent][ipt][id]->Write();          
      }
    }
  }
  for (int ieta=0;ieta<neta;ieta++){
    H_Qw[ieta]->Write();
    H_EP[ieta]->Write();
    for (int icent=0;icent<ncent;icent++){
      H_Qx[ieta][icent]->Write();
      H_Qy[ieta][icent]->Write();
    }
  }
  // d_outfile -> Write();
  d_outfile -> Close();
  cout << "Histfile has been written" << endl;

  timer.Stop();
  timer.Print();
}
// source /weekly/parfenov/Soft/PicoDst/build/setPicoDst.sh 
// root -l -b -q readPicoDst.C+'("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/picodst/picodst_1106385_22.root","test.root")'
// root -l -b -q readPicoDst.C+'("/weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/merged_new/picodst_merged_600.root","test.root")'
