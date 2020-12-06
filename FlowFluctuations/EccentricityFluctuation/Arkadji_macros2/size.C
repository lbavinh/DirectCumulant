/** \file size.C
 * Script plotting the event-by-event scaled standard deviation of the size parameter <r>, defined as 
 * the average distance of sources from the center of mass
 * (part of GLISSANDO 2)
 * 
 */

#include "label.C"

//! Produces the plot of the scaled standard deviation of the size parameter 
/*! Produces the plot of the scaled standard deviation of the size parameter. Used for the transverse momentum fuctuations. */
void size(
 char *p  //!< name of the ROOT input file
         ) {

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TH1D *h = ((TH1D*)f->Get("nsize2")); 
TAxis *xaxis = h->GetXaxis();

h->SetTitle("scaled standard deviation of the size vs. N_{W}");
h->SetXTitle("N_{W} ");
h->SetYTitle("#Delta <r>/<<r>>  ");

int ima=(xaxis->GetNbins());
float ima_w=(xaxis->GetBinWidth(1));

float zas=ima_w*ima;

for (int i=1;i<=ima;i++) {
float v =(h->GetBinContent(i));
if (v>0){
h->SetBinContent(i,sqrt(v));
}else{
h->SetBinContent(i,0.0);
}
}


int reb;
//reb=1 - number of bins as in original histigram
//reb=x - x times smaller number of bins
cout << "give the rebinning parameter (a small natural number): ";
cin >> reb;
cout << endl;

TH1D *hnew = (TH1D*)h -> Rebin(reb,"hnew");
hnew -> Scale(1./reb);

float label_size=0.04;
float title_size=0.05;
float title_offset=0.8;

TCanvas *c2 = new TCanvas("c2","size",650,600);
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

hnew->SetStats(kFALSE);

hnew->Draw();

c2->SaveAs("sigma_r.eps");


}
