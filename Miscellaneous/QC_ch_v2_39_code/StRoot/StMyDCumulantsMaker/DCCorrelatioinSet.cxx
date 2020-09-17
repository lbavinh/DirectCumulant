#define COVARIANCE

#include "DCCorrelatioinSet.h"

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::fixed;
using std::scientific;

ClassImp(DCCorrelatioinSet)

// ----------------------------------------------------------------------
const Int_t DCCorrelatioinSet::nObjects = 23;

// const Char_t* DCCorrelatioinSet::objNames[DCCorrelatioinSet::nObjects] = {"refCorrelations", "refBinSumW2",
//                                                                           "C14", "C15", "T28", "C17a", "C17b",
//                                                                           "C18a", "C18b", "C19a", "C19b", "T32",
//                                                                           "diffBinSumW12", "diffBinSumW22",
//                                                                           "diffBinSumW32", "diffBinSumW42",
//                                                                           "yield"};

// ----------------------------------------------------------------------
void DCCorrelatioinSet::DeclareHistograms() {
    // for ROOT_Version < 5.24, use kERRORSPREAD for correlations which are filled with weights
    // need to calculate binSumW2 by myself for ROOT_Version < 5.24

    // 8 bins for 8 correlations for ref flow
    pRefCorrelations = new TProfile("refCorrelations", "", 8, 0, 8, "s");
    hRefBinSumW2     = new TH1D("refBinSumW2", "", 8, 0, 8); // binsumw2

    // diff correlations
    pC14             = new TProfile3D("C14",  "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC15             = new TProfile3D("C15",  "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pT28             = new TProfile3D("T28",  "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC17a            = new TProfile3D("C17a", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC17b            = new TProfile3D("C17b", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC18a            = new TProfile3D("C18a", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC18b            = new TProfile3D("C18b", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC19a            = new TProfile3D("C19a", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pC19b            = new TProfile3D("C19b", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");
    pT32             = new TProfile3D("T32",  "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp, "s");

    hDiffBinSumW12   = new TH3D("diffBinSumW12", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hDiffBinSumW22   = new TH3D("diffBinSumW22", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hDiffBinSumW32   = new TH3D("diffBinSumW32", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hDiffBinSumW42   = new TH3D("diffBinSumW42", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);

    pT16T18          = new TProfile3D("T16T18", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    pT16T28          = new TProfile3D("T16T28", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    pT16T32          = new TProfile3D("T16T32", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    pT18T28          = new TProfile3D("T18T28", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    pT18T32          = new TProfile3D("T18T32", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    pT28T32          = new TProfile3D("T28T32", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);

    hYield           = new TH3D("yield", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);

    allCorrelations        = new TObjArray(nObjects);
    (*allCorrelations)[0]  = pRefCorrelations;
    (*allCorrelations)[1]  = hRefBinSumW2;
    (*allCorrelations)[2]  = pC14;
    (*allCorrelations)[3]  = pC15;
    (*allCorrelations)[4]  = pT28;
    (*allCorrelations)[5]  = pC17a;
    (*allCorrelations)[6]  = pC17b;
    (*allCorrelations)[7]  = pC18a;
    (*allCorrelations)[8]  = pC18b;
    (*allCorrelations)[9]  = pC19a;
    (*allCorrelations)[10] = pC19b;
    (*allCorrelations)[11] = pT32;
    (*allCorrelations)[12] = hDiffBinSumW12;
    (*allCorrelations)[13] = hDiffBinSumW22;
    (*allCorrelations)[14] = hDiffBinSumW32;
    (*allCorrelations)[15] = hDiffBinSumW42;
    (*allCorrelations)[16] = pT16T18;
    (*allCorrelations)[17] = pT16T28;
    (*allCorrelations)[18] = pT16T32;
    (*allCorrelations)[19] = pT18T28;
    (*allCorrelations)[20] = pT18T32;
    (*allCorrelations)[21] = pT28T32;
    (*allCorrelations)[22] = hYield;

    return;
}

// -----------------------------------------------------------------------------
void DCCorrelatioinSet::ReadHistograms(TFile* inFile, TString _postfix) {
    if ( NULL == inFile ) {
        cerr << "DCCorrelatioinSet::ReadHistograms Error: Invalid input file" << endl;
        return;
    }

    postfix = _postfix;
    
    pRefCorrelations = (TProfile*)inFile->Get(TString("refCorrelations").Append(postfix).Data());
    hRefBinSumW2     = (TH1D*)inFile->Get(TString("refBinSumW2").Append(postfix).Data());
    pC14             = (TProfile3D*)inFile->Get(TString("C14").Append(postfix).Data());
    pC15             = (TProfile3D*)inFile->Get(TString("C15").Append(postfix).Data());
    pT28             = (TProfile3D*)inFile->Get(TString("T28").Append(postfix).Data());
    pC17a            = (TProfile3D*)inFile->Get(TString("C17a").Append(postfix).Data());
    pC17b            = (TProfile3D*)inFile->Get(TString("C17b").Append(postfix).Data());
    pC18a            = (TProfile3D*)inFile->Get(TString("C18a").Append(postfix).Data());
    pC18b            = (TProfile3D*)inFile->Get(TString("C18b").Append(postfix).Data());
    pC19a            = (TProfile3D*)inFile->Get(TString("C19a").Append(postfix).Data());
    pC19b            = (TProfile3D*)inFile->Get(TString("C19b").Append(postfix).Data());
    pT32             = (TProfile3D*)inFile->Get(TString("T32").Append(postfix).Data());
    hDiffBinSumW12   = (TH3D*)inFile->Get(TString("diffBinSumW12").Append(postfix).Data());
    hDiffBinSumW22   = (TH3D*)inFile->Get(TString("diffBinSumW22").Append(postfix).Data());
    hDiffBinSumW32   = (TH3D*)inFile->Get(TString("diffBinSumW32").Append(postfix).Data());
    hDiffBinSumW42   = (TH3D*)inFile->Get(TString("diffBinSumW42").Append(postfix).Data());
    pT16T18          = (TProfile3D*)inFile->Get(TString("T16T18").Append(postfix).Data());
    pT16T28          = (TProfile3D*)inFile->Get(TString("T16T28").Append(postfix).Data());
    pT16T32          = (TProfile3D*)inFile->Get(TString("T16T32").Append(postfix).Data());
    pT18T28          = (TProfile3D*)inFile->Get(TString("T18T28").Append(postfix).Data());
    pT18T32          = (TProfile3D*)inFile->Get(TString("T18T32").Append(postfix).Data());
    pT28T32          = (TProfile3D*)inFile->Get(TString("T28T32").Append(postfix).Data());
    hYield           = (TH3D*)inFile->Get(TString("yield").Append(postfix).Data());

    if ( NULL == pC14 ) {
        cerr << "Error: Can not find C14" << endl;
        return;
    }

    nPOIs    = pC14->GetNbinsX();
    nPtBins  = pC14->GetNbinsY();
    ptLow    = pC14->GetYaxis()->GetXmin();
    ptUp     = pC14->GetYaxis()->GetXmax();
    nEtaBins = pC14->GetNbinsZ();
    etaLow   = pC14->GetZaxis()->GetXmin();
    etaUp    = pC14->GetZaxis()->GetXmax();

    cout << nPOIs    << "\t"
         << nPtBins  << "\t"
         << ptLow    << "\t"
         << ptUp     << "\t"
         << nEtaBins << "\t"
         << etaLow   << "\t"
         << etaUp    << endl;

    return;
}

#ifndef COVARIANCE
// -- stat. error without covariance terms -------------------------------------
void DCCorrelatioinSet::CalculateDiffFlow(TFile* outFile) {
    Double_t refMean[nRefCorr]        = {0};
    Double_t refMeanError2[nRefCorr]  = {0};
    for ( Int_t i = 0; i < nRefCorr; ++i ) {
        refMean[i]              = pRefCorrelations->GetBinContent(i+1);
        refMeanError2[i]        = TMath::Power(pRefCorrelations->GetBinError(i+1), 2);
        Double_t effBinEntries  = TMath::Power(pRefCorrelations->GetBinEntries(i+1), 2) / hRefBinSumW2->GetBinContent(i+1); // \sum{w_i}^2 / \sum{w_i^2}
        refMeanError2[i]       /= effBinEntries;
    }

    Double_t c22     = refMean[T16] - refMean[C2]*refMean[C2] - refMean[C3]*refMean[C3];
    Double_t c22Err2 = 0;

    Double_t dC22dx2[3];
    dC22dx2[C2]  = 4*refMean[C2]*refMean[C2];
    dC22dx2[C3]  = 4*refMean[C3]*refMean[C3];
    dC22dx2[T16] = 1.0;
    for ( int i = 0; i < 3; ++i ) {
        c22Err2 += dC22dx2[i] * refMeanError2[i];
    }

    Double_t c24 = refMean[T18] - 2*refMean[T16]*refMean[T16]
        - 4*refMean[C2]*refMean[C9]
        + 4*refMean[C3]*refMean[C10]
        - refMean[C7]*refMean[C7] - refMean[C8]*refMean[C8]
        + 4*refMean[C7]*(refMean[C2]*refMean[C2] - refMean[C3]*refMean[C3])
        + 8*refMean[C8]*refMean[C3]*refMean[C2]
        + 8*refMean[T16]*(refMean[C2]*refMean[C2] + refMean[C3]*refMean[C3])
        - 6*pow(refMean[C2]*refMean[C2] + refMean[C3]*refMean[C3], 2);

    // c24 = -TMath::Abs(c24);

    Double_t dC24dx2[8];
    dC24dx2[C2]  = 16 * TMath::Power(6*pow(refMean[C2], 3) - 2*refMean[C3]*refMean[C8] + refMean[C9]
                                     - 2*refMean[C2]*(-3*refMean[C3]*refMean[C3] + refMean[C7] + 2*refMean[T16]), 2);
    dC24dx2[C3]  = 16 * TMath::Power(refMean[C10] - 6*refMean[C3]*(refMean[C2]*refMean[C2]+refMean[C3]*refMean[C3])
                                     - 2*refMean[C3]*refMean[C7] + 2*refMean[C2]*refMean[C8] + 4*refMean[C3]*refMean[T16], 2);
    dC24dx2[T16] = TMath::Power(8*(refMean[C2]*refMean[C2] + refMean[C3]*refMean[C3]) - 4*refMean[T16], 2);
    dC24dx2[C7]  = TMath::Power(4*refMean[C2]*refMean[C2] - 2*(2*refMean[C3]*refMean[C3]+refMean[C7]), 2);
    dC24dx2[C8]  = TMath::Power(8*refMean[C2]*refMean[C3] -2*refMean[C8], 2);
    dC24dx2[C9]  = 16 * refMean[C2] * refMean[C2];
    dC24dx2[C10] = 16 * refMean[C3] * refMean[C3];
    dC24dx2[T18] = 1;
        
    Double_t c24Err2 = 0;
    for ( int i = 0; i < nRefCorr; ++i ) {
        c24Err2 += dC24dx2[i] * refMeanError2[i];
    }

    // without acceptance corretion
    // c22 = refMean[T16];
    // c24 = refMean[T18] - 2*refMean[T16]*refMean[T16];
    
    // Double_t refV22    = sqrt(c22);
    // Double_t refV22Err = sqrt(c22Err2 / 4.0 / c22);
    // Double_t refV24    = sqrt(sqrt(-c24));
    // Double_t refV24Err = sqrt(c24Err2 / 16 / pow(-c24, 1.5));

    // cout << "ref flow: " << refV22 << "\t" << refV24 << endl;
    
    cout << std::scientific;
    cout << "c22 = " << c22 << ",\t -c24 = " << -c24 << endl;
    
    // diff flow
    double     d22[nPOIs][nPtBins][nEtaBins];
    double     d24[nPOIs][nPtBins][nEtaBins];
    double d22Err2[nPOIs][nPtBins][nEtaBins];
    double d24Err2[nPOIs][nPtBins][nEtaBins];
    double     v22[nPOIs][nPtBins][nEtaBins];
    double     v24[nPOIs][nPtBins][nEtaBins];
    double  v22Err[nPOIs][nPtBins][nEtaBins];
    double  v24Err[nPOIs][nPtBins][nEtaBins];

    TH3D* v22Hist = new TH3D(TString("v22Hist").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    v22Hist->GetXaxis()->SetTitle("# POI");
    v22Hist->GetYaxis()->SetTitle("p_{T} (GeV/c)");
    v22Hist->GetZaxis()->SetTitle("#eta");
    TH3D* v24Hist = new TH3D(TString("v24Hist").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    v24Hist->GetXaxis()->SetTitle("# POI");
    v24Hist->GetYaxis()->SetTitle("p_{T} (GeV/c)");
    v24Hist->GetZaxis()->SetTitle("#eta");
    
    double mean[nRefCorr+nDiffCorr]       = {0};
    double meanError2[nRefCorr+nDiffCorr] = {0};
    for ( int i = 0; i < nRefCorr; ++i ) {
        mean[i]       = refMean[i];
        meanError2[i] = refMeanError2[i];
    }

    for ( Int_t iPOI = 0; iPOI < nPOIs; ++iPOI ) {
        for ( Int_t iPt = 0; iPt < nPtBins; ++iPt ) {
            for ( Int_t iEta = 0; iEta < nEtaBins; ++iEta ) {
                Int_t globalBinNum = pC14->GetBin(iPOI+1, iPt+1, iEta+1);
                
                mean[C14]  = pC14->GetBinContent(globalBinNum);
                mean[C15]  = pC15->GetBinContent(globalBinNum);
                mean[T28]  = pT28->GetBinContent(globalBinNum);
                mean[C17a] = pC17a->GetBinContent(globalBinNum);
                mean[C17b] = pC17b->GetBinContent(globalBinNum);
                mean[C18a] = pC18a->GetBinContent(globalBinNum);
                mean[C18b] = pC18b->GetBinContent(globalBinNum);
                mean[C19a] = pC19a->GetBinContent(globalBinNum);
                mean[C19b] = pC19b->GetBinContent(globalBinNum);
                mean[T32]  = pT32->GetBinContent(globalBinNum); 

                meanError2[C14]  = TMath::Power(pC14->GetBinError(globalBinNum), 2);
                meanError2[C15]  = TMath::Power(pC15->GetBinError(globalBinNum), 2);
                meanError2[T28]  = TMath::Power(pT28->GetBinError(globalBinNum), 2);
                meanError2[C17a] = TMath::Power(pC17a->GetBinError(globalBinNum), 2);
                meanError2[C17b] = TMath::Power(pC17b->GetBinError(globalBinNum), 2);
                meanError2[C18a] = TMath::Power(pC18a->GetBinError(globalBinNum), 2);
                meanError2[C18b] = TMath::Power(pC18b->GetBinError(globalBinNum), 2);
                meanError2[C19a] = TMath::Power(pC19a->GetBinError(globalBinNum), 2);
                meanError2[C19b] = TMath::Power(pC19b->GetBinError(globalBinNum), 2);
                meanError2[T32]  = TMath::Power(pT32->GetBinError(globalBinNum), 2);

                meanError2[C14]  /= TMath::Power(pC14->GetBinEntries(globalBinNum),  2) / hDiffBinSumW12->GetBinContent(globalBinNum); 
                meanError2[C15]  /= TMath::Power(pC15->GetBinEntries(globalBinNum),  2) / hDiffBinSumW12->GetBinContent(globalBinNum); 
                meanError2[T28]  /= TMath::Power(pT28->GetBinEntries(globalBinNum),  2) / hDiffBinSumW22->GetBinContent(globalBinNum); 
                meanError2[C17a] /= TMath::Power(pC17a->GetBinEntries(globalBinNum), 2) / hDiffBinSumW22->GetBinContent(globalBinNum);
                meanError2[C17b] /= TMath::Power(pC17b->GetBinEntries(globalBinNum), 2) / hDiffBinSumW22->GetBinContent(globalBinNum);
                meanError2[C18a] /= TMath::Power(pC18a->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum);
                meanError2[C18b] /= TMath::Power(pC18b->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum);
                meanError2[C19a] /= TMath::Power(pC19a->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum);
                meanError2[C19b] /= TMath::Power(pC19b->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum);
                meanError2[T32]  /= TMath::Power(pT32->GetBinEntries(globalBinNum),  2) / hDiffBinSumW42->GetBinContent(globalBinNum); 

                meanError2[C14]  = TMath::IsNaN(meanError2[C14] ) ? 0 : meanError2[C14] ;
                meanError2[C15]  = TMath::IsNaN(meanError2[C15] ) ? 0 : meanError2[C15] ;
                meanError2[T28]  = TMath::IsNaN(meanError2[T28] ) ? 0 : meanError2[T28] ;
                meanError2[C17a] = TMath::IsNaN(meanError2[C17a]) ? 0 : meanError2[C17a];
                meanError2[C17b] = TMath::IsNaN(meanError2[C17b]) ? 0 : meanError2[C17b];
                meanError2[C18a] = TMath::IsNaN(meanError2[C18a]) ? 0 : meanError2[C18a];
                meanError2[C18b] = TMath::IsNaN(meanError2[C18b]) ? 0 : meanError2[C18b];
                meanError2[C19a] = TMath::IsNaN(meanError2[C19a]) ? 0 : meanError2[C19a];
                meanError2[C19b] = TMath::IsNaN(meanError2[C19b]) ? 0 : meanError2[C19b];
                meanError2[T32]  = TMath::IsNaN(meanError2[T32] ) ? 0 : meanError2[T32] ;
                
                d22[iPOI][iPt][iEta]     = mean[T28] - mean[C14]*mean[C2] - mean[C15]*mean[C3];
                d22Err2[iPOI][iPt][iEta] = mean[C14]*mean[C14]*meanError2[C2] +
                    mean[C15] * mean[C15] * meanError2[C3] +
                    mean[C2] * mean[C2] * meanError2[C14] +
                    mean[C3] * mean[C3] * meanError2[C15] +
                    meanError2[T28];

                d24[iPOI][iPt][iEta] = mean[T32] - 2*mean[T28]*mean[T16]
                    - mean[C14]*mean[C9]
                    + mean[C15]*mean[C10]
                    - mean[C2]*mean[C19a]
                    + mean[C3]*mean[C19b]
                    - 2*mean[C2]*mean[C18a]
                    - 2*mean[C3]*mean[C18b]
                    - mean[C17a]*mean[C7]
                    - mean[C17b]*mean[C8]
                    + 2*mean[C7]*(mean[C14]*mean[C2] - mean[C15]*mean[C3])
                    + 2*mean[C8]*(mean[C14]*mean[C3] + mean[C15]*mean[C2])
                    + 4*mean[T16]*(mean[C14]*mean[C2] + mean[C15]*mean[C3])
                    + 2*mean[C17a]*(mean[C2]*mean[C2] - mean[C3]*mean[C3])
                    + 4*mean[C17b]*mean[C2]*mean[C3]
                    + 4*mean[T28]*(mean[C2]*mean[C2] + mean[C3]*mean[C3])
                    - 6*(mean[C2]*mean[C2]-mean[C3]*mean[C3])*(mean[C14]*mean[C2]-mean[C15]*mean[C3])
                    - 12*mean[C2]*mean[C3]*(mean[C15]*mean[C2]+mean[C14]*mean[C3]);
            
                double dd24dx2[nRefCorr+nDiffCorr] = {0};
                dd24dx2[C2]  = pow( 2*mean[C18a] + mean[C19a]
                                    - 2*(2*mean[C17a]*mean[C2] + 2*mean[C17b]*mean[C3]
                                         - 6*mean[C15]*mean[C2]*mean[C3] + mean[C15]*mean[C8]
                                         + mean[C14]*(-9*mean[C2]*mean[C2] - 3*mean[C3]*mean[C3] + mean[C7] + 2*mean[T16])
                                         + 4*mean[C2]*mean[T28]), 2 );
                dd24dx2[C3]  = pow( -2*mean[C18b] + mean[C19b] + 4*mean[C17b]*mean[C2] - 6*mean[C15]*mean[C2]*mean[C2]
                                    - 4*mean[C17a]*mean[C3] - 12*mean[C14]*mean[C2]*mean[C3]
                                    - 18*mean[C15]*mean[C3]*mean[C3] - 2*mean[C15]*mean[C7]
                                    + 2*mean[C14]*mean[C8] + 4*mean[C15]*mean[T16] + 8*mean[C3]*mean[T28], 2 );
                dd24dx2[T16] = pow( 4*mean[C14]*mean[C2] + 4*mean[C15]*mean[C3] - 2*mean[T28], 2 );
                dd24dx2[C7]  = pow( mean[C17a] - 2*mean[C14]*mean[C2] + 2*mean[C15]*mean[C3], 2 );
                dd24dx2[C8]  = pow( mean[C17b] - 2*(mean[C15]*mean[C2] + mean[C14]*mean[C3]), 2 );
                dd24dx2[C9]  = pow( mean[C14], 2 );
                dd24dx2[C10] = pow( mean[C15], 2 );
                dd24dx2[T18] = 0;

                dd24dx2[C14]  = pow(6*mean[C2]*mean[C2] - 2*mean[C3]*mean[C8] + mean[C9] +
                                    mean[C2]*(6*mean[C3]*mean[C3] - 2*(mean[C7] + 2*mean[T16])), 2);
                dd24dx2[C15]  = pow(mean[C10] - 6*mean[C2]*mean[C2]*mean[C3] + 2*mean[C2]*mean[C8] -
                                    2*mean[C3]*(3*mean[C3]*mean[C3] + mean[C7] - 2*mean[T16]), 2);
                dd24dx2[T28]  = pow(4*(mean[C2]*mean[C2] + mean[C3]*mean[C3]) - 2*mean[T16], 2);
                dd24dx2[C17a] = pow(-2*mean[C2]*mean[C2] + 2*mean[C3]*mean[C3] + mean[C7], 2);
                dd24dx2[C17b] = pow(-4*mean[C2]*mean[C3] + mean[C8], 2);
                dd24dx2[C18a] = 4 * mean[C2]*mean[C2];
                dd24dx2[C18b] = 4 * mean[C3]*mean[C3];
                dd24dx2[C19a] = mean[C2]*mean[C2];
                dd24dx2[C19b] = mean[C3]*mean[C3];
                dd24dx2[T32]  = 1;

                d24Err2[iPOI][iPt][iEta] = 0;
                for ( int k = 0; k < nRefCorr+nDiffCorr; ++k ) {
                    d24Err2[iPOI][iPt][iEta] += dd24dx2[k] * meanError2[k];
                }

                // d22[iPOI][iPt][iEta] = mean[T28];
                // d24[iPOI][iPt][iEta] = mean[T32] - 2*mean[T28]*mean[T16];
            
                v22[iPOI][iPt][iEta]    = d22[iPOI][iPt][iEta] / sqrt(c22);
                v22Err[iPOI][iPt][iEta] = sqrt(d22Err2[iPOI][iPt][iEta]/c22 + c22Err2*d22[iPOI][iPt][iEta]*d22[iPOI][iPt][iEta]/4.0/pow(c22, 3));
                v24[iPOI][iPt][iEta]    = -1.0 * d24[iPOI][iPt][iEta] / pow(-c24, 3.0/4.0);
                v24Err[iPOI][iPt][iEta] = sqrt(d24Err2[iPOI][iPt][iEta]/pow(-c24, 1.5) +
                                               c24Err2*9*d24[iPOI][iPt][iEta]*d24[iPOI][iPt][iEta]/(16*pow(-c24,7.0/2)));

                v22Hist->SetBinContent(globalBinNum, v22[iPOI][iPt][iEta]);
                v22Hist->SetBinError(globalBinNum, v22Err[iPOI][iPt][iEta]);
                v24Hist->SetBinContent(globalBinNum, v24[iPOI][iPt][iEta]);
                v24Hist->SetBinError(globalBinNum, v24Err[iPOI][iPt][iEta]);

                // -- debug ----------------------------------------------------
                // cout << scientific;
                // if ( postfix.Contains("cent3") && iPOI == 0 && iEta == 10) {
                //     // cout << postfix << endl;
                //     for ( int k = 0; k < nRefCorr+nDiffCorr; ++k ) {
                //         // cout << setw(15) << meanError2[k]
                //         //      << setw(15) << dd24dx2[k]
                //         //      << setw(15) << meanError2[k] * dd24dx2[k] << endl;
                //     }
                //     // cout << endl;
                    
                //     cout << setw(15) << d24Err2[iPOI][iPt][iEta] / pow(-c24, 1.5)
                //          << setw(15) << d24Err2[iPOI][iPt][iEta]
                //          << setw(15) << pow(-c24, 1.5)
                //          << setw(15) << c24Err2*9*d24[iPOI][iPt][iEta]*d24[iPOI][iPt][iEta]/(16*pow(-c24,7.0/2)) << endl;
                // }

                // if ( postfix.Contains("cent7") && iPOI == 0 && iEta == 10) {
                //     // cout << postfix << endl;
                //     for ( int k = 0; k < nRefCorr+nDiffCorr; ++k ) {
                //         // cout << setw(15) << meanError2[k] << endl;
                //         // cout << setw(15) << dd24dx2[k] << endl;
                //         // cout << setw(15) << meanError2[k]
                //         //      << setw(15) << dd24dx2[k]
                //         //      << setw(15) << meanError2[k] * dd24dx2[k] << endl;
                //     }
                //     // cout << endl;
                    
                //     cout << setw(15) << d24Err2[iPOI][iPt][iEta] / pow(-c24, 1.5)
                //          << setw(15) << d24Err2[iPOI][iPt][iEta]
                //          << setw(15) << pow(-c24, 1.5)
                //          << setw(15) << c24Err2*9*d24[iPOI][iPt][iEta]*d24[iPOI][iPt][iEta]/(16*pow(-c24,7.0/2)) << endl;
                // }
                // -- debug ----------------------------------------------------
            }
        }  
    } // POI loop end

    if ( outFile ) {
        outFile->cd();
        v22Hist->Write();
        v24Hist->Write();
        hYield->Write();
    }

    return;
}

#else
// -- stat. error with covariance terms ----------------------------------------
void DCCorrelatioinSet::CalculateDiffFlow(TFile* outFile) {
    cout << "DCCorrelatioinSet::CalculateDiffFlow: with covariance terms" << endl;

    // diff flow
    double     d22[nPOIs][nPtBins][nEtaBins];
    double     d24[nPOIs][nPtBins][nEtaBins];
    double     v22[nPOIs][nPtBins][nEtaBins];
    double     v24[nPOIs][nPtBins][nEtaBins];
    double  v22Err[nPOIs][nPtBins][nEtaBins];
    double  v24Err[nPOIs][nPtBins][nEtaBins];

    TH3D* v22Hist = new TH3D(TString("v22Hist").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    v22Hist->GetXaxis()->SetTitle("# POI");
    v22Hist->GetYaxis()->SetTitle("p_{T} (GeV/c)");
    v22Hist->GetZaxis()->SetTitle("#eta");
    TH3D* v24Hist = new TH3D(TString("v24Hist").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    v24Hist->GetXaxis()->SetTitle("# POI");
    v24Hist->GetYaxis()->SetTitle("p_{T} (GeV/c)");
    v24Hist->GetZaxis()->SetTitle("#eta");
    
    double mean[nRefCorr+nDiffCorr]       = {0};
    double entries[nRefCorr+nDiffCorr]    = {0};
    double meanError2[nRefCorr+nDiffCorr] = {0};
    double cov[6]                         = {0}; // ignore acceptance correction terms
    double nneff[6]                       = {0};
    
    for ( Int_t i = 0; i < nRefCorr; ++i ) {
        mean[i]                 = pRefCorrelations->GetBinContent(i+1);
        entries[i]              = pRefCorrelations->GetBinEntries(i+1);
        meanError2[i]           = TMath::Power(pRefCorrelations->GetBinError(i+1), 2);
        Double_t effBinEntries  = TMath::Power(pRefCorrelations->GetBinEntries(i+1), 2) / hRefBinSumW2->GetBinContent(i+1); // \sum{w_i}^2 / \sum{w_i^2}
        meanError2[i]          /= effBinEntries - 1;
    }

    Double_t c22 = mean[T16] - mean[C2]*mean[C2] - mean[C3]*mean[C3];
    Double_t c24 = mean[T18] - 2*mean[T16]*mean[T16]
        - 4*mean[C2]*mean[C9]
        + 4*mean[C3]*mean[C10]
        - mean[C7]*mean[C7] - mean[C8]*mean[C8]
        + 4*mean[C7]*(mean[C2]*mean[C2] - mean[C3]*mean[C3])
        + 8*mean[C8]*mean[C3]*mean[C2]
        + 8*mean[T16]*(mean[C2]*mean[C2] + mean[C3]*mean[C3])
        - 6*pow(mean[C2]*mean[C2] + mean[C3]*mean[C3], 2);

    for ( Int_t iPOI = 0; iPOI < nPOIs; ++iPOI ) {
        for ( Int_t iPt = 0; iPt < nPtBins; ++iPt ) {
            for ( Int_t iEta = 0; iEta < nEtaBins; ++iEta ) {
                Int_t globalBinNum = pC14->GetBin(iPOI+1, iPt+1, iEta+1);
                
                mean[C14]  = pC14->GetBinContent(globalBinNum);
                mean[C15]  = pC15->GetBinContent(globalBinNum);
                mean[T28]  = pT28->GetBinContent(globalBinNum);
                mean[C17a] = pC17a->GetBinContent(globalBinNum);
                mean[C17b] = pC17b->GetBinContent(globalBinNum);
                mean[C18a] = pC18a->GetBinContent(globalBinNum);
                mean[C18b] = pC18b->GetBinContent(globalBinNum);
                mean[C19a] = pC19a->GetBinContent(globalBinNum);
                mean[C19b] = pC19b->GetBinContent(globalBinNum);
                mean[T32]  = pT32->GetBinContent(globalBinNum); 

                entries[C14]  = pC14 ->GetBinEntries(globalBinNum);
                entries[C15]  = pC15 ->GetBinEntries(globalBinNum);
                entries[T28]  = pT28 ->GetBinEntries(globalBinNum);
                entries[C17a] = pC17a->GetBinEntries(globalBinNum);
                entries[C17b] = pC17b->GetBinEntries(globalBinNum);
                entries[C18a] = pC18a->GetBinEntries(globalBinNum);
                entries[C18b] = pC18b->GetBinEntries(globalBinNum);
                entries[C19a] = pC19a->GetBinEntries(globalBinNum);
                entries[C19b] = pC19b->GetBinEntries(globalBinNum);
                entries[T32]  = pT32 ->GetBinEntries(globalBinNum); 

                meanError2[C14]  = TMath::Power(pC14->GetBinError(globalBinNum), 2);
                meanError2[C15]  = TMath::Power(pC15->GetBinError(globalBinNum), 2);
                meanError2[T28]  = TMath::Power(pT28->GetBinError(globalBinNum), 2);
                meanError2[C17a] = TMath::Power(pC17a->GetBinError(globalBinNum), 2);
                meanError2[C17b] = TMath::Power(pC17b->GetBinError(globalBinNum), 2);
                meanError2[C18a] = TMath::Power(pC18a->GetBinError(globalBinNum), 2);
                meanError2[C18b] = TMath::Power(pC18b->GetBinError(globalBinNum), 2);
                meanError2[C19a] = TMath::Power(pC19a->GetBinError(globalBinNum), 2);
                meanError2[C19b] = TMath::Power(pC19b->GetBinError(globalBinNum), 2);
                meanError2[T32]  = TMath::Power(pT32->GetBinError(globalBinNum), 2);

                meanError2[C14]  /= TMath::Power(pC14->GetBinEntries(globalBinNum),  2) / hDiffBinSumW12->GetBinContent(globalBinNum) - 1; 
                meanError2[C15]  /= TMath::Power(pC15->GetBinEntries(globalBinNum),  2) / hDiffBinSumW12->GetBinContent(globalBinNum) - 1; 
                meanError2[T28]  /= TMath::Power(pT28->GetBinEntries(globalBinNum),  2) / hDiffBinSumW22->GetBinContent(globalBinNum) - 1; 
                meanError2[C17a] /= TMath::Power(pC17a->GetBinEntries(globalBinNum), 2) / hDiffBinSumW22->GetBinContent(globalBinNum) - 1;
                meanError2[C17b] /= TMath::Power(pC17b->GetBinEntries(globalBinNum), 2) / hDiffBinSumW22->GetBinContent(globalBinNum) - 1;
                meanError2[C18a] /= TMath::Power(pC18a->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum) - 1;
                meanError2[C18b] /= TMath::Power(pC18b->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum) - 1;
                meanError2[C19a] /= TMath::Power(pC19a->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum) - 1;
                meanError2[C19b] /= TMath::Power(pC19b->GetBinEntries(globalBinNum), 2) / hDiffBinSumW32->GetBinContent(globalBinNum) - 1;
                meanError2[T32]  /= TMath::Power(pT32->GetBinEntries(globalBinNum),  2) / hDiffBinSumW42->GetBinContent(globalBinNum) - 1; 

                meanError2[C14]  = TMath::IsNaN(meanError2[C14] ) ? 0 : meanError2[C14] ;
                meanError2[C15]  = TMath::IsNaN(meanError2[C15] ) ? 0 : meanError2[C15] ;
                meanError2[T28]  = TMath::IsNaN(meanError2[T28] ) ? 0 : meanError2[T28] ;
                meanError2[C17a] = TMath::IsNaN(meanError2[C17a]) ? 0 : meanError2[C17a];
                meanError2[C17b] = TMath::IsNaN(meanError2[C17b]) ? 0 : meanError2[C17b];
                meanError2[C18a] = TMath::IsNaN(meanError2[C18a]) ? 0 : meanError2[C18a];
                meanError2[C18b] = TMath::IsNaN(meanError2[C18b]) ? 0 : meanError2[C18b];
                meanError2[C19a] = TMath::IsNaN(meanError2[C19a]) ? 0 : meanError2[C19a];
                meanError2[C19b] = TMath::IsNaN(meanError2[C19b]) ? 0 : meanError2[C19b];
                meanError2[T32]  = TMath::IsNaN(meanError2[T32] ) ? 0 : meanError2[T32] ;
                
                // -- central values ^ -------------------------------------------
                d22[iPOI][iPt][iEta] = mean[T28] - mean[C14]*mean[C2] - mean[C15]*mean[C3];
                d24[iPOI][iPt][iEta] = mean[T32] - 2*mean[T28]*mean[T16]
                    - mean[C14]*mean[C9]
                    + mean[C15]*mean[C10]
                    - mean[C2]*mean[C19a]
                    + mean[C3]*mean[C19b]
                    - 2*mean[C2]*mean[C18a]
                    - 2*mean[C3]*mean[C18b]
                    - mean[C17a]*mean[C7]
                    - mean[C17b]*mean[C8]
                    + 2*mean[C7]*(mean[C14]*mean[C2] - mean[C15]*mean[C3])
                    + 2*mean[C8]*(mean[C14]*mean[C3] + mean[C15]*mean[C2])
                    + 4*mean[T16]*(mean[C14]*mean[C2] + mean[C15]*mean[C3])
                    + 2*mean[C17a]*(mean[C2]*mean[C2] - mean[C3]*mean[C3])
                    + 4*mean[C17b]*mean[C2]*mean[C3]
                    + 4*mean[T28]*(mean[C2]*mean[C2] + mean[C3]*mean[C3])
                    - 6*(mean[C2]*mean[C2]-mean[C3]*mean[C3])*(mean[C14]*mean[C2]-mean[C15]*mean[C3])
                    - 12*mean[C2]*mean[C3]*(mean[C15]*mean[C2]+mean[C14]*mean[C3]);
            
                v22[iPOI][iPt][iEta] = d22[iPOI][iPt][iEta] / sqrt(c22);
                v24[iPOI][iPt][iEta] = -1.0 * d24[iPOI][iPt][iEta] / pow(-c24, 3.0/4.0);

                v22[iPOI][iPt][iEta] = TMath::IsNaN(v22[iPOI][iPt][iEta]) ? 0 : v22[iPOI][iPt][iEta];
                v24[iPOI][iPt][iEta] = TMath::IsNaN(v24[iPOI][iPt][iEta]) ? 0 : v24[iPOI][iPt][iEta];

                v22Hist->SetBinContent(globalBinNum, v22[iPOI][iPt][iEta]);
                v24Hist->SetBinContent(globalBinNum, v24[iPOI][iPt][iEta]);
                // -- central values v -------------------------------------------


                // -- statistical errors ^ -------------------------------------------
                // -- ^ --
                // Double_t dV22dx2[6] = {0};
                // Double_t v22Error2  = 0;
                // dV22dx2[0] = - TMath::Power(mean[C14]*(mean[C3]*mean[C3] - mean[T16]) -
                //                             mean[C2]*(mean[T28] - mean[C15]*mean[C3]), 2) /
                //     TMath::Power(mean[C2]*mean[C2] + mean[C3]*mean[C3] - mean[T16], 3);
                
                // dV22dx2[1] = - TMath::Power(mean[C15]*(mean[C2]*mean[C2]-mean[T16]) +
                //                             mean[C3]*(mean[T28] - mean[C14]*mean[C2]), 2) /
                //     TMath::Power(mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16], 3);
                // dV22dx2[2] = - TMath::Power(mean[C14]*mean[C2] + mean[C15]*mean[C3] - mean[T28], 2) / 4.0 /
                //     TMath::Power(mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16], 3);
                // dV22dx2[3] = - mean[C2]*mean[C2] / (mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16]);
                // dV22dx2[4] = - mean[C3]*mean[C3] / (mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16]);
                // dV22dx2[5] = - 1.0 / (mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16]);
                
                // v22Error2 = dV22dx2[0] * meanError2[C2]
                //     + dV22dx2[1] * meanError2[C3]
                //     + dV22dx2[2] * meanError2[T16]
                //     + dV22dx2[3] * meanError2[C14]
                //     + dV22dx2[4] * meanError2[C15]
                //     + dV22dx2[5] * meanError2[T28];

                // Double_t meanT16T28    = pT16T28->GetBinContent(globalBinNum);
                // Double_t entriesT16T28 = pT16T28->GetBinEntries(globalBinNum);
                // Double_t neffT16T28    = entriesT16T28 / entries[T16] / entries[T18];
                // Double_t covT16T28     = (meanT16T28 - mean[T16]*mean[T18]) / (1.0 - neffT16T28);

                // v22Error2 -= mean[T28]*neffT16T28*covT16T28 / (mean[T16]*mean[T16]);
                // v22Err[iPOI][iPt][iEta] = TMath::Sqrt(v22Error2);
                // -- v --

                nneff[T16T18] = pT16T18->GetBinEntries(globalBinNum) / (entries[T16] * entries[T18]);
                nneff[T16T28] = pT16T28->GetBinEntries(globalBinNum) / (entries[T16] * entries[T28]);
                nneff[T16T32] = pT16T32->GetBinEntries(globalBinNum) / (entries[T16] * entries[T32]);
                nneff[T18T28] = pT18T28->GetBinEntries(globalBinNum) / (entries[T18] * entries[T28]);
                nneff[T18T32] = pT18T32->GetBinEntries(globalBinNum) / (entries[T18] * entries[T32]);
                nneff[T28T32] = pT28T32->GetBinEntries(globalBinNum) / (entries[T28] * entries[T32]);

                cov[T16T18] = (pT16T18->GetBinContent(globalBinNum) - mean[T16]*mean[T18]) / (1 - nneff[T16T18]);
                cov[T16T28] = (pT16T28->GetBinContent(globalBinNum) - mean[T16]*mean[T28]) / (1 - nneff[T16T28]);
                cov[T16T32] = (pT16T32->GetBinContent(globalBinNum) - mean[T16]*mean[T32]) / (1 - nneff[T16T32]);
                cov[T18T28] = (pT18T28->GetBinContent(globalBinNum) - mean[T18]*mean[T28]) / (1 - nneff[T18T28]);
                cov[T18T32] = (pT18T32->GetBinContent(globalBinNum) - mean[T18]*mean[T32]) / (1 - nneff[T18T32]);
                cov[T28T32] = (pT28T32->GetBinContent(globalBinNum) - mean[T28]*mean[T32]) / (1 - nneff[T28T32]);

                cov[T16T18] *= nneff[T16T18];
                cov[T16T28] *= nneff[T16T28];
                cov[T16T32] *= nneff[T16T32];
                cov[T18T28] *= nneff[T18T28];
                cov[T18T32] *= nneff[T18T32];
                cov[T28T32] *= nneff[T28T32];

                // v22Err
                Double_t dV22dx2[6] = {0};
                dV22dx2[0] = - TMath::Power(mean[C14]*(mean[C3]*mean[C3] - mean[T16]) -
                                            mean[C2]*(mean[T28] - mean[C15]*mean[C3]), 2) /
                    TMath::Power(mean[C2]*mean[C2] + mean[C3]*mean[C3] - mean[T16], 3);
                
                dV22dx2[1] = - TMath::Power(mean[C15]*(mean[C2]*mean[C2]-mean[T16]) +
                                            mean[C3]*(mean[T28] - mean[C14]*mean[C2]), 2) /
                    TMath::Power(mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16], 3);
                dV22dx2[2] = - TMath::Power(mean[C14]*mean[C2] + mean[C15]*mean[C3] - mean[T28], 2) / 4.0 /
                    TMath::Power(mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16], 3);
                dV22dx2[3] = - mean[C2]*mean[C2] / (mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16]);
                dV22dx2[4] = - mean[C3]*mean[C3] / (mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16]);
                dV22dx2[5] = - 1.0 / (mean[C2]*mean[C2]+mean[C3]*mean[C3]-mean[T16]);
                
                Double_t v22Err2  = 0;
                v22Err2 = dV22dx2[0] * meanError2[C2]
                    + dV22dx2[1] * meanError2[C3]
                    + dV22dx2[2] * meanError2[T16]
                    + dV22dx2[3] * meanError2[C14]
                    + dV22dx2[4] * meanError2[C15]
                    + dV22dx2[5] * meanError2[T28];

                v22Err2 += cov[T16T28] * (mean[C14]*mean[C2] + mean[C15]*mean[C3] - mean[T28]) /
                    pow(mean[C2]*mean[C2] + mean[C3]*mean[C3] - mean[T16], 2.0);

                // -- ignore all correction terms ------------------------------
                // Double_t v22Error2 =  (mean[T28]*mean[T28]*meanError2[T16]
                //                        + 4.0*mean[T16]*mean[T16]*meanError2[T28]
                //                        - 4.0*mean[T16]*mean[T28]*cov[T16T28]) / (4.0*pow(mean[T16], 3.0));

                v22Err[iPOI][iPt][iEta] = sqrt(v22Err2);
                

                // v24
                Double_t v24Err2 = 0;

                // v24Err2 += meanError2[T16] * pow(2*mean[T16]*mean[T16]*mean[T28] + 2*mean[T18]*mean[T28] - 3*mean[T16]*mean[T32], 2.0);
                // v24Err2 += meanError2[T18] * 9.0 * pow(mean[T32] - 2*mean[T16]*mean[28], 2.0) / 16.0;
                // v24Err2 += meanError2[T28] * 4.0 * mean[T16]*mean[T16] * pow(2*mean[T16]*mean[T16] - mean[T18], 2.0);
                // v24Err2 += meanError2[T32] * pow(2*mean[T16]*mean[T16] - mean[T18], 2.0);

                v24Err2 += cov[T16T18] * -3.0 * (2*mean[T16]*mean[T28] - mean[T32])
                    * (2.0*mean[T16]*mean[T16]*mean[T28] + 2.0*mean[T18]*mean[T28] - 3.0*mean[T18]*mean[T32]) / 2.0;

                v24Err2 += cov[T16T28] * -4.0 * mean[T16] * (2.0*mean[T16]*mean[T16] - mean[T18])
                    * (2.0*mean[T16]*mean[T16]*mean[T28] + 2.0*mean[T18]*mean[T28] - 3.0*mean[T18]*mean[T32]);

                v24Err2 += cov[T16T32] * 2.0 * (2.0*mean[T16]*mean[T16] - mean[T18])
                    * (2.0*mean[T16]*mean[T16]*mean[T28] + 2.0*mean[T18]*mean[T28] - 3.0*mean[T18]*mean[T32]);

                v24Err2 += cov[T18T28] * 3.0 * mean[T16] * (2.0*mean[T16]*mean[T16] - mean[T18])
                    * (2.0*mean[T16]*mean[T28] - mean[T32]);

                v24Err2 += cov[T18T32] * (2.0*mean[T16]*mean[T16] - mean[T18])
                    * (3.0*mean[T32] - 6.0*mean[T16]*mean[T28]) / 2.0;

                v24Err2 += cov[T28T32] * -4.0 * mean[T16] * (2.0*mean[T16]*mean[T16] - mean[T18]);

                v24Err2 *= pow(2.0*mean[T16]*mean[T16] - mean[T18], 7.0/2.0);


                double dv24dx2[nRefCorr+nDiffCorr] = {0};
                dv24dx2[C2]  = pow((2*mean[C18a] + mean[C19a] - 2*(2*mean[C17a]*mean[C2] + 2*mean[C17b]*mean[C3] - 6*mean[C15]*mean[C2]*mean[C3] + mean[C15]*mean[C8] + mean[C14]*(-9*pow(mean[C2],2) - 3*pow(mean[C3],2) + mean[C7] + 2*mean[T16]) + 4*mean[C2]*mean[T28]))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],0.75) - (3*(6*pow(mean[C2],3) - 2*mean[C3]*mean[C8] + mean[C9] + mean[C2]*(6*pow(mean[C3],2) - 2*(mean[C7] + 2*mean[T16])))*(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.75),2);
                dv24dx2[C3]  = pow((2*mean[C18b] - mean[C19b] + 2*(-2*mean[C17b]*mean[C2] + 3*mean[C15]*pow(mean[C2],2) + 2*mean[C17a]*mean[C3] + 6*mean[C14]*mean[C2]*mean[C3] + 9*mean[C15]*pow(mean[C3],2) + mean[C15]*mean[C7] - mean[C14]*mean[C8] - 2*mean[C15]*mean[T16] - 4*mean[C3]*mean[T28]))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],0.75) + (3*(mean[C10] - 6*pow(mean[C2],2)*mean[C3] + 2*mean[C2]*mean[C8] - 2*mean[C3]*(3*pow(mean[C3],2) + mean[C7] - 2*mean[T16]))*(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.75),2);
                dv24dx2[T16] = pow((-4*mean[C14]*mean[C2] - 4*mean[C15]*mean[C3] + 2*mean[T28])/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],0.75) - (3*(-8*(pow(mean[C2],2) + pow(mean[C3],2)) + 4*mean[T16])*(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]))/(4.*pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.75)),2);
                dv24dx2[C7]  = pow((mean[C17a] - 2*mean[C14]*mean[C2] + 2*mean[C15]*mean[C3])/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],0.75) - (3*(-4*pow(mean[C2],2) + 4*pow(mean[C3],2) + 2*mean[C7])*(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]))/(4.*pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.75)),2);
                dv24dx2[C8]  = pow((mean[C17b] - 2*(mean[C15]*mean[C2] + mean[C14]*mean[C3]))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],0.75) - (3*(-8*mean[C2]*mean[C3] + 2*mean[C8])*(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]))/(4.*pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.75)),2);
                dv24dx2[C9]  = pow(mean[C14]/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],0.75) - (3*mean[C2]*(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.75),2);
                dv24dx2[C10] = pow(mean[C15]*(-6*pow(mean[C2],4) + mean[C10]*mean[C3] + 12*pow(mean[C3],4) + 2*pow(mean[C3],2)*mean[C7] - pow(mean[C7],2) - pow(mean[C8],2) + 2*mean[C2]*(mean[C3]*mean[C8] - 2*mean[C9]) - 4*pow(mean[C3],2)*mean[T16] - 2*pow(mean[T16],2) + pow(mean[C2],2)*(6*pow(mean[C3],2) + 4*mean[C7] + 8*mean[T16]) + mean[T18]) + 3*mean[C3]*(2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32]),2)/pow(6*pow(mean[C2],4) - 4*mean[C10]*mean[C3] + 6*pow(mean[C3],4) + 4*pow(mean[C3],2)*mean[C7] + pow(mean[C7],2) + pow(mean[C8],2) + mean[C2]*(-8*mean[C3]*mean[C8] + 4*mean[C9]) + 4*pow(mean[C2],2)*(3*pow(mean[C3],2) - mean[C7] - 2*mean[T16]) - 8*pow(mean[C3],2)*mean[T16] + 2*pow(mean[T16],2) - mean[T18],3.5);
                dv24dx2[T18] = (9*pow(-(mean[C10]*mean[C15]) + 2*mean[C18a]*mean[C2] + mean[C19a]*mean[C2] - 2*mean[C17a]*pow(mean[C2],2) + 6*mean[C14]*pow(mean[C2],3) + 2*mean[C18b]*mean[C3] - mean[C19b]*mean[C3] - 4*mean[C17b]*mean[C2]*mean[C3] + 6*mean[C15]*pow(mean[C2],2)*mean[C3] + 2*mean[C17a]*pow(mean[C3],2) + 6*mean[C14]*mean[C2]*pow(mean[C3],2) + 6*mean[C15]*pow(mean[C3],3) + mean[C17a]*mean[C7] - 2*mean[C14]*mean[C2]*mean[C7] + 2*mean[C15]*mean[C3]*mean[C7] + mean[C17b]*mean[C8] - 2*mean[C15]*mean[C2]*mean[C8] - 2*mean[C14]*mean[C3]*mean[C8] + mean[C14]*mean[C9] - 4*mean[C14]*mean[C2]*mean[T16] - 4*mean[C15]*mean[C3]*mean[T16] - 4*pow(mean[C2],2)*mean[T28] - 4*pow(mean[C3],2)*mean[T28] + 2*mean[T16]*mean[T28] - mean[T32],2))/(16.*pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],3.5));

                dv24dx2[C14]  = pow(6*pow(mean[C2],3) + 6*mean[C2]*pow(mean[C3],2) - 2*mean[C2]*mean[C7] - 2*mean[C3]*mean[C8] + mean[C9] - 4*mean[C2]*mean[T16],2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C15]  = pow(mean[C10] - 6*pow(mean[C2],2)*mean[C3] + 2*mean[C2]*mean[C8] - 2*mean[C3]*(3*pow(mean[C3],2) + mean[C7] - 2*mean[T16]),2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[T28]  = pow(4*pow(mean[C2],2) + 4*pow(mean[C3],2) - 2*mean[T16],2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C17a] = pow(-2*pow(mean[C2],2) + 2*pow(mean[C3],2) + mean[C7],2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C17b] = pow(-4*mean[C2]*mean[C3] + mean[C8],2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C18a] = (4*pow(mean[C2],2))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C18b] = (4*pow(mean[C3],2))/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C19a] = pow(mean[C2],2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[C19b] = pow(mean[C3],2)/pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],1.5);
                dv24dx2[T32]  = pow(-4*mean[C10]*mean[C3] + 6*pow(pow(mean[C2],2) + pow(mean[C3],2),2) - 4*(pow(mean[C2],2) - pow(mean[C3],2))*mean[C7] + pow(mean[C7],2) - 8*mean[C2]*mean[C3]*mean[C8] + pow(mean[C8],2) + 4*mean[C2]*mean[C9] - 8*(pow(mean[C2],2) + pow(mean[C3],2))*mean[T16] + 2*pow(mean[T16],2) - mean[T18],-1.5);

                for ( int k = 0; k < nRefCorr+nDiffCorr; ++k ) {
                    v24Err2 += dv24dx2[k] * meanError2[k];
                }

                v24Err[iPOI][iPt][iEta] = sqrt(v24Err2);
                // -- statistical errors v -------------------------------------------

                v22Err[iPOI][iPt][iEta] = TMath::IsNaN(v22Err[iPOI][iPt][iEta]) ? 0 : v22Err[iPOI][iPt][iEta];
                v24Err[iPOI][iPt][iEta] = TMath::IsNaN(v24Err[iPOI][iPt][iEta]) ? 0 : v24Err[iPOI][iPt][iEta];

                v22Err[iPOI][iPt][iEta] = TMath::Finite(v22Err[iPOI][iPt][iEta]) ? v22Err[iPOI][iPt][iEta] : 0.0;
                v24Err[iPOI][iPt][iEta] = TMath::Finite(v24Err[iPOI][iPt][iEta]) ? v24Err[iPOI][iPt][iEta] : 0.0;

                v22Hist->SetBinError(globalBinNum, v22Err[iPOI][iPt][iEta]);
                v24Hist->SetBinError(globalBinNum, v24Err[iPOI][iPt][iEta]);

            }
        }  
    } // POI loop end

    if ( outFile ) {
        outFile->cd();
        v22Hist->Write();
        v24Hist->Write();
        hYield->Write();
    }

    return;
}

#endif  // def COVARIANCE
