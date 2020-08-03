
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TRandom3.h"
#include "TTree.h"
#include <string>
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"

TH1F *hBimp;
TH1I *hNpart, *hNcoll;
TH2F *hBimpvsNpart, *hBimpvsNcoll;

TRandom3 *ar;
TRandom2 *br;
TRandom3 *TRpsi;
TRandom2 *TRpt;

TFile *fi;

void Book()
{ // Read histograms from the Glauber file
  ar = new TRandom3();
  TRpsi = new TRandom3();
  br = new TRandom2();
  TRpt = new TRandom2();
}

double v1 = 0, v2 = 0.2, v3 = 0, v4 = 0, v5 = 0, v6 = 0;
double Cp = 3.1415926535;
static const float PI = TMath::Pi();
static const float pTmax = 4900.;
float massLambda = 1.115;
float massProton = 0.938;
float massPion = 0.137;
float T = 0.26;
float ptMax = 5.0;
float alpha_Lambda = 0.642;

float calc_v2(double b, double eta, double pt)
{
  float a1, a2, a3, a4;
  a1 = 0.4397 * exp(-(b - 4.526) * (b - 4.526) / 72.0) + 0.636;
  a2 = 1.916 / (b + 2) + 0.1;
  a3 = 4.79 * 0.0001 * (b - 0.621) * (b - 10.172) * (b - 23) + 1.2; // this is >0 for b>0
  a4 = 0.135 * exp(-0.5 * (b - 10.855) * (b - 10.855) / 4.607 / 4.607) + 0.0120;

  float temp1 = pow(pt, a1) / (1 + exp((pt - 3.0) / a3));
  float temp2 = pow(pt + 0.1, -a2) / (1 + exp(-(pt - 4.5) / a3));
  float temp3 = 0.01 / (1 + exp(-(pt - 4.5) / a3));

  v2 = (a4 * (temp1 + temp2) + temp3) * exp(-0.5 * eta * eta / 2.0 / 2.0);

  return v2;
}

// New parameterization for vn
void jjia_minbias_new(double b, double eta, double pt)
{
  v2 = calc_v2(b, eta, pt);

  float fb = 0.97 + 1.06 * exp(-0.5 * b * b / 3.2 / 3.2);
  v3 = pow(fb * sqrt(v2), 3);

  float gb = 1.096 + 1.36 * exp(-0.5 * b * b / 3.0 / 3.0);
  gb = gb * sqrt(v2);
  v4 = pow(gb, 4);
  v5 = pow(gb, 5);
  v6 = pow(gb, 6);
  v1 = 0;
}

double F(double a, double pt)
{
  return (1 + 2 * v1 * cos(a) + 2 * v2 * cos(2 * (a)) + 2 * v3 * cos(3 * (a)) + 2 * v4 * cos(4 * (a)) + 2 * v5 * cos(5 * (a)) + 2 * v6 * cos(6 * (a))) / (2 * Cp);
}
double ra, rb;
double FGen(double a, double b, double pt)
{
  ra = 2 * Cp * a; // (0, 2*PI)
  rb = (1 + 2 * v1 + 2 * v2 + 2 * v3 + 2 * v4 + 2 * v5 + 2 * v6) / (2 * Cp) * b;
  while (F(ra, pt) < rb)
  {
    rb = (1 + 2 * v1 + 2 * v2 + 2 * v3 + 2 * v4 + 2 * v5 + 2 * v6) / (2 * Cp) * br->Rndm();
    ra = 2 * Cp * ar->Rndm();
  }
  return ra;
}

double GetProjectedRandom(double b, TH2F *const &hist)
// Projects Npart or Ncoll distribution for given impact parameter and gives you random Npart or Ncoll
// using the projected distribution as a probability function (i.e. gives you random number within RMS)
{
  TH1D *hist1D = hist->ProjectionY("tmp", hist->GetXaxis()->FindBin(b), hist->GetXaxis()->FindBin(b));
  double result = hist1D->GetRandom();
  return result;
}

double *DrawMult(TString glauberFileName = "./merge_hist_glaub_200gev.root")
{
  // Main parameters:
  //  f - Npart to Ncoll contribution to multiplicity. Essentially, it reflects how multiplicity behaves near its maximum (in the most central region).
  //    f = 0 - Multiplicity is renormalized Ncoll
  //    f = 1 - Multiplicity is renormalized Npart
  //  MeanMult - mean value of the multiplicity
  //  Nevents - number of generated events
  const double f = 0.1, MeanMult = 250.;
  //const int Nevents = 2e5;

  hBimp = (TH1F *)fi->Get("hBimp");
  hNpart = (TH1I *)fi->Get("hNpart");
  hNcoll = (TH1I *)fi->Get("hNcoll");
  hBimpvsNpart = (TH2F *)fi->Get("hBimpvsNpart");
  hBimpvsNcoll = (TH2F *)fi->Get("hBimpvsNcoll");

  double b = hBimp->GetRandom();
  double Npart = GetProjectedRandom(b, hBimpvsNpart);
  double Ncoll = GetProjectedRandom(b, hBimpvsNcoll);
  double Na = f * Npart + (1 - f) * Ncoll;
  double NaNorm = (f * hNpart->GetMean() + (1 - f) * hNcoll->GetMean()) / MeanMult;
  int mult = (Na / NaNorm);
  double *bmult = new double[2];
  bmult[0] = b;
  bmult[1] = mult;
  return bmult;
}

double dndpT(double pT)
{
  double temp;
  double pTmin = 100.;
  double pTmax = 4900.;
  double pT0 = 500.;
  double pT1 = 3000.;
  double T0 = 300.;
  if (pT < pTmin)
    temp = 0;
  else if (pT <= pT0)
    temp = 1;
  else if (pT <= pT1)
    temp = exp(-(pT - pT0) / T0);
  else
    temp = exp(-(pT1 - pT0) / T0) * pow((pT1 / pT), 7.);
  return temp;
}

void generator(TString glauberFileName = "./merge_hist_glaub_200gev.root", int run0 = 3000000, const char *file_name = "./v2hadron.root")
{
  Book();
  fi = new TFile(glauberFileName.Data(), "read");
  TRandom2 rnd;
  gRandom->SetSeed(rnd.Uniform(50000000., 500000000));
  TRpsi->SetSeed(rnd.Uniform(50000000., 500000000));
  ar->SetSeed(rnd.Uniform(50000000., 500000000));
  br->SetSeed(rnd.Uniform(50000000., 500000000));
  TFile *f0 = new TFile(file_name, "recreate");
  f0->cd();

  Int_t event;
  Int_t nh = 0;
  Float_t b;
  Float_t rp;
  Float_t phi0[1500];
  Bool_t d_bflow[1500];
  Float_t dPHI[1500];
  Float_t meta[1500];
  Float_t mpt[1500];
  Int_t nonflow = 0;
  Float_t nonflowrate = 0.25;

  TTree *tree = new TTree("htree", "My Tree");
  tree->Branch("nh", &nh, "nh/I");
  tree->Branch("b", &b, "b/F");
  tree->Branch("rp", &rp, "rp/F");
  tree->Branch("phi0", &phi0, "phi0[nh]/F");
  tree->Branch("bFlow", &d_bflow, "d_bflow[nh]/O");
  tree->Branch("eta", &meta, "meta[nh]/F");
  tree->Branch("pt", &mpt, "mpt[nh]/F");

  float A = PI / 3.;
  float B = PI / 2.;

  float C = PI;
  float D = 5. * PI / 4.;

  // Lambda p_t distribution: A*p_t*exp(-m_T/T)
  TF1 *pt_dist = new TF1("pt_dist", "[0]/(2.*[3])*x*exp(-sqrt(x^2+[2]^2)/[1])", 0., ptMax);
  pt_dist->FixParameter(0, 50.);
  pt_dist->FixParameter(1, T);
  pt_dist->FixParameter(2, massLambda);
  pt_dist->FixParameter(3, Cp);
  // Lambda eta distribution: flat
  TF1 *eta_dist = new TF1("eta_dist", "0.5", -1., 1.);

  double *bmult = new double[2];
  for (int k = 1; k < run0; k++)
  {
    if (k % 10000 == 0)
    {
      cout << k << " events were simulated, the process is " << k * 100 / run0 << "% complete" << endl;
    }
    bmult = DrawMult(glauberFileName);
    b = (float)(bmult[0]);
    nh = (int)(bmult[1]);
    /*while(nh<20){bmult=DrawMult(glauberFileName);
    b=(float)(bmult[0]);
    nh=(int)(bmult[1]);}*/

    rp = (TRpsi->Rndm()) * 2 * Cp;
    for (int j = 0; j < nh; j++) 
    {
      //mpt[j]=pt_dist->GetRandom();

    momentum:
      mpt[j] = pTmax * (TRpsi->Rndm());
      if (rnd.Rndm() > dndpT(mpt[j]))
        goto momentum;
      mpt[j] = mpt[j] / 1000.;

      meta[j] = 4. * ar->Rndm() - 2.;
    }
    for (int d = 0; d < nh; d++)
    {
      jjia_minbias_new(b, meta[d], mpt[d]);

      dPHI[d] = FGen(ar->Rndm(), br->Rndm(), mpt[d]);
      phi0[d] = dPHI[d] + rp;
      d_bflow[d] = 1;
      if (phi0[d] > 2 * Cp)
      {
        phi0[d] = phi0[d] - 2 * Cp;
      }

      //while((phi0[d]>=A && phi0[d]<=B) || (phi0[d]>=C && phi0[d]<=D)){dPHI[d]=FGen(ar->Rndm(),br->Rndm(),mpt[d]);phi0[d]=dPHI[d]+rp;if(phi0[d]>2*Cp){phi0[d]=phi0[d]-2*Cp;} }

      if ( nonflow > 0 && (d + nonflow - 1) < nh && TRpt->Rndm() < nonflowrate )
      {
        for (int kk = 1; kk < nonflow; kk++)
        {
          d++;
          mpt[d] = mpt[d - 1];
          dPHI[d] = dPHI[d - 1];
          phi0[d] = phi0[d - 1];
          meta[d] = meta[d -1]; // Vinh's test
          d_bflow[d] = 0;
        }
      }
    }
    event = k;
    tree->Fill();
  }
  tree->Write();
  f0->Close();
  cout << "DONE generator" << endl;
}
