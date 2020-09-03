#include "/weekly/povarov/lbavinh/Reco/mpdsim_MCtracks.C"
void calculateFlow_MCtracks(TString inFile, TString outFile) {
  mpdsim_MCtracks *ana = new mpdsim_MCtracks();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
