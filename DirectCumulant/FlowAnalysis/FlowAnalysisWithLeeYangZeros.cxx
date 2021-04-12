#include <FlowAnalysisWithLeeYangZeros.h>

ClassImp(FlowAnalysisWithLeeYangZeros);

FlowAnalysisWithLeeYangZeros::FlowAnalysisWithLeeYangZeros() :
fDebug(kFALSE),
fUseProduct(kFALSE),
fFirstRun(kTRUE),
fUseMultWeight(kTRUE),
fTheta(),
fQtheta(),
fQn(nullptr),
fPrReGthetaSum(),
fPrImGthetaSum(),
fHistGthetaSum(nullptr),
fPrReGthetaPro(),
fPrImGthetaPro(),
fHistGthetaPro(nullptr),
fRSum(),
fRProduct(),
fMult(0),
fGenFunS(0.),
fGenFunP(),
fWeight(1.),
fPrMultRP(nullptr),
fPrQ2x(nullptr),
fPrQ2y(nullptr),
fPrQ2ModSq(nullptr),
fstrInputFileFromFirstRun(""),
fPrReDenom(),
fPrImDenom(),
fPrReNumer(),
fPrImNumer(),
fPrMultPOI(),
fPrReDenomPro(),
fPrImDenomPro(),
fPrReNumerPro(),
fPrImNumerPro(),
fMultPOI(),
fExponent(),
fdGr0(),
fGenfunPror0(),
fR02Sum(),
fR02Pro(),
fPrReDtheta(),
fPrImDtheta()
{
}

FlowAnalysisWithLeeYangZeros::~FlowAnalysisWithLeeYangZeros()
{
}

void FlowAnalysisWithLeeYangZeros::Init()
{
  fQn = new QVector();
  for (Int_t ith = 0; ith < nTheta; ith++)
  {
    fTheta[ith] = ith * TMath::Pi() / (2.0 * nTheta);
  }
  if (fFirstRun)
  { // First run
    if (fUseMultWeight){
      if (fUseProduct) { fHistGthetaPro = new TH1F(Form("hGthetaPro"), "", rbins, rMinPro, rMaxProWithMweight); }
      else{ fHistGthetaSum = new TH1F(Form("hGthetaSum"), "", rbins, rMinSum, rMaxSumWithMweight); }      
    }else{
      if (fUseProduct) { fHistGthetaPro = new TH1F(Form("hGthetaPro"), "", rbins, rMinPro, rMaxPro); }
      else{ fHistGthetaSum = new TH1F(Form("hGthetaSum"), "", rbins, rMinSum, rMaxSum); }
    }
    for (Int_t i = 0; i < ncent; ++i)
    {
      for (Int_t j = 0; j < nTheta; ++j)
      {
        if (fUseMultWeight){
          if (fUseProduct){
            fPrReGthetaPro[i][j] = new TProfile(Form("prReGthetaPro_cent%i_theta%i", i, j), "", rbins, rMinPro, rMaxProWithMweight);
            fPrImGthetaPro[i][j] = new TProfile(Form("prImGthetaPro_cent%i_theta%i", i, j), "", rbins, rMinPro, rMaxProWithMweight);
          }else{
            fPrReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_cent%i_theta%i", i, j), "", rbins, rMinSum, rMaxSumWithMweight);
            fPrImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_cent%i_theta%i", i, j), "", rbins, rMinSum, rMaxSumWithMweight);
          }
        }else{
          if (fUseProduct){
            fPrReGthetaPro[i][j] = new TProfile(Form("prReGthetaPro_cent%i_theta%i", i, j), "", rbins, rMinPro, rMaxPro);
            fPrImGthetaPro[i][j] = new TProfile(Form("prImGthetaPro_cent%i_theta%i", i, j), "", rbins, rMinPro, rMaxPro);
          }else{
            fPrReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_cent%i_theta%i", i, j), "", rbins, rMinSum, rMaxSum);
            fPrImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_cent%i_theta%i", i, j), "", rbins, rMinSum, rMaxSum);
          }
        }
      }
    }
    if (fUseProduct)
    {
      fPrMultRP = new TProfile("prMultRPPro", "", ncent, 0, ncent);
      fPrQ2x = new TProfile("prQ2xPro", "", ncent, 0, ncent);
      fPrQ2y = new TProfile("prQ2yPro", "", ncent, 0, ncent);
      fPrQ2ModSq = new TProfile("prQ2ModSqPro", "", ncent, 0, ncent);
    }
    else
    {
      fPrMultRP = new TProfile("prMultRPSum", "", ncent, 0, ncent);
      fPrQ2x = new TProfile("prQ2xSum", "", ncent, 0, ncent);
      fPrQ2y = new TProfile("prQ2ySum", "", ncent, 0, ncent);
      fPrQ2ModSq = new TProfile("prQ2ModSqSum", "", ncent, 0, ncent);
    }
    

    for (Int_t rbin = 0; rbin < rbins; ++rbin)
    {
      if (fUseProduct) { fRProduct[rbin] = fHistGthetaPro->GetBinCenter(rbin + 1); }
      else { fRSum[rbin] = fHistGthetaSum->GetBinCenter(rbin + 1); }
    }
  }
  else
  { // Second Run
    ProcessRootFileWithHistFromFirstRun();
    
    
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      if (fUseProduct) fPrMultPOI[ic] = new TProfile(Form("prMultPOIPro_cent%i", ic), "", npt, 0, npt);
      else fPrMultPOI[ic] = new TProfile(Form("prMultPOISum_cent%i", ic), "", npt, 0, npt);
    }
    if (fUseProduct)
    {
      for (Int_t i = 0; i < nTheta; i++)
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
    else
    {
      for (Int_t i = 0; i < nTheta; i++)
      {
        fPrReDenom[i] = new TProfile(Form("prReDenom_theta%i", i), "", ncent, 0, ncent);
        fPrImDenom[i] = new TProfile(Form("prImDenom_theta%i", i), "", ncent, 0, ncent);
        for (Int_t j = 0; j < ncent; j++)
        {
          fPrReNumer[i][j] = new TProfile(Form("prReNumer_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
          fPrImNumer[i][j] = new TProfile(Form("prImNumer_theta%i_cent%i", i, j), "", npt, &pTBin[0]);
        }
        fPrReDtheta[i] = new TProfile(Form("prReDtheta_theta%i",i),"", ncent, 0, ncent); // Lee Yang Zeros Event Plane
        fPrImDtheta[i] = new TProfile(Form("prImDtheta_theta%i",i),"", ncent, 0, ncent); // Lee Yang Zeros Event Plane
      }
    }
    
  }
}

void FlowAnalysisWithLeeYangZeros::Zero()
{
  fQn->Zero();
  fWeight = 1.;
  if (fUseMultWeight) 
  {
    fMult = 0;
  }
  if (!fUseProduct)
  {
    for (Int_t i = 0; i < nTheta; ++i)
    {
      fQtheta[i] = 0.;
    }
  }
  if (fFirstRun)
  { // First Run
    if (fUseProduct) {
      for (Int_t i = 0; i < rbins; ++i) {
        for (Int_t j = 0; j < nTheta; ++j) {
          fGenFunP[i][j] = TComplex::One();
        }
      }
    }
  }
  else
  { // Second Run
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      fMultPOI[ipt] = 0.;
    }

    if (fUseProduct) {
      for (Int_t it = 0; it < nTheta; it++) {
        fdGr0[it] = TComplex(0.0, 0.0);
        fGenfunPror0[it] = TComplex::One();
      }
    }else { for (Int_t it = 0; it < nTheta; it++) fExponent[it] = TComplex(0.0, 0.0); }
    
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessZeroTrackLoopRP()
{ // Only for Product LYZ
  fMult++;
}

void FlowAnalysisWithLeeYangZeros::ProcessFirstTrackLoopRP(const Double_t &phi, const Double_t &pt, const Int_t &icent)
{
  if (fUseMultWeight && fUseProduct)
  {
    if (!fMult) { cerr << "In FlowAnalysisWithLeeYangZeros::ProcessFirstTrackLoopRP() fMult==0!!!!" << endl; return; }
    fWeight = 1.0/fMult;
  }
  fQn->CalQVector(phi, 1.);
  if (fUseProduct)
  {
    if (fFirstRun) {
      for (Int_t it = 0; it < nTheta; ++it) {
        Double_t dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
        for (Int_t rbin = 0; rbin < rbins; ++rbin) {
          fGenFunP[rbin][it] *= TComplex(1.0, fWeight * fRProduct[rbin] * dCosTerm);
        }
      }
    }else{
      for (Int_t it = 0; it < nTheta; ++it) {
        Double_t dCosTerm = TMath::Cos(2. * (phi - fTheta[it]));
        fGenfunPror0[it] *= TComplex(1.0, fWeight * fR02Pro[icent][it] * dCosTerm);
        TComplex cCosTermComplex(1., fWeight * fR02Pro[icent][it] * dCosTerm);
        fdGr0[it] += (fWeight * dCosTerm / cCosTermComplex);
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessFirstTrackLoopPOI(const Double_t &pt)
{
  if (!fFirstRun)
  {
    Int_t ipt = -1;
    for (Int_t j = 0; j < npt; j++)
      if (pt >= pTBin[j] && pt < pTBin[j + 1])
        ipt = j;
    fMultPOI[ipt]++;
  }
}
void FlowAnalysisWithLeeYangZeros::ProcessEventAfterFirstTrackLoop(const Int_t &icent)
{
  if (fQn->GetMult() != 0)
  {
    Double_t Qx = fQn->X();
    Double_t Qy = fQn->Y();
    if (!fUseProduct) {
      Double_t dWeight;
      if (fUseMultWeight) dWeight = 1./fQn->GetMult();
      else { dWeight = 1.; }
      for (Int_t ith = 0; ith < nTheta; ith++) {
        fQtheta[ith] = dWeight * (Qx * TMath::Cos(2.0 * fTheta[ith]) + Qy * TMath::Sin(2.0 * fTheta[ith]));
      }
    }
    if (fFirstRun)
    { // First run
      Double_t QModSq = Qx * Qx + Qy * Qy;
      fPrMultRP->Fill(icent, fQn->GetMult());
      fPrQ2x->Fill(icent, Qx);
      fPrQ2y->Fill(icent, Qy);
      fPrQ2ModSq->Fill(icent, QModSq);
      if (fUseProduct)
      {
        for (Int_t rbin = 0; rbin < rbins; rbin++)
        {
          for (Int_t it = 0; it < nTheta; it++)
          {
            fPrReGthetaPro[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Re());
            fPrImGthetaPro[icent][it]->Fill(fRProduct[rbin], fGenFunP[rbin][it].Im());            
          }
        }
      }
      else
      {
        for (Int_t rbin = 0; rbin < rbins; rbin++)
        {
          for (Int_t it = 0; it < nTheta; it++)
          {
            TComplex cExpo(0., fRSum[rbin] * fQtheta[it]);
            fGenFunS = TComplex::Exp(cExpo); // generating function from Q-vectors
            fPrReGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS.Re());
            fPrImGthetaSum[icent][it]->Fill(fRSum[rbin], fGenFunS.Im());
          }
        }
      }
    }
    else
    { // Second run
      for (Int_t ipt = 0; ipt < npt; ipt++)
      {
        fPrMultPOI[icent]->Fill(ipt + 0.5, fMultPOI[ipt]);
      }
      // Differential LYZ
      if (fUseProduct)
      {
        for (Int_t it = 0; it < nTheta; it++)
        {
          TComplex cDenominator = (fGenfunPror0[it] * fdGr0[it]);
          fPrReDenomPro[it]->Fill(icent, cDenominator.Re());
          fPrImDenomPro[it]->Fill(icent, cDenominator.Im());
        }
      }
      else
      {
        for (Int_t it = 0; it < nTheta; it++)
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
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessSecondTrackLoop(Double_t &phi, Double_t &pt, Int_t &icent)
{
  if (!fFirstRun)
  {
    for (Int_t it = 0; it < nTheta; ++it)
    {
      Double_t dCosTerm = TMath::Cos(2.0 * (phi - fTheta[it]));
      if (fUseProduct)
      {
        TComplex cCosTermComplex(1., fWeight * fR02Pro[icent][it] * dCosTerm);
        TComplex cNumeratorPOIPro = fGenfunPror0[it] * dCosTerm / cCosTermComplex;
        fPrReNumerPro[it][icent]->Fill(pt, cNumeratorPOIPro.Re());
        fPrImNumerPro[it][icent]->Fill(pt, cNumeratorPOIPro.Im());
      }
      else
      {
        TComplex cNumeratorPOI = dCosTerm * (TComplex::Exp(fExponent[it]));
        fPrReNumer[it][icent]->Fill(pt, cNumeratorPOI.Re());
        fPrImNumer[it][icent]->Fill(pt, cNumeratorPOI.Im());
      }
    }
  }
}

void FlowAnalysisWithLeeYangZeros::ProcessRootFileWithHistFromFirstRun()
{
  if (fstrInputFileFromFirstRun == "") cout << "WARNING: fstrInputFileFromFirstRun = """ << endl;
  TFile *fileHist = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  TProfile *prReGthetaSum[ncent][nTheta];
  TProfile *prImGthetaSum[ncent][nTheta];
  TProfile *prReGthetaPro[ncent][nTheta];
  TProfile *prImGthetaPro[ncent][nTheta];

  for (Int_t i = 0; i < ncent; ++i)
  {
    for (Int_t j = 0; j < nTheta; ++j)
    {

      if (fUseProduct)
      {
        prReGthetaPro[i][j] = dynamic_cast<TProfile*> (fileHist->FindObjectAny(Form("prReGthetaPro_cent%i_theta%i", i, j)));
        prImGthetaPro[i][j] = dynamic_cast<TProfile*> (fileHist->FindObjectAny(Form("prImGthetaPro_cent%i_theta%i", i, j)));
        if (!prReGthetaPro[i][j] || !prImGthetaPro[i][j]) { cerr << "Cannot find input hist from first run for Product LYZ method!" << endl; }
      }
      else
      {
        prReGthetaSum[i][j] = dynamic_cast<TProfile*> (fileHist->FindObjectAny(Form("prReGthetaSum_cent%i_theta%i", i, j)));
        prImGthetaSum[i][j] = dynamic_cast<TProfile*> (fileHist->FindObjectAny(Form("prImGthetaSum_cent%i_theta%i", i, j)));
        if (!prReGthetaSum[i][j] || !prImGthetaSum[i][j]) { cerr << "Cannot find input hist from first run for Sum LYZ method!" << endl; }
      }
    }
  }
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    for (Int_t it = 0; it < nTheta; it++)
    {
      if (fUseProduct)
      {
        TH1F *hGthetaPro = FillHistGtheta(prReGthetaPro[ic][it], prImGthetaPro[ic][it]);
        fR02Pro[ic][it] = GetR0(hGthetaPro);
      }
      else
      {
        TH1F *hGthetaSum = FillHistGtheta(prReGthetaSum[ic][it], prImGthetaSum[ic][it]);
        fR02Sum[ic][it] = GetR0(hGthetaSum);
      }
      
    }
  }
  if (fDebug)
  {
    cout << "Value of r02 from first run are:" << endl;
    if (fUseProduct)
    {
      cout << "fR02Pro = " << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << "Cent. " << bin_cent[ic] << "-" << bin_cent[ic + 1] << "%: ";
        for (Int_t it = 0; it < nTheta; it++)
        {
          cout << fR02Pro[ic][it] << ", ";
        }
        cout << endl;
      }
    }
    else
    {
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
                      (2. * ((dX0 - dXlast) * (dG0 - dGnext) - (dX0 - dXnext) * (dG0 - dGlast))); //parabolic Int_terpolated minimum
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
      for (Int_t j = 0; j < nTheta; ++j)
      {
        if (fUseProduct)
        {
          fPrReGthetaPro[i][j]->Write();
          fPrImGthetaPro[i][j]->Write();
        }
        else
        {
          fPrReGthetaSum[i][j]->Write();
          fPrImGthetaSum[i][j]->Write();
        }
      }
    }
    fPrMultRP->Write();
    fPrQ2x->Write();
    fPrQ2y->Write();
    fPrQ2ModSq->Write();
  }
  else
  {
    for (Int_t j = 0; j < nTheta; ++j)
    {
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
      else
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
      }
    }
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fPrMultPOI[ic]->Write();
    }
  }
}
void FlowAnalysisWithLeeYangZeros::SaveHist(TDirectoryFile *const &outputDir)
{
  if (fFirstRun)
  {
    for (Int_t i = 0; i < ncent; ++i)
    {
      for (Int_t j = 0; j < nTheta; ++j)
      {
        if (fUseProduct)
        {
          outputDir->Add(fPrReGthetaPro[i][j]);
          outputDir->Add(fPrImGthetaPro[i][j]);
        }
        else
        {
          outputDir->Add(fPrReGthetaSum[i][j]);
          outputDir->Add(fPrImGthetaSum[i][j]);
        }
      }
    }
    outputDir->Add(fPrMultRP);
    outputDir->Add(fPrQ2x);
    outputDir->Add(fPrQ2y);
    outputDir->Add(fPrQ2ModSq);
  }
  else
  {
    for (Int_t j = 0; j < nTheta; ++j)
    {
      if (fUseProduct)
      {
        outputDir->Add(fPrReDenomPro[j]);
        outputDir->Add(fPrImDenomPro[j]);
        for (Int_t i = 0; i < ncent; i++)
        {
          outputDir->Add(fPrReNumerPro[j][i]);
          outputDir->Add(fPrImNumerPro[j][i]);
        }
      }
      else
      {
        outputDir->Add(fPrReDenom[j]);
        outputDir->Add(fPrImDenom[j]);
        outputDir->Add(fPrReDtheta[j]); // LYZ-EP
        outputDir->Add(fPrImDtheta[j]); // LYZ-EP
        for (Int_t i = 0; i < ncent; i++)
        {
          outputDir->Add(fPrReNumer[j][i]);
          outputDir->Add(fPrImNumer[j][i]);
        }
      }
    }
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      outputDir->Add(fPrMultPOI[ic]);
    }
  }
  outputDir->Write();
}