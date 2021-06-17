// #include "PlotV2QCumulantCentrality1040.C"
#include "constants.C"
#include "DrawTGraph.C"
void Performance_QC_Centrality_10_40()
{
  const Int_t nmethod = 2;
  TString input[nmethod] = {"v3_QCumulant_Model_v3.root.root",
                            "v3_QCumulant_Nhits_16_3_sigma_v3.root.root"};
  // const Int_t npt = 16; // 0-3.6 GeV/c - number of pT bins
  // const Double_t pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
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
  TFile *fi[nmethod];
  for (Int_t i=0;i<nmethod;i++)
  {
    fi[i] = new TFile(input[i].Data(),"READ");

  }
  TString title[]={"Model","Reco"};// MC GEANT4 Reco
  // TString title[]={"Model","Reco, 2#sigma_{DCA}, N_{hits}>16","Reco, 2#sigma_{DCA}, N_{hits}>32"};// MC GEANT4 Reco
  const int markerStyle[] = {24,20,23,22,20,25,28,26,23};
  const float markerSize = 1.3;
  const int npid = 3;
  int pidcode[npid] = {8,9,3};
  TString pidName[npid] = {"hadron","pion","proton"};
  TString pidNameFancy[npid] = {"h^{#pm}","#pi^{#pm}","p"};
  TGraphErrors *graph[nmethod][nmethod];
  for (int i = 0; i < npid; i++)
  {
    for (int j=0;j<nmethod;j++)
    {
      graph[i][j] = (TGraphErrors*) fi[j]->Get(Form("gr_cent10-40_2_%i",pidcode[i]));
    }
  }
  

  for (int ic = 0; ic < npid; ic++)
  {
    for (int i=0; i<nmethod; i++)
    {
    graph[ic][i]->RemovePoint(0);
    graph[ic][i]->SetTitle(title[i].Data());
    graph[ic][i]->SetMarkerStyle(markerStyle[i]);
    graph[ic][i]->SetMarkerSize(markerSize);
    graph[ic][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    graph[ic][i]->GetYaxis()->SetTitle("v_{3}{2}"); // 2,|#Delta#eta|>0.1
    graph[ic][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[ncent];
  for (int ic = 0; ic < npid; ic++)
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

  TCanvas *can = (TCanvas*)DrawTGraph(vGr[ic],"10-40%",0.68, 1.32, minpt, 3.0, -0.005, 0.1,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.65, 0.4, 0.88,
                                      "vHLLE+UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 11.5 GeV, %s, |#eta|<%1.1f", pidNameFancy[ic].Data(),eta_cut),1,"Ratio to Model"); // #pi^{#pm}
  can->SetName(Form("10-40%%"));
  can->SaveAs(Form("Performance_v3_2QC_1040_Model_vs_Reco_Nhits_16_%s_DCA_sigma_3.pdf",pidName[ic].Data()));
  }


  // return vGr;
}