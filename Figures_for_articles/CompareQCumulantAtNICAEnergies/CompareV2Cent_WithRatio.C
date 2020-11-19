void CompareV2Cent_WithRatio(){

  // const
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmethod = 4; // v22, v24, v26, v28
  const int nmodel = 5; // UrQMD, SMASH, AMPT08, AMPT15, vHLLE+UrQMD
  const float mincent = -5;
  const float maxcent = 64.;
  const float maxV2 = 0.09;
  const float minV2 = -0.01;
  const float minV2Ratio = 0.5;
  const float maxV2Ratio = 1.3;
  const float leg_coordinate[4]={0.68,0.07,0.99,0.3}; // top left: 0.28,0.7,0.6,0.99
  const float labelSizeUpperPlot = 0.095;
  const float titleSizeUpperPlot = 0.115;
  const float labelSizeLowerPlot = 0.08;
  const float titleSizeLowerPlot = 0.1;
  const float markerSize = 1.8;
  const float titleOffset = 0.8;
  const float textFont = 42;
  const int npad = 10;
  // flags
  const int ratioToMethod = 0; // v22 gapped
  // some stuffs
  TString energy[nenergy]={"7.7","11.5"};
  TString leg_header[nenergy] = {"7.7 GeV","11.5 GeV"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)"};
  TString xAxisName = {"Centrality (%)"};
  TString ratioName[nmethod-1]={"v2FHCal/v22","v24/v22","v2TPC/v22"};
  TString legendEntries[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{6}","v_{2}{8}"}; // ,"v_2{EP} FHCal
  TString model[nmodel] = {"UrQMD","SMASH","AMPT08","AMPT15","vHLLEUrQMD"};
  TString modelName[nmodel]={"UrQMD","SMASH","AMPT, #sigma_{p}=1.5mb","AMPT, #sigma_{p}=0.8mb","vHLLE+UrQMD"};
  TFile *input[nenergy][nmodel];
  TFile *inputHIghOrderQC[nenergy][nmodel];

  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  TGraphErrors *grRatioV2[nenergy][nmodel][nmethod];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      input[ien][imod] = new TFile(Form("./Data/v2_%s_%sGeV_8PID.root",model[imod].Data(),energy[ien].Data()),"read");
      inputHIghOrderQC[ien][imod] = new TFile(Form("./Data/v2_%s_%s_v26v28.root",model[imod].Data(),energy[ien].Data()),"read");
      grV2[ien][imod][0] = (TGraphErrors*)input[ien][imod]->Get(Form("grRF_2")); // v22gap
      grV2[ien][imod][1] = (TGraphErrors*)input[ien][imod]->Get(Form("grRF_1")); // v24
      // grV2[ien][imod][1] = (TGraphErrors*)inputHIghOrderQC[ien][imod]->Get(Form("grRF_1_8")); // v24
      grV2[ien][imod][2] = (TGraphErrors*)inputHIghOrderQC[ien][imod]->Get(Form("grRF_2_8")); // v26
      grV2[ien][imod][3] = (TGraphErrors*)inputHIghOrderQC[ien][imod]->Get(Form("grRF_3_8")); // v28
      for (int imeth=0; imeth<nmethod; imeth++){
        grV2[ien][imod][imeth] -> RemovePoint(0);
      }
    }
  }

  
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){

      grV2[ien][imod][0] -> SetMarkerColor(kBlue+1);
      grV2[ien][imod][0] -> SetLineColor(kBlue+1);
      grV2[ien][imod][0] -> SetMarkerStyle(kOpenTriangleUp);

      grV2[ien][imod][1] -> SetMarkerColor(kRed+1);
      grV2[ien][imod][1] -> SetLineColor(kRed+1);
      grV2[ien][imod][1] -> SetMarkerStyle(kFullCircle);  

      grV2[ien][imod][2] -> SetMarkerColor(kGreen+3);
      grV2[ien][imod][2] -> SetLineColor(kGreen+3);
      grV2[ien][imod][2] -> SetMarkerStyle(kFullCross);

      grV2[ien][imod][3] -> SetMarkerColor(kBlack);
      grV2[ien][imod][3] -> SetLineColor(kBlack);
      grV2[ien][imod][3] -> SetMarkerStyle(kOpenSquare);


      for (int imeth=0;imeth<nmethod;imeth++){
        grV2[ien][imod][imeth] -> SetMarkerSize(markerSize);
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod], *vy_gr[nenergy][nmodel][nmethod], *ex_gr[nenergy][nmodel][nmethod], *ey_gr[nenergy][nmodel][nmethod];
  Int_t nbins[nenergy][nmodel][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
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
  
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      for (int imeth=0;imeth<nmethod;imeth++){
        std::vector<Double_t> vRatioToV22, vRatioToV22Err;  
        for (int i=0;i<nbins[ien][imod][ratioToMethod];i++){
          Double_t ratio = vy_gr[ien][imod][imeth][i]/vy_gr[ien][imod][ratioToMethod][i];
          Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][ratioToMethod][i]/vy_gr[ien][imod][ratioToMethod][i],2)+TMath::Power(ey_gr[ien][imod][imeth][i]/vy_gr[ien][imod][imeth][i],2)));
          vRatioToV22.push_back(ratio);
          vRatioToV22Err.push_back(ratioErr);
        }
        grRatioV2[ien][imod][imeth] = new TGraphErrors(nbins[ien][imod][ratioToMethod],vx_gr[ien][imod][ratioToMethod],&vRatioToV22[0],ex_gr[ien][imod][ratioToMethod],&vRatioToV22Err[0]);
        grRatioV2[ien][imod][imeth] -> SetTitle(Form("%s",ratioName[imeth].Data()));
        vRatioToV22.clear();
        vRatioToV22Err.clear();
      }

      grRatioV2[ien][imod][0] -> SetMarkerColor(kBlue+1);
      grRatioV2[ien][imod][0] -> SetLineColor(kBlue+1);
      grRatioV2[ien][imod][0] -> SetMarkerStyle(kOpenTriangleUp);

      grRatioV2[ien][imod][1] -> SetMarkerColor(kRed+1);
      grRatioV2[ien][imod][1] -> SetLineColor(kRed+1);
      grRatioV2[ien][imod][1] -> SetMarkerStyle(kFullCircle);

      grRatioV2[ien][imod][2] -> SetMarkerColor(kGreen+3);
      grRatioV2[ien][imod][2] -> SetLineColor(kGreen+3);
      grRatioV2[ien][imod][2] -> SetMarkerStyle(kFullCross);

      grRatioV2[ien][imod][3] -> SetMarkerColor(kBlack);
      grRatioV2[ien][imod][3] -> SetLineColor(kBlack);
      grRatioV2[ien][imod][3] -> SetMarkerStyle(kOpenSquare);
      for (int imeth=0;imeth<nmethod;imeth++){
        grRatioV2[ien][imod][imeth]->SetMarkerSize(markerSize);
      }    
    }
  }
  
  for (int ien=1;ien<nenergy;ien++){
  TCanvas *can = new TCanvas("can","",200,10,2000,1000);
  TPaveLabel* title = new TPaveLabel(0.1,0.963,0.9,0.98,Form("Au+Au at #sqrt{s_{NN}}=%s GeV, Ch. hadrons, 0.2<p_{T}^{}<3.0 GeV/c",energy[ien].Data()));
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.5);
  title->Draw();

  can->SetLeftMargin(0.18);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.17);
  can->SetTopMargin(0.12);
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gStyle->SetPalette(kDarkRainBow);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(nmodel,2,0,0);
  TH2F *h[npad];
  for (int ipad=0;ipad<npad;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;v_{2}",xAxisName.Data()),1,mincent,maxcent,1,minV2,maxV2);
    else if (ipad<npad/2) h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,mincent,maxcent,1,minV2,maxV2);
    else if (ipad==npad/2) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";;Ratio to v_{2}{2}",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else if (ipad==npad/2+2) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;",xAxisName.Data()),1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    if (ipad==npad/2){
      h[ipad]->GetXaxis()->SetLabelSize(labelSizeLowerPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeLowerPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeLowerPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeLowerPlot);
      h[ipad]->GetXaxis()->SetLabelOffset(0.016);
    }else{
      h[ipad]->GetXaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeUpperPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeUpperPlot);
    }

    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(titleOffset-0.05);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->CenterTitle(true);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(titleOffset+0.16);
    h[ipad]->GetYaxis()->SetLabelOffset(0.016);
    if (ipad!=0)h[ipad]->GetYaxis()->CenterTitle(true);
    h[ipad]->Draw();

    // cout << "error" << endl;
    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(11);
    tex.SetTextSize(labelSizeUpperPlot);
    if (ipad==npad/2) tex.SetTextSize(labelSizeLowerPlot);
    if (ipad<npad/2) {
      tex.DrawLatex(mincent+5,maxV2*0.88,padName[ipad].Data());
    }else {
      tex.DrawLatex(mincent+5,maxV2Ratio*0.94,padName[ipad].Data());
    }
    
    tex.DrawLatex(mincent+15,maxV2*0.88,Form("%s",modelName[ipad].Data()));
    if (ipad==0) {
      // tex.DrawLatex(maxcent*0.9,maxV2*0.9,Form("Au+Au at #sqrt{s_{NN}}=%s GeV",energy[0].Data()));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot);
      leg_pt->SetTextFont(textFont);
      // for (int imeth=0;imeth<nmethod;imeth++){
      //   leg_pt->AddEntry(grV2[0][0][imeth],legendEntries[imeth].Data(),"p");
      // }
      leg_pt->AddEntry(grV2[ien][0][0],legendEntries[0].Data(),"p");
      leg_pt->AddEntry(grV2[ien][0][1],legendEntries[1].Data(),"p");
      leg_pt->Draw();
    }
    if (ipad==1) {
      // tex.DrawLatex(maxcent*0.9,maxV2*0.9,Form("UrQMD, 10-40%%"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot);
      leg_pt->SetTextFont(textFont);
      leg_pt->AddEntry(grV2[ien][0][2],legendEntries[2].Data(),"p");
      leg_pt->AddEntry(grV2[ien][0][3],legendEntries[3].Data(),"p");
      leg_pt->Draw();
    }

    
    for (int imeth=0;imeth<nmethod;imeth++){
      
      grV2[ien][ipad][imeth]->Draw("P");
      
      // if (ipad==0) grV2[0][0][imeth]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
      // if (ipad==1) grV2[0][1][imeth]->Draw("P");
      // if (ipad==2) grV2[0][3][imeth]->Draw("P");
    }

    for (int imeth=0;imeth<nmethod;imeth++){
      if (imeth==0) continue;
      if (ipad>=npad/2) grRatioV2[ien][ipad-nmodel][imeth]->Draw("P");
       
      // if (ipad==3) grRatioV2[0][0][imeth]->Draw("P");
      // if (ipad==4) grRatioV2[0][1][imeth]->Draw("P");
      // if (ipad==5) grRatioV2[0][3][imeth]->Draw("P");
    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    if (ipad>=npad/2)lineOne.DrawLine(mincent,1.,maxcent,1.);
  }
  
  can->SaveAs(Form("Figure_Compare_methods_v2cent_%s.pdf",energy[ien].Data()));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("Figure_Compare_methods_v2cent_%s.png",energy[ien].Data()));
  }

}