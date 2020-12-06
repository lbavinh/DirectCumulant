 /** \file centrality2.C
 * Script generating the centrality classes (alternative to centrality.C)
 * (part of GLISSANDO 2)
 * 
 */

#include "label.C"

// Produces centrality windows for the stored Root file.
// This makes sense for minimum bias calculations.
// Plot centrality versus number of wounded nucleons,
// weight, and impact parameter

//! generate the centrality classes
/*! Centrality classes are generated in the total number of wounded nucleons, relative deposited strenth (RDS), and the 
    impact parameter. Plots of distributions divided into classes are produced. The script makes sense for the minimum-bias simulations. */
void centrality2(
 char *p //!< name of the ROOT input file
                ) {

gROOT->Reset();

ofstream *out = new ofstream;
out->open("centrality2.dat");

cout << endl << "Determination of the centrality classes" << endl;
cout <<  "(Warning: this script makes sense for minimum-bias events)" << endl << endl;
*out << endl << "Determination of the centrality classes" << endl;
*out <<  "(Warning: this script makes sense for minimum-bias events)" << endl << endl;

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << ", writes to centrality2.dat" << endl;  
 *out << "reads from: " << inpfile << ", writes to centrality2.dat" << endl;  

cout << endl << "(number of bins in b and RDS determines the resolution)" << endl;

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
Float_t max_nw=nwAB;
Float_t max_npa=npa;
Float_t min_b=b;
Float_t min_nw=nwAB;
Float_t min_npa=npa;
}

for (Int_t i=1; i<nentries; i++) {
events->GetEntry(i);

if (b>max_b) max_b=b;
if (nwAB>max_nw) max_nw=nwAB;
if (npa>max_npa) max_npa=npa;
if (b<min_b) min_b=b;
if (nwAB<min_nw) min_nw=nwAB;
if (npa<min_npa) min_npa=npa;

}

cout <<"b min: "<<min_b<<", "<< "b max: " << max_b << endl;
cout <<"N_w min: "<<min_nw<<", "<<"N_w max: "<< max_nw << endl;
cout <<"RDS min: "<<min_npa<<", "<<"RDS max: "<< max_npa << endl;
cout << endl << endl;

*out <<"b min: "<<min_b<<", "<< "b max: " << max_b << endl;
*out <<"N_w min: "<<min_nw<<", "<<"N_w max: "<< max_nw << endl;
*out <<"RDS min: "<<min_npa<<", "<<"RDS max: "<< max_npa << endl;
*out << endl;


if (min_b==max_b){
min_nb=min_b-0.01;
max_b=max_b+0.01;
}


const Int_t nbin_b=600;
const Int_t nbin_nw=(max_nw-min_nw);
const Int_t nbin_npa=600;
// const Int_t nbin_npa=(max_npa-min_npa);

const Float_t st_b=(max_b-min_b)/nbin_b;
const Float_t st_nw=(max_nw-min_nw)/nbin_nw;
const Float_t st_npa=(max_npa-min_npa)/nbin_npa;

TH1D* hist_b = new TH1D("hist_b","hist_b",nbin_b+1,min_b-st_b/2.,max_b+st_b/2.);
TH1D* hist_nw = new TH1D("hist_nw","hist_nw",nbin_nw+1,min_nw-st_nw/2.,max_nw+st_nw/2.);
TH1D* hist_npa = new TH1D("hist_npa","hist_npa",nbin_npa+1,min_npa-st_npa/2.,max_npa+st_npa/2.);

for (Int_t i=0; i<nentries; i++) {
events->GetEntry(i);
hist_b->Fill(b);
hist_nw->Fill(nwAB);
hist_npa->Fill(npa);
}

bool s5, s10, s20, s30, s40, s50, s60, s70, s80, s90;
Float_t tot;
TAxis *xaxis;
Int_t ima;
Float_t w, v, sum, run;
Int_t j;
TH1D *h, *h2, *h3;
 
// ---------

h=hist_b;

tot= h->Integral();

cout << "number of entries: " << tot << endl << endl;
*out << "number of entries: " << tot << endl << endl;

xaxis = h->GetXaxis();
ima=(xaxis->GetNbins());
w=(xaxis->GetBinWidth(1));
sum = 0;
s5=true, s10=true, s20=true, s30=true, s40=true, s50=true, s60=true, s70=true, s80=true, s90=true;

cout <<  "centrality --> range in b " << endl << endl;
*out <<  "centrality --> range in b " << endl << endl;

//for(Int_t i=ima;i>0;i--) {
for (Int_t i=1;i<ima;i++) {
v=(h->GetBinContent(i)); 
sum+=v; run=100.*sum/tot;
//if(v>0){cout << "debug:  " << run << "% ---> b=" << (i-1)*w+min_b << endl;}
if(run>5 && s5){cout <<   " 0- 5%  --> [" << min_b << "," << (i)*w+min_b << "]" << endl; *out <<   " 0- 5%  --> [" << min_b << "," << (i)*w+min_b << "]" << endl; s5=false;j=i-1;
 TLine *lim5 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>10 && s10){cout << " 5-10%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << " 5-10%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s10=false;j=i-1;
 TLine *lim10 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>20 && s20){cout << "10-20%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "10-20%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s20=false;j=i-1;
 TLine *lim20 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>30 && s30){cout << "20-30%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "20-30%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s30=false;j=i-1;
 TLine *lim30 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>40 && s40){cout << "30-40%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "30-40%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s40=false;j=i-1;
 TLine *lim40 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>50 && s50){cout << "40-50%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "40-50%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s50=false;j=i-1;
 TLine *lim50 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>60 && s60){cout << "50-60%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "50-60%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s60=false;j=i-1; Float_t maxpl=v;
 TLine *lim60 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>70 && s70){cout << "60-70%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "60-70%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s70=false;j=i-1;
 TLine *lim70 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>80 && s80){cout << "70-80%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "70-80%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s80=false;j=i-1;
 TLine *lim80 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);};
if(run>90 && s90){cout << "80-90%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; *out << "80-90%  --> [" << j*w+min_b << "," << (i)*w+min_b << "]" << endl; s90=false;j=i-1;
 TLine *lim90 = new TLine((i-0.5)*w+min_b,0.,(i-0.5)*w+min_b,v);
                  cout << "90-100% --> [" << j*w+min_b << "," << max_b << "]" << endl; *out << "90-100% --> [" << j*w+min_b << "," << max_b << "]" << endl;};

};

TCanvas *cb = new TCanvas("cb","centrality classes in b",650,600);
cb->cd(1);
cb->Range(0,0,25,18);
cb->SetFillColor(0);

label(inpfile);

padb = new TPad("padb","c(b)",0.02,0.02,0.98,0.78,33);
padb->Draw();
padb->cd();
padb->SetFillStyle(4000);
padb->SetFillColor(0);

// h->GetYaxis()->SetRangeUser(0.,1.5*maxpl);

h->SetTitle("division into 0-5%, 5-10%, 10-20%, 20-30%, ..., 90-100% centrality classes");
h->SetXTitle("b [fm]   ");
h->SetLineColor(kCyan);


h->Draw();

lim5 ->Draw("SAME");lim10 ->Draw("SAME");lim20 ->Draw("SAME");lim30 ->Draw("SAME");lim40 ->Draw("SAME");
lim50 ->Draw("SAME");lim60 ->Draw("SAME");lim70 ->Draw("SAME");lim80 ->Draw("SAME");lim90 ->Draw("SAME");

cb->SaveAs("centrality_b.eps");

// ---------

h=hist_nw;

tot= h->Integral();

/*
// debug
cout << (h->Integral(1,3))/tot*100. << endl;
cout << (h->Integral(4,8))/tot*100. << endl;
cout << (h->Integral(9,19))/tot*100. << endl;
cout << (h->Integral(20,37))/tot*100. << endl;
cout << (h->Integral(38,64))/tot*100. << endl;
cout << (h->Integral(65,103))/tot*100. << endl;
cout << (h->Integral(104,155))/tot*100. << endl;
cout << (h->Integral(156,222))/tot*100. << endl;
cout << (h->Integral(223,308))/tot*100. << endl;
cout << (h->Integral(309,360))/tot*100. << endl;
cout << (h->Integral(361,415))/tot*100. << endl;
*/

cout << endl << endl << "number of entries: " << tot << endl << endl;
*out << endl << endl << "number of entries: " << tot << endl << endl;

xaxis = h->GetXaxis();
ima=(xaxis->GetNbins());
w=(xaxis->GetBinWidth(1));
sum = 0;
s5=true, s10=true, s20=true, s30=true, s40=true, s50=true, s60=true, s70=true, s80=true, s90=true;


cout <<  "centrality --> range in N_w " << endl << endl;
*out <<  "centrality --> range in N_w " << endl << endl;


for(Int_t i=ima;i>0;i--) {
//for (Int_t i=1;i<ima;i++) {
v=(h->GetBinContent(i)); 
sum+=v; run=100.*sum/tot;
//if(v>0){cout << "debug:  " << run << "% ---> N_w=" << (i-1)*w+min_nw << endl;}
if(run>5 && s5){cout <<   " 0- 5%  --> [" << max_nw << "," << (i)*w+min_nw << "]" << endl; *out <<   " 0- 5%  --> [" << max_nw << "," << (i)*w+min_nw << "]" << endl; s5=false;j=i-1;
 TLine *lim5 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>10 && s10){cout << " 5-10%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << " 5-10%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s10=false;j=i-1;
 TLine *lim10 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>20 && s20){cout << "10-20%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "10-20%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s20=false;j=i-1;
 TLine *lim20 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>30 && s30){cout << "20-30%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "20-30%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s30=false;j=i-1;
 TLine *lim30 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>40 && s40){cout << "30-40%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "30-40%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s40=false;j=i-1;
 TLine *lim40 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>50 && s50){cout << "40-50%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "40-50%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s50=false;j=i-1;
 TLine *lim50 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>60 && s60){cout << "50-60%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "50-60%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s60=false;j=i-1; Float_t maxpl=v;
 TLine *lim60 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>70 && s70){cout << "60-70%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "60-70%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s70=false;j=i-1;
 TLine *lim70 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>80 && s80){cout << "70-80%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "70-80%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s80=false;j=i-1;
 TLine *lim80 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);};
if(run>90 && s90){cout << "80-90%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; *out << "80-90%  --> [" << j*w+min_nw << "," << (i)*w+min_nw << "]" << endl; s90=false;j=i-1;
 TLine *lim90 = new TLine((i-0.5)*w+min_nw,0.,(i-0.5)*w+min_nw,v);
                  cout << "90-100% --> [" << j*w+min_nw << "," << min_nw << "]" << endl; *out << "90-100% --> [" << j*w+min_nw << "," << min_nw << "]" << endl;};

};


TCanvas *cnw = new TCanvas("cnw","centrality classes in N_w",650,600);
cnw->cd(1);
cnw->Range(0,0,25,18);
cnw->SetFillColor(0);

label(inpfile);

padnw = new TPad("padnw","c(N_w)",0.02,0.02,0.98,0.78,33);
padnw->Draw();
padnw->cd();
padnw->SetFillStyle(4000);
padnw->SetFillColor(0);

h->GetYaxis()->SetRangeUser(0.,1.5*maxpl);

h->SetTitle("division into 0-5%, 5-10%, 10-20%, 20-30%, ..., 90-100% centrality classes");
h->SetXTitle("N_{W}   ");
h->SetLineColor(kCyan);


h->Draw();

lim5 ->Draw("SAME");lim10 ->Draw("SAME");lim20 ->Draw("SAME");lim30 ->Draw("SAME");lim40 ->Draw("SAME");
lim50 ->Draw("SAME");lim60 ->Draw("SAME");lim70 ->Draw("SAME");lim80 ->Draw("SAME");lim90 ->Draw("SAME");

cnw->SaveAs("centrality_nw.eps");

// ---------

h=hist_npa;

tot= h->Integral();

cout << endl << endl << "number of entries: " << tot << endl << endl;
*out << endl << endl << "number of entries: " << tot << endl << endl;

xaxis = h->GetXaxis();
ima=(xaxis->GetNbins());
w=(xaxis->GetBinWidth(1));
sum = 0;
s5=true, s10=true, s20=true, s30=true, s40=true, s50=true, s60=true, s70=true, s80=true, s90=true;


cout <<  "centrality --> range in RDS " << endl << endl;
*out <<  "centrality --> range in RDS " << endl << endl;


for(Int_t i=ima;i>0;i--) {
//for (Int_t i=1;i<ima;i++) {
v=(h->GetBinContent(i)); 
sum+=v; run=100.*sum/tot;
//if(v>0){cout << "debug:  " << run << "% ---> RDS=" << (i-1)*w+min_npa << endl;}
if(run>5 && s5){cout <<   " 0- 5%  --> [" << max_npa << "," << (i)*w+min_npa << "]" << endl; *out <<   " 0- 5%  --> [" << max_npa << "," << (i)*w+min_npa << "]" << endl; s5=false;j=i-1;
 TLine *lim5 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>10 && s10){cout << " 5-10%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << " 5-10%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s10=false;j=i-1;
 TLine *lim10 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>20 && s20){cout << "10-20%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "10-20%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s20=false;j=i-1;
 TLine *lim20 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>30 && s30){cout << "20-30%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "20-30%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s30=false;j=i-1;
 TLine *lim30 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>40 && s40){cout << "30-40%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "30-40%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s40=false;j=i-1;
 TLine *lim40 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>50 && s50){cout << "40-50%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "40-50%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s50=false;j=i-1;
 TLine *lim50 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>60 && s60){cout << "50-60%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "50-60%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s60=false;j=i-1; Float_t maxpl=v;
 TLine *lim60 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>70 && s70){cout << "60-70%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "60-70%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s70=false;j=i-1;
 TLine *lim70 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>80 && s80){cout << "70-80%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "70-80%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s80=false;j=i-1;
 TLine *lim80 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);};
if(run>90 && s90){cout << "80-90%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; *out << "80-90%  --> [" << j*w+min_npa << "," << (i)*w+min_npa << "]" << endl; s90=false;j=i-1;
 TLine *lim90 = new TLine((i-0.5)*w+min_npa,0.,(i-0.5)*w+min_npa,v);
                  cout << "90-100% --> [" << j*w+min_npa << "," << min_npa << "]" << endl; *out << "90-100% --> [" << j*w+min_npa << "," << min_npa << "]" << endl;};

};

TCanvas *cnpa = new TCanvas("cnpa","centrality classes in RDS",650,600);
cnpa->cd(1);
cnpa->Range(0,0,25,18);
cnpa->SetFillColor(0);

label(inpfile);

padnpa = new TPad("padnpa","c(RDS)",0.02,0.02,0.98,0.78,33);
padnpa->Draw();
padnpa->cd();
padnpa->SetFillStyle(4000);
padnpa->SetFillColor(0);

h->GetYaxis()->SetRangeUser(0.,1.*maxpl);

h->SetTitle("division into 0-5%, 5-10%, 10-20%, 20-30%, ..., 90-100% centrality classes");
h->SetXTitle("RDS   ");
h->SetLineColor(kCyan);

h->Draw();

lim5 ->Draw("SAME");lim10 ->Draw("SAME");lim20 ->Draw("SAME");lim30 ->Draw("SAME");lim40 ->Draw("SAME");
lim50 ->Draw("SAME");lim60 ->Draw("SAME");lim70 ->Draw("SAME");lim80 ->Draw("SAME");lim90 ->Draw("SAME");

cnpa->SaveAs("centrality_RDS.eps");

}

