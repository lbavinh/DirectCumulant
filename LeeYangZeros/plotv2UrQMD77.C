void plotv2UrQMD77()
{
  Double_t eX[7]={0.};
  Double_t cent[7] = {2.5,7.5,15,25,35,45,55};
  // v22, v24, v2TPC, v2LYZ
  TString method[5] = {"v_{2}{2}","v_{2}{4}","v_{2}{#Psi_{2,TPC}}","v_{2}^{Product}{LYZ}","v_{2}^{Sum}{LYZ}"};
  Double_t v2[5][7] = {
    {0.0120079, 0.0220798, 0.0323940, 0.0407132, 0.0439643, 0.0434853, 0.0407371},
    {111111111, 0.0202380, 0.0306176, 0.0390201, 0.0412685, 0.0391890, 0.0346015},
    {0.0123947, 0.0222897, 0.0326827, 0.0410350, 0.0444106, 0.0439964, 0.0411749},
    // {0.0250144, 0.0253110, 0.0295299, 0.0331945, 0.0403593, 0.0552838, 0.0699126}, // my
    {0.0000000, 0.0342000, 0.0376000, 0.0392000, 0.0488000, 0.0652000, 0.0806000}, // Borghini's code
    {0.0188169, 0.0207075, 0.0234914, 0.0267185, 0.0312420, 0.0398536, 0.0414163}};  
  Double_t v2e[5][7] = {
    {7.14082e-05, 4.70930e-05, 3.04723e-05, 3.47084e-05, 4.43942e-05, 6.24593e-05, 9.98216e-05},
    {0.000000000, 0.000275786, 0.000113611, 0.000112971, 0.000179747, 0.000397169, 0.001249070},
    {0.000109974, 6.83464e-05, 4.17249e-05, 4.72411e-05, 6.09666e-05, 8.62864e-05, 0.000131244},
    // {0.000180526, 0.000392813, 0.000224329, 0.000441853, 0.000395329, 0.000144053, 0.000147296},
    {0.0,0.000315,0.000286,0.000776,0.000644,0.000405,0.000479},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
    // {0.013701, 0.0126163, 0.0102786, 0.0224198, 0.0354518, 0.0173681, 1.06708}
  TGraphErrors *gr[5];
  for (int i=0;i<5;i++)
  {
    gr[i] = new TGraphErrors(7,cent,v2[i],eX,v2e[i]);
    gr[i] -> SetMarkerStyle(20+i);
    gr[i] -> SetMarkerSize(1.2);
    gr[i] -> SetLineWidth(2);
    gr[i] -> RemovePoint(0);
  }
  gr[0] -> SetMarkerColor(kRed+3);
  gr[1] -> SetMarkerColor(kGreen+3);
  gr[2] -> SetMarkerColor(kBlue+3);
  gr[3] -> SetMarkerColor(kBlack);
  gr[4] -> SetMarkerColor(kCyan+1);
  gr[0] -> SetLineColor(kRed+3);
  gr[1] -> SetLineColor(kGreen+3);
  gr[2] -> SetLineColor(kBlue+3);
  gr[3] -> SetLineColor(kBlack);
  gr[4] -> SetLineColor(kCyan+1);

  TCanvas c;
  gr[0] -> SetTitle("UrQMD, Au+Au #sqrt{s_{NN}}=7.7 GeV, h^{#pm}, 0.2<p_{T}<3.0 GeV/c;centrality, %;v_{2}");
  gr[0] -> GetYaxis()->SetRangeUser(0,0.08);
  gr[0] -> GetXaxis()->SetRangeUser(0,60);
  gr[0]->Draw("APL");
  for (int i=1;i<5;i++)
  {
    // if (i==3) continue;
    gr[i]->Draw("PL");
  }
  TLegend *leg = new TLegend(0.7,0.15,0.85,0.35);
  leg->SetBorderSize(0);
  for (int i=0;i<5;i++)
  {
    // if (i==3) continue;
    leg -> AddEntry(gr[i],method[i].Data(),"p");
  }
  leg -> Draw();
  c.SaveAs("LYZ.png");
  c.SaveAs("LYZ.pdf");

}