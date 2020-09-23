void Compare_fluctuation_v2_cent_with_STAR(){
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmodel = 4; // Star data, vHLLE+UrQMD, UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float minpt = 0.;
  const float maxpt = 74.;
  const float maxV2Ratio = 1.33;
  const float minV2Ratio = 0.55;
  const float leg_coordinate[4]={0.28,0.7,0.35,0.99};
  const float labelSize = 0.06;
  // const TString leg_header[2] = {"UrQMD,20-30%","SMASH,20-30%"};
  const TString leg_header[nenergy] = {"7.7 GeV","11.5 GeV"};
  TString energy[nenergy]={"7.7","11.5"};
  TString method[nmethod]={"v_2{2}","v_2{4}","v_2{#eta-sub}","v_2{2,|#Delta#eta>0.1|}"};
  TString model[nmodel]={"STAR data","vHLLE+UrQMD","UrQMD","SMASH"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  
  TGraphErrors *grRatioV2[nenergy][nmodel];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      input[ien][imod] = new TFile(Form("v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v2(eta-sub), v22(eta-gap)
        grV2[ien][imod][imeth] = (TGraphErrors*)input[ien][imod]->Get(Form("grRF_%i_0",imeth)); // "_0" - Charged Hadrons
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod], *vy_gr[nenergy][nmodel][nmethod], *ex_gr[nenergy][nmodel][nmethod], *ey_gr[nenergy][nmodel][nmethod];
  Int_t nbins[nenergy][nmodel][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      for (int imeth=0;imeth<nmethod;imeth++){
        // Read points
        vx_gr[ien][imod][imeth]=(Double_t*)grV2[ien][imod][imeth]->GetX();
        vy_gr[ien][imod][imeth]=(Double_t*)grV2[ien][imod][imeth]->GetY();

        // Read errors
        ex_gr[ien][imod][imeth]=(Double_t*)grV2[ien][imod][imeth]->GetEX();
        ey_gr[ien][imod][imeth]=(Double_t*)grV2[ien][imod][imeth]->GetEY();

        nbins[ien][imod][imeth]=(Int_t) grV2[ien][imod][imeth]->GetN();
      }
    }
  }
  std::vector<Double_t> vRatioV22GappedV24[nenergy][nmodel], vRatioV22GappedV24Err[nenergy][nmodel];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      for (int i=0;i<nbins[ien][imod][3];i++){
        Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][0][i];
        Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][0][i]/vy_gr[ien][imod][0][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
        vRatioV22GappedV24[ien][imod].push_back(ratio);
        vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
      }
      grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);
      grRatioV2[ien][imod] -> SetTitle(Form("%s;centrality [%];v_{2}{4}/v_{2}{2}",model[imod].Data()));
      
    }
    // grRatioV2[ien][0] -> SetMarkerStyle(kFullCircle);
    // grRatioV2[ien][1] -> SetMarkerStyle(kFullCircle);

    grRatioV2[ien][1] -> SetMarkerColor(kGreen);
    grRatioV2[ien][1] -> SetLineColor(kGreen);
    grRatioV2[ien][2] -> SetMarkerColor(kBlue);
    grRatioV2[ien][2] -> SetLineColor(kBlue);
    grRatioV2[ien][3] -> SetMarkerColor(kRed);
    grRatioV2[ien][3] -> SetLineColor(kRed);
  }
  for (int imod=1;imod<nmodel;imod++){
    // grRatioV2[0][imod] -> SetMarkerColor(kRed);
    // grRatioV2[0][imod] -> SetLineColor(kRed);
    // grRatioV2[1][imod] -> SetMarkerColor(kGreen);
    // grRatioV2[1][imod] -> SetLineColor(kGreen);
    // grRatioV2[2][imod] -> SetMarkerColor(kBlue);
    // grRatioV2[2][imod] -> SetLineColor(kBlue);

    grRatioV2[0][imod] -> SetMarkerStyle(kFullCircle);
    grRatioV2[1][imod] -> SetMarkerStyle(kFullCircle);
    // grRatioV2[3][imod] -> SetMarkerStyle(kFullCircle);
    for (int ien=0;ien<nenergy;ien++){
      grRatioV2[ien][imod]->SetMarkerSize(1.5);
    }
  }
  // cout << "error from here" << endl;
  TString energySTAR[nenergy]={"77","115"};
  TGraphErrors *grV2Star[nenergy][nmethod-1]; // v22, v24, v2etasub
  TGraphErrors *grRatioV2STAR[nenergy]; // "7.7","11.5","19.6"
  for (int iener=0;iener<nenergy;iener++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./v2methods%sCent.txt",energySTAR[iener].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file summary1.txt !\n"<< endl;
      fflush(stdin);
      return;
    }
    int npt = 9;
    double pt[npt], v2eta[npt], v22[npt], v24[npt];
    double pte[npt], v2etae[npt], v22e[npt], v24e[npt];
    double ratiov24v22[npt], ratiov24v22e[npt];
    for (int ipt=0; ipt<npt; ipt++) {
      float  ppt,s2,  s2e,  s2eta,  s2etae,    s22,s22e,s24,s24e,s2b, s2be;
      //    cent,v2EP,v2EPe,v2etasub,v2etasube,v22,v22e,v24,v24e,v2bbc,v2bbce
      fscanf(fp1, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&ppt,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

      pt[ipt]     = ppt;
      v2eta[ipt]  = s2eta;
      v2etae[ipt] = s2etae;
      v22[ipt]    = s22;
      v22e[ipt]   = s22e;
      v24[ipt]    = s24;
      v24e[ipt]   = s24e;
      pte[ipt]    = 0.;
      Double_t ratio = s24/s22;
      Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(s24e/s24,2)+TMath::Power(s22e/s22,2)));
      ratiov24v22[ipt] = ratio;
      ratiov24v22e[ipt] = ratioErr;
    }
    // STAR
    // grV2Star[iener][0] = new TGraphErrors(npt,pt,v22,pte,v22e); // v22
    // grV2Star[iener][1] = new TGraphErrors(npt,pt,v24,pte,v24e); // v24
    // grV2Star[iener][2] = new TGraphErrors(npt,pt,v2eta,pte,v2etae); // v2etasub
    grRatioV2[iener][0] = new TGraphErrors(npt,pt,ratiov24v22,pte,ratiov24v22e);
    grRatioV2[iener][0] -> SetTitle(Form("STAR data;centrality [%];v_{2}{4}/v_{2}{2}"));
    grRatioV2[iener][0] -> SetMarkerStyle(kOpenStar);
    grRatioV2[iener][0] -> SetMarkerSize(1.8);
    grRatioV2[iener][0] -> SetMarkerColor(kBlack);
    grRatioV2[iener][0] -> SetLineColor(kBlack);
    // for (int imethod=0;imethod<nmethod-1;imethod++){
    //   grV2Star[imethod][imethod]->SetTitle(Form("STAR %sGeV;p_{T}, GeV/c;%s",energySTAR[iener].Data(),method[imethod].Data()));
    // }
    // delete fp1;
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
  TH2F *h1 = new TH2F("h1",";centrality [%];v_{2}{4}/v_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h1->GetXaxis()->SetLabelSize(labelSize);
  h1->GetYaxis()->SetLabelSize(labelSize);
  h1->GetXaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetNdivisions(504);
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->Draw();
  TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt->SetBorderSize(0);
  leg_pt->SetHeader(leg_header[0].Data(),"C");

  
  for (int imod=0;imod<nmodel;imod++){
    // grRatioV2[0][imod]->Draw("P");
    leg_pt->AddEntry(grRatioV2[0][imod],Form("%s",grRatioV2[0][imod]->GetTitle()),"p");
    leg_pt->SetTextSize(0.05);
  }
  leg_pt->Draw();
  for (int imod=0;imod<nmodel;imod++){
    grRatioV2[0][imod]->Draw("P");
  }
  // leg_pt->AddEntry(grRatioV2STAR[0],Form("%s",grRatioV2STAR[0]->GetTitle()),"p");
  // grRatioV2STAR[0]->Draw("P");

  leg_pt->Draw();
  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  //=================================================================================
  can->cd(2);
  TH2F *h2 = new TH2F("h2",";centrality [%];v_{2}{4}/v_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h2->GetXaxis()->SetLabelSize(labelSize);
  h2->GetYaxis()->SetLabelSize(labelSize);
  h2->GetXaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetNdivisions(504);
  h2->GetYaxis()->SetTitleOffset(0.5);
  h2->Draw();
  TLegend *leg_pt2 = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt2->SetBorderSize(0);
  leg_pt2->SetHeader(leg_header[1].Data(),"C");
  leg_pt2->SetTextSize(0.05);
  for (int imod=0;imod<nmodel;imod++){
    grRatioV2[1][imod]->Draw("P");
    // leg_pt2->AddEntry(grRatioV2[1][imod],Form("%s",grRatioV2[1][imod]->GetTitle()),"p");
  }
  // leg_pt2->AddEntry(grRatioV2STAR[0],Form("%s",grRatioV2STAR[0]->GetTitle()),"p");
  // grRatioV2STAR[0]->Draw("P");

  leg_pt2->Draw();
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  // //=================================================================================
  // can->cd(3);
  // TH2F *h3 = new TH2F("h3",";centrality [%];v_{2}{4}/v_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  // h3->GetXaxis()->SetLabelSize(labelSize);
  // h3->GetYaxis()->SetLabelSize(labelSize);
  // h3->GetXaxis()->SetTitleSize(labelSize);
  // h3->GetYaxis()->SetTitleSize(labelSize);
  // h3->GetYaxis()->SetNdivisions(504);
  // h3->GetYaxis()->SetTitleOffset(0.5);
  // h3->Draw();
  // TLegend *leg_pt3 = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  // leg_pt3->SetBorderSize(0);
  // leg_pt3->SetHeader(leg_header[2].Data(),"C");
  // leg_pt3->SetTextSize(0.05);
  // for (int imod=0;imod<nmodel;imod++){
  //   grRatioV2[2][imod]->Draw("P");
  //   // leg_pt3->AddEntry(grRatioV2[2][imod],Form("%s",grRatioV2[2][imod]->GetTitle()),"p");
  // }
  // // leg_pt3->AddEntry(grRatioV2STAR[1],Form("%s",grRatioV2STAR[1]->GetTitle()),"p");
  // grRatioV2STAR[1]->Draw("P");

  // leg_pt3->Draw();
  // lineOne.DrawLine(minpt,1.,maxpt,1.);
  // //=================================================================================
  // can->cd(4);
  // TH2F *h4 = new TH2F("h4",";centrality [%];v_{2}{4}/v_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  // h4->GetXaxis()->SetLabelSize(labelSize);
  // h4->GetYaxis()->SetLabelSize(labelSize);
  // h4->GetXaxis()->SetTitleSize(labelSize);
  // h4->GetYaxis()->SetTitleSize(labelSize);
  // h4->GetYaxis()->SetNdivisions(504);
  // h4->GetYaxis()->SetTitleOffset(0.5);
  // h4->Draw();
  // TLegend *leg_pt4 = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  // leg_pt4->SetBorderSize(0);
  // leg_pt4->SetHeader(leg_header[3].Data(),"C");
  // leg_pt4->SetTextSize(0.05);
  // for (int imod=0;imod<nmodel;imod++){
  //   // grRatioV2[3][imod]->Draw("P");
  //   // leg_pt4->AddEntry(grRatioV2[3][imod],Form("%s",grRatioV2[3][imod]->GetTitle()),"p");
  // }
  // // leg_pt4->AddEntry(grRatioV2STAR[2],Form("%s",grRatioV2STAR[2]->GetTitle()),"p");
  // grRatioV2STAR[2]->Draw("P");

  // leg_pt4->Draw();
  // lineOne.DrawLine(minpt,1.,maxpt,1.);
  can->SaveAs("ratiov2cent_vsSTAR.pdf");


}