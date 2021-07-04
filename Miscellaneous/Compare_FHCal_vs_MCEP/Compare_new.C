#include "DrawTGraph.C"
// #include "constants.C"
// vector<TGraphErrors*>*
void Compare_new()
{
  Int_t centlow = 10;
  Int_t centhigh = 40;
  Double_t maxpt = 3.;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  const int ratioToMethod = 0;
  const Int_t nmethod = 2;
  const Int_t npid = 3;
  int pidCode[npid]={8,9,3};
  TString pidName[npid]={"hadrons","pions","protons"};
  TString pidNameFancy[npid]={"h^{#pm}","#pi^{#pm}","p"};
  TString title[]={"v_{2}{#Psi_{1,FHCal}}","v_{2}{MC-EP}"};
  const int markerStyle[] = {20,24,23,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[npid][nmethod];
  TFile *fi = new TFile("FHCal_vs_MCEP.root","READ");

  for (int j=0; j<npid; j++)
  {
    auto pr = (TProfile2D*) fi->Get(Form("FHCALEP/prV2FHCalEPvsPt_pid%i",pidCode[j]));
    TProfile *tmp = PlotV2vsPt(pr,10,40);
    graph[j][0] = Converter(tmp);

    auto pr1 = (TProfile2D*) fi->Get(Form("MCEP/prV2MCvsPt_pid%i",pidCode[j]));
    TProfile *tmp1 = PlotV2vsPt(pr1,10,40);
    graph[j][1] = Converter(tmp1);

  }
  

  for (int id = 0; id < npid; id++)
  {
    for (int i=0; i<nmethod; i++)
    {
    // graph[id][i]->RemovePoint(0);
    graph[id][i]->SetTitle(title[i].Data());
    graph[id][i]->SetMarkerStyle(markerStyle[i]);
    graph[id][i]->SetMarkerSize(markerSize);
    graph[id][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    graph[id][i]->GetYaxis()->SetTitle("v_{2}");
    graph[id][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[npid];
  for (int id = 0; id < npid; id++)
  {
    vGr[id].push_back(graph[id][1]);
    vGr[id].push_back(graph[id][0]);
    // vGr[id].push_back(graph[id][2]);
    TCanvas *can = (TCanvas*)DrawTGraph(vGr[id],Form("%i-%i%%",centlow,centhigh),0.89, 1.11, minpt, maxpt, -0.005, 0.13,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.5, 0.45, 0.88,
                                      "UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 7.7 GeV, %s, |#eta|<%1.1f",pidNameFancy[id].Data(), eta_cut),1,"Ratio to v_{2}{MC-EP}");
    can->SetName(Form("10-40%%"));
    can->SaveAs(Form("Compare_FHCALEP_with_MCEP_%i%i_Model_%s.pdf",centlow,centhigh,pidName[id].Data()));
  }


  // return vGr;
}