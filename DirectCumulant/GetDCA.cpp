
#include <iostream>
#include <fstream>
#include <TStopwatch.h>
#include <TH1F.h>
#include <TClonesArray.h>
#include <TFile.h>

#include <PicoDstMCEvent.h>
#include <PicoDstRecoEvent.h>
#include <PicoDstMCTrack.h>
#include <PicoDstRecoTrack.h>
#include <PicoDstFHCal.h>


#include <IReader.h>
#include <PicoDstReader.h>
#include <QVector.h> // includes constants, need to be improved!!!! - write a class with constants

#include "utilities.C"

Int_t GetPtBin(Double_t pt)
{
  Int_t ipt = -1;
  for (Int_t j = 0; j < npt; j++) { if (pt >= pTBin[j] && pt < pTBin[j + 1]) ipt = j; }
  return ipt;
}

Int_t GetEtaBin(Double_t eta)
{
  Int_t ieta = -1;
  for (Int_t j = 0; j < netaBin; j++) { if (eta >= etaBin[j] && eta < etaBin[j + 1]) ieta = j; }
  return ieta;
}


int main(int argc, char **argv)
{
  TString iFileName, oFileName;
  if (argc < 5)
  {
    std::cerr << "./GetDCA -i INPUTFILE/LIST -o OUTPUT.root" << std::endl;
    return 1;
  }
  for (Int_t i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" )
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
    }
  }

  TStopwatch timer;
  timer.Start();
  // Configure input information
  std::string format = "picodst";
  TChain *chain = initChain(iFileName, format.c_str());

  // IReader* reader = nullptr;
  // if (format == "picodst")
  // {
  //   reader = new PicoDstReader();
  // }


  if (!chain)
  {
    std::cerr << "[ERROR]: nothing to read. Maybe the input TTree(s) is(are) empty?" << std::endl;
    return 10;
  }
  const Int_t Ndim = 3;
  // Init output histograms
  TH1F *h_dca[Ndim][npt][netaBin];

  for (Int_t dim = 0; dim < Ndim; ++dim)
  {
    for (Int_t ptbin = 0; ptbin < npt; ++ptbin)
    {
      for (Int_t etabin = 0; etabin < netaBin; ++etabin)
      {
        h_dca[dim][ptbin][etabin] = new TH1F(
            Form("h_dca_%i_%i_%i", dim, ptbin, etabin),
            Form("DCA distribution for %.2f < p_{t} < %.2f and %.2f < #eta < %.2f",
                 pTBin[ptbin], pTBin[ptbin + 1], etaBin[etabin], etaBin[etabin + 1]),
            4000, -50., 50);
      }
    }
  }


  TClonesArray *recoTracks = nullptr;
  chain->SetBranchAddress("recotracks", &recoTracks);

  // Start event loop
  Int_t n_entries = chain->GetEntries();
  for (Int_t iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 1000 == 0)
      std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
    chain->GetEntry(iEv);

    Int_t reco_mult = recoTracks->GetEntriesFast();
    // Read Reco tracks
    for (Int_t iTr = 0; iTr < reco_mult; iTr++)
    {
      auto recoTrack = (PicoDstRecoTrack *)recoTracks->UncheckedAt(iTr);
      
      if (!recoTrack)
        continue;

      Int_t pt_bin = GetPtBin(TMath::Abs(recoTrack->GetPt()));
      Int_t eta_bin = GetEtaBin(recoTrack->GetEta());
      if ((eta_bin == -1) || (pt_bin == -1))
        continue;
      h_dca[0][pt_bin][eta_bin]->Fill(recoTrack->GetDCAx());
      h_dca[1][pt_bin][eta_bin]->Fill(recoTrack->GetDCAy());
      h_dca[2][pt_bin][eta_bin]->Fill(recoTrack->GetDCAz());
    }
  }

  // Init output file
  TFile *fo = new TFile(oFileName.Data(), "recreate");
  fo->cd();
  for (Int_t dim = 0; dim < Ndim; ++dim)
  {
    for (Int_t ptbin = 0; ptbin < npt; ++ptbin)
    {
      for (Int_t etabin = 0; etabin < netaBin; ++etabin)
      {
        // std::cout << h_dca[dim][ptbin][etabin]->GetName() << " ("
        //           << h_dca[dim][ptbin][etabin]->GetEntries() << " entries)"
        //           << std::endl;
        h_dca[dim][ptbin][etabin]->Write();
      }
    }
  }
  std::cout << "Closing output file." << std::endl;
  fo->Close();

  timer.Stop();
  timer.Print();
  return 0;
}