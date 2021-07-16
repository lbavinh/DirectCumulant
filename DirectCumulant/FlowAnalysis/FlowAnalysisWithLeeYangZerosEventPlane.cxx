#include <FlowAnalysisWithLeeYangZerosEventPlane.h>

ClassImp(FlowAnalysisWithLeeYangZerosEventPlane);

FlowAnalysisWithLeeYangZerosEventPlane::FlowAnalysisWithLeeYangZerosEventPlane() :
fDebug(kFALSE),
fTheta(),
fQtheta(),
fQn(nullptr),
fWR(0.),
fPsiR(0.),
fstrInputFileFromFirstRun(""),
fstrInputFileFromSecondRun(""),
fR02Sum(),
fiHistogramFromSecondRun(nullptr),
fPrReDtheta(),
fPrImDtheta(),
fPrV2vsPt(),
fPrV2vsEta(nullptr),
fPrV2LYZEP(nullptr)
{
}

FlowAnalysisWithLeeYangZerosEventPlane::~FlowAnalysisWithLeeYangZerosEventPlane()
{
}

void FlowAnalysisWithLeeYangZerosEventPlane::Init()
{
  fQn = new QVector();
  for (Int_t it = 0; it < nTheta; it++)
  {
    fTheta[it] = it * TMath::Pi() / (2.0 * nTheta);
  }
  ProcessRootFileWithHistFromFirstRun();
  GetHistFromLYZSecondRun();
  for (Int_t i = 0; i < npid; i++)
  {
    fPrV2vsPt[i] = new TProfile2D(Form("prV2LYZEPvsPt_pid%i",i), Form("v_{2}{LYZ EP}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
  }
  fPrV2vsEta = new TProfile2D("prV2LYZEPvsEta", "v_{2}{LYZ EP}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
  fPrV2LYZEP = new TProfile3D("prV2LYZEP", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
}

void FlowAnalysisWithLeeYangZerosEventPlane::Zero()
{
  fQn->Zero();
  fWR = 0.;
  fPsiR = 0.;
  for (Int_t i = 0; i < nTheta; ++i)
  {
    fQtheta[i] = 0.;
  }
}

void FlowAnalysisWithLeeYangZerosEventPlane::ProcessEventAfterFirstTrackLoop(const Int_t &icent)
{
  if (fQn->GetMult() != 0)
  {
    Double_t dWRcos2Psi = 0., dWRsin2Psi = 0.;
    TComplex cRatio, cDtheta, cExponent;

    Double_t Qx = fQn->X();
    Double_t Qy = fQn->Y();
    for (Int_t it = 0; it < nTheta; it++)
    {
      fQtheta[it] = Qx * TMath::Cos(2.0 * fTheta[it]) + Qy * TMath::Sin(2.0 * fTheta[it]);
    }

    for (Int_t it = 0; it < nTheta; it++)
    {

      cExponent = TComplex(0., fR02Sum[icent][it] * fQtheta[it]);
      cDtheta = TComplex(fPrReDtheta[it]->GetBinContent(icent+1)/rootJ0, fPrImDtheta[it]->GetBinContent(icent+1)/rootJ0);
      if (cDtheta.Rho() != 0) { cRatio = TComplex::Exp(cExponent) / cDtheta;}
      else { cRatio(0.,0.); }
      dWRcos2Psi += cRatio.Re()*TMath::Cos(2.*fTheta[it]);
      dWRsin2Psi += cRatio.Re()*TMath::Sin(2.*fTheta[it]);  
    }
    dWRcos2Psi /= nTheta;
    dWRsin2Psi /= nTheta;
    fWR = TMath::Sqrt(dWRcos2Psi*dWRcos2Psi + dWRsin2Psi*dWRsin2Psi);
    
    // calculate fPsiR
    fPsiR = 0.5*TMath::ATan2(dWRsin2Psi,dWRcos2Psi);   // takes care of the signs correctly!
    if (fPsiR < 0.) { fPsiR += TMath::Pi(); }          // to shift distribution from (-pi/2 to pi/2) to (0 to pi)
  }
}

void FlowAnalysisWithLeeYangZerosEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  Double_t dV2LYZEP = fWR * TMath::Cos(2.0*(phi-fPsiR));
  fPrV2LYZEP->Fill(dCent, pt, eta, dV2LYZEP);
  fPrV2vsPt[8]->Fill(dCent, pt, dV2LYZEP);
  if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, dV2LYZEP); }
  if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, dV2LYZEP); }
  if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, dV2LYZEP); }
  if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, dV2LYZEP); }
  if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, dV2LYZEP); }
  if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, dV2LYZEP); }
  if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, dV2LYZEP); }  
}

void FlowAnalysisWithLeeYangZerosEventPlane::ProcessRootFileWithHistFromFirstRun()
{
  if (fstrInputFileFromFirstRun == "") cout << "WARNING: fstrInputFileFromFirstRun = """ << endl;
  TFile *fileHist = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  TProfile *prReGthetaSum[ncent][nTheta];
  TProfile *prImGthetaSum[ncent][nTheta];

  for (Int_t i = 0; i < ncent; ++i)
  {
    for (Int_t j = 0; j < nTheta; ++j)
    {
      prReGthetaSum[i][j] = dynamic_cast<TProfile*> (fileHist->FindObjectAny(Form("prReGthetaSum_cent%i_theta%i", i, j)));
      prImGthetaSum[i][j] = dynamic_cast<TProfile*> (fileHist->FindObjectAny(Form("prImGthetaSum_cent%i_theta%i", i, j)));
      if (!prReGthetaSum[i][j] || !prImGthetaSum[i][j])
      {
        cerr << "Cannot find input histograms from first run of SUM LYZ for LYZ EP method." << endl;
        return;
      } 
    }
  }
  TH1F *hGthetaSum;
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    for (Int_t it = 0; it < nTheta; it++)
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
      for (Int_t it = 0; it < nTheta; it++)
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
  for (Int_t i = 0; i < nTheta; i++)
  {
    fPrReDtheta[i] = dynamic_cast<TProfile*>
                    (fiHistogramFromSecondRun->FindObjectAny(Form("prReDtheta_theta%i",i)));
    fPrImDtheta[i] = dynamic_cast<TProfile*>
                    (fiHistogramFromSecondRun->FindObjectAny(Form("prImDtheta_theta%i",i)));
    if (!fPrReDtheta[i] || !fPrImDtheta[i])
    {
      cerr << "Cannot find input histograms from second run of SUM LYZ for LYZ EP method." << endl;
      return;
    }           
  }
}

void FlowAnalysisWithLeeYangZerosEventPlane::SaveHist()
{
  fPrV2LYZEP->Write();
  fPrV2vsEta->Write();
  for (Int_t i = 0; i < npid; i++)
  {
    fPrV2vsPt[i]->Write();
  }
}

void FlowAnalysisWithLeeYangZerosEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  outputDir->Add(fPrV2LYZEP);
  outputDir->Add(fPrV2vsEta);
  for (Int_t i = 0; i < npid; i++)
  {
    outputDir->Add(fPrV2vsPt[i]);
  }
  outputDir->Write();
}