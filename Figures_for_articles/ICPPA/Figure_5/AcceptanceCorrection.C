#include "DrawTGraphImp.C"
void AcceptanceCorrection(){
  const int ntype = 3; // uniform acceptance, with AC, w/o AC
  const int nmethod = 4;
  const int npid = 4;
  const int pid = 0;
  const int method = 1; // v22,v24,v2EP,v22Gap

  const double maxpt = 2.5; // for v2 vs pt plotting
  const double minpt = 0.;  // for v2 vs pt plotting

  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.16; // for v2 vs pt plotting

  TFile *input[ntype];
  TGraphErrors *gr[ntype][nmethod][npid];
  TString fileName[ntype]={"","_AC","_NAC"};
  TString methodName[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{#Psi_{2,TPC}}","v_{2}{2}"};
  TString typeOfGraphName[ntype]={"[1] Uniform acceptance;p_{T}, GeV/c;v_{2}","[2] Corrected;p_{T}, GeV/c;v_{2}","[3] Non-corrected;p_{T}, GeV/c;v_{2}"};
  TString pidFancyNames[npid] = {"Ch. hadrons", "#pi^{#pm}", "K^{#pm}", "p+#bar{p}"};
  TString level= (TString) Form("%s, GEANT4, Au+Au at #sqrt{s_{NN}}=%s","UrQMD","7.7 GeV");
  vector <Double_t> coordinateLeg = {0.58,0.02,0.8,0.25}; // {0.18,0.63,0.45,0.889};
  pair<Double_t,Double_t> rangeRatio = {0.89,1.11};

  for(int it=0;it<ntype;it++){
    input[it] = new TFile(Form("v2_UrQMD_7.7GeV_Reco_MotherID%s.root",fileName[it].Data()),"read");
    for (int imeth=0;imeth<nmethod;imeth++){
      for(int id=0;id<npid;id++){
        gr[it][imeth][id] = (TGraphErrors*) input[it] -> Get(Form("gr_cent10-40_%i_%i",imeth,id));
      }
    }
  }
  std::vector<TGraphErrors*> vgrv2pt1040;
  
  for (int imeth=0;imeth<nmethod;imeth++){
    for(int id=0;id<npid;id++){
      gr[0][imeth][id] -> SetMarkerStyle(kOpenSquare);
      gr[1][imeth][id] -> SetMarkerStyle(kFullCircle);
      gr[2][imeth][id] -> SetMarkerStyle(kFullTriangleUp);
      for (int it=0; it<ntype; it++){
        gr[it][imeth][id] -> SetTitle(typeOfGraphName[it].Data());
        
      }
    }
  }
  for (int it=0; it<ntype; it++){
      vgrv2pt1040.push_back(gr[it][method][pid]);
  }
  
  TCanvas *cV2PT1040;
  cV2PT1040 = (TCanvas*) DrawTGraph(vgrv2pt1040,methodName[method].Data(),rangeRatio.first, rangeRatio.second, minpt, maxpt, minV2dif, maxV2dif,
                                        coordinateLeg.at(0), coordinateLeg.at(1), coordinateLeg.at(2), coordinateLeg.at(3),
                                        level.Data(), Form("%s, 10-40%%",pidFancyNames[pid].Data()));
  cV2PT1040 -> SaveAs(Form("CompareAcceptanceCorrection_%s.png",methodName[method].Data()));
}