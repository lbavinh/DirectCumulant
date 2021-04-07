#include "DrawTGraph.C"
void Comparev2PT(){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22

  TGraphErrors *gr[2];
  // TFile *inputPeter = new TFile("graphs_reco_vs_geant.root","read");
  TFile *inputPeter = new TFile("graphs_fhcal_11.5gev_hadrons.root","read");
  gr[0] = (TGraphErrors*)inputPeter->Get("gr_v2_FHCalEp_mc");
  TFile *inputVinh = new TFile("SecondRun_UrQMD_11.5.root","read");
  TProfile3D *pr3D = (TProfile3D*) inputVinh->Get("prV2FHCalEventPlane");
  const int npt = 11; // 0.5 - 3.6 GeV/c - number of pT bins
  const double bin_pT[npt+1]={0.,0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.,3.6};
  TProfile *pr = PlotV2vsPt(pr3D,10,40,1.5);
  pr->Rebin(npt,Form("%s_rebin",pr->GetName()),&bin_pT[0]);
  gr[1] = Converter(pr);
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
  TCanvas *c = DrawTGraph(vGr,"","UrQMD, Au+Au #sqrt{s_{NN}}= 11.5 GeV","h^{#pm}","Ratio to Peter");
  c->SaveAs("Compare_UrQMD_11.pdf");
}