void FHCal_Full()
{
  double res2FHCalApprox[9] = {0.0995286, 0.187507, 0.269828, 0.275466, 0.219263, 0.129643, 0.0530632, 0.07294, 0.0973222};
  double res2FHCal3sub[9] = {0.0676681, 0.177453, 0.257433, 0.26227, 0.202053, 0.109466, 0.0251986, 0.0133402, 0.};
  double x[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double errx[9] = {0.};
  int markerStyle[7] = {20,28,27,23,24,25,26};

  TGraphErrors *gr[2];
  gr[0] = new TGraphErrors(9,x,res2FHCalApprox,errx,errx);
  gr[1] = new TGraphErrors(9,x,res2FHCal3sub,errx,errx);
  for (int i=0; i<2; i++)
  {
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->GetYaxis()->SetRangeUser(0,0.5);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    gr[i]->SetTitle(";Centrality, %;Res_{2}(#Psi_{2})");
  }  
  
  TString legendEntry[2] = {"FHCal L+R (Approx.)","FHCal L+R (3-#eta-sub)"};
  TCanvas can;
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  TLegend *leg1 = new TLegend(0.5,0.65,0.8,0.78);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->Draw();
  TLatex tex;
  tex.DrawLatex(30.,0.45,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  can.SaveAs("Config2_Res2FHCal.pdf");
  can.SaveAs("Config2_Res2FHCal.png");
}