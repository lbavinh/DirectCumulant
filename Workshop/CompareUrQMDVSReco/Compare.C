#include "DrawTGraph.C"
void Compare(){

  TFile *inputVinhUrQMD[2], *inputVinhReco[2];
  TGraphErrors *grReco[2][3], *grUrQMD[2][3];
  char name[400];

  inputVinhReco[0] = new TFile("Vinh_Reco.root","read");
  for (int i=0; i<3; i++){
    sprintf(name,"gr_cent1_%i",i);
    grReco[0][i] = (TGraphErrors*)inputVinhReco[0]->Get(name);
    grReco[0][i] -> SetTitle("Reco MPD;p_{T}, GeV/c;v_{2}");

  }

  inputVinhUrQMD[0] = new TFile("Vinh_UrQMD.root","read");
  for (int i=0; i<3; i++){
    sprintf(name,"gr_cent1_%i",i);
    grUrQMD[0][i] = (TGraphErrors*)inputVinhUrQMD[0]->Get(name);
    grUrQMD[0][i] -> SetTitle("UrQMD;p_{T}, GeV/c;v_{2}");
  }  

  inputVinhReco[1] = new TFile("Vinh_Reco_RF.root","read");
  for (int i=0; i<3; i++){
    sprintf(name,"grRF_%i",i);
    grReco[1][i] = (TGraphErrors*)inputVinhReco[1]->Get(name);
    grReco[1][i] -> SetTitle("Reco MPD;cent, %;v_{2}");

  }

  inputVinhUrQMD[1] = new TFile("Vinh_UrQMD_RF.root","read");
  for (int i=0; i<3; i++){
    sprintf(name,"grRF_%i",i);
    grUrQMD[1][i] = (TGraphErrors*)inputVinhUrQMD[1]->Get(name);
    grUrQMD[1][i] -> SetTitle("UrQMD;cent, %;v_{2}");
  }  


  TCanvas *can[2][3];
  char *ch[3]={"v2{#eta sub-event}","v2{2QC}","v2{4QC}"};
  for (int i=0; i<3; i++){
      sprintf(name,"Centrality 10-40%%");
      can[0][i] = (TCanvas*) DrawTGraph(grReco[0][i],grUrQMD[0][i],ch[i],0.69,1.31,0.,2.5,-0.01,0.2,0.18,0.72,0.42,0.89,name);
      sprintf(name,"%s_Cent10-40.png",ch[i]);
      can[0][i] -> SetName(name);
      can[0][i] -> SaveAs(name);
  }
  for (int i=0; i<3; i++){
      sprintf(name,"");
      can[1][i] = (TCanvas*) DrawTGraph(grReco[1][i],grUrQMD[1][i],ch[i],0.69,1.31,0.,60,-0.01,0.1,0.18,0.72,0.42,0.89,name);
      sprintf(name,"%s_v2cent.png",ch[i]);
      can[1][i] -> SetName(name);
      can[1][i] -> SaveAs(name);
  }
  
}


