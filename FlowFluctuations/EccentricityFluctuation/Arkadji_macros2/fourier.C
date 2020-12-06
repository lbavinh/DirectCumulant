/** \file fourier.C
 * Script generating the epsilon_n^* vs. N_w plot
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generate the plot of epsilon_n^* vs. Nw, n=2,3,4,5,6
/* Useful for the triangular flow and higher-order flow analysis. */
void fourier(
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

TTree *itree = (TTree*)f->Get("events");

up=476;

label(inpfile);

TCanvas *c0 = new TCanvas("c0", "c2",49,120,648,439);
 
TH2D *h2 = new TH2D("h2","#epsilon^{*}_{n} vs N_{W}",up,0.5,up+0.5,100,-1,1);
itree -> Draw("ep:nwAB >> h2");

TH2D *h3 = new TH2D("h3","ep_3 vs Nw",up,0.5,up+0.5,100,-1,1);
itree -> Draw("ep3:nwAB >> h3");

TH2D *h4 = new TH2D("h4","ep_4 vs Nw",up,0.5,up+0.5,100,-1,1);
itree -> Draw("ep4:nwAB >> h4");

TH2D *h5 = new TH2D("h5","ep_5 vs Nw",up,0.5,up+0.5,100,-1,1);
itree -> Draw("ep5:nwAB >> h5");

TH2D *h6 = new TH2D("h6","ep_6 vs Nw",up,0.5,up+0.5,100,-1,1);
itree -> Draw("ep6:nwAB >> h6");

TCanvas *c2 = new TCanvas("c2","eccentricities",650,600);
c2->cd(1);
c2->Range(0,0,25,18);
c2->SetFillColor(0);

label(inpfile);

pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);


TProfile *p2 = h2->ProfileX("p2"); 
p2->SetStats(kFALSE);

p2->SetTitle("variable-axes eccentricities, n=2,3,4,5,6");
p2->SetXTitle("N_{W} ");
p2->SetYTitle("#epsilon*_{n}  ");

p2->Draw("hist");

TProfile *p3 = h3->ProfileX("p3"); 
p3->SetLineColor(kRed);
p3->SetStats(kFALSE);
p3->Draw("histSAME");

TProfile *p4 = h4->ProfileX("p4"); 
p4->SetLineColor(kBlue);
p4->SetStats(kFALSE);
p4->Draw("histSAME");

TProfile *p5 = h5->ProfileX("p5"); 
p5->SetLineColor(kMagenta);
p5->SetStats(kFALSE);
p5->Draw("histSAME");

TProfile *p6 = h6->ProfileX("p6"); 
p6->SetLineColor(kCyan);
p6->SetStats(kFALSE);
p6->Draw("histSAME");

TLegend *leg = new TLegend(0.63,0.47,.79,0.77);
  leg->AddEntry(p2, "n=2", "l");
  leg->AddEntry(p3, "n=3", "l");
  leg->AddEntry(p4, "n=4", "l");
  leg->AddEntry(p5, "n=5", "l");
  leg->AddEntry(p6, "n=6", "l");
  leg->Draw("SAME");

c2->SaveAs("epsn.eps");
c2->SaveAs("epsn.C");

}
