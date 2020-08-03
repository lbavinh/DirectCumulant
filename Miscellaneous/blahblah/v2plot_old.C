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
  wtopx = 200;
  wtopy = 10;
  ww = 1920; // is the canvas size in pixels along X 
  wh = 1080; // is the canvas size in pixels along Y
}
void plot(TString inFile)
{
  static const float maxptRFP = 1.0; // max pt of RFP
  static const float minptRFP = 0.2; // min pt of RFP
  Int_t wtopx, wtopy, ww, wh;
  Cosmetics(wtopx, wtopy, ww, wh);
  TFile *file = new TFile(inFile.Data());
  // Temporary variables

  char hname[800];
  float rms; // root of mean squared = standard deviation (temporary variable)
  int nent; // number of entries (temporary variable)
  float err; // standard error (temporary variable)
  TH1F *h; // temporary TH1F for extracting from root file
  TProfile *pr; // temporary TProfile for TProfile extracting from root file

  //==========================================================================================================================

  // Integrated flow calculation

  float v2int;  // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
  float v2intE; // Standard error of integrated v_{2}{MC}

  float v22int;  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
  float v22intE; // Standard error of integrated v_{2}{2,QC}
  float cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
  float cor2E;   // error of <<2>>
  float c22;     // The 2nd order cumulant of 2nd harmonic, c_2{2}
  float c22E;    // error of c_2{2}

  float v24int;  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
  float v24intE; // Standard error of integrated v_{2}{4,QC}
  float cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
  float cor4E;   // error of <<4>>
  float c24;     // The 4th order cumulant of 2nd harmonic, c_2{4} 
  float c24E;    // error of c_2{4}

  h = (TH1F*) file->Get("hv2");
  v2int = h->GetMean();
  rms = h->GetRMS();
  nent = h->GetEntries();
  err = rms/sqrt(nent);
  v2intE = err;

  pr = (TProfile*) file->Get("hv22");
  cor2 = pr->GetBinContent(1);
  cor2E = pr->GetBinError(1);
  c22 = cor2;
  c22E = cor2E;
  v22int = sqrt(c22);
  v22intE = 0.5*pow(c22,-0.5)*c22E;

  pr = (TProfile*) file->Get("hv24");
  cor4 = pr->GetBinContent(1);
  cor4E = pr->GetBinError(1);
  c24 = cor4-2*cor2*cor2;
  c24E = sqrt(cor4E*cor4E+pow(4*cor2*cor2E,2));
  v24int = pow(-c24,0.25);
  v24intE = 0.25*pow(-c24,-0.75)*c24E;

  float v2compare[3], v2compareE[3];
  float x[3] = {0.5,1.5,2.5}; // 3 methods for comparison
  float xE[3] = {0};

  v2compare[0]=v2int;
  v2compareE[0]=v2intE;
  v2compare[1]=v22int;
  v2compareE[1]=v22intE;
  v2compare[2]=v24int;
  v2compareE[2]=v24intE;

  auto c2 = new TCanvas("c2","Integrated flow result",wtopx,wtopy,ww,wh);
  float ymin2=v2int-v2intE*15;
  float ymax2=v2int+v2intE*15;
  TH2F *hr3 = new TH2F("hr3","Integrated flow result", 3,0,3,10,ymin2,ymax2);
  hr3->SetYTitle("v_{n}");
  // Set name of methods on X axis
  hr3->SetCanExtend(TH1::kAllAxes);
  const char *method[3]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}"};
  TAxis* a = hr3 -> GetXaxis();
  hr3 -> Fill(method[0],(ymin2+ymax2)/2,1);
  hr3 -> Fill(method[1],(ymin2+ymax2)/2,1);
  hr3 -> Fill(method[2],(ymin2+ymax2)/2,1);
  hr3->GetXaxis()->SetLabelSize(0.05);
  a->SetNdivisions(300); // 3 division, 0 sub-division
  hr3->Draw();

  // Set a shade between error of v_{2}{MC}
  TGraph *grshade = new TGraph(8);
  for (Int_t i=0; i<4; i++) {
    grshade->SetPoint(i,i+0.005,v2compare[0]+v2compareE[0]);
    grshade->SetPoint(4+i,3+0.005-i,v2compare[0]-v2compareE[0]);
  }
  grshade -> SetFillStyle(1001);
  grshade -> SetFillColor(18);
  grshade -> Draw("f");
  auto gr4 = new TGraphErrors(3,x,v2compare,xE,v2compareE);
  gr4->SetMarkerColor(kRed);
  gr4->SetMarkerStyle(20);
  gr4->SetMarkerSize(1.3);
  gr4->Draw("P");

  // TLatex shows pT range of RFP
  char text2[800];
  sprintf(text2,"#splitline{M=250#pm50}{#splitline{5#upoint10^{6} events}{RFP: %2.1f < p_{T} < %2.1f GeV/c}}",minptRFP,maxptRFP);
  float ylatex = ymin2*1.002;
  TLatex *latex = new TLatex(0.2,ylatex,text2);
  latex -> SetTextFont(62);latex -> SetTextSize(0.04);
  //latex2 -> SetTextAlign(13);
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

  //==========================================================================================================================

  // Differential flow calculation

  const int npt = 24; // number of pT bin

  float hpt[npt]; // transverse momentum distribution in npt bin of pT
  float hpte[npt]; // error bin pT = 0.001

  float v2[npt]; // distribution of v2 in given pT bin
  float v2e[npt]; // standard error of v2 in given pT bin

  for(int i=0; i<npt; i++){
    sprintf(hname,"hpt_%i",i);
    TH1F *h = (TH1F*) file->Get(hname);
    hpt[i]= h->GetMean();
    hpte[i] = 0.001;
    // cout << hpt[i] << endl;

    sprintf(hname,"hv2pt_%i",i);
    h = (TH1F*) file->Get(hname);
    v2[i] = h->GetMean();
    rms = h->GetRMS();
    nent = h->GetEntries();
    err = rms/sqrt(nent);
    v2e[i] = err;
  }
  float d22[npt];         // Differential 2nd order cumulant d_{2}{2} = <<2'>>
  float d22E[npt];        // Error of d_{2}{2}
  float v22dif[npt];      // Differential elliptic flow v'_{2}{2} extracted from 2nd order cumulants
                          // v'_{2}{2} = d_{2}{2} / sqrt( c_{2}{2} )
  float v22difE[npt];     // Error of v'_{2}{2}

  float corr4Red[npt];    // Reduced average all-event 4-particle correlation <<4'>>
  float corr4RedE[npt];   // Error of <<4'>>
  float d24[npt];         // Differential 4th order cumulant d_{2}{4} = <<4'>> - 2*<<2>>*<<2'>>
  float d24E[npt];        // Error of d_{2}{4}
  float v24dif[npt];      // Differential elliptic flow v'_{2}{4} extracted from 4th order cumulants
                          // v'_{2}{4} = -d_{2}{4} / pow( -c_{2}{4} , 3/4 )
  float v24difE[npt];     // Error of v'_{2}{4}

  for(int i=0; i<npt; i++){ // loop for all pT bin
    sprintf(hname,"hv22pt_%i",i);
    pr = (TProfile*) file->Get(hname);
    d22[i] = pr->GetBinContent(1);
    d22E[i] = pr->GetBinError(1);
    v22dif[i] = d22[i] / sqrt(c22);
    v22difE[i] = sqrt(d22E[i]*d22E[i]/c22+0.25*d22[i]*d22[i]*c22E*c22E*pow(c22,-3));

    sprintf(hname,"hv24pt_%i",i);
    pr = (TProfile*) file->Get(hname);
    corr4Red[i] = pr->GetBinContent(1);
    corr4RedE[i] = pr->GetBinError(1);
    d24[i] = corr4Red[i]-2*d22[i]*c22;
    d24E[i] = sqrt(corr4RedE[i]*corr4RedE[i]+pow(2*c22*d22E[i],2)+pow(2*c22E*d22[i],2));
    v24dif[i] = -d24[i]*pow(-c24,-0.75);
    v24difE[i] = sqrt(pow(-c24,-1.5)*d24E[i]*d24E[i] + 9/16*d24[i]*d24[i]*pow(-c24,-3.5)*c24E*c24E);
  }
  
  auto c1 = new TCanvas("c1","Flow analysis results",wtopx,wtopy,ww,wh);
    
  float xmin1=maxptRFP;
  float xmax1=3.5;
  float ymin1=0.;
  float ymax1=0.3;


  TH2F *hr2 = new TH2F("hr2","v_{n} vs p_{T};p_{T}, GeV/c;v_{n}", 2,xmin1,xmax1,2,ymin1,ymax1);
  
  hr2->Draw();
  
  auto gr1 = new TGraphErrors(npt,hpt,v2,hpte,v2e);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.3);
  //gr1->SetLineWidth(2);
  gr1->Draw("P");

  float hptv22[npt], hptv24[npt];
  for (int i=0; i<npt; i++) {
    hptv22[i]=hpt[i]+0.007;
    hptv24[i]=hpt[i]-0.007;
  }

  auto gr2 = new TGraphErrors(npt,hptv22,v22dif,hpte,v22difE);
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1.3);
  gr2->Draw("P");
  //gr2->SetLineWidth(2);

  auto gr3 = new TGraphErrors(npt,hptv24,v24dif,hpte,v24difE);
  gr3->SetMarkerColor(kGreen);
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerSize(1.3);
  //gr3->SetLineWidth(2);
  gr3->Draw("P");

  TLegend *leg = new TLegend(0.15,.7,0.4,.87);
  leg -> AddEntry(gr1,"V_{2} [Gen]","lp");
  leg -> AddEntry(gr2,"V_{2}{2,QC}","lp");
  leg -> AddEntry(gr3,"V_{2}{4,QC}","lp");
  leg -> SetFillColor(0);
  leg -> SetTextSize(0.04);
  leg -> SetTextFont(62);
  leg -> SetBorderSize(0);
  leg -> Draw();

  TLatex *latex2 = new TLatex(1.1,0.04,text2);
  latex2 -> SetTextFont(62);latex2 -> SetTextSize(0.04);
  //latex2 -> SetTextAlign(13);
  latex2 -> Draw();

  // ofstream ofile("v2pt.txt");
  // ofile.precision(5);
  // ofile << "pT" << "\t\t\tv2(MC)" << "\t\t\tE(v2(MC))" << "\t\t\tv2{2}"
  //       << "\t\t\tE(v2{2})" << "\t\t\tv2{4}" << "\t\t\tE(v2{4})" << endl;
  // for(int i=0; i<npt; i++){
  //   ofile << std::setprecision(5) << hpt[i] << "\t\t\t" << v2[i] << "\t\t\t" << v2e[i]
  //         << "\t\t\t" << v22dif[i] << "\t\t\t" << v22difE[i]
  //         << "\t\t\t" << v24dif[i] << "\t\t\t" << v24difE[i] << endl;
  // }
}

void v2plot_original(){
  plot("v2QC_5mil_ver2.root");
}