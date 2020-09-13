{
  TFile *inFile[2];
  inFile[0] = new TFile("PID_MC.root","read");
  inFile[1] = new TFile("PID.root","read");
  TH1F *hEta[2], *hPt[2], *hPhi[2], *hMult[2];
  for (int i=0;i<2;i++){
    hEta[i] = (TH1F*)inFile[i]->Get("hEta");
    hPt[i] = (TH1F*)inFile[i]->Get("hPt");
    hPhi[i] = (TH1F*)inFile[i]->Get("hPhi");
    hMult[i] = (TH1F*)inFile[i]->Get("hMult");
    hEta[i] -> SetLineWidth(2);
    hPt[i] -> SetLineWidth(2);
    hPhi[i] -> SetLineWidth(2);
    hMult[i] -> SetLineWidth(2);
  }
  hEta[0] -> SetTitle("GEANT");
  hPt[0] -> SetTitle("GEANT");
  hPhi[0] -> SetTitle("GEANT");
  hMult[0] -> SetTitle("GEANT");

  hEta[1] -> SetTitle("Reco");
  hPt[1] -> SetTitle("Reco");
  hPhi[1] -> SetTitle("Reco");
  hMult[1] -> SetTitle("Reco");

  hEta[0] -> GetXaxis() ->SetRangeUser(-2.2,2.2);
  hPt[0] -> GetXaxis() ->SetRangeUser(0,3.5);
  // hPhi[1] -> SetLineColor(kRed);
  // hMult[1] -> SetLineColor(kRed);
  gStyle->SetOptStat(0);
  gROOT->SetStyle("Pub");
  hEta[1] -> SetLineColor(kRed);
  hPt[1] -> SetLineColor(kRed);
  hPhi[1] -> SetLineColor(kRed);
  hMult[1] -> SetLineColor(kRed);
  for (int i=0;i<2;i++){
    // hPt[i]->Scale(1./hPt[i]->Integral("width"));
    hEta[i]->Scale(1./hEta[i]->Integral("width"));
    hPhi[i]->Scale(1./hPhi[i]->Integral("width"));
    // hMult[i]->Scale(1./hMult[i]->Integral("width"));
  }
  gStyle->SetOptStat(0);
  auto c1 = new TCanvas("c1", "A ratio example");
  auto rp1 = new TRatioPlot(hEta[0], hEta[1]);
  // c1->SetTicks(0, 1);
  rp1->SetSeparationMargin(0.0);
  rp1->SetLowBottomMargin(0.5);
  rp1->SetLeftMargin(0.17);
  rp1->Draw();
  rp1->GetLowerRefGraph()->GetYaxis()->SetNdivisions(203);
  rp1->GetLowerRefYaxis()->SetTitle("GEANT/RECO");
  rp1->GetLowerRefGraph()->GetYaxis()->SetLabelSize(0.02);
  rp1->GetLowerRefGraph()->SetLineColor(kBlue);
  rp1->GetLowerRefYaxis()->SetTitleOffset(1.);
  rp1->GetLowerRefYaxis()->SetTitleFont(4);
  rp1->GetLowerRefYaxis()->SetTitleSize(0.04);
  rp1->GetLowerRefYaxis()->CenterTitle();
  // rp1->GetLowerRefGraph()->SetMinimum(0);
  // rp1->GetLowerRefGraph()->SetMaximum(5);
  c1->Update();
  TPad *pUp1 = rp1->GetUpperPad();
  TLegend *l1 = pUp1->BuildLegend();
  // TPad *pDown1 = rp1->GetLowerPad();


  auto c2 = new TCanvas("c2", "A ratio example");
  auto rp2 = new TRatioPlot(hPt[0], hPt[1]);
  rp2->SetSeparationMargin(0.0);
  rp2->SetLowBottomMargin(0.5);
  rp2->SetLeftMargin(0.17);
  rp2->Draw();
  c2->Update();  
  TPad *pUp2 = rp2->GetUpperPad();
  TLegend *l2 = pUp2->BuildLegend();
  rp2->GetLowerRefYaxis()->SetNdivisions(302);
  rp2->GetLowerRefYaxis()->SetTitle("GEANT/RECO");
  rp2->GetLowerRefGraph()->GetYaxis()->SetLabelSize(0.02);
  rp2->GetLowerRefGraph()->SetLineColor(kBlue);
  rp2->GetLowerRefYaxis()->SetTitleOffset(1.);
  rp2->GetLowerRefYaxis()->SetTitleFont(4);
  rp2->GetLowerRefYaxis()->SetTitleSize(0.04);
  rp2->GetLowerRefYaxis()->CenterTitle();

  auto c3 = new TCanvas("c3", "A ratio example");
  auto rp3 = new TRatioPlot(hPhi[0], hPhi[1]);
  rp3->SetSeparationMargin(0.0);
  rp3->SetLowBottomMargin(0.5);
  rp3->SetLeftMargin(0.17);
  rp3->Draw();
  c3->Update();  
  TPad *pUp3 = rp3->GetUpperPad();
  TLegend *l3 = pUp3->BuildLegend();
  rp3->GetLowerRefYaxis()->SetNdivisions(302);
  rp3->GetLowerRefYaxis()->SetTitle("GEANT/RECO");
  rp3->GetLowerRefGraph()->GetYaxis()->SetLabelSize(0.02);
  rp3->GetLowerRefGraph()->SetLineColor(kBlue);
  rp3->GetLowerRefYaxis()->SetTitleOffset(1.);
  rp3->GetLowerRefYaxis()->SetTitleFont(4);
  rp3->GetLowerRefYaxis()->SetTitleSize(0.04);
  rp3->GetLowerRefYaxis()->CenterTitle();


  auto c4 = new TCanvas("c4", "A ratio example");
  auto rp4 = new TRatioPlot(hMult[0], hMult[1]);
  rp4->SetSeparationMargin(0.0);
  rp4->SetLowBottomMargin(0.5);
  rp4->SetLeftMargin(0.17);
  rp4->Draw();
  c4->Update();  
  TPad *pUp4 = rp4->GetUpperPad();
  TLegend *l4 = pUp4->BuildLegend();
  rp4->GetLowerRefYaxis()->SetNdivisions(302);
  rp4->GetLowerRefYaxis()->SetTitle("GEANT/RECO");
  // rp4->GetLowerRefGraph()->GetYaxis()->SetLabelSize(0.02);
  rp4->GetLowerRefGraph()->SetLineColor(kBlue);
  // rp4->GetLowerRefYaxis()->SetTitleOffset(1.);
  // rp4->GetLowerRefYaxis()->SetTitleFont(4);
  // rp4->GetLowerRefYaxis()->SetTitleSize(0.04);
  // rp4->GetLowerRefYaxis()->CenterTitle();

}