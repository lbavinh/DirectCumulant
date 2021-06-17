void proton_negDFCent10-40()
{
//=========Macro generated from canvas: 10-40%, #bar{p}/Canvas
//=========  (Fri Apr 23 19:43:59 2021) by ROOT version 6.22/08
   TCanvas *10-40%, #bar{p} = new TCanvas("10-40%, #bar{p}", "Canvas",0,0,550,550);
   10-40%, #bar{p}->Range(0,0,1,1);
   10-40%, #bar{p}->SetFillColor(0);
   10-40%, #bar{p}->SetBorderMode(0);
   10-40%, #bar{p}->SetBorderSize(2);
   10-40%, #bar{p}->SetTickx(1);
   10-40%, #bar{p}->SetTicky(1);
   10-40%, #bar{p}->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1085[33] = {
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
   Double_t Graph0_fy1085[33] = {
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
   Double_t Graph0_fex1085[33] = {
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
   Double_t Graph0_fey1085[33] = {
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
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1085,Graph0_fy1085,Graph0_fex1085,Graph0_fey1085);
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
   
   TH1F *Graph_Graph01085 = new TH1F("Graph_Graph01085","",100,0,3);
   Graph_Graph01085->SetMinimum(-0.01);
   Graph_Graph01085->SetMaximum(0.2);
   Graph_Graph01085->SetDirectory(0);
   Graph_Graph01085->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01085->SetLineColor(ci);
   Graph_Graph01085->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01085->GetXaxis()->SetLabelFont(42);
   Graph_Graph01085->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01085->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01085->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01085->GetXaxis()->SetTitleFont(42);
   Graph_Graph01085->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01085->GetYaxis()->SetLabelFont(42);
   Graph_Graph01085->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01085->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01085->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01085->GetYaxis()->SetTitleFont(42);
   Graph_Graph01085->GetZaxis()->SetLabelFont(42);
   Graph_Graph01085->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01085->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01085);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1086[33] = {
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
   Double_t Graph1_fy1086[33] = {
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
   Double_t Graph1_fex1086[33] = {
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
   Double_t Graph1_fey1086[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1086,Graph1_fy1086,Graph1_fex1086,Graph1_fey1086);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11086 = new TH1F("Graph_Graph11086","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11086->SetMinimum(-0.1801467);
   Graph_Graph11086->SetMaximum(0.5191063);
   Graph_Graph11086->SetDirectory(0);
   Graph_Graph11086->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11086->SetLineColor(ci);
   Graph_Graph11086->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11086->GetXaxis()->SetLabelFont(42);
   Graph_Graph11086->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11086->GetXaxis()->SetTitleFont(42);
   Graph_Graph11086->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11086->GetYaxis()->SetLabelFont(42);
   Graph_Graph11086->GetYaxis()->SetTitleFont(42);
   Graph_Graph11086->GetZaxis()->SetLabelFont(42);
   Graph_Graph11086->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11086->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11086);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1087[33] = {
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
   Double_t Graph2_fy1087[33] = {
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
   Double_t Graph2_fex1087[33] = {
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
   Double_t Graph2_fey1087[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1087,Graph2_fy1087,Graph2_fex1087,Graph2_fey1087);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21087 = new TH1F("Graph_Graph21087","v_{2}{2}",100,0,3.1325);
   Graph_Graph21087->SetMinimum(-0.2181706);
   Graph_Graph21087->SetMaximum(0.2622533);
   Graph_Graph21087->SetDirectory(0);
   Graph_Graph21087->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21087->SetLineColor(ci);
   Graph_Graph21087->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21087->GetXaxis()->SetLabelFont(42);
   Graph_Graph21087->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21087->GetXaxis()->SetTitleFont(42);
   Graph_Graph21087->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21087->GetYaxis()->SetLabelFont(42);
   Graph_Graph21087->GetYaxis()->SetTitleFont(42);
   Graph_Graph21087->GetZaxis()->SetLabelFont(42);
   Graph_Graph21087->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21087->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21087);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1088[33] = {
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
   Double_t Graph3_fy1088[33] = {
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
   Double_t Graph3_fex1088[33] = {
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
   Double_t Graph3_fey1088[33] = {
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
   gre = new TGraphErrors(33,Graph3_fx1088,Graph3_fy1088,Graph3_fex1088,Graph3_fey1088);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31088 = new TH1F("Graph_Graph31088","v_{2}{4}",100,0,3.1325);
   Graph_Graph31088->SetMinimum(-0.3525045);
   Graph_Graph31088->SetMaximum(0.8610669);
   Graph_Graph31088->SetDirectory(0);
   Graph_Graph31088->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31088->SetLineColor(ci);
   Graph_Graph31088->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31088->GetXaxis()->SetLabelFont(42);
   Graph_Graph31088->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31088->GetXaxis()->SetTitleFont(42);
   Graph_Graph31088->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31088->GetYaxis()->SetLabelFont(42);
   Graph_Graph31088->GetYaxis()->SetTitleFont(42);
   Graph_Graph31088->GetZaxis()->SetLabelFont(42);
   Graph_Graph31088->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31088->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31088);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph4_fx1089[33] = {
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
   Double_t Graph4_fy1089[33] = {
   0.1439088,
   -0.01722348,
   0.008247853,
   0.005925991,
   -0.009651633,
   0.01254642,
   -0.000603206,
   -0.001738185,
   0.009513119,
   0.009736173,
   0.02568411,
   0.02765312,
   0.03233853,
   0.04656301,
   0.05761556,
   0.06748026,
   0.07930599,
   0.09333376,
   0.09920289,
   0.0999742,
   0.1076503,
   0.1072162,
   0.108081,
   0.09263224,
   0.1279617,
   0.123486,
   0.111113,
   0.140806,
   0.1115209,
   0.1269138,
   0.129247,
   0.0794135,
   0.2702145};
   Double_t Graph4_fex1089[33] = {
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
   Double_t Graph4_fey1089[33] = {
   0.07715722,
   0.02904702,
   0.01765014,
   0.01276068,
   0.00988016,
   0.008103313,
   0.006875653,
   0.006013695,
   0.005338764,
   0.004858712,
   0.00451385,
   0.004240943,
   0.002829066,
   0.00274817,
   0.002798902,
   0.002967183,
   0.003253422,
   0.003669727,
   0.004232683,
   0.004960719,
   0.005914747,
   0.007115419,
   0.008653943,
   0.01059104,
   0.01295853,
   0.01613985,
   0.02004895,
   0.02462106,
   0.03073516,
   0.0392525,
   0.04850354,
   0.04653169,
   0.06600218};
   gre = new TGraphErrors(33,Graph4_fx1089,Graph4_fy1089,Graph4_fex1089,Graph4_fey1089);
   gre->SetName("Graph4");
   gre->SetTitle("v_{2}^{EP}{#Psi_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41089 = new TH1F("Graph_Graph41089","v_{2}^{EP}{#Psi_{2,TPC}}",100,0,3.1325);
   Graph_Graph41089->SetMinimum(-0.08451922);
   Graph_Graph41089->SetMaximum(0.3744654);
   Graph_Graph41089->SetDirectory(0);
   Graph_Graph41089->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41089->SetLineColor(ci);
   Graph_Graph41089->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41089->GetXaxis()->SetLabelFont(42);
   Graph_Graph41089->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41089->GetXaxis()->SetTitleFont(42);
   Graph_Graph41089->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph41089->GetYaxis()->SetLabelFont(42);
   Graph_Graph41089->GetYaxis()->SetTitleFont(42);
   Graph_Graph41089->GetZaxis()->SetLabelFont(42);
   Graph_Graph41089->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41089->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41089);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph5_fx1090[33] = {
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
   Double_t Graph5_fy1090[33] = {
   0.1587362,
   -0.03078831,
   -0.01190318,
   0.0004121074,
   -0.001346891,
   0.002142274,
   -0.008477076,
   -0.007116888,
   0.008037578,
   0.009414913,
   0.02324117,
   0.02779235,
   0.03406861,
   0.04586121,
   0.05736684,
   0.06836558,
   0.08047416,
   0.08956984,
   0.09948208,
   0.0984086,
   0.1060792,
   0.1136206,
   0.1196485,
   0.09609347,
   0.1247226,
   0.1294903,
   0.1276858,
   0.1317606,
   0.1266978,
   0.1481529,
   0.1433888,
   0.1327158,
   0.2827016};
   Double_t Graph5_fex1090[33] = {
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
   Double_t Graph5_fey1090[33] = {
   0.06720239,
   0.02636371,
   0.01581556,
   0.01154886,
   0.008929737,
   0.007358262,
   0.006298783,
   0.005526598,
   0.00493616,
   0.004507826,
   0.004204735,
   0.003969716,
   0.002659567,
   0.002596841,
   0.002657115,
   0.002829457,
   0.00310956,
   0.003523721,
   0.00405684,
   0.004764347,
   0.005710032,
   0.006833052,
   0.008360802,
   0.01023042,
   0.01257734,
   0.01559241,
   0.01948422,
   0.02399618,
   0.0300105,
   0.03766676,
   0.0485517,
   0.04577584,
   0.06505358};
   gre = new TGraphErrors(33,Graph5_fx1090,Graph5_fy1090,Graph5_fex1090,Graph5_fey1090);
   gre->SetName("Graph5");
   gre->SetTitle("v_{2}^{SP}{Q_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph51090 = new TH1F("Graph_Graph51090","v_{2}^{SP}{Q_{2,TPC}}",100,0,3.1325);
   Graph_Graph51090->SetMinimum(-0.09764274);
   Graph_Graph51090->SetMaximum(0.3882459);
   Graph_Graph51090->SetDirectory(0);
   Graph_Graph51090->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51090->SetLineColor(ci);
   Graph_Graph51090->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph51090->GetXaxis()->SetLabelFont(42);
   Graph_Graph51090->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51090->GetXaxis()->SetTitleFont(42);
   Graph_Graph51090->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph51090->GetYaxis()->SetLabelFont(42);
   Graph_Graph51090->GetYaxis()->SetTitleFont(42);
   Graph_Graph51090->GetZaxis()->SetLabelFont(42);
   Graph_Graph51090->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51090->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51090);
   
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

   ci = TColor::GetColor("#2f4c4a");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","v_{2}{2}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#4e6d2c");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph3","v_{2}{4}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#a39e35");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph4","v_{2}^{EP}{#Psi_{2,TPC}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#a85d33");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph5","v_{2}^{SP}{Q_{2,TPC}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#9c272b");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
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
   10-40%, #bar{p}->cd();
  
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
   
   Double_t Graph0_fx1091[33] = {
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
   Double_t Graph0_fy1091[33] = {
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
   Double_t Graph0_fex1091[33] = {
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
   Double_t Graph0_fey1091[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1091,Graph0_fy1091,Graph0_fex1091,Graph0_fey1091);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01091 = new TH1F("Graph_Graph01091","",100,0,3);
   Graph_Graph01091->SetMinimum(0.84);
   Graph_Graph01091->SetMaximum(1.16);
   Graph_Graph01091->SetDirectory(0);
   Graph_Graph01091->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01091->SetLineColor(ci);
   Graph_Graph01091->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01091->GetXaxis()->SetLabelFont(42);
   Graph_Graph01091->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01091->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01091->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01091->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01091->GetXaxis()->SetTitleFont(42);
   Graph_Graph01091->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01091->GetYaxis()->CenterTitle(true);
   Graph_Graph01091->GetYaxis()->SetNdivisions(504);
   Graph_Graph01091->GetYaxis()->SetLabelFont(42);
   Graph_Graph01091->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01091->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01091->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01091->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01091->GetYaxis()->SetTitleFont(42);
   Graph_Graph01091->GetZaxis()->SetLabelFont(42);
   Graph_Graph01091->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01091->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01091);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1092[33] = {
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
   Double_t Graph0_fy1092[33] = {
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
   Double_t Graph0_fex1092[33] = {
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
   Double_t Graph0_fey1092[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1092,Graph0_fy1092,Graph0_fex1092,Graph0_fey1092);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010911092 = new TH1F("Graph_Graph_Graph010911092","",100,0,3);
   Graph_Graph_Graph010911092->SetMinimum(0.84);
   Graph_Graph_Graph010911092->SetMaximum(1.16);
   Graph_Graph_Graph010911092->SetDirectory(0);
   Graph_Graph_Graph010911092->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010911092->SetLineColor(ci);
   Graph_Graph_Graph010911092->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010911092->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010911092->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010911092->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010911092->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010911092->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010911092->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010911092->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010911092->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010911092->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010911092->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010911092->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010911092->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010911092->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010911092->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010911092->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010911092->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010911092->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010911092->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010911092);
   
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
   
   Double_t Graph1_fx1093[33] = {
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
   Double_t Graph1_fy1093[33] = {
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
   Double_t Graph1_fex1093[33] = {
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
   Double_t Graph1_fey1093[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1093,Graph1_fy1093,Graph1_fex1093,Graph1_fey1093);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11093 = new TH1F("Graph_Graph11093","",100,0,3.1325);
   Graph_Graph11093->SetMinimum(0.84);
   Graph_Graph11093->SetMaximum(1.16);
   Graph_Graph11093->SetDirectory(0);
   Graph_Graph11093->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11093->SetLineColor(ci);
   Graph_Graph11093->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11093->GetXaxis()->SetLabelFont(42);
   Graph_Graph11093->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11093->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11093->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11093->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11093->GetXaxis()->SetTitleFont(42);
   Graph_Graph11093->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11093->GetYaxis()->CenterTitle(true);
   Graph_Graph11093->GetYaxis()->SetNdivisions(504);
   Graph_Graph11093->GetYaxis()->SetLabelFont(42);
   Graph_Graph11093->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11093->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11093->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11093->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11093->GetYaxis()->SetTitleFont(42);
   Graph_Graph11093->GetZaxis()->SetLabelFont(42);
   Graph_Graph11093->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11093->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11093);
   
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
   
   Double_t Graph2_fx1094[33] = {
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
   Double_t Graph2_fy1094[33] = {
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
   Double_t Graph2_fex1094[33] = {
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
   Double_t Graph2_fey1094[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1094,Graph2_fy1094,Graph2_fex1094,Graph2_fey1094);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21094 = new TH1F("Graph_Graph21094","",100,0,3.1325);
   Graph_Graph21094->SetMinimum(0.84);
   Graph_Graph21094->SetMaximum(1.16);
   Graph_Graph21094->SetDirectory(0);
   Graph_Graph21094->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21094->SetLineColor(ci);
   Graph_Graph21094->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21094->GetXaxis()->SetLabelFont(42);
   Graph_Graph21094->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21094->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21094->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21094->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21094->GetXaxis()->SetTitleFont(42);
   Graph_Graph21094->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21094->GetYaxis()->CenterTitle(true);
   Graph_Graph21094->GetYaxis()->SetNdivisions(504);
   Graph_Graph21094->GetYaxis()->SetLabelFont(42);
   Graph_Graph21094->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21094->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21094->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21094->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21094->GetYaxis()->SetTitleFont(42);
   Graph_Graph21094->GetZaxis()->SetLabelFont(42);
   Graph_Graph21094->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21094->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21094);
   
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
   
   Double_t Graph3_fx1095[33] = {
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
   Double_t Graph3_fy1095[33] = {
   0.8899022,
   0.5446697,
   0.6726687,
   14.02995,
   6.971597,
   5.753249,
   0.0700492,
   0.2412866,
   1.169643,
   1.024235,
   1.096301,
   0.9890034,
   0.9455311,
   1.013696,
   1.004436,
   0.988144,
   0.9878192,
   1.04562,
   1.001016,
   1.020181,
   1.021227,
   0.9496151,
   0.9093972,
   0.9694312,
   1.033329,
   0.9631481,
   0.8790638,
   1.07633,
   0.8887488,
   0.8695458,
   0.9103972,
   0.6042742,
   0.9780949};
   Double_t Graph3_fex1095[33] = {
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
   Double_t Graph3_fey1095[33] = {
   0.6435854,
   1.061687,
   1.757311,
   442.2571,
   52.06612,
   22.3739,
   0.8005309,
   0.8598085,
   1.020827,
   0.7363671,
   0.2872593,
   0.2138411,
   0.1138178,
   0.08484537,
   0.06874321,
   0.06062608,
   0.05643164,
   0.05889896,
   0.0596888,
   0.07131574,
   0.07908584,
   0.08554441,
   0.09706376,
   0.151948,
   0.1480597,
   0.1712596,
   0.2075414,
   0.2705887,
   0.3227109,
   0.34832,
   0.4547703,
   0.4095846,
   0.3269851};
   gre = new TGraphErrors(33,Graph3_fx1095,Graph3_fy1095,Graph3_fex1095,Graph3_fey1095);
   gre->SetName("Graph3");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31095 = new TH1F("Graph_Graph31095","",100,0,3.1325);
   Graph_Graph31095->SetMinimum(0.84);
   Graph_Graph31095->SetMaximum(1.16);
   Graph_Graph31095->SetDirectory(0);
   Graph_Graph31095->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31095->SetLineColor(ci);
   Graph_Graph31095->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31095->GetXaxis()->SetLabelFont(42);
   Graph_Graph31095->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph31095->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph31095->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph31095->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31095->GetXaxis()->SetTitleFont(42);
   Graph_Graph31095->GetYaxis()->SetTitle("Ratio");
   Graph_Graph31095->GetYaxis()->CenterTitle(true);
   Graph_Graph31095->GetYaxis()->SetNdivisions(504);
   Graph_Graph31095->GetYaxis()->SetLabelFont(42);
   Graph_Graph31095->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph31095->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph31095->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph31095->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph31095->GetYaxis()->SetTitleFont(42);
   Graph_Graph31095->GetZaxis()->SetLabelFont(42);
   Graph_Graph31095->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31095->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31095);
   
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
   
   Double_t Graph4_fx1096[33] = {
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
   Double_t Graph4_fy1096[33] = {
   0.9815918,
   0.9736395,
   0.9707857,
   0.9756758,
   0.9728902,
   0.9823549,
   0.9844273,
   0.9879328,
   0.9882245,
   0.9904391,
   0.9920261,
   0.9939828,
   0.996116,
   0.9984175,
   1.0001,
   1.001108,
   1.00237,
   1.003453,
   1.003833,
   1.004205,
   1.006323,
   1.006339,
   1.006726,
   1.005654,
   1.007172,
   1.00998,
   1.010179,
   1.007186,
   1.009699,
   1.015065,
   1.01001,
   1.009862,
   1.023295};
   Double_t Graph4_fex1096[33] = {
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
   Double_t Graph4_fey1096[33] = {
   0.6321966,
   1.265179,
   1.944195,
   41.09857,
   9.664641,
   5.057393,
   1.090868,
   1.139839,
   0.8970228,
   0.6983033,
   0.2634059,
   0.2076268,
   0.1132725,
   0.08189691,
   0.06686042,
   0.05959484,
   0.05557231,
   0.05653923,
   0.05851609,
   0.06934448,
   0.07713882,
   0.08614272,
   0.09998608,
   0.1519481,
   0.1440088,
   0.1720933,
   0.217758,
   0.2583464,
   0.3379058,
   0.3652034,
   0.4773271,
   0.4896212,
   0.3316676};
   gre = new TGraphErrors(33,Graph4_fx1096,Graph4_fy1096,Graph4_fex1096,Graph4_fey1096);
   gre->SetName("Graph4");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41096 = new TH1F("Graph_Graph41096","",100,0,3.1325);
   Graph_Graph41096->SetMinimum(0.84);
   Graph_Graph41096->SetMaximum(1.16);
   Graph_Graph41096->SetDirectory(0);
   Graph_Graph41096->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41096->SetLineColor(ci);
   Graph_Graph41096->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41096->GetXaxis()->SetLabelFont(42);
   Graph_Graph41096->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph41096->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph41096->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph41096->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41096->GetXaxis()->SetTitleFont(42);
   Graph_Graph41096->GetYaxis()->SetTitle("Ratio");
   Graph_Graph41096->GetYaxis()->CenterTitle(true);
   Graph_Graph41096->GetYaxis()->SetNdivisions(504);
   Graph_Graph41096->GetYaxis()->SetLabelFont(42);
   Graph_Graph41096->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph41096->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph41096->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph41096->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph41096->GetYaxis()->SetTitleFont(42);
   Graph_Graph41096->GetZaxis()->SetLabelFont(42);
   Graph_Graph41096->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41096->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41096);
   
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
   10-40%, #bar{p}->cd();
   10-40%, #bar{p}->Modified();
   10-40%, #bar{p}->cd();
   10-40%, #bar{p}->SetSelected(10-40%, #bar{p});
}
