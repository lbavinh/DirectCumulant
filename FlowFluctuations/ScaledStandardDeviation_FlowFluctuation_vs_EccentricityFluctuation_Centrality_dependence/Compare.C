#include <TProfile.h>
double StandardDeviation(TProfile *const &pr, Int_t bin = 0)
{
  double StdDev;
  pr->SetErrorOption("s");
  return StdDev = pr->GetBinError(bin + 1);
}

double Mean(TProfile *const &pr, Int_t bin = 0)
{
  double mean = pr->GetBinContent(bin + 1);
  return mean;
}

double StandardDeviationScaled(TProfile *const &pr, Int_t bin = 0)
{
  double stdDevScaled = (double)StandardDeviation(pr, bin) / Mean(pr, bin) ; //
  return stdDevScaled;
}
void Compare()
{
  const int ncent = 9;
  const double bin_cent[ncent] = {2.5, 7.5, 15., 25., 35., 45., 55., 65., 75.};
  const double bin_centE[ncent] = {0};

  TFile *fiEcc2 = new TFile("Glauber_7.7GeV.root", "read");
  TProfile *prEcc2vsCent = (TProfile *)fiEcc2->Get("prEcc2vsCent");
  TFile *fiV2 = new TFile("UrQMD_7.7GeV.root", "read");
  TProfile *prV2[ncent][8], *prRes[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int id = 0; id < 8; id++)
    {
      prV2[ic][id] = (TProfile *)fiV2->Get(Form("hv22EP_%i_%i", ic, id));
      prRes[ic] = (TProfile *)fiV2->Get(Form("HRes_%i", ic));
    }
    prV2[ic][0]->Add(prV2[ic][4]);
  }

  double stdDevScaled[2][ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    // stdDevScaled[0][ic] = StandardDeviationScaled(prV2[ic][0], 0);
    double v2Mean = Mean(prV2[ic][0]) / sqrt(Mean(prRes[ic]));
    double v2StdDev = StandardDeviation(prV2[ic][0]) / sqrt(Mean(prRes[ic])); // 
    stdDevScaled[0][ic] = v2StdDev/v2Mean;
    // cout << v2Mean << ", " << v2StdDev << endl;
    double ecc2StdDev = StandardDeviation(prEcc2vsCent, ic);
    cout << ecc2StdDev << endl;
    stdDevScaled[1][ic] = StandardDeviationScaled(prEcc2vsCent, ic);
    // cout << stdDevScaled[0][ic] << " " << stdDevScaled[1][ic] << endl;
  }
}