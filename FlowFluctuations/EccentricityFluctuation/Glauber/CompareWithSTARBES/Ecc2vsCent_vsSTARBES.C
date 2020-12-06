void Ecc2vsCent_vsSTARBES()
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
  vector<Double_t> epart7 = {0.102, 0.14, 0.21, 0.3, 0.37, 0.43, 0.5, 0.58, 0.68};
  vector<Double_t> eparterr7 = {0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.04};
  vector<Double_t> epart11 = {0.102, 0.14, 0.22, 0.3, 0.37, 0.43, 0.5, 0.58, 0.68};
  vector<Double_t> eparterr11 = {0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.05};
  TGraphErrors *grSTAR[2];
  grSTAR[0] = new TGraphErrors(ncent,cent,&epart7[0],centE,&eparterr7[0]);
  grSTAR[0]->SetMarkerStyle(29);
  grSTAR[0]->SetMarkerSize(2.);
  grSTAR[1] = new TGraphErrors(ncent,cent,&epart11[0],centE,&eparterr11[0]);
  grSTAR[1]->SetMarkerStyle(29);
  grSTAR[1]->SetMarkerSize(2.);
  TCanvas c;
  for (int m=0; m<nenergy; m++)
  {
    gr[m][0]->SetMarkerStyle(20);
    gr[m][1]->SetMarkerStyle(21);

  }
  for (int e=0; e<nenergy; e++)
  {
    for (int m=0; m<nmodel; m++)
    {
    gr[e][m]->SetMarkerSize(1.3);
    gr[e][m]->SetTitle(";Centrality (%);<#epsilon_{2}>");
    gr[e][m]->GetXaxis()->SetRangeUser(0,80);
    gr[e][m]->SetMinimum(0.);
    gr[e][m]->SetMaximum(0.8);
    }
  }
  gStyle->SetPalette(kDarkRainBow);
  // gr[1][1]->Draw("AP PLC PMC");
  gr[1][1]->Draw("AP PLC PMC");
  for (int e=2; e<nenergy; e++)
  {
    for (int m=1; m<nmodel; m++)
    {
      // if (e==0 && m==0) continue;
      // gr[e][m] -> Draw("P PLC PMC");
    }
  }
  // grSTAR[0] -> Draw("P PLC PMC"); // 7.7
  grSTAR[0] -> Draw("P PLC PMC"); // 11.5

  TLatex tex;
  tex.SetTextFont(42);
  // tex.DrawLatex(10,0.55,"UrQMD, Au+Au");
  TLegend *l = new TLegend(0.15,0.6,0.4,0.85);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->SetHeader("Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  // l->SetTextAlign(22);
  for (int m=1; m<nmodel; m++)
  {
    for (int e=1; e<2; e++){

      l->AddEntry(gr[e][m],Form("%s",model[m].Data()),"p");
    }
  }
  // l->AddEntry(grSTAR[0],"STAR BES","p");
  l->AddEntry(grSTAR[0],"STAR BES","p");
  l->Draw();
  // tex.DrawLatex(10,0.50,"#tau < 3.2 fm/c");
  // c.SaveAs("ecc2vsCent_vsSTARBES77.png");
  c.SaveAs("ecc2vsCent_vsSTARBES77.png");
  // c.SaveAs("ecc2_wo_t_start_cut.png");
}