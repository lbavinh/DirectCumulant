#include "DrawTGraph.C"
void Compare(){
  static const int npid = 8; // charged hadrons, pions, kaons, protons
  static const int nmethod = 3; // UrQMD, GEANT, Reco
  static const float maxpt = 2.5;
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
  TFile *inputVinh[3];
  TGraphErrors *grVinh[5][nmethod][npid], *grPeter[5][nmethod][npid];
  char name[400];
  char *method[3]={"[1] UrQMD","[2] GEANT","[3] Reco"};
  inputVinh[0] = new TFile("VinhPID_UrQMD.root","read");
  inputVinh[1] = new TFile("VinhPID_GEANT.root","read");
  inputVinh[2] = new TFile("VinhPID_Reco.root","read");
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      grVinh[0][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent10-40_2_%i",id));
      grVinh[0][i][id] -> SetTitle(Form("%s;p_{T}, GeV/c;v_{2}{EP}",method[i]));
      grVinh[4][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("grRF_2_%i",id));
      grVinh[4][i][id] -> SetTitle(Form("%s;cent, %;v_{2}{EP}",method[i]));
      for (int icent=1;icent<4;icent++){
        grVinh[icent][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent%i_2_%i",icent,id));
        grVinh[icent][i][id] -> SetTitle(Form("%s;p_{T}, GeV/c;v_{2}{EP}",method[i]));
      }
    }
  }
  for (int id=0;id<npid;id++){
    for (int icent=0;icent<5;icent++){
      grVinh[icent][0][id]->SetMarkerStyle(kOpenSquare);
      grVinh[icent][1][id]->SetMarkerStyle(kFullCircle);
      grVinh[icent][2][id]->SetMarkerStyle(kFullTriangleUp);
      for (int i=0;i<nmethod;i++){
        grVinh[icent][i][id] -> SetMarkerSize(1.6);
      }
    }
  }
  std::vector<TGraphErrors*> vgrv2pt1040[npid];
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      vgrv2pt1040[id].push_back(grVinh[0][i][id]);
    }
  }
  std::vector<TGraphErrors*> vgrv2pt[4][npid];
  for (int i=0; i<nmethod; i++){
    for (int icent=1; icent<4; icent++){
      for (int id=0;id<npid;id++){
        vgrv2pt[icent][id].push_back(grVinh[icent][i][id]);
      }
    }
  }
  std::vector<TGraphErrors*> vgrv2cent[npid];
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      vgrv2cent[id].push_back(grVinh[4][i][id]);
    }
  }
  TCanvas *can[5][nmethod][npid];
  
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      sprintf(name,"%s, centrality 10-40%%",pidFancyNames.at(id).Data());
      can[0][i][id] = (TCanvas*) DrawTGraph(vgrv2pt1040[id],"",0.67,1.33,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,name);
      sprintf(name,"%s_%s_Cent10-40.png",method[i],pidNames.at(id).Data());
      can[0][i][id] -> SetName(name);
      can[0][i][id] -> SaveAs(name);

      sprintf(name,"%s",pidFancyNames.at(id).Data());
      can[4][i][id] = (TCanvas*) DrawTGraph(vgrv2cent[id],"",0.67,1.33,    0.,60,-0.01,0.2,     0.18,0.56,0.5,0.8,name);
      sprintf(name,"%s_%s_v2cent.png",method[i],pidNames.at(id).Data());
      can[4][i][id] -> SetName(name);
      can[4][i][id] -> SaveAs(name);

      for (int icent=1;icent<4;icent++){
        sprintf(name,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
        can[icent][i][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",0.67,1.33,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,name);
        sprintf(name,"%s_%s_Cent%i-%i.png",method[i],pidNames.at(id).Data(),icent*10,(icent+1)*10);
        can[icent][i][id] -> SetName(name);
        can[icent][i][id] -> SaveAs(name);
      }
    }
  }
}


