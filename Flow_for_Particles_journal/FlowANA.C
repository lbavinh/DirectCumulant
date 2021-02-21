#define FlowANA_cxx
#include "FlowANA.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile3D.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TVector3.h"
#include "TDatabasePDG.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;
//List of histograms and Ntuples....
bool bFirstRun = 0;
static const Int_t neta = 9;
static const Int_t ndet = 5;
static const Int_t ncent = 9;
static const Int_t nth = 3;
static const Int_t npid = 4;

// List of MPD based cuts
static const Double_t MpdPtMin = 0.2;
static const Double_t MpdPtMax = 3.;
static const Double_t MpdEtaMin = -1.5;
static const Double_t MpdEtaGap = 0.05;
static const Double_t MpdEtaMax = 1.5;

// List of STAR based cuts (for 7.7 GeV)
static const Double_t StarVtxZ = 70.;
static const Double_t StarPtMin = 0.2;
static const Double_t StarPtMax = 2.0;
static const Double_t StarEtaMin = -1.;
static const Double_t StarEtaMax = 1.;
static const Double_t StarEtaGap = 0.05;
static const Double_t StarProtonPtMin = 0.4;
static const Double_t StarProtonPtMax = 2.0;
static const Double_t StarPionPtMin = 0.2;
static const Double_t StarPionPMax = 1.6;

static const Int_t npt = 15; // 0.5 - 3.6 GeV/c - number of pT bins
static const Double_t bin_w[15] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2};
const Double_t bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
const Int_t netaBin = 14;
const Double_t etaBin[netaBin+1] = {-1.5,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.,1.2,1.5};
static const Double_t maxpt = 4.0; // max pt
static const Double_t minpt = 0.2; // min pt

TH1F *hpt[ncent][npt][npid];
TH1F *hv2[ndet][ncent][npt][npid];
TH1F *hv1[ndet][ncent][npt][npid];
TH1F *hv22[ndet][npt][npid];
TH1F *hv12[ndet][npt][npid];
TProfile *pv2[ndet][ncent][npid];
TProfile *pv22[ndet][npid];
TProfile *pv1[ndet][ncent][npid];
TProfile *pv12[ndet][npid];
TProfile *pv1_y[ndet][ncent][npid];
TProfile *pv12_y[ndet][npid];
TProfile3D *prV2FHCalEventPlane;
TProfile *pV2FHCal;

TH1F *H_Qw[neta];
TH1F *H_EP[nth][neta];
TH1F *H_Qv[nth][neta];
TH1F *H_QvX[nth][neta];
TH1F *H_QvY[nth][neta];
TH1F *H_Phi[nth][neta];

TH1F *HRes[nth][ndet][ncent];
TProfile *prResFHCal;

// for centrality determination
TH1F *href1; // PHENIX BBC
TH1F *href2; // PHENIX RXN
TH1F *href3; // STAR TPC
TH1F *href4; // STAR ntracks>2
TH1F *href5; // STAR ntracks>4

TH1F *hbimp;  // impact parameter
TH1F *hbimp2; // impact parameter
TH1F *hbimp3; // impact parameter
TH1F *hbimp4; // impact parameter
TH1F *hbimp5; // impact parameter

TH1F *h2pt;
TH1F *h2eta;
TH1F *h2phi;
TH1F *h2phis;
TH1F *h2phirp;

static const Double_t MYPI = 3.141592654;

TFile *d_outfile;

void FlowANA::Loop()
{

  if (fChain == 0)
    return;

  Int_t nentries = Int_t(fChain->GetEntries());

  Int_t nbytes = 0, nb = 0;

  for (Int_t jentry = 0; jentry < nentries; jentry++)
  {

    Int_t ientry = LoadTree(jentry); //in case of a TChain, ientry is the entry number in the current file
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    if (jentry % 10000 == 0)
      cout << "Event [" << jentry << "/" << nentries << "]" << endl; // event counter

    ana_event(jentry, ientry);
  }
  cout << "const Double_t v2FHCal[" << ncent << "] = {";
  for (Int_t i = 0; i < ncent - 1; i++)
  {
    cout << pV2FHCal->GetBinContent(i + 1) << ", ";
  }
  cout << pV2FHCal->GetBinContent(ncent - 1) << "};" << endl;
}

void FlowANA::ana_init(const char *outfile)
{

  book_hist(outfile);
  gRandom->SetSeed((unsigned int)time(NULL));
}

void FlowANA::loop_a_file(const char *file)
{
  TFile *treefile = TFile::Open(file);
  TTree *tree = (TTree *)treefile->Get("mctree"); // put the name of the TTree
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
  cout << "one file processed" << endl;
}

void FlowANA::ana_end()
{
  d_outfile->cd();

  for (Int_t ieta = 0; ieta < neta; ieta++)
  {
    H_Qw[ieta]->Write();
  }

  for (Int_t ith = 0; ith < 3; ith++)
  {
    for (Int_t ieta = 0; ieta < neta; ieta++)
    {
      H_EP[ith][ieta]->Write();
      H_Qv[ith][ieta]->Write();
      H_QvX[ith][ieta]->Write();
      H_QvY[ith][ieta]->Write();
      H_Phi[ith][ieta]->Write();
    }
  }

  for (Int_t ith = 0; ith < 3; ith++)
  {
    for (Int_t idet = 0; idet < ndet; idet++)
    {
      for (Int_t icent = 0; icent < ncent; icent++)
      {

        HRes[ith][idet][icent]->Write();
      }
    }
  }

  for (Int_t icent = 0; icent < ncent; icent++)
  {
    for (Int_t ipt = 0; ipt < npt - 1; ipt++)
    {
      for (Int_t id = 0; id < npid; id++)
      {
        hpt[icent][ipt][id]->Write();
      }
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {
    for (Int_t icent = 0; icent < ncent; icent++)
    {
      for (Int_t ipt = 0; ipt < npt - 1; ipt++)
      {
        for (Int_t id = 0; id < npid; id++)
        {
          hv2[idet][icent][ipt][id]->Write();
          hv1[idet][icent][ipt][id]->Write();
        }
      }
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {
    for (Int_t icent = 0; icent < ncent; icent++)
    {
      for (Int_t id = 0; id < npid; id++)
      {
        pv2[idet][icent][id]->Write();
        pv1[idet][icent][id]->Write();
        pv1_y[idet][icent][id]->Write();
      }
    }
  }
  for (Int_t idet = 0; idet < ndet; idet++)
  {
    for (Int_t id = 0; id < npid; id++)
    {
      pv22[idet][id]->Write();
      pv12[idet][id]->Write();
      pv12_y[idet][id]->Write();
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {

    for (Int_t ipt = 0; ipt < npt - 1; ipt++)
    {

      for (Int_t id = 0; id < npid; id++)
      {

        hv22[idet][ipt][id]->Write();
        hv12[idet][ipt][id]->Write();
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
  prV2FHCalEventPlane->Write();
  prResFHCal->Write();
  d_outfile->Close();

} // end of ana_end

void FlowANA::book_hist(const char *outfile)
{
  d_outfile = new TFile(outfile, "recreate");

  h2eta = new TH1F("h2eta", "eta distribution", 200, -7, 7);
  h2pt = new TH1F("h2pt", "pt distribution", 200, 0, 10.0);

  href1 = new TH1F("href1", "Centrality by BBC (PHENIX)", 1000, 0, 1000);
  href2 = new TH1F("href2", "Centrality by BBC (PHENIX)", 1000, 0, 1000);
  href3 = new TH1F("href3", "Centrality by TPC (STAR)", 1000, 0, 1000);
  href4 = new TH1F("href4", "Centrality by TPC (STAR), ntracks >1", 1000, 0, 1000);
  href5 = new TH1F("href5", "Centrality by TPC (STAR), ntracks >2", 1000, 0, 1000);

  hbimp2 = new TH1F("hbimp2", "Imact Parameter", 180, 0, 18);
  hbimp3 = new TH1F("hbimp3", "Imact Parameter", 180, 0, 18);
  hbimp4 = new TH1F("hbimp4", "Imact Parameter", 180, 0, 18);
  hbimp5 = new TH1F("hbimp5", "Imact Parameter", 180, 0, 18);

  hbimp = new TH1F("hbimp", "Imact Parameter", 180, 0, 18);

  h2phi = new TH1F("h2phi", "azim. angle", 100, -TMath::Pi(), TMath::Pi() + 2. * TMath::Pi() / 100);
  h2phis = new TH1F("h2phis", "azim. angle (|eta| <0.5)", 100, -TMath::Pi(), TMath::Pi() + 2. * TMath::Pi() / 100);
  h2phirp = new TH1F("h2phirp", "azim. angle", 100, -TMath::Pi(), TMath::Pi() + 2. * TMath::Pi() / 100);

  for (Int_t ieta = 0; ieta < neta; ieta++)
    H_Qw[ieta] = new TH1F(Form("H_Qw_%d", ieta), Form("H_Qw_%d", ieta), 100, 0, 1000);

  for (Int_t ith = 0; ith < 3; ith++)
  {
    for (Int_t ieta = 0; ieta < neta; ieta++)
    {
      H_EP[ith][ieta] = new TH1F(Form("H_EP_%d_%d", ith, ieta), Form("H_EP_%d_%d", ith, ieta), 372, -TMath::Pi() / (ith + 1.) - 0.1, TMath::Pi() / (ith + 1.) + 0.10);
      H_Phi[ith][ieta] = new TH1F(Form("H_Phi_%d_%d", ith, ieta), Form("H_Phi_%d_%d", ith, ieta), 372, -TMath::Pi() / (ith + 1.) - 0.1, TMath::Pi() / (ith + 1.) + 0.10);
      H_Qv[ith][ieta] = new TH1F(Form("H_Qv_%d_%d", ith, ieta), Form("H_Qv_%d_%d", ith, ieta), 100, 0, 10);
      H_QvX[ith][ieta] = new TH1F(Form("H_QvX_%d_%d", ith, ieta), Form("H_QvX_%d_%d", ith, ieta), 200, -10, 10);
      H_QvY[ith][ieta] = new TH1F(Form("H_QvY_%d_%d", ith, ieta), Form("H_QvY_%d_%d", ith, ieta), 200, -10, 10);
    }
  }

  for (Int_t ith = 0; ith < 3; ith++)
  {
    for (Int_t idet = 0; idet < ndet; idet++)
    {
      for (Int_t icent = 0; icent < ncent; icent++)
      {
        HRes[ith][idet][icent] = new TH1F(Form("HRes_%d_%d_%d", ith, idet, icent), Form("HRes_%d_%d_%d", ith, idet, icent), 300, -20, 20);
      }
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {
    for (Int_t icent = 0; icent < ncent; icent++)
    {

      for (Int_t ipt = 0; ipt < npt - 1; ipt++)
      {

        for (Int_t id = 0; id < npid; id++)
        {

          hv2[idet][icent][ipt][id] = new TH1F(Form("hv2_%d_%d_%d_%d", idet, icent, ipt, id), Form("hv2_%d_%d_%d_%d", idet, icent, ipt, id), 400, -10, 10);
          hv1[idet][icent][ipt][id] = new TH1F(Form("hv1_%d_%d_%d_%d", idet, icent, ipt, id), Form("hv1_%d_%d_%d_%d", idet, icent, ipt, id), 400, -10, 10);
        }
      }
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {
    for (Int_t icent = 0; icent < ncent; icent++)
    {

      for (Int_t id = 0; id < npid; id++)
      {

        pv2[idet][icent][id] = new TProfile(Form("pv2_%d_%d_%d", idet, icent, id), Form("pv2_%d_%d_%d", idet, icent, id), 50, 0., 5.);
        pv1[idet][icent][id] = new TProfile(Form("pv1_%d_%d_%d", idet, icent, id), Form("pv1_%d_%d_%d", idet, icent, id), 50, 0., 5.);
        pv1_y[idet][icent][id] = new TProfile(Form("pv1_y_%d_%d_%d", idet, icent, id), Form("pv1_y_%d_%d_%d", idet, icent, id), 100, -5., 5.);
      }
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {

    for (Int_t ipt = 0; ipt < npt - 1; ipt++)
    {

      for (Int_t id = 0; id < npid; id++)
      {

        hv22[idet][ipt][id] = new TH1F(Form("hv22_%d_%d_%d", idet, ipt, id), Form("hv22_%d_%d_%d", idet, ipt, id), 400, -10, 10);
        hv12[idet][ipt][id] = new TH1F(Form("hv12_%d_%d_%d", idet, ipt, id), Form("hv12_%d_%d_%d", idet, ipt, id), 400, -10, 10);
      }
    }
  }

  for (Int_t idet = 0; idet < ndet; idet++)
  {
    for (Int_t id = 0; id < npid; id++)
    {

      pv22[idet][id] = new TProfile(Form("pv22_%d_%d", idet, id), Form("pv22_%d_%d", idet, id), 50, 0., 5.);
      pv12[idet][id] = new TProfile(Form("pv12_%d_%d", idet, id), Form("pv12_%d_%d", idet, id), 50, 0., 5.);
      pv12_y[idet][id] = new TProfile(Form("pv12_y_%d_%d", idet, id), Form("pv12_y_%d_%d", idet, id), 100, -5., 5.);
    }
  }

  for (Int_t icent = 0; icent < ncent; icent++)
  {

    for (Int_t ipt = 0; ipt < npt - 1; ipt++)
    {

      for (Int_t id = 0; id < npid; id++)
      {

        hpt[icent][ipt][id] = new TH1F(Form("hpt_%d_%d_%d", icent, ipt, id), Form("hpt_%d_%d_%d", icent, ipt, id), 400, 0, 10);
      }
    }
  }

  prV2FHCalEventPlane = new TProfile3D("prV2FHCalEventPlane", "", ncent, &bin_cent[0], npt, &bin_w[0], netaBin, &etaBin[0]);
  prResFHCal = new TProfile("prResFHCal", "", ncent, 0., ncent);
  pV2FHCal = new TProfile("pV2FHCal","",ncent,0,ncent);
}

// Analysis for each event !!!!

void FlowANA::ana_event(Int_t jentry, Int_t ientry)
{

  //Double_t phiRP = gRandom->Uniform(0, 2.*TMath::Pi());

  // Double_t phiRP = gRandom->Uniform(-1.0*TMath::Pi(),TMath::Pi());
  //h2phirp->Fill(phiRP);

  // centrality cut and vertex +/- 30 cm cut

  //if(ientry%100000==0) cout << ientry <<endl;// event counter

  Double_t sumQxy[3][9][2] = {{{0}}}; //[ith][eta][x,y]
  //Double_t sumQxyFull[3][2] = {{{0}}};
  Double_t multQv[9] = {0}; //[eta]
  Double_t fhcalFullEP_x = 0.;
  Double_t fhcalFullEP_y = 0.;
  Double_t fhcalFullEP_phi = 0.;

  hbimp->Fill(bimp);

  Double_t refMult1 = 0;
  Double_t refMult2 = 0;

  Double_t Nch_L = 0;
  Double_t Nch_R = 0;

  Double_t Nch_L2 = 0;
  Double_t Nch_R2 = 0;

  for (Int_t itrk = 0; itrk < nh; itrk++)
  { //track loop

    //        Double_t pt  = sqrt( TMath::Power(momx[itrk], 2.0 ) + TMath::Power(momy[itrk], 2.0 ) );

    //	Double_t oldphi = atan2( momy[itrk], momx[itrk] );
    //	Double_t phi=oldphi;

    //	Double_t the = atan2( pt, momz[itrk] );//atan2(pt/pz)
    //	Double_t eta = -TMath::Log( TMath::Tan( 0.5 * the ) );
    TVector3 vect(momx[itrk], momy[itrk], momz[itrk]);
    Double_t pt = vect.Pt();
    Double_t eta = vect.Eta();
    Double_t phi = vect.Phi();
    Double_t ch;
    if (TDatabasePDG::Instance()->GetParticle(pdg[itrk]))
      ch = 1. / 3. * TDatabasePDG::Instance()->GetParticle(pdg[itrk])->Charge();
    else
      ch = -999.;
    //	phi += phiRP;
    // Double_t px = pt * cos(phi);
    //	Double_t py = pt * sin(phi);
    //	pt  = sqrt( TMath::Power(px, 2.0 ) + TMath::Power(py, 2.0 ) );

    h2pt->Fill(pt);
    h2eta->Fill(eta);
    //            h2phi->Fill(oldphi);
    h2phis->Fill(phi);

    if (pt > 0.1 && fabs(eta) < 0.5)
      refMult1++;
    if (pt > 0.0 && fabs(eta) < 0.5)
      refMult2++;
    if (eta >= 3.1 && eta <= 4.0)
      Nch_R++;
    if (eta >= -4.0 && eta <= -3.1)
      Nch_L++;
    Bool_t bTPC = 1;
    // if( pt<0.15  || pt>2. ) continue;
    if (pt < MpdPtMin || pt > MpdPtMax)
      bTPC = 0;
    // if ( pt<StarPtMin || pt>StarPtMax ) continue;

    Int_t fEta = -1;

    // TPC plane
    if (eta > -1 && eta < -0.1)
      fEta = 0; // TPC East
    if (eta > 0.1 && eta < 1)
      fEta = 1; // TPC West
    if (fabs(eta) < 0.1)
      fEta = 2; // TPC Mid

    // RXN plane
    if (eta > -3.0 && eta < -1.0)
      fEta = 3; // RXN East
    if (eta > 1.0 && eta < 3.0)
      fEta = 4; // RXN West

    // BBC plane
    //if( eta>-5 && eta<-3 )      fEta = 5; //East
    //if( eta>3.0 && eta<5  )     fEta = 6; //West

    // FHCal plane
    if (eta > -5.0 && eta < -2.0)
      fEta = 7; //East
    if (eta > 2.0 && eta < 5.0)
      fEta = 8; //West

    // BBC plane - first harmonic
    //if( eta>-5.0 && eta<-3.3 )      fEta = 7; //East
    //if( eta>3.3 && eta<5.0  )     fEta = 8; //West

    // if( fabs(eta)>1.1 && fabs(eta)<2.9 )     fEta = 7; // RXN combined
    //if( fabs(eta)>3.0 && fabs(eta)<5.0 )     fEta = 8; // BBC combined

    if (fEta > -1.)
      H_Phi[0][fEta]->Fill(phi);

    if (fEta < 3 && (ch == 0 || ch == -999.))
      continue;

    if (fEta > -1.)
    {
      for (Int_t ith = 0; ith < 3; ith++)
      {
        if (fEta < 7)
        {
          if (bTPC)
          {
            sumQxy[ith][fEta][0] += pt * TMath::Cos((ith + 2.0) * phi);
            sumQxy[ith][fEta][1] += pt * TMath::Sin((ith + 2.0) * phi);

          }
        }
        else
        {
          if (fEta == 7)
          {
            sumQxy[ith][fEta][0] += -1. * pt * TMath::Cos((ith + 1.0) * phi);
            sumQxy[ith][fEta][1] += -1. * pt * TMath::Sin((ith + 1.0) * phi);
          }
          if (fEta == 8)
          {
            sumQxy[ith][fEta][0] += 1. * pt * TMath::Cos((ith + 1.0) * phi);
            sumQxy[ith][fEta][1] += 1. * pt * TMath::Sin((ith + 1.0) * phi);
          }
        }
        //if(fEta == 7 || fEta == 8){
        //	sumQxyFull[ith][0] += pt * cos( (ith+1.0) * phi );
        //	sumQxyFull[ith][1] += pt * sin( (ith+1.0) * phi );
        //}
      }
      multQv[fEta]++;
    } // end of eta selection

  } // end of track loop

  if (Nch_L >= 1 && Nch_R >= 1)
  {
    href1->Fill(Nch_L + Nch_R);
  }

  if (Nch_L >= 2 && Nch_R >= 2)
  {
    href2->Fill(Nch_L + Nch_R);
    hbimp2->Fill(bimp);
  }
  if (refMult1 > 0)
  {
    href3->Fill(refMult1);
    hbimp3->Fill(bimp);
  }

  if (refMult2 > 0)
  {
    href4->Fill(refMult1);
    hbimp4->Fill(bimp);
  }

  if (refMult1 > 2)
  {
    href5->Fill(refMult1);
    hbimp5->Fill(bimp);
  }

  Double_t sumLR = Nch_L + Nch_R;

  // Int_t fCent   = GetCentrality10_RefMult( refMult1 );// STAR def
  //if( fCent<0 ) cout << fCent << endl;

  // Int_t fCent   =  GetCentrality10_RefMultPHENIX(sumLR);

  Int_t fCent = GetCentrality10_Bimp(bimp);
  Double_t dCent = CentB(bimp);
  //Int_t fCent   =  GetCentrality10_BimpExp(bimp);

  Double_t fEP[3][9];  //[ith][eta]
  Double_t fQv[3][9];  //[ith][eta]
  Double_t fQvX[3][9]; //[ith][eta]
  Double_t fQvY[3][9]; //[ith][eta]
  for (Int_t ith = 0; ith < 3; ith++)
  { // flow harmonic loop
    for (Int_t ieta = 0; ieta < 9; ieta++)
    { // ep detector gap
      if (multQv[ieta] > 5)
      { // multiplicity > 5
        if (ieta < 7)
        {
          fEP[ith][ieta] = atan2(sumQxy[ith][ieta][1], sumQxy[ith][ieta][0]) / (ith + 2.0);
          fEP[ith][ieta] = atan2(sin((ith + 2.0) * fEP[ith][ieta]), cos((ith + 2.0) * fEP[ith][ieta]));
          fEP[ith][ieta] /= (ith + 2.0);
        }
        else
        {
          fEP[ith][ieta] = atan2(sumQxy[ith][ieta][1], sumQxy[ith][ieta][0]) / (ith + 1.0);
          //	fEP[ith][ieta] = atan2( sin( (ith+1.0)*fEP[ith][ieta] ), cos( (ith+1.0)*fEP[ith][ieta] ) );
          //	fEP[ith][ieta] /= ( ith + 1.0 );
        }
        fQv[ith][ieta] = sqrt(TMath::Power(sumQxy[ith][ieta][0], 2.0) + TMath::Power(sumQxy[ith][ieta][1], 2.0)) / sqrt(multQv[ieta]);
        fQvX[ith][ieta] = sumQxy[ith][ieta][0] / sqrt(multQv[ieta]);
        fQvY[ith][ieta] = sumQxy[ith][ieta][1] / sqrt(multQv[ieta]);
        H_Qw[ieta]->Fill(multQv[ieta]);
      }
      else
      {
        fEP[ith][ieta] = -9999;
        fQv[ith][ieta] = -9999;
        fQvX[ith][ieta] = -9999;
        fQvY[ith][ieta] = -9999;
      } // end of mult cut selection
    }   // end of loop on EP detectors
  }     // end of flow harmonic loop
  fhcalFullEP_x = sumQxy[0][7][0] + sumQxy[0][8][0];
  fhcalFullEP_y = sumQxy[0][7][1] + sumQxy[0][8][1];
  fhcalFullEP_phi = atan2(fhcalFullEP_y, fhcalFullEP_x);

  for (Int_t ith = 0; ith < 3; ith++)
  { // harmonic loop
    for (Int_t ieta = 0; ieta < 9; ieta++)
    { // eta EP detector loop
      if (fEP[ith][ieta] > -9000)
      { // EP reconstructed
        H_EP[ith][ieta]->Fill(fEP[ith][ieta]);
        H_Qv[ith][ieta]->Fill(fQv[ith][ieta]);
        H_QvX[ith][ieta]->Fill(fQvX[ith][ieta]);
        H_QvY[ith][ieta]->Fill(fQvY[ith][ieta]);
      } // end of EP reconstructed
    }   // end of eta loop
  }     // end of harm loop

  //Resolution
  for (Int_t ith = 0; ith < 3; ith++)
  {
    for (Int_t icb = 0; icb < 4; icb++)
    {
      Double_t psi1, psi2, fq1, fq2, HarmStart = 2.;

      if (icb == 0)
      {
        psi1 = fEP[ith][0];
        psi2 = fEP[ith][1];
        fq1 = fQv[ith][0];
        fq2 = fQv[ith][1];
      } // TPC.E-TPC.W
      else if (icb == 1)
      {
        psi1 = fEP[ith][3];
        psi2 = fEP[ith][4];
        fq1 = fQv[ith][3];
        fq2 = fQv[ith][4];
      } // RXN.E-RXN.W
      else if (icb == 2)
      {
        psi1 = fEP[ith][5];
        psi2 = fEP[ith][6];
        fq1 = fQv[ith][5];
        fq2 = fQv[ith][6];
      } // BBC.E-BBC.W
      else
      {
        psi1 = fEP[ith][7];
        psi2 = fEP[ith][8];
        fq1 = fQv[ith][7];
        fq2 = fQv[ith][8];
        HarmStart = 1.;
      } // FHCal.E-FHCal.W

      if (psi1 < -9000 || psi2 < -9000)
        continue;
      //			if( fq1<0 || fq2<0 ) continue;

      Double_t dPsi = (ith + HarmStart) * (psi1 - psi2);
      // dPsi = atan2( sin(dPsi), cos(dPsi) );
      if (fCent > -1 && fCent < ncent)
      {
        if (ith==0 && icb==3) prResFHCal->Fill(fCent, TMath::Cos(dPsi));
        HRes[ith][icb][fCent]->Fill(TMath::Cos(dPsi));
      }
    }
  }

  if (bFirstRun) return;
  // 7.7 gev
  
  Double_t res2tpc[9] = {0.215422, 0.319671, 0.321595, 0.286121, 0.230794, 0.187664, 0.169983, 0.180262, 0.};
  Double_t res2rxn[9] = {0.174276, 0.278904, 0.284986, 0.235424, 0.182337, 0.145134, 0.136635, 0.154262, 0.};
  Double_t res2bbc[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  Double_t res2fhcal[9] = {0.21303, 0.451618, 0.525957, 0.527378, 0.486444, 0.413006, 0.317347, 0.220505, 0.};
  //Double_t res2fhcalFull[9] = {0.222354, 0.476169, 0.632075, 0.683942, 0.659132, 0.581878, 0.450756, 0.289863, 0.154283};
  Double_t res1fhcalFull[9] = {0.710235, 0.887721, 0.915807, 0.916269, 0.901899, 0.869522, 0.809946, 0.719049, 0.};
  Double_t res2fhcalFull[9] = {0.0577404,0.135084,0.164236,0.18023,0.147677,0.141475,0.102279,0.0789313,0.0740087};
  if (fCent >= 0 && fCent < ncent)
  {

    Double_t phiRP = 0.; // True RP plane angle

    for (Int_t itrk = 0; itrk < nh; itrk++)
    { //track loop
      TVector3 vect(momx[itrk], momy[itrk], momz[itrk]);
      Double_t pt = vect.Pt();
      Double_t eta = vect.Eta();
      Double_t phi = vect.Phi();
      // Double_t pt = sqrt(TMath::Power(momx[itrk], 2.0) + TMath::Power(momy[itrk], 2.0));
      // Double_t p = sqrt(TMath::Power(pt, 2.0) + TMath::Power(momz[itrk], 2.0));

      // Double_t oldphi = atan2(momy[itrk], momx[itrk]);
      // Double_t phi = oldphi;
      Double_t dphiRP = atan2(momy[itrk], momx[itrk]) - phiRP;
      Double_t oldphiV1 = atan2(momy[itrk], momx[itrk]);
      Double_t phiV1 = atan2(sin(oldphiV1), cos(oldphiV1));

      // Double_t the = atan2(pt, momz[itrk]); //atan2(pt/pz)
      // Double_t eta = -log(tan(0.5 * the));
      Double_t rapidity = 0.5 * log((ene[itrk] + momz[itrk]) / (ene[itrk] - momz[itrk]));

      Double_t ch;
      if (TDatabasePDG::Instance()->GetParticle(pdg[itrk]))
        ch = 1. / 3. * TDatabasePDG::Instance()->GetParticle(pdg[itrk])->Charge();
      else
        ch = -999.;
      if (pt < MpdPtMin || pt > MpdPtMax)
        continue;
      //if ( pt<StarPtMin || pt>StarPtMax ) continue;
      //if ( eta<MpdEtaMin || eta>MpdEtaMax ) continue;
      if (ch == 0 || ch == -999.)
        continue;

      Int_t ipt = 0;
      for (Int_t i = 0; i < npt - 1; i++)
      {
        if (pt >= bin_w[i] && pt < bin_w[i + 1])
          ipt = i;
      } // end of ipt loop

      Double_t v2tpc = -999.0;
      Double_t v2rxn = -999.0;
      Double_t v2bbc = -999.0;
      Double_t v2fhcal = -999.0;
      Double_t v2fhcalFull = -999.0;
      Double_t v1fhcalFull = -999.0;
      Double_t v2RP = -999.0;
      Double_t v1RP = -999.0;
      if (fEP[0][7]!=-9999 && fEP[0][8]!=-9999 && fabs(eta) < MpdEtaMax)
      {
        v2fhcalFull = TMath::Cos(2.0 * (phi - fhcalFullEP_phi)) / res2fhcalFull[fCent];
        prV2FHCalEventPlane->Fill(dCent, pt, eta, v2fhcalFull);
        pV2FHCal->Fill(fCent,v2fhcalFull);
      }
      if (eta > MpdEtaGap && eta < MpdEtaMax)
      {
        v2tpc = cos(2.0 * (phi - fEP[0][0])) / res2tpc[fCent];
        v2rxn = cos(2.0 * (phi - fEP[0][3])) / res2rxn[fCent];
        v2bbc = cos(2.0 * (phi - fEP[0][5])) / res2bbc[fCent];
        v2fhcal = cos(2.0 * (phi - fEP[0][7])) / res2fhcal[fCent];
        // v2fhcalFull = TMath::Cos(2.0 * (phi - fhcalFullEP_phi)) / res2fhcalFull[fCent];
        v2RP = cos(2.0 * (dphiRP));
        v1fhcalFull = 1.0 * cos(1.0 * (phiV1 - fhcalFullEP_phi)) / res1fhcalFull[fCent];
        v1RP = 1.0 * cos(1.0 * (dphiRP));
      }

      if (eta < -1. * MpdEtaGap && eta > MpdEtaMin)
      {
        v2tpc = cos(2.0 * (phi - fEP[0][1])) / res2tpc[fCent];
        v2rxn = cos(2.0 * (phi - fEP[0][4])) / res2rxn[fCent];
        v2bbc = cos(2.0 * (phi - fEP[0][6])) / res2bbc[fCent];
        v2fhcal = cos(2.0 * (phi - fEP[0][8])) / res2fhcal[fCent];
        // v2fhcalFull = TMath::Cos(2.0 * (phi - fhcalFullEP_phi)) / res2fhcalFull[fCent];
        v2RP = cos(2.0 * (dphiRP));
        v1fhcalFull = -1.0 * cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent];
        v1RP = -1.0 * cos(1.0 * (dphiRP));
      }

      if (fabs(eta) > MpdEtaGap && fabs(eta) < MpdEtaMax)
      {
        hv2[0][fCent][ipt][0]->Fill(v2tpc);
        hv2[1][fCent][ipt][0]->Fill(v2rxn);
        hv2[2][fCent][ipt][0]->Fill(v2bbc);
        hv2[3][fCent][ipt][0]->Fill(v2fhcalFull);
        hv2[4][fCent][ipt][0]->Fill(v2RP);
        hv1[3][fCent][ipt][0]->Fill(v1fhcalFull);
        hv1[4][fCent][ipt][0]->Fill(v1RP);
        if (v2tpc != -999.)
          pv2[0][fCent][0]->Fill(pt, v2tpc);
        if (v2rxn != -999.)
          pv2[1][fCent][0]->Fill(pt, v2rxn);
        if (v2bbc != -999.)
          pv2[2][fCent][0]->Fill(pt, v2bbc);
        //if (v2fhcal!=-999.)  pv2[3][fCent][0]->Fill(pt,v2fhcal);
        if (v2fhcalFull != -999.)
          pv2[3][fCent][0]->Fill(pt, v2fhcalFull);
        if (v2RP != -999.)
          pv2[4][fCent][0]->Fill(pt, v2RP);
        if (v1fhcalFull != -999.)
          pv1[3][fCent][0]->Fill(pt, v1fhcalFull);
        if (v1RP != -999.)
          pv1[4][fCent][0]->Fill(pt, v1RP);
        if (v1fhcalFull != -999.)
          pv1[3][fCent][0]->Fill(pt, v1fhcalFull);
        if (v1RP != -999.)
          pv1[4][fCent][0]->Fill(pt, v1RP);

        //std::cout << "v2TPC " << v2tpc << "; v2RP " << v2RP << std::endl;
        //cos(1.0 * (phi-fhcalFullEP_phi) )/res1fhcalFull[fCent]
        hpt[fCent][ipt][0]->Fill(pt);

        if (fCent > 0 && fCent < 4)
        {

          hv22[0][ipt][0]->Fill(v2tpc);
          hv22[1][ipt][0]->Fill(v2rxn);
          hv22[2][ipt][0]->Fill(v2bbc);
          hv22[3][ipt][0]->Fill(v2fhcalFull);
          hv22[4][ipt][0]->Fill(v2RP);
          hv12[3][ipt][0]->Fill(v1fhcalFull);
          hv12[4][ipt][0]->Fill(v1RP);
          if (v2tpc != -999.)
            pv22[0][0]->Fill(pt, v2tpc);
          if (v2rxn != -999.)
            pv22[1][0]->Fill(pt, v2rxn);
          if (v2bbc != -999.)
            pv22[2][0]->Fill(pt, v2bbc);
          //if (v2fhcal!=-999.)  pv22[3][0]->Fill(pt,v2fhcal);
          if (v2fhcalFull != -999.)
            pv22[3][0]->Fill(pt, v2fhcalFull);
          if (v2RP != -999.)
            pv22[4][0]->Fill(pt, v2RP);
          if (v1fhcalFull != -999.)
            pv12[3][0]->Fill(pt, v1fhcalFull);
          if (v1RP != -999.)
            pv12[4][0]->Fill(pt, v1RP);
        }

        if (pdg[itrk] == 211)
        {
          hv2[0][fCent][ipt][1]->Fill(v2tpc);
          hv2[1][fCent][ipt][1]->Fill(v2rxn);
          hv2[2][fCent][ipt][1]->Fill(v2bbc);
          hv2[3][fCent][ipt][1]->Fill(v2fhcalFull);
          hv2[4][fCent][ipt][1]->Fill(v2RP);
          hv1[3][fCent][ipt][1]->Fill(v1fhcalFull);
          hv1[4][fCent][ipt][1]->Fill(v1RP);
          if (v2tpc != -999.)
            pv2[0][fCent][1]->Fill(pt, v2tpc);
          if (v2rxn != -999.)
            pv2[1][fCent][1]->Fill(pt, v2rxn);
          if (v2bbc != -999.)
            pv2[2][fCent][1]->Fill(pt, v2bbc);
          //if (v2fhcal!=-999.)  pv2[3][fCent][1]->Fill(pt,v2fhcal);
          if (v2fhcalFull != -999.)
            pv2[3][fCent][1]->Fill(pt, v2fhcalFull);
          if (v2RP != -999.)
            pv2[4][fCent][1]->Fill(pt, v2RP);
          if (v1fhcalFull != -999.)
            pv1[3][fCent][1]->Fill(pt, v1fhcalFull);
          if (v1RP != -999.)
            pv1[4][fCent][1]->Fill(pt, v1RP);
          hpt[fCent][ipt][1]->Fill(pt);

          if (fCent > 0 && fCent < 4)
          {

            hv22[0][ipt][1]->Fill(v2tpc);
            hv22[1][ipt][1]->Fill(v2rxn);
            hv22[2][ipt][1]->Fill(v2bbc);
            hv22[3][ipt][1]->Fill(v2fhcalFull);
            hv22[4][ipt][1]->Fill(v2RP);
            hv12[3][ipt][1]->Fill(v1fhcalFull);
            hv12[4][ipt][1]->Fill(v1RP);
            if (v2tpc != -999.)
              pv22[0][1]->Fill(pt, v2tpc);
            if (v2rxn != -999.)
              pv22[1][1]->Fill(pt, v2rxn);
            if (v2bbc != -999.)
              pv22[2][1]->Fill(pt, v2bbc);
            //if (v2fhcal!=-999.)  pv22[3][1]->Fill(pt,v2fhcal);
            if (v2fhcalFull != -999.)
              pv22[3][1]->Fill(pt, v2fhcalFull);
            if (v2RP != -999.)
              pv22[4][1]->Fill(pt, v2RP);
            if (v1fhcalFull != -999.)
              pv12[3][1]->Fill(pt, v1fhcalFull);
            if (v1RP != -999.)
              pv12[4][1]->Fill(pt, v1RP);
          }

        } // end of pion selection

        if (pdg[itrk] == 321)
        {
          hv2[0][fCent][ipt][2]->Fill(v2tpc);
          hv2[1][fCent][ipt][2]->Fill(v2rxn);
          hv2[2][fCent][ipt][2]->Fill(v2bbc);
          hv2[3][fCent][ipt][2]->Fill(v2fhcalFull);
          hv2[4][fCent][ipt][2]->Fill(v2RP);
          hv1[3][fCent][ipt][2]->Fill(v1fhcalFull);
          hv1[4][fCent][ipt][2]->Fill(v1RP);
          if (v2tpc != -999.)
            pv2[0][fCent][2]->Fill(pt, v2tpc);
          if (v2rxn != -999.)
            pv2[1][fCent][2]->Fill(pt, v2rxn);
          if (v2bbc != -999.)
            pv2[2][fCent][2]->Fill(pt, v2bbc);
          //if (v2fhcal!=-999.)  pv2[3][fCent][2]->Fill(pt,v2fhcal);
          if (v2fhcalFull != -999.)
            pv2[3][fCent][2]->Fill(pt, v2fhcalFull);
          if (v2RP != -999.)
            pv2[4][fCent][2]->Fill(pt, v2RP);
          if (v1fhcalFull != -999.)
            pv1[3][fCent][2]->Fill(pt, v1fhcalFull);
          if (v1RP != -999.)
            pv1[4][fCent][2]->Fill(pt, v1RP);
          hpt[fCent][ipt][2]->Fill(pt);

          if (fCent > 0 && fCent < 4)
          {

            hv22[0][ipt][2]->Fill(v2tpc);
            hv22[1][ipt][2]->Fill(v2rxn);
            hv22[2][ipt][2]->Fill(v2bbc);
            hv22[3][ipt][2]->Fill(v2fhcalFull);
            hv22[4][ipt][2]->Fill(v2RP);
            hv12[3][ipt][2]->Fill(v1fhcalFull);
            hv12[4][ipt][2]->Fill(v1RP);
            if (v2tpc != -999.)
              pv22[0][2]->Fill(pt, v2tpc);
            if (v2rxn != -999.)
              pv22[1][2]->Fill(pt, v2rxn);
            if (v2bbc != -999.)
              pv22[2][2]->Fill(pt, v2bbc);
            //if (v2fhcal!=-999.)  pv22[3][2]->Fill(pt,v2fhcal);
            if (v2fhcalFull != -999.)
              pv22[3][2]->Fill(pt, v2fhcalFull);
            if (v2RP != -999.)
              pv22[4][2]->Fill(pt, v2RP);
            if (v1fhcalFull != -999.)
              pv12[3][2]->Fill(pt, v1fhcalFull);
            if (v1RP != -999.)
              pv12[4][2]->Fill(pt, v1RP);
          }

        } // end of kaon selection

        if (pdg[itrk] == 2212)
        {
          hv2[0][fCent][ipt][3]->Fill(v2tpc);
          hv2[1][fCent][ipt][3]->Fill(v2rxn);
          hv2[2][fCent][ipt][3]->Fill(v2bbc);
          hv2[3][fCent][ipt][3]->Fill(v2fhcalFull);
          hv2[4][fCent][ipt][3]->Fill(v2RP);
          hv1[3][fCent][ipt][3]->Fill(v1fhcalFull);
          hv1[4][fCent][ipt][3]->Fill(v1RP);
          if (v2tpc != -999.)
            pv2[0][fCent][3]->Fill(pt, v2tpc);
          if (v2rxn != -999.)
            pv2[1][fCent][3]->Fill(pt, v2rxn);
          if (v2bbc != -999.)
            pv2[2][fCent][3]->Fill(pt, v2bbc);
          //if (v2fhcal!=-999.)  pv2[3][fCent][3]->Fill(pt,v2fhcal);
          if (v2fhcalFull != -999.)
            pv2[3][fCent][3]->Fill(pt, v2fhcalFull);
          if (v2RP != -999.)
            pv2[4][fCent][3]->Fill(pt, v2RP);
          if (v1fhcalFull != -999.)
            pv1[3][fCent][3]->Fill(pt, v1fhcalFull);
          if (v1RP != -999.)
            pv1[4][fCent][3]->Fill(pt, v1RP);
          hpt[fCent][ipt][3]->Fill(pt);

          if (fCent > 0 && fCent < 4)
          {

            hv22[0][ipt][3]->Fill(v2tpc);
            hv22[1][ipt][3]->Fill(v2rxn);
            hv22[2][ipt][3]->Fill(v2bbc);
            hv22[3][ipt][3]->Fill(v2fhcalFull);
            hv22[4][ipt][3]->Fill(v2RP);
            hv12[3][ipt][3]->Fill(v1fhcalFull);
            hv12[4][ipt][3]->Fill(v1RP);
            if (v2tpc != -999.)
              pv22[0][3]->Fill(pt, v2tpc);
            if (v2rxn != -999.)
              pv22[1][3]->Fill(pt, v2rxn);
            if (v2bbc != -999.)
              pv22[2][3]->Fill(pt, v2bbc);
            //if (v2fhcal!=-999.)  pv22[3][3]->Fill(pt,v2fhcal);
            if (v2fhcalFull != -999.)
              pv22[3][3]->Fill(pt, v2fhcalFull);
            if (v2RP != -999.)
              pv22[4][3]->Fill(pt, v2RP);
            if (v1fhcalFull != -999.)
              pv12[3][3]->Fill(pt, v1fhcalFull);
            if (v1RP != -999.)
              pv12[4][3]->Fill(pt, v1RP);
          }

        } // end of proton selection
      }

      if (pt > MpdPtMin && pt < MpdPtMax)
      {
        pv1_y[3][fCent][0]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
        pv1_y[4][fCent][0]->Fill(rapidity, cos(1.0 * (dphiRP)));
        if (fCent > 0 && fCent < 4)
        {
          pv12_y[3][0]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
          pv12_y[4][0]->Fill(rapidity, cos(1.0 * (dphiRP)));
        }
        if (pdg[itrk] == 211)
        { // && pt > StarPionPtMin & p < StarPionPMax){
          pv1_y[3][fCent][1]->Fill(rapidity, cos(1.0 * (oldphiV1 - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
          pv1_y[4][fCent][1]->Fill(rapidity, cos(1.0 * (dphiRP)));
          if (fCent > 0 && fCent < 4)
          {
            pv12_y[3][1]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
            pv12_y[4][1]->Fill(rapidity, cos(1.0 * (dphiRP)));
          }
        }
        if (pdg[itrk] == 321)
        {
          pv1_y[3][fCent][2]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
          pv1_y[4][fCent][2]->Fill(rapidity, cos(1.0 * (dphiRP)));
          if (fCent > 0 && fCent < 4)
          {
            pv12_y[3][2]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
            pv12_y[4][2]->Fill(rapidity, cos(1.0 * (dphiRP)));
          }
        }
        if (pdg[itrk] == 2212)
        { // && pt > StarProtonPtMin && pt < StarProtonPtMax){
          pv1_y[3][fCent][3]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
          pv1_y[4][fCent][3]->Fill(rapidity, cos(1.0 * (dphiRP)));
          if (fCent > 0 && fCent < 4)
          {
            pv12_y[3][3]->Fill(rapidity, cos(1.0 * (phi - fhcalFullEP_phi)) / res1fhcalFull[fCent]);
            pv12_y[4][3]->Fill(rapidity, cos(1.0 * (dphiRP)));
          }
        }
      }

    } // end of the track loop

  } // end of centrality selection
}

// Urqmd 7.7 GeV
Int_t FlowANA::GetCentrality10_Bimp(Double_t bimp)
{

  Int_t fcent;
  if (bimp < 2.91)
    fcent = 0; // 0-10%
  else if (bimp < 4.18)
    fcent = 1;
  else if (bimp < 6.01)
    fcent = 2; //10-20%
  else if (bimp < 7.37)
    fcent = 3; //20-30%
  else if (bimp < 8.52)
    fcent = 4; //30-40%
  else if (bimp < 9.57)
    fcent = 5; //40-50%
  else if (bimp < 10.55)
    fcent = 6; //50-60%
  else if (bimp < 11.46)
    fcent = 7; //60-70%
  else if (bimp < 12.31)
    fcent = 8; //70-80%
  else
    fcent = -1;

  return fcent;
}

Double_t FlowANA::CentB(Double_t bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  Double_t fcent;
  if      (bimp < 2.91)  fcent = 2.5; // 0-5%
  else if (bimp < 4.18)  fcent = 7.5; // 5-10%
  else if (bimp < 6.01)  fcent = 15.; // 10-20%
  else if (bimp < 7.37)  fcent = 25.; // 20-30%
  else if (bimp < 8.52)  fcent = 35.; // 30-40%
  else if (bimp < 9.57)  fcent = 45.; // 40-50%
  else if (bimp < 10.55) fcent = 55.; // 50-60%
  else if (bimp < 11.46) fcent = 65.; // 60-70%
  else if (bimp < 12.31) fcent = 75.; // 70-80%
  else                   fcent = -1;
  return fcent;
}