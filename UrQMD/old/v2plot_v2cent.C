#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFrame.h"

using namespace std;
#include <fstream>
void Cosmetics(Int_t &wtopx, Int_t &wtopy, Int_t &ww, Int_t &wh ){
  gStyle->SetOptStat(0);
  // Set Canvas Resolution
  // 	wtopx,wtopy	are the pixel coordinates of the top left corner of the canvas
  // (if wtopx < 0) the menubar is not shown)
  wtopx = 100;
  wtopy = 10;
  ww = 800; // is the canvas size in pixels along X 
  wh = 600; // is the canvas size in pixels along Y
}

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
  static const Int_t ncent = 8;
  static const Double_t bin_cent[ncent] = {5,15,25,35,45,55,65,75};
  Double_t bin_centE[ncent]={0};
  Int_t wtopx, wtopy, ww, wh;
  Cosmetics(wtopx, wtopy, ww, wh);
  TFile *file = new TFile(inFile.Data());

  // Temporary variables

  char hname[800];
  Double_t rms; // root of mean squared = standard deviation (temporary variable)
  int nent; // number of entries (temporary variable)
  Double_t err; // standard error (temporary variable)
  TH1F *h; // temporary TH1F for extracting from root file
  TProfile *pr; // temporary TProfile for TProfile extracting from root file
  TProfile *prx, *pry, *prxy;

  Double_t stats[6]; // stats of TProfile

  //==========================================================================================================================

  // Integrated flow calculation

  Double_t v2int[ncent];  // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
  Double_t v2intE[ncent]; // Standard error of integrated v_{2}{MC}

  Double_t v22int[ncent];  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
  Double_t v22intE[ncent]; // Standard error of integrated v_{2}{2,QC}
  Double_t cor2[ncent];    // The average all-event 2-particle correlation of RFP, <<2>>
  Double_t cor2E[ncent];   // error of <<2>>
  Double_t c22[ncent];     // The 2nd order cumulant of 2nd harmonic, c_2{2}
  Double_t c22E[ncent];    // error of c_2{2}

  Double_t v24int[ncent];  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
  Double_t v24intE[ncent]; // Standard error of integrated v_{2}{4,QC}
  Double_t cor4[ncent];    // The average all-event 4-particle correlation of RFP, <<4>>
  Double_t cor4E[ncent];   // error of <<4>>
  Double_t c24[ncent];     // The 4th order cumulant of 2nd harmonic, c_2{4} 
  Double_t c24E[ncent];    // error of c_2{4}

  Double_t sumw2cor2[ncent];    // sumw2 of <2>
  Double_t sumwcor2[ncent];     // sumw of <2>
  Double_t sumw2cor4[ncent];    // sumw2 of <4>
  Double_t sumwcor4[ncent];     // sumw of <4>

  Double_t sumwcor24[ncent];    // sum(w<2>,w<4>)
  Double_t cov24[ncent];        // Cov(<2>,<4>)

  for (int i=0; i<ncent; i++){ // loop over centrality bin
    sprintf(hname,"hv2MC_cent%d",i);
    pr = (TProfile*) file->Get(hname);
    v2int[i] = pr -> GetBinContent(1);
    v2intE[i] = pr -> GetBinError(1);
    // stat. error is calculated refer to
    // Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider. 
    // Appendix C
    
    // v2{2,QC}
    sprintf(hname,"hv22_cent%d",i);
    pr = (TProfile*) file->Get(hname);
    // v22 estimation
    cor2[i] = pr->GetBinContent(1);     // <<2>>
    c22[i] = cor2[i];                   // c_{2}{2,QC} = <<2>>
    v22int[i] = sqrt(c22[i]);
    // statistical error of the 2-particle reference flow estimate (C.24)
    cor2E[i] = sx(pr);
    pr -> GetStats(stats);
    sumwcor2[i] = stats[0];
    sumw2cor2[i] = stats[1];
    v22intE[i] = 0.5*pow(cor2[i],-0.5)*sqrt(sumw2cor2[i])/sumwcor2[i]*cor2E[i];


    // v2{4,QC}
    sprintf(hname,"hv24_cent%d",i);
    pr = (TProfile*) file->Get(hname);
    // v24 estimation
    cor4[i] = pr->GetBinContent(1);  // <<4>>
    v24int[i] = pow(2.*cor2[i]*cor2[i]-cor4[i],0.25);
    // statistical error of the 4-particle reference flow estimate (C.28)
    cor4E[i] = sx(pr);
    pr -> GetStats(stats);
    sumwcor4[i] = stats[0];
    sumw2cor4[i] = stats[1];
    // calculate covariance of <2> and <4>
    sprintf(hname,"hcov24_cent%d",i);
    prxy = (TProfile*) file->Get(hname);
    sprintf(hname,"hv22_cent%d",i);
    prx = (TProfile*) file->Get(hname);
    sprintf(hname,"hv24_cent%d",i);
    pry = (TProfile*) file->Get(hname);
    cov24[i] = Cov(prxy,prx,pry);
    sumwcor24[i] = Sumwxwy(prxy);
    v24intE[i] = pow(2*cor2[i]*cor2[i]-cor4[i],-1.5)*(sumw2cor2[i]*pow(cor2[i]*cor2E[i]/sumwcor2[i],2)
            + 1./16.*sumw2cor4[i]*pow(cor4E[i]/sumwcor4[i],2) - 0.5*cor2[i]*sumwcor24[i]*cov24[i]/sumwcor2[i]/sumwcor4[i]);  
    v24intE[i] = sqrt(v24intE[i]);
  } // end of loop over centrality bin

  for (int i=0;i<ncent;i++){
    cout << v2int[i] << " " << v22int[i] << " " << v24int[i] << endl;
  }
  // plotting

  auto c2 = new TCanvas("c2","v_{2} vs cent",wtopx,wtopy,ww,wh);
  Double_t xmin = 0.;
  Double_t xmax = 80.;
  //Double_t ymin = TMath::MinElement(ncent,v2int)*0.9;
  Double_t ymin = -0.02;
  Double_t ymax = TMath::MaxElement(ncent,v2int)*2.;
  TH2F *hr3 = new TH2F("hr3","v_{2} vs cent;cent, %; v_{2}", ncent,xmin,xmax,10,ymin,ymax);
  hr3->Draw();

  auto gr1 = new TGraphErrors(ncent,bin_cent,v2int,bin_centE,v2intE);
  gr1->SetTitle("v2MC");
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(25);
  gr1->SetMarkerSize(1.3);
  gr1->Draw("P");

  auto gr2 = new TGraphErrors(ncent,bin_cent,v22int,bin_centE,v22intE);
  gr2->SetTitle("v22");
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.3);
  gr2->Draw("P");

  auto gr3 = new TGraphErrors(ncent,bin_cent,v24int,bin_centE,v24intE);
  gr3->SetTitle("v24");
  gr3->SetMarkerColor(8);
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerSize(1.3);
  gr3->Draw("P");

  // legend
  Double_t xlegtl = 0.12;
  Double_t ylegtl = 0.88;
  Double_t xlegbr = 0.4;
  Double_t ylegbr = 0.75;
  TLegend *leg = new TLegend(xlegtl,ylegtl,xlegbr,ylegbr);
  leg -> AddEntry(gr1,"v_{2}{MC}","p");
  leg -> AddEntry(gr2,"v_{2}{2,QC}","p");
  leg -> AddEntry(gr3,"v_{2}{4,QC}","p");
  leg -> SetFillColor(0);
  leg -> SetTextSize(0.04);
  leg -> SetTextFont(62);
  leg -> SetBorderSize(0);
  leg -> Draw();

  // TLatex shows pT range of RFP
  char text[800];
  sprintf(text,"#splitline{MultMean=250}{#splitline{}{-2.5#leq#eta#leq-0.05}}");
  Double_t ylatex = ymax*0.985;
  Double_t xlatex = xmax*0.985;
  TLatex *latex = new TLatex(xlatex,ylatex,text);
  latex -> SetTextFont(62);
  latex -> SetTextSize(0.04);
  latex -> SetTextAlign(13);
  latex -> Draw();

  TFile *outFile = new TFile("v2cent.root","recreate");
  outFile -> cd();
  gr1 -> Write("v2MC");
  gr2 -> Write("v22");
  gr3 -> Write("v24");
  outFile -> Close();
}

void v2plot_v2cent(){
  plot("./ROOTFile/v2QC_etagap_eta2.5.root");
}