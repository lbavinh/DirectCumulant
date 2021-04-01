#include "PlotV2LYZ.C"
#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
#include "PlotV2HighOrderQCumulant.C"
#include "DrawTGraphImp.C"

vector<TGraphErrors*> PlotV2DifferentialChargedHadronsFor10_40Centrality_AMPT08(TString inputFirstRunFileName = "FirstRun_AMPT08_7.7_new.root", TString inputSecondRunFileName = "SecondRun_AMPT08_7.7_new.root")
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
  Int_t nmethod = 6;
  TString title[]={"v_{2}{#Psi_{2,TPC}}","v_{2}{SP}","v_{2}{2}","v_{2}{2}","v_{2}{4}","v_{2}{LYZ}"}; //"v_{2}{LYZ, Sum}"
                                                      //,#eta-gap
  
  const int markerStyle[] = {24,22,27,21,20,25,28,26,23};
  const float markerSize = 1.3;
  TGraphErrors *gr[nmethod];
  TFile *firun1 = new TFile(inputFirstRunFileName.Data(),"read");
  TFile *firun2 = new TFile(inputSecondRunFileName.Data(),"read");
  auto *prV2EP3D = (TProfile3D*) firun2->Get("prV2EtaSubEventPlane");
  auto *prV2SP3D = (TProfile3D*) firun2->Get("prV2ScalarProduct");

  TProfile *prV2EPInt = PlotV2EPDifferentialVersusPt(prV2EP3D,10,40-1,eta_cut);
  TProfile *prV2SPInt = PlotV2SPDifferentialVersusPt(prV2SP3D,10,40-1,eta_cut);
  gr[0] = Converter(prV2EPInt);
  gr[1] = Converter(prV2SPInt);
  
const double v221040[16] = {-0.0804356, 0.0318837, 0.0490628, 0.057313, 0.0665388, 0.075852, 0.0848015, 0.0919373, 0.097149, 0.100656, 0.105554, 0.106605, 0.107141, 0.103093, 0.0807867, 0.0401759};
const double v241040[16] = {0.00567798, 0.0305446, 0.047052, 0.0562518, 0.0651016, 0.0739099, 0.082349, 0.0873393, 0.0931062, 0.0906038, 0.0976119, 0.107019, 0.104246, 0.117705, 0.0854513, 0.0531401};
const double v22Gap1040[16] = {0.00820783, 0.0321704, 0.0496651, 0.05875, 0.0681409, 0.0771917, 0.0856357, 0.0928038, 0.0969779, 0.100735, 0.104478, 0.105693, 0.104311, 0.0986897, 0.0949859, 0.120557};
const double v22e1040[16] = {4.78911e-05, 2.8031e-05, 3.95705e-05, 5.8425e-05, 8.74968e-05, 0.000130635, 0.000191471, 0.000278304, 0.000405965, 0.000608173, 0.000937017, 0.00146609, 0.00231292, 0.00366664, 0.00486602, 0.0119776};
const double v24e1040[16] = {0.000185575, 0.000180083, 0.000251448, 0.000339891, 0.000472298, 0.000664278, 0.000928192, 0.00128862, 0.00179658, 0.00259204, 0.00391525, 0.00608204, 0.0095638, 0.0151502, 0.0197213, 0.0492123};
const double v22Gape1040[16] = {4.39072e-05, 2.98e-05, 4.56094e-05, 7.12454e-05, 0.000108199, 0.000158838, 0.000229396, 0.000331757, 0.000491204, 0.00075151, 0.00117328, 0.00185077, 0.00292755, 0.0046465, 0.00614812, 0.0151308};
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
    // gr[i]->RemovePoint(0);
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
  TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.85, 1.11, minpt, 2.8, -0.005, 0.14,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.45, 0.4, 0.88,
                                      "AMPT SM, #sigma_{p}=0.8mb, Au+Au at #sqrt{s_{NN}}=7.7GeV", Form("Ch. hadrons, |#eta|<%1.1f",eta_cut), true, "v_{2}{2}");
  can->SetName("Cent1040");
  can->SaveAs("v2pT_AMPT08_ener7_10_40.pdf");
  // can->SetCanvasSize(1000,1000);
  can->SaveAs("v2pT_AMPT08_ener7_10_40.png");
  


  return vGr;
}