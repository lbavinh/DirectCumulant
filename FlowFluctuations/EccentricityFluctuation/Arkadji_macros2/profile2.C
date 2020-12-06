/** \file profile2.C
 * Script generating the radial profiles of subsequent Fourier components of the density 
 * (part of GLISSANDO 2)
 * 
 */


#include "label.C"

//! produces plots of the fixed-axes and variable-axes Fourier profiles of the density of sources.
/*! The plots are obtained by Fourier-projecting the 2-dim distribution of sources. */
void profile2(
char *p //!< name of the GLISSANDO input ROOT file
             ){

gROOT->Reset();

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);  

TH1F *hc0hp  = (TH1F*)f->Get("c0hp");
TH1F *hc0rhp = (TH1F*)f->Get("c0rhp");
TH1F *hc2hp  = (TH1F*)f->Get("c2hp"); 
TH1F *hc2rhp = (TH1F*)f->Get("c2rhp"); 
TH1F *hc4hp  = (TH1F*)f->Get("c4hp"); 
TH1F *hc4rhp = (TH1F*)f->Get("c4rhp"); 
TH1F *hc6hp  = (TH1F*)f->Get("c6hp"); 
TH1F *hc6rhp = (TH1F*)f->Get("c6rhp"); 

Float_t label_size=0.04;
Float_t title_size=0.05;
Float_t title_offset=1.0;

char x_title[]="#rho [fm]  ";

gStyle->SetOptStat(0);
gStyle->SetStatBorderSize(0);
 
  TCanvas *c1= new TCanvas("c1", "f0 profile",650, 600);
  c1->Range(0,0,25,18);
  c1->SetFillColor(0);

label(inpfile);
 
pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.78,33);
pad1->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

hc0hp->SetTitle("");
hc0hp->SetStats(kFALSE);
hc0hp->SetLineColor(4);
hc0hp->SetLineStyle(2);

hc0rhp->SetTitle("");
hc0rhp->SetStats(kFALSE);
hc0rhp->GetXaxis()->SetNdivisions(405);
hc0rhp->GetXaxis()->SetLabelSize(label_size);
hc0rhp->GetXaxis()->SetTitleSize(title_size);
hc0rhp->GetXaxis()->SetTitleOffset(title_offset);
hc0rhp->GetXaxis()->SetTitle(x_title);

hc0rhp->GetYaxis()->SetNdivisions(606);
hc0rhp->GetYaxis()->SetLabelSize(label_size);
hc0rhp->GetYaxis()->SetTitleSize(title_size);
hc0rhp->GetYaxis()->SetTitleOffset(title_offset);
hc0rhp->GetYaxis()->SetTitle("f_{0}, f_{0}*  ");
hc0rhp->SetLineColor(2);
hc0rhp->Draw();
hc0hp->Draw("SAME");

TLegend *leg0 = new TLegend(0.7,0.7,0.8,0.8);
  leg0->AddEntry(hc0hp, "f_{0}", "l");
  leg0->AddEntry(hc0rhp, "f_{0}*", "l");
  leg0->Draw("SAME");

c1->Modified();
c1->Update();
c1->SaveAs("f0_fig.eps");

TCanvas *c2= new TCanvas("c2", " f2 profile",0,0,650,600);
   c2->Range(0,0,25,18);
   c2->SetFillColor(0);

label(inpfile);
 
pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.78,33);
pad1->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

hc2hp->SetTitle("");
hc2hp->SetStats(kFALSE);
hc2hp->SetLineColor(4);
hc2hp->SetLineStyle(2);

hc2rhp->SetTitle("");
hc2rhp->SetStats(kFALSE);
hc2rhp->GetXaxis()->SetNdivisions(405);
hc2rhp->GetXaxis()->SetLabelSize(label_size);
hc2rhp->GetXaxis()->SetTitleSize(title_size);
hc2rhp->GetXaxis()->SetTitleOffset(title_offset);
hc2rhp->GetXaxis()->SetTitle(x_title);

hc2rhp->GetYaxis()->SetNdivisions(606);
hc2rhp->GetYaxis()->SetLabelSize(label_size);
hc2rhp->GetYaxis()->SetTitleSize(title_size);
hc2rhp->GetYaxis()->SetTitleOffset(title_offset);
hc2rhp->GetYaxis()->SetTitle("f_{2}, f_{2}*  ");
hc2rhp->SetLineColor(2);
hc2rhp->Draw();
hc2hp->Draw("SAME");

TLegend *leg2 = new TLegend(0.7,0.7,0.8,0.8);
  leg2->AddEntry(hc2hp, "f_{2}", "l");
  leg2->AddEntry(hc2rhp, "f_{2}*", "l");
  leg2->Draw("SAME");

c2->Modified();
c2->Update();
c2->SaveAs("f2_fig.eps");

TCanvas *c3= new TCanvas("c3", " f4 profile",0,0,650,600);
   c3->Range(0,0,25,18);
   c3->SetFillColor(0);

label(inpfile);
 
pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.78,33);
pad1->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

hc4hp->SetTitle("");
hc4hp->SetStats(kFALSE);
hc4hp->SetLineColor(4);
hc4hp->SetLineStyle(2);

hc4rhp->SetTitle("");
hc4rhp->SetStats(kFALSE);
hc4rhp->GetXaxis()->SetNdivisions(405);
hc4rhp->GetXaxis()->SetLabelSize(label_size);
hc4rhp->GetXaxis()->SetTitleSize(title_size);
hc4rhp->GetXaxis()->SetTitleOffset(title_offset);
hc4rhp->GetXaxis()->SetTitle(x_title);

hc4rhp->GetYaxis()->SetNdivisions(606);
hc4rhp->GetYaxis()->SetLabelSize(label_size);
hc4rhp->GetYaxis()->SetTitleSize(title_size);
hc4rhp->GetYaxis()->SetTitleOffset(title_offset);
hc4rhp->GetYaxis()->SetTitle("f_{4}, f_{4}*  ");
hc4rhp->SetLineColor(2);
hc4rhp->Draw();
hc4hp->Draw("SAME");

TLegend *leg4 = new TLegend(0.7,0.2,0.8,0.3);
  leg4->AddEntry(hc4hp, "f_{4}", "l");
  leg4->AddEntry(hc4rhp, "f_{4}*", "l");
  leg4->Draw("SAME");

c3->Modified();
c3->Update();
c3->SaveAs("f4_fig.eps");

TCanvas *c4= new TCanvas("c4", " f6 profile",0,0,650,600);
   c4->Range(0,0,25,18);
   c4->SetFillColor(0);

label(inpfile);

pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.78,33);
pad1->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

hc6hp->SetTitle("");
hc6hp->SetStats(kFALSE);
hc6hp->SetLineColor(4);
hc6hp->SetLineStyle(2);

hc6rhp->SetTitle("");
hc6rhp->SetStats(kFALSE);
hc6rhp->GetXaxis()->SetNdivisions(405);
hc6rhp->GetXaxis()->SetLabelSize(label_size);
hc6rhp->GetXaxis()->SetTitleSize(title_size);
hc6rhp->GetXaxis()->SetTitleOffset(title_offset);
hc6rhp->GetXaxis()->SetTitle(x_title);

hc6rhp->GetYaxis()->SetNdivisions(606);
hc6rhp->GetYaxis()->SetLabelSize(label_size);
hc6rhp->GetYaxis()->SetTitleSize(title_size);
hc6rhp->GetYaxis()->SetTitleOffset(title_offset);
hc6rhp->GetYaxis()->SetTitle("f_{6}, f_{6}*  ");
hc6rhp->SetLineColor(2);
hc6rhp->Draw();
hc6hp->Draw("SAME");

TLegend *leg6 = new TLegend(0.7,0.2,0.8,0.3);
  leg6->AddEntry(hc6hp, "f_{6}", "l");
  leg6->AddEntry(hc6rhp, "f_{6}*", "l");
  leg6->Draw("SAME");

c4->Modified();
c4->Update();
c4->SaveAs("f6_fig.eps");
}
