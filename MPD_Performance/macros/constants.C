#include <vector>
#include <RtypesCore.h>
#include <TString.h>


// Constant declaration
const Int_t npid = 12; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-, h, pions, kaons, protons and antiproton
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "antiproton","hadron", "pion", "kaon", "proton_antiproton"};
const Int_t npidQC = 8; // due to some specific problems, for QC, I will merged TProfile later to obtain 12 npid when plotting in macros/PlotV2QCumulant.C

// const Int_t npt = 17; // 0-3.6 GeV/c - number of pT bins
// const Double_t pTBin[npt + 1] = {0., 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0};

const Int_t npt = 9; // 0-3.6 GeV/c - number of pT bins
const Double_t pTBin[npt + 1] = {0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};


const Int_t neta = 2; // [eta-,eta+]

const Int_t netaBin = 16;
const Double_t etaBin[netaBin+1] = {-1.5, -1.2, -1., -0.8, -0.6, -0.4, -0.2, -0.1, 0.0, 0.1, 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.5};
const Int_t mult_EP_cut = 4;
const Int_t ncent = 9;
const Double_t bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};

// LYZ
const Int_t rbins = 2500;
const Double_t rMinPro = 0.0;
const Double_t rMaxPro = 1.0;
const Double_t rMaxProWithMweight = 250.0; // using particle weight 1/M to reduce the effect of multiplicity fluctuations
const Double_t rMinSum = 0.0;
const Double_t rMaxSum = 1.0;
const Double_t rMaxSumWithMweight = 250.0; // using particle weight 1/M to reduce the effect of multiplicity fluctuations
const Int_t nTheta = 5;

// QCumulant - High Order
// Pick up randomly some harmonics:
const Int_t h1=2, h2=-2, h3=2, h4=-2, h5=2, h6=-2, h7=2, h8=-2;
// Book Q-vector components: 
const Int_t sum = (h1<0?-1*h1:h1)+(h2<0?-1*h2:h2)+(h3<0?-1*h3:h3)+(h4<0?-1*h4:h4) 
                + (h5<0?-1*h5:h5)+(h6<0?-1*h6:h6)+(h7<0?-1*h7:h7)+(h8<0?-1*h8:h8);
const Int_t maxCorrelator = 8; // We will not go beyond 8-p correlations
const Int_t maxHarmonic = sum+1;
const Int_t maxPower = maxCorrelator+1;

// LYZ-EP
const Double_t rootJ0 = 2.4048256;