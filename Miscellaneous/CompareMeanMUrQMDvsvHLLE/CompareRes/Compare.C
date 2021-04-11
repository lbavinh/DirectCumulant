void Compare()
{
  TFile *fi[2]; TProfile *pr[2];
  fi[0] = new TFile("UrQMD_11.5GeV.root","READ");
  fi[1] = new TFile("vHLLEUrQMD_11.5GeV.root","READ");
  const int ncent = 9;
  double res[2][ncent];
  double err[ncent]={0.};
  double cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
  TGraphErrors *gr[2];
  for (int i=0; i<2; i++)
  {
    for (int ic=0;ic<ncent;ic++)
    {
      TProfile *pr = (TProfile*)fi[i]->Get(Form("HRes_%i",ic));
      res[i][ic] = sqrt(pr->GetBinContent(1));
      cout << sqrt(pr->GetBinContent(1)) << endl;
    }
    gr[i] = new TGraphErrors(ncent,cent,res[i],err,err);
    gr[i]->SetTitle(";Centrality, %;R_{2}{#Psi_{2}}");
    gr[i]->GetYaxis()->SetRangeUser(0.,0.5);
  }
  gr[0]->SetLineColor(kRed);
  gr[1]->SetLineColor(kBlue);
  gr[0]->SetMarkerColor(kRed);
  gr[1]->SetMarkerColor(kBlue);
  gr[0]->SetMarkerStyle(20);
  gr[1]->SetMarkerStyle(22);
  TCanvas c;
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  gr[0]->SetTitle("Au+Au #sqrt{s_{NN}} = 11.5 GeV, h^{#pm}, |#eta|<1.5, 0.2<p_{T}<3.0 GeV/c");
  gr[0]->Draw("AP");
  gr[1]->Draw("P");
  TLegend *leg = new TLegend(0.6,0.6,0.8,0.8);
  leg->SetBorderSize(0);
  leg->AddEntry(gr[0],"UrQMD","p");
  leg->AddEntry(gr[1],"vHLLE+UrQMD","p");
  leg->Draw();
  
  c.SaveAs("CompareRes.png");


}