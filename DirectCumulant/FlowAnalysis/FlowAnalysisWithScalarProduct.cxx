


#include "FlowAnalysisWithScalarProduct.h"
ClassImp(FlowAnalysisWithScalarProduct);

FlowAnalysisWithScalarProduct::FlowAnalysisWithScalarProduct() :
  fFirstRun(kTRUE),
  fMultCut(kTRUE),
  fHarmonic(2),
  fEtaGap(0.),
  fcQVector_L(0.,0.),
  fcQVector_R(0.,0.),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fDenom(),
  fstrInputFileFromFirstRun(""),
  fPrDenom(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2ScalarProduct(nullptr)
{
}

FlowAnalysisWithScalarProduct::~FlowAnalysisWithScalarProduct()
{
}

void FlowAnalysisWithScalarProduct::Init()
{
  fPrDenom = new TProfile("prDenomSP", "Denominator of SP method", ncent, &bin_cent[0]);
  fQvector_L = new QVector(fHarmonic);
  fQvector_R = new QVector(fHarmonic);
  if (!fFirstRun) 
  {
    for (Int_t i = 0; i < npid; i++)
    {
      fPrV2vsPt[i] = new TProfile2D(Form("prV2SPvsPt_pid%i",i), Form("v_{2}{SP}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
    }
    fPrV2vsEta = new TProfile2D("prV2SPvsEta", "v_{2}{SP}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
    fPrV2ScalarProduct = new TProfile3D("prV2ScalarProduct", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes();
  }  
}

void FlowAnalysisWithScalarProduct::Zero()
{
  fcQVector_L(0.,0.);
  fcQVector_R(0.,0.);
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithScalarProduct::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight)
{
  if (eta < -fEtaGap)
  {
    fQvector_L->CalQVector(phi, weight);
  }
  if (eta > fEtaGap)
  {
    fQvector_R->CalQVector(phi, weight);
  }
}

void FlowAnalysisWithScalarProduct::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = kFALSE;
    fcQVector_L = TComplex( fQvector_L->X(), fQvector_L->Y() );
    fcQVector_R = TComplex( fQvector_R->X(), fQvector_R->Y() );
    if (fFirstRun) fPrDenom->Fill(dCent, (fcQVector_L * TComplex::Conjugate(fcQVector_R)).Re() );
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithScalarProduct::GetRes()
{
  if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
  TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  fPrDenom = dynamic_cast<TProfile*> (fi->FindObjectAny("prDenomSP"));
  if (!fPrDenom)
  {
    cerr << "Cannot find histograms from first run for Scalar Product method." << endl;
    return;
  }
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    fDenom[ic] = TMath::Sqrt(fPrDenom->GetBinContent(ic+1));
  }
}

void FlowAnalysisWithScalarProduct::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  if (!fMultCut && !fFirstRun)
  {
    TComplex u2 = TComplex(TMath::Cos(fHarmonic * phi), TMath::Sin(fHarmonic * phi));
    Double_t v2ScalarProduct;
    if (eta < -fEtaGap)
    {
      v2ScalarProduct = ( u2 * TComplex::Conjugate(fcQVector_R) ).Re();
    }
    else if (eta > fEtaGap)
    {
      v2ScalarProduct = ( u2 * TComplex::Conjugate(fcQVector_L) ).Re();
    }
    else { return; }
    Int_t icent = fPrDenom->FindBin(dCent) - 1;
    if (fDenom[icent] != 0)
    { 
      v2ScalarProduct /= fDenom[icent];
      fPrV2ScalarProduct->Fill(dCent, pt, eta, v2ScalarProduct);
      fPrV2vsPt[8]->Fill(dCent, pt, v2ScalarProduct);
      if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, v2ScalarProduct); }
      if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, v2ScalarProduct); }
      if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, v2ScalarProduct); }
      if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, v2ScalarProduct); }
      if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, v2ScalarProduct); }
      if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, v2ScalarProduct); }
      if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, v2ScalarProduct); }
    }
  }
}

void FlowAnalysisWithScalarProduct::SaveHist()
{
  if (fFirstRun) fPrDenom->Write();
  else
  {
    fPrV2ScalarProduct->Write();
    fPrV2vsEta->Write();
    for (Int_t i = 0; i < npid; i++)
    {
      fPrV2vsPt[i]->Write();
    }
  }
}

void FlowAnalysisWithScalarProduct::SaveHist(TDirectoryFile *const &outputDir)
{
  if (fFirstRun) outputDir->Add(fPrDenom);  
  else
  {
    outputDir->Add(fPrV2ScalarProduct);
    outputDir->Add(fPrV2vsEta);
    for (Int_t i = 0; i < npid; i++)
    {
      outputDir->Add(fPrV2vsPt[i]);
    }
  }
  outputDir->Write();
}