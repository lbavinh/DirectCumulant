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
 
static const double MYPI=3.141592654;

static const float PI = TMath::Pi();
static const float  pTmax=4900.;
static TH1F *hRun;
static TH1F *hRP;
static TH1F *hPt;
static TH1F *hphi1;
static TH1F *hphi;

static TH1F *hbbcz=0;// BBC vertex 
static TH1F *hclock=0;// centrality by clock

static const int npt = 26; // 0.3 - 6.0 GeV/c 
static const double bin_w[26]={0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.6,2.8,3.0,3.2,3.4};
static const float maxpt = 3.4; // max pt
static const float minpt = 0.4; // min pt

static const int ncut = 6;

TH1F *hpt[npt];
TH1F *hv2pt[npt];
TH1F *hv2Ept[npt];
TH1F *hv2Wpt[npt];
TH1F *hv2TEpt[npt];
TH1F *hv2TWpt[npt];

TH1F *hcos2[npt][ncut];
TH1F *hsin2[npt][ncut];
TH1F *hcos4[npt][ncut];
TH1F *hsin4[npt][ncut];

TH1F *hv2x[npt][ncut];
TH1F *hv2y[npt][ncut];

static int MAXANGLE = 600;
static int MAXPT = 50;
static double ACCEPT[50][600];

TH1F *hacc[npt];

TH1F *mv2pt[npt];

TFile *d_outfile;

void hTana::Loop() {}

void hTana::ana_init(char *outfile) {
  TFile *file_in    = new TFile("/phenix/gh/data03/arkadij/sim4/v2hadron/phenix.root","read");
  TH2D  *phenix = (TH2D*) file_in -> Get("hphitof");

  int i_count=0;
  int i_pt=0;
  for (i_pt=0; i_pt < MAXPT; i_pt++) {
    for (i_count=0; i_count < MAXANGLE; i_count++) {
        ACCEPT[i_pt][i_count] = phenix -> GetBinContent(i_pt+1,i_count+1);
        // cout << i_pt << "   "<< i_count<<"   "<< ACCEPT[i_pt][i_count]<<endl;
      }
  }

  //acceptance
  double norma = 0;
  for (i_pt=0; i_pt < MAXPT; i_pt++){
    for (i_count=0; i_count < MAXANGLE; i_count++){
    if (ACCEPT[i_pt][i_count] > norma)  norma = ACCEPT[i_pt][i_count];
    }
  }
  for (i_pt=0; i_pt < MAXPT; i_pt++){
    for (i_count=0; i_count < MAXANGLE; i_count++){
    ACCEPT[i_pt][i_count] /= norma;
    }
  }
  book_hist(outfile);
}

void hTana::v2gen(int nevent,int Mmean,int dmult) {
  cout << "number of events to generate:"<<nevent<<endl;

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
  double pT;
  double phi, phil, phirp;

 /* Monte-Carlo simulation */
  for(int ne=0; ne<nevent; ne++) { /* Loop over events */
    rndm=GR->Rndm();
    mult=int(Mmean+2.*(GR->Rndm()-0.5)*dmult); /* Emitted multiplicity */
    phirp=-9999.0;
    phirp=2.*PI*(GR->Rndm());
    hRP->Fill(phirp);

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

      //cout << pT << "    " << v2pT <<  "   " << v4pT << endl;

      phil=phi+phirp; /* particle angle with respect to the laboratory frame */
      while (phil>2.*PI)
      phil-=2.*PI; /* To make sure that phil is between 0 and 2 Pi */

      if(pT>=0.4&&pT<=3.4){//track selection 
        int ipt = 0;
        for(int i=0; i<npt-1;i++){
          if(pT>=bin_w[i] && pT<bin_w[i+1]) ipt = i;
        }
        hpt[ipt]->Fill(pT);
        hphi->Fill(phil); 
        double cos2a= TMath::Cos(2*phil);
        double sin2a= TMath::Sin(2*phil);
        double cos4a= TMath::Cos(4*phil);
        double sin4a= TMath::Sin(4*phil);
        double v2x= TMath::Cos(2*phil)*TMath::Cos(2*phirp);
        double v2y= TMath::Sin(2*phil)*TMath::Sin(2*phirp);
        double DphiR=2*(phil - phirp); 
        DphiR=0.5*TMath::ATan2(TMath::Sin(DphiR),TMath::Cos(DphiR));
        double v2rxn = TMath::Cos(2*DphiR);
    
        hv2pt[ipt]->Fill(v2rxn);
        hv2x[ipt][0]->Fill(v2x);
        hv2y[ipt][0]->Fill(v2y);

        hcos2[ipt][0]->Fill(cos2a);
        hsin2[ipt][0]->Fill(sin2a);
        hcos4[ipt][0]->Fill(cos4a);
        hsin4[ipt][0]->Fill(sin4a);

        double A=-3*PI/16+PI/2;
        double B=5*PI/16+PI/2;
        double C=11*PI/16+PI/2;
        double D=19*PI/16+PI/2;
        //if( ( (phil >-3*PI/16) && (phil < 5*PI/16) ) || ( (phil > 11*PI/16) && (phil < 19*PI/16) ) ){

        int i_phi = (int) (phil / 6 * (double) MAXANGLE);
        int i_pt = (int)(50.*(pT-0.4)/(3.0))+1;

        //cout << i_pt << "   "<< i_phi<<"   "<< ACCEPT[i_pt][i_phi]<<endl;

        short iacp = 0;
        float eff=ACCEPT[i_pt][i_phi];
        //cout << eff << endl;
        if (  GR -> Rndm() < eff) iacp =1;

        // if( ( (phil > A) && (phil < B) ) || ( (phil > C) && (phil < D ){

        if(iacp==1){
          mv2pt[ipt]->Fill(v2rxn);
          hphi1->Fill(phil);

          hacc[ipt]->Fill(phil);

          hcos2[ipt][1]->Fill(cos2a);
          hsin2[ipt][1]->Fill(sin2a);
          hcos4[ipt][1]->Fill(cos4a);
          hsin4[ipt][1]->Fill(sin4a);

          hv2x[ipt][1]->Fill(v2x);
          hv2y[ipt][1]->Fill(v2y);

          if((phil > A) && (phil < B) ){//West Arm selection

            hv2Wpt[ipt]->Fill(v2rxn);
            hcos2[ipt][2]->Fill(cos2a);
            hsin2[ipt][2]->Fill(sin2a);
            hcos4[ipt][2]->Fill(cos4a);
            hsin4[ipt][2]->Fill(sin4a);
            hv2x[ipt][2]->Fill(v2x);
            hv2y[ipt][2]->Fill(v2y);

          }
          if((phil > C) && (phil < D) ){//East Arm selection 
            hv2Ept[ipt]->Fill(v2rxn);
            hcos2[ipt][3]->Fill(cos2a);
            hsin2[ipt][3]->Fill(sin2a);
            hcos4[ipt][3]->Fill(cos4a);
            hsin4[ipt][3]->Fill(sin4a);
            hv2x[ipt][3]->Fill(v2x);
            hv2y[ipt][3]->Fill(v2y);

            hv2TEpt[ipt]->Fill(v2rxn);

            hcos2[ipt][5]->Fill(cos2a);
            hsin2[ipt][5]->Fill(sin2a);
            hcos4[ipt][5]->Fill(cos4a);
            hsin4[ipt][5]->Fill(sin4a);

            hv2x[ipt][5]->Fill(v2x);
            hv2y[ipt][5]->Fill(v2y);
          }
	        if((phil > 1.2) && (phil < 2.4) ){
            hv2TWpt[ipt]->Fill(v2rxn);  
            hcos2[ipt][4]->Fill(cos2a);
            hsin2[ipt][4]->Fill(sin2a);
            hcos4[ipt][4]->Fill(cos4a);
            hsin4[ipt][4]->Fill(sin4a);
            hv2x[ipt][4]->Fill(v2x);
            hv2y[ipt][4]->Fill(v2y);
          }
          if((phil > 4.4) && (phil < 5.2) ){ }
        }
      }// end of track selection 
    }//end of the particle loop
  }// end of event loop
}

void hTana::ana_end() {
  d_outfile->cd();

  for(int fpt=0; fpt<npt-1; fpt++){

    hpt[fpt]->Write(); 
    hv2pt[fpt]->Write(); 
    hv2Ept[fpt]->Write(); 
    mv2pt[fpt]->Write(); 
    hv2Wpt[fpt]->Write(); 
    hv2TWpt[fpt]->Write(); 
    hv2TEpt[fpt]->Write(); 
    hacc[fpt]->Write(); 

    for(int nc=0; nc<ncut; nc++){
      hcos2[fpt][nc]->Write();
      hsin2[fpt][nc]->Write();
      hcos4[fpt][nc]->Write();
      hsin4[fpt][nc]->Write();
      hv2x[fpt][nc]->Write();
      hv2y[fpt][nc]->Write();
    }
  }
  //htree->Write();

  hRP->Write();
  hRun->Write();   
  hbbcz->Write();
  hclock->Write();
  hPt->Write();
  hphi1->Write();
  hphi->Write();

  d_outfile->Close();
}

void hTana::book_hist(char *outfile) {
  d_outfile = new TFile(outfile,"recreate");

  char name[800];
  char title[800];

  for(int kpt=0; kpt<npt-1; kpt++){
    sprintf(name,"hpt_%d",kpt);
    sprintf(title,"P_{T} distr for pions, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hpt[kpt]=new TH1F(name,title,300,0.1,9.2);

    sprintf(name,"hv2pt_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for pions, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2pt[kpt]=new TH1F(name,title,400,-1,1);


    sprintf(name,"hv2Ept_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for hadrons East Arm, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2Ept[kpt]=new TH1F(name,title,400,-1,1);

    sprintf(name,"hv2Wpt_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for hadrons West Arm, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2Wpt[kpt]=new TH1F(name,title,400,-1,1);




    sprintf(name,"mv2pt_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for pions, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    mv2pt[kpt]=new TH1F(name,title,400,-1,1);


    sprintf(name,"hv2TEpt_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for hadrons East Arm, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2TEpt[kpt]=new TH1F(name,title,400,-1,1);

    sprintf(name,"hv2TWpt_%d",kpt);
    sprintf(title,"v_{2}(P_{T})  for hadrons West Arm, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2TWpt[kpt]=new TH1F(name,title,400,-1,1);

    sprintf(name,"hacc_%d",kpt);
    sprintf(title,"Acc for hadrons  for hadrons , %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hacc[kpt]=new TH1F(name,title,700,0,7);

    for(int lc=0; lc<ncut; lc++){
      sprintf(name,"hcos2_%d_%d",kpt,lc);
      sprintf(title,"<cos[2phi0]>  for hadrons, %2.1f<pt<%2.1f GeV/c, cut: %d",bin_w[kpt],bin_w[kpt+1],lc);
      hcos2[kpt][lc]=new TH1F(name,title,400,-1,1);

      sprintf(name,"hsin2_%d_%d",kpt,lc);
      sprintf(title,"<sin[2phi0]>  for hadrons, %2.1f<pt<%2.1f GeV/c, cut: %d",bin_w[kpt],bin_w[kpt+1],lc);
      hsin2[kpt][lc]=new TH1F(name,title,400,-1,1);


      sprintf(name,"hcos4_%d_%d",kpt,lc);
      sprintf(title,"<cos[4phi0]>  for hadrons, %2.1f<pt<%2.1f GeV/c, cut: %d",bin_w[kpt],bin_w[kpt+1],lc);
      hcos4[kpt][lc]=new TH1F(name,title,400,-1,1);

      sprintf(name,"hsin4_%d_%d",kpt,lc);
      sprintf(title,"<sin[4phi0]>  for hadrons, %2.1f<pt<%2.1f GeV/c, cut: %d",bin_w[kpt],bin_w[kpt+1],lc);
      hsin4[kpt][lc]=new TH1F(name,title,400,-1,1);


      sprintf(name,"hv2x_%d_%d",kpt,lc);
      sprintf(title,"<cos[2phi0]>  for hadrons, %2.1f<pt<%2.1f GeV/c, cut: %d",bin_w[kpt],bin_w[kpt+1],lc);
      hv2x[kpt][lc]=new TH1F(name,title,400,-1,1);

      sprintf(name,"hv2y_%d_%d",kpt,lc);
      sprintf(title,"<sin[2phi0]>  for hadrons, %2.1f<pt<%2.1f GeV/c, cut: %d",bin_w[kpt],bin_w[kpt+1],lc);
      hv2y[kpt][lc]=new TH1F(name,title,400,-1,1);
    }
  }
  hphi  = new TH1F("hphi","PHENIX Azimuthal angle acceptance",600,0,7);
  hphi1  = new TH1F("hphi1","PHENIX Azimuthal angle acceptance [run4, stat]",600,0,7);
  hPt  = new TH1F("hPt","Pt-distribution",500,0.0,6);
  hRP  = new TH1F("hRP","Event Plane",300,0,7);

  hRun= new TH1F("hRun"," Run number  ",2000,228000,242000);
  hbbcz  = new TH1F("hbbcz","bbc vertex",100,-50,50);
  hclock  = new TH1F("hclock","Centrality by clock",100,0,100);
}


