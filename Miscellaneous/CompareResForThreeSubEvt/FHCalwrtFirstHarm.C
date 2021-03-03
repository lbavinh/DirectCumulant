#include "DrawTGraphImp.C"
void FHCalwrtFirstHarm()
{
  TFile *fi = new TFile("EventPlane_UrQMD_7.7.root","read");
  TProfile *prResFHCal = (TProfile*)fi->Get("prResFHCal");
  TProfile *prRes1TPCLvsR = (TProfile*)fi->Get("prRes1TPCLvsR");
  TProfile *prRes1TPCLvsFHCal = (TProfile*)fi->Get("prRes1TPCLvsFHCal");
  TProfile *prRes1TPCRvsFHCal = (TProfile*)fi->Get("prRes1TPCRvsFHCal");
  TGraphErrors *grTPCLR = Converter(prRes1TPCLvsR);
  TGraphErrors *grFHCalTPCL = Converter(prRes1TPCLvsFHCal);
  TGraphErrors *grFHCalTPCR = Converter(prRes1TPCRvsFHCal);
  TCanvas can;
  grFHCalTPCL->Draw("AL");
  grFHCalTPCR->Draw("L");

  grTPCLR->Draw("L");

  can.SaveAs("FHCalwrtFirstHarm.pdf");


}