#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TString.h>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#define MAX_TRACKS 10000

Double_t maxpt = 3.6;   // max pt for differential flow
Double_t minpt = 0.;    // min pt for differential flow
Double_t maxptRF = 3.;  // max pt for reference flow
Double_t minptRF = 0.2; // min pt for reference flow
Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements 
Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap

#include <iostream>
#include <fstream>

#include "QVector.h"
#include "FlowAnalysisWithScalarProduct.h"
#include "utilities.C"
void RunFlowAnalysisToyModel(TString inputFileName, TString outputFileName, TString inputFileHistFromFirstRun = "", Bool_t bFirstRun = 1)
{
  TStopwatch timer;
  timer.Start();

  TChain *chain = new TChain("tree");
  if (inputFileName.Contains(".root"))
  {
    chain->Add(inputFileName.Data());
  }
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
  Float_t eta0[MAX_TRACKS]; //[nh]
  Float_t pt0[MAX_TRACKS];  //[nh]

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

  // from 1-st run
  double res2[9];
  if (!bFirstRun){
    if (!inputFileHistFromFirstRun) cerr << "inputFileHistFromFirstRun=NULL!!" << endl;
    TFile *fiHist = new TFile(inputFileHistFromFirstRun.Data(),"read");
    HRes =  (TProfile*) fiHist->Get("HRes");
    for (int ic = 0; ic < ncent; ic++){
      res2[ic] = TMath::Sqrt(HRes->GetBinContent(ic+1));
    }
  }

  TProfile *hv2MCpt[ncent];
  TProfile *hv2EPpt[ncent];

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2EPpt[icent] = new TProfile(Form("hv2EPpt_%i", icent), "", npt, &pTBin[0]);
    hv2MCpt[icent] = new TProfile(Form("hv2MCpt_%i", icent), "", npt, &pTBin[0]);
  } // end of loop over centrality classes

  FlowAnalysisWithScalarProduct *flowSP = new FlowAnalysisWithScalarProduct();
  if (bFirstRun)
  {
    flowSP->SetFirstRun(true);
    flowSP->SetEtaGap(eta_gap);
    flowSP->Init();
  }
  else
  {
    flowSP->SetFirstRun(false);
    flowSP->SetEtaGap(eta_gap);
    flowSP->SetInputFileFromFirstRun(inputFileHistFromFirstRun);
    flowSP->Init();
  }


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
    int icent = GetCentBin(dCent);
    hBimp->Fill(bimp);

    double sumQxy[neta][2] = {{0}}; // [eta-,eta+][x,y]
    double multQv[neta] = {0};      // [eta+,eta-]

    flowSP->Zero();

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

      flowSP->ProcessFirstTrackLoop(eta, phi);
      Double_t v2 = TMath::Cos(2 * (phi - rp));
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

    } // end of track loop
    flowSP->ProcessEventAfterFirstTrackLoop(dCent);

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
        flowSP->ProcessSecondTrackLoop(eta, phi, pt, dCent);

      } // end of track loop
    }
  } // end event loop

  // Writing output
  fo->cd();
  flowSP->SaveHist();
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