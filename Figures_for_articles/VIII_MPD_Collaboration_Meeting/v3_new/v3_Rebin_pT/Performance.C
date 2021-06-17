#include "DrawTGraph.C"
// #include "constants.C"
// vector<TGraphErrors*>*
void Performance()
{
  TString inputName[2] = {"./SecondRun_vHLLEUrQMD_11.5_Model_v3.root",
                          "./SecondRun_vHLLEUrQMD_11.5_Reco_Nhits_16_DCA_3sigma_v3.root"};


  Int_t centlow = 10;
  Int_t centhigh = 40;
  Double_t maxpt = 3.6;    // max pt for differential flow
  Double_t minpt = 0.;     // min pt for differential flow
  Double_t eta_cut = 1.5;  // pseudorapidity acceptance window for flow measurements
  
  const Int_t npt_Rebin = 7; // 0-3.6 GeV/c - number of pT bins
  const Double_t pTBin_Rebin[npt_Rebin + 1] = {0.2, 0.4, 0.6, 1.0, 1.4, 1.8, 2.2, 3.0};

  const int ratioToMethod = 0;
  const Int_t nlevel = 2;
  const Int_t nmethod = 3;
  const Int_t npid = 3;
  int pidCode[npid]={8,9,3};
  TString pidName[npid]={"hadrons","pions","protons"};
  TString pidNameFancy[npid]={"h^{#pm}","#pi^{#pm}","p"};
  TString title[]={"Model","Reco"};
  TString methodName[nmethod] = {"v_{3}{SP}","v_{3}{#Psi_{3,TPC}}","v_{3}{2}"};
  const int markerStyle[] = {24,20,23,22,20,25,28,26,23};
  const float markerSize = 1.2;
  TGraphErrors *graph[npid][nlevel][nmethod];
  TFile *fi[2];
  for (int i = 0; i < nlevel; i++){
    fi[i] = new TFile(inputName[i].Data(),"READ");
    for (int j=0; j<npid; j++)
    {
      for (int k=0; k<2; k++)
      {
        TProfile2D* pr = nullptr;
        if (k==0) pr = (TProfile2D*) fi[i]->Get(Form("SP/prV2SPvsPt_pid%i",pidCode[j]));
        if (k==1) pr = (TProfile2D*) fi[i]->Get(Form("ETASUBEP/prV2EtaSubvsPt_pid%i",pidCode[j]));
        TProfile *tmp = PlotV2vsPt(pr,10,40);
        tmp = (TProfile*) tmp->Rebin(npt_Rebin,Form("%s_Rebin",tmp->GetName()),&pTBin_Rebin[0]);
        graph[j][i][k] = Converter(tmp);
      }
    }
  }

  TString input[nlevel] = {"v3_QCumulant_Model_v3.root.root",
                            "v3_QCumulant_Nhits_16_3_sigma_v3.root.root"};

  for (Int_t i=0;i<nlevel;i++)
  {
    fi[i] = new TFile(input[i].Data(),"READ");
  }

  for (int i = 0; i < npid; i++)
  {
    for (int j=0;j<nlevel;j++)
    {
      graph[i][j][2] = (TGraphErrors*) fi[j]->Get(Form("gr_cent10-40_2_%i",pidCode[i]));
    }
  }

  for (int id = 0; id < npid; id++)
  {
    for (int i=0; i<nlevel; i++)
    {
      for (int k=0; k<nmethod; k++)
      {
      // graph[id][i]->RemovePoint(0);
      graph[id][i][k]->SetTitle("");
      graph[id][i][k]->SetMarkerStyle(markerStyle[i]);
      graph[id][i][k]->SetMarkerSize(markerSize);
      graph[id][i][k]->GetXaxis()->SetTitle("p_{T}, GeV/c");
      graph[id][i][k]->GetYaxis()->SetTitle("v_{3}");
      graph[id][i][k]->GetYaxis()->SetRangeUser(0., 0.07);
      graph[id][i][k]->GetXaxis()->SetLimits(-0.05, 3.1);
      graph[id][i][k]->GetXaxis()->SetNdivisions(506);
      graph[id][i][k]->GetYaxis()->SetNdivisions(506);
      graph[id][i][k]->GetYaxis()->SetLabelSize(.06);
      graph[id][i][k]->GetYaxis()->SetTitleSize(.07);
      graph[id][i][k]->GetXaxis()->SetLabelSize(.06);
      graph[id][i][k]->GetXaxis()->SetTitleSize(.07);

      graph[id][i][k]->SetDrawOption("P PLC PMC");
      }
    }
  }
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPalette(kDarkRainBow);
  // gROOT->SetStyle("Pub");
  for (int id = 0; id < npid; id++)
  {
    TCanvas c("","",1200,400);
    c.SetLeftMargin(0.16);
    c.SetRightMargin(0.01);
    c.SetBottomMargin(0.15);
    c.Divide(3,1,0,0);
    for (int i=0;i<3;i++)
    {
      c.cd(i+1);
      // for (int j=0;j<nlevel;j++)
      // {
        graph[id][0][i]->Draw("AP PLC PMC");
        graph[id][1][i]->Draw("P PLC PMC");
      // }
      TLatex tex;
      tex.SetTextFont(42);
      // tex.SetTextAlign(13);
      tex.SetTextSize(0.07);
      if (i==0) tex.DrawLatex(0.1,0.063,"vHLLE+UrQMD, Au+Au");
      if (i==1) tex.DrawLatex(0.1,0.063,Form("#sqrt{s_{NN}} = 11.5 GeV, 10-40%%, %s",pidNameFancy[id].Data()));
      if (i==2) tex.DrawLatex(0.1,0.063,"open - true, closed - reco");
      tex.DrawLatex(0.1,0.055,methodName[i].Data());
    }
    c.SaveAs(Form("Performance_v3_%i%i_Model_vs_Reco_%s.pdf",centlow,centhigh,pidName[id].Data()));
  }
}