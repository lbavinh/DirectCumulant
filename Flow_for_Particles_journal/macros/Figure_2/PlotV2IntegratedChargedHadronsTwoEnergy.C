#include "../PlotV2IntegratedChargedHadrons.C~"

void PlotV2IntegratedChargedHadronsTwoEnergy()
{

  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow

  int ratioToMethod = 8;
  // v24 vs. v26 v28
  // int excludeMethod1 = 0;
  // int excludeMethod2 = 1;
  // int excludeMethod3 = 2;
  // int excludeMethod4 = 6;
  // int excludeMethod5 = 7;
  // int excludeMethod6 = 8;

  // //v24 vs. LYZ
  // int excludeMethod1 = 0; // EP
  // int excludeMethod2 = 1; // SP
  // int excludeMethod3 = 2; // 2
  // int excludeMethod4 = 4; // 6
  // int excludeMethod5 = 5; // 8
  // int excludeMethod6 = 8; // 2,eta-gap

  //v24 vs. others
  int excludeMethod1 = 2;
  int excludeMethod2 = 4;
  int excludeMethod3 = 5;
  int excludeMethod4 = 6;
  int excludeMethod5 = -1;
  int excludeMethod6 = -1;

  const double errX[ncent] = {0.};
  const double X[ncent] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
  bool bUseProduct = 1;
  Int_t nmethod = 9;
  TString title[]={"#it{v}_{2}{#Psi_{2,TPC}}","#it{v}_{2}^{SP}{Q_{2,TPC}}","#it{v}_{2}{2}","#it{v}_{2}{4}","#it{v}_{2}{6}","#it{v}_{2}{8}","#it{v}_{2}{LYZ, Sum}","#it{v}_{2}{LYZ}","#it{v}_{2}{2}"}; // ,#eta-gap
  // "#it{v}_{2}{#Psi_{1,FHCal}}"
  const int markerStyle[] = {24,22,23,20,30,27,26,32,25};
  const float markerSize = 1.5;
  const float labelSize = 0.07;
  const float titleSize = 0.08;
  const float titleOffSet = 0.8;
  const int textFont = 132;
  const double maxRatio = 1.11;
  const double minRatio = 0.79;
  const double maxX = 62.;
  const double minX = -1.;
  vector<TGraphErrors*> vGr77 = PlotV2IntegratedChargedHadrons("../FirstRun_7.7.root","../SecondRun_7.7.root");
  vector<TGraphErrors*> vGr115 = PlotV2IntegratedChargedHadrons("../FirstRun_11.5.root","../SecondRun_11.5.root");
  vector<TGraphErrors*> vGr77_ratio, vGr115_ratio;
  for (int i=0; i<vGr77.size(); i++)
  {
    vGr77.at(i)->SetMarkerStyle(markerStyle[i]);
    vGr115.at(i)->SetMarkerStyle(markerStyle[i]);
    TGraphErrors* vGrRatio77 = Ratio(vGr77.at(i), vGr77.at(ratioToMethod));
    vGr77_ratio.push_back(vGrRatio77);
    TGraphErrors* vGrRatio115 = Ratio(vGr115.at(i), vGr115.at(ratioToMethod));
    vGr115_ratio.push_back(vGrRatio115);
  }
  for (int i=0; i<vGr77.size(); i++)
  {
    vGr77.at(i)->GetXaxis()->SetLimits(minX,maxX);
    vGr115.at(i)->GetXaxis()->SetLimits(minX,maxX);
    vGr77_ratio.at(i)->GetXaxis()->SetLimits(minX,maxX);
    vGr115_ratio.at(i)->GetXaxis()->SetLimits(minX,maxX);

    vGr77.at(i)->GetYaxis()->SetNdivisions(504);
    vGr115.at(i)->GetYaxis()->SetNdivisions(504);
    vGr77_ratio.at(i)->GetYaxis()->SetNdivisions(508);
    vGr115_ratio.at(i)->GetYaxis()->SetNdivisions(508);

    vGr77.at(i)->GetYaxis()->SetRangeUser(-0.005,0.075);
    vGr115.at(i)->GetYaxis()->SetRangeUser(-0.005,0.075);
    vGr77_ratio.at(i)->GetYaxis()->SetRangeUser(minRatio,maxRatio);
    vGr115_ratio.at(i)->GetYaxis()->SetRangeUser(minRatio,maxRatio);

    vGr77.at(i)->SetMarkerSize(markerSize);
    vGr115.at(i)->SetMarkerSize(markerSize);
    vGr77_ratio.at(i)->SetMarkerSize(markerSize);
    vGr115_ratio.at(i)->SetMarkerSize(markerSize);
  }
  TCanvas *can = new TCanvas("can","",1000,600);
  TPaveLabel* label = new TPaveLabel(0.1,0.95,0.9,0.99,Form("AMPT SM, #it{#sigma}_{p}=1.5 mb, Au+Au, Charged Hadrons, 0.2< #it{p}_{T}<3.0 GeV/c"));
  label->SetTextFont(132);
  // label->SetTextSize(labelSize);
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();
  // gStyle->SetTextFont(132);
  gStyle->SetLegendFont(132);
  can->SetTopMargin(0.12);
  can->SetLeftMargin(0.12);
  can->SetRightMargin(0.04);
  can->SetBottomMargin(0.16);
  // gROOT->SetStyle("Pub");
  TLine lineOne;
  TLatex tex;
  tex.SetTextFont(textFont);
  tex.SetTextSize(titleSize+0.015);
  lineOne.SetLineStyle(2);
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(2,2,0,0);
  can->cd(1);


  vGr77.at(ratioToMethod)->Draw("AP PLC PMC");
  vGr77.at(ratioToMethod)->GetYaxis()->SetTitleSize(titleSize+0.015);
  vGr77.at(ratioToMethod)->GetYaxis()->SetLabelSize(labelSize+0.015);
  vGr77.at(ratioToMethod)->GetYaxis()->SetTitleFont(textFont);
  vGr77.at(ratioToMethod)->GetYaxis()->SetLabelFont(textFont);
  vGr77.at(ratioToMethod)->GetXaxis()->SetTitleSize(titleSize+0.015);
  vGr77.at(ratioToMethod)->GetXaxis()->SetLabelSize(labelSize+0.015);
  vGr77.at(ratioToMethod)->GetXaxis()->SetTitleFont(textFont);
  vGr77.at(ratioToMethod)->GetXaxis()->SetLabelFont(textFont);
  vGr77.at(ratioToMethod)->GetYaxis()->SetTitleOffset(titleOffSet-0.1);
  for (int i=0; i<vGr77.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr77.at(i)->Draw("P PLC PMC");
  }
  cout << vGr77.size() << endl;
  TLegend *leg1 = new TLegend(0.6,0.15,0.85,0.4);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(titleSize+0.015);
  tex.DrawLatex(3,0.065,"(a)   #sqrt{#it{s}_{NN}} = 7.7 GeV");  
  for (int i=0; i<2; i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6) continue;
    leg1->AddEntry(vGr77.at(i),title[i].Data(),"p");
  }
  leg1->Draw();
  vGr77.at(ratioToMethod)->SetTitle(";Centrality, %;#it{v}_{2}");

  
  can->cd(2);
  vGr115.at(ratioToMethod)->Draw("AP PLC PMC");
  vGr115.at(ratioToMethod)->GetYaxis()->SetTitleSize(titleSize);
  vGr115.at(ratioToMethod)->GetYaxis()->SetLabelSize(labelSize);
  vGr115.at(ratioToMethod)->GetYaxis()->SetTitleFont(textFont);
  vGr115.at(ratioToMethod)->GetYaxis()->SetLabelFont(textFont);
  vGr115.at(ratioToMethod)->GetXaxis()->SetTitleSize(titleSize);
  vGr115.at(ratioToMethod)->GetXaxis()->SetLabelSize(labelSize);
  vGr115.at(ratioToMethod)->GetXaxis()->SetTitleFont(textFont);
  vGr115.at(ratioToMethod)->GetXaxis()->SetLabelFont(textFont);

  for (int i=0; i<vGr115.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr115.at(i)->Draw("P PLC PMC");
  }
  TLegend *leg2 = new TLegend(0.6,0.15,0.85,0.4);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(titleSize+0.015);
  for (int i=2; i<vGr77.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6) continue;
    leg2->AddEntry(vGr77.at(i),title[i].Data(),"p");
  }
  leg2->Draw();
  tex.DrawLatex(3,0.065,"(b)   #sqrt{#it{s}_{NN}} = 11.5 GeV");
  vGr115.at(ratioToMethod)->SetTitle("");
  can->cd(3);
  vGr77_ratio.at(ratioToMethod-1)->Draw("AP PLC PMC");
  vGr77_ratio.at(ratioToMethod-1)->GetYaxis()->SetTitleSize(titleSize);
  vGr77_ratio.at(ratioToMethod-1)->GetYaxis()->SetLabelSize(labelSize);
  vGr77_ratio.at(ratioToMethod-1)->GetYaxis()->SetTitleFont(textFont);
  vGr77_ratio.at(ratioToMethod-1)->GetYaxis()->SetLabelFont(textFont);
  vGr77_ratio.at(ratioToMethod-1)->GetXaxis()->SetTitleSize(titleSize);
  vGr77_ratio.at(ratioToMethod-1)->GetXaxis()->SetLabelSize(labelSize);
  vGr77_ratio.at(ratioToMethod-1)->GetXaxis()->SetTitleFont(textFont);
  vGr77_ratio.at(ratioToMethod-1)->GetXaxis()->SetLabelFont(textFont);
  vGr77_ratio.at(ratioToMethod-1)->GetYaxis()->SetTitleOffset(titleOffSet);
  lineOne.DrawLine(minX,1.,maxX,1.);
  for (int i=0; i<vGr77_ratio.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr77_ratio.at(i)->Draw("P PLC PMC");
  }
  vGr77_ratio.at(ratioToMethod-1)->SetTitle(Form(";Centrality, %%;Ratio to %s", title[ratioToMethod].Data()));
  tex.SetTextSize(titleSize);
  tex.DrawLatex(3,1.08,"(c)");
  can->cd(4);
  vGr115_ratio.at(ratioToMethod-1)->Draw("AP PLC PMC");
  vGr115_ratio.at(ratioToMethod-1)->GetYaxis()->SetTitleSize(titleSize);
  vGr115_ratio.at(ratioToMethod-1)->GetYaxis()->SetLabelSize(labelSize);
  vGr115_ratio.at(ratioToMethod-1)->GetYaxis()->SetTitleFont(textFont);
  vGr115_ratio.at(ratioToMethod-1)->GetYaxis()->SetLabelFont(textFont);
  vGr115_ratio.at(ratioToMethod-1)->GetXaxis()->SetTitleSize(titleSize);
  vGr115_ratio.at(ratioToMethod-1)->GetXaxis()->SetLabelSize(labelSize);
  vGr115_ratio.at(ratioToMethod-1)->GetXaxis()->SetTitleFont(textFont);
  vGr115_ratio.at(ratioToMethod-1)->GetXaxis()->SetLabelFont(textFont);  

  lineOne.DrawLine(-1.,1.,61.,1.);
  for (int i=0; i<vGr115_ratio.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr115_ratio.at(i)->Draw("P PLC PMC");
  }
  vGr115_ratio.at(ratioToMethod-1)->SetTitle(Form(";Centrality, %%;Ratio to %s", title[ratioToMethod].Data()));
  tex.DrawLatex(3,1.08,"(d)");
  can->SaveAs("V2Cent_Others_AMPT.png");
  can->SaveAs("V2Cent_Others_AMPT.pdf");

}