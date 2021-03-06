#include "PlotV2LYZ.C"
#include "PlotV2EtaSubEventPlane.C"
#include "PlotV2ScalarProduct.C"
#include "PlotV2HighOrderQCumulant.C"
#include "DrawTGraphImp.C"

vector<TGraphErrors*> PlotV2DifferentialChargedHadronsFor10_40Centrality(TString inputFirstRunFileName = "FirstRun_7.7.root", TString inputSecondRunFileName = "SecondRun_7.7.root")
{

  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t maxptRF = 3.;   // max pt for reference flow
  Double_t minptRF = 0.2;  // min pt for reference flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  Double_t eta_gap = 0.05; // +-0.05, eta-gap between 2 eta sub-event of two-particle cumulants method with eta-gap
  const int ratioToMethod = 4;
  const double J1rootJ0 = 0.519147;
  double X[npt];
  for (int ipt=0; ipt<npt; ipt++)
  {
    X[ipt] = (pTBin[ipt] + pTBin[ipt+1]) / 2.;
  }
  const double errX[npt] = {0.};
  bool bUseProduct = 1;
  Int_t nmethod = 6;
  TString title[]={"v_{2}{#Psi_{2,TPC}}","v_{2}{SP}","v_{2}{2,#eta-gap}","v_{2}{2}","v_{2}{4}","v_{2}{LYZ, Prod.}"}; //"v_{2}{LYZ, Sum}"
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
  
const double v221040[16] = {-0.0818663, 0.0304641, 0.0494609, 0.0598629, 0.0710271, 0.0828205, 0.0935024, 0.102448, 0.109797, 0.115035, 0.117596, 0.120454, 0.118533, 0.112218, 0.0861491, 0.0392331};
const double v241040[16] = {0.00476282, 0.0293219, 0.047868, 0.0584055, 0.0694344, 0.0799784, 0.0895586, 0.0980653, 0.103965, 0.107809, 0.109036, 0.122194, 0.123758, 0.111551, 0.112619, 0.129317};
const double v22Gap1040[16] = {0.0070712, 0.0310401, 0.0503092, 0.0616217, 0.0726653, 0.0841001, 0.094094, 0.10214, 0.10848, 0.11267, 0.115217, 0.115418, 0.119612, 0.10233, 0.0978402, 0.106685};
const double v22e1040[16] = {6.25001e-05, 3.65868e-05, 5.15842e-05, 7.66693e-05, 0.000115456, 0.000172573, 0.000253467, 0.000371185, 0.000548218, 0.000834753, 0.00131446, 0.00210307, 0.00339154, 0.00546907, 0.00748149, 0.0193317};
const double v24e1040[16] = {0.000240157, 0.000227987, 0.00032423, 0.000443678, 0.000621031, 0.000876134, 0.00122445, 0.00170827, 0.00241011, 0.00352326, 0.0054264, 0.0085853, 0.0138814, 0.0223482, 0.0304467, 0.0882325};
const double v22Gape1040[16] = {5.86977e-05, 4.02059e-05, 6.13738e-05, 9.64514e-05, 0.00014677, 0.000215305, 0.000312396, 0.000456343, 0.000686666, 0.00107086, 0.00171306, 0.0027653, 0.0044611, 0.00723382, 0.00984428, 0.0253488};

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
  vGr.push_back(gr[1]);
  vGr.push_back(gr[3]);
  TCanvas *can = (TCanvas*)DrawTGraph(vGr,"10-40%",0.89, 1.11, minpt, 2.8, -0.005, 0.25,
                                      // 0.65, 0.05, 0.9, 0.5,
                                      0.2, 0.45, 0.4, 0.88,
                                      "AMPT, #sigma_{p}=1.5mb, Au+Au at #sqrt{s_{NN}}=7.7GeV", Form("Ch. hadrons, |#eta|<%1.1f",eta_cut));
  can->SetName("Cent1040");
  can->SaveAs("IntFlow_AMPT_7.7_10-40%_v24_versus_others.pdf");
  


  return vGr;
}