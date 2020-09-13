#include "DrawTGraph.C"

TFile *outFile = new TFile("../CompareResult/VinhPID_Reco_merged_ACS.root","recreate");
TString outDirName={"Reco_merged_ACS"};
bool bDrawPlots1040 = 0;
bool drawDistributions = 0;
bool bSaveCanvas = 0;
bool bMergeCharged = 1;
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

static const int npid = 8; // charged hadrons, pions, kaons, protons
static const int nmethod = 3; // 2QC, 4QC, EP

static const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
static const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};
static const double maxpt = 2.5; // max pt
static const double minpt = 0.2; // min pt

static const int ncent = 8; // 0-80 %
static const double bin_cent[ncent] = {5,15,25,35,45,55,65,75};
static const double bin_centE[ncent] = {0};

std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};

TProfile *prV22int[ncent][npid], *prV24int[ncent][npid], *prV2EPint[ncent][npid]; // TProfile for integrated flow 
TProfile *prV22dif1040[npt][npid], *prV24dif1040[npt][npid], *prV2EPdif1040[npt][npid], *pt1040[npt][npid]; // TProfile for differential flow of 10-40% centrality bin

void v2plot_differential_flow(){
  TFile *inFile = new TFile("../ROOTFile/PID_ACS.root","read");


  // Temporary variables
  char hname[800]; // histogram hname
  double stats[6]; // stats of TProfile
  // char analysis[20]={"pure"};

  if (drawDistributions){
    TCanvas *cTemp = new TCanvas("cTemp","cTemp",200,10,800,450);

    TH1I *hMult = (TH1I*)inFile->Get("hMult");
    hMult -> Draw();
    sprintf(hname,"../%s/mult.png",outDirName.Data());
    cTemp -> Draw();
    cTemp -> SaveAs(hname);

    TH1I *hEvt = (TH1I*)inFile->Get("hEvt");
    hEvt -> Draw();
    sprintf(hname,"../%s/evt.png",outDirName.Data());
    cTemp -> Draw();
    cTemp -> SaveAs(hname);

    TH1F *hEta = (TH1F*)inFile->Get("hEta");
    hEta -> Draw();
    sprintf(hname,"../%s/eta.png",outDirName.Data());
    cTemp -> SaveAs(hname);  

    TH1F *hPhi = (TH1F*)inFile->Get("hPhi");
    hPhi -> Draw();
    sprintf(hname,"../%s/phi.png",outDirName.Data());
    cTemp -> SaveAs(hname);

    TH1F *hPt = (TH1F*)inFile->Get("hPt");
    hPt -> Draw();
    sprintf(hname,"../%s/pt.png",outDirName.Data());
    cTemp -> SaveAs(hname);
  }

  // Input hist
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  TProfile *hPT[ncent][npt][npid];       // profile pt 
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  TProfile *hv2EP[ncent][npt][npid];	  // elliptic flow from EP method
  TProfile *HRes[ncent];
  // OUTPUT
  TGraphErrors *grDifFl[3][ncent][npid];    // v2(pt); 3 = {2QC, 4QC, EP}
  TGraphErrors *grDifFl1040[3][npid];
  
  // Get TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    HRes[icent] = (TProfile*)inFile->Get(Form("HRes_%i",icent));
    hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv2EP[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv2EP_%i_%i_%i",icent,ipt,id));
        hPT[icent][ipt][id]=(TProfile*)inFile->Get(Form("hPT_%i_%i_%i",icent,ipt,id));
        hv22pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

  //==========================================================================================================================
  if(bMergeCharged){
    for (int icent=0;icent<ncent;icent++){
      for (int ipt=0;ipt<npt;ipt++){
        for (int id=0;id<npid/2;id++){
          hv2EP[icent][ipt][id] -> Add(hv2EP[icent][ipt][id+4]);
          hPT[icent][ipt][id] -> Add(hPT[icent][ipt][id+4]);
          hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id+4]);
          hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id+4]);
          hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id+4]);
          hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id+4]);
          hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id+4]);
          hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id+4]);
          hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id+4]);
        }
      }
    }
  }
  if (bDrawPlots1040){
    // Add
    for (int icent=2; icent<4; icent++){ // loop over centrality classes
      HRes[1] -> Add(HRes[icent]);
      hv22[1] -> Add(hv22[icent]);
      hv24[1] -> Add(hv24[icent]);
      hcov24[1] -> Add(hcov24[icent]);
      for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
        for (int id=0;id<npid;id++){ // loop over pid
          hv2EP[1][ipt][id]-> Add(hv2EP[icent][ipt][id]);
          hPT[1][ipt][id]-> Add(hPT[icent][ipt][id]);
          hv22pt[1][ipt][id]-> Add(hv22pt[icent][ipt][id]);
          hv24pt[1][ipt][id]-> Add(hv24pt[icent][ipt][id]);
          hcov22prime[1][ipt][id]-> Add(hcov22prime[icent][ipt][id]);
          hcov24prime[1][ipt][id]-> Add(hcov24prime[icent][ipt][id]);
          hcov42prime[1][ipt][id]-> Add(hcov42prime[icent][ipt][id]);
          hcov44prime[1][ipt][id]-> Add(hcov44prime[icent][ipt][id]);
          hcov2prime4prime[1][ipt][id]-> Add(hcov2prime4prime[icent][ipt][id]);
        }
      } // end of loop over pt bin
    }
  }
  //==========================================================================================================================
  /*
  // Filling pT bin
  double pt[ncent][npt];
  double ept[ncent][npt]={{0}}; // error bin pT = 0.0
  for (int icent=0; icent<ncent; icent++){
    for (int ipt=0; ipt<npt; ipt++){
      // pt[icent][ipt] = hPT[icent][ipt] -> GetBinContent(1);
      pt[icent][ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
    }
  }
  */
  //==========================================================================================================================
  for (int ipt=0;ipt<npt;ipt++){
    for (int id=0;id<npid;id++){
      sprintf(hname,"prV22dif1040_%i_%i",ipt,id);
      prV22dif1040[ipt][id]=new TProfile(hname,hname,1,0.,1.);
      sprintf(hname,"prV24dif1040_%i_%i",ipt,id);
      prV24dif1040[ipt][id]=new TProfile(hname,hname,1,0.,1.);
      sprintf(hname,"prV2EPdif1040_%i_%i",ipt,id);
      prV2EPdif1040[ipt][id]=new TProfile(hname,hname,1,0.,1.);
      sprintf(hname,"pt1040_%i_%i",ipt,id);
      pt1040[ipt][id]=new TProfile(hname,hname,1,0.,1.);
    }
  }

  std::vector<TString> errVectorNames = {"double eV22Dif1040CHp[npt]=", "double eV22Dif1040Pionp[npt]=", "double eV22Dif1040Kaonp[npt]=", "double eV22Dif1040Protonp[npt]=", "double eV22Dif1040CHm[npt]=", "double eV22Dif1040Pionm[npt]=", "double eV22Dif1040Kaonm[npt]=", "double eV22Dif1040Protonm[npt]="};
  // std::vector<TString> errVectorNames = {"double eV24Dif1040CHp[npt]=", "double eV24Dif1040Pionp[npt]=", "double eV24Dif1040Kaonp[npt]=", "double eV24Dif1040Protonp[npt]=", "double eV24Dif1040CHm[npt]=", "double eV24Dif1040Pionm[npt]=", "double eV24Dif1040Kaonm[npt]=", "double eV24Dif1040Protonm[npt]="};
  // std::vector<TString> errVectorNames = {"double eV2EPDif1040CHp[npt]=", "double eV2EPDif1040Pionp[npt]=", "double eV2EPDif1040Kaonp[npt]=", "double eV2EPDif1040Protonp[npt]=", "double eV2EPDif1040CHm[npt]=", "double eV2EPDif1040Pionm[npt]=", "double eV2EPDif1040Kaonm[npt]=", "double eV2EPDif1040Protonm[npt]="};
  
  if (bMergeCharged){
    errVectorNames.clear();
    // errVectorNames = {"double eV22Dif1040CH[npt]=", "double eV22Dif1040Pion[npt]=", "double eV22Dif1040Kaon[npt]=", "double eV22Dif1040Proton[npt]=", "double eV22Dif1040CHm[npt]=", "double eV22Dif1040Pionm[npt]=", "double eV22Dif1040Kaonm[npt]=", "double eV22Dif1040Protonm[npt]="};
    // errVectorNames = {"double eV24Dif1040CH[npt]=", "double eV24Dif1040Pion[npt]=", "double eV24Dif1040Kaon[npt]=", "double eV24Dif1040Proton[npt]=", "double eV24Dif1040CHm[npt]=", "double eV24Dif1040Pionm[npt]=", "double eV24Dif1040Kaonm[npt]=", "double eV24Dif1040Protonm[npt]="};
    errVectorNames = {"double eV2EPDif1040CH[npt]=", "double eV2EPDif1040Pion[npt]=", "double eV2EPDif1040Kaon[npt]=", "double eV2EPDif1040Proton[npt]=", "double eV2EPDif1040CHm[npt]=", "double eV2EPDif1040Pionm[npt]=", "double eV2EPDif1040Kaonm[npt]=", "double eV2EPDif1040Protonm[npt]="};
  
  }
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // double v2EP = hv22EP[icent]->GetBinContent(1)/sqrt(HRes[icent]->GetBinContent(1));
    // double ev2EP = hv22EP[icent]->GetBinError(1)/sqrt(HRes[icent]->GetBinContent(1));
    // 2QC
    term cor2 = term(hv22[icent]);
    double v22 = sqrt(cor2.mVal);
    double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(hv24[icent]);
    double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
    double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
    for (int id=0;id<npid;id++){
      sprintf(hname,"prV22int_%i_%i",icent,id);
      prV22int[icent][id]=new TProfile(hname,hname,1,0.,1.);
      sprintf(hname,"prV24int_%i_%i",icent,id);
      prV24int[icent][id]=new TProfile(hname,hname,1,0.,1.);

      if (icent==1 && bDrawPlots1040) {
        // cout << "PID: "<< pidNames.at(id) << endl;
        cout << errVectorNames.at(id);
        cout <<"{";
      }
      vector <double> vV2EPDif, vV22Dif, vV24Dif, vPt;
      vector <double> eV2EPDif, eV22Dif, eV24Dif, ePt;
      // Differential flow calculation
      for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
        // vPt.push_back(hPT[icent][ipt][id] -> GetBinContent(1));
        vPt.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
        ePt.push_back(0);
        // v2EP
        double res2 = sqrt(HRes[icent]->GetBinContent(1));
        double v2obs = hv2EP[icent][ipt][id]->GetBinContent(1);
        double v2EPDif = v2obs / res2;
        // double v2EPDif = v2obs;
        double ev2EP = hv2EP[icent][ipt][id]->GetBinError(1) / res2;
        vV2EPDif.push_back(v2EPDif);
        eV2EPDif.push_back(ev2EP);
        
        // v22
        term cor2red = term(hv22pt[icent][ipt][id]);
        double v22Dif = cor2red.mVal/v22;
        double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
        double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
        vV22Dif.push_back(v22Dif);
        eV22Dif.push_back(ev22Dif);
        
        // v24
        term cor4red = term(hv24pt[icent][ipt][id]);
        double cov24prime = Covariance(hcov24prime[icent][ipt][id],hv22[icent],hv24pt[icent][ipt][id]);
        double cov42prime = Covariance(hcov42prime[icent][ipt][id],hv24[icent],hv22pt[icent][ipt][id]);
        double cov44prime = Covariance(hcov44prime[icent][ipt][id],hv24[icent],hv24pt[icent][ipt][id]);
        double cov2prime4prime = Covariance(hcov2prime4prime[icent][ipt][id],hv22pt[icent][ipt][id],hv24pt[icent][ipt][id]);
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
        prV22int[icent][id] -> Fill(0.5,v22Dif,hPT[icent][ipt][id] -> GetBinEntries(1));
        prV24int[icent][id] -> Fill(0.5,v24Dif,hPT[icent][ipt][id] -> GetBinEntries(1));
        if (icent>=1 && icent <=3) {
          prV2EPdif1040[ipt][id]->Fill(0.5,v2EPDif,hPT[icent][ipt][id] -> GetBinEntries(1));
          prV22dif1040[ipt][id]->Fill(0.5,v22Dif,hPT[icent][ipt][id] -> GetBinEntries(1));
          prV24dif1040[ipt][id]->Fill(0.5,v24Dif,hPT[icent][ipt][id] -> GetBinEntries(1));
          pt1040[ipt][id]->Fill(0.5,hPT[icent][ipt][id] -> GetBinContent(1),hPT[icent][ipt][id] -> GetBinEntries(1));
        }
        // if (icent==1 && bDrawPlots1040) cout << ev22Dif;
        // if (icent==1 && bDrawPlots1040) cout << ev24Dif;
        if (icent==1 && bDrawPlots1040) cout << ev2EP;
        if (icent==1 && bDrawPlots1040 && ipt != npt-1) cout <<",";
      } // end of loop for all pT bin
      if (icent==1 && bDrawPlots1040) cout <<"};"<< endl;
      // 2QC differential flow
      grDifFl[0][icent][id] = new TGraphErrors(npt,&vPt[0],&vV22Dif[0],&ePt[0],&eV22Dif[0]);
      grDifFl[0][icent][id] -> SetMarkerColor(kRed);
      grDifFl[0][icent][id] -> SetMarkerStyle(25);
      // 4QC differential flow
      grDifFl[1][icent][id] = new TGraphErrors(npt,&vPt[0],&vV24Dif[0],&ePt[0],&eV24Dif[0]);
      grDifFl[1][icent][id] -> SetMarkerColor(kGreen+1);
      grDifFl[1][icent][id] -> SetMarkerStyle(20);
      // EP differential flow
      grDifFl[2][icent][id] = new TGraphErrors(npt,&vPt[0],&vV2EPDif[0],&ePt[0],&eV2EPDif[0]);
      grDifFl[2][icent][id] -> SetMarkerColor(kAzure+2);
      grDifFl[2][icent][id] -> SetMarkerStyle(22);
      for (int i=0; i<3; i++){
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }
    } // end of loop over PID
  } // end of loop over centrality classes

  //==========================================================================================================================
  if (bDrawPlots1040) return;
  const char *grTitleDF[4]={"[1] v_{2}{2,QC};p_{T}, GeV/c;v_{2}","[2] v_{2}{4,QC};p_{T}, GeV/c;v_{2}","[3] v_{2}{#eta sub-event};p_{T}, GeV/c;v_{2}","v_{2}{MC};p_{T}, GeV/c;v_{2}"};
  
  outFile -> cd();
  for (int imethod=0; imethod<3; imethod++){
    for (int icent=0;icent<ncent;icent++){
      for (int id=0;id<npid;id++){
        grDifFl[imethod][icent][id] -> SetTitle(grTitleDF[imethod]);
        grDifFl[imethod][icent][id] -> Write(Form("gr_cent%i_%i_%i",icent,imethod,id));
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[ncent][npid];
  for (int icent=0; icent<ncent; icent++){
    for (int id=0;id<npid;id++){
      for (int i=0; i<3; i++){
        vgrv2pt[icent][id].push_back(grDifFl[i][icent][id]);
      }
    }
  }
  TCanvas *cV2PT[ncent][npid];
  for (int icent=0; icent<6; icent++){
    for (int id=0;id<npid;id++){
      if (bMergeCharged && id>3) continue;
      sprintf(hname,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
      cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",0.77, 1.23, 0., maxpt, -0.01, 0.2, 0.18, 0.56, 0.5, 0.8, hname);
      cV2PT[icent][id] -> SetName(hname);
      sprintf(hname,"../%s/%sDFCent%i-%i.png",outDirName.Data(),pidNames.at(id).Data(),icent*10,(icent+1)*10);
      cV2PT[icent][id] -> SaveAs(hname);
    }
  }

  double eV22Dif1040CHp[npt]={0.000284795,0.000343314,0.000424882,0.000536291,0.000700513,0.000822093,0.00128172,0.00172503,0.00527953};
  double eV22Dif1040Pionp[npt]={0.000309189,0.000434458,0.000658201,0.000984849,0.00140232,0.00176958,0.00298576,0.00447632,0.0158138};
  double eV22Dif1040Kaonp[npt]={0.00128089,0.00114552,0.00131394,0.00164775,0.00215593,0.00261805,0.00437701,0.00657983,0.0238803};
  double eV22Dif1040Protonp[npt]={0.000969744,0.000680618,0.000629249,0.000690441,0.000837971,0.000940906,0.0014125,0.0018708,0.00572755};
  double eV22Dif1040CHm[npt]={0.000292025,0.000403375,0.000602087,0.000899312,0.00128357,0.00161285,0.00269534,0.00403247,0.0143444};
  double eV22Dif1040Pionm[npt]={0.000295929,0.000416012,0.000630731,0.000948255,0.00135466,0.00170914,0.00287847,0.00432067,0.0154218};
  double eV22Dif1040Kaonm[npt]={0.00175301,0.00159707,0.00189932,0.00249853,0.0034384,0.00434513,0.00754273,0.0115944,0.0405028};
  double eV22Dif1040Protonm[npt]={0.0159032,0.00969228,0.00798111,0.00813049,0.00960957,0.0109534,0.0185254,0.0279018,0.0549318};

  double eV24Dif1040CHp[npt]={0.0038566,0.00455999,0.00568421,0.00743603,0.00944111,0.0109492,0.0159435,0.0213047,0.060701};
  double eV24Dif1040Pionp[npt]={0.00418971,0.00577807,0.00871217,0.0125798,0.0173322,0.0214279,0.0353812,0.0526449,0.183447};
  double eV24Dif1040Kaonp[npt]={0.0155753,0.014063,0.0158551,0.0199517,0.0257908,0.0311569,0.0510409,0.0757213,0.268599};
  double eV24Dif1040Protonp[npt]={0.0119719,0.00847551,0.00794035,0.00915268,0.0109667,0.0123458,0.0173411,0.0227749,0.0655787};
  double eV24Dif1040CHm[npt]={0.00393232,0.00550686,0.00780567,0.0114134,0.0159587,0.0195133,0.0319473,0.0476235,0.166862};
  double eV24Dif1040Pionm[npt]={0.00398465,0.00564314,0.0081248,0.0120754,0.016832,0.0206969,0.0343871,0.0511972,0.180905};
  double eV24Dif1040Kaonm[npt]={0.0212522,0.019352,0.0226186,0.0290804,0.0390949,0.0498657,0.0829334,0.125843,0.429726};
  double eV24Dif1040Protonm[npt]={0.217224,0.126833,0.0994648,0.101401,0.116998,0.12702,0.21438,0.335478,0.396688};

  double eV2EPDif1040CHp[npt]={0.000233848,0.000278236,0.000340489,0.000423025,0.000543829,0.000633678,0.00103177,0.00146503,0.00502191};
  double eV2EPDif1040Pionp[npt]={0.000252506,0.000346265,0.000514895,0.000773006,0.00115201,0.0015144,0.00273493,0.00421362,0.0151611};
  double eV2EPDif1040Kaonp[npt]={0.00104426,0.000920251,0.00107444,0.00139775,0.00191265,0.00237852,0.00414045,0.00629583,0.0227473};
  double eV2EPDif1040Protonp[npt]={0.000770194,0.000542589,0.000500764,0.0005421,0.000651721,0.000729796,0.00115675,0.00161297,0.00547429};
  double eV2EPDif1040CHm[npt]={0.000238195,0.000322293,0.000472727,0.000702461,0.00103934,0.00135971,0.00245025,0.00377798,0.0138248};
  double eV2EPDif1040Pionm[npt]={0.000241291,0.000332128,0.000494423,0.000742414,0.00110635,0.00145422,0.00262891,0.00405493,0.0147984};
  double eV2EPDif1040Kaonm[npt]={0.00150009,0.00134963,0.00165382,0.00226585,0.00322049,0.00412867,0.00733204,0.0112874,0.0420852};
  double eV2EPDif1040Protonm[npt]={0.0141952,0.00886018,0.00735405,0.0075635,0.00900402,0.010338,0.0174838,0.0267754,0.0995876};

double eV22Dif1040CH[npt]={0.000147395,0.000190843,0.000267835,0.000370511,0.000495379,0.000583849,0.00089873,0.00122104,0.00381526};
double eV22Dif1040Pion[npt]={0.000154448,0.000217461,0.000339504,0.00051773,0.000744598,0.000941296,0.0015915,0.00239205,0.00851476};
double eV22Dif1040Kaon[npt]={0.000807205,0.000727614,0.000840028,0.00106438,0.00140821,0.00172696,0.00291958,0.00439683,0.0137498};
double eV22Dif1040Proton[npt]={0.000751845,0.000529628,0.000485976,0.000528597,0.000637722,0.000712753,0.00107487,0.00142791,0.00439644};
  
double eV24Dif1040CH[npt]={0.00121723,0.00155052,0.00208748,0.00280425,0.00370882,0.00433051,0.00638905,0.00846593,0.0249101};
double eV24Dif1040Pion[npt]={0.00127336,0.00176324,0.00260286,0.00380112,0.00529319,0.00659956,0.0107575,0.0160294,0.057639};
double eV24Dif1040Kaon[npt]={0.0056829,0.00513308,0.00585185,0.00727854,0.00948257,0.0115267,0.0191994,0.0287673,0.085812};
double eV24Dif1040Proton[npt]={0.0054158,0.00386111,0.00355892,0.00388148,0.00468478,0.00519871,0.00757187,0.00984133,0.0283817};

double eV2EPDif1040CH[npt]={0.000179589,0.000226668,0.000297348,0.000389998,0.000518541,0.000618136,0.00102334,0.00147015,0.00508335};
double eV2EPDif1040Pion[npt]={0.000187744,0.000257964,0.000383819,0.000576227,0.00085873,0.00112886,0.00203899,0.0031429,0.0113904};
double eV2EPDif1040Kaon[npt]={0.000922293,0.000818273,0.000969741,0.00128017,0.00176998,0.00221904,0.00388065,0.00591852,0.0216215};
double eV2EPDif1040Proton[npt]={0.000827639,0.000582899,0.000537681,0.000581938,0.000699489,0.000783411,0.00124228,0.00173319,0.00588726};

  double eV22Dif1040[npid][npt], eV24Dif1040[npid][npt], eV2EPDif1040[npid][npt];

  for (int ipt=0;ipt<npt;ipt++){
    eV22Dif1040[0][ipt] = eV22Dif1040CHp[ipt];
    eV22Dif1040[1][ipt] = eV22Dif1040Pionp[ipt];
    eV22Dif1040[2][ipt] = eV22Dif1040Kaonp[ipt];
    eV22Dif1040[3][ipt] = eV22Dif1040Protonp[ipt];
    eV22Dif1040[4][ipt] = eV22Dif1040CHm[ipt];
    eV22Dif1040[5][ipt] = eV22Dif1040Pionm[ipt];
    eV22Dif1040[6][ipt] = eV22Dif1040Kaonm[ipt];
    eV22Dif1040[7][ipt] = eV22Dif1040Protonm[ipt];    

    eV24Dif1040[0][ipt] = eV24Dif1040CHp[ipt];
    eV24Dif1040[1][ipt] = eV24Dif1040Pionp[ipt];
    eV24Dif1040[2][ipt] = eV24Dif1040Kaonp[ipt];
    eV24Dif1040[3][ipt] = eV24Dif1040Protonp[ipt];
    eV24Dif1040[4][ipt] = eV24Dif1040CHm[ipt];
    eV24Dif1040[5][ipt] = eV24Dif1040Pionm[ipt];
    eV24Dif1040[6][ipt] = eV24Dif1040Kaonm[ipt];
    eV24Dif1040[7][ipt] = eV24Dif1040Protonm[ipt];    

    eV2EPDif1040[0][ipt] = eV2EPDif1040CHp[ipt];
    eV2EPDif1040[1][ipt] = eV2EPDif1040Pionp[ipt];
    eV2EPDif1040[2][ipt] = eV2EPDif1040Kaonp[ipt];
    eV2EPDif1040[3][ipt] = eV2EPDif1040Protonp[ipt];
    eV2EPDif1040[4][ipt] = eV2EPDif1040CHm[ipt];
    eV2EPDif1040[5][ipt] = eV2EPDif1040Pionm[ipt];
    eV2EPDif1040[6][ipt] = eV2EPDif1040Kaonm[ipt];
    eV2EPDif1040[7][ipt] = eV2EPDif1040Protonm[ipt];
    if (bMergeCharged){
    eV22Dif1040[0][ipt] = eV22Dif1040CH[ipt];
    eV22Dif1040[1][ipt] = eV22Dif1040Pion[ipt];
    eV22Dif1040[2][ipt] = eV22Dif1040Kaon[ipt];
    eV22Dif1040[3][ipt] = eV22Dif1040Proton[ipt];
    eV24Dif1040[0][ipt] = eV24Dif1040CH[ipt];
    eV24Dif1040[1][ipt] = eV24Dif1040Pion[ipt];
    eV24Dif1040[2][ipt] = eV24Dif1040Kaon[ipt];
    eV24Dif1040[3][ipt] = eV24Dif1040Proton[ipt];
    eV2EPDif1040[0][ipt] = eV2EPDif1040CH[ipt];
    eV2EPDif1040[1][ipt] = eV2EPDif1040Pion[ipt];
    eV2EPDif1040[2][ipt] = eV2EPDif1040Kaon[ipt];
    eV2EPDif1040[3][ipt] = eV2EPDif1040Proton[ipt];
    }
  }
  double ePT[npt]={0.};
  TCanvas *cV2PT1040[npid];
  for (int id=0;id<npid;id++){
    if (bMergeCharged && id>3) continue;
    vector <double> vV22Dif1040, vV24Dif1040, vV2EPDif1040, vPT;
    for (int ipt=0;ipt<npt;ipt++){
      vV22Dif1040.push_back(prV22dif1040[ipt][id]->GetBinContent(1));
      vV24Dif1040.push_back(prV24dif1040[ipt][id]->GetBinContent(1));
      vV2EPDif1040.push_back(prV2EPdif1040[ipt][id]->GetBinContent(1));
      // vPT.push_back(pt1040[ipt][id]->GetBinContent(1));
      vPT.push_back((bin_pT[ipt]+bin_pT[ipt+1])/2.);
    }
    grDifFl1040[0][id] = new TGraphErrors(npt,&vPT[0],&vV22Dif1040[0],&ePT[0],eV22Dif1040[id]);
    grDifFl1040[0][id] -> SetMarkerColor(kRed);
    grDifFl1040[0][id] -> SetMarkerStyle(25);
    // 4QC differential flow
    grDifFl1040[1][id] = new TGraphErrors(npt,&vPT[0],&vV24Dif1040[0],&ePT[0],eV24Dif1040[id]);
    grDifFl1040[1][id] -> SetMarkerColor(kGreen+1);
    grDifFl1040[1][id] -> SetMarkerStyle(20);
    // EP differential flow
    grDifFl1040[2][id] = new TGraphErrors(npt,&vPT[0],&vV2EPDif1040[0],&ePT[0],eV2EPDif1040[id]);
    grDifFl1040[2][id] -> SetMarkerColor(kAzure+2);
    grDifFl1040[2][id] -> SetMarkerStyle(22);
    for (int i=0; i<3; i++){
      grDifFl1040[i][id] -> SetMarkerSize(1.5);
      grDifFl1040[i][id] -> SetDrawOption("P");
      grDifFl1040[i][id] -> SetLineWidth(1);
    }

    std::vector<TGraphErrors*> vgrv2pt1040;
    for (int imeth=0; imeth<3; imeth++){
      grDifFl1040[imeth][id] -> SetTitle(grTitleDF[imeth]);
      vgrv2pt1040.push_back(grDifFl1040[imeth][id]);
      grDifFl1040[imeth][id] -> Write(Form("gr_cent10-40_%i_%i",imeth,id));
    }
    
    
    sprintf(hname,"%s, centrality 10-40%%",pidFancyNames.at(id).Data());
    cV2PT1040[id] = (TCanvas*) DrawTGraph(vgrv2pt1040,"",0.67,1.33,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,hname);
    cV2PT1040[id] -> SetName(hname);
    cV2PT1040[id] -> SaveAs(Form("../%s/%sDFCent10-40.png",outDirName.Data(),pidNames.at(id).Data()));
  }
}

void v2plot_integrated_flow(){
  if (bDrawPlots1040) return;
  char hname[400];
  TFile *inFile = new TFile("../ROOTFile/PID_ACS.root","read");
  // Input histograms
  TProfile *hv22[ncent][npid];        // profile of integrated flow from v2{2}
  TProfile *hv24[ncent][npid];        // profile of integrated flow from v2{4}
  TProfile *hPT[ncent][npt][npid];       // profile pt 
  TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
  TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
  TProfile *hcov24[ncent][npid];       // <2>*<4>
  TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
  TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
  TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
  TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
  TProfile *hv2EP[ncent][npt][npid];	// elliptic flow from EP method
  TProfile *hv22EP[ncent][npid];      
  TProfile *HRes[ncent];
  // Get histograms
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // hv22EP[icent] = (TProfile*)inFile->Get(Form("hv22EP_%i",icent));
    HRes[icent] = (TProfile*)inFile->Get(Form("HRes_%i",icent));
    // hv22[icent] = (TProfile*)inFile->Get(Form("hv22_%i",icent));
    // hv24[icent] = (TProfile*)inFile->Get(Form("hv24_%i",icent));
    // hcov24[icent] = (TProfile*)inFile->Get(Form("hcov24_%i",icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv2EP[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv2EP_%i_%i_%i",icent,ipt,id));
        hPT[icent][ipt][id]=(TProfile*)inFile->Get(Form("hPT_%i_%i_%i",icent,ipt,id));
        hv22pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        // hcov22prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        // hcov24prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        // hcov42prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        // hcov44prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes
  // inFile -> Close();
  for (int icent=0;icent<ncent;icent++){
    for (int id=0;id<npid;id++){
      hv22EP[icent][id] = (TProfile*) hv2EP[icent][0][id]->Clone();
      hv22[icent][id] = (TProfile*) hv22pt[icent][0][id]->Clone();
      hv24[icent][id] = (TProfile*) hv24pt[icent][0][id]->Clone();
      hcov24[icent][id] = (TProfile*) hcov2prime4prime[icent][0][id]->Clone();
      for (int ipt=1;ipt<npt;ipt++){
        hv22EP[icent][id]->Add(hv2EP[icent][ipt][id]);
        hv22[icent][id]->Add(hv22pt[icent][ipt][id]);
        hv24[icent][id]->Add(hv24pt[icent][ipt][id]);
        hcov24[icent][id]->Add(hcov2prime4prime[icent][ipt][id]);
      }
    }
  }
  if (bMergeCharged){
    for (int icent=0;icent<ncent;icent++){
      for (int ipt=1;ipt<npt;ipt++){
        for (int id=0;id<npid/2;id++){
          hv22EP[icent][id]->Add(hv22EP[icent][id+4]);
          hv22[icent][id]->Add(hv22[icent][id+4]);
          hv24[icent][id]->Add(hv24[icent][id+4]);
          hcov24[icent][id]->Add(hcov24[icent][id+4]);
        }
      }
    }  
  }
  TGraphErrors *grIntFlowVsCent[nmethod][npid];
  TCanvas *can[npid];
  for (int id=0;id<npid;id++){
    if (bMergeCharged && id>3) continue;
    std::vector<double> vV2EP, vV22, vV24, vV22int, vV24int;
    std::vector<double> eV2EP, eV22, eV24, eV22int, eV24int;

    for (int icent=0;icent<ncent;icent++){

      // EP
      vV2EP.push_back( hv22EP[icent][id]->GetBinContent(1) / sqrt( HRes[icent]->GetBinContent(1) ) );
      eV2EP.push_back( hv22EP[icent][id]->GetBinError(1)   / sqrt( HRes[icent]->GetBinContent(1) ) );
      // vV2EP.push_back( hv22EP[icent]->GetBinContent(1));
      // eV2EP.push_back( hv22EP[icent]->GetBinError(1)  );    
      // 2QC
      term cor2 = term(hv22[icent][id]);
      vV22.push_back(sqrt(cor2.mVal)); // not in used
      eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
      // 4QC
      term cor4 = term(hv24[icent][id]);
      double cov24 = Covariance(hcov24[icent][id],hv22[icent][id],hv24[icent][id]);
      double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
      vV24.push_back(v24); // not in used
      eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );
  
      vV22int.push_back(prV22int[icent][id]->GetBinContent(1));
      vV24int.push_back(prV24int[icent][id]->GetBinContent(1));
      eV22int.push_back(prV22int[icent][id]->GetBinError(1)); // not in used
      eV24int.push_back(prV24int[icent][id]->GetBinError(1)); // not in used
    }
    
    // grIntFlowVsCent[0][id] = new TGraphErrors(ncent,bin_cent,&vV22[0],bin_centE,&eV22[0]);
    // grIntFlowVsCent[0][id] -> SetMarkerColor(kRed);
    // grIntFlowVsCent[0][id] -> SetMarkerStyle(25);  

    // grIntFlowVsCent[1][id] = new TGraphErrors(ncent,bin_cent,&vV24[0],bin_centE,&eV24[0]);
    // grIntFlowVsCent[1][id]->SetMarkerColor(kGreen+1);
    // grIntFlowVsCent[1][id]->SetMarkerStyle(20);

    grIntFlowVsCent[2][id] = new TGraphErrors(ncent,bin_cent,&vV2EP[0],bin_centE,&eV2EP[0]);
    grIntFlowVsCent[2][id] -> SetMarkerColor(kAzure+2);
    grIntFlowVsCent[2][id] -> SetMarkerStyle(22);

    grIntFlowVsCent[0][id] = new TGraphErrors(ncent,bin_cent,&vV22int[0],bin_centE,&eV22[0]);
    grIntFlowVsCent[0][id] -> SetMarkerColor(kRed);
    grIntFlowVsCent[0][id] -> SetMarkerStyle(25); 

    grIntFlowVsCent[1][id] = new TGraphErrors(ncent,bin_cent,&vV24int[0],bin_centE,&eV24[0]);
    grIntFlowVsCent[1][id] -> SetMarkerColor(kGreen+1);
    grIntFlowVsCent[1][id] -> SetMarkerStyle(20);

    for (int i=0;i<nmethod;i++){
      grIntFlowVsCent[i][id] -> SetMarkerSize(1.5);
      grIntFlowVsCent[i][id] -> SetDrawOption("P");
    }
    const char *grTitle[3]={"[1] v_{2}{2,QC};cent, %;v_{2}",
                            "[2] v_{2}{4,QC};cent, %;v_{2}",
                            "[3] v_{2}{#eta sub-event};cent, %;v_{2}",};
    outFile -> cd();
    for (int imeth=0; imeth<nmethod; imeth++){
      grIntFlowVsCent[imeth][id] -> SetTitle(grTitle[imeth]);
      grIntFlowVsCent[imeth][id] -> Write(Form("grRF_%i_%i",imeth,id));
    }


    std::vector<TGraphErrors*> vgr;
    for (int imeth=0; imeth<nmethod; imeth++){
      vgr.push_back(grIntFlowVsCent[imeth][id]);
    }

    
    can[id] = (TCanvas*) DrawTGraph(vgr,"",0.48,1.22,   0,60,-0.005,0.1,    0.18,0.56,0.5,0.8,pidFancyNames.at(id).Data()); // DCA<0.5: 0.88, 1.12 // wo DCA: 0.76, 1.03
    can[id] -> SetName(pidNames.at(id).Data());
    can[id] -> SaveAs(Form("../%s/%sV2vsCent.png",outDirName.Data(),pidNames.at(id).Data()));
  } // end of loop over particle ID
}
void v2plotPID_Reco_ACS(){

  if (bMergeCharged){
    pidNames.clear();
    pidFancyNames.clear();
    pidNames = {"hadron", "pion", "kaon", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
    pidFancyNames = {"hadron", "#pi", "K", "p(#bar{p})", "h-", "#pi-", "K-", "#bar{p}"};
  }
  gSystem->Exec(Form("mkdir -p ../%s/",outDirName.Data()));
  v2plot_differential_flow();
  v2plot_integrated_flow();
}