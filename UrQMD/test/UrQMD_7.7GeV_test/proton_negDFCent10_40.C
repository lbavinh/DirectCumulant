void proton_negDFCent10_40()
{
//=========Macro generated from canvas: c1_n9/Canvas
//=========  (Fri Apr 23 20:00:15 2021) by ROOT version 6.22/08
   TCanvas *c1_n9 = new TCanvas("c1_n9", "Canvas",0,0,550,550);
   c1_n9->Range(0,0,1,1);
   c1_n9->SetFillColor(0);
   c1_n9->SetBorderMode(0);
   c1_n9->SetBorderSize(2);
   c1_n9->SetTickx(1);
   c1_n9->SetTicky(1);
   c1_n9->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: padUp
   TPad *padUp = new TPad("padUp", "v2 vs pt",0,0.33,1,1);
   padUp->Draw();
   padUp->cd();
   padUp->Range(-0.6296296,-0.01,3.074074,0.2233333);
   padUp->SetFillColor(0);
   padUp->SetBorderMode(0);
   padUp->SetBorderSize(0);
   padUp->SetTickx(1);
   padUp->SetTicky(1);
   padUp->SetLeftMargin(0.17);
   padUp->SetRightMargin(0.02);
   padUp->SetBottomMargin(0);
   padUp->SetFrameBorderMode(0);
   padUp->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1057[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph0_fy1057[33] = {
   0.1617131,
   -0.03162188,
   -0.01226139,
   0.0004223815,
   -0.001384422,
   0.002180753,
   -0.008611175,
   -0.007203818,
   0.008133353,
   0.009505797,
   0.02342799,
   0.02796059,
   0.03420144,
   0.0459339,
   0.05736113,
   0.06828991,
   0.08028392,
   0.08926161,
   0.09910225,
   0.09799655,
   0.1054127,
   0.1129049,
   0.1188491,
   0.09555319,
   0.1238345,
   0.1282108,
   0.1263992,
   0.1308205,
   0.1254807,
   0.1459541,
   0.1419677,
   0.1314196,
   0.2762661};
   Double_t Graph0_fex1057[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1057[33] = {
   0.07848846,
   0.03090694,
   0.01837334,
   0.01328336,
   0.01024172,
   0.008362991,
   0.007079182,
   0.006147101,
   0.005436452,
   0.004919572,
   0.004553197,
   0.004261639,
   0.002827937,
   0.002726058,
   0.002765302,
   0.00292197,
   0.003191839,
   0.003600517,
   0.00412801,
   0.004825337,
   0.005752874,
   0.006877622,
   0.008388025,
   0.01024466,
   0.01255257,
   0.01545686,
   0.01924531,
   0.0236298,
   0.02966532,
   0.03715524,
   0.04680547,
   0.04477961,
   0.06305873};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1057,Graph0_fy1057,Graph0_fex1057,Graph0_fey1057);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#2b3f79");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2b3f79");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01057 = new TH1F("Graph_Graph01057","",100,0,3);
   Graph_Graph01057->SetMinimum(-0.01);
   Graph_Graph01057->SetMaximum(0.2);
   Graph_Graph01057->SetDirectory(0);
   Graph_Graph01057->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01057->SetLineColor(ci);
   Graph_Graph01057->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01057->GetXaxis()->SetLabelFont(42);
   Graph_Graph01057->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01057->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01057->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01057->GetXaxis()->SetTitleFont(42);
   Graph_Graph01057->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01057->GetYaxis()->SetLabelFont(42);
   Graph_Graph01057->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01057->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01057->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01057->GetYaxis()->SetTitleFont(42);
   Graph_Graph01057->GetZaxis()->SetLabelFont(42);
   Graph_Graph01057->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01057->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01057);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1058[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph1_fy1058[33] = {
   0.2165396,
   -0.06804859,
   -0.05513699,
   -0.0102158,
   0.02233606,
   -0.008593362,
   0.02250505,
   -0.006177112,
   0.01316384,
   0.01994034,
   0.01978111,
   0.0253632,
   0.0409608,
   0.04025141,
   0.05253489,
   0.06665501,
   0.08224146,
   0.08869684,
   0.08170709,
   0.1093218,
   0.09375113,
   0.1272041,
   0.1139004,
   0.110324,
   0.1471482,
   0.107195,
   0.02837182,
   0.1154428,
   0.1634663,
   0.09147689,
   0.1045317,
   0.02057601,
   0.3391593};
   Double_t Graph1_fex1058[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1058[33] = {
   0.1446245,
   0.05382701,
   0.03266415,
   0.02380867,
   0.01846162,
   0.01515219,
   0.01281202,
   0.01119044,
   0.01000729,
   0.009101461,
   0.008488302,
   0.007928597,
   0.005288996,
   0.005128148,
   0.005233716,
   0.005545392,
   0.006076216,
   0.00684302,
   0.007878394,
   0.009184608,
   0.01102524,
   0.01324144,
   0.0160889,
   0.01964139,
   0.02420206,
   0.02980727,
   0.03721596,
   0.04542894,
   0.05624737,
   0.07105613,
   0.08762455,
   0.08574422,
   0.1216759};
   gre = new TGraphErrors(33,Graph1_fx1058,Graph1_fy1058,Graph1_fex1058,Graph1_fey1058);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11058 = new TH1F("Graph_Graph11058","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11058->SetMinimum(-0.1801467);
   Graph_Graph11058->SetMaximum(0.5191063);
   Graph_Graph11058->SetDirectory(0);
   Graph_Graph11058->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11058->SetLineColor(ci);
   Graph_Graph11058->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11058->GetXaxis()->SetLabelFont(42);
   Graph_Graph11058->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11058->GetXaxis()->SetTitleFont(42);
   Graph_Graph11058->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11058->GetYaxis()->SetLabelFont(42);
   Graph_Graph11058->GetYaxis()->SetTitleFont(42);
   Graph_Graph11058->GetZaxis()->SetLabelFont(42);
   Graph_Graph11058->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11058->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11058);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1059[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph2_fy1059[33] = {
   -0.02940424,
   -0.1551388,
   -0.1326114,
   -0.1372629,
   -0.01065402,
   -0.00739056,
   -0.01657253,
   -0.0130903,
   -0.006228516,
   -0.0003692585,
   0.01046639,
   0.01081058,
   0.02306943,
   0.03703905,
   0.04895807,
   0.06265895,
   0.07522272,
   0.08437158,
   0.09167354,
   0.09427478,
   0.1086016,
   0.113218,
   0.1094124,
   0.1016082,
   0.1179161,
   0.1249997,
   0.1249466,
   0.114097,
   0.118785,
   0.17195,
   0.1153274,
   0.140543,
   0.1761326};
   Double_t Graph2_fex1059[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1059[33] = {
   0.05847134,
   0.02299647,
   0.01381318,
   0.009883314,
   0.007641726,
   0.006254083,
   0.005274463,
   0.004579168,
   0.004049132,
   0.003666021,
   0.00338842,
   0.003164084,
   0.002098898,
   0.002021463,
   0.002050169,
   0.002159283,
   0.002354682,
   0.002655125,
   0.003051287,
   0.003542031,
   0.004221819,
   0.005080248,
   0.006156706,
   0.007483575,
   0.009183575,
   0.01127618,
   0.014188,
   0.01736086,
   0.02171177,
   0.02748644,
   0.03395234,
   0.0319052,
   0.04608529};
   gre = new TGraphErrors(33,Graph2_fx1059,Graph2_fy1059,Graph2_fex1059,Graph2_fey1059);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21059 = new TH1F("Graph_Graph21059","v_{2}{2}",100,0,3.1325);
   Graph_Graph21059->SetMinimum(-0.2181706);
   Graph_Graph21059->SetMaximum(0.2622533);
   Graph_Graph21059->SetDirectory(0);
   Graph_Graph21059->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21059->SetLineColor(ci);
   Graph_Graph21059->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21059->GetXaxis()->SetLabelFont(42);
   Graph_Graph21059->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21059->GetXaxis()->SetTitleFont(42);
   Graph_Graph21059->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21059->GetYaxis()->SetLabelFont(42);
   Graph_Graph21059->GetYaxis()->SetTitleFont(42);
   Graph_Graph21059->GetZaxis()->SetLabelFont(42);
   Graph_Graph21059->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21059->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21059);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1060[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph3_fy1060[33] = {
   0.3528317,
   0.2194821,
   -0.1558377,
   0.04655536,
   0.03936029,
   0.03014171,
   0.01991834,
   -0.001156523,
   0.02128159,
   0.05564697,
   0.02427984,
   0.01745687,
   0.04526749,
   0.06283966,
   0.0782423,
   0.07927661,
   0.08144637,
   0.09544342,
   0.1088085,
   0.09742599,
   0.1600188,
   0.1187247,
   0.05677297,
   0.0978674,
   0.1258295,
   0.09924993,
   0.1212128,
   0.06209572,
   0.1432923,
   -0.05728208,
   0.1237518,
   0.06545651,
   0.2773777};
   Double_t Graph3_fex1060[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1060[33] = {
   0.4071042,
   0.1771363,
   0.09553584,
   0.07029237,
   0.05554643,
   0.04273468,
   0.03584524,
   0.03068748,
   0.02661337,
   0.02424134,
   0.02178795,
   0.02053335,
   0.01335474,
   0.01267232,
   0.01275994,
   0.01324991,
   0.01423687,
   0.01634942,
   0.01864086,
   0.02148727,
   0.02529392,
   0.03065095,
   0.03664201,
   0.04364181,
   0.05419206,
   0.06391614,
   0.08732902,
   0.1011671,
   0.1165997,
   0.1620407,
   0.1856423,
   0.1894848,
   0.2907499};
   gre = new TGraphErrors(33,Graph3_fx1060,Graph3_fy1060,Graph3_fex1060,Graph3_fey1060);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31060 = new TH1F("Graph_Graph31060","v_{2}{4}",100,0,3.1325);
   Graph_Graph31060->SetMinimum(-0.3525045);
   Graph_Graph31060->SetMaximum(0.8610669);
   Graph_Graph31060->SetDirectory(0);
   Graph_Graph31060->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31060->SetLineColor(ci);
   Graph_Graph31060->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31060->GetXaxis()->SetLabelFont(42);
   Graph_Graph31060->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31060->GetXaxis()->SetTitleFont(42);
   Graph_Graph31060->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31060->GetYaxis()->SetLabelFont(42);
   Graph_Graph31060->GetYaxis()->SetTitleFont(42);
   Graph_Graph31060->GetZaxis()->SetLabelFont(42);
   Graph_Graph31060->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31060->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31060);
   
   gre->Draw("p plc pmc");
   
   TLegend *leg = new TLegend(0.18,0.5,0.45,0.889,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextAlign(22);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph0","v_{2}{2,#eta-gap,TPC}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#2b3f79");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","v_{2}{2,#eta-gap,FHCal}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#3d6030");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","v_{2}{2}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ae9437");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph3","v_{2}{4}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#9c272b");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.56,0.74,0.85,0.85,"NDC NB");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.05);
   TText *pt_LaTex = pt->AddText("UrQMD, Au+Au at #sqrt{s_{NN}}=7.7GeV");
   pt_LaTex = pt->AddText("10-40%, #bar{p}");
   pt->Draw();
   padUp->Modified();
   c1_n9->cd();
  
// ------------>Primitives in pad: padDown
   TPad *padDown = new TPad("padDown", "Ratio v2",0,0,1,0.33);
   padDown->Draw();
   padDown->cd();
   padDown->Range(-0.6296296,0.7018705,3.074074,1.162302);
   padDown->SetFillColor(0);
   padDown->SetBorderMode(0);
   padDown->SetBorderSize(0);
   padDown->SetTickx(1);
   padDown->SetTicky(1);
   padDown->SetLeftMargin(0.17);
   padDown->SetRightMargin(0.02);
   padDown->SetTopMargin(0.005);
   padDown->SetBottomMargin(0.3);
   padDown->SetFrameBorderMode(0);
   padDown->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1061[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph0_fy1061[33] = {
   1.339036,
   2.151947,
   4.496799,
   24.18619,
   16.13385,
   3.940548,
   2.61347,
   0.8574776,
   1.618502,
   2.097703,
   0.8443369,
   0.9071051,
   1.197634,
   0.8762899,
   0.9158623,
   0.9760595,
   1.024383,
   0.9936729,
   0.8244726,
   1.115568,
   0.8893722,
   1.126648,
   0.9583617,
   1.154582,
   1.188265,
   0.8360836,
   0.224462,
   0.8824516,
   1.30272,
   0.6267509,
   0.7363064,
   0.1565672,
   1.227654};
   Double_t Graph0_fex1061[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1061[33] = {
   1.105534,
   2.7058,
   7.245815,
   762.7107,
   120.0981,
   16.63245,
   2.613383,
   1.717103,
   1.638367,
   1.447528,
   0.3977428,
   0.315473,
   0.1836313,
   0.1231604,
   0.101363,
   0.09131384,
   0.08594599,
   0.08650819,
   0.08659844,
   0.1086347,
   0.1153048,
   0.1358844,
   0.1513297,
   0.23995,
   0.2295743,
   0.2533966,
   0.2964087,
   0.3820961,
   0.5438608,
   0.5123167,
   0.6632371,
   0.6546234,
   0.5220152};
   gre = new TGraphErrors(33,Graph0_fx1061,Graph0_fy1061,Graph0_fex1061,Graph0_fey1061);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01061 = new TH1F("Graph_Graph01061","",100,0,3);
   Graph_Graph01061->SetMinimum(0.84);
   Graph_Graph01061->SetMaximum(1.16);
   Graph_Graph01061->SetDirectory(0);
   Graph_Graph01061->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01061->SetLineColor(ci);
   Graph_Graph01061->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01061->GetXaxis()->SetLabelFont(42);
   Graph_Graph01061->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01061->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01061->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01061->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01061->GetXaxis()->SetTitleFont(42);
   Graph_Graph01061->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01061->GetYaxis()->CenterTitle(true);
   Graph_Graph01061->GetYaxis()->SetNdivisions(504);
   Graph_Graph01061->GetYaxis()->SetLabelFont(42);
   Graph_Graph01061->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01061->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01061->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01061->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01061->GetYaxis()->SetTitleFont(42);
   Graph_Graph01061->GetZaxis()->SetLabelFont(42);
   Graph_Graph01061->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01061->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01061);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1062[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph0_fy1062[33] = {
   1.339036,
   2.151947,
   4.496799,
   24.18619,
   16.13385,
   3.940548,
   2.61347,
   0.8574776,
   1.618502,
   2.097703,
   0.8443369,
   0.9071051,
   1.197634,
   0.8762899,
   0.9158623,
   0.9760595,
   1.024383,
   0.9936729,
   0.8244726,
   1.115568,
   0.8893722,
   1.126648,
   0.9583617,
   1.154582,
   1.188265,
   0.8360836,
   0.224462,
   0.8824516,
   1.30272,
   0.6267509,
   0.7363064,
   0.1565672,
   1.227654};
   Double_t Graph0_fex1062[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1062[33] = {
   1.105534,
   2.7058,
   7.245815,
   762.7107,
   120.0981,
   16.63245,
   2.613383,
   1.717103,
   1.638367,
   1.447528,
   0.3977428,
   0.315473,
   0.1836313,
   0.1231604,
   0.101363,
   0.09131384,
   0.08594599,
   0.08650819,
   0.08659844,
   0.1086347,
   0.1153048,
   0.1358844,
   0.1513297,
   0.23995,
   0.2295743,
   0.2533966,
   0.2964087,
   0.3820961,
   0.5438608,
   0.5123167,
   0.6632371,
   0.6546234,
   0.5220152};
   gre = new TGraphErrors(33,Graph0_fx1062,Graph0_fy1062,Graph0_fex1062,Graph0_fey1062);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010611062 = new TH1F("Graph_Graph_Graph010611062","",100,0,3);
   Graph_Graph_Graph010611062->SetMinimum(0.84);
   Graph_Graph_Graph010611062->SetMaximum(1.16);
   Graph_Graph_Graph010611062->SetDirectory(0);
   Graph_Graph_Graph010611062->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010611062->SetLineColor(ci);
   Graph_Graph_Graph010611062->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010611062->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010611062->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010611062->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010611062->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010611062->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010611062->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010611062->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010611062->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010611062->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010611062->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010611062->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010611062->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010611062->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010611062->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010611062->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010611062->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010611062->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010611062->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010611062);
   
   gre->Draw("p plc pmc");
   TLine *line = new TLine(0,1,3,1);

   ci = TColor::GetColor("#006699");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(0,0.95,3,0.95);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,1.05,3,1.05);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   Double_t Graph1_fx1063[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph1_fy1063[33] = {
   0.1818297,
   4.90606,
   10.81536,
   324.9736,
   7.695642,
   3.388994,
   1.924538,
   1.817134,
   0.7657994,
   0.03884562,
   0.4467475,
   0.3866365,
   0.6745163,
   0.8063555,
   0.8535061,
   0.9175434,
   0.9369588,
   0.945217,
   0.92504,
   0.9620214,
   1.030251,
   1.002773,
   0.9205993,
   1.063368,
   0.9522074,
   0.974954,
   0.9885077,
   0.8721642,
   0.9466396,
   1.178109,
   0.8123497,
   1.069422,
   0.637547};
   Double_t Graph1_fex1063[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1063[33] = {
   0.372189,
   4.849971,
   16.24562,
   10220.03,
   57.19801,
   13.30914,
   1.696575,
   1.675817,
   0.7140449,
   0.3861853,
   0.1686913,
   0.1275868,
   0.08292559,
   0.06501402,
   0.05450205,
   0.05040932,
   0.04741118,
   0.04835754,
   0.04932209,
   0.05958455,
   0.06903163,
   0.07586759,
   0.08309661,
   0.1383172,
   0.1217212,
   0.1468012,
   0.1877559,
   0.2059834,
   0.2828862,
   0.3541336,
   0.3590616,
   0.4378591,
   0.2213684};
   gre = new TGraphErrors(33,Graph1_fx1063,Graph1_fy1063,Graph1_fex1063,Graph1_fey1063);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11063 = new TH1F("Graph_Graph11063","",100,0,3.1325);
   Graph_Graph11063->SetMinimum(0.84);
   Graph_Graph11063->SetMaximum(1.16);
   Graph_Graph11063->SetDirectory(0);
   Graph_Graph11063->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11063->SetLineColor(ci);
   Graph_Graph11063->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11063->GetXaxis()->SetLabelFont(42);
   Graph_Graph11063->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11063->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11063->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11063->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11063->GetXaxis()->SetTitleFont(42);
   Graph_Graph11063->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11063->GetYaxis()->CenterTitle(true);
   Graph_Graph11063->GetYaxis()->SetNdivisions(504);
   Graph_Graph11063->GetYaxis()->SetLabelFont(42);
   Graph_Graph11063->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11063->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11063->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11063->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11063->GetYaxis()->SetTitleFont(42);
   Graph_Graph11063->GetZaxis()->SetLabelFont(42);
   Graph_Graph11063->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11063->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11063);
   
   gre->Draw("p plc pmc");
   line = new TLine(0,1,3,1);

   ci = TColor::GetColor("#006699");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(0,0.95,3,0.95);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,1.05,3,1.05);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   Double_t Graph2_fx1064[33] = {
   0.025,
   0.075,
   0.125,
   0.175,
   0.225,
   0.275,
   0.325,
   0.375,
   0.425,
   0.475,
   0.525,
   0.575,
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.25,
   1.35,
   1.45,
   1.55,
   1.65,
   1.75,
   1.85,
   1.95,
   2.05,
   2.15,
   2.25,
   2.35,
   2.45,
   2.6,
   2.85};
   Double_t Graph2_fy1064[33] = {
   2.181838,
   6.940831,
   12.70963,
   110.2211,
   28.43084,
   13.82169,
   2.31308,
   0.160543,
   2.616583,
   5.854004,
   1.03636,
   0.6243385,
   1.323555,
   1.368045,
   1.36403,
   1.160883,
   1.014479,
   1.069255,
   1.097942,
   0.9941778,
   1.518022,
   1.051546,
   0.4776897,
   1.024219,
   1.01611,
   0.774115,
   0.9589676,
   0.4746634,
   1.141947,
   0.3924663,
   0.8716903,
   0.4980725,
   1.004024};
   Double_t Graph2_fex1064[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1064[33] = {
   2.731109,
   8.797751,
   20.57721,
   3470.306,
   214.1193,
   56.51141,
   4.576411,
   4.262093,
   3.710214,
   3.960062,
   0.9515576,
   0.7405071,
   0.405519,
   0.2875803,
   0.2319651,
   0.2002816,
   0.1818603,
   0.1881725,
   0.1935772,
   0.2246638,
   0.2538505,
   0.2789304,
   0.310145,
   0.4697434,
   0.4495746,
   0.507184,
   0.7061584,
   0.7780655,
   0.9676478,
   1.114703,
   1.338846,
   1.451784,
   1.07709};
   gre = new TGraphErrors(33,Graph2_fx1064,Graph2_fy1064,Graph2_fex1064,Graph2_fey1064);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21064 = new TH1F("Graph_Graph21064","",100,0,3.1325);
   Graph_Graph21064->SetMinimum(0.84);
   Graph_Graph21064->SetMaximum(1.16);
   Graph_Graph21064->SetDirectory(0);
   Graph_Graph21064->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21064->SetLineColor(ci);
   Graph_Graph21064->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21064->GetXaxis()->SetLabelFont(42);
   Graph_Graph21064->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21064->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21064->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21064->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21064->GetXaxis()->SetTitleFont(42);
   Graph_Graph21064->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21064->GetYaxis()->CenterTitle(true);
   Graph_Graph21064->GetYaxis()->SetNdivisions(504);
   Graph_Graph21064->GetYaxis()->SetLabelFont(42);
   Graph_Graph21064->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21064->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21064->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21064->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21064->GetYaxis()->SetTitleFont(42);
   Graph_Graph21064->GetZaxis()->SetLabelFont(42);
   Graph_Graph21064->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21064->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21064);
   
   gre->Draw("p plc pmc");
   line = new TLine(0,1,3,1);

   ci = TColor::GetColor("#006699");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(0,0.95,3,0.95);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,1.05,3,1.05);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   padDown->Modified();
   c1_n9->cd();
   c1_n9->Modified();
   c1_n9->cd();
   c1_n9->SetSelected(c1_n9);
}
