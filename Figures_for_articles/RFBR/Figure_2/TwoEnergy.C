void TwoEnergy(){
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmodel = 4; // Star data, vHLLE+UrQMD, UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float mincent = -1;
  const float maxcent = 63.;
  const float maxV2Ratio = 1.3;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.6,0.2,0.9,0.45}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.06;
  const float titleSize = 0.075;
  TString legendEntries[nmodel]={"STAR data","UrQMD","SMASH","AMPT, #sigma=1.5mb"};//(Phys.Rev.C.86.054908)
  TString energy[nenergy]={"11.5","7.7"};
  TString model[nmodel]={"STAR data","UrQMD","SMASH","AMPT15"};
  TString xAxisName = {"Centrality (%)"};
  TString padName[6]={"(a)","(b)","(c)","(d)","(e)","(f)"};
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
        Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][3][i];
        Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][3][i]/vy_gr[ien][imod][3][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
        vRatioV22GappedV24[ien][imod].push_back(ratio);
        vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
      }
      grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);
      grRatioV2[ien][imod] -> SetTitle(Form("%s;centrality [%%];v_{2}{4}/v_{2}{2,|#Delta#eta|>0.1}",model[imod].Data()));
      
    }
    // grRatioV2[ien][0] -> SetMarkerStyle(kFullCircle);
    // grRatioV2[ien][1] -> SetMarkerStyle(kFullCircle);
    grRatioV2[ien][2] -> SetMarkerColor(kBlue+1);
    grRatioV2[ien][2] -> SetLineColor(kBlue+1);
    grRatioV2[ien][2] -> SetMarkerStyle(kOpenSquare);

    grRatioV2[ien][3] -> SetMarkerColor(kGreen+2);
    grRatioV2[ien][3] -> SetLineColor(kGreen+2);
    grRatioV2[ien][3] -> SetMarkerStyle(kFullTriangleUp);

    grRatioV2[ien][1] -> SetMarkerColor(kBlack);
    grRatioV2[ien][1] -> SetLineColor(kBlack);
    grRatioV2[ien][1] -> SetMarkerStyle(kOpenCircle);

  }
  for (int imod=1;imod<nmodel;imod++){
    // grRatioV2[0][imod] -> SetMarkerColor(kRed);
    // grRatioV2[0][imod] -> SetLineColor(kRed);
    // grRatioV2[1][imod] -> SetMarkerColor(kGreen);
    // grRatioV2[1][imod] -> SetLineColor(kGreen);
    // grRatioV2[2][imod] -> SetMarkerColor(kBlue);
    // grRatioV2[2][imod] -> SetLineColor(kBlue);

    // grRatioV2[0][imod] -> SetMarkerStyle(kFullCircle);
    // grRatioV2[1][imod] -> SetMarkerStyle(kFullCircle);
    // grRatioV2[2][imod] -> SetMarkerStyle(kFullCircle);
    for (int ien=0;ien<nenergy;ien++){

      grRatioV2[ien][imod]->SetMarkerSize(1.8);
    }
  }
  TString energySTAR[nenergy]={"115","77"};
  TGraphErrors *grV2Star[nenergy-1][nmethod-1]; // v22, v24, v2etasub
  TGraphErrors *grRatioV2STAR[nenergy-1]; // "7.7","11.5","19.6"
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
    grRatioV2[iener][0] -> SetTitle(Form("STAR data (Phys.Rev.C.86.054908);centrality [%%];v_{2}{4}/v_{2}{2,|#Delta#eta|>0.1}"));
    grRatioV2[iener][0] -> SetMarkerStyle(kFullStar);
    grRatioV2[iener][0] -> SetMarkerSize(3.);
    grRatioV2[iener][0] -> SetMarkerColor(kRed+1);
    grRatioV2[iener][0] -> SetLineColor(kRed+1);

  }

  // cout << "error from here" << endl;
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1500,600);
  can->SetLeftMargin(0.12);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.15);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(2,1,0,0);
  TH2F *h[nenergy];
  for (int ipad=0;ipad<nenergy;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";;v_{2}{4}/v_{2}{2}"),1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else if (ipad==1) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s         ;v_{2}",xAxisName.Data()),1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    h[ipad]->GetXaxis()->SetLabelFont(42);
    h[ipad]->GetYaxis()->SetLabelFont(42);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.8);

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(0.75);
    h[ipad]->Draw();

    TLatex tex;
    tex.SetTextFont(42);
    tex.SetTextAlign(13);
    tex.SetTextSize(labelSize);
    tex.DrawLatex(mincent+2,maxV2Ratio*0.98,padName[ipad].Data());
    if (ipad==0) {
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Au+Au at"));
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98-0.12,Form("#sqrt{s_{NN}}=%s GeV",energy[ipad].Data()));
    }else if (ipad==1) {
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Ch. hadrons, 0.2<p_{T}^{}<3.0 GeV/c"));
      tex.DrawLatex(mincent+10,maxV2Ratio*0.98-0.12,Form("#sqrt{s_{NN}}=%s GeV",energy[ipad].Data()));
    }
    if (ipad==0){
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(42);
      leg_pt->SetTextSize(labelSize);
      for (int imod=0; imod<nmodel; imod++){
        leg_pt->AddEntry(grRatioV2[0][imod],legendEntries[imod].Data(),"p");
      }
      leg_pt->Draw();
    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(mincent,1.,maxcent,1.);

    for (int imod=nmodel-1;imod>=0;imod--){

      if (ipad==0) grRatioV2[0][imod]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
      if (ipad==1) grRatioV2[1][imod]->Draw("P"); // PZ


    }
  }
  can->SaveAs("Figure_2_Ratiov24v22_v2cent_2ener.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("Figure_2_Ratiov24v22_v2cent_2ener.png");


}