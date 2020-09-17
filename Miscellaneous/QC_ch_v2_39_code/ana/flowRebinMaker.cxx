#include "flowRebinMaker.h"

#include <iostream>
#include <cmath>
using namespace std;

ClassImp(flowRebinMaker);

// -------------------------------------------------------------------------------------
flowRebinMaker::flowRebinMaker() {
    v22POIPtEta = NULL;
    v24POIPtEta = NULL;
    yldPOIPtEta = NULL;

    v22POIPt = NULL;
    v24POIPt = NULL;
    yldPOIPt = NULL;

    v22POIPtRebin = NULL;
    v24POIPtRebin = NULL;
    yldPOIPtRebin = NULL;

    v22POIEta = NULL;
    v24POIEta = NULL;
    yldPOIEta = NULL;

    v22POI = NULL;
    v24POI = NULL;
    yldPOI = NULL;
}

// -------------------------------------------------------------------------------------
flowRebinMaker::~flowRebinMaker() {}

// -------------------------------------------------------------------------------------
Int_t flowRebinMaker::readHists(TFile* inFile, const Char_t* pfix) {
    if (NULL == inFile) {
        cerr << "Error: flowRebinMaker::readHists: invalid input file" << endl;
        return 1;
    }

    postfix.Append(pfix);
    cout << postfix << endl;
    
    v22POIPtEta = (TH3D*)inFile->Get( TString("v22Hist").Append(postfix).Data() );
    v24POIPtEta = (TH3D*)inFile->Get( TString("v24Hist").Append(postfix).Data() );
    yldPOIPtEta = (TH3D*)inFile->Get( TString("yield").Append(postfix).Data() );

    if (NULL == v22POIPtEta || NULL == v24POIPtEta || NULL == yldPOIPtEta) {
        cerr << "Error: flowRebinMaker::readHists: Incompleted input file" << endl;
        return 2;
    }

    nPOIs    = v24POIPtEta->GetNbinsX();
    nPtBins  = v24POIPtEta->GetNbinsY();
    ptLow    = v24POIPtEta->GetYaxis()->GetXmin();
    ptUp     = v24POIPtEta->GetYaxis()->GetXmax();
    nEtaBins = v24POIPtEta->GetNbinsZ();
    etaLow   = v24POIPtEta->GetZaxis()->GetXmin();
    etaUp    = v24POIPtEta->GetZaxis()->GetXmax();

    cout << nPOIs    << endl;
    cout << nPtBins  << endl;
    cout << ptLow    << endl;
    cout << ptUp     << endl;
    cout << nEtaBins << endl;
    cout << etaLow   << endl;
    cout << etaUp    << endl;

    cout << "Read Histograms done!" << endl;
    
    return 0;
}

// -------------------------------------------------------------------------------------
Int_t flowRebinMaker::writeHists(TFile* outFile) {
    if (NULL == outFile) {
        cerr << "Error: flowRebinMaker::writeHists: invalid output file" << endl;
        return 1;
    }

    outFile->cd();

    v22POIPtEta->Write();
    v24POIPtEta->Write();
    yldPOIPtEta->Write();

    v22POIPt->Write();
    v24POIPt->Write();
    yldPOIPt->Write();

    v22POIEta->Write();
    v24POIEta->Write();
    yldPOIEta->Write();

    v22POI->Write();
    v24POI->Write();
    yldPOI->Write();

    outFile->Write();

    return 0;
}

// -------------------------------------------------------------------------------------
void flowRebinMaker::integratePt(Double_t inPtLow, Double_t inPtUp) {
    v22POIEta = new TH2D(TString("v22POIEta").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nEtaBins, etaLow, etaUp);
    v24POIEta = new TH2D(TString("v24POIEta").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nEtaBins, etaLow, etaUp);
    yldPOIEta = new TH2D(TString("yldPOIEta").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nEtaBins, etaLow, etaUp);

    Int_t inPtLowBin = v22POIPtEta->GetYaxis()->FindBin(inPtLow + 1.0e-6);
    Int_t inPtUpBin  = v22POIPtEta->GetYaxis()->FindBin(inPtUp  + 1.0e-6);

    // v22
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        for (Int_t iEta = 1; iEta <= nEtaBins; ++iEta) {
            Double_t vSum      = 0.;
            Double_t yieldSum  = 0.;
            Double_t error2sum = 0.;
            Double_t vSqrSum   = 0.;

            for (Int_t iPt = inPtLowBin; iPt < inPtUpBin; ++iPt) { // [inPtLowBin, inPtUpBin)
                Double_t v     = v22POIPtEta->GetBinContent(iPOI, iPt, iEta);
                Double_t verr  = v22POIPtEta->GetBinError(iPOI, iPt, iEta);
                Double_t yield = yldPOIPtEta->GetBinContent(iPOI, iPt, iEta);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }
            } // pt loop

            if (yieldSum) {
                v22POIEta->SetBinContent(iPOI, iEta, vSum / yieldSum);
                v22POIEta->SetBinError(iPOI, iEta, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
                yldPOIEta->SetBinContent(iPOI, iEta, yieldSum);
            }
        } // eta loop
    } // POI loop

    // v24
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        for (Int_t iEta = 1; iEta <= nEtaBins; ++iEta) {
            Double_t vSum      = 0.;
            Double_t yieldSum  = 0.;
            Double_t error2sum = 0.;
            Double_t vSqrSum   = 0.;

            for (Int_t iPt = inPtLowBin; iPt < inPtUpBin; ++iPt) { // [inPtLowBin, inPtUpBin)
                Double_t v     = v24POIPtEta->GetBinContent(iPOI, iPt, iEta);
                Double_t verr  = v24POIPtEta->GetBinError(iPOI, iPt, iEta);
                Double_t yield = yldPOIPtEta->GetBinContent(iPOI, iPt, iEta);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }
            } // pt loop

            if (yieldSum) {
                v24POIEta->SetBinContent(iPOI, iEta, vSum / yieldSum);
                v24POIEta->SetBinError(iPOI, iEta, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
            }
        } // eta loop
    } // POI loop

    return;
}

// -------------------------------------------------------------------------------------
void flowRebinMaker::integrateEta(Double_t inEtaLow, Double_t inEtaUp) {
    v22POIPt = new TH2D(TString("v22POIPt").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp);
    v24POIPt = new TH2D(TString("v24POIPt").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp);
    yldPOIPt = new TH2D(TString("yldPOIPt").Append(postfix).Data(), "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp);

    Int_t inEtaLowBin = v22POIPtEta->GetZaxis()->FindBin(inEtaLow + 1.0e-6);
    Int_t inEtaUpBin  = v22POIPtEta->GetZaxis()->FindBin(inEtaUp  + 1.0e-6);

    // v22
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        for (Int_t iPt = 1; iPt <= nPtBins; ++iPt) {
            Double_t vSum      = 0.;
            Double_t yieldSum  = 0.;
            Double_t error2sum = 0.;
            Double_t vSqrSum   = 0.;

            for (Int_t iEta = inEtaLowBin; iEta < inEtaUpBin; ++iEta) { // [inEtaLowBin, inEtaUpBin)
                Double_t v     = v22POIPtEta->GetBinContent(iPOI, iPt, iEta);
                Double_t verr  = v22POIPtEta->GetBinError(iPOI, iPt, iEta);
                Double_t yield = yldPOIPtEta->GetBinContent(iPOI, iPt, iEta);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }
            } // pt loop

            if (yieldSum) {
                v22POIPt->SetBinContent(iPOI, iPt, vSum / yieldSum);
                v22POIPt->SetBinError(iPOI, iPt, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));

                yldPOIPt->SetBinContent(iPOI, iPt, yieldSum);
            }
        } // eta loop
    } // POI loop

    // v24
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        for (Int_t iPt = 1; iPt <= nPtBins; ++iPt) {
            Double_t vSum      = 0.;
            Double_t yieldSum  = 0.;
            Double_t error2sum = 0.;
            Double_t vSqrSum   = 0.;

            for (Int_t iEta = inEtaLowBin; iEta < inEtaUpBin; ++iEta) { // [inEtaLowBin, inEtaUpBin)
                Double_t v     = v24POIPtEta->GetBinContent(iPOI, iPt, iEta);
                Double_t verr  = v24POIPtEta->GetBinError(iPOI, iPt, iEta);
                Double_t yield = yldPOIPtEta->GetBinContent(iPOI, iPt, iEta);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }
            } // pt loop

            if (yieldSum) {
                v24POIPt->SetBinContent(iPOI, iPt, vSum / yieldSum);
                v24POIPt->SetBinError(iPOI, iPt, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
            }
        } // eta loop
    } // POI loop

}

// ---------------------------------------------------------------------------------------------------------------------
void flowRebinMaker::integratePtEta(Double_t inPtLow, Double_t inPtUp,
                                    Double_t inEtaLow, Double_t inEtaUp) {
    v22POI =  new TH1D(TString("v22POI").Append(postfix).Data(), "", nPOIs, 0, nPOIs);
    v24POI =  new TH1D(TString("v24POI").Append(postfix).Data(), "", nPOIs, 0, nPOIs);
    yldPOI =  new TH1D(TString("yldPOI").Append(postfix).Data(), "", nPOIs, 0, nPOIs);

    Int_t inPtLowBin  = v22POIPtEta->GetYaxis()->FindBin(inPtLow + 1.0E-6);
    Int_t inPtUpBin   = v22POIPtEta->GetYaxis()->FindBin(inPtUp  - 1.0E-6);
    Int_t inEtaLowBin = v22POIPtEta->GetZaxis()->FindBin(inEtaLow + 1.0E-6);
    Int_t inEtaUpBin  = v22POIPtEta->GetZaxis()->FindBin(inEtaUp  - 1.0E-6);

    cout << "pt:  " << inPtLowBin << "\t" << inPtUpBin << "\n"
         << "Eta:"  << inEtaLowBin << "\t" << inEtaUpBin << endl;
    
    // v22
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        Double_t vSum      = 0.;
        Double_t yieldSum  = 0.;
        Double_t error2sum = 0.;
        Double_t vSqrSum   = 0.;

        for (Int_t iEta = inEtaLowBin; iEta <= inEtaUpBin; ++iEta) { // [inEtaLowBin, inEtaUpBin)
            for (Int_t iPt = inPtLowBin; iPt <= inPtUpBin; ++iPt) {
                Double_t v     = v22POIPtEta->GetBinContent(iPOI, iPt, iEta);
                Double_t verr  = v22POIPtEta->GetBinError(iPOI, iPt, iEta);
                Double_t yield = yldPOIPtEta->GetBinContent(iPOI, iPt, iEta);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }
            } // pt loop
        } // eta loop

        if (yieldSum) {
            v22POI->SetBinContent(iPOI, vSum / yieldSum);
            v22POI->SetBinError(iPOI, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
            yldPOI->SetBinContent(iPOI, yieldSum);
        }
    } // POI loop

    // v24
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        Double_t vSum      = 0.;
        Double_t yieldSum  = 0.;
        Double_t error2sum = 0.;
        Double_t vSqrSum   = 0.;

        for (Int_t iEta = inEtaLowBin; iEta <= inEtaUpBin; ++iEta) { // [inEtaLowBin, inEtaUpBin)
            for (Int_t iPt = inPtLowBin; iPt <= inPtUpBin; ++iPt) {
                Double_t v     = v24POIPtEta->GetBinContent(iPOI, iPt, iEta);
                Double_t verr  = v24POIPtEta->GetBinError(iPOI, iPt, iEta);
                Double_t yield = yldPOIPtEta->GetBinContent(iPOI, iPt, iEta);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }
            } // pt loop
        } // eta loop

        if (yieldSum) {
            v24POI->SetBinContent(iPOI, vSum / yieldSum);
            v24POI->SetBinError(iPOI, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
            yldPOI->SetBinContent(iPOI, yieldSum);
        }
    } // POI loop

    cout << "integratePtEta Done" << endl;
    
}

// -----------------------------------------------------------------------------
void flowRebinMaker::rebinPt(Int_t nBins, Double_t* ptBins) {
    // nBins   : number of bins
    // ptBins  : array of low-edges for each bin. This is an array of size nbins+1

    if (NULL == v22POIPt || NULL == v24POIPt || NULL == yldPOIPt) {
        cerr << "Error: You should integrate diff. v2 over eta firse" << endl;
        return;
    }

    v22POIPtRebin = new TH2D(TString("v22POIPtRebin").Append(postfix).Data(),
                             "v22POIPtRebin;POI#;p_{T}(GeV/c);v_{2}{2}",
                             nPOIs, 0, nPOIs, nBins, ptBins);
    v24POIPtRebin = new TH2D(TString("v24POIPtRebin").Append(postfix).Data(),
                             "v24POIPtRebin;POI#;p_{T}(GeV/c);v_{2}{4}",
                             nPOIs, 0, nPOIs, nBins, ptBins);
    yldPOIPtRebin = new TH2D(TString("yldPOIPtRebin").Append(postfix).Data(),
                             "yldPOIPtRebin;POI#;p_{T}(GeV/c);Yield",
                             nPOIs, 0, nPOIs, nBins, ptBins);
    // v22
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        for (Int_t iBin = 0; iBin < nBins; ++iBin) {
            Int_t    ptBinLow  = v22POIPt->GetYaxis()->FindBin(ptBins[iBin] + 1.0e-6);
            Int_t    ptBinUp   = v22POIPt->GetYaxis()->FindBin(ptBins[iBin+1] - 1.0e-6);
            Double_t vSum      = 0.;
            Double_t yieldSum  = 0.;
            Double_t error2sum = 0.;
            Double_t vSqrSum   = 0.;
            for (Int_t iPt = ptBinLow; iPt <= ptBinUp; ++iPt) {
                Double_t v     = v22POIPt->GetBinContent(iPOI, iPt);
                Double_t verr  = v22POIPt->GetBinError(iPOI, iPt);
                Double_t yield = yldPOIPt->GetBinContent(iPOI, iPt);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }

            } // iPt

            if (yieldSum) {
                v22POIPtRebin->SetBinContent(iPOI, iBin, vSum / yieldSum);
                v22POIPtRebin->SetBinError(iPOI, iBin, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
                yldPOIPtRebin->SetBinContent(iPOI, iBin, yieldSum);
            }

        } // iBin
    } // iPOI

    // v24
    for (Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI) {
        for (Int_t iBin = 0; iBin < nBins; ++iBin) {
            Int_t    ptBinLow  = v24POIPt->GetYaxis()->FindBin(ptBins[iBin] + 1.0e-6);
            Int_t    ptBinUp   = v24POIPt->GetYaxis()->FindBin(ptBins[iBin+1] - 1.0e-6);
            Double_t vSum      = 0.;
            Double_t yieldSum  = 0.;
            Double_t error2sum = 0.;
            Double_t vSqrSum   = 0.;
            for (Int_t iPt = ptBinLow; iPt <= ptBinUp; ++iPt) {
                Double_t v     = v24POIPt->GetBinContent(iPOI, iPt);
                Double_t verr  = v24POIPt->GetBinError(iPOI, iPt);
                Double_t yield = yldPOIPt->GetBinContent(iPOI, iPt);

                if (v != 0) {
                    yieldSum  += yield;
                    vSum      += yield * v;
                    error2sum += pow(yield*verr, 2.);
                    vSqrSum   += yield * (yield*pow(verr, 2.) + pow(v, 2.));
                }

            } // iPt

            if (yieldSum) {
                v24POIPtRebin->SetBinContent(iPOI, iBin, vSum / yieldSum);
                v24POIPtRebin->SetBinError(iPOI, iBin, sqrt(vSqrSum/yieldSum - pow(vSum/yieldSum, 2.)) / sqrt(yieldSum));
            }

        } // iBin
    } // iPOI

    return;
}
