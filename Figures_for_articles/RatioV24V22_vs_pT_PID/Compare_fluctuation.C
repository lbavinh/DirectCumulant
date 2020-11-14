void Compare_fluctuation(){
  const int nmodel = 5; // "STAR data","AMPT15","vHLLE+UrQMD"
  const int npid = 2; 
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const int nenergy = 5; // 7.7, 11.5, 19.6, 27, 39 GeV
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
  TString legendEntries[npid]={"#pi^{#pm}","p"}; //(Phys.Rev.C.86.054908)
  TString energy[nenergy]={"7.7","11.5","19.6","27","39"};
  TString model[nmodel]={"UrQMD","SMASH","AMPT15","AMPT08","vHLLEUrQMD"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)"};
  TString padFancyName[nmodel]={"UrQMD","SMASH","AMPT, #sigma_{p}=1.5mb","AMPT, #sigma_{p}=0.8mb","vHLLE+UrQMD"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod][npid];
  TGraphErrors *grRatioV2[nenergy][nmodel][npid];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (ien==2 && imod!=4) continue; // at 19.6 GeV only have vHLLE+UrQMD
      if (ien==3 && imod==1) continue;  // at 27 GeV only SMASH is missing
      if (ien==4 && imod!=2 && imod!=4) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      input[ien][imod] = new TFile(Form("./Data/v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      if (!input[ien][imod]) { cout << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v2(eta-sub), v22(eta-gap)

        grV2[ien][imod][imeth][0] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_cent10-40_%i_1",imeth));
        grV2[ien][imod][imeth][1] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_cent10-40_%i_3",imeth));
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod][npid], *vy_gr[nenergy][nmodel][nmethod][npid], *ex_gr[nenergy][nmodel][nmethod][npid], *ey_gr[nenergy][nmodel][nmethod][npid];
  Int_t nbins[nenergy][nmodel][nmethod][npid];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (ien==2 && imod!=4) continue; // at 19.6 GeV only have vHLLE+UrQMD
      if (ien==3 && imod==1) continue;  // at 27 GeV only SMASH is missing
      if (ien==4 && imod!=2 && imod!=4) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
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
      for (int id=0;id<2;id++){

        if      (ien==2 && imod!=4)            grRatioV2[ien][imod][id] = new TGraphErrors(2,xx,yy,xx,yy); // at 19.6 GeV only have vHLLE+UrQMD
        else if (ien==3 && imod==1)            grRatioV2[ien][imod][id] = new TGraphErrors(2,xx,yy,xx,yy);  // at 27 GeV only SMASH is missing
        else if (ien==4 && imod!=2 && imod!=4) grRatioV2[ien][imod][id] = new TGraphErrors(2,xx,yy,xx,yy);  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
        else{
          std::vector<Double_t> vRatioV22GappedV24, vRatioV22GappedV24Err;
          for (int i=0;i<nbins[ien][imod][3][id];i++){
            Double_t ratio = vy_gr[ien][imod][1][id][i]/vy_gr[ien][imod][3][id][i];
            Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][3][id][i]/vy_gr[ien][imod][3][id][i],2)+TMath::Power(ey_gr[ien][imod][1][id][i]/vy_gr[ien][imod][1][id][i],2)));
            vRatioV22GappedV24.push_back(ratio);
            vRatioV22GappedV24Err.push_back(ratioErr);
          }
          grRatioV2[ien][imod][id] = new TGraphErrors(nbins[ien][imod][3][id],vx_gr[ien][imod][3][id],&vRatioV22GappedV24[0],ex_gr[ien][imod][3][id],&vRatioV22GappedV24Err[0]);      
        }
      }
    }
  }
  // cout << "Code breaks here" << endl;
  for (int imod=0;imod<nmodel;imod++){
    // ,"UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"


    grRatioV2[0][imod][0] -> SetMarkerStyle(kFullTriangleUp);
    grRatioV2[0][imod][1] -> SetMarkerStyle(kOpenTriangleUp);

    grRatioV2[1][imod][0] -> SetMarkerStyle(kFullCircle);
    grRatioV2[1][imod][1] -> SetMarkerStyle(kOpenCircle);

    grRatioV2[2][imod][0] -> SetMarkerStyle(kFullCrossX);
    grRatioV2[2][imod][1] -> SetMarkerStyle(kOpenCrossX);

    grRatioV2[3][imod][0] -> SetMarkerStyle(kFullSquare);
    grRatioV2[3][imod][1] -> SetMarkerStyle(kOpenSquare);
    
    grRatioV2[4][imod][0] -> SetMarkerStyle(kFullCross);
    grRatioV2[4][imod][1] -> SetMarkerStyle(kOpenCross);
    for (int id=0;id<npid;id++){
      grRatioV2[0][imod][id] -> SetMarkerColor(kGreen+3);
      grRatioV2[0][imod][id] -> SetLineColor(kGreen+3);
      grRatioV2[1][imod][id] -> SetMarkerColor(kBlack);
      grRatioV2[1][imod][id] -> SetLineColor(kBlack);
      grRatioV2[2][imod][id] -> SetMarkerColor(kYellow+2);
      grRatioV2[2][imod][id] -> SetLineColor(kYellow+2);
      grRatioV2[3][imod][id] -> SetMarkerColor(kGray+2);
      grRatioV2[3][imod][id] -> SetLineColor(kGray+2);
      grRatioV2[4][imod][id] -> SetMarkerColor(kBlue+2);
      grRatioV2[4][imod][id] -> SetLineColor(kBlue+2);
    }
  }
  for (int imod=0;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      for (int id=0;id<npid;id++){
      grRatioV2[ien][imod][id]->SetMarkerSize(markerSize);
      }
    }
  }
  // cout << "Code breaks here" << endl;
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1800,500);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.17);

  TPaveLabel* title = new TPaveLabel(0.1,0.94,0.9,0.97,"Au+Au, 10-40%");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.5);
  title->Draw();

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(nmodel,1,0,0);
  TH2F *h[nmodel];
  for (int ipad=0;ipad<nmodel;ipad++){
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
    tex.DrawLatex(minpt+0.5,maxV2Ratio*0.98,Form("%s",padFancyName[ipad].Data())); // #sqrt{s_{NN}}=
    if (ipad==1) {

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      leg_pt->AddEntry(grRatioV2[0][ipad][0],energy[0].Data(),"p");
      leg_pt->AddEntry(grRatioV2[1][ipad][0],energy[1].Data(),"p");
      leg_pt->Draw();      
    }else if (ipad==2) {

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      leg_pt->AddEntry(grRatioV2[2][ipad][0],energy[2].Data(),"p");
      leg_pt->AddEntry(grRatioV2[3][ipad][0],energy[3].Data(),"p");
      leg_pt->Draw();
    }else if (ipad==3){

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2]+0.2,leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      leg_pt->AddEntry(grRatioV2[4][ipad][0],energy[4].Data(),"p");
      leg_pt->Draw();

    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(minpt,1.,maxpt,1.);

    for (int ien=0;ien<nenergy;ien++){
      for (int id=0;id<npid;id++){
      grRatioV2[ien][ipad][id]->Draw("P");
      }
    }
  }
  can->SaveAs("Figure_Ratiov24v22_vs_pt_PID.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("Figure_Ratiov24v22_vs_pt_PID.png");


}