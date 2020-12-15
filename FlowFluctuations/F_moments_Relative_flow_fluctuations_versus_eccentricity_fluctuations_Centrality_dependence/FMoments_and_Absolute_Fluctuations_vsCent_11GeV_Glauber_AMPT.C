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

void FMoments_and_Absolute_Fluctuations_vsCent_11GeV_Glauber_AMPT()
{
  const int ncent = 9;
  const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  const double bin_centE[ncent] = {0};
  
  const int nmethod = 3; // 22, 24, 22-gapped
  const int ratioToMethod = 2; // v22-gapped
  const int marker[nmethod]={21,20,22};
  const float markerSize = 2.5;

  const float maxY = 1.;
  const float minY = 0.;
  const float minX = 0;
  const float maxX = 60;

  TFile *fiFlow = new TFile("AMPT15_11.5GeV.root","read");
  TFile *fiEcc = new TFile("Glauber_11.5GeV.root","read");

  TProfile *prEcc2vsCent = (TProfile *)fiEcc->Get("prEcc2vsCent");
  double stdDevScaled[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    stdDevScaled[ic] = StandardDeviationScaled(prEcc2vsCent, ic);
  }
  TGraphErrors *grStdDevScaled;



  grStdDevScaled = new TGraphErrors(ncent,bin_cent,stdDevScaled,bin_centE,bin_centE);
  grStdDevScaled -> SetMarkerStyle(kFullTriangleUp);
  grStdDevScaled -> SetMarkerSize(markerSize);
  grStdDevScaled -> SetMarkerColor(kGreen+3);
  grStdDevScaled -> SetLineColor(kGreen+3);
  grStdDevScaled -> SetLineWidth(markerSize+1);
  grStdDevScaled -> SetLineStyle(2);
  grStdDevScaled -> SetTitle("\\sigma_{\\varepsilon_{2}}/\\bar{\\varepsilon_{2}};centrality, %"); // /
  grStdDevScaled -> RemovePoint(0);
  // grStdDevScaled -> RemovePoint(5);
  // grStdDevScaled -> RemovePoint(6);
  // grStdDevScaled -> RemovePoint(7);
  // grStdDevScaled -> RemovePoint(8);
  
  // =====================================================================================================


  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hv22Gap[ncent];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)fiFlow->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)fiFlow->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)fiFlow->Get(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)fiFlow->Get(Form("hv22Gap_%i",icent));
  }

  double v2_STAR[nmethod][ncent] = {{0.0203, 0.02903, 0.04072, 0.0515, 0.05737, 0.05834, 0.05585, 0.05198, 0.05215},
                                    {1000.02, 0.02428, 0.03578, 0.04618, 0.05232, 0.05055, 0.04541, 1000.02, 1000},
                                    {0.0203, 0.02903, 0.04072, 0.0515, 0.05737, 0.05834, 0.05585, 0.05198, 0.05215}};

  double v2e_STAR[nmethod][ncent] = {{0.00012, 0.00011, 8e-05, 9e-05, 0.00012, 0.00017, 0.00029, 0.00058, 0.00114},
                                     {0.00353, 0.00164, 0.00067, 0.00063, 0.00096, 0.00241, 0.01105, 1000.05, 1000},
                                     {0.00012, 0.00011, 8e-05, 9e-05, 0.00012, 0.00017, 0.00029, 0.00058, 0.00114}};
  double ratioV2_STAR[nmethod][ncent], ratioV2E_STAR[nmethod][ncent];
  double FMomentsV2_STAR[nmethod][ncent], FMomentsV2E_STAR[nmethod][ncent];  
  
  for (int icent=0; icent<ncent; icent++)
  { // loop over centrality classes
    for (int imeth=0; imeth<nmethod; imeth++)
    {
      ratioV2_STAR[imeth][icent] = v2_STAR[imeth][icent] / v2_STAR[ratioToMethod][icent];
      ratioV2E_STAR[imeth][icent] = ratioV2_STAR[imeth][icent] * sqrt(v2e_STAR[imeth][icent]/v2_STAR[imeth][icent] + v2e_STAR[ratioToMethod][icent]/v2_STAR[ratioToMethod][icent]);
      FMomentsV2_STAR[imeth][icent] = sqrt((pow(v2_STAR[ratioToMethod][icent],2)-pow(v2_STAR[imeth][icent],2))/(pow(v2_STAR[ratioToMethod][icent],2)+pow(v2_STAR[imeth][icent],2)));    
      FMomentsV2E_STAR[imeth][icent] = 2*v2_STAR[ratioToMethod][icent]*v2_STAR[imeth][icent]
                              / (FMomentsV2_STAR[imeth][icent]*pow(pow(v2_STAR[ratioToMethod][icent],2)+pow(v2_STAR[imeth][icent],2),2))
                              * sqrt(pow(v2_STAR[imeth][icent],2)*pow(v2e_STAR[ratioToMethod][icent],2)+pow(v2_STAR[ratioToMethod][icent],2)*pow(v2e_STAR[imeth][icent],2));    
      // if (imeth==1) cout << FMomentsV2[imeth][icent] << ", "; // debug
      // if (imeth==1) cout << FMomentsV2E[imeth][icent] << ", "; // debug
    }    
  }

  TGraphErrors *grV2_STAR[nmethod], *grRatioV2_STAR[nmethod], *grFMomentsV2_STAR[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grV2_STAR[imeth] = new TGraphErrors(ncent,bin_cent,v2_STAR[imeth],bin_centE,v2e_STAR[imeth]);
    grV2_STAR[imeth] -> SetMarkerStyle(marker[imeth]);
    grV2_STAR[imeth] -> SetMarkerSize(markerSize);

    grRatioV2_STAR[imeth] = new TGraphErrors(ncent,bin_cent,ratioV2_STAR[imeth],bin_centE,ratioV2E_STAR[imeth]);
    grRatioV2_STAR[imeth] -> SetMarkerStyle(marker[imeth]);
    grRatioV2_STAR[imeth] -> SetMarkerSize(markerSize);

    grFMomentsV2_STAR[imeth] = new TGraphErrors(ncent,bin_cent,FMomentsV2_STAR[imeth],bin_centE,FMomentsV2E_STAR[imeth]);
    grFMomentsV2_STAR[imeth] -> SetMarkerStyle(kFullStar);
    grFMomentsV2_STAR[imeth] -> SetMarkerColor(kRed+2);
    grFMomentsV2_STAR[imeth] -> SetMarkerSize(markerSize+1);
    grFMomentsV2_STAR[imeth] -> SetTitle(";centrality, %;F");
    grFMomentsV2_STAR[imeth] -> RemovePoint(0);
  }

  // =====

  double v2_RF[nmethod][ncent],    v2e_RF[nmethod][ncent];
  double ratioV2[nmethod][ncent], ratioV2E[nmethod][ncent];
  double FMomentsV2[nmethod][ncent], FMomentsV2E[nmethod][ncent]; 
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(hv22[icent]);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    v2_RF[0][icent] = v22;
    v2e_RF[0][icent] = ev22;
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    v2_RF[1][icent] = v24;
    v2e_RF[1][icent] = ev24;
    // 2QC Gapped
    term cor2Gap = term(hv22Gap[icent]);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    v2_RF[2][icent] = v22Gap;
    v2e_RF[2][icent] = ev22Gap;
    for (int imeth=0; imeth<nmethod; imeth++){
      ratioV2[imeth][icent] = v2_RF[imeth][icent] / v2_RF[ratioToMethod][icent];
      ratioV2E[imeth][icent] = ratioV2[imeth][icent] * sqrt(v2e_RF[imeth][icent]/v2_RF[imeth][icent] + v2e_RF[ratioToMethod][icent]/v2_RF[ratioToMethod][icent]);
      FMomentsV2[imeth][icent] = sqrt((pow(v2_RF[ratioToMethod][icent],2)-pow(v2_RF[imeth][icent],2))/(pow(v2_RF[ratioToMethod][icent],2)+pow(v2_RF[imeth][icent],2)));    
      FMomentsV2E[imeth][icent] = 2*v2_RF[ratioToMethod][icent]*v2_RF[imeth][icent]
                              / (FMomentsV2[imeth][icent]*pow(pow(v2_RF[ratioToMethod][icent],2)+pow(v2_RF[imeth][icent],2),2))
                              * sqrt(pow(v2_RF[imeth][icent],2)*pow(v2e_RF[ratioToMethod][icent],2)+pow(v2_RF[ratioToMethod][icent],2)*pow(v2e_RF[imeth][icent],2));    
      // if (imeth==1) cout << FMomentsV2[imeth][icent] << ", "; // debug
      // if (imeth==1) cout << FMomentsV2E[imeth][icent] << ", "; // debug
    }
  }

  TGraphErrors *grV2[nmethod], *grRatioV2[nmethod], *grFMomentsV2[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grV2[imeth] = new TGraphErrors(ncent,bin_cent,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grV2[imeth] -> SetMarkerStyle(marker[imeth]);
    grV2[imeth] -> SetMarkerSize(markerSize);

    grRatioV2[imeth] = new TGraphErrors(ncent,bin_cent,ratioV2[imeth],bin_centE,ratioV2E[imeth]);
    grRatioV2[imeth] -> SetMarkerStyle(marker[imeth]);
    grRatioV2[imeth] -> SetMarkerSize(markerSize);

    grFMomentsV2[imeth] = new TGraphErrors(ncent,bin_cent,FMomentsV2[imeth],bin_centE,FMomentsV2E[imeth]);
    grFMomentsV2[imeth] -> SetMarkerStyle(marker[imeth]+4);
    grFMomentsV2[imeth] -> SetMarkerSize(markerSize);
    grFMomentsV2[imeth] -> SetMarkerColor(kBlue+3);
    grFMomentsV2[imeth] -> SetTitle(";centrality, %;F");
    grFMomentsV2[imeth] -> RemovePoint(0);
  }
  // =====================================================================================================
  TProfile *prEcc22 = (TProfile*)fiEcc->Get(Form("prEcc22vsCent"));
  TProfile *prEcc24 = (TProfile*)fiEcc->Get(Form("prEcc24vsCent"));
  TProfile *prCov24 = (TProfile*)fiEcc->Get(Form("prCov24vsCent"));
  TProfile *ecc2vsCent = (TProfile *) fiEcc -> Get("prEcc2vsCent");  
  
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
    ecc2_RF[0][icent] = ecc2vsCent -> GetBinContent(icent+1);
    ecc2e_RF[0][icent] = ecc2vsCent -> GetBinError(icent+1);
    for (int imeth=0; imeth<nmethod; imeth++){
      ratioEcc2[imeth][icent] = ecc2_RF[imeth][icent] / ecc2_RF[ratioToMethod][icent];
      ratioEcc2E[imeth][icent] = ratioEcc2[imeth][icent] * sqrt(ecc2e_RF[imeth][icent]/ecc2_RF[imeth][icent] + ecc2e_RF[ratioToMethod][icent]/ecc2_RF[ratioToMethod][icent]);
      FMomentsEcc2[imeth][icent] = sqrt((pow(ecc2_RF[ratioToMethod][icent],2)-pow(ecc2_RF[imeth][icent],2))/(pow(ecc2_RF[ratioToMethod][icent],2)+pow(ecc2_RF[imeth][icent],2)));    
      FMomentsEcc2E[imeth][icent] = 2*ecc2_RF[ratioToMethod][icent]*ecc2_RF[imeth][icent]
                                  / (FMomentsEcc2[imeth][icent]*pow(pow(ecc2_RF[ratioToMethod][icent],2)+pow(ecc2_RF[imeth][icent],2),2))
                                  * sqrt(pow(ecc2_RF[imeth][icent],2)*pow(ecc2e_RF[ratioToMethod][icent],2)+pow(ecc2_RF[ratioToMethod][icent],2)*pow(ecc2e_RF[imeth][icent],2));    
      if (imeth==1) cout << FMomentsEcc2[imeth][icent] << endl; // debug
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
  grFMomentsV2[1] -> SetTitle("R_{v_{2}};centrality, %;F\\");
  grFMomentsV2_STAR[1] -> SetTitle("R_{v_{2}};centrality, %;F\\");
  TCanvas c("c","c",1440,1080);

  grFMomentsEcc2[1]->GetXaxis()->SetRangeUser(minX,maxX);
  grFMomentsEcc2[1]->SetMinimum(minY);
  grFMomentsEcc2[1]->SetMaximum(maxY);
  grFMomentsEcc2[1] -> Draw("AP");
  grFMomentsV2[1] -> Draw("P");
  grFMomentsV2_STAR[1] -> Draw("P");
  grStdDevScaled->Draw("L");


  TLegend *l = new TLegend(0.2,0.65,0.4,0.85);
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->SetHeader("Au+Au at #sqrt{s_{NN}} = 11.5 GeV");

  l->AddEntry(grStdDevScaled,Form("%s\\ (Glauber)",grStdDevScaled->GetTitle()),"l");
  l->AddEntry(grFMomentsEcc2[1],Form("%s\\ (Glauber)",grFMomentsEcc2[1]->GetTitle()),"p");
  
  l->AddEntry(grFMomentsV2[1],Form("%s\\ (AMPT)",grFMomentsV2[1]->GetTitle()),"p");
  l->AddEntry(grFMomentsV2_STAR[1],Form("%s\\ (STAR)",grFMomentsV2[1]->GetTitle()),"p");
  
  l->Draw();
  TMathText tex;
  tex.DrawMathText(30.,0.8,"R_{v_{2}}=\\sqrt{v_{2}\\{2\\}^{2}-v_{2}\\{4\\}^{2} \\over v_{2}\\{2\\}^{2}+v_{2}\\{4\\}^{2}} \\approx {\\sigma_{v_{2}}\\over\\bar{v_{2}}}");
  grFMomentsEcc2[1]->SetTitle("");
  c.SaveAs("FMoments_and_Absolute_Fluctuations_vsCent_11GeV_Glauber_AMPT.png");


}