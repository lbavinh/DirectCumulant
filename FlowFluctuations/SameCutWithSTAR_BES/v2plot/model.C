#include "v2plot.C"
void model(){
  const int nmodel = 5;
  const int nenergy = 2;
  TString model[nmodel] = {"UrQMD","SMASH","AMPT08","AMPT15","vHLLEUrQMD"};
  TString energy[nenergy] = {"7.7GeV","11.5GeV"};
  for (int imod=0;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      // if (ien==0 && imod!=0 && imod!=1) continue; // at 4.5 GeV only have SMASH & UrQMD
      // if (ien==3 && imod!=4) continue; // at 19.6 GeV only have vHLLE+UrQMD
      // if (ien==4 && imod==1) continue;  // at 27 GeV only SMASH is missing
      // if (ien==5 && imod!=3 && imod!=4) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD      
      v2plot(model[imod].Data(), energy[ien].Data());
    }
  }
}