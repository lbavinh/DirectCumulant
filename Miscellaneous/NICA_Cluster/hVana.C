#define hVana_cxx
#include "hVana.h"
#include "function.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include "TString.h"
#include "TVectorD.h"

#include <iostream>
#include <fstream>
using namespace std;

static const int ncent = 8; // 0-80%
static const int bin_cent[ncent] = {5, 15, 25, 35, 45, 55, 65, 75};

static const Float_t maxpt = 3.5; // max pt
static const Float_t minpt = 0.2; // min pt
static const int npt = 24;        // 0.2 - 3.5 GeV/c
static const double bin_pT[25] = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1,
                                  1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 2.0, 2.2, 2.4,
                                  2.6, 2.8, 3.0, 3.2, 3.5};

TFile *d_outfile; // out file with histograms and profiles

TH1F *hRP;         // reaction plane distr
TH1F *hPt;         // transverse momentum distr
TH1F *hPhi;        // distr of particle azimuthal angle with respect to RP
TH1F *hPhil;       // distr of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta;        // pseudorapidity
TH1F *hBimp;       // impact parameter
TH1I *hMult;       // emitted multiplicity
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

// histograms for differential flow calculation from MC toy
TH1F *hpt[ncent][npt];
TH1F *hv2pt[ncent][npt]; // dif. v2 distr in each pT bin from MC toy
// TProfile for reference flow
TProfile *hv2MC[ncent]; // profile for MC integrated v2
TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
// TProfile for differential flow
TProfile *hPT[ncent][npt];     // profile pt
TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
TProfile *hv22pt[ncent][npt];  // profile <<2'>> from 2nd Q-Cumulants
TProfile *hv24pt[ncent][npt];  // profile <<4'>> from 4th Q-Cumulants
// TProfile for covariance calculation according to (C.12)
// Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider.
// Appendix C
TProfile *hcov24[ncent];                // <2>*<4>
TProfile *hcov22prime[ncent][npt];      // <2>*<2'>
TProfile *hcov24prime[ncent][npt];      // <2>*<4'>
TProfile *hcov42prime[ncent][npt];      // <2>*<4'>
TProfile *hcov44prime[ncent][npt];      // <4>*<4'>
TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

void hVana::Booking(TString outFile)
{
  char name[800];
  char title[800];
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << outFile.Data() << " has been initialized" << endl;

  hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 2500, 0, 2500);
  hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 1500, 0, 1500, 200, 0., 20.);
  hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  hRP = new TH1F("hRP", "Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}", 300, 0., 7.);
  hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 300, 0., 7.);
  hPhil = new TH1F("hPhil", "Azimuthal angle distr in laboratory coordinate system; #phi; dN/d#phi", 300, 0., 7.);
  hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -2.2, 2.2);

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    sprintf(name, "hv2MC_cent%i", icent);
    sprintf(title, "v_{2}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv2MC[icent] = new TProfile(name, title, 1, 0., 1.);
    hv2MC[icent]->Sumw2();

    sprintf(name, "hv22_cent%i", icent);
    sprintf(title, "v_{2}{2}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv22[icent] = new TProfile(name, title, 1, 0., 1.);
    hv22[icent]->Sumw2();

    sprintf(name, "hv24_cent%i", icent);
    sprintf(title, "v_{2}{4}(cent), cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hv24[icent] = new TProfile(name, title, 1, 0., 1.);
    hv24[icent]->Sumw2();

    sprintf(name, "hcov24_cent%i", icent);
    sprintf(title, "<2>#upoint<4> distr, cent=%i-%i%%", bin_cent[icent] - 5, bin_cent[icent] + 5);
    hcov24[icent] = new TProfile(name, title, 1, 0., 1.);
    hcov24[icent]->Sumw2();

    for (int kpt = 0; kpt < npt; kpt++)
    { // loop over pt bin
      sprintf(name, "hpt_cent%i_pt%i", icent, kpt);
      sprintf(title, "p_{T} distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hpt[icent][kpt] = new TH1F(name, title, 300, 0.1, 9.2);

      sprintf(name, "hv2pt_cent%i_pt%i", icent, kpt);
      sprintf(title, "v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv2pt[icent][kpt] = new TH1F(name, title, 400, -1, 1);

      sprintf(name, "hPT_cent%i_pt%i", icent, kpt);
      sprintf(title, "p_{T} distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hPT[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hPT[icent][kpt]->Sumw2();

      sprintf(name, "hv2MCpt_cent%i_pt%i", icent, kpt);
      sprintf(title, "v_{2}{MC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv2MCpt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv2MCpt[icent][kpt]->Sumw2();

      sprintf(name, "hv22pt_cent%i_pt%i", icent, kpt);
      sprintf(title, "v_{2}{2,QC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv22pt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv22pt[icent][kpt]->Sumw2();

      sprintf(name, "hv24pt_cent%i_pt%i", icent, kpt);
      sprintf(title, "v_{2}{4,QC}(p_{T}), cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hv24pt[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hv24pt[icent][kpt]->Sumw2();

      sprintf(name, "hcov22prime_cent%i_pt%i", icent, kpt);
      sprintf(title, "<2>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov22prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov22prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov24prime_cent%i_pt%i", icent, kpt);
      sprintf(title, "<2>#upoint<4'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov24prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov24prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov42prime_cent%i_pt%i", icent, kpt);
      sprintf(title, "<4>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov42prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov42prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov44prime_cent%i_pt%i", icent, kpt);
      sprintf(title, "<4>#upoint<4'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov44prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov44prime[icent][kpt]->Sumw2();

      sprintf(name, "hcov2prime4prime_cent%i_pt%i", icent, kpt);
      sprintf(title, "<4'>#upoint<2'> distr, cent:%i-%i%%, %2.1f<pt<%2.1f GeV/c", bin_cent[icent] - 5, bin_cent[icent] + 5, bin_pT[kpt], bin_pT[kpt + 1]);
      hcov2prime4prime[icent][kpt] = new TProfile(name, title, 1, 0., 1.);
      hcov2prime4prime[icent][kpt]->Sumw2();
    } // end of loop over pt bin
  }   // end of loop over centrality classes

  cout << "Histograms have been initialized" << endl;
}

void hVana::Loop_a_file(TString file)
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
  Loop();
  treefile->Close();
  cout << file << " file processed" << endl;
}

void hVana::Ana_end()
{

  d_outfile->cd();
  d_outfile->Write();
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

void hVana::Loop()
{
  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
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

void hVana::Ana_event()
{
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
  // notation as (26) in DOI:10.1103/PhysRevC.83.044913

  // Q-vector of RFP
  Double_t Qx2 = 0, Qy2 = 0, Qx4 = 0, Qy4 = 0;
  TComplex Q2 = 0., Q4 = 0.;
  // p-vector of POI
  Double_t px2[npt] = {0.}, py2[npt] = {0.};
  TComplex p2[npt] = {0.}, p4[npt] = {0.}, q2[npt] = {0.}, q4[npt] = {0.};
  // q-vector of particles marked as POI and RFP, which is used for
  // autocorrelation substraction
  Double_t qx2[npt] = {0.}, qy2[npt] = {0.}, qx4[npt] = {0.}, qy4[npt] = {0.};
  // My RFP selection
  Double_t M = 0.;
  // numbers of POI (mp) and particles marked both POI and RFP (mq) are equal
  // due to my selection
  Double_t mq[npt] = {0.}, mp[npt] = {0.};
  // average reduced single-event 2- and 4-particle correlations
  Double_t redCor22[npt] = {0.}, redCor24[npt] = {0.};
  // event weights for correlation calculation
  Double_t w2 = 0., w4 = 0.;
  // event weights for reduced correlation calculation
  Double_t wred2[npt] = {0.}, wred4[npt] = {0.};
  // <2> & <4>
  Double_t cor22 = 0., cor24 = 0.;
  for (int i = 0; i < nh; i++)
  { // track loop
    Float_t pT = pt[i];
    if (pT < minpt || pT > maxpt) continue;
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
    if (bFlow[i]){
      Double_t v2 = TMath::Cos(2 * (phi0[i] - rp));
      // calculate reference v2 from MC toy
      if (eta[i] < -0.05) hv2MC[icent]->Fill(0.5, v2, 1);
      // Calculate differential v2 from MC toy
      hPT[icent][ipt]->Fill(0.5, pT, 1);
      hv2MCpt[icent][ipt]->Fill(0.5, v2, 1);
    }
    
    // RFP
    if (eta[i] < -0.05)
    {
      Qx2 += TMath::Cos(2 * phi0[i]);
      Qy2 += TMath::Sin(2 * phi0[i]);
      Qx4 += TMath::Cos(4 * phi0[i]);
      Qy4 += TMath::Sin(4 * phi0[i]);
      M++;
    }

    // POI
    if (eta[i] >= 0.05)
    {
      px2[ipt] += TMath::Cos(2 * phi0[i]);
      py2[ipt] += TMath::Sin(2 * phi0[i]);
      mp[ipt]++;
    }

    // qx2[ipt]+=TMath::Cos(2*phi0[i]);
    // qy2[ipt]+=TMath::Sin(2*phi0[i]);
    // mq[ipt]++;

  } // end of track loop
  if (M >= 2.)
  { // <2> definition condition
    Q2 = TComplex(Qx2, Qy2);
    w2 = M * (M - 1);                  // w(<2>)
    cor22 = CalCor22(Q2, M, w2);       // <2>
    hv22[icent]->Fill(0.5, cor22, w2); // <<2>>
  }                                    // end of <2> definition condition

  for (int ipt = 0; ipt < npt; ipt++)
  {
    if (mp[ipt] == 0 || M < 1)
      continue;
    p2[ipt] = TComplex(px2[ipt], py2[ipt]);
    q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
    // wred2[ipt] = mp[ipt]*M-mq[ipt];                                         // w(<2'>)
    wred2[ipt] = mp[ipt] * M;
    // redCor22[ipt] = CalRedCor22(Q2,p2[ipt],M,mp[ipt],mq[ipt],wred2[ipt]);   // <2'>
    redCor22[ipt] = CalRedCor22(Q2, p2[ipt], M, mp[ipt], 0, wred2[ipt]);
    hv22pt[icent][ipt]->Fill(0.5, redCor22[ipt], wred2[ipt]); // <<2'>>

    // TProfile for covariance calculation in statistic error
    hcov22prime[icent][ipt]->Fill(0.5, cor22 * redCor22[ipt], w2 * wred2[ipt]); // <2>*<2'>
  }

  if (M >= 4.)
  { // <4> definition condition
    Q4 = TComplex(Qx4, Qy4);
    w4 = M * (M - 1) * (M - 2) * (M - 3); // w(<4>)
    cor24 = CalCor24(Q2, Q4, M, w4);      // <4>
    hv24[icent]->Fill(0.5, cor24, w4);    // <<4>>

    // TProfile for covariance calculation in statistic error
    hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
  }                                                   // end of <4> definition condition
  for (int ipt = 0; ipt < npt; ipt++)
  {
    if (mp[ipt] == 0 || M < 3)
      continue;
    q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
    // wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);    // w(<4'>)
    wred4[ipt] = (mp[ipt] * M) * (M - 1.) * (M - 2.);
    // redCor24[ipt] = CalRedCor24(Q2,Q4,p2[ipt],q2[ipt],q4[ipt],M,mp[ipt],mq[ipt],wred4[ipt]);  // <4'>
    redCor24[ipt] = CalRedCor24(Q2, Q4, p2[ipt], 0, 0, M, mp[ipt], 0, wred4[ipt]); // <4'>

    hv24pt[icent][ipt]->Fill(0.5, redCor24[ipt], wred4[ipt]); // <<4'>>

    // TProfile for covariance calculation in statistic error
    hcov24prime[icent][ipt]->Fill(0.5, cor22 * redCor24[ipt], w2 * wred4[ipt]);
    hcov42prime[icent][ipt]->Fill(0.5, cor24 * redCor22[ipt], w4 * wred2[ipt]);
    hcov44prime[icent][ipt]->Fill(0.5, cor24 * redCor24[ipt], w4 * wred4[ipt]);
    hcov2prime4prime[icent][ipt]->Fill(0.5, redCor22[ipt] * redCor24[ipt], wred2[ipt] * wred4[ipt]);
  }
}
/*
void loop_a_list_of_trees()
{
  hVana *ana = new hVana();
  ana->Booking("/mnt/pool/2/lbavinh/DirectCumulant/OUT/v2QC_nonflow_etagap0.1.root");

  ifstream ifile("/mnt/pool/2/lbavinh/EventGenerator/OUT/Non-flowPairWise/runlist.list");
  char filename[200];
  int nfiles = 1;
  while (ifile.getline(filename, 200))
  {
    cout << nfiles << " file is processing " << filename << endl;
    ana->Loop_a_file(filename);
    nfiles++;
  }
  cout << "Done. " << nfiles - 1 << " files are processed." << endl;
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
*/
void loop_a_list_of_trees()
{
  hVana *ana = new hVana();
  ana->Booking("/weekly/nikolaev/lbavinh/DirectCumulant/OUT/v2QC_nonflow_etagap0.1.root");
  ana->Loop_a_file("/weekly/nikolaev/lbavinh/Generator/v2hadron_nonflow.root");
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}