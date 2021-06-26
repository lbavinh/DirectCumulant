#include "DrawTGraph.C"
#include "constants.C"
void CompareV2FHCal()
{

  Bool_t saveAsPNG = true;
  TString inputFileName[5];
  inputFileName[0] = "../data/SecondRun_UrQMD_7.7_Model.root";
  inputFileName[1] = "../data/SecondRun_UrQMD_7.7_Model_GEANT4.root";
  inputFileName[2] = "../data/SecondRun_UrQMD_7.7_Reco_motherID.root";
  inputFileName[3] = "../data/SecondRun_UrQMD_7.7_Reco_3sigma_32hits.root";
  inputFileName[4] = "../data/SecondRun_UrQMD_7.7_Reco_2sigma_16_TPChits.root";

  TString outDirName = "CompareV2FHCal";
  Double_t maxpt = 3.;    // max pt for differential flow
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
  bool bUseProduct = 1;
  const Int_t npid = 12;
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_bar", "hadron", "pion", "kaon","proton_antiproton"};
  const std::vector<TString> pidFancyNames = {"h^{+}", "#pi^{+}", "K^{+}", "p", "h^{-}", "#pi^{-}", "K^{-}", "#bar{p}", "h^{#pm}","#pi^{#pm}","K^{#pm}","p(#bar{p})"};
  const Int_t nmethod = 5;
  TString methodName[] = {"FHCalEP", "MC", "FHCalEP","FHCalEP","FHCalEP"}; // FHCalEP
  TString title[]={"v_{2}{#Psi_{1,FHCal}} (model)","v_{2}{MC-EP}","v_{2}{#Psi_{1,FHCal}} (motherID)","v_{2}{#Psi_{1,FHCal}} (3#sigma)","v_{2}{#Psi_{1,FHCal}} (2#sigma)"};
  const Int_t markerStyle[] = {20,23,22,22,24};
  const Float_t markerSize = 1.3;
  TGraphErrors *graph[nmethod][npid];
  TFile *fi[5];
  for (int i=0;i<5;i++)
  {
    fi[i] = new TFile(inputFileName[i].Data(),"read");
  }
  for (Int_t id=0;id<npid;id++)
  {
    for (Int_t i=0; i<nmethod; i++)
    {
      auto prV2CentPt = (TProfile2D *)fi[i]->FindObjectAny(Form("prV2%svsPt_pid%i",methodName[i].Data(),id));
      TProfile *tmp = PlotV2vsPt(prV2CentPt,10,40);// v2 versus pt, 10-40%
      graph[i][id] = Converter(tmp);
      // graph[i][id]->RemovePoint(0);
      graph[i][id]->SetTitle(title[i].Data());
      graph[i][id]->SetMarkerStyle(markerStyle[i]);
      graph[i][id]->SetMarkerSize(markerSize);
      graph[i][id]->GetXaxis()->SetTitle("p_{T}, GeV/c");
      graph[i][id]->GetYaxis()->SetTitle("v_{2}");
      graph[i][id]->SetDrawOption("P PLC PMC");
      delete prV2CentPt;
    }
    
    vector<TGraphErrors*> vGr;
    vGr.push_back(graph[ratioToMethod][id]);
    // for (Int_t i=0; i<nmethod; i++)
    // {
    //   if (i==ratioToMethod) continue;
    //   vGr.push_back(graph[i][id]);
    // }
    // vGr.push_back(graph[1][id]); // MC
    vGr.push_back(graph[2][id]); // motherID
    // vGr.push_back(graph[3][id]); // 3sigma
    vGr.push_back(graph[4][id]); // 2sigma

    TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.89, 1.11, minpt, 2.0, -0.005, 0.13,
                                        0.2, 0.4, 0.4, 0.88,
                                        "UrQMD, Au+Au at #sqrt{s_{NN}}=7.7GeV", Form("%s, |#eta|<%1.1f", pidFancyNames.at(id).Data(),eta_cut),
                                        true,Form("Ratio to %s",title[ratioToMethod].Data()));
    can->SetName(Form("10-40%%"));
    if (saveAsPNG){
      gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
      can->SaveAs(Form("./%s/DiffFlow_Centrality_10_40_%s.png",outDirName.Data(),pidNames.at(id).Data()));
    }
    

  }

}