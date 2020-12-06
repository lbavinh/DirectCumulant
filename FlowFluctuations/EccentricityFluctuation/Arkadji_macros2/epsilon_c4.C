/** \file epsilon_c4.C
 * Script generating the plots of participant eccentricities and their scaled standard deviations as functions of centrality (part of GLISSANDO 2)
 */

#include "label.C"

#include "data_ALICE.C"

//! produces plots of the mean and the scaled standard deviation of the participant eccentricities as functions of centrality
/*! Produce plots of the mean and the scaled standard deviation of the participant eccentricities as functions of centrality. Centrality 
is determined from the number of wounded nucleons. */

void epsilon_c4(
 char *p //!< name of the ROOT input file
            ) {

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);
TH1D *ho = ((TH1D*)f->Get("nepsp")); 
TH1D *ho2 = ((TH1D*)f->Get("nepsp2"));
TH1D *ho22 = ((TH1D*)f->Get("nepsp22"));

TH1D *n = ((TH1D*)f->Get("nuni")); 

TAxis *xaxis = ho->GetXaxis();
Int_t ima=(xaxis->GetNbins());
Float_t ima_w=(xaxis->GetBinWidth(1));
Float_t zas=ima_w*ima;
Float_t sc=(n->Integral());

Float_t bins[416];
Int_t  binnum = ima; 

bins[0]=0;

for (Int_t i=1;i<=ima;i++) {bins[i]=bins[i-1]+(n->GetBinContent(ima-i+1))/sc;};

TH1D* h = new TH1D("n","t", binnum, bins);
TH1D* h4 = new TH1D("n4","t4", binnum, bins);


for (Int_t i=1;i<=ima;i++) {
Float_t v =(ho2->GetBinContent(i));
if (v>0){
         h->SetBinContent(ima-i+1,sqrt(v));
        } else
        {
         h->SetBinContent(i,0.0);
        }
                            }

for (Int_t i=1;i<=ima;i++) {
Float_t w =(ho->GetBinContent(i));
Float_t w2 =(ho2->GetBinContent(i))*w*w+w*w;
Float_t w22 =(ho22->GetBinContent(i));
Float_t w4=sqrt(2.*w2*w2-w22);
if (w2>w4){
         h4->SetBinContent(ima-i+1,sqrt((w2-w4)/(w2+w4)));
        } else
        {
         h4->SetBinContent(i,0.0);
        }
                            }



Int_t reb;
//reb=1 - number of bins as in original histigram
//reb=x - x times smaller number of bins
cout << "Warning: this script makes sense for the minimum-bias case" << endl << 
        "Give the rebinning parameter (a small natural number): ";
cin >> reb;
cout << endl;

TH1D *hnew = (TH1D*)h -> Rebin(reb,"hnew");
hnew -> Scale(1./reb);

TH1D *h4new = (TH1D*)h4 -> Rebin(reb,"h4new");
h4new -> Scale(1./reb);


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

hnew->SetStats(kFALSE);

hnew->SetTitle("");
hnew->SetXTitle("centrality");
hnew->GetXaxis()->SetLabelSize(label_size);
hnew->GetYaxis()->SetLabelSize(label_size);
hnew->GetXaxis()->SetTitleSize(title_size);
hnew->GetYaxis()->SetTitleSize(title_size);
hnew->GetXaxis()->SetTitleOffset(title_offset);
hnew->GetYaxis()->SetTitleOffset(title_offset);
hnew->GetYaxis()->SetRangeUser(0.,0.8);
hnew->SetYTitle("#Delta#epsilon*/<#epsilon*>, #Deltav_{2}/<v_{2}>   ");
hnew->SetLineColor(2);
h4new->SetLineColor(4);
hnew->SetLineStyle(1);
h4new->SetLineStyle(2);

hnew->Draw();
h4new->Draw("SAME");

data_ALICE();


Float_t ymax=sqrt(4/3.14159265-1);
TLine *liml = new TLine(0,ymax,0.2,ymax);
liml->Draw("SAME");

c2->SaveAs("sigma_epsilon_c.eps");
c2->SaveAs("sigma_epsilon_c.C");

TH1D *hepso = ((TH1D*)f->Get("nepsp")); 

TH1D* heps = new TH1D("n","t", binnum, bins);

for (Int_t i=1;i<=ima;i++) {
Float_t v =(hepso->GetBinContent(i));
heps->SetBinContent(ima-i+1,v);
}


TH1D *hepsnew = (TH1D*)heps -> Rebin(reb,"hepsnew");
hepsnew -> Scale(1./reb);

hepsnew->SetStats(kFALSE);

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

hepsnew->Draw();

hepsnew->SetTitle("");
hepsnew->SetXTitle("centrality");
hepsnew->GetXaxis()->SetLabelSize(label_size);
hepsnew->GetYaxis()->SetLabelSize(label_size);
hepsnew->GetXaxis()->SetTitleSize(title_size);
hepsnew->GetYaxis()->SetTitleSize(title_size);
hepsnew->GetXaxis()->SetTitleOffset(title_offset);
hepsnew->GetYaxis()->SetTitleOffset(title_offset);
hepsnew->GetYaxis()->SetRangeUser(0,1.05);
hepsnew->SetYTitle("#epsilon*    ");
hepsnew->SetLineColor(4);
hepsnew->SetLineStyle(2);

c4->SaveAs("epsilon_c.eps");
//c4->SaveAs("epsilon_c.C");

}
