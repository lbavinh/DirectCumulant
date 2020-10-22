void CompareV2PT_withRatio(){

  // const
  const int nenergy = 2; // 7.7, 11.5 GeV
  const int nmethod = 5; // 0: v2FHCal, 1: v24, 2: v2TPC, 3:v2SP, 4:v22(eta-gap)
  const int npid = 4; // CH, pions, kaons, protons
  const float minpt = -0.05;
  const float maxpt = 2.35;
  const float maxV2 = 0.16;
  const float minV2 = -0.01;
  const float minV2Ratio = 0.82;
  const float maxV2Ratio = 1.18;
  const float leg_coordinate[4]={0.6,0.05,0.99,0.32}; // top left: 0.28,0.7,0.6,0.99
  const float labelSizeUpperPlot = 0.095;
  const float titleSizeUpperPlot = 0.115;
  const float labelSizeLowerPlot = 0.08;
  const float titleSizeLowerPlot = 0.1;
  const float markerSize = 1.8;
  const float titleOffset = 0.8;
  const float textFont = 42;
  const int npad = 6;
  // flags
  const int ratioToMethod = 4; // v22 gapped
  // some stuffs
  TString energy[nenergy]={"7.7","11.5"};
  TString leg_header[nenergy] = {"7.7 GeV","11.5 GeV"};
  TString padName[npad]={"(a)","(b)","(c)","(d)","(e)","(f)"};
  TString grTitle[nmethod]={"v22","v24","v2etasub","v22etagap"};
  TString xAxisName = {"p_{T} (GeV/c)"};
  TString ratioName[nmethod-1]={"v2FHCal/v22","v24/v22","v2TPC/v22","v2SP/v22"};
  TString legendEntries[nmethod]={"v_{2}^{EP}{#Psi_{1,FHCal}}","v_{2}{4}","v_{2}^{EP}{#Psi_{2,TPC}^{}}","v_{2}^{SP}{Q_{2,TPC}}","v_{2}{2}"};
  TString pidInPads[npad]={"Ch. hadrons","#pi^{#pm}","p","h^{#pm}","#pi^{+}","p"};
  TFile *input[nenergy][2];
  TFile *inputFlowANA = new TFile("v2_UrQMD_7.7GeV_V2R1.root","read");
  TFile *inputScalarProduct = new TFile("v2_UrQMD_7.7GeV_V2SP.root","read");
  TGraphErrors *grV2[nenergy][npid][nmethod];
  TGraphErrors *grRatioV2[nenergy][npid][nmethod];

  for (int id=0;id<npid;id++){
    grV2[0][id][0] = (TGraphErrors*)inputFlowANA->Get(Form("grv22fhcal_%i",id));
    grV2[1][id][0] = (TGraphErrors*)inputFlowANA->Get(Form("grv22fhcal_%i",id)); // fake
  }
  for (int id=0;id<npid;id++){
    grV2[0][id][3] = (TGraphErrors*)inputScalarProduct->Get(Form("gr_rebinned_cent_10_40_pv2TPC_pid%i",id));
    grV2[1][id][3] = (TGraphErrors*)inputScalarProduct->Get(Form("gr_rebinned_cent_10_40_pv2TPC_pid%i",id)); // fake
  
  }
  for (int ien=0;ien<nenergy;ien++){
    input[ien][0] = new TFile(Form("v2_UrQMD_%sGeV.root",energy[ien].Data()),"read");
    input[ien][1] = new TFile(Form("v2_UrQMD_%sGeV_8PID.root",energy[ien].Data()),"read");
    for (int id=0;id<npid;id++){

      if (id==0 || id==1 || id==2) {
        grV2[ien][id][1] = (TGraphErrors*)input[ien][0]->Get(Form("gr_cent10-40_1_%i",id)); // v24
        grV2[ien][id][2] = (TGraphErrors*)input[ien][0]->Get(Form("gr_cent10-40_2_%i",id)); // v2EP TPC
        grV2[ien][id][4] = (TGraphErrors*)input[ien][0]->Get(Form("gr_cent10-40_3_%i",id)); // v22Gap
        
      }else {
        grV2[ien][id][1] = (TGraphErrors*)input[ien][1]->Get(Form("gr_cent10-40_1_%i",id)); // v24
        grV2[ien][id][2] = (TGraphErrors*)input[ien][1]->Get(Form("gr_cent10-40_2_%i",id)); // v2EP TPC
        grV2[ien][id][4] = (TGraphErrors*)input[ien][1]->Get(Form("gr_cent10-40_3_%i",id)); // v22Gap
      }
    }
  }
  
  for (int ien=0;ien<nenergy;ien++){
    for (int id=0;id<npid;id++){

      grV2[ien][id][0] -> SetMarkerColor(kBlue+1);
      grV2[ien][id][0] -> SetLineColor(kBlue+1);
      grV2[ien][id][0] -> SetMarkerStyle(kOpenTriangleUp);

      grV2[ien][id][1] -> SetMarkerColor(kRed+1);
      grV2[ien][id][1] -> SetLineColor(kRed+1);
      grV2[ien][id][1] -> SetMarkerStyle(kFullCircle);  

      grV2[ien][id][2] -> SetMarkerColor(kBlack);
      grV2[ien][id][2] -> SetLineColor(kBlack);
      grV2[ien][id][2] -> SetMarkerStyle(kFullCross);

      grV2[ien][id][3] -> SetMarkerColor(kGreen+3);
      grV2[ien][id][3] -> SetLineColor(kGreen+3);
      grV2[ien][id][3] -> SetMarkerStyle(kOpenCircle);

      grV2[ien][id][4] -> SetMarkerColor(kBlack);
      grV2[ien][id][4] -> SetLineColor(kBlack);
      grV2[ien][id][4] -> SetMarkerStyle(kOpenSquare);
      for (int imeth=0;imeth<nmethod;imeth++){
        grV2[ien][id][imeth] -> SetMarkerSize(markerSize);
      }
    }
  }
  
  Double_t *vx_gr[nenergy][npid][nmethod], *vy_gr[nenergy][npid][nmethod], *ex_gr[nenergy][npid][nmethod], *ey_gr[nenergy][npid][nmethod];
  Int_t nbins[nenergy][npid][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int id=0;id<npid;id++){
      for (int imeth=0;imeth<nmethod;imeth++){
        // Read points
        vx_gr[ien][id][imeth]=(Double_t*)grV2[ien][id][imeth]->GetX();
        vy_gr[ien][id][imeth]=(Double_t*)grV2[ien][id][imeth]->GetY();

        // Read errors
        ex_gr[ien][id][imeth]=(Double_t*)grV2[ien][id][imeth]->GetEX();
        ey_gr[ien][id][imeth]=(Double_t*)grV2[ien][id][imeth]->GetEY();

        nbins[ien][id][imeth]=(Int_t) grV2[ien][id][imeth]->GetN();
      }
    }
  }
  
  for (int ien=0;ien<nenergy-1;ien++){
    for (int id=0;id<npid;id++){
      for (int imeth=0;imeth<nmethod;imeth++){
        std::vector<Double_t> vRatioToV22, vRatioToV22Err;  
        for (int i=0;i<nbins[ien][id][ratioToMethod];i++){
          Double_t ratio = vy_gr[ien][id][imeth][i]/vy_gr[ien][id][ratioToMethod][i];
          Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][id][ratioToMethod][i]/vy_gr[ien][id][ratioToMethod][i],2)+TMath::Power(ey_gr[ien][id][imeth][i]/vy_gr[ien][id][imeth][i],2)));
          vRatioToV22.push_back(ratio);
          vRatioToV22Err.push_back(ratioErr);
        }
        grRatioV2[ien][id][imeth] = new TGraphErrors(nbins[ien][id][ratioToMethod],vx_gr[ien][id][ratioToMethod],&vRatioToV22[0],ex_gr[ien][id][ratioToMethod],&vRatioToV22Err[0]);
        grRatioV2[ien][id][imeth] -> SetTitle(Form("%s",ratioName[imeth].Data()));
        vRatioToV22.clear();
        vRatioToV22Err.clear();
      }

      grRatioV2[ien][id][0] -> SetMarkerColor(kBlue+1);
      grRatioV2[ien][id][0] -> SetLineColor(kBlue+1);
      grRatioV2[ien][id][0] -> SetMarkerStyle(kOpenTriangleUp);

      grRatioV2[ien][id][1] -> SetMarkerColor(kRed+1);
      grRatioV2[ien][id][1] -> SetLineColor(kRed+1);
      grRatioV2[ien][id][1] -> SetMarkerStyle(kFullCircle);

      grRatioV2[ien][id][2] -> SetMarkerColor(kBlack);
      grRatioV2[ien][id][2] -> SetLineColor(kBlack);
      grRatioV2[ien][id][2] -> SetMarkerStyle(kFullCross);

      grRatioV2[ien][id][3] -> SetMarkerColor(kGreen+3);
      grRatioV2[ien][id][3] -> SetLineColor(kGreen+3);
      grRatioV2[ien][id][3] -> SetMarkerStyle(kOpenCircle);

      grRatioV2[ien][id][4] -> SetMarkerColor(kBlack);
      grRatioV2[ien][id][4] -> SetLineColor(kBlack);
      grRatioV2[ien][id][4] -> SetMarkerStyle(kOpenSquare);

      for (int imeth=0;imeth<nmethod;imeth++){
        grRatioV2[ien][id][imeth]->SetMarkerSize(markerSize);
      }    
    }
  }
  

  TCanvas *can = new TCanvas("can","",200,10,2000,1000);
  can->SetLeftMargin(0.15);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.2);
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gStyle->SetPalette(kDarkRainBow);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(3,2,0,0);
  TH2F *h[npad];
  for (int ipad=0;ipad<6;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;v_{2} ",xAxisName.Data()),1,minpt,maxpt,1,minV2,maxV2);
    if (ipad==1 || ipad==2) h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2,maxV2);
    if (ipad==3) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";;Ratio to v_{2}{2}    ",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    if (ipad==4) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s           ;",xAxisName.Data()),1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    if (ipad==5) h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    if (ipad>=npad/2){
      h[ipad]->GetXaxis()->SetLabelSize(labelSizeLowerPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeLowerPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeLowerPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeLowerPlot);
    }else{
      h[ipad]->GetXaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeUpperPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeUpperPlot);
    }

    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(titleOffset);

    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);


    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(titleOffset);
    h[ipad]->Draw();
    
    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(33); 
    if (ipad<3) {
      tex.SetTextSize(labelSizeUpperPlot); 
      tex.DrawLatex(0.2,maxV2*0.9,padName[ipad].Data());
    }else {
      tex.SetTextSize(labelSizeLowerPlot);
      tex.DrawLatex(0.2,maxV2Ratio*0.97,padName[ipad].Data());
    }
    TLatex tex1;
    tex1.SetTextFont(textFont);
    tex1.SetTextAlign(33);
    tex1.SetTextSize(labelSizeUpperPlot+0.02);
    tex1.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("%s",pidInPads[ipad].Data()));
    if (ipad==0) {
      tex.DrawLatex(maxpt*0.97,maxV2*0.9,Form("Au+Au at #sqrt{s_{NN}}=%s GeV, 10-40%%",energy[0].Data()));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot);
      leg_pt->SetTextFont(textFont);
      // for (int imeth=0;imeth<nmethod;imeth++){
      //   leg_pt->AddEntry(grV2[0][0][imeth],legendEntries[imeth].Data(),"p");
      // }
      leg_pt->AddEntry(grV2[0][0][0],legendEntries[0].Data(),"p");
      leg_pt->AddEntry(grV2[0][0][2],legendEntries[2].Data(),"p");
      leg_pt->Draw();
    }
    if (ipad==1) {
      tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("UrQMD                             "));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot);
      leg_pt->SetTextFont(textFont);
      leg_pt->AddEntry(grV2[0][0][1],legendEntries[1].Data(),"p");
      leg_pt->AddEntry(grV2[0][0][4],legendEntries[4].Data(),"p");
      leg_pt->Draw();
    }
    if (ipad==2) {
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot);
      leg_pt->SetTextFont(textFont);
      leg_pt->AddEntry(grV2[0][0][3],legendEntries[3].Data(),"p");
      leg_pt->Draw();
    }

    TLine lineOne;
    lineOne.SetLineStyle(2);
    if (ipad>2)lineOne.DrawLine(minpt,1.,maxpt,1.);
    
    for (int imeth=1;imeth<nmethod;imeth++){
      if (ipad==0) grV2[0][0][imeth]->Draw("P");
      if (ipad==1) grV2[0][1][imeth]->Draw("P");
      if (ipad==2) grV2[0][3][imeth]->Draw("P");
    }
    for (int imeth=1;imeth<nmethod;imeth++){
      if (ipad==3) grRatioV2[0][0][imeth]->Draw("P");
      if (ipad==4) grRatioV2[0][1][imeth]->Draw("P");
      if (ipad==5) grRatioV2[0][3][imeth]->Draw("P");
    }
    if (ipad==0) grV2[0][0][0]->Draw("P");
    if (ipad==1) grV2[0][1][0]->Draw("P");
    if (ipad==2) grV2[0][3][0]->Draw("P");  
    if (ipad==3) grRatioV2[0][0][0]->Draw("P");
    if (ipad==4) grRatioV2[0][1][0]->Draw("P");
    if (ipad==5) grRatioV2[0][3][0]->Draw("P");

  }
  


  // can->SaveAs(Form("Figure_1_Compare_methods_v2pt.eps"));
  can->SaveAs(Form("Figure_1_Compare_methods_v2pt.pdf"));
  // can->SaveAs(Form("Figure_1_Compare_methods_v2pt.C"));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("Figure_1_Compare_methods_v2pt.png"));

}