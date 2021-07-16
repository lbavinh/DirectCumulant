#include <vector>

#include <RtypesCore.h>
#include <TString.h>


// Constant declaration
const Int_t npid = 12; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-, h, pions, kaons, protons and antiproton
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "antiproton","hadron", "pion", "kaon", "proton_antiproton"};
const Int_t ncent = 9;
const Double_t bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
const Int_t npt = 16; // 0-3.6 GeV/c - number of pT bins
const Double_t pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
const Int_t neta = 2; // two eta-sub events [eta-,eta+]
const Int_t netaBin = 14;
const Double_t etaBin[netaBin+1] = {-1.5,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.,1.2,1.5};
const Int_t mult_EP_cut = 4; // multiplicity cut for TPC event plane & SP