#include <vector>
using namespace std;
void Test()
{
  const float maxY = 14.;
  const float minY = 0.;
  const float minX = 0;
  const float maxX = 60;

  TString iFileModel = "UrQMD_7.7GeV_res.root";

  TFile *fiModel = new TFile(iFileModel.Data(), "read");

  TProfile2D *tmp;
  TProfile *pV2EbE = (TProfile *) fiModel -> Get("pV2EbE");

  const int ncent = 20;
  pV2EbE -> SetErrorOption("s");
  double vStdDevScaled[ncent];
  double bincent[ncent];
  double bincentE[ncent]={0.};
  for (int ic=0; ic<ncent; ic++)
  {
    bincent[ic] = (ic*5.) + 2.5;
  }

  for (int ic=0; ic<ncent; ic++)
  {
    double stdDevV2 = pV2EbE->GetBinError(ic+1);
    double meanV2 = pV2EbE->GetBinContent(ic+1);
    double stdDevScaled = stdDevV2 / meanV2;
    vStdDevScaled[ic] = stdDevScaled;
    // cout << ic*5<<"-"<<(ic+1)*5 << ": " << meanV2 << " " << stdDevV2 << " " << stdDevScaled << endl;
  }
  TGraphErrors *gr = new TGraphErrors(ncent, bincent, vStdDevScaled, bincentE, bincentE);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kRed+2);
  gr->SetMarkerSize(1.2);
  gr->SetTitle(";centrality, %;#sigma_{v_{2}}/#bar{v_{2}}");

  gr->GetXaxis()->SetRangeUser(minX,maxX);
  gr->SetMinimum(minY);
  gr->SetMaximum(maxY);

  TCanvas c;
  gr->Draw("AP");
  c.SaveAs("trueFlowFluctuations.png");
}
  

  // tmp = (TProfile2D *)fiReco->Get(Form("pv2recoTPC_pid%i", 0));
  // auto prof = (TProfile *)tmp->ProfileX("prof_test", 1, 1);
  // prof = (TProfile *)prof->Rebin(n_pt_bins, "rebinned_prof_test", &pt_binning[0]);
  // std::cout << "CHECK 1 ::::: " << prof->GetBinContent(4) << std::endl;
