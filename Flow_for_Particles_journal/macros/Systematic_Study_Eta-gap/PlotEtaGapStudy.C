#include "PlotV2QCumulant.C"
void PlotEtaGapStudy()
{
  const int nEta_gap = 5;
  const int markerStyle[nEta_gap] = {22,24,25,32,23};
  const TString sEta_gap[nEta_gap] = {"0","0.1","0.5","1.0","2.0"};
  std::vector<TGraphErrors*> vV2[nEta_gap];
  for (int ietagap=0; ietagap<nEta_gap; ietagap++)
  {
    vV2[ietagap] = PlotV2QCumulant(sEta_gap[ietagap]);
  }
  std::vector<TGraphErrors*> vV2SysStudy;
  vV2SysStudy.push_back(vV2[0].at(1)); // v22
  vV2SysStudy.push_back(vV2[0].at(2)); // v24
  for (int ietagap=0; ietagap<nEta_gap; ietagap++)
  {
    TGraphErrors *gr = vV2[ietagap].at(0);
    gr->SetMarkerStyle(markerStyle[ietagap]);
    gr->SetTitle(Form("v_{2}{2,|#Delta#eta|>%s}",sEta_gap[ietagap].Data()));
    vV2SysStudy.push_back(gr);
  }
  TCanvas *cV2CentRF = (TCanvas*) DrawTGraph(vV2SysStudy,"",0.89, 1.11, -1, 61, -0.01, 0.11,
                                            0.18,0.43,0.45,0.889,
                                            "AMPT SM, #sigma_{p}=1.5mb at #sqrt{s_{NN}}=7.7GeV", Form("Ch. hadrons, 0.2<p_{T}<3.0 GeV/c"), true, "v_{2}{2}");
  cV2CentRF -> SetName("Reference flow");
  cV2CentRF -> SaveAs(Form("./SysStudy.png"));

}