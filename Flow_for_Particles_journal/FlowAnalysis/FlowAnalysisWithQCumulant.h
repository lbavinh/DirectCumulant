#ifndef FLOWANALYSISWITHQCUMULANT_H
#define FLOWANALYSISWITHQCUMULANT_H
#include <iostream>
#include <TMath.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TString.h>
#include <TComplex.h>
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
  void ProcessFirstTrackLoopRP(const double &eta, const double &phi);
  void ProcessFirstTrackLoopPOI(const int &ipt, const double &eta, const double &phi, const int &pid, const double &charge);
  void ProcessEventAfterFirstTrackLoop(const int &icent);
  void SetEtaGap(double d) { this->fEtaGap = d; }
  void SaveHist();

  TComplex Qstar(const TComplex &Q);
  double CalCor22(const TComplex &Q2, const double &M, const double &w2);
  double CalCor24(const TComplex &Q2, const TComplex &Q4, const double &M, const double &w4);
  double CalRedCor22(const TComplex &Q2, const TComplex &p2, const double &M,
                     const double &mp, const double &mq, const double &wred2);
  double CalRedCor24(const TComplex &Q2, const TComplex &Q4, const TComplex &p2, const TComplex &q2,
                     const TComplex &q4, const double &M, const double &mp, const double &mq, const double &wred4);
  double CalCor24TwoSub(const TComplex &Q2a, const TComplex &Q4a, const TComplex &Q2b, const TComplex &Q4b, const double &Ma, const double &Mb);
  double CalRedCor24TwoSub(const TComplex &Q2a, const TComplex &Q2b, const TComplex &Q4b,
                           const TComplex &p2a, const TComplex &q2a, const TComplex &q4a,
                           const double &Ma, const double &Mb, const double &mpa, const double &mqa);
private:
  double fEtaGap;

  // 2,QC & 4,QC without eta-gap
  Double_t Q2x, Q2y, Q4x, Q4y;
  TComplex Q2, Q4;
  Double_t p2x[npt][npid], p2y[npt][npid];
  TComplex p2[npt][npid], q2[npt][npid], q4[npt][npid]; // , p4[npt][npid]
  Double_t q2x[npt][npid], q2y[npt][npid], q4x[npt][npid], q4y[npt][npid];
  Double_t M = 0.;
  Double_t mq[npt][npid], mp[npt][npid];
  Double_t redCor22[npt][npid], redCor24[npt][npid];
  Double_t w2, w4;
  Double_t wred2[npt][npid], wred4[npt][npid];
  Double_t cor22, cor24;

  // 2,4-QC with 2-sub
  Double_t Q2xGap[neta], Q2yGap[neta];
  Double_t Q4xGap[neta], Q4yGap[neta];
  Double_t p2xGap[neta][npt][npid], p2yGap[neta][npt][npid];
  Double_t q2xGap[neta][npt][npid], q2yGap[neta][npt][npid], q4xGap[neta][npt][npid], q4yGap[neta][npt][npid];
  TComplex Q2Gap[neta], Q4Gap[neta], p2Gap[neta][npt][npid], q2Gap[neta][npt][npid], q4Gap[neta][npt][npid];
  Double_t MGap[neta];
  Double_t mpGap[neta][npt][npid], mqGap[neta][npt][npid];
  Double_t w2Gap, w4Gap;
  Double_t wred2Gap[neta][npt][npid], wred4Gap[neta][npt][npid];
  Double_t cor22Gap, cor24Gap;
  Double_t redCor22Gap[neta][npt][npid], redCor24Gap[neta][npt][npid];

  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt[ncent][npt][npid];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];  // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>

  TProfile *hcounter[ncent][npt][npid]; // for testing how different are particle entries of each method
  // 2,4 QC 2-sub
  TProfile *hv22Gap[ncent];                         // <2>
  TProfile *hv24Gap[ncent];                         // <4>  
  TProfile *hcov24Gap[ncent];                       // <2><4>
  TProfile *hv22ptGap[ncent][npt][npid];            // <2'>
  TProfile *hv24ptGap[ncent][npt][npid];            // <4'>
  TProfile *hcov22primeGap[ncent][npt][npid];       // <2><2'>  
  TProfile *hcov24primeGap[ncent][npt][npid];       // <2><4'>
  TProfile *hcov42primeGap[ncent][npt][npid];       // <2><4'>
  TProfile *hcov44primeGap[ncent][npt][npid];       // <4><4'>
  TProfile *hcov2prime4primeGap[ncent][npt][npid];  // <2'><4'>

  ClassDef(FlowAnalysisWithQCumulant, 0);
};

#endif

