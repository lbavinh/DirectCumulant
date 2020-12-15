void Compare_fluctuation(){
  const int nenergy = 2; // 7.7, 11.5, 19.6, 27, 39 GeV
  const int nmodel = 6; // "STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float mincent = -3;
  const float maxcent = 64.;
  const float maxV2Ratio = 1.25;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.35,0.25,0.5,0.43}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.07;
  const float titleSize = 0.09;
  const float labelSize1 = 0.067;
  const float titleSize1 = 0.08;
  const float markerSize = 2.0;
  const float textFont = 42;
  TString legendEntries[nmodel]={"STAR data","UrQMD","SMASH","AMPT, #sigma_{p}=1.5mb","AMPT, #sigma_{p}=0.8mb","vHLLE+UrQMD"}; //(Phys.Rev.C.86.054908)
  TString energy[nenergy]={"7.7","11.5"};
  TString model[nmodel]={"#STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLEUrQMD"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  
  TGraphErrors *grRatioV2[nenergy][nmodel];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      input[ien][imod] = new TFile(Form("./Data/v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      if (!input[ien][imod]) { cout << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v2(eta-sub), v22(eta-gap)
        grV2[ien][imod][imeth] = (TGraphErrors*)input[ien][imod]->Get(Form("grRF_%i_0",imeth)); // "_0" - Charged Hadrons
        if (!grV2[ien][imod][imeth]) { cout << "Graphs in " << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
        grV2[ien][imod][imeth] -> RemovePoint(0);
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
  // cout << "Code breaks here" << endl;
  double xx[2]={0},yy[2]={0};
  std::vector<Double_t> vRatioV22GappedV24[nenergy][nmodel], vRatioV22GappedV24Err[nenergy][nmodel];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      // cout << "Code breaks here " << ien <<" "<< imod << endl;
      if (ien==2 && imod!=5) grRatioV2[ien][imod] = new TGraphErrors(2,xx,yy,xx,yy); // at 19.6 GeV only have vHLLE+UrQMD
      else if (ien==3 && imod==2) grRatioV2[ien][imod] = new TGraphErrors(2,xx,yy,xx,yy);  // at 27 GeV only SMASH is missing
      else if (ien==4 && imod!=3 && imod!=5) grRatioV2[ien][imod] = new TGraphErrors(2,xx,yy,xx,yy);  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      else{
        
        for (int i=0;i<nbins[ien][imod][3];i++){
          
          Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][3][i];
          Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][3][i]/vy_gr[ien][imod][3][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
          vRatioV22GappedV24[ien][imod].push_back(ratio);
          vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
        }
        grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);      
      }
    }
  }
  
  for (int ien=0;ien<nenergy;ien++){
    // "STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"
    grRatioV2[ien][5] -> SetMarkerColor(kBlue+2);
    grRatioV2[ien][5] -> SetLineColor(kBlue+2);
    grRatioV2[ien][5] -> SetMarkerStyle(kOpenCircle);

    grRatioV2[ien][4] -> SetMarkerColor(kGray+2);
    grRatioV2[ien][4] -> SetLineColor(kGray+2);
    grRatioV2[ien][4] -> SetMarkerStyle(kOpenSquare);
    
    grRatioV2[ien][1] -> SetMarkerColor(kGreen+3);
    grRatioV2[ien][1] -> SetLineColor(kGreen+3);
    grRatioV2[ien][1] -> SetMarkerStyle(kFullTriangleUp);

    grRatioV2[ien][2] -> SetMarkerColor(kBlack);
    grRatioV2[ien][2] -> SetLineColor(kBlack);
    grRatioV2[ien][2] -> SetMarkerStyle(kOpenCross);

    grRatioV2[ien][3] -> SetMarkerColor(kYellow+2);
    grRatioV2[ien][3] -> SetLineColor(kYellow+2);
    grRatioV2[ien][3] -> SetMarkerStyle(kFullCrossX);
  
  }
  for (int imod=1;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      grRatioV2[ien][imod]->SetMarkerSize(markerSize);
    }
  }


  TString energySTAR[5]={"77","115","196","27","39"};
  TString energySTARLegend[5]={"7.7 GeV","11.5 GeV","19.6 GeV","27 GeV","39 GeV"};
  TGraphErrors *grRatioV2STAR[nenergy];
  for (int iener=0;iener<nenergy;iener++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./Data/v2methods%sCent.txt",energySTAR[iener].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file summary1.txt !\n"<< endl;
      fflush(stdin);
      return;
    }
    int ncent = 9;
    double cent[ncent], v2eta[ncent], v22[ncent], v24[ncent];
    double centE[ncent], v2etae[ncent], v22e[ncent], v24e[ncent];
    double ratiov24v22[ncent], ratiov24v22e[ncent];
    for (int ipt=0; ipt<ncent; ipt++) {
      float  mCent,s2,  s2e,  s2eta,  s2etae,    s22,s22e,s24,s24e,s2b, s2be;
      //    cent,v2EP,v2EPe,v2etasub,v2etasube,v22,v22e,v24,v24e,v2bbc,v2bbce
      fscanf(fp1, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&mCent,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

      cent[ipt]     = mCent;
      v2eta[ipt]  = s2eta;
      v2etae[ipt] = s2etae;
      v22[ipt]    = s22;
      v22e[ipt]   = s22e;
      v24[ipt]    = s24;
      v24e[ipt]   = s24e;
      centE[ipt]    = 0.;
      Double_t ratio = s24/s22;
      Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(s24e/s24,2)+TMath::Power(s22e/s22,2)));
      ratiov24v22[ipt] = ratio;
      ratiov24v22e[ipt] = ratioErr;
    }
    // STAR
    grRatioV2[iener][0] = new TGraphErrors(ncent,cent,ratiov24v22,centE,ratiov24v22e);
    grRatioV2[iener][0] -> SetMarkerStyle(kFullStar);
    grRatioV2[iener][0] -> SetMarkerSize(markerSize+1);
    grRatioV2[iener][0] -> SetMarkerColor(kRed+1);
    grRatioV2[iener][0] -> SetLineColor(kRed+1);
    // grRatioV2STAR[iener] = new TGraphErrors(ncent,cent,ratiov24v22,centE,ratiov24v22e);
  }
  TFile *fEcc2[nenergy];
  TGraphErrors *grRatioEcc2[nenergy];
  for (int iener=0; iener<nenergy; iener++){
  fEcc2[iener] = new TFile(Form("./Data/ecc_Glauber_%sGeV.root",energy[iener].Data()),"read");
  grRatioEcc2[iener] = (TGraphErrors*) fEcc2[iener] -> Get("gr_e24e22");  
  grRatioEcc2[iener] -> SetMarkerStyle(23);
  grRatioEcc2[iener] -> SetTitle("#epsilon_{2}{4}/#epsilon_{2}{2};centrality, %");
  grRatioEcc2[iener] -> SetMarkerColor(kRed+2);
  grRatioEcc2[iener] -> SetLineWidth(markerSize+1);
  grRatioEcc2[iener] -> SetLineStyle(2);
  grRatioEcc2[iener] -> SetLineColor(kRed+2);
  grRatioEcc2[iener] -> RemovePoint(0);
  }
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1500,800);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.15);
  can->SetTopMargin(0.08);

  TPaveLabel* title = new TPaveLabel(0.1,0.957,0.9,0.98,"Au+Au, Ch. hadrons");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.5);
  title->Draw();

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(nenergy,1,0,0);
  TH2F *h[nenergy];
  for (int ipad=0;ipad<nenergy;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";;v_{2}{4}/v_{2}{2}",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else if (ipad==1) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";Centrality (%);",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.8);
    h[ipad]->GetXaxis()->SetLabelOffset(0.000005);
    h[ipad]->GetXaxis()->CenterTitle(true);

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(1.25);
    h[ipad]->GetYaxis()->CenterTitle(true);
    if (ipad==0) {
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    // h[ipad]->GetXaxis()->SetLabelOffset(0.012);
    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize); 
    h[ipad]->GetYaxis()->SetLabelOffset(0.012);
    }
    h[ipad]->Draw();

    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(13);
    tex.SetTextSize(labelSize);
    // if (ipad==0) tex.SetTextSize(labelSize1);
    tex.DrawLatex(mincent+2,maxV2Ratio*0.98,padName[ipad].Data());
    tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("#sqrt{s_{NN}}=%s GeV",energy[ipad].Data())); // #sqrt{s_{NN}}=
    if (ipad==0) {
      // tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Au+Au at"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0]+0.2,leg_coordinate[1],leg_coordinate[2]+0.2,leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize1-0.02);
      // for (int imod=3; imod<nmethod; imod++){
      leg_pt->AddEntry(grRatioV2[0][1],legendEntries[1].Data(),"p");
      leg_pt->AddEntry(grRatioV2[0][2],legendEntries[2].Data(),"p");
      leg_pt->AddEntry(grRatioV2[0][0],legendEntries[0].Data(),"p");
      // leg_pt->AddEntry("","Phys.Rev.C86,054908(2012)","");
      tex.SetTextSize(labelSize1-0.01);
      tex.SetTextAlign(11);
      // tex.DrawLatex(mincent+3,minV2Ratio+0.05,"Phys.Rev.C86,054908(2012)");
      
      // leg_pt->AddEntry(grRatioV2[0][5],legendEntries[5].Data(),"p");

      // }
      leg_pt->Draw();      

    }else if (ipad==1) {
      // tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Ch. hadrons"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize1-0.02);
      leg_pt->AddEntry(grRatioV2[0][5],legendEntries[5].Data(),"p");
      leg_pt->AddEntry(grRatioV2[0][3],legendEntries[3].Data(),"p");
      leg_pt->AddEntry(grRatioV2[0][4],legendEntries[4].Data(),"p");
      leg_pt->AddEntry(grRatioEcc2[0],"#epsilon_{2}{4}/#epsilon_{2}{2}(Glauber)","l");
      
      

      leg_pt->Draw();
    }else if (ipad==2){
      // tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("0.2<p_{T}^{}<3.0 GeV/c"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.02);
      leg_pt->AddEntry(grRatioV2[0][1],legendEntries[1].Data(),"p");
      leg_pt->AddEntry(grRatioV2[0][2],legendEntries[2].Data(),"p");
      leg_pt->Draw();

    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(mincent,1.,maxcent,1.);
    grRatioEcc2[ipad] -> Draw("L");
    for (int imod=0;imod<nmodel;imod++){
      
      grRatioV2[ipad][imod]->Draw("P");
      
      
    }
  }
  can->SaveAs("Figure_Ratiov24v22_v2cent_7.7-11.5_compareWithSTAR.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("Figure_Ratiov24v22_v2cent_7.7-11.5_compareWithSTAR.png");


}