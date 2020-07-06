#include "hVana.C"
using namespace std;
void v2QC() {
    //gSystem->Load("./hVana_C.so");
    hVana *ana=new hVana();
    ana->ana_init("v2QC_10000.root"); // name for root file with results 
    ana->loop_a_file("v2hadron_10000.root");
    ana->ana_end();
    cout<<"histfile written"<<endl;
}