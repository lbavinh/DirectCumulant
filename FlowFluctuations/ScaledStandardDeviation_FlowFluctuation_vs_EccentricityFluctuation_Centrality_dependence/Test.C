#include <vector>
using namespace std;
void Test()
{
  TString iFileModel = "flow_model.root";

  TFile *fiModel = new TFile(iFileModel.Data(), "read");

  TProfile2D *tmp;

  const int npid = 8;
  const int ncent = 8;
  TProfile *pv2_model[npid];

  // Get Model results
  for (int i = 0; i < npid; i++)
  {
    tmp = (TProfile2D *)fiModel->Get(Form("pv2TPC_pid%i", i));
    int lowPtBin = tmp->GetXaxis()->FindBin(0.2);
    int highPtBin = tmp->GetXaxis()->FindBin(3.0);
    pv2_model[i] = (TProfile *)tmp->ProfileY(Form("%s_integrated_over_pt", tmp->GetName()), lowPtBin, highPtBin);
    delete tmp;
  }
  pv2_model[0] -> Add(pv2_model[4]);
  pv2_model[0] ->SetErrorOption("s");
  for (int ic=0; ic<ncent; ic++)
  {
    double stdDevV2 = pv2_model[0]->GetBinError(ic+1);
    double meanV2 = pv2_model[0]->GetBinContent(ic+1);
    double stdDevScaled = stdDevV2 / meanV2;
    cout << meanV2 << " " << stdDevV2 << " " << stdDevScaled << endl;
  }
}
  

  // tmp = (TProfile2D *)fiReco->Get(Form("pv2recoTPC_pid%i", 0));
  // auto prof = (TProfile *)tmp->ProfileX("prof_test", 1, 1);
  // prof = (TProfile *)prof->Rebin(n_pt_bins, "rebinned_prof_test", &pt_binning[0]);
  // std::cout << "CHECK 1 ::::: " << prof->GetBinContent(4) << std::endl;
