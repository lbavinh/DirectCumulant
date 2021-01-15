void plotv2UrQMD77()
{
  Double_t eX[7]={0.};
  Double_t cent[7] = {2.5,7.5,15,25,35,45,55};
  // v22, v24, v2TPC, v2LYZ
  TString method[4] = {"v_{2}{2}","v_{2}{4}","v_{2}{TPC}","v_{2}{LYZ}"};
  Double_t v2[4][7] = {
    {0.0120079, 0.0220798, 0.0323940, 0.0407132, 0.0439643, 0.0434853, 0.0407371},
    {111111111, 0.0202380, 0.0306176, 0.0390201, 0.0412685, 0.0391890, 0.0346015},
    {0.0123947, 0.0222897, 0.0326827, 0.0410350, 0.0444106, 0.0439964, 0.0411749},
    {0.0277605, 0.0292579, 0.0309128, 0.0378464, 0.0462157, 0.0487147, 0.0707277}};  
  Double_t v2e[4][7] = {
    {7.14082e-05, 4.70930e-05, 3.04723e-05, 3.47084e-05, 4.43942e-05, 6.24593e-05, 9.98216e-05},
    {0.000000000, 0.000275786, 0.000113611, 0.000112971, 0.000179747, 0.000397169, 0.001249070},
    {0.000109974, 6.83464e-05, 4.17249e-05, 4.72411e-05, 6.09666e-05, 8.62864e-05, 0.000131244},
    {0.000220184, 0.000291683, 0.000402764, 0.000347186, 0.000323006, 0.001246200, 0.000372922}};
  TGraphErrors *gr[4];
  for (int i=0;i<4;i++)
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
  gr[0] -> SetLineColor(kRed+3);
  gr[1] -> SetLineColor(kGreen+3);
  gr[2] -> SetLineColor(kBlue+3);
  gr[3] -> SetLineColor(kBlack);

  TCanvas c;
  gr[0] -> SetTitle("UrQMD, Au+Au #sqrt{s_{NN}}=7.7 GeV, h^{#pm}, 0.2<p_{T}<3.0 GeV/c;centrality, %;v_{2}");
  gr[0] -> GetYaxis()->SetRangeUser(0,0.08);
  gr[0] -> GetXaxis()->SetRangeUser(0,60);
  gr[0]->Draw("AP");
  for (int i=1;i<4;i++)
  {
    gr[i]->Draw("PL");
  }
  TLegend *leg = new TLegend(0.7,0.15,0.9,0.3);
  leg->SetBorderSize(0);
  for (int i=0;i<4;i++)
  {
    leg -> AddEntry(gr[i],method[i].Data(),"p");
  }
  leg -> Draw();
  c.SaveAs("LYZ.png");

}