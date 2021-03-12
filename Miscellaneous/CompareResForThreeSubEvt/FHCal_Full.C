void FHCal_Full()
{
  // double res2FHCalApprox[9] = {0.539752, 0.776864, 0.87774, 0.91216, 0.918623, 0.909002, 0.886465, 0.844807, 0.79559};
  // double res2FHCal3sub[9] = {0.397546, 0.747048, 0.850532, 0.892055, 0.875286, 0.870657, 0.829737, 0.831893, 0.769704};
  double res2FHCalApprox[9] = {0.539752, 0.776864, 0.87774, 0.912159, 0.918641, 0.909248, 0.888151, 0.853748, 0.810033};
  double res2FHCal3sub[9] = {0.358083, 0.664762, 0.793875, 0.849174, 0.852737, 0.817487, 0.804339, 0.737109, 0.643753};

  double x[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double errx[9] = {0.};
  int markerStyle[7] = {20,28,27,23,24,25,26};

  TGraphErrors *gr[2];
  gr[0] = new TGraphErrors(9,x,res2FHCalApprox,errx,errx);
  gr[1] = new TGraphErrors(9,x,res2FHCal3sub,errx,errx);
  for (int i=0; i<2; i++)
  {
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->GetYaxis()->SetRangeUser(0,1.);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    gr[i]->SetTitle(";Centrality, %;Res_{1}(#Psi_{1})");
  }  
  
  TString legendEntry[2] = {"FHCal L+R (Approx.)","FHCal L+R (3-sub)"};
  TCanvas can;
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  TLegend *leg1 = new TLegend(0.5,0.2,0.8,0.4);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->Draw();
  TLatex tex;
  tex.DrawLatex(30.,0.45,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  can.SaveAs("Config2_Res1FHCal.pdf");
  can.SaveAs("Config2_Res1FHCal.png");
}
// TCanvas c1;
// gStyle->SetOptStat(0)
// gStyle->SetLineWidth(2)
// gStyle->SetPalette(kDarkRainBow)
// prV1_2->SetTitle("UrQMD, Au+Au at #sqrt{s_{NN}}=7.7 GeV, h^{#pm};p_{T}, GeV/c;v_{1}")
// prV1_2->GetYaxis()->SetRangeUser(-0.1,0.01)
// prV1_2->Draw("PL PLC PMC")
// prV1_3->Draw("PL PLC PMC same")
// prV1_4->Draw("PL PLC PMC same")
// prV1_5->Draw("PL PLC PMC same")
// prV1_6->Draw("PL PLC PMC same")
// TLegend *leg1 = new TLegend(0.5,0.2,0.8,0.4);
// leg1->SetBorderSize(0);
// leg1->SetTextSize(0.04);
// leg1->AddEntry(prV1_2,"10-20%","ple");
// leg1->AddEntry(prV1_3,"20-30%","ple");
// leg1->AddEntry(prV1_4,"30-40%","ple");
// leg1->AddEntry(prV1_5,"40-50%","ple");
// leg1->AddEntry(prV1_6,"50-60%","ple");
// leg1->Draw();
// c1.SetLeftMargin(0.15)
// c1.Draw()


// gStyle->SetOptStat(0)
// prV1eta_2->Draw()
// prV1eta_2->SetTitle("UrQMD, Au+Au at #sqrt{s_{NN}}=7.7 GeV, 10-20%, h^{#pm}, 0.15 < p_{T} < 0.5 GeV/c;#eta;v_{1}")
// prV1eta_2->GetYaxis()->SetRangeUser(-0.05,0.01)
// c1->SetLeftMargin(0.15)
// c1->Draw()

// TCanvas c1;
// gStyle->SetOptStat(0)
// gStyle->SetPalette(kDarkRainBow)
// prV1_TPCEP_2->SetTitle("UrQMD, Au+Au at #sqrt{s_{NN}}=7.7 GeV, h^{#pm}, TPC EP, |#Delta#eta|>1.5, |#eta|<1.5;p_{T}, GeV/c;v_{1}")
// prV1_TPCEP_2->GetYaxis()->SetRangeUser(-0.15,0.01)
// prV1_TPCEP_2->Draw("PL PLC PMC")
// prV1_TPCEP_3->Draw("PL PLC PMC same")
// prV1_TPCEP_4->Draw("PL PLC PMC same")
// prV1_TPCEP_5->Draw("PL PLC PMC same")
// prV1_TPCEP_6->Draw("PL PLC PMC same")
// TLegend *leg1 = new TLegend(0.5,0.2,0.8,0.4);
// leg1->SetBorderSize(0);
// leg1->SetTextSize(0.04);
// leg1->AddEntry(prV1_TPCEP_2,"10-20%","ple");
// leg1->AddEntry(prV1_TPCEP_3,"20-30%","ple");
// leg1->AddEntry(prV1_TPCEP_4,"30-40%","ple");
// leg1->AddEntry(prV1_TPCEP_5,"40-50%","ple");
// leg1->AddEntry(prV1_TPCEP_6,"50-60%","ple");
// leg1->Draw();
// c1.SetLeftMargin(0.15)
// c1.Draw()