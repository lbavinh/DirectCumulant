#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
// #include "PlotV2QCumulant.C"
#include "DrawTGraph.C"
#include "constants.C"
// vector<TGraphErrors*>*
void Performance_EP(TString inputMC = "SecondRun_vHLLEUrQMD_11.5_MC.root", TString inputRECO = "SecondRun_vHLLEUrQMD_11.5_Reco.root")
{
  Int_t centlow = 40;
  Int_t centhigh = 80;
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
  TString title[]={"MC","Reco"};
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[1][nmethod];
  TFile *firun1 = new TFile(inputMC.Data(),"read");
  TFile *firun2 = new TFile(inputRECO.Data(),"read");
  auto *prV2TPCEP3D_MC = (TProfile3D*) firun1->Get("prV2EtaSubEventPlane");
  auto *prV2TPCEP3D_RECO = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");
  for (int i = 0; i < 1; i++)
  {
    TProfile *prV2TPCEP_MC = PlotV2EtaSubDifferentialVersusPt(prV2TPCEP3D_MC,centlow,centhigh,eta_cut);
    TProfile *prV2TPCEP_RECO = PlotV2EtaSubDifferentialVersusPt(prV2TPCEP3D_RECO,centlow,centhigh,eta_cut);
    graph[i][0] = Converter(prV2TPCEP_MC);
    graph[i][1] = Converter(prV2TPCEP_RECO);
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
    graph[ic][i]->GetYaxis()->SetTitle("v_{3}{#Psi_{3,TPC}}");
    graph[ic][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[ncent];
  for (int ic = 0; ic < 1; ic++)
  {
    vGr[ic].push_back(graph[ic][ratioToMethod]);
    vGr[ic].push_back(graph[ic][1]);
    TCanvas *can = (TCanvas*)DrawTGraph(vGr[ic],Form("%i-%i%%",centlow,centhigh),0.68, 1.32, minpt, 2.8, -0.005, 0.1,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.65, 0.4, 0.88,
                                      "vHLLE+UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 11.5 GeV, h^{#pm}, |#eta|<%1.1f",eta_cut),1,"Reco/MC");
  can->SetName(Form("10-40%%"));
  can->SaveAs(Form("Performance_v3_TPCEP_%i%i.pdf",centlow,centhigh));
  }


  // return vGr;
}