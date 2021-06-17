void Compare_scaled_with_N_events()
{
  TFile *fi[3];
  fi[0] = new TFile("vHLLE_1PT_11.5_reco.root","READ");
  fi[1] = new TFile("vHLLE_XPT_11.5_reco.root","READ");
  fi[2] = new TFile("UrQMD_11.5_reco.root","READ");
  const Int_t ncent = 9 ;
  TString centrality[ncent+1] = {"0","5","10","20","30","40","50","60","70","80"};
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    // TH1F *hMult[3];
    TH1I *hMult[3];
    for (int i=0;i<3;i++)
    {
      // hMult[i] = dynamic_cast<TH1F*>(fi[i]->Get(Form("hPt_%i",ic)));
      hMult[i] = dynamic_cast<TH1I*>(fi[i]->Get(Form("hMult_%i",ic)));
      // if (!hMult[i] || !hMult[i]) return;
      // hMult[i]->Scale(1./hMult[i]->GetEntries());
    }
    hMult[0]->SetLineColor(kRed+1);
    hMult[0]->SetMarkerColor(kRed+1);
    hMult[1]->SetLineColor(kBlue+1);
    hMult[1]->SetMarkerColor(kBlue+1);
    hMult[2]->SetLineColor(kBlack);
    hMult[2]->SetMarkerColor(kBlack);    
    hMult[0]->SetMarkerStyle(20);
    hMult[1]->SetMarkerStyle(24);
    hMult[2]->SetMarkerStyle(20);
    hMult[0]->SetMarkerSize(1.);
    hMult[1]->SetMarkerSize(1.);
    hMult[2]->SetMarkerSize(1.);
    TCanvas c;
    // gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    hMult[0]->SetTitle(Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm}, |#eta|<1.5, 0.2<p_{T}<3.0 GeV/c",centrality[ic].Data(),centrality[ic+1].Data()));
    hMult[0]->GetXaxis()->SetRangeUser(0,1000);
    hMult[0]->Draw("hist");
    hMult[1]->Draw("hist SAME");
    hMult[2]->Draw("hist SAME");
    TLegend *leg = new TLegend(0.7,0.7,0.85,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(hMult[0],"vHLLE+UrQMD 1PT","l");
    leg->AddEntry(hMult[1],"vHLLE+UrQMD XPT","l");
    leg->AddEntry(hMult[2],"UrQMD","l");
    leg->Draw();
    c.SaveAs(Form("Compare_dN_dM_%s_%s.png",centrality[ic].Data(),centrality[ic+1].Data()));

  }


}