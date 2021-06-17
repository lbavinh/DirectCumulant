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
    TH1F *hPt[3];
    TH1I *hMult[3];
    for (int i=0;i<3;i++)
    {
      hPt[i] = dynamic_cast<TH1F*>(fi[i]->Get(Form("hPt_%i",ic)));
      hMult[i] = dynamic_cast<TH1I*>(fi[i]->Get(Form("hMult_%i",ic)));
      // if (!hPt[i] || !hMult[i]) return;
      hPt[i]->Scale(1./hMult[i]->GetEntries());
    }
    hPt[0]->SetLineColor(kRed+1);
    hPt[0]->SetMarkerColor(kRed+1);
    hPt[1]->SetLineColor(kBlue+1);
    hPt[1]->SetMarkerColor(kBlue+1);
    hPt[2]->SetLineColor(kBlack);
    hPt[2]->SetMarkerColor(kBlack);    
    hPt[0]->SetMarkerStyle(20);
    hPt[1]->SetMarkerStyle(24);
    hPt[2]->SetMarkerStyle(20);
    hPt[0]->SetMarkerSize(1.);
    hPt[1]->SetMarkerSize(1.);
    hPt[2]->SetMarkerSize(1.);
    TCanvas c;
    // gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    hPt[2]->SetTitle(Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm}, |#eta|<1.5",centrality[ic].Data(),centrality[ic+1].Data()));
    hPt[2]->Draw("hist");
    hPt[1]->Draw("hist SAME");
    hPt[0]->Draw("hist SAME");
    TLegend *leg = new TLegend(0.7,0.7,0.85,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(hPt[0],"vHLLE+UrQMD 1PT","l");
    leg->AddEntry(hPt[1],"vHLLE+UrQMD XPT","l");
    leg->AddEntry(hPt[2],"UrQMD","l");
    leg->Draw();
    c.SaveAs(Form("Compare_dN_dPt_%s_%s.png",centrality[ic].Data(),centrality[ic+1].Data()));

  }


}