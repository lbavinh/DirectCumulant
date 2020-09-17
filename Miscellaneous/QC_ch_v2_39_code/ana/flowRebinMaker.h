#ifndef FLOWREBINMAKER_H
#define FLOWREBINMAKER_H

#include "Rtypes.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TString.h"

class flowRebinMaker {
public:
    flowRebinMaker();
    ~flowRebinMaker();
    
    Int_t readHists(TFile* inFile = NULL, const Char_t* pfix = "");
    Int_t writeHists(TFile* outFile);
    void  integratePt(Double_t inPtLow, Double_t inPtUp);
    void  integrateEta(Double_t inEtaLow, Double_t inEtaUp);
    void  integratePtEta(Double_t inPtLow, Double_t inPtUp, Double_t inEtaLow, Double_t inEtaUp);

    void  rebinPt(Int_t nBins, Double_t* ptBins);
    
    Int_t GetNPtBins() {return nPtBins;}
    Int_t GetPtLow()   {return ptLow;}
    Int_t GetPtUp()    {return ptUp;}

    Int_t GetNEtaBins() {return nEtaBins;}
    Int_t GetEtaLow()   {return etaLow;}
    Int_t GetEtaUp()    {return etaUp;}

    // 3D, v2 POI pt eta
    TH3D* v22POIPtEta;
    TH3D* v24POIPtEta;
    TH3D* yldPOIPtEta;

    // 2D, v2 POI pt
    TH2D* v22POIPt;
    TH2D* v24POIPt;
    TH2D* yldPOIPt;

    TH2D* v22POIPtRebin;
    TH2D* v24POIPtRebin;
    TH2D* yldPOIPtRebin;

    TH2D* v22POIEta;
    TH2D* v24POIEta;
    TH2D* yldPOIEta;

    // 1D, integrated v2
    TH1D* v22POI;
    TH1D* v24POI;
    TH1D* yldPOI;

private:
    TString postfix;
    
    Int_t nPOIs;

    Int_t nPtBins;
    Double_t ptLow, ptUp;

    Int_t nEtaBins;
    Double_t etaLow, etaUp;

    ClassDef(flowRebinMaker, 1);
};

#endif
