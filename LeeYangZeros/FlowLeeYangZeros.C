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

float CentB(float bimp);
int GetCentBin(float cent);
Double_t GetR0(TH1F *const &hist);

using std::cout;
using std::endl;

#define MAX_TRACKS 10000

void FlowLeeYangZeros(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration
  // const int npid = 8;  // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
  const int ncent = 9; // 0-80%
  // const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
  // const int npt = 16; // 0.5 - 3.6 GeV/c - number of pT bins
  // const double bin_pT[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
  const double maxpt = 3.; // max pt
  const double minpt = 0.2;  // min pt
  const double maxptRF = 3.;
  const double minptRF = 0.2;
  const float eta_cut = 1.5;
  const float eta_gap = 0.05;
  const int neta = 2; // [eta-,eta+]

  // Configure input information
  TChain *chain = new TChain("mctree");

  std::ifstream file(inputFileName.Data());
  std::string line;
  while (std::getline(file, line))
  {
    chain->Add(line.c_str());
  }

  Float_t bimp;
  Float_t phi2;
  Float_t phi3;
  Float_t ecc2;
  Float_t ecc3;
  Int_t npart;
  Int_t nh;
  Float_t momx[MAX_TRACKS];   //[nh]
  Float_t momy[MAX_TRACKS];   //[nh]
  Float_t momz[MAX_TRACKS];   //[nh]
  Float_t ene[MAX_TRACKS];    //[nh]
  Int_t hid[MAX_TRACKS];      //[nh]
  Int_t pdg[MAX_TRACKS];      //[nh]
  Short_t charge[MAX_TRACKS]; //[nh]

  // List of branches
  TBranch *b_bimp;   //!
  TBranch *b_phi2;   //!
  TBranch *b_phi3;   //!
  TBranch *b_ecc2;   //!
  TBranch *b_ecc3;   //!
  TBranch *b_npart;  //!
  TBranch *b_nh;     //!
  TBranch *b_momx;   //!
  TBranch *b_momy;   //!
  TBranch *b_momz;   //!
  TBranch *b_ene;    //!
  TBranch *b_hid;    //!
  TBranch *b_pdg;    //!
  TBranch *b_charge; //!

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
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  TH1I *hEvt = new TH1I("hEvt", "Event number", 1, 0, 1);
  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 300, 0, MAX_TRACKS);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 350, -3.5, 3.5);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);
  TH1F *hQtheta = new TH1F("hQtheta", "", 300, -20, 20);
  TProfile *pQtheta = new TProfile("pQtheta", "", 1, 0, 1);
  // Flow Analysis with Lee Yang Zeros Method
  const int rbins = 500;
  const int thetabins = 5;
  const float rootJ0 = 2.4048256;
  const int rmult = 290;
  float theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; ++thetabin)
  {
    // float theta_width = TMath::Pi() / (2.0 * thetabins);
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
    // cout << theta[thetabin] << endl;
  }
  Double_t r[rbins];
  for (int rbin = 0; rbin < rbins; ++rbin)
  {
    r[rbin] = (double(rbin) / rbins);
    // r[rbin] = rootJ0/((0.15-0.001*rbin)*rmult);
  }

  // TComplex Qtheta[thetabins];
  float Qtheta[thetabins];
  TComplex genfunS[rbins][thetabins]; // sum
  TComplex genfunP[rbins][thetabins]; // product
  TComplex cExpo;
  // const int multbins = 10; // we'll do just a few for now, may do more later
  TProfile *prReGthetaSum[ncent][thetabins];
  TProfile *prImGthetaSum[ncent][thetabins];
  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];



  TH1F *hGthetaSum[ncent][thetabins];
  TH1F *hGthetaProduct[ncent][thetabins];
  TProfile *prRefMult = new TProfile("prRefMult","",ncent,0,ncent);
  TProfile *prQ2x = new TProfile("prQ2x","",ncent,0,ncent);
  TProfile *prQ2y = new TProfile("prQ2y","",ncent,0,ncent);
  TProfile *prQ2ModSq = new TProfile("prQ2ModSq","",ncent,0,ncent);

  for (int i = 0; i < ncent; ++i)
  {
    for (int j = 0; j < thetabins; ++j)
    {
      prReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, 0, 1);
      prImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, 0, 1);
      prReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, 0, 1);
      prImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, 0, 1);



      hGthetaSum[i][j] = new TH1F(Form("hGthetaSum_mult%d_theta%d", i, j), "", rbins, 0, 1);
      hGthetaProduct[i][j] = new TH1F(Form("hGthetaProduct_mult%d_theta%d", i, j), "", rbins, 0, 1);
    }
  }

  float Q2x, Q2y;
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    if (iEv == 20000) break;
    chain->GetEntry(iEv);
    hEvt->Fill(0);

    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1)
    // if (cent != 25.)
      continue;
    int mult = 0;
    int fcent = GetCentBin(cent);

    hBimp->Fill(bimp);
    for (int i = 0; i < thetabins; ++i)
    {
      // Qtheta[i] = TComplex(0.0, 0.0);
      Qtheta[i] = 0.;
    }
    for (int i = 0; i < rbins; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        genfunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
        genfunP[i][j] = TComplex(1.0, 0.0); // initialize to 1, calcualte via product
        // genfunP[i][j] = TComplex::One(); // initialize to 1, calcualte via product
      }
    }
    Q2x = 0.;
    Q2y = 0.;

    for (int iTrk = 0; iTrk < nh; iTrk++)
    {
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      float pt = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
        continue; // track selection
      // if (fabs(eta)<eta_gap) continue;
      auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      if (!particle)
        continue;
      float charge = 1. / 3. * particle->Charge();
      if (charge == 0)
        continue;

      hPt->Fill(pt);
      hEta->Fill(eta);
      hPhi->Fill(phi);
      // Int_t ipt = -1;
      // for (int j = 0; j < npt; j++)
      // {
      //   if (pt >= bin_pT[j] && pt < bin_pT[j + 1])
      //     ipt = j;
      // }

      // int fId = -1;
      // if (pdg[iTrk] == 211)
      //   fId = 1; // pion+
      // if (pdg[iTrk] == 321)
      //   fId = 2; // kaon+
      // if (pdg[iTrk] == 2212)
      //   fId = 3; // proton
      // if (pdg[iTrk] == -211)
      //   fId = 5; // pion-
      // if (pdg[iTrk] == -321)
      //   fId = 6; // kaon-
      // if (pdg[iTrk] == -2212)
      //   fId = 7; // anti-proton
      Q2x += TMath::Cos(2.0 * phi);
      Q2y += TMath::Sin(2.0 * phi);

      // ---------------------------------------------
      // --- calculate the product generating function
      // ---
      for (int rbin = 0; rbin < rbins; ++rbin)
      {
        for (int thetabin = 0; thetabin < thetabins; ++thetabin)
        {
          genfunP[rbin][thetabin] *= TComplex(1.0, r[rbin] * TMath::Cos(2. * (phi - theta[thetabin])));
        }
      }
      mult++;
    } // end of track loop
    // if (iEv % 10000 == 0) for (int thetabin = 0; thetabin < thetabins; ++thetabin) cout << genfunP[0][thetabin].Rho2() << endl;
    hMult->Fill(mult);
    prRefMult->Fill(fcent, mult);
    prQ2x->Fill(fcent, Q2x);
    prQ2y->Fill(fcent, Q2y);
    TComplex Q2(Q2x, Q2y);
    prQ2ModSq->Fill(fcent, Q2.Rho2());


    // -------------------------------------------
    // --- fill the generating function histograms
    // ---
    // Q2x /= mult;
    // Q2y /= mult;
    for (int thetabin = 0; thetabin < thetabins; ++thetabin)
    {

      Qtheta[thetabin] = Q2x * TMath::Cos(2.0 * theta[thetabin]) + Q2y * TMath::Sin(2.0 * theta[thetabin]);
      hQtheta->Fill(Qtheta[thetabin]);
      pQtheta->Fill(0.5,Qtheta[thetabin]);
    }

    for (int rbin = 0; rbin < rbins; ++rbin)
    {
      for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      {
        cExpo = TComplex(0., r[rbin] * Qtheta[thetabin]);
        genfunS[rbin][thetabin] = TComplex::Exp(cExpo); // generating function from Q-vectors
        prReGthetaSum[fcent][thetabin]->Fill(r[rbin], genfunS[rbin][thetabin].Re());
        prImGthetaSum[fcent][thetabin]->Fill(r[rbin], genfunS[rbin][thetabin].Im());
        // if (genfunP[rbin][thetabin].Rho2() > 100.) continue;
        prReGthetaProduct[fcent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Re());
        prImGthetaProduct[fcent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Im());
      }
    }

  } // end event loop
  for (int icent = 0; icent < ncent; icent++)
  {
    for (int thetabin = 0; thetabin < thetabins; thetabin++)
    {  
      for (int rbin = 0; rbin < rbins; rbin++)
      {
        // get bincentre of bins in histogram
        Double_t dRe = prReGthetaSum[icent][thetabin]->GetBinContent(rbin+1);
        Double_t dIm = prImGthetaSum[icent][thetabin]->GetBinContent(rbin+1);
        TComplex cGtheta(dRe,dIm);
        //fill fHistGtheta with the modulus squared of cGtheta
        //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
        hGthetaSum[icent][thetabin]->SetBinContent(rbin+1,cGtheta.Rho2());
        // if (icent == 3 && thetabin == 0) cout << cGtheta.Rho2() << " ";
        hGthetaSum[icent][thetabin]->SetBinError(rbin+1,0.0);
      }
    }
  }
  cout << endl;

    for (int icent = 0; icent < ncent; icent++)
    {
      for (int thetabin = 0; thetabin < thetabins; thetabin++)
      {  
        for (int rbin = 0; rbin < rbins; rbin++)
        {
          // get bincentre of bins in histogram
          Double_t dRe = prReGthetaProduct[icent][thetabin]->GetBinContent(rbin+1);
          Double_t dIm = prImGthetaProduct[icent][thetabin]->GetBinContent(rbin+1);
          TComplex cGtheta(dRe,dIm);
          //fill fHistGtheta with the modulus squared of cGtheta
          //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
          hGthetaProduct[icent][thetabin]->SetBinContent(rbin+1,cGtheta.Rho2());
          // if (icent == 3 && thetabin == 0) cout << cGtheta.Rho2() << " ";
          hGthetaProduct[icent][thetabin]->SetBinError(rbin+1,0.0);
        }
      }
    }
    cout << endl;

  float v2int[ncent];
  cout << "My flow" << endl;
  for (int ic = 0; ic < ncent; ic++){
    for (int it = 0; it < thetabins; it++)
    {
      float r0theta = GetR0(hGthetaProduct[ic][it]);
      if (ic == 3 && it == 0) cout << "r0theta = " << r0theta << endl;
      float refmult = prRefMult->GetBinContent(ic+1);
      v2int[ic] = rootJ0 / r0theta / refmult;
    }
    v2int[ic] /= (float)thetabins;
    cout << v2int[ic] << " ";
  }
  cout << endl;

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if (bimp < 2.91)
    fcent = 2.5; // 0-5%
  else if (bimp < 4.18)
    fcent = 7.5; // 5-10%
  else if (bimp < 6.01)
    fcent = 15.; // 10-20%
  else if (bimp < 7.37)
    fcent = 25.; // 20-30%
  else if (bimp < 8.52)
    fcent = 35.; // 30-40%
  else if (bimp < 9.57)
    fcent = 45.; // 40-50%
  else if (bimp < 10.55)
    fcent = 55.; // 50-60%
  else if (bimp < 11.46)
    fcent = 65.; // 60-70%
  else if (bimp < 12.31)
    fcent = 75.; // 70-80%
  else
    fcent = -1;
  return fcent;
}

int GetCentBin(float cent)
{
  if (cent == -1)
    return -1;
  if (cent == 2.5)
    return 0;
  if (cent == 7.5)
    return 1;
  if (cent == 15.)
    return 2;
  if (cent == 25.)
    return 3;
  if (cent == 35.)
    return 4;
  if (cent == 45.)
    return 5;
  if (cent == 55.)
    return 6;
  if (cent == 65.)
    return 7;
  if (cent == 75.)
    return 8;
  return -1;
}

Double_t GetR0(TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of Gtheta 

  Int_t iNbins = hist->GetNbinsX();
  Double_t dR0 = 0.; 

  for (Int_t b=2;b<iNbins;b++)
  {
    Double_t dG0 = hist->GetBinContent(b);
    Double_t dGnext = hist->GetBinContent(b+1);
    Double_t dGnextnext = hist->GetBinContent(b+2);
    
    if (dGnext > dG0 && dGnextnext > dG0)
    {
      Double_t dGlast = hist->GetBinContent(b-1);
      Double_t dXlast = hist->GetBinCenter(b-1);
      Double_t dX0 = hist->GetBinCenter(b);
      Double_t dXnext = hist->GetBinCenter(b+1);

      dR0 = dX0 - ((dX0-dXlast)*(dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dX0-dXnext)*(dG0-dGlast))/
        (2.*((dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dG0-dGlast))); //parabolic interpolated minimum
      
      break; //stop loop if minimum is found
    } //if

  }//b

      
  return dR0;
}

// root -l -b -q FlowLeeYangZeros.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'