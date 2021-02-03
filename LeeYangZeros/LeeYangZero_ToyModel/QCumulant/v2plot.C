#include "Func_StatErrCalc.C"
#include "DrawTGraph.C"
const int ncent = 9; // 0-80%
TGraphErrors *grDifFl[3][ncent];    // v2(pt); 4 = {MC, 2QC, 4QC, EP}
TGraphErrors *grRefFlCent[3];       // v2(cent); 4 = {MC, 2QC, 4QC, EP}
void v2plot(TString inputFileName = "QCumulant.root"){
  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile

  TFile *inFile = new TFile(inputFileName.Data(),"read");

  static const double bin_cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
  static const double bin_centE[ncent] = {0};
  static const float maxpt = 3.5; // max pt
  static const float minpt = 0.2; // min pt
  static const int npt = 12;        // 0.2 - 3.5 GeV/c
  static const double bin_pT[npt + 1] ={0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.2, 2.6, 3.0, 3.5};
  

  // Input hist
  // TProfile for reference flow
  TProfile *hv2MC[ncent];       // profile for MC integrated v2
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hPT[npt];       // profile pt 
  TProfile *hv2MCpt[ncent][npt];   // profile v2pt from MC toy   
  TProfile *hv22pt[ncent][npt];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt]; // <2'>*<4'>

  // Get TProfile histograms from ROOTFile

  for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
    sprintf(hname,"hPT_%i",ipt);
    hPT[ipt]=(TProfile*)inFile->Get(hname);
  }
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

  double v2cent[3][ncent], v2centE[3][ncent];
  double v2pt[3][ncent][npt], v2ptE[3][ncent][npt];

  // ofstream ofile2("v2int.txt");

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

    // ofile2 << icent*10<<"-"<< (icent+1)*10<<" "<< v22intE << " " << v24intE << endl;

    v2cent[0][icent] = v2MCint;
    v2cent[1][icent] = v22int;
    v2cent[2][icent] = v24int;

    v2centE[0][icent] = v2MCintE;
    v2centE[1][icent] = v22intE;
    v2centE[2][icent] = v24intE;

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

      v2MCpt[ipt]  = hv2MCpt[icent][ipt] -> GetBinContent(1);
      ev2MCpt[ipt] = hv2MCpt[icent][ipt] -> GetBinError(1);
      v2pt[0][icent][ipt] = v2MCpt[ipt];
      v2ptE[0][icent][ipt] = ev2MCpt[ipt];
      // 2-particle correlations
      // estimate of the 2-particle differential flow (C.41)
      cor2Red[ipt] = hv22pt[icent][ipt]->GetBinContent(1);
      v22dif[ipt] = Vn2Dif(cor2Red[ipt],cor2);
      v2pt[1][icent][ipt] = v22dif[ipt];
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
      v2ptE[1][icent][ipt] = v22difE[ipt];
      // 4-particle correlations
      // estimate of the 4-particle differential flow (C.45)
      cor4Red[ipt] = hv24pt[icent][ipt]->GetBinContent(1);
      v24dif[ipt] = Vn4Dif(cor2Red[ipt], cor2, cor4Red[ipt], cor4);
      v2pt[2][icent][ipt] = v24dif[ipt];
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
      v2ptE[2][icent][ipt] = v24difE[ipt];
    } // end of loop for all pT bin

    // Monte-Carlo differential flow
    grDifFl[0][icent] = new TGraphErrors(npt,pt[icent],v2MCpt,ept[icent],ev2MCpt);
    grDifFl[0][icent] -> SetMarkerColor(kRed+1);
    grDifFl[0][icent] -> SetMarkerStyle(25);
    // 2QC differential flow
    grDifFl[1][icent] = new TGraphErrors(npt,pt[icent],v22dif,ept[icent],v22difE);
    grDifFl[1][icent] -> SetMarkerColor(kGreen+1);
    grDifFl[1][icent] -> SetMarkerStyle(20);
    // 4QC differential flow
    grDifFl[2][icent] = new TGraphErrors(npt,pt[icent],v24dif,ept[icent],v24difE);
    grDifFl[2][icent] -> SetMarkerColor(kAzure+2);
    grDifFl[2][icent] -> SetMarkerStyle(22);

  } // end of loop over centrality classes
  //==========================================================================================================================
  grRefFlCent[0] = new TGraphErrors(ncent,bin_cent,v2cent[0],bin_centE,v2centE[0]);
  grRefFlCent[0]->SetMarkerColor(kRed+1);
  grRefFlCent[0]->SetMarkerStyle(25);

  grRefFlCent[1] = new TGraphErrors(ncent,bin_cent,v2cent[1],bin_centE,v2centE[1]);
  grRefFlCent[1]->SetMarkerColor(kGreen+1);
  grRefFlCent[1]->SetMarkerStyle(20);

  grRefFlCent[2] = new TGraphErrors(ncent,bin_cent,v2cent[2],bin_centE,v2centE[2]);
  grRefFlCent[2] -> SetMarkerColor(kAzure+2);
  grRefFlCent[2] -> SetMarkerStyle(22);


  for (int i=0;i<3;i++){
    grRefFlCent[i]->SetMarkerSize(1.3);
    grRefFlCent[i]->SetDrawOption("P");
  }

  cout << "v22[9]={";
  for (int ic = 0 ; ic < ncent-1; ic++)
  {
    cout << v2cent[1][ic] <<", ";
  }
  cout << v2cent[1][ncent-1] <<"};" << endl;

  cout << "v22e[9]={";
  for (int ic = 0 ; ic < ncent-1; ic++)
  {
    cout << v2centE[1][ic] <<", ";
  }
  cout << v2centE[1][ncent-1] <<"};" << endl;

  cout << "v24[9]={";
  for (int ic = 0 ; ic < ncent-1; ic++)
  {
    cout << v2cent[2][ic] <<", ";
  }
  cout << v2cent[2][ncent-1] <<"};" << endl;

  cout << "v24e[9]={";
  for (int ic = 0 ; ic < ncent-1; ic++)
  {
    cout << v2centE[2][ic] <<", ";
  }
  cout << v2centE[2][ncent-1] <<"};" << endl;

  // Debug
  // pT-integrated flow

  for (int ic = 0 ; ic < ncent; ic++)
  {
    for (int i = 0; i < 3; i++)
    {
      cout << v2cent[i][ic] << " ";
    }
    cout << endl;

  }

  // Differential flow

  // for (int ic = 0 ; ic < ncent; ic++)
  // {
  //   cout << "Cent:" << ic << endl;
  //   for (int ipt = 0; ipt < npt; ipt++){
  //   for (int i = 0; i < 3; i++)
  //   {
  //     cout << v2pt[i][ic][ipt] << " ";
  //   }
  //   cout << endl;
  //   }
  // }

  
}