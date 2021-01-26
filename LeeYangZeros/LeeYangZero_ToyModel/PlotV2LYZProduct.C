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

void PlotV2LYZProduct(TString inputFileName = "LYZ_nonflow_M_1000_run1.root", TString inputFileName_sencondRun = "LYZ_nonflow_M_1000_run2.root")
{
  TString titleGraph = "Toy Model, 1M events, <M>=1000";
  TFile *fi = new TFile(inputFileName.Data(), "read");

  const int ncent = 9; // 0-80%
  const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
  const int thetabins = 5;
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  bool bUseProduct = 0;
    const double rootJ0 = 2.4048256;
    TProfile *HRes = (TProfile*) fi->Get("HRes");
  TProfile *hv2MC = (TProfile*) fi->Get("hv2MC");

  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TH1F *hGthetaSum[ncent][thetabins];

  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TH1F *hGthetaProduct[ncent][thetabins];


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
      hGthetaSum[i][j] = (TH1F*) fi->Get(Form("hGthetaSum_mult%d_theta%d", i, j));
      if (bUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile*) fi->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile*) fi->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
        hGthetaProduct[i][j] = (TH1F*) fi->Get(Form("hGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }
  const double J1rootJ0 = 0.519147;
  const int npt = 12;
  const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};  
  TComplex cDenominator, cExpo;
  TFile *fi2 = new TFile(inputFileName_sencondRun.Data(),"read");
  TProfile *hv2EP = (TProfile*) fi2->Get("hv2EP");
  // Differential flow
  TProfile *prReDenom[thetabins];
  TProfile *prImDenom[thetabins];
  TProfile *prReNumer[thetabins][ncent];
  TProfile *prImNumer[thetabins][ncent];
  for (int i = 0; i < thetabins; i++)
  {
    prReDenom[i] = (TProfile*) fi2->Get(Form("prReDenom_theta%i",i));
    prImDenom[i] = (TProfile*) fi2->Get(Form("prImDenom_theta%i",i));

    for (int j = 0; j < ncent; j++)
    {
      prReNumer[i][j] = (TProfile*) fi2->Get(Form("prReNumer_theta%i_cent%i", i, j));
      prImNumer[i][j] = (TProfile*) fi2->Get(Form("prImNumer_theta%i_cent%i", i, j));
    }
  }

  TProfile *prReDenomPro[thetabins];
  TProfile *prImDenomPro[thetabins];
  TProfile *prReNumerPro[thetabins][ncent];
  TProfile *prImNumerPro[thetabins][ncent];
  for (int i = 0; i < thetabins; i++)
  {
    prReDenomPro[i] = (TProfile*) fi2->Get(Form("prReDenomPro_theta%i",i));
    prImDenomPro[i] = (TProfile*) fi2->Get(Form("prImDenomPro_theta%i",i));

    for (int j = 0; j < ncent; j++)
    {
      prReNumerPro[i][j] = (TProfile*) fi2->Get(Form("prReNumerPro_theta%i_cent%i", i, j));
      prImNumerPro[i][j] = (TProfile*) fi2->Get(Form("prImNumerPro_theta%i_cent%i", i, j));
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
  // GetRes(HRes);
  // GetMultMean(prRefMult);
  double dChi2[ncent];
  float v2int[ncent]={0.}, v2e[ncent]={0.};
  double dVtheta[ncent][thetabins] = {0.};
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
      else {hGtheta = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);}
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
    float temp=0.;
    for(int it=0; it<thetabins; it++) 
      /* Loop over the angles of the interpolation points,     
        to compute the statistical error bar on the average estimate V2{infty}, 
        with the help of Eqs.(89) of Ref.[A]. */
    {    
      // float arg=((float) it)*TMath::Pi()/(thetabins-1.);
      double arg = theta[it];
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    float neve = prRefMult->GetBinEntries(ic+1);
    float err2mean = v2int[ic]*sqrt(temp/2./neve/thetabins)/rootJ0/J1rootJ0;
    v2e[ic] = err2mean;
    // cout << err2mean << ", ";
  } // end of V2RP calculation
  
  cout << " };" << endl;
  // ===== Get Chi2 ===== //
  cout << "const double chisq[" << ncent << "] = {";
  for (int ic = 0; ic < ncent-1; ic++)
  {cout << dChi2[ic] <<", ";}
  cout << dChi2[ncent-1] << "};" << endl;
  // ===== Get Chi2 ===== //
  TH1F *hLYZ = new TH1F("hLYZ","",ncent,&bin_cent[0]);
  for (int ic=0; ic<ncent; ic++)
  {
    hLYZ->SetBinContent(ic+1,v2int[ic]);
    hLYZ->SetBinError(ic+1,v2e[ic]);
  }

  
  // Differential v2 LYZ
  TComplex cNumeratorPOI;
  double re, im, reRatio;
  double v2diff[ncent][npt]={0.};
  double v2diffe[ncent][npt]={0.};
  double dV2thetaDif[ncent][npt][thetabins] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
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
    int thetacount[npt] = {0};
    for (int thetabin = 0; thetabin < thetabins; thetabin++)
    {
      re = prReDenom[thetabin]->GetBinContent(ic+1);
      im = prImDenom[thetabin]->GetBinContent(ic+1);
      cDenominator = TComplex(re, im);
      if (cDenominator.Rho()==0) {
	      cerr<<"WARNING: modulus of cDenominator is zero"<<endl;
	    }

      for (int ipt = 0; ipt < npt; ipt++)
      {
        re = prReNumer[thetabin][ic]->GetBinContent(ipt+1);
        im = prImNumer[thetabin][ic]->GetBinContent(ipt+1);
        cNumeratorPOI = TComplex(re, im);
        if (cDenominator.Rho()!=0) {
          reRatio = (cNumeratorPOI/cDenominator).Re();
          double dVthetaPOI = reRatio * dVtheta[ic][thetabin];
          // cout << "reRatio * dVtheta[ic][thetabin] = " << reRatio <<" * "<< dVtheta[ic][thetabin] << endl;
          if (dVtheta[ic][thetabin] != 0)
          { 
            v2diff[ic][ipt] += dVthetaPOI;
            dV2thetaDif[ic][ipt][thetabin] = dVthetaPOI;
            thetacount[ipt]++;
          }
        }
      }
    }
    double neve = prReDenom[0]->GetBinEntries(ic+1);
    for (int ipt = 0; ipt < npt; ipt++)
    {    
      v2diff[ic][ipt] /= thetacount[ipt];
      double rpmult = prMultPOI[ic]->GetBinContent(ipt+1);
      v2diffe[ic][ipt] = sqrt(temp/rpmult/neve/thetabins)/2./J1rootJ0;
      // if (ic == 2) cout << v2diffe[ic][ipt] << ", ";
    }

  }
  // Cross-check // => Result: Correct!
  // for (int it = 0; it < thetabins; it++)
  // {
  //   cout << "Theta = " << theta[it] << endl;
  //   for (int ic = 0; ic < ncent; ic++)
  //   {
  //     double v2IntOverPt = 0, w = 0, sumW = 0;
  //     for (int ipt = 0; ipt < npt; ipt++)
  //     {
  //       w = prMultPOI[ic]->GetBinContent(ipt+1);
  //       v2IntOverPt += dV2thetaDif[ic][ipt][it] * w;
  //       sumW += w;
  //     }
  //     v2IntOverPt /= sumW;

  //     cout << "Cent: " << ic << " " << v2IntOverPt << "\t" << dVtheta[ic][it] / prRefMult->GetBinContent(ic+1) << endl;
  //   }
  // }
  double v2diffMC[ncent][npt] = {0.}, v2diffeMC[ncent][npt] = {0.}, v2diffEP[ncent][npt] = {0.}, v2diffeEP[ncent][npt] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      v2diffMC[ic][ipt] = hv2MCpt[ic]->GetBinContent(ipt+1);
      v2diffeMC[ic][ipt] = hv2MCpt[ic]->GetBinError(ipt+1);
      v2diffEP[ic][ipt] = hv2EPpt[ic]->GetBinContent(ipt+1);
      v2diffeEP[ic][ipt] = hv2EPpt[ic]->GetBinError(ipt+1);
    }
  }
  double dRatio[ncent][npt][2] = {0.}, dRatioErr[ncent][npt][2] = {0.};
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      // for (int i = 0; i < 3; i++)
      // {
        dRatio[ic][ipt][0] = v2diffEP[ic][ipt] / v2diffMC[ic][ipt];
        dRatio[ic][ipt][1] = v2diff[ic][ipt] / v2diffMC[ic][ipt];
        dRatioErr[ic][ipt][0] = dRatio[ic][ipt][0] * sqrt(pow(v2diffeEP[ic][ipt] / v2diffEP[ic][ipt], 2) + pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2));
        dRatioErr[ic][ipt][1] = dRatio[ic][ipt][1] * sqrt(pow(v2diffe[ic][ipt] / v2diff[ic][ipt], 2) + pow(v2diffeMC[ic][ipt] / v2diffMC[ic][ipt], 2));      
      // }
    }
  }

  //================= Drawing =========================
  TCanvas c;
  // TPaveLabel* title1 = new TPaveLabel(0.1,0.95,0.9,0.98,"Toy Model, 1M events, <M>=1000");
  // title1->SetBorderSize(0);
  // title1->SetFillColor(0);
  // // title1->SetTextFont(textFont);
  // // title1->SetTextSize(2.);
  // title1->Draw();
  hLYZ->SetMarkerStyle(23);
  hLYZ->SetMarkerColor(kBlue+2);
  hLYZ->SetLineColor(kBlue+2);

  hv2EP->SetMarkerStyle(20);
  hv2EP->SetMarkerColor(kRed+2);
  hv2EP->SetLineColor(kRed+2);

  hv2MC->SetMarkerStyle(25);
  hv2MC->SetMarkerColor(kBlack);
  hv2MC->SetLineColor(kBlack);
  hv2MC->SetTitle(Form("%s;centrality, %%;v_{2}",titleGraph.Data()));
  hv2MC->GetYaxis()->SetRangeUser(0,0.1);
  hv2MC->GetXaxis()->SetLimits(0,60);
  hv2MC->Draw();
  hv2EP->Draw("same");
  hLYZ->Draw("same");
  TLegend *leg = new TLegend(0.55,0.15,0.8,0.35);
  leg->SetBorderSize(0);
  leg->AddEntry(hv2MC,"MC","p");
  leg->AddEntry(hv2EP,"EP","p");
  leg->AddEntry(hLYZ,"LYZ","p");
  leg->Draw();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  c.SaveAs("Flow.pdf");
  //================= Drawing =========================
  TCanvas c2;
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,titleGraph.Data());
  title->SetBorderSize(0);
  title->SetFillColor(0);
  // title->SetTextFont(textFont);
  // title->SetTextSize(2.);
  title->Draw();
  // int centrality = 4; // 10-20%
  // c2.SetLeftMargin(0.13);
  TString legHeader[] = {"0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%","60-70%","70-80%"};
  c2.Divide(3,2,0,0);
  for (int centrality = 1; centrality < 7; centrality++){
  c2.cd(centrality);
  TH1F *hLYZDiff = new TH1F("hLYZDiff","",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiff->SetBinContent(ipt+1,v2diff[centrality][ipt]);
    hLYZDiff->SetBinError(ipt+1,v2diffe[centrality][ipt]);
  }
  hLYZDiff->SetMarkerStyle(23);
  hLYZDiff->SetMarkerColor(kBlue+2);
  hLYZDiff->SetLineColor(kBlue+2);
  hLYZDiff->GetXaxis()->SetLimits(-0.1,3.6);
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
  TLegend *leg2 = new TLegend(0.15,0.7,0.4,0.9);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[centrality].Data());
  leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ","p");
  // leg2->AddEntry(hLYZ,"LYZ","p");
  leg2->Draw();
  // c2.SaveAs(Form("DifFlow_%i.png",centrality));
  }
  c2.SaveAs(Form("DifFlow.pdf"));
  //================= Drawing =========================
  TCanvas c3("c3","",1400,700);
  TPaveLabel* title3 = new TPaveLabel(0.1,0.96,0.9,0.99,titleGraph.Data());
  title3->SetBorderSize(0);
  title3->SetFillColor(0);
  // title3->SetTextFont(textFont);
  // title3->SetTextSize(2.);
  title3->Draw();
  // TCanvas c3;
  c3.Divide(6,2,0,0);
  // gROOT->SetStyle("Pub");
  c3.SetLeftMargin(0.15);
  // gStyle->SetTextSize(2.5);
  for (int centrality = 1; centrality < 7; centrality++){
  c3.cd(centrality);
  TH1F *hLYZDiff = new TH1F("hLYZDiff","",npt,&bin_pT[0]);
  for (int ipt=0; ipt<npt; ipt++)
  {
    hLYZDiff->SetBinContent(ipt+1,v2diff[centrality][ipt]);
    hLYZDiff->SetBinError(ipt+1,v2diffe[centrality][ipt]);
  }

  hLYZDiff->SetMarkerStyle(23);
  hLYZDiff->SetMarkerColor(kBlue+2);
  hLYZDiff->SetLineColor(kBlue+2);
  hLYZDiff->GetXaxis()->SetLimits(-0.1,3.6);
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
  TLegend *leg2 = new TLegend(0.15,0.7,0.4,0.9);
  leg2->SetBorderSize(0);
  leg2->SetHeader(legHeader[centrality].Data());
  leg2->AddEntry(hv2MCpt[centrality],"MC","p");
  leg2->AddEntry(hv2EPpt[centrality],"EP","p");
  leg2->AddEntry(hLYZDiff,"LYZ","p");
  // leg2->AddEntry(hLYZ,"LYZ","p");
  leg2->Draw();
  }
  for (int centrality = 1; centrality < 7; centrality++){
    c3.cd(centrality+6);

    TH1F *hLYZDiffRatio = new TH1F("hLYZDiffRatio","",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hLYZDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][1]);
      hLYZDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][1]);
    }
    hLYZDiffRatio->SetMarkerStyle(23);
    hLYZDiffRatio->SetMarkerColor(kBlue+2);
    hLYZDiffRatio->SetLineColor(kBlue+2);
    hLYZDiffRatio->SetTitle(";p_{T}, GeV/c;Ratio to MC");
    // hLYZDiffRatio->GetXaxis()->SetLabelSize(0.5);
    hLYZDiffRatio->GetYaxis()->SetRangeUser(0.89,1.11);
    TH1F *hEPDiffRatio = new TH1F("hEPDiffRatio","",npt,&bin_pT[0]);
    for (int ipt=0; ipt<npt; ipt++)
    {
      hEPDiffRatio->SetBinContent(ipt+1,dRatio[centrality][ipt][0]);
      hEPDiffRatio->SetBinError(ipt+1,dRatioErr[centrality][ipt][0]);
    }
    hEPDiffRatio->SetMarkerStyle(20);
    hEPDiffRatio->SetMarkerColor(kRed+2);
    hEPDiffRatio->SetLineColor(kRed+2);
    hLYZDiffRatio->Draw();
    hEPDiffRatio->Draw("same");
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(0.2,1.,3.5,1.);
  }
  c3.SaveAs("RatioDiffFlow.pdf");
}
