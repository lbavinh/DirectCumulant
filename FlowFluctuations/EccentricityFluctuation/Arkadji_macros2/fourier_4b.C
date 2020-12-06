/** \file fourier_3.C
 * cos((2 Psi_2 - Psi_4)) 238U+238U
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generate the plot of epsilon_n^* vs. Nw, n=2,3,4,5,6
/* Useful for the triangular flow and higher-order flow analysis. */
void fourier_4b(
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
Float_t b,phir,phir3,phir4;
itree->SetBranchAddress("b",&b);
itree->SetBranchAddress("phir",&phir);
itree->SetBranchAddress("phir3",&phir3);
itree->SetBranchAddress("phir4",&phir4);

Int_t up=476;

label(inpfile);

Int_t nbin=100;
const Float_t pi=3.1415926, pi2=pi/2.0, pi3=pi/3.0, pi6=pi/6.0;


TH2D * angles1 = new TH2D("angles1", "(c:0-5)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles2 = new TH2D("angles2", "(c:5-10)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles3 = new TH2D("angles3", "(c:10-20)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles4 = new TH2D("angles4", "(c:20-30)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles5 = new TH2D("angles5", "(c:30-40)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles6 = new TH2D("angles6", "(c:40-50)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles7 = new TH2D("angles7", "(c:50-60)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles8 = new TH2D("angles8", "(c:60-70)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles9 = new TH2D("angles9", "(c:70-80)", nbin,-pi2,pi2,nbin,-pi6,pi6);
TH2D * angles10 = new TH2D("angles10", "(c:80-95)", nbin,-pi2,pi2,nbin,-pi6,pi6);

Int_t nentries = (Int_t)itree->GetEntries();
for (Int_t i=1; i<nentries; i++) {
itree->GetEntry(i);

if ((b>0.0)&&(b<2.61818)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;

angles1->Fill(phir,phir3);
}

if ((b>2.61818)&&(b<3.72656)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;

angles2->Fill(phir,phir3);
}

if ((b>3.72656)&&(b<5.26599)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles3->Fill(phir,phir3);
}

if ((b>5.26599)&&(b<6.43595)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles4->Fill(phir,phir3);
}

if ((b>6.43595)&&(b<7.42118)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles5->Fill(phir,phir3);
}
if ((b>7.42118)&&(b<8.28326)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles6->Fill(phir,phir3);
}
if ((b>8.28326)&&(b<9.08376)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles7->Fill(phir,phir3);
}

if ((b>9.08376)&&(b<9.82268)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles8->Fill(phir,phir3);
}

if ((b>9.82268)&&(b<10.5616)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles9->Fill(phir,phir3);
}

if ((b>10.5616)&&(b<12.1626)){
if (phir<-pi2)phir=phir+pi;
if (phir>pi2)phir=phir-pi;

if (phir3<-pi6)phir3=phir3+pi3;
if (phir3>pi6)phir3=phir3-pi3;
angles10->Fill(phir,phir3);
}
}

Char_t tt[25];
Float_t tA=0.65,tB=0.15;
TLatex *t = new TLatex();
   t->SetNDC();
   t->SetTextFont(32);
   t->SetTextColor(10);
   t->SetTextSize(0.07);
   t->SetTextAlign(12);

TCanvas *c2 = new TCanvas("c2","c2",600,1000);
label(inpfile);
c2->SetFillColor(0);
c2->Divide(2,5);
c2->cd(1);
angles1->SetXTitle("#Psi_{2}");
angles1->SetYTitle("#Psi_{3}");
angles1->Draw("colz");
sprintf(tt,"#rho=%.4f",angles1->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(2);
angles2->SetXTitle("#Psi_{2}");
angles2->SetYTitle("#Psi_{3}");
angles2->Draw("colz");
sprintf(tt,"#rho=%.4f",angles2->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(3);
angles3->SetXTitle("#Psi_{2}");
angles3->SetYTitle("#Psi_{3}");
angles3->Draw("colz");
sprintf(tt,"#rho=%.4f",angles3->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(4);
angles4->SetXTitle("#Psi_{2}");
angles4->SetYTitle("#Psi_{3}");
angles4->Draw("colz");
sprintf(tt,"#rho=%.4f",angles4->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(5);
angles5->SetXTitle("#Psi_{2}");
angles5->SetYTitle("#Psi_{3}");
angles5->Draw("colz");
sprintf(tt,"#rho=%.4f",angles5->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(6);
angles6->SetXTitle("#Psi_{2}");
angles6->SetYTitle("#Psi_{3}");
angles6->Draw("colz");
sprintf(tt,"#rho=%.4f",angles6->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(7);
angles7->SetXTitle("#Psi_{2}");
angles7->SetYTitle("#Psi_{3}");
angles7->Draw("colz");
sprintf(tt,"#rho=%.4f",angles7->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(8);
angles8->SetXTitle("#Psi_{2}");
angles8->SetYTitle("#Psi_{3}");
angles8->Draw("colz");
sprintf(tt,"#rho=%.4f",angles8->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);   
c2->cd(9);
angles9->SetXTitle("#Psi_{2}");
angles9->SetYTitle("#Psi_{3}");
angles9->Draw("colz");
sprintf(tt,"#rho=%.4f",angles9->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->cd(10);
angles10->SetXTitle("#Psi_{2}");
angles10->SetYTitle("#Psi_{3}");
angles10->Draw("colz");
sprintf(tt,"#rho=%.4f",angles10->GetCorrelationFactor());
   t->DrawLatex(tA,tB,tt);
   
c2->SaveAs("new_psi2_psi3_42_CuAu.eps");


}
