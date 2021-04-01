#include "DrawTGraphImp.C"
struct term{
  term(){
    mVal = 0;
    mSumW = 0;
    mNeff = 0;
    mS2 = 0;
    mMSE = 0;
  }
  term(TProfile *const &pr){
    double stats[6];
    pr->GetStats(stats);
    mSumW = stats[0];
    double sumW2 = stats[1];
    
    mNeff = pr -> GetBinEffectiveEntries(1); // Number of effective entries
    // mNeff = mSumW*mSumW/sumW2;
    mVal = pr -> GetBinContent(1);
    pr -> SetErrorOption("s");
    double stdevW = pr -> GetBinError(1);
    mS2 = stdevW*stdevW/(1-sumW2/mSumW/mSumW); // formula (C.3)
    // mS2 = pr -> GetBinError(1);
    mMSE = mS2/mNeff;
  };
 public: 
  double mVal; // weithted mean value
  double mSumW; // sum of weights
  double mNeff; // Number of effective entries
  double mS2; // Unbiased estimator for the root of variance, (C.3) in Ante's dissertation
  double mMSE; // Mean squared error of mean, https://en.wikipedia.org/wiki/Mean_squared_error

};

double Covariance(TProfile *const &hcovXY, TProfile *const &hX, TProfile *const &hY){
  double statsXY[6], statsX[6], statsY[6];
  double meanXY, meanX, meanY, sumWX, sumWY;
  hcovXY -> GetStats(statsXY);
  hX -> GetStats(statsX);
  hY -> GetStats(statsY);
  
  double mSumWXY = statsXY[0];
  sumWX = statsX[0];
  sumWY = statsY[0];

  meanXY = hcovXY -> GetBinContent(1);
  meanX = hX -> GetBinContent(1);
  meanY = hY -> GetBinContent(1);
  // mVal = (meanXY-meanX*meanY)/(1-mSumW/sumWX/sumWY); // Cov(x,y) // formula (C.12)
  double mVal = (meanXY-meanX*meanY)/(sumWX*sumWY/mSumWXY-1.); // Cov(x,y)/(sumWX*sumWY/sumWXY)
  return mVal;
}

TGraphErrors** PlotV2HighOrderQCumulant(TString inputFileName){
  // TString energy="7.7GeV";
  // TFile *fi = new TFile(Form("../UrQMD_%s_GenericFramework.root",energy.Data()),"read");
  TFile *fi = new TFile(inputFileName.Data(),"read");
  // TFile *fo = new TFile(Form("v2_AMPT_%s_GenericFramework.root",energy.Data()),"recreate");
  const int ncent = 9;
  const double centBinMin = 0.;
  const double centBinMax = 62.;
  double binCent[]={2.5,7.5,15,25,35,45,55,65,75};
  double eBinCent[ncent];
  const double v2Min = -0.005;
  const double v2Max = 0.1;
  const double v2RatioMin = 0.78;
  const double v2RatioMax = 1.05;
  const float pt_min_cut = 0.2;
  const float pt_max_cut = 3.;
  const int maxCorrelator = 8; // We will not go beyond 8-p correlations
  const int nMethod = 4; // v22,v24,v26,v28
  const int ratioToType = 0;
  TString grName[]={"v_{2}{2}","v_{2}{4}","v_{2}{6}","v_{2}{8}"};
  TProfile *recursion[maxCorrelator][ncent];    // Correlations calculated from Q-vector components using recursive algorithm 
  for(int c=0;c<maxCorrelator;c++){
    for(int icent=0;icent<ncent;icent++){
      recursion[c][icent] = (TProfile*)fi->Get(Form("recursion_%i_%i",c,icent));
    }
  }
  TProfile *pCovariance[6][ncent];
  for (int i=0;i<6;i++){
    for (int c=0;c<ncent;c++){
      pCovariance[i][c] = (TProfile*)fi->Get(Form("pCovariance_%i_%i",i,c));
    }
  }
  double vV22[ncent], vV24[ncent], vV26[ncent], vV28[ncent];
  double veV22[ncent], veV24[ncent], veV26[ncent], veV28[ncent];
  std::vector<double> vecV22, vecEV22;
  for (int icent=0;icent<ncent;icent++){
    // 2QC
    term cor2 = term(recursion[0][icent]);
    double V22  = sqrt(cor2.mVal);
    double eV22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(recursion[2][icent]);
    double cov24 = Covariance(pCovariance[0][icent],recursion[0][icent],recursion[2][icent]);
    double V24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double eV24= sqrt( 1./pow(V24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) ;
    // 6QC
    term cor6 = term(recursion[4][icent]);
    double cov26 = Covariance(pCovariance[1][icent],recursion[0][icent],recursion[4][icent]);
    double cov46 = Covariance(pCovariance[3][icent],recursion[2][icent],recursion[4][icent]);
    double V26 = pow(2,-1./3.)*pow(cor6.mVal-9*cor2.mVal*cor4.mVal+12*pow(cor2.mVal,3),1./6.);
    double eV26 = sqrt(1./(2*pow(2,4)*pow(V26,10))*(9./2.*pow(4*pow(cor2.mVal,2)-cor4.mVal,2)*cor2.mMSE
                     + 9./2.*pow(cor2.mVal,2)*cor4.mMSE+1./18.*cor6.mMSE
                     - 9*cor2.mVal*(4*pow(cor2.mVal,2)-cor4.mVal)*cov24
                     +(4*pow(cor2.mVal,2)-cor4.mVal)*cov26
                     - cor2.mVal*cov46));
    // 8QC
    term cor8 = term(recursion[6][icent]);
    double cov28 = Covariance(pCovariance[2][icent],recursion[0][icent],recursion[6][icent]);
    double cov48 = Covariance(pCovariance[4][icent],recursion[2][icent],recursion[6][icent]);
    double cov68 = Covariance(pCovariance[5][icent],recursion[4][icent],recursion[6][icent]);
    double V28 = pow(33,-1./8.)*pow(-cor8.mVal+16*cor6.mVal*cor2.mVal+18*pow(cor4.mVal,2)-144*cor4.mVal*pow(cor2.mVal,2)+144*pow(cor2.mVal,4),1./8.);
    double eV28 = sqrt(4.*pow(33,-2)/pow(V28,14)
                *(pow(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal,2)*cor2.mMSE
                + 81./16.*pow(4*pow(cor2.mVal,2)-cor4.mVal,2)*cor4.mMSE
                + pow(cor2.mVal,2)*cor6.mMSE+1./256.*cor8.mMSE
                - 9./2.*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)*(4*pow(cor2.mVal,2)-cor4.mVal)
                * cov24
                + 2*cor2.mVal*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)
                * cov26
                - 1./8.*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)*cov28
                - 9./2.*cor2.mVal*(4*pow(cor2.mVal,2)-cor4.mVal)*cov46
                + 9./32.*(4*pow(cor2.mVal,2)-cor4.mVal)*cov48
                - 1./8.*cor2.mVal*cov68));
  

  vV22[icent] = V22; vV24[icent] = V24; vV26[icent] = V26; vV28[icent] = V28;
  veV22[icent] = eV22; veV24[icent] = eV24; veV26[icent] = eV26; veV28[icent] = eV28;

  eBinCent[icent] = 0.;
  }
  // for (int icent=0;icent<ncent;icent++){
  //   cout << vV22[icent] <<" "<< vV24[icent] <<" "<< vV26[icent] <<" "<< vV28[icent] << endl;
  // }
  TGraphErrors *gr[nMethod];
  gr[0] = new TGraphErrors(ncent,binCent,vV22,eBinCent,veV22);
  gr[1] = new TGraphErrors(ncent,binCent,vV24,eBinCent,veV24);
  gr[2] = new TGraphErrors(ncent,binCent,vV26,eBinCent,veV26);
  gr[3] = new TGraphErrors(ncent,binCent,vV28,eBinCent,veV28);
  for (int m=0;m<nMethod;m++){
    gr[m]->SetMarkerStyle(20+m);
    // gr[m]->SetMarkerSize(1.5);
  }
  // fo->cd();
  for (int m=0;m<nMethod;m++){
    gr[m]->SetTitle(grName[m].Data());
  //   gr[m]->Write(Form("gr_%i",m));
  }


  // ratio graph
  TGraphErrors *grRatio[nMethod];
  Double_t *vx_gr[nMethod], *vy_gr[nMethod], *ex_gr[nMethod], *ey_gr[nMethod];
  Int_t nbins[nMethod];

    for (int m=0;m<nMethod;m++){
      // Read points
      vx_gr[m]=(Double_t*)gr[m]->GetX();
      vy_gr[m]=(Double_t*)gr[m]->GetY();

      // Read errors
      ex_gr[m]=(Double_t*)gr[m]->GetEX();
      ey_gr[m]=(Double_t*)gr[m]->GetEY();

      nbins[m]=(Int_t) gr[m]->GetN();
    }

  for (int m=0;m<nMethod;m++){

    std::vector<Double_t> vRatioToUniformAcceptance, vRatioToUniformAcceptanceErr;
    for (int i=0;i<nbins[ratioToType];i++){
      Double_t ratio = vy_gr[m][i]/vy_gr[ratioToType][i];
      Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ratioToType][i]/vy_gr[ratioToType][i],2)+TMath::Power(ey_gr[m][i]/vy_gr[m][i],2)));
      vRatioToUniformAcceptance.push_back(ratio);
      vRatioToUniformAcceptanceErr.push_back(ratioErr);
    }
    grRatio[m] = new TGraphErrors(nbins[ratioToType],vx_gr[ratioToType],&vRatioToUniformAcceptance[0],ex_gr[ratioToType],&vRatioToUniformAcceptanceErr[0]);
    grRatio[m] -> SetMarkerStyle(gr[m]->GetMarkerStyle());
    grRatio[m] -> SetMarkerColor(gr[m]->GetMarkerStyle());
    grRatio[m] -> SetLineColor(gr[m]->GetMarkerStyle());
    vRatioToUniformAcceptance.clear();
    vRatioToUniformAcceptanceErr.clear();
  }
  TCanvas *cV2CentRF;
  gr[1]->SetMarkerStyle(22);
  gr[2]->SetMarkerStyle(25);
  gr[3]->SetMarkerStyle(20);
  for (int imeth=1;imeth<nMethod;imeth++){
    gr[imeth]->RemovePoint(0);
    gr[imeth]->SetMarkerSize(1.5);
  }
  vector<TGraphErrors*> vgrv2cent_chargedHardons;
  vgrv2cent_chargedHardons.push_back(gr[1]);

  for (int imeth=2;imeth<nMethod;imeth++){
    vgrv2cent_chargedHardons.push_back(gr[imeth]);
    
  }
  // cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",0.89, 1.11, 0, 60, -0.01, 0.1,
  //                                   0.18,0.63,0.45,0.889,
  //                                   "AMPT SM, #sigma_{p}=0.8mb at #sqrt{s_{NN}}=7.7 GeV", Form("Ch. hadrons, %1.1f<p_{T}<%1.1f GeV/c",0.2,3.0),true,grName[1]);
  // cV2CentRF -> SetName("Reference flow");
  // cV2CentRF -> SaveAs(Form("IntegratedFlow_HighQC_hadron.png"));
  

  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",0.89, 1.11, 0, 60, -0.01, 0.1,
                                    0.18,0.63,0.45,0.889,
                                    "UrQMD at #sqrt{s_{NN}}=7.7 GeV", Form("Ch. hadrons, %1.1f<p_{T}<%1.1f GeV/c",0.2,3.0),true,grName[1]);
  cV2CentRF -> SetName("Reference flow");
  cV2CentRF -> SaveAs(Form("IntegratedFlow_HighQC_hadron_UrQMD.png"));
  
  // TCanvas *c = new TCanvas("c","",200,10,800,600);

  // TCanvas *c = new TCanvas("c","",200,10,800,600);
  // gStyle->SetOptStat(0);
  // gStyle->SetPalette(kDarkRainBow);
  // gStyle->SetErrorX(0);
  // gStyle->SetPadTickX(1);
  // gStyle->SetPadTickY(1);

  // c->SetLeftMargin(0.12);
  // c->Divide(1,2,0,0);
  // c->cd(1);
  // TH2F *h = new TH2F("h",Form("Au+Au at #sqrt{s_{NN}}=%s, AMPT, #sigma_{p}=1.5mb, ch. hadrons, %1.1f<p_{T}<%1.1f GeV/c;centrality (%%);v_{2}", energy.Data(), pt_min_cut,pt_max_cut),ncent,centBinMin,centBinMax,1,v2Min,v2Max);
  // h->GetXaxis()->SetNdivisions(504);
  // h->GetYaxis()->SetNdivisions(504);
  // h->GetYaxis()->SetTitleOffset(0.8);
  // h->GetYaxis()->SetLabelSize(0.05);
  // h->GetYaxis()->SetTitleSize(0.05);
  // h->Draw();
  // for (int m=0;m<nMethod;m++){
  //   gr[m]->Draw("P PLC PMC");
  // }
  // TLegend *leg = new TLegend(0.8,0.1,0.9,0.5);
  // leg->SetBorderSize(0);
  // leg->SetTextSize(0.05);
  // leg->SetTextFont(42);
  // for (int m=0;m<nMethod;m++){
  //   leg->AddEntry(gr[m],gr[m]->GetTitle(),"p");
  // }
  // leg->Draw();
  // c->cd(2);
  // TH2F *hRatio = new TH2F("hRatio",Form(";centrality (%%);Ratio to v_{2}{2}"),ncent,centBinMin,centBinMax,1,v2RatioMin,v2RatioMax);
  // hRatio->GetXaxis()->SetNdivisions(504);
  // hRatio->GetYaxis()->SetNdivisions(504);
  // hRatio->GetYaxis()->SetTitleOffset(0.8);
  // hRatio->GetYaxis()->SetLabelSize(0.05);
  // hRatio->GetYaxis()->SetTitleSize(0.05);
  // hRatio->GetXaxis()->SetTitleSize(0.05);
  // hRatio->GetXaxis()->SetLabelSize(0.05);
  // hRatio->GetXaxis()->CenterTitle(true);
  // hRatio->GetYaxis()->CenterTitle(true);
  // hRatio->Draw();
  // TLine lineOne;
  // lineOne.SetLineStyle(2);
  // lineOne.DrawLine(centBinMin,1.,centBinMax,1.);
  // for (int m=0;m<nMethod;m++){
  //   grRatio[m]->Draw("P PLC PMC");
  // }
  // c->SaveAs(Form("v2_AMPT_%s.pdf",energy.Data()));
  return gr;
}