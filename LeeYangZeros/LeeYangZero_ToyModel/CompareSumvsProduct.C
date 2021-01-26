#include "DrawTGraph.C"
void CompareSumvsProduct()
{
  const int ncent = 9;
  double cent[ncent] = {2.5, 7.5, 15., 25., 35., 45., 55., 65., 75.};
  double cente[ncent] = {0.};
  double v2LYZProduct[9] = {0.0165796, 0.0237801, 0.0341849, 0.0465793, 0.0563654, 0.0633173, 0.0669408, 0.0650736, 0.0758058};
  double v2eLYZProduct[9] = {0.000333132, 0.000307433, 0.000222057, 0.000271605, 0.000338438, 0.000432338, 0.00062058, 0.00152073, 0.00203279};
  double v2LYZ[9] = {0.0165542, 0.0237351, 0.0341195, 0.046343, 0.055882, 0.0621322, 0.0639077, 0.0467113, 0.0484139};
  double v2eLYZ[9] = {0.000335302, 0.000309596, 0.000223623, 0.000276917, 0.000349565, 0.000462961, 0.000742606, 0.0213738, 0.162356};
  double v2MC[9] = {0.0158618, 0.0237889, 0.0342819, 0.0467447, 0.0567011, 0.0641187, 0.0686057, 0.0712646, 0.0719149};
  double v2eMC[9] = {0.000185839, 0.000196922, 0.000157283, 0.000191181, 0.000233944, 0.000282158, 0.000357384, 0.000468458, 0.000643759};
  double v2EP[9] = {0.0158562, 0.0238397, 0.0341991, 0.0468494, 0.0569996, 0.0644846, 0.069377, 0.0737289, 0.0770661};
  double v2eEP[9] = {0.000312693, 0.000275082, 0.000193331, 0.000223371, 0.000274545, 0.000345734, 0.000482968, 0.000750182, 0.00132778};
  TGraphErrors *gr[4];
  gr[0] = new TGraphErrors(ncent, cent, v2MC, cente, v2eMC);
  gr[1] = new TGraphErrors(ncent, cent, v2EP, cente, v2eEP);
  gr[2] = new TGraphErrors(ncent, cent, v2LYZ, cente, v2eLYZ);
  gr[3] = new TGraphErrors(ncent, cent, v2LYZProduct, cente, v2eLYZProduct);
  int marker[4] = {25,20,22,23};
  TString title[4] = {"v_{2}{MC};centrality, %;v_{2}", "v_{2}{EP};centrality, %;v_{2}", "v_{2}{LYZ,Sum};centrality, %;v_{2}", "v_{2}{LYZ,Product};centrality, %;v_{2}"};
  std::vector<TGraphErrors*> vgr;
  for (int i = 0; i < 4; i++)
  {
    gr[i]->SetTitle(title[i].Data());
    gr[i]->SetMarkerStyle(marker[i]);
    gr[i]->SetMarkerSize(1.2);
    vgr.push_back(gr[i]);
  }
  TCanvas *c = DrawTGraph(vgr,"", 
                    0.88, 1.12,
                    0.0, 80.0,
                    -0.01, 0.12,
                    0.22, 0.55,
                    0.55, 0.89, "Toy Model, Event = 100k", "<M> = 1000", 1);
  c->SetName("canvas");
  c->SaveAs("Compare.pdf");
}