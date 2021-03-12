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

static const int min_mult = 2;
static const double Pi = 3.1415927;
static const int n = 1, m = 1;
static const int Nb = 9;
static const double binCentr[Nb] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
static const double binCentrEr[Nb] = {2.5, 2.5, 5., 5., 5., 5., 5., 5., 5.};

static const double binCent[Nb] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
static const double RMSbinCent[Nb] = {2.5, 2.5, 5., 5., 5., 5., 5., 5., 5.};

static const double pt_min = 0.2, pt_max = 0.8;
static const double eta_min = 0.5, eta_max = 1.5;
static const double etafh_min = 2., etafh_max = 5.;
//static const int NN = 12;
//static const double pt_bin[NN + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
//static const double ptbinEr[NN] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

static const int NN = 16;
static const double pt_bin[NN + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
static const double ptbinEr[NN] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

/*static const int NN = 14;
static const double pt_bin[NN + 1] = {-1.5, -1.3, -1.1, -0.9, -0.7, -0.5, -0.3, 0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5};
static const double ptbinEr[NN] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
*/

//Toy
//static const float resTPCmin[Nb]={0.55309,0.677011,0.779746,0.82809,0.820695,0.780637,0.710066,0.582216,0.449645};
//static const float resTPCplus[Nb]={0.534663,0.676831,0.780566,0.826048,0.825491,0.78709,0.703754,0.597282,0.445949};

static const float resTPCmin[Nb] = {0.102388, 0.154468, 0.173134, 0.18147, 0.182073, 0.185378, 0.18291, 0.176926, 0.197889};
static const float resTPCplus[Nb] = {0.103274, 0.154259, 0.173145, 0.180854, 0.181809, 0.18393, 0.181321, 0.172527, 0.20484};

Double_t MQ2[Nb], MQ4[Nb], M[Nb], sv2[Nb], sv4[Nb];
TComplex Q[Nb], Q2[Nb], ZQQQ[Nb];
TComplex p[Nb][NN], p2[Nb][NN];
TComplex q[Nb][NN], q2[Nb][NN];
Double_t mp[Nb][NN], mq[Nb][NN];
Double_t DiffMQ2[Nb][NN], DiffMQ4[Nb][NN], Diffsv2[Nb][NN], Diffsv4[Nb][NN];

Double_t PSIplus[Nb], PSIminus[Nb], PSItpcLR[Nb], Mplus[Nb], Mminus[Nb], Vobs[Nb], Res[Nb], Vobs3SUB[Nb];
Double_t PSIfhcal[Nb], PSIfhcalR[Nb], PSIfhcalL[Nb], Mfhcal[Nb], MfhcalR[Nb], MfhcalL[Nb];
TComplex Qplus[Nb], Qminus[Nb], Qfhcal[Nb], QfhcalR[Nb], QfhcalL[Nb], QtpcLR[Nb];
Double_t dMplus[Nb][NN], dMminus[Nb][NN], dVobs[Nb][NN], dVobs3SUB[Nb][NN];

TH1F *SV2[Nb]; //2 частичная референсная корреляция
TH1F *SV4[Nb]; //4 частичная референсная корреляция
TH1F *hNpart = new TH1F("hNpart", "hNpart", 6000, 0, 6000);
TH1F *hBimp = new TH1F("hBimp", "hBimp", 1000, 0, 25);
TH1F *hPt = new TH1F("hPt", "hPt", 1000, -5, 5);
TH1F *hETA = new TH1F("hETA", "hETA", 1000, -8, 8);
TH1F *hdPHI = new TH1F("hdPHI", "dPHI", 1000, -6.5, 6.5);

TH1F *HPHI[Nb], *HRES[Nb], *HVobs[Nb], *HDiffVobs[Nb][NN], *HVobs3SUB[Nb], *HDiffVobs3SUB[Nb][NN], *HRES_1_TPC_LR[Nb], *HRES_1_FHCal_LR[Nb];
TH1F *SV2_SV4[Nb];
TH1F *HQxTPC[Nb], *HQyTPC[Nb], *HQxFHCal[Nb], *HQyFHCal[Nb], *HRES_TPCLR_fhcalL[Nb], *HRES_TPCLR_fhcalR[Nb];
TH1F *HRESminus_fhcal[Nb], *HRESfhcal_plus[Nb], *HRESfhcalR_L[Nb], *HRES_TPCR_fhcalR[Nb], *HRES_TPCL_fhcalR[Nb], *HRES_TPCR_fhcalL[Nb], *HRES_TPCL_fhcalL[Nb];
TH1F *DiffSV2[Nb][NN], *DiffSV4[Nb][NN];
TH1F *SV2_DiffSV2[Nb][NN], *SV2_DiffSV4[Nb][NN];
TH1F *SV4_DiffSV2[Nb][NN], *SV4_DiffSV4[Nb][NN];
TH1F *DiffSV2_DiffSV4[Nb][NN];
TH1F *hcounter[Nb][NN];

TComplex NQ[2][Nb], Np[2][Nb][NN];
Double_t NM[2][Nb], Nmp[2][Nb][NN], Nsv2[Nb], NDiffsv2[Nb][NN];
TH1F *NSV2[Nb], *NDiffSV2[Nb][NN], *NSV2_DiffSV2[Nb][NN];

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
        HQxTPC[k] = new TH1F(Form("%sCENT%d_%d", "HQxTPC", k * 10, (k + 1) * 10), "HQxTPC", 2000, -1000, 1000);
        HQyTPC[k] = new TH1F(Form("%sCENT%d_%d", "HQyTPC", k * 10, (k + 1) * 10), "HQyTPC", 2000, -1000, 1000);
        HQxFHCal[k] = new TH1F(Form("%sCENT%d_%d", "HQxFHCal", k * 10, (k + 1) * 10), "HQxFHCal", 2000, -1000, 1000);
        HQyFHCal[k] = new TH1F(Form("%sCENT%d_%d", "HQyFHCal", k * 10, (k + 1) * 10), "HQyFHCal", 2000, -1000, 1000);
        HRESfhcalR_L[k] = new TH1F(Form("%sCENT%d_%d", "HRESfhcalR_L", k * 10, (k + 1) * 10), "HRESfhcalR_L", 200, -1, 1);
        HRES_TPCR_fhcalR[k] = new TH1F(Form("%sCENT%d_%d", "TPCR_fhcalR", k * 10, (k + 1) * 10), "TPCR_fhcalR", 200, -1, 1);
        HRES_TPCL_fhcalR[k] = new TH1F(Form("%sCENT%d_%d", "TPCL_fhcalR", k * 10, (k + 1) * 10), "TPCL_fhcalR", 200, -1, 1);
        HRES_TPCR_fhcalL[k] = new TH1F(Form("%sCENT%d_%d", "TPCR_fhcalL", k * 10, (k + 1) * 10), "TPCR_fhcalL", 200, -1, 1);
        HRES_TPCL_fhcalL[k] = new TH1F(Form("%sCENT%d_%d", "TPCL_fhcalL", k * 10, (k + 1) * 10), "TPCL_fhcalL", 200, -1, 1);
        HRES_TPCLR_fhcalL[k] = new TH1F(Form("%sCENT%d_%d", "TPCLR_fhcalL", k * 10, (k + 1) * 10), "TPCLR_fhcalL", 200, -1, 1);
        HRES_TPCLR_fhcalR[k] = new TH1F(Form("%sCENT%d_%d", "TPCLR_fhcalR", k * 10, (k + 1) * 10), "TPCLR_fhcalR", 200, -1, 1);
        HRES_1_TPC_LR[k] = new TH1F(Form("%sCENT%d_%d", "HRES_1_TPC_LR", k * 10, (k + 1) * 10), "HRES_1_TPC_LR", 200, -1, 1);
        HRES_1_FHCal_LR[k] = new TH1F(Form("%sCENT%d_%d", "HRES_1_FHCal_LR", k * 10, (k + 1) * 10), "HRES_1_FHCal_LR", 200, -1, 1);

        sprintf(str, "%sCENT%d_%d", "PHI", k * 10, (k + 1) * 10);
        STR = (char *)str;
        HPHI[k] = new TH1F(STR, "PHI", 600, -6.5, 6.5);

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
    MfhcalR[k] = 0;
    MfhcalL[k] = 0;
    Qplus[k] = TComplex(0, 0);
    Qminus[k] = TComplex(0, 0);
    Qfhcal[k] = TComplex(0, 0);
    QfhcalR[k] = TComplex(0, 0);
    QfhcalL[k] = TComplex(0, 0);
    QtpcLR[k] = TComplex(0, 0);

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
    Double_t sign;
    if (n == 1)
    {
        sign = Veta / fabs(Veta);
    }
    else
    {
        sign = 1;
    }

    cos_phi = TMath::Cos(n * (Vphi)) * sign;
    sin_phi = TMath::Sin(n * (Vphi)) * sign;

    int bin_pt = GetBinPt(Vpt);

    if (Veta < -eta_min)
    {
        if (pt_min < Vpt < pt_max)
        {
            Qminus[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
            Mminus[k] += 1;
            NQ[0][k] += TComplex(cos_phi, sin_phi);
            NM[0][k] += 1;
            QtpcLR[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        }
        if (bin_pt != -1)
        {
            Nmp[0][k][bin_pt] += 1;
            Np[0][k][bin_pt] += TComplex(cos_phi, sin_phi);
        }
    }
    else if (Veta > eta_min)
    {
        if (pt_min < Vpt < pt_max)
        {
            Qplus[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
            Mplus[k] += 1;
            NQ[1][k] += TComplex(cos_phi, sin_phi);
            NM[1][k] += 1;
            QtpcLR[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        }
        if (bin_pt != -1)
        {
            Nmp[1][k][bin_pt] += 1;
            Np[1][k][bin_pt] += TComplex(cos_phi, sin_phi);
        }
    }

    PSIplus[k] = TMath::ATan2(Qplus[k].Im(), Qplus[k].Re()) / n;
    PSIminus[k] = TMath::ATan2(Qminus[k].Im(), Qminus[k].Re()) / n;

    //hETA->Fill(eta);
    //hdPHI->Fill(phi);
    //hPt->Fill(pt);
}

void LoopVarFHCal(int k, double Vpt, double Veta, double Vphi)
{
    Double_t cos_phi, sin_phi;
    Double_t sign;
    if (n == 1)
    {
        sign = Veta / fabs(Veta);
    }
    else
    {
        sign = 1;
    }
    cos_phi = TMath::Cos(n * (Vphi)) * sign;
    sin_phi = TMath::Sin(n * (Vphi)) * sign;
    // if (pt_min < Vpt < pt_max)
    //{
    if (Veta < -etafh_min && Veta > -etafh_max) //FHCal Left
    //if (TMath::Abs(Veta) > etafh_min && TMath::Abs(Veta) < etafh_max)
    {
        Qfhcal[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        Mfhcal[k] += 1;
        QfhcalL[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        MfhcalL[k] += 1;
    }
    else if (Veta > etafh_min && Veta < etafh_max) //FHCal Right
    {
        Qfhcal[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        Mfhcal[k] += 1;
        QfhcalR[k] += TComplex(Vpt * cos_phi, Vpt * sin_phi);
        MfhcalR[k] += 1;
    }
    //}
    PSIfhcalR[k] = TMath::ATan2(QfhcalR[k].Im(), QfhcalR[k].Re()) / n;
    PSIfhcalL[k] = TMath::ATan2(QfhcalL[k].Im(), QfhcalL[k].Re()) / n;
}
/*
void LoopVarEP(int k, double Vpt, double Veta, double Vphi)//FHcal
{
    //int bin_pt = GetBinPt(Veta);
    Double_t sign;
    int bin_pt = GetBinPt(Vpt);
    if (n == 1)
    {
        sign = Veta / fabs(Veta);
    }
    else
    {
        sign = 1;
    }
    //sign = 1;
    if (Veta > eta_min)
    {
        if (pt_min < Vpt < pt_max)
        {
            Vobs[k] += sign * cos(n * (Vphi - PSIfhcalL[k]));
            Vobs3SUB[k] += sign * cos(n * (Vphi - PSIfhcalL[k])) / resTPCmin[k];
        }
        if (bin_pt != -1)
        {
            dVobs[k][bin_pt] += sign * cos(n * (Vphi - PSIfhcalL[k]));
            dVobs3SUB[k][bin_pt] += sign * cos(n * (Vphi - PSIfhcalL[k])) / resTPCmin[k];
            dMplus[k][bin_pt] += 1;
        }
    }

    if (Veta < -eta_min)
    {
        if (pt_min < Vpt < pt_max)
        {
            Vobs[k] += sign * cos(n * (Vphi - PSIfhcalR[k]));
            Vobs3SUB[k] += sign * cos(n * (Vphi - PSIfhcalR[k])) / resTPCplus[k];
        }
        if (bin_pt != -1)
        {
            dVobs[k][bin_pt] += sign * cos(n * (Vphi - PSIfhcalR[k]));
            dVobs3SUB[k][bin_pt] += sign * cos(n * (Vphi - PSIfhcalR[k])) / resTPCplus[k];
            dMminus[k][bin_pt] += 1;
        }
    }
}
*/

void LoopVarEP(int k, double Vpt, double Veta, double Vphi) //FHcal
{
    //int bin_pt = GetBinPt(Veta);
    Double_t sign;
    int bin_pt = GetBinPt(Vpt);
    if (n == 1)
    {
        sign = Veta / fabs(Veta);
    }
    else
    {
        sign = 1;
    }
    //sign = 1;
    if (Veta > eta_min)
    {
        if (pt_min < Vpt < pt_max)
        {
            Vobs[k] += sign * cos(n * (Vphi - PSIminus[k]));
            Vobs3SUB[k] += sign * cos(n * (Vphi - PSIminus[k])) / resTPCmin[k];
        }
        if (bin_pt != -1)
        {
            dVobs[k][bin_pt] += sign * cos(n * (Vphi - PSIminus[k]));
            dVobs3SUB[k][bin_pt] += sign * cos(n * (Vphi - PSIminus[k])) / resTPCmin[k];
            dMplus[k][bin_pt] += 1;
        }
    }

    if (Veta < -eta_min)
    {
        if (pt_min < Vpt < pt_max)
        {
            Vobs[k] += sign * cos(n * (Vphi - PSIplus[k]));
            Vobs3SUB[k] += sign * cos(n * (Vphi - PSIplus[k])) / resTPCplus[k];
        }
        if (bin_pt != -1)
        {
            dVobs[k][bin_pt] += sign * cos(n * (Vphi - PSIplus[k]));
            dVobs3SUB[k][bin_pt] += sign * cos(n * (Vphi - PSIplus[k])) / resTPCplus[k];
            dMminus[k][bin_pt] += 1;
        }
    }
}

void LoopVar2(int k, double Vpt, double Veta, double Vphi)
{
    Double_t cos_phi, sin_phi, cos_2phi, sin_2phi;

    int bin_pt = GetBinPt(Vpt);
    Double_t sign;
    if (n == 1)
    {
        sign = Veta / fabs(Veta);
    }
    else
    {
        sign = 1;
    }

    cos_phi = TMath::Cos(n * (Vphi)) * sign;
    sin_phi = TMath::Sin(n * (Vphi)) * sign;
    cos_2phi = TMath::Cos(2 * n * (Vphi)) * sign;
    sin_2phi = TMath::Sin(2 * n * (Vphi)) * sign;

    /*cos_phi = TMath::Cos(n * (Vphi));
    sin_phi = TMath::Sin(n * (Vphi));
    cos_2phi = TMath::Cos(2 * n * (Vphi));
    sin_2phi = TMath::Sin(2 * n * (Vphi));*/
    if (pt_min < Vpt < pt_max)
    {
        Q[k] += TComplex(cos_phi, sin_phi);
        Q2[k] += TComplex(cos_2phi, sin_2phi);
        M[k] += 1;
    }
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
        HRES[k]->Fill(cos(m * PSIplus[k] - m * PSIminus[k]));
        HQxTPC[k]->Fill(Qplus[k].Re());
        HQyTPC[k]->Fill(Qplus[k].Im());
        HRES_1_TPC_LR[k]->Fill(cos(PSIplus[k] - PSIminus[k]));

        if (MfhcalR[k] > min_mult && MfhcalL[k] > min_mult)
        {
            PSIfhcal[k] = TMath::ATan2(Qfhcal[k].Im(), Qfhcal[k].Re()) / n;
            HRESminus_fhcal[k]->Fill(cos(m * PSIminus[k] - m * PSIfhcal[k]));
            HRESfhcal_plus[k]->Fill(cos(m * PSIfhcal[k] - m * PSIplus[k]));
            HVobs3SUB[k]->Fill(Vobs3SUB[k] / (Mplus[k] + Mminus[k]), Mplus[k] + Mminus[k]);
            HPHI[k]->Fill(m * PSIfhcal[k]);

            HQxFHCal[k]->Fill(Qfhcal[k].Re());
            HQyFHCal[k]->Fill(Qfhcal[k].Im());

            HRESfhcalR_L[k]->Fill(cos(m * PSIfhcalR[k] - m * PSIfhcalL[k]));
            HRES_1_FHCal_LR[k]->Fill(cos(PSIfhcalR[k] - PSIfhcalL[k]));

            HRES_TPCR_fhcalR[k]->Fill(cos(m * PSIplus[k] - m * PSIfhcalR[k]));
            HRES_TPCL_fhcalR[k]->Fill(cos(m * PSIminus[k] - m * PSIfhcalR[k]));
            HRES_TPCR_fhcalL[k]->Fill(cos(m * PSIplus[k] - m * PSIfhcalL[k]));
            HRES_TPCL_fhcalL[k]->Fill(cos(m * PSIminus[k] - m * PSIfhcalL[k]));

            PSItpcLR[k] = TMath::ATan2(QtpcLR[k].Im(), QtpcLR[k].Re()) / n;
            HRES_TPCLR_fhcalL[k]->Fill(cos(m * PSItpcLR[k] - m * PSIfhcalL[k]));
            HRES_TPCLR_fhcalR[k]->Fill(cos(m * PSItpcLR[k] - m * PSIfhcalR[k]));
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
            if (Mfhcal[k] > 0)
            {
                HDiffVobs3SUB[k][s]->Fill(dVobs3SUB[k][s] / (dMplus[k][s] + dMminus[k][s]), dMplus[k][s] + dMminus[k][s]);
            }
        }
    }
}

void SaveData(const char *outfile)
{
    TFile *d_outfile = new TFile(outfile, "recreate");
    //hPt->Write();
    //hNpart->Write();
    //hdPHI->Write();
    //hETA->Write();
    hBimp->Write();
    for (int k = 0; k < Nb; k++)
    {
        HRES_1_TPC_LR[k]->Write();
        HRES_1_FHCal_LR[k]->Write();
        HRESfhcalR_L[k]->Write();
        HRES_TPCR_fhcalR[k]->Write();
        HRES_TPCL_fhcalR[k]->Write();
        HRES_TPCR_fhcalL[k]->Write();
        HRES_TPCL_fhcalL[k]->Write();
        HRES_TPCLR_fhcalL[k]->Write();
        HRES_TPCLR_fhcalR[k]->Write();
        HQxTPC[k]->Write();
        HQyTPC[k]->Write();
        HQxFHCal[k]->Write();
        HQyFHCal[k]->Write();
        HPHI[k]->Write();
        SV2[k]->Write();
        NSV2[k]->Write();
        SV4[k]->Write();
        SV2_SV4[k]->Write();
        HVobs[k]->Write();
        HVobs3SUB[k]->Write();
        HRES[k]->Write();
        HRESminus_fhcal[k]->Write();
        HRESfhcal_plus[k]->Write();
        for (int s = 0; s < NN; s++)
        {
            hcounter[k][s]->Write();
            DiffSV2[k][s]->Write();
            NDiffSV2[k][s]->Write();
            HDiffVobs[k][s]->Write();
            HDiffVobs3SUB[k][s]->Write();
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
