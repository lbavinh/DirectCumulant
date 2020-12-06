#include <TROOT.h>
#include <TString.h>

#include "Glissando.C"

void readGlissando(TString inFileName, TString outFileName)
{
  //const char *treeName = "nt_Bi_Bi";
  const char *treeName = "events";
  TFile *fi = new TFile(inFileName.Data(),"read");
  TTree *tree = (TTree*) fi->Get(treeName);
  if (!tree) return;
  Glissando *t = new Glissando(tree);
  t->SetOutputName(outFileName);
  t->Loop();
}
// source /mnt/pool/4/anikeev/root-6.18.02/builddir/bin/thisroot.sh
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_5gev/merge_glaub_5gev.root","Glauber_4.5GeV.root")'
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_7gev/merge_glaub_7gev.root","Glauber_7.7GeV.root")'
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_11gev/merge_glaub_11gev.root","Glauber_11.5GeV.root")'
// root -l -b -q readGlauber.C+'("/mnt/pool/nica/6/parfenovpeter/CentralityGlauber/Glauber_gen_200gev/merge_glaub_200gev.root","Glauber_200GeV.root")'