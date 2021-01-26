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

void ToyModelTreeReaderQCumulant(TString file="ToyModel_M_1000.root", TString outFile="QCumulant.root")
{

  const int ncent = 9; // 0-80%
  const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
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

  for (int ipt=0;ipt<npt;ipt++){
    hPT[ipt] = new TProfile(Form("hPT_%i", ipt), "", ncent,0.,ncent);
  }
  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2MC[icent] = new TProfile(Form("hv2MC_%i", icent),"", 1, 0., 1.);
    hv22[icent] = new TProfile(Form("hv22_%i", icent), "", 1, 0., 1.);
    hv24[icent] = new TProfile(Form("hv24_%i", icent), "", 1, 0., 1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i", icent), "", 1, 0., 1.);
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
    if (jentry % 100000 == 0)
      cout << jentry << endl;
    double dCent = CentB(b);
    if (dCent < 0)
      continue;
    int icent = GetCentBin(dCent);

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


    for (int i = 0; i < nh; i++){ // track loop
      double pT = pt[i];
      if( pT < minpt  || pT > maxpt || eta[i] > eta_cut) continue;
      hPt->Fill(pT);
      double phi = phi0[i];
      if (phi<0) phi += 2.*TMath::Pi();
      hPhi->Fill(phi-rp);
      hPhil->Fill(phi);
      hEta->Fill(eta[i]);

      Int_t ipt = -1;
      for (int j = 0; j < npt; j++) {
        if (pT >= bin_pT[j] && pT < bin_pT[j + 1]) ipt = j;
      }
  
      Double_t v2 = TMath::Cos(2 * (phi - rp));
      hPT[ipt]->Fill(0.5+icent, pT, 1);

      if (bFlow[i]) {
        hv2MC[icent]->Fill(0.5, v2); // calculate reference v2 from MC toy
        hv2MCpt[icent][ipt]->Fill(0.5, v2); // Calculate differential v2 from MC toy
      }
      Double_t cos4phi = TMath::Cos(4.*phi);
      Double_t sin4phi = TMath::Sin(4.*phi);
      Double_t cos2phi = TMath::Cos(2.*phi);
      Double_t sin2phi = TMath::Sin(2.*phi);

      Qx2 += cos2phi;
      Qy2 += sin2phi;
      Qx4 += cos4phi;
      Qy4 += sin4phi; 
      M++;

      px2[ipt] += cos2phi;
      py2[ipt] += sin2phi;
      mp[ipt]++;

      qx2[ipt] += cos2phi;
      qy2[ipt] += sin2phi;
      qx4[ipt] += cos4phi;
      qy4[ipt] += sin4phi;
      mq[ipt]++;

    } // end of track loop

    if (M >= 4.){
      Q2 = TComplex(Qx2, Qy2);
      w2 = M * (M - 1.);                 // w(<2>)
      cor22 = CalCor22(Q2, M, w2);       // <2>
      hv22[icent]->Fill(0.5, cor22, w2); // <<2>>
      Q4 = TComplex(Qx4, Qy4);
      w4 = M * (M - 1.) * (M - 2.) * (M - 3.); // w(<4>)
      cor24 = CalCor24(Q2, Q4, M, w4);      // <4>
      hv24[icent]->Fill(0.5, cor24, w4);    // <<4>>
      hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
      if (w2 == 0 || w4 == 0) cerr << "WARNING: w2,4=0" << endl;
      for (int ipt = 0; ipt < npt; ipt++){
        if (mp[ipt] == 0) continue;
        p2[ipt] = TComplex(px2[ipt], py2[ipt]);
        q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
        wred2[ipt] = mp[ipt] * M - mq[ipt];                                        // w(<2'>)
        if (wred2[ipt]==0) continue;
        redCor22[ipt] = CalRedCor22(Q2, p2[ipt], M, mp[ipt], mq[ipt], wred2[ipt]); // <2'>
        hv22pt[icent][ipt]->Fill(0.5, redCor22[ipt], wred2[ipt]);                  // <<2'>>

        hcov22prime[icent][ipt]->Fill(0.5, cor22 * redCor22[ipt], w2 * wred2[ipt]); // <2>*<2'>

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
    }
  } // end of event loop

  // fChain->Close();
  cout << file << " file processed" << endl;
  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;

}