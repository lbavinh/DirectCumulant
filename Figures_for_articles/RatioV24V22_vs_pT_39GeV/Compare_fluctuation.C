void Compare_fluctuation(){
  const int ncent = 5; // 5-10, 10-20, 20-30, 30-40, 40-50
  const int nmodel = 3; // "STAR data","AMPT15","vHLLE+UrQMD"
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float minpt = -0.1;
  const float maxpt = 3.2;
  const float maxV2Ratio = 1.3;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.07,0.2,0.45,0.4}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.085;
  const float titleSize = 0.1;
  const float labelSize1 = 0.07;
  const float titleSize1 = 0.08;
  const float markerSize = 2.0;
  const float textFont = 42;
  TString legendEntries[nmodel]={"STAR data","AMPT, #sigma_{p}=1.5mb","vHLLE+UrQMD"}; //(Phys.Rev.C.86.054908)
  TString centrality[ncent]={"5-10%","10-20%","20-30%","30-40%","40-50%"};
  TString model[nmodel]={"STAR data","AMPT15","vHLLEUrQMD"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)"};
  TFile *input[nmodel];
  TGraphErrors *grV2[ncent][nmodel][nmethod];
  TGraphErrors *grRatioV2[ncent][nmodel];

  
  for (int imod=1;imod<nmodel;imod++){
    input[imod] = new TFile(Form("./Data/v2_%s_39GeV.root",model[imod].Data()),"read");
    for (int icent=0;icent<ncent;icent++){
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v2(eta-sub), v22(eta-gap)
        grV2[icent][imod][imeth] = (TGraphErrors*)input[imod]->Get(Form("gr_cent%i_%i_0",icent+1,imeth)); // "_0" - Charged Hadrons
        if (!grV2[icent][imod][imeth]) { cout << "Graphs in " << model[imod].Data() << centrality[icent].Data() << "not found!" << endl; return; }
      }
    }
  }
  
  Double_t *vx_gr[ncent][nmodel][nmethod], *vy_gr[ncent][nmodel][nmethod], *ex_gr[ncent][nmodel][nmethod], *ey_gr[ncent][nmodel][nmethod];
  Int_t nbins[ncent][nmodel][nmethod];
  for (int icent=0;icent<ncent;icent++){
    for (int imod=1;imod<nmodel;imod++){
      for (int imeth=0;imeth<nmethod;imeth++){
        // Read points
        vx_gr[icent][imod][imeth]=(Double_t*)grV2[icent][imod][imeth]->GetX();
        vy_gr[icent][imod][imeth]=(Double_t*)grV2[icent][imod][imeth]->GetY();

        // Read errors
        ex_gr[icent][imod][imeth]=(Double_t*)grV2[icent][imod][imeth]->GetEX();
        ey_gr[icent][imod][imeth]=(Double_t*)grV2[icent][imod][imeth]->GetEY();

        nbins[icent][imod][imeth]=(Int_t) grV2[icent][imod][imeth]->GetN();
      }
    }
  }
  // cout << "Code breaks here" << endl;
  double xx[2]={0},yy[2]={0};
  std::vector<Double_t> vRatioV22GappedV24[ncent][nmodel], vRatioV22GappedV24Err[ncent][nmodel];
  for (int icent=0;icent<ncent;icent++){
    for (int imod=1;imod<nmodel;imod++){
      for (int i=0;i<nbins[icent][imod][3];i++){
        Double_t ratio = vy_gr[icent][imod][1][i]/vy_gr[icent][imod][3][i];
        Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[icent][imod][3][i]/vy_gr[icent][imod][3][i],2)+TMath::Power(ey_gr[icent][imod][1][i]/vy_gr[icent][imod][1][i],2)));
        vRatioV22GappedV24[icent][imod].push_back(ratio);
        vRatioV22GappedV24Err[icent][imod].push_back(ratioErr);
      }
      grRatioV2[icent][imod] = new TGraphErrors(nbins[icent][imod][3],vx_gr[icent][imod][3],&vRatioV22GappedV24[icent][imod][0],ex_gr[icent][imod][3],&vRatioV22GappedV24Err[icent][imod][0]);      
    
    }
  }
  
  for (int icent=0;icent<ncent;icent++){
    // "STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"

    grRatioV2[icent][1] -> SetMarkerColor(kGreen+3);
    grRatioV2[icent][1] -> SetLineColor(kGreen+3);
    grRatioV2[icent][1] -> SetMarkerStyle(kFullTriangleUp);

    grRatioV2[icent][2] -> SetMarkerColor(kBlack);
    grRatioV2[icent][2] -> SetLineColor(kBlack);
    grRatioV2[icent][2] -> SetMarkerStyle(kOpenCircle);

    // grRatioV2[icent][3] -> SetMarkerColor(kYellow+2);
    // grRatioV2[icent][3] -> SetLineColor(kYellow+2);
    // grRatioV2[icent][3] -> SetMarkerStyle(kFullCrossX);

    // grRatioV2[icent][4] -> SetMarkerColor(kGray+2);
    // grRatioV2[icent][4] -> SetLineColor(kGray+2);
    // grRatioV2[icent][4] -> SetMarkerStyle(kOpenSquare);

    // grRatioV2[icent][5] -> SetMarkerColor(kBlue+2);
    // grRatioV2[icent][5] -> SetLineColor(kBlue+2);
    // grRatioV2[icent][5] -> SetMarkerStyle(kOpenCross);  
  }
  for (int imod=1;imod<nmodel;imod++){
    for (int icent=0;icent<ncent;icent++){
      grRatioV2[icent][imod]->SetMarkerSize(markerSize);
    }
  }

  TGraphErrors *grRatioV2STAR[ncent];
  for (int icent=0;icent<ncent;icent++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./Data/v2vspt_39GeV_%s.txt",centrality[icent].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file summary1.txt !\n"<< endl;
      fflush(stdin);
      return;
    }
    int npt = 14;
    double pt[npt], v24GF[npt], v22[npt], v24[npt];
    double pte[npt], v24GFe[npt], v22e[npt], v24e[npt];
    double ratiov24v22[npt], ratiov24v22e[npt];
    for (int ipt=0; ipt<npt; ipt++) {
      float  mPt,s22GF,s22GFe,  s24GF,  s24GFe,    s22,s22e,s24,s24e;
      //    pt,v2EP,v2EPe,v2etasub,v2etasube,v22,v22e,v24,v24e
      fscanf(fp1, "%f  %f  %f  %f  %f  %f  %f  %f  %f\n",&mPt,&s22GF,&s22GFe,&s24GF,&s24GFe,&s22,&s22e,&s24,&s24e);

      pt[ipt]     = mPt;
      v24GF[ipt]  = s24GF;
      v24GFe[ipt] = s24GFe;
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
    grRatioV2[icent][0] = new TGraphErrors(npt,pt,ratiov24v22,pte,ratiov24v22e);
    grRatioV2[icent][0] -> SetMarkerStyle(kFullStar);
    grRatioV2[icent][0] -> SetMarkerSize(markerSize+1);
    grRatioV2[icent][0] -> SetMarkerColor(kRed+1);
    grRatioV2[icent][0] -> SetLineColor(kRed+1);
    // grRatioV2STAR[icent] = new TGraphErrors(npt,pt,ratiov24v22,pte,ratiov24v22e);
  }
  
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1800,500);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.17);

  TPaveLabel* title = new TPaveLabel(0.1,0.94,0.9,0.97,"Au+Au at #sqrt{s_{NN}}=39 GeV, Ch. hadrons");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.5);
  title->Draw();

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(ncent,1,0,0);
  TH2F *h[ncent];
  for (int ipad=0;ipad<ncent;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";;v_{2}{4}/v_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else if (ipad==2) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";p_{T} (GeV/c);",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.8);
    h[ipad]->GetXaxis()->SetLabelOffset(0.01);
    h[ipad]->GetXaxis()->CenterTitle(true);

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(1.2);
    h[ipad]->GetYaxis()->CenterTitle(true);
    if (ipad==0) {
    h[ipad]->GetXaxis()->SetLabelSize(labelSize1);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize1);
    h[ipad]->GetXaxis()->SetLabelOffset(0.02);
    h[ipad]->GetYaxis()->SetLabelSize(labelSize1);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize1);      
    }
    h[ipad]->Draw();

    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(13);
    tex.SetTextSize(labelSize);
    if (ipad==0) tex.SetTextSize(labelSize1);
    tex.DrawLatex(minpt+0.1,maxV2Ratio*0.98,padName[ipad].Data());
    tex.DrawLatex(minpt+0.5,maxV2Ratio*0.98,Form("%s",centrality[ipad].Data())); // #sqrt{s_{NN}}=
    if (ipad==1) {

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      leg_pt->AddEntry(grRatioV2[ipad][0],legendEntries[0].Data(),"p");
      leg_pt->Draw();      
    }else if (ipad==2) {

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      leg_pt->AddEntry(grRatioV2[ipad][1],legendEntries[1].Data(),"p");
      leg_pt->Draw();
    }else if (ipad==3){

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2]+0.2,leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      leg_pt->AddEntry(grRatioV2[ipad][2],legendEntries[2].Data(),"p");
      leg_pt->Draw();

    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(minpt,1.,maxpt,1.);

    for (int imod=0;imod<nmodel;imod++){
      
      grRatioV2[ipad][imod]->Draw("P");
      
    }
  }
  can->SaveAs("Figure_Ratiov24v22_vs_pt_39GeV_CH.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("Figure_Ratiov24v22_vs_pt_39GeV_CH.png");


}