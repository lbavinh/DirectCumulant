void Compare_fluctuation_v2cent(){
  const int nenergy = 3; // 4.5, 7.7, 11.5 GeV
  const int nmodel = 2; // UrQMD, SMASH
  const int nmethod = 4; // v22, v24, v2(eta-sub), v22(eta-gap)
  const float minpt = 0.;
  const float maxpt = 72.;
  const float maxV2Ratio = 1.23;
  const float minV2Ratio = 0.77;
  const float leg_coordinate[4]={0.17,0.7,0.3,0.99};
  const float labelSize = 0.08;
  const TString leg_header[2] = {"UrQMD","SMASH"};
  TString energy[3]={"4.5","7.7","11.5"};
  TString model[2]={"UrQMD","SMASH"};
  TFile *input[nenergy][nmodel];
  TGraphErrors *grV2[nenergy][nmodel][nmethod];
  TGraphErrors *grRatioV2[nenergy][nmodel];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      input[ien][imod] = new TFile(Form("v2_%s_%sGeV.root",model[imod].Data(),energy[ien].Data()),"read");
      for (int imeth=0;imeth<nmethod;imeth++){ // v24 = 1; v22(eta-gap) = 3
        grV2[ien][imod][imeth] = (TGraphErrors*)input[ien][imod]->Get(Form("grRF_%i_0",imeth)); // "_0" - Charged Hadrons
      }
    }
  }
  
  Double_t *vx_gr[nenergy][nmodel][nmethod], *vy_gr[nenergy][nmodel][nmethod], *ex_gr[nenergy][nmodel][nmethod], *ey_gr[nenergy][nmodel][nmethod];
  Int_t nbins[nenergy][nmodel][nmethod];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
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
  std::vector<Double_t> vRatioV22GappedV24[nenergy][nmodel], vRatioV22GappedV24Err[nenergy][nmodel];
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel;imod++){
      for (int i=0;i<nbins[ien][imod][3];i++){
        Double_t ratio = vy_gr[ien][imod][1][i]/vy_gr[ien][imod][2][i];
        Double_t ratioErr = ratio*(TMath::Sqrt(TMath::Power(ey_gr[ien][imod][2][i]/vy_gr[ien][imod][2][i],2)+TMath::Power(ey_gr[ien][imod][1][i]/vy_gr[ien][imod][1][i],2)));
        vRatioV22GappedV24[ien][imod].push_back(ratio);
        vRatioV22GappedV24Err[ien][imod].push_back(ratioErr);
      }
      grRatioV2[ien][imod] = new TGraphErrors(nbins[ien][imod][3],vx_gr[ien][imod][3],&vRatioV22GappedV24[ien][imod][0],ex_gr[ien][imod][3],&vRatioV22GappedV24Err[ien][imod][0]);
      grRatioV2[ien][imod] -> SetTitle(Form("%s GeV;;v_{2}{4}/v_{2}{2}",energy[ien].Data()));
      
    }
    grRatioV2[ien][0] -> SetMarkerStyle(kFullCircle);
    grRatioV2[ien][1] -> SetMarkerStyle(kFullCircle);
  }
  for (int imod=0;imod<nmodel;imod++){
    grRatioV2[0][imod] -> SetMarkerColor(kRed);
    grRatioV2[0][imod] -> SetLineColor(kRed);
    grRatioV2[1][imod] -> SetMarkerColor(kGreen);
    grRatioV2[1][imod] -> SetLineColor(kGreen);
    grRatioV2[2][imod] -> SetMarkerColor(kBlue);
    grRatioV2[2][imod] -> SetLineColor(kBlue);
    for (int ien=0;ien<nenergy;ien++){
      grRatioV2[ien][imod]->SetMarkerSize(1.5);
    }
  }
  TCanvas *can = new TCanvas("can","can",200,10,800,650);
  can->SetLeftMargin(0.12);
  can->SetRightMargin(0.01);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.17);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gStyle->SetPalette(kBird);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  can->Divide(1,2,0,0);
  can->cd(1);
  TH2F *h1 = new TH2F("h1",";centrality [%];v_{2}{4}/v_{2}{#eta-sub}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h1->GetXaxis()->SetLabelSize(labelSize);
  h1->GetYaxis()->SetLabelSize(labelSize);
  h1->GetXaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetTitleSize(labelSize);
  h1->GetYaxis()->SetNdivisions(504);
  h1->GetYaxis()->SetTitleOffset(0.5);
  h1->Draw();
  TLegend *leg_pt = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt->SetBorderSize(0);
  leg_pt->SetHeader(leg_header[0].Data(),"C");
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=0;imod<nmodel-1;imod++){
      grRatioV2[ien][imod]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
      leg_pt->AddEntry(grRatioV2[ien][imod],Form("%s",grRatioV2[ien][imod]->GetTitle()),"p");
    }
  }
  leg_pt->Draw();
  TLine lineOne;
  lineOne.SetLineStyle(2);
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  can->cd(2);
  TH2F *h2 = new TH2F("h2",";centrality [%];v_{2}{4}/v_{2}{#eta-sub}",1,minpt,maxpt,1,minV2Ratio,maxV2Ratio);
  h2->GetXaxis()->SetLabelSize(labelSize);
  h2->GetYaxis()->SetLabelSize(labelSize);
  h2->GetXaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetTitleSize(labelSize);
  h2->GetYaxis()->SetNdivisions(504);
  h2->GetYaxis()->SetTitleOffset(0.5);
  h2->Draw();
  
  TLegend *leg_pt2 = new TLegend(leg_coordinate[0],leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
  leg_pt2->SetBorderSize(0);
  leg_pt2->SetHeader(leg_header[1].Data(),"C");
  for (int ien=0;ien<nenergy;ien++){
    for (int imod=1;imod<nmodel;imod++){
      grRatioV2[ien][imod]->Draw("P"); // PLC PMC
      leg_pt2->AddEntry(grRatioV2[ien][imod],Form("%s",grRatioV2[ien][imod]->GetTitle()),"p");
    }
  }
  leg_pt2->Draw();
  lineOne.DrawLine(minpt,1.,maxpt,1.);
  can->SaveAs("v24_v2EP_ratiov2cent.png");


}