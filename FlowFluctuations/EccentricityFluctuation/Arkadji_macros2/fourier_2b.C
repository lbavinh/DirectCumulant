/** \file fourier_2.C
 * epsilon_2 vs epsilon_4 63Cu+197Au
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generate the plot of epsilon_n^* vs. Nw, n=2,3,4,5,6
/* Useful for the triangular flow and higher-order flow analysis. */
void fourier_2b(
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

TH2D *h1 = new TH2D("h1","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:0-5)",100,0.0,1.0,100,0.0,1.0);
TH2D *h2 = new TH2D("h2","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:5-10)",100,0.0,1.0,100,0.0,1.0);
TH2D *h3 = new TH2D("h3","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:10-20)",100,0.0,1.0,100,0.0,1.0);
TH2D *h4 = new TH2D("h4","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:20-30)",100,0.0,1.0,100,0.0,1.0);
TH2D *h5 = new TH2D("h5","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:30-40)",100,0.0,1.0,100,0.0,1.0);
TH2D *h6 = new TH2D("h6","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:40-50)",100,0.0,1.0,100,0.0,1.0);
TH2D *h7 = new TH2D("h7","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:50-60)",100,0.0,1.0,100,0.0,1.0);
TH2D *h8 = new TH2D("h8","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:60-70)",100,0.0,1.0,100,0.0,1.0);
TH2D *h9 = new TH2D("h9","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:70-80)",100,0.0,1.0,100,0.0,1.0);
TH2D *h10 = new TH2D("h10","#epsilon^{*}_{2} vs #epsilon^{*}_{4} (c:80-100)",100,0.0,1.0,100,0.0,1.0);

Int_t nentries = (Int_t)itree->GetEntries();
for (Int_t i=1; i<nentries; i++) {
itree->GetEntry(i);


if ((b>0.0)&&(b<2.61818)){
h1->Fill(ep,ep4);
}

if ((b>2.61818)&&(b<3.72656)){
h2->Fill(ep,ep4);
}

if ((b>3.72656)&&(b<5.26599)){
h3->Fill(ep,ep4);
}

if ((b>5.26599)&&(b<6.43595)){
h4->Fill(ep,ep4);
}

if ((b>6.43595)&&(b<7.42118)){
h5->Fill(ep,ep4);
}
if ((b>7.42118)&&(b<8.28326)){
h6->Fill(ep,ep4);
}
if ((b>8.28326)&&(b<9.08376)){
h7->Fill(ep,ep4);
}

if ((b>9.08376)&&(b<9.82268)){
h8->Fill(ep,ep4);
}

if ((b>9.82268)&&(b<10.5616)){
h9->Fill(ep,ep4);
}

if ((b>10.5616)&&(b<30.0)){
h10->Fill(ep,ep4);
}
}

Char_t tt[25];
Float_t tA=0.65,tB=0.15;
TLatex *t = new TLatex();
   t->SetNDC();
   t->SetTextFont(32);
   t->SetTextColor(1);
   t->SetTextSize(0.07);
   t->SetTextAlign(12);

TCanvas *c2 = new TCanvas("c2","c2",600,1000);
label(inpfile);
c2->SetFillColor(0);
c2->Divide(2,5);
c2->cd(1);
h1->SetXTitle("#epsilon*_{4}");
h1->SetYTitle("#epsilon*_{2}  ");
h1->Draw("colz");
sprintf(tt,"#rho=%.4f",h1->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(2);
h2->SetXTitle("#epsilon*_{4}");
h2->SetYTitle("#epsilon*_{2}  ");
h2->Draw("colz");
sprintf(tt,"#rho=%.4f",h2->GetCorrelationFactor());
	t->DrawLatex(tA,tB,tt);
   
c2->cd(3);
h3->SetXTitle("#epsilon*_{4}");
h3->SetYTitle("#epsilon*_{2}  ");
h3->Draw("colz");
sprintf(tt,"#rho=%.4f",h3->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(4);
h4->SetXTitle("#epsilon*_{4}");
h4->SetYTitle("#epsilon*_{2}  ");
h4->Draw("colz");
sprintf(tt,"#rho=%.4f",h4->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(5);
h5->SetXTitle("#epsilon*_{4}");
h5->SetYTitle("#epsilon*_{2}  ");
h5->Draw("colz");
sprintf(tt,"#rho=%.4f",h5->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(6);
h6->SetXTitle("#epsilon*_{4}");
h6->SetYTitle("#epsilon*_{2}  ");
h6->Draw("colz");
sprintf(tt,"#rho=%.4f",h6->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);

c2->cd(7);
h7->SetXTitle("#epsilon*_{4}");
h7->SetYTitle("#epsilon*_{2}  ");
h7->Draw("colz");
sprintf(tt,"#rho=%.4f",h7->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);

c2->cd(8);
h8->SetXTitle("#epsilon*_{4}");
h8->SetYTitle("#epsilon*_{2}  ");
h8->Draw("colz");
sprintf(tt,"#rho=%.4f",h8->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(9);
h9->SetXTitle("#epsilon*_{4}");
h9->SetYTitle("#epsilon*_{2}  ");
h9->Draw("colz");
sprintf(tt,"#rho=%.4f",h9->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(10);
h10->SetXTitle("#epsilon*_{4}");
h10->SetYTitle("#epsilon*_{2}  ");
h10->Draw("colz");
sprintf(tt,"#rho=%.4f",h10->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);

c2->SaveAs("ep2_vs_ep4_42_CuAu.eps");

}
