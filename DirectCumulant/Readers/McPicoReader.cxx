#include "McPicoReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

// ClassImp(McPicoReader);
McPicoReader::McPicoReader() : fChain(0)
{
}

McPicoReader::~McPicoReader()
{
}

void McPicoReader::Init(TChain *chain)
{
  if (!chain)
    return;
  fChain = chain;
  // fChain->SetMakeClass(1);

  fChain->SetBranchAddress("bimp", &bimp, &b_bimp);
  fChain->SetBranchAddress("phi2", &phi2, &b_phi2);
  fChain->SetBranchAddress("phi3", &phi3, &b_phi3);
  fChain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
  fChain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
  fChain->SetBranchAddress("npart", &npart, &b_npart);
  fChain->SetBranchAddress("nh", &nh, &b_nh);
  fChain->SetBranchAddress("momx", momx, &b_momx);
  fChain->SetBranchAddress("momy", momy, &b_momy);
  fChain->SetBranchAddress("momz", momz, &b_momz);
  fChain->SetBranchAddress("ene", ene, &b_ene);
  fChain->SetBranchAddress("hid", hid, &b_hid);
  fChain->SetBranchAddress("pdg", pdg, &b_pdg);
  fChain->SetBranchAddress("charge", charge, &b_charge);
}

PicoDstMCEvent *McPicoReader::ReadMcEvent(Int_t ev_num)
{
  if (!fChain)
    return nullptr;
  fChain->GetEntry(ev_num);
  auto event = new PicoDstMCEvent();
  event->SetB(bimp);
  event->SetPhiRP(0.);
  // event->SetVertex(0., 0., 0.);
  return event;
}

Int_t McPicoReader::GetMcTrackSize()
{
  return nh;
}

PicoDstMCTrack *McPicoReader::ReadMcTrack(Int_t tr_num)
{
  if (!fChain)
  {
    return nullptr;
  }
  auto track = new PicoDstMCTrack();
  track->SetPxPyPz(momx[tr_num], momy[tr_num], momz[tr_num]);
  track->SetPdg(pdg[tr_num]);
  track->SetEnergy(ene[tr_num]);
  return track;
}
