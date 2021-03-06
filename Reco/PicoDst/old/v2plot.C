#include "DrawTGraph.C"

TFile *outFile = new TFile("../CompareResult/Vinh.root","recreate");

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

// static const double maxpt = 3.0; // max pt
// static const double minpt = 0.1; // min pt
// static const int npt = 8; // 0.5 - 3.6 GeV/c - number of pT bins
// static const double bin_pT[npt+1]={0.1, 0.3, 0.6, 0.9, 1.2, 1.5, 1.9, 2.4, 3.};

static const int npt = 7; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_pT[npt+1]={0.1, 0.3, 0.6, 0.9, 1.2, 1.5, 1.9, 2.5};
static const double maxpt = 2.5; // max pt
static const double minpt = 0.1; // min pt


static const int ncent = 8; // 0-80 %
static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
static const double bin_centE[ncent] = {0};

TProfile *v22int[ncent], *v24int[ncent];
TProfile *v22dif[npt], *v24dif[npt], *v2EPdif[npt], *pt1040[npt];

void v2plot_differential_flow(){
  TFile *inFile = new TFile("../ROOTFile/sum.root","read");

  bool bDrawPlots1040 = 0;
  bool drawDistributions = 0;
  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile
  // char analysis[20]={"pure"};

  
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
  TProfile *hv2EP[ncent][npt];	  // elliptic flow from EP method
  TProfile *hv22EP[ncent];        // elliptic flow cent: 10-80% from EP method
  TProfile *HRes[ncent];
  // OUTPUT
  TGraphErrors *grDifFl[3][ncent];    // v2(pt); 4 = {MC, 2QC, 4QC, EP}
  TGraphErrors *grRefFl[ncent];       //
  TGraphErrors *grDifFl1040[3];
  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv22EP_%i",icent);
    hv22EP[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"HRes_%i",icent);
    HRes[icent] = (TProfile*)inFile->Get(hname);
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
  if (bDrawPlots1040){
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
  for (int ipt=0;ipt<npt;ipt++){
    sprintf(hname,"v22dif_%i",ipt);
    v22dif[ipt]=new TProfile(hname,hname,1,0.,1.);
    sprintf(hname,"v24dif_%i",ipt);
    v24dif[ipt]=new TProfile(hname,hname,1,0.,1.);
    sprintf(hname,"v2EPdif_%i",ipt);
    v2EPdif[ipt]=new TProfile(hname,hname,1,0.,1.);
    sprintf(hname,"pt1040_%i",ipt);
    pt1040[ipt]=new TProfile(hname,hname,1,0.,1.);
  }
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"v22int_%i",icent);
    v22int[icent]=new TProfile(hname,hname,1,0.,1.);
    v22int[icent] -> Sumw2();
    sprintf(hname,"v24int_%i",icent);
    v24int[icent]=new TProfile(hname,hname,1,0.,1.);
    v24int[icent] -> Sumw2();

    double v2[3], ev2[3];
    double x[3]={0.5,1.5,2.5};
    double ex[3]={0};
    vector <double> vV2EPDif, vV22Dif, vV24Dif, vPt;
    vector <double> eV2EPDif, eV22Dif, eV24Dif, ePt;
    double v2EP = hv22EP[icent]->GetBinContent(1)/sqrt(HRes[icent]->GetBinContent(1));
    double ev2EP = hv22EP[icent]->GetBinError(1)/sqrt(HRes[icent]->GetBinContent(1));
    // 2QC
    term cor2 = term(hv22[icent]);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    for (int i=0;i<3;i++){
      v2[0] = v22; ev2[0] = ev22;
      v2[1] = v24; ev2[1] = ev24;
      v2[2] = v2EP;   ev2[2] = ev2EP;
    }
    grRefFl[icent] = new TGraphErrors(3,x,v2,ex,ev2);
    grRefFl[icent]->SetMarkerColor(kRed);
    grRefFl[icent]->SetMarkerStyle(20);
    grRefFl[icent]->SetMarkerSize(1.5);
    grRefFl[icent]->SetDrawOption("P");

    // Differential flow calculation
    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      vPt.push_back(hPT[icent][ipt] -> GetBinContent(1));
      ePt.push_back(0);
      // v2EP
      double res2 = sqrt(HRes[icent]->GetBinContent(1));
      double v2obs = hv2EP[icent][ipt]->GetBinContent(1);
      double v2EPDif = v2obs / res2;
      double ev2EP = hv2EP[icent][ipt]->GetBinError(1) / res2;
      vV2EPDif.push_back(v2EPDif);
      eV2EPDif.push_back(ev2EP);
      
      // v22
      term cor2red = term(hv22pt[icent][ipt]);
      double v22Dif = cor2red.mVal/v22;
      double cov22prime = Covariance(hcov22prime[icent][ipt],hv22[icent],hv22pt[icent][ipt]);
      double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                          + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
      vV22Dif.push_back(v22Dif);
      eV22Dif.push_back(ev22Dif);
      
      // v24
      term cor4red = term(hv24pt[icent][ipt]);
      double cov24prime = Covariance(hcov24prime[icent][ipt],hv22[icent],hv24pt[icent][ipt]);
      double cov42prime = Covariance(hcov42prime[icent][ipt],hv24[icent],hv22pt[icent][ipt]);
      double cov44prime = Covariance(hcov44prime[icent][ipt],hv24[icent],hv24pt[icent][ipt]);
      double cov2prime4prime = Covariance(hcov2prime4prime[icent][ipt],hv22pt[icent][ipt],hv24pt[icent][ipt]);
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
      vV24Dif.push_back(v24Dif);
      eV24Dif.push_back(ev24Dif);
      v22int[icent] -> Fill(0.5,v22Dif,hPT[icent][ipt] -> GetBinEntries(1));
      v24int[icent] -> Fill(0.5,v24Dif,hPT[icent][ipt] -> GetBinEntries(1));
      if (icent>=1 && icent <=3) {
        v2EPdif[ipt]->Fill(0.5,v2EPDif,hPT[icent][ipt] -> GetBinEntries(1));
        v22dif[ipt]->Fill(0.5,v22Dif,hPT[icent][ipt] -> GetBinEntries(1));
        v24dif[ipt]->Fill(0.5,v24Dif,hPT[icent][ipt] -> GetBinEntries(1));
        pt1040[ipt]->Fill(0.5,hPT[icent][ipt] -> GetBinContent(1),hPT[icent][ipt] -> GetBinEntries(1));
      }
      if (icent==1) cout << ev24Dif <<", ";
    } // end of loop for all pT bin
    cout << endl;
    // 2QC differential flow
    grDifFl[0][icent] = new TGraphErrors(npt,&vPt[0],&vV22Dif[0],&ePt[0],&eV22Dif[0]);
    grDifFl[0][icent] -> SetMarkerColor(kRed);
    grDifFl[0][icent] -> SetMarkerStyle(25);
    // 4QC differential flow
    grDifFl[1][icent] = new TGraphErrors(npt,&vPt[0],&vV24Dif[0],&ePt[0],&eV24Dif[0]);
    grDifFl[1][icent] -> SetMarkerColor(kGreen+1);
    grDifFl[1][icent] -> SetMarkerStyle(20);
    // EP differential flow
    grDifFl[2][icent] = new TGraphErrors(npt,&vPt[0],&vV2EPDif[0],&ePt[0],&eV2EPDif[0]);
    grDifFl[2][icent] -> SetMarkerColor(kAzure+2);
    grDifFl[2][icent] -> SetMarkerStyle(22);
    for (int i=0; i<3; i++){
      grDifFl[i][icent] -> SetMarkerSize(1.5);
      grDifFl[i][icent] -> SetDrawOption("P");
    }
  } // end of loop over centrality classes

  //==========================================================================================================================
  
  const char *grTitleDF[4]={"[1] v_{2}{2,QC};p_{T}, GeV/c;v_{2}","[2] v_{2}{4,QC};p_{T}, GeV/c;v_{2}","[3] v_{2}{#eta sub-event};p_{T}, GeV/c;v_{2}","v_{2}{MC};p_{T}, GeV/c;v_{2}"};
  
  outFile -> cd();

  for (int i=0; i<3; i++){
    for (int icent=0;icent<ncent;icent++){
      sprintf(hname,"gr_cent%i_%i",icent,i);
      grDifFl[i][icent] -> SetTitle(grTitleDF[i]);
      grDifFl[i][icent] -> Write(hname);
    }
  }

  if (!bDrawPlots1040) {
    std::vector<TGraphErrors*> vgrv2pt[6];
    for (int icent=0; icent<6; icent++){
      for (int i=0; i<3; i++){
        vgrv2pt[icent].push_back(grDifFl[i][icent]);
      }  
    }
    TCanvas *cV2PT[6];
    for (int icent=0; icent<6; icent++){
    
      sprintf(hname,"Centrality %i-%i%%",icent*10,(icent+1)*10);
      cV2PT[icent] = (TCanvas*) DrawTGraph(vgrv2pt[icent],"",0.77, 1.23, 0., maxpt, -0.01, 0.2, 0.18, 0.56, 0.5, 0.8, hname);
      cV2PT[icent] -> SetName(hname);
      sprintf(hname,"../Graphics/DFCent%i-%i.png",icent*10,(icent+1)*10);
      cV2PT[icent] -> SaveAs(hname);
    }
    vector <double> vV22Dif1040, vV24Dif1040, vV2EPDif1040, vPT;
    vector <double> ePT;
    for (int ipt=0;ipt<npt;ipt++){
      vV22Dif1040.push_back(v22dif[ipt]->GetBinContent(1));
      vV24Dif1040.push_back(v24dif[ipt]->GetBinContent(1));
      vV2EPDif1040.push_back(v2EPdif[ipt]->GetBinContent(1));
      // cout << v2EPdif[ipt]->GetBinContent(1)<< " ";
      vPT.push_back(pt1040[ipt]->GetBinContent(1));
      ePT.push_back(0);
    }
    // cout << endl;
    double eV22Dif1040[npt]={0.000172404, 0.000181321, 0.000267834, 0.000408164, 0.000656159, 0.000979545, 0.00157977};
    double eV24Dif1040[npt]={0.00236593, 0.0027449, 0.00404271, 0.00612153, 0.00876516, 0.012711, 0.0193739};
    double eV2EPDif1040[npt]={0.00015175, 0.000149594, 0.000225381, 0.000343574, 0.000543087, 0.00081989, 0.00142446};
    grDifFl1040[0] = new TGraphErrors(npt,&vPT[0],&vV22Dif1040[0],&ePT[0],&eV22Dif1040[0]);
    grDifFl1040[0] -> SetMarkerColor(kRed);
    grDifFl1040[0] -> SetMarkerStyle(25);
    // 4QC differential flow
    grDifFl1040[1] = new TGraphErrors(npt,&vPT[0],&vV24Dif1040[0],&ePT[0],&eV24Dif1040[0]);
    grDifFl1040[1] -> SetMarkerColor(kGreen+1);
    grDifFl1040[1] -> SetMarkerStyle(20);
    // EP differential flow
    grDifFl1040[2] = new TGraphErrors(npt,&vPT[0],&vV2EPDif1040[0],&ePT[0],&eV2EPDif1040[0]);
    grDifFl1040[2] -> SetMarkerColor(kAzure+2);
    grDifFl1040[2] -> SetMarkerStyle(22);
    for (int i=0; i<3; i++){
      grDifFl1040[i] -> SetMarkerSize(1.5);
      grDifFl1040[i] -> SetDrawOption("P");
      grDifFl1040[i] -> SetLineWidth(1.);
    }

    std::vector<TGraphErrors*> vgrv2pt1040;
    for (int i=0; i<3; i++){
      grDifFl1040[i] -> SetTitle(grTitleDF[i]);
      vgrv2pt1040.push_back(grDifFl1040[i]);

      sprintf(hname,"gr_cent10-40_%i",i);
      grDifFl1040[i] -> Write(hname);
    }
    
    TCanvas *cV2PT1040;
    // cV2PT[0] = (TCanvas*) DrawTGraph(vgrv2pt[0],"",0.65, 1.35, 0., maxpt, 0, 0.2, 0.18, 0.65, 0.5, 0.89, "Centrality 0-10%");
    // cV2PT[0] -> SetName("Cent10-40");
    // cV2PT[0] -> SaveAs("../Graphics/DFCent0-10.png");

    cV2PT1040 = (TCanvas*) DrawTGraph(vgrv2pt1040,"",0.77,1.23,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,"Centrality 10-40%");
    cV2PT1040 -> SetName("Cent10-40");
    cV2PT1040 -> SaveAs("../Graphics/DFCent10-40.png");


    return;
  }


  //=============================================
  std::vector<TGraphErrors*> vgrv2pt[2];
  for (int icent=0; icent<2; icent++){
    for (int i=0; i<3; i++){
      vgrv2pt[icent].push_back(grDifFl[i][icent]);
    }
  }
  TCanvas *cV2PT;
  // cV2PT[0] = (TCanvas*) DrawTGraph(vgrv2pt[0],"",0.65, 1.35, 0., maxpt, 0, 0.2, 0.18, 0.65, 0.5, 0.89, "Centrality 0-10%");
  // cV2PT[0] -> SetName("Cent10-40");
  // cV2PT[0] -> SaveAs("../Graphics/DFCent0-10.png");

  cV2PT = (TCanvas*) DrawTGraph(vgrv2pt[1],"",0.77,1.23,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,"Centrality 10-40%");
  cV2PT -> SetName("Cent10-40");
  cV2PT -> SaveAs("../Graphics/DFCent10-40.png");


  double ymin = 0.01;
  double ymax = 0.05;
  TCanvas *c1040 = new TCanvas("c1040","c1040",200,10,550,550);
  TH2F *h1040 = new TH2F("h1040","Reference flow, 10-40% centrality",3,0,3,10,ymin,ymax);
  h1040 = new TH2F("","",3,0,3,10,ymin,ymax);
  h1040->SetYTitle("v_{2}");
  h1040->SetCanExtend(TH1::kAllAxes);
  TAxis* a = h1040 -> GetXaxis();
  const char *ch[3]  = {"v_{2}{2,QC}","v_{2}{4,QC}","v_{2}{#eta-sub,EP}"};
  for (int j=0; j<3; j++) h1040->Fill(ch[j],(ymin+ymax)/2.,1);
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
  ptext1->AddText("UrQMD, GEANT, Au+Au, #sqrt{s_{NN}}=7.7 GeV");
  ptext1->AddText("10-40% centrality");
  ptext1->Draw();
  c1040 -> SaveAs("../Graphics/RFCent10-40.png");

}

void v2plot_integrated_flow(){
  char hname[400];
  TFile *inFile = new TFile("../ROOTFile/sum.root","read");
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

  std::vector<double> vV2EP, vV22, vV24, vV22int, vV24int;
  std::vector<double> eV2EP, eV22, eV24;

  for (int icent=0;icent<ncent;icent++){

    // EP
    vV2EP.push_back( hv22EP[icent]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
    eV2EP.push_back( hv22EP[icent]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
    // vV2EP.push_back( hv22EP[icent]->GetBinContent(1));
    // eV2EP.push_back( hv22EP[icent]->GetBinError(1)  );    
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
 
    vV22int.push_back(v22int[icent]->GetBinContent(1));
    vV24int.push_back(v24int[icent]->GetBinContent(1));
  }
  TGraphErrors *grIntFlowVsCent[3];       // v2(cent); 4 = {2QC, 4QC, EP, MC}
  // grIntFlowVsCent[0] = new TGraphErrors(ncent,bin_cent,&vV22[0],bin_centE,&eV22[0]);
  // grIntFlowVsCent[0] -> SetMarkerColor(kRed);
  // grIntFlowVsCent[0] -> SetMarkerStyle(25);  

  // grIntFlowVsCent[1] = new TGraphErrors(ncent,bin_cent,&vV24[0],bin_centE,&eV24[0]);
  // grIntFlowVsCent[1]->SetMarkerColor(kGreen+1);
  // grIntFlowVsCent[1]->SetMarkerStyle(20);

  grIntFlowVsCent[2] = new TGraphErrors(ncent,bin_cent,&vV2EP[0],bin_centE,&eV2EP[0]);
  grIntFlowVsCent[2] -> SetMarkerColor(kAzure+2);
  grIntFlowVsCent[2] -> SetMarkerStyle(22);

  grIntFlowVsCent[0] = new TGraphErrors(ncent,bin_cent,&vV22int[0],bin_centE,&eV22[0]);
  grIntFlowVsCent[0] -> SetMarkerColor(kRed);
  grIntFlowVsCent[0] -> SetMarkerStyle(25); 

  grIntFlowVsCent[1] = new TGraphErrors(ncent,bin_cent,&vV24int[0],bin_centE,&eV24[0]);
  grIntFlowVsCent[1]->SetMarkerColor(kGreen+1);
  grIntFlowVsCent[1]->SetMarkerStyle(20);

  for (int i=0;i<3;i++){
    grIntFlowVsCent[i]->SetMarkerSize(1.5);
    grIntFlowVsCent[i]->SetDrawOption("P");
  }
  // const char *grTitle[5]={"[1] v_{2}{2,QC};cent, %;v_{2}",
  //                         "[2] v_{2}{4,QC};cent, %;v_{2}",
  //                         "[3] v_{2}{#eta sub-event};cent, %;v_{2}",
  //                         "[4] v_{2}{2,QC fix};cent, %;v_{2}",
  //                         "[5] v_{2}{4,QC fix};cent, %;v_{2}"};
  const char *grTitle[3]={"[1] v_{2}{2,QC fix};cent, %;v_{2}",
                          "[2] v_{2}{4,QC fix};cent, %;v_{2}",
                          "[3] v_{2}{#eta sub-event};cent, %;v_{2}",};
  outFile -> cd();
  for (int i=0; i<3; i++){
    sprintf(hname,"grRF_%i",i);
    grIntFlowVsCent[i] -> SetTitle(grTitle[i]);
    grIntFlowVsCent[i] -> Write(hname);
  }


  std::vector<TGraphErrors*> vgr;
  for (int i=0; i<3; i++){
    vgr.push_back(grIntFlowVsCent[i]);
  }

  TCanvas *can;
  can = (TCanvas*) DrawTGraph(vgr,"",0.78,1.22,   0,60,-0.005,0.1,    0.18,0.56,0.5,0.8,""); // DCA<0.5: 0.88, 1.12 // wo DCA: 0.76, 1.03
  sprintf(hname,"v2 vs cent");
  can -> SetName(hname);
  sprintf(hname,"../Graphics/v2centratio.png");
  can -> SaveAs(hname);
}
void v2plot(){
  v2plot_differential_flow();
  v2plot_integrated_flow();
}