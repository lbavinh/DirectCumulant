// Draws N TGraphErrors (upper panel) with their grN/gr1 ratio (lower pannel)
TCanvas *DrawTGraph(std::vector<TGraphErrors*> vgr, TString str, 
                    Double_t yRatio_low=0.89, Double_t yRatio_high=1.11,
                    Double_t x_low=0.0, Double_t x_high=1.0,
                    Double_t y_low=0.0, Double_t y_high=1.0,
                    Double_t leg_x_low=0.22, Double_t leg_y_low=0.55,
                    Double_t leg_x_high=0.55, Double_t leg_y_high=0.89,TString strModel="", TString strCent="", bool drawLeg=1, TString titleRatioPlot = "Ratio")
{
  // Setting up global variables for the plot
  gROOT->SetStyle("Pub");
	gROOT->ForceStyle();
	gStyle->SetPalette(kDarkRainBow);// kDarkRainBow, kVisibleSpectrum, kRainBow,kPastel, kCMYK, kBlueRedYellow, kBird (default), kDeepSea
	gStyle->SetErrorX(0);

  std::vector<Double_t*> vx_gr, vy_gr, ex_gr, ey_gr;
  std::vector<Int_t> nbins;
  for (Int_t i=0; i<vgr.size();i++)
  {
    // Read poInt_ts
    vx_gr.push_back(vgr.at(i)->GetX());
    vy_gr.push_back(vgr.at(i)->GetY());

    // Read errors
    ex_gr.push_back(vgr.at(i)->GetEX());
    ey_gr.push_back(vgr.at(i)->GetEY());

    nbins.push_back(vgr.at(i)->GetN());
  }

  // Initialization of the canvas & pads
  TCanvas *canv = new TCanvas(Form("canv"),Form("Canvas"),550,550); // 900 800
  if (vgr.size() < 2) return canv;
  canv->cd();

  // canv->SetRightMargin(0.09);
  // canv->SetLeftMargin(0.20);
  // canv->SetBottomMargin(0.15);
  TPad *padUp = new TPad(Form("padUp"),"v2 vs pt",0.,0.33,1.,1.,0,-1,0);
  TPad *padDown = new TPad(Form("padDown"),"Ratio v2",0.,0.,1.,0.33,0,-1,0);

  Double_t padUW;
	Double_t padUH;
	Double_t padDW;
	Double_t padDH;

  padUp->SetBorderSize(0);
  padDown->SetBorderSize(0);
  
  padUp->SetBottomMargin(0.);
  padDown->SetTopMargin(0.005);
  
  //=====
  padUp->SetLeftMargin(0.17);
  padDown->SetLeftMargin(0.17);
  padUp->SetRightMargin(0.02);
  padDown->SetRightMargin(0.02);

  //=====

  padUW = padUp->GetWw()*padUp->GetAbsWNDC();
  padUH = padUp->GetWh()*padUp->GetAbsHNDC();
  padDW = padDown->GetWw()*padDown->GetAbsWNDC();
  padDH = padDown->GetWh()*padDown->GetAbsHNDC();
  
  padUp->Draw();
  padDown->Draw();

  // Draw TGraphErrors in the upper pad
  padUp->cd();

  // gr1->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);
  vgr.at(0)->GetXaxis()->SetLimits(x_low,x_high);
  vgr.at(0)->GetYaxis()->SetRangeUser(y_low,y_high);

  vgr.at(0)->GetXaxis()->SetLabelSize(0.06);
  vgr.at(0)->GetYaxis()->SetLabelSize(0.06);
  vgr.at(0)->GetXaxis()->SetTitleSize(0.07);
  vgr.at(0)->GetYaxis()->SetTitleSize(0.07);
  vgr.at(0)->GetYaxis()->SetTitleOffset(1.08);
  vgr.at(0)->SetLineWidth(1.);
  vgr.at(0)->Draw("AP PLC PMC");
  for (Int_t i=1; i<vgr.size();i++)
  {
    vgr.at(i)->SetLineWidth(1.);
    vgr.at(i)->Draw("P PLC PMC");
  }

  // TLegend *leg_pt = new TLegend(0.568,0.02,0.89,0.295);
  TLegend *leg_pt = new TLegend(leg_x_low,leg_y_low,leg_x_high,leg_y_high);
  leg_pt->SetBorderSize(0);
  leg_pt->SetHeader(str.Data(),"C");
  for (Int_t i=0; i<vgr.size();i++)
  {
    leg_pt->AddEntry(vgr.at(i),Form("%s",vgr.at(i)->GetTitle()),"p");
  }

  if (drawLeg) leg_pt->Draw();

  //==============================================
  TPaveText *pt = new TPaveText(0.56,0.74,0.85,0.85,"NDC NB"); // right corner 0.56,0.72,0.89,0.89
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  char hname[400];
  pt->SetTextSize(0.05);
  pt->AddText(strModel.Data());

  pt->AddText(strCent.Data());
  pt->Draw();
  padUp->Modified();

  TLine lineZero;
	lineZero.SetLineStyle(2);
  lineZero.SetLineWidth(2.);
  lineZero.SetLineColor(kAzure+2);
  // lineZero.DrawLine(x_low,0.00,x_high,0.00);
  //==============================================
  //Draw grN/gr1 ratio in the bottom pad
  padDown->cd();
  
  std::vector<Double_t> v1X;
	std::vector<Double_t> v1Y;
	std::vector<Double_t> v1Xerr;
	std::vector<Double_t> v1Yerr;
  std::vector<Double_t> v2X;
	std::vector<Double_t> v2Y;
	std::vector<Double_t> v2Xerr;
	std::vector<Double_t> v2Yerr;
  std::vector<Double_t> vRatioY;
	std::vector<Double_t> vRatioYerr;

  std::vector<TGraphErrors*> vgrRatio;
  for (Int_t igr=1; igr<vgr.size();igr++)
  {
    v1X.clear();
    v1Y.clear();
    v1Xerr.clear();
    v1Yerr.clear();
    v2X.clear();
    v2Y.clear();
    v2Xerr.clear();
    v2Yerr.clear();
    vRatioY.clear();
    vRatioYerr.clear();
    for (Int_t i=0; i<vgr.at(igr)->GetN();i++)
    {
      v1X.push_back(vx_gr.at(igr)[i]);
      v1Y.push_back(abs(vy_gr.at(igr)[i]));
      v1Xerr.push_back(ex_gr.at(igr)[i]);
      v1Yerr.push_back(ey_gr.at(igr)[i]);

      v2Y.push_back((Double_t) abs(vgr.at(0)->Eval(v1X.at(i),0,"S")));
      v2Yerr.push_back(ey_gr.at(0)[i]);

      vRatioY.push_back(v1Y.at(i)/v2Y.at(i));
      vRatioYerr.push_back(
        TMath::Sqrt(
          TMath::Power(v1Yerr.at(i)/v2Y.at(i),2) + 
          TMath::Power(v1Y.at(i)*v2Yerr.at(i)/(v2Y.at(i)*v2Y.at(i)),2)
        )
      );
    }
    vgrRatio.push_back(new TGraphErrors(v1X.size(),&v1X[0],&vRatioY[0],&v1Xerr[0],&vRatioYerr[0]));
  }
  
  padDown->SetBottomMargin(0.3);

  for (Int_t igr=0; igr<vgrRatio.size();igr++)
  {
    vgrRatio.at(igr)->GetXaxis()->SetLabelSize(0.11);
    vgrRatio.at(igr)->GetYaxis()->SetLabelSize(0.11);
    vgrRatio.at(igr)->GetXaxis()->SetTitleSize(0.12);
    vgrRatio.at(igr)->GetYaxis()->SetTitleSize(0.12);

    // vgrRatio.at(igr)->GetYaxis()->SetTitle(Form("%s/%s",vgr.at(igr+1)->GetTitle(),vgr.at(0)->GetTitle()));
    vgrRatio.at(igr)->GetYaxis()->SetTitle(titleRatioPlot.Data());
    vgrRatio.at(igr)->GetYaxis()->SetTitleOffset(0.5);
    vgrRatio.at(igr)->GetXaxis()->SetTitle(Form("%s",vgr.at(0)->GetXaxis()->GetTitle()));
    vgrRatio.at(igr)->GetYaxis()->SetNdivisions(504);
    vgrRatio.at(igr)->GetXaxis()->SetTickLength(3*12/padUH);
    vgrRatio.at(igr)->GetYaxis()->SetTickLength(2.6*12/padUW);
    vgrRatio.at(igr)->GetYaxis()->SetRangeUser(yRatio_low,yRatio_high);

    vgrRatio.at(igr)->SetMarkerStyle(vgr.at(igr+1)->GetMarkerStyle());
    vgrRatio.at(igr)->SetMarkerSize(1.6);
    vgrRatio.at(igr)->SetLineColor(vgr.at(igr+1)->GetMarkerStyle());
    vgrRatio.at(igr)->SetMarkerColor(vgr.at(igr+1)->GetMarkerStyle());
    vgrRatio.at(igr)->SetLineWidth(1.);
    // grRatio->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);
    if (igr==0)
    {
      vgrRatio.at(igr)->GetXaxis()->SetLimits(x_low,x_high);
      vgrRatio.at(igr)->Draw("AP PLC PMC");
    }
    // else{
    vgrRatio.at(igr)->Draw("P PLC PMC");
    // }

    TLine lineOne;
    lineOne.SetLineStyle(1);
    lineOne.SetLineColor(kAzure+4); // 1

    TLine line95;
    line95.SetLineWidth(2.);
    line95.SetLineStyle(2);	
    TLine line105;
    line105.SetLineWidth(2.);
    line105.SetLineStyle(2);

    TLine line90;
    line90.SetLineWidth(2.);
    line90.SetLineStyle(2);	
    TLine line110;
    line110.SetLineWidth(2.);
    line110.SetLineStyle(2);

    //========
    TLine line80;
    line80.SetLineWidth(2.);
    line80.SetLineStyle(2);	
    TLine line120;
    line120.SetLineWidth(2.);
    line120.SetLineStyle(2);

    TLine line70;
    line70.SetLineWidth(2.);
    line70.SetLineStyle(2);	
    TLine line130;
    line130.SetLineWidth(2.);
    line130.SetLineStyle(2);

    TLine line85;
    line85.SetLineWidth(2.);
    line85.SetLineStyle(2);	

    lineOne.DrawLine(x_low,1.,  x_high,1.);
    line95.DrawLine( x_low,.95, x_high,.95);
    line105.DrawLine(x_low,1.05,x_high,1.05);

  }

  return canv;
}

TProfile *PlotPtIntegratedV2(TProfile2D *const &prV2,
                             const Double_t pt_low = 0.2,
                             const Double_t pt_high = 3.0)
{
  Int_t pt_bin_low = prV2->GetYaxis()->FindBin(pt_low);
  Int_t pt_bin_high = prV2->GetYaxis()->FindBin(pt_high-0.001);
  TProfile *prV2Integrated = (TProfile *)prV2->ProfileX(Form("%s_pt_%1.1f_%1.1f",prV2->GetName(),pt_low, pt_high), pt_bin_low, pt_bin_high);
  prV2Integrated->SetTitle(Form("%.1f<p_{T}<%.1f GeV/c;Centrality, %%;v_{2}", pt_low, pt_high));
  return prV2Integrated;
}

TGraphErrors* Converter(const TProfile* const &pr)
{
  const Int_t iNbins = pr->GetNbinsX();
  std::vector<Double_t> x, errX;
  std::vector<Double_t> y, errY;
  for (Int_t i = 0; i < iNbins; i++)
  {
    x.push_back( pr->GetBinCenter(i+1) );
    y.push_back( pr->GetBinContent(i+1) );
    errX.push_back(0.);
    errY.push_back( pr->GetBinError(i+1) );
  }
  TGraphErrors *gr = new TGraphErrors(iNbins, &x[0], &y[0], &errX[0], &errY[0]);
  return gr;
}

TGraphErrors* Ratio(const TGraphErrors* const& gr1, const TGraphErrors* const& gr2)
{
  Int_t iNbins = gr2->GetN();
  Double_t *vx = (Double_t*) gr2->GetX();
  Double_t *vy2 = (Double_t*) gr2->GetY();
  Double_t *vy1 = (Double_t*) gr1->GetY();
  Double_t *vey2 = (Double_t*) gr2->GetEY();
  Double_t *vey1 = (Double_t*) gr1->GetEY();
  vector<Double_t> ratio, ratioErr, XErr;
  for (Int_t i = 0; i < iNbins; i++)
  {
    XErr.push_back(0.);
    Double_t dRatio = vy1[i] / vy2[i];
    ratio.push_back(dRatio);
    Double_t dRatioErr = dRatio*(TMath::Sqrt(TMath::Power(vey2[i]/vy2[i],2)+TMath::Power(vey1[i]/vy1[i],2)));
    ratioErr.push_back(dRatioErr);
  }
  TGraphErrors *grRatio = new TGraphErrors(iNbins, &vx[0], &ratio[0], &XErr[0], &ratioErr[0]);
  grRatio->SetMarkerStyle(gr1->GetMarkerStyle());
  grRatio->SetMarkerColor(gr1->GetMarkerStyle());
  grRatio->SetLineColor(gr1->GetMarkerStyle());
  return grRatio;
}

void Comparison(TString inputFileName = "ForthRun.root")
// methodName can be "EtaSub", "SP", "FHCalEP", "LYZEP", "Eta3Sub", "MC"
{
  int drawRatioToMethod = 0;
  TFile *fi = TFile::Open(inputFileName.Data());
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  TGraphErrors *gr[3];

  TProfile2D *pV2etasub = (TProfile2D *)fi->FindObjectAny("pV2etasub");
  TProfile2D *pV2etasubRAW = (TProfile2D *)fi->FindObjectAny("pV2etasubRAW");
  TProfile2D *pV2MC = (TProfile2D *)fi->FindObjectAny("pV2MC");
  TProfile *tmp[3];
  tmp[0] = PlotPtIntegratedV2(pV2MC,0.2,3.0);// v2 versus centrality, 0.2<pt<3.0 GeV/c
  tmp[1] = PlotPtIntegratedV2(pV2etasubRAW,0.2,3.0);// v2 versus pt, 40-80%
  tmp[2] = PlotPtIntegratedV2(pV2etasub,0.2,3.0);// v2 versus pt, 10-40%
  const char *grTitle[3]={"v_{2}{MC,EP}","v_{2}{EP,w/o AC}","v_{2}{EP}"};
  for (Int_t j=0; j<3; j++)
  {
    gr[j] = Converter(tmp[j]);
    gr[j]->GetYaxis()-> SetTitle("v_{2}");
    gr[j]->GetYaxis()->SetRangeUser(0., 0.2);
    gr[j]->SetMarkerStyle(20);
    gr[j]->SetMarkerColor(kRed);

    gr[j]->GetXaxis()-> SetTitle("Centrality, %");
    // gr[j]->GetXaxis()->SetRangeUser(0., 80);
    gr[j]->SetTitle(grTitle[j]);
  }
  TCanvas *cV2CentRF;
  std::vector<TGraphErrors*> vgrv2cent_chargedHardons;
  vgrv2cent_chargedHardons.push_back(gr[drawRatioToMethod]);
  for (int imeth=0;imeth<3;imeth++){
    if (imeth==drawRatioToMethod) continue;
    vgrv2cent_chargedHardons.push_back(gr[imeth]);
  }
  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",0.5, 1.5, 0, 8., -0.03, 0.21,
                                    0.65,0.1,0.9,0.3,
                                    "Toy Model", Form("%1.1f<p_{T}<%1.1f GeV/c",0.2,3.0),
                                    true, Form("Ratio to %s",grTitle[drawRatioToMethod]));
  cV2CentRF -> SetName("Reference flow");
  cV2CentRF -> SaveAs("./IntegratedFlow.png");

}