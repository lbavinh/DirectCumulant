void Compare()
{
  TFile *fi[2]; TProfile *pr[2];
  fi[0] = new TFile("FirstRun_UrQMD.root","READ");
  fi[1] = new TFile("FirstRun_vHLLE.root","READ");
  for (int i=0; i<2; i++)
  {
    pr[i] = (TProfile*) fi[i]->Get("prRefMult");
    pr[i]->SetTitle(";Centrality, %;<M>");
  }
  pr[0]->SetLineColor(kRed);
  pr[1]->SetLineColor(kBlue);
  pr[0]->SetMarkerColor(kRed);
  pr[1]->SetMarkerColor(kBlue);
  pr[0]->SetMarkerStyle(20);
  pr[1]->SetMarkerStyle(22);
  TCanvas c;
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  pr[0]->SetTitle("Au+Au #sqrt{s_{NN}} = 11.5 GeV, h^{#pm}, |#eta|<1.5, 0.2<p_{T}<3.0 GeV/c");
  pr[0]->Draw("P");
  pr[1]->Draw("P same");
  TLegend *leg = new TLegend(0.6,0.6,0.8,0.8);
  leg->SetBorderSize(0);
  leg->AddEntry(pr[0],"UrQMD","p");
  leg->AddEntry(pr[1],"vHLLE+UrQMD","p");
  leg->Draw();
  
  c.SaveAs("CompareM.png");


}