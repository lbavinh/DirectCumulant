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
TH1F *hRP;         // reaction plane distr
TH1F *hPt;         // transverse momentum distr
TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta;        // pseudorapidity
TH1F *hBimp;       // impact parameter
TH1I *hMult;       // emitted multiplicity
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

void CalRes::Booking(TString outFile){
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << outFile.Data() << " has been initialized" << endl;
  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 7.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);
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
  // int fcent=CentB(bimp);
  // if (fcent<0) return;
  hMult -> Fill(nh);
  hRP -> Fill(rp);
  hBimp -> Fill(bimp);
  hBimpvsMult -> Fill(nh,bimp);

  for(int i=0;i<nh;i++) { // track loop
    float pt  = sqrt( TMath::Power(momx[i], 2.0 ) + TMath::Power(momy[i], 2.0 ) );
    float the = TMath::ATan2( pt, momz[i] );//atan2(pt/pz)
    float eta = -TMath::Log( TMath::Tan( 0.5 * the ) );
    // if (pt < minpt || pt > maxpt || eta>2.5 || eta<-2.5) continue; // track selection
    if (abs(eta)<2.5) continue; // spectator
    float phi = TMath::ATan2( momy[i], momx[i] );
    if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */
    float phil = phi+rp;
    hPhi -> Fill(phi);
    while (phil>2.*TMath::Pi()) phil-=2.*TMath::Pi(); /* To make sure that phil is between 0 and 2 Pi */
    hPhil -> Fill(phil);
    hEta -> Fill(eta);

    Int_t ipt = 0;
    hPt -> Fill(pt);
    for(int j=0; j<npt;j++){
      if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
    }


  } // end of track loop

}
void loop_test(){
  CalRes *ana = new CalRes();
  ana->Booking("test.root");
  ana->Loop_a_file("urqmd_1033721.mcpico.root");
  ana -> Ana_end();
  cout << "Histfile written. Congratz!" << endl;   
}