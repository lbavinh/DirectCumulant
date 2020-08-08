#include "Func_StatErrCalc.C"
void refflowv2plot(){
  // TFile *inFile = new TFile("./ROOTFile/nonflow_50mil_0.2rate.root","read");
  // TFile *outFile = new TFile("./ROOTFile/TGraphError_refflow_nonflow.root","recreate");

  TFile *inFile = new TFile("./ROOTFile/pure_50mil.root","read");
  TFile *outFile = new TFile("./ROOTFile/TGraphError_refflow_pure.root","recreate");

  static const int ncent = 8; // 0-80%
  static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
  static const double bin_centE[ncent] = {0};
  static const Float_t maxpt = 3.5; // max pt
  static const Float_t minpt = 0.2; // min pt
  // static const int npt = 24; // 0.2 - 3.5 GeV/c 
  // static const double bin_pT[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
  //                                 1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,
  //                                 2.6,2.8,3.0,3.2,3.5};
  static const int npt = 12;        // 0.2 - 3.5 GeV/c
  static const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  // Input hist

  // TProfile for reference flow
  TProfile *hv2MC[ncent];       // profile for MC integrated v2
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow
  TProfile *hPT[ncent][npt];       // profile pt 
  TProfile *hv2MCpt[ncent][npt];   // profile v2pt from MC toy   
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

  TH1F *hv2EP[ncent][npt];	// elliptic flow from EP method
  TH1F *hv22EP[npt];        // elliptic flow cent: 10-40% from EP method


  // OUTPUT
  TGraphErrors *grRefFl[4];     // 4 = {MC, 2QC, 4QC, EP}
  // Temporary variables
  char hname[800]; // histogram hname
  TProfile *pr; // temporary TProfile for TProfile extracting from root file
  TProfile *prx, *pry, *prxy; // for covariance calculation
  Double_t stats[6]; // stats of TProfile
  Double_t rms; // root of mean squared = standard deviation (temporary variable)
  int nent; // number of entries (temporary variable)
  Double_t err; // standard error (temporary variable)



  // Get TProfile histograms from ROOTFile
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv2MC_cent%i",icent);
    hv2MC[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv22_cent%i",icent);
    hv22[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv24_cent%i",icent);
    hv24[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcov24_cent%i",icent);
    hcov24[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv22EP_cent%i",icent);
    hv22EP[icent] = (TH1F*)inFile->Get(hname);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
        sprintf(hname,"hPT_cent%i_pt%i",icent,ipt);
        hPT[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv2MCpt_cent%i_pt%i",icent,ipt);
        hv2MCpt[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv22pt_cent%i_pt%i",icent,ipt);
        hv22pt[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv24pt_cent%i_pt%i",icent,ipt);
        hv24pt[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov22prime_cent%i_pt%i",icent,ipt);
        hcov22prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov24prime_cent%i_pt%i",icent,ipt);
        hcov24prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov42prime_cent%i_pt%i",icent,ipt);
        hcov42prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov44prime_cent%i_pt%i",icent,ipt);
        hcov44prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov2prime4prime_cent%i_pt%i",icent,ipt);
        hcov2prime4prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv2EP_cent%i_pt%i",icent,ipt);
        hv2EP[icent][ipt]=(TH1F*)inFile->Get(hname);
    } // end of loop over pt bin
  } // end of loop over centrality classes

  //==========================================================================================================================
  // Filling pT bin
  Double_t pt[ncent][npt];
  Double_t ept[ncent][npt]={{0}}; // error bin pT = 0.0
  for (int icent=0; icent<ncent; icent++){
    for (int ipt=0; ipt<npt; ipt++){
      // pt[icent][ipt] = hPT[icent][ipt] -> GetBinContent(1);
      pt[icent][ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
    }
  }
  //==========================================================================================================================
  
  // reference flow comparison
  double v2[4][ncent];
  double ev2[4][ncent];


  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // Reference flow calculation

    Double_t v2MCint;  // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
    Double_t v2MCintE; // Standard error of integrated v_{2}{MC}

    Double_t v22int;  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
    Double_t v22intE; // Standard error of integrated v_{2}{2,QC}
    Double_t cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
    Double_t cor2E;   // stat. err. of 2-particle correlations, s(<<2>>)

    Double_t v24int;  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
    Double_t v24intE; // Standard error of integrated v_{2}{4,QC}
    Double_t cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
    Double_t cor4E;   // error of <<4>>

    Double_t sumw2cor2;    // sumw2 of <2>
    Double_t sumwcor2;     // sumw of <2>
    Double_t sumw2cor4;    // sumw2 of <4>
    Double_t sumwcor4;     // sumw of <4>

    Double_t sumwcor24;    // sum(w<2>,w<4>)
    Double_t cov24;        // Cov(<2>,<4>)

    Double_t v2EPint;
    Double_t v2EPintE;
    //=============================================
    //v2{MC}
    v2MCint  = hv2MC[icent] -> GetBinContent(1);
    v2MCintE = hv2MC[icent] -> GetBinError(1);
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
    v2EPint = hv22EP[icent]->GetMean();
    rms = hv22EP[icent]->GetRMS();
    nent = hv22EP[icent]->GetEntries();
    err = rms/sqrt(nent);
    v2EPintE = err;
    //=============================================
    // Reference flow comparison: MC, 2QC, 4QC, eta sub-event
    v2[0][icent] = v2MCint;
    v2[1][icent] = v22int;
    v2[2][icent] = v24int;
    v2[3][icent] = v2EPint;

    ev2[0][icent] = v2MCintE;
    ev2[1][icent] = v22intE;
    ev2[2][icent] = v24intE;
    ev2[3][icent] = v2EPintE;
  } // end of loop over centrality classes
  grRefFl[0] = new TGraphErrors(ncent,bin_cent,v2[0],bin_centE,ev2[0]);
  grRefFl[0]->SetMarkerColor(kRed+1);
  grRefFl[0]->SetMarkerStyle(25);

  grRefFl[1] = new TGraphErrors(ncent,bin_cent,v2[1],bin_centE,ev2[1]);
  grRefFl[1]->SetMarkerColor(kGreen+1);
  grRefFl[1]->SetMarkerStyle(20);

  grRefFl[2] = new TGraphErrors(ncent,bin_cent,v2[2],bin_centE,ev2[2]);
  grRefFl[2] -> SetMarkerColor(kAzure+2);
  grRefFl[2] -> SetMarkerStyle(22);

  grRefFl[3] = new TGraphErrors(ncent,bin_cent,v2[3],bin_centE,ev2[3]);
  grRefFl[3] -> SetMarkerColor(kBlack);
  grRefFl[3] -> SetMarkerStyle(23);  

  for (int i=0;i<4;i++){
    grRefFl[i]->SetMarkerSize(1.3);
    grRefFl[i]->SetDrawOption("P");
  }
  //==========================================================================================================================

  const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};
  outFile -> cd();
  // int mycent = 3;
  for (int i=0; i<4; i++){
    sprintf(hname,"gr_%i",i);
    grRefFl[i] -> SetTitle(ch[i]);
    grRefFl[i] -> Write(hname);
  }
  outFile -> Close();
}