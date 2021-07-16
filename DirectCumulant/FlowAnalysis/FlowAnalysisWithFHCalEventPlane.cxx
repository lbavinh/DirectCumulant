#include <FlowAnalysisWithFHCalEventPlane.h>
ClassImp(FlowAnalysisWithFHCalEventPlane);

FlowAnalysisWithFHCalEventPlane::FlowAnalysisWithFHCalEventPlane() :
  fFirstRun(kTRUE),
  fMultCut(kTRUE),
  fDebug(kFALSE),
  fHarmonic(2),
  fEtaGap(0.),
  fPsi_L(0.),
  fPsi_R(0.),
  fPsi(0.),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fRes2(),
  fstrInputFileFromFirstRun(""),
  fPrRes(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2FHCalEventPlane(nullptr)
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
    for (Int_t i=0; i < npid; i++)
    {
      fPrV2vsPt[i] = new TProfile2D(Form("prV2FHCalEPvsPt_pid%i",i), Form("v_{2}{FHCal EP}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
    }
    fPrV2vsEta = new TProfile2D("prV2FHCalEPvsEta", "v_{2}{FHCal EP}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
    fPrV2FHCalEventPlane = new TProfile3D("prV2FHCalEventPlane", "", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
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
  if (fQvector_L->GetWeight() != 0 && fQvector_R->GetWeight() != 0 && fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = kFALSE;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fPsi_L = TMath::ATan2(fQvector_L->Y(), fQvector_L->X());
    fPsi_R = TMath::ATan2(fQvector_R->Y(), fQvector_R->X());
    fPsi = TMath::ATan2(fQvector_L->Y()+fQvector_R->Y(),fQvector_L->X()+fQvector_R->X());
    if (fFirstRun) fPrRes->Fill(dCent, TMath::Cos( fPsi_L - fPsi_R ));
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithFHCalEventPlane::GetRes()
{
  if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
  TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  fPrRes = dynamic_cast<TProfile*> (fi->FindObjectAny("prResFHCal"));
  if (!fPrRes) cerr << "Cannot find histograms from first run for FHCAL EP method!" << endl;
  Double_t chi, res, res2, chiF, resF; 
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    res2 = fPrRes->GetBinContent(ic+1);
    res = (res2>0) ? TMath::Sqrt(res2) : 0.;
    chi = GetChi(res,1.,50);
    chiF = TMath::Sqrt(2.)*chi;
    resF = Res(chiF,fHarmonic);
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

void FlowAnalysisWithFHCalEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  if (!fMultCut && !fFirstRun) //  && fabs(eta)>=fEtaGap
  {
    Double_t v2FHCalEventPlane = TMath::Cos( fHarmonic * (phi - fPsi) );
    Int_t icent = fPrRes->FindBin(dCent) - 1;
    if (fRes2[icent] != 0)
    { 
      v2FHCalEventPlane /= fRes2[icent];
      fPrV2FHCalEventPlane->Fill(dCent, pt, eta, v2FHCalEventPlane);
      fPrV2vsPt[8]->Fill(dCent, pt, v2FHCalEventPlane);
      if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, v2FHCalEventPlane); }
      if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, v2FHCalEventPlane); }
      if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, v2FHCalEventPlane); }      
    }
  }
}

void FlowAnalysisWithFHCalEventPlane::SaveHist()
{
  if (fFirstRun) fPrRes->Write();
  else
  {
    fPrV2FHCalEventPlane->Write();
    fPrV2vsEta->Write();
    for (Int_t i=0; i < npid; i++)
    {
      fPrV2vsPt[i]->Write();
    }
  }
}
void FlowAnalysisWithFHCalEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  if (fFirstRun) outputDir->Add(fPrRes);  
  else
  {
    outputDir->Add(fPrV2FHCalEventPlane);
    outputDir->Add(fPrV2vsEta);
    for (Int_t i=0; i < npid; i++)
    {
      outputDir->Add(fPrV2vsPt[i]);
    }
  }
  outputDir->Write();
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