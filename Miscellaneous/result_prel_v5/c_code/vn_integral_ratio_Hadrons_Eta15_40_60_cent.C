void vn_integral_ratio_Hadrons_Eta15_40_60_cent()
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
   PadAxisDown_0_1->Range(4,0.15,75,1.15);
   PadAxisDown_0_1->SetFillColor(0);
   PadAxisDown_0_1->SetBorderMode(0);
   PadAxisDown_0_1->SetBorderSize(0);
   PadAxisDown_0_1->SetTickx(1);
   PadAxisDown_0_1->SetTicky(1);
   PadAxisDown_0_1->SetLeftMargin(0);
   PadAxisDown_0_1->SetRightMargin(0);
   PadAxisDown_0_1->SetTopMargin(0);
   PadAxisDown_0_1->SetBottomMargin(0.35);
   
   TH2F *__12 = new TH2F("__12","",2,4,75,2,0.5,1.15);
   __12->SetStats(0);
   __12->SetFillColor(10);
   __12->SetFillStyle(0);
   __12->GetXaxis()->SetNdivisions(508);
   __12->GetXaxis()->SetLabelFont(42);
   __12->GetXaxis()->SetLabelOffset(0.02);
   __12->GetXaxis()->SetLabelSize(0.086);
   __12->GetXaxis()->SetTitleSize(0.05);
   __12->GetXaxis()->SetTitleOffset(1.2);
   __12->GetXaxis()->SetTitleFont(42);
   __12->GetYaxis()->SetNdivisions(505);
   __12->GetYaxis()->SetLabelFont(42);
   __12->GetYaxis()->SetLabelOffset(0.02);
   __12->GetYaxis()->SetLabelSize(0.086);
   __12->GetYaxis()->SetTitleSize(0.05);
   __12->GetYaxis()->SetTitleOffset(1.4);
   __12->GetYaxis()->SetTitleFont(42);
   __12->GetZaxis()->SetLabelFont(42);
   __12->GetZaxis()->SetLabelSize(0.035);
   __12->GetZaxis()->SetTitleSize(0.035);
   __12->GetZaxis()->SetTitleFont(42);
   __12->Draw("");
   PadAxisDown_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisDown_1_1
   TPad *PadAxisDown_1_1 = new TPad("PadAxisDown_1_1", "",0.53,0,0.9,0.2933333);
   PadAxisDown_1_1->Draw();
   PadAxisDown_1_1->cd();
   PadAxisDown_1_1->Range(4,0.15,75,1.15);
   PadAxisDown_1_1->SetFillColor(0);
   PadAxisDown_1_1->SetBorderMode(0);
   PadAxisDown_1_1->SetBorderSize(0);
   PadAxisDown_1_1->SetTickx(1);
   PadAxisDown_1_1->SetTicky(1);
   PadAxisDown_1_1->SetLeftMargin(0);
   PadAxisDown_1_1->SetRightMargin(0);
   PadAxisDown_1_1->SetTopMargin(0);
   PadAxisDown_1_1->SetBottomMargin(0.35);
   
   TH2F *__13 = new TH2F("__13","",2,4,75,2,0.5,1.15);
   __13->SetStats(0);
   __13->SetFillColor(10);
   __13->SetFillStyle(0);
   __13->GetXaxis()->SetNdivisions(508);
   __13->GetXaxis()->SetLabelFont(42);
   __13->GetXaxis()->SetLabelOffset(0.02);
   __13->GetXaxis()->SetLabelSize(0.086);
   __13->GetXaxis()->SetTitleSize(0.05);
   __13->GetXaxis()->SetTitleOffset(1.2);
   __13->GetXaxis()->SetTitleFont(42);
   __13->GetYaxis()->SetNdivisions(505);
   __13->GetYaxis()->SetLabelFont(42);
   __13->GetYaxis()->SetLabelOffset(0.02);
   __13->GetYaxis()->SetLabelSize(0.086);
   __13->GetYaxis()->SetTitleSize(0.05);
   __13->GetYaxis()->SetTitleOffset(1.4);
   __13->GetYaxis()->SetTitleFont(42);
   __13->GetZaxis()->SetLabelFont(42);
   __13->GetZaxis()->SetLabelSize(0.035);
   __13->GetZaxis()->SetTitleSize(0.035);
   __13->GetZaxis()->SetTitleFont(42);
   __13->Draw("");
   PadAxisDown_1_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_3
   TPad *PadAxisLeft_0_3 = new TPad("PadAxisLeft_0_3", "",0,0.6866667,0.37,0.98);
   PadAxisLeft_0_3->Draw();
   PadAxisLeft_0_3->cd();
   PadAxisLeft_0_3->Range(-51.78571,0.5,75,1.15);
   PadAxisLeft_0_3->SetFillColor(0);
   PadAxisLeft_0_3->SetBorderMode(0);
   PadAxisLeft_0_3->SetBorderSize(0);
   PadAxisLeft_0_3->SetTickx(1);
   PadAxisLeft_0_3->SetTicky(1);
   PadAxisLeft_0_3->SetLeftMargin(0.44);
   PadAxisLeft_0_3->SetRightMargin(0);
   PadAxisLeft_0_3->SetTopMargin(0);
   PadAxisLeft_0_3->SetBottomMargin(0);
   
   TH2F *__14 = new TH2F("__14","",2,4,75,2,0.5,1.15);
   __14->SetStats(0);
   __14->SetFillColor(10);
   __14->SetFillStyle(0);
   __14->GetXaxis()->SetNdivisions(508);
   __14->GetXaxis()->SetLabelFont(42);
   __14->GetXaxis()->SetLabelOffset(0.02);
   __14->GetXaxis()->SetLabelSize(0.086);
   __14->GetXaxis()->SetTitleSize(0.05);
   __14->GetXaxis()->SetTitleOffset(1.2);
   __14->GetXaxis()->SetTitleFont(42);
   __14->GetYaxis()->SetNdivisions(505);
   __14->GetYaxis()->SetLabelFont(42);
   __14->GetYaxis()->SetLabelOffset(0.02);
   __14->GetYaxis()->SetLabelSize(0.086);
   __14->GetYaxis()->SetTitleSize(0.05);
   __14->GetYaxis()->SetTitleOffset(1.4);
   __14->GetYaxis()->SetTitleFont(42);
   __14->GetZaxis()->SetLabelFont(42);
   __14->GetZaxis()->SetLabelSize(0.035);
   __14->GetZaxis()->SetTitleSize(0.035);
   __14->GetZaxis()->SetTitleFont(42);
   __14->Draw("");
   PadAxisLeft_0_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_2
   TPad *PadAxisLeft_0_2 = new TPad("PadAxisLeft_0_2", "",0,0.3933333,0.37,0.6866667);
   PadAxisLeft_0_2->Draw();
   PadAxisLeft_0_2->cd();
   PadAxisLeft_0_2->Range(-51.78571,0.5,75,1.15);
   PadAxisLeft_0_2->SetFillColor(0);
   PadAxisLeft_0_2->SetBorderMode(0);
   PadAxisLeft_0_2->SetBorderSize(0);
   PadAxisLeft_0_2->SetTickx(1);
   PadAxisLeft_0_2->SetTicky(1);
   PadAxisLeft_0_2->SetLeftMargin(0.44);
   PadAxisLeft_0_2->SetRightMargin(0);
   PadAxisLeft_0_2->SetTopMargin(0);
   PadAxisLeft_0_2->SetBottomMargin(0);
   
   TH2F *__15 = new TH2F("__15","",2,4,75,2,0.5,1.15);
   __15->SetStats(0);
   __15->SetFillColor(10);
   __15->SetFillStyle(0);
   __15->GetXaxis()->SetNdivisions(508);
   __15->GetXaxis()->SetLabelFont(42);
   __15->GetXaxis()->SetLabelOffset(0.02);
   __15->GetXaxis()->SetLabelSize(0.086);
   __15->GetXaxis()->SetTitleSize(0.05);
   __15->GetXaxis()->SetTitleOffset(1.2);
   __15->GetXaxis()->SetTitleFont(42);
   __15->GetYaxis()->SetNdivisions(505);
   __15->GetYaxis()->SetLabelFont(42);
   __15->GetYaxis()->SetLabelOffset(0.02);
   __15->GetYaxis()->SetLabelSize(0.086);
   __15->GetYaxis()->SetTitleSize(0.05);
   __15->GetYaxis()->SetTitleOffset(1.4);
   __15->GetYaxis()->SetTitleFont(42);
   __15->GetZaxis()->SetLabelFont(42);
   __15->GetZaxis()->SetLabelSize(0.035);
   __15->GetZaxis()->SetTitleSize(0.035);
   __15->GetZaxis()->SetTitleFont(42);
   __15->Draw("");
   PadAxisLeft_0_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_1
   TPad *PadAxisLeft_0_1 = new TPad("PadAxisLeft_0_1", "",0,0.1,0.37,0.3933333);
   PadAxisLeft_0_1->Draw();
   PadAxisLeft_0_1->cd();
   PadAxisLeft_0_1->Range(-51.78571,0.5,75,1.15);
   PadAxisLeft_0_1->SetFillColor(0);
   PadAxisLeft_0_1->SetBorderMode(0);
   PadAxisLeft_0_1->SetBorderSize(0);
   PadAxisLeft_0_1->SetTickx(1);
   PadAxisLeft_0_1->SetTicky(1);
   PadAxisLeft_0_1->SetLeftMargin(0.44);
   PadAxisLeft_0_1->SetRightMargin(0);
   PadAxisLeft_0_1->SetTopMargin(0);
   PadAxisLeft_0_1->SetBottomMargin(0);
   
   TH2F *__16 = new TH2F("__16","",2,4,75,2,0.5,1.15);
   __16->SetStats(0);
   __16->SetFillColor(10);
   __16->SetFillStyle(0);
   __16->GetXaxis()->SetNdivisions(508);
   __16->GetXaxis()->SetLabelFont(42);
   __16->GetXaxis()->SetLabelOffset(0.02);
   __16->GetXaxis()->SetLabelSize(0.086);
   __16->GetXaxis()->SetTitleSize(0.05);
   __16->GetXaxis()->SetTitleOffset(1.2);
   __16->GetXaxis()->SetTitleFont(42);
   __16->GetYaxis()->SetNdivisions(505);
   __16->GetYaxis()->SetLabelFont(42);
   __16->GetYaxis()->SetLabelOffset(0.02);
   __16->GetYaxis()->SetLabelSize(0.086);
   __16->GetYaxis()->SetTitleSize(0.05);
   __16->GetYaxis()->SetTitleOffset(1.4);
   __16->GetYaxis()->SetTitleFont(42);
   __16->GetZaxis()->SetLabelFont(42);
   __16->GetZaxis()->SetLabelSize(0.035);
   __16->GetZaxis()->SetTitleSize(0.035);
   __16->GetZaxis()->SetTitleFont(42);
   __16->Draw("");
   PadAxisLeft_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_3
   TPad *Pad_0_3 = new TPad("Pad_0_3", "",0.16,0.6866667,0.53,0.98);
   Pad_0_3->Draw();
   Pad_0_3->cd();
   Pad_0_3->Range(4,0.5,75,1.15);
   Pad_0_3->SetFillColor(0);
   Pad_0_3->SetBorderMode(0);
   Pad_0_3->SetBorderSize(0);
   Pad_0_3->SetTickx(1);
   Pad_0_3->SetTicky(1);
   Pad_0_3->SetLeftMargin(0);
   Pad_0_3->SetRightMargin(0);
   Pad_0_3->SetTopMargin(0);
   Pad_0_3->SetBottomMargin(0);
   
   TH2F *__17 = new TH2F("__17","",2,4,75,2,0.5,1.15);
   __17->SetStats(0);
   __17->SetFillColor(10);
   __17->SetFillStyle(0);
   __17->GetXaxis()->SetNdivisions(508);
   __17->GetXaxis()->SetLabelFont(42);
   __17->GetXaxis()->SetLabelOffset(0.02);
   __17->GetXaxis()->SetLabelSize(0.086);
   __17->GetXaxis()->SetTitleSize(0.05);
   __17->GetXaxis()->SetTitleOffset(1.2);
   __17->GetXaxis()->SetTitleFont(42);
   __17->GetYaxis()->SetNdivisions(505);
   __17->GetYaxis()->SetLabelFont(42);
   __17->GetYaxis()->SetLabelOffset(0.02);
   __17->GetYaxis()->SetLabelSize(0.086);
   __17->GetYaxis()->SetTitleSize(0.05);
   __17->GetYaxis()->SetTitleOffset(1.4);
   __17->GetYaxis()->SetTitleFont(42);
   __17->GetZaxis()->SetLabelFont(42);
   __17->GetZaxis()->SetLabelSize(0.035);
   __17->GetZaxis()->SetTitleSize(0.035);
   __17->GetZaxis()->SetTitleFont(42);
   __17->Draw("");
   TLatex *   tex = new TLatex(8,1.058,"#font[42]{#scale[0.85]{(b) 0-5%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fx1029[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fy1029[6] = {
   0.7323096,
   0.7864644,
   0.8470653,
   0.9002834,
   0.9354984,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fex1029[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fey1029[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   TGraphErrors *gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fx1029,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fy1029,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fex1029,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fey1029);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1193;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->SetMinimum(0.6975835);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->SetMaximum(1.027492);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1029);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fx1030[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fy1030[6] = {
   0.7914934,
   0.7893403,
   0.8189556,
   0.8607474,
   0.9212125,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fex1030[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fey1030[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fx1030,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fy1030,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fex1030,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fey1030);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1194;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->SetMinimum(0.7626857);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->SetMaximum(1.021574);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1030);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fx1031[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fy1031[6] = {
   0.7323096,
   0.7864644,
   0.8470653,
   0.9002834,
   0.9354984,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fex1031[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_systematic_fey1031[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fx1031,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fy1031,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fex1031,ratio_data_v2_Hadrons_int_cent_0_5_systematic_fey1031);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1195;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->SetMinimum(0.6975835);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->SetMaximum(1.027492);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_0_5_systematic1031);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fx1032[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fy1032[6] = {
   0.7914934,
   0.7893403,
   0.8189556,
   0.8607474,
   0.9212125,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fex1032[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_systematic_fey1032[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fx1032,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fy1032,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fex1032,ratio_data_v3_Hadrons_int_cent_0_5_systematic_fey1032);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_0_5_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1196;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->SetMinimum(0.7626857);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->SetMaximum(1.021574);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_0_5_systematic1032);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fx1033[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fy1033[6] = {
   0.7323096,
   0.7864644,
   0.8470653,
   0.9002834,
   0.9354984,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fex1033[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fey1033[6] = {
   0.01057734,
   0.006627051,
   0.004990671,
   0.002286152,
   0.002810138,
   0.003241233};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_0_5_fx1033,ratio_data_v2_Hadrons_int_cent_0_5_fy1033,ratio_data_v2_Hadrons_int_cent_0_5_fex1033,ratio_data_v2_Hadrons_int_cent_0_5_fey1033);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_0_51033 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_0_51033","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->SetMinimum(0.6935813);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->SetMaximum(1.031392);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51033->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_0_51033);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fx1034[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fy1034[6] = {
   0.7914934,
   0.7893403,
   0.8189556,
   0.8607474,
   0.9212125,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fex1034[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fey1034[6] = {
   0.02275033,
   0.01562069,
   0.01181536,
   0.005079246,
   0.006410927,
   0.007374902};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_0_5_fx1034,ratio_data_v3_Hadrons_int_cent_0_5_fy1034,ratio_data_v3_Hadrons_int_cent_0_5_fex1034,ratio_data_v3_Hadrons_int_cent_0_5_fey1034);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_0_51034 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_0_51034","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->SetMinimum(0.7448798);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->SetMaximum(1.031238);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51034->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_0_51034);
   
   gre->Draw("p");
   
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fx1035[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fy1035[6] = {
   0.7323096,
   0.7864644,
   0.8470653,
   0.9002834,
   0.9354984,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fex1035[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_0_5_fey1035[6] = {
   0.01057734,
   0.006627051,
   0.004990671,
   0.002286152,
   0.002810138,
   0.003241233};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_0_5_fx1035,ratio_data_v2_Hadrons_int_cent_0_5_fy1035,ratio_data_v2_Hadrons_int_cent_0_5_fex1035,ratio_data_v2_Hadrons_int_cent_0_5_fey1035);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_0_51035 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_0_51035","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->SetMinimum(0.6935813);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->SetMaximum(1.031392);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_0_51035->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_0_51035);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fx1036[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fy1036[6] = {
   0.7914934,
   0.7893403,
   0.8189556,
   0.8607474,
   0.9212125,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fex1036[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_0_5_fey1036[6] = {
   0.02275033,
   0.01562069,
   0.01181536,
   0.005079246,
   0.006410927,
   0.007374902};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_0_5_fx1036,ratio_data_v3_Hadrons_int_cent_0_5_fy1036,ratio_data_v3_Hadrons_int_cent_0_5_fex1036,ratio_data_v3_Hadrons_int_cent_0_5_fey1036);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_0_5");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_0_51036 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_0_51036","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->SetMinimum(0.7448798);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->SetMaximum(1.031238);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_0_51036->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_0_51036);
   
   gre->Draw("p");
   TLine *line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(24.85,0.5975,"#font[42]{ #scale[0.85]{ #splitline{Au+Au, Hadrons}{ 0.2<p_{T}<3.2 GeV/c }}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_0_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_3
   TPad *Pad_1_3 = new TPad("Pad_1_3", "",0.53,0.6866667,0.9,0.98);
   Pad_1_3->Draw();
   Pad_1_3->cd();
   Pad_1_3->Range(4,0.5,75,1.15);
   Pad_1_3->SetFillColor(0);
   Pad_1_3->SetBorderMode(0);
   Pad_1_3->SetBorderSize(0);
   Pad_1_3->SetTickx(1);
   Pad_1_3->SetTicky(1);
   Pad_1_3->SetLeftMargin(0);
   Pad_1_3->SetRightMargin(0);
   Pad_1_3->SetTopMargin(0);
   Pad_1_3->SetBottomMargin(0);
   
   TH2F *__18 = new TH2F("__18","",2,4,75,2,0.5,1.15);
   __18->SetStats(0);
   __18->SetFillColor(10);
   __18->SetFillStyle(0);
   __18->GetXaxis()->SetNdivisions(508);
   __18->GetXaxis()->SetLabelFont(42);
   __18->GetXaxis()->SetLabelOffset(0.02);
   __18->GetXaxis()->SetLabelSize(0.086);
   __18->GetXaxis()->SetTitleSize(0.05);
   __18->GetXaxis()->SetTitleOffset(1.2);
   __18->GetXaxis()->SetTitleFont(42);
   __18->GetYaxis()->SetNdivisions(505);
   __18->GetYaxis()->SetLabelFont(42);
   __18->GetYaxis()->SetLabelOffset(0.02);
   __18->GetYaxis()->SetLabelSize(0.086);
   __18->GetYaxis()->SetTitleSize(0.05);
   __18->GetYaxis()->SetTitleOffset(1.4);
   __18->GetYaxis()->SetTitleFont(42);
   __18->GetZaxis()->SetLabelFont(42);
   __18->GetZaxis()->SetLabelSize(0.035);
   __18->GetZaxis()->SetTitleSize(0.035);
   __18->GetZaxis()->SetTitleFont(42);
   __18->Draw("");
   
   TLegend *leg = new TLegend(0.5,0.1,0.98,0.4,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ratio_data_v2_Hadrons_int_cent_0_5","#font[42]{v_{2}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.8);
   entry->SetTextFont(62);
   entry=leg->AddEntry("ratio_data_v3_Hadrons_int_cent_0_5","#font[42]{v_{3}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.8);
   entry->SetTextFont(62);
   leg->Draw();
      tex = new TLatex(8,1.058,"#font[42]{#scale[0.85]{(c) 5-10%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_systematic_fx1037[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_systematic_fy1037[6] = {
   0.8061389,
   0.8365921,
   0.8805068,
   0.9201703,
   0.9435925,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_systematic_fex1037[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_systematic_fey1037[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_5_10_systematic_fx1037,ratio_data_v2_Hadrons_int_cent_5_10_systematic_fy1037,ratio_data_v2_Hadrons_int_cent_5_10_systematic_fex1037,ratio_data_v2_Hadrons_int_cent_5_10_systematic_fey1037);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_5_10_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1197;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->SetMinimum(0.7787958);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->SetMaximum(1.020109);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_5_10_systematic1037);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_systematic_fx1038[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_systematic_fy1038[6] = {
   0.7545063,
   0.7891527,
   0.831745,
   0.8713452,
   0.9284583,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_systematic_fex1038[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_systematic_fey1038[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_5_10_systematic_fx1038,ratio_data_v3_Hadrons_int_cent_5_10_systematic_fy1038,ratio_data_v3_Hadrons_int_cent_5_10_systematic_fex1038,ratio_data_v3_Hadrons_int_cent_5_10_systematic_fey1038);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_5_10_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1198;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->SetMinimum(0.722);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->SetMaximum(1.025273);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_5_10_systematic1038);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_fx1039[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_fy1039[6] = {
   0.8061389,
   0.8365921,
   0.8805068,
   0.9201703,
   0.9435925,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_fex1039[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_5_10_fey1039[6] = {
   0.005447704,
   0.003387101,
   0.002752786,
   0.001298475,
   0.001564377,
   0.001810563};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_5_10_fx1039,ratio_data_v2_Hadrons_int_cent_5_10_fy1039,ratio_data_v2_Hadrons_int_cent_5_10_fex1039,ratio_data_v2_Hadrons_int_cent_5_10_fey1039);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_5_10");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_5_101039 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_5_101039","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->SetMinimum(0.7805792);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->SetMaximum(1.021923);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_5_101039->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_5_101039);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_fx1040[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_fy1040[6] = {
   0.7545063,
   0.7891527,
   0.831745,
   0.8713452,
   0.9284583,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_fex1040[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_5_10_fey1040[6] = {
   0.0236074,
   0.01446798,
   0.01149656,
   0.004889967,
   0.006103232,
   0.007006885};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_5_10_fx1040,ratio_data_v3_Hadrons_int_cent_5_10_fy1040,ratio_data_v3_Hadrons_int_cent_5_10_fex1040,ratio_data_v3_Hadrons_int_cent_5_10_fey1040);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_5_10");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_5_101040 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_5_101040","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->SetMinimum(0.7032881);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->SetMaximum(1.034618);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_5_101040->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_5_101040);
   
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
   Pad_0_2->Range(4,0.5,75,1.15);
   Pad_0_2->SetFillColor(0);
   Pad_0_2->SetBorderMode(0);
   Pad_0_2->SetBorderSize(0);
   Pad_0_2->SetTickx(1);
   Pad_0_2->SetTicky(1);
   Pad_0_2->SetLeftMargin(0);
   Pad_0_2->SetRightMargin(0);
   Pad_0_2->SetTopMargin(0);
   Pad_0_2->SetBottomMargin(0);
   
   TH2F *__19 = new TH2F("__19","",2,4,75,2,0.5,1.15);
   __19->SetStats(0);
   __19->SetFillColor(10);
   __19->SetFillStyle(0);
   __19->GetXaxis()->SetNdivisions(508);
   __19->GetXaxis()->SetLabelFont(42);
   __19->GetXaxis()->SetLabelOffset(0.02);
   __19->GetXaxis()->SetLabelSize(0.086);
   __19->GetXaxis()->SetTitleSize(0.05);
   __19->GetXaxis()->SetTitleOffset(1.2);
   __19->GetXaxis()->SetTitleFont(42);
   __19->GetYaxis()->SetNdivisions(505);
   __19->GetYaxis()->SetLabelFont(42);
   __19->GetYaxis()->SetLabelOffset(0.02);
   __19->GetYaxis()->SetLabelSize(0.086);
   __19->GetYaxis()->SetTitleSize(0.05);
   __19->GetYaxis()->SetTitleOffset(1.4);
   __19->GetYaxis()->SetTitleFont(42);
   __19->GetZaxis()->SetLabelFont(42);
   __19->GetZaxis()->SetLabelSize(0.035);
   __19->GetZaxis()->SetTitleSize(0.035);
   __19->GetZaxis()->SetTitleFont(42);
   __19->Draw("");
      tex = new TLatex(8,1.058,"#font[42]{#scale[0.85]{(d) 10-20%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_systematic_fx1041[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_systematic_fy1041[6] = {
   0.8303372,
   0.8546011,
   0.8842721,
   0.9225336,
   0.9469551,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_systematic_fex1041[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_systematic_fey1041[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_10_20_systematic_fx1041,ratio_data_v2_Hadrons_int_cent_10_20_systematic_fy1041,ratio_data_v2_Hadrons_int_cent_10_20_systematic_fex1041,ratio_data_v2_Hadrons_int_cent_10_20_systematic_fey1041);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_10_20_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1199;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->SetMinimum(0.8054139);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->SetMaximum(1.01769);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_10_20_systematic1041);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_systematic_fx1042[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_systematic_fy1042[6] = {
   0.7416343,
   0.7720064,
   0.8071405,
   0.8620453,
   0.9216746,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_systematic_fex1042[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_systematic_fey1042[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_10_20_systematic_fx1042,ratio_data_v3_Hadrons_int_cent_10_20_systematic_fy1042,ratio_data_v3_Hadrons_int_cent_10_20_systematic_fex1042,ratio_data_v3_Hadrons_int_cent_10_20_systematic_fey1042);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_10_20_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1200;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->SetMinimum(0.7078408);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->SetMaximum(1.02656);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_10_20_systematic1042);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_fx1043[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_fy1043[6] = {
   0.8303372,
   0.8546011,
   0.8842721,
   0.9225336,
   0.9469551,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_fex1043[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_10_20_fey1043[6] = {
   0.002442897,
   0.001482431,
   0.001252644,
   0.0006064956,
   0.0007321778,
   0.0008485559};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_10_20_fx1043,ratio_data_v2_Hadrons_int_cent_10_20_fy1043,ratio_data_v2_Hadrons_int_cent_10_20_fex1043,ratio_data_v2_Hadrons_int_cent_10_20_fey1043);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_10_20");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_10_201043 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_10_201043","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->SetMinimum(0.8105989);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->SetMaximum(1.018144);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_10_201043->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_10_201043);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_fx1044[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_fy1044[6] = {
   0.7416343,
   0.7720064,
   0.8071405,
   0.8620453,
   0.9216746,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_fex1044[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_10_20_fey1044[6] = {
   0.01795978,
   0.01073049,
   0.008694392,
   0.003663345,
   0.004609751,
   0.005307785};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_10_20_fx1044,ratio_data_v3_Hadrons_int_cent_10_20_fy1044,ratio_data_v3_Hadrons_int_cent_10_20_fex1044,ratio_data_v3_Hadrons_int_cent_10_20_fey1044);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_10_20");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_10_201044 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_10_201044","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->SetMinimum(0.6955112);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->SetMaximum(1.033471);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_10_201044->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_10_201044);
   
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
   Pad_1_2->Range(4,0.5,75,1.15);
   Pad_1_2->SetFillColor(0);
   Pad_1_2->SetBorderMode(0);
   Pad_1_2->SetBorderSize(0);
   Pad_1_2->SetTickx(1);
   Pad_1_2->SetTicky(1);
   Pad_1_2->SetLeftMargin(0);
   Pad_1_2->SetRightMargin(0);
   Pad_1_2->SetTopMargin(0);
   Pad_1_2->SetBottomMargin(0);
   
   TH2F *__20 = new TH2F("__20","",2,4,75,2,0.5,1.15);
   __20->SetStats(0);
   __20->SetFillColor(10);
   __20->SetFillStyle(0);
   __20->GetXaxis()->SetNdivisions(508);
   __20->GetXaxis()->SetLabelFont(42);
   __20->GetXaxis()->SetLabelOffset(0.02);
   __20->GetXaxis()->SetLabelSize(0.086);
   __20->GetXaxis()->SetTitleSize(0.05);
   __20->GetXaxis()->SetTitleOffset(1.2);
   __20->GetXaxis()->SetTitleFont(42);
   __20->GetYaxis()->SetNdivisions(505);
   __20->GetYaxis()->SetLabelFont(42);
   __20->GetYaxis()->SetLabelOffset(0.02);
   __20->GetYaxis()->SetLabelSize(0.086);
   __20->GetYaxis()->SetTitleSize(0.05);
   __20->GetYaxis()->SetTitleOffset(1.4);
   __20->GetYaxis()->SetTitleFont(42);
   __20->GetZaxis()->SetLabelFont(42);
   __20->GetZaxis()->SetLabelSize(0.035);
   __20->GetZaxis()->SetTitleSize(0.035);
   __20->GetZaxis()->SetTitleFont(42);
   __20->Draw("");
      tex = new TLatex(8,1.058,"#font[42]{#scale[0.85]{(i) 20-30%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_systematic_fx1045[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_systematic_fy1045[6] = {
   0.8292372,
   0.8571237,
   0.883128,
   0.9205127,
   0.9481683,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_systematic_fex1045[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_systematic_fey1045[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_20_30_systematic_fx1045,ratio_data_v2_Hadrons_int_cent_20_30_systematic_fy1045,ratio_data_v2_Hadrons_int_cent_20_30_systematic_fex1045,ratio_data_v2_Hadrons_int_cent_20_30_systematic_fey1045);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_20_30_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1201;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->SetMinimum(0.8042039);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->SetMaximum(1.0178);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_20_30_systematic1045);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_systematic_fx1046[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_systematic_fy1046[6] = {
   0.7090016,
   0.7357964,
   0.7823603,
   0.8398536,
   0.9002128,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_systematic_fex1046[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_systematic_fey1046[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_20_30_systematic_fx1046,ratio_data_v3_Hadrons_int_cent_20_30_systematic_fy1046,ratio_data_v3_Hadrons_int_cent_20_30_systematic_fex1046,ratio_data_v3_Hadrons_int_cent_20_30_systematic_fey1046);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_20_30_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1202;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->SetMinimum(0.6719448);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->SetMaximum(1.029823);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_20_30_systematic1046);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_fx1047[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_fy1047[6] = {
   0.8292372,
   0.8571237,
   0.883128,
   0.9205127,
   0.9481683,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_fex1047[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_20_30_fey1047[6] = {
   0.002175572,
   0.001303562,
   0.001117004,
   0.0005459276,
   0.0006565629,
   0.000764071};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_20_30_fx1047,ratio_data_v2_Hadrons_int_cent_20_30_fy1047,ratio_data_v2_Hadrons_int_cent_20_30_fex1047,ratio_data_v2_Hadrons_int_cent_20_30_fey1047);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_20_30");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_20_301047 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_20_301047","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->SetMinimum(0.8096914);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->SetMaximum(1.018134);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_20_301047->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_20_301047);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_fx1048[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_fy1048[6] = {
   0.7090016,
   0.7357964,
   0.7823603,
   0.8398536,
   0.9002128,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_fex1048[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_20_30_fey1048[6] = {
   0.02317647,
   0.01399179,
   0.01128949,
   0.004585895,
   0.00578269,
   0.006731245};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_20_30_fx1048,ratio_data_v3_Hadrons_int_cent_20_30_fy1048,ratio_data_v3_Hadrons_int_cent_20_30_fex1048,ratio_data_v3_Hadrons_int_cent_20_30_fey1048);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_20_30");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_20_301048 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_20_301048","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->SetMinimum(0.6537345);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->SetMaximum(1.038822);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_20_301048->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_20_301048);
   
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
   Pad_0_1->Range(4,0.5,75,1.15);
   Pad_0_1->SetFillColor(0);
   Pad_0_1->SetBorderMode(0);
   Pad_0_1->SetBorderSize(0);
   Pad_0_1->SetTickx(1);
   Pad_0_1->SetTicky(1);
   Pad_0_1->SetLeftMargin(0);
   Pad_0_1->SetRightMargin(0);
   Pad_0_1->SetTopMargin(0);
   Pad_0_1->SetBottomMargin(0);
   
   TH2F *__21 = new TH2F("__21","",2,4,75,2,0.5,1.15);
   __21->SetStats(0);
   __21->SetFillColor(10);
   __21->SetFillStyle(0);
   __21->GetXaxis()->SetNdivisions(508);
   __21->GetXaxis()->SetLabelFont(42);
   __21->GetXaxis()->SetLabelOffset(0.02);
   __21->GetXaxis()->SetLabelSize(0.086);
   __21->GetXaxis()->SetTitleSize(0.05);
   __21->GetXaxis()->SetTitleOffset(1.2);
   __21->GetXaxis()->SetTitleFont(42);
   __21->GetYaxis()->SetNdivisions(505);
   __21->GetYaxis()->SetLabelFont(42);
   __21->GetYaxis()->SetLabelOffset(0.02);
   __21->GetYaxis()->SetLabelSize(0.086);
   __21->GetYaxis()->SetTitleSize(0.05);
   __21->GetYaxis()->SetTitleOffset(1.4);
   __21->GetYaxis()->SetTitleFont(42);
   __21->GetZaxis()->SetLabelFont(42);
   __21->GetZaxis()->SetLabelSize(0.035);
   __21->GetZaxis()->SetTitleSize(0.035);
   __21->GetZaxis()->SetTitleFont(42);
   __21->Draw("");
      tex = new TLatex(8,1.058,"#font[42]{#scale[0.85]{(f) 30-40%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_systematic_fx1049[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_systematic_fy1049[6] = {
   0.8180754,
   0.853363,
   0.8746372,
   0.913707,
   0.9469566,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_systematic_fex1049[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_systematic_fey1049[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_30_40_systematic_fx1049,ratio_data_v2_Hadrons_int_cent_30_40_systematic_fy1049,ratio_data_v2_Hadrons_int_cent_30_40_systematic_fex1049,ratio_data_v2_Hadrons_int_cent_30_40_systematic_fey1049);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_30_40_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1203;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->SetMinimum(0.7919259);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->SetMaximum(1.018916);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_30_40_systematic1049);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_systematic_fx1050[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_systematic_fy1050[6] = {
   0.6613818,
   0.7213873,
   0.7576338,
   0.8275199,
   0.9004737,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_systematic_fex1050[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_systematic_fey1050[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_30_40_systematic_fx1050,ratio_data_v3_Hadrons_int_cent_30_40_systematic_fy1050,ratio_data_v3_Hadrons_int_cent_30_40_systematic_fex1050,ratio_data_v3_Hadrons_int_cent_30_40_systematic_fey1050);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_30_40_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1204;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->SetMinimum(0.619563);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->SetMaximum(1.034585);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_30_40_systematic1050);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_fx1051[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_fy1051[6] = {
   0.8180754,
   0.853363,
   0.8746372,
   0.913707,
   0.9469566,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_fex1051[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_30_40_fey1051[6] = {
   0.002632964,
   0.001548768,
   0.001361187,
   0.0006504798,
   0.0007884537,
   0.0009167419};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_30_40_fx1051,ratio_data_v2_Hadrons_int_cent_30_40_fy1051,ratio_data_v2_Hadrons_int_cent_30_40_fex1051,ratio_data_v2_Hadrons_int_cent_30_40_fey1051);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_30_40");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_30_401051 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_30_401051","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->SetMinimum(0.796895);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->SetMaximum(1.019464);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_30_401051->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_30_401051);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_fx1052[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_fy1052[6] = {
   0.6613818,
   0.7213873,
   0.7576338,
   0.8275199,
   0.9004737,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_fex1052[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_30_40_fey1052[6] = {
   0.03865464,
   0.02082099,
   0.0174248,
   0.006837506,
   0.008705474,
   0.01013243};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_30_40_fx1052,ratio_data_v3_Hadrons_int_cent_30_40_fy1052,ratio_data_v3_Hadrons_int_cent_30_40_fex1052,ratio_data_v3_Hadrons_int_cent_30_40_fey1052);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_30_40");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_30_401052 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_30_401052","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->SetMinimum(0.5839867);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->SetMaximum(1.048873);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_30_401052->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_30_401052);
   
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
   Pad_1_1->Range(4,0.5,75,1.15);
   Pad_1_1->SetFillColor(0);
   Pad_1_1->SetBorderMode(0);
   Pad_1_1->SetBorderSize(0);
   Pad_1_1->SetTickx(1);
   Pad_1_1->SetTicky(1);
   Pad_1_1->SetLeftMargin(0);
   Pad_1_1->SetRightMargin(0);
   Pad_1_1->SetTopMargin(0);
   Pad_1_1->SetBottomMargin(0);
   
   TH2F *__22 = new TH2F("__22","",2,4,75,2,0.5,1.15);
   __22->SetStats(0);
   __22->SetFillColor(10);
   __22->SetFillStyle(0);
   __22->GetXaxis()->SetNdivisions(508);
   __22->GetXaxis()->SetLabelFont(42);
   __22->GetXaxis()->SetLabelOffset(0.02);
   __22->GetXaxis()->SetLabelSize(0.086);
   __22->GetXaxis()->SetTitleSize(0.05);
   __22->GetXaxis()->SetTitleOffset(1.2);
   __22->GetXaxis()->SetTitleFont(42);
   __22->GetYaxis()->SetNdivisions(505);
   __22->GetYaxis()->SetLabelFont(42);
   __22->GetYaxis()->SetLabelOffset(0.02);
   __22->GetYaxis()->SetLabelSize(0.086);
   __22->GetYaxis()->SetTitleSize(0.05);
   __22->GetYaxis()->SetTitleOffset(1.4);
   __22->GetYaxis()->SetTitleFont(42);
   __22->GetZaxis()->SetLabelFont(42);
   __22->GetZaxis()->SetLabelSize(0.035);
   __22->GetZaxis()->SetTitleSize(0.035);
   __22->GetZaxis()->SetTitleFont(42);
   __22->Draw("");
      tex = new TLatex(8,1.058,"#font[42]{#scale[0.85]{(g) 40-60%}}");
   tex->SetTextSize(0.09);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_systematic_fx1053[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_systematic_fy1053[6] = {
   0.7907359,
   0.8277608,
   0.8592764,
   0.8999542,
   0.9422681,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_systematic_fex1053[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_systematic_fey1053[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_40_60_systematic_fx1053,ratio_data_v2_Hadrons_int_cent_40_60_systematic_fy1053,ratio_data_v2_Hadrons_int_cent_40_60_systematic_fex1053,ratio_data_v2_Hadrons_int_cent_40_60_systematic_fey1053);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_40_60_systematic");
   gre->SetTitle("#font[42]{v_{2}}");

   ci = 1205;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053","#font[42]{v_{2}}",100,4.61,69.29);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->SetMinimum(0.7618525);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->SetMaximum(1.02165);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_40_60_systematic1053);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_systematic_fx1054[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_systematic_fy1054[6] = {
   0.5838221,
   0.598715,
   0.7026283,
   0.7994133,
   0.8888035,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_systematic_fex1054[6] = {
   1.5,
   1.5,
   1.5,
   1.5,
   1.5,
   1.5};
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_systematic_fey1054[6] = {
   0.007233622,
   0.004011175,
   0.00363152,
   0.002147652,
   0.002129896,
   0};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_40_60_systematic_fx1054,ratio_data_v3_Hadrons_int_cent_40_60_systematic_fy1054,ratio_data_v3_Hadrons_int_cent_40_60_systematic_fex1054,ratio_data_v3_Hadrons_int_cent_40_60_systematic_fey1054);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_40_60_systematic");
   gre->SetTitle("#font[42]{v_{3}}");

   ci = 1206;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054","#font[42]{v_{3}}",100,4.61,69.29);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->SetMinimum(0.5342474);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->SetMaximum(1.042341);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_40_60_systematic1054);
   
   gre->Draw("e5");
   
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_fx1055[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_fy1055[6] = {
   0.7907359,
   0.8277608,
   0.8592764,
   0.8999542,
   0.9422681,
   1};
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_fex1055[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v2_Hadrons_int_cent_40_60_fey1055[6] = {
   0.003774865,
   0.002269799,
   0.001904618,
   0.0008741865,
   0.001068293,
   0.001234248};
   gre = new TGraphErrors(6,ratio_data_v2_Hadrons_int_cent_40_60_fx1055,ratio_data_v2_Hadrons_int_cent_40_60_fy1055,ratio_data_v2_Hadrons_int_cent_40_60_fex1055,ratio_data_v2_Hadrons_int_cent_40_60_fey1055);
   gre->SetName("ratio_data_v2_Hadrons_int_cent_40_60");
   gre->SetTitle("#font[42]{v_{2}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v2_Hadrons_int_cent_40_601055 = new TH1F("Graph_ratio_data_v2_Hadrons_int_cent_40_601055","#font[42]{v_{2}}",100,6.41,67.49);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->SetMinimum(0.7655337);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->SetMaximum(1.022662);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->SetDirectory(0);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->SetStats(0);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->SetFillColor(10);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->SetFillStyle(0);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v2_Hadrons_int_cent_40_601055->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v2_Hadrons_int_cent_40_601055);
   
   gre->Draw("p");
   
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_fx1056[6] = {
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4};
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_fy1056[6] = {
   0.5838221,
   0.598715,
   0.7026283,
   0.7994133,
   0.8888035,
   1};
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_fex1056[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t ratio_data_v3_Hadrons_int_cent_40_60_fey1056[6] = {
   0.06781389,
   0.04525197,
   0.03202775,
   0.0115947,
   0.01504685,
   0.01720889};
   gre = new TGraphErrors(6,ratio_data_v3_Hadrons_int_cent_40_60_fx1056,ratio_data_v3_Hadrons_int_cent_40_60_fy1056,ratio_data_v3_Hadrons_int_cent_40_60_fex1056,ratio_data_v3_Hadrons_int_cent_40_60_fey1056);
   gre->SetName("ratio_data_v3_Hadrons_int_cent_40_60");
   gre->SetTitle("#font[42]{v_{3}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.8);
   
   TH1F *Graph_ratio_data_v3_Hadrons_int_cent_40_601056 = new TH1F("Graph_ratio_data_v3_Hadrons_int_cent_40_601056","#font[42]{v_{3}}",100,6.41,67.49);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->SetMinimum(0.4658882);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->SetMaximum(1.067329);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->SetDirectory(0);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->SetStats(0);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->SetFillColor(10);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->SetFillStyle(0);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetNdivisions(508);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetTitleOffset(1.2);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetXaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetNdivisions(505);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetLabelOffset(0.02);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetLabelSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetTitleSize(0.05);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetTitleOffset(1.4);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetYaxis()->SetTitleFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetZaxis()->SetLabelFont(42);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetZaxis()->SetLabelSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetZaxis()->SetTitleSize(0.035);
   Graph_ratio_data_v3_Hadrons_int_cent_40_601056->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_ratio_data_v3_Hadrons_int_cent_40_601056);
   
   gre->Draw("p");
   line = new TLine(4,0,75,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(4,1,75,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(30.53,0.5975,"#font[42]{ #scale[0.85]{ STAR Preliminary}}");
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
      tex = new TLatex(0.5,0.4,"#font[42]{#scale[1.2]{#frac{ v_{n}}{ v_{n}(62.4 GeV)}}}");
   tex->SetTextSize(0.3);
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
