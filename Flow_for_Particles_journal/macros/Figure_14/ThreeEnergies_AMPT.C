void ThreeEnergies_AMPT(){
  const int nenergy = 3; // 4.5, 7.7, 11.5 GeV
  const int nmodel = 7; // "STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float mincent = -3;
  const float maxcent = 64.;
  const float maxV2Ratio = 1.3;
  const float minV2Ratio = 0.5;
  const float leg_coordinate[4]={0.2,0.25,0.7,0.45}; //  0.05,0.7,0.35,0.99
  const float labelSize = 0.085;
  const float titleSize = 0.1;
  const float markerSize = 1.7;
  const float textFont = 132;
  TString legendEntries[nmodel]={"STAR data","UrQMD","SMASH","AMPT, #sigma_{p}=1.5mb","AMPT, #sigma_{p}=0.8mb","vHLLE+UrQMD","AMPT, #sigma_{p}=0"}; //(Phys.Rev.C.86.054908)
  TString energy[nenergy]={"4.5","7.7","11.5"};
  TString model[nmodel]={"STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLEUrQMD","AMPT00"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)","(k)","(l)","(m)","(n)","(o)"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  
  TGraphErrors *grRatioV2[nenergy][nmodel];

  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      if (ien==0 && imod!=1 && imod!=2 && imod!=3 && imod!=6) continue;  // at 4.5 GeV only SMASH & UrQMD & AMPT15
      if (ien==2 && imod==6) continue;  // at 11.5 GeV AMPT00 not found
      input[ien][imod] = new TFile(Form("./Data/v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      if (!input[ien][imod]) { cout << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
      for (int imeth=0;imeth<nmethod;imeth++){ // v22, v24, v2(eta-sub), v22(eta-gap)
        grV2[ien][imod][imeth] = (TGraphErrors*)input[ien][imod]->Get(Form("grRF_%i_0",imeth)); // "_0" - Charged Hadrons
        if (!grV2[ien][imod][imeth]) { cout << "Graphs in " << model[imod].Data() << energy[ien].Data() << "not found!" << endl; return; }
      }
    }
  }

  Double_t *vx_gr[nenergy][nmodel][nmethod], *vy_gr[nenergy][nmodel][nmethod], *ex_gr[nenergy][nmodel][nmethod], *ey_gr[nenergy][nmodel][nmethod];
  Int_t nbins[nenergy][nmodel][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      if (ien==0 && imod!=1 && imod!=2 && imod!=3 && imod!=6) continue;  // at 4.5 GeV only SMASH & UrQMD & vHLLE+UrQMD
      if (ien==2 && imod==6) continue;  // at 11.5 GeV AMPT00 not found
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
  
  double xx[2]={0},yy[2]={0};
  std::vector<Double_t> vRatioV22GappedV24[nenergy][nmodel], vRatioV22GappedV24Err[nenergy][nmodel];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      // cout << "Code breaks here " << ien <<" "<< imod << endl;
      if (ien==0 && imod!=1 && imod!=2 && imod!=3 && imod!=6) grRatioV2[ien][imod] = new TGraphErrors(2,xx,yy,xx,yy);  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      else if (ien==2 && imod==6) grRatioV2[ien][imod] = new TGraphErrors(2,xx,yy,xx,yy); // at 11.5 GeV AMPT00 not found
      else{
        for (int i=0;i<nbins[ien][imod][3];i++){
          Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][3][i];
          // if (ien==2 && imod==4) cout << vy_gr[ien][imod][1][i] <<" ";
          Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][3][i]/vy_gr[ien][imod][3][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
          vRatioV22GappedV24[ien][imod].push_back(ratio);
          vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
        }
        grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);      
      }
    }
  }
  for (int ien=0;ien<nenergy;ien++){
    // "STAR data","UrQMD","SMASH","AMPT15","AMPT08","vHLLE+UrQMD"

    grRatioV2[ien][1] -> SetMarkerColor(kGreen+3);
    grRatioV2[ien][1] -> SetLineColor(kGreen+3);
    grRatioV2[ien][1] -> SetMarkerStyle(kFullCircle); //kFullCircle 

    grRatioV2[ien][2] -> SetMarkerColor(kAzure+3);
    grRatioV2[ien][2] -> SetLineColor(kAzure+3);
    grRatioV2[ien][2] -> SetMarkerStyle(kFullTriangleUp); // kOpenTriangleDown

    grRatioV2[ien][3] -> SetMarkerColor(kGreen+3);
    grRatioV2[ien][3] -> SetLineColor(kGreen+3);
    grRatioV2[ien][3] -> SetMarkerStyle(kFullCircle); // AMPT15

    grRatioV2[ien][4] -> SetMarkerColor(kBlack);
    grRatioV2[ien][4] -> SetLineColor(kBlack);
    grRatioV2[ien][4] -> SetMarkerStyle(kOpenSquare); // AMPT08

    grRatioV2[ien][5] -> SetMarkerColor(kGray+2);
    grRatioV2[ien][5] -> SetLineColor(kGray+2);
    grRatioV2[ien][5] -> SetMarkerStyle(kOpenCircle);

    grRatioV2[ien][6] -> SetMarkerColor(kBlue+3);
    grRatioV2[ien][6] -> SetLineColor(kBlue+3);
    grRatioV2[ien][6] -> SetMarkerStyle(kFullTriangleUp);  // AMPT00

  }
  for (int imod=1;imod<nmodel;imod++){
    for (int ien=0;ien<nenergy;ien++){
      if (ien==0 && imod!=1 && imod!=2 && imod!=3 && imod!=6) continue;  // at 39 GeV ony AMPT15 & vHLLE+UrQMD
      if (ien==2 && imod==6) continue;  // at 11.5 GeV AMPT00 not found
      grRatioV2[ien][imod]->SetMarkerSize(markerSize);
      grRatioV2[ien][imod]->RemovePoint(0);
    }
  }

  
  TString energySTAR[nenergy]={"77","77","115"};
  TString energySTARLegend[nenergy]={"7.7 GeV","7.7 GeV","11.5 GeV"};
  TGraphErrors *grRatioV2STAR[nenergy];
  for (int iener=0;iener<nenergy;iener++){
    FILE *fp1;
    char path1[800];
    sprintf(path1,"./Data/v2methods%sCent.txt",energySTAR[iener].Data());
    if((fp1=fopen(path1,"r"))== NULL) {
      cout << "\n Can't open file summary1.txt !\n"<< endl;
      fflush(stdin);
      return;
    }
    int ncent = 9;
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
    grRatioV2[iener][0] = new TGraphErrors(ncent,cent,ratiov24v22,centE,ratiov24v22e);
    grRatioV2[iener][0] -> SetMarkerStyle(kFullStar);
    grRatioV2[iener][0] -> SetMarkerSize(markerSize+1);
    grRatioV2[iener][0] -> SetMarkerColor(kRed+1);
    grRatioV2[iener][0] -> SetLineColor(kRed+1);
    // grRatioV2STAR[iener] = new TGraphErrors(ncent,cent,ratiov24v22,centE,ratiov24v22e);
  }

  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  TCanvas *can = new TCanvas("can","can",200,10,1500,500);
  can->SetLeftMargin(0.17);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.18);
  can->SetTopMargin(0.12);
  TPaveLabel* title = new TPaveLabel(0.1,0.915,0.9,0.95,"Au+Au, Charged hadrons, 0.2 < #it{p}_{T}< 3.0 GeV/c");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.5);
  title->Draw();

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(nenergy,1,0,0);
  TH2F *h[nenergy];
  for (int ipad=0;ipad<nenergy;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";;#it{v}_{2}{4}/#it{v}_{2}{2}",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    else if (ipad==1) h[ipad] = new TH2F(Form("pad_%i",ipad+1),";Centrality, %;",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio); // 
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,mincent,maxcent,1,minV2Ratio,maxV2Ratio);
    
    h[ipad]->GetXaxis()->SetLabelSize(labelSize);
    h[ipad]->GetXaxis()->SetTitleSize(titleSize);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->SetTitleFont(textFont);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.9);
    h[ipad]->GetXaxis()->SetLabelOffset(0.01);
    h[ipad]->GetXaxis()->CenterTitle(true);

    h[ipad]->GetYaxis()->SetLabelSize(labelSize);
    h[ipad]->GetYaxis()->SetTitleSize(titleSize);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetTitleFont(textFont);
    h[ipad]->GetYaxis()->SetLabelOffset(0.01);
    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(0.9);
    h[ipad]->GetYaxis()->CenterTitle(true);
    h[ipad]->Draw();

    TLatex tex;
    tex.SetTextFont(textFont);
    tex.SetTextAlign(13);
    tex.SetTextSize(labelSize);
    if (ipad==0) tex.SetTextSize(labelSize);
    tex.DrawLatex(mincent+2,maxV2Ratio*0.98,padName[ipad].Data());
    tex.DrawLatex(mincent+11,maxV2Ratio*0.98,Form("#sqrt{#it{s}_{NN}} = %s GeV",energy[ipad].Data())); // #sqrt{s_{NN}}=
    if (ipad==0) {
      // tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Au+Au at"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0]+0.1,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.02);
      // for (int imod=3; imod<nmethod; imod++){
      leg_pt->AddEntry(grRatioV2[1][3],legendEntries[3].Data(),"p");
      leg_pt->AddEntry(grRatioV2[1][4],legendEntries[4].Data(),"p");
      leg_pt->AddEntry(grRatioV2[1][6],legendEntries[6].Data(),"p");
      // }
      leg_pt->Draw();      

    }else if (ipad==1) {
      // tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("Ch. hadrons"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.02);
      leg_pt->AddEntry(grRatioV2[1][0],legendEntries[0].Data(),"p");
      // leg_pt->AddEntry(grRatioV2[1][5],legendEntries[5].Data(),"p");

      leg_pt->Draw();
    }else if (ipad==2){
      // tex.DrawLatex(mincent+10,maxV2Ratio*0.98,Form("0.2<p_{T}^{}<3.0 GeV/c"));
      TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSize-0.02);
      leg_pt->AddEntry(grRatioV2[1][1],legendEntries[1].Data(),"p");
      leg_pt->AddEntry(grRatioV2[1][2],legendEntries[2].Data(),"p");
      // leg_pt->Draw();

    }
    TLine lineOne;
    lineOne.SetLineStyle(2);
    lineOne.DrawLine(mincent,1.,maxcent,1.);

    for (int imod=0;imod<nmodel;imod++){
      
      if (imod!=0 && imod!=3 && imod!=4 && imod!=6)   continue;
      if (ipad==0 && imod!=1 && imod!=2 && imod!=3 && imod!=6) continue;
      if (ipad==2 && imod==6) continue;  // at 11.5 GeV AMPT00 not found
      grRatioV2[ipad][imod]->Draw("P");
      
    }
  }

  can->SaveAs("v24v22Cent_4_11GeV_AMPT_vs_STAR.pdf");
  gROOT->SetStyle("Pub");
  can->SaveAs("v24v22Cent_4_11GeV_AMPT_vs_STAR.png");


}