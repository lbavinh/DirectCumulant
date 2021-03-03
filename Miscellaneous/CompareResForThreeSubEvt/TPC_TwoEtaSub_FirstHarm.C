void TPC_TwoEtaSub_FirstHarm()
{
  // double res2TPC[9] = {0.223754, 0.196945, 0.2118, 0.220772, 0.21686, 0.239546, 0.241125, 0.258975, 0.276253};
  // double res2TPCL[9] = {0.232972, 0.204899, 0.214283, 0.221453, 0.221459, 0.23631, 0.246033, 0.25614, 0.270362};
  // double res2TPCR[9] = {0.214899, 0.1893, 0.209346, 0.220092, 0.212358, 0.242827, 0.236314, 0.261842, 0.282273}; // eta_gap=1
  double res2TPC[9] = {0.445757, 0.452034, 0.451493, 0.453612, 0.452738, 0.45347, 0.446697, 0.436919, 0.436073};
  double res2TPCL[9] = {0.469959, 0.459813, 0.456481, 0.452013, 0.452742, 0.448903, 0.447283, 0.439022, 0.437747};
  double res2TPCR[9] = {0.422801, 0.444386, 0.44656, 0.455217, 0.452734, 0.458084, 0.446112, 0.434826, 0.434404};

  double x[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double errx[9] = {0.};
  int markerStyle[7] = {20,28,27,23,24,25,26};

  TGraphErrors *gr[3];
  gr[0] = new TGraphErrors(9,x,res2TPC,errx,errx);
  gr[1] = new TGraphErrors(9,x,res2TPCL,errx,errx);
  gr[2] = new TGraphErrors(9,x,res2TPCR,errx,errx);
  for (int i=0; i<3; i++)
  {
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->GetYaxis()->SetRangeUser(0,1);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    gr[i]->SetTitle(";Centrality, %;Res_{1}(#Psi_{1})");
  }  
  
  TString legendEntry[3] = {"TPC L/R (2-#eta-sub)","TPC L (3-#eta-sub)", "TPC R (3-#eta-sub)"};
  TCanvas can;
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  gr[2]->Draw("P PLC PMC");
  TLegend *leg1 = new TLegend(0.5,0.7,0.8,0.85);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->AddEntry(gr[2],legendEntry[2].Data(),"p");
  leg1->Draw();
  TLatex tex;
  tex.DrawLatex(15.,0.65,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  can.SaveAs("Config2_Res1TPC.pdf");
  can.SaveAs("Config2_Res1TPC.png");
}