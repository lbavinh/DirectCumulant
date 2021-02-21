#include "PlotV2LYZ.C"
#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
#include "PlotV2HighOrderQCumulant.C"
#include "DrawTGraphImp.C"
#include "PlotV2FHCalEventPlane.C"

vector<TGraphErrors*> PlotV2DifferentialChargedHadronsFor10_40Centrality_UrQMD(TString inputFirstRunFileName = "FirstRun_UrQMD_7.7.root", TString inputSecondRunFileName = "SecondRun_UrQMD_7.7.root")
{

  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const int ratioToMethod = 2;
  const double J1rootJ0 = 0.519147;
  double X[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const double errX[npt] = {0.};
  bool bUseProduct = 1;
  Int_t nmethod = 7;
  TString title[]={"v_{2}{#Psi_{2,TPC}}","v_{2}^{SP}{Q_{2,TPC}}","v_{2}{2}","v_{2}{2}","v_{2}{4}","v_{2}{LYZ, Prod.}", "v_{2}{#Psi_{1,FHCal}}"}; //"v_{2}{LYZ, Sum}"
                                                          //,#eta-gap
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *gr[nmethod];
  TFile *firun1 = new TFile(inputFirstRunFileName.Data(),"read");
  TFile *firun2 = new TFile(inputSecondRunFileName.Data(),"read");
  auto *prV2EP3D = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");
  auto *prV2SP3D = (TProfile3D*) firun2->Get("prV2ScalarProduct");

  TProfile *prV2EPInt = PlotV2EPDifferentialVersusPt(prV2EP3D,10,40,eta_cut);
  TProfile *prV2SPInt = PlotV2SPDifferentialVersusPt(prV2SP3D,10,40,eta_cut);
  gr[0] = Converter(prV2EPInt);
  gr[1] = Converter(prV2SPInt);
  
  TFile *fiFHCal = new TFile(Form("FHCal_UrQMD_7.7_1.root"),"read");
  auto *prV2FHCalEP3D = (TProfile3D*) fiFHCal->Get("prV2FHCalEventPlane");
  TProfile *prV2FHCalEPInt = PlotV2FHCalEPDifferentialVersusPt(prV2FHCalEP3D,10,40,eta_cut);
  gr[6] = Converter(prV2FHCalEPInt);
const double v221040[16] = {-0.099514, 0.0277907, 0.037071, 0.0407959, 0.0469382, 0.0546367, 0.0626488, 0.0707101, 0.0776825, 0.083827, 0.0894573, 0.0935739, 0.0970924, 0.0995878, 0.0708095, 0.00273912};
const double v241040[16] = {0.0116233, 0.0261234, 0.0356098, 0.0399645, 0.0457176, 0.0540901, 0.060519, 0.068566, 0.0771133, 0.081593, 0.0861553, 0.0912922, 0.0974836, 0.0982032, 0.112604, 0.135282};
const double v22Gap1040[16] = {0.0118249, 0.027465, 0.0375146, 0.0423629, 0.0488011, 0.056489, 0.0641292, 0.0724304, 0.0796486, 0.0856575, 0.092499, 0.0962294, 0.0985425, 0.10423, 0.107843, 0.123153};
const double v22e1040[16] = {6.59574e-05, 3.22043e-05, 4.26328e-05, 6.02664e-05, 8.46168e-05, 0.000116918, 0.000158849, 0.000214739, 0.000290821, 0.000396446, 0.000551242, 0.000786247, 0.0011476, 0.00170226, 0.00213886, 0.00487454};
const double v24e1040[16] = {0.000319479, 0.000267128, 0.00034372, 0.000449252, 0.000602043, 0.00080581, 0.00106163, 0.00139579, 0.00183615, 0.00242409, 0.00328226, 0.00458347, 0.00661357, 0.00971616, 0.0121693, 0.0276312};
const double v22Gape1040[16] = {5.80092e-05, 3.80523e-05, 5.36513e-05, 7.92862e-05, 0.000112394, 0.000152797, 0.000204248, 0.000273234, 0.000369182, 0.000509614, 0.0007231, 0.00104902, 0.00154808, 0.00231276, 0.00290486, 0.00662462};
  gr[2] = new TGraphErrors(npt, X, v22Gap1040, errX, v22Gape1040); // v2{2,eta-gap}
  gr[3] = new TGraphErrors(npt, X, v221040, errX, v22e1040); // v2{2}
  gr[4] = new TGraphErrors(npt, X, v241040, errX, v24e1040); // v2{4}
  
  gr[5] = PlotV2LYZ(inputFirstRunFileName, inputSecondRunFileName);


    for (int i=0; i<nmethod; i++)
    {
    gr[i]->SetTitle(title[i].Data());
    gr[i]->SetMarkerStyle(markerStyle[i]);
    gr[i]->SetMarkerSize(markerSize);
    gr[i]->GetXaxis()->SetTitle("p_{T}, GeV/c");
    gr[i]->GetYaxis()->SetTitle("v_{2}");
    gr[i]->SetDrawOption("P PLC PMC");
    }
  

  vector<TGraphErrors*> vGr;

  vGr.push_back(gr[ratioToMethod]);
  // for (int i=0; i<nmethod; i++)
  // {
  //   if (i==ratioToMethod) continue;
  //   vGr.push_back(gr[i]);
  // }
  // vGr.push_back(gr[5]);

  vGr.push_back(gr[0]);
  vGr.push_back(gr[4]);
  vGr.push_back(gr[1]);
  // vGr.push_back(gr[3]);
  vGr.push_back(gr[6]);
  TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.75, 1.25, minpt, 2.8, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.45, 0.4, 0.88,
                                      "UrQMD, Au+Au at #sqrt{s_{NN}}=7.7GeV", Form("Ch. hadrons, |#eta|<%1.1f",eta_cut));
  can->SetName("Cent1040");
  can->SaveAs("v2pT_UrQMD_ener7_10_40.pdf");
  


  return vGr;
}