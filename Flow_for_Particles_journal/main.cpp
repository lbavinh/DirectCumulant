// #include "FlowQCumulant.C"
#include "RunFlowAnalysis.C"
// C++ headers
#include <iostream>
#include <fstream>
// ROOT headers
#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TString.h>

int main(int argc, char **argv)
{
  TString iFileName, oFileName, inputHistogram = "", inputHistogramFromLYZSecondRun = "";

  if (argc < 5)
  {
    std::cerr << "./FlowQCumulant -i INPUT -o OUTPUT [-inHist FirstRun.root -inHist2 SecondRun.root]" << std::endl;
    return 1;
  }
  for (Int_t i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" &&
        std::string(argv[i]) != "-inHist" &&
        std::string(argv[i]) != "-inHist2")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 2;
    }
    else
    {
      if (std::string(argv[i]) == "-i" && i != argc - 1)
      {
        iFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-i" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input file name was not specified " << std::endl;
        return 3;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 4;
      }
      if (std::string(argv[i]) == "-inHist" && i != argc - 1)
      {
        inputHistogram = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-inHist" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input histogram file name was not specified " << std::endl;
        return 1;
      }
      if (std::string(argv[i]) == "-inHist2" && i != argc - 1)
      {
        inputHistogramFromLYZSecondRun = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-inHist2" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Input histogram file from LYZ second run name was not specified " << std::endl;
        return 1;
      }
    }
  }

  RunFlowAnalysis(iFileName, oFileName, inputHistogram, inputHistogramFromLYZSecondRun);

  return 0;
}