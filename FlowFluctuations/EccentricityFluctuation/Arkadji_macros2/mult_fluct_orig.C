#include "label.C"

// Produces plots of the mean and scaled variance 
// of the weight (multiplicity) distributions
// as a function of number of wounded nucleons from projectile
void mult_fluct_orig(char *p) {

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TH1D *h = ((TH1D*)f->Get("nwei")); 
TAxis *xaxis = h->GetXaxis();

TAxis *xaxis = h->GetXaxis();
Int_t ima=(xaxis->GetNbins());
Float_t ima_w=(xaxis->GetBinWidth(1));

Float_t zas=ima_w*ima;

Float_t k,q;
cout << "Give scaling parameter"<<endl;
cin>>k;
cout << "Give acceptance parameter"<<endl;
cin>>q;


for (Int_t i=1;i<=ima;i++) {
Float_t v =(h->GetBinContent(i));
if (v>0){
h->SetBinContent(i,q*k*v);
}else{
h->SetBinContent(i,0.0);
}
}


Int_t reb;
//reb=1 - number of bins as in original histigram
//reb=x - x times smaller number of bins
cout << "give rebinning parameter: ";
cin >> reb;
cout << endl;

TH1D *hnew = (TH1D*)h -> Rebin(reb,"hnew");
hnew -> Scale(1./reb);

Float_t label_size=0.04;
Float_t title_size=0.05;
Float_t title_offset=0.8;

TCanvas *c2 = new TCanvas("c2","<N>",650,600);
c2->cd(1);
c2->Range(0,0,25,18);
c2->SetFillColor(0);
label(inpfile);

pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(29);

hnew->SetStats(kFALSE);

hnew->Draw();

hnew->SetTitle("");
hnew->SetXTitle("N_{w}^{PROJ}");
hnew->GetXaxis()->SetLabelSize(label_size);
hnew->GetYaxis()->SetLabelSize(label_size);
hnew->GetXaxis()->SetTitleSize(title_size);
hnew->GetYaxis()->SetTitleSize(title_size);
hnew->GetXaxis()->SetTitleOffset(title_offset);
hnew->GetYaxis()->SetTitleOffset(title_offset);
//hnew->GetYaxis()->SetRangeUser(0.,1.5);
hnew->SetYTitle("<N>    ");
hnew->SetLineColor(4);
hnew->SetLineStyle(2);

c2->SaveAs("mean_mult.eps");

TH1D *h2 = ((TH1D*)f->Get("nwei2")); 

Int_t imap=(h2->GetNbinsX());

for (Int_t i=1;i<=imap;i++) {
Float_t vp =(h2->GetBinContent(i));

if (vp>0){
vp=k*vp;
vp=(1.-q)+q*vp;
h2->SetBinContent(i,vp);
}else{
h2->SetBinContent(i,0.0);
}
} 

TH1D *h2new = (TH1D*)h2 -> Rebin(reb,"h2new");
h2new -> Scale(1./reb);

ofstream *out = new ofstream;
out->open("mult_fluct.txt");

for (Int_t i=1;i<=(Int_t)imap/reb;i++){
Float_t varn=h2new->GetBinContent(i);
Float_t krot=hnew->GetBinContent(i);;
Float_t sig2=varn*krot;
//if (sig2>0){
//Float_t sig=sqrt(sig2);
//}else{
//sig=0.0;
//}
//*out <<i*reb<<"\t"<<varn<<"\t"<<sig/krot<<endl;
 
}
h2new->SetStats(kFALSE);

TCanvas *c4 = new TCanvas("c4","var(N)/<N>",650,600);
 c4->cd(1);
 c4->Range(0,0,25,18);
 c4->SetFillColor(0);
 label(inpfile);

pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(29);

h2new->Draw();

h2new->SetTitle("");
h2new->SetXTitle("N_{w}^{PROJ}");
h2new->GetXaxis()->SetLabelSize(label_size);
h2new->GetYaxis()->SetLabelSize(label_size);
h2new->GetXaxis()->SetTitleSize(title_size);
h2new->GetYaxis()->SetTitleSize(title_size);
h2new->GetXaxis()->SetTitleOffset(title_offset);
h2new->GetYaxis()->SetTitleOffset(title_offset);
//h2new->GetYaxis()->SetRangeUser(0,0.8);
h2new->SetYTitle("var(N)/<N>    ");
h2new->SetLineColor(4);
h2new->SetLineStyle(2);

c4->SaveAs("var_mult.eps");

}
