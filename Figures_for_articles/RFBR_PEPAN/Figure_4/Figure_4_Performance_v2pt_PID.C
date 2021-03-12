void Figure_4_Performance_v2pt_PID()
{
//=========Macro generated from canvas: can/
//=========  (Sun Mar  7 10:49:34 2021) by ROOT version 6.19/01
   TCanvas *can = new TCanvas("can", "",0,0,2200,850);
   gStyle->SetOptStat(0);
   can->Range(0,0,1,1);
   can->SetFillColor(0);
   can->SetBorderMode(0);
   can->SetBorderSize(2);
   can->SetLeftMargin(0.04938272);
   can->SetRightMargin(0.002081995);
   can->SetTopMargin(0.06859821);
   can->SetBottomMargin(0.1195652);
   can->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: can_1
   TPad *can_1 = new TPad("can_1", "_1",0,0.5254835,0.2390898,0.9314018);
   can_1->Draw();
   can_1->cd();
   can_1->Range(-0.8368852,-0.01,2.35,0.13);
   can_1->SetFillColor(0);
   can_1->SetBorderMode(0);
   can_1->SetBorderSize(2);
   can_1->SetTickx(1);
   can_1->SetTicky(1);
   can_1->SetLeftMargin(0.2469136);
   can_1->SetRightMargin(0);
   can_1->SetTopMargin(0);
   can_1->SetBottomMargin(0);
   can_1->SetFrameBorderMode(0);
   can_1->SetFrameBorderMode(0);
   
   TH2F *pad_1__1 = new TH2F("pad_1__1","",1,-0.05,2.35,1,-0.01,0.13);
   pad_1__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   pad_1__1->SetLineColor(ci);
   pad_1__1->GetXaxis()->SetNdivisions(504);
   pad_1__1->GetXaxis()->SetLabelFont(42);
   pad_1__1->GetXaxis()->SetLabelSize(0.13);
   pad_1__1->GetXaxis()->SetTitleSize(0.13);
   pad_1__1->GetXaxis()->SetTitleOffset(0.9);
   pad_1__1->GetXaxis()->SetTitleFont(42);
   pad_1__1->GetYaxis()->SetTitle("v_{2} ");
   pad_1__1->GetYaxis()->SetNdivisions(504);
   pad_1__1->GetYaxis()->SetLabelFont(42);
   pad_1__1->GetYaxis()->SetLabelSize(0.13);
   pad_1__1->GetYaxis()->SetTitleSize(0.13);
   pad_1__1->GetYaxis()->SetTitleOffset(0.7);
   pad_1__1->GetYaxis()->SetTitleFont(42);
   pad_1__1->GetZaxis()->SetLabelFont(42);
   pad_1__1->GetZaxis()->SetLabelSize(0.035);
   pad_1__1->GetZaxis()->SetTitleSize(0.035);
   pad_1__1->GetZaxis()->SetTitleOffset(1);
   pad_1__1->GetZaxis()->SetTitleFont(42);
   pad_1__1->Draw("");
   TLatex *   tex = new TLatex(0.3,0.1235,"(a)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.2325,0.1235,"v_{2}{4}");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.5,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","open - reco","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","filled - true","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
      tex = new TLatex(1.5275,0.1014,"#sqrt{s_{NN}}=7.7 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1001[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1001[9] = {
   0.02814592,
   0.04163224,
   0.04869064,
   0.05401081,
   0.05624284,
   0.06030688,
   0.06954177,
   0.07906435,
   0.07639367};
   Double_t Graph0_fex1001[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[9] = {
   0.0002823105,
   0.0003952314,
   0.0005645718,
   0.0008363038,
   0.001216095,
   0.001539485,
   0.00249039,
   0.003741722,
   0.0162055};
   TGraphErrors *gre = new TGraphErrors(9,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01001->SetMinimum(0.02139006);
   Graph_Graph01001->SetMaximum(0.09907273);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->SetLineWidth(3);
   Graph_Graph01001->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01001->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01001->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01001->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1002[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1002[9] = {
   0.004049613,
   0.01418752,
   0.02674057,
   0.04021824,
   0.05481269,
   0.06525033,
   0.07922003,
   0.0883291,
   0.1028818};
   Double_t Graph1_fex1002[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1002[9] = {
   0.001094377,
   0.000786532,
   0.0007390284,
   0.0008185966,
   0.0009997029,
   0.001137094,
   0.001767186,
   0.002393214,
   0.007839679};
   gre = new TGraphErrors(9,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph11002->SetMinimum(0.002659713);
   Graph_Graph11002->SetMaximum(0.1214981);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->SetLineWidth(3);
   Graph_Graph11002->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11002->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11002->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11002->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11002->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11002->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11002->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11002->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11002->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1003[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1003[9] = {
   0.02770414,
   0.04115081,
   0.04803474,
   0.05223082,
   0.0559484,
   0.060788,
   0.07704536,
   0.07727297,
   0.07421863};
   Double_t Graph2_fex1003[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1003[9] = {
   0.0007468748,
   0.001027867,
   0.001468366,
   0.002168081,
   0.003139155,
   0.00392937,
   0.0062091,
   0.008563029,
   0.02313982};
   gre = new TGraphErrors(9,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph21003->SetMinimum(0.01991715);
   Graph_Graph21003->SetMaximum(0.1043986);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->SetLineWidth(3);
   Graph_Graph21003->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21003->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21003->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21003->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21003->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21003->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21003->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21003->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21003->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1004[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph3_fy1004[9] = {
   0.002801767,
   0.01454385,
   0.02869443,
   0.04066883,
   0.05297569,
   0.06074363,
   0.07475709,
   0.09098526,
   0.09061776};
   Double_t Graph3_fex1004[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1004[9] = {
   0.002917825,
   0.002049155,
   0.001925398,
   0.002140707,
   0.002612682,
   0.002956358,
   0.004492,
   0.005829327,
   0.01422842};
   gre = new TGraphErrors(9,Graph3_fx1004,Graph3_fy1004,Graph3_fex1004,Graph3_fey1004);
   gre->SetName("Graph3");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph31004 = new TH1F("Graph_Graph31004","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph31004->SetMinimum(-0.01061228);
   Graph_Graph31004->SetMaximum(0.1153424);
   Graph_Graph31004->SetDirectory(0);
   Graph_Graph31004->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31004->SetLineColor(ci);
   Graph_Graph31004->SetLineWidth(3);
   Graph_Graph31004->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31004->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph31004->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph31004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31004->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31004->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph31004->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph31004->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph31004->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph31004->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph31004->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph31004);
   
   gre->Draw("p");
   can_1->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_6
   TPad *can_6 = new TPad("can_6", "_6",0,0,0.2390898,0.5254835);
   can_6->Draw();
   can_6->cd();
   can_6->Range(-0.8368852,-0.054,2.35,0.13);
   can_6->SetFillColor(0);
   can_6->SetBorderMode(0);
   can_6->SetBorderSize(2);
   can_6->SetTickx(1);
   can_6->SetTicky(1);
   can_6->SetLeftMargin(0.2469136);
   can_6->SetRightMargin(0);
   can_6->SetTopMargin(0);
   can_6->SetBottomMargin(0.2391304);
   can_6->SetFrameBorderMode(0);
   can_6->SetFrameBorderMode(0);
   
   TH2F *pad_6__2 = new TH2F("pad_6__2","",1,-0.05,2.35,1,-0.01,0.13);
   pad_6__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_6__2->SetLineColor(ci);
   pad_6__2->GetXaxis()->SetNdivisions(504);
   pad_6__2->GetXaxis()->SetLabelFont(42);
   pad_6__2->GetXaxis()->SetLabelSize(0.105);
   pad_6__2->GetXaxis()->SetTitleSize(0.105);
   pad_6__2->GetXaxis()->SetTitleOffset(0.9);
   pad_6__2->GetXaxis()->SetTitleFont(42);
   pad_6__2->GetYaxis()->SetNdivisions(504);
   pad_6__2->GetYaxis()->SetLabelFont(42);
   pad_6__2->GetYaxis()->SetLabelSize(0.105);
   pad_6__2->GetYaxis()->SetTitleSize(0.105);
   pad_6__2->GetYaxis()->SetTitleOffset(0.7);
   pad_6__2->GetYaxis()->SetTitleFont(42);
   pad_6__2->GetZaxis()->SetLabelFont(42);
   pad_6__2->GetZaxis()->SetLabelSize(0.035);
   pad_6__2->GetZaxis()->SetTitleSize(0.035);
   pad_6__2->GetZaxis()->SetTitleOffset(1);
   pad_6__2->GetZaxis()->SetTitleFont(42);
   pad_6__2->Draw("");
      tex = new TLatex(0.3,0.1235,"(f)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.5275,0.1014,"#sqrt{s_{NN}}=11 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1005[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1005[9] = {
   0.02763387,
   0.04088062,
   0.04686255,
   0.05093014,
   0.05527769,
   0.05783664,
   0.06545426,
   0.06942853,
   0.06665278};
   Double_t Graph0_fex1005[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1005[9] = {
   0.0002649134,
   0.0003669217,
   0.0005104206,
   0.0007366436,
   0.001083909,
   0.001383305,
   0.002212065,
   0.003163208,
   0.01199011};
   gre = new TGraphErrors(9,Graph0_fx1005,Graph0_fy1005,Graph0_fex1005,Graph0_fey1005);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01005 = new TH1F("Graph_Graph01005","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01005->SetMinimum(0.02224157);
   Graph_Graph01005->SetMaximum(0.08377028);
   Graph_Graph01005->SetDirectory(0);
   Graph_Graph01005->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01005->SetLineColor(ci);
   Graph_Graph01005->SetLineWidth(3);
   Graph_Graph01005->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01005->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01005->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01005->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01005->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01005->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01005->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01005->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01005->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01005->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01005->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01005);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1006[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1006[9] = {
   0.003466597,
   0.01308276,
   0.0231456,
   0.03838506,
   0.04960748,
   0.06291269,
   0.0714328,
   0.08096518,
   0.0914726};
   Double_t Graph1_fex1006[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1006[9] = {
   0.001330431,
   0.0009460063,
   0.0008782499,
   0.0009554398,
   0.001146096,
   0.001279453,
   0.001925074,
   0.002520892,
   0.007673772};
   gre = new TGraphErrors(9,Graph1_fx1006,Graph1_fy1006,Graph1_fex1006,Graph1_fey1006);
   gre->SetName("Graph1");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11006 = new TH1F("Graph_Graph11006","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph11006->SetMinimum(0.001922549);
   Graph_Graph11006->SetMaximum(0.1088474);
   Graph_Graph11006->SetDirectory(0);
   Graph_Graph11006->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11006->SetLineColor(ci);
   Graph_Graph11006->SetLineWidth(3);
   Graph_Graph11006->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11006->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11006->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11006->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11006->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11006->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11006->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11006->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11006->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11006->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11006->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11006);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1007[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1007[9] = {
   0.02645201,
   0.04051061,
   0.04751136,
   0.05153136,
   0.05357016,
   0.06079902,
   0.06277165,
   0.06157653,
   0.03233437};
   Double_t Graph2_fex1007[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1007[9] = {
   0.0008225873,
   0.001133833,
   0.001570461,
   0.002266938,
   0.003309977,
   0.004190438,
   0.006508079,
   0.008559007,
   0.02113154};
   gre = new TGraphErrors(9,Graph2_fx1007,Graph2_fy1007,Graph2_fex1007,Graph2_fey1007);
   gre->SetName("Graph2");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph21007 = new TH1F("Graph_Graph21007","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph21007->SetMinimum(0.005309559);
   Graph_Graph21007->SetMaximum(0.07602881);
   Graph_Graph21007->SetDirectory(0);
   Graph_Graph21007->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21007->SetLineColor(ci);
   Graph_Graph21007->SetLineWidth(3);
   Graph_Graph21007->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21007->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21007->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21007->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21007->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21007->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21007->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21007->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21007->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21007->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21007->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21007);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1008[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph3_fy1008[9] = {
   0.005943075,
   0.007743687,
   0.02485423,
   0.03551307,
   0.04837866,
   0.06240446,
   0.07673851,
   0.07519306,
   0.07436517};
   Double_t Graph3_fex1008[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1008[9] = {
   0.004172969,
   0.002922699,
   0.00271211,
   0.0029583,
   0.003563148,
   0.003971111,
   0.005882601,
   0.007280371,
   0.01696441};
   gre = new TGraphErrors(9,Graph3_fx1008,Graph3_fy1008,Graph3_fex1008,Graph3_fey1008);
   gre->SetName("Graph3");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph31008 = new TH1F("Graph_Graph31008","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph31008->SetMinimum(0.001593095);
   Graph_Graph31008->SetMaximum(0.1002855);
   Graph_Graph31008->SetDirectory(0);
   Graph_Graph31008->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31008->SetLineColor(ci);
   Graph_Graph31008->SetLineWidth(3);
   Graph_Graph31008->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31008->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph31008->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph31008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31008->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31008->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31008->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph31008->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph31008->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph31008->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph31008->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph31008->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph31008);
   
   gre->Draw("p");
   can_6->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_2
   TPad *can_2 = new TPad("can_2", "_2",0.2390898,0.5254835,0.4287968,0.9314018);
   can_2->Draw();
   can_2->cd();
   can_2->Range(-0.05,-0.01,2.35,0.13);
   can_2->SetFillColor(0);
   can_2->SetBorderMode(0);
   can_2->SetBorderSize(2);
   can_2->SetTickx(1);
   can_2->SetTicky(1);
   can_2->SetLeftMargin(0);
   can_2->SetRightMargin(0);
   can_2->SetTopMargin(0);
   can_2->SetBottomMargin(0);
   can_2->SetFrameBorderMode(0);
   can_2->SetFrameBorderMode(0);
   
   TH2F *pad_2__3 = new TH2F("pad_2__3","",1,-0.05,2.35,1,-0.01,0.13);
   pad_2__3->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_2__3->SetLineColor(ci);
   pad_2__3->GetXaxis()->SetNdivisions(504);
   pad_2__3->GetXaxis()->SetLabelFont(42);
   pad_2__3->GetXaxis()->SetLabelSize(0.13);
   pad_2__3->GetXaxis()->SetTitleSize(0.13);
   pad_2__3->GetXaxis()->SetTitleOffset(0.9);
   pad_2__3->GetXaxis()->SetTitleFont(42);
   pad_2__3->GetYaxis()->SetNdivisions(504);
   pad_2__3->GetYaxis()->SetLabelFont(42);
   pad_2__3->GetYaxis()->SetLabelSize(0.13);
   pad_2__3->GetYaxis()->SetTitleSize(0.13);
   pad_2__3->GetYaxis()->SetTitleOffset(0.7);
   pad_2__3->GetYaxis()->SetTitleFont(42);
   pad_2__3->GetZaxis()->SetLabelFont(42);
   pad_2__3->GetZaxis()->SetLabelSize(0.035);
   pad_2__3->GetZaxis()->SetTitleSize(0.035);
   pad_2__3->GetZaxis()->SetTitleOffset(1);
   pad_2__3->GetZaxis()->SetTitleFont(42);
   pad_2__3->Draw("");
      tex = new TLatex(0.3,0.1235,"(b)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.2325,0.1235,"v_{2}{2}");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.75,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph0","#pi^{#pm}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#cc0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","p","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t Graph0_fx1009[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1009[9] = {
   0.02959696,
   0.04390868,
   0.05163154,
   0.05692678,
   0.06069205,
   0.06465908,
   0.07116341,
   0.07981131,
   0.09489536};
   Double_t Graph0_fex1009[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1009[9] = {
   4.102414e-05,
   6.404997e-05,
   0.0001063501,
   0.0001674396,
   0.0002447418,
   0.0003123564,
   0.0005368646,
   0.0008494891,
   0.00385057};
   gre = new TGraphErrors(9,Graph0_fx1009,Graph0_fy1009,Graph0_fex1009,Graph0_fey1009);
   gre->SetName("Graph0");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01009 = new TH1F("Graph_Graph01009","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph01009->SetMinimum(0.02263694);
   Graph_Graph01009->SetMaximum(0.1056649);
   Graph_Graph01009->SetDirectory(0);
   Graph_Graph01009->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01009->SetLineColor(ci);
   Graph_Graph01009->SetLineWidth(3);
   Graph_Graph01009->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01009->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01009->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01009->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01009->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01009->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01009->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01009->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01009->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01009->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01009->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01009);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1010[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1010[9] = {
   0.004553472,
   0.01481927,
   0.02884637,
   0.04360347,
   0.05668268,
   0.06910713,
   0.08275471,
   0.09497957,
   0.1052999};
   Double_t Graph1_fex1010[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1010[9] = {
   0.000229742,
   0.0001636629,
   0.0001505354,
   0.000164927,
   0.0002020135,
   0.0002285448,
   0.0003553075,
   0.0004922835,
   0.001835849};
   gre = new TGraphErrors(9,Graph1_fx1010,Graph1_fy1010,Graph1_fex1010,Graph1_fey1010);
   gre->SetName("Graph1");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11010 = new TH1F("Graph_Graph11010","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph11010->SetMinimum(0.003891357);
   Graph_Graph11010->SetMaximum(0.1174169);
   Graph_Graph11010->SetDirectory(0);
   Graph_Graph11010->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11010->SetLineColor(ci);
   Graph_Graph11010->SetLineWidth(3);
   Graph_Graph11010->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11010->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11010->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11010->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11010->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11010->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11010->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11010->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11010->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11010->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11010->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11010);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1011[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1011[9] = {
   0.02958313,
   0.04328474,
   0.05151076,
   0.05622909,
   0.06029478,
   0.06323357,
   0.07034379,
   0.07656355,
   0.05716797};
   Double_t Graph2_fex1011[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1011[9] = {
   0.0001026904,
   0.0001575757,
   0.000260487,
   0.0004076683,
   0.0005922489,
   0.0007494129,
   0.001253993,
   0.001795076,
   0.005023955};
   gre = new TGraphErrors(9,Graph2_fx1011,Graph2_fy1011,Graph2_fex1011,Graph2_fey1011);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph21011 = new TH1F("Graph_Graph21011","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21011->SetMinimum(0.02459262);
   Graph_Graph21011->SetMaximum(0.08324644);
   Graph_Graph21011->SetDirectory(0);
   Graph_Graph21011->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21011->SetLineColor(ci);
   Graph_Graph21011->SetLineWidth(3);
   Graph_Graph21011->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21011->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21011->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21011->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21011->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21011->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21011->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21011->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21011->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21011->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21011->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21011);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1012[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph3_fy1012[9] = {
   0.006162503,
   0.01533491,
   0.02960571,
   0.04354584,
   0.05606575,
   0.06922081,
   0.07995901,
   0.08777889,
   0.09357652};
   Double_t Graph3_fex1012[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1012[9] = {
   0.0005740739,
   0.0004009113,
   0.0003694065,
   0.0004063522,
   0.0004975465,
   0.0005594646,
   0.0008523138,
   0.001112345,
   0.003059122};
   gre = new TGraphErrors(9,Graph3_fx1012,Graph3_fy1012,Graph3_fex1012,Graph3_fey1012);
   gre->SetName("Graph3");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph31012 = new TH1F("Graph_Graph31012","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph31012->SetMinimum(0.005029586);
   Graph_Graph31012->SetMaximum(0.1057404);
   Graph_Graph31012->SetDirectory(0);
   Graph_Graph31012->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31012->SetLineColor(ci);
   Graph_Graph31012->SetLineWidth(3);
   Graph_Graph31012->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31012->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph31012->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph31012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31012->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31012->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31012->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph31012->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph31012->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph31012->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph31012->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph31012->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph31012);
   
   gre->Draw("p");
   can_2->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_7
   TPad *can_7 = new TPad("can_7", "_7",0.2390898,0,0.4287968,0.5254835);
   can_7->Draw();
   can_7->cd();
   can_7->Range(-0.05,-0.054,2.35,0.13);
   can_7->SetFillColor(0);
   can_7->SetBorderMode(0);
   can_7->SetBorderSize(2);
   can_7->SetTickx(1);
   can_7->SetTicky(1);
   can_7->SetLeftMargin(0);
   can_7->SetRightMargin(0);
   can_7->SetTopMargin(0);
   can_7->SetBottomMargin(0.2391304);
   can_7->SetFrameBorderMode(0);
   can_7->SetFrameBorderMode(0);
   
   TH2F *pad_7__4 = new TH2F("pad_7__4","",1,-0.05,2.35,1,-0.01,0.13);
   pad_7__4->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_7__4->SetLineColor(ci);
   pad_7__4->GetXaxis()->SetNdivisions(504);
   pad_7__4->GetXaxis()->SetLabelFont(42);
   pad_7__4->GetXaxis()->SetLabelSize(0.105);
   pad_7__4->GetXaxis()->SetTitleSize(0.105);
   pad_7__4->GetXaxis()->SetTitleOffset(0.9);
   pad_7__4->GetXaxis()->SetTitleFont(42);
   pad_7__4->GetYaxis()->SetNdivisions(504);
   pad_7__4->GetYaxis()->SetLabelFont(42);
   pad_7__4->GetYaxis()->SetLabelSize(0.105);
   pad_7__4->GetYaxis()->SetTitleSize(0.105);
   pad_7__4->GetYaxis()->SetTitleOffset(0.7);
   pad_7__4->GetYaxis()->SetTitleFont(42);
   pad_7__4->GetZaxis()->SetLabelFont(42);
   pad_7__4->GetZaxis()->SetLabelSize(0.035);
   pad_7__4->GetZaxis()->SetTitleSize(0.035);
   pad_7__4->GetZaxis()->SetTitleOffset(1);
   pad_7__4->GetZaxis()->SetTitleFont(42);
   pad_7__4->Draw("");
      tex = new TLatex(0.3,0.1235,"(g)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.2925,0.1235,"Au+Au");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1013[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1013[9] = {
   0.02942976,
   0.04382055,
   0.05168478,
   0.05708856,
   0.06068402,
   0.06441118,
   0.06993508,
   0.07740925,
   0.08910997};
   Double_t Graph0_fex1013[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1013[9] = {
   4.082171e-05,
   6.234322e-05,
   0.0001025931,
   0.0001634386,
   0.0002433143,
   0.0003096558,
   0.0005166527,
   0.000778418,
   0.003162168};
   gre = new TGraphErrors(9,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
   gre->SetName("Graph0");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01013 = new TH1F("Graph_Graph01013","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph01013->SetMinimum(0.02310061);
   Graph_Graph01013->SetMaximum(0.09856046);
   Graph_Graph01013->SetDirectory(0);
   Graph_Graph01013->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01013->SetLineColor(ci);
   Graph_Graph01013->SetLineWidth(3);
   Graph_Graph01013->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01013->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01013->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01013->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01013->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01013->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01013->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01013->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01013->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01013->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01013);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1014[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1014[9] = {
   0.003536013,
   0.01281175,
   0.02586928,
   0.0410303,
   0.05392715,
   0.06706854,
   0.07971051,
   0.09058293,
   0.1032134};
   Double_t Graph1_fex1014[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1014[9] = {
   0.0003093649,
   0.0002235164,
   0.0002048296,
   0.0002204292,
   0.0002629885,
   0.0002893424,
   0.0004332074,
   0.0005759403,
   0.001980261};
   gre = new TGraphErrors(9,Graph1_fx1014,Graph1_fy1014,Graph1_fex1014,Graph1_fey1014);
   gre->SetName("Graph1");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11014 = new TH1F("Graph_Graph11014","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph11014->SetMinimum(0.002903983);
   Graph_Graph11014->SetMaximum(0.1153904);
   Graph_Graph11014->SetDirectory(0);
   Graph_Graph11014->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11014->SetLineColor(ci);
   Graph_Graph11014->SetLineWidth(3);
   Graph_Graph11014->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11014->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11014->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11014->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11014->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11014->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11014->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11014->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11014->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11014->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11014->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11014->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11014);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1015[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1015[9] = {
   0.02941839,
   0.04366634,
   0.05158579,
   0.05703142,
   0.06020858,
   0.06292428,
   0.06650694,
   0.07157244,
   0.07474549};
   Double_t Graph2_fex1015[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1015[9] = {
   0.0001189288,
   0.0001782498,
   0.0002925913,
   0.0004636945,
   0.0006857246,
   0.000863712,
   0.001404144,
   0.001916172,
   0.005092904};
   gre = new TGraphErrors(9,Graph2_fx1015,Graph2_fy1015,Graph2_fex1015,Graph2_fey1015);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph21015 = new TH1F("Graph_Graph21015","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21015->SetMinimum(0.02424557);
   Graph_Graph21015->SetMaximum(0.08489229);
   Graph_Graph21015->SetDirectory(0);
   Graph_Graph21015->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21015->SetLineColor(ci);
   Graph_Graph21015->SetLineWidth(3);
   Graph_Graph21015->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21015->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21015->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21015->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21015->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21015->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21015->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21015->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21015->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21015->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21015->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21015->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21015);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1016[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph3_fy1016[9] = {
   0.004075518,
   0.01359744,
   0.02598671,
   0.0403151,
   0.05332386,
   0.06715687,
   0.07718241,
   0.08441296,
   0.08135299};
   Double_t Graph3_fex1016[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1016[9] = {
   0.0008962709,
   0.0006363064,
   0.0005838952,
   0.0006317973,
   0.0007538362,
   0.0008267468,
   0.001216221,
   0.001531513,
   0.004003464};
   gre = new TGraphErrors(9,Graph3_fx1016,Graph3_fy1016,Graph3_fex1016,Graph3_fey1016);
   gre->SetName("Graph3");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph31016 = new TH1F("Graph_Graph31016","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph31016->SetMinimum(0.002861323);
   Graph_Graph31016->SetMaximum(0.09422099);
   Graph_Graph31016->SetDirectory(0);
   Graph_Graph31016->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31016->SetLineColor(ci);
   Graph_Graph31016->SetLineWidth(3);
   Graph_Graph31016->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31016->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph31016->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph31016->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31016->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31016->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31016->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph31016->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph31016->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph31016->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph31016->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph31016->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph31016);
   
   gre->Draw("p");
   can_7->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_3
   TPad *can_3 = new TPad("can_3", "_3",0.4287968,0.5254835,0.6185039,0.9314018);
   can_3->Draw();
   can_3->cd();
   can_3->Range(-0.05,-0.01,2.35,0.13);
   can_3->SetFillColor(0);
   can_3->SetBorderMode(0);
   can_3->SetBorderSize(2);
   can_3->SetTickx(1);
   can_3->SetTicky(1);
   can_3->SetLeftMargin(0);
   can_3->SetRightMargin(0);
   can_3->SetTopMargin(0);
   can_3->SetBottomMargin(0);
   can_3->SetFrameBorderMode(0);
   can_3->SetFrameBorderMode(0);
   
   TH2F *pad_3__5 = new TH2F("pad_3__5","",1,-0.05,2.35,1,-0.01,0.13);
   pad_3__5->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_3__5->SetLineColor(ci);
   pad_3__5->GetXaxis()->SetNdivisions(504);
   pad_3__5->GetXaxis()->SetLabelFont(42);
   pad_3__5->GetXaxis()->SetLabelSize(0.13);
   pad_3__5->GetXaxis()->SetTitleSize(0.13);
   pad_3__5->GetXaxis()->SetTitleOffset(0.9);
   pad_3__5->GetXaxis()->SetTitleFont(42);
   pad_3__5->GetYaxis()->SetNdivisions(504);
   pad_3__5->GetYaxis()->SetLabelFont(42);
   pad_3__5->GetYaxis()->SetLabelSize(0.13);
   pad_3__5->GetYaxis()->SetTitleSize(0.13);
   pad_3__5->GetYaxis()->SetTitleOffset(0.7);
   pad_3__5->GetYaxis()->SetTitleFont(42);
   pad_3__5->GetZaxis()->SetLabelFont(42);
   pad_3__5->GetZaxis()->SetLabelSize(0.035);
   pad_3__5->GetZaxis()->SetTitleSize(0.035);
   pad_3__5->GetZaxis()->SetTitleOffset(1);
   pad_3__5->GetZaxis()->SetTitleFont(42);
   pad_3__5->Draw("");
      tex = new TLatex(0.3,0.1235,"(c)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.2325,0.1235,"v_{2}^{EP}{#Psi_{2,TPC}}");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1017[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1017[9] = {
   0.03020634,
   0.04464335,
   0.05203323,
   0.05742479,
   0.06074173,
   0.06495636,
   0.0718179,
   0.08145632,
   0.09696437};
   Double_t Graph0_fex1017[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1017[9] = {
   4.582935e-05,
   6.460901e-05,
   9.708903e-05,
   0.0001466389,
   0.0002196914,
   0.0002906272,
   0.0005340424,
   0.0008695455,
   0.004018892};
   gre = new TGraphErrors(9,Graph0_fx1017,Graph0_fy1017,Graph0_fex1017,Graph0_fey1017);
   gre->SetName("Graph0");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01017 = new TH1F("Graph_Graph01017","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph01017->SetMinimum(0.02307824);
   Graph_Graph01017->SetMaximum(0.1080655);
   Graph_Graph01017->SetDirectory(0);
   Graph_Graph01017->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01017->SetLineColor(ci);
   Graph_Graph01017->SetLineWidth(3);
   Graph_Graph01017->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01017->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01017->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01017->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01017->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01017->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01017->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01017->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01017->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01017->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01017->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01017->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01017);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1018[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1018[9] = {
   0.004691148,
   0.01465543,
   0.02827497,
   0.04281936,
   0.05574515,
   0.068076,
   0.08147732,
   0.09372284,
   0.1043232};
   Double_t Graph1_fex1018[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1018[9] = {
   0.0001978539,
   0.0001437972,
   0.0001338141,
   0.0001454121,
   0.0001753766,
   0.000197636,
   0.0003185239,
   0.0004655738,
   0.001913421};
   gre = new TGraphErrors(9,Graph1_fx1018,Graph1_fy1018,Graph1_fex1018,Graph1_fey1018);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11018 = new TH1F("Graph_Graph11018","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11018->SetMinimum(0.004043965);
   Graph_Graph11018->SetMaximum(0.1164109);
   Graph_Graph11018->SetDirectory(0);
   Graph_Graph11018->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11018->SetLineColor(ci);
   Graph_Graph11018->SetLineWidth(3);
   Graph_Graph11018->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11018->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11018->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11018->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11018->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11018->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11018->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11018->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11018->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11018->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11018->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11018->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11018);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1019[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1019[9] = {
   0.02996593,
   0.04387237,
   0.05230049,
   0.05640383,
   0.06079067,
   0.06452488,
   0.07036659,
   0.0781635,
   0.07050896};
   Double_t Graph2_fex1019[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1019[9] = {
   0.0001151213,
   0.0001601697,
   0.0002393292,
   0.0003599407,
   0.0005364035,
   0.0007021704,
   0.001252856,
   0.001835839,
   0.005259452};
   gre = new TGraphErrors(9,Graph2_fx1019,Graph2_fy1019,Graph2_fex1019,Graph2_fey1019);
   gre->SetName("Graph2");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph21019 = new TH1F("Graph_Graph21019","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph21019->SetMinimum(0.02483596);
   Graph_Graph21019->SetMaximum(0.08501419);
   Graph_Graph21019->SetDirectory(0);
   Graph_Graph21019->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21019->SetLineColor(ci);
   Graph_Graph21019->SetLineWidth(3);
   Graph_Graph21019->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21019->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21019->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21019->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21019->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21019->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21019->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21019->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21019->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21019->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21019->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21019->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21019);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1020[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph3_fy1020[9] = {
   0.00632299,
   0.01491629,
   0.02931212,
   0.04303986,
   0.05483616,
   0.06779309,
   0.07864317,
   0.08663465,
   0.09222475};
   Double_t Graph3_fex1020[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1020[9] = {
   0.000496506,
   0.0003538549,
   0.0003300398,
   0.0003601714,
   0.0004349254,
   0.0004874812,
   0.0007699451,
   0.001047923,
   0.003162272};
   gre = new TGraphErrors(9,Graph3_fx1020,Graph3_fy1020,Graph3_fex1020,Graph3_fey1020);
   gre->SetName("Graph3");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph31020 = new TH1F("Graph_Graph31020","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph31020->SetMinimum(0.005243836);
   Graph_Graph31020->SetMaximum(0.1043431);
   Graph_Graph31020->SetDirectory(0);
   Graph_Graph31020->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31020->SetLineColor(ci);
   Graph_Graph31020->SetLineWidth(3);
   Graph_Graph31020->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31020->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph31020->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph31020->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31020->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31020->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31020->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph31020->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph31020->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph31020->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph31020->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph31020->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph31020);
   
   gre->Draw("p");
   can_3->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_8
   TPad *can_8 = new TPad("can_8", "_8",0.4287968,0,0.6185039,0.5254835);
   can_8->Draw();
   can_8->cd();
   can_8->Range(-0.05,-0.054,2.35,0.13);
   can_8->SetFillColor(0);
   can_8->SetBorderMode(0);
   can_8->SetBorderSize(2);
   can_8->SetTickx(1);
   can_8->SetTicky(1);
   can_8->SetLeftMargin(0);
   can_8->SetRightMargin(0);
   can_8->SetTopMargin(0);
   can_8->SetBottomMargin(0.2391304);
   can_8->SetFrameBorderMode(0);
   can_8->SetFrameBorderMode(0);
   
   TH2F *pad_8__6 = new TH2F("pad_8__6","",1,-0.05,2.35,1,-0.01,0.13);
   pad_8__6->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_8__6->SetLineColor(ci);
   pad_8__6->GetXaxis()->SetTitle("p_{T} (GeV/c)        ");
   pad_8__6->GetXaxis()->SetNdivisions(504);
   pad_8__6->GetXaxis()->SetLabelFont(42);
   pad_8__6->GetXaxis()->SetLabelSize(0.105);
   pad_8__6->GetXaxis()->SetTitleSize(0.105);
   pad_8__6->GetXaxis()->SetTitleOffset(0.9);
   pad_8__6->GetXaxis()->SetTitleFont(42);
   pad_8__6->GetYaxis()->SetTitle("v_{2}");
   pad_8__6->GetYaxis()->SetNdivisions(504);
   pad_8__6->GetYaxis()->SetLabelFont(42);
   pad_8__6->GetYaxis()->SetLabelSize(0.105);
   pad_8__6->GetYaxis()->SetTitleSize(0.105);
   pad_8__6->GetYaxis()->SetTitleOffset(0.7);
   pad_8__6->GetYaxis()->SetTitleFont(42);
   pad_8__6->GetZaxis()->SetLabelFont(42);
   pad_8__6->GetZaxis()->SetLabelSize(0.035);
   pad_8__6->GetZaxis()->SetTitleSize(0.035);
   pad_8__6->GetZaxis()->SetTitleOffset(1);
   pad_8__6->GetZaxis()->SetTitleFont(42);
   pad_8__6->Draw("");
      tex = new TLatex(0.3,0.1235,"(h)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.2925,0.1235,"10-40%");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1021[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1021[9] = {
   0.02971513,
   0.04427443,
   0.05210287,
   0.05747126,
   0.0611535,
   0.06480045,
   0.07109929,
   0.07854217,
   0.09352193};
   Double_t Graph0_fex1021[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1021[9] = {
   4.705908e-05,
   6.51835e-05,
   9.682465e-05,
   0.000144959,
   0.0002155029,
   0.0002820789,
   0.0005071009,
   0.0007927109,
   0.003318794};
   gre = new TGraphErrors(9,Graph0_fx1021,Graph0_fy1021,Graph0_fex1021,Graph0_fey1021);
   gre->SetName("Graph0");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01021 = new TH1F("Graph_Graph01021","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph01021->SetMinimum(0.02295081);
   Graph_Graph01021->SetMaximum(0.103558);
   Graph_Graph01021->SetDirectory(0);
   Graph_Graph01021->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01021->SetLineColor(ci);
   Graph_Graph01021->SetLineWidth(3);
   Graph_Graph01021->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01021->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01021->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01021->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01021->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01021->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01021->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01021->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01021->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01021->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01021->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01021->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01021);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1022[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1022[9] = {
   0.003761504,
   0.01285094,
   0.02577719,
   0.04063418,
   0.05327044,
   0.06651896,
   0.07934012,
   0.09022987,
   0.1047654};
   Double_t Graph1_fex1022[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1022[9] = {
   0.000269136,
   0.0001953907,
   0.0001802998,
   0.0001930555,
   0.0002286684,
   0.0002517103,
   0.0003926647,
   0.0005476087,
   0.002071967};
   gre = new TGraphErrors(9,Graph1_fx1022,Graph1_fy1022,Graph1_fex1022,Graph1_fey1022);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11022 = new TH1F("Graph_Graph11022","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11022->SetMinimum(0.003143131);
   Graph_Graph11022->SetMaximum(0.1171718);
   Graph_Graph11022->SetDirectory(0);
   Graph_Graph11022->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11022->SetLineColor(ci);
   Graph_Graph11022->SetLineWidth(3);
   Graph_Graph11022->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11022->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11022->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11022->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11022->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11022->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11022->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11022->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11022->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11022->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11022->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11022->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11022);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1023[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1023[9] = {
   0.02946989,
   0.04421637,
   0.05205604,
   0.05742832,
   0.06074866,
   0.06347653,
   0.06759721,
   0.07368972,
   0.0737398};
   Double_t Graph2_fex1023[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1023[9] = {
   0.0001377867,
   0.000188323,
   0.0002782435,
   0.00041485,
   0.0006134593,
   0.0007942418,
   0.00138543,
   0.001951371,
   0.005364569};
   gre = new TGraphErrors(9,Graph2_fx1023,Graph2_fy1023,Graph2_fex1023,Graph2_fey1023);
   gre->SetName("Graph2");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph21023 = new TH1F("Graph_Graph21023","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph21023->SetMinimum(0.02435488);
   Graph_Graph21023->SetMaximum(0.08408159);
   Graph_Graph21023->SetDirectory(0);
   Graph_Graph21023->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21023->SetLineColor(ci);
   Graph_Graph21023->SetLineWidth(3);
   Graph_Graph21023->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21023->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21023->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21023->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21023->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21023->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21023->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21023->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21023->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21023->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21023->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21023->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21023);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1024[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph3_fy1024[9] = {
   0.004190136,
   0.01364298,
   0.02494127,
   0.0398406,
   0.05326111,
   0.0663648,
   0.07714953,
   0.08550362,
   0.07733397};
   Double_t Graph3_fex1024[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1024[9] = {
   0.0007859174,
   0.0005593733,
   0.0005173093,
   0.0005571198,
   0.0006612252,
   0.0007259483,
   0.001113938,
   0.001455808,
   0.004185233};
   gre = new TGraphErrors(9,Graph3_fx1024,Graph3_fy1024,Graph3_fex1024,Graph3_fey1024);
   gre->SetName("Graph3");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph31024 = new TH1F("Graph_Graph31024","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph31024->SetMinimum(0.003063797);
   Graph_Graph31024->SetMaximum(0.09531495);
   Graph_Graph31024->SetDirectory(0);
   Graph_Graph31024->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph31024->SetLineColor(ci);
   Graph_Graph31024->SetLineWidth(3);
   Graph_Graph31024->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31024->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph31024->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph31024->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31024->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31024->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph31024->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph31024->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph31024->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph31024->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph31024->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph31024->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph31024);
   
   gre->Draw("p");
   can_8->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_4
   TPad *can_4 = new TPad("can_4", "_4",0.6185039,0.5254835,0.8082109,0.9314018);
   can_4->Draw();
   can_4->cd();
   can_4->Range(-0.05,-0.01,2.35,0.13);
   can_4->SetFillColor(0);
   can_4->SetBorderMode(0);
   can_4->SetBorderSize(2);
   can_4->SetTickx(1);
   can_4->SetTicky(1);
   can_4->SetLeftMargin(0);
   can_4->SetRightMargin(0);
   can_4->SetTopMargin(0);
   can_4->SetBottomMargin(0);
   can_4->SetFrameBorderMode(0);
   can_4->SetFrameBorderMode(0);
   
   TH2F *pad_4__7 = new TH2F("pad_4__7","",1,-0.05,2.35,1,-0.01,0.13);
   pad_4__7->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_4__7->SetLineColor(ci);
   pad_4__7->GetXaxis()->SetNdivisions(504);
   pad_4__7->GetXaxis()->SetLabelFont(42);
   pad_4__7->GetXaxis()->SetLabelSize(0.13);
   pad_4__7->GetXaxis()->SetTitleSize(0.13);
   pad_4__7->GetXaxis()->SetTitleOffset(0.9);
   pad_4__7->GetXaxis()->SetTitleFont(42);
   pad_4__7->GetYaxis()->SetNdivisions(504);
   pad_4__7->GetYaxis()->SetLabelFont(42);
   pad_4__7->GetYaxis()->SetLabelSize(0.13);
   pad_4__7->GetYaxis()->SetTitleSize(0.13);
   pad_4__7->GetYaxis()->SetTitleOffset(0.7);
   pad_4__7->GetYaxis()->SetTitleFont(42);
   pad_4__7->GetZaxis()->SetLabelFont(42);
   pad_4__7->GetZaxis()->SetLabelSize(0.035);
   pad_4__7->GetZaxis()->SetTitleSize(0.035);
   pad_4__7->GetZaxis()->SetTitleOffset(1);
   pad_4__7->GetZaxis()->SetTitleFont(42);
   pad_4__7->Draw("");
      tex = new TLatex(0.3,0.1235,"(d)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.2325,0.1235,"v_{2}^{SP}{Q_{2,TPC}}");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fx1025[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fy1025[9] = {
   0.02992353,
   0.04436488,
   0.05216855,
   0.05750915,
   0.06144276,
   0.06553826,
   0.07160225,
   0.08024811,
   0.09611697};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fex1025[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fey1025[9] = {
   3.407116e-05,
   4.802456e-05,
   7.215488e-05,
   0.0001089738,
   0.0001632613,
   0.0002159672,
   0.0003968476,
   0.000646465,
   0.002992691};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid1_fx1025,gr_rebinned_cent_10_40_pv2TPC_pid1_fy1025,gr_rebinned_cent_10_40_pv2TPC_pid1_fex1025,gr_rebinned_cent_10_40_pv2TPC_pid1_fey1025);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid1");
   gre->SetTitle("v2(TPC EP) MODEL of pion_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025","v2(TPC EP) MODEL of pion_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->SetMinimum(0.02296744);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->SetMaximum(0.1060317);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid11025);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fx1026[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fy1026[9] = {
   0.004590017,
   0.01470855,
   0.02881961,
   0.04363064,
   0.05668089,
   0.06941372,
   0.08280546,
   0.09498426,
   0.1059978};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fex1026[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fey1026[9] = {
   0.0001470142,
   0.000106793,
   9.936952e-05,
   0.0001079607,
   0.0001302128,
   0.000146772,
   0.0002366158,
   0.0003458902,
   0.001421074};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid3_fx1026,gr_rebinned_cent_10_40_pv2TPC_pid3_fy1026,gr_rebinned_cent_10_40_pv2TPC_pid3_fex1026,gr_rebinned_cent_10_40_pv2TPC_pid3_fey1026);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid3");
   gre->SetTitle("v2(TPC EP) MODEL of proton_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026","v2(TPC EP) MODEL of proton_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->SetMinimum(0.003998702);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->SetMaximum(0.1177165);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid31026);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fx1027[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fy1027[9] = {
   0.02970333,
   0.04377557,
   0.05172025,
   0.05718442,
   0.06080032,
   0.06360636,
   0.06947765,
   0.07574532,
   0.05878776};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fex1027[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fey1027[9] = {
   0.0001682061,
   0.0002339655,
   0.0003495765,
   0.0005254515,
   0.0007820173,
   0.001024056,
   0.001825268,
   0.002671858,
   0.007594005};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid1_fx1027,gr_rebinned_cent_10_40_pv2TPC_pid1_fy1027,gr_rebinned_cent_10_40_pv2TPC_pid1_fex1027,gr_rebinned_cent_10_40_pv2TPC_pid1_fey1027);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid1");
   gre->SetTitle("v2(TPC EP) MODEL of pion_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027","v2(TPC EP) MODEL of pion_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->SetMinimum(0.02464692);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->SetMaximum(0.08330539);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid11027);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fx1028[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fy1028[9] = {
   0.005929185,
   0.0151659,
   0.03019037,
   0.04329951,
   0.05638871,
   0.06894415,
   0.08034715,
   0.08714775,
   0.09565};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fex1028[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fey1028[9] = {
   0.0007245718,
   0.0005166161,
   0.0004816432,
   0.0005254346,
   0.0006345971,
   0.0007115497,
   0.001122436,
   0.001526748,
   0.004585082};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid3_fx1028,gr_rebinned_cent_10_40_pv2TPC_pid3_fy1028,gr_rebinned_cent_10_40_pv2TPC_pid3_fex1028,gr_rebinned_cent_10_40_pv2TPC_pid3_fey1028);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid3");
   gre->SetTitle("v2(TPC EP) MODEL of proton_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028","v2(TPC EP) MODEL of proton_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->SetMinimum(0.004684152);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->SetMaximum(0.1097381);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid31028);
   
   gre->Draw("p");
   can_4->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_9
   TPad *can_9 = new TPad("can_9", "_9",0.6185039,0,0.8082109,0.5254835);
   can_9->Draw();
   can_9->cd();
   can_9->Range(-0.05,-0.054,2.35,0.13);
   can_9->SetFillColor(0);
   can_9->SetBorderMode(0);
   can_9->SetBorderSize(2);
   can_9->SetTickx(1);
   can_9->SetTicky(1);
   can_9->SetLeftMargin(0);
   can_9->SetRightMargin(0);
   can_9->SetTopMargin(0);
   can_9->SetBottomMargin(0.2391304);
   can_9->SetFrameBorderMode(0);
   can_9->SetFrameBorderMode(0);
   
   TH2F *pad_9__8 = new TH2F("pad_9__8","",1,-0.05,2.35,1,-0.01,0.13);
   pad_9__8->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_9__8->SetLineColor(ci);
   pad_9__8->GetXaxis()->SetNdivisions(504);
   pad_9__8->GetXaxis()->SetLabelFont(42);
   pad_9__8->GetXaxis()->SetLabelSize(0.105);
   pad_9__8->GetXaxis()->SetTitleSize(0.105);
   pad_9__8->GetXaxis()->SetTitleOffset(0.9);
   pad_9__8->GetXaxis()->SetTitleFont(42);
   pad_9__8->GetYaxis()->SetNdivisions(504);
   pad_9__8->GetYaxis()->SetLabelFont(42);
   pad_9__8->GetYaxis()->SetLabelSize(0.105);
   pad_9__8->GetYaxis()->SetTitleSize(0.105);
   pad_9__8->GetYaxis()->SetTitleOffset(0.7);
   pad_9__8->GetYaxis()->SetTitleFont(42);
   pad_9__8->GetZaxis()->SetLabelFont(42);
   pad_9__8->GetZaxis()->SetLabelSize(0.035);
   pad_9__8->GetZaxis()->SetTitleSize(0.035);
   pad_9__8->GetZaxis()->SetTitleOffset(1);
   pad_9__8->GetZaxis()->SetTitleFont(42);
   pad_9__8->Draw("");
      tex = new TLatex(0.3,0.1235,"(i)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.2925,0.1235,"UrQMD");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fx1029[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fy1029[9] = {
   0.02970451,
   0.0442611,
   0.05225047,
   0.05764142,
   0.06123548,
   0.06512031,
   0.0706286,
   0.07884337,
   0.08936537};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fex1029[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fey1029[9] = {
   3.551683e-05,
   4.918569e-05,
   7.305578e-05,
   0.0001093779,
   0.0001626179,
   0.0002128625,
   0.0003827218,
   0.0005982823,
   0.002502921};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid1_fx1029,gr_rebinned_cent_10_40_pv2TPC_pid1_fy1029,gr_rebinned_cent_10_40_pv2TPC_pid1_fex1029,gr_rebinned_cent_10_40_pv2TPC_pid1_fey1029);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid1");
   gre->SetTitle("v2(TPC EP) MODEL of pion_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029","v2(TPC EP) MODEL of pion_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->SetMinimum(0.02344906);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->SetMaximum(0.09808822);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid11029);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fx1030[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fy1030[9] = {
   0.003483678,
   0.01266211,
   0.02606299,
   0.04118329,
   0.05430039,
   0.06735998,
   0.08019914,
   0.09103464,
   0.103715};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fex1030[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fey1030[9] = {
   0.0002031044,
   0.0001473835,
   0.0001359726,
   0.000145612,
   0.0001725029,
   0.0001898648,
   0.0002962903,
   0.0004132977,
   0.001566182};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid3_fx1030,gr_rebinned_cent_10_40_pv2TPC_pid3_fy1030,gr_rebinned_cent_10_40_pv2TPC_pid3_fex1030,gr_rebinned_cent_10_40_pv2TPC_pid3_fey1030);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid3");
   gre->SetTitle("v2(TPC EP) MODEL of proton_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030","v2(TPC EP) MODEL of proton_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->SetMinimum(0.002952516);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->SetMaximum(0.1154812);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid31030);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fx1031[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fy1031[9] = {
   0.02966355,
   0.04398799,
   0.0519541,
   0.05745741,
   0.06066814,
   0.06356787,
   0.0670853,
   0.07238901,
   0.07550419};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fex1031[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid1_fey1031[9] = {
   0.0001281493,
   0.0001751404,
   0.000258773,
   0.0003858077,
   0.000570687,
   0.0007386109,
   0.001287941,
   0.001815189,
   0.00499525};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid1_fx1031,gr_rebinned_cent_10_40_pv2TPC_pid1_fy1031,gr_rebinned_cent_10_40_pv2TPC_pid1_fex1031,gr_rebinned_cent_10_40_pv2TPC_pid1_fey1031);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid1");
   gre->SetTitle("v2(TPC EP) MODEL of pion_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031","v2(TPC EP) MODEL of pion_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->SetMinimum(0.024439);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->SetMaximum(0.08559585);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid11031);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fx1032[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fy1032[9] = {
   0.004349522,
   0.01369489,
   0.02629642,
   0.04060089,
   0.0538858,
   0.06775571,
   0.07799486,
   0.08542355,
   0.08070276};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fex1032[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid3_fey1032[9] = {
   0.0007307271,
   0.0005200972,
   0.0004808284,
   0.0005181336,
   0.0006148642,
   0.0006754483,
   0.001035765,
   0.001355987,
   0.003888191};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid3_fx1032,gr_rebinned_cent_10_40_pv2TPC_pid3_fy1032,gr_rebinned_cent_10_40_pv2TPC_pid3_fex1032,gr_rebinned_cent_10_40_pv2TPC_pid3_fey1032);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid3");
   gre->SetTitle("v2(TPC EP) MODEL of proton_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032","v2(TPC EP) MODEL of proton_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->SetMinimum(0.003256916);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->SetMaximum(0.09509561);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid31032);
   
   gre->Draw("p");
   can_9->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_5
   TPad *can_5 = new TPad("can_5", "_5",0.8082109,0.5254835,0.997918,0.9314018);
   can_5->Draw();
   can_5->cd();
   can_5->Range(-0.05,-0.01,2.35,0.13);
   can_5->SetFillColor(0);
   can_5->SetBorderMode(0);
   can_5->SetBorderSize(2);
   can_5->SetTickx(1);
   can_5->SetTicky(1);
   can_5->SetLeftMargin(0);
   can_5->SetRightMargin(0);
   can_5->SetTopMargin(0);
   can_5->SetBottomMargin(0);
   can_5->SetFrameBorderMode(0);
   can_5->SetFrameBorderMode(0);
   
   TH2F *pad_5__9 = new TH2F("pad_5__9","",1,-0.05,2.35,1,-0.01,0.13);
   pad_5__9->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_5__9->SetLineColor(ci);
   pad_5__9->GetXaxis()->SetNdivisions(504);
   pad_5__9->GetXaxis()->SetLabelFont(42);
   pad_5__9->GetXaxis()->SetLabelSize(0.13);
   pad_5__9->GetXaxis()->SetTitleSize(0.13);
   pad_5__9->GetXaxis()->SetTitleOffset(0.9);
   pad_5__9->GetXaxis()->SetTitleFont(42);
   pad_5__9->GetYaxis()->SetNdivisions(504);
   pad_5__9->GetYaxis()->SetLabelFont(42);
   pad_5__9->GetYaxis()->SetLabelSize(0.13);
   pad_5__9->GetYaxis()->SetTitleSize(0.13);
   pad_5__9->GetYaxis()->SetTitleOffset(0.7);
   pad_5__9->GetYaxis()->SetTitleFont(42);
   pad_5__9->GetZaxis()->SetLabelFont(42);
   pad_5__9->GetZaxis()->SetLabelSize(0.035);
   pad_5__9->GetZaxis()->SetTitleSize(0.035);
   pad_5__9->GetZaxis()->SetTitleOffset(1);
   pad_5__9->GetZaxis()->SetTitleFont(42);
   pad_5__9->Draw("");
      tex = new TLatex(0.3,0.1235,"(e)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.2325,0.1235,"v_{2}^{EP}{#Psi_{1,FHCal}}");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t proff_mc_graph_fx1033[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_mc_graph_fy1033[9] = {
   0.02656783,
   0.03996313,
   0.04731435,
   0.05242778,
   0.05645332,
   0.06112702,
   0.06802225,
   0.07483301,
   0.06235984};
   Double_t proff_mc_graph_fex1033[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_mc_graph_fey1033[9] = {
   6.652248e-05,
   8.743991e-05,
   0.0001292529,
   0.0001946012,
   0.000293805,
   0.000375463,
   0.00110693,
   0.001460279,
   0.009106175};
   gre = new TGraphErrors(9,proff_mc_graph_fx1033,proff_mc_graph_fy1033,proff_mc_graph_fex1033,proff_mc_graph_fey1033);
   gre->SetName("proff_mc_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_mc_graph1033 = new TH1F("Graph_proff_mc_graph1033","GEANT",100,0.055,2.995);
   Graph_proff_mc_graph1033->SetMinimum(0.02152211);
   Graph_proff_mc_graph1033->SetMaximum(0.08127248);
   Graph_proff_mc_graph1033->SetDirectory(0);
   Graph_proff_mc_graph1033->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_mc_graph1033->SetLineColor(ci);
   Graph_proff_mc_graph1033->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_mc_graph1033->GetXaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1033->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1033->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1033->GetXaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1033->GetXaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1033->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_mc_graph1033->GetYaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1033->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1033->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1033->GetYaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1033->GetZaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1033->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1033->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1033->GetZaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1033->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_mc_graph1033);
   
   gre->Draw("p");
   
   Double_t proff_mc_graph_fx1034[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_mc_graph_fy1034[9] = {
   0.006001062,
   0.01328104,
   0.02556169,
   0.03910178,
   0.05067691,
   0.06403184,
   0.07657867,
   0.08456482,
   0.09810076};
   Double_t proff_mc_graph_fex1034[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_mc_graph_fey1034[9] = {
   0.0003015373,
   0.0001470351,
   0.0001316661,
   0.0001421263,
   0.0001706781,
   0.0001767268,
   0.0004281585,
   0.0004935583,
   0.002579305};
   gre = new TGraphErrors(9,proff_mc_graph_fx1034,proff_mc_graph_fy1034,proff_mc_graph_fex1034,proff_mc_graph_fey1034);
   gre->SetName("proff_mc_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_mc_graph1034 = new TH1F("Graph_proff_mc_graph1034","GEANT",100,0.055,2.995);
   Graph_proff_mc_graph1034->SetMinimum(0.005129573);
   Graph_proff_mc_graph1034->SetMaximum(0.1101781);
   Graph_proff_mc_graph1034->SetDirectory(0);
   Graph_proff_mc_graph1034->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_mc_graph1034->SetLineColor(ci);
   Graph_proff_mc_graph1034->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_mc_graph1034->GetXaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1034->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1034->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1034->GetXaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1034->GetXaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1034->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_mc_graph1034->GetYaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1034->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1034->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1034->GetYaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1034->GetZaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1034->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1034->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1034->GetZaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1034->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_mc_graph1034);
   
   gre->Draw("p");
   
   Double_t proff_reco_graph_fx1035[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_reco_graph_fy1035[9] = {
   0.02731255,
   0.04095964,
   0.04818379,
   0.05325992,
   0.05745576,
   0.06177553,
   0.06922423,
   0.07822526,
   0.06500539};
   Double_t proff_reco_graph_fex1035[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_reco_graph_fey1035[9] = {
   0.0001216251,
   0.0001599793,
   0.0002367713,
   0.000356683,
   0.0005392233,
   0.000689891,
   0.002032036,
   0.002694019,
   0.0167649};
   gre = new TGraphErrors(9,proff_reco_graph_fx1035,proff_reco_graph_fy1035,proff_reco_graph_fex1035,proff_reco_graph_fey1035);
   gre->SetName("proff_reco_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_reco_graph1035 = new TH1F("Graph_proff_reco_graph1035","Reco",100,0.055,2.995);
   Graph_proff_reco_graph1035->SetMinimum(0.02173299);
   Graph_proff_reco_graph1035->SetMaximum(0.08722823);
   Graph_proff_reco_graph1035->SetDirectory(0);
   Graph_proff_reco_graph1035->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_reco_graph1035->SetLineColor(ci);
   Graph_proff_reco_graph1035->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_reco_graph1035->GetXaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1035->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1035->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1035->GetXaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1035->GetXaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1035->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_reco_graph1035->GetYaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1035->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1035->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1035->GetYaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1035->GetZaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1035->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1035->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1035->GetZaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1035->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_reco_graph1035);
   
   gre->Draw("p");
   
   Double_t proff_reco_graph_fx1036[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_reco_graph_fy1036[9] = {
   0.005802583,
   0.01356499,
   0.02639168,
   0.04001196,
   0.05101801,
   0.0644418,
   0.07671464,
   0.08402479,
   0.1009886};
   Double_t proff_reco_graph_fex1036[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_reco_graph_fey1036[9] = {
   0.0005504144,
   0.0002687396,
   0.0002409602,
   0.0002605506,
   0.000313428,
   0.0003252045,
   0.0007898584,
   0.0009123233,
   0.004792404};
   gre = new TGraphErrors(9,proff_reco_graph_fx1036,proff_reco_graph_fy1036,proff_reco_graph_fex1036,proff_reco_graph_fey1036);
   gre->SetName("proff_reco_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_reco_graph1036 = new TH1F("Graph_proff_reco_graph1036","Reco",100,0.055,2.995);
   Graph_proff_reco_graph1036->SetMinimum(0.004726951);
   Graph_proff_reco_graph1036->SetMaximum(0.1158339);
   Graph_proff_reco_graph1036->SetDirectory(0);
   Graph_proff_reco_graph1036->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_reco_graph1036->SetLineColor(ci);
   Graph_proff_reco_graph1036->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_reco_graph1036->GetXaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1036->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1036->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1036->GetXaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1036->GetXaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1036->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_reco_graph1036->GetYaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1036->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1036->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1036->GetYaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1036->GetZaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1036->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1036->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1036->GetZaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1036->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_reco_graph1036);
   
   gre->Draw("p");
   can_5->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_10
   TPad *can_10 = new TPad("can_10", "_10",0.8082109,0,0.997918,0.5254835);
   can_10->Draw();
   can_10->cd();
   can_10->Range(-0.05,-0.054,2.35,0.13);
   can_10->SetFillColor(0);
   can_10->SetBorderMode(0);
   can_10->SetBorderSize(2);
   can_10->SetTickx(1);
   can_10->SetTicky(1);
   can_10->SetLeftMargin(0);
   can_10->SetRightMargin(0);
   can_10->SetTopMargin(0);
   can_10->SetBottomMargin(0.2391304);
   can_10->SetFrameBorderMode(0);
   can_10->SetFrameBorderMode(0);
   
   TH2F *pad_10__10 = new TH2F("pad_10__10","",1,-0.05,2.35,1,-0.01,0.13);
   pad_10__10->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_10__10->SetLineColor(ci);
   pad_10__10->GetXaxis()->SetNdivisions(504);
   pad_10__10->GetXaxis()->SetLabelFont(42);
   pad_10__10->GetXaxis()->SetLabelSize(0.105);
   pad_10__10->GetXaxis()->SetTitleSize(0.105);
   pad_10__10->GetXaxis()->SetTitleOffset(0.9);
   pad_10__10->GetXaxis()->SetTitleFont(42);
   pad_10__10->GetYaxis()->SetNdivisions(504);
   pad_10__10->GetYaxis()->SetLabelFont(42);
   pad_10__10->GetYaxis()->SetLabelSize(0.105);
   pad_10__10->GetYaxis()->SetTitleSize(0.105);
   pad_10__10->GetYaxis()->SetTitleOffset(0.7);
   pad_10__10->GetYaxis()->SetTitleFont(42);
   pad_10__10->GetZaxis()->SetLabelFont(42);
   pad_10__10->GetZaxis()->SetLabelSize(0.035);
   pad_10__10->GetZaxis()->SetTitleSize(0.035);
   pad_10__10->GetZaxis()->SetTitleOffset(1);
   pad_10__10->GetZaxis()->SetTitleFont(42);
   pad_10__10->Draw("");
      tex = new TLatex(0.3,0.1235,"(j)");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.2925,0.1235,"GEANT4");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t proff_mc_graph_fx1037[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_mc_graph_fy1037[9] = {
   0.02603508,
   0.03896386,
   0.04557311,
   0.05025068,
   0.05287335,
   0.05555152,
   0.0608269,
   0.0608809,
   0.05776524};
   Double_t proff_mc_graph_fex1037[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_mc_graph_fey1037[9] = {
   0.0001086077,
   0.0001405554,
   0.0002060396,
   0.0003089219,
   0.0004661116,
   0.0005935591,
   0.001744392,
   0.002279743,
   0.01347125};
   gre = new TGraphErrors(9,proff_mc_graph_fx1037,proff_mc_graph_fy1037,proff_mc_graph_fex1037,proff_mc_graph_fey1037);
   gre->SetName("proff_mc_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_mc_graph1037 = new TH1F("Graph_proff_mc_graph1037","GEANT",100,0.055,2.995);
   Graph_proff_mc_graph1037->SetMinimum(0.02139547);
   Graph_proff_mc_graph1037->SetMaximum(0.07576749);
   Graph_proff_mc_graph1037->SetDirectory(0);
   Graph_proff_mc_graph1037->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_mc_graph1037->SetLineColor(ci);
   Graph_proff_mc_graph1037->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_mc_graph1037->GetXaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1037->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1037->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1037->GetXaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1037->GetXaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1037->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_mc_graph1037->GetYaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1037->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1037->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1037->GetYaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1037->GetZaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1037->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1037->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1037->GetZaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1037->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_mc_graph1037);
   
   gre->Draw("p");
   
   Double_t proff_mc_graph_fx1038[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_mc_graph_fy1038[9] = {
   0.005165088,
   0.01097961,
   0.02168781,
   0.03476376,
   0.04513467,
   0.05861413,
   0.06916352,
   0.07470169,
   0.08438023};
   Double_t proff_mc_graph_fex1038[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_mc_graph_fey1038[9] = {
   0.0006454145,
   0.0003157304,
   0.0002813587,
   0.0003005282,
   0.0003558831,
   0.0003614085,
   0.0008615186,
   0.0009820903,
   0.005026291};
   gre = new TGraphErrors(9,proff_mc_graph_fx1038,proff_mc_graph_fy1038,proff_mc_graph_fex1038,proff_mc_graph_fey1038);
   gre->SetName("proff_mc_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_mc_graph1038 = new TH1F("Graph_proff_mc_graph1038","GEANT",100,0.055,2.995);
   Graph_proff_mc_graph1038->SetMinimum(0.004067706);
   Graph_proff_mc_graph1038->SetMaximum(0.0978952);
   Graph_proff_mc_graph1038->SetDirectory(0);
   Graph_proff_mc_graph1038->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_mc_graph1038->SetLineColor(ci);
   Graph_proff_mc_graph1038->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_mc_graph1038->GetXaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1038->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1038->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1038->GetXaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1038->GetXaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1038->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_mc_graph1038->GetYaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1038->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1038->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1038->GetYaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1038->GetZaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1038->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1038->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1038->GetZaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1038->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_mc_graph1038);
   
   gre->Draw("p");
   
   Double_t proff_reco_graph_fx1039[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_reco_graph_fy1039[9] = {
   0.0267109,
   0.04024616,
   0.04670509,
   0.0515071,
   0.05360008,
   0.05596915,
   0.0572717,
   0.06116395,
   0.06178779};
   Double_t proff_reco_graph_fex1039[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_reco_graph_fey1039[9] = {
   0.0001723561,
   0.0002231781,
   0.0003274219,
   0.0004913689,
   0.0007417895,
   0.0009449485,
   0.002778437,
   0.003635597,
   0.02182263};
   gre = new TGraphErrors(9,proff_reco_graph_fx1039,proff_reco_graph_fy1039,proff_reco_graph_fex1039,proff_reco_graph_fey1039);
   gre->SetName("proff_reco_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_reco_graph1039 = new TH1F("Graph_proff_reco_graph1039","Reco",100,0.055,2.995);
   Graph_proff_reco_graph1039->SetMinimum(0.02083136);
   Graph_proff_reco_graph1039->SetMaximum(0.08931761);
   Graph_proff_reco_graph1039->SetDirectory(0);
   Graph_proff_reco_graph1039->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_reco_graph1039->SetLineColor(ci);
   Graph_proff_reco_graph1039->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_reco_graph1039->GetXaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1039->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1039->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1039->GetXaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1039->GetXaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1039->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_reco_graph1039->GetYaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1039->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1039->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1039->GetYaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1039->GetZaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1039->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1039->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1039->GetZaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1039->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_reco_graph1039);
   
   gre->Draw("p");
   
   Double_t proff_reco_graph_fx1040[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_reco_graph_fy1040[9] = {
   0.005706095,
   0.01160895,
   0.02235751,
   0.03546616,
   0.04532397,
   0.0588679,
   0.06811316,
   0.0749853,
   0.08037192};
   Double_t proff_reco_graph_fex1040[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_reco_graph_fey1040[9] = {
   0.001022497,
   0.0005006644,
   0.0004469536,
   0.0004780321,
   0.0005665656,
   0.0005761802,
   0.001375726,
   0.001571648,
   0.008070755};
   gre = new TGraphErrors(9,proff_reco_graph_fx1040,proff_reco_graph_fy1040,proff_reco_graph_fex1040,proff_reco_graph_fey1040);
   gre->SetName("proff_reco_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_proff_reco_graph1040 = new TH1F("Graph_proff_reco_graph1040","Reco",100,0.055,2.995);
   Graph_proff_reco_graph1040->SetMinimum(0.004215238);
   Graph_proff_reco_graph1040->SetMaximum(0.09681858);
   Graph_proff_reco_graph1040->SetDirectory(0);
   Graph_proff_reco_graph1040->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_reco_graph1040->SetLineColor(ci);
   Graph_proff_reco_graph1040->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_reco_graph1040->GetXaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1040->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1040->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1040->GetXaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1040->GetXaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1040->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_reco_graph1040->GetYaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1040->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1040->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1040->GetYaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1040->GetZaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1040->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1040->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1040->GetZaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1040->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_reco_graph1040);
   
   gre->Draw("p");
   can_10->Modified();
   can->cd();
   can->Modified();
   can->cd();
   can->SetSelected(can);
}
