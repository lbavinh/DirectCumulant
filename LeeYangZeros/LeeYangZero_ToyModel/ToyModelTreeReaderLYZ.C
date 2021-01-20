#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include <TLegend.h>
#include <iostream>

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
  for (int i=0; i<pr->GetNbinsX(); i++)
  {
    cout << TMath::Sqrt(pr->GetBinContent(i+1)) <<", ";
  }
  cout <<"};" << endl;
}

void GetMultMean(TProfile *const &pr)
{
  cout << "const double dMultMean[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX(); i++)
  {
    cout << (pr->GetBinContent(i+1)) <<", ";
  }
  cout <<"};" << endl;
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

void ToyModelTreeReaderLYZ(TString file = "ToyModel.root", TString outFile = "LYZ.root")
{
  bool bUseProduct = 0; 
  const int ncent = 9; // 0-80%
  const double res2[ncent] = {0.574529, 0.716237, 0.815169, 0.852812, 0.849012, 0.814938, 0.745442, 0.620791, 0.49103};
  // const double dMultMean[ncent] = {3866.61, 3225.48, 2453.03, 1680.19, 1130.98, 734.467, 446.53, 253.215, 130.785};
  const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};

  const double maxpt = 3.5; // max pt
  const double minpt = 0.2; // min pt
  const double eta_cut = 2.0;
  const double eta_gap = 0.05;
  const int npt = 12; // 0.2 - 3.5 GeV/c
  const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  const int neta = 2; // [eta-,eta+]
  const int max_nh = 6000;

  // LYZ
  const int rbins = 100;
  const double rMax = 0.5;
  const double rMin = 0.005;
  const double rMaxSum = 0.5;
  const double rMinSum = 0.005;
  const int thetabins = 5;
  const double rootJ0 = 2.4048256;
  const double J1rootJ0 = 0.519147;
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }

  double Qtheta[thetabins];
  TComplex genfunS[rbins][thetabins]; // sum
  TComplex genfunP[rbins][thetabins]; // product
  TComplex cExpo;
  double Q2x, Q2y;
  int mult;
  // Differential LYZ
  const double r02[ncent][thetabins] = {{0.0394293, 0.0612411, 0.0567886, 0.0387612, 0.0393322},
                                        {0.032696, 0.0333119, 0.0339629, 0.0338644, 0.0323053},
                                        {0.0294134, 0.0292616, 0.0293481, 0.0295598, 0.0294885},
                                        {0.0323116, 0.0324761, 0.0320185, 0.0318262, 0.0319852},
                                        {0.0386181, 0.0390448, 0.038841, 0.0386988, 0.0386965},
                                        {0.0537552, 0.0529162, 0.0527976, 0.0533032, 0.0536851},
                                        {0.0831727, 0.0836059, 0.0846148, 0.0839589, 0.0838692},
                                        {0.156505, 0.168634, 0.177089, 0.165882, 0.186232},
                                        {0.425309, 0.379876, 0.357246, 0.434813, 0.367741}};
  // const double chisq[9] = {0.771347, 1.16186, 1.5572, 1.58317, 1.62168, 1.43933, 1.14193, 0.701679, 0.442298};
  double multPOI[npt];
  // TComplex g2r0[thetabins];   
  // TComplex dlng2_dz[thetabins], dG2_dz[thetabins];
  // TComplex dlng2_dw2[thetabins][npt], dG2_dw2[thetabins][npt]; 
  TComplex cDenominator;
  TComplex cExponent[thetabins];
  TFile *d_outfile = new TFile(outFile.Data(), "recreate");

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


  TProfile *prRefMult = new TProfile("prRefMult","",ncent,0,ncent);
  TProfile *prQ2x = new TProfile("prQ2x","",ncent,0,ncent);
  TProfile *prQ2y = new TProfile("prQ2y","",ncent,0,ncent);
  TProfile *prQ2ModSq = new TProfile("prQ2ModSq","",ncent,0,ncent);
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
  }
  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];
  for (int i = 0; i < thetabins; i++)
  {
    prReDenom[i] = new TProfile(Form("prReDenom_theta%i",i),"", ncent, &bin_cent[0]);
    prImDenom[i] = new TProfile(Form("prImDenom_theta%i",i),"", ncent, &bin_cent[0]);

    for (int j = 0; j < ncent; j++)
    {
      prReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j),"", npt, &bin_pT[0]);
      prImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j),"", npt, &bin_pT[0]);
    }
  }
  TProfile *prMultPOI[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    prMultPOI[ic] = new TProfile(Form("prMultPOI_cent%i",ic),"", npt, 0, npt);
  }
  double r[rbins], rSum[rbins];
  for (int rbin = 0; rbin < rbins; ++rbin)
  {
    if (bUseProduct) {r[rbin] = (double) hGthetaProduct[0][0]->GetBinCenter(rbin+1);}
    else{rSum[rbin] = (double) hGthetaSum[0][0]->GetBinCenter(rbin+1);}
  }

  // cout << "Histograms have been initialized" << endl;

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

  TChain *fChain = new TChain("tree");
  fChain->Add(file.Data());
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
    if (jentry % 10000 == 0)
      cout << jentry << endl;
    fChain->GetEntry(jentry);

    double cent = CentB(b);
    if (cent < 0)
      continue;
    int icent = GetCentBin(cent);
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
    for (int i = 0; i < rbins; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        genfunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
        if (bUseProduct) genfunP[i][j] = TComplex::One(); // initialize to 1, calcualte via product
      }
    }
    Q2x = 0.;
    Q2y = 0.;
    for (int ipt = 0; ipt < npt; ipt++) multPOI[ipt] = 0.;
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
      for (int j = 0; j < npt; j++)
        if (pT >= bin_pT[j] && pT < bin_pT[j + 1])
          ipt = j;
    

      multPOI[ipt]++;
      Double_t v2 = TMath::Cos(2 * (phi - rp));

      
      if (bFlow[i])
      {
        hv2MC->Fill(cent, v2);        // calculate reference v2 from MC toy
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
      if (bUseProduct)
      {
        for (int rbin = 0; rbin < rbins; ++rbin)
        {
          for (int thetabin = 0; thetabin < thetabins; ++thetabin)
          {
            genfunP[rbin][thetabin] *= TComplex(1.0, r[rbin] * TMath::Cos(2. * (phi - theta[thetabin])));
          }
        }
      }

      mult++;

    } // end of track loop


    if (mult != 0) 
    {
      hMult->Fill(mult);
      prRefMult->Fill(icent, mult);
      for (int ipt = 0; ipt < npt; ipt++) 
      {prMultPOI[icent]->Fill(ipt+0.5,multPOI[ipt]);}
      // Q2x /= (double) mult;
      // Q2y /= (double) mult;

      prQ2x->Fill(icent, Q2x);
      prQ2y->Fill(icent, Q2y);
      prQ2ModSq->Fill(icent, Q2x*Q2x+Q2y*Q2y);


      for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      {
        Qtheta[thetabin] = Q2x * TMath::Cos(2.0 * theta[thetabin]) + Q2y * TMath::Sin(2.0 * theta[thetabin]);
      }

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
      // Differential LYZ
      for (int thetabin = 0; thetabin < thetabins; thetabin++)
      {
        cExponent[thetabin] = TComplex(0., r02[icent][thetabin] * Qtheta[thetabin]);
        cDenominator = Qtheta[thetabin]*(TComplex::Exp(cExponent[thetabin])); // BP eq 12
        prReDenom[thetabin]->Fill(cent, cDenominator.Re());
        prImDenom[thetabin]->Fill(cent, cDenominator.Im());
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
      HRes->Fill(cent, TMath::Cos(2.0 * (fEP[0] - fEP[1])));
    }
    // Estimate the event plane resolution of 2nd harmonic by the correlation between the azimuthal
    // angles of two subset groups of tracks, called sub-events \eta- and \eta+


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
          hv2EP->Fill(cent, v2);
        }
      }
      
      // if (mult != 0)
      // {
        for (int thetabin = 0; thetabin < thetabins; ++thetabin)
        {
          TComplex cNumeratorPOI = TMath::Cos(2.0 * (phi - theta[thetabin]))*(TComplex::Exp(cExponent[thetabin]));    
          prReNumer[thetabin][icent]->Fill(pT, cNumeratorPOI.Re());
          prImNumer[thetabin][icent]->Fill(pT, cNumeratorPOI.Im());
        }
      // }
    } // end of the track loop
  }   // end of event loop




  //============================================================================================================
  cout << file << " file processed" << endl;
  cout << "Resolution:" << endl;
  GetRes(HRes);
  GetMultMean(prRefMult);
  double dChi2[ncent];
  float v2int[ncent]={0.}, v2e[ncent]={0.};
  double dVtheta[ncent][thetabins] = {0.};
  cout << "const double r02[ncent][thetabins] = {";
  for (int ic = 0; ic < ncent; ic++)
  {
    float refmult = prRefMult->GetBinContent(ic+1);
    int thetacount = 0;
    cout <<"{";
    for (int it = 0; it < thetabins; it++)
    {
      TH1F *hGtheta = NULL;
      if (bUseProduct) {hGtheta = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);}
      else {hGtheta = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);}
      float r0theta = GetR0(hGtheta);
      // if (ic == 3 && it == 0) cout << "r0theta = " << r0theta << endl;
      // cout << "cent:" << ic <<", theta =" << it << ", r0theta = " << r0theta << endl;
      // if (it == 0) cout << rootJ0 <<"/"<< r0theta <<"/"<< refmult << " ";
      cout << r0theta << ", ";
      if (r0theta!=0) 
      {
        v2int[ic] += rootJ0 / r0theta;
        dVtheta[ic][it] = rootJ0 / r0theta;
        thetacount++;
      }
      // if (ic == 2) cout << rootJ0 / r0theta / refmult<< ", ";
    }
    cout << "}," << endl;
    if (thetacount!=0) v2int[ic] /= (float)thetacount*refmult;
    else {v2int[ic]=0.;}
    
    // cout << v2int[ic] << " ";
    float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
    float Q2xmean = prQ2x->GetBinContent(ic+1);
    float Q2ymean = prQ2y->GetBinContent(ic+1);
    float chi2 = v2int[ic]*refmult/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2));
    dChi2[ic] = chi2;
    // cout << chi2 << " ";
    // if (ic==8) cout << modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2) << endl;
    float temp=0.;
    for(int it=0; it<thetabins; it++) 
      /* Loop over the angles of the interpolation points,     
        to compute the statistical error bar on the average estimate V2{infty}, 
        with the help of Eqs.(89) of Ref.[A]. */
    {    
      // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
      double arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    float neve = prRefMult->GetBinEntries(ic+1);
    float err2mean = v2int[ic]*sqrt(temp/2./neve/thetabins)/rootJ0/J1rootJ0;
    v2e[ic] = err2mean;
    // cout << err2mean << ", ";
  } // end of V2RP calculation
  
  cout << " };" << endl;
  // cout << "const double chisq[" << ncent << "] = {";
  // for (int ic = 0; ic < ncent-1; ic++)
  // {
  //   cout << dChi2[ic] <<", ";
  // }
  // cout << dChi2[ncent-1] << "};" << endl;
  cout << "My flow" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << v2int[ic] << ", " << hv2MC->GetBinContent(ic+1) << endl;
  }
  TH1F *hLYZ = new TH1F("hLYZ","",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hLYZ->SetBinContent(ic+1,v2int[ic]);
    hLYZ->SetBinError(ic+1,v2e[ic]);
  }

  
  // Differential v2 LYZ
  TComplex cNumeratorPOI;
  double re, im, reRatio;
  double v2diff[ncent][npt]={0.};
  double v2diffe[ncent][npt]={0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    /* Computation of statistical error bars on the average estimates */
    double temp = 0.;
    double arg[thetabins];
    for(int k1=0; k1<thetabins; k1++)
    {
      // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
      arg[k1] = theta[k1];

      /* Loop over the theta angles, to compute the statistical error */
      temp += (exp(sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
      exp(-sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
    }
    for (int thetabin = 0; thetabin < thetabins; thetabin++)
    {
      re = prReDenom[thetabin]->GetBinContent(ic+1);
      im = prImDenom[thetabin]->GetBinContent(ic+1);
      cDenominator = TComplex(re, im);
      if (cDenominator.Rho()==0) {
	      cerr<<"WARNING: modulus of cDenominator is zero"<<endl;
	    }
      for (int ipt = 0; ipt < npt; ipt++)
      {
        re = prReNumer[thetabin][ic]->GetBinContent(ipt+1);
        im = prImNumer[thetabin][ic]->GetBinContent(ipt+1);
        cNumeratorPOI = TComplex(re, im);
        if (cDenominator.Rho()!=0) {
          reRatio = (cNumeratorPOI/cDenominator).Re();
          double dVetaPOI = reRatio * dVtheta[ic][thetabin];
          // cout << "reRatio * dVtheta[ic][thetabin] = " << reRatio <<" * "<< dVtheta[ic][thetabin] << endl;
          v2diff[ic][ipt] += dVetaPOI;
        }

      }
    }
    double neve = prReDenom[0]->GetBinEntries(ic+1);
    for (int ipt = 0; ipt < npt; ipt++)
    {    
      v2diff[ic][ipt] /= thetabins;
      double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
      v2diffe[ic][ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0;
      if (ic == 2) cout << v2diffe[ic][ipt] << ", ";
    }

  }


  //================= Drawing =========================
  TCanvas c;

  hLYZ->SetMarkerStyle(23);
  hLYZ->SetMarkerColor(kBlue+2);
  hLYZ->SetLineColor(kBlue+2);

  hv2EP->SetMarkerStyle(20);
  hv2EP->SetMarkerColor(kRed+2);
  hv2EP->SetLineColor(kRed+2);

  hv2MC->SetMarkerStyle(25);
  hv2MC->SetMarkerColor(kBlack);
  hv2MC->SetLineColor(kBlack);
  hv2MC->SetTitle(";centrality, %;v_{2}");
  hv2MC->GetYaxis()->SetRangeUser(0,0.1);
  hv2MC->GetXaxis()->SetLimits(0,60);
  hv2MC->Draw();
  hv2EP->Draw("same");
  hLYZ->Draw("same");
  TLegend *leg = new TLegend(0.7,0.15,0.85,0.35);
  leg->SetBorderSize(0);
  leg->AddEntry(hv2MC,"MC","p");
  leg->AddEntry(hv2EP,"EP","p");
  leg->AddEntry(hLYZ,"LYZ","p");
  leg->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  c.SaveAs("Flow.pdf");
  //================= Drawing =========================
  TCanvas c2;
  // TPaveLabel* title = new TPaveLabel(0.1,0.95,0.9,0.98,"Toy Model");
  // title->SetBorderSize(0);
  // title->SetFillColor(0);
  // title->SetTextFont(textFont);
  // title->SetTextSize(2.);
  // title->Draw();
  // int centrality = 4; // 10-20%
  // c2.SetLeftMargin(0.17);
  TString legHeader[] = {"0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%","60-70%","70-80%"};
  c2.Divide(3,2,0,0);
  for (int centrality = 1; centrality < 7; centrality++){
  c2.cd(centrality);
  TH1F *hLYZDiff = new TH1F("hLYZDiff","",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiff->SetBinContent(ipt+1,v2diff[centrality][ipt]);
    hLYZDiff->SetBinError(ipt+1,v2diffe[centrality][ipt]);
  }
  hLYZDiff->SetMarkerStyle(23);
  hLYZDiff->SetMarkerColor(kBlue+2);
  hLYZDiff->SetLineColor(kBlue+2);

  hv2EPpt[centrality]->SetMarkerStyle(20);
  hv2EPpt[centrality]->SetMarkerColor(kRed+2);
  hv2EPpt[centrality]->SetLineColor(kRed+2);

  hv2MCpt[centrality]->SetMarkerStyle(25);
  hv2MCpt[centrality]->SetMarkerColor(kBlack);
  hv2MCpt[centrality]->SetLineColor(kBlack);
  hv2MCpt[centrality]->SetTitle(";p_{T}, GeV/c;v_{2}");
  hv2MCpt[centrality]->GetYaxis()->SetRangeUser(0,0.26);
  hv2MCpt[centrality]->GetXaxis()->SetLimits(-0.05,3.55);
  hv2MCpt[centrality]->Draw();
  hv2EPpt[centrality]->Draw("same");
  hLYZDiff->Draw("P same");
  TLegend *leg2 = new TLegend(0.15,0.6,0.5,0.85);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[centrality].Data());
  leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ","p");
  // leg2->AddEntry(hLYZ,"LYZ","p");
  leg2->Draw();
  // c2.SaveAs(Form("DifFlow_%i.png",centrality));
  }
  c2.SaveAs(Form("DifFlow.pdf"));
  //================= Drawing =========================

  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

