#ifndef StMyDCumulantsMaker_h
#define StMyDCumulantsMaker_h

#include <vector>

#include "StMaker.h"
class StPicoDstMaker;
class StPicoDst;
class StPicoEvent;
class StPicoTrack;

class StRefMultCorr;

#include "Rtypes.h"
#include "TProfile.h"
#include "TProfile3D.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TObjArray.h"
#include "TString.h"

#include "DCCorrelatioinSet.h"

class StMyDCumulantsMaker : public StMaker {
public:
    StMyDCumulantsMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName);
    virtual ~StMyDCumulantsMaker();

    virtual Int_t Init();
    virtual Int_t Make();
    virtual void  Clear(Option_t *opt = "");
    virtual Int_t Finish();

    void    DeclareQAHistograms();
    void    WriteQAHistograms();

    void    DeclareHistograms();
    void    WriteHistograms();

private:
    static const Int_t    nCentBins = 9;
    static const Double_t centLow   = 0;
    static const Double_t centUp    = 9;
    static const Char_t*  centBins[nCentBins];
    static const Int_t    inCentLow = 0; // interested centrality bins
    static const Int_t    inCentUp  = 8;
    
    static const Int_t    nChAsymBins = 4;
    
    static const Double_t ptLow     = 0.0;
    static const Double_t ptUp      = 6.0;
    static const Int_t    nPtBins   = 60;
    static const Double_t ptBinSize;

    static const Double_t etaLow   = -1.0;
    static const Double_t etaUp    =  1.0;
    static const Int_t    nEtaBins =  40;
    
    enum POITypes {
        chargedParticle = 0, piPlus, piMinus,
        nPOIs = 3
    };
    static const Char_t* POINames[nPOIs];
    
    enum DCRefCorrTypes {           // 8 ref. correlations
        C2 = 0, C3, T16, C7, C8, C9, C10, T18, NRefCorrelations = 8
    };

    // ---------------------------------------------------------
    StPicoDstMaker *mPicoDstMaker;
    StPicoDst      *mPicoDst;
    TString         mOutName;

    StRefMultCorr* refmultCorrUtil;
    // -------------- QA ^ --------------------------------------
    // TList* mQAHists;
    TH1D*  hRefMult0;
    TH1D*  hRefMult;
    TH2D*  hVertexXY;
    TH1D*  hVertexZ;
    TH1D*  hCent;
    TH1D*  hPtDist;
    TH1D*  hEtaDist;
    TH1D*  hPhiDist;
    TH1D*  hGDcaDist;
    TH2D*  hM2Pt;
    TH2D*  hM2P;
    TH2D*  hDedxP;
    TH2D*  hCentChAsym;
    
    TH1D*  hNetCharge[nCentBins];
    TH1D*  hChAsym[nCentBins];

    TH2D*  hPOIEtaPt[nPOIs];
    TH2D*  hPOIM2Pt[nPOIs];
    TH2D*  hPOIM2P[nPOIs];
    TH2D*  hPOIDedxP[nPOIs];
    // -------------- QA v --------------------------------------

    
    // correlations of each centrality bin
    DCCorrelatioinSet* mCorrelations[nCentBins];

    // Q vectors
    TH3D* hRep2;
    TH3D* hImp2;
    TH3D* hRep4;
    TH3D* hImp4;
    TH3D* hmp;
    TH3D* hReq2;
    TH3D* hImq2;
    TH3D* hReq4;
    TH3D* hImq4;
    TH3D* hmq;

    TH3D* hCurYield;            // can be removed later

    Int_t centrality(Int_t mult);
    Int_t chAsymBin(Int_t cent, Double_t chAsym);
    bool  passRun(StPicoEvent* pEvent);
    bool  passEvent(StPicoEvent* pEvent);
    bool  passTrack(StPicoTrack* trk);
    bool  passFlowTrack(StPicoTrack* trk);
    bool  passREP(StPicoTrack* trk);
    bool  passPOI(StPicoTrack* trk);
    bool  passChargedParticle(StPicoTrack* trk);
    bool  passPion(StPicoTrack* trk);
    bool  passPiPlus(StPicoTrack* trk);
    bool  passPiMinus(StPicoTrack* trk);

    ClassDef(StMyDCumulantsMaker, 1)
  
};

#endif
