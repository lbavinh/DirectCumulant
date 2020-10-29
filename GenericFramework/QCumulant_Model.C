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


float CentB(float bimp);
int GetCentBin(float cent);


// Use or not the non-unit particle weights above:
bool bUseWeights = false;
// Cross-check with nested loops:
// In this code only available for 2-nd order correlator due to calculation power
bool bEvaluateNestedLoops = false;
bool bEvaluateRecursion = true;
bool bEvaluateStandaloneFormulas = false;
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
TComplex Two(Int_t n1, Int_t n2);
TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4);
TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6);
// TComplex Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0);
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

void QCumulant_Model(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

  // Constant declaration

  // Profile info - general
  const int NcentBins     = 8;
  const double centBinMin = 0.;
  const double centBinMax = 80.;
  const int NptBins       = 300;
  const double ptBinMin   = 0.;
  const double ptBinMax   = 3.;
  const double binCent[NcentBins]={5,15,25,35,45,55,65,75};

  // Track cuts - general
  const float pt_min_cut = 0.2;
  const float pt_max_cut = 3.;
  const float eta_cut    = 1.5;
  // const float eta_gap    = 0.05;

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

  // TProfile2D *pCorrelationRF[maxCorrelator];
  // for (int icor=0;icor<maxCorrelator;icor++)
  // {
  //   pCorrelationRF[icor] = new TProfile2D(Form("pCorrelationRF_%i",icor),Form("pCorrelationRF_%i",icor), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  // }
  // TProfile2D *pCorrelationPOI[Npid];
  // for (int i=0; i < Npid; i++)
  // {
  //   pCorrelationPOI[i] = new TProfile2D(Form("pV2QC_pid%i", i), Form("v2(TPC EP) MODEL of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  // }
  
  TH1I *hEvt  = new TH1I("hEvt","Event number",1,0,1);
  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 250, 0, MAX_TRACKS);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 5.);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr; #phi; dN/d#phi", 350, -3.5, 3.5);

  // ================================== Direct Cumulants ================================== //
  TProfile *correlations[maxCorrelator][NcentBins]; // Correlations calculated from Q-vector componets using standalone formulas
  TProfile *recursion[maxCorrelator][NcentBins];    // Correlations calculated from Q-vector components using recursive algorithm 
  TProfile *nestedLoops[maxCorrelator][NcentBins];  // Correlations calculated from nested loops
  for(Int_t c=0;c<maxCorrelator;c++){
    for(Int_t icent=0;icent<NcentBins;icent++){
      correlations[c][icent] = new TProfile(Form("correlations_%i_%i",c,icent),Form("correlations_%i_%i",c,icent),1,0.,1.);
      recursion[c][icent] = new TProfile(Form("recursion_%i_%i",c,icent),Form("recursion_%i_%i",c,icent),1,0.,1.);
      nestedLoops[c][icent] = new TProfile(Form("nestedLoops_%i_%i",c,icent),Form("nestedLoops_%i_%i",c,icent),1,0.,1.);
    }
  }
  TProfile *pCovariance[6][NcentBins];
  for (int i=0;i<6;i++){
    for (int c=0;c<NcentBins;c++){
      pCovariance[i][c] = new TProfile(Form("pCovariance_%i_%i",i,c),Form("pCovariance_%i_%i",i,c),1,0.,1.);
    }
  }
  TProfile *pV2QC[4];
  for (int i=0;i<4;i++){
    pV2QC[i] = new TProfile(Form("pV2QC_%i",i),Form("pV2QC_%i",i),NcentBins,centBinMin,centBinMax);
  }  
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%10000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
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
      if (!bEvaluateNestedLoops) continue;
      for(int iTr2=0;iTr2<mc_num_particles;iTr2++){
        if(iTr2==iTr) continue; // Get rid of autocorrelations
        TVector3 vect2(momx[iTr2], momy[iTr2], momz[iTr2]);
        float pt2  = vect2.Pt();
        float eta2 = vect2.Eta();
        float phi2 = vect2.Phi();
        if (pt2 < pt_min_cut) continue;
        if (pt2 > pt_max_cut) continue;
        if (abs(eta2) > eta_cut) continue;
        auto particle2 = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTr2]);
        if (!particle2) continue;
        float charge2 = 1./3.*particle2->Charge();
        if (charge2==0) continue;
        Double_t wPhi2 = 1.; // particle weight
        if(bUseWeights){wPhi2 = phi2;} // need to be fixed, weight is not value of azimuthal itself
        nestedLoops[0][fCent]->Fill(0.5,TMath::Cos(h1*phi+h2*phi2),wPhi*wPhi2);
      }
    } // end of mc track loop
    if (M>=8){
      if (bEvaluateStandaloneFormulas){
      // d) Calculate n-particle correlations from Q-vectors (using standalone formulas):
      TComplex two = Two(h1,h2)/Two(0,0).Re();
      Double_t wTwo = Two(0,0).Re(); // Weight is 'number of combinations' by default
      correlations[0][fCent]->Fill(0.5,two.Re(),wTwo); // <<cos(h1*phi1+h2*phi2)>>

      TComplex four = Four(h1,h2,h3,h4)/Four(0,0,0,0).Re();
      Double_t wFour = Four(0,0,0,0).Re(); // Weight is 'number of combinations' by default
      correlations[2][fCent]->Fill(0.5,four.Re(),wFour); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>

      TComplex six = Six(h1,h2,h3,h4,h5,h6)/Six(0,0,0,0,0,0).Re();
      Double_t wSix = Six(0,0,0,0,0,0).Re(); // Weight is 'number of combinations' by default
      correlations[4][fCent]->Fill(0.5,six.Re(),wSix); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
      }
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
      correlations[6][fCent]->Fill(0.5,eightRecursion.Re(),wEightRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>
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

  // for (int icent=0;icent<NcentBins;icent++){
  //   // 2QC
  //   term cor2 = term(recursion[0][icent]);
  //   double V22  = sqrt(cor2.mVal);
  //   // std::cout << V22 << " ";
  //   double eV22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
  //   // 4QC
  //   term cor4 = term(recursion[2][icent]);
  //   double cov24 = Covariance(pCovariance[0][icent],recursion[0][icent],recursion[2][icent]);
  //   double V24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
  //   double eV24= sqrt( 1./pow(V24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) ;
  //   // 6QC
  //   term cor6 = term(recursion[4][icent]);
  //   double cov26 = Covariance(pCovariance[1][icent],recursion[0][icent],recursion[4][icent]);
  //   double cov46 = Covariance(pCovariance[3][icent],recursion[2][icent],recursion[4][icent]);
  //   double V26 = pow(2,-1./3.)*pow(cor6.mVal-9*cor2.mVal*cor4.mVal+12*pow(cor2.mVal,3),1./6.);
  //   double eV26 = sqrt(1./(2*pow(2,4)*pow(V26,10))*(9./2.*pow(4*pow(cor2.mVal,2)-cor4.mVal,2)*cor2.mMSE
  //                    + 9./2.*pow(cor2.mVal,2)*cor4.mMSE+1./18.*cor6.mMSE
  //                    - 9*cor2.mVal*(4*pow(cor2.mVal,2)-cor4.mVal)*cov24
  //                    +(4*pow(cor2.mVal,2)-cor4.mVal)*cov26
  //                    - cor2.mVal*cov46));
  //   // 8QC
  //   term cor8 = term(recursion[6][icent]);
  //   double cov28 = Covariance(pCovariance[2][icent],recursion[0][icent],recursion[6][icent]);
  //   double cov48 = Covariance(pCovariance[4][icent],recursion[2][icent],recursion[6][icent]);
  //   double cov68 = Covariance(pCovariance[5][icent],recursion[4][icent],recursion[6][icent]);
  //   double V28 = pow(33,-1./8.)*pow(-cor8.mVal+16*cor6.mVal*cor2.mVal+18*pow(cor4.mVal,2)-144*cor4.mVal*pow(cor2.mVal,2)+144*pow(cor2.mVal,4),1./8.);
  //   double eV28 = sqrt(4.*pow(33,-2)/pow(V28,14)
  //               *(pow(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal,2)*cor2.mMSE
  //               + 81./16.*pow(4*pow(cor2.mVal,2)-cor4.mVal,2)*cor4.mMSE
  //               + pow(cor2.mVal,2)*cor6.mMSE+1./256.*cor8.mMSE
  //               - 9./2.*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)*(4*pow(cor2.mVal,2)-cor4.mVal)
  //               * cov24
  //               + 2*cor2.mVal*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)
  //               * cov26
  //               - 1./8.*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)*cov28
  //               - 9./2.*cor2.mVal*(4*pow(cor2.mVal,2)-cor4.mVal)*cov46
  //               + 9./32.*(4*pow(cor2.mVal,2)-cor4.mVal)*cov48
  //               - 1./8.*cor2.mVal*cov68));

  //   pV2QC[0]->SetBinContent(icent+1,V22);
  //   pV2QC[1]->SetBinContent(icent+1,V24);
  //   pV2QC[2]->SetBinContent(icent+1,V26);
  //   pV2QC[3]->SetBinContent(icent+1,V28);

  //   pV2QC[0]->SetBinError(icent+1,eV22);
  //   pV2QC[1]->SetBinError(icent+1,eV24);
  //   pV2QC[2]->SetBinError(icent+1,eV26);
  //   pV2QC[3]->SetBinError(icent+1,eV28);
  // }
  // std::cout << std::endl;

  // for (int icent=0;icent<NcentBins;icent++){
  //   printf("Centrality %i-%i%%\n\n",icent*10,(icent+1)*10);

  //   printf("Standalone formula <2>=%.12f\n",correlations[0][icent]->GetBinContent(1));
  //   printf("Recursion <2>=%.12f\n",recursion[0][icent]->GetBinContent(1));
  //   printf("Nested loops <2>=%.12f\n\n",nestedLoops[0][icent]->GetBinContent(1));

  //   printf("Standalone formula <4>=%.12f\n",correlations[2][icent]->GetBinContent(1));
  //   printf("Recursion <4>=%.12f\n\n",recursion[2][icent]->GetBinContent(1));

  //   printf("Standalone formula <6>=%.12f\n",correlations[4][icent]->GetBinContent(1));
  //   printf("Recursion          <6>=%.12f\n\n",recursion[4][icent]->GetBinContent(1));
    
  //   printf("Standalone formula <8>=%.12f\n",correlations[6][icent]->GetBinContent(1));
  //   printf("Recursion <8>=%.12f\n\n",recursion[6][icent]->GetBinContent(1));
  // }

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
  if (bimp < 4.18)
    fcent = 0; // 0-10%
  else if (bimp < 6.01)
    fcent = 10; //10-20%
  else if (bimp < 7.37)
    fcent = 20; //20-30%
  else if (bimp < 8.52)
    fcent = 30; //30-40%
  else if (bimp < 9.57)
    fcent = 40; //40-50%
  else if (bimp < 10.55)
    fcent = 50; //50-60%
  else if (bimp < 11.46)
    fcent = 60; //60-70%
  else if (bimp < 12.31)
    fcent = 70; //70-80%
  else
    fcent = -1;

  if (fcent != -1)
    return fcent + 5.;
  else
    return -1;
}

int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 5.) return 0;
  if (cent == 15.) return 1;
  if (cent == 25.) return 2;
  if (cent == 35.) return 3;
  if (cent == 45.) return 4;
  if (cent == 55.) return 5;
  if (cent == 65.) return 6;
  if (cent == 75.) return 7;
  return -1;
}

TComplex Q(Int_t n, Int_t p)
{
 // Using the fact that Q{-n,p} = Q{n,p}^*. 
 
 if(n>=0){return Qvector[n][p];} 
 return TComplex::Conjugate(Qvector[-n][p]);
 
} // TComplex Q(Int_t n, Int_t p)

TComplex Two(Int_t n1, Int_t n2)
{
 // Generic two-particle correlation <exp[i(n1*phi1+n2*phi2)]>.

 TComplex two = Q(n1,1)*Q(n2,1)-Q(n1+n2,2);

 return two;

} // TComplex Two(Int_t n1, Int_t n2)

TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4)
{
 // Generic four-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4)]>.

 TComplex four = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)-Q(n2,1)*Q(n1+n3,2)*Q(n4,1)
               - Q(n1,1)*Q(n2+n3,2)*Q(n4,1)+2.*Q(n1+n2+n3,3)*Q(n4,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)
               + Q(n2+n3,2)*Q(n1+n4,2)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)+Q(n1+n3,2)*Q(n2+n4,2)
               + 2.*Q(n3,1)*Q(n1+n2+n4,3)-Q(n1,1)*Q(n2,1)*Q(n3+n4,2)+Q(n1+n2,2)*Q(n3+n4,2)
               + 2.*Q(n2,1)*Q(n1+n3+n4,3)+2.*Q(n1,1)*Q(n2+n3+n4,3)-6.*Q(n1+n2+n3+n4,4);

 return four;

} // TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4)

TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6)
{
 // Generic six-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6)]>.

 TComplex six = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)
              - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)
              + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)
              + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)
              + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)
              - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)
              + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)
              - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)
              + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)
              + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6,1)
              - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)
              + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)
              - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6,1)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)
              - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)
              + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)
              + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6,1)
              + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6,1)
              + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6,1)
              - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)
              + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)
              + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6,1)
              + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6,1)
              + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6,1)
              - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)
              - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6,1)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6,1)
              - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6,1)+24.*Q(n1+n2+n3+n4+n5,5)*Q(n6,1)
              - Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)+Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)
              + Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)+Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)
              - 2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6,2)+Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)
              - Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6,2)+Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)
              - Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6,2)-2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6,2)
              + Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)-Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6,2)
              - 2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6,2)-2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6,2)
              + 6.*Q(n2+n3+n4+n5,4)*Q(n1+n6,2)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)
              + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)
              + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6,2)
              + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6,2)
              + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6,2)
              - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6,2)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)
              - Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6,2)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6,2)
              - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6,2)+6.*Q(n1+n3+n4+n5,4)*Q(n2+n6,2)
              + 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)-2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6,3)
              - 2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6,3)-2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6,3)
              + 4.*Q(n3+n4+n5,3)*Q(n1+n2+n6,3)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)
              + Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)+Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)
              + Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)-2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6,2)
              + Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)-Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6,2)
              + Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)-Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6,2)
              - 2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6,2)+Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)
              - Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6,2)-2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6,2)
              - 2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6,2)+6.*Q(n1+n2+n4+n5,4)*Q(n3+n6,2)
              + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6,3)
              - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6,3)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6,3)
              + 4.*Q(n2+n4+n5,3)*Q(n1+n3+n6,3)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)
              - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6,3)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6,3)
              - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6,3)+4.*Q(n1+n4+n5,3)*Q(n2+n3+n6,3)
              - 6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6,4)+6.*Q(n4+n5,2)*Q(n1+n2+n3+n6,4)
              - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)+Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)
              + Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)+Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)
              - 2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6,2)+Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)
              - Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6,2)+Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)
              - Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6,2)-2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6,2)
              + Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)-Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6,2)
              - 2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6,2)-2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6,2)
              + 6.*Q(n1+n2+n3+n5,4)*Q(n4+n6,2)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)
              - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6,3)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6,3)
              - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6,3)+4.*Q(n2+n3+n5,3)*Q(n1+n4+n6,3)
              + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6,3)
              - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6,3)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6,3)
              + 4.*Q(n1+n3+n5,3)*Q(n2+n4+n6,3)-6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6,4)
              + 6.*Q(n3+n5,2)*Q(n1+n2+n4+n6,4)+2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)
              - 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6,3)-2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6,3)
              - 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6,3)+4.*Q(n1+n2+n5,3)*Q(n3+n4+n6,3)
              - 6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6,4)+6.*Q(n2+n5,2)*Q(n1+n3+n4+n6,4)
              - 6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6,4)+6.*Q(n1+n5,2)*Q(n2+n3+n4+n6,4)
              + 24.*Q(n5,1)*Q(n1+n2+n3+n4+n6,5)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)
              + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)
              + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6,2)
              + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6,2)
              + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6,2)
              - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6,2)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)
              - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6,2)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6,2)
              - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6,2)+6.*Q(n1+n2+n3+n4,4)*Q(n5+n6,2)
              + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6,3)
              - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6,3)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6,3)
              + 4.*Q(n2+n3+n4,3)*Q(n1+n5+n6,3)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)
              - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6,3)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6,3)
              - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6,3)+4.*Q(n1+n3+n4,3)*Q(n2+n5+n6,3)
              - 6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6,4)+6.*Q(n3+n4,2)*Q(n1+n2+n5+n6,4)
              + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6,3)
              - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6,3)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6,3)
              + 4.*Q(n1+n2+n4,3)*Q(n3+n5+n6,3)-6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6,4)
              + 6.*Q(n2+n4,2)*Q(n1+n3+n5+n6,4)-6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6,4)
              + 6.*Q(n1+n4,2)*Q(n2+n3+n5+n6,4)+24.*Q(n4,1)*Q(n1+n2+n3+n5+n6,5)
              + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6,3)
              - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6,3)
              + 4.*Q(n1+n2+n3,3)*Q(n4+n5+n6,3)-6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6,4)
              + 6.*Q(n2+n3,2)*Q(n1+n4+n5+n6,4)-6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6,4)
              + 6.*Q(n1+n3,2)*Q(n2+n4+n5+n6,4)+24.*Q(n3,1)*Q(n1+n2+n4+n5+n6,5)
              - 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6,4)+6.*Q(n1+n2,2)*Q(n3+n4+n5+n6,4)
              + 24.*Q(n2,1)*Q(n1+n3+n4+n5+n6,5)+24.*Q(n1,1)*Q(n2+n3+n4+n5+n6,5)
              - 120.*Q(n1+n2+n3+n4+n5+n6,6);

 return six;

} // TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6)

// root -l -b -q QCumulant_Model.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/Urqmd7.7/runlist_Urqmd7.7_9063.list",test.root")'

