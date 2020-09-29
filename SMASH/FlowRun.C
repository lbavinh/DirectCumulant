#include "TROOT.h"
#include "TSystem.h"
#include <iostream>
void FlowRun(TString inFile, TString outFile) {
  R__LOAD_LIBRARY(./smash_C.so)
  // gSystem->Load("./smash_C.so");
  smash *ana = new smash();
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
