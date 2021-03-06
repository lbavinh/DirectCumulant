#define FlowANA_cxx
#include "FlowANA.h"
#include "function.C"
#include "TH1.h"
#include "TH1I.h"
#include "TH2.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TRandom3.h"
#include <TDatabasePDG.h>
#include <TVector3.h>
#include <TStopwatch.h>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//List of histograms and Ntuples....

// static const int neta = 7;
// static const int ndet = 3;
// static const int ncent = 6;
// static const int nth = 3;
static const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-



static const int ncent = 8; // 0-80%
static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};

static const double maxpt = 3.; // max pt
static const double minpt = 0.2; // min pt

static const float eta_cut =  1.5; // min pt
static const float eta_gap = 0.05; // min pt

static const int neta = 2; // [eta-,eta+]

// static const int max_nh = 1700;

TFile *d_outfile; // out file with histograms and profiles
TH1I *hEvt;        // Event number 
TH1F *hRP;         // reaction plane distr
TH1F *hPt;         // transverse momentum distr
TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta;        // pseudorapidity
TH1F *hBimp;       // impact parameter
TH1I *hMult;       // emitted multiplicity
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

// TProfile for reference flow (RF)
// TProfile *hv2MC[ncent][npid]; // profile for MC integrated v2
TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
// TProfile for differential flow (DF)
TProfile *hPT[ncent][npt][npid];     // profile pt
// TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
TProfile *hv22pt[ncent][npt][npid];  // profile <<2'>> from 2nd Q-Cumulants
TProfile *hv24pt[ncent][npt][npid];  // profile <<4'>> from 4th Q-Cumulants

// TProfile for covariance calculation according to (C.12), Appendix C
// in Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider.
TProfile *hcov24[ncent];                // <2>*<4>
TProfile *hcov22prime[ncent][npt][npid];      // <2>*<2'>
TProfile *hcov24prime[ncent][npt][npid];      // <2>*<4'>
TProfile *hcov42prime[ncent][npt][npid];      // <2>*<4'>
TProfile *hcov44prime[ncent][npt][npid];      // <4>*<4'>
TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>

TProfile *hv2EP[ncent][npt][npid];	// elliptic flow from EP method
TProfile *hv22EP[ncent][npid];      // integrated flow from EP method

TH1F *H_Qw[neta];     // sub-event multiplicity
TH1F *H_EP[neta];		  // reaction plane
TH1F *H_Qx[neta][ncent];     //
TH1F *H_Qy[neta][ncent];
TProfile *HRes[ncent];		// resolution
TProfile *hcounter[ncent][npt][npid]; // for testing how different are particle entries of each method

// v22 with eta-gap
TProfile *hv22Gap[ncent];
TProfile *hv22ptGap[ncent][npt][npid];
TProfile *hcov22primeGap[ncent][npt][npid];

void FlowANA::Booking(TString outFile){
  char name[800];
  char title[800];
  d_outfile = new TFile(outFile.Data(),"recreate");
  cout << outFile.Data() << " has been initialized" << endl;
  hEvt  = new TH1I("hEvt","Event number",1,0,1);
  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

  for( int ieta=0;ieta<neta;ieta++){
    H_Qw[ieta] = new TH1F(Form("H_Qw_%d",ieta),Form("H_Qw_%d",ieta), 100, 0, 1000 );    
    H_EP[ieta] = new TH1F(Form("H_EP_%d",ieta),Form("H_EP_%d",ieta), 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    for (int icent=0;icent<ncent;icent++){
      H_Qx[ieta][icent] = new TH1F(Form("H_Qx_%i_%i",ieta,icent),Form("H_Qv_%i_%i",ieta,icent), 240, -1.2, 1.2);
      H_Qy[ieta][icent] = new TH1F(Form("H_Qy_%i_%i",ieta,icent),Form("H_Qv_%i_%i",ieta,icent), 240, -1.2, 1.2);
    }
  }
  for (int icent=0;icent<ncent;icent++){ // loop over centrality classes
    HRes[icent] = new TProfile(Form("HRes_%i",icent),Form("HRes_%i",icent),1,0.,1.);
    hv22[icent] = new TProfile(Form("hv22_%i",icent),Form("hv22_%i",icent),1,0.,1.);
    hv24[icent] = new TProfile(Form("hv24_%i",icent),Form("hv24_%i",icent),1,0.,1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i",icent),Form("hcov24_%i",icent),1,0.,1.);
    hv22Gap[icent] = new TProfile(Form("hv22Gap_%i",icent),Form("hv22Gap_%i",icent),1,0.,1.);

    for (int id=0;id<npid;id++){
      // hv2MC[icent][id] = new TProfile(Form("hv2MC_%i_%i",icent,id),Form("hv2MC_%i_%i",icent,id),1,0.,1.);
      hv22EP[icent][id] = new TProfile(Form("hv22EP_%i_%i",icent,id),Form("hv22EP_%i_%i",icent,id),1,0.,1.);
      // hv22[icent][id] = new TProfile(Form("hv22_%i_%i",icent,id),Form("hv22_%i_%i",icent,id),1,0.,1.);
      // hv24[icent][id] = new TProfile(Form("hv24_%i_%i",icent,id),Form("hv24_%i_%i",icent,id),1,0.,1.);
      // hcov24[icent][id] = new TProfile(Form("hcov24_%i_%i",icent,id),Form("hcov24_%i_%i",icent,id),1,0.,1.);
      for (int ipt = 0; ipt < npt; ipt++){ // loop over pt bin
        // hv2MCpt[icent][ipt] = new TProfile(Form("hv2MCpt_%i_%i_%i",icent,ipt,id),Form("hv2MCpt_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv2EP[icent][ipt][id] = new TProfile(Form("hv2EP_%i_%i_%i",icent,ipt,id),Form("hv2EP_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hPT[icent][ipt][id] = new TProfile(Form("hPT_%i_%i_%i",icent,ipt,id),Form("hPT_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv22pt[icent][ipt][id] = new TProfile(Form("hv22pt_%i_%i_%i",icent,ipt,id),Form("hv22pt_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hv24pt[icent][ipt][id] = new TProfile(Form("hv24pt_%i_%i_%i",icent,ipt,id),Form("hv24pt_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov22prime[icent][ipt][id] = new TProfile(Form("hcov22prime_%i_%i_%i",icent,ipt,id),Form("hcov22prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov24prime[icent][ipt][id] = new TProfile(Form("hcov24prime_%i_%i_%i",icent,ipt,id),Form("hcov24prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov42prime[icent][ipt][id] = new TProfile(Form("hcov42prime_%i_%i_%i",icent,ipt,id),Form("hcov42prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov44prime[icent][ipt][id] = new TProfile(Form("hcov44prime_%i_%i_%i",icent,ipt,id),Form("hcov44prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov2prime4prime[icent][ipt][id] = new TProfile(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id),Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcounter[icent][ipt][id] = new TProfile(Form("hcounter_%i_%i_%i",icent,ipt,id),Form("hcounter_%i_%i_%i",icent,ipt,id),3,0.,3.);
        hv22ptGap[icent][ipt][id] = new TProfile(Form("hv22ptGap_%i_%i_%i",icent,ipt,id),Form("hv22ptGap_%i_%i_%i",icent,ipt,id),1,0.,1.);
        hcov22primeGap[icent][ipt][id] = new TProfile(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id),Form("hcov22primeGap_%i_%i_%i",icent,ipt,id),1,0.,1.);      
      } // end of loop over pt bin
    }
  } // end of loop over centrality classes
  cout << "Histograms have been initialized" << endl;

}

void FlowANA::Loop_a_file(TString file){
  TStopwatch timer;
  timer.Start();
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
  timer.Stop();
  timer.Print();
}

void FlowANA::Loop_a_list_of_file(TString fileList){
  TStopwatch timer;
  timer.Start();
  TChain *chain = new TChain("mctree");
  std::ifstream file(fileList.Data());
  std::string line;
  while(std::getline(file, line))
  {
      chain->Add(line.c_str());
  }
  if (chain == 0){
    cout << "mctree is not found in " << line << endl;
    return;
  }
  Init(chain);
  Loop();
  timer.Stop();
  timer.Print();
}

void FlowANA::Ana_end(){
  d_outfile -> cd();
  d_outfile -> Write();
  d_outfile -> Close();
  cout << "Histfile has been written" << endl;
}

void FlowANA::Loop()
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
      if (jentry%100000==0) cout << jentry << endl;
   }
}

void FlowANA::Ana_event(){
  hEvt -> Fill(1);
  float rp = 0;
  // rp = gRandom->Uniform(0, 2.*TMath::Pi());
  int fcent=CentB(bimp);
  if (fcent<0) return;
  hMult -> Fill(nh);
  hRP -> Fill(rp);
  hBimp -> Fill(bimp);
  hBimpvsMult -> Fill(nh,bimp);
  // notation as (26) in DOI:10.1103/PhysRevC.83.044913
  // Q-vector of RFP
  Double_t Qx2=0., Qy2=0., Qx4=0., Qy4=0.;
  TComplex Q2=0., Q4=0.;
  // p-vector of POI
  Double_t px2[npt][npid]={{0.}}, py2[npt][npid]={{0.}};
  TComplex p2[npt][npid]={{0.}}, p4[npt][npid]={{0.}}, q2[npt][npid]={{0.}}, q4[npt][npid]={{0.}};
  // q-vector of particles marked as POI and RFP, which is used for 
  // autocorrelation substraction
  Double_t qx2[npt][npid]={{0.}}, qy2[npt][npid]={{0.}}, qx4[npt][npid]={{0.}}, qy4[npt][npid]={{0.}};
  // Total number of RFP in given event
  Double_t M = 0.;
  // numbers of POI (mp) and particles marked both POI and RFP (mq)
  Double_t mq[npt][npid]={{0.}},mp[npt][npid]={{0.}};
  // average reduced single-event 2- and 4-particle correlations : <2'> & <4'>
  Double_t redCor22[npt][npid]={{0.}}, redCor24[npt][npid]={{0.}};
  // event weights for correlation calculation
  Double_t w2=0.,w4=0.;
  // event weights for reduced correlation calculation
  Double_t wred2[npt][npid]={{0.}},wred4[npt][npid]={{0.}};
  // Average single-event 2- and 4- particle correlations : <2> & <4>
  Double_t cor22 = 0., cor24 = 0.;

  Double_t Qx2Gap[neta]={0.}, Qy2Gap[neta]={0.};
  Double_t px2Gap[neta][npt][npid]={{{0.}}}, py2Gap[neta][npt][npid]={{{0.}}};
  TComplex Q2Gap[neta]={0.}, p2Gap[neta][npt][npid]={{{0.}}};
  Double_t MGap[neta]={0};
  Double_t mpGap[neta][npt][npid]={{{0.}}};
  Double_t w2Gap=0.;
  Double_t wred2Gap[neta][npt][npid]={{{0.}}};
  Double_t cor22Gap=0.;
  Double_t redCor22Gap[neta][npt][npid]={{{0.}}};

  float sumQxy[neta][2]={{0}};  // [eta-,eta+][x,y]
  float multQv[neta]={0};       // [eta+,eta-]
  float wQv[neta]={0};

  for(int iTrk=0;iTrk<nh;iTrk++) { // track loop
    TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
    float pt  = vect.Pt();
    float eta = vect.Eta();
    float phi = vect.Phi();
    if (pt < minpt || pt > maxpt || abs(eta)>eta_cut) continue; // track selection
    // if (abs(eta)<eta_gap) continue;
    auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
    if (!particle) continue;
    float charge = 1./3.*particle->Charge();
    if (charge == 0) continue;
    // if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

    hPt -> Fill(pt);
    hEta -> Fill(eta);
    hPhi -> Fill(phi);
    Int_t ipt = -1;
    for(int j=0; j<npt;j++){
      if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
    }

    int fId=-1;
    if(pdg[iTrk]==211)  fId=1; // pion+
    if(pdg[iTrk]==321)  fId=2; // kaon+
    if(pdg[iTrk]==2212) fId=3; // proton
    if(pdg[iTrk]==-211)  fId=5; // pion-
    if(pdg[iTrk]==-321)  fId=6; // kaon-
    if(pdg[iTrk]==-2212) fId=7; // anti-proton

    Double_t cos4phi = TMath::Cos(4.*phi);
    Double_t sin4phi = TMath::Sin(4.*phi);
    Double_t cos2phi = TMath::Cos(2.*phi);
    Double_t sin2phi = TMath::Sin(2.*phi);
    
    Qx2+=cos2phi;
    Qy2+=sin2phi;
    Qx4+=cos4phi;
    Qy4+=sin4phi;
    M++;
    // POI selection
    if (charge>0){
      px2[ipt][0]+=cos2phi;
      py2[ipt][0]+=sin2phi;
      mp[ipt][0]++;

      qx2[ipt][0]+=cos2phi;
      qy2[ipt][0]+=sin2phi;
      qx4[ipt][0]+=cos4phi;
      qy4[ipt][0]+=sin4phi;
      mq[ipt][0]++;
    }
    if (charge<0){
      px2[ipt][4]+=cos2phi;
      py2[ipt][4]+=sin2phi;
      mp[ipt][4]++;

      qx2[ipt][4]+=cos2phi;
      qy2[ipt][4]+=sin2phi;
      qx4[ipt][4]+=cos4phi;
      qy4[ipt][4]+=sin4phi;
      mq[ipt][4]++;
    }
    if (fId>0){
      px2[ipt][fId]+=cos2phi;
      py2[ipt][fId]+=sin2phi;
      mp[ipt][fId]++;

      qx2[ipt][fId]+=cos2phi;
      qy2[ipt][fId]+=sin2phi;
      qx4[ipt][fId]+=cos4phi;
      qy4[ipt][fId]+=sin4phi;
      mq[ipt][fId]++;
    }

    if (eta <-eta_gap){
      Qx2Gap[0]+=cos2phi;
      Qy2Gap[0]+=sin2phi;
      MGap[0]++;
      if (charge>0){
        px2Gap[1][ipt][0]+=cos2phi;
        py2Gap[1][ipt][0]+=sin2phi;
        mpGap[1][ipt][0]++;
      }
      if (charge<0){
        px2Gap[1][ipt][4]+=cos2phi;
        py2Gap[1][ipt][4]+=sin2phi;
        mpGap[1][ipt][4]++;
      }
      if (fId>0){
        px2Gap[1][ipt][fId]+=cos2phi;
        py2Gap[1][ipt][fId]+=sin2phi;
        mpGap[1][ipt][fId]++;
      }
    }
    if (eta > eta_gap){
      Qx2Gap[1]+=cos2phi;
      Qy2Gap[1]+=sin2phi;
      MGap[1]++;

      if (charge>0){
        px2Gap[0][ipt][0]+=cos2phi;
        py2Gap[0][ipt][0]+=sin2phi;
        mpGap[0][ipt][0]++;
      }
      if (charge<0){
        px2Gap[0][ipt][4]+=cos2phi;
        py2Gap[0][ipt][4]+=sin2phi;
        mpGap[0][ipt][4]++;
      }
      if (fId>0){
        px2Gap[0][ipt][fId]+=cos2phi;
        py2Gap[0][ipt][fId]+=sin2phi;
        mpGap[0][ipt][fId]++;
      }
    }
    // Sub eta event method, TPC plane
    int fEta = -1;
    if (eta <-eta_gap) fEta = 0; // TPC Left EP
    if (eta > eta_gap) fEta = 1; // TPC Right EP

    if ( fEta>-1 ){
      sumQxy[fEta][0] += pt * cos2phi;
      sumQxy[fEta][1] += pt * sin2phi;
      wQv[fEta]       += pt;
      multQv[fEta]++;
    } // end of eta selection
  } // end of track loop

  // ================================== Direct Cumulants ================================== //
  if (MGap[0]!=0 && MGap[1]!=0){
    for (int ieta=0;ieta<neta;ieta++){
      Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
    }
    w2Gap = MGap[0]*MGap[1];
    cor22Gap = CalRedCor22(Q2Gap[0],Q2Gap[1],MGap[0],MGap[1], 0.,w2Gap);       // <2>
    hv22Gap[fcent]->Fill(0.5, cor22Gap, w2Gap);
  
    for (int ieta=0;ieta<neta;ieta++){
      for (int ipt = 0; ipt < npt; ipt++){ // <2'>
        for (int id=0;id<npid;id++){
          if (mpGap[ieta][ipt][id]==0) continue;
          // Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
          p2Gap[ieta][ipt][id] = TComplex(px2Gap[ieta][ipt][id], py2Gap[ieta][ipt][id]);
          wred2Gap[ieta][ipt][id] = mpGap[ieta][ipt][id]*MGap[ieta];
          redCor22Gap[ieta][ipt][id] = CalRedCor22(Q2Gap[ieta], p2Gap[ieta][ipt][id], MGap[ieta], mpGap[ieta][ipt][id], 0., wred2Gap[ieta][ipt][id]);   // <2'>
          hv22ptGap[fcent][ipt][id]->Fill(0.5, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);                                                                      // <<2'>>
          hcounter[fcent][ipt][id]->Fill(1.5,1,mpGap[ieta][ipt][id]);
          // TProfile for covariance calculation in statistic error
          hcov22primeGap[fcent][ipt][id]->Fill(0.5, cor22Gap*redCor22Gap[ieta][ipt][id], w2Gap*wred2Gap[ieta][ipt][id]); // <2>*<2'>
        }
      }
    }
  }

  Q2 = TComplex(Qx2, Qy2);
  w2 = M*(M-1);                         // w(<2>)
  Q4 = TComplex(Qx4, Qy4);
  w4 = M*(M-1)*(M-2)*(M-3);             // w(<4>)
  if (w2 != 0 && w4 != 0){
    cor22 = CalCor22(Q2, M, w2);        // <2>
    cor24 = CalCor24(Q2, Q4, M, w4);    // <4>
    hv22[fcent]->Fill(0.5, cor22, w2);  // <<2>>
    hv24[fcent]->Fill(0.5, cor24, w4);  // <<4>>

    // TProfile for covariance calculation in statistic error
    hcov24[fcent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
    for (int ipt = 0; ipt < npt; ipt++){
      for (int id=0;id<npid;id++){
        if (mp[ipt][id] == 0) continue;
        p2[ipt][id] = TComplex(px2[ipt][id], py2[ipt][id]);
        q2[ipt][id] = TComplex(qx2[ipt][id], qy2[ipt][id]);
        wred2[ipt][id] = mp[ipt][id]*M-mq[ipt][id];                                                                                   // w(<2'>)
        if (wred2[ipt][id]==0) continue;
        q4[ipt][id] = TComplex(qx4[ipt][id], qy4[ipt][id]);
        wred4[ipt][id] = (mp[ipt][id]*M-3*mq[ipt][id])*(M-1)*(M-2);                                                                   // w(<4'>)
        if (wred4[ipt][id]==0) continue;
        redCor22[ipt][id] = CalRedCor22(Q2, p2[ipt][id], M, mp[ipt][id], mq[ipt][id], wred2[ipt][id]);                                // <2'>
        hv22pt[fcent][ipt][id]->Fill(0.5, redCor22[ipt][id], wred2[ipt][id]);                                                         // <<2'>>
        redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]);  // <4'>
        hv24pt[fcent][ipt][id]->Fill(0.5, redCor24[ipt][id], wred4[ipt][id]);                                                         // <<4'>>

        // TProfile for covariance calculation in statistic error
        hcov22prime[fcent][ipt][id]->Fill(0.5, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]);     // <2>*<2'>
        hcov24prime[fcent][ipt][id]->Fill(0.5, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
        hcov42prime[fcent][ipt][id]->Fill(0.5, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
        hcov44prime[fcent][ipt][id]->Fill(0.5, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
        hcov2prime4prime[fcent][ipt][id]->Fill(0.5, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);

        hcounter[fcent][ipt][id]->Fill(0.5,1,mp[ipt][id]);
      }
    }
  }
  // ==================================== Eta Sub-event ==================================== //

  float fEP[2]; // [eta-,eta+]
  for (int ieta=0; ieta<neta; ieta++){
    if( multQv[ieta]>2 ){ // multiplicity > 2
      for (int i=0;i<2;i++){
        sumQxy[ieta][i] /= wQv[ieta];
      }
      fEP[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
      H_Qw[ieta]->Fill( multQv[ieta] );
      H_EP[ieta]->Fill( fEP[ieta] );
      H_Qx[ieta][fcent]->Fill( sumQxy[ieta][0] );
      H_Qy[ieta][fcent]->Fill( sumQxy[ieta][1] );
    }else{
      fEP[ieta] = -9999;
    }
  }

  // Resolution
  float psiEP_L, psiEP_R;
  psiEP_L = fEP[0];
  psiEP_R = fEP[1];
  if (psiEP_L<-9000 || psiEP_R<-9000) return;
  float dPsi = 2. *(psiEP_L - psiEP_R);
  // dPsi = TMath::ATan2( sin(dPsi) , cos(dPsi));
  HRes[fcent] -> Fill(0.5,cos(dPsi));

  for(int iTrk=0;iTrk<nh;iTrk++) { // track loop
    TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
    float pt  = vect.Pt();
    float eta = vect.Eta();
    float phi = vect.Phi();
    if (pt < minpt || pt > maxpt || abs(eta)>eta_cut || abs(eta)<eta_gap) continue; // track selection
    auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
    if (!particle) continue;
    float charge = 1./3.*particle->Charge();
    if (charge == 0) continue;
    // if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

    Int_t ipt = -1;
    for(int j=0; j<npt;j++){
      if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
    }

    int fId=-1;
    if(pdg[iTrk]==211)  fId=1; // pion+
    if(pdg[iTrk]==321)  fId=2; // kaon+
    if(pdg[iTrk]==2212) fId=3; // proton
    if(pdg[iTrk]==-211)  fId=5; // pion-
    if(pdg[iTrk]==-321)  fId=6; // kaon-
    if(pdg[iTrk]==-2212) fId=7; // anti-proton
    
    // ==================================== Eta Sub-event ==================================== //
    float v2=-999.0;
    if(eta>0){ // eta+
      // v2 = cos(2.0 * (phi-psi1) )/res2[fcent];
      v2 = cos(2.0 * (phi-psiEP_L) );
    }
    if(eta<0){ // eta-
      // v2 = cos(2.0 * (phi-psi2) )/res2[fcent];
      v2 = cos(2.0 * (phi-psiEP_R) );
    }
    if (charge>0){
      hPT[fcent][ipt][0]->Fill(0.5, pt, 1);
      hv2EP[fcent][ipt][0]->Fill(0.5,v2);
      hv22EP[fcent][0]->Fill(0.5,v2);
      hcounter[fcent][ipt][0]->Fill(2.5,1);
    }
    if (charge<0){
      hPT[fcent][ipt][4]->Fill(0.5, pt, 1);
      hv2EP[fcent][ipt][4]->Fill(0.5,v2);
      hv22EP[fcent][4]->Fill(0.5,v2);
      hcounter[fcent][ipt][4]->Fill(2.5,1);
    }
    
    if (fId>0) {
      hPT[fcent][ipt][fId]->Fill(0.5, pt, 1);
      hv2EP[fcent][ipt][fId]->Fill(0.5,v2);
      hv22EP[fcent][fId]->Fill(0.5,v2);
      hcounter[fcent][ipt][fId]->Fill(2.5,1);
    }
  } // end of track loop
} // end of Ana_event();

// root -l -b -q calculateFlow.C+'("/weekly/povarov/lbavinh/UrQMD/chain/chain550.root","test.root")'
// root -l -b -q anaFlow.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/Urqmd11.5/runlist_9889","test.root")'
// root -l -b -q FlowRun.C'("/weekly/lbavinh/lbavinh/UrQMD/split/Urqmd7.7/runlist_Urqmd7.7_00.list","test.root")'
// root -l -b -q anaFlow.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/Urqmd7.7/runlist_Urqmd7.7_00.list","test.root")'