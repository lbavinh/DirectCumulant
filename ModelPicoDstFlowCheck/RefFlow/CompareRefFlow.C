#include "DrawTGraph.C"
void CompareRefFlow(){
  static const int ncent = 8;
  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim[3], *grVinh[3];
  char name[400];

  inputDim = new TFile("Dim.root","read");
  for (int i=0; i<3; i++){
    sprintf(name,"grRF_%i",i);
    grDim[i] = (TGraphErrors*)inputDim->Get(name);
    grDim[i] -> SetTitle("Dim;Centrality, %;v_{2}");
    // grDim[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
    // grDim[icent][i] -> GetXaxis()-> SetTitle("p_{T}, GeV/c");
    // grDim[icent][i] -> Draw("AP");
    // grDim[icent][i] -> SetMinimum(0.);
    // grDim[icent][i] -> SetMaximum(0.25);
  }

  inputVinh = new TFile("Vinh.root","read");
  for (int i=0; i<3; i++){
      sprintf(name,"grRF_%i",i);
      grVinh[i] = (TGraphErrors*)inputVinh->Get(name);
      grVinh[i] -> SetTitle("Vinh;Centrality, %;v_{2}");
      // grVinh[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
      // grVinh[icent][i] -> GetYaxis()-> SetLimits(0.,0.25);
      // grVinh[icent][i] -> Draw("AP");
  }  


  TCanvas *can[3];
  char *ch[3]={"v2{#eta sub-event}","v2{2QC}","v2{4QC}"};
  for (int i=0; i<3; i++){
    sprintf(name,"");
    can[i] = (TCanvas*) DrawTGraph(grDim[i],grVinh[i],ch[i],0.95,1.05,0.,80,0,0.06,0.18,0.72,0.42,0.89,name);
    sprintf(name,"%s.png",ch[i]);
    can[i] -> SetName(name);
    can[i] -> SaveAs(name);
  }
}


