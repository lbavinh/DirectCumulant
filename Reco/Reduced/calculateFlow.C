#include "/weekly/povarov/lbavinh/Reco/mpdsim_reduced.C"
void calculateFlow(TString inFile, TString outFile) {
  mpdsim_reduced *ana = new mpdsim_reduced();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
