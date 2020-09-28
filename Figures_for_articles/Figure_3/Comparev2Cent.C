void Comparev2Cent(){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22
  static const int nlevel = 2; // UrQMD, GEANT, Reco
  static const int ncent = 7; // 0-10,10-20,20-30,30-40,40-50,10-40,v2vscent
  const int nmethod = 3; // v24, v2(eta-sub), v22(eta-gap)

  const double mincent = -1;  // for v2 vs centrality
  const double maxcent = 63.; // for v2 vs centrality


  const float maxV2 = 0.07;
  const float minV2 = 0.0;

  TString model = {"UrQMD"};
  TString energy = {"7.7GeV"};
  TString xAxisName = {"Centrality [%]"};
  TString levelName= (TString) Form("%s, Au+Au@#sqrt{s_{NN}}=%s",model.Data(),energy.Data());
  TString legendEntries[nlevel]={"True","Reco"};
  const float leg_coordinate[4]={0.8,0.25,0.99,0.4}; // top left: 0.28,0.7,0.6,0.99
  const float labelSize = 0.07;
  const float titleSize = 0.1;

  TString graphTitle[nmethod]={"v_{2}{4}","v_{2}{#eta-sub,EP}","v_{2}{2,|#Delta#eta>0.1|}"};

  // const pair<float,float> ratio={0.82,1.18};
  TFile *input[nlevel];
  TGraphErrors *grV2[2][nlevel][nmethod];
  char hname[400];
  TString method[nlevel]={"Model","Reco"};
  input[0] = new TFile(Form("v2_%s_%s.root",model.Data(),energy.Data()),"read");
  input[1] = new TFile(Form("v2_%s_%s_Reco_MotherID.root",model.Data(),energy.Data()),"read");
  // input[2] = new TFile(Form("v2_%s_%s_MC.root",model.Data(),energy.Data()),"read");
  for (int ilev=0; ilev<nlevel; ilev++){
    for (int imeth=0;imeth<nmethod;imeth++){
      grV2[0][ilev][imeth] = (TGraphErrors*)input[ilev]->Get(Form("gr_cent10-40_%i_0",imeth+1));
      // grV2[0][ilev][imeth] -> SetTitle(Form("%s;p_{T} [GeV/c];%s",method[i].Data(),graphTitle[meth].Data()));
      grV2[1][ilev][imeth] = (TGraphErrors*)input[ilev]->Get(Form("grRF_%i_0",imeth+1));
      // grV2[1][ilev][imeth] -> SetTitle(Form("%s;centrality [%%];%s",method[i].Data(),graphTitle[meth].Data()));
    }
  }
  for (int imeth=0;imeth<nmethod;imeth++){
    for (int i=0;i<2;i++){
      grV2[i][0][imeth]->SetMarkerStyle(kOpenSquare);
      grV2[i][1][imeth]->SetMarkerStyle(kFullCircle);
      // grV2[i][2][imeth]->SetMarkerStyle(kFullTriangleUp);
      // grV2[icent][3][imeth]->SetMarkerStyle(kFullCircle); // kOpenCircle
      for (int ilev=0;ilev<nlevel;ilev++){
        grV2[i][ilev][imeth] -> SetMarkerSize(1.9);
        grV2[i][ilev][imeth] -> SetMarkerColor(1);
        grV2[i][ilev][imeth] -> SetLineColor(1);
      }
    }
  }


  TCanvas *can = new TCanvas("can","",200,10,2000,600);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.2);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // gStyle->SetPalette(kBird);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(3,1,0,0);
  TH2F *h[nmethod];
  for (int imeth=0;imeth<nmethod;imeth++){
    can->cd(imeth+1);
    if (imeth==0) h[imeth] = new TH2F(Form("pad_%i",imeth+1),Form(";;v_{2}        "),1,mincent,maxcent,1,minV2,maxV2);
    else if (imeth==1) h[imeth] = new TH2F(Form("pad_%i",imeth+1),Form(";%s         ;v_{2}",xAxisName.Data()),1,mincent,maxcent,1,minV2,maxV2);
    else h[imeth] = new TH2F(Form("pad_%i",imeth+1),"",1,mincent,maxcent,1,minV2,maxV2);
    
    h[imeth]->GetXaxis()->SetLabelSize(labelSize);
    h[imeth]->GetXaxis()->SetTitleSize(titleSize);
    h[imeth]->GetXaxis()->SetNdivisions(504);
    h[imeth]->GetXaxis()->SetTitleOffset(1.);

    h[imeth]->GetYaxis()->SetLabelSize(labelSize);
    h[imeth]->GetYaxis()->SetTitleSize(titleSize);
    h[imeth]->GetYaxis()->SetNdivisions(504);
    h[imeth]->GetYaxis()->SetTitleOffset(1.);
    h[imeth]->Draw();
    
    TLatex tex;
    tex.SetTextFont(42);
    tex.SetTextAlign(33);
    tex.SetTextSize(labelSize);
    if (imeth==0) {
      tex.DrawLatex(maxcent*0.95,maxV2*0.95,Form("UrQMD, Au+Au @ #sqrt{s_{NN}}=%s",energy.Data()));
      tex.DrawLatex(maxcent*0.95,maxV2*0.95-0.01,Form("Charged Hadrons, 0.2<p_{T}<3.0 GeV/c"));
      tex.DrawLatex(maxcent*0.95,maxV2*0.95-0.01*2,Form("%s",graphTitle[imeth].Data()));
    }else{
      tex.DrawLatex(maxcent*0.9,maxV2*0.9,Form("%s",graphTitle[imeth].Data()));
    }
    if (imeth==0){
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSize);
      for (int ilev=0; ilev<nlevel; ilev++){
        leg_pt->AddEntry(grV2[1][ilev][0],legendEntries[ilev].Data(),"p");
      }
      leg_pt->Draw();
    }

    
    for (int ilev=0;ilev<nlevel;ilev++){

        if (imeth==0) grV2[1][ilev][0]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (imeth==1) grV2[1][ilev][1]->Draw("P");
        if (imeth==2) grV2[1][ilev][2]->Draw("P");

    }
  }
  can->SaveAs(Form("Performance_v2cent_%s.png",energy.Data()));

  
}