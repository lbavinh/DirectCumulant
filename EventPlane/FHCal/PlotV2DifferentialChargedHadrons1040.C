#include "DrawTGraph.C"
#include "constants.C"
void PlotV2DifferentialChargedHadrons1040(TString inputFileName = "SecondRun.root")
{
  Bool_t saveAsPNG = true;
  TString outDirName = "pics";
  Double_t maxpt = 3.0;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const Int_t ratioToMethod = 0;
  const Double_t J1rootJ0 = 0.519147;
  Double_t X[npt];
  for (Int_t ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const Double_t errX[npt] = {0.};
  const Int_t nmethod = 2;
  TString methodName[nmethod] = {"FHCalEP", "MC"};
  TString title[nmethod]={"v_{2}{#Psi_{1,FHCal}}","v_{2}{MC-EP}"};
  const Int_t markerStyle[] = {25,20,22,24};
  const Float_t markerSize = 1.3;
  TGraphErrors *graph[nmethod];
  TFile *fi = new TFile(inputFileName.Data(),"read");
  for (Int_t i=0; i<nmethod; i++)
  {
    auto prV2CentPt = (TProfile2D *)fi->FindObjectAny(Form("prV2%svsPt_pid%i",methodName[i].Data(),8));
    TProfile *tmp = PlotV2vsPt(prV2CentPt,10,40);// v2 versus pt, 10-40%
    graph[i] = Converter(tmp);
    // graph[i]->RemovePoint(0);
    graph[i]->SetTitle(title[i].Data());
    graph[i]->SetMarkerStyle(markerStyle[i]);
    graph[i]->SetMarkerSize(markerSize);
    graph[i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    graph[i]->GetYaxis()->SetTitle("v_{2}");
    graph[i]->SetDrawOption("P PLC PMC");
  }

  vector<TGraphErrors*> vGr;
  vGr.push_back(graph[ratioToMethod]);
  for (Int_t i=0; i<nmethod; i++)
  {
    if (i==ratioToMethod) continue;
    vGr.push_back(graph[i]);
  }
  TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.89, 1.11, minpt, maxpt, -0.005, 0.2,
                                      0.2, 0.45, 0.4, 0.88,
                                      "UrQMD, Au+Au at #sqrt{s_{NN}}=7.7GeV", Form("h^{#pm}, |#eta|<%1.1f",eta_cut),
                                      true,Form("Ratio to %s",title[ratioToMethod].Data()));
  can->SetName(Form("10-40%%"));
  if (saveAsPNG){
    gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
    can->SaveAs(Form("./%s/DiffFlow_Centrality_10_40_hadrons.png",outDirName.Data()));
  }  
}