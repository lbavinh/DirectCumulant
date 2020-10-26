#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>

#define MAX_TRACKS 10000


void get_flow_model(TString inputFileName, TString outputFileName)
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
  const int NQvBins       = 240;
  const double QvBinMin   = -1.2;
  const double QvBinMax   = 1.2;

  // Track cuts - general
  const float pt_min_cut = 0.2;
  const float pt_max_cut = 3.;
  const float eta_cut    = 1.5;
  const float eta_gap    = 0.05;
  const int   mult_EP_cut= 2;

  // Track cuts - mc tracks
  // const int motherId_cut = -1;

  // Track cuts - reco tracks
  // const int Nhits_cut    = 32;
  // const float dca_cut    = 0.5;

  // PID - general
  const std::vector<TString> pidNames = {"hadron_pos", "pion_pos", "kaon_pos", "proton_pos", "hadron_neg", "pion_neg", "kaon_neg", "proton_neg"};
  const std::vector<TString> pidFancyNames = {"h+", "#pi+", "K+", "p", "h-", "#pi-", "K-", "#bar{p}"};
  const int Npid = 8; //pidNames.size()

  // PID - mc/model tracks
  const std::vector<int> pdgCodes = {999, 211, 321, 2212, -999, -211, -321, -2212};

  // PID - reco tracks
  // const float PidProb_cut = 0.9;

  // const std::vector<float> vResTpc     = {6.27383, 8.52203, 7.73442, 5.99234, 4.13289, 2.57332, 1.55835, 1.06316}; // 7.7
  const std::vector<float> vResTpc     = {8.57096, 10.8675, 9.73692, 7.45796, 5.10023, 3.16144, 1.87627, 1.22423}; // 11.5
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

  TProfile *pResMcTPC = new TProfile("pResTPC","Resolution for TPC EP MODEL", NcentBins, centBinMin, centBinMax);
  TProfile2D *pv2mcTPC[Npid];
  for (int i=0; i < Npid; i++)
  {
    pv2mcTPC[i] = new TProfile2D(Form("pv2TPC_pid%i", i), Form("v2(TPC EP) MODEL of %s", pidNames.at(i).Data()), NptBins, ptBinMin, ptBinMax, NcentBins, centBinMin, centBinMax);
  }
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%10000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1) continue;

    Int_t mc_num_particles = nh;

    // Read MC tracks
    float Qx_L_mc = 0., Qy_L_mc = 0., W_L_mc = 0.;
    float Qx_R_mc = 0., Qy_R_mc = 0., W_R_mc = 0.;
    TComplex Qv2_L = 0., Qv2_R = 0.; // scalar product
    int   Mult_L_mc = 0, Mult_R_mc = 0;
    float PsiEP_L_mc = 0., PsiEP_R_mc = 0.;

    ////////////////////////////////////////////////////////////////////
    //
    // RESOLUTION CALCULATIONS
    //
    ////////////////////////////////////////////////////////////////////

    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      TVector3 vect(momx[iTr], momy[iTr], momz[iTr]);

      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();

      // Main track cuts
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      if (abs(eta) < eta_gap) continue;

      // TPC Left EP
      if (eta < 0)
      {
        Qx_L_mc += 1. * cos(2.* phi);
        Qy_L_mc += 1. * sin(2.* phi);
        // W_L_mc  += 1.;
        Mult_L_mc++;
      }

      // TPC Right EP
      if (eta > 0)
      {
        Qx_R_mc += 1. * cos(2.* phi);
        Qy_R_mc += 1. * sin(2.* phi);
        // W_R_mc  += 1.;
        Mult_R_mc++;
      }
    } // end of mc track loop

    if (Mult_L_mc > mult_EP_cut && Mult_R_mc > mult_EP_cut)
    {
      Qv2_L = TComplex(Qx_L_mc,Qy_L_mc);
      Qv2_R = TComplex(Qx_R_mc,Qy_R_mc);
      float res_mc   = (float) (Qv2_L*TComplex::Conjugate(Qv2_R)).Re();
      pResMcTPC->Fill(cent, res_mc);
    }
    else{ continue; } 

    ////////////////////////////////////////////////////////////////////
    //
    // FLOW CALCULATIONS
    //
    ////////////////////////////////////////////////////////////////////
    
    float res_v2TPC_mc = vResTpc.at(GetCentBin(cent));

    // Read MC tracks
    for (int iTr=0; iTr<mc_num_particles; iTr++)
    {
      TVector3 vect(momx[iTr], momy[iTr], momz[iTr]);

      float pt  = vect.Pt();
      float eta = vect.Eta();
      float phi = vect.Phi();

      // Main track cuts
      if (pt < pt_min_cut) continue;
      if (pt > pt_max_cut) continue;
      if (abs(eta) > eta_cut) continue;
      if (abs(eta) < eta_gap) continue;

      // PID-related cut
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTr]);
      if (!particle) continue;
      
      TComplex u2 = TComplex(cos(2.*phi),sin(2.*phi));

      float v2TPC = 0.;
      if (eta < 0)
      {
        v2TPC = (float) (u2*TComplex::Conjugate(Qv2_R)).Re();
      }
      if (eta > 0)
      {
        v2TPC = (float) (u2*TComplex::Conjugate(Qv2_L)).Re();
      }
      v2TPC /= res_v2TPC_mc;

      int pidID = -1;
      float charge = 1./3.*particle->Charge();

      for (int ipid=0; ipid < Npid; ipid++)
      {
        if (abs(pdgCodes.at(ipid)) == 999) continue;
        if (pdgCodes.at(ipid) == pdg[iTr]) pidID = ipid;
      }

      if (charge > 0)
        pv2mcTPC[0]->Fill(pt, cent, v2TPC);
      if (charge < 0)
        pv2mcTPC[4]->Fill(pt, cent, v2TPC);

      if (pidID == -1) continue;

      pv2mcTPC[pidID]->Fill(pt, cent, v2TPC);

    } // end mc tracks loop

  } // end event loop

  // Writing output
  fo->cd();
  // std::cout << "Integrated v2 =";
  // for (int i=0;i<8;i++){
  //   std::cout<< pTest->GetBinContent(1+i) <<" ";
  // }
  // std::cout<<std::endl;
  pResMcTPC->Write();

  for (int ipid=0; ipid < Npid; ipid++)
  {
    pv2mcTPC[ipid]->Write();
  }
  
  // hQx_L_mc->Write();
  // hQy_L_mc->Write();
  // hQx_R_mc->Write();
  // hQy_R_mc->Write();

  fo->Close();

  timer.Stop();
  timer.Print();
}

Int_t CentB(Float_t bimp)
{
	Int_t fcent;
	if     ( bimp<4.18 ) fcent = 0; // 0-10%
	else if( bimp<6.01 ) fcent = 1; // 10-20%
	else if( bimp<7.37 ) fcent = 2; // 20-30%
	else if( bimp<8.52 ) fcent = 3; // 30-40%
	else if( bimp<9.57)  fcent = 4; // 40-50%
	else if( bimp<10.55) fcent = 5; // 50-60%
	else if( bimp<11.46) fcent = 6; // 60-70%
	else if( bimp<12.31) fcent = 7; // 70-80%
	else                 fcent =-1;

	return fcent;
}

TComplex Qstar(TComplex Q){
  TComplex QStar   = TComplex::Conjugate(Q);
  return QStar;
}

Double_t CalCor22(TComplex Q2, Double_t M, Double_t w2){
  // single-event average 2-particle azimuthal correlation <2>

  Double_t Q2Square = Q2.Rho2();
  Double_t coor22   = Q2Square - M;                                          

  return coor22/w2;
}

Double_t CalCor24(TComplex Q2, TComplex Q4, Double_t M, Double_t w4){
  // single-event average 4-particle azimuthal correlation <4>

  TComplex Q2Star   = Qstar(Q2);
  TComplex Q4Star   = Qstar(Q4);
  
  Double_t Q2Square = Q2.Rho2();
  Double_t Q4Square = Q4.Rho2();
  Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

  Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2*ReQQQ
                      - 4*(M-2)*Q2Square + 2*M*(M-3));

  return coor24/w4;
}

Double_t CalRedCor22(TComplex Q2, TComplex p2, Double_t M, Double_t mp, 
                     Double_t mq, Double_t wred2){

  // Calculate the average reduced single-event 2-particle correlations                      
  TComplex Q2Star = TComplex::Conjugate(Q2);
  Double_t coor22 = (p2*Q2Star-mq).Re();

  return coor22/wred2;
}

Double_t CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                     TComplex q4, Double_t M, Double_t mp, Double_t mq, Double_t wred4){

  // Calculate the average reduced single-event 2-particle correlations                      
  TComplex Q2Star = TComplex::Conjugate(Q2);
  TComplex Q4Star = TComplex::Conjugate(Q4);
  TComplex q2Star = TComplex::Conjugate(q2);
  Double_t Q2Square = Q2.Rho2();
  TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
                - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
                - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
                + 2.0*mq*M-6.0*mq;
  Double_t coor24 = coorc.Re(); 
  return coor24/wred4;
}



// root -l -b -q get_flow_model.C+'("/weekly/lbavinh/lbavinh/ScalarProduct/split/UrQMD_7.7/runlist_UrQMD_7.7_9639.list","test.root")'