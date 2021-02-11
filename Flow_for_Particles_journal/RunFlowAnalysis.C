// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TString.h>

#include <QVector.h>
#include <FlowAnalysisWithEtaSubEventPlane.h>
#include <FlowAnalysisWithLeeYangZeros.h>
#include <FlowAnalysisWithScalarProduct.h>
#include <FlowAnalysisWithQCumulant.h>
#include <FlowAnalysisWithHighOrderQCumulant.h>
#include <FlowAnalysisWithLeeYangZerosEventPlane.h>

#include "utilities.C"

using std::cerr;
using std::cout;
using std::endl;

bool ETASUBEVENTPLANE_1 = 1;
bool ETASUBEVENTPLANE_2 = 0;
bool LYZ_SUM_1 = 0;
bool LYZ_SUM_2 = 0;
bool LYZ_SUM_PRODUCT_1 = 1;
bool LYZ_SUM_PRODUCT_2 = 0;
bool SCALARPRODUCT_1 = 1;
bool SCALARPRODUCT_2 = 0;
bool QCUMULANT = 1;
bool HIGHORDERQCUMULANT = 1;
bool LYZEP = 0;

Double_t maxpt = 3.6;    // max pt for differential flow
Double_t minpt = 0.;     // min pt for differential flow
Double_t maxptRF = 3.;   // max pt for reference flow
Double_t minptRF = 0.2;  // min pt for reference flow
Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
Long64_t Nevents = -1;

Int_t debug = 0;

std::string format = "mctree";
#define MAX_TRACKS 10000

void RunFlowAnalysis(TString inputFileName, TString outputFileName, TString inputHistogramFileName, TString inputHistFromLYZSecondRun)
{
  TStopwatch timer;
  timer.Start();

  if ((LYZ_SUM_1 && LYZ_SUM_PRODUCT_1) || (LYZ_SUM_2 && LYZ_SUM_PRODUCT_2))
  {
    cerr << "Both LYZ_SUM_1(2) and LYZ_SUM_PRODUCT_1(2) are TRUE. Set one of them to FASLE to run flow analysis." << endl;
    return;
  }

  // Configure input information
  TChain *chain = initChain(inputFileName, format.c_str());

  Float_t         bimp;
  Float_t         phi2;
  Float_t         phi3;
  Float_t         ecc2;
  Float_t         ecc3;
  Int_t           npart;
  Int_t           nh;
  Float_t         momx[MAX_TRACKS];   //[nh]
  Float_t         momy[MAX_TRACKS];   //[nh]
  Float_t         momz[MAX_TRACKS];   //[nh]
  Float_t         ene[MAX_TRACKS];   //[nh]
  Int_t           hid[MAX_TRACKS];   //[nh]
  Int_t           pdg[MAX_TRACKS];   //[nh]
  Short_t         charge0[MAX_TRACKS];   //[nh]

  // List of branches
  TBranch        *b_bimp;   //!
  TBranch        *b_phi2;   //!
  TBranch        *b_phi3;   //!
  TBranch        *b_ecc2;   //!
  TBranch        *b_ecc3;   //!
  TBranch        *b_npart;   //!
  TBranch        *b_nh;   //!
  TBranch        *b_momx;   //!
  TBranch        *b_momy;   //!
  TBranch        *b_momz;   //!
  TBranch        *b_ene;   //!
  TBranch        *b_hid;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_charge;   //!

  chain->SetBranchAddress("bimp", &bimp, &b_bimp);
  chain->SetBranchAddress("phi2", &phi2, &b_phi2);
  chain->SetBranchAddress("phi3", &phi3, &b_phi3);
  chain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  chain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  chain->SetBranchAddress("npart", &npart, &b_npart);
  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("momx", momx, &b_momx);
  chain->SetBranchAddress("momy", momy, &b_momy);
  chain->SetBranchAddress("momz", momz, &b_momz);
  chain->SetBranchAddress("ene", ene, &b_ene);
  chain->SetBranchAddress("hid", hid, &b_hid);
  chain->SetBranchAddress("pdg", pdg, &b_pdg);
  chain->SetBranchAddress("charge", charge0, &b_charge);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  FlowAnalysisWithEtaSubEventPlane *flowEtaSub = NULL; // Eta-sub Event Plane
  FlowAnalysisWithLeeYangZeros *flowLYZ = NULL;        // Lee Yang Zeros
  FlowAnalysisWithScalarProduct *flowSP = NULL;        // Scalar Product
  FlowAnalysisWithQCumulant *flowQC = NULL;            // Q-Cumulant
  FlowAnalysisWithHighOrderQCumulant *flowHighQC = NULL;
  FlowAnalysisWithLeeYangZerosEventPlane *flowLYZEP = NULL;

  if (ETASUBEVENTPLANE_1)
  {
    flowEtaSub = new FlowAnalysisWithEtaSubEventPlane();
    flowEtaSub->SetFirstRun(true);
    flowEtaSub->SetEtaGap(eta_gap);
    flowEtaSub->Init();
  }
  if (ETASUBEVENTPLANE_2)
  {
    flowEtaSub = new FlowAnalysisWithEtaSubEventPlane();
    flowEtaSub->SetFirstRun(false);
    flowEtaSub->SetEtaGap(eta_gap);
    flowEtaSub->SetInputFileFromFirstRun(inputHistogramFileName); // need to be improve!!!
    flowEtaSub->Init();
  }
  if (LYZ_SUM_1)
  {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    flowLYZ->SetFirstRun(true);
    flowLYZ->Init();
  }
  if (LYZ_SUM_2)
  {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    // flowLYZ->SetDebugFlag(true);
    flowLYZ->SetFirstRun(false);
    flowLYZ->SetInputFileFromFirstRun(inputHistogramFileName); // need to be improve!!!
    flowLYZ->Init();
  }

  if (LYZ_SUM_PRODUCT_1)
  {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    flowLYZ->SetFirstRun(true);
    flowLYZ->SetUseProduct(true);
    flowLYZ->Init();
  }
  if (LYZ_SUM_PRODUCT_2)
  {
    flowLYZ = new FlowAnalysisWithLeeYangZeros();
    // flowLYZ->SetDebugFlag(true);
    flowLYZ->SetFirstRun(false);
    flowLYZ->SetUseProduct(true);
    flowLYZ->SetInputFileFromFirstRun(inputHistogramFileName); // need to be improve!!!
    flowLYZ->Init();
  }
  QVector *Q2 = new QVector(); // for LYZ only, need to be improve to be also feasible to QC.
  // Start event loop
  if (SCALARPRODUCT_1)
  {
    flowSP = new FlowAnalysisWithScalarProduct();
    flowSP->SetFirstRun(true);
    flowSP->SetEtaGap(eta_gap);
    flowSP->Init();
  }
  if (SCALARPRODUCT_2)
  {
    flowSP = new FlowAnalysisWithScalarProduct();
    flowSP->SetFirstRun(false);
    flowSP->SetEtaGap(eta_gap);
    flowSP->SetInputFileFromFirstRun(inputHistogramFileName); // need to be improve!!!
    flowSP->Init();
  }
  if (QCUMULANT)
  {
    flowQC = new FlowAnalysisWithQCumulant();
    flowQC->SetEtaGap(eta_gap);
    flowQC->Init();
  }

  if (HIGHORDERQCUMULANT)
  {
    flowHighQC = new FlowAnalysisWithHighOrderQCumulant();
    flowHighQC->Init();
  }
  if (LYZEP)
  {
    if (inputHistogramFileName=="" || inputHistFromLYZSecondRun=="")
    {
      cerr << "Input files with needed histograms for Lee Yang Zeros Event Plane aren't set" << endl;
      return;
    }
    flowLYZEP = new FlowAnalysisWithLeeYangZerosEventPlane();
    flowLYZEP->SetInputFileFromFirstAndSecondRun(inputHistogramFileName, inputHistFromLYZSecondRun);
    flowLYZEP->Init();
  }
  Double_t pt, eta, phi, charge;
  Long64_t chain_size = chain->GetEntries();
  Long64_t n_entries = (Nevents < chain_size && Nevents > 0) ? Nevents : chain_size;
  cout << "Hi Master, let's do some physics together..." << endl;
  for (Int_t iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    if (!nh) continue;
    // Read MC event
    Double_t cent = CentB(bimp);
    if (cent == -1)
      continue;
    Int_t icent = GetCentBin(cent);

    if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2)
      flowEtaSub->Zero();
    if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2)
      flowLYZ->Zero();
    if (SCALARPRODUCT_1 || SCALARPRODUCT_2)
      flowSP->Zero();
    Q2->Zero();
    if (QCUMULANT)
      flowQC->Zero();
    if (HIGHORDERQCUMULANT)
      flowHighQC->Zero();
    for (Int_t iTrk = 0; iTrk < nh; iTrk++)
    { // Track loop
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      pt  = vect.Pt();
      eta = vect.Eta();
      phi = vect.Phi();
      if (pt < minpt || pt > maxpt || fabs(eta)>eta_cut) continue; // track selection
      // if (abs(eta)<eta_gap) continue;
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      if (!particle) continue;
      charge = 1./3.*particle->Charge();
      if (charge == 0) continue;

      Int_t ipt = findBin(pt);
      Int_t fId = findId(pdg[iTrk]);

      // phiAngles.recalc(phi);

      if (pt > minptRF && pt < maxptRF)
      { // Reference Flow pt cut
        // 2,4-QC

        if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2)
          flowEtaSub->ProcessFirstTrackLoop(eta, phi, pt);
        if (SCALARPRODUCT_1 || SCALARPRODUCT_2)
          flowSP->ProcessFirstTrackLoop(eta, phi);
        if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2)
          flowLYZ->ProcessFirstTrackLoop(phi, pt, icent);
        Q2->CalQVector(phi, 1.);
        if (QCUMULANT)
          flowQC->ProcessFirstTrackLoopRP(eta, phi);
        if (HIGHORDERQCUMULANT)
          flowHighQC->ProcessFirstTrackLoopRP(phi);
      }
      if (QCUMULANT)
        flowQC->ProcessFirstTrackLoopPOI(ipt, eta, phi, fId, charge);
    } // end of track loop
    Q2->WeightQVector();
    if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2)
      flowEtaSub->ProcessEventAfterFirstTrackLoop(cent);
    if (SCALARPRODUCT_1 || SCALARPRODUCT_2)
      flowSP->ProcessEventAfterFirstTrackLoop(cent);
    if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2)
      flowLYZ->ProcessEventAfterFirstTrackLoop(Q2, icent);
    if (QCUMULANT)
      flowQC->ProcessEventAfterFirstTrackLoop(icent);
    if (HIGHORDERQCUMULANT)
      flowHighQC->ProcessEventAfterFirstTrackLoop(icent);
    if (LYZEP)
      flowLYZEP->ProcessEventAfterFirstTrackLoop(Q2, icent);
    if (ETASUBEVENTPLANE_2 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_2 || SCALARPRODUCT_2 || LYZEP)
    {
      for (Int_t iTrk = 0; iTrk < nh; iTrk++)
      { // 2nd Track loop
        TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
        pt  = vect.Pt();
        eta = vect.Eta();
        phi = vect.Phi();
        if (pt < minpt || pt > maxpt || fabs(eta)>eta_cut) continue; // track selection
        // if (abs(eta)<eta_gap) continue;
        auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
        if (!particle) continue;
        charge = 1./3.*particle->Charge();
        if (charge == 0) continue;

        if (ETASUBEVENTPLANE_2)
          flowEtaSub->ProcessSecondTrackLoop(eta, phi, pt, cent);
        if (SCALARPRODUCT_2)
          flowSP->ProcessSecondTrackLoop(eta, phi, pt, cent);
        if (LYZ_SUM_2 || LYZ_SUM_PRODUCT_2)
          flowLYZ->ProcessSecondTrackLoop(phi, pt, icent);
        if (LYZEP)
          flowLYZEP->ProcessSecondTrackLoop(eta, phi, pt, cent);
      }
    }
  } // end event loop

  // Writing output
  fo->cd();

  if (ETASUBEVENTPLANE_1 || ETASUBEVENTPLANE_2)
    flowEtaSub->SaveHist();
  if (SCALARPRODUCT_1 || SCALARPRODUCT_2)
    flowSP->SaveHist();
  if (LYZ_SUM_1 || LYZ_SUM_2 || LYZ_SUM_PRODUCT_1 || LYZ_SUM_PRODUCT_2)
    flowLYZ->SaveHist();
  if (QCUMULANT)
    flowQC->SaveHist();
  if (HIGHORDERQCUMULANT)
    flowHighQC->SaveHist();
  if (LYZEP)
    flowLYZEP->SaveHist();
  fo->Close();

  timer.Stop();
  timer.Print();
}