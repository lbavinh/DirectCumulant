#include "TFile.h"
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <iostream>
#include "TLine.h"
#include "TMath.h"

void res2() {
  static const int ncent = 8; // bins of centrality classes
  
  // TFile *file = new TFile("./ROOTFile/res2_nonflow.root","read");
  // TFile *file = new TFile("./ROOTFile/res2.root","read");
  TFile *file = new TFile("./OUT/res2.root","read");
  float res2EW[ncent]; // 8 - number of cent bins


  float cent[ncent] = {5, 15, 25, 35, 45, 55, 65, 75};
  float eres[ncent];    // errors of resolution
  float ecent[ncent];   // errors of centrality bin

  char hname1[800];
  for (int ic = 0; ic < ncent; ic++) {
    TProfile *h3 = (TProfile *)file->Get("HRes");
    res2EW[ic] = sqrt(h3->GetBinContent(1+ic));
    eres[ic] = 0.01;
    ecent[ic] = 0.03;

    cout << res2EW[ic] << ",";
  }
  cout << endl;
  TCanvas *c1;
  c1 = new TCanvas("c1", "Flow analysis results", 100, 10, 800, 600);

  c1->GetFrame()->SetBorderSize(12);

  c1->cd();

  gStyle->SetOptStat(0);

  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetHistFillColor(10);
  gStyle->SetHistFillStyle(0);
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);
  c1->SetBorderMode(0);

  c1->SetFillColor(0);
  float xmin1 = 0.0;
  float xmax1 = 80;
  float ymin1 = 0.0;
  float ymax1 = 1.0;

  char title[800];
  sprintf(title, "EP resolution, 0.05<|#eta|<2.0");

  TH2F *hr2 = new TH2F("hr2", title, 2, xmin1, xmax1, 2, ymin1, ymax1);

  hr2->SetXTitle("Centrality %");
  hr2->SetYTitle("R_{2}{#Psi_{2}}");

  hr2->Draw();

  TGraphErrors *gr1;
  TGraphErrors *gr2;
  TGraphErrors *gr3;

  // const int npt=12;
  gr1 = new TGraphErrors(ncent, cent, res2EW, ecent, eres);
  gr1->SetTitle("EP resolution, 0.05<|#eta|<2.0");
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.2);
  gr1->Draw("P");



  TLegend *legC12 = new TLegend(0.17, .75, 0.39, .87);

  legC12->SetFillColor(0);
  legC12->SetBorderSize(0);
  legC12->Draw();

  float hmax = 0.88;

  // TLatex *harmMark = new TLatex(24, hmax, "Au+Au #sqrt{s_{NN}}=7.7 GeV, UrQMD");
  // harmMark->SetTextFont(47);
  // harmMark->SetTextSize(16);
  // harmMark->Draw("same");

  // legC12->AddEntry(gr1, "EP 0.05<|#eta|<2.0", "lp");
  // legC12->SetFillColor(0);
  // legC12->SetBorderSize(0);
  // legC12->Draw();
  // c1 -> SaveAs("./Graphics/pure/res2.png");
}
