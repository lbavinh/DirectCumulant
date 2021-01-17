#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include <TLegend.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

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
  cout << "const double res2 = {";
  for (int i=0; i<pr->GetNbinsX(); i++)
  {
    cout << TMath::Sqrt(pr->GetBinContent(i+1)) <<", ";
  }
  cout <<"};" << endl;
}

void ToyModelTreeReaderLYZ(TString file = "ToyModel.root", TString outFile = "LYZ.root")
{
  
  const int ncent = 9; // 0-80%
  const double res2[ncent] = {0.574529, 0.716237, 0.815169, 0.852812, 0.849012, 0.814938, 0.745442, 0.620791, 0.49103};
  const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};

  const double maxpt = 3.5; // max pt
  const double minpt = 0.2; // min pt
  const double eta_cut = 2.0;
  const double eta_gap = 0.05;
  const int npt = 12; // 0.2 - 3.5 GeV/c
  const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  const int neta = 2; // [eta-,eta+]
  const int max_nh = 6000;
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

    hMult->Fill(nh);
    hRP->Fill(rp);
    hBimp->Fill(b);
    hBimpvsMult->Fill(nh, b);
    double sumQxy[neta][2] = {{0}}; // [eta-,eta+][x,y]
    double multQv[neta] = {0};      // [eta+,eta-]
    for (int i = 0; i < nh; i++)
    { // track loop
      double pT = pt[i];
      if (pT < minpt || pT > maxpt || eta[i] > eta_cut)
        continue;
      hPt->Fill(pT);
      double phi = phi0[i] - rp;
      if (phi < 0)
        phi += 2. * TMath::Pi();
      hPhi->Fill(phi);
      hPhil->Fill(phi0[i]);
      hEta->Fill(eta[i]);

      Int_t ipt = -1;
      for (int j = 0; j < npt; j++)
        if (pT >= bin_pT[j] && pT < bin_pT[j + 1])
          ipt = j;

      Double_t v2 = TMath::Cos(2 * (phi0[i] - rp));

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
        sumQxy[fEta][0] += pT * TMath::Cos(2.0 * phi0[i]);
        sumQxy[fEta][1] += pT * TMath::Sin(2.0 * phi0[i]);
        multQv[fEta]++;
      } // end of eta selection
    }   // end of track loop

    // Eta sub-event method
    double fEP[2]; // [eta-,eta+]
    double fQv[2];
    for (int ieta = 0; ieta < neta; ieta++)
    {
      if (multQv[ieta] > 5)
      { // multiplicity > 5
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
        fEP[ieta] = TMath::ATan2(sin(2.0 * fEP[ieta]), cos(2.0 * fEP[ieta])); // what for?
        fEP[ieta] /= 2.0;
        fQv[ieta] = TMath::Sqrt(TMath::Power(sumQxy[ieta][0], 2.0) + TMath::Power(sumQxy[ieta][1], 2.0)) / TMath::Sqrt(multQv[ieta]);
      }
      else
      {
        fEP[ieta] = -9999;
        fQv[ieta] = -9999;
      }
    }

    // Estimate the event plane resolution of 2nd harmonic by the correlation between the azimuthal
    // angles of two subset groups of tracks, called sub-events \eta- and \eta+
    double psi1, psi2, fq1, fq2;
    psi1 = fEP[0]; // eta-
    psi2 = fEP[1]; // eta+
    fq1 = fQv[0];
    fq2 = fQv[1];
    if (psi1 < -9000 || psi2 < -9000)
      continue;
    if (fq1 < 0 || fq2 < 0)
      continue;
    HRes->Fill(cent, TMath::Cos(2.0 * (fEP[0] - fEP[1])));
    for (int itrk = 0; itrk < nh; itrk++)
    { //track loop
      double pT = pt[itrk];
      if (pT < minpt || pT > maxpt || eta[itrk] > eta_cut)
        continue;

      // Int_t ipt = 0;
      // for (int j = 0; j < npt; j++) if (pT >= bin_pT[j] && pT < bin_pT[j + 1]) ipt = j;
      float v2 = -999.0;
      if (eta[itrk] > 0)
      { // eta+
        v2 = cos(2.0 * (phi0[itrk] - psi1)) / res2[icent];
      }
      if (eta[itrk] < 0)
      { // eta-
        v2 = cos(2.0 * (phi0[itrk] - psi2)) / res2[icent];
      }
      // if(fabs(eta[itrk])<1.0){ // eliminate spectators
      if (v2 != 999.0)
      {
        hv2EPpt[icent]->Fill(pT, v2);
        hv2EP->Fill(cent, v2);
      }
    } // end of the track loop
  }   // end of event loop

  // fChain->Close();
  cout << file << " file processed" << endl;
  cout << "Resolution:" << endl;
  GetRes(HRes);
  TCanvas c;

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
  TLegend *leg = new TLegend(0.7,0.15,0.85,0.35);
  leg->SetBorderSize(0);
  leg->AddEntry(hv2EP,"EP","p");
  leg->AddEntry(hv2MC,"MC","p");
  leg->Draw();
  gStyle->SetOptStat(0);
  c.SaveAs("Flow.png");
  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

