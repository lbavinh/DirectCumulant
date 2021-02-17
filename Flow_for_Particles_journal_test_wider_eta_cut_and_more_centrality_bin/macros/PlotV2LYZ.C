#define PLOTV2LYZ
#include "../constants.C"
#define sqr(x) ((x)*(x))
void GetMultMean(TProfile *const &pr)
{
  cout << "const double dMultMean[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX()-1; i++)
  {
    cout << (pr->GetBinContent(i+1)) <<", ";
  }
  cout <<(pr->GetBinContent(pr->GetNbinsX()))<<"};" << endl;
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

TGraphErrors* PlotV2LYZ(TString inputFileName1 = "FirstRun_AMPT15_11.5.root", TString inputFileName2 = "SecondRun_AMPT15_11.5.root")
{
  bool bUseProduct = 1;
  bool bDebug = 1;
  const int markerStyle[]={25,20,28,27,23,26};
  const TString methodName[]={"LYZ (Sum)", "LYZ (Prod.)"};
  std::pair<double,double> ratioRange = {0.67,1.23};
  TString label = "AMPT, #sigma_{p}=1.5mb, Au+Au, #sqrt{s_{NN}}=11.5 GeV"; // AMPT, #sigma_{p}=1.5 mb
  TFile *fi1 = new TFile(inputFileName1.Data(),"read");


  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  const double J1rootJ0 = 0.519147;
  const double rootJ0 = 2.4048256;



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
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile*) fi1->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile*) fi1->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }
  
  TFile *fi2 = new TFile(inputFileName2.Data(),"read");

  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];

  TProfile *prReDenomPro[thetabins];
  TProfile *prImDenomPro[thetabins];
  TProfile *prReNumerPro[thetabins][ncent];
  TProfile *prImNumerPro[thetabins][ncent];
  TProfile *prV2Diff1040 = new TProfile("prV2Diff1040","", npt, 0, npt);
  TProfile *prV2Diff1040Pro = new TProfile("prV2Diff1040Pro","", npt, 0, npt);
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



  if (bDebug){
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

    cout << "const double chiPRO[" << ncent << "] = {";
    for (int ic = 0; ic < ncent-1; ic++)
    {
      cout << sqrt(dChi2Pro[ic]) <<", ";
    }
    cout << sqrt(dChi2Pro[ncent-1]) << "};" << endl;

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
      if (ic>=2 && ic<=4)prV2Diff1040->Fill(ipt, v2diff[ic][ipt], rpmult);
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
      if (ic>=2 && ic<=4)prV2Diff1040Pro->Fill(ipt, v2diffPro[ic][ipt], rpmult);
    }
  }} // end of Diff LYZ Product


  if (bDebug)
  {
    if (bUseProduct)
    {
      cout << "const double v2LYZPro[" << ncent << "] = {";
      for (int ic = 0; ic < ncent-1; ic++)
      {
        cout << v2LYZIntPro[ic] <<", ";
      }
      cout << v2LYZIntPro[ncent-1] << "};" << endl;

      cout << "const double v2eLYZPro[" << ncent << "] = {";
      for (int ic = 0; ic < ncent-1; ic++)
      {
        cout << v2eLYZIntPro[ic] <<", ";
      }
      cout << v2eLYZIntPro[ncent-1] << "};" << endl;   

    }
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
        cout <<"cent: "<< ic << " " <<dVtheta[ic][thetabin] << "\t" << integratedFlow << endl;//refmult
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

  // Stat. error calculation for 10-40%
  double v2ErrLYZ1040[npt], v2ErrLYZPro1040[npt];
  bool bCent1040 = 1;
  if (bCent1040)
  {
    double refmult = prRefMult->GetBinContent(2+1) * prRefMult->GetBinEntries(2+1)
                   + prRefMult->GetBinContent(3+1) * prRefMult->GetBinEntries(3+1)
                   + prRefMult->GetBinContent(4+1) * prRefMult->GetBinEntries(4+1);
    refmult /= prRefMult->GetBinEntries(2+1) + prRefMult->GetBinEntries(3+1) + prRefMult->GetBinEntries(4+1);
    cout << prRefMult->GetBinContent(2+1) <<" "<<prRefMult->GetBinContent(3+1)<<" "<<prRefMult->GetBinContent(4+1) << endl; 
    cout << "refmult=" << refmult << endl;    
    double v2int;
    float thetacount = 0;

    for (int it = 0; it < thetabins; it++)
    {
      TProfile* prRetheta = (TProfile*) prReGthetaSum[2][it]->Clone(Form("Clone_%s",prReGthetaSum[2][it]->GetName()));
      prRetheta->Add(prReGthetaSum[3][it]);
      prRetheta->Add(prReGthetaSum[4][it]);
      TProfile* prImtheta = (TProfile*) prImGthetaSum[2][it]->Clone(Form("Clone_%s",prImGthetaSum[2][it]->GetName()));
      prImtheta->Add(prImGthetaSum[3][it]);
      prImtheta->Add(prImGthetaSum[4][it]);

      TH1F *hGtheta = FillHistGtheta(prRetheta, prImtheta);
      float r0theta = GetR0(hGtheta);
      if (r0theta!=0) 
      {
        v2int += rootJ0 / r0theta;
        thetacount++;
      }
    }
    if (thetacount!=0) v2int /= thetacount; // refmult
    else {v2int = 0.;}
    cout << "v2int = " << v2int << endl;
    float modQ2sqmean=0, Q2xmean=0, Q2ymean=0, mult=0;
    for (int ic = 2; ic < 5; ic++)
    {
      mult += prRefMult->GetBinContent(ic+1);
      modQ2sqmean += prQ2ModSq->GetBinContent(ic+1) * prRefMult->GetBinContent(ic+1);
      Q2xmean += prQ2x->GetBinContent(ic+1) * prRefMult->GetBinContent(ic+1);
      Q2ymean += prQ2y->GetBinContent(ic+1) * prRefMult->GetBinContent(ic+1);
    }
    modQ2sqmean /= mult;
    Q2xmean /= mult;
    Q2ymean /= mult;
    float chi2 = v2int/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int,2));
    cout << "Chi2 of 10-40%: " << chi2 << endl;
    float temp=0.;
    for(int it=0; it<thetabins; it++)
    {
      double arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    float neve = prRefMult->GetBinEntries(2+1) + prRefMult->GetBinEntries(3+1) + prRefMult->GetBinEntries(4+1);
    TProfile* prMultPOI1040 = (TProfile*) prMultPOI[2]->Clone(Form("Clone_%s",prMultPOI[2]->GetName()));
    prMultPOI1040->Add(prMultPOI[3]);
    prMultPOI1040->Add(prMultPOI[4]);
    for (int ipt = 0; ipt < npt; ipt++)
    {
      double rpmult = prMultPOI1040->GetBinContent(ipt+1);
      v2ErrLYZ1040[ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0;
    }
    cout << "const double v2ErrLYZ1040[" << npt <<"] = {";
    for (int ipt = 0; ipt < npt-1; ipt++)
    {
      cout << v2ErrLYZ1040[ipt] <<", ";
    }
    cout << v2ErrLYZ1040[npt-1] << " };" << endl;

  } // end of V2 calculation

  // LYZ Product 10-40%
  if (bCent1040)
  {
    double refmult = prRefMult->GetBinContent(2+1) * prRefMult->GetBinEntries(2+1)
                   + prRefMult->GetBinContent(3+1) * prRefMult->GetBinEntries(3+1)
                   + prRefMult->GetBinContent(4+1) * prRefMult->GetBinEntries(4+1);
    refmult /= prRefMult->GetBinEntries(2+1) + prRefMult->GetBinEntries(3+1) + prRefMult->GetBinEntries(4+1);
    double v2int;
    float thetacount = 0;

    for (int it = 0; it < thetabins; it++)
    {
      TProfile* prRetheta = (TProfile*) prReGthetaProduct[2][it]->Clone(Form("Clone_%s",prReGthetaProduct[2][it]->GetName()));
      prRetheta->Add(prReGthetaProduct[3][it]);
      prRetheta->Add(prReGthetaProduct[4][it]);
      TProfile* prImtheta = (TProfile*) prImGthetaProduct[2][it]->Clone(Form("Clone_%s",prImGthetaProduct[2][it]->GetName()));
      prImtheta->Add(prImGthetaProduct[3][it]);
      prImtheta->Add(prImGthetaProduct[4][it]);

      TH1F *hGtheta = FillHistGtheta(prRetheta, prImtheta);
      float r0theta = GetR0(hGtheta);
      if (r0theta!=0) 
      {
        v2int += rootJ0 / r0theta;
        thetacount++;
      }
    }
    if (thetacount!=0) v2int /= thetacount*refmult; // 
    else {v2int = 0.;}
    float modQ2sqmean=0, Q2xmean=0, Q2ymean=0, mult=0;
    for (int ic = 2; ic < 5; ic++)
    {
      mult += prRefMult->GetBinContent(ic+1);
      modQ2sqmean += prQ2ModSq->GetBinContent(ic+1) * prRefMult->GetBinContent(ic+1);
      Q2xmean += prQ2x->GetBinContent(ic+1) * prRefMult->GetBinContent(ic+1);
      Q2ymean += prQ2y->GetBinContent(ic+1) * prRefMult->GetBinContent(ic+1);
    }
    modQ2sqmean /= mult;
    Q2xmean /= mult;
    Q2ymean /= mult;
    float chi2 = v2int/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int,2));
    cout << "Chi2 of 10-40% Pro: " << chi2 << endl;
    float temp=0.;
    for(int it=0; it<thetabins; it++)
    {
      double arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    // float neve = prRefMult->GetBinEntries(2+1) + prRefMult->GetBinEntries(3+1) + prRefMult->GetBinEntries(4+1);
    double neve = prReDenomPro[0]->GetBinEntries(2+1) + prReDenomPro[0]->GetBinEntries(3+1) + prReDenomPro[0]->GetBinEntries(4+1);
    TProfile* prMultPOI1040 = (TProfile*) prMultPOI[2]->Clone(Form("Clone_%s",prMultPOI[2]->GetName()));
    prMultPOI1040->Add(prMultPOI[3]);
    prMultPOI1040->Add(prMultPOI[4]);
    for (int ipt = 0; ipt < npt; ipt++)
    {
      double rpmult = prMultPOI1040->GetBinContent(ipt+1);
      v2ErrLYZPro1040[ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0;
    }
    cout << "const double v2ErrLYZPro1040[" << npt <<"] = {";
    for (int ipt = 0; ipt < npt-1; ipt++)
    {
      cout << v2ErrLYZPro1040[ipt] <<", ";
    }
    cout << v2ErrLYZPro1040[npt-1] << " };" << endl;

  } // end of V2 calculation
  double X[npt], ErrX[npt], V2Diff1040Pro[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1])/2.;
    ErrX[ipt] = 0;
    V2Diff1040Pro[ipt] = prV2Diff1040Pro->GetBinContent(ipt+1);
  }
  TGraphErrors *grV2Diff1040Pro = new TGraphErrors(npt, X, V2Diff1040Pro, ErrX, v2ErrLYZPro1040);
   

  //================= Drawing =========================
  gStyle->SetErrorX(0);
  TCanvas c;
  TPaveLabel* title2 = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title2->SetBorderSize(0);
  title2->SetFillColor(0);
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

  hLYZ->GetXaxis()->SetLimits(0,60.);
  TH2F *hist = new TH2F("hist",Form("%s;centrality, %%;v_{2}",label.Data()),6,0,80,1,0,0.1);
  hist->Draw("");
  hLYZ->Draw("P same");
  if (bUseProduct) { hLYZPro->GetXaxis()->SetLimits(0,80); hLYZPro->Draw("P same");}
  TLegend *leg = new TLegend(0.25,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->AddEntry(hLYZ,"LYZ (Sum)","p");
  if (bUseProduct) leg->AddEntry(hLYZPro,"LYZ (Prod.)","p");
  leg->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  c.SaveAs("IntFlowLYZSum&Pro_AMPT_11.5.pdf");
  //================= Drawing =========================
  TCanvas c2;
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title->SetBorderSize(0);
  title->SetFillColor(0);

  title->Draw();
  TString legHeader[] = {"0-5%","5-10%","10-15%","15-20%","20-25%","25-30%","30-35%","35-40%","40-45%"};
  c2.Divide(3,2,0,0);
  for (int ic = 1; ic < 7; ic++){
  c2.cd(ic);
  TH1F *hLYZDiff = new TH1F(Form("hLYZDiff_%i",ic),";p_{T}, GeV/c;v_{2}",npt,&pTBin[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiff->SetBinContent(ipt+1,v2diff[ic][ipt]);
    hLYZDiff->SetBinError(ipt+1,v2diffe[ic][ipt]);
  }
  hLYZDiff->SetMarkerStyle(23);
  hLYZDiff->SetMarkerColor(kBlue+2);
  hLYZDiff->SetLineColor(kBlue+2);
  hLYZDiff->GetXaxis()->SetLimits(-0.1,3.6);

  TH1F *hLYZDiffPro;
  if (bUseProduct){
  hLYZDiffPro = new TH1F(Form("hLYZDiffPro_%i",ic),";p_{T}, GeV/c;v_{2}",npt,&pTBin[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiffPro->SetBinContent(ipt+1,v2diffPro[ic][ipt]);
    hLYZDiffPro->SetBinError(ipt+1,v2diffePro[ic][ipt]);
  }
  hLYZDiffPro->SetMarkerStyle(26);
  hLYZDiffPro->SetMarkerColor(kGreen+2);
  hLYZDiffPro->SetLineColor(kGreen+2);
  hLYZDiffPro->GetXaxis()->SetLimits(-0.1,3.6);
  }


  hLYZDiff->GetYaxis()->SetRangeUser(-0.01,0.26);
  hLYZDiff->Draw();
  if (bUseProduct) hLYZDiffPro->Draw("P same");
  TLegend *leg2 = new TLegend(0.15,0.7,0.4,0.9);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[ic].Data());
  leg2->AddEntry(hLYZDiff,"LYZ (Sum)","p");
  if (bUseProduct) leg2->AddEntry(hLYZDiffPro,"LYZ (Prod.)","p");
  leg2->Draw();
  }
  c2.SaveAs(Form("DifFlowLYZSum&Pro_AMPT_11.5.pdf"));
  return grV2Diff1040Pro;
}
