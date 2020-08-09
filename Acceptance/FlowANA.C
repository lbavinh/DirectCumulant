#define FlowANA_cxx
#include "FlowANA.h"
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
static const int max_nh = 5100;
static const double maxpt = 3.5; // max pt
static const double minpt = 0.2; // min pt
static const int npt = 12;        // 0.2 - 3.5 GeV/c
static const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2,
                                      1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
static const int neta = 2; // [eta-,eta+]
static const int nharm = 10; // v2,v3,...,v6
TFile *d_outfile; // out file with histograms and profiles

TH1F *hRP;         // reaction plane distr
TH1F *hPt;         // transverse momentum distr
TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta;        // pseudorapidity
TH1F *hBimp;       // impact parameter
TH1I *hMult;       // emitted multiplicity
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

// ================= Eta sub-event ================= //

TH1F *H_Qw[ncent][neta];
TH1F *H_EP[ncent][neta];				// reaction plane (raw - without recentering & flattening)
TH1F *H_Qv[ncent][neta];
TH1F *HRes[ncent];		          // resolution

TProfile *pQx[neta];            // <Qx>
TProfile *pQy[neta];            // <Qy>
TProfile *pCosNPsi[neta][nharm];
TProfile *pSinNPsi[neta][nharm];

TH1F *hPsiRecentered[ncent][neta];
TH1F *hPsiFlattened[ncent][neta];

Double_t qxMean[ncent][neta];   // <Qx>
Double_t qyMean[ncent][neta];   // <Qy>
float res2[ncent]={0};  // Resolution Psi2

TProfile *hv2EP[npt];	   // elliptic flow from EP method
TProfile *hv22EP;        // integrated elliptic flow from EP method (eta<-0.05)

// ================= Direct cumulants ================= //

// TProfile for reference flow (RF)
TProfile *hv2MC[ncent]; // profile for MC integrated v2
TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
// TProfile for differential flow (DF)
TProfile *hPT[npt];     // profile pt
TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
TProfile *hv22pt[ncent][npt];  // profile <<2'>> from 2nd Q-Cumulants
TProfile *hv24pt[ncent][npt];  // profile <<4'>> from 4th Q-Cumulants

// TProfile for covariance calculation according to (C.12), Appendix C
// in Bilandzic, A. (2012)
// Anisotropic flow measurements in ALICE at the large hadron collider.
TProfile *hcov24[ncent];                // <2>*<4>
TProfile *hcov22prime[ncent][npt];      // <2>*<2'>
TProfile *hcov24prime[ncent][npt];      // <2>*<4'>
TProfile *hcov42prime[ncent][npt];      // <2>*<4'>
TProfile *hcov44prime[ncent][npt];      // <4>*<4'>
TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

// non-uniform acceptance correction
// Reference flow acceptance correction
TProfile *hcos2phi1, *hsin2phi1, *hcos2phi12, *hsin2phi12, *hcos2phi123, *hsin2phi123;

// Differential flow acceptance correction
TProfile *hcos2psi1[npt], *hsin2psi1[npt], *hcos2psi1phi2[npt], *hsin2psi1phi2[npt],
         *hcos2psi1pphi23[npt], *hsin2psi1pphi23[npt], *hcos2psi1mphi23[npt], *hsin2psi1mphi23[npt];

void FlowANA::Booking(TString outFile)
{
  char name[800];
  char title[800];
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << "Output file \"" << outFile.Data() << "\" has been initialized" << endl;

  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);

  // Acceptance correction
  hcos2phi1 = new TProfile("hcos2phi1","hcos2phi1",ncent,0.,ncent);
  hcos2phi1 ->Sumw2();
  hsin2phi1 = new TProfile("hsin2phi1","hsin2phi1",ncent,0.,ncent);
  hsin2phi1 ->Sumw2();
  hcos2phi12 = new TProfile("hcos2phi12","hcos2phi12",ncent,0.,ncent);
  hcos2phi12 ->Sumw2();
  hsin2phi12 = new TProfile("hsin2phi12","hsin2phi12",ncent,0.,ncent);
  hsin2phi12 ->Sumw2();
  hcos2phi123 = new TProfile("hcos2phi123","hcos2phi123",ncent,0.,ncent);
  hcos2phi123 ->Sumw2();
  hsin2phi123 = new TProfile("hsin2phi123","hsin2phi123",ncent,0.,ncent);
  hsin2phi123 ->Sumw2();
  hv22EP = new TProfile("hv22EP","Ref. v_{2}{EP}", ncent,0.,ncent);
  hv22EP->Sumw2();

  for( int ieta=0; ieta<neta; ieta++ ){
    sprintf(name, "pQx_%i", ieta);
    sprintf(title, "Qx_%i before recentering. Centrality", ieta);
    pQx[ieta] = new TProfile(name, title, ncent, 0.5, ncent+0.5);

    sprintf(name, "pQy_%i", ieta);
    sprintf(title, "Qy_%i before recentering. Centrality", ieta);
    pQy[ieta] = new TProfile(name, title, ncent,0.,ncent);


    for (int iharm=0; iharm<nharm; iharm++){
      sprintf(name, "pCosNPsi_%i_%i_rec", ieta,iharm);
      sprintf(title, "<cos(2n#Psi_{2#eta%i})> recentered, harm_%i", ieta,iharm);
      pCosNPsi[ieta][iharm] = new TProfile(name, title, ncent,0.,ncent);

      sprintf(name, "pSinNPsi_%i_%i_rec", ieta,iharm);
      sprintf(title, "<sin(2n#Psi_{2#eta%i})> recentered, harm_%i", ieta,iharm);
      pSinNPsi[ieta][iharm] = new TProfile(name, title, ncent,0.,ncent);
    }
    for (int icent=0;icent<ncent;icent++){
      sprintf(name,"H_Qw_%i_%i",icent,ieta);
      H_Qw[icent][ieta] = new TH1F(name,name, 100, 0, 1000 );

      sprintf(name,"H_EP_%i_%i",icent,ieta);
      H_EP[icent][ieta] = new TH1F(name,name, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );

      sprintf(name,"H_Qv_%i_%i",icent,ieta);
      H_Qv[icent][ieta] = new TH1F(name,name, 100, 0, 10 );

      sprintf(name, "hPsiRecentered_%i_%i",icent,ieta);
      sprintf(title, "Recentered #Psi_{2%i}, cent%i-%i",ieta,icent*10,(icent+1)*10);
      hPsiRecentered[icent][ieta] = new TH1F(name, title, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );

      sprintf(name, "hPsiFlattened_%i_%i",icent,ieta);
      sprintf(title, "Flattened #Psi_{2%i}, cent%i-%i",ieta,icent*10,(icent+1)*10);
      hPsiFlattened[icent][ieta] = new TH1F(name, title, 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );

    }
  }

  for (int ipt=0;ipt<npt;ipt++){

    sprintf(name, "hPT_%i", ipt);
    sprintf(title, "p_{T} distr, %2.1f<pt<%2.1f GeV/c", bin_pT[ipt], bin_pT[ipt + 1]);
    hPT[ipt] = new TProfile(name, title, 1, 0., 1.);
    hPT[ipt]->Sumw2();

    sprintf(name, "hcos2psi1_%i", ipt);
    hcos2psi1[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hcos2psi1[ipt] -> Sumw2();

    sprintf(name, "hsin2psi1_%i", ipt);
    hsin2psi1[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hsin2psi1[ipt] -> Sumw2();

    sprintf(name, "hcos2psi1phi2_%i", ipt);
    hcos2psi1phi2[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hcos2psi1phi2[ipt] -> Sumw2();

    sprintf(name, "hsin2psi1phi2_%i", ipt);
    hsin2psi1phi2[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hsin2psi1phi2[ipt] -> Sumw2();

    sprintf(name, "hcos2psi1pphi23_%i", ipt);
    hcos2psi1pphi23[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hcos2psi1pphi23[ipt] -> Sumw2();

    sprintf(name, "hsin2psi1pphi23_%i", ipt);
    hsin2psi1pphi23[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hsin2psi1pphi23[ipt] -> Sumw2();

    sprintf(name, "hcos2psi1mphi23_%i", ipt);
    hcos2psi1mphi23[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hcos2psi1mphi23[ipt] -> Sumw2();

    sprintf(name, "hsin2psi1mphi23_%i", ipt);
    hsin2psi1mphi23[ipt] = new TProfile(name,name,ncent,0.,ncent);
    hsin2psi1mphi23[ipt] -> Sumw2();

    sprintf(name,"hv2EP_%i",ipt);
    hv2EP[ipt] = new TProfile(name,name, ncent,0.,ncent);
    hv2EP[ipt]->Sumw2();
  }

  for (int icent=0;icent<ncent;icent++){

    sprintf(name,"HRes_cent%i",icent);
    HRes[icent] = new TH1F(name,name, 100, -10, 10 );

    sprintf(name, "hv2MC_%i", icent);
    hv2MC[icent] = new TProfile(name, name, 1, 0., 1.);
    hv2MC[icent]->Sumw2();

    sprintf(name, "hv22_%i", icent);
    hv22[icent] = new TProfile(name, name, 1, 0., 1.);
    hv22[icent]->Sumw2();

    sprintf(name, "hv24_%i", icent);
    hv24[icent] = new TProfile(name, name, 1, 0., 1.);
    hv24[icent]->Sumw2();

    sprintf(name, "hcov24_%i", icent);
    hcov24[icent] = new TProfile(name, name, 1, 0., 1.);
    hcov24[icent]->Sumw2();

    for (int ipt=0;ipt<npt;ipt++){
      sprintf(name, "hv2MCpt_%i_%i", icent, ipt);
      hv2MCpt[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hv2MCpt[icent][ipt]->Sumw2();

      sprintf(name, "hv22pt_%i_%i", icent, ipt);
      hv22pt[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hv22pt[icent][ipt]->Sumw2();

      sprintf(name, "hv24pt_%i_%i", icent, ipt);
      hv24pt[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hv24pt[icent][ipt]->Sumw2();

      sprintf(name, "hcov22prime_%i_%i", icent, ipt);
      hcov22prime[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hcov22prime[icent][ipt]->Sumw2();

      sprintf(name, "hcov24prime_%i_%i", icent, ipt);
      hcov24prime[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hcov24prime[icent][ipt]->Sumw2();

      sprintf(name, "hcov42prime_%i_%i", icent, ipt);
      hcov42prime[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hcov42prime[icent][ipt]->Sumw2();

      sprintf(name, "hcov44prime_%i_%i", icent, ipt);
      hcov44prime[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hcov44prime[icent][ipt]->Sumw2();

      sprintf(name, "hcov2prime4prime_%i_%i", icent, ipt);
      hcov2prime4prime[icent][ipt] = new TProfile(name, name, 1, 0., 1.);
      hcov2prime4prime[icent][ipt]->Sumw2();
    }
  }
  cout << "Histograms have been initialized" << endl;
}

void FlowANA::Loop_a_file(TString file)
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
  Resolution();
  FinishResolution();
  CalFlow();
  treefile->Close();
  cout <<"File \"" << file << "\" is processed" << endl;
}

void FlowANA::Ana_end()
{
  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

void FlowANA::Recentering(){
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
    if (ientry % 100000 == 0) cout << ientry << endl;    
    // if (Cut(ientry) < 0) continue;
    Double_t sumQxy[neta][2]={{0}};    // [eta-,eta+][x,y]
    Double_t multQv[neta]={0};         // [eta+,eta-]    
    int icent = -1;
    for (int i = 0; i < ncent; i++)
    {
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0) continue;
    for (int i = 0; i < nh; i++)
    { // track loop
      if( pt[i]<minpt  || pt[i]>maxpt ) continue;
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pt[i] * cos( 2.0 * phi0[i] );
        sumQxy[fEta][1] += pt[i] * sin( 2.0 * phi0[i] );
        multQv[fEta]++;
      } // end of eta selection

    } // end of track loop

    for (int ieta=0; ieta<neta; ieta++){
      if (sumQxy[ieta][0]==0 && sumQxy[ieta][1]==0) continue;
      pQx[ieta]->Fill(0.5+icent, sumQxy[ieta][0]);
      pQy[ieta]->Fill(0.5+icent, sumQxy[ieta][1]);
    }
  }
}
void FlowANA::FinishRecentering(){
  cout << "Finish Recentering..." << endl;
  for( int ieta=0; ieta<neta; ieta++ ){
    for (int icent=0; icent<ncent; icent++){
      qxMean[icent][ieta] = pQx[ieta]->GetBinContent(icent + 1);
      qyMean[icent][ieta] = pQy[ieta]->GetBinContent(icent + 1);
    }
  }
}
void FlowANA::Flattening(){
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
    if (ientry % 100000 == 0) cout << ientry << endl;
    // if (Cut(ientry) < 0) continue;
 
    Double_t sumQxy[neta][2]={{0}};    // [eta-,eta+][x,y]
    Double_t multQv[neta]={0};         // [eta+,eta-]    
    int icent = -1;
    for (int i = 0; i < ncent; i++)
    { // loop over centrality
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0) continue;
    for (int i = 0; i < nh; i++)
    { // track loop
      if( pt[i]<minpt  || pt[i]>maxpt ) continue;
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pt[i] * cos( 2.0 * phi0[i] );
        sumQxy[fEta][1] += pt[i] * sin( 2.0 * phi0[i] );
        multQv[fEta]++;
      } // end of eta selection

    } // end of track loop

    double qxRec, qyRec, psi2;
    for( int ieta=0; ieta<neta; ieta++ ){
      if (sumQxy[ieta][0]==0 && sumQxy[ieta][1]==0) continue;
      qxRec = sumQxy[ieta][0] - qxMean[icent][ieta];
      qyRec = sumQxy[ieta][1] - qyMean[icent][ieta];
      psi2 = TMath::ATan2(qyRec, qxRec) / 2.;

      // Fill Flattening profiles

      for (int iharm=0;iharm<nharm;iharm++){
        pCosNPsi[ieta][iharm]->Fill(0.5+icent, TMath::Cos( 2*(iharm+2)*psi2));
        pSinNPsi[ieta][iharm]->Fill(0.5+icent, TMath::Sin( 2*(iharm+2)*psi2));

        // pCosNPsi[ieta][iharm]->Fill(0.5+icent, TMath::Cos( (iharm+2)*psi2));
        // pSinNPsi[ieta][iharm]->Fill(0.5+icent, TMath::Sin( (iharm+2)*psi2));        
      }
    }

  } // end of loop over entries 
}
void FlowANA::FinishFlattening(){}

void FlowANA::Resolution()
{
  cout << "Calculating resolution..." << endl;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  { // loop over all entries (nentries) of chain
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if (ientry % 100000 == 0)
      cout << ientry << endl; // event counter

    Double_t sumQxy[neta][2]={{0}};    // [eta-,eta+][x,y]
    Double_t multQv[neta]={0};         // [eta+,eta-]    

    int icent = -1;
    for (int i = 0; i < ncent; i++)
    { // loop over centrality
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0) continue;
    for (int i = 0; i < nh; i++)
    { // track loop
      double pT = pt[i];
      if (pT < minpt || pT > maxpt) continue; // pt cut
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pT * cos( 2.0 * phi0[i] );
        sumQxy[fEta][1] += pT * sin( 2.0 * phi0[i] );
        multQv[fEta]++;
      } // end of eta selection

    } // end of track loop

    Double_t fEP[2]={0}, fEPRaw[2]={0}; // [eta-,eta+]
    Double_t fQv[2]={0};
    Double_t cosNPhiMean=0, sinNPhiMean=0;
    Double_t psi2Rec=0; // Psi_2 (recentered)
    Double_t psi2Flat=0;
    
    for (int ieta=0; ieta<neta; ieta++){
      if( multQv[ieta]>5 ){ // multiplicity > 5
        
        // Raw
        H_Qw[icent][ieta]->Fill( multQv[ieta] );

        fEPRaw[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
        H_EP[icent][ieta]->Fill( fEPRaw[ieta] );

        fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0],2.0)+TMath::Power( sumQxy[ieta][1],2.0))/TMath::Sqrt(multQv[ieta]);
        H_Qv[icent][ieta]->Fill( fQv[ieta] );

        // Recentering
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1]-qyMean[icent][ieta], sumQxy[ieta][0]- qxMean[icent][ieta]) / 2.0;
        fEP[ieta] = TMath::ATan2( sin( 2.0*fEP[ieta] ), cos( 2.0*fEP[ieta] ) );
        fEP[ieta] /= 2.0;
        psi2Rec = fEP[ieta];
        hPsiRecentered[icent][ieta] -> Fill(fEP[ieta]);
        Double_t dPsi=0;
        // Flattening
        // L. Adamczyk et al. (STAR Collaboration). Phys. Rev. C 86, 054908 (2012)
        // formula (15)
        for (int iharm=0;iharm<nharm;iharm++){
          cosNPhiMean = pCosNPsi[ieta][iharm] -> GetBinContent(icent+1);
          sinNPhiMean = pSinNPsi[ieta][iharm] -> GetBinContent(icent+1);
          dPsi += 1./(iharm+2) * (-sinNPhiMean*cos(2*(iharm+2)*psi2Rec) + cosNPhiMean*sin(2*(iharm+2)*psi2Rec));

          // dPsi += 2./(iharm+2) * (-sinNPhiMean*cos((iharm+2)*psi2Rec) + cosNPhiMean*sin((iharm+2)*psi2Rec));
        }
        psi2Flat = psi2Rec + dPsi;
        fEP[ieta] = psi2Flat;
        hPsiFlattened[icent][ieta] -> Fill(psi2Flat);
      }else{
        fEP[ieta] = -9999;
        fQv[ieta] = -9999;
      }
    }

    // Resolution
    Double_t psi1, psi2, fq1, fq2;
    psi1 = fEP[0];
    psi2 = fEP[1];
    // fq1 = fQv[0];
    // fq2 = fQv[1];
    if (psi1<-9000 || psi2<-9000) continue;
    // if (fq1<0 || fq2<0) continue;
    Double_t dPsi = 2. *(psi1 - psi2);
    dPsi = TMath::ATan2( sin(dPsi) , cos(dPsi));
    HRes[icent] -> Fill( cos(dPsi) );
  }
}
void FlowANA::FinishResolution(){
  cout << "Resolution psi2 = {";
  for (int icent=0; icent<ncent; icent++){
    res2[icent] = TMath::Sqrt(HRes[icent]->GetMean());
    cout << res2[icent] <<", ";
  }
  cout << "}" <<endl;
}



void FlowANA::CalFlow(){
  cout << "CalV2..." << endl;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  { // loop over all entries (nentries) of chain
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if (ientry % 100000 == 0) cout << ientry << endl; // event counter

    // ==================== Analysis ==================== //
    
    int icent = -1;
    for (int i = 0; i < ncent; i++)
    { // loop over centrality
      if (CentB(b) == bin_cent[i])
        icent = i;
    }
    if (icent < 0) continue;
    hMult->Fill(nh);
    hRP->Fill(rp);
    hBimp->Fill(b);
    hBimpvsMult->Fill(nh, b);

    // ================= Direct cumulants ================= //

    // Q-vector of RFP
    Double_t Qx2 = 0., Qy2 = 0., Qx4 = 0., Qy4 = 0.;
    TComplex Q2 = 0., Q4 = 0.;
    // p-vector of POI
    Double_t px2[npt] = {0.}, py2[npt] = {0.};
    TComplex p2[npt] = {0.}, p4[npt] = {0.}, q2[npt] = {0.}, q4[npt] = {0.};
    // q-vector of particles marked as POI and RFP, which is used for
    // autocorrelation substraction
    Double_t qx2[npt] = {0.}, qy2[npt] = {0.}, qx4[npt] = {0.}, qy4[npt] = {0.};
    // Total number of RFP in given event
    Double_t M = 0.;
    // numbers of POI (mp) and particles marked both POI and RFP (mq)
    Double_t mq[npt] = {0.}, mp[npt] = {0.};
    // average reduced single-event 2- and 4-particle correlations : <2'> & <4'>
    Double_t redCor22[npt] = {0.}, redCor24[npt] = {0.};
    // event weights for correlation calculation
    Double_t w2 = 0., w4 = 0.;
    // event weights for reduced correlation calculation
    Double_t wred2[npt] = {0.}, wred4[npt] = {0.};
    // Average single-event 2- and 4- particle correlations : <2> & <4>
    Double_t cor22 = 0., cor24 = 0.;

    Double_t sumQxy[neta][2]={{0}};  // [eta-,eta+][x,y]
    Double_t multQv[neta]={0};       // [eta+,eta-]  

    for (int i = 0; i < nh; i++)
    { // track loop
      double pT = pt[i];
      if (pT < minpt || pT > maxpt) continue; // pt cut
      hPt->Fill(pT);
      double phi = phi0[i] - rp;
      if (phi<0) phi += 2.*TMath::Pi();
      hPhi->Fill(phi);
      hPhil->Fill(phi0[i]);
      hEta->Fill(eta[i]);
      Int_t ipt = 0;
      for (int j = 0; j < npt; j++){
        if (pT >= bin_pT[j] && pT < bin_pT[j + 1]) ipt = j;
      }
      // ======================= MC ======================= //
      if (bFlow[i]){ // Bool_t bFlow : flow particle flag
        Double_t v2 = TMath::Cos(2 * (phi0[i] - rp));
        // calculate reference v2 from MC toy
        if (eta[i] < -0.05) hv2MC[icent]->Fill(0.5, v2, 1);
        // Calculate differential v2 from MC toy
        hPT[ipt]->Fill(0.5+icent, pT, 1);
        hv2MCpt[icent][ipt]->Fill(0.5, v2, 1);
      }
      // ================= Direct cumulants ================= //
      // RFP
      if (eta[i] < -0.05)
      {
        Qx2 += TMath::Cos(2. * phi0[i]);
        Qy2 += TMath::Sin(2. * phi0[i]);
        Qx4 += TMath::Cos(4. * phi0[i]);
        Qy4 += TMath::Sin(4. * phi0[i]);   
        M++;
      }
      // POI
      if (eta[i] > 0.05)
      {
        px2[ipt] += TMath::Cos(2. * phi0[i]);
        py2[ipt] += TMath::Sin(2. * phi0[i]); 
        mp[ipt]++;
      }
      // ================= Eta sub-event ================= //
      int fEta = -1;
      if (eta[i] <-0.05 && eta[i] >-2.0) fEta = 0;
      if (eta[i] > 0.05 && eta[i] < 2.0) fEta = 1;
      if ( fEta>-1 ){
        sumQxy[fEta][0] += pT * cos( 2.0 * phi0[i] );
        sumQxy[fEta][1] += pT * sin( 2.0 * phi0[i] );
        multQv[fEta]++;
      } // end of eta selection
    } // end of track loop

    Double_t fEP[2]={0}; // [eta-,eta+]
    // Double_t fQv[2]={0};
    Double_t cosNPhiMean=0, sinNPhiMean=0;
    Double_t psi2Rec=0; // Psi_2 (recentered)
    Double_t psi2Flat=0;
    
    for (int ieta=0; ieta<neta; ieta++){
      if( multQv[ieta]>5 ){ // multiplicity > 5
        // fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0],2.0)+TMath::Power( sumQxy[ieta][1],2.0))/TMath::Sqrt(multQv[ieta]);
        // Recentering
        fEP[ieta] = TMath::ATan2(sumQxy[ieta][1]-qyMean[icent][ieta], sumQxy[ieta][0]- qxMean[icent][ieta]) / 2.0;
        fEP[ieta] = TMath::ATan2( sin( 2.0*fEP[ieta] ), cos( 2.0*fEP[ieta] ) );
        fEP[ieta] /= 2.0;
        psi2Rec = fEP[ieta];

        Double_t dPsi=0;
        // Flattening
        // L. Adamczyk et al. (STAR Collaboration). Phys. Rev. C 86, 054908 (2012)
        // formula (15)
        for (int iharm=0;iharm<nharm;iharm++){
          cosNPhiMean = pCosNPsi[ieta][iharm] -> GetBinContent(icent+1);
          sinNPhiMean = pSinNPsi[ieta][iharm] -> GetBinContent(icent+1);
          dPsi += 1./(iharm+2) * (-sinNPhiMean*cos(2*(iharm+2)*psi2Rec) + cosNPhiMean*sin(2*(iharm+2)*psi2Rec));

          // dPsi += 2./(iharm+2) * (-sinNPhiMean*cos((iharm+2)*psi2Rec) + cosNPhiMean*sin((iharm+2)*psi2Rec));
        }
        psi2Flat = psi2Rec + dPsi;
        fEP[ieta] = psi2Flat;

      }else{
        fEP[ieta] = -9999;
        // fQv[ieta] = -9999;
      }
    }
    Double_t psi1, psi2, fq1, fq2;
    psi1 = fEP[0];
    psi2 = fEP[1];
    // fq1 = fQv[0];
    // fq2 = fQv[1];
    if (psi1<-9000 || psi2<-9000) continue;
    // if (fq1<0 || fq2<0) continue;
    if (psi1<0) psi1 += 2.*TMath::Pi();
    if (psi1<0) psi2 += 2.*TMath::Pi();
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
        hv2EP[ipt]->Fill(0.5+icent,v2);
        if (eta[itrk] < -0.05) { // Reference flow
          hv22EP->Fill(0.5+icent,v2);
        }
        
        // } // end of |eta| < 1.0
      }// end of the track loop
    }// end of centrality selection


    // ================= Direct cumulants ================= //
    
    if (M >= 2.)
    { // <2> definition condition
      Q2 = TComplex(Qx2, Qy2);
      w2 = M * (M - 1.);                 // w(<2>)
      cor22 = CalCor22(Q2, M, w2);       // <2>
      hv22[icent]->Fill(0.5, cor22, w2); // <<2>>

      // Non-uniform acceptance correction
      hcos2phi1 -> Fill(0.5+icent,Qx2/M,M);
      hsin2phi1 -> Fill(0.5+icent,Qy2/M,M);
    } // end of <2> definition condition
    for (int ipt = 0; ipt < npt; ipt++)
    {
      if (mp[ipt] == 0 || M < 1)
        continue;

      p2[ipt] = TComplex(px2[ipt], py2[ipt]);
      q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
      wred2[ipt] = mp[ipt] * M - mq[ipt];                                        // w(<2'>)
      redCor22[ipt] = CalRedCor22(Q2, p2[ipt], M, mp[ipt], mq[ipt], wred2[ipt]); // <2'>
      hv22pt[icent][ipt]->Fill(0.5, redCor22[ipt], wred2[ipt]);                  // <<2'>>

      // TProfile for covariance calculation in statistic error
      hcov22prime[icent][ipt]->Fill(0.5, cor22 * redCor22[ipt], w2 * wred2[ipt]); // <2>*<2'>

      // Non-uniform acceptance correction
      hcos2psi1[ipt] -> Fill(0.5+icent,px2[ipt]/mp[ipt],mp[ipt]);
      hsin2psi1[ipt] -> Fill(0.5+icent,py2[ipt]/mp[ipt],mp[ipt]);
    }

    if (M >= 4.)
    { // <4> definition condition
      Q4 = TComplex(Qx4, Qy4);
      w4 = M * (M - 1.) * (M - 2.) * (M - 3.);  // w(<4>)
      cor24 = CalCor24(Q2, Q4, M, w4);          // <4>
      hv24[icent]->Fill(0.5, cor24, w4);        // <<4>>

      // TProfile for covariance calculation in statistic error
      hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>

      // Non-uniform acceptance correction
      Double_t cos2phi12=(Q2 * Q2 - Q4).Re();
      Double_t sin2phi12=(Q2 * Q2 - Q4).Im();
      Double_t cos2phi123=((Q2 * Qstar(Q2) * Qstar(Q2) - Q2 * Qstar(Q4)).Re()) - 2. * (M - 1.) * (Qstar(Q2).Re());
      Double_t sin2phi123=((Q2 * Qstar(Q2) * Qstar(Q2) - Q2 * Qstar(Q4)).Im()) - 2. * (M - 1.) * (Qstar(Q2).Im());
      Double_t sumMMm1=M*(M-1);
      Double_t sumMMm1Mm2=M*(M-1)*(M-2);
      hcos2phi12  -> Fill( 0.5+icent, cos2phi12/sumMMm1, sumMMm1);
      hsin2phi12  -> Fill( 0.5+icent, sin2phi12/sumMMm1, sumMMm1);
      hcos2phi123 -> Fill( 0.5+icent, cos2phi123/sumMMm1Mm2, sumMMm1Mm2);
      hsin2phi123 -> Fill( 0.5+icent, sin2phi123/sumMMm1Mm2, sumMMm1Mm2);
    } // end of <4> definition condition
    for (int ipt = 0; ipt < npt; ipt++)
    {
      if (mp[ipt] == 0 || M < 3)
        continue;
      q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
      wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);                                 // w(<4'>)
      redCor24[ipt] = CalRedCor24(Q2, Q4, p2[ipt], q2[ipt], q4[ipt], M, mp[ipt], mq[ipt], wred4[ipt]);  // <4'>
      hv24pt[icent][ipt]->Fill(0.5, redCor24[ipt], wred4[ipt]);                                          // <<4'>>

      // TProfile for covariance calculation in statistic error
      hcov24prime[icent][ipt]->Fill(0.5, cor22 * redCor24[ipt], w2 * wred4[ipt]);
      hcov42prime[icent][ipt]->Fill(0.5, cor24 * redCor22[ipt], w4 * wred2[ipt]);
      hcov44prime[icent][ipt]->Fill(0.5, cor24 * redCor24[ipt], w4 * wred4[ipt]);
      hcov2prime4prime[icent][ipt]->Fill(0.5, redCor22[ipt] * redCor24[ipt], wred2[ipt] * wred4[ipt]);

      // Non-uniform acceptance correction
      hcos2psi1phi2[ipt] -> Fill(0.5+icent,(p2[ipt] * Q2 - q4[ipt]).Re()/(mp[ipt]*M-mq[ipt]),(mp[ipt]*M-mq[ipt]));
      hsin2psi1phi2[ipt] -> Fill(0.5+icent,(p2[ipt] * Q2 - q4[ipt]).Im()/(mp[ipt]*M-mq[ipt]),(mp[ipt]*M-mq[ipt]));
      hcos2psi1pphi23[ipt] -> Fill(0.5+icent,(((p2[ipt]*(Q2.Rho2()-M)).Re())-((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Re()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),(mp[ipt]*M-2*mq[ipt])*(M-1));
      hsin2psi1pphi23[ipt] -> Fill(0.5+icent,(((p2[ipt]*(Q2.Rho2()-M)).Im())-((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Im()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),(mp[ipt]*M-2*mq[ipt])*(M-1));
      hcos2psi1mphi23[ipt] -> Fill(0.5+icent,(((p2[ipt] * Qstar(Q2) * Qstar(Q2) - p2[ipt] * Qstar(Q4)).Re()) - ((2. * mq[ipt] * Qstar(Q2) - 2. * Qstar(q2[ipt])).Re()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),((mp[ipt]*M-2*mq[ipt])*(M-1)));
      hsin2psi1mphi23[ipt] -> Fill(0.5+icent,(((p2[ipt] * Qstar(Q2) * Qstar(Q2) - p2[ipt] * Qstar(Q4)).Im()) - ((2. * mq[ipt] * Qstar(Q2) - 2. * Qstar(q2[ipt])).Im()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),((mp[ipt]*M-2*mq[ipt])*(M-1)));
    }
  } // end of loop over event
} // end of FlowANA::CalFlow()

void loop_a_list_of_trees()
{
  FlowANA *ana = new FlowANA();
  ana->Booking("./ROOTFile/acceptance_test.root");
  ana->Loop_a_file("acc.root");
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}