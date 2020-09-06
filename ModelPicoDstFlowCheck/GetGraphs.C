#include "DrawTGraph.C"
#include "Utils.C"

const double beam_energy = 7.7; // sqrt(sNN) in GeV

const std::vector<std::pair<float, float>> centRange = {{0., 10.}, {10., 20.}, {20., 30.}, {30., 40.}, {40., 50.}, {10., 40.}, {40., 80.}, {0., 60.}, {10., 60}};
const int n_cent_bins = centRange.size();

const std::vector<double> pt_binning = {0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.5, 1.8, 2.5, 3.};
// const std::vector<double> pt_binning = {0.2, 0.6, 1., 1.5, 2.5, 3.}; // for kaons specifically
const int n_pt_bins = pt_binning.size() - 1;

const std::pair<double, double> ratio_y_region = {0.79, 1.21};
// const std::pair<double,double> ratio_y_region = {0.64, 1.36}; // for kaons specifically

void GetGraphs(TString iFileModel, TString iFileReco, TString oFile)
{
  gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  gStyle->SetPalette(kDarkRainBow);

  TFile *fiModel = new TFile(iFileModel.Data(), "read");
  TFile *fiReco = new TFile(iFileReco.Data(), "read");

  TProfile2D *tmp;
  std::pair<int, int> cent_bins;
  TProfile *pv2_mc[n_cent_bins][Npid];
  TProfile *pv2_reco[n_cent_bins][Npid];
  TProfile *pv2_model[n_cent_bins][Npid];

  // Get Model results
  for (int i = 0; i < Npid; i++)
  {
    tmp = (TProfile2D *)fiModel->Get(Form("pv2TPC_pid%i", i));
    for (int icent = 0; icent < n_cent_bins; icent++)
    {
      cent_bins.first = tmp->GetYaxis()->FindBin(centRange.at(icent).first);
      cent_bins.second = tmp->GetYaxis()->FindBin(centRange.at(icent).second - 1);
      pv2_model[icent][i] = (TProfile *)tmp->ProfileX(Form("cent_%1.0f_%1.0f_%s", centRange.at(icent).first, centRange.at(icent).second, tmp->GetName()), cent_bins.first, cent_bins.second);
      pv2_model[icent][i] = (TProfile *)pv2_model[icent][i]->Rebin(n_pt_bins, Form("rebinned_%s", pv2_model[icent][i]->GetName()), &pt_binning[0]);
    }
    delete tmp;
  }

  // Get MC results
  for (int i = 0; i < Npid; i++)
  {
    tmp = (TProfile2D *)fiReco->Get(Form("pv2mcTPC_pid%i", i));
    for (int icent = 0; icent < n_cent_bins; icent++)
    {
      cent_bins.first = tmp->GetYaxis()->FindBin(centRange.at(icent).first);
      cent_bins.second = tmp->GetYaxis()->FindBin(centRange.at(icent).second - 1);
      pv2_mc[icent][i] = (TProfile *)tmp->ProfileX(Form("cent_%1.0f_%1.0f_%s", centRange.at(icent).first, centRange.at(icent).second, tmp->GetName()), cent_bins.first, cent_bins.second);
      pv2_mc[icent][i] = (TProfile *)pv2_mc[icent][i]->Rebin(n_pt_bins, Form("rebinned_%s", pv2_mc[icent][i]->GetName()), &pt_binning[0]);
    }
    delete tmp;
  }

  // Get RECO results
  for (int i = 0; i < Npid; i++)
  {
    tmp = (TProfile2D *)fiReco->Get(Form("pv2recoTPC_pid%i", i));
    for (int icent = 0; icent < n_cent_bins; icent++)
    {
      cent_bins.first = tmp->GetYaxis()->FindBin(centRange.at(icent).first);
      cent_bins.second = tmp->GetYaxis()->FindBin(centRange.at(icent).second - 1);
      pv2_reco[icent][i] = (TProfile *)tmp->ProfileX(Form("cent_%1.0f_%1.0f_%s", centRange.at(icent).first, centRange.at(icent).second, tmp->GetName()), cent_bins.first, cent_bins.second);
      pv2_reco[icent][i] = (TProfile *)pv2_reco[icent][i]->Rebin(n_pt_bins, Form("rebinned_%s", pv2_reco[icent][i]->GetName()), &pt_binning[0]);
      // if (icent == 0 && i == 0)
      // {
      //   std::cout << "Cent bins: " << tmp->GetYaxis()->FindBin(centRange.at(0).first) << " " << tmp->GetYaxis()->FindBin(centRange.at(0).second - 1) << std::endl;
      //   std::cout << "CHECK 1 ::::: " << pv2_reco[icent][i]->GetBinContent(4) << std::endl;
      // }
    }
    delete tmp;
  }

  // tmp = (TProfile2D *)fiReco->Get(Form("pv2recoTPC_pid%i", 0));
  // auto prof = (TProfile *)tmp->ProfileX("prof_test", 1, 1);
  // prof = (TProfile *)prof->Rebin(n_pt_bins, "rebinned_prof_test", &pt_binning[0]);
  // std::cout << "CHECK 1 ::::: " << prof->GetBinContent(4) << std::endl;

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

      pv2_mc[icent][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
      pv2_mc[icent][i]->GetYaxis()->SetTitle("v_{2}");
      pv2_mc[icent][i]->SetLineColor(kBlue + 1);
      pv2_mc[icent][i]->SetMarkerColor(kBlue + 1);
      pv2_mc[icent][i]->SetMarkerStyle(kOpenCircle);
      pv2_mc[icent][i]->SetMarkerSize(1.6);

      pv2_reco[icent][i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
      pv2_reco[icent][i]->GetYaxis()->SetTitle("v_{2}");
      pv2_reco[icent][i]->SetLineColor(kRed + 2);
      pv2_reco[icent][i]->SetMarkerColor(kRed + 2);
      pv2_reco[icent][i]->SetMarkerStyle(kFullTriangleUp);
      pv2_reco[icent][i]->SetMarkerSize(1.6);
    }
  }

  TGraphErrors *grv2_mc[n_cent_bins][Npid];
  TGraphErrors *grv2_reco[n_cent_bins][Npid];
  TGraphErrors *grv2_model[n_cent_bins][Npid];
  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    for (int i = 0; i < Npid; i++)
    {
      grv2_model[icent][i] = (TGraphErrors *)ConvertProfile(pv2_model[icent][i]);
      grv2_model[icent][i]->SetName(Form("gr_%s", pv2_model[icent][i]->GetName()));

      grv2_mc[icent][i] = (TGraphErrors *)ConvertProfile(pv2_mc[icent][i]);
      grv2_mc[icent][i]->SetName(Form("gr_%s", pv2_mc[icent][i]->GetName()));

      grv2_reco[icent][i] = (TGraphErrors *)ConvertProfile(pv2_reco[icent][i]);
      grv2_reco[icent][i]->SetName(Form("gr_%s", pv2_reco[icent][i]->GetName()));
    }
  }

  TFile *fo = new TFile(oFile.Data(), "recreate");
  fo->cd();
  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    for (int i = 0; i < Npid; i++)
    {
      grv2_model[icent][i]->Write();
      grv2_mc[icent][i]->Write();
      grv2_reco[icent][i]->Write();
    }
  }
  fo->Close();

  gSystem->Exec("mkdir -p ./pics/");

  TCanvas *canv;
  std::vector<TGraphErrors *> vgr;
  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    for (int i = 0; i < Npid; i++)
    {
      vgr.clear();

      grv2_model[icent][i]->SetTitle("model");
      grv2_mc[icent][i]->SetTitle("geant");
      grv2_reco[icent][i]->SetTitle("reco");

      vgr.push_back(grv2_model[icent][i]);
      vgr.push_back(grv2_mc[icent][i]);
      vgr.push_back(grv2_reco[icent][i]);

      canv = (TCanvas *)DrawTGraph(vgr, Form("UrQMD, AuAu, %1.1f GeV, %1.0f-%1.0f%, %s", beam_energy, centRange.at(icent).first, centRange.at(icent).second, pidFancyNames.at(i).Data()),
                                   ratio_y_region.first, ratio_y_region.second, 0., 2.5, -0.004, 0.19, 0.22, 0.55, 0.85, 0.89);
      canv->SaveAs(Form("./pics/v2_comparison_cent_%1.0f_%1.0f_%s.png", centRange.at(icent).first, centRange.at(icent).second, pidNames.at(i).Data()));
    }
  }
}