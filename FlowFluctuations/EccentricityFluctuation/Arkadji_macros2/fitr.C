/** \file fitr.C
 * Script fitting the density profile of nucleus A to the Woods-Saxon form
 * (part of GLISSANDO 2)
 * 
 */

#include "label.C"

//! Woods-Saxon radial density function
Double_t saxon(
           Double_t *x,   //!< radial coordinate
           Double_t *par  //!< Woods-Saxon parameters (par[0]=norm, par[1]=R, par[2]=a)
              ) {
return 
4.0*TMath::Pi()*x[0]*x[0]*par[0]/(1.0+TMath::Exp((x[0]-par[1])/par[2]));
}

//! fit the obtained density to the Woods-Saxon form and plot the result
/*! Fit the obtained density of nucleons in nucleus A to the Woods-Saxon form and plot the result. Requires _profile_=1. */
void fitr(
     char *p //!< name of the ROOT input file 
         ) {

gROOT->Reset();

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);
TH1D *hr = ((TH1D*)f->Get("radA")); 

TTree *param =  (TTree*)f->Get("param");
Float_t r;
Int_t NUMA;
Float_t RWSA,AWSA;

param->SetBranchAddress("NUMA",&NUMA);param->GetEntry(0);
param->SetBranchAddress("RWSA",&RWSA);param->GetEntry(0);
param->SetBranchAddress("AWSA",&AWSA);param->GetEntry(0);

cout << "Mass number=" << NUMA << ", original WS parameters: R=" << RWSA <<
   " a=" << AWSA <<endl << endl;

    gStyle->SetOptFit(0000);
    gStyle->SetOptStat("");
  
    TCanvas *c2 = new TCanvas("c2","WS",650,600);
    c2->cd(1);
    c2->Range(0,0,25,18);
    c2->SetFillColor(0);
    
//    label_fit(inpfile);
   
pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);


//TH1F *k1 = (TH1F *)f->Get("hr");
hr->SetTitle("Fit of the radial distribution to the Woods-Saxon form");
hr->SetMarkerStyle(21);
hr->SetStats(kFALSE);
hr->SetMarkerSize(0.5);
hr->SetXTitle("r [fm] ");
hr->SetYTitle("4 #pi r^{2} #rho(r) (normalized to A)  ");

Float_t sc=1./(hr->Integral())/(hr->GetBinWidth(1))*NUMA;
hr->Scale(sc);


hr->Draw("E");  

TF1 *func = new TF1("saxon",saxon,0.0,10.0,3);
func->SetParameters(500,5,0.5);
func->SetParNames("Norm","R","a");
    
func->SetNpx(500);
func->SetLineWidth(1);
func->SetLineColor(kBlue);

hr->Fit(func,"r");
hr->Fit(func,"REM");

func->Draw("SAME");

TF1 *fitpar=hr->GetFunction(saxon);
Float_t p0=fitpar->GetParameter(0);
Float_t e0=fitpar->GetParError(0);
Float_t p1=fitpar->GetParameter(1);
Float_t e1=fitpar->GetParError(1);
Float_t p2=fitpar->GetParameter(2);
Float_t e2=fitpar->GetParError(2);


char optr[300];
char opta[300];

sprintf(optr,"R = %.4f #pm %.4f",p1,e1);
sprintf(opta,"a = %.4f #pm %.4f",p2,e2);

TLatex *t = new TLatex();
   t->SetNDC();
   t->SetTextFont(32);
   t->SetTextColor(1);
   t->SetTextSize(0.05);
   t->SetTextAlign(12);
   t->DrawLatex(.6,.85,optr);
   t->DrawLatex(.6,.8,opta);

c2->SaveAs("fitr.eps");


}
