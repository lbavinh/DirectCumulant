#include <FlowAnalysisWithLeeYangZeros.h>

ClassImp(FlowAnalysisWithLeeYangZeros);

FlowAnalysisWithLeeYangZeros::FlowAnalysisWithLeeYangZeros() :
fDebug(0),
fUseProduct(false),
fFirstRun(true),
// fTheta,
// fQtheta,
// fPrReGthetaSum,
// fPrImGthetaSum,
fHistGthetaSum(NULL),
// fPrReGthetaProduct,
// fPrImGthetaProduct,
fHistGthetaProduct(NULL),
// fRSum,
// fRProduct,
fMult(0),
// fGenFunS,
// fGenFunP,
prRefMult(NULL),
prQ2x(NULL),
prQ2y(NULL),
prQ2ModSq(NULL),
fstrInputFileFromFirstRun("")
// fPrReDenom
// fPrImDenom
// fPrReNumer
// fPrImNumer
// fPrMultPOI
// fPrReDenomPro
// fPrImDenomPro
// fPrReNumerPro
// fPrImNumerPro
// fMultPOI
// fExponent
// fdGr0
// fGenfunPror0
// fR02Sum
// fR02Pro

{
}

FlowAnalysisWithLeeYangZeros::~FlowAnalysisWithLeeYangZeros()
{
}

void FlowAnalysisWithLeeYangZeros::Init()
{
  for (int itheta = 0; itheta < thetabins; itheta++)
  {
    fTheta[itheta] = itheta * TMath::Pi() / (2.0 * thetabins);
  }
  if (fFirstRun)
  {
    fHistGthetaSum = new TH1F(Form("hGthetaSum"), "", rbins, rMinSum, rMaxSum);
    if (fUseProduct)
      fHistGthetaProduct = new TH1F(Form("hGthetaProduct"), "", rbins, rMin, rMax);
    for (int i = 0; i < ncent; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        fPrReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);
        fPrImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, rMinSum, rMaxSum);

        if (fUseProduct)
        {
          fPrReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
          fPrImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
        }
      }
    }

    prRefMult = new TProfile("prRefMult", "", ncent, 0, ncent);
    prQ2x = new TProfile("prQ2x", "", ncent, 0, ncent);
    prQ2y = new TProfile("prQ2y", "", ncent, 0, ncent);
    prQ2ModSq = new TProfile("prQ2ModSq", "", ncent, 0, ncent);

    for (int rbin = 0; rbin < rbins; ++rbin)
    {
      if (fUseProduct)
      {
        fRProduct[rbin] = fHistGthetaProduct->GetBinCenter(rbin + 1);
      }
      fRSum[rbin] = fHistGthetaSum->GetBinCenter(rbin + 1);
      // cout << r[rbin] << " ";
    }
  }
  else
  {
    ProcessRootFileWithHistFromFirstRun();
    for (int i = 0; i < thetabins; i++)
    {
      fPrReDenom[i] = new TProfile(Form("prReDenom_theta%i", i), "", ncent, 0, ncent);
      fPrImDenom[i] = new TProfile(Form("prImDenom_theta%i", i), "", ncent, 0, ncent);

      for (int j = 0; j < ncent; j++)
      {
        fPrReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
        fPrImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
      }
    }
    if (fUseProduct)
    {
      for (int i = 0; i < thetabins; i++)
      {
        fPrReDenomPro[i] = new TProfile(Form("prReDenomPro_theta%i", i), "", ncent, 0, ncent);
        fPrImDenomPro[i] = new TProfile(Form("prImDenomPro_theta%i", i), "", ncent, 0, ncent);

        for (int j = 0; j < ncent; j++)
        {
          fPrReNumerPro[i][j] = new TProfile(Form("prReNumerPro_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
          fPrImNumerPro[i][j] = new TProfile(Form("prImNumerPro_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
        }
      }
    }
    for (int ic = 0; ic < ncent; ic++)
    {
      fPrMultPOI[ic] = new TProfile(Form("prMultPOI_cent%i", ic), "", npt, 0, npt);
    }
  }
}

void FlowAnalysisWithLeeYangZeros::Zero()
{
  fMult = 0.;
  for (int i = 0; i < thetabins; ++i)
  {
    fQtheta[i] = 0.;
  }
  if (fFirstRun)
  {
    for (int i = 0; i < rbins; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        fGenFunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
        if (fUseProduct)
        {
          fGenFunP[i][j] = TComplex::One();
        } // initialize to 1, calcualte via product
      }
    }
  }
  else
  {
    for (int ipt = 0; ipt < npt; ipt++)
    {
      fMultPOI[ipt] = 0.;
    }
    for (int it = 0; it < thetabins; it++)
    {
      fExponent[it] = TComplex(0.0, 0.0);
      fdGr0[it] = TComplex(0.0, 0.0);
      fGenfunPror0[it] = TComplex::One();
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessFirstTrackLoop(const double &phi, const double &pt, const int &icent)
{
  fMult++;
  if (!fFirstRun)
  {
    Int_t ipt = -1;
    for (int j = 0; j < npt; j++)
      if (pt >= pTBin[j] && pt < pTBin[j + 1])
        ipt = j;
    fMultPOI[ipt]++;
  }
  if (fUseProduct)
  {
    if (fFirstRun)
    {
      for (int it = 0; it < thetabins; ++it)
      {
        double dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
        for (int rbin = 0; rbin < rbins; ++rbin)
        {
          fGenFunP[rbin][it] *= TComplex(1.0, fRProduct[rbin] * dCosTerm);
        }
      }
    }
    else
    {
      for (int it = 0; it < thetabins; ++it)
      {
        double dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
        fGenfunPror0[it] *= TComplex(1.0, fR02Pro[icent][it] * dCosTerm);
        TComplex cCosTermComplex(1., fR02Pro[icent][it] * dCosTerm);
        fdGr0[it] += (dCosTerm / cCosTermComplex);
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessEventAfterFirstTrackLoop(const QVector *const Qvector, const int &icent)
{
  if (fMult != 0)
  {
    double Qx = Qvector->X();
    double Qy = Qvector->Y();
    for (int itheta = 0; itheta < thetabins; itheta++)
    {
      fQtheta[itheta] = Qx * TMath::Cos(2.0 * fTheta[itheta]) + Qy * TMath::Sin(2.0 * fTheta[itheta]);
    }
    if (fFirstRun)
    {
      for (int rbin = 0; rbin < rbins; rbin++)
      {
        for (int it = 0; it < thetabins; it++)
        {
          TComplex cExpo = TComplex(0., fRSum[rbin] * fQtheta[it]);
          fGenFunS[rbin][it] = TComplex::Exp(cExpo); // generating function from Q-vectors
        }
      }

      for (int rbin = 0; rbin < rbins; rbin++)
      {
        for (int it = 0; it < thetabins; it++)
        {
          fPrReGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Re());
          fPrImGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Im());          
          // fPrReGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Re(), fMult);
          // fPrImGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Im(), fMult);
        }
      }

      double QModSq = Qx * Qx + Qy * Qy;
      prRefMult->Fill(icent, fMult);
      prQ2x->Fill(icent, Qx);
      prQ2y->Fill(icent, Qy);
      prQ2ModSq->Fill(icent, QModSq);
      if (fUseProduct)
      {
        for (int rbin = 0; rbin < rbins; rbin++)
        {
          for (int it = 0; it < thetabins; it++)
          {
            fPrReGthetaProduct[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Re());
            fPrImGthetaProduct[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Im());            
            // fPrReGthetaProduct[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Re(), fMult);
            // fPrImGthetaProduct[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Im(), fMult);
          }
        }
      }
    }
    else
    {
      for (int ipt = 0; ipt < npt; ipt++)
      {
        fPrMultPOI[icent]->Fill(ipt + 0.5, fMultPOI[ipt]);
      }
      // Differential LYZ

      for (int it = 0; it < thetabins; it++)
      {

        fExponent[it] = TComplex(0., fR02Sum[icent][it] * fQtheta[it]);
        TComplex cDenominator = fQtheta[it] * (TComplex::Exp(fExponent[it]));

        fPrReDenom[it]->Fill(icent, cDenominator.Re());
        fPrImDenom[it]->Fill(icent, cDenominator.Im());
      }
      if (fUseProduct)
      {
        for (int it = 0; it < thetabins; it++)
        {
          TComplex cDenominator = (fGenfunPror0[it] * fdGr0[it]);
          fPrReDenomPro[it]->Fill(icent, cDenominator.Re());
          fPrImDenomPro[it]->Fill(icent, cDenominator.Im());
        }
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessSecondTrackLoop(double phi, double pt, int icent)
{
  if (!fFirstRun)
  {
    for (int it = 0; it < thetabins; ++it)
    {
      double dCosTerm = TMath::Cos(2.0 * (phi - fTheta[it]));
      TComplex cNumeratorPOI = dCosTerm * (TComplex::Exp(fExponent[it]));
      fPrReNumer[it][icent]->Fill(pt, cNumeratorPOI.Re());
      fPrImNumer[it][icent]->Fill(pt, cNumeratorPOI.Im());
      if (fUseProduct)
      {
        TComplex cCosTermComplex(1., fR02Pro[icent][it] * dCosTerm);
        TComplex cNumeratorPOIPro = fGenfunPror0[it] * dCosTerm / cCosTermComplex;
        fPrReNumerPro[it][icent]->Fill(pt, cNumeratorPOIPro.Re());
        fPrImNumerPro[it][icent]->Fill(pt, cNumeratorPOIPro.Im());
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessRootFileWithHistFromFirstRun()
{
  if (fstrInputFileFromFirstRun == "") cout << "WARNING: fstrInputFileFromFirstRun = """ << endl;
  TFile *fileHist = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];

  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile *)fileHist->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile *)fileHist->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
      if (fUseProduct)
      {
        prReGthetaProduct[i][j] = (TProfile *)fileHist->Get(Form("prReGthetaProduct_mult%d_theta%d", i, j));
        prImGthetaProduct[i][j] = (TProfile *)fileHist->Get(Form("prImGthetaProduct_mult%d_theta%d", i, j));
      }
    }
  }
  for (int ic = 0; ic < ncent; ic++)
  {
    for (int it = 0; it < thetabins; it++)
    {
      TH1F *hGthetaSum = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      fR02Sum[ic][it] = GetR0(hGthetaSum);
      if (fUseProduct)
      {
        TH1F *hGthetaPro = FillHistGtheta(prReGthetaProduct[ic][it], prImGthetaProduct[ic][it]);
        fR02Pro[ic][it] = GetR0(hGthetaPro);
      }
    }
  }
  if (fDebug)
  {
    cout << "Value of r02 from first run are:" << endl;
    cout << "fR02Sum = " << endl;
    for (int ic = 0; ic < ncent; ic++)
    {
      cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic + 1] << "%: ";
      for (int it = 0; it < thetabins; it++)
      {
        cout << fR02Sum[ic][it] << ", ";
      }
      cout << endl;
    }
    cout << "fR02Pro = " << endl;
    for (int ic = 0; ic < ncent; ic++)
    {
      cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic + 1] << "%: ";
      for (int it = 0; it < thetabins; it++)
      {
        cout << fR02Pro[ic][it] << ", ";
      }
      cout << endl;
    }
  }
}

TH1F *FlowAnalysisWithLeeYangZeros::FillHistGtheta(const TProfile *const prReGtheta, const TProfile *const prImGtheta)
{
  Int_t iNbins = prReGtheta->GetNbinsX();
  Double_t xMin = prReGtheta->GetXaxis()->GetBinLowEdge(1);
  Double_t xMax = prReGtheta->GetXaxis()->GetBinLowEdge(iNbins) + prReGtheta->GetXaxis()->GetBinWidth(iNbins);
  TH1F *hGtheta = new TH1F(Form("hist_%s", prReGtheta->GetName()), "", iNbins, xMin, xMax);
  for (int rbin = 0; rbin < iNbins; rbin++)
  {
    // get bincentre of bins in histogram
    Double_t dRe = prReGtheta->GetBinContent(rbin + 1);
    Double_t dIm = prImGtheta->GetBinContent(rbin + 1);
    TComplex cGtheta(dRe, dIm);
    //fill fHistGtheta with the modulus squared of cGtheta
    //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
    if (cGtheta.Rho2() > 3.)
      hGtheta->SetBinContent(rbin + 1, 0);
    else
      hGtheta->SetBinContent(rbin + 1, cGtheta.Rho2());
    // hGtheta->SetBinContent(rbin+1,cGtheta.Rho2());
    hGtheta->SetBinError(rbin + 1, 0.0);
  }
  return hGtheta;
}

double FlowAnalysisWithLeeYangZeros::GetR0(const TH1F *const hist)
{
  //find the first minimum of the square of the modulus of flowLYZ

  int iNbins = hist->GetNbinsX();
  double dR0 = 0.;

  for (int b = 2; b < iNbins; b++)
  {
    double dG0 = hist->GetBinContent(b);
    double dGnext = hist->GetBinContent(b + 1);
    double dGnextnext = hist->GetBinContent(b + 2);
    // cout << hist->GetBinCenter(b);
    if (dGnext > dG0 && dGnextnext > dG0 && dG0 < 1.)
    {
      double dGlast = hist->GetBinContent(b - 1);
      double dXlast = hist->GetBinCenter(b - 1);
      double dX0 = hist->GetBinCenter(b);
      double dXnext = hist->GetBinCenter(b + 1);

      dR0 = dX0 - ((dX0 - dXlast) * (dX0 - dXlast) * (dG0 - dGnext) - (dX0 - dXnext) * (dX0 - dXnext) * (dG0 - dGlast)) /
                      (2. * ((dX0 - dXlast) * (dG0 - dGnext) - (dX0 - dXnext) * (dG0 - dGlast))); //parabolic interpolated minimum
      break;                                                                                      //stop loop if minimum is found
    }                                                                                             //if

  } //b

  return dR0;
}

void FlowAnalysisWithLeeYangZeros::SaveHist()
{
  if (fFirstRun)
  {
    for (int i = 0; i < ncent; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        fPrReGthetaSum[i][j]->Write();
        fPrImGthetaSum[i][j]->Write();
        if (fUseProduct)
        {
          fPrReGthetaProduct[i][j]->Write();
          fPrImGthetaProduct[i][j]->Write();
        }
      }
    }
    prRefMult->Write();
    prQ2x->Write();
    prQ2y->Write();
    prQ2ModSq->Write();
  }
  else
  {
    for (int j = 0; j < thetabins; ++j)
    {
      fPrReDenom[j]->Write();
      fPrImDenom[j]->Write();
      for (int i = 0; i < ncent; i++)
      {
        fPrReNumer[j][i]->Write();
        fPrImNumer[j][i]->Write();
      }
      if (fUseProduct)
      {
        fPrReDenomPro[j]->Write();
        fPrImDenomPro[j]->Write();
        for (int i = 0; i < ncent; i++)
        {
          fPrReNumerPro[j][i]->Write();
          fPrImNumerPro[j][i]->Write();
        }
      }
    }
    for (int ic = 0; ic < ncent; ic++)
    {
      fPrMultPOI[ic]->Write();
    }
  }
}