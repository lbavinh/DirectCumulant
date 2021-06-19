#include "FlowANA.C"
void calculateFlow(TString inFile, TString outFile, Int_t runNum = 0) {
  FlowANA *ana = new FlowANA();
  ana->SetRunNum(runNum);
  ana->Booking(outFile.Data());
  ana->Loop_a_file(inFile.Data());
  ana->Ana_end();
  cout << "Histfile written. Congratz!" << endl;
}
int main(int argc, char **argv)
{
  TString iFileName, oFileName, run ;
  if (argc < 5)
  {
    std::cerr << "./FlowQCumulant -i INPUT -o OUTPUT -r RUNNUMBER" << std::endl;
    return 1;
  }
  for (Int_t i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "-i" &&
        std::string(argv[i]) != "-o" &&
        std::string(argv[i]) != "-r")
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
      if (std::string(argv[i]) == "-r" && i != argc - 1)
      {
        run = argv[++i];
        continue;
      }
      if (std::string(argv[i]) == "-r" && i == argc - 1)
      {
        std::cerr << "\n[ERROR]: Run order was not specified " << std::endl;
        return 1;
      }
    }
  }
  int runNum = strtol(run, NULL, 10);
  calculateFlow(iFileName, oFileName, runNum);

  return 0;
}
