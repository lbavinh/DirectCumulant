#ifndef FLOWANALYSISWITHQCUMULANT_H
#define FLOWANALYSISWITHQCUMULANT_H
#include <iostream>
#include <TMath.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TString.h>
#include <TComplex.h>
#include <TDirectoryFile.h>
#include "QVector.h"

using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithQCumulant
{
public:
  FlowAnalysisWithQCumulant();
  virtual ~FlowAnalysisWithQCumulant();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoopRP(const Double_t &eta, const Double_t &phi);
  void ProcessFirstTrackLoopPOI(const Int_t &ipt, const Double_t &eta, const Double_t &phi, const Int_t &pid, const Double_t &charge);
  void ProcessEventAfterFirstTrackLoop(const Int_t &icent);
  void SetHarmonic(Int_t i) { this->fHarmonic = i; }
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);

  TComplex Qstar(const TComplex &Q);
  Double_t CalCor22(const TComplex &Q2, const Double_t &M, const Double_t &w2);
  Double_t CalCor24(const TComplex &Q2, const TComplex &Q4, const Double_t &M, const Double_t &w4);
  Double_t CalRedCor22(const TComplex &Q2, const TComplex &p2, const Double_t &M,
                     const Double_t &mp, const Double_t &mq, const Double_t &wred2);
  Double_t CalRedCor24(const TComplex &Q2, const TComplex &Q4, const TComplex &p2, const TComplex &q2,
                     const TComplex &q4, const Double_t &M, const Double_t &mp, const Double_t &mq, const Double_t &wred4);
  Double_t CalCor24TwoSub(const TComplex &Q2a, const TComplex &Q4a, const TComplex &Q2b, const TComplex &Q4b, const Double_t &Ma, const Double_t &Mb);
  Double_t CalRedCor24TwoSub(const TComplex &Q2a, const TComplex &Q2b, const TComplex &Q4b,
                           const TComplex &p2a, const TComplex &q2a, const TComplex &q4a,
                           const Double_t &Ma, const Double_t &Mb, const Double_t &mpa, const Double_t &mqa);
private:
  Int_t fHarmonic;
  Double_t fEtaGap;
  // 2,QC & 4,QC without eta-gap
  Double_t Q2x, Q2y, Q4x, Q4y;
  TComplex Q2, Q4;
  Double_t p2x[npt][npidQC], p2y[npt][npidQC];
  TComplex p2[npt][npidQC], q2[npt][npidQC], q4[npt][npidQC];
  Double_t q2x[npt][npidQC], q2y[npt][npidQC], q4x[npt][npidQC], q4y[npt][npidQC];
  Double_t M = 0.;
  Double_t mq[npt][npidQC], mp[npt][npidQC];
  Double_t redCor22[npt][npidQC], redCor24[npt][npidQC];
  Double_t w2, w4;
  Double_t wred2[npt][npidQC], wred4[npt][npidQC];
  Double_t cor22, cor24;

  // 2,4-QC with 2-sub
  Double_t Q2xGap[neta], Q2yGap[neta];
  Double_t Q4xGap[neta], Q4yGap[neta];
  Double_t p2xGap[neta][npt][npidQC], p2yGap[neta][npt][npidQC];
  Double_t q2xGap[neta][npt][npidQC], q2yGap[neta][npt][npidQC], q4xGap[neta][npt][npidQC], q4yGap[neta][npt][npidQC];
  TComplex Q2Gap[neta], Q4Gap[neta], p2Gap[neta][npt][npidQC], q2Gap[neta][npt][npidQC], q4Gap[neta][npt][npidQC];
  Double_t MGap[neta];
  Double_t mpGap[neta][npt][npidQC], mqGap[neta][npt][npidQC];
  Double_t w2Gap, w4Gap;
  Double_t wred2Gap[neta][npt][npidQC], wred4Gap[neta][npt][npidQC];
  Double_t cor22Gap, cor24Gap;
  Double_t redCor22Gap[neta][npt][npidQC], redCor24Gap[neta][npt][npidQC];

  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt[ncent][npt][npidQC];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npidQC];  // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npidQC];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npidQC];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npidQC];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npidQC];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npidQC]; // <2'>*<4'>

  TProfile *hcounter[ncent][npt][npidQC];
  TProfile *hmult[ncent][npt][npidQC];

  // 2,4 QC 2-sub
  TProfile *hv22Gap[ncent];                         // <2>
  TProfile *hv24Gap[ncent];                         // <4>  
  TProfile *hcov24Gap[ncent];                       // <2><4>
  TProfile *hv22ptGap[ncent][npt][npidQC];            // <2'>
  TProfile *hv24ptGap[ncent][npt][npidQC];            // <4'>
  TProfile *hcov22primeGap[ncent][npt][npidQC];       // <2><2'>  
  TProfile *hcov24primeGap[ncent][npt][npidQC];       // <2><4'>
  TProfile *hcov42primeGap[ncent][npt][npidQC];       // <2><4'>
  TProfile *hcov44primeGap[ncent][npt][npidQC];       // <4><4'>
  TProfile *hcov2prime4primeGap[ncent][npt][npidQC];  // <2'><4'>

  // covariance for v2{4}/v2{2,subevent} ratio
  TProfile *hcov2Gap4[ncent];                         // <2>_{a|b}  * <4>  
  TProfile *hcov2primeGap4[ncent][npt][npidQC];       // <2'>_{a|b} * <4>
  TProfile *hcov2Gap4prime[ncent][npt][npidQC];       // <2>_{a|b}  * <4'>
  TProfile *hcov2primeGap4prime[ncent][npt][npidQC];  // <2'>_{a|b} * <4'>

  // testing Cochran-Endlich variance of the weighted mean (Eq. 17) http://arxiv.org/abs/2104.00588
  TProfile *hv22_Variance[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24_Variance[ncent];  // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt_Variance[ncent][npt][npidQC];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt_Variance[ncent][npt][npidQC];  // profile <<4'>> from 4th Q-Cumulants  
  TProfile *hv22Gap_Variance[ncent];                         // <2>
  TProfile *hv24Gap_Variance[ncent];                         // <4>  
  TProfile *hv22ptGap_Variance[ncent][npt][npidQC];            // <2'>
  TProfile *hv24ptGap_Variance[ncent][npt][npidQC];            // <4'>
  ClassDef(FlowAnalysisWithQCumulant, 0);
};

#endif

