#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFrame.h"

using namespace std;
#include <fstream>

void v2plot()
{
  TFile *file = new TFile("v2QC.root");

  // differential flow calculation
  const int npt = 24;

  float hpt[npt];
  float hpte[npt];

  float v2[npt];
  float v2e[npt];

  char hname[800];
  float rms; // root of mean squared = standard deviation
  int nent; // number of entries
  float err; // standard error
  TH1F *h;

  for(int i=0; i<npt; i++){

    sprintf(hname,"hpt_%i",i);
    TH1F *h = (TH1F*) file->Get(hname);
    hpt[i]= h->GetMean();
    hpte[i] = 0.001;
    cout << hpt[i] << endl;

    sprintf(hname,"hv2pt_%i",i);
    h = (TH1F*) file->Get(hname);
    v2[i] = h->GetMean();
    rms = h->GetRMS();
    nent = h->GetEntries();
    err = rms/sqrt(nent);
    v2e[i] = err;

  }

  float c22,c24,cor2,cor4,v22int,v24int;
  float c22E,c24E,cor2E,cor4E,v22intE,v24intE;
  TProfile *pr;

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

  float corr4Red[npt], corr4RedE[npt];
  float d22[npt], d24[npt], d22E[npt], d24E[npt];
  float v22dif[npt], v24dif[npt], v22difE[npt], v24difE[npt];

  for(int i=0; i<npt; i++){
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

  for(int i=0;i<3;i++){
    v22dif[i] = 0.; v22difE[i] = 0.; v24dif[i] = 0.; v24difE[i] = 0.;
  }
  



  auto c1 = new TCanvas("c1","Flow analysis results",200,10,700,550);
    
  c1->GetFrame()->SetBorderSize(12);

  c1->cd(); 
	
  gStyle->SetOptStat(0);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetHistFillColor(10);
  gStyle->SetHistFillStyle(0);
  gStyle->SetOptTitle(1);

  c1->SetBorderMode(0);

  c1->SetFillColor(0);
  float xmin1=0.5;
  float xmax1=2.;
  float ymin1=0.;
  float ymax1=0.3;


  char title1[800];
  sprintf(title1,"V_{n} vs p_{T};p_{T}, GeV/c;v_{n}");
  TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);
  
  hr2->Draw();
  
  auto gr1 = new TGraphErrors(npt,hpt,v2,hpte,v2e);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.3);
  gr1->SetLineWidth(2);
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
  gr2->SetLineWidth(2);

  auto gr3 = new TGraphErrors(npt,hptv24,v24dif,hpte,v24difE);
  gr3->SetMarkerColor(kGreen);
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerSize(1.3);
  gr3->SetLineWidth(2);
  gr3->Draw("P");

  TLegend *leg = new TLegend(0.15,.7,0.6,.87);
  leg->AddEntry(gr1,"V_{2} [Gen]","lp");
  leg->AddEntry(gr2,"V_{2}{2,QC}","lp");
  leg->AddEntry(gr3,"V_{2}{4,QC}","lp");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

  ofstream ofile("v2pt.txt");
  ofile.precision(5);
  ofile << "pT" << "\t\t\tv2(MC)" << "\t\t\tE(v2(MC))" << "\t\t\tv2{2}"
        << "\t\t\tE(v2{2})" << "\t\t\tv2{4}" << "\t\t\tE(v2{4})" << endl;
  for(int i=0; i<npt; i++){
    ofile << std::setprecision(5) << hpt[i] << "\t\t\t" << v2[i] << "\t\t\t" << v2e[i]
          << "\t\t\t" << v22dif[i] << "\t\t\t" << v22difE[i]
          << "\t\t\t" << v24dif[i] << "\t\t\t" << v24difE[i] << endl;
  }

  // integrated flow calculation

  float v2int, v2intE;
  h = (TH1F*) file->Get("hv2");
  v2int = h->GetMean();
  rms = h->GetRMS();
  nent = h->GetEntries();
  err = rms/sqrt(nent);
  v2intE = err;
  float v2compare[3], v2compareE[3];
  float x[3] = {0.5,1.5,2.5};
  float xE[3] = {0};

  v2compare[0]=v2int;
  v2compareE[0]=v2intE;
  v2compare[1]=v22int;
  v2compareE[1]=v22intE;
  v2compare[2]=v24int;
  v2compareE[2]=v24intE;

  auto c2 = new TCanvas("c2","Integrated flow result",200,10,700,550);
  float ymin2=v2int-v2intE*15;
  float ymax2=v2int+v2intE*15;
  TH2F *hr3 = new TH2F("hr3","Integrated flow result", 3,0,3,10,ymin2,ymax2);
  hr3->SetYTitle("v_{n}");
  hr3->SetCanExtend(TH1::kAllAxes);
  const char *method[3]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}"};
  TAxis* a = hr3 -> GetXaxis();
  hr3 -> Fill(method[0],(ymin2+ymax2)/2,1);
  hr3 -> Fill(method[1],(ymin2+ymax2)/2,1);
  hr3 -> Fill(method[2],(ymin2+ymax2)/2,1);
  hr3->GetXaxis()->SetLabelSize(0.05);
  a->SetNdivisions(300);
  // a->ChangeLabel(0,-1,-1,-1,-1,-1,"#v_{2}{MC}");
  // a->ChangeLabel(0,-1,-1,-1,-1,-1,"#v_2{2,QC}");
  // a->ChangeLabel(0,-1,-1,-1,-1,-1,"#v_2{4,QC}");
  hr3->Draw();

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


  ofstream ofile2("v2int.txt");
  ofile2 << "v2";
  for(int i=0; i<3; i++){
  ofile2 << "\t" << v2compare[i];
  }
  ofile2 << endl;
  ofile2 << "E(v2)";
  for(int i=0; i<3; i++){
  ofile2 << "\t" << v2compareE[i];
  }
  ofile2 << endl;  
}
