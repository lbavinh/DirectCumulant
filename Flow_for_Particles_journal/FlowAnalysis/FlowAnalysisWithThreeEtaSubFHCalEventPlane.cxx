#include <FlowAnalysisWithThreeEtaSubFHCalEventPlane.h>
ClassImp(FlowAnalysisWithThreeEtaSubFHCalEventPlane);

FlowAnalysisWithThreeEtaSubFHCalEventPlane::FlowAnalysisWithThreeEtaSubFHCalEventPlane() :
  fFirstRun(true),
  fMultCut(true),
  fDebug(false),
  fPsiTPCL(0),
  fPsiTPCR(0),
  fPsiFHCal(0),
  fQvectorTPCL(NULL),
  fQvectorTPCR(NULL),
  fQvectorFHCalL(NULL),
  fQvectorFHCalR(NULL),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrResTPCLvsR(NULL),
  fPrResTPCLvsFHCal(NULL),
  fPrResTPCRvsFHCal(NULL),
  fPrV2ThreeEtaSubFHCal(NULL)
{
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    fResFHCal[ic] = 0.;
  }
}

FlowAnalysisWithThreeEtaSubFHCalEventPlane::~FlowAnalysisWithThreeEtaSubFHCalEventPlane()
{
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::Init()
{
  fPrResTPCLvsR = new TProfile("prRes1TPCLvsR", "Left versus Right TPC event resolution w.r.t 1-st harmonic", ncent, &bin_cent[0]);
  fPrResTPCLvsFHCal = new TProfile("prRes1TPCLvsFHCal", "Left TPC versus FHCal resolution w.r.t 1-st harmonic", ncent, &bin_cent[0]);
  fPrResTPCRvsFHCal = new TProfile("prRes1TPCRvsFHCal", "Right TPC versus FHCal resolution w.r.t 1-st harmonic", ncent, &bin_cent[0]);
  fQvectorTPCL = new QVector(1.);
  fQvectorTPCR = new QVector(1.);
  fQvectorFHCalL = new QVector(1.);
  fQvectorFHCalR = new QVector(1.);
  if (!fFirstRun) 
  {
    fPrV2ThreeEtaSubFHCal = new TProfile3D("prV2ThreeEtaSubFHCal", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes();
  }  
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::Zero()
{
  fPsiTPCL = 0.;
  fPsiTPCR = 0.;
  fPsiFHCal = 0.;
  fQvectorTPCL->Zero();
  fQvectorTPCR->Zero();
  fQvectorFHCalL->Zero();
  fQvectorFHCalR->Zero();
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::ProcessFirstTrackLoopFHCal(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  if ( eta < -2. && eta > -5. )
  {
    fQvectorFHCalL->CalQVector(phi, -pt);
  }
  if ( eta > 2. && eta < 5. )
  {
    fQvectorFHCalR->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::ProcessFirstTrackLoopTPC(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  if (eta < -1.) // fEtaGap
  {
    fQvectorTPCL->CalQVector(phi, pt);
  }
  if (eta > 1.) // fEtaGap
  {
    fQvectorTPCR->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvectorTPCL->GetMult() > 0 && fQvectorTPCR->GetMult() > 0 && fQvectorFHCalL->GetMult() > 0 && fQvectorFHCalR->GetMult() > 0)
  {
    fMultCut = false;
    fQvectorTPCL->WeightQVector();
    fQvectorTPCR->WeightQVector();
    fQvectorFHCalL->WeightQVector();
    fQvectorFHCalR->WeightQVector();
    fPsiTPCL = TMath::ATan2(fQvectorTPCL->Y(), fQvectorTPCL->X());
    fPsiTPCR = TMath::ATan2(fQvectorTPCR->Y(), fQvectorTPCR->X());
    fPsiFHCal = TMath::ATan2(fQvectorFHCalL->Y()+fQvectorFHCalR->Y(), fQvectorFHCalL->X()+fQvectorFHCalR->X());
    if (fFirstRun)
    {
      fPrResTPCLvsR->Fill(dCent, TMath::Cos( (fPsiTPCL - fPsiTPCR) ));
      fPrResTPCLvsFHCal->Fill(dCent, TMath::Cos( (fPsiTPCL - fPsiFHCal) ));
      fPrResTPCRvsFHCal->Fill(dCent, TMath::Cos( (fPsiTPCR - fPsiFHCal) ));
    }
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrResTPCLvsR = (TProfile*)fi->Get("prRes1TPCLvsR");
    fPrResTPCLvsFHCal = (TProfile*)fi->Get("prRes1TPCLvsFHCal");
    fPrResTPCRvsFHCal = (TProfile*)fi->Get("prRes1TPCRvsFHCal");
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fResFHCal[ic] = TMath::Sqrt(fPrResTPCRvsFHCal->GetBinContent(ic+1)*fPrResTPCLvsFHCal->GetBinContent(ic+1)/fPrResTPCLvsR->GetBinContent(ic+1));
    }
    if (fDebug)
    {
      cout << "FHCal Resolution (3sub-event) with respect to 1-st harm:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << fResFHCal[ic] <<", ";
      }
      cout << endl;
    }
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent)
{
  if (!fMultCut && !fFirstRun)
  {
    Double_t v2ThreeEtaSubFHCalEventPlane = -999.0;
    Int_t icent = fPrResTPCLvsR->FindBin(dCent) - 1;
    if (fResFHCal[icent] != 0)
    {
      v2ThreeEtaSubFHCalEventPlane = TMath::Cos( 2.0 * (phi - fPsiFHCal) ) / fResFHCal[icent];
      fPrV2ThreeEtaSubFHCal->Fill(dCent, pt, eta, v2ThreeEtaSubFHCalEventPlane);
    }
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlane::SaveHist()
{
  fPrResTPCLvsR->Write();
  fPrResTPCLvsFHCal->Write();
  fPrResTPCRvsFHCal->Write();
  if (!fFirstRun) fPrV2ThreeEtaSubFHCal->Write();
}