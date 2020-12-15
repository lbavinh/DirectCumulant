#include "plot.C"
void macro()
{
  const int nenergy = 6; // "4.5", "7.7", "11.5", "19.6", "27", "39"
  TString energy[nenergy] = {"4.5", "7.7", "11.5", "19.6", "27", "39"};
  for (int ie=0; ie<nenergy; ie++)
  {
    plot("Glauber",Form("%sGeV",energy[ie].Data()));
  }
}