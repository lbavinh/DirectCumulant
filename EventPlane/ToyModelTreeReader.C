#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include "TString.h"

#include <iostream>
#include <fstream>
using namespace std;
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

TComplex Qstar(TComplex Q){
   TComplex QStar   = TComplex::Conjugate(Q);
   return QStar;
}

Double_t CalCor22(TComplex Q2, Double_t M, Double_t w2){
   // single-event average 2-particle azimuthal correlation <2>

  Double_t Q2Square = Q2.Rho2();
  Double_t coor22   = Q2Square - M;                                          
  
  return coor22/w2;
}

Double_t CalCor24(TComplex Q2, TComplex Q4, Double_t M, Double_t w4){
   // single-event average 4-particle azimuthal correlation <4>

   TComplex Q2Star   = Qstar(Q2);
   TComplex Q4Star   = Qstar(Q4);
   
   Double_t Q2Square = Q2.Rho2();
   Double_t Q4Square = Q4.Rho2();
   Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

   Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2.*ReQQQ
                        - 4.*(M-2.)*Q2Square + 2.*M*(M-3.));

   return coor24/w4;
}

Double_t CalRedCor22(TComplex Q2, TComplex p2, Double_t M, Double_t mp, 
                     Double_t mq, Double_t wred2){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   Double_t coor22 = (p2*Q2Star-mq).Re();

   return coor22/wred2;
}

Double_t CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                            TComplex q4, Double_t M, Double_t mp, Double_t mq, Double_t wred4){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   TComplex Q4Star = TComplex::Conjugate(Q4);
   TComplex q2Star = TComplex::Conjugate(q2);
   Double_t Q2Square = Q2.Rho2();
   TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
                  - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
                  - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
                  + 2.0*mq*M-6.0*mq;
             
   Double_t coor24 = coorc.Re(); 
   return coor24/wred4;
}

Int_t CentB(Float_t bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  int fcent;
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
    return fcent + 5;
  else
    return -1;
}

void ToyModelTreeReader(TString file="ToyModel.root", TString outFile="out.root")
{

  const int ncent = 8; // 0-80%
  const int bin_cent[ncent] = {5, 15, 25, 35, 45, 55, 65, 75};

  const double maxpt = 3.5; // max pt
  const double minpt = 0.2; // min pt
  const int npt = 12;        // 0.2 - 3.5 GeV/c
  const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  const int neta = 2; // [eta-,eta+]
  const int max_nh = 6000;
  TFile *d_outfile; // out file with histograms and profiles

  TH1F *hRP;         // reaction plane distr
  TH1F *hPt;         // transverse momentum distr
  TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
  TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
  TH1F *hEta;        // pseudorapidity
  TH1F *hBimp;       // impact parameter
  TH1I *hMult;       // emitted multiplicity
  TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

  // TProfile for reference flow (RF)
  TProfile *hv2MC[ncent]; // profile for MC integrated v2
  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow (DF)
  TProfile *hPT[npt];     // profile pt
  TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
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

  TProfile *hv2EP[npt];	// elliptic flow from EP method
  TProfile *hv22EP;      // integrated elliptic flow from EP method

  TH1F *H_Qw[neta];     // sub-event multiplicity
  TH1F *H_EP[neta];		  // reaction plane
  TH1F *H_Qv[neta];     // sub-event <Q> - probably
  TProfile *HRes;		// resolution
  float res2[ncent];

  char name[800];
  char title[800];
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << outFile.Data() << " has been initialized" << endl;

  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);
  hv22EP = new TProfile("hv22EP","Ref. v_{2}{EP}", ncent,0.,ncent);
  hv22EP->Sumw2();
  HRes = new TProfile("HRes","EP resolution", ncent,0.,ncent);
  HRes->Sumw2();
  for( int ieta=0; ieta<neta; ieta++ ){
    (void)sprintf(name,"H_Qw_%d",ieta);
    H_Qw[ieta] = new TH1F(name,name, 100, 0, 1000 );    
    (void)sprintf(name,"H_EP_%d",ieta);
    H_EP[ieta] = new TH1F(name,name, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    (void)sprintf(name,"H_Qv_%d",ieta);
    H_Qv[ieta] = new TH1F(name,name, 100, 0, 10 );
  }
  for (int ipt=0;ipt<npt;ipt++){
    sprintf(name,"hv2EP_%i",ipt);
    hv2EP[ipt] = new TProfile(name,name, ncent,0.,ncent);
    hv2EP[ipt]->Sumw2();
    sprintf(name, "hPT_%i", ipt);
    hPT[ipt] = new TProfile(name, name, ncent,0.,ncent);
    hPT[ipt]->Sumw2();
  }
  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    sprintf(name, "hv2MC_%i", icent);
    sprintf(title, "v_{2}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv2MC[icent] = new TProfile(name, title, 1, 0., 1.);
    hv2MC[icent]->Sumw2();

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
    
      sprintf(name, "hv2MCpt_%i_%i", icent, kpt);
      sprintf(title, "v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv2MCpt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv2MCpt[icent][kpt]->Sumw2();

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

  // Declaration of leaf types
  Int_t nh;
  Float_t b;
  Float_t rp;
  Float_t phi0[6000]; //[nh]
  Bool_t bFlow[6000]; //[nh]
  Float_t eta[6000];  //[nh]
  Float_t pt[6000];   //[nh]

  // List of branches
  TBranch *b_nh;    //!
  TBranch *b_b;     //!
  TBranch *b_rp;    //!
  TBranch *b_phi0;  //!
  TBranch *b_bFlow; //!
  TBranch *b_eta;   //!
  TBranch *b_pt;    //!

  // TFile *treefile = TFile::Open(file.Data());
  // TTree *tree = (TTree *)treefile->Get("tree");
  // if (tree == 0)
  // {
  //   cout << "tree is not found in " << file << endl;
  //   treefile->Close();
  //   return;
  // }
  // cout << file << " is opened" << endl;
  
  TChain *fChain = new TChain("tree");
  fChain->Add(file.Data());
  if (!fChain) return;
  fChain->SetBranchAddress("nh", &nh, &b_nh);
  fChain->SetBranchAddress("b", &b, &b_b);
  fChain->SetBranchAddress("rp", &rp, &b_rp);
  fChain->SetBranchAddress("phi0", phi0, &b_phi0);
  fChain->SetBranchAddress("bFlow", bFlow, &b_bFlow);
  fChain->SetBranchAddress("eta", eta, &b_eta);
  fChain->SetBranchAddress("pt", pt, &b_pt);

  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntries();
  cout << "Calculating flow..." << endl;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    fChain->GetEntry(jentry);

    int icent = -1;
    for (int i = 0; i < ncent; i++)
    { // loop over centrality
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0)
      continue;
    hMult->Fill(nh);
    hRP->Fill(rp);
    hBimp->Fill(b);
    hBimpvsMult->Fill(nh, b);
    // notation as (26) in DOI:10.1103/PhysRevC.83.044913

    // Q-vector of RFP
    Double_t Qx2 = 0., Qy2 = 0., Qx4 = 0., Qy4 = 0.;
    TComplex Q2 = 0., Q4 = 0.;
    // p-vector of POI
    Double_t px2[npt] = {0.}, py2[npt] = {0.};
    TComplex p2[npt] = {0.}, p4[npt] = {0.}, q2[npt] = {0.}, q4[npt] = {0.};
    // q-vector of particles marked as POI and RFP, which is used for
    // autocorrelation substraction
    Double_t qx2[npt] = {0.}, qy2[npt] = {0.}, qx4[npt] = {0.}, qy4[npt] = {0.};
    // Total number of RFP in given event
    Double_t M = 0.;
    // numbers of POI (mp) and particles marked both POI and RFP (mq)
    Double_t mq[npt] = {0.}, mp[npt] = {0.};
    // average reduced single-event 2- and 4-particle correlations : <2'> & <4'>
    Double_t redCor22[npt] = {0.}, redCor24[npt] = {0.};
    // event weights for correlation calculation
    Double_t w2 = 0., w4 = 0.;
    // event weights for reduced correlation calculation
    Double_t wred2[npt] = {0.}, wred4[npt] = {0.};
    // Average single-event 2- and 4- particle correlations : <2> & <4>
    Double_t cor22 = 0., cor24 = 0.;

    Double_t sumQxy[neta][2]={{0}};  // [eta-,eta+][x,y]
    Double_t multQv[neta]={0};       // [eta+,eta-]
    for (int i = 0; i < nh; i++){ // track loop
      double pT = pt[i];
      if( pT<minpt  || pT>maxpt ) continue;
      hPt->Fill(pT);
      double phi = phi0[i] - rp;
      if (phi<0) phi += 2.*TMath::Pi();
      hPhi->Fill(phi);
      hPhil->Fill(phi0[i]);
      hEta->Fill(eta[i]);

      Int_t ipt = 0;
      for (int j = 0; j < npt; j++) {
        if (pT >= bin_pT[j] && pT < bin_pT[j + 1]) ipt = j;
      }
    
      Double_t v2 = TMath::Cos(2 * (phi0[i] - rp));
      hPT[ipt]->Fill(0.5+icent, pT, 1);

      // RFP
      if (eta[i] < -0.05){
        if (bFlow[i]) hv2MC[icent]->Fill(0.5, v2, 1); // calculate reference v2 from MC toy
        Qx2 += TMath::Cos(2. * phi0[i]);
        Qy2 += TMath::Sin(2. * phi0[i]);
        Qx4 += TMath::Cos(4. * phi0[i]);
        Qy4 += TMath::Sin(4. * phi0[i]);   
        M++;
      }

      // POI
      if (eta[i] > 0.05){
        if (bFlow[i]) hv2MCpt[icent][ipt]->Fill(0.5, v2, 1); // Calculate differential v2 from MC toy
        px2[ipt] += TMath::Cos(2. * phi0[i]);
        py2[ipt] += TMath::Sin(2. * phi0[i]); 
        mp[ipt]++;
      }
      // if (eta[i] > 0.05) {
      //   qx2[ipt] += TMath::Cos(2. * phi0[i]);
      //   qy2[ipt] += TMath::Sin(2. * phi0[i]);
      //   mq[ipt]++;
      // }

      // Sub eta event method
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pT * cos( (2.0) * phi0[i] );
        sumQxy[fEta][1] += pT * sin( (2.0) * phi0[i] );
        multQv[fEta]++;
      } // end of eta selection
    } // end of track loop

    if (M >= 2.){ // <2> definition condition
      Q2 = TComplex(Qx2, Qy2);
      w2 = M * (M - 1.);                 // w(<2>)
      cor22 = CalCor22(Q2, M, w2);       // <2>
      hv22[icent]->Fill(0.5, cor22, w2); // <<2>>
    } // end of <2> definition condition

    for (int ipt = 0; ipt < npt; ipt++){
      if (mp[ipt] == 0 || M<1) continue;
      Q2 = TComplex(Qx2, Qy2);
      p2[ipt] = TComplex(px2[ipt], py2[ipt]);
      q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
      wred2[ipt] = mp[ipt] * M - mq[ipt];                                        // w(<2'>)
      if (wred2[ipt]==0) continue;
      redCor22[ipt] = CalRedCor22(Q2, p2[ipt], M, mp[ipt], mq[ipt], wred2[ipt]); // <2'>
      hv22pt[icent][ipt]->Fill(0.5, redCor22[ipt], wred2[ipt]);                  // <<2'>>

      // TProfile for covariance calculation in statistic error
      hcov22prime[icent][ipt]->Fill(0.5, cor22 * redCor22[ipt], w2 * wred2[ipt]); // <2>*<2'>
    }

    if (M >= 4.){ // <4> definition condition
      Q4 = TComplex(Qx4, Qy4);
      w4 = M * (M - 1.) * (M - 2.) * (M - 3.); // w(<4>)
      cor24 = CalCor24(Q2, Q4, M, w4);      // <4>
      hv24[icent]->Fill(0.5, cor24, w4);    // <<4>>

      // TProfile for covariance calculation in statistic error
      hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
    } // end of <4> definition condition

    for (int ipt = 0; ipt < npt; ipt++){
      if ( mp[ipt] == 0 || M < 3 ) continue;
      Q4 = TComplex(Qx4, Qy4);
      q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
      wred4[ipt] = (mp[ipt] * M - 3. * mq[ipt]) * (M - 1.) * (M - 2.);                                 // w(<4'>)
      if (wred4[ipt]==0) continue;
      redCor24[ipt] = CalRedCor24(Q2, Q4, p2[ipt], q2[ipt], q4[ipt], M, mp[ipt], mq[ipt], wred4[ipt]); // <4'>
      hv24pt[icent][ipt]->Fill(0.5, redCor24[ipt], wred4[ipt]);                                        // <<4'>>

      // TProfile for covariance calculation in statistic error
      hcov24prime[icent][ipt]->Fill(0.5, cor22 * redCor24[ipt], w2 * wred4[ipt]);
      hcov42prime[icent][ipt]->Fill(0.5, cor24 * redCor22[ipt], w4 * wred2[ipt]);
      hcov44prime[icent][ipt]->Fill(0.5, cor24 * redCor24[ipt], w4 * wred4[ipt]);
      hcov2prime4prime[icent][ipt]->Fill(0.5, redCor22[ipt] * redCor24[ipt], wred2[ipt] * wred4[ipt]);
    }
    // Eta sub-event method

    Double_t fEP[2]; // [eta-,eta+]
    Double_t fQv[2];
    for (int ieta=0; ieta<neta; ieta++){
      if( multQv[ieta]>5 ){ // multiplicity > 5
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
        fEP[ieta] = TMath::ATan2( sin( 2.0*fEP[ieta] ), cos( 2.0*fEP[ieta] ) ); // what for?
        fEP[ieta] /= 2.0;
        fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0],2.0)+TMath::Power( sumQxy[ieta][1],2.0))/TMath::Sqrt(multQv[ieta]);
      }else{
        fEP[ieta] = -9999;
        fQv[ieta] = -9999;
      }
    }

    // Estimate the event plane resolution of 2nd harmonic by the correlation between the azimuthal
    // angles of two subset groups of tracks, called sub-events \eta- and \eta+
    Double_t psi1, psi2, fq1, fq2;
    psi1 = fEP[0];  // eta-
    psi2 = fEP[1];  // eta+
    fq1 = fQv[0];
    fq2 = fQv[1];
    if (psi1<-9000 || psi2<-9000) return;
    if (fq1<0 || fq2<0) return;

    if(icent>=0&&icent<=7){ // centrality selection 0-80%
      for(int itrk=0;itrk<nh;itrk++) {  //track loop
        Double_t pT = pt[itrk];
        if( pT<minpt || pT>maxpt ) continue;

        Int_t ipt = 0;
        for (int j = 0; j < npt; j++)
        {
          if (pT >= bin_pT[j] && pT < bin_pT[j + 1])
            ipt = j;
        }

        float v2=-999.0;
        
        if(eta[itrk]>0){ // eta+
          v2 = cos(2.0 * (phi0[itrk]-psi1) );
        }

        if(eta[itrk]<0){ // eta-
          v2 = cos(2.0 * (phi0[itrk]-psi2) );
        }
        // if(fabs(eta[itrk])<1.0){ // eliminate spectators
        hv2EP[ipt]->Fill(0.5+icent,v2);
        if (eta[itrk] < -0.05) { // Reference flow
          hv22EP->Fill(0.5+icent,v2);
        }
        
        // } // end of |eta| < 1.0
      }// end of the track loop
    }// end of centrality selection 

    if (jentry % 100000 == 0)
      cout << jentry << endl;
  }

  // fChain->Close();
  cout << file << " file processed" << endl;
  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;

}