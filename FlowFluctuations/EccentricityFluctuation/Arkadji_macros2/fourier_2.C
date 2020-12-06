/** \file fourier_2.C
 * Script generating the epsilon_n^* vs. N_w plot
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generate the plot of epsilon_n^* vs. Nw, n=2,3,4,5,6
/* Useful for the triangular flow and higher-order flow analysis. */
void fourier_2(
            char *p //!< name of the ROOT input file
                ){

gROOT->Reset();
gStyle->SetPalette(1);

//ofstream *out = new ofstream;
//out->open("e3.txt");

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TTree *itree = (TTree*)f->Get("events");
Float_t b,ep,ep4;
itree->SetBranchAddress("b",&b);
itree->SetBranchAddress("ep",&ep);
itree->SetBranchAddress("ep4",&ep4);

Int_t up=476;

label(inpfile);

TH2D *h2 = new TH2D("h2","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:0-5)",100,0.0,1.0,100,0.0,1.0);
TH2D *h3 = new TH2D("h3","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:5-10)",100,0.0,1.0,100,0.0,1.0);
TH2D *h4 = new TH2D("h4","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:10-20)",100,0.0,1.0,100,0.0,1.0);
TH2D *h5 = new TH2D("h5","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:20-30)",100,0.0,1.0,100,0.0,1.0);
TH2D *h6 = new TH2D("h6","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:30-40)",100,0.0,1.0,100,0.0,1.0);

TCanvas *c0 = new TCanvas("c0", "c2",49,120,648,439);

Int_t nentries = (Int_t)itree->GetEntries();
for (Int_t i=1; i<nentries; i++) {
itree->GetEntry(i);


if ((b>0.0)&&(b<3.58734)){
h2->Fill(ep,ep4);
//itree -> Draw("ep:ep4 >> h2");
}

if ((b>3.58734)&&(b<5.09925)){
h3->Fill(ep,ep4);
//itree -> Draw("ep:ep4 >> h3");
}

if ((b>5.09925)&&(b<7.20277)){
h4->Fill(ep,ep4);
//itree -> Draw("ep:ep4 >> h4");
}

if ((b>7.20277)&&(b<8.84615)){
h5->Fill(ep,ep4);
//itree -> Draw("ep:ep4 >> h5");
}

if ((b>8.84615)&&(b<10.1609)){
h6->Fill(ep,ep4);
//itree -> Draw("ep:ep4 >> h6");
}
}

TCanvas *c2 = new TCanvas("c2","eccentricities (c:0-5)",650,600);
c2->cd(1);
c2->Range(0,0,25,18);
c2->SetFillColor(0);

label(inpfile);

pad2 = new TPad("pad2","This is pad1",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);


//TProfile *p2 = h2->ProfileX("p2"); 
//p2->SetStats(kFALSE);

//h2->SetTitle("variable-axes eccentricities, n=2,3,4,5,6");
h2->SetXTitle("#epsilon*_{4}");
h2->SetYTitle("#epsilon*_{2}  ");

h2->Draw("colz");

TCanvas *c3 = new TCanvas("c3","eccentricities (c:5-10)",650,600);
c3->cd(1);
c3->Range(0,0,25,18);
c3->SetFillColor(0);

label(inpfile);

pad3 = new TPad("pad3","This is pad1",0.02,0.02,0.98,0.78,33);
pad3->Draw();
pad3->cd();
pad3->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

h3->SetXTitle("#epsilon*_{4}");
h3->SetYTitle("#epsilon*_{2}  ");

h3->Draw("colz");

TCanvas *c4 = new TCanvas("c4","eccentricities (c:10-20)",650,600);
c4->cd(1);
c4->Range(0,0,25,18);
c4->SetFillColor(0);

label(inpfile);

pad4 = new TPad("pad4","This is pad1",0.02,0.02,0.98,0.78,33);
pad4->Draw();
pad4->cd();
pad4->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

h4->SetXTitle("#epsilon*_{4}");
h4->SetYTitle("#epsilon*_{2}  ");

h4->Draw("colz");

TCanvas *c5 = new TCanvas("c5","eccentricities (c:20-30)",650,600);
c5->cd(1);
c5->Range(0,0,25,18);
c5->SetFillColor(0);

label(inpfile);

pad5 = new TPad("pad5","This is pad1",0.02,0.02,0.98,0.78,33);
pad5->Draw();
pad5->cd();
pad5->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

h5->SetXTitle("#epsilon*_{4}");
h5->SetYTitle("#epsilon*_{2}  ");

h5->Draw("colz");

TCanvas *c6 = new TCanvas("c6","eccentricities (c:30-40)",650,600);
c6->cd(1);
c6->Range(0,0,25,18);
c6->SetFillColor(0);

label(inpfile);

pad6 = new TPad("pad6","This is pad1",0.02,0.02,0.98,0.78,33);
pad6->Draw();
pad6->cd();
pad6->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

h6->SetXTitle("#epsilon*_{4}");
h6->SetYTitle("#epsilon*_{2}  ");

h6->Draw("colz");

c2->SaveAs("ep2_vs_ep4_c05.eps");
c3->SaveAs("ep2_vs_ep4_c510.eps");
c4->SaveAs("ep2_vs_ep4_c1020.eps");
c5->SaveAs("ep2_vs_ep4_c2030.eps");
c6->SaveAs("ep2_vs_ep4_c3040.eps");
}
