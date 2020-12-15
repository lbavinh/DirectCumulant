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
const float eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements 
const float eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
const int Nhits_cut = 16;   // minimum nhits of reconstructed tracks
const float DCAcut = 0.5;
const int neta = 2; // [eta-,eta+]

TChain* initChain(const TString &inputFileName, const char* chainName)
{
    TChain *chain = new TChain(chainName);
    std::ifstream file(inputFileName.Data());
    std::string line;
    while(std::getline(file, line))
    {
        chain->Add(line.c_str());
    }

    return chain;
}

 // TProfile of multi-particle correlations
struct CCorrelator
{
    TProfile *pCorrelator2EtaGap;
    TProfile *pCorrelator2;
    TProfile *pCorrelator4;

    TProfile2D *pReducedCorrelator2EtaGap[npid];
    TProfile2D *pReducedCorrelator2[npid];
    TProfile2D *pReducedCorrelator4[npid];

    CCorrelator();
};

CCorrelator::CCorrelator()
{
    pCorrelator2EtaGap = new TProfile("pCorrelator2EtaGap", "2nd order correlator with eta-gap, TPC", ncent, 0, ncent); // <<2>> (with eta-gap)
    pCorrelator2 = new TProfile("pCorrelator2", "2nd order correlator", ncent, 0, ncent);                               // <<2>>
    pCorrelator4 = new TProfile("pCorrelator4", "4th order correlator", ncent, 0, ncent);                               // <<4>>

    for (int i = 0; i < npid; i++)
    {
        pReducedCorrelator2EtaGap[i] = new TProfile2D(Form("pReducedCorrelator2EtaGap_pid%i", i), Form("Reduced 2nd order correlator with eta-gap of %s (TPC", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
        pReducedCorrelator2[i] = new TProfile2D(Form("pReducedCorrelator2_pid%i", i), Form("Reduced 2nd order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
        pReducedCorrelator4[i] = new TProfile2D(Form("pReducedCorrelator4_pid%i", i), Form("Reduced 4th order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    }  
}

// TProfile for covariance calculation of statistical errors of QCumulant
struct CCovCorrelator
{
    TProfile *pCov24;                                                                  // <2>*<4>
    TProfile2D *pCov22Red[npid];                                                       // <2>*<2'>
    TProfile2D *pCov24Red[npid];                                                       // <2>*<4'>
    TProfile2D *pCov42Red[npid];                                                       // <4>*<2'>
    TProfile2D *pCov44Red[npid];                                                       // <4>*<4'>
    TProfile2D *pCov2Red4Red[npid];                                                    // <2'>*<4'>
    TProfile2D *pCov22RedEtaGap[npid];                                                 // <2>*<2'> (with eta-gap)

    CCovCorrelator();

};

CCovCorrelator::CCovCorrelator()
{
    pCov24 = new TProfile("pCov24", "Covariance(<2>,<4>)", ncent, 0, ncent); // <2>*<4>

    for (int i = 0; i < npid; i++)
    {
      pCov22RedEtaGap[i] = new TProfile2D(Form("pCov22RedEtaGap_pid%i", i), Form("Covariance(<2>,<2'>) with eta-gap of %s (TPC)", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov22Red[i] = new TProfile2D(Form("pCov22Red_pid%i", i), Form("Covariance(<2>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov24Red[i] = new TProfile2D(Form("pCov24Red_pid%i", i), Form("Covariance(<2>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov42Red[i] = new TProfile2D(Form("pCov42Red_pid%i", i), Form("Covariance(<4>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov44Red[i] = new TProfile2D(Form("pCov44Red_pid%i", i), Form("Covariance(<4>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov2Red4Red[i] = new TProfile2D(Form("pCov2Red4Red_pid%i", i), Form("Covariance(<4'>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    }    

}

struct CPhiAngles
{
      Double_t cos4phi, sin4phi, cos2phi, sin2phi;

      void recalc(float phi);
};

void CPhiAngles::recalc(float phi)
{
      cos4phi = TMath::Cos(4. * phi);
      sin4phi = TMath::Sin(4. * phi);
      cos2phi = TMath::Cos(2. * phi);
      sin2phi = TMath::Sin(2. * phi);
}

// 2,4-QC
struct CQC24
{
    Double_t Qx2, Qy2, Qx4, Qy4;
    TComplex Q2, Q4;
    Double_t px2[npt][npid], py2[npt][npid];
    TComplex p2[npt][npid], p4[npt][npid], q2[npt][npid], q4[npt][npid];
    Double_t qx2[npt][npid], qy2[npt][npid], qx4[npt][npid], qy4[npt][npid];
    Double_t M = 0.;
    Double_t mq[npt][npid], mp[npt][npid];
    Double_t redCor22[npt][npid], redCor24[npt][npid];
    Double_t w2, w4;
    Double_t wred2[npt][npid], wred4[npt][npid];
    Double_t cor22, cor24;

    int fCentBin;

    CQC24() { zero(); }
    void zero();
    void setQxQy(const CPhiAngles& phiAngles);
    void setQP(const CPhiAngles& phiAngles, const int ipt, const float charge, const int fId);
    void calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr);

  private:        
    void setQP(const CPhiAngles& phiAngles, const int ipt, const int idx1);
};

void CQC24::zero()
{
    Qx2 = 0.; Qy2 = 0.; Qx4 = 0.; Qy4 = 0.;
    Q2 = TComplex(0.,0.); Q4 = TComplex(0.,0.);
    // px2[npt][npid] = {{0.}}; py2[npt][npid] = {{0.}};
    // p2[npt][npid] = {{0.}}; p4[npt][npid] = {{0.}}; q2[npt][npid] = {{0.}}; q4[npt][npid] = {{0.}};
    // qx2[npt][npid] = {{0.}}; qy2[npt][npid] = {{0.}}; qx4[npt][npid] = {{0.}}; qy4[npt][npid] = {{0.}};
    M = 0.;
    // mq[npt][npid] = {{0.}}; mp[npt][npid] = {{0.}};
    // redCor22[npt][npid] = {{0.}}; redCor24[npt][npid] = {{0.}};
    w2 = 0.; w4 = 0.;
    // wred2[npt][npid] = {{0.}}; wred4[npt][npid] = {{0.}};
    cor22 = 0.; cor24 = 0.;
    for (int ipt = 0; ipt < npt; ipt++)
    {
        for (int ipid = 0; ipid < npid; ipid++)
        {
            px2[ipt][ipid] = 0.;
            py2[ipt][ipid] = 0.;
            mq[ipt][ipid] = 0.;
            mp[ipt][ipid] = 0.;
            redCor22[ipt][ipid] = 0.;
            redCor24[ipt][ipid] = 0.;
            wred2[ipt][ipid] = 0.;
            wred4[ipt][ipid] = 0.;
            p2[ipt][ipid] = TComplex(0., 0.);
            p4[ipt][ipid] = TComplex(0., 0.);
            q2[ipt][ipid] = TComplex(0., 0.);
            q4[ipt][ipid] = TComplex(0., 0.);
        }
    }
}

void CQC24::setQxQy(const CPhiAngles& phiAngles)
{
        Qx2 += phiAngles.cos2phi;
        Qy2 += phiAngles.sin2phi;
        Qx4 += phiAngles.cos4phi;
        Qy4 += phiAngles.sin4phi;
        M++;
}

void CQC24::setQP(const CPhiAngles& phiAngles, const int ipt, const int idx1)
{
        px2[ipt][idx1] += phiAngles.cos2phi;
        py2[ipt][idx1] += phiAngles.sin2phi;
        mp[ipt][idx1]++;

        qx2[ipt][idx1] += phiAngles.cos2phi;
        qy2[ipt][idx1] += phiAngles.sin2phi;
        qx4[ipt][idx1] += phiAngles.cos4phi;
        qy4[ipt][idx1] += phiAngles.sin4phi;
        mq[ipt][idx1]++;
}

void CQC24::setQP(const CPhiAngles& phiAngles, const int ipt, const float charge, const int fId)
{
      if (charge > 0)
      {
          setQP(phiAngles, ipt, 0);
      }
      else if (charge < 0)
      {
          setQP(phiAngles, ipt, 4);
      }
      if (fId > 0)
      {
          setQP(phiAngles, ipt, fId);
      }
}

void CQC24::calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr)
{
    Q2 = TComplex(Qx2, Qy2);
    w2 = M * (M - 1); // w(<2>)
    Q4 = TComplex(Qx4, Qy4);
    w4 = M * (M - 1) * (M - 2) * (M - 3); // w(<4>)
    if (w2 != 0 && w4 != 0)
    {
      cor22 = CalCor22(Q2, M, w2);                   // <2>
      cor24 = CalCor24(Q2, Q4, M, w4);               // <4>
      pCorr->pCorrelator2->Fill(0.5 + fCentBin, cor22, w2); // <<2>>
      pCorr->pCorrelator4->Fill(0.5 + fCentBin, cor24, w4); // <<4>>
      // TProfile for covariance calculation in statistic error
      pCovCorr->pCov24->Fill(0.5 + fCentBin, cor22 * cor24, w2 * w4); // <2>*<4>
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
          pCorr->pReducedCorrelator2[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22[ipt][id], wred2[ipt][id]);
          redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]); // <4'>
          pCorr->pReducedCorrelator4[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor24[ipt][id], wred4[ipt][id]);                                 // <<4'>>

          // TProfile for covariance calculation in statistic error
          pCovCorr->pCov22Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]); // <2>*<2'>
          pCovCorr->pCov24Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
          pCovCorr->pCov42Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
          pCovCorr->pCov44Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
          pCovCorr->pCov2Red4Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
        }
      }
    }                                                                                                                                                                         
}

// 2-QC, eta-gapped
struct CQC2eg
{
    Double_t Qx2Gap[neta], Qy2Gap[neta];
    Double_t px2Gap[neta][npt][npid], py2Gap[neta][npt][npid];
    TComplex Q2Gap[neta], p2Gap[neta][npt][npid];
    Double_t MGap[neta];
    Double_t mpGap[neta][npt][npid];
    Double_t w2Gap;
    Double_t wred2Gap[neta][npt][npid];
    Double_t cor22Gap;
    Double_t redCor22Gap[neta][npt][npid];

    int fCentBin;

    CQC2eg() { zero(); }
    void zero();
    void setQxQy(const CPhiAngles& phiAngles, const float eta);
    void setPxPy(const CPhiAngles& phiAngles, const int ipt, const float eta, const float charge, const int fId);
    void calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr);

private:
    void setQxQy(const CPhiAngles& phiAngles, const int idx);
    void setPxPy(const CPhiAngles& phiAngles, const int ipt, const int idx, const int idx1);
    void setPxPy(const CPhiAngles& phiAngles, const int ipt, const int idx, const float charge, const int fId);

};

void CQC2eg::zero()
{
    // Qx2Gap[neta] = {0.}; Qy2Gap[neta] = {0.};
    // px2Gap[neta][npt][npid] = {{{0.}}}; py2Gap[neta][npt][npid] = {{{0.}}};
    // Q2Gap[neta] = {0.}; p2Gap[neta][npt][npid] = {{{0.}}};
    // MGap[neta] = {0};
    // mpGap[neta][npt][npid] = {{{0.}}};
    w2Gap = 0.;
    // wred2Gap[neta][npt][npid] = {{{0.}}};
    cor22Gap = 0.;
    // redCor22Gap[neta][npt][npid] = {{{0.}}};
    for (int ieta = 0; ieta < neta; ieta++)
    {
        Qx2Gap[ieta] = 0.;
        Qy2Gap[ieta] = 0.;
        MGap[ieta] = 0.;
        Q2Gap[ieta] = TComplex(0., 0.);
        for (int ipt = 0; ipt < npt; ipt++)
        {
            for (int ipid = 0; ipid < npid; ipid++)
            {
                px2Gap[ieta][ipt][ipid] = 0;
                py2Gap[ieta][ipt][ipid] = 0;
                mpGap[ieta][ipt][ipid] = 0;
                wred2Gap[ieta][ipt][ipid] = 0;
                redCor22Gap[ieta][ipt][ipid] = 0;
                p2Gap[ieta][ipt][ipid] = TComplex(0., 0.);
            }
        }
    }
}

void CQC2eg::setQxQy(const CPhiAngles& phiAngles, const int idx)
{
    Qx2Gap[idx] += phiAngles.cos2phi;
    Qy2Gap[idx] += phiAngles.sin2phi;
    MGap[idx]++;
}

void CQC2eg::setPxPy(const CPhiAngles& phiAngles, const int ipt, const int idx, const int idx1)
{
    px2Gap[idx][ipt][idx1] += phiAngles.cos2phi;
    py2Gap[idx][ipt][idx1] += phiAngles.sin2phi;
    mpGap[idx][ipt][idx1]++;  
}

void CQC2eg::setPxPy(const CPhiAngles& phiAngles, const int ipt, const int idx, const float charge, const int fId)
{
      if (charge > 0)
      {
          setPxPy(phiAngles, ipt, idx, 0);
      }
      else if (charge < 0)
      {
          setPxPy(phiAngles, ipt, idx, 4);
      }
      if (fId > 0)
      {
          setPxPy(phiAngles, ipt, idx, fId);
      }
}

void CQC2eg::setQxQy(const CPhiAngles& phiAngles, const float eta)
{
    if (eta < -eta_gap)
    {
        setQxQy(phiAngles, 0);
    }
    else if (eta > eta_gap)
    {
        setQxQy(phiAngles, 1);
    }
}

void CQC2eg::setPxPy(const CPhiAngles& phiAngles, const int ipt, const float eta, const float charge, const int fId)
{
    if (eta < -eta_gap)
    {
        setPxPy(phiAngles, ipt, 0, charge, fId);
    }
    else if (eta > eta_gap)
    {
        setPxPy(phiAngles, ipt, 1, charge, fId);
    }
}

void CQC2eg::calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr)
{
     // 2-QC, eta-gapped: multi-particle correlation calculation
    if (MGap[0] != 0 && MGap[1] != 0)
    {
        for (int ieta = 0; ieta < neta; ieta++)
        {
            Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
        }

        w2Gap = MGap[0] * MGap[1];
        cor22Gap = CalRedCor22(Q2Gap[0], Q2Gap[1], MGap[0], MGap[1], 0., w2Gap); // <2>
        pCorr->pCorrelator2EtaGap->Fill(0.5 + fCentBin, cor22Gap, w2Gap);
      
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
                    pCorr->pReducedCorrelator2EtaGap[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);
                    // TProfile for covariance calculation in statistic error
                    pCovCorr->pCov22RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22Gap * redCor22Gap[ieta][ipt][id], w2Gap * wred2Gap[ieta][ipt][id]);
                }
            }
        }
    }
}

bool trackCut(PicoDstRecoTrack *recoTrack)
{
    if (!recoTrack)
    {
        return false;
    }

    float pt = recoTrack->GetPt();
    float eta = recoTrack->GetEta();

    if (pt < minpt || pt > maxpt || abs(eta) > eta_cut)
        return false;
    if (abs(recoTrack->GetDCAx()) > DCAcut)
        return false; // DCAx cut
    if (abs(recoTrack->GetDCAy()) > DCAcut)
        return false; // DCAy cut
    if (abs(recoTrack->GetDCAz()) > DCAcut)
        return false; // DCAz cut
    if (recoTrack->GetNhits() < Nhits_cut)
        return false; // TPC hits cut    

    return true;                                   
}

int findBin(float pt)
{
    int ipt = -1;
    
    for (int j = 0; j < npt; j++)
    {
        if (pt >= pTBin[j] && pt < pTBin[j + 1])
        ipt = j;
    }
    
    return ipt;
}

int findId(PicoDstRecoTrack *recoTrack)
{
    int fId = -1;

    float charge = recoTrack->GetCharge();
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

    return fId;
}

void FlowQCumulant(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Configure input information
  TChain *chain = initChain(inputFileName, "picodst");

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
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  CCorrelator corr;
  CCovCorrelator cov_corr;

  // Start event loop

  CQC24   qc24;
  CQC2eg  qc2eg;

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

    int reco_mult = recoTracks->GetEntriesFast();

    qc24.zero();
    qc2eg.zero();

    qc24.fCentBin = GetCentBin(cent);
    qc2eg.fCentBin = GetCentBin(cent);


    float pt, eta, phi, charge;
    Double_t cos4phi, sin4phi, cos2phi, sin2phi;
    CPhiAngles phiAngles;

    for (int iTrk = 0; iTrk < reco_mult; iTrk++)
    { // Track loop
      auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(iTrk);
      if (!trackCut(recoTrack))
      {
        continue;
      }

      pt = recoTrack->GetPt();
      eta = recoTrack->GetEta();
      phi = recoTrack->GetPhi();
      charge = recoTrack->GetCharge();

      int ipt = findBin(pt);
      int fId = findId(recoTrack);

      phiAngles.recalc(phi);

      if (pt > minptRF && pt < maxptRF)
      { // Reference Flow pt cut
        // 2,4-QC
        qc24.setQxQy(phiAngles);
        qc2eg.setQxQy(phiAngles, eta);
      }

      // Differential Flow of 2,4-QC
      qc24.setQP(phiAngles, ipt, charge, fId);
      
      // Differential Flow of 2-QC, eta-gapped
      qc2eg.setPxPy(phiAngles, ipt, eta, charge, fId);
      
    } // end of track loop

    // 2-QC, eta-gapped: multi-particle correlation calculation
    qc2eg.calcMPCorr(&corr, &cov_corr);

    // 2,4-QC: multi-particle correlation calculation
    qc24.calcMPCorr(&corr, &cov_corr);
  } // end event loop

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}

int main(int argc, char **argv)
{
  TString iFileName, oFileName;

  if (argc < 5)
  {
    std::cerr << "./FlowQCumulant -i INPUT -o OUTPUT" << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" &&
        std::string(argv[i]) != "--bad-acceptance")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 3;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 4;
      }
    }
  }

  FlowQCumulant(iFileName, oFileName);

  return 0;
}
