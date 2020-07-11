#include "/mnt/pool/2/lbavinh/EventGenerator/hTana.C"
using namespace std;
void v2hadron(char *outFile) {
    hTana *ana=new hTana();
    ana->ana_init(outFile);
    ana->v2gen(1000000,250,50);
    ana->ana_end();
}
