#include <FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm.h>
ClassImp(FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm);

FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm() :
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

FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::~FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm()
{
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::Init()
{
  fPrResTPCLvsR = new TProfile("prRes2TPCLvsR", "Left versus Right TPC event resolution", ncent, &bin_cent[0]);
  fPrResTPCLvsFHCal = new TProfile("prRes2TPCLvsFHCal", "Left TPC versus FHCal resolution", ncent, &bin_cent[0]);
  fPrResTPCRvsFHCal = new TProfile("prRes2TPCRvsFHCal", "Right TPC versus FHCal resolution", ncent, &bin_cent[0]);
  fQvectorTPCL = new QVector();
  fQvectorTPCR = new QVector();
  fQvectorFHCalL = new QVector();
  fQvectorFHCalR = new QVector();
  if (!fFirstRun) 
  {
    fPrV2ThreeEtaSubFHCal = new TProfile3D("prV2ThreeEtaSubFHCalWRTSecondHarm", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes();
  }  
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::Zero()
{
  fPsiTPCL = 0.;
  fPsiTPCR = 0.;
  fPsiFHCal = 0.;
  fQvectorTPCL->Zero();
  fQvectorTPCR->Zero();
  fQvectorFHCalL->Zero();
  fQvectorFHCalR->Zero();
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::ProcessFirstTrackLoopFHCal(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  if ( eta < -2. && eta > -5. )
  {
    fQvectorFHCalL->CalQVector(phi, pt);
  }
  if ( eta > 2. && eta < 5. )
  {
    fQvectorFHCalR->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::ProcessFirstTrackLoopTPC(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  if (eta < - fEtaGap)
  {
    fQvectorTPCL->CalQVector(phi, pt);
  }
  if (eta > fEtaGap)
  {
    fQvectorTPCR->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvectorTPCL->GetMult() > 0 && fQvectorTPCR->GetMult() > 0 && fQvectorFHCalL->GetMult() > 0 && fQvectorFHCalR->GetMult() > 0)
  {
    fMultCut = false;
    fQvectorTPCL->WeightQVector();
    fQvectorTPCR->WeightQVector();
    fQvectorFHCalL->WeightQVector();
    fQvectorFHCalR->WeightQVector();
    fPsiTPCL = 0.5 * TMath::ATan2(fQvectorTPCL->Y(), fQvectorTPCL->X());
    fPsiTPCR = 0.5 * TMath::ATan2(fQvectorTPCR->Y(), fQvectorTPCR->X());
    fPsiFHCal = 0.5 * TMath::ATan2(fQvectorFHCalL->Y()+fQvectorFHCalR->Y(), fQvectorFHCalL->X()+fQvectorFHCalR->X());
    if (fFirstRun)
    {
      fPrResTPCLvsR->Fill(dCent, TMath::Cos( 2.0 * (fPsiTPCL - fPsiTPCR) ));
      fPrResTPCLvsFHCal->Fill(dCent, TMath::Cos( 2.0 * (fPsiTPCL - fPsiFHCal) ));
      fPrResTPCRvsFHCal->Fill(dCent, TMath::Cos( 2.0 * (fPsiTPCR - fPsiFHCal) ));
    }
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrResTPCLvsR = (TProfile*)fi->Get("prRes2TPCLvsR");
    fPrResTPCLvsFHCal = (TProfile*)fi->Get("prRes2TPCLvsFHCal");
    fPrResTPCRvsFHCal = (TProfile*)fi->Get("prRes2TPCRvsFHCal");
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fResFHCal[ic] = TMath::Sqrt(fPrResTPCRvsFHCal->GetBinContent(ic+1)*fPrResTPCLvsFHCal->GetBinContent(ic+1)/fPrResTPCLvsR->GetBinContent(ic+1));
    }
    if (fDebug)
    {
      cout << "FHCal Resolution (3sub-event) with respect to 2-nd harm:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << fResFHCal[ic] <<", ";
      }
      cout << endl;
    }
  }
}

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent)
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

void FlowAnalysisWithThreeEtaSubFHCalEventPlaneWRTSecondHarm::SaveHist()
{
  fPrResTPCLvsR->Write();
  fPrResTPCLvsFHCal->Write();
  fPrResTPCRvsFHCal->Write();
  if (!fFirstRun) fPrV2ThreeEtaSubFHCal->Write();
}