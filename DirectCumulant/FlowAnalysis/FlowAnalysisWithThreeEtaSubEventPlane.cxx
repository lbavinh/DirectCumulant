#include <FlowAnalysisWithThreeEtaSubEventPlane.h>
ClassImp(FlowAnalysisWithThreeEtaSubEventPlane);

FlowAnalysisWithThreeEtaSubEventPlane::FlowAnalysisWithThreeEtaSubEventPlane() :
  fFirstRun(kTRUE),
  fMultCut(kTRUE),
  fDebug(kFALSE),
  fHarmonic(2),
  fPsi_L(0),
  fPsi_R(0),
  fPsi_FHCal(0),
  fQvector_L(nullptr),
  fQvector_R(nullptr),
  fQvector_FHCal(nullptr),
  fResTPCL(),
  fResTPCR(),
  fEtaGap(0.),
  fstrInputFileFromFirstRun(""),
  fPrResTPCLvsR(nullptr),
  fPrResTPCLvsFHCal(nullptr),
  fPrResTPCRvsFHCal(nullptr),
  fPrV2vsPt(),
  fPrV2vsEta(nullptr),
  fPrV2ThreeEtaSub(nullptr)
{
}

FlowAnalysisWithThreeEtaSubEventPlane::~FlowAnalysisWithThreeEtaSubEventPlane()
{
}

void FlowAnalysisWithThreeEtaSubEventPlane::Init()
{
  fPrResTPCLvsR = new TProfile("prResTPCLvsR", "Left versus Right TPC event resolution", ncent, &bin_cent[0]);
  fPrResTPCLvsFHCal = new TProfile("prResTPCLvsFHCal", "Left TPC versus FHCal resolution", ncent, &bin_cent[0]);
  fPrResTPCRvsFHCal = new TProfile("prResTPCRvsFHCal", "Right TPC versus FHCal resolution", ncent, &bin_cent[0]);
  fQvector_L = new QVector(fHarmonic);
  fQvector_R = new QVector(fHarmonic);
  fQvector_FHCal = new QVector(fHarmonic);
  if (!fFirstRun) 
  {
    for (Int_t i = 0; i < npid; i++)
    {
      fPrV2vsPt[i] = new TProfile2D(Form("prV2Eta3SubvsPt_pid%i",i), Form("v_{2}{3eta-sub}(p_{T}) of %s",pidNames.at(i).Data()), ncent, &bin_cent[0], npt, &pTBin[0]);
    }
    fPrV2vsEta = new TProfile2D("prV2Eta3SubvsEta", "v_{2}{3eta-sub}(#eta) of charged hadrons", ncent, &bin_cent[0], netaBin, &etaBin[0]);
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

void FlowAnalysisWithThreeEtaSubEventPlane::ProcessFirstTrackLoopFHCal(const Double_t &eta, const Double_t &phi, const Double_t &weight)
{
  if ( TMath::Abs(eta) > 2. && TMath::Abs(eta) < 5. )
  {
    fQvector_FHCal->CalQVector(phi, weight);
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
    fMultCut = kFALSE;
    fQvector_L->WeightQVector();
    fQvector_R->WeightQVector();
    fQvector_FHCal->WeightQVector();
    fPsi_L = TMath::ATan2(fQvector_L->Y(), fQvector_L->X())/fHarmonic;
    fPsi_R = TMath::ATan2(fQvector_R->Y(), fQvector_R->X())/fHarmonic;
    fPsi_FHCal = TMath::ATan2(fQvector_FHCal->Y(), fQvector_FHCal->X())/fHarmonic;
    if (fFirstRun)
    {
      fPrResTPCLvsR->Fill(dCent, TMath::Cos( fHarmonic * (fPsi_L - fPsi_R) ));
      fPrResTPCLvsFHCal->Fill(dCent, TMath::Cos( fHarmonic * (fPsi_L - fPsi_FHCal) ));
      fPrResTPCRvsFHCal->Fill(dCent, TMath::Cos( fHarmonic * (fPsi_R - fPsi_FHCal) ));
    }
  }
  else
  {
    fMultCut = kTRUE;
  }
  
}

void FlowAnalysisWithThreeEtaSubEventPlane::GetRes()
{
  if (fstrInputFileFromFirstRun == "") { cerr << "Warning: fstrInputFileFromFirstRun="" " << endl;}
  TFile *fi = new TFile(fstrInputFileFromFirstRun.Data(), "read");
  fPrResTPCLvsR = dynamic_cast<TProfile*> (fi->FindObjectAny("prResTPCLvsR"));
  fPrResTPCLvsFHCal = dynamic_cast<TProfile*> (fi->FindObjectAny("prResTPCLvsFHCal"));
  fPrResTPCRvsFHCal = dynamic_cast<TProfile*> (fi->FindObjectAny("prResTPCRvsFHCal"));
  if (!fPrResTPCLvsR || !fPrResTPCLvsFHCal || !fPrResTPCRvsFHCal)
  {
    cerr << "Cannot find histograms from first run for three eta-sub event plane method." << endl;
    return;      
  }
  for (Int_t ic = 0; ic < ncent; ic++)
  {
    fResTPCL[ic] = TMath::Sqrt(fPrResTPCLvsR->GetBinContent(ic+1)*fPrResTPCLvsFHCal->GetBinContent(ic+1)/fPrResTPCRvsFHCal->GetBinContent(ic+1));
    fResTPCR[ic] = TMath::Sqrt(fPrResTPCLvsR->GetBinContent(ic+1)*fPrResTPCRvsFHCal->GetBinContent(ic+1)/fPrResTPCLvsFHCal->GetBinContent(ic+1));
  }
  if (fDebug)
  {
    cout << "Left TPC Resolution from three eta-sub event plane method:" << endl;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      cout << fResTPCL[ic] <<", ";
    }
    cout << endl;
    cout << "Right TPC Resolution from three eta-sub event plane method:" << endl;
    for (Int_t ic = 0; ic < ncent; ic++)
    {
      cout << fResTPCR[ic] <<", ";
    }
    cout << endl;
  }
}

void FlowAnalysisWithThreeEtaSubEventPlane::ProcessSecondTrackLoop(const Double_t &eta, const Double_t &phi, const Double_t &pt, const Double_t &dCent, const Int_t &pid, const Double_t &charge)
{
  if (!fMultCut && !fFirstRun)
  {
    Double_t v2EtaSubEventPlane;
    Int_t icent = fPrResTPCLvsR->FindBin(dCent) - 1;
    if (eta < -fEtaGap && fResTPCR[icent] != 0)
    {
      v2EtaSubEventPlane = TMath::Cos( fHarmonic * (phi - fPsi_R) ) / fResTPCR[icent];
    }
    else if (eta > fEtaGap && fResTPCL[icent] != 0)
    {
      v2EtaSubEventPlane = TMath::Cos( fHarmonic * (phi - fPsi_L) ) / fResTPCL[icent];
    }
    else { return; }
    fPrV2ThreeEtaSub->Fill(dCent, pt, eta, v2EtaSubEventPlane);
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

void FlowAnalysisWithThreeEtaSubEventPlane::SaveHist()
{
  if (fFirstRun)
  {
    fPrResTPCLvsR->Write();
    fPrResTPCLvsFHCal->Write();
    fPrResTPCRvsFHCal->Write();
  }
  else
  {
    fPrV2ThreeEtaSub->Write();
    fPrV2vsEta->Write();
    for (Int_t i = 0; i < npid; i++)
    {
      fPrV2vsPt[i]->Write();
    }
  }
   
}
void FlowAnalysisWithThreeEtaSubEventPlane::SaveHist(TDirectoryFile *const &outputDir)
{
  if (fFirstRun)
  {
    outputDir->Add(fPrResTPCLvsR);
    outputDir->Add(fPrResTPCLvsFHCal);
    outputDir->Add(fPrResTPCRvsFHCal);
  }
  else
  {
    outputDir->Add(fPrV2ThreeEtaSub);
    outputDir->Add(fPrV2vsEta);
    for (Int_t i = 0; i < npid; i++)
    {
      outputDir->Add(fPrV2vsPt[i]);
    }
  }
  outputDir->Write();
}