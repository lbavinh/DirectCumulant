/*
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
  static const int nhitsmin = 32; // minimum nhits of reconstructed tracks
  static const float DCAcut = 0.5;
  static const int neta = 2; // [eta-,eta+]

  static const int max_nh = 1700;


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
  TProfile *hv22EP[ncent][npid];      // integrated flow from EP method

  TH1F *H_Qw[neta];     // sub-event multiplicity
  TH1F *H_EP[neta];		  // reaction plane
  TH1F *H_Qv[neta];     // sub-event <Q> - probably
  TProfile *HRes[ncent];		// resolution
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

  for( int ieta=0;ieta<neta;ieta++){
    H_Qw[ieta] = new TH1F(Form("H_Qw_%d",ieta),Form("H_Qw_%d",ieta), 100, 0, 1000 );    
    H_EP[ieta] = new TH1F(Form("H_EP_%d",ieta),Form("H_EP_%d",ieta), 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    H_Qv[ieta] = new TH1F(Form("H_Qv_%d",ieta),Form("H_Qv_%d",ieta), 100, 0, 10 );
  }

  for (int icent=0;icent<ncent;icent++){ // loop over centrality classes
    HRes[icent] = new TProfile(Form("HRes_%i",icent),Form("HRes_%i",icent),1,0.,1.);
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
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      if (mcTrack->GetMotherId() != -1) continue;
      if (recoTrack->GetNhits()<=nhitsmin ) continue;
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      // if (abs(recoTrack->GetDCAx()) > DCAcut) continue; //трек не проходит по DCAx
      // if (abs(recoTrack->GetDCAy()) > DCAcut) continue; //трек не проходит по DCAy
      // if (abs(recoTrack->GetDCAz()) > DCAcut) continue; //трек не проходит по DCAz
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // track selection
      float phi = recoTrack->GetPhi();
      if (phi<0) phi += 2.*TMath::Pi();

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

      
      // Double_t v2 = TMath::Cos(2.*phi);
      // hv2MC[fcent]->Fill(0.5, v2, 1);
      // hv2MCpt[fcent][ipt]->Fill(0.5, v2, 1);
      if(eta<0){
        // RFP selection
        Qx2[0]+=TMath::Cos(2.*phi);
        Qy2[0]+=TMath::Sin(2.*phi);
        Qx4[0]+=TMath::Cos(4.*phi);
        Qy4[0]+=TMath::Sin(4.*phi);
        M[0]++;
        // POI selection
        if (recoTrack->GetCharge()>0){
          px2[1][ipt][0]+=TMath::Cos(2.*phi);
          py2[1][ipt][0]+=TMath::Sin(2.*phi);
          mp[1][ipt][0]++;
        }
        if (recoTrack->GetCharge()<0){
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
        // if (recoTrack->GetCharge()>0){
          px2[0][ipt][0]+=TMath::Cos(2.*phi);
          py2[0][ipt][0]+=TMath::Sin(2.*phi);
          mp[0][ipt][0]++;
        // }
        // if (recoTrack->GetCharge()<0){
          px2[0][ipt][4]+=TMath::Cos(2.*phi);
          py2[0][ipt][4]+=TMath::Sin(2.*phi);
          mp[0][ipt][4]++;
        // }
        if (fId>0){
          px2[0][ipt][fId]+=TMath::Cos(2.*phi);
          py2[0][ipt][fId]+=TMath::Sin(2.*phi);
          mp[0][ipt][fId]++;
        }
      }

      // Sub eta event method, TPC plane
      int fEta = -1;
      if (eta < 0) fEta = 0; // TPC East
      if (eta > 0) fEta = 1; // TPC West

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pt * cos( (2.0) * phi );
        sumQxy[fEta][1] += pt * sin( (2.0) * phi );
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

    Double_t fEP[2]; // [eta-,eta+]
    Double_t fQv[2];
    for (int ieta=0; ieta<neta; ieta++){
      if( multQv[ieta]>=4 ){ // multiplicity > 3
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

    float res2[ncent] = {0.205352,0.326948,0.344818,0.318183,0.264808,0.19769,0.148519,0.128865};

    for (int iTr=0; iTr<reco_mult; iTr++) { // track loop
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(iTr);
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId());
      if (mcTrack->GetMotherId() != -1) continue;
      if (recoTrack->GetNhits()<=nhitsmin ) continue;
      float pt  = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      // if (recoTrack->GetDCAx() > 2.*fDCAx->Eval(pt, eta)) continue; //трек не проходит по DCAx
      // if (recoTrack->GetDCAy() > 2.*fDCAy->Eval(pt, eta)) continue; //трек не проходит по DCAy
      // if (recoTrack->GetDCAz() > 2.*fDCAz->Eval(pt, eta)) continue; //трек не проходит по DCAz
      // if (abs(recoTrack->GetDCAx()) > DCAcut) continue; //трек не проходит по DCAx
      // if (abs(recoTrack->GetDCAy()) > DCAcut) continue; //трек не проходит по DCAy
      // if (abs(recoTrack->GetDCAz()) > DCAcut) continue; //трек не проходит по DCAz
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // track selection      
      float phi = recoTrack->GetPhi();
      if (phi<0) phi += 2.*TMath::Pi();

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
      if (fId>0) hPT[fcent][ipt][fId]->Fill(0.5, pt, 1);
      // ==================================== Eta Sub-event ==================================== //
      float v2=-999.0;
      if(eta>0){ // eta+
        // v2 = cos(2.0 * (phi-psi1) )/res2[fcent];
        v2 = cos(2.0 * (phi-psi1) );
      }
      if(eta<0){ // eta-
        // v2 = cos(2.0 * (phi-psi2) )/res2[fcent];
        v2 = cos(2.0 * (phi-psi2) );
      }
      // if (recoTrack->GetCharge()>0){
        hPT[fcent][ipt][0]->Fill(0.5, pt, 1);
        hv2EP[fcent][ipt][0]->Fill(0.5,v2);
        hv22EP[fcent][0]->Fill(0.5,v2);
        hcounter[fcent][ipt][0]->Fill(2.5,1);
      // }
      // if (recoTrack->GetCharge()<0){
        hPT[fcent][ipt][4]->Fill(0.5, pt, 1);
        hv2EP[fcent][ipt][4]->Fill(0.5,v2);
        hv22EP[fcent][4]->Fill(0.5,v2);
        hcounter[fcent][ipt][4]->Fill(2.5,1);
      // }
      
      if (fId>0) {
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
  hPhil->Write();
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
    H_Qv[ieta]->Write();
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
*/
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
