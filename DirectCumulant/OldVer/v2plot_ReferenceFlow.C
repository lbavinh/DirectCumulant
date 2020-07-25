#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TProfile.h"

using namespace std;
#include <fstream>

Double_t sx(TProfile *pr){ // Unbiased estimator for the root of variance (C.3)
  Double_t temp=0;
  Double_t stats[6];
  pr -> GetStats(stats);
  Double_t sumw = stats[0];
  Double_t sumw2 = stats[1];
  pr -> SetErrorOption("s");
  Double_t stdevw = pr -> GetBinError(1);

  temp = stdevw*stdevw/(1-sumw2/sumw/sumw);
  return sqrt(temp);
}

Double_t Cov(TProfile *prxy, TProfile *prx, TProfile *pry){
  Double_t temp=0;
  Double_t stats[6];
  prxy -> GetStats(stats);
  Double_t sumwxy = stats[0];
  Double_t meanxy = prxy -> GetBinContent(1);

  prx -> GetStats(stats);
  Double_t sumwx = stats[0];
  Double_t meanx = prx -> GetBinContent(1);

  pry -> GetStats(stats);
  Double_t sumwy = stats[0];
  Double_t meany = pry -> GetBinContent(1);
  temp = (meanxy-meanx*meany)/(1-sumwxy/sumwx/sumwy);
  return temp;
}

Double_t Sumwxwy(TProfile *prxy){
  Double_t temp = 0;
  Double_t stats[6];
  prxy -> GetStats(stats);
  temp = stats[0];
  return temp;
}

void plot(TString inFile)
{
  gStyle->SetOptStat(0); // turn of statistic panel
  TFile *file = new TFile(inFile.Data());

  // Temporary variables
  char hname[800];
  Double_t rms; // root of mean squared = standard deviation (temporary variable)
  int nent; // number of entries (temporary variable)
  Double_t err; // standard error (temporary variable)
  TH1F *h; // temporary TH1F for extracting from root file
  TProfile *pr; // temporary TProfile for TProfile extracting from root file
  TProfile *prx, *pry, *prxy; // temporary TProfile for covariance calculation
  Double_t stats[6]; // stats of TProfile

  //==========================================================================================================================

  // Integrated flow calculation

  // Flow estimates
  Double_t v2int;   // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
  Double_t v22int;  // Reference elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
  Double_t cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
  Double_t c22;     // The 2nd order cumulant of 2nd harmonic, c_2{2}
  Double_t v24int;  // Reference elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
  Double_t cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
  Double_t c24;     // The 4th order cumulant of 2nd harmonic, c_2{4} 

  // Statistical error of estimation
  Double_t v2intE;  // Standard error of integrated v_{2}{MC}
  Double_t v22intE; // Standard error of integrated v_{2}{2,QC}
  Double_t v24intE; // Standard error of integrated v_{2}{4,QC}
  Double_t cor2E;   // error of <<2>>
  Double_t c22E;    // error of c_2{2}
  Double_t cor4E;   // error of <<4>>
  Double_t c24E;    // error of c_2{4}
  Double_t sumw2cor2;    // sumw2 of <2>
  Double_t sumwcor2;     // sumw of <2>
  Double_t sumw2cor4;    // sumw2 of <4>
  Double_t sumwcor4;     // sumw of <4>
  Double_t sumwcor24;    // sum(w<2>,w<4>)
  Double_t cov24;        // Cov(<2>,<4>)
  
  // v2{MC}
  pr = (TProfile*) file->Get("hv2MC");
  v2int = pr->GetBinContent(1);
  v22intE = pr -> GetBinError(1);
  
  // v2{2,QC}
  pr = (TProfile*) file->Get("hv22");

  // estimate of the 2-particle reference flow (C.22)
  cor2 = pr->GetBinContent(1);  // <<2>>
  c22 = cor2;                   // c_{2}{2,QC} = <<2>>
  v22int = sqrt(c22);

  // statistical error of the 2-particle reference flow estimate (C.24)
  cor2E = sx(pr);
  pr -> GetStats(stats);
  sumwcor2 = stats[0];
  sumw2cor2 = stats[1];
  v22intE = 0.5*pow(cor2,-0.5)*sqrt(sumw2cor2)/sumwcor2*cor2E;

  // v2{4,QC}
  pr = (TProfile*) file->Get("hv24");

  // estimate of the 4-particle reference flow (C.27)
  cor4 = pr->GetBinContent(1);  // <<4>>
  v24int = pow(2*cor2*cor2-cor4,0.25);

  // statistical error of the 4-particle reference flow estimate (C.28)
  cor4E = sx(pr);
  pr -> GetStats(stats);
  sumwcor4 = stats[0];
  sumw2cor4 = stats[1];

  // calculate covariance of <2> and <4>
  prxy = (TProfile*) file->Get("hcov24");
  prx = (TProfile*) file->Get("hv22");
  pry = (TProfile*) file->Get("hv24");
  cov24 = Cov(prxy,prx,pry);
  sumwcor24 = Sumwxwy(prxy);
  v24intE = pow(2*cor2*cor2-cor4,-1.5)*(sumw2cor2*pow(cor2*cor2E/sumwcor2,2)
          + 1./16.*sumw2cor4*pow(cor4E/sumwcor4,2) - 0.5*cor2*sumwcor24*cov24/sumwcor2/sumwcor4);  
  v24intE = sqrt(v24intE);

  //==========================================================================================================================
  // plotting
  Double_t v2compare[3], v2compareE[3];
  Double_t x[3] = {0.5,1.5,2.5}; // 3 methods for comparison
  Double_t xE[3] = {0};

  v2compare[0]=v2int;
  v2compareE[0]=v2intE;
  v2compare[1]=v22int;
  v2compareE[1]=v22intE;
  v2compare[2]=v24int;
  v2compareE[2]=v24intE;

  TCanvas *c1 = new TCanvas("c1","Integrated flow result",200,100,800,600);
  Double_t ymin = TMath::MinElement(3,v2compare)*0.95;
  Double_t ymax = TMath::MaxElement(3,v2compare)*1.05;
  TH2F *hr3 = new TH2F("hr3","Integrated elliptic flow result", 3,0,3,10,ymin,ymax);
  hr3->SetYTitle("v_{n}");
  // Set name of methods on X axis
  hr3->SetCanExtend(TH1::kAllAxes);
  const char *method[3]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}"};
  TAxis* a = hr3 -> GetXaxis();
  hr3 -> Fill(method[0],(ymin+ymax)/2,1);
  hr3 -> Fill(method[1],(ymin+ymax)/2,1);
  hr3 -> Fill(method[2],(ymin+ymax)/2,1);
  hr3->GetXaxis()->SetLabelSize(0.05);
  a->SetNdivisions(300); // 3 division, 0 sub-division
  hr3->Draw();

  // Draw reference elliptic flow
  auto gr4 = new TGraphErrors(3,x,v2compare,xE,v2compareE);
  gr4->SetMarkerColor(kRed);
  gr4->SetMarkerStyle(20);
  gr4->SetMarkerSize(1.3);
  gr4->Draw("P");

  // Set a shade between error of v_{2}{MC}
  TGraph *grshade = new TGraph(8);
  for (Int_t i=0; i<4; i++) {
    grshade->SetPoint(i,i+0.005,v2compare[0]+v2compareE[0]);
    grshade->SetPoint(4+i,3+0.005-i,v2compare[0]-v2compareE[0]);
  }
  grshade -> SetFillStyle(1001);
  grshade -> SetFillColor(18);
  grshade -> Draw("f");

  // TLatex shows pT range of RFP
  char text[800];
  sprintf(text,"#splitline{Nonflow: pair-wise (rate: 25%)}{#splitline{M=250#pm50}{#splitline{5#upoint10^{6} events}{RFP: %2.1f < p_{T} < %2.1f GeV/c}}}",minptRFP,maxptRFP);
  Double_t ylatex = ymax*0.985;
  Double_t xlatex = 0.1;
  TLatex *latex = new TLatex(xlatex,ylatex,text);
  latex -> SetTextFont(62);
  latex -> SetTextSize(0.04);
  latex -> SetTextAlign(13);
  latex -> Draw();

  // ofstream ofile2("v2int.txt");
  // ofile2 << "v2";
  // for(int i=0; i<3; i++){
  // ofile2 << "\t" << v2compare[i];
  // }
  // ofile2 << endl;
  // ofile2 << "E(v2)";
  // for(int i=0; i<3; i++){
  // ofile2 << "\t" << v2compareE[i];
  // }
  // ofile2 << endl;
}

void v2plot_ReferenceFlow(){
  plot("v2QC_5mil_v2cent.root");
}