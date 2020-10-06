#include "TFile.h"
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <iostream>
#include "TLine.h"
#include "TMath.h"
#include <Math/SpecFuncMathMore.h>
#include <TMath.h>

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
R__LOAD_LIBRARY(libMathMore.so);
#endif

// Resolution calculation
//S----------------------------------------------------------------
double GetRes(double _chi, double _harm){
  double con = TMath::Sqrt(TMath::Pi() / 2) / 2;
  double arg = _chi * _chi / 4.;
  double order1 = (_harm - 1) / 2.;
  double order2 = (_harm + 1) / 2.;
  double res = con * _chi * exp(-arg) * (ROOT::Math::cyl_bessel_i(order1, arg) + ROOT::Math::cyl_bessel_i(order2, arg));
  return res;
}
//E----------------------------------------------------------------


// Chi2 calculation
//S----------------------------------------------------------------
double GetChi(double _res, double _harm, int accuracy){
  double chi = 2.0;
  double delta = 1.0;
  for (int i = 0; i < accuracy; i++){
    if(GetRes(chi, _harm) < _res) chi = chi + delta;
    else chi = chi - delta;
    delta = delta / 2.;
  }
  return chi;
}
//E----------------------------------------------------------------




void res2(Int_t mEnergy = 6)
{

#if ROOT_VERSION_CODE < ROOT_VERSION(6, 0, 0)
gSystem->Load(libMathMore.so);
#endif

//TFile *file = new TFile("sum.root");
//TFile *file = new TFile("./out/res_11gev.root");
//TFile *file = new TFile("./out/res_7gev_new.root");
//TFile *file = new TFile("./OUT/7gev/urqmd_flow_7gev_check.root");
// TFile *file = new TFile("./OUT/urqmd/11.5gev/urqmd_res_11gev_STAR_check.root");
// TFile *file = new TFile("./OUT/urqmd/7.7gev/res.root","read");
TFile *file = new TFile("UrQMD_7.7GeV_V2R1.root","read");

//TFile *file = new TFile("./OUT/ampt/7.7gev_melt_6mb/res_ampt_7.7gev.root");
  
char hname1[800];
char title[800];


const int ncent = 6;
 
 float res2tpcEW[ncent];
 float res2rxnEW[ncent]; 
 float res2bbcEW[ncent];
 float res2fhcalEW[ncent];
 float res2fhcalFull[ncent];
 float res1fhcalFull[ncent];

float cent[ncent]={5,15,25,35,45,55};
float eres[ncent];
float ecent[ncent];

float chi, res, chiF, resF;
 
for (int ic=0; ic<ncent; ic++) {

(void) sprintf(hname1,"HRes_%i_%i_%i",0,0,ic);
TH1F *h3 = (TH1F*) file->Get(hname1);
res = sqrt(h3->GetMean());
//chi = GetChi(res,1.,50);
//chiF = TMath::Sqrt(2)*chi;
//resF = GetRes(chiF,1.);
resF=sqrt(h3->GetMean());
res2tpcEW[ic]=resF;//sqrt(h3->GetMean());

(void) sprintf(hname1,"HRes_%i_%i_%i",0,1,ic);
TH1F *h4 = (TH1F*) file->Get(hname1);
res2rxnEW[ic]=sqrt(h4->GetMean());

(void) sprintf(hname1,"HRes_%i_%i_%i",0,2,ic);
TH1F *h5 = (TH1F*) file->Get(hname1);
res2bbcEW[ic]=sqrt(h5->GetMean());

(void) sprintf(hname1,"HRes_%i_%i_%i",0,3,ic);
TH1F *h6 = (TH1F*) file->Get(hname1);
res = sqrt(h6->GetMean());
chi = GetChi(res,1.,50);
chiF = chi;//TMath::Sqrt(2)*chi;
resF = GetRes(chiF,2.);
res2fhcalEW[ic]=resF;
chiF = TMath::Sqrt(2)*chi;
resF = GetRes(chiF,2.);
res2fhcalFull[ic]=resF;

(void) sprintf(hname1,"HRes_%i_%i_%i",0,3,ic);
TH1F *h7 = (TH1F*) file->Get(hname1);
res = sqrt(h7->GetMean());
chi = GetChi(res,1.,50);
chiF = TMath::Sqrt(2)*chi;
resF = GetRes(chiF,1.);
res1fhcalFull[ic]=resF;

 eres[ic]=0.01;
 ecent[ic]=0.03;



 //cout << res2bbcEW[ic] <<",";
  
 }
 cout << endl;
 cout << "Resolution for the analysis:" << endl;
 cout << "float res2tpc[8] = {";
 for (int ic=0; ic<ncent; ic++) {
   cout << res2tpcEW[ic];
   if (ic < ncent-1) cout << ",";
   else cout << "};" << endl;
 }
 cout << "float res2rxn[8] = {";
 for (int ic=0; ic<ncent; ic++) {
   cout << res2rxnEW[ic];
   if (ic < ncent-1) cout << ",";
   else cout << "};" << endl;
 }
 cout << "float res2bbc[8] = {";
 for (int ic=0; ic<ncent; ic++) {
   cout << res2bbcEW[ic];
   if (ic < ncent-1) cout << ",";
   else cout << "};" << endl;
 }
 cout << "float res2fhcal[8] = {";
 for (int ic=0; ic<ncent; ic++) {
   cout << res2fhcalEW[ic];
   if (ic < ncent-1) cout << ",";
   else cout << "};" << endl;
 }
 cout << "float res2fhcalFull[8] = {";
 for (int ic=0; ic<ncent; ic++) {
   cout << res2fhcalFull[ic];
   if (ic < ncent-1) cout << ",";
   else cout << "};" << endl;
 }
 cout << "float res1fhcalFull[8] = {";
 for (int ic=0; ic<ncent; ic++) {
   cout << res1fhcalFull[ic];
   if (ic < ncent-1) cout << ",";
   else cout << "};" << endl;
 }
 cout << endl;

 TCanvas *c1;
 c1 = new TCanvas("c1","Flow analysis results",200,10,700,560);
  
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



sprintf(title,"PHSD: #sigma_{RP}   vs centrality for v_{2} , Au+Au  #sqrt{s_{NN}}=200 GeV");


 TH2F *hr2 = new TH2F("hr2",title, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("Centrality %");
  hr2->SetYTitle("#sigma_{RP}");



  hr2->Draw();


  TGraphErrors *gr1;
  TGraphErrors *gr2;
  TGraphErrors *gr3;
  TGraphErrors *gr4;
  TGraphErrors *gr5;




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

 // const int npt=12;
 gr4 = new TGraphErrors(6,cent,res2fhcalEW,ecent,eres);
 gr4->SetTitle("TGraphErrors Example ");
 gr4->SetMarkerColor(kBlue);
 gr4->SetMarkerStyle(25);
 gr4->SetMarkerSize(1.2);
 gr4->Draw("P");

 // const int npt=12;
 gr5 = new TGraphErrors(6,cent,res2fhcalFull,ecent,eres);
 gr5->SetTitle("TGraphErrors Example ");
 gr5->SetMarkerColor(kBlue);
 gr5->SetMarkerStyle(26);
 gr5->SetMarkerSize(1.2);
 gr5->Draw("P");

TF1 *f1 = new TF1("f1","[0]+[1]*(x)+[2]/x+[3]*x*x",5,55);
gr3->Fit("f1","R+");
gr3->Draw("P");



 TLegend *legC12 = new TLegend(0.17,.75,0.27,.87);

 legC12->SetFillColor(0);
 legC12->SetBorderSize(0);
 legC12->Draw();


legC12->AddEntry(gr1,"TPC","lp");
legC12->AddEntry(gr2,"RXN","lp");
legC12->AddEntry(gr3,"BBC","lp");
legC12->AddEntry(gr4,"FHCal","lp");
legC12->AddEntry(gr5,"FHCalFull","lp");



 legC12->SetFillColor(0);
 legC12->SetBorderSize(0);
 legC12->Draw();





}
