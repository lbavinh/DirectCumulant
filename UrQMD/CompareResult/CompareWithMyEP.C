#include "DrawTGraph.C"
void CompareWithMyEP(){
  static const int ncent = 8;
  TFile *inputDim, *inputVinh;
  TGraphErrors *grDim[ncent][3], *grVinh[ncent][3];
  char name[400];

  inputDim = new TFile("Dim.root","read");
  for (int icent=0; icent<ncent; icent++){
    for (int i=0; i<3; i++){
      sprintf(name,"gr_cent%i_%i",icent,i);
      grDim[icent][i] = (TGraphErrors*)inputDim->Get(name);
      // grDim[icent][i] -> SetTitle("Dim; p_{T}, GeV/c; v_{2}");
      // grDim[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
      // grDim[icent][i] -> GetXaxis()-> SetTitle("p_{T}, GeV/c");
      // grDim[icent][i] -> Draw("AP");
      // grDim[icent][i] -> SetMinimum(0.);
      // grDim[icent][i] -> SetMaximum(0.25);
    }
    grDim[icent][0] -> SetTitle("v_2{#eta sub-evt}Dim; p_{T}, GeV/c; v_{2}");
    grDim[icent][1] -> SetTitle("v_2{2}Dim; p_{T}, GeV/c; v_{2}");
    grDim[icent][2] -> SetTitle("v_2{4}Dim; p_{T}, GeV/c; v_{2}");
  }

  inputVinh = new TFile("Vinh.root","read");
  for (int icent=0; icent<ncent; icent++){
    for (int i=0; i<3; i++){
      sprintf(name,"gr_cent%i_%i",icent,i);
      grVinh[icent][i] = (TGraphErrors*)inputVinh->Get(name);
      // grVinh[icent][i] -> GetXaxis()-> SetLimits(0.,2.8);
      // grVinh[icent][i] -> GetYaxis()-> SetLimits(0.,0.25);
      // grVinh[icent][i] -> Draw("AP");
    }
    grVinh[icent][0] -> SetTitle("v_2{#eta sub-evt}Vinh; p_{T}, GeV/c; v_{2}");


    grVinh[icent][1] -> SetTitle("v_2{2}Vinh; p_{T}, GeV/c; v_{2}");
    grVinh[icent][1] -> SetMarkerColor(kGreen+1);
    grVinh[icent][1] -> SetMarkerStyle(20);

    grVinh[icent][2] -> SetTitle("v_2{4}Vinh; p_{T}, GeV/c; v_{2}");
    grVinh[icent][2] -> SetMarkerColor(kAzure+2);
    grVinh[icent][2] -> SetMarkerStyle(22);
    
  }  


  std::vector<TGraphErrors*> vgrv2pt[8];
  for (int icent=0; icent<8; icent++){
    for (int i=0; i<3; i++){
      vgrv2pt[icent].push_back(grVinh[i][icent]);
    }  
  }
  for (int icent=0; icent<8; icent++){
    for (int i=1; i<3; i++){
      vgrv2pt[icent].push_back(grDim[i][icent]);
    }  
  }
  TCanvas *cV2PT[8];
  // TLatex lV2PT[8];
  TPaveText *ptext[8];

  for (int icent=0; icent<6; icent++){
    sprintf(name,"Centrality %i-%i%%",icent*10,(icent+1)*10);
    //                                                           yRatio_low   x_low     y_low    leg_x_low  leg_x_high
    cV2PT[icent] = (TCanvas*) DrawTGraph(vgrv2pt[icent],"",0.65, 1.35, 0., 2.8, 0., 0.25, 0.18, 0.65, 0.42, 0.89, name);
    //                                                                yRatio_high  x_high   y_high     leg_y_low   leg_y_high
    sprintf(name,"Cent %i-%i%%",icent*10,(icent+1)*10);
    cV2PT[icent] -> SetName(name);

    // lV2PT[icent].SetNDC();
    // lV2PT[icent].SetTextSize(0.12);
    // lV2PT[icent].SetTextAlign(21);  
    // lV2PT[icent].DrawLatex(0.5,0.1,hname);
    sprintf(name,"DFCent%i-%i%%.png",icent*10,(icent+1)*10);
    cV2PT[icent] -> SaveAs(name);
  }
}


