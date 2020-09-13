// Do not forget to source setPicoDst.sh script

#include <iostream>
#include <TDatabasePDG.h>
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2F.h>
#include <TMath.h>

#include <TF2.h>
#include <iostream>
#include <fstream>
#include "TComplex.h"

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>

// R__LOAD_LIBRARY(libPicoDst.so)

//TFile *inputDCAfile = new TFile("/nica/mpd21/parfenov/mpd_winter2019/mpd_prod/7.7gev/prod_new_test_picodst/dca/dca_fit.root");

TFile *d_outfile;
int min_mult = 2;
static const float Pi = 3.141592654;
static const int n = 2;
float b_bin[9] = {0.0, 4.18, 6.01, 7.37, 8.52, 9.57, 10.55, 11.46, 12.31};
static const int Nb = 8;
float pt_min = 0.2, pt_max = 2.5, eta_min = 0.05, eta_max = 1.5;
int Nhits = 16;
float pt_bin[9] = {0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.5, 1.8, 2.5};
static const int NN = 8;
float DCAsigma = 2000.;

float MQ2[Nb], MQ4[Nb], M[Nb];
float MCQ[Nb];
TComplex Q[Nb], Q2[Nb], ZQQQ[Nb];
TComplex p[Nb][NN], p2[Nb][NN];
TComplex q[Nb][NN], q2[Nb][NN];
float mp[Nb][NN], mq[Nb][NN];
float DiffMQ2[Nb][NN], DiffMQ4[Nb][NN];
float sv4[Nb], sv2[Nb], v4[Nb], v2[Nb], vMC[Nb], vEvPl[Nb], cn2[Nb], cn4[Nb];

float PSIplus[Nb], PSIminus[Nb], PSI[Nb], Mplus[Nb], Mminus[Nb], Vobs[Nb];
TComplex Qplus[Nb], Qminus[Nb];

float dMplus[Nb][NN], dMminus[Nb][NN], dVobs[Nb][NN];

TH1F *SV2[Nb]; //2 частичная референсная корреляция
TH1F *SV4[Nb]; //4 частичная референсная корреляция
TH1F *COSf1[Nb];
TH1F *SINf1[Nb];
TH1F *COSf1f2[Nb];
TH1F *SINf1f2[Nb];
TH1F *COSf1f2f3[Nb];
TH1F *SINf1f2f3[Nb];
TH1I *hNpart = new TH1I("hNpart", "hNpart", 6000, 0, 6000);
TH1F *hBimp = new TH1F("hBimp", "hBimp", 1000, 0, 25);
TH1F *hPt = new TH1F("hPt", "hPt", 1000, 0, 5);
TH1F *hETA = new TH1F("hETA", "hETA", 1000, -8, 8);
TH1F *hdPHI = new TH1F("hdPHI", "dPHI", 1000, -0.2, 6.5);

TH1F *HMC[Nb], *HQx[Nb], *HQy[Nb], *HQxKor[Nb], *HQyKor[Nb], *HPHI[Nb], *HRES[Nb], *HVobs[Nb], *HDiffVobs[Nb][NN];
TH1F *SV2_SV4[Nb];
TH1F *DiffMC[Nb][NN], *DiffSV2[Nb][NN], *DiffSV4[Nb][NN];
TH1F *SV2_DiffSV2[Nb][NN], *SV2_DiffSV4[Nb][NN];
TH1F *SV4_DiffSV2[Nb][NN], *SV4_DiffSV4[Nb][NN];
TH1F *DiffSV2_DiffSV4[Nb][NN];
TH1F *hBin_Pt[Nb][NN];

TH1F *COSp1[Nb][NN], *SINp1[Nb][NN];
TH1F *COSp1f2[Nb][NN], *SINp1f2[Nb][NN];
TH1F *COSp1f2mf3[Nb][NN], *SINp1f2mf3[Nb][NN];
TH1F *COSp1mf2mf3[Nb][NN], *SINp1mf2mf3[Nb][NN];

float *binPt = new float[NN];
float QMC[Nb][NN];
float dn2[Nb][NN], dn4[Nb][NN];
float Diffv2[Nb][NN], Diffv4[Nb][NN], DiffEvPlv[Nb][NN];
float Diffsv2[Nb][NN], Diffsv4[Nb][NN];
float neff[Nb];
float Sigma[Nb], Res[Nb];
float QxMEAN[Nb], QxSIGMA[Nb], QyMEAN[Nb], QySIGMA[Nb];
char strvObs[200];
char strRES[200];

char strCOVsv2sv2[200];
char strCOVsv2sv4[200];
char strCOVsv4sv2[200];
char strCOVsv4sv4[200];
char DiffCOVsv2sv4[200];
char strE[200];
char strW[200];
char strMC[200];

char strCOSp1[200];
char strSINp1[200];
char strCOSp1f2[200];
char strSINp1f2[200];
char strCOSp1f2mf3[200];
char strSINp1f2mf3[200];
char strCOSp1mf2mf3[200];
char strSINp1mf2mf3[200];
char hBinPt[200];
char str[200];
const char *STR;

static const int garm = 1;
TH1F *HMeanCosP[Nb][garm], *HMeanSinP[Nb][garm];
float MeanCosP[Nb][garm], MeanSinP[Nb][garm];

void Book()
{

    for (int k = 0; k < Nb; k++)
    {
        sprintf(str, "%sCENT%d_%d", "sv2", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SV2[k] = new TH1F(STR, "sv2", 500, -0.5, 0.5);

        sprintf(str, "%sCENT%d_%d", "sv4", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SV4[k] = new TH1F(STR, "sv4", 500, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "cosf1", k * 10, (k + 1) * 10);
        STR = (char *)str;
        COSf1[k] = new TH1F(STR, "cosf1", 100, -1, 1);

        sprintf(str, "%sCENT%d_%d", "cosf1f2", k * 10, (k + 1) * 10);
        STR = (char *)str;
        COSf1f2[k] = new TH1F(STR, "cosf1f2", 100, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "cosf1f2f3", k * 10, (k + 1) * 10);
        STR = (char *)str;
        COSf1f2f3[k] = new TH1F(STR, "cosf1f2f3", 100, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "sinf1", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SINf1[k] = new TH1F(STR, "sinf1", 100, -0.5, 0.5);

        sprintf(str, "%sCENT%d_%d", "sinf1f2", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SINf1f2[k] = new TH1F(STR, "sinf1f2", 100, -0.1, 0.1);
        sprintf(str, "%sCENT%d_%d", "sinf1f2f3", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SINf1f2f3[k] = new TH1F(STR, "sinf1f2f3", 100, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "sv2_sv4", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SV2_SV4[k] = new TH1F(STR, "sv2_sv4", 500, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "mc", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HMC[k] = new TH1F(STR, "mc", 400, -1, 1);

        sprintf(str, "%sCENT%d_%d", "HQx", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HQx[k] = new TH1F(STR, "HQx", 400, -200, 200);
        sprintf(str, "%sCENT%d_%d", "HQy", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HQy[k] = new TH1F(STR, "HQy", 400, -200, 200);

        sprintf(str, "%sCENT%d_%d", "HRES", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HRES[k] = new TH1F(STR, "HRES", 200, -1, 1);

        sprintf(str, "%sCENT%d_%d", "PHI", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HPHI[k] = new TH1F(STR, "PHI", 100, -0.5, 0.5);

        sprintf(str, "%sCENT%d_%d", "Vobs", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HVobs[k] = new TH1F(STR, "Vobs", 200, -1, 1);

        SV2[k]->StatOverflows(kTRUE);
        SV4[k]->StatOverflows(kTRUE);
        HPHI[k]->StatOverflows(kTRUE);
        HMC[k]->StatOverflows(kTRUE);
        HVobs[k]->StatOverflows(kTRUE);
        SV2[k]->Sumw2();
        SV4[k]->Sumw2();
        HMC[k]->Sumw2();
        HPHI[k]->Sumw2();
        HRES[k]->Sumw2();
        HVobs[k]->Sumw2();
        QxMEAN[k] = 0.;
        QxSIGMA[k] = 1.;
        QyMEAN[k] = 0.;
        QySIGMA[k] = 1.;

        for (int g = 0; g < garm; g++)
        {
            sprintf(str, "%s%dGARM%d_%d", "HMeanCosP", 2 * g + 2, k * 10, (k + 1) * 10);
            STR = (char *)str;
            HMeanCosP[k][g] = new TH1F(STR, "HMeanCosP", 10000, -100, 100);
            sprintf(str, "%s%dGARM%d_%d", "HMeanSinP", 2 * g + 2, k * 10, (k + 1) * 10);
            STR = (char *)str;
            HMeanSinP[k][g] = new TH1F(STR, "HMeanSinP", 10000, -100, 100);
        }

        for (int m = 0; m < NN; m++)
        {
            sprintf(strE, "%s%d_CENT%d_%d", "sv2Diff", m, k * 10, (k + 1) * 10);
            sprintf(strW, "%s%d_CENT%d_%d", "sv4Diff", m, k * 10, (k + 1) * 10);
            sprintf(strMC, "%s%d_CENT%d_%d", "DiffMC", m, k * 10, (k + 1) * 10);
            sprintf(strCOVsv2sv2, "%s%d_CENT%d_%d", "SV2_DiffSV2", m, k * 10, (k + 1) * 10);
            sprintf(strCOVsv2sv4, "%s%d_CENT%d_%d", "SV2_DiffSV4", m, k * 10, (k + 1) * 10);
            sprintf(strCOVsv4sv2, "%s%d_CENT%d_%d", "SV4_DiffSV2", m, k * 10, (k + 1) * 10);
            sprintf(strCOVsv4sv4, "%s%d_CENT%d_%d", "SV4_DiffSV4", m, k * 10, (k + 1) * 10);
            sprintf(DiffCOVsv2sv4, "%s%d_CENT%d_%d", "DiffSV2_DiffSV4", m, k * 10, (k + 1) * 10);
            sprintf(strCOSp1, "%s%d_CENT%d_%d", "COSp1", m, k * 10, (k + 1) * 10);
            sprintf(strCOSp1f2, "%s%d_CENT%d_%d", "COSp1f2", m, k * 10, (k + 1) * 10);
            sprintf(strCOSp1f2mf3, "%s%d_CENT%d_%d", "COSp1f2mf3", m, k * 10, (k + 1) * 10);
            sprintf(strCOSp1mf2mf3, "%s%d_CENT%d_%d", "COSp1mf2mf3", m, k * 10, (k + 1) * 10);
            sprintf(strSINp1, "%s%d_CENT%d_%d", "SINp1", m, k * 10, (k + 1) * 10);
            sprintf(strSINp1f2, "%s%d_CENT%d_%d", "SINp1f2", m, k * 10, (k + 1) * 10);
            sprintf(strSINp1f2mf3, "%s%d_CENT%d_%d", "SINp1f2mf3", m, k * 10, (k + 1) * 10);
            sprintf(strSINp1mf2mf3, "%s%d_CENT%d_%d", "SINp1mf2mf3", m, k * 10, (k + 1) * 10);
            sprintf(hBinPt, "%s%d_CENT%d_%d", "BIN_pt_", m, k * 10, (k + 1) * 10);
            sprintf(strvObs, "%s%d_CENT%d_%d", "diffVobs", m, k * 10, (k + 1) * 10);
            sprintf(strRES, "%s%d_CENT%d_%d", "diffRES", m, k * 10, (k + 1) * 10);

            const char *rvObs = (char *)strvObs;
            const char *rRES = (char *)strRES;
            const char *EastH = (char *)strE;
            const char *WastH = (char *)strW;
            const char *SMC = (char *)strMC;
            const char *stCOVsv2sv2 = (char *)strCOVsv2sv2;
            const char *stCOVsv2sv4 = (char *)strCOVsv2sv4;
            const char *stCOVsv4sv2 = (char *)strCOVsv4sv2;
            const char *stCOVsv4sv4 = (char *)strCOVsv4sv4;
            const char *DifCOVsv2sv4 = (char *)DiffCOVsv2sv4;
            const char *stCOSp1 = (char *)strCOSp1;
            const char *stCOSp1f2 = (char *)strCOSp1f2;
            const char *stCOSp1f2mf3 = (char *)strCOSp1f2mf3;
            const char *stCOSp1mf2mf3 = (char *)strCOSp1mf2mf3;
            const char *stSINp1 = (char *)strSINp1;
            const char *stSINp1f2 = (char *)strSINp1f2;
            const char *stSINp1f2mf3 = (char *)strSINp1f2mf3;
            const char *stSINp1mf2mf3 = (char *)strSINp1mf2mf3;
            const char *HBinPt = (char *)hBinPt;

            HDiffVobs[k][m] = new TH1F(rvObs, "Diffvobs", 200, -1, 1);
            DiffSV2[k][m] = new TH1F(EastH, "Diffsv2", 500, -0.5, 0.5);
            DiffSV4[k][m] = new TH1F(WastH, "Diffsv4", 500, -0.2, 0.2);
            DiffMC[k][m] = new TH1F(SMC, "MC", 100, -1, 1);
            SV2_DiffSV2[k][m] = new TH1F(stCOVsv2sv2, "sv2sv2", 500, -0.1, 0.1);
            SV2_DiffSV4[k][m] = new TH1F(stCOVsv2sv4, "sv2sv4", 500, -0.1, 0.1);
            SV4_DiffSV2[k][m] = new TH1F(stCOVsv4sv2, "sv4sv2", 500, -0.1, 0.1);
            SV4_DiffSV4[k][m] = new TH1F(stCOVsv4sv4, "sv4sv4", 500, -0.1, 0.1);
            DiffSV2_DiffSV4[k][m] = new TH1F(DifCOVsv2sv4, "diffsv2sv4", 500, -0.1, 0.1);
            COSp1[k][m] = new TH1F(stCOSp1, "COSp1", 100, -1, 1);
            COSp1f2[k][m] = new TH1F(stCOSp1f2, "COSp1f2", 100, -0.2, 0.2);
            COSp1f2mf3[k][m] = new TH1F(stCOSp1f2mf3, "COSp1f2mf3", 100, -0.2, 0.2);
            COSp1mf2mf3[k][m] = new TH1F(stCOSp1mf2mf3, "COSp1mf2mf3", 100, -0.2, 0.2);
            SINp1[k][m] = new TH1F(stSINp1, "SINp1", 100, -1, 1);
            SINp1f2[k][m] = new TH1F(stSINp1f2, "SINp1f2", 100, -0.2, 0.2);
            SINp1f2mf3[k][m] = new TH1F(stSINp1f2mf3, "SINp1f2mf3", 100, -0.2, 0.2);
            SINp1mf2mf3[k][m] = new TH1F(stSINp1mf2mf3, "SINp1mf2mf3", 100, -0.2, 0.2);
            hBin_Pt[k][m] = new TH1F(HBinPt, "Bin_Pt", 100, -1, 1);

            DiffSV2[k][m]->StatOverflows(kTRUE);

            HVobs[k]->StatOverflows(kTRUE);
            SV2_DiffSV2[k][m]->StatOverflows(kTRUE);
            SV2_DiffSV4[k][m]->StatOverflows(kTRUE);
            SV4_DiffSV2[k][m]->StatOverflows(kTRUE);
            SV4_DiffSV4[k][m]->StatOverflows(kTRUE);
            DiffSV2_DiffSV4[k][m]->StatOverflows(kTRUE);
        }
    }
}

TComplex Sopr(TComplex Z)
{
    return TComplex::Conjugate(Z);
}

float Eta(float momx, float momy, float momz)
{
    float mom = pow(momx * momx + momy * momy + momz * momz, 0.5);
    return 0.5 * log((mom + momz) / (mom - momz));
}

float fPt(float momx, float momy, float momz)
{
    float mom = pow(momx * momx + momy * momy, 0.5);
    return mom;
}

float Phi(float momx, float momy, float momz)
{

    float phi = TMath::ATan2(momy, momx);
    if (phi < 0)
    {
        phi = phi + 2 * Pi;
    }
    return phi;
}

void Centering(const char *infileC)
{
    TFile *fC = new TFile(infileC);
    for (int k = 0; k < Nb; k++)
    {
        sprintf(str, "%sCENT%d_%d", "HQx", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HQxKor[k] = (TH1F *)fC->Get(STR);
        sprintf(str, "%sCENT%d_%d", "HQy", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HQyKor[k] = (TH1F *)fC->Get(STR);

        QxMEAN[k] = HQxKor[k]->GetMean();
        QxSIGMA[k] = HQxKor[k]->GetRMS() / pow(HQxKor[k]->GetEntries(), 0.5);
        QyMEAN[k] = HQyKor[k]->GetMean();
        QySIGMA[k] = HQyKor[k]->GetRMS() / pow(HQyKor[k]->GetEntries(), 0.5);
    }
}

float KorPSI(float Psi, int cent)
{
    float kor = 0;
    for (int g = 0; g < garm; g++)
    {
        kor += (-MeanSinP[cent][g] * cos(Psi * (g + 1)) + MeanCosP[cent][g] * sin(Psi * (g + 1))) * 2 / (1 + g);
    };
    return kor / n;
}

float PHIn(float x, float y, int cent)
{
    float PHIn = TMath::ATan2((y - QyMEAN[cent]), (x - QxMEAN[cent]));
    if (PHIn < 0)
    {
        PHIn = PHIn + 2 * Pi;
    }
    if (PHIn > 2 * Pi)
    {
        PHIn = PHIn - 2 * Pi;
    }

    return PHIn / n;
}

bool RefETA(float eta)
{
    if ((eta > eta_min && eta < eta_max) || (eta > -eta_max && eta < -eta_min))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void readPicoDst(TString inputFileName)
{
    TStopwatch timer;
    timer.Start();

    //TF2 *fDCAx = (TF2 *)inputDCAfile->Get("f_sigma0");
    //TF2 *fDCAy = (TF2 *)inputDCAfile->Get("f_sigma1");
    //TF2 *fDCAz = (TF2 *)inputDCAfile->Get("f_sigma2");

    int t = 0;
    float Ntree = 0;
    float Mf[Nb], dMf[Nb][NN], eta, pt, phi, rp, mcevent_fB;

    // Configure input information
    TChain *chain = new TChain("picodst");
    chain->Add(inputFileName.Data());

    PicoDstMCEvent *mcEvent = nullptr;
    TClonesArray *recoTracks = nullptr;
    TClonesArray *mcTracks = nullptr;

    // chain->SetBranchAddress("mcevent.", &mcEvent);
    // chain->SetBranchAddress("recotracks",&recoTracks);
    chain->SetBranchAddress("mcevent.", &mcEvent);
    chain->SetBranchAddress("recotracks", &recoTracks);
    chain->SetBranchAddress("mctracks", &mcTracks);

    // Start event loop
    int n_entries = chain->GetEntries();
    for (int iEv = 0; iEv < n_entries; iEv++)
    {
        if (iEv % 1000 == 0)
            std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
        chain->GetEntry(iEv);

        //Обнуление переменных
        for (int k = 0; k < Nb; k++)
        {
            MQ2[k] = 0;
            Mf[k] = 0;
            Vobs[k] = 0;
            Mplus[k] = 0;
            Mminus[k] = 0;
            MQ4[k] = 0;
            M[k] = 0;
            MCQ[k] = 0;

            Qplus[k] = TComplex(0, 0);
            Qminus[k] = TComplex(0, 0);
            Q[k] = TComplex(0, 0);
            Q2[k] = TComplex(0, 0);
            ZQQQ[k] = TComplex(0, 0);
            Res[k] = 0;
            for (int s = 0; s < NN; s++)
            {
                dMf[k][s] = 0;
                dVobs[k][s] = 0;
                dMplus[k][s] = 0;
                dMminus[k][s] = 0;

                p[k][s] = TComplex(0, 0);
                p2[k][s] = TComplex(0, 0);
                mp[k][s] = 0;
                q[k][s] = TComplex(0, 0);
                q2[k][s] = TComplex(0, 0);
                mq[k][s] = 0;
                Diffsv2[k][s] = 0;
                DiffMQ2[k][s] = 0;
                Diffsv4[k][s] = 0;
                DiffMQ4[k][s] = 0;
                QMC[k][s] = 0;
            }
        }

        //cout << "hBimp" << endl;

        //rp=2*Pi*(rnd.Rndm());

        rp = mcEvent->GetPhiRP();
        mcevent_fB = mcEvent->GetB();
        Int_t reco_mult = recoTracks->GetEntriesFast();

        // Read Reco tracks

        for (int k = 0; k < Nb; k++)
        {
            if (mcevent_fB >= b_bin[k] && mcevent_fB < b_bin[k + 1])
            {
                hBimp->Fill(mcEvent->GetB());

                for (int i = 0; i < reco_mult; i++)
                {
                    auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(i);
                    if (!recoTrack)
                        continue;
                    pt = recoTrack->GetPt();
                    eta = recoTrack->GetEta();
                    phi = recoTrack->GetPhi();
                    auto mcTrack = (PicoDstMCTrack *)mcTracks->UncheckedAt(recoTrack->GetMcId());
                    if (!mcTrack)
                        continue;

                    if (mcTrack->GetMotherId() != -1)
                        continue;

                    // PID-related cut
                    auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
                    if (!particle)
                        continue;
                    float charge = 1. / 3. * particle->Charge();
                    //if(charge<=0) continue;
                    if (phi < 0)
                    {
                        phi = phi + 2 * Pi;
                    }

                    /*if (fabs(recoTrack->GetDCAx()) > DCAsigma )
                        continue; //трек не проходит по DCAx
                    if (fabs(recoTrack->GetDCAy()) > DCAsigma)
                        continue; //трек не проходит по DCAy
                    if (fabs(recoTrack->GetDCAz()) > DCAsigma)
                        continue; //трек не проходит по DCAz*/

                    if (recoTrack->GetNhits() < Nhits)
                        continue;

                    hdPHI->Fill(phi);

                    if (eta > -eta_max && eta < -eta_min && pt > pt_min && pt < pt_max)
                    {
                        hETA->Fill(eta);
                        hPt->Fill(pt);
                        Qminus[k] += TComplex(cos(n * (phi)), sin(n * (phi)));
                        Mminus[k] += 1;
                    }
                    if (eta < eta_max && eta > eta_min && pt > pt_min && pt < pt_max)
                    {
                        hETA->Fill(eta);
                        hPt->Fill(pt);
                        Qplus[k] += TComplex(cos(n * (phi)), sin(n * (phi)));
                        Mplus[k] += 1;
                        MCQ[k] += cos(n * (phi - rp));
                        Mf[k] += 1;
                    }

                    if (eta > -eta_max && eta < -eta_min && pt > pt_min && pt < pt_max)
                    {
                        Q[k] += TComplex(cos(n * (phi)), sin(n * (phi)));
                        Q2[k] += TComplex(cos(2 * n * (phi)), sin(2 * n * (phi)));
                        MCQ[k] += cos(n * (phi - rp));
                        Mf[k] += 1;
                        M[k] += 1;
                    }

                    if (eta < eta_max && eta > eta_min && pt > pt_min && pt < pt_max)
                    {
                        for (int m = 0; m < NN; m++)
                        {
                            if (pt >= pt_bin[m] && pt < pt_bin[m + 1])
                            {
                                mp[k][m] += 1;
                                hBin_Pt[k][m]->Fill(pt);
                                p2[k][m] += TComplex(cos(2 * n * (phi)), sin(2 * n * (phi)));
                                p[k][m] += TComplex(cos(n * (phi)), sin(n * (phi)));

                                QMC[k][m] += (cos(n * (phi - rp)));
                                dMf[k][m] += 1;
                            }
                        }
                    }
                }
            }
        }

        for (int k = 0; k < Nb; k++)
        {
            if (mcevent_fB >= b_bin[k] && mcevent_fB < b_bin[k + 1])
            {
                PSIplus[k] = PHIn(Qplus[k].Re(), Qplus[k].Im(), k);
                PSIminus[k] = PHIn(Qminus[k].Re(), Qminus[k].Im(), k);

                for (int i = 0; i < reco_mult; i++)
                {
                    auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(i);
                    if (!recoTrack)
                        continue;
                    pt = recoTrack->GetPt();
                    eta = recoTrack->GetEta();
                    phi = recoTrack->GetPhi();
                    auto mcTrack = (PicoDstMCTrack *)mcTracks->UncheckedAt(recoTrack->GetMcId());
                    if (!mcTrack)
                        continue;
                    if (mcTrack->GetMotherId() != -1)
                        continue;
                    // PID-related cut
                    auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(mcTrack->GetPdg());
                    if (!particle)
                        continue;
                    float charge = 1. / 3. * particle->Charge();
                    if (charge <= 0)
                        continue;
                    if (phi < 0)
                    {
                        phi = phi + 2 * Pi;
                    }
                    /*
                    if (fabs(recoTrack->GetDCAx()) > DCAsigma)
                        continue; //трек не проходит по DCAx
                    if (fabs(recoTrack->GetDCAy()) > DCAsigma)
                        continue; //трек не проходит по DCAy
                    if (fabs(recoTrack->GetDCAz()) > DCAsigma)
                        continue; //трек не проходит по DCAz*/

                    if (recoTrack->GetNhits() < Nhits)
                        continue;

                    if (eta < eta_max && eta > eta_min && pt > pt_min && pt < pt_max)
                    {
                        Vobs[k] += cos(n * phi - n * PSIminus[k]);

                        for (int m = 0; m < NN; m++)
                        {
                            if (pt >= pt_bin[m] && pt < pt_bin[m + 1])
                            {
                                dVobs[k][m] += cos(n * phi - n * PSIminus[k]);
                                dMplus[k][m] += 1;
                            }
                        }
                    }

                    if (eta > -eta_max && eta < -eta_min && pt > pt_min && pt < pt_max)
                    {
                        Vobs[k] += cos(n * phi - n * PSIplus[k]);

                        for (int m = 0; m < NN; m++)
                        {
                            if (pt >= pt_bin[m] && pt < pt_bin[m + 1])
                            {
                                dVobs[k][m] += cos(n * phi - n * PSIplus[k]);
                                dMminus[k][m] += 1;
                            }
                        }
                    }
                }
            }
        }

        for (int k = 0; k < Nb; k++)
        {

            MQ2[k] = M[k] * (M[k] - 1);
            MQ4[k] = M[k] * (M[k] - 1) * (M[k] - 2) * (M[k] - 3);
            ZQQQ[k] = Q2[k] * Sopr(Q[k]) * Sopr(Q[k]);
            sv4[k] = ((Q[k] * Q[k] * Sopr(Q[k]) * Sopr(Q[k])).Re() + (Q2[k] * Sopr(Q2[k])).Re() - 2 * ((ZQQQ[k]).Re()) - 2 * 2 * (M[k] - 2) * Q[k].Rho2() + 2 * M[k] * (M[k] - 3)) / MQ4[k];
            sv2[k] = (Q[k].Rho2() - M[k]) / MQ2[k];

            if (Mplus[k] > min_mult && Mminus[k] > min_mult)
            {
                HVobs[k]->Fill(Vobs[k] / (Mplus[k] + Mminus[k]), Mplus[k] + Mminus[k]);
                HRES[k]->Fill(cos(n * PSIplus[k] - n * PSIminus[k]));
            }

            if (MQ4[k] == 0)
                continue;

            if (MQ2[k] != 0 && MQ4[k] != 0)
            {
                SV2[k]->Fill(sv2[k], MQ2[k]);
            }
            if (Mf[k] > min_mult)
            {
                HMC[k]->Fill(MCQ[k] / Mf[k], Mf[k]);
                hNpart->Fill(Mf[k]);
            }
            if (MQ4[k] != 0)
            {
                SV4[k]->Fill(sv4[k], MQ4[k]);
                SV2_SV4[k]->Fill(sv2[k] * sv4[k], MQ2[k] * MQ4[k]);
            }
            for (int s = 0; s < NN; s++)
            {
                Diffsv2[k][s] = (p[k][s] * Sopr(Q[k])).Re() - mq[k][s]; //cout <<" "<<p[k][s]<<" "<<Diffsv2[k][s]<< " "<<Sopr(Q[k])<<endl;
                DiffMQ2[k][s] = mp[k][s] * M[k] - mq[k][s];
                Diffsv2[k][s] = Diffsv2[k][s] / DiffMQ2[k][s];
                QMC[k][s] = QMC[k][s] / dMf[k][s];
                Diffsv4[k][s] = (p[k][s] * Q[k] * Sopr(Q[k]) * Sopr(Q[k])).Re() - (q2[k][s] * Sopr(Q[k]) * Sopr(Q[k])).Re() - (p[k][s] * Q[k] * Sopr(Q2[k])).Re() - 2 * M[k] * (p[k][s] * Sopr(Q[k])).Re() - 2 * mq[k][s] * Q[k].Rho2() + 7 * (q[k][s] * Sopr(Q[k])).Re() - (Q[k] * Sopr(q[k][s])).Re() + (q2[k][s] * Sopr(Q2[k])).Re() + 2 * (p[k][s] * Sopr(Q[k])).Re() + 2 * mq[k][s] * M[k] - 6 * mq[k][s];
                DiffMQ4[k][s] = (mp[k][s] * M[k] - 3 * mq[k][s]) * (M[k] - 1) * (M[k] - 2);
                Diffsv4[k][s] = Diffsv4[k][s] / DiffMQ4[k][s];

                if (Mplus[k] > min_mult && Mminus[k] > min_mult && (dMplus[k][s] + dMminus[k][s]) > 0)
                {
                    HDiffVobs[k][s]->Fill(dVobs[k][s] / (dMplus[k][s] + dMminus[k][s]), dMplus[k][s] + dMminus[k][s]);
                }
                if (dMf[k][s] != 0 && MQ4[k] != 0)
                {
                    DiffMC[k][s]->Fill(QMC[k][s], dMf[k][s]);
                }
                if (DiffMQ2[k][s] != 0 && DiffMQ4[k][s] != 0 && MQ2[k] != 0 && MQ4[k] != 0)
                {
                    DiffSV2[k][s]->Fill(Diffsv2[k][s], DiffMQ2[k][s]);
                    DiffSV4[k][s]->Fill(Diffsv4[k][s], DiffMQ4[k][s]);
                    SV2_DiffSV2[k][s]->Fill(Diffsv2[k][s] * sv2[k], DiffMQ2[k][s] * MQ2[k]);
                    SV2_DiffSV4[k][s]->Fill(Diffsv4[k][s] * sv2[k], DiffMQ4[k][s] * MQ2[k]);
                    SV4_DiffSV2[k][s]->Fill(Diffsv2[k][s] * sv4[k], DiffMQ2[k][s] * MQ4[k]);
                    SV4_DiffSV4[k][s]->Fill(Diffsv4[k][s] * sv4[k], DiffMQ4[k][s] * MQ4[k]);

                    DiffSV2_DiffSV4[k][s]->Fill(Diffsv4[k][s] * Diffsv2[k][s], DiffMQ4[k][s] * DiffMQ2[k][s]);
                }
            }
        }
    } // end event loop

    timer.Stop();
    timer.Print();
}

void SaveData(TString outputFileName)
{
    d_outfile = new TFile(outputFileName, "recreate");
    hNpart->Write();
    hBimp->Write();
    hPt->Write();
    hETA->Write();
    hdPHI->Write();
    for (int k = 0; k < Nb; k++)
    {
        SV2[k]->Write();
        HVobs[k]->Write();
        HRES[k]->Write();
        HQx[k]->Write();
        HQy[k]->Write();
        //HPHI[k]->Write();

        SV4[k]->Write();
        HMC[k]->Write();
        SV2_SV4[k]->Write();
        /*COSf1[k]->Write();
        COSf1f2[k]->Write();
        COSf1f2f3[k]->Write();
        SINf1[k]->Write();
        SINf1f2[k]->Write();
        SINf1f2f3[k]->Write();*/
        /*for (int g = 0; g < garm; g++)
        {
            HMeanCosP[k][g]->Write();
            HMeanSinP[k][g]->Write();
        }*/
        for (int s = 0; s < NN; s++)
        {
            DiffSV2[k][s]->Write();
            HDiffVobs[k][s]->Write();
            DiffSV4[k][s]->Write();
            DiffMC[k][s]->Write();
            SV2_DiffSV2[k][s]->Write();
            SV2_DiffSV4[k][s]->Write();
            SV4_DiffSV2[k][s]->Write();
            SV4_DiffSV4[k][s]->Write();
            DiffSV2_DiffSV4[k][s]->Write();
            /*COSp1[k][s]->Write();
            COSp1f2[k][s]->Write();
            COSp1f2mf3[k][s]->Write();
            COSp1mf2mf3[k][s]->Write();
            SINp1[k][s]->Write();
            SINp1f2[k][s]->Write();
            SINp1f2mf3[k][s]->Write();
            SINp1mf2mf3[k][s]->Write();
            hBin_Pt[k][s]->Write();*/
        }
    }
    d_outfile->Close();
}
