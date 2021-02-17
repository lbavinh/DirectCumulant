void v3_27Run18gevAntiparticlesCent060_def()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Sun Oct  4 14:11:52 2020) by ROOT version 6.18/02

   gStyle->SetCanvasPreferGL(kTRUE);

   TCanvas *canvas = new TCanvas("canvas", "plot",0,0,640,480);
   canvas->Range(0,0,1,1);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetTickx(1);
   canvas->SetTicky(1);
   canvas->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "This is pad1",0.08,0,1,1);
   pad1->Draw();
   pad1->cd();
   pad1->Range(0,0,1,1);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetFrameBorderMode(0);
   
   Double_t v3_PionsMinusSys_fx1019[7] = {
   0.3406721,
   0.6247821,
   0.9229881,
   1.222788,
   1.553068,
   1.997742,
   2.629163};
   Double_t v3_PionsMinusSys_fy1019[7] = {
   0.01445203,
   0.04021591,
   0.07182095,
   0.1014213,
   0.1282611,
   0.1563321,
   0.1681419};
   Double_t v3_PionsMinusSys_fex1019[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_PionsMinusSys_fey1019[7] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   TGraphErrors *gre = new TGraphErrors(7,v3_PionsMinusSys_fx1019,v3_PionsMinusSys_fy1019,v3_PionsMinusSys_fex1019,v3_PionsMinusSys_fey1019);
   gre->SetName("v3_PionsMinusSys");
   gre->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1188;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v3_PionsMinusSys1019 = new TH1F("Graph_v3_PionsMinusSys1019","",100,-0.085,3.27);
   Graph_v3_PionsMinusSys1019->SetMinimum(-0.025);
   Graph_v3_PionsMinusSys1019->SetMaximum(0.32);
   Graph_v3_PionsMinusSys1019->SetDirectory(0);
   Graph_v3_PionsMinusSys1019->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v3_PionsMinusSys1019->SetLineColor(ci);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetNdivisions(505);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetLabelSize(0.035);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetTitleOffset(1.3);
   Graph_v3_PionsMinusSys1019->GetXaxis()->SetTitleFont(42);
   Graph_v3_PionsMinusSys1019->GetYaxis()->SetNdivisions(505);
   Graph_v3_PionsMinusSys1019->GetYaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1019->GetYaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsMinusSys1019->GetYaxis()->SetLabelSize(0.035);
   Graph_v3_PionsMinusSys1019->GetYaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1019->GetYaxis()->SetTitleFont(42);
   Graph_v3_PionsMinusSys1019->GetZaxis()->SetLabelFont(42);
   Graph_v3_PionsMinusSys1019->GetZaxis()->SetLabelSize(0.035);
   Graph_v3_PionsMinusSys1019->GetZaxis()->SetTitleSize(0.035);
   Graph_v3_PionsMinusSys1019->GetZaxis()->SetTitleOffset(1);
   Graph_v3_PionsMinusSys1019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v3_PionsMinusSys1019);
   
   gre->Draw("ae5");
   
   Double_t v3_PionsMinus_fx1020[7] = {
   0.3406721,
   0.6247821,
   0.9229881,
   1.222788,
   1.553068,
   1.997742,
   2.629163};
   Double_t v3_PionsMinus_fy1020[7] = {
   0.01445203,
   0.04021591,
   0.07182095,
   0.1014213,
   0.1282611,
   0.1563321,
   0.1681419};
   Double_t v3_PionsMinus_fex1020[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_PionsMinus_fey1020[7] = {
   0.0002261597,
   0.0002435838,
   0.0003386121,
   0.0005094343,
   0.0007262668,
   0.001256033,
   0.003601429};
   gre = new TGraphErrors(7,v3_PionsMinus_fx1020,v3_PionsMinus_fy1020,v3_PionsMinus_fex1020,v3_PionsMinus_fey1020);
   gre->SetName("v3_PionsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.2);
   gre->Draw("pe");
   
   Double_t v3_KaonsMinusSys_fx1021[4] = {
   0.3973548,
   0.6429538,
   0.9285217,
   1.22352};
   Double_t v3_KaonsMinusSys_fy1021[4] = {
   0.008621007,
   0.02672821,
   0.05334559,
   0.08006908};
   Double_t v3_KaonsMinusSys_fex1021[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_KaonsMinusSys_fey1021[4] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421};
   gre = new TGraphErrors(4,v3_KaonsMinusSys_fx1021,v3_KaonsMinusSys_fy1021,v3_KaonsMinusSys_fex1021,v3_KaonsMinusSys_fey1021);
   gre->SetName("v3_KaonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1189;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("e5");
   
   Double_t v3_KaonsMinus_fx1022[4] = {
   0.3973548,
   0.6429538,
   0.9285217,
   1.22352};
   Double_t v3_KaonsMinus_fy1022[4] = {
   0.008621007,
   0.02672821,
   0.05334559,
   0.08006908};
   Double_t v3_KaonsMinus_fex1022[4] = {
   0,
   0,
   0,
   0};
   Double_t v3_KaonsMinus_fey1022[4] = {
   0.00119645,
   0.0007122618,
   0.0007850897,
   0.00110565};
   gre = new TGraphErrors(4,v3_KaonsMinus_fx1022,v3_KaonsMinus_fy1022,v3_KaonsMinus_fex1022,v3_KaonsMinus_fey1022);
   gre->SetName("v3_KaonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   gre->Draw("pe");
   
   Double_t v3_ProtonsMinusSys_fx1023[6] = {
   0.6581107,
   0.9419849,
   1.234144,
   1.563778,
   2.006968,
   2.633273};
   Double_t v3_ProtonsMinusSys_fy1023[6] = {
   0.008737569,
   0.03805156,
   0.07577888,
   0.1179798,
   0.1645116,
   0.2312877};
   Double_t v3_ProtonsMinusSys_fex1023[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_ProtonsMinusSys_fey1023[6] = {
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   gre = new TGraphErrors(6,v3_ProtonsMinusSys_fx1023,v3_ProtonsMinusSys_fy1023,v3_ProtonsMinusSys_fex1023,v3_ProtonsMinusSys_fey1023);
   gre->SetName("v3_ProtonsMinusSys");
   gre->SetTitle("Graph");

   ci = 1190;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("e5");
   
   Double_t v3_ProtonsMinus_fx1024[6] = {
   0.6581107,
   0.9419849,
   1.234144,
   1.563778,
   2.006968,
   2.633273};
   Double_t v3_ProtonsMinus_fy1024[6] = {
   0.008737569,
   0.03805156,
   0.07577888,
   0.1179798,
   0.1645116,
   0.2312877};
   Double_t v3_ProtonsMinus_fex1024[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_ProtonsMinus_fey1024[6] = {
   0.001427345,
   0.00116051,
   0.001251255,
   0.001428347,
   0.002119513,
   0.005550263};
   gre = new TGraphErrors(6,v3_ProtonsMinus_fx1024,v3_ProtonsMinus_fy1024,v3_ProtonsMinus_fex1024,v3_ProtonsMinus_fey1024);
   gre->SetName("v3_ProtonsMinus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   gre->Draw("pe");
   
   TLegend *leg = new TLegend(0.15,0.5,0.3,0.7);
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("v3_PionsMinus","#pi^{-}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("v3_KaonsMinus","K^{-}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("v3_ProtonsMinus","#bar{p}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   TLatex *   tex = new TLatex(0,0.28,"#splitline{ #font[42]{Au+Au #sqrt{s_{NN}} = 27 GeV Run18} }{ #font[42]{centrality 0-60%} }");
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.9,0.27," #font[42]{ STAR Preliminary } ");
   tex->SetLineWidth(2);
   tex->Draw();
   TLine *line = new TLine(-0.085,0,3.27,0);
   line->SetLineStyle(2);
   line->Draw();
   pad1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pad3
   TPad *pad3 = new TPad("pad3", "This is pad3",0,0,0.08,1);
   pad3->Draw();
   pad3->cd();
   pad3->Range(0,0,1,1);
   pad3->SetFillColor(0);
   pad3->SetBorderMode(0);
   pad3->SetBorderSize(2);
   pad3->SetTickx(1);
   pad3->SetTicky(1);
   pad3->SetFrameBorderMode(0);
      tex = new TLatex(0.9,0.65,"#scale[0.7]{#font[42]{ 2.5 #times v_{3} }}");
   tex->SetTextSize(0.6);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
   pad3->Modified();
   canvas->cd();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
