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
#include <TDirectoryFile.h>
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
  void SetFirstRun(Bool_t kt) { this->fFirstRun = kt; }
  void SetUseMultiplicityWeight(Bool_t kt) {this->fUseMultWeight = kt; }
  Bool_t GetUseMultiplicityWeight() const { return this->fUseMultWeight; }
  void Init();
  void Zero(); // Reset variables for new event loop
  void ProcessZeroTrackLoopRP(); // Need this method for Product LYZ
  void ProcessFirstTrackLoopRP(const Double_t &phi, const Double_t &pt, const Int_t &icent);
  void ProcessFirstTrackLoopPOI(const Double_t &pt);
  void ProcessEventAfterFirstTrackLoop(const Int_t &icent);
  void ProcessSecondTrackLoop(Double_t &phi, Double_t &pt, Int_t &icent);
  void SetInputFileFromFirstRun(TString str) { this->fstrInputFileFromFirstRun = str; }
  void ProcessRootFileWithHistFromFirstRun();
  TH1F *FillHistGtheta(const TProfile *const &prReGtheta, const TProfile *const &prImGtheta);
  Double_t GetR0(const TH1F *const &hist);

  void SaveHist();
  void SaveHist(TDirectoryFile *const &outputDir);

private:
  Bool_t fDebug;
  Bool_t fUseProduct;
  Bool_t fFirstRun;
  Bool_t fUseMultWeight;
  Double_t fTheta[nTheta];
  Double_t fQtheta[nTheta];
  QVector *fQn;
  // First run
  // Integrated flow
  TProfile *fPrReGthetaSum[ncent][nTheta];
  TProfile *fPrImGthetaSum[ncent][nTheta];
  TH1F *fHistGthetaSum;

  TProfile *fPrReGthetaPro[ncent][nTheta];
  TProfile *fPrImGthetaPro[ncent][nTheta];
  TH1F *fHistGthetaPro;

  Double_t fRSum[rbins];
  Double_t fRProduct[rbins];
  Int_t fMult; // multiplicity of reference particles
  TComplex fGenFunS;                // sum
  TComplex fGenFunP[rbins][nTheta]; // product
  Double_t fWeight;
  TProfile *fPrMultRP; // TProfile multiplicity of reference particles
  TProfile *fPrQ2x;
  TProfile *fPrQ2y;
  TProfile *fPrQ2ModSq;

  // Second run
  // Differential flow
  TString fstrInputFileFromFirstRun;
  TProfile *fPrReDenom[nTheta];
  TProfile *fPrImDenom[nTheta];
  TProfile *fPrReNumer[nTheta][ncent];
  TProfile *fPrImNumer[nTheta][ncent];
  TProfile *fPrMultPOI[ncent];
  TProfile *fPrReDenomPro[nTheta];
  TProfile *fPrImDenomPro[nTheta];
  TProfile *fPrReNumerPro[nTheta][ncent];
  TProfile *fPrImNumerPro[nTheta][ncent];
  Double_t fMultPOI[npt]; // multiplicity of particles of interest
  TComplex fExponent[nTheta];
  TComplex fdGr0[nTheta];
  TComplex fGenfunPror0[nTheta];
  Double_t fR02Sum[ncent][nTheta];
  Double_t fR02Pro[ncent][nTheta];

  // Event plane Lee Yang Zeros
  TProfile *fPrReDtheta[nTheta];
  TProfile *fPrImDtheta[nTheta];

  ClassDef(FlowAnalysisWithLeeYangZeros,0);
};

#endif