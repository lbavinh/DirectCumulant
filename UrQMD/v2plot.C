#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "Func_StatErrCalc.C"
using namespace std;
#include <fstream>

void v2plot(){
  static const int ncent = 8; // 0-80%
  static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};
  static const Float_t maxpt = 3.5; // max pt
  static const Float_t minpt = 0.; // min pt
  static const int npt = 12; // 0.2 - 3.5 GeV/c 
  static const double bin_pT[13]={0.,0.1,0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.4,1.7,2.0};
  // Input hist

  // TProfile for reference flow
  TProfile *hv2MC[ncent];       // profile for MC integrated v2
  TProfile *hv22[ncent];        // profile <<2>> from 2nd Q-Cumulants
  TProfile *hv24[ncent];        // profile <<4>> from 4th Q-Cumulants
  // TProfile for differential flow
  TProfile *hPT[ncent][npt];       // profile pt 
  TProfile *hv2MCpt[ncent][npt];   // profile v2pt from MC toy   
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

  TFile *inFile;
  // OUTPUT
  TGraphErrors *grDifFl[3][ncent], *grRefFl[ncent];     // 3 = {MC, 2QC, 4QC}
  TGraph *grshade[ncent];
  TMultiGraph *mgRefFl[ncent], *mgDifFl[ncent];


  // Temporary variables
  char hname[800]; // histogram hname
  TProfile *pr; // temporary TProfile for TProfile extracting from root file
  TProfile *prx, *pry, *prxy; // for covariance calculation
  Double_t stats[6]; // stats of TProfile

  // inFile = new TFile("./ROOTFile/v2QC.root","read");

  // inFile = new TFile("./ROOTFile/test.root","read");
  // inFile = new TFile("./ROOTFile/v2QC_etagap.root","read");
  inFile = new TFile("./ROOTFile/v2QC_etagap_eta2.5.root","read");  
  // Get TProfile histograms from ROOTFile
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    sprintf(hname,"hv2MC_cent%i",icent);
    hv2MC[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv22_cent%i",icent);
    hv22[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hv24_cent%i",icent);
    hv24[icent] = (TProfile*)inFile->Get(hname);
    sprintf(hname,"hcov24_cent%i",icent);
    hcov24[icent] = (TProfile*)inFile->Get(hname);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
        sprintf(hname,"hPT_cent%i_pt%i",icent,ipt);
        hPT[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv2MCpt_cent%i_pt%i",icent,ipt);
        hv2MCpt[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv22pt_cent%i_pt%i",icent,ipt);
        hv22pt[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hv24pt_cent%i_pt%i",icent,ipt);
        hv24pt[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov22prime_cent%i_pt%i",icent,ipt);
        hcov22prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov24prime_cent%i_pt%i",icent,ipt);
        hcov24prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov42prime_cent%i_pt%i",icent,ipt);
        hcov42prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov44prime_cent%i_pt%i",icent,ipt);
        hcov44prime[icent][ipt]=(TProfile*)inFile->Get(hname);
        sprintf(hname,"hcov2prime4prime_cent%i_pt%i",icent,ipt);
        hcov2prime4prime[icent][ipt]=(TProfile*)inFile->Get(hname);
    } // end of loop over pt bin
  } // end of loop over centrality classes

  //==========================================================================================================================
  // reference flow comparison
  Double_t v2[ncent][3];
  Double_t ev2[ncent][3];
  Double_t x[3]={0.5,1.5,2.5};
  Double_t ex[3]={0};

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    // Reference flow calculation

    Double_t v2MCint;  // The Monte Carlo estimate for integrated v2 obtained using the known reaction plane event-by-event, v_{2}{MC}
    Double_t v2MCintE; // Standard error of integrated v_{2}{MC}

    Double_t v22int;  // Integrated elliptic flow obtained with direct cumulants of 2nd order, v_{2}{2,QC}
    Double_t v22intE; // Standard error of integrated v_{2}{2,QC}
    Double_t cor2;    // The average all-event 2-particle correlation of RFP, <<2>>
    Double_t cor2E;   // stat. err. of 2-particle correlations, s(<<2>>)

    Double_t v24int;  // Integrated elliptic flow obtained with direct cumulants of 4th order, v_{2}{4,QC}
    Double_t v24intE; // Standard error of integrated v_{2}{4,QC}
    Double_t cor4;    // The average all-event 4-particle correlation of RFP, <<4>>
    Double_t cor4E;   // error of <<4>>

    Double_t sumw2cor2;    // sumw2 of <2>
    Double_t sumwcor2;     // sumw of <2>
    Double_t sumw2cor4;    // sumw2 of <4>
    Double_t sumwcor4;     // sumw of <4>

    Double_t sumwcor24;    // sum(w<2>,w<4>)
    Double_t cov24;        // Cov(<2>,<4>)
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
    //=============================================
    // reference flow comparison
    v2[icent][0] = v2MCint;
    v2[icent][1] = v22int;
    v2[icent][2] = v24int;
    ev2[icent][0] = v2MCintE;
    ev2[icent][1] = v22intE;
    ev2[icent][2] = v24intE;

    grRefFl[icent] = new TGraphErrors(3,x,v2[icent],ex,ev2[icent]);
    grRefFl[icent]->SetMarkerColor(kRed);
    grRefFl[icent]->SetMarkerStyle(20);
    grRefFl[icent]->SetMarkerSize(1.3);
    grRefFl[icent]->SetDrawOption("P");
    // Set a shade between error of v2MC
    grshade[icent] = new TGraph(8);
    for (Int_t i=0; i<4; i++) {
      grshade[icent]->SetPoint(i,i+0.005,v2[icent][0]+ev2[icent][0]);
      grshade[icent]->SetPoint(4+i,3+0.005-i,v2[icent][0]-ev2[icent][0]);
    }
    grshade[icent] -> SetFillStyle(1001);
    grshade[icent] -> SetFillColor(18);
    grshade[icent] -> SetDrawOption("f");
    mgRefFl[icent] = new TMultiGraph();
    mgRefFl[icent] -> Add(grRefFl[icent]);
    mgRefFl[icent] -> Add(grshade[icent]);

    //==========================================================================================================================

    // Differential flow calculation

    Double_t pt[npt];
    Double_t ept[npt]; // error bin pT = 0.0
    Double_t v2MCpt[npt]; // v2 in given pT bin
    Double_t ev2MCpt[npt]; // standard error of v2 in given pT bin
  
    Double_t cor2Red[npt];         // Differential 2nd order cumulant d_{2}{2} = <<2'>>
    Double_t cor2RedE[npt];        // Error of <<2'>>
    Double_t v22dif[npt];      // Differential elliptic flow v'_{2}{2} extracted from 2nd order cumulants
                            // v'_{2}{2} = d_{2}{2} / sqrt( c_{2}{2} )
    Double_t v22difE[npt];     // Error of v'_{2}{2}
    
    Double_t cor4Red[npt];    // Reduced average all-event 4-particle correlation <<4'>>
    Double_t cor4RedE[npt];   // Error of <<4'>>
    Double_t v24dif[npt];      // Differential elliptic flow v'_{2}{4} extracted from 4th order cumulants
                            // v'_{2}{4} = -d_{2}{4} / pow( -c_{2}{4} , 3/4 )
    Double_t v24difE[npt];     // Error of v'_{2}{4}

    Double_t sumwcor22prime[npt];        // sum(w(<2>)*w(<2'>))
    Double_t cov22prime[npt];            // Cov(<2>,<2'>)
    Double_t sumwcor24prime[npt];        // sum(w(<2>)*w(<4'>))
    Double_t cov24prime[npt];            // Cov(<2>,<4'>)
    Double_t sumwcor42prime[npt];        // sum(w(<4>)*w(<2'>))
    Double_t cov42prime[npt];            // Cov(<4>,<2'>)
    Double_t sumwcor44prime[npt];        // sum(w(<4>)*w(<4'>))
    Double_t cov44prime[npt];            // Cov(<4>,<4'>)
    Double_t sumwcor2prime4prime[npt];   // sum(w(<2'>)*w(<4'>))
    Double_t cov2prime4prime[npt];       // Cov(<2'>,<4'>)

    Double_t sumw2cor2red[npt]; // sumw2 of <2'>
    Double_t sumwcor2red[npt];  // sumw of <2'>    
    Double_t sumw2cor4red[npt]; // sumw2 of <4'>
    Double_t sumwcor4red[npt];  // sumw of <4'>

    for(int ipt=0; ipt<npt; ipt++){ // loop for all pT bin
      
      // Differential flow v2MC
      pt[ipt] = hPT[icent][ipt] -> GetBinContent(1);
      ept[ipt] = 0;
      v2MCpt[ipt]  = hv2MCpt[icent][ipt] -> GetBinContent(1);
      ev2MCpt[ipt] = hv2MCpt[icent][ipt] -> GetBinError(1);

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
    grDifFl[0][icent] = new TGraphErrors(npt,pt,v2MCpt,ept,ev2MCpt);
    grDifFl[0][icent] -> SetMarkerColor(kRed+1);
    grDifFl[0][icent] -> SetMarkerStyle(25);

    grDifFl[1][icent] = new TGraphErrors(npt,pt,v22dif,ept,v22difE);
    grDifFl[1][icent] -> SetMarkerColor(kGreen+1);
    grDifFl[1][icent] -> SetMarkerStyle(20);

    grDifFl[2][icent] = new TGraphErrors(npt,pt,v24dif,ept,v24difE);
    grDifFl[2][icent] -> SetMarkerColor(kAzure+2);
    grDifFl[2][icent] -> SetMarkerStyle(22);
    mgDifFl[icent] = new TMultiGraph();
    for (int i=0; i<3; i++){
      grDifFl[i][icent] -> SetMarkerSize(1.3);
      grDifFl[i][icent] -> SetDrawOption("P");
      mgDifFl[icent] -> Add(grDifFl[i][icent]);
    }
  } // end of loop over centrality classes

  //==========================================================================================================================

  TLegend *leg = new TLegend(0.11,.89,0.4,.78);
  leg -> AddEntry(grDifFl[0][0],"v_{2}{MC}","p");
  leg -> AddEntry(grDifFl[1][0],"v_{2}{2,QC}","p");
  leg -> AddEntry(grDifFl[2][0],"v_{2}{4,QC}","p");
  leg -> SetFillColor(0);
  leg -> SetTextSize(0.04);
  leg -> SetTextFont(62);
  leg -> SetBorderSize(0);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1","multipads",200,10,1600,900);
  c1->Divide(4,2,0,0);
  TCanvas *c2 = new TCanvas("c2","multipads",200,10,1600,900);
  c2->Divide(4,2,0,0);
  Double_t xmin=0.;
  Double_t xmax=2.15;
  Double_t ymin=-0.03;
  Double_t ymax=0.15;
  TH2F *h[ncent], *h2[ncent];
  TLatex *latex, *latex2, *latex3;

  for(int icent=0; icent<8; icent++){
    // differential flow
    h[icent] = new TH2F("","",5,xmin,xmax,5,ymin,ymax);
    c1 -> cd(icent+1);
    h[icent] -> Draw();
    h[icent] -> SetXTitle("p_{T}, GeV/c");
    h[icent] -> SetYTitle("v_{2}");
    mgDifFl[icent]-> Draw("P");
    leg -> Draw();
    char text1[800];
    sprintf(text1,"#splitline{cent: %i-%i%%}{#splitline{#eta_{RFP}<-0.05}{#eta_{POI}>0.05}}",10*(icent),10*(icent+1));
    latex = new TLatex(xmax*0.98,ymin+0.025,text1);
    latex -> SetTextFont(62);
    latex -> SetTextSize(0.04);
    latex -> SetTextAlign(31);
    latex -> Draw();
    // reference flow
    Double_t ymin2 = TMath::MinElement(3,v2[icent])*0.98;
    Double_t ymax2 = TMath::MaxElement(3,v2[icent]) + TMath::MaxElement(3,ev2[icent])*1.1;
    h2[icent] = new TH2F("","",3,0,3,10,ymin,0.1);
    c2 -> cd(icent+1);
    h2[icent]->SetYTitle("v_{n}");
    h2[icent]->SetCanExtend(TH1::kAllAxes);
    const char *method[3]  = {"v_{2}{MC}","v_{2}{2,QC}","v_{2}{4,QC}"};
    TAxis* a = h2[icent] -> GetXaxis();
    h2[icent] -> Fill(method[0],(ymin2+ymax2)/2.,1);
    h2[icent] -> Fill(method[1],(ymin2+ymax2)/2.,1);
    h2[icent] -> Fill(method[2],(ymin2+ymax2)/2.,1);
    h2[icent]->GetXaxis()->SetLabelSize(0.05);
    a->SetNdivisions(300); // 3 division, 0 sub-division
    h2[icent]->Draw();
    //grshade[icent] -> Draw("f");
    mgRefFl[icent]-> Draw("P");

    latex2 = new TLatex(3*0.98,-0.01,text1);
    latex2 -> SetTextFont(62);
    latex2 -> SetTextSize(0.04);
    latex2 -> SetTextAlign(31);
    latex2 -> Draw();
  }
  c1 -> SaveAs("~/NIRS/Event Generator, Direct Cumulant/urqmd/graph/v2pt.png");
  c2 -> SaveAs("~/NIRS/Event Generator, Direct Cumulant/urqmd/graph/v2.png");
  TCanvas *c[ncent];
  TLatex *text[ncent];
  for (int i=0;i<ncent;i++){
    sprintf(hname,"Cent%i-%i%%",i*10,(i+1)*10);
    c[i] = new TCanvas(hname,hname,200,10,800,600);
    grshade[i] -> SetFillStyle(1001);
    grshade[i] -> SetFillColor(18);
    grshade[i] -> Draw("f");
    grRefFl[i] -> SetTitle("Reference flow");
    grRefFl[i] -> Draw("AP");
    char text1[800];
    sprintf(text1,"#splitline{cent: %i-%i%%}{#splitline{#eta_{RFP}<-0.05}{#eta_{POI}>0.05}}",10*(i),10*(i+1));
    text[i] = new TLatex(1.,(TMath::MinElement(3,grRefFl[i]->GetY())),text1);
    text[i] -> SetTextFont(62);
    text[i] -> SetTextSize(0.04);
    text[i] -> SetTextAlign(21);
    text[i] -> Draw();
    sprintf(hname,"~/NIRS/Event Generator, Direct Cumulant/urqmd/graph/Cent%i-%i%%.png",i*10,(i+1)*10);
    c[i] -> SaveAs(hname);
  }
  for (int i=0; i<ncent; i++){
    cout<< 10*(i)<<"-"<<10*(i+1)<<"\t"<< v2[i][0]<<"\t"<< v2[i][1]<<"\t"<< v2[i][2] << endl;
  }
  TCanvas *c3 = new TCanvas("c3","v2pt",200,10,1600,900);
  // differential flow
  TH2F *h3 = new TH2F("h3","",5,xmin,xmax,5,ymin,ymax);
  h3 -> Draw();
  h3 -> SetXTitle("p_{T}, GeV/c");
  h3 -> SetYTitle("v_{2}");
  int mycent = 3;
  mgDifFl[mycent]-> Draw("P");
  leg -> Draw();
  sprintf(hname,"#splitline{cent: %i-%i%%}{#splitline{#eta_{RFP}<-0.05}{#eta_{POI}>0.05}}",10*(mycent),10*(mycent+1));
  latex3 = new TLatex(xmax*0.98,ymin+0.03,hname);
  latex3 -> SetTextFont(62);
  latex3 -> SetTextSize(0.04);
  latex3 -> SetTextAlign(31);
  latex3 -> Draw();
  sprintf(hname,"~/NIRS/Event Generator, Direct Cumulant/urqmd/graph/v2pt_Cent%i-%i%%.png",mycent*10,(mycent+1)*10);
  c3 -> SaveAs(hname);
  TFile *outFile = new TFile("TGraph.root","recreate");
  outFile -> cd();
  for (int i=0; i<3; i++){
    sprintf(hname,"gr_%i",i);
    grDifFl[i][mycent] -> Write(hname);
  }
  outFile -> Close();
}