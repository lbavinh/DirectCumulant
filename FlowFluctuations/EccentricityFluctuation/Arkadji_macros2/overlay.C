/** \file overlay.C
 * Script generating the overlaid distribution for the wounded and binary-collision sources
 * (part of GLISSANDO 2)
 */

#include "label.C"

//!  generate the overlaid distribution for the wounded and binary-collision sources
/*  Generates the overlaid distribution for the wounded and binary-collision sources in the superposition model. Works when 
a distribution of produced particles is folded with the distribution of sources (MODEL = 1 or MODEL = 2). */
void overlay(
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

TH1D *h = (TH1D*)f->Get("weih"); 
TH1D *hr = (TH1D*)f->Get("weih_bin"); 

Float_t title_offset=.8;


TCanvas *c1= new TCanvas("c1", " overlaid distributions",0,0,1000,600);
   c1->Range(0,0,25,18);
   c1->SetFillColor(0);

label(inpfile);
   
pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.48,0.78,33);
pad2 = new TPad("pad2","This is pad2",0.52,0.02,0.98,0.78,33);

pad1->Draw();
pad2->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(29);

Double_t scale; 

scale= 1./(h->Integral());
h->Scale(scale);

h->SetStats(kFALSE);
h->GetXaxis()->SetTitleOffset(title_offset);
h->SetXTitle("n ");
h->Draw();

   pad2->cd();
   pad2->Range(-0.43642,-23.75,3.92778,-6.25);
   gPad->SetFillStyle(4000);
   gPad->SetFillColor(29);

scale= 1./(hr->Integral());
hr->Scale(scale);

hr->SetStats(kFALSE);
hr->GetXaxis()->SetTitleOffset(title_offset);
hr->SetXTitle("n  ");

hr->Draw();

c1->SaveAs("overlay_pr.eps");
//c1->SaveAs("overlay_pr.C");


}
