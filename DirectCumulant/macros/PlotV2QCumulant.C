#define PLOTV2QCUMULANT
#include "DrawTGraph.C"
#include "../constants.C"
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

void PlotV2QCumulant(TString inFileName = "FirstRun.root", TString outFileName = "graphs_v2QC.root"){
  
  bool saveTGraphToOutputFile = true;
  // Constants
  const int nmethod = 4; // 2QC, 4QC, 2QC (2-sub), 4QC (2-sub)
  // const int npid = 12; // CH+, pion+, kaon+, proton, CH-, pion-, kaon-, antiproton, CH, pions, kaons, protons+antiproton
  // const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_bar", "hadron", "pion", "kaon","proton_antiproton"}; // included in constants.C
  // const int ncent = 9; // included in constants.C
  // const int npt = 18; // 0.5 - 3.6 GeV/c - number of pT bins, included in constants.C
  // const Double_t pTBin[npt + 1] = {0., 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};// included in constants.C
  
  // IMPORTANT!!! Set low and high pT cut for integrated flow (v2 vs centrality)
  const double minptRFP = 0.2; // GeV/c
  const double maxptRFP = 3.0; // GeV/c
  if (maxptRFP>pTBin[npt]) { cerr << "maxptRFP need to be <= max pt bin" << endl; return; }
  int binMinPtRFP, binMaxPtRFP;
  for (Int_t j = 0; j < npt; j++) { if (minptRFP >= pTBin[j] && minptRFP < pTBin[j + 1]) binMinPtRFP = j; }
  for (Int_t j = 0; j < npt; j++) { if (maxptRFP > pTBin[j] && maxptRFP <= pTBin[j + 1]) binMaxPtRFP = j+1; }
  // cout << "binMinPtRFP=" << binMinPtRFP <<", pt=" << pTBin[binMinPtRFP] << endl;
  // cout << "binMaxPtRFP=" << binMaxPtRFP <<", pt=" << pTBin[binMaxPtRFP] << endl;

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Cosmetics for drawing 
  //
    bool saveAsPNG = true;
    TString outDirName = "pics"; // save png pics to output directory
    const char *grTitle[nmethod]={"v_{2}{2,standard}","v_{2}{4,standard}","v_{2}{2,2-sub}","v_{2}{4,2-sub}"};
    int drawRatioToMethod = 2; // Ratio to v2{2,2-sub}
    TString level = (TString) Form("UrQMD, Au+Au at #sqrt{#it{s}_{NN}} = 7.7 GeV"); // Title inside plots
    double centrality_bin[ncent]; // Filling centrality bin for drawing
    for (int ic=0; ic<ncent; ic++){
      centrality_bin[ic] = ( bin_cent[ic] + bin_cent[ic+1] ) / 2.;
    }
    const double centrality_bin_err[ncent] = {0};
    const vector<pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};

    double pt[npt]; // Filling pT bin for drawing
    const double ept[npt]={0}; // error bin pT = 0.0
    for (int ipt=0; ipt<npt; ipt++){
      pt[ipt] = ( pTBin[ipt] + pTBin[ipt+1] ) / 2.;
    }
    // Range of plots
    const double mincent = 0.;      // for v2 vs centrality
    const double maxcent = 60.;     // for v2 vs centrality
    const double minV2int = -0.005; // for v2 vs centrality
    const double maxV2int = 0.1;    // for v2 vs centrality
    const double maxpt = 3.1;       // for v2 vs pt
    const double minpt = -0.1;        // for v2 vs pt
    const double minV2dif = -0.01;  // for v2 vs pt
    const double maxV2dif = 0.25;    // for v2 vs pt
    // Range of ratio plots
    vector<pair<Double_t,Double_t>> rangeRatio = {{0.78,1.22},{0.68,1.32}};  // range of ratio pads for pT-differential flow plots
    vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.65,1.11},{0.65,1.11}}; // range of ratio pads for pT-integrated flow plots
    const std::vector<TString> pidFancyNames = {"h^{+}", "#pi^{+}", "K^{+}", "p", "h^{-}", "#pi^{-}", "K^{-}", "#bar{p}", "h^{#pm}","#pi^{#pm}","K^{#pm}","p(#bar{p})"};
    const int marker[nmethod]={24,22,20,26}; // markers for: 2QC, 4QC, 2QC(2-sub), 4QC(2-sub)
    vector <Double_t> coordinateLeg = {0.18,0.63,0.45,0.889}; // coordinate of legends
  //
  //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Input hist
  TFile *inFile = new TFile(inFileName.Data(),"read");
  // standard Q-Cumulant method
  TProfile *pCorrelator2 = (TProfile*)inFile->FindObjectAny("pCorrelator2"); // <<2>>
  TProfile *pCorrelator4 = (TProfile*)inFile->FindObjectAny("pCorrelator4"); // <<4>>
  TProfile *pCov24 = (TProfile*)inFile->FindObjectAny("pCov24");
  TProfile2D *pReducedCorrelator2[npid]; // <<2'>>
  TProfile2D *pReducedCorrelator4[npid]; // <<4'>>
  TProfile2D *pCov22Red[npid];
  TProfile2D *pCov24Red[npid];
  TProfile2D *pCov42Red[npid];
  TProfile2D *pCov44Red[npid];
  TProfile2D *pCov2Red4Red[npid];
  // sub-event Q-Cumulant method
  TProfile *pCorrelator2EtaGap = (TProfile*)inFile->FindObjectAny("pCorrelator2EtaGap"); // <<2>>
  TProfile *pCorrelator4EtaGap = (TProfile*)inFile->FindObjectAny("pCorrelator4EtaGap"); // <<4>>
  TProfile *pCov24EtaGap = (TProfile*)inFile->FindObjectAny("pCov24EtaGap");
  TProfile2D *pReducedCorrelator2EtaGap[npid]; // <<2'>>
  TProfile2D *pReducedCorrelator4EtaGap[npid]; // <<4'>>
  TProfile2D *pCov22RedEtaGap[npid];
  TProfile2D *pCov24RedEtaGap[npid];
  TProfile2D *pCov42RedEtaGap[npid];
  TProfile2D *pCov44RedEtaGap[npid];
  TProfile2D *pCov2Red4RedEtaGap[npid];

  // Initially calculated multiparticle correlations only for 8 particle species:
  // hadron+, pion+, kaon+, proton, hadron-, pion-, kaon-, antiproton
  // That's why here the loop goes up to npid-4=8
  for (int i=0; i<npid-4; i++)
  { 
    pReducedCorrelator2[i]       = (TProfile2D*) inFile->FindObjectAny(Form("pReducedCorrelator2_pid%i",i));
    pReducedCorrelator4[i]       = (TProfile2D*) inFile->FindObjectAny(Form("pReducedCorrelator4_pid%i",i));
    pCov22Red[i]                 = (TProfile2D*) inFile->FindObjectAny(Form("pCov22Red_pid%i",i));
    pCov24Red[i]                 = (TProfile2D*) inFile->FindObjectAny(Form("pCov24Red_pid%i",i));
    pCov42Red[i]                 = (TProfile2D*) inFile->FindObjectAny(Form("pCov42Red_pid%i",i));
    pCov44Red[i]                 = (TProfile2D*) inFile->FindObjectAny(Form("pCov44Red_pid%i",i));
    pCov2Red4Red[i]              = (TProfile2D*) inFile->FindObjectAny(Form("pCov2Red4Red_pid%i",i));
    pReducedCorrelator2EtaGap[i] = (TProfile2D*) inFile->FindObjectAny(Form("pReducedCorrelator2EtaGap_pid%i",i));
    pReducedCorrelator4EtaGap[i] = (TProfile2D*) inFile->FindObjectAny(Form("pReducedCorrelator4EtaGap_pid%i",i));
    pCov22RedEtaGap[i]           = (TProfile2D*) inFile->FindObjectAny(Form("pCov22RedEtaGap_pid%i",i));
    pCov24RedEtaGap[i]           = (TProfile2D*) inFile->FindObjectAny(Form("pCov24RedEtaGap_pid%i",i));
    pCov42RedEtaGap[i]           = (TProfile2D*) inFile->FindObjectAny(Form("pCov42RedEtaGap_pid%i",i));
    pCov44RedEtaGap[i]           = (TProfile2D*) inFile->FindObjectAny(Form("pCov44RedEtaGap_pid%i",i));
    pCov2Red4RedEtaGap[i]        = (TProfile2D*) inFile->FindObjectAny(Form("pCov2Red4RedEtaGap_pid%i",i));
  }

  TProfile *pReducedCorrelator2_cent[npid][ncent];
  TProfile *pReducedCorrelator4_cent[npid][ncent];
  TProfile *pCov22Red_cent[npid][ncent];
  TProfile *pCov24Red_cent[npid][ncent];
  TProfile *pCov42Red_cent[npid][ncent];
  TProfile *pCov44Red_cent[npid][ncent];
  TProfile *pCov2Red4Red_cent[npid][ncent];
  TProfile *pReducedCorrelator2EtaGap_cent[npid][ncent];
  TProfile *pReducedCorrelator4EtaGap_cent[npid][ncent];
  TProfile *pCov22RedEtaGap_cent[npid][ncent];
  TProfile *pCov24RedEtaGap_cent[npid][ncent];
  TProfile *pCov42RedEtaGap_cent[npid][ncent];
  TProfile *pCov44RedEtaGap_cent[npid][ncent];
  TProfile *pCov2Red4RedEtaGap_cent[npid][ncent];
  for (int i = 0; i < npid-4; i++)
  {
    for (int c = 0; c < ncent; c++)
    {
      pReducedCorrelator2_cent[i][c] = (TProfile*)pReducedCorrelator2[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2[i]->GetName(),c), c+1, c+1);
      pReducedCorrelator4_cent[i][c] = (TProfile*)pReducedCorrelator4[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator4[i]->GetName(),c), c+1, c+1);
      pCov22Red_cent[i][c] = (TProfile*)pCov22Red[i]->ProfileX(Form("%s_cent%i",pCov22Red[i]->GetName(),c), c+1, c+1);
      pCov24Red_cent[i][c] = (TProfile*)pCov24Red[i]->ProfileX(Form("%s_cent%i",pCov24Red[i]->GetName(),c), c+1, c+1); 
      pCov42Red_cent[i][c] = (TProfile*)pCov42Red[i]->ProfileX(Form("%s_cent%i",pCov42Red[i]->GetName(),c), c+1, c+1); 
      pCov44Red_cent[i][c] = (TProfile*)pCov44Red[i]->ProfileX(Form("%s_cent%i",pCov44Red[i]->GetName(),c), c+1, c+1); 
      pCov2Red4Red_cent[i][c] = (TProfile*)pCov2Red4Red[i]->ProfileX(Form("%s_cent%i",pCov2Red4Red[i]->GetName(),c), c+1, c+1); 
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2EtaGap[i]->GetName(),c), c+1, c+1);
      pReducedCorrelator4EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator4EtaGap[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator4EtaGap[i]->GetName(),c), c+1, c+1);
      pCov22RedEtaGap_cent[i][c] = (TProfile*)pCov22RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov22RedEtaGap[i]->GetName(),c), c+1, c+1);
      pCov24RedEtaGap_cent[i][c] = (TProfile*)pCov24RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov24RedEtaGap[i]->GetName(),c), c+1, c+1); 
      pCov42RedEtaGap_cent[i][c] = (TProfile*)pCov42RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov42RedEtaGap[i]->GetName(),c), c+1, c+1); 
      pCov44RedEtaGap_cent[i][c] = (TProfile*)pCov44RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov44RedEtaGap[i]->GetName(),c), c+1, c+1); 
      pCov2Red4RedEtaGap_cent[i][c] = (TProfile*)pCov2Red4RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov2Red4RedEtaGap[i]->GetName(),c), c+1, c+1);     
    }
  }
  // Now, need to merged positive and negative to obtain 12 particle species:
  for (int i=8;i<npid;i++)
  {
    for (int c = 0; c < ncent; c++)
    {
      pReducedCorrelator2_cent[i][c] = (TProfile*)  pReducedCorrelator2_cent[i-8][c] -> Clone();
      pReducedCorrelator4_cent[i][c] = (TProfile*)  pReducedCorrelator4_cent[i-8][c] -> Clone();
      pCov22Red_cent[i][c] = (TProfile*)  pCov22Red_cent[i-8][c] -> Clone();
      pCov24Red_cent[i][c] = (TProfile*)  pCov24Red_cent[i-8][c] -> Clone();
      pCov42Red_cent[i][c] = (TProfile*)  pCov42Red_cent[i-8][c] -> Clone();
      pCov44Red_cent[i][c] = (TProfile*)  pCov44Red_cent[i-8][c] -> Clone();
      pCov2Red4Red_cent[i][c] = (TProfile*)  pCov2Red4Red_cent[i-8][c] -> Clone();
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)  pReducedCorrelator2EtaGap_cent[i-8][c] -> Clone();
      pReducedCorrelator4EtaGap_cent[i][c] = (TProfile*)  pReducedCorrelator4EtaGap_cent[i-8][c] -> Clone();
      pCov22RedEtaGap_cent[i][c] = (TProfile*)  pCov22RedEtaGap_cent[i-8][c] -> Clone();
      pCov24RedEtaGap_cent[i][c] = (TProfile*)  pCov24RedEtaGap_cent[i-8][c] -> Clone();
      pCov42RedEtaGap_cent[i][c] = (TProfile*)  pCov42RedEtaGap_cent[i-8][c] -> Clone();
      pCov44RedEtaGap_cent[i][c] = (TProfile*)  pCov44RedEtaGap_cent[i-8][c] -> Clone();
      pCov2Red4RedEtaGap_cent[i][c] = (TProfile*)  pCov2Red4RedEtaGap_cent[i-8][c] -> Clone();

      pReducedCorrelator2_cent[i][c] -> Add(pReducedCorrelator2_cent[i-4][c]);
      pReducedCorrelator4_cent[i][c] -> Add(pReducedCorrelator4_cent[i-4][c]);
      pCov22Red_cent[i][c] -> Add(pCov22Red_cent[i-4][c]);
      pCov24Red_cent[i][c] -> Add(pCov24Red_cent[i-4][c]);
      pCov42Red_cent[i][c] -> Add(pCov42Red_cent[i-4][c]);
      pCov44Red_cent[i][c] -> Add(pCov44Red_cent[i-4][c]);
      pCov2Red4Red_cent[i][c] -> Add(pCov2Red4Red_cent[i-4][c]);
      pReducedCorrelator2EtaGap_cent[i][c] -> Add(pReducedCorrelator2EtaGap_cent[i-4][c]);
      pReducedCorrelator4EtaGap_cent[i][c] -> Add(pReducedCorrelator4EtaGap_cent[i-4][c]);
      pCov22RedEtaGap_cent[i][c] -> Add(pCov22RedEtaGap_cent[i-4][c]);
      pCov24RedEtaGap_cent[i][c] -> Add(pCov24RedEtaGap_cent[i-4][c]);
      pCov42RedEtaGap_cent[i][c] -> Add(pCov42RedEtaGap_cent[i-4][c]);
      pCov44RedEtaGap_cent[i][c] -> Add(pCov44RedEtaGap_cent[i-4][c]);
      pCov2Red4RedEtaGap_cent[i][c] -> Add(pCov2Red4RedEtaGap_cent[i-4][c]);
    }
  } // Done merging TProfile to obtain needed 12 particle species!

  // OUTPUT
  TFile *outFile;
  if (saveTGraphToOutputFile) outFile = new TFile(outFileName.Data(),"recreate"); // Save TGraphErrors
  TGraphErrors *grDifFl[nmethod][ncent][npid]; // v2{Q-Cumulant} (pT) of 12 PID
  TGraphErrors *grIntFlPID[nmethod][npid];     // v2{Q-Cumulant} (Centrality) of 11 PID (excluded inclusive charged hadrons)
  TGraphErrors *grRefFl[nmethod];              // v2{Q-Cumulant} (Centrality) of inclusive charged hadrons, a.k.a reference flow

  
  double v2Dif[nmethod][ncent][npid][npt], v2eDif[nmethod][ncent][npid][npt];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(pCorrelator2,icent);
    double v22 = sqrt(cor2.mVal);
    // double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(pCorrelator4,icent);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4,icent,icent,icent);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    // double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    // 2QC 2-sub
    term cor2Gap = term(pCorrelator2EtaGap,icent);
    double v22Gap = sqrt(cor2Gap.mVal);
    // double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    // 4QC 2-sub
    term cor4Gap = term(pCorrelator4EtaGap,icent);
    double cov24Gap = Covariance(pCov24EtaGap,pCorrelator2EtaGap,pCorrelator4EtaGap,icent,icent,icent);
    double v24Gap = pow(2*pow(cor2Gap.mVal,2)-cor4Gap.mVal,0.25);
    // double ev24Gap = sqrt( 1./pow(v24Gap,6)*(cor2Gap.mVal*cor2Gap.mVal*cor2Gap.mMSE+1./16*cor4Gap.mMSE-0.5*cor2Gap.mVal*cov24Gap) );

    for (int id=0;id<npid;id++){ // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin

        // v22
        term cor2red = term(pReducedCorrelator2_cent[id][icent],ipt);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(pCov22Red_cent[id][icent],pCorrelator2,pReducedCorrelator2_cent[id][icent],ipt,icent,ipt);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        v2Dif[0][icent][id][ipt] = v22Dif;
        v2eDif[0][icent][id][ipt] = ev22Dif;
        
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
        v2Dif[1][icent][id][ipt] = v24Dif;
        v2eDif[1][icent][id][ipt] = ev24Dif;
        // v22,subevent
        term cor2redGap = term(pReducedCorrelator2EtaGap_cent[id][icent],ipt);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(pCov22RedEtaGap_cent[id][icent],pCorrelator2EtaGap,pReducedCorrelator2EtaGap_cent[id][icent],ipt,icent,ipt);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        v2Dif[2][icent][id][ipt] = v22DifGap;
        v2eDif[2][icent][id][ipt] = ev22DifGap;
        // v24,subevent
        term cor4redGap = term(pReducedCorrelator4EtaGap_cent[id][icent],ipt);
        double cov24primeGap = Covariance(pCov24RedEtaGap_cent[id][icent],pCorrelator2EtaGap,pReducedCorrelator4EtaGap_cent[id][icent],ipt,icent,ipt);
        double cov42primeGap = Covariance(pCov42RedEtaGap_cent[id][icent],pCorrelator4EtaGap,pReducedCorrelator2EtaGap_cent[id][icent],ipt,icent,ipt);
        double cov44primeGap = Covariance(pCov44RedEtaGap_cent[id][icent],pCorrelator4EtaGap,pReducedCorrelator4EtaGap_cent[id][icent],ipt,icent,ipt);
        double cov2prime4primeGap = Covariance(pCov2Red4RedEtaGap_cent[id][icent],pReducedCorrelator2EtaGap_cent[id][icent],pReducedCorrelator4EtaGap_cent[id][icent],ipt,ipt,ipt);
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

      } // end of loop for all pT bin
      for (int i=0; i<nmethod; i++){
        grDifFl[i][icent][id] = new TGraphErrors(npt,pt,v2Dif[i][icent][id],ept,v2eDif[i][icent][id]);
        grDifFl[i][icent][id] -> SetMarkerStyle(marker[i]);
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }
    } // end of loop over PID
  } // end of loop over centrality classes
  
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent;icent++){
        grDifFl[imeth][icent][id]->SetTitle(grTitle[imeth]);
        grDifFl[imeth][icent][id]->GetYaxis()-> SetTitle("v_{2}");
        grDifFl[imeth][icent][id]->GetXaxis()-> SetTitle("p_{T}, GeV/c");
      }
    }
  }
  
  if (saveAsPNG) gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
  TCanvas *cV2PTMultPad[npid];
  TString strCent[5] = {"0-5%","5-10%","10-20%","20-30%","30-40%"};
  for (int id=0;id<npid;id++)
  {
    std::vector<TGraphErrors*> vgrv2pt[5];
    for (int icent=0; icent<5; icent++)
    {
      vgrv2pt[icent].push_back(grDifFl[drawRatioToMethod][icent][id]);
      for (int i=0; i<nmethod; i++){
        if (i==drawRatioToMethod) continue;
        vgrv2pt[icent].push_back(grDifFl[i][icent][id]);
      }
    }
    cV2PTMultPad[id] = (TCanvas*) DrawTGraph(vgrv2pt, 5,"",rangeRatio.at(0).first, rangeRatio.at(0).second, minpt, maxpt, minV2dif, maxV2dif,
                                              coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                              Form("%s, %s", level.Data(), pidFancyNames.at(id).Data()),
                                              strCent, true, grTitle[drawRatioToMethod]);
    cV2PTMultPad[id] -> SetName("");
    if (saveAsPNG) cV2PTMultPad[id] -> SaveAs(Form("./%s/DifferentialFlow_%s_Cent_0_40.png",outDirName.Data(),pidNames.at(id).Data()));
  }

  TCanvas *cV2PTMultPad2[npid];
  TString strCent2[4] = {"40-50%","50-60%","60-70%","70-80%"};
  for (int id=0;id<npid;id++)
  {
    std::vector<TGraphErrors*> vgrv2pt[4];
    for (int icent=5; icent<ncent; icent++)
    {
      vgrv2pt[icent-5].push_back(grDifFl[drawRatioToMethod][icent][id]);
      for (int i=0; i<nmethod; i++){
        if (i==drawRatioToMethod) continue;
        vgrv2pt[icent-5].push_back(grDifFl[i][icent][id]);
      }
    }
    cV2PTMultPad2[id] = (TCanvas*) DrawTGraph(vgrv2pt, 4,"",rangeRatio.at(1).first, rangeRatio.at(1).second, minpt, maxpt, minV2dif, maxV2dif,
                                              coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                              Form("%s, %s", level.Data(), pidFancyNames.at(id).Data()),
                                              strCent2, true, grTitle[drawRatioToMethod]);
    cV2PTMultPad2[id] -> SetName("");
    if (saveAsPNG) cV2PTMultPad2[id] -> SaveAs(Form("./%s/DifferentialFlow_%s_Cent_40_80.png",outDirName.Data(),pidNames.at(id).Data()));
  }

  //==========================================================================================================================

  // v2 vs centrality for PID
  TProfile *pReducedCorrelator2_PID[npid];
  TProfile *pReducedCorrelator4_PID[npid];
  TProfile *pCov22Red_PID[npid];
  TProfile *pCov24Red_PID[npid];
  TProfile *pCov42Red_PID[npid];
  TProfile *pCov44Red_PID[npid];
  TProfile *pCov2Red4Red_PID[npid];
  TProfile *pReducedCorrelator2EtaGap_PID[npid];
  TProfile *pReducedCorrelator4EtaGap_PID[npid];
  TProfile *pCov22RedEtaGap_PID[npid];
  TProfile *pCov24RedEtaGap_PID[npid];
  TProfile *pCov42RedEtaGap_PID[npid];
  TProfile *pCov44RedEtaGap_PID[npid];
  TProfile *pCov2Red4RedEtaGap_PID[npid];
  for (int i = 0; i < npid-4; i++)
  {
    pReducedCorrelator2_PID[i] = (TProfile*)pReducedCorrelator2[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator2[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pReducedCorrelator4_PID[i] = (TProfile*)pReducedCorrelator4[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator4[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov22Red_PID[i] = (TProfile*)pCov22Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov22Red[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov24Red_PID[i] = (TProfile*)pCov24Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov24Red[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pCov42Red_PID[i] = (TProfile*)pCov42Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov42Red[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pCov44Red_PID[i] = (TProfile*)pCov44Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov44Red[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov2Red4Red_PID[i] = (TProfile*)pCov2Red4Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov2Red4Red[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pReducedCorrelator2EtaGap_PID[i] = (TProfile*)pReducedCorrelator2EtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator2EtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pReducedCorrelator4EtaGap_PID[i] = (TProfile*)pReducedCorrelator4EtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator4EtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov22RedEtaGap_PID[i] = (TProfile*)pCov22RedEtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov22RedEtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov24RedEtaGap_PID[i] = (TProfile*)pCov24RedEtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov24RedEtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pCov42RedEtaGap_PID[i] = (TProfile*)pCov42RedEtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov42RedEtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pCov44RedEtaGap_PID[i] = (TProfile*)pCov44RedEtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov44RedEtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov2Red4RedEtaGap_PID[i] = (TProfile*)pCov2Red4RedEtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov2Red4RedEtaGap[i]->GetName(),pTBin[binMinPtRFP], pTBin[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
  }
  for (int i=8;i<npid;i++)
  {
    pReducedCorrelator2_PID[i] = (TProfile*)  pReducedCorrelator2_PID[i-8] -> Clone();
    pReducedCorrelator4_PID[i] = (TProfile*)  pReducedCorrelator4_PID[i-8] -> Clone();
    pCov22Red_PID[i] = (TProfile*)  pCov22Red_PID[i-8] -> Clone();
    pCov24Red_PID[i] = (TProfile*)  pCov24Red_PID[i-8] -> Clone();
    pCov42Red_PID[i] = (TProfile*)  pCov42Red_PID[i-8] -> Clone();
    pCov44Red_PID[i] = (TProfile*)  pCov44Red_PID[i-8] -> Clone();
    pCov2Red4Red_PID[i] = (TProfile*)  pCov2Red4Red_PID[i-8] -> Clone();
    pReducedCorrelator2EtaGap_PID[i] = (TProfile*)  pReducedCorrelator2EtaGap_PID[i-8] -> Clone();
    pReducedCorrelator4EtaGap_PID[i] = (TProfile*)  pReducedCorrelator4EtaGap_PID[i-8] -> Clone();
    pCov22RedEtaGap_PID[i] = (TProfile*)  pCov22RedEtaGap_PID[i-8] -> Clone();
    pCov24RedEtaGap_PID[i] = (TProfile*)  pCov24RedEtaGap_PID[i-8] -> Clone();
    pCov42RedEtaGap_PID[i] = (TProfile*)  pCov42RedEtaGap_PID[i-8] -> Clone();
    pCov44RedEtaGap_PID[i] = (TProfile*)  pCov44RedEtaGap_PID[i-8] -> Clone();
    pCov2Red4RedEtaGap_PID[i] = (TProfile*)  pCov2Red4RedEtaGap_PID[i-8] -> Clone();

    pReducedCorrelator2_PID[i] -> Add(pReducedCorrelator2_PID[i-4]);
    pReducedCorrelator4_PID[i] -> Add(pReducedCorrelator4_PID[i-4]);
    pCov22Red_PID[i] -> Add(pCov22Red_PID[i-4]);
    pCov24Red_PID[i] -> Add(pCov24Red_PID[i-4]);
    pCov42Red_PID[i] -> Add(pCov42Red_PID[i-4]);
    pCov44Red_PID[i] -> Add(pCov44Red_PID[i-4]);
    pCov2Red4Red_PID[i] -> Add(pCov2Red4Red_PID[i-4]);
    pReducedCorrelator2EtaGap_PID[i] -> Add(pReducedCorrelator2EtaGap_PID[i-4]);
    pReducedCorrelator4EtaGap_PID[i] -> Add(pReducedCorrelator4EtaGap_PID[i-4]);
    pCov22RedEtaGap_PID[i] -> Add(pCov22RedEtaGap_PID[i-4]);
    pCov24RedEtaGap_PID[i] -> Add(pCov24RedEtaGap_PID[i-4]);
    pCov42RedEtaGap_PID[i] -> Add(pCov42RedEtaGap_PID[i-4]);
    pCov44RedEtaGap_PID[i] -> Add(pCov44RedEtaGap_PID[i-4]);
    pCov2Red4RedEtaGap_PID[i] -> Add(pCov2Red4RedEtaGap_PID[i-4]);
  }
  
  double v2_vs_centrality_PID[nmethod][npid][ncent], v2err_vs_centrality_PID[nmethod][npid][ncent];
  double v2_vs_centrality_hadrons[nmethod][ncent],    v2err_vs_centrality_hadrons[nmethod][ncent];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(pCorrelator2,icent);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    v2_vs_centrality_hadrons[0][icent] = v22;
    v2err_vs_centrality_hadrons[0][icent] = ev22;
    // 4QC
    term cor4 = term(pCorrelator4,icent);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4,icent,icent,icent);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    v2_vs_centrality_hadrons[1][icent] = v24;
    v2err_vs_centrality_hadrons[1][icent] = ev24;
    // 2QC Gapped
    term cor2Gap = term(pCorrelator2EtaGap,icent);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    v2_vs_centrality_hadrons[2][icent] = v22Gap;
    v2err_vs_centrality_hadrons[2][icent] = ev22Gap;
    // 4QC, 2-sub
    term cor4Gap = term(pCorrelator4EtaGap,icent);
    double cov24Gap = Covariance(pCov24EtaGap,pCorrelator2EtaGap,pCorrelator4EtaGap,icent,icent,icent);
    double v24Gap = pow(2*pow(cor2Gap.mVal,2)-cor4Gap.mVal,0.25);
    double ev24Gap = sqrt( 1./pow(v24Gap,6)*(cor2Gap.mVal*cor2Gap.mVal*cor2Gap.mMSE+1./16*cor4Gap.mMSE-0.5*cor2Gap.mVal*cov24Gap) );
    v2_vs_centrality_hadrons[3][icent] = v24Gap;
    v2err_vs_centrality_hadrons[3][icent] = ev24Gap;    
    for (int id=0;id<npid;id++){
      // v22
      term cor2red = term(pReducedCorrelator2_PID[id],icent);
      double v22Dif = cor2red.mVal/v22;
      double cov22prime = Covariance(pCov22Red_PID[id],pCorrelator2,pReducedCorrelator2_PID[id],icent,icent,icent);
      double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                          + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
      v2_vs_centrality_PID[0][id][icent] = v22Dif;
      v2err_vs_centrality_PID[0][id][icent] = ev22Dif;
      // v24
      term cor4red = term(pReducedCorrelator4_PID[id],icent);
      double cov24prime = Covariance(pCov24Red_PID[id],pCorrelator2,pReducedCorrelator4_PID[id],icent,icent,icent);
      double cov42prime = Covariance(pCov42Red_PID[id],pCorrelator4,pReducedCorrelator2_PID[id],icent,icent,icent);
      double cov44prime = Covariance(pCov44Red_PID[id],pCorrelator4,pReducedCorrelator4_PID[id],icent,icent,icent);
      double cov2prime4prime = Covariance(pCov2Red4Red_PID[id],pReducedCorrelator2_PID[id],pReducedCorrelator4_PID[id],icent,icent,icent);
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
      v2_vs_centrality_PID[1][id][icent] = v24Dif;
      v2err_vs_centrality_PID[1][id][icent] = ev24Dif;
      // v22,subevent
      term cor2redGap = term(pReducedCorrelator2EtaGap_PID[id],icent);
      double v22DifGap = cor2redGap.mVal/v22Gap;
      double cov22primeGap = Covariance(pCov22RedEtaGap_PID[id],pCorrelator2EtaGap,pReducedCorrelator2EtaGap_PID[id],icent,icent,icent);
      double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                          + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
      v2_vs_centrality_PID[2][id][icent] = v22DifGap;
      v2err_vs_centrality_PID[2][id][icent] = ev22DifGap;
      // v24,subevent
      term cor4redGap = term(pReducedCorrelator4EtaGap_PID[id],icent);
      double cov24primeGap = Covariance(pCov24RedEtaGap_PID[id],pCorrelator2EtaGap,pReducedCorrelator4EtaGap_PID[id],icent,icent,icent);
      double cov42primeGap = Covariance(pCov42RedEtaGap_PID[id],pCorrelator4EtaGap,pReducedCorrelator2EtaGap_PID[id],icent,icent,icent);
      double cov44primeGap = Covariance(pCov44RedEtaGap_PID[id],pCorrelator4EtaGap,pReducedCorrelator4EtaGap_PID[id],icent,icent,icent);
      double cov2prime4primeGap = Covariance(pCov2Red4RedEtaGap_PID[id],pReducedCorrelator2EtaGap_PID[id],pReducedCorrelator4EtaGap_PID[id],icent,icent,icent);        
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
      v2_vs_centrality_PID[3][id][icent] = v24DifGap;
      v2err_vs_centrality_PID[3][id][icent] = ev24DifGap;  
    } // end of loop over PID
  } // end of loop over centrality classes
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] = new TGraphErrors(ncent,centrality_bin,v2_vs_centrality_hadrons[imeth],centrality_bin_err,v2err_vs_centrality_hadrons[imeth]);
    grRefFl[imeth] -> SetMarkerStyle(marker[imeth]);
    grRefFl[imeth] -> SetMarkerSize(1.5);
    for (int id=0; id<npid; id++){
      grIntFlPID[imeth][id] = new TGraphErrors(ncent,centrality_bin,v2_vs_centrality_PID[imeth][id],centrality_bin_err,v2err_vs_centrality_PID[imeth][id]);
      grIntFlPID[imeth][id] -> SetMarkerStyle(marker[imeth]);
      grIntFlPID[imeth][id] -> SetMarkerSize(1.5);
    }
  }
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      if (id==8) continue;
      grIntFlPID[imeth][id]->SetTitle(grTitle[imeth]);
      grIntFlPID[imeth][id]->GetYaxis()-> SetTitle("v_{2}");
      grIntFlPID[imeth][id]->GetXaxis()-> SetTitle("Centrality, %");
    }
  }

  std::vector<TGraphErrors*> vgrv2cent[npid];
    for (int id=0;id<npid;id++){
      if (id==8) continue;  
      vgrv2cent[id].push_back(grIntFlPID[drawRatioToMethod][id]); // v2{gapped 2QC}
      for (int i=0; i<nmethod; i++){
        if (i==drawRatioToMethod) continue;
        vgrv2cent[id].push_back(grIntFlPID[i][id]);
      }
    }
  
  TCanvas *cV2Cent[npid];
  for (int id=0;id<npid;id++){
    if (id==8) continue;
    cV2Cent[id] = (TCanvas*) DrawTGraph(vgrv2cent[id],"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second, mincent, maxcent, minV2int, maxV2int,
                                        coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                        level.Data(), Form("%s, %1.1f<p_{T}<%1.1f",pidFancyNames.at(id).Data(),pTBin[binMinPtRFP],pTBin[binMaxPtRFP]),
                                        true, Form("Ratio to %s",grTitle[drawRatioToMethod]));

    cV2Cent[id] -> SetName(pidFancyNames.at(id).Data());
    if (saveAsPNG) cV2Cent[id] -> SaveAs(Form("./%s/IntegratedFlow_%s.png",outDirName.Data(),pidNames.at(id).Data()));
  }
  

  TCanvas *cV2CentRF;

  std::vector<TGraphErrors*> vgrv2cent_chargedHardons;
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth]->SetTitle(grTitle[imeth]);
    grRefFl[imeth]->GetYaxis()->SetTitle("v_{2}");
    grRefFl[imeth]->GetXaxis()->SetTitle("Centrality, %");
  }
  vgrv2cent_chargedHardons.push_back(grRefFl[drawRatioToMethod]);
  for (int imeth=0;imeth<nmethod;imeth++){
    if (imeth==drawRatioToMethod) continue;
    vgrv2cent_chargedHardons.push_back(grRefFl[imeth]);
  }
  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second, mincent, maxcent, minV2int, maxV2int,
                                    coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                    level.Data(), Form("Ch. hadrons, %1.1f<p_{T}<%1.1f GeV/c",minptRFP,maxptRFP),
                                    true, Form("Ratio to %s",grTitle[drawRatioToMethod]));
  cV2CentRF -> SetName("Reference flow");
  if (saveAsPNG) cV2CentRF -> SaveAs(Form("./%s/IntegratedFlow_hadron.png",outDirName.Data()));

  if (saveTGraphToOutputFile)
  {
    outFile -> cd();
    for (int imeth=0;imeth<nmethod;imeth++)
    {
      grRefFl[imeth]->SetTitle(Form("%s vs. centrality of inclusive charged hadrons",grTitle[imeth]));
      grRefFl[imeth]->SetMarkerColor(kBlack);
      grRefFl[imeth]->Write(Form("grRF_%i_8",imeth));
    }
    for (int imeth=0;imeth<nmethod;imeth++)
    {
      for (int id=0; id < npid; id++)
      {
        if (id==8) continue;
        grIntFlPID[imeth][id]->SetMarkerColor(kBlack);
        grIntFlPID[imeth][id]->SetTitle(Form("%s vs. centrality of %s",grTitle[imeth],pidNames.at(id).Data()));
        grIntFlPID[imeth][id]->Write(Form("grRF_%i_%i",imeth,id));
      }
    }
    for (int imeth=0;imeth<nmethod;imeth++){
      for (int icent=0; icent < ncent; icent++){
        for (int id=0; id < npid; id++){
          grDifFl[imeth][icent][id]->SetMarkerColor(kBlack);
          grDifFl[imeth][icent][id]->SetTitle(Form("%s vs. pT at %i-%i%% of %s",grTitle[imeth],centrality.at(icent).first,centrality.at(icent).second,pidNames.at(id).Data()));
          grDifFl[imeth][icent][id]->Write(Form("gr_cent%i_%i_%i",icent,imeth,id));
        }
      }   
    }
    outFile->Close();
  }
  inFile->Close();

}
