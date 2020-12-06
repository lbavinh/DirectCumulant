void Ecc2vsCent()
{
  
  const int ncent = 9;
  const double centE[ncent]={0};
  const double cent[ncent]={2.5,7.5,15,25,35,45,55,65,75};
  const int nenergy = 3;
  const TString energy[nenergy]={"4.5","7.7","11.5"};
  TGraphErrors *gr[nenergy];
  for (int e=0; e<nenergy; e++){
    TFile *fi = new TFile(Form("../ROOTFile/UrQMD_%sGeV.root",energy[e].Data()),"read");
    // TFile *fi = new TFile("../ROOTFile/UrQMD_7.7GeV_without_t_start_cut.root","read");
    TProfile *ecc2vsCent = (TProfile *) fi -> Get("prEcc2vsCent6");
    double ecc2[ncent], ecc2E[ncent];
    for (int i=0; i<ncent; i++){
      ecc2[i] = ecc2vsCent -> GetBinContent(i+1);
      ecc2E[i] = ecc2vsCent -> GetBinError(i+1);
    }
    gr[e] = new TGraphErrors(ncent,cent,ecc2,centE,ecc2E);
  }
  TCanvas c;
  gr[0]->SetMarkerStyle(24);
  gr[1]->SetMarkerStyle(22);
  gr[2]->SetMarkerStyle(25);
  for (int e=0; e<nenergy; e++){
    
    gr[e]->SetMarkerSize(1.3);
    gr[e]->SetTitle(";Centrality (%);<#epsilon_{2}>");
    gr[e]->GetXaxis()->SetRangeUser(0,80);
    gr[e]->SetMinimum(0.);
    gr[e]->SetMaximum(0.6);
    
  }
  gStyle->SetPalette(kDarkRainBow);
  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  gr[2]->Draw("P PLC PMC");
  TLatex tex;
  tex.SetTextFont(42);
  tex.DrawLatex(10,0.55,"UrQMD, Au+Au");
  TLegend *l = new TLegend(0.7,0.15,0.9,0.4);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  
  l->SetTextSize(0.05);
  l->SetHeader("     #sqrt{s_{NN}}");
  // l->SetTextAlign(22);
  for (int e=0; e<nenergy; e++){
    l->AddEntry(gr[e],Form("%s GeV",energy[e].Data()),"p");
  }
  l->Draw();
  // tex.DrawLatex(10,0.50,"#tau < 3.2 fm/c");
  c.SaveAs("ecc2vsCent.png");
  // c.SaveAs("ecc2_wo_t_start_cut.png");
}