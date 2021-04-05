#define PERFORMANCEQC
// #include "PlotV2EtaSubEventPlane.C"
// #include "PlotV2ScalarProduct.C"
#include "PlotV2QCumulant.C"
// #include "PlotV2QCumulant_Model.C"
// #include "constants.C"
// vector<TGraphErrors*>*
void Performance_QC_protons_and_pions(TString inputModel = "FirstRun_vHLLEUrQMD_11.5_Model.root", TString inputRECO = "FirstRun_vHLLEUrQMD_11.5_Reco_Nhits_32.root")
{
const Int_t npt = 16; // 0-3.6 GeV/c - number of pT bins
const Double_t pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const int ratioToMethod = 0;
  double X[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const double errX[npt] = {0.};
  bool bUseProduct = 1;
  Int_t nmethod = 2;
  TString title[]={"Model","Reco"};// MC GEANT4 Reco
  const int markerStyle[] = {20,22,24,26};
  const float markerSize = 1.3;
  const int particle = 2;
  const int cent = 4;
  const int firstCentToDraw = 1;
  TString PIDNAMEFancy[particle] = {"#pi^{#pm}","p"};
  TString PIDNAME = "pion_and_proton";
  TGraphErrors *graph[cent][particle][nmethod];
  for (int i = 0; i < cent; i++)
  {
    graph[i][0][0] = PlotV2QCumulant_Model(inputModel,3,firstCentToDraw+i,9); // pi
    graph[i][0][1] = PlotV2QCumulant(inputRECO,2,firstCentToDraw+i,9);
    graph[i][1][0] = PlotV2QCumulant_Model(inputModel,3,firstCentToDraw+i,3); // p
    graph[i][1][1] = PlotV2QCumulant(inputRECO,2,firstCentToDraw+i,3);
  }
  

  for (int ic = 0; ic < cent; ic++)
  {
    for (int id=0; id<particle; id++)
    {
      for (int i=0; i<nmethod; i++)
      {
      // graph[ic][i]->RemovePoint(0);
      graph[ic][id][i]->SetTitle("");
      graph[ic][id][i]->SetMarkerSize(markerSize);
      graph[ic][id][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
      graph[ic][id][i]->GetYaxis()->SetTitle("v_{2}{2}"); // 2,|#Delta#eta|>0.1
      graph[ic][id][i]->SetDrawOption("P PLC PMC");
      graph[ic][id][i]->GetXaxis()->SetLimits(0.,2.8);
      graph[ic][id][i]->GetYaxis()->SetRangeUser(0.,0.23);
      }
    }
    Red(graph[ic][0][0]);
    Red(graph[ic][0][1]);
    Blue(graph[ic][1][0]);
    Blue(graph[ic][1][1]);
    graph[ic][0][0]->SetMarkerStyle(20);
    graph[ic][0][1]->SetMarkerStyle(24);
    graph[ic][1][0]->SetMarkerStyle(22);
    graph[ic][1][1]->SetMarkerStyle(26);
  }
  const vector<pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};
  const TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)"};
  TCanvas *c = new TCanvas("c","",1200,600);
  TPaveLabel* label = new TPaveLabel(0.1,0.95,0.9,0.99,Form("vHLLE+UrQMD XPT, Au+Au #sqrt{s_{NN}} = 11.5 GeV"));
  label->SetTextFont(132);
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();
  // c->SetTopMargin(0.12);
  c->SetLeftMargin(0.17);
  c->SetRightMargin(0.04);
  // c->SetBottomMargin(0.17);
  TLatex tex;
  tex.SetTextFont(132);
  // tex.SetTextSize(0.1);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  c->Divide(cent,1,0,0);
  for (int i=0; i<cent; i++)
  {
    c->cd(i+1);
    tex.DrawLatex(0.2,0.22,padName[i].Data());
    tex.DrawLatex(0.25,0.22,Form("%i-%i%%",centrality.at(i+firstCentToDraw).first, centrality.at(i+firstCentToDraw).second));
    graph[i][0][0]->Draw("AP");
    graph[i][0][1]->Draw("P");
    graph[i][1][0]->Draw("P");
    graph[i][1][1]->Draw("P");
  }
  c->SaveAs("Performance_2QC_protons_and_pions.pdf");
  c->SaveAs("Performance_2QC_protons_and_pions.png");

}