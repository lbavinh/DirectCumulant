double Covariance(TProfile *const &hcovXY, TProfile *const &hX, TProfile *const &hY, Int_t binXY=0, Int_t binX=0, Int_t binY=0){

  double mSumWXY = hcovXY->GetBinEntries(binXY+1);
  double sumWX = hX->GetBinEntries(binX+1);
  double sumWY = hY->GetBinEntries(binY+1);

  double meanXY = hcovXY -> GetBinContent(binXY+1);
  double meanX = hX -> GetBinContent(binX+1);
  double meanY = hY -> GetBinContent(binY+1);
  double mVal = (meanXY-meanX*meanY)/(sumWX*sumWY/mSumWXY-1.); // Cov(x,y)/(sumWX*sumWY/sumWXY)
  return mVal;
}

struct term{ // structure for "Mean squared error of MEAN" calculation, using unbiased estimator for the root of variance
  term(){
    mVal = 0;
    mMSE = 0;
  }
  term(TProfile *const &pr, Int_t bin=0){

    double Neff = pr -> GetBinEffectiveEntries(bin+1);
    mVal = pr -> GetBinContent(bin+1);
    pr -> SetErrorOption("s");
    double stdevW = pr -> GetBinError(bin+1);
    double S2 = stdevW*stdevW/(1-1./Neff);
    mMSE = S2/Neff;
  };
 public: 
  double mVal; // weithted mean value
  double mMSE; // Mean squared error of mean, https://en.wikipedia.org/wiki/Mean_squared_error

};

double StandardDeviation(TProfile *const &pr, Int_t bin = 0)
{
  double StdDev;
  pr->SetErrorOption("s");
  return StdDev = pr->GetBinError(bin + 1);
}

double Mean(TProfile *const &pr, Int_t bin = 0)
{
  double mean = pr->GetBinContent(bin + 1);
  return mean;
}

double StandardDeviationScaled(TProfile *const &pr, Int_t bin = 0)
{
  double stdDevScaled = (double)StandardDeviation(pr, bin) / Mean(pr, bin) ; //
  return stdDevScaled;
}

void plotRelativeFluctuation_vs_Npart()
{
  const int ncent = 7;
  const double bin_cent[ncent] = {25,75,125,175,225,275,325};
  const double bin_centE[ncent] = {0};

  const int nmethod = 3; // 22, 24, 22-gapped
  const int ratioToMethod = 2; // v22-gapped
  const int marker[nmethod]={21,20,22};
  const float markerSize = 2.5;

  const float maxY = 1.;
  const float minY = 0.;
  const float minX = 0.;
  const float maxX = 350.;


  TFile *fiEcc = new TFile("Glauber_200GeV.root","read");


  TProfile *prEcc22 = (TProfile*)fiEcc->Get(Form("prEcc22vsNpart"));
  TProfile *prEcc24 = (TProfile*)fiEcc->Get(Form("prEcc24vsNpart"));
  TProfile *prCov24 = (TProfile*)fiEcc->Get(Form("prCov24vsNpart"));
  TProfile *prEcc2  = (TProfile*)fiEcc->Get("prEcc2vsNpart");
  if (!prEcc22) {cout << "prEcc22=NULL" << endl; return;}
  if (!prEcc24) {cout << "prEcc24=NULL" << endl; return;}
  if (!prCov24) {cout << "prCov24=NULL" << endl; return;}
  if (!prEcc2) {cout << "prEcc2=NULL" << endl; return;}
  double ecc2_RF[nmethod][ncent],    ecc2e_RF[nmethod][ncent];
  double ratioEcc2[nmethod][ncent], ratioEcc2E[nmethod][ncent];
  double FMomentsEcc2[nmethod][ncent], FMomentsEcc2E[nmethod][ncent]; 
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // Ecc22
    term cor2 = term(prEcc22,icent);
    double ecc22 = sqrt(cor2.mVal);
    double eecc22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    ecc2_RF[2][icent] = ecc22;
    ecc2e_RF[2][icent] = eecc22;
    // Ecc24
    term cor4 = term(prEcc24,icent);
    double cov24 = Covariance(prCov24,prEcc22,prEcc24,icent,icent,icent);
    double ecc24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double eecc24 = sqrt( 1./pow(ecc24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    ecc2_RF[1][icent] = ecc24;
    ecc2e_RF[1][icent] = eecc24;
    // Ecc2
    ecc2_RF[0][icent] = prEcc2 -> GetBinContent(icent+1);
    ecc2e_RF[0][icent] = prEcc2 -> GetBinError(icent+1);
    for (int imeth=0; imeth<nmethod; imeth++){
      ratioEcc2[imeth][icent] = ecc2_RF[imeth][icent] / ecc2_RF[ratioToMethod][icent];
      ratioEcc2E[imeth][icent] = ratioEcc2[imeth][icent] * sqrt(ecc2e_RF[imeth][icent]/ecc2_RF[imeth][icent] + ecc2e_RF[ratioToMethod][icent]/ecc2_RF[ratioToMethod][icent]);
      FMomentsEcc2[imeth][icent] = sqrt((pow(ecc2_RF[ratioToMethod][icent],2)-pow(ecc2_RF[imeth][icent],2))/(pow(ecc2_RF[ratioToMethod][icent],2)+pow(ecc2_RF[imeth][icent],2)));    
      FMomentsEcc2E[imeth][icent] = 2*ecc2_RF[ratioToMethod][icent]*ecc2_RF[imeth][icent]
                                  / (FMomentsEcc2[imeth][icent]*pow(pow(ecc2_RF[ratioToMethod][icent],2)+pow(ecc2_RF[imeth][icent],2),2))
                                  * sqrt(pow(ecc2_RF[imeth][icent],2)*pow(ecc2e_RF[ratioToMethod][icent],2)+pow(ecc2_RF[ratioToMethod][icent],2)*pow(ecc2e_RF[imeth][icent],2));    
      // if (imeth==1) cout << FMomentsEcc2[imeth][icent] << endl; // debug
      // if (imeth==1) cout << FMomentsEcc2E[imeth][icent] << ", "; // debug
    }
  }
  TGraphErrors *grEcc2[nmethod], *grRatioEcc2[nmethod], *grFMomentsEcc2[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grEcc2[imeth] = new TGraphErrors(ncent,bin_cent,ecc2_RF[imeth],bin_centE,ecc2e_RF[imeth]);
    grEcc2[imeth] -> SetMarkerStyle(marker[imeth]);
    grEcc2[imeth] -> SetMarkerSize(markerSize);

    grRatioEcc2[imeth] = new TGraphErrors(ncent,bin_cent,ratioEcc2[imeth],bin_centE,ratioEcc2E[imeth]);
    grRatioEcc2[imeth] -> SetMarkerStyle(marker[imeth]);
    grRatioEcc2[imeth] -> SetMarkerSize(markerSize);

    grFMomentsEcc2[imeth] = new TGraphErrors(ncent,bin_cent,FMomentsEcc2[imeth],bin_centE,FMomentsEcc2E[imeth]);
    grFMomentsEcc2[imeth] -> SetMarkerStyle(marker[imeth]);
    grFMomentsEcc2[imeth] -> SetMarkerSize(markerSize);
    grFMomentsEcc2[imeth] -> SetTitle(";centrality, %;F");
    grFMomentsEcc2[imeth] -> RemovePoint(0);
  }
  // ============================================================================================================================  
  grFMomentsEcc2[1] -> SetTitle("R_{\\varepsilon_{2}};centrality, %;\\sigma_{v_{2}}/{\\bar{v_{2}}}~or~\\sigma_{\\varepsilon_{2}}/\\bar{\\varepsilon_{2}}");
  // grFMomentsV2[1] -> SetTitle("R_{v_{2}};centrality, %;F\\");
  // grFMomentsV2_STAR[1] -> SetTitle("R_{v_{2}};centrality, %;F\\");
  TCanvas c("c","c",1440,1080);

  grFMomentsEcc2[1]->GetXaxis()->SetRangeUser(minX,maxX);
  grFMomentsEcc2[1]->SetMinimum(minY);
  grFMomentsEcc2[1]->SetMaximum(maxY);
  grFMomentsEcc2[1]->Draw("AP");
  // grFMomentsV2[1] -> Draw("P");
  // grFMomentsV2_STAR[1] -> Draw("P");
  // grStdDevScaled->Draw("L");


  TLegend *l = new TLegend(0.2,0.65,0.4,0.85);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->SetHeader("Au+Au at #sqrt{s_{NN}} = 200 GeV");

  // l->AddEntry(grStdDevScaled,Form("%s\\ (Glauber)",grStdDevScaled->GetTitle()),"l");
  l->AddEntry(grFMomentsEcc2[1],Form("%s\\ (Glauber)",grFMomentsEcc2[1]->GetTitle()),"p");
  
  // l->AddEntry(grFMomentsV2[1],Form("%s\\ (UrQMD)",grFMomentsV2[1]->GetTitle()),"p");
  // l->AddEntry(grFMomentsV2_STAR[1],Form("%s\\ (STAR)",grFMomentsV2[1]->GetTitle()),"p");
  
  l->Draw();
  TMathText tex;
  tex.DrawMathText(200,0.8,"R_{v_{2}}=\\sqrt{v_{2}\\{2\\}^{2}-v_{2}\\{4\\}^{2} \\over v_{2}\\{2\\}^{2}+v_{2}\\{4\\}^{2}} \\approx {\\sigma_{v_{2}}\\over\\bar{v_{2}}}");
  grFMomentsEcc2[1]->SetTitle("");
  c.SaveAs("plotRelativeFluctuation_vs_Npart.png");


}