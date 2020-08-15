void test()
{
//=========Macro generated from canvas: v2 vs cent/Canvas
//=========  (Fri Aug 14 20:35:27 2020) by ROOT version 6.19/01
   TCanvas *v2 vs cent = new TCanvas("v2 vs cent", "Canvas",93,107,900,827);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   v2 vs cent->Range(0,0,1,1);
   v2 vs cent->SetFillColor(10);
   v2 vs cent->SetBorderMode(0);
   v2 vs cent->SetBorderSize(2);
   v2 vs cent->SetTickx(1);
   v2 vs cent->SetTicky(1);
   v2 vs cent->SetLeftMargin(0.15);
   v2 vs cent->SetBottomMargin(0.15);
   v2 vs cent->SetFrameLineWidth(3);
  
// ------------>Primitives in pad: padUp
   TPad *padUp = new TPad("padUp", "v2 vs pt",0,0.33,1,1);
   padUp->Draw();
   padUp->cd();
   padUp->Range(-16,0,90.66667,0.1111111);
   padUp->SetFillColor(0);
   padUp->SetBorderMode(0);
   padUp->SetBorderSize(0);
   padUp->SetTickx(1);
   padUp->SetTicky(1);
   padUp->SetLeftMargin(0.15);
   padUp->SetBottomMargin(0);
   padUp->SetFrameFillColor(10);
   padUp->SetFrameLineWidth(3);
   padUp->SetFrameFillColor(10);
   padUp->SetFrameLineWidth(3);
   
   Double_t Graph0_fx1001[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph0_fy1001[8] = {
   0.01343992,
   0.02880506,
   0.03412879,
   0.03380121,
   0.02887206,
   0.02080323,
   0.01048595,
   -0.001413495};
   Double_t Graph0_fex1001[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[8] = {
   1.423019e-05,
   1.704261e-05,
   1.971233e-05,
   2.364437e-05,
   2.841925e-05,
   3.767963e-05,
   4.343506e-05,
   6.085537e-05};
   TGraphErrors *gre = new TGraphErrors(8,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("v_{2}{MC}");
   gre->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#2b3f79");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2b3f79");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.3);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","v_{2}{MC}",100,0,80);
   Graph_Graph01001->SetMinimum(0);
   Graph_Graph01001->SetMaximum(0.1);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("cent, %");
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1002[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph1_fy1002[8] = {
   0.01413081,
   0.02853412,
   0.03389406,
   0.03377915,
   0.02943958,
   0.02259419,
   0.01739981,
   0.02319791};
   Double_t Graph1_fex1002[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1002[8] = {
   3.77268e-05,
   2.985459e-05,
   3.451476e-05,
   4.748159e-05,
   7.608044e-05,
   0.0001588812,
   0.0003175869,
   0.0004965357};
   gre = new TGraphErrors(8,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,QC}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.3);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","v_{2}{2,QC}",100,0,82);
   Graph_Graph11002->SetMinimum(0.01210953);
   Graph_Graph11002->SetMaximum(0.03591213);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->GetXaxis()->SetTitle("cent, %");
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1003[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph2_fy1003[8] = {
   0.01347424,
   0.02914489,
   0.03473343,
   0.03460169,
   0.02974335,
   0.02595818,
   0.02204484,
   -nan};
   Double_t Graph2_fex1003[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1003[8] = {
   0.0005576583,
   0.0001366576,
   0.0001549611,
   0.0002978632,
   0.0009443057,
   0.003405284,
   0.01418546,
   -nan};
   gre = new TGraphErrors(8,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{4,QC}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.3);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","v_{2}{4,QC}",100,0,82);
   Graph_Graph21003->SetMinimum(0.005022285);
   Graph_Graph21003->SetMaximum(0.03906739);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->GetXaxis()->SetTitle("cent, %");
   Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   Graph_Graph21003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph21003->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   Graph_Graph21003->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   Graph_Graph21003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph21003->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph21003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1004[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph3_fy1004[8] = {
   0.01680331,
   0.03084945,
   0.03663759,
   0.03734756,
   0.03456342,
   0.03099325,
   0.03154341,
   0.04260913};
   Double_t Graph3_fex1004[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1004[8] = {
   4.338621e-05,
   3.530697e-05,
   4.106139e-05,
   5.692891e-05,
   8.777101e-05,
   0.0001459267,
   0.0001805671,
   0.000229041};
   gre = new TGraphErrors(8,Graph3_fx1004,Graph3_fy1004,Graph3_fex1004,Graph3_fey1004);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{#eta sub-event}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.3);
   
   TH1F *Graph_Graph31004 = new TH1F("Graph_Graph31004","v_{2}{#eta sub-event}",100,0,82);
   Graph_Graph31004->SetMinimum(0.0141521);
   Graph_Graph31004->SetMaximum(0.045446);
   Graph_Graph31004->SetDirectory(0);
   Graph_Graph31004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31004->SetLineColor(ci);
   Graph_Graph31004->GetXaxis()->SetTitle("cent, %");
   Graph_Graph31004->GetXaxis()->SetLabelFont(42);
   Graph_Graph31004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph31004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph31004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetXaxis()->SetTitleFont(42);
   Graph_Graph31004->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31004->GetYaxis()->SetLabelFont(42);
   Graph_Graph31004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph31004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph31004->GetYaxis()->SetTitleFont(42);
   Graph_Graph31004->GetZaxis()->SetLabelFont(42);
   Graph_Graph31004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph31004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph31004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31004);
   
   gre->Draw("p plc pmc");
   
   TLegend *leg = new TLegend(0.18,0.61,0.42,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(3);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","v2 ratio","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextAlign(22);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph0","v_{2}{MC}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#2b3f79");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.3);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph1","v_{2}{2,QC}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#3d6030");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.3);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph2","v_{2}{4,QC}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ae9437");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.3);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph3","v_{2}{#eta sub-event}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#9c272b");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.3);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(43.15367,0.06895629,72.37416,0.09335045,"br");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetLineWidth(3);
   TText *pt_LaTex = pt->AddText("UrQMD Au+Au at #sqrt{s_{NN}}=7.7 GeV");
   pt->Draw();
   padUp->Modified();
   v2 vs cent->cd();
  
// ------------>Primitives in pad: padDown
   TPad *padDown = new TPad("padDown", "Ratio v2",0,0,1,0.33);
   padDown->Draw();
   padDown->cd();
   padDown->Range(-16,0.795036,90.66667,1.111583);
   padDown->SetFillColor(0);
   padDown->SetBorderMode(0);
   padDown->SetBorderSize(0);
   padDown->SetTickx(1);
   padDown->SetTicky(1);
   padDown->SetLeftMargin(0.15);
   padDown->SetTopMargin(0.005);
   padDown->SetBottomMargin(0.3);
   padDown->SetFrameFillColor(10);
   padDown->SetFrameLineWidth(3);
   padDown->SetFrameFillColor(10);
   padDown->SetFrameLineWidth(3);
   
   Double_t Graph0_fx1005[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph0_fy1005[8] = {
   1.051406,
   0.9905939,
   0.9931224,
   0.9993475,
   1.019657,
   1.08609,
   1.659345,
   16.41174};
   Double_t Graph0_fex1005[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1005[8] = {
   0.003019755,
   0.001190671,
   0.001162661,
   0.001569059,
   0.002819759,
   0.00788661,
   0.03105704,
   0.7890819};
   gre = new TGraphErrors(8,Graph0_fx1005,Graph0_fy1005,Graph0_fex1005,Graph0_fey1005);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.6);
   
   TH1F *Graph_Graph01005 = new TH1F("Graph_Graph01005","Graph",100,0,80);
   Graph_Graph01005->SetMinimum(0.89);
   Graph_Graph01005->SetMaximum(1.11);
   Graph_Graph01005->SetDirectory(0);
   Graph_Graph01005->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01005->SetLineColor(ci);
   Graph_Graph01005->SetLineWidth(3);
   Graph_Graph01005->GetXaxis()->SetTitle("cent, %");
   Graph_Graph01005->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01005->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01005->GetXaxis()->SetTickLength(0.06933077);
   Graph_Graph01005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01005->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01005->GetYaxis()->SetNdivisions(504);
   Graph_Graph01005->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01005->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01005->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01005->GetYaxis()->SetTickLength(0.03474388);
   Graph_Graph01005->GetYaxis()->SetTitleOffset(0.65);
   Graph_Graph01005->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01005->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01005->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01005);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1006[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph0_fy1006[8] = {
   1.051406,
   0.9905939,
   0.9931224,
   0.9993475,
   1.019657,
   1.08609,
   1.659345,
   16.41174};
   Double_t Graph0_fex1006[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1006[8] = {
   0.003019755,
   0.001190671,
   0.001162661,
   0.001569059,
   0.002819759,
   0.00788661,
   0.03105704,
   0.7890819};
   gre = new TGraphErrors(8,Graph0_fx1006,Graph0_fy1006,Graph0_fex1006,Graph0_fey1006);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.6);
   
   TH1F *Graph_Graph_Graph010051006 = new TH1F("Graph_Graph_Graph010051006","Graph",100,0,80);
   Graph_Graph_Graph010051006->SetMinimum(0.89);
   Graph_Graph_Graph010051006->SetMaximum(1.11);
   Graph_Graph_Graph010051006->SetDirectory(0);
   Graph_Graph_Graph010051006->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph_Graph010051006->SetLineColor(ci);
   Graph_Graph_Graph010051006->SetLineWidth(3);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitle("cent, %");
   Graph_Graph_Graph010051006->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010051006->GetXaxis()->SetTickLength(0.06933077);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010051006->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010051006->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph_Graph010051006->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010051006->GetYaxis()->SetTickLength(0.03474388);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitleOffset(0.65);
   Graph_Graph_Graph010051006->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph010051006->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph010051006->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph_Graph010051006);
   
   gre->Draw("p plc pmc");
   TLine *line = new TLine(0,1,80,1);
   line->SetLineWidth(3);
   line->Draw();
   line = new TLine(0,0.95,80,0.95);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,1.05,80,1.05);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   Double_t Graph1_fx1007[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph1_fy1007[8] = {
   1.002553,
   1.011798,
   1.017717,
   1.023682,
   1.030178,
   1.247796,
   2.102322,
   nan};
   Double_t Graph1_fex1007[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1007[8] = {
   0.04150626,
   0.004781839,
   0.004578373,
   0.008841252,
   0.03272228,
   0.1637058,
   1.352835,
   -nan};
   gre = new TGraphErrors(8,Graph1_fx1007,Graph1_fy1007,Graph1_fex1007,Graph1_fey1007);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.6);
   
   TH1F *Graph_Graph11007 = new TH1F("Graph_Graph11007","Graph",100,0,82);
   Graph_Graph11007->SetMinimum(0.89);
   Graph_Graph11007->SetMaximum(1.11);
   Graph_Graph11007->SetDirectory(0);
   Graph_Graph11007->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11007->SetLineColor(ci);
   Graph_Graph11007->SetLineWidth(3);
   Graph_Graph11007->GetXaxis()->SetTitle("cent, %");
   Graph_Graph11007->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11007->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11007->GetXaxis()->SetTickLength(0.06933077);
   Graph_Graph11007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11007->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11007->GetYaxis()->SetNdivisions(504);
   Graph_Graph11007->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11007->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11007->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11007->GetYaxis()->SetTickLength(0.03474388);
   Graph_Graph11007->GetYaxis()->SetTitleOffset(0.65);
   Graph_Graph11007->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11007->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11007->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11007);
   
   gre->Draw("p plc pmc");
   line = new TLine(0,1,80,1);
   line->SetLineWidth(3);
   line->Draw();
   line = new TLine(0,0.95,80,0.95);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,1.05,80,1.05);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   Double_t Graph2_fx1008[8] = {
   5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph2_fy1008[8] = {
   1.250254,
   1.070973,
   1.07351,
   1.104918,
   1.197124,
   1.489829,
   3.00816,
   30.14453};
   Double_t Graph2_fex1008[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1008[8] = {
   0.003489038,
   0.001379818,
   0.001353506,
   0.001853106,
   0.003260383,
   0.007515745,
   0.02125531,
   1.307893};
   gre = new TGraphErrors(8,Graph2_fx1008,Graph2_fy1008,Graph2_fex1008,Graph2_fey1008);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.6);
   
   TH1F *Graph_Graph21008 = new TH1F("Graph_Graph21008","Graph",100,0,82);
   Graph_Graph21008->SetMinimum(0.89);
   Graph_Graph21008->SetMaximum(1.11);
   Graph_Graph21008->SetDirectory(0);
   Graph_Graph21008->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21008->SetLineColor(ci);
   Graph_Graph21008->SetLineWidth(3);
   Graph_Graph21008->GetXaxis()->SetTitle("cent, %");
   Graph_Graph21008->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21008->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21008->GetXaxis()->SetTickLength(0.06933077);
   Graph_Graph21008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21008->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21008->GetYaxis()->SetNdivisions(504);
   Graph_Graph21008->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21008->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21008->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21008->GetYaxis()->SetTickLength(0.03474388);
   Graph_Graph21008->GetYaxis()->SetTitleOffset(0.65);
   Graph_Graph21008->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21008->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21008->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21008);
   
   gre->Draw("p plc pmc");
   line = new TLine(0,1,80,1);
   line->SetLineWidth(3);
   line->Draw();
   line = new TLine(0,0.95,80,0.95);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,1.05,80,1.05);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(0.5,0.1,"v2 vs cent");
tex->SetNDC();
   tex->SetTextAlign(21);
   tex->SetTextSize(0.12);
   tex->SetLineWidth(2);
   tex->Draw();
   padDown->Modified();
   v2 vs cent->cd();
   v2 vs cent->Modified();
   v2 vs cent->cd();
   v2 vs cent->SetSelected(v2 vs cent);
   v2 vs cent->ToggleToolBar();
}
