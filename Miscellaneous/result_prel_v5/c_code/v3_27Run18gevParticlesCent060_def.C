void v3_27Run18gevParticlesCent060_def()
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
   
   Double_t v3_PionsPlusSys_fx1013[7] = {
   0.3411545,
   0.6249777,
   0.9230846,
   1.222863,
   1.553378,
   1.999755,
   2.634247};
   Double_t v3_PionsPlusSys_fy1013[7] = {
   0.01331131,
   0.03904083,
   0.07053617,
   0.1000185,
   0.1259021,
   0.1508224,
   0.1700106};
   Double_t v3_PionsPlusSys_fex1013[7] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_PionsPlusSys_fey1013[7] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   TGraphErrors *gre = new TGraphErrors(7,v3_PionsPlusSys_fx1013,v3_PionsPlusSys_fy1013,v3_PionsPlusSys_fex1013,v3_PionsPlusSys_fey1013);
   gre->SetName("v3_PionsPlusSys");
   gre->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1185;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   
   TH1F *Graph_v3_PionsPlusSys1013 = new TH1F("Graph_v3_PionsPlusSys1013","",100,-0.085,3.27);
   Graph_v3_PionsPlusSys1013->SetMinimum(-0.025);
   Graph_v3_PionsPlusSys1013->SetMaximum(0.32);
   Graph_v3_PionsPlusSys1013->SetDirectory(0);
   Graph_v3_PionsPlusSys1013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_v3_PionsPlusSys1013->SetLineColor(ci);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetNdivisions(505);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetLabelFont(42);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetLabelSize(0.035);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetTitleSize(0.035);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetTitleOffset(1.3);
   Graph_v3_PionsPlusSys1013->GetXaxis()->SetTitleFont(42);
   Graph_v3_PionsPlusSys1013->GetYaxis()->SetNdivisions(505);
   Graph_v3_PionsPlusSys1013->GetYaxis()->SetLabelFont(42);
   Graph_v3_PionsPlusSys1013->GetYaxis()->SetLabelOffset(0.01);
   Graph_v3_PionsPlusSys1013->GetYaxis()->SetLabelSize(0.035);
   Graph_v3_PionsPlusSys1013->GetYaxis()->SetTitleSize(0.035);
   Graph_v3_PionsPlusSys1013->GetYaxis()->SetTitleFont(42);
   Graph_v3_PionsPlusSys1013->GetZaxis()->SetLabelFont(42);
   Graph_v3_PionsPlusSys1013->GetZaxis()->SetLabelSize(0.035);
   Graph_v3_PionsPlusSys1013->GetZaxis()->SetTitleSize(0.035);
   Graph_v3_PionsPlusSys1013->GetZaxis()->SetTitleOffset(1);
   Graph_v3_PionsPlusSys1013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_v3_PionsPlusSys1013);
   
   gre->Draw("ae5");
   
   Double_t v3_PionsPlus_fx1014[7] = {
   0.3411545,
   0.6249777,
   0.9230846,
   1.222863,
   1.553378,
   1.999755,
   2.634247};
   Double_t v3_PionsPlus_fy1014[7] = {
   0.01331131,
   0.03904083,
   0.07053617,
   0.1000185,
   0.1259021,
   0.1508224,
   0.1700106};
   Double_t v3_PionsPlus_fex1014[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_PionsPlus_fey1014[7] = {
   0.0002278114,
   0.0002434647,
   0.0003372383,
   0.0005056904,
   0.0007193392,
   0.001228983,
   0.003396896};
   gre = new TGraphErrors(7,v3_PionsPlus_fx1014,v3_PionsPlus_fy1014,v3_PionsPlus_fex1014,v3_PionsPlus_fey1014);
   gre->SetName("v3_PionsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.2);
   gre->Draw("pe");
   
   Double_t v3_KaonsPlusSys_fx1015[4] = {
   0.3986119,
   0.6437496,
   0.92927,
   1.224081};
   Double_t v3_KaonsPlusSys_fy1015[4] = {
   0.008524177,
   0.02771368,
   0.05314108,
   0.07931415};
   Double_t v3_KaonsPlusSys_fex1015[4] = {
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_KaonsPlusSys_fey1015[4] = {
   0.0001736451,
   0.00036616,
   0.001201423,
   0.002248421};
   gre = new TGraphErrors(4,v3_KaonsPlusSys_fx1015,v3_KaonsPlusSys_fy1015,v3_KaonsPlusSys_fex1015,v3_KaonsPlusSys_fey1015);
   gre->SetName("v3_KaonsPlusSys");
   gre->SetTitle("Graph");

   ci = 1186;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->Draw("e5");
   
   Double_t v3_KaonsPlus_fx1016[4] = {
   0.3986119,
   0.6437496,
   0.92927,
   1.224081};
   Double_t v3_KaonsPlus_fy1016[4] = {
   0.008524177,
   0.02771368,
   0.05314108,
   0.07931415};
   Double_t v3_KaonsPlus_fex1016[4] = {
   0,
   0,
   0,
   0};
   Double_t v3_KaonsPlus_fey1016[4] = {
   0.0009974252,
   0.0005883808,
   0.0006399172,
   0.0008910947};
   gre = new TGraphErrors(4,v3_KaonsPlus_fx1016,v3_KaonsPlus_fy1016,v3_KaonsPlus_fex1016,v3_KaonsPlus_fey1016);
   gre->SetName("v3_KaonsPlus");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(28);
   gre->SetMarkerColor(28);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   gre->Draw("pe");
   
   Double_t v3_ProtonsPlusSys_fx1017[6] = {
   0.6575329,
   0.9423184,
   1.234741,
   1.565072,
   2.0097,
   2.636862};
   Double_t v3_ProtonsPlusSys_fy1017[6] = {
   0.0152527,
   0.04533733,
   0.08577327,
   0.1319009,
   0.1849764,
   0.239242};
   Double_t v3_ProtonsPlusSys_fex1017[6] = {
   0.04,
   0.04,
   0.04,
   0.04,
   0.04,
   0.04};
   Double_t v3_ProtonsPlusSys_fey1017[6] = {
   0.00036616,
   0.001201423,
   0.002248421,
   0.003424892,
   0.005175648,
   0.006687586};
   gre = new TGraphErrors(6,v3_ProtonsPlusSys_fx1017,v3_ProtonsPlusSys_fy1017,v3_ProtonsPlusSys_fex1017,v3_ProtonsPlusSys_fey1017);
   gre->SetName("v3_ProtonsPlusSys");
   gre->SetTitle("Graph");

   ci = 1187;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->Draw("e5");
   
   Double_t v3_ProtonsPlus_fx1018[6] = {
   0.6575329,
   0.9423184,
   1.234741,
   1.565072,
   2.0097,
   2.636862};
   Double_t v3_ProtonsPlus_fy1018[6] = {
   0.0152527,
   0.04533733,
   0.08577327,
   0.1319009,
   0.1849764,
   0.239242};
   Double_t v3_ProtonsPlus_fex1018[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t v3_ProtonsPlus_fey1018[6] = {
   0.0005855933,
   0.0004817701,
   0.0005193398,
   0.0005891997,
   0.000861728,
   0.002206044};
   gre = new TGraphErrors(6,v3_ProtonsPlus_fx1018,v3_ProtonsPlus_fy1018,v3_ProtonsPlus_fex1018,v3_ProtonsPlus_fey1018);
   gre->SetName("v3_ProtonsPlus");
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
   TLegendEntry *entry=leg->AddEntry("v3_PionsPlus","#pi^{+}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("v3_KaonsPlus","K^{+}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("v3_ProtonsPlus","p","p");
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
