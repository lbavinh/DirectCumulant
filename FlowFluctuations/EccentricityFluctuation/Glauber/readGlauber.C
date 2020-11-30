#include <TROOT.h>
#include <TString.h>

#include "GlauberEccReader.C"

void readGlauber(TString inFileName, TString outFileName)
{
  //const char *treeName = "nt_Bi_Bi";
  const char *treeName = "nt_Au3_Au3";
  TFile *fi = new TFile(inFileName.Data(),"read");
  TTree *tree = (TTree*) fi->Get(treeName);
  if (!tree) return;
  GlauberEccReader *t = new GlauberEccReader(tree);
  t->SetOutputName(outFileName);
  t->Loop();
}
// source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_5gev/merge_glaub_5gev.root","Glauber_4.5GeV.root")'
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_7gev/merge_glaub_7gev.root","Glauber_7.7GeV.root")'
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_11gev/merge_glaub_11gev.root","Glauber_11.5GeV.root")'