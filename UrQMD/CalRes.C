#define CalRes_cxx
#include "CalRes.h"
#include "function.C"
#include "TH1.h"
#include "TH1I.h"
#include "TH2.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TVector3.h"
#include "TVectorD.h"
#include "TRandom3.h"

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//List of histograms and Ntuples....

// static const int neta = 7;
// static const int ndet = 3;
// static const int ncent = 6;
// static const int nth = 3;
// static const int npid = 4;

static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.8,2.3,2.8};

static const int ncent = 8; // 0-80%
static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

static const double maxpt = 2.8; // max pt
static const double minpt = 0.2; // min pt

static const int neta = 2; // [eta-,eta+]

static const int max_nh = 1633;

TFile *d_outfile; // out file with histograms and profiles
TProfile *HRes;		// resolution



void CalRes::Booking(TString outFile){
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << outFile.Data() << " has been initialized" << endl;
  HRes = new TProfile("HRes","EP resolution", ncent,0.,ncent);
  HRes->Sumw2();
  cout << "Histograms have been initialized" << endl;

}

void CalRes::Loop_a_file(TString file){
  TFile *treefile = TFile::Open(file.Data());
  TTree *tree = (TTree *)treefile->Get("mctree");
  if (tree == 0)
  {
    cout << "mctree is not found in " << file << endl;
    treefile->Close();
    return;
  }
  cout << file << " is opened" << endl;
  Init(tree);
  Loop();
  treefile->Close();
  cout << file << " file processed" << endl;
}

void CalRes::Ana_end(){
  d_outfile -> cd();
  d_outfile -> Write();
  d_outfile -> Close();
  cout << "Histfile has been written" << endl;
}

void CalRes::Loop()
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

void CalRes::Ana_event(){
  float rp = 0;
  // rp = gRandom->Uniform(0, 2.*TMath::Pi());
  int fcent=CentB(bimp);
  if (fcent<0) return;
  Double_t sumQxy[neta][2]={{0}};  // [eta-,eta+][x,y]
  Double_t multQv[neta]={0};       // [eta+,eta-]

  for(int i=0;i<nh;i++) { // track loop
    float pt  = sqrt( TMath::Power(momx[i], 2.0 ) + TMath::Power(momy[i], 2.0 ) );
    float the = TMath::ATan2( pt, momz[i] );//atan2(pt/pz)
    float eta = -TMath::Log( TMath::Tan( 0.5 * the ) );
    if (pt < minpt || pt > maxpt || eta>2.5 || eta<-2.5) continue; // track selection
    float phi = TMath::ATan2( momy[i], momx[i] );
    if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

    float phil = phi+rp;
    while (phil>2.*TMath::Pi()) phil-=2.*TMath::Pi(); /* To make sure that phil is between 0 and 2 Pi */

    // Sub eta event method, TPC plane
    int fEta = -1;
    if (eta >-2.5 && eta <-0.1) fEta = 0; // TPC East
    if (eta > 0.1 && eta < 2.5) fEta = 1; // TPC West

		if ( fEta>-1 ){
      sumQxy[fEta][0] += pt * cos( (2.0) * phi );
      sumQxy[fEta][1] += pt * sin( (2.0) * phi );
			multQv[fEta]++;
		} // end of eta selection
  } // end of track loop

  // ==================================== Eta Sub-event ==================================== //

  Double_t fEP[2]; // [eta-,eta+]
  Double_t fQv[2];
  for (int ieta=0; ieta<neta; ieta++){
    if( multQv[ieta]>5 ){ // multiplicity > 5
      fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
      fEP[ieta] = TMath::ATan2( sin( 2.0*fEP[ieta] ), cos( 2.0*fEP[ieta] ) ); // what for?
      fEP[ieta] /= 2.0;
      fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0],2.0)+TMath::Power( sumQxy[ieta][1],2.0))/TMath::Sqrt(multQv[ieta]);
    }else{
      fEP[ieta] = -9999;
      fQv[ieta] = -9999;
    }
  }

  // Resolution
  Double_t psi1, psi2, fq1, fq2;
  psi1 = fEP[0];
  psi2 = fEP[1];
  fq1 = fQv[0];
  fq2 = fQv[1];
  if (psi1<-9000 || psi2<-9000) return;
  if (fq1<0 || fq2<0) return;
  Double_t dPsi = 2. *(psi1 - psi2);
  dPsi = TMath::ATan2( sin(dPsi) , cos(dPsi));
  HRes -> Fill(0.5+fcent,cos(dPsi));
}
void loop_test(){
  CalRes *ana = new CalRes();
  ana->Booking("test.root");
  ana->Loop_a_file("./ROOTFile/urqmd_1033721_1.mcpico.root");
  ana -> Ana_end();
  cout << "Histfile written. Congratz!" << endl;   
}