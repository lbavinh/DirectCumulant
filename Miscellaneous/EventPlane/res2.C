#include "TFile.h"
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <iostream>
#include "TLine.h"
#include "TMath.h"


void res2(Int_t mEnergy = 6)
{

TFile *file = new TFile("sum.root");
  
char hname1[800];
char title[800];



 
 float res2tpcEW[6];
 float res2rxnEW[6]; 
 float res2bbcEW[6];

float cent[6]={5,15,25,35,45,55};
float eres[6];
float ecent[6];
 
for (int ic=0; ic<6; ic++) {

(void) sprintf(hname1,"HRes_%i_%i_%i",0,0,ic);
TH1F *h3 = (TH1F*) file->Get(hname1);
res2tpcEW[ic]=sqrt(h3->GetMean());

(void) sprintf(hname1,"HRes_%i_%i_%i",0,1,ic);
TH1F *h4 = (TH1F*) file->Get(hname1);
res2rxnEW[ic]=sqrt(h4->GetMean());

(void) sprintf(hname1,"HRes_%i_%i_%i",0,2,ic);
TH1F *h5 = (TH1F*) file->Get(hname1);
res2bbcEW[ic]=sqrt(h5->GetMean());

 eres[ic]=0.01;
 ecent[ic]=0.03;



 cout << res2bbcEW[ic] <<",";
  
 }

 TCanvas *c1;
 c1 = new TCanvas("c1","Flow analysis results",100,10,500,500);
  
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
  float xmin1=0.0;
  float xmax1=60;
  float ymin1=0.0;
  float ymax1=1.0;



sprintf(title,"");


 TH2F *hr2 = new TH2F("hr2",title, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("Centrality %");
  hr2->SetYTitle("R_{2}{#Psi_{2}}");



  hr2->Draw();


  TGraphErrors *gr1;
  TGraphErrors *gr2;
  TGraphErrors *gr3;




  // const int npt=12;
 gr1 = new TGraphErrors(6,cent,res2tpcEW,ecent,eres);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kRed);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.2);
 gr1->Draw("P");



  // const int npt=12;
 gr2 = new TGraphErrors(6,cent,res2rxnEW,ecent,eres);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kRed);
 gr2->SetMarkerStyle(24);
 gr2->SetMarkerSize(1.2);
 gr2->Draw("P");




  // const int npt=12;
 gr3 = new TGraphErrors(6,cent,res2bbcEW,ecent,eres);
 gr3->SetTitle("TGraphErrors Example ");
 gr3->SetMarkerColor(kBlue);
 gr3->SetMarkerStyle(21);
 gr3->SetMarkerSize(1.2);
 gr3->Draw("P");


//TF1 *f1 = new TF1("f1","[0]+[1]*(x)+[2]/x+[3]*x*x",5,55);
//gr3->Fit("f1","R+");
//gr3->Draw("P");



 TLegend *legC12 = new TLegend(0.17,.75,0.39,.87);

 legC12->SetFillColor(0);
 legC12->SetBorderSize(0);
 legC12->Draw();


 float hmax=0.88;
 

TLatex* harmMark = new TLatex(24, hmax, "Au+Au #sqrt{s_{NN}}=7.7 GeV, UrQMD");
        harmMark->SetTextFont(47);
        harmMark->SetTextSize(16);
	harmMark->Draw("same");


legC12->AddEntry(gr1,"EP 0.1<|#eta|< 1","lp");
legC12->AddEntry(gr2,"EP 1<|#eta|< 3","lp");
legC12->AddEntry(gr3,"EP 3<|#eta|< 5","lp");



 legC12->SetFillColor(0);
 legC12->SetBorderSize(0);
 legC12->Draw();





}
