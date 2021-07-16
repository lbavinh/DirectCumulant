void Ratio_v24_over_v22()
{
  const int ncent = 8;
  double cent[ncent] = {7.5, 15, 25, 35, 45, 55, 65, 75};
  double err_old[ncent] = {0.0129058,
  0.00360814,
  0.00288657,
  0.00418879,
  0.00935042,
  0.0294775,
  0.124009,
  0.402933};
  double err_with_cov[ncent] = {0.0128372,
  0.003544,
  0.00281938,
  0.00413956,
  0.00932754,
  0.0294705,
  0.124008,
  0.402923};
  double err_cochran[ncent]={0.0119366,
  0.00303364,
  0.00240212,
  0.0034363,
  0.00730257,
  0.0203577,
  0.0715017,
  0.086764};
  double old_div_cochran[ncent];
  double cov_div_cochran[ncent];
  for (int i=0;i<ncent;i++)
  {
    old_div_cochran[i] = err_old[i]/err_cochran[i];
    cov_div_cochran[i] = err_with_cov[i]/err_cochran[i];
  }
  TCanvas c;
  TGraph *gr1 = new TGraph(ncent,cent,old_div_cochran);
  TGraph *gr2 = new TGraph(ncent,cent,cov_div_cochran);
  gr1->SetTitle("");
  gr1->GetYaxis()->SetTitle("\\sigma/\\sigma_{Cochran}^{v_{2}\\{4\\}/v_{2}\\{2,sub-event\\}}");
  gr1->GetXaxis()->SetTitle("Centrality, %");
  gr1->GetYaxis()->SetRangeUser(0.8,2.);
  gr1->GetYaxis()->SetNdivisions(508);
  gr1->GetXaxis()->SetRangeUser(0,80);
  gr1->SetMarkerStyle(20);
  gr2->SetMarkerStyle(22);
  gr1->SetMarkerColor(2);
  gr2->SetMarkerColor(1);
  gr1->SetMarkerSize(1.2);
  gr2->SetMarkerSize(1.2);  
  gr1->Draw("AP");
  gr2->Draw("P");
  TLegend *leg = new TLegend(0.2,0.6,0.45,0.85);
  leg->SetBorderSize(0);
  // leg->SetHeader("","C");
  leg->SetTextSize(0.05);
  leg->AddEntry(gr1,"#sigma_{stat.propagation}/#sigma_{Cochran}","p");
  leg->AddEntry(gr2,"#sigma_{covariance}/#sigma_{Cochran}","p");
  leg->Draw();

  TLine line;
	line.SetLineStyle(2);
  line.SetLineWidth(2.);
  line.SetLineColor(kAzure+2);
  line.DrawLine(0,1.00,80,1.00);
  c.SaveAs("Ratio_v24_over_v22.png");
}