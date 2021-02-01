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
// #include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
float CentB(float bimp);
int GetCentBin(float cent);
// using namespace std;
using std::cerr;
using std::cout;
using std::endl;

#define MAX_TRACKS 10000

// Constant declaration
// const int npid = 8;  // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
const int ncent = 9; // 0-80%
const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
  const int npt = 12; // 0.2 - 3.5 GeV/c
  const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  const double maxpt = 3.5; // max pt
  const double minpt = 0.2; // min pt
const double maxptRF = 3.;
const double minptRF = 0.2;
const float eta_cut = 2.0;
const float eta_gap = 0;
const int neta = 2; // [eta-,eta+]

// LYZ
const int rbins = 2500;
const double rMax = 0.5;
const double rMin = 0.005;
const double rMaxSum = 0.5;
const double rMinSum = 0.005;
const int thetabins = 10;

class CQVector
{
public:
  CQVector();
  virtual ~CQVector(){};
  void Reset();
  void CalQVector(double phi);
  double X() { return this->fQx; }
  double Y() { return this->fQy; }

private:
  double fQx;
  double fQy;
};
CQVector::CQVector() : fQx(0), fQy(0) {}
void CQVector::Reset()
{
  fQx = 0.;
  fQy = 0.;
}
void CQVector::CalQVector(double phi)
{
  fQx += TMath::Cos(2.0 * phi);
  fQy += TMath::Sin(2.0 * phi);
}

class CGtheta
{
public:
  CGtheta(bool bFirstRun, bool bUseProduct);
  virtual ~CGtheta() {}
  void SetDebugFlag(bool bDebug) {this->fDebug = bDebug;}
  void SetUseProduct(bool kt) { this->fUseProduct = kt; }
  bool GetUseProduct() const { return this->fUseProduct; }
  // TH1F* GetHistGthetaSum() const { return this->fHistGthetaSum[0][0]; }
  // TH1F* GetHistGthetaProduct() const { return this->fHistGthetaProduct[0][0]; }
  void FillHistGF(int icent, CQVector *Q);
  void SaveHist();

  void Reset(); // Set GFPro to 1, GFSum and Qtheta to 0
  void CalQtheta(CQVector *Q);
  void CalGFProduct(double phi, int icent);
  void CalGFSum();

  void ProcessRootFileWithHistFromFirstRun(TString inputFileNameFromFirstRun);
  TH1F *FillHistGtheta(TProfile *const &prReGtheta, TProfile *const &prImGtheta);
  double GetR0(TH1F *const &hist);
  void CalMult();
  void CalMult(double pt);
  double GetMult() const { return this->fMult; }
  void CalDenominatorPOI(int icent);
  void CalNumeratorPOI(int icent, double phi, double pt);

private:
  bool fDebug;
  bool fUseProduct;
  bool fFirstRun;
  double fTheta[thetabins];
  double fQtheta[thetabins];

  // First run
  TProfile *fPrReGthetaSum[ncent][thetabins];
  TProfile *fPrImGthetaSum[ncent][thetabins];
  TH1F *fHistGthetaSum;

  TProfile *fPrReGthetaProduct[ncent][thetabins];
  TProfile *fPrImGthetaProduct[ncent][thetabins];
  TH1F *fHistGthetaProduct;

  double fRSum[rbins];
  double fRProduct[rbins];
  double fMult;
  TComplex fGenFunS[rbins][thetabins]; // sum
  TComplex fGenFunP[rbins][thetabins]; // product

  TProfile *prRefMult;
  TProfile *prQ2x;
  TProfile *prQ2y;
  TProfile *prQ2ModSq;

  // Second run
  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];
  TProfile *prMultPOI[ncent];
  TProfile *prReDenomPro[thetabins];
  TProfile *prImDenomPro[thetabins];
  TProfile *prReNumerPro[thetabins][ncent];
  TProfile *prImNumerPro[thetabins][ncent];
  double fMultPOI[npt];
  TComplex fExponent[thetabins];
  TComplex fdGr0[thetabins];
  TComplex fGenfunPror0[thetabins];
  double fR02Sum[ncent][thetabins];
  double fR02Pro[ncent][thetabins];
};

void CGtheta::CalNumeratorPOI(int icent, double phi, double pt)
{
  for (int it = 0; it < thetabins; ++it)
  {
    double dCosTerm = TMath::Cos(2.0 * (phi - fTheta[it]));
    TComplex cNumeratorPOI = dCosTerm * (TComplex::Exp(fExponent[it]));
    prReNumer[it][icent]->Fill(pt, cNumeratorPOI.Re());
    prImNumer[it][icent]->Fill(pt, cNumeratorPOI.Im());
    if (fUseProduct){
      TComplex cCosTermComplex(1., fR02Pro[icent][it] * dCosTerm);
      TComplex cNumeratorPOIPro = fGenfunPror0[it] * dCosTerm / cCosTermComplex;   
      prReNumerPro[it][icent]->Fill(pt, cNumeratorPOIPro.Re());
      prImNumerPro[it][icent]->Fill(pt, cNumeratorPOIPro.Im());          
    }
  }
}

void CGtheta::CalMult()
{
  fMult++;
}

void CGtheta::CalMult(double pt)
{
  Int_t ipt = -1;
  for (int j = 0; j < npt; j++)
    if (pt >= bin_pT[j] && pt < bin_pT[j + 1])
      ipt = j;
  fMultPOI[ipt]++;
}

void CGtheta::CalDenominatorPOI(int icent)
{
  for (int ipt = 0; ipt < npt; ipt++)
  {
    prMultPOI[icent]->Fill(ipt + 0.5, fMultPOI[ipt]);
  }
  // Differential LYZ

  for (int it = 0; it < thetabins; it++)
  {

    fExponent[it] = TComplex(0., fR02Sum[icent][it] * fQtheta[it]);
    TComplex cDenominator = fQtheta[it] * (TComplex::Exp(fExponent[it])); // BP eq 12

    prReDenom[it]->Fill(icent, cDenominator.Re());
    prImDenom[it]->Fill(icent, cDenominator.Im());
  }
  if (fUseProduct)
  {
    for (int it = 0; it < thetabins; it++)
    {
      TComplex cDenominator = (fGenfunPror0[it] * fdGr0[it]);
      prReDenomPro[it]->Fill(icent, cDenominator.Re());
      prImDenomPro[it]->Fill(icent, cDenominator.Im());
    }
  }  
}

CGtheta::CGtheta(bool bFirstRun, bool bUseProduct) : fFirstRun(bFirstRun), fUseProduct(bUseProduct), fDebug(0)
{
  for (int itheta = 0; itheta < thetabins; itheta++)
  {
    fTheta[itheta] = itheta * TMath::Pi() / (2.0 * thetabins);
  }
  if (fFirstRun)
  {
    fHistGthetaSum = new TH1F(Form("hGthetaSum"), "", rbins, rMinSum, rMaxSum);
    if (fUseProduct) fHistGthetaProduct = new TH1F(Form("hGthetaProduct"), "", rbins, rMin, rMax);
    for (int i = 0; i < ncent; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        fPrReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
        fPrImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
        
        if (fUseProduct)
        {
          fPrReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
          fPrImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
          
        }
      }
    }

    prRefMult = new TProfile("prRefMult", "", ncent, 0, ncent);
    prQ2x = new TProfile("prQ2x", "", ncent, 0, ncent);
    prQ2y = new TProfile("prQ2y", "", ncent, 0, ncent);
    prQ2ModSq = new TProfile("prQ2ModSq", "", ncent, 0, ncent);

    for (int rbin = 0; rbin < rbins; ++rbin)
    {
      if (fUseProduct)
        {fRProduct[rbin] = fHistGthetaProduct->GetBinCenter(rbin + 1);}
      fRSum[rbin] = fHistGthetaSum->GetBinCenter(rbin + 1);
      // cout << r[rbin] << " ";
    }
  }
  else
  {
    for (int i = 0; i < thetabins; i++)
    {
      prReDenom[i] = new TProfile(Form("prReDenom_theta%i", i), "", ncent, 0, ncent);
      prImDenom[i] = new TProfile(Form("prImDenom_theta%i", i), "", ncent, 0, ncent);

      for (int j = 0; j < ncent; j++)
      {
        prReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j), "", npt, &bin_pT[0]);
        prImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j), "", npt, &bin_pT[0]);
      }
    }
    if (fUseProduct)
    {
      for (int i = 0; i < thetabins; i++)
      {
        prReDenomPro[i] = new TProfile(Form("prReDenomPro_theta%i", i), "", ncent, 0, ncent);
        prImDenomPro[i] = new TProfile(Form("prImDenomPro_theta%i", i), "", ncent, 0, ncent);

        for (int j = 0; j < ncent; j++)
        {
          prReNumerPro[i][j] = new TProfile(Form("prReNumerPro_theta%i_cent%i", i, j), "", npt, &bin_pT[0]);
          prImNumerPro[i][j] = new TProfile(Form("prImNumerPro_theta%i_cent%i", i, j), "", npt, &bin_pT[0]);
        }
      }
    }
    for (int ic = 0; ic < ncent; ic++)
    {
      prMultPOI[ic] = new TProfile(Form("prMultPOI_cent%i", ic), "", npt, 0, npt);
    }
  }
}
void CGtheta::FillHistGF(int icent, CQVector *Q)
{
  for (int rbin = 0; rbin < rbins; rbin++)
  {
    for (int it = 0; it < thetabins; it++)
    {
      fPrReGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Re(), fMult);
      fPrImGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Im(), fMult);
    }
  }
  double Qx = Q->X();
  double Qy = Q->Y();
  double QModSq = Qx * Qx + Qy * Qy;
  prRefMult->Fill(icent, fMult);
  prQ2x->Fill(icent, Qx);
  prQ2y->Fill(icent, Qy);
  prQ2ModSq->Fill(icent, QModSq);
  if (fUseProduct){
  for (int rbin = 0; rbin < rbins; rbin++){
    for (int it = 0; it < thetabins; it++){
      fPrReGthetaProduct[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Re(), fMult);
      fPrImGthetaProduct[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Im(), fMult);
  }}}

}

void CGtheta::ProcessRootFileWithHistFromFirstRun(TString inputFileNameFromFirstRun)
{
  TFile *fileHist = new TFile(inputFileNameFromFirstRun.Data(), "read");
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];

  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile *)fileHist->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile *)fileHist->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      if (fUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile *)fileHist->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile *)fileHist->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int it = 0; it < thetabins; it++)
    {
      TH1F *hGthetaSum = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      fR02Sum[ic][it] = GetR0(hGthetaSum);
      if (fUseProduct)
      {
        TH1F *hGthetaPro = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);
        fR02Pro[ic][it] = GetR0(hGthetaPro);
      }
    }
  }
  if (fDebug)
  {
    cout << "Value of r02 from first run are:" << endl;
    cout << "fR02Sum = " << endl;
    for (int ic = 0; ic < ncent; ic++)
    {
      cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic+1] << "%: ";
      for (int it = 0; it < thetabins; it++)
      {
        cout << fR02Sum[ic][it] << ", ";
      }
      cout << endl;
    }
    cout << "fR02Pro = " << endl;
    for (int ic = 0; ic < ncent; ic++)
    {
      cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic+1] << "%: ";
      for (int it = 0; it < thetabins; it++)
      {
        cout << fR02Pro[ic][it] << ", ";
      }
      cout << endl;
    }    
  }
}

TH1F *CGtheta::FillHistGtheta(TProfile *const &prReGtheta, TProfile *const &prImGtheta)
{
  Int_t iNbins = prReGtheta->GetNbinsX();
  Double_t xMin = prReGtheta->GetXaxis()->GetBinLowEdge(1);
  Double_t xMax = prReGtheta->GetXaxis()->GetBinLowEdge(iNbins) + prReGtheta->GetXaxis()->GetBinWidth(iNbins);
  TH1F *hGtheta = new TH1F(Form("hist_%s", prReGtheta->GetName()), "", iNbins, xMin, xMax);
  for (int rbin = 0; rbin < iNbins; rbin++)
  {
    // get bincentre of bins in histogram
    Double_t dRe = prReGtheta->GetBinContent(rbin + 1);
    Double_t dIm = prImGtheta->GetBinContent(rbin + 1);
    TComplex cGtheta(dRe, dIm);
    //fill fHistGtheta with the modulus squared of cGtheta
    //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
    if (cGtheta.Rho2() > 3.)
      hGtheta->SetBinContent(rbin + 1, 0);
    else
      hGtheta->SetBinContent(rbin + 1, cGtheta.Rho2());
    // hGtheta->SetBinContent(rbin+1,cGtheta.Rho2());
    hGtheta->SetBinError(rbin + 1, 0.0);
  }
  return hGtheta;
}

double CGtheta::GetR0(TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of Gtheta

  int iNbins = hist->GetNbinsX();
  double dR0 = 0.;

  for (int b = 2; b < iNbins; b++)
  {
    double dG0 = hist->GetBinContent(b);
    double dGnext = hist->GetBinContent(b + 1);
    double dGnextnext = hist->GetBinContent(b + 2);
    // cout << hist->GetBinCenter(b);
    if (dGnext > dG0 && dGnextnext > dG0 && dG0 < 1.)
    {
      double dGlast = hist->GetBinContent(b - 1);
      double dXlast = hist->GetBinCenter(b - 1);
      double dX0 = hist->GetBinCenter(b);
      double dXnext = hist->GetBinCenter(b + 1);

      dR0 = dX0 - ((dX0 - dXlast) * (dX0 - dXlast) * (dG0 - dGnext) - (dX0 - dXnext) * (dX0 - dXnext) * (dG0 - dGlast)) /
                      (2. * ((dX0 - dXlast) * (dG0 - dGnext) - (dX0 - dXnext) * (dG0 - dGlast))); //parabolic interpolated minimum
      break;                                                                                      //stop loop if minimum is found
    }                                                                                             //if

  } //b

  return dR0;
}



void CGtheta::SaveHist()
{
  if (fFirstRun){
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      fPrReGthetaSum[i][j]->Write();
      fPrImGthetaSum[i][j]->Write();
      if (fUseProduct)
      {
        fPrReGthetaProduct[i][j]->Write();
        fPrImGthetaProduct[i][j]->Write();
      }
    }
  }
  prRefMult->Write();
  prQ2x->Write();
  prQ2y->Write();
  prQ2ModSq->Write();
  }else{
    for (int j = 0; j < thetabins; ++j)
    {
      prReDenom[j]->Write();
      prImDenom[j]->Write();
      for (int i = 0; i < ncent; i++)
      {
        prReNumer[j][i]->Write();
        prImNumer[j][i]->Write();
      }
      if (fUseProduct){
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
    }
  }
}

void CGtheta::Reset()
{
  fMult = 0.;
  for (int i = 0; i < thetabins; ++i)
  {
    fQtheta[i] = 0.;
  }
  if (fFirstRun)
  {
    for (int i = 0; i < rbins; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        fGenFunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
        if (fUseProduct)
        {
          fGenFunP[i][j] = TComplex::One();
        } // initialize to 1, calcualte via product
      }
    }
  }
  else
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      fMultPOI[ipt] = 0.;
    }
    for (int it = 0; it < thetabins; it++)
    {
      fExponent[it] = TComplex(0.0, 0.0);
      fdGr0[it] = TComplex(0.0, 0.0);
      fGenfunPror0[it] = TComplex::One();
    }
  }
}
void CGtheta::CalQtheta(CQVector *Q)
{
  for (int itheta = 0; itheta < thetabins; itheta++)
  {
    fQtheta[itheta] = Q->X() * TMath::Cos(2.0 * fTheta[itheta]) + Q->Y() * TMath::Sin(2.0 * fTheta[itheta]);
  }
}

void CGtheta::CalGFProduct(double phi, int icent)
{
  if (fFirstRun){
  for (int it = 0; it < thetabins; ++it)
  {
    double dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
    for (int rbin = 0; rbin < rbins; ++rbin)
    {
      fGenFunP[rbin][it] *= TComplex(1.0, fRProduct[rbin] * dCosTerm);
    }
  }}
  else{
    for (int it = 0; it < thetabins; ++it)
    {
      double dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
      fGenfunPror0[it] *= TComplex(1.0, fR02Pro[icent][it] * dCosTerm);
      TComplex cCosTermComplex(1., fR02Pro[icent][it] * dCosTerm);
      fdGr0[it] += (dCosTerm/cCosTermComplex);
    }    
  }
}
void CGtheta::CalGFSum()
{
  for (int rbin = 0; rbin < rbins; rbin++)
  {
    for (int it = 0; it < thetabins; it++)
    {
      TComplex cExpo = TComplex(0., fRSum[rbin] * fQtheta[it]);
      fGenFunS[rbin][it] = TComplex::Exp(cExpo); // generating function from Q-vectors
    }
  }
}

void ToyModelTreeReaderLYZ(TString inputFileName, TString outputFileName, TString inputFileHistFromFirstRun = "", Bool_t bFirstRun = 1)
{
  TStopwatch timer;
  timer.Start();

  TChain *chain = new TChain("tree");
  if (inputFileName.Contains(".root"))
  {chain->Add(inputFileName.Data());}
  else
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    while (std::getline(file, line))
    {
      chain->Add(line.c_str());
    }
  }
  
  if (!chain)
    return;

  // Declaration of leaf types
  Int_t nh;
  Float_t bimp;
  Float_t rp;
  Float_t phi0[MAX_TRACKS]; //[nh]
  Bool_t bFlow[MAX_TRACKS]; //[nh]
  Float_t eta0[MAX_TRACKS];  //[nh]
  Float_t pt0[MAX_TRACKS];   //[nh]

  // List of branches
  TBranch *b_nh;    //!
  TBranch *b_b;     //!
  TBranch *b_rp;    //!
  TBranch *b_phi0;  //!
  TBranch *b_bFlow; //!
  TBranch *b_eta;   //!
  TBranch *b_pt;    //!

  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("b", &bimp, &b_b);
  chain->SetBranchAddress("rp", &rp, &b_rp);
  chain->SetBranchAddress("phi0", phi0, &b_phi0);
  chain->SetBranchAddress("bFlow", bFlow, &b_bFlow);
  chain->SetBranchAddress("eta", eta0, &b_eta);
  chain->SetBranchAddress("pt", pt0, &b_pt);

  if (chain == 0)
    return;

  const double rootJ0 = 2.4048256;
  const double J1rootJ0 = 0.519147;
  double theta[thetabins];
  // double multPOI[npt];
  for (int it = 0; it < thetabins; ++it)
  {
    theta[it] = it * TMath::Pi() / (2.0 * thetabins);
  }

  int mult;
  bool bUseProduct = 0;
  // TComplex cExponent[thetabins];

  // from 1-st run
  const double res2[9] = {0.3872, 0.498813, 0.604171, 0.629951, 0.600002, 0.534153, 0.427024, 0.300824, 0.195141};

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(), "recreate");
  // QA histograms
  TH1I *hEvt = new TH1I("hEvt", "Event number", 1, 0, 1);
  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 300, 0, MAX_TRACKS);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 350, -3.5, 3.5);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

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

  CGtheta *Gtheta = new CGtheta(bFirstRun, true);
  Gtheta->SetDebugFlag(false);
  if (!bFirstRun) Gtheta->ProcessRootFileWithHistFromFirstRun(inputFileHistFromFirstRun);
  
  CQVector *Q2 = new CQVector();
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 1000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    // if (iEv == 10000)
    //   break;
    chain->GetEntry(iEv);
    hEvt->Fill(0);

    // Get centrality
    double dCent = CentB(bimp);
    if (dCent == -1)
      continue;
    mult = 0;
    int icent = GetCentBin(dCent);
    hBimp->Fill(bimp);

    double sumQxy[neta][2] = {{0}}; // [eta-,eta+][x,y]
    double multQv[neta] = {0};      // [eta+,eta-]

    Q2->Reset();
    Gtheta->Reset();

    for (int iTrk = 0; iTrk < nh; iTrk++)
    {
      float pt = pt0[iTrk];
      float eta = eta0[iTrk];
      float phi = phi0[iTrk];
      if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
        continue; // track selection

      hPt->Fill(pt);
      hEta->Fill(eta);
      hPhi->Fill(phi);

      Q2->CalQVector(phi);
      if (bFirstRun) Gtheta->CalMult();
      else Gtheta->CalMult(pt);
      Double_t v2 = TMath::Cos(2 * (phi-rp));
      if (bFlow[iTrk])
      {
        hv2MC->Fill(dCent, v2);       // calculate reference v2 from MC toy
        hv2MCpt[icent]->Fill(pt, v2); // Calculate differential v2 from MC toy
      }
      // Sub eta event method
      int fEta = -1;
      if (eta < -eta_gap && eta > -eta_cut)
        fEta = 0;
      if (eta > eta_gap && eta < eta_cut)
        fEta = 1;

      if (fEta > -1)
      {
        sumQxy[fEta][0] += pt * TMath::Cos(2.0 * phi);
        sumQxy[fEta][1] += pt * TMath::Sin(2.0 * phi);
        multQv[fEta]++;
      } // end of eta selection
      if (Gtheta->GetUseProduct())
      {
        Gtheta->CalGFProduct(phi, icent);
      }

      mult++;
    } // end of track loop
    if (mult != 0)
    {
      hMult->Fill(mult);

      // Q2x /= (double) mult;
      // Q2y /= (double) mult;
      Gtheta->CalQtheta(Q2);

      if (bFirstRun)
      {
        Gtheta->CalGFSum();
        Gtheta->FillHistGF(icent, Q2);
      }
      else
      {
        Gtheta->CalDenominatorPOI(icent);
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
    if (!bFirstRun)
    {
      for (int iTrk = 0; iTrk < nh; iTrk++)
      {
        float pt = pt0[iTrk];
        float eta = eta0[iTrk];
        float phi = phi0[iTrk];
        if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
          continue; // track selection
        if (fEP[0] != -9999. && fEP[1] != -9999.)
        {
          float v2 = -999.0;
          if (eta > 0)
          { // eta+
            v2 = TMath::Cos(2.0 * (phi - fEP[0])) / res2[icent];
          }
          if (eta < 0)
          { // eta-
            v2 = TMath::Cos(2.0 * (phi - fEP[1])) / res2[icent];
          }
          // if(fabs(eta[itrk])<1.0){ // eliminate spectators
          if (v2 != -999.0)
          {
            hv2EPpt[icent]->Fill(pt, v2);
            hv2EP->Fill(dCent, v2);
          }
        }
        Gtheta->CalNumeratorPOI(icent, phi, pt);

      } // end of track loop
    }
  } // end event loop

  // Writing output
  fo->cd();
  Gtheta->SaveHist();
  if (bFirstRun)
  {
    hEvt->Write();
    hMult->Write();
    hBimp->Write();
    hPt->Write();
    hPhi->Write();
    hEta->Write();
    hv2MC->Write();
    HRes->Write();
    for (int ic = 0; ic < ncent; ic++)
    {
      hv2MCpt[ic]->Write();
    }
  }
  else
  {
    hv2EP->Write();
    for (int ic = 0; ic < ncent; ic++)
    {
      hv2EPpt[ic]->Write();
    }
  }

  fo->Close();

  timer.Stop();
  timer.Print();
}

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
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

int GetCentBin(float cent)
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

// root -l -b -q FlowLeeYangZeros.C+'("/weekly/demanov/mchybrid/39GeVxpt500new/hybrid39GeV500Evrun022.root","testrun2.root","./OUT/HistFromFirstRun.root",0)'
// root -l -b -q FlowLeeYangZeros.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/Urqmd11.5/runlist_00","test.root")'

// prReGthetaSum_mult0_theta0->Draw()