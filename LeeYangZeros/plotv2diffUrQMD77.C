void plotv2diffUrQMD77()
{
  Double_t eX[9]={0.};
  Double_t cent[9] = {0.3,0.5,0.7,0.9,1.1,1.35,1.65,2.15,2.75};
  // v22, v24, v2TPC, v2LYZ
  TString method[4] = {"v_{2}{2}","v_{2}{4}","v_{2}{#Psi_{2,TPC}}","v_{2}{LYZ}"};
  Double_t v2[4][9] = {
    {0.0233638, 0.0321127, 0.0362688, 0.0418208, 0.0487735, 0.0566999, 0.0669486, 0.0777085, 0.0891267},
    {0.0219784, 0.0304235, 0.0339408, 0.0395583, 0.0468198, 0.0531505, 0.0662188, 0.0745372, 0.089785},
    {0.0239969, 0.0326456, 0.0362478, 0.0415883, 0.0480493, 0.0561734, 0.0659362, 0.0761272, 0.0874353},
    {0.0365,    0.0345   , 0.0438   , 0.0299   , 0.0232   , 0.0566   , 0.0803   , 0.117    , 0.0861   }};  
  Double_t v2e[4][9] = {
    {4.64711e-05, 6.71729e-05, 0.000102205, 0.000148167, 0.000206095, 0.0002468, 0.000400834, 0.000571197, 0.00216526},
    {0.000273568, 0.0003732, 0.000545258, 0.000779077, 0.00109445, 0.00132929, 0.00214549, 0.00303766, 0.0105646},
    {6.49941e-05, 8.33979e-05, 0.000108988, 0.000141701, 0.000186891, 0.000221467, 0.000367873, 0.000546756, 0.00227037},
    {0.00113, 0.00146, 0.0019, 0.00247, 0.00326, 0.00386, 0.00641, 0.00949,0.0396}};

  TGraphErrors *gr[4];
  for (int i=0;i<4;i++)
  {
    gr[i] = new TGraphErrors(9,cent,v2[i],eX,v2e[i]);
    gr[i] -> SetMarkerStyle(20+i);
    gr[i] -> SetMarkerSize(1.2);
    gr[i] -> SetLineWidth(2);
    gr[i] -> RemovePoint(0);
  }
  gr[0] -> SetMarkerColor(kRed+3);
  gr[1] -> SetMarkerColor(kGreen+3);
  gr[2] -> SetMarkerColor(kBlue+3);
  gr[3] -> SetMarkerColor(kBlack);
  // gr[4] -> SetMarkerColor(kCyan+1);
  gr[0] -> SetLineColor(kRed+3);
  gr[1] -> SetLineColor(kGreen+3);
  gr[2] -> SetLineColor(kBlue+3);
  gr[3] -> SetLineColor(kBlack);
  // gr[4] -> SetLineColor(kCyan+1);

  TCanvas c;
  gr[0] -> SetTitle("UrQMD, Au+Au #sqrt{s_{NN}}=7.7 GeV, h^{#pm},|#eta|<1.5, 10-20%;p_{T}, GeV/c;v_{2}");
  gr[0] -> GetYaxis()->SetRangeUser(0,0.15);
  gr[0] -> GetXaxis()->SetRangeUser(0,3.);
  gr[0]->Draw("APL");
  for (int i=1;i<4;i++)
  {
    // if (i==3) continue;
    gr[i]->Draw("PL");
  }
  TLegend *leg = new TLegend(0.7,0.15,0.85,0.35);
  leg->SetBorderSize(0);
  for (int i=0;i<4;i++)
  {
    // if (i==3) continue;
    leg -> AddEntry(gr[i],method[i].Data(),"p");
  }
  leg -> Draw();
  c.SaveAs("LYZ_10-20.png");
  c.SaveAs("LYZ_10-20.pdf");

}