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

TTree *htree; // TTree to save events
TFile *d_outfile; // output ROOT file
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

    d_rp=phirp;
    d_b = b;
    
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

      if(pT>=0.2 && pT<=3.5){ //track selection

        hPhi  -> Fill(phi);
        hPhil -> Fill(phil);
        hEta  -> Fill(eta);

        d_phi0[nh] = phil;
        d_pt[nh]   = pT;
        d_eta[nh]  = eta;

        nh++;
      }// end of track selection
    }//end of the particle loop
    d_nh = nh;

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
  d_infile = new TFile("/mnt/pool/2/lbavinh/EventGenerator/merge_hist_glaub_200gev.root", "read"); // /mnt/pool/2/lbavinh/EventGenerator/ /mnt/pool/nica/6/parfenovpeter/CentralityGlauber/
  hBimp = (TH1F *)d_infile->Get("hBimp");
  hNpart = (TH1I *)d_infile->Get("hNpart");
  hNcoll = (TH1I *)d_infile->Get("hNcoll");
  hBimpvsNpart = (TH2F *)d_infile->Get("hBimpvsNpart");
  hBimpvsNcoll = (TH2F *)d_infile->Get("hBimpvsNcoll");

  d_outfile = new TFile(outfile.Data(),"recreate");
  cout << outfile.Data() << " was initialized." << endl;
  d_outfile -> cd();
  htree = new TTree("htree","Simulation");

  htree->Branch("rp",&d_rp,"rp/F");
  htree->Branch("nh",&d_nh,"nh/I");
  htree->Branch("b",&d_b,"b/F");
  htree->Branch("pt",&d_pt,"pt[nh]/F");
  htree->Branch("phi0",&d_phi0,"phi0[nh]/F");
  htree->Branch("eta",&d_eta,"eta[nh]/F");

  // Create output histograms
  hMult = new TH1I("hMult", "Multiplicity", 2500, 0, 2500);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 2500, 0, 2500, 200, 0., 20.);
  hB    = new TH1F("hB","Impact parameter;b (fm);dN/db",200, 0., 20.);
  hPt   = new TH1F("hPt","Pt-distribution;p_{T} (GeV/c); dN/dP_{T}",500,0.,6.);
  hRP   = new TH1F("hRP","Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}",300,0.,7.);
  hPhi  = new TH1F("hPhi","Particle azimuthal angle distribution with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})",300,0.,7.);
  hPhil = new TH1F("hPhil","Azimuthal angle distribution in laboratory coordinate system; #phi; dN/d#phi",300,0.,7.);
  hEta  = new TH1F("hEta","Pseudorapidity distribution; #eta; dN/d#eta",300,-2.2,2.2);
}