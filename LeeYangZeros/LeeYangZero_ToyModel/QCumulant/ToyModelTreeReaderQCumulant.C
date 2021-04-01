#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include "TString.h"
#include <TStopwatch.h>

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

double CalCor24TwoSub(const TComplex &Q2a, const TComplex &Q4a, 
                      const TComplex &Q2b, const TComplex &Q4b,
                      const double &Ma, const double &Mb)
{
  double dNumerator = ((Q2a*Q2a - Q4a) * TComplex::Conjugate(Q2b*Q2b - Q4b)).Re();
  double dDenominator = Ma * (Ma-1) * Mb * (Mb-1);
  if (dDenominator != 0) { return dNumerator/dDenominator; }
  else 
  { 
    cerr << "In CalCor24TwoSub, dDenominator=0" << endl;
    return 999;
  }
}

double CalRedCor24TwoSub(const TComplex &Q2a, // const TComplex &Q4a, 
                         const TComplex &Q2b, const TComplex &Q4b,
                         const TComplex &p2a, const TComplex &q2a, 
                         const TComplex &q4a,
                         const double &Ma, const double &Mb,
                         const double &mpa, const double &mqa)
{
  double dNumerator = ( p2a*Q2a*Qstar(Q2b)*Qstar(Q2b) - q4a*Qstar(Q2b)*Qstar(Q2b) -p2a*Q2a*Qstar(Q4b) + q4a*Qstar(Q4b) ).Re();
  double dDenominator = (mpa*Ma-mqa)*Mb*(Mb-1);
  if (dDenominator != 0) { return dNumerator/dDenominator; }
  else 
  { 
    cerr << "In CalRedCor24TwoSub, dDenominator=0" << endl;
    return 999;
  }
}

double CentB(double bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  double fcent;
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

int GetCentBin(double cent)
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

void ToyModelTreeReaderQCumulant(TString inputFileName="ToyModel_M_1000.root", TString outFile="QCumulant.root")
{
  TStopwatch timer;
  timer.Start();
  const int ncent = 9; // 0-80%
  // const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
  const int npt = 12; // 0.2 - 3.5 GeV/c
  const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  const double maxpt = 3.5; // max pt
  const double minpt = 0.2; // min pt
  const double eta_cut = 2.0;
  const double eta_gap = 0;

  const int neta = 2; // [eta-,eta+]
  const int max_nh = 20000;
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
  // 2,4 QC 2-sub
  TProfile *hv22Gap[ncent];                   // <2>
  TProfile *hv24Gap[ncent];                   // <4>  
  TProfile *hcov24Gap[ncent];                 // <2><4>
  TProfile *hv22ptGap[ncent][npt];            // <2'>
  TProfile *hv24ptGap[ncent][npt];            // <4'>
  TProfile *hcov22primeGap[ncent][npt];       // <2><2'>  
  TProfile *hcov24primeGap[ncent][npt];       // <2><4'>
  TProfile *hcov42primeGap[ncent][npt];       // <2><4'>
  TProfile *hcov44primeGap[ncent][npt];       // <4><4'>
  TProfile *hcov2prime4primeGap[ncent][npt];  // <2'><4'>
  d_outfile = new TFile(outFile.Data(), "recreate");
  

  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);

  for (int ipt=0;ipt<npt;ipt++){
    hPT[ipt] = new TProfile(Form("hPT_%i", ipt), "", ncent,0.,ncent);
  }
  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2MC[icent] = new TProfile(Form("hv2MC_%i", icent),"", 1, 0., 1.);
    hv22[icent] = new TProfile(Form("hv22_%i", icent), "", 1, 0., 1.);
    hv24[icent] = new TProfile(Form("hv24_%i", icent), "", 1, 0., 1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i", icent), "", 1, 0., 1.);

    hv22Gap[icent] = new TProfile(Form("hv22Gap_%i", icent), "", 1, 0., 1.);
    hv24Gap[icent] = new TProfile(Form("hv24Gap_%i", icent), "", 1, 0., 1.);
    hcov24Gap[icent] = new TProfile(Form("hcov24Gap_%i", icent), "", 1, 0., 1.);
    for (int kpt = 0; kpt < npt; kpt++)
    { // loop over pt bin
      hv2MCpt[icent][kpt] = new TProfile(Form("hv2MCpt_%i_%i", icent, kpt), "", 1, 0., 1.);

      hv22pt[icent][kpt] = new TProfile(Form("hv22pt_%i_%i", icent, kpt), "", 1, 0., 1.);
      hv24pt[icent][kpt] = new TProfile(Form("hv24pt_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov22prime[icent][kpt] = new TProfile(Form("hcov22prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov24prime[icent][kpt] = new TProfile(Form("hcov24prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov42prime[icent][kpt] = new TProfile(Form("hcov42prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov44prime[icent][kpt] = new TProfile(Form("hcov44prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov2prime4prime[icent][kpt] = new TProfile(Form("hcov2prime4prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      
      hv22ptGap[icent][kpt] = new TProfile(Form("hv22ptGap_%i_%i", icent, kpt), "", 1, 0., 1.);
      hv24ptGap[icent][kpt] = new TProfile(Form("hv24ptGap_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov22primeGap[icent][kpt] = new TProfile(Form("hcov22primeGap_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov24primeGap[icent][kpt] = new TProfile(Form("hcov24primeGap_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov42primeGap[icent][kpt] = new TProfile(Form("hcov42primeGap_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov44primeGap[icent][kpt] = new TProfile(Form("hcov44primeGap_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov2prime4primeGap[icent][kpt] = new TProfile(Form("hcov2prime4primeGap_%i_%i", icent, kpt), "", 1, 0., 1.);

    } // end of loop over pt bin
  } // end of loop over centrality classes


  // Declaration of leaf types
  Int_t nh;
  Float_t b;
  Float_t rp;
  Float_t phi0[6000]; //[nh]
  Bool_t bFlow[6000]; //[nh]
  Float_t eta0[6000];  //[nh]
  Float_t pt0[6000];   //[nh]

  // List of branches
  TBranch *b_nh;    //!
  TBranch *b_b;     //!
  TBranch *b_rp;    //!
  TBranch *b_phi0;  //!
  TBranch *b_bFlow; //!
  TBranch *b_eta;   //!
  TBranch *b_pt;    //!

  // Configure input information
  TChain *chain = new TChain("tree");
  if (inputFileName.Contains(".root"))
  {
    chain->Add(inputFileName.Data());
  }
  // if str contains filelist
  if (!inputFileName.Contains(".root"))
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    while (std::getline(file, line))
    {
      chain->Add(line.c_str());
    }
  }
  if (!chain) return;

  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("b", &b, &b_b);
  chain->SetBranchAddress("rp", &rp, &b_rp);
  chain->SetBranchAddress("phi0", phi0, &b_phi0);
  chain->SetBranchAddress("bFlow", bFlow, &b_bFlow);
  chain->SetBranchAddress("eta", eta0, &b_eta);
  chain->SetBranchAddress("pt", pt0, &b_pt);

  // notation as (26) in DOI:10.1103/PhysRevC.83.044913

  Double_t Q2x = 0., Q2y = 0., Q4x = 0., Q4y = 0.;
  Double_t p2x[npt] = {0.}, p2y[npt] = {0.};
  Double_t q2x[npt] = {0.}, q2y[npt] = {0.}, q4x[npt] = {0.}, q4y[npt] = {0.};
  TComplex Q2 = 0., Q4 = 0., p2[npt] = {0.}, q2[npt] = {0.}, q4[npt] = {0.};
  Double_t M = 0.;
  Double_t mp[npt] = {0.}, mq[npt] = {0.};
  Double_t w2 = 0., w4 = 0.;
  Double_t wred2[npt] = {0.}, wred4[npt] = {0.};
  Double_t cor22 = 0., cor24 = 0.;
  Double_t redCor22[npt] = {0.}, redCor24[npt] = {0.};

  // 2-sub
  Double_t Q2xGap[neta]={0.}, Q2yGap[neta]={0.}, Q4xGap[neta]={0.}, Q4yGap[neta]={0.};
  Double_t p2xGap[neta][npt]={{0.}}, p2yGap[neta][npt]={{0.}};
  Double_t q2xGap[neta][npt]={{0.}}, q2yGap[neta][npt]={{0.}}, q4xGap[neta][npt]={{0.}}, q4yGap[neta][npt]={{0.}};
  TComplex Q2Gap[neta]={0.}, Q4Gap[neta]={0.}, p2Gap[neta][npt]={{0.}}, q2Gap[neta][npt]={{0.}}, q4Gap[neta][npt]={{0.}};
  Double_t MGap[neta]={0};
  Double_t mpGap[neta][npt]={{0.}}, mqGap[neta][npt]={{0.}};
  Double_t w2Gap=0., w4Gap=0.;
  Double_t wred2Gap[neta][npt]={{0.}}, wred4Gap[neta][npt]={{0.}};
  Double_t cor22Gap=0., cor24Gap=0.;
  Double_t redCor22Gap[neta][npt]={{0.}}, redCor24Gap[neta][npt]={{0.}};

  Long64_t nentries = chain->GetEntries();
  cout << "Hi, Master! Let's do some physics together!" << endl;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    chain->GetEntry(jentry);
    if (jentry % 10000 == 0) cout << "Event [" << jentry <<"/" << nentries << "]" << endl;
    double dCent = CentB(b);
    if (dCent < 0)
      continue;
    int icent = GetCentBin(dCent);

    hMult->Fill(nh);
    hRP->Fill(rp);
    hBimp->Fill(b);
    hBimpvsMult->Fill(nh, b);

    Q2x = 0.;
    Q2y = 0.;
    Q4x = 0.;
    Q4y = 0.;
    Q2 = 0.;
    Q4 = 0.;
    M = 0.;
    w2 = 0.;
    w4 = 0.;
    cor22 = 0.;
    cor24 = 0.;    
    for (int ipt=0; ipt<npt; ipt++)
    {
      redCor22[ipt] = 0.;
      redCor24[ipt] = 0.;
      mq[ipt] = 0.;
      mp[ipt] = 0.;
      wred2[ipt] = 0.;
      wred4[ipt] = 0.;
      p2x[ipt] = 0.;
      p2y[ipt] = 0.;
      p2[ipt] = 0.;
      q2[ipt] = 0.;
      q4[ipt] = 0.;
      q2x[ipt] = 0.;
      q2y[ipt] = 0.;
      q4x[ipt] = 0.;
      q4y[ipt] = 0.;
    }

    // 2-sub
    w2Gap=0.;
    w4Gap=0.;
    cor22Gap=0.;
    cor24Gap=0.;
    for (int ieta=0; ieta<neta; ieta++)
    {
      Q2xGap[ieta]=0.;
      Q2yGap[ieta]=0.;
      Q4xGap[ieta]=0.;
      Q4yGap[ieta]=0.;
      MGap[ieta]=0;
      Q2Gap[ieta]=0.;
      Q4Gap[ieta]=0.;
      for (int ipt=0; ipt<npt; ipt++)
      {
        p2xGap[ieta][ipt]=0.;
        p2yGap[ieta][ipt]=0.;
        p2Gap[ieta][ipt]=0.;
        q2xGap[ieta][ipt]=0.;
        q2yGap[ieta][ipt]=0.;
        q2Gap[ieta][ipt]=0.;
        q4xGap[ieta][ipt]=0.;
        q4yGap[ieta][ipt]=0.;
        q4Gap[ieta][ipt]=0.;            
        mpGap[ieta][ipt]=0.;
        mqGap[ieta][ipt]=0.;
        wred2Gap[ieta][ipt]=0.;
        wred4Gap[ieta][ipt]=0.;
        redCor22Gap[ieta][ipt]=0.;
        redCor24Gap[ieta][ipt]=0.;        
      }
    }

    for (int i = 0; i < nh; i++){ // track loop
      double pt = pt0[i];
      double eta = eta0[i];
      if( pt < minpt  || pt > maxpt || fabs(eta) > eta_cut) continue;
      hPt->Fill(pt);
      double phi = phi0[i];
      if (phi<0) phi += 2.*TMath::Pi();
      hPhi->Fill(phi-rp);
      hPhil->Fill(phi);
      hEta->Fill(eta);

      Int_t ipt = -1;
      for (int j = 0; j < npt; j++) {
        if (pt >= bin_pT[j] && pt < bin_pT[j + 1]) ipt = j;
      }
  
      Double_t v2 = TMath::Cos(2 * (phi - rp));
      hPT[ipt]->Fill(0.5+icent, pt, 1);

      if (bFlow[i]) {
        hv2MC[icent]->Fill(0.5, v2); // calculate reference v2 from MC toy
        hv2MCpt[icent][ipt]->Fill(0.5, v2); // Calculate differential v2 from MC toy
      }
      Double_t cos4phi = TMath::Cos(4.*phi);
      Double_t sin4phi = TMath::Sin(4.*phi);
      Double_t cos2phi = TMath::Cos(2.*phi);
      Double_t sin2phi = TMath::Sin(2.*phi);

      Q2x += cos2phi;
      Q2y += sin2phi;
      Q4x += cos4phi;
      Q4y += sin4phi; 
      M++;
      // 2,4-QC, 2-sub
      if (eta < -eta_gap)
      { // Left TPC subevent selection
        Q2xGap[0] += cos2phi;
        Q2yGap[0] += sin2phi;
        Q4xGap[0] += cos4phi;
        Q4yGap[0] += sin4phi;
        MGap[0]++;

        p2xGap[1][ipt]+=cos2phi;
        p2yGap[1][ipt]+=sin2phi;
        mpGap[1][ipt]++;

        q2xGap[1][ipt]+=cos2phi;
        q2yGap[1][ipt]+=sin2phi;
        q4xGap[1][ipt]+=cos4phi;
        q4yGap[1][ipt]+=sin4phi;
        mqGap[1][ipt]++;

      }
      if (eta > eta_gap)
      { // Right TPC subevent selection
        Q2xGap[1] += cos2phi;
        Q2yGap[1] += sin2phi;
        Q4xGap[1] += cos4phi;
        Q4yGap[1] += sin4phi;
        MGap[1]++;

        p2xGap[0][ipt]+=cos2phi;
        p2yGap[0][ipt]+=sin2phi;
        mpGap[0][ipt]++;

        q2xGap[0][ipt]+=cos2phi;
        q2yGap[0][ipt]+=sin2phi;
        q4xGap[0][ipt]+=cos4phi;
        q4yGap[0][ipt]+=sin4phi;
        mqGap[0][ipt]++;

      }

      p2x[ipt] += cos2phi;
      p2y[ipt] += sin2phi;
      mp[ipt]++;

      q2x[ipt] += cos2phi;
      q2y[ipt] += sin2phi;
      q4x[ipt] += cos4phi;
      q4y[ipt] += sin4phi;
      mq[ipt]++;

    } // end of track loop

    // if (M >= 4.){
    if (MGap[0] >= 2 && MGap[1] >= 2)
    {
      Q2 = TComplex(Q2x, Q2y);
      w2 = M * (M - 1.);                 // w(<2>)
      cor22 = CalCor22(Q2, M, w2);       // <2>
      hv22[icent]->Fill(0.5, cor22, w2); // <<2>>
      Q4 = TComplex(Q4x, Q4y);
      w4 = M * (M - 1.) * (M - 2.) * (M - 3.); // w(<4>)
      cor24 = CalCor24(Q2, Q4, M, w4);      // <4>
      hv24[icent]->Fill(0.5, cor24, w4);    // <<4>>
      hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
      if (w2 == 0 || w4 == 0) cerr << "WARNING: w2,4=0" << endl;
      for (int ipt = 0; ipt < npt; ipt++){
        if (mp[ipt] == 0) continue;
        wred2[ipt] = mp[ipt] * M - mq[ipt];                                        // w(<2'>)
        wred4[ipt] = (mp[ipt] * M - 3. * mq[ipt]) * (M - 1.) * (M - 2.);           // w(<4'>)
        if (wred2[ipt]==0) continue;
        if (wred4[ipt]==0) continue;
        p2[ipt] = TComplex(p2x[ipt], p2y[ipt]);
        q2[ipt] = TComplex(q2x[ipt], q2y[ipt]);
        q4[ipt] = TComplex(q4x[ipt], q4y[ipt]);
        redCor22[ipt] = CalRedCor22(Q2, p2[ipt], M, mp[ipt], mq[ipt], wred2[ipt]); // <2'>
        redCor24[ipt] = CalRedCor24(Q2, Q4, p2[ipt], q2[ipt], q4[ipt], M, mp[ipt], mq[ipt], wred4[ipt]); // <4'>
        hv22pt[icent][ipt]->Fill(0.5, redCor22[ipt], wred2[ipt]);                  // <<2'>>
        hv24pt[icent][ipt]->Fill(0.5, redCor24[ipt], wred4[ipt]);                                        // <<4'>>
        // TProfile for covariance calculation in statistic error
        hcov22prime[icent][ipt]->Fill(0.5, cor22 * redCor22[ipt], w2 * wred2[ipt]); // <2>*<2'>
        hcov24prime[icent][ipt]->Fill(0.5, cor22 * redCor24[ipt], w2 * wred4[ipt]);
        hcov42prime[icent][ipt]->Fill(0.5, cor24 * redCor22[ipt], w4 * wred2[ipt]);
        hcov44prime[icent][ipt]->Fill(0.5, cor24 * redCor24[ipt], w4 * wred4[ipt]);
        hcov2prime4prime[icent][ipt]->Fill(0.5, redCor22[ipt] * redCor24[ipt], wred2[ipt] * wred4[ipt]);
      }
      // 2,4-QC, 2-sub
      for (Int_t ieta = 0; ieta < neta; ieta++)
      {
        Q2Gap[ieta] = TComplex(Q2xGap[ieta], Q2yGap[ieta]);
        Q4Gap[ieta] = TComplex(Q4xGap[ieta], Q4yGap[ieta]);
      }
      w2Gap = MGap[0] * MGap[1];
      w4Gap = MGap[0] * (MGap[0]-1) * MGap[1] * (MGap[1]-1); // / 4.
      if (w4Gap==0) cout << "Error!!! w4Gap==0!!!" << endl;
      cor22Gap = CalRedCor22(Q2Gap[0], Q2Gap[1], MGap[0], MGap[1], 0., w2Gap); // <2>
      cor24Gap = CalCor24TwoSub(Q2Gap[0], Q4Gap[0], Q2Gap[1], Q4Gap[1], MGap[0], MGap[1]);
      // pCorrelator2EtaGap->Fill(0.5 + icent, cor22Gap, w2Gap);
      hv22Gap[icent]->Fill(0.5, cor22Gap, w2Gap);
      hv24Gap[icent]->Fill(0.5, cor24Gap, w4Gap);
      hcov24Gap[icent]->Fill(0.5, cor22Gap * cor24Gap, w2Gap * w4Gap); // <2>*<4>
      for (Int_t ieta = 0; ieta < neta; ieta++)
      {
        for (Int_t ipt = 0; ipt < npt; ipt++)
        {
          if (mpGap[ieta][ipt] == 0) continue;
          wred2Gap[ieta][ipt] = mpGap[ieta][ipt] * MGap[ieta];
          if (ieta==0) wred4Gap[ieta][ipt] = (mpGap[ieta][ipt]*MGap[ieta+1] - mqGap[ieta][ipt]) * MGap[ieta]*(MGap[ieta]-1);
          if (ieta==1) wred4Gap[ieta][ipt] = (mpGap[ieta][ipt]*MGap[ieta-1] - mqGap[ieta][ipt]) * MGap[ieta]*(MGap[ieta]-1);
          if (wred2Gap[ipt]==0) continue;
          if (wred4Gap[ipt]==0) continue;
          p2Gap[ieta][ipt] = TComplex(p2xGap[ieta][ipt], p2yGap[ieta][ipt]);
          q2Gap[ieta][ipt] = TComplex(q2xGap[ieta][ipt], q2yGap[ieta][ipt]);
          q4Gap[ieta][ipt] = TComplex(q4xGap[ieta][ipt], q4yGap[ieta][ipt]);
          redCor22Gap[ieta][ipt] = CalRedCor22(Q2Gap[ieta], p2Gap[ieta][ipt], MGap[ieta], mpGap[ieta][ipt], 0., wred2Gap[ieta][ipt]); // <2'>
          if (ieta==0) redCor24Gap[ieta][ipt] = CalRedCor24TwoSub(Q2Gap[ieta+1], Q2Gap[ieta],
                                                                  Q4Gap[ieta], p2Gap[ieta][ipt],
                                                                  q2Gap[ieta][ipt], q4Gap[ieta][ipt],
                                                                  MGap[ieta+1], MGap[ieta],
                                                                  mpGap[ieta][ipt], mqGap[ieta][ipt]);                                // <4'>
          if (ieta==1) redCor24Gap[ieta][ipt] = CalRedCor24TwoSub(Q2Gap[ieta-1], Q2Gap[ieta],
                                                                  Q4Gap[ieta], p2Gap[ieta][ipt],
                                                                  q2Gap[ieta][ipt], q4Gap[ieta][ipt],
                                                                  MGap[ieta-1], MGap[ieta],
                                                                  mpGap[ieta][ipt], mqGap[ieta][ipt]);                                // <4'>
          hv22ptGap[icent][ipt]->Fill(0.5, redCor22Gap[ieta][ipt], wred2Gap[ieta][ipt]);                                              // <<2'>>
          hv24ptGap[icent][ipt]->Fill(0.5, redCor24Gap[ieta][ipt], wred4Gap[ieta][ipt]);                                              // <<4'>>
          // Covariances
          hcov22primeGap[icent][ipt]->Fill(0.5, cor22Gap * redCor22Gap[ieta][ipt], w2Gap * wred2Gap[ieta][ipt]);                                  // <2>*<2'>
          hcov24primeGap[icent][ipt]->Fill(0.5, cor22Gap * redCor24Gap[ieta][ipt], w2Gap * wred4Gap[ieta][ipt]);                                  // <2>*<4'>
          hcov42primeGap[icent][ipt]->Fill(0.5, cor24Gap * redCor22Gap[ieta][ipt], w4Gap * wred2Gap[ieta][ipt]);                                  // <4>*<2'>  
          hcov44primeGap[icent][ipt]->Fill(0.5, cor24Gap * redCor24Gap[ieta][ipt], w4Gap * wred4Gap[ieta][ipt]);                                  // <4>*<4'>
          hcov2prime4primeGap[icent][ipt]->Fill(0.5, redCor22Gap[ieta][ipt]*redCor24Gap[ieta][ipt], wred2Gap[ieta][ipt]*wred4Gap[ieta][ipt]);     // <2'>*<4'>

        }
      }

    }
  } // end of event loop

  // chain->Close();
  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  timer.Stop();
  timer.Print();
}

int main(int argc, char **argv)
{
  TString iFileName, oFileName;

  if (argc < 5)
  {
    std::cerr << "./FlowQCumulant -i INPUT -o OUTPUT" << std::endl;
    return 1;
  }
  for (Int_t i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 3;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 4;
      }
    }
  }
  ToyModelTreeReaderQCumulant(iFileName, oFileName);
  return 0;
}