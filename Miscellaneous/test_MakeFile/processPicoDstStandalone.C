/**
 * Elliptic flow v2 measurements using Q-Cumulant
 * proposed by Ante Bilandzic in https://arxiv.org/abs/1010.0233
 * implemeted for PicoDst format: https://dev.ut.mephi.ru/PEParfenov/PicoDst
 * by Vinh Ba Luong (lbavinh@gmail.com)
 * 25/11/2020
 */
// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TClonesArray.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TString.h>

// PicoDst headers
#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

#include "utilities.C"

int main(int argc, char* argv[])
{
  const char* inputFileName;
  const char* outputFileName;

  switch (argc) {
  case 3:
    inputFileName = argv[1];
    outputFileName = argv[2];
    break;
  default:
    std::cout << "Usage: processMcDstStandalone inputFileName outputFileName.root" << std::endl;
    return -1;
  }
  std::cout << " inputFileName : " << inputFileName << std::endl;
  std::cout << " outputFileName: " << outputFileName << std::endl;


  TStopwatch timer;
  timer.Start();

  // Constant declaration
  const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "antiproton"};
  const int ncent = 9; //
  // const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  const int npt = 16; // 0-3.6 GeV/c - number of pT bins
  const double pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
  const double maxpt = 3.6;   // max pt for differential flow
  const double minpt = 0.;    // min pt for differential flow
  const double maxptRF = 3.;  // max pt for reference flow
  const double minptRF = 0.2; // min pt for reference flow
  const float eta_cut = 1.5;
  const float eta_gap = 0.05; // +-0.05
  const int Nhits_cut = 16;   // minimum nhits of reconstructed tracks
  const float DCAcut = 0.5;
  const int neta = 2; // [eta-,eta+]

  // Configure input information

  TChain *chain = new TChain("picodst");
  std::ifstream file(inputFileName);
  std::string line;
  while(std::getline(file, line))
  {
    chain->Add(line.c_str());
  }

  // TFile *treefile = TFile::Open(inputFileName.Data());
  // TTree *chain = (TTree *)treefile->Get("picodst");
  // if (!chain)
  // {
  //   cout << "picodst is not found in " << inputFileName.Data() << endl;
  //   treefile->Close();
  //   return;
  // }

  PicoDstMCEvent *mcEvent = nullptr;
  PicoDstRecoEvent *recoEvent = nullptr;
  TClonesArray *recoTracks = nullptr;
  // TClonesArray *mcTracks = nullptr;
  // TClonesArray *fhcalmodules = nullptr;

  chain->SetBranchAddress("mcevent.", &mcEvent);
  chain->SetBranchAddress("recoevent.", &recoEvent);
  chain->SetBranchAddress("recotracks", &recoTracks);
  // chain->SetBranchAddress("mctracks",&mcTracks);
  // chain->SetBranchAddress("FHCalModules",&fhcalmodules);

  // Configure output information
  TFile *fo = new TFile(outputFileName, "recreate");

  // TProfile of multi-particle correlations
  TProfile *pCorrelator2EtaGap = new TProfile("pCorrelator2EtaGap", "2nd order correlator with eta-gap, TPC", ncent, 0, ncent); // <<2>> (with eta-gap)
  TProfile *pCorrelator2 = new TProfile("pCorrelator2", "2nd order correlator", ncent, 0, ncent);                               // <<2>>
  TProfile *pCorrelator4 = new TProfile("pCorrelator4", "4th order correlator", ncent, 0, ncent);                               // <<4>>

  TProfile2D *pReducedCorrelator2EtaGap[npid]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2[npid];       // <<2'>>
  TProfile2D *pReducedCorrelator4[npid];       // <<4'>>

  for (int i = 0; i < npid; i++)
  {
    pReducedCorrelator2EtaGap[i] = new TProfile2D(Form("pReducedCorrelator2EtaGap_pid%i", i), Form("Reduced 2nd order correlator with eta-gap of %s (TPC", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pReducedCorrelator2[i] = new TProfile2D(Form("pReducedCorrelator2_pid%i", i), Form("Reduced 2nd order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pReducedCorrelator4[i] = new TProfile2D(Form("pReducedCorrelator4_pid%i", i), Form("Reduced 4th order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
  }

  // TProfile for covariance calculation of statistical errors of QCumulant
  TProfile *pCov24 = new TProfile("pCov24", "Covariance(<2>,<4>)", ncent, 0, ncent); // <2>*<4>
  TProfile2D *pCov22Red[npid];                                                       // <2>*<2'>
  TProfile2D *pCov24Red[npid];                                                       // <2>*<4'>
  TProfile2D *pCov42Red[npid];                                                       // <4>*<2'>
  TProfile2D *pCov44Red[npid];                                                       // <4>*<4'>
  TProfile2D *pCov2Red4Red[npid];                                                    // <2'>*<4'>
  TProfile2D *pCov22RedEtaGap[npid];                                                 // <2>*<2'> (with eta-gap)

  for (int i = 0; i < npid; i++)
  {
    pCov22RedEtaGap[i] = new TProfile2D(Form("pCov22RedEtaGap_pid%i", i), Form("Covariance(<2>,<2'>) with eta-gap of %s (TPC)", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov22Red[i] = new TProfile2D(Form("pCov22Red_pid%i", i), Form("Covariance(<2>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov24Red[i] = new TProfile2D(Form("pCov24Red_pid%i", i), Form("Covariance(<2>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov42Red[i] = new TProfile2D(Form("pCov42Red_pid%i", i), Form("Covariance(<4>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov44Red[i] = new TProfile2D(Form("pCov44Red_pid%i", i), Form("Covariance(<4>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov2Red4Red[i] = new TProfile2D(Form("pCov2Red4Red_pid%i", i), Form("Covariance(<4'>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
  }

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    // Read MC event
    float bimp = mcEvent->GetB();
    float cent = CentB(bimp);
    if (cent == -1)
      continue;
    int fCentBin = GetCentBin(cent);
    int reco_mult = recoTracks->GetEntriesFast();

    // 2,4-QC
    Double_t Qx2 = 0., Qy2 = 0., Qx4 = 0., Qy4 = 0.;
    TComplex Q2 = 0., Q4 = 0.;
    Double_t px2[npt][npid] = {{0.}}, py2[npt][npid] = {{0.}};
    TComplex p2[npt][npid] = {{0.}}, p4[npt][npid] = {{0.}}, q2[npt][npid] = {{0.}}, q4[npt][npid] = {{0.}};
    Double_t qx2[npt][npid] = {{0.}}, qy2[npt][npid] = {{0.}}, qx4[npt][npid] = {{0.}}, qy4[npt][npid] = {{0.}};
    Double_t M = 0.;
    Double_t mq[npt][npid] = {{0.}}, mp[npt][npid] = {{0.}};
    Double_t redCor22[npt][npid] = {{0.}}, redCor24[npt][npid] = {{0.}};
    Double_t w2 = 0., w4 = 0.;
    Double_t wred2[npt][npid] = {{0.}}, wred4[npt][npid] = {{0.}};
    Double_t cor22 = 0., cor24 = 0.;

    // 2-QC, eta-gapped
    Double_t Qx2Gap[neta] = {0.}, Qy2Gap[neta] = {0.};
    Double_t px2Gap[neta][npt][npid] = {{{0.}}}, py2Gap[neta][npt][npid] = {{{0.}}};
    TComplex Q2Gap[neta] = {0.}, p2Gap[neta][npt][npid] = {{{0.}}};
    Double_t MGap[neta] = {0};
    Double_t mpGap[neta][npt][npid] = {{{0.}}};
    Double_t w2Gap = 0.;
    Double_t wred2Gap[neta][npt][npid] = {{{0.}}};
    Double_t cor22Gap = 0.;
    Double_t redCor22Gap[neta][npt][npid] = {{{0.}}};

    for (int iTrk = 0; iTrk < reco_mult; iTrk++)
    { // Track loop
      auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(iTrk);
      if (!recoTrack)
        continue;
      float pt = recoTrack->GetPt();
      float eta = recoTrack->GetEta();
      float phi = recoTrack->GetPhi();
      if (pt < minpt || pt > maxpt || abs(eta) > eta_cut)
        continue;
      if (abs(recoTrack->GetDCAx()) > DCAcut)
        continue; // DCAx cut
      if (abs(recoTrack->GetDCAy()) > DCAcut)
        continue; // DCAy cut
      if (abs(recoTrack->GetDCAz()) > DCAcut)
        continue; // DCAz cut
      if (recoTrack->GetNhits() < Nhits_cut)
        continue; // TPC hits cut
      float charge = recoTrack->GetCharge();

      int ipt = -1;
      for (int j = 0; j < npt; j++)
      {
        if (pt >= pTBin[j] && pt < pTBin[j + 1])
          ipt = j;
      }

      int fId = -1;
      if (recoTrack->GetTofFlag() != 0 && recoTrack->GetTofFlag() != 4)
      {
        if (recoTrack->GetPidProbPion() > 0.9 && charge > 0)
          fId = 1; // pion+
        if (recoTrack->GetPidProbKaon() > 0.9 && charge > 0)
          fId = 2; // kaon+
        if (recoTrack->GetPidProbProton() > 0.9 && charge > 0)
          fId = 3; // proton
        if (recoTrack->GetPidProbPion() > 0.9 && charge < 0)
          fId = 5; // pion-
        if (recoTrack->GetPidProbKaon() > 0.9 && charge < 0)
          fId = 6; // kaon-
        if (recoTrack->GetPidProbProton() > 0.9 && charge < 0)
          fId = 7; // antiproton
      }

      Double_t cos4phi = TMath::Cos(4. * phi);
      Double_t sin4phi = TMath::Sin(4. * phi);
      Double_t cos2phi = TMath::Cos(2. * phi);
      Double_t sin2phi = TMath::Sin(2. * phi);

      if (pt > minptRF && pt < maxptRF)
      { // Reference Flow pt cut
        // 2,4-QC
        Qx2 += cos2phi;
        Qy2 += sin2phi;
        Qx4 += cos4phi;
        Qy4 += sin4phi;
        M++;
        // 2-QC, eta-gapped
        if (eta < -eta_gap)
        {
          Qx2Gap[0] += cos2phi;
          Qy2Gap[0] += sin2phi;
          MGap[0]++;
        }
        if (eta > eta_gap)
        {
          Qx2Gap[1] += cos2phi;
          Qy2Gap[1] += sin2phi;
          MGap[1]++;
        }
      }

      // Differential Flow of 2,4-QC
      if (charge > 0)
      {
        px2[ipt][0] += cos2phi;
        py2[ipt][0] += sin2phi;
        mp[ipt][0]++;

        qx2[ipt][0] += cos2phi;
        qy2[ipt][0] += sin2phi;
        qx4[ipt][0] += cos4phi;
        qy4[ipt][0] += sin4phi;
        mq[ipt][0]++;
      }
      if (charge < 0)
      {
        px2[ipt][4] += cos2phi;
        py2[ipt][4] += sin2phi;
        mp[ipt][4]++;

        qx2[ipt][4] += cos2phi;
        qy2[ipt][4] += sin2phi;
        qx4[ipt][4] += cos4phi;
        qy4[ipt][4] += sin4phi;
        mq[ipt][4]++;
      }
      if (fId > 0)
      {
        px2[ipt][fId] += cos2phi;
        py2[ipt][fId] += sin2phi;
        mp[ipt][fId]++;

        qx2[ipt][fId] += cos2phi;
        qy2[ipt][fId] += sin2phi;
        qx4[ipt][fId] += cos4phi;
        qy4[ipt][fId] += sin4phi;
        mq[ipt][fId]++;
      }
      // Differential Flow of 2-QC, eta-gapped
      if (eta < -eta_gap)
      { // Left TPC subevent selection
        if (charge > 0)
        { // Inclusive positively charged hadrons
          px2Gap[1][ipt][0] += cos2phi;
          py2Gap[1][ipt][0] += sin2phi;
          mpGap[1][ipt][0]++;
        }
        if (charge < 0)
        { // Inclusive negatively charged hadrons
          px2Gap[1][ipt][4] += cos2phi;
          py2Gap[1][ipt][4] += sin2phi;
          mpGap[1][ipt][4]++;
        }
        if (fId > 0)
        { // Identified charged hadrons
          px2Gap[1][ipt][fId] += cos2phi;
          py2Gap[1][ipt][fId] += sin2phi;
          mpGap[1][ipt][fId]++;
        }
      } // end of Left TPC subevent selection
      if (eta > eta_gap)
      { // Right TPC subevent selection
        if (charge > 0)
        { // Inclusive positively charged hadrons
          px2Gap[0][ipt][0] += cos2phi;
          py2Gap[0][ipt][0] += sin2phi;
          mpGap[0][ipt][0]++;
        }
        if (charge < 0)
        { // Inclusive negatively charged hadrons
          px2Gap[0][ipt][4] += cos2phi;
          py2Gap[0][ipt][4] += sin2phi;
          mpGap[0][ipt][4]++;
        }
        if (fId > 0)
        { // Identified charged hadrons
          px2Gap[0][ipt][fId] += cos2phi;
          py2Gap[0][ipt][fId] += sin2phi;
          mpGap[0][ipt][fId]++;
        }
      } // end of Right TPC subevent selection
    } // end of track loop

    // 2-QC, eta-gapped: multi-particle correlation calculation
    if (MGap[0] != 0 && MGap[1] != 0)
    {
      for (int ieta = 0; ieta < neta; ieta++)
      {
        Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
      }
      w2Gap = MGap[0] * MGap[1];
      cor22Gap = CalRedCor22(Q2Gap[0], Q2Gap[1], MGap[0], MGap[1], 0., w2Gap); // <2>
      pCorrelator2EtaGap->Fill(0.5 + fCentBin, cor22Gap, w2Gap);
      for (int ieta = 0; ieta < neta; ieta++)
      {
        for (int ipt = 0; ipt < npt; ipt++)
        { // <2'>
          for (int id = 0; id < npid; id++)
          {
            if (mpGap[ieta][ipt][id] == 0)
              continue;
            p2Gap[ieta][ipt][id] = TComplex(px2Gap[ieta][ipt][id], py2Gap[ieta][ipt][id]);
            wred2Gap[ieta][ipt][id] = mpGap[ieta][ipt][id] * MGap[ieta];
            redCor22Gap[ieta][ipt][id] = CalRedCor22(Q2Gap[ieta], p2Gap[ieta][ipt][id], MGap[ieta], mpGap[ieta][ipt][id], 0., wred2Gap[ieta][ipt][id]); // <2'>
            pReducedCorrelator2EtaGap[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);
            // TProfile for covariance calculation in statistic error
            pCov22RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22Gap * redCor22Gap[ieta][ipt][id], w2Gap * wred2Gap[ieta][ipt][id]);
          }
        }
      }
    }

    // 2,4-QC: multi-particle correlation calculation
    Q2 = TComplex(Qx2, Qy2);
    w2 = M * (M - 1); // w(<2>)
    Q4 = TComplex(Qx4, Qy4);
    w4 = M * (M - 1) * (M - 2) * (M - 3); // w(<4>)
    if (w2 != 0 && w4 != 0)
    {
      cor22 = CalCor22(Q2, M, w2);                   // <2>
      cor24 = CalCor24(Q2, Q4, M, w4);               // <4>
      pCorrelator2->Fill(0.5 + fCentBin, cor22, w2); // <<2>>
      pCorrelator4->Fill(0.5 + fCentBin, cor24, w4); // <<4>>
      // TProfile for covariance calculation in statistic error
      pCov24->Fill(0.5 + fCentBin, cor22 * cor24, w2 * w4); // <2>*<4>
      for (int ipt = 0; ipt < npt; ipt++)
      {
        for (int id = 0; id < npid; id++)
        {
          wred2[ipt][id] = mp[ipt][id] * M - mq[ipt][id];                           // w(<2'>)
          wred4[ipt][id] = (mp[ipt][id] * M - 3 * mq[ipt][id]) * (M - 1) * (M - 2); // w(<4'>)
          if (mp[ipt][id] == 0 || wred2[ipt][id] == 0 || wred4[ipt][id] == 0)
            continue;
          p2[ipt][id] = TComplex(px2[ipt][id], py2[ipt][id]);
          q2[ipt][id] = TComplex(qx2[ipt][id], qy2[ipt][id]);
          q4[ipt][id] = TComplex(qx4[ipt][id], qy4[ipt][id]);
          redCor22[ipt][id] = CalRedCor22(Q2, p2[ipt][id], M, mp[ipt][id], mq[ipt][id], wred2[ipt][id]); // <2'>
          pReducedCorrelator2[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22[ipt][id], wred2[ipt][id]);
          redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]); // <4'>
          pReducedCorrelator4[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor24[ipt][id], wred4[ipt][id]);                                 // <<4'>>

          // TProfile for covariance calculation in statistic error
          pCov22Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]); // <2>*<2'>
          pCov24Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
          pCov42Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
          pCov44Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
          pCov2Red4Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
        }
      }
    }
  } // end event loop

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}