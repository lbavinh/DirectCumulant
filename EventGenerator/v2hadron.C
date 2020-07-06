#include "hTana.C"
using namespace std;
void v2hadron()
{
    //gSystem->Load("./hTana_C.so");
    hTana *ana=new hTana();
    ana->ana_init("v2hadron_10000.root"); // name for root file with results 
    ana->v2gen(10000,50,10);
    ana->ana_end();
    cout<<"histfile written"<<endl;
}
