#include "Func_StatErrCalc.C"
#include "DrawTGraph.C"
static const int ncent = 2; // 0-40%
TGraphErrors *grDifFl[4][ncent];    // v2(pt); 4 = {MC, 2QC, 4QC, EP}
TGraphErrors *grRefFl[ncent];     
TGraphErrors *grRefFlCent[4];       // v2(cent); 4 = {MC, 2QC, 4QC, EP}
void v2plot(){
  bool bDrawPlots = 1;
  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile
  // char analysis[20]={"pure"};

  TFile *inFile, *outFile;
  sprintf(hname,"../ROOTFile/sum.root");
  inFile = new TFile(hname,"read");
  sprintf(hname,"../CompareResult/Vinh.root");
  outFile = new TFile(hname,"recreate");
  
  
  static const double bin_centE[ncent] = {0};
  static const int npt = 10; // 0.5 - 3.6 GeV/c - number of pT bins
  static const double bin_pT[npt+1]={0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.8,2.3,3.0};

  static const int ncent = 2; // 0-40%
  static const double bin_cent[ncent] = {5,25};

  static const double maxpt = 3.; // max pt
  static const double minpt = 0.; // min pt

  
  if (bDrawPlots){
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
    // cTemp -> SaveAs("../Graphics/pt.pdf");
  }

  
  // Input hist
  // TProfile for reference flow
  // TProfile *hv2MC[ncent];       // profile for MC integrated v2
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow
  TProfile *hPT[npt];       // profile pt 
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

  TProfile *hv2EP[npt];	// elliptic flow from EP method
  TProfile *hv22EP;        // elliptic flow cent: 10-40% from EP method
  TProfile *HRes;

  // OUTPUT

  TGraph *grshade[ncent];
  TMultiGraph *mgRefFl[ncent], *mgDifFl[ncent];

  // Get TProfile histograms from ROOTFile
  hv22EP = (TProfile*)inFile->Get("hv22EP");
  HRes = (TProfile*)inFile->Get("HRes");
  for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
    sprintf(hname,"hv2EP_%i",ipt);
    hv2EP[ipt]=(TProfile*)inFile->Get(hname);
    sprintf(hname,"hPT_%i",ipt);
    hPT[ipt]=(TProfile*)inFile->Get(hname);
  }
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // sprintf(hname,"hv2MC_%i",icent);
    // hv2MC[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv22_%i",icent);
    hv22[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv24_%i",icent);
    hv24[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcov24_%i",icent);
    hcov24[icent] = (TProfile*)inFile->Get(hname);

    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
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

  double v2cent[4][ncent];
  double v2centE[4][ncent];

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
    double res2 = sqrt(HRes->GetBinContent(icent+1));
    double v2obs = hv22EP->GetBinContent(icent+1);
    v2EPint = v2obs / res2;
    double dv2obs = hv22EP->GetBinError(icent+1);
    double dres2 = HRes->GetBinError(icent+1);

    // v2EPintE = sqrt(dv2obs*dv2obs/res2/res2 + v2obs*v2obs/(4*pow(res2,6)*dres2*dres2));
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

    v2cent[0][icent] = v2MCint;
    v2cent[1][icent] = v22int;
    v2cent[2][icent] = v24int;
    v2cent[3][icent] = v2EPint;  

    v2centE[0][icent] = v2MCintE;
    v2centE[1][icent] = v22intE;
    v2centE[2][icent] = v24intE;
    v2centE[3][icent] = v2EPintE; 

    grRefFl[icent] = new TGraphErrors(4,x,v2[icent],ex,ev2[icent]);
    grRefFl[icent]->SetMarkerColor(kRed);
    grRefFl[icent]->SetMarkerStyle(20);
    grRefFl[icent]->SetMarkerSize(1.3);
    grRefFl[icent]->SetDrawOption("P");
    // Set a shade between error of v2MC
    grshade[icent] = new TGraph(10);
    for (Int_t i=0; i<5; i++) {
      grshade[icent]->SetPoint(i,i+0.005,v2[icent][0]+ev2[icent][0]);
      grshade[icent]->SetPoint(5+i,4+0.005-i,v2[icent][0]-ev2[icent][0]);
    }
    grshade[icent] -> SetFillStyle(1001);
    grshade[icent] -> SetFillColor(18);
    grshade[icent] -> SetDrawOption("f");
    mgRefFl[icent] = new TMultiGraph();
    mgRefFl[icent] -> Add(grRefFl[icent]);
    mgRefFl[icent] -> Add(grshade[icent]);

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
    // create multigraph
    mgDifFl[icent] = new TMultiGraph();
    for (int i=1; i<4; i++){
      grDifFl[i][icent] -> SetMarkerSize(1.3);
      grDifFl[i][icent] -> SetDrawOption("P");
      mgDifFl[icent] -> Add(grDifFl[i][icent]);
    }
  } // end of loop over centrality classes
  //==========================================================================================================================
  grRefFlCent[3] = new TGraphErrors(ncent,bin_cent,v2cent[0],bin_centE,v2centE[0]);
  grRefFlCent[3]->SetMarkerColor(kBlack);
  grRefFlCent[3]->SetMarkerStyle(24);

  grRefFlCent[1] = new TGraphErrors(ncent,bin_cent,v2cent[1],bin_centE,v2centE[1]);
  grRefFlCent[1]->SetMarkerColor(kGreen+1);
  grRefFlCent[1]->SetMarkerStyle(20);

  grRefFlCent[2] = new TGraphErrors(ncent,bin_cent,v2cent[2],bin_centE,v2centE[2]);
  grRefFlCent[2] -> SetMarkerColor(kAzure+2);
  grRefFlCent[2] -> SetMarkerStyle(22);

  grRefFlCent[0] = new TGraphErrors(ncent,bin_cent,v2cent[3],bin_centE,v2centE[3]);
  grRefFlCent[0] -> SetMarkerColor(kRed);
  grRefFlCent[0] -> SetMarkerStyle(25);  

  for (int i=0;i<4;i++){
    grRefFlCent[i]->SetMarkerSize(1.3);
    grRefFlCent[i]->SetDrawOption("P");
  }
  //==========================================================================================================================

  const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};

  // Elliptic flow from eta sub-event method
  for (int icent=0; icent<ncent; icent++){
    double v2EP[npt]={0}, ev2EP[npt]={0};
    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      // v2EP[ipt] = hv2EP[ipt]->GetBinContent(icent+1);
      // ev2EP[ipt] = hv2EP[ipt]->GetBinError(icent+1);

      double res2 = sqrt(HRes->GetBinContent(icent+1));
      double v2obs = hv2EP[ipt]->GetBinContent(icent+1);
      v2EP[ipt] = v2obs / res2;
      double dv2obs = hv2EP[ipt]->GetBinError(icent+1);
      double dres2 = HRes->GetBinError(icent+1);

      // ev2EP[ipt] = sqrt(dv2obs*dv2obs/res2/res2 + v2obs*v2obs/(4*pow(res2,6)*dres2*dres2));
      ev2EP[ipt] = hv2EP[ipt]->GetBinError(icent+1);
    }
    // Event plane differential flow
    grDifFl[0][icent] = new TGraphErrors(npt,pt[icent],v2EP,ept[icent],ev2EP);
    grDifFl[0][icent] -> SetMarkerColor(kRed);
    grDifFl[0][icent] -> SetMarkerStyle(25);
    grDifFl[0][icent] -> SetMarkerSize(1.3);
    grDifFl[0][icent] -> SetDrawOption("P");
    // mgDifFl[icent] -> Add(grDifFl[0][icent]);
  }
  //==========================================================================================================================
  // TFile *inFileGraphEP = new TFile("../ROOTFile/TGraphErrors_EP_MultLargerThan5.root","read");
  // for (int icent=0;icent<ncent;icent++){
  //   sprintf(hname,"gr_cent%i_0",icent);
  //   grDifFl[0][icent] = (TGraphErrors*)inFileGraphEP->Get(hname);
  //   grDifFl[0][icent] -> SetMarkerColor(kRed);
  //   grDifFl[0][icent] -> SetMarkerStyle(25);
  //   grDifFl[0][icent] -> SetMarkerSize(1.3);
  //   grDifFl[0][icent] -> SetDrawOption("P");    
  // }
  // sprintf(hname,"grRF_0");
  // grRefFlCent[0] = (TGraphErrors*)inFileGraphEP->Get(hname);
  // grRefFlCent[0] -> SetMarkerColor(kRed);
  // grRefFlCent[0] -> SetMarkerStyle(25);
  // inFileGraphEP -> Close();

  //==========================================================================================================================
  // Drawing multipads of reference & differential flow
  /*
  TLegend *leg = new TLegend(0.11,.95,0.4,.78);
  leg -> AddEntry(grDifFl[0][0],"v_{2}{MC}","p");
  leg -> AddEntry(grDifFl[1][0],"v_{2}{2,QC}","p");
  leg -> AddEntry(grDifFl[2][0],"v_{2}{4,QC}","p");
  leg -> AddEntry(grDifFl[3][0],"v_{2}{#eta sub-event}","p");
  leg -> SetFillColor(0);
  leg -> SetTextSize(0.04);
  leg -> SetTextFont(62);
  leg -> SetBorderSize(0);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1","multipads",200,10,1600,900);
  c1->Divide(3,2,0,0);
  TCanvas *c2 = new TCanvas("c2","multipads",200,10,1600,900);
  c2->Divide(3,2,0,0);
  double xmin=0.;
  double xmax=maxpt;
  double ymin=-0.005;
  double ymax=0.255;
  TH2F *h[ncent], *h2[ncent], *h3[ncent];
  TLatex *latex, *latex2;
  for(int icent=0; icent<6; icent++){
    // differential flow
    h[icent] = new TH2F("","",5,xmin,xmax,5,ymin,ymax);
    c1 -> cd(icent+1);
    h[icent] -> Draw();
    h[icent] -> SetXTitle("p_{T}, GeV/c");
    h[icent] -> SetYTitle("v_{2}");
    mgDifFl[icent]-> Draw("P");
    leg -> Draw();
    char text1[800];
    sprintf(text1,"cent: %i-%i%%",10*(icent),10*(icent+1));
    latex = new TLatex(xmax*0.98,ymin+0.02,text1);
    latex -> SetTextFont(62);
    latex -> SetTextSize(0.04);
    latex -> SetTextAlign(31);
    latex -> Draw();
    //=============================================
    // reference flow
    double ymin2 = TMath::MinElement(4,v2[icent])*0.98;
    double ymax2 = TMath::MaxElement(4,v2[icent]) + TMath::MaxElement(4,ev2[icent])*1.1;
    h2[icent] = new TH2F("","",4,0,4,10,0.015,0.075);
    c2 -> cd(icent+1);
    h2[icent]->SetYTitle("v_{n}");
    h2[icent]->SetCanExtend(TH1::kAllAxes);
    const char *ch[4]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta sub-event}"};
    TAxis* a = h2[icent] -> GetXaxis();
    h2[icent] -> Fill(ch[0],(ymin2+ymax2)/2.,1);
    h2[icent] -> Fill(ch[1],(ymin2+ymax2)/2.,1);
    h2[icent] -> Fill(ch[2],(ymin2+ymax2)/2.,1);
    h2[icent] -> Fill(ch[3],(ymin2+ymax2)/2.,1);
    h2[icent]->GetXaxis()->SetLabelSize(0.05);
    a->SetNdivisions(300); // 3 division, 0 sub-division
    h2[icent]->Draw();
    //grshade[icent] -> Draw("f");
    mgRefFl[icent]-> Draw("P");

    latex2 = new TLatex(3*0.98,0.03*1.02,text1);
    latex2 -> SetTextFont(62);
    latex2 -> SetTextSize(0.04);
    latex2 -> SetTextAlign(31);
    latex2 -> Draw();
  }
  sprintf(hname,"../Graphics/v2pt.png");
  c1 -> SaveAs(hname);
  sprintf(hname,"../Graphics/v2.png");
  c2 -> SaveAs(hname);
  //=============================================
  
  // Drawing reference flow separately for analysis
  TCanvas *c[ncent];
  TLatex *text[ncent];
  for (int i=0;i<ncent;i++){
    double ymin = TMath::MinElement(4,v2[i])*0.98;
    double ymax = TMath::MaxElement(4,v2[i])*1.02;
    // double ymin = 0.01*(i+1);
    // double ymax = 0.03*(i+1);
    sprintf(hname,"Cent%i-%i%%",i*10,(i+1)*10);
    c[i] = new TCanvas(hname,hname,200,10,800,600);

    h3[i] = new TH2F("","",4,0,4,10,ymin,ymax);
    h3[i]->SetYTitle("v_{n}");
    h3[i]->SetCanExtend(TH1::kAllAxes);
    
    TAxis* a = h3[i] -> GetXaxis();
    for (int j=0; j<4; j++) h3[i]->Fill(ch[j],(ymin+ymax)/2.,1);
    h3[i]->GetXaxis()->SetLabelSize(0.05);
    a->SetNdivisions(300); // 3 division, 0 sub-division
    h3[i]->Draw();
    grshade[i] -> SetFillStyle(1001);
    grshade[i] -> SetFillColor(18);
    grshade[i] -> Draw("f");
    grRefFl[i] -> SetTitle("Reference flow");
    grRefFl[i] -> Draw("P");
    char text1[800];
    sprintf(text1,"#splitline{Ref. flow}{#splitline{-2<#eta<-0.05}{cent: %i-%i%%}}",10*(i),10*(i+1));
    text[i] = new TLatex(1.,(TMath::MinElement(3,grRefFl[i]->GetY())),text1);
    text[i] -> SetTextFont(62);
    text[i] -> SetTextSize(0.04);
    text[i] -> SetTextAlign(21);
    text[i] -> Draw();
    sprintf(hname,"../Graphics/Cent%i-%i%%.png",i*10,(i+1)*10);
    c[i] -> SaveAs(hname);
  }
  */
  //==========================================================================================================================
  const char *grTitleDF[4]={"[1] v_{2}{#eta sub-event};p_{T}, GeV/c;v_{2}","[2] v_{2}{2,QC};p_{T}, GeV/c;v_{2}","[3] v_{2}{4,QC};p_{T}, GeV/c;v_{2}","v_{2}{MC};p_{T}, GeV/c;v_{2}"};
  const char *grTitleRF[4]={"[1] v_{2}{#eta sub-event};cent, %;v_{2}","[2] v_{2}{2,QC};cent, %;v_{2}","[3] v_{2}{4,QC};cent, %;v_{2}","v_{2}{MC};cent, %;v_{2}"};

  outFile -> cd();
  for (int i=0; i<4; i++){
    sprintf(hname,"grRF_%i",i);
    grRefFlCent[i] -> SetTitle(grTitleRF[i]);
    grRefFlCent[i] -> Write(hname);
    for (int icent=0;icent<ncent;icent++){
      sprintf(hname,"gr_cent%i_%i",icent,i);
      grDifFl[i][icent] -> SetTitle(grTitleDF[i]);
      grDifFl[i][icent] -> Write(hname);
    }
  }
  outFile -> Close();
  if (!bDrawPlots) return;
  std::vector<TGraphErrors*> vgr;
  for (int i=0; i<3; i++){
    vgr.push_back(grRefFlCent[i]);
  }
  
  TCanvas *can;
  TLatex l;
  //                                                    yRatio_low    x_low     y_low    leg_x_low  leg_x_high
  can = (TCanvas*) DrawTGraph(vgr,"",0.67, 1.07,    0    , 80, 0., 0.1 , 0.18, 0.65, 0.5, 0.89);
  //                                                          yRatio_high  x_high   y_high     leg_y_low   leg_y_high
  sprintf(hname,"v2 vs cent");
  can -> SetName(hname);
  // l.SetNDC();
  // l.SetTextSize(0.12);
  // l.SetTextAlign(21);  
  // l.DrawLatex(0.5,0.1,hname);
  sprintf(hname,"../Graphics/v2centratio.png");
  can -> SaveAs(hname);

  //=============================================
  // for (int i=0;i<ncent;i++){
  //   grDifFl[2][i] -> SetMarkerColor(kRed);
  // }
  std::vector<TGraphErrors*> vgrv2pt[ncent];
  for (int icent=0; icent<ncent; icent++){
    for (int i=0; i<3; i++){
      vgrv2pt[icent].push_back(grDifFl[i][icent]);
    }  
  }
  TCanvas *cV2PT[ncent];
  // TLatex lV2PT[ncent];
  TPaveText *ptext[ncent];

  sprintf(hname,"Centrality 0-10");
  cV2PT[0] = (TCanvas*) DrawTGraph(vgrv2pt[0],"",0.76, 1.24, 0., maxpt, 0., 0.2, 0.18, 0.65, 0.5, 0.89, "Centrality 0-10%");
  sprintf(hname,"Centrality 0-10");
  cV2PT[0] -> SetName(hname);
  sprintf(hname,"../Graphics/DFCentrality0-10.png");
  cV2PT[0] -> SaveAs(hname);

  sprintf(hname,"Centrality 10-40");
  cV2PT[1] = (TCanvas*) DrawTGraph(vgrv2pt[1],"",0.76, 1.24, 0., maxpt, 0., 0.2, 0.18, 0.65, 0.5, 0.89, "Centrality 10-40%");
  sprintf(hname,"Centrality 10-40");
  cV2PT[1] -> SetName(hname);
  sprintf(hname,"../Graphics/DFCentrality10-40.png");
  cV2PT[1] -> SaveAs(hname);

  // for (int icent=4; icent<8; icent++){
  //   sprintf(hname,"Centrality %i-%i%%",icent*10,(icent+1)*10);
  //   //                                                           yRatio_low   x_low     y_low    leg_x_low  leg_x_high
  //   cV2PT[icent] = (TCanvas*) DrawTGraph(vgrv2pt[icent],"",0.65, 1.35, 0., maxpt, -0.5, 1.0, 0.18, 0.65, 0.5, 0.89, hname);
  //   //                                                                yRatio_high  x_high   y_high     leg_y_low   leg_y_high
  //   sprintf(hname,"Cent %i-%i%%",icent*10,(icent+1)*10);
  //   cV2PT[icent] -> SetName(hname);

  //   // lV2PT[icent].SetNDC();
  //   // lV2PT[icent].SetTextSize(0.12);
  //   // lV2PT[icent].SetTextAlign(21);  
  //   // lV2PT[icent].DrawLatex(0.5,0.1,hname);
  //   sprintf(hname,"../Graphics/DFCent%i-%i%%.png",icent*10,(icent+1)*10);
  //   // cV2PT[icent] -> SaveAs(hname);
  // }
}