#include "DrawTGraph.C"
void Compare1040(){

  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim[3], *grVinh[3];
  char name[400];

  inputDim = new TFile("Dim.root","read");
  for (int i=0; i<3; i++){

    sprintf(name,"gr_cent1_%i",i);
    grDim[i] = (TGraphErrors*)inputDim->Get(name);
    grDim[i] -> SetTitle("Dim; p_{T}, GeV/c; v_{2}");
    // grDim[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
    // grDim[icent][i] -> GetXaxis()-> SetTitle("p_{T}, GeV/c");
    // grDim[icent][i] -> Draw("AP");
    // grDim[icent][i] -> SetMinimum(0.);
    // grDim[icent][i] -> SetMaximum(0.25);

  }

  inputVinh = new TFile("Vinh.root","read");
  for (int i=0; i<3; i++){

      sprintf(name,"gr_cent1_%i",i);
      grVinh[i] = (TGraphErrors*)inputVinh->Get(name);
      grVinh[i] -> SetTitle("Vinh; p_{T}, GeV/c; v_{2}");
      // grVinh[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
      // grVinh[icent][i] -> GetYaxis()-> SetLimits(0.,0.25);
      // grVinh[icent][i] -> Draw("AP");

  }  


  TCanvas *can[3];
  char *ch[3]={"v2{#eta sub-event}","v2{2QC}","v2{4QC}"};
  for (int i=0; i<3; i++){
      sprintf(name,"Centrality 10-40%%");
      can[i] = (TCanvas*) DrawTGraph(grDim[i],grVinh[i],ch[i],0.69,1.31,0.,2.8,0,0.25,0.18,0.72,0.42,0.89,name);
      sprintf(name,"%s_Cent10-40.png",ch[i]);
      can[i] -> SetName(name);
      can[i] -> SaveAs(name);
  }

  
}


