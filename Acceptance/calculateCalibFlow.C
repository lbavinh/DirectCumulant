#include "CalibRes.C"
// void calculateRes() {
//   loop_a_list_of_trees();
// }

void calculateCalibFlow() {
  CalibRes *ana = new CalibRes();
  ana->Booking("test.root");
  ana->Loop_a_file("acc.root");
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
