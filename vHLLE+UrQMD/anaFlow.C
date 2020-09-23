#include "/weekly/lbavinh/lbavinh/vHLLE+UrQMD/FlowANA.C"
void anaFlow(TString inFile, TString outFile) {
  FlowANA *ana = new FlowANA();
  ana->Booking(outFile.Data());
  ana->Loop_a_list_of_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
