#ifndef FLOWANALYSISWITHTHREEETASUBEVENTPLANE_H
#define FLOWANALYSISWITHTHREEETASUBEVENTPLANE_H
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

using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithThreeEtaSubEventPlane
{
public:
  FlowAnalysisWithThreeEtaSubEventPlane();
  virtual ~FlowAnalysisWithThreeEtaSubEventPlane();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoopFHCal(const Double_t &eta, const Double_t &phi, const Double_t &pt);
  void ProcessFirstTrackLoopTPC(const Double_t &eta, const Double_t &phi, const Double_t &pt);
  void ProcessEventAfterFirstTrackLoop(const Double_t &dCent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent);
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SetFirstRun(bool kt) { this->fFirstRun = kt; }
  void SetDebugFlag(bool kt) { this->fDebug = kt; }
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void GetRes();
  void SaveHist();
private:
  bool fFirstRun;
  bool fMultCut;
  bool fDebug;
  Double_t fPsi_L;
  Double_t fPsi_R;
  Double_t fPsi_FHCal;
  QVector *fQvector_L;
  QVector *fQvector_R;
  QVector *fQvector_FHCal;
  Double_t fResTPCL[ncent];
  Double_t fResTPCR[ncent];
  Double_t fEtaGap;
  TString fstrInputFileFromFirstRun;
  TProfile *fPrResTPCLvsR;
  TProfile *fPrResTPCLvsFHCal;
  TProfile *fPrResTPCRvsFHCal;
  TProfile3D *fPrV2ThreeEtaSub;
  ClassDef(FlowAnalysisWithThreeEtaSubEventPlane,0);

};

#endif