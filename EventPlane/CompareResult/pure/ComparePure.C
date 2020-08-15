#include "DrawTGraph.C"
void ComparePure(){
  static const int ncent = 8;
  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim[ncent][4], *grVinh[ncent][4];
  char name[400];

  inputDim = new TFile("Dim.root","read");
  for (int i=0; i<4; i++){
    for (int icent=0; icent<ncent; icent++){
      sprintf(name,"gr_cent%i_%i",icent,i);
      grDim[icent][i] = (TGraphErrors*)inputDim->Get(name);
      grDim[icent][i] -> SetTitle("Dim; p_{T}, GeV/c; v_{2}");
      // grDim[icent][i] -> GetXaxis()-> SetTitle("p_{T}, GeV/c");
      grDim[icent][i] -> Draw("AP");
      grDim[icent][i] -> SetMinimum(0.);
      grDim[icent][i] -> SetMaximum(0.25);
    }
  }

  inputVinh = new TFile("Vinh.root","read");
  for (int i=0; i<4; i++){
    for (int icent=0; icent<ncent; icent++){
      sprintf(name,"gr_%i_%i",icent,i);
      grVinh[icent][i] = (TGraphErrors*)inputVinh->Get(name);
      grVinh[icent][i] -> SetTitle("Vinh");
      // grVinh[icent][i] -> GetXaxis()-> SetLimits(0.,3.5);
      // grVinh[icent][i] -> GetYaxis()-> SetLimits(0.,0.25);
    }
  }  

  TCanvas *can[ncent][4];
  TLatex l[8][4];
  char *ch[4]={"v2{MC}", "v2{2QC}", "v2{4QC}", "v2{EP}"};
  for (int i=0; i<4; i++){
    for (int icent=1;icent<6;icent++){
      can[icent][i] = (TCanvas*) DrawTGraph(grDim[icent][i],grVinh[icent][i],ch[i]);
      sprintf(name,"Cent %i-%i%%",icent*10,(icent+1)*10);
      l[icent][i].SetNDC();
      l[icent][i].SetTextSize(0.12);
      l[icent][i].SetTextAlign(21);  
      l[icent][i].DrawLatex(0.5,0.1,name);
      sprintf(name,"%s_Cent%i-%i%%.png",ch[i], icent*10,(icent+1)*10);
      can[icent][i] -> SetName(name);
      can[icent][i] -> SaveAs(name);
    }
  }
}

/*

t->SetTextAlign(13); //align at top left
t->SetTextAlign(12); // left, vertically centered
t->SetTextAlign(22); // centered horizontally and vertically
t->SetTextAlign(11); //default bottom alignment

*/
