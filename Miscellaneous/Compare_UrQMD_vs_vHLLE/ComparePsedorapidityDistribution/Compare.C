void Compare()
{
  TFile *fi[2];
  TH1D *hEta[2];
  fi[0] = new TFile("UrQMD_11.5.root","READ");
  fi[1] = new TFile("vHLLEUrQMD_11.5.root","READ");
  for (int i=0;i<2;i++)
  {
    hEta[i] = dynamic_cast<TH1D*>(fi[i]->Get("hEta"));
    if (!hEta[i]) return;
    cout << hEta[i]->Integral() << endl;
    hEta[i]->Scale(1./hEta[i]->Integral());
    cout << hEta[i]->Integral() << endl;
  }
  hEta[0]->SetLineColor(kRed+1);
  hEta[1]->SetLineColor(kBlue+1);
  hEta[0]->SetMarkerColor(kRed+1);
  hEta[1]->SetMarkerColor(kBlue+1);
  hEta[0]->SetMarkerStyle(20);
  hEta[1]->SetMarkerStyle(24);
  hEta[0]->SetMarkerSize(1.);
  hEta[1]->SetMarkerSize(1.);
  TCanvas c;
  gPad->SetLogy(1);
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  hEta[1]->SetTitle("Au+Au #sqrt{s_{NN}} = 11.5 GeV, charged hadrons");
  hEta[1]->Draw("P");
  hEta[0]->Draw("P SAME");
  TLegend *leg = new TLegend(0.3,0.2,0.6,0.4);
  leg->SetBorderSize(0);
  leg->AddEntry(hEta[0],"UrQMD","p");
  leg->AddEntry(hEta[1],"vHLLE+UrQMD","p");
  leg->Draw();
  c.SaveAs("Compare_dN_dEta.png");


}