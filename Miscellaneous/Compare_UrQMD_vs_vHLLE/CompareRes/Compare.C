void Compare()
{
  TFile *fi[2]; TProfile *pr[2];
  fi[0] = new TFile("UrQMD_11.5GeV.root","READ");
  fi[1] = new TFile("vHLLEUrQMD_11.5GeV.root","READ");
  const int ncent = 9;
  Double_t res[3][ncent], resErr[3][ncent];
  Double_t err[ncent]={0.};
  Double_t cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
  TGraphErrors *gr[3];
  for (int i=0; i<2; i++)
  {
    for (int ic=0;ic<ncent;ic++)
    {
      TProfile *pr = (TProfile*)fi[i]->Get(Form("HRes_%i",ic));
      res[i][ic] = sqrt(pr->GetBinContent(1));
      resErr[i][ic] = pr->GetBinError(1)/(2.*res[i][ic]);
    }
    gr[i] = new TGraphErrors(ncent,cent,res[i],err,err);

  }
  Double_t STAR_11GeV_res2[9]={0.208805,	0.304974,	0.382106,	0.401141,	0.365707,	0.292365,	0.209263,	0.141614,	0.108964};
  Double_t STAR_11GeV_res2_err[9]={0.00430218,	0.00296599,	0.00161536,	0.00151679,	0.0016682,	0.00207178,	0.00288927,	0.00442509,	0.00691686};
  gr[2] = new TGraphErrors(ncent,cent,STAR_11GeV_res2,err,STAR_11GeV_res2_err);

  for (Int_t i=0;i<3;i++)
  {
    gr[i]->SetTitle(";Centrality, %;R_{2}{#Psi_{2}}");
    gr[i]->GetYaxis()->SetRangeUser(0.,0.5);
  }
  gr[0]->SetLineColor(kRed+2);
  gr[0]->SetMarkerColor(kRed+2);
  gr[1]->SetLineColor(kBlue+2);
  gr[1]->SetMarkerColor(kBlue+2);
  gr[2]->SetLineColor(kGreen+2);
  gr[2]->SetMarkerColor(kGreen+2);
  gr[0]->SetMarkerStyle(20);
  gr[1]->SetMarkerStyle(22);
  gr[2]->SetMarkerStyle(26);
  TCanvas c;
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  gr[0]->SetTitle("Au+Au #sqrt{s_{NN}} = 11.5 GeV, h^{#pm}, |#eta|<1.5, 0.2<p_{T}<3.0 GeV/c");
  gr[0]->Draw("AP");
  gr[1]->Draw("P");
  gr[2]->Draw("P");
  TLegend *leg = new TLegend(0.6,0.6,0.8,0.8);
  leg->SetBorderSize(0);
  leg->AddEntry(gr[0],"UrQMD","p");
  leg->AddEntry(gr[1],"vHLLE+UrQMD","p");
  leg->AddEntry(gr[2],"STAR","p");
  leg->Draw();
  
  c.SaveAs("CompareRes.png");


}