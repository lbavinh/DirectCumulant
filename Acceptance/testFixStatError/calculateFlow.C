#include "/weekly/povarov/lbavinh/Acceptance/FlowANA.C"
void calculateFlow(TString inFile, TString outFile) {
  FlowANA *ana = new FlowANA();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
