void ParAntVsEnergy_v3_Eta01_cent_0_60_pt()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Sun Oct  4 19:46:29 2020) by ROOT version 6.14/04
   TCanvas *canvas = new TCanvas("canvas", "plot",0,0,1000,1000);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   canvas->Range(0,0,1,1);
   canvas->SetFillColor(10);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetTickx(1);
   canvas->SetTicky(1);
   canvas->SetLeftMargin(0.16);
   canvas->SetBottomMargin(0.15);
   canvas->SetFrameFillColor(0);
   canvas->SetFrameBorderSize(115);
  
// ------------>Primitives in pad: PadAxisDown_0_1
   TPad *PadAxisDown_0_1 = new TPad("PadAxisDown_0_1", "",0.2,0,0.9,0.88);
   PadAxisDown_0_1->Draw();
   PadAxisDown_0_1->cd();
   PadAxisDown_0_1->Range(6.8,-0.009255814,68,0.014);
   PadAxisDown_0_1->SetFillColor(0);
   PadAxisDown_0_1->SetBorderMode(0);
   PadAxisDown_0_1->SetBorderSize(0);
   PadAxisDown_0_1->SetTickx(1);
   PadAxisDown_0_1->SetTicky(1);
   PadAxisDown_0_1->SetLeftMargin(0);
   PadAxisDown_0_1->SetRightMargin(0);
   PadAxisDown_0_1->SetTopMargin(0);
   PadAxisDown_0_1->SetBottomMargin(0.14);
   
   TH2F *__1 = new TH2F("__1","",2,6.8,68,2,-0.006,0.014);
   __1->SetStats(0);
   __1->SetFillColor(10);
   __1->SetFillStyle(0);
   __1->GetXaxis()->SetNdivisions(508);
   __1->GetXaxis()->SetLabelFont(42);
   __1->GetXaxis()->SetLabelOffset(0.02);
   __1->GetXaxis()->SetLabelSize(0.05);
   __1->GetXaxis()->SetTitleSize(0.05);
   __1->GetXaxis()->SetTitleOffset(1.2);
   __1->GetXaxis()->SetTitleFont(42);
   __1->GetYaxis()->SetNdivisions(505);
   __1->GetYaxis()->SetLabelFont(42);
   __1->GetYaxis()->SetLabelOffset(0.02);
   __1->GetYaxis()->SetLabelSize(0.05);
   __1->GetYaxis()->SetTitleSize(0.05);
   __1->GetYaxis()->SetTitleOffset(1.4);
   __1->GetYaxis()->SetTitleFont(42);
   __1->GetZaxis()->SetLabelFont(42);
   __1->GetZaxis()->SetLabelSize(0.035);
   __1->GetZaxis()->SetTitleSize(0.035);
   __1->GetZaxis()->SetTitleFont(42);
   __1->Draw("");
   PadAxisDown_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_1
   TPad *PadAxisLeft_0_1 = new TPad("PadAxisLeft_0_1", "",0,0.1,0.7,0.98);
   PadAxisLeft_0_1->Draw();
   PadAxisLeft_0_1->cd();
   PadAxisLeft_0_1->Range(-19.42857,-0.006,68,0.014);
   PadAxisLeft_0_1->SetFillColor(0);
   PadAxisLeft_0_1->SetBorderMode(0);
   PadAxisLeft_0_1->SetBorderSize(0);
   PadAxisLeft_0_1->SetTickx(1);
   PadAxisLeft_0_1->SetTicky(1);
   PadAxisLeft_0_1->SetLeftMargin(0.3);
   PadAxisLeft_0_1->SetRightMargin(0);
   PadAxisLeft_0_1->SetTopMargin(0);
   PadAxisLeft_0_1->SetBottomMargin(0);
   
   TH2F *__2 = new TH2F("__2","",2,6.8,68,2,-0.006,0.014);
   __2->SetStats(0);
   __2->SetFillColor(10);
   __2->SetFillStyle(0);
   __2->GetXaxis()->SetNdivisions(508);
   __2->GetXaxis()->SetLabelFont(42);
   __2->GetXaxis()->SetLabelOffset(0.02);
   __2->GetXaxis()->SetLabelSize(0.05);
   __2->GetXaxis()->SetTitleSize(0.05);
   __2->GetXaxis()->SetTitleOffset(1.2);
   __2->GetXaxis()->SetTitleFont(42);
   __2->GetYaxis()->SetNdivisions(505);
   __2->GetYaxis()->SetLabelFont(42);
   __2->GetYaxis()->SetLabelOffset(0.02);
   __2->GetYaxis()->SetLabelSize(0.05);
   __2->GetYaxis()->SetTitleSize(0.05);
   __2->GetYaxis()->SetTitleOffset(1.4);
   __2->GetYaxis()->SetTitleFont(42);
   __2->GetZaxis()->SetLabelFont(42);
   __2->GetZaxis()->SetLabelSize(0.035);
   __2->GetZaxis()->SetTitleSize(0.035);
   __2->GetZaxis()->SetTitleFont(42);
   __2->Draw("");
   PadAxisLeft_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_1
   TPad *Pad_0_1 = new TPad("Pad_0_1", "",0.2,0.1,0.9,0.98);
   Pad_0_1->Draw();
   Pad_0_1->cd();
   Pad_0_1->Range(6.8,-0.006,68,0.014);
   Pad_0_1->SetFillColor(0);
   Pad_0_1->SetBorderMode(0);
   Pad_0_1->SetBorderSize(0);
   Pad_0_1->SetTickx(1);
   Pad_0_1->SetTicky(1);
   Pad_0_1->SetLeftMargin(0);
   Pad_0_1->SetRightMargin(0);
   Pad_0_1->SetTopMargin(0);
   Pad_0_1->SetBottomMargin(0);
   
   TH2F *__3 = new TH2F("__3","",2,6.8,68,2,-0.006,0.014);
   __3->SetStats(0);
   __3->SetFillColor(10);
   __3->SetFillStyle(0);
   __3->GetXaxis()->SetNdivisions(508);
   __3->GetXaxis()->SetLabelFont(42);
   __3->GetXaxis()->SetLabelOffset(0.02);
   __3->GetXaxis()->SetLabelSize(0.05);
   __3->GetXaxis()->SetTitleSize(0.05);
   __3->GetXaxis()->SetTitleOffset(1.2);
   __3->GetXaxis()->SetTitleFont(42);
   __3->GetYaxis()->SetNdivisions(505);
   __3->GetYaxis()->SetLabelFont(42);
   __3->GetYaxis()->SetLabelOffset(0.02);
   __3->GetYaxis()->SetLabelSize(0.05);
   __3->GetYaxis()->SetTitleSize(0.05);
   __3->GetYaxis()->SetTitleOffset(1.4);
   __3->GetYaxis()->SetTitleFont(42);
   __3->GetZaxis()->SetLabelFont(42);
   __3->GetZaxis()->SetLabelSize(0.035);
   __3->GetZaxis()->SetTitleSize(0.035);
   __3->GetZaxis()->SetTitleFont(42);
   __3->Draw("");
   
   TLegend *leg = new TLegend(0.7,0.75,0.94,0.98,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("data_v3_Pion","#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v3_Kaon","#font[42]{#scale[1.1]{K^{+} - K^{-}}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v3_Proton","#font[42]{#scale[1.1]{p - #bar{p}}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   leg->Draw();
   TLatex *   tex = new TLatex(0.04,0.0119,"#font[42]{(a)}");
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v3_Pion_systematic_fx1001[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Pion_systematic_fy1001[6] = {
   -0.0004232856,
   -0.0007534253,
   -0.0005631702,
   -0.0003948853,
   -9.628227e-05,
   8.284806e-05};
   Double_t data_v3_Pion_systematic_fex1001[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Pion_systematic_fey1001[6] = {
   0.0007139736,
   0.0003977314,
   0.0002079363,
   3.163268e-05,
   6.491327e-05,
   2.814549e-05};
   TGraphErrors *gre = new TGraphErrors(6,data_v3_Pion_systematic_fx1001,data_v3_Pion_systematic_fy1001,data_v3_Pion_systematic_fex1001,data_v3_Pion_systematic_fey1001);
   gre->SetName("data_v3_Pion_systematic");
   gre->SetTitle("#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1179;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Pion_systematic1001 = new TH1F("Graph_data_v3_Pion_systematic1001","#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}",100,4.61,69.29);
   Graph_data_v3_Pion_systematic1001->SetMinimum(-0.001295341);
   Graph_data_v3_Pion_systematic1001->SetMaximum(0.0004348725);
   Graph_data_v3_Pion_systematic1001->SetDirectory(0);
   Graph_data_v3_Pion_systematic1001->SetStats(0);
   Graph_data_v3_Pion_systematic1001->SetFillColor(10);
   Graph_data_v3_Pion_systematic1001->SetFillStyle(0);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Pion_systematic1001->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Pion_systematic1001->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Pion_systematic1001->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Pion_systematic1001->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Pion_systematic1001->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Pion_systematic1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Pion_systematic1001);
   
   gre->Draw("e5");
   
   Double_t data_v3_Kaon_systematic_fx1002[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Kaon_systematic_fy1002[6] = {
   0.003455926,
   0.002029796,
   0.0008757857,
   0.0003111092,
   0.0002844904,
   0.0008691442};
   Double_t data_v3_Kaon_systematic_fex1002[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Kaon_systematic_fey1002[6] = {
   0.001337374,
   0.001227987,
   0.000690503,
   7.8295e-05,
   0.0001431508,
   0.0002798572};
   gre = new TGraphErrors(6,data_v3_Kaon_systematic_fx1002,data_v3_Kaon_systematic_fy1002,data_v3_Kaon_systematic_fex1002,data_v3_Kaon_systematic_fey1002);
   gre->SetName("data_v3_Kaon_systematic");
   gre->SetTitle("#font[42]{#scale[1.1]{K^{+} - K^{-}}}");

   ci = 1180;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_Kaon_systematic1002 = new TH1F("Graph_data_v3_Kaon_systematic1002","#font[42]{#scale[1.1]{K^{+} - K^{-}}}",100,4.61,69.29);
   Graph_data_v3_Kaon_systematic1002->SetMinimum(0.0001272056);
   Graph_data_v3_Kaon_systematic1002->SetMaximum(0.005258496);
   Graph_data_v3_Kaon_systematic1002->SetDirectory(0);
   Graph_data_v3_Kaon_systematic1002->SetStats(0);
   Graph_data_v3_Kaon_systematic1002->SetFillColor(10);
   Graph_data_v3_Kaon_systematic1002->SetFillStyle(0);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Kaon_systematic1002->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Kaon_systematic1002->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon_systematic1002->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon_systematic1002->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Kaon_systematic1002->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Kaon_systematic1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Kaon_systematic1002);
   
   gre->Draw("e5");
   
   Double_t data_v3_Proton_systematic_fx1003[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Proton_systematic_fy1003[6] = {
   -0.0002391825,
   0.005787852,
   0.007293476,
   0.004291609,
   0.003160696,
   0.001426514};
   Double_t data_v3_Proton_systematic_fex1003[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Proton_systematic_fey1003[6] = {
   0.01149244,
   0.0009371489,
   0.001079533,
   0.0002704333,
   0.0002992574,
   0.0002942052};
   gre = new TGraphErrors(6,data_v3_Proton_systematic_fx1003,data_v3_Proton_systematic_fy1003,data_v3_Proton_systematic_fex1003,data_v3_Proton_systematic_fey1003);
   gre->SetName("data_v3_Proton_systematic");
   gre->SetTitle("#font[42]{#scale[1.1]{p - #bar{p}}}");

   ci = 1181;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_Proton_systematic1003 = new TH1F("Graph_data_v3_Proton_systematic1003","#font[42]{#scale[1.1]{p - #bar{p}}}",100,4.61,69.29);
   Graph_data_v3_Proton_systematic1003->SetMinimum(-0.01403011);
   Graph_data_v3_Proton_systematic1003->SetMaximum(0.01355175);
   Graph_data_v3_Proton_systematic1003->SetDirectory(0);
   Graph_data_v3_Proton_systematic1003->SetStats(0);
   Graph_data_v3_Proton_systematic1003->SetFillColor(10);
   Graph_data_v3_Proton_systematic1003->SetFillStyle(0);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Proton_systematic1003->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Proton_systematic1003->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Proton_systematic1003->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Proton_systematic1003->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Proton_systematic1003->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Proton_systematic1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Proton_systematic1003);
   
   gre->Draw("e5");
   
   Double_t data_v3_Pion_systematic_fx1004[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Pion_systematic_fy1004[6] = {
   -0.0004232856,
   -0.0007534253,
   -0.0005631702,
   -0.0003948853,
   -9.628227e-05,
   8.284806e-05};
   Double_t data_v3_Pion_systematic_fex1004[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Pion_systematic_fey1004[6] = {
   0.0007139736,
   0.0003977314,
   0.0002079363,
   3.163268e-05,
   6.491327e-05,
   2.814549e-05};
   gre = new TGraphErrors(6,data_v3_Pion_systematic_fx1004,data_v3_Pion_systematic_fy1004,data_v3_Pion_systematic_fex1004,data_v3_Pion_systematic_fey1004);
   gre->SetName("data_v3_Pion_systematic");
   gre->SetTitle("#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}");

   ci = 1182;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Pion_systematic1004 = new TH1F("Graph_data_v3_Pion_systematic1004","#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}",100,4.61,69.29);
   Graph_data_v3_Pion_systematic1004->SetMinimum(-0.001295341);
   Graph_data_v3_Pion_systematic1004->SetMaximum(0.0004348725);
   Graph_data_v3_Pion_systematic1004->SetDirectory(0);
   Graph_data_v3_Pion_systematic1004->SetStats(0);
   Graph_data_v3_Pion_systematic1004->SetFillColor(10);
   Graph_data_v3_Pion_systematic1004->SetFillStyle(0);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Pion_systematic1004->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Pion_systematic1004->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Pion_systematic1004->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Pion_systematic1004->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Pion_systematic1004->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Pion_systematic1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Pion_systematic1004);
   
   gre->Draw("e5");
   
   Double_t data_v3_Kaon_systematic_fx1005[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Kaon_systematic_fy1005[6] = {
   0.003455926,
   0.002029796,
   0.0008757857,
   0.0003111092,
   0.0002844904,
   0.0008691442};
   Double_t data_v3_Kaon_systematic_fex1005[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Kaon_systematic_fey1005[6] = {
   0.001337374,
   0.001227987,
   0.000690503,
   7.8295e-05,
   0.0001431508,
   0.0002798572};
   gre = new TGraphErrors(6,data_v3_Kaon_systematic_fx1005,data_v3_Kaon_systematic_fy1005,data_v3_Kaon_systematic_fex1005,data_v3_Kaon_systematic_fey1005);
   gre->SetName("data_v3_Kaon_systematic");
   gre->SetTitle("#font[42]{#scale[1.1]{K^{+} - K^{-}}}");

   ci = 1183;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_Kaon_systematic1005 = new TH1F("Graph_data_v3_Kaon_systematic1005","#font[42]{#scale[1.1]{K^{+} - K^{-}}}",100,4.61,69.29);
   Graph_data_v3_Kaon_systematic1005->SetMinimum(0.0001272056);
   Graph_data_v3_Kaon_systematic1005->SetMaximum(0.005258496);
   Graph_data_v3_Kaon_systematic1005->SetDirectory(0);
   Graph_data_v3_Kaon_systematic1005->SetStats(0);
   Graph_data_v3_Kaon_systematic1005->SetFillColor(10);
   Graph_data_v3_Kaon_systematic1005->SetFillStyle(0);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Kaon_systematic1005->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Kaon_systematic1005->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon_systematic1005->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon_systematic1005->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Kaon_systematic1005->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Kaon_systematic1005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Kaon_systematic1005);
   
   gre->Draw("e5");
   
   Double_t data_v3_Proton_systematic_fx1006[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Proton_systematic_fy1006[6] = {
   -0.0002391825,
   0.005787852,
   0.007293476,
   0.004291609,
   0.003160696,
   0.001426514};
   Double_t data_v3_Proton_systematic_fex1006[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Proton_systematic_fey1006[6] = {
   0.01149244,
   0.0009371489,
   0.001079533,
   0.0002704333,
   0.0002992574,
   0.0002942052};
   gre = new TGraphErrors(6,data_v3_Proton_systematic_fx1006,data_v3_Proton_systematic_fy1006,data_v3_Proton_systematic_fex1006,data_v3_Proton_systematic_fey1006);
   gre->SetName("data_v3_Proton_systematic");
   gre->SetTitle("#font[42]{#scale[1.1]{p - #bar{p}}}");

   ci = 1184;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_Proton_systematic1006 = new TH1F("Graph_data_v3_Proton_systematic1006","#font[42]{#scale[1.1]{p - #bar{p}}}",100,4.61,69.29);
   Graph_data_v3_Proton_systematic1006->SetMinimum(-0.01403011);
   Graph_data_v3_Proton_systematic1006->SetMaximum(0.01355175);
   Graph_data_v3_Proton_systematic1006->SetDirectory(0);
   Graph_data_v3_Proton_systematic1006->SetStats(0);
   Graph_data_v3_Proton_systematic1006->SetFillColor(10);
   Graph_data_v3_Proton_systematic1006->SetFillStyle(0);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Proton_systematic1006->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Proton_systematic1006->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Proton_systematic1006->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Proton_systematic1006->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Proton_systematic1006->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Proton_systematic1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Proton_systematic1006);
   
   gre->Draw("e5");
   
   Double_t data_v3_Pion_fx1007[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Pion_fy1007[6] = {
   -0.0004232856,
   -0.0007534253,
   -0.0005631702,
   -0.0003948853,
   -9.628227e-05,
   8.284806e-05};
   Double_t data_v3_Pion_fex1007[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Pion_fey1007[6] = {
   0.0009357613,
   0.0005148635,
   0.0003958505,
   8.032104e-05,
   0.0001371949,
   0.0001695362};
   gre = new TGraphErrors(6,data_v3_Pion_fx1007,data_v3_Pion_fy1007,data_v3_Pion_fex1007,data_v3_Pion_fey1007);
   gre->SetName("data_v3_Pion");
   gre->SetTitle("#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_Pion1007 = new TH1F("Graph_data_v3_Pion1007","#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}",100,6.41,67.49);
   Graph_data_v3_Pion1007->SetMinimum(-0.001546199);
   Graph_data_v3_Pion1007->SetMaximum(0.000699628);
   Graph_data_v3_Pion1007->SetDirectory(0);
   Graph_data_v3_Pion1007->SetStats(0);
   Graph_data_v3_Pion1007->SetFillColor(10);
   Graph_data_v3_Pion1007->SetFillStyle(0);
   Graph_data_v3_Pion1007->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Pion1007->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Pion1007->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion1007->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion1007->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion1007->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Pion1007->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Pion1007->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Pion1007->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Pion1007->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion1007->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion1007->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion1007->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Pion1007->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Pion1007->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Pion1007->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Pion1007->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Pion1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Pion1007);
   
   gre->Draw("p");
   
   Double_t data_v3_Kaon_fx1008[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Kaon_fy1008[6] = {
   0.003455926,
   0.002029796,
   0.0008757857,
   0.0003111092,
   0.0002844904,
   0.0008691442};
   Double_t data_v3_Kaon_fex1008[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Kaon_fey1008[6] = {
   0.002778778,
   0.001556635,
   0.001141946,
   0.0002256084,
   0.0003850383,
   0.0004996817};
   gre = new TGraphErrors(6,data_v3_Kaon_fx1008,data_v3_Kaon_fy1008,data_v3_Kaon_fex1008,data_v3_Kaon_fey1008);
   gre->SetName("data_v3_Kaon");
   gre->SetTitle("#font[42]{#scale[1.1]{K^{+} - K^{-}}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_Kaon1008 = new TH1F("Graph_data_v3_Kaon1008","#font[42]{#scale[1.1]{K^{+} - K^{-}}}",100,6.41,67.49);
   Graph_data_v3_Kaon1008->SetMinimum(-0.0009162467);
   Graph_data_v3_Kaon1008->SetMaximum(0.006884791);
   Graph_data_v3_Kaon1008->SetDirectory(0);
   Graph_data_v3_Kaon1008->SetStats(0);
   Graph_data_v3_Kaon1008->SetFillColor(10);
   Graph_data_v3_Kaon1008->SetFillStyle(0);
   Graph_data_v3_Kaon1008->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Kaon1008->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon1008->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon1008->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon1008->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon1008->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Kaon1008->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon1008->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Kaon1008->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon1008->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon1008->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon1008->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon1008->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Kaon1008->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon1008->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon1008->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Kaon1008->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Kaon1008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Kaon1008);
   
   gre->Draw("p");
   
   Double_t data_v3_Proton_fx1009[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Proton_fy1009[6] = {
   -0.0002391825,
   0.005787852,
   0.007293476,
   0.004291609,
   0.003160696,
   0.001426514};
   Double_t data_v3_Proton_fex1009[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Proton_fey1009[6] = {
   0.005463638,
   0.002420407,
   0.001570812,
   0.0002753704,
   0.0004334752,
   0.0005155895};
   gre = new TGraphErrors(6,data_v3_Proton_fx1009,data_v3_Proton_fy1009,data_v3_Proton_fex1009,data_v3_Proton_fey1009);
   gre->SetName("data_v3_Proton");
   gre->SetTitle("#font[42]{#scale[1.1]{p - #bar{p}}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_Proton1009 = new TH1F("Graph_data_v3_Proton1009","#font[42]{#scale[1.1]{p - #bar{p}}}",100,6.41,67.49);
   Graph_data_v3_Proton1009->SetMinimum(-0.007159532);
   Graph_data_v3_Proton1009->SetMaximum(0.010321);
   Graph_data_v3_Proton1009->SetDirectory(0);
   Graph_data_v3_Proton1009->SetStats(0);
   Graph_data_v3_Proton1009->SetFillColor(10);
   Graph_data_v3_Proton1009->SetFillStyle(0);
   Graph_data_v3_Proton1009->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Proton1009->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Proton1009->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton1009->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton1009->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton1009->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Proton1009->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Proton1009->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Proton1009->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Proton1009->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton1009->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton1009->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton1009->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Proton1009->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Proton1009->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Proton1009->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Proton1009->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Proton1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Proton1009);
   
   gre->Draw("p");
   
   Double_t data_v3_Pion_fx1010[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Pion_fy1010[6] = {
   -0.0004232856,
   -0.0007534253,
   -0.0005631702,
   -0.0003948853,
   -9.628227e-05,
   8.284806e-05};
   Double_t data_v3_Pion_fex1010[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Pion_fey1010[6] = {
   0.0009357613,
   0.0005148635,
   0.0003958505,
   8.032104e-05,
   0.0001371949,
   0.0001695362};
   gre = new TGraphErrors(6,data_v3_Pion_fx1010,data_v3_Pion_fy1010,data_v3_Pion_fex1010,data_v3_Pion_fey1010);
   gre->SetName("data_v3_Pion");
   gre->SetTitle("#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_Pion1010 = new TH1F("Graph_data_v3_Pion1010","#font[42]{#scale[1.1]{#pi^{+} - #pi^{-}}}",100,6.41,67.49);
   Graph_data_v3_Pion1010->SetMinimum(-0.001546199);
   Graph_data_v3_Pion1010->SetMaximum(0.000699628);
   Graph_data_v3_Pion1010->SetDirectory(0);
   Graph_data_v3_Pion1010->SetStats(0);
   Graph_data_v3_Pion1010->SetFillColor(10);
   Graph_data_v3_Pion1010->SetFillStyle(0);
   Graph_data_v3_Pion1010->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Pion1010->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Pion1010->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion1010->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion1010->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion1010->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Pion1010->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Pion1010->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Pion1010->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Pion1010->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Pion1010->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Pion1010->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Pion1010->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Pion1010->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Pion1010->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Pion1010->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Pion1010->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Pion1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Pion1010);
   
   gre->Draw("p");
   
   Double_t data_v3_Kaon_fx1011[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Kaon_fy1011[6] = {
   0.003455926,
   0.002029796,
   0.0008757857,
   0.0003111092,
   0.0002844904,
   0.0008691442};
   Double_t data_v3_Kaon_fex1011[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Kaon_fey1011[6] = {
   0.002778778,
   0.001556635,
   0.001141946,
   0.0002256084,
   0.0003850383,
   0.0004996817};
   gre = new TGraphErrors(6,data_v3_Kaon_fx1011,data_v3_Kaon_fy1011,data_v3_Kaon_fex1011,data_v3_Kaon_fey1011);
   gre->SetName("data_v3_Kaon");
   gre->SetTitle("#font[42]{#scale[1.1]{K^{+} - K^{-}}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_Kaon1011 = new TH1F("Graph_data_v3_Kaon1011","#font[42]{#scale[1.1]{K^{+} - K^{-}}}",100,6.41,67.49);
   Graph_data_v3_Kaon1011->SetMinimum(-0.0009162467);
   Graph_data_v3_Kaon1011->SetMaximum(0.006884791);
   Graph_data_v3_Kaon1011->SetDirectory(0);
   Graph_data_v3_Kaon1011->SetStats(0);
   Graph_data_v3_Kaon1011->SetFillColor(10);
   Graph_data_v3_Kaon1011->SetFillStyle(0);
   Graph_data_v3_Kaon1011->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Kaon1011->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon1011->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon1011->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon1011->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon1011->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Kaon1011->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon1011->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Kaon1011->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon1011->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Kaon1011->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Kaon1011->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Kaon1011->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Kaon1011->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Kaon1011->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Kaon1011->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Kaon1011->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Kaon1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Kaon1011);
   
   gre->Draw("p");
   
   Double_t data_v3_Proton_fx1012[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Proton_fy1012[6] = {
   -0.0002391825,
   0.005787852,
   0.007293476,
   0.004291609,
   0.003160696,
   0.001426514};
   Double_t data_v3_Proton_fex1012[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Proton_fey1012[6] = {
   0.005463638,
   0.002420407,
   0.001570812,
   0.0002753704,
   0.0004334752,
   0.0005155895};
   gre = new TGraphErrors(6,data_v3_Proton_fx1012,data_v3_Proton_fy1012,data_v3_Proton_fex1012,data_v3_Proton_fey1012);
   gre->SetName("data_v3_Proton");
   gre->SetTitle("#font[42]{#scale[1.1]{p - #bar{p}}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_Proton1012 = new TH1F("Graph_data_v3_Proton1012","#font[42]{#scale[1.1]{p - #bar{p}}}",100,6.41,67.49);
   Graph_data_v3_Proton1012->SetMinimum(-0.007159532);
   Graph_data_v3_Proton1012->SetMaximum(0.010321);
   Graph_data_v3_Proton1012->SetDirectory(0);
   Graph_data_v3_Proton1012->SetStats(0);
   Graph_data_v3_Proton1012->SetFillColor(10);
   Graph_data_v3_Proton1012->SetFillStyle(0);
   Graph_data_v3_Proton1012->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Proton1012->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Proton1012->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton1012->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton1012->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton1012->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Proton1012->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Proton1012->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Proton1012->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Proton1012->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Proton1012->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Proton1012->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Proton1012->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Proton1012->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Proton1012->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Proton1012->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Proton1012->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Proton1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Proton1012);
   
   gre->Draw("p");
   TLine *line = new TLine(6.8,0,68,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(6.8,1,68,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(13.6,0.0119,"#font[42]{ #scale[1.2]{ #splitline{Au+Au, 0-60 %}{STAR Preliminary} }}");
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pad_AxisY
   TPad *pad_AxisY = new TPad("pad_AxisY", "",0,0.1,0.1,1);
   pad_AxisY->Draw();
   pad_AxisY->cd();
   pad_AxisY->Range(0,0,1,1);
   pad_AxisY->SetFillColor(0);
   pad_AxisY->SetBorderMode(0);
   pad_AxisY->SetBorderSize(0);
   pad_AxisY->SetTickx(1);
   pad_AxisY->SetTicky(1);
   pad_AxisY->SetLeftMargin(0.16);
   pad_AxisY->SetRightMargin(0.23);
   pad_AxisY->SetBottomMargin(0);
   pad_AxisY->SetFrameBorderMode(0);
      tex = new TLatex(0.6,0.4,"#font[42]{ v_{3}(X) - v_{3}(#bar{X}) }");
   tex->SetTextSize(0.5);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
   pad_AxisY->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pad_AxisX
   TPad *pad_AxisX = new TPad("pad_AxisX", "",0,0,1,0.07);
   pad_AxisX->Draw();
   pad_AxisX->cd();
   pad_AxisX->Range(0,0,1,1);
   pad_AxisX->SetFillColor(0);
   pad_AxisX->SetBorderMode(0);
   pad_AxisX->SetBorderSize(0);
   pad_AxisX->SetTickx(1);
   pad_AxisX->SetTicky(1);
   pad_AxisX->SetLeftMargin(0.16);
   pad_AxisX->SetTopMargin(0);
   pad_AxisX->SetBottomMargin(0);
   pad_AxisX->SetFrameBorderMode(0);
      tex = new TLatex(0.5,0.4,"#font[42]{#sqrt{s_{NN}} [GeV]}");
   tex->SetTextSize(0.6);
   tex->SetLineWidth(2);
   tex->Draw();
   pad_AxisX->Modified();
   canvas->cd();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
