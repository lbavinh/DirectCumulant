// #include "DrawTGraph.C"
// double Covariance(TProfile *const &hcovXY, TProfile *const &hX, TProfile *const &hY, Int_t binXY=0, Int_t binX=0, Int_t binY=0){
//   double mSumWXY = hcovXY->GetBinEntries(binXY+1);
//   double sumWX = hX->GetBinEntries(binX+1);
//   double sumWY = hY->GetBinEntries(binY+1);

//   double meanXY = hcovXY -> GetBinContent(binXY+1);
//   double meanX = hX -> GetBinContent(binX+1);
//   double meanY = hY -> GetBinContent(binY+1);
//   double mVal = (meanXY-meanX*meanY)/(sumWX*sumWY/mSumWXY-1.); // Cov(x,y)/(sumWX*sumWY/sumWXY)
//   return mVal;
// }
// struct term{ // structure for "Mean squared error of MEAN" calculation, using unbiased estimator for the root of variance
//   term(){
//     mVal = 0;
//     mMSE = 0;
//   }
//   term(TProfile *const &pr, Int_t bin=0){
//     double Neff = pr -> GetBinEffectiveEntries(bin+1);
//     mVal = pr -> GetBinContent(bin+1);
//     pr -> SetErrorOption("s");
//     double stdevW = pr -> GetBinError(bin+1);
//     double S2 = stdevW*stdevW/(1-1./Neff);
//     mMSE = S2/Neff;
//   };
//  public: 
//   double mVal; // weithted mean value
//   double mMSE; // Mean squared error of mean, https://en.wikipedia.org/wiki/Mean_squared_error
// };
#include "PlotV2QCumulantCentrality1040.C"
TGraphErrors* PlotV2QCumulant(TString inFileName, int METHOD=3, int CENT=3, int ID=8){
  // Flags
  bool saveAsPNG = false;
  int ratioToMethod = 0; // not including i-th method in v2 plotting, where i=0,1,2,3 correspond v22,v24,v2eta-sub,v22eta-gap, respectively
  bool saveGraph = true;
  TFile *outFile;
  if (saveGraph) outFile = new TFile(Form("./v2_%s_full.root",inFileName.Data()),"recreate");
  TString outDirName = "pics";
  int drawDifferentialFlowTill = 0; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
  // Constants
  // const int npid = 12; // CH+, pion+, kaon+, proton, CH-, pion-, kaon-, antiproton, CH, pions, kaons, protons+antiproton
  // const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_bar", "hadron", "pion", "kaon","proton_antiproton"};
  const std::vector<TString> pidFancyNames = {"h^{+}", "#pi^{+}", "K^{+}", "p", "h^{-}", "#pi^{-}", "K^{-}", "#bar{p}", "h^{#pm}","#pi^{#pm}","K^{#pm}","p(#bar{p})"};

  // const int nmethod = 3; // 2QC, 4QC, 2QC-gapped

  // const int npt = 16; // 0.5 - 3.6 GeV/c - number of pT bins
  // const double pTBin[npt+1]={0.,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.2,3.6};
  const int binMinPtRFP = 3;  // 0.2 GeV 
  const int binMaxPtRFP = 16; // 2.8 GeV
  // const int binMaxPtRFP = 10; // 2.0 GeV
  // const int binMaxPtRFP = 16; // 3.6 GeV
  const double minptRFP = 0.2;
  const double maxptRFP = 3.0;

  const double maxpt = 3.0; // for v2 vs pt plotting
  const double minpt = 0.;  // for v2 vs pt plotting

  // const int ncent = 9; // 0-80 %
  const double centralityBins[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
  const double bin_centE[ncent] = {0};
  const vector<pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};
  const float eta_gap = 0.05;

  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.2; // for v2 vs pt plotting


  vector <Double_t> coordinateLeg = {0.18,0.63,0.45,0.889};
  vector<pair<Double_t,Double_t>> rangeRatio = {{0.84,1.16},{0.84,1.16}};
  vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.65,1.11},{0.65,1.11}};
  int marker[]={21,20,22,25}; // 2QC, 4QC, 2QC-gapped

  // 2QC, 4QC, EP, 2QC-gapped
  // TString outDirName=(TString)Form("%s_%s",model.Data(),energy.Data());
  TString level= (TString) Form("vHLLE+UrQMD, Au+Au at #sqrt{s_{NN}}=11.5 GeV");
  double v2eDif1040[nmethod][npid][npt];
  TFile *inFile = new TFile(inFileName.Data(),"read");


  // Temporary variables
  char hname[800]; // histogram hname

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
  TProfile *hv22Gap[ncent];
  TProfile *hv22ptGap[ncent][npt][npid];
  TProfile *hcov22primeGap[ncent][npt][npid];
  TProfile *hcounter[ncent][npt][npid];
  // OUTPUT
  TGraphErrors *grDifFl[nmethod][ncent][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  
  // FindObjectAny TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)inFile->FindObjectAny(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->FindObjectAny(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->FindObjectAny(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hv22Gap_%i",icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid-4;id++){
        hv22pt[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id));
        hcounter[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcounter_%i_%i_%i",icent,ipt,id));      
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

  //==========================================================================================================================
  for (int icent=0;icent<ncent;icent++){
    for (int ipt=0;ipt<npt;ipt++){
      for (int id=8;id<npid;id++){
        hv22pt[icent][ipt][id] = (TProfile*)  hv22pt[icent][ipt][id-8] -> Clone();
        hv24pt[icent][ipt][id] = (TProfile*)  hv24pt[icent][ipt][id-8] -> Clone();
        hcov22prime[icent][ipt][id] = (TProfile*)  hcov22prime[icent][ipt][id-8] -> Clone();
        hcov24prime[icent][ipt][id] = (TProfile*)  hcov24prime[icent][ipt][id-8] -> Clone();
        hcov42prime[icent][ipt][id] = (TProfile*)  hcov42prime[icent][ipt][id-8] -> Clone();
        hcov44prime[icent][ipt][id] = (TProfile*)  hcov44prime[icent][ipt][id-8] -> Clone();
        hcov2prime4prime[icent][ipt][id] = (TProfile*)  hcov2prime4prime[icent][ipt][id-8] -> Clone();
        hv22ptGap[icent][ipt][id] = (TProfile*)  hv22ptGap[icent][ipt][id-8] -> Clone();
        hcov22primeGap[icent][ipt][id] = (TProfile*)  hcov22primeGap[icent][ipt][id-8] -> Clone();
        hcounter[icent][ipt][id] = (TProfile*)  hcounter[icent][ipt][id-8] -> Clone();

        hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id-4]);
        hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id-4]);
        hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id-4]);
        hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id-4]);
        hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id-4]);
        hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id-4]);
        hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id-4]);
        hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id-4]);
        hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id-4]);
        hcounter[icent][ipt][id] -> Add(hcounter[icent][ipt][id-4]);
      }
    }
  }
  
  // Filling pT bin
  double pt[npt];
  double ept[npt]={0}; // error bin pT = 0.0
  for (int ipt=0; ipt<npt; ipt++){
    // pt[icent][ipt][id] = hPT[icent][ipt][id] -> GetBinContent(1);
    pt[ipt] = ( pTBin[ipt] + pTBin[ipt+1] ) / 2.;
  }

  double v2Dif[nmethod][ncent][npid][npt], v2eDif[nmethod][ncent][npid][npt];
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
    for (int id=0;id<npid;id++){ // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        // vPt.push_back((pTBin[ipt]+pTBin[ipt+1])/2.);
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


      } // end of loop for all pT bin
      for (int i=0; i<nmethod; i++){
        grDifFl[i][icent][id] = new TGraphErrors(npt,pt,v2Dif[i][icent][id],ept,v2eDif[i][icent][id]);
        grDifFl[i][icent][id] -> SetMarkerStyle(marker[i]);
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }
    } // end of loop over PID
  } // end of loop over centrality classes

  const char *grTitleDF[nmethod]={"v_{2}{2};p_{T} [GeV/c];v_{2}",
                                  "v_{2}{4};p_{T} [GeV/c];v_{2}",
                                  "v_{2}{2,#eta-gap};p_{T} [GeV/c];v_{2}"};
  if (saveGraph) outFile -> cd();
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent;icent++){
        grDifFl[imeth][icent][id] -> SetTitle(grTitleDF[imeth]);
        if (saveGraph) grDifFl[imeth][icent][id] -> Write(Form("gr_cent%i_%i_%i",icent,imeth,id));
      }
    }
  }
  //==========================================================================================================================
  TGraphErrors *grIntFlPID[nmethod][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  TGraphErrors *grRefFl[nmethod];
  
  // v2 vs centrality for PID
  for (int icent=0;icent<ncent;icent++){
    for (int id=0;id<npid;id++){
      for (int ipt=binMinPtRFP+1;ipt<binMaxPtRFP;ipt++){
        hv22pt[icent][binMinPtRFP][id]          -> Add(hv22pt[icent][ipt][id]);
        hv24pt[icent][binMinPtRFP][id]          -> Add(hv24pt[icent][ipt][id]);
        hcov22prime[icent][binMinPtRFP][id]     -> Add(hcov22prime[icent][ipt][id]);
        hcov24prime[icent][binMinPtRFP][id]     -> Add(hcov24prime[icent][ipt][id]);
        hcov42prime[icent][binMinPtRFP][id]     -> Add(hcov42prime[icent][ipt][id]);
        hcov44prime[icent][binMinPtRFP][id]     -> Add(hcov44prime[icent][ipt][id]);
        hcov2prime4prime[icent][binMinPtRFP][id]-> Add(hcov2prime4prime[icent][ipt][id]);
        hv22ptGap[icent][binMinPtRFP][id]       -> Add(hv22ptGap[icent][ipt][id]);
        hcov22primeGap[icent][binMinPtRFP][id]  -> Add(hcov22primeGap[icent][ipt][id]);
      }
    }
  }
  
  double v2[nmethod][npid][ncent], v2e[nmethod][npid][ncent];
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
    // 2QC Gapped
    term cor2Gap = term(hv22Gap[icent]);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    v2_RF[2][icent] = v22Gap;
    v2e_RF[2][icent] = ev22Gap;
    // Differential flow calculation
    for (int id=0;id<npid;id++){   
      for(int ipt=binMinPtRFP; ipt<binMinPtRFP+1; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        // vPt.push_back((pTBin[ipt]+pTBin[ipt+1])/2.);
        // ePt.push_back(0);

        
        // v22
        term cor2red = term(hv22pt[icent][ipt][id]);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        v2[0][id][icent] = v22Dif;
        v2e[0][id][icent] = ev22Dif;
        
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
        v2[1][id][icent] = v24Dif;
        v2e[1][id][icent] = ev24Dif;
        // v22 Gapped
        term cor2redGap = term(hv22ptGap[icent][ipt][id]);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(hcov22primeGap[icent][ipt][id],hv22Gap[icent],hv22ptGap[icent][ipt][id]);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        v2[2][id][icent] = v22DifGap;
        v2e[2][id][icent] = ev22DifGap;
      } // end of loop for all pT bin
    } // end of loop over PID
  } // end of loop over centrality classes
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] = new TGraphErrors(ncent,centralityBins,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grRefFl[imeth] -> SetMarkerStyle(marker[imeth]);
    grRefFl[imeth] -> SetMarkerSize(1.5);
    for (int id=0; id<npid; id++){
      grIntFlPID[imeth][id] = new TGraphErrors(ncent,centralityBins,v2[imeth][id],bin_centE,v2e[imeth][id]);
      grIntFlPID[imeth][id] -> SetMarkerStyle(marker[imeth]);
      grIntFlPID[imeth][id] -> SetMarkerSize(1.5);
    }
  }
  const char *grTitleRF[nmethod]={"v_{2}{2};centrality (%);v_{2}",
                                  "v_{2}{4};centrality (%);v_{2}",
                                  "v_{2}{2,#eta-gap};centrality (%);v_{2}"};
  if (saveGraph) outFile -> cd();
  for (int imeth=0; imeth<nmethod; imeth++){

    for (int id=0;id<npid;id++){
      if (id==8) continue;
      grIntFlPID[imeth][id] -> SetTitle(grTitleRF[imeth]);
      if (saveGraph) grIntFlPID[imeth][id] -> Write(Form("grRF_%i_%i",imeth,id));
    }
  
  }

  std::vector<TGraphErrors*> vgrv2cent[npid];
  for (int id=0;id<npid;id++){
    if (id==8) continue;  
    vgrv2cent[id].push_back(grIntFlPID[ratioToMethod][id]); // v2{gapped 2QC}
    for (int i=0; i<nmethod; i++){
      if (i==ratioToMethod) continue;
      vgrv2cent[id].push_back(grIntFlPID[i][id]);
    }
  }
  

  TCanvas *cV2CentRF;

  std::vector<TGraphErrors*> vgrv2cent_chargedHardons;
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] -> SetTitle(grTitleRF[imeth]);
    if (saveGraph) grRefFl[imeth] -> Write(Form("grRF_%i_8",imeth));
  }
  vgrv2cent_chargedHardons.push_back(grRefFl[ratioToMethod]);
  for (int imeth=0;imeth<nmethod;imeth++){
    if (imeth==ratioToMethod) continue;
    vgrv2cent_chargedHardons.push_back(grRefFl[imeth]);
  }

  inFile->Close();
  // return grRefFl[3];
  return grDifFl[METHOD][CENT][ID];
  
}
