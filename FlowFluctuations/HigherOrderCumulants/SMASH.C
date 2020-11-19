// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include <TVector3.h>

#define MAX_TRACKS 10000

#include "/weekly/lbavinh/lbavinh/FlowFluctuations/utilities.C"

// Use or not the non-unit particle weights above:
bool bUseWeights = false;
// Cross-check with nested loops:
// In this code only available for 2-nd order correlator due to calculation power
bool bEvaluateRecursion = true;
// bool bEvaluateStandaloneFormulas = false;
// Pick up randomly some harmonics:
const int h1=2, h2=-2, h3=2, h4=-2, h5=2, h6=-2, h7=2, h8=-2;
// Book Q-vector components: 
const int sum = (h1<0?-1*h1:h1)+(h2<0?-1*h2:h2)+(h3<0?-1*h3:h3)+(h4<0?-1*h4:h4) 
                + (h5<0?-1*h5:h5)+(h6<0?-1*h6:h6)+(h7<0?-1*h7:h7)+(h8<0?-1*h8:h8);
const int maxCorrelator = 8; // We will not go beyond 8-p correlations
const int maxHarmonic = sum+1;
const int maxPower = maxCorrelator+1;
TComplex Qvector[maxHarmonic][maxPower]; // All needed Q-vector components
TComplex Q(Int_t n, Int_t p);
TComplex Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0) 
{
 // Calculate multi-particle correlators by using recursion (an improved faster version) originally developed by 
 // Kristjan Gulbrandsen (gulbrand@nbi.dk). 

  Int_t nm1 = n-1;
  TComplex c(Q(harmonic[nm1], mult));
  if (nm1 == 0) return c;
  c *= Recursion(nm1, harmonic);
  if (nm1 == skip) return c;

  Int_t multp1 = mult+1;
  Int_t nm2 = n-2;
  Int_t counter1 = 0;
  Int_t hhold = harmonic[counter1];
  harmonic[counter1] = harmonic[nm2];
  harmonic[nm2] = hhold + harmonic[nm1];
  TComplex c2(Recursion(nm1, harmonic, multp1, nm2));
  Int_t counter2 = n-3;
  while (counter2 >= skip) {
    harmonic[nm2] = harmonic[counter1];
    harmonic[counter1] = hhold;
    ++counter1;
    hhold = harmonic[counter1];
    harmonic[counter1] = harmonic[nm2];
    harmonic[nm2] = hhold + harmonic[nm1];
    c2 += Recursion(nm1, harmonic, multp1, counter2);
    --counter2;
  }
  harmonic[nm2] = harmonic[counter1];
  harmonic[counter1] = hhold;

  if (mult == 1) return c-c2;
  return c-Double_t(mult)*c2;

} // TComplex AliFlowAnalysisWithMultiparticleCorrelations::Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0)

void SMASH(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration

  // Profile info - general
  const int NcentBins     = 9;
  const double binCent[NcentBins]={2.5,7.5,15,25,35,45,55,65,75};

  // Track cuts - general
  const float pt_min_cut = 0.2;
  const float pt_max_cut = 3.;
  const float eta_cut    = 1.5;
  // const float eta_gap    = 0.05;

  // Configure input information
  TChain *chain = new TChain("particles");
  std::ifstream file(inputFileName.Data());
  std::string line;
  while(std::getline(file, line))
  {
    chain->Add(line.c_str());
  }

  Int_t           nh;
  Double_t        bimp;
  Bool_t          empty_event;
  Int_t           ev;
  Int_t           tcounter;
  Int_t           pdg[MAX_TRACKS];   //[npart]
  Int_t           charge[MAX_TRACKS];   //[npart]
  Double_t        p0[MAX_TRACKS];   //[npart]
  Double_t        momx[MAX_TRACKS];   //[npart]
  Double_t        momy[MAX_TRACKS];   //[npart]
  Double_t        momz[MAX_TRACKS];   //[npart]
  Double_t        t[MAX_TRACKS];   //[npart]
  Double_t        x[MAX_TRACKS];   //[npart]
  Double_t        y[MAX_TRACKS];   //[npart]
  Double_t        z[MAX_TRACKS];   //[npart]

  // List of branches
  TBranch        *b_npart;   //!
  TBranch        *b_impact_b;   //!
  TBranch        *b_empty_event;   //!
  TBranch        *b_ev;   //!
  TBranch        *b_tcounter;   //!
  TBranch        *b_pdgcode;   //!
  TBranch        *b_charge;   //!
  TBranch        *b_p0;   //!
  TBranch        *b_px;   //!
  TBranch        *b_py;   //!
  TBranch        *b_pz;   //!
  TBranch        *b_t;   //!
  TBranch        *b_x;   //!
  TBranch        *b_y;   //!
  TBranch        *b_z;   //!

  chain->SetBranchAddress("npart", &nh, &b_npart);
  chain->SetBranchAddress("impact_b", &bimp, &b_impact_b);
  chain->SetBranchAddress("empty_event", &empty_event, &b_empty_event);
  chain->SetBranchAddress("ev", &ev, &b_ev);
  chain->SetBranchAddress("tcounter", &tcounter, &b_tcounter);
  chain->SetBranchAddress("pdgcode", pdg, &b_pdgcode);
  chain->SetBranchAddress("charge", charge, &b_charge);
  chain->SetBranchAddress("p0", p0, &b_p0);
  chain->SetBranchAddress("px", momx, &b_px);
  chain->SetBranchAddress("py", momy, &b_py);
  chain->SetBranchAddress("pz", momz, &b_pz);
  chain->SetBranchAddress("t", t, &b_t);
  chain->SetBranchAddress("x", x, &b_x);
  chain->SetBranchAddress("y", y, &b_y);
  chain->SetBranchAddress("z", z, &b_z);

  // Configure output information
  TFile *fo = new TFile(outputFileName.Data(),"recreate");

  TH1I *hEvt  = new TH1I("hEvt","Event number",1,0,1);
  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 250, 0, MAX_TRACKS);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 5.);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr; #phi; dN/d#phi", 350, -3.5, 3.5);

  // ================================== Direct Cumulants ================================== //
  TProfile *recursion[maxCorrelator][NcentBins];    // Correlations calculated from Q-vector components using recursive algorithm 
  for(Int_t c=0;c<maxCorrelator;c++){
    for(Int_t icent=0;icent<NcentBins;icent++){
      recursion[c][icent] = new TProfile(Form("recursion_%i_%i",c,icent),Form("recursion_%i_%i",c,icent),1,0.,1.);
    }
  }
  TProfile *pCovariance[6][NcentBins];
  for (int i=0;i<6;i++){
    for (int c=0;c<NcentBins;c++){
      pCovariance[i][c] = new TProfile(Form("pCovariance_%i_%i",i,c),Form("pCovariance_%i_%i",i,c),1,0.,1.);
    }
  }

  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%100000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);
    hEvt->Fill(0);
    float cent = CentB(bimp);
    if (cent == -1) continue;
    int fCent = GetCentBin(cent);
    Int_t mc_num_particles = nh;
    hMult->Fill(mc_num_particles);
    hBimp->Fill(bimp);

    // a) Make sure all Q-vectors are initially zero:
    for(Int_t h=0;h<maxHarmonic;h++){
      for(Int_t p=0;p<maxPower;p++){
        Qvector[h][p] = TComplex(0.,0.);
      }
    }
    Int_t M = 0;
    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      TVector3 vect(momx[iTr], momy[iTr], momz[iTr]);
      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTr]);
      if (!particle) continue;
      float charge = 1./3.*particle->Charge();
      if (charge==0) continue;
      hPt->Fill(pt);
      hEta->Fill(eta);
      hPhi->Fill(phi);
      // b) Calculate Q-vectors for available angles and weights: 
      Double_t wPhi = 1.; // particle weight
      Double_t wPhiToPowerP = 1.;
      if(bUseWeights){wPhi = phi;} // need to be fixed, weight is not value of azimuthal itself
      for(Int_t h=0;h<maxHarmonic;h++){
        for(Int_t p=0;p<maxPower;p++){
          if(bUseWeights){wPhiToPowerP = pow(wPhi,p);}
          Qvector[h][p] += TComplex(wPhiToPowerP*TMath::Cos(h*phi),wPhiToPowerP*TMath::Sin(h*phi));
        } //  for(Int_t p=0;p<maxPower;p++)
      } // for(Int_t h=0;h<maxHarmonic;h++)
      M++;
    } // end of mc track loop
    if (M>=8){
      if (bEvaluateRecursion){
      // e) Calculate n-particle correlations from Q-vectors (using recursion):
      Int_t harmonics_Two_Num[2] = {h1,h2};       
      Int_t harmonics_Two_Den[2] = {0,0};       
      TComplex twoRecursion = Recursion(2,harmonics_Two_Num)/Recursion(2,harmonics_Two_Den).Re();
      Double_t wTwoRecursion = Recursion(2,harmonics_Two_Den).Re();
      recursion[0][fCent]->Fill(0.5,twoRecursion.Re(),wTwoRecursion); // <<cos(h1*phi1+h2*phi2)>>

      Int_t harmonics_Four_Num[4] = {h1,h2,h3,h4};       
      Int_t harmonics_Four_Den[4] = {0,0,0,0};       
      TComplex fourRecursion = Recursion(4,harmonics_Four_Num)/Recursion(4,harmonics_Four_Den).Re();
      Double_t wFourRecursion = Recursion(4,harmonics_Four_Den).Re();
      recursion[2][fCent]->Fill(0.5,fourRecursion.Re(),wFourRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>

      Int_t harmonics_Six_Num[6] = {h1,h2,h3,h4,h5,h6};       
      Int_t harmonics_Six_Den[6] = {0,0,0,0,0,0};       
      TComplex sixRecursion = Recursion(6,harmonics_Six_Num)/Recursion(6,harmonics_Six_Den).Re();
      Double_t wSixRecursion = Recursion(6,harmonics_Six_Den).Re();
      recursion[4][fCent]->Fill(0.5,sixRecursion.Re(),wSixRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
    
      Int_t harmonics_Eight_Num[8] = {h1,h2,h3,h4,h5,h6,h7,h8};       
      Int_t harmonics_Eight_Den[8] = {0,0,0,0,0,0,0,0};       
      TComplex eightRecursion = Recursion(8,harmonics_Eight_Num)/Recursion(8,harmonics_Eight_Den).Re();
      Double_t wEightRecursion = Recursion(8,harmonics_Eight_Den).Re();
      recursion[6][fCent]->Fill(0.5,eightRecursion.Re(),wEightRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>

      pCovariance[0][fCent]->Fill(0.5,twoRecursion.Re()*fourRecursion.Re(),wTwoRecursion*wFourRecursion);
      pCovariance[1][fCent]->Fill(0.5,twoRecursion.Re()*sixRecursion.Re(),wTwoRecursion*wSixRecursion);
      pCovariance[2][fCent]->Fill(0.5,twoRecursion.Re()*eightRecursion.Re(),wTwoRecursion*wEightRecursion);
      pCovariance[3][fCent]->Fill(0.5,fourRecursion.Re()*sixRecursion.Re(),wFourRecursion*wSixRecursion);
      pCovariance[4][fCent]->Fill(0.5,fourRecursion.Re()*eightRecursion.Re(),wFourRecursion*wEightRecursion);
      pCovariance[5][fCent]->Fill(0.5,sixRecursion.Re()*eightRecursion.Re(),wSixRecursion*wEightRecursion);
      }
    }
  } // end of event loop

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}

TComplex Q(Int_t n, Int_t p)
{
 // Using the fact that Q{-n,p} = Q{n,p}^*. 
 
 if(n>=0){return Qvector[n][p];} 
 return TComplex::Conjugate(Qvector[-n][p]);
 
} // TComplex Q(Int_t n, Int_t p)

// root -l -b -q UrQMD.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'
