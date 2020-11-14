void CompareV2PT(){
  gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // const
  const int nenergy = 2; // 7.7, 11.5 GeV
  // const int nmodel = 3; // vHLLE+UrQMD, UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const int npid = 4; // CH, pions, kaons, protons
  const float minpt = -0.05;
  const float maxpt = 2.35;
  const float maxV2 = 0.16;
  const float minV2 = -0.01;
  const float leg_coordinate[4]={0.65,0.01,0.99,0.3}; // top left: 0.28,0.7,0.6,0.99
  const float labelSize = 0.07;
  const float titleSize = 0.1;
  const int npad = 6;
  // flags
  const int pid = 1; // v2 for: 0: CH; 1: Pions; 2: Kaons; 3: (Anti)protons
  // some stuffs
  TString energy[nenergy]={"7.7","11.5"};
  TString leg_header[nenergy] = {"7.7 GeV","11.5 GeV"};

  TString grFancyTitle[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{#eta-sub}","v_{2}{2,|#{Delta}|>0.1}"}; //#{eta}
  TString grTitle[nmethod]={"v22","v24","v2etasub","v22etagap"};
  TString pidFancyNames[npid] = {"Charged hadrons", "Pions", "Kaons", "(Anti)protons"};
  TString xAxisName = {"p_{T} [GeV/c]"};
  TString legendEntries[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{2,|#Delta#eta|>0.1}","v_{2}{#eta-sub,EP} TPC"}; // ,"v_2{EP} FHCal
  TString energyInPads[npad]={"7.7","7.7","7.7","11.5","11.5","11.5"};
  TString pidInPads[npad]={"h^{#pm}","#pi^{+}","p","h^{#pm}","#pi^{+}","p"};
  TFile *input[nenergy][2];
  TGraphErrors *grV2[nenergy][npid][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    input[ien][0] = new TFile(Form("v2_UrQMD_%sGeV_Reco_MotherID.root",energy[ien].Data()),"read");
    input[ien][1] = new TFile(Form("v2_UrQMD_%sGeV_Reco_MotherID_8PID.root",energy[ien].Data()),"read");
    for (int id=0;id<npid;id++){
      for (int imeth=0;imeth<nmethod;imeth++){ // v24 = 1; v22(eta-gap) = 3
      // grV2[ien][id][imeth] = (TGraphErrors*)input[ien][0]->Get(Form("gr_cent10-40_%i_%i",imeth,id));
        if (id==0) grV2[ien][id][imeth] = (TGraphErrors*)input[ien][0]->Get(Form("gr_cent10-40_%i_%i",imeth,id));
        else grV2[ien][id][imeth] = (TGraphErrors*)input[ien][1]->Get(Form("gr_cent10-40_%i_%i",imeth,id));
      }
    }
  }

  for (int ien=0;ien<nenergy;ien++){
    for (int id=0;id<npid;id++){
      grV2[ien][id][1] -> SetMarkerColor(kRed);
      grV2[ien][id][1] -> SetLineColor(kRed);

      grV2[ien][id][2] -> SetMarkerColor(kBlue);
      grV2[ien][id][2] -> SetLineColor(kBlue);
      grV2[ien][id][2] -> SetMarkerStyle(kOpenCircle);

      grV2[ien][id][3] -> SetMarkerColor(kGreen+2);
      grV2[ien][id][3] -> SetLineColor(kGreen);
      grV2[ien][id][3] -> SetMarkerStyle(kFullTriangleUp);
      for (int imeth=0;imeth<nmethod;imeth++){
        // grV2[ien][id][imeth] -> SetMarkerStyle(kFullCircle);
        grV2[ien][id][imeth] -> SetMarkerSize(1.5);
      }
    }
  }

  TCanvas *can = new TCanvas("can","",200,10,1000,600);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.2);
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
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;v_{2}              ",xAxisName.Data()),1,minpt,maxpt,1,minV2,maxV2);
    else if (ipad==4) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s         ;v_{2}",xAxisName.Data()),1,minpt,maxpt,1,minV2,maxV2);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2,maxV2);
    
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(1.);

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(1.);
    h[ipad]->Draw();
    
    TLatex tex;
    tex.SetTextFont(42);
    tex.SetTextAlign(33);
    tex.SetTextSize(labelSize);
    if (ipad==0) {
      tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("#splitline{UrQMD, Au+Au, centrality 10-40%%}{%s @ #sqrt{s_{NN}}=%s GeV}",pidInPads[ipad].Data(),energyInPads[ipad].Data()));
    }else{
      tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("%s @ #sqrt{s_{NN}}=%s GeV",pidInPads[ipad].Data(),energyInPads[ipad].Data()));
    }
    if (ipad==0){
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSize);
      // leg_pt->SetHeader(leg_header[0].Data(),"C");
      for (int imeth=1;imeth<nmethod;imeth++){
        leg_pt->AddEntry(grV2[0][0][imeth],legendEntries[imeth].Data(),"p");
      }
      leg_pt->Draw();
    }

    
    for (int imeth=1;imeth<nmethod;imeth++){

        if (ipad==0) grV2[0][0][imeth]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (ipad==1) grV2[0][1][imeth]->Draw("P");
        if (ipad==2) grV2[0][3][imeth]->Draw("P");
        if (ipad==3) grV2[1][0][imeth]->Draw("P");
        if (ipad==4) grV2[1][1][imeth]->Draw("P");
        if (ipad==5) grV2[1][3][imeth]->Draw("P");
    }
  }
  
  // TLine lineOne;
  // lineOne.SetLineStyle(2);
  // lineOne.DrawLine(minpt,1.,maxpt,1.);

  can->SaveAs(Form("v2pt_Reco.png"));


}
// 8 (965) 354-26-87 