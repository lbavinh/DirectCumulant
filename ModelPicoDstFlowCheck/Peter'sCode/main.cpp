#include <get_flow_pico.C>
#include <get_flow_model.C>

#include <iostream>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>

int main(int argc, char **argv)
{
  TString iFileName, oFileName;
  if (argc < 5)
  {
    std::cerr << "./run -i inputfile -o outputfile" << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
      std::string(argv[i]) != "-o")
    {
      std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 1;
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
        return 1;
      }
      if (std::string(argv[i]) == "-o" && i != argc - 1)
      {
        oFileName = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-o" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Output file name was not specified " << std::endl;
        return 1;
      }
    }
  }

  TFile *fi = new TFile(iFileName.Data(),"read");
  TTree *mctree   = (TTree*) fi->Get("mctree");
  TTree *picotree = (TTree*) fi->Get("picodst");

  bool isModel = (mctree) ? true : false;
  bool isPico  = (picotree) ? true : false;

  fi->Close();

  if (!isModel && !isPico)
  {
    std::cerr << "\n[ERROR]: No mcpico nor picodst TTree were found. Exit the program." << std::endl;
    return 2;
  }

  if (isModel)
  {
    std::cout << "run: mcpico was found in the input file" << std::endl;
    get_flow_model(iFileName, oFileName);
  }
  if (isPico)
  {
    std::cout << "run: picodst was found in the input file" << std::endl;
    get_flow_pico(iFileName, oFileName);
  }
  return 0;
}
