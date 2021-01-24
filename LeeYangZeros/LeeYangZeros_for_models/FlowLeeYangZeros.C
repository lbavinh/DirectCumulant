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

using std::cerr;
using std::cout;
using std::endl;

#define MAX_TRACKS 10000

// Constant declaration
// const int npid = 8;  // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
const int ncent = 9; // 0-80%
const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
const int npt = 15; // 0.5 - 3.6 GeV/c - number of pT bins
const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
const double maxpt = 3.;  // max pt
const double minpt = 0.2; // min pt
const double maxptRF = 3.;
const double minptRF = 0.2;
const float eta_cut = 1.5;
const float eta_gap = 0.05;
const int neta = 2; // [eta-,eta+]

// LYZ
const int rbins = 2500;
const double rMax = 0.5;
const double rMin = 0.005;
const double rMaxSum = 0.9;
const double rMinSum = 0.0005;
const int thetabins = 10;

class CGtheta
{
public:
  CGtheta();
  virtual ~CGtheta(){}
  void SetUseProduct(bool kt) { this->fUseProduct = kt; }
  bool GetUseProduct() const { return this->fUseProduct; }
  TH1F* GetHistGthetaSum() const { return this->fHistGthetaSum[0][0]; }
  void Fill(Double_t r, TComplex Gtheta, Int_t icent, Int_t itheta);
  void Fill(Double_t r, TComplex GthetaSum, TComplex GthetaProduct, Int_t icent, Int_t itheta);
  void SaveHist();
private:
  bool fUseProduct;
  TProfile *fPrReGthetaSum[ncent][thetabins];
  TProfile *fPrImGthetaSum[ncent][thetabins];
  TH1F *fHistGthetaSum[ncent][thetabins];

  TProfile *fPrReGthetaProduct[ncent][thetabins];
  TProfile *fPrImGthetaProduct[ncent][thetabins];
  TH1F *fHistGthetaProduct[ncent][thetabins];
};
CGtheta::CGtheta() : fUseProduct(0)
{

  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      fPrReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
      fPrImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
      fHistGthetaSum[i][j] = new TH1F(Form("hGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
      if (fUseProduct)
      {
        fPrReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
        fPrImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
        fHistGthetaProduct[i][j] = new TH1F(Form("hGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
      }
    }
  }
}
void CGtheta::Fill(Double_t r, TComplex Gtheta, Int_t icent, Int_t itheta)
{
  fPrReGthetaSum[icent][itheta]->Fill(r, Gtheta.Re());
  fPrImGthetaSum[icent][itheta]->Fill(r, Gtheta.Im());
}

void CGtheta::Fill(Double_t r, TComplex Gtheta, TComplex GthetaProduct, Int_t icent, Int_t itheta)
{
  fPrReGthetaSum[icent][itheta]->Fill(r, Gtheta.Re());
  fPrImGthetaSum[icent][itheta]->Fill(r, Gtheta.Im());

  fPrReGthetaProduct[icent][itheta]->Fill(r, GthetaProduct.Re());
  fPrImGthetaProduct[icent][itheta]->Fill(r, GthetaProduct.Im());

}

void CGtheta::SaveHist()
{
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
}

void FlowLeeYangZeros(TString inputFileName, TString outputFileName, Bool_t bFirstRun = 1)
{
  TStopwatch timer;
  timer.Start();

  // Configure input information
  TChain *chain = new TChain("mctree");
  chain->Add(inputFileName.Data());
  // std::ifstream file(inputFileName.Data());
  // std::string line;
  // while (std::getline(file, line))
  // {
  //   chain->Add(line.c_str());
  // }

  Float_t bimp;
  Float_t phi2;
  Float_t phi3;
  Float_t ecc2;
  Float_t ecc3;
  Int_t npart;
  Int_t nh;
  Float_t momx[MAX_TRACKS];   //[nh]
  Float_t momy[MAX_TRACKS];   //[nh]
  Float_t momz[MAX_TRACKS];   //[nh]
  Float_t ene[MAX_TRACKS];    //[nh]
  Int_t hid[MAX_TRACKS];      //[nh]
  Int_t pdg[MAX_TRACKS];      //[nh]
  Short_t charge[MAX_TRACKS]; //[nh]

  // List of branches
  TBranch *b_bimp;   //!
  TBranch *b_phi2;   //!
  TBranch *b_phi3;   //!
  TBranch *b_ecc2;   //!
  TBranch *b_ecc3;   //!
  TBranch *b_npart;  //!
  TBranch *b_nh;     //!
  TBranch *b_momx;   //!
  TBranch *b_momy;   //!
  TBranch *b_momz;   //!
  TBranch *b_ene;    //!
  TBranch *b_hid;    //!
  TBranch *b_pdg;    //!
  TBranch *b_charge; //!

  chain->SetBranchAddress("bimp", &bimp, &b_bimp);
  chain->SetBranchAddress("phi2", &phi2, &b_phi2);
  chain->SetBranchAddress("phi3", &phi3, &b_phi3);
  chain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  chain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  chain->SetBranchAddress("npart", &npart, &b_npart);
  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("momx", momx, &b_momx);
  chain->SetBranchAddress("momy", momy, &b_momy);
  chain->SetBranchAddress("momz", momz, &b_momz);
  chain->SetBranchAddress("ene", ene, &b_ene);
  chain->SetBranchAddress("hid", hid, &b_hid);
  chain->SetBranchAddress("pdg", pdg, &b_pdg);
  chain->SetBranchAddress("charge", charge, &b_charge);

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
  TComplex cExpo;
  double Q2x, Q2y;
  int mult;
  bool bUseProduct = 0;
  TComplex cDenominator;
  TComplex cExponent[thetabins];

  // from 1-st run
  const double res2[9] = {0.3872, 0.498813, 0.604171, 0.629951, 0.600002, 0.534153, 0.427024, 0.300824, 0.195141};
  const double r02[ncent][thetabins] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0.114015, 0.116277, 0, 0, 0, 0, 0, 0, 0, 0.122012},
      {0.10385, 0.106375, 0.11648, 0, 0, 0, 0, 0.152084, 0.116449, 0.106778},
      {0.120191, 0.123039, 0.134209, 0, 0, 0, 0, 0, 0.136188, 0.124},
      {0.151126, 0.155544, 0.173591, 0, 0, 0, 0, 0, 0.174351, 0.15612},
      {0.217719, 0.228114, 0, 0, 0, 0, 0, 0, 0, 0.22895},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  const double chisq[9] = {0, 0.930226, 1.19355, 1.39133, 1.2499, 0.981304, 0, 0, 0};

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

  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TH1F *hGthetaSum[ncent][thetabins];

  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TH1F *hGthetaProduct[ncent][thetabins];

  TProfile *prRefMult = new TProfile("prRefMult", "", ncent, &bin_cent[0]);
  TProfile *prQ2x = new TProfile("prQ2x", "", ncent, &bin_cent[0]);
  TProfile *prQ2y = new TProfile("prQ2y", "", ncent, &bin_cent[0]);
  TProfile *prQ2ModSq = new TProfile("prQ2ModSq", "", ncent, &bin_cent[0]);

  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];
  TProfile *prMultPOI[ncent];
  if (bFirstRun)
  {
    // for (int i = 0; i < ncent; ++i)
    // {
    //   for (int j = 0; j < thetabins; ++j)
    //   {
    //     prReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
    //     prImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
    //     hGthetaSum[i][j] = new TH1F(Form("hGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
    //     if (bUseProduct)
    //     {
    //       prReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
    //       prImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
    //       hGthetaProduct[i][j] = new TH1F(Form("hGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
    //     }
    //   }
    // }
  }

  else
  {
    for (int i = 0; i < thetabins; i++)
    {
      prReDenom[i] = new TProfile(Form("prReDenom_theta%i", i), "", ncent, &bin_cent[0]);
      prImDenom[i] = new TProfile(Form("prImDenom_theta%i", i), "", ncent, &bin_cent[0]);

      for (int j = 0; j < ncent; j++)
      {
        prReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j), "", npt, &bin_pT[0]);
        prImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j), "", npt, &bin_pT[0]);
      }
    }

    for (int ic = 0; ic < ncent; ic++)
    {
      prMultPOI[ic] = new TProfile(Form("prMultPOI_cent%i", ic), "", npt, 0, npt);
    }
  }
  CGtheta *Gtheta = new CGtheta();
  // Gtheta->SetUseProduct(true);
  double r[rbins], rSum[rbins];
  if (bFirstRun)
  {
    for (int rbin = 0; rbin < rbins; ++rbin)
    {
      // if (bUseProduct)
      // {
      //   r[rbin] = (double)hGthetaProduct[0][0]->GetBinCenter(rbin + 1);
      // }
      // else
      // {
      //   rSum[rbin] = (double)hGthetaSum[0][0]->GetBinCenter(rbin + 1);
      // }
      r[rbin] = Gtheta->GetHistGthetaSum()->GetBinCenter(rbin + 1);
      rSum[rbin] = Gtheta->GetHistGthetaSum()->GetBinCenter(rbin + 1);
      // cout << r[rbin] << " ";
    }
    // cout << endl;
  }
  
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    // if (iEv == 20000) break;
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

    for (int i = 0; i < thetabins; ++i)
    {
      Qtheta[i] = 0.;
      cExponent[i] = TComplex(0.0, 0.0);
    }
    if (bFirstRun)
    {
      for (int i = 0; i < rbins; ++i)
      {
        for (int j = 0; j < thetabins; ++j)
        {
          genfunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
          if (bUseProduct)
            genfunP[i][j] = TComplex::One(); // initialize to 1, calcualte via product
        }
      }
    }

    Q2x = 0.;
    Q2y = 0.;
    if (!bFirstRun)
      for (int ipt = 0; ipt < npt; ipt++)
        multPOI[ipt] = 0.;

    for (int iTrk = 0; iTrk < nh; iTrk++)
    {
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      float pt = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
        continue; // track selection
      // if (fabs(eta)<eta_gap) continue;
      auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      if (!particle)
        continue;
      float charge = 1. / 3. * particle->Charge();
      if (charge == 0)
        continue;
      hPt->Fill(pt);
      hEta->Fill(eta);
      hPhi->Fill(phi);
      // int fId = -1;
      // if (pdg[iTrk] == 211)
      //   fId = 1; // pion+
      // if (pdg[iTrk] == 321)
      //   fId = 2; // kaon+
      // if (pdg[iTrk] == 2212)
      //   fId = 3; // proton
      // if (pdg[iTrk] == -211)
      //   fId = 5; // pion-
      // if (pdg[iTrk] == -321)
      //   fId = 6; // kaon-
      // if (pdg[iTrk] == -2212)
      //   fId = 7; // anti-proton
      Q2x += TMath::Cos(2.0 * phi);
      Q2y += TMath::Sin(2.0 * phi);
      if (!bFirstRun)
      {
        Int_t ipt = -1;
        for (int j = 0; j < npt; j++)
          if (pt >= bin_pT[j] && pt < bin_pT[j + 1])
            ipt = j;
        multPOI[ipt]++;
      }
      Double_t v2 = TMath::Cos(2 * phi);
      hv2MC->Fill(dCent, v2);       // calculate reference v2 from MC toy
      hv2MCpt[icent]->Fill(pt, v2); // Calculate differential v2 from MC toy

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
      if (bFirstRun)
      {
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
      }
      mult++;
    } // end of track loop
    if (mult != 0)
    {
      hMult->Fill(mult);
      if (bFirstRun)
      {
        prRefMult->Fill(dCent, mult);
      }
      else
      {
        for (int ipt = 0; ipt < npt; ipt++)
        {
          prMultPOI[icent]->Fill(ipt + 0.5, multPOI[ipt]);
        }
      }

      // Q2x /= (double) mult;
      // Q2y /= (double) mult;
      for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      {
        Qtheta[thetabin] = Q2x * TMath::Cos(2.0 * theta[thetabin]) + Q2y * TMath::Sin(2.0 * theta[thetabin]);
      }

      if (bFirstRun)
      {
        prQ2x->Fill(dCent, Q2x);
        prQ2y->Fill(dCent, Q2y);
        prQ2ModSq->Fill(dCent, Q2x * Q2x + Q2y * Q2y);

        for (int rbin = 0; rbin < rbins; rbin++)
        {
          for (int thetabin = 0; thetabin < thetabins; thetabin++)
          {
            cExpo = TComplex(0., rSum[rbin] * Qtheta[thetabin]);
            genfunS[rbin][thetabin] = TComplex::Exp(cExpo); // generating function from Q-vectors
            // prReGthetaSum[icent][thetabin]->Fill(rSum[rbin], genfunS[rbin][thetabin].Re());
            // prImGthetaSum[icent][thetabin]->Fill(rSum[rbin], genfunS[rbin][thetabin].Im());
            // if (bUseProduct)
            // {
            //   prReGthetaProduct[icent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Re());
            //   prImGthetaProduct[icent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Im());
            // }
            Gtheta->Fill(rSum[rbin], genfunS[rbin][thetabin], icent, thetabin);
          }
        }
      }
      else
      {
        // Differential LYZ
        for (int thetabin = 0; thetabin < thetabins; thetabin++)
        {
          cExponent[thetabin] = TComplex(0., r02[icent][thetabin] * Qtheta[thetabin]);
          cDenominator = Qtheta[thetabin] * (TComplex::Exp(cExponent[thetabin])); // BP eq 12
          prReDenom[thetabin]->Fill(dCent, cDenominator.Re());
          prImDenom[thetabin]->Fill(dCent, cDenominator.Im());
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
    if (!bFirstRun)
    {
      for (int iTrk = 0; iTrk < nh; iTrk++)
      {
        TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
        float pt = vect.Pt();
        float eta = vect.Eta();
        float phi = vect.Phi();
        if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
          continue; // track selection
        // if (fabs(eta)<eta_gap) continue;
        auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
        if (!particle)
          continue;
        float charge = 1. / 3. * particle->Charge();
        if (charge == 0)
          continue;

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
          if (v2 != 999.0)
          {
            hv2EPpt[icent]->Fill(pt, v2);
            hv2EP->Fill(dCent, v2);
          }
        }

        for (int thetabin = 0; thetabin < thetabins; ++thetabin)
        {
          TComplex cNumeratorPOI = TMath::Cos(2.0 * (phi - theta[thetabin])) * (TComplex::Exp(cExponent[thetabin]));
          prReNumer[thetabin][icent]->Fill(pt, cNumeratorPOI.Re());
          prImNumer[thetabin][icent]->Fill(pt, cNumeratorPOI.Im());
        }
      } // end of track loop
    }
  } // end event loop

  // Writing output
  fo->cd();
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
    prRefMult->Write();
    prQ2x->Write();
    prQ2y->Write();
    prQ2ModSq->Write();
    // for (int i = 0; i < ncent; ++i)
    // {
    //   for (int j = 0; j < thetabins; ++j)
    //   {
    //     prReGthetaSum[i][j]->Write();
    //     prImGthetaSum[i][j]->Write();
    //     if (bUseProduct)
    //     {
    //       prReGthetaProduct[i][j]->Write();
    //       prImGthetaProduct[i][j]->Write();
    //     }
    //   }
    // }
    Gtheta->SaveHist();
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
    }
    for (int ic = 0; ic < ncent; ic++)
    {
      prMultPOI[ic]->Write();
      hv2EPpt[ic]->Write();
      hv2MCpt[ic]->Write();
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

// root -l -b -q FlowLeeYangZeros.C+'("/weekly/demanov/mchybrid/39GeVxpt500new/hybrid39GeV500Evrun022.root","test.root",0)'