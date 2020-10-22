void CompareV2PT_withRatio(){

  // const
  const int ntype = 2; // Good acceptance, Bad acceptance with correction, 
  const int nmethod = 6; // 0:v22, 1:v24, 2:v2 TPC, 3:v22(eta-gap), 4:Peter's v2TPC, 5:Peter's v2FHCal
  const int npid = 1; // CH, pions, kaons, protons
  const float minpt = -0.05;
  const float maxpt = 2.35;
  const float maxV2 = 0.13;
  const float minV2 = -0.01;
  const float minV2Ratio = 0.88;
  const float maxV2Ratio = 1.12;
  const float leg_coordinate[4]={0.45,0.29,0.99,0.3}; // top left: 0.28,0.7,0.6,0.99
  const float labelSizeUpperPlot = 0.1;
  const float titleSizeUpperPlot = 0.12;
  const float labelSizeLowerPlot = 0.08;
  const float titleSizeLowerPlot = 0.1;
  const float markerSize = 1.8;
  const float titleOffset = 0.9;
  const float textFont = 42;
  const int npad = 8;
  // flags
  const int ratioToType = 0; // Good Acceptance
  // some stuffs
  TString typeOfGraphName[ntype]={"open - uniform acceptance","filled - non-uniform acceptance"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)"};
  TString xAxisName[] = {"","p_{T} (GeV/c)            "};
  // TString ratioName[nmethod-1]={"v2FHCal/v22","v24/v22","v2TPC/v22"};
  TString legendEntries[nmethod]={"v_{2}{2}","v_{2}{4}","v_{2}{#Psi_{2,TPC}^{}}","v_{2}{2}","v_{2}^{EP}{#Psi_{2,TPC}^{}}","v_{2}^{EP}{#Psi_{1,FHCal}}"}; // ,"v_2{EP} FHCal
  // TString pidInPads[npad]={"Ch. hadrons","#pi","p","h^{#pm}","#pi^{+}","p"};
  TString fileName[ntype]={"","_AC"};
  TFile *input[ntype];

  TGraphErrors *grV2[ntype][npid][nmethod];
  TGraphErrors *grRatioV2[ntype][npid][nmethod];
  for(int it=0;it<ntype;it++){
    input[it] = new TFile(Form("v2_UrQMD_7.7GeV_Reco_MotherID%s.root",fileName[it].Data()),"read");
    for (int imeth=0;imeth<nmethod;imeth++){
      for(int id=0;id<npid;id++){
        grV2[it][id][imeth] = (TGraphErrors*) input[it] -> Get(Form("gr_cent10-40_%i_%i",imeth,id));
      }
    }
  }

  TFile *inputPeter = new TFile("graphs_acceptance_correction.root","read");
  grV2[0][0][4] = (TGraphErrors*) inputPeter -> Get("gr_v2Tpc_uniform_acceptance");
  grV2[0][0][5] = (TGraphErrors*) inputPeter -> Get("gr_v2FHcal_uniform_acceptance");
  grV2[1][0][4] = (TGraphErrors*) inputPeter -> Get("gr_v2Tpc_nonuniform_acceptance");
  grV2[1][0][5] = (TGraphErrors*) inputPeter -> Get("gr_v2FHcal_nonuniform_acceptance");

  // for (int imeth=0;imeth<nmethod;imeth++){
    for (int id=0;id<npid;id++){


      grV2[0][id][1] -> SetMarkerStyle(kOpenSquare);
      grV2[1][id][1] -> SetMarkerStyle(kFullSquare);
      for(int it=0;it<ntype;it++){
        grV2[it][id][1] -> SetMarkerColor(kBlue+1);
        grV2[it][id][1] -> SetLineColor(kBlue+1);
      }

      grV2[0][id][3] -> SetMarkerStyle(kOpenCircle);
      grV2[1][id][3] -> SetMarkerStyle(kFullCircle);
      for(int it=0;it<ntype;it++){
        grV2[it][id][3] -> SetMarkerColor(kRed+1);
        grV2[it][id][3] -> SetLineColor(kRed+1);
      }

      grV2[0][id][4] -> SetMarkerStyle(kOpenTriangleUp);
      grV2[1][id][4] -> SetMarkerStyle(kFullTriangleUp);
      for(int it=0;it<ntype;it++){
        grV2[it][id][4] -> SetMarkerColor(kGreen+2);
        grV2[it][id][4] -> SetLineColor(kGreen+2);
      } 

      grV2[0][id][5] -> SetMarkerStyle(kOpenTriangleDown);
      grV2[1][id][5] -> SetMarkerStyle(kFullTriangleDown);
      for(int it=0;it<ntype;it++){
        grV2[it][id][5] -> SetMarkerColor(kBlack);
        grV2[it][id][5] -> SetLineColor(kBlack);
      }

      for(int it=0;it<ntype;it++){
        for (int imeth=0;imeth<nmethod;imeth++){
        grV2[it][id][imeth] -> SetMarkerSize(markerSize);
        }
      }
    }
  // }
  
  Double_t *vx_gr[ntype][npid][nmethod], *vy_gr[ntype][npid][nmethod], *ex_gr[ntype][npid][nmethod], *ey_gr[ntype][npid][nmethod];
  Int_t nbins[ntype][npid][nmethod];
  for (int itype=0;itype<ntype;itype++){
    for (int id=0;id<npid;id++){
      for (int imeth=0;imeth<nmethod;imeth++){
        // Read points
        vx_gr[itype][id][imeth]=(Double_t*)grV2[itype][id][imeth]->GetX();
        vy_gr[itype][id][imeth]=(Double_t*)grV2[itype][id][imeth]->GetY();

        // Read errors
        ex_gr[itype][id][imeth]=(Double_t*)grV2[itype][id][imeth]->GetEX();
        ey_gr[itype][id][imeth]=(Double_t*)grV2[itype][id][imeth]->GetEY();

        nbins[itype][id][imeth]=(Int_t) grV2[itype][id][imeth]->GetN();
      }
    }
  }
  for (int imeth=0;imeth<nmethod;imeth++){
  
    for (int id=0;id<npid;id++){
      for (int itype=0;itype<ntype;itype++){
        std::vector<Double_t> vRatioToUniformAcceptance, vRatioToUniformAcceptanceErr;
        for (int i=0;i<nbins[ratioToType][id][imeth];i++){
          Double_t ratio = vy_gr[itype][id][imeth][i]/vy_gr[ratioToType][id][imeth][i];
          Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ratioToType][id][imeth][i]/vy_gr[ratioToType][id][imeth][i],2)+TMath::Power(ey_gr[itype][id][imeth][i]/vy_gr[itype][id][imeth][i],2)));
          vRatioToUniformAcceptance.push_back(ratio);
          vRatioToUniformAcceptanceErr.push_back(ratioErr);
        }
        grRatioV2[itype][id][imeth] = new TGraphErrors(nbins[ratioToType][id][imeth],vx_gr[ratioToType][id][imeth],&vRatioToUniformAcceptance[0],ex_gr[ratioToType][id][imeth],&vRatioToUniformAcceptanceErr[0]);
        // grRatioV2[itype][id][imeth] -> SetTitle(Form("%s",ratioName[imeth].Data()));
        vRatioToUniformAcceptance.clear();
        vRatioToUniformAcceptanceErr.clear();
      }
    }
  }
  for (int imeth=0;imeth<nmethod;imeth++){
    for (int id=0;id<npid;id++){
      grRatioV2[1][id][1] -> SetMarkerStyle(kFullSquare);
      grRatioV2[1][id][1] -> SetMarkerColor(kBlue+1);
      grRatioV2[1][id][1] -> SetLineColor(kBlue+1);

      grRatioV2[1][id][3] -> SetMarkerStyle(kFullCircle);
      grRatioV2[1][id][3] -> SetMarkerColor(kRed+1);
      grRatioV2[1][id][3] -> SetLineColor(kRed+1);

      grRatioV2[1][id][4] -> SetMarkerStyle(kFullTriangleUp);
      grRatioV2[1][id][4] -> SetMarkerColor(kGreen+2);
      grRatioV2[1][id][4] -> SetLineColor(kGreen+2);

      grRatioV2[1][id][5] -> SetMarkerStyle(kFullTriangleDown);
      grRatioV2[1][id][5] -> SetMarkerColor(kBlack);
      grRatioV2[1][id][5] -> SetLineColor(kBlack);

      for(int it=0;it<ntype;it++){
        grRatioV2[it][id][imeth] -> SetMarkerSize(markerSize+0.1);
      }
    }
  }

  TCanvas *can = new TCanvas("can","",200,10,2100,1000);
  TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,"Au+Au at #sqrt{s_{NN}}=7.7 GeV 10-40%, UrQMD, reconstructed (GEANT4), 20M events, Ch. hadrons");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(1.5);
  title->Draw();
  can->SetLeftMargin(0.17);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.2);
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
  can->Divide(4,2,0,0);
  TH2F *h[npad];
  for (int ipad=0;ipad<npad;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";;v_{2}"),1,minpt,maxpt,1,minV2,maxV2);
    if (ipad==1 || ipad==2 || ipad==3) h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2,maxV2);
    else if (ipad==4) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";;v_{2}^{non-unif.}/v_{2}^{unif.}    ",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else if (ipad==6) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s     ;",xAxisName[1].Data()),1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else if (ipad==5) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s     ;",xAxisName[0].Data()),1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else if (ipad==7) h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);

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
    if (ipad<npad/2) {
      tex.SetTextSize(labelSizeUpperPlot); 
      tex.DrawLatex(0.3,maxV2*0.94,padName[ipad].Data());
    }else {
      tex.SetTextSize(labelSizeLowerPlot);
      tex.DrawLatex(0.3,maxV2Ratio*0.985,padName[ipad].Data());
    }
    
    if (ipad==0) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("Au+Au"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{4}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0]-0.18,leg_coordinate[1]-0.2,leg_coordinate[2]-0.7,leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextAlign(11);
      for(int it=0;it<1;it++){
        leg_pt->AddEntry(grV2[it][0][0],typeOfGraphName[it].Data(),"");
      }
      leg_pt->Draw();
    }
    if (ipad==1) {
      // tex.DrawLatex(maxpt*0.98,maxV2*0.9,Form("at #sqrt{s_{NN}}=7.7 GeV, 10-40%%"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{4}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0]-0.43,leg_coordinate[1]-0.2,leg_coordinate[2]-0.9,leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextAlign(11);
      for(int it=1;it<ntype;it++){
        leg_pt->AddEntry(grV2[it][0][0],typeOfGraphName[it].Data(),"");
      }
      leg_pt->Draw();
    }
    if (ipad==2) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("UrQMD"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{2}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->SetTextFont(textFont);
      // leg_pt->AddEntry(grV2[1][0][1],legendEntries[1].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][3],legendEntries[3].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][4],legendEntries[4].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][5],legendEntries[5].Data(),"p");
      // leg_pt->Draw();
    }
    if (ipad==3) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("Ch. hadrons"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{2}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      leg_pt->SetTextFont(textFont);
      // leg_pt->AddEntry(grV2[1][0][1],legendEntries[1].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][3],legendEntries[3].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][4],legendEntries[4].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][5],legendEntries[5].Data(),"p");
      // leg_pt->Draw();
    }
    if (ipad==4) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("Ch. hadrons"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{2}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0]+0.28,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeLowerPlot);
      leg_pt->SetTextFont(textFont);
      leg_pt->AddEntry(grV2[1][0][1],legendEntries[1].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][3],legendEntries[3].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][4],legendEntries[4].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][5],legendEntries[5].Data(),"p");
      leg_pt->Draw();
    }

    if (ipad==5) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("Ch. hadrons"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{2}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0]+0.25,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeLowerPlot);
      leg_pt->SetTextFont(textFont);
      // leg_pt->AddEntry(grV2[1][0][1],legendEntries[1].Data(),"p");
      leg_pt->AddEntry(grV2[1][0][3],legendEntries[3].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][4],legendEntries[4].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][5],legendEntries[5].Data(),"p");
      leg_pt->Draw();
    }

    if (ipad==6) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("Ch. hadrons"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{2}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeLowerPlot);
      leg_pt->SetTextFont(textFont);
      // leg_pt->AddEntry(grV2[1][0][1],legendEntries[1].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][3],legendEntries[3].Data(),"p");
      leg_pt->AddEntry(grV2[1][0][4],legendEntries[4].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][5],legendEntries[5].Data(),"p");
      leg_pt->Draw();
    }

    if (ipad==7) {
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9,Form("Ch. hadrons"));
      // tex.DrawLatex(maxpt*0.9,maxV2*0.9-0.02,Form("v_{2}{2}")); 
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextSize(labelSizeLowerPlot);
      leg_pt->SetTextFont(textFont);
      // leg_pt->AddEntry(grV2[1][0][1],legendEntries[1].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][3],legendEntries[3].Data(),"p");
      // leg_pt->AddEntry(grV2[1][0][4],legendEntries[4].Data(),"p");
      leg_pt->AddEntry(grV2[1][0][5],legendEntries[5].Data(),"p");
      leg_pt->Draw();
    }

    for(int it=0;it<ntype;it++){
      if (ipad==0) grV2[it][0][1]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
      if (ipad==1) grV2[it][0][3]->Draw("P");
      if (ipad==2) grV2[it][0][4]->Draw("P");
      if (ipad==3) grV2[it][0][5]->Draw("P");
    }
    for(int it=1;it<ntype;it++){
      if (ipad==4) grRatioV2[it][0][1]->Draw("P");
      if (ipad==5) grRatioV2[it][0][3]->Draw("P");
      if (ipad==6) grRatioV2[it][0][4]->Draw("P");
      if (ipad==7) grRatioV2[it][0][5]->Draw("P");
    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    if (ipad>=npad/2)lineOne.DrawLine(minpt,1.,maxpt,1.);
  }
  


  can->SaveAs(Form("Figure_5_AcceptanceCorrection_v2pt.pdf"));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("Figure_5_AcceptanceCorrection_v2pt.png"));

}
// Au+Au at #sqrt{s_{NN}}=7.7 GeV, 10-40%%, UrQMD, Ch. hadrons