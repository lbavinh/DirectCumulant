 /** \file centrality.C
 * Script generating the centrality classes (alternative to centrality2.C)
 * (part of GLISSANDO 2)
 * 
 */

#include "label.C"
#include <iostream>
#include <fstream>

// Produces centrality windows for the stored Root file.
// This makes sense for minimum bias calculations.
// Plot centrality versus number of wounded nucleons,
// weight, and impact parameter

//! generate the centrality classes
/*! Centrality classes are generated in the total number of wounded nucleons, relative deposited strenth (RDS), and the 
    impact parameter. Plots of centrality vs. these variables are generated. The script makes sense for the minimum-bias simulations. */
void centrality(
          char *p //!< name of the ROOT input file 
               ) {

cout << endl << "This script makes sense for minimum-bias events" << endl << endl;

gROOT->Reset();

ofstream *out = new ofstream;
out->open("centrality.dat");

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  
 *out << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TTree *events = (TTree*)f->Get("events");
Float_t b,nwAB,npa;
events->SetBranchAddress("b",&b);
events->SetBranchAddress("nwAB",&nwAB);
events->SetBranchAddress("npa",&npa);

//TFile *hfile = new TFile("centrality.root","RECREATE","histfile");

Int_t nentries = (Int_t)events->GetEntries();
for (Int_t i=0;i<1;i++){
events->GetEntry(i);
Float_t max_b=b;
Float_t max_nwAB=nwAB;
Float_t max_npa=npa;
Float_t min_b=b;
Float_t min_nwAB=nwAB;
Float_t min_npa=npa;
}

for (Int_t i=1; i<nentries; i++) {
events->GetEntry(i);

if (b>max_b) max_b=b;
if (nwAB>max_nwAB) max_nwAB=nwAB;
if (npa>max_npa) max_npa=npa;
if (b<min_b) min_b=b;
if (nwAB<min_nwAB) min_nwAB=nwAB;
if (npa<min_npa) min_npa=npa;

}

cout <<"b min: "<<min_b<<", "<< "b max: " << max_b << endl;
cout <<"N_w min: "<<min_nwAB<<", "<<"N_w max: "<< max_nwAB << endl;
cout <<"RDS min: "<<min_npa<<", "<<"RDS max: "<< max_npa << endl;
cout <<endl;

*out <<"b min: "<<min_b<<", "<< "b max: " << max_b << endl;
*out <<"N_w min: "<<min_nwAB<<", "<<"N_w max: "<< max_nwAB << endl;
*out <<"RDS min: "<<min_npa<<", "<<"RDS max: "<< max_npa << endl;
*out << endl;

const Int_t nbin_b=400;
const Int_t nbin_nw=max_nwAB-min_nwAB;
const Int_t nbin_npa=max_npa-min_npa;

if (min_b==max_b){
min_b=min_b-0.01;
max_b=max_b+0.01;
}

TH1D* hist_b = new TH1D("hist_b","hist_b",nbin_b,min_b,max_b+0.1*max_b);
TH1D* hist_nw = new TH1D("hist_nw","hist_nw",nbin_nw,min_nwAB-0.5,0.5+max_nwAB);
TH1D* hist_npa = new TH1D("hist_npa","hist_npa",nbin_npa,min_npa-0.5,0.5+max_npa);

for (Int_t i=0; i<nentries; i++) {
events->GetEntry(i);
hist_b->Fill(b);
hist_nw->Fill(nwAB);
hist_npa->Fill(npa);
}

Int_t i;
Float_t cent_b,cont_b,sum_b=0;
Float_t tab_b[nbin_b],tab_sum_b[nbin_b];

//calculation of values of impact parameter
//in each 5% centrality bin

for (i=1;i<=nbin_b;i++){
cont_b=hist_b->GetBinContent(i);
sum_b+=(cont_b/(Float_t)nentries);
tab_b[i-1]=hist_b->GetBinCenter(i);
tab_sum_b[i-1]=sum_b;
}

Float_t tr=0.05;
Float_t dtr=0.05;
Int_t k=0;
Float_t tab_cent_b[19];
while (tr<1){
for (i=0;i<nbin_b;i++)
if (tab_sum_b[i]>tr) {
tab_cent_b[k]=tab_b[i];
break;
}
tr+=dtr;
k++;
}

Float_t cont_nw,sum_nw=0;
Float_t tab_nw[nbin_nw],tab_sum_nw[nbin_nw];

//calculation of values of number of wounded nucleons
//in each 5% centrality bin

Int_t j=nbin_nw-1;
for (i=1;i<=nbin_nw;i++){
cont_nw=hist_nw->GetBinContent(j);
sum_nw+=(cont_nw/(Float_t)nentries);
tab_nw[i-1]=hist_nw->GetBinCenter(i);
tab_sum_nw[j]=sum_nw;
j--;
}

tr=0.05;
dtr=0.05;
k=0;
Float_t tab_cent_nw[19];
while (tr<1){
for (i=nbin_nw;i>=0;i--)
if (tab_sum_nw[i]>tr) {
tab_cent_nw[k]=tab_nw[i];
break;
}
tr+=dtr;
k++;
}

Float_t cont_npa,sum_npa=0;
Float_t tab_npa[nbin_npa],tab_sum_npa[nbin_npa];

//calculation of values of RDS
//in each 5% centrality bin

j=nbin_npa-1;
for (i=1;i<=nbin_npa;i++){
cont_npa=hist_npa->GetBinContent(j);
sum_npa+=(cont_npa/(Float_t)nentries);
tab_npa[i-1]=hist_npa->GetBinCenter(i);
tab_sum_npa[j]=sum_npa;
j--;
}

tr=0.05;
dtr=0.05;
k=0;
Float_t tab_cent_npa[19];
while (tr<1){
for (i=nbin_npa;i>=0;i--)
if (tab_sum_npa[i]>tr) {
tab_cent_npa[k]=tab_npa[i];
break;
}
tr+=dtr;
k++;
}
cout << " c  "<<" --> "<<" b      "<<" N_w     "<<" RDS "<<endl;
*out << " c  "<<" --> "<<" b      "<<" N_w     "<<" RDS "<<endl;

for (i=0;i<19;i++) {
cout<<"0-"<<dtr*(i+1)*100<<"\% --> " <<tab_cent_b[i]<<", "<<tab_cent_nw[i]<<", "<<tab_cent_npa[i]<<endl;
*out<<"0-"<<dtr*(i+1)*100<<"\% --> " <<tab_cent_b[i]<<", "<<tab_cent_nw[i]<<", "<<tab_cent_npa[i]<<endl;

}

f->Close("R");
//hfile->Write();
out->close();

Float_t m=0.2;

Double_t zakd_b=min_b-m*min_b;
Double_t zakd_nw=min_nwAB-m*min_nwAB;
Double_t zakd_npa=min_npa-m*min_npa;

Double_t zakg_b=max_b+m*max_b;
Double_t zakg_nw=max_nwAB+m*max_nwAB;
Double_t zakg_npa=max_npa+m*max_npa;

Float_t label_size=0.04;
Float_t title_size=0.05;
Float_t title_offset=0.8;

gStyle->SetOptStat(10000000);
gStyle->SetStatBorderSize(0);
gStyle->SetPalette(0);

  TCanvas *c1= new TCanvas("c1", "cent vs b",650, 600);
  c1->Range(0,0,25,18);
  c1->SetFillColor(0);

  label(inpfile);   

pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.78,33);
pad1->Draw();
pad1->cd();
pad1->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

  TH2F *hRadii1 = new TH2F("hRadii1","",100, zakd_b, zakg_b, 100, 0, 1.1);
	//create empty histogram

	hRadii1->SetStats(kFALSE);
   hRadii1->GetXaxis()->SetNdivisions(405);
   hRadii1->GetXaxis()->SetLabelSize(label_size);
   hRadii1->GetXaxis()->SetTitleSize(title_size);
   hRadii1->GetXaxis()->SetTitleOffset(title_offset);
   hRadii1->SetXTitle("b [fm]  ");
	
 hRadii1->GetYaxis()->SetNdivisions(606);
 hRadii1->GetYaxis()->SetLabelSize(label_size);
 hRadii1->GetYaxis()->SetTitleSize(title_size);
 hRadii1->GetYaxis()->SetTitleOffset(title_offset);
 hRadii1->SetYTitle("centrality  ");
 hRadii1->Draw();
	
       cent_vs_b = new TGraph(nbin_b,tab_b,tab_sum_b);
       cent_vs_b->SetLineStyle(1);
       cent_vs_b->SetLineColor(2);
       cent_vs_b->SetLineWidth(3);
       cent_vs_b->Draw("L");
              

  c1->Modified();
  c1->Update();
  c1->SaveAs("centrality_vs_b.eps");


  TCanvas *c1_l= new TCanvas("c1_l", "cent vs b",650, 600);
  c1_l->Range(0,0,25,18);
  c1_l->SetFillColor(0);

  label(inpfile);   

pad1_l = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.78,33);
pad1_l->SetLogy();
pad1_l->Draw();
pad1_l->cd();
pad1_l->Range(-0.255174,-19.25,2.29657,-6.75);
 gPad->SetFillStyle(4000);
 gPad->SetFillColor(0);//29 grey
 
  TH2F *hRadii1_l = new TH2F("hRadii1_l","",100, zakd_b, zakg_b, 100, 0, 1.1);
	//create empty histogram

   hRadii1_l->SetStats(kFALSE);
   hRadii1_l->GetXaxis()->SetNdivisions(405);
   hRadii1_l->GetXaxis()->SetLabelSize(label_size);
   hRadii1_l->GetXaxis()->SetTitleSize(title_size);
   hRadii1_l->GetXaxis()->SetTitleOffset(title_offset);
   hRadii1_l->SetXTitle("b [fm]  ");
	
 hRadii1_l->GetYaxis()->SetNdivisions(606);
 hRadii1_l->GetYaxis()->SetLabelSize(label_size);
 hRadii1_l->GetYaxis()->SetTitleSize(title_size);
 hRadii1_l->GetYaxis()->SetTitleOffset(title_offset);
 hRadii1_l->SetYTitle("centrality  ");
 hRadii1_l->Draw();
	
       cent_vs_b_l = new TGraph(nbin_b,tab_b,tab_sum_b);
       cent_vs_b_l->SetLineStyle(1);
       cent_vs_b_l->SetLineColor(2);
       cent_vs_b_l->SetLineWidth(3);
       cent_vs_b_l->Draw("L");
              

  c1_l->Modified();
  c1_l->Update();
  c1_l->SaveAs("centrality_vs_b_log.eps");

  TCanvas *c2= new TCanvas("c2", "cent vs N_w",650, 600);
  c2->Range(0,0,25,18);
  c2->SetFillColor(0);

   label(inpfile);

pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

  TH2F *hRadii2 = new TH2F("hRadii2","",100, zakd_nw, zakg_nw, 100, 0, 1.1);
	//create empty histogram

   hRadii2->SetStats(kFALSE);
   hRadii2->GetXaxis()->SetNdivisions(405);
   hRadii2->GetXaxis()->SetLabelSize(label_size);
   hRadii2->GetXaxis()->SetTitleSize(title_size);
   hRadii2->GetXaxis()->SetTitleOffset(title_offset);
   hRadii2->SetXTitle("N_{w}  ");
	
 hRadii2->GetYaxis()->SetNdivisions(606);
 hRadii2->GetYaxis()->SetLabelSize(label_size);
 hRadii2->GetYaxis()->SetTitleSize(title_size);
 hRadii2->GetYaxis()->SetTitleOffset(title_offset);
 hRadii2->SetYTitle("centrality  ");
 hRadii2->Draw();
	
       cent_vs_nw = new TGraph(nbin_nw,tab_nw,tab_sum_nw);
       cent_vs_nw->SetLineStyle(1);
       cent_vs_nw->SetLineColor(2);
       cent_vs_nw->SetLineWidth(3);
       cent_vs_nw->Draw("L");

  c2->Modified();
  c2->Update();                
  c2->SaveAs("centrality_vs_nw.eps");
  

TCanvas *c2_l= new TCanvas("c2_l", "cent vs N_w",650, 600);
  c2_l->Range(0,0,25,18);
  c2_l->SetFillColor(0);

   label(inpfile);

pad2_l = new TPad("pad2_l","This is pad2",0.02,0.02,0.98,0.78,33);
pad2_l->SetLogy();
pad2_l->Draw();
pad2_l->cd();
pad2_l->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

  TH2F *hRadii2_l = new TH2F("hRadii2_l","",100, zakd_nw, zakg_nw, 100, 0, 1.1);
	//create empty histogram

   hRadii2_l->SetStats(kFALSE);
   hRadii2_l->GetXaxis()->SetNdivisions(405);
   hRadii2_l->GetXaxis()->SetLabelSize(label_size);
   hRadii2_l->GetXaxis()->SetTitleSize(title_size);
   hRadii2_l->GetXaxis()->SetTitleOffset(title_offset);
   hRadii2_l->SetXTitle("N_{w}  ");
	
 hRadii2_l->GetYaxis()->SetNdivisions(606);
 hRadii2_l->GetYaxis()->SetLabelSize(label_size);
 hRadii2_l->GetYaxis()->SetTitleSize(title_size);
 hRadii2_l->GetYaxis()->SetTitleOffset(title_offset);
 hRadii2_l->SetYTitle("centrality  ");
 hRadii2_l->Draw();
	
       cent_vs_nw_l = new TGraph(nbin_nw,tab_nw,tab_sum_nw);
       cent_vs_nw_l->SetLineStyle(1);
       cent_vs_nw_l->SetLineColor(2);
       cent_vs_nw_l->SetLineWidth(3);
       cent_vs_nw_l->Draw("L");

  c2_l->Modified();
  c2_l->Update();                
  c2_l->SaveAs("centrality_vs_nw_log.eps");


  TCanvas *c3= new TCanvas("c3", "cent vs RDS",650, 600);
  c3->Range(0,0,25,18);
  c3->SetFillColor(0);

   label(inpfile);

pad3 = new TPad("pad3","This is pad3",0.02,0.02,0.98,0.78,33);
pad3->Draw();
pad3->cd();
pad3->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);
  
  TH2F *hRadii3 = new TH2F("hRadii3","",100, zakd_npa, zakg_npa, 100, 0, 1.1);
	//create empty histogram

   hRadii3->SetStats(kFALSE);
   hRadii3->GetXaxis()->SetNdivisions(405);
   hRadii3->GetXaxis()->SetLabelSize(label_size);
   hRadii3->GetXaxis()->SetTitleSize(title_size);
   hRadii3->GetXaxis()->SetTitleOffset(title_offset);
   hRadii3->SetXTitle("RDS  ");
	
 hRadii3->GetYaxis()->SetNdivisions(606);
 hRadii3->GetYaxis()->SetLabelSize(label_size);
 hRadii3->GetYaxis()->SetTitleSize(title_size);
 hRadii3->GetYaxis()->SetTitleOffset(title_offset);
 hRadii3->SetYTitle("centrality  ");
 hRadii3->Draw();
	
       cent_vs_npa = new TGraph(nbin_npa,tab_npa,tab_sum_npa);
       cent_vs_npa->SetLineStyle(1);
       cent_vs_npa->SetLineColor(2);
       cent_vs_npa->SetLineWidth(3);
       cent_vs_npa->Draw("L");
  
  c3->Modified();
  c3->Update();            
  c3->SaveAs("centrality_vs_RDS.eps");
    
  
  TCanvas *c3_l= new TCanvas("c3_l", "cent vs RDS",650, 600);
  c3_l->Range(0,0,25,18);
  c3_l->SetFillColor(0);

   label(inpfile);

pad3_l = new TPad("pad3_l","This is pad3",0.02,0.02,0.98,0.78,33);
pad3_l->SetLogy();
pad3_l->Draw();
pad3_l->cd();
pad3_l->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

  TH2F *hRadii3_l = new TH2F("hRadii3_l","",100, zakd_npa, zakg_npa, 100, 0, 1.1);
	//create empty histogram

   hRadii3_l->SetStats(kFALSE);
   hRadii3_l->GetXaxis()->SetNdivisions(405);
   hRadii3_l->GetXaxis()->SetLabelSize(label_size);
   hRadii3_l->GetXaxis()->SetTitleSize(title_size);
   hRadii3_l->GetXaxis()->SetTitleOffset(title_offset);
   hRadii3_l->SetXTitle("RDS  ");
	
 hRadii3_l->GetYaxis()->SetNdivisions(606);
 hRadii3_l->GetYaxis()->SetLabelSize(label_size);
 hRadii3_l->GetYaxis()->SetTitleSize(title_size);
 hRadii3_l->GetYaxis()->SetTitleOffset(title_offset);
 hRadii3_l->SetYTitle("centrality  ");
 hRadii3_l->Draw();
	
       cent_vs_npa_l = new TGraph(nbin_npa,tab_npa,tab_sum_npa);
       cent_vs_npa_l->SetLineStyle(1);
       cent_vs_npa_l->SetLineColor(2);
       cent_vs_npa_l->SetLineWidth(3);
       cent_vs_npa_l->Draw("L");
  
  c3_l->Modified();
  c3_l->Update();            
  c3_l->SaveAs("centrality_vs_RDS_log.eps");

//hfile->Close("R");
    
}
