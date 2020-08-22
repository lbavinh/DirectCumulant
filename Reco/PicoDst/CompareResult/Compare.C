#include "DrawTGraph.C"
void Compare(){
  static const int ncent = 1;
  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim[3], *grVinh[3];
  char name[400];

  inputDim = new TFile("Dim.root","read");
  for (int i=0; i<3; i++){
    sprintf(name,"gr_cent1_%i",i);
    grDim[i] = (TGraphErrors*)inputDim->Get(name);
    grDim[i] -> SetTitle("Dim; p_{T}, GeV/c; v_{2}");

  }

  inputVinh = new TFile("Vinh.root","read");
  for (int i=0; i<3; i++){

    sprintf(name,"gr_cent1_%i",i);
    grVinh[i] = (TGraphErrors*)inputVinh->Get(name);
    grVinh[i] -> SetTitle("Vinh; p_{T}, GeV/c; v_{2}");

  }  


  TCanvas *can[3];
  char *ch[3]={"v2{#eta sub-event}","v2{2QC}","v2{4QC}"};
  for (int i=0; i<3; i++){
    can[i] = (TCanvas*) DrawTGraph(grDim[i],grVinh[i],ch[i],0.84,1.16,0.,2.8,0,0.2,0.18,0.72,0.42,0.89,"Centrality 10-40%");
    sprintf(name,"Centrality 10-40%i.png",i);
    can[i] -> SetName(name);
    can[i] -> SaveAs(name);

  }
}


