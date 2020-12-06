void Ratio()
{
  const int markerColor[]={2,3,45,6};
  const int markerStyle[]={21,22,23,24,25};
  const double centE[9]={0};
  const double cent[9]={2.5,7.5,15,25,35,45,55,65,75};

  double ecc22STAR[2][9] = {{0.117,0.16,0.24,0.32,0.39,0.46,0.53,0.62,0.72},
                            {0.116,0.16,0.24,0.32,0.39,0.46,0.53,0.62,0.71}};
  double ecc22STARE[2][9] = {{0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.04},
                             {0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.05}};

  double ecc2STAR[2][9] = {{0.102, 0.14, 0.22, 0.3, 0.37, 0.43, 0.5, 0.58, 0.68},
                           {0.102, 0.14, 0.21, 0.3, 0.37, 0.43, 0.5, 0.58, 0.68}};
  double ecc2STARE[2][9] = {{0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.04},
                            {0.003, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.05}};
  double ratioEcc2Ecc22[2][9]={{0.881337, 0.897875, 0.918491, 0.93755, 0.944015, 0.945596, 0.94488, 0.944171, 0.945998},
                               {0.881065, 0.897061, 0.917436, 0.93661, 0.943374, 0.945215, 0.94462, 0.943846, 0.945682}};
  double ratioEcc2Ecc22E[2][9]={{0.000742844, 0.00065943, 0.000409188, 0.000362822, 0.000341918, 0.00032864, 0.000321902, 0.000318909, 0.000309577},
                                {0.000745539, 0.00066388, 0.000412575, 0.000366358, 0.000344276, 0.000330374, 0.000323598, 0.00032069, 0.000311571}};
  TGraphErrors *gr[2];
  for (int e=0; e<2; e++){
    gr[e] = new TGraphErrors(9,cent,ratioEcc2Ecc22[e],centE,ratioEcc2Ecc22E[e]);
    gr[e]->SetMarkerSize(1.3);  
    gr[e]->SetTitle(";Centrality (%);#epsilon_{2}{part}/#epsilon_{2}{2}");
    gr[e]->SetMarkerStyle(markerStyle[e]+4);
    gr[e]->SetMarkerColor(markerColor[e]+3);
  }
  TGraphErrors *grRatio[2];
  for (int e=0; e<2; e++){
    vector<Double_t> ratio, ratioErr;
    for (int c=0; c<9; c++){
      ratio.push_back(ecc2STAR[e][c]/ecc22STAR[e][c]);
      ratioErr.push_back(ecc2STAR[e][c]/ecc22STAR[e][c]*(TMath::Sqrt(TMath::Power(ecc22STARE[e][c]/ecc22STAR[e][c],2)+TMath::Power(ecc2STARE[e][c]/ecc2STAR[e][c],2))));
    }
    grRatio[e] = new TGraphErrors(9,cent,&ratio[0],centE,&ratioErr[0]);
    grRatio[e]->SetMarkerSize(1.3);  
    grRatio[e]->SetTitle(";Centrality (%);#epsilon_{2}{part}/#epsilon_{2}{2}");
    grRatio[e]->SetMarkerStyle(markerStyle[e]);
    grRatio[e]->SetMarkerColor(markerColor[e]+1);
    grRatio[e]->SetLineColor(markerColor[e]+1);
    grRatio[e]->GetXaxis()->SetRangeUser(0,80);
    grRatio[e]->SetMinimum(0.3);
    grRatio[e]->SetMaximum(1.4);

  }
  TCanvas c;
  // grRatio[0]->Draw("AP");
  grRatio[1]->Draw("AP");
  // gr[0]->Draw("P");
  gr[1]->Draw("P");
  TLegend *l = new TLegend(0.15,0.15,0.4,0.4);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->SetHeader("Au+Au at #sqrt{s_{NN}} = 11.5 GeV");
  l->AddEntry(grRatio[1],"STAR BES","p");
  l->AddEntry(gr[1],"Glauber","p");
  l->Draw();

  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(0,1.,80.,1.);
  c.SaveAs("RatioEccSTARBES_11.5.png");

}