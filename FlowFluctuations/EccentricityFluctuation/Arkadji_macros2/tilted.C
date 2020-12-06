/** \file tilted.C
 * Script generating the tilted initial profile in the x-rapidity space at y=0
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generating the tilted initial profile in the x-rapidity space near y=0
/*! Generates the tilted initial profile in the x-rapidity space near y=0. Useful for testing the initial conditions to hydrodynamics. 
Requires _rrapidity_=1. */
void tilted(
            char *p //!< name of the ROOT input file
                ){

gROOT->Reset();
gStyle->SetPalette(1);

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TH3D *h = (TH3D*)f->Get("rap_distr"); 

TTree *param =  (TTree*)f->Get("param");
Float_t MAXYRAP;
param->SetBranchAddress("MAXYRAP",&MAXYRAP); param->GetEntry(0);
  
Float_t title_offset=.8;


TCanvas *c1= new TCanvas("c1", "x-y-rapidity distributions",0,0,1000,600);
   c1->Range(0,0,25,18);
   c1->SetFillColor(0);

label(inpfile);
   
pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.48,0.78,33);
pad2 = new TPad("pad2","This is pad2",0.52,0.02,0.98,0.78,33);

pad1->Draw();
pad2->Draw();

pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);

h->SetTitle("x-y-rapidity distribution");
h->SetStats(kFALSE);

h->Draw();

   pad2->cd();
   pad2->Range(-0.43642,-23.75,3.92778,-6.25);
   gPad->SetFillStyle(4000);
   gPad->SetFillColor(29);

TProfile *h2 = h->Project3D("xz");

char tW[200];
sprintf(tW,"x-rapidity distribution (projected for spatial coordinate |y|<%.1f)",MAXYRAP);


h2->SetStats(kFALSE);
h2->SetTitle(tW);

h2->Draw("cont4");

c1->SaveAs("tilted_pr.eps");
//c1->SaveAs("tilted_pr.C");

}
