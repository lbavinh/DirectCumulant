#include "DrawTGraph.C"
void CompareRes2(){

  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim, *grVinh;
  char name[400];

  inputDim = new TFile("Dim.root","read");
  sprintf(name,"Res");
  grDim = (TGraphErrors*)inputDim->Get(name);
  grDim -> SetTitle("Dim;Centrality, %;R_{2}{#Psi_{2}}");

  inputVinh = new TFile("Vinh.root","read");
  sprintf(name,"res2");
  grVinh = (TGraphErrors*)inputVinh->Get(name);
  grVinh -> SetTitle("Vinh;Centrality, %;R_{2}{#Psi_{2}}");
  // grVinh[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
  // grVinh[icent][i] -> GetYaxis()-> SetLimits(0.,0.25);
  // grVinh[icent][i] -> Draw("AP");



  TCanvas *can;


  // sprintf(name,"Centrality %i-%i%%",icent*10,(icent+1)*10);
  can = (TCanvas*) DrawTGraph(grDim,grVinh,"R_{2}{#Psi_{2}}",0.89,1.11,0.,80.,0,1.,0.18,0.72,0.42,0.89,"");
  sprintf(name,"CompareRes2.png");
  can -> SetName(name);
  can -> SaveAs(name);
}


