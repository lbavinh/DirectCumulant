void Ecc2vsB()
{
  
  vector<double> bimp_binning={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,20};
  int nBbins = bimp_binning.size()-1;
  const int nenergy = 4;
  const int nmodel = 2;
  const TString energy[nenergy]={"4.5","7.7","11.5","200"};
  const TString model[nmodel]={"UrQMD","Glauber"};
  TGraphErrors *gr[nenergy][nmodel];
  for (int e=0; e<nenergy; e++){
    TFile *fi = new TFile(Form("UrQMD_%sGeV.root",energy[e].Data()),"read");
    TFile *fi_Glauber = new TFile(Form("Glauber_%sGeV.root",energy[e].Data()),"read");
    TProfile *ecc2vsBimp = (TProfile *) fi -> Get("ValvsB/pEcc2vsB6");
    ecc2vsBimp = (TProfile*)ecc2vsBimp->Rebin(nBbins,"ecc2vsBimp_rebin",&bimp_binning[0]);
    vector<Double_t> ecc2, ecc2E, b, bE;
    // int nBbins = ecc2vsBimp->GetNbinsX();
    for (int i=0; i<nBbins; i++){
      b.push_back(ecc2vsBimp -> GetBinCenter(i+1));
      bE.push_back(0.);
      ecc2.push_back(ecc2vsBimp -> GetBinContent(i+1));
      ecc2E.push_back(ecc2vsBimp -> GetBinError(i+1));
    }

    gr[e][0] = new TGraphErrors(nBbins,&b[0],&ecc2[0],&bE[0],&ecc2E[0]);
    ecc2.clear();
    ecc2E.clear();
    b.clear();
    bE.clear();
    ecc2vsBimp = (TProfile *) fi_Glauber -> Get("prEcc2vsB");
    ecc2vsBimp = (TProfile*)ecc2vsBimp->Rebin(nBbins,"ecc2vsBimp_rebin",&bimp_binning[0]);
    for (int i=0; i<nBbins; i++){
      b.push_back(ecc2vsBimp -> GetBinCenter(i+1));
      bE.push_back(0.);
      ecc2.push_back(ecc2vsBimp -> GetBinContent(i+1));
      ecc2E.push_back(ecc2vsBimp -> GetBinError(i+1));
    }
    gr[e][1] = new TGraphErrors(nBbins,&b[0],&ecc2[0],&bE[0],&ecc2E[0]);

  }
  TCanvas c;
  for (int m=0; m<nmodel; m++)
  {
    gr[0][m]->SetMarkerStyle(20+4*m);
    gr[1][m]->SetMarkerStyle(21+4*m);
    gr[2][m]->SetMarkerStyle(22+4*m);
    gr[3][m]->SetMarkerStyle(24+4*m);
  }
  for (int e=0; e<nenergy; e++)
  {
    for (int m=0; m<nmodel; m++)
    {
    gr[e][m]->SetMarkerSize(1.3);
    gr[e][m]->SetTitle(";b, fm;<#epsilon_{2}>");
    gr[e][m]->GetXaxis()->SetRangeUser(0,12);
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
      if (m==0 && e==3) continue;
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
      if (m==0 && e==3) continue;
      l->AddEntry(gr[e][m],Form("%s GeV (%s)",energy[e].Data(),model[m].Data()),"p");
    }
  }
  l->Draw();
  // tex.DrawLatex(10,0.50,"#tau < 3.2 fm/c");
  c.SaveAs("ecc2vsBimp.png");
  // c.SaveAs("ecc2_wo_t_start_cut.png");
}