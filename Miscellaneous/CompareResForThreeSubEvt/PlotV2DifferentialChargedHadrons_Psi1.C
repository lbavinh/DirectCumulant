#include "DrawTGraphImp.C"
void PlotV2DifferentialChargedHadrons_Psi1()
{
  TString energy = {"7.7"};
  const vector<pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};
  const TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)"};
  const int ratioToMethod = 2;
  const int ncent = 9;
  const Int_t npt = 16; // 0-3.6 GeV/c - number of pT bins
  // const Double_t pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
  const Double_t pTBin[npt + 1] = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
  const int markerStyle[] = {24,22,23,27,30,28,26};
  const float markerSize = 1.2;
  const float labelSize = 0.07;
  const float titleSize = 0.08;
  const float titleOffSet = 1.2;
  const int textFont = 132;
  const double maxRatio = 1.16;
  const double minRatio = 0.84;
  const double maxX = 2.8;
  const double minX = -0.08;
  const double maxY = 0.16;
  const double minY = -0.01;
  const int firstCentToDraw = 2;
  const int numberOfCentToDraw = 4;

  int excludeMethod1 = -1;
  int excludeMethod2 = -1;
  int excludeMethod3 = -1;
  int excludeMethod4 = -1;
  int excludeMethod5 = -1;
  int excludeMethod6 = -1;

  double X[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const double errX[npt] = {0.};
  bool bUseProduct = 1;
  Int_t nmethod = 3;
  TString title[]={"#it{v}_{2}{#Psi_{1,FHCal full}}","#it{v}_{2}{#Psi_{1,FHCal R}}","#it{v}_{2}{#Psi_{1,FHCal L}}"}; //  |#Delta#eta|>0.5    |#Delta#eta|>2
  TGraphErrors *graph[ncent][nmethod];
  TProfile *prV1_FHCalEP[ncent];
  TProfile *prV1_FHCalHalfEP_L[ncent];
  TProfile *prV1_FHCalHalfEP_R[ncent];
  TFile *firun1 = new TFile("v2_Psi1.root","read");
  for (int ic = 0; ic < ncent; ic++)
  {
    prV1_FHCalEP[ic] = (TProfile *) firun1->Get(Form("prV1_FHCalEP_%i",ic));
    prV1_FHCalHalfEP_R[ic] = (TProfile *) firun1->Get(Form("prV1_FHCalHalfEP_R_%i",ic));
    prV1_FHCalHalfEP_L[ic] = (TProfile *) firun1->Get(Form("prV1_FHCalHalfEP_L_%i",ic));
    graph[ic][0] = Converter(prV1_FHCalEP[ic]);
    graph[ic][1] = Converter(prV1_FHCalHalfEP_R[ic]);  
    graph[ic][2] = Converter(prV1_FHCalHalfEP_L[ic]);  
    for (int i=0; i<nmethod; i++)
    {
    // graph[ic][i]->RemovePoint(0);
    graph[ic][i]->SetTitle(title[i].Data());
    graph[ic][i]->SetMarkerStyle(markerStyle[i]);
    graph[ic][i]->SetMarkerSize(markerSize);
    graph[ic][i]->GetXaxis()->SetTitle("#it{p}_{T}, GeV/c");
    graph[ic][i]->GetYaxis()->SetTitle("#it{v}_{2}");
    graph[ic][i]->SetDrawOption("P PLC PMC");
    graph[ic][i]->GetXaxis()->SetLimits(minX,maxX);
    graph[ic][i]->GetYaxis()->SetRangeUser(minY,maxY);
    graph[ic][i]->GetXaxis()->SetNdivisions(504);
    graph[ic][i]->GetYaxis()->SetNdivisions(504);
    }
  }
  

  vector<TGraphErrors*> vGr[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int i=0; i<nmethod; i++)
    {
      vGr[ic].push_back(graph[ic][i]);
    }
  }
  vector<TGraphErrors*> vGr_ratio[ncent];
  for (int ic=0; ic<ncent; ic++)
  {
    for (int i=0; i<vGr[ic].size(); i++)
    {
      TGraphErrors *grRatio = Ratio(vGr[ic].at(i), vGr[ic].at(ratioToMethod));
      grRatio->GetXaxis()->SetLimits(minX,maxX);
      grRatio->GetYaxis()->SetRangeUser(minRatio,maxRatio);
      grRatio->SetMarkerSize(markerSize);
      grRatio->GetXaxis()->SetNdivisions(504);
      grRatio->GetYaxis()->SetNdivisions(504);
      vGr_ratio[ic].push_back(grRatio);
    }
  }

  TCanvas *can = new TCanvas("can","",1000,600);
  TPaveLabel* label = new TPaveLabel(0.1,0.95,0.9,0.99,Form("UrQMD, Au+Au at #sqrt{s_{NN}} = %s GeV, Charged Hadrons, |#eta|<1.5",energy.Data()));
  label->SetTextFont(132);
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();
  gStyle->SetLegendFont(132);
  can->SetTopMargin(0.12);
  can->SetLeftMargin(0.17);
  can->SetRightMargin(0.04);
  can->SetBottomMargin(0.17);
  TLine lineOne;
  TLatex tex;
  tex.SetTextFont(textFont);
  tex.SetTextSize(titleSize+0.015);
  lineOne.SetLineStyle(2);
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(numberOfCentToDraw,2,0,0);
  for (int ic=firstCentToDraw; ic<numberOfCentToDraw+firstCentToDraw; ic++)
  {
    int padID = ic+1-firstCentToDraw;
    can->cd(padID);
    vGr[ic].at(ratioToMethod)->Draw("AP PLC PMC");
    vGr[ic].at(ratioToMethod)->GetYaxis()->SetTitleSize(titleSize+0.015);
    vGr[ic].at(ratioToMethod)->GetYaxis()->SetLabelSize(labelSize+0.015);
    vGr[ic].at(ratioToMethod)->GetYaxis()->SetTitleFont(textFont);
    vGr[ic].at(ratioToMethod)->GetYaxis()->SetLabelFont(textFont);
    vGr[ic].at(ratioToMethod)->GetXaxis()->SetTitleSize(titleSize+0.015);
    vGr[ic].at(ratioToMethod)->GetXaxis()->SetLabelSize(labelSize+0.015);
    vGr[ic].at(ratioToMethod)->GetXaxis()->SetTitleFont(textFont);
    vGr[ic].at(ratioToMethod)->GetXaxis()->SetLabelFont(textFont);
    vGr[ic].at(ratioToMethod)->GetYaxis()->SetTitleOffset(titleOffSet-0.15);
    for (int i=0; i<vGr[ic].size(); i++)
    {
      if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
      vGr[ic].at(i)->Draw("P PLC PMC");
      
    }
    // cout << vGr[ic].size() << endl;
    tex.DrawLatex(0.2,maxY*0.8,padName[padID-1].Data());
    tex.DrawLatex(0.55,maxY*0.8,Form("%i-%i%%",centrality.at(ic).first, centrality.at(ic).second));
    if (ic==firstCentToDraw)
    {
    TLegend *leg1 = new TLegend(0.2,0.5,0.7,0.72);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(titleSize);
    
    for (int i=0; i<vGr[ic].size(); i++)
    {
      if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6) continue;
      leg1->AddEntry(vGr[ic].at(i),title[i].Data(),"p");
    }
    leg1->Draw();
    
    }
    for (int i=0; i<vGr[ic].size(); i++)
    {
      vGr[ic].at(i)->SetTitle(";#it{p}_{T}, GeV/c;#it{v}_{2}");
    }
    TLine lineZero;
    lineZero.SetLineStyle(2);
    lineZero.DrawLine(minX,0.,maxX,0.);
  }
  for (int ic=firstCentToDraw; ic<firstCentToDraw+numberOfCentToDraw; ic++)
  {
    int padID = ic+1-firstCentToDraw+numberOfCentToDraw;
    can->cd(padID);
    vGr_ratio[ic].at(ratioToMethod-1)->Draw("AP PLC PMC");
    if (ic==firstCentToDraw)
    {
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetTitleSize(titleSize);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetLabelSize(labelSize);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetTitleFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetLabelFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetTitleSize(titleSize);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetLabelSize(labelSize);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetTitleFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetLabelFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetTitleOffset(titleOffSet);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetTitleOffset(1.);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetLabelOffset(0.017);
    tex.SetTextSize(titleSize);
    }
    else
    {
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetTitleSize(titleSize+0.015);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetLabelSize(labelSize+0.015);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetTitleFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetLabelFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetTitleSize(titleSize+0.015);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetLabelSize(labelSize+0.015);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetTitleFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetLabelFont(textFont);
    vGr_ratio[ic].at(ratioToMethod-1)->GetYaxis()->SetTitleOffset(titleOffSet-0.1);
    vGr_ratio[ic].at(ratioToMethod-1)->GetXaxis()->SetTitleOffset(0.8);
    tex.SetTextSize(titleSize+0.015);
    }
    

    lineOne.DrawLine(minX,1.,maxX,1.);
    for (int i=0; i<vGr_ratio[ic].size(); i++)
    {
      if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
      vGr_ratio[ic].at(i)->Draw("P PLC PMC");
    }
    vGr_ratio[ic].at(ratioToMethod-1)->SetTitle(Form(";#it{p}_{T}, GeV/c;Ratio to %s", title[ratioToMethod].Data()));
    
    tex.DrawLatex(0.2,maxRatio*0.95,padName[padID-1].Data());
  }
  can->SaveAs(Form("v2pt_FHCalEPFull_vs_FHCalEPHalfLR.pdf"));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("v2pt_FHCalEPFull_vs_FHCalEPHalfLR.png"));

}