#include "DrawTGraph.C"
void Performance(){ // 0: v22; 1:v24; 2: v2EP, 3: gapped v22
  const int nlevel = 2; // model , Reco
  const int nenergy = 1;
  const int nmethod = 4; // v24, v2(eta-sub), v22(eta-gap), v2SP TPC, v2EP FHCal
  const int npid = 3; // pions, protons
  const float textFont = 132;

  const float minpt = -0.2;
  const float maxpt = 2.4;
  const float maxV2 = 0.05;
  const float minV2 = -0.005;

  const double minV2dif = -0.01; // for v2 vs pt plotting
  const double maxV2dif = 0.2; // for v2 vs pt plotting
  TString model = {"UrQMD"};
  TString energy[] = {"7.7GeV","11.5GeV"};
  TString xAxisName = {"#it{p}_{T}, GeV/c"};
  TString legendEntries[nlevel]={"open - reco","filled - true"};
  TString legendEntries1[]={"#pi^{#pm}","p","h^{#pm}"};
  TString padName[]={"(a)","(b)","(c)","(d)","(e)","(f)","(g)","(h)","(i)","(j)"};
  const float leg_coordinate[4]={0.6,0.05,0.99,0.35}; // top left: 0.28,0.7,0.6,0.99
  const float labelSizeUpperPlot = 0.09;
  const float labelSizeLowerPlot = 0.09;
  const float titleSizeUpperPlot = 0.1;
  const float titleSizeLowerPlot = 0.105;
  TGraphErrors *grV2[npid][nlevel][nmethod][nenergy];
  TString graphTitle[]={"#it{v}_{3}{4}","#it{v}_{3}{2}","#it{v}_{3}{#Psi_{3,TPC}}","#it{v}_{3}^{SP}{Q_{3,TPC}}","#it{v}_{3}{#Psi_{1,FHCal}}"};
  TString pidName[]={"pions","protons"};
  TString energyName[]={"7.7","11.5"};
  TString levelName[]={"mc","reco"};
  TFile *fi[nlevel][nenergy]; // QC

  for (int ien=0;ien<nenergy;ien++){
    fi[0][ien] = new TFile(Form("v2_Model.root",energyName[ien].Data()),"READ");
    fi[1][ien] = new TFile(Form("v2_Reco.root",energyName[ien].Data()),"READ");

    for (int ilev=0; ilev<nlevel; ilev++){
      for (int imeth=0;imeth<nmethod-2;imeth++){

        grV2[0][ilev][imeth][ien] = (TGraphErrors*)fi[ilev][ien]->Get(Form("gr_cent10-40_%i_9",imeth+1)); // pions
        grV2[1][ilev][imeth][ien] = (TGraphErrors*)fi[ilev][ien]->Get(Form("gr_cent10-40_%i_3",imeth+1)); // protons
        grV2[2][ilev][imeth][ien] = (TGraphErrors*)fi[ilev][ien]->Get(Form("gr_cent10-40_%i_8",imeth+1)); // hadrons

      }
    }
  }

  // TFile *inputPeter[npid][nenergy];

  // for (int id=0;id<npid;id++){
  //   for (int e=0;e<nenergy;e++){
  //     inputPeter[id][e] = new TFile(Form("./Data/graphs_fhcal_%sgev_%s.root",energyName[e].Data(),pidName[id].Data()),"read");
  //     if (!inputPeter[id][e]) cout << "root file of graphs not found\n";
  //   }
  // }
  // for (int id=0;id<npid;id++){
  //   for (int ilev=0; ilev<nlevel; ilev++){
  //     for (int ien=0;ien<nenergy;ien++){
  //       grV2[id][ilev][4][ien] = (TGraphErrors*)inputPeter[id][ien]->Get(Form("gr_v2_FHCalEp_%s",levelName[ilev].Data()));
  //       if (!grV2[id][ilev][4][ien]) {
  //         cout << "graph "<< pidName[id].Data() <<" "<<levelName[ilev].Data()<<" "<<energyName[ien].Data()<<" does not exist."<<endl;
  //         return;
  //       }
  //     }
  //   }
  // }
  TFile *fiEP[nlevel][nenergy]; // EP
  for (int ien=0;ien<nenergy;ien++){
    fi[0][ien] = new TFile(Form("v2_Model_EP.root",energyName[ien].Data()),"READ");
    fi[1][ien] = new TFile(Form("v2_Reco_EP.root",energyName[ien].Data()),"READ");

    for (int ilev=0; ilev<nlevel; ilev++){
      for (int imeth=2;imeth<nmethod;imeth++){

        grV2[0][ilev][imeth][ien] = (TGraphErrors*)fi[ilev][ien]->Get(Form("gr_cent10-40_%i_9",imeth-2)); // pions
        grV2[1][ilev][imeth][ien] = (TGraphErrors*)fi[ilev][ien]->Get(Form("gr_cent10-40_%i_3",imeth-2)); // protons
        grV2[2][ilev][imeth][ien] = (TGraphErrors*)fi[ilev][ien]->Get(Form("gr_cent10-40_%i_8",imeth-2)); // hadrons

      }
    }
  }

  // Cosmetics
  for (int imeth=0;imeth<nmethod;imeth++){
    for (int ien=0;ien<nenergy;ien++){
      grV2[0][0][imeth][ien]->SetMarkerStyle(kFullTriangleUp); // pion
      grV2[0][1][imeth][ien]->SetMarkerStyle(kOpenTriangleUp); // pion - reco
      grV2[1][0][imeth][ien]->SetMarkerStyle(kFullCircle); // proton
      grV2[1][1][imeth][ien]->SetMarkerStyle(kOpenCircle); // proton - reco

      grV2[2][0][imeth][ien]->SetMarkerStyle(kFullCircle); // proton
      grV2[2][1][imeth][ien]->SetMarkerStyle(kOpenCircle); // proton - reco

    }
  }
  for (int imeth=0;imeth<nmethod;imeth++){
    for (int ien=0;ien<nenergy;ien++){
      for (int ilev=0;ilev<nlevel;ilev++){
        // grV2[0][ilev][imeth][ien]->SetMarkerColor(kRed+1);
        // grV2[0][ilev][imeth][ien]->SetLineColor(kRed+1);
        // grV2[1][ilev][imeth][ien]->SetMarkerColor(kBlue+1);
        // grV2[1][ilev][imeth][ien]->SetLineColor(kBlue+1);
        Red(grV2[1][ilev][imeth][ien]);
        Blue(grV2[0][ilev][imeth][ien]);
        Green(grV2[2][ilev][imeth][ien]);

        for (int id=0;id<npid;id++){
          grV2[id][ilev][imeth][ien] -> SetMarkerSize(2.0);
        }
      }
      Red(grV2[2][0][imeth][ien]);
      Blue(grV2[2][1][imeth][ien]);
    }
  }

  TCanvas *can = new TCanvas("can","",200,10,1500,550);
  TPaveLabel* title = new TPaveLabel(0.1,0.945,0.9,0.98,"vHLLE+UrQMD, Au+Au, #sqrt{s_{NN}}= 11.5 GeV, 10-40%, reconstructed (GEANT4)");
  title->SetBorderSize(0);
  title->SetFillColor(0);
  title->SetTextFont(textFont);
  title->SetTextSize(2.);
  title->Draw();
  can->SetTopMargin(0.1);
  can->SetLeftMargin(0.2);
  can->SetRightMargin(0.01);
  can->SetBottomMargin(0.185);
  // can->SetFillColor(0);
  // can->SetFrameFillStyle(0);
  // can->SetBorderSize(1);
  // gROOT->SetStyle("Pub");
  gStyle->SetErrorX(0);
  // gStyle->SetPalette(kBird);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);


  can->Divide(3,1,0,0);
  TH2F *h[3];
  for (int ipad=0;ipad<3;ipad++){
    can->cd(ipad+1);
    if (ipad==0) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";;#it{v}_{3} "),1,minpt,maxpt,1,minV2,maxV2);
    else if (ipad==1) h[ipad] = new TH2F(Form("pad_%i",ipad+1),Form(";%s;#it{v}_{3}",xAxisName.Data()),1,minpt,maxpt,1,minV2,maxV2);
    else h[ipad] = new TH2F(Form("pad_%i",ipad+1),"",1,minpt,maxpt,1,minV2,maxV2);
    

      h[ipad]->GetXaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetXaxis()->SetTitleSize(titleSizeUpperPlot);
      h[ipad]->GetYaxis()->SetLabelSize(labelSizeUpperPlot);
      h[ipad]->GetYaxis()->SetTitleSize(titleSizeUpperPlot);
    

    h[ipad]->GetXaxis()->SetTitleFont(textFont);
    h[ipad]->GetYaxis()->SetTitleFont(textFont);
    h[ipad]->GetXaxis()->SetLabelFont(textFont);
    h[ipad]->GetYaxis()->SetLabelFont(textFont);
    h[ipad]->GetXaxis()->CenterTitle(true);
    h[ipad]->GetXaxis()->SetNdivisions(504);
    h[ipad]->GetXaxis()->SetTitleOffset(0.9);

    h[ipad]->GetYaxis()->SetNdivisions(504);
    h[ipad]->GetYaxis()->SetTitleOffset(1.);
    h[ipad]->Draw();
    
    TLatex tex, tex1;
    tex.SetTextFont(textFont);
    tex1.SetTextFont(textFont);
    tex.SetTextAlign(33);
    tex1.SetTextAlign(13);
    if (ipad<=4) tex.SetTextSize(labelSizeUpperPlot);
    else tex.SetTextSize(labelSizeLowerPlot);
    if (ipad<=4) tex1.SetTextSize(labelSizeUpperPlot);
    else tex1.SetTextSize(labelSizeLowerPlot);
    tex.DrawLatex(0.3,maxV2*0.95,padName[ipad].Data());
    if (ipad<5)tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("%s",graphTitle[ipad+1].Data())); // 0.95-0.025
    // if (ipad==6) tex.DrawLatex(maxpt*0.55,maxV2*0.95,"Au+Au"); // , , , 
    // if (ipad==7) tex.DrawLatex(maxpt*0.55,maxV2*0.95,"10-40%");
    // if (ipad==8) tex.DrawLatex(maxpt*0.55,maxV2*0.95,"UrQMD");
    // if (ipad==9) tex.DrawLatex(maxpt*0.55,maxV2*0.95,"GEANT4");
    // if (ipad==4) tex.DrawLatex(maxpt*0.15,maxV2*0.95,"Ch. hadrons");

    if (ipad==0) {
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("Au+Au at #sqrt{s_{NN}}=%s, 10-40%%",energy[0].Data()));
      
      TLegend *leg_pt = new TLegend(leg_coordinate[0]-0.1,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt->SetBorderSize(0);
      leg_pt->SetTextFont(textFont);
      leg_pt->SetTextSize(labelSizeUpperPlot-0.01);
      for (int ilev=0; ilev<nlevel; ilev++){
        leg_pt->AddEntry(grV2[0][ilev][0][0],legendEntries[ilev].Data(),"");
      }
      // leg_pt->Draw();
    }else if (ipad==1) {
      // tex.DrawLatex(maxpt*0.95,maxV2*0.95,Form("UrQMD         "));
      TLegend *leg_pt1 = new TLegend(leg_coordinate[0]+0.15,leg_coordinate[1],leg_coordinate[2],leg_coordinate[3]);
      leg_pt1->SetBorderSize(0);
      leg_pt1->SetTextFont(textFont);
      leg_pt1->SetTextSize(labelSizeUpperPlot-0.01);
      for (int id=0; id<npid-1; id++){
        leg_pt1->AddEntry(grV2[id][0][0][0],legendEntries1[id].Data(),"p");
      }
      // leg_pt1->Draw();
    }
    if (ipad==0)tex.DrawLatex(maxpt*0.65,maxV2*0.78,Form("open - reco"));// energy[0].Data()
    if (ipad==1)tex.DrawLatex(maxpt*0.65,maxV2*0.78,"filled - true");
    // if (ipad==6)tex.DrawLatex(maxpt*0.55,maxV2*0.78,"10M events");



    
    for (int ilev=0;ilev<nlevel;ilev++){
      for (int id=2;id<npid;id++){
        if (ipad==0) grV2[id][ilev][1][0]->Draw("P"); // PLC PMC // PLC (Palette Line Color) and PMC (Palette Marker Color)
        if (ipad==1) grV2[id][ilev][2][0]->Draw("P"); // PZ
        if (ipad==2) grV2[id][ilev][3][0]->Draw("P");


      }
    }
    // cout << "error here" << endl;
  }
  can->SaveAs(Form("Performance_v3_hadrons.pdf"));
  // can->SaveAs(Form("Performance_PID.C"));
  gROOT->SetStyle("Pub");
  can->SaveAs(Form("Performance_v3_hadrons.png"));

  
}