#include "/mnt/pool/2/lbavinh/EventGenerator/hTana.C" // /mnt/pool/2/lbavinh/EventGenerator/
using namespace std;
void v2hadron(TString outFile) {
    hTana *ana=new hTana();
    ana->ana_init(outFile.Data());
    ana->v2gen(500000,250.);
    ana->ana_end();
}
