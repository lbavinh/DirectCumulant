#include "hVana.C"
void macro() {
    //gSystem->Load("./hVana_C.so");
    hVana *ana = new hVana();
    ana->Booking("v2QC.root");
    ana->Loop_a_file("v2hadron.root");
    ana->Ana_end();
}