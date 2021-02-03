


#include "FlowAnalysisWithScalarProduct.h"
ClassImp(FlowAnalysisWithScalarProduct);

FlowAnalysisWithScalarProduct::FlowAnalysisWithScalarProduct() :
  fFirstRun(true),
  fMultCut(true),
  fcQVector_L(0.,0.),
  fcQVector_R(0.,0.),
  fQvector_L(NULL),
  fQvector_R(NULL),
  // fDenom(NULL),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrDenom(NULL),
  fPrV2ScalarProduct(NULL)
{
}

FlowAnalysisWithScalarProduct::~FlowAnalysisWithScalarProduct()
{
}

void FlowAnalysisWithScalarProduct::Init()
{
  fPrDenom = new TProfile("prDenomSP", "Denominator of SP method", ncent, &bin_cent[0]);
  fQvector_L = new QVector();
  fQvector_R = new QVector();
  if (!fFirstRun) 
  {
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

void FlowAnalysisWithScalarProduct::ProcessFirstTrackLoop(const double &eta, const double &phi)
{
  if (eta < - fEtaGap)
  {
    fQvector_L->CalQVector(phi, 1.);
  }
  if (eta > fEtaGap)
  {
    fQvector_R->CalQVector(phi, 1.);
  }
}

void FlowAnalysisWithScalarProduct::ProcessEventAfterFirstTrackLoop(const double &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = false;
    // fQvector_L->WeightQVector();
    // fQvector_R->WeightQVector();
    fcQVector_L = TComplex( fQvector_L->X(), fQvector_L->Y() );
    fcQVector_R = TComplex( fQvector_R->X(), fQvector_R->Y() );
    fPrDenom->Fill(dCent, (fcQVector_L * TComplex::Conjugate(fcQVector_R)).Re() );
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithScalarProduct::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrDenom = (TProfile*)fi->Get("prDenomSP");
    for (int ic = 0; ic < ncent; ic++)
    {
      fDenom[ic] = TMath::Sqrt(fPrDenom->GetBinContent(ic+1));
    }
  }
}

void FlowAnalysisWithScalarProduct::ProcessSecondTrackLoop(const double &eta, const double &phi, const double &pt, const double &dCent)
{
  if (!fMultCut && !fFirstRun)
  {
    TComplex u2 = TComplex(TMath::Cos(2.0 * phi), TMath::Sin(2.0 * phi));
    double v2ScalarProduct = -999.0;
    if (eta < -fEtaGap)
    {
      v2ScalarProduct = ( u2 * TComplex::Conjugate(fcQVector_R) ).Re();
    }
    else if (eta > fEtaGap)
    {
      v2ScalarProduct = ( u2 * TComplex::Conjugate(fcQVector_L) ).Re();
    }
    else { return; }
    int icent = fPrDenom->FindBin(dCent) - 1;
    if (fDenom[icent] != 0)
    { 
      v2ScalarProduct /= fDenom[icent];
      fPrV2ScalarProduct->Fill(dCent, pt, eta, v2ScalarProduct);
    }
  }
}

void FlowAnalysisWithScalarProduct::SaveHist()
{
  fPrDenom->Write();
  if (!fFirstRun) fPrV2ScalarProduct->Write();
}