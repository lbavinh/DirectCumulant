#ifndef FLOWANALYSISWITHTHREEETASUBEVENTPLANE_H
#define FLOWANALYSISWITHTHREEETASUBEVENTPLANE_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>
#include <TDatabasePDG.h>
#include <TString.h>
#include <TDirectoryFile.h>

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
  void ProcessFirstTrackLoopFHCal(const Double_t &eta, const Double_t &phi, const Double_t &weight);
  void ProcessFirstTrackLoopTPC(const Double_t &eta, const Double_t &phi, const Double_t &pt);
  void ProcessEventAfterFirstTrackLoop(const Double_t &dCent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge);
  void SetEtaGap(Double_t d) { this->fEtaGap = d; }
  void SetFirstRun(Bool_t kt) { this->fFirstRun = kt; }
  void SetDebugFlag(Bool_t kt) { this->fDebug = kt; }
  void SetHarmonic(Int_t i) { this->fHarmonic = i; }
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void GetRes();
  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);
private:
  Bool_t fFirstRun;
  Bool_t fMultCut;
  Bool_t fDebug;
  Int_t fHarmonic;
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
  TProfile2D *fPrV2vsPt[npid];
  TProfile2D *fPrV2vsEta;
  TProfile3D *fPrV2ThreeEtaSub;
  ClassDef(FlowAnalysisWithThreeEtaSubEventPlane,0);

};

#endif