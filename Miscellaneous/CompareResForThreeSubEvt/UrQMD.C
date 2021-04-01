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
  const Int_t npt = 16; // 0-3.6 GeV/c - number of pT bins
  const Double_t pTBin[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
  // const Double_t pTBin[npt + 1] = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
  // const Double_t pTBin[npt + 1] = {0., 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8};
  // const Int_t netaBin = 14;
  // const Double_t etaBin[netaBin+1] = {-1.5,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.,1.2,1.5};
  const int ncent = 9; // 0-80%
  const double bin_cent[ncent+1] = {0,5,10,20,30,40,50,60,70,80};
  // const double maxptRF = 0.5;
  // const double minptRF = 0.2;
  const double maxpt = 3.6;
  const double minpt = 0.0;
  const float eta_cut =  1.5;
  // const float eta_gap = 0.5;
  const int mult_cut = 1;
  const double harmonic = 1.;
  const double k = 2.;
  bool multcut;
  bool firstrun = 0;
  const double res1FHCalHalf[ncent] = {0.109364, 0.274315, 0.428357, 0.517762, 0.532985, 0.505748, 0.443084, 0.351471, 0.2523}; // res2psi1 FHCal
  const double res1FHCalFull[ncent] = {0.20308, 0.453266, 0.631984, 0.714464, 0.727125, 0.704201, 0.64657, 0.548948, 0.423564}; // res2psi1 FHCal

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
  // TProfile *prFHCalLTPC = new TProfile("prFHCalLTPC","",ncent,&bin_cent[0]);
  // TProfile *prFHCalRTPC = new TProfile("prFHCalRTPC","",ncent,&bin_cent[0]);
  TProfile *prFHCalLR = new TProfile("prFHCalLR","",ncent,&bin_cent[0]);
  // configuration 2
  // TProfile *prFHCalTPCL = new TProfile("prFHCalTPCL","",ncent,&bin_cent[0]);
  // TProfile *prFHCalTPCR = new TProfile("prFHCalTPCR","",ncent,&bin_cent[0]);
  // TProfile *prTPCLR = new TProfile("prTPCLR","",ncent,&bin_cent[0]);
  // QVector *Q2_TPC_L = new QVector(harmonic);
  // QVector *Q2_TPC_R = new QVector(harmonic);
  QVector *Q2_FHCal_L = new QVector(harmonic);
  QVector *Q2_FHCal_R = new QVector(harmonic);

  TProfile *prV1_FHCalEP[ncent];
  TProfile *prV1_FHCalHalfEP_L[ncent];
  TProfile *prV1_FHCalHalfEP_R[ncent];
  for (int ic = 0; ic < ncent; ic++)
  {
    prV1_FHCalEP[ic] = new TProfile(Form("prV1_FHCalEP_%i",ic),"",npt,&pTBin[0]);
    prV1_FHCalHalfEP_L[ic] = new TProfile(Form("prV1_FHCalHalfEP_L_%i",ic),"",npt,&pTBin[0]);
    prV1_FHCalHalfEP_R[ic] = new TProfile(Form("prV1_FHCalHalfEP_R_%i",ic),"",npt,&pTBin[0]);
  }
  // Start event loop
  float PsiFHCal, PsiTPC_L, PsiTPC_R, PsiFHCal_L, PsiFHCal_R, PsiTPC;
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%100000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1) continue;
    int fcent = GetCentBin(cent);

    // Q2_TPC_L->Zero();
    // Q2_TPC_R->Zero();
    Q2_FHCal_L->Zero();
    Q2_FHCal_R->Zero();
    for (int iTrk=0; iTrk<nh; iTrk++)
    { // 1st track loop
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      float weight = pt;
      if (eta<-2. && eta>-5.) { if (harmonic==1) Q2_FHCal_L->CalQVector(phi,-weight); else { Q2_FHCal_L->CalQVector(phi,weight); } }
      if (eta> 2. && eta< 5.) Q2_FHCal_R->CalQVector(phi,weight);
      // if (pt < minptRF || pt > maxptRF || fabs(eta)>eta_cut) continue; // track selection
      // auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      // if (!particle) continue;
      // float charge = 1./3.*particle->Charge();
      // if (charge == 0) continue;
      // if (eta<-eta_gap) { if (harmonic==1) Q2_TPC_L->CalQVector(phi,-weight); else { Q2_TPC_L->CalQVector(phi,weight);} }
      // if (eta> eta_gap) Q2_TPC_R->CalQVector(phi,weight);

    } // end of 1st track loop
    // if (Q2_FHCal_L->GetMult() > mult_cut && Q2_FHCal_R->GetMult() > mult_cut && Q2_TPC_R->GetMult() > mult_cut && Q2_TPC_L->GetMult() > mult_cut)
    if (Q2_FHCal_L->GetMult() > mult_cut && Q2_FHCal_R->GetMult() > mult_cut)
    {
      multcut = false;
      Q2_FHCal_L->WeightQVector();
      Q2_FHCal_R->WeightQVector();
      // Q2_TPC_L->WeightQVector();
      // Q2_TPC_R->WeightQVector();
      // PsiTPC_L = TMath::ATan2(Q2_TPC_L->Y(),Q2_TPC_L->X()) / harmonic;
      // PsiTPC_R = TMath::ATan2(Q2_TPC_R->Y(),Q2_TPC_R->X()) / harmonic;
      // PsiTPC = TMath::ATan2(Q2_TPC_L->Y()+Q2_TPC_R->Y(),Q2_TPC_R->X()+Q2_TPC_L->X()) / harmonic;
      PsiFHCal_L = TMath::ATan2(Q2_FHCal_L->Y(),Q2_FHCal_L->X()) / harmonic;
      PsiFHCal_R = TMath::ATan2(Q2_FHCal_R->Y(),Q2_FHCal_R->X()) / harmonic;
      PsiFHCal = TMath::ATan2(Q2_FHCal_R->Y()+Q2_FHCal_L->Y(),Q2_FHCal_R->X()+Q2_FHCal_L->X()) / harmonic;

      if (firstrun)
      {
        // prFHCalLTPC->Fill(cent,TMath::Cos( harmonic * (PsiFHCal_L-PsiTPC) ));
        // prFHCalRTPC->Fill(cent,TMath::Cos( harmonic * (PsiFHCal_R-PsiTPC) ));
        prFHCalLR->Fill(cent,TMath::Cos( harmonic * (PsiFHCal_L-PsiFHCal_R) ));
        // configuration 2
        // prFHCalTPCL->Fill(cent,TMath::Cos( harmonic * k * (PsiFHCal-PsiTPC_L) ));
        // prFHCalTPCR->Fill(cent,TMath::Cos( harmonic * k * (PsiFHCal-PsiTPC_R) ));
        // prTPCLR->Fill(cent,TMath::Cos( harmonic * k * (PsiTPC_L-PsiTPC_R) ));      
      }    
    }
    else { multcut = true; }
    if (!multcut && !firstrun)
    {
      for (int iTrk=0; iTrk<nh; iTrk++)
      { // 1st track loop
        TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
        float pt  = vect.Pt();
        float eta = vect.Eta();
        float phi = vect.Phi();
        if (pt < minpt || pt > maxpt || fabs(eta)>eta_cut) continue; // track selection
        auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
        if (!particle) continue;
        float charge = 1./3.*particle->Charge();
        if (charge == 0) continue;
        prV1_FHCalEP[fcent]->Fill(pt,TMath::Cos(harmonic*k*(phi-PsiFHCal))/res1FHCalFull[fcent]);
        prV1_FHCalHalfEP_L[fcent]->Fill(pt,TMath::Cos(harmonic*k*(phi-PsiFHCal_L))/res1FHCalHalf[fcent]);
        prV1_FHCalHalfEP_R[fcent]->Fill(pt,TMath::Cos(harmonic*k*(phi-PsiFHCal_R))/res1FHCalHalf[fcent]);
      }
    }
  } // end event loop

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}




// root -l -b -q UrQMD.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'