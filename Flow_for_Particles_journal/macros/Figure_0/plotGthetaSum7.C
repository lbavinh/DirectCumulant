#define sqr(x) ((x)*(x))
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
    
    if (dGnext > dG0 && dGnextnext > dG0 && dG0 < 1.)
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
  int iNbins = prReGtheta->GetNbinsX();
  double xMin = prReGtheta->GetXaxis()->GetBinLowEdge(1);
  double xMax = prReGtheta->GetXaxis()->GetBinLowEdge(iNbins) + prReGtheta->GetXaxis()->GetBinWidth(iNbins);
  TH1F* hGtheta = new TH1F(Form("hist_%s",prReGtheta->GetName()),"",iNbins,xMin,xMax);
  for (int rbin = 0; rbin < iNbins; rbin++)
  {
    // get bincentre of bins in histogram
    double dRe = prReGtheta->GetBinContent(rbin+1);
    double dIm = prImGtheta->GetBinContent(rbin+1);
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
void plotGthetaSum7()
{
  TFile *fi = new TFile("../FirstRun_7.7.root","read");
  const int ncent = 9;
  const int rbins = 500;
  const int thetabins = 5;
  const float rootJ0 = 2.4048256;
  const float J1rootJ0 = 0.519147;
  TProfile *prRefMult = (TProfile*) fi ->Get("prRefMult");
  TProfile *prQ2x = (TProfile*) fi ->Get("prQ2x");
  TProfile *prQ2y = (TProfile*) fi ->Get("prQ2y");
  TProfile *prQ2ModSq = (TProfile*) fi ->Get("prQ2ModSq");
  // TProfile *prV2RP = (TProfile*) fi ->Get("prV2RP");
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  // TProfile *prReGthetaProduct[ncent][thetabins];
  // TProfile *prImGthetaProduct[ncent][thetabins];
  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile*) fi -> Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile*) fi -> Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      // prReGthetaProduct[i][j] = (TProfile*) fi -> Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
      // prImGthetaProduct[i][j] = (TProfile*) fi -> Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
    }
  }


  // TH1F *test = FillHistGtheta(prReGthetaProduct[1][2], prImGthetaProduct[1][2]);
  // // // TH1F *test = FillHistGtheta(prReGthetaSum[7][0], prImGthetaSum[7][0]);
  // test -> SetMarkerStyle(kFullCircle);
  // test -> SetMarkerColor(kRed+2);
  // test -> SetMarkerSize(1.2);
  // test -> Draw("P");
  // double r0 = GetR0(test);
  // cout << "r0 = " << r0 << endl;

  TH1F *hGthetaSum[ncent][thetabins];
  // TH1F *hGthetaProduct[ncent][thetabins];

  float v2int[ncent]={0.}, v2e[ncent]={0.};
  
  for (int ic = 0; ic < ncent; ic++)
  {
    // float refmult = prRefMult->GetBinContent(ic+1);
    for (int it = 0; it < thetabins; it++)
    {
      hGthetaSum[ic][it] = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      // TH1F *hGtheta = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);
      float r0theta = GetR0(hGthetaSum[ic][it]);
      // if (ic == 3 && it == 0) cout << "r0theta = " << r0theta << endl;
      cout << "cent:" << ic <<", theta =" << it << ", r0theta = " << r0theta << endl;
      // if (it == 0) cout << rootJ0 <<"/"<< r0theta <<"/"<< refmult << " ";
      v2int[ic] += rootJ0 / r0theta;
    }
    v2int[ic] /= (float)thetabins;//refmult
    // cout << v2int[ic] << " ";
    float modQ2sqmean = prQ2ModSq->GetBinContent(ic+1);
    float Q2xmean = prQ2x->GetBinContent(ic+1);
    float Q2ymean = prQ2y->GetBinContent(ic+1);
    // float chi2 = v2int[ic]*refmult/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2));
    float chi2 = v2int[ic]/sqrt(modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic],2));
    // cout << chi2 << " ";
    // if (ic==8) cout << modQ2sqmean-Q2xmean*Q2xmean-Q2ymean*Q2ymean-pow(v2int[ic]*refmult,2) << endl;
    float temp=0.;
    for(int it=0; it<thetabins; it++) 
      /* Loop over the angles of the interpolation points,     
        to compute the statistical error bar on the average estimate V2{infty}, 
        with the help of Eqs.(89) of Ref.[A]. */
    {    
      float arg=((float) it)*TMath::Pi()/(thetabins-1.); 
      temp+=exp(sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*sin(arg/2.))+
        exp(-sqr(rootJ0/chi2)*cos(arg)/2.)*
        BesselJ0(2.*rootJ0*cos(arg/2.));
    }
    float neve = prRefMult->GetBinEntries(ic+1);
    float err2mean = v2int[ic]*sqrt(temp/2./neve/thetabins)/rootJ0/J1rootJ0;

    double dRelErr2comb = 0.;
    int iNtheta = thetabins;
    int iEvts = neve;
    double dJ01 = rootJ0;
    double dChi = chi2;
    if (iEvts!=0) {
      for (int theta=0;theta<iNtheta;theta++)
      {
	      double dTheta = ((double)theta/iNtheta)*TMath::Pi(); 
	      double dApluscomb = TMath::Exp((dJ01*dJ01)/(2*dChi*dChi)*
				       TMath::Cos(dTheta));
	      double dAmincomb = TMath::Exp(-(dJ01*dJ01)/(2*dChi*dChi)*
				       TMath::Cos(dTheta));
	             dRelErr2comb += (1/(2*iEvts*(dJ01*dJ01)*TMath::BesselJ1(dJ01)*
			         TMath::BesselJ1(dJ01)))*
	             (dApluscomb*TMath::BesselJ0(2*dJ01*TMath::Sin(dTheta/2)) + 
	             dAmincomb*TMath::BesselJ0(2*dJ01*TMath::Cos(dTheta/2)));
      }
      dRelErr2comb /= iNtheta;
    }
    double dRelErrcomb = TMath::Sqrt(dRelErr2comb);
    // float err2mean = v2int[ic] * dRelErrcomb;


    // cout << err2mean << ", ";
  }
  cout << endl;
  cout << "My flow" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << v2int[ic] << ", ";
  }
  cout << endl;

  // ==== //
  double rmax = 1.0;
  int thetaDraw = 2;
  int edge[ncent] = {1200,1200,790,550,490,460,430,45,40};
  TH1F *hGtheta[ncent];
  for (int ic=0; ic<ncent; ic++)
  {
    hGtheta[ic] = new TH1F(Form("hGtheta_%i",ic),"",2500,0,rmax);
    for (int iBin=1; iBin<edge[ic]; iBin++)
    {
      hGtheta[ic] -> SetBinContent(iBin,hGthetaSum[ic][thetaDraw]->GetBinContent(iBin));
    }
    // for (int iBin=edge[ic]; iBin<hGtheta[ic]->GetNbinsX(); iBin++)
    // {
    //   hGtheta[ic] -> SetBinContent(iBin,hGthetaSum[ic][thetaDraw]->GetBinContent(edge[ic]));
    // }

  }
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  const int markerStyle[] = {20,20,25,24,22,20,24,25,26,27,28};
  TCanvas c;
  const int textFont = 132;
  gStyle->SetLegendFont(textFont);
  c.SetTopMargin(0.12);
  c.SetLeftMargin(0.15);
  c.SetRightMargin(0.04);
  c.SetBottomMargin(0.16);
  for (int ic=0; ic<ncent; ic++)
  {
    // hGtheta[ic] -> SetMarkerStyle(markerStyle[ic]);
    hGtheta[ic] -> SetMarkerStyle(20);

    hGtheta[ic] -> SetMarkerSize(1.);
    hGtheta[ic] -> GetXaxis()->SetRangeUser(0.,0.4);
  }
  gStyle->SetPalette(kDarkRainBow);
  // hGthetaSum[0][thetaDraw] -> GetYaxis()->SetRangeUser(0,1);
  
  hGtheta[4]->SetTitle(";#it{r};|#it{G}^{#it{#theta}}(i#it{r})|^{2}");
  hGtheta[4]->GetXaxis()->SetTitleSize(0.06);
  hGtheta[4]->GetXaxis()->SetLabelSize(0.05);
  hGtheta[4]->GetYaxis()->SetTitleSize(0.06);
  hGtheta[4]->GetYaxis()->SetLabelSize(0.05);
  hGtheta[4]->GetYaxis()->SetTitleFont(textFont);
  hGtheta[4]->GetYaxis()->SetLabelFont(textFont);
  hGtheta[4]->GetXaxis()->SetTitleFont(textFont);
  hGtheta[4]->GetXaxis()->SetLabelFont(textFont);
  hGtheta[4]->Draw("P PLC PMC");
  hGtheta[4]->GetXaxis()->SetLimits(0,rmax);
  for (int ic=2; ic<ncent-3; ic++)
  {
    hGtheta[ic] -> Draw("P PLC PMC SAME");
  }
  TString legEntry[ncent] = {"0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%","60-70%","70-80%"};

  TLegend *leg = new TLegend(0.2,0.2,0.35,0.6);
  leg->SetBorderSize(0);
  leg->SetTextAlign(22);
  leg->SetTextSize(0.05);
  TString sTheta[5] = {"0","#pi/10","#pi/5","3#pi/10","2#pi/5"};

  leg->SetHeader(Form("#it{#theta} = %s",sTheta[thetaDraw].Data()));
  for (int i=2;i<ncent-3;i++)
  {
    leg -> AddEntry(hGtheta[i],legEntry[i].Data(),"p");
  }
  leg -> Draw();
  TLatex tex;
  tex.SetTextFont(textFont);
  tex.SetTextSize(0.05);
  tex.DrawLatex(0.36,0.2,"(a)");
  tex.DrawLatex(0.21,0.01,"#splitline{AMPT SM, #it{#sigma}_{p}=1.5 mb}{Au+Au at #sqrt{#it{s}_{NN}} = 7.7 GeV}");
  
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  c.SaveAs("Gtheta77.pdf");
  c.SaveAs("Gtheta77.png");
}
// hGthetaProduct[1][3]->Draw()