void TPC_TwoEtaSub()
{
  double res2TPC[9] = {0.160595, 0.272198, 0.350073, 0.368081, 0.336855, 0.280704, 0.224385, 0.191913, 0.192041};
  // Left TPC Resolution (3-sub event):
  double res2TPCL[9] = {0.163155, 0.272926, 0.350384, 0.367444, 0.335892, 0.280769, 0.22538, 0.202976, 0.216007};
  // Right TPC Resolution (3-sub event):
  double res2TPCR[9] = {0.158075, 0.271472, 0.349762, 0.36872, 0.33782, 0.280639, 0.223395, 0.181453, 0.170735};
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
    gr[i]->GetYaxis()->SetRangeUser(0,0.5);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    gr[i]->SetTitle(";Centrality, %;Res_{2}(#Psi_{2})");
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
  TLegend *leg1 = new TLegend(0.5,0.65,0.8,0.78);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->AddEntry(gr[2],legendEntry[2].Data(),"p");
  leg1->Draw();
  TLatex tex;
  tex.DrawLatex(30.,0.45,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  can.SaveAs("Config2_Res2TPC.pdf");
  can.SaveAs("Config2_Res2TPC.png");
}