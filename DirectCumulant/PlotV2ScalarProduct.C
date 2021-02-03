bool bDebug = false;
TProfile *PlotV2Integrated(TProfile3D* &prV2,
                           const double pt_low = 0.2,
                           const double pt_high = 3.0,
                           const double eta_cut = 1.5)
{
  prV2->GetZaxis()->SetRange(-eta_cut, eta_cut);
  // prV2->GetZaxis()->SetRange(-(eta_cut-0.001), eta_cut-0.001);
  TProfile2D *prV2_2D = (TProfile2D *)prV2->Project3DProfile("yx");
  prV2_2D->SetName(Form("%s_eta_cut_%1.1f",prV2->GetName(),eta_cut));
  int pt_bin_low = prV2_2D->GetYaxis()->FindBin(pt_low);
  int pt_bin_high = prV2_2D->GetYaxis()->FindBin(pt_high);
  TProfile *prV2int = (TProfile *)prV2_2D->ProfileX(Form("%s_pt_%1.1f_%1.1f",prV2_2D->GetName(),pt_low, pt_high), pt_bin_low, pt_bin_high);
  // prV2int->SetTitle(";centrality, %;v_{2}");
  prV2int->SetTitle(Form("|#eta|<%.1f, %.1f<p_{T}<%.1f GeV/c;centrality, %%;v_{2}", eta_cut, pt_low, pt_high));
  return prV2int;
}

TProfile *PlotV2DifferentialVersusPt(TProfile3D *const &prV2,
                           const double cent_low = 10,
                           const double cent_high = 40,
                           const double eta_cut = 1.5)
{
  prV2->GetZaxis()->SetRange(-eta_cut, eta_cut);
  TProfile2D *prV2_2D = (TProfile2D *)prV2->Project3DProfile("yx");
  prV2_2D->SetName(Form("%s_eta_cut_%1.1f",prV2->GetName(),eta_cut));
  int cent_bin_low = prV2_2D->GetXaxis()->FindBin(cent_low);
  int cent_bin_high = prV2_2D->GetXaxis()->FindBin(cent_high-1);
  TProfile *prV2diffpt = (TProfile *)prV2_2D->ProfileY(Form("%s_cent_%1.0f_%1.0f",prV2_2D->GetName(),cent_low, cent_high), cent_bin_low, cent_bin_high);
  // prV2diffpt->SetTitle(";p_{T}, GeV/c;v_{2}");
  prV2diffpt->SetTitle(Form("|#eta|<%.1f, %.0f-%.0f%%;p_{T}, GeV/c;v_{2}", eta_cut, cent_low, cent_high));
  return prV2diffpt;
}

TProfile *PlotV2DifferentialVersusEta(TProfile3D*const &prV2,
                           const double pt_low = 0.2,
                           const double pt_high = 3.0,
                           const double cent_low = 10,
                           const double cent_high = 40)
{
  prV2->GetYaxis()->SetRange(pt_low, pt_high);
  TProfile2D *prV2_2D = (TProfile2D *)prV2->Project3DProfile("zx");
  prV2_2D->SetName(Form("%s_pt_%1.1f_%1.1f",prV2->GetName(),pt_low,pt_high));
  int cent_bin_low = prV2_2D->GetXaxis()->FindBin(cent_low);
  int cent_bin_high = prV2_2D->GetXaxis()->FindBin(cent_high-1);
  if (bDebug) 
  {
    cout << "cent_bin_low = " << cent_bin_low << ", cent_low = " << cent_low << endl;
    cout << "cent_bin_high = " << cent_bin_high << ", cent_high = " << cent_high << endl;
  }
  TProfile *prV2diffEta = (TProfile *)prV2_2D->ProfileY(Form("%s_cent_%1.0f_%1.0f",prV2_2D->GetName(),cent_low, cent_high), cent_bin_low, cent_bin_high);
  // prV2diffEta->SetTitle(";#eta;v_{2}");
  prV2diffEta->SetTitle(Form("%.1f<p_{T}<%.1f GeV/c, %.0f-%.0f%%;#eta;v_{2}", pt_low, pt_high, cent_low, cent_high));
  return prV2diffEta;
}

void PlotV2ScalarProduct(TString inputFileName = "SecondRun.root")
{
  TFile *fi = TFile::Open(inputFileName.Data());
  TProfile3D *pr = (TProfile3D *)fi->Get("prV2ScalarProduct");
  TProfile3D *prClone = (TProfile3D *)pr->Clone(Form("Clone_%s",pr->GetName()));
  TCanvas c;
  c.Divide(2,2);

  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  
  c.cd(1);
  // v2 versus pt, 10-40%, |eta|<1.5
  TProfile *prV2diffpt = PlotV2DifferentialVersusPt(pr,10,40,1.5);
  prV2diffpt->SetMarkerStyle(27);
  prV2diffpt->SetMarkerColor(kBlue + 3);
  prV2diffpt->GetYaxis()->SetRangeUser(0., 0.2);
  prV2diffpt->GetXaxis()->SetRangeUser(0., 3.5);
  prV2diffpt->Draw();

  c.cd(2);
  // v2 versus pt, 40-80%, |eta|<1.5
  TProfile *prV2diffpt4080 = PlotV2DifferentialVersusPt(pr,40,80,1.5);
  prV2diffpt4080->SetMarkerStyle(27);
  prV2diffpt4080->SetMarkerColor(kBlue + 3);
  prV2diffpt4080->GetYaxis()->SetRangeUser(0., 0.2);
  prV2diffpt4080->GetXaxis()->SetRangeUser(0., 3.5);
  prV2diffpt4080->Draw();

  c.cd(3);
  // v2 versus centrality, 0.2<pt<3.5 GeV/c, |eta|<1.5
  TProfile *prV2int = PlotV2Integrated(pr,0.2,3.5,1.5);
  prV2int->SetMarkerStyle(27);
  prV2int->SetMarkerColor(kBlue + 3);
  prV2int->GetYaxis()->SetRangeUser(0., 0.1);
  prV2int->Draw();
  
  c.cd(4);
  // v2 versus eta, 0.2<pt<3.5 GeV/c, 10-40%
  TProfile *prV2diffEta = PlotV2DifferentialVersusEta(prClone, 0.2, 3.5, 10, 40);
  // TProfile *prV2diffEta = PlotV2DifferentialVersusEta(pr, 0.2, 3.5, 10, 40);
  prV2diffEta->SetMarkerStyle(27);
  prV2diffEta->SetMarkerColor(kBlue + 3);
  prV2diffEta->GetYaxis()->SetRangeUser(0., 0.1);
  prV2diffEta->Draw();

  c.SaveAs("FlowSP.pdf");
}