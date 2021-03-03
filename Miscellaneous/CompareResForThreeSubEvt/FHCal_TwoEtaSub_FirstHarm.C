void FHCal_TwoEtaSub_FirstHarm()
{
  // double res2FHCal[9] = {0.402391, 0.627781, 0.757747, 0.814076, 0.825777, 0.808424, 0.771776, 0.716457, 0.66312};
  // double res2FHCalL[9] = {0.358572, 0.645371, 0.747921, 0.800397, 0.824846, 0.808479, 0.760895, 0.716519, 0.666518};
  // double res2FHCalR[9] = {0.451566, 0.610671, 0.767703, 0.827988, 0.826709, 0.808369, 0.782812, 0.716395, 0.659738}; // eta_gap=1
  double res2FHCal[9] = {0.407205, 0.626196, 0.757244, 0.815119, 0.825017, 0.80885, 0.767927, 0.696776, 0.614317};
  double res2FHCalL[9] = {0.412493, 0.628498, 0.759561, 0.812477, 0.823298, 0.807305, 0.766597, 0.695812, 0.614899};
  double res2FHCalR[9] = {0.401985, 0.623903, 0.754933, 0.81777, 0.826739, 0.810397, 0.769259, 0.697742, 0.613736};
  double x[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double errx[9] = {0.};
  int markerStyle[7] = {20,28,27,23,24,25,26};

  TGraphErrors *gr[3];
  gr[0] = new TGraphErrors(9,x,res2FHCal,errx,errx);
  gr[1] = new TGraphErrors(9,x,res2FHCalL,errx,errx);
  gr[2] = new TGraphErrors(9,x,res2FHCalR,errx,errx);
  for (int i=0; i<3; i++)
  {
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->GetYaxis()->SetRangeUser(0,1);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    gr[i]->SetTitle(";Centrality, %;Res_{1}(#Psi_{1})");
  }  
  
  TString legendEntry[3] = {"FHCal L/R (2-#eta-sub)","FHCal L (3-#eta-sub)", "FHCal R (3-#eta-sub)"};
  TCanvas can;
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  gr[2]->Draw("P PLC PMC");
  TLegend *leg1 = new TLegend(0.5,0.2,0.8,0.4);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->AddEntry(gr[2],legendEntry[2].Data(),"p");
  leg1->Draw();
  TLatex tex;
  tex.DrawLatex(15.,0.45,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  can.SaveAs("Config1_Res1FHCal.pdf");
  can.SaveAs("Config1_Res1FHCal.png");
}