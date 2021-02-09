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

void PlotV2(TString inputFileName1 = "FirstRun.root", TString inputFileName2 = "SecondRun.root")
{
  // bool bUseProduct = 1;
  bool bDebug = 1;
  const int markerStyle[]={25,20,28,27,23,26};
  const TString methodName[]={"LYZ (Sum)", "LYZ (Prod.)"};
  std::pair<double,double> ratioRange = {0.67,1.23};
  TString label = "AMPT, #sigma_{p}=1.5 mb, Au+Au, #sqrt{s_{NN}}=7.7 GeV";
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
  TH2F *hist = new TH2F("hist",Form("%s;centrality, %%;v_{2}",label.Data()),6,0,60,1,0,0.1);
  hist->Draw("");
  hLYZ->Draw("P same");
  if (bUseProduct) { hLYZPro->GetXaxis()->SetLimits(0,60); hLYZPro->Draw("P same");}
  TLegend *leg = new TLegend(0.25,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->AddEntry(hLYZ,"LYZ (Sum)","p");
  if (bUseProduct) leg->AddEntry(hLYZPro,"LYZ (Prod.)","p");
  leg->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  c.SaveAs("IntFlowLYZ.pdf");
  //================= Drawing =========================
  TCanvas c2;
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title->SetBorderSize(0);
  title->SetFillColor(0);

  title->Draw();
  TString legHeader[] = {"0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%","60-70%","70-80%"};
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
  c2.SaveAs(Form("DifFlowLYZ.pdf"));

}
