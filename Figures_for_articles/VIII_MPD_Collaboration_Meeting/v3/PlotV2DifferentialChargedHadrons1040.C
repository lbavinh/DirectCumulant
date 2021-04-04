#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
// #include "PlotV2QCumulant.C"
#include "DrawTGraph.C"
#include "constants.C"
// vector<TGraphErrors*>*
void PlotV2DifferentialChargedHadrons1040(TString inputFirstRunFileName = "FirstRun_vHLLEUrQMD_11.5_MC.root", TString inputSecondRunFileName = "SecondRun_vHLLEUrQMD_11.5_MC.root")
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
  TString title[]={"v_{3}{#Psi_{3,TPC}}","v_{3}^{SP}{Q_{3,TPC}}"};
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[1][nmethod];
  TFile *firun1 = new TFile(inputFirstRunFileName.Data(),"read");
  TFile *firun2 = new TFile(inputSecondRunFileName.Data(),"read");
  auto *prV2TPCEP3D = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");
  auto *prV2SP3D = (TProfile3D*) firun2->Get("prV2ScalarProduct");
  auto *prV2FHCalEP3D = (TProfile3D*) firun2->Get("prV2FHCalEventPlane");
  auto *prV2ThreeSubEP3D = (TProfile3D*) firun2->Get("prV2ThreeEtaSub");
  for (int i = 0; i < 1; i++)
  {
    TProfile *prV2TPCEP = PlotV2EtaSubDifferentialVersusPt(prV2TPCEP3D,10.,40.,eta_cut);
    TProfile *prV2SP = PlotV2ScalarProductDifferentialVersusPt(prV2SP3D,10.,40.,eta_cut);
    graph[i][0] = Converter(prV2TPCEP);
    graph[i][1] = Converter(prV2SP);
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
    graph[ic][i]->GetYaxis()->SetTitle("v_{3}");
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

  TCanvas *can = (TCanvas*)DrawTGraph(vGr[ic],"10-40%",0.68, 1.32, minpt, 2.8, -0.005, 0.1,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.65, 0.4, 0.88,
                                      "vHLLE+UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 11.5 GeV, h^{#pm}, |#eta|<%1.1f",eta_cut),1,Form("Ratio to %s",title[ratioToMethod].Data()));
  can->SetName(Form("10-40%%"));
  can->SaveAs(Form("DiffFlow_vHLLEUrQMD_11_GeV_MC.pdf"));
  }


  // return vGr;
}