#include "../PlotV2EtaSubEventPlane.C"
#include "../PlotV2ScalarProduct.C"
#include "../PlotV2HighOrderQCumulant.C"
#include "../DrawTGraphImp.C"
#include "../PlotV2LYZ.C"
void PlotV2DifferentialChargedHadrons()
{

  const vector<pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};
  const TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)"};
  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const int ratioToMethod = 0;
  const double J1rootJ0 = 0.519147;
  int excludeMethod1 = 4;
  int excludeMethod2 = 1;
  int excludeMethod3 = 2;
  int excludeMethod4 = 3;
  int excludeMethod5 = 5;
  int excludeMethod6 = 6;  
  const int markerStyle[] = {24,22,23,27,30,28,26,20};
  const float markerSize = 1.5;
  const float labelSize = 0.07;
  const float titleSize = 0.08;
  const float titleOffSet = 1.2;
  const int textFont = 132;
  const double maxRatio = 1.65;
  const double minRatio = 0.55;
  const double maxX = 3.2;
  const double minX = -0.08;
  const double maxY = 0.26;
  const double minY = -0.01;
  const int firstCentToDraw = 2;
  const int numberOfCentToDraw = 3;

  double X[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const double errX[npt] = {0.};
  bool bUseProduct = 1;
  const Int_t nmethod = 3;
  TString title[nmethod]={"#it{v}_{2}{#Psi_{2,TPC}}","#it{v}_{2}{2}","#it{v}_{2}{4}"}; // "#it{v}_{2}{2,#eta-gap}"
  const int nenergy = 2;
  TGraphErrors *graph[nmethod][nenergy][2]; // v2{Eta-sub}, v2{2}, v2{4}

  // STAR
  const double pTBinSTAR[16] = {0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,3.0,3.4};

  const double v2EtaSubSTAR77_20_30[16] = {0.,0.0256,0.0424,0.0573,0.0704,0.0869,0.1013,0.1161,0.1295,0.1329,0.1526,0.1606,0.1782,0.1965,0.1783,0.};
  const double v2EtaSubeSTAR77_20_30[16] = {0.,0.0005,0.0006,0.0008,0.001,0.0013,0.0017,0.0023,0.0032,0.0044,0.0062,0.0088,0.0131,0.0183,0.0215,0.};

  const double v22STAR77_20_30[16] = {0.,0.0312,0.0423,0.0524,0.067,0.0821,0.0968,0.111,0.1253,0.1336,0.1483,0.1584,0.1786,0.183,0.181,0.};
  const double v22eSTAR77_20_30[16] = {0.,0.0003,0.0004,0.0005,0.0006,0.0008,0.0011,0.0015,0.0021,0.0029,0.0041,0.0058,0.0083,0.0117,0.0137,0.};

  const double v24STAR77_20_30[16] = {0.,0.0219,0.0357,0.0546,0.061,0.088,0.1051,0.1228,0.1615,0.1417,0.1466,0.126,0.3078,0.1102,0.4632,0.};
  const double v24eSTAR77_20_30[16] = {0.,0.0025,0.0031,0.004,0.0053,0.007,0.0093,0.0129,0.0177,0.0244,0.035,0.0497,0.0694,0.1043,0.1135,0.};

  const double v2EtaSubSTAR115_20_30[16] = {0.,0.0263,0.0462,0.0632,0.0796,0.0967,0.1135,0.128,0.1436,0.1528,0.1669,0.1753,0.1842,0.189,0.2095,0.};
  const double v2EtaSubeSTAR115_20_30[16] = {0.,0.0002,0.0003,0.0004,0.0005,0.0006,0.0009,0.0012,0.0016,0.0022,0.003,0.0042,0.0062,0.0087,0.0099,0.};

  const double v22STAR115_20_30[16] = {0.,0.0315,0.0464,0.0608,0.0767,0.0931,0.1087,0.1242,0.1395,0.1502,0.1628,0.1736,0.1783,0.1961,0.2002,0.};
  const double v22eSTAR115_20_30[16] = {0.,0.0001,0.0002,0.0002,0.0003,0.0004,0.0006,0.0008,0.001,0.0014,0.002,0.0028,0.004,0.0056,0.0064,0.};

  const double v24STAR115_20_30[16] = {0.,0.0234,0.0416,0.0577,0.0749,0.0923,0.1103,0.1221,0.1351,0.1457,0.1455,0.1545,0.219,0.1482,0.238,0.};
  const double v24eSTAR115_20_30[16] = {0.,0.001,0.0012,0.0016,0.0022,0.0029,0.0039,0.0054,0.0074,0.0103,0.0148,0.0213,0.0283,0.0429,0.0447,0.};



  const double zeroArray[16]={0.};

  graph[0][0][0] = new TGraphErrors(16,pTBinSTAR,v2EtaSubSTAR77_20_30,zeroArray,v2EtaSubeSTAR77_20_30);
  graph[1][0][0] = new TGraphErrors(16,pTBinSTAR,v22STAR77_20_30,zeroArray,v22eSTAR77_20_30);
  graph[2][0][0] = new TGraphErrors(16,pTBinSTAR,v24STAR77_20_30,zeroArray,v24eSTAR77_20_30);
  graph[0][1][0] = new TGraphErrors(16,pTBinSTAR,v2EtaSubSTAR115_20_30,zeroArray,v2EtaSubeSTAR115_20_30);
  graph[1][1][0] = new TGraphErrors(16,pTBinSTAR,v22STAR115_20_30,zeroArray,v22eSTAR115_20_30);
  graph[2][1][0] = new TGraphErrors(16,pTBinSTAR,v24STAR115_20_30,zeroArray,v24eSTAR115_20_30);

  const TString energy[nenergy] = {"7.7","11.5"};
  for (int ien = 0; ien < nenergy; ien++)
  {

    TString inputFirstRunFileName = Form("../FirstRun_%s.root",energy[ien].Data());
    TString inputSecondRunFileName = Form("../SecondRun_%s.root",energy[ien].Data());
    TFile *firun1 = new TFile(inputFirstRunFileName.Data(),"read");
    TFile *firun2 = new TFile(inputSecondRunFileName.Data(),"read");
    auto *prV2EP3D = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");

    TProfile *prV2EPInt = PlotV2EPDifferentialVersusPt(prV2EP3D,20.,30.,eta_cut);
    graph[0][ien][1] = Converter(prV2EPInt);
    

    // QCumulant
    TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
    TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
    TProfile *hv22pt[ncent][npt][npid];    // profile <<2'>> from 2nd Q-Cumulants
    TProfile *hv24pt[ncent][npt][npid];    // profile <<4'>> from 4th Q-Cumulants
    TProfile *hcov24[ncent];       // <2>*<4>
    TProfile *hcov22prime[ncent][npt][npid]; // <2>*<2'>
    TProfile *hcov24prime[ncent][npt][npid]; // <2>*<4'>
    TProfile *hcov42prime[ncent][npt][npid]; // <2>*<4'>
    TProfile *hcov44prime[ncent][npt][npid]; // <4>*<4'>
    TProfile *hcov2prime4prime[ncent][npt][npid]; // <2'>*<4'>
    // v22 with eta-gap
    TProfile *hv22Gap[ncent];
    TProfile *hv22ptGap[ncent][npt][npid];
    TProfile *hcov22primeGap[ncent][npt][npid];  

    // Get TProfile histograms from ROOTFile

    for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
      hv22[icent] = (TProfile*)firun1->Get(Form("hv22_%i",icent));
      hv24[icent] = (TProfile*)firun1->Get(Form("hv24_%i",icent));
      hcov24[icent] = (TProfile*)firun1->Get(Form("hcov24_%i",icent));
      hv22Gap[icent] = (TProfile*)firun1->Get(Form("hv22Gap_%i",icent));
      for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
        for (int id=0;id<npid;id++){
          hv22pt[icent][ipt][id]=(TProfile*)firun1->Get(Form("hv22pt_%i_%i_%i",icent,ipt,id));
          hv24pt[icent][ipt][id]=(TProfile*)firun1->Get(Form("hv24pt_%i_%i_%i",icent,ipt,id));
          hcov22prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
          hcov24prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
          hcov42prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
          hcov44prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
          hcov2prime4prime[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
          hv22ptGap[icent][ipt][id]=(TProfile*)firun1->Get(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
          hcov22primeGap[icent][ipt][id]=(TProfile*)firun1->Get(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id));
        }
      } // end of loop over pt bin
    } // end of loop over centrality classes

    for (int icent=0;icent<ncent;icent++){
      for (int ipt=0;ipt<npt;ipt++){
        for (int id=0;id<1;id++){
          hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id+4]);
          hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id+4]);
          hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id+4]);
          hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id+4]);
          hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id+4]);
          hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id+4]);
          hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id+4]);
          hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id+4]);
          hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id+4]);
        }
      }
    }

    double v2Dif[3][ncent][1][npt], v2eDif[3][ncent][1][npt];
    for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
      // 2QC
      term cor2 = term(hv22[icent]);
      double v22 = sqrt(cor2.mVal);
      double ev22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
      // 4QC
      term cor4 = term(hv24[icent]);
      double cov24 = Covariance(hcov24[icent],hv22[icent],hv24[icent]);
      double v24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
      double ev24 = sqrt( 1./pow(v24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );
      // 2QC Gapped
      term cor2Gap = term(hv22Gap[icent]);
      double v22Gap = sqrt(cor2Gap.mVal);
      double ev22Gap = sqrt(1./(4.*cor2Gap.mVal)*cor2Gap.mMSE);
      for (int id=0;id<1;id++){ // Differential flow calculation
        for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
          // v22
          term cor2red = term(hv22pt[icent][ipt][id]);
          double v22Dif = cor2red.mVal/v22;
          double cov22prime = Covariance(hcov22prime[icent][ipt][id],hv22[icent],hv22pt[icent][ipt][id]);
          double ev22Dif = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                              + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
          v2Dif[1][icent][id][ipt] = v22Dif;
          v2eDif[1][icent][id][ipt] = ev22Dif;
          
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
          v2Dif[2][icent][id][ipt] = v24Dif;
          v2eDif[2][icent][id][ipt] = ev24Dif;

          // v22 Gapped
          term cor2redGap = term(hv22ptGap[icent][ipt][id]);
          double v22DifGap = cor2redGap.mVal/v22Gap;
          double cov22primeGap = Covariance(hcov22primeGap[icent][ipt][id],hv22Gap[icent],hv22ptGap[icent][ipt][id]);
          double ev22DifGap = sqrt(0.25*pow(cor2Gap.mVal,-3)*(pow(cor2redGap.mVal,2)*cor2Gap.mMSE
                              + 4*pow(cor2Gap.mVal,2)*cor2redGap.mMSE - 4*cor2Gap.mVal*cor2redGap.mVal*cov22primeGap));
          v2Dif[0][icent][id][ipt] = v22DifGap;
          v2eDif[0][icent][id][ipt] = ev22DifGap;
        }
      }

    }
    graph[1][ien][1] = new TGraphErrors(npt, X, v2Dif[0][3][0], errX, v2eDif[0][3][0]); // v2{2}
    graph[2][ien][1] = new TGraphErrors(npt, X, v2Dif[1][3][0], errX, v2eDif[1][3][0]); // v2{4}
    // graph[1][ien][1] = new TGraphErrors(npt, X, v2Dif[2][3][0], errX, v2eDif[2][3][0]); // v2{2,eta-gap}

  } // end of loop over energy
  
  for (int ien = 0; ien < nenergy; ien++)
  {
    for (int i=0; i<nmethod; i++)
    {
      for (int j=0; j<2; j++)
      {
        graph[i][ien][j]->RemovePoint(0);
        graph[i][ien][j]->SetTitle("");// title[i].Data()
        
        graph[i][ien][j]->SetMarkerSize(markerSize);
        graph[i][ien][j]->GetXaxis()->SetTitle("#it{p}_{T}, GeV/c");
        graph[i][ien][j]->GetYaxis()->SetTitle("#it{v}_{2}");
        graph[i][ien][j]->SetDrawOption("P PLC PMC");
        graph[i][ien][j]->GetXaxis()->SetLimits(minX,maxX);
        graph[i][ien][j]->GetYaxis()->SetRangeUser(minY,maxY);
      }
    }
    graph[0][ien][0]->SetMarkerStyle(kFullCircle);
    graph[0][ien][1]->SetMarkerStyle(kOpenCircle);
    graph[1][ien][0]->SetMarkerStyle(kFullTriangleUp);
    graph[1][ien][1]->SetMarkerStyle(kOpenTriangleUp);
    graph[2][ien][0]->SetMarkerStyle(kFullStar);
    graph[2][ien][1]->SetMarkerStyle(kOpenStar);
  }

  TCanvas *can = new TCanvas("can","",1000,600);
  TPaveLabel* label = new TPaveLabel(0.1,0.95,0.9,0.99,Form("Au+Au, 20-30%%, Charged Hadrons")); // at 
  label->SetTextFont(132);
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();
  // gStyle->SetTextFont(132);
  gStyle->SetLegendFont(132);
  can->SetTopMargin(0.12);
  can->SetLeftMargin(0.17);
  can->SetRightMargin(0.04);
  can->SetBottomMargin(0.17);
  // gROOT->SetStyle("Pub");
  TLine lineOne;
  TLatex tex;
  tex.SetTextFont(textFont);
  tex.SetTextSize(titleSize+0.015);
  lineOne.SetLineStyle(2);
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(nmethod,nenergy,0,0);
  for (int i=0; i<3; i++)
  {
    can->cd(i+1);
    graph[i][0][0]->Draw("AP PLC PMC");
    graph[i][0][0]->GetYaxis()->SetTitleSize(titleSize+0.015);
    graph[i][0][0]->GetYaxis()->SetLabelSize(labelSize+0.015);
    graph[i][0][0]->GetYaxis()->SetTitleFont(textFont);
    graph[i][0][0]->GetYaxis()->SetLabelFont(textFont);
    graph[i][0][0]->GetXaxis()->SetTitleSize(titleSize+0.015);
    graph[i][0][0]->GetXaxis()->SetLabelSize(labelSize+0.015);
    graph[i][0][0]->GetXaxis()->SetTitleFont(textFont);
    graph[i][0][0]->GetXaxis()->SetLabelFont(textFont);
    graph[i][0][0]->GetYaxis()->SetTitleOffset(titleOffSet-0.15);
    graph[i][0][1]->Draw("P PLC PMC");
    
    tex.DrawLatex(0.07,0.235,padName[i].Data());
    // 
    TLatex tex1;
    tex1.SetTextFont(textFont);  
    tex1.SetTextSize(titleSize-0.02);
    tex1.DrawLatex(1.6,0.01,"#sqrt{#it{s}_{NN}} = 7.7 GeV");

    TLegend *leg1;
    if (i==0) leg1 = new TLegend(0.25,0.6,0.5,0.9);
    else leg1 = new TLegend(0.05,0.6,0.3,0.9);
    leg1->SetBorderSize(0);
    leg1->SetHeader(title[i].Data());
    leg1->SetTextSize(titleSize-0.01);
    leg1->AddEntry(graph[i][0][1],"AMPT SM, #it{#sigma}_{p}=1.5mb","p");
    leg1->AddEntry(graph[i][0][0],"STAR","p");
    leg1->Draw();
    
  }
  for (int i=0; i<3; i++)
  {
    can->cd(i+nmethod+1);
    graph[i][1][0]->Draw("AP PLC PMC");
    // if (i==0)
    // {
      graph[i][1][0]->GetYaxis()->SetTitleSize(titleSize);
      graph[i][1][0]->GetYaxis()->SetLabelSize(labelSize);
      graph[i][1][0]->GetYaxis()->SetTitleFont(textFont);
      graph[i][1][0]->GetYaxis()->SetLabelFont(textFont);
      graph[i][1][0]->GetXaxis()->SetTitleSize(titleSize);
      graph[i][1][0]->GetXaxis()->SetLabelSize(labelSize);
      graph[i][1][0]->GetXaxis()->SetTitleFont(textFont);
      graph[i][1][0]->GetXaxis()->SetLabelFont(textFont);
      graph[i][1][0]->GetYaxis()->SetTitleOffset(titleOffSet);
      graph[i][1][0]->GetXaxis()->SetTitleOffset(1.);
      // graph[i][1][0]->GetXaxis()->SetLabelOffset(0.017);
      tex.SetTextSize(titleSize);
    // }
    // else
    // {
    // graph[i][1][0]->GetYaxis()->SetTitleSize(titleSize);
    // graph[i][1][0]->GetYaxis()->SetLabelSize(labelSize);
    // graph[i][1][0]->GetYaxis()->SetTitleFont(textFont);
    // graph[i][1][0]->GetYaxis()->SetLabelFont(textFont);
    // graph[i][1][0]->GetXaxis()->SetTitleSize(titleSize);
    // graph[i][1][0]->GetXaxis()->SetLabelSize(labelSize);
    // graph[i][1][0]->GetXaxis()->SetTitleFont(textFont);
    // graph[i][1][0]->GetXaxis()->SetLabelFont(textFont);
    // // graph[i][1][0]->GetYaxis()->SetTitleOffset(titleOffSet-0.05);
    // // graph[i][1][0]->GetXaxis()->SetTitleOffset(0.8);
    // tex.SetTextSize(titleSize+0.015);
    // }
    


    graph[i][1][1]->Draw("P PLC PMC");
    
    tex.DrawLatex(0.07,0.235,padName[i+nmethod+1].Data());
    tex.SetTextSize(titleSize-0.02);
    tex.DrawLatex(1.6,0.01,"#sqrt{#it{s}_{NN}} = 11.5 GeV");
  }
  can->SaveAs(Form("V2pT_AMPT_vs_STAR.png"));
  can->SaveAs(Form("V2pT_AMPT_vs_STAR.pdf"));
}