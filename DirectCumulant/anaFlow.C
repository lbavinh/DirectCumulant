#include "QCumulant.C"
void anaFlow(TString inFile, TString outFile) {
  QCumulant *ana = new QCumulant();
  ana->Booking(outFile.Data());
  ana->Loop_a_list_of_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
