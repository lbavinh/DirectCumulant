#include "/weekly/povarov/lbavinh/UrQMD/CalRes.C"
void calculateRes(TString inFile, TString outFile) {
  CalRes *ana = new CalRes();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
