#define PLOTV2EventPlane
#include "DrawTGraph.C"
#include "../constants.C"
void PlotV2EventPlane(TString inputFileName = "SecondRun_test_rebin.root",
                      TString methodName = "EtaSub",
                      Bool_t saveAsPNG = true,
                      TString outDirName = "pics")
// methodName can be "EtaSub", "SP", "FHCalEP", "LYZEP", "Eta3Sub", "MC"
{

  TFile *fi = TFile::Open(inputFileName.Data());
  TProfile2D *prV2CentEta = (TProfile2D *)fi->FindObjectAny(Form("prV2%svsEta",methodName.Data()));
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  TGraphErrors *gr[4];
  TProfile *tmp[3];
  const std::vector<TString> pidFancyNames = {"h^{+}", "#pi^{+}", "K^{+}", "p", "h^{-}", "#pi^{-}", "K^{-}", "#bar{p}", "h^{#pm}","#pi^{#pm}","K^{#pm}","p(#bar{p})"};
  for (Int_t i=0; i < npid; i++)
  {
    TCanvas c("c","",1200,400);
    c.Divide(3,1);
    TProfile2D *prV2CentPt = (TProfile2D *)fi->FindObjectAny(Form("prV2%svsPt_pid%i",methodName.Data(),i));
    tmp[0] = PlotV2vsPt(prV2CentPt,10,40);// v2 versus pt, 10-40%
    tmp[1] = PlotV2vsPt(prV2CentPt,40,80);// v2 versus pt, 40-80%
    tmp[2] = PlotPtIntegratedV2(prV2CentPt,0.2,3.0);// v2 versus centrality, 0.2<pt<3.0 GeV/c
    for (Int_t j=0; j<3; j++)
    {
      gr[j] = Converter(tmp[j]);
      gr[j]->GetYaxis()-> SetTitle("v_{3}");
      gr[j]->GetYaxis()->SetRangeUser(0., 0.1);
      gr[j]->SetMarkerStyle(20);
      gr[j]->SetMarkerColor(kRed);
      if (j!=2)
      {
        gr[j]->GetXaxis()-> SetTitle("p_{T}, GeV/c");
        gr[j]->GetXaxis()->SetRangeUser(0., 3.5);
      }
    }
    gr[2]->GetXaxis()-> SetTitle("Centrality, %");
    gr[2]->GetXaxis()->SetRangeUser(0., 80);
    gr[0]->SetTitle(Form("v_{3}{%s} of %s at 10-40%%",methodName.Data(),pidFancyNames.at(i).Data()));
    gr[1]->SetTitle(Form("v_{3}{%s} of %s at 40-80%%",methodName.Data(),pidFancyNames.at(i).Data()));
    gr[2]->SetTitle(Form("p_{T}-integrated v_{3}{%s} of %s",methodName.Data(),pidFancyNames.at(i).Data()));
    for (Int_t j=0; j<3; j++)
    {
      c.cd(j+1);
      gr[j]->Draw("AP");
    }
    if (saveAsPNG){
      gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
      c.SaveAs(Form("./%s/Flow_%s_%s.png",outDirName.Data(),methodName.Data(),pidNames.at(i).Data()));
    }

  }
  TCanvas can;
  TProfile *prV2diffEta = PlotV2vsEta(prV2CentEta,10,40);// v2 versus eta of charged hadrons, 0.2<pt<3.5 GeV/c, 10-40%
  gr[3]=Converter(prV2diffEta);
  gr[3]->SetTitle(Form("v_{3}{%s} of charged hadrons, 0.2<#it{p}_{T}^{}< 3.0 GeV/c",methodName.Data()));
  gr[3]->GetYaxis()->SetTitle("v_{3}");
  gr[3]->GetXaxis()->SetTitle("#eta");
  gr[3]->GetYaxis()->SetRangeUser(0., 0.1);
  gr[3]->SetMarkerStyle(20);
  gr[3]->SetMarkerColor(kRed);
  gr[3]->Draw("AP");
  if (saveAsPNG){
    can.SaveAs(Form("./%s/Flow_%s_versus_eta_charged_hadrons.png",outDirName.Data(),methodName.Data()));
  }  


}