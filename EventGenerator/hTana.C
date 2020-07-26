#define hTana_cxx
#include "hTana.h"

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TRandom2.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TString.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include "function.C"
using namespace std;
//List of histograms and Ntuples....

static const float PI = TMath::Pi();
static const float pTmax=4900.;


static const int npt = 25; // 0.3 - 6.0 GeV/c 
static const double bin_pT[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.5};
static const float maxpt = 3.5; // max pt
static const float minpt = 0.2; // min pt

static const int max_nh = 1500;

float   d_rp;           // reaction plane azimuthal angle
float   d_b;            // impact parameter
int     d_nh;           // number of hadrons
float   d_pt[max_nh];   // transverse momentum
float   d_phi0[max_nh]; // particle azimuthal angle in laboratory system
float   d_eta[max_nh];  // pseudorapidity


TFile *d_outfile; // output ROOT file
TTree *htree; // TTree to save events
TFile *d_infile; // input ROOT file with neccessary histograms for impact par simulation

// Read histograms from the Glauber file
TH1F *hBimp; // impact parameter b distribution
TH1I *hNpart, *hNcoll; // number of participant, number of binary collision
TH2F *hBimpvsNpart, *hBimpvsNcoll;

// Histograms to be written to ROOT file
static TH1I *hMult; // emitted multiplicity 
static TH1F *hB; // impact parameter
static TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)
static TH1F *hRP; // reaction plane
static TH1F *hPt; // transverse momentum
static TH1F *hPhi; // azimuthal angle
static TH1F *hPhil; // azimuthal angle in laboratory frame
static TH1F *hEta; // pseudorapidity

void hTana::Loop() {}

void hTana::ana_init(TString outfile) {
  book_hist(outfile.Data());
}

void hTana::v2gen(int nevent,double Mmean) {
  cout << "number of events to generate:" << nevent << endl;

  int seed1 = (int) clock();
  int seed2 = (int) clock() * 2;
  cout << "seed1="<<seed1<<"   "<<"seed2="<<seed2<<endl;

  TRandom2 *GR = new TRandom2();
  GR -> SetSeed(seed1);

  //Set random seed so your random numbers don't repeat each time you run this macro
  TRandom3 rnd;
  gRandom->SetSeed(rnd.Uniform(0., 1000000.));

  // Start the timer: that way we can see how much time Nevents will be generated
  TStopwatch timer;
  timer.Start();

  // Main parameters:
  //  f - Npart to Ncoll contribution to multiplicity. Essentially, it reflects how multiplicity behaves
  //      near its maximum (in the most central region).
  //    f = 0 - Multiplicity is renormalized Ncoll
  //    f = 1 - Multiplicity is renormalized Npart
  const double f = 0.1;
  int mult=0; // emmitted multiplicity
  double b; // impact parameter

  double v2pT, v4pT;

  double pT; // transverse momentum
  double phi; // azimuthal angle
  double phil; // azimuthal angle in laboratory coordinates
  double phirp; // azimuthal angle of reation plane
  double eta; // pseudorapidity

  float nonflow = 1.; /* Simulating nonflow correlations: 
		     0: no nonflow correlations; 
		     1: "pair wise" emission (2 particles with same azimuth);
         2: "quadruplet" emission (4 particles with same azimuth).*/
  float nonflowrate = 0.250;
  /* Fraction of particles that are affected by nonflow effects. */

  Bool_t bAcceptance = kFALSE;

  float A = PI/3.;
  float B = PI/2.;

  float C = PI;
  float D = 5.*PI/4.;

  /* Monte-Carlo simulation */
  for(int ne=0; ne<nevent; ne++) { /* Loop over events */

    if(ne%50000==0) cout << ne << endl;

    b = hBimp -> GetRandom();
    double Npart = GetProjectedRandom(b, hBimpvsNpart);
    double Ncoll = GetProjectedRandom(b, hBimpvsNcoll);
    double Na = f * Npart + (1 - f) * Ncoll; // number of ancestors
    double NaNorm = (f * hNpart->GetMean() + (1 - f) * hNcoll->GetMean()) / Mmean;
    mult = (Na / NaNorm); /* Emitted multiplicity */
    hMult->Fill(mult);
    hBimpvsMult->Fill(Na / NaNorm, b);  
    hB -> Fill(b);
    phirp=-9999.0;

    phirp=2.*PI*(GR->Rndm());
    hRP->Fill(phirp);

    int nh = 0;   

    /* Loop over particles */
    for(int nm=0; nm<mult; nm++) {
      momentum:
      pT=pTmax*(GR->Rndm());
      if (GR->Rndm()>dndpT(pT)) goto momentum;

      pT=pT/1000.;
      
      /* generate transverse momentum according to the distribution, 
         using the hit-or-miss method. */
      if(pT>=0.2 && pT<=3.5){ //track's transverse momentum selection
        eta = 4.*(GR->Rndm()-0.5); /* Random pseudorapidity eta between -2 and 2 */

        v2pT = calc_v2(b,eta,pT);
        v4pT = calc_v4(b,eta,pT);

        flow:
        phi=2.*PI*(GR->Rndm()); /* Random azimuth phi between 0 and 2Pi */
        if (GR->Rndm()>dndphi(phi,v2pT,v4pT)) goto flow; 
        /* simulate anisotropic flow, with the hit-or-miss method */

        phil=phi+phirp; /* particle angle with respect to the laboratory frame */
        while (phil>2.*PI)
        phil-=2.*PI; /* To make sure that phil is between 0 and 2 Pi */
        // if (((phil>=0.) && (phil<=A    )) ||
        //     ((phil>=B ) && (phil<=C    )) ||
        //     ((phil>=D ) && (phil<=2.*PI)) ){ // 2 holes

          hPt->Fill(pT);
          hPhi  -> Fill(phi);
          hPhil -> Fill(phil);
          hEta  -> Fill(eta);
          d_phi0[nh] = phil;
          d_pt[nh]   = pT;
          d_eta[nh]  = eta;
          nh++;

          if (nonflow>0 && (nm<=(mult-2*nonflow)) && (GR->Rndm()<=nonflowrate)){ /* NONFLOW CORRELATION simulation */
              /* Two tests: 
              - a first, very inelegant one, to avoid having more particles in the 
              event than the multiplicity which has been determined earlier;
              - a second, more useful one, to have a fraction ~nonflowrate of 
              particles affected by nonflow effects. */
            if (nonflow==1) { // Pair-wise emission
              // Generating a second particle with the same momentum and azimuth.
              nm++;
              hPt->Fill(pT);
              hPhi -> Fill(phi);
              hPhil -> Fill(phil);
              hEta  -> Fill(eta);
              d_phi0[nh] = phil;
              d_pt[nh]   = pT;
              d_eta[nh]  = eta;
              nh++;

            } // end of Pair-wise emission
            else if (nonflow==2) { // Quadruplet-wise emission
              // Generating three more particles with the same momentum and azimuth.
              nm+=3;
              for(int i=0; i<3;i++){ // Generate 3 more particle
                hPt->Fill(pT);
                hPhi -> Fill(phi);
                hPhil -> Fill(phil);
                hEta  -> Fill(eta);
                d_phi0[nh] = phil;
                d_pt[nh]   = pT;
                d_eta[nh]  = eta;
                nh++;         
              } // end of 3 more particle generation
            } // End of generation Quadruplet-wise emission
          } // End of NONFLOW CORRELATION simulation
        // } // end of acceptance simulation
      } // end of track's transverse momentum selection
    }//end of the particle loop
    d_nh = nh;
    d_rp = phirp;
    d_b  = b;
    htree->Fill();
  }// end of event loop
  // Stop the timer and print how much time it took to generate Nevents
  timer.Stop();
  timer.Print();
}

void hTana::ana_end() {
  d_outfile->cd();

  htree -> Write();

  hMult -> Write();
  hBimpvsMult -> Write();
  hB    -> Write();
  hRP   -> Write();
  hPt   -> Write();
  hPhi  -> Write();
  hPhil -> Write();
  hEta  -> Write();

  d_outfile->Close();
}

void hTana::book_hist(TString outfile) {
  // read input TFile
  d_infile = new TFile("/mnt/pool/2/lbavinh/EventGenerator/merge_hist_glaub_200gev.root", "read");
  hBimp = (TH1F *)d_infile->Get("hBimp");
  hNpart = (TH1I *)d_infile->Get("hNpart");
  hNcoll = (TH1I *)d_infile->Get("hNcoll");
  hBimpvsNpart = (TH2F *)d_infile->Get("hBimpvsNpart");
  hBimpvsNcoll = (TH2F *)d_infile->Get("hBimpvsNcoll");

  d_outfile = new TFile(outfile.Data(),"recreate");
  cout << outfile.Data() << " was initialized." << endl;
  d_outfile -> cd();
  htree = new TTree("htree","Simulation of acceptance");

  htree->Branch("rp",&d_rp,"rp/F");
  htree->Branch("nh",&d_nh,"nh/I");
  htree->Branch("b",&d_b,"b/F");
  htree->Branch("pt",&d_pt,"pt[nh]/F");
  htree->Branch("phi0",&d_phi0,"phi0[nh]/F");
  htree->Branch("eta",&d_eta,"eta[nh]/F");

  // Create output histograms
  hMult = new TH1I("hMult", "Multiplicity;N_{ch};dN/dN_{ch}", 1500, 0, 1500);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 1500, 0, 1500, 200, 0., 20.);
  hB    = new TH1F("hB","Impact parameter;b (fm);dN/db",200, 0., 20.);
  hPt   = new TH1F("hPt","Pt-distribution;p_{T} (GeV/c); dN/dP_{T}",500,0.,6.);
  hRP   = new TH1F("hRP","Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}",300,0.,7.);
  hPhi  = new TH1F("hPhi","Particle azimuthal angle distribution with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})",300,0.,7.);
  hPhil = new TH1F("hPhil","Azimuthal angle distribution in laboratory coordinate system; #phi; dN/d#phi",300,0.,7.);
  hEta  = new TH1F("hEta","Pseudorapidity distribution; #eta; dN/d#eta",300,-2.2,2.2);
}