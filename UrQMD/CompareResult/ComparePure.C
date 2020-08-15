#include "DrawTGraph.C"
void ComparePure(){
  static const int ncent = 8;
  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim[ncent][3], *grVinh[ncent][3];
  char name[400];

  inputDim = new TFile("Dim.root","read");
  for (int i=0; i<3; i++){
    for (int icent=0; icent<ncent; icent++){
      sprintf(name,"gr_cent%i_%i",icent,i);
      grDim[icent][i] = (TGraphErrors*)inputDim->Get(name);
      grDim[icent][i] -> SetTitle("Dim; p_{T}, GeV/c; v_{2}");
      // grDim[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
      // grDim[icent][i] -> GetXaxis()-> SetTitle("p_{T}, GeV/c");
      // grDim[icent][i] -> Draw("AP");
      // grDim[icent][i] -> SetMinimum(0.);
      // grDim[icent][i] -> SetMaximum(0.25);
    }
  }

  inputVinh = new TFile("Vinh.root","read");
  for (int i=0; i<3; i++){
    for (int icent=0; icent<ncent; icent++){
      sprintf(name,"gr_%i_%i",icent,i);
      grVinh[icent][i] = (TGraphErrors*)inputVinh->Get(name);
      grVinh[icent][i] -> SetTitle("Vinh; p_{T}, GeV/c; v_{2}");
      // grVinh[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
      // grVinh[icent][i] -> GetYaxis()-> SetLimits(0.,0.25);
      // grVinh[icent][i] -> Draw("AP");
    }
  }  


  TCanvas *can[ncent][3];
  TLatex l[8][3];
  char *ch[3]={"v2{#eta sub-event}","v2{2QC}","v2{4QC}"};
  for (int i=0; i<3; i++){
    for (int icent=0;icent<8;icent++){
      sprintf(name,"Centrality %i-%i%%",icent*10,(icent+1)*10);
      can[icent][i] = (TCanvas*) DrawTGraph(grDim[icent][i],grVinh[icent][i],ch[i],0.69,1.31,0.,2.8,0,0.6,0.18,0.72,0.42,0.89,name);
      sprintf(name,"%s_Cent%i-%i%%.png",ch[i], icent*10,(icent+1)*10);
      can[icent][i] -> SetName(name);
      can[icent][i] -> SaveAs(name);
    }
  }
}


