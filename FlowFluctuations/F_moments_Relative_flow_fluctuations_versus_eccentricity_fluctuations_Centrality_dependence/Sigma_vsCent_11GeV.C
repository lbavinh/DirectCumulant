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

void Sigma_vsCent_11GeV()
{
  const int ncent = 9;
  const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  const double bin_centE[ncent] = {0};
  
  const int nmethod = 3; // 22, 24, 22-gapped
  const int ratioToMethod = 2; // v22-gapped
  const int marker[nmethod]={21,20,22};
  const float markerSize = 1.2;
  const float scaleSigma = 0.09;
  const float maxY = 0.05;
  const float minY = 0.;
  const float minX = 0;
  const float maxX = 60;

  TFile *fiFlow = new TFile("UrQMD_11.5GeV.root","read");
  TFile *fiEcc = new TFile("Glauber_11.5GeV.root","read");


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
  double SigmaV2_STAR[nmethod][ncent], SigmaV2E_STAR[nmethod][ncent];

  for (int icent=0; icent<ncent; icent++)
  { // loop over centrality classes
    for (int imeth=0; imeth<nmethod; imeth++)
    {
      ratioV2_STAR[imeth][icent] = v2_STAR[imeth][icent] / v2_STAR[ratioToMethod][icent];
      ratioV2E_STAR[imeth][icent] = ratioV2_STAR[imeth][icent] * sqrt(v2e_STAR[imeth][icent]/v2_STAR[imeth][icent] + v2e_STAR[ratioToMethod][icent]/v2_STAR[ratioToMethod][icent]);
      SigmaV2_STAR[imeth][icent] = sqrt((pow(v2_STAR[ratioToMethod][icent],2)-pow(v2_STAR[imeth][icent],2))/2.);    
      SigmaV2E_STAR[imeth][icent] = 1.
                                  / (SigmaV2_STAR[imeth][icent]*2)
                                  * sqrt(pow(v2_STAR[ratioToMethod][icent],2)*pow(v2e_STAR[ratioToMethod][icent],2)+pow(v2_STAR[imeth][icent],2)*pow(v2e_STAR[imeth][icent],2));    
      if (imeth==1) cout << SigmaV2_STAR[imeth][icent] << ", "; // debug
      // if (imeth==1) cout << SigmaV2E_STAR[imeth][icent] << ", "; // debug
    }    
  }

  TGraphErrors *grV2_STAR[nmethod], *grRatioV2_STAR[nmethod], *grSigmaV2_STAR[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grV2_STAR[imeth] = new TGraphErrors(ncent,bin_cent,v2_STAR[imeth],bin_centE,v2e_STAR[imeth]);
    grV2_STAR[imeth] -> SetMarkerStyle(marker[imeth]);
    grV2_STAR[imeth] -> SetMarkerSize(markerSize);

    grRatioV2_STAR[imeth] = new TGraphErrors(ncent,bin_cent,ratioV2_STAR[imeth],bin_centE,ratioV2E_STAR[imeth]);
    grRatioV2_STAR[imeth] -> SetMarkerStyle(marker[imeth]);
    grRatioV2_STAR[imeth] -> SetMarkerSize(markerSize);

    grSigmaV2_STAR[imeth] = new TGraphErrors(ncent,bin_cent,SigmaV2_STAR[imeth],bin_centE,SigmaV2E_STAR[imeth]);
    grSigmaV2_STAR[imeth] -> SetMarkerStyle(kFullStar);
    grSigmaV2_STAR[imeth] -> SetMarkerColor(kRed+2);
    grSigmaV2_STAR[imeth] -> SetMarkerSize(markerSize+1);
    grSigmaV2_STAR[imeth] -> SetTitle(";centrality, %");
    grSigmaV2_STAR[imeth] -> RemovePoint(0);
  }

  double v2_RF[nmethod][ncent],    v2e_RF[nmethod][ncent];
  double ratioV2[nmethod][ncent], ratioV2E[nmethod][ncent];
  double SigmaV2[nmethod][ncent], SigmaV2E[nmethod][ncent];
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
      SigmaV2[imeth][icent] = sqrt((pow(v2_RF[ratioToMethod][icent],2)-pow(v2_RF[imeth][icent],2))/2.);    
      SigmaV2E[imeth][icent] = 1./ (SigmaV2[imeth][icent]*2.)
                             * sqrt(pow(v2_RF[ratioToMethod][icent],2)*pow(v2e_RF[ratioToMethod][icent],2)+pow(v2_RF[imeth][icent],2)*pow(v2e_RF[imeth][icent],2));    
      if (imeth==1) cout << SigmaV2[imeth][icent] << ", "; // debug
      // if (imeth==1) cout << SigmaV2E[imeth][icent] << ", "; // debug
    }
  }

  TGraphErrors *grV2[nmethod], *grRatioV2[nmethod], *grSigmaV2[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grV2[imeth] = new TGraphErrors(ncent,bin_cent,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grV2[imeth] -> SetMarkerStyle(marker[imeth]);
    grV2[imeth] -> SetMarkerSize(markerSize);

    grRatioV2[imeth] = new TGraphErrors(ncent,bin_cent,ratioV2[imeth],bin_centE,ratioV2E[imeth]);
    grRatioV2[imeth] -> SetMarkerStyle(marker[imeth]);
    grRatioV2[imeth] -> SetMarkerSize(markerSize);

    grSigmaV2[imeth] = new TGraphErrors(ncent,bin_cent,SigmaV2[imeth],bin_centE,SigmaV2E[imeth]);
    grSigmaV2[imeth] -> SetMarkerStyle(marker[imeth]+4);
    grSigmaV2[imeth] -> SetMarkerSize(markerSize);
    grSigmaV2[imeth] -> SetTitle(";centrality, %;F");
    grSigmaV2[imeth] -> RemovePoint(0);
  }
  // =====================================================================================================
  TProfile *prEcc22 = (TProfile*)fiEcc->Get(Form("prEcc22vsCent"));
  TProfile *prEcc24 = (TProfile*)fiEcc->Get(Form("prEcc24vsCent"));
  TProfile *prCov24 = (TProfile*)fiEcc->Get(Form("prCov24vsCent"));
  TProfile *ecc2vsCent = (TProfile *) fiEcc -> Get("prEcc2vsCent");  
  
  double ecc2_RF[nmethod][ncent],    ecc2e_RF[nmethod][ncent];
  double ratioEcc2[nmethod][ncent], ratioEcc2E[nmethod][ncent];
  double SigmaEcc2[nmethod][ncent], SigmaEcc2E[nmethod][ncent]; 
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
      SigmaEcc2[imeth][icent] = scaleSigma*sqrt((pow(ecc2_RF[ratioToMethod][icent],2)-pow(ecc2_RF[imeth][icent],2))/2.);    
      SigmaEcc2E[imeth][icent] = scaleSigma*1./ (SigmaEcc2[imeth][icent]*2.)
                               * sqrt(pow(ecc2_RF[ratioToMethod][icent],2)*pow(ecc2e_RF[ratioToMethod][icent],2)+pow(ecc2_RF[imeth][icent],2)*pow(ecc2e_RF[imeth][icent],2));    
      // if (imeth==1) cout << SigmaEcc2[imeth][icent] << endl; // debug
      // if (imeth==1) cout << SigmaEcc2E[imeth][icent] << ", "; // debug
    }
  }

  TGraphErrors *grEcc2[nmethod], *grRatioEcc2[nmethod], *grSigmaEcc2[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grEcc2[imeth] = new TGraphErrors(ncent,bin_cent,ecc2_RF[imeth],bin_centE,ecc2e_RF[imeth]);
    grEcc2[imeth] -> SetMarkerStyle(marker[imeth]);
    grEcc2[imeth] -> SetMarkerSize(markerSize);

    grRatioEcc2[imeth] = new TGraphErrors(ncent,bin_cent,ratioEcc2[imeth],bin_centE,ratioEcc2E[imeth]);
    grRatioEcc2[imeth] -> SetMarkerStyle(marker[imeth]);
    grRatioEcc2[imeth] -> SetMarkerSize(markerSize);

    grSigmaEcc2[imeth] = new TGraphErrors(ncent,bin_cent,SigmaEcc2[imeth],bin_centE,SigmaEcc2E[imeth]);
    grSigmaEcc2[imeth] -> SetMarkerStyle(marker[imeth]);
    grSigmaEcc2[imeth] -> SetMarkerSize(markerSize);
    grSigmaEcc2[imeth] -> SetTitle(";centrality, %;F");
    grSigmaEcc2[imeth] -> RemovePoint(0);
  }
  // ============================================================================================================================  
  grSigmaEcc2[1] -> SetTitle(Form("\\sigma(\\varepsilon_{2})\\times%1.2f;centrality, %%;\\sigma(v_2)~or~\\sigma(\\varepsilon_2)",scaleSigma));
  grSigmaV2[1] -> SetTitle("\\sigma(v_{2});centrality, %;\\sigma(v_2) or \\sigma(\\varepsilon_2)");
  grSigmaV2_STAR[1] -> SetTitle("\\sigma(v_{2});centrality, %");
  TCanvas c;

  grSigmaEcc2[1]->GetXaxis()->SetRangeUser(minX,maxX);
  grSigmaEcc2[1]->SetMinimum(minY);
  grSigmaEcc2[1]->SetMaximum(maxY);
  grSigmaEcc2[1] -> Draw("AP");
  grSigmaV2[1] -> Draw("P");
  grSigmaV2_STAR[1] -> Draw("P");

  TLegend *l = new TLegend(0.2,0.7,0.4,0.85);
  l->SetHeader("Au+Au at #sqrt{s_{NN}} = 11.5 GeV");
  l->SetBorderSize(0);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.04);
  l->AddEntry(grSigmaEcc2[1],Form("%s\\ (Glauber)",grSigmaEcc2[1]->GetTitle()),"p");
  l->AddEntry(grSigmaV2[1],Form("%s\\ (UrQMD)",grSigmaV2[1]->GetTitle()),"p");
  l->AddEntry(grSigmaV2_STAR[1],Form("%s\\ (STAR)",grSigmaV2_STAR[1]->GetTitle()),"p");

  l->Draw();
  TMathText tex;
  tex.DrawMathText(5.,0.03,"\\sigma(v_{2})=\\sqrt{v_{2}\\{2\\}^{2}-v_{2}\\{4\\}^{2} \\over 2}");
  tex.DrawMathText(35.,0.03,"\\sigma(\\varepsilon_{2})=\\sqrt{\\varepsilon_{2}\\{2\\}^{2}-\\varepsilon_{2}\\{4\\}^{2} \\over 2}");
  grSigmaEcc2[1]->SetTitle("");
  c.SaveAs("Sigma_vsCent_11GeV.png");


}