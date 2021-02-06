void Compare()
{
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);

  const int ratioToMethod = 0;
  const int ncent = 9;
  const double bin_cent[ncent + 1] = {0, 5, 10, 20, 30, 40, 50, 60, 70, 80};
  const int nmethod = 4;
  const TString methodName[nmethod] = {"v_{2}{4}","v_{2}{2}","v_{2}{#Psi_{2,TPC}}","v_{2}{LYZ, Sum}"};
  const int marker[nmethod] = {25,27,20,23};
  const int markerColor[nmethod] = {1,210,214,205};
  const double markerSize = 1.8;
  const double ymax = 0.072;
  const double ymin = -0.002;
  const double xmax = 60.;
  const double xmin = 0.;
  const double ymaxRatio = 1.205;
  const double yminRatio = 0.795;
  TString label = "AMPT, #sigma_{p}=1.5 mb, Au+Au, h^{#pm}, 0.2<p_{T}<3.0 GeV/c, |#eta|<1.5"; 
  // v24, v22, v2EP, v2LYZ
  // 7.7 GeV
  double v2_77[nmethod][ncent] = {
    {0.00537454, 0.0212914, 0.0357041, 0.0482054, 0.0547887, 0.0565958, 0.0534608, 0.0465203, 0.0275073},
    {0.0113216, 0.0232893, 0.0371917, 0.0496032, 0.0563328, 0.0586043, 0.0567791, 0.0513854, 0.0453823},
    {0.0137825, 0.0247818, 0.0383146, 0.0507175, 0.057651, 0.0601278, 0.058893, 0.0541198, 0.0488181},
    {0.0193048, 0.0224333, 0.0317347, 0.0471285, 0.0540729, 0.0565354, 0.0540885, 0.0510156, 0.0644466}
  };
  double v2e_77[nmethod][ncent] = {
    {0.0140557, 0.000379915, 0.000119255, 0.00010169, 0.000123726, 0.000190571, 0.000407178, 0.00129339, 0.016424},
    {8.09656e-05, 5.04225e-05, 3.19245e-05, 3.47904e-05, 4.07511e-05, 5.03289e-05, 6.85703e-05, 0.000108643, 0.000200761},
    {0.000150452, 9.05502e-05, 5.11536e-05, 5.32313e-05, 6.28924e-05, 8.07655e-05, 0.000116002, 0.000187356, 0.000318933},
    {0.00897757, 0.00893256, 0.000893764, 0.000161481, 0.000189812, 0.000394812, 0.00289353, 0.13232, 0.107653}
  };
  //11.5
  double v2_115[nmethod][ncent] = {
    {10, 0.020776, 0.0354656, 0.048369, 0.0554192, 0.057536, 0.0551578, 0.0478817, 0.0410066},
    {0.0139146, 0.0246251, 0.0381705, 0.0509129, 0.0582498, 0.0610783, 0.059685, 0.0545889, 0.0476602},
    {0.0153683, 0.025527, 0.0389159, 0.0516424, 0.0591287, 0.062237, 0.0613262, 0.0569484, 0.0507278},
    {0.0154659, 0.0225698, 0.0332932, 0.0472447, 0.0547136, 0.0572985, 0.053923, 0.0482132, 0.0572468}
  };
  double v2e_115[nmethod][ncent] = {
    {0, 0.00024747, 7.70506e-05, 6.506e-05, 7.72696e-05, 0.000114822, 0.000223266, 0.000677737, 0.00265276},
    {4.65402e-05, 3.41064e-05, 2.25827e-05, 2.4824e-05, 2.8876e-05, 3.50411e-05, 4.6458e-05, 7.11101e-05, 0.000129373},
    {9.02443e-05, 5.96848e-05, 3.43632e-05, 3.56785e-05, 4.17296e-05, 5.28781e-05, 7.50528e-05, 0.000121461, 0.00021458},
    {0.0884387, 0.00183321, 0.000204375, 8.17905e-05, 9.13648e-05, 0.000162065, 0.000909222, 0.0490166, 0.105525}
  };

  double ratioIntFlow_77[nmethod][ncent], ratioIntFlowE_77[nmethod][ncent];
  for (int ic = 0; ic < ncent; ic++){
    for (int i=0; i<nmethod; i++){
    ratioIntFlow_77[i][ic] = v2_77[i][ic]/v2_77[ratioToMethod][ic]; // v24
    ratioIntFlowE_77[i][ic] = ratioIntFlow_77[i][ic]
     * sqrt(pow( v2e_77[i][ic]/ v2_77[i][ic], 2) + pow(v2e_77[ratioToMethod][ic] / v2_77[ratioToMethod][ic], 2));
    }
  }

  double ratioIntFlow_115[nmethod][ncent], ratioIntFlowE_115[nmethod][ncent];
  for (int ic = 0; ic < ncent; ic++){
    for (int i=0; i<nmethod; i++){
    ratioIntFlow_115[i][ic] = v2_115[i][ic]/v2_115[ratioToMethod][ic]; // v24
    ratioIntFlowE_115[i][ic] = ratioIntFlow_115[i][ic]
     * sqrt(pow( v2e_115[i][ic]/ v2_115[i][ic], 2) + pow(v2e_115[ratioToMethod][ic] / v2_115[ratioToMethod][ic], 2));
    }
  }

  TCanvas c("c","",1600,1200);
  c.SetLeftMargin(0.12);
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,label.Data());
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->Draw();
  c.Divide(2,2,0,0);
  c.cd(1);
  TH1F *hV2_77[nmethod];
  for (int im = 0; im < nmethod; im++){
    hV2_77[im] = new TH1F("",";centrality, %;v_{2}", ncent, &bin_cent[0]);
    for (int ic = 1; ic < ncent; ic++){
      hV2_77[im]->SetBinContent(ic+1, v2_77[im][ic]  );
      hV2_77[im]->SetBinError(  ic+1, v2e_77[im][ic] );
    }
    hV2_77[im]->SetMarkerStyle(marker[im]);
    hV2_77[im]->SetMarkerSize(markerSize);
    hV2_77[im]->SetLineColor(markerColor[im]);
    hV2_77[im]->SetMarkerColor(markerColor[im]);

    hV2_77[im]->GetYaxis()->SetRangeUser(ymin, ymax);
    hV2_77[im]->GetXaxis()->SetRangeUser(xmin, xmax);
    if (im==0) hV2_77[im]->Draw();
    else hV2_77[im]->Draw("same");
  }

  TLegend *leg = new TLegend(0.65,0.1,0.9,0.4);
  leg->SetBorderSize(0);
  for (int im = 0; im < nmethod; im++){
    leg->AddEntry(hV2_77[im],methodName[im].Data(),"p");
  }
  leg->Draw();
  TLatex tex;
  tex.DrawLatex(5.,0.065,"#sqrt{s_{NN}}=7.7 GeV");
  c.cd(2);
  TH1F *hV2_115[nmethod];
  for (int im = 0; im < nmethod; im++){
    hV2_115[im] = new TH1F("",";centrality, %;v_{2}", ncent, &bin_cent[0]);
    for (int ic = 1; ic < ncent; ic++){
      hV2_115[im]->SetBinContent(ic+1, v2_115[im][ic]  );
      hV2_115[im]->SetBinError(  ic+1, v2e_115[im][ic] );
    }
    hV2_115[im]->SetMarkerStyle(marker[im]);
    hV2_115[im]->SetMarkerSize(markerSize);
    hV2_115[im]->SetLineColor(markerColor[im]);
    hV2_115[im]->SetMarkerColor(markerColor[im]);

    hV2_115[im]->GetYaxis()->SetRangeUser(ymin, ymax);
    hV2_115[im]->GetXaxis()->SetRangeUser(xmin, xmax);

  }
  hV2_115[1]->Draw();
  for (int im = 0; im < nmethod; im++) hV2_115[im]->Draw("same");
  tex.DrawLatex(5.,0.065,"#sqrt{s_{NN}}=11.5 GeV");
  c.cd(3);
  TH1F *hV2_77_Ratio[nmethod];
  for (int im = 0; im < nmethod; im++){
    hV2_77_Ratio[im] = new TH1F("",";centrality, %;Ratio to v_{2}{4}", ncent, &bin_cent[0]);
    for (int ic = 1; ic < ncent; ic++){
      hV2_77_Ratio[im]->SetBinContent(ic+1, ratioIntFlow_77[im][ic]  );
      hV2_77_Ratio[im]->SetBinError(  ic+1, ratioIntFlowE_77[im][ic] );
    }
    hV2_77_Ratio[im]->SetMarkerStyle(marker[im]);
    hV2_77_Ratio[im]->SetMarkerSize(markerSize);
    hV2_77_Ratio[im]->SetLineColor(markerColor[im]);
    hV2_77_Ratio[im]->SetMarkerColor(markerColor[im]);

    hV2_77_Ratio[im]->GetYaxis()->SetRangeUser(yminRatio, ymaxRatio);
    hV2_77_Ratio[im]->GetXaxis()->SetRangeUser(xmin, xmax);
    
  }
  hV2_77_Ratio[0]->Draw();
  for (int im = 1; im < nmethod; im++) hV2_77_Ratio[im]->Draw("same");
  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(xmin,1.,xmax,1.);
  c.cd(4);
  TH1F *hV2_115_Ratio[nmethod];
  for (int im = 0; im < nmethod; im++){
    hV2_115_Ratio[im] = new TH1F("",";centrality, %;Ratio to v_{2}{4}", ncent, &bin_cent[0]);
    for (int ic = 1; ic < ncent; ic++){
      hV2_115_Ratio[im]->SetBinContent(ic+1, ratioIntFlow_115[im][ic]  );
      hV2_115_Ratio[im]->SetBinError(  ic+1, ratioIntFlowE_115[im][ic] );
    }
    hV2_115_Ratio[im]->SetMarkerStyle(marker[im]);
    hV2_115_Ratio[im]->SetMarkerSize(markerSize);
    hV2_115_Ratio[im]->SetLineColor(markerColor[im]);
    hV2_115_Ratio[im]->SetMarkerColor(markerColor[im]);

    hV2_115_Ratio[im]->GetYaxis()->SetRangeUser(yminRatio, ymaxRatio);
    hV2_115_Ratio[im]->GetXaxis()->SetRangeUser(xmin, xmax);
    
  }
  hV2_115_Ratio[0]->Draw();
  for (int im = 1; im < nmethod; im++) hV2_115_Ratio[im]->Draw("same");
  lineOne.DrawLine(xmin,1.,xmax,1.);

  c.SaveAs("Compare.pdf");
  c.SaveAs("Compare.png");




}