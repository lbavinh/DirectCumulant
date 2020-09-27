void CompareV2PT(){
  // const
  const int nenergy = 3; // 4.5, 7.7, 11.5 GeV
  const int nmodel = 3; // vHLLE+UrQMD, UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const int npid = 4; // CH, pions, kaons, protons
  const float minpt = -0.05;
  const float maxpt = 2.36;
  const float maxV2Ratio = 1.58;
  const float minV2Ratio = 0.42;
  const float leg_coordinate[4]={0.28,0.7,0.6,0.99};
  const float labelSize = 0.05;
  // flags
  const int method = 3; // compare v2{4} with: 0: v22, 2: v2{eta-sub}, 3: v2{2,eta-gap}
  const int pid = 1; // v2 for: 0: CH; 1: Pions; 2: Kaons; 3: (Anti)protons
  // some stuffs
  TString energy[nenergy]={"4.5","7.7","11.5"};
  TString leg_header[nenergy] = {"4.5 GeV","7.7 GeV","11.5 GeV"};
  TString model[nmodel]={"vHLLE+UrQMD","UrQMD","SMASH"};
  TString grFancyTitle[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{#eta-sub}","v_{2}{2,|#Delta#eta|>0.1}"};
  TString grTitle[nmethod]={"v22","v24","v2etasub","v22etagap"};
  TString pidFancyNames[npid] = {"Charged hadrons", "Pions", "Kaons", "(Anti)protons"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  TGraphErrors *grRatioV2[nenergy][nmodel];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (imod==0 && ien==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
      input[ien][imod] = new TFile(Form("v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      for (int imeth=0;imeth<nmethod;imeth++){ // v24 = 1; v22(eta-gap) = 3
        grV2[ien][imod][imeth] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_cent10-40_%i_%i",imeth,pid)); // "_0" - Charged Hadrons
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod], *vy_gr[nenergy][nmodel][nmethod], *ex_gr[nenergy][nmodel][nmethod], *ey_gr[nenergy][nmodel][nmethod];
  Int_t nbins[nenergy][nmodel][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (imod==0 && ien==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
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
    for (int imod=0;imod<nmodel;imod++){
      if (imod==0 && ien==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
      for (int i=0;i<nbins[ien][imod][3];i++){
        Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][method][i];
        Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][method][i]/vy_gr[ien][imod][method][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
        vRatioV22GappedV24[ien][imod].push_back(ratio);
        vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
      }
      grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);
      grRatioV2[ien][imod] -> SetTitle(Form("%s;p_{T} [GeV/c];v_{2}{4}/%s",model[imod].Data(),grFancyTitle[method].Data()));
      
    }
    
    grRatioV2[ien][1] -> SetMarkerColor(kBlue);
    grRatioV2[ien][1] -> SetLineColor(kBlue);
    grRatioV2[ien][2] -> SetMarkerColor(kGreen);
    grRatioV2[ien][2] -> SetLineColor(kGreen);
    if (ien==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
    grRatioV2[ien][0] -> SetMarkerColor(kRed);
    grRatioV2[ien][0] -> SetLineColor(kRed);
  }
  for (int imod=0;imod<nmodel;imod++){
    grRatioV2[1][imod] -> SetMarkerStyle(kFullCircle);
    grRatioV2[2][imod] -> SetMarkerStyle(kFullCircle);
    if (imod==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
    grRatioV2[0][imod] -> SetMarkerStyle(kFullCircle);
  }
  for (int imod=0;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      if (imod==0 && ien==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
      grRatioV2[ien][imod]->SetMarkerSize(1.5);
    }
  }
  TCanvas *can = new TCanvas("can","",200,10,1600,650);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.17);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gStyle->SetPalette(kBird);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(3,1,0,0);
  can->cd(1);
  TH2F *h1 = new TH2F("h1",Form(";p_{T} [GeV/c];v_{2}{4}/%s",grFancyTitle[method].Data()),1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h1->GetXaxis()->SetLabelSize(labelSize);
  h1->GetYaxis()->SetLabelSize(labelSize);
  h1->GetXaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetNdivisions(504);
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->Draw();
  TLatex tex;
  tex.SetTextFont(42);
  tex.SetTextAlign(31);
  tex.DrawLatex(maxpt,minV2Ratio*1.1,Form("#splitline{Au+Au, centrality 10-40%%}{%s}",pidFancyNames[pid].Data()));
  TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt->SetBorderSize(0);
  leg_pt->SetTextSize(0.05);
  leg_pt->SetHeader(leg_header[0].Data(),"C");
  for (int imod=0;imod<nmodel;imod++){
    leg_pt->AddEntry(grRatioV2[1][imod],Form("%s",grRatioV2[1][imod]->GetTitle()),"p");
  }
  leg_pt->Draw();
  
  for (int imod=nmodel-1;imod>0;imod--){
    grRatioV2[0][imod]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
  }
  
  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  //=================================================================================
  can->cd(2);
  TH2F *h2 = new TH2F("h2",Form(";p_{T} [GeV/c];v_{2}{4}/%s",grFancyTitle[method].Data()),1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h2->GetXaxis()->SetLabelSize(labelSize);
  h2->GetYaxis()->SetLabelSize(labelSize);
  h2->GetXaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetNdivisions(504);
  h2->GetYaxis()->SetTitleOffset(0.5);
  h2->Draw();
  
  TLegend *leg_pt2 = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt2->SetBorderSize(0);
  leg_pt2->SetTextSize(0.05);
  leg_pt2->SetHeader(leg_header[1].Data(),"C");
  for (int imod=0;imod<nmodel;imod++){
    leg_pt2->AddEntry("","","");
  }
  leg_pt2->Draw();

  for (int imod=nmodel-1;imod>=0;imod--){
  // for (int imod=0;imod<nmodel;imod++){
    grRatioV2[1][imod]->Draw("P");
  }
  
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  //=================================================================================
  can->cd(3);
  TH2F *h3 = new TH2F("h3",Form(";p_{T} [GeV/c];v_{2}{4}/%s",grFancyTitle[method].Data()),1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h3->GetXaxis()->SetLabelSize(labelSize);
  h3->GetYaxis()->SetLabelSize(labelSize);
  h3->GetXaxis()->SetTitleSize(labelSize);
  h3->GetYaxis()->SetTitleSize(labelSize);
  h3->GetYaxis()->SetNdivisions(504);
  h3->GetYaxis()->SetTitleOffset(0.5);
  h3->Draw();
  
  TLegend *leg_pt3 = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt3->SetBorderSize(0);
  leg_pt3->SetTextSize(0.05);
  leg_pt3->SetHeader(leg_header[2].Data(),"C");
  for (int imod=0;imod<nmodel;imod++){
    leg_pt3->AddEntry("","","");
  }
  leg_pt3->Draw();

  for (int imod=nmodel-1;imod>=0;imod--){
  // for (int imod=0;imod<nmodel;imod++){
    grRatioV2[2][imod]->Draw("P");
  }
  
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  can->SaveAs(Form("Ratio_v24_%s_%s_v2pt.eps",grTitle[method].Data(),pidFancyNames[pid].Data()));


}