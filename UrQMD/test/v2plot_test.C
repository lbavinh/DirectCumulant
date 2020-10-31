#include "DrawTGraphImp.C"
#include <vector>

#include <TGraphErrors.h>

TString model = {"UrQMD"};
TString energy = {"7.7GeV"};
TString inFileName= (TString) Form("./%s_%s_test_same_gap_forv22v24.root",model.Data(),energy.Data());
TFile *outFile = new TFile(Form("./v2_%s_%s_test.root",model.Data(),energy.Data()),"recreate");
TString outDirName=(TString)Form("%s_%s_test",model.Data(),energy.Data());
TString level= (TString) Form("%s, Au+Au at #sqrt{s_{NN}}=%s",model.Data(),energy.Data());

// Flags
bool bDrawQAHist = false; // auxiliary plots: eta, bimp, mult, etc.
bool bMergeCharged = false; // merge CH(+) with CH(-); Pion(+) with Pion(-) and so on
bool saveAsPNG = true;
int excludeMethod = -1; // not including i-th method in v2 plotting, where i=0,1,2,3 correspond v22,v24,v2eta-sub,v22eta-gap, respectively
int drawDifferentialFlowTill = 4; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
int ratioToMethod = 1; // 2QC,FHCal; 2QC,eta-gap; 2QC; 4QC; TPC,EP; TPC,SP; FHCal,EP
// Constants
const int npid = 8; // charged hadrons, pions, kaons, protons
const int nmethod = 7; // 2QC,FHCal; 2QC,eta-gap; 2QC; 4QC; TPC,EP; TPC,SP; FHCal,EP

const int npt = 10; // 0.5 - 3.6 GeV/c - number of pT bins
const double bin_pT[npt+1]={0.,0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.}; // pT bins

const std::vector<double> pt_binning = {0.,0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};
const int n_pt_bins = pt_binning.size() - 1;

const double minptRFP = 0.2;
const double maxptRFP = 3.0;

const double maxpt = 2.5; // for v2 vs pt plotting
const double minpt = 0.;  // for v2 vs pt plotting

// const std::vector<std::pair<float, float>> centRange = {{0., 5.}, {5., 10.}, {10.,20.}, {20., 30.}, {30., 40.}, {40., 50.}, {50.,60.}, {60.,70.}, {70.,80.}};
const std::vector<std::pair<float, float>> centRange = {{0., 10.}, {10.,20.}, {20., 30.}, {30., 40.}, {40., 50.}, {50.,60.}, {60.,70.}, {70.,80.}};
const int n_cent_bins = centRange.size();

const int ncent = 8; // 0-80 %
// const double bin_cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
const double bin_centE[ncent] = {0};
const float eta_gap = 0.05;

const double mincent = 0.;  // for v2 vs centrality
const double maxcent = 60.; // for v2 vs centrality

const double minV2int = -0.005; // for v2 vs centrality plotting
const double maxV2int = 0.1; // for v2 vs centrality plotting
const double minV2dif = -0.01; // for v2 vs pt plotting
const double maxV2dif = 0.2; // for v2 vs pt plotting

std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
vector <Double_t> coordinateLeg = {0.18,0.5,0.45,0.889};
vector<pair<Double_t,Double_t>> rangeRatio = {{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16}}; // 0-10; 10-20; 20-30; 30-40; 40-50; 50-60; 60-70; 70-80; 10-40%
vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11}}; // charged hadrons, pions, kaons, protons
int marker[nmethod]={21,20,22,25,23,24,26}; // 2QC,FHCal; 2QC,eta-gap; 2QC; 4QC; TPC,EP; TPC,SP; FHCal,EP
int color[]={205,102,96,87,81,69,104,154,213};
//            Br, R, Or,Gr,Gr,Cy,B, B,  DarkB 
const float markerSize = 1.2; const int markerStyle = 20;
TProfile *prV22int[ncent][npid], *prV24int[ncent][npid], *prV22FHCalint[ncent][npid], *prV22intGap[ncent][npid]; // TProfile for integrated flow 
TProfile *pV2Integrated[npid][nmethod];
double eV2Cent1040[npid][nmethod][npt];
double eV22FHCalcent1040[npid][npt], eV22Gapcent1040[npid][npt], eV22cent1040[npid][npt], eV24cent1040[npid][npt], eV2EPcent1040[npid][npt], eV2SPcent1040[npid][npt], eV2EPFHCalcent1040[npid][npt];
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

void CalStatErrCent1040(){
  TFile *inFile = new TFile(inFileName.Data(),"read");

  TProfile *pCorrelator2EtaGap_FHCal = (TProfile*)inFile->Get("pCorrelator2EtaGap_FHCal");
  TProfile *pCorrelator2EtaGap = (TProfile*)inFile->Get("pCorrelator2EtaGap");
  TProfile *pCorrelator2 = (TProfile*)inFile->Get("pCorrelator2");
  TProfile *pCorrelator4 = (TProfile*)inFile->Get("pCorrelator4");
  
  TProfile *pResTPC_EP = (TProfile*)inFile->Get("pResTPC_EP");
  TProfile *pResTPC_SP = (TProfile*)inFile->Get("pResTPC_SP");
  TProfile *pResFHCal_EP = (TProfile*)inFile->Get("pResFHCal_EP");

  TProfile2D *pReducedCorrelator2EtaGap_FHCal[npid]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2EtaGap[npid]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2[npid]; // <<2'>>
  TProfile2D *pReducedCorrelator4[npid]; // <<4'>>
  
  TProfile2D *pv2TPC_EP[npid];
  TProfile2D *pv2TPC_SP[npid];
  TProfile2D *pv2FHCal_EP[npid];

  TProfile2D *pCov22RedEtaGap_FHCal[npid];
  TProfile2D *pCov22RedEtaGap[npid];
  TProfile *pCov24 = (TProfile*)inFile->Get("pCov24");
  TProfile2D *pCov22Red[npid];
  TProfile2D *pCov24Red[npid];
  TProfile2D *pCov42Red[npid];
  TProfile2D *pCov44Red[npid];
  TProfile2D *pCov2Red4Red[npid];
  TProfile2D *pPt[npid][nmethod];
  // cerr <<"error"<<endl;
  for (int i=0; i<npid; i++)
  {
    pReducedCorrelator2EtaGap_FHCal[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_FHCal_pid%i",i));
    pReducedCorrelator2EtaGap[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_pid%i",i));
    pReducedCorrelator2[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2_pid%i",i));
    pReducedCorrelator4[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator4_pid%i",i));
    
    pv2TPC_EP[i] = (TProfile2D*)inFile->Get(Form("pv2TPC_EP_pid%i",i));
    pv2TPC_SP[i] = (TProfile2D*)inFile->Get(Form("pv2TPC_SP_pid%i",i));
    pv2FHCal_EP[i] = (TProfile2D*)inFile->Get(Form("pv2FHCal_EP_pid%i",i));
  
    pCov22RedEtaGap_FHCal[i] = (TProfile2D*)inFile->Get(Form("pCov22RedEtaGap_FHCal_pid%i",i));
    pCov22RedEtaGap[i] = (TProfile2D*)inFile->Get(Form("pCov22RedEtaGap_pid%i",i));
    pCov22Red[i] = (TProfile2D*)inFile->Get(Form("pCov22Red_pid%i",i));
    pCov24Red[i] = (TProfile2D*)inFile->Get(Form("pCov24Red_pid%i",i));
    pCov42Red[i] = (TProfile2D*)inFile->Get(Form("pCov42Red_pid%i",i));
    pCov44Red[i] = (TProfile2D*)inFile->Get(Form("pCov44Red_pid%i",i));
    pCov2Red4Red[i] = (TProfile2D*)inFile->Get(Form("pCov2Red4Red_pid%i",i));
  }

  double centrality_bin[2] = {10.,40.};
  pCorrelator2EtaGap_FHCal = (TProfile*)pCorrelator2EtaGap_FHCal->Rebin(1,pCorrelator2EtaGap_FHCal->GetName(), &centrality_bin[0]); 
  pCorrelator2EtaGap = (TProfile*)pCorrelator2EtaGap->Rebin(1,pCorrelator2EtaGap->GetName(), &centrality_bin[0]); 
  pCorrelator2 = (TProfile*)pCorrelator2->Rebin(1,pCorrelator2->GetName(), &centrality_bin[0]); 
  pCorrelator4 = (TProfile*)pCorrelator4->Rebin(1,pCorrelator4->GetName(), &centrality_bin[0]); 
  
  pResTPC_EP = (TProfile*)pResTPC_EP->Rebin(1,pResTPC_EP->GetName(), &centrality_bin[0]); 
  pResTPC_SP = (TProfile*)pResTPC_SP->Rebin(1,pResTPC_SP->GetName(), &centrality_bin[0]); 
  pResFHCal_EP = (TProfile*)pResFHCal_EP->Rebin(1,pResFHCal_EP->GetName(), &centrality_bin[0]); 
  pCov24 = (TProfile*)pCov24->Rebin(1,pCov24->GetName(), &centrality_bin[0]);

  TProfile *pReducedCorrelator2EtaGap_FHCal_cent[npid][1];
  TProfile *pReducedCorrelator2EtaGap_cent[npid][1];
  TProfile *pReducedCorrelator2_cent[npid][1];
  TProfile *pReducedCorrelator4_cent[npid][1];
  TProfile *pv2TPC_EP_cent[npid][1];
  TProfile *pv2TPC_SP_cent[npid][1];
  TProfile *pv2FHCal_EP_cent[npid][1];
  TProfile *pCov22RedEtaGap_FHCal_cent[npid][1];
  TProfile *pCov22RedEtaGap_cent[npid][1];
  TProfile *pCov22Red_cent[npid][1];
  TProfile *pCov24Red_cent[npid][1];
  TProfile *pCov42Red_cent[npid][1];
  TProfile *pCov44Red_cent[npid][1];
  TProfile *pCov2Red4Red_cent[npid][1];
  std::pair<int, int> cent_bins;
  for (int i = 0; i < npid; i++)
  {
    for (int c = 0; c < 1; c++)
    {
      cent_bins.first  = pv2TPC_EP[i]->GetYaxis()->FindBin(10.);
      cent_bins.second = pv2TPC_EP[i]->GetYaxis()->FindBin(39.);

      pReducedCorrelator2EtaGap_FHCal_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap_FHCal[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2EtaGap_FHCal[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2EtaGap[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pReducedCorrelator2_cent[i][c] = (TProfile*)pReducedCorrelator2[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pReducedCorrelator4_cent[i][c] = (TProfile*)pReducedCorrelator4[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator4[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pv2TPC_EP_cent[i][c]  = (TProfile*)pv2TPC_EP[i]->ProfileX(Form("%s_cent%i",pv2TPC_EP[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pv2TPC_SP_cent[i][c]  = (TProfile*)pv2TPC_SP[i]->ProfileX(Form("%s_cent%i",pv2TPC_SP[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pv2FHCal_EP_cent[i][c]  = (TProfile*)pv2FHCal_EP[i]->ProfileX(Form("%s_cent%i",pv2FHCal_EP[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov22RedEtaGap_FHCal_cent[i][c] = (TProfile*)pCov22RedEtaGap_FHCal[i]->ProfileX(Form("%s_cent%i",pCov22RedEtaGap_FHCal[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov22RedEtaGap_cent[i][c] = (TProfile*)pCov22RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov22RedEtaGap[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov22Red_cent[i][c] = (TProfile*)pCov22Red[i]->ProfileX(Form("%s_cent%i",pCov22Red[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov24Red_cent[i][c] = (TProfile*)pCov24Red[i]->ProfileX(Form("%s_cent%i",pCov24Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 
      pCov42Red_cent[i][c] = (TProfile*)pCov42Red[i]->ProfileX(Form("%s_cent%i",pCov42Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 
      pCov44Red_cent[i][c] = (TProfile*)pCov44Red[i]->ProfileX(Form("%s_cent%i",pCov44Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 
      pCov2Red4Red_cent[i][c] = (TProfile*)pCov2Red4Red[i]->ProfileX(Form("%s_cent%i",pCov2Red4Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 

      pReducedCorrelator2EtaGap_FHCal_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap_FHCal_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator2EtaGap_FHCal_cent[i][c]->GetName(), &pt_binning[0]);
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator2EtaGap_cent[i][c]->GetName(), &pt_binning[0]);
      pReducedCorrelator2_cent[i][c] = (TProfile*)pReducedCorrelator2_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator2_cent[i][c]->GetName(), &pt_binning[0]);
      pReducedCorrelator4_cent[i][c] = (TProfile*)pReducedCorrelator4_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator4_cent[i][c]->GetName(), &pt_binning[0]);
      pv2TPC_EP_cent[i][c]  = (TProfile*)pv2TPC_EP_cent[i][c]->Rebin(n_pt_bins,pv2TPC_EP_cent[i][c]->GetName(), &pt_binning[0]);
      pv2TPC_SP_cent[i][c]  = (TProfile*)pv2TPC_SP_cent[i][c]->Rebin(n_pt_bins,pv2TPC_SP_cent[i][c]->GetName(), &pt_binning[0]);
      pv2FHCal_EP_cent[i][c]  = (TProfile*)pv2FHCal_EP_cent[i][c]->Rebin(n_pt_bins,pv2FHCal_EP_cent[i][c]->GetName(), &pt_binning[0]);
      pCov22RedEtaGap_FHCal_cent[i][c] = (TProfile*)pCov22RedEtaGap_FHCal_cent[i][c]->Rebin(n_pt_bins,pCov22RedEtaGap_FHCal_cent[i][c]->GetName(), &pt_binning[0]);
      pCov22RedEtaGap_cent[i][c] = (TProfile*)pCov22RedEtaGap_cent[i][c]->Rebin(n_pt_bins,pCov22RedEtaGap_cent[i][c]->GetName(), &pt_binning[0]);
      pCov22Red_cent[i][c] = (TProfile*)pCov22Red_cent[i][c]->Rebin(n_pt_bins,pCov22Red_cent[i][c]->GetName(), &pt_binning[0]);
      pCov24Red_cent[i][c] = (TProfile*)pCov24Red_cent[i][c]->Rebin(n_pt_bins,pCov24Red_cent[i][c]->GetName(), &pt_binning[0]); 
      pCov42Red_cent[i][c] = (TProfile*)pCov42Red_cent[i][c]->Rebin(n_pt_bins,pCov42Red_cent[i][c]->GetName(), &pt_binning[0]); 
      pCov44Red_cent[i][c] = (TProfile*)pCov44Red_cent[i][c]->Rebin(n_pt_bins,pCov44Red_cent[i][c]->GetName(), &pt_binning[0]); 
      pCov2Red4Red_cent[i][c] = (TProfile*)pCov2Red4Red_cent[i][c]->Rebin(n_pt_bins,pCov2Red4Red_cent[i][c]->GetName(), &pt_binning[0]);
    }
  }

  for (int icent=0;icent<1;icent++){
    // 2QC,FHCal
    term cor2GapFHCal = term(pCorrelator2EtaGap_FHCal);
    // 2QC,eta-gap,TPC
    term cor2Gap = term(pCorrelator2EtaGap);    
    // 2QC
    term cor2 = term(pCorrelator2);
    // 4QC
    term cor4 = term(pCorrelator4);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);

    for (int id=0;id<npid;id++){     
      for(int ipt=0; ipt<npt; ipt++){
        // 2QC,FHCal
        term cor2redGapFHCal = term(pReducedCorrelator2EtaGap_FHCal_cent[id][icent],ipt);
        double cov22primeGapFHCal = Covariance(pCov22RedEtaGap_FHCal_cent[id][icent],pCorrelator2EtaGap_FHCal,pReducedCorrelator2EtaGap_FHCal_cent[id][icent],ipt,icent,ipt);
        double ev22DifGapFHCal = sqrt(0.25*pow(cor2GapFHCal.mVal,-3)*(pow(cor2redGapFHCal.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2GapFHCal.mVal,2)*cor2redGapFHCal.mMSE - 4*cor2GapFHCal.mVal*cor2redGapFHCal.mVal*cov22primeGapFHCal));
        eV2Cent1040[id][0][ipt] = ev22DifGapFHCal;

        // 2QC,eta-gap,TPC
        term cor2redGap = term(pReducedCorrelator2EtaGap_cent[id][icent],ipt);
        double cov22primeGap = Covariance(pCov22RedEtaGap_cent[id][icent],pCorrelator2EtaGap,pReducedCorrelator2EtaGap_cent[id][icent],ipt,icent,ipt);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        // eV22Gapcent1040[id][ipt] = ev22DifGap;
        eV2Cent1040[id][1][ipt] = ev22DifGap;

        // v22
        term cor2red = term(pReducedCorrelator2_cent[id][icent],ipt);
        double cov22prime = Covariance(pCov22Red_cent[id][icent],pCorrelator2,pReducedCorrelator2_cent[id][icent],ipt,icent,ipt);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        // eV22cent1040[id][ipt] = ev22Dif;
        eV2Cent1040[id][2][ipt] = ev22Dif;

        // v24
        term cor4red = term(pReducedCorrelator4_cent[id][icent],ipt);
        double cov24prime = Covariance(pCov24Red_cent[id][icent],pCorrelator2,pReducedCorrelator4_cent[id][icent],ipt,icent,ipt);
        double cov42prime = Covariance(pCov42Red_cent[id][icent],pCorrelator4,pReducedCorrelator2_cent[id][icent],ipt,icent,ipt);
        double cov44prime = Covariance(pCov44Red_cent[id][icent],pCorrelator4,pReducedCorrelator4_cent[id][icent],ipt,icent,ipt);
        double cov2prime4prime = Covariance(pCov2Red4Red_cent[id][icent],pReducedCorrelator2_cent[id][icent],pReducedCorrelator4_cent[id][icent],ipt,ipt,ipt);
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
        // eV24cent1040[id][ipt] = ev24Dif;

        eV2Cent1040[id][3][ipt] = ev24Dif;
        // TPC, EP
        double res2EP = sqrt(pResTPC_EP->GetBinContent(1));
        double ev2EP = pv2TPC_EP_cent[id][icent]->GetBinError(ipt+1) / res2EP;
        // eV2EPcent1040[id][ipt] = ev2EP;
        eV2Cent1040[id][4][ipt] = ev2EP;
        // TPC, SP
        double res2SP = sqrt(pResTPC_SP->GetBinContent(1));
        double ev2SP = pv2TPC_SP_cent[id][icent]->GetBinError(ipt+1) / res2SP;
        eV2Cent1040[id][5][ipt] = ev2SP;
        // FHCal, EP
        // double res1EP_FHCal = sqrt(pResFHCal_EP->GetBinContent(icent+1));
        double res1EP_FHCal = 1.;
        double ev2EPFHCal = pv2FHCal_EP_cent[id][icent]->GetBinError(ipt+1) / res1EP_FHCal;
        eV2Cent1040[id][6][ipt] = ev2EPFHCal;
      } // end of loop for all pT bin
    } // end of loop for PID
  }

  delete pCorrelator2EtaGap_FHCal;
  delete pCorrelator2EtaGap;
  delete pCorrelator2;
  delete pCorrelator4;
  
  delete pResTPC_EP;
  delete pResTPC_SP;
  delete pResFHCal_EP;
  delete pCov24;
  for (int i=0; i<npid; i++)
  {
    delete pReducedCorrelator2EtaGap_FHCal[i];
    delete pReducedCorrelator2EtaGap[i];
    delete pReducedCorrelator2[i];
    delete pReducedCorrelator4[i];
    
    delete pv2TPC_EP[i];
    delete pv2TPC_SP[i];
    delete pv2FHCal_EP[i];
  
    delete pCov22RedEtaGap_FHCal[i];
    delete pCov22RedEtaGap[i];
    delete pCov22Red[i];
    delete pCov24Red[i];
    delete pCov42Red[i];
    delete pCov44Red[i];
    delete pCov2Red4Red[i];

    for (int c=0;c<1; c++){
    delete pReducedCorrelator2EtaGap_FHCal_cent[i][c];
    delete pReducedCorrelator2EtaGap_cent[i][c];
    delete pReducedCorrelator2_cent[i][c];
    delete pReducedCorrelator4_cent[i][c];
    delete pv2TPC_EP_cent[i][c];
    delete pv2TPC_SP_cent[i][c];
    delete pv2FHCal_EP_cent[i][c];
    delete pCov22RedEtaGap_FHCal_cent[i][c];
    delete pCov22RedEtaGap_cent[i][c];
    delete pCov22Red_cent[i][c];
    delete pCov24Red_cent[i][c];
    delete pCov42Red_cent[i][c];
    delete pCov44Red_cent[i][c];
    delete pCov2Red4Red_cent[i][c];
    }
  }

  delete inFile;
}

void v2plot_differential_flow(){
  TFile *inFile = new TFile(inFileName.Data(),"read");


  // Temporary variables
  char hname[800]; // histogram hname

  if (bDrawQAHist){
    TCanvas *cTemp = new TCanvas("cTemp","cTemp",200,10,800,450);

    TH1I *hMult = (TH1I*)inFile->Get("hMult");
    hMult -> Draw();
    if (saveAsPNG) cTemp -> SaveAs(Form("./%s/mult.png",outDirName.Data()));

    TH1F *hEta = (TH1F*)inFile->Get("hEta");
    hEta -> Draw();
    if (saveAsPNG) cTemp -> SaveAs(Form("./%s/eta.png",outDirName.Data()));  

    TH1F *hPhi = (TH1F*)inFile->Get("hPhi");
    hPhi -> Draw();
    if (saveAsPNG) cTemp -> SaveAs(Form("./%s/phi.png",outDirName.Data()));

    TH1F *hPt = (TH1F*)inFile->Get("hPt");
    hPt -> Draw();
    if (saveAsPNG) cTemp -> SaveAs(Form("./%s/pt.png",outDirName.Data()));
  }

  TProfile *pCorrelator2EtaGap_FHCal = (TProfile*)inFile->Get("pCorrelator2EtaGap_FHCal");
  TProfile *pCorrelator2EtaGap = (TProfile*)inFile->Get("pCorrelator2EtaGap");
  TProfile *pCorrelator2 = (TProfile*)inFile->Get("pCorrelator2");
  TProfile *pCorrelator4 = (TProfile*)inFile->Get("pCorrelator4");
  
  TProfile *pResTPC_EP = (TProfile*)inFile->Get("pResTPC_EP");
  TProfile *pResTPC_SP = (TProfile*)inFile->Get("pResTPC_SP");
  TProfile *pResFHCal_EP = (TProfile*)inFile->Get("pResFHCal_EP");

  TProfile2D *pReducedCorrelator2EtaGap_FHCal[npid]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2EtaGap[npid]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2[npid]; // <<2'>>
  TProfile2D *pReducedCorrelator4[npid]; // <<4'>>
  
  TProfile2D *pv2TPC_EP[npid];
  TProfile2D *pv2TPC_SP[npid];
  TProfile2D *pv2FHCal_EP[npid];

  TProfile2D *pCov22RedEtaGap_FHCal[npid];
  TProfile2D *pCov22RedEtaGap[npid];
  TProfile *pCov24 = (TProfile*)inFile->Get("pCov24");
  TProfile2D *pCov22Red[npid];
  TProfile2D *pCov24Red[npid];
  TProfile2D *pCov42Red[npid];
  TProfile2D *pCov44Red[npid];
  TProfile2D *pCov2Red4Red[npid];
  TProfile2D *pPt[npid][nmethod];

  for (int i=0; i<npid; i++)
  {

    pReducedCorrelator2EtaGap_FHCal[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_FHCal_pid%i",i));
    pReducedCorrelator2EtaGap[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_pid%i",i));
    pReducedCorrelator2[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2_pid%i",i));
    pReducedCorrelator4[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator4_pid%i",i));
    
    pv2TPC_EP[i] = (TProfile2D*)inFile->Get(Form("pv2TPC_EP_pid%i",i));
    pv2TPC_SP[i] = (TProfile2D*)inFile->Get(Form("pv2TPC_SP_pid%i",i));
    pv2FHCal_EP[i] = (TProfile2D*)inFile->Get(Form("pv2FHCal_EP_pid%i",i));
  
    pCov22RedEtaGap_FHCal[i] = (TProfile2D*)inFile->Get(Form("pCov22RedEtaGap_FHCal_pid%i",i));
    pCov22RedEtaGap[i] = (TProfile2D*)inFile->Get(Form("pCov22RedEtaGap_pid%i",i));
    pCov22Red[i] = (TProfile2D*)inFile->Get(Form("pCov22Red_pid%i",i));
    pCov24Red[i] = (TProfile2D*)inFile->Get(Form("pCov24Red_pid%i",i));
    pCov42Red[i] = (TProfile2D*)inFile->Get(Form("pCov42Red_pid%i",i));
    pCov44Red[i] = (TProfile2D*)inFile->Get(Form("pCov44Red_pid%i",i));
    pCov2Red4Red[i] = (TProfile2D*)inFile->Get(Form("pCov2Red4Red_pid%i",i));
    for (int m=0; m<nmethod; m++)
    {
      pPt[i][m] = (TProfile2D*)inFile->Get(Form("pPt_pid%i_meth%i",i,m));
    }
    
  }

  TProfile *pReducedCorrelator2EtaGap_FHCal_cent[npid][n_cent_bins];
  TProfile *pReducedCorrelator2EtaGap_cent[npid][n_cent_bins];
  TProfile *pReducedCorrelator2_cent[npid][n_cent_bins];
  TProfile *pReducedCorrelator4_cent[npid][n_cent_bins];
  TProfile *pv2TPC_EP_cent[npid][n_cent_bins];
  TProfile *pv2TPC_SP_cent[npid][n_cent_bins];
  TProfile *pv2FHCal_EP_cent[npid][n_cent_bins];
  TProfile *pCov22RedEtaGap_FHCal_cent[npid][n_cent_bins];
  TProfile *pCov22RedEtaGap_cent[npid][n_cent_bins];
  TProfile *pCov22Red_cent[npid][n_cent_bins];
  TProfile *pCov24Red_cent[npid][n_cent_bins];
  TProfile *pCov42Red_cent[npid][n_cent_bins];
  TProfile *pCov44Red_cent[npid][n_cent_bins];
  TProfile *pCov2Red4Red_cent[npid][n_cent_bins];
  TProfile *pPt_cent[npid][nmethod][n_cent_bins];
  std::pair<int, int> cent_bins;
  // TProfile2D *tmp;
  for (int i = 0; i < npid; i++)
  {
    // cout << "id=" << i << endl;
    for (int c = 0; c < n_cent_bins; c++)
    {
      cent_bins.first  = pv2TPC_EP[i]->GetYaxis()->FindBin(centRange.at(c).first);
      cent_bins.second = pv2TPC_EP[i]->GetYaxis()->FindBin(centRange.at(c).second - 1.);

      // tmp = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_FHCal_pid%i",i));
      // pReducedCorrelator2EtaGap_FHCal_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_pid%i",i));
      // pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2_pid%i",i));
      // pReducedCorrelator2_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pReducedCorrelator4_pid%i",i));
      // pReducedCorrelator4_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pv2TPC_EP_pid%i",i));
      // pv2TPC_EP_cent[i][c]  = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pv2TPC_SP_pid%i",i));
      // pv2TPC_SP_cent[i][c]  = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pv2FHCal_EP_pid%i",i));
      // pv2FHCal_EP_cent[i][c]  = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov22RedEtaGap_FHCal_pid%i",i));
      // pCov22RedEtaGap_FHCal_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov22RedEtaGap_pid%i",i));
      // pCov22RedEtaGap_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov22Red_pid%i",i));
      // pCov22Red_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov24Red_pid%i",i));
      // pCov24Red_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov42Red_pid%i",i));
      // pCov42Red_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov44Red_pid%i",i));
      // pCov44Red_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      // tmp = (TProfile2D*)inFile->Get(Form("pCov2Red4Red_pid%i",i));
      // pCov2Red4Red_cent[i][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);

      pReducedCorrelator2EtaGap_FHCal_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap_FHCal[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2EtaGap_FHCal[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2EtaGap[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pReducedCorrelator2_cent[i][c] = (TProfile*)pReducedCorrelator2[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pReducedCorrelator4_cent[i][c] = (TProfile*)pReducedCorrelator4[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator4[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pv2TPC_EP_cent[i][c]  = (TProfile*)pv2TPC_EP[i]->ProfileX(Form("%s_cent%i",pv2TPC_EP[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pv2TPC_SP_cent[i][c]  = (TProfile*)pv2TPC_SP[i]->ProfileX(Form("%s_cent%i",pv2TPC_SP[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pv2FHCal_EP_cent[i][c]  = (TProfile*)pv2FHCal_EP[i]->ProfileX(Form("%s_cent%i",pv2FHCal_EP[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov22RedEtaGap_FHCal_cent[i][c] = (TProfile*)pCov22RedEtaGap_FHCal[i]->ProfileX(Form("%s_cent%i",pCov22RedEtaGap_FHCal[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov22RedEtaGap_cent[i][c] = (TProfile*)pCov22RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov22RedEtaGap[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov22Red_cent[i][c] = (TProfile*)pCov22Red[i]->ProfileX(Form("%s_cent%i",pCov22Red[i]->GetName(),c), cent_bins.first, cent_bins.second);
      pCov24Red_cent[i][c] = (TProfile*)pCov24Red[i]->ProfileX(Form("%s_cent%i",pCov24Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 
      pCov42Red_cent[i][c] = (TProfile*)pCov42Red[i]->ProfileX(Form("%s_cent%i",pCov42Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 
      pCov44Red_cent[i][c] = (TProfile*)pCov44Red[i]->ProfileX(Form("%s_cent%i",pCov44Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 
      pCov2Red4Red_cent[i][c] = (TProfile*)pCov2Red4Red[i]->ProfileX(Form("%s_cent%i",pCov2Red4Red[i]->GetName(),c), cent_bins.first, cent_bins.second); 

      pReducedCorrelator2EtaGap_FHCal_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap_FHCal_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator2EtaGap_FHCal_cent[i][c]->GetName(), &pt_binning[0]);
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator2EtaGap_cent[i][c]->GetName(), &pt_binning[0]);
      pReducedCorrelator2_cent[i][c] = (TProfile*)pReducedCorrelator2_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator2_cent[i][c]->GetName(), &pt_binning[0]);
      pReducedCorrelator4_cent[i][c] = (TProfile*)pReducedCorrelator4_cent[i][c]->Rebin(n_pt_bins,pReducedCorrelator4_cent[i][c]->GetName(), &pt_binning[0]);
      pv2TPC_EP_cent[i][c]  = (TProfile*)pv2TPC_EP_cent[i][c]->Rebin(n_pt_bins,pv2TPC_EP_cent[i][c]->GetName(), &pt_binning[0]);
      pv2TPC_SP_cent[i][c]  = (TProfile*)pv2TPC_SP_cent[i][c]->Rebin(n_pt_bins,pv2TPC_SP_cent[i][c]->GetName(), &pt_binning[0]);
      pv2FHCal_EP_cent[i][c]  = (TProfile*)pv2FHCal_EP_cent[i][c]->Rebin(n_pt_bins,pv2FHCal_EP_cent[i][c]->GetName(), &pt_binning[0]);
      pCov22RedEtaGap_FHCal_cent[i][c] = (TProfile*)pCov22RedEtaGap_FHCal_cent[i][c]->Rebin(n_pt_bins,pCov22RedEtaGap_FHCal_cent[i][c]->GetName(), &pt_binning[0]);
      pCov22RedEtaGap_cent[i][c] = (TProfile*)pCov22RedEtaGap_cent[i][c]->Rebin(n_pt_bins,pCov22RedEtaGap_cent[i][c]->GetName(), &pt_binning[0]);
      pCov22Red_cent[i][c] = (TProfile*)pCov22Red_cent[i][c]->Rebin(n_pt_bins,pCov22Red_cent[i][c]->GetName(), &pt_binning[0]);
      pCov24Red_cent[i][c] = (TProfile*)pCov24Red_cent[i][c]->Rebin(n_pt_bins,pCov24Red_cent[i][c]->GetName(), &pt_binning[0]); 
      pCov42Red_cent[i][c] = (TProfile*)pCov42Red_cent[i][c]->Rebin(n_pt_bins,pCov42Red_cent[i][c]->GetName(), &pt_binning[0]); 
      pCov44Red_cent[i][c] = (TProfile*)pCov44Red_cent[i][c]->Rebin(n_pt_bins,pCov44Red_cent[i][c]->GetName(), &pt_binning[0]); 
      pCov2Red4Red_cent[i][c] = (TProfile*)pCov2Red4Red_cent[i][c]->Rebin(n_pt_bins,pCov2Red4Red_cent[i][c]->GetName(), &pt_binning[0]);
      for (int m=0; m<nmethod; m++)
      {
        // tmp = (TProfile2D*)inFile->Get(Form("pPt_pid%i_meth%i",i,m));
        // pPt_cent[i][m][c] = (TProfile*)tmp->ProfileX(Form("%s_cent%i",tmp->GetName(),c), cent_bins.first, cent_bins.second);
      pPt_cent[i][m][c] = (TProfile*)pPt[i][m]->ProfileX(Form("%s_cent%i",pPt[i][m]->GetName(),c), cent_bins.first, cent_bins.second);

        pPt_cent[i][m][c] = (TProfile*)pPt_cent[i][m][c]->Rebin(n_pt_bins,pPt_cent[i][m][c]->GetName(), &pt_binning[0]);
      }
    }
  }

  // OUTPUT
  TGraphErrors *grDifFl[nmethod][ncent][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  TGraphErrors *grDifFl1040[nmethod][npid];

  // //==========================================================================================================================
  // if(bMergeCharged){
  //   for (int icent=0;icent<ncent;icent++){
  //     for (int ipt=0;ipt<npt;ipt++){
  //       for (int id=0;id<npid/2;id++){
  //         hv2EP[icent][ipt][id] -> Add(hv2EP[icent][ipt][id+4]);
  //         hPT[icent][ipt][id] -> Add(hPT[icent][ipt][id+4]);
  //         hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id+4]);
  //         hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id+4]);
  //         hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id+4]);
  //         hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id+4]);
  //         hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id+4]);
  //         hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id+4]);
  //         hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id+4]);
  //         hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id+4]);
  //         hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id+4]);
  //         hcounter[icent][ipt][id] -> Add(hcounter[icent][ipt][id+4]);
  //       }
  //     }
  //   }
  // }
  //==========================================================================================================================
  /*
  // Filling pT bin
  double pt[ncent][npt];
  double ept[ncent][npt]={{0}}; // error bin pT = 0.0
  for (int icent=0; icent<ncent; icent++){
    for (int ipt=0; ipt<npt; ipt++){
      // pt[icent][ipt] = hPT[icent][ipt] -> GetBinContent(1);
      pt[icent][ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
    }
  }
  */
  //==========================================================================================================================
  TProfile *prV22dif1040[npt][npid], *prV24dif1040[npt][npid], *prV22FHCaldif1040[npt][npid], *prV22dif1040Gap[npt][npid], *pt1040[npt][npid]; // TProfile for differential flow of 10-40% centrality bin
  for (int ipt=0;ipt<npt;ipt++){
    for (int id=0;id<npid;id++){
      prV22dif1040[ipt][id]=new TProfile(Form("prV22dif1040_%i_%i",ipt,id),"",1,0.,1.);
      prV24dif1040[ipt][id]=new TProfile(Form("prV24dif1040_%i_%i",ipt,id),"",1,0.,1.);
      prV22FHCaldif1040[ipt][id]=new TProfile(Form("prV22FHCaldif1040_%i_%i",ipt,id),"",1,0.,1.);
      prV22dif1040Gap[ipt][id]=new TProfile(Form("prV22dif1040Gap_%i_%i",ipt,id),"",1,0.,1.);
      pt1040[ipt][id]=new TProfile(Form("pt1040_%i_%i",ipt,id),"",1,0.,1.);
    }
  }

  TProfile *pV2DifCent1040[npid][nmethod];
  for (int id=0;id<npid;id++){
    for (int meth=0; meth<nmethod; meth++){
      pV2DifCent1040[id][meth] = new TProfile(Form("pV2DifCent1040_id%i_meth%i",id,meth),"",npt,0.,npt);
    }
  }
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC,FHCal
    term cor2GapFHCal = term(pCorrelator2EtaGap_FHCal,icent);
    double v22GapFHCal = sqrt(cor2GapFHCal.mVal);
    double ev22GapFHCal = sqrt(1./(4.*cor2GapFHCal.mVal)*cor2GapFHCal.mMSE);

    // 2QC Gapped
    term cor2Gap = term(pCorrelator2EtaGap,icent);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);

    // 2QC
    term cor2 = term(pCorrelator2,icent);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(pCorrelator4,icent);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4,icent,icent,icent);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    
    for (int id=0;id<npid;id++){

      std::vector <double> vV22DifGapFHCal, vV22DifGap, vV22Dif, vV24Dif, vV2EPDif, vV2SPDif, vV2FHCalEPDif, vPt;
      std::vector <double> eV22DifGapFHCal, eV22DifGap, eV22Dif, eV24Dif, eV2EPDif, eV2SPDif, eV2FHCalEPDif, ePt;

      // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        vPt.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
        ePt.push_back(0);



        // 2QC,FHCal
        term cor2redGapFHCal = term(pReducedCorrelator2EtaGap_FHCal_cent[id][icent],ipt);
        double v22DifGapFHCal = cor2redGapFHCal.mVal/v22GapFHCal;
        double cov22primeGapFHCal = Covariance(pCov22RedEtaGap_FHCal_cent[id][icent],pCorrelator2EtaGap_FHCal,pReducedCorrelator2EtaGap_FHCal_cent[id][icent],ipt,icent,ipt);
        double ev22DifGapFHCal = sqrt(0.25*pow(cor2GapFHCal.mVal,-3)*(pow(cor2redGapFHCal.mVal,2)*cor2GapFHCal.mMSE
                            + 4*pow(cor2GapFHCal.mVal,2)*cor2redGapFHCal.mMSE - 4*cor2GapFHCal.mVal*cor2redGapFHCal.mVal*cov22primeGapFHCal));
        vV22DifGapFHCal.push_back(v22DifGapFHCal);
        eV22DifGapFHCal.push_back(ev22DifGapFHCal);

        // 2QC,eta-gap,TPC
        term cor2redGap = term(pReducedCorrelator2EtaGap_cent[id][icent],ipt);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(pCov22RedEtaGap_cent[id][icent],pCorrelator2EtaGap,pReducedCorrelator2EtaGap_cent[id][icent],ipt,icent,ipt);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        vV22DifGap.push_back(v22DifGap);
        eV22DifGap.push_back(ev22DifGap);

        // v22
        term cor2red = term(pReducedCorrelator2_cent[id][icent],ipt);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(pCov22Red_cent[id][icent],pCorrelator2,pReducedCorrelator2_cent[id][icent],ipt,icent,ipt);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        vV22Dif.push_back(v22Dif);
        eV22Dif.push_back(ev22Dif);
        
        // v24
        term cor4red = term(pReducedCorrelator4_cent[id][icent],ipt);
        double cov24prime = Covariance(pCov24Red_cent[id][icent],pCorrelator2,pReducedCorrelator4_cent[id][icent],ipt,icent,ipt);
        double cov42prime = Covariance(pCov42Red_cent[id][icent],pCorrelator4,pReducedCorrelator2_cent[id][icent],ipt,icent,ipt);
        double cov44prime = Covariance(pCov44Red_cent[id][icent],pCorrelator4,pReducedCorrelator4_cent[id][icent],ipt,icent,ipt);
        double cov2prime4prime = Covariance(pCov2Red4Red_cent[id][icent],pReducedCorrelator2_cent[id][icent],pReducedCorrelator4_cent[id][icent],ipt,ipt,ipt);
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
        vV24Dif.push_back(v24Dif);
        eV24Dif.push_back(ev24Dif);

        // TPC, EP
        double res2EP = sqrt(pResTPC_EP->GetBinContent(icent+1));
        double v2obsEP = pv2TPC_EP_cent[id][icent]->GetBinContent(ipt+1);
        double v2EP = v2obsEP / res2EP;
        // double v2EP = v2obsEP;
        double ev2EP = pv2TPC_EP_cent[id][icent]->GetBinError(ipt+1) / res2EP;
        vV2EPDif.push_back(v2EP);
        eV2EPDif.push_back(ev2EP);

        // TPC, SP
        double res2SP = sqrt(pResTPC_SP->GetBinContent(icent+1));
        double v2obsSP = pv2TPC_SP_cent[id][icent]->GetBinContent(ipt+1);
        double v2SP = v2obsSP / res2SP;
        // double v2EP = v2obsEP;
        double ev2SP = pv2TPC_SP_cent[id][icent]->GetBinError(ipt+1) / res2SP;
        vV2SPDif.push_back(v2SP);
        eV2SPDif.push_back(ev2SP);

        // FHCal, EP
        // double res1EP_FHCal = sqrt(pResFHCal_EP->GetBinContent(icent+1));
        double res1EP_FHCal = 1.;
        double v2obsEP_FHCal = pv2FHCal_EP_cent[id][icent]->GetBinContent(ipt+1);
        if (icent==4 && id==0) cout << v2obsEP_FHCal << endl;
        double v2FHCalEPDif = v2obsEP_FHCal / res1EP_FHCal;
        double ev2FHCalEP = pv2FHCal_EP_cent[id][icent]->GetBinError(ipt+1) / res1EP_FHCal;

        vV2FHCalEPDif.push_back(v2FHCalEPDif);
        eV2FHCalEPDif.push_back(v2FHCalEPDif);

        // Fill TProfile of v2 vs. cent
        prV22FHCalint[icent][id] -> Fill(0.5,v2EP,pPt_cent[id][0][icent] -> GetBinEntries(ipt+1));
        prV22intGap[icent][id] -> Fill(0.5,v22DifGap,pPt_cent[id][1][icent] -> GetBinEntries(ipt+1));
        prV22int[icent][id] -> Fill(0.5,v22Dif,pPt_cent[id][2][icent] -> GetBinEntries(ipt+1));
        prV24int[icent][id] -> Fill(0.5,v24Dif,pPt_cent[id][3][icent] -> GetBinEntries(ipt+1));
        
        pV2Integrated[id][0] -> Fill(0.5+icent, v22DifGapFHCal, pPt_cent[id][0][icent] -> GetBinEntries(ipt+1));
        pV2Integrated[id][1] -> Fill(0.5+icent, v22DifGap,      pPt_cent[id][1][icent] -> GetBinEntries(ipt+1));
        pV2Integrated[id][2] -> Fill(0.5+icent, v22Dif,         pPt_cent[id][2][icent] -> GetBinEntries(ipt+1));
        pV2Integrated[id][3] -> Fill(0.5+icent, v24Dif,         pPt_cent[id][3][icent] -> GetBinEntries(ipt+1));
        pV2Integrated[id][4] -> Fill(0.5+icent, v2EP,           pPt_cent[id][4][icent] -> GetBinEntries(ipt+1));
        pV2Integrated[id][5] -> Fill(0.5+icent, v2SP,           pPt_cent[id][5][icent] -> GetBinEntries(ipt+1));
        pV2Integrated[id][6] -> Fill(0.5+icent, v2FHCalEPDif,   pPt_cent[id][6][icent] -> GetBinEntries(ipt+1));


        // Fill TProfile of v2 vs. pt cent 10-40%
        if (icent>=1 && icent <=3) { // 10-40%
          prV22FHCaldif1040[ipt][id]->Fill(0.5,v2EP,pPt_cent[id][0][icent] -> GetBinEntries(ipt+1));
          prV22dif1040Gap[ipt][id]->Fill(0.5,v22DifGap,pPt_cent[id][1][icent] -> GetBinEntries(ipt+1));
          prV22dif1040[ipt][id]->Fill(0.5,v22Dif,pPt_cent[id][2][icent] -> GetBinEntries(ipt+1));
          prV24dif1040[ipt][id]->Fill(0.5,v24Dif,pPt_cent[id][3][icent] -> GetBinEntries(ipt+1));
          pt1040[ipt][id]->Fill(0.5,pPt_cent[id][0][icent]->GetBinContent(ipt+1),pPt_cent[id][0][icent]->GetBinEntries(ipt+1));

          pV2DifCent1040[id][0] -> Fill(0.5+ipt, v22DifGapFHCal, pPt_cent[id][0][icent] -> GetBinEntries(ipt+1));
          pV2DifCent1040[id][1] -> Fill(0.5+ipt, v22DifGap,      pPt_cent[id][1][icent] -> GetBinEntries(ipt+1));
          pV2DifCent1040[id][2] -> Fill(0.5+ipt, v22Dif,         pPt_cent[id][2][icent] -> GetBinEntries(ipt+1));
          pV2DifCent1040[id][3] -> Fill(0.5+ipt, v24Dif,         pPt_cent[id][3][icent] -> GetBinEntries(ipt+1));
          pV2DifCent1040[id][4] -> Fill(0.5+ipt, v2EP,           pPt_cent[id][4][icent] -> GetBinEntries(ipt+1));
          pV2DifCent1040[id][5] -> Fill(0.5+ipt, v2SP,           pPt_cent[id][5][icent] -> GetBinEntries(ipt+1));
          pV2DifCent1040[id][6] -> Fill(0.5+ipt, v2FHCalEPDif,   pPt_cent[id][6][icent] -> GetBinEntries(ipt+1));

        }

      } // end of loop for all pT bin
      // 2QC,FHCal; 2QC,eta-gap; 2QC; 4QC; TPC,EP; TPC,SP; FHCal,EP
      grDifFl[0][icent][id] = new TGraphErrors(npt, &vPt[0], &vV22DifGapFHCal[0], &ePt[0], &eV22DifGapFHCal[0]);
      grDifFl[1][icent][id] = new TGraphErrors(npt, &vPt[0], &vV22DifGap[0],      &ePt[0], &eV22DifGap[0]);
      grDifFl[2][icent][id] = new TGraphErrors(npt, &vPt[0], &vV22Dif[0],         &ePt[0], &eV22Dif[0]);
      grDifFl[3][icent][id] = new TGraphErrors(npt, &vPt[0], &vV24Dif[0],         &ePt[0], &eV24Dif[0]);
      grDifFl[4][icent][id] = new TGraphErrors(npt, &vPt[0], &vV2EPDif[0],        &ePt[0], &eV2EPDif[0]);
      grDifFl[5][icent][id] = new TGraphErrors(npt, &vPt[0], &vV2SPDif[0],        &ePt[0], &eV2SPDif[0]);
      grDifFl[6][icent][id] = new TGraphErrors(npt, &vPt[0], &vV2FHCalEPDif[0],   &ePt[0], &eV2FHCalEPDif[0]);
      

      // grDifFl[0][icent][id] -> SetMarkerColor(kBlack);
      // grDifFl[1][icent][id] -> SetMarkerColor(kBlack);
      // grDifFl[2][icent][id] -> SetMarkerColor(213);
      // grDifFl[3][icent][id] -> SetMarkerColor(209);
      // grDifFl[4][icent][id] -> SetMarkerColor(218);
      // grDifFl[5][icent][id] -> SetMarkerColor(kGreen+1);
      // grDifFl[6][icent][id] -> SetMarkerColor(kAzure+2);


      

      
      

      for (int meth=0; meth<nmethod; meth++){
        grDifFl[meth][icent][id] -> SetMarkerColor(color[meth+1]);
        grDifFl[meth][icent][id] -> SetMarkerStyle(marker[meth]); // markerStyle
        grDifFl[meth][icent][id] -> SetMarkerSize(markerSize);

        grDifFl[meth][icent][id] -> SetLineColor(color[meth+1]);
        grDifFl[meth][icent][id] -> SetLineWidth(1.);
        grDifFl[meth][icent][id] -> SetDrawOption("P");
        
      }
    } // end of loop over PID
  } // end of loop over centrality classes

  //==========================================================================================================================

  char nameV22Gap[400], nameV2EP[400];
  const char *grTitleDF[]={ "v_{2}{2,#eta-gap,FHCal};p_{T} [GeV/c];v_{2}",
                            "v_{2}{2,#eta-gap,TPC};p_{T} [GeV/c];v_{2}",
                            "v_{2}{2};p_{T} [GeV/c];v_{2}",
                            "v_{2}{4};p_{T} [GeV/c];v_{2}",
                            "v_{2}^{EP}{#Psi_{2,TPC}};p_{T} [GeV/c];v_{2}",
                            "v_{2}^{SP}{Q_{2,TPC}};p_{T} [GeV/c];v_{2}",
                            "v_{2}^{EP}{#Psi_{1,FHCal}};p_{T} [GeV/c];v_{2}"};
  outFile -> cd();
  for (int imethod=0; imethod<nmethod; imethod++){
    for (int icent=0;icent<ncent;icent++){
      for (int id=0;id<npid;id++){
        if (bMergeCharged && id>3) continue; // if joining positively charged particles with negatively then id=0,1,2,3
        // grDifFl[imethod][icent][id] -> SetTitle(Form("V2 vs. pT, %s, centrality %1.0f-%1.0f%%, %s",pidNames.at(id).Data(),icent*10,(icent+1)*10,grTitleDF[imethod]));
        grDifFl[imethod][icent][id] -> SetTitle(grTitleDF[imethod]);
        grDifFl[imethod][icent][id] -> Write(Form("gr_cent%i_%i_%i",icent,imethod,id));
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[ncent][npid];
  for (int icent=0; icent<ncent; icent++){
    for (int id=0;id<npid;id++){
      vgrv2pt[icent][id].push_back(grDifFl[ratioToMethod][icent][id]);
      for (int i=0; i<nmethod; i++){
        if (i==excludeMethod) continue;
        if (i==ratioToMethod) continue;
        vgrv2pt[icent][id].push_back(grDifFl[i][icent][id]);
      }
    }
  }
  TCanvas *cV2PT[ncent][npid];
  for (int icent=0; icent<drawDifferentialFlowTill; icent++){
    for (int id=0;id<npid;id++){
      if (bMergeCharged && id>3) continue; // if joining positively charged particles with negatively then id=0,1,2,3
      
      if (icent<drawDifferentialFlowTill) {
        sprintf(hname,"%s, %1.0f-%1.0f%%",pidFancyNames.at(id).Data(),centRange.at(icent).first,centRange.at(icent).second);
        cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",rangeRatio.at(icent).first, rangeRatio.at(icent).second, minpt, maxpt, minV2dif, maxV2dif,
                                                 coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                 level.Data(), hname);
      }else{
        sprintf(hname,"%1.0f-%1.0f%%",centRange.at(icent).first,centRange.at(icent).second);
        cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",rangeRatio.at(icent).first, rangeRatio.at(icent).second, minpt, maxpt, minV2dif, maxV2dif,
                                                 coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                 "", hname,0);
      }
      cV2PT[icent][id] -> SetName(hname);
      if (saveAsPNG) cV2PT[icent][id] -> SaveAs(Form("./%s/%sDFCent%1.0f-%1.0f.png",outDirName.Data(),pidNames.at(id).Data(),centRange.at(icent).first,centRange.at(icent).second));
    }
  }

  
  TCanvas *cV2PT1040[npid];
  for (int id=0;id<npid;id++){
    if (bMergeCharged && id>3) continue; // if joining positively charged particles with negatively then id=0,1,2,3
    // vector <double> vV22Dif1040, vV24Dif1040, vV2EPDif1040, vV22GapDif1040, vPT;
    // for (int ipt=0;ipt<npt;ipt++){
    //   vV22Dif1040.push_back(prV22dif1040[ipt][id]->GetBinContent(1));
    //   vV24Dif1040.push_back(prV24dif1040[ipt][id]->GetBinContent(1));
    //   vV2EPDif1040.push_back(prV22FHCaldif1040[ipt][id]->GetBinContent(1));
    //   vV22GapDif1040.push_back(prV22dif1040Gap[ipt][id]->GetBinContent(1));
    //   // vPT.push_back(pt1040[ipt][id]->GetBinContent(1));
    //   vPT.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
    // }
    // grDifFl1040[0][id] = new TGraphErrors(npt,&vPT[0],&vV22Dif1040[0],&ePT[0],eV22cent1040[id]);
    // grDifFl1040[0][id] -> SetMarkerColor(kRed);
    // grDifFl1040[0][id] -> SetMarkerStyle(marker[0]);
    // // 4QC differential flow
    // grDifFl1040[1][id] = new TGraphErrors(npt,&vPT[0],&vV24Dif1040[0],&ePT[0],eV24cent1040[id]);
    // grDifFl1040[1][id] -> SetMarkerColor(kGreen+1);
    // grDifFl1040[1][id] -> SetMarkerStyle(marker[1]);
    // // EP differential flow
    // grDifFl1040[2][id] = new TGraphErrors(npt,&vPT[0],&vV2EPDif1040[0],&ePT[0],eV2EPcent1040[id]);
    // grDifFl1040[2][id] -> SetMarkerColor(kAzure+2);
    // grDifFl1040[2][id] -> SetMarkerStyle(marker[2]);
    // // v2 gapped
    // grDifFl1040[3][id] = new TGraphErrors(npt,&vPT[0],&vV22GapDif1040[0],&ePT[0],eV22Gapcent1040[id]);
    // grDifFl1040[3][id] -> SetMarkerColor(kAzure+2);
    // grDifFl1040[3][id] -> SetMarkerStyle(marker[3]);

    double v2Dif[nmethod][npt]={{0.}};
    double ePT[npt]={0.};
    vector <double> vPT;
    for (int ipt=0; ipt<npt; ipt++) vPT.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
    for (int meth=0; meth<nmethod; meth++){
      for (int ipt=0; ipt<npt; ipt++){
        v2Dif[meth][ipt] = pV2DifCent1040[id][meth] -> GetBinContent(1+ipt);
      }
      grDifFl1040[meth][id] = new TGraphErrors(npt,&vPT[0],&v2Dif[meth][0],&ePT[0],&eV2Cent1040[id][meth][0]);
    }

    for (int meth=0; meth<nmethod; meth++){
      grDifFl1040[meth][id] -> SetMarkerColor(color[meth+1]);
      grDifFl1040[meth][id] -> SetMarkerStyle(marker[meth]); // markerStyle
      grDifFl1040[meth][id] -> SetMarkerSize(markerSize);

      grDifFl1040[meth][id] -> SetLineColor(color[meth+1]);
      grDifFl1040[meth][id] -> SetLineWidth(1.);
      grDifFl1040[meth][id] -> SetDrawOption("P");
    }

    std::vector<TGraphErrors*> vgrv2pt1040;
    for (int imeth=0; imeth<nmethod; imeth++){
      // grDifFl1040[imeth][id] -> SetTitle(Form("V2 vs. pT, %s, centrality 10-40%%, %s",pidNames.at(id).Data(),grTitleDF[imeth]));
      grDifFl1040[imeth][id] -> SetTitle(grTitleDF[imeth]);
      grDifFl1040[imeth][id] -> Write(Form("gr_cent10-40_%i_%i",imeth,id));
    }
    vgrv2pt1040.push_back(grDifFl1040[ratioToMethod][id]);
    for (int imeth=0;imeth<nmethod;imeth++){
      if (imeth==excludeMethod) continue;
      if (imeth==ratioToMethod) continue;
      vgrv2pt1040.push_back(grDifFl1040[imeth][id]);
    }
    
    
    sprintf(hname,"10-40%%, %s",pidFancyNames.at(id).Data());

    cV2PT1040[id] = (TCanvas*) DrawTGraph(vgrv2pt1040,"",rangeRatio.at(ncent).first, rangeRatio.at(ncent).second, minpt, maxpt, minV2dif, maxV2dif,
                                          coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                          level.Data(), hname);
    cV2PT1040[id] -> SetName(hname);
    if (saveAsPNG) cV2PT1040[id] -> SaveAs(Form("./%s/%sDFCent10-40.png",outDirName.Data(),pidNames.at(id).Data()));
  }

  delete pCorrelator2EtaGap_FHCal;
  delete pCorrelator2EtaGap;
  delete pCorrelator2;
  delete pCorrelator4;
  
  delete pResTPC_EP;
  delete pResTPC_SP;
  delete pResFHCal_EP;
  delete pCov24;
  for (int i=0; i<npid; i++)
  {
    delete pReducedCorrelator2EtaGap_FHCal[i];
    delete pReducedCorrelator2EtaGap[i];
    delete pReducedCorrelator2[i];
    delete pReducedCorrelator4[i];
    
    delete pv2TPC_EP[i];
    delete pv2TPC_SP[i];
    delete pv2FHCal_EP[i];
  
    delete pCov22RedEtaGap_FHCal[i];
    delete pCov22RedEtaGap[i];
    delete pCov22Red[i];
    delete pCov24Red[i];
    delete pCov42Red[i];
    delete pCov44Red[i];
    delete pCov2Red4Red[i];

    for (int c=0;c<n_cent_bins; c++){
    delete pReducedCorrelator2EtaGap_FHCal_cent[i][c];
    delete pReducedCorrelator2EtaGap_cent[i][c];
    delete pReducedCorrelator2_cent[i][c];
    delete pReducedCorrelator4_cent[i][c];
    delete pv2TPC_EP_cent[i][c];
    delete pv2TPC_SP_cent[i][c];
    delete pv2FHCal_EP_cent[i][c];
    delete pCov22RedEtaGap_FHCal_cent[i][c];
    delete pCov22RedEtaGap_cent[i][c];
    delete pCov22Red_cent[i][c];
    delete pCov24Red_cent[i][c];
    delete pCov42Red_cent[i][c];
    delete pCov44Red_cent[i][c];
    delete pCov2Red4Red_cent[i][c];
    }
  }

  inFile->Close();
}

void v2plot_integrated_flow_for_CH(){ // v2int = v2 reference
  // if (!bMergeCharged) { 
  //   // if one doesn't merge CH(+) with CH(-), then this function can't be used 
  //   // due to the fact that reference flow includes both CH+ and CH-
  //   return;
  // }

  TFile *inFile = new TFile(inFileName.Data(),"read");

  // Histogram input

  TProfile *pCorrelator2EtaGap_FHCal = (TProfile*)inFile->Get("pCorrelator2EtaGap_FHCal");
  TProfile *pCorrelator2EtaGap = (TProfile*)inFile->Get("pCorrelator2EtaGap");
  TProfile *pCorrelator2 = (TProfile*)inFile->Get("pCorrelator2");
  TProfile *pCorrelator4 = (TProfile*)inFile->Get("pCorrelator4");
  TProfile *pCov24 = (TProfile*)inFile->Get("pCov24");

  TGraphErrors *grIntFlowVsCent[nmethod-3];
  TCanvas *can;


  std::vector<double> vV2EP, vV22, vV24, vV22int, vV24int, vV22Gap, vV22Gapint, vV22GapFHCalint;
  std::vector<double> eV2EP, eV22, eV24, eV22int, eV24int, eV22Gap, eV22Gapint, eV22GapFHCalint;

  for (int icent=0;icent<ncent;icent++){

    // // EP
    // vV2EP.push_back( hv22EP[icent][0]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
    // eV2EP.push_back( hv22EP[icent][0]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
    // 2QC
    term cor2 = term(pCorrelator2,icent);
    vV22.push_back(sqrt(cor2.mVal));
    eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
    // 4QC
    term cor4 = term(pCorrelator4,icent);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4,icent,icent,icent);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    vV24.push_back(v24);
    eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );

    // 2QC,eta-gap,FHCal
    term cor2GapFHCal = term(pCorrelator2EtaGap_FHCal,icent);
    vV22GapFHCalint.push_back(sqrt(cor2GapFHCal.mVal));
    eV22GapFHCalint.push_back(sqrt(1./(4.*cor2GapFHCal.mVal)*cor2GapFHCal.mMSE));

    // 2QC,eta-gap,TPC
    term cor2Gap = term(pCorrelator2EtaGap,icent);
    vV22Gap.push_back(sqrt(cor2Gap.mVal));
    eV22Gap.push_back(sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE));

    // Checking if there are differences with v2plot_integrated_flow_for_PID() or not
    // cout << icent <<" "<<vV22Gap.at(icent)<<" "<< eV22Gap.at(icent) <<endl;
    // cout << icent <<" "<<vV24.at(icent)<<" "<< eV24.at(icent) <<endl;
    // cout << icent <<" "<<vV22.at(icent)<<" "<< eV22.at(icent) <<endl;
    // cout << icent <<" "<<vV22.at(icent)<<" "<< prV22int[icent][0]->GetBinContent(1)<<" "<< eV22.at(icent) <<endl;
    // cout << icent <<" "<<vV24.at(icent)<<" "<< prV24int[icent][0]->GetBinContent(1)<<" "<< eV24.at(icent) <<endl;
    // cout << icent <<" "<<vV2EP.at(icent)<<" "<< prV22FHCalint[icent][0]->GetBinContent(1)<<" "<< eV2EP.at(icent) <<endl;
    // cout << icent <<" "<<vV22Gap.at(icent)<<" "<< prV22intGap[icent][0]->GetBinContent(1)<<" "<< eV22Gap.at(icent) <<endl;
  }
  
  grIntFlowVsCent[0] = new TGraphErrors(ncent,bin_cent,&vV22[0],bin_centE,&eV22[0]);
  grIntFlowVsCent[0] -> SetMarkerColor(kRed);
  grIntFlowVsCent[0] -> SetMarkerStyle(marker[0]);

  grIntFlowVsCent[1] = new TGraphErrors(ncent,bin_cent,&vV24[0],bin_centE,&eV24[0]);
  grIntFlowVsCent[1] -> SetMarkerColor(kGreen+1);
  grIntFlowVsCent[1] -> SetMarkerStyle(marker[1]);

  // grIntFlowVsCent[2] = new TGraphErrors(ncent,bin_cent,&vV2EP[0],bin_centE,&eV2EP[0]);
  grIntFlowVsCent[2] = new TGraphErrors(ncent,bin_cent,&vV22GapFHCalint[0],bin_centE,&eV22GapFHCalint[0]);
  grIntFlowVsCent[2] -> SetMarkerColor(kAzure+2);
  grIntFlowVsCent[2] -> SetMarkerStyle(marker[2]);

  grIntFlowVsCent[3] = new TGraphErrors(ncent,bin_cent,&vV22Gap[0],bin_centE,&eV22Gap[0]);
  grIntFlowVsCent[3] -> SetMarkerColor(kYellow+2);
  grIntFlowVsCent[3] -> SetMarkerStyle(marker[3]);


  for (int i=0;i<nmethod-3;i++){
    grIntFlowVsCent[i] -> SetMarkerSize(1.5);
    grIntFlowVsCent[i] -> SetDrawOption("P");
  }
  const char *grTitle[nmethod-3]={"v_{2}{2};centrality (%);v_{2}",
                                "v_{2}{4};centrality (%);v_{2}",
                                "v_{2}{2,#eta-gap,FHCal};centrality (%);v_{2}",
                                "v_{2}{2,#eta-gap,TPC};centrality (%);v_{2}"};
  outFile -> cd();
  for (int imeth=0; imeth<nmethod-3; imeth++){
    // grIntFlowVsCent[imeth] -> SetTitle(Form("V2 vs. centrality, %s, %s",pidNames.at(0).Data(),grTitle[imeth]));
    grIntFlowVsCent[imeth] -> SetTitle(grTitle[imeth]);
    grIntFlowVsCent[imeth] -> Write(Form("grRF_%i_0",imeth));
  }

  std::vector<TGraphErrors*> vgr;
  vgr.push_back(grIntFlowVsCent[3]);
  for (int imeth=0; imeth<nmethod-4; imeth++){
    // if (imeth==excludeMethod) continue;
    vgr.push_back(grIntFlowVsCent[imeth]);
  }

  
  can = (TCanvas*) DrawTGraph(vgr,"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second,   mincent,maxcent,minV2int,maxV2int,
                                  coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                  level.Data(), Form("%s, %1.1f<p_{T}<%1.1f GeV/c",pidFancyNames.at(0).Data(),minptRFP,maxptRFP));
  can -> SetName(pidNames.at(0).Data());
  // we can extract only v2 vs centrality for charged hadrons !
  if (saveAsPNG) can -> SaveAs(Form("./%s/%sV2vsCent.png",outDirName.Data(),pidNames.at(0).Data()));

  // Clear memory
  // for (int icent=0; icent<ncent; icent++){
  //   delete HRes[icent];
  //   delete hv22[icent];
  //   delete hv24[icent];
  //   delete hcov24[icent];
  //   delete hv22Gap[icent];
  //   for (int id=0;id<npid;id++){
  //     delete hv22EP[icent][id];
  //   }
  // }
  delete inFile;

}

void v2plot_integrated_flow_for_PID(){ 
  // integrated elliptic flow calculation using integral over all pT bins of differential flow

  TFile *inFile = new TFile(inFileName.Data(),"read");
  // Input histograms
  TProfile *hv22[ncent][npid];        // profile of integrated flow from v2{2}
  TProfile *hv24[ncent][npid];        // profile of integrated flow from v2{4}
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent][npid];       // <2>*<4>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  TProfile *hv2EP[ncent][npt][npid];	// elliptic flow from EP method
  TProfile *hv22EP[ncent][npid];      
  TProfile *HRes[ncent];

  TProfile *hv22Gap[ncent][npid];
  TProfile *hv22ptGap[ncent][npt][npid];
  // Get histograms
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    
    HRes[icent] = (TProfile*)inFile->Get(Form("HRes_%i",icent));
    for (int id=0;id<npid;id++){
      // hv22EP[icent][id] = (TProfile*)inFile->Get(Form("hv22EP_%i_%i",icent,id));
    }
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv2EP[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv2EP_%i_%i_%i",icent,ipt,id));
        hv22pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

  for (int icent=0;icent<ncent;icent++){
    for (int id=0;id<npid;id++){
      hv22EP[icent][id] = (TProfile*) hv2EP[icent][0][id]->Clone();
      hv22[icent][id] = (TProfile*) hv22pt[icent][0][id]->Clone();
      hv24[icent][id] = (TProfile*) hv24pt[icent][0][id]->Clone();
      hcov24[icent][id] = (TProfile*) hcov2prime4prime[icent][0][id]->Clone();
      hv22Gap[icent][id] = (TProfile*) hv22ptGap[icent][0][id]->Clone();
      for (int ipt=1;ipt<npt;ipt++){
        hv22EP[icent][id]->Add(hv2EP[icent][ipt][id]);
        hv22[icent][id]->Add(hv22pt[icent][ipt][id]);
        hv24[icent][id]->Add(hv24pt[icent][ipt][id]);
        hcov24[icent][id]->Add(hcov2prime4prime[icent][ipt][id]);
        hv22Gap[icent][id]->Add(hv22ptGap[icent][ipt][id]);
      }
    }
  }
  if (bMergeCharged){
    for (int icent=0;icent<ncent;icent++){
      for (int id=0;id<npid/2;id++){
        hv22EP[icent][id]->Add(hv22EP[icent][id+4]);
        hv22[icent][id]->Add(hv22[icent][id+4]);
        hv24[icent][id]->Add(hv24[icent][id+4]);
        hcov24[icent][id]->Add(hcov24[icent][id+4]);
        hv22Gap[icent][id]->Add(hv22Gap[icent][id+4]);
      }
    }  
  }
  TGraphErrors *grIntFlowVsCent[nmethod][npid];
  TCanvas *can[npid];
  for (int id=0;id<npid;id++){
    if (bMergeCharged && (id>3 || id==0)) continue; // if one merges CH+ with CH- then V2vsCentrality of CH (id=0) will be calculated by previous function
    std::vector<double> vV2EP, vV22, vV24, vV22int, vV24int, vV22Gap, vV22Gapint, vV2EPint;
    std::vector<double> eV2EP, eV22, eV24, eV22int, eV24int, eV22Gap, eV22Gapint;

    for (int icent=0;icent<ncent;icent++){

      // EP
      vV2EP.push_back( hv22EP[icent][id]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
      eV2EP.push_back( hv22EP[icent][id]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
      // 2QC
      term cor2 = term(hv22[icent][id]);
      vV22.push_back(sqrt(cor2.mVal)); // not in used
      eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
      // 4QC
      term cor4 = term(hv24[icent][id]);
      double cov24 = Covariance(hcov24[icent][id],hv22[icent][id],hv24[icent][id]);
      double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
      vV24.push_back(v24); // not in used
      eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );
  
      vV22int.push_back(prV22int[icent][id]->GetBinContent(1));
      vV24int.push_back(prV24int[icent][id]->GetBinContent(1));
      vV22Gapint.push_back(prV22intGap[icent][id]->GetBinContent(1));
      vV2EPint.push_back(prV22FHCalint[icent][id]->GetBinContent(1));
      term cor2Gap = term(hv22Gap[icent][id]);
      vV22Gap.push_back(sqrt(cor2Gap.mVal)); // not in used
      eV22Gap.push_back(sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE));

      // Checking if there are differences of vV2{x} & vV2{X}int 
      if (id==3) { // PID: 0,1,2,3: CH,Pions,Kaons, protons & antiprotons
        // cout << icent <<" "<<vV22.at(icent)<<" "<< vV22int.at(icent)<<" "<< eV22.at(icent)<<endl;
        // cout << icent <<" "<<vV24.at(icent)<<" "<< vV24int.at(icent)<<" "<< eV24.at(icent)<<endl; // discrepancy ~3% for mid-central collisions, >10% for the rest
        // cout << icent <<" "<<vV2EP.at(icent)<<" "<< vV2EPint.at(icent)<<" "<< eV2EP.at(icent)<<endl; // Both pt-bin merging method and integral over pt-bin method of integrated flow measurements give the same results for v2{eta-sub} ! 
        // cout << icent <<" "<<vV22Gap.at(icent)<<" "<< vV22Gapint.at(icent)<<" "<< eV22Gap.at(icent)<<endl; // discrepancy approximately 2% at central collisions, >10% at peripheral collisions 
      }
    }
    
    // grIntFlowVsCent[0][id] = new TGraphErrors(ncent,bin_cent,&vV22[0],bin_centE,&eV22[0]); // v2int = mergence pt bin 
    grIntFlowVsCent[0][id] = new TGraphErrors(ncent,bin_cent,&vV22int[0],bin_centE,&eV22[0]); // v2int = integral over pT of differential v2
    grIntFlowVsCent[0][id] -> SetMarkerColor(kRed);
    grIntFlowVsCent[0][id] -> SetMarkerStyle(marker[0]);

    // grIntFlowVsCent[1][id] = new TGraphErrors(ncent,bin_cent,&vV24[0],bin_centE,&eV24[0]); // v2int = mergence pt bin 
    grIntFlowVsCent[1][id] = new TGraphErrors(ncent,bin_cent,&vV24int[0],bin_centE,&eV24[0]); // v2int = integral over pT of differential v2
    grIntFlowVsCent[1][id] -> SetMarkerColor(kGreen+1);
    grIntFlowVsCent[1][id] -> SetMarkerStyle(marker[1]);

    grIntFlowVsCent[2][id] = new TGraphErrors(ncent,bin_cent,&vV2EP[0],bin_centE,&eV2EP[0]); // same results
    // grIntFlowVsCent[2][id] = new TGraphErrors(ncent,bin_cent,&vV2EPint[0],bin_centE,&eV2EP[0]); // same results
    grIntFlowVsCent[2][id] -> SetMarkerColor(kAzure+2);
    grIntFlowVsCent[2][id] -> SetMarkerStyle(marker[2]);

    // grIntFlowVsCent[3][id] = new TGraphErrors(ncent,bin_cent,&vV22Gap[0],bin_centE,&eV22Gap[0]); // v2int = mergence pt bin 
    grIntFlowVsCent[3][id] = new TGraphErrors(ncent,bin_cent,&vV22Gapint[0],bin_centE,&eV22Gap[0]); // v2int = integral over pT of differential v2
    grIntFlowVsCent[3][id] -> SetMarkerColor(kYellow+2);
    grIntFlowVsCent[3][id] -> SetMarkerStyle(marker[3]);

    for (int i=0;i<nmethod;i++){
      grIntFlowVsCent[i][id] -> SetMarkerSize(1.5);
      grIntFlowVsCent[i][id] -> SetDrawOption("P");
    }
    const char *grTitle[nmethod]={"v_{2}{2,QC};centrality (%);v_{2}",
                                  "[2] v_{2}{4};centrality (%);v_{2}",
                                  "[3] v_{2}{#Psi_{2,TPC}^{}};centrality (%);v_{2}",
                                  "[1] v_{2}{2};centrality (%);v_{2}"};
    outFile -> cd();
    for (int imeth=0; imeth<nmethod; imeth++){
      // grIntFlowVsCent[imeth][id] -> SetTitle(Form("V2 vs. centrality, %s, %s",pidNames.at(id).Data(),grTitle[imeth]));
      grIntFlowVsCent[imeth][id] -> SetTitle(grTitle[imeth]);
      grIntFlowVsCent[imeth][id] -> Write(Form("grRF_%i_%i",imeth,id));
    }


    std::vector<TGraphErrors*> vgr;
    vgr.push_back(grIntFlowVsCent[3][id]);
    for (int imeth=0; imeth<nmethod-1; imeth++){
      if (imeth==excludeMethod) continue;
      vgr.push_back(grIntFlowVsCent[imeth][id]);
    }

    
    can[id] = (TCanvas*) DrawTGraph(vgr,"",rangeRatioRF.at(id).first, rangeRatioRF.at(id).second,   mincent,maxcent,minV2int,maxV2int,
                                    coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                    level.Data(), pidFancyNames.at(id).Data());
    can[id] -> SetName(pidNames.at(id).Data());
    if (saveAsPNG) can[id] -> SaveAs(Form("./%s/%sV2vsCent.png",outDirName.Data(),pidNames.at(id).Data()));
  } // end of loop over particle ID

  // clear memory
  for (int icent=0;icent<ncent;icent++){
    delete HRes[icent];
    for (int id=0;id<npid;id++){
      delete hv22[icent][id];
      delete hv24[icent][id];
      delete hv22EP[icent][id];
      delete hv22Gap[icent][id];
      delete hcov24[icent][id];
      for (int ipt=0;ipt<npt;ipt++){
        delete hv2EP[icent][ipt][id];
        delete hv22ptGap[icent][ipt][id];
        delete hv22pt[icent][ipt][id];
        delete hv24pt[icent][ipt][id];
        delete hcov2prime4prime[icent][ipt][id];
      }
    }
  }
  delete inFile;
}

void v2plot_test(){
  CalStatErrCent1040();
  if (bMergeCharged){
    pidNames.clear();
    pidFancyNames.clear();
    pidNames = {"hadron", "pion", "kaon", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
    pidFancyNames = {"Ch. hadrons", "#pi", "K", "p+#bar{p}", "h-", "#pi-", "K-", "#bar{p}"};
  }
  gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
  for (int icent=0;icent<ncent;icent++){
    for (int id=0;id<npid;id++){
      prV22int[icent][id] = new TProfile(Form("prV22int_%i_%i",icent,id),"",1,0.,1.);
      prV24int[icent][id] = new TProfile(Form("prV24int_%i_%i",icent,id),"",1,0.,1.);
      prV22intGap[icent][id] = new TProfile(Form("prV22intGap_%i_%i",icent,id),"",1,0.,1.);
      prV22FHCalint[icent][id] = new TProfile(Form("prV22FHCalint_%i_%i",icent,id),"",1,0.,1.);

    }
  }
  for (int id=0;id<npid;id++){
    for (int meth=0;meth<nmethod;meth++){
      pV2Integrated[id][meth] = new TProfile(Form("pV2Integrated_pid%i_meth%i",id,meth),"",ncent,0.,ncent);
    }
  }
  v2plot_differential_flow();
  v2plot_integrated_flow_for_CH();
  // v2plot_integrated_flow_for_PID();
}