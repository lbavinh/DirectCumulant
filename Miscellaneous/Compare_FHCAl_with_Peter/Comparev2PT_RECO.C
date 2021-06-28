#include "DrawTGraph.C"
void Comparev2PT_RECO(){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22

  TGraphErrors *gr[2];
  TFile *inputPeter = new TFile("graphs_reco_vs_geant.root","read");
  // TFile *inputPeter = new TFile("graphs_fhcal_11.5gev_hadrons.root","read");
  gr[0] = (TGraphErrors*)inputPeter->Get("gr_v2_FHCalEp_reco");
  TFile *inputVinh = new TFile("SecondRun_UrQMD_7.7_Reco_2sigma_16_TPChits.root","read");
  auto prV2CentPt = (TProfile2D *)inputVinh->FindObjectAny(Form("prV2FHCalEPvsPt_pid8"));
  TProfile *tmp = PlotV2vsPt(prV2CentPt,10,40);// v2 versus pt, 10-40%
  gr[1] = Converter(tmp);
  gr[0]->SetMarkerStyle(24);
  gr[0]->SetTitle("Peter's");
  gr[1]->SetMarkerStyle(20);
  gr[1]->SetTitle("Vinh's");
  for (int i=0; i<2; i++)
  {
    gr[i]->SetMarkerSize(1.);
  }
  vector<TGraphErrors*> vGr;
  vGr.push_back(gr[0]);
  vGr.push_back(gr[1]);
  TCanvas *c = DrawTGraph(vGr,"","GEANT4, UrQMD, Au+Au #sqrt{s_{NN}}= 7.7 GeV","h^{#pm}","Ratio to Peter");
  c->SaveAs("Compare_UrQMD_7_RECO.pdf");
}