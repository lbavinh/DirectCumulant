void v2v3_AntiparticlesPads_scale_cent060()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Tue Oct  6 21:59:37 2020) by ROOT version 6.18/02

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
   0.01149155,
   0.02171205,
   0.03158849,
   0.04040056,
   0.04762524,
   0.05407225,
   0.05866352,
   0.06228466,
   0.06536489,
   0.06783023,
   0.06872496,
   0.07055198,
   0.06958289,
   0.06978434};
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
   ci = 1314;
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
   0.01149155,
   0.02171205,
   0.03158849,
   0.04040056,
   0.04762524,
   0.05407225,
   0.05866352,
   0.06228466,
   0.06536489,
   0.06783023,
   0.06872496,
   0.07055198,
   0.06958289,
   0.06978434};
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
   5.168826e-05,
   4.785099e-05,
   5.527604e-05,
   6.838244e-05,
   8.721452e-05,
   0.0001120689,
   0.0001458853,
   0.0001933303,
   0.0002600621,
   0.0003601087,
   0.0005117686,
   0.0007234379,
   0.001017854,
   0.001425629};
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
   0.005773894,
   0.01381886,
   0.02384529,
   0.0329793,
   0.04083459,
   0.04777139,
   0.05434949};
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

   ci = 1315;
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
   0.005773894,
   0.01381886,
   0.02384529,
   0.0329793,
   0.04083459,
   0.04777139,
   0.05434949};
   Double_t Graph3_fex1004[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1004[7] = {
   0.0003479404,
   0.0001725817,
   0.000148827,
   0.0001658933,
   0.0002116936,
   0.0002824115,
   0.0003819584};
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
   0.005967408,
   0.01180592,
   0.01853739,
   0.02513784,
   0.03143934,
   0.03732926,
   0.04218086,
   0.04640483,
   0.04996141,
   0.05279387,
   0.05564897,
   0.05914935};
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
   0.0001025089,
   0.0001506745,
   0.0001966987,
   0.0002549908,
   0.0002922206,
   0.0003184733,
   0.0003784436,
   0.0004474402,
   0.0004761105,
   0.0003787278,
   0.000493752,
   0.0005007415};
   gre = new TGraphErrors(12,Graph4_fx1005,Graph4_fy1005,Graph4_fex1005,Graph4_fey1005);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1316;
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
   0.005967408,
   0.01180592,
   0.01853739,
   0.02513784,
   0.03143934,
   0.03732926,
   0.04218086,
   0.04640483,
   0.04996141,
   0.05279387,
   0.05564897,
   0.05914935};
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
   0.0001797266,
   0.0001418556,
   0.000133498,
   0.0001399576,
   0.0001594242,
   0.0001935816,
   0.0002454159,
   0.0003208367,
   0.0004415805,
   0.0006157183,
   0.0006963386,
   0.001450123};
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
   0.005437666,
   0.01577573,
   0.02810754,
   0.03972779,
   0.05010184,
   0.06106602,
   0.06086787};
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

   ci = 1320;
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
   0.005437666,
   0.01577573,
   0.02810754,
   0.03972779,
   0.05010184,
   0.06106602,
   0.06086787};
   Double_t Graph1_fex1008[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1008[7] = {
   0.0001737056,
   0.0001822327,
   0.0002472982,
   0.0003566869,
   0.0004870041,
   0.0008201713,
   0.002238312};
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
   0.003434171,
   0.009792926,
   0.02099635,
   0.03290459};
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

   ci = 1321;
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
   0.003434171,
   0.009792926,
   0.02099635,
   0.03290459};
   Double_t Graph3_fex1010[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1010[4] = {
   0.000910151,
   0.0005206351,
   0.0005905328,
   0.0008734046};
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
   0.002667615,
   0.008058881,
   0.01588041,
   0.02545277,
   0.03547037,
   0.04959871};
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

   ci = 1322;
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
   0.002667615,
   0.008058881,
   0.01588041,
   0.02545277,
   0.03547037,
   0.04959871};
   Double_t Graph5_fex1012[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1012[6] = {
   0.0004925,
   0.0003847563,
   0.0003996891,
   0.000454289,
   0.0006803744,
   0.001740159};
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
   0.01139603,
   0.0212274,
   0.03076751,
   0.03911532,
   0.04616727,
   0.05200799,
   0.05678954,
   0.06068078,
   0.06366625,
   0.06505786,
   0.06608893,
   0.06878284,
   0.06953449,
   0.06916352};
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

   ci = 1302;
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
   0.01139603,
   0.0212274,
   0.03076751,
   0.03911532,
   0.04616727,
   0.05200799,
   0.05678954,
   0.06068078,
   0.06366625,
   0.06505786,
   0.06608893,
   0.06878284,
   0.06953449,
   0.06916352};
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
   3.804089e-05,
   3.569625e-05,
   4.165902e-05,
   5.214795e-05,
   6.771294e-05,
   8.899011e-05,
   0.0001182639,
   0.0001586908,
   0.0002145721,
   0.0002978269,
   0.0004250609,
   0.0006046565,
   0.0008566719,
   0.001203395};
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
   0.00593969,
   0.01389437,
   0.02317473,
   0.03168868,
   0.03899525,
   0.04551231,
   0.05047575};
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

   ci = 1303;
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
   0.00593969,
   0.01389437,
   0.02317473,
   0.03168868,
   0.03899525,
   0.04551231,
   0.05047575};
   Double_t Graph3_fex1016[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1016[7] = {
   0.0002556299,
   0.0001308445,
   0.0001133517,
   0.0001222619,
   0.000149438,
   0.0001935723,
   0.0002578899};
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
   0.005753727,
   0.01146637,
   0.01800974,
   0.02472064,
   0.03092355,
   0.03630829,
   0.04013728,
   0.04427555,
   0.04703138,
   0.05182863,
   0.05566678,
   0.05577713};
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
   0.0001092595,
   0.0001851519,
   0.0002258867,
   0.0002736759,
   0.0003138245,
   0.0003435757,
   0.0004065153,
   0.0004156133,
   0.0004056065,
   0.0004494341,
   0.0004209056,
   0.0004781804};
   gre = new TGraphErrors(12,Graph4_fx1017,Graph4_fy1017,Graph4_fex1017,Graph4_fey1017);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1304;
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
   0.005753727,
   0.01146637,
   0.01800974,
   0.02472064,
   0.03092355,
   0.03630829,
   0.04013728,
   0.04427555,
   0.04703138,
   0.05182863,
   0.05566678,
   0.05577713};
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
   0.000143543,
   0.0001158065,
   0.0001108216,
   0.0001173665,
   0.0001334528,
   0.0001604751,
   0.000200744,
   0.000259777,
   0.0003554226,
   0.0004946334,
   0.000562795,
   0.001195082};
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
   0.005297161,
   0.01494169,
   0.02655178,
   0.03782185,
   0.04755978,
   0.05761053,
   0.06461349};
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

   ci = 1308;
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
   0.005297161,
   0.01494169,
   0.02655178,
   0.03782185,
   0.04755978,
   0.05761053,
   0.06461349};
   Double_t Graph1_fex1020[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1020[7] = {
   0.0001380052,
   0.0001470799,
   0.0002032158,
   0.0003021568,
   0.0004269516,
   0.000729488,
   0.002016297};
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
   0.003178157,
   0.01020304,
   0.01985766,
   0.03056907};
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

   ci = 1309;
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
   0.003178157,
   0.01020304,
   0.01985766,
   0.03056907};
   Double_t Graph3_fex1022[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1022[4] = {
   0.0007291296,
   0.0004249202,
   0.0004603414,
   0.0006404627};
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
   0.001714045,
   0.007955816,
   0.01470991,
   0.02527355,
   0.03430338,
   0.04258107};
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

   ci = 1310;
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
   0.001714045,
   0.007955816,
   0.01470991,
   0.02527355,
   0.03430338,
   0.04258107};
   Double_t Graph5_fex1024[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1024[6] = {
   0.0004291454,
   0.0003429802,
   0.0003598296,
   0.0004025658,
   0.0005855587,
   0.001481347};
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
   
   Double_t v2_PionsMinusSys_fx1025[12] = {
   0.09517796,
   0.1849961,
   0.2814194,
   0.3796219,
   0.4785289,
   0.5779062,
   0.6774689,
   0.777073,
   0.8767332,
   0.9764702,
   1.108608,
   1.331677};
   Double_t v2_PionsMinusSys_fy1025[12] = {
   0.01157825,
   0.02110689,
   0.03026237,
   0.03824574,
   0.04505659,
   0.0505034,
   0.0548657,
   0.05821493,
   0.06117554,
   0.06272498,
   0.06435283,
   0.06632592};
   Double_t v2_PionsMinusSys_fex1025[12] = {
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
   Double_t v2_PionsMinusSys_fey1025[12] = {
   1.789612e-05,
   0.0001086815,
   0.0002252819,
   0.0003102881,
   0.000388456,
   0.0004413142,
   0.0004990566,
   0.0005964601,
   0.0005797595,
   0.000709393,
   0.0007675468,
   0.0007787093};
   gre = new TGraphErrors(12,v2_PionsMinusSys_fx1025,v2_PionsMinusSys_fy1025,v2_PionsMinusSys_fex1025,v2_PionsMinusSys_fey1025);
   gre->SetName("v2_PionsMinusSys");
   gre->SetTitle("");

   ci = 1290;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v2_PionsMinusSys1025 = new TH1F("Graph_v2_PionsMinusSys1025","",100,-0.07,1.7);
   Graph_v2_PionsMinusSys1025->SetMinimum(-0.01);
   Graph_v2_PionsMinusSys1025->SetMaximum(0.14);
   Graph_v2_PionsMinusSys1025->SetDirectory(0);
   Graph_v2_PionsMinusSys1025->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v2_PionsMinusSys1025->SetLineColor(ci);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetNdivisions(505);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetLabelFont(42);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetLabelOffset(0.01);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetLabelSize(0.1);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetTitleSize(0.035);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetTitleOffset(1);
   Graph_v2_PionsMinusSys1025->GetXaxis()->SetTitleFont(42);
   Graph_v2_PionsMinusSys1025->GetYaxis()->SetNdivisions(505);
   Graph_v2_PionsMinusSys1025->GetYaxis()->SetLabelFont(42);
   Graph_v2_PionsMinusSys1025->GetYaxis()->SetLabelOffset(0.01);
   Graph_v2_PionsMinusSys1025->GetYaxis()->SetLabelSize(0.1);
   Graph_v2_PionsMinusSys1025->GetYaxis()->SetTitleSize(0.035);
   Graph_v2_PionsMinusSys1025->GetYaxis()->SetTitleFont(42);
   Graph_v2_PionsMinusSys1025->GetZaxis()->SetLabelFont(42);
   Graph_v2_PionsMinusSys1025->GetZaxis()->SetLabelSize(0.035);
   Graph_v2_PionsMinusSys1025->GetZaxis()->SetTitleSize(0.035);
   Graph_v2_PionsMinusSys1025->GetZaxis()->SetTitleOffset(1);
   Graph_v2_PionsMinusSys1025->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v2_PionsMinusSys1025);
   
   gre->Draw("ae5");
   
   Double_t v2_PionsMinus_fx1026[12] = {
   0.09517796,
   0.1849961,
   0.2814194,
   0.3796219,
   0.4785289,
   0.5779062,
   0.6774689,
   0.777073,
   0.8767332,
   0.9764702,
   1.108608,
   1.331677};
   Double_t v2_PionsMinus_fy1026[12] = {
   0.01157825,
   0.02110689,
   0.03026237,
   0.03824574,
   0.04505659,
   0.0505034,
   0.0548657,
   0.05821493,
   0.06117554,
   0.06272498,
   0.06435283,
   0.06632592};
   Double_t v2_PionsMinus_fex1026[12] = {
   0,
   0,
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
   Double_t v2_PionsMinus_fey1026[12] = {
   2.045823e-05,
   1.93997e-05,
   2.272669e-05,
   2.860891e-05,
   3.735147e-05,
   4.971414e-05,
   6.657669e-05,
   8.987809e-05,
   0.0001223633,
   0.0001714377,
   0.0002034476,
   0.000391477};
   gre = new TGraphErrors(12,v2_PionsMinus_fx1026,v2_PionsMinus_fy1026,v2_PionsMinus_fex1026,v2_PionsMinus_fey1026);
   gre->SetName("v2_PionsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v2_KaonsMinusSys_fx1027[7] = {
   0.05143948,
   0.1058934,
   0.1794402,
   0.2624583,
   0.3508999,
   0.4428252,
   0.5368764};
   Double_t v2_KaonsMinusSys_fy1027[7] = {
   0.006392082,
   0.01377664,
   0.02251505,
   0.03066243,
   0.03765216,
   0.04391742,
   0.04907429};
   Double_t v2_KaonsMinusSys_fex1027[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v2_KaonsMinusSys_fey1027[7] = {
   1.789612e-05,
   0.0001086815,
   0.0002252819,
   0.0003102881,
   0.000388456,
   0.0004413142,
   0.0004990566};
   gre = new TGraphErrors(7,v2_KaonsMinusSys_fx1027,v2_KaonsMinusSys_fy1027,v2_KaonsMinusSys_fex1027,v2_KaonsMinusSys_fey1027);
   gre->SetName("v2_KaonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1291;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t v2_KaonsMinus_fx1028[7] = {
   0.05143948,
   0.1058934,
   0.1794402,
   0.2624583,
   0.3508999,
   0.4428252,
   0.5368764};
   Double_t v2_KaonsMinus_fy1028[7] = {
   0.006392082,
   0.01377664,
   0.02251505,
   0.03066243,
   0.03765216,
   0.04391742,
   0.04907429};
   Double_t v2_KaonsMinus_fex1028[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v2_KaonsMinus_fey1028[7] = {
   0.0001373832,
   7.191818e-05,
   6.310645e-05,
   6.893129e-05,
   8.473326e-05,
   0.000110911,
   0.0001491843};
   gre = new TGraphErrors(7,v2_KaonsMinus_fx1028,v2_KaonsMinus_fy1028,v2_KaonsMinus_fex1028,v2_KaonsMinus_fey1028);
   gre->SetName("v2_KaonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v2_ProtonsMinusSys_fx1029[12] = {
   0.05944657,
   0.09810951,
   0.143264,
   0.1932283,
   0.2467791,
   0.3028479,
   0.3608631,
   0.4203665,
   0.4810458,
   0.5426361,
   0.625738,
   0.7426798};
   Double_t v2_ProtonsMinusSys_fy1029[12] = {
   0.005601134,
   0.01102842,
   0.01718161,
   0.02353677,
   0.02930631,
   0.03447129,
   0.03884836,
   0.04275034,
   0.04597594,
   0.0485325,
   0.05161179,
   0.0543966};
   Double_t v2_ProtonsMinusSys_fex1029[12] = {
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
   Double_t v2_ProtonsMinusSys_fey1029[12] = {
   0.000109693,
   0.0001800826,
   0.0002301136,
   0.0002809878,
   0.0003207524,
   0.0003586191,
   0.0004052413,
   0.0004195584,
   0.0004831546,
   0.0005001951,
   0.0005026257,
   0.0006166628};
   gre = new TGraphErrors(12,v2_ProtonsMinusSys_fx1029,v2_ProtonsMinusSys_fy1029,v2_ProtonsMinusSys_fex1029,v2_ProtonsMinusSys_fey1029);
   gre->SetName("v2_ProtonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1292;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t v2_ProtonsMinus_fx1030[12] = {
   0.05944657,
   0.09810951,
   0.143264,
   0.1932283,
   0.2467791,
   0.3028479,
   0.3608631,
   0.4203665,
   0.4810458,
   0.5426361,
   0.625738,
   0.7426798};
   Double_t v2_ProtonsMinus_fy1030[12] = {
   0.005601134,
   0.01102842,
   0.01718161,
   0.02353677,
   0.02930631,
   0.03447129,
   0.03884836,
   0.04275034,
   0.04597594,
   0.0485325,
   0.05161179,
   0.0543966};
   Double_t v2_ProtonsMinus_fex1030[12] = {
   0,
   0,
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
   Double_t v2_ProtonsMinus_fey1030[12] = {
   8.4874e-05,
   6.929097e-05,
   6.724641e-05,
   7.277294e-05,
   8.4271e-05,
   0.000102423,
   0.0001293989,
   0.0001693086,
   0.0002342498,
   0.0003297232,
   0.0003819668,
   0.0008311075};
   gre = new TGraphErrors(12,v2_ProtonsMinus_fx1030,v2_ProtonsMinus_fy1030,v2_ProtonsMinus_fex1030,v2_ProtonsMinus_fey1030);
   gre->SetName("v2_ProtonsMinus");
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
      tex = new TLatex(0,0.11,"#scale[0.8]{ #font[42]{ 27 GeV Run18} }");
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
   
   Double_t v3_PionsMinusSys_fx1031[7] = {
   0.1142919,
   0.2503058,
   0.3969555,
   0.545579,
   0.7098784,
   0.9315208,
   1.246647};
   Double_t v3_PionsMinusSys_fy1031[7] = {
   0.005109565,
   0.01421847,
   0.02539254,
   0.03585783,
   0.04534713,
   0.05527175,
   0.05944716};
   Double_t v3_PionsMinusSys_fex1031[7] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v3_PionsMinusSys_fey1031[7] = {
   6.139281e-05,
   0.0001294571,
   0.0004247672,
   0.0007949368,
   0.001210882,
   0.001829868,
   0.002364419};
   gre = new TGraphErrors(7,v3_PionsMinusSys_fx1031,v3_PionsMinusSys_fy1031,v3_PionsMinusSys_fex1031,v3_PionsMinusSys_fey1031);
   gre->SetName("v3_PionsMinusSys");
   gre->SetTitle("");

   ci = 1296;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v3_PionsMinusSys1031 = new TH1F("Graph_v3_PionsMinusSys1031","",100,-0.07,1.7);
   Graph_v3_PionsMinusSys1031->SetMinimum(-0.01);
   Graph_v3_PionsMinusSys1031->SetMaximum(0.14);
   Graph_v3_PionsMinusSys1031->SetDirectory(0);
   Graph_v3_PionsMinusSys1031->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v3_PionsMinusSys1031->SetLineColor(ci);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetNdivisions(505);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetLabelSize(0.1);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetTitleOffset(1);
   Graph_v3_PionsMinusSys1031->GetXaxis()->SetTitleFont(42);
   Graph_v3_PionsMinusSys1031->GetYaxis()->SetNdivisions(505);
   Graph_v3_PionsMinusSys1031->GetYaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1031->GetYaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsMinusSys1031->GetYaxis()->SetLabelSize(0.1);
   Graph_v3_PionsMinusSys1031->GetYaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1031->GetYaxis()->SetTitleFont(42);
   Graph_v3_PionsMinusSys1031->GetZaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1031->GetZaxis()->SetLabelSize(0.035);
   Graph_v3_PionsMinusSys1031->GetZaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1031->GetZaxis()->SetTitleOffset(1);
   Graph_v3_PionsMinusSys1031->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v3_PionsMinusSys1031);
   
   gre->Draw("ae5");
   
   Double_t v3_PionsMinus_fx1032[7] = {
   0.1142919,
   0.2503058,
   0.3969555,
   0.545579,
   0.7098784,
   0.9315208,
   1.246647};
   Double_t v3_PionsMinus_fy1032[7] = {
   0.005109565,
   0.01421847,
   0.02539254,
   0.03585783,
   0.04534713,
   0.05527175,
   0.05944716};
   Double_t v3_PionsMinus_fex1032[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_PionsMinus_fey1032[7] = {
   7.995953e-05,
   8.611988e-05,
   0.0001197174,
   0.0001801122,
   0.0002567741,
   0.0004440748,
   0.001273297};
   gre = new TGraphErrors(7,v3_PionsMinus_fx1032,v3_PionsMinus_fy1032,v3_PionsMinus_fex1032,v3_PionsMinus_fey1032);
   gre->SetName("v3_PionsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v3_KaonsMinusSys_fx1033[4] = {
   0.07002529,
   0.158474,
   0.2789658,
   0.4128458};
   Double_t v3_KaonsMinusSys_fy1033[4] = {
   0.003047986,
   0.009449848,
   0.01886052,
   0.02830869};
   Double_t v3_KaonsMinusSys_fex1033[4] = {
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v3_KaonsMinusSys_fey1033[4] = {
   6.139281e-05,
   0.0001294571,
   0.0004247672,
   0.0007949368};
   gre = new TGraphErrors(4,v3_KaonsMinusSys_fx1033,v3_KaonsMinusSys_fy1033,v3_KaonsMinusSys_fex1033,v3_KaonsMinusSys_fey1033);
   gre->SetName("v3_KaonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1297;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t v3_KaonsMinus_fx1034[4] = {
   0.07002529,
   0.158474,
   0.2789658,
   0.4128458};
   Double_t v3_KaonsMinus_fy1034[4] = {
   0.003047986,
   0.009449848,
   0.01886052,
   0.02830869};
   Double_t v3_KaonsMinus_fex1034[4] = {
   0,
   0,
   0,
   0};
   Double_t v3_KaonsMinus_fey1034[4] = {
   0.0004230091,
   0.0002518226,
   0.0002775711,
   0.0003909064};
   gre = new TGraphErrors(4,v3_KaonsMinus_fx1034,v3_KaonsMinus_fy1034,v3_KaonsMinus_fex1034,v3_KaonsMinus_fey1034);
   gre->SetName("v3_KaonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t v3_ProtonsMinusSys_fx1035[6] = {
   0.0692642,
   0.1304243,
   0.2040132,
   0.2951313,
   0.4257301,
   0.6190558};
   Double_t v3_ProtonsMinusSys_fy1035[6] = {
   0.001681546,
   0.007323026,
   0.01458365,
   0.02270523,
   0.03166027,
   0.04451134};
   Double_t v3_ProtonsMinusSys_fex1035[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t v3_ProtonsMinusSys_fey1035[6] = {
   7.046752e-05,
   0.000231214,
   0.0004327088,
   0.0006591208,
   0.000996054,
   0.001287027};
   gre = new TGraphErrors(6,v3_ProtonsMinusSys_fx1035,v3_ProtonsMinusSys_fy1035,v3_ProtonsMinusSys_fex1035,v3_ProtonsMinusSys_fey1035);
   gre->SetName("v3_ProtonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1298;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t v3_ProtonsMinus_fx1036[6] = {
   0.0692642,
   0.1304243,
   0.2040132,
   0.2951313,
   0.4257301,
   0.6190558};
   Double_t v3_ProtonsMinus_fy1036[6] = {
   0.001681546,
   0.007323026,
   0.01458365,
   0.02270523,
   0.03166027,
   0.04451134};
   Double_t v3_ProtonsMinus_fex1036[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_ProtonsMinus_fey1036[6] = {
   0.0002746926,
   0.0002233403,
   0.0002408041,
   0.0002748855,
   0.0004079004,
   0.001068149};
   gre = new TGraphErrors(6,v3_ProtonsMinus_fx1036,v3_ProtonsMinus_fy1036,v3_ProtonsMinus_fex1036,v3_ProtonsMinus_fey1036);
   gre->SetName("v3_ProtonsMinus");
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
   0.09504635,
   0.1848341,
   0.2812202,
   0.3793808,
   0.4783293,
   0.5776596,
   0.6770567,
   0.7765732,
   0.9074665,
   1.106991,
   1.328526};
   Double_t Graph0_fy1037[11] = {
   0.01148763,
   0.02067352,
   0.02938097,
   0.03698051,
   0.04325892,
   0.04858625,
   0.0523481,
   0.05560174,
   0.05799105,
   0.06043101,
   0.06556903};
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

   ci = 1278;
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
   0.09504635,
   0.1848341,
   0.2812202,
   0.3793808,
   0.4783293,
   0.5776596,
   0.6770567,
   0.7765732,
   0.9074665,
   1.106991,
   1.328526};
   Double_t Graph1_fy1038[11] = {
   0.01148763,
   0.02067352,
   0.02938097,
   0.03698051,
   0.04325892,
   0.04858625,
   0.0523481,
   0.05560174,
   0.05799105,
   0.06043101,
   0.06556903};
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
   9.493263e-05,
   9.087072e-05,
   0.0001076547,
   0.0001371483,
   0.000181954,
   0.0002450611,
   0.0003351783,
   0.000464705,
   0.0005348886,
   0.001152982,
   0.002363226};
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
   0.05155269,
   0.1057455,
   0.179222,
   0.2621224,
   0.3505854,
   0.4425362,
   0.5366839};
   Double_t Graph2_fy1039[7] = {
   0.006229332,
   0.01356043,
   0.02174685,
   0.02927261,
   0.03571342,
   0.04126919,
   0.04539103};
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

   ci = 1279;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1040[7] = {
   0.05155269,
   0.1057455,
   0.179222,
   0.2621224,
   0.3505854,
   0.4425362,
   0.5366839};
   Double_t Graph3_fy1040[7] = {
   0.006229332,
   0.01356043,
   0.02174685,
   0.02927261,
   0.03571342,
   0.04126919,
   0.04539103};
   Double_t Graph3_fex1040[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1040[7] = {
   0.0006625036,
   0.0003491159,
   0.0003105127,
   0.0003457287,
   0.0004358637,
   0.0005817956,
   0.0007979195};
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
   0.05936137,
   0.09802074,
   0.1431735,
   0.1931856,
   0.2466236,
   0.3026517,
   0.3607024,
   0.4201918,
   0.480892,
   0.5424344,
   0.6250776,
   0.7425747};
   Double_t Graph4_fy1041[12] = {
   0.004933923,
   0.009584757,
   0.01587472,
   0.02205015,
   0.02746032,
   0.03230822,
   0.03526295,
   0.04193838,
   0.04492819,
   0.03964997,
   0.05036199,
   0.05603336};
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

   ci = 1280;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1042[12] = {
   0.05936137,
   0.09802074,
   0.1431735,
   0.1931856,
   0.2466236,
   0.3026517,
   0.3607024,
   0.4201918,
   0.480892,
   0.5424344,
   0.6250776,
   0.7425747};
   Double_t Graph5_fy1042[12] = {
   0.004933923,
   0.009584757,
   0.01587472,
   0.02205015,
   0.02746032,
   0.03230822,
   0.03526295,
   0.04193838,
   0.04492819,
   0.03964997,
   0.05036199,
   0.05603336};
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
   0.0004625609,
   0.0003830818,
   0.0003767636,
   0.0004105414,
   0.0004806431,
   0.0005951657,
   0.0007668172,
   0.001020223,
   0.001436943,
   0.002057164,
   0.002441395,
   0.005482666};
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
   0.1139914,
   0.2499043,
   0.3963934,
   0.545131,
   0.7082913,
   0.9283461,
   1.241622};
   Double_t Graph0_fy1043[7] = {
   0.004777072,
   0.01358946,
   0.02464595,
   0.03426167,
   0.04306986,
   0.04856344,
   0.05695925};
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

   ci = 1284;
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
   0.1139914,
   0.2499043,
   0.3963934,
   0.545131,
   0.7082913,
   0.9283461,
   1.241622};
   Double_t Graph1_fy1044[7] = {
   0.004777072,
   0.01358946,
   0.02464595,
   0.03426167,
   0.04306986,
   0.04856344,
   0.05695925};
   Double_t Graph1_fex1044[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1044[7] = {
   0.0003874778,
   0.0004235534,
   0.000599305,
   0.0009183106,
   0.001352322,
   0.002473372,
   0.007657638};
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
   0.0700446,
   0.1580626,
   0.2781655,
   0.4122275};
   Double_t Graph2_fy1045[4] = {
   0.003592783,
   0.006473572,
   0.01850341,
   0.02638364};
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

   ci = 1285;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1046[4] = {
   0.0700446,
   0.1580626,
   0.2781655,
   0.4122275};
   Double_t Graph3_fy1046[4] = {
   0.003592783,
   0.006473572,
   0.01850341,
   0.02638364};
   Double_t Graph3_fex1046[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1046[4] = {
   0.002127865,
   0.001282847,
   0.001448838,
   0.002104766};
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
   0.06905591,
   0.1302127,
   0.2038742,
   0.2944429,
   0.4243663,
   0.6172325};
   Double_t Graph4_fy1047[6] = {
   0.0001175471,
   0.005677518,
   0.0131122,
   0.02007898,
   0.03628352,
   0.05264573};
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

   ci = 1286;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1048[6] = {
   0.06905591,
   0.1302127,
   0.2038742,
   0.2944429,
   0.4243663,
   0.6172325};
   Double_t Graph5_fy1048[6] = {
   0.0001175471,
   0.005677518,
   0.0131122,
   0.02007898,
   0.03628352,
   0.05264573};
   Double_t Graph5_fex1048[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1048[6] = {
   0.001583747,
   0.001305574,
   0.001416866,
   0.001655056,
   0.00254159,
   0.007007572};
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
   0.09404354,
   0.1845511,
   0.2809936,
   0.3792393,
   0.4781749,
   0.5775294,
   0.6770072,
   0.7764965,
   0.8760219,
   0.9756739,
   1.075431,
   1.174981};
   Double_t Graph0_fy1049[12] = {
   0.01247206,
   0.02110988,
   0.02941603,
   0.03663424,
   0.04271657,
   0.04718044,
   0.05094594,
   0.05323684,
   0.05667419,
   0.05808177,
   0.05964912,
   0.05926991};
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

   ci = 1266;
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
   0.09404354,
   0.1845511,
   0.2809936,
   0.3792393,
   0.4781749,
   0.5775294,
   0.6770072,
   0.7764965,
   0.8760219,
   0.9756739,
   1.075431,
   1.174981};
   Double_t Graph1_fy1050[12] = {
   0.01247206,
   0.02110988,
   0.02941603,
   0.03663424,
   0.04271657,
   0.04718044,
   0.05094594,
   0.05323684,
   0.05667419,
   0.05808177,
   0.05964912,
   0.05926991};
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
   0.0001119497,
   0.0001103683,
   0.0001327062,
   0.0001714182,
   0.0002291742,
   0.0003110004,
   0.0004276294,
   0.0005958448,
   0.0008429209,
   0.001233984,
   0.00187266,
   0.002876159};
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
   0.05112654,
   0.1056487,
   0.1791608,
   0.2619625,
   0.350221,
   0.4420703,
   0.5361258};
   Double_t Graph2_fy1051[7] = {
   0.006634866,
   0.01366109,
   0.02133317,
   0.02868794,
   0.03410294,
   0.04124329,
   0.04389089};
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

   ci = 1267;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1052[7] = {
   0.05112654,
   0.1056487,
   0.1791608,
   0.2619625,
   0.350221,
   0.4420703,
   0.5361258};
   Double_t Graph3_fy1052[7] = {
   0.006634866,
   0.01366109,
   0.02133317,
   0.02868794,
   0.03410294,
   0.04124329,
   0.04389089};
   Double_t Graph3_fex1052[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1052[7] = {
   0.0008515639,
   0.0004574857,
   0.0004090744,
   0.0004596345,
   0.0005894951,
   0.0008077767,
   0.001144433};
   gre = new TGraphErrors(7,Graph3_fx1052,Graph3_fy1052,Graph3_fex1052,Graph3_fey1052);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1053[11] = {
   0.05931234,
   0.09789655,
   0.1430542,
   0.1930349,
   0.2464437,
   0.3024598,
   0.3604135,
   0.4199125,
   0.4805145,
   0.5423924,
   0.6045047};
   Double_t Graph4_fy1053[11] = {
   0.005030231,
   0.009531295,
   0.01551266,
   0.02070452,
   0.02695991,
   0.02966547,
   0.03587376,
   0.03804623,
   0.03994274,
   0.04020114,
   0.04202699};
   Double_t Graph4_fex1053[11] = {
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
   Double_t Graph4_fey1053[11] = {
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
   0.0004272441};
   gre = new TGraphErrors(11,Graph4_fx1053,Graph4_fy1053,Graph4_fex1053,Graph4_fey1053);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1268;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1054[11] = {
   0.05931234,
   0.09789655,
   0.1430542,
   0.1930349,
   0.2464437,
   0.3024598,
   0.3604135,
   0.4199125,
   0.4805145,
   0.5423924,
   0.6045047};
   Double_t Graph5_fy1054[11] = {
   0.005030231,
   0.009531295,
   0.01551266,
   0.02070452,
   0.02695991,
   0.02966547,
   0.03587376,
   0.03804623,
   0.03994274,
   0.04020114,
   0.04202699};
   Double_t Graph5_fex1054[11] = {
   0,
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
   Double_t Graph5_fey1054[11] = {
   0.0006605762,
   0.0005532319,
   0.0005517954,
   0.0006118329,
   0.0007295316,
   0.0009257961,
   0.001220028,
   0.001669048,
   0.002410858,
   0.003519988,
   0.00524546};
   gre = new TGraphErrors(11,Graph5_fx1054,Graph5_fy1054,Graph5_fex1054,Graph5_fey1054);
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
   0.1124094,
   0.2494017,
   0.3961167,
   0.544897,
   0.7080329,
   0.9262043,
   1.236468};
   Double_t Graph0_fy1055[7] = {
   0.005704581,
   0.01277553,
   0.02287793,
   0.03190448,
   0.03524173,
   0.05515853,
   0.04329345};
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

   ci = 1272;
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
   0.1124094,
   0.2494017,
   0.3961167,
   0.544897,
   0.7080329,
   0.9262043,
   1.236468};
   Double_t Graph1_fy1056[7] = {
   0.005704581,
   0.01277553,
   0.02287793,
   0.03190448,
   0.03524173,
   0.05515853,
   0.04329345};
   Double_t Graph1_fex1056[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1056[7] = {
   0.0005055322,
   0.000571952,
   0.0008241964,
   0.001275107,
   0.00188661,
   0.003500667,
   0.01158998};
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
   0.06942723,
   0.1579096,
   0.2777316,
   0.4113346};
   Double_t Graph2_fy1057[4] = {
   0.002128646,
   0.009185661,
   0.01612237,
   0.02563175};
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

   ci = 1273;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1058[4] = {
   0.06942723,
   0.1579096,
   0.2777316,
   0.4113346};
   Double_t Graph3_fy1058[4] = {
   0.002128646,
   0.009185661,
   0.01612237,
   0.02563175};
   Double_t Graph3_fex1058[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1058[4] = {
   0.003018858,
   0.001845439,
   0.002104572,
   0.00314363};
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
   0.06891857,
   0.1299592,
   0.2034765,
   0.2935994,
   0.4225405,
   0.615083};
   Double_t Graph4_fy1059[6] = {
   0.003271736,
   0.006818422,
   0.01263893,
   0.0190372,
   0.02789509,
   0.03845096};
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

   ci = 1274;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1060[6] = {
   0.06891857,
   0.1299592,
   0.2034765,
   0.2935994,
   0.4225405,
   0.615083};
   Double_t Graph5_fy1060[6] = {
   0.003271736,
   0.006818422,
   0.01263893,
   0.0190372,
   0.02789509,
   0.03845096};
   Double_t Graph5_fex1060[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1060[6] = {
   0.002492232,
   0.002090421,
   0.002321458,
   0.002792148,
   0.004501061,
   0.01303391};
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
   0.09465283,
   0.184544,
   0.2809988,
   0.3791137,
   0.5087371,
   0.7070823,
   0.8758017,
   1.004965};
   Double_t Graph0_fy1061[8] = {
   0.01179097,
   0.02030961,
   0.0277115,
   0.03539734,
   0.04139042,
   0.04911334,
   0.04947555,
   0.05191516};
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

   ci = 1254;
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
   0.09465283,
   0.184544,
   0.2809988,
   0.3791137,
   0.5087371,
   0.7070823,
   0.8758017,
   1.004965};
   Double_t Graph1_fy1062[8] = {
   0.01179097,
   0.02030961,
   0.0277115,
   0.03539734,
   0.04139042,
   0.04911334,
   0.04947555,
   0.05191516};
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
   0.0002058718,
   0.0002015064,
   0.0002425206,
   0.0003136884,
   0.0003424742,
   0.0006622569,
   0.001649224,
   0.00206032};
   gre = new TGraphErrors(8,Graph1_fx1062,Graph1_fy1062,Graph1_fex1062,Graph1_fey1062);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph2_fx1063[6] = {
   0.05150121,
   0.1055191,
   0.1790689,
   0.2619701,
   0.378864,
   0.5647484};
   Double_t Graph2_fy1063[6] = {
   0.005371673,
   0.01194747,
   0.01916553,
   0.02735644,
   0.03568907,
   0.04331475};
   Double_t Graph2_fex1063[6] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph2_fey1063[6] = {
   5.045821e-05,
   0.0001248944,
   0.0001546414,
   0.0002982466,
   0.0004348228,
   0.0005114478};
   gre = new TGraphErrors(6,Graph2_fx1063,Graph2_fy1063,Graph2_fex1063,Graph2_fey1063);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");

   ci = 1255;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1064[6] = {
   0.05150121,
   0.1055191,
   0.1790689,
   0.2619701,
   0.378864,
   0.5647484};
   Double_t Graph3_fy1064[6] = {
   0.005371673,
   0.01194747,
   0.01916553,
   0.02735644,
   0.03568907,
   0.04331475};
   Double_t Graph3_fex1064[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1064[6] = {
   0.001574365,
   0.0008421658,
   0.0007618632,
   0.0008566042,
   0.0008825979,
   0.001725571};
   gre = new TGraphErrors(6,Graph3_fx1064,Graph3_fy1064,Graph3_fex1064,Graph3_fey1064);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1065[5] = {
   0.04342294,
   0.09700307,
   0.2024818,
   0.3639693,
   0.5563995};
   Double_t Graph4_fy1065[5] = {
   -0.0008800252,
   0.008134061,
   0.01801439,
   0.02733384,
   0.04063731};
   Double_t Graph4_fex1065[5] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1065[5] = {
   8.326295e-05,
   0.0001424372,
   0.0002924758,
   0.0003920599,
   0.0002976935};
   gre = new TGraphErrors(5,Graph4_fx1065,Graph4_fy1065,Graph4_fex1065,Graph4_fey1065);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1256;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1066[5] = {
   0.04342294,
   0.09700307,
   0.2024818,
   0.3639693,
   0.5563995};
   Double_t Graph5_fy1066[5] = {
   -0.0008800252,
   0.008134061,
   0.01801439,
   0.02733384,
   0.04063731};
   Double_t Graph5_fex1066[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1066[5] = {
   0.001835802,
   0.0009104637,
   0.0008848479,
   0.001810431,
   0.00513742};
   gre = new TGraphErrors(5,Graph5_fx1066,Graph5_fy1066,Graph5_fex1066,Graph5_fey1066);
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
   0.113162,
   0.2493905,
   0.3957982,
   0.5444908,
   0.7070823,
   0.9245015,
   1.232262};
   Double_t Graph0_fy1067[7] = {
   0.005274582,
   0.01299483,
   0.01965354,
   0.0283594,
   0.04139338,
   0.0353601,
   0.06810809};
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

   ci = 1260;
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
   0.113162,
   0.2493905,
   0.3957982,
   0.5444908,
   0.7070823,
   0.9245015,
   1.232262};
   Double_t Graph1_fy1068[7] = {
   0.005274582,
   0.01299483,
   0.01965354,
   0.0283594,
   0.04139338,
   0.0353601,
   0.06810809};
   Double_t Graph1_fex1068[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1068[7] = {
   0.00088922,
   0.0009983054,
   0.001439574,
   0.002255697,
   0.003402635,
   0.006514402,
   0.02239664};
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
   0.06982395,
   0.1406992,
   0.2610039,
   0.4705397};
   Double_t Graph2_fy1069[4] = {
   0.001596602,
   0.01244205,
   0.01483647,
   0.0106379};
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

   ci = 1261;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("pe5");
   
   Double_t Graph3_fx1070[4] = {
   0.06982395,
   0.1406992,
   0.2610039,
   0.4705397};
   Double_t Graph3_fy1070[4] = {
   0.001596602,
   0.01244205,
   0.01483647,
   0.0106379};
   Double_t Graph3_fex1070[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1070[4] = {
   0.005292798,
   0.004003691,
   0.002890618,
   0.005962323};
   gre = new TGraphErrors(4,Graph3_fx1070,Graph3_fy1070,Graph3_fex1070,Graph3_fey1070);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(0.8);
   gre->Draw("pe");
   
   Double_t Graph4_fx1071[5] = {
   0.05931037,
   0.1079293,
   0.2024818,
   0.3505484,
   0.4901615};
   Double_t Graph4_fy1071[5] = {
   -0.003718665,
   0.002069351,
   0.02393716,
   0.01485094,
   0.06241022};
   Double_t Graph4_fex1071[5] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t Graph4_fey1071[5] = {
   0.0004243674,
   0.00052389,
   0.0004257729,
   0.0008048911,
   0.001212963};
   gre = new TGraphErrors(5,Graph4_fx1071,Graph4_fy1071,Graph4_fex1071,Graph4_fey1071);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");

   ci = 1262;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("pe5");
   
   Double_t Graph5_fx1072[5] = {
   0.05931037,
   0.1079293,
   0.2024818,
   0.3505484,
   0.4901615};
   Double_t Graph5_fy1072[5] = {
   -0.003718665,
   0.002069351,
   0.02393716,
   0.01485094,
   0.06241022};
   Double_t Graph5_fex1072[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1072[5] = {
   0.007232677,
   0.004682535,
   0.003773716,
   0.007930422,
   0.01358463};
   gre = new TGraphErrors(5,Graph5_fx1072,Graph5_fy1072,Graph5_fex1072,Graph5_fey1072);
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
