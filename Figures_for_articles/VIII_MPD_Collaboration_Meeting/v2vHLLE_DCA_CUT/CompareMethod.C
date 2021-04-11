// #include "PlotV2QCumulantCentrality1040.C"
#include "constants.C"
#include "DrawTGraph.C"
void CompareMethod()
{
  TString inputModel = "v2_FirstRun_vHLLEUrQMD_11.5_Model.root.root";
  TString inputModel2 = "SecondRun_vHLLEUrQMD_11.5_Model.root";
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
  Int_t nmethod = 3;
  TFile *fi = new TFile(inputModel.Data(),"READ");
  TFile *fi2 = new TFile(inputModel2.Data(),"READ");
  TString title[]={"2QC","SP","EP"};// MC GEANT4 Reco
  const int markerStyle[] = {24,20,20,21,20,25,28,26,23};
  const float markerSize = 1.3;
  const int npid = 3;
  int pidcode[npid] = {8,9,3};
  TString pidName[npid] = {"hadron","pion","proton"};
  TString pidNameFancy[npid] = {"h^{#pm}","#pi^{#pm}","p"};
  TGraphErrors *graph[3][nmethod];
  for (int i = 0; i < npid; i++)
  {
    graph[i][0] = (TGraphErrors*) fi->Get(Form("gr_cent10-40_2_%i",pidcode[i]));
    auto pr = (TProfile2D*) fi2->Get(Form("SP/prV2SPvsPt_pid%i",pidcode[i]));
    TProfile *tmp = PlotV2vsPt(pr,10,40);
    graph[i][1] = Converter(tmp);
    auto pr2 = (TProfile2D*) fi2->Get(Form("ETASUBEP/prV2EtaSubvsPt_pid%i",pidcode[i]));
    TProfile *tmp2 = PlotV2vsPt(pr2,10,40);
    graph[i][2] = Converter(tmp2);

  }
  

  for (int ic = 0; ic < npid; ic++)
  {
    for (int i=0; i<nmethod; i++)
    {
    // graph[ic][i]->RemovePoint(0);
    graph[ic][i]->SetTitle(title[i].Data());
    graph[ic][i]->SetMarkerStyle(markerStyle[i]);
    graph[ic][i]->SetMarkerSize(markerSize);
    graph[ic][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    graph[ic][i]->GetYaxis()->SetTitle("v_{2}{2}"); // 2,|#Delta#eta|>0.1
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
    vGr[ic].push_back(graph[ic][2]);
    // vGr[ic].push_back(graph[ic][3]);
    // vGr[ic].push_back(graph[ic][4]);

  TCanvas *can = (TCanvas*)DrawTGraph(vGr[ic],"10-40%",0.89, 1.11, minpt, 3.0, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.65, 0.4, 0.88,
                                      "vHLLE+UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 11.5 GeV, %s, |#eta|<%1.1f", pidNameFancy[ic].Data(),eta_cut),1,"Ratio to Model"); // #pi^{#pm}
  can->SetName(Form("10-40%%"));
  can->SaveAs(Form("Compare_v2_2QC_SP_1040_Model_%s.pdf",pidName[ic].Data()));
  }


  // return vGr;
}