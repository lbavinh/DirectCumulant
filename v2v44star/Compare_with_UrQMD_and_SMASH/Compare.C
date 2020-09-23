// #include "DrawTGraph.C"
#include "DrawTGraphImp.C"
void Compare(){ 
  static const int nenergy = 2;
  static const int nModel = 3; // "STAR","UrQMD","SMASH"
  static const float maxpt = 2.0;
  static const float maxv2 = 0.25;
  static const int nmethod = 3; // 0: v22; 1:v24; 2: v2EP, 3: gapped v22
  const std::vector<std::pair<float, float>> ratioRange = {{0.4,1.34},{0.4,1.34}};
  const std::vector<TString> pidNames = {"CH", "pion", "kaon", "proton", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"Charged hadrons", "#pi", "K", "p(#bar{p})", "h-", "#pi-", "K-", "#bar{p}"};
  TString energy[nenergy] = {"7.7GeV","11.5GeV"};
  TString graphTitle[4]={"v_{2}{2}","v_{2}{4}","v_{2}{#eta-sub}","v_{2}{2,|#Delta#eta>0.1|}"};
  // const pair<float,float> ratio={0.82,1.18};
  TFile *inputVinh[nModel][nenergy];
  TGraphErrors *grVinh[nmethod][nModel][nenergy];
  char name[400], name1[400];
  TString modelName[nModel]={"STAR data","UrQMD","SMASH"};
  for (int iener=0;iener<nenergy;iener++){
    inputVinh[1][iener] = new TFile(Form("v2_%s_%s.root",modelName[1].Data(),energy[iener].Data()),"read");
    inputVinh[2][iener] = new TFile(Form("v2_%s_%s.root",modelName[2].Data(),energy[iener].Data()),"read");
  }


  for (int iener=0;iener<nenergy;iener++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./v2methods%sptCent20-30.txt",energy[iener].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file summary1.txt !\n"<< endl;
      fflush(stdin);
      return;
    }
    int npt = 14;
    double pt[npt], v2eta[npt], v22[npt], v24[npt];
    double pte[npt], v2etae[npt], v22e[npt], v24e[npt];  
    for (int ipt=0; ipt<npt; ipt++) {
      float  ppt,s2,s2e,s2eta,s2etae,s22,s22e,s24,s24e,s2b,s2be;
      fscanf(fp1, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&ppt,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

      pt[ipt]     = ppt;
      v2eta[ipt]  = s2eta;
      v2etae[ipt] = s2etae;
      v22[ipt]    = s22;
      v22e[ipt]   = s22e;
      v24[ipt]    = s24;
      v24e[ipt]   = s24e;
      pte[ipt]    = 0.;
    }
    // STAR
    grVinh[0][0][iener] = new TGraphErrors(npt,pt,v22,pte,v22e); // v22
    grVinh[1][0][iener] = new TGraphErrors(npt,pt,v24,pte,v24e); // v24
    grVinh[2][0][iener] = new TGraphErrors(npt,pt,v2eta,pte,v2etae); // v2etasub
    for (int imethod=0;imethod<nmethod;imethod++){
      grVinh[imethod][0][iener]->SetTitle(Form("%s;p_{T}, GeV/c;%s",modelName[0].Data(),graphTitle[imethod].Data()));
    }
  }




  for (int imodel=1; imodel<nModel; imodel++){
    for (int iener=0;iener<nenergy;iener++){
      for (int imethod=0;imethod<nmethod;imethod++){
        grVinh[imethod][imodel][iener] = (TGraphErrors*)inputVinh[imodel][iener]->Get(Form("gr_cent2_%i_0",imethod));
        grVinh[imethod][imodel][iener] -> SetTitle(Form("%s;p_{T}, GeV/c;%s",modelName[imodel].Data(),graphTitle[imethod].Data()));
      }
    }
  }
  for (int iener=0;iener<nenergy;iener++){
    for (int imethod=0;imethod<nmethod;imethod++){
      grVinh[imethod][0][iener]->SetMarkerStyle(kOpenSquare); // STAR
      grVinh[imethod][1][iener]->SetMarkerStyle(kFullCircle); // UrQMD
      grVinh[imethod][2][iener]->SetMarkerStyle(kFullTriangleUp); // SMASH
      // grVinh[imethod][3][iener]->SetMarkerStyle(kFullSquare); // MPD RECO
      for (int imodel=0;imodel<nModel;imodel++){
        grVinh[imethod][imodel][iener] -> SetMarkerSize(1.6);
        grVinh[imethod][imodel][iener] -> SetMarkerColor(2+imodel);
      }
    }
  }

  std::vector<TGraphErrors*> vgrv2pt[nmethod][nenergy];
  for (int imodel=0; imodel<nModel; imodel++){
    for (int imethod=0; imethod<nmethod; imethod++){
      for (int iener=0;iener<nenergy;iener++){
        vgrv2pt[imethod][iener].push_back(grVinh[imethod][imodel][iener]);
      }
    }
  }
  TString dirName[nmethod]={"2QC","4QC","Eta-sub"};

  
  TCanvas *can[nmethod][nenergy];
  for (int imethod=0;imethod<nmethod;imethod++){
    // gSystem->Exec(Form("mkdir -p ./%s/",dirName[imethod].Data()));
    for (int iener=0;iener<nenergy;iener++){
      if (imethod == 0 && iener == 0){
        sprintf(name,"Au+Au, Ch.Hadrons, centrality 20-30%%");
        sprintf(name1,"#sqrt{s_{NN}}=%s",energy[iener].Data());
        can[imethod][iener] = (TCanvas*) DrawTGraph(vgrv2pt[imethod][iener],"",ratioRange.at(iener).first,ratioRange.at(iener).second,    0.,maxpt,-0.01,maxv2,     0.18,0.56,0.5,0.8,name,name1);
      }else{
        sprintf(name1,"#sqrt{s_{NN}}=%s",energy[iener].Data());
        can[imethod][iener] = (TCanvas*) DrawTGraph(vgrv2pt[imethod][iener],"",ratioRange.at(iener).first,ratioRange.at(iener).second,    0.,maxpt,-0.01,maxv2,     0.18,0.56,0.5,0.8,"",name1);        
      }
      sprintf(name,"./CH_%s_%s.png",energy[iener].Data(),dirName[imethod].Data());
      can[imethod][iener] -> SetName(name);
      can[imethod][iener] -> SaveAs(name);
    }
  }
}