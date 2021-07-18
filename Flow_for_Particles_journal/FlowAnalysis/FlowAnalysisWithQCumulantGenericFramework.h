#ifndef FLOWANALYSISWITHQCUMULANTGENERICFRAMEWORK_H
#define FLOWANALYSISWITHQCUMULANTGENERICFRAMEWORK_H
#include <iostream>
#include <TMath.h>
#include <TProfile.h>
#include <TString.h>
#include <TComplex.h>
#include "QVector.h"

using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithQCumulantGenericFramework
{
public:
  FlowAnalysisWithQCumulantGenericFramework();
  virtual ~FlowAnalysisWithQCumulantGenericFramework();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoopRP(const Double_t &eta, const Double_t &phi);
  void ProcessFirstTrackLoopPOI(const Int_t &ipt, const Double_t &eta, const Double_t &phi, const Int_t &pid, const Double_t &charge);
  void ProcessEventAfterFirstTrackLoop(const Int_t &icent);
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SaveHist();

  TComplex Q(Int_t n, Int_t p) const;
  TComplex QGapPos(Int_t n, Int_t p) const;
  TComplex QGapNeg(Int_t n, Int_t p) const;
  TComplex Two(Int_t n1, Int_t n2) const;
  TComplex TwoGap(Int_t n1, Int_t n2) const;
  TComplex Three(Int_t n1, Int_t n2, Int_t n3) const;
  TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4) const;
  TComplex FourGap(Int_t n1, Int_t n2, Int_t n3, Int_t n4) const;
  TComplex Five(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5) const;
  TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6) const;
  TComplex Seven(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7) const;
  TComplex Eight(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8) const;
  TComplex Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0);

  TComplex P(Int_t n, Int_t p, Int_t ipt, Int_t pid) const;
  TComplex PGapPos(Int_t n, Int_t p, Int_t ipt, Int_t pid) const;
  TComplex PGapNeg(Int_t n, Int_t p, Int_t ipt, Int_t pid) const;
  TComplex S(Int_t n, Int_t p, Int_t ipt, Int_t pid) const;
  TComplex SGapPos(Int_t n, Int_t p, Int_t ipt, Int_t pid) const;
  TComplex SGapNeg(Int_t n, Int_t p, Int_t ipt, Int_t pid) const;
  TComplex TwoDiff(Int_t n1, Int_t n2, Int_t ipt, Int_t pid) const;
  TComplex TwoDiffGapPos(Int_t n1, Int_t n2, Int_t ipt, Int_t pid) const;
  TComplex TwoDiffGapNeg(Int_t n1, Int_t n2, Int_t ipt, Int_t pid) const;
  TComplex ThreeDiff(Int_t n1, Int_t n2, Int_t n3, Int_t ipt, Int_t pid) const;
  TComplex FourDiff(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t ipt, Int_t pid) const;
  TComplex FourDiffGapPos(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t ipt, Int_t pid) const;
  TComplex FourDiffGapNeg(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t ipt, Int_t pid) const;

private:
  Int_t M;
  Double_t fEtaGap;
  Bool_t fUseWeight;
  TComplex fQvector[maxHarmonic][maxPower];
  TComplex fQvectorGapPos[maxHarmonic][maxPower];
  TComplex fQvectorGapNeg[maxHarmonic][maxPower];
  TComplex fPvector[maxHarmonic][maxPower][npt][npid];
  TComplex fSvector[maxHarmonic][maxPower][npt][npid];
  TComplex fPvectorGapPos[maxHarmonic][maxPower][npt][npid];
  TComplex fSvectorGapPos[maxHarmonic][maxPower][npt][npid];
  TComplex fPvectorGapNeg[maxHarmonic][maxPower][npt][npid];
  TComplex fSvectorGapNeg[maxHarmonic][maxPower][npt][npid];    
  TProfile *recursion[maxCorrelator][ncent];    // Correlations calculated from Q-vector components using recursive algorithm
  TProfile *pCovariance[6][ncent];

  TProfile *hv22[ncent];                        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];                        // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt[ncent][npt][npid];           // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];           // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];                      // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>

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

  TProfile *hcounter[ncent][npt][npid];             

  ClassDef(FlowAnalysisWithQCumulantGenericFramework, 0);
};

#endif

