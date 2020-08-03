#include <TF1.h>
#include <TLine.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TGraph.h>

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
  return weight * RMS * RMS / (neff - 1);
}
void read(const char *outfile)
{
  //double pt_bin[11]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};int NN=10;
  //double pt_bin[15]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2};int NN=14;//бины пот импульсу для дифференциального потока
  double pt_bin[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.7, 2.0, 2.4};
  int NN = 10;
  double RMSSV2, RMSSV4, RMSVMC; //RMS для SV2 и SV4
  double *RMSdn2 = new double[NN];
  double *RMSv2 = new double[NN];
  double *RMSdn4 = new double[NN];
  double *RMSv4 = new double[NN];
  double *Rv2 = new double[NN];
  double *Rv4 = new double[NN];
  double *mc = new double[NN];
  double *RMSmc = new double[NN];
  double *RMSbinPt = new double[NN];

  double sv4 = 0, sv2 = 0, v4, v2, vMC, cn2, cn4;

  TH1F *SV2; //2 частичная референсная корреляция
  TH1F *SV4; //4 частичная референсная корреляция
  TH1F *SV2_SV4;
  TH1F *HMC;
  /*
  TH1F *DiffSV2[14];TH1F *DiffSV4[14];TH1F *DiffMC[14];
  TH1F *SV2_DiffSV2[14];TH1F *SV2_DiffSV4[14];
  TH1F *SV4_DiffSV2[14];TH1F *SV4_DiffSV4[14];
  TH1F *DiffSV2_DiffSV4[14];
  */

  TH1F *DiffSV2[10];
  TH1F *DiffSV4[10];
  TH1F *DiffMC[10];
  TH1F *SV2_DiffSV2[10];
  TH1F *SV2_DiffSV4[10];
  TH1F *SV4_DiffSV2[10];
  TH1F *SV4_DiffSV4[10];
  TH1F *DiffSV2_DiffSV4[10];

  double *binPt = new double[NN];
  double *QMC = new double[NN];
  double *dn2 = new double[NN];
  double *dn4 = new double[NN];
  double *dsv4 = new double[NN];
  double *Diffv2 = new double[NN];
  double *Diffv4 = new double[NN];
  double *Diffsv2 = new double[NN];
  double *Diffsv4 = new double[NN];

  char strCOVsv2sv2[20];
  char strCOVsv2sv4[20];
  char strCOVsv4sv2[20];
  char strCOVsv4sv4[20];
  char DiffCOVsv2sv4[20];
  char strE[20];
  char strW[20];
  char strMC[20];

  TFile *f = new TFile(outfile);
  SV2 = (TH1F *)f->Get("sv2");
  SV4 = (TH1F *)f->Get("sv4");
  SV2_SV4 = (TH1F *)f->Get("sv2_sv4");
  HMC = (TH1F *)f->Get("mc");

  for (int m = 0; m < NN; m++)
  {
    sprintf(strE, "%s%d", "sv2Diff", m);
    sprintf(strW, "%s%d", "sv4Diff", m);
    sprintf(strMC, "%s%d", "DiffMC", m);
    sprintf(strCOVsv2sv2, "%s%d", "SV2_DiffSV2", m);
    sprintf(strCOVsv2sv4, "%s%d", "SV2_DiffSV4", m);
    sprintf(strCOVsv4sv2, "%s%d", "SV4_DiffSV2", m);
    sprintf(strCOVsv4sv4, "%s%d", "SV4_DiffSV4", m);
    sprintf(DiffCOVsv2sv4, "%s%d", "DiffSV2_DiffSV4", m);
    const char *EastH = (char *)strE;
    const char *WastH = (char *)strW;
    const char *SMC = (char *)strMC;
    const char *stCOVsv2sv2 = (char *)strCOVsv2sv2;
    const char *stCOVsv2sv4 = (char *)strCOVsv2sv4;
    const char *stCOVsv4sv2 = (char *)strCOVsv4sv2;
    const char *stCOVsv4sv4 = (char *)strCOVsv4sv4;
    const char *DifCOVsv2sv4 = (char *)DiffCOVsv2sv4;
    DiffSV2[m] = (TH1F *)f->Get(EastH);
    DiffSV4[m] = (TH1F *)f->Get(WastH);
    DiffMC[m] = (TH1F *)f->Get(SMC);
    SV2_DiffSV2[m] = (TH1F *)f->Get(stCOVsv2sv2);
    SV2_DiffSV4[m] = (TH1F *)f->Get(stCOVsv2sv4);
    SV4_DiffSV2[m] = (TH1F *)f->Get(stCOVsv4sv2);
    SV4_DiffSV4[m] = (TH1F *)f->Get(stCOVsv4sv4);
    DiffSV2_DiffSV4[m] = (TH1F *)f->Get(DifCOVsv2sv4);
    RMSbinPt[m] = 0;
  }

  //Референсный поток
  SV2->Sumw2();
  SV4->Sumw2();
  sv2 = SV2->GetMean();
  v2 = pow(fabs(sv2), 0.5);
  RMSSV2 = SV2->GetStdDev();
  sv4 = SV4->GetMean();
  cn4 = sv4 - 2 * (sv2 * sv2);
  v4 = pow(fabs(cn4), 0.25);
  RMSSV4 = SV4->GetStdDev();
  vMC = HMC->GetMean();
  RMSVMC = HMC->GetStdDev();
  cout << " v2{2} is " << v2 << " v2{4} is " << v4 << endl;

  //Дифференциальный поток
  for (int m = 0; m < NN; m++)
  {
    dn2[m] = DiffSV2[m]->GetMean();
    Diffv2[m] = dn2[m] / pow(fabs(sv2), 0.5);
    dsv4[m] = DiffSV4[m]->GetMean();
    dn4[m] = dsv4[m] - 2 * dn2[m] * sv2;
    Diffv4[m] = -dn4[m] / pow(fabs(cn4), 0.75);
    binPt[m] = 0.5 * (pt_bin[m] + pt_bin[m + 1]);
    cout << "Different. flow "
         << " v2{2} is " << Diffv2[m] << ", v2{4} is " << Diffv4[m] << " Pt " << binPt[m] << endl;
    //cout <<"Different. flow "<<" v2{2} is "<<dn2[m]<<", v2{4} is "<<dsv4[m]<<" Pt "<<binPt[m]<<endl ;
  }
  //погрешность для дифференциального потока

  for (int m = 0; m < NN; m++)
  {
    mc[m] = DiffMC[m]->GetMean();
    RMSmc[m] = pow(sigmaX(DiffMC[m], 1), 0.5);
    RMSdn2[m] = sigmaX(DiffSV2[m], 1);
    RMSdn4[m] = DiffSV4[m]->GetStdDev();

    Rv2[m] = 0.25 * pow(sv2, -3) * (pow(dn2[m], 2) * sigmaX(SV2, 1) + 4 * sv2 * sv2 * sigmaX(DiffSV2[m], 1) - 4 * dn2[m] * sv2 * sigmaXY(SV2, DiffSV2[m], SV2_DiffSV2[m], 1));
    RMSv2[m] = pow(Rv2[m], 0.5);

    Rv4[m] = (pow(fabs(cn4), -3.5)) * (pow((2 * sv2 * sv2 * dn2[m] - 3 * sv2 * dsv4[m] + 2 * sv4 * dn2[m]), 2) * sigmaX(SV2, 1) +

                                       9 / 16 * pow(dn4[m], 2) * sigmaX(SV4, 1) +

                                       4 * sv2 * sv2 * pow(fabs(cn4), 2) * sigmaX(DiffSV2[m], 1) +

                                       pow(fabs(cn4), 2) * sigmaX(DiffSV4[m], 1) -

                                       1.5 * fabs(dn4[m]) * (2 * sv2 * sv2 * dn2[m] - 3 * sv2 * dsv4[m] + 2 * sv4 * dn2[m]) * sigmaXY(SV2, SV4, SV2_SV4, 1) -

                                       4 * sv2 * fabs(cn4) * (2 * sv2 * sv2 * dn2[m] - 3 * sv2 * dsv4[m] + 2 * sv4 * dn2[m]) * sigmaXY(SV2, DiffSV2[m], SV2_DiffSV2[m], 1) +

                                       2 * fabs(cn4) * (2 * sv2 * sv2 * dn2[m] - 3 * sv2 * dsv4[m] + 2 * sv4 * dn2[m]) * sigmaXY(SV2, DiffSV4[m], SV2_DiffSV4[m], 1) +

                                       3 * sv2 * (fabs(cn4)) * dn4[m] * sigmaXY(SV4, DiffSV2[m], SV4_DiffSV2[m], 1) -

                                       1.5 * fabs(cn4) * sigmaXY(SV4, DiffSV4[m], SV4_DiffSV4[m], 1) -

                                       4 * sv2 * pow(fabs(cn4), 2) * sigmaXY(DiffSV2[m], DiffSV4[m], DiffSV2_DiffSV4[m], 1));

    RMSv4[m] = pow(Rv4[m], 0.5);
  }

  TCanvas *c1 = new TCanvas("c1", "Graph Draw Options1", 650, 500);

  //TF1 *momentdist = new TF1("momentdist","[1]*x+[0]", 0., 2.1);
  TF1 *momentdist = new TF1("momentdist", "[1]*(exp(2*x)-1)/(exp(2*x)+1)+[0]", 0., 2.3);
  /*
  momentdist->FixParameter(0, 0.02);
  momentdist->FixParameter(1, 0.1);
  momentdist->SetLineColorAlpha(kBlack, 0.8);
  momentdist->SetLineWidth(2);momentdist->SetLineStyle(5);
  momentdist->GetXaxis()->SetTitle("Pt,Gev/c");
  momentdist->GetYaxis()->SetTitle("V_{2}");
  momentdist->SetTitle("V_{2}(Pt)");
  momentdist->Draw();
  */

  TGraphErrors *grv4 = new TGraphErrors(NN, binPt, Diffv4, RMSbinPt, RMSv4);
  grv4->SetMarkerStyle(21);
  grv4->SetMarkerSize(1);
  grv4->SetMarkerColorAlpha(kBlack, 1);
  grv4->SetLineColorAlpha(kBlack, 1);
  grv4->SetLineWidth(2);
  grv4->Draw("AP");
  grv4->SetTitle("V_{2}{4}");

  TGraphErrors *grv2 = new TGraphErrors(NN, binPt, Diffv2, RMSbinPt, RMSv2);
  grv2->SetMarkerStyle(20);
  grv2->SetMarkerSize(1);
  grv2->SetMarkerColorAlpha(kBlue, 1);
  grv2->SetLineColorAlpha(kBlue, 1);
  grv2->GetYaxis()->SetTitle("V_{2}");
  grv2->GetXaxis()->SetTitle("Pt,Gev/c");
  grv2->SetLineWidth(2);
  grv2->Draw("SAME P");
  grv2->SetTitle("V_{2}{2}");

  TGraphErrors *grv = new TGraphErrors(NN, binPt, mc, RMSbinPt, RMSmc);
  grv->SetMarkerStyle(22);
  grv->SetMarkerSize(1);
  grv->SetMarkerColorAlpha(kGreen, 1);
  grv->SetLineColorAlpha(kGreen, 1);
  grv->SetLineWidth(1);
  grv->Draw("SAME P");
  grv->SetTitle("V_{2}{MC}");

  gPad->BuildLegend();
  gROOT->SetStyle("Pub");
  gStyle->SetOptStat(1111);
  //Рефренсный поток с погрешностями
  TCanvas *c2 = new TCanvas("c2", "Graph Draw Options", 650, 500);
  double x[1] = {1}, y[1] = {vMC}, ex[1] = {0.}, ey[1] = {pow(sigmaX(HMC, 1), 0.5)};
  TGraphErrors *grMC = new TGraphErrors(1, x, y, ex, ey);
  grMC->SetMarkerStyle(20);
  grMC->GetYaxis()->SetTitle("V_{2}");
  double x2[1] = {1.4}, y2[1] = {v2}, ex2[1] = {0.}, ey2[1] = {pow(sigmaX(SV2, 0.25 / sv2), 0.5)};
  TGraphErrors *grsv2 = new TGraphErrors(1, x2, y2, ex2, ey2);
  grsv2->SetMarkerStyle(20);

  double x4[1] = {1.8}, y4[1] = {v4}, ex4[1] = {0.}, ey4[1] = {0};
  double s4 = pow(fabs(cn4), -1.5) * (sigmaX(SV2, sv2 * sv2) + sigmaX(SV4, 0.125) - 0.5 * sv2 * sigmaXY(SV2, SV4, SV2_SV4, 1));
  ey4[0] = pow(s4, 0.5);
  TGraphErrors *grsv4 = new TGraphErrors(1, x4, y4, ex4, ey4);
  grsv4->SetMarkerStyle(20);
  cout << "MC eror " << ey[0] << " SV2 eror " << ey2[0] << " SV4 eror " << ey4[0] << endl;
  grMC->GetXaxis()->SetRangeUser(0, 1.9);
  grMC->GetYaxis()->SetRangeUser(y4[0] - 2 * ey4[0], y4[0] + 2 * ey4[0]);

  TLine *line = new TLine(0.9, vMC, 1.9, vMC);
  line->SetLineWidth(1);
  line->SetLineStyle(5);
  grMC->Draw("AP");
  grsv4->Draw("SAME P");
  grsv2->Draw("SAME P");
  line->Draw("SAME");
}
