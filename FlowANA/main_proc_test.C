//#include "FlowANA.C"
#include "FlowANA_test.C"
#include <TStopwatch.h>
#include <TChain.h>
#include <iostream>
#include <fstream>

void main_proc_test(const char *filelist, char *output)
{
  TStopwatch timer;
  timer.Start();

  TChain *chain = new TChain("mctree");
  std::ifstream file(filelist);
  std::string str;
  while (std::getline(file,str))
  {
    chain->Add(str.c_str());
  }

  FlowANA *t = new FlowANA(chain);
  t->ana_init(output);
  t->Loop();
  t->ana_end();

  timer.Stop();
  timer.Print();
}
