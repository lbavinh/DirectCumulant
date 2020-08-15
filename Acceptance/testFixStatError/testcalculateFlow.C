#include "FlowANA.C"
void testcalculateFlow() {
  FlowANA *ana = new FlowANA();
  ana->Booking("sum_test.root");
  ana->Loop_a_file("tree_acceptance.root");
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
