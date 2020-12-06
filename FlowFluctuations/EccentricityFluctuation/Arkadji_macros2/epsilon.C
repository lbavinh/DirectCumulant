/** \file epsilon.C
 * Script generating the plots of eccentricities and their scaled standard deviations as functions of the 
 * number of wounded nucleons (part of GLISSANDO 2)
 */

#include "label.C"

//! produces plots of the mean and the scaled standard deviation of the eccentricities as functions of the number of wounded nucleons
/*! Produce plots of the mean and the scaled standard deviation of the eccentricities as functions of the number of wounded nucleons */
void epsilon(
 char *p //!< name of the ROOT input file
            ) {

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);
/*
TH1D *h = ((TH1D*)f->Get("neps2")); 

TAxis *xaxis = h->GetXaxis();
Int_t ima=(xaxis->GetNbins());
Float_t ima_w=(xaxis->GetBinWidth(1));

Float_t zas=ima_w*ima;

for (Int_t i=1;i<=ima;i++) {
Float_t v =(h->GetBinContent(i));
if (v>0){
h->SetBinContent(i,sqrt(v));
}else{
h->SetBinContent(i,0.0);
}
}

*/

Int_t reb;
//reb=1 - number of bins as in original histigram
//reb=x - x times smaller number of bins
cout << "Warning: this script makes sense for the minimum-bias case" << endl << 
        "Give the rebinning parameter (a small natural number): ";
cin >> reb;
cout << endl;

//TH1D *hnew = (TH1D*)h -> Rebin(reb,"hnew");
//hnew -> Scale(1./reb);

Float_t label_size=0.04;
Float_t title_size=0.05;
Float_t title_offset=0.8;

TCanvas *c2 = new TCanvas("c2","sigma epsilon",650,600);
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

//hnew->SetStats(kFALSE);

//hnew->Draw();

TH1D *hp = (TH1D*)f->Get("nepsp2"); 

TAxis *xaxis = hp->GetXaxis();
Int_t ima=(xaxis->GetNbins());
Float_t ima_w=(xaxis->GetBinWidth(1));

Float_t zas=ima_w*ima;


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

hnewp->SetTitle("");
hnewp->SetXTitle("N_{w}");
hnewp->GetXaxis()->SetLabelSize(label_size);
hnewp->GetYaxis()->SetLabelSize(label_size);
hnewp->GetXaxis()->SetTitleSize(title_size);
hnewp->GetYaxis()->SetTitleSize(title_size);
hnewp->GetXaxis()->SetTitleOffset(title_offset);
hnewp->GetYaxis()->SetTitleOffset(title_offset);
hnewp->GetYaxis()->SetRangeUser(0.,1.5);
hnewp->SetYTitle("#Delta#epsilon*/#epsilon*    ");
hnewp->SetLineColor(4);
hnewp->SetLineColor(2);
hnewp->SetLineStyle(2);
hnewp->SetStats(kFALSE);
hnewp->Draw();

Float_t ymax=sqrt(4/3.14159265-1);
Float_t start=0.75*zas;
TLine *liml = new TLine(start,ymax,zas,ymax);
liml->Draw("SAME");

//TLegend *leg = new TLegend(0.2,0.7,0.35,0.8);
//  leg->AddEntry(hnew, "#Delta#epsilon/#epsilon", "l");
//  leg->AddEntry(hnewp, "#Delta#epsilon*/#epsilon*", "l");
//  leg->Draw("SAME");

c2->SaveAs("sigma_epsilon.eps");

//TH1D *heps = ((TH1D*)f->Get("neps")); 
//TH1D *hepsnew = (TH1D*)heps -> Rebin(reb,"hepsnew");
//hepsnew -> Scale(1./reb);

//hepsnew->SetStats(kFALSE);

TCanvas *c4 = new TCanvas("c4","epsilon",650,600);
 c4->cd(1);
 c4->Range(0,0,25,18);
 c4->SetFillColor(0);
 label(inpfile); 

pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

//hepsnew->Draw();

TH1D *hpeps = (TH1D*)f->Get("nepsp"); 

TH1D *hpepsnew = (TH1D*)hpeps -> Rebin(reb,"hpepsnew");
hpepsnew -> Scale(1./reb);

hpepsnew->SetTitle("");
hpepsnew->SetXTitle("N_{w}");
hpepsnew->GetXaxis()->SetLabelSize(label_size);
hpepsnew->GetYaxis()->SetLabelSize(label_size);
hpepsnew->GetXaxis()->SetTitleSize(title_size);
hpepsnew->GetYaxis()->SetTitleSize(title_size);
hpepsnew->GetXaxis()->SetTitleOffset(title_offset);
hpepsnew->GetYaxis()->SetTitleOffset(title_offset);
hpepsnew->GetYaxis()->SetRangeUser(0,1.05);
hpepsnew->SetYTitle("#epsilon*    ");
hpepsnew->SetLineColor(2);
hpepsnew->SetLineColor(4);
hpepsnew->SetLineStyle(2);

hpepsnew->SetStats(kFALSE);
hpepsnew->Draw();

//TLegend *legeps = new TLegend(0.2,0.7,0.35,0.8);
//  legeps->AddEntry(hepsnew, "#epsilon", "l");
//  legeps->AddEntry(hpepsnew, "#epsilon*", "l");
//  legeps->Draw("SAME");

c4->SaveAs("epsilon.eps");

//c4->SaveAs("epsilon.C");

}
