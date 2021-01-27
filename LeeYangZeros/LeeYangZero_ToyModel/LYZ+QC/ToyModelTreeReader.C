#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include <TLegend.h>
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

using std::cout;
using std::endl;
using std::cerr;
#define sqr(x) ((x)*(x))
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

void GetRes(TProfile *const &pr)
{
  cout << "const double res2[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX()-1; i++)
  {
    cout << TMath::Sqrt(pr->GetBinContent(i+1)) <<", ";
  }
  cout << TMath::Sqrt(pr->GetBinContent(pr->GetNbinsX())) <<"};" << endl;
}

void GetMultMean(TProfile *const &pr)
{
  cout << "const double dMultMean[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX()-1; i++)
  {
    cout << (pr->GetBinContent(i+1)) <<", ";
  }
  cout <<(pr->GetBinContent(pr->GetNbinsX()))<<"};" << endl;
}

double GetR0(TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of Gtheta 

  int iNbins = hist->GetNbinsX();
  double dR0 = 0.; 

  for (int b=2;b<iNbins;b++)
  {
    double dG0 = hist->GetBinContent(b);
    double dGnext = hist->GetBinContent(b+1);
    double dGnextnext = hist->GetBinContent(b+2);
    // cout << hist->GetBinCenter(b);
    if (dGnext > dG0 && dGnextnext > dG0 && dG0<1.)
    {
      double dGlast = hist->GetBinContent(b-1);
      double dXlast = hist->GetBinCenter(b-1);
      double dX0 = hist->GetBinCenter(b);
      double dXnext = hist->GetBinCenter(b+1);

      dR0 = dX0 - ((dX0-dXlast)*(dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dX0-dXnext)*(dG0-dGlast))/
        (2.*((dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dG0-dGlast))); //parabolic interpolated minimum
      break; //stop loop if minimum is found
    } //if

  }//b

      
  return dR0;
}

TH1F* FillHistGtheta(TProfile *const &prReGtheta, TProfile *const &prImGtheta)
{
  Int_t iNbins = prReGtheta->GetNbinsX();
  Double_t xMin = prReGtheta->GetXaxis()->GetBinLowEdge(1);
  Double_t xMax = prReGtheta->GetXaxis()->GetBinLowEdge(iNbins) + prReGtheta->GetXaxis()->GetBinWidth(iNbins);
  TH1F* hGtheta = new TH1F(Form("hist_%s",prReGtheta->GetName()),"",iNbins,xMin,xMax);
  for (int rbin = 0; rbin < iNbins; rbin++)
  {
    // get bincentre of bins in histogram
    Double_t dRe = prReGtheta->GetBinContent(rbin+1);
    Double_t dIm = prImGtheta->GetBinContent(rbin+1);
    TComplex cGtheta(dRe,dIm);
    //fill fHistGtheta with the modulus squared of cGtheta
    //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
    if (cGtheta.Rho2()>3.) hGtheta->SetBinContent(rbin+1,0);
    else hGtheta->SetBinContent(rbin+1,cGtheta.Rho2());
    // hGtheta->SetBinContent(rbin+1,cGtheta.Rho2());
    hGtheta->SetBinError(rbin+1,0.0);
  }
  return hGtheta;
}

double BesselJ0(double x)
{
  double temp=1., xn=1.;
  long n, Nmax;

  Nmax=int(floor(2.*x)+4);
  for (n=1;n<Nmax;n++)
  {
    xn*=(-sqr(x/2./((float) n)));
    temp+=xn;
  }
  return temp;
}

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

void ToyModelTreeReader(TString inputFileName = "ToyModel.root", TString outputFileName = "test.root", Bool_t bFirstRun = 1)
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

  // LYZ
  bool bUseProduct = 1;
  const int rbins = 2500;
  const double rMax = 0.5;
  const double rMin = 0.005;
  const double rMaxSum = 250;
  const double rMinSum = 0;
  const int thetabins = 5;
  const double rootJ0 = 2.4048256;
  const double J1rootJ0 = 0.519147;
  double theta[thetabins];
  double multPOI[npt];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  double Qtheta[thetabins];
  TComplex genfunS[rbins][thetabins]; // sum
  TComplex genfunP[rbins][thetabins]; // product
  TComplex genfunPr0[thetabins]; // product
  TComplex cdGr0[thetabins];
  TComplex cExpo;
  double Q2x, Q2y;
  int mult;
  
  // Differential LYZ
  TComplex cDenominator;
  TComplex cExponent[thetabins];

  // from 1-st run

const double res2[9] = {0.584718, 0.724644, 0.81762, 0.858491, 0.85583, 0.82071, 0.748597, 0.63331, 0.488836};
// const double r02[ncent][thetabins] = {{0.0395063, 0.0398562, 0.0399983, 0.0399956, 0.0397162 },
// {0.0317756, 0.0317372, 0.0316871, 0.0317655, 0.0318764 },
// {0.0290447, 0.0289142, 0.0289302, 0.0289397, 0.0290322 },
// {0.0309952, 0.0309848, 0.031009, 0.0310251, 0.0310295 },
// {0.0381208, 0.0380498, 0.03805, 0.0380708, 0.0381157 },
// {0.0530593, 0.0530336, 0.0529607, 0.0530779, 0.0530818 },
// {0.0848463, 0.0847794, 0.0849068, 0.0849609, 0.0849139 },
// {0.174272, 0.173572, 0.17187, 0.17073, 0.171588 },
// {0, 0, 0, 0, 0 },
//  };
// const double chisq[9] = {0.911555, 1.25572, 1.58118, 1.7373, 1.66083, 1.4094, 1.07872, 0.654145, 0.33026};

const double r02[ncent][thetabins] = {{155.722, 157.143, 157.945, 157.756, 156.773 },
{102.677, 102.609, 102.479, 102.714, 103.054 },
{70.9911, 70.651, 70.7183, 70.748, 70.9474 },
{51.4769, 51.4586, 51.5087, 51.5327, 51.5382 },
{42.356, 42.2836, 42.2978, 42.3127, 42.3665 },
{37.4947, 37.4645, 37.4393, 37.4674, 37.4931 },
{34.7908, 34.7983, 34.8452, 34.8488, 34.7904 },
{33.9464, 33.8188, 33.7661, 33.724, 33.7591 },
{33.4536, 33.8116, 34.1762, 33.6193, 33.3224 },
 };

const double r02Pro[ncent][thetabins] = {{0.0395839, 0.0399656, 0.0400806, 0.0400938, 0.0398228 },
{0.0317164, 0.0316762, 0.0316221, 0.0316982, 0.0318117 },
{0.028981, 0.0288555, 0.0288653, 0.0288714, 0.0289637 },
{0.0308428, 0.0308339, 0.0308573, 0.0308734, 0.0308762 },
{0.0377878, 0.0377225, 0.0377136, 0.0377306, 0.0377742 },
{0.0520696, 0.0520408, 0.0519703, 0.0520912, 0.0520978 },
{0.0807638, 0.0807058, 0.0808258, 0.080827, 0.080787 },
{0.144313, 0.143242, 0.143493, 0.142505, 0.141877 },
{0.272917, 0.274304, 0.282908, 0.269197, 0.264743 },
 };


  TFile *d_outfile = new TFile(outputFileName.Data(), "recreate");

  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  TH2F *hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  TH1F *hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);

  TProfile *hv2MC = new TProfile("hv2MC", "MC flow", ncent, &bin_cent[0]);
  TProfile *hv2EP = new TProfile("hv2EP", "Ref. v_{2}{EP}", ncent, &bin_cent[0]);
  TProfile *HRes = new TProfile("HRes", "EP resolution", ncent, &bin_cent[0]);

  TProfile *hv2MCpt[ncent];
  TProfile *hv2EPpt[ncent];

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2EPpt[icent] = new TProfile(Form("hv2EPpt_%i", icent), "", npt, &bin_pT[0]);
    hv2MCpt[icent] = new TProfile(Form("hv2MCpt_%i", icent), "", npt, &bin_pT[0]);
  } // end of loop over centrality classes

  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TH1F *hGthetaSum[ncent][thetabins];

  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TH1F *hGthetaProduct[ncent][thetabins];


  TProfile *prRefMult = new TProfile("prRefMult","",ncent, &bin_cent[0]);
  TProfile *prQ2x = new TProfile("prQ2x","",ncent, &bin_cent[0]);
  TProfile *prQ2y = new TProfile("prQ2y","",ncent, &bin_cent[0]);
  TProfile *prQ2ModSq = new TProfile("prQ2ModSq","",ncent, &bin_cent[0]);

  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];

  TProfile *prReDenomPro[thetabins];
  TProfile *prImDenomPro[thetabins];
  TProfile *prReNumerPro[thetabins][ncent];
  TProfile *prImNumerPro[thetabins][ncent];

  TProfile *prMultPOI[ncent];
  if (bFirstRun){
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
      prImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
      hGthetaSum[i][j] = new TH1F(Form("hGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
        prImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
        hGthetaProduct[i][j] = new TH1F(Form("hGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
      }
    }
  }}

  else{
  for (int i = 0; i < thetabins; i++)
  {
    prReDenom[i] = new TProfile(Form("prReDenom_theta%i",i),"", ncent, &bin_cent[0]);
    prImDenom[i] = new TProfile(Form("prImDenom_theta%i",i),"", ncent, &bin_cent[0]);

    for (int j = 0; j < ncent; j++)
    {
      prReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j),"", npt, &bin_pT[0]);
      prImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j),"", npt, &bin_pT[0]);
    }
    if (bUseProduct){
    prReDenomPro[i] = new TProfile(Form("prReDenomPro_theta%i",i),"", ncent, &bin_cent[0]);
    prImDenomPro[i] = new TProfile(Form("prImDenomPro_theta%i",i),"", ncent, &bin_cent[0]);

    for (int j = 0; j < ncent; j++)
    {
      prReNumerPro[i][j] = new TProfile(Form("prReNumerPro_theta%i_cent%i", i, j),"", npt, &bin_pT[0]);
      prImNumerPro[i][j] = new TProfile(Form("prImNumerPro_theta%i_cent%i", i, j),"", npt, &bin_pT[0]);
    }
    }

  }

  for (int ic = 0; ic < ncent; ic++)
  {
    prMultPOI[ic] = new TProfile(Form("prMultPOI_cent%i",ic),"", npt, 0, npt);
  }}
  double r[rbins], rSum[rbins];
  if (bFirstRun){
  for (int rbin = 0; rbin < rbins; ++rbin)
  {
    if (bUseProduct) {
      r[rbin] = (double) hGthetaProduct[0][0]->GetBinCenter(rbin+1);
      rSum[rbin] = (double) hGthetaSum[0][0]->GetBinCenter(rbin+1);
    }
    else{rSum[rbin] = (double) hGthetaSum[0][0]->GetBinCenter(rbin+1);}
  }}

  // QC

  // TProfile for reference flow (RF)
  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow (DF)
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
  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv22[icent] = new TProfile(Form("hv22_%i", icent), "", 1, 0., 1.);
    hv24[icent] = new TProfile(Form("hv24_%i", icent), "", 1, 0., 1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i", icent), "", 1, 0., 1.);
    for (int kpt = 0; kpt < npt; kpt++)
    { // loop over pt bin
      hv22pt[icent][kpt] = new TProfile(Form("hv22pt_%i_%i", icent, kpt), "", 1, 0., 1.);
      hv24pt[icent][kpt] = new TProfile(Form("hv24pt_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov22prime[icent][kpt] = new TProfile(Form("hcov22prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov24prime[icent][kpt] = new TProfile(Form("hcov24prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov42prime[icent][kpt] = new TProfile(Form("hcov42prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov44prime[icent][kpt] = new TProfile(Form("hcov44prime_%i_%i", icent, kpt), "", 1, 0., 1.);
      hcov2prime4prime[icent][kpt] = new TProfile(Form("hcov2prime4prime_%i_%i", icent, kpt), "", 1, 0., 1.);
    } // end of loop over pt bin
  } // end of loop over centrality classes

  // cout << "Histograms have been initialized" << endl;

  // Declaration of leaf types
  Int_t nh;
  Float_t b;
  Float_t rp;
  Float_t phi0[max_nh]; //[nh]
  Bool_t bFlow[max_nh]; //[nh]
  Float_t eta[max_nh];  //[nh]
  Float_t pt[max_nh];   //[nh]

  // List of branches
  TBranch *b_nh;    //!
  TBranch *b_b;     //!
  TBranch *b_rp;    //!
  TBranch *b_phi0;  //!
  TBranch *b_bFlow; //!
  TBranch *b_eta;   //!
  TBranch *b_pt;    //!

  TChain *fChain = new TChain("tree");
  if (inputFileName.Contains(".root"))
  {fChain->Add(inputFileName.Data());}
  else
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    while (std::getline(file, line))
    {
      fChain->Add(line.c_str());
    }
  }
  
  if (!fChain)
    return;
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
    if (jentry % 1000 == 0)
      cout << "[" << jentry << "/" << nentries << "]" << endl;
    // if (jentry == 100000) break;  
    fChain->GetEntry(jentry);

    double dCent = CentB(b);
    if (dCent < 0)
      continue;
    int icent = GetCentBin(dCent);
    mult = 0;
    hMult->Fill(nh);
    hRP->Fill(rp);
    hBimp->Fill(b);
    hBimpvsMult->Fill(nh, b);
    double sumQxy[neta][2] = {{0}}; // [eta-,eta+][x,y]
    double multQv[neta] = {0};      // [eta+,eta-]

    for (int i = 0; i < thetabins; ++i)
    {
      Qtheta[i] = 0.;
      cExponent[i] = TComplex(0.0,0.0);
    }
    Q2x = 0.;
    Q2y = 0.;
    if (bFirstRun)
    {
      for (int i = 0; i < rbins; ++i)
      {
        for (int j = 0; j < thetabins; ++j)
        {
          genfunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
          if (bUseProduct) genfunP[i][j] = TComplex::One(); // initialize to 1, calcualte via product
        }
      }
    }
    else{
      
      for (int it = 0; it < thetabins; it++){
        genfunPr0[it] = TComplex::One();
        cdGr0[it] = TComplex(0.0,0.0);
      }
      for (int ipt = 0; ipt < npt; ipt++) multPOI[ipt] = 0.;
    } 

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

    for (int i = 0; i < nh; i++)
    { // track loop
      double pT = pt[i];
      if (pT < minpt || pT > maxpt || eta[i] > eta_cut)
        continue;
      hPt->Fill(pT);
      double phi = phi0[i];
      if (phi < 0)
        phi += 2. * TMath::Pi();
      hPhi->Fill(phi-rp);
      hPhil->Fill(phi);
      hEta->Fill(eta[i]);

      Q2x += TMath::Cos(2.0 * phi);
      Q2y += TMath::Sin(2.0 * phi);
        Int_t ipt = -1;
        for (int j = 0; j < npt; j++) if (pT >= bin_pT[j] && pT < bin_pT[j + 1]) ipt = j;
      if (!bFirstRun)
      {

        multPOI[ipt]++;
      }
      Double_t v2 = TMath::Cos(2 * (phi - rp));

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
      
      if (bFlow[i])
      {
        hv2MC->Fill(dCent, v2);        // calculate reference v2 from MC toy
        hv2MCpt[icent]->Fill(pT, v2); // Calculate differential v2 from MC toy
      }
      // Sub eta event method
      int fEta = -1;
      if (eta[i] < -eta_gap && eta[i] > -eta_cut)
        fEta = 0;
      if (eta[i] > eta_gap && eta[i] < eta_cut)
        fEta = 1;

      if (fEta > -1)
      {
        sumQxy[fEta][0] += pT * TMath::Cos(2.0 * phi);
        sumQxy[fEta][1] += pT * TMath::Sin(2.0 * phi);
        multQv[fEta]++;
      } // end of eta selection
      if (bUseProduct){
        
        if (bFirstRun){
          for (int thetabin = 0; thetabin < thetabins; ++thetabin)
          {
            double dCosTerm = TMath::Cos(2. * (phi - theta[thetabin]));
            for (int rbin = 0; rbin < rbins; ++rbin)
            {
              genfunP[rbin][thetabin] *= TComplex(1.0, r[rbin] * dCosTerm);
            }
          }
        }
        else{
          for (int thetabin = 0; thetabin < thetabins; ++thetabin)
          {
            double dCosTerm = TMath::Cos(2. * (phi - theta[thetabin]));
            genfunPr0[thetabin] *= TComplex(1.0, r02Pro[icent][thetabin] * dCosTerm);
            TComplex cCosTermComplex(1., r02Pro[icent][thetabin] * dCosTerm);
            cdGr0[thetabin] += (dCosTerm/cCosTermComplex); 
          }
        }
      }
      mult++;
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

    if (mult != 0) 
    {
      hMult->Fill(mult);
      if (bFirstRun) {prRefMult->Fill(dCent, mult);}
      else{
        for (int ipt = 0; ipt < npt; ipt++) 
        {prMultPOI[icent]->Fill(ipt+0.5,multPOI[ipt]);}
      }

      double Q2xMean = Q2x / mult;
      double Q2yMean = Q2y / mult;
      for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      {
        Qtheta[thetabin] = Q2xMean * TMath::Cos(2.0 * theta[thetabin]) + Q2yMean * TMath::Sin(2.0 * theta[thetabin]);
      }

      if (bFirstRun)
      {
        prQ2x->Fill(dCent, Q2x);
        prQ2y->Fill(dCent, Q2y);
        prQ2ModSq->Fill(dCent, Q2x*Q2x+Q2y*Q2y);

        for (int rbin = 0; rbin < rbins; rbin++)
        {
          for (int thetabin = 0; thetabin < thetabins; thetabin++)
          {
            cExpo = TComplex(0., rSum[rbin] * Qtheta[thetabin]);
            genfunS[rbin][thetabin] = TComplex::Exp(cExpo); // generating function from Q-vectors
            prReGthetaSum[icent][thetabin]->Fill(rSum[rbin], genfunS[rbin][thetabin].Re());
            prImGthetaSum[icent][thetabin]->Fill(rSum[rbin], genfunS[rbin][thetabin].Im());
            if (bUseProduct)
            {
              prReGthetaProduct[icent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Re());
              prImGthetaProduct[icent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Im());
            }
          }
        }


      }
      else
      {
        // Differential LYZ
        for (int thetabin = 0; thetabin < thetabins; thetabin++)
        {
          cExponent[thetabin] = TComplex(0., r02[icent][thetabin] * Qtheta[thetabin]);
          cDenominator = Qtheta[thetabin]*(TComplex::Exp(cExponent[thetabin])); // BP eq 12
          prReDenom[thetabin]->Fill(dCent, cDenominator.Re());
          prImDenom[thetabin]->Fill(dCent, cDenominator.Im());
        }
        if (bUseProduct)
        {
          for (int thetabin = 0; thetabin < thetabins; thetabin++)
          {
            prReDenomPro[thetabin]->Fill(dCent, (genfunPr0[thetabin] * cdGr0[thetabin]).Re());
            prImDenomPro[thetabin]->Fill(dCent, (genfunPr0[thetabin] * cdGr0[thetabin]).Im());
          }
        }
      }
    } // end of if (mult!=0)

    // Eta sub-event method
    double fEP[2] = {0.}; // [eta-,eta+]
    for (int ieta = 0; ieta < neta; ieta++)
    {
      if (multQv[ieta] > 5)
      { // multiplicity > 5
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
        fEP[ieta] = TMath::ATan2(sin(2.0 * fEP[ieta]), cos(2.0 * fEP[ieta])); // what for?
        fEP[ieta] /= 2.0;
      }
      else
      {
        fEP[ieta] = -9999.;
      }
    }
    if (fEP[0] != -9999. && fEP[1] != -9999.)
    {
      HRes->Fill(dCent, TMath::Cos(2.0 * (fEP[0] - fEP[1])));
    }
    // Estimate the event plane resolution of 2nd harmonic by the correlation between the azimuthal
    // angles of two subset groups of tracks, called sub-events \eta- and \eta+

    if (!bFirstRun){
    for (int itrk = 0; itrk < nh; itrk++)
    { //track loop
      double pT = pt[itrk];
      if (pT < minpt || pT > maxpt || eta[itrk] > eta_cut)
        continue;
      double phi = phi0[itrk];
  
      if (fEP[0] != -9999. && fEP[1] != -9999.)
      {
        float v2 = -999.0;
        if (eta[itrk] > 0)
        { // eta+
          v2 = TMath::Cos(2.0 * (phi - fEP[0])) / res2[icent];
        }
        if (eta[itrk] < 0)
        { // eta-
          v2 = TMath::Cos(2.0 * (phi - fEP[1])) / res2[icent];
        }
        // if(fabs(eta[itrk])<1.0){ // eliminate spectators
        if (v2 != 999.0)
        {
          hv2EPpt[icent]->Fill(pT, v2);
          hv2EP->Fill(dCent, v2);
        }
      }
    
      for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      {
        double dCosTerm = TMath::Cos(2.0 * (phi - theta[thetabin]));
        TComplex cNumeratorPOI = dCosTerm*(TComplex::Exp(cExponent[thetabin]));    
        prReNumer[thetabin][icent]->Fill(pT, cNumeratorPOI.Re());
        prImNumer[thetabin][icent]->Fill(pT, cNumeratorPOI.Im());
        if (bUseProduct){
          TComplex cCosTermComplex(1., r02Pro[icent][thetabin] * dCosTerm);
          TComplex cNumeratorPOIPro = genfunPr0[thetabin] * dCosTerm / cCosTermComplex;   
          prReNumerPro[thetabin][icent]->Fill(pT, cNumeratorPOIPro.Re());
          prImNumerPro[thetabin][icent]->Fill(pT, cNumeratorPOIPro.Im());          
        }
      }
    } // end of the track loop
    }
  }   // end of event loop

  // cout << "double v2EP[9] = {";
  // for (int ic = 0 ; ic < ncent-1; ic++)
  // {
  //   cout << hv2EP->GetBinContent(ic+1) << ", ";
  // }
  // cout << hv2EP->GetBinContent(ncent) << "};" << endl;

  // cout << "double v2eEP[9] = {";
  // for (int ic = 0 ; ic < ncent-1; ic++)
  // {
  //   cout << hv2EP->GetBinError(ic+1) << ", ";
  // }
  // cout << hv2EP->GetBinError(ncent) << "};" << endl;

  // cout << "double v2MC[9] = {";
  // for (int ic = 0 ; ic < ncent-1; ic++)
  // {
  //   cout << hv2MC->GetBinContent(ic+1) << ", ";
  // }
  // cout << hv2MC->GetBinContent(ncent) << "};" << endl;

  // cout << "double v2eMC[9] = {";
  // for (int ic = 0 ; ic < ncent-1; ic++)
  // {
  //   cout << hv2MC->GetBinError(ic+1) << ", ";
  // }
  // cout << hv2MC->GetBinError(ncent) << "};" << endl;

  // //============================================================================================================
  // cout << inputFileName.Data() << " file processed" << endl;
  // cout << "Resolution:" << endl;
  // GetRes(HRes);
  // GetMultMean(prRefMult);
  // double dChi2[ncent];
  // float v2int[ncent]={0.}, v2e[ncent]={0.};
  // double dVtheta[ncent][thetabins] = {0.};
  // cout << "const double r02[ncent][thetabins] = {";
  // for (int ic = 0; ic < ncent; ic++)
  // {
  //   float refmult = prRefMult->GetBinContent(ic+1);
  //   int thetacount = 0;
  //   cout <<"{";
  //   for (int it = 0; it < thetabins; it++)
  //   {
  //     TH1F *hGtheta = NULL;
  //     if (bUseProduct) {hGtheta = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);}
  //     else {hGtheta = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);}
  //     float r0theta = GetR0(hGtheta);
  //     // if (ic == 3 && it == 0) cout << "r0theta = " << r0theta << endl;
  //     // cout << "cent:" << ic <<", theta =" << it << ", r0theta = " << r0theta << endl;
  //     // if (it == 0) cout << rootJ0 <<"/"<< r0theta <<"/"<< refmult << " ";
  //     cout << r0theta << ", ";
  //     if (r0theta!=0) 
  //     {
  //       v2int[ic] += rootJ0 / r0theta;
  //       dVtheta[ic][it] = rootJ0 / r0theta;
  //       thetacount++;
  //     }
  //     // if (ic == 2) cout << rootJ0 / r0theta / refmult<< ", ";
  //   }
  //   cout << "}," << endl;
  //   if (thetacount!=0) v2int[ic] /= (float)thetacount; // refmult
  //   else {v2int[ic]=0.;}
    
  //   // cout << v2int[ic] << " ";
  //   float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
  //   float Q2xmean = prQ2x->GetBinContent(ic+1);
  //   float Q2ymean = prQ2y->GetBinContent(ic+1);
  //   float chi2 = v2int[ic]*refmult/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2));
  //   dChi2[ic] = chi2;
  //   // cout << chi2 << " ";
  //   // if (ic==8) cout << modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2) << endl;
  //   float temp=0.;
  //   for(int it=0; it<thetabins; it++) 
  //     /* Loop over the angles of the interpolation points,     
  //       to compute the statistical error bar on the average estimate V2{infty}, 
  //       with the help of Eqs.(89) of Ref.[A]. */
  //   {    
  //     // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
  //     double arg = theta[it];
  //     temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
  //       BesselJ0(2.*rootJ0*sin(arg/2.))+
  //       exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
  //       BesselJ0(2.*rootJ0*cos(arg/2.));
  //   }
  //   float neve = prRefMult->GetBinEntries(ic+1);
  //   float err2mean = v2int[ic]*sqrt(temp/2./neve/thetabins)/rootJ0/J1rootJ0;
  //   v2e[ic] = err2mean;
  //   // cout << err2mean << ", ";
  // } // end of V2RP calculation
  
  // cout << " };" << endl;
  // cout << "const double chisq[" << ncent << "] = {";
  // for (int ic = 0; ic < ncent-1; ic++)
  // {
  //   cout << dChi2[ic] <<", ";
  // }
  // cout << dChi2[ncent-1] << "};" << endl;



  //   cout << "My flow" << endl;
  //   cout << "double v2MC[9] = {";
  //   for (int ic = 0 ; ic < ncent-1; ic++)
  //   {
  //     cout << hv2MC->GetBinContent(ic+1) << ", ";
  //   }
  //   cout << hv2MC->GetBinContent(ncent) << "};" << endl;

  //   cout << "double v2LYZ[9] = {";
  //   for (int ic = 0 ; ic < ncent-1; ic++)
  //   {
  //     cout << v2int[ic] << ", ";
  //   }
  //   cout << v2int[ncent-1] << "};" << endl;
  //   cout << "double v2eLYZ[9] = {";
  //   for (int ic = 0 ; ic < ncent-1; ic++)
  //   {
  //     cout << v2e[ic] << ", ";
  //   }
  //   cout << v2e[ncent-1] << "};" << endl;


  // TH1F *hLYZ = new TH1F("hLYZ","",ncent,&bin_cent[0]);
  // for (int ic=0; ic<ncent; ic++)
  // {
  //   hLYZ->SetBinContent(ic+1,v2int[ic]);
  //   hLYZ->SetBinError(ic+1,v2e[ic]);
  // }

  // cout << "double v2LYZ[9] = {";
  // for (int ic = 0 ; ic < ncent-1; ic++)
  // {
  //   cout << v2int[ic] << ", ";
  // }
  // cout << v2int[ncent-1] << "};" << endl;
  // cout << "double v2eLYZ[9] = {";
  // for (int ic = 0 ; ic < ncent-1; ic++)
  // {
  //   cout << v2e[ic] << ", ";
  // }
  // cout << v2e[ncent-1] << "};" << endl;
  // // Differential v2 LYZ
  // TComplex cNumeratorPOI;
  // double re, im, reRatio;
  // double v2diff[ncent][npt]={0.};
  // double v2diffe[ncent][npt]={0.};
  // for (int ic = 0; ic < ncent; ic++)
  // {
  //   /* Computation of statistical error bars on the average estimates */
  //   double temp = 0.;
  //   double arg[thetabins];
  //   for(int k1=0; k1<thetabins; k1++)
  //   {
  //     // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
  //     arg[k1] = theta[k1];

  //     /* Loop over the theta angles, to compute the statistical error */
  //     temp += (exp(sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
  //     BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
  //     exp(-sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
  //     BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
  //   }
  //   for (int thetabin = 0; thetabin < thetabins; thetabin++)
  //   {
  //     re = prReDenom[thetabin]->GetBinContent(ic+1);
  //     im = prImDenom[thetabin]->GetBinContent(ic+1);
  //     cDenominator = TComplex(re, im);
  //     if (cDenominator.Rho()==0) {
	//       cerr<<"WARNING: modulus of cDenominator is zero"<<endl;
	//     }
  //     for (int ipt = 0; ipt < npt; ipt++)
  //     {
  //       re = prReNumer[thetabin][ic]->GetBinContent(ipt+1);
  //       im = prImNumer[thetabin][ic]->GetBinContent(ipt+1);
  //       cNumeratorPOI = TComplex(re, im);
  //       if (cDenominator.Rho()!=0) {
  //         reRatio = (cNumeratorPOI/cDenominator).Re();
  //         double dVetaPOI = reRatio * dVtheta[ic][thetabin];
  //         // cout << "reRatio * dVtheta[ic][thetabin] = " << reRatio <<" * "<< dVtheta[ic][thetabin] << endl;
  //         v2diff[ic][ipt] += dVetaPOI;
  //       }

  //     }
  //   }
  //   double neve = prReDenom[0]->GetBinEntries(ic+1);
  //   for (int ipt = 0; ipt < npt; ipt++)
  //   {    
  //     v2diff[ic][ipt] /= thetabins;
  //     double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
  //     v2diffe[ic][ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0;
  //     if (ic == 2) cout << v2diffe[ic][ipt] << ", ";
  //   }

  // }


  // //================= Drawing =========================
  // TCanvas c;

  // hLYZ->SetMarkerStyle(23);
  // hLYZ->SetMarkerColor(kBlue+2);
  // hLYZ->SetLineColor(kBlue+2);

  // hv2EP->SetMarkerStyle(20);
  // hv2EP->SetMarkerColor(kRed+2);
  // hv2EP->SetLineColor(kRed+2);

  // hv2MC->SetMarkerStyle(25);
  // hv2MC->SetMarkerColor(kBlack);
  // hv2MC->SetLineColor(kBlack);
  // hv2MC->SetTitle(";centrality, %;v_{2}");
  // hv2MC->GetYaxis()->SetRangeUser(0,0.1);
  // hv2MC->GetXaxis()->SetLimits(0,60);
  // hv2MC->Draw();
  // hv2EP->Draw("same");
  // hLYZ->Draw("same");
  // TLegend *leg = new TLegend(0.7,0.15,0.85,0.35);
  // leg->SetBorderSize(0);
  // leg->AddEntry(hv2MC,"MC","p");
  // leg->AddEntry(hv2EP,"EP","p");
  // leg->AddEntry(hLYZ,"LYZ","p");
  // leg->Draw();
  // gStyle->SetPadTickX(1);
  // gStyle->SetPadTickY(1);
  // gStyle->SetOptStat(0);
  // c.SaveAs("Flow.pdf");
  // //================= Drawing =========================
  // TCanvas c2;
  // // TPaveLabel* title = new TPaveLabel(0.1,0.95,0.9,0.98,"Toy Model");
  // // title->SetBorderSize(0);
  // // title->SetFillColor(0);
  // // title->SetTextFont(textFont);
  // // title->SetTextSize(2.);
  // // title->Draw();
  // // int centrality = 4; // 10-20%
  // // c2.SetLeftMargin(0.17);
  // TString legHeader[] = {"0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%","60-70%","70-80%"};
  // c2.Divide(3,2,0,0);
  // for (int centrality = 1; centrality < 7; centrality++){
  // c2.cd(centrality);
  // TH1F *hLYZDiff = new TH1F("hLYZDiff","",npt,&bin_pT[0]);
  // for (int ipt=0; ipt<npt; ipt++)
  // {
  //   hLYZDiff->SetBinContent(ipt+1,v2diff[centrality][ipt]);
  //   hLYZDiff->SetBinError(ipt+1,v2diffe[centrality][ipt]);
  // }
  // hLYZDiff->SetMarkerStyle(23);
  // hLYZDiff->SetMarkerColor(kBlue+2);
  // hLYZDiff->SetLineColor(kBlue+2);

  // hv2EPpt[centrality]->SetMarkerStyle(20);
  // hv2EPpt[centrality]->SetMarkerColor(kRed+2);
  // hv2EPpt[centrality]->SetLineColor(kRed+2);

  // hv2MCpt[centrality]->SetMarkerStyle(25);
  // hv2MCpt[centrality]->SetMarkerColor(kBlack);
  // hv2MCpt[centrality]->SetLineColor(kBlack);
  // hv2MCpt[centrality]->SetTitle(";p_{T}, GeV/c;v_{2}");
  // hv2MCpt[centrality]->GetYaxis()->SetRangeUser(0,0.26);
  // hv2MCpt[centrality]->GetXaxis()->SetLimits(-0.05,3.55);
  // hv2MCpt[centrality]->Draw();
  // hv2EPpt[centrality]->Draw("same");
  // hLYZDiff->Draw("P same");
  // TLegend *leg2 = new TLegend(0.15,0.6,0.5,0.85);
  // leg2->SetBorderSize(0);
  // leg2->SetHeader(legHeader[centrality].Data());
  // leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  // leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  // leg2->AddEntry(hLYZDiff,"LYZ","p");
  // // leg2->AddEntry(hLYZ,"LYZ","p");
  // leg2->Draw();
  // // c2.SaveAs(Form("DifFlow_%i.png",centrality));
  // }
  // c2.SaveAs(Form("DifFlow.pdf"));
  // //================= Drawing =========================

  d_outfile->cd();
  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv22[icent]->Write();
    hv24[icent]->Write();
    hcov24[icent] ->Write();
    for (int kpt = 0; kpt < npt; kpt++)
    { // loop over pt bin
      hv22pt[icent][kpt] ->Write();
      hv24pt[icent][kpt] ->Write();
      hcov22prime[icent][kpt]->Write();
      hcov24prime[icent][kpt]->Write();
      hcov42prime[icent][kpt]->Write();
      hcov44prime[icent][kpt]->Write();
      hcov2prime4prime[icent][kpt]->Write();
    } // end of loop over pt bin
  } // end of loop over centrality classes

  if (bFirstRun)
  {
    hMult->Write();
    hBimp->Write();
    hPt->Write();
    hPhi->Write();
    hEta->Write();
    hv2MC->Write();
    HRes->Write();
    prRefMult->Write();
    prQ2x->Write();
    prQ2y->Write();
    prQ2ModSq->Write();
    for (int i = 0; i < ncent; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        prReGthetaSum[i][j]->Write();
        prImGthetaSum[i][j]->Write();
        if (bUseProduct)
        {
          prReGthetaProduct[i][j]->Write();
          prImGthetaProduct[i][j]->Write();
        }
      }
    }
  }
  else
  {
    hv2EP->Write();
    for (int j = 0; j < thetabins; ++j)
    {
      prReDenom[j]->Write();
      prImDenom[j]->Write();
      for (int i = 0; i < ncent; i++)
      {
        prReNumer[j][i]->Write();
        prImNumer[j][i]->Write();
      }
      if (bUseProduct){
        prReDenomPro[j]->Write();
        prImDenomPro[j]->Write();
        for (int i = 0; i < ncent; i++)
        {
          prReNumerPro[j][i]->Write();
          prImNumerPro[j][i]->Write();
        }
      }
    }
    for (int ic = 0; ic < ncent; ic++)
    {
      prMultPOI[ic]->Write();
      hv2EPpt[ic]->Write();
      hv2MCpt[ic]->Write();
    }
  }
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

