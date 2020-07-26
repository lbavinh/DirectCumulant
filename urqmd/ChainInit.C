#include "TChain.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
using namespace std;

void MakeChain(const char* fileList, const char *outFile, const int line1, const int lineLast){
    TChain *chain = new TChain("mctree");
    ifstream ifile(fileList);
    char fileName[200];
    int nFiles = 0;
    while(ifile.getline(fileName,200)) {
        ++nFiles;
        if (nFiles > lineLast) { break; }
        if (nFiles < line1)  { continue; }
        cout << "Adding "<< fileName <<" to chain "<< outFile << endl;
        chain -> Add(fileName);
    }
    TFile *f = new TFile (outFile,"recreate");
    f -> cd();
    chain -> Write();
    f -> Close();
    cout << "Done. " << nFiles << " files are added to chain" << outFile <<endl;
}

void ChainInit(){
    char list[500], chain[500];
    sprintf(list,"/mnt/pool/2/lbavinh/urqmd/runlist_urqmd_AuAu_7.7GeV.list");
    for (int i=0; i<10; i++){
        sprintf(chain,"/mnt/pool/2/lbavinh/urqmd/chain/chain%i.root",i);
        MakeChain(list,chain,(i*354)+1,(i+1)*354);
    }
    cout << "Tree chains were created successfully!" << endl;
}

