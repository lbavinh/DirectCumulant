#ifndef FLOWANALYSISWITHLEEYANGZEROSEVENTPLANE_H
#define FLOWANALYSISWITHLEEYANGZEROSEVENTPLANE_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>
#include <TString.h>
#include <TComplex.h>
#include <TDirectoryFile.h>
#include "QVector.h"

using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithLeeYangZerosEventPlane
{
public:
  FlowAnalysisWithLeeYangZerosEventPlane();
  virtual ~FlowAnalysisWithLeeYangZerosEventPlane();
  void SetDebugFlag(Bool_t bDebug) { this->fDebug = bDebug; }

  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessEventAfterFirstTrackLoop(const Int_t &icent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge);
  void SetInputFileFromFirstAndSecondRun(TString str, TString str2) { this->fstrInputFileFromFirstRun = str; this->fstrInputFileFromSecondRun = str2;}
  void ProcessRootFileWithHistFromFirstRun();
  void GetHistFromLYZSecondRun();
  TH1F *FillHistGtheta(const TProfile *const &prReGtheta, const TProfile *const &prImGtheta);
  Double_t GetR0(const TH1F *const &hist);

  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);

private:
  Bool_t fDebug;
  Double_t fTheta[nTheta];
  Double_t fQtheta[nTheta];
  QVector *fQn;
  Double_t fWR;
  Double_t fPsiR;
  TString fstrInputFileFromFirstRun;
  TString fstrInputFileFromSecondRun;

  Double_t fR02Sum[ncent][nTheta];
  TFile *fiHistogramFromSecondRun;
  TProfile *fPrReDtheta[nTheta];
  TProfile *fPrImDtheta[nTheta];
  TProfile2D *fPrV2vsPt[npid];
  TProfile2D *fPrV2vsEta;
  TProfile3D *fPrV2LYZEP;

  ClassDef(FlowAnalysisWithLeeYangZerosEventPlane,0);
};

#endif