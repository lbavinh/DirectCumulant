#include <FlowAnalysisWithThreeEtaSubEventPlane.h>
ClassImp(FlowAnalysisWithThreeEtaSubEventPlane);

FlowAnalysisWithThreeEtaSubEventPlane::FlowAnalysisWithThreeEtaSubEventPlane() :
  fFirstRun(true),
  fMultCut(true),
  fDebug(false),
  fPsi_L(0),
  fPsi_R(0),
  fPsi_FHCal(0),
  fQvector_L(NULL),
  fQvector_R(NULL),
  fQvector_FHCal(NULL),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrResTPCLvsR(NULL),
  fPrResTPCLvsFHCal(NULL),
  fPrResTPCRvsFHCal(NULL),
  fPrV2ThreeEtaSub(NULL)
{
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    fResTPCL[ic] = 0.;
    fResTPCR[ic] = 0.;
  }
}

FlowAnalysisWithThreeEtaSubEventPlane::~FlowAnalysisWithThreeEtaSubEventPlane()
{
}

void FlowAnalysisWithThreeEtaSubEventPlane::Init()
{
  fPrResTPCLvsR = new TProfile("prResTPCLvsR", "Left versus Right TPC event resolution", ncent, &bin_cent[0]);
  fPrResTPCLvsFHCal = new TProfile("prResTPCLvsFHCal", "Left TPC versus FHCal resolution", ncent, &bin_cent[0]);
  fPrResTPCRvsFHCal = new TProfile("prResTPCRvsFHCal", "Right TPC versus FHCal resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector();
  fQvector_R = new QVector();
  fQvector_FHCal = new QVector();
  if (!fFirstRun) 
  {
    fPrV2ThreeEtaSub = new TProfile3D("prV2ThreeEtaSub", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes();
  }  
}

void FlowAnalysisWithThreeEtaSubEventPlane::Zero()
{
  fPsi_L = 0.;
  fPsi_R = 0.;
  fPsi_FHCal = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
  fQvector_FHCal->Zero();
}

void FlowAnalysisWithThreeEtaSubEventPlane::ProcessFirstTrackLoopFHCal(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  // if ( (eta < -2. && eta > -5.) || (eta > 2. && eta < 5.) )
  if ( TMath::Abs(eta) > 2. && TMath::Abs(eta) < 5. )
  {
    fQvector_FHCal->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithThreeEtaSubEventPlane::ProcessFirstTrackLoopTPC(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  if (eta < - fEtaGap)
  {
    fQvector_L->CalQVector(phi, pt);
  }
  if (eta > fEtaGap)
  {
    fQvector_R->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithThreeEtaSubEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut && fQvector_FHCal->GetWeight() != 0)
  {
    fMultCut = false;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fQvector_FHCal->WeightQVector();
    fPsi_L = 0.5 * TMath::ATan2(fQvector_L->Y(), fQvector_L->X());
    fPsi_R = 0.5 * TMath::ATan2(fQvector_R->Y(), fQvector_R->X());
    fPsi_FHCal = 0.5 * TMath::ATan2(fQvector_FHCal->Y(), fQvector_FHCal->X());
    if (fFirstRun)
    {
      fPrResTPCLvsR->Fill(dCent, TMath::Cos( 2.0 * (fPsi_L - fPsi_R) ));
      fPrResTPCLvsFHCal->Fill(dCent, TMath::Cos( 2.0 * (fPsi_L - fPsi_FHCal) ));
      fPrResTPCRvsFHCal->Fill(dCent, TMath::Cos( 2.0 * (fPsi_R - fPsi_FHCal) ));
    }
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithThreeEtaSubEventPlane::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrResTPCLvsR = (TProfile*)fi->Get("prResTPCLvsR");
    fPrResTPCLvsFHCal = (TProfile*)fi->Get("prResTPCLvsFHCal");
    fPrResTPCRvsFHCal = (TProfile*)fi->Get("prResTPCRvsFHCal");
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      fResTPCL[ic] = TMath::Sqrt(fPrResTPCLvsR->GetBinContent(ic+1)*fPrResTPCLvsFHCal->GetBinContent(ic+1)/fPrResTPCRvsFHCal->GetBinContent(ic+1));
      fResTPCR[ic] = TMath::Sqrt(fPrResTPCLvsR->GetBinContent(ic+1)*fPrResTPCRvsFHCal->GetBinContent(ic+1)/fPrResTPCLvsFHCal->GetBinContent(ic+1));
    }
    if (fDebug)
    {
      cout << "Left TPC Resolution:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << fResTPCL[ic] <<", ";
      }
      cout << endl;
      cout << "Right TPC Resolution:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << fResTPCR[ic] <<", ";
      }
      cout << endl;
    }
  }
}

void FlowAnalysisWithThreeEtaSubEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent)
{
  if (!fMultCut && !fFirstRun)
  {
    Double_t v2EtaSubEventPlane = -999.0;
    Int_t icent = fPrResTPCLvsR->FindBin(dCent) - 1;
    if (eta < -fEtaGap && fResTPCR[icent] != 0)
    {
      v2EtaSubEventPlane = TMath::Cos( 2.0 * (phi - fPsi_R) ) / fResTPCR[icent];
      fPrV2ThreeEtaSub->Fill(dCent, pt, eta, v2EtaSubEventPlane);
    }
    else if (eta > fEtaGap && fResTPCL[icent] != 0)
    {
      v2EtaSubEventPlane = TMath::Cos( 2.0 * (phi - fPsi_L) ) / fResTPCL[icent];
      fPrV2ThreeEtaSub->Fill(dCent, pt, eta, v2EtaSubEventPlane);
    }
    else { return; }
  }
}

void FlowAnalysisWithThreeEtaSubEventPlane::SaveHist()
{
  fPrResTPCLvsR->Write();
  fPrResTPCLvsFHCal->Write();
  fPrResTPCRvsFHCal->Write();
  if (!fFirstRun) fPrV2ThreeEtaSub->Write();
}