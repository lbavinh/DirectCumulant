#include "/weekly/lbavinh/lbavinh/AMPT/AMPT.C"
void anaFlow(TString inFile, TString outFile) {
  AMPT *ana = new AMPT();
  ana->Booking(outFile.Data());
  ana->Loop_a_list_of_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
