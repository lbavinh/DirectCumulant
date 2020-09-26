#include "DrawTGraphImp.C"
void Compare(int meth = 3){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22
  static const int npid = 4; // charged hadrons, pions, kaons, protons
  static const int nlevel = 3; // UrQMD, GEANT, Reco
  static const int ncent = 7; // 0-10,10-20,20-30,30-40,40-50,10-40,v2vscent

  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality

  const double maxpt = 2.5; // for v2 vs pt plotting
  const double minpt = 0.;  // for v2 vs pt plotting

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.2; // for v2 vs pt plotting
  TString model = {"UrQMD"};
  TString energy = {"11.5GeV"};
  TString levelName= (TString) Form("%s, Au+Au@#sqrt{s_{NN}}=%s",model.Data(),energy.Data());

  const std::vector<std::pair<float, float>> ratioRange = {{0.88,1.12},{0.88,1.12},{0.64, 1.36},{0.88,1.12},{0.82,1.18},{0.82,1.18},{0.64, 1.36},{0.82,1.18}};
  vector <Double_t> coordinateLeg = {0.18,0.56,0.5,0.8};
  const std::vector<TString> pidNames = {"hadron", "pion", "kaon", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"Charged hadrons", "Pions", "Kaons", "(Anti)protons"};
  TString graphTitle[4]={"v_{2}{2}","v_{2}{4}","v_{2}{#eta-sub}","v_{2}{2,|#Delta#eta>0.1|}"};

  // const pair<float,float> ratio={0.82,1.18};
  TFile *inputVinh[nlevel];
  TGraphErrors *grVinh[ncent][nlevel][npid];
  char hname[400];
  TString method[nlevel]={"[1] UrQMD","[2] GEANT","[3] Reco"};
  inputVinh[0] = new TFile(Form("v2_%s_%s.root",model.Data(),energy.Data()),"read");
  inputVinh[1] = new TFile(Form("v2_%s_%s_MC.root",model.Data(),energy.Data()),"read");
  inputVinh[2] = new TFile(Form("v2_%s_%s_Reco_MotherID.root",model.Data(),energy.Data()),"read");
  for (int i=0; i<nlevel; i++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent-2;icent++){
        grVinh[icent][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent%i_%i_%i",icent,meth,id));
        grVinh[icent][i][id] -> SetTitle(Form("%s;p_{T}, GeV/c;%s",method[i].Data(),graphTitle[meth].Data()));
      }
      grVinh[5][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent10-40_%i_%i",meth,id));
      grVinh[5][i][id] -> SetTitle(Form("%s;p_{T}, GeV/c;%s",method[i].Data(),graphTitle[meth].Data()));
      grVinh[6][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("grRF_%i_%i",meth,id));
      grVinh[6][i][id] -> SetTitle(Form("%s;cent, %%;%s",method[i].Data(),graphTitle[meth].Data())); 
    }
  }
  for (int id=0;id<npid;id++){
    for (int icent=0;icent<ncent;icent++){
      grVinh[icent][0][id]->SetMarkerStyle(kOpenSquare);
      grVinh[icent][1][id]->SetMarkerStyle(kFullCircle);
      grVinh[icent][2][id]->SetMarkerStyle(kFullTriangleUp);
      // grVinh[icent][3][id]->SetMarkerStyle(kFullCircle); // kOpenCircle
      for (int i=0;i<nlevel;i++){
        grVinh[icent][i][id] -> SetMarkerSize(1.6);
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[5][npid];
  for (int i=0; i<nlevel; i++){
    for (int icent=0; icent<5; icent++){
      for (int id=0;id<npid;id++){
        vgrv2pt[icent][id].push_back(grVinh[icent][i][id]);
      }
    }
  }
    std::vector<TGraphErrors*> vgrv2pt1040[npid];
  for (int i=0; i<nlevel; i++){
    for (int id=0;id<npid;id++){
      vgrv2pt1040[id].push_back(grVinh[5][i][id]);
    }
  }
  std::vector<TGraphErrors*> vgrv2cent[npid];
  for (int i=0; i<nlevel; i++){
    for (int id=0;id<npid;id++){
      vgrv2cent[id].push_back(grVinh[6][i][id]);
    }
  }
  TString dirName;
  if (meth==0) dirName = "merged_2QC";
  if (meth==1) dirName = "merged_4QC";
  if (meth==2) dirName = "merged_EP";
  if (meth==3) dirName = "merged_gapped_2QC";

  gSystem->Exec(Form("mkdir -p ./%s/",dirName.Data()));
  TCanvas *can[ncent][npid];
  
  for (int id=0;id<npid;id++){
    for (int icent=0;icent<ncent-2;icent++){
      sprintf(hname,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
      can[icent][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][id],"",ratioRange.at(id).first, ratioRange.at(id).second, minpt, maxpt, minV2dif, maxV2dif,
                                                 coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                 levelName.Data(), hname);
      sprintf(hname,"./%s/%s_Cent%i-%i.png",dirName.Data(),pidNames.at(id).Data(),icent*10,(icent+1)*10);
      can[icent][id] -> SetName(hname);
      // can[icent][id] -> SaveAs(hname);
    }
    
    if (id==0) {
      can[5][id] = (TCanvas*) DrawTGraph(vgrv2pt1040[id],"",ratioRange.at(id).first, ratioRange.at(id).second, minpt, maxpt, minV2dif, maxV2dif,
                                                coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                levelName.Data(), Form("%s, centrality 10-40%%",pidFancyNames.at(id).Data()));
    }else{
      can[5][id] = (TCanvas*) DrawTGraph(vgrv2pt1040[id],"",ratioRange.at(id).first, ratioRange.at(id).second, minpt, maxpt, minV2dif, maxV2dif,
                                                coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                "", Form("%s",pidFancyNames.at(id).Data()),0);
    }
   
    sprintf(hname,"./%s/%s_Cent10-40.png",dirName.Data(),pidNames.at(id).Data());
    can[5][id] -> SetName(hname);
    can[5][id] -> SaveAs(hname);

    if (id==0) {
      can[6][id] = (TCanvas*) DrawTGraph(vgrv2cent[id],"",ratioRange.at(id).first, ratioRange.at(id).second, mincent, maxcent, minV2int, maxV2int,
                                                coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                levelName.Data(), Form("%s",pidFancyNames.at(id).Data()));
    }else{
      can[6][id] = (TCanvas*) DrawTGraph(vgrv2cent[id],"",ratioRange.at(id).first, ratioRange.at(id).second, mincent, maxcent, minV2int, maxV2int,
                                                coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                                "", Form("%s",pidFancyNames.at(id).Data()),0);
    }
    sprintf(hname,"./%s/%s_v2cent.png",dirName.Data(),pidNames.at(id).Data());
    can[6][id] -> SetName(hname);
    can[6][id] -> SaveAs(hname);
  }
}