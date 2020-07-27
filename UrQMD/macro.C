#include "/mnt/pool/2/lbavinh/urqmd/FlowANA.C"
#include <iostream>
#include <fstream>  
void macro(){
    FlowANA *ana = new FlowANA();
    ana->Booking("/mnt/pool/2/lbavinh/urqmd/OUT/v2QC_etagap_0.root");
    // ifstream ifile("/mnt/pool/2/lbavinh/urqmd/runlist_urqmd_AuAu_7.7GeV.list");
    // char filename[200];
    // int nfiles=1;
    // while(ifile.getline(filename,200)) {
    //     cout << nfiles <<" file is processing "<<filename <<endl;
    //     ana->Loop_a_file(filename);
    //     nfiles++;
    // }
    ana->Loop_a_file("/mnt/pool/2/lbavinh/urqmd/chain/chain0.root");
    // cout<< "Done. " << nfiles-1 << " files are processed." << endl;
    ana -> Ana_end();
    cout << "Histfile written. Congratz!" << endl;
}