void kaon_negDFCent10-40()
{
//=========Macro generated from canvas: 10-40%, K-/Canvas
//=========  (Fri Apr 23 19:43:59 2021) by ROOT version 6.22/08
   TCanvas *10-40%, K- = new TCanvas("10-40%, K-", "Canvas",0,0,550,550);
   10-40%, K-->Range(0,0,1,1);
   10-40%, K-->SetFillColor(0);
   10-40%, K-->SetBorderMode(0);
   10-40%, K-->SetBorderSize(2);
   10-40%, K-->SetTickx(1);
   10-40%, K-->SetTicky(1);
   10-40%, K-->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1073[33] = {
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
   Double_t Graph0_fy1073[33] = {
   -0.01325454,
   0.0005934076,
   0.004208006,
   0.005069688,
   0.008514235,
   0.01308832,
   0.0181687,
   0.02175057,
   0.02552139,
   0.02903004,
   0.03218907,
   0.03367471,
   0.03825995,
   0.04137086,
   0.04420682,
   0.04527275,
   0.04792722,
   0.04880314,
   0.0511509,
   0.05447547,
   0.05523696,
   0.05838422,
   0.061325,
   0.06123539,
   0.06844072,
   0.06010127,
   0.06130044,
   0.07866486,
   0.08455745,
   0.06485505,
   0.09911957,
   0.0955662,
   0.1355978};
   Double_t Graph0_fex1073[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1073[33] = {
   0.004495141,
   0.001744122,
   0.00111359,
   0.0008549712,
   0.0007233549,
   0.0006520692,
   0.000615241,
   0.0006009048,
   0.0006030325,
   0.0006181979,
   0.000644191,
   0.0006801019,
   0.0005297416,
   0.0006165222,
   0.0007297602,
   0.0008709302,
   0.001045608,
   0.001260881,
   0.001521553,
   0.001848807,
   0.002245951,
   0.002740021,
   0.003363297,
   0.004124907,
   0.005106815,
   0.006271349,
   0.007759953,
   0.009683795,
   0.01194945,
   0.01498468,
   0.01854245,
   0.01817384,
   0.02613633};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1073,Graph0_fy1073,Graph0_fex1073,Graph0_fey1073);
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
   
   TH1F *Graph_Graph01073 = new TH1F("Graph_Graph01073","",100,0,3);
   Graph_Graph01073->SetMinimum(-0.01);
   Graph_Graph01073->SetMaximum(0.2);
   Graph_Graph01073->SetDirectory(0);
   Graph_Graph01073->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01073->SetLineColor(ci);
   Graph_Graph01073->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01073->GetXaxis()->SetLabelFont(42);
   Graph_Graph01073->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01073->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01073->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01073->GetXaxis()->SetTitleFont(42);
   Graph_Graph01073->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01073->GetYaxis()->SetLabelFont(42);
   Graph_Graph01073->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01073->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01073->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01073->GetYaxis()->SetTitleFont(42);
   Graph_Graph01073->GetZaxis()->SetLabelFont(42);
   Graph_Graph01073->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01073->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01073);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1074[33] = {
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
   Double_t Graph1_fy1074[33] = {
   0.004099745,
   0.001710526,
   0.003683953,
   0.00609899,
   0.007868258,
   0.01258803,
   0.01725282,
   0.01999604,
   0.02468129,
   0.02619906,
   0.03247964,
   0.03323607,
   0.03532128,
   0.04094328,
   0.04454564,
   0.04599014,
   0.05040343,
   0.04776576,
   0.05303152,
   0.05206668,
   0.06318357,
   0.05888819,
   0.06183682,
   0.06235946,
   0.07151354,
   0.05829335,
   0.08425822,
   0.06522844,
   0.03854149,
   0.06419432,
   0.1146084,
   0.0466533,
   -0.02142684};
   Double_t Graph1_fex1074[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1074[33] = {
   0.008699766,
   0.003384756,
   0.002158078,
   0.001655268,
   0.001402176,
   0.001264941,
   0.001194495,
   0.001167477,
   0.001173274,
   0.001203436,
   0.001255863,
   0.001327429,
   0.001036679,
   0.00120841,
   0.0014303,
   0.001708321,
   0.002054562,
   0.002478812,
   0.002996417,
   0.003639839,
   0.00441819,
   0.005409701,
   0.00664479,
   0.008147376,
   0.0100578,
   0.01249566,
   0.01542946,
   0.01914846,
   0.02386869,
   0.02987282,
   0.03701509,
   0.0357214,
   0.05228676};
   gre = new TGraphErrors(33,Graph1_fx1074,Graph1_fy1074,Graph1_fex1074,Graph1_fey1074);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11074 = new TH1F("Graph_Graph11074","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11074->SetMinimum(-0.0962473);
   Graph_Graph11074->SetMaximum(0.1741572);
   Graph_Graph11074->SetDirectory(0);
   Graph_Graph11074->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11074->SetLineColor(ci);
   Graph_Graph11074->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11074->GetXaxis()->SetLabelFont(42);
   Graph_Graph11074->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11074->GetXaxis()->SetTitleFont(42);
   Graph_Graph11074->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11074->GetYaxis()->SetLabelFont(42);
   Graph_Graph11074->GetYaxis()->SetTitleFont(42);
   Graph_Graph11074->GetZaxis()->SetLabelFont(42);
   Graph_Graph11074->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11074->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11074);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1075[33] = {
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
   Double_t Graph2_fy1075[33] = {
   -0.1175105,
   -0.1132789,
   -0.1105883,
   -0.1095815,
   0.005480403,
   0.009740351,
   0.01486168,
   0.01878772,
   0.02385208,
   0.0270623,
   0.03109981,
   0.03270255,
   0.03712985,
   0.040907,
   0.04402901,
   0.0455298,
   0.04732965,
   0.04807394,
   0.04970292,
   0.05196576,
   0.05406478,
   0.0552625,
   0.05702459,
   0.05772782,
   0.05587789,
   0.05796376,
   0.0574844,
   0.06978969,
   0.0711942,
   0.07504613,
   0.08654136,
   0.08330785,
   0.1115485};
   Double_t Graph2_fex1075[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1075[33] = {
   0.00336389,
   0.001312717,
   0.0008401923,
   0.0006468747,
   0.0005442616,
   0.0004913839,
   0.0004638206,
   0.000452859,
   0.0004540705,
   0.0004646364,
   0.0004836334,
   0.0005092156,
   0.0003955794,
   0.0004588477,
   0.0005412399,
   0.0006444192,
   0.0007718514,
   0.0009290967,
   0.001121131,
   0.00135928,
   0.001648758,
   0.002012883,
   0.00246503,
   0.003021429,
   0.00374211,
   0.004601365,
   0.005675733,
   0.007064216,
   0.008770803,
   0.01092899,
   0.01364532,
   0.01324654,
   0.01909682};
   gre = new TGraphErrors(33,Graph2_fx1075,Graph2_fy1075,Graph2_fex1075,Graph2_fey1075);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21075 = new TH1F("Graph_Graph21075","v_{2}{2}",100,0,3.1325);
   Graph_Graph21075->SetMinimum(-0.1460263);
   Graph_Graph21075->SetMaximum(0.1557973);
   Graph_Graph21075->SetDirectory(0);
   Graph_Graph21075->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21075->SetLineColor(ci);
   Graph_Graph21075->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21075->GetXaxis()->SetLabelFont(42);
   Graph_Graph21075->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21075->GetXaxis()->SetTitleFont(42);
   Graph_Graph21075->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21075->GetYaxis()->SetLabelFont(42);
   Graph_Graph21075->GetYaxis()->SetTitleFont(42);
   Graph_Graph21075->GetZaxis()->SetLabelFont(42);
   Graph_Graph21075->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21075->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21075);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1076[33] = {
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
   Double_t Graph3_fy1076[33] = {
   0.0177229,
   0.01614179,
   0.001523633,
   0.00572276,
   0.009292419,
   0.008998207,
   0.01459975,
   0.02185758,
   0.02110965,
   0.03061178,
   0.02758864,
   0.03350133,
   0.03691806,
   0.04300552,
   0.04170674,
   0.04251275,
   0.04870191,
   0.05519323,
   0.05329128,
   0.05262755,
   0.06263937,
   0.05292844,
   0.0841072,
   0.05381502,
   0.08982657,
   0.02873078,
   0.04967911,
   0.1110956,
   0.1130302,
   0.06318084,
   0.1017217,
   0.1533882,
   0.0228709};
   Double_t Graph3_fex1076[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1076[33] = {
   0.02030121,
   0.008012694,
   0.005105846,
   0.003918437,
   0.003242697,
   0.002922964,
   0.002761167,
   0.00268913,
   0.002683052,
   0.002732875,
   0.002842408,
   0.002975868,
   0.002304497,
   0.002657174,
   0.003112138,
   0.003690546,
   0.004396508,
   0.005257905,
   0.006343382,
   0.007628747,
   0.009199416,
   0.01128996,
   0.01367972,
   0.01683256,
   0.02086924,
   0.02528948,
   0.03144458,
   0.0391828,
   0.04743209,
   0.06028497,
   0.07683125,
   0.07501256,
   0.1053436};
   gre = new TGraphErrors(33,Graph3_fx1076,Graph3_fy1076,Graph3_fex1076,Graph3_fey1076);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31076 = new TH1F("Graph_Graph31076","v_{2}{4}",100,0,3.1325);
   Graph_Graph31076->SetMinimum(-0.11356);
   Graph_Graph31076->SetMaximum(0.2594881);
   Graph_Graph31076->SetDirectory(0);
   Graph_Graph31076->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31076->SetLineColor(ci);
   Graph_Graph31076->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31076->GetXaxis()->SetLabelFont(42);
   Graph_Graph31076->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31076->GetXaxis()->SetTitleFont(42);
   Graph_Graph31076->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31076->GetYaxis()->SetLabelFont(42);
   Graph_Graph31076->GetYaxis()->SetTitleFont(42);
   Graph_Graph31076->GetZaxis()->SetLabelFont(42);
   Graph_Graph31076->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31076->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31076);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph4_fx1077[33] = {
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
   Double_t Graph4_fy1077[33] = {
   -0.01122544,
   0.001157748,
   0.002105929,
   0.00507026,
   0.008776937,
   0.01272655,
   0.01894652,
   0.0228991,
   0.02567257,
   0.03030698,
   0.03327504,
   0.03420806,
   0.0393484,
   0.04166758,
   0.04514894,
   0.04631068,
   0.04910418,
   0.04875802,
   0.05170656,
   0.05528965,
   0.05750186,
   0.05754612,
   0.0622227,
   0.06552133,
   0.06361412,
   0.05980559,
   0.06015536,
   0.0803757,
   0.08882794,
   0.07638537,
   0.07528908,
   0.1046013,
   0.1305039};
   Double_t Graph4_fex1077[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1077[33] = {
   0.004609546,
   0.001789558,
   0.001141367,
   0.0008742458,
   0.000739009,
   0.0006659135,
   0.0006282956,
   0.0006141308,
   0.0006174331,
   0.0006339913,
   0.0006624787,
   0.0007008816,
   0.0005484879,
   0.0006408942,
   0.000761012,
   0.0009110201,
   0.001096676,
   0.001325418,
   0.001603095,
   0.001950588,
   0.002373577,
   0.002896704,
   0.003563139,
   0.004372641,
   0.00540437,
   0.006680489,
   0.008251041,
   0.01030623,
   0.01278104,
   0.01593309,
   0.01980168,
   0.01951512,
   0.0280774};
   gre = new TGraphErrors(33,Graph4_fx1077,Graph4_fy1077,Graph4_fex1077,Graph4_fey1077);
   gre->SetName("Graph4");
   gre->SetTitle("v_{2}^{EP}{#Psi_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41077 = new TH1F("Graph_Graph41077","v_{2}^{EP}{#Psi_{2,TPC}}",100,0,3.1325);
   Graph_Graph41077->SetMinimum(-0.03327661);
   Graph_Graph41077->SetMaximum(0.1760229);
   Graph_Graph41077->SetDirectory(0);
   Graph_Graph41077->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41077->SetLineColor(ci);
   Graph_Graph41077->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41077->GetXaxis()->SetLabelFont(42);
   Graph_Graph41077->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41077->GetXaxis()->SetTitleFont(42);
   Graph_Graph41077->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph41077->GetYaxis()->SetLabelFont(42);
   Graph_Graph41077->GetYaxis()->SetTitleFont(42);
   Graph_Graph41077->GetZaxis()->SetLabelFont(42);
   Graph_Graph41077->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41077->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41077);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph5_fx1078[33] = {
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
   Double_t Graph5_fy1078[33] = {
   -0.01333257,
   0.0005994149,
   0.004234188,
   0.005107119,
   0.008580175,
   0.01319419,
   0.01832658,
   0.02194765,
   0.02576188,
   0.02931427,
   0.03251637,
   0.03402394,
   0.03867876,
   0.04184457,
   0.04472149,
   0.04583036,
   0.04852705,
   0.0494365,
   0.05184234,
   0.0552094,
   0.05602195,
   0.05923212,
   0.06225337,
   0.06220641,
   0.06949049,
   0.06110564,
   0.06230394,
   0.08000949,
   0.08594204,
   0.06617277,
   0.100762,
   0.0974482,
   0.1378757};
   Double_t Graph5_fex1078[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph5_fey1078[33] = {
   0.004433357,
   0.001719464,
   0.001097396,
   0.0008418824,
   0.0007124722,
   0.0006426179,
   0.0006072948,
   0.0005944395,
   0.0005980732,
   0.0006150973,
   0.0006431904,
   0.000681433,
   0.0005338121,
   0.0006245322,
   0.0007427778,
   0.0008903717,
   0.001072709,
   0.001297773,
   0.00157101,
   0.001912855,
   0.002329622,
   0.002848824,
   0.003504543,
   0.00430795,
   0.005346883,
   0.006587843,
   0.008164884,
   0.01019911,
   0.01263533,
   0.01587699,
   0.01963816,
   0.01934306,
   0.02798574};
   gre = new TGraphErrors(33,Graph5_fx1078,Graph5_fy1078,Graph5_fex1078,Graph5_fey1078);
   gre->SetName("Graph5");
   gre->SetTitle("v_{2}^{SP}{Q_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph51078 = new TH1F("Graph_Graph51078","v_{2}^{SP}{Q_{2,TPC}}",100,0,3.1325);
   Graph_Graph51078->SetMinimum(-0.03612866);
   Graph_Graph51078->SetMaximum(0.1842242);
   Graph_Graph51078->SetDirectory(0);
   Graph_Graph51078->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51078->SetLineColor(ci);
   Graph_Graph51078->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph51078->GetXaxis()->SetLabelFont(42);
   Graph_Graph51078->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51078->GetXaxis()->SetTitleFont(42);
   Graph_Graph51078->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph51078->GetYaxis()->SetLabelFont(42);
   Graph_Graph51078->GetYaxis()->SetTitleFont(42);
   Graph_Graph51078->GetZaxis()->SetLabelFont(42);
   Graph_Graph51078->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51078->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51078);
   
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
   pt_LaTex = pt->AddText("10-40%, K-");
   pt->Draw();
   padUp->Modified();
   10-40%, K-->cd();
  
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
   
   Double_t Graph0_fx1079[33] = {
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
   Double_t Graph0_fy1079[33] = {
   0.3093087,
   2.882548,
   0.8754631,
   1.203031,
   0.9241298,
   0.961776,
   0.9495902,
   0.9193344,
   0.9670826,
   0.9024809,
   1.009027,
   0.9869739,
   0.9231922,
   0.9896647,
   1.007664,
   1.015846,
   1.051666,
   0.9787434,
   1.036766,
   0.9557822,
   1.143864,
   1.008632,
   1.008346,
   1.018357,
   1.044897,
   0.9699187,
   1.374512,
   0.8291942,
   0.4558024,
   0.9898123,
   1.156264,
   0.4881778,
   0.1580176};
   Double_t Graph0_fex1079[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1079[33] = {
   0.6646907,
   10.21344,
   0.5627528,
   0.3844033,
   0.1824437,
   0.1078727,
   0.07318706,
   0.05938153,
   0.05133808,
   0.04569302,
   0.04393129,
   0.04417239,
   0.02995939,
   0.03272141,
   0.03638038,
   0.04249413,
   0.04862216,
   0.05673852,
   0.06620209,
   0.07427378,
   0.09252539,
   0.104048,
   0.1216502,
   0.1496931,
   0.166358,
   0.2312348,
   0.3059891,
   0.2639542,
   0.2895337,
   0.5142588,
   0.4315598,
   0.3851433,
   0.3868028};
   gre = new TGraphErrors(33,Graph0_fx1079,Graph0_fy1079,Graph0_fex1079,Graph0_fey1079);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01079 = new TH1F("Graph_Graph01079","",100,0,3);
   Graph_Graph01079->SetMinimum(0.84);
   Graph_Graph01079->SetMaximum(1.16);
   Graph_Graph01079->SetDirectory(0);
   Graph_Graph01079->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01079->SetLineColor(ci);
   Graph_Graph01079->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01079->GetXaxis()->SetLabelFont(42);
   Graph_Graph01079->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01079->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01079->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01079->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01079->GetXaxis()->SetTitleFont(42);
   Graph_Graph01079->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01079->GetYaxis()->CenterTitle(true);
   Graph_Graph01079->GetYaxis()->SetNdivisions(504);
   Graph_Graph01079->GetYaxis()->SetLabelFont(42);
   Graph_Graph01079->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01079->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01079->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01079->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01079->GetYaxis()->SetTitleFont(42);
   Graph_Graph01079->GetZaxis()->SetLabelFont(42);
   Graph_Graph01079->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01079->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01079);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1080[33] = {
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
   Double_t Graph0_fy1080[33] = {
   0.3093087,
   2.882548,
   0.8754631,
   1.203031,
   0.9241298,
   0.961776,
   0.9495902,
   0.9193344,
   0.9670826,
   0.9024809,
   1.009027,
   0.9869739,
   0.9231922,
   0.9896647,
   1.007664,
   1.015846,
   1.051666,
   0.9787434,
   1.036766,
   0.9557822,
   1.143864,
   1.008632,
   1.008346,
   1.018357,
   1.044897,
   0.9699187,
   1.374512,
   0.8291942,
   0.4558024,
   0.9898123,
   1.156264,
   0.4881778,
   0.1580176};
   Double_t Graph0_fex1080[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1080[33] = {
   0.6646907,
   10.21344,
   0.5627528,
   0.3844033,
   0.1824437,
   0.1078727,
   0.07318706,
   0.05938153,
   0.05133808,
   0.04569302,
   0.04393129,
   0.04417239,
   0.02995939,
   0.03272141,
   0.03638038,
   0.04249413,
   0.04862216,
   0.05673852,
   0.06620209,
   0.07427378,
   0.09252539,
   0.104048,
   0.1216502,
   0.1496931,
   0.166358,
   0.2312348,
   0.3059891,
   0.2639542,
   0.2895337,
   0.5142588,
   0.4315598,
   0.3851433,
   0.3868028};
   gre = new TGraphErrors(33,Graph0_fx1080,Graph0_fy1080,Graph0_fex1080,Graph0_fey1080);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010791080 = new TH1F("Graph_Graph_Graph010791080","",100,0,3);
   Graph_Graph_Graph010791080->SetMinimum(0.84);
   Graph_Graph_Graph010791080->SetMaximum(1.16);
   Graph_Graph_Graph010791080->SetDirectory(0);
   Graph_Graph_Graph010791080->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010791080->SetLineColor(ci);
   Graph_Graph_Graph010791080->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010791080->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010791080->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010791080->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010791080->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010791080->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010791080->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010791080->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010791080->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010791080->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010791080->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010791080->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010791080->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010791080->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010791080->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010791080->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010791080->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010791080->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010791080->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010791080);
   
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
   
   Double_t Graph1_fx1081[33] = {
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
   Double_t Graph1_fy1081[33] = {
   8.865677,
   190.8956,
   26.28045,
   21.61505,
   0.6436753,
   0.7442017,
   0.8179827,
   0.8637806,
   0.9345918,
   0.9322172,
   0.9661607,
   0.9711308,
   0.9704626,
   0.9887877,
   0.9959778,
   1.005678,
   0.9875318,
   0.9850582,
   0.971692,
   0.9539295,
   0.9787791,
   0.9465314,
   0.929875,
   0.9427198,
   0.8164421,
   0.9644348,
   0.9377485,
   0.8871775,
   0.8419624,
   1.157136,
   0.8731007,
   0.8717292,
   0.8226425};
   Double_t Graph1_fex1081[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1081[33] = {
   3.017395,
   561.0778,
   6.957618,
   3.647475,
   0.08412344,
   0.05276558,
   0.03766891,
   0.03166977,
   0.02835854,
   0.0255002,
   0.02448685,
   0.02476569,
   0.01695435,
   0.01844287,
   0.02049931,
   0.02401881,
   0.02689848,
   0.03178263,
   0.03627481,
   0.04087464,
   0.04974725,
   0.05623077,
   0.06493471,
   0.08041883,
   0.08185842,
   0.1264473,
   0.150547,
   0.1413925,
   0.1578489,
   0.3160312,
   0.2136098,
   0.2160903,
   0.212077};
   gre = new TGraphErrors(33,Graph1_fx1081,Graph1_fy1081,Graph1_fex1081,Graph1_fey1081);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11081 = new TH1F("Graph_Graph11081","",100,0,3.1325);
   Graph_Graph11081->SetMinimum(0.84);
   Graph_Graph11081->SetMaximum(1.16);
   Graph_Graph11081->SetDirectory(0);
   Graph_Graph11081->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11081->SetLineColor(ci);
   Graph_Graph11081->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11081->GetXaxis()->SetLabelFont(42);
   Graph_Graph11081->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11081->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11081->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11081->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11081->GetXaxis()->SetTitleFont(42);
   Graph_Graph11081->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11081->GetYaxis()->CenterTitle(true);
   Graph_Graph11081->GetYaxis()->SetNdivisions(504);
   Graph_Graph11081->GetYaxis()->SetLabelFont(42);
   Graph_Graph11081->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11081->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11081->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11081->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11081->GetYaxis()->SetTitleFont(42);
   Graph_Graph11081->GetZaxis()->SetLabelFont(42);
   Graph_Graph11081->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11081->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11081);
   
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
   
   Double_t Graph2_fx1082[33] = {
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
   Double_t Graph2_fy1082[33] = {
   1.337119,
   27.20185,
   0.3620797,
   1.128819,
   1.091398,
   0.687499,
   0.8035659,
   1.00492,
   0.8271356,
   1.054486,
   0.8570811,
   0.994851,
   0.9649272,
   1.039512,
   0.9434459,
   0.9390361,
   1.016164,
   1.130936,
   1.041844,
   0.9660779,
   1.134012,
   0.9065538,
   1.371499,
   0.8788222,
   1.312473,
   0.4780394,
   0.8104201,
   1.412264,
   1.336726,
   0.9741855,
   1.026253,
   1.605047,
   0.1686672};
   Double_t Graph2_fex1082[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1082[33] = {
   1.597361,
   81.08294,
   1.217142,
   0.7960135,
   0.3919807,
   0.2259375,
   0.1543906,
   0.1267138,
   0.1069308,
   0.09678069,
   0.08995401,
   0.09062632,
   0.06169655,
   0.0660699,
   0.07210165,
   0.08349563,
   0.09437382,
   0.1116289,
   0.1278268,
   0.143827,
   0.1728096,
   0.1979986,
   0.2354096,
   0.2811852,
   0.3202648,
   0.4237274,
   0.5231166,
   0.5275662,
   0.5918984,
   0.9563976,
   0.7985579,
   0.8421865,
   0.7775625};
   gre = new TGraphErrors(33,Graph2_fx1082,Graph2_fy1082,Graph2_fex1082,Graph2_fey1082);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21082 = new TH1F("Graph_Graph21082","",100,0,3.1325);
   Graph_Graph21082->SetMinimum(0.84);
   Graph_Graph21082->SetMaximum(1.16);
   Graph_Graph21082->SetDirectory(0);
   Graph_Graph21082->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21082->SetLineColor(ci);
   Graph_Graph21082->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21082->GetXaxis()->SetLabelFont(42);
   Graph_Graph21082->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21082->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21082->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21082->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21082->GetXaxis()->SetTitleFont(42);
   Graph_Graph21082->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21082->GetYaxis()->CenterTitle(true);
   Graph_Graph21082->GetYaxis()->SetNdivisions(504);
   Graph_Graph21082->GetYaxis()->SetLabelFont(42);
   Graph_Graph21082->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21082->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21082->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21082->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21082->GetYaxis()->SetTitleFont(42);
   Graph_Graph21082->GetZaxis()->SetLabelFont(42);
   Graph_Graph21082->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21082->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21082);
   
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
   
   Double_t Graph3_fx1083[33] = {
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
   Double_t Graph3_fy1083[33] = {
   0.8469126,
   1.951016,
   0.5004577,
   1.000113,
   1.030855,
   0.9723594,
   1.042811,
   1.052805,
   1.005924,
   1.043987,
   1.033737,
   1.015838,
   1.028449,
   1.007172,
   1.021312,
   1.022926,
   1.024557,
   0.9990754,
   1.010863,
   1.014946,
   1.041003,
   0.985645,
   1.014638,
   1.069991,
   0.9294777,
   0.9950803,
   0.9813201,
   1.021749,
   1.050504,
   1.177786,
   0.7595784,
   1.094543,
   0.9624335};
   Double_t Graph3_fex1083[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1083[33] = {
   0.4510444,
   6.479003,
   0.3018437,
   0.2412149,
   0.1233041,
   0.07025241,
   0.04942493,
   0.04053661,
   0.03391506,
   0.03116411,
   0.02918152,
   0.02922504,
   0.0202061,
   0.02156991,
   0.02409561,
   0.02814557,
   0.03198778,
   0.03746799,
   0.04343273,
   0.0496852,
   0.06031673,
   0.06783304,
   0.08045156,
   0.1014591,
   0.1050971,
   0.1521068,
   0.1831634,
   0.1816182,
   0.2118626,
   0.3666163,
   0.2451559,
   0.2915921,
   0.2780083};
   gre = new TGraphErrors(33,Graph3_fx1083,Graph3_fy1083,Graph3_fex1083,Graph3_fey1083);
   gre->SetName("Graph3");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31083 = new TH1F("Graph_Graph31083","",100,0,3.1325);
   Graph_Graph31083->SetMinimum(0.84);
   Graph_Graph31083->SetMaximum(1.16);
   Graph_Graph31083->SetDirectory(0);
   Graph_Graph31083->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31083->SetLineColor(ci);
   Graph_Graph31083->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31083->GetXaxis()->SetLabelFont(42);
   Graph_Graph31083->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph31083->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph31083->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph31083->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31083->GetXaxis()->SetTitleFont(42);
   Graph_Graph31083->GetYaxis()->SetTitle("Ratio");
   Graph_Graph31083->GetYaxis()->CenterTitle(true);
   Graph_Graph31083->GetYaxis()->SetNdivisions(504);
   Graph_Graph31083->GetYaxis()->SetLabelFont(42);
   Graph_Graph31083->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph31083->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph31083->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph31083->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph31083->GetYaxis()->SetTitleFont(42);
   Graph_Graph31083->GetZaxis()->SetLabelFont(42);
   Graph_Graph31083->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31083->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31083);
   
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
   
   Double_t Graph4_fx1084[33] = {
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
   Double_t Graph4_fy1084[33] = {
   1.005887,
   1.010124,
   1.006222,
   1.007383,
   1.007745,
   1.008089,
   1.00869,
   1.009061,
   1.009423,
   1.009791,
   1.010168,
   1.01037,
   1.010946,
   1.01145,
   1.011642,
   1.012317,
   1.012516,
   1.012978,
   1.013518,
   1.013473,
   1.014211,
   1.014523,
   1.015139,
   1.015857,
   1.015338,
   1.016711,
   1.01637,
   1.017093,
   1.016374,
   1.020318,
   1.016571,
   1.019693,
   1.016799};
   Double_t Graph4_fex1084[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1084[33] = {
   0.4777548,
   4.148569,
   0.3727152,
   0.2375686,
   0.1197185,
   0.07023595,
   0.04779068,
   0.03903935,
   0.0334371,
   0.03018856,
   0.02842466,
   0.02873807,
   0.01976342,
   0.02133265,
   0.02368988,
   0.02767733,
   0.03144689,
   0.03731051,
   0.04303758,
   0.04915336,
   0.05898575,
   0.06817505,
   0.07978338,
   0.09814189,
   0.1088262,
   0.152545,
   0.1851877,
   0.1802398,
   0.2072656,
   0.339861,
   0.2746253,
   0.2803049,
   0.2846169};
   gre = new TGraphErrors(33,Graph4_fx1084,Graph4_fy1084,Graph4_fex1084,Graph4_fey1084);
   gre->SetName("Graph4");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41084 = new TH1F("Graph_Graph41084","",100,0,3.1325);
   Graph_Graph41084->SetMinimum(0.84);
   Graph_Graph41084->SetMaximum(1.16);
   Graph_Graph41084->SetDirectory(0);
   Graph_Graph41084->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41084->SetLineColor(ci);
   Graph_Graph41084->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41084->GetXaxis()->SetLabelFont(42);
   Graph_Graph41084->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph41084->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph41084->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph41084->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41084->GetXaxis()->SetTitleFont(42);
   Graph_Graph41084->GetYaxis()->SetTitle("Ratio");
   Graph_Graph41084->GetYaxis()->CenterTitle(true);
   Graph_Graph41084->GetYaxis()->SetNdivisions(504);
   Graph_Graph41084->GetYaxis()->SetLabelFont(42);
   Graph_Graph41084->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph41084->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph41084->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph41084->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph41084->GetYaxis()->SetTitleFont(42);
   Graph_Graph41084->GetZaxis()->SetLabelFont(42);
   Graph_Graph41084->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41084->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41084);
   
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
   10-40%, K-->cd();
   10-40%, K-->Modified();
   10-40%, K-->cd();
   10-40%, K-->SetSelected(10-40%, K-);
}
