void kaon_negDFCent10_40()
{
//=========Macro generated from canvas: c1_n8/Canvas
//=========  (Fri Apr 23 20:00:15 2021) by ROOT version 6.22/08
   TCanvas *c1_n8 = new TCanvas("c1_n8", "Canvas",0,0,550,550);
   c1_n8->Range(0,0,1,1);
   c1_n8->SetFillColor(0);
   c1_n8->SetBorderMode(0);
   c1_n8->SetBorderSize(2);
   c1_n8->SetTickx(1);
   c1_n8->SetTicky(1);
   c1_n8->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1049[33] = {
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
   Double_t Graph0_fy1049[33] = {
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
   Double_t Graph0_fex1049[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1049[33] = {
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
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1049,Graph0_fy1049,Graph0_fex1049,Graph0_fey1049);
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
   
   TH1F *Graph_Graph01049 = new TH1F("Graph_Graph01049","",100,0,3);
   Graph_Graph01049->SetMinimum(-0.01);
   Graph_Graph01049->SetMaximum(0.2);
   Graph_Graph01049->SetDirectory(0);
   Graph_Graph01049->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01049->SetLineColor(ci);
   Graph_Graph01049->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01049->GetXaxis()->SetLabelFont(42);
   Graph_Graph01049->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01049->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01049->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01049->GetXaxis()->SetTitleFont(42);
   Graph_Graph01049->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01049->GetYaxis()->SetLabelFont(42);
   Graph_Graph01049->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01049->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01049->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01049->GetYaxis()->SetTitleFont(42);
   Graph_Graph01049->GetZaxis()->SetLabelFont(42);
   Graph_Graph01049->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01049->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01049);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1050[33] = {
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
   Double_t Graph1_fy1050[33] = {
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
   Double_t Graph1_fex1050[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1050[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1050,Graph1_fy1050,Graph1_fex1050,Graph1_fey1050);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11050 = new TH1F("Graph_Graph11050","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11050->SetMinimum(-0.0962473);
   Graph_Graph11050->SetMaximum(0.1741572);
   Graph_Graph11050->SetDirectory(0);
   Graph_Graph11050->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11050->SetLineColor(ci);
   Graph_Graph11050->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11050->GetXaxis()->SetLabelFont(42);
   Graph_Graph11050->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11050->GetXaxis()->SetTitleFont(42);
   Graph_Graph11050->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11050->GetYaxis()->SetLabelFont(42);
   Graph_Graph11050->GetYaxis()->SetTitleFont(42);
   Graph_Graph11050->GetZaxis()->SetLabelFont(42);
   Graph_Graph11050->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11050->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11050);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1051[33] = {
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
   Double_t Graph2_fy1051[33] = {
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
   Double_t Graph2_fex1051[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1051[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1051,Graph2_fy1051,Graph2_fex1051,Graph2_fey1051);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21051 = new TH1F("Graph_Graph21051","v_{2}{2}",100,0,3.1325);
   Graph_Graph21051->SetMinimum(-0.1460263);
   Graph_Graph21051->SetMaximum(0.1557973);
   Graph_Graph21051->SetDirectory(0);
   Graph_Graph21051->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21051->SetLineColor(ci);
   Graph_Graph21051->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21051->GetXaxis()->SetLabelFont(42);
   Graph_Graph21051->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21051->GetXaxis()->SetTitleFont(42);
   Graph_Graph21051->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21051->GetYaxis()->SetLabelFont(42);
   Graph_Graph21051->GetYaxis()->SetTitleFont(42);
   Graph_Graph21051->GetZaxis()->SetLabelFont(42);
   Graph_Graph21051->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21051->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21051);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1052[33] = {
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
   Double_t Graph3_fy1052[33] = {
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
   Double_t Graph3_fex1052[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1052[33] = {
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
   gre = new TGraphErrors(33,Graph3_fx1052,Graph3_fy1052,Graph3_fex1052,Graph3_fey1052);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31052 = new TH1F("Graph_Graph31052","v_{2}{4}",100,0,3.1325);
   Graph_Graph31052->SetMinimum(-0.11356);
   Graph_Graph31052->SetMaximum(0.2594881);
   Graph_Graph31052->SetDirectory(0);
   Graph_Graph31052->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31052->SetLineColor(ci);
   Graph_Graph31052->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31052->GetXaxis()->SetLabelFont(42);
   Graph_Graph31052->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31052->GetXaxis()->SetTitleFont(42);
   Graph_Graph31052->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31052->GetYaxis()->SetLabelFont(42);
   Graph_Graph31052->GetYaxis()->SetTitleFont(42);
   Graph_Graph31052->GetZaxis()->SetLabelFont(42);
   Graph_Graph31052->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31052->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31052);
   
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
   pt_LaTex = pt->AddText("10-40%, K-");
   pt->Draw();
   padUp->Modified();
   c1_n8->cd();
  
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
   
   Double_t Graph0_fx1053[33] = {
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
   Double_t Graph0_fy1053[33] = {
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
   Double_t Graph0_fex1053[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1053[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1053,Graph0_fy1053,Graph0_fex1053,Graph0_fey1053);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01053 = new TH1F("Graph_Graph01053","",100,0,3);
   Graph_Graph01053->SetMinimum(0.84);
   Graph_Graph01053->SetMaximum(1.16);
   Graph_Graph01053->SetDirectory(0);
   Graph_Graph01053->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01053->SetLineColor(ci);
   Graph_Graph01053->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01053->GetXaxis()->SetLabelFont(42);
   Graph_Graph01053->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01053->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01053->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01053->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01053->GetXaxis()->SetTitleFont(42);
   Graph_Graph01053->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01053->GetYaxis()->CenterTitle(true);
   Graph_Graph01053->GetYaxis()->SetNdivisions(504);
   Graph_Graph01053->GetYaxis()->SetLabelFont(42);
   Graph_Graph01053->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01053->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01053->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01053->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01053->GetYaxis()->SetTitleFont(42);
   Graph_Graph01053->GetZaxis()->SetLabelFont(42);
   Graph_Graph01053->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01053->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01053);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1054[33] = {
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
   Double_t Graph0_fy1054[33] = {
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
   Double_t Graph0_fex1054[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1054[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1054,Graph0_fy1054,Graph0_fex1054,Graph0_fey1054);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010531054 = new TH1F("Graph_Graph_Graph010531054","",100,0,3);
   Graph_Graph_Graph010531054->SetMinimum(0.84);
   Graph_Graph_Graph010531054->SetMaximum(1.16);
   Graph_Graph_Graph010531054->SetDirectory(0);
   Graph_Graph_Graph010531054->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010531054->SetLineColor(ci);
   Graph_Graph_Graph010531054->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010531054->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010531054->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010531054->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010531054->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010531054->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010531054->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010531054->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010531054->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010531054->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010531054->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010531054->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010531054->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010531054->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010531054->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010531054->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010531054->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010531054->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010531054->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010531054);
   
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
   
   Double_t Graph1_fx1055[33] = {
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
   Double_t Graph1_fy1055[33] = {
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
   Double_t Graph1_fex1055[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1055[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1055,Graph1_fy1055,Graph1_fex1055,Graph1_fey1055);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11055 = new TH1F("Graph_Graph11055","",100,0,3.1325);
   Graph_Graph11055->SetMinimum(0.84);
   Graph_Graph11055->SetMaximum(1.16);
   Graph_Graph11055->SetDirectory(0);
   Graph_Graph11055->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11055->SetLineColor(ci);
   Graph_Graph11055->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11055->GetXaxis()->SetLabelFont(42);
   Graph_Graph11055->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11055->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11055->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11055->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11055->GetXaxis()->SetTitleFont(42);
   Graph_Graph11055->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11055->GetYaxis()->CenterTitle(true);
   Graph_Graph11055->GetYaxis()->SetNdivisions(504);
   Graph_Graph11055->GetYaxis()->SetLabelFont(42);
   Graph_Graph11055->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11055->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11055->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11055->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11055->GetYaxis()->SetTitleFont(42);
   Graph_Graph11055->GetZaxis()->SetLabelFont(42);
   Graph_Graph11055->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11055->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11055);
   
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
   
   Double_t Graph2_fx1056[33] = {
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
   Double_t Graph2_fy1056[33] = {
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
   Double_t Graph2_fex1056[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1056[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1056,Graph2_fy1056,Graph2_fex1056,Graph2_fey1056);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21056 = new TH1F("Graph_Graph21056","",100,0,3.1325);
   Graph_Graph21056->SetMinimum(0.84);
   Graph_Graph21056->SetMaximum(1.16);
   Graph_Graph21056->SetDirectory(0);
   Graph_Graph21056->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21056->SetLineColor(ci);
   Graph_Graph21056->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21056->GetXaxis()->SetLabelFont(42);
   Graph_Graph21056->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21056->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21056->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21056->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21056->GetXaxis()->SetTitleFont(42);
   Graph_Graph21056->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21056->GetYaxis()->CenterTitle(true);
   Graph_Graph21056->GetYaxis()->SetNdivisions(504);
   Graph_Graph21056->GetYaxis()->SetLabelFont(42);
   Graph_Graph21056->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21056->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21056->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21056->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21056->GetYaxis()->SetTitleFont(42);
   Graph_Graph21056->GetZaxis()->SetLabelFont(42);
   Graph_Graph21056->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21056->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21056);
   
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
   c1_n8->cd();
   c1_n8->Modified();
   c1_n8->cd();
   c1_n8->SetSelected(c1_n8);
}
