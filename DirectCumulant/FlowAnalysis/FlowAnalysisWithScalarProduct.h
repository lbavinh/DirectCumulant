#ifndef FLOWANALYSISWITHSCARLARPRODUCT_H
#define FLOWANALYSISWITHSCARLARPRODUCT_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile3D.h>
#include <TDatabasePDG.h>
#include <TString.h>
#include <TComplex.h>
#include "QVector.h"

using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithScalarProduct
{
public:
  FlowAnalysisWithScalarProduct();
  virtual ~FlowAnalysisWithScalarProduct();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const double &eta, const double &phi);
  void ProcessEventAfterFirstTrackLoop(const double &dCent);
  void ProcessSecondTrackLoop(const double &eta, const double &phi, const double &pt, const double &dCent);
  void SetEtaGap(double d) { this->fEtaGap = d; }
  void SetFirstRun(bool kt) { this->fFirstRun = kt; }
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void GetRes();
  void SaveHist();
private:
  bool fFirstRun;
  bool fMultCut;
  TComplex fcQVector_L;
  TComplex fcQVector_R;
  QVector *fQvector_L;
  QVector *fQvector_R;
  double fDenom[ncent];
  double fEtaGap;
  TString fstrInputFileFromFirstRun;
  TProfile *fPrDenom;
  TProfile3D *fPrV2ScalarProduct;
  ClassDef(FlowAnalysisWithScalarProduct,0);

};

#endif