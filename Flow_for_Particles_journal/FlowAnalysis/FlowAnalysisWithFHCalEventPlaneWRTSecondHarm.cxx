#include <FlowAnalysisWithFHCalEventPlaneWRTSecondHarm.h>
ClassImp(FlowAnalysisWithFHCalEventPlaneWRTSecondHarm);

FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::FlowAnalysisWithFHCalEventPlaneWRTSecondHarm() :
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

FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::~FlowAnalysisWithFHCalEventPlaneWRTSecondHarm()
{
}

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::Init()
{
  fPrRes = new TProfile("prRes2FHCal", "FHCal EP resolution with respect to 2-nd harmonic", ncent, &bin_cent[0]);
  fQvector_L = new QVector(2.);
  fQvector_R = new QVector(2.);
  if (!fFirstRun) 
  {
    fPrV2FHCalEventPlane = new TProfile3D("prV2FHCalEventPlaneWRTSecondHarm", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
    if (fDebug) fPrV2FHCalEventPlaneIntegrated = new TProfile("fPrV2FHCalEventPlaneIntegratedWRTSecondHarm", "", ncent, &bin_cent[0]);
    GetRes();
  }  
}

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::Zero()
{
  fPsi_L = 0.;
  fPsi_R = 0.;
  fPsi = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt)
{
  if (eta < -2.0 && eta > -5.0)
  {
    fQvector_L->CalQVector(phi, pt);
  }
  if (eta > 2.0 && eta < 5.0)
  {
    fQvector_R->CalQVector(phi, pt);
  }
}

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > 0 && fQvector_R->GetMult() > 0)
  { // mult_EP_cut
    fMultCut = false;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fPsi_L = 0.5 * TMath::ATan2(fQvector_L->Y(), fQvector_L->X());
    fPsi_R = 0.5 * TMath::ATan2(fQvector_R->Y(), fQvector_R->X());
    fPsi = 0.5 * TMath::ATan2(fQvector_L->Y()+fQvector_R->Y(),fQvector_L->X()+fQvector_R->X());
    if (fFirstRun) fPrRes->Fill(dCent, TMath::Cos( 2.0 *(fPsi_L - fPsi_R) ));
  }
  else
  {
    fMultCut = true;
  }
  
}

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::GetRes()
{
  if (!fFirstRun)
  {
    if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
    TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
    fPrRes = (TProfile*)fi->Get("prRes2FHCal");
    Double_t chi, res, res2, chiF, resF; 
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      res2 = fPrRes->GetBinContent(ic+1);
      res = (res2>0) ? TMath::Sqrt(res2) : 0.;
      chi = GetChi(res,1.,50);
      chiF = TMath::Sqrt(2.)*chi;
      resF = Res(chiF,1.);
      fRes2[ic]=(res!=0) ? resF : 0.;
    }
    if (fDebug)
    {
      cout << "FHCal Resolution w.r.t 2-nd harmonic:" << endl;
      for (Int_t ic = 0; ic < ncent; ic++)
      {
        cout << fRes2[ic] <<", ";
      }
      cout << endl;
      // cout << "FHCal Chi:" << endl;
      // for (Int_t ic = 0; ic < ncent; ic++)
      // {
      //   res2 = fPrRes->GetBinContent(ic+1);
      //   res = (res2>0) ? TMath::Sqrt(res2) : 0.;
      //   chi = GetChi(res,1.,50);
      //   chiF = TMath::Sqrt(2.)*chi;
      //   cout << chiF <<", ";
      // }
      // cout << endl;

    }
  }
}

Double_t FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::Res(Double_t chi, Double_t harmonic)
{
  Double_t con = TMath::Sqrt(TMath::Pi() / 2) / 2;
  Double_t arg = chi * chi / 4.;
  Double_t order1 = (harmonic - 1) / 2.;
  Double_t order2 = (harmonic + 1) / 2.;
  Double_t res = con * chi * TMath::Exp(-arg) * (ROOT::Math::cyl_bessel_i(order1, arg) + ROOT::Math::cyl_bessel_i(order2, arg));
  return res;
}

Double_t FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::GetChi(Double_t res, Double_t harmonic, Int_t accuracy)
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

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent)
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

void FlowAnalysisWithFHCalEventPlaneWRTSecondHarm::SaveHist()
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