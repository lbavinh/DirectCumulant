#include "DrawTGraph1.C"
void CumulantsCompare(){
  static const int npid = 8; // charged hadrons, pions, kaons, protons
  static const int nmethod = 3; // UrQMD, GEANT, Reco
  static const int ncent = 5;
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
  TFile *inputVinh[nmethod], *inputDim[2][nmethod];
  TGraphErrors *grVinh[ncent][nmethod][npid], *grDim[ncent][nmethod][npid];
  char name[400];

  inputVinh[0] = new TFile("VinhPID_UrQMD.root","read");
  inputVinh[1] = new TFile("VinhPID_GEANT.root","read");
  inputVinh[2] = new TFile("VinhPID_Reco.root","read");


  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      // grVinh[0][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent10-40_2_%i",id));
      // grVinh[0][i][id] -> SetTitle("Vinh;p_{T}, GeV/c;v_{2}{EP}");
      for (int icent=0;icent<ncent;icent++){
        grVinh[icent][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent%i_0_%i",icent,id));
        grVinh[icent][i][id] -> SetTitle("[1] Vinh;p_{T}, GeV/c;v_{2}{2}");
      }
    }
  }

  inputDim[0][0] = new TFile("urqmdPOS.root","read");
  inputDim[0][1] = new TFile("urqmdNEG.root","read");
  inputDim[1][0] = new TFile("geantPOS.root","read");
  inputDim[1][1] = new TFile("geantNEG.root","read");
  inputDim[2][0] = new TFile("picoPOS.root","read");
  inputDim[2][1] = new TFile("picoNEG.root","read");

  for (int i=0;i<nmethod;i++){
    for (int icent=0;icent<ncent;icent++){
      for (int id=0;id<4;id++){
        grDim[icent][i][id] = (TGraphErrors*)inputDim[i][0]->Get(Form("gr_cent%i_1",icent));
        grDim[icent][i][id] -> SetTitle("[2] Dim;p_{T}, GeV/c;v_{2}{2}");
      }
      for (int id=4;id<npid;id++){
        grDim[icent][i][id] = (TGraphErrors*)inputDim[i][1]->Get(Form("gr_cent%i_1",icent));
        grDim[icent][i][id] -> SetTitle("[2] Dim;p_{T}, GeV/c;v_{2}{2}");
      }
    }
  }

  for (int id=0;id<npid;id++){
    for (int icent=0;icent<ncent;icent++){
      for (int i=0;i<nmethod;i++){
        grVinh[icent][i][id]->SetMarkerStyle(kFullCircle);
        grDim[icent][i][id]->SetMarkerStyle(kFullTriangleUp);
        grDim[icent][i][id] -> SetMarkerSize(1.6);
        grVinh[icent][i][id] -> SetMarkerSize(1.6);
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[ncent][nmethod][npid];
  for (int i=0; i<nmethod; i++){
    for (int icent=0; icent<ncent; icent++){
      for (int id=0;id<npid;id++){
        vgrv2pt[icent][i][id].push_back(grVinh[icent][i][id]);
        vgrv2pt[icent][i][id].push_back(grDim[icent][i][id]);
      }
    }
  }

  TCanvas *can[ncent][nmethod][npid];
  char *method[nmethod]={"UrQMD","GEANT","Reco"};
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      for (int icent=0;icent<ncent;icent++){
        sprintf(name,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
        can[icent][i][id] = (TCanvas*) DrawTGraph(vgrv2pt[icent][i][id],method[i],name,0.88,1.12,0.,2.5,-0.01,0.2,0.18,0.6,0.42,0.89);
        sprintf(name,"v22%s_%s_Cent%i-%i.png",pidNames.at(id).Data(),method[i],icent*10,(icent+1)*10);
        can[icent][i][id] -> SetName(name);
        if (id==0 || id==4) can[icent][i][id] -> SaveAs(name);
      }
    }
  }
}


