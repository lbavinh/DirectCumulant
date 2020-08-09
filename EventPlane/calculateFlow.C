#include "/weekly/povarov/lbavinh/EventPlane/hVana.C"
void calculateFlow(TString inFile, TString outFile) {
  hVana *ana = new hVana();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
// #include "hVana.C"
// void calculateFlow() {
//   hVana *ana = new hVana();
//   ana->Booking("./test.root");
//   ana->Loop_a_file("../Generator/test.root");
//   ana->Ana_end();
//   cout << "Histfile written. Congratz!" << endl;
// }