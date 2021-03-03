#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>

#include "utilities.C"

#define MAX_TRACKS 10000
class QVector
{
public:
  QVector();
  QVector(Double_t n);
  virtual ~QVector();
  void Zero();
  void CalQVector(const Double_t &phi, const Double_t &weight);
  void WeightQVector();
  Double_t X() const { return this->fQx; }
  Double_t Y() const { return this->fQy; }
  Int_t GetMult() const { return this->fMult; }

private:
  Double_t fNHarmonic;
  Double_t fQx;
  Double_t fQy;
  Double_t fWeight;
  Int_t fMult;
  // ClassDef(QVector,0);
};
// ClassImp(QVector);

QVector::QVector() : fNHarmonic(2), fQx(0), fQy(0), fMult(0), fWeight(0) 
{
}

QVector::QVector(Double_t n) : fNHarmonic(n), fQx(0), fQy(0), fMult(0), fWeight(0) 
{
}

QVector::~QVector()
{
}

void QVector::Zero()
{
  fQx = 0.;
  fQy = 0.;
  fMult = 0;
  fWeight = 0.;
}

void QVector::CalQVector(const Double_t &phi, const Double_t &weight)
{
  fQx += weight * TMath::Cos( fNHarmonic * phi );
  fQy += weight * TMath::Sin( fNHarmonic * phi );
  fWeight += weight;
  fMult++;
}

void QVector::WeightQVector()
{
  if (fMult == 0) { cout << "Warning! fMult==0!" << endl;}
  if (fMult != 0)
  {
    if (fWeight<0) fWeight *= -1.;
    fQx /= fWeight;
    fQy /= fWeight;
  }
  
}
void UrQMD(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration
  const int ncent = 9; // 0-80%
  const double bin_cent[ncent+1] = {0,5,10,20,30,40,50,60,70,80};
  const double maxptRF = 3.;
  const double minptRF = 0.2;
  const float eta_cut =  1.5;
  const float eta_gap = 0.05;
  const int mult_cut = 4;
  const double harmonic = 1.;
  // Configure input information
  TChain *chain = new TChain("mctree");

  std::ifstream file(inputFileName.Data());
  std::string line;
  while(std::getline(file, line))
  {
    chain->Add(line.c_str());
  }

  Float_t         bimp;
  Float_t         phi2;
  Float_t         phi3;
  Float_t         ecc2;
  Float_t         ecc3;
  Int_t           npart;
  Int_t           nh;
  Float_t         momx[MAX_TRACKS];   //[nh]
  Float_t         momy[MAX_TRACKS];   //[nh]
  Float_t         momz[MAX_TRACKS];   //[nh]
  Float_t         ene[MAX_TRACKS];   //[nh]
  Int_t           hid[MAX_TRACKS];   //[nh]
  Int_t           pdg[MAX_TRACKS];   //[nh]
  Short_t         charge[MAX_TRACKS];   //[nh]

  // List of branches
  TBranch        *b_bimp;   //!
  TBranch        *b_phi2;   //!
  TBranch        *b_phi3;   //!
  TBranch        *b_ecc2;   //!
  TBranch        *b_ecc3;   //!
  TBranch        *b_npart;   //!
  TBranch        *b_nh;   //!
  TBranch        *b_momx;   //!
  TBranch        *b_momy;   //!
  TBranch        *b_momz;   //!
  TBranch        *b_ene;   //!
  TBranch        *b_hid;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_charge;   //!

  chain->SetBranchAddress("bimp", &bimp, &b_bimp);
  chain->SetBranchAddress("phi2", &phi2, &b_phi2);
  chain->SetBranchAddress("phi3", &phi3, &b_phi3);
  chain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  chain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  chain->SetBranchAddress("npart", &npart, &b_npart);
  chain->SetBranchAddress("nh", &nh, &b_nh);
  chain->SetBranchAddress("momx", momx, &b_momx);
  chain->SetBranchAddress("momy", momy, &b_momy);
  chain->SetBranchAddress("momz", momz, &b_momz);
  chain->SetBranchAddress("ene", ene, &b_ene);
  chain->SetBranchAddress("hid", hid, &b_hid);
  chain->SetBranchAddress("pdg", pdg, &b_pdg);
  chain->SetBranchAddress("charge", charge, &b_charge);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(),"recreate");
  // configuration 1
  TProfile *prFHCalLTPC = new TProfile("prFHCalLTPC","",ncent,&bin_cent[0]);
  TProfile *prFHCalRTPC = new TProfile("prFHCalRTPC","",ncent,&bin_cent[0]);
  TProfile *prFHCalLR = new TProfile("prFHCalLR","",ncent,&bin_cent[0]);
  // configuration 2
  TProfile *prFHCalTPCL = new TProfile("prFHCalTPCL","",ncent,&bin_cent[0]);
  TProfile *prFHCalTPCR = new TProfile("prFHCalTPCR","",ncent,&bin_cent[0]);
  TProfile *prTPCLR = new TProfile("prTPCLR","",ncent,&bin_cent[0]);
  QVector *Q2_TPC_L = new QVector(harmonic);
  QVector *Q2_TPC_R = new QVector(harmonic);
  QVector *Q2_FHCal_L = new QVector(harmonic);
  QVector *Q2_FHCal_R = new QVector(harmonic);

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%100000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1) continue;
    int fcent = GetCentBin(cent);

    Q2_TPC_L->Zero();
    Q2_TPC_R->Zero();
    Q2_FHCal_L->Zero();
    Q2_FHCal_R->Zero();

    for (int iTrk=0; iTrk<nh; iTrk++)
    { // 1st track loop
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      if (eta<-2. && eta>-5.) { if (harmonic==1) Q2_FHCal_L->CalQVector(phi,-pt); else { Q2_FHCal_L->CalQVector(phi,pt);} }
      if (eta> 2. && eta< 5.) Q2_FHCal_R->CalQVector(phi,pt);
      if (pt < minptRF || pt > maxptRF || abs(eta)>eta_cut) continue; // track selection
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (charge == 0) continue;

      if (eta<-eta_gap) { if (harmonic==1) Q2_TPC_L->CalQVector(phi,-pt); else { Q2_TPC_L->CalQVector(phi,pt);} }
      if (eta> eta_gap) Q2_TPC_R->CalQVector(phi,pt);
      
    } // end of 1st track loop
    if (Q2_FHCal_L->GetMult() > mult_cut && Q2_FHCal_R->GetMult() > mult_cut && Q2_TPC_R->GetMult() > mult_cut && Q2_TPC_L->GetMult() > mult_cut)
    {
      Q2_FHCal_L->WeightQVector();
      Q2_FHCal_R->WeightQVector();
      Q2_TPC_L->WeightQVector();
      Q2_TPC_R->WeightQVector();
      float Psi2TPCL = TMath::ATan2(Q2_TPC_L->Y(),Q2_TPC_L->X()) / harmonic;
      float Psi2TPCR = TMath::ATan2(Q2_TPC_R->Y(),Q2_TPC_R->X()) / harmonic;
      float Psi2TPC = TMath::ATan2(Q2_TPC_L->Y()+Q2_TPC_R->Y(),Q2_TPC_R->X()+Q2_TPC_L->X()) / harmonic;
      float Psi2FHCalL = TMath::ATan2(Q2_FHCal_L->Y(),Q2_FHCal_L->X()) / harmonic;
      float Psi2FHCalR = TMath::ATan2(Q2_FHCal_R->Y(),Q2_FHCal_R->X()) / harmonic;
      float Psi2FHCal = TMath::ATan2(Q2_FHCal_R->Y()+Q2_FHCal_L->Y(),Q2_FHCal_R->X()+Q2_FHCal_L->X()) / harmonic;

      prFHCalLTPC->Fill(cent,TMath::Cos( harmonic * (Psi2FHCalL-Psi2TPC) ));
      prFHCalRTPC->Fill(cent,TMath::Cos( harmonic * (Psi2FHCalR-Psi2TPC) ));
      prFHCalLR->Fill(cent,TMath::Cos( harmonic * (Psi2FHCalL-Psi2FHCalR) ));

      // configuration 2
      prFHCalTPCL->Fill(cent,TMath::Cos( harmonic * (Psi2FHCal-Psi2TPCL) ));
      prFHCalTPCR->Fill(cent,TMath::Cos( harmonic * (Psi2FHCal-Psi2TPCR) ));
      prTPCLR->Fill(cent,TMath::Cos( harmonic * (Psi2TPCL-Psi2TPCR) ));      
    }

  } // end event loop
  cout << "Harmonic = " << harmonic << endl;
  cout << "FHCal 2-sub resolution:" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << TMath::Sqrt(prFHCalLR->GetBinContent(ic+1)) << ", ";
  }
  cout << endl;
  cout << "FHCal L 3-sub resolution:" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << TMath::Sqrt(prFHCalLTPC->GetBinContent(ic+1)*prFHCalLR->GetBinContent(ic+1)/prFHCalRTPC->GetBinContent(ic+1)) << ", ";
  }
  cout << endl;
  cout << "FHCal R 3-sub resolution:" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << TMath::Sqrt(prFHCalRTPC->GetBinContent(ic+1)*prFHCalLR->GetBinContent(ic+1)/prFHCalLTPC->GetBinContent(ic+1)) << ", ";
  }
  cout << endl;

  cout << "TPC 2-sub resolution:" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << TMath::Sqrt(prTPCLR->GetBinContent(ic+1)) << ", ";
  }
  cout << endl;
  cout << "TPC L 3-sub resolution:" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << TMath::Sqrt(prFHCalTPCL->GetBinContent(ic+1)*prTPCLR->GetBinContent(ic+1)/prFHCalTPCR->GetBinContent(ic+1)) << ", ";
  }
  cout << endl;
  cout << "TPC R 3-sub resolution:" << endl;
  for (int ic=0; ic<ncent; ic++)
  {
    cout << TMath::Sqrt(prFHCalTPCR->GetBinContent(ic+1)*prTPCLR->GetBinContent(ic+1)/prFHCalTPCL->GetBinContent(ic+1)) << ", ";
  }
  cout << endl;

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}




// root -l -b -q UrQMD.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'