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
void PlotGthetaSum()
{
  TFile *fi = new TFile("LYZ.root","read");
  const int ncent = 9;
  const int rbins = 100;
  const int thetabins = 5;
  const float rootJ0 = 2.4048256;
  const float J1rootJ0 = 0.519147;
  TProfile *prRefMult = (TProfile*) fi ->Get("prRefMult");
  TProfile *prQ2x = (TProfile*) fi ->Get("prQ2x");
  TProfile *prQ2y = (TProfile*) fi ->Get("prQ2y");
  TProfile *prQ2ModSq = (TProfile*) fi ->Get("prQ2ModSq");
  TProfile *prV2RP = (TProfile*) fi ->Get("prV2RP");
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
  for (int ic = 0; ic < ncent; ic++)
  {
    // float refmult = prRefMult->GetBinContent(ic+1);
    for (int it = 0; it < thetabins; it++)
    {
      hGthetaSum[ic][it] = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      // TH1F *hGtheta = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);
      float r0theta = GetR0(hGthetaSum[ic][it]);
      if (it == 0) cout << "cent:" << ic << "; r0theta = " << r0theta << endl;
      // cout << "cent:" << ic <<", theta =" << it << ", r0theta = " << r0theta << endl;
      // if (it == 0) cout << rootJ0 <<"/"<< r0theta <<"/"<< refmult << " ";
    }
  }
  cout << endl;

  TCanvas c;
  int theta = 0;
  double rmax = 1.;
  double edge[ncent] = {0.3,0.05,0.05,0.05,0.05,0.07,0.1,0.05,0.05};
  TH1F *hGtheta[ncent];
  for (int ic=0; ic<ncent; ic++)
  {
    hGtheta[ic] = (TH1F*) hGthetaSum[ic][theta]->Clone(Form("hGtheta_%i",ic));
    hGtheta[ic]->Reset();
    for (int iBin=1; iBin<hGthetaSum[ic][theta]->FindBin(edge[ic]); iBin++)
    {
      hGtheta[ic] -> SetBinContent(iBin,hGthetaSum[ic][theta]->GetBinContent(iBin));
    }
  }

  for (int ic=0; ic<ncent; ic++)
  {
    hGtheta[ic] -> SetMarkerStyle(24);
    hGtheta[ic] -> SetMarkerSize(1.2);
    hGtheta[ic]->SetLineWidth(2);
    for (int it = 0; it < thetabins; it++)
    {
      hGthetaSum[ic][it]->SetMarkerStyle(24);
      hGthetaSum[ic][it]->SetMarkerSize(1.5);
      hGthetaSum[ic][it]->SetLineWidth(2);
    }
  }
  gStyle->SetPalette(kDarkRainBow);
  // hGthetaSum[0][theta] -> GetYaxis()->SetRangeUser(0,1);
  
  hGthetaSum[1][theta]->SetTitle("Toy Model, 1M, <M>=1000;r;|G^{#theta}(ir)|");
  // hGthetaSum[1][theta]->Draw("LP PLC PMC");
  hGtheta[1]->Draw("PL PLC PMC");
  // hGthetaSum[1][theta]->GetXaxis()->SetRangeUser(0,.1);
  hGtheta[1]->GetXaxis()->SetRangeUser(0,.1);
  for (int ic=2; ic<ncent-2; ic++)
  {
    hGtheta[ic] -> Draw("PL PLC PMC SAME");
    // hGthetaSum[ic][theta] -> Draw("LP PLC PMC SAME");
  }
  TString legEntry[ncent] = {"0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%","60-70%","70-80%"};

  TLegend *leg = new TLegend(0.7,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetHeader("\\theta=0");
  for (int i=1;i<ncent-2;i++)
  {
    // leg -> AddEntry(hGthetaSum[i][theta],legEntry[i].Data(),"lp");
    leg -> AddEntry(hGtheta[i],legEntry[i].Data(),"lp");
  }
  leg -> Draw();

  gPad->SetLogy();
  gStyle->SetOptStat(0);
  // c.SaveAs("Gtheta.pdf");
  c.SaveAs("Gtheta.png");
  // c.SaveAs("Gtheta.eps");
}
// hGthetaProduct[1][3]->Draw()