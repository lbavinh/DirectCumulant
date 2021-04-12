#define PLOTV2LYZ
#include "../constants.C"
#define sqr(x) ((x)*(x))
void GetMultMean(TProfile *const &pr)
{
  cout << "const Double_t dMultMean[" << pr->GetNbinsX() <<"] = {";
  for (Int_t i=0; i<pr->GetNbinsX()-1; i++)
  {
    cout << (pr->GetBinContent(i+1)) <<", ";
  }
  cout <<(pr->GetBinContent(pr->GetNbinsX()))<<"};" << endl;
}

Double_t GetR0(TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of Gtheta 

  Int_t iNbins = hist->GetNbinsX();
  Double_t dR0 = 0.; 

  for (Int_t b=2;b<iNbins;b++)
  {
    Double_t dG0 = hist->GetBinContent(b);
    Double_t dGnext = hist->GetBinContent(b+1);
    Double_t dGnextnext = hist->GetBinContent(b+2);
    // cout << hist->GetBinCenter(b);
    if (dGnext > dG0 && dGnextnext > dG0 && dG0<1.)
    {
      Double_t dGlast = hist->GetBinContent(b-1);
      Double_t dXlast = hist->GetBinCenter(b-1);
      Double_t dX0 = hist->GetBinCenter(b);
      Double_t dXnext = hist->GetBinCenter(b+1);

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
  for (Int_t rbin = 0; rbin < iNbins; rbin++)
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

Double_t BesselJ0(Double_t x)
{
  Double_t temp=1., xn=1.;
  long n, Nmax;

  Nmax=Int_t(floor(2.*x)+4);
  for (n=1;n<Nmax;n++)
  {
    xn*=(-sqr(x/2./((Float_t) n)));
    temp+=xn;
  }
  return temp;
}

TGraphErrors* PlotV2LYZ(TString inputFileName1 = "FirstRun.root", TString inputFileName2 = "SecondRun.root")
{
  Bool_t bUseProduct = 1;
  Bool_t bUseMultWeight = 1;
  Bool_t bDebug = 1;
  const Int_t markerStyle[]={25,20,28,27,23,26};
  const TString methodName[]={"LYZ (Sum)", "LYZ (Prod)"};
  std::pair<Double_t,Double_t> ratioRange = {0.67,1.23};
  TString label = "AMPT, #sigma_{p}=1.5mb, Au+Au, #sqrt{s_{NN}}=11.5 GeV";
  TFile *fi1 = new TFile(inputFileName1.Data(),"read");


  Double_t theta[nTheta];
  for (Int_t ith = 0; ith < nTheta; ++ith)
  {
    theta[ith] = ith * TMath::Pi() / (2.0 * nTheta);
  }
  const Double_t J1rootJ0 = 0.519147;
  const Double_t rootJ0 = 2.4048256;

  TProfile *prReGtheta[ncent][nTheta];
  TProfile *prImGtheta[ncent][nTheta];
  TProfile *prMultRP;
  TProfile *prQ2x;
  TProfile *prQ2y;
  TProfile *prQ2ModSq;
  if (bUseProduct){
    prMultRP = (TProfile*) fi1->FindObjectAny("prMultRPPro");
    prQ2x = (TProfile*) fi1->FindObjectAny("prQ2xPro");
    prQ2y = (TProfile*) fi1->FindObjectAny("prQ2yPro");
    prQ2ModSq = (TProfile*) fi1->FindObjectAny("prQ2ModSqPro");
  }else{
    prMultRP = (TProfile*) fi1->FindObjectAny("prMultRPSum");
    prQ2x = (TProfile*) fi1->FindObjectAny("prQ2xSum");
    prQ2y = (TProfile*) fi1->FindObjectAny("prQ2ySum");
    prQ2ModSq = (TProfile*) fi1->FindObjectAny("prQ2ModSqSum");
  }

  for (Int_t i = 0; i < ncent; ++i)
  {
    for (Int_t j = 0; j < nTheta; ++j)
    {
      if (bUseProduct)
      {
        prReGtheta[i][j] = (TProfile*) fi1->FindObjectAny(Form("prReGthetaPro_cent%i_theta%i", i, j));
        prImGtheta[i][j] = (TProfile*) fi1->FindObjectAny(Form("prImGthetaPro_cent%i_theta%i", i, j));
      }
      else{
      prReGtheta[i][j] = (TProfile*) fi1->FindObjectAny(Form("prReGthetaSum_cent%i_theta%i", i, j));
      prImGtheta[i][j] = (TProfile*) fi1->FindObjectAny(Form("prImGthetaSum_cent%i_theta%i", i, j));
      }
    }
  }
  
  TFile *fi2 = new TFile(inputFileName2.Data(),"read");

  // Differential flow
  TProfile *prReDenom[nTheta];
  TProfile *prImDenom[nTheta];
  TProfile *prReNumer[nTheta][ncent];
  TProfile *prImNumer[nTheta][ncent];

  TProfile *prReDenomPro[nTheta];
  TProfile *prImDenomPro[nTheta];
  TProfile *prReNumerPro[nTheta][ncent];
  TProfile *prImNumerPro[nTheta][ncent];
  TProfile *prV2Diff1040 = new TProfile("prV2Diff1040","", npt, 0, npt);
  for (Int_t i = 0; i < nTheta; i++)
  {

    if (bUseProduct)
    {
      prReDenomPro[i] = (TProfile*) fi2->FindObjectAny(Form("prReDenomPro_theta%i", i));
      prImDenomPro[i] = (TProfile*) fi2->FindObjectAny(Form("prImDenomPro_theta%i", i));

      for (Int_t j = 0; j < ncent; j++)
      {
        prReNumerPro[i][j] = (TProfile*) fi2->FindObjectAny(Form("prReNumerPro_theta%i_cent%i", i, j));
        prImNumerPro[i][j] = (TProfile*) fi2->FindObjectAny(Form("prImNumerPro_theta%i_cent%i", i, j));
      }    
    }else{
      prReDenom[i] = (TProfile*) fi2->FindObjectAny(Form("prReDenom_theta%i",i));
      prImDenom[i] = (TProfile*) fi2->FindObjectAny(Form("prImDenom_theta%i",i));

      for (Int_t j = 0; j < ncent; j++)
      {
        prReNumer[i][j] = (TProfile*) fi2->FindObjectAny(Form("prReNumer_theta%i_cent%i", i, j));
        prImNumer[i][j] = (TProfile*) fi2->FindObjectAny(Form("prImNumer_theta%i_cent%i", i, j));
      }
    }
  }
  TProfile *prMultPOI[ncent];
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    if (bUseProduct) prMultPOI[ic] = (TProfile*) fi2->FindObjectAny(Form("prMultPOIPro_cent%i",ic));
    else prMultPOI[ic] = (TProfile*) fi2->FindObjectAny(Form("prMultPOISum_cent%i",ic));
  }



  if (bDebug){
    cout << "MultMean:" << endl;
    GetMultMean(prMultRP);
  }

  Double_t dChi2[ncent]={0.};
  Double_t v2LYZInt[ncent]={0.}, v2eLYZInt[ncent]={0.};
  Double_t dVtheta[ncent][nTheta] = {{0.}};

  for (Int_t ic = 0; ic < ncent; ic++)
  {
    Double_t multRP = prMultRP->GetBinContent(ic+1);
    Double_t v2int = 0., v2eint = 0., v2theta[nTheta] = {0.};
    Int_t thetacount = 0;

    for (Int_t it = 0; it < nTheta; it++)
    {
      TH1F *hGtheta = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      Float_t r0theta = GetR0(hGtheta);
      if (r0theta!=0) 
      {
        v2int += rootJ0 / r0theta;
        v2theta[it] = rootJ0 / r0theta;
        thetacount++;
      }
    }
    if (thetacount!=0) 
    {
      if (bUseMultWeight) v2int /= thetacount; // 1/M weight gives v = V_int
      else v2int /= thetacount*multRP;
    }
    else {v2int = 0.;}
    
    Float_t modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
    Float_t Q2xmean = prQ2x->GetBinContent(ic+1);
    Float_t Q2ymean = prQ2y->GetBinContent(ic+1);
    Float_t chi2 = v2int/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int,2));
    
    Float_t temp=0.;
    for(Int_t it=0; it<nTheta; it++)
    {
      Double_t arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    Float_t neve = prMultRP->GetBinEntries(ic+1);
    Float_t err2mean = v2int*sqrt(temp/2./neve/nTheta)/rootJ0/J1rootJ0;

    for (Int_t it = 0; it < nTheta; it++) dVtheta[ic][it] = v2theta[it];
    v2LYZInt[ic] = v2int;
    dChi2[ic] = chi2;
    v2eLYZInt[ic] = err2mean;

  } // end of V2RP calculation
  

  if (bDebug){
    cout << "const Double_t chisq[" << ncent << "] = {";
    for (Int_t ic = 0; ic < ncent-1; ic++)
    {
      cout << dChi2[ic] <<", ";
    }
    cout << dChi2[ncent-1] << "};" << endl;

    cout << "const Double_t chi[" << ncent << "] = {";
    for (Int_t ic = 0; ic < ncent-1; ic++)
    {
      cout << sqrt(dChi2[ic]) <<", ";
    }
    cout << sqrt(dChi2[ncent-1]) << "};" << endl;

  }

  // Differential v2 LYZ
  Double_t v2diff[ncent][npt]={0.};
  Double_t v2diffe[ncent][npt]={0.};
  Double_t v2diff_check[ncent][npt][nTheta]={{{0.}}};
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    Double_t thetacount = 0.;
    for (Int_t ith = 0; ith < nTheta; ith++)
    {
      if (dVtheta[ic][ith] != 0)
      {
        thetacount++;
        Double_t re = prReDenom[ith]->GetBinContent(ic+1);
        Double_t im = prImDenom[ith]->GetBinContent(ic+1);
        TComplex cDenominator = TComplex(re, im);
        if (cDenominator.Rho()==0) {
          cerr<<"WARNING: modulus of cDenominator is zero" << "Cent:" << bin_cent[ic] << "-"<< bin_cent[ic+1] <<"%, Theta=" << theta[ith] <<endl;
        }
        
        for (Int_t ipt = 0; ipt < npt; ipt++)
        {
          Double_t reNum = prReNumer[ith][ic]->GetBinContent(ipt+1);
          Double_t imNum = prImNumer[ith][ic]->GetBinContent(ipt+1);
          TComplex cNumeratorPOI = TComplex(reNum, imNum);
          if (cDenominator.Rho()!=0) {
            Double_t reRatio = (cNumeratorPOI/cDenominator).Re();
            Double_t dVetaPOI = reRatio * dVtheta[ic][ith];
            v2diff[ic][ipt] += dVetaPOI;
            v2diff_check[ic][ipt][ith] = dVetaPOI;
          }
        }
      }
    }
    Double_t neve = prReDenom[0]->GetBinEntries(ic+1);
    /* Computation of statistical error bars on the average estimates */
    Double_t temp = 0.;
    Double_t arg[nTheta];
    for(Int_t k1=0; k1<nTheta; k1++)
    {
      // Float_t arg=((Float_t) it)*TMath::Pi()/(nTheta-1.);
      arg[k1] = theta[k1];

      /* Loop over the theta angles, to compute the statistical error */
      temp += (exp(sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
      exp(-sqr(rootJ0/dChi2[ic])*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
    }
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {    
      v2diff[ic][ipt] /= thetacount;
      Double_t rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
      v2diffe[ic][ipt] = sqrt(temp/rpmult/neve/nTheta)/2./J1rootJ0;
      if (ic>=2 && ic<=4)prV2Diff1040->Fill(ipt, v2diff[ic][ipt], rpmult);
    }
  } // end of Differential flow calculation by LYZ


  if (bDebug)
  {

    cout << "const Double_t v2LYZ[" << ncent << "] = {";
    for (Int_t ic = 0; ic < ncent-1; ic++)
    {
      cout << v2LYZInt[ic] <<", ";
    }
    cout << v2LYZInt[ncent-1] << "};" << endl;

    cout << "const Double_t v2eLYZ[" << ncent << "] = {";
    for (Int_t ic = 0; ic < ncent-1; ic++)
    {
      cout << v2eLYZInt[ic] <<", ";
    }
    cout << v2eLYZInt[ncent-1] << "};" << endl;   

    // Cross check integrated flow - correct!
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      Float_t multRP = prMultRP->GetBinContent(ic+1);
      for (Int_t ith = 0; ith < nTheta; ith++)
      {
        Double_t integratedFlow = 0;
        Double_t denominator = 0;
        for (Int_t ipt = 0; ipt < npt; ipt++)
        {
          Double_t rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
          integratedFlow += v2diff_check[ic][ipt][ith] * rpmult;
          denominator += rpmult;
        }
        if (denominator != 0) integratedFlow /= denominator;
        cout <<"cent: "<< ic << " " <<dVtheta[ic][ith] << "\t" << integratedFlow << endl;//multRP
      }
    }
  }

  // Stat. error calculation for 10-40%
  Double_t v2ErrLYZ1040[npt];
  Bool_t bCent1040 = 1;
  if (bCent1040)
  {
    Double_t multRP = prMultRP->GetBinContent(2+1) * prMultRP->GetBinEntries(2+1)
                   + prMultRP->GetBinContent(3+1) * prMultRP->GetBinEntries(3+1)
                   + prMultRP->GetBinContent(4+1) * prMultRP->GetBinEntries(4+1);
    multRP /= prMultRP->GetBinEntries(2+1) + prMultRP->GetBinEntries(3+1) + prMultRP->GetBinEntries(4+1);
    cout << prMultRP->GetBinContent(2+1) <<" "<<prMultRP->GetBinContent(3+1)<<" "<<prMultRP->GetBinContent(4+1) << endl; 
    if (bDebug) cout << "multRP 10-40% =" << multRP << endl;    
    Double_t v2int;
    Float_t thetacount = 0;

    for (Int_t it = 0; it < nTheta; it++)
    {
      TProfile* prRetheta = (TProfile*) prReGtheta[2][it]->Clone(Form("Clone_%s",prReGtheta[2][it]->GetName()));
      prRetheta->Add(prReGtheta[3][it]);
      prRetheta->Add(prReGtheta[4][it]);
      TProfile* prImtheta = (TProfile*) prImGtheta[2][it]->Clone(Form("Clone_%s",prImGtheta[2][it]->GetName()));
      prImtheta->Add(prImGtheta[3][it]);
      prImtheta->Add(prImGtheta[4][it]);

      TH1F *hGtheta = FillHistGtheta(prRetheta, prImtheta);
      Float_t r0theta = GetR0(hGtheta);
      if (r0theta!=0) 
      {
        v2int += rootJ0 / r0theta;
        thetacount++;
      }
    }
    if (thetacount!=0) 
    {
      if (bUseMultWeight) v2int /= thetacount; // 1/M weight gives v = V_int
      else v2int /= thetacount*multRP;
    }
    else {v2int = 0.;}
    Float_t modQ2sqmean=0, Q2xmean=0, Q2ymean=0, mult=0;
    for (Int_t ic = 2; ic < 5; ic++)
    {
      mult += prMultRP->GetBinContent(ic+1);
      modQ2sqmean += prQ2ModSq->GetBinContent(ic+1) * prMultRP->GetBinContent(ic+1);
      Q2xmean += prQ2x->GetBinContent(ic+1) * prMultRP->GetBinContent(ic+1);
      Q2ymean += prQ2y->GetBinContent(ic+1) * prMultRP->GetBinContent(ic+1);
    }
    modQ2sqmean /= mult;
    Q2xmean /= mult;
    Q2ymean /= mult;
    Float_t chi2 = v2int/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int,2));
    if (bDebug) cout << "Chi2 of 10-40%: " << chi2 << endl;
    Float_t temp=0.;
    for(Int_t it=0; it<nTheta; it++)
    {
      Double_t arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    Float_t neve = prMultRP->GetBinEntries(2+1) + prMultRP->GetBinEntries(3+1) + prMultRP->GetBinEntries(4+1);
    TProfile* prMultPOI1040 = (TProfile*) prMultPOI[2]->Clone(Form("Clone_%s",prMultPOI[2]->GetName()));
    prMultPOI1040->Add(prMultPOI[3]);
    prMultPOI1040->Add(prMultPOI[4]);
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      Double_t rpmult = prMultPOI1040->GetBinContent(ipt+1);
      v2ErrLYZ1040[ipt] = sqrt(temp/rpmult/neve/nTheta)/2./J1rootJ0;
    }
    if (bDebug) 
    {
      cout << "const Double_t v2ErrLYZ1040[" << npt <<"] = {";
      for (Int_t ipt = 0; ipt < npt-1; ipt++)
      {
        cout << v2ErrLYZ1040[ipt] <<", ";
      }
      cout << v2ErrLYZ1040[npt-1] << " };" << endl;
    }

  } // end of V2 calculation

  //================= Plotting LYZ =========================//
  Double_t centralityBin[ncent] centralityBinErr[ncent];
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    centralityBin[ic] = (bin_cent[ic]+bin_cent[ic+1])/2.;
    centralityBinErr[ic] = 0.;
  }
  Double_t X[npt], ErrX[npt], V2Diff1040[npt];
  for (Int_t ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1])/2.;
    ErrX[ipt] = 0;
    V2Diff1040[ipt] = prV2Diff1040->GetBinContent(ipt+1);
  }
  TGraphErrors *grV2Diff1040 = new TGraphErrors(npt, X, V2Diff1040, ErrX, v2ErrLYZ1040);
  TGraphErrors *grV2Int = newTGraphErrors(ncent,centralityBin,v2LYZInt,centralityBinErr,v2eLYZInt);
  TGraphErrors *grV2Diff[ncent];
  for (Int_t ic = 0l ic < ncent; ic++)
  {
    grV2Diff[ic] = new TGraphErrors(npt, X, v2diff[ic], ErrX, v2diffe[ic]);
  }

  gStyle->SetErrorX(0);
  TCanvas c;

}
