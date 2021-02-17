#define sqr(x) ((x)*(x))
#include "PlotV2LYZ.C"
#include "DrawTGraphImp.C"
TString energy = "7.7";
TString input1 = Form("FirstRun_AMPT15_%s.root",energy.Data());
void PlotV2LYZInt(TString inputFileName1 = input1)
{
  bool bUseProduct = 1;
  bool bDebug = 1;
  TString label = Form("AMPT, #sigma_{p}=1.5 mb, Au+Au, #sqrt{s_{NN}}= %s GeV",energy.Data());
  TFile *fi1 = new TFile(inputFileName1.Data(),"read");
  // const int npt = 14; // 0.5 - 3.6 GeV/c - number of pt bins
  // const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0};
  // const double rootJ0 = 2.4048256;
  // const int ncent = 9;
  // const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
  // const int thetabins = 5;
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  const double J1rootJ0 = 0.519147;

  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TProfile *prRefMult = (TProfile*) fi1->Get("prRefMult");
  TProfile *prQ2x = (TProfile*) fi1->Get("prQ2x");
  TProfile *prQ2y = (TProfile*) fi1->Get("prQ2y");
  TProfile *prQ2ModSq = (TProfile*) fi1->Get("prQ2ModSq");
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile*) fi1->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile*) fi1->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile*) fi1->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile*) fi1->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }

  double dChi2[ncent]={0.}, dChi2Pro[ncent] = {0.};
  double v2LYZInt[ncent]={0.}, v2eLYZInt[ncent]={0.};
  double v2LYZIntPro[ncent]={0.}, v2eLYZIntPro[ncent]={0.};
  double dVtheta[ncent][thetabins] = {{0.}}, dVthetaPro[ncent][thetabins] = {{0.}};

  // Sum
  for (int ic = 0; ic < ncent; ic++)
  {
    double refmult = prRefMult->GetBinContent(ic+1);
    double v2int = 0., v2eint = 0., v2theta[thetabins] = {0.};
    int thetacount = 0;

    for (int it = 0; it < thetabins; it++)
    {
      TH1F *hGtheta = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      float r0theta = GetR0(hGtheta);
      if (r0theta!=0) 
      {
        v2int += rootJ0 / r0theta;
        v2theta[it] = rootJ0 / r0theta;
        thetacount++;
      }
    }
    if (thetacount!=0) v2int /= (float)thetacount*refmult; // refmult
    else {v2int = 0.;}
    
    float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
    float Q2xmean = prQ2x->GetBinContent(ic+1);
    float Q2ymean = prQ2y->GetBinContent(ic+1);
    float chi2 = v2int*refmult/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int*refmult,2));
    
    float temp=0.;
    for(int it=0; it<thetabins; it++)
    {
      double arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    float neve = prRefMult->GetBinEntries(ic+1);
    float err2mean = v2int*sqrt(temp/2./neve/thetabins)/rootJ0/J1rootJ0;

    for (int it = 0; it < thetabins; it++) dVtheta[ic][it] = v2theta[it];
    v2LYZInt[ic] = v2int;
    dChi2[ic] = chi2;
    v2eLYZInt[ic] = err2mean;

  } // end of V2RP calculation
  

  // Product
  if (bUseProduct) {
    for (int ic = 0; ic < ncent; ic++)
    {
      double refmult = prRefMult->GetBinContent(ic+1);
      double v2int = 0., v2eint = 0., v2theta[thetabins] = {0.};
      int thetacount = 0;

      for (int it = 0; it < thetabins; it++)
      {
        TH1F *hGtheta = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);
        float r0theta = GetR0(hGtheta);
        if (r0theta!=0) 
        {
          v2int += rootJ0 / r0theta;
          v2theta[it] = rootJ0 / r0theta;
          thetacount++;
        }
      }
      if (thetacount!=0) v2int /= (float)thetacount*refmult;
      else {v2int = 0.;}
      
      float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
      float Q2xmean = prQ2x->GetBinContent(ic+1);
      float Q2ymean = prQ2y->GetBinContent(ic+1);
      float chi2 = v2int*refmult/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int*refmult,2));
      
      float temp=0.;
      for(int it=0; it<thetabins; it++)
      {
        double arg = theta[it];
        temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
          BesselJ0(2.*rootJ0*sin(arg/2.))+
          exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
          BesselJ0(2.*rootJ0*cos(arg/2.));
      }
      float neve = prRefMult->GetBinEntries(ic+1);
      float err2mean = v2int*sqrt(temp/2./neve/thetabins)/rootJ0/J1rootJ0;

      for (int it = 0; it < thetabins; it++) dVthetaPro[ic][it] = v2theta[it];
      v2LYZIntPro[ic] = v2int;
      dChi2Pro[ic] = chi2;
      v2eLYZIntPro[ic] = err2mean;

    } // end of V2RP calculation    
  } 

  double v2Int[2][ncent], v2eInt[2][ncent];
  double x[ncent], errX[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    v2Int[0][ic] = v2LYZInt[ic]; // LYZ, Sum
    v2Int[1][ic] = v2LYZIntPro[ic]; // LYZ, Pro

    v2eInt[0][ic] = v2eLYZInt[ic]; // LYZ, Sum
    v2eInt[1][ic] = v2eLYZIntPro[ic]; // LYZ, Pro

    x[ic] = (bin_cent[ic] + bin_cent[ic+1]) / 2.;
    errX[ic] = 0.;
  }

  if (bDebug){
    cout << "const double ChiSum[" << ncent << "] = {";
    for (int ic = 0; ic < ncent-1; ic++)
    {
      cout << sqrt(dChi2[ic]) <<", ";
    }
    cout << sqrt(dChi2[ncent-1]) << "};" << endl;

    cout << "const double v2LYZSum[" << ncent << "] = {";
    for (int ic = 0; ic < ncent-1; ic++)
    {
      cout << v2Int[0][ic] <<", ";
    }
    cout << v2Int[0][ncent-1] << "};" << endl;
    if (bUseProduct)
    {
      cout << "const double ChiPro[" << ncent << "] = {";
      for (int ic = 0; ic < ncent-1; ic++)
      {
        cout << sqrt(dChi2Pro[ic]) <<", ";
      }
      cout << sqrt(dChi2Pro[ncent-1]) << "};" << endl;

      cout << "const double v2LYZPro[" << ncent << "] = {";
      for (int ic = 0; ic < ncent-1; ic++)
      {
        cout << v2Int[1][ic] <<", ";
      }
      cout << v2Int[1][ncent-1] << "};" << endl;
    }
  }

  TGraphErrors *grV2IntLYZ[2];
  grV2IntLYZ[0] = new TGraphErrors(ncent, x, v2Int[0], errX, v2eInt[0]); // Sum
  grV2IntLYZ[0]->SetTitle("v_{2}{LYZ, Sum};Centrality, %;v_{2}");
  grV2IntLYZ[0]->SetMarkerStyle(28);
  // grV2IntLYZ[0]->SetMarkerColor(kRed+2);
  // grV2IntLYZ[0]->SetLineColor(kRed+2);
  grV2IntLYZ[0]->GetYaxis()->SetRangeUser(-0.01,0.1);
  grV2IntLYZ[1] = new TGraphErrors(ncent, x, v2Int[1], errX, v2eInt[1]); // Product
  grV2IntLYZ[1]->SetTitle("v_{2}{LYZ, Prod.};Centrality, %;v_{2}");
  grV2IntLYZ[1]->SetMarkerStyle(26);
  // grV2IntLYZ[1]->SetMarkerColor(kBlack);
  // grV2IntLYZ[1]->SetLineColor(kBlack);
  grV2IntLYZ[1]->GetYaxis()->SetRangeUser(-0.01,0.1);
  TGraphErrors *grRatioProductToSum = Ratio(grV2IntLYZ[1],grV2IntLYZ[0]);
  TString legEntries[2] = {"v_{2}{LYZ, Sum}","v_{2}{LYZ, Prod.}"};
  grRatioProductToSum->SetTitle(Form(";Centrality, %%;%s/%s",legEntries[1].Data(),legEntries[0].Data()));
  grRatioProductToSum->GetYaxis()->SetRangeUser(0.79,1.19);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  gStyle->SetPalette(kDarkRainBow);
  TCanvas c;
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title->SetBorderSize(0);
  title->SetFillColor(0);
  c.Divide(2,1);
  c.cd(1);
  grV2IntLYZ[0]->Draw("AP  PLC PMC");
  grV2IntLYZ[1]->Draw("P  PLC PMC");
  TLegend *leg = new TLegend(0.6,0.2,0.85,0.45);
  
  leg->SetBorderSize(0);
  for (int i=0;i<2;i++) leg->AddEntry(grV2IntLYZ[i],legEntries[i].Data(),"p");
  leg->Draw();
  c.cd(2);
  TLine lineOne;
  lineOne.SetLineStyle(2);
  grRatioProductToSum->Draw("AP  PLC PMC");
  lineOne.DrawLine(0,1,80,1);
  c.SaveAs(Form("IntFlowLYZ_%s.pdf",energy.Data()));

}
