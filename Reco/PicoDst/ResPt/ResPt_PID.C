#include "DrawTGraph.C"
void ResPt_PID()
{
  const int npid = 8;
  const vector<TString> pidName = {"Hadron+","Pion+","Kaon+","Proton","Hadron-","Pion-","Kaon-","Antiproton"};
  TH1F *hPt[npid], *hPt_MC[npid];
  TFile *inFile = new TFile("../ROOTFile/ResPt_PID.root","read");
  TH1F *hPhil = (TH1F*)inFile->Get("hPhil");
  TH1F *hPhil_MC = (TH1F*)inFile->Get("hPhil_MC");
  TH1F *hEta = (TH1F*)inFile->Get("hEta");
  TH1F *hEta_MC = (TH1F*)inFile->Get("hEta_MC");
  TH1F *hBimp = (TH1F*)inFile->Get("hBimp");
  TH1I *hMult = (TH1I*)inFile->Get("hMult");
  TH1I *hMult_MC = (TH1I*)inFile->Get("hMult_MC");
  for (int id=0;id<npid;id++){
    hPt[id] = (TH1F*)inFile->Get(Form("hPt_%i",id));
    hPt_MC[id] = (TH1F*)inFile->Get(Form("hPt_MC_%i",id));
  }

  TProfile2D *prResPt2D = (TProfile2D*)inFile->Get("prResPt");

  const std::vector<double> pt_binning = {0.,0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.,1.2,1.5,1.8,2.,2.5,3.};
  const int n_pt_bins = pt_binning.size() - 1;

  const std::vector<std::pair<float, float>> centRange = {{0., 10.}, {10., 20.}, {20., 30.}, {30., 40.}, {40., 50.}, {10., 40.}, {40., 80.}, {0., 60.}, {10., 60}, {0.,80.}};
  const int n_cent_bins = centRange.size();
  TProfile *prResPt[n_cent_bins];
  std::pair<int, int> cent_bins;
  for (int icent = 0; icent < n_cent_bins; icent++)
  {
    cent_bins.first = prResPt2D->GetYaxis()->FindBin(centRange.at(icent).first);
    cent_bins.second = prResPt2D->GetYaxis()->FindBin(centRange.at(icent).second - 1);
    // if (icent==8) cout << "cent_bins.first=" << cent_bins.first << "\ncent_bins.second=" << cent_bins.second << endl;
    prResPt[icent] = (TProfile *)prResPt2D->ProfileX(Form("cent_%1.0f_%1.0f_%s", centRange.at(icent).first, centRange.at(icent).second, prResPt2D->GetName()), cent_bins.first, cent_bins.second);
    prResPt[icent] = (TProfile *)prResPt[icent]->Rebin(n_pt_bins, Form("rebinned_%s", prResPt[icent]->GetName()), &pt_binning[0]);
  }
  gSystem->Exec("mkdir -p ./ResPt/");
  TGraphErrors *grResPt[n_cent_bins];
  TCanvas *canv[n_cent_bins];
  for (int icent = 0; icent < n_cent_bins; icent++){
    canv[icent] = new TCanvas(Form("canv_%i",icent),Form("canv_%i",icent),200,10,800,600);
    canv[icent] -> SetLeftMargin(0.15);
    grResPt[icent] = (TGraphErrors *)ConvertProfile(prResPt[icent]);
    grResPt[icent]-> SetTitle(Form("Pt resolution, cent %1.0f-%1.0f%%;p_{T} [GeV/c];(p_{T}^{Reco}-p_{T}^{MC})/p_{T}^{Reco}",centRange.at(icent).first, centRange.at(icent).second));
    grResPt[icent] -> SetMarkerStyle(kFullCircle);
    // grResPt[icent] -> GetXaxis() -> SetLimits(0.,2.5);
    grResPt[icent] -> GetHistogram()->SetMaximum(0.36);
    grResPt[icent] -> GetHistogram()->SetMinimum(-0.06);
    grResPt[icent]->Draw("AP");
    TLine lineZero;
    lineZero.SetLineStyle(2);
    lineZero.DrawLine(pt_binning.at(0),0.,pt_binning.at(n_pt_bins),0.);
    canv[icent]->SaveAs(Form("./ResPt/ResPt_cent_%1.0f_%1.0f.png",centRange.at(icent).first, centRange.at(icent).second));
  }
  gStyle->SetOptStat(0);
  TCanvas *canvas[npid];
  TH1F *hPtEff[npid];
  for (int id=0;id<npid;id++){
    canvas[id] = new TCanvas(Form("canvas_%i",id),Form("canvas_%i",id),200,10,800,600);
    canvas[id] -> SetLeftMargin(0.15);
    hPtEff[id] = (TH1F*)hPt[id]->Clone(Form("hPtEff_%i",id));
    
    hPtEff[id] -> Divide(hPt[id],hPt_MC[id]);
    
    hPtEff[id] -> SetTitle(Form("%s;p_{T} [GeV/c]; Efficiency",pidName.at(id).Data()));
    hPtEff[id] -> SetMaximum(2.);
    hPtEff[id] -> SetMinimum(0.);
    hPtEff[id] -> GetXaxis()->SetRangeUser(0.,3.);
    hPtEff[id] -> SetLineWidth(2.);
    hPtEff[id] -> SetMarkerStyle(kFullCircle);
    hPtEff[id] -> SetMarkerSize(1.);
    hPtEff[id] -> Draw("P");
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(pt_binning.at(0),1.,pt_binning.at(n_pt_bins),1.);
    canvas[id] -> SaveAs(Form("./ResPt/Eff_%s.png",pidName.at(id).Data()));
  }
}