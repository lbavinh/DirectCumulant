#define PLOTV2QCUMULANT
#include "DrawTGraph.C"
#include "PlotV2QCumulant_Model.C"
TGraphErrors* PlotV2QCumulant(TString inFileName = "FirstRun_vHLLEUrQMD_11.5_Reco.root", int METHOD=2, int CENT=3, int ID=8){
  // 2QC, 4QC, 2QC-gapped
  TFile *inFile = new TFile(inFileName.Data(),"read");
  TProfile *pCorrelator2EtaGap = (TProfile*)inFile->Get("pCorrelator2EtaGap");
  TProfile *pCorrelator2 = (TProfile*)inFile->Get("pCorrelator2");
  TProfile *pCorrelator4 = (TProfile*)inFile->Get("pCorrelator4");
  TProfile2D *pReducedCorrelator2EtaGap[npid]; // <<2'>> (with eta-gap)
  TProfile2D *pReducedCorrelator2[npid]; // <<2'>>
  TProfile2D *pReducedCorrelator4[npid]; // <<4'>>
  TProfile2D *pCov22RedEtaGap[npid];
  TProfile *pCov24 = (TProfile*)inFile->Get("pCov24");
  TProfile2D *pCov22Red[npid];
  TProfile2D *pCov24Red[npid];
  TProfile2D *pCov42Red[npid];
  TProfile2D *pCov44Red[npid];
  TProfile2D *pCov2Red4Red[npid];
  for (int i=0; i<npid-4; i++)
  {
    pReducedCorrelator2EtaGap[i] = (TProfile2D*)inFile->Get(Form("pReducedCorrelator2EtaGap_pid%i",i));
    pReducedCorrelator2[i]   = (TProfile2D*) inFile->Get(Form("pReducedCorrelator2_pid%i",i));
    pReducedCorrelator4[i]   = (TProfile2D*) inFile->Get(Form("pReducedCorrelator4_pid%i",i));
    pCov22RedEtaGap[i]       = (TProfile2D*) inFile->Get(Form("pCov22RedEtaGap_pid%i",i));
    pCov22Red[i]             = (TProfile2D*) inFile->Get(Form("pCov22Red_pid%i",i));
    pCov24Red[i]             = (TProfile2D*) inFile->Get(Form("pCov24Red_pid%i",i));
    pCov42Red[i]             = (TProfile2D*) inFile->Get(Form("pCov42Red_pid%i",i));
    pCov44Red[i]             = (TProfile2D*) inFile->Get(Form("pCov44Red_pid%i",i));
    pCov2Red4Red[i]          = (TProfile2D*) inFile->Get(Form("pCov2Red4Red_pid%i",i));
  }

  TProfile *pReducedCorrelator2EtaGap_cent[npid][ncent];
  TProfile *pReducedCorrelator2_cent[npid][ncent];
  TProfile *pReducedCorrelator4_cent[npid][ncent];
  TProfile *pCov22RedEtaGap_cent[npid][ncent];
  TProfile *pCov22Red_cent[npid][ncent];
  TProfile *pCov24Red_cent[npid][ncent];
  TProfile *pCov42Red_cent[npid][ncent];
  TProfile *pCov44Red_cent[npid][ncent];
  TProfile *pCov2Red4Red_cent[npid][ncent];
  for (int i = 0; i < npid-4; i++)
  {
    for (int c = 0; c < ncent; c++)
    {
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)pReducedCorrelator2EtaGap[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2EtaGap[i]->GetName(),c), c+1, c+1);
      pReducedCorrelator2_cent[i][c] = (TProfile*)pReducedCorrelator2[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator2[i]->GetName(),c), c+1, c+1);
      pReducedCorrelator4_cent[i][c] = (TProfile*)pReducedCorrelator4[i]->ProfileX(Form("%s_cent%i",pReducedCorrelator4[i]->GetName(),c), c+1, c+1);
      pCov22RedEtaGap_cent[i][c] = (TProfile*)pCov22RedEtaGap[i]->ProfileX(Form("%s_cent%i",pCov22RedEtaGap[i]->GetName(),c), c+1, c+1);
      pCov22Red_cent[i][c] = (TProfile*)pCov22Red[i]->ProfileX(Form("%s_cent%i",pCov22Red[i]->GetName(),c), c+1, c+1);
      pCov24Red_cent[i][c] = (TProfile*)pCov24Red[i]->ProfileX(Form("%s_cent%i",pCov24Red[i]->GetName(),c), c+1, c+1); 
      pCov42Red_cent[i][c] = (TProfile*)pCov42Red[i]->ProfileX(Form("%s_cent%i",pCov42Red[i]->GetName(),c), c+1, c+1); 
      pCov44Red_cent[i][c] = (TProfile*)pCov44Red[i]->ProfileX(Form("%s_cent%i",pCov44Red[i]->GetName(),c), c+1, c+1); 
      pCov2Red4Red_cent[i][c] = (TProfile*)pCov2Red4Red[i]->ProfileX(Form("%s_cent%i",pCov2Red4Red[i]->GetName(),c), c+1, c+1); 
    }
  }
  for (int i=8;i<npid;i++)
  {
    for (int c = 0; c < ncent; c++)
    {
      pReducedCorrelator2EtaGap_cent[i][c] = (TProfile*)  pReducedCorrelator2EtaGap_cent[i-8][c] -> Clone();
      pReducedCorrelator2_cent[i][c] = (TProfile*)  pReducedCorrelator2_cent[i-8][c] -> Clone();
      pReducedCorrelator4_cent[i][c] = (TProfile*)  pReducedCorrelator4_cent[i-8][c] -> Clone();
      pCov22RedEtaGap_cent[i][c] = (TProfile*)  pCov22RedEtaGap_cent[i-8][c] -> Clone();
      pCov22Red_cent[i][c] = (TProfile*)  pCov22Red_cent[i-8][c] -> Clone();
      pCov24Red_cent[i][c] = (TProfile*)  pCov24Red_cent[i-8][c] -> Clone();
      pCov42Red_cent[i][c] = (TProfile*)  pCov42Red_cent[i-8][c] -> Clone();
      pCov44Red_cent[i][c] = (TProfile*)  pCov44Red_cent[i-8][c] -> Clone();
      pCov2Red4Red_cent[i][c] = (TProfile*)  pCov2Red4Red_cent[i-8][c] -> Clone();

      pReducedCorrelator2EtaGap_cent[i][c] -> Add(pReducedCorrelator2EtaGap_cent[i-4][c]);
      pReducedCorrelator2_cent[i][c] -> Add(pReducedCorrelator2_cent[i-4][c]);
      pReducedCorrelator4_cent[i][c] -> Add(pReducedCorrelator4_cent[i-4][c]);
      pCov22RedEtaGap_cent[i][c] -> Add(pCov22RedEtaGap_cent[i-4][c]);
      pCov22Red_cent[i][c] -> Add(pCov22Red_cent[i-4][c]);
      pCov24Red_cent[i][c] -> Add(pCov24Red_cent[i-4][c]);
      pCov42Red_cent[i][c] -> Add(pCov42Red_cent[i-4][c]);
      pCov44Red_cent[i][c] -> Add(pCov44Red_cent[i-4][c]);
      pCov2Red4Red_cent[i][c] -> Add(pCov2Red4Red_cent[i-4][c]);
    }
  }
  // OUTPUT
  TGraphErrors *grDifFl[nmethod][ncent][npid];    // v2(pt)
  
  // Filling pT bin
  double pt[npt];
  double ept[npt]={0}; // error bin pT = 0.0
  for (int ipt=0; ipt<npt; ipt++){
    pt[ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
  }
  
  double v2Dif[nmethod][ncent][npid][npt], v2eDif[nmethod][ncent][npid][npt];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(pCorrelator2,icent);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(pCorrelator4,icent);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4,icent,icent,icent);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    // 2QC Gapped
    term cor2Gap = term(pCorrelator2EtaGap,icent);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    for (int id=0;id<npid;id++){ // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin

        // v22
        term cor2red = term(pReducedCorrelator2_cent[id][icent],ipt);
        double v22Dif = cor2red.mVal/v22;
        // if (id==8 && icent==3) cout << v22Dif <<" ";
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
        // if (id==8 && icent==3) cout << v24Dif <<" ";
        // if (id==8 && icent==3) cout << ev24Dif <<" ";
        // v22 Gapped
        term cor2redGap = term(pReducedCorrelator2EtaGap_cent[id][icent],ipt);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(pCov22RedEtaGap_cent[id][icent],pCorrelator2EtaGap,pReducedCorrelator2EtaGap_cent[id][icent],ipt,icent,ipt);
        double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                            + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
        v2Dif[2][icent][id][ipt] = v22DifGap;
        v2eDif[2][icent][id][ipt] = ev22DifGap;
        // if (id==8 && icent==3) cout << v22DifGap <<" ";
        // if (id==8 && icent==3) cout << ev22DifGap <<" ";
      } // end of loop for all pT bin
      for (int i=0; i<nmethod; i++){
        grDifFl[i][icent][id] = new TGraphErrors(npt,pt,v2Dif[i][icent][id],ept,v2eDif[i][icent][id]);
        grDifFl[i][icent][id] -> SetMarkerStyle(marker[i]);
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }
    } // end of loop over PID
  } // end of loop over centrality classes
  // cout << endl;
  const char *grTitleDF[nmethod]={"v_{3}{2};p_{T} [GeV/c];v_{3}",
                                  "v_{3}{4};p_{T} [GeV/c];v_{3}",
                                  "v_{3}{2,#eta-gap};p_{T} [GeV/c];v_{3}"};
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent;icent++){
        grDifFl[imeth][icent][id] -> SetTitle(grTitleDF[imeth]);
      }
    }
  }


  //==========================================================================================================================
  TGraphErrors *grIntFlPID[nmethod][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  TGraphErrors *grRefFl[nmethod];
  // v2 vs centrality for PID
  TProfile *pReducedCorrelator2EtaGap_PID[npid];
  TProfile *pReducedCorrelator2_PID[npid];
  TProfile *pReducedCorrelator4_PID[npid];
  TProfile *pCov22RedEtaGap_PID[npid];
  TProfile *pCov22Red_PID[npid];
  TProfile *pCov24Red_PID[npid];
  TProfile *pCov42Red_PID[npid];
  TProfile *pCov44Red_PID[npid];
  TProfile *pCov2Red4Red_PID[npid];
  for (int i = 0; i < npid-4; i++)
  {
    pReducedCorrelator2EtaGap_PID[i] = (TProfile*)pReducedCorrelator2EtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator2EtaGap[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pReducedCorrelator2_PID[i] = (TProfile*)pReducedCorrelator2[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator2[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pReducedCorrelator4_PID[i] = (TProfile*)pReducedCorrelator4[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pReducedCorrelator4[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov22RedEtaGap_PID[i] = (TProfile*)pCov22RedEtaGap[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov22RedEtaGap[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov22Red_PID[i] = (TProfile*)pCov22Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov22Red[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov24Red_PID[i] = (TProfile*)pCov24Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov24Red[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pCov42Red_PID[i] = (TProfile*)pCov42Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov42Red[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
    pCov44Red_PID[i] = (TProfile*)pCov44Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov44Red[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP);
    pCov2Red4Red_PID[i] = (TProfile*)pCov2Red4Red[i]->ProfileY(Form("%s_ptcut_%1.1f_%1.1f.",pCov2Red4Red[i]->GetName(),bin_pT[binMinPtRFP], bin_pT[binMaxPtRFP]), binMinPtRFP+1, binMaxPtRFP); 
  }
  for (int i=8;i<npid;i++)
  {
    pReducedCorrelator2EtaGap_PID[i] = (TProfile*)  pReducedCorrelator2EtaGap_PID[i-8] -> Clone();
    pReducedCorrelator2_PID[i] = (TProfile*)  pReducedCorrelator2_PID[i-8] -> Clone();
    pReducedCorrelator4_PID[i] = (TProfile*)  pReducedCorrelator4_PID[i-8] -> Clone();
    pCov22RedEtaGap_PID[i] = (TProfile*)  pCov22RedEtaGap_PID[i-8] -> Clone();
    pCov22Red_PID[i] = (TProfile*)  pCov22Red_PID[i-8] -> Clone();
    pCov24Red_PID[i] = (TProfile*)  pCov24Red_PID[i-8] -> Clone();
    pCov42Red_PID[i] = (TProfile*)  pCov42Red_PID[i-8] -> Clone();
    pCov44Red_PID[i] = (TProfile*)  pCov44Red_PID[i-8] -> Clone();
    pCov2Red4Red_PID[i] = (TProfile*)  pCov2Red4Red_PID[i-8] -> Clone();

    pReducedCorrelator2EtaGap_PID[i] -> Add(pReducedCorrelator2EtaGap_PID[i-4]);
    pReducedCorrelator2_PID[i] -> Add(pReducedCorrelator2_PID[i-4]);
    pReducedCorrelator4_PID[i] -> Add(pReducedCorrelator4_PID[i-4]);
    pCov22RedEtaGap_PID[i] -> Add(pCov22RedEtaGap_PID[i-4]);
    pCov22Red_PID[i] -> Add(pCov22Red_PID[i-4]);
    pCov24Red_PID[i] -> Add(pCov24Red_PID[i-4]);
    pCov42Red_PID[i] -> Add(pCov42Red_PID[i-4]);
    pCov44Red_PID[i] -> Add(pCov44Red_PID[i-4]);
    pCov2Red4Red_PID[i] -> Add(pCov2Red4Red_PID[i-4]);
  }
  
  double v2[nmethod][npid][ncent], v2e[nmethod][npid][ncent];
  double v2_RF[nmethod][ncent],    v2e_RF[nmethod][ncent];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // 2QC
    term cor2 = term(pCorrelator2,icent);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    v2_RF[0][icent] = v22;
    v2e_RF[0][icent] = ev22;

    // 4QC
    term cor4 = term(pCorrelator4,icent);
    double cov24 = Covariance(pCov24,pCorrelator2,pCorrelator4,icent,icent,icent);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    v2_RF[1][icent] = v24;
    v2e_RF[1][icent] = ev24;
    // 2QC Gapped
    term cor2Gap = term(pCorrelator2EtaGap,icent);
    double v22Gap = sqrt(cor2Gap.mVal);
    double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
    v2_RF[2][icent] = v22Gap;
    v2e_RF[2][icent] = ev22Gap;
    for (int id=0;id<npid;id++){
      // v22
      term cor2red = term(pReducedCorrelator2_PID[id],icent);
      double v22Dif = cor2red.mVal/v22;
      double cov22prime = Covariance(pCov22Red_PID[id],pCorrelator2,pReducedCorrelator2_PID[id],icent,icent,icent);
      double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                          + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
      v2[0][id][icent] = v22Dif;
      v2e[0][id][icent] = ev22Dif;
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
      v2[1][id][icent] = v24Dif;
      v2e[1][id][icent] = ev24Dif;
      // v22 Gapped
        term cor2redGap = term(pReducedCorrelator2EtaGap_PID[id],icent);
        double v22DifGap = cor2redGap.mVal/v22Gap;
        double cov22primeGap = Covariance(pCov22RedEtaGap_PID[id],pCorrelator2EtaGap,pReducedCorrelator2EtaGap_PID[id],icent,icent,icent);
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
    // grRefFl[imeth] -> RemovePoint(0);
    for (int id=0; id<npid; id++){
      grIntFlPID[imeth][id] = new TGraphErrors(ncent,bin_cent,v2[imeth][id],bin_centE,v2e[imeth][id]);
      grIntFlPID[imeth][id] -> SetMarkerStyle(marker[imeth]);
      grIntFlPID[imeth][id] -> SetMarkerSize(1.5);
    }
  }
  const char *grTitleRF[nmethod]={"v_{3}{2};centrality (%);v_{3}",
                                  "v_{3}{4};centrality (%);v_{3}",
                                  "v_{3}{2,#eta-gap};centrality (%);v_{3}"};
  for (int imeth=0; imeth<nmethod; imeth++){

    for (int id=0;id<npid;id++){
      if (id==8) continue;
      grIntFlPID[imeth][id] -> SetTitle(grTitleRF[imeth]);
    }
  
  }

  inFile->Close();
  return grDifFl[METHOD][CENT][ID];
  // return grRefFl[2];
  
}
