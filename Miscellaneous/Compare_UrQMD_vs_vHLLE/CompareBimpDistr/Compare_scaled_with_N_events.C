void Compare_scaled_with_N_events()
{
  TFile *fi[2];
  TH1F *hBimp[2];
  TH1I *hEvt[2];
  fi[0] = new TFile("UrQMD_11.5.root","READ");
  fi[1] = new TFile("vHLLEUrQMD_11.5.root","READ");
  for (int i=0;i<2;i++)
  {
    hBimp[i] = dynamic_cast<TH1F*>(fi[i]->Get("hBimp"));
    hEvt[i] = dynamic_cast<TH1I*>(fi[i]->Get("hEvt"));
    if (!hBimp[i]) return;
    hBimp[i]->Scale(1./hEvt[i]->GetBinContent(1));
  }
  hBimp[0]->SetLineColor(kRed+1);
  hBimp[1]->SetLineColor(kBlue+1);
  hBimp[0]->SetMarkerColor(kRed+1);
  hBimp[1]->SetMarkerColor(kBlue+1);
  hBimp[0]->SetMarkerStyle(20);
  hBimp[1]->SetMarkerStyle(24);
  hBimp[0]->SetMarkerSize(1.);
  hBimp[1]->SetMarkerSize(1.);
  TCanvas c;
  // gPad->SetLogy(1);
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  hBimp[1]->SetTitle("Au+Au #sqrt{s_{NN}} = 11.5 GeV, charged hadrons");
  hBimp[1]->Draw("P");
  hBimp[0]->Draw("P SAME");
  TLegend *leg = new TLegend(0.3,0.15,0.6,0.3);
  leg->SetBorderSize(0);
  leg->AddEntry(hBimp[0],"UrQMD","p");
  leg->AddEntry(hBimp[1],"vHLLE+UrQMD","p");
  leg->Draw();
  c.SaveAs("Compare_dN_db_scaled_by_N_evt.png");


}