#include <iostream>
#include <fstream>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>

#define MAX_TRACKS 10000

#include "/weekly/povarov/lbavinh/FlowFluctuations/Utils.C"

// R__LOAD_LIBRARY(libPicoDst.so)
const std::vector<float> vResTpc     = {0.213283, 0.355882, 0.433301, 0.46899, 0.476427, 0.466547, 0.446308, 0.41826, 0.384213, 0.347087, 0.311748, 0.285125, 0.265693, 0.258114, 0.2607, 0.272007, 0.287717, 0.310834, 0.340145, 0.377696};

void UrQMD(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

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

  TH2F *hQx_L_mc = new TH2F("hQx_L","Qx from Left TPC MODEL",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_L_mc = new TH2F("hQy_L","Qy from Left TPC MODEL",  NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQx_R_mc = new TH2F("hQx_R","Qx from Right TPC MODEL", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);
  TH2F *hQy_R_mc = new TH2F("hQy_R","Qy from Right TPC MODEL", NcentBins, centBinMin, centBinMax, NQvBins, QvBinMin, QvBinMax);

  TProfile *pV2EbE = new TProfile("pV2EbE","Integrated V2 Event by Event", NcentBins, centBinMin, centBinMax);
  TH2F     *hV2EbE = new TH2F("hV2EbE","Integrated V2 Event by Event",NcentBins, centBinMin, centBinMax,600,-3,3.);
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv=0; iEv<n_entries; iEv++)
  {
    if (iEv%100000==0) std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    // Get centrality
    float cent = CentB(bimp);
    if (cent == -1) continue;

    Int_t mc_num_particles = nh;

    // Read MC tracks
    float Qx_L_mc = 0., Qy_L_mc = 0., W_L_mc = 0.;
    float Qx_R_mc = 0., Qy_R_mc = 0., W_R_mc = 0.;
    int   Mult_L_mc = 0, Mult_R_mc = 0;
    float PsiEP_L_mc = 0., PsiEP_R_mc = 0.;
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
        Qx_L_mc += pt * cos(2.* phi);
        Qy_L_mc += pt * sin(2.* phi);
        W_L_mc  += pt;
        Mult_L_mc++;
      }

      // TPC Right EP
      if (eta > 0)
      {
        Qx_R_mc += pt * cos(2.* phi);
        Qy_R_mc += pt * sin(2.* phi);
        W_R_mc  += pt;
        Mult_R_mc++;
      }
    } // end of mc track loop

    if (Mult_L_mc > mult_EP_cut && Mult_R_mc > mult_EP_cut)
    {
      Qx_L_mc /= W_L_mc;
      Qy_L_mc /= W_L_mc;
      Qx_R_mc /= W_R_mc;
      Qy_R_mc /= W_R_mc;

      hQx_L_mc->Fill(cent, Qx_L_mc);
      hQy_L_mc->Fill(cent, Qy_L_mc);
      hQx_R_mc->Fill(cent, Qx_R_mc);
      hQy_R_mc->Fill(cent, Qy_R_mc);

      PsiEP_L_mc = 0.5 * atan2(Qy_L_mc, Qx_L_mc);
      PsiEP_R_mc = 0.5 * atan2(Qy_R_mc, Qx_R_mc);
    }
    else
    {
      PsiEP_L_mc = -999.;
      PsiEP_R_mc = -999.;
    } 

    float res_mc   = cos(2. * (PsiEP_R_mc - PsiEP_L_mc) );

    if (PsiEP_L_mc != -999. && PsiEP_R_mc != -999.)
    {
      pResMcTPC->Fill(cent, res_mc);
    }

    ////////////////////////////////////////////////////////////////////
    //
    // FLOW CALCULATIONS
    //
    ////////////////////////////////////////////////////////////////////
    
    float res_v2TPC_mc = vResTpc.at(GetCentBin(cent));
    TProfile *v2 = new TProfile("v2","Average Integrated V2 within Event", 1, 0, 1.);
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

      // EP-related cut
      if (PsiEP_L_mc == -999.) continue;
      if (PsiEP_R_mc == -999.) continue;

      // PID-related cut
      auto particle = (TParticlePDG*) TDatabasePDG::Instance()->GetParticle(pdg[iTr]);
      if (!particle) continue;
      
      float v2TPC = 0.;
      if (eta < 0)
      {
        v2TPC = cos( 2. * (phi - PsiEP_R_mc) );
      }
      if (eta > 0)
      {
        v2TPC = cos( 2. * (phi - PsiEP_L_mc) );
      }
      v2TPC /= res_v2TPC_mc;

      int pidID = -1;
      float charge = 1./3.*particle->Charge();

      if (charge!=0) v2->Fill(0.5,v2TPC);

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
    pV2EbE->Fill(cent, v2->GetBinContent(1));
    hV2EbE->Fill(cent, v2->GetBinContent(1));
    delete v2;
  } // end event loop

  //Writing output
  fo->cd();

  pResMcTPC->Write();
  pV2EbE -> Write();
  hV2EbE -> Write();
  for (int ipid=0; ipid < Npid; ipid++)
  {
    pv2mcTPC[ipid]->Write();
  }
  
  hQx_L_mc->Write();
  hQy_L_mc->Write();
  hQx_R_mc->Write();
  hQy_R_mc->Write();

  fo->Close();

  timer.Stop();
  timer.Print();
}
// root -l -b -q UrQMD.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'
