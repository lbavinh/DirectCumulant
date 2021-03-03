void FHCal_TwoEtaSub()
{
  double res2FHCal[9] = {0.0584711, 0.131816, 0.19954, 0.197273, 0.150637, 0.0958629, 0.033632, 0.0595364, 0.0527};
  double res2FHCalL[9] = {0.0589055, 0.132353, 0.197854, 0.196094, 0.151346, 0.0947136, 0.0328497, 0.0481105, 0.};
  double res2FHCalR[9] = {0.0580399, 0.131282, 0.20124, 0.198458, 0.149931, 0.0970262, 0.0344329, 0.0736759, 0.};
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
    gr[i]->GetYaxis()->SetRangeUser(0,0.5);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    gr[i]->SetTitle(";Centrality, %;Res_{2}(#Psi_{2})");
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
  TLegend *leg1 = new TLegend(0.5,0.65,0.8,0.78);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->AddEntry(gr[2],legendEntry[2].Data(),"p");
  leg1->Draw();
  TLatex tex;
  tex.DrawLatex(30.,0.45,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  can.SaveAs("Config1_Res2FHCal.pdf");
  can.SaveAs("Config1_Res2FHCal.png");
}