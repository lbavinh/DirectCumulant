#ifndef FLOWANALYSISWITHLEEYANGZEROS_H
#define FLOWANALYSISWITHLEEYANGZEROS_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TString.h>
#include <TComplex.h>
#include "QVector.h"
// #include "../constants.C"
using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithLeeYangZeros
{
public:
  FlowAnalysisWithLeeYangZeros();
  virtual ~FlowAnalysisWithLeeYangZeros();
  void SetDebugFlag(bool bDebug) { this->fDebug = bDebug; }
  void SetUseProduct(bool kt) {this->fUseProduct = kt; }
  bool GetUseProduct() const { return this->fUseProduct; }
  void SetFirstRun(bool kt) { this->fFirstRun = kt; }
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const double &phi, const double &pt, const int &icent);
  void ProcessEventAfterFirstTrackLoop(const QVector *const Qvector, const int &icent);
  void ProcessSecondTrackLoop(double phi, double pt, int icent);
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void ProcessRootFileWithHistFromFirstRun();
  TH1F *FillHistGtheta(const TProfile *const prReGtheta, const TProfile *const prImGtheta);
  double GetR0(const TH1F *const hist);

  void SaveHist();

private:
  bool fDebug;
  bool fUseProduct;
  bool fFirstRun;
  double fTheta[thetabins];
  double fQtheta[thetabins];

  // First run
  // Integrated flow
  TProfile *fPrReGthetaSum[ncent][thetabins];
  TProfile *fPrImGthetaSum[ncent][thetabins];
  TH1F *fHistGthetaSum;

  TProfile *fPrReGthetaProduct[ncent][thetabins];
  TProfile *fPrImGthetaProduct[ncent][thetabins];
  TH1F *fHistGthetaProduct;

  double fRSum[rbins];
  double fRProduct[rbins];
  double fMult;
  TComplex fGenFunS[rbins][thetabins]; // sum
  TComplex fGenFunP[rbins][thetabins]; // product

  TProfile *prRefMult;
  TProfile *prQ2x;
  TProfile *prQ2y;
  TProfile *prQ2ModSq;

  // Second run
  // Differential flow
  TString fstrInputFileFromFirstRun;
  TProfile *fPrReDenom[thetabins];
  TProfile *fPrImDenom[thetabins];
  TProfile *fPrReNumer[thetabins][ncent];
  TProfile *fPrImNumer[thetabins][ncent];
  TProfile *fPrMultPOI[ncent];
  TProfile *fPrReDenomPro[thetabins];
  TProfile *fPrImDenomPro[thetabins];
  TProfile *fPrReNumerPro[thetabins][ncent];
  TProfile *fPrImNumerPro[thetabins][ncent];
  double fMultPOI[npt];
  TComplex fExponent[thetabins];
  TComplex fdGr0[thetabins];
  TComplex fGenfunPror0[thetabins];
  double fR02Sum[ncent][thetabins];
  double fR02Pro[ncent][thetabins];

  ClassDef(FlowAnalysisWithLeeYangZeros,0);
};

#endif