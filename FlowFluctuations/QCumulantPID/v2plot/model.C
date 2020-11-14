#include "v2plot.C"
void model(){
  const int nmodel = 5;
  const int nenergy = 2;
  TString model[nmodel] = {"UrQMD","SMASH","AMPT08","AMPT15","vHLLEUrQMD"};
  TString energy[nenergy] = {"7.7GeV","11.5GeV"};
  for (int imod=0;imod<nmodel;imod++){
    for (int iener=0;iener<nenergy;iener++){
      v2plot(model[imod].Data(), energy[iener].Data());
    }
  }
}