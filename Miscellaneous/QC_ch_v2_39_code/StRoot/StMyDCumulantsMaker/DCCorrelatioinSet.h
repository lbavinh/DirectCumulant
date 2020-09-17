#ifndef DCCORRELATIOINSET_H
#define DCCORRELATIOINSET_H

#include "Rtypes.h"
#include "TProfile.h"
#include "TProfile3D.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TObjArray.h"
#include "TString.h"
#include "TFile.h"
#include "TMath.h"

class DCCorrelatioinSet {
public:
    DCCorrelatioinSet(Int_t _nPOIs = 0,
                      Int_t _nPtBins = 0, Double_t _ptLow = 0, Double_t _ptUp = 0,
                      Int_t _nEtaBins = 0, Double_t _etaLow = 0, Double_t _etaUp = 0)
        :nPOIs(_nPOIs), nPtBins(_nPtBins), ptLow(_ptLow), ptUp(_ptUp),
         nEtaBins(_nEtaBins), etaLow(_etaLow), etaUp(_etaUp),
         pRefCorrelations(NULL), hRefBinSumW2(NULL),
         pC14(NULL), pC15(NULL), pT28(NULL),
         pC17a(NULL), pC17b(NULL), pC18a(NULL), pC18b(NULL),
         pC19a(NULL), pC19b(NULL), pT32(NULL),
         hDiffBinSumW12(NULL), hDiffBinSumW22(NULL),
         hDiffBinSumW32(NULL), hDiffBinSumW42(NULL),
         allCorrelations(NULL) {}
    ~DCCorrelatioinSet() {}

    void DeclareHistograms();

    void WriteHistograms() {
        allCorrelations->Write();
    }

    void Write() {
        WriteHistograms();
    }
    
    void ReadHistograms(TFile* inFile = NULL, TString _postfix = "");
    void CalculateDiffFlow(TFile* outFile = NULL);
    
    // -----------------------------------------------------------------------------
    static const Int_t nObjects;
    // static const Char_t* objNames[nObjects];

    enum CorrelationTypes {
        C2 = 0, C3, T16, C7, C8, C9, C10, T18,
        C14, C15, T28, C17a, C17b, C18a, C18b, C19a, C19b, T32,
        nRefCorr = 8, nDiffCorr = 10
    };

    enum CovTypes{
        T16T18 = 0, T16T28, T16T32, T18T28, T18T32, T28T32
    };
    
    Int_t       nPOIs;
    
    Int_t       nPtBins;
    Double_t    ptLow;
    Double_t    ptUp;

    Int_t       nEtaBins;
    Double_t    etaLow;
    Double_t    etaUp;

    TString     postfix;
    
    TProfile*   pRefCorrelations; // 8 bins for 8 ref. correlations
    TH1D*       hRefBinSumW2;

    // differential correlations
    TProfile3D* pC14;           // 3D: nPOI, pt, eta
    TProfile3D* pC15;
    TProfile3D* pT28;
    TProfile3D* pC17a;
    TProfile3D* pC17b;
    TProfile3D* pC18a;
    TProfile3D* pC18b;
    TProfile3D* pC19a;
    TProfile3D* pC19b;
    TProfile3D* pT32;

    TH3D*       hDiffBinSumW12; // sum M1^2
    TH3D*       hDiffBinSumW22;
    TH3D*       hDiffBinSumW32;
    TH3D*       hDiffBinSumW42;

    // covariance terms
    TProfile3D* pT16T18;        // Cov(<2>, <4>)
    TProfile3D* pT16T28;        // Cov(<2>, <2'>)
    TProfile3D* pT16T32;        // Cov(<2>, <4'>)
    TProfile3D* pT18T28;        // Cov(<4>, <2'>)
    TProfile3D* pT18T32;        // Cov(<4>, <4'>)
    TProfile3D* pT28T32;        // Cov(<2'>, <4'>)
    
    TH3D*       hYield;         // yield for each particle species

    TObjArray*  allCorrelations;

    ClassDef(DCCorrelatioinSet, 1)
    
};

#endif
