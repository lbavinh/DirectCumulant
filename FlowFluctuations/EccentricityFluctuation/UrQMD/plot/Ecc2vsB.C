void Ecc2vsB()
{
  const int nenergy = 3;
  const TString energy[nenergy]={"4.5","7.7","11.5"};
  TGraphErrors *gr[nenergy];
  for (int e=0; e<nenergy; e++){
    TFile *fi = new TFile(Form("../ROOTFile/UrQMD_%sGeV.root",energy[e].Data()),"read");
    TProfile *ecc2vsBimp = (TProfile *) fi -> Get("ValvsB/pEcc2vsB6");
  

    vector<double> bimp_binning={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,20};
    int nBbins = bimp_binning.size()-1;
    ecc2vsBimp = (TProfile*)ecc2vsBimp->Rebin(nBbins,"ecc2vsBimp_rebin",&bimp_binning[0]);
    vector<Double_t> ecc2, ecc2E, b, bE;
    // int nBbins = ecc2vsBimp->GetNbinsX();
    for (int i=0; i<nBbins; i++){
      b.push_back(ecc2vsBimp -> GetBinCenter(i+1));
      bE.push_back(0.);
      ecc2.push_back(ecc2vsBimp -> GetBinContent(i+1));
      cout << ecc2.at(i) << endl;
      ecc2E.push_back(ecc2vsBimp -> GetBinError(i+1));
    }
    
    gr[e] = new TGraphErrors(nBbins,&b[0],&ecc2[0],&bE[0],&ecc2E[0]);
    
    gr[e]->SetMarkerSize(1.3);
    gr[e]->SetTitle(";b, fm;<#epsilon_{2}>");
    gr[e]->GetXaxis()->SetRangeUser(0,12);
    gr[e]->SetMinimum(0.);
    gr[e]->SetMaximum(0.6);
  }
  TCanvas c;
  gr[0]->SetMarkerStyle(24);
  gr[1]->SetMarkerStyle(22);
  gr[2]->SetMarkerStyle(25);

  gStyle->SetPalette(kDarkRainBow);
  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  gr[2]->Draw("P PLC PMC");  
  TLatex tex;
  tex.SetTextFont(42);
  tex.DrawLatex(1,0.5,"UrQMD, Au+Au");
  // tex.DrawLatex(10,0.50,"#tau < 3.2 fm/c");

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

  c.SaveAs("ecc2vsBimp.png");
  // c.SaveAs("ecc2_wo_t_start_cut.png");
}