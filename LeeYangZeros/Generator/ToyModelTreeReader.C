#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include <TLegend.h>
#include <iostream>
#include <fstream>
#include <string>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

using std::cout;
using std::endl;
using std::cerr;
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


void ToyModelTreeReader(TString inputFileName, TString outputFileName)
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


  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  TH2F *hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  TH1F *hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);

  TProfile *hv2MC = new TProfile("hv2MC", "MC flow", ncent, &bin_cent[0]);
  TProfile *hv2MCpt[ncent];


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
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    if (jentry % 10000 == 0)
      cout << "[" << jentry << "/" << nentries << "]" << endl;
    fChain->GetEntry(jentry);

    double dCent = CentB(b);
    if (dCent < 0)
      continue;
    int icent = GetCentBin(dCent);

    hMult->Fill(nh);
    hRP->Fill(rp);
    hBimp->Fill(b);
    hBimpvsMult->Fill(nh, b);

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

      Int_t ipt = -1;
      for (int j = 0; j < npt; j++) if (pT >= bin_pT[j] && pT < bin_pT[j + 1]) ipt = j;

      Double_t v2 = TMath::Cos(2 * (phi - rp));
      if (bFlow[i])
      {
        hv2MC->Fill(dCent, v2);        // calculate reference v2 from MC toy
        hv2MCpt[icent]->Fill(pT, v2); // Calculate differential v2 from MC toy
      }
    } // end of track loop
  }   // end of event loop

  fo->cd();
  hMult->Write();
  hBimp->Write();
  hBimpvsMult->Write();
  hPt->Write();
  hPhi->Write();
  hEta->Write();
  hv2MC->Write();
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hv2MCpt[ipt]->Write();
  }
  fo->Close();
}

