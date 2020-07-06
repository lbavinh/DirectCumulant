#define hTana_cxx
#include "hTana.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <TRandom2.h>
#include "TRandom3.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TH2F.h>
#include <sys/time.h>
#include "function.C"
using namespace std;
//List of histograms and Ntuples....

static const float PI = TMath::Pi();
static const float pTmax=4900.;

static TH1F *hRP;
static TH1F *hPt;

// static TH1F *hRun;
// static TH1F *hbbcz=0;// BBC vertex 
// static TH1F *hclock=0;// centrality by clock

static const int npt = 25; // 0.3 - 6.0 GeV/c 
static const double bin_w[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.5};
static const float maxpt = 3.5; // max pt
static const float minpt = 0.2; // min pt

TH1F *hpt[npt];
TH1F *hv2pt[npt];
TH1F *hv4pt[npt];
TH1F *hPhi;
TH1F *hPhil;

static const int max_nh = 800;

float d_rp; // reaction plane azimuthal angle 
int     d_nh; // number of hadrons
float   d_pt[max_nh]; // transverse momentum
float   d_phi0[max_nh]; // particle azimuthal angle in laboratory system 

TTree *htree;
TFile *d_outfile;

void hTana::Loop() {}

void hTana::ana_init(char *outfile) {
  book_hist(outfile);
}

void hTana::v2gen(int nevent,int Mmean,int dmult) {
  cout << "number of events to generate:" << nevent << endl;

  int seed1 = (int) clock();
  int seed2 = (int) clock() * 2;
  cout << "seed1="<<seed1<<"   "<<"seed2="<<seed2<<endl;

  TRandom2 *GR = new TRandom2();
  GR ->SetSeed(seed1);

  int mult=0; 
  double rndm;

  double pTmean=0.;

  double v2pT,v4pT;
  double v2ev, v4ev;  /* Integrated flow values in a given event */
  double v2mean=0., v4mean=0.; /* Mean flow parameters <vnev> */

  double pT; // transverse momentum
  double phi; // azimuthal angle
  double phil; // azimuthal angle in laboratory coordinates
  double phirp; // azimuthal angle of reation plane

  /* Monte-Carlo simulation */
  for(int ne=0; ne<nevent; ne++) { /* Loop over events */
    rndm=GR->Rndm();
    
    mult=int(Mmean+2.*(GR->Rndm()-0.5)*dmult); /* Emitted multiplicity */

    phirp=-9999.0;

    phirp=2.*PI*(GR->Rndm());
    hRP->Fill(phirp);

    d_rp=phirp;

    if(ne%50000==0) cout << ne<<endl;

    int nh = 0;   

    /* Loop over particles */
    for(int nm=0; nm<mult; nm++) {
      momentum:
      pT=pTmax*(GR->Rndm());
      if (GR->Rndm()>dndpT(pT)) goto momentum;

      pT=pT/1000;
      hPt->Fill(pT);
      /* generate transverse momentum according to the distribution, 
         using the hit-or-miss method. */

      v2pT=v2(pT);
      v4pT=v4(pT);

      flow:
      phi=2.*PI*(GR->Rndm()); /* Random pion azimuth phi between 0 and 2Pi */
      if (GR->Rndm()>dndphi(phi,v2pT,v4pT)) goto flow; 
      /* simulate anisotropic flow, with the hit-or-miss method */

      hPhi -> Fill(phi);

      //cout << pT <<"\t"<< v2pT <<"\t"<< v4pT << endl;

      phil=phi+phirp; /* particle angle with respect to the laboratory frame */
      while (phil>2.*PI)
      phil-=2.*PI; /* To make sure that phil is between 0 and 2 Pi */

      hPhil -> Fill(phil);

      if(pT>=0.2&&pT<=3.5){ //track selection 
        int ipt = 0;
        for(int i=0; i<npt-1;i++){
	        if(pT>=bin_w[i] && pT<bin_w[i+1]) ipt = i;
        }
        hpt[ipt]->Fill(pT);

        double DphiR = (phil - phirp); 
        double v2rxn = TMath::Cos(2*DphiR);
        double v4rxn = TMath::Cos(4*DphiR);

        hv2pt[ipt]->Fill(v2rxn);
        hv4pt[ipt]->Fill(v4rxn);

        d_phi0[nh] = phil;
        d_pt[nh]   = pT;

        nh++;
      }// end of track selection
    }//end of the particle loop
    d_nh = nh;   
    htree->Fill();
  }// end of event loop
}

void hTana::ana_end() {
  d_outfile->cd();

  for(int fpt=0; fpt<npt-1; fpt++){
    hpt[fpt]->Write(); 
    hv2pt[fpt]->Write(); 
    hv4pt[fpt]->Write(); 
  }

  htree->Write();

  hRP   -> Write();
  hPt   -> Write();
  hPhi  -> Write();
  hPhil -> Write();

  // hRun->Write();
  // hbbcz->Write();
  // hclock->Write();

  d_outfile->Close();
}

void hTana::book_hist(char *outfile) {
  d_outfile = new TFile(outfile,"recreate");

  htree = new TTree("htree","Hadron EMC + TOF tree");

  htree->Branch("rp",&d_rp,"rp/F");
  htree->Branch("nh",&d_nh,"nh/I");
  htree->Branch("pt",&d_pt,"pt[nh]/F");
  htree->Branch("phi0",&d_phi0,"phi0[nh]/F");

  char name[800];
  char title[800];

  for(int kpt=0; kpt<npt-1; kpt++){
    sprintf(name,"hpt_%d",kpt);
    sprintf(title,"P_{T} distr for pions, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hpt[kpt]=new TH1F(name,title,300,0.1,9.2);

    sprintf(name,"hv2pt_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for pions, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2pt[kpt]=new TH1F(name,title,400,-1,1);

    sprintf(name,"hv4pt_%d",kpt);
    sprintf(title,"v_{4}(P_{T})  for pions, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv4pt[kpt]=new TH1F(name,title,400,-1,1);
  }
  hPt  = new TH1F("hPt","Pt-distribution",500,0.0,6);
  hRP  = new TH1F("hRP","Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}",300,0,7);
  hPhi = new TH1F("hPhi","Particle azimuthal angle distribution with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})",300,0.,7.);
  hPhil = new TH1F("hPhil","Azimuthal angle distribution in laboratory coordinate system; #phi; dN/d#phi",300,0.,7.);

  // hRun= new TH1F("hRun"," Run number  ",2000,228000,242000);
  // hbbcz  = new TH1F("hbbcz","bbc vertex",100,-50,50);
  // hclock  = new TH1F("hclock","Centrality by clock",100,0,100);
}