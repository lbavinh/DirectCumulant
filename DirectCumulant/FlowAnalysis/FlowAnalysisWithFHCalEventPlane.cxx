#include <FlowAnalysisWithFHCalEventPlane.h>
ClassImp(FlowAnalysisWithFHCalEventPlane);

FlowAnalysisWithFHCalEventPlane::FlowAnalysisWithFHCalEventPlane() :
  fFirstRun(true),
  fMultCut(true),
  fDebug(false),
  fPsi_L(0.),
  fPsi_R(0.),
  fQvector_L(NULL),
  fQvector_R(NULL),
  // fRes2(NULL),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrRes(NULL),
  fPrV2FHCalEventPlaneIntegrated(NULL),
  fPrV2FHCalEventPlane(NULL)
{
}

FlowAnalysisWithFHCalEventPlane::~FlowAnalysisWithFHCalEventPlane()
{
}

void FlowAnalysisWithFHCalEventPlane::Init()
{
  fPrRes = new TProfile("prResFHCal", "FHCal, EP resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector(1.);
  fQvector_R = new QVector(1.);
  if (!fFirstRun) 
  {
    fPrV2FHCalEventPlane = new TProfile3D("prV2FHCalEventPlane", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    if (fDebug) fPrV2FHCalEventPlaneIntegrated = new TProfile("fPrV2FHCalEventPlaneIntegrated", "", ncent, &bin_cent[0]);
    GetRes();
  }  
}

void FlowAnalysisWithFHCalEventPlane::Zero()
{
  fPsi_L = 0.;
  fPsi_R = 0.;
  fPsi = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithFHCalEventPlane::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight)
{
  if (eta < -2.0 && eta > -5.0)
  {
    fQvector_L->CalQVector(phi, -weight);
  }
  if (eta > 2.0 && eta < 5.0)
  {
    fQvector_R->CalQVector(phi, weight);
  }
}

void FlowAnalysisWithFHCalEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetWeight() != 0 && fQvector_R->GetWeight() != 0)
  {
    fMultCut = false;
    // fQvector_L->WeightQVector();
    // fQvector_R->WeightQVector();
    fPsi_L = TMath::ATan2(fQvector_L->Y(), fQvector_L->X());
    fPsi_R = TMath::ATan2(fQvector_R->Y(), fQvector_R->X());
    fPsi = TMath::ATan2(fQvector_L->Y()+fQvector_R->Y(),fQvector_L->X()+fQvector_R->X());
    fPrRes->Fill(dCent, TMath::Cos( fPsi_L - fPsi_R ));
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithFHCalEventPlane::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrRes = (TProfile*)fi->Get("prResFHCal");
    Double_t chi, res, res2, chiF, resF; 
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      res2 = fPrRes->GetBinContent(ic+1);
      res = (res2>0) ? TMath::Sqrt(res2) : 0.;
      chi = GetChi(res,1.,50);
      chiF = TMath::Sqrt(2.)*chi;
      resF = Res(chiF,2.);
      fRes2[ic]=(res!=0) ? resF : 0.;
    }
    if (fDebug)
    {
      cout << "FHCal Resolution:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << fRes2[ic] <<", ";
      }
      cout << endl;
      cout << "FHCal Chi:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        res2 = fPrRes->GetBinContent(ic+1);
        res = (res2>0) ? TMath::Sqrt(res2) : 0.;
        chi = GetChi(res,1.,50);
        chiF = TMath::Sqrt(2.)*chi;
        cout << chiF <<", ";
      }
      cout << endl;

    }
  }
}

Double_t FlowAnalysisWithFHCalEventPlane::Res(Double_t chi, Double_t harmonic)
{
  Double_t con = TMath::Sqrt(TMath::Pi() / 2) / 2;
  Double_t arg = chi * chi / 4.;
  Double_t order1 = (harmonic - 1) / 2.;
  Double_t order2 = (harmonic + 1) / 2.;
  Double_t res = con * chi * TMath::Exp(-arg) * (ROOT::Math::cyl_bessel_i(order1, arg) + ROOT::Math::cyl_bessel_i(order2, arg));
  return res;
}

Double_t FlowAnalysisWithFHCalEventPlane::GetChi(Double_t res, Double_t harmonic, Int_t accuracy)
{
  Double_t chi = 2.0;
  Double_t delta = 1.0;
  for (Int_t i = 0; i < accuracy; i++){
    if(Res(chi, harmonic) < res) chi = chi + delta;
    else chi = chi - delta;
    delta = delta / 2.;
  }
  return chi;
}

void FlowAnalysisWithFHCalEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent)
{
  if (!fMultCut && !fFirstRun) //  && fabs(eta)>=fEtaGap
  {
    Double_t v2FHCalEventPlane = TMath::Cos( 2.0 * (phi - fPsi) );
    Int_t icent = fPrRes->FindBin(dCent) - 1;
    if (fRes2[icent] != 0)
    { 
      v2FHCalEventPlane /= fRes2[icent];
      fPrV2FHCalEventPlane->Fill(dCent, pt, eta, v2FHCalEventPlane);
      if (fDebug && pt < 3.0 && pt > 0.2) fPrV2FHCalEventPlaneIntegrated->Fill(dCent, v2FHCalEventPlane);
    }
  }
}

void FlowAnalysisWithFHCalEventPlane::SaveHist()
{
  fPrRes->Write();
  if (!fFirstRun) fPrV2FHCalEventPlane->Write();
  if (!fFirstRun && fDebug)
  {
    fPrV2FHCalEventPlaneIntegrated->Write();
    cout << "const Double_t v2FHCal[" << ncent << "] = {";
    for (Int_t ic=0; ic<ncent-1; ic++)
    {
      cout << fPrV2FHCalEventPlaneIntegrated->GetBinContent(ic+1) << ", ";
    }
    cout << fPrV2FHCalEventPlaneIntegrated->GetBinContent(ncent-1) << "};" << endl;
  }
   
}