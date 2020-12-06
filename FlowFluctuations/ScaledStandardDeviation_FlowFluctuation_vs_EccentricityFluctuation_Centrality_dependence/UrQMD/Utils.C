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
  // for sqrt{sNN} = 7.7 GeV
  float fcent;
  if (bimp < 2.91)
    fcent = 0; // 0-5%
  else if (bimp < 4.17)
    fcent = 5; // 5-10%
  else if (bimp < 5.18)
    fcent = 10; //10-15%
  else if (bimp < 6.02)
    fcent = 15; //15-20%
  else if (bimp < 6.74)
    fcent = 20; //20-25%
  else if (bimp < 7.38)
    fcent = 25; //25-30%
  else if (bimp < 7.97)
    fcent = 30; //30-35%
  else if (bimp < 8.53)
    fcent = 35; //35-40%    
  else if (bimp < 9.06)
    fcent = 40; //40-45%
  else if (bimp < 9.56)
    fcent = 45; //45-50%    
  else if (bimp < 10.05)
    fcent = 50; //50-55%
  else if (bimp < 10.50)
    fcent = 55; //55-60%    
  else if (bimp < 10.94)
    fcent = 60; //60-65%
  else if (bimp < 11.35)
    fcent = 65; //65-70%    
  else if (bimp < 11.76)
    fcent = 70; //70-75%
  else if (bimp < 12.19)
    fcent = 75; //75-80%
  else if (bimp < 12.68)
    fcent = 80; //80-85%
  else if (bimp < 13.27)
    fcent = 85; //85-90%
  else if (bimp < 14.04)
    fcent = 90; //90-95%            
  else if (bimp < 15.08)
    fcent = 95; //95-100%  
  else
    fcent = -1;

  if (fcent != -1)
    return fcent + 2.5;
  else
    return -1;
}

int GetCentBin(float cent)
{
  if (cent == -1)
    return -1;
  if (cent == 2.5)
    return 0;
  if (cent == 7.5)
    return 1;
  if (cent == 12.5)
    return 2;
  if (cent == 17.5)
    return 3;
  if (cent == 22.5)
    return 4;
  if (cent == 27.5)
    return 5;
  if (cent == 32.5)
    return 6;
  if (cent == 37.5)
    return 7;
  if (cent == 42.5)
    return 8;
  if (cent == 47.5)
    return 9;
  if (cent == 52.5)
    return 10;
  if (cent == 57.5)
    return 11;
  if (cent == 62.5)
    return 12;
  if (cent == 67.5)
    return 13;
  if (cent == 72.5)
    return 14;
  if (cent == 77.5)
    return 15;
  if (cent == 82.5)
    return 16;
  if (cent == 87.5)
    return 17;
  if (cent == 92.5)
    return 18;
  if (cent == 97.5)
    return 19;
  return -1;
}

// Profile info - general
const int NcentBins = 20;
const double centBinMin = 0.;
const double centBinMax = 100.;
const int NptBins = 300;
const double ptBinMin = 0.;
const double ptBinMax = 3.;
const int NQvBins = 240;
const double QvBinMin = -1.2;
const double QvBinMax = 1.2;

// Track cuts - general
const float pt_min_cut = 0.2;
const float pt_max_cut = 3.;
const float eta_cut = 1.5;
const float eta_gap = 0.05;
const int mult_EP_cut = 2;

// Track cuts - mc tracks
const int motherId_cut = -1;

// Track cuts - reco tracks
const int Nhits_cut = 32;
const float dca_cut = 0.5;

// PID - general
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
const int Npid = 8; //pidNames.size()

// PID - mc/model tracks
const std::vector<int> pdgCodes = {999, 211, 321, 2212, -999, -211, -321, -2212};

// PID - reco tracks
const float PidProb_cut = 0.9;

#endif
