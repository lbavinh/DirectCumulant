#include "PlotV2LYZ.C"
#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
#include "PlotV2HighOrderQCumulant.C"
#include "DrawTGraphImp.C"

vector<TGraphErrors*>* PlotV2DifferentialChargedHadrons(TString inputFirstRunFileName = "FirstRun_AMPT15_11.5.root", TString inputSecondRunFileName = "SecondRun_AMPT15_11.5.root")
{

  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const int ratioToMethod = 4;
  const double J1rootJ0 = 0.519147;
  double X[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const double errX[npt] = {0.};
  bool bUseProduct = 1;
  Int_t nmethod = 7;
  TString title[]={"v_{2}{#Psi_{2,TPC}}","v_{2}{SP}","v_{2}{2,#eta-gap}","v_{2}{2}","v_{2}{4}","v_{2}{LYZ, Sum}","v_{2}{LYZ, Prod.}"};
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[ncent][nmethod];
  TFile *firun1 = new TFile(inputFirstRunFileName.Data(),"read");
  TFile *firun2 = new TFile(inputSecondRunFileName.Data(),"read");
  auto *prV2EP3D = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");
  auto *prV2SP3D = (TProfile3D*) firun2->Get("prV2ScalarProduct");
  for (int i = 0; i< ncent; i++)
  {
    TProfile *prV2EPInt = PlotV2EPDifferentialVersusPt(prV2EP3D,bin_cent[i],bin_cent[i+1]-1,eta_cut);
    TProfile *prV2SPInt = PlotV2SPDifferentialVersusPt(prV2SP3D,bin_cent[i],bin_cent[i+1]-1,eta_cut);
    graph[i][0] = Converter(prV2EPInt);
    graph[i][1] = Converter(prV2SPInt);  
  }
  
  // QCumulant

  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  // v22 with eta-gap
  TProfile *hv22Gap[ncent];
  TProfile *hv22ptGap[ncent][npt][npid];
  TProfile *hcov22primeGap[ncent][npt][npid];  

  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)firun1->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)firun1->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)firun1->Get(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)firun1->Get(Form("hv22Gap_%i",icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv22pt[icent][ipt][id]=(TProfile*)firun1->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)firun1->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)firun1->Get(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id));
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

  for (int icent=0;icent<ncent;icent++){
    for (int ipt=0;ipt<npt;ipt++){
      for (int id=0;id<1;id++){
        hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id+4]);
        hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id+4]);
        hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id+4]);
        hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id+4]);
        hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id+4]);
        hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id+4]);
        hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id+4]);
        hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id+4]);
        hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id+4]);
      }
    }
  }

  double v2Dif[3][ncent][1][npt], v2eDif[3][ncent][1][npt];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(hv22[icent]);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    // 2QC Gapped
    term cor2Gap = term(hv22Gap[icent]);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    for (int id=0;id<1;id++){ // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        // vPt.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
        // ePt.push_back(0);

        // v22
        term cor2red = term(hv22pt[icent][ipt][id]);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        v2Dif[1][icent][id][ipt] = v22Dif;
        v2eDif[1][icent][id][ipt] = ev22Dif;
        
        // v24
        term cor4red = term(hv24pt[icent][ipt][id]);
        double cov24prime = Covariance(hcov24prime[icent][ipt][id],hv22[icent],hv24pt[icent][ipt][id]);
        double cov42prime = Covariance(hcov42prime[icent][ipt][id],hv24[icent],hv22pt[icent][ipt][id]);
        double cov44prime = Covariance(hcov44prime[icent][ipt][id],hv24[icent],hv24pt[icent][ipt][id]);
        double cov2prime4prime = Covariance(hcov2prime4prime[icent][ipt][id],hv22pt[icent][ipt][id],hv24pt[icent][ipt][id]);
        double v24Dif = (2.*cor2.mVal*cor2red.mVal-cor4red.mVal)*pow(v24,-3);
        double ev24Dif = sqrt( pow(v24,-14)
            * (pow(2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal,2.)
            * cor2.mMSE
            + 9./16*pow(2.*cor2.mVal*cor2red.mVal-cor4red.mVal,2.)*cor4.mMSE
            + 4*pow(cor2.mVal,2)*pow(v24,8)*cor2red.mMSE
            + pow(v24,8)*cor4red.mMSE
            - 1.5*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov24
            - 4*cor2.mVal*pow(v24,4)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov22prime
            + 2*pow(v24,4)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov24prime
            + 3*cor2.mVal*pow(v24,4)*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * cov42prime
            - 1.5*pow(v24,4)*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * cov44prime
            - 4*cor2.mVal*pow(v24,8)*cov2prime4prime));
        v2Dif[2][icent][id][ipt] = v24Dif;
        v2eDif[2][icent][id][ipt] = ev24Dif;

        // v22 Gapped
        term cor2redGap = term(hv22ptGap[icent][ipt][id]);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(hcov22primeGap[icent][ipt][id],hv22Gap[icent],hv22ptGap[icent][ipt][id]);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        v2Dif[0][icent][id][ipt] = v22DifGap;
        v2eDif[0][icent][id][ipt] = ev22DifGap;
      }
    }
    graph[icent][2] = new TGraphErrors(npt, X, v2Dif[0][icent][0], errX, v2eDif[0][icent][0]); // v2{2}
    graph[icent][3] = new TGraphErrors(npt, X, v2Dif[1][icent][0], errX, v2eDif[1][icent][0]); // v2{4}
    graph[icent][4] = new TGraphErrors(npt, X, v2Dif[2][icent][0], errX, v2eDif[2][icent][0]); // v2{2,eta-gap}
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
  


  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];

  TProfile *prReDenomPro[thetabins];
  TProfile *prImDenomPro[thetabins];
  TProfile *prReNumerPro[thetabins][ncent];
  TProfile *prImNumerPro[thetabins][ncent];

  for (int i = 0; i < thetabins; i++)
  {
    prReDenom[i] = (TProfile*) firun2->Get(Form("prReDenom_theta%i",i));
    prImDenom[i] = (TProfile*) firun2->Get(Form("prImDenom_theta%i",i));

    for (int j = 0; j < ncent; j++)
    {
      prReNumer[i][j] = (TProfile*) firun2->Get(Form("prReNumer_theta%i_cent%i", i, j));
      prImNumer[i][j] = (TProfile*) firun2->Get(Form("prImNumer_theta%i_cent%i", i, j));
    }
    if (bUseProduct)
    {
      prReDenomPro[i] = (TProfile*) firun2->Get(Form("prReDenomPro_theta%i", i));
      prImDenomPro[i] = (TProfile*) firun2->Get(Form("prImDenomPro_theta%i", i));

      for (int j = 0; j < ncent; j++)
      {
        prReNumerPro[i][j] = (TProfile*) firun2->Get(Form("prReNumerPro_theta%i_cent%i", i, j));
        prImNumerPro[i][j] = (TProfile*) firun2->Get(Form("prImNumerPro_theta%i_cent%i", i, j));
      }    
    }   
  }
  TProfile *prMultPOI[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    prMultPOI[ic] = (TProfile*) firun2->Get(Form("prMultPOI_cent%i",ic));
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

  // Differential v2 LYZ Sum
  double v2diff[ncent][npt]={0.};
  double v2diffe[ncent][npt]={0.};
  double v2diff_check[ncent][npt][thetabins]={{{0.}}};
  for (int ic = 0; ic < ncent; ic++)
  {
    double thetacount = 0.;
    for (int thetabin = 0; thetabin < thetabins; thetabin++)
    {
      if (dVtheta[ic][thetabin] != 0)
      {
        thetacount++;
        double re = prReDenom[thetabin]->GetBinContent(ic+1);
        double im = prImDenom[thetabin]->GetBinContent(ic+1);
        TComplex cDenominator = TComplex(re, im);
        if (cDenominator.Rho()==0) {
          cerr<<"WARNING: modulus of cDenominator is zero" << "Cent:" << bin_cent[ic] << "-"<< bin_cent[ic+1] <<"%, Theta=" << theta[thetabin] <<endl;
        }
        
        for (int ipt = 0; ipt < npt; ipt++)
        {
          double reNum = prReNumer[thetabin][ic]->GetBinContent(ipt+1);
          double imNum = prImNumer[thetabin][ic]->GetBinContent(ipt+1);
          TComplex cNumeratorPOI = TComplex(reNum, imNum);
          if (cDenominator.Rho()!=0) {
            double reRatio = (cNumeratorPOI/cDenominator).Re();
            double dVetaPOI = reRatio * dVtheta[ic][thetabin];
            v2diff[ic][ipt] += dVetaPOI;
            v2diff_check[ic][ipt][thetabin] = dVetaPOI;
          }
        }
      }
    }
    double neve = prReDenom[0]->GetBinEntries(ic+1);
    /* Computation of statistical error bars on the average estimates */
    double temp = 0.;
    double arg[thetabins];
    for(int k1=0; k1<thetabins; k1++)
    {
      // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
      arg[k1] = theta[k1];

      /* Loop over the theta angles, to compute the statistical error */
      temp += (exp(sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
      exp(-sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
    }
    for (int ipt = 0; ipt < npt; ipt++)
    {    
      v2diff[ic][ipt] /= thetacount;
      double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
      v2diffe[ic][ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0;
    }
  } // end of Diff LYZ Sum

  // Differential v2 LYZ Pro
  double v2diffPro[ncent][npt]={0.};
  double v2diffePro[ncent][npt]={0.};
  double v2diff_checkPro[ncent][npt][thetabins]={{{0.}}};
  if (bUseProduct){
  for (int ic = 0; ic < ncent; ic++)
  {
    double thetacount = 0.;
    for (int thetabin = 0; thetabin < thetabins; thetabin++)
    {
      if (dVthetaPro[ic][thetabin] != 0)
      {
        thetacount++;
        double re = prReDenomPro[thetabin]->GetBinContent(ic+1);
        double im = prImDenomPro[thetabin]->GetBinContent(ic+1);
        TComplex cDenominator = TComplex(re, im);
        if (cDenominator.Rho()==0) {
          cerr<<"WARNING: modulus of cDenominator (Product) is zero" << "Cent:" << bin_cent[ic] << "-"<< bin_cent[ic+1] <<"%, Theta=" << theta[thetabin] <<endl;
        }
        
        for (int ipt = 0; ipt < npt; ipt++)
        {
          double reNum = prReNumerPro[thetabin][ic]->GetBinContent(ipt+1);
          double imNum = prImNumerPro[thetabin][ic]->GetBinContent(ipt+1);
          TComplex cNumeratorPOI = TComplex(reNum, imNum);
          if (cDenominator.Rho()!=0) {
            double reRatio = (cNumeratorPOI/cDenominator).Re();
            double dVetaPOI = reRatio * dVthetaPro[ic][thetabin];
            v2diffPro[ic][ipt] += dVetaPOI;
            v2diff_checkPro[ic][ipt][thetabin] = dVetaPOI;
          }
        }
      }
    }
    double neve = prReDenomPro[0]->GetBinEntries(ic+1);
    /* Computation of statistical error bars on the average estimates */
    double temp = 0.;
    double arg[thetabins];
    for(int k1=0; k1<thetabins; k1++)
    {
      // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
      arg[k1] = theta[k1];

      /* Loop over the theta angles, to compute the statistical error */
      temp += (exp(sqr(rootJ0/dChi2Pro[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
      exp(-sqr(rootJ0/dChi2Pro[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
    }
    for (int ipt = 0; ipt < npt; ipt++)
    {    
      v2diffPro[ic][ipt] /= thetacount;
      double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
      v2diffePro[ic][ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0; // 
    }
  }} // end of Diff LYZ Product

  for (int ic = 0; ic < ncent; ic++)
  {
    graph[ic][5] = new TGraphErrors(npt, X, v2diff[ic], errX, v2diffe[ic]);
    graph[ic][6] = new TGraphErrors(npt, X, v2diffPro[ic], errX, v2diffePro[ic]);
  }

  for (int ic = 0; ic < ncent; ic++)
  {
    for (int i=0; i<nmethod; i++)
    {
    // graph[ic][i]->RemovePoint(0);
    graph[ic][i]->SetTitle(title[i].Data());
    graph[ic][i]->SetMarkerStyle(markerStyle[i]);
    graph[ic][i]->SetMarkerSize(markerSize);
    graph[ic][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    graph[ic][i]->GetYaxis()->SetTitle("v_{2}");
    graph[ic][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    vGr[ic].push_back(graph[ic][ratioToMethod]);
    // for (int i=0; i<nmethod; i++)
    // {
    //   if (i==ratioToMethod) continue;
    //   vGr[ic].push_back(graph[ic][i]);
    // }
    vGr[ic].push_back(graph[ic][5]);
    vGr[ic].push_back(graph[ic][6]);
  TCanvas *can = (TCanvas*)DrawTGraph(vGr[ic],Form("%.0f-%.0f%%",bin_cent[ic],bin_cent[ic+1]),0.89, 1.11, minpt, 2.8, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.45, 0.4, 0.88,
                                      "AMPT, #sigma_{p}=1.5mb, Au+Au at #sqrt{s_{NN}}=11.5GeV", Form("Ch. hadrons, |#eta|<%1.1f",eta_cut));
  can->SetName(Form("%.0f-%.0f%%",bin_cent[ic],bin_cent[ic+1]));
  can->SaveAs(Form("DiffFlow_AMPT_11.5_vs_v2LYZ_%.0f-%.0f%%.pdf",bin_cent[ic],bin_cent[ic+1]));
  }


  return vGr;
}