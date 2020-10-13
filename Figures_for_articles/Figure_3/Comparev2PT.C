void Comparev2PT(){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22
  const int nlevel = 2; // UrQMD, GEANT, Reco
  const int ncent = 7; // 0-10,10-20,20-30,30-40,40-50,10-40,v2vscent
  const int nenergy = 2;
  const int nmethod = 3; // v24, v2(eta-sub), v22(eta-gap)

  const double mincent = 0.;  // for v2 vs centrality
  const double maxcent = 60.; // for v2 vs centrality


  const float minpt = -0.05;
  const float maxpt = 2.35;
  const float maxV2 = 0.16;
  const float minV2 = -0.01;

  const double minV2int = -0.005; // for v2 vs centrality plotting
  const double maxV2int = 0.1; // for v2 vs centrality plotting
  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.2; // for v2 vs pt plotting
  TString model = {"UrQMD"};
  TString energy[nenergy] = {"7.7GeV","11.5GeV"};
  TString xAxisName = {"p_{T} (GeV/c)"};
  TString legendEntries[nlevel]={"True","Reco"};
  TString padName[6]={"(a)","(b)","(c)","(d)","(e)","(f)"};
  const float leg_coordinate[4]={0.68,0.07,0.99,0.3}; // top left: 0.28,0.7,0.6,0.99
  const float labelSizeUpperPlot = 0.115;
  const float titleSizeUpperPlot = 0.135;
  const float labelSizeLowerPlot = 0.09;
  const float titleSizeLowerPlot = 0.11;

  TString graphTitle[6]={"v_{2}{4}","v_{2}{2}","v_{2}{#Psi_{2,TPC}^{}}","v_{2}{4}","v_{2}{2}","v_{2}{#Psi_{2,TPC}^{}}"};

  // const pair<float,float> ratio={0.82,1.18};
  TFile *input[nlevel][nenergy];
  TGraphErrors *grV2[2][nlevel][nmethod][nenergy];
  char hname[400];
  TString method[nlevel]={"Model","Reco"};
  for (int i=0;i<nenergy;i++){
    input[0][i] = new TFile(Form("v2_%s_%s.root",model.Data(),energy[i].Data()),"read");
    input[1][i] = new TFile(Form("v2_%s_%s_Reco_MotherID.root",model.Data(),energy[i].Data()),"read");
  }
  for (int ilev=0; ilev<nlevel; ilev++){
    for (int imeth=0;imeth<nmethod;imeth++){
      for (int ien=0;ien<nenergy;ien++){
      grV2[0][ilev][imeth][ien] = (TGraphErrors*)input[ilev][ien]->Get(Form("gr_cent10-40_%i_2",imeth+1));
      grV2[1][ilev][imeth][ien] = (TGraphErrors*)input[ilev][ien]->Get(Form("grRF_%i_2",imeth+1));
      }
    }
  }
  for (int imeth=0;imeth<nmethod;imeth++){
    for (int i=0;i<2;i++){
      for (int ien=0;ien<nenergy;ien++){
        grV2[i][0][imeth][ien]->SetMarkerStyle(kOpenSquare);
        grV2[i][0][imeth][ien]->SetMarkerColor(kRed+1);
        grV2[i][0][imeth][ien]->SetLineColor(kRed+1);

        grV2[i][1][imeth][ien]->SetMarkerStyle(kFullCircle);
        grV2[i][1][imeth][ien]->SetMarkerColor(kBlue+1);
        grV2[i][1][imeth][ien]->SetLineColor(kBlue+1);
        // grV2[i][2][imeth]->SetMarkerStyle(kFullTriangleUp);
        // grV2[icent][3][imeth]->SetMarkerStyle(kFullCircle); // kOpenCircle
        for (int ilev=0;ilev<nlevel;ilev++){
          grV2[i][ilev][imeth][ien] -> SetMarkerSize(1.9);
          // grV2[i][ilev][imeth] -> SetMarkerColor(1);
          // grV2[i][ilev][imeth] -> SetLineColor(1);
        }
      }
    }
  }
  cout << "error here" << endl;

  TCanvas *can = new TCanvas("can","",200,10,2000,850);
  can->SetLeftMargin(0.16);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.22);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // gStyle->SetPalette(kBird);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(3,2,0,0);
  TH2F *h[6];
  for (int ipad=0;ipad<6;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";;v_{2} "),1,minpt,maxpt,1,minV2,maxV2);
    else if (ipad==4) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s             ;v_{2}",xAxisName.Data()),1,minpt,maxpt,1,minV2,maxV2);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2,maxV2);
    
    if (ipad>=3){
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


    h[ipad]->GetXaxis()->SetLabelFont(42);
    h[ipad]->GetYaxis()->SetLabelFont(42);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.9);

    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(0.7);
    h[ipad]->Draw();
    
    TLatex tex;
    tex.SetTextFont(42);
    tex.SetTextAlign(33);
    if (ipad<=2) tex.SetTextSize(labelSizeUpperPlot);
    else tex.SetTextSize(labelSizeLowerPlot);
    tex.DrawLatex(0.2,maxV2*0.95,padName[ipad].Data());
    tex.DrawLatex(maxpt*0.95,maxV2*0.95-0.025,Form("%s",graphTitle[ipad].Data()));
    if (ipad==0) {
      tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("Au+Au at #sqrt{s_{NN}}=%s",energy[0].Data()));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(42);
      leg_pt->SetTextSize(labelSizeUpperPlot);
      for (int ilev=0; ilev<nlevel; ilev++){
        leg_pt->AddEntry(grV2[0][ilev][0][0],legendEntries[ilev].Data(),"p");
      }
      leg_pt->Draw();
    }else if (ipad==1) {
      tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("10-40%%, UrQMD, K^{#pm}"));
    }else if (ipad==3) {
      tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("#sqrt{s_{NN}}=%s",energy[1].Data()));
    }



    
    for (int ilev=0;ilev<nlevel;ilev++){

        if (ipad==0) grV2[0][ilev][0][0]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (ipad==1) grV2[0][ilev][2][0]->Draw("P"); // PZ
        if (ipad==2) grV2[0][ilev][1][0]->Draw("P");
        if (ipad==3) grV2[0][ilev][0][1]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (ipad==4) grV2[0][ilev][2][1]->Draw("P"); // PZ
        if (ipad==5) grV2[0][ilev][1][1]->Draw("P");
    }
    // cout << "error here" << endl;
  }
  can->SaveAs(Form("Figure_3_Performance_v2pt_kaons.pdf"));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("Figure_3_Performance_v2pt_kaons.png"));

  
}