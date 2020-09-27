#define FlowANA_cxx
#include "FlowANA_test.h"
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
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>



using namespace std;
//List of histograms and Ntuples....

static const int neta = 7;
static const int ndet = 3;
static const int ncent = 6;
static const int nth = 3;
static const int npid = 4;




static const int npt = 11; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_w[11]={0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.8,2.3,2.8,4.0};

static const float maxpt = 4.0; // max pt
static const float minpt = 0.2; // min pt


TH1F *hpt[ncent][npt][npid];
TH1F *hv2[ndet][ncent][npt][npid];
TH1F *hv22[ndet][npt][npid];



TH1F *H_Qw[neta];
TH1F *H_EP[nth][neta];
TH1F *H_Qv[nth][neta];


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
     
      ana_event(jentry,ientry);
   }
}

void FlowANA::ana_init(char *outfile) {

book_hist(outfile);
 gRandom->SetSeed( (unsigned int)time(NULL) ); 
}




void FlowANA::loop_a_file(char *file) {
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
		    
		         }
	            }

             }

}


for( int idet=0; idet<ndet; idet++ ){
               

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
			            hv22[idet][ipt][id]->Write();
		    
		         
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

void FlowANA::book_hist(char *outfile) {
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
  H_EP[ith][ieta] = new TH1F( Form("H_EP_%d_%d",ith,ieta), Form("H_EP_%d_%d",ith,ieta), 100, -TMath::Pi()/(ith+2.)-0.1, TMath::Pi()/(ith+2.)+0.10 );
 H_Qv[ith][ieta] = new TH1F( Form("H_Qv_%d_%d",ith,ieta), Form("H_Qv_%d_%d",ith,ieta), 100, 0, 10 );
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
		    
		         }
	            }

             }

}



for( int idet=0; idet<ndet; idet++ ){
             

			   for( int ipt=0; ipt<npt-1; ipt++ ){

			     for( int id=0; id<npid; id++ ){
		  
hv22[idet][ipt][id] = new TH1F( Form("hv22_%d_%d_%d",idet,ipt,id), Form("hv22_%d_%d_%d",idet,ipt,id), 400, -10, 10 );			    
		    
		       
	            }

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


  float phiRP = gRandom->Uniform(0, 2.*TMath::Pi());

  // float phiRP = gRandom->Uniform(-1.0*TMath::Pi(),TMath::Pi());
 h2phirp->Fill(phiRP);

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

 if(jentry%1000==0) cout << jentry<<endl;// event counter



	float sumQxy[3][7][2] = {{{0}}}; //[ith][eta][x,y]
	float multQv[7] = {0}; //[eta]


 
hbimp->Fill(bimp);

double refMult1 = 0;
double refMult2 = 0;

 

double Nch_L = 0;
double Nch_R = 0;

double Nch_L2 = 0;
double Nch_R2 = 0;
 
  for(int itrk=0;itrk<nh;itrk++) {  //track loop

        float pt  = sqrt( TMath::Power(momx[itrk], 2.0 ) + TMath::Power(momy[itrk], 2.0 ) );
	
	float oldphi = atan2( momx[itrk], momy[itrk] );
	float phi=oldphi;
	
	float the = atan2( pt, momz[itrk] );//atan2(pt/pz)
	float eta = -log( tan( 0.5 * the ) );

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

       
        if( pt<0.15  || pt>2. ) continue;

        int fEta = -1;

	// TPC plane
	if( eta>-1 && eta<-0.1 ) fEta = 0; // TPC East
	if( eta>0.1 && eta<1 )   fEta = 1; // TPC West
	if( fabs(eta)<0.1 )      fEta = 2; // TPC Mid

      	// RXN plane
       	if( eta>-3.0 && eta<-1.0 )   fEta = 3; // RXN East
       	if( eta>1.0 && eta<3.0 )     fEta = 4; // RXN West

	// BBC plane 
	if( eta>-5 && eta<-3 )      fEta = 5; //East
	if( eta>3.0 && eta<5  )     fEta = 6; //West

	// if( fabs(eta)>1.1 && fabs(eta)<2.9 )     fEta = 7; // RXN combined
        //if( fabs(eta)>3.0 && fabs(eta)<5.0 )     fEta = 8; // BBC combined
	


           if( fEta>-1 ){
			for( int ith=0; ith<3; ith++ ){
				sumQxy[ith][fEta][0] += pt * cos( (ith+2.0) * phi );
				sumQxy[ith][fEta][1] += pt * sin( (ith+2.0) * phi );
			}
			multQv[fEta]++;
	   }// end of eta selection
      

   }// end of track loop


  
      
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
      //if( fCent<0 ) cout << fCent << endl;

      // int fCent   =  GetCentrality10_RefMultPHENIX(sumLR);

      int fCent   = GetCentrality10_Bimp(bimp);
      //int fCent   =  GetCentrality10_BimpExp(bimp);
      
  	float fEP[3][7]; //[ith][eta]
	float fQv[3][7]; //[ith][eta]
	for( int ith=0; ith<3; ith++ ){ // flow harmonic loop
	  for( int ieta=0; ieta<7; ieta++ ){ // ep detector gap 
	    if( multQv[ieta]>5 ){ // multiplicity > 5
				fEP[ith][ieta] = atan2( sumQxy[ith][ieta][1], sumQxy[ith][ieta][0] ) / ( ith + 2.0 );
				fEP[ith][ieta] = atan2( sin( (ith+2.0)*fEP[ith][ieta] ), cos( (ith+2.0)*fEP[ith][ieta] ) );
				fEP[ith][ieta] /= ( ith + 2.0 );

 fQv[ith][ieta] = sqrt( TMath::Power( sumQxy[ith][ieta][0],2.0)+TMath::Power( sumQxy[ith][ieta][1], 2.0))/sqrt( multQv[ieta]);
 H_Qw[ieta]->Fill( multQv[ieta] );
			}else{
				fEP[ith][ieta] = -9999;
				fQv[ith][ieta] = -9999;
	    }// end of mult cut selection
	  } // end of loop on EP detectors
	} // end of flow harmonic loop



	for( int ith=0; ith<3; ith++ ){ // harmonic loop
	  for( int ieta=0; ieta<7; ieta++ ){// eta EP detector loop
	    if( fEP[ith][ieta]>-9000 ){ // EP reconstructed 
				H_EP[ith][ieta]->Fill( fEP[ith][ieta] );
				H_Qv[ith][ieta]->Fill( fQv[ith][ieta] );
	    }// end of EP reconstructed
	  }// end of eta loop
	}// end of harm loop

	
		//Resolution
	for( int ith=0; ith<3; ith++ ){
		for( int icb=0; icb<3; icb++ ){
			double psi1, psi2, fq1, fq2;
       
	       if ( icb==0 ){ psi1 = fEP[ith][0]; psi2 = fEP[ith][1]; fq1 = fQv[ith][0]; fq2 = fQv[ith][1]; } // TPC.E-TPC.W
	       else if( icb==1 ){ psi1 = fEP[ith][3]; psi2 = fEP[ith][4]; fq1 = fQv[ith][3];  fq2 = fQv[ith][4]; } // RXN.E-RXN.W
	       else { psi1 = fEP[ith][5]; psi2 = fEP[ith][6]; fq1 = fQv[ith][5]; fq2 = fQv[ith][6]; } // BBC.E-BBC.W
		       

		        
		
		

			if( psi1<-9000 || psi2<-9000 ) continue;
			if( fq1<0 || fq2<0 ) continue;



                        double dPsi = ( ith + 2. ) * ( psi1 - psi2 );
		   	dPsi = atan2( sin(dPsi), cos(dPsi) );
			if(fCent>-1&&fCent<6){
			
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

// 11.5 gev
float res2tpc[6] = {0.323761,0.434068,0.433521,0.383028,0.307532,0.250556};
float res2rxn[6] = {0.212259,0.333732,0.340171,0.303697,0.247778,0.206723};

float res2bbc[6]={0.248559,0.383837,0.40206,0.373202,0.299496,0.2273};

if(fCent>=0&&fCent<6){

 

  
  for(int itrk=0;itrk<nh;itrk++) {  //track loop

        float pt  = sqrt( TMath::Power(momx[itrk], 2.0 ) + TMath::Power(momy[itrk], 2.0 ) );
	
	float oldphi = atan2( momx[itrk], momy[itrk] );
	float phi=oldphi;
	
	float the = atan2( pt, momz[itrk] );//atan2(pt/pz)
	float eta = -log( tan( 0.5 * the ) );

        // phi += phiRP;
	//  float px = pt * cos(phi);
	//	float py = pt * sin(phi);
	//	pt  = sqrt( TMath::Power(px, 2.0 ) + TMath::Power(py, 2.0 ) );


	

        if( pt<0.2  || pt>4.0 ) continue;


	
       int ipt = 0;
 	for(int i=0; i<npt-1;i++){
	if(pt>=bin_w[i] && pt<bin_w[i+1]) ipt = i;
	}// end of ipt loop

        float v2tpc=-999.0;
	float v2rxn=-999.0;
	float v2bbc=-999.0;

	if(eta>0&&eta<1.0){
         v2tpc = cos(2.0 * (phi-fEP[0][0]) )/res2tpc[fCent];
         v2rxn = cos(2.0 * (phi-fEP[0][3]) )/res2rxn[fCent];
         v2bbc = cos(2.0 * (phi-fEP[0][5]) )/res2bbc[fCent];
 
	}

        if(eta<0&&eta>-1.0){
         v2tpc = cos(2.0 * (phi-fEP[0][1]) )/res2tpc[fCent];
         v2rxn = cos(2.0 * (phi-fEP[0][4]) )/res2rxn[fCent];
         v2bbc = cos(2.0 * (phi-fEP[0][6]) )/res2bbc[fCent];
 
	}

        
	

        if(fabs(eta)<1.0){
	  hv2[0][fCent][ipt][0]->Fill(v2tpc);
          hv2[1][fCent][ipt][0]->Fill(v2rxn);
          hv2[2][fCent][ipt][0]->Fill(v2bbc);
	  hpt[fCent][ipt][0]->Fill(pt);

          if(fCent>0&&fCent<4){

          hv22[0][ipt][0]->Fill(v2tpc);
          hv22[1][ipt][0]->Fill(v2rxn);
          hv22[2][ipt][0]->Fill(v2bbc);

	  }
	  

	  if ( pdg[itrk]==211){
              hv2[0][fCent][ipt][1]->Fill(v2tpc);
              hv2[1][fCent][ipt][1]->Fill(v2rxn);
              hv2[2][fCent][ipt][1]->Fill(v2bbc);
	      hpt[fCent][ipt][1]->Fill(pt);


          if(fCent>0&&fCent<4){

          hv22[0][ipt][1]->Fill(v2tpc);
          hv22[1][ipt][1]->Fill(v2rxn);
          hv22[2][ipt][1]->Fill(v2bbc);

	  }


	      

          }// end of pion selection


	  if ( pdg[itrk]==321){
              hv2[0][fCent][ipt][2]->Fill(v2tpc);
              hv2[1][fCent][ipt][2]->Fill(v2rxn);
              hv2[2][fCent][ipt][2]->Fill(v2bbc);
	      hpt[fCent][ipt][2]->Fill(pt);

          if(fCent>0&&fCent<4){

          hv22[0][ipt][2]->Fill(v2tpc);
          hv22[1][ipt][2]->Fill(v2rxn);
          hv22[2][ipt][2]->Fill(v2bbc);

	  }
	      

          }// end of kaon selection


	   if ( pdg[itrk]==2212){
              hv2[0][fCent][ipt][3]->Fill(v2tpc);
              hv2[1][fCent][ipt][3]->Fill(v2rxn);
              hv2[2][fCent][ipt][3]->Fill(v2bbc);
	      hpt[fCent][ipt][3]->Fill(pt);

           if(fCent>0&&fCent<4){

          hv22[0][ipt][3]->Fill(v2tpc);
          hv22[1][ipt][3]->Fill(v2rxn);
          hv22[2][ipt][3]->Fill(v2bbc);

	  }
	      

          }// end of proton selection

	   
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
