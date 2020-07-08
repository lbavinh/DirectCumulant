#define hVana_cxx
#include "hVana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1F.h"
#include "TString.h"

#include <iostream>
using namespace std;

static const int npt = 24; // 0.2 - 3.5 GeV/c 
static const double bin_pT[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
                                1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,
                                2.6,2.8,3.0,3.2,3.5};
static const float maxpt = 3.5; // max pt
static const float minpt = 0.2; // min pt

static const float maxptRFP = 3.5; // max pt
static const float minptRFP = 0.2; // min pt

TFile *d_outfile;
TH1F *hpt[npt];
TH1F *hv2pt[npt];
TH1F *hv2;
TProfile *hv22pt[npt];
TProfile *hv24pt[npt];
TProfile *hv22;
TProfile *hv24;

void hVana::Booking(TString outFile){
   char name[800];
   char title[800];
   d_outfile = new TFile(outFile.Data(),"recreate");
   hv2 = new TH1F("hv2","v2 distribution;v_{2}",400,-1,1);
   for(int kpt=0; kpt<npt; kpt++){

      sprintf(name,"hpt_%d",kpt);
      sprintf(title,"P_{T} distr, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hpt[kpt]=new TH1F(name,title,300,0.1,9.2);

      sprintf(name,"hv2pt_%d",kpt);
      sprintf(title,"v_{2}(P_{T}) Monte-Carlo Simulation, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hv2pt[kpt]=new TH1F(name,title,400,-1,1);

      sprintf(name,"hv22pt_%d",kpt);
      sprintf(title,"v_{2}(P_{T}) from 2nd order cumulants, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hv22pt[kpt]=new TProfile(name,title,1,0.,1.);
      hv22pt[kpt]->Sumw2();

      sprintf(name,"hv24pt_%d",kpt);
      sprintf(title,"v_{2}(P_{T}) from 4th order cumulants, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hv24pt[kpt]=new TProfile(name,title,1,0.,1.);
      hv24pt[kpt]->Sumw2();
   }
   hv22 = new TProfile("hv22","Reference flow from 2nd QC",1,0.,1.);
   hv22->Sumw2();
   hv24 = new TProfile("hv24","Reference flow from 4th QC",1,0.,1.);
   hv24->Sumw2();
   cout << "Histograms have been initialized" << endl;
}

void hVana::Loop_a_file(TString file){
   TFile *treefile = TFile::Open(file.Data());
   TTree *tree = (TTree*)treefile->Get("htree");
   if(tree == 0) {
      cout << "htree is not found in "<< file << endl;
      treefile->Close();
      return;
   }
   cout << file << " is opened" << endl;
   Init(tree);
   Loop();
   treefile->Close();
   cout << file  <<" file processed"<<endl;
}

void hVana::Ana_end(){
   d_outfile -> cd();
   d_outfile -> Write();
   d_outfile -> Close();
   cout << "Histfile has been written" << endl;
}

void hVana::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      Ana_event();
      if (ientry%1000==0) cout << ientry << endl;
   }
}

void hVana::Ana_event(){
   
   Double_t Qx2=0, Qy2=0, Qx4=0, Qy4=0; // notation as (26) in 
   Double_t px2[npt], py2[npt];
   // Double_t px4[npt]={NULL}, py4[npt]={NULL}; 
   Double_t qx2[npt], qy2[npt], qx4[npt], qy4[npt];
   Double_t M = nh; // выбор RFP - все частицы в событии
   Double_t mq[npt],mp[npt];// DOI:10.1103/PhysRevC.83.044913
   Double_t redCor22[npt], redCor24[npt];
   TComplex Q2,Q4;
   TComplex p2[npt],p4[npt],q2[npt],q4[npt];
   Double_t wred2[npt],wred4[npt];
   Double_t w2,w4;
   for(int i=0;i<nh;i++) { // track loop
      Int_t ipt = 0;
      Float_t pT = pt[i];
      for(int j=0; j<npt;j++){
         if(pT>=bin_pT[j] && pT<bin_pT[j+1]) ipt = j;
      }      
      
      if(pT>=minpt && pT<maxpt){ // track's momentum selection
         hpt[ipt]->Fill(pT);
         Double_t v2rxn = TMath::Cos(2*(phi0[i] - rp));
         hv2pt[ipt]->Fill(v2rxn);
         hv2 -> Fill(v2rxn);
      }//track's momentum selection

      // RFP
      if(pT>=minptRFP && pT<maxptRFP){
         Qx2+=TMath::Cos(2*phi0[i]);
         Qy2+=TMath::Sin(2*phi0[i]);
         Qx4+=TMath::Cos(4*phi0[i]);
         Qy4+=TMath::Sin(4*phi0[i]);
      }
      // POI
      px2[ipt]+=TMath::Cos(2*phi0[i]);
      py2[ipt]+=TMath::Sin(2*phi0[i]);
      // px4[ipt]+=TMath::Cos(4*phi0[i]);
      // py4[ipt]+=TMath::Sin(4*phi0[i]);
      mp[ipt]++;

      // POI + RFP
      qx2[ipt]+=TMath::Cos(2*phi0[i]);
      qy2[ipt]+=TMath::Sin(2*phi0[i]);
      qx4[ipt]+=TMath::Cos(4*phi0[i]);
      qy4[ipt]+=TMath::Sin(4*phi0[i]);
      mq[ipt]++;
   } // end of track loop
   Q2 = TComplex(Qx2, Qy2);
   Q4 = TComplex(Qx4, Qy4);

   w2 = M*(M-1);
   w4 = M*(M-1)*(M-2)*(M-3); 

   Double_t cor22 = CalCor22(Q2, M, w2);
   Double_t cor24 = CalCor24(Q2, Q4, M, w4);

   hv22 -> Fill(0.5,cor22,w2);
   hv24 -> Fill(0.5,cor24,w4);

   for(int ipt=0; ipt<npt;ipt++){
      p2[ipt] = TComplex(px2[ipt], py2[ipt]);
      q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
      q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
      wred2[ipt] = mp[ipt]*M-mq[ipt];
      wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);
      redCor22[ipt] = CalRedCor22(Q2,p2[ipt],M,mp[ipt],mq[ipt],wred2[ipt]);
      hv22pt[ipt] -> Fill(0.5,redCor22[ipt],wred2[ipt]);
      redCor24[ipt] = CalRedCor24(Q2,Q4,p2[ipt],q2[ipt],q4[ipt],M,mp[ipt],mq[ipt],wred4[ipt]);
      hv24pt[ipt] -> Fill(0.5,redCor24[ipt],wred4[ipt]);
   }
}

Double_t hVana::CalCor22(TComplex Q2, Double_t M, Double_t w2){
   // single-event average 2-particle azimuthal correlation <2>

  Double_t Q2Square = Q2.Rho2();
  // Double_t Rho2() const {return fRe*fRe+fIm*fIm;}
  Double_t coor22   = Q2Square - M;                                          
  
  return coor22/w2;
}

Double_t hVana::CalCor24(TComplex Q2, TComplex Q4, Double_t M, Double_t w4){ 
   // single-event average 4-particle azimuthal correlation <4>

   TComplex Q2Star   = TComplex::Conjugate(Q2);
   // static TComplex Conjugate(const TComplex &c) {return TComplex(c.Re(),-c.Im());}
   TComplex Q4Star   = TComplex::Conjugate(Q4);
   
   Double_t Q2Square = Q2.Rho2();
   Double_t Q4Square = Q4.Rho2();
   Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

   Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2*ReQQQ
                        - 4*(M-2)*Q2Square + 2*M*(M-3));

   return coor24/w4;
}

Double_t hVana::CalRedCor22(TComplex Q2, TComplex p2, Double_t M, Double_t mp, 
                     Double_t mq, Double_t wred2){

   TComplex Q2Star = TComplex::Conjugate(Q2);
   Double_t coor22 = (p2*Q2Star).Re()-mq;

   return coor22/wred2;
}

Double_t hVana::CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                     TComplex q4, Double_t M, Double_t mp, Double_t mq, Double_t wred2){
   TComplex Q2Star = TComplex::Conjugate(Q2);
   TComplex Q4Star = TComplex::Conjugate(Q4);
   TComplex q2Star = TComplex::Conjugate(q2);
   Double_t Q2Square = Q2.Rho2();
   TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
                  - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
                  - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
                  + 2.0*mq*M-6.0*mq;
   Double_t coor24 = coorc.Re(); 
   return coor24/wred2;
}