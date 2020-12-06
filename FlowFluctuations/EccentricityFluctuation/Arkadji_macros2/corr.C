 /** \file corr.C
 * Script generating the NN correlation plot for nucleus A 
 * (part of GLISSANDO 2)
 * 
 */


#include "label.C"

//! generating the plot of the radial NN correlation function, C(r), for nucleus A 
/*! C(r) is obtained via division of the correlated and uncorrelated distributions of the 
    relative distance in the nucleon pairs. Requires _profile_=1.
*/ 
void corr(
      char *p //!< name of the ROOT input file
         ) {


TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);
TH1D *h = ((TH1D*)f->Get("rrelA")); 
TH1D *hu = ((TH1D*)f->Get("rrel_u")); 

TAxis *xaxis = h->GetXaxis();
h->SetXTitle("r [fm] ");
h->SetYTitle("C(r) ");

Int_t ima=(xaxis->GetNbins());

for (Int_t i=1;i<=ima;i++) {
Double_t v =(h->GetBinContent(i));
Double_t vu =(hu->GetBinContent(i));
h->SetBinContent(i, 1.-v/(vu+0.000001));
}


TCanvas *c2 = new TCanvas("c2","correlation C(r)",650,600);
c2->cd(1);
c2->Range(0,0,25,18);
c2->SetFillColor(0);

label_fit(inpfile);


pad2 = new TPad("pad2","C(r)",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
//pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

h->SetTitle("Radial NN correlations in nucleus A");

h->GetYaxis()->SetRangeUser(-0.1,1.1);
h->GetXaxis()->SetRangeUser(0.,2.5);
h->SetLineColor(2);

h->SetXTitle("r [fm]");
h->SetYTitle("C(r)");

h->SetStats(kFALSE);

h->Draw();

TLine *liml = new TLine(0.,0.,2.5,0.);
liml->Draw("SAME");
TLine *liml2 = new TLine(0.,1.,2.5,1.);
liml2->Draw("SAME");

c2->SaveAs("corr.eps");
//c2->SaveAs("corr_data.C");

}

