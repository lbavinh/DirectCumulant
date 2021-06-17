#include "DrawTGraphImp.C"

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

void CompareV24_Standard_vs_TwoSub(){
  
  // Flags
  bool saveAsPNG = true;
  int ratioToMethod = 1;
  int drawDifferentialFlowTill = 0; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
  // Constants
  TString inputFileName = "AMPT15_7.7_v24_2sub.root";
  TString model = "AMPT SM, #sigma_{p} = 1.5 mb";
  TString energy = "7.7GeV";
  const int nmethod = 4; // 2QC, 4QC, 2QC(2-sub), 4QC(2-sub)

  const double minptRFP = 0.2;
  const double maxptRFP = 3.0;

  const double maxpt = 2.5; // for v2 vs pt plotting
  const double minpt = 0.;  // for v2 vs pt plotting

  const int ncent = 9; // 0-80 %
  const double bin_cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
  const double bin_centE[ncent] = {0};
  const vector<pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};


  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.2; // for v2 vs pt plotting


  vector <Double_t> coordinateLeg = {0.18,0.55,0.45,0.8};
  vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.92,1.08},{0.88,1.22}};
  int marker[]={21,25,22,20}; // 2QC, 4QC, EP, 2QC-gapped

  // TString inFileName= (TString) Form("../ROOTFile/%s_%s.root",model.Data(),energy.Data());
  TString outDirName=(TString)Form("%s_%s",model.Data(),energy.Data());
  TString level= (TString) Form("%s, Au+Au at #sqrt{s_{NN}}=%s",model.Data(),energy.Data());
  TFile *inFile = new TFile(inputFileName.Data(),"read");


  // Temporary variables
  char hname[800]; // histogram hname

  // Input hist
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov24Gap[ncent];       // <2>*<4>
  TProfile *hv22Gap[ncent];
  TProfile *hv24Gap[ncent];

  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    hcov24Gap[icent] = (TProfile*)inFile->Get(Form("hcov24Gap_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->Get(Form("hv22Gap_%i",icent));
    hv24Gap[icent] = (TProfile*)inFile->Get(Form("hv24Gap_%i",icent));

  } // end of loop over centrality classes

  TGraphErrors *grRefFl[nmethod];
  double v2_RF[nmethod][ncent],    v2e_RF[nmethod][ncent];
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
    // 2QC, 2-sub
    term cor2Gap = term(hv22Gap[icent]);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    v2_RF[2][icent] = v22Gap;
    v2e_RF[2][icent] = ev22Gap;
    // 4QC, 2-sub
    term cor4Gap = term(hv24Gap[icent]);
    double cov24Gap = Covariance(hcov24Gap[icent],hv22Gap[icent],hv24Gap[icent]);
    double v24Gap = pow(2*pow(cor2Gap.mVal,2)-cor4Gap.mVal,0.25);
    double ev24Gap = sqrt( 1./pow(v24Gap,6)*(cor2Gap.mVal*cor2Gap.mVal*cor2Gap.mMSE+1./16*cor4Gap.mMSE-0.5*cor2Gap.mVal*cov24Gap) );
    cout << cor4.mVal << " " << cor4Gap.mVal << endl;
    v2_RF[3][icent] = v24Gap;
    v2e_RF[3][icent] = ev24Gap;

  } // end of loop over centrality classes
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] = new TGraphErrors(ncent,bin_cent,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grRefFl[imeth] -> SetMarkerStyle(marker[imeth]);
    grRefFl[imeth] -> SetMarkerSize(1.5);
    grRefFl[imeth] -> RemovePoint(0);
  }
  const char *grTitleRF[nmethod]={"v_{2}{2};Centrality, %;v_{2}",
                                  "v_{2}{4};Centrality, %;v_{2}",
                                  "v_{2}{2,|#Delta#eta|>0};Centrality, %;v_{2}",
                                  "v_{2}{4,|#Delta#eta|>0};Centrality, %;v_{2}"};


  TCanvas *cV2CentRF;
  std::vector<TGraphErrors*> vgrv2cent_chargedHardons;
  for (int imeth=0; imeth<nmethod; imeth++){
    // grRefFl[imeth][id] -> SetTitle(Form("V2 vs. pT, %s, centrality 10-40%%, %s",pidNames.at(id).Data(),grTitleDF[imeth]));
    grRefFl[imeth] -> SetTitle(grTitleRF[imeth]);
  }
  vgrv2cent_chargedHardons.push_back(grRefFl[ratioToMethod]);
  vgrv2cent_chargedHardons.push_back(grRefFl[3]);
  // for (int imeth=0;imeth<nmethod;imeth++){
  //   if (imeth==ratioToMethod) continue;
  //   vgrv2cent_chargedHardons.push_back(grRefFl[imeth]);
  // }
  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second, mincent, maxcent, minV2int, maxV2int,
                                    coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                    level.Data(), Form("Charged hadrons, %1.1f < p_{T}< %1.1f GeV/c",minptRFP,maxptRFP),1,"v_{2}{4}");
  cV2CentRF -> SetName("Reference flow");
  if (saveAsPNG) cV2CentRF -> SaveAs(Form("CompareV24_Standard_vs_TwoSub.pdf"));
  if (saveAsPNG) cV2CentRF -> SaveAs(Form("CompareV24_Standard_vs_TwoSub.png"));

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    delete hv22[icent];
    delete hv24[icent];
    delete hcov24[icent];
    delete hv22Gap[icent];
  } // end of loop over centrality classes
  inFile->Close();
}
