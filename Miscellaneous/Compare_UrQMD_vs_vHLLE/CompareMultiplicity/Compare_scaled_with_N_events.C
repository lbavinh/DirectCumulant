void Compare_scaled_with_N_events()
{
  TFile *fi[2];
  fi[0] = new TFile("UrQMD_11.5.root","READ");
  fi[1] = new TFile("vHLLE_11.5.root","READ");
  const Int_t ncent = 9 ;
  TString centrality[ncent+1] = {"0","5","10","20","30","40","50","60","70","80"};
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    TH1I *hMult[2];
    for (int i=0;i<2;i++)
    {
      hMult[i] = dynamic_cast<TH1I*>(fi[i]->Get(Form("hMult_%i",ic)));
      // hMult[i]->Scale(1./hMult[i]->GetEntries());
    }
    hMult[0]->SetLineColor(kRed+1);
    hMult[1]->SetLineColor(kBlue+1);
    hMult[0]->SetMarkerColor(kRed+1);
    hMult[1]->SetMarkerColor(kBlue+1);
    hMult[0]->SetMarkerStyle(20);
    hMult[1]->SetMarkerStyle(24);
    hMult[0]->SetMarkerSize(1.);
    hMult[1]->SetMarkerSize(1.);
    TCanvas c;
    gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    hMult[0]->SetTitle(Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, charged hadrons",centrality[ic].Data(),centrality[ic+1].Data()));
    hMult[0]->GetXaxis()->SetRangeUser(0,1700);
    hMult[0]->Draw("");
    hMult[1]->Draw("SAME");
    TLegend *leg = new TLegend(0.15,0.7,0.35,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(hMult[0],"UrQMD","p");
    leg->AddEntry(hMult[1],"vHLLE+UrQMD","p");
    leg->Draw();
    c.SaveAs(Form("Compare_dN_dM_%s_%s.png",centrality[ic].Data(),centrality[ic+1].Data()));

  }


}