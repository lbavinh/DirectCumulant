#include "Func_StatErrCalc.C"
#include "DrawTGraph.C"

char tGraphErrors[400]={"./ROOTFile/TGraphError.root"};

void acceptance_correction_v2plot(){
  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile
  char analysis[20]={"acceptance"};
  TFile* inFile = new TFile("./ROOTFile/acceptance_10mil.root","read");
  TFile *outFile = new TFile(tGraphErrors,"recreate");
  
  static const int ncent = 8; // 0-80%
  static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
  static const double bin_centE[ncent] = {0};
  static const double maxpt = 3.5; // max pt
  static const double minpt = 0.2; // min pt
  static const int npt = 12;        // 0.2 - 3.5 GeV/c
  static const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  
  // TCanvas *cTemp = new TCanvas("cTemp","cTemp",200,10,800,450);

  // TH1I *hMult = (TH1I*)inFile->Get("hMult");
  // hMult -> Draw();
  // sprintf(hname,"./Graphics/%s/mult.png",analysis);
  // cTemp -> Draw();
  // cTemp -> SaveAs(hname);

  // TH1F *hEta = (TH1F*)inFile->Get("hEta");
  // hEta -> Draw();
  // sprintf(hname,"./Graphics/%s/eta.png",analysis);
  // cTemp -> SaveAs(hname);  

  // TH1F *hPhi = (TH1F*)inFile->Get("hPhi");
  // hPhi -> Draw();
  // sprintf(hname,"./Graphics/%s/phi.png",analysis);
  // cTemp -> SaveAs(hname);

  // TH1F *hPhil = (TH1F*)inFile->Get("hPhil");
  // hPhil -> Draw();
  // sprintf(hname,"./Graphics/%s/phil.png",analysis);
  // cTemp -> SaveAs(hname);

  // TH1F *hPt = (TH1F*)inFile->Get("hPt");
  // hPt -> Draw();
  // sprintf(hname,"./Graphics/%s/pt.png",analysis);
  // cTemp -> SaveAs(hname);

  // TH1F *H_EP = (TH1F*)inFile->Get("H_EP_1_0");
  // H_EP -> Draw();
  // H_EP -> SetTitle("Raw event plane #Psi_{2,#eta-} distr, cent: 10-20%;#Psi_{2,#eta-}, rad");
  // sprintf(hname,"./Graphics/%s/raw.png",analysis);
  // cTemp -> SaveAs(hname);

  // TH1F *hPsiRecentered = (TH1F*)inFile->Get("hPsiRecentered_1_0");
  // hPsiRecentered -> Draw();
  // hPsiRecentered -> SetTitle("Recentered event plane #Psi_{2,#eta-} distr, cent: 10-20%;#Psi_{2,#eta-}, rad");
  // sprintf(hname,"./Graphics/%s/rec.png",analysis);
  // cTemp -> SaveAs(hname);  

  // TH1F *hPsiFlattened = (TH1F*)inFile->Get("hPsiFlattened_1_0");
  // hPsiFlattened -> Draw();
  // hPsiFlattened -> SetTitle("Flattened event plane #Psi_{2,#eta-} distr, cent: 10-20%;#Psi_{2,#eta-}, rad");
  // sprintf(hname,"./Graphics/%s/flat.png",analysis);
  // cTemp -> SaveAs(hname);  

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
  double v2[ncent][4];
  double ev2[ncent][4];
  double x[4]={0.5,1.5,2.5,3.5};
  double ex[4]={0};

  double v2AC[ncent][4];

  double v2centAC[4][ncent];
  double v2centEAC[4][ncent];

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

    v2centAC[0][icent] = v2MCint;
    v2centAC[1][icent] = v22intAC;
    v2centAC[2][icent] = v24intAC;
    v2centAC[3][icent] = v2EPint;  

    v2centEAC[0][icent] = v2MCintE;
    v2centEAC[1][icent] = v22intE;
    v2centEAC[2][icent] = v24intE;
    v2centEAC[3][icent] = v2EPintE;  

    // TGraphErrors for compare 4 method
    grRefFl[icent] = new TGraphErrors(4,x,v2AC[icent],ex,ev2[icent]);
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

    double v22difAC[npt], v24difAC[npt];

    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      
      // Differential flow v2MC
      v2MCpt[ipt]  = hv2MCpt[icent][ipt] -> GetBinContent(1);
      ev2MCpt[ipt] = hv2MCpt[icent][ipt] -> GetBinError(1);

      // 2-particle correlations
      // estimate of the 2-particle differential flow (C.41)
      cor2Red[ipt] = hv22pt[icent][ipt]->GetBinContent(1);
      v22dif[ipt] = Vn2Dif(cor2Red[ipt],cor2);
      // acceptance correction
      v22difAC[ipt] = (cor2Red[ipt] - cos2psi1[icent][ipt] * cos2phi1[icent] - sin2psi1[icent][ipt] * sin2phi1[icent]) / v22intAC;


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
  // Elliptic flow from eta sub-event method
  for (int icent=0; icent<ncent; icent++){
    double v2EP[npt]={0}, ev2EP[npt]={0};
    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      v2EP[ipt] = hv2EP[ipt]->GetBinContent(icent+1);
      ev2EP[ipt] = hv2EP[ipt]->GetBinError(icent+1);
    }
    // Event plane differential flow
    grDifFl[3][icent] = new TGraphErrors(npt,pt[icent],v2EP,ept[icent],ev2EP);
    grDifFl[3][icent] -> SetMarkerColor(kBlack);
    grDifFl[3][icent] -> SetMarkerStyle(23);
    grDifFl[3][icent] -> SetMarkerSize(1.3);
    grDifFl[3][icent] -> SetDrawOption("P");
    mgDifFl[icent] -> Add(grDifFl[3][icent]);
  }
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
  /*
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
  */
  const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};
  //==========================================================================================================================

  // Drawing multipads of reference & differential flow
/*

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
  const char *grTitleDF[4]={"[1] v_{2}{MC};p_{T}, GeV/c;v_{2}","[2] v_{2}{2,QC};p_{T}, GeV/c;v_{2}","[3] v_{2}{4,QC};p_{T}, GeV/c;v_{2}","[1] v_{2}{#eta sub-event};p_{T}, GeV/c;v_{2}"};

  outFile -> cd();
  for (int i=0; i<4; i++){
    sprintf(hname,"grRF_%i",i);
    grRefFlCent[i] -> SetTitle(ch[i]);
    grRefFlCent[i] -> Write(hname);
    for (int icent=0;icent<ncent;icent++){
      sprintf(hname,"gr_%i_%i",icent,i);
      grDifFl[i][icent] -> SetTitle(grTitleDF[i]);
      grDifFl[i][icent] -> Write(hname);
    }
  }
  outFile -> Close();

  // std::vector<TGraphErrors*> vgr;
  // for (int i=0; i<3; i++){
  //   vgr.push_back(grRefFlCent[i]);
  // }
  
  // TCanvas *can;
  // can = (TCanvas*) DrawTGraph(vgr,"",0.89,1.11,0,80,0.,0.1,0.65,0.11,0.89,0.35);
  // sprintf(hname,"v2 vs cent");
  // can -> SetName(hname);
  // sprintf(hname,"./Graphics/%s/v2centratio.png",analysis);
  // can -> SaveAs(hname);

  //=============================================
  std::vector<TGraphErrors*> vgrv2pt[8];
  for (int icent=0; icent<8; icent++){
    for (int i=0; i<3; i++){
      vgrv2pt[icent].push_back(grDifFl[i][icent]);
    }  
  }
  TCanvas *cV2PT[8];
  TLatex lV2PT[8];
  for (int icent=0; icent<8; icent++){
    sprintf(hname,"#splitline{Toy model generator}{#splitline{with non-uniform acceptance}{Centrality %i-%i%%}}",icent*10,(icent+1)*10);
    cV2PT[icent] = (TCanvas*) DrawTGraph(vgrv2pt[icent],"",0.89, 1.11, 0., 2.2, -0.01, 0.25, 0.18, 0.65, 0.5, 0.89, hname);
    cV2PT[icent] -> SetName(hname);
  }
  sprintf(hname,"./Graphics/%s/DFCent30-40.png",analysis);
  cV2PT[3] -> SaveAs(hname);

  // Drawing reference flow separately for analysis
  TCanvas *c = new TCanvas("c","canvas",200,10,550,550);
  c->SetBottomMargin(0.1);
  c->SetTopMargin(0.06);
  c->SetLeftMargin(0.17);
  c->SetRightMargin(0.02);



  // double ymin2 = TMath::MinElement(3,v2AC[3])*0.9;
  // double ymax2 = TMath::MaxElement(3,v2[3])*1.1;
  double ymin2 = 0.04;
  double ymax2 = 0.2;
  TH2F *h = new TH2F("h","",3,0,3,10,ymin2,ymax2);
  h->SetYTitle("v_{2}");
  h->SetCanExtend(TH1::kAllAxes);
  
  TAxis* a = h -> GetXaxis();
  for (int j=0; j<3; j++) h->Fill(ch[j],(ymin2+ymax2)/2.,1);
  h->GetXaxis()->SetLabelSize(0.05);
  a->SetNdivisions(300); // 3 division, 0 sub-division
  h->Draw();
  grshade[3] -> SetFillStyle(1001);
  grshade[3] -> SetFillColor(18);
  
  grRefFl[3] -> Draw("P");
  grRefFlWOAC[3] -> SetMarkerSize(1.5);
  grRefFlWOAC[3] -> Draw("P");
  grshade[3] -> Draw("f");
    TLegend *legend;
  legend = new TLegend(.2,.9,.42,.8); // legend for dif. flow plotting
  legend -> AddEntry(grRefFlWOAC[3],"without acceptance correction","p");
  legend -> AddEntry(grRefFl[3],"with acceptance correction","p");
  legend -> SetFillColor(0);
  legend -> SetTextSize(0.04);
  legend -> SetTextFont(62);
  legend -> SetBorderSize(0);
  legend -> Draw();
  sprintf(hname,"./Graphics/%s/RFCent30-40.png",analysis);
  c -> SaveAs(hname);


}