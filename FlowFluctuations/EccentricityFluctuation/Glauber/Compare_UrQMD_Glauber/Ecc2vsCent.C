void Ecc2vsCent()
{
  
  const int ncent = 9;
  const double centE[ncent]={0};
  const double cent[ncent]={2.5,7.5,15,25,35,45,55,65,75};
  const int nenergy = 3;
  const int nmodel = 2;
  const TString energy[nenergy]={"4.5","7.7","11.5"};
  const TString model[nmodel]={"UrQMD","Glauber"};
  TGraphErrors *gr[nenergy][nmodel];
  for (int e=0; e<nenergy; e++){
    TFile *fi = new TFile(Form("UrQMD_%sGeV.root",energy[e].Data()),"read");
    TFile *fi_Glauber = new TFile(Form("Glauber_%sGeV.root",energy[e].Data()),"read");
    TProfile *ecc2vsCent = (TProfile *) fi -> Get("prEcc2vsCent6");
    double ecc2[ncent], ecc2E[ncent];
    for (int i=0; i<ncent; i++){
      ecc2[i] = ecc2vsCent -> GetBinContent(i+1);
      ecc2E[i] = ecc2vsCent -> GetBinError(i+1);
    }
    gr[e][0] = new TGraphErrors(ncent,cent,ecc2,centE,ecc2E);
    ecc2vsCent = (TProfile *) fi_Glauber -> Get("prEcc2vsCent");
    // double ecc2[ncent], ecc2E[ncent];
    for (int i=0; i<ncent; i++){
      ecc2[i] = ecc2vsCent -> GetBinContent(i+1);
      ecc2E[i] = ecc2vsCent -> GetBinError(i+1);
    }
    gr[e][1] = new TGraphErrors(ncent,cent,ecc2,centE,ecc2E);

  }
  TCanvas c;
  for (int m=0; m<nmodel; m++)
  {
    gr[0][m]->SetMarkerStyle(20+4*m);
    gr[1][m]->SetMarkerStyle(21+4*m);
    gr[2][m]->SetMarkerStyle(22+4*m);
  }
  for (int e=0; e<nenergy; e++)
  {
    for (int m=0; m<nmodel; m++)
    {
    gr[e][m]->SetMarkerSize(1.3);
    gr[e][m]->SetTitle(";Centrality (%);<#epsilon_{2}>");
    gr[e][m]->GetXaxis()->SetRangeUser(0,80);
    gr[e][m]->SetMinimum(0.);
    gr[e][m]->SetMaximum(0.7);
    }
  }
  gStyle->SetPalette(kDarkRainBow);
  gr[0][0]->Draw("AP PLC PMC");
  for (int e=0; e<nenergy; e++)
  {
    for (int m=0; m<nmodel; m++)
    {
      if (e==0 && m==0) continue;
      gr[e][m] -> Draw("P PLC PMC");
    }
  }

  TLatex tex;
  tex.SetTextFont(42);
  // tex.DrawLatex(10,0.55,"UrQMD, Au+Au");
  TLegend *l = new TLegend(0.15,0.6,0.4,0.85);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->SetHeader("            #sqrt{s_{NN}}");
  // l->SetTextAlign(22);
  for (int m=0; m<nmodel; m++)
  {
    for (int e=0; e<nenergy; e++){

      l->AddEntry(gr[e][m],Form("%s GeV (%s)",energy[e].Data(),model[m].Data()),"p");
    }
  }
  l->Draw();
  // tex.DrawLatex(10,0.50,"#tau < 3.2 fm/c");
  c.SaveAs("ecc2vsCent.png");
  // c.SaveAs("ecc2_wo_t_start_cut.png");
}