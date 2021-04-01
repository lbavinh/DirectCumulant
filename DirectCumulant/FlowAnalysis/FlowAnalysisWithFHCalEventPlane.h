#ifndef FLOWANALYSISWITHFHCALEVENTPLANE_H
#define FLOWANALYSISWITHFHCALEVENTPLANE_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile3D.h>
#include <TDatabasePDG.h>
#include <TString.h>
#include "QVector.h"
#include <Math/SpecFuncMathMore.h>
using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithFHCalEventPlane
{
public:
  FlowAnalysisWithFHCalEventPlane();
  virtual ~FlowAnalysisWithFHCalEventPlane();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight);
  void ProcessEventAfterFirstTrackLoop(const Double_t &dCent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent);
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SetFirstRun(bool kt) { this->fFirstRun = kt; }
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void GetRes();
  Double_t Res(Double_t chi, Double_t harmonic);
  Double_t GetChi(Double_t _res, Double_t _harm, Int_t accuracy);
  void SaveHist();
  void SetDebugFlag(bool kt) { this->fDebug = kt; }
private:
  bool fFirstRun;
  bool fMultCut;
  bool fDebug;
  Double_t fPsi_L;
  Double_t fPsi_R;
  Double_t fPsi;
  QVector *fQvector_L;
  QVector *fQvector_R;
  Double_t fRes2[ncent];
  Double_t fEtaGap;
  TString fstrInputFileFromFirstRun;
  TProfile *fPrRes;
  TProfile *fPrV2FHCalEventPlaneIntegrated;
  TProfile3D *fPrV2FHCalEventPlane;
  ClassDef(FlowAnalysisWithFHCalEventPlane,0);

};

#endif