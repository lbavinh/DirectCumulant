void v2v3_AntiparticlesPads_cent060()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Sun Oct  4 12:44:07 2020) by ROOT version 6.18/02

   gStyle->SetCanvasPreferGL(kTRUE);

   TCanvas *canvas = new TCanvas("canvas", "plot",460,88,460,680);
   canvas->Range(0,0,1,1);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetTickx(1);
   canvas->SetTicky(1);
   canvas->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pd_left
   TPad *pd_left = new TPad("pd_left", "left",0,0.05,0.08,0.95);
   pd_left->Draw();
   pd_left->cd();
   pd_left->Range(0,0,1,1);
   pd_left->SetFillColor(0);
   pd_left->SetBorderMode(0);
   pd_left->SetBorderSize(2);
   pd_left->SetTickx(1);
   pd_left->SetTicky(1);
   pd_left->SetFrameBorderMode(0);
   TLatex *   tex = new TLatex(0.6,0.475,"#font[42]{ v_{n} }");
   tex->SetTextSize(0.7);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_left->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_up
   TPad *pd_up = new TPad("pd_up", "up",0.1,0.95,1,1);
   pd_up->Draw();
   pd_up->cd();
   pd_up->Range(0,0,1,1);
   pd_up->SetFillColor(0);
   pd_up->SetBorderMode(0);
   pd_up->SetBorderSize(2);
   pd_up->SetTickx(1);
   pd_up->SetTicky(1);
   pd_up->SetFrameBorderMode(0);
      tex = new TLatex(0.275,0.4,"#font[42]{ Antiparticles }");
   tex->SetTextSize(0.7);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_up->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_down
   TPad *pd_down = new TPad("pd_down", "down",0.1,0,1,0.04);
   pd_down->Draw();
   pd_down->cd();
   pd_down->Range(0,0,1,1);
   pd_down->SetFillColor(0);
   pd_down->SetBorderMode(0);
   pd_down->SetBorderSize(2);
   pd_down->SetTickx(1);
   pd_down->SetTicky(1);
   pd_down->SetFrameBorderMode(0);
      tex = new TLatex(0.325,0.45,"#font[42]{ p_{T} [GeV/c] }");
   tex->SetTextSize(0.7);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_down->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent00
   TPad *pd_cent00 = new TPad("pd_cent00", "pd_cent00",0.1,0.05,0.5,0.2);
   pd_cent00->Draw();
   pd_cent00->cd();
   pd_cent00->Range(0,0,1,1);
   pd_cent00->SetFillColor(0);
   pd_cent00->SetBorderMode(0);
   pd_cent00->SetBorderSize(2);
   pd_cent00->SetTickx(1);
   pd_cent00->SetTicky(1);
   pd_cent00->SetLeftMargin(0.15);
   pd_cent00->SetRightMargin(0);
   pd_cent00->SetTopMargin(0);
   pd_cent00->SetBottomMargin(0.15);
   pd_cent00->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1073[14] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5,
   1.7,
   1.9,
   2.1,
   2.3,
   2.5,
   2.7,
   2.9};
   Double_t Graph0_fy1073[14] = {
   0.02298309,
   0.0434241,
   0.06317698,
   0.08080113,
   0.09525049,
   0.1081445,
   0.117327,
   0.1245693,
   0.1307298,
   0.1356605,
   0.1374499,
   0.141104,
   0.1391658,
   0.1395687};
   Double_t Graph0_fex1073[14] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1073[14] = {
   6.024512e-05,
   0.000220157,
   0.0004128988,
   0.0005098657,
   0.0006472391,
   0.0008431012,
   0.0009466611,
   0.001033403,
   0.00118958,
   0.001231592,
   0.00161506,
   0.001116802,
   0.001430561,
   0.001299229};
   TGraphErrors *gre = new TGraphErrors(14,Graph0_fx1073,Graph0_fy1073,Graph0_fex1073,Graph0_fey1073);
   gre->SetName("Graph0");
   gre->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1314;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01073 = new TH1F("Graph_Graph01073","",100,-0.085,3.27);
   Graph_Graph01073->SetMinimum(-0.02);
   Graph_Graph01073->SetMaximum(0.32);
   Graph_Graph01073->SetDirectory(0);
   Graph_Graph01073->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01073->SetLineColor(ci);
   Graph_Graph01073->GetXaxis()->SetNdivisions(505);
   Graph_Graph01073->GetXaxis()->SetLabelFont(42);
   Graph_Graph01073->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01073->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01073->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01073->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01073->GetXaxis()->SetTitleFont(42);
   Graph_Graph01073->GetYaxis()->SetNdivisions(505);
   Graph_Graph01073->GetYaxis()->SetLabelFont(42);
   Graph_Graph01073->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01073->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01073->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01073->GetYaxis()->SetTitleFont(42);
   Graph_Graph01073->GetZaxis()->SetLabelFont(42);
   Graph_Graph01073->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01073->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01073->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01073->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01073);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1074[14] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5,
   1.7,
   1.9,
   2.1,
   2.3,
   2.5,
   2.7,
   2.9};
   Double_t Graph1_fy1074[14] = {
   0.02298309,
   0.0434241,
   0.06317698,
   0.08080113,
   0.09525049,
   0.1081445,
   0.117327,
   0.1245693,
   0.1307298,
   0.1356605,
   0.1374499,
   0.141104,
   0.1391658,
   0.1395687};
   Double_t Graph1_fex1074[14] = {
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1074[14] = {
   0.0001033765,
   9.570197e-05,
   0.0001105521,
   0.0001367649,
   0.000174429,
   0.0002241378,
   0.0002917706,
   0.0003866606,
   0.0005201242,
   0.0007202174,
   0.001023537,
   0.001446876,
   0.002035709,
   0.002851258};
   gre = new TGraphErrors(14,Graph1_fx1074,Graph1_fy1074,Graph1_fex1074,Graph1_fey1074);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1075[7] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph2_fy1075[7] = {
   0.01154779,
   0.02763772,
   0.04769057,
   0.0659586,
   0.08166917,
   0.09554278,
   0.108699};
   Double_t Graph2_fex1075[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1075[7] = {
   6.024512e-05,
   0.000220157,
   0.0004128988,
   0.0005098657,
   0.0006472391,
   0.0008431012,
   0.0009466611};
   gre = new TGraphErrors(7,Graph2_fx1075,Graph2_fy1075,Graph2_fex1075,Graph2_fey1075);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1315;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1076[7] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph3_fy1076[7] = {
   0.01154779,
   0.02763772,
   0.04769057,
   0.0659586,
   0.08166917,
   0.09554278,
   0.108699};
   Double_t Graph3_fex1076[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1076[7] = {
   0.0006958807,
   0.0003451635,
   0.000297654,
   0.0003317867,
   0.0004233873,
   0.0005648229,
   0.0007639167};
   gre = new TGraphErrors(7,Graph3_fx1076,Graph3_fy1076,Graph3_fex1076,Graph3_fey1076);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1077[12] = {
   0.6,
   0.8,
   1,
   1.2,
   1.4,
   1.6,
   1.8,
   2,
   2.2,
   2.4,
   2.7,
   3.05};
   Double_t Graph4_fy1077[12] = {
   0.01790223,
   0.03541777,
   0.05561216,
   0.07541353,
   0.09431802,
   0.1119878,
   0.1265426,
   0.1392145,
   0.1498842,
   0.1583816,
   0.1669469,
   0.177448};
   Double_t Graph4_fex1077[12] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1077[12] = {
   0.0003075268,
   0.0004520236,
   0.000590096,
   0.0007649725,
   0.0008766618,
   0.0009554198,
   0.001135331,
   0.001342321,
   0.001428332,
   0.001136183,
   0.001481256,
   0.001502224};
   gre = new TGraphErrors(12,Graph4_fx1077,Graph4_fy1077,Graph4_fex1077,Graph4_fey1077);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1316;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1078[12] = {
   0.6,
   0.8,
   1,
   1.2,
   1.4,
   1.6,
   1.8,
   2,
   2.2,
   2.4,
   2.7,
   3.05};
   Double_t Graph5_fy1078[12] = {
   0.01790223,
   0.03541777,
   0.05561216,
   0.07541353,
   0.09431802,
   0.1119878,
   0.1265426,
   0.1392145,
   0.1498842,
   0.1583816,
   0.1669469,
   0.177448};
   Double_t Graph5_fex1078[12] = {
   0,
   0,
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
   Double_t Graph5_fey1078[12] = {
   0.0005391798,
   0.0004255668,
   0.000400494,
   0.0004198728,
   0.0004782727,
   0.0005807448,
   0.0007362478,
   0.00096251,
   0.001324742,
   0.001847155,
   0.002089016,
   0.004350369};
   gre = new TGraphErrors(12,Graph5_fx1078,Graph5_fy1078,Graph5_fex1078,Graph5_fey1078);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   TLine *line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 62.4 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (l) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent00->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent01
   TPad *pd_cent01 = new TPad("pd_cent01", "pd_cent01",0.5,0.05,0.9,0.2);
   pd_cent01->Draw();
   pd_cent01->cd();
   pd_cent01->Range(0,0,1,1);
   pd_cent01->SetFillColor(0);
   pd_cent01->SetBorderMode(0);
   pd_cent01->SetBorderSize(2);
   pd_cent01->SetTickx(1);
   pd_cent01->SetTicky(1);
   pd_cent01->SetLeftMargin(0);
   pd_cent01->SetRightMargin(0.15);
   pd_cent01->SetTopMargin(0);
   pd_cent01->SetBottomMargin(0.15);
   pd_cent01->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1079[7] = {
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph0_fy1079[7] = {
   0.01538004,
   0.0446205,
   0.07950014,
   0.1123672,
   0.1417094,
   0.1727208,
   0.1721603};
   Double_t Graph0_fex1079[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1079[7] = {
   0.0001022449,
   0.0005302357,
   0.001307843,
   0.002434605,
   0.003028863,
   0.003706161,
   0.005677942};
   gre = new TGraphErrors(7,Graph0_fx1079,Graph0_fy1079,Graph0_fex1079,Graph0_fey1079);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1320;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01079 = new TH1F("Graph_Graph01079","",100,-0.085,3.27);
   Graph_Graph01079->SetMinimum(-0.02);
   Graph_Graph01079->SetMaximum(0.32);
   Graph_Graph01079->SetDirectory(0);
   Graph_Graph01079->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01079->SetLineColor(ci);
   Graph_Graph01079->GetXaxis()->SetNdivisions(505);
   Graph_Graph01079->GetXaxis()->SetLabelFont(42);
   Graph_Graph01079->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01079->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01079->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01079->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01079->GetXaxis()->SetTitleFont(42);
   Graph_Graph01079->GetYaxis()->SetNdivisions(505);
   Graph_Graph01079->GetYaxis()->SetLabelFont(42);
   Graph_Graph01079->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01079->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01079->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01079->GetYaxis()->SetTitleFont(42);
   Graph_Graph01079->GetZaxis()->SetLabelFont(42);
   Graph_Graph01079->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01079->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01079->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01079->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01079);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1080[7] = {
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph1_fy1080[7] = {
   0.01538004,
   0.0446205,
   0.07950014,
   0.1123672,
   0.1417094,
   0.1727208,
   0.1721603};
   Double_t Graph1_fex1080[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1080[7] = {
   0.0004913137,
   0.0005154318,
   0.0006994649,
   0.001008863,
   0.001377455,
   0.002319795,
   0.006330903};
   gre = new TGraphErrors(7,Graph1_fx1080,Graph1_fy1080,Graph1_fex1080,Graph1_fey1080);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1081[4] = {
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph2_fy1081[4] = {
   0.009713302,
   0.02769858,
   0.05938664,
   0.09306824};
   Double_t Graph2_fex1081[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1081[4] = {
   0.0001022449,
   0.0005302357,
   0.001307843,
   0.002434605};
   gre = new TGraphErrors(4,Graph2_fx1081,Graph2_fy1081,Graph2_fex1081,Graph2_fey1081);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1321;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1082[4] = {
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph3_fy1082[4] = {
   0.009713302,
   0.02769858,
   0.05938664,
   0.09306824};
   Double_t Graph3_fex1082[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1082[4] = {
   0.002574296,
   0.001472578,
   0.001670279,
   0.002470361};
   gre = new TGraphErrors(4,Graph3_fx1082,Graph3_fy1082,Graph3_fex1082,Graph3_fey1082);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1083[6] = {
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph4_fy1083[6] = {
   0.01386134,
   0.04187517,
   0.08251703,
   0.1322565,
   0.1843094,
   0.2577225};
   Double_t Graph4_fex1083[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1083[6] = {
   0.0005302357,
   0.001307843,
   0.002434605,
   0.003028863,
   0.003706161,
   0.005677942};
   gre = new TGraphErrors(6,Graph4_fx1083,Graph4_fy1083,Graph4_fex1083,Graph4_fey1083);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1322;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1084[6] = {
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph5_fy1084[6] = {
   0.01386134,
   0.04187517,
   0.08251703,
   0.1322565,
   0.1843094,
   0.2577225};
   Double_t Graph5_fex1084[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1084[6] = {
   0.002559105,
   0.001999252,
   0.002076845,
   0.002360555,
   0.003535329,
   0.009042133};
   gre = new TGraphErrors(6,Graph5_fx1084,Graph5_fy1084,Graph5_fex1084,Graph5_fey1084);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (m) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent01->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent10
   TPad *pd_cent10 = new TPad("pd_cent10", "pd_cent10",0.1,0.2,0.5,0.35);
   pd_cent10->Draw();
   pd_cent10->cd();
   pd_cent10->Range(0,0,1,1);
   pd_cent10->SetFillColor(0);
   pd_cent10->SetBorderMode(0);
   pd_cent10->SetBorderSize(2);
   pd_cent10->SetTickx(1);
   pd_cent10->SetTicky(1);
   pd_cent10->SetLeftMargin(0.15);
   pd_cent10->SetRightMargin(0);
   pd_cent10->SetTopMargin(0);
   pd_cent10->SetBottomMargin(0);
   pd_cent10->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1085[14] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5,
   1.7,
   1.9,
   2.1,
   2.3,
   2.5,
   2.7,
   2.9};
   Double_t Graph0_fy1085[14] = {
   0.02279206,
   0.04245479,
   0.06153502,
   0.07823064,
   0.09233455,
   0.104016,
   0.1135791,
   0.1213616,
   0.1273325,
   0.1301157,
   0.1321779,
   0.1375657,
   0.139069,
   0.138327};
   Double_t Graph0_fex1085[14] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1085[14] = {
   4.293925e-05,
   0.000237891,
   0.0004453871,
   0.0006120029,
   0.0007785774,
   0.0008631873,
   0.0009997836,
   0.00109478,
   0.001230805,
   0.001263181,
   0.001181595,
   0.001174012,
   0.001348498,
   0.00174989};
   gre = new TGraphErrors(14,Graph0_fx1085,Graph0_fy1085,Graph0_fex1085,Graph0_fey1085);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1302;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01085 = new TH1F("Graph_Graph01085","",100,-0.085,3.27);
   Graph_Graph01085->SetMinimum(-0.02);
   Graph_Graph01085->SetMaximum(0.32);
   Graph_Graph01085->SetDirectory(0);
   Graph_Graph01085->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01085->SetLineColor(ci);
   Graph_Graph01085->GetXaxis()->SetNdivisions(505);
   Graph_Graph01085->GetXaxis()->SetLabelFont(42);
   Graph_Graph01085->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01085->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01085->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01085->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01085->GetXaxis()->SetTitleFont(42);
   Graph_Graph01085->GetYaxis()->SetNdivisions(505);
   Graph_Graph01085->GetYaxis()->SetLabelFont(42);
   Graph_Graph01085->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01085->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01085->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01085->GetYaxis()->SetTitleFont(42);
   Graph_Graph01085->GetZaxis()->SetLabelFont(42);
   Graph_Graph01085->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01085->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01085->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01085->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01085);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1086[14] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5,
   1.7,
   1.9,
   2.1,
   2.3,
   2.5,
   2.7,
   2.9};
   Double_t Graph1_fy1086[14] = {
   0.02279206,
   0.04245479,
   0.06153502,
   0.07823064,
   0.09233455,
   0.104016,
   0.1135791,
   0.1213616,
   0.1273325,
   0.1301157,
   0.1321779,
   0.1375657,
   0.139069,
   0.138327};
   Double_t Graph1_fex1086[14] = {
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1086[14] = {
   7.608179e-05,
   7.13925e-05,
   8.331804e-05,
   0.0001042959,
   0.0001354259,
   0.0001779802,
   0.0002365278,
   0.0003173815,
   0.0004291442,
   0.0005956538,
   0.0008501218,
   0.001209313,
   0.001713344,
   0.002406789};
   gre = new TGraphErrors(14,Graph1_fx1086,Graph1_fy1086,Graph1_fex1086,Graph1_fey1086);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1087[7] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph2_fy1087[7] = {
   0.01187938,
   0.02778874,
   0.04634946,
   0.06337735,
   0.07799049,
   0.09102463,
   0.1009515};
   Double_t Graph2_fex1087[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1087[7] = {
   4.293925e-05,
   0.000237891,
   0.0004453871,
   0.0006120029,
   0.0007785774,
   0.0008631873,
   0.0009997836};
   gre = new TGraphErrors(7,Graph2_fx1087,Graph2_fy1087,Graph2_fex1087,Graph2_fey1087);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1303;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1088[7] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph3_fy1088[7] = {
   0.01187938,
   0.02778874,
   0.04634946,
   0.06337735,
   0.07799049,
   0.09102463,
   0.1009515};
   Double_t Graph3_fex1088[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1088[7] = {
   0.0005112598,
   0.0002616889,
   0.0002267034,
   0.0002445239,
   0.0002988761,
   0.0003871447,
   0.0005157798};
   gre = new TGraphErrors(7,Graph3_fx1088,Graph3_fy1088,Graph3_fex1088,Graph3_fey1088);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1089[12] = {
   0.6,
   0.8,
   1,
   1.2,
   1.4,
   1.6,
   1.8,
   2,
   2.2,
   2.4,
   2.7,
   3.05};
   Double_t Graph4_fy1089[12] = {
   0.01726118,
   0.03439911,
   0.05402923,
   0.07416191,
   0.09277065,
   0.1089249,
   0.1204118,
   0.1328267,
   0.1410941,
   0.1554859,
   0.1670004,
   0.1673314};
   Double_t Graph4_fex1089[12] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1089[12] = {
   0.0003277786,
   0.0005554558,
   0.0006776602,
   0.0008210278,
   0.0009414736,
   0.001030727,
   0.001219546,
   0.00124684,
   0.00121682,
   0.001348302,
   0.001262717,
   0.001434541};
   gre = new TGraphErrors(12,Graph4_fx1089,Graph4_fy1089,Graph4_fex1089,Graph4_fey1089);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1304;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1090[12] = {
   0.6,
   0.8,
   1,
   1.2,
   1.4,
   1.6,
   1.8,
   2,
   2.2,
   2.4,
   2.7,
   3.05};
   Double_t Graph5_fy1090[12] = {
   0.01726118,
   0.03439911,
   0.05402923,
   0.07416191,
   0.09277065,
   0.1089249,
   0.1204118,
   0.1328267,
   0.1410941,
   0.1554859,
   0.1670004,
   0.1673314};
   Double_t Graph5_fex1090[12] = {
   0,
   0,
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
   Double_t Graph5_fey1090[12] = {
   0.0004306291,
   0.0003474195,
   0.0003324649,
   0.0003520996,
   0.0004003584,
   0.0004814254,
   0.0006022321,
   0.000779331,
   0.001066268,
   0.0014839,
   0.001688385,
   0.003585247};
   gre = new TGraphErrors(12,Graph5_fx1090,Graph5_fy1090,Graph5_fex1090,Graph5_fey1090);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 39 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (j) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent10->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent11
   TPad *pd_cent11 = new TPad("pd_cent11", "pd_cent11",0.5,0.2,0.9,0.35);
   pd_cent11->Draw();
   pd_cent11->cd();
   pd_cent11->Range(0,0,1,1);
   pd_cent11->SetFillColor(0);
   pd_cent11->SetBorderMode(0);
   pd_cent11->SetBorderSize(2);
   pd_cent11->SetTickx(1);
   pd_cent11->SetTicky(1);
   pd_cent11->SetLeftMargin(0);
   pd_cent11->SetRightMargin(0.15);
   pd_cent11->SetTopMargin(0);
   pd_cent11->SetBottomMargin(0);
   pd_cent11->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1091[7] = {
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph0_fy1091[7] = {
   0.01498263,
   0.04226149,
   0.07509978,
   0.1069764,
   0.1345194,
   0.1629472,
   0.1827545};
   Double_t Graph0_fex1091[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1091[7] = {
   6.308166e-05,
   0.0004831624,
   0.001240194,
   0.002151077,
   0.00342592,
   0.004952157,
   0.004983159};
   gre = new TGraphErrors(7,Graph0_fx1091,Graph0_fy1091,Graph0_fex1091,Graph0_fey1091);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1308;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01091 = new TH1F("Graph_Graph01091","",100,-0.085,3.27);
   Graph_Graph01091->SetMinimum(-0.02);
   Graph_Graph01091->SetMaximum(0.32);
   Graph_Graph01091->SetDirectory(0);
   Graph_Graph01091->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01091->SetLineColor(ci);
   Graph_Graph01091->GetXaxis()->SetNdivisions(505);
   Graph_Graph01091->GetXaxis()->SetLabelFont(42);
   Graph_Graph01091->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01091->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01091->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01091->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01091->GetXaxis()->SetTitleFont(42);
   Graph_Graph01091->GetYaxis()->SetNdivisions(505);
   Graph_Graph01091->GetYaxis()->SetLabelFont(42);
   Graph_Graph01091->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01091->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01091->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01091->GetYaxis()->SetTitleFont(42);
   Graph_Graph01091->GetZaxis()->SetLabelFont(42);
   Graph_Graph01091->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01091->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01091->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01091->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01091);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1092[7] = {
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph1_fy1092[7] = {
   0.01498263,
   0.04226149,
   0.07509978,
   0.1069764,
   0.1345194,
   0.1629472,
   0.1827545};
   Double_t Graph1_fex1092[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1092[7] = {
   0.0003903377,
   0.0004160049,
   0.000574781,
   0.0008546285,
   0.001207602,
   0.002063304,
   0.005702949};
   gre = new TGraphErrors(7,Graph1_fx1092,Graph1_fy1092,Graph1_fex1092,Graph1_fey1092);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1093[4] = {
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph2_fy1093[4] = {
   0.008989186,
   0.02885856,
   0.05616594,
   0.08646239};
   Double_t Graph2_fex1093[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1093[4] = {
   6.308166e-05,
   0.0004831624,
   0.001240194,
   0.002151077};
   gre = new TGraphErrors(4,Graph2_fx1093,Graph2_fy1093,Graph2_fex1093,Graph2_fey1093);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1309;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1094[4] = {
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph3_fy1094[4] = {
   0.008989186,
   0.02885856,
   0.05616594,
   0.08646239};
   Double_t Graph3_fex1094[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1094[4] = {
   0.00206229,
   0.001201856,
   0.001302042,
   0.001811502};
   gre = new TGraphErrors(4,Graph3_fx1094,Graph3_fy1094,Graph3_fex1094,Graph3_fey1094);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1095[6] = {
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph4_fy1095[6] = {
   0.008906442,
   0.04133963,
   0.07643496,
   0.1313252,
   0.1782456,
   0.2212577};
   Double_t Graph4_fex1095[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1095[6] = {
   0.0004831624,
   0.001240194,
   0.002151077,
   0.00342592,
   0.004952157,
   0.004983159};
   gre = new TGraphErrors(6,Graph4_fx1095,Graph4_fy1095,Graph4_fex1095,Graph4_fey1095);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1310;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1096[6] = {
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph5_fy1096[6] = {
   0.008906442,
   0.04133963,
   0.07643496,
   0.1313252,
   0.1782456,
   0.2212577};
   Double_t Graph5_fex1096[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1096[6] = {
   0.002229905,
   0.001782177,
   0.001869729,
   0.002091793,
   0.003042652,
   0.007697305};
   gre = new TGraphErrors(6,Graph5_fx1096,Graph5_fy1096,Graph5_fex1096,Graph5_fey1096);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (k) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent11->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent20
   TPad *pd_cent20 = new TPad("pd_cent20", "pd_cent20",0.1,0.35,0.5,0.5);
   pd_cent20->Draw();
   pd_cent20->cd();
   pd_cent20->Range(0,0,1,1);
   pd_cent20->SetFillColor(0);
   pd_cent20->SetBorderMode(0);
   pd_cent20->SetBorderSize(2);
   pd_cent20->SetTickx(1);
   pd_cent20->SetTicky(1);
   pd_cent20->SetLeftMargin(0.15);
   pd_cent20->SetRightMargin(0);
   pd_cent20->SetTopMargin(0);
   pd_cent20->SetBottomMargin(0);
   pd_cent20->SetFrameBorderMode(0);
   
   Double_t v2_PionsMinusSys_fx1097[12] = {
   0.2989504,
   0.4900753,
   0.6884028,
   0.8879113,
   1.08771,
   1.287841,
   1.487976,
   1.687955,
   1.887884,
   2.087851,
   2.35265,
   2.799448};
   Double_t v2_PionsMinusSys_fy1097[12] = {
   0.0231565,
   0.04221379,
   0.06052474,
   0.07649148,
   0.09011317,
   0.1010068,
   0.1097314,
   0.1164299,
   0.1223511,
   0.12545,
   0.1287057,
   0.1326518};
   Double_t v2_PionsMinusSys_fex1097[12] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v2_PionsMinusSys_fey1097[12] = {
   3.579225e-05,
   0.000217363,
   0.0004505639,
   0.0006205761,
   0.000776912,
   0.0008826284,
   0.0009981133,
   0.00119292,
   0.001159519,
   0.001418786,
   0.001535094,
   0.001557419};
   gre = new TGraphErrors(12,v2_PionsMinusSys_fx1097,v2_PionsMinusSys_fy1097,v2_PionsMinusSys_fex1097,v2_PionsMinusSys_fey1097);
   gre->SetName("v2_PionsMinusSys");
   gre->SetTitle("");

   ci = 1290;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v2_PionsMinusSys1097 = new TH1F("Graph_v2_PionsMinusSys1097","",100,-0.085,3.27);
   Graph_v2_PionsMinusSys1097->SetMinimum(-0.02);
   Graph_v2_PionsMinusSys1097->SetMaximum(0.32);
   Graph_v2_PionsMinusSys1097->SetDirectory(0);
   Graph_v2_PionsMinusSys1097->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v2_PionsMinusSys1097->SetLineColor(ci);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetNdivisions(505);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetLabelFont(42);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetLabelOffset(0.01);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetLabelSize(0.1);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetTitleSize(0.035);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetTitleOffset(1);
   Graph_v2_PionsMinusSys1097->GetXaxis()->SetTitleFont(42);
   Graph_v2_PionsMinusSys1097->GetYaxis()->SetNdivisions(505);
   Graph_v2_PionsMinusSys1097->GetYaxis()->SetLabelFont(42);
   Graph_v2_PionsMinusSys1097->GetYaxis()->SetLabelOffset(0.01);
   Graph_v2_PionsMinusSys1097->GetYaxis()->SetLabelSize(0.1);
   Graph_v2_PionsMinusSys1097->GetYaxis()->SetTitleSize(0.035);
   Graph_v2_PionsMinusSys1097->GetYaxis()->SetTitleFont(42);
   Graph_v2_PionsMinusSys1097->GetZaxis()->SetLabelFont(42);
   Graph_v2_PionsMinusSys1097->GetZaxis()->SetLabelSize(0.035);
   Graph_v2_PionsMinusSys1097->GetZaxis()->SetTitleSize(0.035);
   Graph_v2_PionsMinusSys1097->GetZaxis()->SetTitleOffset(1);
   Graph_v2_PionsMinusSys1097->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v2_PionsMinusSys1097);
   
   gre->Draw("ae5");
   
   Double_t v2_PionsMinus_fx1098[12] = {
   0.2989504,
   0.4900753,
   0.6884028,
   0.8879113,
   1.08771,
   1.287841,
   1.487976,
   1.687955,
   1.887884,
   2.087851,
   2.35265,
   2.799448};
   Double_t v2_PionsMinus_fy1098[12] = {
   0.0231565,
   0.04221379,
   0.06052474,
   0.07649148,
   0.09011317,
   0.1010068,
   0.1097314,
   0.1164299,
   0.1223511,
   0.12545,
   0.1287057,
   0.1326518};
   Double_t v2_PionsMinus_fex1098[12] = {
   6.83011e-07,
   8.380384e-07,
   1.163658e-06,
   1.663659e-06,
   2.405326e-06,
   3.489108e-06,
   5.028252e-06,
   7.237371e-06,
   1.043191e-05,
   1.506098e-05,
   3.443228e-05,
   9.415083e-05};
   Double_t v2_PionsMinus_fey1098[12] = {
   4.091646e-05,
   3.87994e-05,
   4.545338e-05,
   5.721781e-05,
   7.470293e-05,
   9.942828e-05,
   0.0001331534,
   0.0001797562,
   0.0002447266,
   0.0003428755,
   0.0004068952,
   0.0007829539};
   gre = new TGraphErrors(12,v2_PionsMinus_fx1098,v2_PionsMinus_fy1098,v2_PionsMinus_fex1098,v2_PionsMinus_fey1098);
   gre->SetName("v2_PionsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v2_KaonsMinusSys_fx1099[7] = {
   0.3349029,
   0.5039425,
   0.6950756,
   0.8909577,
   1.088776,
   1.287948,
   1.487648};
   Double_t v2_KaonsMinusSys_fy1099[7] = {
   0.01278416,
   0.02755329,
   0.04503011,
   0.06132486,
   0.07530431,
   0.08783484,
   0.09814858};
   Double_t v2_KaonsMinusSys_fex1099[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v2_KaonsMinusSys_fey1099[7] = {
   3.579225e-05,
   0.000217363,
   0.0004505639,
   0.0006205761,
   0.000776912,
   0.0008826284,
   0.0009981133};
   gre = new TGraphErrors(7,v2_KaonsMinusSys_fx1099,v2_KaonsMinusSys_fy1099,v2_KaonsMinusSys_fex1099,v2_KaonsMinusSys_fey1099);
   gre->SetName("v2_KaonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1291;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t v2_KaonsMinus_fx1100[7] = {
   0.3349029,
   0.5039425,
   0.6950756,
   0.8909577,
   1.088776,
   1.287948,
   1.487648};
   Double_t v2_KaonsMinus_fy1100[7] = {
   0.01278416,
   0.02755329,
   0.04503011,
   0.06132486,
   0.07530431,
   0.08783484,
   0.09814858};
   Double_t v2_KaonsMinus_fex1100[7] = {
   3.930716e-06,
   3.143036e-06,
   3.26277e-06,
   4.025148e-06,
   5.455758e-06,
   7.762265e-06,
   1.122073e-05};
   Double_t v2_KaonsMinus_fey1100[7] = {
   0.0002747664,
   0.0001438364,
   0.0001262129,
   0.0001378626,
   0.0001694665,
   0.000221822,
   0.0002983685};
   gre = new TGraphErrors(7,v2_KaonsMinus_fx1100,v2_KaonsMinus_fy1100,v2_KaonsMinus_fex1100,v2_KaonsMinus_fey1100);
   gre->SetName("v2_KaonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v2_ProtonsMinusSys_fx1101[12] = {
   0.6053655,
   0.7993433,
   0.9956126,
   1.193247,
   1.391896,
   1.590715,
   1.78984,
   1.989191,
   2.18878,
   2.388499,
   2.654545,
   3.024099};
   Double_t v2_ProtonsMinusSys_fy1101[12] = {
   0.0168034,
   0.03308527,
   0.05154483,
   0.07061031,
   0.08791893,
   0.1034139,
   0.1165451,
   0.128251,
   0.1379278,
   0.1455975,
   0.1548354,
   0.1631898};
   Double_t v2_ProtonsMinusSys_fex1101[12] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v2_ProtonsMinusSys_fey1101[12] = {
   0.000329079,
   0.0005402479,
   0.0006903408,
   0.0008429634,
   0.0009622571,
   0.001075857,
   0.001215724,
   0.001258675,
   0.001449464,
   0.001500585,
   0.001507877,
   0.001849989};
   gre = new TGraphErrors(12,v2_ProtonsMinusSys_fx1101,v2_ProtonsMinusSys_fy1101,v2_ProtonsMinusSys_fex1101,v2_ProtonsMinusSys_fey1101);
   gre->SetName("v2_ProtonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1292;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t v2_ProtonsMinus_fx1102[12] = {
   0.6053655,
   0.7993433,
   0.9956126,
   1.193247,
   1.391896,
   1.590715,
   1.78984,
   1.989191,
   2.18878,
   2.388499,
   2.654545,
   3.024099};
   Double_t v2_ProtonsMinus_fy1102[12] = {
   0.0168034,
   0.03308527,
   0.05154483,
   0.07061031,
   0.08791893,
   0.1034139,
   0.1165451,
   0.128251,
   0.1379278,
   0.1455975,
   0.1548354,
   0.1631898};
   Double_t v2_ProtonsMinus_fex1102[12] = {
   6.141719e-06,
   5.797971e-06,
   6.277536e-06,
   7.423321e-06,
   9.263882e-06,
   1.201268e-05,
   1.608302e-05,
   2.205602e-05,
   3.072871e-05,
   4.331126e-05,
   9.684133e-05,
   0.0001619307};
   Double_t v2_ProtonsMinus_fey1102[12] = {
   0.000254622,
   0.0002078729,
   0.0002017392,
   0.0002183188,
   0.000252813,
   0.0003072691,
   0.0003881966,
   0.0005079259,
   0.0007027494,
   0.0009891697,
   0.0011459,
   0.002493322};
   gre = new TGraphErrors(12,v2_ProtonsMinus_fx1102,v2_ProtonsMinus_fy1102,v2_ProtonsMinus_fex1102,v2_ProtonsMinus_fey1102);
   gre->SetName("v2_ProtonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 27 GeV Run18} }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (h) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent20->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent21
   TPad *pd_cent21 = new TPad("pd_cent21", "pd_cent21",0.5,0.35,0.9,0.5);
   pd_cent21->Draw();
   pd_cent21->cd();
   pd_cent21->Range(0,0,1,1);
   pd_cent21->SetFillColor(0);
   pd_cent21->SetBorderMode(0);
   pd_cent21->SetBorderSize(2);
   pd_cent21->SetTickx(1);
   pd_cent21->SetTicky(1);
   pd_cent21->SetLeftMargin(0);
   pd_cent21->SetRightMargin(0.15);
   pd_cent21->SetTopMargin(0);
   pd_cent21->SetBottomMargin(0);
   pd_cent21->SetFrameBorderMode(0);
   
   Double_t v3_PionsMinusSys_fx1103[7] = {
   0.3406721,
   0.6247821,
   0.9229881,
   1.222788,
   1.553068,
   1.997742,
   2.629163};
   Double_t v3_PionsMinusSys_fy1103[7] = {
   0.01445203,
   0.04021591,
   0.07182095,
   0.1014213,
   0.1282611,
   0.1563321,
   0.1681419};
   Double_t v3_PionsMinusSys_fex1103[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_PionsMinusSys_fey1103[7] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   gre = new TGraphErrors(7,v3_PionsMinusSys_fx1103,v3_PionsMinusSys_fy1103,v3_PionsMinusSys_fex1103,v3_PionsMinusSys_fey1103);
   gre->SetName("v3_PionsMinusSys");
   gre->SetTitle("");

   ci = 1296;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v3_PionsMinusSys1103 = new TH1F("Graph_v3_PionsMinusSys1103","",100,-0.085,3.27);
   Graph_v3_PionsMinusSys1103->SetMinimum(-0.02);
   Graph_v3_PionsMinusSys1103->SetMaximum(0.32);
   Graph_v3_PionsMinusSys1103->SetDirectory(0);
   Graph_v3_PionsMinusSys1103->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v3_PionsMinusSys1103->SetLineColor(ci);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetNdivisions(505);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetLabelSize(0.1);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetTitleOffset(1);
   Graph_v3_PionsMinusSys1103->GetXaxis()->SetTitleFont(42);
   Graph_v3_PionsMinusSys1103->GetYaxis()->SetNdivisions(505);
   Graph_v3_PionsMinusSys1103->GetYaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1103->GetYaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsMinusSys1103->GetYaxis()->SetLabelSize(0.1);
   Graph_v3_PionsMinusSys1103->GetYaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1103->GetYaxis()->SetTitleFont(42);
   Graph_v3_PionsMinusSys1103->GetZaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1103->GetZaxis()->SetLabelSize(0.035);
   Graph_v3_PionsMinusSys1103->GetZaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1103->GetZaxis()->SetTitleOffset(1);
   Graph_v3_PionsMinusSys1103->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v3_PionsMinusSys1103);
   
   gre->Draw("ae5");
   
   Double_t v3_PionsMinus_fx1104[7] = {
   0.3406721,
   0.6247821,
   0.9229881,
   1.222788,
   1.553068,
   1.997742,
   2.629163};
   Double_t v3_PionsMinus_fy1104[7] = {
   0.01445203,
   0.04021591,
   0.07182095,
   0.1014213,
   0.1282611,
   0.1563321,
   0.1681419};
   Double_t v3_PionsMinus_fex1104[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_PionsMinus_fey1104[7] = {
   0.0002261597,
   0.0002435838,
   0.0003386121,
   0.0005094343,
   0.0007262668,
   0.001256033,
   0.003601429};
   gre = new TGraphErrors(7,v3_PionsMinus_fx1104,v3_PionsMinus_fy1104,v3_PionsMinus_fex1104,v3_PionsMinus_fey1104);
   gre->SetName("v3_PionsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v3_KaonsMinusSys_fx1105[4] = {
   0.3973548,
   0.6429538,
   0.9285217,
   1.22352};
   Double_t v3_KaonsMinusSys_fy1105[4] = {
   0.008621007,
   0.02672821,
   0.05334559,
   0.08006908};
   Double_t v3_KaonsMinusSys_fex1105[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_KaonsMinusSys_fey1105[4] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421};
   gre = new TGraphErrors(4,v3_KaonsMinusSys_fx1105,v3_KaonsMinusSys_fy1105,v3_KaonsMinusSys_fex1105,v3_KaonsMinusSys_fey1105);
   gre->SetName("v3_KaonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1297;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t v3_KaonsMinus_fx1106[4] = {
   0.3973548,
   0.6429538,
   0.9285217,
   1.22352};
   Double_t v3_KaonsMinus_fy1106[4] = {
   0.008621007,
   0.02672821,
   0.05334559,
   0.08006908};
   Double_t v3_KaonsMinus_fex1106[4] = {
   0,
   0,
   0,
   0};
   Double_t v3_KaonsMinus_fey1106[4] = {
   0.00119645,
   0.0007122618,
   0.0007850897,
   0.00110565};
   gre = new TGraphErrors(4,v3_KaonsMinus_fx1106,v3_KaonsMinus_fy1106,v3_KaonsMinus_fex1106,v3_KaonsMinus_fey1106);
   gre->SetName("v3_KaonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v3_ProtonsMinusSys_fx1107[6] = {
   0.6581107,
   0.9419849,
   1.234144,
   1.563778,
   2.006968,
   2.633273};
   Double_t v3_ProtonsMinusSys_fy1107[6] = {
   0.008737569,
   0.03805156,
   0.07577888,
   0.1179798,
   0.1645116,
   0.2312877};
   Double_t v3_ProtonsMinusSys_fex1107[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_ProtonsMinusSys_fey1107[6] = {
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   gre = new TGraphErrors(6,v3_ProtonsMinusSys_fx1107,v3_ProtonsMinusSys_fy1107,v3_ProtonsMinusSys_fex1107,v3_ProtonsMinusSys_fey1107);
   gre->SetName("v3_ProtonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1298;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t v3_ProtonsMinus_fx1108[6] = {
   0.6581107,
   0.9419849,
   1.234144,
   1.563778,
   2.006968,
   2.633273};
   Double_t v3_ProtonsMinus_fy1108[6] = {
   0.008737569,
   0.03805156,
   0.07577888,
   0.1179798,
   0.1645116,
   0.2312877};
   Double_t v3_ProtonsMinus_fex1108[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_ProtonsMinus_fey1108[6] = {
   0.001427345,
   0.00116051,
   0.001251255,
   0.001428347,
   0.002119513,
   0.005550263};
   gre = new TGraphErrors(6,v3_ProtonsMinus_fx1108,v3_ProtonsMinus_fy1108,v3_ProtonsMinus_fex1108,v3_ProtonsMinus_fey1108);
   gre->SetName("v3_ProtonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (i) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent21->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent30
   TPad *pd_cent30 = new TPad("pd_cent30", "pd_cent30",0.1,0.5,0.5,0.65);
   pd_cent30->Draw();
   pd_cent30->cd();
   pd_cent30->Range(0,0,1,1);
   pd_cent30->SetFillColor(0);
   pd_cent30->SetBorderMode(0);
   pd_cent30->SetBorderSize(2);
   pd_cent30->SetTickx(1);
   pd_cent30->SetTicky(1);
   pd_cent30->SetLeftMargin(0.15);
   pd_cent30->SetRightMargin(0);
   pd_cent30->SetTopMargin(0);
   pd_cent30->SetBottomMargin(0);
   pd_cent30->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1109[11] = {
   0.2986599,
   0.4897384,
   0.6879962,
   0.8874232,
   1.087307,
   1.287345,
   1.487148,
   1.686953,
   1.949513,
   2.349411,
   2.793138};
   Double_t Graph0_fy1109[11] = {
   0.02297526,
   0.04134705,
   0.05876194,
   0.07396102,
   0.08651784,
   0.09717249,
   0.1046962,
   0.1112035,
   0.1159821,
   0.120862,
   0.1311381};
   Double_t Graph0_fex1109[11] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1109[11] = {
   3.169811e-05,
   0.0002391877,
   0.000447512,
   0.0006878044,
   0.0007946885,
   0.000882219,
   0.0008353776,
   0.001047781,
   0.00127009,
   0.001077326,
   0.00189985};
   gre = new TGraphErrors(11,Graph0_fx1109,Graph0_fy1109,Graph0_fex1109,Graph0_fey1109);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1278;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01109 = new TH1F("Graph_Graph01109","",100,-0.085,3.27);
   Graph_Graph01109->SetMinimum(-0.02);
   Graph_Graph01109->SetMaximum(0.32);
   Graph_Graph01109->SetDirectory(0);
   Graph_Graph01109->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01109->SetLineColor(ci);
   Graph_Graph01109->GetXaxis()->SetNdivisions(505);
   Graph_Graph01109->GetXaxis()->SetLabelFont(42);
   Graph_Graph01109->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01109->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01109->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01109->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01109->GetXaxis()->SetTitleFont(42);
   Graph_Graph01109->GetYaxis()->SetNdivisions(505);
   Graph_Graph01109->GetYaxis()->SetLabelFont(42);
   Graph_Graph01109->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01109->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01109->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01109->GetYaxis()->SetTitleFont(42);
   Graph_Graph01109->GetZaxis()->SetLabelFont(42);
   Graph_Graph01109->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01109->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01109->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01109->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01109);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1110[11] = {
   0.2986599,
   0.4897384,
   0.6879962,
   0.8874232,
   1.087307,
   1.287345,
   1.487148,
   1.686953,
   1.949513,
   2.349411,
   2.793138};
   Double_t Graph1_fy1110[11] = {
   0.02297526,
   0.04134705,
   0.05876194,
   0.07396102,
   0.08651784,
   0.09717249,
   0.1046962,
   0.1112035,
   0.1159821,
   0.120862,
   0.1311381};
   Double_t Graph1_fex1110[11] = {
   2.90732e-06,
   3.599876e-06,
   5.055521e-06,
   7.306794e-06,
   1.074334e-05,
   1.575625e-05,
   2.317525e-05,
   3.42604e-05,
   8.054233e-05,
   0.0001777196,
   0.0005129363};
   Double_t Graph1_fey1110[11] = {
   0.0001898653,
   0.0001817414,
   0.0002153094,
   0.0002742966,
   0.0003639081,
   0.0004901222,
   0.0006703567,
   0.00092941,
   0.001069777,
   0.002305964,
   0.004726451};
   gre = new TGraphErrors(11,Graph1_fx1110,Graph1_fy1110,Graph1_fex1110,Graph1_fey1110);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1111[7] = {
   0.3353061,
   0.5035281,
   0.6945401,
   0.8901895,
   1.088086,
   1.287329,
   1.487243};
   Double_t Graph2_fy1111[7] = {
   0.01245866,
   0.02712086,
   0.04349369,
   0.05854521,
   0.07142683,
   0.08253839,
   0.09078206};
   Double_t Graph2_fex1111[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1111[7] = {
   3.169811e-05,
   0.0002391877,
   0.000447512,
   0.0006878044,
   0.0007946885,
   0.000882219,
   0.0008353776};
   gre = new TGraphErrors(7,Graph2_fx1111,Graph2_fy1111,Graph2_fex1111,Graph2_fey1111);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1279;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1112[7] = {
   0.3353061,
   0.5035281,
   0.6945401,
   0.8901895,
   1.088086,
   1.287329,
   1.487243};
   Double_t Graph3_fy1112[7] = {
   0.01245866,
   0.02712086,
   0.04349369,
   0.05854521,
   0.07142683,
   0.08253839,
   0.09078206};
   Double_t Graph3_fex1112[7] = {
   1.731027e-05,
   1.400994e-05,
   1.472877e-05,
   1.848045e-05,
   2.569682e-05,
   3.727588e-05,
   5.497566e-05};
   Double_t Graph3_fey1112[7] = {
   0.001325007,
   0.0006982317,
   0.0006210253,
   0.0006914575,
   0.0008717275,
   0.001163591,
   0.001595839};
   gre = new TGraphErrors(7,Graph3_fx1112,Graph3_fy1112,Graph3_fex1112,Graph3_fey1112);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1113[12] = {
   0.6048939,
   0.7989326,
   0.9952399,
   1.193084,
   1.391333,
   1.590032,
   1.789295,
   1.988611,
   2.188278,
   2.387849,
   2.652443,
   3.023769};
   Double_t Graph4_fy1113[12] = {
   0.01480177,
   0.02875427,
   0.04762417,
   0.06615045,
   0.08238095,
   0.09692466,
   0.1057888,
   0.1258152,
   0.1347846,
   0.1189499,
   0.151086,
   0.1681001};
   Double_t Graph4_fex1113[12] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1113[12] = {
   0.0003624371,
   0.0005750471,
   0.0006661102,
   0.0009125257,
   0.0008185087,
   0.001033367,
   0.001005834,
   0.001162517,
   0.001413742,
   0.001281207,
   0.001752517,
   0.001354931};
   gre = new TGraphErrors(12,Graph4_fx1113,Graph4_fy1113,Graph4_fex1113,Graph4_fey1113);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1280;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1114[12] = {
   0.6048939,
   0.7989326,
   0.9952399,
   1.193084,
   1.391333,
   1.590032,
   1.789295,
   1.988611,
   2.188278,
   2.387849,
   2.652443,
   3.023769};
   Double_t Graph5_fy1114[12] = {
   0.01480177,
   0.02875427,
   0.04762417,
   0.06615045,
   0.08238095,
   0.09692466,
   0.1057888,
   0.1258152,
   0.1347846,
   0.1189499,
   0.151086,
   0.1681001};
   Double_t Graph5_fex1114[12] = {
   3.076432e-05,
   2.945683e-05,
   3.2296e-05,
   3.839723e-05,
   4.839737e-05,
   6.388996e-05,
   8.721738e-05,
   0.0001216751,
   0.0001722955,
   0.0002473723,
   0.0005654793,
   0.000968123};
   Double_t Graph5_fey1114[12] = {
   0.001387683,
   0.001149245,
   0.001130291,
   0.001231624,
   0.001441929,
   0.001785497,
   0.002300452,
   0.003060669,
   0.004310829,
   0.006171491,
   0.007324184,
   0.016448};
   gre = new TGraphErrors(12,Graph5_fx1114,Graph5_fy1114,Graph5_fex1114,Graph5_fey1114);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 19.6 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (e) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent30->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent31
   TPad *pd_cent31 = new TPad("pd_cent31", "pd_cent31",0.5,0.5,0.9,0.65);
   pd_cent31->Draw();
   pd_cent31->cd();
   pd_cent31->Range(0,0,1,1);
   pd_cent31->SetFillColor(0);
   pd_cent31->SetBorderMode(0);
   pd_cent31->SetBorderSize(2);
   pd_cent31->SetTickx(1);
   pd_cent31->SetTicky(1);
   pd_cent31->SetLeftMargin(0);
   pd_cent31->SetRightMargin(0.15);
   pd_cent31->SetTopMargin(0);
   pd_cent31->SetBottomMargin(0);
   pd_cent31->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1115[7] = {
   0.3400224,
   0.6239593,
   0.921851,
   1.221887,
   1.549881,
   1.991377,
   2.619099};
   Double_t Graph0_fy1115[7] = {
   0.0135116,
   0.03843678,
   0.06970928,
   0.09690664,
   0.12182,
   0.1373581,
   0.1611051};
   Double_t Graph0_fex1115[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1115[7] = {
   0.0003008765,
   0.0003064206,
   0.001197021,
   0.002394465,
   0.004534064,
   0.004058159,
   0.006601629};
   gre = new TGraphErrors(7,Graph0_fx1115,Graph0_fy1115,Graph0_fex1115,Graph0_fey1115);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1284;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01115 = new TH1F("Graph_Graph01115","",100,-0.085,3.27);
   Graph_Graph01115->SetMinimum(-0.02);
   Graph_Graph01115->SetMaximum(0.32);
   Graph_Graph01115->SetDirectory(0);
   Graph_Graph01115->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01115->SetLineColor(ci);
   Graph_Graph01115->GetXaxis()->SetNdivisions(505);
   Graph_Graph01115->GetXaxis()->SetLabelFont(42);
   Graph_Graph01115->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01115->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01115->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01115->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01115->GetXaxis()->SetTitleFont(42);
   Graph_Graph01115->GetYaxis()->SetNdivisions(505);
   Graph_Graph01115->GetYaxis()->SetLabelFont(42);
   Graph_Graph01115->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01115->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01115->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01115->GetYaxis()->SetTitleFont(42);
   Graph_Graph01115->GetZaxis()->SetLabelFont(42);
   Graph_Graph01115->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01115->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01115->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01115->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01115);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1116[7] = {
   0.3400224,
   0.6239593,
   0.921851,
   1.221887,
   1.549881,
   1.991377,
   2.619099};
   Double_t Graph1_fy1116[7] = {
   0.0135116,
   0.03843678,
   0.06970928,
   0.09690664,
   0.12182,
   0.1373581,
   0.1611051};
   Double_t Graph1_fex1116[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1116[7] = {
   0.001095953,
   0.00119799,
   0.001695091,
   0.002597375,
   0.003824946,
   0.006995752,
   0.02165907};
   gre = new TGraphErrors(7,Graph1_fx1116,Graph1_fy1116,Graph1_fex1116,Graph1_fey1116);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1117[4] = {
   0.3974164,
   0.641916,
   0.9267085,
   1.222186};
   Double_t Graph2_fy1117[4] = {
   0.01016192,
   0.01831003,
   0.05233554,
   0.07462419};
   Double_t Graph2_fex1117[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1117[4] = {
   0.0003008765,
   0.0003064206,
   0.001197021,
   0.002394465};
   gre = new TGraphErrors(4,Graph2_fx1117,Graph2_fy1117,Graph2_fex1117,Graph2_fey1117);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1285;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1118[4] = {
   0.3974164,
   0.641916,
   0.9267085,
   1.222186};
   Double_t Graph3_fy1118[4] = {
   0.01016192,
   0.01831003,
   0.05233554,
   0.07462419};
   Double_t Graph3_fex1118[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1118[4] = {
   0.006018512,
   0.003628441,
   0.004097933,
   0.005953179};
   gre = new TGraphErrors(4,Graph3_fx1118,Graph3_fy1118,Graph3_fex1118,Graph3_fey1118);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1119[6] = {
   0.6570219,
   0.9410886,
   1.23362,
   1.56137,
   2.00245,
   2.627466};
   Double_t Graph4_fy1119[6] = {
   0.0006107928,
   0.02950125,
   0.068133,
   0.1043335,
   0.1885347,
   0.2735552};
   Double_t Graph4_fex1119[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1119[6] = {
   0.0003064206,
   0.001197021,
   0.002394465,
   0.004534064,
   0.004058159,
   0.006601629};
   gre = new TGraphErrors(6,Graph4_fx1119,Graph4_fy1119,Graph4_fex1119,Graph4_fey1119);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1286;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1120[6] = {
   0.6570219,
   0.9410886,
   1.23362,
   1.56137,
   2.00245,
   2.627466};
   Double_t Graph5_fy1120[6] = {
   0.0006107928,
   0.02950125,
   0.068133,
   0.1043335,
   0.1885347,
   0.2735552};
   Double_t Graph5_fex1120[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1120[6] = {
   0.008229393,
   0.006783959,
   0.00736225,
   0.008599923,
   0.01320649,
   0.03641241};
   gre = new TGraphErrors(6,Graph5_fx1120,Graph5_fy1120,Graph5_fex1120,Graph5_fey1120);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ STAR Preliminary } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (f) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent31->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent40
   TPad *pd_cent40 = new TPad("pd_cent40", "pd_cent40",0.1,0.65,0.5,0.8);
   pd_cent40->Draw();
   pd_cent40->cd();
   pd_cent40->Range(0,0,1,1);
   pd_cent40->SetFillColor(0);
   pd_cent40->SetBorderMode(0);
   pd_cent40->SetBorderSize(2);
   pd_cent40->SetTickx(1);
   pd_cent40->SetTicky(1);
   pd_cent40->SetLeftMargin(0.15);
   pd_cent40->SetRightMargin(0);
   pd_cent40->SetTopMargin(0);
   pd_cent40->SetBottomMargin(0);
   pd_cent40->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1121[12] = {
   0.2964446,
   0.4891498,
   0.6875339,
   0.8871368,
   1.086996,
   1.287084,
   1.487049,
   1.686799,
   1.886458,
   2.086254,
   2.286176,
   2.485617};
   Double_t Graph0_fy1121[12] = {
   0.02494412,
   0.04221977,
   0.05883206,
   0.07326848,
   0.08543314,
   0.09436087,
   0.1018919,
   0.1064737,
   0.1133484,
   0.1161635,
   0.1192982,
   0.1185398};
   Double_t Graph0_fex1121[12] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1121[12] = {
   0.0001137964,
   0.0002627299,
   0.0005399538,
   0.0005345494,
   0.0008808209,
   0.0006777511,
   0.0008020956,
   0.0008695172,
   0.001516855,
   0.0008169932,
   0.001894015,
   0.0006452003};
   gre = new TGraphErrors(12,Graph0_fx1121,Graph0_fy1121,Graph0_fex1121,Graph0_fey1121);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1266;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01121 = new TH1F("Graph_Graph01121","",100,-0.085,3.27);
   Graph_Graph01121->SetMinimum(-0.02);
   Graph_Graph01121->SetMaximum(0.32);
   Graph_Graph01121->SetDirectory(0);
   Graph_Graph01121->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01121->SetLineColor(ci);
   Graph_Graph01121->GetXaxis()->SetNdivisions(505);
   Graph_Graph01121->GetXaxis()->SetLabelFont(42);
   Graph_Graph01121->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01121->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01121->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01121->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01121->GetXaxis()->SetTitleFont(42);
   Graph_Graph01121->GetYaxis()->SetNdivisions(505);
   Graph_Graph01121->GetYaxis()->SetLabelFont(42);
   Graph_Graph01121->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01121->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01121->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01121->GetYaxis()->SetTitleFont(42);
   Graph_Graph01121->GetZaxis()->SetLabelFont(42);
   Graph_Graph01121->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01121->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01121->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01121->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01121);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1122[12] = {
   0.2964446,
   0.4891498,
   0.6875339,
   0.8871368,
   1.086996,
   1.287084,
   1.487049,
   1.686799,
   1.886458,
   2.086254,
   2.286176,
   2.485617};
   Double_t Graph1_fy1122[12] = {
   0.02494412,
   0.04221977,
   0.05883206,
   0.07326848,
   0.08543314,
   0.09436087,
   0.1018919,
   0.1064737,
   0.1133484,
   0.1161635,
   0.1192982,
   0.1185398};
   Double_t Graph1_fex1122[12] = {
   3.20587e-06,
   4.079695e-06,
   5.812058e-06,
   8.530524e-06,
   1.264161e-05,
   1.868678e-05,
   2.762644e-05,
   4.101772e-05,
   6.13894e-05,
   9.250604e-05,
   0.0001402149,
   0.0002147261};
   Double_t Graph1_fey1122[12] = {
   0.0002238993,
   0.0002207366,
   0.0002654124,
   0.0003428364,
   0.0004583484,
   0.0006220009,
   0.0008552589,
   0.00119169,
   0.001685842,
   0.002467969,
   0.00374532,
   0.005752318};
   gre = new TGraphErrors(12,Graph1_fx1122,Graph1_fy1122,Graph1_fex1122,Graph1_fey1122);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1123[7] = {
   0.3337868,
   0.503257,
   0.6943899,
   0.8898237,
   1.087285,
   1.286331,
   1.486067};
   Double_t Graph2_fy1123[7] = {
   0.01326973,
   0.02732218,
   0.04266635,
   0.05737589,
   0.06820588,
   0.08248658,
   0.08778178};
   Double_t Graph2_fex1123[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1123[7] = {
   0.0001137964,
   0.0002627299,
   0.0005399538,
   0.0005345494,
   0.0008808209,
   0.0006777511,
   0.0008020956};
   gre = new TGraphErrors(7,Graph2_fx1123,Graph2_fy1123,Graph2_fex1123,Graph2_fey1123);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1267;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1124[7] = {
   0.3337868,
   0.503257,
   0.6943899,
   0.8898237,
   1.087285,
   1.286331,
   1.486067};
   Double_t Graph3_fy1124[7] = {
   0.01326973,
   0.02732218,
   0.04266635,
   0.05737589,
   0.06820588,
   0.08248658,
   0.08778178};
   Double_t Graph3_fex1124[7] = {
   2.099889e-05,
   1.716086e-05,
   1.81201e-05,
   2.292386e-05,
   3.241307e-05,
   4.822499e-05,
   7.342439e-05};
   Double_t Graph3_fey1124[7] = {
   0.001703128,
   0.0009149714,
   0.0008181488,
   0.000919269,
   0.00117899,
   0.001615553,
   0.002288867};
   gre = new TGraphErrors(7,Graph3_fx1124,Graph3_fy1124,Graph3_fex1124,Graph3_fey1124);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1125[11] = {
   0.6046224,
   0.7983578,
   0.9947478,
   1.192509,
   1.390682,
   1.589363,
   1.788317,
   1.987685,
   2.187045,
   2.387713,
   2.586885};
   Double_t Graph4_fy1125[11] = {
   0.01509069,
   0.02859388,
   0.04653798,
   0.06211355,
   0.08087972,
   0.08899641,
   0.1076213,
   0.1141387,
   0.1198282,
   0.1206034,
   0.126081};
   Double_t Graph4_fex1125[11] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1125[11] = {
   0.0003811986,
   0.0005730318,
   0.0007409039,
   0.0008032287,
   0.0006979347,
   0.0006915733,
   0.001411169,
   0.001068109,
   0.001429325,
   0.0005753889,
   0.001281732};
   gre = new TGraphErrors(11,Graph4_fx1125,Graph4_fy1125,Graph4_fex1125,Graph4_fey1125);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1268;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1126[11] = {
   0.6046224,
   0.7983578,
   0.9947478,
   1.192509,
   1.390682,
   1.589363,
   1.788317,
   1.987685,
   2.187045,
   2.387713,
   2.586885};
   Double_t Graph5_fy1126[11] = {
   0.01509069,
   0.02859388,
   0.04653798,
   0.06211355,
   0.08087972,
   0.08899641,
   0.1076213,
   0.1141387,
   0.1198282,
   0.1206034,
   0.126081};
   Double_t Graph5_fex1126[11] = {
   4.102776e-05,
   3.974084e-05,
   4.416956e-05,
   5.348232e-05,
   6.870872e-05,
   9.269179e-05,
   0.0001294077,
   0.0001851984,
   0.0002689623,
   0.0003983656,
   0.0005892347};
   Double_t Graph5_fey1126[11] = {
   0.001981728,
   0.001659696,
   0.001655386,
   0.001835499,
   0.002188595,
   0.002777388,
   0.003660083,
   0.005007144,
   0.007232574,
   0.01055996,
   0.01573638};
   gre = new TGraphErrors(11,Graph5_fx1126,Graph5_fy1126,Graph5_fex1126,Graph5_fey1126);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 14.5 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (c) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent40->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent41
   TPad *pd_cent41 = new TPad("pd_cent41", "pd_cent41",0.5,0.65,0.9,0.8);
   pd_cent41->Draw();
   pd_cent41->cd();
   pd_cent41->Range(0,0,1,1);
   pd_cent41->SetFillColor(0);
   pd_cent41->SetBorderMode(0);
   pd_cent41->SetBorderSize(2);
   pd_cent41->SetTickx(1);
   pd_cent41->SetTicky(1);
   pd_cent41->SetLeftMargin(0);
   pd_cent41->SetRightMargin(0.15);
   pd_cent41->SetTopMargin(0);
   pd_cent41->SetBottomMargin(0);
   pd_cent41->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1127[7] = {
   0.3365998,
   0.6229292,
   0.9212915,
   1.221416,
   1.549362,
   1.987083,
   2.608774};
   Double_t Graph0_fy1127[7] = {
   0.01613499,
   0.03613464,
   0.06470854,
   0.09023949,
   0.09967867,
   0.1560119,
   0.1224524};
   Double_t Graph0_fex1127[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1127[7] = {
   0.0002996215,
   0.0002322319,
   0.001073177,
   0.002764091,
   0.003924008,
   0.002741888,
   0.01382106};
   gre = new TGraphErrors(7,Graph0_fx1127,Graph0_fy1127,Graph0_fex1127,Graph0_fey1127);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1272;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01127 = new TH1F("Graph_Graph01127","",100,-0.085,3.27);
   Graph_Graph01127->SetMinimum(-0.02);
   Graph_Graph01127->SetMaximum(0.32);
   Graph_Graph01127->SetDirectory(0);
   Graph_Graph01127->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01127->SetLineColor(ci);
   Graph_Graph01127->GetXaxis()->SetNdivisions(505);
   Graph_Graph01127->GetXaxis()->SetLabelFont(42);
   Graph_Graph01127->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01127->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01127->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01127->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01127->GetXaxis()->SetTitleFont(42);
   Graph_Graph01127->GetYaxis()->SetNdivisions(505);
   Graph_Graph01127->GetYaxis()->SetLabelFont(42);
   Graph_Graph01127->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01127->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01127->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01127->GetYaxis()->SetTitleFont(42);
   Graph_Graph01127->GetZaxis()->SetLabelFont(42);
   Graph_Graph01127->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01127->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01127->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01127->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01127);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1128[7] = {
   0.3365998,
   0.6229292,
   0.9212915,
   1.221416,
   1.549362,
   1.987083,
   2.608774};
   Double_t Graph1_fy1128[7] = {
   0.01613499,
   0.03613464,
   0.06470854,
   0.09023949,
   0.09967867,
   0.1560119,
   0.1224524};
   Double_t Graph1_fex1128[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1128[7] = {
   0.001429861,
   0.001617724,
   0.00233118,
   0.003606546,
   0.005336138,
   0.00990138,
   0.03278141};
   gre = new TGraphErrors(7,Graph1_fx1128,Graph1_fy1128,Graph1_fex1128,Graph1_fey1128);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1129[4] = {
   0.3954444,
   0.64153,
   0.9257252,
   1.22026};
   Double_t Graph2_fy1129[4] = {
   0.00602072,
   0.02598097,
   0.04560094,
   0.07249755};
   Double_t Graph2_fex1129[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1129[4] = {
   0.0002996215,
   0.0002322319,
   0.001073177,
   0.002764091};
   gre = new TGraphErrors(4,Graph2_fx1129,Graph2_fy1129,Graph2_fex1129,Graph2_fey1129);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1273;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1130[4] = {
   0.3954444,
   0.64153,
   0.9257252,
   1.22026};
   Double_t Graph3_fy1130[4] = {
   0.00602072,
   0.02598097,
   0.04560094,
   0.07249755};
   Double_t Graph3_fex1130[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1130[4] = {
   0.008538619,
   0.005219689,
   0.005952628,
   0.008891529};
   gre = new TGraphErrors(4,Graph3_fx1130,Graph3_fy1130,Graph3_fex1130,Graph3_fey1130);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1131[6] = {
   0.6563033,
   0.9400144,
   1.232121,
   1.558417,
   1.9964,
   2.620617};
   Double_t Graph4_fy1131[6] = {
   0.01700044,
   0.03542956,
   0.06567379,
   0.09892019,
   0.1449471,
   0.199797};
   Double_t Graph4_fex1131[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1131[6] = {
   0.0002322319,
   0.001073177,
   0.002764091,
   0.003924008,
   0.002741888,
   0.01382106};
   gre = new TGraphErrors(6,Graph4_fx1131,Graph4_fy1131,Graph4_fex1131,Graph4_fey1131);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1274;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1132[6] = {
   0.6563033,
   0.9400144,
   1.232121,
   1.558417,
   1.9964,
   2.620617};
   Double_t Graph5_fy1132[6] = {
   0.01700044,
   0.03542956,
   0.06567379,
   0.09892019,
   0.1449471,
   0.199797};
   Double_t Graph5_fex1132[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1132[6] = {
   0.01295002,
   0.01086215,
   0.01206265,
   0.01450843,
   0.0233882,
   0.0677262};
   gre = new TGraphErrors(6,Graph5_fx1132,Graph5_fy1132,Graph5_fex1132,Graph5_fey1132);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
   
   TLegend *leg = new TLegend(0.1,0.4,0.3,0.9);
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph1","  #pi^{-}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph3","  K^{-}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph5","  #bar{p}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (d) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent41->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent50
   TPad *pd_cent50 = new TPad("pd_cent50", "pd_cent50",0.1,0.8,0.5,0.9499999);
   pd_cent50->Draw();
   pd_cent50->cd();
   pd_cent50->Range(0,0,1,1);
   pd_cent50->SetFillColor(0);
   pd_cent50->SetBorderMode(0);
   pd_cent50->SetBorderSize(2);
   pd_cent50->SetTickx(1);
   pd_cent50->SetTicky(1);
   pd_cent50->SetLeftMargin(0.15);
   pd_cent50->SetRightMargin(0);
   pd_cent50->SetTopMargin(0);
   pd_cent50->SetBottomMargin(0);
   pd_cent50->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1133[8] = {
   0.2977909,
   0.4891351,
   0.6875444,
   0.8868823,
   1.148595,
   1.547453,
   1.886016,
   2.144964};
   Double_t Graph0_fy1133[8] = {
   0.02358194,
   0.04061922,
   0.055423,
   0.07079469,
   0.08278085,
   0.09822669,
   0.09895111,
   0.1038303};
   Double_t Graph0_fex1133[8] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1133[8] = {
   0.0001009164,
   0.0002497888,
   0.0003092828,
   0.0005964932,
   0.0008696456,
   0.001022896,
   0.001154754,
   0.0007961114};
   gre = new TGraphErrors(8,Graph0_fx1133,Graph0_fy1133,Graph0_fex1133,Graph0_fey1133);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1254;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01133 = new TH1F("Graph_Graph01133","",100,-0.085,3.27);
   Graph_Graph01133->SetMinimum(-0.02);
   Graph_Graph01133->SetMaximum(0.32);
   Graph_Graph01133->SetDirectory(0);
   Graph_Graph01133->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01133->SetLineColor(ci);
   Graph_Graph01133->GetXaxis()->SetNdivisions(505);
   Graph_Graph01133->GetXaxis()->SetLabelFont(42);
   Graph_Graph01133->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01133->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01133->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01133->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01133->GetXaxis()->SetTitleFont(42);
   Graph_Graph01133->GetYaxis()->SetNdivisions(505);
   Graph_Graph01133->GetYaxis()->SetLabelFont(42);
   Graph_Graph01133->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01133->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01133->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01133->GetYaxis()->SetTitleFont(42);
   Graph_Graph01133->GetZaxis()->SetLabelFont(42);
   Graph_Graph01133->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01133->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01133->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01133->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01133);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1134[8] = {
   0.2977909,
   0.4891351,
   0.6875444,
   0.8868823,
   1.148595,
   1.547453,
   1.886016,
   2.144964};
   Double_t Graph1_fy1134[8] = {
   0.02358194,
   0.04061922,
   0.055423,
   0.07079469,
   0.08278085,
   0.09822669,
   0.09895111,
   0.1038303};
   Double_t Graph1_fex1134[8] = {
   5.287427e-06,
   6.694443e-06,
   9.551359e-06,
   1.40055e-05,
   3.326118e-05,
   7.447512e-05,
   0.0001076009,
   0.0002619972};
   Double_t Graph1_fey1134[8] = {
   0.0004117436,
   0.0004030127,
   0.0004850411,
   0.0006273769,
   0.0006849485,
   0.001324514,
   0.003298447,
   0.00412064};
   gre = new TGraphErrors(8,Graph1_fx1134,Graph1_fy1134,Graph1_fex1134,Graph1_fey1134);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1135[6] = {
   0.3351228,
   0.5028939,
   0.6941645,
   0.8898411,
   1.149905,
   1.546271};
   Double_t Graph2_fy1135[6] = {
   0.01074335,
   0.02389494,
   0.03833106,
   0.05471289,
   0.07137813,
   0.0866295};
   Double_t Graph2_fex1135[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1135[6] = {
   0.0001009164,
   0.0002497888,
   0.0003092828,
   0.0005964932,
   0.0008696456,
   0.001022896};
   gre = new TGraphErrors(6,Graph2_fx1135,Graph2_fy1135,Graph2_fex1135,Graph2_fey1135);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1255;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1136[6] = {
   0.3351228,
   0.5028939,
   0.6941645,
   0.8898411,
   1.149905,
   1.546271};
   Double_t Graph3_fy1136[6] = {
   0.01074335,
   0.02389494,
   0.03833106,
   0.05471289,
   0.07137813,
   0.0866295};
   Double_t Graph3_fex1136[6] = {
   3.455119e-05,
   2.835594e-05,
   3.030856e-05,
   3.833908e-05,
   8.52028e-05,
   0.0001918953};
   Double_t Graph3_fey1136[6] = {
   0.00314873,
   0.001684332,
   0.001523726,
   0.001713208,
   0.001765196,
   0.003451142};
   gre = new TGraphErrors(6,Graph3_fx1136,Graph3_fy1136,Graph3_fex1136,Graph3_fey1136);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1137[5] = {
   0.5112975,
   0.7942153,
   1.228368,
   1.800354,
   2.432806};
   Double_t Graph4_fy1137[5] = {
   -0.002640076,
   0.02440218,
   0.05404317,
   0.08200153,
   0.1219119};
   Double_t Graph4_fex1137[5] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1137[5] = {
   0.0002497888,
   0.0004273116,
   0.0008774275,
   0.00117618,
   0.0008930805};
   gre = new TGraphErrors(5,Graph4_fx1137,Graph4_fy1137,Graph4_fex1137,Graph4_fey1137);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1256;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1138[5] = {
   0.5112975,
   0.7942153,
   1.228368,
   1.800354,
   2.432806};
   Double_t Graph5_fy1138[5] = {
   -0.002640076,
   0.02440218,
   0.05404317,
   0.08200153,
   0.1219119};
   Double_t Graph5_fex1138[5] = {
   9.194711e-05,
   0.0001155661,
   0.0001984215,
   0.0004673528,
   0.001879032};
   Double_t Graph5_fey1138[5] = {
   0.005507407,
   0.002731391,
   0.002654544,
   0.005431294,
   0.01541226};
   gre = new TGraphErrors(5,Graph5_fx1138,Graph5_fy1138,Graph5_fex1138,Graph5_fey1138);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{Au+Au #sqrt{s_{NN}} = 11.5 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-0.05,0.19,"#scale[0.8]{ #font[42]{ v_{2} } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (a) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent50->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pd_cent51
   TPad *pd_cent51 = new TPad("pd_cent51", "pd_cent51",0.5,0.8,0.9,0.9499999);
   pd_cent51->Draw();
   pd_cent51->cd();
   pd_cent51->Range(0,0,1,1);
   pd_cent51->SetFillColor(0);
   pd_cent51->SetBorderMode(0);
   pd_cent51->SetBorderSize(2);
   pd_cent51->SetTickx(1);
   pd_cent51->SetTicky(1);
   pd_cent51->SetLeftMargin(0);
   pd_cent51->SetRightMargin(0.15);
   pd_cent51->SetTopMargin(0);
   pd_cent51->SetBottomMargin(0);
   pd_cent51->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1139[7] = {
   0.3382286,
   0.6229062,
   0.920647,
   1.220598,
   1.547453,
   1.983669,
   2.600351};
   Double_t Graph0_fy1139[7] = {
   0.01491877,
   0.03675492,
   0.0555886,
   0.0802125,
   0.1170782,
   0.1000135,
   0.1926388};
   Double_t Graph0_fex1139[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1139[7] = {
   0.001716966,
   0.001267891,
   0.002730168,
   0.002047547,
   0.003716983,
   0.005057148,
   0.02236226};
   gre = new TGraphErrors(7,Graph0_fx1139,Graph0_fy1139,Graph0_fex1139,Graph0_fey1139);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1260;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01139 = new TH1F("Graph_Graph01139","",100,-0.085,3.27);
   Graph_Graph01139->SetMinimum(-0.02);
   Graph_Graph01139->SetMaximum(0.32);
   Graph_Graph01139->SetDirectory(0);
   Graph_Graph01139->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01139->SetLineColor(ci);
   Graph_Graph01139->GetXaxis()->SetNdivisions(505);
   Graph_Graph01139->GetXaxis()->SetLabelFont(42);
   Graph_Graph01139->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01139->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01139->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01139->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01139->GetXaxis()->SetTitleFont(42);
   Graph_Graph01139->GetYaxis()->SetNdivisions(505);
   Graph_Graph01139->GetYaxis()->SetLabelFont(42);
   Graph_Graph01139->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01139->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01139->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01139->GetYaxis()->SetTitleFont(42);
   Graph_Graph01139->GetZaxis()->SetLabelFont(42);
   Graph_Graph01139->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01139->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01139->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01139->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01139);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1140[7] = {
   0.3382286,
   0.6229062,
   0.920647,
   1.220598,
   1.547453,
   1.983669,
   2.600351};
   Double_t Graph1_fy1140[7] = {
   0.01491877,
   0.03675492,
   0.0555886,
   0.0802125,
   0.1170782,
   0.1000135,
   0.1926388};
   Double_t Graph1_fex1140[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1140[7] = {
   0.002515094,
   0.002823634,
   0.004071729,
   0.006380074,
   0.009624106,
   0.01842551,
   0.06334727};
   gre = new TGraphErrors(7,Graph1_fx1140,Graph1_fy1140,Graph1_fex1140,Graph1_fey1140);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1141[4] = {
   0.3967123,
   0.5975109,
   0.8876308,
   1.347141};
   Double_t Graph2_fy1141[4] = {
   0.004515871,
   0.03519143,
   0.04196387,
   0.03008853};
   Double_t Graph2_fex1141[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1141[4] = {
   0.001716966,
   0.002205078,
   0.002057398,
   0.006334881};
   gre = new TGraphErrors(4,Graph2_fx1141,Graph2_fy1141,Graph2_fex1141,Graph2_fey1141);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1261;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1142[4] = {
   0.3967123,
   0.5975109,
   0.8876308,
   1.347141};
   Double_t Graph3_fy1142[4] = {
   0.004515871,
   0.03519143,
   0.04196387,
   0.03008853};
   Double_t Graph3_fex1142[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1142[4] = {
   0.01497029,
   0.01132415,
   0.008175902,
   0.016864};
   gre = new TGraphErrors(4,Graph3_fx1142,Graph3_fy1142,Graph3_fex1142,Graph3_fey1142);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1143[5] = {
   0.6046115,
   0.844062,
   1.228368,
   1.754827,
   2.218503};
   Double_t Graph4_fy1143[5] = {
   -0.01932275,
   0.01075267,
   0.1243811,
   0.07716776,
   0.324293};
   Double_t Graph4_fex1143[5] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1143[5] = {
   0.002205078,
   0.002722212,
   0.002212381,
   0.004182337,
   0.006302739};
   gre = new TGraphErrors(5,Graph4_fx1143,Graph4_fy1143,Graph4_fex1143,Graph4_fey1143);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1262;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1144[5] = {
   0.6046115,
   0.844062,
   1.228368,
   1.754827,
   2.218503};
   Double_t Graph5_fy1144[5] = {
   -0.01932275,
   0.01075267,
   0.1243811,
   0.07716776,
   0.324293};
   Double_t Graph5_fex1144[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1144[5] = {
   0.03758209,
   0.02433116,
   0.0196088,
   0.04120768,
   0.0705878};
   gre = new TGraphErrors(5,Graph5_fx1144,Graph5_fy1144,Graph5_fex1144,Graph5_fey1144);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 0-60% } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-0.05,0.19,"#scale[0.8]{ #font[42]{ 2.5 #times v_{3}} }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.7,0.26,"#scale[0.8]{ #font[42]{ (b) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent51->Modified();
   canvas->cd();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
