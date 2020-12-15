// Do not forget to source setPicoDst.sh script

void test_Ids(TString infile)
{
  TStopwatch timer;
  timer.Start();

  TFile *fi = new TFile(infile.Data(),"read");
  TTree *tree = (TTree*) fi->Get("picodst");
  TClonesArray *recoTracks = nullptr;
  TClonesArray *mcTracks = nullptr;
  tree->SetBranchAddress("mctracks",&mcTracks);
  tree->SetBranchAddress("recotracks",&recoTracks);
  bool is_success = true;
  int n_entries = tree->GetEntriesFast();
  for (int iEv=0; iEv<n_entries; iEv++)
  { 
    tree->GetEntry(iEv); 
    std::cout << "Event [" << iEv << "/" << n_entries << "]\r" << std::flush;
    for (int i=0; i<recoTracks->GetEntriesFast(); i++)
    { 
      auto recoTrack = (PicoDstRecoTrack*) recoTracks->UncheckedAt(i); 
      auto mcTrack = (PicoDstMCTrack*) mcTracks->UncheckedAt(recoTrack->GetMcId()); 
      if (recoTrack->GetInitialMcId() != mcTrack->GetInitialId()) 
      {
        is_success = false;
        std::cout << "[WARNING] Event " << iEv << ", recotrack " << i << ": InitMcId(reco)= " << recoTrack->GetInitialMcId() << ", InitMcId(mc)= " << mcTrack->GetInitialId() << ", McId= " << recoTrack->GetMcId() << std::endl; 
      }
    } 
  }
  std::cout << "Total number of events: " << n_entries << std::endl;
  if (is_success)
    std::cout << "SUCCESS: MC and RECO tracks are linked correctly." << std::endl;
  if (!is_success)
    std::cout << "FAILED." << std::endl;

  timer.Stop();
  timer.Print();
}
