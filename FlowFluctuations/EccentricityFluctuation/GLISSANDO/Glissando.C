#define Glissando_cxx
#include "Glissando.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TMath.h>

#include <iostream>

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if      (bimp < 2.91)  fcent = 2.5; // 0-5%
  else if (bimp < 4.18)  fcent = 7.5; // 5-10%
  else if (bimp < 6.01)  fcent = 15.; // 10-20%
  else if (bimp < 7.37)  fcent = 25.; // 20-30%
  else if (bimp < 8.52)  fcent = 35.; // 30-40%
  else if (bimp < 9.57)  fcent = 45.; // 40-50%
  else if (bimp < 10.55) fcent = 55.; // 50-60%
  else if (bimp < 11.46) fcent = 65.; // 60-70%
  else if (bimp < 12.31) fcent = 75.; // 70-80%
  else                   fcent = -1;
  return fcent;
}


int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 2.5) return 0;
  if (cent == 7.5) return 1;
  if (cent == 15.) return 2;
  if (cent == 25.) return 3;
  if (cent == 35.) return 4;
  if (cent == 45.) return 5;
  if (cent == 55.) return 6;
  if (cent == 65.) return 7;
  if (cent == 75.) return 8;
  return -1;
}

void Glissando::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Glissando.C
//      root> Glissando t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  TFile *fo = new TFile(outName.Data(), "recreate");
  const int ncent = 9;
  TProfile *prEcc22vsCent = new TProfile(Form("prEcc22vsCent"),Form("prEcc22vsCent"),ncent,0.,ncent);
  TProfile *prEcc24vsCent = new TProfile(Form("prEcc24vsCent"),Form("prEcc24vsCent"),ncent,0.,ncent);
  TProfile *prCov24vsCent = new TProfile(Form("prCov24vsCent"),Form("prCov24vsCent"),ncent,0.,ncent);
  TProfile *prEcc2vsCent = new TProfile(Form("prEcc2vsCent"),Form("prEcc2vsCent"),ncent,0.,ncent);

  TProfile *prEcc22vsB = new TProfile(Form("prEcc22vsB"),Form("prEcc22vsB"),200,0.,20);
  TProfile *prEcc24vsB = new TProfile(Form("prEcc24vsB"),Form("prEcc24vsB"),200,0.,20);
  TProfile *prCov24vsB = new TProfile(Form("prCov24vsB"),Form("prCov24vsB"),200,0.,20);
  TProfile *prEcc2vsB = new TProfile(Form("prEcc2vsB"),Form("prEcc2vsB"),200,0.,20);
  Long64_t nentries = fChain->GetEntries();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if (jentry % 10000 == 0) std::cout << "Event [" << jentry << "/" << nentries << "]" << std::endl;
    Double_t ecc22 =  TMath::Power(eps,2.);
    Double_t ecc24 =  TMath::Power(eps,4.);

    prEcc2vsB->Fill(b, eps);
    prEcc22vsB->Fill(b, ecc22);  // <eps^2>
    prEcc24vsB->Fill(b, ecc24);  // <eps^4>
    prCov24vsB->Fill(b, ecc22*ecc24); // <eps^2*eps^4>

    float cent = CentB(b);
    int fcent = GetCentBin(cent);
    if (fcent!=-1)
    {
    prEcc2vsCent->Fill(0.5+fcent, eps);
    prEcc22vsCent->Fill(0.5+fcent, ecc22);  // <eps^2>
    prEcc24vsCent->Fill(0.5+fcent, ecc24);  // <eps^4>
    prCov24vsCent->Fill(0.5+fcent, ecc22*ecc24); // <eps^2*eps^4>
    }

  }
  
  fo->cd();
  fo->Write();
  fo->Close();

}
