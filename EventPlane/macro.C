// #include "/mnt/pool/2/lbavinh/EventPlane/FlowANA.C"
// #include <iostream>
// #include <fstream>  
void macro(TString inFile, TString outFile){
  gSystem->Load("/mnt/pool/2/lbavinh/EventPlane/FlowANA_C.so");
  FlowANA *ana = new FlowANA();
  // ana->Booking("/mnt/pool/2/lbavinh/EventPlane/OUT/sum_test_1.root");
  ana -> Booking(outFile.Data());
  // ana->Loop_a_file("/mnt/pool/2/lbavinh/urqmd/chain/chain1.root");
  ana -> Loop_a_file(inFile.Data());
  // cout<< "Done. " << nfiles-1 << " files are processed." << endl;
  ana -> Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}