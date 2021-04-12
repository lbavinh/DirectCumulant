#include <FlowAnalysisWithEtaSubEventPlane.h>
ClassImp(FlowAnalysisWithEtaSubEventPlane);

FlowAnalysisWithEtaSubEventPlane::FlowAnalysisWithEtaSubEventPlane() :
  fFirstRun(kTRUE),
  fMultCut(kTRUE),
  fDebug(kFALSE),
  fHarmonic(2),
  fPsi_L(0.),
  fPsi_R(0.),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fRes2(),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrRes(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2EtaSubEventPlane(nullptr)
{
}

FlowAnalysisWithEtaSubEventPlane::~FlowAnalysisWithEtaSubEventPlane()
{
}

void FlowAnalysisWithEtaSubEventPlane::Init()
{
  fPrRes = new TProfile("prResEtaSub", "Eta-sub, TPC EP resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector(fHarmonic);
  fQvector_R = new QVector(fHarmonic);
  if (!fFirstRun) 
  {
    for (Int_t i; i < npid; i++)
    {
      fPrV2vsPt[i] = new TProfile2D(Form("prV2EtaSubvsPt_pid%i",i), Form("v_{2}{eta-sub}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
    }
    fPrV2vsEta = new TProfile2D("prV2EtaSubvsEta", "v_{2}{eta-sub}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
    fPrV2EtaSubEventPlane = new TProfile3D("prV2EtaSubEventPlane", "Testing TProfile3D", ncent, &bin_cent[0], npt, &pTBin[0], netaBin, &etaBin[0]);
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

void FlowAnalysisWithEtaSubEventPlane::ProcessFirstTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt)
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

void FlowAnalysisWithEtaSubEventPlane::ProcessEventAfterFirstTrackLoop(const Double_t &dCent)
{
  if (fQvector_L->GetMult() > mult_EP_cut && fQvector_R->GetMult() > mult_EP_cut)
  {
    fMultCut = kFALSE;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fPsi_L = TMath::ATan2(fQvector_L->Y(), fQvector_L->X())/fHarmonic;
    fPsi_R = TMath::ATan2(fQvector_R->Y(), fQvector_R->X())/fHarmonic;
    if (fFirstRun) fPrRes->Fill(dCent, TMath::Cos( fHarmonic * (fPsi_L - fPsi_R) ));
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithEtaSubEventPlane::GetRes()
{
  if (fstrInputFileFromFirstRun == "") 
  { cerr << "Warning: in FlowAnalysisWithEtaSubEventPlane::GetRes() fstrInputFileFromFirstRun="" " << endl;}
  TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  fPrRes = dynamic_cast<TProfile*> (fi->FindObjectAny("prResEtaSub"));
  if (!fPrRes)
  {
    cerr << "Cannot find histograms from first run for eta-sub event plane method." << endl;
    return;
  }
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    fRes2[ic] = TMath::Sqrt(fPrRes->GetBinContent(ic+1));
  }
  if (fDebug)
  {
    cout << "TPC EP Resolution w.r.t. " << fHarmonic << "-th harmonic (2-eta-sub):" << endl;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      cout << fRes2[ic] <<", ";
    }
    cout << endl;
  }
}

void FlowAnalysisWithEtaSubEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  if (!fMultCut && !fFirstRun)
  {
    Double_t v2EtaSubEventPlane = -999.0;
    if (eta < -fEtaGap)
    {
      v2EtaSubEventPlane = TMath::Cos( fHarmonic * (phi - fPsi_R) );
    }
    else if (eta > fEtaGap)
    {
      v2EtaSubEventPlane = TMath::Cos( fHarmonic * (phi - fPsi_L) );
    }
    else { return; }
    Int_t icent = fPrRes->FindBin(dCent) - 1;
    if (fRes2[icent] != 0)
    {
      v2EtaSubEventPlane /= fRes2[icent];
      fPrV2EtaSubEventPlane->Fill(dCent, pt, eta, v2EtaSubEventPlane);
      fPrV2vsPt[8]->Fill(dCent, pt, v2EtaSubEventPlane);
      if (pt > 0.2 && pt < 3.0) { fPrV2vsEta->Fill(dCent, eta, v2EtaSubEventPlane); }
      if (charge>0) { fPrV2vsPt[0]->Fill(dCent, pt, v2EtaSubEventPlane); }
      if (charge<0) { fPrV2vsPt[4]->Fill(dCent, pt, v2EtaSubEventPlane); }
      if (pid>0) { fPrV2vsPt[pid]->Fill(dCent, pt, v2EtaSubEventPlane); }
      if (pid==1 || pid==5) { fPrV2vsPt[9]->Fill(dCent, pt, v2EtaSubEventPlane); }
      if (pid==2 || pid==6) { fPrV2vsPt[10]->Fill(dCent, pt, v2EtaSubEventPlane); }
      if (pid==3 || pid==7) { fPrV2vsPt[11]->Fill(dCent, pt, v2EtaSubEventPlane); }
    }
  }
}

void FlowAnalysisWithEtaSubEventPlane::SaveHist()
{
  if (fFirstRun) fPrRes->Write();
  else
  {
    fPrV2EtaSubEventPlane->Write();
    fPrV2vsEta->Write();
    for (Int_t i; i < npid; i++)
    {
      fPrV2vsPt[i]->Write();
    }
  }
}

void FlowAnalysisWithEtaSubEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  if (fFirstRun) outputDir->Add(fPrRes); 
  else
  {
    outputDir->Add(fPrV2EtaSubEventPlane);
    outputDir->Add(fPrV2vsEta);
    for (Int_t i; i < npid; i++)
    {
      outputDir->Add(fPrV2vsPt[i]);
    }
  }
  outputDir->Write();
}