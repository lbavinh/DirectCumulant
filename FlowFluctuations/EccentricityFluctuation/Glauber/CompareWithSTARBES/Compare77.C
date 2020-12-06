void Compare77()
{
  const double centE[9]={0};
  const double cent[9]={2.5,7.5,15,25,35,45,55,65,75};
  double ecc22[2][9] = {{0.0972787, 0.144257, 0.216788, 0.299268, 0.36967, 0.434684, 0.497773, 0.564191, 0.640236},
                        {0.0960504, 0.142373, 0.2143, 0.296078, 0.366328, 0.430967, 0.494409, 0.560023, 0.635028}};
  double ecc22E[2][9] = {{5.70976e-05, 7.23493e-05, 6.55047e-05, 7.81319e-05, 8.9796e-05, 0.000100519, 0.000111758, 0.000124251, 0.000134879},
                         {5.65954e-05, 7.19949e-05, 6.53773e-05, 7.80956e-05, 8.96492e-05, 0.000100239, 0.000111674, 0.000124117, 0.000134755}};
  double ecc22STAR[2][9] = {{0.117,0.16,0.24,0.32,0.39,0.46,0.53,0.62,0.72},
                            {0.116,0.16,0.24,0.32,0.39,0.46,0.53,0.62,0.71}};
  double ecc22STARE[2][9] = {{0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.04},
                             {0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.05}};
  TGraphErrors *gr[2][2];
  for (int e=0; e<2; e++){
    gr[e][0] = new TGraphErrors(9,cent,ecc22[e],centE,ecc22E[e]);
    gr[e][1] = new TGraphErrors(9,cent,ecc22STAR[e],centE,ecc22STARE[e]);
    gr[e][0]->SetMarkerStyle(21);
    gr[e][0]->SetMarkerColor(kRed+2);
    gr[e][1]->SetMarkerStyle(22);
    gr[e][1]->SetMarkerColor(kBlue+2);
    for (int m=0; m<2; m++){
    gr[e][m]->SetMarkerSize(1.3);  
    gr[e][m]->SetTitle(";Centrality (%);#epsilon_{2}{2}");
    gr[e][m]->GetXaxis()->SetRangeUser(0,80);
    gr[e][m]->SetMinimum(0.);
    gr[e][m]->SetMaximum(0.8);
    }

  }

  TCanvas c;
  gr[0][0]->Draw("AP");
  gr[0][1]->Draw("P");
  TLegend *l = new TLegend(0.15,0.6,0.4,0.85);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->SetHeader("Au+Au at #sqrt{s_{NN}} = 7.7 GeV");
  l->AddEntry(gr[0][0],"Glauber","p");
  l->AddEntry(gr[0][1],"STAR BES","p");
  l->Draw();
  c.SaveAs("ecc22vsCent_vsSTARBES77GeV.png");

}