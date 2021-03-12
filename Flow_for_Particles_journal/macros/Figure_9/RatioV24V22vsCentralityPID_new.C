void RatioV24V22vsCentralityPID_new(){
  const int nmodel = 5; // "STAR data","AMPT15","vHLLE+UrQMD"
  const int npid = 7;
  const int nmethod = 3; // v22, v24, v22(eta-gap)
  const int nenergy = 2; // 7.7, 11.5, 19.6, 27, 39 GeV
  const float minpt = -5;
  const float maxpt = 64.;
  const float maxV2Ratio = 1.3;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.75,0.01,0.95,0.3}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.08;
  const float titleSize = 0.09;
  const float labelSize1 = 0.095;
  const float titleSize1 = 0.105;
  const float markerSize = 1.5;
  const float textFont = 132;
  // const int ratioToMethod = 0; // v22
  const int ratioToMethod = 2; // v22,eta-gap
  TString legendEntries[npid]={"#pi^{#pm}","p"}; //(Phys.Rev.C.86.054908)
  TString energy[nenergy]={"7.7","11.5"};
  TString model[nmodel]={"UrQMD","AMPT15","AMPT08","SMASH","vHLLEUrQMD"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)"};
  TString padFancyName[nmodel]={"UrQMD","AMPT SM, #it{#sigma}_{p}=1.5mb","AMPT SM, #it{#sigma}_{p}=0.8mb","SMASH","vHLLE+UrQMD"};
  // int color[]={205,102,96,87,81,69,104,154,213};
  // int color[]={99,94,91,63,213};
  int color[]={206,218,1,226,212,206,213};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod][npid];
  TGraphErrors *grRatioV2[nenergy][nmodel][npid];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      // if (ien==2 && imod!=4) continue; // at 19.6 GeV only have vHLLE+UrQMD
      // if (ien==3 && imod==1) continue;  // at 27 GeV only SMASH is missing
      // if (ien==4 && imod!=2 && imod!=4) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      input[ien][imod] = new TFile(Form("./DataNew/v2_%s_%sGeV_8PID.root",model[imod].Data(),energy[ien].Data()),"read");
      if (!input[ien][imod]) { cout << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v22(eta-gap)

        grV2[ien][imod][imeth][0] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_1",imeth)); // Pion+
        grV2[ien][imod][imeth][1] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_2",imeth)); // Kaon+
        grV2[ien][imod][imeth][2] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_3",imeth)); // Proton
        grV2[ien][imod][imeth][3] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_5",imeth)); // Pion-
        grV2[ien][imod][imeth][4] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_6",imeth)); // Kaon-
        grV2[ien][imod][imeth][5] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_8",imeth)); // Pion
        grV2[ien][imod][imeth][6] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_%i_9",imeth)); // Kaon
        for (int id=0; id<npid; id++){
          grV2[ien][imod][imeth][id] -> RemovePoint(0);
        }
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod][npid], *vy_gr[nenergy][nmodel][nmethod][npid], *ex_gr[nenergy][nmodel][nmethod][npid], *ey_gr[nenergy][nmodel][nmethod][npid];
  Int_t nbins[nenergy][nmodel][nmethod][npid];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      for (int imeth=0;imeth<nmethod;imeth++){
        for (int id=0;id<npid;id++){
        // Read points
        vx_gr[ien][imod][imeth][id]=(Double_t*)grV2[ien][imod][imeth][id]->GetX();
        vy_gr[ien][imod][imeth][id]=(Double_t*)grV2[ien][imod][imeth][id]->GetY();

        // Read errors
        ex_gr[ien][imod][imeth][id]=(Double_t*)grV2[ien][imod][imeth][id]->GetEX();
        ey_gr[ien][imod][imeth][id]=(Double_t*)grV2[ien][imod][imeth][id]->GetEY();

        nbins[ien][imod][imeth][id]=(Int_t) grV2[ien][imod][imeth][id]->GetN();
        }
      }
    }
  }
  // cout << "Code breaks here" << endl;
  double xx[2]={0},yy[2]={0};
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      for (int id=0;id<npid;id++){
        std::vector<Double_t> vRatioV22GappedV24, vRatioV22GappedV24Err;
        for (int i=0;i<nbins[ien][imod][2][id];i++){
          Double_t ratio = vy_gr[ien][imod][1][id][i]/vy_gr[ien][imod][ratioToMethod][id][i];
          Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][ratioToMethod][id][i]/vy_gr[ien][imod][ratioToMethod][id][i],2)+TMath::Power(ey_gr[ien][imod][1][id][i]/vy_gr[ien][imod][1][id][i],2)));
          vRatioV22GappedV24.push_back(ratio);
          vRatioV22GappedV24Err.push_back(ratioErr);
        }
        grRatioV2[ien][imod][id] = new TGraphErrors(nbins[ien][imod][2][id],vx_gr[ien][imod][ratioToMethod][id],&vRatioV22GappedV24[0],ex_gr[ien][imod][ratioToMethod][id],&vRatioV22GappedV24Err[0]);      

      }
    }
  }
  // cout << "Code breaks here" << endl;
  for (int imod=0;imod<nmodel;imod++){
    // ,"UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"
    for (int ien=0;ien<nenergy;ien++){
      grRatioV2[ien][imod][0] -> SetMarkerStyle(kFullCircle); // pi+
      grRatioV2[ien][imod][3] -> SetMarkerStyle(kOpenCircle); // pi-
      grRatioV2[ien][imod][1] -> SetMarkerStyle(kFullTriangleUp); // k-
      grRatioV2[ien][imod][4] -> SetMarkerStyle(kOpenTriangleUp); // k+
      grRatioV2[ien][imod][2] -> SetMarkerStyle(kOpenSquare); // p
      grRatioV2[ien][imod][5] -> SetMarkerStyle(kFullCircle);  // pi kFullCircle
      grRatioV2[ien][imod][6] -> SetMarkerStyle(kFullTriangleDown); // k


      // for (int id=0;id<npid;id++){
      // grRatioV2[ien][imod][id] -> SetMarkerColor(color[id]);
      // grRatioV2[ien][imod][id] -> SetLineColor(color[id]);    
      // }
    }

    // grRatioV2[0][imod][0] -> SetMarkerStyle(kFullTriangleUp);
    // grRatioV2[0][imod][1] -> SetMarkerStyle(kOpenTriangleUp);

    // grRatioV2[1][imod][0] -> SetMarkerStyle(kFullCircle);
    // grRatioV2[1][imod][1] -> SetMarkerStyle(kOpenCircle);

    // grRatioV2[2][imod][0] -> SetMarkerStyle(kFullCrossX);
    // grRatioV2[2][imod][1] -> SetMarkerStyle(kOpenCrossX);

    // grRatioV2[3][imod][0] -> SetMarkerStyle(kFullSquare);
    // grRatioV2[3][imod][1] -> SetMarkerStyle(kOpenSquare);
    
    // grRatioV2[4][imod][0] -> SetMarkerStyle(kFullCross);
    // grRatioV2[4][imod][1] -> SetMarkerStyle(kOpenCross);
    for (int id=0;id<npid;id++){
      // grRatioV2[0][imod][id] -> SetMarkerColor(kGreen+3);
      // grRatioV2[0][imod][id] -> SetLineColor(kGreen+3);
      // grRatioV2[1][imod][id] -> SetMarkerColor(kBlack);
      // grRatioV2[1][imod][id] -> SetLineColor(kBlack);
      // grRatioV2[2][imod][id] -> SetMarkerColor(kYellow+2);
      // grRatioV2[2][imod][id] -> SetLineColor(kYellow+2);
      // grRatioV2[3][imod][id] -> SetMarkerColor(kGray+2);
      // grRatioV2[3][imod][id] -> SetLineColor(kGray+2);
      // grRatioV2[4][imod][id] -> SetMarkerColor(kBlue+2);
      // grRatioV2[4][imod][id] -> SetLineColor(kBlue+2);
      for (int ien=0;ien<nenergy;ien++){
        // grRatioV2[ien][imod][id] -> SetMarkerColor(color[ien]);
        // grRatioV2[ien][imod][id] -> SetLineColor(color[ien]);
      }
    }
  }
  for (int imod=0;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      for (int id=0;id<npid;id++){
      grRatioV2[ien][imod][id]->SetMarkerSize(markerSize);
      grRatioV2[ien][imod][id]->SetDrawOption("P PLC PMC");
      }
    }
  }
  // cout << "Code breaks here" << endl;
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1000,600);
  TPaveLabel* label = new TPaveLabel(0.1,0.95,0.9,0.99,Form("Au+Au, 0.2< #it{p}_{T}^{}<3.0 GeV/c")); // at 
  label->SetTextFont(132);
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->Draw();
  gStyle->SetTextFont(textFont);
  gStyle->SetLegendFont(textFont);
  can->SetTopMargin(0.12);
  can->SetLeftMargin(0.17);
  can->SetRightMargin(0.04);
  can->SetBottomMargin(0.17);
  gStyle->SetPalette(kDarkRainBow);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(3,nenergy,0,0);
  TH2F *h[3][nenergy];
  for (int imod=0;imod<3;imod++){
    for (int ien=0;ien<nenergy;ien++){
      if (ien==0) can->cd(imod+1);
      if (ien==1) can->cd(imod+4);

      // if (ien==0 && imod==0) h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),";;#it{v}_{2}{4}/#it{v}_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
      // else if (ien==1 && imod==1) h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),";centrality, %;",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
      // else h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),"",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
      h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),"",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
      h[imod][ien]->GetXaxis()->SetTitle("Centrality, %");
      h[imod][ien]->GetYaxis()->SetTitle("#it{v}_{2}{4}/#it{v}_{2}{2}");
      h[imod][ien]->GetXaxis()->SetLabelSize(labelSize);
      h[imod][ien]->GetXaxis()->SetTitleSize(titleSize);
      h[imod][ien]->GetXaxis()->SetLabelFont(textFont);
      h[imod][ien]->GetXaxis()->SetTitleFont(textFont);
      h[imod][ien]->GetXaxis()->SetNdivisions(504);
      h[imod][ien]->GetXaxis()->SetTitleOffset(0.8);
      h[imod][ien]->GetXaxis()->SetLabelOffset(0.01);
      // h[imod][ien]->GetXaxis()->CenterTitle(true);

      h[imod][ien]->GetYaxis()->SetLabelSize(labelSize);
      h[imod][ien]->GetYaxis()->SetTitleSize(titleSize);
      h[imod][ien]->GetYaxis()->SetLabelFont(textFont);
      h[imod][ien]->GetYaxis()->SetTitleFont(textFont);
      h[imod][ien]->GetYaxis()->SetNdivisions(504);
      h[imod][ien]->GetYaxis()->SetLabelOffset(0.015);
      h[imod][ien]->GetYaxis()->SetTitleOffset(0.9);
      // h[imod][ien]->GetYaxis()->CenterTitle(true);
      if (ien==0) {
      h[imod][ien]->GetXaxis()->SetLabelSize(labelSize1);
      h[imod][ien]->GetXaxis()->SetTitleSize(titleSize1);
      // h[imod][ien]->GetXaxis()->SetLabelOffset(0.022);
      h[imod][ien]->GetYaxis()->SetLabelSize(labelSize1);
      h[imod][ien]->GetYaxis()->SetTitleSize(titleSize1);      
      }
      h[imod][ien]->Draw();

      TLatex tex;
      tex.SetTextFont(textFont);
      tex.SetTextAlign(13);
      tex.SetTextSize(labelSize);
      if (ien==0) tex.SetTextSize(labelSize+0.015);
      if (imod==0 && ien==1) tex.SetTextSize(labelSize1);
      if (ien==0) tex.DrawLatex(minpt+1,maxV2Ratio*0.98,padName[imod].Data());
      if (ien==1) tex.DrawLatex(minpt+1,maxV2Ratio*0.98,padName[imod+3].Data());
      if (ien==0) tex.DrawLatex(minpt+10.,maxV2Ratio*0.98,Form("%s",padFancyName[imod].Data())); // #sqrt{s_{NN}}=
      if (imod==0) tex.DrawLatex(minpt+10,minV2Ratio+0.1,Form("#sqrt{#it{s}_{NN}}=%s GeV",energy[ien].Data()));
      // if (ien==2 && imod==1) tex.DrawLatex(minpt+0.3,minV2Ratio+0.1,"open - p");
      // if (ien==2 && imod==2) tex.DrawLatex(minpt+0.3,minV2Ratio+0.1,"filled - #pi^{#pm}");

      TLine lineOne;
      lineOne.SetLineStyle(2);
      lineOne.DrawLine(minpt,1.,maxpt,1.);


      for (int id=0;id<npid;id++){
        if (id==2 || id==5 || id==6) { 
        // grRatioV2[ien][imod][id]->Draw("P");
        grRatioV2[ien][imod][id]->Draw("P PLC PMC");
        }
      }

      // if (imod==0 && ien==0) {

      //   TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      //   leg_pt->SetBorderSize(0);
      //   leg_pt->SetTextFont(textFont);
      //   leg_pt->SetTextSize(labelSize);
      //   leg_pt->AddEntry(grRatioV2[1][1][5],"#pi^{#pm}","p");
      //   leg_pt->AddEntry(grRatioV2[1][1][6],"K^{#pm}","p");
      //   leg_pt->Draw();
      // }else if (imod==1 && ien==0) {
        if (imod==1 && ien==0) {
          TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
          leg_pt->SetBorderSize(0);
          leg_pt->SetTextFont(textFont);
          leg_pt->SetTextSize(labelSize);
          // leg_pt->AddEntry(grRatioV2[0][0][3],"#pi^{-}","p");
          leg_pt->AddEntry(grRatioV2[1][0][5],"#pi^{#pm}","p");
          leg_pt->AddEntry(grRatioV2[1][0][6],"K^{#pm}","p");
          leg_pt->AddEntry(grRatioV2[1][0][2],"p","p");
          leg_pt->Draw();
        }
      // }else if (imod==2 && ien==0){

      //   TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      //   leg_pt->SetBorderSize(0);
      //   leg_pt->SetTextFont(textFont);
      //   leg_pt->SetTextSize(labelSize);
      //   leg_pt->AddEntry(grRatioV2[1][0][2],"p","p");
      //   leg_pt->Draw();

      // }
    }
  }
  can->SaveAs("v24v22Cent_PID.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("v24v22Cent_PID.png");


}