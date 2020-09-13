#include "DrawTGraph.C"
void Compare(int meth = 0){ // 0: v22; 1:v24; 2: v2EP
  static const int npid = 4; // charged hadrons, pions, kaons, protons
  static const int nmethod = 4; // UrQMD, GEANT, Reco, Reco AC
  static const float maxpt = 2.5;
  static const int ncent = 7; // 0-10,10-20,20-30,30-40,40-50,10-40,v2vscent
  const std::vector<std::pair<float, float>> ratioRange = {{0.88,1.12},{0.88,1.12},{0.64, 1.36},{0.88,1.12},{0.82,1.18},{0.82,1.18},{0.64, 1.36},{0.82,1.18}};
  const std::vector<TString> pidNames = {"hadron", "pion", "kaon", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"Charged hadrons", "#pi", "K", "p(#bar{p})", "h-", "#pi-", "K-", "#bar{p}"};
  TString graphTitle[3]={"v_{2}{2}","v_{2}{4}","v_{2}{EP}"};
  // const pair<float,float> ratio={0.82,1.18};
  TFile *inputVinh[nmethod];
  TGraphErrors *grVinh[ncent][nmethod][npid];
  char name[400];
  TString method[nmethod]={"[1] UrQMD","[2] GEANT","[3] Reco","[4] Reco corrected"};
  inputVinh[0] = new TFile("VinhPID_UrQMD_merged.root","read");
  inputVinh[1] = new TFile("VinhPID_GEANT_merged.root","read");
  inputVinh[2] = new TFile("VinhPID_Reco_merged.root","read");
  inputVinh[3] = new TFile("VinhPID_Reco_AC_merged.root","read");
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent-2;icent++){
        grVinh[icent][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent%i_%i_%i",icent,meth,id));
        grVinh[icent][i][id] -> SetTitle(Form("%s;p_{T}, GeV/c;%s",method[i].Data(),graphTitle[meth].Data()));
      }
      grVinh[5][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent10-40_%d_%i",meth,id));
      grVinh[5][i][id] -> SetTitle(Form("%s;p_{T}, GeV/c;%s",method[i].Data(),graphTitle[meth].Data()));
      grVinh[6][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("grRF_%d_%i",meth,id));
      grVinh[6][i][id] -> SetTitle(Form("%s;cent, %%;%s",method[i].Data(),graphTitle[meth].Data())); 
    }
  }
  for (int id=0;id<npid;id++){
    for (int icent=0;icent<ncent;icent++){
      grVinh[icent][0][id]->SetMarkerStyle(kOpenSquare);
      grVinh[icent][1][id]->SetMarkerStyle(kFullCircle);
      grVinh[icent][2][id]->SetMarkerStyle(kFullTriangleUp);
      grVinh[icent][3][id]->SetMarkerStyle(kOpenCircle);
      for (int i=0;i<nmethod;i++){
        grVinh[icent][i][id] -> SetMarkerSize(1.6);
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[5][npid];
  for (int i=0; i<nmethod; i++){
    for (int icent=0; icent<5; icent++){
      for (int id=0;id<npid;id++){
        vgrv2pt[icent][id].push_back(grVinh[icent][i][id]);
      }
    }
  }
    std::vector<TGraphErrors*> vgrv2pt1040[npid];
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      vgrv2pt1040[id].push_back(grVinh[5][i][id]);
    }
  }
  std::vector<TGraphErrors*> vgrv2cent[npid];
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      vgrv2cent[id].push_back(grVinh[6][i][id]);
    }
  }
  TString dirName;
  if (meth==0) dirName = "merged_2QC_AC";
  if (meth==1) dirName = "merged_4QC_AC";
  if (meth==2) dirName = "merged_EP";

  gSystem->Exec(Form("mkdir -p ./%s/",dirName.Data()));
  TCanvas *can[ncent][npid];
  
  for (int id=0;id<npid;id++){
    for (int icent=0;icent<ncent-2;icent++){
      sprintf(name,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
      can[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",ratioRange.at(id).first,ratioRange.at(id).second,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,name);
      sprintf(name,"./%s/%s_Cent%i-%i.png",dirName.Data(),pidNames.at(id).Data(),icent*10,(icent+1)*10);
      can[icent][id] -> SetName(name);
      can[icent][id] -> SaveAs(name);
    }
    sprintf(name,"%s, centrality 10-40%%",pidFancyNames.at(id).Data());
    can[5][id] = (TCanvas*) DrawTGraph(vgrv2pt1040[id],"",ratioRange.at(id).first,ratioRange.at(id).second,    0.,maxpt,-0.01,0.2,     0.18,0.56,0.5,0.8,name);
    sprintf(name,"./%s/%s_Cent10-40.png",dirName.Data(),pidNames.at(id).Data());
    can[5][id] -> SetName(name);
    can[5][id] -> SaveAs(name);

    sprintf(name,"%s",pidFancyNames.at(id).Data());
    can[6][id] = (TCanvas*) DrawTGraph(vgrv2cent[id],"",ratioRange.at(id).first,ratioRange.at(id).second,    0.,60,-0.01,0.1,     0.18,0.56,0.5,0.8,name);
    sprintf(name,"./%s/%s_v2cent.png",dirName.Data(),pidNames.at(id).Data());
    can[6][id] -> SetName(name);
    can[6][id] -> SaveAs(name);
  }
}