#include <TROOT.h>
#include <TString.h>
#include <fstream>
#include "Glissando.C"

void readGlissando_chain(TString inFileName, TString outFileName)
{

  TChain *chain = new TChain("events");
  std::ifstream file(inFileName.Data());
  std::string line;
  while(std::getline(file, line))
  {
    chain->Add(line.c_str());
  }
  if (!chain) return;
  Glissando *t = new Glissando(chain);
  t->SetOutputName(outFileName);
  t->Loop();
}
// root -l -b -q readGlissando_chain.C+'("/weekly/lbavinh/lbavinh/glissando3.44/runlist_7.7.list","Glissando_7.7GeV.root")'
