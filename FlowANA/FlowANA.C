#define FlowANA_cxx
#include "FlowANA.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TVector3.h"
#include "TDatabasePDG.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>



using namespace std;
//List of histograms and Ntuples....

static const int neta = 9;
static const int ndet = 5;
static const int ncent = 6;
static const int nth = 3;
static const int npid = 4;


// List of MPD based cuts
static const float MpdPtMin = 0.;
static const float MpdPtMax = 3.;
static const float MpdEtaMin = -1.5;
static const float MpdEtaGap = 0.05;
static const float MpdEtaMax = 1.5;

// List of STAR based cuts (for 7.7 GeV)
static const float StarVtxZ = 70.;
static const float StarPtMin = 0.2;
static const float StarPtMax = 2.5;
static const float StarPtMax1 = 4.0;
static const float StarEtaMin = -1.;
static const float StarEtaMax = 1.;
static const float StarEtaGap = 0.05;
static const float StarProtonPtMin = 0.4;
static const float StarProtonPtMax = 2.0;
static const float StarPionPtMin = 0.2;
static const float StarPionPMax = 1.6;

static const int npt = 10; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_w[npt]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};

static const float maxpt = 3.0; // max pt
static const float minpt = 0.2; // min pt


TH1F *hpt[ncent][npt][npid];
TH1F *hv2[ndet][ncent][npt][npid];
TH1F *hv1[ndet][ncent][npt][npid];
TH1F *hv22[ndet][npt][npid];
TH1F *hv12[ndet][npt][npid];
TProfile *pv2[ndet][ncent][npid];
TProfile *pv22[ndet][npid];
TProfile *pv1[ndet][ncent][npid];
TProfile *pv12[ndet][npid];
TProfile *pv1_y[ndet][ncent][npid];
TProfile *pv12_y[ndet][npid];



TH1F *H_Qw[neta];
TH1F *H_EP[nth][neta];
TH1F *H_Qv[nth][neta];
TH1F *H_QvX[nth][neta];
TH1F *H_QvY[nth][neta];
TH1F *H_Phi[nth][neta];


TH1F *HRes[nth][ndet][ncent];

// for centrality determination
TH1F *href1; // PHENIX BBC
TH1F *href2; // PHENIX RXN
TH1F *href3; // STAR TPC
TH1F *href4; // STAR ntracks>2
TH1F *href5; // STAR ntracks>4


TH1F *hbimp; // impact parameter
TH1F *hbimp2; // impact parameter
TH1F *hbimp3; // impact parameter
TH1F *hbimp4; // impact parameter
TH1F *hbimp5; // impact parameter

TH1F *h2pt;
TH1F *h2eta;
TH1F *h2phi;
TH1F *h2phis;
TH1F *h2phirp;




static const double MYPI=3.141592654;

TFile *d_outfile;


void FlowANA::Loop()
{

   if (fChain == 0) return;

   Int_t nentries = Int_t(fChain->GetEntries());

   Int_t nbytes = 0, nb = 0;
 

   for (Int_t jentry=0; jentry<nentries;jentry++) {

    
      Int_t ientry = LoadTree(jentry); //in case of a TChain, ientry is the entry number in the current file
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(jentry%1000==0) cout << "Event [" << jentry << "/" << nentries << "]" <<endl;// event counter
     
      ana_event(jentry,ientry);
   }
}

void FlowANA::ana_init(const char *outfile) {

book_hist(outfile);
 gRandom->SetSeed( (unsigned int)time(NULL) ); 
}




void FlowANA::loop_a_file(const char *file) {
  TFile *treefile = TFile::Open(file);
  TTree *tree = (TTree*)treefile->Get("mctree"); // put the name of the TTree
  if(tree == 0) {
    cout <<"htree is not found in "<<file<<endl;
    treefile->Close();
    return;
  }
  cout << file <<" is opened"<<endl;
  Init(tree);

  

  Loop();
  treefile->Close();
  cout <<"one file processed"<<endl;
}

void FlowANA::ana_end() {
d_outfile->cd();

for( int ieta=0; ieta<neta; ieta++ ){
		H_Qw[ieta]->Write();
	}


 	for( int ith=0; ith<3; ith++ ){
		for( int ieta=0; ieta<neta; ieta++ ){
			H_EP[ith][ieta]->Write();
			H_Qv[ith][ieta]->Write();
			H_QvX[ith][ieta]->Write();
			H_QvY[ith][ieta]->Write();
			H_Phi[ith][ieta]->Write();
		}
	}


	for( int ith=0; ith<3; ith++ ){
		for( int idet=0; idet<ndet; idet++ ){
                         for( int icent=0; icent<ncent; icent++ ){
		  
			HRes[ith][idet][icent]->Write();
		    
		}
	}

}
	

for( int icent=0; icent<ncent; icent++ ){

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
			            hpt[icent][ipt][id]->Write();
		    
		         }
	            }

             }


for( int idet=0; idet<ndet; idet++ ){
               for( int icent=0; icent<ncent; icent++ ){

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
			            hv2[idet][icent][ipt][id]->Write();
			            hv1[idet][icent][ipt][id]->Write();
		    
		         }
	            }

             }

}

for( int idet=0; idet<ndet; idet++ ){
  for( int icent=0; icent<ncent; icent++ ){
	  for( int id=0; id<npid; id++ ){
      pv2[idet][icent][id]->Write();
      pv1[idet][icent][id]->Write();
      pv1_y[idet][icent][id]->Write();
    }
  }
}
for( int idet=0; idet<ndet; idet++ ){
  for( int id=0; id<npid; id++ ){
    pv22[idet][id]->Write();
    pv12[idet][id]->Write();
    pv12_y[idet][id]->Write();
  }
}

for( int idet=0; idet<ndet; idet++ ){
               

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
			            hv22[idet][ipt][id]->Write();
			            hv12[idet][ipt][id]->Write();
		    
		         
	            }

             }

}


	
h2pt->Write();
h2eta->Write();
h2phis->Write();
h2phi->Write();
h2phirp->Write();

 
href1->Write();
href2->Write();
href3->Write();
href4->Write();
href5->Write();


 
hbimp->Write();
hbimp2->Write();
hbimp3->Write(); 
hbimp4->Write();
hbimp5->Write(); 

 d_outfile->Close();



} // end of ana_end

void FlowANA::book_hist(const char *outfile) {
  d_outfile = new TFile(outfile,"recreate");



h2eta  = new TH1F("h2eta","eta distribution",200,-7,7);
h2pt  = new TH1F("h2pt","pt distribution",200,0,10.0);


 
href1  = new TH1F("href1","Centrality by BBC (PHENIX)",1000,0,1000);
href2  = new TH1F("href2","Centrality by BBC (PHENIX)",1000,0,1000);
href3  = new TH1F("href3","Centrality by TPC (STAR)",1000,0,1000);
href4  = new TH1F("href4","Centrality by TPC (STAR), ntracks >1",1000,0,1000);
href5  = new TH1F("href5","Centrality by TPC (STAR), ntracks >2",1000,0,1000);

hbimp2  = new TH1F("hbimp2","Imact Parameter",180,0,18);
hbimp3  = new TH1F("hbimp3","Imact Parameter",180,0,18);
hbimp4  = new TH1F("hbimp4","Imact Parameter",180,0,18);
hbimp5  = new TH1F("hbimp5","Imact Parameter",180,0,18);

 
hbimp  = new TH1F("hbimp","Imact Parameter",180,0,18);

h2phi = new TH1F("h2phi","azim. angle", 100, -TMath::Pi(), TMath::Pi()+2.*TMath::Pi()/100 );
h2phis = new TH1F("h2phis","azim. angle (|eta| <0.5)", 100, -TMath::Pi(), TMath::Pi()+2.*TMath::Pi()/100 );
h2phirp = new TH1F("h2phirp","azim. angle", 100, -TMath::Pi(), TMath::Pi()+2.*TMath::Pi()/100 );


for( int ieta=0; ieta<neta; ieta++ ) H_Qw[ieta] = new TH1F( Form("H_Qw_%d",ieta), Form("H_Qw_%d",ieta), 100, 0, 1000 );
  

for( int ith=0; ith<3; ith++ ){
     for( int ieta=0; ieta<neta; ieta++ ){
  H_EP[ith][ieta] = new TH1F( Form("H_EP_%d_%d",ith,ieta), Form("H_EP_%d_%d",ith,ieta), 372, -TMath::Pi()/(ith+1.)-0.1, TMath::Pi()/(ith+1.)+0.10 );
  H_Phi[ith][ieta] = new TH1F( Form("H_Phi_%d_%d",ith,ieta), Form("H_Phi_%d_%d",ith,ieta), 372, -TMath::Pi()/(ith+1.)-0.1, TMath::Pi()/(ith+1.)+0.10 );
 H_Qv[ith][ieta] = new TH1F( Form("H_Qv_%d_%d",ith,ieta), Form("H_Qv_%d_%d",ith,ieta), 100, 0, 10 );
 H_QvX[ith][ieta] = new TH1F( Form("H_QvX_%d_%d",ith,ieta), Form("H_QvX_%d_%d",ith,ieta), 200, -10, 10 );
 H_QvY[ith][ieta] = new TH1F( Form("H_QvY_%d_%d",ith,ieta), Form("H_QvY_%d_%d",ith,ieta), 200, -10, 10 );
		}
	}



	for( int ith=0; ith<3; ith++ ){
		for( int idet=0; idet<ndet; idet++ ){
                         for( int icent=0; icent<ncent; icent++ ){
   HRes[ith][idet][icent] = new TH1F( Form("HRes_%d_%d_%d",ith,idet,icent), Form("HRes_%d_%d_%d",ith,idet,icent), 100, -10, 10 );	       
		    
		}
	}

}


for( int idet=0; idet<ndet; idet++ ){
               for( int icent=0; icent<ncent; icent++ ){

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
hv2[idet][icent][ipt][id] = new TH1F( Form("hv2_%d_%d_%d_%d",idet,icent,ipt,id), Form("hv2_%d_%d_%d_%d",idet,icent,ipt,id), 400, -10, 10 );			    
hv1[idet][icent][ipt][id] = new TH1F( Form("hv1_%d_%d_%d_%d",idet,icent,ipt,id), Form("hv1_%d_%d_%d_%d",idet,icent,ipt,id), 400, -10, 10 );			    
		    
		         }
	            }

             }

}

for( int idet=0; idet<ndet; idet++ ){
               for( int icent=0; icent<ncent; icent++ ){

			     for( int id=0; id<npid; id++ ){
		  
pv2[idet][icent][id] = new TProfile( Form("pv2_%d_%d_%d",idet,icent,id), Form("pv2_%d_%d_%d",idet,icent,id), 50, 0., 5. );			    
pv1[idet][icent][id] = new TProfile( Form("pv1_%d_%d_%d",idet,icent,id), Form("pv1_%d_%d_%d",idet,icent,id), 50, 0., 5. );			    
pv1_y[idet][icent][id] = new TProfile( Form("pv1_y_%d_%d_%d",idet,icent,id), Form("pv1_y_%d_%d_%d",idet,icent,id), 100, -5., 5. );			    
		    
	            }

             }

}


for( int idet=0; idet<ndet; idet++ ){
             

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
hv22[idet][ipt][id] = new TH1F( Form("hv22_%d_%d_%d",idet,ipt,id), Form("hv22_%d_%d_%d",idet,ipt,id), 400, -10, 10 );			    
hv12[idet][ipt][id] = new TH1F( Form("hv12_%d_%d_%d",idet,ipt,id), Form("hv12_%d_%d_%d",idet,ipt,id), 400, -10, 10 );			    
		    
		       
	            }

             }

}

for( int idet=0; idet<ndet; idet++ ){
			     for( int id=0; id<npid; id++ ){
		  
pv22[idet][id] = new TProfile( Form("pv22_%d_%d",idet,id), Form("pv22_%d_%d",idet,id), 50, 0., 5. );			    
pv12[idet][id] = new TProfile( Form("pv12_%d_%d",idet,id), Form("pv12_%d_%d",idet,id), 50, 0., 5. );			    
pv12_y[idet][id] = new TProfile( Form("pv12_y_%d_%d",idet,id), Form("pv12_y_%d_%d",idet,id), 100, -5., 5. );			    

             }
}


               for( int icent=0; icent<ncent; icent++ ){

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
hpt[icent][ipt][id] = new TH1F( Form("hpt_%d_%d_%d",icent,ipt,id), Form("hpt_%d_%d_%d",icent,ipt,id), 400, 0, 10 );			    
		    
		         }
	            }

             }




	

}







// Analysis for each event !!!!  

void FlowANA::ana_event(int jentry, int ientry) { 


  //float phiRP = gRandom->Uniform(0, 2.*TMath::Pi());

  // float phiRP = gRandom->Uniform(-1.0*TMath::Pi(),TMath::Pi());
 //h2phirp->Fill(phiRP);

  // centrality cut and vertex +/- 30 cm cut
  /*

 if(cent>0&&cent<=80){


       if(centrality<=5)        mycent=0;
       else if(centrality<=10)  mycent=1;
       else if(centrality<=15)  mycent=2;
       else if(centrality<=20)  mycent=3;
       else if(centrality<=25)  mycent=4;
       else if(centrality<=30)  mycent=5;
       else if(centrality<=35)  mycent=6;
       else if(centrality<=40)  mycent=7;
       else if(centrality<=45)  mycent=8;
       else if(centrality<=50)  mycent=9;
       else if(centrality<=55)  mycent=10;

      else   mycent=11;

  */

 if(ientry%100000==0) cout << ientry <<endl;// event counter



	float sumQxy[3][9][2] = {{{0}}}; //[ith][eta][x,y]
	//float sumQxyFull[3][2] = {{{0}}};
	float multQv[9] = {0}; //[eta]
  float fhcalFullEP_x = 0.;
  float fhcalFullEP_y = 0.;
  float fhcalFullEP_phi = 0.;


 
hbimp->Fill(bimp);

double refMult1 = 0;
double refMult2 = 0;

 

double Nch_L = 0;
double Nch_R = 0;

double Nch_L2 = 0;
double Nch_R2 = 0;
 
  for(int itrk=0;itrk<nh;itrk++) {  //track loop

  float pt  = sqrt( TMath::Power(momx[itrk], 2.0 ) + TMath::Power(momy[itrk], 2.0 ) );
	
	float oldphi = atan2( momy[itrk], momx[itrk] );
	float phi=oldphi;
	
	float the = atan2( pt, momz[itrk] );//atan2(pt/pz)
	float eta = -log( tan( 0.5 * the ) );
 
  float ch;
  if (TDatabasePDG::Instance()->GetParticle(pdg[itrk]))
    ch = 1./3.*TDatabasePDG::Instance()->GetParticle(pdg[itrk])->Charge();
  else ch = -999.;
	//	phi += phiRP;
	// float px = pt * cos(phi);
	//	float py = pt * sin(phi);
	//	pt  = sqrt( TMath::Power(px, 2.0 ) + TMath::Power(py, 2.0 ) );

            h2pt->Fill(pt);
            h2eta->Fill(eta);
            h2phi->Fill(oldphi);
            h2phis->Fill(phi);
	    

        if( pt>0.1 && fabs(eta)<0.5 ) refMult1++;
	      if( pt>0.0 && fabs(eta)<0.5 ) refMult2++;
        if(eta >=  3.1 && eta <=  4.0) Nch_R++;
        if(eta >= -4.0 && eta <= -3.1) Nch_L++;

       
        if( pt<minpt  || pt>maxpt ) continue;
        //if ( pt<MpdPtMin || pt>MpdPtMax ) continue;
        // if ( pt<StarPtMin || pt>StarPtMax ) continue;

        int fEta = -1;

	// TPC plane
	if( eta>MpdEtaMin  && eta<-StarEtaGap ) fEta = 0; // TPC East
	if( eta>StarEtaGap && eta<MpdEtaMax )   fEta = 1; // TPC West
	if( fabs(eta)<0.1 )      fEta = 2; // TPC Mid

      	// RXN plane
       	if( eta>-3.0 && eta<-1.0 )   fEta = 3; // RXN East
       	if( eta>1.0 && eta<3.0 )     fEta = 4; // RXN West

	// BBC plane 
	//if( eta>-5.0 && eta<-3.0 )      fEta = 5; //East
	//if( eta>3.0 && eta<5.0  )     fEta = 6; //West

	// FHCal plane
	if( eta>-5.0 && eta<-2.0 )      fEta = 7; //East
	if( eta>2.0 && eta<5.0  )     fEta = 8; //West
	
	// BBC plane - first harmonic
	// if( eta>-5.0 && eta<-3.0 )      fEta = 7; //East
	// if( eta>3.0 && eta<5.0  )     fEta = 8; //West

	// if( fabs(eta)>1.1 && fabs(eta)<2.9 )     fEta = 7; // RXN combined
        //if( fabs(eta)>3.0 && fabs(eta)<5.0 )     fEta = 8; // BBC combined

  if( fEta>-1. ) H_Phi[0][fEta]->Fill( phi );
	
  if ( fEta < 3 && (ch == 0 || ch == -999.)) continue;

           if( fEta>-1. ){
			for( int ith=0; ith<3; ith++ ){
				if (fEta < 7){
					sumQxy[ith][fEta][0] += pt * cos( (ith+2.0) * phi );
					sumQxy[ith][fEta][1] += pt * sin( (ith+2.0) * phi );
				}else{
          if (fEta == 7){
            sumQxy[ith][fEta][0] += -1. * pt * cos( (ith+1.0) * phi ); // отсиметризировать т.к. v1: нечетная по отношению с y(eta), а v2: четная (интеграл нечетной функции=0 => необходимо отсимметризировать)
            sumQxy[ith][fEta][1] += -1. * pt * sin( (ith+1.0) * phi );
          }
          if (fEta == 8){
            sumQxy[ith][fEta][0] += 1. * pt * cos( (ith+1.0) * phi );
            sumQxy[ith][fEta][1] += 1. * pt * sin( (ith+1.0) * phi );
          }
				}
				// if(fEta == 7 || fEta == 8){
				// 	sumQxyFull[ith][0] += pt * cos( (ith+1.0) * phi );
				// 	sumQxyFull[ith][1] += pt * sin( (ith+1.0) * phi );
				// }
			}
			multQv[fEta]++;
	   } // end of eta selection
   } // end of track loop

      if(Nch_L >= 1 && Nch_R >= 1){
          href1 -> Fill(Nch_L + Nch_R);
      }

      if(Nch_L >= 2 && Nch_R >= 2){
          href2 -> Fill(Nch_L + Nch_R);
	  hbimp2->Fill(bimp);
      }
      if(refMult1>0){
          href3 -> Fill(refMult1);
	  hbimp3->Fill(bimp);
      }
      if(refMult2>0){
          href4 -> Fill(refMult1);
	  hbimp4->Fill(bimp);
      }
      if(refMult1>2){
          href5 -> Fill(refMult1);
	  hbimp5->Fill(bimp);
      }
      float sumLR=Nch_L + Nch_R;
  
      // int fCent   = GetCentrality10_RefMult( refMult1 );// STAR def
      // if( fCent<0 ) cout << fCent << endl;

      // int fCent   =  GetCentrality10_RefMultPHENIX(sumLR);

      int fCent   = GetCentrality10_Bimp(bimp);
      // int fCent   =  GetCentrality10_BimpExp(bimp);
      
  	float fEP[3][9]; //[ith][eta]
	float fQv[3][9]; //[ith][eta]
	float fQvX[3][9]; //[ith][eta]
	float fQvY[3][9]; //[ith][eta]
	for( int ith=0; ith<3; ith++ ){ // flow harmonic loop
	  for( int ieta=0; ieta<9; ieta++ ){ // ep detector gap 
	    if( multQv[ieta]>5 ){ // multiplicity > 5
			if( ieta<7 )
			{
				fEP[ith][ieta] = atan2( sumQxy[ith][ieta][1], sumQxy[ith][ieta][0] ) / ( ith + 2.0 );
				fEP[ith][ieta] = atan2( sin( (ith+2.0)*fEP[ith][ieta] ), cos( (ith+2.0)*fEP[ith][ieta] ) );
				fEP[ith][ieta] /= ( ith + 2.0 );
			}else{
				fEP[ith][ieta] = atan2( sumQxy[ith][ieta][1], sumQxy[ith][ieta][0] ) / ( ith + 1.0 );
				fEP[ith][ieta] = atan2( sin( (ith+1.0)*fEP[ith][ieta] ), cos( (ith+1.0)*fEP[ith][ieta] ) );
				fEP[ith][ieta] /= ( ith + 1.0 );
			}
 fQv[ith][ieta] = sqrt( TMath::Power( sumQxy[ith][ieta][0],2.0)+TMath::Power( sumQxy[ith][ieta][1], 2.0))/sqrt( multQv[ieta]);
 fQvX[ith][ieta] = sumQxy[ith][ieta][0] / sqrt( multQv[ieta]);
 fQvY[ith][ieta] = sumQxy[ith][ieta][1] / sqrt( multQv[ieta]);
 H_Qw[ieta]->Fill( multQv[ieta] );
		}else{
			fEP[ith][ieta] = -9999;
			fQv[ith][ieta] = -9999;
			fQvX[ith][ieta] = -9999;
			fQvY[ith][ieta] = -9999;
	    }// end of mult cut selection
	  } // end of loop on EP detectors
	} // end of flow harmonic loop
  fhcalFullEP_x = sumQxy[0][7][0] + sumQxy[0][8][0];
  fhcalFullEP_y = sumQxy[0][7][1] + sumQxy[0][8][1]; // полный Q-вектор (правый и левый)
  fhcalFullEP_phi = atan2( fhcalFullEP_y, fhcalFullEP_x );

	for( int ith=0; ith<3; ith++ ){ // harmonic loop
	  for( int ieta=0; ieta<9; ieta++ ){// eta EP detector loop
	    if( fEP[ith][ieta]>-9000 ){ // EP reconstructed 
				H_EP[ith][ieta]->Fill( fEP[ith][ieta] );
				H_Qv[ith][ieta]->Fill( fQv[ith][ieta] );
				H_QvX[ith][ieta]->Fill( fQvX[ith][ieta] );
				H_QvY[ith][ieta]->Fill( fQvY[ith][ieta] );
	    } // end of EP reconstructed
	  } // end of eta loop
	} // end of harm loop

	
		// Resolution
	for( int ith=0; ith<3; ith++ ){
		for( int icb=0; icb<4; icb++ ){
			double psi1, psi2, fq1, fq2, HarmStart=2.;
       
	       if ( icb==0 ){ psi1 = fEP[ith][0]; psi2 = fEP[ith][1]; fq1 = fQv[ith][0]; fq2 = fQv[ith][1]; } // TPC.E-TPC.W
	       else if( icb==1 ){ psi1 = fEP[ith][3]; psi2 = fEP[ith][4]; fq1 = fQv[ith][3];  fq2 = fQv[ith][4]; } // RXN.E-RXN.W
	       else if( icb==2 ){ psi1 = fEP[ith][5]; psi2 = fEP[ith][6]; fq1 = fQv[ith][5]; fq2 = fQv[ith][6]; } // BBC.E-BBC.W
	       else { psi1 = fEP[ith][7]; psi2 = fEP[ith][8]; fq1 = fQv[ith][7]; fq2 = fQv[ith][8]; HarmStart=1.; } // FHCal.E-FHCal.W
		       
			if( psi1<-9000 || psi2<-9000 ) continue;
			if( fq1<0 || fq2<0 ) continue;

      double dPsi = ( ith + HarmStart ) * ( psi1 - psi2 );
		  dPsi = atan2( sin(dPsi), cos(dPsi) );
			if(fCent>-1&&fCent<ncent){
			  HRes[ith][icb][fCent]->Fill(cos(dPsi) );
			}
		}
	}



// refmult star
//float res2tpc[6]={0.503463,0.71591,0.749962,0.708934,0.61689,0.475386};
//float res2rxn[6]={0.547883,0.791309,0.824213,0.793991,0.709638,0.561604};
//float res2bbc[6]={0.252904,0.377894,0.401809,0.366931,0.300508,0.223784};

// phenix ala cent

// float res2tpc[6]={0.482228,0.704061,0.749667,0.7259,0.655706,0.541163};
//float res2rxn[6]={ 0.526791,0.780304,0.824815,0.806745,0.746894,0.634004};
//float res2bbc[6]={0.241286,0.375359,0.40532,0.384438,0.326188,0.250811};

//float res2tpc[6]={0.493507,0.716751,0.748541,0.709883,0.623788,0.491104};

//float res2rxn[6]={0.540663,0.793812,0.82354,0.794412,0.714603,0.579696};
//float res2bbc[6]={0.248559,0.383837,0.40206,0.373202,0.299496,0.2273};
//float res2fhcal[6]={0.38477,0.577671,0.601972,0.555919,0.46528,0.339993};

// 11.5 gev
//
// float res2tpc[8] = {0.250293,0.342728,0.341794,0.298791,0.24115,0.193414};
// float res2rxn[8] = {0.213336,0.332103,0.338945,0.300795,0.249002,0.209882};
// float res2bbc[8] = {0,0,0,0,0,0};
// float res2fhcal[8] = {0.191224,0.360089,0.382126,0.334111,0.252005,0.169188};
// float res2fhcalFull[8] = {0.335332,0.558849,0.583473,0.528534,0.423159,0.301339};
// float res1fhcalFull[8] = {0.682628,0.839479,0.852782,0.822161,0.753006,0.6515};

// 7.7 gev
//
// float res2tpc[8] = {0.213044,0.313382,0.317931,0.281622,0.226518,0.186429};
// float res2rxn[8] = {0.174124,0.278866,0.276151,0.232497,0.177124,0.138825};
// float res2bbc[8] = {0,0,0,0,0,0};
// float res2fhcal[8] = {0.227257,0.445739,0.481247,0.434915,0.340458,0.230958};
// float res2fhcalFull[8] = {0.388437,0.649156,0.682502,0.63853,0.53607,0.393719};
// float res1fhcalFull[8] = {0.726749,0.885128,0.899905,0.880192,0.826566,0.730868};


// 4.5 GeV
//
float res2tpc[8] = {0.135633,0.238925,0.23404,0.193519,0.14216,0.107586};
float res2rxn[8] = {0.151828,0.226671,0.196096,0.131148,0.0654044,0.0495813};
float res2bbc[8] = {0,0,0,0,0,0};
float res2fhcal[8] = {0.181347,0.412004,0.48672,0.474508,0.402176,0.296816};
float res2fhcalFull[8] = {0.320239,0.615302,0.687439,0.676348,0.605028,0.482505};
float res1fhcalFull[8] = {0.669109,0.86901,0.902004,0.897258,0.863888,0.793756};  

if(fCent>=0&&fCent<ncent){

 
  float phiRP = 0.; // True RP plane angle
  
  for(int itrk=0;itrk<nh;itrk++) {  //track loop

        float pt  = sqrt( TMath::Power(momx[itrk], 2.0 ) + TMath::Power(momy[itrk], 2.0 ) );
        float p  = sqrt( TMath::Power(pt, 2.0 ) + TMath::Power(momz[itrk], 2.0 ) );
	
	float oldphi = atan2( momy[itrk], momx[itrk] );
	float phi=oldphi;
	float dphiRP = atan2( momy[itrk], momx[itrk] ) - phiRP;
  float oldphiV1 = atan2( momy[itrk], momx[itrk] );
  float phiV1 = atan2( sin(oldphiV1), cos(oldphiV1) );
	
	float the = atan2( pt, momz[itrk] );//atan2(pt/pz)
	float eta = -log( tan( 0.5 * the ) );
        float rapidity = 0.5*log( (ene[itrk] + momz[itrk])/(ene[itrk] - momz[itrk]) );

  float ch;
  if (TDatabasePDG::Instance()->GetParticle(pdg[itrk]))
    ch = 1./3.*TDatabasePDG::Instance()->GetParticle(pdg[itrk])->Charge();
  else ch = -999.;
        // phi += phiRP;
	//  float px = pt * cos(phi);
	//	float py = pt * sin(phi);
	//	pt  = sqrt( TMath::Power(px, 2.0 ) + TMath::Power(py, 2.0 ) );

	

        if( pt<minpt  || pt>maxpt ) continue;
        //if ( pt<MpdPtMin || pt>MpdPtMax ) continue;
        //if ( pt<StarPtMin || pt>StarPtMax1 ) continue;
        //if ( eta<MpdEtaMin || eta>MpdEtaMax ) continue;
				if( ch == 0 || ch == -999. ) continue;

	
       int ipt = 0;
 	for(int i=0; i<npt-1;i++){
	if(pt>=bin_w[i] && pt<bin_w[i+1]) ipt = i;
	}// end of ipt loop

        float v2tpc=-999.0;
	float v2rxn=-999.0;
	float v2bbc=-999.0;
	float v2fhcal=-999.0;
	float v2fhcalFull=-999.0;
	float v1fhcalFull=-999.0;
  float v2RP=-999.0;
  float v1RP=-999.0;

	if(eta>StarEtaGap&&eta<MpdEtaMax){
         v2tpc = cos(2.0 * (phi-fEP[0][0]) )/res2tpc[fCent];
         v2rxn = cos(2.0 * (phi-fEP[0][3]) )/res2rxn[fCent];
         v2bbc = cos(2.0 * (phi-fEP[0][5]) )/res2bbc[fCent];
         v2fhcal = cos(2.0 * (phi-fEP[0][7]) )/res2fhcal[fCent];
         v2fhcalFull = cos(2.0 * (phi-fhcalFullEP_phi) )/res2fhcalFull[fCent];
         v2RP = cos(2.0 * (dphiRP) );
         v1fhcalFull = 1.0 * cos(1.0 * (phiV1-fhcalFullEP_phi) )/res1fhcalFull[fCent];
         v1RP = 1.0 * cos(1.0 * (dphiRP) );
         
	}

        if(eta<-1.*StarEtaGap&&eta>MpdEtaMin){
         v2tpc = cos(2.0 * (phi-fEP[0][1]) )/res2tpc[fCent];
         v2rxn = cos(2.0 * (phi-fEP[0][4]) )/res2rxn[fCent];
         v2bbc = cos(2.0 * (phi-fEP[0][6]) )/res2bbc[fCent];
         v2fhcal = cos(2.0 * (phi-fEP[0][8]) )/res2fhcal[fCent];
         v2fhcalFull = cos(2.0 * (phi-fhcalFullEP_phi) )/res2fhcalFull[fCent];
         v2RP = cos(2.0 * (dphiRP) );
         v1fhcalFull = -1.0 * cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent];
         v1RP = -1.0 * cos(1.0 * (dphiRP) );
 
	}

        if(fabs(eta)>StarEtaGap&&fabs(eta)<MpdEtaMax){
	  hv2[0][fCent][ipt][0]->Fill(v2tpc);
          hv2[1][fCent][ipt][0]->Fill(v2rxn);
          hv2[2][fCent][ipt][0]->Fill(v2bbc);
          hv2[3][fCent][ipt][0]->Fill(v2fhcalFull);
          hv2[4][fCent][ipt][0]->Fill(v2RP);
          hv1[3][fCent][ipt][0]->Fill(v1fhcalFull);
          hv1[4][fCent][ipt][0]->Fill(v1RP);
	        if (v2tpc!=-999.)    pv2[0][fCent][0]->Fill(pt,v2tpc);
          if (v2rxn!=-999.)    pv2[1][fCent][0]->Fill(pt,v2rxn);
          if (v2bbc!=-999.)    pv2[2][fCent][0]->Fill(pt,v2bbc);
          //if (v2fhcal!=-999.)  pv2[3][fCent][0]->Fill(pt,v2fhcal);
          if (v2fhcalFull!=-999.)  pv2[3][fCent][0]->Fill(pt,v2fhcalFull);
          if (v2RP!=-999.)     pv2[4][fCent][0]->Fill(pt,v2RP);
          if (v1fhcalFull!=-999.)  pv1[3][fCent][0]->Fill(pt,v1fhcalFull);
          if (v1RP!=-999.)     pv1[4][fCent][0]->Fill(pt,v1RP);
          if (v1fhcalFull!=-999.)  pv1[3][fCent][0]->Fill(pt,v1fhcalFull);
          if (v1RP!=-999.)     pv1[4][fCent][0]->Fill(pt,v1RP);
          //std::cout << "v2TPC " << v2tpc << "; v2RP " << v2RP << std::endl;
          //cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]
	  hpt[fCent][ipt][0]->Fill(pt);

          if(fCent>0&&fCent<4){

          hv22[0][ipt][0]->Fill(v2tpc);
          hv22[1][ipt][0]->Fill(v2rxn);
          hv22[2][ipt][0]->Fill(v2bbc);
          hv22[3][ipt][0]->Fill(v2fhcalFull);
          hv22[4][ipt][0]->Fill(v2RP);
          hv12[3][ipt][0]->Fill(v1fhcalFull);
          hv12[4][ipt][0]->Fill(v1RP);
          if (v2tpc!=-999.)    pv22[0][0]->Fill(pt,v2tpc);
          if (v2rxn!=-999.)    pv22[1][0]->Fill(pt,v2rxn);
          if (v2bbc!=-999.)    pv22[2][0]->Fill(pt,v2bbc);
          //if (v2fhcal!=-999.)  pv22[3][0]->Fill(pt,v2fhcal);
          if (v2fhcalFull!=-999.)  pv22[3][0]->Fill(pt,v2fhcalFull);
          if (v2RP!=-999.)     pv22[4][0]->Fill(pt,v2RP);
          if (v1fhcalFull!=-999.)  pv12[3][0]->Fill(pt,v1fhcalFull);
          if (v1RP!=-999.)     pv12[4][0]->Fill(pt,v1RP);

	  }
	  

	  if ( pdg[itrk]==211 || pdg[itrk]==-211){
              hv2[0][fCent][ipt][1]->Fill(v2tpc);
              hv2[1][fCent][ipt][1]->Fill(v2rxn);
              hv2[2][fCent][ipt][1]->Fill(v2bbc);
			  hv2[3][fCent][ipt][1]->Fill(v2fhcalFull);
			  hv2[4][fCent][ipt][1]->Fill(v2RP);
			  hv1[3][fCent][ipt][1]->Fill(v1fhcalFull);
			  hv1[4][fCent][ipt][1]->Fill(v1RP);
        if (v2tpc!=-999.)    pv2[0][fCent][1]->Fill(pt,v2tpc);
        if (v2rxn!=-999.)    pv2[1][fCent][1]->Fill(pt,v2rxn);
        if (v2bbc!=-999.)    pv2[2][fCent][1]->Fill(pt,v2bbc);
			  //if (v2fhcal!=-999.)  pv2[3][fCent][1]->Fill(pt,v2fhcal);
			  if (v2fhcalFull!=-999.)  pv2[3][fCent][1]->Fill(pt,v2fhcalFull);
			  if (v2RP!=-999.)     pv2[4][fCent][1]->Fill(pt,v2RP);
			  if (v1fhcalFull!=-999.)  pv1[3][fCent][1]->Fill(pt,v1fhcalFull);
			  if (v1RP!=-999.)     pv1[4][fCent][1]->Fill(pt,v1RP);
	      hpt[fCent][ipt][1]->Fill(pt);


          if(fCent>0&&fCent<4){

          hv22[0][ipt][1]->Fill(v2tpc);
          hv22[1][ipt][1]->Fill(v2rxn);
          hv22[2][ipt][1]->Fill(v2bbc);
          hv22[3][ipt][1]->Fill(v2fhcalFull);
          hv22[4][ipt][1]->Fill(v2RP);
          hv12[3][ipt][1]->Fill(v1fhcalFull);
          hv12[4][ipt][1]->Fill(v1RP);
          if (v2tpc!=-999.)    pv22[0][1]->Fill(pt,v2tpc);
          if (v2rxn!=-999.)    pv22[1][1]->Fill(pt,v2rxn);
          if (v2bbc!=-999.)    pv22[2][1]->Fill(pt,v2bbc);
          //if (v2fhcal!=-999.)  pv22[3][1]->Fill(pt,v2fhcal);
          if (v2fhcalFull!=-999.)  pv22[3][1]->Fill(pt,v2fhcalFull);
          if (v2RP!=-999.)     pv22[4][1]->Fill(pt,v2RP);
          if (v1fhcalFull!=-999.)  pv12[3][1]->Fill(pt,v1fhcalFull);
          if (v1RP!=-999.)     pv12[4][1]->Fill(pt,v1RP);

	  }


	      

          }// end of pion selection


	  if ( pdg[itrk]==321){
              hv2[0][fCent][ipt][2]->Fill(v2tpc);
              hv2[1][fCent][ipt][2]->Fill(v2rxn);
              hv2[2][fCent][ipt][2]->Fill(v2bbc);
			  hv2[3][fCent][ipt][2]->Fill(v2fhcalFull);
			  hv2[4][fCent][ipt][2]->Fill(v2RP);
			  hv1[3][fCent][ipt][2]->Fill(v1fhcalFull);
			  hv1[4][fCent][ipt][2]->Fill(v1RP);
        if (v2tpc!=-999.)    pv2[0][fCent][2]->Fill(pt,v2tpc);
        if (v2rxn!=-999.)    pv2[1][fCent][2]->Fill(pt,v2rxn);
        if (v2bbc!=-999.)    pv2[2][fCent][2]->Fill(pt,v2bbc);
			  //if (v2fhcal!=-999.)  pv2[3][fCent][2]->Fill(pt,v2fhcal);
			  if (v2fhcalFull!=-999.)  pv2[3][fCent][2]->Fill(pt,v2fhcalFull);
			  if (v2RP!=-999.)     pv2[4][fCent][2]->Fill(pt,v2RP);
			  if (v1fhcalFull!=-999.)  pv1[3][fCent][2]->Fill(pt,v1fhcalFull);
			  if (v1RP!=-999.)     pv1[4][fCent][2]->Fill(pt,v1RP);
	      hpt[fCent][ipt][2]->Fill(pt);

          if(fCent>0&&fCent<4){

          hv22[0][ipt][2]->Fill(v2tpc);
          hv22[1][ipt][2]->Fill(v2rxn);
          hv22[2][ipt][2]->Fill(v2bbc);
          hv22[3][ipt][2]->Fill(v2fhcalFull);
          hv22[4][ipt][2]->Fill(v2RP);
          hv12[3][ipt][2]->Fill(v1fhcalFull);
          hv12[4][ipt][2]->Fill(v1RP);
          if (v2tpc!=-999.)    pv22[0][2]->Fill(pt,v2tpc);
          if (v2rxn!=-999.)    pv22[1][2]->Fill(pt,v2rxn);
          if (v2bbc!=-999.)    pv22[2][2]->Fill(pt,v2bbc);
          //if (v2fhcal!=-999.)  pv22[3][2]->Fill(pt,v2fhcal);
          if (v2fhcalFull!=-999.)  pv22[3][2]->Fill(pt,v2fhcalFull);
          if (v2RP!=-999.)     pv22[4][2]->Fill(pt,v2RP);
          if (v1fhcalFull!=-999.)  pv12[3][2]->Fill(pt,v1fhcalFull);
          if (v1RP!=-999.)     pv12[4][2]->Fill(pt,v1RP);

	  }
	      

          }// end of kaon selection


	   if ( pdg[itrk]==2212){
              hv2[0][fCent][ipt][3]->Fill(v2tpc);
              hv2[1][fCent][ipt][3]->Fill(v2rxn);
              hv2[2][fCent][ipt][3]->Fill(v2bbc);
			  hv2[3][fCent][ipt][3]->Fill(v2fhcalFull);
        hv2[4][fCent][ipt][3]->Fill(v2RP);
			  hv1[3][fCent][ipt][3]->Fill(v1fhcalFull);
        hv1[4][fCent][ipt][3]->Fill(v1RP);
        if (v2tpc!=-999.)    pv2[0][fCent][3]->Fill(pt,v2tpc);
        if (v2rxn!=-999.)    pv2[1][fCent][3]->Fill(pt,v2rxn);
        if (v2bbc!=-999.)    pv2[2][fCent][3]->Fill(pt,v2bbc);
			  //if (v2fhcal!=-999.)  pv2[3][fCent][3]->Fill(pt,v2fhcal);
			  if (v2fhcalFull!=-999.)  pv2[3][fCent][3]->Fill(pt,v2fhcalFull);
			  if (v2RP!=-999.)     pv2[4][fCent][3]->Fill(pt,v2RP);
			  if (v1fhcalFull!=-999.)  pv1[3][fCent][3]->Fill(pt,v1fhcalFull);
			  if (v1RP!=-999.)     pv1[4][fCent][3]->Fill(pt,v1RP);
	      hpt[fCent][ipt][3]->Fill(pt);

           if(fCent>0&&fCent<4){

          hv22[0][ipt][3]->Fill(v2tpc);
          hv22[1][ipt][3]->Fill(v2rxn);
          hv22[2][ipt][3]->Fill(v2bbc);
          hv22[3][ipt][3]->Fill(v2fhcalFull);
          hv22[4][ipt][3]->Fill(v2RP);
          hv12[3][ipt][3]->Fill(v1fhcalFull);
          hv12[4][ipt][3]->Fill(v1RP);
          if (v2tpc!=-999.)    pv22[0][3]->Fill(pt,v2tpc);
          if (v2rxn!=-999.)    pv22[1][3]->Fill(pt,v2rxn);
          if (v2bbc!=-999.)    pv22[2][3]->Fill(pt,v2bbc);
          //if (v2fhcal!=-999.)  pv22[3][3]->Fill(pt,v2fhcal);
          if (v2fhcalFull!=-999.)  pv22[3][3]->Fill(pt,v2fhcalFull);
          if (v2RP!=-999.)     pv22[4][3]->Fill(pt,v2RP);
          if (v1fhcalFull!=-999.)  pv12[3][3]->Fill(pt,v1fhcalFull);
          if (v1RP!=-999.)     pv12[4][3]->Fill(pt,v1RP);

	  }
	      

          }// end of proton selection

	   
	}

  if(pt>StarPtMin&&pt<StarPtMax){
    pv1_y[3][fCent][0]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
    pv1_y[4][fCent][0]->Fill(rapidity,cos(1.0 * (dphiRP) )); 
    if(fCent>0&&fCent<4){
      pv12_y[3][0]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
      pv12_y[4][0]->Fill(rapidity,cos(1.0 * (dphiRP) ));
    }
    if ( pdg[itrk]==211 && pt > StarPionPtMin & p < StarPionPMax){
      pv1_y[3][fCent][1]->Fill(rapidity,cos(1.0 * (oldphiV1 - fhcalFullEP_phi) )/res1fhcalFull[fCent]);
      pv1_y[4][fCent][1]->Fill(rapidity,cos(1.0 * (dphiRP) )); 
      if(fCent>0&&fCent<4){
        pv12_y[3][1]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
        pv12_y[4][1]->Fill(rapidity,cos(1.0 * (dphiRP) ));
      }
    }
    if ( pdg[itrk]==321){ // && pt > StarPionPtMin & p < StarPionPMax){
      pv1_y[3][fCent][2]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
      pv1_y[4][fCent][2]->Fill(rapidity,cos(1.0 * (dphiRP) )); 
      if(fCent>0&&fCent<4){
        pv12_y[3][2]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
        pv12_y[4][2]->Fill(rapidity,cos(1.0 * (dphiRP) ));
      }
    }
    if ( pdg[itrk]==2212 && pt > StarProtonPtMin && pt < StarProtonPtMax){
      pv1_y[3][fCent][3]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
      pv1_y[4][fCent][3]->Fill(rapidity,cos(1.0 * (dphiRP) )); 
      if(fCent>0&&fCent<4){
        pv12_y[3][3]->Fill(rapidity,cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]);
        pv12_y[4][3]->Fill(rapidity,cos(1.0 * (dphiRP) ));
      }
    }
  }





	


  }// end of the track loop

 }// end of centrality selection 









	
     
 }



// Urqmd 7.7 GeV

int FlowANA::GetCentrality10_RefMult( double refMult ){

	int fcent;
	if     ( refMult>=268 ) fcent = 0; // 0-10% 
	else if( refMult>=185 ) fcent = 1; //10-20% 
	else if( refMult>=126 ) fcent = 2; //20-30% 
	else if( refMult>=83 ) fcent = 3; //30-40% 
	else if( refMult>=52 ) fcent = 4; //40-50% 
	else if( refMult>= 21 ) fcent = 5; //50-60% 
	else if( refMult>= 17 ) fcent = 6; //60-70% 
	else if( refMult>= 9 ) fcent = 7; //70-80% 
	else                    fcent =-1;

	return fcent;
}


int FlowANA::GetCentrality10_RefMultPHENIX( double refMult ){

	int fcent;
	if     ( refMult>=516 ) fcent = 0; // 0-10% 
	else if( refMult>=382 ) fcent = 1; //10-20% 
	else if( refMult>=280 ) fcent = 2; //20-30% 
	else if( refMult>=199 ) fcent = 3; //30-40% 
	else if( refMult>=137 ) fcent = 4; //40-50% 
	else if( refMult>= 90 ) fcent = 5; //50-60% 
	else if( refMult>= 55 ) fcent = 6; //60-70% 
	else if( refMult>= 31 ) fcent = 7; //70-80% 
	else                    fcent =-1;

	return fcent;
}







/*int FlowANA::GetCentrality10_Bimp( float bimp ){

	int fcent;
	if     ( bimp<4.17 ) fcent = 0; // 0-10%
	else if( bimp<6.02 )  fcent = 1; //10-20%
	else if( bimp<7.38 ) fcent = 2; //20-30%
	else if( bimp<8.53 ) fcent = 3; //30-40%
	else if( bimp<9.56)  fcent = 4; //40-50%
	else if( bimp<10.50) fcent = 5; //50-60%
	else if( bimp<11.35) fcent = 6; //60-70%
	else if( bimp<12.19) fcent = 7; //70-80%
	else                fcent =-1;

	return fcent;
}*/

int FlowANA::GetCentrality10_Bimp( float bimp ){

	int fcent;
	if     ( bimp<4.5 ) fcent = 0; // 0-10%
	else if( bimp<6.3 )  fcent = 1; //10-20%
	else if( bimp<7.73 ) fcent = 2; //20-30%
	else if( bimp<8.92 ) fcent = 3; //30-40%
	else if( bimp<9.99)  fcent = 4; //40-50%
	else if( bimp<10.83) fcent = 5; //50-60%
	else if( bimp<11.78) fcent = 6; //60-70%
	else if( bimp<12.61) fcent = 7; //70-80%
	else                fcent =-1;

	return fcent;
}

int FlowANA::GetCentrality10_BimpExp( float bimp ){

	int fcent;
	if     ( bimp<4.68 ) fcent = 0; // 0-10%
	else if( bimp<6.47 ) fcent = 1; //10-20%
	else if( bimp<7.99 ) fcent = 2; //20-30%
	else if( bimp<9.31 ) fcent = 3; //30-40%
	else if( bimp<10.48 ) fcent = 4; //40-50%
	else if( bimp<11.49 ) fcent = 5; //50-60%
	else if( bimp<12.35) fcent = 6; //60-70%
	else if( bimp<13.0) fcent = 7; //70-80%
	else                fcent =-1;

	return fcent;
}

// /nica/mpd21/parfenov/Soft/FlowANA 

