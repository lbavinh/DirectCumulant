void res2(TString infile="UrQMD_7.7GeV_res.root")
{
  TFile *fi = new TFile(infile.Data(),"read");
  
  if (!fi) return;

  TProfile *pRes2_mc   = (TProfile*) fi->Get("pResMcTPC");
  TProfile *pRes2_reco = (TProfile*) fi->Get("pResRecoTPC");
  TProfile *pRes2_model= (TProfile*) fi->Get("pResTPC");

  if (!pRes2_mc && !pRes2_reco && !pRes2_model) return;

  std::vector<float> vRes_mc;
  std::vector<float> vRes_reco;
  std::vector<float> vRes_model;

  float res2, res;
 
  if (pRes2_mc)
  { 
    for (int ibin = 0; ibin < pRes2_mc->GetNbinsX(); ibin++)
    {
      res2 = pRes2_mc->GetBinContent(ibin+1);
      if (res2 < 0) res = 0;
      else          res = sqrt(res2);
      vRes_mc.push_back(res);
    }
    std::cout << "const std::vector<float> vResMcTpc   = {";
    for (int i=0; i<vRes_mc.size(); i++)
    {
      std::cout << vRes_mc.at(i);
      if (i < vRes_mc.size()-1) std::cout << ", ";
    }
    std::cout << "};" << std::endl;
  }

  if (pRes2_reco)
  {
    for (int ibin = 0; ibin < pRes2_reco->GetNbinsX(); ibin++)
    {
      res2 = pRes2_reco->GetBinContent(ibin+1);
      if (res2 < 0) res = 0;
      else          res = sqrt(res2);
      vRes_reco.push_back(res);
    }
    std::cout << "const std::vector<float> vResRecoTpc = {";
    for (int i=0; i<vRes_reco.size(); i++)
    {
      std::cout << vRes_reco.at(i);
      if (i < vRes_reco.size()-1) std::cout << ", ";
    }
    std::cout << "};" << std::endl;
  }

  if (pRes2_model)
  { 
    for (int ibin = 0; ibin < pRes2_model->GetNbinsX(); ibin++)
    {
      res2 = pRes2_model->GetBinContent(ibin+1);
      if (res2 < 0) res = 0;
      else          res = sqrt(res2);
      vRes_model.push_back(res);
    }
    std::cout << "const std::vector<float> vResTpc     = {";
    for (int i=0; i<vRes_model.size(); i++)
    {
      std::cout << vRes_model.at(i);
      if (i < vRes_model.size()-1) std::cout << ", ";
    }
    std::cout << "};" << std::endl;
  }
}
