// Draws 2 TGraphErrors (upper panel) with their gr1/gr2 ratio (lower pannel)
TCanvas *DrawTGraph(TGraphErrors *const &gr1, TGraphErrors *const &gr2, TString str="", 
                    Double_t yRatio_low=0.89, Double_t yRatio_high=1.11,
                    Double_t x_low=0.0, Double_t x_high=1.0,
                    Double_t y_low=0.0, Double_t y_high=1.0,
                    Double_t leg_x_low=0.18, Double_t leg_y_low=0.72,
                    Double_t leg_x_high=0.42, Double_t leg_y_high=0.89, TString strCent="")
{
  // Setting up global variables for the plot
  gROOT->SetStyle("Pub");
	gROOT->ForceStyle();
	gStyle->SetPalette(kDarkRainBow);
	gStyle->SetErrorX(0);

  // Read points
  Double_t *vx_gr1 = gr1->GetX();
  Double_t *vy_gr1 = gr1->GetY();
  Double_t *vx_gr2 = gr2->GetX();
  Double_t *vy_gr2 = gr2->GetY();

  // Read errors
  Double_t *ex_gr1 = gr1->GetEX();
  Double_t *ey_gr1 = gr1->GetEY();
  Double_t *ex_gr2 = gr2->GetEX();
  Double_t *ey_gr2 = gr2->GetEY();

  Int_t n1bins = gr1->GetN();

  // Initialization of the canvas & pads
  TCanvas *canv = new TCanvas(Form("canv"),Form("Canvas"),900,800);
  canv->cd();
  TPad *padUp = new TPad(Form("padUp"),"v2 vs pt",0.,0.33,1.,1.,0,-1,0);
  TPad *padDown = new TPad(Form("padDown"),"Ratio v2",0.,0.,1.,0.33,0,-1,0);

  double padUW;
	double padUH;
	double padDW;
	double padDH;

  padUp->SetBorderSize(0);
  padDown->SetBorderSize(0);
  
  padUp->SetBottomMargin(0.);
  padDown->SetTopMargin(0.005);
  
  padUW = padUp->GetWw()*padUp->GetAbsWNDC();
  padUH = padUp->GetWh()*padUp->GetAbsHNDC();
  padDW = padDown->GetWw()*padDown->GetAbsWNDC();
  padDH = padDown->GetWh()*padDown->GetAbsHNDC();
  
  padUp->Draw();
  padDown->Draw();

  // Setting up markers & colors for TGraphErrors

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.6);
  gr1->SetLineColor(kGreen+2);
  gr1->SetMarkerColor(kGreen+2);

  gr2 -> SetMinimum(y_low);
  gr2 -> SetMaximum(y_high);

  gr2->SetMarkerStyle(25);
  gr2->SetMarkerSize(1.6);
  gr2->SetLineColor(kRed+1);
  gr2->SetMarkerColor(kRed+1);

  // Draw TGraphErrors in the upper pad
  padUp->cd();
  
  // gr1->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);

  gr2->GetXaxis()->SetLabelSize(0.06);
  gr2->GetYaxis()->SetLabelSize(0.06);
  gr2->GetXaxis()->SetTitleSize(0.07);
  gr2->GetYaxis()->SetTitleSize(0.07);
  gr2->GetYaxis()->SetTitleOffset(1.08);
  
  gr2->Draw("AP");
  // gPad->Modified(); gPad->Update();
  gr2->GetXaxis()-> SetLimits(x_low,x_high);
  // gPad->Modified(); gPad->Update();
  gr1->Draw("P");

  TLegend *leg_pt = new TLegend(leg_x_low,leg_y_low,leg_x_high,leg_y_high);
  leg_pt->SetBorderSize(0);
  leg_pt->SetHeader(str.Data(),"C");
  // leg_pt->SetHeader(Form("Au+Au,#sqrt{s_{NN}}=200 GeV"),"C");
  leg_pt->AddEntry(gr1,Form("%s",gr1->GetTitle()),"p");
  leg_pt->AddEntry(gr2,Form("%s",gr2->GetTitle()),"p");

  leg_pt->Draw();
  // ======

  TPaveText *pt = new TPaveText(0.42,0.72,0.75,0.89,"NDC NB"); // 0.56,0.72,0.89,0.89 right corner
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  char hname[400];
  pt->AddText("");// UrQMD Au+Au @ #sqrt{s_{NN}}=7.7 GeV

  pt->AddText(strCent.Data());
  pt->Draw();
  padUp->Modified();

  // ======
  TLine lineZero;
	lineZero.SetLineStyle(2);
  lineZero.SetLineWidth(2.);
  lineZero.SetLineColor(kAzure+2);
  lineZero.DrawLine(x_low,0.00,x_high,0.00);
  //Draw gr1/gr2 ratio in the bottom pad
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

  for (int i=0; i<gr1->GetN();i++)
  {
    v1X.push_back(vx_gr1[i]);
    v1Y.push_back(vy_gr1[i]);
    v1Xerr.push_back(ex_gr1[i]);
    v1Yerr.push_back(ey_gr1[i]);

    v2Y.push_back((Double_t) gr2->Eval(v1X.at(i),0,"S"));
    v2Yerr.push_back(ey_gr2[i]);

    vRatioY.push_back(v1Y.at(i)/v2Y.at(i));
    vRatioYerr.push_back(
      TMath::Sqrt(
        TMath::Power(v1Yerr.at(i)/v2Y.at(i),2) + 
        TMath::Power(v1Y.at(i)*v2Yerr.at(i)/(v2Y.at(i)*v2Y.at(i)),2)
      )
    );
  }
  TGraphErrors *grRatio = new TGraphErrors(v1X.size(),&v1X[0],&vRatioY[0],&v1Xerr[0],&vRatioYerr[0]);

  grRatio->GetXaxis()->SetLabelSize(0.11);
  grRatio->GetYaxis()->SetLabelSize(0.11);
  grRatio->GetXaxis()->SetTitleSize(0.12);
  grRatio->GetYaxis()->SetTitleSize(0.12);

  grRatio->GetYaxis()->SetTitle(Form("%s/%s",gr1->GetTitle(),gr2->GetTitle()));
  grRatio->GetYaxis()->SetTitleOffset(0.65);
  grRatio->GetXaxis()->SetTitle(Form("%s",gr1->GetXaxis()->GetTitle()));
  padDown->SetBottomMargin(0.3);
  grRatio->GetYaxis()->SetNdivisions(504);
  grRatio->GetXaxis()->SetTickLength(3*12/padUH);
  grRatio->GetYaxis()->SetTickLength(2.6*12/padUW);
  grRatio->GetYaxis()->SetRangeUser(yRatio_low,yRatio_high);
  // grRatio->GetYaxis()->SetRangeUser(0.81,1.19);

  grRatio->SetMarkerStyle(20);
  grRatio->SetMarkerSize(1.6);
  grRatio->SetLineColor(kGreen+2);
  grRatio->SetMarkerColor(kGreen+2);

  // grRatio->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);
  grRatio->GetXaxis()-> SetLimits(x_low,x_high);
  //gPad->Modified(); gPad->Update();
  grRatio->Draw("AP");

  TLine lineOne;
	lineOne.SetLineStyle(1);
  lineOne.SetLineColor(kAzure+2);
	TLine line90;
	line90.SetLineWidth(2.);
	line90.SetLineStyle(2);	
	TLine line110;
	line110.SetLineWidth(2.);
	line110.SetLineStyle(2);

	TLine line80;
	line80.SetLineWidth(2.);
	line80.SetLineStyle(2);	
	TLine line120;
	line120.SetLineWidth(2.);
	line120.SetLineStyle(2);

  // lineOne.SetLineColor(kRed);
  // lineOne.DrawLine(0.95*vx_gr1[0],1.,  1.05*vx_gr1[n1bins-1],1.);
  // line90.DrawLine( 0.95*vx_gr1[0],.95, 1.05*vx_gr1[n1bins-1],.95);
  // line110.DrawLine(0.95*vx_gr1[0],1.05,1.05*vx_gr1[n1bins-1],1.05);

  // lineOne.DrawLine(0,1.00,2.8,1.00);
  // line90.DrawLine( 0,0.95,2.8,0.95);
  // line110.DrawLine(0,1.05,2.8,1.05);

  lineOne.DrawLine(x_low,1.00,x_high,1.00);
  line90.DrawLine( x_low,0.9,x_high,0.9);
  line110.DrawLine(x_low,1.1,x_high,1.1);


  line80.DrawLine( x_low,0.8,x_high,0.8);
  line120.DrawLine(x_low,1.2,x_high,1.2);

  return canv;
}