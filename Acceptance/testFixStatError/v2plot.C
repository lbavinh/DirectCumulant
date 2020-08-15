#include "Func_StatErrCalc.C"
#include "DrawTGraph.C"

char tGraphErrors[400]={"TGraphError.root"};

// struct Covariance{
//   Covariance(){
//     mVal = 0;
//     mSumWXY = 0;
//   }
//   Covariance(TProfile *const &hcovXY, TProfile *const &hX, TProfile *const &hY){
//     double statsXY[6], statsX[6], statsY[6];
//     double meanXY, meanX, meanY, sumWX, sumWY;
//     hcovXY -> GetStats(statsXY);
//     hX -> GetStats(statsX);
//     hY -> GetStats(statsY);
    
//     mSumWXY = statsXY[0];
//     sumWX = statsX[0];
//     sumWY = statsY[0];

//     meanXY = hcovXY -> GetBinContent(1);
//     meanX = hX -> GetBinContent(1);
//     meanY = hY -> GetBinContent(1);
//     // mVal = (meanXY-meanX*meanY)/(1-mSumW/sumWX/sumWY); // Cov(x,y) // formula (C.12)
//     mVal = (meanXY-meanX*meanY)/(sumWX*sumWY/mSumWXY-1.); // Cov(x,y)/(sumWX*sumWY/sumWXY)

//   }
//  public:
//   double mVal;
//   double mSumWXY; // sum(wx*wy)
// };

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

void v2plot(){
  // Temporary variables
  char hname[800]; // histogram hname
  char name[800];
  double stats[6]; // stats of TProfile
  char analysis[20]={"acceptance"};
  TFile* inFile = new TFile("sum.root","read");
  TFile *outFile = new TFile(tGraphErrors,"recreate");
  
  static const int ncent = 8; // 0-80%
  static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
  static const double bin_centE[ncent] = {0};
  static const double maxpt = 3.5; // max pt
  static const double minpt = 0.2; // min pt
  static const int npt = 12;        // 0.2 - 3.5 GeV/c
  static const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  
  TCanvas *cTemp = new TCanvas("cTemp","cTemp",200,10,800,450);

  TH1I *hMult = (TH1I*)inFile->Get("hMult");
  hMult -> Draw();
  sprintf(hname,"./Graphics/%s/mult.png",analysis);
  cTemp -> Draw();
  cTemp -> SaveAs(hname);

  TH1F *hEta = (TH1F*)inFile->Get("hEta");
  hEta -> Draw();
  sprintf(hname,"./Graphics/%s/eta.png",analysis);
  cTemp -> SaveAs(hname);  

  TH1F *hPhi = (TH1F*)inFile->Get("hPhi");
  hPhi -> Draw();
  sprintf(hname,"./Graphics/%s/phi.png",analysis);
  cTemp -> SaveAs(hname);

  TH1F *hPhil = (TH1F*)inFile->Get("hPhil");
  hPhil -> Draw();
  sprintf(hname,"./Graphics/%s/phil.png",analysis);
  cTemp -> SaveAs(hname);

  TH1F *hPt = (TH1F*)inFile->Get("hPt");
  hPt -> Draw();
  sprintf(hname,"./Graphics/%s/pt.png",analysis);
  cTemp -> SaveAs(hname);

  TH1F *H_EP = (TH1F*)inFile->Get("H_EP_1_0");
  H_EP -> Draw();
  H_EP -> SetTitle("Raw event plane #Psi_{2,#eta-} distr, cent: 10-20%;#Psi_{2,#eta-}, rad");
  sprintf(hname,"./Graphics/%s/raw.png",analysis);
  cTemp -> SaveAs(hname);

  TH1F *hPsiRecentered = (TH1F*)inFile->Get("hPsiRecentered_1_0");
  hPsiRecentered -> Draw();
  hPsiRecentered -> SetTitle("Recentered event plane #Psi_{2,#eta-} distr, cent: 10-20%;#Psi_{2,#eta-}, rad");
  sprintf(hname,"./Graphics/%s/rec.png",analysis);
  cTemp -> SaveAs(hname);  

  TH1F *hPsiFlattened = (TH1F*)inFile->Get("hPsiFlattened_1_0");
  hPsiFlattened -> Draw();
  hPsiFlattened -> SetTitle("Flattened event plane #Psi_{2,#eta-} distr, cent: 10-20%;#Psi_{2,#eta-}, rad");
  sprintf(hname,"./Graphics/%s/flat.png",analysis);
  cTemp -> SaveAs(hname);  

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

  // TProfile for Covariance calculation according to (C.12), Appendix C
  // in Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider.
  TProfile *hcov24[ncent];                // <2>*<4>
  TProfile *hcov22prime[ncent][npt];      // <2>*<2'>
  TProfile *hcov24prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov42prime[ncent][npt];      // <2>*<4'>
  TProfile *hcov44prime[ncent][npt];      // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

  // non-uniform acceptance correction
  // Reference flow acceptance correction
  // TProfile *hcos2phi1, *hsin2phi1, *hcos2phi12, *hsin2phi12, *hcos2phi123, *hsin2phi123; // 6
  // test fix stat. error
  TProfile *hcos2phi1[ncent], *hsin2phi1[ncent], *hcos2phi12[ncent], *hsin2phi12[ncent], *hcos2phi123[ncent], *hsin2phi123[ncent]; // 6
  // Differential flow acceptance correction
  TProfile *hcos2psi1[ncent][npt], *hsin2psi1[ncent][npt], *hcos2psi1phi2[npt], *hsin2psi1phi2[npt],
           *hcos2psi1pphi23[npt], *hsin2psi1pphi23[npt], *hcos2psi1mphi23[npt], *hsin2psi1mphi23[npt];

  TProfile *hv2EP[npt];	// elliptic flow from EP method
  TProfile *hv22EP;      // integrated elliptic flow from EP method

  // test fix stat. error
  TProfile*hcov4cos2phi1[ncent], *hcov4sin2phi1[ncent], *hcov4cos2phi123[ncent], *hcov4sin2phi123[ncent],
          *hcov4cos2phi12[ncent], *hcov4sin2phi12[ncent],
          *hcov2cos2phi1[ncent], *hcov2sin2phi1[ncent], *hcov2cos2phi123[ncent], *hcov2sin2phi123[ncent],
          *hcov2cos2phi12[ncent], *hcov2sin2phi12[ncent],
          *hcovcos2phi1sin2phi1[ncent], *hcovcos2phi1cos2phi123[ncent], *hcovcos2phi1sin2phi123[ncent],
          *hcovcos2phi1cos2phi12[ncent], *hcovcos2phi1sin2phi12[ncent],
          *hcovsin2phi1cos2phi123[ncent], *hcovsin2phi1sin2phi123[ncent],
          *hcovsin2phi1cos2phi12[ncent], *hcovsin2phi1sin2phi12[ncent],
          *hcovcos2phi123sin2phi123[ncent], *hcovcos2phi123cos2phi12[ncent], *hcovcos2phi123sin2phi12[ncent],
          *hcovsin2phi123cos2phi12[ncent], *hcovsin2phi123sin2phi12[ncent], *hcovcos2phi12sin2phi12[ncent];

  TProfile *hcov[ncent][npt][6][6];

  // OUTPUT    

  // Acceptance correction terms
  // double  cos2phi1[ncent], sin2phi1[ncent], cos2phi12[ncent], sin2phi12[ncent],
  //         cos2phi123[ncent], sin2phi123[ncent];
  // double  cos2psi1[ncent][npt], sin2psi1[ncent][npt];
  double  cos2psi1phi2[ncent][npt], sin2psi1phi2[ncent][npt],
          cos2psi1pphi23[ncent][npt], sin2psi1pphi23[ncent][npt], cos2psi1mphi23[ncent][npt], sin2psi1mphi23[ncent][npt];

  TGraphErrors *grDifFl[4][ncent], *grRefFl[ncent];     // 4 = {MC, 2QC, 4QC, EP}
  TGraphErrors *grRefFlCent[4];                         // v2(cent)
  TGraph *grshade[ncent];
  TMultiGraph *mgDifFl[ncent];

  TGraphErrors *grDifFlWOAC[2][ncent], *grRefFlWOAC[ncent]; // WOAC - without acceptance correction - 2QC & 4QC
  TMultiGraph *mgDifFlWOAC[ncent];



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

    // test fix stat. error
    sprintf(hname,"hcos2phi1_%i",icent);
    hcos2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2phi1_%i",icent);
    hsin2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcos2phi12_%i",icent);
    hcos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2phi12_%i",icent);
    hsin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcos2phi123_%i",icent);
    hcos2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hsin2phi123_%i",icent);
    hsin2phi123[icent] = (TProfile*)inFile->Get(hname);

    // test fix stat. error
    sprintf(name, "hcov4cos2phi1_%i", icent);
    hcov4cos2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov4sin2phi1_%i", icent);
    hcov4sin2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov4cos2phi123_%i", icent);
    hcov4cos2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov4sin2phi123_%i", icent);
    hcov4sin2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov4cos2phi12_%i", icent);
    hcov4cos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov4sin2phi12_%i", icent);
    hcov4sin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov2cos2phi1_%i", icent);
    hcov2cos2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov2sin2phi1_%i", icent);
    hcov2sin2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov2cos2phi123_%i", icent);
    hcov2cos2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov2sin2phi123_%i", icent);
    hcov2sin2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov2cos2phi12_%i", icent);
    hcov2cos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcov2sin2phi12_%i", icent);
    hcov2sin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi1sin2phi1_%i", icent);
    hcovcos2phi1sin2phi1[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi1cos2phi123_%i", icent);
    hcovcos2phi1cos2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi1sin2phi123_%i", icent);
    hcovcos2phi1sin2phi123[icent] = (TProfile*)inFile->Get(hname);  
    sprintf(name, "hcovcos2phi1cos2phi12_%i", icent);
    hcovcos2phi1cos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi1sin2phi12_%i", icent);
    hcovcos2phi1sin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovsin2phi1cos2phi123_%i", icent);
    hcovsin2phi1cos2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovsin2phi1sin2phi123_%i", icent);
    hcovsin2phi1sin2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovsin2phi1cos2phi12_%i", icent);
    hcovsin2phi1cos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovsin2phi1sin2phi12_%i", icent);
    hcovsin2phi1sin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi123sin2phi123_%i", icent);
    hcovcos2phi123sin2phi123[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi123cos2phi12_%i", icent);
    hcovcos2phi123cos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi123sin2phi12_%i", icent);
    hcovcos2phi123sin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovsin2phi123cos2phi12_%i", icent);
    hcovsin2phi123cos2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovsin2phi123sin2phi12_%i", icent);
    hcovsin2phi123sin2phi12[icent] = (TProfile*)inFile->Get(hname);
    sprintf(name, "hcovcos2phi12sin2phi12_%i", icent);
    hcovcos2phi12sin2phi12[icent] = (TProfile*)inFile->Get(hname);




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

      // test fix stat. error
      sprintf(hname,"hcos2psi1_%i_%i",icent,ipt);
      hcos2psi1[icent][ipt]=(TProfile*)inFile->Get(hname);
      sprintf(hname,"hsin2psi1_%i_%i",icent,ipt);
      hsin2psi1[icent][ipt]=(TProfile*)inFile->Get(hname);

      for (int iterm=0;iterm<6;iterm++){
        for (int jterm=0;jterm<6;jterm++){
          sprintf(hname, "hcov_%i_%i_%i_%i", icent, ipt, iterm, jterm);
          hcov[icent][ipt][iterm][jterm] = (TProfile*)inFile->Get(hname);   
        }
      }




    } // end of loop over pt bin
  } // end of loop over centrality classes

  hv22EP = (TProfile*)inFile->Get("hv22EP");
  for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
    sprintf(hname,"hPT_%i",ipt);
    hPT[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hv2EP_%i",ipt);
    hv2EP[ipt]=(TProfile*)inFile->Get(hname);
    // sprintf(hname,"hcos2psi1_%i",ipt);
    // hcos2psi1[ipt]=(TProfile*)inFile->Get(hname);
    // sprintf(hname,"hsin2psi1_%i",ipt);
    // hsin2psi1[ipt]=(TProfile*)inFile->Get(hname);
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
    // cos2phi1[icent] = hcos2phi1[icent] -> GetBinContent(1);
    // sin2phi1[icent] = hsin2phi1[icent] -> GetBinContent(1);
    // cos2phi12[icent] = hcos2phi12[icent] -> GetBinContent(1);
    // sin2phi12[icent] = hsin2phi12[icent] -> GetBinContent(1);
    // cos2phi123[icent] = hcos2phi123[icent] -> GetBinContent(1);
    // sin2phi123[icent] = hsin2phi123[icent] -> GetBinContent(1);
    for (int ipt=0; ipt<npt; ipt++){
      // cos2psi1[icent][ipt] = hcos2psi1[icent][ipt] -> GetBinContent(1);
      // sin2psi1[icent][ipt] = hsin2psi1[icent][ipt] -> GetBinContent(1);
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
  double v2[ncent][4];
  double ev2[ncent][4];
  double x[4]={0.5,1.5,2.5,3.5};
  double ex[4]={0};

  double v2AC[ncent][4];
  double v2EAC[ncent][4];

  double v2centAC[4][ncent];
  double v2centEAC[4][ncent];

  ofstream ofile2("v2int.txt");

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

    // test fix stat. error
    double v22intEAC;     // error of integrated v2 WITH acceptance correction from 2QC
    double v24intEAC;     // error of integrated v2 WITH acceptance correction from 4QC


    //=============================================

    //v2{MC}
    v2MCint  = hv2MC[icent] -> GetBinContent(1);
    v2MCintE = hv2MC[icent] -> GetBinError(1);
    //=============================================
    // v2{2,QC}
    // estimate of the 2-particle reference flow (C.22)
    // cor2 = hv22[icent] -> GetBinContent(1);  // <<2>>
    // v22int = Vn2(cor2);
    // acceptance correction



    // v22intAC = sqrt(cor2 - (pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2)));
    
    // statistical error of the 2-particle reference flow estimate (C.24)
    // cor2E = sx(hv22[icent]);
    // hv22[icent] -> GetStats(stats);
    // sumwcor2 = stats[0];
    // sumw2cor2 = stats[1];
    // v22intE = Evn2(cor2,cor2E,sumwcor2,sumw2cor2);

    // test fix stat. error

    term cor22, cosnphi1, sinnphi1;
    cor22 = term(hv22[icent]);
    cosnphi1 = term(hcos2phi1[icent]);
    sinnphi1 = term(hsin2phi1[icent]);
    cor2 = cor22.mVal;
    v22int = sqrt(cor2);
    v22intAC = sqrt(cor22.mVal - pow(cosnphi1.mVal,2) - pow(sinnphi1.mVal,2) );
    
    v22intE  = sqrt(1./(4.*cor22.mVal)*cor22.mMSE);

    double cor2cosnphi1, cor2sinnphi1, cosnphi1sinnphi1;
    cor2cosnphi1 = Covariance(hcov2cos2phi1[icent],hv22[icent],hcos2phi1[icent]);
    cor2sinnphi1 = Covariance(hcov2sin2phi1[icent],hv22[icent],hsin2phi1[icent]);
    cosnphi1sinnphi1 = Covariance(hcovcos2phi1sin2phi1[icent],hsin2phi1[icent],hcos2phi1[icent]);

    v22intEAC = sqrt(
      1./pow(2*v22intAC,2)
      *( cor22.mMSE
      + pow(2*cosnphi1.mVal,2)*cosnphi1.mMSE
      + pow(2*sinnphi1.mVal,2)*sinnphi1.mMSE
      - 4*cosnphi1.mVal*cor2cosnphi1
      - 4*sinnphi1.mVal*cor2sinnphi1
      + 8*cosnphi1.mVal*sinnphi1.mVal*cosnphi1sinnphi1
       )
    );

    //=============================================
    // v2{4,QC}
    // estimate of the 4-particle reference flow (C.27)
    // cor4 = hv24[icent]->GetBinContent(1);  // <<4>>
    // v24int = Vn4(cor2,cor4);

    // v24intAC = pow( -
    //     (cor4 - 2.*cor2*cor2
    //     - 4. * cosnphi1.mVal * cos2phi123[icent]
    //     + 4. * sinnphi1.mVal * sin2phi123[icent]
    //     - pow(cos2phi12[icent],2) - pow(sin2phi12[icent],2)
    //     + 4. * cos2phi12[icent]
    //     * (pow(cos2phi1[icent],2) - pow(sin2phi1[icent],2))
    //     + 8. * sin2phi12[icent] * sin2phi1[icent] * cos2phi1[icent]
    //     + 8. * cor2
    //     * (pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2))
    //     - 6. * pow(pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2),2))
    //     ,0.25);

    // statistical error of the 4-particle reference flow estimate (C.28)
    // cor4E = sx(hv24[icent]);
    // hv24[icent] -> GetStats(stats);
    // sumwcor4 = stats[0];
    // sumw2cor4 = stats[1];
    // calculate Covariance of <2> and <4>
    // cov24 = Cov(hcov24[icent],hv22[icent],hv24[icent]);
    // sumwcor24 = Sumwxwy(hcov24[icent]);
    // v24intE = Evn4(cor2,cor2E,sumwcor2,sumw2cor2,
    //               cor4,cor4E,sumwcor4,sumw2cor4,
    //               cov24,sumwcor24);

    // test fix stat. error

    term cor24,cos2phi1,sin2phi1,cos2phi123,sin2phi123,cos2phi12,sin2phi12;
    cor24 = term(hv24[icent]);
    cos2phi1 = term(hcos2phi1[icent]);
    sin2phi1 = term(hsin2phi1[icent]);
    cos2phi123 = term(hcos2phi123[icent]);
    sin2phi123 = term(hsin2phi123[icent]);
    cos2phi12 = term(hcos2phi12[icent]);
    sin2phi12 = term(hsin2phi12[icent]);

    double cov42, cov4cos2phi1, cov4sin2phi1, cov4cos2phi123, cov4sin2phi123, cov4cos2phi12, cov4sin2phi12;
    double cov2cos2phi1, cov2sin2phi1, cov2cos2phi123, cov2sin2phi123, cov2cos2phi12, cov2sin2phi12;
    double covcos2phi1sin2phi1, covcos2phi1cos2phi123, covcos2phi1sin2phi123, covcos2phi1cos2phi12, covcos2phi1sin2phi12;
    double covsin2phi1cos2phi123, covsin2phi1sin2phi123, covsin2phi1cos2phi12, covsin2phi1sin2phi12;
    double covcos2phi123sin2phi123, covcos2phi123cos2phi12, covcos2phi123sin2phi12;
    double covsin2phi123cos2phi12, covsin2phi123sin2phi12;
    double covcos2phi12sin2phi12;

    cov42 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    cov4cos2phi1 = Covariance(hcov4cos2phi1[icent],hv24[icent],hcos2phi1[icent]);
    cov4sin2phi1 = Covariance(hcov4sin2phi1[icent],hv24[icent],hsin2phi1[icent]);
    cov4cos2phi123 = Covariance(hcov4cos2phi123[icent],hv24[icent],hcos2phi123[icent]);
    cov4sin2phi123 = Covariance(hcov4sin2phi123[icent],hv24[icent],hsin2phi123[icent]);
    cov4cos2phi12 = Covariance(hcov4cos2phi12[icent],hv24[icent],hcos2phi12[icent]);
    cov4sin2phi12 = Covariance(hcov4sin2phi12[icent],hv24[icent],hsin2phi12[icent]);

    cov2cos2phi1 = Covariance(hcov2cos2phi1[icent],hv22[icent],hcos2phi1[icent]);
    cov2sin2phi1 = Covariance(hcov2sin2phi1[icent],hv22[icent],hsin2phi1[icent]);
    cov2cos2phi123 = Covariance(hcov2cos2phi123[icent],hv22[icent],hcos2phi123[icent]);
    cov2sin2phi123 = Covariance(hcov2sin2phi123[icent],hv22[icent],hsin2phi123[icent]);
    cov2cos2phi12 = Covariance(hcov2cos2phi12[icent],hv22[icent],hcos2phi12[icent]);
    cov2sin2phi12 = Covariance(hcov2sin2phi12[icent],hv22[icent],hsin2phi12[icent]);

    covcos2phi1sin2phi1 = Covariance(hcovcos2phi1sin2phi1[icent],hcos2phi1[icent],hsin2phi1[icent]);
    covcos2phi1cos2phi123 = Covariance(hcovcos2phi1cos2phi123[icent],hcos2phi1[icent],hcos2phi123[icent]);
    covcos2phi1sin2phi123 = Covariance(hcovcos2phi1sin2phi123[icent],hcos2phi1[icent],hsin2phi123[icent]);
    covcos2phi1cos2phi12 = Covariance(hcovcos2phi1cos2phi12[icent],hcos2phi1[icent],hcos2phi12[icent]);
    covcos2phi1sin2phi12 = Covariance(hcovcos2phi1sin2phi12[icent],hcos2phi1[icent],hsin2phi12[icent]);

    covsin2phi1cos2phi123 = Covariance(hcovsin2phi1cos2phi123[icent],hsin2phi1[icent],hcos2phi123[icent]);
    covsin2phi1sin2phi123 = Covariance(hcovsin2phi1sin2phi123[icent],hsin2phi1[icent],hsin2phi123[icent]);
    covsin2phi1cos2phi12 = Covariance(hcovsin2phi1cos2phi12[icent],hsin2phi1[icent],hcos2phi12[icent]);
    covsin2phi1sin2phi12 = Covariance(hcovsin2phi1sin2phi12[icent],hsin2phi1[icent],hsin2phi12[icent]);

    covcos2phi123sin2phi123 = Covariance(hcovcos2phi123sin2phi123[icent],hcos2phi123[icent],hsin2phi123[icent]);
    covcos2phi123cos2phi12 = Covariance(hcovcos2phi123cos2phi12[icent],hcos2phi123[icent],hcos2phi12[icent]);
    covcos2phi123sin2phi12 = Covariance(hcovcos2phi123sin2phi12[icent],hcos2phi123[icent],hsin2phi12[icent]);

    covsin2phi123cos2phi12 = Covariance(hcovsin2phi123cos2phi12[icent],hsin2phi123[icent],hcos2phi12[icent]);
    covsin2phi123sin2phi12 = Covariance(hcovsin2phi123sin2phi12[icent],hsin2phi123[icent],hsin2phi12[icent]);

    covcos2phi12sin2phi12 = Covariance(hcovcos2phi12sin2phi12[icent],hcos2phi12[icent],hsin2phi12[icent]);
    // without AC
    cor4 = cor24.mVal;
    v24int = pow(2*pow(cor2,2)-cor4,0.25);
    v24intE = sqrt(
      1./pow(v24int,6)*(
        cor22.mVal*cor22.mVal*cor22.mMSE
      + 1./16*cor24.mMSE
      - 0.5*cor22.mVal*cov42
      )
    );
    // end of without AC
    v24intAC = pow( -
        (cor4 - 2.*cor2*cor2
        - 4. * cosnphi1.mVal * cos2phi123.mVal
        + 4. * sinnphi1.mVal * sin2phi123.mVal
        - pow(cos2phi12.mVal,2) - pow(sin2phi12.mVal,2)
        + 4. * cos2phi12.mVal
        * (pow(cos2phi1.mVal,2) - pow(sin2phi1.mVal,2))
        + 8. * sin2phi12.mVal * sin2phi1.mVal * cos2phi1.mVal
        + 8. * cor2
        * (pow(cos2phi1.mVal,2) + pow(sin2phi1.mVal,2))
        - 6. * pow(pow(cos2phi1.mVal,2) + pow(sin2phi1.mVal,2),2))
        ,0.25);

    double c = 4*cor2-8*(pow(cos2phi1.mVal,2)+pow(sin2phi1.mVal,2));
    double a = 4*cos2phi123.mVal-8*cos2phi12.mVal*cos2phi1.mVal
             - 8*sin2phi12.mVal*sin2phi1.mVal-16*cor2*cos2phi1.mVal+24*(pow(cos2phi1.mVal,2)+pow(sin2phi1.mVal,2))*cos2phi1.mVal;
    double b =-4*sin2phi123.mVal+8*cos2phi12.mVal*sin2phi1.mVal
             - 8*sin2phi12.mVal*cos2phi1.mVal-16*cor2*sin2phi1.mVal+24*(pow(cos2phi1.mVal,2)+pow(sin2phi1.mVal,2))*sin2phi1.mVal;
    double d = 4*cos2phi1.mVal;
    double e =-4*sin2phi1.mVal;
    double f = 2*cos2phi12.mVal-4*(pow(cos2phi1.mVal,2)-pow(sin2phi1.mVal,2));
    double g = 2*sin2phi12.mVal-8*sin2phi1.mVal*cos2phi1.mVal;
    v24intEAC = (1./(16.*pow(v24intAC,6)))
              *( cor24.mMSE
               + c*c*cor22.mMSE
               + a*a*cos2phi1.mMSE
               + b*b*sin2phi1.mMSE
               + d*d*cos2phi123.mMSE
               + e*e*sin2phi123.mMSE
               + f*f*cos2phi12.mMSE
               + g*g*sin2phi12.mMSE

               - 2*c*cov24
               - 2*a*cov4cos2phi1
               - 2*b*cov4sin2phi1
               - 2*d*cov4cos2phi123
               - 2*e*cov4sin2phi123
               - 2*f*cov4cos2phi12
               - 2*g*cov4sin2phi12

               + 2*c*a*cov2cos2phi1
               + 2*c*b*cov2sin2phi1
               + 2*c*d*cov2cos2phi123
               + 2*c*e*cov2sin2phi123
               + 2*c*f*cov2cos2phi12
               + 2*c*g*cov2sin2phi12

               + 2*a*b*covcos2phi1sin2phi1
               + 2*a*e*covcos2phi1sin2phi123
               + 2*a*g*covcos2phi1sin2phi12
               + 2*a*d*covcos2phi1cos2phi123
               + 2*a*f*covcos2phi1cos2phi12

               + 2*b*d*covsin2phi1cos2phi123
               + 2*b*e*covsin2phi1sin2phi123
               + 2*b*f*covsin2phi1cos2phi12
               + 2*b*g*covsin2phi1sin2phi12

               + 2*d*e*covcos2phi123sin2phi123
               + 2*d*f*covcos2phi123cos2phi12
               + 2*d*g*covcos2phi123sin2phi12

               + 2*e*f*covsin2phi123cos2phi12
               + 2*e*g*covsin2phi123sin2phi12

               + 2*f*g*covcos2phi12sin2phi12
              );
    v24intEAC = sqrt(v24intEAC);          


    
    ofile2 << icent*10<<"-"<< (icent+1)*10<<" "<< v22intAC <<" "<< v22intEAC << " "<< v24intAC <<" "<< v24intEAC << endl;

    //=============================================

    // v2{#eta sub-event}
    v2EPint = hv22EP->GetBinContent(icent+1);
    v2EPintE = hv22EP->GetBinError(icent+1);
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

    v2AC[icent][0] = v2MCint;
    v2AC[icent][1] = v22intAC;
    v2AC[icent][2] = v24intAC;
    v2AC[icent][3] = v2EPint;

    v2EAC[icent][0] = v2MCintE;
    v2EAC[icent][1] = v22intEAC;
    v2EAC[icent][2] = v24intEAC;
    v2EAC[icent][3] = v2EPintE;


    v2centAC[0][icent] = v2MCint;
    v2centAC[1][icent] = v22intAC;
    v2centAC[2][icent] = v24intAC;
    v2centAC[3][icent] = v2EPint;  

    v2centEAC[0][icent] = v2MCintE;
    v2centEAC[1][icent] = v22intEAC;
    v2centEAC[2][icent] = v24intE;
    v2centEAC[3][icent] = v2EPintE;  

    // TGraphErrors for compare 4 method
    grRefFl[icent] = new TGraphErrors(4,x,v2AC[icent],ex,v2EAC[icent]);
    grRefFl[icent]->SetMarkerColor(kRed);
    grRefFl[icent]->SetMarkerStyle(20);
    grRefFl[icent]->SetMarkerSize(1.3);
    grRefFl[icent]->SetDrawOption("P");

    grRefFlWOAC[icent] = new TGraphErrors(4,x,v2[icent],ex,ev2[icent]);
    grRefFlWOAC[icent]->SetMarkerColor(kRed);
    grRefFlWOAC[icent]->SetMarkerStyle(24);
    grRefFlWOAC[icent]->SetMarkerSize(1.3);
    grRefFlWOAC[icent]->SetDrawOption("P");






    // Set a shade between error of v2MC
    grshade[icent] = new TGraph(10);
    for (Int_t i=0; i<5; i++) {
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
  
    // double cor2Red[npt];         // Differential 2nd order cumulant d_{2}{2} = <<2'>>
    // double cor2RedE[npt];        // Error of <<2'>>
    double v22dif[npt];      // Differential elliptic flow v'_{2}{2} extracted from 2nd order cumulants
                            // v'_{2}{2} = d_{2}{2} / sqrt( c_{2}{2} )
    double v22difE[npt];     // Error of v'_{2}{2}
    
    // double cor4Red[npt];    // Reduced average all-event 4-particle correlation <<4'>>
    // double cor4RedE[npt];   // Error of <<4'>>
    double v24dif[npt];      // Differential elliptic flow v'_{2}{4} extracted from 4th order cumulants
                            // v'_{2}{4} = -d_{2}{4} / pow( -c_{2}{4} , 3/4 )
    double v24difE[npt];     // Error of v'_{2}{4}

    // double sumwcor22prime[npt];        // sum(w(<2>)*w(<2'>))
    // double cov22prime[npt];            // Cov(<2>,<2'>)
    // double sumwcor24prime[npt];        // sum(w(<2>)*w(<4'>))
    // double cov24prime[npt];            // Cov(<2>,<4'>)
    // double sumwcor42prime[npt];        // sum(w(<4>)*w(<2'>))
    // double cov42prime[npt];            // Cov(<4>,<2'>)
    // double sumwcor44prime[npt];        // sum(w(<4>)*w(<4'>))
    // double cov44prime[npt];            // Cov(<4>,<4'>)
    // double sumwcor2prime4prime[npt];   // sum(w(<2'>)*w(<4'>))
    // double cov2prime4prime[npt];       // Cov(<2'>,<4'>)

    // double sumw2cor2red[npt]; // sumw2 of <2'>
    // double sumwcor2red[npt];  // sumw of <2'>    
    // double sumw2cor4red[npt]; // sumw2 of <4'>
    // double sumwcor4red[npt];  // sumw of <4'>

    double v22difAC[npt], v24difAC[npt];
    double v22difEAC[npt]={0}, v24difEAC[npt]={0};

    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      
      // Differential flow v2MC
      v2MCpt[ipt]  = hv2MCpt[icent][ipt] -> GetBinContent(1);
      ev2MCpt[ipt] = hv2MCpt[icent][ipt] -> GetBinError(1);

      // 2-particle correlations
      // // estimate of the 2-particle differential flow (C.41)
      // cor2Red[ipt] = hv22pt[icent][ipt]->GetBinContent(1);
      // v22dif[ipt] = Vn2Dif(cor2Red[ipt],cor2);
      // // acceptance correction
      // v22difAC[ipt] = (cor2Red[ipt] - cos2psi1[icent][ipt] * cos2phi1[icent] - sin2psi1[icent][ipt] * sin2phi1[icent]) / v22intAC;

      term cor2Red, cos2psi1, sin2psi1;
      cor2Red = term(hv22pt[icent][ipt]);
      cos2psi1 = term(hcos2psi1[icent][ipt]);
      sin2psi1 = term(hsin2psi1[icent][ipt]);

      double cov[6][6]={{0}};
      for (int iterm=0;iterm<6;iterm++){
        for (int jterm=iterm;jterm<6;jterm++){
          if (iterm==jterm) continue;
          cov[iterm][jterm] = Covariance(hcov[icent][ipt][iterm][jterm],hterm[icent][ipt][iterm],hterm[jterm]);
        }  
      }

      v22dif[ipt] = cor2Red.mVal/v22int;
      v22difAC[ipt] = (cor2Red.mVal - cos2psi1.mVal * cos2phi1.mVal - sin2psi1.mVal * sin2phi1.mVal) / v22intAC;
      v22difE[ipt] = sqrt(0.25*pow(cor2,-3.)*(cor2Red.mVal*cor2Red.mVal*cor22.mMSE
          + 4.*cor2*cor2*cor2Red.mMSE - 4.*cor2*cor2Red.mVal
          * cov[0][1]));
      // partial derivate terms
      double partDer[6];

      double h = v22intAC;
      double i = cor2Red.mVal - cos2psi1.mVal * cos2phi1.mVal - sin2psi1.mVal * sin2phi1.mVal;
      partDer[0] = 1./h;
      partDer[1] = -0.5*i*pow(h,-3);
      partDer[2] = -cos2phi1.mVal/h;
      partDer[3] = -sin2phi.mVal/h;
      partDer[4] = (-cos2psi1.mVal*h+i/h*cos2phi1.mVal)/(h*h);
      partDer[5] = (-sin2psi1.mVal*h+i/h*sin2phi1.mVal)/(h*h);

      // double j = 1./h;
      // double k = -0.5*i*pow(h,-3);
      // double l = -cos2phi1.mVal/h;
      // double m = -sin2phi.mVal/h;
      // double n = (-cos2psi1.mVal*h+i/h*cos2phi1.mVal)/(h*h);
      // double o = (-sin2psi1.mVal*h+i/h*sin2phi1.mVal)/(h*h);
      term termV22Dif[6];
      termV22Dif[0] = cor2Red;
      termV22Dif[1] = cor22;
      termV22Dif[2] = cos2psi1;
      termV22Dif[3] = sin2psi1;
      termV22Dif[4] = cos2phi1;
      termV22Dif[5] = sin2phi1;

      for (int iterm=0;iterm<6;iterm++){
        v22difEAC[ipt] += pow(partDer[iterm],2)*termV22Dif[iterm].mMSE;
      }
      for (int iterm=0;iterm<6;iterm++){
        for (int jterm=iterm;jterm<6;jterm++){
          if (iterm==jterm) continue;
          v22difEAC[ipt] += 2*partDer[iterm]*partDer[jterm]*cov[iterm][jterm];
        }
      }
      v22difEAC[ipt] = sqrt(v22difEAC[ipt]);

      // statistical error of the 2-particle differential flow estimate (C.42)
      // cor2RedE[ipt] = sx(hv22pt[icent][ipt]);
      // hv22pt[icent][ipt] -> GetStats(stats);
      // sumwcor2red[ipt] = stats[0];
      // sumw2cor2red[ipt] = stats[1];

      // calculate Covariance of <2> and <2'>
      // cov22prime[ipt] = Cov(hcov22prime[icent][ipt],hv22[icent],hv22pt[icent][ipt]);
      // sumwcor22prime[ipt] = Sumwxwy(hcov22prime[icent][ipt]);
      // v22difE[ipt] = Evn2dif(cor2, cor2E, sumwcor2, sumw2cor2,
      //                        cor2Red[ipt], cor2RedE[ipt], sumwcor2red[ipt],sumw2cor2red[ipt],
      //                        cov22prime[ipt], sumwcor22prime[ipt]);

      // 4-particle correlations
      // estimate of the 4-particle differential flow (C.45)
      cor4Red[ipt] = hv24pt[icent][ipt]->GetBinContent(1);
      v24dif[ipt] = Vn4Dif(cor2Red[ipt], cor2, cor4Red[ipt], cor4);

      // acceptance correction

      v24difAC[ipt] =
            - (cor4Red[ipt] - 2.*cor2Red[ipt]*cor2
            - cos2psi1[icent][ipt] * cos2phi123[icent]
            + sin2psi1[icent][ipt] * sin2phi123[icent]
            - cos2phi1[icent] * cos2psi1mphi23[icent][ipt]
            + sin2phi1[icent] * sin2psi1mphi23[icent][ipt]
            - 2. * cos2phi1[icent] * cos2psi1pphi23[icent][ipt]
            - 2. * sin2phi1[icent] * sin2psi1pphi23[icent][ipt]
            - cos2psi1phi2[icent][ipt] * cos2phi12[icent]
            - sin2psi1phi2[icent][ipt] * sin2phi12[icent]
            + 2. * cos2phi12[icent]
            * (cos2psi1[icent][ipt] * cos2phi1[icent] - sin2psi1[icent][ipt] * sin2phi1[icent])
            + 2. * sin2phi12[icent]
            * (cos2psi1[icent][ipt] * sin2phi1[icent] + sin2psi1[icent][ipt] * cos2phi1[icent])
            + 4. * cor2
            * (cos2psi1[icent][ipt] * cos2phi1[icent] + sin2psi1[icent][ipt] * sin2phi1[icent])
            + 2. * cos2psi1phi2[icent][ipt]
            * (pow(cos2phi1[icent],2) - pow(sin2phi1[icent],2))
            + 4. * sin2psi1phi2[icent][ipt] * cos2phi1[icent] * sin2phi1[icent]
            + 4. * cor2Red[ipt] * (pow(cos2phi1[icent],2) + pow(sin2phi1[icent],2))
            - 6. * (pow(cos2phi1[icent],2) - pow(sin2phi1[icent],2))
            * (cos2psi1[icent][ipt] * cos2phi1[icent] - sin2psi1[icent][ipt] * sin2phi1[icent])
            - 12. * cos2phi1[icent] * sin2phi1[icent]
            * (sin2psi1[icent][ipt] * cos2phi1[icent] + cos2psi1[icent][ipt] * sin2phi1[icent]))
            * pow(v24intAC,-3.);

      // statistical error of the 4-particle differential flow estimate (C.46)
      cor4RedE[ipt] = sx(hv24pt[icent][ipt]);
      hv24pt[icent][ipt] -> GetStats(stats);
      sumwcor4red[ipt] = stats[0];
      sumw2cor4red[ipt] = stats[1];

      // calculate Covariance of <2> and <4'>
      cov24prime[ipt] = Cov(hcov24prime[icent][ipt],hv22[icent],hv24pt[icent][ipt]);
      sumwcor24prime[ipt] = Sumwxwy(hcov24prime[icent][ipt]);

      // calculate Covariance of <4> and <2'>
      cov42prime[ipt] = Cov(hcov42prime[icent][ipt],hv24[icent],hv22pt[icent][ipt]);
      sumwcor42prime[ipt] = Sumwxwy(hcov42prime[icent][ipt]);

      // calculate Covariance of <4> and <4'>
      cov44prime[ipt] = Cov(hcov44prime[icent][ipt],hv24[icent],hv24pt[icent][ipt]);
      sumwcor44prime[ipt] = Sumwxwy(hcov44prime[icent][ipt]);

      // calculate Covariance of <2'> and <4'>
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
    grDifFl[0][icent] = new TGraphErrors(npt,pt[icent],v2MCpt,ept[icent],ev2MCpt);
    grDifFl[0][icent] -> SetMarkerColor(kRed+1);
    grDifFl[0][icent] -> SetMarkerStyle(25);

    grDifFl[1][icent] = new TGraphErrors(npt,pt[icent],v22difAC,ept[icent],v22difE);
    grDifFl[1][icent] -> SetMarkerColor(kGreen+1);
    grDifFl[1][icent] -> SetMarkerStyle(20);

    grDifFl[2][icent] = new TGraphErrors(npt,pt[icent],v24difAC,ept[icent],v24difE);
    grDifFl[2][icent] -> SetMarkerColor(kAzure+2);
    grDifFl[2][icent] -> SetMarkerStyle(22);

    mgDifFl[icent] = new TMultiGraph();

    // Without acceptance correction
    grDifFlWOAC[0][icent] = new TGraphErrors(npt,pt[icent],v22dif,ept[icent],v22difE);
    grDifFlWOAC[0][icent] -> SetMarkerColor(kGreen+1);
    grDifFlWOAC[0][icent] -> SetMarkerStyle(20+4);

    grDifFlWOAC[1][icent] = new TGraphErrors(npt,pt[icent],v24dif,ept[icent],v24difE);
    grDifFlWOAC[1][icent] -> SetMarkerColor(kAzure+2);
    grDifFlWOAC[1][icent] -> SetMarkerStyle(22+4);
    mgDifFlWOAC[icent] = new TMultiGraph();

    for (int i=0; i<3; i++){
      grDifFl[i][icent] -> SetMarkerSize(1.3);
      grDifFl[i][icent] -> SetDrawOption("P");
      mgDifFl[icent] -> Add(grDifFl[i][icent]);
    }
    for (int i=0; i<2; i++){
      grDifFlWOAC[i][icent] -> SetMarkerSize(1.3);
      grDifFlWOAC[i][icent] -> SetDrawOption("P");
      mgDifFlWOAC[icent] -> Add(grDifFlWOAC[i][icent]);
    }    
  
  } // end of loop over centrality classes

  //==========================================================================================================================
  // // Elliptic flow from eta sub-event method
  // for (int icent=0; icent<ncent; icent++){
  //   double v2EP[npt]={0}, ev2EP[npt]={0};
  //   for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
  //     v2EP[ipt] = hv2EP[ipt]->GetBinContent(icent+1);
  //     ev2EP[ipt] = hv2EP[ipt]->GetBinError(icent+1);
  //   }
  //   // Event plane differential flow
  //   grDifFl[3][icent] = new TGraphErrors(npt,pt[icent],v2EP,ept[icent],ev2EP);
  //   grDifFl[3][icent] -> SetMarkerColor(kBlack);
  //   grDifFl[3][icent] -> SetMarkerStyle(23);
  //   grDifFl[3][icent] -> SetMarkerSize(1.3);
  //   grDifFl[3][icent] -> SetDrawOption("P");
  //   mgDifFl[icent] -> Add(grDifFl[3][icent]);
  // }

  //==========================================================================================================================
  // TGraphErrors of reference flow with respect to centrality
  grRefFlCent[0] = new TGraphErrors(ncent,bin_cent,v2centAC[0],bin_centE,v2centEAC[0]);
  grRefFlCent[0]->SetMarkerColor(kRed+1);
  grRefFlCent[0]->SetMarkerStyle(25);

  grRefFlCent[1] = new TGraphErrors(ncent,bin_cent,v2centAC[1],bin_centE,v2centEAC[1]);
  grRefFlCent[1]->SetMarkerColor(kGreen+1);
  grRefFlCent[1]->SetMarkerStyle(20);

  grRefFlCent[2] = new TGraphErrors(ncent,bin_cent,v2centAC[2],bin_centE,v2centEAC[2]);
  grRefFlCent[2] -> SetMarkerColor(kAzure+2);
  grRefFlCent[2] -> SetMarkerStyle(22);

  grRefFlCent[3] = new TGraphErrors(ncent,bin_cent,v2centAC[3],bin_centE,v2centEAC[3]);
  grRefFlCent[3] -> SetMarkerColor(kBlack);
  grRefFlCent[3] -> SetMarkerStyle(23);

  for (int i=0;i<4;i++){
    grRefFl[i]->SetMarkerSize(1.6);
    grRefFl[i]->SetDrawOption("P");
  }
  const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};
  /*  
  //==========================================================================================================================
  
  TLegend *leg[3];
  leg[0] = new TLegend(.11,.95,.42,.78); // legend for dif. flow plotting
  leg[0] -> AddEntry(grDifFl[0][0],"v_{2}{MC}","p");
  leg[0] -> AddEntry(grDifFl[1][0],"v_{2}{2,QC}","p");
  leg[0] -> AddEntry(grDifFl[2][0],"v_{2}{4,QC}","p");
  leg[0] -> AddEntry(grDifFl[3][0],"v_{2}{#eta sub-event}","p");
  leg[0] -> AddEntry(grDifFlWOAC[0][0],"v_{2}{2,QC} w/o AC","p");
  leg[0] -> AddEntry(grDifFlWOAC[1][0],"v_{2}{4,QC} w/o AC","p");

  leg[1] = new TLegend(0.11,.89,0.4,.7); // legend for ref. flow plotting
  leg[1] -> AddEntry(grRefFl[0],"v_{2} with AC","p");
  leg[1] -> AddEntry(grRefFlWOAC[0],"v_{2} w/o AC","p");

  leg[2] = new TLegend(.11,.89,.42,.68);
  leg[2] -> AddEntry(grRefFlCent[0],"v_{2}{MC}","p");
  leg[2] -> AddEntry(grRefFlCent[1],"v_{2}{2,QC}","p");
  leg[2] -> AddEntry(grRefFlCent[2],"v_{2}{4,QC}","p");
  leg[2] -> AddEntry(grRefFlCent[3],"v_{2}{#eta sub-event}","p");
  for (int i=0;i<3;i++){
    leg[i] -> SetFillColor(0);
    leg[i] -> SetTextSize(0.04);
    leg[i] -> SetTextFont(62);
    leg[i] -> SetBorderSize(0);
  }  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);  
  
  // v2 vs cent
  TCanvas *c4 = new TCanvas("c4","Reference flow vs cent",200,10,800,450);
  TH2F *h5 = new TH2F("","",8,0,80,15,0.0,0.08);
  h5 -> Draw();
  h5 -> SetXTitle("cent, %");
  h5 -> SetYTitle("v_{2}");
  for (int i=0;i<4;i++){
    grRefFlCent[i] -> Draw("P");
  }
  leg[2] -> Draw();
  c4 -> SaveAs("./Graphics/v2cent_AC.png");
  
  
  //==========================================================================================================================

  // Drawing multipads of reference & differential flow


  TCanvas *c1 = new TCanvas("c1","Differential flow",200,10,1600,900);
  c1->Divide(3,2,0,0);
  TCanvas *c2 = new TCanvas("c2","Reference flow with & without acceptance correction",200,10,1600,900);
  c2->Divide(3,2,0,0);
  TCanvas *c3 = new TCanvas("c3","Reference flow with acceptance correction",200,10,1600,900);
  c3->Divide(3,2,0,0);
  double xmin=0.15;
  double xmax=3.45;
  double ymin=-0.005;
  double ymax=0.255;
  TH2F *h[ncent], *h2[ncent], *h3[ncent], *h4[ncent];
  TLatex *latex, *latex2, *latex3;
  
  for(int icent=0; icent<6; icent++){
    // Differential flow

    h[icent] = new TH2F("","",1,xmin,xmax,1,ymin,ymax);
    c1 -> cd(icent+1);
    h[icent] -> Draw();
    h[icent] -> SetXTitle("p_{T}, GeV/c");
    h[icent] -> SetYTitle("v_{2}");
    leg[0] -> Draw();
    mgDifFl[icent]-> Draw("P");
    mgDifFlWOAC[icent]-> Draw("P");
    sprintf(hname,"cent: %i-%i%%",10*(icent),10*(icent+1));
    latex = new TLatex(xmax*0.98,ymin+0.02,hname);
    latex -> SetTextFont(62);
    latex -> SetTextSize(0.04);
    latex -> SetTextAlign(31);
    latex -> Draw();
    //=============================================
    // Reference flow with & without acceptance correction
    double ymin1 = TMath::Min(TMath::MinElement(4,v2[icent]),TMath::MinElement(4,v2AC[icent]))*0.98;
    double ymax1 = TMath::Max(TMath::MaxElement(4,v2[icent]),TMath::MaxElement(4,v2AC[icent]))*1.02;
    h2[icent] = new TH2F("","",4,0,4,15,0.01,0.17);
    c2 -> cd(icent+1);
    h2[icent]->SetYTitle("v_{n}");
    h2[icent]->SetCanExtend(TH1::kAllAxes);
    TAxis* a = h2[icent] -> GetXaxis();
    for (int j=0; j<4; j++) h2[icent]->Fill(ch[j],(ymin1+ymax1)/2.,1);
    h2[icent]->GetXaxis()->SetLabelSize(0.05);
    a->SetNdivisions(300); // 3 division, 0 sub-division
    h2[icent]->Draw();
    grshade[icent] -> Draw("f");
    grRefFlWOAC[icent] -> Draw("P");
    grRefFl[icent]-> Draw("P");
    leg[1] -> Draw();
    latex2 = new TLatex(3*0.98,0.03*1.02,hname);
    latex2 -> SetTextFont(62);
    latex2 -> SetTextSize(0.04);
    latex2 -> SetTextAlign(31);
    latex2 -> Draw();
    //=============================================
    // Only Reference flow with acceptance correction
    h3[icent] = new TH2F("","",4,0,4,15,0.01,0.08);
    c3 -> cd(icent+1);
    h3[icent]->SetYTitle("v_{n}");
    h3[icent]->SetCanExtend(TH1::kAllAxes);
    TAxis* a2 = h3[icent] -> GetXaxis();
    for (int j=0; j<4; j++) h3[icent]->Fill(ch[j],0.02,1);
    h3[icent]->GetXaxis()->SetLabelSize(0.05);
    a2->SetNdivisions(300); // 3 division, 0 sub-division
    h3[icent]->Draw();
    grshade[icent] -> Draw("f");
    grRefFl[icent]-> Draw("P");
    latex3 = new TLatex(3*0.98,0.03*1.02,hname);
    latex3 -> SetTextFont(62);
    latex3 -> SetTextSize(0.04);
    latex3 -> SetTextAlign(31);
    latex3 -> Draw();
  } // end of loop over centrality
  c1 -> SaveAs("./Graphics/v2pt_AC.png");
  c2 -> SaveAs("./Graphics/v2compare_AC.png");
  c3 -> SaveAs("./Graphics/v2_AC.png");
  //=============================================
  // Drawing reference flow separately for analysis
  TCanvas *c[ncent];
  TLatex *text[ncent];
  for (int i=0;i<ncent;i++){
    double ymin2 = TMath::MinElement(4,v2AC[i])*0.98;
    double ymax2 = TMath::MaxElement(4,v2AC[i])*1.02;
    // double ymin = 0.01*(i+1);
    // double ymax = 0.03*(i+1);
    sprintf(hname,"Cent%i-%i%%",i*10,(i+1)*10);
    c[i] = new TCanvas(hname,hname,200,10,800,600);

    h4[i] = new TH2F("","",4,0,4,10,ymin2,ymax2);
    h4[i]->SetYTitle("v_{n}");
    h4[i]->SetCanExtend(TH1::kAllAxes);
    
    TAxis* a = h4[i] -> GetXaxis();
    for (int j=0; j<4; j++) h4[i]->Fill(ch[j],(ymin2+ymax2)/2.,1);
    h4[i]->GetXaxis()->SetLabelSize(0.05);
    a->SetNdivisions(300); // 3 division, 0 sub-division
    h4[i]->Draw();
    grshade[i] -> SetFillStyle(1001);
    grshade[i] -> SetFillColor(18);
    grshade[i] -> Draw("f");
    grRefFl[i] -> SetTitle("Reference flow");
    // grRefFlWOAC[i] -> Draw("P");
    grRefFl[i] -> Draw("P");
    sprintf(hname,"#splitline{Ref. flow}{#splitline{-2<#eta<-0.05}{cent: %i-%i%%}}",10*(i),10*(i+1));
    text[i] = new TLatex(1.,(TMath::MinElement(4,grRefFl[i]->GetY())),hname);
    text[i] -> SetTextFont(62);
    text[i] -> SetTextSize(0.04);
    text[i] -> SetTextAlign(21);
    text[i] -> Draw();
    sprintf(hname,"./Graphics/RFCent%i-%i%%.png",i*10,(i+1)*10);
    c[i] -> SaveAs(hname);
  }
  */
  //==========================================================================================================================

  // outFile -> cd();
  // for (int i=0; i<4; i++){
  //   sprintf(hname,"grRF_%i",i);
  //   grRefFlCent[i] -> SetTitle(ch[i]);
  //   grRefFlCent[i] -> Write(hname);
  //   for (int icent=0;icent<ncent;icent++){
  //     sprintf(hname,"gr_%i_%i",icent,i);
  //     grDifFl[i][icent] -> SetTitle(ch[i]);
  //     grDifFl[i][icent] -> Write(hname);
  //   }
  // }
  // outFile -> Close();


  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);  
  TCanvas *c[ncent];
  TLatex *text[ncent];
  TH2F *h4[ncent];
  for (int i=0;i<ncent;i++){
    double ymin2 = TMath::MinElement(4,v2AC[i])*0.8;
    double ymax2 = TMath::MaxElement(4,v2AC[i])*1.2;
    // double ymin = 0.01*(i+1);
    // double ymax = 0.03*(i+1);
    sprintf(hname,"Cent%i-%i%%",i*10,(i+1)*10);
    c[i] = new TCanvas(hname,hname,200,10,800,600);

    h4[i] = new TH2F("","",4,0,4,10,ymin2,ymax2);
    h4[i]->SetYTitle("v_{n}");
    h4[i]->SetCanExtend(TH1::kAllAxes);
    
    TAxis* a = h4[i] -> GetXaxis();
    for (int j=0; j<4; j++) h4[i]->Fill(ch[j],(ymin2+ymax2)/2.,1);
    h4[i]->GetXaxis()->SetLabelSize(0.05);
    a->SetNdivisions(300); // 3 division, 0 sub-division
    h4[i]->Draw();
    grshade[i] -> SetFillStyle(1001);
    grshade[i] -> SetFillColor(18);
    grshade[i] -> Draw("f");
    grRefFl[i] -> SetTitle("Reference flow");
    // grRefFlWOAC[i] -> Draw("P");
    grRefFl[i] -> Draw("P");
    sprintf(hname,"#splitline{Ref. flow}{#splitline{-2<#eta<-0.05}{cent: %i-%i%%}}",10*(i),10*(i+1));
    text[i] = new TLatex(1.,(TMath::MinElement(4,grRefFl[i]->GetY())),hname);
    text[i] -> SetTextFont(62);
    text[i] -> SetTextSize(0.04);
    text[i] -> SetTextAlign(21);
    text[i] -> Draw();
    sprintf(hname,"./Graphics/RFCent%i-%i%%.png",i*10,(i+1)*10);
    c[i] -> SaveAs(hname);
  }
  const char *grTitleRF[4]={"v_{2}{MC};cent, %;v_{2}","v_{2}{2,QC};cent, %;v_{2}","v_{2}{4,QC};cent, %;v_{2}","v_{2}{#eta sub-event};cent, %;v_{2}"};
  for (int i=0; i<4; i++){
    grRefFlCent[i] -> SetTitle(grTitleRF[i]);
  }
  std::vector<TGraphErrors*> vgr;
  for (int i=0; i<4; i++){
    vgr.push_back(grRefFlCent[i]);
  }
  
  TCanvas *can;
  TLatex l;
  //                                                    yRatio_low    x_low     y_low    leg_x_low  leg_x_high
  can = (TCanvas*) DrawTGraph(vgr,"v2 ratio",0.89, 1.11,    0    , 80, 0., 0.1 , 0.65, 0.11, 0.89, 0.35);
  //                                                          yRatio_high  x_high   y_high     leg_y_low   leg_y_high
  sprintf(hname,"v2 vs cent");
  can -> SetName(hname);
  l.SetNDC();
  l.SetTextSize(0.12);
  l.SetTextAlign(21);  
  l.DrawLatex(0.5,0.1,hname);
  sprintf(hname,"./Graphics/%s/v2centratio.png",analysis);
  can -> SaveAs(hname);
/*
  //=============================================
  std::vector<TGraphErrors*> vgrv2pt[8];
  for (int icent=0; icent<8; icent++){
    for (int i=0; i<4; i++){
      vgrv2pt[icent].push_back(grDifFl[i][icent]);
    }  
  }
  TCanvas *cV2PT[8];
  TLatex lV2PT[8];
  for (int icent=0; icent<8; icent++){
    //                                                           yRatio_low   x_low     y_low    leg_x_low  leg_x_high
    cV2PT[icent] = (TCanvas*) DrawTGraph(vgrv2pt[icent],"v2 ratio",0.89, 1.11, 0.0, 3.5, 0., 0.25, 0.65, 0.11, 0.89, 0.35);
    //                                                                yRatio_high  x_high   y_high     leg_y_low   leg_y_high
    sprintf(hname,"Cent %i-%i%%",icent*10,(icent+1)*10);
    cV2PT[icent] -> SetName(hname);
    lV2PT[icent].SetNDC();
    lV2PT[icent].SetTextSize(0.12);
    lV2PT[icent].SetTextAlign(21);  
    lV2PT[icent].DrawLatex(0.5,0.1,hname);
    sprintf(hname,"./Graphics/%s/DFCent%i-%i%%.png",analysis,icent*10,(icent+1)*10);
    cV2PT[icent] -> SaveAs(hname);
  }

*/
}
