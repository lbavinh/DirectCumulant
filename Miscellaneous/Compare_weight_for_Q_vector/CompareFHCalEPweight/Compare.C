#include "DrawTGraph.C"
// #include "constants.C"
// vector<TGraphErrors*>*
void Compare()
{
  TString inputName[3] = {"./SecondRun_UrQMD_7.7_FHCal_Model_unit_weight.root",
                          "./SecondRun_UrQMD_7.7_FHCal_Model_pt_weight.root",
                          "./SecondRun_UrQMD_7.7_FHCal_Model_energy_weight.root"};


  Int_t centlow = 10;
  Int_t centhigh = 40;
  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  const int ratioToMethod = 0;
  const Int_t nmethod = 3;
  const Int_t npid = 3;
  int pidCode[npid]={8,9,3};
  TString pidName[npid]={"hadrons","pions","protons"};
  TString pidNameFancy[npid]={"h^{#pm}","#pi^{#pm}","p"};
  TString title[]={"Unit weight","p_{T} weight","E weight"};
  const int markerStyle[] = {24,20,23,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[npid][nmethod];
  TFile *fi[3];
  for (int i=0;i<nmethod;i++)
  {
    fi[i] = new TFile(inputName[i].Data(),"READ");
    for (int j=0; j<npid; j++)
    {
      auto pr = (TProfile2D*) fi[i]->Get(Form("FHCALEP/prV2FHCalEPvsPt_pid%i",pidCode[j]));
      TProfile *tmp = PlotV2vsPt(pr,10,40);
      graph[j][i] = Converter(tmp);
    }
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
    graph[id][i]->GetYaxis()->SetTitle("v_{2}{#Psi_{1,FHCal}}");
    graph[id][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[npid];
  for (int id = 0; id < npid; id++)
  {
    vGr[id].push_back(graph[id][ratioToMethod]);
    vGr[id].push_back(graph[id][1]);
    vGr[id].push_back(graph[id][2]);
    TCanvas *can = (TCanvas*)DrawTGraph(vGr[id],Form("%i-%i%%",centlow,centhigh),0.89, 1.11, minpt, 2.8, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.5, 0.45, 0.88,
                                      "UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 7.7 GeV, %s, |#eta|<%1.1f",pidNameFancy[id].Data(), eta_cut),1,"Ratio to Unit weight");
    can->SetName(Form("10-40%%"));
    can->SaveAs(Form("Compare_FHCALEP_%i%i_Model_%s.pdf",centlow,centhigh,pidName[id].Data()));
  }


  // return vGr;
}