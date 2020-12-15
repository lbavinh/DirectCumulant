#define GlauberEccReader_cxx
#include "GlauberEccReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TMath.h>

#include <iostream>

double S_overlap(double r, double b)
{
  double F = TMath::ACos(b/(2*r));
  return 2*(pow(r,2)*F - b*r/4*TMath::Sin(F));
}

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

void GlauberEccReader::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L GlauberEccReader.C
  //      root> GlauberEccReader t
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
  if (fChain == 0)
    return;

  TProfile *pEcc2vsB = new TProfile("pEcc2vsB", "pEcc2vsB", 200, 0, 20);
  TProfile *pEcc3vsB = new TProfile("pEcc3vsB", "pEcc3vsB", 200, 0, 20);
  TProfile *pNpartvsB = new TProfile("pNpartvsB", "pNpartvsB", 200, 0, 20);
  TProfile *pNcollvsB = new TProfile("pNcollvsB", "pNcollvsB", 200, 0, 20);
  TH2F *hEcc2vsB = new TH2F("hEcc2vsB", "hEcc2vsB", 200, 0, 20, 1000, 0., 2.5);
  TH2F *hEcc3vsB = new TH2F("hEcc3vsB", "hEcc3vsB", 200, 0, 20, 1000, 0., 2.5);

  TProfile *pEcc2vsS = new TProfile("pEcc2vsS", "pEcc2vsB", 2000, 0, 200);
  TProfile *pEcc3vsS = new TProfile("pEcc3vsS", "pEcc3vsB", 2000, 0, 200);

  const Double_t bBins [] = {0.,3.31,4.68,5.73,6.61,7.39,8.1,8.75,9.35,9.92,10.5,11.,11.5,11.9,12.4,12.8,13.2,13.7,14.2,14.9,20.};
  const Int_t Nbins = 20;
  // const Double_t R = 6.75; // BiBi
  const Double_t R = 6.38; // AuAu

  TProfile *pEcc2vsBSTAR = new TProfile("pEcc2vsBSTAR", "pEcc2vsBSTAR", Nbins,bBins);
  TProfile *pEcc3vsBSTAR = new TProfile("pEcc3vsBSTAR", "pEcc3vsBSTAR", Nbins,bBins);

  const int ncent = 9;
  TProfile *prEcc22vsCent = new TProfile(Form("prEcc22vsCent"),Form("prEcc22vsCent"),ncent,0.,ncent);
  TProfile *prEcc24vsCent = new TProfile(Form("prEcc24vsCent"),Form("prEcc24vsCent"),ncent,0.,ncent);
  TProfile *prCov24vsCent = new TProfile(Form("prCov24vsCent"),Form("prCov24vsCent"),ncent,0.,ncent);
  TProfile *prEcc2vsCent = new TProfile(Form("prEcc2vsCent"),Form("prEcc2vsCent"),ncent,0.,ncent);

  TProfile *prEcc22vsB = new TProfile(Form("prEcc22vsB"),Form("prEcc22vsB"),200,0.,20);
  TProfile *prEcc24vsB = new TProfile(Form("prEcc24vsB"),Form("prEcc24vsB"),200,0.,20);
  TProfile *prCov24vsB = new TProfile(Form("prCov24vsB"),Form("prCov24vsB"),200,0.,20);
  TProfile *prEcc2vsB = new TProfile(Form("prEcc2vsB"),Form("prEcc2vsB"),200,0.,20);


  const int nNpartBin = 7;
  TProfile *prEcc22vsNpart = new TProfile(Form("prEcc22vsNpart"),Form("prEcc22vsNpart"),nNpartBin,0.,350.);
  TProfile *prEcc24vsNpart = new TProfile(Form("prEcc24vsNpart"),Form("prEcc24vsNpart"),nNpartBin,0.,350.);
  TProfile *prCov24vsNpart = new TProfile(Form("prCov24vsNpart"),Form("prCov24vsNpart"),nNpartBin,0.,350.);
  TProfile *prEcc2vsNpart  = new TProfile(Form("prEcc2vsNpart"),Form("prEcc2vsNpart"),nNpartBin,0.,350.);

  // TFile *foTree = new TFile("output_ecc.tree.root","recreate");
  // TTree *eccTree = new TTree("eccTree","Eccentricity and Npart tree");

  // Double_t t_bimp;
  // Double_t t_ecc2;
  // Double_t t_ecc3;
  // Int_t t_npart;

  // eccTree->Branch("bimp",&t_bimp,"bimp/D");
  // eccTree->Branch("ecc2",&t_ecc2,"ecc2/D");
  // eccTree->Branch("ecc3",&t_ecc3,"ecc3/D");
  // eccTree->Branch("npart",&t_npart,"npart/I");

  Long64_t nentries = fChain->GetEntries();
  // Long64_t nentries = 500e3;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (jentry % 10000 == 0)
        std::cout << "Event [" << jentry << "/" << nentries << "]" << std::endl;
    // if (Cut(ientry) < 0) continue;

    // t_bimp = B;
    // t_ecc2 = Ecc2;
    // t_ecc3 = Ecc3;
    // t_npart = (int)Npart;

    // eccTree->Fill();

    Double_t Soverlap = S_overlap(R, B);

    Double_t ecc22 =  TMath::Power(Ecc2,2.);
    Double_t ecc24 =  TMath::Power(Ecc2,4.);

    prEcc2vsB->Fill(B, Ecc2);
    prEcc22vsB->Fill(B, ecc22);  // <Ecc2^2>
    prEcc24vsB->Fill(B, ecc24);  // <Ecc2^4>
    prCov24vsB->Fill(B, ecc22*ecc24); // <Ecc2^2*Ecc2^4>

    prEcc2vsNpart->Fill(Npart, Ecc2);
    prEcc22vsNpart->Fill(Npart, ecc22);  // <Ecc2^2>
    prEcc24vsNpart->Fill(Npart, ecc24);  // <Ecc2^4>
    prCov24vsNpart->Fill(Npart, ecc22*ecc24); // <Ecc2^2*Ecc2^4>

    float cent = CentB(B);
    int fcent = GetCentBin(cent);
    if (fcent!=-1)
    {
    prEcc2vsCent->Fill(0.5+fcent, Ecc2);
    prEcc22vsCent->Fill(0.5+fcent, ecc22);  // <Ecc2^2>
    prEcc24vsCent->Fill(0.5+fcent, ecc24);  // <Ecc2^4>
    prCov24vsCent->Fill(0.5+fcent, ecc22*ecc24); // <Ecc2^2*Ecc2^4>
    }

    pNpartvsB->Fill(B, Npart);
    pNcollvsB->Fill(B, Ncoll);
    pEcc2vsB->Fill(B, Ecc2);
    pEcc3vsB->Fill(B, Ecc3);
    pEcc2vsBSTAR->Fill(B, Ecc2);
    pEcc3vsBSTAR->Fill(B, Ecc3);
    hEcc2vsB->Fill(B, Ecc2);
    hEcc3vsB->Fill(B, Ecc3);

    pEcc2vsS->Fill(Soverlap, Ecc2);
    pEcc3vsS->Fill(Soverlap, Ecc3);

  }

  // foTree->cd();
  // eccTree->Write();
  //foTree->Close();

  TFile *fo = new TFile(outName.Data(), "recreate");
  fo->cd();

  prEcc2vsB->Write();
  prEcc22vsB->Write();
  prEcc24vsB->Write();
  prCov24vsB->Write();
  
  prEcc2vsCent->Write();
  prEcc22vsCent->Write();
  prEcc24vsCent->Write();
  prCov24vsCent->Write();

  prEcc2vsNpart->Write();
  prEcc22vsNpart->Write();
  prEcc24vsNpart->Write();
  prCov24vsNpart->Write();

  pEcc2vsB->Write();
  pEcc3vsB->Write();
  pEcc2vsBSTAR->Write();
  pEcc3vsBSTAR->Write();
  hEcc2vsB->Write();
  hEcc3vsB->Write();
  pNpartvsB->Write();
  pNcollvsB->Write();
  pEcc2vsS->Write();
  pEcc3vsS->Write();
  fo->Close();
}
