//#include "FlowANA.C"
#include "FlowANA.C"
#include <TStopwatch.h>
#include <TChain.h>
#include <iostream>
#include <fstream>

void main_proc(const char *filelist, const char *output = "./test1.root")
{
  TStopwatch timer;
  timer.Start();

  TChain *chain = new TChain("mctree");
  std::ifstream file(filelist);
  std::string str;
  int nfiles = 0;
  while (std::getline(file,str))
  {
    chain->Add(str.c_str());
    nfiles++;
  }
  std::cout << nfiles << " files were opened." << std::endl;

  FlowANA *t = new FlowANA(chain);
  t->ana_init(output);
  t->Loop();
  t->ana_end();

  timer.Stop();
  timer.Print();
}
