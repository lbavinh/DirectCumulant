void Compare()
{
  TFile *fi[2]; TProfile *pr[2];
  fi[0] = new TFile("FirstRun_UrQMD_11.5_v3_ETASUB.root","READ");
  fi[1] = new TFile("FirstRun_vHLLEUrQMD_11.5_Model_v3.root","READ");
  const int ncent = 9;
  Double_t res[3][ncent], resErr[3][ncent];
  Double_t err[ncent]={0.};
  Double_t cent[ncent] = {2.5,7.5,15,25,35,45,55,65,75};
  TGraphErrors *gr[3];
  for (int i=0; i<2; i++)
  {
    TProfile *pr = (TProfile*)fi[i]->Get(Form("ETASUBEP/prResEtaSub"));
    for (int ic=0;ic<ncent;ic++)
    {
      res[i][ic] = TMath::Sqrt(pr->GetBinContent(ic+1));
      resErr[i][ic] = pr->GetBinError(ic+1)/(2.*res[i][ic]);
    }
    gr[i] = new TGraphErrors(ncent,cent,res[i],err,resErr[i]);
  }


  Double_t STAR_11GeV_res3[9]={0.14205,	0.144407,	0.13707,	0.117446,	0.0891094,	0.0632447,	0.0406928,	0.01682,	0.0217658};
  Double_t STAR_11GeV_res3_err[9]={0.00632713,	0.00629676,	0.00456954,	0.00527912,	0.00693575,	0.00962678,	0.0148815,	0.0372423,	0.0346214};
  gr[2] = new TGraphErrors(ncent,cent,STAR_11GeV_res3,err,STAR_11GeV_res3_err);
  for (Int_t i=0;i<3;i++)
  {
    gr[i]->SetTitle(";Centrality, %;R_{3}{#Psi_{3}}");
    gr[i]->GetYaxis()->SetRangeUser(0.,0.2);
  }
  gr[0]->SetLineColor(kRed+2);
  gr[0]->SetMarkerColor(kRed+2);
  gr[1]->SetLineColor(kBlue+2);
  gr[1]->SetMarkerColor(kBlue+2);
  gr[2]->SetLineColor(kGreen+2);
  gr[2]->SetMarkerColor(kGreen+2);
  gr[0]->SetMarkerStyle(20);
  gr[1]->SetMarkerStyle(22);
  gr[2]->SetMarkerStyle(23);
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
  
  c.SaveAs("CompareRes3.png");


}