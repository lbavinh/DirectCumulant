#ifndef FLOWANALYSISWITHETASUBEVENTPLANE_H
#define FLOWANALYSISWITHETASUBEVENTPLANE_H
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

class FlowAnalysisWithEtaSubEventPlane
{
public:
  FlowAnalysisWithEtaSubEventPlane();
  virtual ~FlowAnalysisWithEtaSubEventPlane();
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const double &eta, const double &phi, const double &pt);
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
  double fPsi_L;
  double fPsi_R;
  QVector *fQvector_L;
  QVector *fQvector_R;
  double fRes2[ncent];
  double fEtaGap;
  TString fstrInputFileFromFirstRun;
  TProfile *fPrRes;
  TProfile3D *fPrV2EtaSubEventPlane;
  ClassDef(FlowAnalysisWithEtaSubEventPlane,0);

};

#endif