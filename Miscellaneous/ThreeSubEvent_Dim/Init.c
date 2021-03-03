#include "TComplex.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TROOT.h>
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLine.h>

static const int min_mult = 4;
static const double Pi = 3.1415927;
static const int n = 2;
static const int Nb = 9;
static const double binCentr[Nb] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
static const double binCentrEr[Nb] = {2.5, 2.5, 5., 5., 5., 5., 5., 5., 5.};

static const double binCent[Nb] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
static const double RMSbinCent[Nb] = {2.5, 2.5, 5., 5., 5., 5., 5., 5., 5.};

static const double pt_min = 0.2, pt_max = 3.;
static const double eta_min = 0.05, eta_max = 1.5;
//static const int NN = 12;
//static const double pt_bin[NN + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
//static const double ptbinEr[NN] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

static const int NN = 16;
static const double pt_bin[NN + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
static const double ptbinEr[NN] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,0.,0.,0.,0.};

static const float resTPCmin[Nb] = {0.922305, 0.913071, 0.870445, 0.81255, 0.736074, 0.628231, 0.531513, 0.401507, 0.332925};
static const float resTPCplus[Nb] = {0.931988, 0.907183, 0.876622, 0.812243, 0.737734, 0.655801, 0.536632, 0.408368, 0.278789};

Double_t MQ2[Nb], MQ4[Nb], M[Nb], sv2[Nb], sv4[Nb];
TComplex Q[Nb], Q2[Nb], ZQQQ[Nb];
TComplex p[Nb][NN], p2[Nb][NN];
TComplex q[Nb][NN], q2[Nb][NN];
Double_t mp[Nb][NN], mq[Nb][NN];
Double_t DiffMQ2[Nb][NN], DiffMQ4[Nb][NN], Diffsv2[Nb][NN], Diffsv4[Nb][NN];

Double_t PSIplus[Nb], PSIminus[Nb], PSI[Nb], Mplus[Nb], Mminus[Nb], Vobs[Nb], Res[Nb], Vobs3SUB[Nb];
Double_t PSIfhcal[Nb], Mfhcal[Nb];
TComplex Qplus[Nb], Qminus[Nb], Qfhcal[Nb];
Double_t dMplus[Nb][NN], dMminus[Nb][NN], dVobs[Nb][NN], dVobs3SUB[Nb][NN];

TH1F *SV2[Nb]; //2 частичная референсная корреляция
TH1F *SV4[Nb]; //4 частичная референсная корреляция
TH1F *COSf1[Nb];
TH1F *SINf1[Nb];
TH1F *COSf1f2[Nb];
TH1F *SINf1f2[Nb];
TH1F *COSf1f2f3[Nb];
TH1F *SINf1f2f3[Nb];
TH1F *hNpart = new TH1F("hNpart", "hNpart", 6000, 0, 6000);
TH1F *hBimp = new TH1F("hBimp", "hBimp", 1000, 0, 25);
TH1F *hPt = new TH1F("hPt", "hPt", 1000, -5, 5);
TH1F *hETA = new TH1F("hETA", "hETA", 1000, -8, 8);
TH1F *hdPHI = new TH1F("hdPHI", "dPHI", 1000, -6.5, 6.5);

TH1F *HPHI[Nb], *HRES[Nb], *HVobs[Nb], *HDiffVobs[Nb][NN], *HVobs3SUB[Nb], *HDiffVobs3SUB[Nb][NN];
TH1F *HRESminus_fhcal[Nb], *HRESfhcal_plus[Nb];
TH1F *SV2_SV4[Nb];
TH1F *DiffSV2[Nb][NN], *DiffSV4[Nb][NN];
TH1F *SV2_DiffSV2[Nb][NN], *SV2_DiffSV4[Nb][NN];
TH1F *SV4_DiffSV2[Nb][NN], *SV4_DiffSV4[Nb][NN];
TH1F *DiffSV2_DiffSV4[Nb][NN];
TH1F *hcounter[Nb][NN];
//////////////////////////////////////////////
TComplex NQ[2][Nb], Np[2][Nb][NN];
Double_t NM[2][Nb], Nmp[2][Nb][NN], Nsv2[Nb], NDiffsv2[Nb][NN];
TH1F *NSV2[Nb], *NDiffSV2[Nb][NN], *NSV2_DiffSV2[Nb][NN];
///////////////////////////////////////////////////
TH1F *COSp1[Nb][NN], *SINp1[Nb][NN];
TH1F *COSp1f2[Nb][NN], *SINp1f2[Nb][NN];
TH1F *COSp1f2mf3[Nb][NN], *SINp1f2mf3[Nb][NN];
TH1F *COSp1mf2mf3[Nb][NN], *SINp1mf2mf3[Nb][NN];

char str[200];
const char *STR;

void Book()
{

    for (int k = 0; k < Nb; k++)
    {
        sprintf(str, "%sCENT%d_%d", "sv2", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SV2[k] = new TH1F(STR, "sv2", 500, -0.5, 0.5);

        sprintf(str, "%sCENT%d_%d", "Nsv2", k * 10, (k + 1) * 10);
        STR = (char *)str;
        NSV2[k] = new TH1F(STR, "Nsv2", 500, -0.5, 0.5);

        sprintf(str, "%sCENT%d_%d", "sv4", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SV4[k] = new TH1F(STR, "sv4", 500, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "sv2_sv4", k * 10, (k + 1) * 10);
        STR = (char *)str;
        SV2_SV4[k] = new TH1F(STR, "sv2_sv4", 500, -0.1, 0.1);

        sprintf(str, "%sCENT%d_%d", "HRES", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HRES[k] = new TH1F(STR, "HRES", 200, -1, 1);

        HRESminus_fhcal[k] = new TH1F(Form("%sCENT%d_%d", "HRESmin_fh", k * 10, (k + 1) * 10), "HRESmin_fh", 200, -1, 1);
        HRESfhcal_plus[k] = new TH1F(Form("%sCENT%d_%d", "HRESfh_pl", k * 10, (k + 1) * 10), "HRESfh_pl", 200, -1, 1);

        sprintf(str, "%sCENT%d_%d", "PHI", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HPHI[k] = new TH1F(STR, "PHI", 100, -0.5, 0.5);

        sprintf(str, "%sCENT%d_%d", "Vobs", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HVobs[k] = new TH1F(STR, "Vobs", 100, -1, 1);

        HVobs3SUB[k] = new TH1F(Form("%sCENT%d_%d", "Vobs3", k * 10, (k + 1) * 10), "Vobs3", 100, -1, 1);

        SV2[k]->StatOverflows(kTRUE);
        NSV2[k]->StatOverflows(kTRUE);
        SV4[k]->StatOverflows(kTRUE);
        HPHI[k]->StatOverflows(kTRUE);

        for (int m = 0; m < NN; m++)
        {
            sprintf(str, "%s%d_CENT%d_%d", "hcounter", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            hcounter[k][m] = new TH1F(STR, "hcounter", 10, 0, 2);

            sprintf(str, "%s%d_CENT%d_%d", "sv2Diff", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            DiffSV2[k][m] = new TH1F(STR, "Diffsv2", 500, -0.5, 0.5);

            sprintf(str, "%s%d_CENT%d_%d", "Nsv2Diff", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            NDiffSV2[k][m] = new TH1F(STR, "NDiffsv2", 500, -0.5, 0.5);

            sprintf(str, "%s%d_CENT%d_%d", "sv4Diff", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            DiffSV4[k][m] = new TH1F(STR, "Diffsv4", 500, -0.2, 0.2);

            sprintf(str, "%s%d_CENT%d_%d", "SV2_DiffSV2", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            SV2_DiffSV2[k][m] = new TH1F(STR, "sv2sv2", 500, -0.1, 0.1);

            sprintf(str, "%s%d_CENT%d_%d", "NSV2_DiffSV2", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            NSV2_DiffSV2[k][m] = new TH1F(STR, "Nsv2sv2", 500, -0.1, 0.1);

            sprintf(str, "%s%d_CENT%d_%d", "SV2_DiffSV4", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            SV2_DiffSV4[k][m] = new TH1F(STR, "sv2sv4", 500, -0.1, 0.1);

            sprintf(str, "%s%d_CENT%d_%d", "SV4_DiffSV2", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            SV4_DiffSV2[k][m] = new TH1F(STR, "sv4sv2", 500, -0.1, 0.1);

            sprintf(str, "%s%d_CENT%d_%d", "SV4_DiffSV4", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            SV4_DiffSV4[k][m] = new TH1F(STR, "sv4sv4", 500, -0.1, 0.1);

            sprintf(str, "%s%d_CENT%d_%d", "DiffSV2_DiffSV4", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            DiffSV2_DiffSV4[k][m] = new TH1F(STR, "diffsv2sv4", 500, -0.1, 0.1);

            sprintf(str, "%s%d_CENT%d_%d", "diffVobs", m, k * 10, (k + 1) * 10);
            STR = (char *)str;
            HDiffVobs[k][m] = new TH1F(STR, "Diffvobs", 200, -1, 1);

            HDiffVobs3SUB[k][m] = new TH1F(Form("%s%d_CENT%d_%d", "diffVobs3", m, k * 10, (k + 1) * 10), "Diffvobs3", 200, -1, 1);

            HVobs[k]->StatOverflows(kTRUE);
            DiffSV2[k][m]->StatOverflows(kTRUE);
            NDiffSV2[k][m]->StatOverflows(kTRUE);
            SV2_DiffSV2[k][m]->StatOverflows(kTRUE);
            NSV2_DiffSV2[k][m]->StatOverflows(kTRUE);
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

int GetBinPt(double pt)
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

int GetBinb(double bimp)
{
    // Hard coded centrality defenition
    // based on the impact parameter
    int fcent;
    if (bimp < 2.91)
        fcent = 0; // 0-5%
    else if (bimp < 4.18)
        fcent = 1; // 5-10%
    else if (bimp < 6.01)
        fcent = 2; //10-20%
    else if (bimp < 7.37)
        fcent = 3; //20-30%
    else if (bimp < 8.52)
        fcent = 4; //30-40%
    else if (bimp < 9.57)
        fcent = 5; //40-50%
    else if (bimp < 10.55)
        fcent = 6; //50-60%
    else if (bimp < 11.46)
        fcent = 7.; // 60-70%
    else if (bimp < 12.31)
        fcent = 8; // 70-80%
    else
        fcent = -1;

    if (fcent != -1)
        return fcent;
    else
        return -1;
}

void ClearVar(int k)
{
    Vobs[k] = 0;
    Vobs3SUB[k] = 0;
    Mplus[k] = 0;
    Mminus[k] = 0;
    Mfhcal[k] = 0;
    Qplus[k] = TComplex(0, 0);
    Qminus[k] = TComplex(0, 0);
    Qfhcal[k] = TComplex(0, 0);

    Q[k] = TComplex(0, 0);
    NQ[0][k] = TComplex(0, 0);
    NQ[1][k] = TComplex(0, 0);
    Q2[k] = TComplex(0, 0);
    MQ2[k] = 0;

    MQ4[k] = 0;
    M[k] = 0;

    NM[0][k] = 0;
    NM[1][k] = 0;

    for (int s = 0; s < NN; s++)
    {
        dVobs[k][s] = 0;
        dVobs3SUB[k][s] = 0;
        dMplus[k][s] = 0;
        dMminus[k][s] = 0;

        p[k][s] = TComplex(0, 0);
        Np[0][k][s] = TComplex(0, 0);
        Np[1][k][s] = TComplex(0, 0);
        p2[k][s] = TComplex(0, 0);
        mp[k][s] = 0;
        Nmp[0][k][s] = 0;
        Nmp[1][k][s] = 0;
        q[k][s] = TComplex(0, 0);
        q2[k][s] = TComplex(0, 0);
        mq[k][s] = 0;
    }
}

void LoopVar1(int k, double Vpt, double Veta, double Vphi)
{
    Double_t cos_phi, sin_phi;
    cos_phi = TMath::Cos(n * (Vphi));
    sin_phi = TMath::Sin(n * (Vphi));

    int bin_pt = GetBinPt(Vpt);

    if (Veta < -eta_min)
    {
        Qminus[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        Mminus[k] += 1;
        NQ[0][k] += TComplex(cos_phi, sin_phi);
        NM[0][k] += 1;
        if (bin_pt != -1)
        {
            Nmp[0][k][bin_pt] += 1;
            Np[0][k][bin_pt] += TComplex(cos_phi, sin_phi);
        }
    }
    if (Veta > eta_min)
    {
        Qplus[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        Mplus[k] += 1;
        NQ[1][k] += TComplex(cos_phi, sin_phi);
        NM[1][k] += 1;
        if (bin_pt != -1)
        {
            Nmp[1][k][bin_pt] += 1;
            Np[1][k][bin_pt] += TComplex(cos_phi, sin_phi);
        }
    }

    //hETA->Fill(eta);
    //hdPHI->Fill(phi);
    //hPt->Fill(pt);
}

void LoopVarFHCal(int k, double Vpt, double Veta, double Vphi)
{
    Double_t cos_phi, sin_phi;
    cos_phi = TMath::Cos(n * (Vphi));
    sin_phi = TMath::Sin(n * (Vphi));

    if (Veta < -eta_max || Veta > eta_max)
    {
        Qfhcal[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        Mfhcal[k] += 1;
    }
}

void LoopVarEP(int k, double Vpt, double Veta, double Vphi)
{
    int bin_pt = GetBinPt(Vpt);
    PSIplus[k] = TMath::ATan2(Qplus[k].Im(), Qplus[k].Re()) / n;
    PSIminus[k] = TMath::ATan2(Qminus[k].Im(), Qminus[k].Re()) / n;

    if (Veta > eta_min)
    {
        Vobs[k] += cos(n * (Vphi - PSIminus[k]));
        Vobs3SUB[k] += cos(n * (Vphi - PSIminus[k])) / resTPCmin[k];
        if (bin_pt != -1)
        {
            dVobs[k][bin_pt] += cos(n * (Vphi - PSIminus[k]));
            dVobs3SUB[k][bin_pt] += cos(n * (Vphi - PSIminus[k])) / resTPCmin[k];
            dMplus[k][bin_pt] += 1;
        }
    }

    if (Veta < -eta_min)
    {
        Vobs[k] += cos(n * (Vphi - PSIplus[k]));
        Vobs3SUB[k] += cos(n * (Vphi - PSIplus[k])) / resTPCplus[k];
        if (bin_pt != -1)
        {
            dVobs[k][bin_pt] += cos(n * (Vphi - PSIplus[k]));
            dVobs3SUB[k][bin_pt] += cos(n * (Vphi - PSIplus[k])) / resTPCplus[k];
            dMminus[k][bin_pt] += 1;
        }
    }
}

void LoopVar2(int k, double Vpt, double Veta, double Vphi)
{
    Double_t cos_phi, sin_phi, cos_2phi, sin_2phi;

    int bin_pt = GetBinPt(Vpt);

    cos_phi = TMath::Cos(n * (Vphi));
    sin_phi = TMath::Sin(n * (Vphi));
    cos_2phi = TMath::Cos(2 * n * (Vphi));
    sin_2phi = TMath::Sin(2 * n * (Vphi));

    Q[k] += TComplex(cos_phi, sin_phi);
    Q2[k] += TComplex(cos_2phi, sin_2phi);
    M[k] += 1;

    if (bin_pt != -1)
    {
        mp[k][bin_pt] += 1;
        p2[k][bin_pt] += TComplex(cos_2phi, sin_2phi);
        p[k][bin_pt] += TComplex(cos_phi, sin_phi);
        mq[k][bin_pt] += 1;
        q2[k][bin_pt] += TComplex(cos_2phi, sin_2phi);
        q[k][bin_pt] += TComplex(cos_phi, sin_phi);
    }
}

void FiilHist(int k)
{

    MQ2[k] = M[k] * (M[k] - 1);
    MQ4[k] = M[k] * (M[k] - 1) * (M[k] - 2) * (M[k] - 3);
    sv2[k] = (Q[k].Rho2() - M[k]) / MQ2[k];
    ZQQQ[k] = Q2[k] * Sopr(Q[k]) * Sopr(Q[k]);
    sv4[k] = ((Q[k] * Q[k] * Sopr(Q[k]) * Sopr(Q[k])).Re() + (Q2[k] * Sopr(Q2[k])).Re() - 2 * ((ZQQQ[k]).Re()) - 2 * 2 * (M[k] - 2) * Q[k].Rho2() + 2 * M[k] * (M[k] - 3)) / MQ4[k];
    Nsv2[k] = (NQ[0][k] * Sopr(NQ[1][k])).Re() / (NM[0][k] * NM[1][k]);

    if (NM[0][k] * NM[1][k] != 0)
    {
        NSV2[k]->Fill(Nsv2[k], NM[0][k] * NM[1][k]);
    }

    if (MQ4[k] != 0)
    {
        SV2[k]->Fill(sv2[k], MQ2[k]);
        SV4[k]->Fill(sv4[k], MQ4[k]);
        SV2_SV4[k]->Fill(sv2[k] * sv4[k], MQ2[k] * MQ4[k]);
    }

    if (Mplus[k] > min_mult && Mminus[k] > min_mult)
    {
        HVobs[k]->Fill(Vobs[k] / (Mplus[k] + Mminus[k]), Mplus[k] + Mminus[k]);
        HRES[k]->Fill(cos(n * PSIplus[k] - n * PSIminus[k]));
        if (Mfhcal[k] > min_mult)
        {
            PSIfhcal[k] = TMath::ATan2(Qfhcal[k].Im(), Qfhcal[k].Re()) / n;
            HRESminus_fhcal[k]->Fill(cos(n * PSIminus[k] - n * PSIfhcal[k]));
            HRESfhcal_plus[k]->Fill(cos(n * PSIfhcal[k] - n * PSIplus[k]));
            HVobs3SUB[k]->Fill(Vobs3SUB[k] / (Mplus[k] + Mminus[k]), Mplus[k] + Mminus[k]);
        }
    }

    for (int s = 0; s < NN; s++)
    {
        DiffMQ2[k][s] = mp[k][s] * M[k] - mq[k][s];
        Diffsv2[k][s] = ((p[k][s] * Sopr(Q[k])).Re() - mq[k][s]) / DiffMQ2[k][s];

        Diffsv4[k][s] = (p[k][s] * Q[k] * Sopr(Q[k]) * Sopr(Q[k])).Re() - (q2[k][s] * Sopr(Q[k]) * Sopr(Q[k])).Re() - (p[k][s] * Q[k] * Sopr(Q2[k])).Re() - 2 * M[k] * (p[k][s] * Sopr(Q[k])).Re() - 2 * mq[k][s] * Q[k].Rho2() + 7 * (q[k][s] * Sopr(Q[k])).Re() - (Q[k] * Sopr(q[k][s])).Re() + (q2[k][s] * Sopr(Q2[k])).Re() + 2 * (p[k][s] * Sopr(Q[k])).Re() + 2 * mq[k][s] * M[k] - 6 * mq[k][s];
        DiffMQ4[k][s] = (mp[k][s] * M[k] - 3 * mq[k][s]) * (M[k] - 1) * (M[k] - 2);
        Diffsv4[k][s] = Diffsv4[k][s] / DiffMQ4[k][s];

        if (DiffMQ4[k][s] != 0 && MQ4[k] != 0)
        {
            DiffSV2[k][s]->Fill(Diffsv2[k][s], DiffMQ2[k][s]);
            SV2_DiffSV2[k][s]->Fill(Diffsv2[k][s] * sv2[k], DiffMQ2[k][s] * MQ2[k]);
            DiffSV4[k][s]->Fill(Diffsv4[k][s], DiffMQ4[k][s]);
            SV2_DiffSV4[k][s]->Fill(Diffsv4[k][s] * sv2[k], DiffMQ4[k][s] * MQ2[k]);
            SV4_DiffSV2[k][s]->Fill(Diffsv2[k][s] * sv4[k], DiffMQ2[k][s] * MQ4[k]);
            SV4_DiffSV4[k][s]->Fill(Diffsv4[k][s] * sv4[k], DiffMQ4[k][s] * MQ4[k]);
            DiffSV2_DiffSV4[k][s]->Fill(Diffsv4[k][s] * Diffsv2[k][s], DiffMQ4[k][s] * DiffMQ2[k][s]);
            hcounter[k][s]->Fill(1, mp[k][s]);
        }

        NDiffsv2[k][s] = (Np[0][k][s] * Sopr(NQ[1][k])).Re() / (Nmp[0][k][s] * NM[1][k]);
        if (Nmp[0][k][s] * NM[1][k] != 0)
        {
            NDiffSV2[k][s]->Fill(NDiffsv2[k][s], Nmp[0][k][s] * NM[1][k]);
            NSV2_DiffSV2[k][s]->Fill(NDiffsv2[k][s] * Nsv2[k], Nmp[0][k][s] * NM[1][k] * NM[0][k] * NM[1][k]);
        }

        NDiffsv2[k][s] = (Np[1][k][s] * Sopr(NQ[0][k])).Re() / (Nmp[1][k][s] * NM[0][k]);
        if (Nmp[1][k][s] * NM[0][k] != 0)
        {
            NDiffSV2[k][s]->Fill(NDiffsv2[k][s], Nmp[1][k][s] * NM[0][k]);
            NSV2_DiffSV2[k][s]->Fill(NDiffsv2[k][s] * Nsv2[k], Nmp[1][k][s] * NM[0][k] * NM[0][k] * NM[1][k]);
        }

        if (Mplus[k] > min_mult && Mminus[k] > min_mult && (dMplus[k][s] + dMminus[k][s]) > 0)
        {
            HDiffVobs[k][s]->Fill(dVobs[k][s] / (dMplus[k][s] + dMminus[k][s]), dMplus[k][s] + dMminus[k][s]);
            if (Mfhcal[k] > min_mult)
            {
                HDiffVobs3SUB[k][s]->Fill(dVobs3SUB[k][s] / (dMplus[k][s] + dMminus[k][s]), dMplus[k][s] + dMminus[k][s]);
            }
        }
    }
}

void SaveData(const char *outfile)
{
    TFile *d_outfile = new TFile(outfile, "recreate");
    hPt->Write();
    hNpart->Write();
    hdPHI->Write();
    hETA->Write();
    for (int k = 0; k < Nb; k++)
    {
        SV2[k]->Write();
        NSV2[k]->Write();
        SV4[k]->Write();
        SV2_SV4[k]->Write();
        HVobs[k]->Write();HVobs3SUB[k]->Write();
        HRES[k]->Write();
        HRESminus_fhcal[k]->Write();
        HRESfhcal_plus[k]->Write();
        for (int s = 0; s < NN; s++)
        {
            hcounter[k][s]->Write();
            DiffSV2[k][s]->Write();
            NDiffSV2[k][s]->Write();
            HDiffVobs[k][s]->Write();HDiffVobs3SUB[k][s]->Write();
            DiffSV4[k][s]->Write();

            SV2_DiffSV2[k][s]->Write();
            NSV2_DiffSV2[k][s]->Write();
            SV2_DiffSV4[k][s]->Write();
            SV4_DiffSV2[k][s]->Write();
            SV4_DiffSV4[k][s]->Write();
            DiffSV2_DiffSV4[k][s]->Write();
        }
    }
    d_outfile->Close();
}
