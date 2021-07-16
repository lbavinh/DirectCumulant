#include <FlowAnalysisWithMCEventPlane.h>
ClassImp(FlowAnalysisWithMCEventPlane);

FlowAnalysisWithMCEventPlane::FlowAnalysisWithMCEventPlane() :
  fMultCut(kTRUE),
  fDebug(kFALSE),
  fHarmonic(2),
  fEtaGap(0.),
  fPsiRP(0.),
  fPsiEP(0.),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fPrRes(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2MCEventPlane(nullptr)
{
}

FlowAnalysisWithMCEventPlane::~FlowAnalysisWithMCEventPlane()
{
}

void FlowAnalysisWithMCEventPlane::Init()
{
  fPrRes = new TProfile("prResMCEventPlane", "MC EP resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector(fHarmonic);
  fQvector_R = new QVector(fHarmonic);

  for (Int_t i = 0; i < npid; i++)
  {
    fPrV2vsPt[i] = new TProfile2D(Form("prV2MCvsPt_pid%i",i), Form("v_{2}{MC EP}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
  }
  fPrV2vsEta = new TProfile2D("prV2MCvsEta", "v_{2}{MC EP}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
  fPrV2MCEventPlane = new TProfile3D("prV2MCEventPlane", "Testing TProfile3D", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
  
}

void FlowAnalysisWithMCEventPlane::Zero()
{
  fPsiRP = 0.;
  fPsiEP = 0.;
  fQvector_L->Zero();
  fQvector_R->Zero();
}

void FlowAnalysisWithMCEventPlane::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &weight)
{
  if (eta < - fEtaGap)
  {
    fQvector_L->CalQVector(phi, weight);
  }
  if (eta > fEtaGap)
  {
    fQvector_R->CalQVector(phi, weight);
  }
}

void FlowAnalysisWithMCEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = kFALSE;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fPsiEP = TMath::ATan2(fQvector_L->Y()+fQvector_R->Y(), fQvector_L->X()+fQvector_R->X())/fHarmonic;
    fPrRes->Fill(dCent, TMath::Cos( fHarmonic * (fPsiEP - fPsiRP) ));
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithMCEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  if (!fMultCut && TMath::Abs(eta) > fEtaGap)
  {
    Double_t v2MCEventPlane = TMath::Cos( fHarmonic * (phi - fPsiRP) );
    fPrV2MCEventPlane->Fill(dCent, pt, eta, v2MCEventPlane);
    fPrV2vsPt[8]->Fill(dCent, pt, v2MCEventPlane);
    if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, v2MCEventPlane); }
    if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, v2MCEventPlane); }
    if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, v2MCEventPlane); }
    if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, v2MCEventPlane); }
  }
}

void FlowAnalysisWithMCEventPlane::SaveHist()
{
  fPrRes->Write();
  fPrV2MCEventPlane->Write();
  fPrV2vsEta->Write();
  for (Int_t i = 0; i < npid; i++)
  {
    fPrV2vsPt[i]->Write();
  }
  
}

void FlowAnalysisWithMCEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  outputDir->Add(fPrRes); 
  outputDir->Add(fPrV2MCEventPlane);
  outputDir->Add(fPrV2vsEta);
  for (Int_t i = 0; i < npid; i++)
  {
    outputDir->Add(fPrV2vsPt[i]);
  }
  outputDir->Write();
}