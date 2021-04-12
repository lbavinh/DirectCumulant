#ifndef FLOWANALYSISWITHSCARLARPRODUCT_H
#define FLOWANALYSISWITHSCARLARPRODUCT_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>
#include <TDatabasePDG.h>
#include <TString.h>
#include <TComplex.h>
#include <TDirectoryFile.h>
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
  void ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight);
  void ProcessEventAfterFirstTrackLoop(const Double_t &dCent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge);
  void SetFirstRun(Bool_t kt) { this->fFirstRun = kt; }
  void SetHarmonic(Int_t i) { this->fHarmonic = i; }
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void GetRes();
  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);
private:
  Bool_t fFirstRun;
  Bool_t fMultCut;
  Int_t fHarmonic;
  Double_t fEtaGap;
  TComplex fcQVector_L;
  TComplex fcQVector_R;
  QVector *fQvector_L;
  QVector *fQvector_R;
  Double_t fDenom[ncent];
  TString fstrInputFileFromFirstRun;
  TProfile *fPrDenom;
  TProfile2D *fPrV2vsPt[npid];
  TProfile2D *fPrV2vsEta;
  TProfile3D *fPrV2ScalarProduct;
  ClassDef(FlowAnalysisWithScalarProduct,0);

};

#endif