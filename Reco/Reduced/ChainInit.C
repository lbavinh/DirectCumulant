#include "TChain.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
using namespace std;

void MakeChain(const char* fileList, const char *outFile, const int line1, const int lineLast){
  TChain *chain = new TChain("mpdsim_reduced");
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

// void ChainInit(){
//   char list[500], chain[500];
//   sprintf(list,"/weekly/povarov/lbavinh/UrQMD/runlist_1.list");
//   for (int i=0; i<396; i++){
//     sprintf(chain,"/weekly/povarov/lbavinh/UrQMD/chain/chain%i.root",i);
//     MakeChain(list,chain,(i*49)+1,(i+1)*49);
//   }
//   cout << "Tree chains were created successfully!" << endl;
// }

void ChainInit(){
  char list[500], chain[500];
  sprintf(list,"/weekly/povarov/lbavinh/Reco/runlist.list");
  for (int i=0; i<390; i++){
    sprintf(chain,"/weekly/povarov/lbavinh/Reco/chain/chain%i.root",i);
    MakeChain(list,chain,(i*17)+1,(i+1)*17);
  }
  cout << "Tree chains were created successfully!" << endl;
}
