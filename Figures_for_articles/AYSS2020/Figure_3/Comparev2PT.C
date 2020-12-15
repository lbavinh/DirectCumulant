void Comparev2PT(){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22
  const int nlevel = 2; // UrQMD, GEANT, Reco
  const int ncent = 7; // 0-10,10-20,20-30,30-40,40-50,10-40,v2vscent
  const int nenergy = 2;
  const int nmethod = 5; // v24, v2(eta-sub), v22(eta-gap), v2SP TPC, v2EP FHCal

  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality
  const float textFont = 132;

  const float minpt = -0.05;
  const float maxpt = 2.35;
  const float maxV2 = 0.13;
  const float minV2 = -0.01;

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.2; // for v2 vs pt plotting
  TString model = {"UrQMD"};
  TString energy[nenergy] = {"7.7GeV","11.5GeV"};
  TString xAxisName = {"#it{p_{T}} (GeV/c)"};
  TString legendEntries[nlevel]={"open - reco","filled - true"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)"};
  const float leg_coordinate[4]={0.4,0.05,0.99,0.35}; // top left: 0.28,0.7,0.6,0.99
  const float labelSizeUpperPlot = 0.13;
  const float labelSizeLowerPlot = 0.105;
  const float titleSizeUpperPlot = 0.13;
  const float titleSizeLowerPlot = 0.105;
  TGraphErrors *grV2[2][nlevel][nmethod][nenergy];
  TString graphTitle[]={"#it{v}_{2}{4}","#it{v}_{2}{#Psi_{2,TPC}}","#it{v}_{2}{2}","#it{v}_{2}^{SP}{Q_{2,TPC}}","#it{v}_{2}{#Psi_{1,FHCal}}"};

  TFile *input1[2][2][2]; // [model,reco][v2SP,v2EPFHCal][77,115]
  input1[0][0][0] = new TFile("v2_UrQMD_7.7GeV_V2SP.root","read");
  input1[1][0][0] = new TFile("v2_Reco_UrQMD_7.7GeV_V2SP.root","read");
  input1[0][0][1] = new TFile("v2_UrQMD_11.5GeV_V2SP.root","read");
  input1[1][0][1] = new TFile("v2_Reco_UrQMD_11.5GeV_V2SP.root","read");

  input1[0][1][0] = new TFile("v2_graphs_V2R1_7.7.root","read");
  input1[1][1][0] = new TFile("v2_graphs_V2R1_7.7_Reco.root","read");
  input1[0][1][1] = new TFile("v2_graphs_V2R1_11.5.root","read");
  input1[1][1][1] = new TFile("v2_graphs_V2R1_11.5_Reco.root","read");

  for (int i=0;i<2;i++){
    for (int ilev=0; ilev<nlevel; ilev++){
      for (int ien=0;ien<nenergy;ien++){
        grV2[i][ilev][3][ien] = (TGraphErrors*)input1[ilev][0][ien]->Get("gr_rebinned_cent_10_40_pv2TPC_pid0");
        grV2[i][ilev][4][ien] = (TGraphErrors*)input1[ilev][1][ien]->Get("grv22fhcal_0");
      }
    }
  }
  // const pair<float,float> ratio={0.82,1.18};
  TFile *inputPeter = new TFile("graphs_reco_vs_geant.root","read");
  for (int i=0;i<2;i++){
  grV2[i][0][4][0] = (TGraphErrors*)inputPeter->Get("gr_v2_FHCalEp_mc");
  grV2[i][1][4][0] = (TGraphErrors*)inputPeter->Get("gr_v2_FHCalEp_reco");
  }
  TFile *inputPeter115GeV = new TFile("graphs_fhcal_11.5gev_hadrons.root","read");
  for (int i=0;i<2;i++){
  grV2[i][0][4][1] = (TGraphErrors*)inputPeter115GeV->Get("gr_v2_FHCalEp_mc");
  grV2[i][1][4][1] = (TGraphErrors*)inputPeter115GeV->Get("gr_v2_FHCalEp_reco");
  }
  TFile *input[nlevel][nenergy];
  char hname[400];
  for (int i=0;i<nenergy;i++){
    input[0][i] = new TFile(Form("v2_%s_%s.root",model.Data(),energy[i].Data()),"read");
    input[1][i] = new TFile(Form("v2_%s_%s_Reco_MotherID.root",model.Data(),energy[i].Data()),"read");
  }

  for (int ilev=0; ilev<nlevel; ilev++){
    for (int imeth=0;imeth<nmethod-2;imeth++){
      for (int ien=0;ien<nenergy;ien++){
      grV2[0][ilev][imeth][ien] = (TGraphErrors*)input[ilev][ien]->Get(Form("gr_cent10-40_%i_0",imeth+1));
      grV2[1][ilev][imeth][ien] = (TGraphErrors*)input[ilev][ien]->Get(Form("grRF_%i_0",imeth+1));
      }
    }
  }
  for (int i=0;i<2;i++){
  grV2[i][0][1][0] = (TGraphErrors*)inputPeter->Get("gr_v2_TpcEp_mc");
  grV2[i][1][1][0] = (TGraphErrors*)inputPeter->Get("gr_v2_TpcEp_reco");  
  }
  // for (int imeth=0;imeth<nmethod;imeth++){
    for (int i=0;i<2;i++){
      for (int ien=0;ien<nenergy;ien++){
        grV2[i][0][0][ien]->SetMarkerStyle(kFullSquare);
        grV2[i][1][0][ien]->SetMarkerStyle(kOpenSquare);
        for (int ilev=0; ilev<nlevel; ilev++){
        grV2[i][ilev][0][ien]->SetMarkerColor(kBlue+1);
        grV2[i][ilev][0][ien]->SetLineColor(kBlue+1);
        }
        grV2[i][0][2][ien]->SetMarkerStyle(kFullTriangleUp);
        grV2[i][1][2][ien]->SetMarkerStyle(kOpenTriangleUp);
        for (int ilev=0; ilev<nlevel; ilev++){
        grV2[i][ilev][2][ien]->SetMarkerColor(kRed+1);
        grV2[i][ilev][2][ien]->SetLineColor(kRed+1);
        }
        
        grV2[i][0][1][ien]->SetMarkerStyle(kFullCircle);
        grV2[i][1][1][ien]->SetMarkerStyle(kOpenCircle);
        for (int ilev=0; ilev<nlevel; ilev++){
        grV2[i][ilev][1][ien]->SetMarkerColor(kGreen+2);
        grV2[i][ilev][1][ien]->SetLineColor(kGreen+2);
        }

        grV2[i][0][3][ien]->SetMarkerStyle(kFullTriangleDown);
        grV2[i][1][3][ien]->SetMarkerStyle(kOpenTriangleDown);
        for (int ilev=0; ilev<nlevel; ilev++){
        grV2[i][ilev][3][ien]->SetMarkerColor(kCyan+2);
        grV2[i][ilev][3][ien]->SetLineColor(kCyan+2);
        }
        grV2[i][0][4][ien]->SetMarkerStyle(kFullDiamond);
        grV2[i][1][4][ien]->SetMarkerStyle(kOpenDiamond);
        for (int ilev=0; ilev<nlevel; ilev++){
        grV2[i][ilev][4][ien]->SetMarkerColor(kBlack);
        grV2[i][ilev][4][ien]->SetLineColor(kBlack);        
        }
        for (int ilev=0;ilev<nlevel;ilev++){
          for (int imeth=0;imeth<nmethod;imeth++){
            grV2[i][ilev][imeth][ien] -> SetMarkerSize(1.9);
            grV2[i][ilev][4][ien] -> SetMarkerSize(2.5);
          }
        }
      }
    }
  // }

  TCanvas *can = new TCanvas("can","",200,10,2200,850);
  TPaveLabel* title = new TPaveLabel(0.1,0.95,0.9,0.98,"Au+Au, 10-40%, UrQMD, reconstructed (GEANT4), charged hadrons");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.);
  title->Draw();
  can->SetTopMargin(0.14);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.22);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);

  can->Divide(5,2,0,0);
  TH2F *h[10];
  for (int ipad=0;ipad<10;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";;#it{v}_{2} "),1,minpt,maxpt,1,minV2,maxV2);
    else if (ipad==7) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;v_{2}",xAxisName.Data()),1,minpt,maxpt,1,minV2,maxV2);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2,maxV2);
    
    if (ipad>=5){
      h[ipad]->GetXaxis()->SetLabelSize(labelSizeLowerPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeLowerPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeLowerPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeLowerPlot);
    }else{
      h[ipad]->GetXaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeUpperPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeUpperPlot+0.02);
    }

    h[ipad]->GetXaxis()->SetTitleFont(textFont);
    h[ipad]->GetYaxis()->SetTitleFont(textFont);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.9);
    h[ipad]->GetXaxis()->CenterTitle(true);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(0.7);
    h[ipad]->Draw();
    
    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(33);
    if (ipad<=4) tex.SetTextSize(labelSizeUpperPlot);
    else tex.SetTextSize(labelSizeLowerPlot);
    tex.DrawLatex(0.3,maxV2*0.95,padName[ipad].Data());
    // for (int imeth=0; imeth<nmethod; imeth++){
    // tex.DrawLatex(maxpt*0.95,maxV2*0.95-0.025,Form("%s",graphTitle[imeth].Data()));
    // }
    if (ipad==0) {
      tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("#it{#sqrt{s_{NN}}}=%s",energy[0].Data()));
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,"#sqrt{s_{NN}}=7.7 GeV");
      
      TLegend *leg_pt = new TLegend(leg_coordinate[0]+0.05,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->AddEntry("",legendEntries[0].Data(),"");
      leg_pt->AddEntry(grV2[0][0][0][0],graphTitle[0].Data(),"p");
      
        
      leg_pt->Draw();
    }else if (ipad==1) {
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("10-40%%, UrQMD, Ch. hadrons"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);

      leg_pt->AddEntry("",legendEntries[1].Data(),"");
      leg_pt->AddEntry(grV2[0][0][2][0],graphTitle[2].Data(),"p");
      

      leg_pt->Draw();
    }else if (ipad==5) {
      tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("#it{#sqrt{s_{NN}}}=%s",energy[1].Data()));
    }else if (ipad==2) {
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("10-40%%, UrQMD, Ch. hadrons"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]-0.1);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->AddEntry(grV2[0][0][1][0],graphTitle[1].Data(),"p");


      leg_pt->Draw();
    }else if (ipad==3) {
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("10-40%%, UrQMD, Ch. hadrons"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]-0.1);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);

      leg_pt->AddEntry(grV2[0][0][3][0],graphTitle[3].Data(),"p");

      leg_pt->Draw();
    }else if (ipad==4) {
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("10-40%%, UrQMD, Ch. hadrons"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0]-0.05,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]-0.1);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->AddEntry(grV2[0][0][4][0],graphTitle[4].Data(),"p");
      leg_pt->Draw();
    }
    if (ipad==1)tex.DrawLatex(maxpt*0.7,maxV2*0.95,"20M events");
    if (ipad==6)tex.DrawLatex(maxpt*0.7,maxV2*0.95,"10M events");    

    for (int ilev=0;ilev<nlevel;ilev++){

        if (ipad==0) grV2[0][ilev][0][0]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (ipad==1) grV2[0][ilev][2][0]->Draw("P"); // PZ
        if (ipad==2) grV2[0][ilev][1][0]->Draw("P");
        if (ipad==3) grV2[0][ilev][3][0]->Draw("P");
        if (ipad==4) grV2[0][ilev][4][0]->Draw("P");



        if (ipad==5) grV2[0][ilev][0][1]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (ipad==6) grV2[0][ilev][2][1]->Draw("P"); // PZ
        if (ipad==7) grV2[0][ilev][1][1]->Draw("P");
        if (ipad==8) grV2[0][ilev][3][1]->Draw("P");
        if (ipad==9) grV2[0][ilev][4][1]->Draw("P");
    }
    // cout << "error here" << endl;
  }   

  can->SaveAs(Form("Figure_3_Performance_v2pt.pdf"));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("Figure_3_Performance_v2pt.png"));

  
}