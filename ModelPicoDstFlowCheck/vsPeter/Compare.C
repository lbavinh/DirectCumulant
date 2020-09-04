#include "DrawTGraph.C"
void Compare(){
  static const int npid = 8; // charged hadrons, pions, kaons, protons
  static const int nmethod = 3; // UrQMD, GEANT, Reco
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
  TFile *inputVinh[3], *inputPeter;
  TGraphErrors *grVinh[4][nmethod][npid], *grPeter[4][nmethod][npid];
  char name[400];

  inputVinh[0] = new TFile("VinhPID_UrQMD.root","read");
  inputVinh[1] = new TFile("VinhPID_GEANT.root","read");
  inputVinh[2] = new TFile("VinhPID_Reco.root","read");
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      grVinh[0][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent10-40_2_%i",id));
      grVinh[0][i][id] -> SetTitle("Vinh;p_{T}, GeV/c;v_{2}");
      for (int icent=1;icent<4;icent++){
        grVinh[icent][i][id] = (TGraphErrors*)inputVinh[i]->Get(Form("gr_cent%i_2_%i",icent,id));
        grVinh[icent][i][id] -> SetTitle("Vinh;p_{T}, GeV/c;v_{2}");
      }
    }
  }

  inputPeter = new TFile("PeterPID.root","read");
  
  for (int id=0;id<npid;id++){
    
    grPeter[0][0][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_10_40_pv2TPC_pid%i",id));
    grPeter[0][0][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[0][1][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_10_40_pv2mcTPC_pid%i",id));
    grPeter[0][1][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[0][2][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_10_40_pv2recoTPC_pid%i",id));
    grPeter[0][2][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");

    grPeter[1][0][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_10_20_pv2TPC_pid%i",id));
    grPeter[1][0][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[1][1][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_10_20_pv2mcTPC_pid%i",id));
    grPeter[1][1][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[1][2][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_10_20_pv2recoTPC_pid%i",id));
    grPeter[1][2][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");

    grPeter[2][0][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_20_30_pv2TPC_pid%i",id));
    grPeter[2][0][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[2][1][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_20_30_pv2mcTPC_pid%i",id));
    grPeter[2][1][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[2][2][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_20_30_pv2recoTPC_pid%i",id));
    grPeter[2][2][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");

    grPeter[3][0][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_30_40_pv2TPC_pid%i",id));
    grPeter[3][0][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[3][1][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_30_40_pv2mcTPC_pid%i",id));
    grPeter[3][1][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
    grPeter[3][2][id] = (TGraphErrors*)inputPeter->Get(Form("gr_rebinned_cent_30_40_pv2recoTPC_pid%i",id));
    grPeter[3][2][id] -> SetTitle("Peter;p_{T}, GeV/c;v_{2}");
  }
  


  TCanvas *can[4][nmethod][npid];
  char *method[3]={"UrQMD","GEANT","Reco"};
  for (int i=0; i<nmethod; i++){
    for (int id=0;id<npid;id++){
      sprintf(name,"%s, centrality 10-40%%",pidFancyNames.at(id).Data());
      can[0][i][id] = (TCanvas*) DrawTGraph(grVinh[0][i][id],grPeter[0][i][id],method[i],0.69,1.31,0.,2.5,-0.01,0.2,0.18,0.72,0.42,0.89,name);
      sprintf(name,"%s_%s_Cent10-40.png",method[i],pidNames.at(id).Data());
      can[0][i][id] -> SetName(name);
      // can[0][i][id] -> SaveAs(name);
      for (int icent=1;icent<4;icent++){
        sprintf(name,"%s, centrality %i-%i%%",pidFancyNames.at(id).Data(),icent*10,(icent+1)*10);
        can[icent][i][id] = (TCanvas*) DrawTGraph(grVinh[icent][i][id],grPeter[icent][i][id],method[i],0.69,1.31,0.,2.5,-0.01,0.2,0.18,0.72,0.42,0.89,name);
        sprintf(name,"%s_%s_Cent%i-%i.png",method[i],pidNames.at(id).Data(),icent*10,(icent+1)*10);
        can[icent][i][id] -> SetName(name);
        can[icent][i][id] -> SaveAs(name);
      }
    }
  }
}


