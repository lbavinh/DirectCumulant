#include "DrawTGraph.C"
void PeterPerformance()
{
  TFile *inputPeter = new TFile("graphs_reco_vs_geant.root","read");
  TGraphErrors *gr[2];
  gr[0] = (TGraphErrors*)inputPeter->Get("gr_v2_FHCalEp_mc");
  gr[1] = (TGraphErrors*)inputPeter->Get("gr_v2_FHCalEp_reco");
  vector<TGraphErrors*> vGr;
  gr[1]->SetMarkerStyle(20);
  gr[0]->SetMarkerStyle(24);
  for (int i=0; i<2; i++)
  {
    gr[i]->SetMarkerSize(1.2);
  }
  vGr.push_back(gr[0]);
  vGr.push_back(gr[1]);
  TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.89, 1.11, 0, 3.1, -0.005, 0.15,
                                    0.2, 0.65, 0.4, 0.88,
                                    "UrQMD, Au+Au","#sqrt{s_{NN}} = 7.7 GeV, h^{#pm}, |#eta|<1.5",1,"Reco/MC");
  can->SetName(Form("10-40%%"));
  can->SaveAs(Form("Performance_v2_FHCALEP_Peter.pdf"));
  

}