#include "Func_StatErrCalc.C"
#include "FlowLeeYangZeros.C"
#define sqr(x) ((x)*(x))


void PlotV2LYZEP(TString inputFileName1 = "FirstRun.root", TString inputFileName2 = "ThirdRun.root")
{
  bUseProduct = 0;
  bool bDebug = 1;
  const int markerStyle[]={25,20,28,27,23,25,26};
  const float markerSize = 2.0;
  const TString methodName[]={"MC","EP","2,QC","4,QC","LYZ (Sum)", "LYZ, EP","LYZ (Prod.)"};
  const int excludeMethod = 1;
  std::pair<double,double> ratioRange = {0.67,1.23};
  TString label = "AMPT, #sigma_{p}=1.5 mb, Au+Au, #sqrt{s_{NN}}=7.7 GeV";
  TFile *fi1 = new TFile(inputFileName1.Data(),"read");

  // const int ncent = 9;
  // const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
  // const int thetabins = 5;
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  const double J1rootJ0 = 0.519147;
  // const int npt = 12;
  // const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  // const double rootJ0 = 2.4048256;

  TProfile *HRes = (TProfile*) fi1->Get("HRes");
  TProfile *hv2MC = (TProfile*) fi1->Get("hv2MC");

  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TProfile *prRefMult = (TProfile*) fi1->Get("prRefMult");
  TProfile *prQ2x = (TProfile*) fi1->Get("prQ2x");
  TProfile *prQ2y = (TProfile*) fi1->Get("prQ2y");
  TProfile *prQ2ModSq = (TProfile*) fi1->Get("prQ2ModSq");
  // TFile *fi_fixedGFS = new TFile("FirstRun_fixedGFSum.root","read");
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile*) fi1->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile*) fi1->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      // prReGthetaSum[i][j] = (TProfile*) fi_fixedGFS->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      // prImGthetaSum[i][j] = (TProfile*) fi_fixedGFS->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile*) fi1->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile*) fi1->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }
  
  TFile *fi2 = new TFile(inputFileName2.Data(),"read");
  TProfile *hv2EP = (TProfile*) fi2->Get("hv2EP");
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
    prReDenom[i] = (TProfile*) fi2->Get(Form("prReDenom_theta%i",i));
    prImDenom[i] = (TProfile*) fi2->Get(Form("prImDenom_theta%i",i));

    for (int j = 0; j < ncent; j++)
    {
      prReNumer[i][j] = (TProfile*) fi2->Get(Form("prReNumer_theta%i_cent%i", i, j));
      prImNumer[i][j] = (TProfile*) fi2->Get(Form("prImNumer_theta%i_cent%i", i, j));
    }
    if (bUseProduct)
    {
      prReDenomPro[i] = (TProfile*) fi2->Get(Form("prReDenomPro_theta%i", i));
      prImDenomPro[i] = (TProfile*) fi2->Get(Form("prImDenomPro_theta%i", i));

      for (int j = 0; j < ncent; j++)
      {
        prReNumerPro[i][j] = (TProfile*) fi2->Get(Form("prReNumerPro_theta%i_cent%i", i, j));
        prImNumerPro[i][j] = (TProfile*) fi2->Get(Form("prImNumerPro_theta%i_cent%i", i, j));
      }    
    }   
  }
  TProfile *prMultPOI[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    prMultPOI[ic] = (TProfile*) fi2->Get(Form("prMultPOI_cent%i",ic));
  }
  TProfile *hv2MCpt[ncent];
  TProfile *hv2EPpt[ncent];

  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2EPpt[icent] = (TProfile*) fi2->Get(Form("hv2EPpt_%i", icent));
    hv2MCpt[icent] = (TProfile*) fi2->Get(Form("hv2MCpt_%i", icent));
  } // end of loop over centrality classes

  // Test LYZ, RP
  TProfile *hv2LYZEP = (TProfile*) fi2->Get("hv2LYZEP");
  TProfile *hv2LYZEPpt[ncent];
  for (int icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv2LYZEPpt[icent] = (TProfile*) fi2->Get(Form("hv2LYZEPpt_%i", icent));
  } // end of loop over centrality classes


  if (bDebug){
    cout << "Resolution:" << endl;
    GetRes(HRes);
    cout << "MultMean:" << endl;
    GetMultMean(prRefMult);
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


  if (bDebug){
    cout << "const double chisq[" << ncent << "] = {";
    for (int ic = 0; ic < ncent-1; ic++)
    {
      cout << dChi2[ic] <<", ";
    }
    cout << dChi2[ncent-1] << "};" << endl;

    cout << "const double chisqPRO[" << ncent << "] = {";
    for (int ic = 0; ic < ncent-1; ic++)
    {
      cout << dChi2Pro[ic] <<", ";
    }
    cout << dChi2Pro[ncent-1] << "};" << endl;

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


  if (bDebug)
  {
    cout << "// ====== Sum ====== //" << endl;
    // Cross check integrated flow - correct!
    for (int ic = 0; ic < ncent; ic++)
    {
      float refmult = prRefMult->GetBinContent(ic+1);
      for (int thetabin = 0; thetabin < thetabins; thetabin++)
      {
        double integratedFlow = 0;
        double denominator = 0;
        for (int ipt = 0; ipt < npt; ipt++)
        {
          double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
          integratedFlow += v2diff_check[ic][ipt][thetabin] * rpmult;
          denominator += rpmult;
        }
        if (denominator != 0) integratedFlow /= denominator;
        cout <<"cent: "<< ic << " " <<dVtheta[ic][thetabin]/refmult << "\t" << integratedFlow << endl;//refmult
      }
    }
    cout << "// ====== Product ====== //" << endl;
    for (int ic = 0; ic < ncent; ic++)
    {
      float refmult = prRefMult->GetBinContent(ic+1);
      for (int thetabin = 0; thetabin < thetabins; thetabin++)
      {
        double integratedFlow = 0;
        double denominator = 0;
        for (int ipt = 0; ipt < npt; ipt++)
        {
          double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
          integratedFlow += v2diff_checkPro[ic][ipt][thetabin] * rpmult;
          denominator += rpmult;
        }
        if (denominator != 0) integratedFlow /= denominator;
        cout <<"cent: "<< ic << " " <<dVthetaPro[ic][thetabin]/refmult << "\t" << integratedFlow << endl;
      }
    }

  }

  double v2diffMC[ncent][npt] = {0.}, v2diffeMC[ncent][npt] = {0.}, v2diffEP[ncent][npt] = {0.}, v2diffeEP[ncent][npt] = {0.}, v2diffLYZEP[ncent][npt] = {0.}, v2ediffLYZEP[ncent][npt] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      v2diffMC[ic][ipt] = hv2MCpt[ic]->GetBinContent(ipt+1);
      v2diffeMC[ic][ipt] = hv2MCpt[ic]->GetBinError(ipt+1);
      v2diffEP[ic][ipt] = hv2EPpt[ic]->GetBinContent(ipt+1);
      v2diffeEP[ic][ipt] = hv2EPpt[ic]->GetBinError(ipt+1);
      v2diffLYZEP[ic][ipt] = hv2LYZEPpt[ic]->GetBinContent(ipt+1);
      v2ediffLYZEP[ic][ipt] = hv2LYZEPpt[ic]->GetBinError(ipt+1);

    }
  }

  // QC

  // Input hist
  // TProfile for reference flow
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt[ncent][npt];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>
  char hname[400];
  double stats[6]; // stats of TProfile
  // Get TProfile histograms from ROOTFile
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv22_%i",icent);
    hv22[icent] = (TProfile*)fi1->Get(hname);
    sprintf(hname,"hv24_%i",icent);
    hv24[icent] = (TProfile*)fi1->Get(hname);
    sprintf(hname,"hcov24_%i",icent);
    hcov24[icent] = (TProfile*)fi1->Get(hname);

    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
        sprintf(hname,"hv22pt_%i_%i",icent,ipt);
        hv22pt[icent][ipt]=(TProfile*)fi1->Get(hname);
        sprintf(hname,"hv24pt_%i_%i",icent,ipt);
        hv24pt[icent][ipt]=(TProfile*)fi1->Get(hname);
        sprintf(hname,"hcov22prime_%i_%i",icent,ipt);
        hcov22prime[icent][ipt]=(TProfile*)fi1->Get(hname);
        sprintf(hname,"hcov24prime_%i_%i",icent,ipt);
        hcov24prime[icent][ipt]=(TProfile*)fi1->Get(hname);
        sprintf(hname,"hcov42prime_%i_%i",icent,ipt);
        hcov42prime[icent][ipt]=(TProfile*)fi1->Get(hname);
        sprintf(hname,"hcov44prime_%i_%i",icent,ipt);
        hcov44prime[icent][ipt]=(TProfile*)fi1->Get(hname);
        sprintf(hname,"hcov2prime4prime_%i_%i",icent,ipt);
        hcov2prime4prime[icent][ipt]=(TProfile*)fi1->Get(hname);
    } // end of loop over pt bin
  } // end of loop over centrality classes

  //==========================================================================================================================
  // Filling pT bin
  double pt[ncent][npt];
  double ept[ncent][npt]={{0}}; // error bin pT = 0.0
  for (int icent=0; icent<ncent; icent++){
    for (int ipt=0; ipt<npt; ipt++){
      pt[icent][ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
    }
  }
  //==========================================================================================================================

  double v2cent[2][ncent], v2centE[2][ncent];
  double v2pt[2][ncent][npt], v2ptE[2][ncent][npt];

  // ofstream ofile2("v2int.txt");

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // Reference flow calculation


    double v22int;  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
    double v22intE; // Standard error of integrated v_{2}{2,QC}
    double cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
    double cor2E;   // stat. err. of 2-particle correlations, s(<<2>>)

    double v24int;  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
    double v24intE; // Standard error of integrated v_{2}{4,QC}
    double cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
    double cor4E;   // error of <<4>>

    double sumw2cor2;    // sumw2 of <2>
    double sumwcor2;     // sumw of <2>
    double sumw2cor4;    // sumw2 of <4>
    double sumwcor4;     // sumw of <4>

    double sumwcor24;    // sum(w<2>,w<4>)
    double cov24;        // Cov(<2>,<4>)


    // v2{2,QC}
    // estimate of the 2-particle reference flow (C.22)
    cor2 = hv22[icent] -> GetBinContent(1);  // <<2>>
    v22int = Vn2(cor2);
    // statistical error of the 2-particle reference flow estimate (C.26)
    cor2E = sx(hv22[icent]);
    hv22[icent] -> GetStats(stats);
    sumwcor2 = stats[0];
    sumw2cor2 = stats[1];
    v22intE = Evn2(cor2,cor2E,sumwcor2,sumw2cor2);
    //=============================================
    // v2{4,QC}
    // estimate of the 4-particle reference flow (C.27)
    cor4 = hv24[icent]->GetBinContent(1);  // <<4>>
    v24int = Vn4(cor2,cor4);
    // statistical error of the 4-particle reference flow estimate (C.28)
    cor4E = sx(hv24[icent]);
    hv24[icent] -> GetStats(stats);
    sumwcor4 = stats[0];
    sumw2cor4 = stats[1];
    // calculate covariance of <2> and <4>
    cov24 = Cov(hcov24[icent],hv22[icent],hv24[icent]);
    sumwcor24 = Sumwxwy(hcov24[icent]);
    v24intE = Evn4(cor2,cor2E,sumwcor2,sumw2cor2,
                  cor4,cor4E,sumwcor4,sumw2cor4,
                  cov24,sumwcor24);

    // ofile2 << icent*10<<"-"<< (icent+1)*10<<" "<< v22intE << " " << v24intE << endl;

    v2cent[0][icent] = v22int;
    v2cent[1][icent] = v24int;

    v2centE[0][icent] = v22intE;
    v2centE[1][icent] = v24intE;

    //==========================================================================================================================

    // Differential flow calculation


    double v2MCpt[npt]; // v2 in given pT bin
    double ev2MCpt[npt]; // standard error of v2 in given pT bin
  
    double cor2Red[npt];         // Differential 2nd order cumulant d_{2}{2} = <<2'>>
    double cor2RedE[npt];        // Error of <<2'>>
    double v22dif[npt];      // Differential elliptic flow v'_{2}{2} extracted from 2nd order cumulants
                            // v'_{2}{2} = d_{2}{2} / sqrt( c_{2}{2} )
    double v22difE[npt];     // Error of v'_{2}{2}
    
    double cor4Red[npt];    // Reduced average all-event 4-particle correlation <<4'>>
    double cor4RedE[npt];   // Error of <<4'>>
    double v24dif[npt];      // Differential elliptic flow v'_{2}{4} extracted from 4th order cumulants
                            // v'_{2}{4} = -d_{2}{4} / pow( -c_{2}{4} , 3/4 )
    double v24difE[npt];     // Error of v'_{2}{4}

    double sumwcor22prime[npt];        // sum(w(<2>)*w(<2'>))
    double cov22prime[npt];            // Cov(<2>,<2'>)
    double sumwcor24prime[npt];        // sum(w(<2>)*w(<4'>))
    double cov24prime[npt];            // Cov(<2>,<4'>)
    double sumwcor42prime[npt];        // sum(w(<4>)*w(<2'>))
    double cov42prime[npt];            // Cov(<4>,<2'>)
    double sumwcor44prime[npt];        // sum(w(<4>)*w(<4'>))
    double cov44prime[npt];            // Cov(<4>,<4'>)
    double sumwcor2prime4prime[npt];   // sum(w(<2'>)*w(<4'>))
    double cov2prime4prime[npt];       // Cov(<2'>,<4'>)

    double sumw2cor2red[npt]; // sumw2 of <2'>
    double sumwcor2red[npt];  // sumw of <2'>    
    double sumw2cor4red[npt]; // sumw2 of <4'>
    double sumwcor4red[npt];  // sumw of <4'>

    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      
      // 2-particle correlations
      // estimate of the 2-particle differential flow (C.41)
      cor2Red[ipt] = hv22pt[icent][ipt]->GetBinContent(1);
      v22dif[ipt] = Vn2Dif(cor2Red[ipt],cor2);
      v2pt[0][icent][ipt] = v22dif[ipt];
      // statistical error of the 2-particle differential flow estimate (C.42)
      cor2RedE[ipt] = sx(hv22pt[icent][ipt]);
      hv22pt[icent][ipt] -> GetStats(stats);
      sumwcor2red[ipt] = stats[0];
      sumw2cor2red[ipt] = stats[1];

      // calculate covariance of <2> and <2'>
      cov22prime[ipt] = Cov(hcov22prime[icent][ipt],hv22[icent],hv22pt[icent][ipt]);
      sumwcor22prime[ipt] = Sumwxwy(hcov22prime[icent][ipt]);
      v22difE[ipt] = Evn2dif(cor2, cor2E, sumwcor2, sumw2cor2,
                             cor2Red[ipt], cor2RedE[ipt], sumwcor2red[ipt],sumw2cor2red[ipt],
                             cov22prime[ipt], sumwcor22prime[ipt]);
      v2ptE[0][icent][ipt] = v22difE[ipt];
      // 4-particle correlations
      // estimate of the 4-particle differential flow (C.45)
      cor4Red[ipt] = hv24pt[icent][ipt]->GetBinContent(1);
      v24dif[ipt] = Vn4Dif(cor2Red[ipt], cor2, cor4Red[ipt], cor4);
      v2pt[1][icent][ipt] = v24dif[ipt];
      // statistical error of the 4-particle differential flow estimate (C.46)
      cor4RedE[ipt] = sx(hv24pt[icent][ipt]);
      hv24pt[icent][ipt] -> GetStats(stats);
      sumwcor4red[ipt] = stats[0];
      sumw2cor4red[ipt] = stats[1];

      // calculate covariance of <2> and <4'>
      cov24prime[ipt] = Cov(hcov24prime[icent][ipt],hv22[icent],hv24pt[icent][ipt]);
      sumwcor24prime[ipt] = Sumwxwy(hcov24prime[icent][ipt]);

      // calculate covariance of <4> and <2'>
      cov42prime[ipt] = Cov(hcov42prime[icent][ipt],hv24[icent],hv22pt[icent][ipt]);
      sumwcor42prime[ipt] = Sumwxwy(hcov42prime[icent][ipt]);

      // calculate covariance of <4> and <4'>
      cov44prime[ipt] = Cov(hcov44prime[icent][ipt],hv24[icent],hv24pt[icent][ipt]);
      sumwcor44prime[ipt] = Sumwxwy(hcov44prime[icent][ipt]);

      // calculate covariance of <2'> and <4'>
      cov2prime4prime[ipt] = Cov(hcov2prime4prime[icent][ipt],hv22pt[icent][ipt],hv24pt[icent][ipt]);
      sumwcor2prime4prime[ipt] = Sumwxwy(hcov2prime4prime[icent][ipt]);
      v24difE[ipt] = Evn4dif(cor2, cor2E, sumwcor2, sumw2cor2,
                          cor2Red[ipt], cor2RedE[ipt], sumwcor2red[ipt], sumw2cor2red[ipt],
                          cor4, cor4E, sumwcor4, sumw2cor4,
                          cor4Red[ipt], cor4RedE[ipt], sumwcor4red[ipt], sumw2cor4red[ipt],
                          cov24, sumwcor24, cov22prime[ipt], sumwcor22prime[ipt],
                          cov2prime4prime[ipt], sumwcor2prime4prime[ipt], cov44prime[ipt], sumwcor44prime[ipt],
                          cov24prime[ipt], sumwcor24prime[ipt], cov42prime[ipt], sumwcor42prime[ipt]);
      v2ptE[1][icent][ipt] = v24difE[ipt];
    } // end of loop for all pT bin
  } // end of loop over centrality classes

  TH1F *hV22 = new TH1F("hV22","",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hV22->SetBinContent(ic+1,v2cent[0][ic]);
    hV22->SetBinError(ic+1,v2centE[0][ic]);
  }

  TH1F *hV24 = new TH1F("hV24","",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hV24->SetBinContent(ic+1,v2cent[1][ic]);
    hV24->SetBinError(ic+1,v2centE[1][ic]);
  }
    // Calculate ratio
  double v2Diff[7][ncent][npt], v2eDiff[7][ncent][npt];
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      v2Diff[0][ic][ipt] = v2diffMC[ic][ipt]; // MC
      v2Diff[1][ic][ipt] = v2diffEP[ic][ipt]; // EP
      v2Diff[2][ic][ipt] = v2pt[0][ic][ipt];  // 2QC
      v2Diff[3][ic][ipt] = v2pt[1][ic][ipt];  // 4QC
      v2Diff[4][ic][ipt] = v2diff[ic][ipt]; // LYZ, Sum
      v2Diff[6][ic][ipt] = v2diffPro[ic][ipt]; // LYZ, Pro
      v2Diff[5][ic][ipt] = v2diffLYZEP[ic][ipt]; // LYZ, EP

      v2eDiff[0][ic][ipt] = v2diffeMC[ic][ipt]; // MC
      v2eDiff[1][ic][ipt] = v2diffeEP[ic][ipt]; // EP
      v2eDiff[2][ic][ipt] = v2ptE[0][ic][ipt];  // 2QC
      v2eDiff[3][ic][ipt] = v2ptE[1][ic][ipt];  // 4QC
      v2eDiff[4][ic][ipt] = v2diffe[ic][ipt]; // LYZ, Sum
      v2eDiff[6][ic][ipt] = v2diffePro[ic][ipt]; // LYZ, Pro
      v2eDiff[5][ic][ipt] = v2diffeEP[ic][ipt]; // LYZ, Pro

    }
  }
  if (bDebug){
    cout << "v24:" << endl;
    for (int ic = 0; ic < ncent; ic++) cout << v2cent[1][ic] <<", ";
    cout << endl;
  }
  const int ratioToMethod = 3;
  double dRatio[ncent][npt][7] = {0.}, dRatioErr[ncent][npt][7] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      for (int i = 0; i < 7; i++)
      {
        dRatio[ic][ipt][i] = v2Diff[i][ic][ipt] / v2Diff[ratioToMethod][ic][ipt];
        dRatioErr[ic][ipt][i] = dRatio[ic][ipt][i] * sqrt(pow(v2eDiff[ratioToMethod][ic][ipt] / v2Diff[ratioToMethod][ic][ipt], 2) + pow(v2eDiff[i][ic][ipt] / v2Diff[i][ic][ipt], 2)); 

      }
    }
  }

  double v2Int[7][ncent], v2eInt[7][ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    
      v2Int[0][ic] = hv2MC->GetBinContent(ic+1); // MC
      v2Int[1][ic] = hv2EP->GetBinContent(ic+1); // EP
      v2Int[2][ic] = v2cent[0][ic];  // 2QC
      v2Int[3][ic] = v2cent[1][ic];  // 4QC
      v2Int[4][ic] = v2LYZInt[ic]; // LYZ, Sum
      v2Int[6][ic] = v2LYZIntPro[ic]; // LYZ, Pro
      v2Int[5][ic] = hv2LYZEP->GetBinContent(ic+1);

      v2eInt[0][ic] = hv2MC->GetBinError(ic+1); // MC
      v2eInt[1][ic] = hv2EP->GetBinError(ic+1); // EP
      v2eInt[2][ic] = v2centE[0][ic];  // 2QC
      v2eInt[3][ic] = v2centE[1][ic];  // 4QC
      v2eInt[4][ic] = v2eLYZInt[ic]; // LYZ, Sum
      v2eInt[6][ic] = v2eLYZIntPro[ic]; // LYZ, Pro
      v2eInt[5][ic] = hv2LYZEP->GetBinError(ic+1);

    
  }

  double ratioIntFlow[ncent][7] = {0.}, ratioIntFlowe[ncent][7] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int i=0; i<7; i++){
    ratioIntFlow[ic][i] = v2Int[i][ic]/v2Int[ratioToMethod][ic]; // v24
    ratioIntFlowe[ic][i] = ratioIntFlow[ic][i] * sqrt(pow( v2eInt[i][ic]/ v2Int[i][ic], 2) + pow(v2eInt[ratioToMethod][ic] / v2Int[ratioToMethod][ic], 2));
    }
  }
  //================= Drawing =========================
  gStyle->SetErrorX(0);
  TCanvas c("c","",1920,1080);
  
  c.Divide(2,1);
  // c.SetLeftMargin(0.2);
  c.cd(1);

  hv2LYZEP->SetMarkerStyle(markerStyle[5]);
  hv2LYZEP->SetMarkerSize(markerSize);
  hv2LYZEP->SetMarkerColor(kYellow+2);
  hv2LYZEP->SetLineColor(kYellow+2);

  hV22->SetMarkerStyle(28);
  hV22->SetMarkerSize(markerSize);
  hV22->SetMarkerColor(kBlack);
  hV22->SetLineColor(kBlack);

  hV24->SetMarkerStyle(27);
  hV24->SetMarkerSize(markerSize);
  hV24->SetMarkerColor(kGray+2);
  hV24->SetLineColor(kGray+2);


  TH1F *hLYZ = new TH1F(Form("hLYZ"),"",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hLYZ->SetBinContent(ic+1,v2LYZInt[ic]);
    hLYZ->SetBinError(ic+1,v2eLYZInt[ic]);
  }
  hLYZ->SetMarkerStyle(23);
  hLYZ->SetMarkerSize(markerSize);
  hLYZ->SetMarkerColor(kBlue+2);
  hLYZ->SetLineColor(kBlue+2);


  TH1F *hLYZPro;
  if (bUseProduct){
  hLYZPro = new TH1F(Form("hLYZPro"),"",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hLYZPro->SetBinContent(ic+1,v2LYZIntPro[ic]);
    hLYZPro->SetBinError(ic+1,v2eLYZIntPro[ic]);
  }
  hLYZPro->SetMarkerStyle(26);
  hLYZPro->SetMarkerSize(markerSize);
  hLYZPro->SetMarkerColor(kGreen+2);
  hLYZPro->SetLineColor(kGreen+2);
  }

  hv2EP->SetMarkerStyle(20);
  hv2EP->SetMarkerSize(markerSize);
  hv2EP->SetMarkerColor(kRed+2);
  hv2EP->SetLineColor(kRed+2);

  hv2MC->SetMarkerStyle(25);
  hv2MC->SetMarkerSize(markerSize);
  hv2MC->SetMarkerColor(kBlack);
  hv2MC->SetLineColor(kBlack);
  hv2EP->SetTitle(Form("%s;centrality, %%;v_{2}",label.Data()));
  hv2EP->GetYaxis()->SetRangeUser(0,0.1);
  hv2EP->GetXaxis()->SetRangeUser(0,60);
  // hLYZ->GetXaxis()->SetRangeUser(0,60);
  // hV22->GetXaxis()->SetRangeUser(0,60);
  // hV24->GetXaxis()->SetRangeUser(0,60);
  // hv2LYZEP->GetXaxis()->SetRangeUser(0,60);

  // hv2MC->Draw();
  hv2EP->Draw();
  hLYZ->Draw("same");
  if (bUseProduct) hLYZPro->Draw("same");
  hV22->Draw("same");
  hV24->Draw("same");
  hv2LYZEP->Draw("same");
  TLegend *leg = new TLegend(0.55,0.15,0.8,0.55);
  leg->SetBorderSize(0);
  leg->AddEntry(hv2MC,"MC","p");
  leg->AddEntry(hv2EP,"EP","p");
  leg->AddEntry(hLYZ,"LYZ (Sum)","p");
  if (bUseProduct) leg->AddEntry(hLYZPro,"LYZ (Prod.)","p");
  leg->AddEntry(hV22,"2,QC","p");
  leg->AddEntry(hV24,"4,QC","p");
  leg->AddEntry(hv2LYZEP,"LYZ,EP","p");
  // leg->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  c.cd(2);
  TH1F *hRatioInt[7];
  for (int i=0; i<6; i++)
  {
    hRatioInt[i] = new TH1F(Form("hRatioInt_%i",i),"",ncent,&bin_cent[0]);
    for (int ic=0; ic<ncent; ic++)
    {
      hRatioInt[i]->SetBinContent(ic+1,ratioIntFlow[ic][i]);
      hRatioInt[i]->SetBinError(ic+1,ratioIntFlowe[ic][i]);
    }
    hRatioInt[i]->SetMarkerStyle(markerStyle[i]);
    hRatioInt[i]->SetMarkerSize(markerSize);
    hRatioInt[i]->GetYaxis()->SetRangeUser(ratioRange.first,ratioRange.second);
    hRatioInt[i]->SetTitle(";centrality, %;Ratio to v_{2}{4}");
  }
  if (bUseProduct){
    hRatioInt[6] = new TH1F(Form("hRatioInt_5"),"",ncent,&bin_cent[0]);
    for (int ic=0; ic<ncent; ic++)
    {
      hRatioInt[6]->SetBinContent(ic+1,ratioIntFlow[ic][6]);
      hRatioInt[6]->SetBinError(ic+1,ratioIntFlowe[ic][6]);
    }
    hRatioInt[6]->SetMarkerStyle(markerStyle[6]);    
    hRatioInt[6]->SetMarkerSize(markerSize);
  }

  hRatioInt[4]->SetMarkerColor(kBlue+2);
  hRatioInt[4]->SetLineColor(kBlue+2);
  if (bUseProduct){
  hRatioInt[6]->SetMarkerColor(kGreen+2);
  hRatioInt[6]->SetLineColor(kGreen+2);
  }
  hRatioInt[2]->SetMarkerColor(kBlack);
  hRatioInt[2]->SetLineColor(kBlack);

  hRatioInt[3]->SetMarkerColor(kGray+2);
  hRatioInt[3]->SetLineColor(kGray+2);

  hRatioInt[1]->SetMarkerColor(kRed+2);
  hRatioInt[1]->SetLineColor(kRed+2);

  hRatioInt[0]->SetMarkerColor(kBlack);
  hRatioInt[0]->SetLineColor(kBlack);

  hRatioInt[5]->SetMarkerColor(kYellow+2);
  hRatioInt[5]->SetLineColor(kYellow+2);

  TH2F *hist1 = new TH2F("hist1",Form("%s;centrality, %%;Ratio to v_{2}{4}",label.Data()),6,0,60,1,ratioRange.first,ratioRange.second);
  hist1->Draw();
  for (int i=1; i<6; i++) if (i!=ratioToMethod)hRatioInt[i]->Draw("P same");
  if (bUseProduct) hRatioInt[6]->Draw("P same");
  TLine lineOne1;
  lineOne1.SetLineStyle(2);
  lineOne1.DrawLine(0,1.,60,1.);
  TLegend *leg3 = new TLegend(0.15,0.15,0.35,0.35);
  leg3->SetBorderSize(0);
  for (int i=1; i<6; i++){if (i!=ratioToMethod) leg3->AddEntry(hRatioInt[i],methodName[i].Data(),"p");}
  if (bUseProduct) leg3->AddEntry(hRatioInt[6],"LYZ (Prod.)","p");
  leg3->Draw();
  
  c.SaveAs("Flow.pdf");
  c.SaveAs("Flow.png");
  //================= Drawing =========================
  TCanvas c2;
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title->SetBorderSize(0);
  title->SetFillColor(0);
  // title->SetTextFont(textFont);
  // title->SetTextSize(2.);
  title->Draw();
  // int centrality = 4; // 10-20%
  // c2.SetLeftMargin(0.13);
  TString legHeader[] = {"0-5%","5-10%","10-15%","15-20%","20-25%","25-30%","30-35%","35-40%","40-45%","45-50%","50-55%","55-60%","60-65%", "65-70%","70-75%","75-80%"};
  c2.Divide(3,2,0,0);
  for (int centrality = 1; centrality < 7; centrality++){
  c2.cd(centrality);
  TH1F *hLYZDiff = new TH1F(Form("hLYZDiff_%i",centrality),"",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiff->SetBinContent(ipt+1,v2diff[centrality][ipt]);
    hLYZDiff->SetBinError(ipt+1,v2diffe[centrality][ipt]);
  }
  hLYZDiff->SetMarkerStyle(23);
  hLYZDiff->SetMarkerColor(kBlue+2);
  hLYZDiff->SetLineColor(kBlue+2);
  hLYZDiff->GetXaxis()->SetLimits(-0.1,3.6);

  TH1F *hLYZDiffPro;
  if (bUseProduct){
  hLYZDiffPro = new TH1F(Form("hLYZDiffPro_%i",centrality),"",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiffPro->SetBinContent(ipt+1,v2diffPro[centrality][ipt]);
    hLYZDiffPro->SetBinError(ipt+1,v2diffePro[centrality][ipt]);
  }
  hLYZDiffPro->SetMarkerStyle(26);
  hLYZDiffPro->SetMarkerColor(kGreen+2);
  hLYZDiffPro->SetLineColor(kGreen+2);
  hLYZDiffPro->GetXaxis()->SetLimits(-0.1,3.6);
  }

  TH1F *hV22Diff = new TH1F(Form("hV22Diff_%i",centrality),"",npt,&bin_pT[0]);
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hV22Diff->SetBinContent(ipt+1,v2pt[0][centrality][ipt]);
    hV22Diff->SetBinError(ipt+1,v2ptE[0][centrality][ipt]);    
  }
  hV22Diff->SetMarkerStyle(28);
  hV22Diff->SetMarkerColor(kBlack);
  hV22Diff->SetLineColor(kBlack);
  hV22Diff->GetXaxis()->SetLimits(-0.1,3.6);
  
  TH1F *hV24Diff = new TH1F(Form("hV24Diff_%i",centrality),"",npt,&bin_pT[0]);
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hV24Diff->SetBinContent(ipt+1,v2pt[1][centrality][ipt]);
    hV24Diff->SetBinError(ipt+1,v2ptE[1][centrality][ipt]);    
  }
  hV24Diff->SetMarkerStyle(27);
  hV24Diff->SetMarkerColor(kGray+2);
  hV24Diff->SetLineColor(kGray+2);
  hV24Diff->GetXaxis()->SetLimits(-0.1,3.6);



  hv2EPpt[centrality]->SetMarkerStyle(20);
  hv2EPpt[centrality]->SetMarkerColor(kRed+2);
  hv2EPpt[centrality]->SetLineColor(kRed+2);
  hv2EPpt[centrality]->GetXaxis()->SetLimits(-0.1,3.6);
  hv2MCpt[centrality]->SetMarkerStyle(25);
  hv2MCpt[centrality]->SetMarkerColor(kBlack);
  hv2MCpt[centrality]->SetLineColor(kBlack);
  hv2MCpt[centrality]->SetTitle(";p_{T}, GeV/c;v_{2}");
  hv2MCpt[centrality]->GetYaxis()->SetRangeUser(-0.01,0.26);
  hv2MCpt[centrality]->GetXaxis()->SetLimits(-0.1,3.6);
  hv2MCpt[centrality]->Draw();
  hv2EPpt[centrality]->Draw("same");
  hLYZDiff->Draw("P same");
  if (bUseProduct) hLYZDiffPro->Draw("P same");
  hV22Diff->Draw("P same");
  hV24Diff->Draw("P same");
  TLegend *leg2 = new TLegend(0.15,0.7,0.4,0.9);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[centrality].Data());
  leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ (Sum)","p");
  if (bUseProduct) leg2->AddEntry(hLYZDiffPro,"LYZ (Prod.)","p");
  leg2->AddEntry(hV22Diff,"2,QC","p");
  leg2->AddEntry(hV24Diff,"4,QC","p");
  // leg2->AddEntry(hLYZ,"LYZ","p");
  leg2->Draw();
  // c2.SaveAs(Form("DifFlow_%i.png",centrality));
  }
  c2.SaveAs(Form("DifFlow.pdf"));
  //================= Drawing =========================
  TCanvas c3("c3","",1920,1080);
  TPaveLabel* title3 = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title3->SetBorderSize(0);
  title3->SetFillColor(0);
  c3.SetLeftMargin(0.15);
  // title3->SetTextFont(textFont);
  // title3->SetTextSize(2.);
  title3->Draw();
  c3.Divide(6,2,0,0);
  // gROOT->SetStyle("Pub");
  for (int centrality = 2; centrality < 8; centrality++){
  c3.cd(centrality-1);
  TH1F *hV22Diff = new TH1F(Form("hV22Diff_%i",centrality+100),"",npt,&bin_pT[0]);
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hV22Diff->SetBinContent(ipt+1,v2pt[0][centrality][ipt]);
    hV22Diff->SetBinError(ipt+1,v2ptE[0][centrality][ipt]);    
  }
  TH1F *hV24Diff = new TH1F(Form("hV24Diff_%i",centrality+100),"",npt,&bin_pT[0]);
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hV24Diff->SetBinContent(ipt+1,v2pt[1][centrality][ipt]);
    hV24Diff->SetBinError(ipt+1,v2ptE[1][centrality][ipt]);    
  }

  hV22Diff->SetMarkerStyle(28);
  hV22Diff->SetMarkerSize(markerSize);
  hV22Diff->SetMarkerColor(kBlack);
  hV22Diff->SetLineColor(kBlack);
  hV22Diff->GetXaxis()->SetLimits(-0.1,3.6);

  hV24Diff->SetMarkerStyle(27);
  hV24Diff->SetMarkerSize(markerSize);
  hV24Diff->SetMarkerColor(kGray+2);
  hV24Diff->SetLineColor(kGray+2);
  hV24Diff->GetXaxis()->SetLimits(-0.1,3.6);



  TH1F *hLYZDiff = new TH1F(Form("hLYZDiff_%i",centrality+100),"",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiff->SetBinContent(ipt+1,v2diff[centrality][ipt]);
    hLYZDiff->SetBinError(ipt+1,v2diffe[centrality][ipt]);
  }
  hLYZDiff->SetMarkerStyle(23);
  hLYZDiff->SetMarkerSize(markerSize);
  hLYZDiff->SetMarkerColor(kBlue+2);
  hLYZDiff->SetLineColor(kBlue+2);
  hLYZDiff->GetXaxis()->SetLimits(-0.1,3.6);

  TH1F *hLYZDiffPro;
  if (bUseProduct){
  hLYZDiffPro = new TH1F(Form("hLYZDiffPro_%i",centrality+100),"",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiffPro->SetBinContent(ipt+1,v2diffPro[centrality][ipt]);
    hLYZDiffPro->SetBinError(ipt+1,v2diffePro[centrality][ipt]);
  }
  hLYZDiffPro->SetMarkerStyle(26);
  hLYZDiffPro->SetMarkerSize(markerSize);
  hLYZDiffPro->SetMarkerColor(kGreen+2);
  hLYZDiffPro->SetLineColor(kGreen+2);
  hLYZDiffPro->GetXaxis()->SetLimits(-0.1,3.6);
  }
  hv2LYZEPpt[centrality]->SetMarkerStyle(markerStyle[5]);
  hv2LYZEPpt[centrality]->SetMarkerSize(markerSize);
  hv2LYZEPpt[centrality]->SetMarkerColor(kYellow+2);
  hv2LYZEPpt[centrality]->SetLineColor(kYellow+2);
  hv2LYZEPpt[centrality]->GetXaxis()->SetLimits(-0.1,3.6);

// hV22Diff->GetXaxis()->SetRangeUser(-0.,3.6);
// hV24Diff->GetXaxis()->SetRangeUser(-0.,3.6);
// hLYZDiff->GetXaxis()->SetRangeUser(-0.,3.6);
// hLYZDiffPro->GetXaxis()->SetRangeUser(-0.,3.6);
// hv2LYZEPpt[centrality]->GetXaxis()->SetRangeUser(-0.,3.6);
// hLYZDiff->GetYaxis()->SetRangeUser(-0.01,0.26);

  hv2EPpt[centrality]->SetTitle(";p_{T}, GeV/c;v_{2}");
  hv2EPpt[centrality]->GetYaxis()->SetRangeUser(-0.01,0.26);
  hv2EPpt[centrality]->GetXaxis()->SetRangeUser(-0.1,3.6);
  // hv2EPpt[centrality]->Draw();
  TH1F *hist = new TH1F("",";p_{T}, GeV/c;v_{2}", npt, &bin_pT[0]);
  hist->GetYaxis()->SetRangeUser(-0.01,0.26);
  hist->GetXaxis()->SetRangeUser(-0.1,3.6);
  hist->Draw();

  // hLYZDiff->Draw("P same");
  if (bUseProduct) hLYZDiffPro->Draw("P same");
  hV22Diff->Draw("P same");
  hV24Diff->Draw("P same");
  // hv2MCpt[centrality]->Draw("P same");
  hv2LYZEPpt[centrality]->Draw("P same");
  TLatex tex;
  tex.DrawLatex(0.25,0.24,legHeader[centrality].Data());
  TLegend *leg2 = new TLegend(0.1,0.6,0.4,0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.05);
  // leg2->SetHeader(legHeader[centrality].Data());
  // leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  // leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ (Sum)","p");
  if (bUseProduct) leg2->AddEntry(hLYZDiffPro,"LYZ (Prod.)","p");
  leg2->AddEntry(hV22Diff,"2,QC","p");
  leg2->AddEntry(hV24Diff,"4,QC","p");
  leg2->AddEntry(hv2LYZEPpt[centrality],"LYZ, EP","p");
  if (centrality == 3)leg2->Draw();
  }
  for (int centrality = 2; centrality < 8; centrality++){
    c3.cd(centrality+5);
    TH1F *hDifRatio[7];
    for (int i = 0; i<6; i++)
    {
      hDifRatio[i] = new TH1F(Form("hDifRatio_%i_%i",centrality,i),"",npt,&bin_pT[0]);
      for (int ipt = 0; ipt < npt; ipt++)
      {
        hDifRatio[i]->SetBinContent(ipt+1,dRatio[centrality][ipt][i]);
        hDifRatio[i]->SetBinError(ipt+1,dRatioErr[centrality][ipt][1]);
      }
    hDifRatio[i]->SetTitle(";p_{T}, GeV/c;Ratio to v_{2}{4}");
    hDifRatio[i]->GetYaxis()->SetRangeUser(ratioRange.first,ratioRange.second);
    hDifRatio[i]->GetXaxis()->SetRangeUser(-0.1,3.6);
    hDifRatio[i]->SetMarkerStyle(markerStyle[i]);
    hDifRatio[i]->SetMarkerSize(markerSize);
    }
    if (bUseProduct){
      hDifRatio[6] = new TH1F(Form("hDifRatio_%i_6",centrality),"",npt,&bin_pT[0]);
      for (int ipt = 0; ipt < npt; ipt++)
      {
        hDifRatio[6]->SetBinContent(ipt+1,dRatio[centrality][ipt][6]);
        hDifRatio[6]->SetBinError(ipt+1,dRatioErr[centrality][ipt][6]);
      }
      hDifRatio[6]->SetMarkerSize(markerSize);
      hDifRatio[6]->SetMarkerStyle(markerStyle[6]);
    }
    hDifRatio[5]->SetMarkerColor(kYellow+2);
    hDifRatio[5]->SetLineColor(kYellow+2);    

    hDifRatio[4]->SetMarkerColor(kBlue+2);
    hDifRatio[4]->SetLineColor(kBlue+2);
    if (bUseProduct){
    hDifRatio[6]->SetMarkerColor(kGreen+2);
    hDifRatio[6]->SetLineColor(kGreen+2);
    }
    hDifRatio[2]->SetMarkerColor(kBlack);
    hDifRatio[2]->SetLineColor(kBlack);

    hDifRatio[3]->SetMarkerColor(kGray+2);
    hDifRatio[3]->SetLineColor(kGray+2);

    hDifRatio[1]->SetMarkerColor(kRed+2);
    hDifRatio[1]->SetLineColor(kRed+2);

    hDifRatio[0]->SetMarkerColor(kBlack);
    hDifRatio[0]->SetLineColor(kBlack);
    
    hDifRatio[2]->Draw();
    for (int i=2; i<6; i++)
    {
      if (i==excludeMethod) continue;
      if (i==4) continue;
      if (i!=ratioToMethod) hDifRatio[i]->Draw("same");
    }
    if (bUseProduct) hDifRatio[6]->Draw("same");
   
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(0.0,1.,3.6,1.);
  }
  c3.SaveAs("RatioDiffFlow.pdf");
  c3.SaveAs("RatioDiffFlow.png");
}
