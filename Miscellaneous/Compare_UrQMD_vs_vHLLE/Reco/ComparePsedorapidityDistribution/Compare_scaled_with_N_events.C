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
    TH1D *hEta[3];
    TH1I *hMult[3];
    for (int i=0;i<3;i++)
    {
      hEta[i] = dynamic_cast<TH1D*>(fi[i]->Get(Form("hEta_%i",ic)));
      hMult[i] = dynamic_cast<TH1I*>(fi[i]->Get(Form("hMult_%i",ic)));
      // if (!hEta[i] || !hMult[i]) return;
      hEta[i]->Scale(1./hMult[i]->GetEntries());
    }
    hEta[0]->SetLineColor(kRed+1);
    hEta[0]->SetMarkerColor(kRed+1);
    hEta[1]->SetLineColor(kBlue+1);
    hEta[1]->SetMarkerColor(kBlue+1);
    hEta[2]->SetLineColor(kBlack);
    hEta[2]->SetMarkerColor(kBlack);    
    hEta[0]->SetMarkerStyle(20);
    hEta[1]->SetMarkerStyle(24);
    hEta[2]->SetMarkerStyle(20);
    hEta[0]->SetMarkerSize(1.);
    hEta[1]->SetMarkerSize(1.);
    hEta[2]->SetMarkerSize(1.);
    hEta[0]->SetLineWidth(2.);
    hEta[1]->SetLineWidth(2.);
    hEta[2]->SetLineWidth(2.);

    TCanvas c;
    gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    hEta[2]->SetTitle(Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%, h^{#pm}",centrality[ic].Data(),centrality[ic+1].Data())); // 0.2<p_{T}<3.0 GeV/c
    hEta[2]->Draw("hist");
    hEta[1]->Draw("hist SAME");
    hEta[0]->Draw("hist SAME");
    TLegend *leg = new TLegend(0.3,0.3,0.7,0.5);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);
    leg->AddEntry(hEta[0],"vHLLE+UrQMD 1PT","l");
    leg->AddEntry(hEta[1],"vHLLE+UrQMD XPT","l");
    leg->AddEntry(hEta[2],"UrQMD","l");
    leg->Draw();
    c.SaveAs(Form("Compare_dN_dEta_%s_%s.png",centrality[ic].Data(),centrality[ic+1].Data()));

  }


}