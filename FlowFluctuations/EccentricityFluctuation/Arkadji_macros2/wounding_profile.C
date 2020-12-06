/** \file wounding_profile.C
 * Script generating the wounding and binary-collision profiles
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generate the plots of the wounding and binary-collision profiles  
/* Generates the plots of the wounding and binary-collision profiles as functions of the separation of the nucleon centers.
For the commonly used case (hard-sphere wounding profile) these are step functions, however, the Gaussian wounding profile implemented in 
GLISSANDO 2 is more realistic. */
void wounding_profile(
            char *p //!< name of the ROOT input file
                ){

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TH1D *h = (TH1D*)f->Get("w_distr"); 
TH1D *hr = (TH1D*)f->Get("w_distr_bin"); 

Float_t title_offset=.8;

TCanvas *c1= new TCanvas("c1", " wounding and binary profiles",0,0,1000,600);
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
gPad->SetFillColor(0);

h->SetStats(kFALSE);
h->GetXaxis()->SetTitleOffset(title_offset);
h->SetXTitle("d^{2} [fm^{2}] ");
h->Draw();

   pad2->cd();
   pad2->Range(-0.43642,-23.75,3.92778,-6.25);
   gPad->SetFillStyle(4000);
   gPad->SetFillColor(0);

hr->SetStats(kFALSE);
hr->GetXaxis()->SetTitleOffset(title_offset);
hr->SetXTitle("d^{2} [fm^{2}]  ");
hr->Draw();

c1->SaveAs("wounding_pr.eps");
//c1->SaveAs("wounding_pr.C");

}
