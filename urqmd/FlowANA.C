#define FlowANA_cxx
#include "FlowANA.h"
#include "function.C"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TVector3.h"
#include "TVectorD.h"
#include "TString.h"
#include <iostream>
#include <fstream>

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
} // end of book hist

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
	}	
  */

 	if(ientry%100000==0) cout << ientry<<endl;// event counter

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
		
		if( pt<0.2  || pt>2.5 ) continue;

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
		// if( fabs(eta)>3.0 && fabs(eta)<5.0 )     fEta = 8; // BBC combined
		
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

	float res2tpc[6]={0.493507,0.716751,0.748541,0.709883,0.623788,0.491104};

	float res2rxn[6]={0.540663,0.793812,0.82354,0.794412,0.714603,0.579696};
	float res2bbc[6]={0.248559,0.383837,0.40206,0.373202,0.299496,0.2273};

	if(fCent>=0&&fCent<6){ // centrality selection
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
		if(fabs(eta)<1.0){ // |eta| < 1.0
			hv2[0][fCent][ipt][0]->Fill(v2tpc);
			hv2[1][fCent][ipt][0]->Fill(v2rxn);
			hv2[2][fCent][ipt][0]->Fill(v2bbc);
			hpt[fCent][ipt][0]->Fill(pt);

			if(fCent>0&&fCent<4){
			hv22[0][ipt][0]->Fill(v2tpc);
			hv22[1][ipt][0]->Fill(v2rxn);
			hv22[2][ipt][0]->Fill(v2bbc);
			}
			if ( pdg[itrk]==211){ // pion selection
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


			if ( pdg[itrk]==321){ // kaon selection
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

			if ( pdg[itrk]==2212){ // proton selection
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
		} // end of |eta| < 1.0
  		}// end of the track loop
 	}// end of centrality selection 
} // end of ana_event

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
/*



static const int ncent = 8; // 0-80%
static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

static const Float_t maxpt = 3.5; // max pt
static const Float_t minpt = 0.2; // min pt
static const int npt = 24; // 0.2 - 3.5 GeV/c 
static const double bin_pT[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
                                1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,
                                2.6,2.8,3.0,3.2,3.5};

TFile *d_outfile;      // out file with histograms and profiles

TH1F *hRP; // reaction plane distr
TH1F *hPt; // transverse momentum distr
TH1F *hPhi; // distr of particle azimuthal angle with respect to RP 
TH1F *hPhil; // distr of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta; // pseudorapidity
TH1F *hBimp;// impact parameter
TH1I *hMult; // emitted multiplicity 
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

// histograms for differential flow calculation from MC toy
TH1F *hpt[ncent][npt];
TH1F *hv2pt[ncent][npt];      // dif. v2 distr in each pT bin from MC toy
// TProfile for reference flow
TProfile *hv2MC[ncent];       // profile for MC integrated v2
TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
// TProfile for differential flow
TProfile *hPT[ncent][npt];       // profile pt 
TProfile *hv2MCpt[ncent][npt];   // profile v2pt from MC toy   
TProfile *hv22pt[ncent][npt];    // profile <<2'>> from 2nd Q-Cumulants
TProfile *hv24pt[ncent][npt];    // profile <<4'>> from 4th Q-Cumulants
// TProfile for covariance calculation according to (C.12)
// Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider. 
// Appendix C
TProfile *hcov24[ncent];       // <2>*<4>
TProfile *hcov22prime[ncent][npt]; // <2>*<2'>
TProfile *hcov24prime[ncent][npt]; // <2>*<4'>
TProfile *hcov42prime[ncent][npt]; // <2>*<4'>
TProfile *hcov44prime[ncent][npt]; // <4>*<4'>
TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>


// Vectors for non-uniform acceptance correction
Double_t cos2phi1[ncent]={0}, sin2phi1[ncent]={0}, cos2phi12[ncent]={0}, sin2phi12[ncent]={0}, cos2phi123[ncent]={0}, sin2phi123[ncent]={0}; // for non-uniform acceptance RF calc
Double_t cos2psi1[ncent][npt]={{0}}, sin2psi1[ncent][npt]={{0}}, cos2psi1phi2[ncent][npt]={{0}}, sin2psi1phi2[ncent][npt]={{0}},
         cos2psi1pphi23[ncent][npt]={{0}}, sin2psi1pphi23[ncent][npt]={{0}}, cos2psi1mphi23[ncent][npt]={{0}}, sin2psi1mphi23[ncent][npt]={{0}}; // for non-uniform acceptance DF calc
Double_t sumM[ncent]={0}, sumMMm1[ncent]={0}, sumMMm1Mm2[ncent]={0}; // for non-uniform acceptance RF calc
Double_t summp[ncent][npt]={{0}}, summpMmmq[ncent][npt]={{0}}, summpMm2mqMm1[ncent][npt]={{0}}; // for non-uniform acceptance DF calc

TVectorD *vcos2phi1[ncent], *vsin2phi1[ncent], *vcos2phi12[ncent], *vsin2phi12[ncent], *vcos2phi123[ncent], *vsin2phi123[ncent];
TVectorD *vcos2psi1[ncent], *vsin2psi1[ncent], *vcos2psi1phi2[ncent], *vsin2psi1phi2[ncent], *vcos2psi1pphi23[ncent],
         *vsin2psi1pphi23[ncent], *vcos2psi1mphi23[ncent], *vsin2psi1mphi23[ncent];

void hVana::Booking(TString outFile){
   char name[800];
   char title[800];
   d_outfile = new TFile(outFile.Data(),"recreate");
   cout << outFile.Data() << " has been initialized" << endl;

   hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 2500, 0, 2500);
   hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 1500, 0, 1500, 200, 0., 20.);
   hBimp = new TH1F("hBimp","Impact parameter;b (fm);dN/db",200, 0., 20.);
   hPt   = new TH1F("hPt","Pt-distr;p_{T} (GeV/c); dN/dP_{T}",500,0.,6.);
   hRP   = new TH1F("hRP","Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}",300,0.,7.);
   hPhi  = new TH1F("hPhi","Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})",300,0.,7.);
   hPhil = new TH1F("hPhil","Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi",300,0.,7.);
   hEta  = new TH1F("hEta","Pseudorapidity distr; #eta; dN/d#eta",300,-2.2,2.2);

   for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
      sprintf(name,"hv2MC_cent%i",icent);
      sprintf(title,"v_{2}(cent), cent=%i-%i%%",bin_cent[icent]-5,bin_cent[icent]+5);
      hv2MC[icent] = new TProfile(name,title,1,0.,1.);
      hv2MC[icent]->Sumw2();

      sprintf(name,"hv22_cent%i",icent);
      sprintf(title,"v_{2}{2}(cent), cent=%i-%i%%",bin_cent[icent]-5,bin_cent[icent]+5);
      hv22[icent] = new TProfile(name,title,1,0.,1.);
      hv22[icent]->Sumw2();

      sprintf(name,"hv24_cent%i",icent);
      sprintf(title,"v_{2}{4}(cent), cent=%i-%i%%",bin_cent[icent]-5,bin_cent[icent]+5);
      hv24[icent] = new TProfile(name,title,1,0.,1.);
      hv24[icent]->Sumw2();

      sprintf(name,"hcov24_cent%i",icent);
      sprintf(title,"<2>#upoint<4> distr, cent=%i-%i%%",bin_cent[icent]-5,bin_cent[icent]+5);
      hcov24[icent] = new TProfile(name,title,1,0.,1.);
      hcov24[icent]->Sumw2();        

      for(int kpt=0; kpt<npt; kpt++){ // loop over pt bin
         sprintf(name,"hpt_cent%i_pt%i",icent,kpt);
         sprintf(title,"p_{T} distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hpt[icent][kpt]=new TH1F(name,title,300,0.1,9.2);

         sprintf(name,"hv2pt_cent%i_pt%i",icent,kpt);
         sprintf(title,"v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hv2pt[icent][kpt]=new TH1F(name,title,400,-1,1);

         sprintf(name,"hPT_cent%i_pt%i",icent,kpt);
         sprintf(title,"p_{T} distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hPT[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hPT[icent][kpt]->Sumw2();

         sprintf(name,"hv2MCpt_cent%i_pt%i",icent,kpt);
         sprintf(title,"v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hv2MCpt[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hv2MCpt[icent][kpt]->Sumw2();

         sprintf(name,"hv22pt_cent%i_pt%i",icent,kpt);
         sprintf(title,"v_{2}{2,QC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hv22pt[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hv22pt[icent][kpt]->Sumw2();

         sprintf(name,"hv24pt_cent%i_pt%i",icent,kpt);
         sprintf(title,"v_{2}{4,QC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hv24pt[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hv24pt[icent][kpt]->Sumw2();

         sprintf(name,"hcov22prime_cent%i_pt%i",icent,kpt);
         sprintf(title,"<2>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hcov22prime[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hcov22prime[icent][kpt]->Sumw2();

         sprintf(name,"hcov24prime_cent%i_pt%i",icent,kpt);
         sprintf(title,"<2>#upoint<4'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hcov24prime[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hcov24prime[icent][kpt]->Sumw2();

         sprintf(name,"hcov42prime_cent%i_pt%i",icent,kpt);
         sprintf(title,"<4>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hcov42prime[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hcov42prime[icent][kpt]->Sumw2();

         sprintf(name,"hcov44prime_cent%i_pt%i",icent,kpt);
         sprintf(title,"<4>#upoint<4'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hcov44prime[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hcov44prime[icent][kpt]->Sumw2();

         sprintf(name,"hcov2prime4prime_cent%i_pt%i",icent,kpt);
         sprintf(title,"<4'>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c",bin_cent[icent]-5,bin_cent[icent]+5,bin_pT[kpt],bin_pT[kpt+1]);
         hcov2prime4prime[icent][kpt]=new TProfile(name,title,1,0.,1.);
         hcov2prime4prime[icent][kpt]->Sumw2();
      } // end of loop over pt bin

      // Vectors for non-uniform acceptance correction
      vcos2phi1[icent] = new TVectorD(1);
      vsin2phi1[icent] = new TVectorD(1);
      vcos2phi12[icent] = new TVectorD(1);
      vsin2phi12[icent] = new TVectorD(1);
      vcos2phi123[icent] = new TVectorD(1);
      vsin2phi123[icent] = new TVectorD(1);

      vcos2psi1[icent] = new TVectorD(npt);
      vsin2psi1[icent] = new TVectorD(npt);
      vcos2psi1phi2[icent] = new TVectorD(npt);
      vsin2psi1phi2[icent] = new TVectorD(npt);
      vcos2psi1pphi23[icent] = new TVectorD(npt);
      vsin2psi1pphi23[icent] = new TVectorD(npt);
      vcos2psi1mphi23[icent] = new TVectorD(npt);
      vsin2psi1mphi23[icent] = new TVectorD(npt);

   } // end of loop over centrality classes

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
   char name[800];
   for(int icent=0; icent<ncent; icent++){
      cos2phi1[icent]    /= sumM[icent];
      sin2phi1[icent]    /= sumM[icent];
      cos2phi12[icent]   /= sumMMm1[icent];
      sin2phi12[icent]   /= sumMMm1[icent];
      cos2phi123[icent]  /= sumMMm1Mm2[icent];
      sin2phi123[icent]  /= sumMMm1Mm2[icent];

      (*vcos2phi1[icent])(0)   = cos2phi1[icent];
      (*vsin2phi1[icent])(0)   = sin2phi1[icent];
      (*vcos2phi12[icent])(0)  = cos2phi12[icent];
      (*vsin2phi12[icent])(0)  = sin2phi12[icent];
      (*vcos2phi123[icent])(0) = cos2phi123[icent];
      (*vsin2phi123[icent])(0) = sin2phi123[icent];

      sprintf(name,"vcos2phi1_cent%i",icent);
      vcos2phi1[icent] -> Write(name);
      sprintf(name,"vsin2phi1_cent%i",icent);
      vsin2phi1[icent] -> Write(name);
      sprintf(name,"vcos2phi12_cent%i",icent);
      vcos2phi12[icent] -> Write(name);
      sprintf(name,"vsin2phi12_cent%i",icent);
      vsin2phi12[icent] -> Write(name);
      sprintf(name,"vcos2phi123_cent%i",icent);
      vcos2phi123[icent] -> Write(name);
      sprintf(name,"vsin2phi123_cent%i",icent);
      vsin2phi123[icent] -> Write(name);

      for(int i=0; i<npt; i++){
         cos2psi1[icent][i]         /= summp[icent][i];
         sin2psi1[icent][i]         /= summp[icent][i];
         cos2psi1phi2[icent][i]     /= summpMmmq[icent][i];
         sin2psi1phi2[icent][i]     /= summpMmmq[icent][i];
         cos2psi1pphi23[icent][i]   /= summpMm2mqMm1[icent][i];
         sin2psi1pphi23[icent][i]   /= summpMm2mqMm1[icent][i];
         cos2psi1mphi23[icent][i]   /= summpMm2mqMm1[icent][i];
         sin2psi1mphi23[icent][i]   /= summpMm2mqMm1[icent][i];

         (*vcos2psi1[icent])(i)         = cos2psi1[icent][i];
         (*vsin2psi1[icent])(i)         = sin2psi1[icent][i];
         (*vcos2psi1phi2[icent])(i)     = cos2psi1phi2[icent][i];
         (*vsin2psi1phi2[icent])(i)     = sin2psi1phi2[icent][i];
         (*vcos2psi1pphi23[icent])(i)   = cos2psi1pphi23[icent][i];
         (*vsin2psi1pphi23[icent])(i)   = sin2psi1pphi23[icent][i];
         (*vcos2psi1mphi23[icent])(i)   = cos2psi1mphi23[icent][i];
         (*vsin2psi1mphi23[icent])(i)   = sin2psi1mphi23[icent][i];
      }

      sprintf(name,"vcos2psi1_cent%i",icent);
      vcos2psi1[icent] -> Write(name);
      sprintf(name,"vsin2psi1_cent%i",icent);
      vsin2psi1[icent] -> Write(name);
      sprintf(name,"vcos2psi1phi2_cent%i",icent);
      vcos2psi1phi2[icent] -> Write(name);
      sprintf(name,"vsin2psi1phi2_cent%i",icent);
      vsin2psi1phi2[icent] -> Write(name);
      sprintf(name,"vcos2psi1pphi23_cent%i",icent);
      vcos2psi1pphi23[icent] -> Write(name);
      sprintf(name,"vsin2psi1pphi23_cent%i",icent);
      vsin2psi1pphi23[icent] -> Write(name);
      sprintf(name,"vcos2psi1mphi23_cent%i",icent);
      vcos2psi1mphi23[icent] -> Write(name);
      sprintf(name,"vsin2psi1mphi23_cent%i",icent);
      vsin2psi1mphi23[icent] -> Write(name);
   }

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
   int icent=-1;   
   for (int i=0; i<ncent; i++){ // loop over centrality
      if (CentB(b) == bin_cent[i]) icent = i;
   }
   if (icent<0) return;
   hMult -> Fill(nh);
   hRP -> Fill(rp);
   hBimp -> Fill(b);
   hBimpvsMult -> Fill(nh,b);
   // notation as (26) in DOI:10.1103/PhysRevC.83.044913

   // Q-vector of RFP
   Double_t Qx2=0., Qy2=0., Qx4=0., Qy4=0.;
   TComplex Q2=0., Q4=0.;
   // p-vector of POI
   Double_t px2[npt]={0.}, py2[npt]={0.};
   TComplex p2[npt]={0.}, p4[npt]={0.}, q2[npt]={0.}, q4[npt]={0.};
   // q-vector of particles marked as POI and RFP, which is used for 
   // autocorrelation substraction
   Double_t qx2[npt]={0.}, qy2[npt]={0.}, qx4[npt]={0.}, qy4[npt]={0.};
   // Total number of RFP in given event
   Double_t M = 0.;
   // numbers of POI (mp) and particles marked both POI and RFP (mq)
   Double_t mq[npt]={0.},mp[npt]={0.};
   // average reduced single-event 2- and 4-particle correlations : <2'> & <4'>
   Double_t redCor22[npt]={0.}, redCor24[npt]={0.};
   // event weights for correlation calculation
   Double_t w2=0.,w4=0.;
   // event weights for reduced correlation calculation
   Double_t wred2[npt]={0.},wred4[npt]={0.};
   // Average single-event 2- and 4- particle correlations : <2> & <4>
   Double_t cor22 = 0., cor24 = 0.;
   for(int i=0;i<nh;i++) { // track loop
      hPhi -> Fill(phi0[i]-rp);
      hPhil -> Fill(phi0[i]);
      hEta -> Fill(eta[i]);
      
      Int_t ipt = 0;
      Float_t pT = pt[i];
      hPt -> Fill(pT);
      
      for(int j=0; j<npt;j++){
         if(pT>=bin_pT[j] && pT<bin_pT[j+1]) ipt = j;
      }

      Double_t v2 = TMath::Cos(2*(phi0[i] - rp));
      // Calculate differential v2 from MC toy
      hpt[icent][ipt]->Fill(pT);             // pt histogram
      hPT[icent][ipt]-> Fill(0.5,pT,1);      // pt profile
      hv2pt[icent][ipt]->Fill(v2);
      hv2MCpt[icent][ipt]->Fill(0.5,v2,1);   // I found it better to use TProfile, than TH1

      // RFP
      if(eta[i]<0){
         hv2MC[icent] -> Fill(0.5,v2,1); // v2 from MC toy
         Qx2+=TMath::Cos(2*phi0[i]);
         Qy2+=TMath::Sin(2*phi0[i]);
         Qx4+=TMath::Cos(4*phi0[i]);
         Qy4+=TMath::Sin(4*phi0[i]);
         M++;
      }

      // POI
      if(eta[i]>=0){
      px2[ipt]+=TMath::Cos(2*phi0[i]);
      py2[ipt]+=TMath::Sin(2*phi0[i]);
      mp[ipt]++;
      }

   } // end of track loop
   if (M >= 2.){ // <2> definition condition
      Q2 = TComplex(Qx2, Qy2);
      w2 = M*(M-1);                             // w(<2>)
      cor22 = CalCor22(Q2, M, w2);     // <2>
      if (w2<0) cout << "ERROR!!!" << endl; // test
      hv22[icent] -> Fill(0.5,cor22,w2); // <<2>>

      // Non-uniform acceptance correction
      cos2phi1[icent]   += Qx2; // formula (C2)
      sin2phi1[icent]   += Qy2; // formula (C3)     
      sumM[icent] += M;

      for(int ipt=0; ipt<npt;ipt++){
         if (mp[ipt] == 0) continue;

         p2[ipt] = TComplex(px2[ipt], py2[ipt]);
         q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
         wred2[ipt] = mp[ipt]*M-mq[ipt];                                         // w(<2'>)
         redCor22[ipt] = CalRedCor22(Q2,p2[ipt],M,mp[ipt],mq[ipt],wred2[ipt]);   // <2'>
         hv22pt[icent][ipt] -> Fill(0.5,redCor22[ipt],wred2[ipt]);                      // <<2'>>
         
         // TProfile for covariance calculation in statistic error
         hcov22prime[icent][ipt] -> Fill(0.5,cor22*redCor22[ipt],w2*wred2[ipt]);        // <2>*<2'>

         // Non-uniform acceptance correction
         cos2psi1[icent][ipt] += px2[ipt];
         sin2psi1[icent][ipt] += py2[ipt];
         summp[icent][ipt] += mp[ipt];
      }
   } // end of <2> definition condition

   if (M >= 4.){ // <4> definition condition
      Q4 = TComplex(Qx4, Qy4);                                   
      w4 = M*(M-1)*(M-2)*(M-3);                             // w(<4>)
      cor24 = CalCor24(Q2, Q4, M, w4); // <4>
      hv24[icent] -> Fill(0.5,cor24,w4); // <<4>>

      // TProfile for covariance calculation in statistic error
      hcov24[icent] -> Fill(0.5,cor22*cor24,w2*w4); // <2>*<4>

      // Non-uniform acceptance correction
      cos2phi12[icent]  += (Q2*Q2-Q4).Re();
      sin2phi12[icent]  += (Q2*Q2-Q4).Im();
      cos2phi123[icent] += ((Q2*Qstar(Q2)*Qstar(Q2)-Q2*Qstar(Q4)).Re())
                  - 2.*(M-1)*(Qstar(Q2).Re());
      sin2phi123[icent] += ((Q2*Qstar(Q2)*Qstar(Q2)-Q2*Qstar(Q4)).Im())
                  - 2.*(M-1)*(Qstar(Q2).Im());
      sumMMm1[icent] += M*(M-1);
      sumMMm1Mm2[icent] += M*(M-1)*(M-2);

      for(int ipt=0; ipt<npt;ipt++){
         if (mp[ipt] == 0) continue;
         q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
         wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);    // w(<4'>)
         redCor24[ipt] = CalRedCor24(Q2,Q4,p2[ipt],q2[ipt],q4[ipt],M,mp[ipt],mq[ipt],wred4[ipt]);  // <4'>
         hv24pt[icent][ipt] -> Fill(0.5,redCor24[ipt],wred4[ipt]);                                 // <<4'>>
         
         // TProfile for covariance calculation in statistic error
         hcov24prime[icent][ipt] -> Fill(0.5,cor22*redCor24[ipt],w2*wred4[ipt]);
         hcov42prime[icent][ipt] -> Fill(0.5,cor24*redCor22[ipt],w4*wred2[ipt]);
         hcov44prime[icent][ipt] -> Fill(0.5,cor24*redCor24[ipt],w4*wred4[ipt]);
         hcov2prime4prime[icent][ipt] -> Fill(0.5,redCor22[ipt]*redCor24[ipt],wred2[ipt]*wred4[ipt]);

         // Non-uniform acceptance correction
         cos2psi1phi2[icent][ipt] += (p2[ipt]*Q2-q4[ipt]).Re();
         sin2psi1phi2[icent][ipt] += (p2[ipt]*Q2-q4[ipt]).Im();
         cos2psi1pphi23[icent][ipt] += ((p2[ipt]*(Q2.Rho2()-M)).Re()) - ((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Re());
         sin2psi1pphi23[icent][ipt] += ((p2[ipt]*(Q2.Rho2()-M)).Im()) - ((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Im());
         cos2psi1mphi23[icent][ipt] += ((p2[ipt]*Qstar(Q2)*Qstar(Q2)-p2[ipt]*Qstar(Q4)).Re())-((2.*mq[ipt]*Qstar(Q2)-2.*Qstar(q2[ipt])).Re());
         sin2psi1mphi23[icent][ipt] += ((p2[ipt]*Qstar(Q2)*Qstar(Q2)-p2[ipt]*Qstar(Q4)).Im())-((2.*mq[ipt]*Qstar(Q2)-2.*Qstar(q2[ipt])).Im());

         summpMmmq[icent][ipt] += mp[ipt]*M-mq[ipt];
         summpMm2mqMm1[icent][ipt] += (mp[ipt]*M-2.*mq[ipt])*(M-1);
      }
   } // end of <4> definition condition

}
*/