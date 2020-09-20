#include "/weekly/lbavinh/lbavinh/SMASH/smash.C"
void anaFlow(TString inFile, TString outFile) {
  smash *ana = new smash();
  ana->Booking(outFile.Data());
  ana->Loop_a_list_of_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
