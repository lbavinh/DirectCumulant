void Compare()
{
  TFile *fi[2];
  fi[0] = new TFile("v2_UrQMD_11.5GeV.root","READ");
  fi[1] = new TFile("v2_vHLLEUrQMD_11.5GeV.root","READ");


  const int nmethod = 3;
  // TString methodName[nmethod] = {"v_{2}{4}","v_{2}{#Psi_{2,TPC}}","v_{2}{2}"};
  TString methodName[nmethod] = {"v24","v2EP","v22"};
  for (int j=0;j<nmethod;j++)
  {
    TGraphErrors *gr[2];
    for (int i=0;i<2;i++)
    {
      gr[i] = dynamic_cast<TGraphErrors*>(fi[i]->Get(Form("gr_cent10-40_%i_3",j+1)));
      if (!gr[i]) return;
      gr[i]->GetYaxis()->SetRangeUser(0.,0.25);
      gr[i]->GetXaxis()->SetLimits(0.,3.5);
    }
    gr[0]->SetLineColor(kRed+1);
    gr[1]->SetLineColor(kBlue+1);
    gr[0]->SetMarkerColor(kRed+1);
    gr[1]->SetMarkerColor(kBlue+1);
    gr[0]->SetMarkerStyle(20);
    gr[1]->SetMarkerStyle(24);
    gr[0]->SetMarkerSize(1.);
    gr[1]->SetMarkerSize(1.);
    TCanvas c;
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    gr[1]->SetTitle("Au+Au #sqrt{s_{NN}} = 11.5 GeV, 10-40%, proton"); // #pi^{#pm}
    gr[1]->Draw("AP");
    gr[0]->Draw("P");
    TLegend *leg = new TLegend(0.15,0.7,0.3,0.8);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    leg->AddEntry(gr[0],"UrQMD","p");
    leg->AddEntry(gr[1],"vHLLE+UrQMD","p");
    leg->Draw();
    c.SaveAs(Form("Compare_v2_proton_%s.png",methodName[j].Data()));
  }


}