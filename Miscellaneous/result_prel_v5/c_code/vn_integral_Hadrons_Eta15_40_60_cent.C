void vn_integral_Hadrons_Eta15_40_60_cent()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Wed Oct  7 17:23:29 2020) by ROOT version 6.14/04
   TCanvas *canvas = new TCanvas("canvas", "plot",0,0,1000,1280);
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
   TPad *PadAxisDown_0_1 = new TPad("PadAxisDown_0_1", "",0.16,0,0.53,0.2933333);
   PadAxisDown_0_1->Draw();
   PadAxisDown_0_1->cd();
   PadAxisDown_0_1->Range(4,-0.06961539,75,0.115);
   PadAxisDown_0_1->SetFillColor(0);
   PadAxisDown_0_1->SetBorderMode(0);
   PadAxisDown_0_1->SetBorderSize(0);
   PadAxisDown_0_1->SetTickx(1);
   PadAxisDown_0_1->SetTicky(1);
   PadAxisDown_0_1->SetLeftMargin(0);
   PadAxisDown_0_1->SetRightMargin(0);
   PadAxisDown_0_1->SetTopMargin(0);
   PadAxisDown_0_1->SetBottomMargin(0.35);
   
   TH2F *__1 = new TH2F("__1","",2,4,75,2,-0.005,0.115);
   __1->SetStats(0);
   __1->SetFillColor(10);
   __1->SetFillStyle(0);
   __1->GetXaxis()->SetNdivisions(508);
   __1->GetXaxis()->SetLabelFont(42);
   __1->GetXaxis()->SetLabelOffset(0.02);
   __1->GetXaxis()->SetLabelSize(0.086);
   __1->GetXaxis()->SetTitleSize(0.05);
   __1->GetXaxis()->SetTitleOffset(1.2);
   __1->GetXaxis()->SetTitleFont(42);
   __1->GetYaxis()->SetNdivisions(505);
   __1->GetYaxis()->SetLabelFont(42);
   __1->GetYaxis()->SetLabelOffset(0.02);
   __1->GetYaxis()->SetLabelSize(0.086);
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
  
// ------------>Primitives in pad: PadAxisDown_1_1
   TPad *PadAxisDown_1_1 = new TPad("PadAxisDown_1_1", "",0.53,0,0.9,0.2933333);
   PadAxisDown_1_1->Draw();
   PadAxisDown_1_1->cd();
   PadAxisDown_1_1->Range(4,-0.06961539,75,0.115);
   PadAxisDown_1_1->SetFillColor(0);
   PadAxisDown_1_1->SetBorderMode(0);
   PadAxisDown_1_1->SetBorderSize(0);
   PadAxisDown_1_1->SetTickx(1);
   PadAxisDown_1_1->SetTicky(1);
   PadAxisDown_1_1->SetLeftMargin(0);
   PadAxisDown_1_1->SetRightMargin(0);
   PadAxisDown_1_1->SetTopMargin(0);
   PadAxisDown_1_1->SetBottomMargin(0.35);
   
   TH2F *__2 = new TH2F("__2","",2,4,75,2,-0.005,0.115);
   __2->SetStats(0);
   __2->SetFillColor(10);
   __2->SetFillStyle(0);
   __2->GetXaxis()->SetNdivisions(508);
   __2->GetXaxis()->SetLabelFont(42);
   __2->GetXaxis()->SetLabelOffset(0.02);
   __2->GetXaxis()->SetLabelSize(0.086);
   __2->GetXaxis()->SetTitleSize(0.05);
   __2->GetXaxis()->SetTitleOffset(1.2);
   __2->GetXaxis()->SetTitleFont(42);
   __2->GetYaxis()->SetNdivisions(505);
   __2->GetYaxis()->SetLabelFont(42);
   __2->GetYaxis()->SetLabelOffset(0.02);
   __2->GetYaxis()->SetLabelSize(0.086);
   __2->GetYaxis()->SetTitleSize(0.05);
   __2->GetYaxis()->SetTitleOffset(1.4);
   __2->GetYaxis()->SetTitleFont(42);
   __2->GetZaxis()->SetLabelFont(42);
   __2->GetZaxis()->SetLabelSize(0.035);
   __2->GetZaxis()->SetTitleSize(0.035);
   __2->GetZaxis()->SetTitleFont(42);
   __2->Draw("");
   PadAxisDown_1_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_3
   TPad *PadAxisLeft_0_3 = new TPad("PadAxisLeft_0_3", "",0,0.6866667,0.37,0.98);
   PadAxisLeft_0_3->Draw();
   PadAxisLeft_0_3->cd();
   PadAxisLeft_0_3->Range(-51.78571,-0.005,75,0.115);
   PadAxisLeft_0_3->SetFillColor(0);
   PadAxisLeft_0_3->SetBorderMode(0);
   PadAxisLeft_0_3->SetBorderSize(0);
   PadAxisLeft_0_3->SetTickx(1);
   PadAxisLeft_0_3->SetTicky(1);
   PadAxisLeft_0_3->SetLeftMargin(0.44);
   PadAxisLeft_0_3->SetRightMargin(0);
   PadAxisLeft_0_3->SetTopMargin(0);
   PadAxisLeft_0_3->SetBottomMargin(0);
   
   TH2F *__3 = new TH2F("__3","",2,4,75,2,-0.005,0.115);
   __3->SetStats(0);
   __3->SetFillColor(10);
   __3->SetFillStyle(0);
   __3->GetXaxis()->SetNdivisions(508);
   __3->GetXaxis()->SetLabelFont(42);
   __3->GetXaxis()->SetLabelOffset(0.02);
   __3->GetXaxis()->SetLabelSize(0.086);
   __3->GetXaxis()->SetTitleSize(0.05);
   __3->GetXaxis()->SetTitleOffset(1.2);
   __3->GetXaxis()->SetTitleFont(42);
   __3->GetYaxis()->SetNdivisions(505);
   __3->GetYaxis()->SetLabelFont(42);
   __3->GetYaxis()->SetLabelOffset(0.02);
   __3->GetYaxis()->SetLabelSize(0.086);
   __3->GetYaxis()->SetTitleSize(0.05);
   __3->GetYaxis()->SetTitleOffset(1.4);
   __3->GetYaxis()->SetTitleFont(42);
   __3->GetZaxis()->SetLabelFont(42);
   __3->GetZaxis()->SetLabelSize(0.035);
   __3->GetZaxis()->SetTitleSize(0.035);
   __3->GetZaxis()->SetTitleFont(42);
   __3->Draw("");
   PadAxisLeft_0_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_2
   TPad *PadAxisLeft_0_2 = new TPad("PadAxisLeft_0_2", "",0,0.3933333,0.37,0.6866667);
   PadAxisLeft_0_2->Draw();
   PadAxisLeft_0_2->cd();
   PadAxisLeft_0_2->Range(-51.78571,-0.005,75,0.115);
   PadAxisLeft_0_2->SetFillColor(0);
   PadAxisLeft_0_2->SetBorderMode(0);
   PadAxisLeft_0_2->SetBorderSize(0);
   PadAxisLeft_0_2->SetTickx(1);
   PadAxisLeft_0_2->SetTicky(1);
   PadAxisLeft_0_2->SetLeftMargin(0.44);
   PadAxisLeft_0_2->SetRightMargin(0);
   PadAxisLeft_0_2->SetTopMargin(0);
   PadAxisLeft_0_2->SetBottomMargin(0);
   
   TH2F *__4 = new TH2F("__4","",2,4,75,2,-0.005,0.115);
   __4->SetStats(0);
   __4->SetFillColor(10);
   __4->SetFillStyle(0);
   __4->GetXaxis()->SetNdivisions(508);
   __4->GetXaxis()->SetLabelFont(42);
   __4->GetXaxis()->SetLabelOffset(0.02);
   __4->GetXaxis()->SetLabelSize(0.086);
   __4->GetXaxis()->SetTitleSize(0.05);
   __4->GetXaxis()->SetTitleOffset(1.2);
   __4->GetXaxis()->SetTitleFont(42);
   __4->GetYaxis()->SetNdivisions(505);
   __4->GetYaxis()->SetLabelFont(42);
   __4->GetYaxis()->SetLabelOffset(0.02);
   __4->GetYaxis()->SetLabelSize(0.086);
   __4->GetYaxis()->SetTitleSize(0.05);
   __4->GetYaxis()->SetTitleOffset(1.4);
   __4->GetYaxis()->SetTitleFont(42);
   __4->GetZaxis()->SetLabelFont(42);
   __4->GetZaxis()->SetLabelSize(0.035);
   __4->GetZaxis()->SetTitleSize(0.035);
   __4->GetZaxis()->SetTitleFont(42);
   __4->Draw("");
   PadAxisLeft_0_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_1
   TPad *PadAxisLeft_0_1 = new TPad("PadAxisLeft_0_1", "",0,0.1,0.37,0.3933333);
   PadAxisLeft_0_1->Draw();
   PadAxisLeft_0_1->cd();
   PadAxisLeft_0_1->Range(-51.78571,-0.005,75,0.115);
   PadAxisLeft_0_1->SetFillColor(0);
   PadAxisLeft_0_1->SetBorderMode(0);
   PadAxisLeft_0_1->SetBorderSize(0);
   PadAxisLeft_0_1->SetTickx(1);
   PadAxisLeft_0_1->SetTicky(1);
   PadAxisLeft_0_1->SetLeftMargin(0.44);
   PadAxisLeft_0_1->SetRightMargin(0);
   PadAxisLeft_0_1->SetTopMargin(0);
   PadAxisLeft_0_1->SetBottomMargin(0);
   
   TH2F *__5 = new TH2F("__5","",2,4,75,2,-0.005,0.115);
   __5->SetStats(0);
   __5->SetFillColor(10);
   __5->SetFillStyle(0);
   __5->GetXaxis()->SetNdivisions(508);
   __5->GetXaxis()->SetLabelFont(42);
   __5->GetXaxis()->SetLabelOffset(0.02);
   __5->GetXaxis()->SetLabelSize(0.086);
   __5->GetXaxis()->SetTitleSize(0.05);
   __5->GetXaxis()->SetTitleOffset(1.2);
   __5->GetXaxis()->SetTitleFont(42);
   __5->GetYaxis()->SetNdivisions(505);
   __5->GetYaxis()->SetLabelFont(42);
   __5->GetYaxis()->SetLabelOffset(0.02);
   __5->GetYaxis()->SetLabelSize(0.086);
   __5->GetYaxis()->SetTitleSize(0.05);
   __5->GetYaxis()->SetTitleOffset(1.4);
   __5->GetYaxis()->SetTitleFont(42);
   __5->GetZaxis()->SetLabelFont(42);
   __5->GetZaxis()->SetLabelSize(0.035);
   __5->GetZaxis()->SetTitleSize(0.035);
   __5->GetZaxis()->SetTitleFont(42);
   __5->Draw("");
   PadAxisLeft_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_3
   TPad *Pad_0_3 = new TPad("Pad_0_3", "",0.16,0.6866667,0.53,0.98);
   Pad_0_3->Draw();
   Pad_0_3->cd();
   Pad_0_3->Range(4,-0.005,75,0.115);
   Pad_0_3->SetFillColor(0);
   Pad_0_3->SetBorderMode(0);
   Pad_0_3->SetBorderSize(0);
   Pad_0_3->SetTickx(1);
   Pad_0_3->SetTicky(1);
   Pad_0_3->SetLeftMargin(0);
   Pad_0_3->SetRightMargin(0);
   Pad_0_3->SetTopMargin(0);
   Pad_0_3->SetBottomMargin(0);
   
   TH2F *__6 = new TH2F("__6","",2,4,75,2,-0.005,0.115);
   __6->SetStats(0);
   __6->SetFillColor(10);
   __6->SetFillStyle(0);
   __6->GetXaxis()->SetNdivisions(508);
   __6->GetXaxis()->SetLabelFont(42);
   __6->GetXaxis()->SetLabelOffset(0.02);
   __6->GetXaxis()->SetLabelSize(0.086);
   __6->GetXaxis()->SetTitleSize(0.05);
   __6->GetXaxis()->SetTitleOffset(1.2);
   __6->GetXaxis()->SetTitleFont(42);
   __6->GetYaxis()->SetNdivisions(505);
   __6->GetYaxis()->SetLabelFont(42);
   __6->GetYaxis()->SetLabelOffset(0.02);
   __6->GetYaxis()->SetLabelSize(0.086);
   __6->GetYaxis()->SetTitleSize(0.05);
   __6->GetYaxis()->SetTitleOffset(1.4);
   __6->GetYaxis()->SetTitleFont(42);
   __6->GetZaxis()->SetLabelFont(42);
   __6->GetZaxis()->SetLabelSize(0.035);
   __6->GetZaxis()->SetTitleSize(0.035);
   __6->GetZaxis()->SetTitleFont(42);
   __6->Draw("");
   TLatex *   tex = new TLatex(8,0.09775,"#font[42]{#scale[0.85]{(a) 0-5%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fx1001[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fy1001[6] = {
   0.02154405,
   0.02313725,
   0.02492008,
   0.02648572,
   0.02752172,
   0.02941932};
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fex1001[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fey1001[6] = {
   0.0005004225,
   0.0004495822,
   0.0004710829,
   0.0004507319,
   0.0004673649,
   0.0004352811};
   TGraphErrors *gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_0_5_systematic_fx1001,data_v2_Hadrons_int_cent_0_5_systematic_fy1001,data_v2_Hadrons_int_cent_0_5_systematic_fex1001,data_v2_Hadrons_int_cent_0_5_systematic_fey1001);
   gre->SetName("data_v2_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1179;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_0_5_systematic1001 = new TH1F("Graph_data_v2_Hadrons_int_cent_0_5_systematic1001","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->SetMinimum(0.02016253);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->SetMaximum(0.0307357);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_0_5_systematic1001);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fx1002[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fy1002[6] = {
   0.01529551,
   0.01525391,
   0.01582622,
   0.01663384,
   0.01780232,
   0.01932488};
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fex1002[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fey1002[6] = {
   0.0003053906,
   0.0002916635,
   0.000222263,
   0.0001943055,
   0.0002706086,
   0.0002392051};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_0_5_systematic_fx1002,data_v3_Hadrons_int_cent_0_5_systematic_fy1002,data_v3_Hadrons_int_cent_0_5_systematic_fex1002,data_v3_Hadrons_int_cent_0_5_systematic_fey1002);
   gre->SetName("data_v3_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1180;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_0_5_systematic1002 = new TH1F("Graph_data_v3_Hadrons_int_cent_0_5_systematic1002","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->SetMinimum(0.01450206);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->SetMaximum(0.02002427);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_0_5_systematic1002);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fx1003[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fy1003[6] = {
   0.02154405,
   0.02313725,
   0.02492008,
   0.02648572,
   0.02752172,
   0.02941932};
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fex1003[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_0_5_systematic_fey1003[6] = {
   0.0005004225,
   0.0004495822,
   0.0004710829,
   0.0004507319,
   0.0004673649,
   0.0004352811};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_0_5_systematic_fx1003,data_v2_Hadrons_int_cent_0_5_systematic_fy1003,data_v2_Hadrons_int_cent_0_5_systematic_fex1003,data_v2_Hadrons_int_cent_0_5_systematic_fey1003);
   gre->SetName("data_v2_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1181;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_0_5_systematic1003 = new TH1F("Graph_data_v2_Hadrons_int_cent_0_5_systematic1003","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->SetMinimum(0.02016253);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->SetMaximum(0.0307357);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_5_systematic1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_0_5_systematic1003);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fx1004[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fy1004[6] = {
   0.01529551,
   0.01525391,
   0.01582622,
   0.01663384,
   0.01780232,
   0.01932488};
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fex1004[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_0_5_systematic_fey1004[6] = {
   0.0003053906,
   0.0002916635,
   0.000222263,
   0.0001943055,
   0.0002706086,
   0.0002392051};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_0_5_systematic_fx1004,data_v3_Hadrons_int_cent_0_5_systematic_fy1004,data_v3_Hadrons_int_cent_0_5_systematic_fex1004,data_v3_Hadrons_int_cent_0_5_systematic_fey1004);
   gre->SetName("data_v3_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1182;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_0_5_systematic1004 = new TH1F("Graph_data_v3_Hadrons_int_cent_0_5_systematic1004","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->SetMinimum(0.01450206);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->SetMaximum(0.02002427);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_5_systematic1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_0_5_systematic1004);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_0_5_fx1005[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_0_5_fy1005[6] = {
   0.02154405,
   0.02313725,
   0.02492008,
   0.02648572,
   0.02752172,
   0.02941932};
   Double_t data_v2_Hadrons_int_cent_0_5_fex1005[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_0_5_fey1005[6] = {
   0.0003072356,
   0.0001876132,
   0.0001352579,
   2.896044e-05,
   5.344166e-05,
   6.742608e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_0_5_fx1005,data_v2_Hadrons_int_cent_0_5_fy1005,data_v2_Hadrons_int_cent_0_5_fex1005,data_v2_Hadrons_int_cent_0_5_fey1005);
   gre->SetName("data_v2_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_0_51005 = new TH1F("Graph_data_v2_Hadrons_int_cent_0_51005","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_0_51005->SetMinimum(0.02041182);
   Graph_data_v2_Hadrons_int_cent_0_51005->SetMaximum(0.03031174);
   Graph_data_v2_Hadrons_int_cent_0_51005->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_0_51005->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_0_51005->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_0_51005->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_51005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_0_51005);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_0_5_fx1006[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_0_5_fy1006[6] = {
   0.01529551,
   0.01525391,
   0.01582622,
   0.01663384,
   0.01780232,
   0.01932488};
   Double_t data_v3_Hadrons_int_cent_0_5_fex1006[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_0_5_fey1006[6] = {
   0.0004323512,
   0.0002911986,
   0.0002128929,
   4.593734e-05,
   8.203809e-05,
   0.0001007762};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_0_5_fx1006,data_v3_Hadrons_int_cent_0_5_fy1006,data_v3_Hadrons_int_cent_0_5_fex1006,data_v3_Hadrons_int_cent_0_5_fey1006);
   gre->SetName("data_v3_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_0_51006 = new TH1F("Graph_data_v3_Hadrons_int_cent_0_51006","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_0_51006->SetMinimum(0.01440691);
   Graph_data_v3_Hadrons_int_cent_0_51006->SetMaximum(0.0198819);
   Graph_data_v3_Hadrons_int_cent_0_51006->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_0_51006->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_0_51006->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_0_51006->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_51006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_0_51006);
   
   gre->Draw("p");
   
   Double_t data_v2_Hadrons_int_cent_0_5_fx1007[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_0_5_fy1007[6] = {
   0.02154405,
   0.02313725,
   0.02492008,
   0.02648572,
   0.02752172,
   0.02941932};
   Double_t data_v2_Hadrons_int_cent_0_5_fex1007[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_0_5_fey1007[6] = {
   0.0003072356,
   0.0001876132,
   0.0001352579,
   2.896044e-05,
   5.344166e-05,
   6.742608e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_0_5_fx1007,data_v2_Hadrons_int_cent_0_5_fy1007,data_v2_Hadrons_int_cent_0_5_fex1007,data_v2_Hadrons_int_cent_0_5_fey1007);
   gre->SetName("data_v2_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_0_51007 = new TH1F("Graph_data_v2_Hadrons_int_cent_0_51007","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_0_51007->SetMinimum(0.02041182);
   Graph_data_v2_Hadrons_int_cent_0_51007->SetMaximum(0.03031174);
   Graph_data_v2_Hadrons_int_cent_0_51007->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_0_51007->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_0_51007->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_0_51007->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_0_51007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_0_51007);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_0_5_fx1008[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_0_5_fy1008[6] = {
   0.01529551,
   0.01525391,
   0.01582622,
   0.01663384,
   0.01780232,
   0.01932488};
   Double_t data_v3_Hadrons_int_cent_0_5_fex1008[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_0_5_fey1008[6] = {
   0.0004323512,
   0.0002911986,
   0.0002128929,
   4.593734e-05,
   8.203809e-05,
   0.0001007762};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_0_5_fx1008,data_v3_Hadrons_int_cent_0_5_fy1008,data_v3_Hadrons_int_cent_0_5_fex1008,data_v3_Hadrons_int_cent_0_5_fey1008);
   gre->SetName("data_v3_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_0_51008 = new TH1F("Graph_data_v3_Hadrons_int_cent_0_51008","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_0_51008->SetMinimum(0.01440691);
   Graph_data_v3_Hadrons_int_cent_0_51008->SetMaximum(0.0198819);
   Graph_data_v3_Hadrons_int_cent_0_51008->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_0_51008->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_0_51008->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_0_51008->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_0_51008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_0_51008);
   
   gre->Draw("p");
   TLine *line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(24.85,0.09775,"#font[42]{ #scale[0.85]{ #splitline{Au+Au, Hadrons}{ 0.2<p_{T}<3.2 GeV/c }}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_0_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_3
   TPad *Pad_1_3 = new TPad("Pad_1_3", "",0.53,0.6866667,0.9,0.98);
   Pad_1_3->Draw();
   Pad_1_3->cd();
   Pad_1_3->Range(4,-0.005,75,0.115);
   Pad_1_3->SetFillColor(0);
   Pad_1_3->SetBorderMode(0);
   Pad_1_3->SetBorderSize(0);
   Pad_1_3->SetTickx(1);
   Pad_1_3->SetTicky(1);
   Pad_1_3->SetLeftMargin(0);
   Pad_1_3->SetRightMargin(0);
   Pad_1_3->SetTopMargin(0);
   Pad_1_3->SetBottomMargin(0);
   
   TH2F *__7 = new TH2F("__7","",2,4,75,2,-0.005,0.115);
   __7->SetStats(0);
   __7->SetFillColor(10);
   __7->SetFillStyle(0);
   __7->GetXaxis()->SetNdivisions(508);
   __7->GetXaxis()->SetLabelFont(42);
   __7->GetXaxis()->SetLabelOffset(0.02);
   __7->GetXaxis()->SetLabelSize(0.086);
   __7->GetXaxis()->SetTitleSize(0.05);
   __7->GetXaxis()->SetTitleOffset(1.2);
   __7->GetXaxis()->SetTitleFont(42);
   __7->GetYaxis()->SetNdivisions(505);
   __7->GetYaxis()->SetLabelFont(42);
   __7->GetYaxis()->SetLabelOffset(0.02);
   __7->GetYaxis()->SetLabelSize(0.086);
   __7->GetYaxis()->SetTitleSize(0.05);
   __7->GetYaxis()->SetTitleOffset(1.4);
   __7->GetYaxis()->SetTitleFont(42);
   __7->GetZaxis()->SetLabelFont(42);
   __7->GetZaxis()->SetLabelSize(0.035);
   __7->GetZaxis()->SetTitleSize(0.035);
   __7->GetZaxis()->SetTitleFont(42);
   __7->Draw("");
   
   TLegend *leg = new TLegend(0.5,0.7,0.98,0.95,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("data_v2_Hadrons_int_cent_0_5","#font[42]{v_{2}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.8);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v3_Hadrons_int_cent_0_5","#font[42]{v_{3}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.8);
   entry->SetTextFont(62);
   leg->Draw();
      tex = new TLatex(8,0.09775,"#font[42]{#scale[0.85]{(b) 5-10%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_Hadrons_int_cent_5_10_systematic_fx1009[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_5_10_systematic_fy1009[6] = {
   0.03565459,
   0.0370015,
   0.0389438,
   0.04069807,
   0.04173401,
   0.04422885};
   Double_t data_v2_Hadrons_int_cent_5_10_systematic_fex1009[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_5_10_systematic_fey1009[6] = {
   0.0003661557,
   0.0004780349,
   0.0004695831,
   0.0004226927,
   0.0004368415,
   0.0004335078};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_5_10_systematic_fx1009,data_v2_Hadrons_int_cent_5_10_systematic_fy1009,data_v2_Hadrons_int_cent_5_10_systematic_fex1009,data_v2_Hadrons_int_cent_5_10_systematic_fey1009);
   gre->SetName("data_v2_Hadrons_int_cent_5_10_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1183;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_5_10_systematic1009 = new TH1F("Graph_data_v2_Hadrons_int_cent_5_10_systematic1009","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->SetMinimum(0.03435105);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->SetMaximum(0.04559975);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_5_10_systematic1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_5_10_systematic1009);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_5_10_systematic_fx1010[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_5_10_systematic_fy1010[6] = {
   0.01637622,
   0.01712821,
   0.01805265,
   0.01891216,
   0.02015177,
   0.02170455};
   Double_t data_v3_Hadrons_int_cent_5_10_systematic_fex1010[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_5_10_systematic_fey1010[6] = {
   0.0002768709,
   0.0002799309,
   0.0002253793,
   0.0002573686,
   0.0002698672,
   0.0002367458};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_5_10_systematic_fx1010,data_v3_Hadrons_int_cent_5_10_systematic_fy1010,data_v3_Hadrons_int_cent_5_10_systematic_fex1010,data_v3_Hadrons_int_cent_5_10_systematic_fey1010);
   gre->SetName("data_v3_Hadrons_int_cent_5_10_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1184;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_5_10_systematic1010 = new TH1F("Graph_data_v3_Hadrons_int_cent_5_10_systematic1010","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->SetMinimum(0.01551516);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->SetMaximum(0.02252549);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_5_10_systematic1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_5_10_systematic1010);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_5_10_fx1011[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_5_10_fy1011[6] = {
   0.03565459,
   0.0370015,
   0.0389438,
   0.04069807,
   0.04173401,
   0.04422885};
   Double_t data_v2_Hadrons_int_cent_5_10_fex1011[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_5_10_fey1011[6] = {
   0.0002365822,
   0.0001421205,
   0.0001110758,
   2.415299e-05,
   4.396052e-05,
   5.662449e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_5_10_fx1011,data_v2_Hadrons_int_cent_5_10_fy1011,data_v2_Hadrons_int_cent_5_10_fex1011,data_v2_Hadrons_int_cent_5_10_fey1011);
   gre->SetName("data_v2_Hadrons_int_cent_5_10");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_5_101011 = new TH1F("Graph_data_v2_Hadrons_int_cent_5_101011","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_5_101011->SetMinimum(0.03453127);
   Graph_data_v2_Hadrons_int_cent_5_101011->SetMaximum(0.04517222);
   Graph_data_v2_Hadrons_int_cent_5_101011->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_5_101011->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_5_101011->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_5_101011->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_5_101011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_5_101011);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_5_10_fx1012[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_5_10_fy1012[6] = {
   0.01637622,
   0.01712821,
   0.01805265,
   0.01891216,
   0.02015177,
   0.02170455};
   Double_t data_v3_Hadrons_int_cent_5_10_fex1012[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_5_10_fey1012[6] = {
   0.0005059231,
   0.0003023366,
   0.000232946,
   4.98436e-05,
   8.70567e-05,
   0.0001075377};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_5_10_fx1012,data_v3_Hadrons_int_cent_5_10_fy1012,data_v3_Hadrons_int_cent_5_10_fex1012,data_v3_Hadrons_int_cent_5_10_fey1012);
   gre->SetName("data_v3_Hadrons_int_cent_5_10");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_5_101012 = new TH1F("Graph_data_v3_Hadrons_int_cent_5_101012","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_5_101012->SetMinimum(0.01527612);
   Graph_data_v3_Hadrons_int_cent_5_101012->SetMaximum(0.02240627);
   Graph_data_v3_Hadrons_int_cent_5_101012->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_5_101012->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_5_101012->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_5_101012->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_5_101012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_5_101012);
   
   gre->Draw("p");
   line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_1_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_2
   TPad *Pad_0_2 = new TPad("Pad_0_2", "",0.16,0.3933333,0.53,0.6866667);
   Pad_0_2->Draw();
   Pad_0_2->cd();
   Pad_0_2->Range(4,-0.005,75,0.115);
   Pad_0_2->SetFillColor(0);
   Pad_0_2->SetBorderMode(0);
   Pad_0_2->SetBorderSize(0);
   Pad_0_2->SetTickx(1);
   Pad_0_2->SetTicky(1);
   Pad_0_2->SetLeftMargin(0);
   Pad_0_2->SetRightMargin(0);
   Pad_0_2->SetTopMargin(0);
   Pad_0_2->SetBottomMargin(0);
   
   TH2F *__8 = new TH2F("__8","",2,4,75,2,-0.005,0.115);
   __8->SetStats(0);
   __8->SetFillColor(10);
   __8->SetFillStyle(0);
   __8->GetXaxis()->SetNdivisions(508);
   __8->GetXaxis()->SetLabelFont(42);
   __8->GetXaxis()->SetLabelOffset(0.02);
   __8->GetXaxis()->SetLabelSize(0.086);
   __8->GetXaxis()->SetTitleSize(0.05);
   __8->GetXaxis()->SetTitleOffset(1.2);
   __8->GetXaxis()->SetTitleFont(42);
   __8->GetYaxis()->SetNdivisions(505);
   __8->GetYaxis()->SetLabelFont(42);
   __8->GetYaxis()->SetLabelOffset(0.02);
   __8->GetYaxis()->SetLabelSize(0.086);
   __8->GetYaxis()->SetTitleSize(0.05);
   __8->GetYaxis()->SetTitleOffset(1.4);
   __8->GetYaxis()->SetTitleFont(42);
   __8->GetZaxis()->SetLabelFont(42);
   __8->GetZaxis()->SetLabelSize(0.035);
   __8->GetZaxis()->SetTitleSize(0.035);
   __8->GetZaxis()->SetTitleFont(42);
   __8->Draw("");
      tex = new TLatex(8,0.09775,"#font[42]{#scale[0.85]{(c) 10-20%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_Hadrons_int_cent_10_20_systematic_fx1013[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_10_20_systematic_fy1013[6] = {
   0.05218303,
   0.05370791,
   0.0555726,
   0.05797717,
   0.05951195,
   0.06284559};
   Double_t data_v2_Hadrons_int_cent_10_20_systematic_fex1013[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_10_20_systematic_fey1013[6] = {
   0.0004592462,
   0.0004447778,
   0.000461919,
   0.0004377278,
   0.0004583631,
   0.0004188968};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_10_20_systematic_fx1013,data_v2_Hadrons_int_cent_10_20_systematic_fy1013,data_v2_Hadrons_int_cent_10_20_systematic_fex1013,data_v2_Hadrons_int_cent_10_20_systematic_fey1013);
   gre->SetName("data_v2_Hadrons_int_cent_10_20_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1185;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_10_20_systematic1013 = new TH1F("Graph_data_v2_Hadrons_int_cent_10_20_systematic1013","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->SetMinimum(0.05056972);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->SetMaximum(0.06441856);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_10_20_systematic1013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_10_20_systematic1013);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_10_20_systematic_fx1014[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_10_20_systematic_fy1014[6] = {
   0.01769149,
   0.01841601,
   0.01925412,
   0.02056386,
   0.0219863,
   0.02385473};
   Double_t data_v3_Hadrons_int_cent_10_20_systematic_fex1014[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_10_20_systematic_fey1014[6] = {
   0.0003958065,
   0.0002666556,
   0.0002901949,
   0.0002822556,
   0.0003494897,
   0.0003461984};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_10_20_systematic_fx1014,data_v3_Hadrons_int_cent_10_20_systematic_fy1014,data_v3_Hadrons_int_cent_10_20_systematic_fex1014,data_v3_Hadrons_int_cent_10_20_systematic_fey1014);
   gre->SetName("data_v3_Hadrons_int_cent_10_20_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1186;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_10_20_systematic1014 = new TH1F("Graph_data_v3_Hadrons_int_cent_10_20_systematic1014","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->SetMinimum(0.01660516);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->SetMaximum(0.02489146);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_10_20_systematic1014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_10_20_systematic1014);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_10_20_fx1015[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_10_20_fy1015[6] = {
   0.05218303,
   0.05370791,
   0.0555726,
   0.05797717,
   0.05951195,
   0.06284559};
   Double_t data_v2_Hadrons_int_cent_10_20_fex1015[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_10_20_fey1015[6] = {
   0.0001502986,
   8.741325e-05,
   7.131245e-05,
   1.557662e-05,
   2.902096e-05,
   3.770859e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_10_20_fx1015,data_v2_Hadrons_int_cent_10_20_fy1015,data_v2_Hadrons_int_cent_10_20_fex1015,data_v2_Hadrons_int_cent_10_20_fey1015);
   gre->SetName("data_v2_Hadrons_int_cent_10_20");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_10_201015 = new TH1F("Graph_data_v2_Hadrons_int_cent_10_201015","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_10_201015->SetMinimum(0.05094768);
   Graph_data_v2_Hadrons_int_cent_10_201015->SetMaximum(0.06396836);
   Graph_data_v2_Hadrons_int_cent_10_201015->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_10_201015->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_10_201015->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_10_201015->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_10_201015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_10_201015);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_10_20_fx1016[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_10_20_fy1016[6] = {
   0.01769149,
   0.01841601,
   0.01925412,
   0.02056386,
   0.0219863,
   0.02385473};
   Double_t data_v3_Hadrons_int_cent_10_20_fex1016[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_10_20_fey1016[6] = {
   0.0004232492,
   0.0002464647,
   0.000194406,
   4.098757e-05,
   7.268348e-05,
   8.953089e-05};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_10_20_fx1016,data_v3_Hadrons_int_cent_10_20_fy1016,data_v3_Hadrons_int_cent_10_20_fex1016,data_v3_Hadrons_int_cent_10_20_fey1016);
   gre->SetName("data_v3_Hadrons_int_cent_10_20");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_10_201016 = new TH1F("Graph_data_v3_Hadrons_int_cent_10_201016","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_10_201016->SetMinimum(0.01660064);
   Graph_data_v3_Hadrons_int_cent_10_201016->SetMaximum(0.02461187);
   Graph_data_v3_Hadrons_int_cent_10_201016->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_10_201016->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_10_201016->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_10_201016->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_10_201016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_10_201016);
   
   gre->Draw("p");
   line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_0_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_2
   TPad *Pad_1_2 = new TPad("Pad_1_2", "",0.53,0.3933333,0.9,0.6866667);
   Pad_1_2->Draw();
   Pad_1_2->cd();
   Pad_1_2->Range(4,-0.005,75,0.115);
   Pad_1_2->SetFillColor(0);
   Pad_1_2->SetBorderMode(0);
   Pad_1_2->SetBorderSize(0);
   Pad_1_2->SetTickx(1);
   Pad_1_2->SetTicky(1);
   Pad_1_2->SetLeftMargin(0);
   Pad_1_2->SetRightMargin(0);
   Pad_1_2->SetTopMargin(0);
   Pad_1_2->SetBottomMargin(0);
   
   TH2F *__9 = new TH2F("__9","",2,4,75,2,-0.005,0.115);
   __9->SetStats(0);
   __9->SetFillColor(10);
   __9->SetFillStyle(0);
   __9->GetXaxis()->SetNdivisions(508);
   __9->GetXaxis()->SetLabelFont(42);
   __9->GetXaxis()->SetLabelOffset(0.02);
   __9->GetXaxis()->SetLabelSize(0.086);
   __9->GetXaxis()->SetTitleSize(0.05);
   __9->GetXaxis()->SetTitleOffset(1.2);
   __9->GetXaxis()->SetTitleFont(42);
   __9->GetYaxis()->SetNdivisions(505);
   __9->GetYaxis()->SetLabelFont(42);
   __9->GetYaxis()->SetLabelOffset(0.02);
   __9->GetYaxis()->SetLabelSize(0.086);
   __9->GetYaxis()->SetTitleSize(0.05);
   __9->GetYaxis()->SetTitleOffset(1.4);
   __9->GetYaxis()->SetTitleFont(42);
   __9->GetZaxis()->SetLabelFont(42);
   __9->GetZaxis()->SetLabelSize(0.035);
   __9->GetZaxis()->SetTitleSize(0.035);
   __9->GetZaxis()->SetTitleFont(42);
   __9->Draw("");
      tex = new TLatex(8,0.09775,"#font[42]{#scale[0.85]{(d) 20-30%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_Hadrons_int_cent_20_30_systematic_fx1017[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_20_30_systematic_fy1017[6] = {
   0.06690268,
   0.06915256,
   0.07125058,
   0.07426677,
   0.07649802,
   0.08067979};
   Double_t data_v2_Hadrons_int_cent_20_30_systematic_fex1017[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_20_30_systematic_fey1017[6] = {
   0.0005934517,
   0.0005602322,
   0.0004851553,
   0.0004874416,
   0.0005105102,
   0.0005028898};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_20_30_systematic_fx1017,data_v2_Hadrons_int_cent_20_30_systematic_fy1017,data_v2_Hadrons_int_cent_20_30_systematic_fex1017,data_v2_Hadrons_int_cent_20_30_systematic_fey1017);
   gre->SetName("data_v2_Hadrons_int_cent_20_30_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1187;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_20_30_systematic1017 = new TH1F("Graph_data_v2_Hadrons_int_cent_20_30_systematic1017","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->SetMinimum(0.06482188);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->SetMaximum(0.08267002);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_20_30_systematic1017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_20_30_systematic1017);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_20_30_systematic_fx1018[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_20_30_systematic_fy1018[6] = {
   0.01818285,
   0.01887002,
   0.02006418,
   0.02153864,
   0.02308659,
   0.0256457};
   Double_t data_v3_Hadrons_int_cent_20_30_systematic_fex1018[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_20_30_systematic_fey1018[6] = {
   0.0002171962,
   0.0003272184,
   0.0003317992,
   0.0003839668,
   0.0004556137,
   0.0004693043};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_20_30_systematic_fx1018,data_v3_Hadrons_int_cent_20_30_systematic_fy1018,data_v3_Hadrons_int_cent_20_30_systematic_fex1018,data_v3_Hadrons_int_cent_20_30_systematic_fey1018);
   gre->SetName("data_v3_Hadrons_int_cent_20_30_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1188;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_20_30_systematic1018 = new TH1F("Graph_data_v3_Hadrons_int_cent_20_30_systematic1018","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->SetMinimum(0.01715071);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->SetMaximum(0.02692994);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_20_30_systematic1018->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_20_30_systematic1018);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_20_30_fx1019[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_20_30_fy1019[6] = {
   0.06690268,
   0.06915256,
   0.07125058,
   0.07426677,
   0.07649802,
   0.08067979};
   Double_t data_v2_Hadrons_int_cent_20_30_fex1019[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_20_30_fey1019[6] = {
   0.0001717626,
   9.831102e-05,
   8.148419e-05,
   1.816558e-05,
   3.313258e-05,
   4.358966e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_20_30_fx1019,data_v2_Hadrons_int_cent_20_30_fy1019,data_v2_Hadrons_int_cent_20_30_fex1019,data_v2_Hadrons_int_cent_20_30_fey1019);
   gre->SetName("data_v2_Hadrons_int_cent_20_30");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_20_301019 = new TH1F("Graph_data_v2_Hadrons_int_cent_20_301019","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_20_301019->SetMinimum(0.06533167);
   Graph_data_v2_Hadrons_int_cent_20_301019->SetMaximum(0.08212262);
   Graph_data_v2_Hadrons_int_cent_20_301019->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_20_301019->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_20_301019->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_20_301019->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_20_301019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_20_301019);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_20_30_fx1020[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_20_30_fy1020[6] = {
   0.01818285,
   0.01887002,
   0.02006418,
   0.02153864,
   0.02308659,
   0.0256457};
   Double_t data_v3_Hadrons_int_cent_20_30_fex1020[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_20_30_fey1020[6] = {
   0.0005880425,
   0.0003474071,
   0.0002733234,
   5.763585e-05,
   9.959126e-05,
   0.0001220661};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_20_30_fx1020,data_v3_Hadrons_int_cent_20_30_fy1020,data_v3_Hadrons_int_cent_20_30_fex1020,data_v3_Hadrons_int_cent_20_30_fey1020);
   gre->SetName("data_v3_Hadrons_int_cent_20_30");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_20_301020 = new TH1F("Graph_data_v3_Hadrons_int_cent_20_301020","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_20_301020->SetMinimum(0.01677751);
   Graph_data_v3_Hadrons_int_cent_20_301020->SetMaximum(0.02658507);
   Graph_data_v3_Hadrons_int_cent_20_301020->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_20_301020->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_20_301020->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_20_301020->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_20_301020->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_20_301020);
   
   gre->Draw("p");
   line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_1_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_1
   TPad *Pad_0_1 = new TPad("Pad_0_1", "",0.16,0.1,0.53,0.3933333);
   Pad_0_1->Draw();
   Pad_0_1->cd();
   Pad_0_1->Range(4,-0.005,75,0.115);
   Pad_0_1->SetFillColor(0);
   Pad_0_1->SetBorderMode(0);
   Pad_0_1->SetBorderSize(0);
   Pad_0_1->SetTickx(1);
   Pad_0_1->SetTicky(1);
   Pad_0_1->SetLeftMargin(0);
   Pad_0_1->SetRightMargin(0);
   Pad_0_1->SetTopMargin(0);
   Pad_0_1->SetBottomMargin(0);
   
   TH2F *__10 = new TH2F("__10","",2,4,75,2,-0.005,0.115);
   __10->SetStats(0);
   __10->SetFillColor(10);
   __10->SetFillStyle(0);
   __10->GetXaxis()->SetNdivisions(508);
   __10->GetXaxis()->SetLabelFont(42);
   __10->GetXaxis()->SetLabelOffset(0.02);
   __10->GetXaxis()->SetLabelSize(0.086);
   __10->GetXaxis()->SetTitleSize(0.05);
   __10->GetXaxis()->SetTitleOffset(1.2);
   __10->GetXaxis()->SetTitleFont(42);
   __10->GetYaxis()->SetNdivisions(505);
   __10->GetYaxis()->SetLabelFont(42);
   __10->GetYaxis()->SetLabelOffset(0.02);
   __10->GetYaxis()->SetLabelSize(0.086);
   __10->GetYaxis()->SetTitleSize(0.05);
   __10->GetYaxis()->SetTitleOffset(1.4);
   __10->GetYaxis()->SetTitleFont(42);
   __10->GetZaxis()->SetLabelFont(42);
   __10->GetZaxis()->SetLabelSize(0.035);
   __10->GetZaxis()->SetTitleSize(0.035);
   __10->GetZaxis()->SetTitleFont(42);
   __10->Draw("");
      tex = new TLatex(8,0.09775,"#font[42]{#scale[0.85]{(i) 30-40%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_Hadrons_int_cent_30_40_systematic_fx1021[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_30_40_systematic_fy1021[6] = {
   0.07379251,
   0.07697555,
   0.07889454,
   0.08241874,
   0.08541794,
   0.09020259};
   Double_t data_v2_Hadrons_int_cent_30_40_systematic_fex1021[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_30_40_systematic_fey1021[6] = {
   0.000577463,
   0.000628543,
   0.0005601891,
   0.0005742795,
   0.0005925194,
   0.0005956405};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_30_40_systematic_fx1021,data_v2_Hadrons_int_cent_30_40_systematic_fy1021,data_v2_Hadrons_int_cent_30_40_systematic_fex1021,data_v2_Hadrons_int_cent_30_40_systematic_fey1021);
   gre->SetName("data_v2_Hadrons_int_cent_30_40_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1189;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_30_40_systematic1021 = new TH1F("Graph_data_v2_Hadrons_int_cent_30_40_systematic1021","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->SetMinimum(0.07145673);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->SetMaximum(0.09255655);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_30_40_systematic1021->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_30_40_systematic1021);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_30_40_systematic_fx1022[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_30_40_systematic_fy1022[6] = {
   0.01698293,
   0.01852375,
   0.01945449,
   0.02124902,
   0.02312232,
   0.02567795};
   Double_t data_v3_Hadrons_int_cent_30_40_systematic_fex1022[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_30_40_systematic_fey1022[6] = {
   0.0005581913,
   0.0003307694,
   0.0005108242,
   0.0005178856,
   0.0005482771,
   0.0007348328};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_30_40_systematic_fx1022,data_v3_Hadrons_int_cent_30_40_systematic_fy1022,data_v3_Hadrons_int_cent_30_40_systematic_fex1022,data_v3_Hadrons_int_cent_30_40_systematic_fey1022);
   gre->SetName("data_v3_Hadrons_int_cent_30_40_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1190;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_30_40_systematic1022 = new TH1F("Graph_data_v3_Hadrons_int_cent_30_40_systematic1022","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->SetMinimum(0.01542594);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->SetMaximum(0.02741159);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_30_40_systematic1022->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_30_40_systematic1022);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_30_40_fx1023[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_30_40_fy1023[6] = {
   0.07379251,
   0.07697555,
   0.07889454,
   0.08241874,
   0.08541794,
   0.09020259};
   Double_t data_v2_Hadrons_int_cent_30_40_fex1023[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_30_40_fey1023[6] = {
   0.0002326331,
   0.0001304878,
   0.0001116246,
   2.425578e-05,
   4.463411e-05,
   5.847242e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_30_40_fx1023,data_v2_Hadrons_int_cent_30_40_fy1023,data_v2_Hadrons_int_cent_30_40_fex1023,data_v2_Hadrons_int_cent_30_40_fey1023);
   gre->SetName("data_v2_Hadrons_int_cent_30_40");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_30_401023 = new TH1F("Graph_data_v2_Hadrons_int_cent_30_401023","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_30_401023->SetMinimum(0.07188976);
   Graph_data_v2_Hadrons_int_cent_30_401023->SetMaximum(0.09193118);
   Graph_data_v2_Hadrons_int_cent_30_401023->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_30_401023->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_30_401023->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_30_401023->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_30_401023->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_30_401023);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_30_40_fx1024[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_30_40_fy1024[6] = {
   0.01698293,
   0.01852375,
   0.01945449,
   0.02124902,
   0.02312232,
   0.02567795};
   Double_t data_v3_Hadrons_int_cent_30_40_fex1024[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_30_40_fey1024[6] = {
   0.0009850857,
   0.000517906,
   0.0004251684,
   8.745276e-05,
   0.0001500826,
   0.0001839751};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_30_40_fx1024,data_v3_Hadrons_int_cent_30_40_fy1024,data_v3_Hadrons_int_cent_30_40_fex1024,data_v3_Hadrons_int_cent_30_40_fey1024);
   gre->SetName("data_v3_Hadrons_int_cent_30_40");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_30_401024 = new TH1F("Graph_data_v3_Hadrons_int_cent_30_401024","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_30_401024->SetMinimum(0.01501144);
   Graph_data_v3_Hadrons_int_cent_30_401024->SetMaximum(0.02684834);
   Graph_data_v3_Hadrons_int_cent_30_401024->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_30_401024->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_30_401024->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_30_401024->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_30_401024->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_30_401024);
   
   gre->Draw("p");
   line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_1
   TPad *Pad_1_1 = new TPad("Pad_1_1", "",0.53,0.1,0.9,0.3933333);
   Pad_1_1->Draw();
   Pad_1_1->cd();
   Pad_1_1->Range(4,-0.005,75,0.115);
   Pad_1_1->SetFillColor(0);
   Pad_1_1->SetBorderMode(0);
   Pad_1_1->SetBorderSize(0);
   Pad_1_1->SetTickx(1);
   Pad_1_1->SetTicky(1);
   Pad_1_1->SetLeftMargin(0);
   Pad_1_1->SetRightMargin(0);
   Pad_1_1->SetTopMargin(0);
   Pad_1_1->SetBottomMargin(0);
   
   TH2F *__11 = new TH2F("__11","",2,4,75,2,-0.005,0.115);
   __11->SetStats(0);
   __11->SetFillColor(10);
   __11->SetFillStyle(0);
   __11->GetXaxis()->SetNdivisions(508);
   __11->GetXaxis()->SetLabelFont(42);
   __11->GetXaxis()->SetLabelOffset(0.02);
   __11->GetXaxis()->SetLabelSize(0.086);
   __11->GetXaxis()->SetTitleSize(0.05);
   __11->GetXaxis()->SetTitleOffset(1.2);
   __11->GetXaxis()->SetTitleFont(42);
   __11->GetYaxis()->SetNdivisions(505);
   __11->GetYaxis()->SetLabelFont(42);
   __11->GetYaxis()->SetLabelOffset(0.02);
   __11->GetYaxis()->SetLabelSize(0.086);
   __11->GetYaxis()->SetTitleSize(0.05);
   __11->GetYaxis()->SetTitleOffset(1.4);
   __11->GetYaxis()->SetTitleFont(42);
   __11->GetZaxis()->SetLabelFont(42);
   __11->GetZaxis()->SetLabelSize(0.035);
   __11->GetZaxis()->SetTitleSize(0.035);
   __11->GetZaxis()->SetTitleFont(42);
   __11->Draw("");
      tex = new TLatex(8,0.09775,"#font[42]{#scale[0.85]{(f) 40-60%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_Hadrons_int_cent_40_60_systematic_fx1025[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_40_60_systematic_fy1025[6] = {
   0.07179606,
   0.07515779,
   0.07801929,
   0.08171269,
   0.08555465,
   0.09079651};
   Double_t data_v2_Hadrons_int_cent_40_60_systematic_fex1025[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v2_Hadrons_int_cent_40_60_systematic_fey1025[6] = {
   0.0006501137,
   0.0007239663,
   0.0007197416,
   0.000749464,
   0.0007957137,
   0.0007920863};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_40_60_systematic_fx1025,data_v2_Hadrons_int_cent_40_60_systematic_fy1025,data_v2_Hadrons_int_cent_40_60_systematic_fex1025,data_v2_Hadrons_int_cent_40_60_systematic_fey1025);
   gre->SetName("data_v2_Hadrons_int_cent_40_60_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1191;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_40_60_systematic1025 = new TH1F("Graph_data_v2_Hadrons_int_cent_40_60_systematic1025","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->SetMinimum(0.06910168);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->SetMaximum(0.09363286);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_40_60_systematic1025->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_40_60_systematic1025);
   
   gre->Draw("e5");
   
   Double_t data_v3_Hadrons_int_cent_40_60_systematic_fx1026[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_40_60_systematic_fy1026[6] = {
   0.01379058,
   0.01414237,
   0.01659693,
   0.01888311,
   0.02099461,
   0.02362121};
   Double_t data_v3_Hadrons_int_cent_40_60_systematic_fex1026[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t data_v3_Hadrons_int_cent_40_60_systematic_fey1026[6] = {
   0.001141538,
   0.0007028405,
   0.0007158484,
   0.0007949661,
   0.0008456686,
   0.001009};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_40_60_systematic_fx1026,data_v3_Hadrons_int_cent_40_60_systematic_fy1026,data_v3_Hadrons_int_cent_40_60_systematic_fex1026,data_v3_Hadrons_int_cent_40_60_systematic_fey1026);
   gre->SetName("data_v3_Hadrons_int_cent_40_60_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1192;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_40_60_systematic1026 = new TH1F("Graph_data_v3_Hadrons_int_cent_40_60_systematic1026","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->SetMinimum(0.01145093);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->SetMaximum(0.02582832);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_40_60_systematic1026->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_40_60_systematic1026);
   
   gre->Draw("e5");
   
   Double_t data_v2_Hadrons_int_cent_40_60_fx1027[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v2_Hadrons_int_cent_40_60_fy1027[6] = {
   0.07179606,
   0.07515779,
   0.07801929,
   0.08171269,
   0.08555465,
   0.09079651};
   Double_t data_v2_Hadrons_int_cent_40_60_fex1027[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_Hadrons_int_cent_40_60_fey1027[6] = {
   0.0003369682,
   0.0001953727,
   0.0001589633,
   3.484748e-05,
   6.191326e-05,
   7.924222e-05};
   gre = new TGraphErrors(6,data_v2_Hadrons_int_cent_40_60_fx1027,data_v2_Hadrons_int_cent_40_60_fy1027,data_v2_Hadrons_int_cent_40_60_fex1027,data_v2_Hadrons_int_cent_40_60_fey1027);
   gre->SetName("data_v2_Hadrons_int_cent_40_60");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v2_Hadrons_int_cent_40_601027 = new TH1F("Graph_data_v2_Hadrons_int_cent_40_601027","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_data_v2_Hadrons_int_cent_40_601027->SetMinimum(0.06951742);
   Graph_data_v2_Hadrons_int_cent_40_601027->SetMaximum(0.09281741);
   Graph_data_v2_Hadrons_int_cent_40_601027->SetDirectory(0);
   Graph_data_v2_Hadrons_int_cent_40_601027->SetStats(0);
   Graph_data_v2_Hadrons_int_cent_40_601027->SetFillColor(10);
   Graph_data_v2_Hadrons_int_cent_40_601027->SetFillStyle(0);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_Hadrons_int_cent_40_601027->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_Hadrons_int_cent_40_601027);
   
   gre->Draw("p");
   
   Double_t data_v3_Hadrons_int_cent_40_60_fx1028[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t data_v3_Hadrons_int_cent_40_60_fy1028[6] = {
   0.01379058,
   0.01414237,
   0.01659693,
   0.01888311,
   0.02099461,
   0.02362121};
   Double_t data_v3_Hadrons_int_cent_40_60_fex1028[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_Hadrons_int_cent_40_60_fey1028[6] = {
   0.001593032,
   0.001054962,
   0.0007290787,
   0.0001490371,
   0.0002471034,
   0.0002874352};
   gre = new TGraphErrors(6,data_v3_Hadrons_int_cent_40_60_fx1028,data_v3_Hadrons_int_cent_40_60_fy1028,data_v3_Hadrons_int_cent_40_60_fex1028,data_v3_Hadrons_int_cent_40_60_fey1028);
   gre->SetName("data_v3_Hadrons_int_cent_40_60");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_data_v3_Hadrons_int_cent_40_601028 = new TH1F("Graph_data_v3_Hadrons_int_cent_40_601028","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_data_v3_Hadrons_int_cent_40_601028->SetMinimum(0.01102644);
   Graph_data_v3_Hadrons_int_cent_40_601028->SetMaximum(0.02507975);
   Graph_data_v3_Hadrons_int_cent_40_601028->SetDirectory(0);
   Graph_data_v3_Hadrons_int_cent_40_601028->SetStats(0);
   Graph_data_v3_Hadrons_int_cent_40_601028->SetFillColor(10);
   Graph_data_v3_Hadrons_int_cent_40_601028->SetFillStyle(0);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_Hadrons_int_cent_40_601028->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_Hadrons_int_cent_40_601028);
   
   gre->Draw("p");
   line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(30.53,0.09775,"#font[42]{ #scale[0.85]{ STAR Preliminary}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_1_1->Modified();
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
      tex = new TLatex(0.5,0.7,"#font[42]{#scale[1.7]{v_{n}}}");
   tex->SetTextSize(0.3);
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
      tex = new TLatex(0.5,0.4,"#font[42]{#scale[0.85]{#sqrt{s_{NN}} [GeV]}}");
   tex->SetTextSize(0.5);
   tex->SetLineWidth(2);
   tex->Draw();
   pad_AxisX->Modified();
   canvas->cd();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
