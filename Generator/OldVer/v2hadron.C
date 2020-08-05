#include "/mnt/pool/2/lbavinh/EventGenerator/hTana.C"
void v2hadron(TString outFile) {
    //gSystem -> Load("./hTana_C.so");
    hTana *ana=new hTana();
    ana->ana_init(outFile.Data());
    ana->v2gen(1000000,250.);
    ana->ana_end();
}
