#include "Func_StatErrCalc.C"
#include "DrawTGraph.C"
// #include <vector>
// #include <cmath>
// using namespace std; 

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

static const double maxpt = 3.0; // max pt
static const double minpt = 0.1; // min pt

static const int ncent = 8; // 0-80 %
static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
static const double bin_centE[ncent] = {0};
static const int npt = 8; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_pT[npt+1]={0.1, 0.3, 0.6, 0.9, 1.2, 1.5, 1.9, 2.4, 3.};

void v2plot_differential_flow(TString inFileName="../ROOTFile/sum.root", TString outFileName="../CompareResult/Vinh.root"){
  bool bDrawPlots = 1;
  bool drawDistributions = 0;
  bool cent1040 = 1;
  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile
  // char analysis[20]={"pure"};

  TFile *inFile, *outFile;
  inFile = new TFile("../ROOTFile/sum.root","read");
  outFile = new TFile("../CompareResult/Vinh.root","recreate");
  
  if (drawDistributions){
    TCanvas *cTemp = new TCanvas("cTemp","cTemp",200,10,800,450);

    TH1I *hMult = (TH1I*)inFile->Get("hMult");
    hMult -> Draw();
    sprintf(hname,"../Graphics/mult.png");
    cTemp -> Draw();
    cTemp -> SaveAs(hname);

    TH1I *hEvt = (TH1I*)inFile->Get("hEvt");
    hEvt -> Draw();
    sprintf(hname,"../Graphics/evt.png");
    cTemp -> Draw();
    cTemp -> SaveAs(hname);

    TH1F *hEta = (TH1F*)inFile->Get("hEta");
    hEta -> Draw();
    sprintf(hname,"../Graphics/eta.png");
    cTemp -> SaveAs(hname);  

    TH1F *hPhi = (TH1F*)inFile->Get("hPhi");
    hPhi -> Draw();
    sprintf(hname,"../Graphics/phi.png");
    cTemp -> SaveAs(hname);

    TH1F *hPt = (TH1F*)inFile->Get("hPt");
    hPt -> Draw();
    sprintf(hname,"../Graphics/pt.png");
    cTemp -> SaveAs(hname);
  }

  // Input hist
  // TProfile for reference flow
  // TProfile *hv2MC[ncent];       // profile for MC integrated v2
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow
  TProfile *hPT[ncent][npt];       // profile pt 
  // TProfile *hv2MCpt[ncent][npt];   // profile v2pt from MC toy   
  TProfile *hv22pt[ncent][npt];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];    // profile <<4'>> from 4th Q-Cumulants
  // TProfile for covariance calculation according to (C.12)
  // Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider. 
  // Appendix C
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

  TProfile *hv2EP[ncent][npt];	// elliptic flow from EP method
  TProfile *hv22EP[ncent];        // elliptic flow cent: 10-40% from EP method
  TProfile *HRes[ncent];

  // OUTPUT

  TGraph *grshade[ncent];
  TGraphErrors *grDifFl[4][ncent];    // v2(pt); 4 = {MC, 2QC, 4QC, EP}
  TGraphErrors *grRefFl[ncent];       // 
  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv22EP_%i",icent);
    hv22EP[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"HRes_%i",icent);
    HRes[icent] = (TProfile*)inFile->Get(hname);
    // sprintf(hname,"hv2MC_%i",icent);
    // hv2MC[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv22_%i",icent);
    hv22[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv24_%i",icent);
    hv24[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcov24_%i",icent);
    hcov24[icent] = (TProfile*)inFile->Get(hname);

    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      sprintf(hname,"hv2EP_%i_%i",icent,ipt);
      hv2EP[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hPT_%i_%i",icent,ipt);
      hPT[icent][ipt]=(TProfile*)inFile->Get(hname);

      // sprintf(hname,"hv2MCpt_%i_%i",icent,ipt);
      // hv2MCpt[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hv22pt_%i_%i",icent,ipt);
      hv22pt[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hv24pt_%i_%i",icent,ipt);
      hv24pt[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov22prime_%i_%i",icent,ipt);
      hcov22prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov24prime_%i_%i",icent,ipt);
      hcov24prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov42prime_%i_%i",icent,ipt);
      hcov42prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov44prime_%i_%i",icent,ipt);
      hcov44prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov2prime4prime_%i_%i",icent,ipt);
      hcov2prime4prime[icent][ipt]=(TProfile*)inFile->Get(hname);
    } // end of loop over pt bin
  } // end of loop over centrality classes
  // inFile -> Close();

  //==========================================================================================================================
  if (cent1040){
  // Add
  for (int icent=2; icent<4; icent++){ // loop over centrality classes
    hv22EP[1] -> Add(hv22EP[icent]);
    HRes[1] -> Add(HRes[icent]);
    hv22[1] -> Add(hv22[icent]);
    hv24[1] -> Add(hv24[icent]);
    hcov24[1] -> Add(hcov24[icent]);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin

      hv2EP[1][ipt]-> Add(hv2EP[icent][ipt]);
      hPT[1][ipt]-> Add(hPT[icent][ipt]);
      hv22pt[1][ipt]-> Add(hv22pt[icent][ipt]);
      hv24pt[1][ipt]-> Add(hv24pt[icent][ipt]);
      hcov22prime[1][ipt]-> Add(hcov22prime[icent][ipt]);
      hcov24prime[1][ipt]-> Add(hcov24prime[icent][ipt]);
      hcov42prime[1][ipt]-> Add(hcov42prime[icent][ipt]);
      hcov44prime[1][ipt]-> Add(hcov44prime[icent][ipt]);
      hcov2prime4prime[1][ipt]-> Add(hcov2prime4prime[icent][ipt]);
    } // end of loop over pt bin
  }
  }
  //==========================================================================================================================

  // Filling pT bin
  double pt[ncent][npt];
  double ept[ncent][npt]={{0}}; // error bin pT = 0.0
  for (int icent=0; icent<ncent; icent++){
    for (int ipt=0; ipt<npt; ipt++){
      // pt[icent][ipt] = hPT[icent][ipt] -> GetBinContent(1);
      pt[icent][ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
    }
  }
  //==========================================================================================================================
  
  // reference flow comparison
  double v2[ncent][4];
  double ev2[ncent][4];
  double x[4]={0.5,1.5,2.5,3.5};
  double ex[4]={0};

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // Reference flow calculation

    double v2MCint;  // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
    double v2MCintE; // Standard error of integrated v_{2}{MC}

    double v22int;  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
    double v22intE; // Standard error of integrated v_{2}{2,QC}
    double cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
    double cor2E;   // stat. err. of 2-particle correlations, s(<<2>>)

    double v24int;  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
    double v24intE; // Standard error of integrated v_{2}{4,QC}
    double cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
    double cor4E;   // error of <<4>>

    double sumw2cor2;    // sumw2 of <2>
    double sumwcor2;     // sumw of <2>
    double sumw2cor4;    // sumw2 of <4>
    double sumwcor4;     // sumw of <4>

    double sumwcor24;    // sum(w<2>,w<4>)
    double cov24;        // Cov(<2>,<4>)

    double v2EPint;
    double v2EPintE;
    //=============================================
    //v2{MC}
    // v2MCint  = hv2MC[icent] -> GetBinContent(1);
    // v2MCintE = hv2MC[icent] -> GetBinError(1);
    //=============================================
    // v2{2,QC}
    // estimate of the 2-particle reference flow (C.22)
    cor2 = hv22[icent] -> GetBinContent(1);  // <<2>>
    v22int = Vn2(cor2);
    // statistical error of the 2-particle reference flow estimate (C.24)
    cor2E = sx(hv22[icent]);
    hv22[icent] -> GetStats(stats);
    sumwcor2 = stats[0];
    sumw2cor2 = stats[1];
    v22intE = Evn2(cor2,cor2E,sumwcor2,sumw2cor2);
    //=============================================
    // v2{4,QC}
    // estimate of the 4-particle reference flow (C.27)
    cor4 = hv24[icent]->GetBinContent(1);  // <<4>>
    v24int = Vn4(cor2,cor4);
    // statistical error of the 4-particle reference flow estimate (C.28)
    cor4E = sx(hv24[icent]);
    hv24[icent] -> GetStats(stats);
    sumwcor4 = stats[0];
    sumw2cor4 = stats[1];
    // calculate covariance of <2> and <4>
    cov24 = Cov(hcov24[icent],hv22[icent],hv24[icent]);
    sumwcor24 = Sumwxwy(hcov24[icent]);
    v24intE = Evn4(cor2,cor2E,sumwcor2,sumw2cor2,
                  cor4,cor4E,sumwcor4,sumw2cor4,
                  cov24,sumwcor24);
    //=============================================
    // v2{#eta sub-event}
    double res2 = sqrt(HRes[icent]->GetBinContent(1));
    double v2obs = hv22EP[icent]->GetBinContent(1);
    v2EPint = v2obs / res2;
    double dv2obs = hv22EP[icent]->GetBinError(1);
    double dres2 = HRes[icent]->GetBinError(1);

    // v2EPintE = sqrt(dv2obs*dv2obs/res2/res2 + v2obs*v2obs/(4*pow(res2,6)*dres2*dres2));
    v2EPintE = hv22EP[icent]->GetBinError(1)/res2;
    //=============================================
    // Reference flow comparison: MC, 2QC, 4QC, eta sub-event
    v2[icent][0] = v2MCint;
    v2[icent][1] = v22int;
    v2[icent][2] = v24int;
    v2[icent][3] = v2EPint;

    ev2[icent][0] = v2MCintE;
    ev2[icent][1] = v22intE;
    ev2[icent][2] = v24intE;
    ev2[icent][3] = v2EPintE;

    grRefFl[icent] = new TGraphErrors(4,x,v2[icent],ex,ev2[icent]);
    grRefFl[icent]->SetMarkerColor(kRed);
    grRefFl[icent]->SetMarkerStyle(20);
    grRefFl[icent]->SetMarkerSize(1.3);
    grRefFl[icent]->SetDrawOption("P");
    // Set a shade between error of v2MC
    grshade[icent] = new TGraph(10);
    for (int i=0; i<5; i++) {
      grshade[icent]->SetPoint(i,i+0.005,v2[icent][0]+ev2[icent][0]);
      grshade[icent]->SetPoint(5+i,4+0.005-i,v2[icent][0]-ev2[icent][0]);
    }
    grshade[icent] -> SetFillStyle(1001);
    grshade[icent] -> SetFillColor(18);
    grshade[icent] -> SetDrawOption("f");

    //==========================================================================================================================

    // Differential flow calculation


    double v2MCpt[npt]; // v2 in given pT bin
    double ev2MCpt[npt]; // standard error of v2 in given pT bin
  
    double cor2Red[npt];         // Differential 2nd order cumulant d_{2}{2} = <<2'>>
    double cor2RedE[npt];        // Error of <<2'>>
    double v22dif[npt];      // Differential elliptic flow v'_{2}{2} extracted from 2nd order cumulants
                            // v'_{2}{2} = d_{2}{2} / sqrt( c_{2}{2} )
    double v22difE[npt];     // Error of v'_{2}{2}
    
    double cor4Red[npt];    // Reduced average all-event 4-particle correlation <<4'>>
    double cor4RedE[npt];   // Error of <<4'>>
    double v24dif[npt];      // Differential elliptic flow v'_{2}{4} extracted from 4th order cumulants
                            // v'_{2}{4} = -d_{2}{4} / pow( -c_{2}{4} , 3/4 )
    double v24difE[npt];     // Error of v'_{2}{4}

    double sumwcor22prime[npt];        // sum(w(<2>)*w(<2'>))
    double cov22prime[npt];            // Cov(<2>,<2'>)
    double sumwcor24prime[npt];        // sum(w(<2>)*w(<4'>))
    double cov24prime[npt];            // Cov(<2>,<4'>)
    double sumwcor42prime[npt];        // sum(w(<4>)*w(<2'>))
    double cov42prime[npt];            // Cov(<4>,<2'>)
    double sumwcor44prime[npt];        // sum(w(<4>)*w(<4'>))
    double cov44prime[npt];            // Cov(<4>,<4'>)
    double sumwcor2prime4prime[npt];   // sum(w(<2'>)*w(<4'>))
    double cov2prime4prime[npt];       // Cov(<2'>,<4'>)

    double sumw2cor2red[npt]; // sumw2 of <2'>
    double sumwcor2red[npt];  // sumw of <2'>    
    double sumw2cor4red[npt]; // sumw2 of <4'>
    double sumwcor4red[npt];  // sumw of <4'>

    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      
      // Differential flow v2MC

      // v2MCpt[ipt]  = hv2MCpt[icent][ipt] -> GetBinContent(1);
      // ev2MCpt[ipt] = hv2MCpt[icent][ipt] -> GetBinError(1);

      // 2-particle correlations
      // estimate of the 2-particle differential flow (C.41)
      cor2Red[ipt] = hv22pt[icent][ipt]->GetBinContent(1);
      v22dif[ipt] = Vn2Dif(cor2Red[ipt],cor2);

      // statistical error of the 2-particle differential flow estimate (C.42)
      cor2RedE[ipt] = sx(hv22pt[icent][ipt]);
      hv22pt[icent][ipt] -> GetStats(stats);
      sumwcor2red[ipt] = stats[0];
      sumw2cor2red[ipt] = stats[1];

      // calculate covariance of <2> and <2'>
      cov22prime[ipt] = Cov(hcov22prime[icent][ipt],hv22[icent],hv22pt[icent][ipt]);
      sumwcor22prime[ipt] = Sumwxwy(hcov22prime[icent][ipt]);
      v22difE[ipt] = Evn2dif(cor2, cor2E, sumwcor2, sumw2cor2,
                             cor2Red[ipt], cor2RedE[ipt], sumwcor2red[ipt],sumw2cor2red[ipt],
                             cov22prime[ipt], sumwcor22prime[ipt]);

      // 4-particle correlations
      // estimate of the 4-particle differential flow (C.45)
      cor4Red[ipt] = hv24pt[icent][ipt]->GetBinContent(1);
      v24dif[ipt] = Vn4Dif(cor2Red[ipt], cor2, cor4Red[ipt], cor4);
      // statistical error of the 4-particle differential flow estimate (C.46)
      cor4RedE[ipt] = sx(hv24pt[icent][ipt]);
      hv24pt[icent][ipt] -> GetStats(stats);
      sumwcor4red[ipt] = stats[0];
      sumw2cor4red[ipt] = stats[1];

      // calculate covariance of <2> and <4'>
      cov24prime[ipt] = Cov(hcov24prime[icent][ipt],hv22[icent],hv24pt[icent][ipt]);
      sumwcor24prime[ipt] = Sumwxwy(hcov24prime[icent][ipt]);

      // calculate covariance of <4> and <2'>
      cov42prime[ipt] = Cov(hcov42prime[icent][ipt],hv24[icent],hv22pt[icent][ipt]);
      sumwcor42prime[ipt] = Sumwxwy(hcov42prime[icent][ipt]);

      // calculate covariance of <4> and <4'>
      cov44prime[ipt] = Cov(hcov44prime[icent][ipt],hv24[icent],hv24pt[icent][ipt]);
      sumwcor44prime[ipt] = Sumwxwy(hcov44prime[icent][ipt]);

      // calculate covariance of <2'> and <4'>
      cov2prime4prime[ipt] = Cov(hcov2prime4prime[icent][ipt],hv22pt[icent][ipt],hv24pt[icent][ipt]);
      sumwcor2prime4prime[ipt] = Sumwxwy(hcov2prime4prime[icent][ipt]);
      v24difE[ipt] = Evn4dif(cor2, cor2E, sumwcor2, sumw2cor2,
                          cor2Red[ipt], cor2RedE[ipt], sumwcor2red[ipt], sumw2cor2red[ipt],
                          cor4, cor4E, sumwcor4, sumw2cor4,
                          cor4Red[ipt], cor4RedE[ipt], sumwcor4red[ipt], sumw2cor4red[ipt],
                          cov24, sumwcor24, cov22prime[ipt], sumwcor22prime[ipt],
                          cov2prime4prime[ipt], sumwcor2prime4prime[ipt], cov44prime[ipt], sumwcor44prime[ipt],
                          cov24prime[ipt], sumwcor24prime[ipt], cov42prime[ipt], sumwcor42prime[ipt]);

    } // end of loop for all pT bin

    // Monte-Carlo differential flow
    grDifFl[3][icent] = new TGraphErrors(npt,pt[icent],v2MCpt,ept[icent],ev2MCpt);
    grDifFl[3][icent] -> SetMarkerColor(kRed+1);
    grDifFl[3][icent] -> SetMarkerStyle(25);
    // 2QC differential flow
    grDifFl[1][icent] = new TGraphErrors(npt,pt[icent],v22dif,ept[icent],v22difE);
    grDifFl[1][icent] -> SetMarkerColor(kGreen+1);
    grDifFl[1][icent] -> SetMarkerStyle(20);
    // 4QC differential flow
    grDifFl[2][icent] = new TGraphErrors(npt,pt[icent],v24dif,ept[icent],v24difE);
    grDifFl[2][icent] -> SetMarkerColor(kAzure+2);
    grDifFl[2][icent] -> SetMarkerStyle(22);
    for (int i=1; i<4; i++){
      grDifFl[i][icent] -> SetMarkerSize(1.3);
      grDifFl[i][icent] -> SetDrawOption("P");
    }
  } // end of loop over centrality classes
  //==========================================================================================================================

  //==========================================================================================================================

  const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};

  // Elliptic flow from eta sub-event method
  for (int icent=0; icent<ncent; icent++){
    double v2EP[npt]={0}, ev2EP[npt]={0};
    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      // v2EP[ipt] = hv2EP[ipt]->GetBinContent(icent+1);
      // ev2EP[ipt] = hv2EP[ipt]->GetBinError(icent+1);

      double res2 = sqrt(HRes[icent]->GetBinContent(1));
      double v2obs = hv2EP[icent][ipt]->GetBinContent(1);
      v2EP[ipt] = v2obs / res2;
      double dv2obs = hv2EP[icent][ipt]->GetBinError(1);
      double dres2 = HRes[icent]->GetBinError(1);

      // ev2EP[ipt] = sqrt(dv2obs*dv2obs/res2/res2 + v2obs*v2obs/(4*pow(res2,6)*dres2*dres2));
      ev2EP[ipt] = hv2EP[icent][ipt]->GetBinError(1);
    }
    // Event plane differential flow
    grDifFl[0][icent] = new TGraphErrors(npt,pt[icent],v2EP,ept[icent],ev2EP);
    grDifFl[0][icent] -> SetMarkerColor(kRed);
    grDifFl[0][icent] -> SetMarkerStyle(25);
    grDifFl[0][icent] -> SetMarkerSize(1.3);
    grDifFl[0][icent] -> SetDrawOption("P");
  }

  //==========================================================================================================================

  const char *grTitleDF[4]={"[1] v_{2}{#eta sub-event};p_{T}, GeV/c;v_{2}","[2] v_{2}{2,QC};p_{T}, GeV/c;v_{2}","[3] v_{2}{4,QC};p_{T}, GeV/c;v_{2}","v_{2}{MC};p_{T}, GeV/c;v_{2}"};
  
  outFile -> cd();

  for (int i=0; i<3; i++){
    for (int icent=0;icent<ncent;icent++){
      sprintf(hname,"gr_cent%i_%i",icent,i);
      grDifFl[i][icent] -> SetTitle(grTitleDF[i]);
      grDifFl[i][icent] -> Write(hname);
    }
  }
  outFile -> Close();

  if (!bDrawPlots) return;


  //=============================================
  std::vector<TGraphErrors*> vgrv2pt[2];
  for (int icent=0; icent<2; icent++){
    for (int i=0; i<3; i++){
      vgrv2pt[icent].push_back(grDifFl[i][icent]);
    }  
  }
  TCanvas *cV2PT[2];
  // cV2PT[0] = (TCanvas*) DrawTGraph(vgrv2pt[0],"",0.65, 1.35, 0., maxpt, 0, 0.2, 0.18, 0.65, 0.5, 0.89, "Centrality 0-10%");
  // cV2PT[0] -> SetName("Cent10-40");
  // cV2PT[0] -> SaveAs("../Graphics/DFCent0-10.png");

  cV2PT[1] = (TCanvas*) DrawTGraph(vgrv2pt[1],"",0.88, 1.12, 0., maxpt, -0.01, 0.2, 0.18, 0.65, 0.5, 0.89, "Centrality 10-40%");
  cV2PT[1] -> SetName("Cent10-40");
  cV2PT[1] -> SaveAs("../Graphics/DFCent10-40.png");

  // double ymin = TMath::MinElement(4,v2[1])*0.98;
  // double ymax = TMath::MaxElement(4,v2[1])*1.02;
  double ymin = 0.025;
  double ymax = 0.035;
  TCanvas *c1040 = new TCanvas("c1040","c1040",200,10,800,600);
  TH2F *h1040 = new TH2F("h1040","Reference flow, 10-40% centrality",4,0,4,10,ymin,ymax);
  h1040 = new TH2F("","",3,1,4,10,ymin,ymax);
  h1040->SetYTitle("v_{2}");
  h1040->SetCanExtend(TH1::kAllAxes);
  TAxis* a = h1040 -> GetXaxis();
  for (int j=1; j<4; j++) h1040->Fill(ch[j],(ymin+ymax)/2.,1);
  h1040->GetXaxis()->SetLabelSize(0.05);
  a->SetNdivisions(300); // 3 division, 0 sub-division
  h1040->Draw();
  // grshade[1] -> SetFillStyle(1001);
  // grshade[1] -> SetFillColor(18);
  // grshade[1] -> Draw("f");
  grRefFl[1] -> SetTitle("Reference flow, 10-40% centrality");
  grRefFl[1] -> Draw("P");
  TPaveText *ptext1 = new TPaveText(0.2,0.74,0.6,0.89,"NDC NB"); // right corner 0.56,0.72,0.89,0.89
  ptext1->SetBorderSize(0);
  ptext1->SetFillColor(0);
  ptext1->AddText("UrQMD, Au+Au, #sqrt{s_{NN}}=7.7 GeV");
  ptext1->AddText("10-40% centrality");
  ptext1->Draw();
  TLine line[3];
  for (int i=0;i<3;i++){
    line[i].SetLineWidth(2.);
    line[i].SetLineStyle(2);
  }
  line[0].DrawLine(1.,v2[1][1],4.,v2[1][1]);
  line[1].DrawLine(1.,v2[1][2],4.,v2[1][2]);
  line[2].DrawLine(1.,v2[1][3],4.,v2[1][3]);
  c1040 -> SaveAs("../Graphics/RFCent10-40.png");


}

void v2plot_integrated_flow(TString inFileName, TString outFileName){
  char hname[400];
  TFile *inFile = new TFile(inFileName.Data(),"read");
  TFile *outFile = new TFile(outFileName.Data(),"recreate");
  // Input histograms
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hPT[ncent][npt];       // profile pt 
  TProfile *hv22pt[ncent][npt];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>
  TProfile *hv2EP[ncent][npt];	// elliptic flow from EP method
  TProfile *hv22EP[ncent];      
  TProfile *HRes[ncent];
  // Get histograms
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv22EP_%i",icent);
    hv22EP[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"HRes_%i",icent);
    HRes[icent] = (TProfile*)inFile->Get(hname);
    // sprintf(hname,"hv22_%i",icent);
    // hv22[icent] = (TProfile*)inFile->Get(hname);
    // sprintf(hname,"hv24_%i",icent);
    // hv24[icent] = (TProfile*)inFile->Get(hname);
    // sprintf(hname,"hcov24_%i",icent);
    // hcov24[icent] = (TProfile*)inFile->Get(hname);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      sprintf(hname,"hv2EP_%i_%i",icent,ipt);
      hv2EP[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hPT_%i_%i",icent,ipt);
      hPT[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hv22pt_%i_%i",icent,ipt);
      hv22pt[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hv24pt_%i_%i",icent,ipt);
      hv24pt[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov22prime_%i_%i",icent,ipt);
      hcov22prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov24prime_%i_%i",icent,ipt);
      hcov24prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov42prime_%i_%i",icent,ipt);
      hcov42prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov44prime_%i_%i",icent,ipt);
      hcov44prime[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hcov2prime4prime_%i_%i",icent,ipt);
      hcov2prime4prime[icent][ipt]=(TProfile*)inFile->Get(hname);
    } // end of loop over pt bin
  } // end of loop over centrality classes
  // inFile -> Close();
  for (int icent=0;icent<ncent;icent++){
    hv22[icent] = (TProfile*) hv22pt[icent][0]->Clone();
    hv24[icent] = (TProfile*) hv24pt[icent][0]->Clone();
    hcov24[icent] = (TProfile*) hcov2prime4prime[icent][0]->Clone();
    for (int ipt=1;ipt<npt;ipt++){
      hv22[icent]->Add(hv22pt[icent][ipt]);
      hv24[icent]->Add(hv24pt[icent][ipt]);
      hcov24[icent]->Add(hcov2prime4prime[icent][ipt]);
    }
  }

  std::vector<double> vV2EP, vV22, vV24;
  std::vector<double> eV2EP, eV22, eV24;

  for (int icent=0;icent<ncent;icent++){
    // EP
    vV2EP.push_back( hv22EP[icent]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
    eV2EP.push_back( hv22EP[icent]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
    // 2QC
    term cor2 = term(hv22[icent]);
    vV22.push_back(sqrt(cor2.mVal));
    eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    vV24.push_back(v24);
    eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );
  }
  TGraphErrors *grIntFlowVsCent[3];       // v2(cent); 4 = {2QC, 4QC, EP, MC}
  grIntFlowVsCent[0] = new TGraphErrors(ncent,bin_cent,&vV2EP[0],bin_centE,&eV2EP[0]);
  grIntFlowVsCent[0] -> SetMarkerColor(kRed);
  grIntFlowVsCent[0] -> SetMarkerStyle(25);  

  grIntFlowVsCent[1] = new TGraphErrors(ncent,bin_cent,&vV22[0],bin_centE,&eV22[0]);
  grIntFlowVsCent[1]->SetMarkerColor(kGreen+1);
  grIntFlowVsCent[1]->SetMarkerStyle(20);

  grIntFlowVsCent[2] = new TGraphErrors(ncent,bin_cent,&vV24[0],bin_centE,&eV24[0]);
  grIntFlowVsCent[2] -> SetMarkerColor(kAzure+2);
  grIntFlowVsCent[2] -> SetMarkerStyle(22);

  for (int i=0;i<3;i++){
    grIntFlowVsCent[i]->SetMarkerSize(1.5);
    grIntFlowVsCent[i]->SetDrawOption("P");
  }
  const char *grTitle[3]={"[1] v_{2}{#eta sub-event};cent, %;v_{2}","[2] v_{2}{2,QC};cent, %;v_{2}","[3] v_{2}{4,QC};cent, %;v_{2}"};

  outFile -> cd();
  for (int i=0; i<3; i++){
    sprintf(hname,"grRF_%i",i);
    grIntFlowVsCent[i] -> SetTitle(grTitle[i]);
    grIntFlowVsCent[i] -> Write(hname);
  }
  outFile -> Close();  


  std::vector<TGraphErrors*> vgr;
  for (int i=0; i<3; i++){
    vgr.push_back(grIntFlowVsCent[i]);
  }

  TCanvas *can;
  can = (TCanvas*) DrawTGraph(vgr,"",0.79, 1.04, 0, 60, -0.005, 0.1 , 0.18, 0.65, 0.5, 0.89);
  sprintf(hname,"v2 vs cent");
  can -> SetName(hname);
  sprintf(hname,"../Graphics/v2centratio.png");
  can -> SaveAs(hname);
}
void v2plot(){
  char inFile[400], outFile[400];
  sprintf(inFile,"../ROOTFile/sum.root");
  sprintf(outFile,"../CompareResult/Vinh.root");
  v2plot_differential_flow(inFile,outFile);
  sprintf(outFile,"../CompareResult/Vinh_RF.root");
  v2plot_integrated_flow(inFile,outFile);
}