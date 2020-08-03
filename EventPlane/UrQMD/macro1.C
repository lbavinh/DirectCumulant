// #include "/mnt/pool/2/lbavinh/EventPlane/FlowANA.C"
// #include <iostream>
// #include <fstream>  
void macro1(int chain){
  gSystem->Load("/mnt/pool/2/lbavinh/EventPlane/FlowANA_C.so");
  char inFile[200], outFile[200];
  sprintf(inFile,"/mnt/pool/2/lbavinh/urqmd/chain/chain%i",chain);
  sprintf(outFile,"/mnt/pool/2/lbavinh/EventPlane/OUT/sum_perl_%i.root",chain);

  FlowANA *ana = new FlowANA();
  // ana->Booking("/mnt/pool/2/lbavinh/EventPlane/OUT/sum_test_1.root");
  ana -> Booking(outFile);
  // ana->Loop_a_file("/mnt/pool/2/lbavinh/urqmd/chain/chain1.root");
  ana -> Loop_a_file(inFile);
  // cout<< "Done. " << nfiles-1 << " files are processed." << endl;
  ana -> Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}