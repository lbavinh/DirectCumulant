#include "TROOT.h"
#include "TSystem.h"
void FlowRun(TString inFile, TString outFile) {
  R__LOAD_LIBRARY(./FlowANA_C.so)
  FlowANA *ana = new FlowANA();
  ana->Booking(outFile.Data());
  ana->Loop_a_list_of_file(inFile.Data());
  ana->Ana_end();
}
