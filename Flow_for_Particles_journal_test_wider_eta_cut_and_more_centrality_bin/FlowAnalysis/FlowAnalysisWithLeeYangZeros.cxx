#include <FlowAnalysisWithLeeYangZeros.h>

ClassImp(FlowAnalysisWithLeeYangZeros);

FlowAnalysisWithLeeYangZeros::FlowAnalysisWithLeeYangZeros() :
  fDebug(kFALSE),
  fUseProduct(kFALSE),
  fFirstRun(kTRUE),
  fHistGthetaSum(NULL),
  fHistGthetaProduct(NULL),
  prRefMult(NULL),
  prQ2x(NULL),
  prQ2y(NULL),
  prQ2ModSq(NULL),
  fstrInputFileFromFirstRun("")
{
  for (Int_t i = 0; i < ncent; ++i)
  {
    for (Int_t j = 0; j < thetabins; ++j)
    {
      fPrReGthetaSum[i][j] = NULL;
      fPrImGthetaSum[i][j] = NULL;
      if (fUseProduct)
      {
        fPrReGthetaProduct[i][j] = NULL;
        fPrImGthetaProduct[i][j] = NULL;
      }
    }
  }
  for (Int_t it = 0; it < thetabins; it++)
  {
    fPrReDtheta[it] = NULL;
    fPrImDtheta[it] = NULL;
    fPrReDenom[it] = NULL;
    fPrImDenom[it] = NULL;
    if (fUseProduct)
    {
      fPrReDenomPro[it] = NULL;
      fPrImDenomPro[it] = NULL;
    }
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fPrReNumer[it][ic] = NULL;
      fPrImNumer[it][ic] = NULL;
      if (fUseProduct)
      {
        fPrReNumerPro[it][ic] = NULL;
        fPrImNumerPro[it][ic] = NULL;
      }
    }
  }
  Zero();
}

FlowAnalysisWithLeeYangZeros::~FlowAnalysisWithLeeYangZeros()
{
}

void FlowAnalysisWithLeeYangZeros::Init()
{
  for (Int_t itheta = 0; itheta < thetabins; itheta++)
  {
    fTheta[itheta] = itheta * TMath::Pi() / (2.0 * thetabins);
  }
  if (fFirstRun)
  {
    fHistGthetaSum = new TH1F(Form("hGthetaSum"), "", rbins, rMinSum, rMaxSum);
    if (fUseProduct)
      fHistGthetaProduct = new TH1F(Form("hGthetaProduct"), "", rbins, rMin, rMax);
    for (Int_t i = 0; i < ncent; ++i)
    {
      for (Int_t j = 0; j < thetabins; ++j)
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

    for (Int_t rbin = 0; rbin < rbins; ++rbin)
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
  { // Second Run 
    ProcessRootFileWithHistFromFirstRun();
    for (Int_t i = 0; i < thetabins; i++)
    {
      fPrReDenom[i] = new TProfile(Form("prReDenom_theta%i", i), "", ncent, 0, ncent);
      fPrImDenom[i] = new TProfile(Form("prImDenom_theta%i", i), "", ncent, 0, ncent);

      for (Int_t j = 0; j < ncent; j++)
      {
        fPrReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
        fPrImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
      }
    }
    if (fUseProduct)
    {
      for (Int_t i = 0; i < thetabins; i++)
      {
        fPrReDenomPro[i] = new TProfile(Form("prReDenomPro_theta%i", i), "", ncent, 0, ncent);
        fPrImDenomPro[i] = new TProfile(Form("prImDenomPro_theta%i", i), "", ncent, 0, ncent);

        for (Int_t j = 0; j < ncent; j++)
        {
          fPrReNumerPro[i][j] = new TProfile(Form("prReNumerPro_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
          fPrImNumerPro[i][j] = new TProfile(Form("prImNumerPro_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
        }
      }
    }
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fPrMultPOI[ic] = new TProfile(Form("prMultPOI_cent%i", ic), "", npt, 0, npt);
    }
    for (Int_t i = 0; i < thetabins; i++)
    { // Lee Yang Zeros Event Plane
      fPrReDtheta[i] = new TProfile(Form("prReDtheta_theta%i",i),"", ncent, 0, ncent);
      fPrImDtheta[i] = new TProfile(Form("prImDtheta_theta%i",i),"", ncent, 0, ncent);
    }
  }
}

void FlowAnalysisWithLeeYangZeros::Zero()
{
  fMult = 0.;
  for (Int_t i = 0; i < thetabins; ++i)
  {
    fQtheta[i] = 0.;
  }
  if (fFirstRun)
  {
    for (Int_t i = 0; i < rbins; ++i)
    {
      for (Int_t j = 0; j < thetabins; ++j)
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
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      fMultPOI[ipt] = 0.;
    }
    for (Int_t it = 0; it < thetabins; it++)
    {
      fExponent[it] = TComplex(0.0, 0.0);
      fdGr0[it] = TComplex(0.0, 0.0);
      fGenfunPror0[it] = TComplex::One();
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessFirstTrackLoop(const Double_t &phi, const Double_t &pt, const Int_t &icent)
{
  fMult++;
  if (!fFirstRun)
  {
    Int_t ipt = -1;
    for (Int_t j = 0; j < npt; j++)
      if (pt >= pTBin[j] && pt < pTBin[j + 1])
        ipt = j;
    fMultPOI[ipt]++;
  }
  if (fUseProduct)
  {
    if (fFirstRun)
    {
      for (Int_t it = 0; it < thetabins; ++it)
      {
        Double_t dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
        for (Int_t rbin = 0; rbin < rbins; ++rbin)
        {
          fGenFunP[rbin][it] *= TComplex(1.0, fRProduct[rbin] * dCosTerm);
        }
      }
    }
    else
    {
      for (Int_t it = 0; it < thetabins; ++it)
      {
        Double_t dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
        fGenfunPror0[it] *= TComplex(1.0, fR02Pro[icent][it] * dCosTerm);
        TComplex cCosTermComplex(1., fR02Pro[icent][it] * dCosTerm);
        fdGr0[it] += (dCosTerm / cCosTermComplex);
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessEventAfterFirstTrackLoop(const QVector *const &Qvector, const Int_t &icent)
{
  if (fMult != 0)
  {
    Double_t Qx = Qvector->X();
    Double_t Qy = Qvector->Y();
    for (Int_t itheta = 0; itheta < thetabins; itheta++)
    {
      fQtheta[itheta] = Qx * TMath::Cos(2.0 * fTheta[itheta]) + Qy * TMath::Sin(2.0 * fTheta[itheta]);
    }
    if (fFirstRun)
    {
      for (Int_t rbin = 0; rbin < rbins; rbin++)
      {
        for (Int_t it = 0; it < thetabins; it++)
        {
          TComplex cExpo = TComplex(0., fRSum[rbin] * fQtheta[it]);
          fGenFunS[rbin][it] = TComplex::Exp(cExpo); // generating function from Q-vectors
        }
      }

      for (Int_t rbin = 0; rbin < rbins; rbin++)
      {
        for (Int_t it = 0; it < thetabins; it++)
        {
          // fPrReGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Re());
          // fPrImGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Im());          
          fPrReGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Re(), fMult);
          fPrImGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS[rbin][it].Im(), fMult);
        }
      }

      Double_t QModSq = Qx * Qx + Qy * Qy;
      prRefMult->Fill(icent, fMult);
      prQ2x->Fill(icent, Qx);
      prQ2y->Fill(icent, Qy);
      prQ2ModSq->Fill(icent, QModSq);
      if (fUseProduct)
      {
        for (Int_t rbin = 0; rbin < rbins; rbin++)
        {
          for (Int_t it = 0; it < thetabins; it++)
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
    { // Second Run
      for (Int_t ipt = 0; ipt < npt; ipt++)
      {
        fPrMultPOI[icent]->Fill(ipt + 0.5, fMultPOI[ipt]);
      }
      // Differential LYZ

      for (Int_t it = 0; it < thetabins; it++)
      {

        fExponent[it] = TComplex(0., fR02Sum[icent][it] * fQtheta[it]);
        TComplex cDenominator = fQtheta[it] * (TComplex::Exp(fExponent[it]));

        fPrReDenom[it]->Fill(icent, cDenominator.Re());
        fPrImDenom[it]->Fill(icent, cDenominator.Im());

        // LYZ-EP
        TComplex cTemporary = fR02Sum[icent][it]*fQtheta[it]*TComplex::Exp(fExponent[it]);
        fPrReDtheta[it]->Fill(icent, cTemporary.Re());
        fPrImDtheta[it]->Fill(icent, cTemporary.Im());
      }
      if (fUseProduct)
      {
        for (Int_t it = 0; it < thetabins; it++)
        {
          TComplex cDenominator = (fGenfunPror0[it] * fdGr0[it]);
          fPrReDenomPro[it]->Fill(icent, cDenominator.Re());
          fPrImDenomPro[it]->Fill(icent, cDenominator.Im());
        }
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessSecondTrackLoop(const Double_t &phi, const Double_t &pt, const Int_t &icent)
{
  if (!fFirstRun)
  {
    for (Int_t it = 0; it < thetabins; ++it)
    {
      Double_t dCosTerm = TMath::Cos(2.0 * (phi - fTheta[it]));
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

  for (Int_t i = 0; i < ncent; ++i)
  {
    for (Int_t j = 0; j < thetabins; ++j)
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
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    for (Int_t it = 0; it < thetabins; it++)
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
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic + 1] << "%: ";
      for (Int_t it = 0; it < thetabins; it++)
      {
        cout << fR02Sum[ic][it] << ", ";
      }
      cout << endl;
    }
    cout << "fR02Pro = " << endl;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic + 1] << "%: ";
      for (Int_t it = 0; it < thetabins; it++)
      {
        cout << fR02Pro[ic][it] << ", ";
      }
      cout << endl;
    }
  }
  delete fileHist;
}

TH1F *FlowAnalysisWithLeeYangZeros::FillHistGtheta(const TProfile *const &prReGtheta, const TProfile *const &prImGtheta)
{
  Int_t iNbins = prReGtheta->GetNbinsX();
  Double_t xMin = prReGtheta->GetXaxis()->GetBinLowEdge(1);
  Double_t xMax = prReGtheta->GetXaxis()->GetBinLowEdge(iNbins) + prReGtheta->GetXaxis()->GetBinWidth(iNbins);
  TH1F *hGtheta = new TH1F(Form("hist_%s", prReGtheta->GetName()), "", iNbins, xMin, xMax);
  for (Int_t rbin = 0; rbin < iNbins; rbin++)
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

Double_t FlowAnalysisWithLeeYangZeros::GetR0(const TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of flowLYZ

  Int_t iNbins = hist->GetNbinsX();
  Double_t dR0 = 0.;

  for (Int_t b = 2; b < iNbins; b++)
  {
    Double_t dG0 = hist->GetBinContent(b);
    Double_t dGnext = hist->GetBinContent(b + 1);
    Double_t dGnextnext = hist->GetBinContent(b + 2);
    // cout << hist->GetBinCenter(b);
    if (dGnext > dG0 && dGnextnext > dG0 && dG0 < 1.)
    {
      Double_t dGlast = hist->GetBinContent(b - 1);
      Double_t dXlast = hist->GetBinCenter(b - 1);
      Double_t dX0 = hist->GetBinCenter(b);
      Double_t dXnext = hist->GetBinCenter(b + 1);

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
    for (Int_t i = 0; i < ncent; ++i)
    {
      for (Int_t j = 0; j < thetabins; ++j)
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
    for (Int_t j = 0; j < thetabins; ++j)
    {
      fPrReDenom[j]->Write();
      fPrImDenom[j]->Write();

      fPrReDtheta[j]->Write(); // LYZ-EP
      fPrImDtheta[j]->Write(); // LYZ-EP

      for (Int_t i = 0; i < ncent; i++)
      {
        fPrReNumer[j][i]->Write();
        fPrImNumer[j][i]->Write();
      }
      if (fUseProduct)
      {
        fPrReDenomPro[j]->Write();
        fPrImDenomPro[j]->Write();
        for (Int_t i = 0; i < ncent; i++)
        {
          fPrReNumerPro[j][i]->Write();
          fPrImNumerPro[j][i]->Write();
        }
      }
    }
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fPrMultPOI[ic]->Write();
    }
  }
}