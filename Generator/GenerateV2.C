// #include "Generator.C"
#include "/weekly/nikolaev/lbavinh/Generator/Generator.C"
void GenerateV2(TString outFile){
  Ana_init(outFile.Data());
  V2gen(100000,250.); // (events to generate,MultMean)
  Ana_end();
}