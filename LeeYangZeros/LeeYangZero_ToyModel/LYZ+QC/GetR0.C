#define sqr(x) ((x)*(x))
void GetRes(TProfile *const &pr)
{
  cout << "const double res2[" << pr->GetNbinsX() <<"] = {";
  for (int i=0; i<pr->GetNbinsX()-1; i++)
  {
    cout << TMath::Sqrt(pr->GetBinContent(i+1)) <<", ";
  }
  cout << TMath::Sqrt(pr->GetBinContent(pr->GetNbinsX())) <<"};" << endl;
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
void GetR0(TString inputFileName = "LYZ_nonflow_M_1000_run1.root")
{
  bool bDebug = 0;
  TFile *fi = new TFile(inputFileName.Data(),"read");
  const int ncent = 9;
  const int thetabins = 5;
  bool bUseProduct = 0;
  const double rootJ0 = 2.4048256;
  TProfile *HRes = (TProfile*) fi->Get("HRes");
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TProfile *prRefMult = (TProfile*) fi->Get("prRefMult");
  TProfile *prQ2x = (TProfile*) fi->Get("prQ2x");
  TProfile *prQ2y = (TProfile*) fi->Get("prQ2y");
  TProfile *prQ2ModSq = (TProfile*) fi->Get("prQ2ModSq");
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile*) fi->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile*) fi->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile*) fi->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile*) fi->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }    
    }
  }  
  cout << "Resolution:" << endl;
  GetRes(HRes);
  // GetMultMean(prRefMult);
  double dChi2[ncent];
  float v2int[ncent]={0.}, v2e[ncent]={0.};
  double dVtheta[ncent][thetabins] = {0.};
  TH1F *hGthetaSum[ncent][thetabins];
  cout << "const double r02[ncent][thetabins] = {";
  for (int ic = 0; ic < ncent; ic++)
  {
    float refmult = prRefMult->GetBinContent(ic+1);
    int thetacount = 0;
    cout <<"{";
    for (int it = 0; it < thetabins; it++)
    {
      TH1F *hGtheta = NULL;
      if (bUseProduct) {hGtheta = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);}
      else {
        hGtheta = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
        if (bDebug) hGthetaSum[ic][it] = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      }
      float r0theta = GetR0(hGtheta);
      // if (ic == 3 && it == 0) cout << "r0theta = " << r0theta << endl;
      // cout << "cent:" << ic <<", theta =" << it << ", r0theta = " << r0theta << endl;
      // if (it == 0) cout << rootJ0 <<"/"<< r0theta <<"/"<< refmult << " ";
      cout << r0theta << ", ";
      if (r0theta!=0) 
      {
        v2int[ic] += rootJ0 / r0theta;
        dVtheta[ic][it] = rootJ0 / r0theta;
        thetacount++;
      }
      // if (ic == 2) cout << rootJ0 / r0theta / refmult<< ", ";
    }
    cout << "}," << endl;
    if (thetacount!=0) v2int[ic] /= (float)thetacount*refmult;
    else {v2int[ic]=0.;}
    
    // cout << v2int[ic] << " ";
    float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
    float Q2xmean = prQ2x->GetBinContent(ic+1);
    float Q2ymean = prQ2y->GetBinContent(ic+1);
    float chi2 = v2int[ic]*refmult/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2));
    dChi2[ic] = chi2;
    // cout << chi2 << " ";
    // if (ic==8) cout << modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2) << endl;
  } // end of V2RP calculation
  
  cout << " };" << endl;
  cout << "const double chisq[" << ncent << "] = {";
  for (int ic = 0; ic < ncent-1; ic++)
  {
    cout << dChi2[ic] <<", ";
  }
  cout << dChi2[ncent-1] << "};" << endl;
  if (bDebug)
  {
    // ======= DEBUG ======== //
    hGthetaSum[1][1]->Draw();
    cout << GetR0(hGthetaSum[1][1]) << endl;
    gPad->SetLogy();
  }

}