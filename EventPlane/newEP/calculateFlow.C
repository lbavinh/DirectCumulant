#include "/weekly/povarov/lbavinh/EventPlane/hVana.C"
void calculateFlow(TString inFile, TString outFile) {
  hVana *ana = new hVana();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
