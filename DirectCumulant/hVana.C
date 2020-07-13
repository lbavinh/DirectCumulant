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
#include <fstream>
using namespace std;

static const int npt = 24; // 0.2 - 3.5 GeV/c 
static const double bin_pT[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
                                1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,
                                2.6,2.8,3.0,3.2,3.5};
static const float maxpt = 3.5; // max pt
static const float minpt = 0.2; // min pt

static const float maxptRFP = 1.0; // max pt of RFP
static const float minptRFP = 0.2; // min pt of RFP

static const float maxptPOI = 3.5; // max pt of RFP
static const float minptPOI = 1.0; // min pt of RFP

TFile *d_outfile;      // out file with histograms and profiles

TH1F *hRP; // reaction plane distribution
TH1F *hPt; // transverse momentum distribution
TH1F *hPhi; // distribution of particle azimuthal angle with respect to RP 
TH1F *hPhil; // distribution of particle azimuthal angle in the laboratory coordinate system


TH1F *hpt[npt];
TH1F *hv2pt[npt];      // dif. v2 distribution in each pT bin from MC toy
TH1F *hv2;             // integrated v2 distribution from toy Monte-Carlo for comparision with integrated v2{2} and v2{4}

TProfile *hv22pt[npt]; // profile <<2'>> from 2nd Q-Cumulants
TProfile *hv24pt[npt]; // profile <<4'>> from 4th Q-Cumulants

TProfile *hv2MC;       // profile for MC integrated v2
TProfile *hv22;        // profile <<2>> from 2nd Q-Cumulants
TProfile *hv24;        // profile <<4>> from 4th Q-Cumulants

// TProfile for covariance calculation according to (C.12)
// Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider. 
// Appendix C
TProfile *hcov24;      // <2>*<4>
TProfile *hcov22prime[npt]; // <2>*<2'>
TProfile *hcov24prime[npt]; // <2>*<4'>
TProfile *hcov42prime[npt]; // <2>*<4'>
TProfile *hcov44prime[npt]; // <4>*<4'>
TProfile *hcov2prime4prime[npt]; // <2'>*<4'>
void hVana::Booking(TString outFile){
   char name[800];
   char title[800];
   d_outfile = new TFile(outFile.Data(),"recreate");

   hPt  = new TH1F("hPt","p_{T}-distribution;GeV/c;dN/dp_{T}",500,0.0,6);
   hRP  = new TH1F("hRP","Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}",300,0,7);
   hPhi = new TH1F("hPhi","Particle azimuthal angle distribution with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})",300,0.,7.);
   hPhil = new TH1F("hPhil","Azimuthal angle distribution in laboratory coordinate system; #phi; dN/d#phi",300,0.,7.);

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

      sprintf(name,"hcov22prime_%d",kpt);
      sprintf(title,"<2>#upoint<2'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov22prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov22prime[kpt]->Sumw2();

      sprintf(name,"hcov24prime_%d",kpt);
      sprintf(title,"<2>#upoint<4'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov24prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov24prime[kpt]->Sumw2();

      sprintf(name,"hcov42prime_%d",kpt);
      sprintf(title,"<4>#upoint<2'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov42prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov42prime[kpt]->Sumw2();

      sprintf(name,"hcov44prime_%d",kpt);
      sprintf(title,"<4>#upoint<4'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov44prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov44prime[kpt]->Sumw2();

      sprintf(name,"hcov2prime4prime_%d",kpt);
      sprintf(title,"<4'>#upoint<2'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov2prime4prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov2prime4prime[kpt]->Sumw2();
   }
   hv22 = new TProfile("hv22","Reference flow from 2nd QC",1,0.,1.);
   hv22->Sumw2();
   hv24 = new TProfile("hv24","Reference flow from 4th QC",1,0.,1.);
   hv24->Sumw2();
   hv2MC = new TProfile("hv2MC","Reference flow from MC",1,0.,1.);
   hv2MC->Sumw2();
   hcov24 = new TProfile("hcov24","<2>#upoint<4> distribution",1,0.,1.);
   hcov24->Sumw2();
   cout << "Histograms have been initialized" << endl;
}

void hVana::Loop_a_file(TString file){
   TFile *treefile = TFile::Open(file.Data());
   TH1F *hRPtemp   = (TH1F*)treefile->Get("hRP");
   TH1F *hPttemp   = (TH1F*)treefile->Get("hPt");
   TH1F *hPhitemp  = (TH1F*)treefile->Get("hPhi");
   TH1F *hPhiltemp = (TH1F*)treefile->Get("hPhil");
   TTree *tree = (TTree*)treefile->Get("htree");
   if(tree == 0) {
      cout << "htree is not found in "<< file << endl;
      treefile->Close();
      return;
   }
   cout << file << " is opened" << endl;
   Init(tree);
   Loop();

   hRP   -> Add(hRPtemp);
   hPt   -> Add(hPttemp);
   hPhi  -> Add(hPhitemp);
   hPhil -> Add(hPhiltemp);

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
      if (ientry%100000==0) cout << ientry << endl;
   }
}

void hVana::Ana_event(){
   // notation as (26) in DOI:10.1103/PhysRevC.83.044913

   // Q-vector of RFP
   Double_t Qx2=0, Qy2=0, Qx4=0, Qy4=0;
   TComplex Q2=0.,Q4=0.;
   // p-vector of POI
   Double_t px2[npt]={0.}, py2[npt]={0.};
   TComplex p2[npt]={0.}, p4[npt]={0.}, q2[npt]={0.}, q4[npt]={0.};
   // q-vector of particles marked as POI and RFP, which is used for 
   // autocorrelation substraction
   Double_t qx2[npt]={0.}, qy2[npt]={0.}, qx4[npt]={0.}, qy4[npt]={0.};
   // My RFP selection
   Double_t M = 0.;
   // numbers of POI (mp) and particles marked both POI and RFP (mq) are equal
   // due to my selection
   Double_t mq[npt]={0.},mp[npt]={0.};
   // average reduced single-event 2- and 4-particle correlations
   Double_t redCor22[npt]={0.}, redCor24[npt]={0.};
   // event weights for correlation calculation
   Double_t w2=0.,w4=0.;
   // event weights for reduced correlation calculation
   Double_t wred2[npt]={0.},wred4[npt]={0.};
   
   for(int i=0;i<nh;i++) { // track loop
      Int_t ipt = 0;
      Float_t pT = pt[i];
      for(int j=0; j<npt;j++){
         if(pT>=bin_pT[j] && pT<bin_pT[j+1]) ipt = j;
      }

      Double_t v2rxn = TMath::Cos(2*(phi0[i] - rp));

      // calculate differential v2 from MC toy
      if(pT>=minpt && pT<maxpt){
         hpt[ipt]->Fill(pT);
         hv2pt[ipt]->Fill(v2rxn);
      }

      // calculate integrated v2 from MC toy for RFP
      if(pT>=minptRFP && pT<maxptRFP){
         hv2 -> Fill(v2rxn);
         hv2MC -> Fill(0.5,v2rxn,1);
      }      

      // RFP
      if(pT>=minptRFP && pT<maxptRFP){
         Qx2+=TMath::Cos(2*phi0[i]);
         Qy2+=TMath::Sin(2*phi0[i]);
         Qx4+=TMath::Cos(4*phi0[i]);
         Qy4+=TMath::Sin(4*phi0[i]);
         M++;
      }

      // POI
      if(pT>=minptPOI && pT<maxptPOI){ // we can also use gap in eta, in this case I use pT region division
      px2[ipt]+=TMath::Cos(2*phi0[i]);
      py2[ipt]+=TMath::Sin(2*phi0[i]);
      mp[ipt]++;
      }

      // POI + RFP (mq)
      Bool_t bOverLap = kFALSE; // POI and RFP have overlap zone at bin 
      if (bOverLap){
      qx2[ipt]+=TMath::Cos(2*phi0[i]);
      qy2[ipt]+=TMath::Sin(2*phi0[i]);
      qx4[ipt]+=TMath::Cos(4*phi0[i]);
      qy4[ipt]+=TMath::Sin(4*phi0[i]);
      mq[ipt]++;
      }
   } // end of track loop

   Q2 = TComplex(Qx2, Qy2);
   Q4 = TComplex(Qx4, Qy4);

   w2 = M*(M-1);                                         // w(<2>)
   w4 = M*(M-1)*(M-2)*(M-3);                             // w(<4>)

   Double_t cor22 = CalCor22(Q2, M, w2);     // <2>
   Double_t cor24 = CalCor24(Q2, Q4, M, w4); // <4>

   hv22 -> Fill(0.5,cor22,w2); // <<2>>
   hv24 -> Fill(0.5,cor24,w4); // <<4>>

   hcov24 -> Fill(0.5,cor22*cor24,w2*w4); // <2>*<4>

   for(int ipt=0; ipt<npt;ipt++){
      if (mp[ipt] == 0) continue;
      p2[ipt] = TComplex(px2[ipt], py2[ipt]);
      q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
      q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
      wred2[ipt] = mp[ipt]*M-mq[ipt];                    // w(<2'>)
      wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);    // w(<4'>)
      redCor22[ipt] = CalRedCor22(Q2,p2[ipt],M,mp[ipt],mq[ipt],wred2[ipt]);                     // <2'>
      hv22pt[ipt] -> Fill(0.5,redCor22[ipt],wred2[ipt]);                                        // <<2'>>
      redCor24[ipt] = CalRedCor24(Q2,Q4,p2[ipt],q2[ipt],q4[ipt],M,mp[ipt],mq[ipt],wred4[ipt]);  // <4'>
      hv24pt[ipt] -> Fill(0.5,redCor24[ipt],wred4[ipt]);                                        // <<4'>>

      hcov22prime[ipt] -> Fill(0.5,cor22*redCor22[ipt],w2*wred2[ipt]);
      hcov24prime[ipt] -> Fill(0.5,cor22*redCor24[ipt],w2*wred4[ipt]);
      hcov42prime[ipt] -> Fill(0.5,cor24*redCor22[ipt],w4*wred2[ipt]);
      hcov44prime[ipt] -> Fill(0.5,cor24*redCor24[ipt],w4*wred4[ipt]);
      hcov2prime4prime[ipt] -> Fill(0.5,redCor22[ipt]*redCor24[ipt],wred2[ipt]*wred4[ipt]);
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

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   Double_t coor22 = (p2*Q2Star-mq).Re();

   return coor22/wred2;
}

Double_t hVana::CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                            TComplex q4, Double_t M, Double_t mp, Double_t mq, Double_t wred4){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   TComplex Q4Star = TComplex::Conjugate(Q4);
   TComplex q2Star = TComplex::Conjugate(q2);
   Double_t Q2Square = Q2.Rho2();
   TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
                  - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
                  - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
                  + 2.0*mq*M-6.0*mq;
   Double_t coor24 = coorc.Re(); 
   return coor24/wred4;
}

void loop_a_list_of_tree(){
   hVana *ana = new hVana();
   ana->Booking("/mnt/pool/2/lbavinh/DirectCumulant/v2QC_5mil.root");
   
   ifstream ifile("/home/lbavinh/maindir/EventGenerator/OUT/runlist.list");
   char filename[200];
   int nfiles=1;
   while(ifile.getline(filename,200)) {
      cout << nfiles <<" file is processing "<<filename <<endl;
      ana->Loop_a_file(filename);
      nfiles++;
   }
   cout<< "Done. " << nfiles << " files are processed." << endl;
   ana -> Ana_end();
   cout << "Histfile written. Congratz!" << endl;
}