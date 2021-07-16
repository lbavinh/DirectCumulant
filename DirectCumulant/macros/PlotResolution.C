#define PLOTRESOLUTION
#include "DrawTGraph.C"
#include "../constants.C"
void PlotResolution(TString inputFileName = "SecondRun.root",
                    TString methodName = "MCEventPlane",
                    Bool_t saveAsPNG = true,
                    TString outDirName = "pics")
// methodName can be "EtaSub", "SP", "FHCalEP", "LYZEP", "Eta3Sub", "MCEventPlane"
{

  TFile *fi = TFile::Open(inputFileName.Data());
  TProfile *prRes = (TProfile *)fi->FindObjectAny(Form("prRes%s",methodName.Data()));
  if (!prRes) { cerr << "prRes not found!" << endl; return; }
  Double_t centrality[ncent], centralityErr[ncent] = {0.};
  Double_t res[ncent], resErr[ncent];
  for (Int_t ic = 0; ic<ncent; ic++)
  {
    centrality[ic] = prRes->GetBinCenter(ic+1);
    if (methodName=="EtaSub") 
    {
      res[ic] = TMath::Sqrt(prRes->GetBinContent(ic+1));
      resErr[ic] = prRes->GetBinError(ic+1)/(2.*res[ic]);
    }
    else if (methodName=="MCEventPlane") 
    {
      res[ic] = prRes->GetBinContent(ic+1);
      resErr[ic] = prRes->GetBinError(ic+1);
    }
    else return; // Need to finish this code for other EP methods
  }

  TCanvas can;
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  TGraphErrors *gr = new TGraphErrors(ncent, centrality, res, centralityErr, resErr);
  gr->SetTitle(Form("Resolution of %s method",methodName.Data()));
  gr->GetYaxis()->SetTitle("Res(#Psi_{2})");
  gr->GetXaxis()->SetTitle("Centrality, %");
  gr->GetYaxis()->SetRangeUser(0., 1.);
  gr->GetXaxis()->SetLimits(0., 80.);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kRed);
  gr->Draw("AP");
  if (saveAsPNG){
    gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
    can.SaveAs(Form("./%s/Resolution_versus_Centrality_%s.png",outDirName.Data(),methodName.Data()));
  }  


}