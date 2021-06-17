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

#define MAX_TRACKS 10000

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if      (bimp < 2.91)  fcent = 2.5; // 0-5%
  else if (bimp < 4.18)  fcent = 7.5; // 5-10%
  else if (bimp < 6.01)  fcent = 15.; // 10-20%
  else if (bimp < 7.37)  fcent = 25.; // 20-30%
  else if (bimp < 8.52)  fcent = 35.; // 30-40%
  else if (bimp < 9.57)  fcent = 45.; // 40-50%
  else if (bimp < 10.55) fcent = 55.; // 50-60%
  else if (bimp < 11.46) fcent = 65.; // 60-70%
  else if (bimp < 12.31) fcent = 75.; // 70-80%
  else                   fcent = -1;
  return fcent;
}


int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 2.5) return 0;
  if (cent == 7.5) return 1;
  if (cent == 15.) return 2;
  if (cent == 25.) return 3;
  if (cent == 35.) return 4;
  if (cent == 45.) return 5;
  if (cent == 55.) return 6;
  if (cent == 65.) return 7;
  if (cent == 75.) return 8;
  return -1;
}

void McPicoReader(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration
  const int ncent = 9; // 0-80%
  // const int npid = 8; // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
  // const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  // const int npt = 16; // 0.5 - 3.6 GeV/c - number of pT bins
  // const double bin_pT[npt+1]={0.,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.2,3.6};
  // const double maxpt = 3.6; // max pt
  // const double minpt = 0.;  // min pt
  // const double maxptRF = 3.;
  // const double minptRF = 0.2;
  // const float eta_cut =  1.5;
  // const float eta_gap = 0.05;
  // const int neta = 2; // [eta-,eta+]

  // Configure input information
  TChain *chain = new TChain("mctree");
  if (inputFileName.Contains(".root"))
  {
    chain->Add(inputFileName);
  }
  else
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    while(std::getline(file, line))
    {
      chain->Add(line.c_str());
    }
  }
  if (!chain) { cout << "I'm really sorry, Master. I cannot find the root tree with data..." << endl; return; }
  
  Float_t         bimp;
  Float_t         phi2;
  Float_t         phi3;
  Float_t         ecc2;
  Float_t         ecc3;
  Int_t           npart;
  Int_t           nh;
  Float_t         momx[MAX_TRACKS];  //[nh]
  Float_t         momy[MAX_TRACKS];  //[nh]
  Float_t         momz[MAX_TRACKS];  //[nh]
  Float_t         ene[MAX_TRACKS];   //[nh]
  Int_t           hid[MAX_TRACKS];   //[nh]
  Int_t           pdg[MAX_TRACKS];   //[nh]
  Short_t         charge[MAX_TRACKS];//[nh]

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
  TH1I *hEvt  = new TH1I("hEvt","Event number",1,0,1);
  TH2F *hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", MAX_TRACKS, 0, MAX_TRACKS, 200, 0., 20.);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 350, -3.5, 3.5);
  TH1D *hEta[ncent];
  TH1I *hMult[ncent];
  for (Int_t i = 0; i < ncent; i++)
  {
    hEta[i] = new TH1D(Form("hEta_%i",i), "Pseudorapidity distr; #eta; dN/d#eta", 400, -10, 10);
    hMult[i] = new TH1I(Form("hMult_%i",i), "Multiplicity distr;M;dN/dM", 300, 0, MAX_TRACKS);
  }  

  // Start event loop
  int n_entries = chain->GetEntries();
  cout << "OK, Master, let's do some physics!" << endl;
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%10000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    hEvt -> Fill(0);

    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1) continue;
    int mult = 0;
    int icent = GetCentBin(cent);

    hBimp -> Fill(bimp);
    hBimpvsMult -> Fill(nh,bimp);
  
    for (int iTrk=0; iTrk<nh; iTrk++)
    {
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (charge == 0) continue;
      if (pt<0.2 || pt>3.0 || fabs(eta)>1.5) continue;
      hPt -> Fill(pt);
      hEta[icent] -> Fill(eta);
      hPhi -> Fill(phi);
      mult++;
    }
    if (mult==0) cout << "mult=0" << endl;
    else if (mult!=0) hMult[icent] -> Fill(mult);

  
  } // end event loop
  
  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}
// root -l -b -q McPicoReader.C+'("/scratch1/lbavinh/lbavinh/UrQMD/split/Urqmd11.5/runlist_00","UrQMD_11.5.root")'