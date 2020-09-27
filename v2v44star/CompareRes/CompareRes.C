void CompareRes(){
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmodel = 3; // Star data, vHLLE+UrQMD, UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const int ncent = 8;
  const float mincent = -1;
  const float maxcent = 63.;
  const float maxRes2 = 0.55;
  const float minRes2 = 0.0;
  const float leg_coordinate[4]={0.05,0.6,0.35,0.99};
  const float labelSize = 0.06;
  // const TString leg_header[2] = {"UrQMD,20-30%","SMASH,20-30%"};
  const TString leg_header[nenergy] = {"7.7 GeV","11.5 GeV"};
  TString energy[nenergy]={"7.7","11.5"};
  TString method[nmethod]={"v_2{2}","v_2{4}","v_2{#eta-sub}","v_2{2,|#Delta#eta>0.1|}"};
  TString model[nmodel]={"vHLLE+UrQMD","UrQMD","SMASH"};
  TFile *input[nenergy][nmodel];
  TProfile *prRes;
  TGraphErrors *grRes[nenergy][nmodel];
  double res2[ncent];
  double res2e[ncent];
  double cent_bin[ncent]={5,15,25,35,45,55,65,75};
  double cent_bin_e[ncent]={0};
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      input[ien][imod] = new TFile(Form("%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      for (int icent=0;icent<ncent;icent++){
        prRes = (TProfile*)input[ien][imod]->Get(Form("HRes_%i",icent));
        res2[icent] = sqrt(prRes -> GetBinContent(1));
        // res2[icent] = prRes -> GetBinContent(1);
        res2e[icent] = prRes -> GetBinError(1);
      }
      grRes[ien][imod] = new TGraphErrors(ncent,cent_bin,res2,cent_bin_e,res2e);
      grRes[ien][imod] -> SetTitle(model[imod].Data());
    }

  

    // grRes[ien][0] -> SetMarkerStyle(kFullCircle);
    // grRes[ien][1] -> SetMarkerStyle(kFullCircle);
    grRes[ien][2] -> SetMarkerColor(kBlue);
    grRes[ien][2] -> SetLineColor(kBlue);
    grRes[ien][0] -> SetMarkerColor(kRed);
    grRes[ien][0] -> SetLineColor(kRed);
    grRes[ien][1] -> SetMarkerColor(kGreen);
    grRes[ien][1] -> SetLineColor(kGreen);

  }
  for (int imod=0;imod<nmodel;imod++){
    // grRes[0][imod] -> SetMarkerColor(kRed);
    // grRes[0][imod] -> SetLineColor(kRed);
    // grRes[1][imod] -> SetMarkerColor(kGreen);
    // grRes[1][imod] -> SetLineColor(kGreen);
    // grRes[2][imod] -> SetMarkerColor(kBlue);
    // grRes[2][imod] -> SetLineColor(kBlue);
    grRes[0][imod] -> SetMarkerStyle(kFullCircle);
    grRes[1][imod] -> SetMarkerStyle(kFullCircle);
    // grRes[2][imod] -> SetMarkerStyle(kFullCircle);
    for (int ien=0;ien<nenergy;ien++){
      grRes[ien][imod]->SetMarkerSize(1.5);
    }
  }

  // cout << "error from here" << endl;
  TCanvas *can = new TCanvas("can","can",200,10,1600,650);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.17);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(2,1,0,0);
  //=================================================================================
  can->cd(1);
  TH2F *h1 = new TH2F("h1",";centrality [%];Res#Psi_{2}",1,mincent,maxcent,1,minRes2,maxRes2);
  h1->GetXaxis()->SetLabelSize(labelSize);
  h1->GetYaxis()->SetLabelSize(labelSize);
  h1->GetXaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetNdivisions(504);
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->Draw();
  TLegend *leg_pt = new TLegend(leg_coordinate[0]+0.4,leg_coordinate[1]+0.2,leg_coordinate[2],leg_coordinate[3]);
  leg_pt->SetBorderSize(0);
  leg_pt->SetHeader(leg_header[0].Data(),"C");
  
  leg_pt->SetTextSize(0.05);

  for (int imod=0;imod<nmodel;imod++){
    // grRes[0][imod]->Draw("P");
    leg_pt->AddEntry(grRes[1][imod],Form("%s",grRes[1][imod]->GetTitle()),"p");
  }
  leg_pt->Draw();
  for (int imod=0;imod<nmodel;imod++){
    grRes[0][imod]->Draw("P");
  }

  leg_pt->Draw();
  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(mincent,1.,maxcent,1.);
  //=================================================================================
  can->cd(2);
  TH2F *h2 = new TH2F("h2",";centrality [%];Res#Psi_{2}",1,mincent,maxcent,1,minRes2,maxRes2);
  h2->GetXaxis()->SetLabelSize(labelSize);
  h2->GetYaxis()->SetLabelSize(labelSize);
  h2->GetXaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetNdivisions(504);
  h2->GetYaxis()->SetTitleOffset(0.5);
  h2->Draw();
  TLegend *leg_pt2 = new TLegend(leg_coordinate[0],leg_coordinate[1]+0.2,leg_coordinate[2],leg_coordinate[3]);
  leg_pt2->SetBorderSize(0);
  leg_pt2->SetHeader(leg_header[1].Data(),"C");
  leg_pt2->SetTextSize(0.05);

  for (int imod=0;imod<nmodel;imod++){
    grRes[1][imod]->Draw("P");
    leg_pt2->AddEntry("","","");
  }
  leg_pt2->Draw();
  lineOne.DrawLine(mincent,1.,maxcent,1.);

  can->SaveAs("Res2.eps");


}