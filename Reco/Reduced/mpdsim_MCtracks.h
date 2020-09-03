//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 19 12:42:37 2020 by ROOT version 6.12/06
// from TTree mpdsim_reduced/mpdsim_reduced
// found on file: /nica/mpd21/parfenov/mpd_winter2019/mpd_prod/picoDst_7.7gev_7M/picodst_997681_9.root
//////////////////////////////////////////////////////////

#ifndef mpdsim_MCtracks_h
#define mpdsim_MCtracks_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TComplex.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.
static const int MAXMC = 2000;
static const int MAXNT = 1500;
class mpdsim_MCtracks {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         b_mc;
   Float_t         phiEP_mc;
   Float_t         x_vertex_mc;
   Float_t         y_vertex_mc;
   Float_t         z_vertex_mc;
   Float_t         x_vertex_mpd;
   Float_t         y_vertex_mpd;
   Float_t         z_vertex_mpd;
   Long64_t        n_tracks_mc;
   Int_t           mother_ID_mc[MAXMC];   //[n_tracks_mc]
   Int_t           PDG_code_mc[MAXMC];   //[n_tracks_mc]
   Float_t         px_mc[MAXMC];   //[n_tracks_mc]
   Float_t         py_mc[MAXMC];   //[n_tracks_mc]
   Float_t         pz_mc[MAXMC];   //[n_tracks_mc]
   Float_t         start_x_mc[MAXMC];   //[n_tracks_mc]
   Float_t         start_y_mc[MAXMC];   //[n_tracks_mc]
   Float_t         start_z_mc[MAXMC];   //[n_tracks_mc]
   Float_t         energy_mc[MAXMC];   //[n_tracks_mc]
   Long64_t        n_tracks_mpd;
   Long64_t        k_tracks_mpd;
   Float_t         eta_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         phi_mpd[MAXNT];   //[n_tracks_mpd]
   Int_t           TOF_flag_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         ZDC_energy_mpd[90];
   Float_t         pid_tpc_prob_electron_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         pid_tpc_prob_pion_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         pid_tpc_prob_kaon_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         pid_tpc_prob_proton_mpd[MAXNT];   //[n_tracks_mpd]
   Bool_t          isPIDTofTpc[MAXNT];   //[n_tracks_mpd]
   Bool_t          isPIDTpc[MAXNT];   //[n_tracks_mpd]
   Float_t         tof_beta_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         tof_mass2_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         dEdx_tpc_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         chi2_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         chi2_vertex[MAXNT];   //[n_tracks_mpd]
   Float_t         pt_error_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         theta_error_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         phi_error_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         DCA_x_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         DCA_y_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         DCA_z_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         DCA_x_mc[MAXNT];   //[n_tracks_mpd]
   Float_t         DCA_y_mc[MAXNT];   //[n_tracks_mpd]
   Float_t         DCA_z_mc[MAXNT];   //[n_tracks_mpd]
   Int_t           n_hits_mpd[MAXNT];   //[n_tracks_mpd]
   Int_t           n_hits_poss_mpd[MAXNT];   //[n_tracks_mpd]
   Float_t         signed_pt_mpd[MAXNT];   //[n_tracks_mpd]
   Int_t           centrality_tpc_mpd;
   Long64_t        id_from_mc_mpd[MAXNT];   //[n_tracks_mpd]

   // List of branches
   TBranch        *b_b_mc;   //!
   TBranch        *b_phiEP_mc;   //!
   TBranch        *b_x_vertex_mc;   //!
   TBranch        *b_y_vertex_mc;   //!
   TBranch        *b_z_vertex_mc;   //!
   TBranch        *b_x_vertex_mpd;   //!
   TBranch        *b_y_vertex_mpd;   //!
   TBranch        *b_z_vertex_mpd;   //!
   TBranch        *b_n_tracks_mc;   //!
   TBranch        *b_mother_ID_mc;   //!
   TBranch        *b_PDG_code_mc;   //!
   TBranch        *b_px_mc;   //!
   TBranch        *b_py_mc;   //!
   TBranch        *b_pz_mc;   //!
   TBranch        *b_start_x_mc;   //!
   TBranch        *b_start_y_mc;   //!
   TBranch        *b_start_z_mc;   //!
   TBranch        *b_energy_mc;   //!
   TBranch        *b_n_tracks_mpd;   //!
   TBranch        *b_k_tracks_mpd;   //!
   TBranch        *b_eta_mpd;   //!
   TBranch        *b_phi_mpd;   //!
   TBranch        *b_TOF_flag_mpd;   //!
   TBranch        *b_ZDC_energy_mpd;   //!
   TBranch        *b_pid_tpc_prob_electron_mpd;   //!
   TBranch        *b_pid_tpc_prob_pion_mpd;   //!
   TBranch        *b_pid_tpc_prob_kaon_mpd;   //!
   TBranch        *b_pid_tpc_prob_proton_mpd;   //!
   TBranch        *b_isPIDTofTpc;   //!
   TBranch        *b_isPIDTpc;   //!
   TBranch        *b_tof_beta_mpd;   //!
   TBranch        *b_tof_mass2_mpd;   //!
   TBranch        *b_dEdx_tpc_mpd;   //!
   TBranch        *b_chi2_mpd;   //!
   TBranch        *b_chi2_vertex;   //!
   TBranch        *b_pt_error_mpd;   //!
   TBranch        *b_theta_error_mpd;   //!
   TBranch        *b_phi_error_mpd;   //!
   TBranch        *b_DCA_x_mpd;   //!
   TBranch        *b_DCA_y_mpd;   //!
   TBranch        *b_DCA_z_mpd;   //!
   TBranch        *b_DCA_x_mc;   //!
   TBranch        *b_DCA_y_mc;   //!
   TBranch        *b_DCA_z_mc;   //!
   TBranch        *b_n_hits_mpd;   //!
   TBranch        *b_n_hits_poss_mpd;   //!
   TBranch        *b_signed_pt_mpd;   //!
   TBranch        *b_centrality_tpc_mpd;   //!
   TBranch        *b_id_from_mc_mpd;   //!

   mpdsim_MCtracks(TTree *tree=0);
   virtual ~mpdsim_MCtracks();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   // additional function
   void Booking(TString outFile);
   void Loop_a_file(TString file);
   void Ana_end();
   void Ana_event();

};

#endif

#ifdef mpdsim_MCtracks_cxx
mpdsim_MCtracks::mpdsim_MCtracks(TTree *tree) : fChain(0) 
{
// // if parameter tree is not specified (or zero), connect the file
// // used to generate this class and read the Tree.
//    if (tree == 0) {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nica/mpd21/parfenov/mpd_winter2019/mpd_prod/picoDst_7.7gev_7M/picodst_997681_9.root");
//       if (!f || !f->IsOpen()) {
//          f = new TFile("/nica/mpd21/parfenov/mpd_winter2019/mpd_prod/picoDst_7.7gev_7M/picodst_997681_9.root");
//       }
//       f->GetObject("mpdsim_reduced",tree);

//    }
//    Init(tree);
}

mpdsim_MCtracks::~mpdsim_MCtracks()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mpdsim_MCtracks::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mpdsim_MCtracks::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void mpdsim_MCtracks::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("b_mc", &b_mc, &b_b_mc);
   fChain->SetBranchAddress("phiEP_mc", &phiEP_mc, &b_phiEP_mc);
   fChain->SetBranchAddress("x_vertex_mc", &x_vertex_mc, &b_x_vertex_mc);
   fChain->SetBranchAddress("y_vertex_mc", &y_vertex_mc, &b_y_vertex_mc);
   fChain->SetBranchAddress("z_vertex_mc", &z_vertex_mc, &b_z_vertex_mc);
   fChain->SetBranchAddress("x_vertex_mpd", &x_vertex_mpd, &b_x_vertex_mpd);
   fChain->SetBranchAddress("y_vertex_mpd", &y_vertex_mpd, &b_y_vertex_mpd);
   fChain->SetBranchAddress("z_vertex_mpd", &z_vertex_mpd, &b_z_vertex_mpd);
   fChain->SetBranchAddress("n_tracks_mc", &n_tracks_mc, &b_n_tracks_mc);
   fChain->SetBranchAddress("mother_ID_mc", mother_ID_mc, &b_mother_ID_mc);
   fChain->SetBranchAddress("PDG_code_mc", PDG_code_mc, &b_PDG_code_mc);
   fChain->SetBranchAddress("px_mc", px_mc, &b_px_mc);
   fChain->SetBranchAddress("py_mc", py_mc, &b_py_mc);
   fChain->SetBranchAddress("pz_mc", pz_mc, &b_pz_mc);
   fChain->SetBranchAddress("start_x_mc", start_x_mc, &b_start_x_mc);
   fChain->SetBranchAddress("start_y_mc", start_y_mc, &b_start_y_mc);
   fChain->SetBranchAddress("start_z_mc", start_z_mc, &b_start_z_mc);
   fChain->SetBranchAddress("energy_mc", energy_mc, &b_energy_mc);
   fChain->SetBranchAddress("n_tracks_mpd", &n_tracks_mpd, &b_n_tracks_mpd);
   fChain->SetBranchAddress("k_tracks_mpd", &k_tracks_mpd, &b_k_tracks_mpd);
   fChain->SetBranchAddress("eta_mpd", eta_mpd, &b_eta_mpd);
   fChain->SetBranchAddress("phi_mpd", phi_mpd, &b_phi_mpd);
   fChain->SetBranchAddress("TOF_flag_mpd", TOF_flag_mpd, &b_TOF_flag_mpd);
   fChain->SetBranchAddress("ZDC_energy_mpd", ZDC_energy_mpd, &b_ZDC_energy_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_electron_mpd", pid_tpc_prob_electron_mpd, &b_pid_tpc_prob_electron_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_pion_mpd", pid_tpc_prob_pion_mpd, &b_pid_tpc_prob_pion_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_kaon_mpd", pid_tpc_prob_kaon_mpd, &b_pid_tpc_prob_kaon_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_proton_mpd", pid_tpc_prob_proton_mpd, &b_pid_tpc_prob_proton_mpd);
   fChain->SetBranchAddress("isPIDTofTpc", isPIDTofTpc, &b_isPIDTofTpc);
   fChain->SetBranchAddress("isPIDTpc", isPIDTpc, &b_isPIDTpc);
   fChain->SetBranchAddress("tof_beta_mpd", tof_beta_mpd, &b_tof_beta_mpd);
   fChain->SetBranchAddress("tof_mass2_mpd", tof_mass2_mpd, &b_tof_mass2_mpd);
   fChain->SetBranchAddress("dEdx_tpc_mpd", dEdx_tpc_mpd, &b_dEdx_tpc_mpd);
   fChain->SetBranchAddress("chi2_mpd", chi2_mpd, &b_chi2_mpd);
   fChain->SetBranchAddress("chi2_vertex", chi2_vertex, &b_chi2_vertex);
   fChain->SetBranchAddress("pt_error_mpd", pt_error_mpd, &b_pt_error_mpd);
   fChain->SetBranchAddress("theta_error_mpd", theta_error_mpd, &b_theta_error_mpd);
   fChain->SetBranchAddress("phi_error_mpd", phi_error_mpd, &b_phi_error_mpd);
   fChain->SetBranchAddress("DCA_x_mpd", DCA_x_mpd, &b_DCA_x_mpd);
   fChain->SetBranchAddress("DCA_y_mpd", DCA_y_mpd, &b_DCA_y_mpd);
   fChain->SetBranchAddress("DCA_z_mpd", DCA_z_mpd, &b_DCA_z_mpd);
   fChain->SetBranchAddress("DCA_x_mc", DCA_x_mc, &b_DCA_x_mc);
   fChain->SetBranchAddress("DCA_y_mc", DCA_y_mc, &b_DCA_y_mc);
   fChain->SetBranchAddress("DCA_z_mc", DCA_z_mc, &b_DCA_z_mc);
   fChain->SetBranchAddress("n_hits_mpd", n_hits_mpd, &b_n_hits_mpd);
   fChain->SetBranchAddress("n_hits_poss_mpd", n_hits_poss_mpd, &b_n_hits_poss_mpd);
   fChain->SetBranchAddress("signed_pt_mpd", signed_pt_mpd, &b_signed_pt_mpd);
   fChain->SetBranchAddress("centrality_tpc_mpd", &centrality_tpc_mpd, &b_centrality_tpc_mpd);
   fChain->SetBranchAddress("id_from_mc_mpd", id_from_mc_mpd, &b_id_from_mc_mpd);
   Notify();
}

Bool_t mpdsim_MCtracks::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mpdsim_MCtracks::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mpdsim_MCtracks::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mpdsim_reduced_cxx
