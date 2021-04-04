#define PERFORMANCEQC
// #include "PlotV2EtaSubEventPlane.C"
// #include "PlotV2ScalarProduct.C"
#include "PlotV2QCumulant.C"
// #include "DrawTGraph.C"
#include "constants.C"
// vector<TGraphErrors*>*
void Performance_QC(TString inputMC = "FirstRun_vHLLEUrQMD_11.5_MC.root", TString inputRECO = "FirstRun_vHLLEUrQMD_11.5_Reco.root")
{

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
  TString title[]={"MC","Reco"};// 
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[1][nmethod];
  for (int i = 0; i < 1; i++)
  {

    graph[i][0] = PlotV2QCumulant(inputMC);
    graph[i][1] = PlotV2QCumulant(inputRECO);
  }
  

  for (int ic = 0; ic < 1; ic++)
  {
    for (int i=0; i<nmethod; i++)
    {
    // graph[ic][i]->RemovePoint(0);
    graph[ic][i]->SetTitle(title[i].Data());
    graph[ic][i]->SetMarkerStyle(markerStyle[i]);
    graph[ic][i]->SetMarkerSize(markerSize);
    graph[ic][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    graph[ic][i]->GetYaxis()->SetTitle("v_{2}{2,|#Delta#eta|>0.1}");
    graph[ic][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[ncent];
  for (int ic = 0; ic < 1; ic++)
  {
    vGr[ic].push_back(graph[ic][ratioToMethod]);
    // for (int i=0; i<nmethod; i++)
    // {
    //   if (i==ratioToMethod) continue;
    //   vGr[ic].push_back(graph[ic][i]);
    // }
    // vGr[ic].push_back(graph[ic][0]);
    vGr[ic].push_back(graph[ic][1]);
    // vGr[ic].push_back(graph[ic][2]);
    // vGr[ic].push_back(graph[ic][3]);
    // vGr[ic].push_back(graph[ic][4]);

  TCanvas *can = (TCanvas*)DrawTGraph(vGr[ic],"20-30%",0.68, 1.15, minpt, 3.6, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.65, 0.4, 0.88,
                                      "vHLLE+UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 11.5 GeV, h^{#pm}, |#eta|<%1.1f",eta_cut),1,"Reco/MC");
  can->SetName(Form("10-40%%"));
  can->SaveAs(Form("Performance_v2_2QC_2030_Nhits_16.pdf"));
  }


  // return vGr;
}