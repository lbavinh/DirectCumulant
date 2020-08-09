#include "/weekly/nikolaev/lbavinh/EventPlane/CalRes.C"
// void calculateRes() {
//   loop_a_list_of_trees();
// }

void calculateRes(TString inFile, TString outFile) {
  CalRes *ana = new CalRes();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
