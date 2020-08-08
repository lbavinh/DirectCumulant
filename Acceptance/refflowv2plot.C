#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TVectorD.h"
#include "TString.h"
#include "Func_StatErrCalc.C"
using namespace std;
#include <fstream>

void refflowv2plot(){
  TFile* inFile = new TFile("./ROOTFile/acceptance_test.root","read");

  static const int ncent = 8; // 0-80%
  static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
  static const double bin_centE[ncent] = {0};
  static const double maxpt = 3.5; // max pt
  static const double minpt = 0.2; // min pt
  static const int npt = 12;        // 0.2 - 3.5 GeV/c
  static const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  // Input hist

  // TProfile for reference flow (RF)
  TProfile *hv2MC[ncent]; // profile for MC integrated v2
  TProfile *hv22[ncent];  // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];  // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow (DF)
  TProfile *hPT[npt];     // profile pt
  TProfile *hv2MCpt[ncent][npt]; // profile v2pt from MC toy
  TProfile *hv22pt[ncent][npt];  // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];  // profile <<4'>> from 4th Q-Cumulants

  // TProfile for covariance calculation according to (C.12), Appendix C
  // in Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider.
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

  // non-uniform acceptance correction
  // Reference flow acceptance correction
  TProfile *hcos2phi1, *hsin2phi1, *hcos2phi12, *hsin2phi12, *hcos2phi123, *hsin2phi123; // 6

  // Differential flow acceptance correction
  TProfile *hcos2psi1[npt], *hsin2psi1[npt], *hcos2psi1phi2[npt], *hsin2psi1phi2[npt],
           *hcos2psi1pphi23[npt], *hsin2psi1pphi23[npt], *hcos2psi1mphi23[npt], *hsin2psi1mphi23[npt]; // 8

  TProfile *hv2EP[npt];	// elliptic flow from EP method
  TProfile *hv22EP;      // integrated elliptic flow from EP method

  // OUTPUT
  // Acceptance correction terms
  double  cos2phi1[ncent], sin2phi1[ncent], cos2phi12[ncent], sin2phi12[ncent],
          cos2phi123[ncent], sin2phi123[ncent];
  double  cos2psi1[ncent][npt], sin2psi1[ncent][npt], cos2psi1phi2[ncent][npt], sin2psi1phi2[ncent][npt],
          cos2psi1pphi23[ncent][npt], sin2psi1pphi23[ncent][npt], cos2psi1mphi23[ncent][npt], sin2psi1mphi23[ncent][npt];

  TGraphErrors *grRefFl[4];     // 4 = {MC, 2QC, 4QC, EP}


  TGraphErrors *grRefFlWOAC[2]; // WOAC - without acceptance correction - 2QC & 4QC

  // Temporary variables
  char hname[800]; // histogram hname
  TProfile *pr; // temporary TProfile for TProfile extracting from root file
  TProfile *prx, *pry, *prxy; // for covariance calculation
  double stats[6]; // stats of TProfile

  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv2MC_%i",icent);
    hv2MC[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv22_%i",icent);
    hv22[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv24_%i",icent);
    hv24[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcov24_%i",icent);
    hcov24[icent] = (TProfile*)inFile->Get(hname);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      sprintf(hname,"hv2MCpt_%i_%i",icent,ipt);
      hv2MCpt[icent][ipt]=(TProfile*)inFile->Get(hname);
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
  hcos2phi1 = (TProfile*)inFile->Get("hcos2phi1");
  hsin2phi1 = (TProfile*)inFile->Get("hsin2phi1");
  hcos2phi12 = (TProfile*)inFile->Get("hcos2phi12");
  hsin2phi12 = (TProfile*)inFile->Get("hsin2phi12");
  hcos2phi123 = (TProfile*)inFile->Get("hcos2phi123");
  hsin2phi123 = (TProfile*)inFile->Get("hsin2phi123");
  hv22EP = (TProfile*)inFile->Get("hv22EP");
  for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
    sprintf(hname,"hPT_%i",ipt);
    hPT[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hv2EP_%i",ipt);
    hv2EP[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hcos2psi1_%i",ipt);
    hcos2psi1[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2psi1_%i",ipt);
    hsin2psi1[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hcos2psi1phi2_%i",ipt);
    hcos2psi1phi2[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2psi1phi2_%i",ipt);
    hsin2psi1phi2[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hcos2psi1pphi23_%i",ipt);
    hcos2psi1pphi23[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2psi1pphi23_%i",ipt);
    hsin2psi1pphi23[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hcos2psi1mphi23_%i",ipt);
    hcos2psi1mphi23[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2psi1mphi23_%i",ipt);
    hsin2psi1mphi23[ipt]=(TProfile*)inFile->Get(hname);
  } // end of loop over pt bin
  //==========================================================================================================================

  // Extract the acceptance correction terms
  for (int icent=0; icent<ncent; icent++){
    cos2phi1[icent] = hcos2phi1 -> GetBinContent(1+icent);
    sin2phi1[icent] = hsin2phi1 -> GetBinContent(1+icent);
    cos2phi12[icent] = hcos2phi12 -> GetBinContent(1+icent);
    sin2phi12[icent] = hsin2phi12 -> GetBinContent(1+icent);
    cos2phi123[icent] = hcos2phi123 -> GetBinContent(1+icent);
    sin2phi123[icent] = hsin2phi123 -> GetBinContent(1+icent);
    for (int ipt=0; ipt<npt; ipt++){
      cos2psi1[icent][ipt] = hcos2psi1[ipt] -> GetBinContent(1+icent);
      sin2psi1[icent][ipt] = hsin2psi1[ipt] -> GetBinContent(1+icent);
      cos2psi1phi2[icent][ipt] = hcos2psi1phi2[ipt] -> GetBinContent(1+icent);
      sin2psi1phi2[icent][ipt] = hsin2psi1phi2[ipt] -> GetBinContent(1+icent);
      cos2psi1pphi23[icent][ipt] = hcos2psi1pphi23[ipt] -> GetBinContent(1+icent);
      sin2psi1pphi23[icent][ipt] = hsin2psi1pphi23[ipt] -> GetBinContent(1+icent);
      cos2psi1mphi23[icent][ipt] = hcos2psi1mphi23[ipt] -> GetBinContent(1+icent);
      sin2psi1mphi23[icent][ipt] = hsin2psi1mphi23[ipt] -> GetBinContent(1+icent);
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
  double v2[4][ncent];
  double ev2[4][ncent];
  double v2AC[4][ncent];

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

    double v22intAC;     // integrated v2 WITH acceptance correction from 2QC
    double v24intAC;     // integrated v2 WITH acceptance correction from 4QC

    double v2EPint;      // integrated v2 WITH acceptance correction from eta sub-event method
    double v2EPintE;     // error of integrated v2 WITH acceptance correction from eta sub-event method
   
    //=============================================

    //v2{MC}
    v2MCint  = hv2MC[icent] -> GetBinContent(1);
    v2MCintE = hv2MC[icent] -> GetBinError(1);
    //=============================================
    // v2{2,QC}
    // estimate of the 2-particle reference flow (C.22)
    cor2 = hv22[icent] -> GetBinContent(1);  // <<2>>
    v22int = Vn2(cor2);
    // acceptance correction
    v22intAC = sqrt(cor2 - (pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2)));

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

    v24intAC = pow( -
        (cor4 - 2.*cor2*cor2
        - 4. * cos2phi1[icent] * cos2phi123[icent]
        + 4. * sin2phi1[icent] * sin2phi123[icent]
        - pow(cos2phi12[icent],2) - pow(sin2phi12[icent],2)
        + 4. * cos2phi12[icent]
        * (pow(cos2phi1[icent],2) - pow(sin2phi1[icent],2))
        + 8. * sin2phi12[icent] * sin2phi1[icent] * cos2phi1[icent]
        + 8. * cor2
        * (pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2))
        - 6. * pow(pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2),2))
        ,0.25);

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
    v2EPint = hv22EP->GetBinContent(icent+1);
    v2EPintE = hv22EP->GetBinError(icent+1);
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

    v2AC[0][icent] = v2MCint;
    v2AC[1][icent] = v22intAC;
    v2AC[2][icent] = v24intAC;
    v2AC[3][icent] = v2EPint;
  } //end of loop over centrality

  grRefFl[0] = new TGraphErrors(ncent,bin_cent,v2AC[0],bin_centE,ev2[0]);
  grRefFl[0]->SetMarkerColor(kRed+1);
  grRefFl[0]->SetMarkerStyle(25);

  grRefFl[1] = new TGraphErrors(ncent,bin_cent,v2AC[1],bin_centE,ev2[1]);
  grRefFl[1]->SetMarkerColor(kGreen+1);
  grRefFl[1]->SetMarkerStyle(20);

  grRefFl[2] = new TGraphErrors(ncent,bin_cent,v2AC[2],bin_centE,ev2[2]);
  grRefFl[2] -> SetMarkerColor(kAzure+2);
  grRefFl[2] -> SetMarkerStyle(22);

  grRefFl[3] = new TGraphErrors(ncent,bin_cent,v2AC[3],bin_centE,ev2[3]);
  grRefFl[3] -> SetMarkerColor(kBlack);
  grRefFl[3] -> SetMarkerStyle(23);  

  for (int i=0;i<4;i++){
    grRefFl[i]->SetMarkerSize(1.3);
    grRefFl[i]->SetDrawOption("P");
  }

  grRefFlWOAC[0] = new TGraphErrors(ncent,bin_cent,v2[1],bin_centE,ev2[1]);
  grRefFlWOAC[0]->SetMarkerColor(kGreen+1);
  grRefFlWOAC[0]->SetMarkerStyle(20+4);
  grRefFlWOAC[0]->SetMarkerSize(1.3);
  grRefFlWOAC[0]->SetDrawOption("P");

  grRefFlWOAC[1] = new TGraphErrors(ncent,bin_cent,v2[2],bin_centE,ev2[2]);
  grRefFlWOAC[1]->SetMarkerColor(kAzure+2);
  grRefFlWOAC[1]->SetMarkerStyle(22+4);
  grRefFlWOAC[1]->SetMarkerSize(1.3);
  grRefFlWOAC[1]->SetDrawOption("P");

  //==========================================================================================================================

  const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};

  TFile *outFile = new TFile("./ROOTFile/TGraphError_refflow_AC.root","recreate");
  outFile -> cd();
  // int mycent = 3;
  for (int i=0; i<4; i++){
    sprintf(hname,"gr_%i",i);
    grRefFl[i] -> SetTitle(ch[i]);
    grRefFl[i] -> Write(hname);
  }
  outFile -> Close();

}