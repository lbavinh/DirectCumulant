/**
 * \brief Example of how to read a file (list of files) using McDst class in a standalone mode
 *
 * processMcDstStandalone.cpp is an example of reading McDst format in a standalone mode
 * on your laptop of local computer farm.
 * Prerequisites:
 * - McDst directory
 * - CERN ROOT package
 * - g++ >= 4.8
 * - Makefile
 *
 * First, the program must be compiled with the Makefile, with simple command in the bash shell:
 * make
 *
 * Then the executable file processMcDstStandalone will be created. The current version of the program
 * expects 3 arguments: ./processMcDstStandalone inputFile outputFile
 * The first one is the program name, the second one is the name of the inputfile that 
 * maybe either the mcDst file itself, in a format dummyname.mcDst.root or a list of
 * such files called dummyname.list or dummyname.lis. The outputFile assumes the some_output_name.root.
 */

// C++ headers
#include <iostream>
#include <cmath>
// ROOT headers
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TDatabasePDG.h"
#include "TComplex.h"
#include "TProfile.h"

// McDst headers
#include "McDstReader.h"
#include "McDst.h"
#include "McEvent.h"
#include "McParticle.h"
#include "McRun.h"

// My utilities
#include "function.C"
//_________________
int main(int argc, char* argv[]) {

// #if ROOT_VERSION_CODE >= ROOT_VERSION(6,0,0)
//   R__LOAD_LIBRARY(libEG)
//   R__LOAD_LIBRARY(libMcDst)
// #else
//   gSystem->Load("libEG");
//   gSystem->Load("libMcDst.so");
// #endif

  std::cout << "Hi! Lets do some physics, Master!" << std::endl;

  const char* fileName;
  const char* oFileName;
  
  switch (argc) {
  case 3:
    fileName = argv[1];
    oFileName = argv[2];
    break;
  default:
    std::cout << "Usage: processMcDstStandalone inputFileName outputFileName.root" << std::endl;
    return -1;
  }
  std::cout << " inputFileName : " << fileName << std::endl;
  std::cout << " outputFileName: " << oFileName << std::endl;

  McDstReader* myReader = new McDstReader(fileName);
  myReader->Init();  

  // This is a way if you want to spead up IO
  std::cout << "Explicit read status for some branches" << std::endl;
  myReader->setStatus("*",0);
  myReader->setStatus("Event",1);
  myReader->setStatus("Particle",1);
  std::cout << "Status has been set" << std::endl;

  std::cout << "Now I know what to read, Master!" << std::endl;

  if( !myReader->chain() ) {
    std::cout << "No chain has been found." << std::endl;
  }
  Long64_t eventsInTree = myReader->tree()->GetEntries();
  std::cout << "eventsInTree: "  << eventsInTree << std::endl;
  Long64_t events2read = myReader->chain()->GetEntries();

  std::cout << "Number of events to read: " << events2read << std::endl;

  TFile *oFile = new TFile(oFileName, "recreate");

  /////////////////////
  //  Histogramming  //
  /////////////////////

  // Event
  TH2D *hImpactParVsNch = new TH2D("hImpactParVsNch",
				   "Impact parameter vs. Nch;Nch;Impact parameter (fm)",
				   300, -0.5, 599.5, 130, 0., 13.);
  TH1D *hNch = new TH1D("hNCh","Number of charged particles;Nch;Entries",
                        300, -0.5, 599.5);

  // Track
  TH1D *hParticleCharge = new TH1D("hParticleCharge","Charge of the particle;Q;Entries",
				   19, -9.5, 9.5);
  TH1D *hPz = new TH1D("hPz","p_{z} of particle;p_{z} (GeV/c);Entries",
                            402, -201., 201.);
  TH2D *hPtVsEta = new TH2D("hPtVsEta",
			    "p_{T} vs. #eta of primary track;#eta;p_{T} (GeV/c)",
                            220, -1.1, 1.1, 80, 0.05, 2.05);
  TH1D *hPionMom = new TH1D("hPionMom","Momentum of #pi;p (GeV/c);Entries",
                            100, 0., 2.);

  /////////////////////
  //     Analysis    //
  /////////////////////

  Int_t eventCounter = 0;
  Int_t hundredIter = 0;

  static const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
  static const int ncent = 8; // 0-80%
  static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
  static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};
  static const double maxpt = 3.; // max pt
  static const double minpt = 0.2; // min pt
  static const float eta_cut =  1.5;
  static const float eta_gap = 0.05;
  static const int neta = 2; // [eta-,eta+]
  static const int max_nh = 1700;

  TH1I *hEvt;        // Event number 
  TH1F *hPt;         // transverse momentum distr
  TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
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

  hEvt  = new TH1I("hEvt","Event number",1,0,1);
  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", max_nh, 0, max_nh);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", max_nh, 0, max_nh, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

  for( int ieta=0;ieta<neta;ieta++){
    H_Qw[ieta] = new TH1F(Form("H_Qw_%d",ieta),Form("H_Qw_%d",ieta), 300, 0, 300 );    
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
      hv22EP[icent][id] = new TProfile(Form("hv22EP_%i_%i",icent,id),Form("hv22EP_%i_%i",icent,id),1,0.,1.);
      for (int ipt = 0; ipt < npt; ipt++){ // loop over pt bin
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
  std::cout << "Histograms have been initialized." << std::endl;
  // Loop over events
  for(Long64_t iEvent=0; iEvent<events2read; iEvent++) {

    eventCounter++;
    if( eventCounter >= 100 ) {
      eventCounter = 0;
      hundredIter++;
      std::cout << "Working on event #[" << (hundredIter * 100)
		<< "/" << events2read << "]" << std::endl;
    }

    Bool_t readEvent = myReader->loadEntry(iEvent);
    if( !readEvent ) {
      std::cout << "Something went wrong, Master! Nothing to analyze..."
		<< std::endl;
      break;
    }

    // Retrieve femtoDst
    McDst *dst = myReader->mcDst();

    // Retrieve event information
    McEvent *event = dst->event();
    if( !event ) {
      std::cout << "Something went wrong, Master! Event is hiding from me..."
		<< std::endl;
      break;
    }
    hEvt -> Fill(1);
    float bimp = event->GetImpact();
    int fcent=CentB(bimp);
    if (fcent < 0) continue;
    hBimp -> Fill(bimp);
    // Track analysis
    Int_t nTracks = dst->numberOfParticles();
    Int_t NumOfCharged = 0;

    hMult -> Fill(nTracks);

    hBimpvsMult -> Fill(nTracks,bimp);
    // notation as (26) in DOI:10.1103/PhysRevC.83.044913
    // Q-vector of RFP
    Double_t Qx2=0., Qy2=0., Qx4=0., Qy4=0.;
    TComplex Q2=0., Q4=0.;
    // p-vector of POI
    Double_t px2[npt][npid]={{0.}}, py2[npt][npid]={{0.}};
    TComplex p2[npt][npid]={{0.}}, q2[npt][npid]={{0.}}, q4[npt][npid]={{0.}};
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

    // Track loop
    for(Int_t iTrk=0; iTrk<nTracks; iTrk++) {

      // Retrieve i-th femto track
      McParticle *particle = (McParticle*)dst->particle(iTrk);

      if (!particle) continue;

      // std::cout << "Track #[" << (iTrk+1) << "/" << nTracks << "]"  
      // 		<< std::endl;

      // std::cout << "pdgId: " << particle->pdg() 
      // 		<< " status: " << particle->status()
      // 		<< " px/py/pz/E/m: " 
      // 		<< particle->px() << " / " 
      // 		<< particle->py() << " / "
      // 		<< particle->pz() << " / " 
      // 		<< particle->e() << " / "
      // 		<< particle->mass() << std::endl;

      
      hPz->Fill( particle->pz() );
      hParticleCharge->Fill( particle->charge() );

      if ( particle->charge() ) {
        NumOfCharged++;

        hPtVsEta->Fill( particle->eta(), particle->pt() );

        if ( particle->pdg() == 211 ) {
          hPionMom->Fill( particle->ptot() );
        }
      } // if ( particle->charge() )

      float pt  = particle->pt();
      float eta = particle->eta();
      float phi = particle->phi();
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut) continue; // track selection
      // if (abs(eta)<eta_gap) continue;
      // if (!particle) continue;
      float charge = particle->charge();
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
      if(particle->pdg()==211)  fId=1; // pion+
      if(particle->pdg()==321)  fId=2; // kaon+
      if(particle->pdg()==2212) fId=3; // proton
      if(particle->pdg()==-211)  fId=5; // pion-
      if(particle->pdg()==-321)  fId=6; // kaon-
      if(particle->pdg()==-2212) fId=7; // anti-proton

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
        qy4[ipt][fId]+=TMath::Sin(4.*phi);
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
    } //for(Int_t iTrk=0; iTrk<nTracks; iTrk++)

    hImpactParVsNch->Fill( NumOfCharged, event->impact() );
    hNch->Fill( NumOfCharged );

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
      if( multQv[ieta]>0 ){ // multiplicity > 2
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
    if (psiEP_L<-9000 || psiEP_R<-9000) continue;
    float dPsi = 2. *(psiEP_L - psiEP_R);
    // dPsi = TMath::ATan2( sin(dPsi) , cos(dPsi));
    HRes[fcent] -> Fill(0.5,cos(dPsi));

    for(int iTrk=0;iTrk<nTracks;iTrk++) { // track loop
      McParticle *particle = (McParticle*)dst->particle(iTrk);

      if (!particle) continue;
      float pt  = particle->pt();
      float eta = particle->eta();
      float phi = particle->phi();
      if (pt < minpt || pt > maxpt || abs(eta)>eta_cut) continue; // track selection
      // if (abs(eta)<eta_gap) continue;
      // if (!particle) continue;
      float charge = particle->charge();
      if (charge == 0) continue;

      // if (phi<0) phi += 2.*TMath::Pi(); /* To make sure that phi is between 0 and 2 Pi */

      Int_t ipt = -1;
      for(int j=0; j<npt;j++){
        if(pt>=bin_pT[j] && pt<bin_pT[j+1]) ipt = j;
      }

      int fId=-1;
      if(particle->pdg()==211)  fId=1; // pion+
      if(particle->pdg()==321)  fId=2; // kaon+
      if(particle->pdg()==2212) fId=3; // proton
      if(particle->pdg()==-211)  fId=5; // pion-
      if(particle->pdg()==-321)  fId=6; // kaon-
      if(particle->pdg()==-2212) fId=7; // anti-proton
      
      // ==================================== Eta Sub-event ==================================== //
      float v2=-999.0;
      if(eta>eta_gap){ // eta+
        // v2 = cos(2.0 * (phi-psi1) )/res2[fcent];
        v2 = cos(2.0 * (phi-psiEP_L) );
      }
      if(eta<-eta_gap){ // eta-
        // v2 = cos(2.0 * (phi-psi2) )/res2[fcent];
        v2 = cos(2.0 * (phi-psiEP_R) );
      }
      if (v2<-900.) continue;
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


  } //for(Long64_t iEvent=0; iEvent<events2read; iEvent++)

  oFile->Write();
  oFile->Close();
  myReader->Finish();

  std::cout << "I'm done with analysis. We'll have a Nobel Prize, Master!" << std::endl;

  return 0;
}
// source /weekly/lbavinh/Soft/McDst/mcdst_environment.sh
// ./processMcDstStandalone /eos/nica/mpd/users/batyuk/mcDst/UrQMD/AuAu/Hg/cms_4.5GeV/AuAu_ecm4.5GeV_EoS_Hg_0-14fm_1000ev_9.mcDst.root ./test.root
// ./processMcDstStandalone /eos/nica/mpd/users/batyuk/mcDst/UrQMD/AuAu/Hg/cms_7.7GeV/AuAu_ecm7.7GeV_EoS_Hg_0-14fm_1000ev_9999.mcDst.root ./test.root