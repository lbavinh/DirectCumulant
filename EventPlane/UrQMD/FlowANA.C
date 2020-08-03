#define FlowANA_cxx
#include "FlowANA.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TString.h"
#include <iostream>
#include <fstream>

using namespace std;
//List of histograms and Ntuples....

static const int neta = 7; 	// bins of pseudorapidity
static const int ndet = 3;	// type of detector: 0-TPC (STAR), 1-RXN (PHENIX), 2-BBC (PHENIX)
static const int ncent = 8; // bins of centrality classes
// static const int nth = 3;	// harmonic order: 0 - 2nd, 1 - 3rd, 2 - 4th
static const int nth = 1;	// harmonic order: 0 - 2nd
static const int npid = 4;	// types of particle: 0 - all, 1 - pion, 2 - kaon,3 - proton

static const int npt = 12; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_w[npt+1]={0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.4,1.8,2.3,2.8,4.0};

static const float maxpt = 3.5; // max pt
static const float minpt = 0.;  // min pt

TH1F *hpt[ncent][npt][npid];		    // transverse momentum distr
TH1F *hv2[ndet][ncent][npt][npid];	// elliptic flow
TH1F *hv22[ndet][npt][npid];

TH1F *H_Qw[neta];
TH1F *H_EP[nth][neta];				// reaction plane
TH1F *H_Qv[nth][neta];

TH1F *HRes[nth][ndet][ncent];		// resolution


TH1F *hbimp;  // impact parameter
TH1F *h2pt;		// pt distribution
TH1F *h2eta;	// eta distribution
TH1F *h2phi;	// azim. angle
// TH1F *h2phirp;	// reaction plane

TFile *d_outfile;

void FlowANA::Loop() {

  if (fChain == 0) return;

  Int_t nentries = Int_t(fChain->GetEntries());

  Int_t nbytes = 0, nb = 0;

  for (Int_t jentry=0; jentry<nentries;jentry++) {
    Int_t ientry = LoadTree(jentry); //in case of a TChain, ientry is the entry number in the current file
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    Ana_event(jentry,ientry);
  }
}

void FlowANA::Ana_init(TString outFile) {
	Booking(outFile.Data());
 	// gRandom->SetSeed( (unsigned int)time(NULL) ); 
}

void FlowANA::Loop_a_file(TString file) {
  TFile *treefile = TFile::Open(file.Data());
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

void FlowANA::Ana_end() {
	d_outfile->cd();

	for( int ieta=0; ieta<neta; ieta++ ){
		H_Qw[ieta]->Write();
	}

	for( int ith=0; ith<nth; ith++ ){
		for( int ieta=0; ieta<neta; ieta++ ){
			H_EP[ith][ieta]->Write();
			H_Qv[ith][ieta]->Write();
		}
	}

	for( int ith=0; ith<nth; ith++ ){
		for( int idet=0; idet<ndet; idet++ ){
			for( int icent=0; icent<ncent; icent++ ){
				HRes[ith][idet][icent]->Write();
			}
		}
	}
	
	for( int icent=0; icent<ncent; icent++ ){
		for( int ipt=0; ipt<npt; ipt++ ){
			for( int id=0; id<npid; id++ ){
				hpt[icent][ipt][id]->Write();
			}
		}

	}

	for( int idet=0; idet<ndet; idet++ ){
		for( int icent=0; icent<ncent; icent++ ){
			for( int ipt=0; ipt<npt; ipt++ ){
				for( int id=0; id<npid; id++ ){
					hv2[idet][icent][ipt][id]->Write();
				}
			}
		}
	}

	for( int idet=0; idet<ndet; idet++ ){
		for( int ipt=0; ipt<npt; ipt++ ){
			for( int id=0; id<npid; id++ ){
				hv22[idet][ipt][id]->Write();
			}
		}
	}
  hbimp->Write();
	h2pt->Write();
	h2eta->Write();
	h2phi->Write();

	d_outfile->Close();
} // end of ana_end

void FlowANA::Booking(TString outFile) {
	d_outfile = new TFile(outFile.Data(),"recreate");

	h2eta  = new TH1F("h2eta","eta distribution",200,-7,7);
	h2pt  = new TH1F("h2pt","pt distribution",200,0,10.0);
	hbimp  = new TH1F("hbimp","Imact Parameter",180,0,18);
	h2phi = new TH1F("h2phi","azim. angle", 100, -TMath::Pi(), TMath::Pi()+2.*TMath::Pi()/100 );
	// h2phirp = new TH1F("h2phirp","azim. angle", 100, -TMath::Pi(), TMath::Pi()+2.*TMath::Pi()/100 );

  char name[800];
	for( int ieta=0; ieta<neta; ieta++ ){
    (void)sprintf(name,"H_Qw_%d",ieta);
    H_Qw[ieta] = new TH1F(name,name, 100, 0, 1000 );
  }

	for( int ith=0; ith<nth; ith++ ){
		for( int ieta=0; ieta<neta; ieta++ ){
      (void)sprintf(name,"H_EP_%d_%d",ith,ieta);
	    H_EP[ith][ieta] = new TH1F(name,name, 100, -TMath::Pi()/(ith+2.)-0.1, TMath::Pi()/(ith+2.)+0.10 );
      (void)sprintf(name,"H_Qv_%d_%d",ith,ieta);
	    H_Qv[ith][ieta] = new TH1F(name,name, 100, 0, 10 );
		}
	}

	for( int ith=0; ith<nth; ith++ ){
		for( int idet=0; idet<ndet; idet++ ){
			for( int icent=0; icent<ncent; icent++ ){
        (void)sprintf(name,"HRes_%d_%d_%d",ith,idet,icent);
	      HRes[ith][idet][icent] = new TH1F(name,name, 100, -10, 10 );
			}
		}
	}

	for( int idet=0; idet<ndet; idet++ ){
		for( int icent=0; icent<ncent; icent++ ){
			for( int ipt=0; ipt<npt; ipt++ ){
				for( int id=0; id<npid; id++ ){
          (void)sprintf(name,"hv2_%d_%d_%d_%d",idet,icent,ipt,id);
	        hv2[idet][icent][ipt][id] = new TH1F(name,name, 400, -10, 10 );
				}
			}
		}
	}

	for( int idet=0; idet<ndet; idet++ ){
		for( int ipt=0; ipt<npt; ipt++ ){
			for( int id=0; id<npid; id++ ){
        (void)sprintf(name,"hv22_%d_%d_%d",idet,ipt,id);
	      hv22[idet][ipt][id] = new TH1F(name,name, 400, -10, 10 );
			}
		}
	}

	for( int icent=0; icent<ncent; icent++ ){
		for( int ipt=0; ipt<npt; ipt++ ){
			for( int id=0; id<npid; id++ ){
        (void)sprintf(name,"hpt_%d_%d_%d",icent,ipt,id);
	      hpt[icent][ipt][id] = new TH1F(name,name, 400, 0, 10 );
			}
		}
	}
  cout << "Histograms have been initialized." << endl;
} // end of book hist

// Analysis for each event !!!!  

void FlowANA::Ana_event(int jentry, int ientry) { 

  // float phiRP = gRandom->Uniform(0, 2.*TMath::Pi());
 	// h2phirp->Fill(phiRP);

 	if(jentry%100000==0) cout <<jentry<<endl;

	float sumQxy[nth][neta][2] = {{{0}}}; //[ith][eta][x,y]
	float multQv[neta] = {0}; //[eta]

	hbimp->Fill(bimp);
	
	for(int itrk=0;itrk<nh;itrk++) {  //track loop

		float pt = sqrt( TMath::Power(momx[itrk],2.) + TMath::Power(momy[itrk],2.) );
		float phi = TMath::ATan2( momy[itrk], momx[itrk] );
		float the = TMath::ATan2( pt, momz[itrk] );
		float eta = -log( tan( 0.5 * the ) );

		h2pt->Fill(pt);
		h2eta->Fill(eta);
		h2phi->Fill(phi);
		
		if( pt<0.2 || pt>2.5 ) continue;

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
		
		if( fEta>-1 ){
			for( int ith=0; ith<nth; ith++ ){
				sumQxy[ith][fEta][0] += pt * cos( (ith+2.0) * phi );
				sumQxy[ith][fEta][1] += pt * sin( (ith+2.0) * phi );
			}
			multQv[fEta]++;
		} // end of eta selection
	} // end of track loop

	int fCent   = GetCentrality10_Bimp(bimp);
	
	float fEP[nth][neta]; // [ith][eta]
	float fQv[nth][neta]; // [ith][eta]
	for( int ith=0; ith<nth; ith++ ){ // flow harmonic loop (2,3,4)
		for( int ieta=0; ieta<neta; ieta++ ){ // ep detector gap 
			if( multQv[ieta]>5 ){ // multiplicity > 5
				fEP[ith][ieta] = TMath::ATan2( sumQxy[ith][ieta][1], sumQxy[ith][ieta][0] ) / ( ith + 2.0 );
				fEP[ith][ieta] = TMath::ATan2( sin( (ith+2.0)*fEP[ith][ieta] ), cos( (ith+2.0)*fEP[ith][ieta] ) ); // what for?
				fEP[ith][ieta] /= ( ith + 2.0 );

				fQv[ith][ieta] = TMath::Sqrt( TMath::Power( sumQxy[ith][ieta][0],2.0)+TMath::Power( sumQxy[ith][ieta][1], 2.0))/TMath::Sqrt( multQv[ieta] );
				H_Qw[ieta]->Fill( multQv[ieta] );
			}else{
				fEP[ith][ieta] = -9999;
				fQv[ith][ieta] = -9999;
			}// end of mult cut selection
		} // end of loop on EP detectors
	} // end of flow harmonic loop

	for( int ith=0; ith<nth; ith++ ){ // harmonic loop
		for( int ieta=0; ieta<7; ieta++ ){// eta EP detector loop
			if( fEP[ith][ieta]>-9000 ){ // EP reconstructed 
				H_EP[ith][ieta]->Fill( fEP[ith][ieta] );
				H_Qv[ith][ieta]->Fill( fQv[ith][ieta] );
			}// end of EP reconstructed
		}// end of eta loop
	}// end of harm loop

	// Resolution
	for( int ith=0; ith<nth; ith++ ){
		for( int icb=0; icb<3; icb++ ){ // icb - detector
			double psi1, psi2, fq1, fq2;
		
			if ( icb==0 ){ psi1 = fEP[ith][0]; psi2 = fEP[ith][1]; fq1 = fQv[ith][0]; fq2 = fQv[ith][1]; } // TPC.E-TPC.W
			else if( icb==1 ){ psi1 = fEP[ith][3]; psi2 = fEP[ith][4]; fq1 = fQv[ith][3];  fq2 = fQv[ith][4]; } // RXN.E-RXN.W
			else { psi1 = fEP[ith][5]; psi2 = fEP[ith][6]; fq1 = fQv[ith][5]; fq2 = fQv[ith][6]; } // BBC.E-BBC.W

			if( psi1<-9000 || psi2<-9000 ) continue;
			if( fq1<0 || fq2<0 ) continue;

			double dPsi = ( ith + 2. ) * ( psi1 - psi2 );
			dPsi = atan2( sin(dPsi), cos(dPsi) );
			if(fCent>-1&&fCent<ncent){
				HRes[ith][icb][fCent]->Fill( cos(dPsi) );
			}
		}
	}

	// float res2tpc[6]={0.493507,0.716751,0.748541,0.709883,0.623788,0.491104};

	// float res2rxn[6]={0.540663,0.793812,0.82354,0.794412,0.714603,0.579696};
	// float res2bbc[6]={0.248559,0.383837,0.40206,0.373202,0.299496,0.2273};

	// if(fCent>=0&&fCent<6){ // centrality selection
	// for(int itrk=0;itrk<nh;itrk++) {  //track loop
	// 	float pt  = sqrt( TMath::Power(momx[itrk], 2.0 ) + TMath::Power(momy[itrk], 2.0 ) );
		
	// 	float phi = TMath::ATan2( momy[itrk], momx[itrk] );
		
	// 	float the = atan2( pt, momz[itrk] );//atan2(pt/pz)
	// 	float eta = -log( tan( 0.5 * the ) );

	// 	if( pt<minpt  || pt>maxpt ) continue;

	// 	int ipt = 0;
	// 	for(int i=0; i<npt;i++){
	// 		if(pt>=bin_w[i] && pt<bin_w[i+1]) ipt = i;
	// 	}// end of ipt loop

	// 	float v2tpc=-999.0;
	// 	float v2rxn=-999.0;
	// 	float v2bbc=-999.0;

	// 	if(eta>0&&eta<1.0){ // East
	// 		v2tpc = cos(2.0 * (phi-fEP[0][0]) )/res2tpc[fCent]; // TPC
	// 		v2rxn = cos(2.0 * (phi-fEP[0][3]) )/res2rxn[fCent]; // RXN
	// 		v2bbc = cos(2.0 * (phi-fEP[0][5]) )/res2bbc[fCent]; // BBC
	// 	}

	// 	if(eta<0&&eta>-1.0){ // West
	// 		v2tpc = cos(2.0 * (phi-fEP[0][1]) )/res2tpc[fCent];
	// 		v2rxn = cos(2.0 * (phi-fEP[0][4]) )/res2rxn[fCent];
	// 		v2bbc = cos(2.0 * (phi-fEP[0][6]) )/res2bbc[fCent];
	// 	}
	// 	if(fabs(eta)<1.0){ // |eta| < 1.0
	// 		hv2[0][fCent][ipt][0]->Fill(v2tpc);
	// 		hv2[1][fCent][ipt][0]->Fill(v2rxn);
	// 		hv2[2][fCent][ipt][0]->Fill(v2bbc);
	// 		hpt[fCent][ipt][0]->Fill(pt);

	// 		if(fCent>0&&fCent<4){ // centrality cut 0-50
	// 		hv22[0][ipt][0]->Fill(v2tpc);
	// 		hv22[1][ipt][0]->Fill(v2rxn);
	// 		hv22[2][ipt][0]->Fill(v2bbc);
	// 		}
	// 		if ( pdg[itrk]==211){ // pion selection
	// 			hv2[0][fCent][ipt][1]->Fill(v2tpc);
	// 			hv2[1][fCent][ipt][1]->Fill(v2rxn);
	// 			hv2[2][fCent][ipt][1]->Fill(v2bbc);
	// 			hpt[fCent][ipt][1]->Fill(pt);


	// 			if(fCent>0&&fCent<4){ // centrality cut 0-50
	// 			hv22[0][ipt][1]->Fill(v2tpc);
	// 			hv22[1][ipt][1]->Fill(v2rxn);
	// 			hv22[2][ipt][1]->Fill(v2bbc);
	// 			}
	// 		}// end of pion selection


	// 		if ( pdg[itrk]==321){ // kaon selection
	// 			hv2[0][fCent][ipt][2]->Fill(v2tpc);
	// 			hv2[1][fCent][ipt][2]->Fill(v2rxn);
	// 			hv2[2][fCent][ipt][2]->Fill(v2bbc);
	// 			hpt[fCent][ipt][2]->Fill(pt);

	// 			if(fCent>0&&fCent<4){ // centrality cut 0-50
	// 			hv22[0][ipt][2]->Fill(v2tpc);
	// 			hv22[1][ipt][2]->Fill(v2rxn);
	// 			hv22[2][ipt][2]->Fill(v2bbc);
	// 			}
	// 		}// end of kaon selection

	// 		if ( pdg[itrk]==2212){ // proton selection
	// 			hv2[0][fCent][ipt][3]->Fill(v2tpc);
	// 			hv2[1][fCent][ipt][3]->Fill(v2rxn);
	// 			hv2[2][fCent][ipt][3]->Fill(v2bbc);
	// 			hpt[fCent][ipt][3]->Fill(pt);

	// 			if(fCent>0&&fCent<4){ // centrality cut 0-50
	// 			hv22[0][ipt][3]->Fill(v2tpc);
	// 			hv22[1][ipt][3]->Fill(v2rxn);
	// 			hv22[2][ipt][3]->Fill(v2bbc);
	// 			}
	// 		}// end of proton selection
	// 	} // end of |eta| < 1.0
	// }// end of the track loop
 	// }// end of centrality selection 
} // end of ana_event

// Urqmd 7.7 GeV

int FlowANA::GetCentrality10_Bimp( float bimp ){

	int fcent;
	if     ( bimp<4.5  ) fcent = 0; // 0-10%
	else if( bimp<6.3  ) fcent = 1; //10-20%
	else if( bimp<7.73 ) fcent = 2; //20-30%
	else if( bimp<8.92 ) fcent = 3; //30-40%
	else if( bimp<9.99 ) fcent = 4; //40-50%
	else if( bimp<10.83) fcent = 5; //50-60%
	else if( bimp<11.78) fcent = 6; //60-70%
	else if( bimp<12.61) fcent = 7; //70-80%
	else                 fcent =-1;

	return fcent;
}