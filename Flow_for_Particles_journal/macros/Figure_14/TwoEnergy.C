void TwoEnergy(){
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmodel = 7; // "STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float mincent = -3;
  const float maxcent = 64.;
  const float maxV2Ratio = 1.3;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.3,0.2,0.7,0.45}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.075;
  const float titleSize = 0.09;
  const float markerSize = 1.5;
  const int textFont = 132;
  TString legendEntries[nmodel]={"STAR data","UrQMD","SMASH","AMPT, #sigma_{p}=1.5mb","AMPT, #sigma_{p}=0.8mb","vHLLE+UrQMD", "AMPT, #sigma_{p}=0 mb"};//(Phys.Rev.C.86.054908)
  TString energy[nenergy]={"7.7","11.5"};
  TString model[nmodel]={"STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLEUrQMD", "AMPT00"};
  TString xAxisName = {"Centrality (%)"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  
  TGraphErrors *grRatioV2[nenergy][nmodel];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){

      input[ien][imod] = new TFile(Form("./Data/v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
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
        Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][3][i];
        Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][3][i]/vy_gr[ien][imod][3][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
        vRatioV22GappedV24[ien][imod].push_back(ratio);
        vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
      }
      grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);
      grRatioV2[ien][imod] -> SetTitle(Form("%s;centrality [%%];v_{2}{4}/v_{2}{2}",model[imod].Data()));
      grRatioV2[ien][imod] -> RemovePoint(0);
    }

    grRatioV2[ien][1] -> SetMarkerColor(kBlack);
    grRatioV2[ien][1] -> SetLineColor(kBlack);
    grRatioV2[ien][1] -> SetMarkerStyle(kOpenCircle);

    grRatioV2[ien][2] -> SetMarkerColor(kBlue+1);
    grRatioV2[ien][2] -> SetLineColor(kBlue+1);
    grRatioV2[ien][2] -> SetMarkerStyle(kFullTriangleDown);

    grRatioV2[ien][3] -> SetMarkerColor(kBlack);
    grRatioV2[ien][3] -> SetLineColor(kBlack);
    grRatioV2[ien][3] -> SetMarkerStyle(kOpenSquare);

    grRatioV2[ien][4] -> SetMarkerColor(kBlue+3);
    grRatioV2[ien][4] -> SetLineColor(kBlue+3);
    grRatioV2[ien][4] -> SetMarkerStyle(kFullTriangleUp);

    grRatioV2[ien][5] -> SetMarkerColor(kYellow+3);
    grRatioV2[ien][5] -> SetLineColor(kYellow+3);
    grRatioV2[ien][5] -> SetMarkerStyle(kFullCircle);

    grRatioV2[ien][6] -> SetMarkerColor(kGreen+4);
    grRatioV2[ien][6] -> SetLineColor(kGreen+4);
    grRatioV2[ien][6] -> SetMarkerStyle(kOpenCircle);

  }
  for (int imod=1;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      grRatioV2[ien][imod]->SetMarkerSize(markerSize);
    }
  }
  TString energySTAR[nenergy]={"77","115"};
  // TGraphErrors *grV2Star[nenergy-1][nmethod-1]; // v22, v24, v2etasub
  for (int iener=0;iener<nenergy;iener++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./Data/v2methods%sCent.txt",energySTAR[iener].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file "<< path1 <<" !\n"<< endl;
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
    grRatioV2[iener][0] -> SetTitle(Form("STAR data (Phys.Rev.C.86.054908);centrality [%%];v_{2}{4}/v_{2}{2,|#Delta#eta|>0.1}"));
    grRatioV2[iener][0] -> SetMarkerStyle(kFullStar);
    grRatioV2[iener][0] -> SetMarkerSize(markerSize+1);
    grRatioV2[iener][0] -> SetMarkerColor(kRed+1);
    grRatioV2[iener][0] -> SetLineColor(kRed+1);
    grRatioV2[iener][0] -> SetLineWidth(1);
  }

  

  // end of update 4-th canvas
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPalette(kDarkRainBow);

  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1000,500);
  can->SetLeftMargin(0.16);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.15);
  gStyle->SetOptStat(0);
  can->Divide(2,1,0,0);
  TH2F *h[3];
  for (int ipad=1;ipad<3;ipad++){
    can->cd(ipad);

    h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;#it{v}_{2}{4}/#it{v}_{2}{2}",xAxisName.Data()),1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->SetTitleFont(textFont);
    h[ipad]->GetYaxis()->SetTitleFont(textFont);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.82);
    

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(0.9);
    h[ipad]->Draw();

    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(13);
    tex.SetTextSize(labelSize);
    tex.DrawLatex(mincent+2,maxV2Ratio*0.98,padName[ipad].Data());


    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(mincent,1.,maxcent,1.);

    for (int imod=0;imod<nmodel;imod++){
      if (imod!=3 && imod!=4 && imod!=6 && imod!=0) continue;  
      if (ipad==1) grRatioV2[0][imod]->Draw("P");
      if (ipad==2 && imod==6) continue;
      if (ipad==2) grRatioV2[1][imod]->Draw("P"); // PZ
      // if (ipad==2) grRatioV2[1][imod]->Draw("P"); // PZ


    }
        if (ipad==1) {
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Au+Au, Charged Hadrons"));
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98-0.12,Form("#sqrt{#it{s}_{NN}}=%s GeV",energy[ipad-1].Data()));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      for (int imod=3; imod<nmodel; imod++){
        if (imod!=3 && imod!=4 && imod!=6 && imod!=0) continue;  
        leg_pt->AddEntry(grRatioV2[0][imod],legendEntries[imod].Data(),"p");
      }
      leg_pt->Draw();

    }else if (ipad==2) {
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("0.2< #it{p}_{T}^{}< 3.0 GeV/c"));
      tex.DrawLatex(mincent+13,maxV2Ratio*0.98-0.12,Form("#sqrt{#it{s}_{NN}}=%s GeV",energy[ipad-1].Data()));

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      for (int imod=0; imod<3; imod++){
        if (imod!=3 && imod!=4 && imod!=6 && imod!=0) continue;  
        leg_pt->AddEntry(grRatioV2[0][imod],legendEntries[imod].Data(),"p");
      }
      leg_pt->Draw();
    }
  }
  // gROOT->SetStyle("Plain");
  can->SaveAs("v24v22Cent_Models.pdf");
  // gROOT->SetStyle("Pub");
  can->SaveAs("v24v22Cent_Models.png");


}