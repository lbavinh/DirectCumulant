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

void plot(TString model ="Glauber", TString energy = "11.5GeV") {
  
  TString inFileName = (TString) Form("../ROOTFile/%s_%s.root",model.Data(),energy.Data());
  TFile *outFile = new TFile(Form("./ecc_%s_%s.root",model.Data(),energy.Data()),"recreate");
  TString level= (TString) Form("%s, Au+Au at #sqrt{s_{NN}}=%s",model.Data(),energy.Data());

  // Flags
  bool bMergeCharged = false; // merge CH(+) with CH(-); Pion(+) with Pion(-) and so on
  bool saveAsPNG = true;
  // Constant
  const int ncent = 9; // 0-80 %
  const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  const double bin_centE[ncent] = {0};
  const int nmethod = 3;
  const int ratioToMethod = 0;
  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 82.; // for v2 vs centrality

  const double minV2int = -0.05; // for v2 vs centrality plotting
  const double maxV2int = 1.05; // for v2 vs centrality plotting
  const TString title[] = {"#epsilon_{2}{2}","#epsilon_{2}{4}","#epsilon_{2}{part}"};
  vector <Double_t> coordinateLeg = {0.18,0.63,0.45,0.889};
  int marker[]={21,20,22,25}; // 2QC, 4QC, EP, 2QC-gapped

  // gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
  TFile *inFile = new TFile(inFileName.Data(),"read");
  // TFile *inFile = new TFile("../ROOTFile/UrQMD_7.7GeV.root","read");

  // OUTPUT
  TGraphErrors *gr[nmethod], *grRatio[nmethod];
  
  // Histogram input
  TProfile *prEcc22 = (TProfile*)inFile->Get(Form("prEcc22vsCent"));
  TProfile *prEcc24 = (TProfile*)inFile->Get(Form("prEcc24vsCent"));
  TProfile *prCov24 = (TProfile*)inFile->Get(Form("prCov24vsCent"));
  TProfile *ecc2vsCent = (TProfile *) inFile -> Get("prEcc2vsCent");

  double ecc2[nmethod][ncent], ecc2e[nmethod][ncent];

  for (int icent=0;icent<ncent;icent++){
    term cor2 = term(prEcc22,icent);
    ecc2[0][icent]  = sqrt(cor2.mVal);
    ecc2e[0][icent] = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // cout << ecc2[0][icent] << endl;
    term cor4 = term(prEcc24,icent);
    double cov24 = Covariance(prCov24,prEcc22,prEcc24,icent,icent,icent);
    double ecc24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    ecc2[1][icent]  = ecc24;
    ecc2e[1][icent] = sqrt( 1./pow(ecc24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    ecc2[2][icent] = ecc2vsCent -> GetBinContent(icent+1);
    ecc2e[2][icent] = ecc2vsCent -> GetBinError(icent+1);
  }
  for (int m=0; m<nmethod; m++){
    gr[m] = new TGraphErrors(ncent,bin_cent,ecc2[m],bin_centE,ecc2e[m]);
    gr[m] -> SetMarkerStyle(marker[m]);
    gr[m] -> SetMarkerSize(2.);
    gr[m] -> SetTitle(title[m].Data());
  }
  gr[0] -> SetMarkerColor(kRed+2);
  gr[1] -> SetMarkerColor(kBlue+3);
  gr[2] -> SetMarkerColor(kGreen+3);
  // ratio graph
  Double_t *vx_gr[nmethod], *vy_gr[nmethod], *ex_gr[nmethod], *ey_gr[nmethod];
  Int_t nbins[nmethod];

  for (int m=0;m<nmethod;m++){
    // Read points
    vx_gr[m]=(Double_t*)gr[m]->GetX();
    vy_gr[m]=(Double_t*)gr[m]->GetY();

    // Read errors
    ex_gr[m]=(Double_t*)gr[m]->GetEX();
    ey_gr[m]=(Double_t*)gr[m]->GetEY();

    nbins[m]=(Int_t) gr[m]->GetN();
  }

  for (int m=0;m<nmethod;m++){

    std::vector<Double_t> vRatio, vRatioErr;
    for (int i=0;i<nbins[ratioToMethod];i++){
      Double_t ratio = vy_gr[m][i]/vy_gr[ratioToMethod][i];
      Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ratioToMethod][i]/vy_gr[ratioToMethod][i],2)+TMath::Power(ey_gr[m][i]/vy_gr[m][i],2)));
      vRatio.push_back(ratio);
      vRatioErr.push_back(ratioErr);
    }
    grRatio[m] = new TGraphErrors(nbins[ratioToMethod],vx_gr[ratioToMethod],&vRatio[0],ex_gr[ratioToMethod],&vRatioErr[0]);
    grRatio[m] -> SetMarkerStyle(gr[m]->GetMarkerStyle());
    grRatio[m] -> SetMarkerColor(gr[m]->GetMarkerStyle());
    grRatio[m] -> SetLineColor(gr[m]->GetMarkerStyle());
    grRatio[m] -> SetMarkerSize(2.);
    vRatio.clear();
    vRatioErr.clear();
  }
  grRatio[0] -> SetMarkerColor(kRed+2);
  grRatio[1] -> SetMarkerColor(kBlue+3);
  grRatio[2] -> SetMarkerColor(kGreen+3);
  

  
  TCanvas *c = new TCanvas("c","",200,10,1600,1200);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetErrorX(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  c->SetLeftMargin(0.12);
  c->Divide(1,2,0,0);
  c->cd(1);
  TH2F *h = new TH2F("h",Form("UrQMD, Au+Au at #sqrt{s_{NN}} = %s;centrality (%%);#epsilon_{2}", energy.Data()),ncent,mincent,maxcent,1,minV2int,maxV2int);
  // h->GetXaxis()->SetNdivisions(504);
  h->GetYaxis()->SetNdivisions(504);
  h->GetYaxis()->SetTitleOffset(0.8);
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->Draw();
  for (int m=0;m<nmethod;m++){
    gr[m]->Draw("P");// PLC PMC
  }
  TLegend *leg = new TLegend(0.8,0.1,0.9,0.25);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetTextFont(42);
  for (int m=0;m<nmethod;m++){
    leg->AddEntry(gr[m],gr[m]->GetTitle(),"p");
  }
  leg->Draw();
  c->cd(2);
  TH2F *hRatio = new TH2F("hRatio",Form(";centrality (%%);Ratio to #epsilon_{2}{2}"),ncent,mincent,maxcent,1,0.3,1.4);
  // hRatio->GetXaxis()->SetNdivisions(504);
  hRatio->GetYaxis()->SetNdivisions(504);
  hRatio->GetYaxis()->SetTitleOffset(0.8);
  hRatio->GetYaxis()->SetLabelSize(0.05);
  hRatio->GetYaxis()->SetTitleSize(0.05);
  hRatio->GetXaxis()->SetTitleSize(0.05);
  hRatio->GetXaxis()->SetLabelSize(0.05);
  hRatio->GetXaxis()->CenterTitle(true);
  hRatio->GetYaxis()->CenterTitle(true);
  hRatio->Draw();
  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(mincent,1.,maxcent,1.);
  for (int m=1;m<nmethod;m++){
    grRatio[m]->Draw("P");
  }
  outFile->cd();
  grRatio[1]->Write("gr_e24e22");
  // c->SaveAs(Form("Eccentricity2_%s_%s.pdf",model.Data(),energy.Data()));
  c->SaveAs(Form("Eccentricity2_%s_%s.png",model.Data(),energy.Data()));
  delete prEcc22;
  delete prEcc24;
  delete prCov24;
  inFile->Close();
}

