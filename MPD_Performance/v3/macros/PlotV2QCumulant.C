#include "DrawTGraph.C"
#include "MultiparticleCorrelation.cxx"
#include <TFile.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLine.h>

#include <vector>
#include <iostream>

// Flags
bool saveAsPNG = true;
int ratioToMethod = 2; // v22,v24,v22eta-sub,v24eta-gap
int drawDifferentialFlowTill = 0; // Draw v2 vs pT (10% centrality cut) till: 0: no drawing; 1: till 10%; 2: till 20%; etc.
// Constants
const int npid = 12; // CH+, pion+, kaon+, proton, CH-, pion-, kaon-, antiproton, CH, pions, kaons, protons+antiproton
const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_bar", "hadron", "pion", "kaon","proton_antiproton"};
const std::vector<TString> pidFancyNames = {"h^{+}", "#pi^{+}", "K^{+}", "p", "h^{-}", "#pi^{-}", "K^{-}", "#bar{p}", "h^{#pm}","#pi^{#pm}","K^{#pm}","p(#bar{p})"};
const float eta_gap = 0.05;
// TString inputFileName = Form("QCumulant_eta_gap_%1.1f.root",eta_gap*2);
// TString model = "AMPT08";
TString modelFancy = "vHLLE+UrQMD";
TString energy = "11.5GeV";
TString model = "Model";
// TString inputFileName = Form("QCumulant_AMPT15_4.5.root");
TString inputFileName = Form("../data/FirstRun_%s.root",model.Data());

const int nmethod = 4; // 2QC, 4QC, 2QC-gapped, 4QC-gapped

const int npt = 7; // 0.5 - 3.6 GeV/c - number of pT bins
const double bin_pT[npt+1]={0.2, 0.4, 0.6, 1.0, 1.4, 1.8, 2.2, 3.0};
const int binMinPtRFP = 0;  // 0.2 GeV 
const int binMaxPtRFP = 7; // 2.8 GeV
// const int binMaxPtRFP = 10; // 2.0 GeV
// const int binMaxPtRFP = 16; // 3.6 GeV
const double minptRFP = 0.2;
const double maxptRFP = 3.0;

const double maxpt = 2.4; // for v2 vs pt plotting
const double minpt = 0.;  // for v2 vs pt plotting

const int ncent = 9; // 0-80 %
const double bin_cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
const double bin_centE[ncent] = {0};
const std::vector<std::pair<int,int>> centrality = {{0,5},{5,10},{10,20},{20,30},{30,40},{40,50},{50,60},{60,70},{70,80}};


const double mincent = 0.;  // for v2 vs centrality
const double maxcent = 60.; // for v2 vs centrality

const double minV2int = -0.005; // for v2 vs centrality plotting
const double maxV2int = 0.1; // for v2 vs centrality plotting
const double minV2dif = -0.01; // for v2 vs pt plotting
const double maxV2dif = 0.2; // for v2 vs pt plotting


std::vector <Double_t> coordinateLeg = {0.18,0.63,0.45,0.889};
std::vector<std::pair<Double_t,Double_t>> rangeRatio = {{0.84,1.16},{0.84,1.16}};
// std::vector<std::pair<Double_t,Double_t>> rangeRatioRF ={{0.65,1.11},{0.65,1.11}};
std::vector<std::pair<Double_t,Double_t>> rangeRatioRF ={{0.89,1.11},{0.89,1.11}};
int marker[]={23,25,26,20}; // v22,v24,v22eta-sub,v24eta-gap

void CalStatErrCent1040(TString model, TString energy,double v2eDif1040[nmethod][npid][npt]){

  // TFile *inFile = new TFile(Form("../ROOTFile/%s_%s.root",model.Data(),energy.Data()),"read");
  TFile *inFile = new TFile(inputFileName.Data(),"read");
  
  // 2,4 QC
  TProfile *hv22[ncent];                            // <2>
  TProfile *hv24[ncent];                            // <4>
  TProfile *hv22pt[ncent][npt][npid];               // <2'>
  TProfile *hv24pt[ncent][npt][npid];               // <4'>
  TProfile *hcov24[ncent];                          // <2><4>
  TProfile *hcov22prime[ncent][npt][npid];          // <2><2'>
  TProfile *hcov24prime[ncent][npt][npid];          // <2><4'>
  TProfile *hcov42prime[ncent][npt][npid];          // <2><4'>
  TProfile *hcov44prime[ncent][npt][npid];          // <4><4'>
  TProfile *hcov2prime4prime[ncent][npt][npid];     // <2'><4'>

  // 2,4 QC 2-sub
  TProfile *hv22Gap[ncent];                         // <2>
  TProfile *hv24Gap[ncent];                         // <4>  
  TProfile *hcov24Gap[ncent];                       // <2><4>
  TProfile *hv22ptGap[ncent][npt][npid];            // <2'>
  TProfile *hv24ptGap[ncent][npt][npid];            // <4'>
  TProfile *hcov22primeGap[ncent][npt][npid];       // <2><2'>  
  TProfile *hcov24primeGap[ncent][npt][npid];       // <2><4'>
  TProfile *hcov42primeGap[ncent][npt][npid];       // <2><4'>
  TProfile *hcov44primeGap[ncent][npt][npid];       // <4><4'>
  TProfile *hcov2prime4primeGap[ncent][npt][npid];  // <2'><4'>

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)inFile->FindObjectAny(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->FindObjectAny(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->FindObjectAny(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hv22Gap_%i", icent));
    hv24Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hv24Gap_%i", icent));
    hcov24Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hcov24Gap_%i", icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid-4;id++){
        hv22pt[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
        hv24ptGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv24ptGap_%i_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id)); 
        hcov24primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov24primeGap_%i_%i_%i",icent,ipt,id));
        hcov42primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov42primeGap_%i_%i_%i",icent,ipt,id));
        hcov44primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov44primeGap_%i_%i_%i",icent,ipt,id));
        hcov2prime4primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov2prime4primeGap_%i_%i_%i",icent,ipt,id));      
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes


  for (int icent=0;icent<ncent;icent++){
    for (int ipt=0;ipt<npt;ipt++){
      for (int id=8;id<npid;id++){
        hv22pt[icent][ipt][id] = (TProfile*)  hv22pt[icent][ipt][id-8] -> Clone();
        hv24pt[icent][ipt][id] = (TProfile*)  hv24pt[icent][ipt][id-8] -> Clone();
        hcov22prime[icent][ipt][id] = (TProfile*)  hcov22prime[icent][ipt][id-8] -> Clone();
        hcov24prime[icent][ipt][id] = (TProfile*)  hcov24prime[icent][ipt][id-8] -> Clone();
        hcov42prime[icent][ipt][id] = (TProfile*)  hcov42prime[icent][ipt][id-8] -> Clone();
        hcov44prime[icent][ipt][id] = (TProfile*)  hcov44prime[icent][ipt][id-8] -> Clone();
        hcov2prime4prime[icent][ipt][id] = (TProfile*)  hcov2prime4prime[icent][ipt][id-8] -> Clone();
        hv22ptGap[icent][ipt][id] = (TProfile*)  hv22ptGap[icent][ipt][id-8] -> Clone();
        hv24ptGap[icent][ipt][id] = (TProfile*)  hv24ptGap[icent][ipt][id-8] -> Clone();
        hcov22primeGap[icent][ipt][id] = (TProfile*)  hcov22primeGap[icent][ipt][id-8] -> Clone();
        hcov24primeGap[icent][ipt][id] = (TProfile*)  hcov24primeGap[icent][ipt][id-8] -> Clone();
        hcov42primeGap[icent][ipt][id] = (TProfile*)  hcov42primeGap[icent][ipt][id-8] -> Clone();
        hcov44primeGap[icent][ipt][id] = (TProfile*)  hcov44primeGap[icent][ipt][id-8] -> Clone();
        hcov2prime4primeGap[icent][ipt][id] = (TProfile*)  hcov2prime4primeGap[icent][ipt][id-8] -> Clone();

        hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id-4]);
        hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id-4]);
        hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id-4]);
        hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id-4]);
        hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id-4]);
        hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id-4]);
        hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id-4]);
        hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id-4]);
        hv24ptGap[icent][ipt][id] -> Add(hv24ptGap[icent][ipt][id-4]);
        hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id-4]);
        hcov24primeGap[icent][ipt][id] -> Add(hcov24primeGap[icent][ipt][id-4]);
        hcov42primeGap[icent][ipt][id] -> Add(hcov42primeGap[icent][ipt][id-4]);
        hcov44primeGap[icent][ipt][id] -> Add(hcov44primeGap[icent][ipt][id-4]);
        hcov2prime4primeGap[icent][ipt][id] -> Add(hcov2prime4primeGap[icent][ipt][id-4]);
      }
    }
  }


  // Add
  for (int icent=3; icent<5; icent++){ // add 20-30% & 30-40% to 10-20%
    hv22[2] -> Add(hv22[icent]);
    hv24[2] -> Add(hv24[icent]);
    hcov24[2] -> Add(hcov24[icent]);
    hv22Gap[2]-> Add(hv22Gap[icent]);
    hv24Gap[2] -> Add(hv24Gap[icent]);
    hcov24Gap[2] -> Add(hcov24Gap[icent]);
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){ // loop over pid
        hv22pt[2][ipt][id]-> Add(hv22pt[icent][ipt][id]);
        hv24pt[2][ipt][id]-> Add(hv24pt[icent][ipt][id]);
        hcov22prime[2][ipt][id]-> Add(hcov22prime[icent][ipt][id]);
        hcov24prime[2][ipt][id]-> Add(hcov24prime[icent][ipt][id]);
        hcov42prime[2][ipt][id]-> Add(hcov42prime[icent][ipt][id]);
        hcov44prime[2][ipt][id]-> Add(hcov44prime[icent][ipt][id]);
        hcov2prime4prime[2][ipt][id]-> Add(hcov2prime4prime[icent][ipt][id]);
        hv22ptGap[2][ipt][id]->Add(hv22ptGap[icent][ipt][id]);
        hv24ptGap[2][ipt][id]-> Add(hv24ptGap[icent][ipt][id]);
        hcov22primeGap[2][ipt][id]->Add(hcov22primeGap[icent][ipt][id]);
        hcov24primeGap[2][ipt][id]-> Add(hcov24primeGap[icent][ipt][id]);
        hcov42primeGap[2][ipt][id]-> Add(hcov42primeGap[icent][ipt][id]);
        hcov44primeGap[2][ipt][id]-> Add(hcov44primeGap[icent][ipt][id]);
        hcov2prime4primeGap[2][ipt][id]-> Add(hcov2prime4primeGap[icent][ipt][id]);
      }
    } // end of loop over pt bin
  }
  Int_t zero = 0;
  for (int icent=2; icent<3; icent++){ // 10-40
    for (int id=0;id<npid;id++){
      for(int ipt=0; ipt<npt; ipt++){
        MultiparticleCorrelation *standardQC = new MultiparticleCorrelation(
          hv22[icent], hv24[icent], hv22pt[icent][ipt][id], hv24pt[icent][ipt][id],
          hcov22prime[icent][ipt][id], hcov24[icent], hcov24prime[icent][ipt][id],
          hcov42prime[icent][ipt][id], hcov2prime4prime[icent][ipt][id], hcov44prime[icent][ipt][id],
          zero, zero);
        MultiparticleCorrelation *subeventQC = new MultiparticleCorrelation(
          hv22Gap[icent], hv24Gap[icent], hv22ptGap[icent][ipt][id], hv24ptGap[icent][ipt][id],
          hcov22primeGap[icent][ipt][id], hcov24Gap[icent], hcov24primeGap[icent][ipt][id],
          hcov42primeGap[icent][ipt][id], hcov2prime4primeGap[icent][ipt][id], hcov44primeGap[icent][ipt][id],
          zero, zero);

        v2eDif1040[0][id][ipt] = standardQC->GetV22DifErr();
        v2eDif1040[1][id][ipt] = standardQC->GetV24DifErr();
        v2eDif1040[2][id][ipt] = subeventQC->GetV22DifErr();
        v2eDif1040[3][id][ipt] = subeventQC->GetV24DifErr();

      } // end of loop for all pT bin
    } // end of loop for PID
  } // end of loop for centrality
  inFile->Close();
}

void PlotV2QCumulant(){

  // TString inFileName= (TString) Form("../ROOTFile/%s_%s.root",model.Data(),energy.Data());
  // TFile *outFile = new TFile(Form("./v2_%s_%s.root",model.Data(),energy.Data()),"recreate");
  TFile *outFile = new TFile(Form("v2_%s.root",model.Data()),"recreate");

  TString outDirName=(TString)Form("%s_%s_eta_gap_%1.1f",model.Data(),energy.Data(),eta_gap*2);
  TString level= (TString) Form("%s, Au+Au at #sqrt{s_{NN}}=%s",modelFancy.Data(),energy.Data());
  double v2eDif1040[nmethod][npid][npt];
  CalStatErrCent1040(model,energy,v2eDif1040);

  TFile *inFile = new TFile(inputFileName.Data(),"read");


  // Temporary variables
  char hname[800]; // histogram hname

  // Input hist

  // 2,4 QC
  TProfile *hv22[ncent];                            // <2>
  TProfile *hv24[ncent];                            // <4>
  TProfile *hv22pt[ncent][npt][npid];               // <2'>
  TProfile *hv24pt[ncent][npt][npid];               // <4'>
  TProfile *hcov24[ncent];                          // <2><4>
  TProfile *hcov22prime[ncent][npt][npid];          // <2><2'>
  TProfile *hcov24prime[ncent][npt][npid];          // <2><4'>
  TProfile *hcov42prime[ncent][npt][npid];          // <2><4'>
  TProfile *hcov44prime[ncent][npt][npid];          // <4><4'>
  TProfile *hcov2prime4prime[ncent][npt][npid];     // <2'><4'>

  // 2,4 QC 2-sub
  TProfile *hv22Gap[ncent];                         // <2>
  TProfile *hv24Gap[ncent];                         // <4>  
  TProfile *hcov24Gap[ncent];                       // <2><4>
  TProfile *hv22ptGap[ncent][npt][npid];            // <2'>
  TProfile *hv24ptGap[ncent][npt][npid];            // <4'>
  TProfile *hcov22primeGap[ncent][npt][npid];       // <2><2'>  
  TProfile *hcov24primeGap[ncent][npt][npid];       // <2><4'>
  TProfile *hcov42primeGap[ncent][npt][npid];       // <2><4'>
  TProfile *hcov44primeGap[ncent][npt][npid];       // <4><4'>
  TProfile *hcov2prime4primeGap[ncent][npt][npid];  // <2'><4'>

  TProfile *hcounter[ncent][npt][npid];
  // OUTPUT
  TGraphErrors *grDifFl[nmethod][ncent][npid];    // v2(pt); 3 = {2QC, 4QC, EP, gapped 2QC}
  TGraphErrors *grDifFl1040[nmethod][npid];
  
  // FindObjectAny TProfile histograms from ROOTFile

  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent] = (TProfile*)inFile->FindObjectAny(Form("hv22_%i",icent));
    hv24[icent] = (TProfile*)inFile->FindObjectAny(Form("hv24_%i",icent));
    hcov24[icent] = (TProfile*)inFile->FindObjectAny(Form("hcov24_%i",icent));
    hv22Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hv22Gap_%i", icent));
    hv24Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hv24Gap_%i", icent));
    hcov24Gap[icent] = (TProfile*)inFile->FindObjectAny(Form("hcov24Gap_%i", icent));
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid-4;id++){
        hv22pt[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv22pt_%i_%i_%i",icent,ipt,id));
        hv24pt[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv24pt_%i_%i_%i",icent,ipt,id));
        hcov22prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov22prime_%i_%i_%i",icent,ipt,id));
        hcov24prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov24prime_%i_%i_%i",icent,ipt,id));
        hcov42prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov42prime_%i_%i_%i",icent,ipt,id));
        hcov44prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov44prime_%i_%i_%i",icent,ipt,id));
        hcov2prime4prime[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov2prime4prime_%i_%i_%i",icent,ipt,id));
        hv22ptGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv22ptGap_%i_%i_%i",icent,ipt,id));
        hv24ptGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hv24ptGap_%i_%i_%i",icent,ipt,id));
        hcov22primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov22primeGap_%i_%i_%i",icent,ipt,id)); 
        hcov24primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov24primeGap_%i_%i_%i",icent,ipt,id));
        hcov42primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov42primeGap_%i_%i_%i",icent,ipt,id));
        hcov44primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov44primeGap_%i_%i_%i",icent,ipt,id));
        hcov2prime4primeGap[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcov2prime4primeGap_%i_%i_%i",icent,ipt,id));   
        hcounter[icent][ipt][id]=(TProfile*)inFile->FindObjectAny(Form("hcounter_%i_%i_%i",icent,ipt,id));      
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

  //==========================================================================================================================
  for (int icent=0;icent<ncent;icent++){
    for (int ipt=0;ipt<npt;ipt++){
      for (int id=8;id<npid;id++){
        hv22pt[icent][ipt][id] = (TProfile*)  hv22pt[icent][ipt][id-8] -> Clone();
        hv24pt[icent][ipt][id] = (TProfile*)  hv24pt[icent][ipt][id-8] -> Clone();
        hcov22prime[icent][ipt][id] = (TProfile*)  hcov22prime[icent][ipt][id-8] -> Clone();
        hcov24prime[icent][ipt][id] = (TProfile*)  hcov24prime[icent][ipt][id-8] -> Clone();
        hcov42prime[icent][ipt][id] = (TProfile*)  hcov42prime[icent][ipt][id-8] -> Clone();
        hcov44prime[icent][ipt][id] = (TProfile*)  hcov44prime[icent][ipt][id-8] -> Clone();
        hcov2prime4prime[icent][ipt][id] = (TProfile*)  hcov2prime4prime[icent][ipt][id-8] -> Clone();
        hv22ptGap[icent][ipt][id] = (TProfile*)  hv22ptGap[icent][ipt][id-8] -> Clone();
        hv24ptGap[icent][ipt][id] = (TProfile*)  hv24ptGap[icent][ipt][id-8] -> Clone();
        hcov22primeGap[icent][ipt][id] = (TProfile*)  hcov22primeGap[icent][ipt][id-8] -> Clone();
        hcov24primeGap[icent][ipt][id] = (TProfile*)  hcov24primeGap[icent][ipt][id-8] -> Clone();
        hcov42primeGap[icent][ipt][id] = (TProfile*)  hcov42primeGap[icent][ipt][id-8] -> Clone();
        hcov44primeGap[icent][ipt][id] = (TProfile*)  hcov44primeGap[icent][ipt][id-8] -> Clone();
        hcov2prime4primeGap[icent][ipt][id] = (TProfile*)  hcov2prime4primeGap[icent][ipt][id-8] -> Clone();
        hcounter[icent][ipt][id] = (TProfile*)  hcounter[icent][ipt][id-8] -> Clone();

        hv22pt[icent][ipt][id] -> Add(hv22pt[icent][ipt][id-4]);
        hv24pt[icent][ipt][id] -> Add(hv24pt[icent][ipt][id-4]);
        hcov22prime[icent][ipt][id] -> Add(hcov22prime[icent][ipt][id-4]);
        hcov24prime[icent][ipt][id] -> Add(hcov24prime[icent][ipt][id-4]);
        hcov42prime[icent][ipt][id] -> Add(hcov42prime[icent][ipt][id-4]);
        hcov44prime[icent][ipt][id] -> Add(hcov44prime[icent][ipt][id-4]);
        hcov2prime4prime[icent][ipt][id] -> Add(hcov2prime4prime[icent][ipt][id-4]);
        hv22ptGap[icent][ipt][id] -> Add(hv22ptGap[icent][ipt][id-4]);
        hv24ptGap[icent][ipt][id] -> Add(hv24ptGap[icent][ipt][id-4]);
        hcov22primeGap[icent][ipt][id] -> Add(hcov22primeGap[icent][ipt][id-4]);
        hcov24primeGap[icent][ipt][id] -> Add(hcov24primeGap[icent][ipt][id-4]);
        hcov42primeGap[icent][ipt][id] -> Add(hcov42primeGap[icent][ipt][id-4]);
        hcov44primeGap[icent][ipt][id] -> Add(hcov44primeGap[icent][ipt][id-4]);
        hcov2prime4primeGap[icent][ipt][id] -> Add(hcov2prime4primeGap[icent][ipt][id-4]);
        hcounter[icent][ipt][id] -> Add(hcounter[icent][ipt][id-4]);
      }
    }
  }
  
  // Filling pT bin
  double pt[npt];
  double ept[npt]={0}; // error bin pT = 0.0
  for (int ipt=0; ipt<npt; ipt++){
    // pt[icent][ipt][id] = hPT[icent][ipt][id] -> GetBinContent(1);
    pt[ipt] = ( bin_pT[ipt] + bin_pT[ipt+1] ) / 2.;
  }
  
  TProfile *prV2Dif1040[nmethod][npid];
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0; id<npid; id++){
      prV2Dif1040[imeth][id] = new TProfile(Form("prV2Dif1040_%i_%i",imeth,id),"",npt,0.,npt);
    }
  }
  double v2Dif[nmethod][ncent][npid][npt], v2eDif[nmethod][ncent][npid][npt];
  int zero = 0;
  for (int icent=0; icent<ncent; icent++){ // 10-40
    for (int id=0;id<npid;id++){
      for(int ipt=0; ipt<npt; ipt++){
        MultiparticleCorrelation *standardQC = new MultiparticleCorrelation(
          hv22[icent], hv24[icent], hv22pt[icent][ipt][id], hv24pt[icent][ipt][id],
          hcov22prime[icent][ipt][id], hcov24[icent], hcov24prime[icent][ipt][id],
          hcov42prime[icent][ipt][id], hcov2prime4prime[icent][ipt][id], hcov44prime[icent][ipt][id],
          zero, zero);
        MultiparticleCorrelation *subeventQC = new MultiparticleCorrelation(
          hv22Gap[icent], hv24Gap[icent], hv22ptGap[icent][ipt][id], hv24ptGap[icent][ipt][id],
          hcov22primeGap[icent][ipt][id], hcov24Gap[icent], hcov24primeGap[icent][ipt][id],
          hcov42primeGap[icent][ipt][id], hcov2prime4primeGap[icent][ipt][id], hcov44primeGap[icent][ipt][id],
          zero, zero);

        v2Dif[0][icent][id][ipt] = standardQC->GetV22Dif();
        v2eDif[0][icent][id][ipt] = standardQC->GetV22DifErr();
        v2Dif[1][icent][id][ipt] = standardQC->GetV24Dif();
        v2eDif[1][icent][id][ipt] = standardQC->GetV24DifErr();
        v2Dif[2][icent][id][ipt] = subeventQC->GetV22Dif();
        v2eDif[2][icent][id][ipt] = subeventQC->GetV22DifErr();
        v2Dif[3][icent][id][ipt] = subeventQC->GetV24Dif();
        v2eDif[3][icent][id][ipt] = subeventQC->GetV24DifErr();
        if (icent>=2 && icent <=4) { // 10-40%

          prV2Dif1040[0][id] -> Fill(0.5+ipt,standardQC->GetV22Dif(),hcounter[icent][ipt][id] -> GetBinEntries(1));
          prV2Dif1040[1][id] -> Fill(0.5+ipt,standardQC->GetV24Dif(),hcounter[icent][ipt][id] -> GetBinEntries(1));
          prV2Dif1040[2][id] -> Fill(0.5+ipt,subeventQC->GetV22Dif(),hcounter[icent][ipt][id] -> GetBinEntries(2));
          prV2Dif1040[3][id] -> Fill(0.5+ipt,subeventQC->GetV24Dif(),hcounter[icent][ipt][id] -> GetBinEntries(2));
        }
        // delete standardQC;
        // delete subeventQC;

      } // end of loop for all pT bin
      
      for (int i=0; i<nmethod; i++){
        grDifFl[i][icent][id] = new TGraphErrors(npt,pt,v2Dif[i][icent][id],ept,v2eDif[i][icent][id]);
        grDifFl[i][icent][id] -> SetMarkerStyle(marker[i]);
        grDifFl[i][icent][id] -> SetMarkerSize(1.5);
        grDifFl[i][icent][id] -> SetDrawOption("P");
      }

    } // end of loop for PID
  } // end of loop for centrality

  double v2Dif1040[nmethod][npid][npt];
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      for(int ipt=0; ipt<npt; ipt++){
        v2Dif1040[imeth][id][ipt] = prV2Dif1040[imeth][id] -> GetBinContent(ipt+1);
      }
      grDifFl1040[imeth][id] = new TGraphErrors(npt,pt,v2Dif1040[imeth][id],ept,v2eDif1040[imeth][id]);
      grDifFl1040[imeth][id] -> SetMarkerStyle(marker[imeth]);
      grDifFl1040[imeth][id] -> SetMarkerSize(1.5);
      grDifFl1040[imeth][id] -> SetDrawOption("P");
    }
  }

  const char *grTitle[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{2,|#Delta#eta|>0.1}","v_{2}{4,|#Delta#eta|>0.1}"};
  outFile -> cd();
  for (int imeth=0; imeth<nmethod; imeth++){
    for (int id=0;id<npid;id++){
      grDifFl1040[imeth][id] -> SetTitle(grTitle[imeth]);
      grDifFl1040[imeth][id]->GetYaxis()-> SetTitle("v_{2}");
      grDifFl1040[imeth][id]->GetXaxis()-> SetTitle("p_{T}, GeV/c");
      grDifFl1040[imeth][id] -> Write(Form("gr_cent10-40_%i_%i",imeth,id));
      for (int icent=0;icent<ncent;icent++){
        grDifFl[imeth][icent][id] -> SetTitle(grTitle[imeth]);
        grDifFl[imeth][icent][id]->GetYaxis()-> SetTitle("v_{2}");
        grDifFl[imeth][icent][id]->GetXaxis()-> SetTitle("p_{T}, GeV/c");
        grDifFl[imeth][icent][id] -> Write(Form("gr_cent%i_%i_%i",icent,imeth,id));
      }
    }
  }

  if (saveAsPNG) gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
  TCanvas *cV2PT[ncent][npid];
  for (int icent=0; icent<drawDifferentialFlowTill; icent++){
    for (int id=0;id<npid;id++){
      std::vector<TGraphErrors*> vgrv2pt;
      vgrv2pt.push_back(grDifFl[ratioToMethod][icent][id]); // v2{gapped 2QC}
      for (int i=0; i<nmethod; i++){
        if (i==ratioToMethod) continue;
        vgrv2pt.push_back(grDifFl[i][icent][id]);
      }
      sprintf(hname,"%s, %i-%i%%",pidFancyNames.at(id).Data(),centrality.at(icent).first,centrality.at(icent).second);
      cV2PT[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt,"",rangeRatio.at(0).first, rangeRatio.at(0).second, minpt, maxpt, minV2dif, maxV2dif,
                                               coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                               level.Data(), hname, true, grTitle[ratioToMethod]);
      cV2PT[icent][id] -> SetName(hname);
      if (saveAsPNG) cV2PT[icent][id] -> SaveAs(Form("./%s/DifferentialFlow_Centrality%i-%i_%s.png",outDirName.Data(),centrality.at(icent).first,centrality.at(icent).second,pidNames.at(id).Data()));
    }
  }

  TCanvas *cV2PT1040[npid];
  for (int id=0;id<npid;id++){
    std::vector<TGraphErrors*> vgrv2pt1040;
    vgrv2pt1040.push_back(grDifFl1040[ratioToMethod][id]);
    // vgrv2pt1040.push_back(grDifFl1040[3][id]);
    for (int imeth=0;imeth<nmethod;imeth++){
      if (imeth==ratioToMethod) continue;
      vgrv2pt1040.push_back(grDifFl1040[imeth][id]);
    }
    sprintf(hname,"10-40%%, %s",pidFancyNames.at(id).Data());
    cV2PT1040[id] = (TCanvas*) DrawTGraph(vgrv2pt1040,"",rangeRatio.at(0).first, rangeRatio.at(0).second, minpt, 3.0, minV2dif, maxV2dif,
                                          coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                          level.Data(), hname, true, grTitle[ratioToMethod]);
    cV2PT1040[id] -> SetName(hname);
    if (saveAsPNG) cV2PT1040[id] -> SaveAs(Form("./%s/DifferentialFlow_Centrality10-40%%_%s.png",outDirName.Data(),pidNames.at(id).Data()));
    // if (saveAsPNG) cV2PT1040[id] -> SaveAs(Form("./%s/DifferentialFlow_Centrality10-40%%_%s.pdf",outDirName.Data(),pidNames.at(id).Data()));
  }
  //==========================================================================================================================
  TGraphErrors *grIntFlPID[nmethod][npid];    // v2(pt); 3 = {2QC, 4QC, 2QCgap, 4QCgap}
  TGraphErrors *grRefFl[nmethod];
  
  // v2 vs centrality for PID
  for (int icent=0;icent<ncent;icent++){
    for (int id=0;id<npid;id++){
      for (int ipt=binMinPtRFP+1;ipt<binMaxPtRFP;ipt++){
        hv22pt[icent][binMinPtRFP][id]              -> Add(hv22pt[icent][ipt][id]);
        hv24pt[icent][binMinPtRFP][id]              -> Add(hv24pt[icent][ipt][id]);
        hcov22prime[icent][binMinPtRFP][id]         -> Add(hcov22prime[icent][ipt][id]);
        hcov24prime[icent][binMinPtRFP][id]         -> Add(hcov24prime[icent][ipt][id]);
        hcov42prime[icent][binMinPtRFP][id]         -> Add(hcov42prime[icent][ipt][id]);
        hcov44prime[icent][binMinPtRFP][id]         -> Add(hcov44prime[icent][ipt][id]);
        hcov2prime4prime[icent][binMinPtRFP][id]    -> Add(hcov2prime4prime[icent][ipt][id]);
        hv22ptGap[icent][binMinPtRFP][id]           -> Add(hv22ptGap[icent][ipt][id]);
        hv24ptGap[icent][binMinPtRFP][id]           -> Add(hv24ptGap[icent][ipt][id]);
        hcov22primeGap[icent][binMinPtRFP][id]      -> Add(hcov22primeGap[icent][ipt][id]);
        hcov24primeGap[icent][binMinPtRFP][id]      -> Add(hcov24primeGap[icent][ipt][id]);
        hcov42primeGap[icent][binMinPtRFP][id]      -> Add(hcov42primeGap[icent][ipt][id]);
        hcov44primeGap[icent][binMinPtRFP][id]      -> Add(hcov44primeGap[icent][ipt][id]);
        hcov2prime4primeGap[icent][binMinPtRFP][id] -> Add(hcov2prime4primeGap[icent][ipt][id]);
      }
    }
  }
  double v2[nmethod][npid][ncent], v2e[nmethod][npid][ncent];
  double v2_RF[nmethod][ncent],    v2e_RF[nmethod][ncent];
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes

    MultiparticleCorrelation *standardQCRef = new MultiparticleCorrelation(hv22[icent], hv24[icent], hcov24[icent], zero);
    MultiparticleCorrelation *subeventQCRef = new MultiparticleCorrelation(hv22Gap[icent], hv24Gap[icent], hcov24Gap[icent], zero);

    v2_RF[0][icent] = standardQCRef->GetV22Ref();
    v2e_RF[0][icent] = standardQCRef->GetV22RefErr();
    v2_RF[1][icent] = standardQCRef->GetV24Ref();
    v2e_RF[1][icent] = standardQCRef->GetV24RefErr();
    v2_RF[2][icent] = subeventQCRef->GetV22Ref();
    v2e_RF[2][icent] = subeventQCRef->GetV22RefErr();
    v2_RF[3][icent] = subeventQCRef->GetV24Ref();
    v2e_RF[3][icent] = subeventQCRef->GetV24RefErr();
    std::cout << "v22etasub = " << subeventQCRef->GetV22Ref() << ", v22 = " << standardQCRef->GetV22Ref() << std::endl;

  } // end of loop over centrality classes
  // Differential flow calculation
  for (Int_t id = 0; id<npid; id++){
    for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
      for(int ipt=binMinPtRFP; ipt<binMinPtRFP+1; ipt++){ // loop for all pT bin
        MultiparticleCorrelation *standardQC = new MultiparticleCorrelation(
          hv22[icent], hv24[icent], hv22pt[icent][ipt][id], hv24pt[icent][ipt][id],
          hcov22prime[icent][ipt][id], hcov24[icent], hcov24prime[icent][ipt][id],
          hcov42prime[icent][ipt][id], hcov2prime4prime[icent][ipt][id], hcov44prime[icent][ipt][id],
          zero, zero);
        MultiparticleCorrelation *subeventQC = new MultiparticleCorrelation(
          hv22Gap[icent], hv24Gap[icent], hv22ptGap[icent][ipt][id], hv24ptGap[icent][ipt][id],
          hcov22primeGap[icent][ipt][id], hcov24Gap[icent], hcov24primeGap[icent][ipt][id],
          hcov42primeGap[icent][ipt][id], hcov2prime4primeGap[icent][ipt][id], hcov44primeGap[icent][ipt][id],
          zero, zero);

        v2[0][id][icent] = standardQC->GetV22Dif();
        v2e[0][id][icent] = standardQC->GetV22DifErr();
        v2[1][id][icent] = standardQC->GetV24Dif();
        v2e[1][id][icent] = standardQC->GetV24DifErr();
        v2[2][id][icent] = subeventQC->GetV22Dif();
        v2e[2][id][icent] = subeventQC->GetV22DifErr();
        v2[3][id][icent] = subeventQC->GetV24Dif();
        v2e[3][id][icent] = subeventQC->GetV24DifErr();

        
      } // end of loop for all pT bin
    } // end of loop over centrality classes
  } // end of loop over PID
  for (int imeth=0; imeth<nmethod; imeth++){
    grRefFl[imeth] = new TGraphErrors(ncent,bin_cent,v2_RF[imeth],bin_centE,v2e_RF[imeth]);
    grRefFl[imeth] -> SetMarkerStyle(marker[imeth]);
    grRefFl[imeth] -> SetMarkerSize(1.5);
    for (int id=0; id<npid; id++){
      grIntFlPID[imeth][id] = new TGraphErrors(ncent,bin_cent,v2[imeth][id],bin_centE,v2e[imeth][id]);
      grIntFlPID[imeth][id] -> SetMarkerStyle(marker[imeth]);
      grIntFlPID[imeth][id] -> SetMarkerSize(1.5);
    }
  }

  outFile -> cd();
  for (int imeth=0; imeth<nmethod; imeth++){

    for (int id=0;id<npid;id++){
      if (id==8) continue;
      grIntFlPID[imeth][id] -> SetTitle(grTitle[imeth]);
      grIntFlPID[imeth][id] -> GetYaxis()-> SetTitle("v_{2}");
      grIntFlPID[imeth][id] -> GetXaxis()-> SetTitle("Centrality, %");
      grIntFlPID[imeth][id] -> Write(Form("grRF_%i_%i",imeth,id));
    }
  
  }

  std::vector<TGraphErrors*> vgrv2cent[npid];
    for (int id=0;id<npid;id++){
      if (id==8) continue;  
      vgrv2cent[id].push_back(grIntFlPID[ratioToMethod][id]); // v2{gapped 2QC}
      for (int i=0; i<nmethod; i++){
        if (i==ratioToMethod) continue;
        vgrv2cent[id].push_back(grIntFlPID[i][id]);
      }
    }
  
  TCanvas *cV2Cent[npid];
  for (int id=0;id<npid;id++){
    if (id==8) continue;
    cV2Cent[id] = (TCanvas*) DrawTGraph(vgrv2cent[id],"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second, mincent, maxcent, minV2int, maxV2int,
                                        coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                        level.Data(), Form("%s, %1.1f<p_{T}<%1.1f",pidFancyNames.at(id).Data(),bin_pT[binMinPtRFP],bin_pT[binMaxPtRFP]),true,grTitle[ratioToMethod]);

    cV2Cent[id] -> SetName(pidFancyNames.at(id).Data());
    if (saveAsPNG) cV2Cent[id] -> SaveAs(Form("./%s/IntegratedFlow_%s.png",outDirName.Data(),pidNames.at(id).Data()));
  }
  

  TCanvas *cV2CentRF;

  std::vector<TGraphErrors*> vgrv2cent_chargedHardons;
  for (int imeth=0; imeth<nmethod; imeth++){
    // grRefFl[imeth][id] -> SetTitle(Form("V2 vs. pT, %s, centrality 10-40%%, %s",pidNames.at(id).Data(),grTitleDF[imeth]));
    grRefFl[imeth] -> SetTitle(grTitle[imeth]);
    grRefFl[imeth]->GetYaxis()-> SetTitle("v_{2}");
    grRefFl[imeth]->GetXaxis()-> SetTitle("Centrality, %");
  }
  grRefFl[0] -> Write(Form("grRF_%i_0",0)); // v22
  grRefFl[1] -> Write(Form("grRF_%i_0",1)); // v24
  grRefFl[2] -> Write(Form("grRF_%i_0",3)); // v22gap
  grRefFl[3] -> Write(Form("grRF_%i_0",2)); // v24gap

  // vgrv2cent_chargedHardons.push_back(grRefFl[ratioToMethod]);
  grRefFl[ratioToMethod]->RemovePoint(0);
  grRefFl[3]->RemovePoint(0);
  vgrv2cent_chargedHardons.push_back(grRefFl[ratioToMethod]);
  // vgrv2cent_chargedHardons.push_back(grRefFl[3]);
  for (int imeth=0;imeth<nmethod;imeth++){
    if (imeth==ratioToMethod) continue;
    vgrv2cent_chargedHardons.push_back(grRefFl[imeth]);
    
  }
  cV2CentRF = (TCanvas*) DrawTGraph(vgrv2cent_chargedHardons,"",rangeRatioRF.at(0).first, rangeRatioRF.at(0).second, mincent, maxcent, minV2int, maxV2int,
                                    coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                    level.Data(), Form("h^{#pm}, %1.1f<p_{T}<%1.1f GeV/c",minptRFP,maxptRFP),true,grTitle[ratioToMethod]);
  cV2CentRF -> SetName("Reference flow");
  if (saveAsPNG) cV2CentRF -> SaveAs(Form("./%s/IntegratedFlow_hadron.png",outDirName.Data()));
  // if (saveAsPNG) cV2CentRF -> SaveAs(Form("./%s/IntegratedFlow_hadron.pdf",outDirName.Data()));

  inFile->Close();
}

int main()
{
  PlotV2QCumulant();
  return 0;
}