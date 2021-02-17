void v2v3_ParticlesPads_scale_cent060()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Sun Oct  4 12:44:29 2020) by ROOT version 6.18/02

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
   TLatex *   tex = new TLatex(0.8,0.46,"#font[42]{ v_{n}/n_{q}^{n/2} }");
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
      tex = new TLatex(0.325,0.4,"#font[42]{ Particles }");
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
      tex = new TLatex(0.275,0.4,"#scale[0.9]{#font[42]{ (m_{T}-m_{0})/n_{q} [GeV/c^{2}] } }");
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
   
   Double_t Graph0_fx1001[14] = {
   0.09565365,
   0.1897722,
   0.2871043,
   0.3855939,
   0.4846246,
   0.5839504,
   0.6834546,
   0.7830749,
   0.8827747,
   0.9825314,
   1.08233,
   1.182161,
   1.282018,
   1.381893};
   Double_t Graph0_fy1001[14] = {
   0.01115193,
   0.02134215,
   0.0313553,
   0.04008676,
   0.04752431,
   0.05330958,
   0.05853537,
   0.06171632,
   0.06451855,
   0.0661711,
   0.06756584,
   0.0703226,
   0.07100841,
   0.07033734};
   Double_t Graph0_fex1001[14] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1001[14] = {
   3.012256e-05,
   0.0001100785,
   0.0002064494,
   0.0002549328,
   0.0003236195,
   0.0004215506,
   0.0004733305,
   0.0005167015,
   0.0005947898,
   0.0006157962,
   0.0008075299,
   0.0005584012,
   0.0007152804,
   0.0006496144};
   TGraphErrors *gre = new TGraphErrors(14,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1242;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,-0.07,1.7);
   Graph_Graph01001->SetMinimum(-0.01);
   Graph_Graph01001->SetMaximum(0.14);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetNdivisions(505);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetNdivisions(505);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1002[14] = {
   0.09565365,
   0.1897722,
   0.2871043,
   0.3855939,
   0.4846246,
   0.5839504,
   0.6834546,
   0.7830749,
   0.8827747,
   0.9825314,
   1.08233,
   1.182161,
   1.282018,
   1.381893};
   Double_t Graph1_fy1002[14] = {
   0.01115193,
   0.02134215,
   0.0313553,
   0.04008676,
   0.04752431,
   0.05330958,
   0.05853537,
   0.06171632,
   0.06451855,
   0.0661711,
   0.06756584,
   0.0703226,
   0.07100841,
   0.07033734};
   Double_t Graph1_fex1002[14] = {
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1002[14] = {
   5.178437e-05,
   4.789678e-05,
   5.522509e-05,
   6.815269e-05,
   8.67847e-05,
   0.0001115574,
   0.0001448309,
   0.0001908431,
   0.0002549156,
   0.0003496262,
   0.0004916736,
   0.0006879815,
   0.0009567381,
   0.001318001};
   gre = new TGraphErrors(14,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1003[7] = {
   0.04200344,
   0.104488,
   0.18145,
   0.2664177,
   0.3560154,
   0.4484555,
   0.5427403};
   Double_t Graph2_fy1003[7] = {
   0.006091826,
   0.01431468,
   0.02419749,
   0.03324246,
   0.0414495,
   0.04796815,
   0.05287826};
   Double_t Graph2_fex1003[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1003[7] = {
   3.012256e-05,
   0.0001100785,
   0.0002064494,
   0.0002549328,
   0.0003236195,
   0.0004215506,
   0.0004733305};
   gre = new TGraphErrors(7,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1243;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1004[7] = {
   0.04200344,
   0.104488,
   0.18145,
   0.2664177,
   0.3560154,
   0.4484555,
   0.5427403};
   Double_t Graph3_fy1004[7] = {
   0.006091826,
   0.01431468,
   0.02419749,
   0.03324246,
   0.0414495,
   0.04796815,
   0.05287826};
   Double_t Graph3_fex1004[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1004[7] = {
   0.000316429,
   0.0001574727,
   0.0001353947,
   0.0001497216,
   0.000189849,
   0.0002524942,
   0.0003405288};
   gre = new TGraphErrors(7,Graph3_fx1004,Graph3_fy1004,Graph3_fex1004,Graph3_fey1004);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1005[12] = {
   0.05847999,
   0.0982515,
   0.1443294,
   0.1949997,
   0.249021,
   0.3055157,
   0.3638645,
   0.4236268,
   0.4844848,
   0.5462055,
   0.6400371,
   0.7509288};
   Double_t Graph4_fy1005[12] = {
   0.007056043,
   0.01324136,
   0.01998666,
   0.02695603,
   0.03365853,
   0.03905944,
   0.04391217,
   0.04864861,
   0.05180403,
   0.05572447,
   0.05852925,
   0.0597687};
   Double_t Graph4_fex1005[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1005[12] = {
   2.008171e-05,
   7.338568e-05,
   0.0001376329,
   0.0001699552,
   0.0002157464,
   0.0002810337,
   0.0003155537,
   0.0003444677,
   0.0003965265,
   0.0004105308,
   0.0005383533,
   0.0003722674};
   gre = new TGraphErrors(12,Graph4_fx1005,Graph4_fy1005,Graph4_fex1005,Graph4_fey1005);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1244;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1006[12] = {
   0.05847999,
   0.0982515,
   0.1443294,
   0.1949997,
   0.249021,
   0.3055157,
   0.3638645,
   0.4236268,
   0.4844848,
   0.5462055,
   0.6400371,
   0.7509288};
   Double_t Graph5_fy1006[12] = {
   0.007056043,
   0.01324136,
   0.01998666,
   0.02695603,
   0.03365853,
   0.03905944,
   0.04391217,
   0.04864861,
   0.05180403,
   0.05572447,
   0.05852925,
   0.0597687};
   Double_t Graph5_fex1006[12] = {
   0,
   0,
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
   Double_t Graph5_fey1006[12] = {
   0.000117871,
   9.397383e-05,
   8.845856e-05,
   9.262453e-05,
   0.0001051011,
   0.0001268613,
   0.0001598254,
   0.0002075809,
   0.0002836943,
   0.0003923783,
   0.0004403905,
   0.0009049166};
   gre = new TGraphErrors(12,Graph5_fx1006,Graph5_fy1006,Graph5_fex1006,Graph5_fey1006);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   TLine *line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ 62.4 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (l) } }");
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
   
   Double_t Graph0_fx1007[7] = {
   0.118616,
   0.2626228,
   0.4103139,
   0.5590989,
   0.733253,
   0.9825314,
   1.331953};
   Double_t Graph0_fy1007[7] = {
   0.005362971,
   0.0156099,
   0.02838093,
   0.04035335,
   0.04978707,
   0.06032276,
   0.06666455};
   Double_t Graph0_fex1007[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1007[7] = {
   3.614902e-05,
   0.0001874666,
   0.0004623924,
   0.0008607627,
   0.001070865,
   0.001310326,
   0.002007456};
   gre = new TGraphErrors(7,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1248;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","",100,-0.07,1.7);
   Graph_Graph01007->SetMinimum(-0.01);
   Graph_Graph01007->SetMaximum(0.14);
   Graph_Graph01007->SetDirectory(0);
   Graph_Graph01007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01007->SetLineColor(ci);
   Graph_Graph01007->GetXaxis()->SetNdivisions(505);
   Graph_Graph01007->GetXaxis()->SetLabelFont(42);
   Graph_Graph01007->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01007->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01007->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetXaxis()->SetTitleFont(42);
   Graph_Graph01007->GetYaxis()->SetNdivisions(505);
   Graph_Graph01007->GetYaxis()->SetLabelFont(42);
   Graph_Graph01007->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01007->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01007->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01007->GetYaxis()->SetTitleFont(42);
   Graph_Graph01007->GetZaxis()->SetLabelFont(42);
   Graph_Graph01007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01007);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1008[7] = {
   0.118616,
   0.2626228,
   0.4103139,
   0.5590989,
   0.733253,
   0.9825314,
   1.331953};
   Double_t Graph1_fy1008[7] = {
   0.005362971,
   0.0156099,
   0.02838093,
   0.04035335,
   0.04978707,
   0.06032276,
   0.06666455};
   Double_t Graph1_fex1008[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1008[7] = {
   0.0001741168,
   0.000182046,
   0.0002460729,
   0.000354515,
   0.0004818231,
   0.0007972573,
   0.002103433};
   gre = new TGraphErrors(7,Graph1_fx1008,Graph1_fy1008,Graph1_fex1008,Graph1_fey1008);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1009[4] = {
   0.05574174,
   0.161274,
   0.2884718,
   0.4251425};
   Double_t Graph2_fy1009[4] = {
   0.003721066,
   0.01094459,
   0.02126399,
   0.03309685};
   Double_t Graph2_fex1009[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1009[4] = {
   3.614902e-05,
   0.0001874666,
   0.0004623924,
   0.0008607627};
   gre = new TGraphErrors(4,Graph2_fx1009,Graph2_fy1009,Graph2_fex1009,Graph2_fey1009);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1249;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1010[4] = {
   0.05574174,
   0.161274,
   0.2884718,
   0.4251425};
   Double_t Graph3_fy1010[4] = {
   0.003721066,
   0.01094459,
   0.02126399,
   0.03309685};
   Double_t Graph3_fex1010[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1010[4] = {
   0.0008260498,
   0.0004726848,
   0.0005310037,
   0.0007807581};
   gre = new TGraphErrors(4,Graph3_fx1010,Graph3_fy1010,Graph3_fex1010,Graph3_fey1010);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1011[6] = {
   0.06771815,
   0.1323212,
   0.2082304,
   0.3055157,
   0.453935,
   0.6715842};
   Double_t Graph4_fy1011[6] = {
   0.003012825,
   0.008708767,
   0.01694628,
   0.02566027,
   0.03672115,
   0.04976068};
   Double_t Graph4_fex1011[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1011[6] = {
   0.0001020439,
   0.0002516946,
   0.0004685399,
   0.000582905,
   0.000713251,
   0.00109272};
   gre = new TGraphErrors(6,Graph4_fx1011,Graph4_fy1011,Graph4_fex1011,Graph4_fey1011);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1250;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1012[6] = {
   0.06771815,
   0.1323212,
   0.2082304,
   0.3055157,
   0.453935,
   0.6715842};
   Double_t Graph5_fy1012[6] = {
   0.003012825,
   0.008708767,
   0.01694628,
   0.02566027,
   0.03672115,
   0.04976068};
   Double_t Graph5_fex1012[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1012[6] = {
   0.0003165854,
   0.0002502494,
   0.0002606308,
   0.0002948661,
   0.0004376918,
   0.001100646};
   gre = new TGraphErrors(6,Graph5_fx1012,Graph5_fy1012,Graph5_fex1012,Graph5_fey1012);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (m) } }");
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
   
   Double_t Graph0_fx1013[14] = {
   0.09565365,
   0.1897722,
   0.2871043,
   0.3855939,
   0.4846246,
   0.5839504,
   0.6834546,
   0.7830749,
   0.8827747,
   0.9825314,
   1.08233,
   1.182161,
   1.282018,
   1.381893};
   Double_t Graph0_fy1013[14] = {
   0.0108633,
   0.02077257,
   0.03023744,
   0.03856318,
   0.04566297,
   0.05150522,
   0.05606106,
   0.05946034,
   0.0625706,
   0.06445049,
   0.06608473,
   0.06673209,
   0.06920108,
   0.06690195};
   Double_t Graph0_fex1013[14] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1013[14] = {
   2.146962e-05,
   0.0001189455,
   0.0002226935,
   0.0003060015,
   0.0003892887,
   0.0004315937,
   0.0004998918,
   0.0005473899,
   0.0006154025,
   0.0006315904,
   0.0005907974,
   0.0005870062,
   0.0006742489,
   0.0008749449};
   gre = new TGraphErrors(14,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1230;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01013 = new TH1F("Graph_Graph01013","",100,-0.07,1.7);
   Graph_Graph01013->SetMinimum(-0.01);
   Graph_Graph01013->SetMaximum(0.14);
   Graph_Graph01013->SetDirectory(0);
   Graph_Graph01013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01013->SetLineColor(ci);
   Graph_Graph01013->GetXaxis()->SetNdivisions(505);
   Graph_Graph01013->GetXaxis()->SetLabelFont(42);
   Graph_Graph01013->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01013->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01013->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetXaxis()->SetTitleFont(42);
   Graph_Graph01013->GetYaxis()->SetNdivisions(505);
   Graph_Graph01013->GetYaxis()->SetLabelFont(42);
   Graph_Graph01013->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01013->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01013->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01013->GetYaxis()->SetTitleFont(42);
   Graph_Graph01013->GetZaxis()->SetLabelFont(42);
   Graph_Graph01013->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01013->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01013->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01013);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1014[14] = {
   0.09565365,
   0.1897722,
   0.2871043,
   0.3855939,
   0.4846246,
   0.5839504,
   0.6834546,
   0.7830749,
   0.8827747,
   0.9825314,
   1.08233,
   1.182161,
   1.282018,
   1.381893};
   Double_t Graph1_fy1014[14] = {
   0.0108633,
   0.02077257,
   0.03023744,
   0.03856318,
   0.04566297,
   0.05150522,
   0.05606106,
   0.05946034,
   0.0625706,
   0.06445049,
   0.06608473,
   0.06673209,
   0.06920108,
   0.06690195};
   Double_t Graph1_fex1014[14] = {
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1014[14] = {
   3.832787e-05,
   3.584199e-05,
   4.162111e-05,
   5.193854e-05,
   6.721079e-05,
   8.810213e-05,
   0.0001166765,
   0.0001557919,
   0.0002093082,
   0.0002882272,
   0.0004065568,
   0.0005716978,
   0.0007992383,
   0.001109365};
   gre = new TGraphErrors(14,Graph1_fx1014,Graph1_fy1014,Graph1_fex1014,Graph1_fey1014);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1015[7] = {
   0.04200344,
   0.104488,
   0.18145,
   0.2664177,
   0.3560154,
   0.4484555,
   0.5427403};
   Double_t Graph2_fy1015[7] = {
   0.00632462,
   0.01419679,
   0.0237132,
   0.03207535,
   0.03917033,
   0.04521261,
   0.05004745};
   Double_t Graph2_fex1015[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1015[7] = {
   2.146962e-05,
   0.0001189455,
   0.0002226935,
   0.0003060015,
   0.0003892887,
   0.0004315937,
   0.0004998918};
   gre = new TGraphErrors(7,Graph2_fx1015,Graph2_fy1015,Graph2_fex1015,Graph2_fey1015);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1231;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1016[7] = {
   0.04200344,
   0.104488,
   0.18145,
   0.2664177,
   0.3560154,
   0.4484555,
   0.5427403};
   Double_t Graph3_fy1016[7] = {
   0.00632462,
   0.01419679,
   0.0237132,
   0.03207535,
   0.03917033,
   0.04521261,
   0.05004745};
   Double_t Graph3_fex1016[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1016[7] = {
   0.0002256625,
   0.0001150773,
   9.882827e-05,
   0.0001054028,
   0.0001273347,
   0.0001633332,
   0.0002158505};
   gre = new TGraphErrors(7,Graph3_fx1016,Graph3_fy1016,Graph3_fex1016,Graph3_fey1016);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1017[12] = {
   0.05847999,
   0.0982515,
   0.1443294,
   0.1949997,
   0.249021,
   0.3055157,
   0.3638645,
   0.4236268,
   0.4844848,
   0.5462055,
   0.6400371,
   0.7509288};
   Double_t Graph4_fy1017[12] = {
   0.007635264,
   0.01372944,
   0.02058481,
   0.02724796,
   0.03339868,
   0.03877708,
   0.04327265,
   0.0473899,
   0.05079731,
   0.05336857,
   0.05606873,
   0.05759347};
   Double_t Graph4_fex1017[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1017[12] = {
   1.431308e-05,
   7.9297e-05,
   0.0001484624,
   0.000204001,
   0.0002595258,
   0.0002877291,
   0.0003332612,
   0.0003649266,
   0.0004102684,
   0.0004210603,
   0.000393865,
   0.0003913374};
   gre = new TGraphErrors(12,Graph4_fx1017,Graph4_fy1017,Graph4_fex1017,Graph4_fey1017);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1232;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1018[12] = {
   0.05847999,
   0.0982515,
   0.1443294,
   0.1949997,
   0.249021,
   0.3055157,
   0.3638645,
   0.4236268,
   0.4844848,
   0.5462055,
   0.6400371,
   0.7509288};
   Double_t Graph5_fy1018[12] = {
   0.007635264,
   0.01372944,
   0.02058481,
   0.02724796,
   0.03339868,
   0.03877708,
   0.04327265,
   0.0473899,
   0.05079731,
   0.05336857,
   0.05606873,
   0.05759347};
   Double_t Graph5_fex1018[12] = {
   0,
   0,
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
   Double_t Graph5_fey1018[12] = {
   7.781243e-05,
   6.314083e-05,
   6.023711e-05,
   6.335334e-05,
   7.130567e-05,
   8.458775e-05,
   0.0001044737,
   0.0001333701,
   0.000180079,
   0.0002472131,
   0.0002770798,
   0.000573501};
   gre = new TGraphErrors(12,Graph5_fx1018,Graph5_fy1018,Graph5_fex1018,Graph5_fey1018);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ 39 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (j) } }");
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
   
   Double_t Graph0_fx1019[7] = {
   0.118616,
   0.2626228,
   0.4103139,
   0.5590989,
   0.733253,
   0.9825314,
   1.331953};
   Double_t Graph0_fy1019[7] = {
   0.005037129,
   0.01469468,
   0.02665598,
   0.03766082,
   0.04665845,
   0.05755734,
   0.06534525};
   Double_t Graph0_fex1019[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1019[7] = {
   2.230274e-05,
   0.0001708237,
   0.0004384748,
   0.0007605204,
   0.001211245,
   0.001750852,
   0.001761813};
   gre = new TGraphErrors(7,Graph0_fx1019,Graph0_fy1019,Graph0_fex1019,Graph0_fey1019);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1236;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01019 = new TH1F("Graph_Graph01019","",100,-0.07,1.7);
   Graph_Graph01019->SetMinimum(-0.01);
   Graph_Graph01019->SetMaximum(0.14);
   Graph_Graph01019->SetDirectory(0);
   Graph_Graph01019->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01019->SetLineColor(ci);
   Graph_Graph01019->GetXaxis()->SetNdivisions(505);
   Graph_Graph01019->GetXaxis()->SetLabelFont(42);
   Graph_Graph01019->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01019->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01019->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01019->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01019->GetXaxis()->SetTitleFont(42);
   Graph_Graph01019->GetYaxis()->SetNdivisions(505);
   Graph_Graph01019->GetYaxis()->SetLabelFont(42);
   Graph_Graph01019->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01019->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01019->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01019->GetYaxis()->SetTitleFont(42);
   Graph_Graph01019->GetZaxis()->SetLabelFont(42);
   Graph_Graph01019->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01019->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01019->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01019);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1020[7] = {
   0.118616,
   0.2626228,
   0.4103139,
   0.5590989,
   0.733253,
   0.9825314,
   1.331953};
   Double_t Graph1_fy1020[7] = {
   0.005037129,
   0.01469468,
   0.02665598,
   0.03766082,
   0.04665845,
   0.05755734,
   0.06534525};
   Double_t Graph1_fex1020[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1020[7] = {
   0.0001390376,
   0.0001469682,
   0.0002018209,
   0.0002985379,
   0.0004191028,
   0.0007057301,
   0.001881243};
   gre = new TGraphErrors(7,Graph1_fx1020,Graph1_fy1020,Graph1_fex1020,Graph1_fey1020);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1021[4] = {
   0.05574174,
   0.161274,
   0.2884718,
   0.4251425};
   Double_t Graph2_fy1021[4] = {
   0.003447792,
   0.01046118,
   0.01989127,
   0.02952246};
   Double_t Graph2_fex1021[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1021[4] = {
   2.230274e-05,
   0.0001708237,
   0.0004384748,
   0.0007605204};
   gre = new TGraphErrors(4,Graph2_fx1021,Graph2_fy1021,Graph2_fex1021,Graph2_fey1021);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1237;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1022[4] = {
   0.05574174,
   0.161274,
   0.2884718,
   0.4251425};
   Double_t Graph3_fy1022[4] = {
   0.003447792,
   0.01046118,
   0.01989127,
   0.02952246};
   Double_t Graph3_fex1022[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1022[4] = {
   0.000638912,
   0.0003693982,
   0.0003944274,
   0.0005409647};
   gre = new TGraphErrors(4,Graph3_fx1022,Graph3_fy1022,Graph3_fex1022,Graph3_fey1022);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1023[6] = {
   0.06771815,
   0.1323212,
   0.2082304,
   0.3055157,
   0.453935,
   0.6715842};
   Double_t Graph4_fy1023[6] = {
   0.002971178,
   0.009097679,
   0.01638545,
   0.0261832,
   0.03641013,
   0.0471785};
   Double_t Graph4_fex1023[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1023[6] = {
   9.298466e-05,
   0.0002386754,
   0.0004139749,
   0.0006593185,
   0.000953043,
   0.0009590094};
   gre = new TGraphErrors(6,Graph4_fx1023,Graph4_fy1023,Graph4_fex1023,Graph4_fey1023);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1238;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1024[6] = {
   0.06771815,
   0.1323212,
   0.2082304,
   0.3055157,
   0.453935,
   0.6715842};
   Double_t Graph5_fy1024[6] = {
   0.002971178,
   0.009097679,
   0.01638545,
   0.0261832,
   0.03641013,
   0.0471785};
   Double_t Graph5_fex1024[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1024[6] = {
   0.0002244522,
   0.0001810276,
   0.0001894904,
   0.0002093493,
   0.0002977808,
   0.0007309279};
   gre = new TGraphErrors(6,Graph5_fx1024,Graph5_fy1024,Graph5_fex1024,Graph5_fey1024);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (k) } }");
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
   
   Double_t v2_PionsPlusSys_fx1025[12] = {
   0.09528883,
   0.1850513,
   0.2814525,
   0.3796431,
   0.4785651,
   0.5779098,
   0.6774903,
   0.7771396,
   0.8768304,
   0.9766151,
   1.10935,
   1.333333};
   Double_t v2_PionsPlusSys_fy1025[12] = {
   0.0109774,
   0.02058219,
   0.02967175,
   0.03763206,
   0.04426548,
   0.04987042,
   0.05419425,
   0.05750309,
   0.06006695,
   0.06213681,
   0.063632,
   0.06600667};
   Double_t v2_PionsPlusSys_fex1025[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v2_PionsPlusSys_fey1025[12] = {
   1.584905e-05,
   0.0001195938,
   0.000223756,
   0.0003439022,
   0.0003973443,
   0.0004411095,
   0.0004176888,
   0.0005238904,
   0.0005784605,
   0.0007374537,
   0.0005386629,
   0.0009499251};
   gre = new TGraphErrors(12,v2_PionsPlusSys_fx1025,v2_PionsPlusSys_fy1025,v2_PionsPlusSys_fex1025,v2_PionsPlusSys_fey1025);
   gre->SetName("v2_PionsPlusSys");
   gre->SetTitle("");

   ci = 1218;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v2_PionsPlusSys1025 = new TH1F("Graph_v2_PionsPlusSys1025","",100,-0.07,1.7);
   Graph_v2_PionsPlusSys1025->SetMinimum(-0.01);
   Graph_v2_PionsPlusSys1025->SetMaximum(0.14);
   Graph_v2_PionsPlusSys1025->SetDirectory(0);
   Graph_v2_PionsPlusSys1025->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v2_PionsPlusSys1025->SetLineColor(ci);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetNdivisions(505);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetLabelFont(42);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetLabelOffset(0.01);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetLabelSize(0.1);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetTitleSize(0.035);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetTitleOffset(1);
   Graph_v2_PionsPlusSys1025->GetXaxis()->SetTitleFont(42);
   Graph_v2_PionsPlusSys1025->GetYaxis()->SetNdivisions(505);
   Graph_v2_PionsPlusSys1025->GetYaxis()->SetLabelFont(42);
   Graph_v2_PionsPlusSys1025->GetYaxis()->SetLabelOffset(0.01);
   Graph_v2_PionsPlusSys1025->GetYaxis()->SetLabelSize(0.1);
   Graph_v2_PionsPlusSys1025->GetYaxis()->SetTitleSize(0.035);
   Graph_v2_PionsPlusSys1025->GetYaxis()->SetTitleFont(42);
   Graph_v2_PionsPlusSys1025->GetZaxis()->SetLabelFont(42);
   Graph_v2_PionsPlusSys1025->GetZaxis()->SetLabelSize(0.035);
   Graph_v2_PionsPlusSys1025->GetZaxis()->SetTitleSize(0.035);
   Graph_v2_PionsPlusSys1025->GetZaxis()->SetTitleOffset(1);
   Graph_v2_PionsPlusSys1025->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v2_PionsPlusSys1025);
   
   gre->Draw("ae5");
   
   Double_t v2_PionsPlus_fx1026[12] = {
   0.09528883,
   0.1850513,
   0.2814525,
   0.3796431,
   0.4785651,
   0.5779098,
   0.6774903,
   0.7771396,
   0.8768304,
   0.9766151,
   1.10935,
   1.333333};
   Double_t v2_PionsPlus_fy1026[12] = {
   0.0109774,
   0.02058219,
   0.02967175,
   0.03763206,
   0.04426548,
   0.04987042,
   0.05419425,
   0.05750309,
   0.06006695,
   0.06213681,
   0.063632,
   0.06600667};
   Double_t v2_PionsPlus_fex1026[12] = {
   0,
   0,
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
   Double_t v2_PionsPlus_fey1026[12] = {
   2.062707e-05,
   1.946026e-05,
   2.273383e-05,
   2.857639e-05,
   3.725459e-05,
   4.951752e-05,
   6.63082e-05,
   8.926915e-05,
   0.0001209254,
   0.0001681356,
   0.0001966803,
   0.0003673884};
   gre = new TGraphErrors(12,v2_PionsPlus_fx1026,v2_PionsPlus_fy1026,v2_PionsPlus_fex1026,v2_PionsPlus_fey1026);
   gre->SetName("v2_PionsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v2_KaonsPlusSys_fx1027[7] = {
   0.05189581,
   0.1059506,
   0.1795996,
   0.2626166,
   0.3510418,
   0.4429427,
   0.5369801};
   Double_t v2_KaonsPlusSys_fy1027[7] = {
   0.006775815,
   0.01456681,
   0.02351483,
   0.0315123,
   0.03841991,
   0.04392771,
   0.04847321};
   Double_t v2_KaonsPlusSys_fex1027[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v2_KaonsPlusSys_fey1027[7] = {
   1.584905e-05,
   0.0001195938,
   0.000223756,
   0.0003439022,
   0.0003973443,
   0.0004411095,
   0.0004176888};
   gre = new TGraphErrors(7,v2_KaonsPlusSys_fx1027,v2_KaonsPlusSys_fy1027,v2_KaonsPlusSys_fex1027,v2_KaonsPlusSys_fey1027);
   gre->SetName("v2_KaonsPlusSys");
   gre->SetTitle("Graph");

   ci = 1219;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t v2_KaonsPlus_fx1028[7] = {
   0.05189581,
   0.1059506,
   0.1795996,
   0.2626166,
   0.3510418,
   0.4429427,
   0.5369801};
   Double_t v2_KaonsPlus_fy1028[7] = {
   0.006775815,
   0.01456681,
   0.02351483,
   0.0315123,
   0.03841991,
   0.04392771,
   0.04847321};
   Double_t v2_KaonsPlus_fex1028[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v2_KaonsPlus_fey1028[7] = {
   0.0001158746,
   6.021294e-05,
   5.236482e-05,
   5.656714e-05,
   6.884137e-05,
   8.935398e-05,
   0.0001193771};
   gre = new TGraphErrors(7,v2_KaonsPlus_fx1028,v2_KaonsPlus_fy1028,v2_KaonsPlus_fex1028,v2_KaonsPlus_fey1028);
   gre->SetName("v2_KaonsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v2_ProtonsPlusSys_fx1029[12] = {
   0.05937957,
   0.09811051,
   0.1433086,
   0.1933069,
   0.2468603,
   0.3029507,
   0.3609652,
   0.4204738,
   0.481154,
   0.5427426,
   0.6261109,
   0.7428787};
   Double_t v2_ProtonsPlusSys_fy1029[12] = {
   0.00816245,
   0.01419601,
   0.02090447,
   0.02738998,
   0.0332111,
   0.03846594,
   0.04301524,
   0.04675684,
   0.05032218,
   0.05255762,
   0.05516661,
   0.05856754};
   Double_t v2_ProtonsPlusSys_fex1029[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v2_ProtonsPlusSys_fey1029[12] = {
   0.0001208124,
   0.0001916824,
   0.0002220367,
   0.0003041752,
   0.0002728362,
   0.0003444558,
   0.0003352781,
   0.0003875057,
   0.0004712475,
   0.0004270691,
   0.0005841725,
   0.0004516437};
   gre = new TGraphErrors(12,v2_ProtonsPlusSys_fx1029,v2_ProtonsPlusSys_fy1029,v2_ProtonsPlusSys_fex1029,v2_ProtonsPlusSys_fey1029);
   gre->SetName("v2_ProtonsPlusSys");
   gre->SetTitle("Graph");

   ci = 1220;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t v2_ProtonsPlus_fx1030[12] = {
   0.05937957,
   0.09811051,
   0.1433086,
   0.1933069,
   0.2468603,
   0.3029507,
   0.3609652,
   0.4204738,
   0.481154,
   0.5427426,
   0.6261109,
   0.7428787};
   Double_t v2_ProtonsPlus_fy1030[12] = {
   0.00816245,
   0.01419601,
   0.02090447,
   0.02738998,
   0.0332111,
   0.03846594,
   0.04301524,
   0.04675684,
   0.05032218,
   0.05255762,
   0.05516661,
   0.05856754};
   Double_t v2_ProtonsPlus_fex1030[12] = {
   0,
   0,
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
   Double_t v2_ProtonsPlus_fey1030[12] = {
   3.660993e-05,
   3.005283e-05,
   2.908196e-05,
   3.124025e-05,
   3.588961e-05,
   4.317952e-05,
   5.397011e-05,
   6.977591e-05,
   9.541464e-05,
   0.0001328061,
   0.0001516839,
   0.0003239383};
   gre = new TGraphErrors(12,v2_ProtonsPlus_fx1030,v2_ProtonsPlus_fy1030,v2_ProtonsPlus_fex1030,v2_ProtonsPlus_fey1030);
   gre->SetName("v2_ProtonsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ 27 GeV Run18 } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (h) } }");
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
   
   Double_t v3_PionsPlusSys_fx1031[7] = {
   0.1145152,
   0.2504012,
   0.3970032,
   0.5456162,
   0.7100327,
   0.9325247,
   1.249186};
   Double_t v3_PionsPlusSys_fy1031[7] = {
   0.004706258,
   0.01380302,
   0.0249383,
   0.03536189,
   0.0445131,
   0.05332376,
   0.06010782};
   Double_t v3_PionsPlusSys_fex1031[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v3_PionsPlusSys_fey1031[7] = {
   6.139281e-05,
   0.0001294571,
   0.0004247672,
   0.0007949368,
   0.001210882,
   0.001829868,
   0.002364419};
   gre = new TGraphErrors(7,v3_PionsPlusSys_fx1031,v3_PionsPlusSys_fy1031,v3_PionsPlusSys_fex1031,v3_PionsPlusSys_fey1031);
   gre->SetName("v3_PionsPlusSys");
   gre->SetTitle("");

   ci = 1224;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v3_PionsPlusSys1031 = new TH1F("Graph_v3_PionsPlusSys1031","",100,-0.07,1.7);
   Graph_v3_PionsPlusSys1031->SetMinimum(-0.01);
   Graph_v3_PionsPlusSys1031->SetMaximum(0.14);
   Graph_v3_PionsPlusSys1031->SetDirectory(0);
   Graph_v3_PionsPlusSys1031->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v3_PionsPlusSys1031->SetLineColor(ci);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetNdivisions(505);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetLabelFont(42);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetLabelSize(0.1);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetTitleSize(0.035);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetTitleOffset(1);
   Graph_v3_PionsPlusSys1031->GetXaxis()->SetTitleFont(42);
   Graph_v3_PionsPlusSys1031->GetYaxis()->SetNdivisions(505);
   Graph_v3_PionsPlusSys1031->GetYaxis()->SetLabelFont(42);
   Graph_v3_PionsPlusSys1031->GetYaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsPlusSys1031->GetYaxis()->SetLabelSize(0.1);
   Graph_v3_PionsPlusSys1031->GetYaxis()->SetTitleSize(0.035);
   Graph_v3_PionsPlusSys1031->GetYaxis()->SetTitleFont(42);
   Graph_v3_PionsPlusSys1031->GetZaxis()->SetLabelFont(42);
   Graph_v3_PionsPlusSys1031->GetZaxis()->SetLabelSize(0.035);
   Graph_v3_PionsPlusSys1031->GetZaxis()->SetTitleSize(0.035);
   Graph_v3_PionsPlusSys1031->GetZaxis()->SetTitleOffset(1);
   Graph_v3_PionsPlusSys1031->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v3_PionsPlusSys1031);
   
   gre->Draw("ae5");
   
   Double_t v3_PionsPlus_fx1032[7] = {
   0.1145152,
   0.2504012,
   0.3970032,
   0.5456162,
   0.7100327,
   0.9325247,
   1.249186};
   Double_t v3_PionsPlus_fy1032[7] = {
   0.004706258,
   0.01380302,
   0.0249383,
   0.03536189,
   0.0445131,
   0.05332376,
   0.06010782};
   Double_t v3_PionsPlus_fex1032[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_PionsPlus_fey1032[7] = {
   8.054349e-05,
   8.607775e-05,
   0.0001192317,
   0.0001787886,
   0.0002543248,
   0.0004345113,
   0.001200984};
   gre = new TGraphErrors(7,v3_PionsPlus_fx1032,v3_PionsPlus_fy1032,v3_PionsPlus_fex1032,v3_PionsPlus_fey1032);
   gre->SetName("v3_PionsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v3_KaonsPlusSys_fx1033[4] = {
   0.07041978,
   0.1587897,
   0.2792962,
   0.4131061};
   Double_t v3_KaonsPlusSys_fy1033[4] = {
   0.003013752,
   0.009798266,
   0.01878821,
   0.02804179};
   Double_t v3_KaonsPlusSys_fex1033[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v3_KaonsPlusSys_fey1033[4] = {
   6.139281e-05,
   0.0001294571,
   0.0004247672,
   0.0007949368};
   gre = new TGraphErrors(4,v3_KaonsPlusSys_fx1033,v3_KaonsPlusSys_fy1033,v3_KaonsPlusSys_fex1033,v3_KaonsPlusSys_fey1033);
   gre->SetName("v3_KaonsPlusSys");
   gre->SetTitle("Graph");

   ci = 1225;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t v3_KaonsPlus_fx1034[4] = {
   0.07041978,
   0.1587897,
   0.2792962,
   0.4131061};
   Double_t v3_KaonsPlus_fy1034[4] = {
   0.003013752,
   0.009798266,
   0.01878821,
   0.02804179};
   Double_t v3_KaonsPlus_fex1034[4] = {
   0,
   0,
   0,
   0};
   Double_t v3_KaonsPlus_fey1034[4] = {
   0.000352643,
   0.000208024,
   0.0002262449,
   0.0003150495};
   gre = new TGraphErrors(4,v3_KaonsPlus_fx1034,v3_KaonsPlus_fy1034,v3_KaonsPlus_fex1034,v3_KaonsPlus_fey1034);
   gre->SetName("v3_KaonsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v3_ProtonsPlusSys_fx1035[6] = {
   0.06915363,
   0.1305031,
   0.2041716,
   0.2955012,
   0.4265553,
   0.6201829};
   Double_t v3_ProtonsPlusSys_fy1035[6] = {
   0.002935384,
   0.008725173,
   0.01650707,
   0.02538434,
   0.03559873,
   0.04604214};
   Double_t v3_ProtonsPlusSys_fex1035[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v3_ProtonsPlusSys_fey1035[6] = {
   7.046752e-05,
   0.000231214,
   0.0004327088,
   0.0006591208,
   0.000996054,
   0.001287027};
   gre = new TGraphErrors(6,v3_ProtonsPlusSys_fx1035,v3_ProtonsPlusSys_fy1035,v3_ProtonsPlusSys_fex1035,v3_ProtonsPlusSys_fey1035);
   gre->SetName("v3_ProtonsPlusSys");
   gre->SetTitle("Graph");

   ci = 1226;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t v3_ProtonsPlus_fx1036[6] = {
   0.06915363,
   0.1305031,
   0.2041716,
   0.2955012,
   0.4265553,
   0.6201829};
   Double_t v3_ProtonsPlus_fy1036[6] = {
   0.002935384,
   0.008725173,
   0.01650707,
   0.02538434,
   0.03559873,
   0.04604214};
   Double_t v3_ProtonsPlus_fex1036[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_ProtonsPlus_fey1036[6] = {
   0.0001126975,
   9.27167e-05,
   9.9947e-05,
   0.0001133915,
   0.0001658396,
   0.0004245534};
   gre = new TGraphErrors(6,v3_ProtonsPlus_fx1036,v3_ProtonsPlus_fy1036,v3_ProtonsPlus_fex1036,v3_ProtonsPlus_fey1036);
   gre->SetName("v3_ProtonsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (i) } }");
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
   
   Double_t Graph0_fx1037[11] = {
   0.09516891,
   0.1849005,
   0.2812766,
   0.3794578,
   0.4783639,
   0.5776665,
   0.6771454,
   0.7767181,
   0.9080008,
   1.107965,
   1.329889};
   Double_t Graph0_fy1037[11] = {
   0.01069541,
   0.0200267,
   0.02867148,
   0.03613934,
   0.04245626,
   0.04689597,
   0.05167925,
   0.05439116,
   0.05664127,
   0.05975151,
   0.05673384};
   Double_t Graph0_fex1037[11] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1037[11] = {
   1.584905e-05,
   0.0001195938,
   0.000223756,
   0.0003439022,
   0.0003973443,
   0.0004411095,
   0.0004176888,
   0.0005238904,
   0.0006350451,
   0.0005386629,
   0.0009499251};
   gre = new TGraphErrors(11,Graph0_fx1037,Graph0_fy1037,Graph0_fex1037,Graph0_fey1037);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1206;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01037 = new TH1F("Graph_Graph01037","",100,-0.07,1.7);
   Graph_Graph01037->SetMinimum(-0.01);
   Graph_Graph01037->SetMaximum(0.14);
   Graph_Graph01037->SetDirectory(0);
   Graph_Graph01037->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01037->SetLineColor(ci);
   Graph_Graph01037->GetXaxis()->SetNdivisions(505);
   Graph_Graph01037->GetXaxis()->SetLabelFont(42);
   Graph_Graph01037->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01037->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01037->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01037->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01037->GetXaxis()->SetTitleFont(42);
   Graph_Graph01037->GetYaxis()->SetNdivisions(505);
   Graph_Graph01037->GetYaxis()->SetLabelFont(42);
   Graph_Graph01037->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01037->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01037->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01037->GetYaxis()->SetTitleFont(42);
   Graph_Graph01037->GetZaxis()->SetLabelFont(42);
   Graph_Graph01037->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01037->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01037->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01037->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01037);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1038[11] = {
   0.09516891,
   0.1849005,
   0.2812766,
   0.3794578,
   0.4783639,
   0.5776665,
   0.6771454,
   0.7767181,
   0.9080008,
   1.107965,
   1.329889};
   Double_t Graph1_fy1038[11] = {
   0.01069541,
   0.0200267,
   0.02867148,
   0.03613934,
   0.04245626,
   0.04689597,
   0.05167925,
   0.05439116,
   0.05664127,
   0.05975151,
   0.05673384};
   Double_t Graph1_fex1038[11] = {
   0,
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
   Double_t Graph1_fey1038[11] = {
   9.605166e-05,
   9.146851e-05,
   0.0001078959,
   0.0001371262,
   0.000181216,
   0.000244113,
   0.0003327575,
   0.0004588329,
   0.0005223711,
   0.001101157,
   0.002177307};
   gre = new TGraphErrors(11,Graph1_fx1038,Graph1_fy1038,Graph1_fex1038,Graph1_fey1038);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1039[7] = {
   0.05202543,
   0.105835,
   0.1794275,
   0.2623387,
   0.3507553,
   0.4426718,
   0.5367071};
   Double_t Graph2_fy1039[7] = {
   0.00686424,
   0.01410318,
   0.02324729,
   0.03068393,
   0.03667279,
   0.04197784,
   0.04589288};
   Double_t Graph2_fex1039[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1039[7] = {
   1.584905e-05,
   0.0001195938,
   0.000223756,
   0.0003439022,
   0.0003973443,
   0.0004411095,
   0.0004176888};
   gre = new TGraphErrors(7,Graph2_fx1039,Graph2_fy1039,Graph2_fex1039,Graph2_fey1039);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1207;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1040[7] = {
   0.05202543,
   0.105835,
   0.1794275,
   0.2623387,
   0.3507553,
   0.4426718,
   0.5367071};
   Double_t Graph3_fy1040[7] = {
   0.00686424,
   0.01410318,
   0.02324729,
   0.03068393,
   0.03667279,
   0.04197784,
   0.04589288};
   Double_t Graph3_fex1040[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1040[7] = {
   0.0005298614,
   0.000276444,
   0.0002430696,
   0.0002666612,
   0.0003312519,
   0.0004376269,
   0.0005958656};
   gre = new TGraphErrors(7,Graph3_fx1040,Graph3_fy1040,Graph3_fex1040,Graph3_fey1040);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1041[12] = {
   0.05932186,
   0.09804898,
   0.1432408,
   0.1932634,
   0.2467388,
   0.3027899,
   0.3607906,
   0.4203191,
   0.4809582,
   0.5425924,
   0.6254593,
   0.7422849};
   Double_t Graph4_fy1041[12] = {
   0.008127675,
   0.01414372,
   0.02066907,
   0.02702061,
   0.03288368,
   0.03763181,
   0.04166226,
   0.04523478,
   0.04844581,
   0.05045447,
   0.05389929,
   0.05379218};
   Double_t Graph4_fex1041[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1041[12] = {
   0.0001208124,
   0.0001916824,
   0.0002220367,
   0.0003041752,
   0.0002728362,
   0.0003444558,
   0.0003352781,
   0.0003875057,
   0.0004712475,
   0.0004270691,
   0.0005841725,
   0.0004516437};
   gre = new TGraphErrors(12,Graph4_fx1041,Graph4_fy1041,Graph4_fex1041,Graph4_fey1041);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1208;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1042[12] = {
   0.05932186,
   0.09804898,
   0.1432408,
   0.1932634,
   0.2467388,
   0.3027899,
   0.3607906,
   0.4203191,
   0.4809582,
   0.5425924,
   0.6254593,
   0.7422849};
   Double_t Graph5_fy1042[12] = {
   0.008127675,
   0.01414372,
   0.02066907,
   0.02702061,
   0.03288368,
   0.03763181,
   0.04166226,
   0.04523478,
   0.04844581,
   0.05045447,
   0.05389929,
   0.05379218};
   Double_t Graph5_fex1042[12] = {
   0,
   0,
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
   Double_t Graph5_fey1042[12] = {
   0.0001523978,
   0.0001265657,
   0.000123525,
   0.0001335681,
   0.00015475,
   0.000189132,
   0.0002407009,
   0.0003164555,
   0.0004399088,
   0.0006227573,
   0.0007279238,
   0.001610732};
   gre = new TGraphErrors(12,Graph5_fx1042,Graph5_fy1042,Graph5_fex1042,Graph5_fey1042);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ 19.6 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (e) } }");
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
   
   Double_t Graph0_fx1043[7] = {
   0.1142238,
   0.2500579,
   0.3965541,
   0.5451409,
   0.7086415,
   0.9295086,
   1.243915};
   Double_t Graph0_fy1043[7] = {
   0.004487694,
   0.01304595,
   0.02322892,
   0.03350112,
   0.04257162,
   0.05618664,
   0.04651511};
   Double_t Graph0_fex1043[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1043[7] = {
   0.0001063759,
   0.0001083361,
   0.0004232109,
   0.0008465712,
   0.001603034,
   0.001434776,
   0.002334028};
   gre = new TGraphErrors(7,Graph0_fx1043,Graph0_fy1043,Graph0_fex1043,Graph0_fey1043);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1212;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01043 = new TH1F("Graph_Graph01043","",100,-0.07,1.7);
   Graph_Graph01043->SetMinimum(-0.01);
   Graph_Graph01043->SetMaximum(0.14);
   Graph_Graph01043->SetDirectory(0);
   Graph_Graph01043->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01043->SetLineColor(ci);
   Graph_Graph01043->GetXaxis()->SetNdivisions(505);
   Graph_Graph01043->GetXaxis()->SetLabelFont(42);
   Graph_Graph01043->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01043->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01043->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01043->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01043->GetXaxis()->SetTitleFont(42);
   Graph_Graph01043->GetYaxis()->SetNdivisions(505);
   Graph_Graph01043->GetYaxis()->SetLabelFont(42);
   Graph_Graph01043->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01043->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01043->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01043->GetYaxis()->SetTitleFont(42);
   Graph_Graph01043->GetZaxis()->SetLabelFont(42);
   Graph_Graph01043->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01043->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01043->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01043->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01043);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1044[7] = {
   0.1142238,
   0.2500579,
   0.3965541,
   0.5451409,
   0.7086415,
   0.9295086,
   1.243915};
   Double_t Graph1_fy1044[7] = {
   0.004487694,
   0.01304595,
   0.02322892,
   0.03350112,
   0.04257162,
   0.05618664,
   0.04651511};
   Double_t Graph1_fex1044[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1044[7] = {
   0.0003917532,
   0.0004240692,
   0.0005962163,
   0.0009100246,
   0.001331606,
   0.002396152,
   0.007108922};
   gre = new TGraphErrors(7,Graph1_fx1044,Graph1_fy1044,Graph1_fex1044,Graph1_fey1044);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1045[4] = {
   0.07047391,
   0.1584654,
   0.2786613,
   0.4125308};
   Double_t Graph2_fy1045[4] = {
   0.00264668,
   0.008291643,
   0.01819162,
   0.02640658};
   Double_t Graph2_fex1045[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1045[4] = {
   0.0001063759,
   0.0001083361,
   0.0004232109,
   0.0008465712};
   gre = new TGraphErrors(4,Graph2_fx1045,Graph2_fy1045,Graph2_fex1045,Graph2_fey1045);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1213;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1046[4] = {
   0.07047391,
   0.1584654,
   0.2786613,
   0.4125308};
   Double_t Graph3_fy1046[4] = {
   0.00264668,
   0.008291643,
   0.01819162,
   0.02640658};
   Double_t Graph3_fex1046[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1046[4] = {
   0.001678268,
   0.0009992392,
   0.001108316,
   0.001585337};
   gre = new TGraphErrors(4,Graph3_fx1046,Graph3_fy1046,Graph3_fex1046,Graph3_fey1046);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1047[6] = {
   0.06899906,
   0.1303631,
   0.2040481,
   0.2948984,
   0.4253138,
   0.618036};
   Double_t Graph4_fy1047[6] = {
   0.003301265,
   0.008017048,
   0.01615098,
   0.02466579,
   0.03622282,
   0.04335219};
   Double_t Graph4_fex1047[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1047[6] = {
   5.897068e-05,
   0.0002303669,
   0.000460815,
   0.000872581,
   0.000780993,
   0.001270484};
   gre = new TGraphErrors(6,Graph4_fx1047,Graph4_fy1047,Graph4_fex1047,Graph4_fey1047);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1214;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1048[6] = {
   0.06899906,
   0.1303631,
   0.2040481,
   0.2948984,
   0.4253138,
   0.618036};
   Double_t Graph5_fy1048[6] = {
   0.003301265,
   0.008017048,
   0.01615098,
   0.02466579,
   0.03622282,
   0.04335219};
   Double_t Graph5_fex1048[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1048[6] = {
   0.0004891715,
   0.000406867,
   0.0004424296,
   0.0005123127,
   0.000776945,
   0.002091407};
   gre = new TGraphErrors(6,Graph5_fx1048,Graph5_fy1048,Graph5_fex1048,Graph5_fey1048);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ STAR Preliminary } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (f) } }");
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
   
   Double_t Graph0_fx1049[12] = {
   0.09435247,
   0.1847129,
   0.2810763,
   0.3792888,
   0.4782333,
   0.5775921,
   0.6770824,
   0.7766862,
   0.876339,
   0.9760625,
   1.075819,
   1.175559};
   Double_t Graph0_fy1049[12] = {
   0.01115109,
   0.02021511,
   0.02829318,
   0.03552892,
   0.04068352,
   0.04580325,
   0.04901487,
   0.05189884,
   0.05341319,
   0.05551612,
   0.05790558,
   0.0604656};
   Double_t Graph0_fex1049[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1049[12] = {
   5.689819e-05,
   0.0001313649,
   0.0002699769,
   0.0002672747,
   0.0004404105,
   0.0003388755,
   0.0004010478,
   0.0004347586,
   0.0007584275,
   0.0004084966,
   0.0009470074,
   0.0003226002};
   gre = new TGraphErrors(12,Graph0_fx1049,Graph0_fy1049,Graph0_fex1049,Graph0_fey1049);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1194;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01049 = new TH1F("Graph_Graph01049","",100,-0.07,1.7);
   Graph_Graph01049->SetMinimum(-0.01);
   Graph_Graph01049->SetMaximum(0.14);
   Graph_Graph01049->SetDirectory(0);
   Graph_Graph01049->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01049->SetLineColor(ci);
   Graph_Graph01049->GetXaxis()->SetNdivisions(505);
   Graph_Graph01049->GetXaxis()->SetLabelFont(42);
   Graph_Graph01049->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01049->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01049->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01049->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01049->GetXaxis()->SetTitleFont(42);
   Graph_Graph01049->GetYaxis()->SetNdivisions(505);
   Graph_Graph01049->GetYaxis()->SetLabelFont(42);
   Graph_Graph01049->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01049->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01049->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01049->GetYaxis()->SetTitleFont(42);
   Graph_Graph01049->GetZaxis()->SetLabelFont(42);
   Graph_Graph01049->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01049->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01049->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01049->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01049);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1050[12] = {
   0.09435247,
   0.1847129,
   0.2810763,
   0.3792888,
   0.4782333,
   0.5775921,
   0.6770824,
   0.7766862,
   0.876339,
   0.9760625,
   1.075819,
   1.175559};
   Double_t Graph1_fy1050[12] = {
   0.01115109,
   0.02021511,
   0.02829318,
   0.03552892,
   0.04068352,
   0.04580325,
   0.04901487,
   0.05189884,
   0.05341319,
   0.05551612,
   0.05790558,
   0.0604656};
   Double_t Graph1_fex1050[12] = {
   0,
   0,
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
   Double_t Graph1_fey1050[12] = {
   0.0001152917,
   0.0001119818,
   0.0001336857,
   0.0001719771,
   0.0002293153,
   0.0003106154,
   0.0004254119,
   0.0005882492,
   0.0008211406,
   0.001183823,
   0.001755434,
   0.002607958};
   gre = new TGraphErrors(12,Graph1_fx1050,Graph1_fy1050,Graph1_fex1050,Graph1_fey1050);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1051[7] = {
   0.05165415,
   0.1057462,
   0.1794032,
   0.2622001,
   0.350434,
   0.4422856,
   0.5363196};
   Double_t Graph2_fy1051[7] = {
   0.007989443,
   0.01505986,
   0.02290984,
   0.0305899,
   0.03628654,
   0.04166119,
   0.04530087};
   Double_t Graph2_fex1051[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1051[7] = {
   5.689819e-05,
   0.0001313649,
   0.0002699769,
   0.0002672747,
   0.0004404105,
   0.0003388755,
   0.0004010478};
   gre = new TGraphErrors(7,Graph2_fx1051,Graph2_fy1051,Graph2_fex1051,Graph2_fey1051);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1195;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1052[7] = {
   0.05165415,
   0.1057462,
   0.1794032,
   0.2622001,
   0.350434,
   0.4422856,
   0.5363196};
   Double_t Graph3_fy1052[7] = {
   0.007989443,
   0.01505986,
   0.02290984,
   0.0305899,
   0.03628654,
   0.04166119,
   0.04530087};
   Double_t Graph3_fex1052[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1052[7] = {
   0.0006346934,
   0.0003377854,
   0.0002979462,
   0.0003286056,
   0.0004144904,
   0.0005592459,
   0.0007796906};
   gre = new TGraphErrors(7,Graph3_fx1052,Graph3_fy1052,Graph3_fex1052,Graph3_fey1052);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1053[12] = {
   0.05911425,
   0.09790534,
   0.1431142,
   0.1931652,
   0.2466094,
   0.3026274,
   0.3606088,
   0.4201263,
   0.4808553,
   0.5424111,
   0.6047688,
   0.6677407};
   Double_t Graph4_fy1053[12] = {
   0.009046926,
   0.01458153,
   0.02096612,
   0.02715832,
   0.03221792,
   0.03691113,
   0.04060524,
   0.04425864,
   0.04638489,
   0.04878789,
   0.04910166,
   0.0517339};
   Double_t Graph4_fex1053[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1053[12] = {
   0.0001270662,
   0.0001910106,
   0.000246968,
   0.0002677429,
   0.0002326449,
   0.0002305244,
   0.0004703896,
   0.0003560362,
   0.0004764418,
   0.0001917963,
   0.0004272441,
   0.0005181862};
   gre = new TGraphErrors(12,Graph4_fx1053,Graph4_fy1053,Graph4_fex1053,Graph4_fey1053);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1196;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1054[12] = {
   0.05911425,
   0.09790534,
   0.1431142,
   0.1931652,
   0.2466094,
   0.3026274,
   0.3606088,
   0.4201263,
   0.4808553,
   0.5424111,
   0.6047688,
   0.6677407};
   Double_t Graph5_fy1054[12] = {
   0.009046926,
   0.01458153,
   0.02096612,
   0.02715832,
   0.03221792,
   0.03691113,
   0.04060524,
   0.04425864,
   0.04638489,
   0.04878789,
   0.04910166,
   0.0517339};
   Double_t Graph5_fex1054[12] = {
   0,
   0,
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
   Double_t Graph5_fey1054[12] = {
   0.0001579205,
   0.0001341836,
   0.0001330622,
   0.0001458122,
   0.0001711643,
   0.0002124343,
   0.0002747241,
   0.0003683167,
   0.0005213511,
   0.0007503439,
   0.001091079,
   0.001586102};
   gre = new TGraphErrors(12,Graph5_fx1054,Graph5_fy1054,Graph5_fex1054,Graph5_fey1054);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ 14.5 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (c) } }");
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
   
   Double_t Graph0_fx1055[7] = {
   0.1130396,
   0.2496217,
   0.3962214,
   0.5449793,
   0.7084569,
   0.9283887,
   1.240579};
   Double_t Graph0_fy1055[7] = {
   0.005397877,
   0.0120084,
   0.02104125,
   0.02862224,
   0.0380274,
   0.055165,
   0.03827256};
   Double_t Graph0_fex1055[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1055[7] = {
   0.0001059322,
   8.210638e-05,
   0.0003794254,
   0.0009772539,
   0.001387346,
   0.000969404,
   0.004886483};
   gre = new TGraphErrors(7,Graph0_fx1055,Graph0_fy1055,Graph0_fex1055,Graph0_fey1055);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1200;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01055 = new TH1F("Graph_Graph01055","",100,-0.07,1.7);
   Graph_Graph01055->SetMinimum(-0.01);
   Graph_Graph01055->SetMaximum(0.14);
   Graph_Graph01055->SetDirectory(0);
   Graph_Graph01055->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01055->SetLineColor(ci);
   Graph_Graph01055->GetXaxis()->SetNdivisions(505);
   Graph_Graph01055->GetXaxis()->SetLabelFont(42);
   Graph_Graph01055->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01055->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01055->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01055->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01055->GetXaxis()->SetTitleFont(42);
   Graph_Graph01055->GetYaxis()->SetNdivisions(505);
   Graph_Graph01055->GetYaxis()->SetLabelFont(42);
   Graph_Graph01055->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01055->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01055->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01055->GetYaxis()->SetTitleFont(42);
   Graph_Graph01055->GetZaxis()->SetLabelFont(42);
   Graph_Graph01055->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01055->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01055->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01055->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01055);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1056[7] = {
   0.1130396,
   0.2496217,
   0.3962214,
   0.5449793,
   0.7084569,
   0.9283887,
   1.240579};
   Double_t Graph1_fy1056[7] = {
   0.005397877,
   0.0120084,
   0.02104125,
   0.02862224,
   0.0380274,
   0.055165,
   0.03827256};
   Double_t Graph1_fex1056[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1056[7] = {
   0.0005193648,
   0.0005756434,
   0.0008227397,
   0.001265192,
   0.001855801,
   0.003345605,
   0.01032005};
   gre = new TGraphErrors(7,Graph1_fx1056,Graph1_fy1056,Graph1_fex1056,Graph1_fey1056);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1057[4] = {
   0.0699,
   0.1583849,
   0.2782616,
   0.4118256};
   Double_t Graph2_fy1057[4] = {
   0.0020982,
   0.01045743,
   0.01734079,
   0.02555524};
   Double_t Graph2_fex1057[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1057[4] = {
   0.0001059322,
   8.210638e-05,
   0.0003794254,
   0.0009772539};
   gre = new TGraphErrors(4,Graph2_fx1057,Graph2_fy1057,Graph2_fex1057,Graph2_fey1057);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1201;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1058[4] = {
   0.0699,
   0.1583849,
   0.2782616,
   0.4118256};
   Double_t Graph3_fy1058[4] = {
   0.0020982,
   0.01045743,
   0.01734079,
   0.02555524};
   Double_t Graph3_fex1058[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1058[4] = {
   0.002217453,
   0.001337378,
   0.001492499,
   0.002183225};
   gre = new TGraphErrors(4,Graph3_fx1058,Graph3_fy1058,Graph3_fex1058,Graph3_fey1058);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1059[6] = {
   0.0685966,
   0.1300904,
   0.2038061,
   0.2943369,
   0.4240041,
   0.6163785};
   Double_t Graph4_fy1059[6] = {
   0.002841211,
   0.009746579,
   0.01606644,
   0.02469889,
   0.03218056,
   0.04162343};
   Double_t Graph4_fex1059[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1059[6] = {
   4.469305e-05,
   0.000206533,
   0.0005319497,
   0.0007551756,
   0.0005276767,
   0.002659864};
   gre = new TGraphErrors(6,Graph4_fx1059,Graph4_fy1059,Graph4_fex1059,Graph4_fey1059);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1202;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1060[6] = {
   0.0685966,
   0.1300904,
   0.2038061,
   0.2943369,
   0.4240041,
   0.6163785};
   Double_t Graph5_fy1060[6] = {
   0.002841211,
   0.009746579,
   0.01606644,
   0.02469889,
   0.03218056,
   0.04162343};
   Double_t Graph5_fex1060[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1060[6] = {
   0.0005563242,
   0.000475942,
   0.000527359,
   0.0006235487,
   0.0009781962,
   0.002762441};
   gre = new TGraphErrors(6,Graph5_fx1060,Graph5_fy1060,Graph5_fex1060,Graph5_fey1060);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
   
   TLegend *leg = new TLegend(0.1,0.4,0.3,0.9);
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph1","  #pi^{+}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph3","  K^{+}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph5","  p","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (d) } }");
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
   
   Double_t Graph0_fx1061[8] = {
   0.09497304,
   0.1846783,
   0.2810941,
   0.3792033,
   0.5090749,
   0.7076816,
   0.8761703,
   1.006298};
   Double_t Graph0_fy1061[8] = {
   0.01047275,
   0.01912179,
   0.02643848,
   0.03280433,
   0.03922913,
   0.04618038,
   0.05225156,
   0.04608841};
   Double_t Graph0_fex1061[8] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1061[8] = {
   5.045821e-05,
   0.0001248944,
   0.0001546414,
   0.0002982466,
   0.0004348228,
   0.0005114478,
   0.0005773772,
   0.0003980557};
   gre = new TGraphErrors(8,Graph0_fx1061,Graph0_fy1061,Graph0_fex1061,Graph0_fey1061);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1182;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01061 = new TH1F("Graph_Graph01061","",100,-0.07,1.7);
   Graph_Graph01061->SetMinimum(-0.01);
   Graph_Graph01061->SetMaximum(0.14);
   Graph_Graph01061->SetDirectory(0);
   Graph_Graph01061->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01061->SetLineColor(ci);
   Graph_Graph01061->GetXaxis()->SetNdivisions(505);
   Graph_Graph01061->GetXaxis()->SetLabelFont(42);
   Graph_Graph01061->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01061->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01061->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01061->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01061->GetXaxis()->SetTitleFont(42);
   Graph_Graph01061->GetYaxis()->SetNdivisions(505);
   Graph_Graph01061->GetYaxis()->SetLabelFont(42);
   Graph_Graph01061->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01061->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01061->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01061->GetYaxis()->SetTitleFont(42);
   Graph_Graph01061->GetZaxis()->SetLabelFont(42);
   Graph_Graph01061->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01061->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01061->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01061->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01061);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1062[8] = {
   0.09497304,
   0.1846783,
   0.2810941,
   0.3792033,
   0.5090749,
   0.7076816,
   0.8761703,
   1.006298};
   Double_t Graph1_fy1062[8] = {
   0.01047275,
   0.01912179,
   0.02643848,
   0.03280433,
   0.03922913,
   0.04618038,
   0.05225156,
   0.04608841};
   Double_t Graph1_fex1062[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1062[8] = {
   0.0002117352,
   0.0002047924,
   0.0002447596,
   0.0003150608,
   0.0003413262,
   0.0006521213,
   0.001590064,
   0.001930757};
   gre = new TGraphErrors(8,Graph1_fx1062,Graph1_fy1062,Graph1_fex1062,Graph1_fey1062);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1063[7] = {
   0.05207938,
   0.1057377,
   0.1794134,
   0.2623597,
   0.3507139,
   0.4425246,
   0.5363316};
   Double_t Graph2_fy1063[7] = {
   0.006504484,
   0.01421138,
   0.02123464,
   0.027955,
   0.03284466,
   0.03612086,
   0.0421749};
   Double_t Graph2_fex1063[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1063[7] = {
   5.045821e-05,
   0.0001248944,
   0.0001546414,
   0.0002982466,
   0.0004002715,
   0.0004852665,
   0.0004376036};
   gre = new TGraphErrors(7,Graph2_fx1063,Graph2_fy1063,Graph2_fex1063,Graph2_fey1063);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1183;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1064[7] = {
   0.05207938,
   0.1057377,
   0.1794134,
   0.2623597,
   0.3507139,
   0.4425246,
   0.5363316};
   Double_t Graph3_fy1064[7] = {
   0.006504484,
   0.01421138,
   0.02123464,
   0.027955,
   0.03284466,
   0.03612086,
   0.0421749};
   Double_t Graph3_fex1064[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1064[7] = {
   0.001123509,
   0.0005889632,
   0.00052132,
   0.0005710153,
   0.0007094465,
   0.000940828,
   0.001297457};
   gre = new TGraphErrors(7,Graph3_fx1064,Graph3_fy1064,Graph3_fex1064,Graph3_fey1064);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1065[12] = {
   0.05930431,
   0.09798921,
   0.1431449,
   0.1931956,
   0.2466918,
   0.3027189,
   0.3607431,
   0.4202341,
   0.4808888,
   0.5424459,
   0.6247159,
   0.7419983};
   Double_t Graph4_fy1065[12] = {
   0.008329593,
   0.01394165,
   0.01989648,
   0.02549678,
   0.03023647,
   0.0354868,
   0.03790678,
   0.04049013,
   0.04344956,
   0.04582776,
   0.04422496,
   0.05124849};
   Double_t Graph4_fex1065[12] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1065[12] = {
   0.000109091,
   0.0001458515,
   0.000196682,
   0.0003630729,
   0.000288246,
   0.000260055,
   0.0005810371,
   0.0002758658,
   0.0003951417,
   0.0002828176,
   0.0008821838,
   0.0009755354};
   gre = new TGraphErrors(12,Graph4_fx1065,Graph4_fy1065,Graph4_fex1065,Graph4_fey1065);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1184;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1066[12] = {
   0.05930431,
   0.09798921,
   0.1431449,
   0.1931956,
   0.2466918,
   0.3027189,
   0.3607431,
   0.4202341,
   0.4808888,
   0.5424459,
   0.6247159,
   0.7419983};
   Double_t Graph5_fy1066[12] = {
   0.008329593,
   0.01394165,
   0.01989648,
   0.02549678,
   0.03023647,
   0.0354868,
   0.03790678,
   0.04049013,
   0.04344956,
   0.04582776,
   0.04422496,
   0.05124849};
   Double_t Graph5_fex1066[12] = {
   0,
   0,
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
   Double_t Graph5_fey1066[12] = {
   0.0002614336,
   0.0002184151,
   0.0002158712,
   0.0002357744,
   0.0002750808,
   0.0003382739,
   0.0004338489,
   0.0005750774,
   0.0008083151,
   0.001160596,
   0.001388562,
   0.003177489};
   gre = new TGraphErrors(12,Graph5_fx1066,Graph5_fy1066,Graph5_fex1066,Graph5_fey1066);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.06,0.11,"#scale[0.8]{ #font[42]{Au+Au #sqrt{s_{NN}} = 11.5 GeV } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-0.08,0.09,"#scale[0.8]{ #font[42]{ v_{2}/n_{q} } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (a) } }");
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
   
   Double_t Graph0_fx1067[7] = {
   0.1137397,
   0.2496357,
   0.3960011,
   0.5446858,
   0.7076816,
   0.9268314,
   1.238144};
   Double_t Graph0_fy1067[7] = {
   0.004343714,
   0.01199708,
   0.02220889,
   0.02646347,
   0.03671047,
   0.05915782,
   0.07851259};
   Double_t Graph0_fex1067[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph0_fey1067[7] = {
   0.0006070392,
   0.000448267,
   0.0009652603,
   0.0007239173,
   0.001314152,
   0.001787972,
   0.007906253};
   gre = new TGraphErrors(7,Graph0_fx1067,Graph0_fy1067,Graph0_fex1067,Graph0_fey1067);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1188;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01067 = new TH1F("Graph_Graph01067","",100,-0.07,1.7);
   Graph_Graph01067->SetMinimum(-0.01);
   Graph_Graph01067->SetMaximum(0.14);
   Graph_Graph01067->SetDirectory(0);
   Graph_Graph01067->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01067->SetLineColor(ci);
   Graph_Graph01067->GetXaxis()->SetNdivisions(505);
   Graph_Graph01067->GetXaxis()->SetLabelFont(42);
   Graph_Graph01067->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph01067->GetXaxis()->SetLabelSize(0.1);
   Graph_Graph01067->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01067->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01067->GetXaxis()->SetTitleFont(42);
   Graph_Graph01067->GetYaxis()->SetNdivisions(505);
   Graph_Graph01067->GetYaxis()->SetLabelFont(42);
   Graph_Graph01067->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01067->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph01067->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01067->GetYaxis()->SetTitleFont(42);
   Graph_Graph01067->GetZaxis()->SetLabelFont(42);
   Graph_Graph01067->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01067->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01067->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01067->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01067);
   
   gre->Draw("ae5");
   
   Double_t Graph1_fx1068[7] = {
   0.1137397,
   0.2496357,
   0.3960011,
   0.5446858,
   0.7076816,
   0.9268314,
   1.238144};
   Double_t Graph1_fy1068[7] = {
   0.004343714,
   0.01199708,
   0.02220889,
   0.02646347,
   0.03671047,
   0.05915782,
   0.07851259};
   Double_t Graph1_fex1068[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1068[7] = {
   0.0009123902,
   0.001005612,
   0.001435687,
   0.002225194,
   0.003317518,
   0.006121217,
   0.01924912};
   gre = new TGraphErrors(7,Graph1_fx1068,Graph1_fy1068,Graph1_fex1068,Graph1_fey1068);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1069[4] = {
   0.07046998,
   0.1410084,
   0.2631707,
   0.4716493};
   Double_t Graph2_fy1069[4] = {
   0.004600768,
   0.007973824,
   0.01829635,
   0.02594732};
   Double_t Graph2_fex1069[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1069[4] = {
   0.0006070392,
   0.0007796128,
   0.0007274,
   0.002239719};
   gre = new TGraphErrors(4,Graph2_fx1069,Graph2_fy1069,Graph2_fex1069,Graph2_fey1069);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1189;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1070[4] = {
   0.07046998,
   0.1410084,
   0.2631707,
   0.4716493};
   Double_t Graph3_fy1070[4] = {
   0.004600768,
   0.007973824,
   0.01829635,
   0.02594732};
   Double_t Graph3_fex1070[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1070[4] = {
   0.003705795,
   0.002747807,
   0.001914131,
   0.003744545};
   gre = new TGraphErrors(4,Graph3_fx1070,Graph3_fy1070,Graph3_fex1070,Graph3_fey1070);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1071[6] = {
   0.06894281,
   0.1301442,
   0.2039048,
   0.2946495,
   0.4245181,
   0.6159177};
   Double_t Graph4_fy1071[6] = {
   0.002507567,
   0.009329549,
   0.0140023,
   0.02375448,
   0.02452757,
   0.02863947};
   Double_t Graph4_fex1071[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1071[6] = {
   0.0002440057,
   0.0005254212,
   0.0003940506,
   0.0007153338,
   0.0009732486,
   0.004303619};
   gre = new TGraphErrors(6,Graph4_fx1071,Graph4_fy1071,Graph4_fex1071,Graph4_fey1071);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1190;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1072[6] = {
   0.06894281,
   0.1301442,
   0.2039048,
   0.2946495,
   0.4245181,
   0.6159177};
   Double_t Graph5_fy1072[6] = {
   0.002507567,
   0.009329549,
   0.0140023,
   0.02375448,
   0.02452757,
   0.02863947};
   Double_t Graph5_fex1072[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1072[6] = {
   0.0008755605,
   0.0007352427,
   0.0008085622,
   0.0009431849,
   0.001446935,
   0.004022091};
   gre = new TGraphErrors(6,Graph5_fx1072,Graph5_fy1072,Graph5_fex1072,Graph5_fey1072);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   line = new TLine(-0.07,0,1.7,0);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(-0.08,0.11,"#scale[0.8]{ #font[42]{ 0-60% } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-0.08,0.09,"#scale[0.8]{ #font[42]{ 2.5 #times v_{3}/n_{q}^{3/2} } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.4,0.11,"#scale[0.8]{ #font[42]{ (b) } }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   pd_cent51->Modified();
   canvas->cd();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
