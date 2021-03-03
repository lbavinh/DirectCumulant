void Compare()
{
  // TPC Resolution (2sub-event) with respect to 2-nd harm:
  double res2TPC[9] = {0.160595, 0.272198, 0.350073, 0.368081, 0.336855, 0.280704, 0.224385, 0.191913, 0.192041};
  // Left TPC Resolution (3-sub event):
  double res2TPCL[9] = {0.163155, 0.272926, 0.350384, 0.367444, 0.335892, 0.280769, 0.22538, 0.202976, 0.216007};
  // Right TPC Resolution (3-sub event):
  double res2TPCR[9] = {0.158075, 0.271472, 0.349762, 0.36872, 0.33782, 0.280639, 0.223395, 0.181453, 0.170735};
  // FHCal Resolution w.r.t 1-st harmonic:
  double res1FHCal[9] = {0.609859, 0.79596, 0.876246, 0.907459, 0.912089, 0.903681, 0.881933, 0.841826, 0.779845};
  // FHCal Resolution (3sub-event) with respect to 1-st harm:
  double res1FHCal3sub[9] = {0.124514, 0.302594, 0.451299, 0.561669, 0.612925, 0.63304, 0.623014, 0.571718, 0.475696};
  // FHCal Resolution (3sub-event) with respect to 2-nd harm:
  double res2FHCal3sub[9] = {0.0676681, 0.177453, 0.257433, 0.26227, 0.202053, 0.109466, 0.0251986, 0.0133402, 0.};
  // FHCal Resolution w.r.t 2-nd harmonic:
  double res2FHCal[9] = {0.0995286, 0.187507, 0.269828, 0.275466, 0.219263, 0.129643, 0.0530632, 0.07294, 0.0973222};
  double x[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double errx[9] = {0.};
  int markerStyle[7] = {20,28,27,23,24,25,26};
  TGraphErrors *gr[7];
  gr[0] = new TGraphErrors(9,x,res2TPC,errx,errx);
  gr[1] = new TGraphErrors(9,x,res2TPCL,errx,errx);
  gr[2] = new TGraphErrors(9,x,res2TPCR,errx,errx);

  gr[3] = new TGraphErrors(9,x,res2FHCal,errx,errx);
  gr[4] = new TGraphErrors(9,x,res2FHCal3sub,errx,errx);

  gr[5] = new TGraphErrors(9,x,res1FHCal,errx,errx);
  gr[6] = new TGraphErrors(9,x,res1FHCal3sub,errx,errx);

  TString legendEntry[7] = {"TPC R/L", "TPC L (3-sub)", "TPC R (3-sub)", "FHCal L+R", "FHCal L+R (3-sub)", "FHCal L+R", "FHCal L+R (3-sub)"};
  for (int i=0; i<7; i++)
  {
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->GetYaxis()->SetRangeUser(0,1);
    gr[i]->GetXaxis()->SetLimits(0,80);
    gr[i]->GetXaxis()->SetNdivisions(208);
    gr[i]->GetYaxis()->SetNdivisions(508);
    if (i<5) gr[i]->SetTitle(";Centrality, %;Res(#Psi_{n})");
    else{ gr[i]->SetTitle(";Centrality, %;Res(#Psi_{n})"); }
  }
  TCanvas can;
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  TPaveLabel* label = new TPaveLabel(0.1,0.95,0.9,0.99,"UrQMD, Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();
  can.Divide(3,1,0,0);
  can.cd(1);

  gr[0]->Draw("AP PLC PMC");
  gr[1]->Draw("P PLC PMC");
  gr[2]->Draw("P PLC PMC");
  TLegend *leg1 = new TLegend(0.3,0.7,0.8,0.8);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->SetHeader("Res(#Psi_{2})");
  leg1->AddEntry(gr[0],legendEntry[0].Data(),"p");
  leg1->AddEntry(gr[1],legendEntry[1].Data(),"p");
  leg1->AddEntry(gr[2],legendEntry[2].Data(),"p");
  leg1->Draw();

  can.cd(2);

  gr[3]->Draw("AP PLC PMC");
  gr[4]->Draw("P PLC PMC");
  TLegend *leg2 = new TLegend(0.3,0.7,0.8,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->SetHeader("Res(#Psi_{2})");
  leg2->AddEntry(gr[3],legendEntry[3].Data(),"p");
  leg2->AddEntry(gr[4],legendEntry[4].Data(),"p");
  leg2->Draw();

  can.cd(3);

  gr[5]->Draw("AP PLC PMC");
  gr[6]->Draw("P PLC PMC");
  TLegend *leg3 = new TLegend(0.3,0.2,0.8,0.3);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.04);
  leg3->SetHeader("Res(#Psi_{1})");
  leg3->AddEntry(gr[5],legendEntry[5].Data(),"p");
  leg3->AddEntry(gr[6],legendEntry[6].Data(),"p");
  leg3->Draw();
  TLatex tex;
  tex.DrawLatex(30.,0.3,"|#Delta#eta|^{TPC}>2");
  can.SaveAs("CompareRes.pdf");
}
// /weekly/parfenov/Soft/FlowANA/McPicoReader.C 
// /weekly/parfenov/Soft/FlowANA/res3sub.C 