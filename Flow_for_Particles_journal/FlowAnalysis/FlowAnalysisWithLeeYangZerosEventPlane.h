#ifndef FLOWANALYSISWITHLEEYANGZEROSEVENTPLANE_H
#define FLOWANALYSISWITHLEEYANGZEROSEVENTPLANE_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile3D.h>
#include <TString.h>
#include <TComplex.h>
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
  // void ProcessFirstTrackLoop(const Double_t &phi, const Double_t &pt, const Int_t &icent);
  void ProcessEventAfterFirstTrackLoop(const QVector *const &Qvector, const Int_t &icent);
  void ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent);
  void SetInputFileFromFirstAndSecondRun(TString str, TString str2) { this->fstrInputFileFromFirstRun = str; this->fstrInputFileFromSecondRun = str2;}
  void ProcessRootFileWithHistFromFirstRun();
  void GetHistFromLYZSecondRun();
  TH1F *FillHistGtheta(const TProfile *const &prReGtheta, const TProfile *const &prImGtheta);
  Double_t GetR0(const TH1F *const &hist);

  void SaveHist();

private:
  Bool_t fDebug;
  Double_t fTheta[thetabins];
  Double_t fQtheta[thetabins];
  Double_t fWR;
  Double_t fPsiR;
  TString fstrInputFileFromFirstRun;
  TString fstrInputFileFromSecondRun;

  Double_t fR02Sum[ncent][thetabins];
  TFile *fiHistogramFromSecondRun;
  TProfile *fPrReDtheta[thetabins];
  TProfile *fPrImDtheta[thetabins];

  TProfile3D *fPrV2LYZEP;

  ClassDef(FlowAnalysisWithLeeYangZerosEventPlane,0);
};

#endif