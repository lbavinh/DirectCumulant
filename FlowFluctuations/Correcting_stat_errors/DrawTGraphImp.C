#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TMath.h>
#include <TString.h>
#include <TPad.h>
#include <TLine.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TProfile.h>
#include <vector>


// Draws N TGraphErrors (upper panel) with their grN/gr1 ratio (lower pannel)
TCanvas *DrawTGraph(std::vector<TGraphErrors*> vgr, TString str, 
                    Double_t yRatio_low=0.89, Double_t yRatio_high=1.11,
                    Double_t x_low=0.0, Double_t x_high=1.0,
                    Double_t y_low=0.0, Double_t y_high=1.0,
                    Double_t leg_x_low=0.22, Double_t leg_y_low=0.55,
                    Double_t leg_x_high=0.55, Double_t leg_y_high=0.89,TString strModel="", TString strCent="", bool drawLeg=1, TString ratioToMethod="")
{
  // Setting up global variables for the plot
  // gROOT->SetStyle("Pub");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
	gROOT->ForceStyle();
	gStyle->SetPalette(kDarkRainBow);// kDarkRainBow, kVisibleSpectrum, kRainBow,kPastel, kCMYK, kBlueRedYellow, kBird (default), kDeepSea
	gStyle->SetErrorX(0);

  std::vector<Double_t*> vx_gr, vy_gr, ex_gr, ey_gr;
  std::vector<Int_t> nbins;
  for (long unsigned int i=0; i<vgr.size();i++)
  {
    // Read points
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
  // canv->SetLeftMargin(0.15);
  // canv->SetBottomMargin(0.07);
  TPad *padUp = new TPad(Form("padUp"),"v2 vs pt",0.,0.4,1.,1.,0,-1,0);
  TPad *padDown = new TPad(Form("padDown"),"Ratio v2",0.,0.,1.,0.4,0,-1,0);

  // double padUW;
	// double padUH;
	// double padDW;
	// double padDH;

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

  // padUW = padUp->GetWw()*padUp->GetAbsWNDC();
  // padUH = padUp->GetWh()*padUp->GetAbsHNDC();
  // padDW = padDown->GetWw()*padDown->GetAbsWNDC();
  // padDH = padDown->GetWh()*padDown->GetAbsHNDC();
  
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

  vgr.at(0)->GetXaxis()->SetLabelFont(132);
  vgr.at(0)->GetYaxis()->SetLabelFont(132);
  vgr.at(0)->GetXaxis()->SetTitleFont(132);
  vgr.at(0)->GetYaxis()->SetTitleFont(132);
  vgr.at(0)->GetXaxis()->SetNdivisions(504);

  vgr.at(0)->Draw("AP PLC PMC");
  
  for (long unsigned int i=1; i<vgr.size();i++)
  {
    vgr.at(i)->GetXaxis()->SetLabelSize(0.06);
    vgr.at(i)->GetYaxis()->SetLabelSize(0.06);
    vgr.at(i)->GetXaxis()->SetTitleSize(0.07);
    vgr.at(i)->GetYaxis()->SetTitleSize(0.07);
    vgr.at(i)->GetYaxis()->SetTitleOffset(1.08);
    vgr.at(i)->Draw("P PLC PMC");

  }

  // TLegend *leg_pt = new TLegend(0.568,0.02,0.89,0.295);
  TLegend *leg_pt = new TLegend(leg_x_low,leg_y_low,leg_x_high,leg_y_high);
  leg_pt->SetBorderSize(0);
  leg_pt->SetHeader(str.Data(),"C");
  leg_pt->SetTextFont(132);
  leg_pt->SetTextSize(0.05);
  for (long unsigned int i=0; i<vgr.size();i++)
  {
    leg_pt->AddEntry(vgr.at(i),Form("%s",vgr.at(i)->GetTitle()),"p");
  }

  if (drawLeg) leg_pt->Draw();
  vgr.at(0)->SetTitle("");
  //==============================================
  TPaveText *pt = new TPaveText(0.5,0.7,0.85,0.85,"NDC NB"); // right corner 0.56,0.72,0.89,0.89
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  pt->SetTextFont(132);
  pt->SetTextSize(0.05);
  pt->AddText(strModel.Data());

  pt->AddText(strCent.Data());
  pt->Draw();
  padUp->Modified();

  // TLine lineZero;
	// lineZero.SetLineStyle(2);
  // lineZero.SetLineWidth(2.);
  // lineZero.SetLineColor(kAzure+2);
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
  for (long unsigned int igr=1; igr<vgr.size();igr++)
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
    for (int i=0; i<vgr.at(igr)->GetN();i++)
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

  for (long unsigned int igr=0; igr<vgrRatio.size();igr++)
  {
    vgrRatio.at(igr)->GetXaxis()->SetLabelSize(0.08);
    vgrRatio.at(igr)->GetYaxis()->SetLabelSize(0.08);
    vgrRatio.at(igr)->GetXaxis()->SetTitleSize(0.09);
    vgrRatio.at(igr)->GetYaxis()->SetTitleSize(0.09);

    vgrRatio.at(igr)->GetXaxis()->SetLabelFont(132);
    vgrRatio.at(igr)->GetYaxis()->SetLabelFont(132);
    vgrRatio.at(igr)->GetXaxis()->SetTitleFont(132);
    vgrRatio.at(igr)->GetYaxis()->SetTitleFont(132);

    // vgrRatio.at(igr)->GetYaxis()->SetTitle(Form("%s/%s",vgr.at(igr+1)->GetTitle(),vgr.at(0)->GetTitle()));
    vgrRatio.at(igr)->GetYaxis()->SetTitle(Form("Ratio to %s",ratioToMethod.Data()));
    vgrRatio.at(igr)->GetYaxis()->SetTitleOffset(1.);
    vgrRatio.at(igr)->GetXaxis()->SetTitle(Form("%s",vgr.at(0)->GetXaxis()->GetTitle()));
    vgrRatio.at(igr)->GetYaxis()->SetNdivisions(504);
    vgrRatio.at(igr)->GetXaxis()->SetNdivisions(504);
    // vgrRatio.at(igr)->GetXaxis()->SetTickLength(3*12/padUH);
    // vgrRatio.at(igr)->GetYaxis()->SetTickLength(2.6*12/padUW);
    vgrRatio.at(igr)->GetYaxis()->SetRangeUser(yRatio_low,yRatio_high);

    vgrRatio.at(igr)->SetMarkerStyle(vgr.at(igr+1)->GetMarkerStyle());
    vgrRatio.at(igr)->SetMarkerSize(1.3);
    vgrRatio.at(igr)->SetLineColor(vgr.at(igr+1)->GetMarkerStyle());
    vgrRatio.at(igr)->SetMarkerColor(vgr.at(igr+1)->GetMarkerStyle());
    vgrRatio.at(igr)->SetLineWidth(1.);
    // grRatio->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);
    if (igr==0)
    {
      vgrRatio.at(igr)->GetXaxis()->SetLimits(x_low,x_high);
      vgrRatio.at(igr)->Draw("AP PLC PMC");
      vgrRatio.at(igr)->SetTitle("");
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

    lineOne.DrawLine(x_low,1.,  x_high,1.);
    line95.DrawLine( x_low,.95, x_high,.95);
    line105.DrawLine(x_low,1.05,x_high,1.05);
  }
  return canv;
}

TCanvas *DrawTGraph(std::vector<TGraphErrors*> *vgr, Int_t const ncent, TString str, 
                    Double_t yRatio_low=0.89, Double_t yRatio_high=1.11,
                    Double_t x_low=0.0, Double_t x_high=1.0,
                    Double_t y_low=0.0, Double_t y_high=1.0,
                    Double_t leg_x_low=0.22, Double_t leg_y_low=0.55,
                    Double_t leg_x_high=0.55, Double_t leg_y_high=0.89,TString strModel="", TString *strCent = nullptr, Bool_t drawLeg=1, TString ratioToMethod="")
{
  // Setting up global variables for the plot
  // gROOT->SetStyle("Pub");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
	gROOT->ForceStyle();
	gStyle->SetPalette(kDarkRainBow);// kDarkRainBow, kVisibleSpectrum, kRainBow,kPastel, kCMYK, kBlueRedYellow, kBird (default), kDeepSea
	gStyle->SetErrorX(0);


  // Initialization of the canvas & pads
  TCanvas *canv = new TCanvas(Form("canv"),Form("Canvas"),1550,550); // 900 800
  canv->cd();

  // canv->SetRightMargin(0.09);
  // canv->SetLeftMargin(0.15);
  // canv->SetBottomMargin(0.07);
  TPad *pad_AxisX = new TPad(Form("xAxis"),"",0.,0., 1.,0.07,0,-1,0);
  pad_AxisX->SetBorderMode(0);
  pad_AxisX->SetBorderSize(0);
  pad_AxisX->Draw();
  pad_AxisX->cd();
  pad_AxisX->Range(0,0,1,1);
  pad_AxisX->SetTickx(1);
  pad_AxisX->SetTicky(1);
  pad_AxisX->SetLeftMargin(0.17);
  pad_AxisX->SetTopMargin(0);
  pad_AxisX->SetBottomMargin(0);
  pad_AxisX->SetFrameBorderMode(0);
  // TPaveText *pt_Xaxis = new TPaveText(0.11,0.89,0.11,0.89,"NDC NB"); // right corner 0.56,0.72,0.89,0.89
  // pt_Xaxis->SetBorderSize(0);
  // pt_Xaxis->SetFillColor(0);
  // pt_Xaxis->SetTextFont(132);
  // pt_Xaxis->SetTextSize(0.05);
  // pt_Xaxis->AddText(Form("%s",vgr[0].at(0)->GetXaxis()->GetTitle()));
  // pt_Xaxis->Draw();
  auto tex = new TLatex(0.5,0.5,Form("%s",vgr[0].at(0)->GetXaxis()->GetTitle()));
  tex->SetTextSize(0.6);
  tex->SetTextFont(132);
  // tex->SetLineWidth(2);
  tex->SetTextAlign(22);
  tex->Draw();
  pad_AxisX->Modified();

  canv->cd();
  canv->Modified();
  canv->cd();



  TPad *padUp[ncent], *padDown[ncent];
  for (Int_t i=0; i<ncent; i++)
  {

    padUp[i] = new TPad(Form("padUp_%i", i),"v2 vs pt",(Double_t) i/ncent,0.4,(Double_t) (i+1)/ncent, 1.,0,-1,0);
    padDown[i] = new TPad(Form("padDown_%i", i),"Ratio v2",(Double_t) i/ncent,0.07,(Double_t) (i+1)/ncent, 0.4,0,-1,0);
    padUp[i]->SetBorderSize(0);
    padDown[i]->SetBorderSize(0);
    
    padUp[i]->SetBottomMargin(0.);
    padDown[i]->SetTopMargin(0.);

    if (i!=0)
    {
      padUp[i]->SetLeftMargin(0.);
      padUp[i]->SetRightMargin(0.);
      padDown[i]->SetLeftMargin(0.);
      padDown[i]->SetRightMargin(0.);
    }
    else if (i==0)
    {
      padUp[i]->SetLeftMargin(0.17);
      padDown[i]->SetLeftMargin(0.17);
      padUp[i]->SetRightMargin(0.);
      padDown[i]->SetRightMargin(0.);      
    }
    padUp[i]->Draw();
    padDown[i]->Draw();
    // padUp->SetLeftMargin(0.17);
    // padUp->SetRightMargin(0.02);
    // padDown->SetLeftMargin(0.17);
    // padDown->SetRightMargin(0.02);
    // double padUW;
    // double padUH;
    // double padDW;
    // double padDH;

    // padUW = padUp->GetWw()*padUp->GetAbsWNDC();
    // padUH = padUp->GetWh()*padUp->GetAbsHNDC();
    // padDW = padDown->GetWw()*padDown->GetAbsWNDC();
    // padDH = padDown->GetWh()*padDown->GetAbsHNDC();
    

    // Draw TGraphErrors in the upper pad
    padUp[i]->cd();

    std::vector<Double_t*> vx_gr, vy_gr, ex_gr, ey_gr;
    std::vector<Int_t> nbins;
    for (long unsigned int j=0; j<vgr[i].size();j++)
    {
      // Read points
      vx_gr.push_back(vgr[i].at(j)->GetX());
      vy_gr.push_back(vgr[i].at(j)->GetY());

      // Read errors
      ex_gr.push_back(vgr[i].at(j)->GetEX());
      ey_gr.push_back(vgr[i].at(j)->GetEY());

      nbins.push_back(vgr[i].at(j)->GetN());
    }
    // gr1->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);
    vgr[i].at(0)->GetXaxis()->SetLimits(x_low,x_high);
    vgr[i].at(0)->GetYaxis()->SetRangeUser(y_low,y_high);

    vgr[i].at(0)->GetXaxis()->SetLabelSize(0.06);
    vgr[i].at(0)->GetYaxis()->SetLabelSize(0.06);
    vgr[i].at(0)->GetXaxis()->SetTitleSize(0.07);
    vgr[i].at(0)->GetYaxis()->SetTitleSize(0.07);
    vgr[i].at(0)->GetYaxis()->SetTitleOffset(1.08);
    vgr[i].at(0)->GetYaxis()->SetNdivisions(504);


    vgr[i].at(0)->GetXaxis()->SetLabelFont(132);
    vgr[i].at(0)->GetYaxis()->SetLabelFont(132);
    vgr[i].at(0)->GetXaxis()->SetTitleFont(132);
    vgr[i].at(0)->GetYaxis()->SetTitleFont(132);
    vgr[i].at(0)->GetXaxis()->SetNdivisions(504);

    vgr[i].at(0)->Draw("AP PLC PMC");
    
    for (long unsigned int j=1; j<vgr[i].size();j++)
    {
      vgr[i].at(j)->GetXaxis()->SetLabelSize(0.06);
      vgr[i].at(j)->GetYaxis()->SetLabelSize(0.06);
      vgr[i].at(j)->GetXaxis()->SetTitleSize(0.07);
      vgr[i].at(j)->GetYaxis()->SetTitleSize(0.07);
      vgr[i].at(j)->GetYaxis()->SetTitleOffset(1.08);
      vgr[i].at(j)->Draw("P PLC PMC");

    }
    if (i==0)
    {
      TLegend *leg_pt = new TLegend(0.2,0.45,0.5,0.7);
      // TLegend *leg_pt = new TLegend(leg_x_low,leg_y_low,leg_x_high,leg_y_high);
      leg_pt->SetBorderSize(0);
      leg_pt->SetHeader(str.Data(),"C");
      leg_pt->SetTextFont(132);
      leg_pt->SetTextSize(0.05);
      leg_pt->SetTextAlign(13);

      for (long unsigned int j=0; j<vgr[i].size();j++)
      {
        leg_pt->AddEntry(vgr[i].at(j),Form("%s",vgr[i].at(j)->GetTitle()),"p");
      }
      if (drawLeg) leg_pt->Draw();
    }


    TPaveText *pt = new TPaveText(0.2,0.7,0.45,0.85,"NDC NB"); // right corner 0.56,0.72,0.89,0.89
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextFont(132);
    pt->SetTextSize(0.05);
    pt->SetTextAlign(13);

    if (i==0) pt->AddText(strModel.Data());
    pt->AddText(strCent[i].Data());
    pt->Draw();
    padUp[i]->Modified();
    
    vgr[i].at(0)->SetTitle("");
    //==============================================

    // TLine lineZero;
    // lineZero.SetLineStyle(2);
    // lineZero.SetLineWidth(2.);
    // lineZero.SetLineColor(kAzure+2);
    // lineZero.DrawLine(x_low,0.00,x_high,0.00);
    //==============================================
    //Draw grN/gr1 ratio in the bottom pad
    padDown[i]->cd();
    
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
    for (long unsigned int igr=1; igr<vgr[i].size();igr++)
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
      for (int j=0; j<vgr[i].at(igr)->GetN();j++)
      {
        v1X.push_back(vx_gr.at(igr)[j]);
        v1Y.push_back(abs(vy_gr.at(igr)[j]));
        v1Xerr.push_back(ex_gr.at(igr)[j]);
        v1Yerr.push_back(ey_gr.at(igr)[j]);

        v2Y.push_back((Double_t) abs(vgr[i].at(0)->Eval(v1X.at(j),0,"S")));
        v2Yerr.push_back(ey_gr.at(0)[j]);

        vRatioY.push_back(v1Y.at(j)/v2Y.at(j));
        vRatioYerr.push_back(
          TMath::Sqrt(
            TMath::Power(v1Yerr.at(j)/v2Y.at(j),2) + 
            TMath::Power(v1Y.at(j)*v2Yerr.at(j)/(v2Y.at(j)*v2Y.at(j)),2)
          )
        );
      }
      vgrRatio.push_back(new TGraphErrors(v1X.size(),&v1X[0],&vRatioY[0],&v1Xerr[0],&vRatioYerr[0]));
    }
    
    padDown[i]->SetBottomMargin(0.2);

    for (long unsigned int igr=0; igr<vgrRatio.size();igr++)
    {
      vgrRatio.at(igr)->GetXaxis()->SetLabelSize(0.1);
      vgrRatio.at(igr)->GetYaxis()->SetLabelSize(0.1);
      vgrRatio.at(igr)->GetXaxis()->SetTitleSize(0.11);
      vgrRatio.at(igr)->GetYaxis()->SetTitleSize(0.11);

      vgrRatio.at(igr)->GetXaxis()->SetLabelFont(132);
      vgrRatio.at(igr)->GetYaxis()->SetLabelFont(132);
      vgrRatio.at(igr)->GetXaxis()->SetTitleFont(132);
      vgrRatio.at(igr)->GetYaxis()->SetTitleFont(132);

      // vgrRatio.at(igr)->GetYaxis()->SetTitle(Form("%s/%s",vgr.at(igr+1)->GetTitle(),vgr.at(0)->GetTitle()));
      vgrRatio.at(igr)->GetYaxis()->SetTitle(Form("Ratio to %s",ratioToMethod.Data()));
      vgrRatio.at(igr)->GetYaxis()->SetTitleOffset(0.75);
      // vgrRatio.at(igr)->GetXaxis()->SetTitle(Form("%s",vgr[i].at(0)->GetXaxis()->GetTitle()));
      vgrRatio.at(igr)->GetYaxis()->SetNdivisions(504);
      vgrRatio.at(igr)->GetXaxis()->SetNdivisions(504);
      // vgrRatio.at(igr)->GetXaxis()->SetTickLength(3*12/padUH);
      // vgrRatio.at(igr)->GetYaxis()->SetTickLength(2.6*12/padUW);
      vgrRatio.at(igr)->GetYaxis()->SetRangeUser(yRatio_low,yRatio_high);

      vgrRatio.at(igr)->SetMarkerStyle(vgr[i].at(igr+1)->GetMarkerStyle());
      vgrRatio.at(igr)->SetMarkerSize(1.3);
      vgrRatio.at(igr)->SetLineColor(vgr[i].at(igr+1)->GetMarkerStyle());
      vgrRatio.at(igr)->SetMarkerColor(vgr[i].at(igr+1)->GetMarkerStyle());
      vgrRatio.at(igr)->SetLineWidth(1.);
      // grRatio->GetXaxis()->SetLimits(0.95*vx_gr1[0],1.05*vx_gr1[n1bins-1]);
      if (igr==0)
      {
        vgrRatio.at(igr)->GetXaxis()->SetLimits(x_low,x_high);
        vgrRatio.at(igr)->Draw("AP PLC PMC");
        vgrRatio.at(igr)->SetTitle("");
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

      lineOne.DrawLine(x_low,1.,  x_high,1.);
      line95.DrawLine( x_low,.95, x_high,.95);
      line105.DrawLine(x_low,1.05,x_high,1.05);
    }
    canv->cd();
  }
  return canv;
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
  std::vector<Double_t> ratio, ratioErr, XErr;
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

TGraphErrors* Blue(TGraphErrors *const &gr)
{
  // gr->SetMarkerColor(kBlue+3);
  // gr->SetLineColor(kBlue+3);
  // gr->SetMarkerColor(kAzure-6);
  // gr->SetLineColor(kAzure-6);
  gr->SetMarkerColor(kAzure+3);
  gr->SetLineColor(kAzure+3);
  return gr;
}

TGraphErrors* Green(TGraphErrors *const &gr)
{
  gr->SetMarkerColor(kGreen+3);
  gr->SetLineColor(kGreen+3);
  return gr;
}

TGraphErrors* Yellow(TGraphErrors *const &gr)
{
  gr->SetMarkerColor(kYellow+3);
  gr->SetLineColor(kYellow+3);
  return gr;
}

TGraphErrors* Red(TGraphErrors *const &gr)
{
  gr->SetMarkerColor(kRed+2);
  gr->SetLineColor(kRed+2);
  return gr;
}

TGraphErrors* Black(TGraphErrors *const &gr)
{
  gr->SetMarkerColor(kBlack);
  gr->SetLineColor(kBlack);
  return gr;
}