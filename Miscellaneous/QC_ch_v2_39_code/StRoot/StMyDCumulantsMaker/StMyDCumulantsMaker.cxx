#include "StMyDCumulantsMaker.h"

// StRoot
#include "StRoot/StPicoDstMaker/StPicoDst.h"
#include "StRoot/StPicoDstMaker/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoV0.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoDstMaker/StPicoEvent.h"
#include "StThreeVectorF.hh"

#include "StRoot/StRefMultCorr/StRefMultCorr.h"

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TMath.h"
#include "TComplex.h"
#include "TString.h"
#include "TBits.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;

ClassImp(StMyDCumulantsMaker)

// ----------------------------------------------------------------------------
const Char_t* StMyDCumulantsMaker::centBins[nCentBins] = {"70-80%", "60-70%", "50-60%",
                                                          "40-50%", "30-40%", "20-30%",
                                                          "10-20%", "5-10%",  "0-5%"};
const Char_t* StMyDCumulantsMaker::POINames[nPOIs]     = {"charged particle", "piPlus", "piMinus"};

// ----------------------------------------------------------------------------
StMyDCumulantsMaker::StMyDCumulantsMaker(const char     *name,
                                         StPicoDstMaker *picoMaker,
                                         const char     *outName)
    : StMaker(name) {
    mPicoDstMaker = picoMaker;
    mPicoDst      = NULL;
    mOutName      = outName;

    refmultCorrUtil = new StRefMultCorr();

}

// ----------------------------------------------------------------------------
StMyDCumulantsMaker::~StMyDCumulantsMaker() {
    delete refmultCorrUtil;
}

// ----------------------------------------------------------------------------
Int_t StMyDCumulantsMaker::Init() {
    DeclareQAHistograms();
    DeclareHistograms();

    return kStOK;
}

// ----------------------------------------------------------------------------
void StMyDCumulantsMaker::Clear( Option_t *opt ) {
    hRep2->Reset();
    hImp2->Reset();
    hRep4->Reset();
    hImp4->Reset();
    hmp  ->Reset();
    hReq2->Reset();
    hImq2->Reset();
    hReq4->Reset();
    hImq4->Reset();
    hmq  ->Reset();

    hCurYield->Reset();
}

//----------------------------------------------------------------------------- 
Int_t StMyDCumulantsMaker::Finish() {
    TFile *fout = new TFile(mOutName.Data(),"RECREATE");
    if (NULL == fout) {
        LOG_ERROR << "Error: Can not open out file: " << mOutName << endm;
        return kStErr;
    }
    
    fout->cd();
    WriteQAHistograms();
    WriteHistograms();
    fout->Write();
    fout->Close();

    cout << "finish done" << endl;
    return kStOK;
}

//-----------------------------------------------------------------------------
void StMyDCumulantsMaker::DeclareHistograms() {
    // declare histograms for correlations

    TH1::SetDefaultSumw2(kTRUE);
    // TH1::StatOverflows(kTRUE);
    
    for (Int_t i = inCentLow; i <= inCentUp; ++i) {
        mCorrelations[i] = new DCCorrelatioinSet(nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
        mCorrelations[i]->DeclareHistograms();
        mCorrelations[i]->postfix += "_cent";
        mCorrelations[i]->postfix += i;
        for (Int_t k = 0; k < DCCorrelatioinSet::nObjects; ++k) {
            TString hName(mCorrelations[i]->allCorrelations->At(k)->GetName());
            hName += mCorrelations[i]->postfix;
            ((TH1*)mCorrelations[i]->allCorrelations->At(k))->SetName(hName.Data());
        }
    }

    // used by every event, but will not be saved
    hRep2 = new TH3D("Rep2", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hImp2 = new TH3D("Imp2", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hRep4 = new TH3D("Rep4", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hImp4 = new TH3D("Imp4", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hmp   = new TH3D("mp",   "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hReq2 = new TH3D("Req2", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hImq2 = new TH3D("Imq2", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hReq4 = new TH3D("Req4", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hImq4 = new TH3D("Imq4", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
    hmq   = new TH3D("mq",   "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);

    // particle yield for the current event
    hCurYield = new TH3D("curYield", "", nPOIs, 0, nPOIs, nPtBins, ptLow, ptUp, nEtaBins, etaLow, etaUp);
}

//----------------------------------------------------------------------------------
void StMyDCumulantsMaker::WriteHistograms() {
    for ( Int_t i = inCentLow; i <= inCentUp; ++i ) {
        mCorrelations[i]->Write();
    }    
}

//----------------------------------------------------------------------------------
void StMyDCumulantsMaker::DeclareQAHistograms() {
    hRefMult0  = new TH1D("hRefMult0", "Ref. Mult.", 1000, 0, 1000);
    hRefMult0->GetXaxis()->SetTitle("Ref. Mult");

    hRefMult  = new TH1D("hRefMult", "Ref. Mult.", 1000, 0, 1000);
    hRefMult->GetXaxis()->SetTitle("Ref. Mult");

    hVertexXY = new TH2D("hVertexXY", "", 100, -10, 10, 100, -10, 10);
    hVertexXY->GetXaxis()->SetTitle("Vertex X (cm)");
    hVertexXY->GetYaxis()->SetTitle("Vertex Y (cm)");

    hVertexZ  = new TH1D("hVertexZ", "", 200, -100, 100);
    hVertexZ->GetXaxis()->SetTitle("Vertex Z (cm)");

    hCent     = new TH1D("hCent", "events used by ana", 9, 0, 9);
    hCent->GetXaxis()->SetTitle("centrality bin #");
    
    hPtDist   = new TH1D("hPtDist", "p_{T} dist.", 100, 0, 10);
    hPtDist->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    hEtaDist  = new TH1D("hEtaDist", "#eta dist.", 100, -2, 2);
    hEtaDist->GetXaxis()->SetTitle("#eta");

    hPhiDist  = new TH1D("hPhiDist", "#phi dist.", 100, -TMath::Pi(), TMath::Pi());
    hPhiDist->GetXaxis()->SetTitle("#phi");

    hGDcaDist = new TH1D("hGDcaDist", "global dca dist.", 100, 0, 10);
    hGDcaDist->GetXaxis()->SetTitle("gDca (cm)");

    hM2Pt = new TH2D("hM2Pt", "", 600, 0, 6.0, 1200, -2, 10);
    hM2Pt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hM2Pt->GetYaxis()->SetTitle("M^2 (GeV^2)");

    hM2P  = new TH2D("hM2P",  "", 1000, 0, 10, 1200, -2, 10);
    hM2P->GetXaxis()->SetTitle("p (GeV/c)");
    hM2P->GetYaxis()->SetTitle("M^2 (GeV^2)");

    hDedxP = new TH2D("hDedxP", "dE/dx vs q*p", 1000, -5, 5, 800, 0, 80);
    hDedxP->GetXaxis()->SetTitle("p*q");
    hDedxP->GetYaxis()->SetTitle("dE/dx");
    
    hCentChAsym = new TH2D("hCentChAsym", "", nCentBins, 0, nCentBins, nChAsymBins, 0, nChAsymBins);
    hCentChAsym->GetXaxis()->SetTitle("centrality bin #");
    hCentChAsym->GetYaxis()->SetTitle("charge Asym. bin #");

    for (Int_t i = inCentLow; i <= inCentUp; ++i) {
        hNetCharge[i] = new TH1D((TString("hNetCharge_cent")+=i).Data(), "", 200, -100, 100);
        hNetCharge[i]->GetXaxis()->SetTitle("net charge");

        hChAsym[i] = new TH1D((TString("hChAsym_cent")+=i).Data(), "", 200, -1, 1);
        hChAsym[i]->GetXaxis()->SetTitle("charge Asymmetry");
    }

    for (Int_t i = 0; i < nPOIs; ++i) {
        hPOIEtaPt[i] = new TH2D((TString("hPOIPtEta_")+=i).Data(), "", 200, 0, 2.0, 260, -1.3, 1.3);
        hPOIM2Pt[i]  = new TH2D((TString("hPOIM2Pt_")+=i).Data(), "", 200, 0, 2.0, 1200, -2, 10);
        hPOIM2P[i]   = new TH2D((TString("hPOIM2P_")+=i).Data(), "", 200, 0, 5.0, 1200, -2, 10);
        hPOIDedxP[i] = new TH2D((TString("hPOIDedxP_")+=i).Data(), "", 1000, -5, 5, 800, 0, 80);
    }
}

//----------------------------------------------------------------------------------
void StMyDCumulantsMaker::WriteQAHistograms() {
    hRefMult0->Write();
    hRefMult->Write();
    hVertexXY->Write();
    hVertexZ->Write();
    hCent->Write();
    hPtDist->Write();
    hEtaDist->Write();
    hPhiDist->Write();
    hGDcaDist->Write();
    hM2Pt->Write();
    hM2P->Write();
    hDedxP->Write();
    hCentChAsym->Write();
    
    for (Int_t i = inCentLow; i <= inCentUp; ++i) {
        hNetCharge[i]->Write();
        hChAsym[i]->Write();
    }

    for (Int_t i = 0; i < nPOIs; ++i) {
        hPOIEtaPt[i]->Write();
        hPOIM2Pt[i] ->Write();
        hPOIM2P[i] ->Write();
        hPOIDedxP[i]->Write();
    }
}

//----------------------------------------------------------------------------- 
Int_t StMyDCumulantsMaker::Make() {
    if (!mPicoDstMaker) {
        LOG_WARN << " No PicoDstMaker " << endm;
        return kStWarn;
    }

    mPicoDst = mPicoDstMaker->picoDst();
    if (!mPicoDst) {
        LOG_WARN << " No PicoDst " << endm;
        return kStWarn;
    }
  
    StPicoEvent* mPicoEvent = mPicoDst->event();
    if (!mPicoEvent) {
        LOG_WARN << " No picoEvent " << endm;
        return kStWarn;
    }
 
    Int_t refMult = mPicoEvent->refMult();
    if (mPicoEvent->isMinBias() || mPicoEvent->isMBSlow()) {
        hRefMult0->Fill(refMult);
    }
    
    //  pass event
    if (!passRun(mPicoEvent))   return kStOK;
    if (!passEvent(mPicoEvent)) return kStOk;

    StThreeVectorF pVtx = mPicoEvent->primaryVertex();
    Double_t       zdcx = mPicoEvent->ZDCx();

    refmultCorrUtil->init(mPicoEvent->runId());
    refmultCorrUtil->initEvent(refMult, pVtx.z(), zdcx) ;
    Int_t cent  = refmultCorrUtil->getCentralityBin9();
    if (cent < 0 || cent > 8) return kStOk;

    hRefMult->Fill(refMult);
    hVertexXY->Fill(pVtx.x(), pVtx.y());
    hVertexZ->Fill(pVtx.z());

    // track level
    Int_t    nTracks    = mPicoDst->numberOfTracks();
    Double_t netCharge  = 0;
    Double_t chargeNN[2] = {0};

    // ref flow
    Double_t refSumCos2phi = 0;
    Double_t refSumSin2phi = 0;
    Double_t refSumCos4phi = 0;
    Double_t refSumSin4phi = 0;
    Long64_t nREP          = 0;
    
    for ( int iTrk = 0; iTrk < nTracks; ++iTrk ) {
        StPicoTrack* trk = mPicoDst->track(iTrk);
        if ( NULL == trk ) continue;
        if ( !passTrack(trk) ) continue; // basic track cuts

        double charge  = trk->charge();
        netCharge     += charge;
        if ( charge > 0 ) {
            chargeNN[0]++;
        } else if ( charge < 0 ) {
            chargeNN[1]++;
        }

        StThreeVectorF pMom    = trk->pMom();
        Double_t       pt      = pMom.perp();
        Double_t       eta     = pMom.pseudoRapidity();
        Double_t       phi     = pMom.phi();

        Double_t       beta    = trk->btofBeta();
        Double_t       mSquare = beta > 0 ? pMom.mag2()*(pow(1.0/beta, 2.0)-1) : -1;

        // -------- QA ^ -----------------------------------
        hPtDist->Fill(pt);
        hEtaDist->Fill(eta);
        hPhiDist->Fill(phi);
        hGDcaDist->Fill(trk->dca());
        hM2Pt->Fill(pt, mSquare);
        hM2P->Fill(pMom.mag(), mSquare);
        hDedxP->Fill(pMom.mag()*trk->charge(), trk->dEdx());
        // -------- QA v -----------------------------------
        
        double cos2phi = TMath::Cos(2*phi);
        double sin2phi = TMath::Sin(2*phi);
        double cos4phi = TMath::Cos(4*phi);
        double sin4phi = TMath::Sin(4*phi);

        // reference flow
        bool isREP = false;
        if ( passREP(trk) ) {
            isREP = true;
            nREP++;

            refSumCos2phi += cos2phi;
            refSumSin2phi += sin2phi;
            refSumCos4phi += cos4phi;
            refSumSin4phi += sin4phi;
        }

        TBits PIDBits(nPOIs);
        PIDBits.SetBitNumber(chargedParticle, passChargedParticle(trk));
        PIDBits.SetBitNumber(piPlus,  passPiPlus(trk));
        PIDBits.SetBitNumber(piMinus, passPiMinus(trk));
        
        for ( Int_t i = 0; i < nPOIs; ++i ) {
            if ( ! PIDBits.TestBitNumber(i) ) continue;

            // ---- QA ^ -----------------------------------------------
            hPOIEtaPt[i]->Fill(pt, eta);
            hPOIM2Pt[i]->Fill(pt, mSquare);
            hPOIM2P[i]->Fill(pMom.mag(), mSquare);
            hPOIDedxP[i]->Fill(pMom.mag()*trk->charge(), trk->dEdx());
            // ---- QA v -----------------------------------------------
            
            hRep2->Fill(i, pt, eta, cos2phi);
            hImp2->Fill(i, pt, eta, sin2phi);
            hRep4->Fill(i, pt, eta, cos4phi);
            hImp4->Fill(i, pt, eta, sin4phi);
            hmp->Fill(i, pt, eta);

            if (isREP) {
                hReq2->Fill(i, pt, eta, cos2phi);
                hImq2->Fill(i, pt, eta, sin2phi);
                hReq4->Fill(i, pt, eta, cos4phi);
                hImq4->Fill(i, pt, eta, sin4phi);
                hmq->Fill(i, pt, eta);
            }

            hCurYield->Fill(i, pt, eta); // same as hmp, can be removed later
        }
    } // track loop end

    // need 4-particle correlation
    if ( nREP < 4 ) return kStOK;

    Double_t chAsym = (chargeNN[0]-chargeNN[1]) / (chargeNN[0]+chargeNN[1]);
    Int_t    nChBin = chAsymBin(cent, chAsym);
    if (nChBin < 0 || nChBin > nChAsymBins-1) return kStOK;

    // used events
    hCent->Fill(cent);
    hNetCharge[cent]->Fill(netCharge);
    hChAsym[cent]->Fill(chAsym);
    hCentChAsym->Fill(cent, nChBin);

    // get current correlation set according to the centrality and net charge
    DCCorrelatioinSet* curSet = mCorrelations[cent];
    // DCCorrelatioinSet* curSet = mCorrelations[cent*nChAsymBins + nChBin];
    // TString pfix("cent"); pfix += cent;
    // pfix += "_netCh"; pfix += nchBin;
    // if ( ! (*curSet).postfix.Contains(pfix) ) {
    //     LOG_ERROR << "Error: Inconsistent correlation set postfix\n"
    //               << "expected: " << pfix
    //               << "get: " << (*curSet).postfix << endm;
    //     return kStErr;
    // }
    
    // accumulate particle yield
    curSet->hYield->Add(hCurYield);
    
    // ref cumulants
    Double_t M       = nREP;
    Double_t nComb1  = M;
    Double_t nComb2  = M * (M-1);
    Double_t nComb3  = M * (M-1) * (M-2);
    Double_t nComb4  = M * (M-1) * (M-2) * (M-3);
    
//    Double_t weight1 = nComb1;
//    Double_t weight2 = nComb2;
//    Double_t weight3 = nComb3;
//    Double_t weight4 = nComb4;

    Double_t weight1 = 1;
    Double_t weight2 = 1;
    Double_t weight3 = 1;
    Double_t weight4 = 1;


    TComplex Q2(refSumCos2phi, refSumSin2phi);
    TComplex Q4(refSumCos4phi, refSumSin4phi);
    TComplex Q2Star   = TComplex::Conjugate(Q2);
    TComplex Q4Star   = TComplex::Conjugate(Q4);
        
    Double_t Q2Square = Q2.Rho2();
    Double_t Q4Square = Q4.Rho2();
    Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

    Double_t coor22   = (Q2Square - M);
    Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2*ReQQQ
                         - 4*(M-2)*Q2Square + 2*M*(M-3));
    TComplex C7_8     = Q2 * Q2 - Q4;
    TComplex C9_10    = Q2*Q2Star*Q2Star - Q2*Q4Star - 2*(M-1)*Q2Star;

    curSet->pRefCorrelations->Fill(C2,  Q2.Re()/nComb1,    weight1);
    curSet->pRefCorrelations->Fill(C3,  Q2.Im()/nComb1,    weight1);
    curSet->pRefCorrelations->Fill(T16, coor22/nComb2,     weight2);
    curSet->pRefCorrelations->Fill(C7,  C7_8.Re()/nComb2,  weight2);
    curSet->pRefCorrelations->Fill(C8,  C7_8.Im()/nComb2,  weight2);
    curSet->pRefCorrelations->Fill(C9,  C9_10.Re()/nComb3, weight3);
    curSet->pRefCorrelations->Fill(C10, C9_10.Im()/nComb3, weight3);
    curSet->pRefCorrelations->Fill(T18, coor24/nComb4,     weight4);

    curSet->hRefBinSumW2->Fill(C2,  weight1*weight1);
    curSet->hRefBinSumW2->Fill(C3,  weight1*weight1);
    curSet->hRefBinSumW2->Fill(T16, weight2*weight2);
    curSet->hRefBinSumW2->Fill(C7,  weight2*weight2);
    curSet->hRefBinSumW2->Fill(C8,  weight2*weight2);
    curSet->hRefBinSumW2->Fill(C9,  weight3*weight3);
    curSet->hRefBinSumW2->Fill(C10, weight3*weight3);
    curSet->hRefBinSumW2->Fill(T18, weight4*weight4);
    
    // diff cumulants
    for ( Int_t iPOI = 1; iPOI <= nPOIs; ++iPOI ) {
        for ( Int_t iPt = 1; iPt <= nPtBins; ++iPt ) {
            for ( Int_t iEta = 1; iEta <= nEtaBins; ++iEta ) {

                Double_t binPOI = hRep2->GetXaxis()->GetBinCenter(iPOI);
                Double_t binPt  = hRep2->GetYaxis()->GetBinCenter(iPt);
                Double_t binEta = hRep2->GetZaxis()->GetBinCenter(iEta);
                    
                TComplex p2(hRep2->GetBinContent(iPOI, iPt, iEta),
                            hImp2->GetBinContent(iPOI, iPt, iEta));
                TComplex p4(hRep4->GetBinContent(iPOI, iPt, iEta),
                            hImp4->GetBinContent(iPOI, iPt, iEta));
                Double_t mp = hmp->GetBinContent(iPOI, iPt, iEta);

                TComplex q2(hReq2->GetBinContent(iPOI, iPt, iEta),
                            hImq2->GetBinContent(iPOI, iPt, iEta));
                TComplex q4(hReq4->GetBinContent(iPOI, iPt, iEta),
                            hImq4->GetBinContent(iPOI, iPt, iEta));
                Double_t mq = hmq->GetBinContent(iPOI, iPt, iEta);

                Double_t diffNComb1 = mp; 
                Double_t diffNComb2 = mp*M - mq;
                Double_t diffNComb3 = (mp*M - 2*mq) * (M-1);
                Double_t diffNComb4 = (mp*M - 3*mq) * (M-1) * (M-2);

//                Double_t diffWeight1 = diffNComb1;
//                Double_t diffWeight2 = diffNComb2;
//                Double_t diffWeight3 = diffNComb3;
//                Double_t diffWeight4 = diffNComb4;

                Double_t diffWeight1 = 1;
                Double_t diffWeight2 = 1;
                Double_t diffWeight3 = 1;
                Double_t diffWeight4 = 1;
								
                if ( diffNComb1 == 0 || diffNComb2 == 0 ||
                     diffNComb3 == 0 || diffNComb4 == 0 ) continue;

                Double_t diffCoor22  = (p2*Q2Star - mq).Re(); // <2'>
                Double_t diffCoor24  = (p2*Q2*Q2Star*Q2Star - q4*Q2Star*Q2Star - p2*Q2*Q4Star
                                        - 2.0*M*p2*Q2Star - 2.0*mq*Q2Square + 7.0*q2*Q2Star
                                        - Q2*TComplex::Conjugate(q2) + q4*Q4Star + 2.0*p2*Q2Star
                                        + 2.0*mq*M - 6.0*mq).Re(); // <4'>
                TComplex C17 = p2*Q2 - q4;
                TComplex C18 = p2*(Q2Square-M) - (q4*Q2Star + mq*Q2 - 2.0*q2);
                TComplex C19 = p2*Q2Star*Q2Star - p2*Q4Star
                    - (2.0*mq*Q2Star - 2.0*TComplex::Conjugate(q2));

                curSet->pC14 ->Fill(binPOI, binPt, binEta, p2.Re()/diffNComb1,    diffWeight1);
                curSet->pC15 ->Fill(binPOI, binPt, binEta, p2.Im()/diffNComb1,    diffWeight1);
                curSet->pT28 ->Fill(binPOI, binPt, binEta, diffCoor22/diffNComb2, diffWeight2);
                curSet->pC17a->Fill(binPOI, binPt, binEta, C17.Re()/diffNComb2,   diffWeight2);
                curSet->pC17b->Fill(binPOI, binPt, binEta, C17.Im()/diffNComb2,   diffWeight2);
                curSet->pC18a->Fill(binPOI, binPt, binEta, C18.Re()/diffNComb3,   diffWeight3);
                curSet->pC18b->Fill(binPOI, binPt, binEta, C18.Im()/diffNComb3,   diffWeight3);
                curSet->pC19a->Fill(binPOI, binPt, binEta, C19.Re()/diffNComb3,   diffWeight3);
                curSet->pC19b->Fill(binPOI, binPt, binEta, C19.Im()/diffNComb3,   diffWeight3);
                curSet->pT32 ->Fill(binPOI, binPt, binEta, diffCoor24/diffNComb4, diffWeight4);

                curSet->hDiffBinSumW12->Fill(binPOI, binPt, binEta, diffWeight1*diffWeight1);
                curSet->hDiffBinSumW22->Fill(binPOI, binPt, binEta, diffWeight2*diffWeight2);
                curSet->hDiffBinSumW32->Fill(binPOI, binPt, binEta, diffWeight3*diffWeight3);
                curSet->hDiffBinSumW42->Fill(binPOI, binPt, binEta, diffWeight4*diffWeight4);

                curSet->pT16T18->Fill(binPOI, binPt, binEta, (coor22/nComb2)*(coor24/nComb4), weight2*weight4);
                curSet->pT16T28->Fill(binPOI, binPt, binEta, (coor22/nComb2)*(diffCoor22/diffNComb2), weight2*diffWeight2);
                curSet->pT16T32->Fill(binPOI, binPt, binEta, (coor22/nComb2)*(diffCoor24/diffNComb4), weight2*diffWeight4);
                curSet->pT18T28->Fill(binPOI, binPt, binEta, (coor24/nComb4)*(diffCoor22/diffNComb2), weight4*diffWeight2);
                curSet->pT18T32->Fill(binPOI, binPt, binEta, (coor24/nComb4)*(diffCoor24/diffNComb4), weight4*diffWeight4);
                curSet->pT28T32->Fill(binPOI, binPt, binEta, (diffCoor22/diffNComb2)*(diffCoor24/diffNComb4), diffWeight2*diffWeight4);
            }
        }
    }
    
    return kStOK;
}

//----------------------------------------------------------------------------
Int_t StMyDCumulantsMaker::centrality(Int_t mult)
{
    int central = -1;
    float centFull[9] = {7,15,28,50,81,125,185,265,316}; // run10 AuAu 39GeV
    // float centFull[9] = {10, 21, 41, 72, 118, 182, 266, 375, 441}; // run10 AuAu 200GeV
    // float centFull[9] = {14, 31, 57, 96, 150, 222, 319, 441, 520}; // cent200Year4Full

    if      (mult>=centFull[8]) central=8; // 0-5
    else if (mult>=centFull[7]) central=7; // 5-10
    else if (mult>=centFull[6]) central=6; // 10-20
    else if (mult>=centFull[5]) central=5; // 20-30
    else if (mult>=centFull[4]) central=4; // 30-40
    else if (mult>=centFull[3]) central=3; // 40-50
    else if (mult>=centFull[2]) central=2; // 50-60
    else if (mult>=centFull[1]) central=1; // 60-70
    else if (mult>=centFull[0]) central=0; // 70-80

    return central;
}

// ---------------------------------------------------------------------------
Int_t StMyDCumulantsMaker::chAsymBin(Int_t cent, Double_t chAsym) {
    // for run10 39GeV
    // Double_t chAsymBinning[nCentBins][nChAsymBins-1] = {{-0.120, 0.000, 0.160},
    //                                                     {-0.080, 0.030, 0.130},
    //                                                     {-0.050, 0.030, 0.100}, 
    //                                                     {-0.030, 0.030, 0.090}, 
    //                                                     {-0.010, 0.030, 0.080}, 
    //                                                     { 0.000, 0.040, 0.070}, 
    //                                                     { 0.010, 0.040, 0.070}, 
    //                                                     { 0.010, 0.040, 0.070}, 
    //                                                     { 0.010, 0.040, 0.070}};

    // Double_t chAsymBinMean[nCentBins][nChAsymBins] = {{-0.258, -0.078, 0.064, 0.299},
    //                                                   {-0.173, -0.023, 0.076, 0.224},
    //                                                   {-0.117, -0.007, 0.064, 0.169},
    //                                                   {-0.080,  0.002, 0.059, 0.142},
    //                                                   {-0.051,  0.011, 0.054, 0.122},
    //                                                   {-0.034,  0.020, 0.055, 0.105},
    //                                                   {-0.018,  0.025, 0.055, 0.099},
    //                                                   {-0.013,  0.026, 0.055, 0.095},
    //                                                   {-0.011,  0.026, 0.055, 0.093}};

    // rejected bad runs
    // Double_t chAsymBinning[nCentBins][nChAsymBins-1] = {{-0.120, 0.000, 0.160},
    //                                                     {-0.080, 0.030, 0.130},
    //                                                     {-0.050, 0.030, 0.100}, 
    //                                                     {-0.030, 0.030, 0.090}, 
    //                                                     {-0.010, 0.030, 0.080}, 
    //                                                     { 0.000, 0.040, 0.070}, 
    //                                                     { 0.010, 0.040, 0.070}, 
    //                                                     { 0.010, 0.040, 0.070}, 
    //                                                     { 0.010, 0.040, 0.070}};

    // Double_t chAsymBinMean[nCentBins][nChAsymBins] = {{-0.258, -0.078, 0.064, 0.298},
    //                                                   {-0.173, -0.023, 0.076, 0.223},
    //                                                   {-0.117, -0.007, 0.064, 0.169},
    //                                                   {-0.080,  0.002, 0.059, 0.142},
    //                                                   {-0.051,  0.011, 0.054, 0.122},
    //                                                   {-0.035,  0.020, 0.055, 0.106},
    //                                                   {-0.018,  0.025, 0.055, 0.099},
    //                                                   {-0.014,  0.026, 0.055, 0.096},
    //                                                   {-0.011,  0.026, 0.055, 0.094}};

    // ptMin = 0.15GeV, w/o tof PID
    Double_t chAsymBinning[nCentBins][nChAsymBins-1] = {{-0.120, 0.000, 0.150},
                                                        {-0.080, 0.020, 0.110},
                                                        {-0.050, 0.020, 0.100}, 
                                                        {-0.030, 0.030, 0.080}, 
                                                        {-0.010, 0.030, 0.070}, 
                                                        { 0.000, 0.030, 0.070}, 
                                                        { 0.000, 0.030, 0.060}, 
                                                        { 0.010, 0.030, 0.060}, 
                                                        { 0.010, 0.040, 0.060}};
    Double_t chAsymBinMean[nCentBins][nChAsymBins] = {{-0.252, -0.077, 0.060, 0.284},
                                                      {-0.167, -0.028, 0.062, 0.200},
                                                      {-0.113, -0.012, 0.059, 0.164},
                                                      {-0.078,  0.002, 0.054, 0.130},
                                                      {-0.049,  0.012, 0.050, 0.111},
                                                      {-0.033,  0.015, 0.049, 0.102},
                                                      {-0.026,  0.015, 0.045, 0.089},
                                                      {-0.013,  0.020, 0.045, 0.086},
                                                      {-0.011,  0.026, 0.050, 0.084}};

    if (chAsym < chAsymBinning[cent][0]) {
        return 0;
    } else if (chAsym < chAsymBinning[cent][1]) {
        return 1;
    } else if (chAsym < chAsymBinning[cent][2]) {
        return 2;
    } else {
        return 3;
    }
    return -1;
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passRun(StPicoEvent* pEvent) {
    // bad run, Wang Gang
    // const Int_t nBadRuns = 78;
    // Int_t badRun[nBadRuns] = {11100005, 11100007, 11100010, 11100045, 11100056,
    //                           11100085, 11101013, 11101015, 11101016, 11101018,
    //                           11101025, 11101056, 11101109, 11102012, 11102056,
    //                           11102092, 11102108, 11103031, 11103034, 11103064,
    //                           11103086, 11103099, 11104001, 11105052, 11105053,
    //                           11105055, 11106002, 11106096, 11106098, 11106099,
    //                           11106101, 11107007, 11107019, 11107030, 11107057,
    //                           11107065, 11108014, 11108076, 11108099, 11108101,
    //                           11108102, 11109015, 11109024, 11109034, 11109036,
    //                           11109063, 11109078, 11109079, 11109088, 11110009,
    //                           11110012, 11110029, 11110095, 11110098, 11111029,
    //                           11111058, 11111089, 11112009, 11112018, 11100009,
    //                           11104002, 11109097, 11110105, 11102039, 11103046,
    //                           11109090, 11110090, 11110094, 11112020, 11101012,
    //                           11102021, 11102033, 11102107, 11105045, 11105056,
    //                           11106001, 11106003, 11109037};

    // badRun, hmasui
    Int_t nBadRuns = 38;
    Int_t bad_run_list_39GeV[38]  = {11199124,11100002,11100045,11101046,11102012,11102051,11102052,11102053,11102054,11102055,11102058,11103035,11103056,11103058,11103092,11103093,11105052,11105053,11105054,11105055,11107007,11107042,11107057,11107061,11107065,11107074,11108101,11109013,11109077,11109088,11109090,11109127,11110013,11110034,11110073,11110076,11111084,11111085};

    Int_t* badRun = &(bad_run_list_39GeV[0]);
    
    Int_t runnumber = pEvent->runId();

    return (std::find(badRun, badRun+nBadRuns, runnumber) == badRun+nBadRuns);
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passEvent(StPicoEvent* pEvent) {
    if (NULL == pEvent) return false;

    if (! pEvent->isMinBias()) return false;

    StThreeVectorF Vertex = pEvent->primaryVertex();
    if (Vertex.perp() > 2.0 )                         return false;
    if (TMath::Abs(Vertex.z()) > 40)                  return false;
    if (pEvent->btofTrayMultiplicity() <= 5)          return false;

    return true;
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passTrack(StPicoTrack* trk)
{
    // for pico data, noly need to choose primary tracks
    
    if (!trk)                                           return kFALSE;
    if (trk->nHitsFit() <= 15)                          return kFALSE;
    if (trk->dca() > 2.0)                               return kFALSE;
    if (trk->pMom().perp() < 0.2)                       return kFALSE;
    if (TMath::Abs(trk->pMom().pseudoRapidity()) > 1.0) return kFALSE;

    return kTRUE;
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passFlowTrack(StPicoTrack* trk)
{
    // if ( trk->flowFlag() == others ) return false;
    
    // double pt = trk->pt();
    // if ( pt < ptLow || pt >= ptUp ) return false;

    // if ( !TMath::Abs(trk->charge()) != 1 ) return false;
    
    return true;
}

// ---------------------------------------------------------------------------
bool  StMyDCumulantsMaker::passREP(StPicoTrack* trk) {
    if (trk->flowFlag() != tpcFlow) return false;
    // if (trk->charge()   == 0)      return false;

    return true;
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passChargedParticle(StPicoTrack* trk) {
    if (trk->charge() == 0) return kFALSE;

    return kTRUE;
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passPiPlus(StPicoTrack* trk) {
    return passPion(trk) && (trk->charge() == +1);
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passPiMinus(StPicoTrack* trk) {
    return passPion(trk) && (trk->charge() == -1);
}

// ---------------------------------------------------------------------------
bool StMyDCumulantsMaker::passPion(StPicoTrack* trk) {
    // valide up to pt ~ 1.5GeV
    // if (TMath::Abs(trk->nSigmaPion()) > 2.0) return false;

    Double_t p2      = trk->pMom().mag2();
    Double_t beta    = trk->btofBeta();
    Double_t mSquare = beta > 0 ? p2*(pow(1/beta, 2)-1) : -1;
    if (mSquare > 0.1) return false;
    if (mSquare < 0.001) return false;

    return true;
}
