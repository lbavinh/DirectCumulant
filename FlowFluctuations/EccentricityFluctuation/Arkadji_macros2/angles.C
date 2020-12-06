/** \file angles.C
 * Script generating the plot of the correlation between principal axes in the forward and backward rapidities (part of GLISSANDO 2)
 */

#include "label.C"

//! produces plots of the correlation between principal axes in the forward and backward rapidities
/*! Produce plots of the correlation between principal axes in the forward and backward rapidities. */
void angles(
 char *p //!< name of the ROOT input file
            ) {

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  

TFile *f = new TFile(inpfile);

TTree *events = (TTree*)f->Get("events");
Float_t phi2_plus,phi2_minus;
events->SetBranchAddress("phi2_plus",&phi2_plus);
events->SetBranchAddress("phi2_minus",&phi2_minus);

TH2D * angles   = new TH2D("angles", "angles", 200,-0.3,0.3,200,-0.3,0.3);

Float_t sx=0, sx2=0, sy=0, sy2=0, sxy=0;
Float_t cx=0, cx2=0, cy=0, cy2=0, cxy=0;


Int_t nentries = (Int_t)events->GetEntries();

for (Int_t i=0;i<nentries;i++){
events->GetEntry(i);
angles -> Fill(phi2_plus,phi2_minus,1);
if((phi2_plus*phi2_plus<10.25*10.25) && (phi2_minus*phi2_minus<10.25*10.25)){
sx+=sin(2*phi2_plus); 
sy+=sin(2*phi2_minus); 
sx2+=sin(2*phi2_plus)*sin(2*phi2_plus); 
sy2+=sin(2*phi2_minus)*sin(2*phi2_minus); 
sxy+=sin(2*phi2_plus)*sin(2*phi2_minus);
cx+=cos(2*phi2_plus); 
cy+=cos(2*phi2_minus); 
cx2+=cos(2*phi2_plus)*cos(2*phi2_plus); 
cy2+=cos(2*phi2_minus)*cos(2*phi2_minus); 
cxy+=cos(2*phi2_plus)*cos(2*phi2_minus);
}; 
}

sx/=nentries;
sy/=nentries;
sx2/=nentries;
sy2/=nentries;
sxy/=nentries; 

cx/=nentries;
cy/=nentries;
cx2/=nentries;
cy2/=nentries;
cxy/=nentries; 

Float_t sigx, sigy;
Float_t cigx, cigy;

sigx=sx2-sx*sx;
sigy=sy2-sy*sy;

cigx=cx2-cx*cx;
cigy=cy2-cy*cy;

//cout << " cumulant:" << sxy+cxy-sx*sy-cx*cy << endl;
//cout << " :" << (sxy+cxy-sx*sy-cx*cy)/(sx*sy+cx*cy) << endl;
//cout << " :" << (sxy+cxy-sx*sy-cx*cy)/sqrt((-sigx+cigx)*(-sigy+cigy)) << endl;

//some problem when comparing to the buily-in statistics
//cout << sx << " " << sy << " " << sx2 << " " << sy2 << endl; 
//cout << (sxy-sx*sy)/sigx/sigy << endl;

TCanvas *c2 = new TCanvas("c2","f-b angle correlation",650,600);
c2->cd(1);
c2->Range(0,0,25,18);
label(inpfile);

pad2 = new TPad("pad2","Pad2",0.02,0.02,0.98,0.78,33);
pad2->Draw();
pad2->cd();
pad2->Range(-0.255174,-19.25,2.29657,-6.75);
gPad->SetFillStyle(4000);
gPad->SetFillColor(0);

angles->Draw("CONT4");

Float_t cov=angles->GetCovariance(1,2);
Float_t varx=angles->GetCovariance(1,1);
Float_t vary=angles->GetCovariance(2,2);

cout << " rho:   " << cov/sqrt(varx*vary) << endl;

c2->SaveAs("angles.eps");

}
