#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TFrame.h"
TLegend *leg;
using namespace std;
#include <fstream>
void Cosmetics(Int_t &wtopx, Int_t &wtopy, Int_t &ww, Int_t &wh ){
  gStyle->SetOptStat(0);
  // Set Canvas Resolution
  // 	wtopx,wtopy	are the pixel coordinates of the top left corner of the canvas
  // (if wtopx < 0) the menubar is not shown)
  wtopx = 200;
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

TMultiGraph* MultiGraph(TString inFile)
{
  const int npt = 24; // number of pT bin
  Float_t markerSize = 1;


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
  TProfile *prx, *pry, *prxy; // for covariance calculation
  Double_t stats[6]; // stats of TProfile

  //==========================================================================================================================

  // Integrated flow calculation

  Double_t v2int;  // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
  Double_t v2intE; // Standard error of integrated v_{2}{MC}

  Double_t v22int;  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
  Double_t v22intE; // Standard error of integrated v_{2}{2,QC}
  Double_t cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
  Double_t cor2E;   // error of <<2>>
  Double_t c22;     // The 2nd order cumulant of 2nd harmonic, c_2{2}
  Double_t c22E;    // error of c_2{2}

  Double_t v24int;  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
  Double_t v24intE; // Standard error of integrated v_{2}{4,QC}
  Double_t cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
  Double_t cor4E;   // error of <<4>>
  Double_t c24;     // The 4th order cumulant of 2nd harmonic, c_2{4} 
  Double_t c24E;    // error of c_2{4}

  Double_t sumw2cor2;    // sumw2 of <2>
  Double_t sumwcor2;     // sumw of <2>
  Double_t sumw2cor4;    // sumw2 of <4>
  Double_t sumwcor4;     // sumw of <4>

  Double_t sumwcor24;    // sum(w<2>,w<4>)
  Double_t cov24;        // Cov(<2>,<4>)

  pr = (TProfile*) file->Get("hv2MC");
  v2int = pr -> GetBinContent(1);
  v2intE = pr -> GetBinError(1);

  // https://en.wikipedia.org/wiki/Weighted_arithmetic_mean // Weighted sample variance // Reliability weights
  // Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider. 
  // Appendix C
  
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

  // auto c2 = new TCanvas("c2","flow result",wtopx,wtopy,ww,wh);
  // Double_t ymin2 = TMath::MinElement(3,v2compare)*0.98;
  // Double_t ymax2 = TMath::MaxElement(3,v2compare) + TMath::MaxElement(3,v2compareE)*1.1;
  // TH2F *hr3 = new TH2F("hr3","Reference elliptic flow", 3,0,3,10,ymin2,ymax2);
  // hr3->SetYTitle("v_{n}");
  // // Set name of methods on X axis
  // hr3->SetCanExtend(TH1::kAllAxes);
  // const char *method[3]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}"};
  // TAxis* a = hr3 -> GetXaxis();
  // hr3 -> Fill(method[0],(ymin2+ymax2)/2,1);
  // hr3 -> Fill(method[1],(ymin2+ymax2)/2,1);
  // hr3 -> Fill(method[2],(ymin2+ymax2)/2,1);
  // hr3->GetXaxis()->SetLabelSize(0.05);
  // a->SetNdivisions(300); // 3 division, 0 sub-division
  // hr3->Draw();

  // // Set a shade between error of v_{2}{MC}
  // TGraph *grshade = new TGraph(8);
  // for (Int_t i=0; i<4; i++) {
  //   grshade->SetPoint(i,i+0.005,v2compare[0]+v2compareE[0]);
  //   grshade->SetPoint(4+i,3+0.005-i,v2compare[0]-v2compareE[0]);
  // }
  // grshade -> SetFillStyle(1001);
  // grshade -> SetFillColor(18);
  // grshade -> Draw("f");
  // auto gr4 = new TGraphErrors(3,x,v2compare,xE,v2compareE);
  // gr4->SetMarkerColor(kRed);
  // gr4->SetMarkerStyle(20);
  // gr4->SetMarkerSize(1.3);
  // gr4->Draw("P");

  // // TLatex shows pT range of RFP
  // char text2[800];
  // sprintf(text2,"#splitline{MultMean=250}{#splitline{5#upoint10^{6} events}{#splitline{RFP: #eta<0}{POI: #eta>0}}}");
  // Double_t ylatex = ymax2*0.985;
  // Double_t xlatex = 0.1;
  // TLatex *latex = new TLatex(xlatex,ylatex,text2);
  // latex -> SetTextFont(62);
  // latex -> SetTextSize(0.04);
  // latex -> SetTextAlign(13);
  // latex -> Draw();

  //==========================================================================================================================

  // Differential flow calculation

  Double_t hpt[npt]; // transverse momentum distribution in npt bin of pT
  Double_t hpte[npt]; // error bin pT = 0.001

  Double_t v2[npt]; // distribution of v2 in given pT bin
  Double_t v2e[npt]; // standard error of v2 in given pT bin

  for(int i=0; i<npt; i++){
    sprintf(hname,"hpt_%i",i);
    TH1F *h = (TH1F*) file->Get(hname);
    hpt[i]= h->GetMean();
    hpte[i] = 0.0;
    // cout << hpt[i] << endl;

    sprintf(hname,"hv2pt_%i",i);
    h = (TH1F*) file->Get(hname);
    v2[i] = h->GetMean();
    rms = h->GetRMS();
    nent = h->GetEntries();
    err = rms/sqrt(nent);
    v2e[i] = err;
  }
  Double_t cor2Red[npt];         // Differential 2nd order cumulant d_{2}{2} = <<2'>>
  Double_t cor2RedE[npt];        // Error of d_{2}{2}
  Double_t v22dif[npt];      // Differential elliptic flow v'_{2}{2} extracted from 2nd order cumulants
                          // v'_{2}{2} = d_{2}{2} / sqrt( c_{2}{2} )
  Double_t v22difE[npt];     // Error of v'_{2}{2}
  
  Double_t cor4Red[npt];    // Reduced average all-event 4-particle correlation <<4'>>
  Double_t cor4RedE[npt];   // Error of <<4'>>
  Double_t d24[npt];         // Differential 4th order cumulant d_{2}{4} = <<4'>> - 2*<<2>>*<<2'>>
  Double_t d24E[npt];        // Error of d_{2}{4}
  Double_t v24dif[npt];      // Differential elliptic flow v'_{2}{4} extracted from 4th order cumulants
                          // v'_{2}{4} = -d_{2}{4} / pow( -c_{2}{4} , 3/4 )
  Double_t v24difE[npt];     // Error of v'_{2}{4}

  Double_t sumwcor22prime[npt];        // sum(w(<2>)*w(<2'>))
  Double_t cov22prime[npt];            // Cov(<2>,<2'>)
  Double_t sumwcor24prime[npt];        // sum(w(<2>)*w(<4'>))
  Double_t cov24prime[npt];            // Cov(<2>,<4'>)
  Double_t sumwcor42prime[npt];        // sum(w(<4>)*w(<2'>))
  Double_t cov42prime[npt];            // Cov(<4>,<2'>)
  Double_t sumwcor44prime[npt];        // sum(w(<4>)*w(<4'>))
  Double_t cov44prime[npt];            // Cov(<4>,<4'>)
  Double_t sumwcor2prime4prime[npt];   // sum(w(<2'>)*w(<4'>))
  Double_t cov2prime4prime[npt];       // Cov(<2'>,<4'>)

  Double_t sumw2cor2red[npt]; // sumw2 of <2'>
  Double_t sumwcor2red[npt];  // sumw of <2'>    
  Double_t sumw2cor4red[npt]; // sumw2 of <4'>
  Double_t sumwcor4red[npt];  // sumw of <4'>

  for(int i=0; i<npt; i++){ // loop for all pT bin
    
    // 2-particle correlations
    sprintf(hname,"hv22pt_%i",i);
    pr = (TProfile*) file->Get(hname);

    // estimate of the 2-particle differential flow (C.41)
    cor2Red[i] = pr->GetBinContent(1);
    v22dif[i] = cor2Red[i] / sqrt(c22);

    // statistical error of the 2-particle differential flow estimate (C.42)
    cor2RedE[i] = sx(pr);
    pr -> GetStats(stats);
    sumwcor2red[i] = stats[0];
    sumw2cor2red[i] = stats[1];

      // calculate covariance of <2> and <2'>
    
    prx = (TProfile*) file->Get("hv22");
    sprintf(hname,"hcov22prime_%i",i);
    prxy = (TProfile*) file->Get(hname);
    sprintf(hname,"hv22pt_%i",i);
    pry = (TProfile*) file->Get(hname);
    cov22prime[i] = Cov(prxy,prx,pry);
    sumwcor22prime[i] = Sumwxwy(prxy);   


    v22difE[i] = 0.25*pow(cor2,-3.)*(cor2Red[i]*cor2Red[i]*sumw2cor2/sumwcor2/sumwcor2*cor2E*cor2E
               + 4.*cor2*cor2*sumw2cor2red[i]*pow(cor2RedE[i]/sumwcor2red[i],2.) - 4.*cor2*cor2Red[i]
               * sumwcor22prime[i]/sumwcor2/sumwcor2red[i]*cov22prime[i]);
    v22difE[i] = sqrt(v22difE[i]);

    // 4-particle correlations
    sprintf(hname,"hv24pt_%i",i);
    pr = (TProfile*) file->Get(hname);

    // estimate of the 4-particle differential flow (C.45)
    cor4Red[i] = pr->GetBinContent(1);
    v24dif[i] = (2*cor2*cor2Red[i]-cor4Red[i])*pow(2*cor2*cor2-cor4,-0.75);

    // statistical error of the 4-particle differential flow estimate (C.46)
    cor4RedE[i] = sx(pr);
    pr -> GetStats(stats);
    sumwcor4red[i] = stats[0];
    sumw2cor4red[i] = stats[1];

      // calculate covariance of <2> and <4'>
    
    prx = (TProfile*) file->Get("hv22");
    sprintf(hname,"hcov24prime_%i",i);
    prxy = (TProfile*) file->Get(hname);
    sprintf(hname,"hv24pt_%i",i);
    pry = (TProfile*) file->Get(hname);
    cov24prime[i] = Cov(prxy,prx,pry);
    sumwcor24prime[i] = Sumwxwy(prxy);

      // calculate covariance of <4> and <2'>
    
    prx = (TProfile*) file->Get("hv24");
    sprintf(hname,"hcov42prime_%i",i);
    prxy = (TProfile*) file->Get(hname);
    sprintf(hname,"hv22pt_%i",i);
    pry = (TProfile*) file->Get(hname);
    cov42prime[i] = Cov(prxy,prx,pry);
    sumwcor42prime[i] = Sumwxwy(prxy);

      // calculate covariance of <4> and <4'>
    
    prx = (TProfile*) file->Get("hv24");
    sprintf(hname,"hcov44prime_%i",i);
    prxy = (TProfile*) file->Get(hname);
    sprintf(hname,"hv24pt_%i",i);
    pry = (TProfile*) file->Get(hname);
    cov44prime[i] = Cov(prxy,prx,pry);
    sumwcor44prime[i] = Sumwxwy(prxy);

      // calculate covariance of <2'> and <4'>
    sprintf(hname,"hv22pt_%i",i);
    prx = (TProfile*) file->Get(hname);
    sprintf(hname,"hcov2prime4prime_%i",i);
    prxy = (TProfile*) file->Get(hname);
    sprintf(hname,"hv24pt_%i",i);
    pry = (TProfile*) file->Get(hname);
    cov2prime4prime[i] = Cov(prxy,prx,pry);
    sumwcor2prime4prime[i] = Sumwxwy(prxy);     

    v24difE[i] = pow(2.*cor2*cor2-cor4,-3.5)*
    (pow(2.*cor2*cor2*cor2Red[i]-3*cor2*cor4Red[i]+2.*cor4*cor2Red[i],2.)
    * sumw2cor2*pow(cor2E/sumwcor2,2.)
    + 9./16.*pow(2.*cor2*cor2Red[i]-cor4Red[i],2.)*sumw2cor4*pow(cor4E/sumwcor4,2.)
    + 4.*cor2*cor2*pow(2*cor2*cor2-cor4,2.)*sumw2cor2red[i]*pow(cor2RedE[i]/sumwcor2red[i],2.)
    + pow(2*cor2*cor2-cor4,2.)*sumw2cor4red[i]*pow(cor4RedE[i]/sumwcor4red[i],2.)
    - 1.5*(2*cor2*cor2Red[i]-cor4Red[i])
    * (2.*cor2*cor2*cor2Red[i]-3.*cor2*cor4Red[i]+2.*cor4*cor2Red[i])
    * sumwcor24/sumwcor2/sumwcor4*cov24
    - 4.*cor2*(2.*cor2*cor2-cor4)
    * (2.*cor2*cor2*cor2Red[i]-3.*cor2*cor4Red[i]+2*cor4*cor2Red[i])
    * sumwcor22prime[i]/sumwcor2/sumwcor2red[i]*cov22prime[i]
    + 2.*(2.*cor2*cor2-cor4)
    * (2.*cor2*cor2*cor2Red[i]-3.*cor2*cor4Red[i]+2.*cor4*cor2Red[i])
    * sumwcor24prime[i]/sumwcor2/sumwcor4red[i]*cov24prime[i]
    + 3.*cor2*(2.*cor2*cor2-cor4)*(2.*cor2*cor2Red[i]-cor4Red[i])
    * sumwcor42prime[i]/sumwcor4/sumwcor2red[i]*cov42prime[i]
    - 1.5*(2*cor2*cor2-cor4)*(2.*cor2*cor2Red[i]-cor4Red[i])
    * sumwcor44prime[i]/sumwcor4/sumwcor4red[i]*cov44prime[i]
    - 4.*cor2*pow(2.*cor2*cor2-cor4,2.)*sumwcor2prime4prime[i]/sumwcor2red[i]/sumwcor4red[i]*cov2prime4prime[i]
    );
    v24difE[i] = sqrt(v24difE[i]);
  } // end of loop for all pT bin
  
    

  
  auto gr1 = new TGraphErrors(npt,hpt,v2,hpte,v2e);
  gr1->SetMarkerColor(kRed+1);
  gr1->SetMarkerStyle(25);
  gr1->SetMarkerSize(1.3);
  gr1->SetDrawOption("P");

  Double_t hptv22[npt], hptv24[npt];
  for (int i=0; i<npt; i++) {
    hptv22[i]=hpt[i]+0.;
    hptv24[i]=hpt[i]-0.;
  }

  auto gr2 = new TGraphErrors(npt,hptv22,v22dif,hpte,v22difE);
  gr2->SetMarkerColor(kGreen+1);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.3);
  gr2->SetDrawOption("P");

  auto gr3 = new TGraphErrors(npt,hptv24,v24dif,hpte,v24difE);
  gr3->SetMarkerColor(kAzure+2);
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerSize(1.3);
  gr3->SetDrawOption("P");

  leg = new TLegend(0.11,.89,0.4,.78);
  leg -> AddEntry(gr1,"V_{2} [Gen]","p");
  leg -> AddEntry(gr2,"V_{2}{2,QC}","p");
  leg -> AddEntry(gr3,"V_{2}{4,QC}","p");
  leg -> SetFillColor(0);
  leg -> SetTextSize(0.04);
  leg -> SetTextFont(62);
  leg -> SetBorderSize(0);


  TMultiGraph *mg = new TMultiGraph();
  mg -> Add(gr1);
  mg -> Add(gr2);
  mg -> Add(gr3);


  return mg;
}

// void v2plot_v2pt(){

  
//   // plot("v2QC_5mil_v2pt_cent10-20.root");
//   // plot("v2QC_5mil_v2pt_cent20-30.root");
//   // plot("v2QC_5mil_v2pt_cent20-30.root");
//   // plot("v2QC_5mil_v2pt_cent20-30.root");
//   // plot("v2QC_5mil_v2pt_cent20-30.root");
//   // plot("v2QC_5mil_v2pt_cent20-30.root");
//   // plot("v2QC_5mil_v2pt_cent20-30.root");
//   // plot("v2QC_5mil_v2pt_cent40-50.root");
// }

TStyle* makeplotstyle()
{
	TStyle *style = new TStyle("style", "Style for Summary Plots");
	style->SetCanvasBorderMode(0);//removes the yellow frame around the canvas
	style->SetFrameBorderMode(0);//removes red highlighting
	style->SetPadTickX(1);//ticks on both pad sides 
	style->SetPadTickY(1);
	style->SetNdivisions(508, "X");
	style->SetNdivisions(508, "Y");
  style->SetCanvasColor(0);

  // style->SetStatBorderSize(1);
  // style->SetFrameFillColor(0);
  // style->SetTitleFillColor(0);

	return style;
}

void v2plot_v2pt_multipads() {

	// TStyle *tsty = makeplotstyle();
	// tsty->cd();
	//gROOT->ForceStyle();
  gStyle->SetPadTickX(1); //ticks on both pad sides 
  gStyle->SetPadTickY(1);
  TCanvas *c1 = new TCanvas("c1","multipads",200,10,1920,1080);
  // c1->SetFillColor(0);
  gStyle->SetOptStat(0);
  c1->Divide(3,2,0,0);
  Double_t xmin=0.;
  Double_t xmax=2.6;
  Double_t ymin=0.;
  Double_t ymax=0.25;
  TMultiGraph *mg[8];
  TH2F *h[8];
  char fname[800];
  TLatex *latex;
  for(int i=1; i<7; i++){
    sprintf(fname,"v2QC_5mil_v2pt_cent%i-%i.root",10*(i),10*(i+1));
    mg[i] = new TMultiGraph();
    mg[i] = MultiGraph(fname);
    h[i] = new TH2F("","",5,xmin,xmax,5,ymin,ymax);
    c1 -> cd(i);
    h[i] -> Draw();
    h[i] -> GetXaxis() -> SetTitle("p_{T}, GeV/c");
    h[i] -> GetYaxis() -> SetTitle("v_{2}");
    mg[i]->Draw("P");
    mg[i]->SetTitle("");
    leg -> Draw();

    char text1[800];
    sprintf(text1,"cent: %i-%i%%",10*(i),10*(i+1));
    latex = new TLatex(xmax*0.98,ymin+0.02,text1);
    latex -> SetTextFont(62);
    latex -> SetTextSize(0.04);
    latex -> SetTextAlign(31);
    latex -> Draw();
  }


}