#include <vector>

#include <RtypesCore.h>
#include <TString.h>


// Constant declaration
const Int_t npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "antiproton"};
const Int_t ncent = 9; //

// const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
const Int_t npt = 16; // 0-3.6 GeV/c - number of pT bins
const Double_t pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};

const Int_t neta = 2; // [eta-,eta+]

const int netaBin = 10;
const double etaBin[netaBin+1] = {-1.5, -1.0, -0.5, -0.25, -0.05, 0.0, 0.05, 0.25, 0.5, 1.0, 1.5};
const int mult_EP_cut = 4;
// const double eta_gapEP = 0.05;
const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};

// LYZ
const int rbins = 2500;
const double rMax = 0.5;
const double rMin = 0.005;
const double rMaxSum = 0.5;
const double rMinSum = 0.005;
const int thetabins = 5;