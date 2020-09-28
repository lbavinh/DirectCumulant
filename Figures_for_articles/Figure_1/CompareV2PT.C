void CompareV2PT(){
  // const
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmodel = 3; // vHLLE+UrQMD, UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const int npid = 4; // CH, pions, kaons, protons
  const float minpt = -0.05;
  const float maxpt = 2.36;
  const float maxV2 = 1.58;
  const float minV2 = 0.42;
  const float leg_coordinate[4]={0.28,0.7,0.6,0.99};
  const float labelSize = 0.05;
  const int npad = 6;
  // flags
  const int pid = 1; // v2 for: 0: CH; 1: Pions; 2: Kaons; 3: (Anti)protons
  // some stuffs
  TString energy[nenergy]={"4.5","7.7","11.5"};
  TString leg_header[nenergy] = {"4.5 GeV","7.7 GeV","11.5 GeV"};
  TString model[nmodel]={"vHLLE+UrQMD","UrQMD","SMASH"};
  TString grFancyTitle[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{#eta-sub}","v_{2}{2,|#Delta#eta|>0.1}"};
  TString grTitle[nmethod]={"v22","v24","v2etasub","v22etagap"};
  TString pidFancyNames[npid] = {"Charged hadrons", "Pions", "Kaons", "(Anti)protons"};
  TString xAxisName = {"p_{T} [GeV/c]"};
  TString legendEntries[3]={"v_2{2,|#Delta#eta|>0.1}","v_2{4}","v_2{#eta-sub,EP} TPC"}; // ,"v_2{EP} FHCal
  TString energyInPads[npad]={"7.7","7.7","7.7","11.5","11.5","11.5"};
  TString pidInPads[npad]={"h^{#pm}","#pi^{+}","p","h^{#pm}","#pi^{+}","p"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (imod==0 && ien==0) continue; // we haven't have 4.5GeV of vHLLE+UrQMD yet.
      input[ien][imod] = new TFile(Form("v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      for (int imeth=0;imeth<nmethod;imeth++){ // v24 = 1; v22(eta-gap) = 3
        grV2[ien][imod][imeth] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_cent10-40_%i_%i",imeth,pid)); // "_0" - Charged Hadrons
      }
    }
  }
  for (int ien=0;ien<nenergy;ien++){
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
  can->Divide(3,2,0,0);
  TH2F *h[npad];
  for (int ipad=0;ipad<npad;ipad++){
    can->cd(ipad+1);
    h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;v_{2}{4}/%s",xAxisName.Data(),grFancyTitle[method].Data()),1,minpt,maxpt,1,minV2,maxV2);
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(labelSize);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    // h[ipad]->GetXaxis()->SetTitleOffset(1.2);

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(labelSize);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(1.2);
    h[ipad]->Draw();
    
    TLatex tex;
    tex.SetTextFont(42);
    tex.SetTextAlign(31);
    // tex.SetTextSize(0.05);
    if (ipad==0) {
      tex.DrawLatex(maxpt,maxV2,Form("#splitline{Au+Au, centrality 10-40%%}{%s @#sqrt{s_{NN}}=%s}",pidInPads[ipad].Data(),energyInPads[ipad].Data()));
    }else{
      tex.DrawLatex(maxpt,maxV2,Form("%s @ #sqrt{s_{NN}}=%s",pidInPads[ipad].Data(),));
    }
    if (ipad==0){
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(0.05);
      leg_pt->SetHeader(leg_header[0].Data(),"C");
      for (int imod=0;imod<nmodel;imod++){
        leg_pt->AddEntry(grRatioV2[1][imod],,"p");
      }
      leg_pt->Draw();
    }

    
    for (int imod=nmodel-1;imod>0;imod--){
      grRatioV2[0][imod]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
    }
  }
  
  // TLine lineOne;
  // lineOne.SetLineStyle(2);
  // lineOne.DrawLine(minpt,1.,maxpt,1.);

  can->SaveAs(Form("Ratio_v24_%s_%s_v2pt.eps",grTitle[method].Data(),pidFancyNames[pid].Data()));


}