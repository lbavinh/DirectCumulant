/** \file dxdy.C
 * Script generating the dispersion of the center-of-mass x and y coordinates
 * as a function of the number of wounded nucleons
 * (part of GLISSANDO 2)
 * 
 */

#include "label.C"

//! produce the plot of the dispersion of the center-of-mass x and y coordinates as a function of the number of wounded nucleons.
/*! Produces the plot of the standard deviation of the  x and y center-of-mass coordinates as a function of the number of wounded nucleons. */
void dxdy(
 char *p //!< name of the ROOT input file
         ) {

gROOT->Reset();

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TH1D *h = ((TH1D*)f->Get("nx2")); 
Int_t ima=(h->GetNbinsX());

for (Int_t i=1;i<=ima;i++) {
Float_t v =(h->GetBinContent(i));
if (v>0){
h->SetBinContent(i,sqrt(v));
}else{
h->SetBinContent(i,0.0);
}
}


Int_t reb;
//reb=1 - number of bins as in original histigram
//reb=x - x times smaller number of bins
cout << "give rebinning parameter (small natural number): ";
cin >> reb;
cout << endl;

TH1D *hnew = (TH1D*)h -> Rebin(reb,"hnew");
hnew -> Scale(1./reb);

TCanvas *c2 = new TCanvas("c2","dxdy",650,600);
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

TH1D *hp = (TH1D*)f->Get("ny2"); 
Int_t imap=(hp->GetNbinsX());

for (Int_t i=1;i<=imap;i++) {
Float_t vp =(hp->GetBinContent(i));

if (vp>0){
hp->SetBinContent(i,sqrt(vp));
}else{
hp->SetBinContent(i,0.0);
}
}

TH1D *hnewp = (TH1D*)hp -> Rebin(reb,"hnewp");
hnewp -> Scale(1./reb);

hnewp->SetTitle("dispersion of the center-of-mass");
hnew->GetXaxis()->SetLabelSize(0.04);
hnew->GetYaxis()->SetLabelSize(0.04);
hnew->GetXaxis()->SetTitleSize(0.05);
hnew->GetYaxis()->SetTitleSize(0.05);
hnew->GetXaxis()->SetTitleOffset(0.8);
hnew->GetYaxis()->SetTitleOffset(0.8);
hnewp->GetXaxis()->SetTitle("N_w ");


// hnew->GetYaxis()->SetRangeUser(0.,1.0);
hnewp->SetYTitle("#Delta x, #Delta y  [fm]  ");
hnew->SetLineColor(4);
hnewp->SetLineColor(2);
hnew->SetLineStyle(2);


hnewp->Draw();
hnew->Draw("SAME");

TLegend *leg = new TLegend(0.4,0.7,0.55,0.8);
  leg->AddEntry(hnew, "#Delta x", "l");
  leg->AddEntry(hnewp, "#Delta y", "l");
  leg->Draw("SAME");

c2->SaveAs("dxdy.eps");

}
