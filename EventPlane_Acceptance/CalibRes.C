#define CalibRes_cxx
#include "CalibRes.h"
#include "function.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include "TString.h"

#include <iostream>
#include <fstream>
using namespace std;

static const int ncent = 8; // 0-80%
static const int bin_cent[ncent] = {5, 15, 25, 35, 45, 55, 65, 75};

static const Float_t maxpt = 3.5; // max pt
static const Float_t minpt = 0.2; // min pt
static const int npt = 24;        // 0.2 - 3.5 GeV/c
static const double bin_pT[npt + 1] = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1,
                                       1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 2.0, 2.2, 2.4,
                                       2.6, 2.8, 3.0, 3.2, 3.5};
static const int neta = 2; // [eta-,eta+]
TFile *d_outfile; // out file with histograms and profiles

TH1F *hRP;         // reaction plane distr
TH1F *hPt;         // transverse momentum distr
TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta;        // pseudorapidity
TH1F *hBimp;       // impact parameter
TH1I *hMult;       // emitted multiplicity
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

// TProfile for MC reference flow (RF)
TProfile *hv2MC[ncent]; // profile for MC integrated v2
// TProfile for MC differential flow (DF)
TProfile *hPT[ncent][npt];     // profile pt
TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy

TH1F *H_Qw[neta];
TH1F *H_EP[neta];				// reaction plane
TH1F *H_Qv[neta];
TH1F *HRes[ncent];		// resolution

TH1F *hv2EP[ncent][npt];	// elliptic flow from EP method
TH1F *hv22EP[ncent];      // integrated elliptic flow from EP method

TProfile *pQx[neta];
TProfile *pQy[neta];
TProfile *pCosNPsi[neta];
TProfile *pSinNPsi[neta];
TProfile *pFlatCos[neta];
TProfile *pFlatSin[neta];

TH1F *hPsiRecentered[neta];
TH1F *hPsiFlattened[neta];



Double_t qxMean[ncent][neta];
Double_t qyMean[ncent][neta];





void CalibRes::Booking(TString outFile)
{
  char name[800];
  char title[800];
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << "Output file \"" << outFile.Data() << "\" has been initialized" << endl;

  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 2500, 0, 2500);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 1500, 0, 1500, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);

  for( int ieta=0; ieta<neta; ieta++ ){
    (void)sprintf(name,"H_Qw_%d",ieta);
    H_Qw[ieta] = new TH1F(name,name, 100, 0, 1000 );    
    (void)sprintf(name,"H_EP_%d",ieta);
    H_EP[ieta] = new TH1F(name,name, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    (void)sprintf(name,"H_Qv_%d",ieta);
    H_Qv[ieta] = new TH1F(name,name, 100, 0, 10 );


    sprintf(name, "pQx_%i", ieta);
    sprintf(title, "Qx_%i before recentering. Centrality", ieta);
    pQx[ieta] = new TProfile(name, title, ncent, 0.5, ncent+0.5);//1..5; 6..10; etc

    sprintf(name, "pQy_%i", ieta);
    sprintf(title, "Qy_%i before recentering. Centrality", ieta);
    pQy[ieta] = new TProfile(name, title, ncent, 0.5, ncent+0.5);//1..5; 6..10; etc


    sprintf(name, "pCosNPsi_%i_rec", ieta);
    sprintf(title, "<cos(#Psi_{2#eta%i})> recentered; Centrality", ieta);
    pCosNPsi[ieta] = new TProfile(name, title, ncent, 0.5, ncent + 0.5); //1..5; 6..10; etc
    sprintf(name, "pSinNPsi_%i_rec", ieta);
    sprintf(title, "<sin(#Psi_{2#eta%i})> recentered; Centrality", ieta);
    pSinNPsi[ieta] = new TProfile(name, title, ncent, 0.5, ncent + 0.5); //1..5; 6..10; etc

    sprintf(name, "pFlatCos_%i", ieta);
    sprintf(title, "FlatCos%i. centrality", ieta);
    pFlatCos[ieta] = new TProfile(name, title, ncent, 0.5, ncent  + 0.5); //1..5; 6..10; etc

    sprintf(name, "pFlatSin_%i", ieta);
    sprintf(title, "FlatSin%i. centrality", ieta);
    pFlatSin[ieta] = new TProfile(name, title, ncent, 0.5, ncent + 0.5); //1..5; 6..10; etc

    sprintf(name, "hPsiRecentered_%i", ieta);
    sprintf(title, "Recentered #Psi_{2%i}", ieta);
    hPsiRecentered[ieta] = new TH1F(name, title, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );

    sprintf(name, "hPsiFlattened_%i", ieta);
    sprintf(title, "Flattened #Psi_{2%i}", ieta);
    hPsiFlattened[ieta] = new TH1F(name, title, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );

    // for (int icent=0; icent<ncent; icent++){
    //   sprintf(name, "hPsiRecentered_%i_%i", ieta, icent);
    //   sprintf(title, "Recentered #Psi_{2%i}. Cent%i", ieta, icent);
    //   hPsiRecentered[ieta][icent] = new TH1F(name, title, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    // }
  }

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    sprintf(name, "hv2MC_cent%i", icent);
    sprintf(title, "v_{2}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv2MC[icent] = new TProfile(name, title, 1, 0., 1.);
    hv2MC[icent]->Sumw2();

    (void)sprintf(name,"hv22EP_cent%i",icent);
    hv22EP[icent] = new TH1F(name,name, 400, -10, 10 );

    (void)sprintf(name,"HRes_cent%i",icent);
    HRes[icent] = new TH1F(name,name, 100, -10, 10 );

    for (int kpt = 0; kpt < npt; kpt++)
    { // loop over pt bin
      sprintf(name, "hPT_cent%i_pt%i", icent, kpt);
      sprintf(title, "p_{T} distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hPT[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hPT[icent][kpt]->Sumw2();

      (void)sprintf(name,"hv2EP_cent%i_pt%i",icent,kpt);
      hv2EP[icent][kpt] = new TH1F(name,name, 400, -10, 10 );

      sprintf(name, "hv2MCpt_cent%i_pt%i", icent, kpt);
      sprintf(title, "v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv2MCpt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv2MCpt[icent][kpt]->Sumw2();
    } // end of loop over pt bin
  } // end of loop over centrality classes



  cout << "Histograms have been initialized" << endl;
}

void CalibRes::Loop_a_file(TString file)
{
  TFile *treefile = TFile::Open(file.Data());
  TTree *tree = (TTree *)treefile->Get("htree");
  if (tree == 0)
  {
    cout << "htree is not found in " << file << endl;
    treefile->Close();
    return;
  }
  cout << file << " is opened" << endl;
  Init(tree);
  Recentering();
  FinishRecentering();
  Flattening();
  FinishFlattening();
  Loop();
  treefile->Close();
  cout << file << " file processed" << endl;
}

void CalibRes::Ana_end()
{
  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

void CalibRes::Loop()
{
  cout << "CalV2..." << endl;
  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  { // loop over all entries (nentries) of chain
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    Ana_event();
    if (ientry % 100000 == 0)
      cout << ientry << endl;
  }
}


void CalibRes::Recentering(){
  cout << "Recentering..." << endl;
  
  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  { // loop over all entries (nentries) of chain
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    Double_t sumQxy[ncent][neta][2]={{{0}}};    // [eta-,eta+][x,y]
    Double_t multQv[ncent][neta]={{0}};       // [eta+,eta-]    
    int icent = -1;
    for (int i = 0; i < ncent; i++)
    { // loop over centrality
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0)
      return;
    for (int i = 0; i < nh; i++)
    { // track loop
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[icent][fEta][0] += pt[i] * cos( 2.0 * phi0[i] );
        sumQxy[icent][fEta][1] += pt[i] * sin( 2.0 * phi0[i] );
        multQv[icent][fEta]++;
      } // end of eta selection

    } // end of track loop

    for (int ieta=0; ieta<neta; ieta++){
      if (sumQxy[icent][ieta][0]==0 && sumQxy[icent][ieta][1]==0) continue;
      pQx[ieta]->Fill(icent, sumQxy[icent][ieta][0]);
      pQy[ieta]->Fill(icent, sumQxy[icent][ieta][1]);
    }

    if (ientry % 100000 == 0)
      cout << ientry << endl;
  }
}
void CalibRes::FinishRecentering(){
  cout << "Finish Recentering..." << endl;
  for( int ieta=0; ieta<neta; ieta++ ){
    for (int icent=0; icent<ncent; icent++){
      qxMean[icent][ieta] = pQx[ieta]->GetBinContent(icent + 1);
      qyMean[icent][ieta] = pQy[ieta]->GetBinContent(icent + 1);
    }
  }
}
void CalibRes::Flattening(){
  cout << "Flattening..." << endl;
  
  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  { // loop over all entries (nentries) of chain
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    // if (Cut(ientry) < 0) continue;
 
    Double_t sumQxy[ncent][neta][2]={{{0}}};    // [eta-,eta+][x,y]
    Double_t multQv[ncent][neta]={{0}};       // [eta+,eta-]    
    int icent = -1;
    for (int i = 0; i < ncent; i++)
    { // loop over centrality
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0)
      return;

    for (int i = 0; i < nh; i++)
    { // track loop
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[icent][fEta][0] += pt[i] * cos( 2.0 * phi0[i] );
        sumQxy[icent][fEta][1] += pt[i] * sin( 2.0 * phi0[i] );
        multQv[icent][fEta]++;
      } // end of eta selection

    } // end of track loop

    Float_t qxRec, qyRec, psi2;
    for( int ieta=0; ieta<neta; ieta++ ){
      if (sumQxy[icent][ieta][0]==0 && sumQxy[icent][ieta][1]==0) continue;
      qxRec = sumQxy[icent][ieta][0] - qxMean[icent][ieta];
      qyRec = sumQxy[icent][ieta][1] - qyMean[icent][ieta];
      psi2 = TMath::ATan2(qyRec, qxRec) / 2.;
      
      pCosNPsi[ieta]->Fill(icent, TMath::Cos( 2. * psi2));
      pSinNPsi[ieta]->Fill(icent, TMath::Sin( 2. * psi2));

      // Fill Flattening profiles
      pFlatCos[ieta]->Fill(icent, TMath::Cos(4. * TMath::ATan2(qyRec, qxRec)));
      pFlatSin[ieta]->Fill(icent, TMath::Sin(4. * TMath::ATan2(qyRec, qxRec)));
    }

      if (ientry % 100000 == 0)
        cout << ientry << endl;
  } // end of loop over entries 
}
void CalibRes::FinishFlattening(){
  cout << "Finish Flattening..." << endl;
  ofstream ofile2("SumQxyMean.txt");
  Double_t mFlatCos, mFlatSin;
  for (int icent=0; icent<ncent; icent++){
    ofile2 << "cent =" << icent*10 <<"-"<< (icent+1)*10 <<"%"<<endl;
    for( int ieta=0; ieta<neta; ieta++ ){

      mFlatCos = pFlatCos[ieta]->GetBinContent(icent + 1);
      mFlatSin = pFlatSin[ieta]->GetBinContent(icent + 1);
      ofile2 << "eta = " << ieta << "; <cos(2npsi)> = " << mFlatCos << "; <sin(2npsi)> = " << mFlatSin << endl;
    }
  }
  cout << "Done Finish Flattening..." << endl;
}

void CalibRes::Ana_event()
{
  Double_t sumQxy[ncent][neta][2]={{{0}}};    // [eta-,eta+][x,y]
  Double_t multQv[ncent][neta]={{0}};       // [eta+,eta-]    

  int icent = -1;
  for (int i = 0; i < ncent; i++)
  { // loop over centrality
    if (CentB(b) == bin_cent[i])
      icent = i;
  }
  if (icent < 0)
    return;
  hMult->Fill(nh);
  hRP->Fill(rp);
  hBimp->Fill(b);
  hBimpvsMult->Fill(nh, b);


  for (int i = 0; i < nh; i++)
  { // track loop
    
    Float_t pT = pt[i];
    if (pT < minpt || pT > maxpt) continue; // pt cut
    hPt->Fill(pT);
    hPhi->Fill(phi0[i] - rp);
    hPhil->Fill(phi0[i]);
    hEta->Fill(eta[i]);

    Int_t ipt = 0;


    for (int j = 0; j < npt; j++)
    {
      if (pT >= bin_pT[j] && pT < bin_pT[j + 1])
        ipt = j;
    }

    if (bFlow[i]){ // Bool_t bFlow : flow particle flag
      Double_t v2 = TMath::Cos(2 * (phi0[i] - rp));
      // calculate reference v2 from MC toy
      if (eta[i] < -0.05) hv2MC[icent]->Fill(0.5, v2, 1);
      // Calculate differential v2 from MC toy
      hPT[icent][ipt]->Fill(0.5, pT, 1);
      hv2MCpt[icent][ipt]->Fill(0.5, v2, 1);
    }


    int fEta = -1;
    if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
    if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

		if ( fEta>-1 ){
      sumQxy[icent][fEta][0] += pT * cos( 2.0 * phi0[i] );
      sumQxy[icent][fEta][1] += pT * sin( 2.0 * phi0[i] );
			multQv[icent][fEta]++;
		} // end of eta selection

  } // end of track loop

  Double_t fEP[2]; // [eta-,eta+]
  Double_t fQv[2];
  for (int ieta=0; ieta<neta; ieta++){
    if( multQv[icent][ieta]>5 ){ // multiplicity > 5
      fEP[ieta] = TMath::ATan2(sumQxy[icent][ieta][1]-qyMean[icent][ieta], sumQxy[icent][ieta][0]- qxMean[icent][ieta]) / 2.0;
      // fEP[ieta] = TMath::ATan2( sin( 2.0*fEP[ieta] ), cos( 2.0*fEP[ieta] ) ); // what for?
      // fEP[ieta] /= 2.0;
      hPsiRecentered[ieta] -> Fill(fEP[ieta]);
      fEP[ieta] = fEP[ieta] + 0.5*(-(pFlatSin[ieta]->GetBinContent(icent + 1)) * cos(4.*fEP[ieta]) + (pFlatCos[ieta]->GetBinContent(icent + 1)) * sin(4.*fEP[ieta]));
      hPsiFlattened[ieta] -> Fill(fEP[ieta]);
      fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[icent][ieta][0],2.0)+TMath::Power( sumQxy[icent][ieta][1],2.0))/TMath::Sqrt(multQv[icent][ieta]);
      H_Qw[ieta]->Fill( multQv[icent][ieta] );

    }else{
      fEP[ieta] = -9999;
      fQv[ieta] = -9999;
    }
  }

  for( int ieta=0; ieta<neta; ieta++ ){// eta EP detector loop
    if( fEP[ieta]>-9000 ){ // EP reconstructed 
      H_EP[ieta]->Fill( fEP[ieta] );
      H_Qv[ieta]->Fill( fQv[ieta] );
    }// end of EP reconstructed
  }// end of eta loop

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
  HRes[icent] -> Fill( cos(dPsi) );

	// float res2[ncent]={0.377939,0.517293,0.570174,0.566116,0.520478,0.449174,0.355887,0.263176}; // pure flow
  // float res2[ncent]={0.333508,0.455988,0.501837,0.506404,0.454911,0.39287,0.304219,0.231337}; // my nonflow 10 mil
  float res2[ncent]={0.95393,0.399415,0.879517,0.459384,0.747582,0.671661,0.534138,0.452148}; // with acceptance effect


  // The \eta sub-event method
	if(icent>=0&&icent<=7){ // centrality selection 0-80%
    for(int itrk=0;itrk<nh;itrk++) {  //track loop
      Double_t pT = pt[itrk];
      if( pT<minpt || pT>maxpt ) continue;

      Int_t ipt = 0;
      for (int j = 0; j < npt; j++)
      {
        if (pT >= bin_pT[j] && pT < bin_pT[j + 1])
          ipt = j;
      }

      float v2=-999.0;
      
      if(eta[itrk]>0){ // eta+
        v2 = cos(2.0 * (phi0[itrk]-psi1) )/res2[icent];
      }

      if(eta[itrk]<0){ // eta-
        v2 = cos(2.0 * (phi0[itrk]-psi2) )/res2[icent];
      }
      // if(fabs(eta[itrk])<1.0){ // eliminate spectators
      hv2EP[icent][ipt]->Fill(v2);
      if (eta[itrk] < -0.05) { // Reference flow
        hv22EP[icent]->Fill(v2);
      }
      
      // } // end of |eta| < 1.0
    }// end of the track loop
 	}// end of centrality selection 

}
/*
void loop_a_list_of_trees()
{
  CalibRes *ana = new CalibRes();
  ana->Booking("/weekly/nikolaev/lbavinh/EventPlane/OUT/res2.root");
  ana->Loop_a_file("/weekly/nikolaev/lbavinh/Generator/v2hadron.root");
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
*/
void loop_a_list_of_trees()
{
  CalibRes *ana = new CalibRes();
  ana->Booking("/weekly/nikolaev/lbavinh/EventPlane/OUT/res2_nonflow.root");
  ana->Loop_a_file("/weekly/nikolaev/lbavinh/Generator/v2hadron_nonflow.root");
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}