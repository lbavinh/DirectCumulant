#include <FlowAnalysisWithLeeYangZerosEventPlane.h>

ClassImp(FlowAnalysisWithLeeYangZerosEventPlane);

FlowAnalysisWithLeeYangZerosEventPlane::FlowAnalysisWithLeeYangZerosEventPlane() :
fDebug(kFALSE),
fPrV2LYZEP(NULL),
fstrInputFileFromFirstRun(""),
fstrInputFileFromSecondRun(""),
fiHistogramFromSecondRun(NULL)
{
  for (Int_t it = 0; it < thetabins; it++)
  {
    fTheta[it] = 0.;
    fPrReDtheta[it] = NULL;
    fPrImDtheta[it] = NULL;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fR02Sum[ic][it] = 0.;
    }
  }
  Zero();
}

FlowAnalysisWithLeeYangZerosEventPlane::~FlowAnalysisWithLeeYangZerosEventPlane()
{
}

void FlowAnalysisWithLeeYangZerosEventPlane::Init()
{
  for (Int_t it = 0; it < thetabins; it++)
  {
    fTheta[it] = it * TMath::Pi() / (2.0 * thetabins);
  }
  ProcessRootFileWithHistFromFirstRun();
  GetHistFromLYZSecondRun();
  fPrV2LYZEP = new TProfile3D("prV2LYZEP", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
}

void FlowAnalysisWithLeeYangZerosEventPlane::Zero()
{
  fWR = 0.;
  fPsiR = 0.;
  for (Int_t i = 0; i < thetabins; ++i)
  {
    fQtheta[i] = 0.;
  }
}

// void FlowAnalysisWithLeeYangZerosEventPlane::ProcessFirstTrackLoop(const Double_t &phi, const Double_t &pt, const Int_t &icent)
// {
// }

void FlowAnalysisWithLeeYangZerosEventPlane::ProcessEventAfterFirstTrackLoop(const QVector *const &Qvector, const Int_t &icent)
{
  if (Qvector->GetMult() != 0)
  {
    Double_t dWRcos2Psi = 0., dWRsin2Psi = 0.;
    TComplex cRatio, cDtheta, cExponent;
    Double_t Qx = Qvector->X();
    Double_t Qy = Qvector->Y();
    for (Int_t it = 0; it < thetabins; it++)
    {
      fQtheta[it] = Qx * TMath::Cos(2.0 * fTheta[it]) + Qy * TMath::Sin(2.0 * fTheta[it]);
    }

    for (Int_t it = 0; it < thetabins; it++)
    {

      cExponent = TComplex(0., fR02Sum[icent][it] * fQtheta[it]);
      cDtheta = TComplex(fPrReDtheta[it]->GetBinContent(icent+1)/rootJ0, fPrImDtheta[it]->GetBinContent(icent+1)/rootJ0);
      if (cDtheta.Rho() != 0) { cRatio = TComplex::Exp(cExponent) / cDtheta;}
      else { cRatio(0.,0.); }
      dWRcos2Psi += cRatio.Re()*TMath::Cos(2.*fTheta[it]);
      dWRsin2Psi += cRatio.Re()*TMath::Sin(2.*fTheta[it]);  
    }
    dWRcos2Psi /= thetabins;
    dWRsin2Psi /= thetabins;
    fWR = TMath::Sqrt(dWRcos2Psi*dWRcos2Psi + dWRsin2Psi*dWRsin2Psi);
    
    // calculate fPsiR
    fPsiR = 0.5*TMath::ATan2(dWRsin2Psi,dWRcos2Psi);   // takes care of the signs correctly!
    if (fPsiR < 0.) { fPsiR += TMath::Pi(); }          // to shift distribution from (-pi/2 to pi/2) to (0 to pi)


  }
}

void FlowAnalysisWithLeeYangZerosEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent)
{
  Double_t dV2LYZEP = fWR * TMath::Cos(2.0*(phi-fPsiR));
  fPrV2LYZEP->Fill(dCent, pt, eta, dV2LYZEP);
}

void FlowAnalysisWithLeeYangZerosEventPlane::ProcessRootFileWithHistFromFirstRun()
{
  if (fstrInputFileFromFirstRun == "") cout << "WARNING: fstrInputFileFromFirstRun = """ << endl;
  TFile *fileHist = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];

  for (Int_t i = 0; i < ncent; ++i)
  {
    for (Int_t j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = (TProfile *)fileHist->Get(Form("prReGthetaSum_mult%d_theta%d", i, j));
      prImGthetaSum[i][j] = (TProfile *)fileHist->Get(Form("prImGthetaSum_mult%d_theta%d", i, j));
    }
  }
  TH1F *hGthetaSum;
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    for (Int_t it = 0; it < thetabins; it++)
    {
      hGthetaSum = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
      fR02Sum[ic][it] = GetR0(hGthetaSum);
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
  }
  delete fileHist;
}

TH1F *FlowAnalysisWithLeeYangZerosEventPlane::FillHistGtheta(const TProfile *const &prReGtheta, const TProfile *const &prImGtheta)
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

Double_t FlowAnalysisWithLeeYangZerosEventPlane::GetR0(const TH1F *const &hist)
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

void FlowAnalysisWithLeeYangZerosEventPlane::GetHistFromLYZSecondRun()
{
  if (fstrInputFileFromSecondRun == "") cout << "WARNING: fstrInputFileFromSecondRun = """ << endl;
  fiHistogramFromSecondRun = new TFile(fstrInputFileFromSecondRun.Data(), "read");
  for (Int_t i = 0; i < thetabins; i++)
  {
    fPrReDtheta[i] = dynamic_cast<TProfile*>
                    (fiHistogramFromSecondRun->Get(Form("prReDtheta_theta%i",i)));
    fPrImDtheta[i] = dynamic_cast<TProfile*>
                    (fiHistogramFromSecondRun->Get(Form("prImDtheta_theta%i",i)));
  }
}

void FlowAnalysisWithLeeYangZerosEventPlane::SaveHist()
{
  fPrV2LYZEP->Write();
}