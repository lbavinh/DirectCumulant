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
    TH1F *h_fhcal_En[3];
    TH1I *hMult[3];
    for (int i=0;i<3;i++)
    {
      h_fhcal_En[i] = dynamic_cast<TH1F*>(fi[i]->Get(Form("h_fhcal_En_%i",ic)));
      // hMult[i] = dynamic_cast<TH1I*>(fi[i]->Get(Form("hMult_%i",ic)));
      // if (!h_fhcal_En[i] || !hMult[i]) return;
      h_fhcal_En[i]->Scale(1./h_fhcal_En[i]->GetEntries());
    }
    h_fhcal_En[0]->SetLineColor(kRed+1);
    h_fhcal_En[0]->SetMarkerColor(kRed+1);
    h_fhcal_En[1]->SetLineColor(kBlue+1);
    h_fhcal_En[1]->SetMarkerColor(kBlue+1);
    h_fhcal_En[2]->SetLineColor(kBlack);
    h_fhcal_En[2]->SetMarkerColor(kBlack);    
    h_fhcal_En[0]->SetMarkerStyle(20);
    h_fhcal_En[1]->SetMarkerStyle(24);
    h_fhcal_En[2]->SetMarkerStyle(20);
    h_fhcal_En[0]->SetMarkerSize(1.);
    h_fhcal_En[1]->SetMarkerSize(1.);
    h_fhcal_En[2]->SetMarkerSize(1.);
    TCanvas c;
    // gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    h_fhcal_En[2]->SetTitle(Form("Au+Au #sqrt{s_{NN}} = 11.5 GeV, %s-%s%%",centrality[ic].Data(),centrality[ic+1].Data()));
    // h_fhcal_En[2]->GetXaxis()->Set
    h_fhcal_En[2]->GetXaxis()->SetRangeUser(0,20);
    h_fhcal_En[2]->SetMaximum(0.1);
    h_fhcal_En[2]->SetMinimum(0.);
    h_fhcal_En[2]->Draw("hist");
    h_fhcal_En[1]->Draw("hist SAME");
    h_fhcal_En[0]->Draw("hist SAME");
    TLegend *leg = new TLegend(0.7,0.7,0.85,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(h_fhcal_En[0],"vHLLE+UrQMD 1PT","l");
    leg->AddEntry(h_fhcal_En[1],"vHLLE+UrQMD XPT","l");
    leg->AddEntry(h_fhcal_En[2],"UrQMD","l");
    leg->Draw();
    c.SaveAs(Form("Compare_dN_dE_%s_%s.png",centrality[ic].Data(),centrality[ic+1].Data()));

  }


}