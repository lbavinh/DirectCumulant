#include "/weekly/povarov/lbavinh/Generator/Generator.C"
// #include "Generator.C"
void GenerateV2(TString outFile){
  Ana_init(outFile.Data());
  V2gen(100000,1000.); // (events to generate,MultMean)
  Ana_end();
}