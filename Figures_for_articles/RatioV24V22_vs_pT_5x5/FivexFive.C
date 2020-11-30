void FivexFive(){
  const int nmodel = 5; // "STAR data","AMPT15","vHLLE+UrQMD"
  const int ncent = 5; // 5-10%, 10-20%, 20-30%, 30-40%, 40-50%
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const int nenergy = 5; // 7.7, 11.5, 19.6, 27, 39 GeV
  const float minpt = -0.1;
  const float maxpt = 2.2;
  const float maxV2Ratio = 1.3;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.3,0.2,0.6,0.6}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.1;
  const float titleSize = 0.12;
  const float labelSize1 = 0.08;
  const float titleSize1 = 0.09;
  const float markerSize = 1.7;
  const float textFont = 42;
  TString legendEntries[ncent]={"5-10%", "10-20%", "20-30%", "30-40%", "40-50%"};
  TString energy[nenergy]={"7.7","11.5","19.6","27","39"};
  TString model[nmodel]={"UrQMD","SMASH","AMPT15","AMPT08","vHLLEUrQMD"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)"};
  TString padFancyName[nmodel]={"UrQMD","SMASH","AMPT, #sigma_{p}=1.5mb","AMPT, #sigma_{p}=0.8mb","vHLLE+UrQMD"};
  // int color[]={205,102,96,87,81,69,104,154,213};
  // int color[]={99,94,91,63,213};
  int color[]={206,218,210,226,213};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod][ncent];
  TGraphErrors *grRatioV2[nenergy][nmodel][ncent];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (ien==2 && imod!=4) continue; // at 19.6 GeV only have vHLLE+UrQMD
      if (ien==3 && imod==1) continue;  // at 27 GeV only SMASH is missing
      if (ien==4 && imod!=2 && imod!=4) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      input[ien][imod] = new TFile(Form("./Data/v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      if (!input[ien][imod]) { cout << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v2(eta-sub), v22(eta-gap)
        for (int icent=0;icent<ncent;icent++){
          grV2[ien][imod][imeth][icent] = (TGraphErrors*)input[ien][imod]->Get(Form("gr_cent%i_%i_8",icent+1,imeth));
          grV2[ien][imod][imeth][icent] -> RemovePoint(0);
        }
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod][ncent], *vy_gr[nenergy][nmodel][nmethod][ncent], *ex_gr[nenergy][nmodel][nmethod][ncent], *ey_gr[nenergy][nmodel][nmethod][ncent];
  Int_t nbins[nenergy][nmodel][nmethod][ncent];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      if (ien==2 && imod!=4) continue; // at 19.6 GeV only have vHLLE+UrQMD
      if (ien==3 && imod==1) continue;  // at 27 GeV only SMASH is missing
      if (ien==4 && imod!=2 && imod!=4) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      for (int imeth=0;imeth<nmethod;imeth++){
        for (int icent=0;icent<ncent;icent++){
        // Read points
        vx_gr[ien][imod][imeth][icent]=(Double_t*)grV2[ien][imod][imeth][icent]->GetX();
        vy_gr[ien][imod][imeth][icent]=(Double_t*)grV2[ien][imod][imeth][icent]->GetY();

        // Read errors
        ex_gr[ien][imod][imeth][icent]=(Double_t*)grV2[ien][imod][imeth][icent]->GetEX();
        ey_gr[ien][imod][imeth][icent]=(Double_t*)grV2[ien][imod][imeth][icent]->GetEY();

        nbins[ien][imod][imeth][icent]=(Int_t) grV2[ien][imod][imeth][icent]->GetN();
        }
      }
    }
  }
  // cout << "Code breaks here" << endl;
  double xx[2]={0},yy[2]={0};
  
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      for (int icent=0;icent<ncent;icent++){

        if      (ien==2 && imod!=4)            grRatioV2[ien][imod][icent] = new TGraphErrors(2,xx,yy,xx,yy); // at 19.6 GeV only have vHLLE+UrQMD
        else if (ien==3 && imod==1)            grRatioV2[ien][imod][icent] = new TGraphErrors(2,xx,yy,xx,yy);  // at 27 GeV only SMASH is missing
        else if (ien==4 && imod!=2 && imod!=4) grRatioV2[ien][imod][icent] = new TGraphErrors(2,xx,yy,xx,yy);  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
        else{
          std::vector<Double_t> vRatioV22GappedV24, vRatioV22GappedV24Err;
          for (int i=0;i<nbins[ien][imod][3][icent];i++){
            Double_t ratio = vy_gr[ien][imod][1][icent][i]/vy_gr[ien][imod][3][icent][i];
            Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][3][icent][i]/vy_gr[ien][imod][3][icent][i],2)+TMath::Power(ey_gr[ien][imod][1][icent][i]/vy_gr[ien][imod][1][icent][i],2)));
            vRatioV22GappedV24.push_back(ratio);
            vRatioV22GappedV24Err.push_back(ratioErr);
          }
          grRatioV2[ien][imod][icent] = new TGraphErrors(nbins[ien][imod][3][icent],vx_gr[ien][imod][3][icent],&vRatioV22GappedV24[0],ex_gr[ien][imod][3][icent],&vRatioV22GappedV24Err[0]);      
        }
      }
    }
  }
  // cout << "Code breaks here" << endl;
  for (int imod=0;imod<nmodel;imod++){
    // ,"UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"
    for (int ien=0;ien<nenergy;ien++){
      grRatioV2[ien][imod][1] -> SetMarkerStyle(kFullCircle);
      grRatioV2[ien][imod][1] -> SetMarkerColor(kRed+2);
      grRatioV2[ien][imod][1] -> SetLineColor(kRed+2);

      grRatioV2[ien][imod][3] -> SetMarkerStyle(kFullTriangleDown);
      grRatioV2[ien][imod][3] -> SetMarkerColor(kBlue+3);
      grRatioV2[ien][imod][3] -> SetLineColor(kBlue+3);

      grRatioV2[ien][imod][2] -> SetMarkerStyle(kOpenTriangleUp);
      grRatioV2[ien][imod][2] -> SetMarkerColor(kGreen+3);
      grRatioV2[ien][imod][2] -> SetLineColor(kGreen+3);

      grRatioV2[ien][imod][4] -> SetMarkerStyle(kOpenTriangleUp); // kOpenSquare
      grRatioV2[ien][imod][4] -> SetMarkerColor(kYellow+3);
      grRatioV2[ien][imod][4] -> SetLineColor(kYellow+3);

      grRatioV2[ien][imod][0] -> SetMarkerStyle(kOpenSquare);
      grRatioV2[ien][imod][0] -> SetMarkerColor(kBlack);
      grRatioV2[ien][imod][0] -> SetLineColor(kBlack);

    }
  }
  
  for (int imod=0;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      for (int icent=0;icent<ncent;icent++){
        grRatioV2[ien][imod][icent]->SetMarkerSize(markerSize);
      }
    }
  }

  TString energySTAR[nenergy]={"7.7","11.5","19.6","27","39"};
  TString energySTARLegend[nenergy]={"7.7 GeV","11.5 GeV","19.6 GeV","27 GeV","39 GeV"};
  TGraphErrors *grRatioV2STAR[nenergy];
  for (int iener=0;iener<nenergy;iener++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./Data/v2vspt_20-30_%sGeV.txt",energySTAR[iener].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file summary1.txt !\n"<< endl;
      fflush(stdin);
      return;
    }
    int ncent = 14;
    double cent[ncent], v2eta[ncent], v22[ncent], v24[ncent];
    double centE[ncent], v2etae[ncent], v22e[ncent], v24e[ncent];
    double ratiov24v22[ncent], ratiov24v22e[ncent];
    for (int ipt=0; ipt<ncent; ipt++) {
      float  mCent,s2,  s2e,  s2eta,  s2etae,    s22,s22e,s24,s24e,s2b, s2be;
      //    cent,v2EP,v2EPe,v2etasub,v2etasube,v22,v22e,v24,v24e,v2bbc,v2bbce
      fscanf(fp1, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&mCent,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

      cent[ipt]     = mCent;
      v2eta[ipt]  = s2eta;
      v2etae[ipt] = s2etae;
      v22[ipt]    = s22;
      v22e[ipt]   = s22e;
      v24[ipt]    = s24;
      v24e[ipt]   = s24e;
      centE[ipt]    = 0.;
      Double_t ratio = s24/s22;
      Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(s24e/s24,2)+TMath::Power(s22e/s22,2)));
      ratiov24v22[ipt] = ratio;
      ratiov24v22e[ipt] = ratioErr;
    }
    // STAR
    // grRatioV2[iener][0] = new TGraphErrors(ncent,cent,ratiov24v22,centE,ratiov24v22e);
    // grRatioV2[iener][0] -> SetMarkerStyle(kFullStar);
    // grRatioV2[iener][0] -> SetMarkerSize(markerSize+1);
    // grRatioV2[iener][0] -> SetMarkerColor(kRed+1);
    // grRatioV2[iener][0] -> SetLineColor(kRed+1);
    grRatioV2STAR[iener] = new TGraphErrors(ncent,cent,ratiov24v22,centE,ratiov24v22e);
    grRatioV2STAR[iener] -> SetMarkerStyle(kFullStar);
    grRatioV2STAR[iener] -> SetMarkerSize(markerSize+1);
    grRatioV2STAR[iener] -> SetMarkerColor(kRed+1);
    grRatioV2STAR[iener] -> SetLineColor(kRed+1);
  }

  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1500,1500);
  can->SetLeftMargin(0.21);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.21);
  can->SetTopMargin(0.17);

  TPaveLabel* title = new TPaveLabel(0.1,0.98,0.9,0.99,"Au+Au, Ch. hadrons");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.5);
  title->Draw();

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(nmodel,nenergy,0,0);
  TH2F *h[nmodel][nenergy];
  for (int imod=0;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
    if (ien==0) can->cd(imod+1);
    if (ien==1) can->cd(imod+6);
    if (ien==2) can->cd(imod+11);
    if (ien==3) can->cd(imod+16);
    if (ien==4) can->cd(imod+21);
    if (ien==2 && imod==0) h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),";;v_{2}{4}/v_{2}{2}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else if (ien==4 && imod==2) h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),";p_{T} (GeV/c);",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    else h[imod][ien] = new TH2F(Form("pad_%i_%i",imod,ien),"",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
    h[imod][ien]->GetXaxis()->SetLabelSize(labelSize);
    h[imod][ien]->GetXaxis()->SetTitleSize(titleSize);
    h[imod][ien]->GetXaxis()->SetLabelFont(textFont);
    h[imod][ien]->GetXaxis()->SetNdivisions(504);
    h[imod][ien]->GetXaxis()->SetTitleOffset(0.8);
    h[imod][ien]->GetXaxis()->SetLabelOffset(0.01);
    h[imod][ien]->GetXaxis()->CenterTitle(true);

    h[imod][ien]->GetYaxis()->SetLabelSize(labelSize);
    h[imod][ien]->GetYaxis()->SetTitleSize(titleSize);
    h[imod][ien]->GetYaxis()->SetLabelFont(textFont);
    h[imod][ien]->GetYaxis()->SetNdivisions(504);
    h[imod][ien]->GetYaxis()->SetLabelOffset(0.015);
    h[imod][ien]->GetYaxis()->SetTitleOffset(1.);
    h[imod][ien]->GetYaxis()->CenterTitle(true);
    if (imod==0 && ien==4) {
    h[imod][ien]->GetXaxis()->SetLabelSize(labelSize1);
    h[imod][ien]->GetXaxis()->SetTitleSize(titleSize1);
    h[imod][ien]->GetXaxis()->SetLabelOffset(0.022);
    h[imod][ien]->GetYaxis()->SetLabelSize(labelSize1);
    h[imod][ien]->GetYaxis()->SetTitleSize(titleSize1);      
    }
    h[imod][ien]->Draw();

    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(13);
    tex.SetTextSize(labelSize);
    if (imod==0 && ien==4) tex.SetTextSize(labelSize1);
    // tex.DrawLatex(minpt+0.1,maxV2Ratio*0.98,padName[imod+ien].Data());
    if (ien==0) tex.DrawLatex(minpt+0.5,maxV2Ratio*0.98,Form("%s",padFancyName[imod].Data())); // #sqrt{s_{NN}}=
    if (imod==0) tex.DrawLatex(minpt+0.3,minV2Ratio+0.1,Form("%s GeV",energy[ien].Data()));
    // if (ien==2 && imod==1) tex.DrawLatex(minpt+0.3,minV2Ratio+0.1,"open - p");
    // if (ien==2 && imod==2) tex.DrawLatex(minpt+0.3,minV2Ratio+0.1,"filled - #pi^{#pm}");
    if (imod==0 && ien==2) {

      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.01);
      for (int icent=0;icent<ncent;icent++){
        leg_pt->AddEntry(grRatioV2[ien][imod][icent],legendEntries[icent].Data(),"p");  
      }
      leg_pt->Draw();
    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(minpt,1.,maxpt,1.);
    grRatioV2STAR[ien] -> Draw("P");
    for (int icent=0;icent<ncent;icent++){
      if (icent!=2 && icent!=2 && icent!=2) continue;
      grRatioV2[ien][imod][icent]->Draw("P");
    }
  
  }
  }
  can->SaveAs("Figure_Ratiov24v22_vs_pt_5x5.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("Figure_Ratiov24v22_vs_pt_5x5.png");


}