#include "DrawTGraphImp.C"


// Flags
bool saveAsPNG = true;
int excludeMethod = -1; // not including i-th method in v2 plotting, where i=0,1,2,3 correspond v22,v24,v2eta-sub,v22eta-gap, respectively
int ratioToMethod = 4;
int drawDifferentialFlowTill = 5; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
// Constants
const int npid = 1;
const std::vector<TString> pidNames = {"hadron"};
const std::vector<TString> pidFancyNames = {"h^{#pm}"};

const float eta_gap = 0;
// TString inputFileName = Form("QCumulant_eta_gap_%1.1f.root",eta_gap*2);
TString inputFileName = "QCumulant.root";

const int nmethod = 5; // 2QC; 4QC; 2QC,2-sub; 4QC,2-sub, MC; 

const int npt = 12; // 0.5 - 3.6 GeV/c - number of pT bins
const double bin_pT[npt + 1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
const int binMinPtRFP = 1;  // 0.2 GeV 
const int binMaxPtRFP = 14; // 2.8 GeV
// const int binMaxPtRFP = 10; // 2.0 GeV
// const int binMaxPtRFP = 16; // 3.6 GeV
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


vector <Double_t> coordinateLeg = {0.18,0.5,0.45,0.889};
vector<pair<Double_t,Double_t>> rangeRatio = {{0.89,1.11},{0.89,1.11}};
vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.89,1.11},{0.89,1.11}};
int marker[]={21,20,22,32,25}; // 2QC, 4QC, 2QC-gapped, 4QC-gapped, MC

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


void v2plot_with_2sub(TString model = "ToyModel", TString statistic = "10M"){
  
  // TString inFileName= (TString) Form("../ROOTFile/%s_%s.root",model.Data(),statistic.Data());
  // TFile *outFile = new TFile(Form("./v2_%s_%s.root",model.Data(),statistic.Data()),"recreate");
  TString outDirName=(TString)Form("%s_%s_eta_gap_%1.1f",model.Data(),statistic.Data(),eta_gap*2);
  TString level= (TString) Form("%s, %s, |#Delta#eta|>0",model.Data(),statistic.Data());
  double v2eDif1040[nmethod][npid][npt];

  TFile *inFile = new TFile(inputFileName.Data(),"read");


  // Temporary variables
  char hname[800]; // histogram hname

  TProfile *hv2MC[ncent];       // profile for MC integrated v2
  TProfile *hv2MCpt[ncent][npt];   // profile v2pt from MC toy   
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv2MC_%i",icent);
    hv2MC[icent] = (TProfile*)inFile->Get(hname);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      sprintf(hname,"hv2MCpt_%i_%i",icent,ipt);
      hv2MCpt[icent][ipt]=(TProfile*)inFile->Get(hname);
    }
  }
  
  // Input hist
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  // v22 with eta-gap
  TProfile *hv22Gap[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24Gap[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hv22ptGap[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24ptGap[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24Gap[ncent];       // <2>*<4>
  TProfile *hcov22primeGap[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24primeGap[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42primeGap[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44primeGap[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4primeGap[ncent][npt][npid]; // <2'>*<4'>
  // OUTPUT
  TGraphErrors *grDifFl[nmethod][ncent][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));

    hv22Gap[icent] = (TProfile*)inFile->Get(Form("hv22Gap_%i",icent));
    hv24Gap[icent] = (TProfile*)inFile->Get(Form("hv24Gap_%i",icent));
    hcov24Gap[icent] = (TProfile*)inFile->Get(Form("hcov24Gap_%i",icent));
    // if (!hv22[icent] || !hv24[icent] || !hcov24[icent] || !hv22Gap[icent]) cout << "errror" << endl;
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv22pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22prime_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov24prime_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov42prime_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov44prime_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i",icent,ipt,id));

        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22ptGap_%i_%i",icent,ipt,id));
        hv24ptGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24ptGap_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22primeGap_%i_%i",icent,ipt,id));
        hcov24primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov24primeGap_%i_%i",icent,ipt,id));
        hcov42primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov42primeGap_%i_%i",icent,ipt,id));
        hcov44primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov44primeGap_%i_%i",icent,ipt,id));
        hcov2prime4primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4primeGap_%i_%i",icent,ipt,id));        
        // if (!hv22pt[icent][ipt][id]) cout << "hv22pt["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hv24pt[icent][ipt][id]) cout << "hv24pt["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hcov22prime[icent][ipt][id]) cout << "hcov22prime["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hcov24prime[icent][ipt][id]) cout << "hcov24prime["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hcov42prime[icent][ipt][id]) cout << "hcov42prime["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hcov44prime[icent][ipt][id]) cout << "hcov44prime["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hcov2prime4prime[icent][ipt][id]) cout << "hcov2prime4prime["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hv22ptGap[icent][ipt][id]) cout << "hv22ptGap["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        // if (!hcov22primeGap[icent][ipt][id]) cout << "hcov22primeGap["<< icent<<"]["<<ipt<<"]["<<id<<"]=nullptr" << endl;
        
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes
  
  //==========================================================================================================================

  // Filling pT bin
  double pt[npt];
  double ept[npt]={0}; // error bin pT = 0.0
  for (int ipt=0; ipt<npt; ipt++){
    // pt[icent][ipt][id] = hPT[icent][ipt][id] -> GetBinContent(1);
    pt[ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
  }
  

  double v2Dif[nmethod][ncent][npid][npt], v2eDif[nmethod][ncent][npid][npt];
  double v2_RF[nmethod][ncent],            v2e_RF[nmethod][ncent];
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
    // 4QC, 2-sub
    term cor4Gap = term(hv24Gap[icent]);
    double cov24Gap = Covariance(hcov24Gap[icent],hv22Gap[icent],hv24Gap[icent]);
    double v24Gap = pow(2*pow(cor2Gap.mVal,2)-cor4Gap.mVal,0.25);
    double ev24Gap = sqrt( 1./pow(v24Gap,6)*(cor2Gap.mVal*cor2Gap.mVal*cor2Gap.mMSE+1./16*cor4Gap.mMSE-0.5*cor2Gap.mVal*cov24Gap) );
    v2_RF[3][icent] = v24Gap;
    v2e_RF[3][icent] = ev24Gap;

    v2_RF[4][icent]  = hv2MC[icent] -> GetBinContent(1);
    v2e_RF[4][icent] = hv2MC[icent] -> GetBinError(1);
    for (int id=0;id<npid;id++){ // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        // vPt.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
        // ePt.push_back(0);

        // v22
        term cor2red = term(hv22pt[icent][ipt][id]);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        v2Dif[0][icent][id][ipt] = v22Dif;
        v2eDif[0][icent][id][ipt] = ev22Dif;
        
        // v24
        term cor4red = term(hv24pt[icent][ipt][id]);
        double cov24prime = Covariance(hcov24prime[icent][ipt][id],hv22[icent],hv24pt[icent][ipt][id]);
        double cov42prime = Covariance(hcov42prime[icent][ipt][id],hv24[icent],hv22pt[icent][ipt][id]);
        double cov44prime = Covariance(hcov44prime[icent][ipt][id],hv24[icent],hv24pt[icent][ipt][id]);
        double cov2prime4prime = Covariance(hcov2prime4prime[icent][ipt][id],hv22pt[icent][ipt][id],hv24pt[icent][ipt][id]);
        double v24Dif = (2.*cor2.mVal*cor2red.mVal-cor4red.mVal)*pow(v24,-3);
        double ev24Dif = sqrt( pow(v24,-14)
            * (pow(2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal,2.)
            * cor2.mMSE
            + 9./16*pow(2.*cor2.mVal*cor2red.mVal-cor4red.mVal,2.)*cor4.mMSE
            + 4*pow(cor2.mVal,2)*pow(v24,8)*cor2red.mMSE
            + pow(v24,8)*cor4red.mMSE
            - 1.5*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov24
            - 4*cor2.mVal*pow(v24,4)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov22prime
            + 2*pow(v24,4)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov24prime
            + 3*cor2.mVal*pow(v24,4)*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * cov42prime
            - 1.5*pow(v24,4)*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * cov44prime
            - 4*cor2.mVal*pow(v24,8)*cov2prime4prime));
        v2Dif[1][icent][id][ipt] = v24Dif;
        v2eDif[1][icent][id][ipt] = ev24Dif;

        // v22 Gapped
        term cor2redGap = term(hv22ptGap[icent][ipt][id]);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(hcov22primeGap[icent][ipt][id],hv22Gap[icent],hv22ptGap[icent][ipt][id]);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        v2Dif[2][icent][id][ipt] = v22DifGap;
        v2eDif[2][icent][id][ipt] = ev22DifGap;

        // v24,2-sub
        term cor4redGap = term(hv24ptGap[icent][ipt][id]);
        double cov24primeGap = Covariance(hcov24primeGap[icent][ipt][id],hv22Gap[icent],hv24ptGap[icent][ipt][id]);
        double cov42primeGap = Covariance(hcov42primeGap[icent][ipt][id],hv24Gap[icent],hv22ptGap[icent][ipt][id]);
        double cov44primeGap = Covariance(hcov44primeGap[icent][ipt][id],hv24Gap[icent],hv24ptGap[icent][ipt][id]);
        double cov2prime4primeGap = Covariance(hcov2prime4primeGap[icent][ipt][id],hv22ptGap[icent][ipt][id],hv24ptGap[icent][ipt][id]);
        double v24DifGap = (2.*cor2Gap.mVal*cor2redGap.mVal-cor4redGap.mVal)*pow(v24Gap,-3);
        double ev24DifGap = sqrt( pow(v24Gap,-14)
            * (pow(2*cor2Gap.mVal*cor2Gap.mVal*cor2redGap.mVal-3*cor2Gap.mVal*cor4redGap.mVal+2*cor4Gap.mVal*cor2redGap.mVal,2.)
            * cor2Gap.mMSE
            + 9./16*pow(2.*cor2Gap.mVal*cor2redGap.mVal-cor4redGap.mVal,2.)*cor4Gap.mMSE
            + 4*pow(cor2Gap.mVal,2)*pow(v24Gap,8)*cor2redGap.mMSE
            + pow(v24Gap,8)*cor4redGap.mMSE
            - 1.5*(2*cor2Gap.mVal*cor2redGap.mVal-cor4redGap.mVal)
            * (2*cor2Gap.mVal*cor2Gap.mVal*cor2redGap.mVal-3*cor2Gap.mVal*cor4redGap.mVal+2*cor4Gap.mVal*cor2redGap.mVal)
            * cov24Gap
            - 4*cor2Gap.mVal*pow(v24Gap,4)
            * (2*cor2Gap.mVal*cor2Gap.mVal*cor2redGap.mVal-3*cor2Gap.mVal*cor4redGap.mVal+2*cor4Gap.mVal*cor2redGap.mVal)
            * cov22primeGap
            + 2*pow(v24Gap,4)
            * (2*cor2Gap.mVal*cor2Gap.mVal*cor2redGap.mVal-3*cor2Gap.mVal*cor4redGap.mVal+2*cor4Gap.mVal*cor2redGap.mVal)
            * cov24primeGap
            + 3*cor2Gap.mVal*pow(v24Gap,4)*(2*cor2Gap.mVal*cor2redGap.mVal-cor4redGap.mVal)
            * cov42primeGap
            - 1.5*pow(v24Gap,4)*(2*cor2Gap.mVal*cor2redGap.mVal-cor4redGap.mVal)
            * cov44primeGap
            - 4*cor2Gap.mVal*pow(v24Gap,8)*cov2prime4primeGap));
        v2Dif[3][icent][id][ipt] = v24DifGap;
        v2eDif[3][icent][id][ipt] = ev24DifGap;

        v2Dif[4][icent][id][ipt]  = hv2MCpt[icent][ipt] -> GetBinContent(1);
        v2eDif[4][icent][id][ipt] = hv2MCpt[icent][ipt] -> GetBinError(1);
      } // end of loop for all pT bin
      for (int i=0; i<nmethod; i++){
        grDifFl[i][icent][id] = new TGraphErrors(npt,pt,v2Dif[i][icent][id],ept,v2eDif[i][icent][id]);
        grDifFl[i][icent][id] -> SetMarkerStyle(marker[i]);
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }
    } // end of loop over PID
  } // end of loop over centrality classes
  const char *grTitleRF[nmethod]={"v_{2}{2};Centrality, %;v_{2}",
                                  "v_{2}{4};Centrality, %;v_{2}",
                                  "v_{2}{2,2-sub};Centrality, %;v_{2}",
                                  "v_{2}{4,2-sub};Centrality, %;v_{2}",
                                  "v_{2}{MC};Centrality, %;v_{2}"};  
  TGraphErrors *grRefFl[nmethod];
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] = new TGraphErrors(ncent,bin_cent,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grRefFl[imeth] -> SetMarkerStyle(marker[imeth]);
    grRefFl[imeth] -> SetMarkerSize(1.5);
    grRefFl[imeth] -> SetTitle(grTitleRF[imeth]);
  }

  const char *grTitleDF[nmethod]={"v_{2}{2};p_{T} [GeV/c];v_{2}",
                                  "v_{2}{4};p_{T} [GeV/c];v_{2}",
                                  "v_{2}{2,2-sub};p_{T} [GeV/c];v_{2}",
                                  "v_{2}{4,2-sub};p_{T} [GeV/c];v_{2}",
                                  "v_{2}{MC};p_{T} [GeV/c];v_{2}"};
  const char *grTitle[nmethod]={"v_{2}{2}",
                                "v_{2}{4}",
                                "v_{2}{2,2-sub}",
                                "v_{2}{4,2-sub}",
                                "v_{2}{MC}"};
  // outFile -> cd();
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent;icent++){
        grDifFl[imeth][icent][id] -> SetTitle(grTitleDF[imeth]);
        // grDifFl[imeth][icent][id] -> Write(Form("gr_cent%i_%i_%i",icent,imeth,id));
      }
    }
  }
  
  if (saveAsPNG) gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
  
  TCanvas *cV2PT[ncent][npid];
  for (int icent=0; icent<drawDifferentialFlowTill; icent++){
    for (int id=0;id<npid;id++){
      std::vector<TGraphErrors*> vgrv2pt;
      vgrv2pt.push_back(grDifFl[ratioToMethod][icent][id]); // v2{gapped 2QC}
      for (int i=0; i<nmethod; i++){
        if (i==ratioToMethod) continue;
        vgrv2pt.push_back(grDifFl[i][icent][id]);
      }
      sprintf(hname,"%i-%i%%",centrality.at(icent).first,centrality.at(icent).second);
      cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt,"",rangeRatio.at(0).first, rangeRatio.at(0).second, minpt, maxpt, minV2dif, maxV2dif,
                                               coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                               level.Data(), hname, true, grTitle[ratioToMethod]);
      cV2PT[icent][id] -> SetName(hname);
      if (saveAsPNG) cV2PT[icent][id] -> SaveAs(Form("./%s/DifferentialFlow_Centrality%i-%i.png",outDirName.Data(),centrality.at(icent).first,centrality.at(icent).second));
    }
  }

  TCanvas *cV2CentRF;
  std::vector<TGraphErrors*> vgrv2cent_chargedHardons;
  vgrv2cent_chargedHardons.push_back(grRefFl[ratioToMethod]);
  for (int imeth=0;imeth<nmethod;imeth++){
    if (imeth==ratioToMethod) continue;
    vgrv2cent_chargedHardons.push_back(grRefFl[imeth]);
  }
  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second, mincent, maxcent, minV2int, maxV2int,
                                    coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                    level.Data(), "", true, grTitle[ratioToMethod]);
  cV2CentRF -> SetName("Reference flow");
  if (saveAsPNG) cV2CentRF -> SaveAs(Form("./%s/IntegratedFlow_hadron.png",outDirName.Data()));
  inFile->Close();
}
