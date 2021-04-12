

#include <TStopwatch.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TF2.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <iostream>
#include <QVector.h> // contains constants.C, need to be improved by Singleton pattern class with these constants

int main(int argc, char **argv)
{
  TString iFileName, oFileName;

  if (argc < 5)
  {
    std::cerr << "./fit-dca -i DCA_HIST.root -o DCA_FIT.root" << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
    }
  }

  TStopwatch timer;
  timer.Start();
  const Int_t NdcaFitIter = 3;
  const Int_t Ndim = 3;
  TH1F *h_dca[Ndim][npt][netaBin];
  TF1 *dca_fit[Ndim][npt][netaBin];

  TFile *fi = new TFile(iFileName.Data(), "READ");
  for (int dim = 0; dim < Ndim; ++dim)
  {
    for (int ptbin = 0; ptbin < npt; ++ptbin)
    {
      for (int etabin = 0; etabin < netaBin; ++etabin)
      {
        h_dca[dim][ptbin][etabin] = (TH1F *)fi->Get(Form("h_dca_%i_%i_%i", dim, ptbin, etabin));
        dca_fit[dim][ptbin][etabin] = new TF1(Form("f_dca_%i_%i_%i", dim, ptbin, etabin), "gaus", -0.2, 0.2);
        h_dca[dim][ptbin][etabin]->Fit(Form("f_dca_%i_%i_%i", dim, ptbin, etabin), "RQ");
      }
    }
  }

  TH2F *h_integral[Ndim];
  TH2F *h_mean[Ndim];
  TH2F *h_sigma[Ndim];

  TF2 *f_sigma[Ndim];

  for (Int_t i_dim = 0; i_dim < Ndim; i_dim++)
  {
    h_integral[i_dim] = new TH2F(Form("h_integral%i", i_dim), Form("Integral of the fit function %i;p_{T};#eta;", i_dim), npt, pTBin, netaBin, etaBin);
    h_mean[i_dim] = new TH2F(Form("h_mean%i", i_dim), Form("Mean of the fit function %i;p_{T};#eta;", i_dim), npt, pTBin, netaBin, etaBin);
    h_sigma[i_dim] = new TH2F(Form("h_sigma%i", i_dim), Form("Sigma of the fit function %i;p_{T};#eta;", i_dim), npt, pTBin, netaBin, etaBin);

    f_sigma[i_dim] = new TF2(Form("f_sigma%i", i_dim),
                             "[0]+[1]*pow(x,1)+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)+[6]*pow(x,6)+[7]*pow(x,7)+[8]*pow(y,1)+[9]*pow(y,2)+[10]*pow(y,3)+[11]*pow(y,4)+[12]*pow(y,5)+[13]*pow(y,6)+[14]*pow(y,7)",
                             0., 3., -1.5, 1.5);
  }

  for (Int_t i_dim = 0; i_dim < Ndim; i_dim++)
  {
    for (Int_t i_pt = 0; i_pt < npt; i_pt++)
    {
      for (Int_t i_eta = 0; i_eta < netaBin; i_eta++)
      {
        h_integral[i_dim]->SetBinContent(i_pt + 1, i_eta + 1, dca_fit[i_dim][i_pt][i_eta]->GetParameter(0));
        h_integral[i_dim]->SetBinError(i_pt + 1, i_eta + 1, dca_fit[i_dim][i_pt][i_eta]->GetParError(0));
        h_mean[i_dim]->SetBinContent(i_pt + 1, i_eta + 1, dca_fit[i_dim][i_pt][i_eta]->GetParameter(1));
        h_mean[i_dim]->SetBinError(i_pt + 1, i_eta + 1, dca_fit[i_dim][i_pt][i_eta]->GetParError(1));
        h_sigma[i_dim]->SetBinContent(i_pt + 1, i_eta + 1, dca_fit[i_dim][i_pt][i_eta]->GetParameter(2));
        h_sigma[i_dim]->SetBinError(i_pt + 1, i_eta + 1, dca_fit[i_dim][i_pt][i_eta]->GetParError(2));
      }
    }
  }

  double *par;
  for (Int_t i_dim = 0; i_dim < Ndim; i_dim++)
  {
    // Fit N iterations
    h_sigma[i_dim]->Fit(f_sigma[i_dim], "R");
    par = f_sigma[i_dim]->GetParameters();
    for (int it=0; it<NdcaFitIter-1; it++)
    {
      f_sigma[i_dim]->SetParameters(par);
      h_sigma[i_dim]->Fit(f_sigma[i_dim], "R");
      par = f_sigma[i_dim]->GetParameters();
    }
  }

  TFile *fo = new TFile(oFileName.Data(), "recreate");
  fo->cd();
  for (Int_t i_dim = 0; i_dim < Ndim; i_dim++)
  {
    h_integral[i_dim]->Write();
    h_mean[i_dim]->Write();
    h_sigma[i_dim]->Write();
    f_sigma[i_dim]->Write();
  }
  fo->mkdir("dca_gaus_fits");
  fo->cd("dca_gaus_fits");
  for (int dim = 0; dim < Ndim; ++dim)
  {
    for (int ptbin = 0; ptbin < npt; ++ptbin)
    {
      for (int etabin = 0; etabin < netaBin; ++etabin)
      {
        h_dca[dim][ptbin][etabin]->Write();
        dca_fit[dim][ptbin][etabin]->Write();
      }
    }
  }
  fo->Close();

  timer.Stop();
  timer.Print();
  return 0;
}