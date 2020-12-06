/** \file density.C
 * Script generating the fixed- and variable-axes densities
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! produce plots of the fixed-axes and variable-axes densities 
/*!  Produces plots of the fixed-axes and variable-axes (participant) densities */
void density(
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

//fixed-axes density distribution
//TH2D *h = (TH2D*)f->Get("xyhist"); 
//variable-axes density distribution
TH2D *hr = (TH2D*)f->Get("xyhistr"); 

Float_t title_offset=1.5;

//3-dimensional plot
TCanvas *c1= new TCanvas("c1", " 3D source density",0,0,1000,600);
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

//h->SetStats(kFALSE);
//h->GetXaxis()->SetTitleOffset(title_offset);
//h->GetYaxis()->SetTitleOffset(title_offset);
//h->SetXTitle("x  ");
//h->SetYTitle("y  ");
//h->Draw("SURF2Z");

   pad2->cd();
   pad2->Range(-0.43642,-23.75,3.92778,-6.25);
   gPad->SetFillStyle(4000);
   gPad->SetFillColor(29);

hr->SetStats(kFALSE);
hr->GetXaxis()->SetTitleOffset(title_offset);
hr->GetYaxis()->SetTitleOffset(title_offset);
hr->SetXTitle("x  ");
hr->SetYTitle("y  ");
hr->Draw("SURF2Z");

c1->Modified();
c1->Update();
c1->SaveAs("3D-density.eps");

title_offset=0.8;

//2-dimensional plot
TCanvas *c2= new TCanvas("c2", " 2D source density",0,0,1000,600);
   c2->Range(0,0,25,18);
   c2->SetFillColor(0);
label(inpfile);
 
pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.48,0.78,33);
pad2 = new TPad("pad2","This is pad2",0.52,0.02,0.98,0.78,33);

pad1->Draw();
pad2->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(29);

//h->SetStats(kFALSE);
//h->GetXaxis()->SetTitleOffset(title_offset);
//h->GetYaxis()->SetTitleOffset(title_offset);
//h->SetXTitle("x  ");
//h->SetYTitle("y  ");
//h->Draw("COLZ");

   pad2->cd();
   pad2->Range(-0.43642,-23.75,3.92778,-6.25);
   gPad->SetFillStyle(4000);
   gPad->SetFillColor(29);

hr->SetStats(kFALSE);
hr->GetXaxis()->SetTitleOffset(title_offset);
hr->GetYaxis()->SetTitleOffset(title_offset);
hr->SetXTitle("x  ");
hr->SetYTitle("y  ");
hr->Draw("COLZ");

c2->Modified();
c2->Update();
c2->SaveAs("2D-density.eps");

}
