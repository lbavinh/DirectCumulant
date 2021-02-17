void v2v3_ParticlesPads_cent060()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Sun Oct  4 12:44:06 2020) by ROOT version 6.18/02

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
   
   Double_t Graph0_fx1001[14] = {
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
   Double_t Graph0_fy1001[14] = {
   0.02230387,
   0.0426843,
   0.06271061,
   0.08017352,
   0.09504862,
   0.1066192,
   0.1170707,
   0.1234326,
   0.1290371,
   0.1323422,
   0.1351317,
   0.1406452,
   0.1420168,
   0.1406747};
   Double_t Graph0_fex1001[14] = {
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
   Double_t Graph0_fey1001[14] = {
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
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,-0.085,3.27);
   Graph_Graph01001->SetMinimum(-0.02);
   Graph_Graph01001->SetMaximum(0.32);
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
   Double_t Graph1_fy1002[14] = {
   0.02230387,
   0.0426843,
   0.06271061,
   0.08017352,
   0.09504862,
   0.1066192,
   0.1170707,
   0.1234326,
   0.1290371,
   0.1323422,
   0.1351317,
   0.1406452,
   0.1420168,
   0.1406747};
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
   0.0001035687,
   9.579356e-05,
   0.0001104502,
   0.0001363054,
   0.0001735694,
   0.0002231148,
   0.0002896618,
   0.0003816863,
   0.0005098312,
   0.0006992524,
   0.0009833472,
   0.001375963,
   0.001913476,
   0.002636002};
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
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph2_fy1003[7] = {
   0.01218365,
   0.02862936,
   0.04839499,
   0.06648491,
   0.082899,
   0.09593631,
   0.1057565};
   Double_t Graph2_fex1003[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1003[7] = {
   6.024512e-05,
   0.000220157,
   0.0004128988,
   0.0005098657,
   0.0006472391,
   0.0008431012,
   0.0009466611};
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
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph3_fy1004[7] = {
   0.01218365,
   0.02862936,
   0.04839499,
   0.06648491,
   0.082899,
   0.09593631,
   0.1057565};
   Double_t Graph3_fex1004[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1004[7] = {
   0.0006328581,
   0.0003149454,
   0.0002707895,
   0.0002994432,
   0.0003796979,
   0.0005049885,
   0.0006810575};
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
   Double_t Graph4_fy1005[12] = {
   0.02116813,
   0.03972409,
   0.05995999,
   0.0808681,
   0.1009756,
   0.1171783,
   0.1317365,
   0.1459458,
   0.1554121,
   0.1671734,
   0.1755878,
   0.1793061};
   Double_t Graph4_fex1005[12] = {
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
   Double_t Graph4_fey1005[12] = {
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
   0.001116802};
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
   Double_t Graph5_fy1006[12] = {
   0.02116813,
   0.03972409,
   0.05995999,
   0.0808681,
   0.1009756,
   0.1171783,
   0.1317365,
   0.1459458,
   0.1554121,
   0.1671734,
   0.1755878,
   0.1793061};
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
   0.000353613,
   0.0002819215,
   0.0002653757,
   0.0002778736,
   0.0003153033,
   0.0003805838,
   0.0004794761,
   0.0006227428,
   0.000851083,
   0.001177135,
   0.001321171,
   0.00271475};
   gre = new TGraphErrors(12,Graph5_fx1006,Graph5_fy1006,Graph5_fex1006,Graph5_fey1006);
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
   
   Double_t Graph0_fx1007[7] = {
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph0_fy1007[7] = {
   0.01516877,
   0.04415146,
   0.0802734,
   0.1141365,
   0.1408191,
   0.1706185,
   0.1885558};
   Double_t Graph0_fex1007[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1007[7] = {
   0.0001022449,
   0.0005302357,
   0.001307843,
   0.002434605,
   0.003028863,
   0.003706161,
   0.005677942};
   gre = new TGraphErrors(7,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1248;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","",100,-0.085,3.27);
   Graph_Graph01007->SetMinimum(-0.02);
   Graph_Graph01007->SetMaximum(0.32);
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
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph1_fy1008[7] = {
   0.01516877,
   0.04415146,
   0.0802734,
   0.1141365,
   0.1408191,
   0.1706185,
   0.1885558};
   Double_t Graph1_fex1008[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1008[7] = {
   0.0004924768,
   0.0005149038,
   0.0006959993,
   0.00100272,
   0.001362802,
   0.002254984,
   0.005949406};
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
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph2_fy1009[4] = {
   0.01052476,
   0.03095597,
   0.06014365,
   0.09361202};
   Double_t Graph2_fex1009[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1009[4] = {
   0.0001022449,
   0.0005302357,
   0.001307843,
   0.002434605};
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
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph3_fy1010[4] = {
   0.01052476,
   0.03095597,
   0.06014365,
   0.09361202};
   Double_t Graph3_fex1010[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1010[4] = {
   0.002336422,
   0.001336955,
   0.001501905,
   0.002208317};
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
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph4_fy1011[6] = {
   0.0156551,
   0.04525208,
   0.08805548,
   0.1333347,
   0.1908087,
   0.2585641};
   Double_t Graph4_fex1011[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1011[6] = {
   0.0005302357,
   0.001307843,
   0.002434605,
   0.003028863,
   0.003706161,
   0.005677942};
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
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph5_fy1012[6] = {
   0.0156551,
   0.04525208,
   0.08805548,
   0.1333347,
   0.1908087,
   0.2585641};
   Double_t Graph5_fex1012[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1012[6] = {
   0.001645026,
   0.001300334,
   0.001354277,
   0.001532169,
   0.002274313,
   0.005719126};
   gre = new TGraphErrors(6,Graph5_fx1012,Graph5_fy1012,Graph5_fex1012,Graph5_fey1012);
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
   
   Double_t Graph0_fx1013[14] = {
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
   Double_t Graph0_fy1013[14] = {
   0.02172661,
   0.04154514,
   0.06047488,
   0.07712636,
   0.09132593,
   0.1030104,
   0.1121221,
   0.1189207,
   0.1251412,
   0.128901,
   0.1321695,
   0.1334642,
   0.1384022,
   0.1338039};
   Double_t Graph0_fex1013[14] = {
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
   Double_t Graph0_fey1013[14] = {
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
   gre = new TGraphErrors(14,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1230;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01013 = new TH1F("Graph_Graph01013","",100,-0.085,3.27);
   Graph_Graph01013->SetMinimum(-0.02);
   Graph_Graph01013->SetMaximum(0.32);
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
   Double_t Graph1_fy1014[14] = {
   0.02172661,
   0.04154514,
   0.06047488,
   0.07712636,
   0.09132593,
   0.1030104,
   0.1121221,
   0.1189207,
   0.1251412,
   0.128901,
   0.1321695,
   0.1334642,
   0.1384022,
   0.1338039};
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
   7.665574e-05,
   7.168398e-05,
   8.324222e-05,
   0.0001038771,
   0.0001344216,
   0.0001762043,
   0.0002333529,
   0.0003115839,
   0.0004186165,
   0.0005764544,
   0.0008131135,
   0.001143396,
   0.001598477,
   0.002218729};
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
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph2_fy1015[7] = {
   0.01264924,
   0.02839358,
   0.0474264,
   0.0641507,
   0.07834066,
   0.09042522,
   0.1000949};
   Double_t Graph2_fex1015[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1015[7] = {
   4.293925e-05,
   0.000237891,
   0.0004453871,
   0.0006120029,
   0.0007785774,
   0.0008631873,
   0.0009997836};
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
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.3,
   1.5};
   Double_t Graph3_fy1016[7] = {
   0.01264924,
   0.02839358,
   0.0474264,
   0.0641507,
   0.07834066,
   0.09042522,
   0.1000949};
   Double_t Graph3_fex1016[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1016[7] = {
   0.0004513249,
   0.0002301547,
   0.0001976565,
   0.0002108056,
   0.0002546695,
   0.0003266664,
   0.000431701};
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
   Double_t Graph4_fy1017[12] = {
   0.02290579,
   0.04118833,
   0.06175443,
   0.08174388,
   0.100196,
   0.1163312,
   0.129818,
   0.1421697,
   0.1523919,
   0.1601057,
   0.1682062,
   0.1727804};
   Double_t Graph4_fex1017[12] = {
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
   Double_t Graph4_fey1017[12] = {
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
   0.001174012};
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
   Double_t Graph5_fy1018[12] = {
   0.02290579,
   0.04118833,
   0.06175443,
   0.08174388,
   0.100196,
   0.1163312,
   0.129818,
   0.1421697,
   0.1523919,
   0.1601057,
   0.1682062,
   0.1727804};
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
   0.0002334373,
   0.0001894225,
   0.0001807113,
   0.00019006,
   0.000213917,
   0.0002537633,
   0.000313421,
   0.0004001104,
   0.0005402371,
   0.0007416392,
   0.0008312394,
   0.001720503};
   gre = new TGraphErrors(12,Graph5_fx1018,Graph5_fy1018,Graph5_fex1018,Graph5_fey1018);
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
   
   Double_t Graph0_fx1019[7] = {
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph0_fy1019[7] = {
   0.01424715,
   0.04156284,
   0.07539448,
   0.1065209,
   0.13197,
   0.1627968,
   0.1848243};
   Double_t Graph0_fex1019[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1019[7] = {
   6.308166e-05,
   0.0004831624,
   0.001240194,
   0.002151077,
   0.00342592,
   0.004952157,
   0.004983159};
   gre = new TGraphErrors(7,Graph0_fx1019,Graph0_fy1019,Graph0_fex1019,Graph0_fey1019);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1236;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01019 = new TH1F("Graph_Graph01019","",100,-0.085,3.27);
   Graph_Graph01019->SetMinimum(-0.02);
   Graph_Graph01019->SetMaximum(0.32);
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
   0.35,
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph1_fy1020[7] = {
   0.01424715,
   0.04156284,
   0.07539448,
   0.1065209,
   0.13197,
   0.1627968,
   0.1848243};
   Double_t Graph1_fex1020[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1020[7] = {
   0.0003932576,
   0.0004156889,
   0.0005708358,
   0.0008443926,
   0.001185402,
   0.001996106,
   0.00532096};
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
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph2_fy1021[4] = {
   0.00975183,
   0.02958868,
   0.056261,
   0.08350212};
   Double_t Graph2_fex1021[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1021[4] = {
   6.308166e-05,
   0.0004831624,
   0.001240194,
   0.002151077};
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
   0.35,
   0.65,
   0.95,
   1.25};
   Double_t Graph3_fy1022[4] = {
   0.00975183,
   0.02958868,
   0.056261,
   0.08350212};
   Double_t Graph3_fex1022[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1022[4] = {
   0.001807116,
   0.001044816,
   0.001115609,
   0.001530079};
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
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph4_fy1023[6] = {
   0.01543869,
   0.04727293,
   0.0851413,
   0.1360519,
   0.1891926,
   0.2451467};
   Double_t Graph4_fex1023[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1023[6] = {
   0.0004831624,
   0.001240194,
   0.002151077,
   0.00342592,
   0.004952157,
   0.004983159};
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
   0.65,
   0.95,
   1.25,
   1.6,
   2.1,
   2.8};
   Double_t Graph5_fy1024[6] = {
   0.01543869,
   0.04727293,
   0.0851413,
   0.1360519,
   0.1891926,
   0.2451467};
   Double_t Graph5_fex1024[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1024[6] = {
   0.001166288,
   0.0009406468,
   0.0009846209,
   0.001087811,
   0.001547315,
   0.003798013};
   gre = new TGraphErrors(6,Graph5_fx1024,Graph5_fy1024,Graph5_fex1024,Graph5_fey1024);
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
   
   Double_t v2_PionsPlusSys_fx1025[12] = {
   0.2991951,
   0.4901901,
   0.6884703,
   0.8879543,
   1.087783,
   1.287849,
   1.488019,
   1.688089,
   1.888079,
   2.088141,
   2.354136,
   2.802763};
   Double_t v2_PionsPlusSys_fy1025[12] = {
   0.02195479,
   0.04116438,
   0.05934349,
   0.07526411,
   0.08853097,
   0.09974085,
   0.1083885,
   0.1150062,
   0.1201339,
   0.1242736,
   0.127264,
   0.1320133};
   Double_t v2_PionsPlusSys_fex1025[12] = {
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
   Double_t v2_PionsPlusSys_fey1025[12] = {
   3.169811e-05,
   0.0002391877,
   0.000447512,
   0.0006878044,
   0.0007946885,
   0.000882219,
   0.0008353776,
   0.001047781,
   0.001156921,
   0.001474907,
   0.001077326,
   0.00189985};
   gre = new TGraphErrors(12,v2_PionsPlusSys_fx1025,v2_PionsPlusSys_fy1025,v2_PionsPlusSys_fex1025,v2_PionsPlusSys_fey1025);
   gre->SetName("v2_PionsPlusSys");
   gre->SetTitle("");

   ci = 1218;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v2_PionsPlusSys1025 = new TH1F("Graph_v2_PionsPlusSys1025","",100,-0.085,3.27);
   Graph_v2_PionsPlusSys1025->SetMinimum(-0.02);
   Graph_v2_PionsPlusSys1025->SetMaximum(0.32);
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
   0.2991951,
   0.4901901,
   0.6884703,
   0.8879543,
   1.087783,
   1.287849,
   1.488019,
   1.688089,
   1.888079,
   2.088141,
   2.354136,
   2.802763};
   Double_t v2_PionsPlus_fy1026[12] = {
   0.02195479,
   0.04116438,
   0.05934349,
   0.07526411,
   0.08853097,
   0.09974085,
   0.1083885,
   0.1150062,
   0.1201339,
   0.1242736,
   0.127264,
   0.1320133};
   Double_t v2_PionsPlus_fex1026[12] = {
   6.894301e-07,
   8.407829e-07,
   1.163792e-06,
   1.661058e-06,
   2.39835e-06,
   3.472483e-06,
   5.003982e-06,
   7.184709e-06,
   1.030345e-05,
   1.476816e-05,
   3.337851e-05,
   8.901756e-05};
   Double_t v2_PionsPlus_fey1026[12] = {
   4.125413e-05,
   3.892052e-05,
   4.546767e-05,
   5.715277e-05,
   7.450918e-05,
   9.903505e-05,
   0.0001326164,
   0.0001785383,
   0.0002418508,
   0.0003362712,
   0.0003933606,
   0.0007347769};
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
   0.3365259,
   0.5041026,
   0.6954666,
   0.8913195,
   1.089088,
   1.288199,
   1.487867};
   Double_t v2_KaonsPlusSys_fy1027[7] = {
   0.01355163,
   0.02913361,
   0.04702966,
   0.0630246,
   0.07683982,
   0.08785541,
   0.09694641};
   Double_t v2_KaonsPlusSys_fex1027[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v2_KaonsPlusSys_fey1027[7] = {
   3.169811e-05,
   0.0002391877,
   0.000447512,
   0.0006878044,
   0.0007946885,
   0.000882219,
   0.0008353776};
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
   0.3365259,
   0.5041026,
   0.6954666,
   0.8913195,
   1.089088,
   1.288199,
   1.487867};
   Double_t v2_KaonsPlus_fy1028[7] = {
   0.01355163,
   0.02913361,
   0.04702966,
   0.0630246,
   0.07683982,
   0.08785541,
   0.09694641};
   Double_t v2_KaonsPlus_fex1028[7] = {
   3.218051e-06,
   2.632175e-06,
   2.708307e-06,
   3.304161e-06,
   4.435281e-06,
   6.2577e-06,
   8.984738e-06};
   Double_t v2_KaonsPlus_fey1028[7] = {
   0.0002317492,
   0.0001204259,
   0.0001047296,
   0.0001131343,
   0.0001376827,
   0.000178708,
   0.0002387542};
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
   0.6049947,
   0.7993479,
   0.9957967,
   1.193547,
   1.39219,
   1.591073,
   1.790185,
   1.989547,
   2.189133,
   2.388842,
   2.655731,
   3.024724};
   Double_t v2_ProtonsPlusSys_fy1029[12] = {
   0.02448735,
   0.04258804,
   0.06271342,
   0.08216994,
   0.09963329,
   0.1153978,
   0.1290457,
   0.1402705,
   0.1509665,
   0.1576729,
   0.1654998,
   0.1757026};
   Double_t v2_ProtonsPlusSys_fex1029[12] = {
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
   Double_t v2_ProtonsPlusSys_fey1029[12] = {
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
   0.6049947,
   0.7993479,
   0.9957967,
   1.193547,
   1.39219,
   1.591073,
   1.790185,
   1.989547,
   2.189133,
   2.388842,
   2.655731,
   3.024724};
   Double_t v2_ProtonsPlus_fy1030[12] = {
   0.02448735,
   0.04258804,
   0.06271342,
   0.08216994,
   0.09963329,
   0.1153978,
   0.1290457,
   0.1402705,
   0.1509665,
   0.1576729,
   0.1654998,
   0.1757026};
   Double_t v2_ProtonsPlus_fex1030[12] = {
   2.647885e-06,
   2.510852e-06,
   2.710113e-06,
   3.180839e-06,
   3.938995e-06,
   5.058371e-06,
   6.701031e-06,
   9.086036e-06,
   1.252591e-05,
   1.744694e-05,
   3.858254e-05,
   6.322475e-05};
   Double_t v2_ProtonsPlus_fey1030[12] = {
   0.0001098298,
   9.01585e-05,
   8.724588e-05,
   9.372074e-05,
   0.0001076688,
   0.0001295386,
   0.0001619103,
   0.0002093277,
   0.0002862439,
   0.0003984183,
   0.0004550516,
   0.000971815};
   gre = new TGraphErrors(12,v2_ProtonsPlus_fx1030,v2_ProtonsPlus_fy1030,v2_ProtonsPlus_fex1030,v2_ProtonsPlus_fey1030);
   gre->SetName("v2_ProtonsPlus");
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
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{ 27 GeV Run18 } }");
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
   
   Double_t v3_PionsPlusSys_fx1031[7] = {
   0.3411545,
   0.6249777,
   0.9230846,
   1.222863,
   1.553378,
   1.999755,
   2.634247};
   Double_t v3_PionsPlusSys_fy1031[7] = {
   0.01331131,
   0.03904083,
   0.07053617,
   0.1000185,
   0.1259021,
   0.1508224,
   0.1700106};
   Double_t v3_PionsPlusSys_fex1031[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_PionsPlusSys_fey1031[7] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   gre = new TGraphErrors(7,v3_PionsPlusSys_fx1031,v3_PionsPlusSys_fy1031,v3_PionsPlusSys_fex1031,v3_PionsPlusSys_fey1031);
   gre->SetName("v3_PionsPlusSys");
   gre->SetTitle("");

   ci = 1224;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v3_PionsPlusSys1031 = new TH1F("Graph_v3_PionsPlusSys1031","",100,-0.085,3.27);
   Graph_v3_PionsPlusSys1031->SetMinimum(-0.02);
   Graph_v3_PionsPlusSys1031->SetMaximum(0.32);
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
   0.3411545,
   0.6249777,
   0.9230846,
   1.222863,
   1.553378,
   1.999755,
   2.634247};
   Double_t v3_PionsPlus_fy1032[7] = {
   0.01331131,
   0.03904083,
   0.07053617,
   0.1000185,
   0.1259021,
   0.1508224,
   0.1700106};
   Double_t v3_PionsPlus_fex1032[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_PionsPlus_fey1032[7] = {
   0.0002278114,
   0.0002434647,
   0.0003372383,
   0.0005056904,
   0.0007193392,
   0.001228983,
   0.003396896};
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
   0.3986119,
   0.6437496,
   0.92927,
   1.224081};
   Double_t v3_KaonsPlusSys_fy1033[4] = {
   0.008524177,
   0.02771368,
   0.05314108,
   0.07931415};
   Double_t v3_KaonsPlusSys_fex1033[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_KaonsPlusSys_fey1033[4] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421};
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
   0.3986119,
   0.6437496,
   0.92927,
   1.224081};
   Double_t v3_KaonsPlus_fy1034[4] = {
   0.008524177,
   0.02771368,
   0.05314108,
   0.07931415};
   Double_t v3_KaonsPlus_fex1034[4] = {
   0,
   0,
   0,
   0};
   Double_t v3_KaonsPlus_fey1034[4] = {
   0.0009974252,
   0.0005883808,
   0.0006399172,
   0.0008910947};
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
   0.6575329,
   0.9423184,
   1.234741,
   1.565072,
   2.0097,
   2.636862};
   Double_t v3_ProtonsPlusSys_fy1035[6] = {
   0.0152527,
   0.04533733,
   0.08577327,
   0.1319009,
   0.1849764,
   0.239242};
   Double_t v3_ProtonsPlusSys_fex1035[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_ProtonsPlusSys_fey1035[6] = {
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
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
   0.6575329,
   0.9423184,
   1.234741,
   1.565072,
   2.0097,
   2.636862};
   Double_t v3_ProtonsPlus_fy1036[6] = {
   0.0152527,
   0.04533733,
   0.08577327,
   0.1319009,
   0.1849764,
   0.239242};
   Double_t v3_ProtonsPlus_fex1036[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_ProtonsPlus_fey1036[6] = {
   0.0005855933,
   0.0004817701,
   0.0005193398,
   0.0005891997,
   0.000861728,
   0.002206044};
   gre = new TGraphErrors(6,v3_ProtonsPlus_fx1036,v3_ProtonsPlus_fy1036,v3_ProtonsPlus_fex1036,v3_ProtonsPlus_fey1036);
   gre->SetName("v3_ProtonsPlus");
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
   
   Double_t Graph0_fx1037[11] = {
   0.2989304,
   0.4898766,
   0.6881114,
   0.887579,
   1.087377,
   1.287359,
   1.487327,
   1.687243,
   1.950585,
   2.351362,
   2.795866};
   Double_t Graph0_fy1037[11] = {
   0.02139083,
   0.0400534,
   0.05734295,
   0.07227868,
   0.08491252,
   0.09379193,
   0.1033585,
   0.1087823,
   0.1132825,
   0.119503,
   0.1134677};
   Double_t Graph0_fex1037[11] = {
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
   Double_t Graph0_fey1037[11] = {
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
   gre = new TGraphErrors(11,Graph0_fx1037,Graph0_fy1037,Graph0_fex1037,Graph0_fey1037);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1206;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01037 = new TH1F("Graph_Graph01037","",100,-0.085,3.27);
   Graph_Graph01037->SetMinimum(-0.02);
   Graph_Graph01037->SetMaximum(0.32);
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
   0.2989304,
   0.4898766,
   0.6881114,
   0.887579,
   1.087377,
   1.287359,
   1.487327,
   1.687243,
   1.950585,
   2.351362,
   2.795866};
   Double_t Graph1_fy1038[11] = {
   0.02139083,
   0.0400534,
   0.05734295,
   0.07227868,
   0.08491252,
   0.09379193,
   0.1033585,
   0.1087823,
   0.1132825,
   0.119503,
   0.1134677};
   Double_t Graph1_fex1038[11] = {
   2.944927e-06,
   3.62431e-06,
   5.063695e-06,
   7.304623e-06,
   1.069337e-05,
   1.567518e-05,
   2.29927e-05,
   3.379363e-05,
   7.890032e-05,
   0.0001699393,
   0.000475569};
   Double_t Graph1_fey1038[11] = {
   0.0001921033,
   0.000182937,
   0.0002157918,
   0.0002742524,
   0.000362432,
   0.000488226,
   0.0006655149,
   0.0009176658,
   0.001044742,
   0.002202315,
   0.004354614};
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
   0.3369859,
   0.5037788,
   0.6950445,
   0.8906841,
   1.088459,
   1.287619,
   1.487292};
   Double_t Graph2_fy1039[7] = {
   0.01372848,
   0.02820637,
   0.04649458,
   0.06136785,
   0.07334557,
   0.08395568,
   0.09178575};
   Double_t Graph2_fex1039[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1039[7] = {
   3.169811e-05,
   0.0002391877,
   0.000447512,
   0.0006878044,
   0.0007946885,
   0.000882219,
   0.0008353776};
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
   0.3369859,
   0.5037788,
   0.6950445,
   0.8906841,
   1.088459,
   1.287619,
   1.487292};
   Double_t Graph3_fy1040[7] = {
   0.01372848,
   0.02820637,
   0.04649458,
   0.06136785,
   0.07334557,
   0.08395568,
   0.09178575};
   Double_t Graph3_fex1040[7] = {
   1.342084e-05,
   1.109997e-05,
   1.153043e-05,
   1.426505e-05,
   1.953995e-05,
   2.806338e-05,
   4.111777e-05};
   Double_t Graph3_fey1040[7] = {
   0.001059723,
   0.0005528879,
   0.0004861391,
   0.0005333224,
   0.0006625039,
   0.0008752538,
   0.001191731};
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
   0.6046751,
   0.7990633,
   0.9955173,
   1.193381,
   1.39175,
   1.590513,
   1.789594,
   1.989034,
   2.188494,
   2.388358,
   2.653658,
   3.022858};
   Double_t Graph4_fy1041[12] = {
   0.02438303,
   0.04243116,
   0.06200721,
   0.08106184,
   0.09865105,
   0.1128954,
   0.1249868,
   0.1357043,
   0.1453374,
   0.1513634,
   0.1616979,
   0.1613765};
   Double_t Graph4_fex1041[12] = {
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
   Double_t Graph4_fey1041[12] = {
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
   0.6046751,
   0.7990633,
   0.9955173,
   1.193381,
   1.39175,
   1.590513,
   1.789594,
   1.989034,
   2.188494,
   2.388358,
   2.653658,
   3.022858};
   Double_t Graph5_fy1042[12] = {
   0.02438303,
   0.04243116,
   0.06200721,
   0.08106184,
   0.09865105,
   0.1128954,
   0.1249868,
   0.1357043,
   0.1453374,
   0.1513634,
   0.1616979,
   0.1613765};
   Double_t Graph5_fex1042[12] = {
   1.012468e-05,
   9.709991e-06,
   1.056188e-05,
   1.246531e-05,
   1.555797e-05,
   2.028948e-05,
   2.734946e-05,
   3.771999e-05,
   5.280305e-05,
   7.498694e-05,
   0.0001689613,
   0.000285865};
   Double_t Graph5_fey1042[12] = {
   0.0004571933,
   0.0003796971,
   0.0003705751,
   0.0004007043,
   0.0004642499,
   0.0005673959,
   0.0007221026,
   0.0009493665,
   0.001319726,
   0.001868272,
   0.002183771,
   0.004832195};
   gre = new TGraphErrors(12,Graph5_fx1042,Graph5_fy1042,Graph5_fex1042,Graph5_fey1042);
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
   
   Double_t Graph0_fx1043[7] = {
   0.3405248,
   0.6242741,
   0.9221761,
   1.221907,
   1.550584,
   1.993708,
   2.623691};
   Double_t Graph0_fy1043[7] = {
   0.01269312,
   0.03689953,
   0.06570131,
   0.09475548,
   0.1204107,
   0.1589198,
   0.1315646};
   Double_t Graph0_fex1043[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1043[7] = {
   0.0003008765,
   0.0003064206,
   0.001197021,
   0.002394465,
   0.004534064,
   0.004058159,
   0.006601629};
   gre = new TGraphErrors(7,Graph0_fx1043,Graph0_fy1043,Graph0_fex1043,Graph0_fey1043);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1212;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01043 = new TH1F("Graph_Graph01043","",100,-0.085,3.27);
   Graph_Graph01043->SetMinimum(-0.02);
   Graph_Graph01043->SetMaximum(0.32);
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
   0.3405248,
   0.6242741,
   0.9221761,
   1.221907,
   1.550584,
   1.993708,
   2.623691};
   Double_t Graph1_fy1044[7] = {
   0.01269312,
   0.03689953,
   0.06570131,
   0.09475548,
   0.1204107,
   0.1589198,
   0.1315646};
   Double_t Graph1_fex1044[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1044[7] = {
   0.001108045,
   0.001199449,
   0.001686354,
   0.002573938,
   0.003766351,
   0.00677734,
   0.02010707};
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
   0.3987842,
   0.6429322,
   0.9278319,
   1.22284};
   Double_t Graph2_fy1045[4] = {
   0.007485941,
   0.02345231,
   0.05145367,
   0.0746891};
   Double_t Graph2_fex1045[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1045[4] = {
   0.0003008765,
   0.0003064206,
   0.001197021,
   0.002394465};
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
   0.3987842,
   0.6429322,
   0.9278319,
   1.22284};
   Double_t Graph3_fy1046[4] = {
   0.007485941,
   0.02345231,
   0.05145367,
   0.0746891};
   Double_t Graph3_fex1046[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1046[4] = {
   0.004746858,
   0.002826275,
   0.003134791,
   0.004484009};
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
   0.6567246,
   0.9417258,
   1.234276,
   1.562964,
   2.005589,
   2.630025};
   Double_t Graph4_fy1047[6] = {
   0.01715387,
   0.0416578,
   0.08392294,
   0.1281672,
   0.1882193,
   0.2252646};
   Double_t Graph4_fex1047[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1047[6] = {
   0.0003064206,
   0.001197021,
   0.002394465,
   0.004534064,
   0.004058159,
   0.006601629};
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
   0.6567246,
   0.9417258,
   1.234276,
   1.562964,
   2.005589,
   2.630025};
   Double_t Graph5_fy1048[6] = {
   0.01715387,
   0.0416578,
   0.08392294,
   0.1281672,
   0.1882193,
   0.2252646};
   Double_t Graph5_fex1048[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1048[6] = {
   0.00254181,
   0.002114143,
   0.002298932,
   0.002662055,
   0.004037124,
   0.01086727};
   gre = new TGraphErrors(6,Graph5_fx1048,Graph5_fy1048,Graph5_fex1048,Graph5_fey1048);
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
   
   Double_t Graph0_fx1049[12] = {
   0.2971273,
   0.4894864,
   0.6877026,
   0.887237,
   1.087114,
   1.28721,
   1.4872,
   1.687179,
   1.887094,
   2.087033,
   2.286953,
   2.486774};
   Double_t Graph0_fy1049[12] = {
   0.02230217,
   0.04043021,
   0.05658635,
   0.07105785,
   0.08136705,
   0.0916065,
   0.09802973,
   0.1037977,
   0.1068264,
   0.1110322,
   0.1158112,
   0.1209312};
   Double_t Graph0_fex1049[12] = {
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
   Double_t Graph0_fey1049[12] = {
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
   gre = new TGraphErrors(12,Graph0_fx1049,Graph0_fy1049,Graph0_fex1049,Graph0_fey1049);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1194;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01049 = new TH1F("Graph_Graph01049","",100,-0.085,3.27);
   Graph_Graph01049->SetMinimum(-0.02);
   Graph_Graph01049->SetMaximum(0.32);
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
   0.2971273,
   0.4894864,
   0.6877026,
   0.887237,
   1.087114,
   1.28721,
   1.4872,
   1.687179,
   1.887094,
   2.087033,
   2.286953,
   2.486774};
   Double_t Graph1_fy1050[12] = {
   0.02230217,
   0.04043021,
   0.05658635,
   0.07105785,
   0.08136705,
   0.0916065,
   0.09802973,
   0.1037977,
   0.1068264,
   0.1110322,
   0.1158112,
   0.1209312};
   Double_t Graph1_fex1050[12] = {
   3.311058e-06,
   4.140697e-06,
   5.854819e-06,
   8.556532e-06,
   1.263995e-05,
   1.863796e-05,
   2.743329e-05,
   4.042707e-05,
   5.981445e-05,
   8.862467e-05,
   0.0001316123,
   0.0001959398};
   Double_t Graph1_fey1050[12] = {
   0.0002305834,
   0.0002239636,
   0.0002673713,
   0.0003439542,
   0.0004586305,
   0.0006212308,
   0.0008508239,
   0.001176498,
   0.001642281,
   0.002367646,
   0.003510868,
   0.005215915};
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
   0.3356671,
   0.5035303,
   0.6949847,
   0.8903672,
   1.087753,
   1.286792,
   1.486475};
   Double_t Graph2_fy1051[7] = {
   0.01597889,
   0.03011972,
   0.04581967,
   0.0611798,
   0.07257309,
   0.08332238,
   0.09060173};
   Double_t Graph2_fex1051[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1051[7] = {
   0.0001137964,
   0.0002627299,
   0.0005399538,
   0.0005345494,
   0.0008808209,
   0.0006777511,
   0.0008020956};
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
   0.3356671,
   0.5035303,
   0.6949847,
   0.8903672,
   1.087753,
   1.286792,
   1.486475};
   Double_t Graph3_fy1052[7] = {
   0.01597889,
   0.03011972,
   0.04581967,
   0.0611798,
   0.07257309,
   0.08332238,
   0.09060173};
   Double_t Graph3_fex1052[7] = {
   1.515352e-05,
   1.268118e-05,
   1.321067e-05,
   1.642233e-05,
   2.282909e-05,
   3.345564e-05,
   5.008534e-05};
   Double_t Graph3_fey1052[7] = {
   0.001269387,
   0.0006755707,
   0.0005958925,
   0.0006572112,
   0.0008289809,
   0.001118492,
   0.001559381};
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
   0.6035246,
   0.7983985,
   0.9949951,
   1.193006,
   1.391282,
   1.589947,
   1.788978,
   1.988394,
   2.188158,
   2.387774,
   2.587728,
   2.787837};
   Double_t Graph4_fy1053[12] = {
   0.02714078,
   0.04374459,
   0.06289835,
   0.08147496,
   0.09665377,
   0.1107334,
   0.1218157,
   0.1327759,
   0.1391547,
   0.1463637,
   0.147305,
   0.1552017};
   Double_t Graph4_fex1053[12] = {
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
   Double_t Graph4_fey1053[12] = {
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
   0.001281732,
   0.001554559};
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
   0.6035246,
   0.7983985,
   0.9949951,
   1.193006,
   1.391282,
   1.589947,
   1.788978,
   1.988394,
   2.188158,
   2.387774,
   2.587728,
   2.787837};
   Double_t Graph5_fy1054[12] = {
   0.02714078,
   0.04374459,
   0.06289835,
   0.08147496,
   0.09665377,
   0.1107334,
   0.1218157,
   0.1327759,
   0.1391547,
   0.1463637,
   0.147305,
   0.1552017};
   Double_t Graph5_fex1054[12] = {
   9.812657e-06,
   9.623247e-06,
   1.062604e-05,
   1.272097e-05,
   1.60833e-05,
   2.128832e-05,
   2.917377e-05,
   4.098452e-05,
   5.845148e-05,
   8.419801e-05,
   0.0001225678,
   0.0001782748};
   Double_t Graph5_fey1054[12] = {
   0.0004737614,
   0.0004025509,
   0.0003991867,
   0.0004374367,
   0.0005134928,
   0.000637303,
   0.0008241722,
   0.00110495,
   0.001564053,
   0.002251032,
   0.003273238,
   0.004758307};
   gre = new TGraphErrors(12,Graph5_fx1054,Graph5_fy1054,Graph5_fex1054,Graph5_fey1054);
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
   
   Double_t Graph0_fx1055[7] = {
   0.3379638,
   0.6233802,
   0.9215031,
   1.221581,
   1.550213,
   1.991463,
   2.61701};
   Double_t Graph0_fy1055[7] = {
   0.0152675,
   0.03396489,
   0.05951363,
   0.08095592,
   0.1075577,
   0.1560302,
   0.1082512};
   Double_t Graph0_fex1055[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1055[7] = {
   0.0002996215,
   0.0002322319,
   0.001073177,
   0.002764091,
   0.003924008,
   0.002741888,
   0.01382106};
   gre = new TGraphErrors(7,Graph0_fx1055,Graph0_fy1055,Graph0_fex1055,Graph0_fey1055);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1200;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01055 = new TH1F("Graph_Graph01055","",100,-0.085,3.27);
   Graph_Graph01055->SetMinimum(-0.02);
   Graph_Graph01055->SetMaximum(0.32);
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
   0.3379638,
   0.6233802,
   0.9215031,
   1.221581,
   1.550213,
   1.991463,
   2.61701};
   Double_t Graph1_fy1056[7] = {
   0.0152675,
   0.03396489,
   0.05951363,
   0.08095592,
   0.1075577,
   0.1560302,
   0.1082512};
   Double_t Graph1_fex1056[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1056[7] = {
   0.001468985,
   0.001628165,
   0.002327059,
   0.003578502,
   0.005248997,
   0.009462801,
   0.0291895};
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
   0.3969551,
   0.6427292,
   0.9269264,
   1.221319};
   Double_t Graph2_fy1057[4] = {
   0.005934605,
   0.02957807,
   0.04904715,
   0.07228113};
   Double_t Graph2_fex1057[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1057[4] = {
   0.0002996215,
   0.0002322319,
   0.001073177,
   0.002764091};
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
   0.3969551,
   0.6427292,
   0.9269264,
   1.221319};
   Double_t Graph3_fy1058[4] = {
   0.005934605,
   0.02957807,
   0.04904715,
   0.07228113};
   Double_t Graph3_fex1058[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1058[4] = {
   0.006271905,
   0.003782675,
   0.004221424,
   0.006175094};
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
   0.6546167,
   0.9405704,
   1.233364,
   1.560998,
   2.00125,
   2.624745};
   Double_t Graph4_fy1059[6] = {
   0.01476337,
   0.05064471,
   0.08348365,
   0.1283392,
   0.1672151,
   0.2162817};
   Double_t Graph4_fex1059[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1059[6] = {
   0.0002322319,
   0.001073177,
   0.002764091,
   0.003924008,
   0.002741888,
   0.01382106};
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
   0.6546167,
   0.9405704,
   1.233364,
   1.560998,
   2.00125,
   2.624745};
   Double_t Graph5_fy1060[6] = {
   0.01476337,
   0.05064471,
   0.08348365,
   0.1283392,
   0.1672151,
   0.2162817};
   Double_t Graph5_fex1060[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1060[6] = {
   0.002890745,
   0.002473067,
   0.002740238,
   0.003240054,
   0.005082857,
   0.01435407};
   gre = new TGraphErrors(6,Graph5_fx1060,Graph5_fy1060,Graph5_fex1060,Graph5_fey1060);
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
   
   Double_t Graph0_fx1061[8] = {
   0.298498,
   0.4894145,
   0.6877389,
   0.8870638,
   1.149276,
   1.548657,
   1.886755,
   2.147635};
   Double_t Graph0_fy1061[8] = {
   0.02094551,
   0.03824357,
   0.05287696,
   0.06560865,
   0.07845826,
   0.09236076,
   0.1045031,
   0.09217682};
   Double_t Graph0_fex1061[8] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1061[8] = {
   0.0001009164,
   0.0002497888,
   0.0003092828,
   0.0005964932,
   0.0008696456,
   0.001022896,
   0.001154754,
   0.0007961114};
   gre = new TGraphErrors(8,Graph0_fx1061,Graph0_fy1061,Graph0_fex1061,Graph0_fey1061);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1182;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01061 = new TH1F("Graph_Graph01061","",100,-0.085,3.27);
   Graph_Graph01061->SetMinimum(-0.02);
   Graph_Graph01061->SetMaximum(0.32);
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
   0.298498,
   0.4894145,
   0.6877389,
   0.8870638,
   1.149276,
   1.548657,
   1.886755,
   2.147635};
   Double_t Graph1_fy1062[8] = {
   0.02094551,
   0.03824357,
   0.05287696,
   0.06560865,
   0.07845826,
   0.09236076,
   0.1045031,
   0.09217682};
   Double_t Graph1_fex1062[8] = {
   5.447759e-06,
   6.804315e-06,
   9.632266e-06,
   1.405563e-05,
   3.31639e-05,
   7.339652e-05,
   0.0001034703,
   0.0002465897};
   Double_t Graph1_fey1062[8] = {
   0.0004234704,
   0.0004095849,
   0.0004895192,
   0.0006301215,
   0.0006826525,
   0.001304243,
   0.003180127,
   0.003861514};
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
   0.3371773,
   0.5035064,
   0.6950098,
   0.8907322,
   1.088368,
   1.287304,
   1.4865};
   Double_t Graph2_fy1063[7] = {
   0.01300897,
   0.02842276,
   0.04246927,
   0.05590999,
   0.06568932,
   0.07224172,
   0.0843498};
   Double_t Graph2_fex1063[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1063[7] = {
   0.0001009164,
   0.0002497888,
   0.0003092828,
   0.0005964932,
   0.000800543,
   0.0009705331,
   0.0008752071};
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
   0.3371773,
   0.5035064,
   0.6950098,
   0.8907322,
   1.088368,
   1.287304,
   1.4865};
   Double_t Graph3_fy1064[7] = {
   0.01300897,
   0.02842276,
   0.04246927,
   0.05590999,
   0.06568932,
   0.07224172,
   0.0843498};
   Double_t Graph3_fex1064[7] = {
   2.384744e-05,
   1.984956e-05,
   2.075083e-05,
   2.559758e-05,
   3.505403e-05,
   5.045001e-05,
   7.481144e-05};
   Double_t Graph3_fey1064[7] = {
   0.002247019,
   0.001177926,
   0.00104264,
   0.001142031,
   0.001418893,
   0.001881656,
   0.002594914};
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
   0.6045779,
   0.7987867,
   0.9951217,
   1.193122,
   1.39158,
   1.590266,
   1.789433,
   1.988752,
   2.188267,
   2.387886,
   2.651292,
   3.021958};
   Double_t Graph4_fy1065[12] = {
   0.02498878,
   0.04182496,
   0.05968944,
   0.07649035,
   0.0907094,
   0.1064604,
   0.1137203,
   0.1214704,
   0.1303487,
   0.1374833,
   0.1326749,
   0.1537455};
   Double_t Graph4_fex1065[12] = {
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
   Double_t Graph4_fey1065[12] = {
   0.0003272731,
   0.0004375545,
   0.0005900459,
   0.001089219,
   0.0008647379,
   0.0007801651,
   0.001743111,
   0.0008275973,
   0.001185425,
   0.0008484529,
   0.002646551,
   0.002926606};
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
   0.6045779,
   0.7987867,
   0.9951217,
   1.193122,
   1.39158,
   1.590266,
   1.789433,
   1.988752,
   2.188267,
   2.387886,
   2.651292,
   3.021958};
   Double_t Graph5_fy1066[12] = {
   0.02498878,
   0.04182496,
   0.05968944,
   0.07649035,
   0.0907094,
   0.1064604,
   0.1137203,
   0.1214704,
   0.1303487,
   0.1374833,
   0.1326749,
   0.1537455};
   Double_t Graph5_fex1066[12] = {
   1.458773e-05,
   1.405883e-05,
   1.547418e-05,
   1.843663e-05,
   2.316175e-05,
   3.039191e-05,
   4.125259e-05,
   5.729909e-05,
   8.125415e-05,
   0.0001164551,
   0.0002668361,
   0.0004745504};
   Double_t Graph5_fey1066[12] = {
   0.0007843007,
   0.0006552453,
   0.0006476137,
   0.0007073232,
   0.0008252424,
   0.001014822,
   0.001301547,
   0.001725232,
   0.002424945,
   0.003481789,
   0.004165685,
   0.009532468};
   gre = new TGraphErrors(12,Graph5_fx1066,Graph5_fy1066,Graph5_fex1066,Graph5_fey1066);
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
      tex = new TLatex(-0.05,0.26,"#scale[0.8]{ #font[42]{Au+Au #sqrt{s_{NN}} = 11.5 GeV} }");
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-0.05,0.19,"#scale[1.0]{ #font[42]{ v_{2} } }");
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
   
   Double_t Graph0_fx1067[7] = {
   0.3394782,
   0.6234089,
   0.9210575,
   1.22099,
   1.548657,
   1.98834,
   2.612132};
   Double_t Graph0_fy1067[7] = {
   0.01228588,
   0.03393287,
   0.06281624,
   0.07485,
   0.1038329,
   0.1673236,
   0.2220671};
   Double_t Graph0_fex1067[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph0_fey1067[7] = {
   0.001716966,
   0.001267891,
   0.002730168,
   0.002047547,
   0.003716983,
   0.005057148,
   0.02236226};
   gre = new TGraphErrors(7,Graph0_fx1067,Graph0_fy1067,Graph0_fex1067,Graph0_fey1067);
   gre->SetName("Graph0");
   gre->SetTitle("");

   ci = 1188;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_Graph01067 = new TH1F("Graph_Graph01067","",100,-0.085,3.27);
   Graph_Graph01067->SetMinimum(-0.02);
   Graph_Graph01067->SetMaximum(0.32);
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
   0.3394782,
   0.6234089,
   0.9210575,
   1.22099,
   1.548657,
   1.98834,
   2.612132};
   Double_t Graph1_fy1068[7] = {
   0.01228588,
   0.03393287,
   0.06281624,
   0.07485,
   0.1038329,
   0.1673236,
   0.2220671};
   Double_t Graph1_fex1068[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1068[7] = {
   0.002580629,
   0.002844301,
   0.004060737,
   0.006293799,
   0.009383357,
   0.01731342,
   0.05444473};
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
   0.3987717,
   0.5983129,
   0.8925861,
   1.349505};
   Double_t Graph2_fy1069[4] = {
   0.01301294,
   0.02255338,
   0.05174989,
   0.0733901};
   Double_t Graph2_fex1069[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph2_fey1069[4] = {
   0.001716966,
   0.002205078,
   0.002057398,
   0.006334881};
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
   0.3987717,
   0.5983129,
   0.8925861,
   1.349505};
   Double_t Graph3_fy1070[4] = {
   0.01301294,
   0.02255338,
   0.05174989,
   0.0733901};
   Double_t Graph3_fex1070[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph3_fey1070[4] = {
   0.01048157,
   0.007771973,
   0.005413979,
   0.01059117};
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
   0.6564302,
   0.9407982,
   1.233736,
   1.562093,
   2.002953,
   2.623277};
   Double_t Graph4_fy1071[6] = {
   0.0130297,
   0.04847776,
   0.0727581,
   0.1234319,
   0.127449,
   0.148815};
   Double_t Graph4_fex1071[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t Graph4_fey1071[6] = {
   0.001267891,
   0.002730168,
   0.002047547,
   0.003716983,
   0.005057148,
   0.02236226};
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
   0.6564302,
   0.9407982,
   1.233736,
   1.562093,
   2.002953,
   2.623277};
   Double_t Graph5_fy1072[6] = {
   0.0130297,
   0.04847776,
   0.0727581,
   0.1234319,
   0.127449,
   0.148815};
   Double_t Graph5_fex1072[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph5_fey1072[6] = {
   0.004549546,
   0.003820433,
   0.004201412,
   0.004900933,
   0.007518493,
   0.0208994};
   gre = new TGraphErrors(6,Graph5_fx1072,Graph5_fy1072,Graph5_fex1072,Graph5_fey1072);
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
      tex = new TLatex(-0.05,0.19,"#scale[1.0]{ #font[42]{ 2.5 #times v_{3}} }");
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
