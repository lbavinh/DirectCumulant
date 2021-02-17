#include "PlotV2IntegratedChargedHadrons.C"

void PlotV2IntegratedChargedHadronsTwoEnergy()
{

  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow

  int ratioToMethod = 2;
  //v24 vs. v26 v28
  // int excludeMethod1 = 0;
  // int excludeMethod2 = 1;
  // int excludeMethod3 = 2;
  // int excludeMethod4 = 6;
  // int excludeMethod5 = 7;
  // int excludeMethod6 = 8;

  //v24 vs. LYZ
  // int excludeMethod1 = 0; // EP
  // int excludeMethod2 = 1; // SP
  // int excludeMethod3 = 2; // 2
  // int excludeMethod4 = 4; // 6
  // int excludeMethod5 = 5; // 8
  // int excludeMethod6 = 8; // 2,eta-gap

  //v24 vs. others
  int excludeMethod1 = 8;
  int excludeMethod2 = 4;
  int excludeMethod3 = 5;
  int excludeMethod4 = 6;
  int excludeMethod5 = 7;
  int excludeMethod6 = -1;

  const double errX[ncent] = {0.};
  const double X[ncent] = {2.5, 7.5, 15, 25, 35, 45, 55, 65, 75};
  bool bUseProduct = 1;
  Int_t nmethod = 9;
  TString title[]={"v_{2}{#Psi_{2,TPC}}","v_{2}{SP}","v_{2}{2}","v_{2}{4}","v_{2}{6}","v_{2}{8}","v_{2}{LYZ, Sum}","v_{2}{LYZ, Prod.}","v_{2}{2,#eta-gap}"};
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.8;
  const float labelSize = 0.05;
  const double maxRatio = 1.06;
  const double minRatio = 0.78;
  vector<TGraphErrors*> vGr77 = PlotV2IntegratedChargedHadrons("FirstRun_7.7.root","SecondRun_7.7.root");
  vector<TGraphErrors*> vGr115 = PlotV2IntegratedChargedHadrons("FirstRun_11.5.root","SecondRun_11.5.root");
  vector<TGraphErrors*> vGr77_ratio, vGr115_ratio;
  for (int i=0; i<vGr77.size(); i++)
  {
    TGraphErrors* vGrRatio77 = Ratio(vGr77.at(i), vGr77.at(ratioToMethod));
    vGr77_ratio.push_back(vGrRatio77);
    TGraphErrors* vGrRatio115 = Ratio(vGr115.at(i), vGr115.at(ratioToMethod));
    vGr115_ratio.push_back(vGrRatio115);
  }
  for (int i=0; i<vGr77.size(); i++)
  {
    vGr77.at(i)->GetXaxis()->SetLimits(-1,61.);
    vGr115.at(i)->GetXaxis()->SetLimits(-1,61.);
    vGr77_ratio.at(i)->GetXaxis()->SetLimits(-1,61.);
    vGr115_ratio.at(i)->GetXaxis()->SetLimits(-1,61.);

    vGr77.at(i)->GetYaxis()->SetNdivisions(508);
    vGr115.at(i)->GetYaxis()->SetNdivisions(508);
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
  TCanvas *can = new TCanvas("can","",1600,1200);
  TPaveLabel* label = new TPaveLabel(0.1,0.96,0.9,0.99,"AMPT, #sigma_{p}=1.5 mb, Au+Au, Charged Hadrons, 0.2<p_{T}<3.0 GeV/c");
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();

  // gROOT->SetStyle("Pub");
  TLine lineOne;
  TLatex tex;
  tex.SetTextSize(labelSize);
  lineOne.SetLineStyle(2);
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(2,2,0,0);
  can->cd(1);


  vGr77.at(ratioToMethod)->Draw("AP PLC PMC");
  
  for (int i=0; i<vGr77.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr77.at(i)->Draw("P PLC PMC");
  }
  cout << vGr77.size() << endl;
  TLegend *leg1 = new TLegend(0.6,0.15,0.85,0.4);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(labelSize);
  tex.DrawLatex(5,0.065,"#sqrt{s_{NN}}=7.7GeV");  
  for (int i=0; i<4; i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6) continue;
    leg1->AddEntry(vGr77.at(i),title[i].Data(),"p");
  }
  leg1->Draw();
  vGr77.at(ratioToMethod)->SetTitle(";centrality, %;v_{2}");
  can->cd(2);
  vGr115.at(ratioToMethod)->Draw("AP PLC PMC");
  for (int i=0; i<vGr115.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr115.at(i)->Draw("P PLC PMC");
  }
  TLegend *leg2 = new TLegend(0.6,0.15,0.85,0.4);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(labelSize);
  for (int i=4; i<vGr77.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6) continue;
    leg2->AddEntry(vGr77.at(i),title[i].Data(),"p");
  }
  leg2->Draw();
  tex.DrawLatex(5,0.065,"#sqrt{s_{NN}}=11.5GeV");
  vGr115.at(ratioToMethod)->SetTitle("");
  can->cd(3);
  vGr77_ratio.at(ratioToMethod)->Draw("AP PLC PMC");
  lineOne.DrawLine(-1.,1.,61.,1.);
  for (int i=0; i<vGr77_ratio.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr77_ratio.at(i)->Draw("P PLC PMC");
  }
  vGr77_ratio.at(ratioToMethod)->SetTitle(Form(";centrality, %;Ratio to %s", title[ratioToMethod].Data()));
  can->cd(4);
  vGr115_ratio.at(ratioToMethod)->Draw("AP PLC PMC");
  lineOne.DrawLine(-1.,1.,61.,1.);
  for (int i=0; i<vGr115_ratio.size(); i++)
  {
    if (i==excludeMethod1 || i==excludeMethod2 || i==excludeMethod3 || i==excludeMethod4 || i==excludeMethod5 || i==excludeMethod6 || i==ratioToMethod) continue;
    vGr115_ratio.at(i)->Draw("P PLC PMC");
  }
  vGr115_ratio.at(ratioToMethod)->SetTitle(";centrality, %;Ratio to v_{2}{4}");
  can->SaveAs("CompareMethods.png");
  can->SaveAs("CompareMethods.pdf");

}