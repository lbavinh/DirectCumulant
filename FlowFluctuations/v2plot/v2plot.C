#include "DrawTGraphImp.C"
TString model = {"UrQMD"};
TString energy = {"7.7GeV"};
TString inFileName= (TString) Form("../ROOTFile/%s_%s.root",model.Data(),energy.Data());
TFile *outFile = new TFile(Form("./v2_%s_%s.root",model.Data(),energy.Data()),"recreate");
TString outDirName=(TString)Form("%s_%s",model.Data(),energy.Data());
TString level= (TString) Form("%s, Au+Au at #sqrt{s_{NN}}=%s",model.Data(),energy.Data());

// Flags
bool drawDistributions = false; // auxiliary plots: eta, bimp, mult, etc.
bool bMergeCharged = false; // merge CH(+) with CH(-); Pion(+) with Pion(-) and so on
bool saveAsPNG = false;
int excludeMethod = 0; // not including i-th method in v2 plotting, where i=0,1,2,3 correspond v22,v24,v2eta-sub,v22eta-gap, respectively
int drawDifferentialFlowTill = 0; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
// Constants
const int npid = 8; // charged hadrons, pions, kaons, protons
const int nmethod = 4; // 2QC, 4QC, EP, 2QC-gapped

const int npt = 16; // 0.5 - 3.6 GeV/c - number of pT bins
const double bin_pT[npt+1]={0.,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.2,3.6};
const double minptRFP = 0.2;
const double maxptRFP = 3.0;

const double maxpt = 3.6; // for v2 vs pt plotting
const double minpt = 0.;  // for v2 vs pt plotting

const int ncent = 9; // 0-80 %
const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
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
vector <Double_t> coordinateLeg = {0.18,0.63,0.45,0.889};
vector<pair<Double_t,Double_t>> rangeRatio = {{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16}}; // 0-10; 10-20; 20-30; 30-40; 40-50; 50-60; 60-70; 70-80; 10-40%
vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11}}; // charged hadrons, pions, kaons, protons
int marker[nmethod]={21,20,22,25}; // 2QC, 4QC, EP, 2QC-gapped

TProfile *prV22int[ncent][npid], *prV24int[ncent][npid], *prV2EPint[ncent][npid], *prV22intGap[ncent][npid]; // TProfile for integrated flow 


double eV22cent1040[npid][npt], eV24cent1040[npid][npt], eV2EPcent1040[npid][npt], eV22Gapcent1040[npid][npt];

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

void CalStatErrCent1040(){
  TFile *inFile = new TFile(inFileName.Data(),"read");

  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hPT[ncent][npt][npid];       // profile pt 
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  TProfile *hv2EP[ncent][npt][npid];	  // elliptic flow from EP method
  TProfile *HRes[ncent];
  TProfile *hv22Gap[ncent];
  TProfile *hv22ptGap[ncent][npt][npid];
  TProfile *hcov22primeGap[ncent][npt][npid];

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    HRes[icent] = (TProfile*)inFile->Get(Form("HRes_%i",icent));
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->Get(Form("hv22Gap_%i",icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv2EP[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv2EP_%i_%i_%i",icent,ipt,id));
        hPT[icent][ipt][id]=(TProfile*)inFile->Get(Form("hPT_%i_%i_%i",icent,ipt,id));
        hv22pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id)); 
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

  if(bMergeCharged){
    for (int icent=0;icent<ncent;icent++){
      for (int ipt=0;ipt<npt;ipt++){
        for (int id=0;id<npid/2;id++){
          hv2EP[icent][ipt][id] -> Add(hv2EP[icent][ipt][id+4]);
          hPT[icent][ipt][id] -> Add(hPT[icent][ipt][id+4]);
          hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id+4]);
          hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id+4]);
          hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id+4]);
          hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id+4]);
          hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id+4]);
          hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id+4]);
          hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id+4]);
          hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id+4]);
          hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id+4]);
        }
      }
    }
  }

  // Add
  for (int icent=3; icent<5; icent++){ // add 20-30% & 30-40% to 10-20%
    HRes[2] -> Add(HRes[icent]);
    hv22[2] -> Add(hv22[icent]);
    hv24[2] -> Add(hv24[icent]);
    hcov24[2] -> Add(hcov24[icent]);
    hv22Gap[2]-> Add(hv22Gap[icent]);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){ // loop over pid
        hv2EP[2][ipt][id]-> Add(hv2EP[icent][ipt][id]);
        hPT[2][ipt][id]-> Add(hPT[icent][ipt][id]);
        hv22pt[2][ipt][id]-> Add(hv22pt[icent][ipt][id]);
        hv24pt[2][ipt][id]-> Add(hv24pt[icent][ipt][id]);
        hcov22prime[2][ipt][id]-> Add(hcov22prime[icent][ipt][id]);
        hcov24prime[2][ipt][id]-> Add(hcov24prime[icent][ipt][id]);
        hcov42prime[2][ipt][id]-> Add(hcov42prime[icent][ipt][id]);
        hcov44prime[2][ipt][id]-> Add(hcov44prime[icent][ipt][id]);
        hcov2prime4prime[2][ipt][id]-> Add(hcov2prime4prime[icent][ipt][id]);
        hv22ptGap[2][ipt][id]->Add(hv22ptGap[icent][ipt][id]);
        hcov22primeGap[2][ipt][id]->Add(hcov22primeGap[icent][ipt][id]);
      }
    } // end of loop over pt bin
  }

  for (int icent=2; icent<3; icent++){ // 10-40
    // 2QC
    term cor2 = term(hv22[icent]);
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    // 2QC Gapped
    term cor2Gap = term(hv22Gap[icent]);
    for (int id=0;id<npid;id++){     
      for(int ipt=0; ipt<npt; ipt++){
        // v2EP
        double res2 = sqrt(HRes[icent]->GetBinContent(1));
        double ev2EP = hv2EP[icent][ipt][id]->GetBinError(1) / res2;
        eV2EPcent1040[id][ipt] = ev2EP;
        // v22
        term cor2red = term(hv22pt[icent][ipt][id]);
        double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        eV22cent1040[id][ipt] = ev22Dif;
        
        // v24
        term cor4red = term(hv24pt[icent][ipt][id]);
        double cov24prime = Covariance(hcov24prime[icent][ipt][id],hv22[icent],hv24pt[icent][ipt][id]);
        double cov42prime = Covariance(hcov42prime[icent][ipt][id],hv24[icent],hv22pt[icent][ipt][id]);
        double cov44prime = Covariance(hcov44prime[icent][ipt][id],hv24[icent],hv24pt[icent][ipt][id]);
        double cov2prime4prime = Covariance(hcov2prime4prime[icent][ipt][id],hv22pt[icent][ipt][id],hv24pt[icent][ipt][id]);
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
        eV24cent1040[id][ipt] = ev24Dif;
        // v22 Gapped
        term cor2redGap = term(hv22ptGap[icent][ipt][id]);
        double cov22primeGap = Covariance(hcov22primeGap[icent][ipt][id],hv22Gap[icent],hv22ptGap[icent][ipt][id]);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        eV22Gapcent1040[id][ipt] = ev22DifGap;
      } // end of loop for all pT bin
    } // end of loop for PID
  } // end of loop for centrality
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    delete HRes[icent];
    delete hv22[icent];
    delete hv24[icent];
    delete hcov24[icent];
    delete hv22Gap[icent];
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        delete hv2EP[icent][ipt][id];
        delete hPT[icent][ipt][id];
        delete hv22pt[icent][ipt][id];
        delete hv24pt[icent][ipt][id];
        delete hcov22prime[icent][ipt][id];
        delete hcov24prime[icent][ipt][id];
        delete hcov42prime[icent][ipt][id];
        delete hcov44prime[icent][ipt][id];
        delete hcov2prime4prime[icent][ipt][id];
        delete hv22ptGap[icent][ipt][id];
        delete hcov22primeGap[icent][ipt][id];
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes
  delete inFile;
}

void v2plot_differential_flow(){
  TFile *inFile = new TFile(inFileName.Data(),"read");


  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile
  // char analysis[20]={"pure"};

  if (drawDistributions){
    TCanvas *cTemp = new TCanvas("cTemp","cTemp",200,10,800,450);

    TH1I *hMult = (TH1I*)inFile->Get("hMult");
    hMult -> Draw();
    if (saveAsPNG) cTemp -> SaveAs(Form("./%s/mult.png",outDirName.Data()));

    TH1I *hEvt = (TH1I*)inFile->Get("hEvt");
    hEvt -> Draw();

    if (saveAsPNG) cTemp -> SaveAs(Form("./%s/evt.png",outDirName.Data()));

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

  // Input hist
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hPT[ncent][npt][npid];       // profile pt 
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  TProfile *hv2EP[ncent][npt][npid];	  // elliptic flow from EP method
  TProfile *HRes[ncent];
  // v22 with eta-gap
  TProfile *hv22Gap[ncent];
  TProfile *hv22ptGap[ncent][npt][npid];
  TProfile *hcov22primeGap[ncent][npt][npid];
  TProfile *hcounter[ncent][npt][npid];
  // OUTPUT
  TGraphErrors *grDifFl[nmethod][ncent][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  TGraphErrors *grDifFl1040[nmethod][npid];
  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    HRes[icent] = (TProfile*)inFile->Get(Form("HRes_%i",icent));
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->Get(Form("hv22Gap_%i",icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv2EP[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv2EP_%i_%i_%i",icent,ipt,id));
        hPT[icent][ipt][id]=(TProfile*)inFile->Get(Form("hPT_%i_%i_%i",icent,ipt,id));
        hv22pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id));
        hcounter[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcounter_%i_%i_%i",icent,ipt,id));      
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes
  
  //==========================================================================================================================
  if(bMergeCharged){
    for (int icent=0;icent<ncent;icent++){
      for (int ipt=0;ipt<npt;ipt++){
        for (int id=0;id<npid/2;id++){
          hv2EP[icent][ipt][id] -> Add(hv2EP[icent][ipt][id+4]);
          hPT[icent][ipt][id] -> Add(hPT[icent][ipt][id+4]);
          hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id+4]);
          hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id+4]);
          hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id+4]);
          hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id+4]);
          hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id+4]);
          hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id+4]);
          hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id+4]);
          hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id+4]);
          hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id+4]);
          hcounter[icent][ipt][id] -> Add(hcounter[icent][ipt][id+4]);
        }
      }
    }
  }
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
  TProfile *prV22dif1040[npt][npid], *prV24dif1040[npt][npid], *prV2EPdif1040[npt][npid], *prV22dif1040Gap[npt][npid], *pt1040[npt][npid]; // TProfile for differential flow of 10-40% centrality bin
  for (int ipt=0;ipt<npt;ipt++){
    for (int id=0;id<npid;id++){
      prV22dif1040[ipt][id]=new TProfile(Form("prV22dif1040_%i_%i",ipt,id),"",1,0.,1.);
      prV24dif1040[ipt][id]=new TProfile(Form("prV24dif1040_%i_%i",ipt,id),"",1,0.,1.);
      prV2EPdif1040[ipt][id]=new TProfile(Form("prV2EPdif1040_%i_%i",ipt,id),"",1,0.,1.);
      prV22dif1040Gap[ipt][id]=new TProfile(Form("prV22dif1040Gap_%i_%i",ipt,id),"",1,0.,1.);
      pt1040[ipt][id]=new TProfile(Form("pt1040_%i_%i",ipt,id),"",1,0.,1.);
    }
  }

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(hv22[icent]);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    
    // 2QC Gapped
    term cor2Gap = term(hv22Gap[icent]);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    for (int id=0;id<npid;id++){

      vector <double> vV2EPDif, vV22Dif, vV24Dif, vPt;
      vector <double> eV2EPDif, eV22Dif, eV24Dif, ePt;
      vector <double> vV22DifGap, vV2MCDif;
      vector <double> eV22DifGap, eV2MCDif;      
      // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        vPt.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
        ePt.push_back(0);
        // v2EP
        double res2 = sqrt(HRes[icent]->GetBinContent(1));
        double v2obs = hv2EP[icent][ipt][id]->GetBinContent(1);
        double v2EPDif = v2obs / res2;
        // if (id==0 && icent==1) cout << v2EPDif << " ";
        // double v2EPDif = v2obs;
        double ev2EP = hv2EP[icent][ipt][id]->GetBinError(1) / res2;
        vV2EPDif.push_back(v2EPDif);
        eV2EPDif.push_back(ev2EP);
        
        // v22
        term cor2red = term(hv22pt[icent][ipt][id]);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        vV22Dif.push_back(v22Dif);
        eV22Dif.push_back(ev22Dif);

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
        vV24Dif.push_back(v24Dif);
        eV24Dif.push_back(ev24Dif);

        // v22 Gapped
        term cor2redGap = term(hv22ptGap[icent][ipt][id]);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(hcov22primeGap[icent][ipt][id],hv22Gap[icent],hv22ptGap[icent][ipt][id]);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        vV22DifGap.push_back(v22DifGap);
        eV22DifGap.push_back(ev22DifGap);
        // if (id==0 && icent==7) cout << v22DifGap << " ";
        if (ipt>0 && ipt<npt-1)
        {
          prV22int[icent][id] -> Fill(0.5,v22Dif,hcounter[icent][ipt][id] -> GetBinEntries(1));
          prV24int[icent][id] -> Fill(0.5,v24Dif,hcounter[icent][ipt][id] -> GetBinEntries(1));
          prV2EPint[icent][id] -> Fill(0.5,v2EPDif,hcounter[icent][ipt][id] -> GetBinEntries(3));
          prV22intGap[icent][id] -> Fill(0.5,v22DifGap,hcounter[icent][ipt][id] -> GetBinEntries(2));
        }
        if (icent>=2 && icent <=4) { // 10-40%
          prV2EPdif1040[ipt][id]->Fill(0.5,v2EPDif,hcounter[icent][ipt][id] -> GetBinEntries(3));
          prV22dif1040Gap[ipt][id]->Fill(0.5,v22DifGap,hcounter[icent][ipt][id] -> GetBinEntries(2));
          prV22dif1040[ipt][id]->Fill(0.5,v22Dif,hcounter[icent][ipt][id] -> GetBinEntries(1));
          prV24dif1040[ipt][id]->Fill(0.5,v24Dif,hcounter[icent][ipt][id] -> GetBinEntries(1));
          pt1040[ipt][id]->Fill(0.5,hPT[icent][ipt][id] -> GetBinContent(1),hPT[icent][ipt][id] -> GetBinEntries(1));
        }

      } // end of loop for all pT bin
      // if (id==0 && icent==1) cout << endl;
      // 2QC differential flow
      grDifFl[0][icent][id] = new TGraphErrors(npt,&vPt[0],&vV22Dif[0],&ePt[0],&eV22Dif[0]);
      grDifFl[0][icent][id] -> SetMarkerColor(kRed);
      grDifFl[0][icent][id] -> SetMarkerStyle(marker[0]);
      // 4QC differential flow
      grDifFl[1][icent][id] = new TGraphErrors(npt,&vPt[0],&vV24Dif[0],&ePt[0],&eV24Dif[0]);
      grDifFl[1][icent][id] -> SetMarkerColor(kGreen+1);
      grDifFl[1][icent][id] -> SetMarkerStyle(marker[1]);
      // EP differential flow
      grDifFl[2][icent][id] = new TGraphErrors(npt,&vPt[0],&vV2EPDif[0],&ePt[0],&eV2EPDif[0]);
      grDifFl[2][icent][id] -> SetMarkerColor(kAzure+2);
      grDifFl[2][icent][id] -> SetMarkerStyle(marker[2]);
      // v2 Gap
      grDifFl[3][icent][id] = new TGraphErrors(npt,&vPt[0],&vV22DifGap[0],&ePt[0],&eV22DifGap[0]);
      grDifFl[3][icent][id] -> SetMarkerColor(kYellow+2);
      grDifFl[3][icent][id] -> SetMarkerStyle(marker[3]);
      for (int i=0; i<nmethod; i++){
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }
    } // end of loop over PID
  } // end of loop over centrality classes

  //==========================================================================================================================

  char nameV22Gap[400], nameV2EP[400];

  sprintf(nameV22Gap,"[1] v_{2}{2};p_{T} [GeV/c];v_{2}");
  sprintf(nameV2EP,"[3] v_{2}{#Psi_{2,TPC}^{}};p_{T} [GeV/c];v_{2}");
  const char *grTitleDF[nmethod]={"v_{2}{2,QC};p_{T} [GeV/c];v_{2}",
                                  "[2] v_{2}{4};p_{T} [GeV/c];v_{2}",
                                  nameV2EP,nameV22Gap};
  outFile -> cd();
  for (int imethod=0; imethod<nmethod; imethod++){
    for (int icent=0;icent<ncent;icent++){
      for (int id=0;id<npid;id++){
        if (bMergeCharged && id>3) continue; // if joining positively charged particles with negatively then id=0,1,2,3
        // grDifFl[imethod][icent][id] -> SetTitle(Form("V2 vs. pT, %s, centrality %i-%i%%, %s",pidNames.at(id).Data(),icent*10,(icent+1)*10,grTitleDF[imethod]));
        grDifFl[imethod][icent][id] -> SetTitle(grTitleDF[imethod]);
        grDifFl[imethod][icent][id] -> Write(Form("gr_cent%i_%i_%i",icent,imethod,id));
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[ncent][npid];
  for (int icent=0; icent<ncent; icent++){
    for (int id=0;id<npid;id++){
      vgrv2pt[icent][id].push_back(grDifFl[3][icent][id]); // v2{gapped 2QC}
      for (int i=0; i<nmethod-1; i++){
        if (i==excludeMethod) continue;
        vgrv2pt[icent][id].push_back(grDifFl[i][icent][id]);
      }
    }
  }
  TCanvas *cV2PT[ncent][npid];
  for (int icent=0; icent<drawDifferentialFlowTill; icent++){
    for (int id=0;id<npid;id++){
      if (bMergeCharged && id>3) continue; // if joining positively charged particles with negatively then id=0,1,2,3
      
      if (icent==0) {
        sprintf(hname,"%s, %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
        cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",rangeRatio.at(icent).first, rangeRatio.at(icent).second, minpt, maxpt, minV2dif, maxV2dif,
                                                 coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                 level.Data(), hname);
      }else{
        sprintf(hname,"%i-%i%%",icent*10,(icent+1)*10);
        cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",rangeRatio.at(icent).first, rangeRatio.at(icent).second, minpt, maxpt, minV2dif, maxV2dif,
                                                 coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                 "", hname,0);
      }
      cV2PT[icent][id] -> SetName(hname);
      if (saveAsPNG) cV2PT[icent][id] -> SaveAs(Form("./%s/%sDFCent%i-%i.png",outDirName.Data(),pidNames.at(id).Data(),(icent-1)*10,(icent)*10));
    }
  }

  double ePT[npt]={0.};
  TCanvas *cV2PT1040[npid];
  for (int id=0;id<npid;id++){
    if (bMergeCharged && id>3) continue; // if joining positively charged particles with negatively then id=0,1,2,3
    vector <double> vV22Dif1040, vV24Dif1040, vV2EPDif1040, vV22GapDif1040, vPT;
    for (int ipt=0;ipt<npt;ipt++){
      vV22Dif1040.push_back(prV22dif1040[ipt][id]->GetBinContent(1));
      vV24Dif1040.push_back(prV24dif1040[ipt][id]->GetBinContent(1));
      // if (id==0) cout << vV24Dif1040.at(ipt) << endl;
      // if (id==0) cout << eV24cent1040[0][ipt] << endl;
      vV2EPDif1040.push_back(prV2EPdif1040[ipt][id]->GetBinContent(1));
      // if (id==0) cout << vV2EPDif1040.at(ipt) << endl;
      // if (id==0) cout << eV2EPcent1040[0][ipt] << endl;
      vV22GapDif1040.push_back(prV22dif1040Gap[ipt][id]->GetBinContent(1));
      // if (id==0) cout << vV22GapDif1040.at(ipt) << endl;
      // if (id==0) cout << eV22Gapcent1040[0][ipt] << endl;
      // vPT.push_back(pt1040[ipt][id]->GetBinContent(1));
      vPT.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
    }
    grDifFl1040[0][id] = new TGraphErrors(npt,&vPT[0],&vV22Dif1040[0],&ePT[0],eV22cent1040[id]);
    grDifFl1040[0][id] -> SetMarkerColor(kRed);
    grDifFl1040[0][id] -> SetMarkerStyle(marker[0]);
    // 4QC differential flow
    grDifFl1040[1][id] = new TGraphErrors(npt,&vPT[0],&vV24Dif1040[0],&ePT[0],eV24cent1040[id]);
    grDifFl1040[1][id] -> SetMarkerColor(kGreen+1);
    grDifFl1040[1][id] -> SetMarkerStyle(marker[1]);
    // EP differential flow
    grDifFl1040[2][id] = new TGraphErrors(npt,&vPT[0],&vV2EPDif1040[0],&ePT[0],eV2EPcent1040[id]);
    grDifFl1040[2][id] -> SetMarkerColor(kAzure+2);
    grDifFl1040[2][id] -> SetMarkerStyle(marker[2]);
    // v2 gapped
    grDifFl1040[3][id] = new TGraphErrors(npt,&vPT[0],&vV22GapDif1040[0],&ePT[0],eV22Gapcent1040[id]);
    grDifFl1040[3][id] -> SetMarkerColor(kAzure+2);
    grDifFl1040[3][id] -> SetMarkerStyle(marker[3]);

    for (int i=0; i<nmethod; i++){
      grDifFl1040[i][id] -> SetMarkerSize(1.5);
      grDifFl1040[i][id] -> SetDrawOption("P");
      grDifFl1040[i][id] -> SetLineWidth(1);
    }

    std::vector<TGraphErrors*> vgrv2pt1040;
    for (int imeth=0; imeth<nmethod; imeth++){
      // grDifFl1040[imeth][id] -> SetTitle(Form("V2 vs. pT, %s, centrality 10-40%%, %s",pidNames.at(id).Data(),grTitleDF[imeth]));
      grDifFl1040[imeth][id] -> SetTitle(grTitleDF[imeth]);
      grDifFl1040[imeth][id] -> Write(Form("gr_cent10-40_%i_%i",imeth,id));
    }
    vgrv2pt1040.push_back(grDifFl1040[3][id]);
    for (int imeth=0;imeth<nmethod-1;imeth++){
      if (imeth==excludeMethod) continue;
      vgrv2pt1040.push_back(grDifFl1040[imeth][id]);
    }
    
    
    sprintf(hname,"10-40%%, %s",pidFancyNames.at(id).Data());

    cV2PT1040[id] = (TCanvas*) DrawTGraph(vgrv2pt1040,"",rangeRatio.at(ncent).first, rangeRatio.at(ncent).second, minpt, maxpt, minV2dif, maxV2dif,
                                          coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                          level.Data(), hname);
    cV2PT1040[id] -> SetName(hname);
    if (saveAsPNG) cV2PT1040[id] -> SaveAs(Form("./%s/%sDFCent10-40.png",outDirName.Data(),pidNames.at(id).Data()));
  }
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    delete HRes[icent];
    delete hv22[icent];
    delete hv24[icent];
    delete hcov24[icent];
    delete hv22Gap[icent];
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        delete hv2EP[icent][ipt][id];
        delete hPT[icent][ipt][id];
        delete hv22pt[icent][ipt][id];
        delete hv24pt[icent][ipt][id];
        delete hcov22prime[icent][ipt][id];
        delete hcov24prime[icent][ipt][id];
        delete hcov42prime[icent][ipt][id];
        delete hcov44prime[icent][ipt][id];
        delete hcov2prime4prime[icent][ipt][id];
        delete hv22ptGap[icent][ipt][id];
        delete hcov22primeGap[icent][ipt][id];
        delete hcounter[icent][ipt][id];
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes
  inFile->Close();
}

void v2plot_integrated_flow_for_CH(){ // v2int = v2 reference
  if (!bMergeCharged) { 
    // if one doesn't merge CH(+) with CH(-), then this function can't be used 
    // due to the fact that reference flow includes both CH+ and CH-
    return;
  }

  TFile *inFile = new TFile(inFileName.Data(),"read");
  // Histogram input
  TProfile *hv22[ncent];         // profile of integrated flow from v2{2}
  TProfile *hv24[ncent];         // profile of integrated flow from v2{4}
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hv22EP[ncent][npid]; // profile of integrated flow from v2{eta-sub}     
  TProfile *HRes[ncent];
  TProfile *hv22Gap[ncent];

  // Get histograms
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    HRes[icent] = (TProfile*)inFile->Get(Form("HRes_%i",icent));
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->Get(Form("hv22Gap_%i",icent));
    // hv22EP[icent][0] = (TProfile*)inFile->Get(Form("hv22EP_%i_0",icent));    
    // hv22EP[icent][4] = (TProfile*)inFile->Get(Form("hv22EP_%i_4",icent));
    for (int id=0;id<npid;id++){
      hv22EP[icent][id] = (TProfile*)inFile->Get(Form("hv22EP_%i_%i",icent,id));
    }
  }

  // TProfile *hv2EP[ncent][npt][npid];
  // for (int icent=0; icent<ncent; icent++){
  //   for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
  //     for (int id=0;id<npid;id++){
  //       hv2EP[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv2EP_%i_%i_%i",icent,ipt,id));
  //     }
  //   }
  // }
  // for (int icent=0;icent<ncent;icent++){
  //   for (int id=0;id<npid;id++){
  //     hv22EP[icent][id] = (TProfile*) hv2EP[icent][0][id]->Clone();
  //     for (int ipt=1;ipt<npt;ipt++){
  //       hv22EP[icent][id]->Add(hv2EP[icent][ipt][id]);
  //     }
  //   }
  // }
  // for (int icent=0; icent<ncent; icent++){
  //   for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
  //     for (int id=0;id<npid;id++){
  //       delete hv2EP[icent][ipt][id];
  //     }
  //   }
  // }

  for (int icent=0;icent<ncent;icent++){
    // merging CH(-) at id=4 with CH(+) at id=0
    hv22EP[icent][0]->Add(hv22EP[icent][4]);
  }
  TGraphErrors *grIntFlowVsCent[nmethod];
  TCanvas *can;


  std::vector<double> vV2EP, vV22, vV24, vV22int, vV24int, vV22Gap, vV22Gapint;
  std::vector<double> eV2EP, eV22, eV24, eV22int, eV24int, eV22Gap, eV22Gapint;

  for (int icent=0;icent<ncent;icent++){
    // cout << hv22EP[icent][0]->GetBinContent(1) << endl;
    // cout << sqrt( HRes[icent]->GetBinContent(1) ) << endl;
    // EP
    vV2EP.push_back( hv22EP[icent][0]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
    eV2EP.push_back( hv22EP[icent][0]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
    // cout << vV2EP.at(icent) << endl;
    // cout << eV2EP.at(icent) << endl;
    // 2QC
    term cor2 = term(hv22[icent]);
    vV22.push_back(sqrt(cor2.mVal));
    eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
    // cout << vV22.at(icent) << endl;
    // cout << eV22.at(icent) << endl;

    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    vV24.push_back(v24);
    eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );
    // cout << vV24.at(icent) << endl;
    cout << eV24.at(icent) << endl;
    term cor2Gap = term(hv22Gap[icent]);
    vV22Gap.push_back(sqrt(cor2Gap.mVal));
    eV22Gap.push_back(sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE));
    // cout << vV22Gap.at(icent) << endl;
    // cout << eV22Gap.at(icent) << endl;
    // Checking if there are differences with v2plot_integrated_flow_for_PID() or not
    // cout << icent <<" "<<vV22Gap.at(icent)<<" "<< eV22Gap.at(icent) <<endl;
    // cout << icent <<" "<<vV24.at(icent)<<" "<< eV24.at(icent) <<endl;
    // cout << icent <<" "<<vV22.at(icent)<<" "<< eV22.at(icent) <<endl;
    // cout << icent <<" "<<vV22.at(icent)<<" "<< prV22int[icent][0]->GetBinContent(1)<<" "<< eV22.at(icent) <<endl;
    // cout << icent <<" "<<vV24.at(icent)<<" "<< prV24int[icent][0]->GetBinContent(1)<<" "<< eV24.at(icent) <<endl;
    // cout << icent <<" "<<vV2EP.at(icent)<<" "<< prV2EPint[icent][0]->GetBinContent(1)<<" "<< eV2EP.at(icent) <<endl;
    // cout << icent <<" "<<vV22Gap.at(icent)<<" "<< prV22intGap[icent][0]->GetBinContent(1)<<" "<< eV22Gap.at(icent) <<endl;
  }
  
  grIntFlowVsCent[0] = new TGraphErrors(ncent,bin_cent,&vV22[0],bin_centE,&eV22[0]);
  grIntFlowVsCent[0] -> SetMarkerColor(kRed);
  grIntFlowVsCent[0] -> SetMarkerStyle(marker[0]);

  grIntFlowVsCent[1] = new TGraphErrors(ncent,bin_cent,&vV24[0],bin_centE,&eV24[0]);
  grIntFlowVsCent[1] -> SetMarkerColor(kGreen+1);
  grIntFlowVsCent[1] -> SetMarkerStyle(marker[1]);

  grIntFlowVsCent[2] = new TGraphErrors(ncent,bin_cent,&vV2EP[0],bin_centE,&eV2EP[0]);
  grIntFlowVsCent[2] -> SetMarkerColor(kAzure+2);
  grIntFlowVsCent[2] -> SetMarkerStyle(marker[2]);

  grIntFlowVsCent[3] = new TGraphErrors(ncent,bin_cent,&vV22Gap[0],bin_centE,&eV22Gap[0]);
  grIntFlowVsCent[3] -> SetMarkerColor(kYellow+2);
  grIntFlowVsCent[3] -> SetMarkerStyle(marker[3]);


  for (int i=0;i<nmethod;i++){
    grIntFlowVsCent[i] -> SetMarkerSize(1.5);
    grIntFlowVsCent[i] -> SetDrawOption("P");
  }
  const char *grTitle[nmethod]={"v_{2}{2,QC};centrality (%);v_{2}",
                                "[2] v_{2}{4};centrality (%);v_{2}",
                                "[3] v_{2}{#Psi_{2,TPC}^{}};centrality (%);v_{2}",
                                "[1] v_{2}{2};centrality (%);v_{2}"};
  outFile -> cd();
  for (int imeth=0; imeth<nmethod; imeth++){
    // grIntFlowVsCent[imeth] -> SetTitle(Form("V2 vs. centrality, %s, %s",pidNames.at(0).Data(),grTitle[imeth]));
    grIntFlowVsCent[imeth] -> SetTitle(grTitle[imeth]);
    grIntFlowVsCent[imeth] -> Write(Form("grRF_%i_0",imeth));
  }

  std::vector<TGraphErrors*> vgr;
  vgr.push_back(grIntFlowVsCent[3]);
  for (int imeth=0; imeth<nmethod-1; imeth++){
    if (imeth==excludeMethod) continue;
    vgr.push_back(grIntFlowVsCent[imeth]);
  }

  
  can = (TCanvas*) DrawTGraph(vgr,"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second,   mincent,maxcent,minV2int,maxV2int,
                                  coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                  level.Data(), Form("%s, %1.1f<p_{T}<%1.1f GeV/c",pidFancyNames.at(0).Data(),minptRFP,maxptRFP));
  can -> SetName(pidNames.at(0).Data());
  // we can extract only v2 vs centrality for charged hadrons !
  if (saveAsPNG) can -> SaveAs(Form("./%s/%sV2vsCent.png",outDirName.Data(),pidNames.at(0).Data()));

  // Clear memory
  for (int icent=0; icent<ncent; icent++){
    delete HRes[icent];
    delete hv22[icent];
    delete hv24[icent];
    delete hcov24[icent];
    delete hv22Gap[icent];
    for (int id=0;id<npid;id++){
      delete hv22EP[icent][id];
    }
  }
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
      hv22EP[icent][id] = (TProfile*)inFile->Get(Form("hv22EP_%i_%i",icent,id));
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
      // hv22EP[icent][id] = (TProfile*) hv2EP[icent][0][id]->Clone();
      hv22[icent][id] = (TProfile*) hv22pt[icent][1][id]->Clone();
      hv24[icent][id] = (TProfile*) hv24pt[icent][1][id]->Clone();
      hcov24[icent][id] = (TProfile*) hcov2prime4prime[icent][1][id]->Clone();
      hv22Gap[icent][id] = (TProfile*) hv22ptGap[icent][1][id]->Clone();
      for (int ipt=2;ipt<npt-1;ipt++){
        // hv22EP[icent][id]->Add(hv2EP[icent][ipt][id]);
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
        prV22int[icent][id]->Add(prV22int[icent][id+4]);
        prV24int[icent][id]->Add(prV24int[icent][id+4]);
        prV22intGap[icent][id]->Add(prV22intGap[icent][id+4]);
        prV2EPint[icent][id]->Add(prV2EPint[icent][id+4]);
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
      if (id==0) cout << sqrt( HRes[icent]->GetBinContent(1) ) << endl;  
      // EP
      vV2EP.push_back( hv22EP[icent][id]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
      eV2EP.push_back( hv22EP[icent][id]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
      // if (id==0) cout << vV2EP.at(icent) << endl;
      // 2QC
      term cor2 = term(hv22[icent][id]);
      vV22.push_back(sqrt(cor2.mVal)); // not in used
      eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
      // if (id==4) cout << vV22.at(icent) << endl;
      // 4QC
      term cor4 = term(hv24[icent][id]);
      double cov24 = Covariance(hcov24[icent][id],hv22[icent][id],hv24[icent][id]);
      double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
      vV24.push_back(v24); // not in used
      eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );
      // if (id==4) cout << vV24.at(icent) << endl;
      vV22int.push_back(prV22int[icent][id]->GetBinContent(1));
      vV24int.push_back(prV24int[icent][id]->GetBinContent(1));
      vV22Gapint.push_back(prV22intGap[icent][id]->GetBinContent(1));
      vV2EPint.push_back(prV2EPint[icent][id]->GetBinContent(1));
      term cor2Gap = term(hv22Gap[icent][id]);
      vV22Gap.push_back(sqrt(cor2Gap.mVal)); // not in used
      eV22Gap.push_back(sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE));

      // Checking if there are differences of vV2{x} & vV2{X}int 
      // if (id==3) { // PID: 0,1,2,3: CH,Pions,Kaons, protons & antiprotons
      //   cout << icent <<" "<<vV22.at(icent)<<" "<< vV22int.at(icent)<<" "<< eV22.at(icent)<<endl;
      //   cout << icent <<" "<<vV24.at(icent)<<" "<< vV24int.at(icent)<<" "<< eV24.at(icent)<<endl; // discrepancy ~3% for mid-central collisions, >10% for the rest
      //   cout << icent <<" "<<vV2EP.at(icent)<<" "<< vV2EPint.at(icent)<<" "<< eV2EP.at(icent)<<endl; // Both pt-bin merging method and integral over pt-bin method of integrated flow measurements give the same results for v2{eta-sub} ! 
      //   cout << icent <<" "<<vV22Gap.at(icent)<<" "<< vV22Gapint.at(icent)<<" "<< eV22Gap.at(icent)<<endl; // discrepancy approximately 2% at central collisions, >10% at peripheral collisions 
      // }
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

void v2plot(){
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
      prV2EPint[icent][id] = new TProfile(Form("prV2EPint_%i_%i",icent,id),"",1,0.,1.);
    }
  }
  v2plot_differential_flow();
  v2plot_integrated_flow_for_CH();
  v2plot_integrated_flow_for_PID();
}