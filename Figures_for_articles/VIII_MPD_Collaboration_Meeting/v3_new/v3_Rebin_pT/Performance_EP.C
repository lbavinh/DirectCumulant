#include "DrawTGraph.C"
// #include "constants.C"
// vector<TGraphErrors*>*
void Performance_EP()
{
  TString inputName[2] = {"./SecondRun_vHLLEUrQMD_11.5_Model_v3.root",
                          "./SecondRun_vHLLEUrQMD_11.5_Reco_Nhits_16_DCA_3sigma_v3.root",};


  Int_t centlow = 10;
  Int_t centhigh = 40;
  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements

  const Int_t npt_Rebin = 7; // 0-3.6 GeV/c - number of pT bins
  const Double_t pTBin_Rebin[npt_Rebin + 1] = {0.2, 0.4, 0.6, 1.0, 1.4, 1.8, 2.2, 3.0};

  const int ratioToMethod = 0;
  const Int_t nmethod = 2;
  const Int_t npid = 3;
  int pidCode[npid]={8,9,3};
  TString pidName[npid]={"hadrons","pions","protons"};
  TString pidNameFancy[npid]={"h^{#pm}","#pi^{#pm}","p"};
  TString title[]={"Model","Reco"};
  const int markerStyle[] = {24,20,23,22,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *graph[npid][nmethod];
  TFile *fi[2];
  for (int i = 0; i < nmethod; i++){
    fi[i] = new TFile(inputName[i].Data(),"READ");
    for (int j=0; j<npid; j++)
    {
      auto pr = (TProfile2D*) fi[i]->Get(Form("ETASUBEP/prV2EtaSubvsPt_pid%i",pidCode[j]));
      TProfile *tmp = PlotV2vsPt(pr,10,40);
      tmp = (TProfile*) tmp->Rebin(npt_Rebin,Form("%s_Rebin",tmp->GetName()),&pTBin_Rebin[0]);
      cout << tmp->GetBinContent(1) << endl;
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
    graph[id][i]->GetYaxis()->SetTitle("v_{3}{eta-sub, EP}");
    graph[id][i]->SetDrawOption("P PLC PMC");
    }
  }

  vector<TGraphErrors*> vGr[npid];
  for (int id = 0; id < npid; id++)
  {
    vGr[id].push_back(graph[id][ratioToMethod]);
    vGr[id].push_back(graph[id][1]);
    // vGr[id].push_back(graph[id][2]);
    // vGr[id].push_back(graph[id][3]);
    TCanvas *can = (TCanvas*)DrawTGraph(vGr[id],Form("%i-%i%%",centlow,centhigh),0.68, 1.32, minpt, 3.0, -0.005, 0.1,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.5, 0.45, 0.88,
                                      "vHLLE+UrQMD, Au+Au", Form("#sqrt{s_{NN}} = 11.5 GeV, %s, |#eta|<%1.1f",pidNameFancy[id].Data(), eta_cut),1,"Ratio to Model");
    can->SetName(Form("10-40%%"));
    can->SaveAs(Form("Performance_v2_EP_%i%i_Model_vs_Nhits_16_DCA_3sigma_%s.pdf",centlow,centhigh,pidName[id].Data()));
  }


  // return vGr;
}