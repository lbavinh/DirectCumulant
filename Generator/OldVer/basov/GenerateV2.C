// #include "/weekly/povarov/lbavinh/Generator/Generator.C"
// #include "/mnt/pool/2/lbavinh/EventGenerator/Generator.C"
void GenerateV2(TString outFile){
  gSystem -> Load("/mnt/pool/2/lbavinh/EventGenerator/Generator_C.so");
  Ana_init(outFile.Data());
  V2gen(1000000,1000.); // (events to generate,MultMean)
  Ana_end();
}