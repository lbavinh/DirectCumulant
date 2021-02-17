// Event selection

Double_t CentB(Double_t bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  Double_t fcent;
  if (bimp < 2.91)
    fcent = 2.5; // 0-5%
  
  else if (bimp < 4.17)
    fcent = 7.5; // 5-10%
    
  else if (bimp < 5.18)
    fcent = 12.5; // 10-15%
  else if (bimp < 6.02)
    fcent = 17.5; // 15-20%
  else if (bimp < 6.74)
    fcent = 22.5; // 20-25%
  else if (bimp < 7.38)
    fcent = 27.5; // 25-30%
  else if (bimp < 7.97)
    fcent = 32.5; // 30-35%
  else if (bimp < 8.53)
    fcent = 37.5; // 35-40%
  else if (bimp < 9.06)
    fcent = 42.5; // 40-45%
  else if (bimp < 9.56)
    fcent = 47.5; // 45-50%
  else if (bimp < 10.05)
    fcent = 52.5; // 50-55%
  else if (bimp < 10.50)
    fcent = 57.5; // 55-60%
  else if (bimp < 10.94)
    fcent = 62.5; // 60-65%
  else if (bimp < 11.35)
    fcent = 67.5; // 65-70%
  else if (bimp < 11.76)
    fcent = 72.5; // 70-75%
  else if (bimp < 12.19)
    fcent = 77.5; // 75-80%
  else
    fcent = -1;
  return fcent;
}

Int_t GetCentBin(Double_t cent)
{
  if (cent == -1)
    return -1;
  if (cent == 2.5)
    return 0;
  if (cent == 7.5)
    return 1;
  if (cent == 12.5)
    return 2;
  if (cent == 17.5)
    return 3;
  if (cent == 22.5)
    return 4;
  if (cent == 27.5)
    return 5;
  if (cent == 32.5)
    return 6;
  if (cent == 37.5)
    return 7;
  if (cent == 42.5)
    return 8;
  if (cent == 47.5)
    return 9;
  if (cent == 52.5)
    return 10;
  if (cent == 57.5)
    return 11;
  if (cent == 62.5)
    return 12;
  if (cent == 67.5)
    return 13;
  if (cent == 72.5)
    return 14;
  if (cent == 77.5)
    return 15;            
  return -1;
}

TChain *initChain(const TString &inputFileName, const char *chainName)
{
  TChain *chain = new TChain(chainName);
  std::ifstream file(inputFileName.Data());
  std::string line;
  while (std::getline(file, line))
  {
    chain->Add(line.c_str());
  }

  return chain;
}

Int_t findBin(Double_t pt)
{
  Int_t ipt = -1;

  for (Int_t j = 0; j < npt; j++)
  {
    if (pt >= pTBin[j] && pt < pTBin[j + 1])
      ipt = j;
  }

  return ipt;
}

Int_t findId(const Int_t &pdg)
{
  Int_t fId = -1;
  if (pdg == 211)
    fId = 1; // pion+
  if (pdg == 321)
    fId = 2; // kaon+
  if (pdg == 2212)
    fId = 3; // proton
  if (pdg == -211)
    fId = 5; // pion-
  if (pdg == -321)
    fId = 6; // kaon-
  if (pdg == -2212)
    fId = 7; // anti-proton
  return fId;
}