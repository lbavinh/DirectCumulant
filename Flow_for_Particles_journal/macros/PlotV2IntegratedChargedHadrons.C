#include "PlotV2LYZ.C"
#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
#include "PlotV2HighOrderQCumulant.C"
// #include "DrawTGraphImp.C"

vector<TGraphErrors*> PlotV2IntegratedChargedHadrons(TString inputFirstRunFileName = "FirstRun_11.5.root", TString inputSecondRunFileName = "SecondRun_11.5.root")
{

  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const int ratioToMethod = 3;
  const double J1rootJ0 = 0.519147;
  const double errX[ncent] = {0.};
  const double X[ncent] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
  bool bUseProduct = 1;
  Int_t nmethod = 9;
  TString title[]={"v_{2}{#Psi_{2,TPC}}","v_{2}{SP}","v_{2}{2}","v_{2}{4}","v_{2}{6}","v_{2}{8}","v_{2}{LYZ, Sum}","v_{2}{LYZ, Prod.}","v_{2}{2,#eta-gap}"};
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *gr[nmethod];
  TFile *firun1 = new TFile(inputFirstRunFileName.Data(),"read");
  TFile *firun2 = new TFile(inputSecondRunFileName.Data(),"read");
  auto *prV2EP3D = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");
  TProfile *prV2EPInt = PlotV2EPIntegrated(prV2EP3D,minptRF,maxptRF,eta_cut);
  gr[0] = Converter(prV2EPInt);
  auto *prV2SP3D = (TProfile3D*) firun2->Get("prV2ScalarProduct");
  TProfile *prV2SPInt = PlotV2SPIntegrated(prV2SP3D,minptRF,maxptRF,eta_cut);
  gr[1] = Converter(prV2SPInt);

  TGraphErrors **grHOQC = PlotV2HighOrderQCumulant(inputFirstRunFileName.Data());
  for (int i=0; i<4; i++)
  {
    gr[i+2] = (TGraphErrors*) grHOQC[i];
  }
  // LYZ
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TProfile *prRefMult = (TProfile*) firun1->Get("prRefMult");
  TProfile *prQ2x = (TProfile*) firun1->Get("prQ2x");
  TProfile *prQ2y = (TProfile*) firun1->Get("prQ2y");
  TProfile *prQ2ModSq = (TProfile*) firun1->Get("prQ2ModSq");
  // TFile *fi_fixedGFS = new TFile("FirstRun_fixedGFSum.root","read");
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile*) firun1->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile*) firun1->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile*) firun1->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile*) firun1->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }
  double dChi2[ncent]={0.}, dChi2Pro[ncent] = {0.};
  double v2LYZInt[ncent]={0.}, v2eLYZInt[ncent]={0.};
  double v2LYZIntPro[ncent]={0.}, v2eLYZIntPro[ncent]={0.};
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
    if (thetacount!=0) v2int /= (float)thetacount; // refmult
    else {v2int = 0.;}
    
    float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
    float Q2xmean = prQ2x->GetBinContent(ic+1);
    float Q2ymean = prQ2y->GetBinContent(ic+1);
    float chi2 = v2int/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int,2));
    
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

    v2LYZInt[ic] = v2int;
    dChi2[ic] = chi2;
    v2eLYZInt[ic] = err2mean;

  } // end of V2RP calculation
  
  // Product
  cout << "Chi = ";
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
      if (thetacount!=0) v2int /= (float)thetacount; // refmult
      else {v2int = 0.;}
      
      float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
      float Q2xmean = prQ2x->GetBinContent(ic+1);
      float Q2ymean = prQ2y->GetBinContent(ic+1);
      float chi2 = v2int/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int,2));
      cout << sqrt(chi2) << ", ";
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

      v2LYZIntPro[ic] = v2int;
      dChi2Pro[ic] = chi2;
      v2eLYZIntPro[ic] = err2mean;

    } // end of V2RP calculation    
  } 
  cout << endl;
  gr[6] = new TGraphErrors(ncent, X, v2LYZInt, errX, v2eLYZInt);
  gr[7] = new TGraphErrors(ncent, X, v2LYZIntPro, errX, v2eLYZIntPro);

  // v22 with eta-gap
  Double_t v22Gap[ncent], v22eGap[ncent];
  TProfile *hv22Gap[ncent];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22Gap[icent] = (TProfile*)firun1->Get(Form("hv22Gap_%i",icent));
    term cor2Gap = term(hv22Gap[icent]);
    v22Gap[icent] = sqrt(cor2Gap.mVal);
    v22eGap[icent] = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
  }
  gr[8] = new TGraphErrors(ncent, X, v22Gap, errX, v22eGap);

  for (int i=0; i<nmethod; i++)
  {
    gr[i]->RemovePoint(0);
    gr[i]->SetTitle(title[i].Data());
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->SetMarkerSize(markerSize);
    gr[i]->GetXaxis()->SetTitle("centrality, %");
    gr[i]->GetYaxis()->SetTitle("v_{2}");
    gr[i]->SetDrawOption("P PLC PMC");
  }

  vector<TGraphErrors*> vGr;
  // vGr.push_back(gr[ratioToMethod]);
  for (int i=0; i<nmethod; i++)
  {
    // if (i==ratioToMethod) continue;
    vGr.push_back(gr[i]);
  }
  // TCanvas *can = (TCanvas*)DrawTGraph(vGr,"",0.48, 1.52, 0, 60, -0.005, 0.1,
  //                                     // 0.65, 0.05, 0.9, 0.5,
  //                                     0.2, 0.45, 0.4, 0.88,
  //                                     "UrQMD, Au+Au at #sqrt{s_{NN}}=7.7GeV", Form("Ch. hadrons, %1.1f<p_{T}<%1.1f GeV/c",minptRF,maxptRF));
  // can->SetName("IntFlow");
  // can->SaveAs("IntFlow_UrQMD_7.7.pdf");
  return vGr;
}