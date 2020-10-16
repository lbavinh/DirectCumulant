#include "DrawTGraph.C"
#include "Utils.C"
Bool_t bMergePIDExeptForProtons = kTRUE;
const double beam_energy = 7.7; // sqrt(sNN) in GeV

const std::vector<std::pair<float, float>> centRange = {{0., 10.}, {10., 20.}, {20., 30.}, {30., 40.}, {40., 50.}, {10., 40.}, {40., 80.}, {0., 60.}, {10., 60}};
const int n_cent_bins = centRange.size();

const std::vector<double> pt_binning = {0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.5, 1.8, 2.5, 3.};
// const std::vector<double> pt_binning = {0.2, 0.6, 1., 1.5, 2.5, 3.}; // for kaons specifically
const int n_pt_bins = pt_binning.size() - 1;

const std::pair<double, double> ratio_y_region = {0.79, 1.21};
// const std::pair<double,double> ratio_y_region = {0.64, 1.36}; // for kaons specifically

void GetGraphs(TString iFileModel="UrQMD_7.7GeV.root", TString oFile="v2_UrQMD_7.7GeV_V2SP.root")
{
  gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  gStyle->SetPalette(kDarkRainBow);

  TFile *fiModel = new TFile(iFileModel.Data(), "read");
  // TFile *fiReco = new TFile(iFileReco.Data(), "read");

  // // Resolution calculation
  // TProfile *pRes2_model= (TProfile*) fiModel->Get("pResTPC");
  // std::vector<float> vRes_model;
  // float res2, res;
  // for (int ibin = 0; ibin < pRes2_model->GetNbinsX(); ibin++)
  // {
  //   res2 = pRes2_model->GetBinContent(ibin+1);
  //   if (res2 < 0) res = 0;
  //   else          res = sqrt(res2);
  //   vRes_model.push_back(res);
  // }

  // std::cout << "const std::vector<float> vResTpc     = {";
  // for (int i=0; i<vRes_model.size(); i++)
  // {
  //   std::cout << vRes_model.at(i);
  //   if (i < vRes_model.size()-1) std::cout << ", ";
  // }
  // std::cout << "};" << std::endl;



  TProfile2D *tmp;
  TProfile2D *mergePr[Npid];
  std::pair<int, int> cent_bins;
  // TProfile *pv2_mc[n_cent_bins][Npid];
  // TProfile *pv2_reco[n_cent_bins][Npid];
  TProfile *pv2_model[n_cent_bins][Npid];
  if (bMergePIDExeptForProtons) {
    for (int id=0;id<Npid;id++){
      mergePr[id] = (TProfile2D *)fiModel->Get(Form("pv2TPC_pid%i", id));
    }
    for (int id=0;id<Npid/2;id++){
      if (id!=3) mergePr[id] -> Add(mergePr[id+4]);
      // delete mergePr[id+4];
    }
  }
  // Get Model results
  for (int i = 0; i < Npid; i++)
  {
    tmp = (TProfile2D *)fiModel->Get(Form("pv2TPC_pid%i", i));
    if (bMergePIDExeptForProtons && i<Npid/2){
      tmp = mergePr[i];
    }
    for (int icent = 0; icent < n_cent_bins; icent++)
    {
      cent_bins.first = tmp->GetYaxis()->FindBin(centRange.at(icent).first);
      cent_bins.second = tmp->GetYaxis()->FindBin(centRange.at(icent).second - 1);
      pv2_model[icent][i] = (TProfile *)tmp->ProfileX(Form("cent_%1.0f_%1.0f_%s", centRange.at(icent).first, centRange.at(icent).second, tmp->GetName()), cent_bins.first, cent_bins.second);
      pv2_model[icent][i] = (TProfile *)pv2_model[icent][i]->Rebin(n_pt_bins, Form("rebinned_%s", pv2_model[icent][i]->GetName()), &pt_binning[0]);
    }
    delete tmp;
  }

  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    for (int i = 0; i < Npid; i++)
    {
      pv2_model[icent][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
      pv2_model[icent][i]->GetYaxis()->SetTitle("v_{2}");
      pv2_model[icent][i]->SetLineColor(kBlack);
      pv2_model[icent][i]->SetMarkerColor(kBlack);
      pv2_model[icent][i]->SetMarkerStyle(kFullSquare);
      pv2_model[icent][i]->SetMarkerSize(1.6);

    }
  }

  TGraphErrors *grv2_model[n_cent_bins][Npid];
  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    for (int i = 0; i < Npid; i++)
    {
      grv2_model[icent][i] = (TGraphErrors *)ConvertProfile(pv2_model[icent][i]);
      grv2_model[icent][i]->SetName(Form("gr_%s", pv2_model[icent][i]->GetName()));

      // grv2_mc[icent][i] = (TGraphErrors *)ConvertProfile(pv2_mc[icent][i]);
      // grv2_mc[icent][i]->SetName(Form("gr_%s", pv2_mc[icent][i]->GetName()));

      // grv2_reco[icent][i] = (TGraphErrors *)ConvertProfile(pv2_reco[icent][i]);
      // grv2_reco[icent][i]->SetName(Form("gr_%s", pv2_reco[icent][i]->GetName()));
    }
  }

  TFile *fo = new TFile(oFile.Data(), "recreate");
  fo->cd();
  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    for (int i = 0; i < Npid; i++)
    {
      grv2_model[icent][i]->Write();
    }
  }
  fo->Close();

  gSystem->Exec("mkdir -p ./pics/");

  TCanvas *canv;
  TH2F *h;
  for (int icent = 5; icent < 6; icent++) // n_cent_bins
  {
    for (int i = 0; i < Npid/2; i++) // Npid
    {
      canv = new TCanvas("c","can",200,10,800,600);  
      grv2_model[icent][i]->SetTitle("model");
      h = new TH2F("h",";p_{T}, GeV/C;v_{2}",10,0.,3.,10,-0.01,0.2);
      h -> Draw();
      grv2_model[icent][i]-> Draw("P");
      TLatex tex;
      tex.DrawLatex(0.1,0.15,Form("Au+Au at #sqrt{s_{NN}}=7.7 GeV, %1.0f-%1.0f%%, %s",centRange.at(icent).first, centRange.at(icent).second,pidFancyNames.at(i).Data()));
      canv->SaveAs(Form("./pics/v2_cent_%1.0f_%1.0f_%s.png", centRange.at(icent).first, centRange.at(icent).second, pidNames.at(i).Data()));
    }
  }
}
