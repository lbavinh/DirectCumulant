#include "DrawTGraphImp.C"
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

void v2plot(TString model ="vHLLEUrQMD", TString energy = "39GeV") {
  
  TString inFileName = (TString) Form("../ROOTFile/%s_%s_PID.root",model.Data(),energy.Data());
  TFile *outFile = new TFile(Form("./v2_%s_%s_8PID.root",model.Data(),energy.Data()),"recreate");
  TString outDirName = (TString)Form("%s_%s_8PID",model.Data(),energy.Data());
  TString level= (TString) Form("%s, Au+Au at #sqrt{s_{NN}}=%s",model.Data(),energy.Data());

  // Flags
  bool drawDistributions = false; // auxiliary plots: eta, bimp, mult, etc.
  bool bMergeCharged = false; // merge CH(+) with CH(-); Pion(+) with Pion(-) and so on
  bool saveAsPNG = true;
  int excludeMethod = 0; // not including i-th method in v2 plotting, where i=0,1,2,3 correspond v22,v24,v2eta-sub,v22eta-gap, respectively
  int drawDifferentialFlowTill = 0; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
  // Constants
  const int npid = 10; // charged hadrons, pions, kaons, protons
  const int nmethod = 3; // 2QC, 4QC, EP, 2QC-gapped

  // const int npt = 16; // 0.5 - 3.6 GeV/c - number of pT bins
  // const double bin_pT[npt+1]={0.,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.2,3.6};
  const double minptRFP = 0.2;
  const double maxptRFP = 3.0;

  const int ncent = 9; // 0-80 %
  const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  const double bin_centE[ncent] = {0};
  const float eta_gap = 0.05;

  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.005; // for v2 vs pt plotting
  const double maxV2dif = 0.1; // for v2 vs pt plotting

  std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "antiproton", "pion", "kaon"};
  std::vector<TString> pidFancyNames = {"h^{+}", "#pi^{+}", "K^{+}", "p", "h^{-}", "#pi^{-}", "K^{-}", "#bar{p}", "#pi^{#pm}", "K^{#pm}"};
  vector <Double_t> coordinateLeg = {0.18,0.63,0.45,0.889};
  vector<pair<Double_t,Double_t>> rangeRatio = {{0.65,1.11},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16},{0.84,1.16}}; // 0-10; 10-20; 20-30; 30-40; 40-50; 50-60; 60-70; 70-80; 10-40%
  vector<pair<Double_t,Double_t>> rangeRatioRF ={{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11},{0.65,1.11}}; // charged hadrons, pions, kaons, protons
  int marker[]={21,20,22,25}; // 2QC, 4QC, EP, 2QC-gapped

  gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
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
  TProfile *hPT[ncent][npid];       // profile pt 
  TProfile *hv22pt[ncent][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npid]; // <2'>*<4'>
  // v22 with eta-gap
  TProfile *hv22Gap[ncent];
  TProfile *hv22ptGap[ncent][npid];
  TProfile *hcov22primeGap[ncent][npid];
  TProfile *hcounter[ncent][npid];
  // OUTPUT
  TGraphErrors *grDifFl[nmethod][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  TGraphErrors *grRefFl[nmethod];
  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->Get(Form("hv22Gap_%i",icent));

    for (int id=0;id<npid;id++){
      hPT[icent][id]=(TProfile*)inFile->Get(Form("hPT_%i_%i",icent,id));
      hv22pt[icent][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i",icent,id));
      hv24pt[icent][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i",icent,id));
      hcov22prime[icent][id]=(TProfile*)inFile->Get(Form("hcov22prime_%i_%i",icent,id));
      hcov24prime[icent][id]=(TProfile*)inFile->Get(Form("hcov24prime_%i_%i",icent,id));
      hcov42prime[icent][id]=(TProfile*)inFile->Get(Form("hcov42prime_%i_%i",icent,id));
      hcov44prime[icent][id]=(TProfile*)inFile->Get(Form("hcov44prime_%i_%i",icent,id));
      hcov2prime4prime[icent][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i",icent,id));
      hv22ptGap[icent][id]=(TProfile*)inFile->Get(Form("hv22ptGap_%i_%i",icent,id));
      hcov22primeGap[icent][id]=(TProfile*)inFile->Get(Form("hcov22primeGap_%i_%i",icent,id));
      hcounter[icent][id]=(TProfile*)inFile->Get(Form("hcounter_%i_%i",icent,id));      
    }
  } // end of loop over centrality classes
  
  //==========================================================================================================================

  for (int icent=0;icent<ncent;icent++){
      
    for (int id=8;id<npid;id++){

      // hPT[icent][id] = (TProfile*)hPT[icent][id-7]->Clone();
      hv22pt[icent][id] = (TProfile*)hv22pt[icent][id-7]->Clone();
      hv24pt[icent][id] = (TProfile*)hv24pt[icent][id-7]->Clone();
      hcov22prime[icent][id] = (TProfile*)hcov22prime[icent][id-7]->Clone();
      hcov24prime[icent][id] = (TProfile*)hcov24prime[icent][id-7]->Clone();
      hcov42prime[icent][id] = (TProfile*)hcov42prime[icent][id-7]->Clone();
      hcov44prime[icent][id] = (TProfile*)hcov44prime[icent][id-7]->Clone();
      hcov2prime4prime[icent][id] = (TProfile*)hcov2prime4prime[icent][id-7]->Clone();
      hv22ptGap[icent][id] = (TProfile*)hv22ptGap[icent][id-7]->Clone();
      hcov22primeGap[icent][id] = (TProfile*)hcov22primeGap[icent][id-7]->Clone();
      // hcounter[icent][id] = (TProfile*)hcounter[icent][id-7]->Clone();

      // hPT[icent][id] -> Add(hPT[icent][id-3]);
      hv22pt[icent][id] -> Add(hv22pt[icent][id-3]);
      hv24pt[icent][id] -> Add(hv24pt[icent][id-3]);
      hcov22prime[icent][id] -> Add(hcov22prime[icent][id-3]);
      hcov24prime[icent][id] -> Add(hcov24prime[icent][id-3]);
      hcov42prime[icent][id] -> Add(hcov42prime[icent][id-3]);
      hcov44prime[icent][id] -> Add(hcov44prime[icent][id-3]);
      hcov2prime4prime[icent][id] -> Add(hcov2prime4prime[icent][id-3]);
      hv22ptGap[icent][id] -> Add(hv22ptGap[icent][id-3]);
      hcov22primeGap[icent][id] -> Add(hcov22primeGap[icent][id-3]);
      // hcounter[icent][id] -> Add(hcounter[icent][id-3]);
    }
    
  }
  
  //==========================================================================================================================
  /*
  // Filling pT bin
  double pt[ncent];
  double ept[ncent]={{0}}; // error bin pT = 0.0
  for (int icent=0; icent<ncent; icent++){
    for (int ipt=0; ipt<npt; ipt++){
      // pt[icent] = hPT[icent] -> GetBinContent(1);
      pt[icent] = ( bin_pT + bin_pT[ipt+1] ) / 2.;
    }
  }
  */
  //==========================================================================================================================
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

    for (int id=0;id<npid;id++){
      // Differential flow calculation
      // vPt.push_back((bin_pT+bin_pT[ipt+1])/2.);
      // ePt.push_back(0);
      // v22
      term cor2red = term(hv22pt[icent][id]);
      double v22Dif = cor2red.mVal/v22;
      double cov22prime = Covariance(hcov22prime[icent][id],hv22[icent],hv22pt[icent][id]);
      double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                          + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
      v2[0][id][icent] = v22Dif;
      v2e[0][id][icent] = ev22Dif;

      // v24
      term cor4red = term(hv24pt[icent][id]);
      double cov24prime = Covariance(hcov24prime[icent][id],hv22[icent],hv24pt[icent][id]);
      double cov42prime = Covariance(hcov42prime[icent][id],hv24[icent],hv22pt[icent][id]);
      double cov44prime = Covariance(hcov44prime[icent][id],hv24[icent],hv24pt[icent][id]);
      double cov2prime4prime = Covariance(hcov2prime4prime[icent][id],hv22pt[icent][id],hv24pt[icent][id]);
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
      term cor2redGap = term(hv22ptGap[icent][id]);
      double v22DifGap = cor2redGap.mVal/v22Gap;
      double cov22primeGap = Covariance(hcov22primeGap[icent][id],hv22Gap[icent],hv22ptGap[icent][id]);
      double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                          + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
      v2[2][id][icent] = v22DifGap;
      v2e[2][id][icent] = ev22DifGap;
    } // end of loop over PID
  } // end of loop over centrality classes
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] = new TGraphErrors(ncent,bin_cent,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grRefFl[imeth] -> SetMarkerStyle(marker[imeth]);
    grRefFl[imeth] -> SetMarkerSize(1.5);
    for (int id=0; id<npid; id++){
      grDifFl[imeth][id] = new TGraphErrors(ncent,bin_cent,v2[imeth][id],bin_centE,v2e[imeth][id]);
      grDifFl[imeth][id] -> SetMarkerStyle(marker[imeth]);
      grDifFl[imeth][id] -> SetMarkerSize(1.5);
    }
  }

  const char *grTitleDF[nmethod]={"v_{2}{2};centrality (%);v_{2}",
                                  "v_{2}{4};centrality (%);v_{2}",
                                  "v_{2}{2,#eta-gap};centrality (%);v_{2}"};
  outFile -> cd();
  for (int imethod=0; imethod<nmethod; imethod++){

    for (int id=0;id<npid;id++){
      grDifFl[imethod][id] -> SetTitle(grTitleDF[imethod]);
      grDifFl[imethod][id] -> Write(Form("gr_%i_%i",imethod,id));
    }
  
  }

  std::vector<TGraphErrors*> vgrv2pt[npid];
    for (int id=0;id<npid;id++){
      vgrv2pt[id].push_back(grDifFl[2][id]); // v2{gapped 2QC}
      for (int i=0; i<nmethod-1; i++){
        if (i==excludeMethod) continue;
        vgrv2pt[id].push_back(grDifFl[i][id]);
      }
    }
  
  TCanvas *cV2PT[npid];
  for (int id=0;id<npid;id++){
    cV2PT[id] = (TCanvas*) DrawTGraph(vgrv2pt[id],"",rangeRatio.at(0).first, rangeRatio.at(0).second, mincent, maxcent, minV2dif, maxV2dif,
                                              coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                              level.Data(), pidFancyNames.at(id).Data());

    cV2PT[id] -> SetName(pidFancyNames.at(id).Data());
    if (saveAsPNG) cV2PT[id] -> SaveAs(Form("./%s/DF_%s.png",outDirName.Data(),pidNames.at(id).Data()));
  }
  

  double ePT={0.};
  TCanvas *cV2CentRF;

  std::vector<TGraphErrors*> vgrv2pt1040;
  for (int imeth=0; imeth<nmethod; imeth++){
    // grRefFl[imeth][id] -> SetTitle(Form("V2 vs. pT, %s, centrality 10-40%%, %s",pidNames.at(id).Data(),grTitleDF[imeth]));
    grRefFl[imeth] -> SetTitle(grTitleDF[imeth]);
    grRefFl[imeth] -> Write(Form("grRF_%i",imeth));
  }
  vgrv2pt1040.push_back(grRefFl[2]);
  for (int imeth=0;imeth<nmethod-1;imeth++){
    if (imeth==excludeMethod) continue;
    vgrv2pt1040.push_back(grRefFl[imeth]);
  }
  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2pt1040,"",rangeRatio.at(0).first, rangeRatio.at(0).second, mincent, maxcent, minV2dif, maxV2dif,
                                        coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                        level.Data(), "Reference flow");
  cV2CentRF -> SetName(hname);
  if (saveAsPNG) cV2CentRF -> SaveAs(Form("./%s/RF.png",outDirName.Data()));
  
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // delete HRes[icent];
    delete hv22[icent];
    delete hv24[icent];
    delete hcov24[icent];
    delete hv22Gap[icent];
    // for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        // delete hv2EP[icent][id];
        // delete hPT[icent][id];
        delete hv22pt[icent][id];
        delete hv24pt[icent][id];
        delete hcov22prime[icent][id];
        delete hcov24prime[icent][id];
        delete hcov42prime[icent][id];
        delete hcov44prime[icent][id];
        delete hcov2prime4prime[icent][id];
        delete hv22ptGap[icent][id];
        delete hcov22primeGap[icent][id];
        // delete hcounter[icent][id];
      }
    // } // end of loop over pt bin
  } // end of loop over centrality classes
  inFile->Close();
}

