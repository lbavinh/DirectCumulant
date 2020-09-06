#include "DrawTGraph.C"

TFile *outFile = new TFile("../CompareResult/VinhPID_GEANT.root","recreate");
bool bDrawPlots1040 = 0;
bool drawDistributions = 0;
bool bSaveCanvas = 0;
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

const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};

TProfile *prV22int[ncent][npid], *prV24int[ncent][npid], *prV2EPint[ncent][npid]; // TProfile for integrated flow 
TProfile *prV22dif1040[npt][npid], *prV24dif1040[npt][npid], *prV2EPdif1040[npt][npid], *pt1040[npt][npid]; // TProfile for differential flow of 10-40% centrality bin

void v2plot_differential_flow(){
  TFile *inFile = new TFile("../ROOTFile/PID_MC.root","read");


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
  const std::vector<TString> errVectorNames = {"double eV22Dif1040CHp[npt]=", "double eV22Dif1040Pionp[npt]=", "double eV22Dif1040Kaonp[npt]=", "double eV22Dif1040Protonp[npt]=", "double eV22Dif1040CHm[npt]=", "double eV22Dif1040Pionm[npt]=", "double eV22Dif1040Kaonm[npt]=", "double eV22Dif1040Protonm[npt]="};
  // const std::vector<TString> errVectorNames = {"double eV24Dif1040CHp[npt]=", "double eV24Dif1040Pionp[npt]=", "double eV24Dif1040Kaonp[npt]=", "double eV24Dif1040Protonp[npt]=", "double eV24Dif1040CHm[npt]=", "double eV24Dif1040Pionm[npt]=", "double eV24Dif1040Kaonm[npt]=", "double eV24Dif1040Protonm[npt]="};
  // const std::vector<TString> errVectorNames = {"double eV2EPDif1040CHp[npt]=", "double eV2EPDif1040Pionp[npt]=", "double eV2EPDif1040Kaonp[npt]=", "double eV2EPDif1040Protonp[npt]=", "double eV2EPDif1040CHm[npt]=", "double eV2EPDif1040Pionm[npt]=", "double eV2EPDif1040Kaonm[npt]=", "double eV2EPDif1040Protonm[npt]="}; 
  
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
        if (icent==1 && bDrawPlots1040) cout << ev22Dif;
        // if (icent==1 && bDrawPlots1040) cout << ev24Dif;
        // if (icent==1 && bDrawPlots1040) cout << ev2EP;
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
      sprintf(hname,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
      cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",0.77, 1.23, 0., maxpt, -0.01, 0.2, 0.18, 0.56, 0.5, 0.8, hname);
      cV2PT[icent][id] -> SetName(hname);
      sprintf(hname,"../Graphics/%sDFCent%i-%i.png",pidNames.at(id).Data(),icent*10,(icent+1)*10);
      cV2PT[icent][id] -> SaveAs(hname);
    }
  }

  double eV22Dif1040CHp[npt]={0.000250377,0.000306068,0.000384392,0.000482183,0.000623315,0.000736009,0.00118403,0.00165664,0.00611936};
  double eV22Dif1040Pionp[npt]={0.000276863,0.000396958,0.000608313,0.000918648,0.00131861,0.00167622,0.00286521,0.00453251,0.0203391};
  double eV22Dif1040Kaonp[npt]={0.000985973,0.000957384,0.00114458,0.00146777,0.00193861,0.00238393,0.00408208,0.0064655,0.0285735};
  double eV22Dif1040Protonp[npt]={0.00084814,0.000608063,0.000571673,0.000628057,0.0007586,0.000858042,0.00132879,0.00183264,0.00677315};
  double eV22Dif1040CHm[npt]={0.000258589,0.000362623,0.000535812,0.000795244,0.00112599,0.00138918,0.00226239,0.00338436,0.0141701};
  double eV22Dif1040Pionm[npt]={0.00026446,0.000380305,0.000580907,0.00088456,0.00127494,0.00161692,0.00276493,0.00435781,0.019839};
  double eV22Dif1040Kaonm[npt]={0.00135412,0.00134511,0.0016598,0.00221894,0.00309684,0.00395623,0.00703582,0.011417,0.0396283};
  double eV22Dif1040Protonm[npt]={0.0139501,0.00877778,0.00729674,0.00748938,0.00891569,0.0102154,0.0176399,0.0276379,0.011604};

  double eV24Dif1040CHp[npt]={0.00393944, 0.0046574, 0.00580832, 0.00754447, 0.00962995, 0.0111394, 0.0162147, 0.0217968, 0.062402};
  double eV24Dif1040Pionp[npt]={0.00427627, 0.00589614, 0.00888263, 0.0127643, 0.0176608, 0.021809, 0.0359699, 0.0536001, 0.187989};
  double eV24Dif1040Kaonp[npt]={0.0159767, 0.014355, 0.0161911, 0.0203085, 0.0262709, 0.0317771, 0.0521675, 0.0777483, 0.278757};
  double eV24Dif1040Protonp[npt]={0.0122489, 0.00866283, 0.00811008, 0.00931179, 0.0111635, 0.012543, 0.017628, 0.023264, 0.0674229};
  double eV24Dif1040CHm[npt]={0.00402892, 0.00562555, 0.0079661, 0.0116505, 0.0162427, 0.0198523, 0.0324849, 0.0485143, 0.175717};
  double eV24Dif1040Pionm[npt]={0.00407939, 0.00576103, 0.00829019, 0.012316, 0.0171313, 0.0210563, 0.0349607, 0.0521695, 0.190774};
  double eV24Dif1040Kaonm[npt]={0.0217772, 0.0197707, 0.0230765, 0.0296323, 0.0399422, 0.0507466, 0.0842217, 0.128386, 0.443462};
  double eV24Dif1040Protonm[npt]={0.223339, 0.129618, 0.101039, 0.103635, 0.11948, 0.130162, 0.217291, 0.337854, 0.412331};

  double eV2EPDif1040CHp[npt]={0.000216868,0.000263009,0.000323103,0.000401615,0.000516494,0.00060393,0.000997111,0.00147976,0.00617821};
  double eV2EPDif1040Pionp[npt]={0.000237602,0.000334177,0.000501853,0.000757703,0.00113487,0.00150182,0.00275872,0.00449628,0.0209408};
  double eV2EPDif1040Kaonp[npt]={0.000824095,0.000797246,0.00096916,0.00128931,0.00178923,0.00226117,0.00405453,0.00650826,0.0303361};
  double eV2EPDif1040Protonp[npt]={0.000708095,0.000514948,0.000479147,0.000520681,0.000627859,0.000707674,0.00114087,0.00166724,0.00685769};
  double eV2EPDif1040CHm[npt]={0.000222178,0.000305923,0.000446643,0.0006531,0.00094523,0.00120708,0.0021318,0.00331945,0.0144208};
  double eV2EPDif1040Pionm[npt]={0.000226899,0.000320516,0.000481987,0.000728219,0.00108965,0.001442,0.00265372,0.00431378,0.0198313};
  double eV2EPDif1040Kaonm[npt]={0.00117716,0.00116778,0.00149415,0.00209478,0.00302912,0.00393833,0.00717724,0.0116886,0.0564848};
  double eV2EPDif1040Protonm[npt]={0.0130691,0.00842116,0.00708112,0.00733731,0.00876258,0.0101419,0.017503,0.0282952,0.136957};

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
  }
    
  

  // double eV22Dif1040[npt]={4.16021e-05, 4.57347e-05, 6.66802e-05, 0.000102774, 0.00017121, 0.000272493, 0.000500597};
  // double eV24Dif1040[npt]={0.000514427, 0.000644468, 0.000887692, 0.00131467, 0.00206218, 0.00311487, 0.005409};
  // double eV2EPDif1040[npt]={3.68069e-05, 3.8137e-05, 5.68007e-05, 8.74456e-05, 0.000142745, 0.000228144, 0.000461732};
  double ePT[npt]={0.};
  TCanvas *cV2PT1040[npid];
  for (int id=0;id<npid;id++){
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
    cV2PT1040[id] -> SaveAs(Form("../Graphics/%sDFCent10-40.png",pidNames.at(id).Data()));
  }
}

void v2plot_integrated_flow(){
  if (bDrawPlots1040) return;
  char hname[400];
  TFile *inFile = new TFile("../ROOTFile/PID_MC.root","read");
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
  TGraphErrors *grIntFlowVsCent[nmethod][npid];
  TCanvas *can[npid];
  for (int id=0;id<npid;id++){
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
      vV22.push_back(sqrt(cor2.mVal));
      eV22.push_back(sqrt(1./(4.*cor2.mVal)*cor2.mMSE));
      // 4QC
      term cor4 = term(hv24[icent][id]);
      double cov24 = Covariance(hcov24[icent][id],hv22[icent][id],hv24[icent][id]);
      double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
      vV24.push_back(v24);
      eV24.push_back( sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) );
  
      vV22int.push_back(prV22int[icent][id]->GetBinContent(1));
      vV24int.push_back(prV24int[icent][id]->GetBinContent(1));
      eV22int.push_back(prV22int[icent][id]->GetBinError(1));
      eV24int.push_back(prV24int[icent][id]->GetBinError(1));
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
    // const char *grTitle[5]={"[1] v_{2}{2,QC};cent, %;v_{2}",
    //                         "[2] v_{2}{4,QC};cent, %;v_{2}",
    //                         "[3] v_{2}{#eta sub-event};cent, %;v_{2}",
    //                         "[4] v_{2}{2,QC fix};cent, %;v_{2}",
    //                         "[5] v_{2}{4,QC fix};cent, %;v_{2}"};
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
    can[id] -> SaveAs(Form("../Graphics/%sV2vsCent.png",pidNames.at(id).Data()));
  } // end of loop over particle ID
}
void v2plotPID_MC(){
  v2plot_differential_flow();
  v2plot_integrated_flow();
}