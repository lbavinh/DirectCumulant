#include "PlotV2LYZ.C"
#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
#include "PlotV2HighOrderQCumulant.C"
#include "DrawTGraphImp.C"
#include "PlotV2FHCalEventPlane.C"

vector<TGraphErrors*> PlotV2DifferentialChargedHadronsFor10_40Centrality_UrQMD_11(TString inputFirstRunFileName = "FirstRun_UrQMD_11.5.root", TString inputSecondRunFileName = "SecondRun_UrQMD_11.5.root")
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
  
  TFile *fiFHCal = new TFile(Form("FHCal_UrQMD_11.5_1.root"),"read");
  auto *prV2FHCalEP3D = (TProfile3D*) fiFHCal->Get("prV2FHCalEventPlane");
  TProfile *prV2FHCalEPInt = PlotV2FHCalEPDifferentialVersusPt(prV2FHCalEP3D,10,40,eta_cut);
  gr[6] = Converter(prV2FHCalEPInt);
// const double v221040[16] = {-0.099514, 0.0277907, 0.037071, 0.0407959, 0.0469382, 0.0546367, 0.0626488, 0.0707101, 0.0776825, 0.083827, 0.0894573, 0.0935739, 0.0970924, 0.0995878, 0.0708095, 0.00273912};
// const double v241040[16] = {0.0116233, 0.0261234, 0.0356098, 0.0399645, 0.0457176, 0.0540901, 0.060519, 0.068566, 0.0771133, 0.081593, 0.0861553, 0.0912922, 0.0974836, 0.0982032, 0.112604, 0.135282};
// const double v22Gap1040[16] = {0.0118249, 0.027465, 0.0375146, 0.0423629, 0.0488011, 0.056489, 0.0641292, 0.0724304, 0.0796486, 0.0856575, 0.092499, 0.0962294, 0.0985425, 0.10423, 0.107843, 0.123153};
// const double v22e1040[16] = {6.59574e-05, 3.22043e-05, 4.26328e-05, 6.02664e-05, 8.46168e-05, 0.000116918, 0.000158849, 0.000214739, 0.000290821, 0.000396446, 0.000551242, 0.000786247, 0.0011476, 0.00170226, 0.00213886, 0.00487454};
// const double v24e1040[16] = {0.000319479, 0.000267128, 0.00034372, 0.000449252, 0.000602043, 0.00080581, 0.00106163, 0.00139579, 0.00183615, 0.00242409, 0.00328226, 0.00458347, 0.00661357, 0.00971616, 0.0121693, 0.0276312};
// const double v22Gape1040[16] = {5.80092e-05, 3.80523e-05, 5.36513e-05, 7.92862e-05, 0.000112394, 0.000152797, 0.000204248, 0.000273234, 0.000369182, 0.000509614, 0.0007231, 0.00104902, 0.00154808, 0.00231276, 0.00290486, 0.00662462};
  
const double v221040[16] = {-0.0734062, 0.0280337, 0.0386921, 0.0431524, 0.0480775, 0.0543169, 0.0610617, 0.0681206, 0.0745985, 0.0799029, 0.0843076, 0.087853, 0.0915372, 0.0971759, 0.0716729, 0.0125097};
const double v241040[16] = {0.00840829, 0.0260162, 0.0365104, 0.0399432, 0.0449439, 0.0510744, 0.0568172, 0.0632881, 0.0680861, 0.0725486, 0.0786882, 0.0772517, 0.0801139, 0.0879787, 0.0751253, 0.0579837};
const double v22Gap1040[16] = {0.0123726, 0.0277508, 0.0390245, 0.0441141, 0.0495765, 0.0556541, 0.0623733, 0.0696223, 0.0759151, 0.0809293, 0.0855867, 0.0895125, 0.0932093, 0.0998623, 0.0990298, 0.106621};
const double v22e1040[16] = {6.11218e-05, 3.3394e-05, 4.4158e-05, 6.30773e-05, 8.99188e-05, 0.000127359, 0.000177359, 0.000242076, 0.000326107, 0.000438776, 0.000599063, 0.000836497, 0.0011927, 0.0017303, 0.00209635, 0.00457128};
const double v24e1040[16] = {0.000287404, 0.000253538, 0.000329723, 0.000427327, 0.000571344, 0.000778394, 0.00105242, 0.00140126, 0.00183289, 0.00238974, 0.00317215, 0.00433943, 0.00609695, 0.00881995, 0.010596, 0.0233558};
const double v22Gape1040[16] = {6.01598e-05, 3.84181e-05, 5.42852e-05, 8.18201e-05, 0.000119658, 0.000168317, 0.00022871, 0.000305607, 0.000408747, 0.000555267, 0.000771826, 0.00109536, 0.00158124, 0.00230554, 0.00279517, 0.00609947};  
  
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
  TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.7, 1.25, minpt, 2.8, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.45, 0.4, 0.88,
                                      "UrQMD, Au+Au at #sqrt{s_{NN}}=11.5GeV", Form("Ch. hadrons, |#eta|<%1.1f",eta_cut));
  can->SetName("Cent1040");
  can->SaveAs("v2pT_UrQMD_ener11_10_40.pdf");
  


  return vGr;
}