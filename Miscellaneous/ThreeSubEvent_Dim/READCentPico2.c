#include "TMath.h"
#include <Math/SpecFuncMathMore.h>
#include <TMath.h>

#include <TLine.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TPaveText.h>
#include <TLegend.h>
#include "/home/dim/LYZ/TOY/Init.C"

// Resolution calculation
//S----------------------------------------------------------------
double GetRes(double _chi, double _harm)
{
    double con = TMath::Sqrt(TMath::Pi() / 2) / 2;
    double arg = _chi * _chi / 4.;
    double order1 = (_harm - 1) / 2.;
    double order2 = (_harm + 1) / 2.;
    double res = con * _chi * exp(-arg) * (ROOT::Math::cyl_bessel_i(order1, arg) + ROOT::Math::cyl_bessel_i(order2, arg));
    return res;
}
//E--

// Chi2 calculation
//S----------------------------------------------------------------
double GetChi(double _res, double _harm, int accuracy)
{
    double chi = 2.0;
    double delta = 1.0;
    for (int i = 0; i < accuracy; i++)
    {
        if (GetRes(chi, _harm) < _res)
            chi = chi + delta;
        else
            chi = chi - delta;
        delta = delta / 2.;
    }
    return chi;
}
//E-----

TGraphErrors *grv4[Nb], *grv2[Nb], *Ngrv2[Nb], *grvEp[Nb], *grvEp3SUB[Nb];                                                                    //differential flow tgraph
TGraphErrors *grIntv4[Nb], *grIntv2[Nb], *NgrIntv2[Nb], *grIntvEp[Nb], *grIntvEp3Sub[Nb];                                                     //
double RMSSV2[Nb], NRMSSV2[Nb], RMSSV4[Nb], RMSVEP[Nb], IntV2[Nb], NIntV2[Nb], IntV4[Nb], IntEv[Nb], ErV2[Nb], NErV2[Nb], ErV4[Nb], ErEv[Nb]; //RMS для SV2 и SV4
double res[Nb];

double sigmaX(TH1F *X, double weight)
{
    double RMS = X->GetStdDev();
    double neff = X->GetEffectiveEntries();
    return weight * RMS * RMS / (neff - 1);
}

double sigmaXY(TH1F *X, TH1F *Y, TH1F *XY, double weight)
{
    double RMS = XY->GetMean() - (X->GetMean()) * (Y->GetMean());
    double Xsum = X->GetSum();
    double Ysum = Y->GetSum();
    double XYsum = XY->GetSum();
    double neff = Xsum * Ysum / XYsum;
    return weight * RMS / (neff - 1);
}

void read(const char *infile, const char *savefile = "~/GIT/urqmd.root")
{
    // Setting up global variables for the plot
    gROOT->SetStyle("Pub");
    gROOT->ForceStyle();

    double RMSdn2[Nb][NN], NRMSdn2[Nb][NN];
    double RMSv2[Nb][NN], NRMSv2[Nb][NN];
    double RMSdn4[Nb][NN];
    double RMSv4[Nb][NN];
    double Rv2[Nb][NN], NRv2[Nb][NN];
    double Rv4[Nb][NN];
    double mc[Nb][NN];
    double RMSmc[Nb][NN];
    double RMSvep[Nb][NN];
    double RMSbinPt[Nb][NN];

    double dsv4[Nb][NN], dsv2[Nb][NN], sv4[Nb], sv2[Nb], Nsv2[Nb], v4[Nb], Nv2[Nb], v2[Nb], vMC[Nb], vEP[Nb], cn2[Nb], cn4[Nb];

    double binPt[Nb][NN];
    double QMC[Nb][NN];
    double dn2[Nb][NN], Ndn2[Nb][NN];
    double dn4[Nb][NN];
    double Diffv2[Nb][NN], NDiffv2[Nb][NN];
    double Diffv4[Nb][NN];
    double DiffvEP[Nb][NN];
    double Diffsv2[Nb][NN];
    double Diffsv4[Nb][NN];

    char str[200];
    const char *STR;
    TH1F *HV2[NN];
    TH1F *HV4[NN];
    TH1F *HNV2[NN];
    TH1F *HVEP[NN];

    TFile *f = new TFile(infile);

    for (int m = 0; m < NN; m++)
    {
        sprintf(str, "%s_%d", "V2", m);
        HV2[m] = new TH1F(str, str, 100, 0, 0.25);

        sprintf(str, "%s_%d", "NV2", m);
        HNV2[m] = new TH1F(str, str, 100, 0, 0.25);

        sprintf(str, "%s_%d", "V4", m);
        HV4[m] = new TH1F(str, str, 100, 0, 0.25);

        sprintf(str, "%s_%d", "VEP", m);
        HVEP[m] = new TH1F(str, str, 100, 0, 0.25);
    }

    for (int k = 0; k < Nb; k++)
    {
        sprintf(str, "%sCENT%d_%d", "sv2", k * 10, (k + 1) * 10);
        SV2[k] = (TH1F *)f->Get(str);

        sprintf(str, "%sCENT%d_%d", "Nsv2", k * 10, (k + 1) * 10);
        NSV2[k] = (TH1F *)f->Get(str);

        sprintf(str, "%sCENT%d_%d", "sv4", k * 10, (k + 1) * 10);
        SV4[k] = (TH1F *)f->Get(str);

        sprintf(str, "%sCENT%d_%d", "sv2_sv4", k * 10, (k + 1) * 10);
        SV2_SV4[k] = (TH1F *)f->Get(str);

        sprintf(str, "%sCENT%d_%d", "HRES", k * 10, (k + 1) * 10);
        HRES[k] = (TH1F *)f->Get(str);

        sprintf(str, "%sCENT%d_%d", "Vobs", k * 10, (k + 1) * 10);
        HVobs[k] = (TH1F *)f->Get(str);

        HRESminus_fhcal[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HRESmin_fh", k * 10, (k + 1) * 10));
        HRESfhcal_plus[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HRESfh_pl", k * 10, (k + 1) * 10));
        HVobs3SUB[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "Vobs3", k * 10, (k + 1) * 10));
        HQxTPC[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HQxTPC", k * 10, (k + 1) * 10));
        HQyTPC[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HQyTPC", k * 10, (k + 1) * 10));
        HQxFHCal[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HQxFHCal", k * 10, (k + 1) * 10));
        HQyFHCal[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HQyFHCal", k * 10, (k + 1) * 10));
        HRESfhcalR_L[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HRESfhcalR_L", k * 10, (k + 1) * 10));

        HRES_TPCR_fhcalR[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "TPCR_fhcalR", k * 10, (k + 1) * 10));
        HRES_TPCL_fhcalR[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "TPCL_fhcalR", k * 10, (k + 1) * 10));
        HRES_TPCR_fhcalL[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "TPCR_fhcalL", k * 10, (k + 1) * 10));
        HRES_TPCL_fhcalL[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "TPCL_fhcalL", k * 10, (k + 1) * 10));
        HRES_TPCLR_fhcalL[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "TPCLR_fhcalL", k * 10, (k + 1) * 10));
        HRES_TPCLR_fhcalR[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "TPCLR_fhcalR", k * 10, (k + 1) * 10));
        HRES_1_TPC_LR[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HRES_1_TPC_LR", k * 10, (k + 1) * 10));
        HRES_1_FHCal_LR[k] = (TH1F *)f->Get(Form("%sCENT%d_%d", "HRES_1_FHCal_LR", k * 10, (k + 1) * 10));

        for (int m = 0; m < NN; m++)
        {
            sprintf(str, "%s%d_CENT%d_%d", "hcounter", m, k * 10, (k + 1) * 10);
            hcounter[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "sv2Diff", m, k * 10, (k + 1) * 10);
            DiffSV2[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "Nsv2Diff", m, k * 10, (k + 1) * 10);
            NDiffSV2[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "sv4Diff", m, k * 10, (k + 1) * 10);
            DiffSV4[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "SV2_DiffSV2", m, k * 10, (k + 1) * 10);
            SV2_DiffSV2[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "NSV2_DiffSV2", m, k * 10, (k + 1) * 10);
            NSV2_DiffSV2[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "SV2_DiffSV4", m, k * 10, (k + 1) * 10);
            SV2_DiffSV4[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "SV4_DiffSV2", m, k * 10, (k + 1) * 10);
            SV4_DiffSV2[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "SV4_DiffSV4", m, k * 10, (k + 1) * 10);
            SV4_DiffSV4[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "DiffSV2_DiffSV4", m, k * 10, (k + 1) * 10);
            DiffSV2_DiffSV4[k][m] = (TH1F *)f->Get(str);

            sprintf(str, "%s%d_CENT%d_%d", "diffVobs", m, k * 10, (k + 1) * 10);
            HDiffVobs[k][m] = (TH1F *)f->Get(str);

            HDiffVobs3SUB[k][m] = (TH1F *)f->Get(Form("%s%d_CENT%d_%d", "diffVobs3", m, k * 10, (k + 1) * 10));

            //hBin_Pt[k][m] = 0.5 * (pt_bin[m] + pt_bin[m + 1]); //hBin_Pt[k][m]=(TH1F*)f->Get(HBinPt);
            RMSbinPt[k][m] = 0;
        }
    }

    //pCosTPC_LR[i]->GetBinError(ic+1)/(2.*res);

    cout << " start read flow" << endl;
    //Референсный поток
    double QxTPC[Nb], QyTPC[Nb], QxFHCal[Nb], QyFHCal[Nb];
    int garm = 2, Mm = 2;
    double TPCmax = 0.5, FHCalMax = 1.1;
    const char *model = "urqmd7_";

    double res_minus_fhcal[Nb], res_fhcal_plus[Nb], res3SUBminus[Nb], res3SUBplus[Nb], res3SUBfhcal[Nb], res2SUBfhcal_LR[Nb], vEP3SUB[Nb], DiffvEP3SUB[Nb][NN], ErEv3SUB[Nb], RMSvep3SUB[Nb][NN];
    double res3SUBfhcalR[Nb], res3SUBfhcalL[Nb], res3SUBfhcalR_tpcLR[Nb], res3SUBfhcalL_tpcLR[Nb], resAproxfhcal_LR[Nb], chi[Nb], res3SUBtpc[Nb], resAproxTPC_LR[Nb];
    for (int k = 0; k < Nb; k++)
    {cout << " start read flow - " <<k<< endl;
        QxTPC[k] = HQxTPC[k]->GetMean();
        QyTPC[k] = HQyTPC[k]->GetMean();
        QxFHCal[k] = HQxFHCal[k]->GetMean();
        QyFHCal[k] = HQyFHCal[k]->GetMean();

        sv2[k] = SV2[k]->GetMean();
        Nsv2[k] = NSV2[k]->GetMean();
        v2[k] = pow(fabs(sv2[k]), 0.5);
        Nv2[k] = pow(fabs(Nsv2[k]), 0.5);

        sv4[k] = SV4[k]->GetMean();
        cn4[k] = sv4[k] - 2 * (sv2[k] * sv2[k]);
        v4[k] = pow(fabs(cn4[k]), 0.25);

        res[k] = pow(fabs(HRES[k]->GetMean()), 0.5); //
        res2SUBfhcal_LR[k] = pow(fabs(HRESfhcalR_L[k]->GetMean()), 0.5);
        vEP[k] = HVobs[k]->GetMean() / res[k];
        res_minus_fhcal[k] = pow(fabs(HRESminus_fhcal[k]->GetMean()), 0.5);
        res_fhcal_plus[k] = pow(fabs(HRESfhcal_plus[k]->GetMean()), 0.5);
        res3SUBminus[k] = res_minus_fhcal[k] * res[k] / res_fhcal_plus[k]; //HRESminus_fhcal[k]->GetMean();
        res3SUBplus[k] = res_fhcal_plus[k] * res[k] / res_minus_fhcal[k];  //HRESfhcal_plus[k]->GetMean();
        res3SUBfhcal[k] = res_fhcal_plus[k] * res_minus_fhcal[k] / res[k];

        res3SUBfhcalR[k] = HRES_TPCR_fhcalR[k]->GetMean() * HRES_TPCL_fhcalR[k]->GetMean();
        res3SUBfhcalR[k] = pow(res3SUBfhcalR[k], 0.5) / res[k];
        res3SUBfhcalL[k] = HRES_TPCR_fhcalL[k]->GetMean() * HRES_TPCL_fhcalL[k]->GetMean();
        res3SUBfhcalL[k] = pow(res3SUBfhcalL[k], 0.5) / res[k];

                if (garm == 1 && Mm == 2)
        {
            chi[k] = TMath::Sqrt(2) * GetChi(pow(HRES_1_FHCal_LR[k]->GetMean(), 0.5), 1., 50);
            //chi[k] = TMath::Sqrt(2) * GetChi(res2SUBfhcal_LR[k], 1., 50);
            resAproxfhcal_LR[k] = GetRes(chi[k], 2.);
        }
        else
        {
            chi[k] = TMath::Sqrt(2) * GetChi(res2SUBfhcal_LR[k], 1., 50);
            resAproxfhcal_LR[k] = GetRes(chi[k], 1.);
        }

        res3SUBfhcalR_tpcLR[k] = HRESfhcalR_L[k]->GetMean() * HRES_TPCLR_fhcalR[k]->GetMean();
        res3SUBfhcalR_tpcLR[k] = pow(fabs(res3SUBfhcalR_tpcLR[k] / HRES_TPCLR_fhcalL[k]->GetMean()), 0.5);
        res3SUBfhcalL_tpcLR[k] = HRESfhcalR_L[k]->GetMean() * HRES_TPCLR_fhcalL[k]->GetMean();
        res3SUBfhcalL_tpcLR[k] = pow(fabs(res3SUBfhcalL_tpcLR[k] / HRES_TPCLR_fhcalR[k]->GetMean()), 0.5);
        res3SUBtpc[k] = HRES_TPCLR_fhcalR[k]->GetMean() * HRES_TPCLR_fhcalL[k]->GetMean();
        res3SUBtpc[k] = pow(fabs(res3SUBtpc[k] / HRESfhcalR_L[k]->GetMean()), 0.5);

        if (garm == 1 && Mm == 2)
        {
            chi[k] = TMath::Sqrt(2) * GetChi(pow(HRES_1_TPC_LR[k]->GetMean(), 0.5), 1., 50);
            resAproxTPC_LR[k] = GetRes(chi[k], 2.);
        }
        else
        {
            chi[k] = TMath::Sqrt(2) * GetChi(res[k], 1., 50);
            resAproxTPC_LR[k] = GetRes(chi[k], 1.);
        }


        vEP3SUB[k] = HVobs3SUB[k]->GetMean();
        //cout << " chiS[k] " << chiS[k] << endl;
        cout << " chi[k] " << chi[k] << endl;
        //cout << " resS[k] " << resS[k] << endl;
        cout << " resAproxfhcal_LR[k] " << resAproxfhcal_LR[k] << endl
             << endl;
        for (int m = 0; m < NN; m++)
        {
            DiffvEP[k][m] = HDiffVobs[k][m]->GetMean() / res[k];
            DiffvEP3SUB[k][m] = HDiffVobs3SUB[k][m]->GetMean();
            dn2[k][m] = DiffSV2[k][m]->GetMean();
            Ndn2[k][m] = NDiffSV2[k][m]->GetMean();
            Diffv2[k][m] = dn2[k][m] / pow(fabs(sv2[k]), 0.5);
            NDiffv2[k][m] = Ndn2[k][m] / pow(fabs(Nsv2[k]), 0.5);

            dsv4[k][m] = DiffSV4[k][m]->GetMean();
            dn4[k][m] = dsv4[k][m] - 2 * dn2[k][m] * sv2[k];
            Diffv4[k][m] = -dn4[k][m] / pow(fabs(cn4[k]), 0.75);
            binPt[k][m] = 0.5 * (pt_bin[m] + pt_bin[m + 1]);
        }

        //погрешность для дифференциального потока
        for (int m = 0; m < NN; m++)
        {

            RMSvep[k][m] = sigmaX(HDiffVobs[k][m], 1) / HRES[k]->GetMean(); //+ 0.25 * HDiffVobs[k][m]->GetMean() * HDiffVobs[k][m]->GetMean() * sigmaX(HRES[k], 1) / pow(HRES[k]->GetMean(), 3);
            RMSvep[k][m] = pow(RMSvep[k][m], 0.5);
            RMSvep3SUB[k][m] = sigmaX(HDiffVobs[k][m], 1); //+ 0.25 * HDiffVobs[k][m]->GetMean() * HDiffVobs[k][m]->GetMean() * sigmaX(HRES[k], 1) / pow(HRES[k]->GetMean(), 3);
            RMSvep3SUB[k][m] = pow(RMSvep3SUB[k][m], 0.5) / res3SUBminus[k];

            RMSdn2[k][m] = sigmaX(DiffSV2[k][m], 1);
            NRMSdn2[k][m] = sigmaX(NDiffSV2[k][m], 1);
            RMSdn4[k][m] = DiffSV4[k][m]->GetStdDev();

            Rv2[k][m] = 0.25 * pow(sv2[k], -3) * (pow(dn2[k][m], 2) * sigmaX(SV2[k], 1) + 4 * sv2[k] * sv2[k] * sigmaX(DiffSV2[k][m], 1) - 4 * dn2[k][m] * sv2[k] * sigmaXY(SV2[k], DiffSV2[k][m], SV2_DiffSV2[k][m], 1));
            RMSv2[k][m] = pow(Rv2[k][m], 0.5);

            NRv2[k][m] = 0.25 * pow(Nsv2[k], -3) * (pow(Ndn2[k][m], 2) * sigmaX(NSV2[k], 1) + 4 * Nsv2[k] * Nsv2[k] * sigmaX(NDiffSV2[k][m], 1) - 4 * Ndn2[k][m] * Nsv2[k] * sigmaXY(NSV2[k], NDiffSV2[k][m], NSV2_DiffSV2[k][m], 1));
            NRMSv2[k][m] = pow(NRv2[k][m], 0.5);

            Rv4[k][m] = (pow(fabs(cn4[k]), -3.5)) * (pow((2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]), 2) * sigmaX(SV2[k], 1) +
                                                     9. / 16 * pow(dn4[k][m], 2) * sigmaX(SV4[k], 1) + 4 * sv2[k] * sv2[k] * pow(fabs(cn4[k]), 2) * sigmaX(DiffSV2[k][m], 1) +

                                                     pow(fabs(cn4[k]), 2) * sigmaX(DiffSV4[k][m], 1) -

                                                     1.5 * fabs(dn4[k][m]) * (2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]) * sigmaXY(SV2[k], SV4[k], SV2_SV4[k], 1) -

                                                     4 * sv2[k] * fabs(cn4[k]) * (2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]) * sigmaXY(SV2[k], DiffSV2[k][m], SV2_DiffSV2[k][m], 1) +

                                                     2 * fabs(cn4[k]) * (2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]) * sigmaXY(SV2[k], DiffSV4[k][m], SV2_DiffSV4[k][m], 1) +

                                                     3 * sv2[k] * (fabs(cn4[k])) * fabs(dn4[k][m]) * sigmaXY(SV4[k], DiffSV2[k][m], SV4_DiffSV2[k][m], 1) -

                                                     1.5 * fabs(cn4[k]) * fabs(dn4[k][m]) * sigmaXY(SV4[k], DiffSV4[k][m], SV4_DiffSV4[k][m], 1) -

                                                     4 * sv2[k] * pow(fabs(cn4[k]), 2) * sigmaXY(DiffSV2[k][m], DiffSV4[k][m], DiffSV2_DiffSV4[k][m], 1));

            RMSv4[k][m] = pow(Rv4[k][m], 0.5);
        }
    }

    cout << endl
         << "static const float resTPCmin[Nb]={" << res3SUBminus[0];
    for (int k = 1; k < Nb; k++)
    {
        cout << "," << res3SUBminus[k];
    }
    cout << "};" << endl
         << "static const float resTPCplus[Nb]={" << res3SUBplus[0];
    for (int k = 1; k < Nb; k++)
    {
        cout << "," << res3SUBplus[k];
    }
    cout << "};" << endl
         << "static const float resFHCal[Nb]={" << res3SUBfhcalR_tpcLR[0];
    for (int k = 1; k < Nb; k++)
    {
        cout << "," << res3SUBfhcalR_tpcLR[k];
    }
    cout << "};" << endl;

    TFile *d_outfile = new TFile(savefile, "recreate");
    d_outfile->cd();

    char name[400];
    for (int kk = 0; kk < Nb; kk++)
    {
        //Дифференциальный поток с погрешностями

        grv4[kk] = new TGraphErrors(NN, binPt[kk], Diffv4[kk], RMSbinPt[kk], RMSv4[kk]);
        sprintf(name, "gr_cent%i_1", kk);
        grv4[kk]->SetName(name);
        grv4[kk]->SetTitle("v_{2}{4};p_{T}, GeV/c;v_{2}");
        grv4[kk]->GetYaxis()->SetRangeUser(-0.01, 0.23);
        grv4[kk]->SetMarkerStyle(21);
        grv4[kk]->SetMarkerSize(1.5);
        grv4[kk]->SetMarkerColorAlpha(kBlack, 1);
        grv4[kk]->SetLineColorAlpha(kBlack, 1);
        grv4[kk]->SetLineWidth(1);
        grv4[kk]->GetXaxis()->SetTitle("Pt,Gev/c");
        grv4[kk]->GetYaxis()->SetTitle("V_{2}");
        grv4[kk]->Write();

        grv2[kk] = new TGraphErrors(NN, binPt[kk], Diffv2[kk], RMSbinPt[kk], RMSv2[kk]);
        sprintf(name, "gr_cent%i_0", kk);
        grv2[kk]->SetName(name);
        grv2[kk]->SetTitle("v_{2}{2};p_{T}, GeV/c;v_{2}");
        grv2[kk]->SetMarkerStyle(20);
        grv2[kk]->SetMarkerSize(1.5);
        grv2[kk]->SetMarkerColorAlpha(kBlue, 1);
        grv2[kk]->SetLineColorAlpha(kBlue, 1);
        grv2[kk]->GetYaxis()->SetTitle("V_{2}");
        grv2[kk]->GetXaxis()->SetTitle("Pt,Gev/c");
        grv2[kk]->SetLineWidth(2);
        grv2[kk]->Write();

        Ngrv2[kk] = new TGraphErrors(NN, binPt[kk], NDiffv2[kk], RMSbinPt[kk], NRMSv2[kk]);
        sprintf(name, "gr_cent%i_3", kk);
        Ngrv2[kk]->SetName(name);
        Ngrv2[kk]->SetTitle("v_{2}{2};p_{T}, GeV/c;v_{2}");
        Ngrv2[kk]->SetMarkerStyle(22);
        Ngrv2[kk]->SetMarkerSize(1.5);
        Ngrv2[kk]->SetMarkerColorAlpha(kGreen, 1);
        Ngrv2[kk]->SetLineColorAlpha(kGreen, 1);
        Ngrv2[kk]->GetYaxis()->SetTitle("V_{2}");
        Ngrv2[kk]->GetXaxis()->SetTitle("Pt,Gev/c");
        Ngrv2[kk]->SetLineWidth(2);
        Ngrv2[kk]->Write();

        grvEp[kk] = new TGraphErrors(NN, binPt[kk], DiffvEP[kk], RMSbinPt[kk], RMSvep[kk]);
        sprintf(name, "gr_cent%i_2", kk);
        grvEp[kk]->SetName(name);
        grvEp[kk]->SetTitle("v_{2}{EP};p_{T}, GeV/c;v_{2}");
        grvEp[kk]->SetMarkerStyle(25);
        grvEp[kk]->SetMarkerSize(1.5);
        grvEp[kk]->SetMarkerColorAlpha(kRed + 2, 1);
        grvEp[kk]->SetLineColorAlpha(kRed + 2, 1);
        grvEp[kk]->SetLineWidth(2);
        grvEp[kk]->GetYaxis()->SetRangeUser(-0.25, 0.25);
        grvEp[kk]->Write();

        grvEp3SUB[kk] = new TGraphErrors(NN, binPt[kk], DiffvEP3SUB[kk], RMSbinPt[kk], RMSvep3SUB[kk]);
        sprintf(name, "gr_cent%i_4", kk);
        grvEp3SUB[kk]->SetName(name);
        grvEp3SUB[kk]->SetTitle("v_{2}{EP};p_{T}, GeV/c;v_{2}");
        grvEp3SUB[kk]->SetMarkerStyle(23);
        grvEp3SUB[kk]->SetMarkerSize(1.5);
        grvEp3SUB[kk]->SetMarkerColorAlpha(kRed, 1);
        grvEp3SUB[kk]->SetLineColorAlpha(kRed, 1);
        grvEp3SUB[kk]->SetLineWidth(2);
        grvEp3SUB[kk]->Write();
    }

    TCanvas *cdif = new TCanvas("cdif", "def Flow All", 200, 10, 1600, 900);
    cdif->Divide(3, 2, 0, 0);
    TLegend *legdif[Nb];
    for (int k = 0; k < Nb; k++)
    {
        cdif->cd(k + 1);

        if (k % 3 == 0)
        {
            legdif[k] = new TLegend(0.16, 0.72, 0.35, 0.995);
        }
        else
        {
            legdif[k] = new TLegend(0., 0.72, 0.24, 0.995);
        }
        legdif[k]->AddEntry(grv4[k], "V_{2}{4}", "pe");
        legdif[k]->AddEntry(grv2[k], "V_{2}{2}", "pe");
        legdif[k]->AddEntry(Ngrv2[k], "V_{2}{N2}", "pe");
        legdif[k]->AddEntry(grvEp[k], "V_{2}{EP}", "pe");
        legdif[k]->AddEntry(grvEp3SUB[k], "V_{2}{EP3}", "pe");
        char strleg[200];
        sprintf(strleg, " cent: %i-%i%%", k * 10, (k + 1) * 10);

        legdif[k]->SetHeader(strleg);
        grv4[k]->Draw("AP");
        grv2[k]->Draw("SAME P");
        Ngrv2[k]->Draw("SAME P");
        grvEp[k]->Draw("SAME P");
        grvEp3SUB[k]->Draw("SAME P");
        legdif[k]->Draw();
        TLine line;
        line.SetLineWidth(1);
        line.SetLineStyle(1);
        line.DrawLine(pt_bin[0], 0, pt_bin[NN], 0);
    }

    for (int kk = 0; kk < Nb; kk++)
    {
        IntV2[kk] = v2[kk];
        ErV2[kk] = pow(sigmaX(SV2[kk], 1), 0.5) / (2 * pow(sv2[kk], 0.5));
        NIntV2[kk] = Nv2[kk];
        NErV2[kk] = pow(sigmaX(NSV2[kk], 1), 0.5) / (2 * pow(Nsv2[kk], 0.5));
        IntV4[kk] = v4[kk];
        double Is4 = pow(fabs(cn4[kk]), -1.5) * (sigmaX(SV2[kk], sv2[kk] * sv2[kk]) + sigmaX(SV4[kk], 0.0625) - 0.5 * sv2[kk] * sigmaXY(SV2[kk], SV4[kk], SV2_SV4[kk], 1));
        ErV4[kk] = pow(Is4, 0.5);
        IntEv[kk] = vEP[kk];
        ErEv[kk] = pow(sigmaX(HVobs[kk], 1) / HRES[kk]->GetMean() + 0.25 * HVobs[kk]->GetMean() * HVobs[kk]->GetMean() * sigmaX(HRES[kk], 1) / pow(HRES[kk]->GetMean(), 3), 0.5);

        ErEv3SUB[kk] = pow(sigmaX(HVobs[kk], 1), 0.5) / res3SUBminus[kk];
    }

    //Референсный поток по центральсности

    TGraphErrors *grIv4 = new TGraphErrors(Nb, binCent, IntV4, RMSbinCent, ErV4);
    grIv4->SetMarkerStyle(21);
    grIv4->SetMarkerSize(1.5);
    grIv4->SetMarkerColorAlpha(kBlack, 1);
    grIv4->SetLineColorAlpha(kBlack, 1);
    grIv4->SetLineWidth(2);
    grIv4->GetXaxis()->SetTitle("Cent, %");
    grIv4->GetYaxis()->SetTitle("V_{2}");
    sprintf(name, "grRF_1");
    grIv4->SetName(name);
    grIv4->Write();

    TGraphErrors *grIv2 = new TGraphErrors(Nb, binCent, IntV2, RMSbinCent, ErV2);
    grIv2->SetMarkerStyle(20);
    grIv2->SetMarkerSize(1.5);
    grIv2->SetMarkerColorAlpha(kBlue, 1);
    grIv2->SetLineColorAlpha(kBlue, 1);
    grIv2->SetLineWidth(2);
    sprintf(name, "grRF_0");
    grIv2->SetName(name);
    grIv2->Write();

    TGraphErrors *NgrIv2 = new TGraphErrors(Nb, binCent, NIntV2, RMSbinCent, NErV2);
    NgrIv2->SetMarkerStyle(22);
    NgrIv2->SetMarkerSize(1.5);
    NgrIv2->SetMarkerColorAlpha(kGreen, 1);
    NgrIv2->SetLineColorAlpha(kGreen, 1);
    NgrIv2->SetLineWidth(2);
    sprintf(name, "grRF_3");
    NgrIv2->SetName(name);
    NgrIv2->Write();

    TGraphErrors *grIvEp = new TGraphErrors(Nb, binCent, IntEv, RMSbinCent, ErEv);
    grIvEp->SetMarkerStyle(25);
    grIvEp->SetMarkerSize(1.5);
    grIvEp->SetMarkerColorAlpha(kRed, 1);
    grIvEp->SetLineColorAlpha(kRed, 1);
    grIvEp->SetLineWidth(1);
    sprintf(name, "grRF_2");
    grIvEp->SetName(name);
    grIvEp->Write();

    TGraphErrors *grIvEp3SUB = new TGraphErrors(Nb, binCent, vEP3SUB, RMSbinCent, ErEv3SUB);
    grIvEp3SUB->SetMarkerStyle(23);
    grIvEp3SUB->SetMarkerSize(1.5);
    grIvEp3SUB->SetMarkerColorAlpha(kRed + 1, 1);
    grIvEp3SUB->SetLineColorAlpha(kRed + 1, 1);
    grIvEp3SUB->SetLineWidth(1);
    sprintf(name, "grRF_4");
    grIvEp3SUB->SetName(name);
    grIvEp3SUB->Write();

    TCanvas *cref = new TCanvas("ref", "ref Flow", 200, 10, 1600, 900);
    TLegend *legdif2;
    legdif2 = new TLegend(0.16, 0.72, 0.35, 0.995);

    legdif2->AddEntry(grIv4, "V_{2}{4}", "pe");
    legdif2->AddEntry(grIv2, "V_{2}{2}", "pe");
    legdif2->AddEntry(NgrIv2, "V_{2}{N2}", "pe");
    legdif2->AddEntry(grIvEp, "V_{2}{EP}", "pe");
    legdif2->AddEntry(grIvEp3SUB, "V_{2}{EP3}", "pe");
    char strleg[200];
    legdif2->SetHeader("Pt 0.2-3 GeV/c");
    grIv4->Draw("AP");
    grIv2->Draw("SAME P");
    NgrIv2->Draw("SAME P");
    grIvEp->Draw("SAME P");
    grIvEp3SUB->Draw("SAME P");
    legdif2->Draw();
    ///
    ///
    ///
    /// resolution!!!------------------------------------------------------------------------------------------------------

    static const double binCentEr[Nb] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    TCanvas *resC = new TCanvas("resC", "res Flow", 1300, 500);
    resC->Divide(4, 1);
    /// TPC L and R  ---------------------------------------------------------------------------------------------------
    resC->cd(1);
    TGraphErrors *resEp = new TGraphErrors(Nb, binCent, res, RMSbinCent, binCentEr);
    resEp->SetMarkerStyle(21);
    resEp->SetMarkerSize(1.5);
    resEp->SetMarkerColorAlpha(1, 1);
    resEp->SetLineColorAlpha(1, 1);
    resEp->SetLineWidth(1);
    sprintf(name, "res");
    resEp->SetName(name);
    resEp->Write();
    resEp->GetYaxis()->SetRangeUser(0., TPCmax);
    resEp->GetXaxis()->SetRangeUser(0., 80);
    resEp->GetXaxis()->SetTitle("Cent, %");
    resEp->GetYaxis()->SetTitle(Form("res_{%d}(#psi_{%d})", Mm, garm));
    resEp->GetYaxis()->SetNdivisions(505);
    resEp->GetXaxis()->SetNdivisions(505);
    resEp->Draw("AP");

    TGraphErrors *resEp3SUB = new TGraphErrors(Nb, binCent, res3SUBminus, RMSbinCent, binCentEr);
    resEp3SUB->SetMarkerStyle(22);
    resEp3SUB->SetMarkerSize(1.5);
    resEp3SUB->SetMarkerColorAlpha(kBlue + 2, 1);
    resEp3SUB->SetLineColorAlpha(kBlue + 2, 1);
    resEp3SUB->SetLineWidth(1);
    sprintf(name, "res3subminus");
    resEp3SUB->SetName(name);
    resEp3SUB->Write();
    resEp3SUB->Draw("SAME P");

    TGraphErrors *resEp3SUBplus = new TGraphErrors(Nb, binCent, res3SUBplus, RMSbinCent, binCentEr);
    resEp3SUBplus->SetMarkerStyle(24);
    resEp3SUBplus->SetMarkerSize(1.5);
    resEp3SUBplus->SetMarkerColorAlpha(kBlue, 1);
    resEp3SUBplus->SetLineColorAlpha(kBlue, 1);
    resEp3SUBplus->SetLineWidth(1);
    sprintf(name, "res3subplus");
    resEp3SUBplus->SetName(name);
    resEp3SUBplus->Write();
    resEp3SUBplus->Draw("SAME P");

    TLegend *legdifres;
    legdifres = new TLegend(0.35, 0.85, 0.98, 1);
    legdifres->SetTextSize(0.03);
    legdifres->AddEntry(resEp, "TPC L/R,2 sub", "pe");
    legdifres->AddEntry(resEp3SUBplus, "TPC R, 3 sub", "pe");
    legdifres->AddEntry(resEp3SUB, "TPC L, 3 sub", "pe");
    legdifres->Draw();

    //FHCal full  ---------------------------------------------------
    resC->cd(2);
    //R+L
    TGraphErrors *resEp3SUBfhcal = new TGraphErrors(Nb, binCent, res3SUBfhcal, RMSbinCent, binCentEr);
    resEp3SUBfhcal->SetMarkerStyle(25);
    resEp3SUBfhcal->SetMarkerSize(1.5);
    resEp3SUBfhcal->SetMarkerColorAlpha(kGreen + 1, 1);
    resEp3SUBfhcal->SetLineColorAlpha(kGreen + 1, 1);
    resEp3SUBfhcal->SetLineWidth(1);

    resEp3SUBfhcal->GetYaxis()->SetRangeUser(0., FHCalMax);

    resEp3SUBfhcal->GetXaxis()->SetRangeUser(0., 80);
    resEp3SUBfhcal->GetXaxis()->SetTitle("Cent, %");
    resEp3SUBfhcal->GetYaxis()->SetTitle(Form("res_{%d}(#psi_{%d})", Mm, garm));
    resEp3SUBfhcal->GetYaxis()->SetNdivisions(506);
    resEp3SUBfhcal->GetXaxis()->SetNdivisions(505);
    sprintf(name, "res3fhcal");
    resEp3SUBfhcal->SetName(name);
    resEp3SUBfhcal->Write();
    resEp3SUBfhcal->Draw("AP");

    //Full
    TGraphErrors *resEp3SUBfhcalR = new TGraphErrors(Nb, binCent, resAproxfhcal_LR, RMSbinCent, binCentEr);
    resEp3SUBfhcalR->SetMarkerStyle(34);
    resEp3SUBfhcalR->SetMarkerSize(1.5);
    resEp3SUBfhcalR->SetMarkerColorAlpha(kGreen + 2, 1);
    resEp3SUBfhcalR->SetLineColorAlpha(kGreen + 2, 1);
    resEp3SUBfhcalR->SetLineWidth(1);
    sprintf(name, "resAproxfhcal_LR");
    resEp3SUBfhcalR->SetName(name);
    resEp3SUBfhcalR->Write();
    resEp3SUBfhcalR->Draw("SAME P");

    TLegend *legdifresF;
    legdifresF = new TLegend(0.3, 0.85, 0.98, 1);
    legdifresF->SetTextSize(0.03);
    legdifresF->AddEntry(resEp3SUBfhcal, "FHCal L+R, 3 sub", "pe");
    legdifresF->AddEntry(resEp3SUBfhcalR, "FHCal L+R, Aprox", "pe");
    legdifresF->Draw();

    //R+L------TPC Full------------------------------------------------------
    resC->cd(3);
    //Full
    TGraphErrors *resEp3SUBtpc = new TGraphErrors(Nb, binCent, res3SUBtpc, RMSbinCent, binCentEr);
    resEp3SUBtpc->SetMarkerStyle(25);
    resEp3SUBtpc->SetMarkerSize(1.5);
    resEp3SUBtpc->SetMarkerColorAlpha(kBlack, 1);
    resEp3SUBtpc->SetLineColorAlpha(kBlack, 1);
    resEp3SUBtpc->SetLineWidth(1);
    resEp3SUBtpc->GetYaxis()->SetRangeUser(0., TPCmax);
    resEp3SUBtpc->GetXaxis()->SetRangeUser(0., 80);
    resEp3SUBtpc->GetXaxis()->SetTitle("Cent, %");
    resEp3SUBtpc->GetYaxis()->SetTitle(Form("res_{%d}(#psi_{%d})", Mm, garm));
    resEp3SUBtpc->GetYaxis()->SetNdivisions(506);
    resEp3SUBtpc->GetXaxis()->SetNdivisions(505);
    sprintf(name, "res3tpc");
    resEp3SUBtpc->SetName(name);
    resEp3SUBtpc->Write();
    resEp3SUBtpc->Draw("AP");

    //Full Approx
    TGraphErrors *GresAproxTPC_LR = new TGraphErrors(Nb, binCent, resAproxTPC_LR, RMSbinCent, binCentEr);
    GresAproxTPC_LR->SetMarkerStyle(34);
    GresAproxTPC_LR->SetMarkerSize(1.5);
    GresAproxTPC_LR->SetMarkerColorAlpha(kBlack, 1);
    GresAproxTPC_LR->SetLineColorAlpha(kBlack, 1);
    GresAproxTPC_LR->SetLineWidth(1);
    sprintf(name, "resAproxTPC_LR");
    GresAproxTPC_LR->SetName(name);
    GresAproxTPC_LR->Write();
    GresAproxTPC_LR->Draw("SAME P");

    TLegend *legdifresT;
    legdifresT = new TLegend(0.3, 0.85, 0.98, 1);
    legdifresT->SetTextSize(0.03);
    legdifresT->AddEntry(resEp3SUBtpc, "TPC L+R, 3 sub", "pe");
    legdifresT->AddEntry(GresAproxTPC_LR, "TPC L+R, Aprox", "pe");
    legdifresT->Draw();

    resC->cd(4);
    //2 SubEvent----------------------------------------------------------
    TGraphErrors *resEp2SUBfhcal = new TGraphErrors(Nb, binCent, res2SUBfhcal_LR, RMSbinCent, binCentEr);
    resEp2SUBfhcal->SetMarkerStyle(21);
    resEp2SUBfhcal->SetMarkerSize(1.5);
    resEp2SUBfhcal->SetMarkerColorAlpha(kGreen + 2, 1);
    resEp2SUBfhcal->SetLineColorAlpha(kGreen + 2, 1);
    resEp2SUBfhcal->SetLineWidth(1);
    sprintf(name, "res2fhcal_LR");
    resEp2SUBfhcal->SetName(name);
    resEp2SUBfhcal->Write();
    resEp2SUBfhcal->GetYaxis()->SetRangeUser(0., FHCalMax);
    resEp2SUBfhcal->GetXaxis()->SetRangeUser(0., 80);
    resEp2SUBfhcal->GetXaxis()->SetTitle("Cent, %");
    resEp2SUBfhcal->GetYaxis()->SetTitle(Form("res_{%d}(#psi_{%d})", Mm, garm));
    resEp2SUBfhcal->GetYaxis()->SetNdivisions(506);
    resEp2SUBfhcal->GetXaxis()->SetNdivisions(505);
    resEp2SUBfhcal->Draw("AP");

    //Right
    TGraphErrors *resEp3SUBfhcalR_tpcLR = new TGraphErrors(Nb, binCent, res3SUBfhcalR_tpcLR, RMSbinCent, binCentEr);
    resEp3SUBfhcalR_tpcLR->SetMarkerStyle(24);
    resEp3SUBfhcalR_tpcLR->SetMarkerSize(1.5);
    resEp3SUBfhcalR_tpcLR->SetMarkerColorAlpha(kRed, 1);
    resEp3SUBfhcalR_tpcLR->SetLineColorAlpha(kRed, 1);
    resEp3SUBfhcalR_tpcLR->SetLineWidth(1);
    sprintf(name, "res3fhcalR_tpcLR");
    resEp3SUBfhcalR_tpcLR->SetName(name);
    resEp3SUBfhcalR_tpcLR->Write();
    resEp3SUBfhcalR_tpcLR->Draw("SAME P");
    //Left
    TGraphErrors *resEp3SUBfhcalL_tpcLR = new TGraphErrors(Nb, binCent, res3SUBfhcalL_tpcLR, RMSbinCent, binCentEr);
    resEp3SUBfhcalL_tpcLR->SetMarkerStyle(22);
    resEp3SUBfhcalL_tpcLR->SetMarkerSize(1.5);
    resEp3SUBfhcalL_tpcLR->SetMarkerColorAlpha(kRed + 2, 1);
    resEp3SUBfhcalL_tpcLR->SetLineColorAlpha(kRed + 2, 1);
    resEp3SUBfhcalL_tpcLR->SetLineWidth(1);
    sprintf(name, "res3fhcalL_tpcLR");
    resEp3SUBfhcalL_tpcLR->SetName(name);
    resEp3SUBfhcalL_tpcLR->Write();
    resEp3SUBfhcalL_tpcLR->Draw("SAME P");

    TLegend *legdifresF2;
    legdifresF2 = new TLegend(0.3, 0.85, 0.98, 1);
    legdifresF2->SetTextSize(0.03);
    legdifresF2->AddEntry(resEp2SUBfhcal, "FHCal L/R, 2 sub", "pe");
    legdifresF2->AddEntry(resEp3SUBfhcalR_tpcLR, "FHCal R, 3 sub", "pe");
    legdifresF2->AddEntry(resEp3SUBfhcalL_tpcLR, "FHCal L, 3 sub", "pe");
    legdifresF2->Draw();

    resC->SaveAs(Form("/home/dim/LYZ/TOY/OUT/garm%d%d/%sRes%d.png", Mm, garm, model, garm));

    TCanvas *resTPC = new TCanvas("resTPC", "res dFlow", 1000, 650);
    resTPC->cd();
    resEp->Draw("AP");
    resEp3SUB->Draw("SAME P");
    resEp3SUBplus->Draw("SAME P");
    TLegend *legres = new TLegend(0.6, 0.85, 0.93, 1);
    legres->SetTextSize(0.03);
    legres->AddEntry(resEp, "TPC L/R,2 sub", "pe");
    legres->AddEntry(resEp3SUBplus, "TPC R, 3 sub", "pe");
    legres->AddEntry(resEp3SUB, "TPC L, 3 sub", "pe");
    legres->Draw();
    resTPC->SaveAs(Form("/home/dim/LYZ/TOY/OUT/garm%d%d/%sResTPC%d.png", Mm, garm, model, garm));

    TCanvas *resFHCal = new TCanvas("resFHCal", "res FHCal", 1000, 650);
    resFHCal->cd();
    resEp2SUBfhcal->Draw("AP");
    resEp3SUBfhcalR_tpcLR->Draw("SAME P");
    resEp3SUBfhcalL_tpcLR->Draw("SAME P");
    TLegend *legresF2 = new TLegend(0.6, 0.85, 0.93, 1);
    legresF2->SetTextSize(0.03);
    legresF2->AddEntry(resEp2SUBfhcal, "FHCal L/R, 2 sub", "pe");
    legresF2->AddEntry(resEp3SUBfhcalR_tpcLR, "FHCal R, 3 sub", "pe");
    legresF2->AddEntry(resEp3SUBfhcalL_tpcLR, "FHCal L, 3 sub", "pe");
    legresF2->Draw();
    resFHCal->SaveAs(Form("/home/dim/LYZ/TOY/OUT/garm%d%d/%sResFHCal%d.png", Mm, garm, model, garm));

    TCanvas *resFHCalFull = new TCanvas("resFHCalFull", "res FHCalFull", 1000, 650);
    resFHCalFull->cd();
    resEp3SUBfhcal->Draw("AP");
    resEp3SUBfhcalR->Draw("SAME P");
    TLegend *legresF = new TLegend(0.6, 0.85, 0.93, 1);
    legresF->SetTextSize(0.03);
    legresF->AddEntry(resEp3SUBfhcal, "FHCal L+R, 3 sub", "pe");
    legresF->AddEntry(resEp3SUBfhcalR, "FHCal L+R, Aprox", "pe");
    legresF->Draw();
    resFHCalFull->SaveAs(Form("/home/dim/LYZ/TOY/OUT/garm%d%d/%sResFHCalFull%d.png", Mm, garm, model, garm));

    TCanvas *resTPCFull = new TCanvas("resTPCFull", "res TPCFull", 1000, 650);
    resTPCFull->cd();
    resEp3SUBtpc->Draw("AP");
    GresAproxTPC_LR->Draw("SAME P");

    TLegend *legresT;
    legresT = new TLegend(0.6, 0.85, 0.93, 1);
    legresT->SetTextSize(0.03);
    legresT->AddEntry(resEp3SUBtpc, "TPC L+R, 3 sub", "pe");
    legresT->AddEntry(GresAproxTPC_LR, "TPC L+R, Aprox", "pe");
    legresT->Draw();
    resTPCFull->SaveAs(Form("/home/dim/LYZ/TOY/OUT/garm%d%d/%sResTPCFull%d.png", Mm, garm, model, garm));
    //Усредненый поток 10-40% не дороботан!!!
    /*
    for (int k = 1; k < 4; k++)
    {
        for (int m = 0; m < NN; m++)
        {
            HV2[m]->Fill(Diffv2[k][m], hcounter[k][m]->GetSum());
            HNV2[m]->Fill(NDiffv2[k][m], hcounter[k][m]->GetSum());
            HV4[m]->Fill(Diffv4[k][m], hcounter[k][m]->GetSum());
            HVEP[m]->Fill(DiffvEP[k][m], hcounter[k][m]->GetSum());
        }
    }

    for (int k = 2; k < 4; k++)
    {

        SV2[1]->Add(SV2[k]);

        NSV2[1]->Add(NSV2[k]);

        SV4[1]->Add(SV4[k]);

        SV2_SV4[1]->Add(SV2_SV4[k]);

        HRES[1]->Add(HRES[k]);

        HVobs[1]->Add(HVobs[k]);

        for (int m = 0; m < NN; m++)
        {
            DiffSV2[1][m]->Add(DiffSV2[k][m]);
            NDiffSV2[1][m]->Add(NDiffSV2[k][m]);
            DiffSV4[1][m]->Add(DiffSV4[k][m]);

            SV2_DiffSV2[1][m]->Add(SV2_DiffSV2[k][m]);
            NSV2_DiffSV2[1][m]->Add(NSV2_DiffSV2[k][m]);

            SV2_DiffSV4[1][m]->Add(SV2_DiffSV4[k][m]);

            SV4_DiffSV2[1][m]->Add(SV4_DiffSV2[k][m]);

            SV4_DiffSV4[1][m]->Add(SV4_DiffSV4[k][m]);

            DiffSV2_DiffSV4[1][m]->Add(DiffSV2_DiffSV4[k][m]);

            HDiffVobs[1][m]->Add(HDiffVobs[k][m]);

            //hBin_Pt[k][m] = 0.5 * (pt_bin[m] + pt_bin[m + 1]); //hBin_Pt[k][m]=(TH1F*)f->Get(HBinPt);
        }
    }

    cout << " start read flow" << endl;
    //Референсный поток
    for (int k = 0; k < Nb; k++)
    {
        sv2[k] = SV2[k]->GetMean();
        Nsv2[k] = NSV2[k]->GetMean();
        v2[k] = pow(fabs(sv2[k]), 0.5);
        Nv2[k] = pow(fabs(sv2[k]), 0.5);
        sv4[k] = SV4[k]->GetMean();
        cn4[k] = sv4[k] - 2 * (sv2[k] * sv2[k]);
        v4[k] = pow(fabs(cn4[k]), 0.25);

        vEP[k] = HVobs[k]->GetMean() / pow(HRES[k]->GetMean(), 0.5);
        res[k] = pow(HRES[k]->GetMean(), 0.5);

        //Дифференциальный поток
        //cout << "flow for cent " << 10 * (k + 0.5) << "REF v{EP} " << vEP[k] << endl;
        //cout << "flow for cent " << 10 * (k + 0.5) << "REF v{2} " << Nv2[k] << endl;
        //cout << "flow for cent " << 10 * (k + 0.5) << "REF v{4} " << v4[k] << endl;
        for (int m = 0; m < NN; m++)
        {
            DiffvEP[k][m] = HDiffVobs[k][m]->GetMean() / pow(HRES[k]->GetMean(), 0.5);
            dn2[k][m] = DiffSV2[k][m]->GetMean();
            Ndn2[k][m] = NDiffSV2[k][m]->GetMean();
            Diffv2[k][m] = dn2[k][m] / pow(fabs(sv2[k]), 0.5);
            NDiffv2[k][m] = Ndn2[k][m] / pow(fabs(Nsv2[k]), 0.5);

            dsv4[k][m] = DiffSV4[k][m]->GetMean();
            dn4[k][m] = dsv4[k][m] - 2 * dn2[k][m] * sv2[k];
            Diffv4[k][m] = -dn4[k][m] / pow(fabs(cn4[k]), 0.75);
            binPt[k][m] = 0.5 * (pt_bin[m] + pt_bin[m + 1]);
        }
        cout << "flow for cent " << 10 * (k + 0.5) << "dif v{2} " << Diffv2[k][7] << endl;
        cout << "flow for cent " << 10 * (k + 0.5) << "dif Nv{2} " << NDiffv2[k][7] << endl;
        //погрешность для дифференциального потока
        for (int m = 0; m < NN; m++)
        {

            RMSvep[k][m] = sigmaX(HDiffVobs[k][m], 1) / HRES[k]->GetMean(); //+ 0.25 * HDiffVobs[k][m]->GetMean() * HDiffVobs[k][m]->GetMean() * sigmaX(HRES[k], 1) / pow(HRES[k]->GetMean(), 3);
            RMSvep[k][m] = pow(RMSvep[k][m], 0.5);
            RMSdn2[k][m] = sigmaX(DiffSV2[k][m], 1);
            NRMSdn2[k][m] = sigmaX(NDiffSV2[k][m], 1);
            RMSdn4[k][m] = DiffSV4[k][m]->GetStdDev();

            Rv2[k][m] = 0.25 * pow(sv2[k], -3) * (pow(dn2[k][m], 2) * sigmaX(SV2[k], 1) + 4 * sv2[k] * sv2[k] * sigmaX(DiffSV2[k][m], 1) - 4 * dn2[k][m] * sv2[k] * sigmaXY(SV2[k], DiffSV2[k][m], SV2_DiffSV2[k][m], 1));
            RMSv2[k][m] = pow(Rv2[k][m], 0.5);

            NRv2[k][m] = 0.25 * pow(Nsv2[k], -3) * (pow(Ndn2[k][m], 2) * sigmaX(NSV2[k], 1) + 4 * Nsv2[k] * Nsv2[k] * sigmaX(NDiffSV2[k][m], 1) - 4 * Ndn2[k][m] * Nsv2[k] * sigmaXY(NSV2[k], NDiffSV2[k][m], NSV2_DiffSV2[k][m], 1));
            NRMSv2[k][m] = pow(NRv2[k][m], 0.5);

            Rv4[k][m] = (pow(fabs(cn4[k]), -3.5)) * (pow((2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]), 2) * sigmaX(SV2[k], 1) +
                                                     9. / 16 * pow(dn4[k][m], 2) * sigmaX(SV4[k], 1) + 4 * sv2[k] * sv2[k] * pow(fabs(cn4[k]), 2) * sigmaX(DiffSV2[k][m], 1) +

                                                     pow(fabs(cn4[k]), 2) * sigmaX(DiffSV4[k][m], 1) -

                                                     1.5 * fabs(dn4[k][m]) * (2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]) * sigmaXY(SV2[k], SV4[k], SV2_SV4[k], 1) -

                                                     4 * sv2[k] * fabs(cn4[k]) * (2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]) * sigmaXY(SV2[k], DiffSV2[k][m], SV2_DiffSV2[k][m], 1) +

                                                     2 * fabs(cn4[k]) * (2 * sv2[k] * sv2[k] * dn2[k][m] - 3 * sv2[k] * dsv4[k][m] + 2 * sv4[k] * dn2[k][m]) * sigmaXY(SV2[k], DiffSV4[k][m], SV2_DiffSV4[k][m], 1) +

                                                     3 * sv2[k] * (fabs(cn4[k])) * fabs(dn4[k][m]) * sigmaXY(SV4[k], DiffSV2[k][m], SV4_DiffSV2[k][m], 1) -

                                                     1.5 * fabs(cn4[k]) * fabs(dn4[k][m]) * sigmaXY(SV4[k], DiffSV4[k][m], SV4_DiffSV4[k][m], 1) -

                                                     4 * sv2[k] * pow(fabs(cn4[k]), 2) * sigmaXY(DiffSV2[k][m], DiffSV4[k][m], DiffSV2_DiffSV4[k][m], 1));

            RMSv4[k][m] = pow(Rv4[k][m], 0.5);
        }
    }

    for (int m = 0; m < NN; m++)
    {
        Diffv2[1][m] = HV2[m]->GetMean();
        NDiffv2[1][m] = HNV2[m]->GetMean();
        Diffv4[1][m] = HV4[m]->GetMean();
        DiffvEP[1][m] = HVEP[m]->GetMean();
    }

    for (int kk = 1; kk < 2; kk++)
    {
        //Дифференциальный поток с погрешностями

        grv4[kk] = new TGraphErrors(NN, binPt[kk], Diffv4[kk], RMSbinPt[kk], RMSv4[kk]);
        //sprintf(name, "gr_cent%i4_2", kk);
        grv4[kk]->SetName("gr_cent10-40_1");
        grv4[kk]->SetTitle("v_{2}{4};p_{T}, GeV/c;v_{2}");
        grv4[kk]->GetYaxis()->SetRangeUser(-0.01, 0.23);
        //grv4[kk]->GetXaxis()->SetRangeUser(0., 2.5);
        grv4[kk]->SetMarkerStyle(21);
        grv4[kk]->SetMarkerSize(1.5);
        grv4[kk]->SetMarkerColorAlpha(kBlack, 1);
        grv4[kk]->SetLineColorAlpha(kBlack, 1);
        grv4[kk]->SetLineWidth(1);
        grv4[kk]->GetXaxis()->SetTitle("Pt,Gev/c");
        grv4[kk]->GetYaxis()->SetTitle("V_{2}");
        grv4[kk]->Write();

        grv2[kk] = new TGraphErrors(NN, binPt[kk], Diffv2[kk], RMSbinPt[kk], RMSv2[kk]);
        //sprintf(name, "gr_cent%i4_1", kk);
        grv2[kk]->SetName("gr_cent10-40_0");
        grv2[kk]->SetTitle("v_{2}{2};p_{T}, GeV/c;v_{2}");
        grv2[kk]->SetMarkerStyle(20);
        grv2[kk]->SetMarkerSize(1.5);
        grv2[kk]->SetMarkerColorAlpha(kBlue, 1);
        grv2[kk]->SetLineColorAlpha(kBlue, 1);
        grv2[kk]->GetYaxis()->SetTitle("V_{2}");
        grv2[kk]->GetXaxis()->SetTitle("Pt,Gev/c");
        grv2[kk]->SetLineWidth(2);
        grv2[kk]->Write();

        Ngrv2[kk] = new TGraphErrors(NN, binPt[kk], NDiffv2[kk], RMSbinPt[kk], NRMSv2[kk]);
        //sprintf(name, "gr_cent%i4_3", kk);
        Ngrv2[kk]->SetName("gr_cent10-40_3");
        Ngrv2[kk]->SetTitle("v_{2}{N2};p_{T}, GeV/c;v_{2}");
        Ngrv2[kk]->SetMarkerStyle(22);
        Ngrv2[kk]->SetMarkerSize(1.5);
        Ngrv2[kk]->SetMarkerColorAlpha(kGreen, 1);
        Ngrv2[kk]->SetLineColorAlpha(kGreen, 1);
        Ngrv2[kk]->GetYaxis()->SetTitle("V_{2}");
        Ngrv2[kk]->GetXaxis()->SetTitle("Pt,Gev/c");
        Ngrv2[kk]->SetLineWidth(2);
        Ngrv2[kk]->Write();

        grvEp[kk] = new TGraphErrors(NN, binPt[kk], DiffvEP[kk], RMSbinPt[kk], RMSvep[kk]);
        //sprintf(name, "gr_cent10-40_0", kk);
        grvEp[kk]->SetName("gr_cent10-40_2");
        grvEp[kk]->SetTitle("v_{2}{EP};p_{T}, GeV/c;v_{2}");
        grvEp[kk]->SetMarkerStyle(23);
        grvEp[kk]->SetMarkerSize(1.5);
        grvEp[kk]->SetMarkerColorAlpha(kRed, 1);
        grvEp[kk]->SetLineColorAlpha(kRed, 1);
        grvEp[kk]->SetLineWidth(2);
        grvEp[kk]->Write();
    }

    TCanvas *cdif14 = new TCanvas("cdif14", "def Flow 10-40", 200, 10, 1600, 900);
    TLegend *legdif3;
    legdif3 = new TLegend(0.16, 0.72, 0.35, 0.995);

    legdif3->AddEntry(grv4[1], "V_{2}{4}", "pe");
    legdif3->AddEntry(grv2[1], "V_{2}{2}", "pe");
    legdif3->AddEntry(Ngrv2[1], "V_{2}{N2}", "pe");
    legdif3->AddEntry(grvEp[1], "V_{2}{EP}", "pe");
    legdif3->SetHeader("Centrality 10-40%");
    grv4[1]->Draw("AP");
    grv2[1]->Draw("SAME P");
    Ngrv2[1]->Draw("SAME P");
    grvEp[1]->Draw("SAME P");
    legdif3->Draw();*/

    d_outfile->Close();
}
