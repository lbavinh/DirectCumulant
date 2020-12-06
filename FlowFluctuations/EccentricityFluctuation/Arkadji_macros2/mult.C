/** \file mult.C
 * Script plotting the event-by-event scaled variance of RDS vs. the number of wounded nucleons in the projectile
 * (part of GLISSANDO 2)
 * 
 */


#include "label.C"


//! produces plots of the scaled variance of RDS vs. the number of wounded nucleons in the projectile
/*! Produce the plot of the scaled variance of RDS vs. the number of wounded nucleons in the projectile. */

void mult(
 char *p //!< name of the ROOT input file
            ) {

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);
TH1D *h = ((TH1D*)f->Get("nwei2")); 
TAxis *xaxis = h->GetXaxis();

int ima=(xaxis->GetNbins());
Float_t ima_w=(xaxis->GetBinWidth(1));
Float_t zas=ima_w*ima;
int skip=0;

for (int i=1;i<=ima-skip;i++) {
Float_t v =(h->GetBinContent(i));
//if (v<500000){
h->SetBinContent(i,v);
//}else{
//h->SetBinContent(i,5);
//}
}


int reb;
//reb=1 - number of bins as in original histogram
//reb=x - x times smaller number of bins
cout << "give rebinning parameter (small natural number): ";
cin >> reb;
cout << endl;

TH1D *hnew = (TH1D*)h -> Rebin(reb,"hnew");
hnew -> Scale(1./reb);

Float_t label_size=0.04;
Float_t title_size=0.05;
Float_t title_offset=0.8;

TCanvas *c2 = new TCanvas("c2","omega (RDS)",650,600);
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
hnew->SetTitle("Scaled variance of the number of souces (RDS)");
hnew->SetXTitle("N_{proj}");
hnew->GetXaxis()->SetLabelSize(label_size);
hnew->GetYaxis()->SetLabelSize(label_size);
hnew->GetXaxis()->SetTitleSize(title_size);
hnew->GetYaxis()->SetTitleSize(title_size);
hnew->GetXaxis()->SetTitleOffset(title_offset);
hnew->GetYaxis()->SetTitleOffset(title_offset);
// hnew->GetYaxis()->SetRangeUser(0.,3);
hnew->SetYTitle("#omega_{s}  ");
hnew->SetLineColor(2);

hnew->Draw();


c2->SaveAs("om_RDS.eps");
//c2->SaveAs("om_RDS.C");

}
