// Event selection

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
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


int GetCentBin(float cent)
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