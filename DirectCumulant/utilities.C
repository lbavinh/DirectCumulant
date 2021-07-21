// Event selection

Float_t CentB(Float_t bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  Float_t fcent;
  if      (bimp < 2.91)  fcent = 2.5; // 0-5%
  else if (bimp < 4.18)  fcent = 7.5; // 5-10%
  else if (bimp < 6.01)  fcent = 15.; // 10-20%
  else if (bimp < 7.37)  fcent = 25.; // 20-30%
  else if (bimp < 8.52)  fcent = 35.; // 30-40%
  else if (bimp < 9.57)  fcent = 45.; // 40-50%
  else if (bimp < 10.55) fcent = 55.; // 50-60%
  else if (bimp < 11.46) fcent = 65.; // 60-70%
  else if (bimp < 12.31) fcent = 75.; // 70-80%
  else                   fcent = -1;
  return fcent;
}


Int_t GetCentBin(Float_t cent)
{
  if (cent == -1) return -1;
  if (cent == 2.5) return 0;
  if (cent == 7.5) return 1;
  if (cent == 15.) return 2;
  if (cent == 25.) return 3;
  if (cent == 35.) return 4;
  if (cent == 45.) return 5;
  if (cent == 55.) return 6;
  if (cent == 65.) return 7;
  if (cent == 75.) return 8;
  return -1;
}

Double_t GetFHCalPhi(Int_t iModule)
{
  Int_t Nmodules = 45;
  Int_t xAxisSwitch = (iModule < Nmodules) ? 1 : -1;
  Int_t module = (iModule < Nmodules) ? iModule : iModule - Nmodules;
  Double_t x, y, phi = -999.;
  if (module >= 0 && module <= 4)
  {
    y = 45.;
    x = (module - 2) * 15.;
    phi = TMath::ATan2(y, x * xAxisSwitch);
  }
  else if ((module >= 5) && (module <= 39))
  {
    y = (3 - (module + 2) / 7) * 15.;
    x = (3 - (module + 2) % 7) * 15.;
    phi = TMath::ATan2(y, x * xAxisSwitch);
  }
  else if ((module >= 40) && (module <= 44))
  {
    y = -45.;
    x = (module - 42) * 15.;
    phi = TMath::ATan2(y, x * xAxisSwitch);
  }

  return phi;
}

std::string GetTreeName(const TString &inputFileName)
{
  std::string treeName;
  TString inputROOTFile;
  if (inputFileName.Contains(".root"))
  {
    inputROOTFile = inputFileName;
  }
  else
  {
    std::ifstream file(inputFileName.Data());
    std::string line;
    std::getline(file, line);
    inputROOTFile = (TString) line;
  }
  TFile *fi = new TFile(inputROOTFile.Data(),"READ");
  TTree* tree = nullptr;
  TIter nextkey( fi->GetListOfKeys() );
  TKey *key = nullptr;
  while ( (key = (TKey*) nextkey()) ) {
    TObject *obj = key->ReadObj();
    if ( obj->IsA()->InheritsFrom( TTree::Class() ) ) {
      tree = (TTree*)obj;
      break;
    }
  }
  if (!tree) { std::cout << "Cannot find any TTree in input ROOT file!!!" << std::endl; }
  else { treeName = (std::string) tree->GetName(); }
  if (treeName != "picodst" && treeName != "mctree") { std::cout << "Given tree format cannot being read!!!" << std::endl; }
  return treeName;
}

TChain* initChain(const TString &inputFileName, const char* chainName)
{
    TChain *chain = new TChain(chainName);
    if (inputFileName.Contains(".root"))
    {
      chain->Add(inputFileName.Data());
    }
    // if inputFileName contains filelist
    if (!inputFileName.Contains(".root"))
    {
      std::ifstream file(inputFileName.Data());
      std::string line;
      while(std::getline(file, line))
      {
        chain->Add(line.c_str());
      }
    }

    return chain;
}

Int_t findId(const PicoDstMCTrack *const &mcTrack)
{
  Int_t fId = -1;
  Int_t pdg = mcTrack->GetPdg();
  if (pdg == 211)                   fId = 1;  // pion+
  if (pdg == 321)                   fId = 2;  // kaon+
  if (pdg == 2212)                  fId = 3;  // proton
  if (pdg == -211)                  fId = 5;  // pion-
  if (pdg == -321)                  fId = 6;  // kaon-
  if (pdg == -2212)                 fId = 7;  // anti-proton

  return fId;
}