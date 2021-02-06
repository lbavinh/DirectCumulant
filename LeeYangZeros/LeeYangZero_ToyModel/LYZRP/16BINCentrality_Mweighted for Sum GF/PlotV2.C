#include "Func_StatErrCalc.C"
#define sqr(x) ((x)*(x))
void GetRes(TProfile *const &pr)
{
  cout << "const double res2[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX(); i++)
  {
    cout << TMath::Sqrt(pr->GetBinContent(i+1)) <<", ";
  }
  cout <<"};" << endl;
}

void GetMultMean(TProfile *const &pr)
{
  cout << "const double dMultMean[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX(); i++)
  {
    cout << (pr->GetBinContent(i+1)) <<", ";
  }
  cout <<"};" << endl;
}

double GetR0(TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of Gtheta 

  int iNbins = hist->GetNbinsX();
  double dR0 = 0.; 

  for (int b=2;b<iNbins;b++)
  {
    double dG0 = hist->GetBinContent(b);
    double dGnext = hist->GetBinContent(b+1);
    double dGnextnext = hist->GetBinContent(b+2);
    // cout << hist->GetBinCenter(b);
    if (dGnext > dG0 && dGnextnext > dG0 && dG0<1.)
    {
      double dGlast = hist->GetBinContent(b-1);
      double dXlast = hist->GetBinCenter(b-1);
      double dX0 = hist->GetBinCenter(b);
      double dXnext = hist->GetBinCenter(b+1);

      dR0 = dX0 - ((dX0-dXlast)*(dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dX0-dXnext)*(dG0-dGlast))/
        (2.*((dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dG0-dGlast))); //parabolic interpolated minimum
      break; //stop loop if minimum is found
    } //if

  }//b

      
  return dR0;
}

TH1F* FillHistGtheta(TProfile *const &prReGtheta, TProfile *const &prImGtheta)
{
  Int_t iNbins = prReGtheta->GetNbinsX();
  Double_t xMin = prReGtheta->GetXaxis()->GetBinLowEdge(1);
  Double_t xMax = prReGtheta->GetXaxis()->GetBinLowEdge(iNbins) + prReGtheta->GetXaxis()->GetBinWidth(iNbins);
  TH1F* hGtheta = new TH1F(Form("hist_%s",prReGtheta->GetName()),"",iNbins,xMin,xMax);
  for (int rbin = 0; rbin < iNbins; rbin++)
  {
    // get bincentre of bins in histogram
    Double_t dRe = prReGtheta->GetBinContent(rbin+1);
    Double_t dIm = prImGtheta->GetBinContent(rbin+1);
    TComplex cGtheta(dRe,dIm);
    //fill fHistGtheta with the modulus squared of cGtheta
    //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
    if (cGtheta.Rho2()>3.) hGtheta->SetBinContent(rbin+1,0);
    else hGtheta->SetBinContent(rbin+1,cGtheta.Rho2());
    // hGtheta->SetBinContent(rbin+1,cGtheta.Rho2());
    hGtheta->SetBinError(rbin+1,0.0);
  }
  return hGtheta;
}

double BesselJ0(double x)
{
  double temp=1., xn=1.;
  long n, Nmax;

  Nmax=int(floor(2.*x)+4);
  for (n=1;n<Nmax;n++)
  {
    xn*=(-sqr(x/2./((float) n)));
    temp+=xn;
  }
  return temp;
}

void PlotV2(TString inputFileName1 = "FirstRun.root", TString inputFileName2 = "ThirdRun.root")
{
  bool bUseProduct = 1;
  bool bDebug = 1;
  TString label = "Toy Model, 10M events, <M>=1000";
  TFile *fi1 = new TFile(inputFileName1.Data(),"read");

  const int ncent = 16;
  const double bin_cent[ncent + 1] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
  TString legHeader[] = {"0-5%","5-10%","10-15%","15-20%","20-25%","25-30%","30-35%","35-40%","40-45%","45-50%","50-55%","55-60%","60-65%","65-70%","70-75%","75-80%"};
  const int thetabins = 5;
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  const double J1rootJ0 = 0.519147;
  const int npt = 12;
  const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  const double rootJ0 = 2.4048256;

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
    hv22[icent] = (TProfile*)fi2->Get(hname);
    sprintf(hname,"hv24_%i",icent);
    hv24[icent] = (TProfile*)fi2->Get(hname);
    sprintf(hname,"hcov24_%i",icent);
    hcov24[icent] = (TProfile*)fi2->Get(hname);

    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
        sprintf(hname,"hv22pt_%i_%i",icent,ipt);
        hv22pt[icent][ipt]=(TProfile*)fi2->Get(hname);
        sprintf(hname,"hv24pt_%i_%i",icent,ipt);
        hv24pt[icent][ipt]=(TProfile*)fi2->Get(hname);
        sprintf(hname,"hcov22prime_%i_%i",icent,ipt);
        hcov22prime[icent][ipt]=(TProfile*)fi2->Get(hname);
        sprintf(hname,"hcov24prime_%i_%i",icent,ipt);
        hcov24prime[icent][ipt]=(TProfile*)fi2->Get(hname);
        sprintf(hname,"hcov42prime_%i_%i",icent,ipt);
        hcov42prime[icent][ipt]=(TProfile*)fi2->Get(hname);
        sprintf(hname,"hcov44prime_%i_%i",icent,ipt);
        hcov44prime[icent][ipt]=(TProfile*)fi2->Get(hname);
        sprintf(hname,"hcov2prime4prime_%i_%i",icent,ipt);
        hcov2prime4prime[icent][ipt]=(TProfile*)fi2->Get(hname);
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


  double dRatio[ncent][npt][6] = {0.}, dRatioErr[ncent][npt][6] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      // for (int i = 0; i < 3; i++)
      // {
        dRatio[ic][ipt][0] = v2diffEP[ic][ipt] / v2diffMC[ic][ipt];
        dRatio[ic][ipt][1] = v2diff[ic][ipt] / v2diffMC[ic][ipt];
        dRatio[ic][ipt][2] = v2pt[0][ic][ipt] / v2diffMC[ic][ipt];
        dRatio[ic][ipt][3] = v2pt[1][ic][ipt] / v2diffMC[ic][ipt];
        dRatio[ic][ipt][4] = v2diffPro[ic][ipt] / v2diffMC[ic][ipt];
        dRatio[ic][ipt][5] = v2diffLYZEP[ic][ipt] / v2diffMC[ic][ipt];

        dRatioErr[ic][ipt][0] = dRatio[ic][ipt][0] * sqrt(pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2) + pow(v2diffeEP[ic][ipt] / v2diffEP[ic][ipt], 2)); 
        dRatioErr[ic][ipt][1] = dRatio[ic][ipt][1] * sqrt(pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2) + pow(v2diffe[ic][ipt] / v2diff[ic][ipt], 2));
        dRatioErr[ic][ipt][2] = dRatio[ic][ipt][2] * sqrt(pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2) + pow(v2ptE[0][ic][ipt] / v2pt[0][ic][ipt], 2));      
        dRatioErr[ic][ipt][3] = dRatio[ic][ipt][3] * sqrt(pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2) + pow(v2ptE[1][ic][ipt] / v2pt[1][ic][ipt], 2));
        dRatioErr[ic][ipt][4] = dRatio[ic][ipt][4] * sqrt(pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2) + pow(v2diffePro[ic][ipt] / v2diffPro[ic][ipt], 2));
        dRatioErr[ic][ipt][5] = dRatio[ic][ipt][5] * sqrt(pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2) + pow(v2ediffLYZEP[ic][ipt] / v2diffLYZEP[ic][ipt], 2)); 
      // }
    }
  }

  double ratioIntFlow[ncent][6] = {0.}, ratioIntFlowe[ncent][6] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    double v2EP = hv2EP->GetBinContent(ic+1);
    double v2MC = hv2MC->GetBinContent(ic+1);
    double v2EPe = hv2EP->GetBinError(ic+1);
    double v2MCe = hv2MC->GetBinError(ic+1);
    double v2LYZEP = hv2LYZEP->GetBinContent(ic+1);
    double v2eLYZEP = hv2LYZEP->GetBinError(ic+1);
    ratioIntFlow[ic][0] = v2EP/v2MC; 
    ratioIntFlow[ic][1] = v2LYZInt[ic]/v2MC; 
    ratioIntFlow[ic][2] = v2LYZIntPro[ic]/v2MC; 
    ratioIntFlow[ic][3] = v2cent[0][ic]/v2MC; // v22
    ratioIntFlow[ic][4] = v2cent[1][ic]/v2MC; // v24
    ratioIntFlow[ic][5] = v2LYZEP/v2MC;

    ratioIntFlowe[ic][0] = ratioIntFlow[ic][0] * sqrt(pow( v2EPe/ v2EP, 2) + pow(v2MCe / v2MC, 2));
    ratioIntFlowe[ic][1] = ratioIntFlow[ic][1] * sqrt(pow( v2eLYZInt[ic]/ v2LYZInt[ic], 2) + pow(v2MCe / v2MC, 2));
    ratioIntFlowe[ic][2] = ratioIntFlow[ic][2] * sqrt(pow( v2eLYZIntPro[ic]/ v2LYZIntPro[ic], 2) + pow(v2MCe / v2MC, 2));
    ratioIntFlowe[ic][3] = ratioIntFlow[ic][3] * sqrt(pow( v2centE[0][ic]/ v2cent[0][ic], 2) + pow(v2MCe / v2MC, 2));
    ratioIntFlowe[ic][4] = ratioIntFlow[ic][4] * sqrt(pow( v2centE[1][ic]/ v2cent[1][ic], 2) + pow(v2MCe / v2MC, 2));
    ratioIntFlowe[ic][5] = ratioIntFlow[ic][5] * sqrt(pow( v2eLYZEP/v2LYZEP, 2) + pow(v2MCe / v2MC, 2));
  }
  //================= Drawing =========================
  gStyle->SetErrorX(0);
  TCanvas c;
  
  c.Divide(2,1);
  // c.SetLeftMargin(0.2);
  c.cd(1);

  hv2LYZEP->SetMarkerStyle(29);
  hv2LYZEP->SetMarkerColor(kYellow+2);
  hv2LYZEP->SetLineColor(kYellow+2);

  hV22->SetMarkerStyle(28);
  hV22->SetMarkerColor(kBlack);
  hV22->SetLineColor(kBlack);

  hV24->SetMarkerStyle(27);
  hV24->SetMarkerColor(kGray+2);
  hV24->SetLineColor(kGray+2);


  TH1F *hLYZ = new TH1F(Form("hLYZ"),"",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hLYZ->SetBinContent(ic+1,v2LYZInt[ic]);
    hLYZ->SetBinError(ic+1,v2eLYZInt[ic]);
  }
  hLYZ->SetMarkerStyle(23);
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
  hLYZPro->SetMarkerColor(kGreen+2);
  hLYZPro->SetLineColor(kGreen+2);
  }

  hv2EP->SetMarkerStyle(20);
  hv2EP->SetMarkerColor(kRed+2);
  hv2EP->SetLineColor(kRed+2);

  hv2MC->SetMarkerStyle(25);
  hv2MC->SetMarkerColor(kBlack);
  hv2MC->SetLineColor(kBlack);
  hv2MC->SetTitle(Form("%s;centrality, %%;v_{2}",label.Data()));
  hv2MC->GetYaxis()->SetRangeUser(0,0.1);
  hv2MC->GetXaxis()->SetLimits(0,60);


  hv2MC->Draw();
  hv2EP->Draw("same");
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
  leg->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  c.cd(2);
  TH1F *hRatioInt[6];
  for (int i=0; i<6; i++)
  {
    hRatioInt[i] = new TH1F(Form("hRatioInt_%i",i),"",ncent,&bin_cent[0]);
    for (int ic=0; ic<ncent; ic++)
    {
      hRatioInt[i]->SetBinContent(ic+1,ratioIntFlow[ic][i]);
      hRatioInt[i]->SetBinError(ic+1,ratioIntFlowe[ic][i]);
    }
  }
  hRatioInt[0]->SetMarkerStyle(20);
  hRatioInt[0]->SetMarkerColor(kRed+2);
  hRatioInt[0]->SetLineColor(kRed+2);
  hRatioInt[2]->SetMarkerStyle(26);
  hRatioInt[2]->SetMarkerColor(kGreen+2);
  hRatioInt[2]->SetLineColor(kGreen+2);
  hRatioInt[1]->SetMarkerStyle(23);
  hRatioInt[1]->SetMarkerColor(kBlue+2);
  hRatioInt[1]->SetLineColor(kBlue+2);
  hRatioInt[3]->SetMarkerStyle(28);
  hRatioInt[3]->SetMarkerColor(kBlack);
  hRatioInt[3]->SetLineColor(kBlack);
  hRatioInt[4]->SetMarkerStyle(27);
  hRatioInt[4]->SetMarkerColor(kGray+2);
  hRatioInt[4]->SetLineColor(kGray+2);

  hRatioInt[5]->SetMarkerStyle(29);
  hRatioInt[5]->SetMarkerColor(kYellow+2);
  hRatioInt[5]->SetLineColor(kYellow+2);

  hRatioInt[0]->GetYaxis()->SetRangeUser(0.89,1.11);
  hRatioInt[0]->SetTitle(";centrality, %;Ratio to MC");
  hRatioInt[0]->Draw();
  for (int i=1; i<6; i++) hRatioInt[i]->Draw("same");
  TLine lineOne1;
  lineOne1.SetLineStyle(2);
  lineOne1.DrawLine(0,1.,80,1.);
  
  c.SaveAs("Flow.pdf");
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
  TCanvas c3("c3","",1400,700);
  TPaveLabel* title3 = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title3->SetBorderSize(0);
  title3->SetFillColor(0);
  c3.SetLeftMargin(0.15);
  // title3->SetTextFont(textFont);
  // title3->SetTextSize(2.);
  title3->Draw();
  c3.Divide(5,2,0,0);
  // gROOT->SetStyle("Pub");
  for (int centrality = 1; centrality < 6; centrality++){
  c3.cd(centrality);
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
  hV22Diff->SetMarkerColor(kBlack);
  hV22Diff->SetLineColor(kBlack);
  hV22Diff->GetXaxis()->SetLimits(-0.1,3.6);

  hV24Diff->SetMarkerStyle(27);
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
  hLYZDiffPro->SetMarkerColor(kGreen+2);
  hLYZDiffPro->SetLineColor(kGreen+2);
  hLYZDiffPro->GetXaxis()->SetLimits(-0.1,3.6);
  }
  hv2LYZEPpt[centrality]->SetMarkerStyle(29);
  hv2LYZEPpt[centrality]->SetMarkerColor(kYellow+2);
  hv2LYZEPpt[centrality]->SetLineColor(kYellow+2);
  hv2LYZEPpt[centrality]->GetXaxis()->SetLimits(-0.1,3.6);

  hv2EPpt[centrality]->SetTitle(";p_{T}, GeV/c;v_{2}");
  hv2EPpt[centrality]->GetYaxis()->SetRangeUser(-0.01,0.26);
  hv2EPpt[centrality]->Draw();
  hLYZDiff->Draw("P same");
  if (bUseProduct) hLYZDiffPro->Draw("P same");
  hV22Diff->Draw("P same");
  hV24Diff->Draw("P same");
  hv2MCpt[centrality]->Draw("P same");
  hv2LYZEPpt[centrality]->Draw("P same");
  TLegend *leg2 = new TLegend(0.17,0.65,0.48,0.97);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[centrality].Data());
  leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ (Sum)","p");
  if (bUseProduct) leg2->AddEntry(hLYZDiffPro,"LYZ (Prod.)","p");
  leg2->AddEntry(hV22Diff,"2,QC","p");
  leg2->AddEntry(hV24Diff,"4,QC","p");
  leg2->AddEntry(hv2LYZEPpt[centrality],"LYZ, EP","p");
  leg2->Draw();
  }
  for (int centrality = 1; centrality < 6; centrality++){
    c3.cd(centrality+5);

    TH1F *hLYZDiffRatio = new TH1F(Form("hLYZDiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hLYZDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][1]);
      hLYZDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][1]);
    }
    hLYZDiffRatio->SetMarkerStyle(23);
    hLYZDiffRatio->SetMarkerColor(kBlue+2);
    hLYZDiffRatio->SetLineColor(kBlue+2);
    hLYZDiffRatio->SetTitle(";p_{T}, GeV/c;Ratio to MC");
    hLYZDiffRatio->GetYaxis()->SetRangeUser(0.89,1.11);
    
    TH1F *hLYZDiffRatioPro;
    hLYZDiffRatioPro = new TH1F(Form("hLYZDiffRatioPro_%i",centrality),"",npt,&bin_pT[0]);
    if (bUseProduct){
    for (int ipt=0; ipt<npt; ipt++)
    {
      hLYZDiffRatioPro->SetBinContent(ipt+1,dRatio[centrality][ipt][4]);
      hLYZDiffRatioPro->SetBinError(ipt+1,dRatioErr[centrality][ipt][4]);
    }
    hLYZDiffRatioPro->SetMarkerStyle(26);
    hLYZDiffRatioPro->SetMarkerColor(kGreen+2);
    hLYZDiffRatioPro->SetLineColor(kGreen+2);
    }
    TH1F *hV22DiffRatio = new TH1F(Form("hV22DiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV22DiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][2]);
      hV22DiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][2]);
    }
    hV22DiffRatio->SetMarkerStyle(28);
    hV22DiffRatio->SetMarkerColor(kBlack);
    hV22DiffRatio->SetLineColor(kBlack);
    hV22DiffRatio->GetYaxis()->SetRangeUser(0.89,1.11);
    TH1F *hV24DiffRatio = new TH1F(Form("hV24DiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV24DiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][3]);
      hV24DiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][3]);
    }
    hV24DiffRatio->SetMarkerStyle(27);
    hV24DiffRatio->SetMarkerColor(kGray+2);
    hV24DiffRatio->SetLineColor(kGray+2);

    TH1F *hV2EPDiffRatio = new TH1F(Form("hV2EPDiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV2EPDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][0]);
      hV2EPDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][0]);
    }
    hV2EPDiffRatio->SetMarkerStyle(20);
    hV2EPDiffRatio->SetMarkerColor(kRed+2);
    hV2EPDiffRatio->SetLineColor(kRed+2);

    TH1F *hV2LYZEPDiffRatio = new TH1F(Form("hV2LYZEPDiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV2LYZEPDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][5]);
      hV2LYZEPDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][5]);
    }
    hV2LYZEPDiffRatio->SetMarkerStyle(29);
    hV2LYZEPDiffRatio->SetMarkerColor(kYellow+2);
    hV2LYZEPDiffRatio->SetLineColor(kYellow+2);

    hLYZDiffRatio->Draw();
    hV22DiffRatio->Draw("same");
    hV24DiffRatio->Draw("same");
    hV2EPDiffRatio->Draw("same");
    
   

    
    if (bUseProduct) hLYZDiffRatioPro->Draw("same");
    
    hV2LYZEPDiffRatio->Draw("same");
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(0.2,1.,3.5,1.);
  }
  c3.SaveAs("RatioDiffFlow.pdf");

  //================= Drawing =========================
  TCanvas c4("c4","",1400,700);
  TPaveLabel* title4 = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title4->SetBorderSize(0);
  title4->SetFillColor(0);
  c4.SetLeftMargin(0.15);
  // title3->SetTextFont(textFont);
  // title3->SetTextSize(2.);
  title4->Draw();
  c4.Divide(5,2,0,0);
  // gROOT->SetStyle("Pub");
  for (int centrality = 6; centrality < 11; centrality++){
  c4.cd(centrality-5);
  TH1F *hV22Diff = new TH1F(Form("hV22Diff_%i",centrality+9),"",npt,&bin_pT[0]);
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hV22Diff->SetBinContent(ipt+1,v2pt[0][centrality][ipt]);
    hV22Diff->SetBinError(ipt+1,v2ptE[0][centrality][ipt]);    
  }
  TH1F *hV24Diff = new TH1F(Form("hV24Diff_%i",centrality+9),"",npt,&bin_pT[0]);
  for (int ipt = 0; ipt < npt; ipt++)
  {
    hV24Diff->SetBinContent(ipt+1,v2pt[1][centrality][ipt]);
    hV24Diff->SetBinError(ipt+1,v2ptE[1][centrality][ipt]);    
  }

  hV22Diff->SetMarkerStyle(28);
  hV22Diff->SetMarkerColor(kBlack);
  hV22Diff->SetLineColor(kBlack);
  hV22Diff->GetXaxis()->SetLimits(-0.1,3.6);

  hV24Diff->SetMarkerStyle(27);
  hV24Diff->SetMarkerColor(kGray+2);
  hV24Diff->SetLineColor(kGray+2);
  hV24Diff->GetXaxis()->SetLimits(-0.1,3.6);



  TH1F *hLYZDiff = new TH1F(Form("hLYZDiff_%i",centrality+9),"",npt,&bin_pT[0]);
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
  hLYZDiffPro = new TH1F(Form("hLYZDiffPro_%i",centrality+9),"",npt,&bin_pT[0]);
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
  hv2LYZEPpt[centrality]->SetMarkerStyle(29);
  hv2LYZEPpt[centrality]->SetMarkerColor(kYellow+2);
  hv2LYZEPpt[centrality]->SetLineColor(kYellow+2);
  hv2LYZEPpt[centrality]->GetXaxis()->SetLimits(-0.1,3.6);

  hv2EPpt[centrality]->SetTitle(";p_{T}, GeV/c;v_{2}");
  hv2EPpt[centrality]->GetYaxis()->SetRangeUser(-0.01,0.26);
  hv2EPpt[centrality]->Draw();
  hLYZDiff->Draw("P same");
  if (bUseProduct) hLYZDiffPro->Draw("P same");
  hV22Diff->Draw("P same");
  hV24Diff->Draw("P same");
  hv2MCpt[centrality]->Draw("P same");
  hv2LYZEPpt[centrality]->Draw("P same");
  TLegend *leg2 = new TLegend(0.17,0.65,0.48,0.97);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[centrality].Data());
  leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ (Sum)","p");
  if (bUseProduct) leg2->AddEntry(hLYZDiffPro,"LYZ (Prod.)","p");
  leg2->AddEntry(hV22Diff,"2,QC","p");
  leg2->AddEntry(hV24Diff,"4,QC","p");
  leg2->AddEntry(hv2LYZEPpt[centrality],"LYZ, EP","p");
  leg2->Draw();
  }
  for (int centrality = 6; centrality < 11; centrality++){
    c4.cd(centrality);

    TH1F *hLYZDiffRatio = new TH1F(Form("hLYZDiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hLYZDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][1]);
      hLYZDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][1]);
    }
    hLYZDiffRatio->SetMarkerStyle(23);
    hLYZDiffRatio->SetMarkerColor(kBlue+2);
    hLYZDiffRatio->SetLineColor(kBlue+2);
    hLYZDiffRatio->SetTitle(";p_{T}, GeV/c;Ratio to MC");
    hLYZDiffRatio->GetYaxis()->SetRangeUser(0.89,1.11);
    
    TH1F *hLYZDiffRatioPro;
    hLYZDiffRatioPro = new TH1F(Form("hLYZDiffRatioPro_%i",centrality),"",npt,&bin_pT[0]);
    if (bUseProduct){
    for (int ipt=0; ipt<npt; ipt++)
    {
      hLYZDiffRatioPro->SetBinContent(ipt+1,dRatio[centrality][ipt][4]);
      hLYZDiffRatioPro->SetBinError(ipt+1,dRatioErr[centrality][ipt][4]);
    }
    hLYZDiffRatioPro->SetMarkerStyle(26);
    hLYZDiffRatioPro->SetMarkerColor(kGreen+2);
    hLYZDiffRatioPro->SetLineColor(kGreen+2);
    }
    TH1F *hV22DiffRatio = new TH1F(Form("hV22DiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV22DiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][2]);
      hV22DiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][2]);
    }
    hV22DiffRatio->SetMarkerStyle(28);
    hV22DiffRatio->SetMarkerColor(kBlack);
    hV22DiffRatio->SetLineColor(kBlack);
    hV22DiffRatio->GetYaxis()->SetRangeUser(0.89,1.11);
    TH1F *hV24DiffRatio = new TH1F(Form("hV24DiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV24DiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][3]);
      hV24DiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][3]);
    }
    hV24DiffRatio->SetMarkerStyle(27);
    hV24DiffRatio->SetMarkerColor(kGray+2);
    hV24DiffRatio->SetLineColor(kGray+2);

    TH1F *hV2EPDiffRatio = new TH1F(Form("hV2EPDiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV2EPDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][0]);
      hV2EPDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][0]);
    }
    hV2EPDiffRatio->SetMarkerStyle(20);
    hV2EPDiffRatio->SetMarkerColor(kRed+2);
    hV2EPDiffRatio->SetLineColor(kRed+2);

    TH1F *hV2LYZEPDiffRatio = new TH1F(Form("hV2LYZEPDiffRatio_%i",centrality),"",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hV2LYZEPDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][5]);
      hV2LYZEPDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][5]);
    }
    hV2LYZEPDiffRatio->SetMarkerStyle(29);
    hV2LYZEPDiffRatio->SetMarkerColor(kYellow+2);
    hV2LYZEPDiffRatio->SetLineColor(kYellow+2);

    hLYZDiffRatio->Draw();
    hV22DiffRatio->Draw("same");
    hV24DiffRatio->Draw("same");
    hV2EPDiffRatio->Draw("same");
    
   

    
    if (bUseProduct) hLYZDiffRatioPro->Draw("same");
    
    hV2LYZEPDiffRatio->Draw("same");
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(0.2,1.,3.5,1.);
  }
  c4.SaveAs("RatioDiffFlow_2.pdf");




}
