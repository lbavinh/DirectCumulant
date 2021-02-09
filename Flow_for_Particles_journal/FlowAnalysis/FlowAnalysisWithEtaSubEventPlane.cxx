#include <FlowAnalysisWithEtaSubEventPlane.h>
ClassImp(FlowAnalysisWithEtaSubEventPlane);

FlowAnalysisWithEtaSubEventPlane::FlowAnalysisWithEtaSubEventPlane() :
  fFirstRun(true),
  fMultCut(true),
  fPsi_L(0.),
  fPsi_R(0.),
  fQvector_L(NULL),
  fQvector_R(NULL),
  // fRes2(NULL),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrRes(NULL),
  fPrV2EtaSubEventPlane(NULL)
{
}

FlowAnalysisWithEtaSubEventPlane::~FlowAnalysisWithEtaSubEventPlane()
{
}

void FlowAnalysisWithEtaSubEventPlane::Init()
{
  fPrRes = new TProfile("prRes", "EP resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector();
  fQvector_R = new QVector();
  if (!fFirstRun) 
  {
    fPrV2EtaSubEventPlane = new TProfile3D("prV2EtaSubEventPlane", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    GetRes();
  }  
}

void FlowAnalysisWithEtaSubEventPlane::Zero()
{
  fPsi_L = 0.;
  fPsi_R = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithEtaSubEventPlane::ProcessFirstTrackLoop(const double &eta, const double &phi, const double &pt)
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

void FlowAnalysisWithEtaSubEventPlane::ProcessEventAfterFirstTrackLoop(const double &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = false;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fPsi_L = 0.5 * TMath::ATan2(fQvector_L->Y(), fQvector_L->X());
    fPsi_R = 0.5 * TMath::ATan2(fQvector_R->Y(), fQvector_R->X());
    fPrRes->Fill(dCent, TMath::Cos( 2.0 * (fPsi_L - fPsi_R) ));
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithEtaSubEventPlane::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrRes = (TProfile*)fi->Get("prRes");
    for (int ic = 0; ic < ncent; ic++)
    {
      fRes2[ic] = TMath::Sqrt(fPrRes->GetBinContent(ic+1));
    }
  }
}

void FlowAnalysisWithEtaSubEventPlane::ProcessSecondTrackLoop(const double &eta, const double &phi, const double &pt, const double &dCent)
{
  if (!fMultCut && !fFirstRun)
  {
    double v2EtaSubEventPlane = -999.0;
    if (eta < -fEtaGap)
    {
      v2EtaSubEventPlane = TMath::Cos( 2.0 * (phi - fPsi_R) );
    }
    else if (eta > fEtaGap)
    {
      v2EtaSubEventPlane = TMath::Cos( 2.0 * (phi - fPsi_L) );
    }
    else { return; }
    int icent = fPrRes->FindBin(dCent) - 1;
    if (fRes2[icent] != 0)
    { 
      v2EtaSubEventPlane /= fRes2[icent];
      fPrV2EtaSubEventPlane->Fill(dCent, pt, eta, v2EtaSubEventPlane);
    }
  }
}

void FlowAnalysisWithEtaSubEventPlane::SaveHist()
{
  fPrRes->Write();
  if (!fFirstRun) fPrV2EtaSubEventPlane->Write();
}