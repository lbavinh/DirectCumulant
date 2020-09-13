// Do not forget to source setPicoDst.sh script

#include <iostream>
#include <TDatabasePDG.h>
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TROOT.h>

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
float pt_min = 0.2, pt_max = 3., eta_min = 0.05, eta_max = 1.5;
int Nhits = 32;
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

int GetBinPt(float pt)
{
    int fPt = -1;
    for (int i = 0; i < NN; i++)
    {
        if (pt_bin[i] <= pt && pt < pt_bin[i + 1])
        {
            fPt = i;
        }
    }
    return fPt;
}

int GetBinb(float biMp)
{
    int fcent = -1;

    for (int i = 0; i < Nb; i++)
    {
        if (b_bin[i] <= biMp && biMp < b_bin[i + 1])
        {
            fcent = i;
        }
    }
    return fcent;
}

void readPicoDst(TString inputFileName)
{
    TStopwatch timer;
    timer.Start();

    int t = 0, bin_b, bin_pt;
    float Ntree = 0;
    float Mf[Nb], dMf[Nb][NN], eta, pt, phi, rp, mcevent_fB;

    // Configure input information
    TChain *chain = new TChain("picodst");
    chain->Add(inputFileName.Data());

    PicoDstMCEvent *mcEvent = nullptr;
    TClonesArray *recoTracks = nullptr;
    TClonesArray *mcTracks = nullptr;

    chain->SetBranchAddress("mcevent.", &mcEvent);
    chain->SetBranchAddress("recotracks", &recoTracks);
    chain->SetBranchAddress("mctracks", &mcTracks);

    // Start event loop
    Long64_t n_entries = chain->GetEntries();
    //Long64_t n_entries = chain->GetEntriesFast();
    for (Long64_t iEv = 0; iEv < n_entries; iEv++)
    {
        if (iEv % 1000 == 0)
            std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
        chain->GetEntry(iEv);

        //Обнуление переменных
        for (int k = 0; k < Nb; k++)
        {
            MQ2[k] = 0;
            Vobs[k] = 0;
            Mplus[k] = 0;
            Mminus[k] = 0;
            MQ4[k] = 0;
            M[k] = 0;

            Qplus[k] = TComplex(0, 0);
            Qminus[k] = TComplex(0, 0);
            Q[k] = TComplex(0, 0);
            Q2[k] = TComplex(0, 0);
            ZQQQ[k] = TComplex(0, 0);
            Res[k] = 0;
            for (int s = 0; s < NN; s++)
            {
                dVobs[k][s] = 0;
                dMplus[k][s] = 0;
                dMminus[k][s] = 0;

                p[k][s] = TComplex(0, 0);
                p2[k][s] = TComplex(0, 0);
                mp[k][s] = 0;
                q[k][s] = TComplex(0, 0);
                q2[k][s] = TComplex(0, 0);
                mq[k][s] = 0;
            }
        }

        mcevent_fB = mcEvent->GetB();
        Int_t reco_mult = recoTracks->GetEntriesFast();

        // Read Reco tracks
        bin_b = GetBinb(mcevent_fB);

        if (bin_b == -1)
            continue;

        for (int i = 0; i < reco_mult; i++)
        {
            auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(i);
            if (!recoTrack)
                continue;
            pt = recoTrack->GetPt();
            bin_pt = GetBinPt(pt);
            if (pt < pt_min || pt > pt_max)
                continue;
            eta = recoTrack->GetEta();
            if (fabs(eta) < eta_min || fabs(eta) > eta_max)
                continue;
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
            if (charge == 0)
                continue;

            if (recoTrack->GetNhits() < Nhits)
                continue;

            if (eta < 0)
            {
                Qminus[bin_b] += TComplex(pt * cos(n * (phi)), pt * sin(n * (phi)));
                Mminus[bin_b] += 1;

                if (charge > 0 && bin_pt != -1)
                {
                    mp[bin_b][bin_pt] += 1;
                    p2[bin_b][bin_pt] += TComplex(cos(2 * n * (phi)), sin(2 * n * (phi)));
                    p[bin_b][bin_pt] += TComplex(cos(n * (phi)), sin(n * (phi)));
                }
            }
            if (eta > 0)
            {
                Qplus[bin_b] += TComplex(pt * cos(n * (phi)), pt * sin(n * (phi)));
                Mplus[bin_b] += 1;

                if (charge > 0 && bin_pt != -1)
                {
                    Q[bin_b] += TComplex(cos(n * (phi)), sin(n * (phi)));
                    Q2[bin_b] += TComplex(cos(2 * n * (phi)), sin(2 * n * (phi)));
                    M[bin_b] += 1;
                }
            }
        }

        MQ2[bin_b] = M[bin_b] * (M[bin_b] - 1);
        MQ4[bin_b] = M[bin_b] * (M[bin_b] - 1) * (M[bin_b] - 2) * (M[bin_b] - 3);
        ZQQQ[bin_b] = Q2[bin_b] * Sopr(Q[bin_b]) * Sopr(Q[bin_b]);
        sv4[bin_b] = ((Q[bin_b] * Q[bin_b] * Sopr(Q[bin_b]) * Sopr(Q[bin_b])).Re() + (Q2[bin_b] * Sopr(Q2[bin_b])).Re() - 2 * ((ZQQQ[bin_b]).Re()) - 2 * 2 * (M[bin_b] - 2) * Q[bin_b].Rho2() + 2 * M[bin_b] * (M[bin_b] - 3)) / MQ4[bin_b];
        sv2[bin_b] = (Q[bin_b].Rho2() - M[bin_b]) / MQ2[bin_b];

        if (MQ2[bin_b] != 0 && MQ4[bin_b] != 0)
        {
            SV2[bin_b]->Fill(sv2[bin_b], MQ2[bin_b]);
            SV4[bin_b]->Fill(sv4[bin_b], MQ4[bin_b]);
            SV2_SV4[bin_b]->Fill(sv2[bin_b] * sv4[bin_b], MQ2[bin_b] * MQ4[bin_b]);

            for (int s = 0; s < NN; s++)
            {
                Diffsv2[bin_b][s] = (p[bin_b][s] * Sopr(Q[bin_b])).Re() - mq[bin_b][s]; //cout <<" "<<p[bin_b][s]<<" "<<Diffsv2[bin_b][s]<< " "<<Sopr(Q[bin_b])<<endl;
                DiffMQ2[bin_b][s] = mp[bin_b][s] * M[bin_b] - mq[bin_b][s];
                Diffsv2[bin_b][s] = Diffsv2[bin_b][s] / DiffMQ2[bin_b][s];
                QMC[bin_b][s] = QMC[bin_b][s] / dMf[bin_b][s];
                Diffsv4[bin_b][s] = (p[bin_b][s] * Q[bin_b] * Sopr(Q[bin_b]) * Sopr(Q[bin_b])).Re() - (q2[bin_b][s] * Sopr(Q[bin_b]) * Sopr(Q[bin_b])).Re() - (p[bin_b][s] * Q[bin_b] * Sopr(Q2[bin_b])).Re() - 2 * M[bin_b] * (p[bin_b][s] * Sopr(Q[bin_b])).Re() - 2 * mq[bin_b][s] * Q[bin_b].Rho2() + 7 * (q[bin_b][s] * Sopr(Q[bin_b])).Re() - (Q[bin_b] * Sopr(q[bin_b][s])).Re() + (q2[bin_b][s] * Sopr(Q2[bin_b])).Re() + 2 * (p[bin_b][s] * Sopr(Q[bin_b])).Re() + 2 * mq[bin_b][s] * M[bin_b] - 6 * mq[bin_b][s];
                DiffMQ4[bin_b][s] = (mp[bin_b][s] * M[bin_b] - 3 * mq[bin_b][s]) * (M[bin_b] - 1) * (M[bin_b] - 2);
                Diffsv4[bin_b][s] = Diffsv4[bin_b][s] / DiffMQ4[bin_b][s];

                if (DiffMQ4[bin_b][s] != 0 && DiffMQ2[bin_b][s] != 0 && MQ4[bin_b] != 0)
                {

                    DiffSV2[bin_b][s]->Fill(Diffsv2[bin_b][s], DiffMQ2[bin_b][s]);
                    SV2_DiffSV2[bin_b][s]->Fill(Diffsv2[bin_b][s] * sv2[bin_b], DiffMQ2[bin_b][s] * MQ2[bin_b]);

                    DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s], DiffMQ4[bin_b][s]);

                    SV2_DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s] * sv2[bin_b], DiffMQ4[bin_b][s] * MQ2[bin_b]);
                    SV4_DiffSV2[bin_b][s]->Fill(Diffsv2[bin_b][s] * sv4[bin_b], DiffMQ2[bin_b][s] * MQ4[bin_b]);
                    SV4_DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s] * sv4[bin_b], DiffMQ4[bin_b][s] * MQ4[bin_b]);

                    DiffSV2_DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s] * Diffsv2[bin_b][s], DiffMQ4[bin_b][s] * DiffMQ2[bin_b][s]);
                }
            }
        }

        PSIplus[bin_b] = TMath::ATan2(Qplus[bin_b].Im(), Qplus[bin_b].Re()) / n;
        PSIminus[bin_b] = TMath::ATan2(Qminus[bin_b].Im(), Qminus[bin_b].Re()) / n;

        //Обнуление переменных

        MQ2[bin_b] = 0;
        Vobs[bin_b] = 0;
        //Mplus[bin_b] = 0;
        //Mminus[bin_b] = 0;
        MQ4[bin_b] = 0;
        M[bin_b] = 0;

        Qplus[bin_b] = TComplex(0, 0);
        Qminus[bin_b] = TComplex(0, 0);
        Q[bin_b] = TComplex(0, 0);
        Q2[bin_b] = TComplex(0, 0);
        ZQQQ[bin_b] = TComplex(0, 0);

        for (int s = 0; s < NN; s++)
        {
            dVobs[bin_b][s] = 0;
            dMplus[bin_b][s] = 0;
            dMminus[bin_b][s] = 0;

            p[bin_b][s] = TComplex(0, 0);
            p2[bin_b][s] = TComplex(0, 0);
            mp[bin_b][s] = 0;
            q[bin_b][s] = TComplex(0, 0);
            q2[bin_b][s] = TComplex(0, 0);
            mq[bin_b][s] = 0;
        }

        for (int i = 0; i < reco_mult; i++)
        {
            auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(i);
            if (!recoTrack)
                continue;
            pt = recoTrack->GetPt();
            bin_pt = GetBinPt(pt);
            if (pt < pt_min || pt > pt_max)
                continue;
            eta = recoTrack->GetEta();
            if (fabs(eta) < eta_min || fabs(eta) > eta_max)
                continue;
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
            if (recoTrack->GetNhits() < Nhits)
                continue;

            if (eta > 0)
            {
                Vobs[bin_b] += cos(n * phi - n * PSIminus[bin_b]);
                if (bin_pt != -1)
                {
                    dVobs[bin_b][bin_pt] += cos(n * phi - n * PSIminus[bin_b]);
                    dMplus[bin_b][bin_pt] += 1;

                    mp[bin_b][bin_pt] += 1;
                    p2[bin_b][bin_pt] += TComplex(cos(2 * n * (phi)), sin(2 * n * (phi)));
                    p[bin_b][bin_pt] += TComplex(cos(n * (phi)), sin(n * (phi)));
                }
            }

            if (eta < 0)
            {
                Vobs[bin_b] += cos(n * phi - n * PSIplus[bin_b]);

                Q[bin_b] += TComplex(cos(n * (phi)), sin(n * (phi)));
                Q2[bin_b] += TComplex(cos(2 * n * (phi)), sin(2 * n * (phi)));
                M[bin_b] += 1;
                if (bin_pt != -1)
                {
                    dVobs[bin_b][bin_pt] += cos(n * phi - n * PSIplus[bin_b]);
                    dMminus[bin_b][bin_pt] += 1;
                }
            }
        }

        if (Mplus[bin_b] > min_mult && Mminus[bin_b] > min_mult)
        {
            HVobs[bin_b]->Fill(Vobs[bin_b] / (Mplus[bin_b] + Mminus[bin_b]), Mplus[bin_b] + Mminus[bin_b]);
            HRES[bin_b]->Fill(cos(n * PSIplus[bin_b] - n * PSIminus[bin_b]));

            for (int s = 0; s < NN; s++)
            {
                if ((dMplus[bin_b][s] + dMminus[bin_b][s]) > 0)
                {
                    HDiffVobs[bin_b][s]->Fill(dVobs[bin_b][s] / (dMplus[bin_b][s] + dMminus[bin_b][s]), dMplus[bin_b][s] + dMminus[bin_b][s]);
                }
            }
        }
        MQ2[bin_b] = M[bin_b] * (M[bin_b] - 1);
        MQ4[bin_b] = M[bin_b] * (M[bin_b] - 1) * (M[bin_b] - 2) * (M[bin_b] - 3);
        ZQQQ[bin_b] = Q2[bin_b] * Sopr(Q[bin_b]) * Sopr(Q[bin_b]);
        sv4[bin_b] = ((Q[bin_b] * Q[bin_b] * Sopr(Q[bin_b]) * Sopr(Q[bin_b])).Re() + (Q2[bin_b] * Sopr(Q2[bin_b])).Re() - 2 * ((ZQQQ[bin_b]).Re()) - 2 * 2 * (M[bin_b] - 2) * Q[bin_b].Rho2() + 2 * M[bin_b] * (M[bin_b] - 3)) / MQ4[bin_b];
        sv2[bin_b] = (Q[bin_b].Rho2() - M[bin_b]) / MQ2[bin_b];

        if (MQ2[bin_b] != 0 && MQ4[bin_b] != 0)
        {
            SV2[bin_b]->Fill(sv2[bin_b], MQ2[bin_b]);
            SV4[bin_b]->Fill(sv4[bin_b], MQ4[bin_b]);
            SV2_SV4[bin_b]->Fill(sv2[bin_b] * sv4[bin_b], MQ2[bin_b] * MQ4[bin_b]);

            for (int s = 0; s < NN; s++)
            {
                Diffsv2[bin_b][s] = (p[bin_b][s] * Sopr(Q[bin_b])).Re() - mq[bin_b][s]; //cout <<" "<<p[bin_b][s]<<" "<<Diffsv2[bin_b][s]<< " "<<Sopr(Q[bin_b])<<endl;
                DiffMQ2[bin_b][s] = mp[bin_b][s] * M[bin_b] - mq[bin_b][s];
                Diffsv2[bin_b][s] = Diffsv2[bin_b][s] / DiffMQ2[bin_b][s];
                QMC[bin_b][s] = QMC[bin_b][s] / dMf[bin_b][s];
                Diffsv4[bin_b][s] = (p[bin_b][s] * Q[bin_b] * Sopr(Q[bin_b]) * Sopr(Q[bin_b])).Re() - (q2[bin_b][s] * Sopr(Q[bin_b]) * Sopr(Q[bin_b])).Re() - (p[bin_b][s] * Q[bin_b] * Sopr(Q2[bin_b])).Re() - 2 * M[bin_b] * (p[bin_b][s] * Sopr(Q[bin_b])).Re() - 2 * mq[bin_b][s] * Q[bin_b].Rho2() + 7 * (q[bin_b][s] * Sopr(Q[bin_b])).Re() - (Q[bin_b] * Sopr(q[bin_b][s])).Re() + (q2[bin_b][s] * Sopr(Q2[bin_b])).Re() + 2 * (p[bin_b][s] * Sopr(Q[bin_b])).Re() + 2 * mq[bin_b][s] * M[bin_b] - 6 * mq[bin_b][s];
                DiffMQ4[bin_b][s] = (mp[bin_b][s] * M[bin_b] - 3 * mq[bin_b][s]) * (M[bin_b] - 1) * (M[bin_b] - 2);
                Diffsv4[bin_b][s] = Diffsv4[bin_b][s] / DiffMQ4[bin_b][s];

                if (DiffMQ4[bin_b][s] != 0 && DiffMQ2[bin_b][s] != 0)
                {
                    DiffSV2[bin_b][s]->Fill(Diffsv2[bin_b][s], DiffMQ2[bin_b][s]);
                    SV2_DiffSV2[bin_b][s]->Fill(Diffsv2[bin_b][s] * sv2[bin_b], DiffMQ2[bin_b][s] * MQ2[bin_b]);

                    DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s], DiffMQ4[bin_b][s]);

                    SV2_DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s] * sv2[bin_b], DiffMQ4[bin_b][s] * MQ2[bin_b]);
                    SV4_DiffSV2[bin_b][s]->Fill(Diffsv2[bin_b][s] * sv4[bin_b], DiffMQ2[bin_b][s] * MQ4[bin_b]);
                    SV4_DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s] * sv4[bin_b], DiffMQ4[bin_b][s] * MQ4[bin_b]);

                    DiffSV2_DiffSV4[bin_b][s]->Fill(Diffsv4[bin_b][s] * Diffsv2[bin_b][s], DiffMQ4[bin_b][s] * DiffMQ2[bin_b][s]);
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

    for (int k = 0; k < Nb; k++)
    {
        SV2[k]->Write();
        HVobs[k]->Write();
        HRES[k]->Write();

        SV4[k]->Write();
        SV2_SV4[k]->Write();

        for (int s = 0; s < NN; s++)
        {
            DiffSV2[k][s]->Write();
            HDiffVobs[k][s]->Write();
            DiffSV4[k][s]->Write();
            SV2_DiffSV2[k][s]->Write();
            SV2_DiffSV4[k][s]->Write();
            SV4_DiffSV2[k][s]->Write();
            SV4_DiffSV4[k][s]->Write();
            DiffSV2_DiffSV4[k][s]->Write();
        }
    }
    d_outfile->Close();
}
