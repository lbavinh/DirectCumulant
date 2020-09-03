#include "DrawTGraph.C"
void Compare(){
  static const int npid = 4; // charged hadrons, pions, kaons, protons
  static const int nmethod = 3; // 2QC, 4QC, EP
  const char *particle[4]={"Charged hadrons","Pions","Kaons","Protons"};
  TFile *inputVinhMC, *inputVinhReco;
  TGraphErrors *grReco[2][nmethod][npid], *grMC[2][nmethod][npid];
  char name[400];

  inputVinhReco = new TFile("VinhPID_UrQMD.root","read");
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      grReco[0][i][id] = (TGraphErrors*)inputVinhReco->Get(Form("gr_cent10-40_%i_%i",i,id));
      grReco[0][i][id] -> SetTitle("UrQMD;p_{T}, GeV/c;v_{2}");
      grReco[1][i][id] = (TGraphErrors*)inputVinhReco->Get(Form("grRF_%i_%i",i,id));
      grReco[1][i][id] -> SetTitle("UrQMD;cent, %;v_{2}");
    }
  }

  inputVinhMC = new TFile("VinhPID_MC.root","read");
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      grMC[0][i][id] = (TGraphErrors*)inputVinhMC->Get(Form("gr_cent10-40_%i_%i",i,id));
      grMC[0][i][id] -> SetTitle("MC tracks;p_{T}, GeV/c;v_{2}");
      grMC[1][i][id] = (TGraphErrors*)inputVinhMC->Get(Form("grRF_%i_%i",i,id));
      grMC[1][i][id] -> SetTitle("MC tracks;cent, %;v_{2}");
    }
  }


  TCanvas *can[2][nmethod][npid];
  char *method[3]={"v2{2QC}","v2{4QC}","v2{#eta sub-event}"};
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      sprintf(name,"%s, centrality 10-40%%",particle[id]);
      can[0][i][id] = (TCanvas*) DrawTGraph(grReco[0][i][id],grMC[0][i][id],method[i],0.69,1.31,0.,2.5,-0.01,0.2,0.18,0.72,0.42,0.89,name);
      sprintf(name,"%s_%s_Cent10-40.png",method[i],particle[id]);
      can[0][i][id] -> SetName(name);
      can[0][i][id] -> SaveAs(name);
      can[1][i][id] = (TCanvas*) DrawTGraph(grReco[1][i][id],grMC[1][i][id],method[i],0.69,1.31,0.,60,-0.01,0.1,0.18,0.72,0.42,0.89,particle[id]);
      sprintf(name,"%s_%s_v2cent.png",method[i],particle[id]);
      can[1][i][id] -> SetName(name);
      can[1][i][id] -> SaveAs(name);
    }
  }
  
}


