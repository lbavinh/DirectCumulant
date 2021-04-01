#ifndef FLOWANALYSISWITHHIGHORDERQCUMULANT_H
#define FLOWANALYSISWITHHIGHORDERQCUMULANT_H
#include <iostream>
#include <TMath.h>
#include <TProfile.h>
#include <TString.h>
#include <TComplex.h>
#include "QVector.h"

using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithHighOrderQCumulant
{
public:
  FlowAnalysisWithHighOrderQCumulant();
  virtual ~FlowAnalysisWithHighOrderQCumulant();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoopRP(const Double_t &phi);
  void ProcessEventAfterFirstTrackLoop(const Int_t &icent);
  void SaveHist();

  TComplex Q(Int_t n, Int_t p);
  TComplex Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0);

private:
  Int_t M;
  TComplex Qvector[maxHarmonic][maxPower];
  TProfile *recursion[maxCorrelator][ncent];    // Correlations calculated from Q-vector components using recursive algorithm
  TProfile *pCovariance[6][ncent];
  ClassDef(FlowAnalysisWithHighOrderQCumulant, 0);
};

#endif

