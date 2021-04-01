#ifndef FLOWANALYSISWITHLEEYANGZEROS_H
#define FLOWANALYSISWITHLEEYANGZEROS_H
#include <iostream>
#include <TFile.h>
#include <TMath.h>
#include <TH1.h>
#include <TProfile.h>
#include <TString.h>
#include <TComplex.h>
#include "QVector.h"
using std::cerr;
using std::cout;
using std::endl;

class FlowAnalysisWithLeeYangZeros
{
public:
  FlowAnalysisWithLeeYangZeros();
  virtual ~FlowAnalysisWithLeeYangZeros();
  void SetDebugFlag(Bool_t bDebug) { this->fDebug = bDebug; }
  void SetUseProduct(Bool_t kt) {this->fUseProduct = kt; }
  Bool_t GetUseProduct() const { return this->fUseProduct; }
  void SetFirstRun(Bool_t kt) { this->fFirstRun = kt; }
  void SetWeight(Double_t kt) { this->fWeight = kt; }
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessFirstTrackLoop(const Double_t &phi, const Double_t &pt, const Int_t &icent);
  void ProcessEventAfterFirstTrackLoop(const QVector *const &Qvector, const Int_t &icent);
  void ProcessSecondTrackLoop(const Double_t &phi, const Double_t &pt, const Int_t &icent);
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void ProcessRootFileWithHistFromFirstRun();
  TH1F *FillHistGtheta(const TProfile *const &prReGtheta, const TProfile *const &prImGtheta);
  Double_t GetR0(const TH1F *const &hist);

  void SaveHist();

private:
  Bool_t fDebug;
  Bool_t fUseProduct;
  Bool_t fFirstRun;
  Double_t fTheta[thetabins];
  Double_t fQtheta[thetabins];

  // First run
  // Integrated flow
  TProfile *fPrReGthetaSum[ncent][thetabins];
  TProfile *fPrImGthetaSum[ncent][thetabins];
  TH1F *fHistGthetaSum;

  TProfile *fPrReGthetaProduct[ncent][thetabins];
  TProfile *fPrImGthetaProduct[ncent][thetabins];
  TH1F *fHistGthetaProduct;

  Double_t fRSum[rbins];
  Double_t fRProduct[rbins];
  Double_t fMult;
  Double_t fWeight;
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
  Double_t fMultPOI[npt];
  TComplex fExponent[thetabins];
  TComplex fdGr0[thetabins];
  TComplex fGenfunPror0[thetabins];
  Double_t fR02Sum[ncent][thetabins];
  Double_t fR02Pro[ncent][thetabins];

  // Event plane Lee Yang Zeros
  TProfile *fPrReDtheta[thetabins];
  TProfile *fPrImDtheta[thetabins];

  ClassDef(FlowAnalysisWithLeeYangZeros,0);
};

#endif