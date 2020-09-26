#ifndef FLOW_CHECK_C
#define FLOW_CHECK_C

#include <iostream>
#include <TROOT.h>
#include <TMath.h>

// Event selection
float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
    float fcent;
  if (bimp < 4.18)
    fcent = 0; // 0-10%
  else if (bimp < 6.01)
    fcent = 10; //10-20%
  else if (bimp < 7.37)
    fcent = 20; //20-30%
  else if (bimp < 8.52)
    fcent = 30; //30-40%
  else if (bimp < 9.57)
    fcent = 40; //40-50%
  else if (bimp < 10.55)
    fcent = 50; //50-60%
  else if (bimp < 11.46)
    fcent = 60; //60-70%
  else if (bimp < 12.31)
    fcent = 70; //70-80%
  else
    fcent = -1;

  if (fcent != -1)
    return fcent + 5.;
  else
    return -1;
}

int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 5.) return 0;
  if (cent == 15.) return 1;
  if (cent == 25.) return 2;
  if (cent == 35.) return 3;
  if (cent == 45.) return 4;
  if (cent == 55.) return 5;
  if (cent == 65.) return 6;
  if (cent == 75.) return 7;
  return -1;
}

// Profile info - general
const int NcentBins     = 8;
const double centBinMin = 0.;
const double centBinMax = 80.;
const int NptBins       = 300;
const double ptBinMin   = 0.;
const double ptBinMax   = 3.;
const int NQvBins       = 240;
const double QvBinMin   = -1.2;
const double QvBinMax   = 1.2;

// Track cuts - general
const float pt_min_cut = 0.2;
const float pt_max_cut = 3.;
const float eta_cut    = 1.5;
const float eta_gap    = 0.05;
const int   mult_EP_cut= 2;

// Track cuts - mc tracks
const int motherId_cut = -1;

// Track cuts - reco tracks
const int Nhits_cut    = 32;
const float dca_cut    = 0.5;

// PID - general
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
const int Npid = 8; //pidNames.size()

// PID - mc/model tracks
const std::vector<int> pdgCodes = {999, 211, 321, 2212, -999, -211, -321, -2212};

// PID - reco tracks
const float PidProb_cut = 0.9;

#endif
