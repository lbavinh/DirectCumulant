/** \file fourier_3.C
 * cos((2 Psi_2 - Psi_4)) 63Cu+197Au
 * (part of GLISSANDO 2)
 */

#include "label.C"

//! generate the plot of epsilon_n^* vs. Nw, n=2,3,4,5,6
/* Useful for the triangular flow and higher-order flow analysis. */
void fourier_3b(
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
Float_t nA=-1.0,nB=1.0;
Float_t x1,x2;

TH1D *h11 = new TH1D("h11","(c:0-5)",nbin,nA,nB);
TH1D *h21 = new TH1D("h21","(c:5-10)",nbin,nA,nB);
TH1D *h31 = new TH1D("h31","(c:10-20)",nbin,nA,nB);
TH1D *h41 = new TH1D("h41","(c:20-30)",nbin,nA,nB);
TH1D *h51 = new TH1D("h51","(c:30-40)",nbin,nA,nB);
TH1D *h61 = new TH1D("h61","(c:40-50)",nbin,nA,nB);
TH1D *h71 = new TH1D("h71","(c:50-60)",nbin,nA,nB);
TH1D *h81 = new TH1D("h81","(c:60-70)",nbin,nA,nB);
TH1D *h91 = new TH1D("h91","(c:70-80)",nbin,nA,nB);
TH1D *h101 = new TH1D("h101","(c:80-100)",nbin,nA,nB);

TH1D *h12 = new TH1D("h12","(c:0-5)",nbin,nA,nB);
TH1D *h22 = new TH1D("h22","(c:5-10)",nbin,nA,nB);
TH1D *h32 = new TH1D("h32","(c:10-20)",nbin,nA,nB);
TH1D *h42 = new TH1D("h42","(c:20-30)",nbin,nA,nB);
TH1D *h52 = new TH1D("h52","(c:30-40)",nbin,nA,nB);
TH1D *h62 = new TH1D("h62","(c:40-50)",nbin,nA,nB);
TH1D *h72 = new TH1D("h72","(c:50-60)",nbin,nA,nB);
TH1D *h82 = new TH1D("h82","(c:60-70)",nbin,nA,nB);
TH1D *h92 = new TH1D("h92","(c:70-80)",nbin,nA,nB);
TH1D *h102 = new TH1D("h102","(c:80-100)",nbin,nA,nB);

Int_t nentries = (Int_t)itree->GetEntries();
for (Int_t i=1; i<nentries; i++) {
itree->GetEntry(i);

if ((b>0.0)&&(b<2.61818)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h11->Fill(x1);
h12->Fill(x2);
}

if ((b>2.61818)&&(b<3.72656)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h21->Fill(x1);
h22->Fill(x2);
}

if ((b>3.72656)&&(b<5.26599)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h31->Fill(x1);
h32->Fill(x2);
}

if ((b>5.26599)&&(b<6.43595)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h41->Fill(x1);
h42->Fill(x2);
}

if ((b>6.43595)&&(b<7.42118)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h51->Fill(x1);
h52->Fill(x2);
}
if ((b>7.42118)&&(b<8.28326)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h61->Fill(x1);
h62->Fill(x2);
}
if ((b>8.28326)&&(b<9.08376)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h71->Fill(x1);
h72->Fill(x2);
}

if ((b>9.08376)&&(b<9.82268)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h81->Fill(x1);
h82->Fill(x2);
}

if ((b>9.82268)&&(b<10.5616)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h91->Fill(x1);
h92->Fill(x2);
}

if ((b>10.5616)&&(b<30.0)){
x1=cos(2.0*phir - phir4);
x2=cos(3.0*phir - 2.0*phir3);
h101->Fill(x1);
h102->Fill(x2);
}
}

TCanvas *c2 = new TCanvas("c2","c2",600,1000);
label(inpfile);
c2->SetFillColor(0);
c2->Divide(2,5);
c2->cd(1);
gPad->SetLogy();
h11->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h11->Draw();
   
c2->cd(2);
gPad->SetLogy();
h21->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h21->Draw();
   
c2->cd(3);
gPad->SetLogy();
h31->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h31->Draw();
   
c2->cd(4);
gPad->SetLogy();
h41->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h41->Draw();
   
c2->cd(5);
gPad->SetLogy();
h51->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h51->Draw();
   
c2->cd(6);
gPad->SetLogy();
h61->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h61->Draw();

c2->cd(7);
gPad->SetLogy();
h71->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h71->Draw();

c2->cd(8);
gPad->SetLogy();
h81->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h81->Draw();
   
c2->cd(9);
gPad->SetLogy();
h91->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h91->Draw();
   
c2->cd(10);
gPad->SetLogy();
h101->SetXTitle("cos(2 #Psi_2 - #Psi_4)");
h101->Draw();

c2->SaveAs("psi2_psi4_42_CuAu.eps");

TCanvas *c4 = new TCanvas("c4","c4",600,1000);
label(inpfile);
c4->SetFillColor(0);
c4->Divide(2,5);
c4->cd(1);
gPad->SetLogy();
h12->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h12->Draw();
   
c4->cd(2);
gPad->SetLogy();
h22->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h22->Draw();

c4->cd(3);   
gPad->SetLogy();
h32->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h32->Draw();
   
c4->cd(4);
gPad->SetLogy();
h42->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h42->Draw();
   
c4->cd(5);
gPad->SetLogy();
h52->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h52->Draw();
   
c4->cd(6);
gPad->SetLogy();
h62->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h62->Draw();

c4->cd(7);
gPad->SetLogy();
h72->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h72->Draw();

c4->cd(8);
gPad->SetLogy();
h82->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h82->Draw();
   
c4->cd(9);
gPad->SetLogy();
h92->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h92->Draw();
   
c4->cd(10);
gPad->SetLogy();
h102->SetXTitle("cos(3 #Psi_2 - 2 #Psi_3)");
h102->Draw();

c4->SaveAs("psi2_psi3_42_CuAu.eps");

}
