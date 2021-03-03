
#include <TLine.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TLegend.h>
#include "/home/dim/LYZ/TOY/Init.C"

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

    cout << " start read flow" << endl;
    //Референсный поток

    double res_minus_fhcal[Nb], res_fhcal_plus[Nb], res3SUB[Nb], res3SUBplus[Nb], vEP3SUB[Nb], DiffvEP3SUB[Nb][NN], ErEv3SUB[Nb], RMSvep3SUB[Nb][NN];
    for (int k = 0; k < Nb; k++)
    {
        sv2[k] = SV2[k]->GetMean();
        Nsv2[k] = NSV2[k]->GetMean();
        v2[k] = pow(fabs(sv2[k]), 0.5);
        Nv2[k] = pow(fabs(Nsv2[k]), 0.5);

        sv4[k] = SV4[k]->GetMean();
        cn4[k] = sv4[k] - 2 * (sv2[k] * sv2[k]);
        v4[k] = pow(fabs(cn4[k]), 0.25);

        res[k] = pow(HRES[k]->GetMean(), 0.5);
        vEP[k] = HVobs[k]->GetMean() / res[k];
        res_minus_fhcal[k] = pow(HRESminus_fhcal[k]->GetMean(), 0.5);
        res_fhcal_plus[k] = pow(HRESfhcal_plus[k]->GetMean(), 0.5);
        res3SUB[k] = res_minus_fhcal[k] * res[k] / res_fhcal_plus[k];
        res3SUBplus[k] = res_fhcal_plus[k] * res[k] / res_minus_fhcal[k];
        vEP3SUB[k] = HVobs3SUB[k]->GetMean();
cout << " res_fhcal_plus "<<res_fhcal_plus[k]<<endl;
cout << " res_fhcal_plus "<<res_fhcal_plus[k]<<endl;
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
            RMSvep3SUB[k][m] = pow(RMSvep3SUB[k][m], 0.5) / res3SUB[k];

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
         << "static const float resTPCmin[Nb]={" << res3SUB[0];
    for (int k = 1; k < Nb; k++)
    {
        cout << "," << res3SUB[k];
    }
    cout << "};" << endl
         << "static const float resTPCplus[Nb]={" << res3SUBplus[0];
    for (int k = 1; k < Nb; k++)
    {
        cout << "," << res3SUBplus[k];
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
        grvEp[kk]->SetMarkerColorAlpha(kRed, 1);
        grvEp[kk]->SetLineColorAlpha(kRed, 1);
        grvEp[kk]->SetLineWidth(2);
        grvEp[kk]->Write();

        grvEp3SUB[kk] = new TGraphErrors(NN, binPt[kk], DiffvEP3SUB[kk], RMSbinPt[kk], RMSvep3SUB[kk]);
        sprintf(name, "gr_cent%i_4", kk);
        grvEp3SUB[kk]->SetName(name);
        grvEp3SUB[kk]->SetTitle("v_{2}{EP};p_{T}, GeV/c;v_{2}");
        grvEp3SUB[kk]->SetMarkerStyle(23);
        grvEp3SUB[kk]->SetMarkerSize(1.5);
        grvEp3SUB[kk]->SetMarkerColorAlpha(kRed + 1, 1);
        grvEp3SUB[kk]->SetLineColorAlpha(kRed + 1, 1);
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

        ErEv3SUB[kk] = pow(sigmaX(HVobs[kk], 1), 0.5) / res3SUB[kk];
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

    static const double binCentEr[Nb] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    TCanvas *resC = new TCanvas("resC", "res Flow", 200, 10, 1600, 900);
    TGraphErrors *resEp = new TGraphErrors(Nb, binCent, res, RMSbinCent, binCentEr);
    resEp->SetMarkerStyle(20);
    resEp->SetMarkerSize(1.5);
    resEp->SetMarkerColorAlpha(1, 1);
    resEp->SetLineColorAlpha(1, 1);
    resEp->SetLineWidth(1);
    sprintf(name, "res");
    resEp->SetName(name);
    resEp->Write();
    resEp->GetYaxis()->SetRangeUser(0, 1);
    resEp->Draw("AP");

    TGraphErrors *resEp3SUB = new TGraphErrors(Nb, binCent, res3SUB, RMSbinCent, binCentEr);
    resEp3SUB->SetMarkerStyle(23);
    resEp3SUB->SetMarkerSize(1.5);
    resEp3SUB->SetMarkerColorAlpha(kRed + 1, 1);
    resEp3SUB->SetLineColorAlpha(kRed + 1, 1);
    resEp3SUB->SetLineWidth(1);
    sprintf(name, "res3sub");
    resEp3SUB->SetName(name);
    resEp3SUB->Write();
    resEp3SUB->Draw("SAME P");

    TGraphErrors *resEp3SUBplus = new TGraphErrors(Nb, binCent, res3SUBplus, RMSbinCent, binCentEr);
    resEp3SUBplus->SetMarkerStyle(25);
    resEp3SUBplus->SetMarkerSize(1.5);
    resEp3SUBplus->SetMarkerColorAlpha(kBlue + 1, 1);
    resEp3SUBplus->SetLineColorAlpha(kBlue + 1, 1);
    resEp3SUBplus->SetLineWidth(1);
    sprintf(name, "res3subplus");
    resEp3SUBplus->SetName(name);
    resEp3SUBplus->Write();
    resEp3SUBplus->Draw("SAME P");

    TLegend *legdifres;
    legdifres = new TLegend(0.16, 0.22, 0.35, 0.45);
    legdifres->AddEntry(resEp, "TPC,2 subEvent", "pe");
    legdifres->AddEntry(resEp3SUB, "TPC,#eta<0, 3 subEvent", "pe");
    legdifres->AddEntry(resEp3SUBplus, "TPC,#eta>0, 3 subEvent", "pe");
    legdifres->Draw();

    d_outfile->Close();
}
