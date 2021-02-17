void intSysBES_vn_Hadrons_Eta15_pt_energy_0_60()
{
//=========Macro generated from canvas: canvas/plot
//=========  (Sat Oct  3 16:46:22 2020) by ROOT version 6.14/04
   TCanvas *canvas = new TCanvas("canvas", "plot",0,0,1000,1280);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   canvas->Range(0,0,1,1);
   canvas->SetFillColor(10);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetTickx(1);
   canvas->SetTicky(1);
   canvas->SetLeftMargin(0.16);
   canvas->SetBottomMargin(0.15);
   canvas->SetFrameFillColor(0);
   canvas->SetFrameBorderSize(115);
  
// ------------>Primitives in pad: PadAxisDown_0_1
   TPad *PadAxisDown_0_1 = new TPad("PadAxisDown_0_1", "",0.15,0,0.525,0.176);
   PadAxisDown_0_1->Draw();
   PadAxisDown_0_1->cd();
   PadAxisDown_0_1->Range(-0.05,-8.377058,2.86,5.67);
   PadAxisDown_0_1->SetFillColor(0);
   PadAxisDown_0_1->SetBorderMode(0);
   PadAxisDown_0_1->SetBorderSize(0);
   PadAxisDown_0_1->SetTickx(1);
   PadAxisDown_0_1->SetTicky(1);
   PadAxisDown_0_1->SetLeftMargin(0);
   PadAxisDown_0_1->SetRightMargin(0);
   PadAxisDown_0_1->SetTopMargin(0);
   PadAxisDown_0_1->SetBottomMargin(0.575);
   
   TH2F *__1 = new TH2F("__1","",2,-0.05,2.86,2,-0.3,5.67);
   __1->SetStats(0);
   __1->SetFillColor(10);
   __1->SetFillStyle(0);
   __1->GetXaxis()->SetNdivisions(508);
   __1->GetXaxis()->SetLabelFont(42);
   __1->GetXaxis()->SetLabelOffset(0.02);
   __1->GetXaxis()->SetLabelSize(0.13);
   __1->GetXaxis()->SetTitleSize(0.05);
   __1->GetXaxis()->SetTitleOffset(1.2);
   __1->GetXaxis()->SetTitleFont(42);
   __1->GetYaxis()->SetNdivisions(505);
   __1->GetYaxis()->SetLabelFont(42);
   __1->GetYaxis()->SetLabelOffset(0.02);
   __1->GetYaxis()->SetLabelSize(0.13);
   __1->GetYaxis()->SetTitleSize(0.05);
   __1->GetYaxis()->SetTitleOffset(1.4);
   __1->GetYaxis()->SetTitleFont(42);
   __1->GetZaxis()->SetLabelFont(42);
   __1->GetZaxis()->SetLabelSize(0.035);
   __1->GetZaxis()->SetTitleSize(0.035);
   __1->GetZaxis()->SetTitleFont(42);
   __1->Draw("");
   PadAxisDown_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisDown_1_1
   TPad *PadAxisDown_1_1 = new TPad("PadAxisDown_1_1", "",0.525,0,0.9,0.176);
   PadAxisDown_1_1->Draw();
   PadAxisDown_1_1->cd();
   PadAxisDown_1_1->Range(-0.05,-8.377058,2.86,5.67);
   PadAxisDown_1_1->SetFillColor(0);
   PadAxisDown_1_1->SetBorderMode(0);
   PadAxisDown_1_1->SetBorderSize(0);
   PadAxisDown_1_1->SetTickx(1);
   PadAxisDown_1_1->SetTicky(1);
   PadAxisDown_1_1->SetLeftMargin(0);
   PadAxisDown_1_1->SetRightMargin(0);
   PadAxisDown_1_1->SetTopMargin(0);
   PadAxisDown_1_1->SetBottomMargin(0.575);
   
   TH2F *__2 = new TH2F("__2","",2,-0.05,2.86,2,-0.3,5.67);
   __2->SetStats(0);
   __2->SetFillColor(10);
   __2->SetFillStyle(0);
   __2->GetXaxis()->SetNdivisions(508);
   __2->GetXaxis()->SetLabelFont(42);
   __2->GetXaxis()->SetLabelOffset(0.02);
   __2->GetXaxis()->SetLabelSize(0.13);
   __2->GetXaxis()->SetTitleSize(0.05);
   __2->GetXaxis()->SetTitleOffset(1.2);
   __2->GetXaxis()->SetTitleFont(42);
   __2->GetYaxis()->SetNdivisions(505);
   __2->GetYaxis()->SetLabelFont(42);
   __2->GetYaxis()->SetLabelOffset(0.02);
   __2->GetYaxis()->SetLabelSize(0.13);
   __2->GetYaxis()->SetTitleSize(0.05);
   __2->GetYaxis()->SetTitleOffset(1.4);
   __2->GetYaxis()->SetTitleFont(42);
   __2->GetZaxis()->SetLabelFont(42);
   __2->GetZaxis()->SetLabelSize(0.035);
   __2->GetZaxis()->SetTitleSize(0.035);
   __2->GetZaxis()->SetTitleFont(42);
   __2->Draw("");
   PadAxisDown_1_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_5
   TPad *PadAxisLeft_0_5 = new TPad("PadAxisLeft_0_5", "",0,0.804,0.375,0.98);
   PadAxisLeft_0_5->Draw();
   PadAxisLeft_0_5->cd();
   PadAxisLeft_0_5->Range(-1.99,-0.3,2.86,5.67);
   PadAxisLeft_0_5->SetFillColor(0);
   PadAxisLeft_0_5->SetBorderMode(0);
   PadAxisLeft_0_5->SetBorderSize(0);
   PadAxisLeft_0_5->SetTickx(1);
   PadAxisLeft_0_5->SetTicky(1);
   PadAxisLeft_0_5->SetLeftMargin(0.4);
   PadAxisLeft_0_5->SetRightMargin(0);
   PadAxisLeft_0_5->SetTopMargin(0);
   PadAxisLeft_0_5->SetBottomMargin(0);
   
   TH2F *__3 = new TH2F("__3","",2,-0.05,2.86,2,-0.3,5.67);
   __3->SetStats(0);
   __3->SetFillColor(10);
   __3->SetFillStyle(0);
   __3->GetXaxis()->SetNdivisions(508);
   __3->GetXaxis()->SetLabelFont(42);
   __3->GetXaxis()->SetLabelOffset(0.02);
   __3->GetXaxis()->SetLabelSize(0.13);
   __3->GetXaxis()->SetTitleSize(0.05);
   __3->GetXaxis()->SetTitleOffset(1.2);
   __3->GetXaxis()->SetTitleFont(42);
   __3->GetYaxis()->SetNdivisions(505);
   __3->GetYaxis()->SetLabelFont(42);
   __3->GetYaxis()->SetLabelOffset(0.02);
   __3->GetYaxis()->SetLabelSize(0.13);
   __3->GetYaxis()->SetTitleSize(0.05);
   __3->GetYaxis()->SetTitleOffset(1.4);
   __3->GetYaxis()->SetTitleFont(42);
   __3->GetZaxis()->SetLabelFont(42);
   __3->GetZaxis()->SetLabelSize(0.035);
   __3->GetZaxis()->SetTitleSize(0.035);
   __3->GetZaxis()->SetTitleFont(42);
   __3->Draw("");
   PadAxisLeft_0_5->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_4
   TPad *PadAxisLeft_0_4 = new TPad("PadAxisLeft_0_4", "",0,0.628,0.375,0.804);
   PadAxisLeft_0_4->Draw();
   PadAxisLeft_0_4->cd();
   PadAxisLeft_0_4->Range(-1.99,-0.3,2.86,5.67);
   PadAxisLeft_0_4->SetFillColor(0);
   PadAxisLeft_0_4->SetBorderMode(0);
   PadAxisLeft_0_4->SetBorderSize(0);
   PadAxisLeft_0_4->SetTickx(1);
   PadAxisLeft_0_4->SetTicky(1);
   PadAxisLeft_0_4->SetLeftMargin(0.4);
   PadAxisLeft_0_4->SetRightMargin(0);
   PadAxisLeft_0_4->SetTopMargin(0);
   PadAxisLeft_0_4->SetBottomMargin(0);
   
   TH2F *__4 = new TH2F("__4","",2,-0.05,2.86,2,-0.3,5.67);
   __4->SetStats(0);
   __4->SetFillColor(10);
   __4->SetFillStyle(0);
   __4->GetXaxis()->SetNdivisions(508);
   __4->GetXaxis()->SetLabelFont(42);
   __4->GetXaxis()->SetLabelOffset(0.02);
   __4->GetXaxis()->SetLabelSize(0.13);
   __4->GetXaxis()->SetTitleSize(0.05);
   __4->GetXaxis()->SetTitleOffset(1.2);
   __4->GetXaxis()->SetTitleFont(42);
   __4->GetYaxis()->SetNdivisions(505);
   __4->GetYaxis()->SetLabelFont(42);
   __4->GetYaxis()->SetLabelOffset(0.02);
   __4->GetYaxis()->SetLabelSize(0.13);
   __4->GetYaxis()->SetTitleSize(0.05);
   __4->GetYaxis()->SetTitleOffset(1.4);
   __4->GetYaxis()->SetTitleFont(42);
   __4->GetZaxis()->SetLabelFont(42);
   __4->GetZaxis()->SetLabelSize(0.035);
   __4->GetZaxis()->SetTitleSize(0.035);
   __4->GetZaxis()->SetTitleFont(42);
   __4->Draw("");
   PadAxisLeft_0_4->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_3
   TPad *PadAxisLeft_0_3 = new TPad("PadAxisLeft_0_3", "",0,0.452,0.375,0.628);
   PadAxisLeft_0_3->Draw();
   PadAxisLeft_0_3->cd();
   PadAxisLeft_0_3->Range(-1.99,-0.3,2.86,5.67);
   PadAxisLeft_0_3->SetFillColor(0);
   PadAxisLeft_0_3->SetBorderMode(0);
   PadAxisLeft_0_3->SetBorderSize(0);
   PadAxisLeft_0_3->SetTickx(1);
   PadAxisLeft_0_3->SetTicky(1);
   PadAxisLeft_0_3->SetLeftMargin(0.4);
   PadAxisLeft_0_3->SetRightMargin(0);
   PadAxisLeft_0_3->SetTopMargin(0);
   PadAxisLeft_0_3->SetBottomMargin(0);
   
   TH2F *__5 = new TH2F("__5","",2,-0.05,2.86,2,-0.3,5.67);
   __5->SetStats(0);
   __5->SetFillColor(10);
   __5->SetFillStyle(0);
   __5->GetXaxis()->SetNdivisions(508);
   __5->GetXaxis()->SetLabelFont(42);
   __5->GetXaxis()->SetLabelOffset(0.02);
   __5->GetXaxis()->SetLabelSize(0.13);
   __5->GetXaxis()->SetTitleSize(0.05);
   __5->GetXaxis()->SetTitleOffset(1.2);
   __5->GetXaxis()->SetTitleFont(42);
   __5->GetYaxis()->SetNdivisions(505);
   __5->GetYaxis()->SetLabelFont(42);
   __5->GetYaxis()->SetLabelOffset(0.02);
   __5->GetYaxis()->SetLabelSize(0.13);
   __5->GetYaxis()->SetTitleSize(0.05);
   __5->GetYaxis()->SetTitleOffset(1.4);
   __5->GetYaxis()->SetTitleFont(42);
   __5->GetZaxis()->SetLabelFont(42);
   __5->GetZaxis()->SetLabelSize(0.035);
   __5->GetZaxis()->SetTitleSize(0.035);
   __5->GetZaxis()->SetTitleFont(42);
   __5->Draw("");
   PadAxisLeft_0_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_2
   TPad *PadAxisLeft_0_2 = new TPad("PadAxisLeft_0_2", "",0,0.276,0.375,0.452);
   PadAxisLeft_0_2->Draw();
   PadAxisLeft_0_2->cd();
   PadAxisLeft_0_2->Range(-1.99,-0.3,2.86,5.67);
   PadAxisLeft_0_2->SetFillColor(0);
   PadAxisLeft_0_2->SetBorderMode(0);
   PadAxisLeft_0_2->SetBorderSize(0);
   PadAxisLeft_0_2->SetTickx(1);
   PadAxisLeft_0_2->SetTicky(1);
   PadAxisLeft_0_2->SetLeftMargin(0.4);
   PadAxisLeft_0_2->SetRightMargin(0);
   PadAxisLeft_0_2->SetTopMargin(0);
   PadAxisLeft_0_2->SetBottomMargin(0);
   
   TH2F *__6 = new TH2F("__6","",2,-0.05,2.86,2,-0.3,5.67);
   __6->SetStats(0);
   __6->SetFillColor(10);
   __6->SetFillStyle(0);
   __6->GetXaxis()->SetNdivisions(508);
   __6->GetXaxis()->SetLabelFont(42);
   __6->GetXaxis()->SetLabelOffset(0.02);
   __6->GetXaxis()->SetLabelSize(0.13);
   __6->GetXaxis()->SetTitleSize(0.05);
   __6->GetXaxis()->SetTitleOffset(1.2);
   __6->GetXaxis()->SetTitleFont(42);
   __6->GetYaxis()->SetNdivisions(505);
   __6->GetYaxis()->SetLabelFont(42);
   __6->GetYaxis()->SetLabelOffset(0.02);
   __6->GetYaxis()->SetLabelSize(0.13);
   __6->GetYaxis()->SetTitleSize(0.05);
   __6->GetYaxis()->SetTitleOffset(1.4);
   __6->GetYaxis()->SetTitleFont(42);
   __6->GetZaxis()->SetLabelFont(42);
   __6->GetZaxis()->SetLabelSize(0.035);
   __6->GetZaxis()->SetTitleSize(0.035);
   __6->GetZaxis()->SetTitleFont(42);
   __6->Draw("");
   PadAxisLeft_0_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: PadAxisLeft_0_1
   TPad *PadAxisLeft_0_1 = new TPad("PadAxisLeft_0_1", "",0,0.1,0.375,0.276);
   PadAxisLeft_0_1->Draw();
   PadAxisLeft_0_1->cd();
   PadAxisLeft_0_1->Range(-1.99,-0.3,2.86,5.67);
   PadAxisLeft_0_1->SetFillColor(0);
   PadAxisLeft_0_1->SetBorderMode(0);
   PadAxisLeft_0_1->SetBorderSize(0);
   PadAxisLeft_0_1->SetTickx(1);
   PadAxisLeft_0_1->SetTicky(1);
   PadAxisLeft_0_1->SetLeftMargin(0.4);
   PadAxisLeft_0_1->SetRightMargin(0);
   PadAxisLeft_0_1->SetTopMargin(0);
   PadAxisLeft_0_1->SetBottomMargin(0);
   
   TH2F *__7 = new TH2F("__7","",2,-0.05,2.86,2,-0.3,5.67);
   __7->SetStats(0);
   __7->SetFillColor(10);
   __7->SetFillStyle(0);
   __7->GetXaxis()->SetNdivisions(508);
   __7->GetXaxis()->SetLabelFont(42);
   __7->GetXaxis()->SetLabelOffset(0.02);
   __7->GetXaxis()->SetLabelSize(0.13);
   __7->GetXaxis()->SetTitleSize(0.05);
   __7->GetXaxis()->SetTitleOffset(1.2);
   __7->GetXaxis()->SetTitleFont(42);
   __7->GetYaxis()->SetNdivisions(505);
   __7->GetYaxis()->SetLabelFont(42);
   __7->GetYaxis()->SetLabelOffset(0.02);
   __7->GetYaxis()->SetLabelSize(0.13);
   __7->GetYaxis()->SetTitleSize(0.05);
   __7->GetYaxis()->SetTitleOffset(1.4);
   __7->GetYaxis()->SetTitleFont(42);
   __7->GetZaxis()->SetLabelFont(42);
   __7->GetZaxis()->SetLabelSize(0.035);
   __7->GetZaxis()->SetTitleSize(0.035);
   __7->GetZaxis()->SetTitleFont(42);
   __7->Draw("");
   PadAxisLeft_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_5
   TPad *Pad_0_5 = new TPad("Pad_0_5", "",0.15,0.804,0.525,0.98);
   Pad_0_5->Draw();
   Pad_0_5->cd();
   Pad_0_5->Range(-0.05,-0.3,2.86,5.67);
   Pad_0_5->SetFillColor(0);
   Pad_0_5->SetBorderMode(0);
   Pad_0_5->SetBorderSize(0);
   Pad_0_5->SetTickx(1);
   Pad_0_5->SetTicky(1);
   Pad_0_5->SetLeftMargin(0);
   Pad_0_5->SetRightMargin(0);
   Pad_0_5->SetTopMargin(0);
   Pad_0_5->SetBottomMargin(0);
   
   TH2F *__8 = new TH2F("__8","",2,-0.05,2.86,2,-0.3,5.67);
   __8->SetStats(0);
   __8->SetFillColor(10);
   __8->SetFillStyle(0);
   __8->GetXaxis()->SetNdivisions(508);
   __8->GetXaxis()->SetLabelFont(42);
   __8->GetXaxis()->SetLabelOffset(0.02);
   __8->GetXaxis()->SetLabelSize(0.13);
   __8->GetXaxis()->SetTitleSize(0.05);
   __8->GetXaxis()->SetTitleOffset(1.2);
   __8->GetXaxis()->SetTitleFont(42);
   __8->GetYaxis()->SetNdivisions(505);
   __8->GetYaxis()->SetLabelFont(42);
   __8->GetYaxis()->SetLabelOffset(0.02);
   __8->GetYaxis()->SetLabelSize(0.13);
   __8->GetYaxis()->SetTitleSize(0.05);
   __8->GetYaxis()->SetTitleOffset(1.4);
   __8->GetYaxis()->SetTitleFont(42);
   __8->GetZaxis()->SetLabelFont(42);
   __8->GetZaxis()->SetLabelSize(0.035);
   __8->GetZaxis()->SetTitleSize(0.035);
   __8->GetZaxis()->SetTitleFont(42);
   __8->Draw("");
   
   TLegend *leg = new TLegend(0.12,0.5,0.98,0.82,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("data_v2_11GeV_Hadrons","#font[42]{#scale[1.3]{11.5 GeV}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(6);
   entry->SetMarkerStyle(8);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v2_14GeV_Hadrons","#font[42]{#scale[1.3]{14.5 GeV}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v2_19GeV_Hadrons","#font[42]{#scale[1.3]{19.6 GeV}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v2_27GeV_Hadrons","#font[42]{#scale[1.3]{27 GeV}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v2_39GeV_Hadrons","#font[42]{#scale[1.3]{39 GeV}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("data_v2_62GeV_Hadrons","#font[42]{#scale[1.3]{62.4 GeV}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   leg->Draw();
   TLatex *   tex = new TLatex(0.04,4.8195,"#font[42]{(a)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.35,4.8195,"#font[42]{#scale[1.0]{0-10%}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_11GeV_Hadrons_systematic_fx1001[9] = {
   0.2953654,
   0.491363,
   0.6910374,
   0.890848,
   1.090598,
   1.290269,
   1.559486,
   1.957432,
   2.40575};
   Double_t data_v2_11GeV_Hadrons_systematic_fy1001[9] = {
   0.4644544,
   0.7359588,
   0.9578514,
   1.140734,
   1.382256,
   1.529369,
   1.84376,
   1.969439,
   2.202494};
   Double_t data_v2_11GeV_Hadrons_systematic_fex1001[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_11GeV_Hadrons_systematic_fey1001[9] = {
   0.001986559,
   0.007362944,
   0.01350998,
   0.009192072,
   0.01249233,
   0.03722305,
   0.02190321,
   0.03194368,
   0.03841728};
   TGraphErrors *gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_systematic_fx1001,data_v2_11GeV_Hadrons_systematic_fy1001,data_v2_11GeV_Hadrons_systematic_fex1001,data_v2_11GeV_Hadrons_systematic_fey1001);
   gre->SetName("data_v2_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 1179;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v2_11GeV_Hadrons_systematic1001 = new TH1F("Graph_data_v2_11GeV_Hadrons_systematic1001","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04832689,2.652788);
   Graph_data_v2_11GeV_Hadrons_systematic1001->SetMinimum(0.2846235);
   Graph_data_v2_11GeV_Hadrons_systematic1001->SetMaximum(2.418755);
   Graph_data_v2_11GeV_Hadrons_systematic1001->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons_systematic1001->SetStats(0);
   Graph_data_v2_11GeV_Hadrons_systematic1001->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons_systematic1001->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons_systematic1001);
   
   gre->Draw("e5");
   
   Double_t data_v2_14GeV_Hadrons_systematic_fx1002[9] = {
   0.296173,
   0.4913518,
   0.6907205,
   0.8905678,
   1.090381,
   1.290136,
   1.559563,
   1.957691,
   2.406222};
   Double_t data_v2_14GeV_Hadrons_systematic_fy1002[9] = {
   0.4443257,
   0.7306928,
   0.9715937,
   1.165869,
   1.382368,
   1.576904,
   1.831103,
   2.119961,
   2.273525};
   Double_t data_v2_14GeV_Hadrons_systematic_fex1002[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_14GeV_Hadrons_systematic_fey1002[9] = {
   0.005216675,
   0.005149393,
   0.007055239,
   0.008094252,
   0.01408002,
   0.009613172,
   0.004893983,
   0.01341295,
   0.03459569};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_systematic_fx1002,data_v2_14GeV_Hadrons_systematic_fy1002,data_v2_14GeV_Hadrons_systematic_fex1002,data_v2_14GeV_Hadrons_systematic_fey1002);
   gre->SetName("data_v2_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1180;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_14GeV_Hadrons_systematic1002 = new TH1F("Graph_data_v2_14GeV_Hadrons_systematic1002","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04916806,2.653227);
   Graph_data_v2_14GeV_Hadrons_systematic1002->SetMinimum(0.2522079);
   Graph_data_v2_14GeV_Hadrons_systematic1002->SetMaximum(2.495022);
   Graph_data_v2_14GeV_Hadrons_systematic1002->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons_systematic1002->SetStats(0);
   Graph_data_v2_14GeV_Hadrons_systematic1002->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons_systematic1002->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons_systematic1002);
   
   gre->Draw("e5");
   
   Double_t data_v2_19GeV_Hadrons_systematic_fx1003[9] = {
   0.2958534,
   0.4913415,
   0.6906559,
   0.8905124,
   1.090409,
   1.290224,
   1.560045,
   1.958585,
   2.408226};
   Double_t data_v2_19GeV_Hadrons_systematic_fy1003[9] = {
   0.4163985,
   0.7185621,
   0.9668558,
   1.198012,
   1.390852,
   1.602417,
   1.873768,
   2.12384,
   2.289236};
   Double_t data_v2_19GeV_Hadrons_systematic_fex1003[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_19GeV_Hadrons_systematic_fey1003[9] = {
   0.004705827,
   0.004812966,
   0.003564974,
   0.002780131,
   0.006335107,
   0.005719787,
   0.004178405,
   0.02261815,
   0.01846339};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_systematic_fx1003,data_v2_19GeV_Hadrons_systematic_fy1003,data_v2_19GeV_Hadrons_systematic_fex1003,data_v2_19GeV_Hadrons_systematic_fey1003);
   gre->SetName("data_v2_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1181;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_19GeV_Hadrons_systematic1003 = new TH1F("Graph_data_v2_19GeV_Hadrons_systematic1003","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.04861612,2.655463);
   Graph_data_v2_19GeV_Hadrons_systematic1003->SetMinimum(0.222092);
   Graph_data_v2_19GeV_Hadrons_systematic1003->SetMaximum(2.4973);
   Graph_data_v2_19GeV_Hadrons_systematic1003->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons_systematic1003->SetStats(0);
   Graph_data_v2_19GeV_Hadrons_systematic1003->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons_systematic1003->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons_systematic1003);
   
   gre->Draw("e5");
   
   Double_t data_v2_27GeV_Hadrons_systematic_fx1004[12] = {
   0.2960064,
   0.4914729,
   0.6907515,
   0.8906228,
   1.090395,
   1.290292,
   1.490139,
   1.689939,
   1.889775,
   2.159377,
   2.559347,
   2.959875};
   Double_t data_v2_27GeV_Hadrons_systematic_fy1004[12] = {
   0.4080203,
   0.7033616,
   0.9623745,
   1.190607,
   1.404853,
   1.6004,
   1.78851,
   1.943247,
   2.088345,
   2.227483,
   2.361315,
   2.435705};
   Double_t data_v2_27GeV_Hadrons_systematic_fex1004[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_27GeV_Hadrons_systematic_fey1004[12] = {
   0.005311202,
   0.005424517,
   0.002281951,
   0.0002973578,
   0.002807899,
   0.004870154,
   0.007283222,
   0.01156781,
   0.01216662,
   0.01847389,
   0.02275124,
   0.03113379};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_systematic_fx1004,data_v2_27GeV_Hadrons_systematic_fy1004,data_v2_27GeV_Hadrons_systematic_fex1004,data_v2_27GeV_Hadrons_systematic_fey1004);
   gre->SetName("data_v2_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1182;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_27GeV_Hadrons_systematic1004 = new TH1F("Graph_data_v2_27GeV_Hadrons_systematic1004","#font[42]{#scale[1.3]{27 GeV}}",100,0,3.262262);
   Graph_data_v2_27GeV_Hadrons_systematic1004->SetMinimum(0.1962961);
   Graph_data_v2_27GeV_Hadrons_systematic1004->SetMaximum(2.673252);
   Graph_data_v2_27GeV_Hadrons_systematic1004->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons_systematic1004->SetStats(0);
   Graph_data_v2_27GeV_Hadrons_systematic1004->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons_systematic1004->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons_systematic1004);
   
   gre->Draw("e5");
   
   Double_t data_v2_39GeV_Hadrons_systematic_fx1005[12] = {
   0.2966062,
   0.4916322,
   0.6908314,
   0.8906613,
   1.090689,
   1.290595,
   1.490402,
   1.690226,
   1.890108,
   2.160936,
   2.561174,
   2.962038};
   Double_t data_v2_39GeV_Hadrons_systematic_fy1005[12] = {
   0.3817828,
   0.6831387,
   0.9499437,
   1.182867,
   1.401954,
   1.605693,
   1.784357,
   1.945368,
   2.069531,
   2.228842,
   2.424402,
   2.40995};
   Double_t data_v2_39GeV_Hadrons_systematic_fex1005[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_39GeV_Hadrons_systematic_fey1005[12] = {
   0.004063726,
   0.00394973,
   0.002067632,
   0.000750761,
   0.002703484,
   0.001067612,
   0.00695404,
   0.007077222,
   0.01317252,
   0.009028876,
   0.01267331,
   0.01857743};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_systematic_fx1005,data_v2_39GeV_Hadrons_systematic_fy1005,data_v2_39GeV_Hadrons_systematic_fex1005,data_v2_39GeV_Hadrons_systematic_fey1005);
   gre->SetName("data_v2_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1183;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_39GeV_Hadrons_systematic1005 = new TH1F("Graph_data_v2_39GeV_Hadrons_systematic1005","#font[42]{#scale[1.3]{39 GeV}}",100,0,3.264581);
   Graph_data_v2_39GeV_Hadrons_systematic1005->SetMinimum(0.1717835);
   Graph_data_v2_39GeV_Hadrons_systematic1005->SetMaximum(2.643011);
   Graph_data_v2_39GeV_Hadrons_systematic1005->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons_systematic1005->SetStats(0);
   Graph_data_v2_39GeV_Hadrons_systematic1005->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons_systematic1005->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons_systematic1005);
   
   gre->Draw("e5");
   
   Double_t data_v2_62GeV_Hadrons_systematic_fx1006[12] = {
   0.2969656,
   0.4918537,
   0.691081,
   0.8909404,
   1.090999,
   1.290904,
   1.490761,
   1.690626,
   1.890535,
   2.162563,
   2.563073,
   2.96399};
   Double_t data_v2_62GeV_Hadrons_systematic_fy1006[12] = {
   0.3593243,
   0.6591396,
   0.9310776,
   1.167943,
   1.382017,
   1.578745,
   1.765347,
   1.932842,
   2.069481,
   2.214858,
   2.350936,
   2.380512};
   Double_t data_v2_62GeV_Hadrons_systematic_fex1006[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_62GeV_Hadrons_systematic_fey1006[12] = {
   0.003218791,
   0.004970042,
   0.001700731,
   0.002275069,
   0.001156867,
   0.007144595,
   0.005575085,
   0.007845776,
   0.01314451,
   0.009234739,
   0.01310738,
   0.02880128};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_systematic_fx1006,data_v2_62GeV_Hadrons_systematic_fy1006,data_v2_62GeV_Hadrons_systematic_fex1006,data_v2_62GeV_Hadrons_systematic_fey1006);
   gre->SetName("data_v2_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1184;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_62GeV_Hadrons_systematic1006 = new TH1F("Graph_data_v2_62GeV_Hadrons_systematic1006","#font[42]{#scale[1.3]{62.4 GeV}}",100,0,3.266692);
   Graph_data_v2_62GeV_Hadrons_systematic1006->SetMinimum(0.1507846);
   Graph_data_v2_62GeV_Hadrons_systematic1006->SetMaximum(2.614635);
   Graph_data_v2_62GeV_Hadrons_systematic1006->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons_systematic1006->SetStats(0);
   Graph_data_v2_62GeV_Hadrons_systematic1006->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons_systematic1006->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons_systematic1006);
   
   gre->Draw("e5");
   
   Double_t data_v2_11GeV_Hadrons_systematic_fx1007[9] = {
   0.2953654,
   0.491363,
   0.6910374,
   0.890848,
   1.090598,
   1.290269,
   1.559486,
   1.957432,
   2.40575};
   Double_t data_v2_11GeV_Hadrons_systematic_fy1007[9] = {
   0.4644544,
   0.7359588,
   0.9578514,
   1.140734,
   1.382256,
   1.529369,
   1.84376,
   1.969439,
   2.202494};
   Double_t data_v2_11GeV_Hadrons_systematic_fex1007[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_11GeV_Hadrons_systematic_fey1007[9] = {
   0.001986559,
   0.007362944,
   0.01350998,
   0.009192072,
   0.01249233,
   0.03722305,
   0.02190321,
   0.03194368,
   0.03841728};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_systematic_fx1007,data_v2_11GeV_Hadrons_systematic_fy1007,data_v2_11GeV_Hadrons_systematic_fex1007,data_v2_11GeV_Hadrons_systematic_fey1007);
   gre->SetName("data_v2_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1185;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v2_11GeV_Hadrons_systematic1007 = new TH1F("Graph_data_v2_11GeV_Hadrons_systematic1007","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04832689,2.652788);
   Graph_data_v2_11GeV_Hadrons_systematic1007->SetMinimum(0.2846235);
   Graph_data_v2_11GeV_Hadrons_systematic1007->SetMaximum(2.418755);
   Graph_data_v2_11GeV_Hadrons_systematic1007->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons_systematic1007->SetStats(0);
   Graph_data_v2_11GeV_Hadrons_systematic1007->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons_systematic1007->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons_systematic1007);
   
   gre->Draw("e5");
   
   Double_t data_v2_14GeV_Hadrons_systematic_fx1008[9] = {
   0.296173,
   0.4913518,
   0.6907205,
   0.8905678,
   1.090381,
   1.290136,
   1.559563,
   1.957691,
   2.406222};
   Double_t data_v2_14GeV_Hadrons_systematic_fy1008[9] = {
   0.4443257,
   0.7306928,
   0.9715937,
   1.165869,
   1.382368,
   1.576904,
   1.831103,
   2.119961,
   2.273525};
   Double_t data_v2_14GeV_Hadrons_systematic_fex1008[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_14GeV_Hadrons_systematic_fey1008[9] = {
   0.005216675,
   0.005149393,
   0.007055239,
   0.008094252,
   0.01408002,
   0.009613172,
   0.004893983,
   0.01341295,
   0.03459569};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_systematic_fx1008,data_v2_14GeV_Hadrons_systematic_fy1008,data_v2_14GeV_Hadrons_systematic_fex1008,data_v2_14GeV_Hadrons_systematic_fey1008);
   gre->SetName("data_v2_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1186;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_14GeV_Hadrons_systematic1008 = new TH1F("Graph_data_v2_14GeV_Hadrons_systematic1008","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04916806,2.653227);
   Graph_data_v2_14GeV_Hadrons_systematic1008->SetMinimum(0.2522079);
   Graph_data_v2_14GeV_Hadrons_systematic1008->SetMaximum(2.495022);
   Graph_data_v2_14GeV_Hadrons_systematic1008->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons_systematic1008->SetStats(0);
   Graph_data_v2_14GeV_Hadrons_systematic1008->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons_systematic1008->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons_systematic1008);
   
   gre->Draw("e5");
   
   Double_t data_v2_19GeV_Hadrons_systematic_fx1009[9] = {
   0.2958534,
   0.4913415,
   0.6906559,
   0.8905124,
   1.090409,
   1.290224,
   1.560045,
   1.958585,
   2.408226};
   Double_t data_v2_19GeV_Hadrons_systematic_fy1009[9] = {
   0.4163985,
   0.7185621,
   0.9668558,
   1.198012,
   1.390852,
   1.602417,
   1.873768,
   2.12384,
   2.289236};
   Double_t data_v2_19GeV_Hadrons_systematic_fex1009[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_19GeV_Hadrons_systematic_fey1009[9] = {
   0.004705827,
   0.004812966,
   0.003564974,
   0.002780131,
   0.006335107,
   0.005719787,
   0.004178405,
   0.02261815,
   0.01846339};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_systematic_fx1009,data_v2_19GeV_Hadrons_systematic_fy1009,data_v2_19GeV_Hadrons_systematic_fex1009,data_v2_19GeV_Hadrons_systematic_fey1009);
   gre->SetName("data_v2_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1187;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_19GeV_Hadrons_systematic1009 = new TH1F("Graph_data_v2_19GeV_Hadrons_systematic1009","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.04861612,2.655463);
   Graph_data_v2_19GeV_Hadrons_systematic1009->SetMinimum(0.222092);
   Graph_data_v2_19GeV_Hadrons_systematic1009->SetMaximum(2.4973);
   Graph_data_v2_19GeV_Hadrons_systematic1009->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons_systematic1009->SetStats(0);
   Graph_data_v2_19GeV_Hadrons_systematic1009->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons_systematic1009->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons_systematic1009);
   
   gre->Draw("e5");
   
   Double_t data_v2_27GeV_Hadrons_systematic_fx1010[12] = {
   0.2960064,
   0.4914729,
   0.6907515,
   0.8906228,
   1.090395,
   1.290292,
   1.490139,
   1.689939,
   1.889775,
   2.159377,
   2.559347,
   2.959875};
   Double_t data_v2_27GeV_Hadrons_systematic_fy1010[12] = {
   0.4080203,
   0.7033616,
   0.9623745,
   1.190607,
   1.404853,
   1.6004,
   1.78851,
   1.943247,
   2.088345,
   2.227483,
   2.361315,
   2.435705};
   Double_t data_v2_27GeV_Hadrons_systematic_fex1010[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_27GeV_Hadrons_systematic_fey1010[12] = {
   0.005311202,
   0.005424517,
   0.002281951,
   0.0002973578,
   0.002807899,
   0.004870154,
   0.007283222,
   0.01156781,
   0.01216662,
   0.01847389,
   0.02275124,
   0.03113379};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_systematic_fx1010,data_v2_27GeV_Hadrons_systematic_fy1010,data_v2_27GeV_Hadrons_systematic_fex1010,data_v2_27GeV_Hadrons_systematic_fey1010);
   gre->SetName("data_v2_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1188;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_27GeV_Hadrons_systematic1010 = new TH1F("Graph_data_v2_27GeV_Hadrons_systematic1010","#font[42]{#scale[1.3]{27 GeV}}",100,0,3.262262);
   Graph_data_v2_27GeV_Hadrons_systematic1010->SetMinimum(0.1962961);
   Graph_data_v2_27GeV_Hadrons_systematic1010->SetMaximum(2.673252);
   Graph_data_v2_27GeV_Hadrons_systematic1010->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons_systematic1010->SetStats(0);
   Graph_data_v2_27GeV_Hadrons_systematic1010->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons_systematic1010->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons_systematic1010);
   
   gre->Draw("e5");
   
   Double_t data_v2_39GeV_Hadrons_systematic_fx1011[12] = {
   0.2966062,
   0.4916322,
   0.6908314,
   0.8906613,
   1.090689,
   1.290595,
   1.490402,
   1.690226,
   1.890108,
   2.160936,
   2.561174,
   2.962038};
   Double_t data_v2_39GeV_Hadrons_systematic_fy1011[12] = {
   0.3817828,
   0.6831387,
   0.9499437,
   1.182867,
   1.401954,
   1.605693,
   1.784357,
   1.945368,
   2.069531,
   2.228842,
   2.424402,
   2.40995};
   Double_t data_v2_39GeV_Hadrons_systematic_fex1011[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_39GeV_Hadrons_systematic_fey1011[12] = {
   0.004063726,
   0.00394973,
   0.002067632,
   0.000750761,
   0.002703484,
   0.001067612,
   0.00695404,
   0.007077222,
   0.01317252,
   0.009028876,
   0.01267331,
   0.01857743};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_systematic_fx1011,data_v2_39GeV_Hadrons_systematic_fy1011,data_v2_39GeV_Hadrons_systematic_fex1011,data_v2_39GeV_Hadrons_systematic_fey1011);
   gre->SetName("data_v2_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1189;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_39GeV_Hadrons_systematic1011 = new TH1F("Graph_data_v2_39GeV_Hadrons_systematic1011","#font[42]{#scale[1.3]{39 GeV}}",100,0,3.264581);
   Graph_data_v2_39GeV_Hadrons_systematic1011->SetMinimum(0.1717835);
   Graph_data_v2_39GeV_Hadrons_systematic1011->SetMaximum(2.643011);
   Graph_data_v2_39GeV_Hadrons_systematic1011->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons_systematic1011->SetStats(0);
   Graph_data_v2_39GeV_Hadrons_systematic1011->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons_systematic1011->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons_systematic1011);
   
   gre->Draw("e5");
   
   Double_t data_v2_62GeV_Hadrons_systematic_fx1012[12] = {
   0.2969656,
   0.4918537,
   0.691081,
   0.8909404,
   1.090999,
   1.290904,
   1.490761,
   1.690626,
   1.890535,
   2.162563,
   2.563073,
   2.96399};
   Double_t data_v2_62GeV_Hadrons_systematic_fy1012[12] = {
   0.3593243,
   0.6591396,
   0.9310776,
   1.167943,
   1.382017,
   1.578745,
   1.765347,
   1.932842,
   2.069481,
   2.214858,
   2.350936,
   2.380512};
   Double_t data_v2_62GeV_Hadrons_systematic_fex1012[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_62GeV_Hadrons_systematic_fey1012[12] = {
   0.003218791,
   0.004970042,
   0.001700731,
   0.002275069,
   0.001156867,
   0.007144595,
   0.005575085,
   0.007845776,
   0.01314451,
   0.009234739,
   0.01310738,
   0.02880128};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_systematic_fx1012,data_v2_62GeV_Hadrons_systematic_fy1012,data_v2_62GeV_Hadrons_systematic_fex1012,data_v2_62GeV_Hadrons_systematic_fey1012);
   gre->SetName("data_v2_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1190;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_62GeV_Hadrons_systematic1012 = new TH1F("Graph_data_v2_62GeV_Hadrons_systematic1012","#font[42]{#scale[1.3]{62.4 GeV}}",100,0,3.266692);
   Graph_data_v2_62GeV_Hadrons_systematic1012->SetMinimum(0.1507846);
   Graph_data_v2_62GeV_Hadrons_systematic1012->SetMaximum(2.614635);
   Graph_data_v2_62GeV_Hadrons_systematic1012->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons_systematic1012->SetStats(0);
   Graph_data_v2_62GeV_Hadrons_systematic1012->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons_systematic1012->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons_systematic1012);
   
   gre->Draw("e5");
   
   Double_t data_v2_11GeV_Hadrons_fx1013[9] = {
   0.2953654,
   0.491363,
   0.6910374,
   0.890848,
   1.090598,
   1.290269,
   1.559486,
   1.957432,
   2.40575};
   Double_t data_v2_11GeV_Hadrons_fy1013[9] = {
   0.4644544,
   0.7359588,
   0.9578514,
   1.140734,
   1.382256,
   1.529369,
   1.84376,
   1.969439,
   2.202494};
   Double_t data_v2_11GeV_Hadrons_fex1013[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_11GeV_Hadrons_fey1013[9] = {
   0.01623304,
   0.01617932,
   0.01818352,
   0.02111492,
   0.02530217,
   0.03056119,
   0.03119003,
   0.05013032,
   0.08603369};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_fx1013,data_v2_11GeV_Hadrons_fy1013,data_v2_11GeV_Hadrons_fex1013,data_v2_11GeV_Hadrons_fey1013);
   gre->SetName("data_v2_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_11GeV_Hadrons1013 = new TH1F("Graph_data_v2_11GeV_Hadrons1013","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08432689,2.616788);
   Graph_data_v2_11GeV_Hadrons1013->SetMinimum(0.2641907);
   Graph_data_v2_11GeV_Hadrons1013->SetMaximum(2.472558);
   Graph_data_v2_11GeV_Hadrons1013->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons1013->SetStats(0);
   Graph_data_v2_11GeV_Hadrons1013->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons1013->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons1013->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons1013->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1013->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1013->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons1013->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons1013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons1013);
   
   gre->Draw("p");
   
   Double_t data_v2_14GeV_Hadrons_fx1014[9] = {
   0.296173,
   0.4913518,
   0.6907205,
   0.8905678,
   1.090381,
   1.290136,
   1.559563,
   1.957691,
   2.406222};
   Double_t data_v2_14GeV_Hadrons_fy1014[9] = {
   0.4443257,
   0.7306928,
   0.9715937,
   1.165869,
   1.382368,
   1.576904,
   1.831103,
   2.119961,
   2.273525};
   Double_t data_v2_14GeV_Hadrons_fex1014[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_14GeV_Hadrons_fey1014[9] = {
   0.009151943,
   0.009047147,
   0.01025828,
   0.01202552,
   0.01445636,
   0.01761081,
   0.01789982,
   0.0289904,
   0.04927583};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_fx1014,data_v2_14GeV_Hadrons_fy1014,data_v2_14GeV_Hadrons_fex1014,data_v2_14GeV_Hadrons_fey1014);
   gre->SetName("data_v2_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_14GeV_Hadrons1014 = new TH1F("Graph_data_v2_14GeV_Hadrons1014","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08516806,2.617227);
   Graph_data_v2_14GeV_Hadrons1014->SetMinimum(0.2464111);
   Graph_data_v2_14GeV_Hadrons1014->SetMaximum(2.511564);
   Graph_data_v2_14GeV_Hadrons1014->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons1014->SetStats(0);
   Graph_data_v2_14GeV_Hadrons1014->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons1014->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons1014->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons1014->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1014->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1014->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons1014->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons1014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons1014);
   
   gre->Draw("p");
   
   Double_t data_v2_19GeV_Hadrons_fx1015[9] = {
   0.2958534,
   0.4913415,
   0.6906559,
   0.8905124,
   1.090409,
   1.290224,
   1.560045,
   1.958585,
   2.408226};
   Double_t data_v2_19GeV_Hadrons_fy1015[9] = {
   0.4163985,
   0.7185621,
   0.9668558,
   1.198012,
   1.390852,
   1.602417,
   1.873768,
   2.12384,
   2.289236};
   Double_t data_v2_19GeV_Hadrons_fex1015[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_19GeV_Hadrons_fey1015[9] = {
   0.006465268,
   0.006414957,
   0.007286404,
   0.008594837,
   0.01030159,
   0.01256164,
   0.01274608,
   0.02037026,
   0.0340772};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_fx1015,data_v2_19GeV_Hadrons_fy1015,data_v2_19GeV_Hadrons_fex1015,data_v2_19GeV_Hadrons_fey1015);
   gre->SetName("data_v2_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_19GeV_Hadrons1015 = new TH1F("Graph_data_v2_19GeV_Hadrons1015","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.08461612,2.619463);
   Graph_data_v2_19GeV_Hadrons1015->SetMinimum(0.2185953);
   Graph_data_v2_19GeV_Hadrons1015->SetMaximum(2.514651);
   Graph_data_v2_19GeV_Hadrons1015->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons1015->SetStats(0);
   Graph_data_v2_19GeV_Hadrons1015->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons1015->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons1015->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons1015->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1015->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1015->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons1015->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons1015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons1015);
   
   gre->Draw("p");
   
   Double_t data_v2_27GeV_Hadrons_fx1016[12] = {
   0.2960064,
   0.4914729,
   0.6907515,
   0.8906228,
   1.090395,
   1.290292,
   1.490139,
   1.689939,
   1.889775,
   2.159377,
   2.559347,
   2.959875};
   Double_t data_v2_27GeV_Hadrons_fy1016[12] = {
   0.4080203,
   0.7033616,
   0.9623745,
   1.190607,
   1.404853,
   1.6004,
   1.78851,
   1.943247,
   2.088345,
   2.227483,
   2.361315,
   2.435705};
   Double_t data_v2_27GeV_Hadrons_fex1016[12] = {
   0,
   0,
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
   Double_t data_v2_27GeV_Hadrons_fey1016[12] = {
   0.001326266,
   0.00130777,
   0.001482714,
   0.00174595,
   0.002093603,
   0.00254773,
   0.003139696,
   0.003921896,
   0.004973032,
   0.005319879,
   0.009733797,
   0.0180019};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_fx1016,data_v2_27GeV_Hadrons_fy1016,data_v2_27GeV_Hadrons_fex1016,data_v2_27GeV_Hadrons_fey1016);
   gre->SetName("data_v2_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_27GeV_Hadrons1016 = new TH1F("Graph_data_v2_27GeV_Hadrons1016","#font[42]{#scale[1.3]{27 GeV}}",100,0.02961946,3.226262);
   Graph_data_v2_27GeV_Hadrons1016->SetMinimum(0.2019927);
   Graph_data_v2_27GeV_Hadrons1016->SetMaximum(2.658408);
   Graph_data_v2_27GeV_Hadrons1016->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons1016->SetStats(0);
   Graph_data_v2_27GeV_Hadrons1016->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons1016->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons1016->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons1016->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1016->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1016->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons1016->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons1016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons1016);
   
   gre->Draw("p");
   
   Double_t data_v2_39GeV_Hadrons_fx1017[12] = {
   0.2966062,
   0.4916322,
   0.6908314,
   0.8906613,
   1.090689,
   1.290595,
   1.490402,
   1.690226,
   1.890108,
   2.160936,
   2.561174,
   2.962038};
   Double_t data_v2_39GeV_Hadrons_fy1017[12] = {
   0.3817828,
   0.6831387,
   0.9499437,
   1.182867,
   1.401954,
   1.605693,
   1.784357,
   1.945368,
   2.069531,
   2.228842,
   2.424402,
   2.40995};
   Double_t data_v2_39GeV_Hadrons_fex1017[12] = {
   0,
   0,
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
   Double_t data_v2_39GeV_Hadrons_fey1017[12] = {
   0.002365914,
   0.002310476,
   0.002615138,
   0.003075001,
   0.003676613,
   0.00443901,
   0.005424348,
   0.006721854,
   0.008431014,
   0.008895254,
   0.01581828,
   0.02824298};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_fx1017,data_v2_39GeV_Hadrons_fy1017,data_v2_39GeV_Hadrons_fex1017,data_v2_39GeV_Hadrons_fey1017);
   gre->SetName("data_v2_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_39GeV_Hadrons1017 = new TH1F("Graph_data_v2_39GeV_Hadrons1017","#font[42]{#scale[1.3]{39 GeV}}",100,0.03006301,3.228581);
   Graph_data_v2_39GeV_Hadrons1017->SetMinimum(0.1733366);
   Graph_data_v2_39GeV_Hadrons1017->SetMaximum(2.646301);
   Graph_data_v2_39GeV_Hadrons1017->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons1017->SetStats(0);
   Graph_data_v2_39GeV_Hadrons1017->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons1017->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons1017->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons1017->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1017->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1017->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons1017->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons1017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons1017);
   
   gre->Draw("p");
   
   Double_t data_v2_62GeV_Hadrons_fx1018[12] = {
   0.2969656,
   0.4918537,
   0.691081,
   0.8909404,
   1.090999,
   1.290904,
   1.490761,
   1.690626,
   1.890535,
   2.162563,
   2.563073,
   2.96399};
   Double_t data_v2_62GeV_Hadrons_fy1018[12] = {
   0.3593243,
   0.6591396,
   0.9310776,
   1.167943,
   1.382017,
   1.578745,
   1.765347,
   1.932842,
   2.069481,
   2.214858,
   2.350936,
   2.380512};
   Double_t data_v2_62GeV_Hadrons_fex1018[12] = {
   0,
   0,
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
   Double_t data_v2_62GeV_Hadrons_fey1018[12] = {
   0.002884248,
   0.002787456,
   0.00313552,
   0.003663996,
   0.004346802,
   0.005204882,
   0.006306377,
   0.007733151,
   0.009584741,
   0.009942898,
   0.01714901,
   0.02964473};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_fx1018,data_v2_62GeV_Hadrons_fy1018,data_v2_62GeV_Hadrons_fex1018,data_v2_62GeV_Hadrons_fey1018);
   gre->SetName("data_v2_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_62GeV_Hadrons1018 = new TH1F("Graph_data_v2_62GeV_Hadrons1018","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.03026319,3.230692);
   Graph_data_v2_62GeV_Hadrons1018->SetMinimum(0.1510683);
   Graph_data_v2_62GeV_Hadrons1018->SetMaximum(2.615529);
   Graph_data_v2_62GeV_Hadrons1018->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons1018->SetStats(0);
   Graph_data_v2_62GeV_Hadrons1018->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons1018->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons1018->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons1018->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1018->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1018->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons1018->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons1018->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons1018);
   
   gre->Draw("p");
   
   Double_t data_v2_11GeV_Hadrons_fx1019[9] = {
   0.2953654,
   0.491363,
   0.6910374,
   0.890848,
   1.090598,
   1.290269,
   1.559486,
   1.957432,
   2.40575};
   Double_t data_v2_11GeV_Hadrons_fy1019[9] = {
   0.4644544,
   0.7359588,
   0.9578514,
   1.140734,
   1.382256,
   1.529369,
   1.84376,
   1.969439,
   2.202494};
   Double_t data_v2_11GeV_Hadrons_fex1019[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_11GeV_Hadrons_fey1019[9] = {
   0.01623304,
   0.01617932,
   0.01818352,
   0.02111492,
   0.02530217,
   0.03056119,
   0.03119003,
   0.05013032,
   0.08603369};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_fx1019,data_v2_11GeV_Hadrons_fy1019,data_v2_11GeV_Hadrons_fex1019,data_v2_11GeV_Hadrons_fey1019);
   gre->SetName("data_v2_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_11GeV_Hadrons1019 = new TH1F("Graph_data_v2_11GeV_Hadrons1019","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08432689,2.616788);
   Graph_data_v2_11GeV_Hadrons1019->SetMinimum(0.2641907);
   Graph_data_v2_11GeV_Hadrons1019->SetMaximum(2.472558);
   Graph_data_v2_11GeV_Hadrons1019->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons1019->SetStats(0);
   Graph_data_v2_11GeV_Hadrons1019->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons1019->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons1019->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons1019->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1019->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1019->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons1019->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons1019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons1019);
   
   gre->Draw("p");
   
   Double_t data_v2_14GeV_Hadrons_fx1020[9] = {
   0.296173,
   0.4913518,
   0.6907205,
   0.8905678,
   1.090381,
   1.290136,
   1.559563,
   1.957691,
   2.406222};
   Double_t data_v2_14GeV_Hadrons_fy1020[9] = {
   0.4443257,
   0.7306928,
   0.9715937,
   1.165869,
   1.382368,
   1.576904,
   1.831103,
   2.119961,
   2.273525};
   Double_t data_v2_14GeV_Hadrons_fex1020[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_14GeV_Hadrons_fey1020[9] = {
   0.009151943,
   0.009047147,
   0.01025828,
   0.01202552,
   0.01445636,
   0.01761081,
   0.01789982,
   0.0289904,
   0.04927583};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_fx1020,data_v2_14GeV_Hadrons_fy1020,data_v2_14GeV_Hadrons_fex1020,data_v2_14GeV_Hadrons_fey1020);
   gre->SetName("data_v2_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_14GeV_Hadrons1020 = new TH1F("Graph_data_v2_14GeV_Hadrons1020","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08516806,2.617227);
   Graph_data_v2_14GeV_Hadrons1020->SetMinimum(0.2464111);
   Graph_data_v2_14GeV_Hadrons1020->SetMaximum(2.511564);
   Graph_data_v2_14GeV_Hadrons1020->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons1020->SetStats(0);
   Graph_data_v2_14GeV_Hadrons1020->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons1020->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons1020->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons1020->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1020->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1020->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons1020->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons1020->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons1020);
   
   gre->Draw("p");
   
   Double_t data_v2_19GeV_Hadrons_fx1021[9] = {
   0.2958534,
   0.4913415,
   0.6906559,
   0.8905124,
   1.090409,
   1.290224,
   1.560045,
   1.958585,
   2.408226};
   Double_t data_v2_19GeV_Hadrons_fy1021[9] = {
   0.4163985,
   0.7185621,
   0.9668558,
   1.198012,
   1.390852,
   1.602417,
   1.873768,
   2.12384,
   2.289236};
   Double_t data_v2_19GeV_Hadrons_fex1021[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_19GeV_Hadrons_fey1021[9] = {
   0.006465268,
   0.006414957,
   0.007286404,
   0.008594837,
   0.01030159,
   0.01256164,
   0.01274608,
   0.02037026,
   0.0340772};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_fx1021,data_v2_19GeV_Hadrons_fy1021,data_v2_19GeV_Hadrons_fex1021,data_v2_19GeV_Hadrons_fey1021);
   gre->SetName("data_v2_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_19GeV_Hadrons1021 = new TH1F("Graph_data_v2_19GeV_Hadrons1021","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.08461612,2.619463);
   Graph_data_v2_19GeV_Hadrons1021->SetMinimum(0.2185953);
   Graph_data_v2_19GeV_Hadrons1021->SetMaximum(2.514651);
   Graph_data_v2_19GeV_Hadrons1021->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons1021->SetStats(0);
   Graph_data_v2_19GeV_Hadrons1021->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons1021->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons1021->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons1021->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1021->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1021->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons1021->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons1021->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons1021);
   
   gre->Draw("p");
   
   Double_t data_v2_27GeV_Hadrons_fx1022[12] = {
   0.2960064,
   0.4914729,
   0.6907515,
   0.8906228,
   1.090395,
   1.290292,
   1.490139,
   1.689939,
   1.889775,
   2.159377,
   2.559347,
   2.959875};
   Double_t data_v2_27GeV_Hadrons_fy1022[12] = {
   0.4080203,
   0.7033616,
   0.9623745,
   1.190607,
   1.404853,
   1.6004,
   1.78851,
   1.943247,
   2.088345,
   2.227483,
   2.361315,
   2.435705};
   Double_t data_v2_27GeV_Hadrons_fex1022[12] = {
   0,
   0,
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
   Double_t data_v2_27GeV_Hadrons_fey1022[12] = {
   0.001326266,
   0.00130777,
   0.001482714,
   0.00174595,
   0.002093603,
   0.00254773,
   0.003139696,
   0.003921896,
   0.004973032,
   0.005319879,
   0.009733797,
   0.0180019};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_fx1022,data_v2_27GeV_Hadrons_fy1022,data_v2_27GeV_Hadrons_fex1022,data_v2_27GeV_Hadrons_fey1022);
   gre->SetName("data_v2_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_27GeV_Hadrons1022 = new TH1F("Graph_data_v2_27GeV_Hadrons1022","#font[42]{#scale[1.3]{27 GeV}}",100,0.02961946,3.226262);
   Graph_data_v2_27GeV_Hadrons1022->SetMinimum(0.2019927);
   Graph_data_v2_27GeV_Hadrons1022->SetMaximum(2.658408);
   Graph_data_v2_27GeV_Hadrons1022->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons1022->SetStats(0);
   Graph_data_v2_27GeV_Hadrons1022->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons1022->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons1022->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons1022->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1022->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1022->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons1022->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons1022->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons1022);
   
   gre->Draw("p");
   
   Double_t data_v2_39GeV_Hadrons_fx1023[12] = {
   0.2966062,
   0.4916322,
   0.6908314,
   0.8906613,
   1.090689,
   1.290595,
   1.490402,
   1.690226,
   1.890108,
   2.160936,
   2.561174,
   2.962038};
   Double_t data_v2_39GeV_Hadrons_fy1023[12] = {
   0.3817828,
   0.6831387,
   0.9499437,
   1.182867,
   1.401954,
   1.605693,
   1.784357,
   1.945368,
   2.069531,
   2.228842,
   2.424402,
   2.40995};
   Double_t data_v2_39GeV_Hadrons_fex1023[12] = {
   0,
   0,
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
   Double_t data_v2_39GeV_Hadrons_fey1023[12] = {
   0.002365914,
   0.002310476,
   0.002615138,
   0.003075001,
   0.003676613,
   0.00443901,
   0.005424348,
   0.006721854,
   0.008431014,
   0.008895254,
   0.01581828,
   0.02824298};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_fx1023,data_v2_39GeV_Hadrons_fy1023,data_v2_39GeV_Hadrons_fex1023,data_v2_39GeV_Hadrons_fey1023);
   gre->SetName("data_v2_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_39GeV_Hadrons1023 = new TH1F("Graph_data_v2_39GeV_Hadrons1023","#font[42]{#scale[1.3]{39 GeV}}",100,0.03006301,3.228581);
   Graph_data_v2_39GeV_Hadrons1023->SetMinimum(0.1733366);
   Graph_data_v2_39GeV_Hadrons1023->SetMaximum(2.646301);
   Graph_data_v2_39GeV_Hadrons1023->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons1023->SetStats(0);
   Graph_data_v2_39GeV_Hadrons1023->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons1023->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons1023->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons1023->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1023->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1023->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons1023->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons1023->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons1023);
   
   gre->Draw("p");
   
   Double_t data_v2_62GeV_Hadrons_fx1024[12] = {
   0.2969656,
   0.4918537,
   0.691081,
   0.8909404,
   1.090999,
   1.290904,
   1.490761,
   1.690626,
   1.890535,
   2.162563,
   2.563073,
   2.96399};
   Double_t data_v2_62GeV_Hadrons_fy1024[12] = {
   0.3593243,
   0.6591396,
   0.9310776,
   1.167943,
   1.382017,
   1.578745,
   1.765347,
   1.932842,
   2.069481,
   2.214858,
   2.350936,
   2.380512};
   Double_t data_v2_62GeV_Hadrons_fex1024[12] = {
   0,
   0,
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
   Double_t data_v2_62GeV_Hadrons_fey1024[12] = {
   0.002884248,
   0.002787456,
   0.00313552,
   0.003663996,
   0.004346802,
   0.005204882,
   0.006306377,
   0.007733151,
   0.009584741,
   0.009942898,
   0.01714901,
   0.02964473};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_fx1024,data_v2_62GeV_Hadrons_fy1024,data_v2_62GeV_Hadrons_fex1024,data_v2_62GeV_Hadrons_fey1024);
   gre->SetName("data_v2_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_62GeV_Hadrons1024 = new TH1F("Graph_data_v2_62GeV_Hadrons1024","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.03026319,3.230692);
   Graph_data_v2_62GeV_Hadrons1024->SetMinimum(0.1510683);
   Graph_data_v2_62GeV_Hadrons1024->SetMaximum(2.615529);
   Graph_data_v2_62GeV_Hadrons1024->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons1024->SetStats(0);
   Graph_data_v2_62GeV_Hadrons1024->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons1024->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons1024->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons1024->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1024->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1024->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons1024->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons1024->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons1024);
   
   gre->Draw("p");
   TLine *line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(0.06,3.969,"#font[42]{(v_{2})}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1,4.8195,"#font[42]{ #scale[1.0]{ Au+Au, Hadrons}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_0_5->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_5
   TPad *Pad_1_5 = new TPad("Pad_1_5", "",0.525,0.804,0.9,0.98);
   Pad_1_5->Draw();
   Pad_1_5->cd();
   Pad_1_5->Range(-0.05,-0.3,2.86,5.67);
   Pad_1_5->SetFillColor(0);
   Pad_1_5->SetBorderMode(0);
   Pad_1_5->SetBorderSize(0);
   Pad_1_5->SetTickx(1);
   Pad_1_5->SetTicky(1);
   Pad_1_5->SetLeftMargin(0);
   Pad_1_5->SetRightMargin(0);
   Pad_1_5->SetTopMargin(0);
   Pad_1_5->SetBottomMargin(0);
   
   TH2F *__9 = new TH2F("__9","",2,-0.05,2.86,2,-0.3,5.67);
   __9->SetStats(0);
   __9->SetFillColor(10);
   __9->SetFillStyle(0);
   __9->GetXaxis()->SetNdivisions(508);
   __9->GetXaxis()->SetLabelFont(42);
   __9->GetXaxis()->SetLabelOffset(0.02);
   __9->GetXaxis()->SetLabelSize(0.13);
   __9->GetXaxis()->SetTitleSize(0.05);
   __9->GetXaxis()->SetTitleOffset(1.2);
   __9->GetXaxis()->SetTitleFont(42);
   __9->GetYaxis()->SetNdivisions(505);
   __9->GetYaxis()->SetLabelFont(42);
   __9->GetYaxis()->SetLabelOffset(0.02);
   __9->GetYaxis()->SetLabelSize(0.13);
   __9->GetYaxis()->SetTitleSize(0.05);
   __9->GetYaxis()->SetTitleOffset(1.4);
   __9->GetYaxis()->SetTitleFont(42);
   __9->GetZaxis()->SetLabelFont(42);
   __9->GetZaxis()->SetLabelSize(0.035);
   __9->GetZaxis()->SetTitleSize(0.035);
   __9->GetZaxis()->SetTitleFont(42);
   __9->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(b)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v3_11GeV_Hadrons_systematic_fx1025[7] = {
   0.2953654,
   0.491363,
   0.6910374,
   0.9635089,
   1.361052,
   1.808584,
   2.40575};
   Double_t data_v3_11GeV_Hadrons_systematic_fy1025[7] = {
   0.2341197,
   0.5207041,
   0.8694349,
   1.286664,
   2.128148,
   2.758275,
   3.240604};
   Double_t data_v3_11GeV_Hadrons_systematic_fex1025[7] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_11GeV_Hadrons_systematic_fey1025[7] = {
   0.006640717,
   0.02619398,
   0.01858218,
   0.005194064,
   0.05359885,
   0.05910746,
   0.1964713};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_systematic_fx1025,data_v3_11GeV_Hadrons_systematic_fy1025,data_v3_11GeV_Hadrons_systematic_fex1025,data_v3_11GeV_Hadrons_systematic_fey1025);
   gre->SetName("data_v3_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1191;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v3_11GeV_Hadrons_systematic1025 = new TH1F("Graph_data_v3_11GeV_Hadrons_systematic1025","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04832689,2.652788);
   Graph_data_v3_11GeV_Hadrons_systematic1025->SetMinimum(0.204731);
   Graph_data_v3_11GeV_Hadrons_systematic1025->SetMaximum(3.758035);
   Graph_data_v3_11GeV_Hadrons_systematic1025->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons_systematic1025->SetStats(0);
   Graph_data_v3_11GeV_Hadrons_systematic1025->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons_systematic1025->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1025->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons_systematic1025);
   
   gre->Draw("e5");
   
   Double_t data_v3_14GeV_Hadrons_systematic_fx1026[8] = {
   0.296173,
   0.4913518,
   0.6907205,
   0.8905678,
   1.161886,
   1.559563,
   1.957691,
   2.406222};
   Double_t data_v3_14GeV_Hadrons_systematic_fy1026[8] = {
   0.2267297,
   0.4759109,
   0.8304863,
   1.203554,
   1.737877,
   2.488586,
   3.213341,
   4.223694};
   Double_t data_v3_14GeV_Hadrons_systematic_fex1026[8] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_14GeV_Hadrons_systematic_fey1026[8] = {
   0.02075119,
   0.01213585,
   0.007411708,
   0.01593764,
   0.008281655,
   0.05090812,
   0.09238446,
   0.21368};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_systematic_fx1026,data_v3_14GeV_Hadrons_systematic_fy1026,data_v3_14GeV_Hadrons_systematic_fex1026,data_v3_14GeV_Hadrons_systematic_fey1026);
   gre->SetName("data_v3_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1192;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_14GeV_Hadrons_systematic1026 = new TH1F("Graph_data_v3_14GeV_Hadrons_systematic1026","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04916806,2.653227);
   Graph_data_v3_14GeV_Hadrons_systematic1026->SetMinimum(0.1853807);
   Graph_data_v3_14GeV_Hadrons_systematic1026->SetMaximum(4.860513);
   Graph_data_v3_14GeV_Hadrons_systematic1026->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons_systematic1026->SetStats(0);
   Graph_data_v3_14GeV_Hadrons_systematic1026->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons_systematic1026->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1026->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons_systematic1026);
   
   gre->Draw("e5");
   
   Double_t data_v3_19GeV_Hadrons_systematic_fx1027[9] = {
   0.2958534,
   0.4913415,
   0.6906559,
   0.8905124,
   1.090409,
   1.361071,
   1.759105,
   2.15805,
   2.608384};
   Double_t data_v3_19GeV_Hadrons_systematic_fy1027[9] = {
   0.2078178,
   0.4922654,
   0.8471551,
   1.207872,
   1.548682,
   2.115781,
   2.926855,
   3.458335,
   4.118056};
   Double_t data_v3_19GeV_Hadrons_systematic_fex1027[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_19GeV_Hadrons_systematic_fey1027[9] = {
   0.006103784,
   0.03161906,
   0.005495194,
   0.005692565,
   0.02549572,
   0.03178263,
   0.04235234,
   0.02056836,
   0.05237595};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_systematic_fx1027,data_v3_19GeV_Hadrons_systematic_fy1027,data_v3_19GeV_Hadrons_systematic_fex1027,data_v3_19GeV_Hadrons_systematic_fey1027);
   gre->SetName("data_v3_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1193;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_19GeV_Hadrons_systematic1027 = new TH1F("Graph_data_v3_19GeV_Hadrons_systematic1027","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.02860037,2.875637);
   Graph_data_v3_19GeV_Hadrons_systematic1027->SetMinimum(0.1815426);
   Graph_data_v3_19GeV_Hadrons_systematic1027->SetMaximum(4.567304);
   Graph_data_v3_19GeV_Hadrons_systematic1027->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons_systematic1027->SetStats(0);
   Graph_data_v3_19GeV_Hadrons_systematic1027->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons_systematic1027->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1027->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons_systematic1027);
   
   gre->Draw("e5");
   
   Double_t data_v3_27GeV_Hadrons_systematic_fx1028[11] = {
   0.2960064,
   0.4914729,
   0.6907515,
   0.8906228,
   1.090395,
   1.290292,
   1.490139,
   1.689939,
   1.889775,
   2.159377,
   2.559347};
   Double_t data_v3_27GeV_Hadrons_systematic_fy1028[11] = {
   0.2045807,
   0.4981128,
   0.8332909,
   1.180211,
   1.550918,
   1.92819,
   2.311186,
   2.693244,
   3.082886,
   3.507922,
   4.004158};
   Double_t data_v3_27GeV_Hadrons_systematic_fex1028[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_27GeV_Hadrons_systematic_fey1028[11] = {
   0.0070584,
   0.009661094,
   0.00466695,
   0.004769423,
   0.00329028,
   0.009745736,
   0.0189845,
   0.02798126,
   0.03109146,
   0.04103624,
   0.06740081};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_systematic_fx1028,data_v3_27GeV_Hadrons_systematic_fy1028,data_v3_27GeV_Hadrons_systematic_fex1028,data_v3_27GeV_Hadrons_systematic_fey1028);
   gre->SetName("data_v3_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1194;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_27GeV_Hadrons_systematic1028 = new TH1F("Graph_data_v3_27GeV_Hadrons_systematic1028","#font[42]{#scale[1.3]{27 GeV}}",100,0.03367235,2.821681);
   Graph_data_v3_27GeV_Hadrons_systematic1028->SetMinimum(0.1777701);
   Graph_data_v3_27GeV_Hadrons_systematic1028->SetMaximum(4.458962);
   Graph_data_v3_27GeV_Hadrons_systematic1028->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons_systematic1028->SetStats(0);
   Graph_data_v3_27GeV_Hadrons_systematic1028->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons_systematic1028->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1028->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons_systematic1028);
   
   gre->Draw("e5");
   
   Double_t data_v3_39GeV_Hadrons_systematic_fx1029[11] = {
   0.2966062,
   0.4916322,
   0.6908314,
   0.8906613,
   1.090689,
   1.290595,
   1.490402,
   1.690226,
   1.890108,
   2.160936,
   2.561174};
   Double_t data_v3_39GeV_Hadrons_systematic_fy1029[11] = {
   0.1975748,
   0.4926621,
   0.8217787,
   1.154189,
   1.52011,
   1.886542,
   2.282616,
   2.646944,
   2.92193,
   3.335379,
   3.743465};
   Double_t data_v3_39GeV_Hadrons_systematic_fex1029[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_39GeV_Hadrons_systematic_fey1029[11] = {
   0.007246211,
   0.003224283,
   0.00420823,
   0.005403225,
   0.006246467,
   0.002417371,
   0.01726081,
   0.02105674,
   0.02443895,
   0.04312265,
   0.05696637};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_systematic_fx1029,data_v3_39GeV_Hadrons_systematic_fy1029,data_v3_39GeV_Hadrons_systematic_fex1029,data_v3_39GeV_Hadrons_systematic_fey1029);
   gre->SetName("data_v3_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1195;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_39GeV_Hadrons_systematic1029 = new TH1F("Graph_data_v3_39GeV_Hadrons_systematic1029","#font[42]{#scale[1.3]{39 GeV}}",100,0.03414945,2.82363);
   Graph_data_v3_39GeV_Hadrons_systematic1029->SetMinimum(0.1712957);
   Graph_data_v3_39GeV_Hadrons_systematic1029->SetMaximum(4.161442);
   Graph_data_v3_39GeV_Hadrons_systematic1029->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons_systematic1029->SetStats(0);
   Graph_data_v3_39GeV_Hadrons_systematic1029->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons_systematic1029->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1029->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons_systematic1029);
   
   gre->Draw("e5");
   
   Double_t data_v3_62GeV_Hadrons_systematic_fx1030[11] = {
   0.2969656,
   0.4918537,
   0.691081,
   0.8909404,
   1.090999,
   1.290904,
   1.490761,
   1.690626,
   1.890535,
   2.162563,
   2.563073};
   Double_t data_v3_62GeV_Hadrons_systematic_fy1030[11] = {
   0.1993072,
   0.4698319,
   0.8072395,
   1.129673,
   1.453593,
   1.833633,
   2.190205,
   2.516152,
   2.8209,
   3.245767,
   3.522547};
   Double_t data_v3_62GeV_Hadrons_systematic_fex1030[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_62GeV_Hadrons_systematic_fey1030[11] = {
   0.003508353,
   0.005307997,
   0.007789991,
   0.005224501,
   0.002281914,
   0.01611461,
   0.01659346,
   0.004536892,
   0.02818916,
   0.03041378,
   0.026529};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_systematic_fx1030,data_v3_62GeV_Hadrons_systematic_fy1030,data_v3_62GeV_Hadrons_systematic_fex1030,data_v3_62GeV_Hadrons_systematic_fey1030);
   gre->SetName("data_v3_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1196;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_62GeV_Hadrons_systematic1030 = new TH1F("Graph_data_v3_62GeV_Hadrons_systematic1030","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.03435488,2.825684);
   Graph_data_v3_62GeV_Hadrons_systematic1030->SetMinimum(0.1762189);
   Graph_data_v3_62GeV_Hadrons_systematic1030->SetMaximum(3.884404);
   Graph_data_v3_62GeV_Hadrons_systematic1030->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons_systematic1030->SetStats(0);
   Graph_data_v3_62GeV_Hadrons_systematic1030->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons_systematic1030->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1030->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons_systematic1030);
   
   gre->Draw("e5");
   
   Double_t data_v3_11GeV_Hadrons_fx1031[7] = {
   0.2953654,
   0.491363,
   0.6910374,
   0.9635089,
   1.361052,
   1.808584,
   2.40575};
   Double_t data_v3_11GeV_Hadrons_fy1031[7] = {
   0.2341197,
   0.5207041,
   0.8694349,
   1.286664,
   2.128148,
   2.758275,
   3.240604};
   Double_t data_v3_11GeV_Hadrons_fex1031[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_11GeV_Hadrons_fey1031[7] = {
   0.04636367,
   0.04566746,
   0.05207155,
   0.05091407,
   0.07838092,
   0.1120827,
   0.2538355};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_fx1031,data_v3_11GeV_Hadrons_fy1031,data_v3_11GeV_Hadrons_fex1031,data_v3_11GeV_Hadrons_fey1031);
   gre->SetName("data_v3_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_11GeV_Hadrons1031 = new TH1F("Graph_data_v3_11GeV_Hadrons1031","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08432689,2.616788);
   Graph_data_v3_11GeV_Hadrons1031->SetMinimum(0.1689804);
   Graph_data_v3_11GeV_Hadrons1031->SetMaximum(3.825108);
   Graph_data_v3_11GeV_Hadrons1031->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons1031->SetStats(0);
   Graph_data_v3_11GeV_Hadrons1031->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons1031->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons1031->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons1031->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1031->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1031->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons1031->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons1031->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons1031);
   
   gre->Draw("p");
   
   Double_t data_v3_14GeV_Hadrons_fx1032[8] = {
   0.296173,
   0.4913518,
   0.6907205,
   0.8905678,
   1.161886,
   1.559563,
   1.957691,
   2.406222};
   Double_t data_v3_14GeV_Hadrons_fy1032[8] = {
   0.2267297,
   0.4759109,
   0.8304863,
   1.203554,
   1.737877,
   2.488586,
   3.213341,
   4.223694};
   Double_t data_v3_14GeV_Hadrons_fex1032[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_14GeV_Hadrons_fey1032[8] = {
   0.02886155,
   0.02803165,
   0.032155,
   0.03865825,
   0.04005555,
   0.06127335,
   0.09783391,
   0.164113};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_fx1032,data_v3_14GeV_Hadrons_fy1032,data_v3_14GeV_Hadrons_fex1032,data_v3_14GeV_Hadrons_fey1032);
   gre->SetName("data_v3_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_14GeV_Hadrons1032 = new TH1F("Graph_data_v3_14GeV_Hadrons1032","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08516806,2.617227);
   Graph_data_v3_14GeV_Hadrons1032->SetMinimum(0.1780814);
   Graph_data_v3_14GeV_Hadrons1032->SetMaximum(4.806801);
   Graph_data_v3_14GeV_Hadrons1032->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons1032->SetStats(0);
   Graph_data_v3_14GeV_Hadrons1032->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons1032->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons1032->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons1032->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1032->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1032->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons1032->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons1032->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons1032);
   
   gre->Draw("p");
   
   Double_t data_v3_19GeV_Hadrons_fx1033[9] = {
   0.2958534,
   0.4913415,
   0.6906559,
   0.8905124,
   1.090409,
   1.361071,
   1.759105,
   2.15805,
   2.608384};
   Double_t data_v3_19GeV_Hadrons_fy1033[9] = {
   0.2078178,
   0.4922654,
   0.8471551,
   1.207872,
   1.548682,
   2.115781,
   2.926855,
   3.458335,
   4.118056};
   Double_t data_v3_19GeV_Hadrons_fex1033[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_19GeV_Hadrons_fey1033[9] = {
   0.02065367,
   0.0201756,
   0.02317267,
   0.02784488,
   0.03392625,
   0.03554706,
   0.05518173,
   0.09088322,
   0.1544517};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_fx1033,data_v3_19GeV_Hadrons_fy1033,data_v3_19GeV_Hadrons_fex1033,data_v3_19GeV_Hadrons_fey1033);
   gre->SetName("data_v3_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_19GeV_Hadrons1033 = new TH1F("Graph_data_v3_19GeV_Hadrons1033","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.06460037,2.839637);
   Graph_data_v3_19GeV_Hadrons1033->SetMinimum(0.1684477);
   Graph_data_v3_19GeV_Hadrons1033->SetMaximum(4.681042);
   Graph_data_v3_19GeV_Hadrons1033->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons1033->SetStats(0);
   Graph_data_v3_19GeV_Hadrons1033->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons1033->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons1033->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons1033->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1033->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1033->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons1033->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons1033->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons1033);
   
   gre->Draw("p");
   
   Double_t data_v3_27GeV_Hadrons_fx1034[11] = {
   0.2960064,
   0.4914729,
   0.6907515,
   0.8906228,
   1.090395,
   1.290292,
   1.490139,
   1.689939,
   1.889775,
   2.159377,
   2.559347};
   Double_t data_v3_27GeV_Hadrons_fy1034[11] = {
   0.2045807,
   0.4981128,
   0.8332909,
   1.180211,
   1.550918,
   1.92819,
   2.311186,
   2.693244,
   3.082886,
   3.507922,
   4.004158};
   Double_t data_v3_27GeV_Hadrons_fex1034[11] = {
   0,
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
   Double_t data_v3_27GeV_Hadrons_fey1034[11] = {
   0.004263107,
   0.004148265,
   0.004736071,
   0.005672956,
   0.006926651,
   0.008539807,
   0.01059065,
   0.01324785,
   0.01675197,
   0.01807345,
   0.0322947};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_fx1034,data_v3_27GeV_Hadrons_fy1034,data_v3_27GeV_Hadrons_fex1034,data_v3_27GeV_Hadrons_fey1034);
   gre->SetName("data_v3_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_27GeV_Hadrons1034 = new TH1F("Graph_data_v3_27GeV_Hadrons1034","#font[42]{#scale[1.3]{27 GeV}}",100,0.06967235,2.785681);
   Graph_data_v3_27GeV_Hadrons1034->SetMinimum(0.1802859);
   Graph_data_v3_27GeV_Hadrons1034->SetMaximum(4.420066);
   Graph_data_v3_27GeV_Hadrons1034->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons1034->SetStats(0);
   Graph_data_v3_27GeV_Hadrons1034->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons1034->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons1034->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons1034->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1034->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1034->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons1034->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons1034->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons1034);
   
   gre->Draw("p");
   
   Double_t data_v3_39GeV_Hadrons_fx1035[11] = {
   0.2966062,
   0.4916322,
   0.6908314,
   0.8906613,
   1.090689,
   1.290595,
   1.490402,
   1.690226,
   1.890108,
   2.160936,
   2.561174};
   Double_t data_v3_39GeV_Hadrons_fy1035[11] = {
   0.1975748,
   0.4926621,
   0.8217787,
   1.154189,
   1.52011,
   1.886542,
   2.282616,
   2.646944,
   2.92193,
   3.335379,
   3.743465};
   Double_t data_v3_39GeV_Hadrons_fex1035[11] = {
   0,
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
   Double_t data_v3_39GeV_Hadrons_fey1035[11] = {
   0.00714707,
   0.006889513,
   0.007835659,
   0.009345855,
   0.01136918,
   0.01389837,
   0.01714902,
   0.0212776,
   0.02653977,
   0.02826129,
   0.04914037};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_fx1035,data_v3_39GeV_Hadrons_fy1035,data_v3_39GeV_Hadrons_fex1035,data_v3_39GeV_Hadrons_fey1035);
   gre->SetName("data_v3_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_39GeV_Hadrons1035 = new TH1F("Graph_data_v3_39GeV_Hadrons1035","#font[42]{#scale[1.3]{39 GeV}}",100,0.07014945,2.78763);
   Graph_data_v3_39GeV_Hadrons1035->SetMinimum(0.171385);
   Graph_data_v3_39GeV_Hadrons1035->SetMaximum(4.152823);
   Graph_data_v3_39GeV_Hadrons1035->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons1035->SetStats(0);
   Graph_data_v3_39GeV_Hadrons1035->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons1035->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons1035->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons1035->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1035->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1035->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons1035->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons1035->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons1035);
   
   gre->Draw("p");
   
   Double_t data_v3_62GeV_Hadrons_fx1036[11] = {
   0.2969656,
   0.4918537,
   0.691081,
   0.8909404,
   1.090999,
   1.290904,
   1.490761,
   1.690626,
   1.890535,
   2.162563,
   2.563073};
   Double_t data_v3_62GeV_Hadrons_fy1036[11] = {
   0.1993072,
   0.4698319,
   0.8072395,
   1.129673,
   1.453593,
   1.833633,
   2.190205,
   2.516152,
   2.8209,
   3.245767,
   3.522547};
   Double_t data_v3_62GeV_Hadrons_fex1036[11] = {
   0,
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
   Double_t data_v3_62GeV_Hadrons_fey1036[11] = {
   0.008313634,
   0.007926171,
   0.008955456,
   0.01059092,
   0.01273207,
   0.01548909,
   0.0189072,
   0.02320671,
   0.02869209,
   0.03012842,
   0.05077875};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_fx1036,data_v3_62GeV_Hadrons_fy1036,data_v3_62GeV_Hadrons_fex1036,data_v3_62GeV_Hadrons_fey1036);
   gre->SetName("data_v3_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_62GeV_Hadrons1036 = new TH1F("Graph_data_v3_62GeV_Hadrons1036","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.07035488,2.789684);
   Graph_data_v3_62GeV_Hadrons1036->SetMinimum(0.1718942);
   Graph_data_v3_62GeV_Hadrons1036->SetMaximum(3.911559);
   Graph_data_v3_62GeV_Hadrons1036->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons1036->SetStats(0);
   Graph_data_v3_62GeV_Hadrons1036->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons1036->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons1036->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons1036->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1036->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1036->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons1036->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons1036->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons1036);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(0.06,3.969,"#font[42]{(v_{3})}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_1_5->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_4
   TPad *Pad_0_4 = new TPad("Pad_0_4", "",0.15,0.628,0.525,0.804);
   Pad_0_4->Draw();
   Pad_0_4->cd();
   Pad_0_4->Range(-0.05,-0.3,2.86,5.67);
   Pad_0_4->SetFillColor(0);
   Pad_0_4->SetBorderMode(0);
   Pad_0_4->SetBorderSize(0);
   Pad_0_4->SetTickx(1);
   Pad_0_4->SetTicky(1);
   Pad_0_4->SetLeftMargin(0);
   Pad_0_4->SetRightMargin(0);
   Pad_0_4->SetTopMargin(0);
   Pad_0_4->SetBottomMargin(0);
   
   TH2F *__10 = new TH2F("__10","",2,-0.05,2.86,2,-0.3,5.67);
   __10->SetStats(0);
   __10->SetFillColor(10);
   __10->SetFillStyle(0);
   __10->GetXaxis()->SetNdivisions(508);
   __10->GetXaxis()->SetLabelFont(42);
   __10->GetXaxis()->SetLabelOffset(0.02);
   __10->GetXaxis()->SetLabelSize(0.13);
   __10->GetXaxis()->SetTitleSize(0.05);
   __10->GetXaxis()->SetTitleOffset(1.2);
   __10->GetXaxis()->SetTitleFont(42);
   __10->GetYaxis()->SetNdivisions(505);
   __10->GetYaxis()->SetLabelFont(42);
   __10->GetYaxis()->SetLabelOffset(0.02);
   __10->GetYaxis()->SetLabelSize(0.13);
   __10->GetYaxis()->SetTitleSize(0.05);
   __10->GetYaxis()->SetTitleOffset(1.4);
   __10->GetYaxis()->SetTitleFont(42);
   __10->GetZaxis()->SetLabelFont(42);
   __10->GetZaxis()->SetLabelSize(0.035);
   __10->GetZaxis()->SetTitleSize(0.035);
   __10->GetZaxis()->SetTitleFont(42);
   __10->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(c)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.35,4.8195,"#font[42]{#scale[1.0]{10-20%}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_11GeV_Hadrons_systematic_fx1037[9] = {
   0.2951268,
   0.4912637,
   0.6908656,
   0.8906337,
   1.090424,
   1.290129,
   1.559091,
   1.957407,
   2.405256};
   Double_t data_v2_11GeV_Hadrons_systematic_fy1037[9] = {
   0.4238967,
   0.6980794,
   0.9327471,
   1.181421,
   1.3977,
   1.643015,
   1.935351,
   2.31926,
   2.611878};
   Double_t data_v2_11GeV_Hadrons_systematic_fex1037[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_11GeV_Hadrons_systematic_fey1037[9] = {
   0.001781309,
   0.002318069,
   0.002188822,
   0.002742002,
   0.004694727,
   0.006729221,
   0.004217144,
   0.01380738,
   0.01604018};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_systematic_fx1037,data_v2_11GeV_Hadrons_systematic_fy1037,data_v2_11GeV_Hadrons_systematic_fex1037,data_v2_11GeV_Hadrons_systematic_fey1037);
   gre->SetName("data_v2_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1197;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v2_11GeV_Hadrons_systematic1037 = new TH1F("Graph_data_v2_11GeV_Hadrons_systematic1037","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04811392,2.652269);
   Graph_data_v2_11GeV_Hadrons_systematic1037->SetMinimum(0.2015351);
   Graph_data_v2_11GeV_Hadrons_systematic1037->SetMaximum(2.848499);
   Graph_data_v2_11GeV_Hadrons_systematic1037->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons_systematic1037->SetStats(0);
   Graph_data_v2_11GeV_Hadrons_systematic1037->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons_systematic1037->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1037->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons_systematic1037);
   
   gre->Draw("e5");
   
   Double_t data_v2_14GeV_Hadrons_systematic_fx1038[9] = {
   0.2959729,
   0.4912729,
   0.69058,
   0.8904142,
   1.0902,
   1.290027,
   1.559285,
   1.957663,
   2.406058};
   Double_t data_v2_14GeV_Hadrons_systematic_fy1038[9] = {
   0.4295658,
   0.7034804,
   0.9478161,
   1.18601,
   1.410682,
   1.64678,
   1.935829,
   2.27048,
   2.530503};
   Double_t data_v2_14GeV_Hadrons_systematic_fex1038[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_14GeV_Hadrons_systematic_fey1038[9] = {
   0.002277076,
   0.001361671,
   0.001375726,
   0.00157236,
   0.002411727,
   0.001140012,
   0.002462137,
   0.009695537,
   0.02811793};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_systematic_fx1038,data_v2_14GeV_Hadrons_systematic_fy1038,data_v2_14GeV_Hadrons_systematic_fex1038,data_v2_14GeV_Hadrons_systematic_fey1038);
   gre->SetName("data_v2_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1198;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_14GeV_Hadrons_systematic1038 = new TH1F("Graph_data_v2_14GeV_Hadrons_systematic1038","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04896437,2.653067);
   Graph_data_v2_14GeV_Hadrons_systematic1038->SetMinimum(0.2141554);
   Graph_data_v2_14GeV_Hadrons_systematic1038->SetMaximum(2.771755);
   Graph_data_v2_14GeV_Hadrons_systematic1038->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons_systematic1038->SetStats(0);
   Graph_data_v2_14GeV_Hadrons_systematic1038->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons_systematic1038->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1038->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons_systematic1038);
   
   gre->Draw("e5");
   
   Double_t data_v2_19GeV_Hadrons_systematic_fx1039[9] = {
   0.2956249,
   0.4912639,
   0.6905406,
   0.8903813,
   1.090259,
   1.290101,
   1.559869,
   1.958654,
   2.408708};
   Double_t data_v2_19GeV_Hadrons_systematic_fy1039[9] = {
   0.3964864,
   0.6925562,
   0.9608167,
   1.198213,
   1.43551,
   1.663961,
   1.939885,
   2.286336,
   2.531981};
   Double_t data_v2_19GeV_Hadrons_systematic_fex1039[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_19GeV_Hadrons_systematic_fey1039[9] = {
   0.002246495,
   0.001978681,
   0.002042395,
   0.001491914,
   0.000678267,
   0.001124661,
   0.005892377,
   0.004269716,
   0.008932181};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_systematic_fx1039,data_v2_19GeV_Hadrons_systematic_fy1039,data_v2_19GeV_Hadrons_systematic_fex1039,data_v2_19GeV_Hadrons_systematic_fey1039);
   gre->SetName("data_v2_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1199;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_19GeV_Hadrons_systematic1039 = new TH1F("Graph_data_v2_19GeV_Hadrons_systematic1039","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.04831652,2.656017);
   Graph_data_v2_19GeV_Hadrons_systematic1039->SetMinimum(0.1795726);
   Graph_data_v2_19GeV_Hadrons_systematic1039->SetMaximum(2.75558);
   Graph_data_v2_19GeV_Hadrons_systematic1039->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons_systematic1039->SetStats(0);
   Graph_data_v2_19GeV_Hadrons_systematic1039->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons_systematic1039->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1039->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons_systematic1039);
   
   gre->Draw("e5");
   
   Double_t data_v2_27GeV_Hadrons_systematic_fx1040[12] = {
   0.2958414,
   0.4914081,
   0.6906679,
   0.8905042,
   1.090294,
   1.290199,
   1.490113,
   1.689953,
   1.889815,
   2.159691,
   2.559786,
   2.960229};
   Double_t data_v2_27GeV_Hadrons_systematic_fy1040[12] = {
   0.3928046,
   0.6863216,
   0.951092,
   1.192575,
   1.423088,
   1.644113,
   1.852861,
   2.033455,
   2.193414,
   2.370325,
   2.574323,
   2.69814};
   Double_t data_v2_27GeV_Hadrons_systematic_fex1040[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_27GeV_Hadrons_systematic_fey1040[12] = {
   0.002481712,
   0.001657525,
   0.0006283179,
   0.0002092529,
   0.0006084176,
   0.0006700774,
   0.001143318,
   0.002962332,
   0.001563961,
   0.005018126,
   0.003557364,
   0.004965087};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_systematic_fx1040,data_v2_27GeV_Hadrons_systematic_fy1040,data_v2_27GeV_Hadrons_systematic_fex1040,data_v2_27GeV_Hadrons_systematic_fey1040);
   gre->SetName("data_v2_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1200;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_27GeV_Hadrons_systematic1040 = new TH1F("Graph_data_v2_27GeV_Hadrons_systematic1040","#font[42]{#scale[1.3]{27 GeV}}",100,0,3.262668);
   Graph_data_v2_27GeV_Hadrons_systematic1040->SetMinimum(0.1590446);
   Graph_data_v2_27GeV_Hadrons_systematic1040->SetMaximum(2.934383);
   Graph_data_v2_27GeV_Hadrons_systematic1040->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons_systematic1040->SetStats(0);
   Graph_data_v2_27GeV_Hadrons_systematic1040->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons_systematic1040->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1040->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons_systematic1040);
   
   gre->Draw("e5");
   
   Double_t data_v2_39GeV_Hadrons_systematic_fx1041[12] = {
   0.2962567,
   0.4915369,
   0.6907406,
   0.8905588,
   1.090591,
   1.29055,
   1.490385,
   1.690278,
   1.890215,
   2.161277,
   2.561725,
   2.962668};
   Double_t data_v2_39GeV_Hadrons_systematic_fy1041[12] = {
   0.3702254,
   0.6688743,
   0.9421611,
   1.187112,
   1.417566,
   1.63465,
   1.835983,
   2.016161,
   2.173777,
   2.33273,
   2.527901,
   2.672655};
   Double_t data_v2_39GeV_Hadrons_systematic_fex1041[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_39GeV_Hadrons_systematic_fey1041[12] = {
   0.002038377,
   0.00168743,
   0.000598357,
   0.000239879,
   0.001436906,
   0.001102967,
   0.0008935697,
   0.001937734,
   0.002291951,
   0.002294229,
   0.006025754,
   0.01527939};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_systematic_fx1041,data_v2_39GeV_Hadrons_systematic_fy1041,data_v2_39GeV_Hadrons_systematic_fex1041,data_v2_39GeV_Hadrons_systematic_fey1041);
   gre->SetName("data_v2_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1201;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_39GeV_Hadrons_systematic1041 = new TH1F("Graph_data_v2_39GeV_Hadrons_systematic1041","#font[42]{#scale[1.3]{39 GeV}}",100,0,3.265309);
   Graph_data_v2_39GeV_Hadrons_systematic1041->SetMinimum(0.1362123);
   Graph_data_v2_39GeV_Hadrons_systematic1041->SetMaximum(2.919909);
   Graph_data_v2_39GeV_Hadrons_systematic1041->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons_systematic1041->SetStats(0);
   Graph_data_v2_39GeV_Hadrons_systematic1041->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons_systematic1041->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1041->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons_systematic1041);
   
   gre->Draw("e5");
   
   Double_t data_v2_62GeV_Hadrons_systematic_fx1042[12] = {
   0.2965595,
   0.4917632,
   0.6909853,
   0.8908598,
   1.090909,
   1.290878,
   1.490765,
   1.690667,
   1.890625,
   2.163099,
   2.563857,
   2.964808};
   Double_t data_v2_62GeV_Hadrons_systematic_fy1042[12] = {
   0.3565855,
   0.6531329,
   0.9231763,
   1.168138,
   1.392099,
   1.601147,
   1.794437,
   1.968169,
   2.123949,
   2.273173,
   2.456044,
   2.528507};
   Double_t data_v2_62GeV_Hadrons_systematic_fex1042[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_62GeV_Hadrons_systematic_fey1042[12] = {
   0.001649177,
   0.0009857521,
   0.001231916,
   0.0006125405,
   0.001782723,
   0.001249023,
   0.001914701,
   0.001296123,
   0.002746288,
   0.003449857,
   0.01032466,
   0.02029076};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_systematic_fx1042,data_v2_62GeV_Hadrons_systematic_fy1042,data_v2_62GeV_Hadrons_systematic_fex1042,data_v2_62GeV_Hadrons_systematic_fey1042);
   gre->SetName("data_v2_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1202;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_62GeV_Hadrons_systematic1042 = new TH1F("Graph_data_v2_62GeV_Hadrons_systematic1042","#font[42]{#scale[1.3]{62.4 GeV}}",100,0,3.267633);
   Graph_data_v2_62GeV_Hadrons_systematic1042->SetMinimum(0.1355502);
   Graph_data_v2_62GeV_Hadrons_systematic1042->SetMaximum(2.768184);
   Graph_data_v2_62GeV_Hadrons_systematic1042->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons_systematic1042->SetStats(0);
   Graph_data_v2_62GeV_Hadrons_systematic1042->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons_systematic1042->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1042->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons_systematic1042);
   
   gre->Draw("e5");
   
   Double_t data_v2_11GeV_Hadrons_fx1043[9] = {
   0.2951268,
   0.4912637,
   0.6908656,
   0.8906337,
   1.090424,
   1.290129,
   1.559091,
   1.957407,
   2.405256};
   Double_t data_v2_11GeV_Hadrons_fy1043[9] = {
   0.4238967,
   0.6980794,
   0.9327471,
   1.181421,
   1.3977,
   1.643015,
   1.935351,
   2.31926,
   2.611878};
   Double_t data_v2_11GeV_Hadrons_fex1043[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_11GeV_Hadrons_fey1043[9] = {
   0.006413711,
   0.006408686,
   0.007237338,
   0.008521139,
   0.01022107,
   0.01250909,
   0.0128034,
   0.0208112,
   0.03553172};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_fx1043,data_v2_11GeV_Hadrons_fy1043,data_v2_11GeV_Hadrons_fex1043,data_v2_11GeV_Hadrons_fey1043);
   gre->SetName("data_v2_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_11GeV_Hadrons1043 = new TH1F("Graph_data_v2_11GeV_Hadrons1043","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08411392,2.616269);
   Graph_data_v2_11GeV_Hadrons1043->SetMinimum(0.1944903);
   Graph_data_v2_11GeV_Hadrons1043->SetMaximum(2.870402);
   Graph_data_v2_11GeV_Hadrons1043->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons1043->SetStats(0);
   Graph_data_v2_11GeV_Hadrons1043->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons1043->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons1043->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons1043->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1043->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1043->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons1043->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons1043->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons1043);
   
   gre->Draw("p");
   
   Double_t data_v2_14GeV_Hadrons_fx1044[9] = {
   0.2959729,
   0.4912729,
   0.69058,
   0.8904142,
   1.0902,
   1.290027,
   1.559285,
   1.957663,
   2.406058};
   Double_t data_v2_14GeV_Hadrons_fy1044[9] = {
   0.4295658,
   0.7034804,
   0.9478161,
   1.18601,
   1.410682,
   1.64678,
   1.935829,
   2.27048,
   2.530503};
   Double_t data_v2_14GeV_Hadrons_fex1044[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_14GeV_Hadrons_fey1044[9] = {
   0.003627658,
   0.00358881,
   0.004080837,
   0.004830708,
   0.005834519,
   0.00715335,
   0.007318057,
   0.01185186,
   0.02012352};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_fx1044,data_v2_14GeV_Hadrons_fy1044,data_v2_14GeV_Hadrons_fex1044,data_v2_14GeV_Hadrons_fey1044);
   gre->SetName("data_v2_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_14GeV_Hadrons1044 = new TH1F("Graph_data_v2_14GeV_Hadrons1044","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08496437,2.617067);
   Graph_data_v2_14GeV_Hadrons1044->SetMinimum(0.2134692);
   Graph_data_v2_14GeV_Hadrons1044->SetMaximum(2.763096);
   Graph_data_v2_14GeV_Hadrons1044->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons1044->SetStats(0);
   Graph_data_v2_14GeV_Hadrons1044->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons1044->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons1044->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons1044->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1044->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1044->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons1044->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons1044->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons1044);
   
   gre->Draw("p");
   
   Double_t data_v2_19GeV_Hadrons_fx1045[9] = {
   0.2956249,
   0.4912639,
   0.6905406,
   0.8903813,
   1.090259,
   1.290101,
   1.559869,
   1.958654,
   2.408708};
   Double_t data_v2_19GeV_Hadrons_fy1045[9] = {
   0.3964864,
   0.6925562,
   0.9608167,
   1.198213,
   1.43551,
   1.663961,
   1.939885,
   2.286336,
   2.531981};
   Double_t data_v2_19GeV_Hadrons_fex1045[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_19GeV_Hadrons_fey1045[9] = {
   0.002846557,
   0.002828817,
   0.00322839,
   0.003823964,
   0.004621989,
   0.00565488,
   0.005752571,
   0.009207187,
   0.01533583};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_fx1045,data_v2_19GeV_Hadrons_fy1045,data_v2_19GeV_Hadrons_fex1045,data_v2_19GeV_Hadrons_fey1045);
   gre->SetName("data_v2_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_19GeV_Hadrons1045 = new TH1F("Graph_data_v2_19GeV_Hadrons1045","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.08431652,2.620017);
   Graph_data_v2_19GeV_Hadrons1045->SetMinimum(0.1782722);
   Graph_data_v2_19GeV_Hadrons1045->SetMaximum(2.762684);
   Graph_data_v2_19GeV_Hadrons1045->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons1045->SetStats(0);
   Graph_data_v2_19GeV_Hadrons1045->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons1045->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons1045->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons1045->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1045->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1045->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons1045->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons1045->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons1045);
   
   gre->Draw("p");
   
   Double_t data_v2_27GeV_Hadrons_fx1046[12] = {
   0.2958414,
   0.4914081,
   0.6906679,
   0.8905042,
   1.090294,
   1.290199,
   1.490113,
   1.689953,
   1.889815,
   2.159691,
   2.559786,
   2.960229};
   Double_t data_v2_27GeV_Hadrons_fy1046[12] = {
   0.3928046,
   0.6863216,
   0.951092,
   1.192575,
   1.423088,
   1.644113,
   1.852861,
   2.033455,
   2.193414,
   2.370325,
   2.574323,
   2.69814};
   Double_t data_v2_27GeV_Hadrons_fex1046[12] = {
   0,
   0,
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
   Double_t data_v2_27GeV_Hadrons_fey1046[12] = {
   0.0006017959,
   0.0005942362,
   0.0006753629,
   0.0007987381,
   0.0009616813,
   0.001175166,
   0.001450765,
   0.001812581,
   0.002294268,
   0.002449519,
   0.004450635,
   0.008158753};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_fx1046,data_v2_27GeV_Hadrons_fy1046,data_v2_27GeV_Hadrons_fex1046,data_v2_27GeV_Hadrons_fey1046);
   gre->SetName("data_v2_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_27GeV_Hadrons1046 = new TH1F("Graph_data_v2_27GeV_Hadrons1046","#font[42]{#scale[1.3]{27 GeV}}",100,0.02940258,3.226668);
   Graph_data_v2_27GeV_Hadrons1046->SetMinimum(0.1607932);
   Graph_data_v2_27GeV_Hadrons1046->SetMaximum(2.937709);
   Graph_data_v2_27GeV_Hadrons1046->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons1046->SetStats(0);
   Graph_data_v2_27GeV_Hadrons1046->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons1046->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons1046->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons1046->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1046->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1046->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons1046->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons1046->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons1046);
   
   gre->Draw("p");
   
   Double_t data_v2_39GeV_Hadrons_fx1047[12] = {
   0.2962567,
   0.4915369,
   0.6907406,
   0.8905588,
   1.090591,
   1.29055,
   1.490385,
   1.690278,
   1.890215,
   2.161277,
   2.561725,
   2.962668};
   Double_t data_v2_39GeV_Hadrons_fy1047[12] = {
   0.3702254,
   0.6688743,
   0.9421611,
   1.187112,
   1.417566,
   1.63465,
   1.835983,
   2.016161,
   2.173777,
   2.33273,
   2.527901,
   2.672655};
   Double_t data_v2_39GeV_Hadrons_fex1047[12] = {
   0,
   0,
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
   Double_t data_v2_39GeV_Hadrons_fey1047[12] = {
   0.001104108,
   0.001082346,
   0.001228225,
   0.001449767,
   0.001739581,
   0.002105541,
   0.002576645,
   0.003191172,
   0.003997563,
   0.004200384,
   0.007404764,
   0.01308838};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_fx1047,data_v2_39GeV_Hadrons_fy1047,data_v2_39GeV_Hadrons_fex1047,data_v2_39GeV_Hadrons_fey1047);
   gre->SetName("data_v2_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_39GeV_Hadrons1047 = new TH1F("Graph_data_v2_39GeV_Hadrons1047","#font[42]{#scale[1.3]{39 GeV}}",100,0.02961563,3.229309);
   Graph_data_v2_39GeV_Hadrons1047->SetMinimum(0.1374591);
   Graph_data_v2_39GeV_Hadrons1047->SetMaximum(2.917405);
   Graph_data_v2_39GeV_Hadrons1047->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons1047->SetStats(0);
   Graph_data_v2_39GeV_Hadrons1047->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons1047->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons1047->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons1047->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1047->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1047->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons1047->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons1047->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons1047);
   
   gre->Draw("p");
   
   Double_t data_v2_62GeV_Hadrons_fx1048[12] = {
   0.2965595,
   0.4917632,
   0.6909853,
   0.8908598,
   1.090909,
   1.290878,
   1.490765,
   1.690667,
   1.890625,
   2.163099,
   2.563857,
   2.964808};
   Double_t data_v2_62GeV_Hadrons_fy1048[12] = {
   0.3565855,
   0.6531329,
   0.9231763,
   1.168138,
   1.392099,
   1.601147,
   1.794437,
   1.968169,
   2.123949,
   2.273173,
   2.456044,
   2.528507};
   Double_t data_v2_62GeV_Hadrons_fex1048[12] = {
   0,
   0,
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
   Double_t data_v2_62GeV_Hadrons_fey1048[12] = {
   0.001385335,
   0.001345222,
   0.001515184,
   0.001775991,
   0.002113403,
   0.002535883,
   0.003072844,
   0.003762259,
   0.004655797,
   0.004810134,
   0.008210113,
   0.01405593};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_fx1048,data_v2_62GeV_Hadrons_fy1048,data_v2_62GeV_Hadrons_fex1048,data_v2_62GeV_Hadrons_fey1048);
   gre->SetName("data_v2_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_62GeV_Hadrons1048 = new TH1F("Graph_data_v2_62GeV_Hadrons1048","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.02973465,3.231633);
   Graph_data_v2_62GeV_Hadrons1048->SetMinimum(0.1364639);
   Graph_data_v2_62GeV_Hadrons1048->SetMaximum(2.761299);
   Graph_data_v2_62GeV_Hadrons1048->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons1048->SetStats(0);
   Graph_data_v2_62GeV_Hadrons1048->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons1048->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons1048->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons1048->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1048->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1048->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons1048->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons1048->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons1048);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_0_4->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_4
   TPad *Pad_1_4 = new TPad("Pad_1_4", "",0.525,0.628,0.9,0.804);
   Pad_1_4->Draw();
   Pad_1_4->cd();
   Pad_1_4->Range(-0.05,-0.3,2.86,5.67);
   Pad_1_4->SetFillColor(0);
   Pad_1_4->SetBorderMode(0);
   Pad_1_4->SetBorderSize(0);
   Pad_1_4->SetTickx(1);
   Pad_1_4->SetTicky(1);
   Pad_1_4->SetLeftMargin(0);
   Pad_1_4->SetRightMargin(0);
   Pad_1_4->SetTopMargin(0);
   Pad_1_4->SetBottomMargin(0);
   
   TH2F *__11 = new TH2F("__11","",2,-0.05,2.86,2,-0.3,5.67);
   __11->SetStats(0);
   __11->SetFillColor(10);
   __11->SetFillStyle(0);
   __11->GetXaxis()->SetNdivisions(508);
   __11->GetXaxis()->SetLabelFont(42);
   __11->GetXaxis()->SetLabelOffset(0.02);
   __11->GetXaxis()->SetLabelSize(0.13);
   __11->GetXaxis()->SetTitleSize(0.05);
   __11->GetXaxis()->SetTitleOffset(1.2);
   __11->GetXaxis()->SetTitleFont(42);
   __11->GetYaxis()->SetNdivisions(505);
   __11->GetYaxis()->SetLabelFont(42);
   __11->GetYaxis()->SetLabelOffset(0.02);
   __11->GetYaxis()->SetLabelSize(0.13);
   __11->GetYaxis()->SetTitleSize(0.05);
   __11->GetYaxis()->SetTitleOffset(1.4);
   __11->GetYaxis()->SetTitleFont(42);
   __11->GetZaxis()->SetLabelFont(42);
   __11->GetZaxis()->SetLabelSize(0.035);
   __11->GetZaxis()->SetTitleSize(0.035);
   __11->GetZaxis()->SetTitleFont(42);
   __11->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(d)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v3_11GeV_Hadrons_systematic_fx1049[7] = {
   0.2951268,
   0.4912637,
   0.6908656,
   0.9627164,
   1.360527,
   1.808141,
   2.405256};
   Double_t data_v3_11GeV_Hadrons_systematic_fy1049[7] = {
   0.2560899,
   0.5892068,
   0.8686554,
   1.261582,
   2.081782,
   2.944532,
   3.287083};
   Double_t data_v3_11GeV_Hadrons_systematic_fex1049[7] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_11GeV_Hadrons_systematic_fey1049[7] = {
   0.02772555,
   0.01327203,
   0.05150144,
   0.01889356,
   0.02041822,
   0.1915396,
   0.2274489};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_systematic_fx1049,data_v3_11GeV_Hadrons_systematic_fy1049,data_v3_11GeV_Hadrons_systematic_fex1049,data_v3_11GeV_Hadrons_systematic_fey1049);
   gre->SetName("data_v3_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1203;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v3_11GeV_Hadrons_systematic1049 = new TH1F("Graph_data_v3_11GeV_Hadrons_systematic1049","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04811392,2.652269);
   Graph_data_v3_11GeV_Hadrons_systematic1049->SetMinimum(0.2055279);
   Graph_data_v3_11GeV_Hadrons_systematic1049->SetMaximum(3.843149);
   Graph_data_v3_11GeV_Hadrons_systematic1049->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons_systematic1049->SetStats(0);
   Graph_data_v3_11GeV_Hadrons_systematic1049->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons_systematic1049->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1049->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons_systematic1049);
   
   gre->Draw("e5");
   
   Double_t data_v3_14GeV_Hadrons_systematic_fx1050[8] = {
   0.2959729,
   0.4912729,
   0.69058,
   0.8904142,
   1.161296,
   1.559285,
   1.957663,
   2.406058};
   Double_t data_v3_14GeV_Hadrons_systematic_fy1050[8] = {
   0.2535625,
   0.5247805,
   0.8770919,
   1.209173,
   1.649971,
   2.525633,
   3.190998,
   3.774721};
   Double_t data_v3_14GeV_Hadrons_systematic_fex1050[8] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_14GeV_Hadrons_systematic_fey1050[8] = {
   0.002349758,
   0.00824053,
   0.02151668,
   0.004779203,
   0.01639244,
   0.05959346,
   0.04103188,
   0.05487986};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_systematic_fx1050,data_v3_14GeV_Hadrons_systematic_fy1050,data_v3_14GeV_Hadrons_systematic_fex1050,data_v3_14GeV_Hadrons_systematic_fey1050);
   gre->SetName("data_v3_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1204;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_14GeV_Hadrons_systematic1050 = new TH1F("Graph_data_v3_14GeV_Hadrons_systematic1050","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04896437,2.653067);
   Graph_data_v3_14GeV_Hadrons_systematic1050->SetMinimum(0.2260915);
   Graph_data_v3_14GeV_Hadrons_systematic1050->SetMaximum(4.187439);
   Graph_data_v3_14GeV_Hadrons_systematic1050->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons_systematic1050->SetStats(0);
   Graph_data_v3_14GeV_Hadrons_systematic1050->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons_systematic1050->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1050->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons_systematic1050);
   
   gre->Draw("e5");
   
   Double_t data_v3_19GeV_Hadrons_systematic_fx1051[9] = {
   0.2956249,
   0.4912639,
   0.6905406,
   0.8903813,
   1.090259,
   1.360765,
   1.75915,
   2.158124,
   2.608553};
   Double_t data_v3_19GeV_Hadrons_systematic_fy1051[9] = {
   0.1972383,
   0.5241834,
   0.8267047,
   1.200328,
   1.579892,
   2.158826,
   2.95071,
   3.608763,
   4.119734};
   Double_t data_v3_19GeV_Hadrons_systematic_fex1051[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_19GeV_Hadrons_systematic_fey1051[9] = {
   0.005643409,
   0.0164954,
   0.007992655,
   0.00711393,
   0.01095344,
   0.01347769,
   0.05893474,
   0.04891613,
   0.0449982};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_systematic_fx1051,data_v3_19GeV_Hadrons_systematic_fy1051,data_v3_19GeV_Hadrons_systematic_fex1051,data_v3_19GeV_Hadrons_systematic_fey1051);
   gre->SetName("data_v3_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1205;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_19GeV_Hadrons_systematic1051 = new TH1F("Graph_data_v3_19GeV_Hadrons_systematic1051","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.02833204,2.875846);
   Graph_data_v3_19GeV_Hadrons_systematic1051->SetMinimum(0.1724354);
   Graph_data_v3_19GeV_Hadrons_systematic1051->SetMaximum(4.562046);
   Graph_data_v3_19GeV_Hadrons_systematic1051->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons_systematic1051->SetStats(0);
   Graph_data_v3_19GeV_Hadrons_systematic1051->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons_systematic1051->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1051->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons_systematic1051);
   
   gre->Draw("e5");
   
   Double_t data_v3_27GeV_Hadrons_systematic_fx1052[11] = {
   0.2958414,
   0.4914081,
   0.6906679,
   0.8905042,
   1.090294,
   1.290199,
   1.490113,
   1.689953,
   1.889815,
   2.159691,
   2.559786};
   Double_t data_v3_27GeV_Hadrons_systematic_fy1052[11] = {
   0.2055853,
   0.4983361,
   0.8404923,
   1.192233,
   1.573008,
   1.957767,
   2.331646,
   2.682212,
   3.112872,
   3.465767,
   3.921212};
   Double_t data_v3_27GeV_Hadrons_systematic_fex1052[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_27GeV_Hadrons_systematic_fey1052[11] = {
   0.006334928,
   0.01116682,
   0.005057337,
   0.003896689,
   0.003137794,
   0.005703306,
   0.01338841,
   0.02191853,
   0.05096958,
   0.05232387,
   0.0503067};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_systematic_fx1052,data_v3_27GeV_Hadrons_systematic_fy1052,data_v3_27GeV_Hadrons_systematic_fex1052,data_v3_27GeV_Hadrons_systematic_fey1052);
   gre->SetName("data_v3_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1206;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_27GeV_Hadrons_systematic1052 = new TH1F("Graph_data_v3_27GeV_Hadrons_systematic1052","#font[42]{#scale[1.3]{27 GeV}}",100,0.03344687,2.822181);
   Graph_data_v3_27GeV_Hadrons_systematic1052->SetMinimum(0.1793253);
   Graph_data_v3_27GeV_Hadrons_systematic1052->SetMaximum(4.348745);
   Graph_data_v3_27GeV_Hadrons_systematic1052->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons_systematic1052->SetStats(0);
   Graph_data_v3_27GeV_Hadrons_systematic1052->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons_systematic1052->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1052->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons_systematic1052);
   
   gre->Draw("e5");
   
   Double_t data_v3_39GeV_Hadrons_systematic_fx1053[11] = {
   0.2962567,
   0.4915369,
   0.6907406,
   0.8905588,
   1.090591,
   1.29055,
   1.490385,
   1.690278,
   1.890215,
   2.161277,
   2.561725};
   Double_t data_v3_39GeV_Hadrons_systematic_fy1053[11] = {
   0.2014186,
   0.4926566,
   0.8154998,
   1.185335,
   1.537009,
   1.909615,
   2.275546,
   2.624953,
   2.952806,
   3.343988,
   3.889255};
   Double_t data_v3_39GeV_Hadrons_systematic_fex1053[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_39GeV_Hadrons_systematic_fey1053[11] = {
   0.004293799,
   0.004592004,
   0.007785455,
   0.00563711,
   0.004132726,
   0.01631834,
   0.01419162,
   0.008833525,
   0.05130418,
   0.01283894,
   0.09820702};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_systematic_fx1053,data_v3_39GeV_Hadrons_systematic_fy1053,data_v3_39GeV_Hadrons_systematic_fex1053,data_v3_39GeV_Hadrons_systematic_fey1053);
   gre->SetName("data_v3_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1207;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_39GeV_Hadrons_systematic1053 = new TH1F("Graph_data_v3_39GeV_Hadrons_systematic1053","#font[42]{#scale[1.3]{39 GeV}}",100,0.0337099,2.824272);
   Graph_data_v3_39GeV_Hadrons_systematic1053->SetMinimum(0.1774123);
   Graph_data_v3_39GeV_Hadrons_systematic1053->SetMaximum(4.366495);
   Graph_data_v3_39GeV_Hadrons_systematic1053->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons_systematic1053->SetStats(0);
   Graph_data_v3_39GeV_Hadrons_systematic1053->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons_systematic1053->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1053->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons_systematic1053);
   
   gre->Draw("e5");
   
   Double_t data_v3_62GeV_Hadrons_systematic_fx1054[11] = {
   0.2965595,
   0.4917632,
   0.6909853,
   0.8908598,
   1.090909,
   1.290878,
   1.490765,
   1.690667,
   1.890625,
   2.163099,
   2.563857};
   Double_t data_v3_62GeV_Hadrons_systematic_fy1054[11] = {
   0.1883614,
   0.478877,
   0.7955384,
   1.140821,
   1.494177,
   1.858373,
   2.218834,
   2.530889,
   2.853789,
   3.175631,
   3.554755};
   Double_t data_v3_62GeV_Hadrons_systematic_fex1054[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_62GeV_Hadrons_systematic_fey1054[11] = {
   0.002453354,
   0.01019706,
   0.001690717,
   0.005102225,
   0.003039227,
   0.01050428,
   0.01424019,
   0.01190259,
   0.03750975,
   0.017968,
   0.05608824};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_systematic_fx1054,data_v3_62GeV_Hadrons_systematic_fy1054,data_v3_62GeV_Hadrons_systematic_fex1054,data_v3_62GeV_Hadrons_systematic_fey1054);
   gre->SetName("data_v3_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1208;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_62GeV_Hadrons_systematic1054 = new TH1F("Graph_data_v3_62GeV_Hadrons_systematic1054","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.03382977,2.826586);
   Graph_data_v3_62GeV_Hadrons_systematic1054->SetMinimum(0.1673172);
   Graph_data_v3_62GeV_Hadrons_systematic1054->SetMaximum(3.953337);
   Graph_data_v3_62GeV_Hadrons_systematic1054->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons_systematic1054->SetStats(0);
   Graph_data_v3_62GeV_Hadrons_systematic1054->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons_systematic1054->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1054->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons_systematic1054);
   
   gre->Draw("e5");
   
   Double_t data_v3_11GeV_Hadrons_fx1055[7] = {
   0.2951268,
   0.4912637,
   0.6908656,
   0.9627164,
   1.360527,
   1.808141,
   2.405256};
   Double_t data_v3_11GeV_Hadrons_fy1055[7] = {
   0.2560899,
   0.5892068,
   0.8686554,
   1.261582,
   2.081782,
   2.944532,
   3.287083};
   Double_t data_v3_11GeV_Hadrons_fex1055[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_11GeV_Hadrons_fey1055[7] = {
   0.0526462,
   0.05246773,
   0.0595621,
   0.05832211,
   0.0903539,
   0.1332283,
   0.2998126};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_fx1055,data_v3_11GeV_Hadrons_fy1055,data_v3_11GeV_Hadrons_fex1055,data_v3_11GeV_Hadrons_fey1055);
   gre->SetName("data_v3_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_11GeV_Hadrons1055 = new TH1F("Graph_data_v3_11GeV_Hadrons1055","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08411392,2.616269);
   Graph_data_v3_11GeV_Hadrons1055->SetMinimum(0.1830993);
   Graph_data_v3_11GeV_Hadrons1055->SetMaximum(3.925241);
   Graph_data_v3_11GeV_Hadrons1055->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons1055->SetStats(0);
   Graph_data_v3_11GeV_Hadrons1055->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons1055->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons1055->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons1055->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1055->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1055->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons1055->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons1055->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons1055);
   
   gre->Draw("p");
   
   Double_t data_v3_14GeV_Hadrons_fx1056[8] = {
   0.2959729,
   0.4912729,
   0.69058,
   0.8904142,
   1.161296,
   1.559285,
   1.957663,
   2.406058};
   Double_t data_v3_14GeV_Hadrons_fy1056[8] = {
   0.2535625,
   0.5247805,
   0.8770919,
   1.209173,
   1.649971,
   2.525633,
   3.190998,
   3.774721};
   Double_t data_v3_14GeV_Hadrons_fex1056[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_14GeV_Hadrons_fey1056[8] = {
   0.02946184,
   0.02883191,
   0.03320788,
   0.0398531,
   0.04079743,
   0.06401894,
   0.1021382,
   0.1699659};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_fx1056,data_v3_14GeV_Hadrons_fy1056,data_v3_14GeV_Hadrons_fex1056,data_v3_14GeV_Hadrons_fey1056);
   gre->SetName("data_v3_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_14GeV_Hadrons1056 = new TH1F("Graph_data_v3_14GeV_Hadrons1056","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08496437,2.617067);
   Graph_data_v3_14GeV_Hadrons1056->SetMinimum(0.2016906);
   Graph_data_v3_14GeV_Hadrons1056->SetMaximum(4.316745);
   Graph_data_v3_14GeV_Hadrons1056->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons1056->SetStats(0);
   Graph_data_v3_14GeV_Hadrons1056->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons1056->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons1056->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons1056->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1056->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1056->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons1056->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons1056->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons1056);
   
   gre->Draw("p");
   
   Double_t data_v3_19GeV_Hadrons_fx1057[9] = {
   0.2956249,
   0.4912639,
   0.6905406,
   0.8903813,
   1.090259,
   1.360765,
   1.75915,
   2.158124,
   2.608553};
   Double_t data_v3_19GeV_Hadrons_fy1057[9] = {
   0.1972383,
   0.5241834,
   0.8267047,
   1.200328,
   1.579892,
   2.158826,
   2.95071,
   3.608763,
   4.119734};
   Double_t data_v3_19GeV_Hadrons_fex1057[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_19GeV_Hadrons_fey1057[9] = {
   0.02212053,
   0.02177977,
   0.02491743,
   0.03010382,
   0.0369829,
   0.0389426,
   0.06037201,
   0.09988503,
   0.1685};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_fx1057,data_v3_19GeV_Hadrons_fy1057,data_v3_19GeV_Hadrons_fex1057,data_v3_19GeV_Hadrons_fey1057);
   gre->SetName("data_v3_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_19GeV_Hadrons1057 = new TH1F("Graph_data_v3_19GeV_Hadrons1057","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.06433204,2.839846);
   Graph_data_v3_19GeV_Hadrons1057->SetMinimum(0.157606);
   Graph_data_v3_19GeV_Hadrons1057->SetMaximum(4.699545);
   Graph_data_v3_19GeV_Hadrons1057->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons1057->SetStats(0);
   Graph_data_v3_19GeV_Hadrons1057->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons1057->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons1057->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons1057->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1057->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1057->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons1057->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons1057->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons1057);
   
   gre->Draw("p");
   
   Double_t data_v3_27GeV_Hadrons_fx1058[11] = {
   0.2958414,
   0.4914081,
   0.6906679,
   0.8905042,
   1.090294,
   1.290199,
   1.490113,
   1.689953,
   1.889815,
   2.159691,
   2.559786};
   Double_t data_v3_27GeV_Hadrons_fy1058[11] = {
   0.2055853,
   0.4983361,
   0.8404923,
   1.192233,
   1.573008,
   1.957767,
   2.331646,
   2.682212,
   3.112872,
   3.465767,
   3.921212};
   Double_t data_v3_27GeV_Hadrons_fex1058[11] = {
   0,
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
   Double_t data_v3_27GeV_Hadrons_fey1058[11] = {
   0.004412993,
   0.004306166,
   0.004931199,
   0.005926672,
   0.007261661,
   0.00897842,
   0.01113822,
   0.01391004,
   0.01760984,
   0.01889682,
   0.03362509};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_fx1058,data_v3_27GeV_Hadrons_fy1058,data_v3_27GeV_Hadrons_fex1058,data_v3_27GeV_Hadrons_fey1058);
   gre->SetName("data_v3_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_27GeV_Hadrons1058 = new TH1F("Graph_data_v3_27GeV_Hadrons1058","#font[42]{#scale[1.3]{27 GeV}}",100,0.06944687,2.786181);
   Graph_data_v3_27GeV_Hadrons1058->SetMinimum(0.181055);
   Graph_data_v3_27GeV_Hadrons1058->SetMaximum(4.330203);
   Graph_data_v3_27GeV_Hadrons1058->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons1058->SetStats(0);
   Graph_data_v3_27GeV_Hadrons1058->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons1058->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons1058->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons1058->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1058->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1058->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons1058->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons1058->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons1058);
   
   gre->Draw("p");
   
   Double_t data_v3_39GeV_Hadrons_fx1059[11] = {
   0.2962567,
   0.4915369,
   0.6907406,
   0.8905588,
   1.090591,
   1.29055,
   1.490385,
   1.690278,
   1.890215,
   2.161277,
   2.561725};
   Double_t data_v3_39GeV_Hadrons_fy1059[11] = {
   0.2014186,
   0.4926566,
   0.8154998,
   1.185335,
   1.537009,
   1.909615,
   2.275546,
   2.624953,
   2.952806,
   3.343988,
   3.889255};
   Double_t data_v3_39GeV_Hadrons_fex1059[11] = {
   0,
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
   Double_t data_v3_39GeV_Hadrons_fey1059[11] = {
   0.00741127,
   0.007181825,
   0.008179085,
   0.009828064,
   0.01196176,
   0.01465344,
   0.01804343,
   0.02236988,
   0.02794891,
   0.02962164,
   0.0512852};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_fx1059,data_v3_39GeV_Hadrons_fy1059,data_v3_39GeV_Hadrons_fex1059,data_v3_39GeV_Hadrons_fey1059);
   gre->SetName("data_v3_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_39GeV_Hadrons1059 = new TH1F("Graph_data_v3_39GeV_Hadrons1059","#font[42]{#scale[1.3]{39 GeV}}",100,0.0697099,2.788272);
   Graph_data_v3_39GeV_Hadrons1059->SetMinimum(0.1746066);
   Graph_data_v3_39GeV_Hadrons1059->SetMaximum(4.315193);
   Graph_data_v3_39GeV_Hadrons1059->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons1059->SetStats(0);
   Graph_data_v3_39GeV_Hadrons1059->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons1059->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons1059->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons1059->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1059->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1059->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons1059->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons1059->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons1059);
   
   gre->Draw("p");
   
   Double_t data_v3_62GeV_Hadrons_fx1060[11] = {
   0.2965595,
   0.4917632,
   0.6909853,
   0.8908598,
   1.090909,
   1.290878,
   1.490765,
   1.690667,
   1.890625,
   2.163099,
   2.563857};
   Double_t data_v3_62GeV_Hadrons_fy1060[11] = {
   0.1883614,
   0.478877,
   0.7955384,
   1.140821,
   1.494177,
   1.858373,
   2.218834,
   2.530889,
   2.853789,
   3.175631,
   3.554755};
   Double_t data_v3_62GeV_Hadrons_fex1060[11] = {
   0,
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
   Double_t data_v3_62GeV_Hadrons_fey1060[11] = {
   0.008586017,
   0.008245119,
   0.009312897,
   0.01107259,
   0.01338455,
   0.01626733,
   0.01986325,
   0.02432396,
   0.03005414,
   0.03130127,
   0.05243575};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_fx1060,data_v3_62GeV_Hadrons_fy1060,data_v3_62GeV_Hadrons_fex1060,data_v3_62GeV_Hadrons_fey1060);
   gre->SetName("data_v3_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_62GeV_Hadrons1060 = new TH1F("Graph_data_v3_62GeV_Hadrons1060","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.06982977,2.790586);
   Graph_data_v3_62GeV_Hadrons1060->SetMinimum(0.1617978);
   Graph_data_v3_62GeV_Hadrons1060->SetMaximum(3.949932);
   Graph_data_v3_62GeV_Hadrons1060->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons1060->SetStats(0);
   Graph_data_v3_62GeV_Hadrons1060->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons1060->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons1060->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons1060->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1060->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1060->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons1060->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons1060->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons1060);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_1_4->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_3
   TPad *Pad_0_3 = new TPad("Pad_0_3", "",0.15,0.452,0.525,0.628);
   Pad_0_3->Draw();
   Pad_0_3->cd();
   Pad_0_3->Range(-0.05,-0.3,2.86,5.67);
   Pad_0_3->SetFillColor(0);
   Pad_0_3->SetBorderMode(0);
   Pad_0_3->SetBorderSize(0);
   Pad_0_3->SetTickx(1);
   Pad_0_3->SetTicky(1);
   Pad_0_3->SetLeftMargin(0);
   Pad_0_3->SetRightMargin(0);
   Pad_0_3->SetTopMargin(0);
   Pad_0_3->SetBottomMargin(0);
   
   TH2F *__12 = new TH2F("__12","",2,-0.05,2.86,2,-0.3,5.67);
   __12->SetStats(0);
   __12->SetFillColor(10);
   __12->SetFillStyle(0);
   __12->GetXaxis()->SetNdivisions(508);
   __12->GetXaxis()->SetLabelFont(42);
   __12->GetXaxis()->SetLabelOffset(0.02);
   __12->GetXaxis()->SetLabelSize(0.13);
   __12->GetXaxis()->SetTitleSize(0.05);
   __12->GetXaxis()->SetTitleOffset(1.2);
   __12->GetXaxis()->SetTitleFont(42);
   __12->GetYaxis()->SetNdivisions(505);
   __12->GetYaxis()->SetLabelFont(42);
   __12->GetYaxis()->SetLabelOffset(0.02);
   __12->GetYaxis()->SetLabelSize(0.13);
   __12->GetYaxis()->SetTitleSize(0.05);
   __12->GetYaxis()->SetTitleOffset(1.4);
   __12->GetYaxis()->SetTitleFont(42);
   __12->GetZaxis()->SetLabelFont(42);
   __12->GetZaxis()->SetLabelSize(0.035);
   __12->GetZaxis()->SetTitleSize(0.035);
   __12->GetZaxis()->SetTitleFont(42);
   __12->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(i)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.35,4.8195,"#font[42]{#scale[1.0]{20-30%}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_11GeV_Hadrons_systematic_fx1061[9] = {
   0.2948828,
   0.4910548,
   0.6906266,
   0.8903789,
   1.090131,
   1.289865,
   1.558311,
   1.956827,
   2.404386};
   Double_t data_v2_11GeV_Hadrons_systematic_fy1061[9] = {
   0.4093973,
   0.7021196,
   0.9517123,
   1.199762,
   1.451885,
   1.687612,
   1.982068,
   2.334614,
   2.68813};
   Double_t data_v2_11GeV_Hadrons_systematic_fex1061[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_11GeV_Hadrons_systematic_fey1061[9] = {
   0.003273414,
   0.001460728,
   0.003029546,
   0.00335412,
   0.003340483,
   0.00420351,
   0.005209817,
   0.009894058,
   0.03257715};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_systematic_fx1061,data_v2_11GeV_Hadrons_systematic_fy1061,data_v2_11GeV_Hadrons_systematic_fex1061,data_v2_11GeV_Hadrons_systematic_fey1061);
   gre->SetName("data_v2_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1209;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v2_11GeV_Hadrons_systematic1061 = new TH1F("Graph_data_v2_11GeV_Hadrons_systematic1061","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04793248,2.651336);
   Graph_data_v2_11GeV_Hadrons_systematic1061->SetMinimum(0.1746655);
   Graph_data_v2_11GeV_Hadrons_systematic1061->SetMaximum(2.952166);
   Graph_data_v2_11GeV_Hadrons_systematic1061->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons_systematic1061->SetStats(0);
   Graph_data_v2_11GeV_Hadrons_systematic1061->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons_systematic1061->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1061->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons_systematic1061);
   
   gre->Draw("e5");
   
   Double_t data_v2_14GeV_Hadrons_systematic_fx1062[9] = {
   0.2957534,
   0.4911171,
   0.690361,
   0.8901574,
   1.089912,
   1.289813,
   1.558675,
   1.95733,
   2.405327};
   Double_t data_v2_14GeV_Hadrons_systematic_fy1062[9] = {
   0.4235938,
   0.7053214,
   0.9620019,
   1.204965,
   1.44122,
   1.692207,
   1.966976,
   2.308855,
   2.606727};
   Double_t data_v2_14GeV_Hadrons_systematic_fex1062[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_14GeV_Hadrons_systematic_fey1062[9] = {
   0.001253794,
   0.000504256,
   0.001249444,
   0.001858414,
   0.001577978,
   0.0009145474,
   0.001437876,
   0.003136938,
   0.01280173};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_systematic_fx1062,data_v2_14GeV_Hadrons_systematic_fy1062,data_v2_14GeV_Hadrons_systematic_fex1062,data_v2_14GeV_Hadrons_systematic_fey1062);
   gre->SetName("data_v2_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1210;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_14GeV_Hadrons_systematic1062 = new TH1F("Graph_data_v2_14GeV_Hadrons_systematic1062","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04879604,2.652285);
   Graph_data_v2_14GeV_Hadrons_systematic1062->SetMinimum(0.2026211);
   Graph_data_v2_14GeV_Hadrons_systematic1062->SetMaximum(2.839248);
   Graph_data_v2_14GeV_Hadrons_systematic1062->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons_systematic1062->SetStats(0);
   Graph_data_v2_14GeV_Hadrons_systematic1062->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons_systematic1062->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1062->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons_systematic1062);
   
   gre->Draw("e5");
   
   Double_t data_v2_19GeV_Hadrons_systematic_fx1063[9] = {
   0.2953795,
   0.491104,
   0.6903375,
   0.8901684,
   1.090018,
   1.289936,
   1.559443,
   1.958449,
   2.408332};
   Double_t data_v2_19GeV_Hadrons_systematic_fy1063[9] = {
   0.3989578,
   0.6969664,
   0.9653109,
   1.216275,
   1.458229,
   1.691773,
   1.983551,
   2.299459,
   2.604013};
   Double_t data_v2_19GeV_Hadrons_systematic_fex1063[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_19GeV_Hadrons_systematic_fey1063[9] = {
   0.003073707,
   0.000662953,
   0.001497883,
   0.002352299,
   0.001823241,
   0.0007461223,
   0.002208253,
   0.005494859,
   0.009935176};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_systematic_fx1063,data_v2_19GeV_Hadrons_systematic_fy1063,data_v2_19GeV_Hadrons_systematic_fex1063,data_v2_19GeV_Hadrons_systematic_fey1063);
   gre->SetName("data_v2_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1211;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_19GeV_Hadrons_systematic1063 = new TH1F("Graph_data_v2_19GeV_Hadrons_systematic1063","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.04808427,2.655627);
   Graph_data_v2_19GeV_Hadrons_systematic1063->SetMinimum(0.1740777);
   Graph_data_v2_19GeV_Hadrons_systematic1063->SetMaximum(2.835754);
   Graph_data_v2_19GeV_Hadrons_systematic1063->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons_systematic1063->SetStats(0);
   Graph_data_v2_19GeV_Hadrons_systematic1063->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons_systematic1063->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1063->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons_systematic1063);
   
   gre->Draw("e5");
   
   Double_t data_v2_27GeV_Hadrons_systematic_fx1064[12] = {
   0.2956264,
   0.4912624,
   0.6905119,
   0.8903099,
   1.090121,
   1.290033,
   1.490013,
   1.68989,
   1.889779,
   2.15975,
   2.559874,
   2.960434};
   Double_t data_v2_27GeV_Hadrons_systematic_fy1064[12] = {
   0.3896235,
   0.6886838,
   0.9613571,
   1.211796,
   1.446468,
   1.669514,
   1.876295,
   2.055401,
   2.212514,
   2.383975,
   2.562961,
   2.680601};
   Double_t data_v2_27GeV_Hadrons_systematic_fex1064[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_27GeV_Hadrons_systematic_fey1064[12] = {
   0.001654222,
   0.001541422,
   0.0007059458,
   0.0003535764,
   0.0001593891,
   0.0009950049,
   0.0009598521,
   0.001524985,
   0.002456788,
   0.001381164,
   0.001649286,
   0.001390301};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_systematic_fx1064,data_v2_27GeV_Hadrons_systematic_fy1064,data_v2_27GeV_Hadrons_systematic_fex1064,data_v2_27GeV_Hadrons_systematic_fey1064);
   gre->SetName("data_v2_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1212;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_27GeV_Hadrons_systematic1064 = new TH1F("Graph_data_v2_27GeV_Hadrons_systematic1064","#font[42]{#scale[1.3]{27 GeV}}",100,0,3.262915);
   Graph_data_v2_27GeV_Hadrons_systematic1064->SetMinimum(0.1585671);
   Graph_data_v2_27GeV_Hadrons_systematic1064->SetMaximum(2.911394);
   Graph_data_v2_27GeV_Hadrons_systematic1064->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons_systematic1064->SetStats(0);
   Graph_data_v2_27GeV_Hadrons_systematic1064->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons_systematic1064->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1064->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons_systematic1064);
   
   gre->Draw("e5");
   
   Double_t data_v2_39GeV_Hadrons_systematic_fx1065[12] = {
   0.2959277,
   0.4913744,
   0.6905801,
   0.890387,
   1.090421,
   1.290432,
   1.490323,
   1.69025,
   1.890197,
   2.161477,
   2.562045,
   2.963033};
   Double_t data_v2_39GeV_Hadrons_systematic_fy1065[12] = {
   0.3709898,
   0.6754912,
   0.9528163,
   1.20155,
   1.437707,
   1.656503,
   1.851525,
   2.026848,
   2.17718,
   2.329243,
   2.511848,
   2.609868};
   Double_t data_v2_39GeV_Hadrons_systematic_fex1065[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_39GeV_Hadrons_systematic_fey1065[12] = {
   0.001719095,
   0.001464683,
   0.0004898636,
   0.0003033684,
   0.0007380117,
   0.0004369162,
   0.002345956,
   0.001804469,
   0.0006581798,
   0.003417609,
   0.003592906,
   0.004653014};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_systematic_fx1065,data_v2_39GeV_Hadrons_systematic_fy1065,data_v2_39GeV_Hadrons_systematic_fex1065,data_v2_39GeV_Hadrons_systematic_fey1065);
   gre->SetName("data_v2_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1213;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_39GeV_Hadrons_systematic1065 = new TH1F("Graph_data_v2_39GeV_Hadrons_systematic1065","#font[42]{#scale[1.3]{39 GeV}}",100,0,3.265744);
   Graph_data_v2_39GeV_Hadrons_systematic1065->SetMinimum(0.1447457);
   Graph_data_v2_39GeV_Hadrons_systematic1065->SetMaximum(2.839046);
   Graph_data_v2_39GeV_Hadrons_systematic1065->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons_systematic1065->SetStats(0);
   Graph_data_v2_39GeV_Hadrons_systematic1065->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons_systematic1065->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1065->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons_systematic1065);
   
   gre->Draw("e5");
   
   Double_t data_v2_62GeV_Hadrons_systematic_fx1066[12] = {
   0.2961904,
   0.4916127,
   0.6908464,
   0.8906989,
   1.090762,
   1.290779,
   1.490726,
   1.690686,
   1.890675,
   2.163294,
   2.564163,
   2.965504};
   Double_t data_v2_62GeV_Hadrons_systematic_fy1066[12] = {
   0.3628493,
   0.6607472,
   0.9343634,
   1.178682,
   1.4099,
   1.612729,
   1.805445,
   1.966884,
   2.11688,
   2.263182,
   2.40871,
   2.443146};
   Double_t data_v2_62GeV_Hadrons_systematic_fex1066[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_62GeV_Hadrons_systematic_fey1066[12] = {
   0.00104587,
   0.001074722,
   0.0006353312,
   0.001957587,
   0.001302563,
   0.0008662755,
   0.0004129198,
   0.0008103612,
   0.002704603,
   0.003485388,
   0.0038241,
   0.01228116};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_systematic_fx1066,data_v2_62GeV_Hadrons_systematic_fy1066,data_v2_62GeV_Hadrons_systematic_fex1066,data_v2_62GeV_Hadrons_systematic_fey1066);
   gre->SetName("data_v2_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1214;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_62GeV_Hadrons_systematic1066 = new TH1F("Graph_data_v2_62GeV_Hadrons_systematic1066","#font[42]{#scale[1.3]{62.4 GeV}}",100,0,3.268436);
   Graph_data_v2_62GeV_Hadrons_systematic1066->SetMinimum(0.1524411);
   Graph_data_v2_62GeV_Hadrons_systematic1066->SetMaximum(2.66479);
   Graph_data_v2_62GeV_Hadrons_systematic1066->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons_systematic1066->SetStats(0);
   Graph_data_v2_62GeV_Hadrons_systematic1066->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons_systematic1066->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1066->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons_systematic1066);
   
   gre->Draw("e5");
   
   Double_t data_v2_11GeV_Hadrons_fx1067[9] = {
   0.2948828,
   0.4910548,
   0.6906266,
   0.8903789,
   1.090131,
   1.289865,
   1.558311,
   1.956827,
   2.404386};
   Double_t data_v2_11GeV_Hadrons_fy1067[9] = {
   0.4093973,
   0.7021196,
   0.9517123,
   1.199762,
   1.451885,
   1.687612,
   1.982068,
   2.334614,
   2.68813};
   Double_t data_v2_11GeV_Hadrons_fex1067[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_11GeV_Hadrons_fey1067[9] = {
   0.005626602,
   0.00566398,
   0.006449055,
   0.007640712,
   0.009270833,
   0.01140092,
   0.01174416,
   0.01925781,
   0.033234};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_fx1067,data_v2_11GeV_Hadrons_fy1067,data_v2_11GeV_Hadrons_fex1067,data_v2_11GeV_Hadrons_fey1067);
   gre->SetName("data_v2_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_11GeV_Hadrons1067 = new TH1F("Graph_data_v2_11GeV_Hadrons1067","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08393248,2.615336);
   Graph_data_v2_11GeV_Hadrons1067->SetMinimum(0.1720113);
   Graph_data_v2_11GeV_Hadrons1067->SetMaximum(2.953124);
   Graph_data_v2_11GeV_Hadrons1067->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons1067->SetStats(0);
   Graph_data_v2_11GeV_Hadrons1067->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons1067->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons1067->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons1067->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1067->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1067->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons1067->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons1067->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons1067);
   
   gre->Draw("p");
   
   Double_t data_v2_14GeV_Hadrons_fx1068[9] = {
   0.2957534,
   0.4911171,
   0.690361,
   0.8901574,
   1.089912,
   1.289813,
   1.558675,
   1.95733,
   2.405327};
   Double_t data_v2_14GeV_Hadrons_fy1068[9] = {
   0.4235938,
   0.7053214,
   0.9620019,
   1.204965,
   1.44122,
   1.692207,
   1.966976,
   2.308855,
   2.606727};
   Double_t data_v2_14GeV_Hadrons_fex1068[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_14GeV_Hadrons_fey1068[9] = {
   0.003127424,
   0.003112542,
   0.003562403,
   0.004243848,
   0.005163715,
   0.006374676,
   0.006549235,
   0.01067951,
   0.01823978};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_fx1068,data_v2_14GeV_Hadrons_fy1068,data_v2_14GeV_Hadrons_fex1068,data_v2_14GeV_Hadrons_fey1068);
   gre->SetName("data_v2_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_14GeV_Hadrons1068 = new TH1F("Graph_data_v2_14GeV_Hadrons1068","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08479604,2.616285);
   Graph_data_v2_14GeV_Hadrons1068->SetMinimum(0.2000163);
   Graph_data_v2_14GeV_Hadrons1068->SetMaximum(2.845417);
   Graph_data_v2_14GeV_Hadrons1068->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons1068->SetStats(0);
   Graph_data_v2_14GeV_Hadrons1068->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons1068->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons1068->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons1068->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1068->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1068->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons1068->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons1068->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons1068);
   
   gre->Draw("p");
   
   Double_t data_v2_19GeV_Hadrons_fx1069[9] = {
   0.2953795,
   0.491104,
   0.6903375,
   0.8901684,
   1.090018,
   1.289936,
   1.559443,
   1.958449,
   2.408332};
   Double_t data_v2_19GeV_Hadrons_fy1069[9] = {
   0.3989578,
   0.6969664,
   0.9653109,
   1.216275,
   1.458229,
   1.691773,
   1.983551,
   2.299459,
   2.604013};
   Double_t data_v2_19GeV_Hadrons_fex1069[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_19GeV_Hadrons_fey1069[9] = {
   0.002507031,
   0.002506379,
   0.002873402,
   0.003427713,
   0.004166136,
   0.005123299,
   0.005242223,
   0.008417181,
   0.01407185};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_fx1069,data_v2_19GeV_Hadrons_fy1069,data_v2_19GeV_Hadrons_fex1069,data_v2_19GeV_Hadrons_fey1069);
   gre->SetName("data_v2_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_19GeV_Hadrons1069 = new TH1F("Graph_data_v2_19GeV_Hadrons1069","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.08408427,2.619627);
   Graph_data_v2_19GeV_Hadrons1069->SetMinimum(0.1742873);
   Graph_data_v2_19GeV_Hadrons1069->SetMaximum(2.840248);
   Graph_data_v2_19GeV_Hadrons1069->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons1069->SetStats(0);
   Graph_data_v2_19GeV_Hadrons1069->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons1069->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons1069->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons1069->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1069->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1069->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons1069->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons1069->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons1069);
   
   gre->Draw("p");
   
   Double_t data_v2_27GeV_Hadrons_fx1070[12] = {
   0.2956264,
   0.4912624,
   0.6905119,
   0.8903099,
   1.090121,
   1.290033,
   1.490013,
   1.68989,
   1.889779,
   2.15975,
   2.559874,
   2.960434};
   Double_t data_v2_27GeV_Hadrons_fy1070[12] = {
   0.3896235,
   0.6886838,
   0.9613571,
   1.211796,
   1.446468,
   1.669514,
   1.876295,
   2.055401,
   2.212514,
   2.383975,
   2.562961,
   2.680601};
   Double_t data_v2_27GeV_Hadrons_fex1070[12] = {
   0,
   0,
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
   Double_t data_v2_27GeV_Hadrons_fey1070[12] = {
   0.0005420691,
   0.0005382339,
   0.0006149065,
   0.0007311322,
   0.0008841264,
   0.001084558,
   0.001342998,
   0.001680605,
   0.002129914,
   0.002272893,
   0.004121164,
   0.007540232};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_fx1070,data_v2_27GeV_Hadrons_fy1070,data_v2_27GeV_Hadrons_fex1070,data_v2_27GeV_Hadrons_fey1070);
   gre->SetName("data_v2_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_27GeV_Hadrons1070 = new TH1F("Graph_data_v2_27GeV_Hadrons1070","#font[42]{#scale[1.3]{27 GeV}}",100,0.02914569,3.226915);
   Graph_data_v2_27GeV_Hadrons1070->SetMinimum(0.1591755);
   Graph_data_v2_27GeV_Hadrons1070->SetMaximum(2.918047);
   Graph_data_v2_27GeV_Hadrons1070->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons1070->SetStats(0);
   Graph_data_v2_27GeV_Hadrons1070->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons1070->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons1070->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons1070->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1070->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1070->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons1070->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons1070->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons1070);
   
   gre->Draw("p");
   
   Double_t data_v2_39GeV_Hadrons_fx1071[12] = {
   0.2959277,
   0.4913744,
   0.6905801,
   0.890387,
   1.090421,
   1.290432,
   1.490323,
   1.69025,
   1.890197,
   2.161477,
   2.562045,
   2.963033};
   Double_t data_v2_39GeV_Hadrons_fy1071[12] = {
   0.3709898,
   0.6754912,
   0.9528163,
   1.20155,
   1.437707,
   1.656503,
   1.851525,
   2.026848,
   2.17718,
   2.329243,
   2.511848,
   2.609868};
   Double_t data_v2_39GeV_Hadrons_fex1071[12] = {
   0,
   0,
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
   Double_t data_v2_39GeV_Hadrons_fey1071[12] = {
   0.0009696371,
   0.0009575876,
   0.001091615,
   0.001293792,
   0.001559834,
   0.001893632,
   0.002321061,
   0.002877607,
   0.003604591,
   0.003781769,
   0.006639312,
   0.01168975};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_fx1071,data_v2_39GeV_Hadrons_fy1071,data_v2_39GeV_Hadrons_fex1071,data_v2_39GeV_Hadrons_fey1071);
   gre->SetName("data_v2_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_39GeV_Hadrons1071 = new TH1F("Graph_data_v2_39GeV_Hadrons1071","#font[42]{#scale[1.3]{39 GeV}}",100,0.02921711,3.229744);
   Graph_data_v2_39GeV_Hadrons1071->SetMinimum(0.1448664);
   Graph_data_v2_39GeV_Hadrons1071->SetMaximum(2.846712);
   Graph_data_v2_39GeV_Hadrons1071->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons1071->SetStats(0);
   Graph_data_v2_39GeV_Hadrons1071->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons1071->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons1071->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons1071->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1071->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1071->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons1071->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons1071->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons1071);
   
   gre->Draw("p");
   
   Double_t data_v2_62GeV_Hadrons_fx1072[12] = {
   0.2961904,
   0.4916127,
   0.6908464,
   0.8906989,
   1.090762,
   1.290779,
   1.490726,
   1.690686,
   1.890675,
   2.163294,
   2.564163,
   2.965504};
   Double_t data_v2_62GeV_Hadrons_fy1072[12] = {
   0.3628493,
   0.6607472,
   0.9343634,
   1.178682,
   1.4099,
   1.612729,
   1.805445,
   1.966884,
   2.11688,
   2.263182,
   2.40871,
   2.443146};
   Double_t data_v2_62GeV_Hadrons_fex1072[12] = {
   0,
   0,
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
   Double_t data_v2_62GeV_Hadrons_fey1072[12] = {
   0.00123419,
   0.001207264,
   0.001365454,
   0.001605768,
   0.001919251,
   0.002306891,
   0.002800341,
   0.003428276,
   0.004239465,
   0.004368555,
   0.007411923,
   0.01257397};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_fx1072,data_v2_62GeV_Hadrons_fy1072,data_v2_62GeV_Hadrons_fex1072,data_v2_62GeV_Hadrons_fey1072);
   gre->SetName("data_v2_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_62GeV_Hadrons1072 = new TH1F("Graph_data_v2_62GeV_Hadrons1072","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.02925901,3.232436);
   Graph_data_v2_62GeV_Hadrons1072->SetMinimum(0.1522046);
   Graph_data_v2_62GeV_Hadrons1072->SetMaximum(2.665131);
   Graph_data_v2_62GeV_Hadrons1072->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons1072->SetStats(0);
   Graph_data_v2_62GeV_Hadrons1072->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons1072->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons1072->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons1072->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1072->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1072->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons1072->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons1072->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons1072);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_0_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_3
   TPad *Pad_1_3 = new TPad("Pad_1_3", "",0.525,0.452,0.9,0.628);
   Pad_1_3->Draw();
   Pad_1_3->cd();
   Pad_1_3->Range(-0.05,-0.3,2.86,5.67);
   Pad_1_3->SetFillColor(0);
   Pad_1_3->SetBorderMode(0);
   Pad_1_3->SetBorderSize(0);
   Pad_1_3->SetTickx(1);
   Pad_1_3->SetTicky(1);
   Pad_1_3->SetLeftMargin(0);
   Pad_1_3->SetRightMargin(0);
   Pad_1_3->SetTopMargin(0);
   Pad_1_3->SetBottomMargin(0);
   
   TH2F *__13 = new TH2F("__13","",2,-0.05,2.86,2,-0.3,5.67);
   __13->SetStats(0);
   __13->SetFillColor(10);
   __13->SetFillStyle(0);
   __13->GetXaxis()->SetNdivisions(508);
   __13->GetXaxis()->SetLabelFont(42);
   __13->GetXaxis()->SetLabelOffset(0.02);
   __13->GetXaxis()->SetLabelSize(0.13);
   __13->GetXaxis()->SetTitleSize(0.05);
   __13->GetXaxis()->SetTitleOffset(1.2);
   __13->GetXaxis()->SetTitleFont(42);
   __13->GetYaxis()->SetNdivisions(505);
   __13->GetYaxis()->SetLabelFont(42);
   __13->GetYaxis()->SetLabelOffset(0.02);
   __13->GetYaxis()->SetLabelSize(0.13);
   __13->GetYaxis()->SetTitleSize(0.05);
   __13->GetYaxis()->SetTitleOffset(1.4);
   __13->GetYaxis()->SetTitleFont(42);
   __13->GetZaxis()->SetLabelFont(42);
   __13->GetZaxis()->SetLabelSize(0.035);
   __13->GetZaxis()->SetTitleSize(0.035);
   __13->GetZaxis()->SetTitleFont(42);
   __13->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(f)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v3_11GeV_Hadrons_systematic_fx1073[7] = {
   0.2948828,
   0.4910548,
   0.6906266,
   0.9615674,
   1.359707,
   1.806986,
   2.404386};
   Double_t data_v3_11GeV_Hadrons_systematic_fy1073[7] = {
   0.2861753,
   0.5081066,
   0.8719218,
   1.293093,
   2.146773,
   3.229805,
   4.025781};
   Double_t data_v3_11GeV_Hadrons_systematic_fex1073[7] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_11GeV_Hadrons_systematic_fey1073[7] = {
   0.01706096,
   0.04611977,
   0.04215216,
   0.02771062,
   0.0200347,
   0.08819806,
   0.2098661};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_systematic_fx1073,data_v3_11GeV_Hadrons_systematic_fy1073,data_v3_11GeV_Hadrons_systematic_fex1073,data_v3_11GeV_Hadrons_systematic_fey1073);
   gre->SetName("data_v3_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1215;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v3_11GeV_Hadrons_systematic1073 = new TH1F("Graph_data_v3_11GeV_Hadrons_systematic1073","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04793248,2.651336);
   Graph_data_v3_11GeV_Hadrons_systematic1073->SetMinimum(0.2422029);
   Graph_data_v3_11GeV_Hadrons_systematic1073->SetMaximum(4.6323);
   Graph_data_v3_11GeV_Hadrons_systematic1073->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons_systematic1073->SetStats(0);
   Graph_data_v3_11GeV_Hadrons_systematic1073->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons_systematic1073->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1073->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons_systematic1073);
   
   gre->Draw("e5");
   
   Double_t data_v3_14GeV_Hadrons_systematic_fx1074[8] = {
   0.2957534,
   0.4911171,
   0.690361,
   0.8901574,
   1.160357,
   1.558675,
   1.95733,
   2.405327};
   Double_t data_v3_14GeV_Hadrons_systematic_fy1074[8] = {
   0.2322712,
   0.532852,
   0.8525876,
   1.172638,
   1.769516,
   2.624354,
   3.32223,
   4.638386};
   Double_t data_v3_14GeV_Hadrons_systematic_fex1074[8] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_14GeV_Hadrons_systematic_fey1074[8] = {
   0.03078286,
   0.01189948,
   0.01764879,
   0.02078592,
   0.0274113,
   0.06104908,
   0.0610836,
   0.2342267};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_systematic_fx1074,data_v3_14GeV_Hadrons_systematic_fy1074,data_v3_14GeV_Hadrons_systematic_fex1074,data_v3_14GeV_Hadrons_systematic_fey1074);
   gre->SetName("data_v3_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1216;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_14GeV_Hadrons_systematic1074 = new TH1F("Graph_data_v3_14GeV_Hadrons_systematic1074","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04879604,2.652285);
   Graph_data_v3_14GeV_Hadrons_systematic1074->SetMinimum(0.1813395);
   Graph_data_v3_14GeV_Hadrons_systematic1074->SetMaximum(5.339725);
   Graph_data_v3_14GeV_Hadrons_systematic1074->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons_systematic1074->SetStats(0);
   Graph_data_v3_14GeV_Hadrons_systematic1074->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons_systematic1074->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1074->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons_systematic1074);
   
   gre->Draw("e5");
   
   Double_t data_v3_19GeV_Hadrons_systematic_fx1075[9] = {
   0.2953795,
   0.491104,
   0.6903375,
   0.8901684,
   1.090018,
   1.360145,
   1.758767,
   2.158217,
   2.60852};
   Double_t data_v3_19GeV_Hadrons_systematic_fy1075[9] = {
   0.220516,
   0.5023194,
   0.8642082,
   1.212563,
   1.676707,
   2.172947,
   2.943756,
   3.574587,
   4.193158};
   Double_t data_v3_19GeV_Hadrons_systematic_fex1075[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_19GeV_Hadrons_systematic_fey1075[9] = {
   0.00799806,
   0.02273675,
   0.03344825,
   0.0208631,
   0.02603958,
   0.06038845,
   0.08303768,
   0.1242463,
   0.1183426};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_systematic_fx1075,data_v3_19GeV_Hadrons_systematic_fy1075,data_v3_19GeV_Hadrons_systematic_fex1075,data_v3_19GeV_Hadrons_systematic_fey1075);
   gre->SetName("data_v3_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1217;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_19GeV_Hadrons_systematic1075 = new TH1F("Graph_data_v3_19GeV_Hadrons_systematic1075","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.02806546,2.875834);
   Graph_data_v3_19GeV_Hadrons_systematic1075->SetMinimum(0.1912662);
   Graph_data_v3_19GeV_Hadrons_systematic1075->SetMaximum(4.721398);
   Graph_data_v3_19GeV_Hadrons_systematic1075->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons_systematic1075->SetStats(0);
   Graph_data_v3_19GeV_Hadrons_systematic1075->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons_systematic1075->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1075->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons_systematic1075);
   
   gre->Draw("e5");
   
   Double_t data_v3_27GeV_Hadrons_systematic_fx1076[11] = {
   0.2956264,
   0.4912624,
   0.6905119,
   0.8903099,
   1.090121,
   1.290033,
   1.490013,
   1.68989,
   1.889779,
   2.15975,
   2.559874};
   Double_t data_v3_27GeV_Hadrons_systematic_fy1076[11] = {
   0.1998239,
   0.5027397,
   0.8548036,
   1.22412,
   1.615242,
   1.998392,
   2.367695,
   2.748161,
   3.048232,
   3.472842,
   3.932718};
   Double_t data_v3_27GeV_Hadrons_systematic_fex1076[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_27GeV_Hadrons_systematic_fey1076[11] = {
   0.006517938,
   0.009643517,
   0.01099479,
   0.003217567,
   0.00356799,
   0.01739862,
   0.01478015,
   0.03062176,
   0.03433694,
   0.05560738,
   0.07286373};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_systematic_fx1076,data_v3_27GeV_Hadrons_systematic_fy1076,data_v3_27GeV_Hadrons_systematic_fex1076,data_v3_27GeV_Hadrons_systematic_fey1076);
   gre->SetName("data_v3_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1218;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_27GeV_Hadrons_systematic1076 = new TH1F("Graph_data_v3_27GeV_Hadrons_systematic1076","#font[42]{#scale[1.3]{27 GeV}}",100,0.03320171,2.822299);
   Graph_data_v3_27GeV_Hadrons_systematic1076->SetMinimum(0.1739754);
   Graph_data_v3_27GeV_Hadrons_systematic1076->SetMaximum(4.38681);
   Graph_data_v3_27GeV_Hadrons_systematic1076->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons_systematic1076->SetStats(0);
   Graph_data_v3_27GeV_Hadrons_systematic1076->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons_systematic1076->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1076->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons_systematic1076);
   
   gre->Draw("e5");
   
   Double_t data_v3_39GeV_Hadrons_systematic_fx1077[11] = {
   0.2959277,
   0.4913744,
   0.6905801,
   0.890387,
   1.090421,
   1.290432,
   1.490323,
   1.69025,
   1.890197,
   2.161477,
   2.562045};
   Double_t data_v3_39GeV_Hadrons_systematic_fy1077[11] = {
   0.1979641,
   0.4936217,
   0.8489562,
   1.201444,
   1.562873,
   1.961253,
   2.323636,
   2.637535,
   2.979606,
   3.250955,
   3.654855};
   Double_t data_v3_39GeV_Hadrons_systematic_fex1077[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_39GeV_Hadrons_systematic_fey1077[11] = {
   0.002493142,
   0.01294532,
   0.002061949,
   0.003878376,
   0.01051527,
   0.008316884,
   0.01325199,
   0.03211651,
   0.02383392,
   0.01450271,
   0.02357383};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_systematic_fx1077,data_v3_39GeV_Hadrons_systematic_fy1077,data_v3_39GeV_Hadrons_systematic_fex1077,data_v3_39GeV_Hadrons_systematic_fey1077);
   gre->SetName("data_v3_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1219;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_39GeV_Hadrons_systematic1077 = new TH1F("Graph_data_v3_39GeV_Hadrons_systematic1077","#font[42]{#scale[1.3]{39 GeV}}",100,0.03331594,2.824657);
   Graph_data_v3_39GeV_Hadrons_systematic1077->SetMinimum(0.1759238);
   Graph_data_v3_39GeV_Hadrons_systematic1077->SetMaximum(4.026724);
   Graph_data_v3_39GeV_Hadrons_systematic1077->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons_systematic1077->SetStats(0);
   Graph_data_v3_39GeV_Hadrons_systematic1077->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons_systematic1077->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1077->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons_systematic1077);
   
   gre->Draw("e5");
   
   Double_t data_v3_62GeV_Hadrons_systematic_fx1078[11] = {
   0.2961904,
   0.4916127,
   0.6908464,
   0.8906989,
   1.090762,
   1.290779,
   1.490726,
   1.690686,
   1.890675,
   2.163294,
   2.564163};
   Double_t data_v3_62GeV_Hadrons_systematic_fy1078[11] = {
   0.1878584,
   0.4841113,
   0.8038616,
   1.175476,
   1.546221,
   1.909571,
   2.212477,
   2.48357,
   2.755432,
   3.196786,
   3.391129};
   Double_t data_v3_62GeV_Hadrons_systematic_fex1078[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_62GeV_Hadrons_systematic_fey1078[11] = {
   0.002807607,
   0.00687919,
   0.005008911,
   0.003640193,
   0.008640673,
   0.008797429,
   0.01263953,
   0.01673966,
   0.02410967,
   0.0216684,
   0.04951861};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_systematic_fx1078,data_v3_62GeV_Hadrons_systematic_fy1078,data_v3_62GeV_Hadrons_systematic_fex1078,data_v3_62GeV_Hadrons_systematic_fey1078);
   gre->SetName("data_v3_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1220;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_62GeV_Hadrons_systematic1078 = new TH1F("Graph_data_v3_62GeV_Hadrons_systematic1078","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.03339309,2.826961);
   Graph_data_v3_62GeV_Hadrons_systematic1078->SetMinimum(0.1665457);
   Graph_data_v3_62GeV_Hadrons_systematic1078->SetMaximum(3.766207);
   Graph_data_v3_62GeV_Hadrons_systematic1078->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons_systematic1078->SetStats(0);
   Graph_data_v3_62GeV_Hadrons_systematic1078->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons_systematic1078->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1078->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons_systematic1078);
   
   gre->Draw("e5");
   
   Double_t data_v3_11GeV_Hadrons_fx1079[7] = {
   0.2948828,
   0.4910548,
   0.6906266,
   0.9615674,
   1.359707,
   1.806986,
   2.404386};
   Double_t data_v3_11GeV_Hadrons_fy1079[7] = {
   0.2861753,
   0.5081066,
   0.8719218,
   1.293093,
   2.146773,
   3.229805,
   4.025781};
   Double_t data_v3_11GeV_Hadrons_fex1079[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_11GeV_Hadrons_fey1079[7] = {
   0.07021071,
   0.06959199,
   0.0802933,
   0.07984661,
   0.1254171,
   0.1900418,
   0.430853};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_fx1079,data_v3_11GeV_Hadrons_fy1079,data_v3_11GeV_Hadrons_fex1079,data_v3_11GeV_Hadrons_fey1079);
   gre->SetName("data_v3_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_11GeV_Hadrons1079 = new TH1F("Graph_data_v3_11GeV_Hadrons1079","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08393248,2.615336);
   Graph_data_v3_11GeV_Hadrons1079->SetMinimum(0.1943681);
   Graph_data_v3_11GeV_Hadrons1079->SetMaximum(4.880701);
   Graph_data_v3_11GeV_Hadrons1079->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons1079->SetStats(0);
   Graph_data_v3_11GeV_Hadrons1079->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons1079->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons1079->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons1079->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1079->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1079->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons1079->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons1079->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons1079);
   
   gre->Draw("p");
   
   Double_t data_v3_14GeV_Hadrons_fx1080[8] = {
   0.2957534,
   0.4911171,
   0.690361,
   0.8901574,
   1.160357,
   1.558675,
   1.95733,
   2.405327};
   Double_t data_v3_14GeV_Hadrons_fy1080[8] = {
   0.2322712,
   0.532852,
   0.8525876,
   1.172638,
   1.769516,
   2.624354,
   3.32223,
   4.638386};
   Double_t data_v3_14GeV_Hadrons_fex1080[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_14GeV_Hadrons_fey1080[8] = {
   0.03995409,
   0.03938908,
   0.04540306,
   0.05473668,
   0.05793228,
   0.09076427,
   0.145427,
   0.2472914};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_fx1080,data_v3_14GeV_Hadrons_fy1080,data_v3_14GeV_Hadrons_fex1080,data_v3_14GeV_Hadrons_fey1080);
   gre->SetName("data_v3_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_14GeV_Hadrons1080 = new TH1F("Graph_data_v3_14GeV_Hadrons1080","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08479604,2.616285);
   Graph_data_v3_14GeV_Hadrons1080->SetMinimum(0.1730854);
   Graph_data_v3_14GeV_Hadrons1080->SetMaximum(5.355013);
   Graph_data_v3_14GeV_Hadrons1080->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons1080->SetStats(0);
   Graph_data_v3_14GeV_Hadrons1080->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons1080->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons1080->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons1080->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1080->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1080->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons1080->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons1080->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons1080);
   
   gre->Draw("p");
   
   Double_t data_v3_19GeV_Hadrons_fx1081[9] = {
   0.2953795,
   0.491104,
   0.6903375,
   0.8901684,
   1.090018,
   1.360145,
   1.758767,
   2.158217,
   2.60852};
   Double_t data_v3_19GeV_Hadrons_fy1081[9] = {
   0.220516,
   0.5023194,
   0.8642082,
   1.212563,
   1.676707,
   2.172947,
   2.943756,
   3.574587,
   4.193158};
   Double_t data_v3_19GeV_Hadrons_fex1081[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_19GeV_Hadrons_fey1081[9] = {
   0.02950016,
   0.02911322,
   0.03372184,
   0.04082527,
   0.05092625,
   0.05335078,
   0.08305076,
   0.1381929,
   0.2344955};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_fx1081,data_v3_19GeV_Hadrons_fy1081,data_v3_19GeV_Hadrons_fex1081,data_v3_19GeV_Hadrons_fey1081);
   gre->SetName("data_v3_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_19GeV_Hadrons1081 = new TH1F("Graph_data_v3_19GeV_Hadrons1081","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.06406546,2.839834);
   Graph_data_v3_19GeV_Hadrons1081->SetMinimum(0.1719143);
   Graph_data_v3_19GeV_Hadrons1081->SetMaximum(4.851317);
   Graph_data_v3_19GeV_Hadrons1081->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons1081->SetStats(0);
   Graph_data_v3_19GeV_Hadrons1081->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons1081->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons1081->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons1081->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1081->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1081->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons1081->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons1081->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons1081);
   
   gre->Draw("p");
   
   Double_t data_v3_27GeV_Hadrons_fx1082[11] = {
   0.2956264,
   0.4912624,
   0.6905119,
   0.8903099,
   1.090121,
   1.290033,
   1.490013,
   1.68989,
   1.889779,
   2.15975,
   2.559874};
   Double_t data_v3_27GeV_Hadrons_fy1082[11] = {
   0.1998239,
   0.5027397,
   0.8548036,
   1.22412,
   1.615242,
   1.998392,
   2.367695,
   2.748161,
   3.048232,
   3.472842,
   3.932718};
   Double_t data_v3_27GeV_Hadrons_fex1082[11] = {
   0,
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
   Double_t data_v3_27GeV_Hadrons_fey1082[11] = {
   0.005858422,
   0.005749853,
   0.006623379,
   0.00801546,
   0.009870801,
   0.01224148,
   0.01522334,
   0.019075,
   0.02404632,
   0.02586602,
   0.04602128};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_fx1082,data_v3_27GeV_Hadrons_fy1082,data_v3_27GeV_Hadrons_fex1082,data_v3_27GeV_Hadrons_fey1082);
   gre->SetName("data_v3_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_27GeV_Hadrons1082 = new TH1F("Graph_data_v3_27GeV_Hadrons1082","#font[42]{#scale[1.3]{27 GeV}}",100,0.06920171,2.786299);
   Graph_data_v3_27GeV_Hadrons1082->SetMinimum(0.174569);
   Graph_data_v3_27GeV_Hadrons1082->SetMaximum(4.357217);
   Graph_data_v3_27GeV_Hadrons1082->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons1082->SetStats(0);
   Graph_data_v3_27GeV_Hadrons1082->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons1082->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons1082->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons1082->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1082->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1082->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons1082->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons1082->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons1082);
   
   gre->Draw("p");
   
   Double_t data_v3_39GeV_Hadrons_fx1083[11] = {
   0.2959277,
   0.4913744,
   0.6905801,
   0.890387,
   1.090421,
   1.290432,
   1.490323,
   1.69025,
   1.890197,
   2.161477,
   2.562045};
   Double_t data_v3_39GeV_Hadrons_fy1083[11] = {
   0.1979641,
   0.4936217,
   0.8489562,
   1.201444,
   1.562873,
   1.961253,
   2.323636,
   2.637535,
   2.979606,
   3.250955,
   3.654855};
   Double_t data_v3_39GeV_Hadrons_fex1083[11] = {
   0,
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
   Double_t data_v3_39GeV_Hadrons_fey1083[11] = {
   0.00955461,
   0.009323271,
   0.01071129,
   0.01289301,
   0.01577625,
   0.01942861,
   0.0239532,
   0.02965818,
   0.03709264,
   0.0390838,
   0.06749211};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_fx1083,data_v3_39GeV_Hadrons_fy1083,data_v3_39GeV_Hadrons_fex1083,data_v3_39GeV_Hadrons_fey1083);
   gre->SetName("data_v3_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_39GeV_Hadrons1083 = new TH1F("Graph_data_v3_39GeV_Hadrons1083","#font[42]{#scale[1.3]{39 GeV}}",100,0.06931594,2.788657);
   Graph_data_v3_39GeV_Hadrons1083->SetMinimum(0.1695685);
   Graph_data_v3_39GeV_Hadrons1083->SetMaximum(4.07574);
   Graph_data_v3_39GeV_Hadrons1083->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons1083->SetStats(0);
   Graph_data_v3_39GeV_Hadrons1083->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons1083->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons1083->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons1083->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1083->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1083->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons1083->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons1083->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons1083);
   
   gre->Draw("p");
   
   Double_t data_v3_62GeV_Hadrons_fx1084[11] = {
   0.2961904,
   0.4916127,
   0.6908464,
   0.8906989,
   1.090762,
   1.290779,
   1.490726,
   1.690686,
   1.890675,
   2.163294,
   2.564163};
   Double_t data_v3_62GeV_Hadrons_fy1084[11] = {
   0.1878584,
   0.4841113,
   0.8038616,
   1.175476,
   1.546221,
   1.909571,
   2.212477,
   2.48357,
   2.755432,
   3.196786,
   3.391129};
   Double_t data_v3_62GeV_Hadrons_fex1084[11] = {
   0,
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
   Double_t data_v3_62GeV_Hadrons_fey1084[11] = {
   0.01076103,
   0.01041145,
   0.01181297,
   0.01414733,
   0.01719757,
   0.02094131,
   0.02547766,
   0.03117031,
   0.03845696,
   0.0401701,
   0.06672624};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_fx1084,data_v3_62GeV_Hadrons_fy1084,data_v3_62GeV_Hadrons_fex1084,data_v3_62GeV_Hadrons_fey1084);
   gre->SetName("data_v3_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_62GeV_Hadrons1084 = new TH1F("Graph_data_v3_62GeV_Hadrons1084","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.06939309,2.790961);
   Graph_data_v3_62GeV_Hadrons1084->SetMinimum(0.1593876);
   Graph_data_v3_62GeV_Hadrons1084->SetMaximum(3.785931);
   Graph_data_v3_62GeV_Hadrons1084->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons1084->SetStats(0);
   Graph_data_v3_62GeV_Hadrons1084->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons1084->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons1084->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons1084->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1084->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1084->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons1084->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons1084->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons1084);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(0.4,4.8195,"#font[42]{ #scale[1.0]{ STAR Preliminary}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_1_3->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_2
   TPad *Pad_0_2 = new TPad("Pad_0_2", "",0.15,0.276,0.525,0.452);
   Pad_0_2->Draw();
   Pad_0_2->cd();
   Pad_0_2->Range(-0.05,-0.3,2.86,5.67);
   Pad_0_2->SetFillColor(0);
   Pad_0_2->SetBorderMode(0);
   Pad_0_2->SetBorderSize(0);
   Pad_0_2->SetTickx(1);
   Pad_0_2->SetTicky(1);
   Pad_0_2->SetLeftMargin(0);
   Pad_0_2->SetRightMargin(0);
   Pad_0_2->SetTopMargin(0);
   Pad_0_2->SetBottomMargin(0);
   
   TH2F *__14 = new TH2F("__14","",2,-0.05,2.86,2,-0.3,5.67);
   __14->SetStats(0);
   __14->SetFillColor(10);
   __14->SetFillStyle(0);
   __14->GetXaxis()->SetNdivisions(508);
   __14->GetXaxis()->SetLabelFont(42);
   __14->GetXaxis()->SetLabelOffset(0.02);
   __14->GetXaxis()->SetLabelSize(0.13);
   __14->GetXaxis()->SetTitleSize(0.05);
   __14->GetXaxis()->SetTitleOffset(1.2);
   __14->GetXaxis()->SetTitleFont(42);
   __14->GetYaxis()->SetNdivisions(505);
   __14->GetYaxis()->SetLabelFont(42);
   __14->GetYaxis()->SetLabelOffset(0.02);
   __14->GetYaxis()->SetLabelSize(0.13);
   __14->GetYaxis()->SetTitleSize(0.05);
   __14->GetYaxis()->SetTitleOffset(1.4);
   __14->GetYaxis()->SetTitleFont(42);
   __14->GetZaxis()->SetLabelFont(42);
   __14->GetZaxis()->SetLabelSize(0.035);
   __14->GetZaxis()->SetTitleSize(0.035);
   __14->GetZaxis()->SetTitleFont(42);
   __14->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(g)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.35,4.8195,"#font[42]{#scale[1.0]{30-40%}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_11GeV_Hadrons_systematic_fx1085[9] = {
   0.2946643,
   0.4908269,
   0.6902763,
   0.8900033,
   1.089768,
   1.289554,
   1.557343,
   1.955953,
   2.402404};
   Double_t data_v2_11GeV_Hadrons_systematic_fy1085[9] = {
   0.4214881,
   0.7058513,
   0.9875069,
   1.227691,
   1.477716,
   1.715834,
   2.022738,
   2.370907,
   2.632191};
   Double_t data_v2_11GeV_Hadrons_systematic_fex1085[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_11GeV_Hadrons_systematic_fey1085[9] = {
   0.003068264,
   0.003133205,
   0.001785257,
   0.001779554,
   0.004213059,
   0.01130359,
   0.004131558,
   0.004629989,
   0.01199532};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_systematic_fx1085,data_v2_11GeV_Hadrons_systematic_fy1085,data_v2_11GeV_Hadrons_systematic_fex1085,data_v2_11GeV_Hadrons_systematic_fey1085);
   gre->SetName("data_v2_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1221;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v2_11GeV_Hadrons_systematic1085 = new TH1F("Graph_data_v2_11GeV_Hadrons_systematic1085","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04789031,2.649178);
   Graph_data_v2_11GeV_Hadrons_systematic1085->SetMinimum(0.1958432);
   Graph_data_v2_11GeV_Hadrons_systematic1085->SetMaximum(2.866763);
   Graph_data_v2_11GeV_Hadrons_systematic1085->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons_systematic1085->SetStats(0);
   Graph_data_v2_11GeV_Hadrons_systematic1085->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons_systematic1085->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1085->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons_systematic1085);
   
   gre->Draw("e5");
   
   Double_t data_v2_14GeV_Hadrons_systematic_fx1086[9] = {
   0.2955169,
   0.4908725,
   0.6900725,
   0.8898255,
   1.08957,
   1.289482,
   1.557878,
   1.956563,
   2.404255};
   Double_t data_v2_14GeV_Hadrons_systematic_fy1086[9] = {
   0.4242043,
   0.7157597,
   0.9813312,
   1.240002,
   1.481976,
   1.709016,
   1.998746,
   2.34067,
   2.635693};
   Double_t data_v2_14GeV_Hadrons_systematic_fex1086[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_14GeV_Hadrons_systematic_fey1086[9] = {
   0.001187894,
   0.0007161413,
   0.001771604,
   0.0006985894,
   0.001925235,
   0.00812594,
   0.005761796,
   0.005621,
   0.01021217};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_systematic_fx1086,data_v2_14GeV_Hadrons_systematic_fy1086,data_v2_14GeV_Hadrons_systematic_fex1086,data_v2_14GeV_Hadrons_systematic_fey1086);
   gre->SetName("data_v2_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1222;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_14GeV_Hadrons_systematic1086 = new TH1F("Graph_data_v2_14GeV_Hadrons_systematic1086","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04864313,2.651129);
   Graph_data_v2_14GeV_Hadrons_systematic1086->SetMinimum(0.2007276);
   Graph_data_v2_14GeV_Hadrons_systematic1086->SetMaximum(2.868194);
   Graph_data_v2_14GeV_Hadrons_systematic1086->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons_systematic1086->SetStats(0);
   Graph_data_v2_14GeV_Hadrons_systematic1086->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons_systematic1086->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1086->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons_systematic1086);
   
   gre->Draw("e5");
   
   Double_t data_v2_19GeV_Hadrons_systematic_fx1087[9] = {
   0.2951085,
   0.4908633,
   0.6900587,
   0.8898548,
   1.089752,
   1.289696,
   1.558722,
   1.957935,
   2.408293};
   Double_t data_v2_19GeV_Hadrons_systematic_fy1087[9] = {
   0.3948144,
   0.706487,
   0.9861582,
   1.252896,
   1.499318,
   1.722265,
   1.993518,
   2.32175,
   2.605406};
   Double_t data_v2_19GeV_Hadrons_systematic_fex1087[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_19GeV_Hadrons_systematic_fey1087[9] = {
   0.001999138,
   0.001202151,
   0.002227848,
   0.005738704,
   0.002227681,
   0.002634105,
   0.007972399,
   0.006381471,
   0.02026862};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_systematic_fx1087,data_v2_19GeV_Hadrons_systematic_fy1087,data_v2_19GeV_Hadrons_systematic_fex1087,data_v2_19GeV_Hadrons_systematic_fey1087);
   gre->SetName("data_v2_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1223;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_19GeV_Hadrons_systematic1087 = new TH1F("Graph_data_v2_19GeV_Hadrons_systematic1087","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.0477901,2.655611);
   Graph_data_v2_19GeV_Hadrons_systematic1087->SetMinimum(0.1695293);
   Graph_data_v2_19GeV_Hadrons_systematic1087->SetMaximum(2.84896);
   Graph_data_v2_19GeV_Hadrons_systematic1087->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons_systematic1087->SetStats(0);
   Graph_data_v2_19GeV_Hadrons_systematic1087->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons_systematic1087->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1087->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons_systematic1087);
   
   gre->Draw("e5");
   
   Double_t data_v2_27GeV_Hadrons_systematic_fx1088[12] = {
   0.2953687,
   0.4910366,
   0.6902741,
   0.8900448,
   1.089885,
   1.28981,
   1.489842,
   1.689774,
   1.889701,
   2.15962,
   2.559864,
   2.960418};
   Double_t data_v2_27GeV_Hadrons_systematic_fy1088[12] = {
   0.3892546,
   0.6971172,
   0.9787784,
   1.236009,
   1.476694,
   1.702113,
   1.903066,
   2.079879,
   2.226991,
   2.377342,
   2.559176,
   2.671257};
   Double_t data_v2_27GeV_Hadrons_systematic_fex1088[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_27GeV_Hadrons_systematic_fey1088[12] = {
   0.002006486,
   0.001546534,
   0.0003168707,
   0.0006592729,
   0.0007942589,
   0.001035436,
   0.001770473,
   0.001297131,
   0.0006650531,
   0.001229615,
   0.004829969,
   0.007823157};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_systematic_fx1088,data_v2_27GeV_Hadrons_systematic_fy1088,data_v2_27GeV_Hadrons_systematic_fex1088,data_v2_27GeV_Hadrons_systematic_fey1088);
   gre->SetName("data_v2_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1224;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_27GeV_Hadrons_systematic1088 = new TH1F("Graph_data_v2_27GeV_Hadrons_systematic1088","#font[42]{#scale[1.3]{27 GeV}}",100,0,3.262923);
   Graph_data_v2_27GeV_Hadrons_systematic1088->SetMinimum(0.1580649);
   Graph_data_v2_27GeV_Hadrons_systematic1088->SetMaximum(2.908263);
   Graph_data_v2_27GeV_Hadrons_systematic1088->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons_systematic1088->SetStats(0);
   Graph_data_v2_27GeV_Hadrons_systematic1088->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons_systematic1088->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1088->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons_systematic1088);
   
   gre->Draw("e5");
   
   Double_t data_v2_39GeV_Hadrons_systematic_fx1089[12] = {
   0.2955851,
   0.4911354,
   0.6903541,
   0.8901448,
   1.090189,
   1.290255,
   1.490199,
   1.690165,
   1.890136,
   2.161552,
   2.56238,
   2.963044};
   Double_t data_v2_39GeV_Hadrons_systematic_fy1089[12] = {
   0.3729329,
   0.6860443,
   0.9704241,
   1.227112,
   1.463008,
   1.67794,
   1.870947,
   2.047384,
   2.172982,
   2.317522,
   2.487484,
   2.548422};
   Double_t data_v2_39GeV_Hadrons_systematic_fex1089[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_39GeV_Hadrons_systematic_fey1089[12] = {
   0.001914367,
   0.001276885,
   0.000407495,
   0.0006640852,
   0.001721149,
   0.0006614184,
   0.002208754,
   0.002550337,
   0.002282555,
   0.004503647,
   0.01239238,
   0.009344443};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_systematic_fx1089,data_v2_39GeV_Hadrons_systematic_fy1089,data_v2_39GeV_Hadrons_systematic_fex1089,data_v2_39GeV_Hadrons_systematic_fey1089);
   gre->SetName("data_v2_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1225;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_39GeV_Hadrons_systematic1089 = new TH1F("Graph_data_v2_39GeV_Hadrons_systematic1089","#font[42]{#scale[1.3]{39 GeV}}",100,0,3.26579);
   Graph_data_v2_39GeV_Hadrons_systematic1089->SetMinimum(0.1523438);
   Graph_data_v2_39GeV_Hadrons_systematic1089->SetMaximum(2.776441);
   Graph_data_v2_39GeV_Hadrons_systematic1089->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons_systematic1089->SetStats(0);
   Graph_data_v2_39GeV_Hadrons_systematic1089->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons_systematic1089->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1089->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons_systematic1089);
   
   gre->Draw("e5");
   
   Double_t data_v2_62GeV_Hadrons_systematic_fx1090[12] = {
   0.2958188,
   0.4913866,
   0.6906265,
   0.8904953,
   1.090565,
   1.29064,
   1.490647,
   1.690626,
   1.890641,
   2.163537,
   2.564395,
   2.966095};
   Double_t data_v2_62GeV_Hadrons_systematic_fy1090[12] = {
   0.3659814,
   0.6701949,
   0.9489423,
   1.201728,
   1.430432,
   1.638775,
   1.826612,
   1.984069,
   2.106788,
   2.249525,
   2.366245,
   2.379511};
   Double_t data_v2_62GeV_Hadrons_systematic_fex1090[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_62GeV_Hadrons_systematic_fey1090[12] = {
   0.001599976,
   0.0008814719,
   0.001339212,
   0.0004263119,
   0.0004029183,
   0.002388339,
   0.003136298,
   0.001380208,
   0.001467435,
   0.003185855,
   0.004692785,
   0.01584967};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_systematic_fx1090,data_v2_62GeV_Hadrons_systematic_fy1090,data_v2_62GeV_Hadrons_systematic_fex1090,data_v2_62GeV_Hadrons_systematic_fey1090);
   gre->SetName("data_v2_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1226;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_62GeV_Hadrons_systematic1090 = new TH1F("Graph_data_v2_62GeV_Hadrons_systematic1090","#font[42]{#scale[1.3]{62.4 GeV}}",100,0,3.269123);
   Graph_data_v2_62GeV_Hadrons_systematic1090->SetMinimum(0.1612835);
   Graph_data_v2_62GeV_Hadrons_systematic1090->SetMaximum(2.598458);
   Graph_data_v2_62GeV_Hadrons_systematic1090->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons_systematic1090->SetStats(0);
   Graph_data_v2_62GeV_Hadrons_systematic1090->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons_systematic1090->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1090->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons_systematic1090);
   
   gre->Draw("e5");
   
   Double_t data_v2_11GeV_Hadrons_fx1091[9] = {
   0.2946643,
   0.4908269,
   0.6902763,
   0.8900033,
   1.089768,
   1.289554,
   1.557343,
   1.955953,
   2.402404};
   Double_t data_v2_11GeV_Hadrons_fy1091[9] = {
   0.4214881,
   0.7058513,
   0.9875069,
   1.227691,
   1.477716,
   1.715834,
   2.022738,
   2.370907,
   2.632191};
   Double_t data_v2_11GeV_Hadrons_fex1091[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_11GeV_Hadrons_fey1091[9] = {
   0.006787051,
   0.006879317,
   0.007932814,
   0.009473198,
   0.01159445,
   0.01437871,
   0.01497543,
   0.02489535,
   0.0437679};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_fx1091,data_v2_11GeV_Hadrons_fy1091,data_v2_11GeV_Hadrons_fex1091,data_v2_11GeV_Hadrons_fey1091);
   gre->SetName("data_v2_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_11GeV_Hadrons1091 = new TH1F("Graph_data_v2_11GeV_Hadrons1091","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08389031,2.613178);
   Graph_data_v2_11GeV_Hadrons1091->SetMinimum(0.1885752);
   Graph_data_v2_11GeV_Hadrons1091->SetMaximum(2.902085);
   Graph_data_v2_11GeV_Hadrons1091->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons1091->SetStats(0);
   Graph_data_v2_11GeV_Hadrons1091->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons1091->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons1091->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons1091->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1091->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1091->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons1091->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons1091->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons1091);
   
   gre->Draw("p");
   
   Double_t data_v2_14GeV_Hadrons_fx1092[9] = {
   0.2955169,
   0.4908725,
   0.6900725,
   0.8898255,
   1.08957,
   1.289482,
   1.557878,
   1.956563,
   2.404255};
   Double_t data_v2_14GeV_Hadrons_fy1092[9] = {
   0.4242043,
   0.7157597,
   0.9813312,
   1.240002,
   1.481976,
   1.709016,
   1.998746,
   2.34067,
   2.635693};
   Double_t data_v2_14GeV_Hadrons_fex1092[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_14GeV_Hadrons_fey1092[9] = {
   0.003665044,
   0.003679334,
   0.004247795,
   0.005111593,
   0.006274169,
   0.007786788,
   0.008076437,
   0.01334903,
   0.02311725};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_fx1092,data_v2_14GeV_Hadrons_fy1092,data_v2_14GeV_Hadrons_fex1092,data_v2_14GeV_Hadrons_fey1092);
   gre->SetName("data_v2_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_14GeV_Hadrons1092 = new TH1F("Graph_data_v2_14GeV_Hadrons1092","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08464313,2.615129);
   Graph_data_v2_14GeV_Hadrons1092->SetMinimum(0.1967122);
   Graph_data_v2_14GeV_Hadrons1092->SetMaximum(2.882637);
   Graph_data_v2_14GeV_Hadrons1092->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons1092->SetStats(0);
   Graph_data_v2_14GeV_Hadrons1092->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons1092->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons1092->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons1092->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1092->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1092->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons1092->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons1092->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons1092);
   
   gre->Draw("p");
   
   Double_t data_v2_19GeV_Hadrons_fx1093[9] = {
   0.2951085,
   0.4908633,
   0.6900587,
   0.8898548,
   1.089752,
   1.289696,
   1.558722,
   1.957935,
   2.408293};
   Double_t data_v2_19GeV_Hadrons_fy1093[9] = {
   0.3948144,
   0.706487,
   0.9861582,
   1.252896,
   1.499318,
   1.722265,
   1.993518,
   2.32175,
   2.605406};
   Double_t data_v2_19GeV_Hadrons_fex1093[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_19GeV_Hadrons_fey1093[9] = {
   0.003049608,
   0.003077551,
   0.003558788,
   0.004283481,
   0.005244163,
   0.006483856,
   0.006667472,
   0.01082623,
   0.01825275};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_fx1093,data_v2_19GeV_Hadrons_fy1093,data_v2_19GeV_Hadrons_fex1093,data_v2_19GeV_Hadrons_fey1093);
   gre->SetName("data_v2_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_19GeV_Hadrons1093 = new TH1F("Graph_data_v2_19GeV_Hadrons1093","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.0837901,2.619611);
   Graph_data_v2_19GeV_Hadrons1093->SetMinimum(0.1685754);
   Graph_data_v2_19GeV_Hadrons1093->SetMaximum(2.846848);
   Graph_data_v2_19GeV_Hadrons1093->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons1093->SetStats(0);
   Graph_data_v2_19GeV_Hadrons1093->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons1093->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons1093->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons1093->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1093->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1093->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons1093->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons1093->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons1093);
   
   gre->Draw("p");
   
   Double_t data_v2_27GeV_Hadrons_fx1094[12] = {
   0.2953687,
   0.4910366,
   0.6902741,
   0.8900448,
   1.089885,
   1.28981,
   1.489842,
   1.689774,
   1.889701,
   2.15962,
   2.559864,
   2.960418};
   Double_t data_v2_27GeV_Hadrons_fy1094[12] = {
   0.3892546,
   0.6971172,
   0.9787784,
   1.236009,
   1.476694,
   1.702113,
   1.903066,
   2.079879,
   2.226991,
   2.377342,
   2.559176,
   2.671257};
   Double_t data_v2_27GeV_Hadrons_fex1094[12] = {
   0,
   0,
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
   Double_t data_v2_27GeV_Hadrons_fey1094[12] = {
   0.0006423096,
   0.0006431431,
   0.0007404776,
   0.0008867042,
   0.001079195,
   0.001331715,
   0.001656603,
   0.002081998,
   0.002645826,
   0.002827529,
   0.005144734,
   0.009429847};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_fx1094,data_v2_27GeV_Hadrons_fy1094,data_v2_27GeV_Hadrons_fex1094,data_v2_27GeV_Hadrons_fey1094);
   gre->SetName("data_v2_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_27GeV_Hadrons1094 = new TH1F("Graph_data_v2_27GeV_Hadrons1094","#font[42]{#scale[1.3]{27 GeV}}",100,0.02886384,3.226923);
   Graph_data_v2_27GeV_Hadrons1094->SetMinimum(0.1594048);
   Graph_data_v2_27GeV_Hadrons1094->SetMaximum(2.909894);
   Graph_data_v2_27GeV_Hadrons1094->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons1094->SetStats(0);
   Graph_data_v2_27GeV_Hadrons1094->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons1094->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons1094->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons1094->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1094->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1094->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons1094->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons1094->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons1094);
   
   gre->Draw("p");
   
   Double_t data_v2_39GeV_Hadrons_fx1095[12] = {
   0.2955851,
   0.4911354,
   0.6903541,
   0.8901448,
   1.090189,
   1.290255,
   1.490199,
   1.690165,
   1.890136,
   2.161552,
   2.56238,
   2.963044};
   Double_t data_v2_39GeV_Hadrons_fy1095[12] = {
   0.3729329,
   0.6860443,
   0.9704241,
   1.227112,
   1.463008,
   1.67794,
   1.870947,
   2.047384,
   2.172982,
   2.317522,
   2.487484,
   2.548422};
   Double_t data_v2_39GeV_Hadrons_fex1095[12] = {
   0,
   0,
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
   Double_t data_v2_39GeV_Hadrons_fey1095[12] = {
   0.001151794,
   0.00114828,
   0.001318556,
   0.001573435,
   0.001907333,
   0.002326134,
   0.002862802,
   0.003560638,
   0.004466555,
   0.004687815,
   0.008229559,
   0.01446244};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_fx1095,data_v2_39GeV_Hadrons_fy1095,data_v2_39GeV_Hadrons_fex1095,data_v2_39GeV_Hadrons_fey1095);
   gre->SetName("data_v2_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_39GeV_Hadrons1095 = new TH1F("Graph_data_v2_39GeV_Hadrons1095","#font[42]{#scale[1.3]{39 GeV}}",100,0.02883919,3.22979);
   Graph_data_v2_39GeV_Hadrons1095->SetMinimum(0.1526708);
   Graph_data_v2_39GeV_Hadrons1095->SetMaximum(2.781995);
   Graph_data_v2_39GeV_Hadrons1095->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons1095->SetStats(0);
   Graph_data_v2_39GeV_Hadrons1095->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons1095->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons1095->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons1095->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1095->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1095->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons1095->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons1095->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons1095);
   
   gre->Draw("p");
   
   Double_t data_v2_62GeV_Hadrons_fx1096[12] = {
   0.2958188,
   0.4913866,
   0.6906265,
   0.8904953,
   1.090565,
   1.29064,
   1.490647,
   1.690626,
   1.890641,
   2.163537,
   2.564395,
   2.966095};
   Double_t data_v2_62GeV_Hadrons_fy1096[12] = {
   0.3659814,
   0.6701949,
   0.9489423,
   1.201728,
   1.430432,
   1.638775,
   1.826612,
   1.984069,
   2.106788,
   2.249525,
   2.366245,
   2.379511};
   Double_t data_v2_62GeV_Hadrons_fex1096[12] = {
   0,
   0,
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
   Double_t data_v2_62GeV_Hadrons_fey1096[12] = {
   0.001458454,
   0.001440161,
   0.001639356,
   0.001940288,
   0.002330224,
   0.002814502,
   0.003425567,
   0.004204307,
   0.005200474,
   0.005351516,
   0.00906252,
   0.01531554};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_fx1096,data_v2_62GeV_Hadrons_fy1096,data_v2_62GeV_Hadrons_fex1096,data_v2_62GeV_Hadrons_fey1096);
   gre->SetName("data_v2_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_62GeV_Hadrons1096 = new TH1F("Graph_data_v2_62GeV_Hadrons1096","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.02879112,3.233123);
   Graph_data_v2_62GeV_Hadrons1096->SetMinimum(0.1614926);
   Graph_data_v2_62GeV_Hadrons1096->SetMaximum(2.597857);
   Graph_data_v2_62GeV_Hadrons1096->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons1096->SetStats(0);
   Graph_data_v2_62GeV_Hadrons1096->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons1096->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons1096->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons1096->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1096->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1096->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons1096->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons1096->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons1096);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_0_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_2
   TPad *Pad_1_2 = new TPad("Pad_1_2", "",0.525,0.276,0.9,0.452);
   Pad_1_2->Draw();
   Pad_1_2->cd();
   Pad_1_2->Range(-0.05,-0.3,2.86,5.67);
   Pad_1_2->SetFillColor(0);
   Pad_1_2->SetBorderMode(0);
   Pad_1_2->SetBorderSize(0);
   Pad_1_2->SetTickx(1);
   Pad_1_2->SetTicky(1);
   Pad_1_2->SetLeftMargin(0);
   Pad_1_2->SetRightMargin(0);
   Pad_1_2->SetTopMargin(0);
   Pad_1_2->SetBottomMargin(0);
   
   TH2F *__15 = new TH2F("__15","",2,-0.05,2.86,2,-0.3,5.67);
   __15->SetStats(0);
   __15->SetFillColor(10);
   __15->SetFillStyle(0);
   __15->GetXaxis()->SetNdivisions(508);
   __15->GetXaxis()->SetLabelFont(42);
   __15->GetXaxis()->SetLabelOffset(0.02);
   __15->GetXaxis()->SetLabelSize(0.13);
   __15->GetXaxis()->SetTitleSize(0.05);
   __15->GetXaxis()->SetTitleOffset(1.2);
   __15->GetXaxis()->SetTitleFont(42);
   __15->GetYaxis()->SetNdivisions(505);
   __15->GetYaxis()->SetLabelFont(42);
   __15->GetYaxis()->SetLabelOffset(0.02);
   __15->GetYaxis()->SetLabelSize(0.13);
   __15->GetYaxis()->SetTitleSize(0.05);
   __15->GetYaxis()->SetTitleOffset(1.4);
   __15->GetYaxis()->SetTitleFont(42);
   __15->GetZaxis()->SetLabelFont(42);
   __15->GetZaxis()->SetLabelSize(0.035);
   __15->GetZaxis()->SetTitleSize(0.035);
   __15->GetZaxis()->SetTitleFont(42);
   __15->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(h)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v3_11GeV_Hadrons_systematic_fx1097[7] = {
   0.2946643,
   0.4908269,
   0.6902763,
   0.9601641,
   1.358414,
   1.805072,
   2.402404};
   Double_t data_v3_11GeV_Hadrons_systematic_fy1097[7] = {
   0.2211433,
   0.5297416,
   1.038079,
   1.41037,
   2.133404,
   2.956276,
   2.784972};
   Double_t data_v3_11GeV_Hadrons_systematic_fex1097[7] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_11GeV_Hadrons_systematic_fey1097[7] = {
   0.05227828,
   0.0455154,
   0.04371088,
   0.03798694,
   0.05764822,
   0.2672339,
   0.6607102};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_systematic_fx1097,data_v3_11GeV_Hadrons_systematic_fy1097,data_v3_11GeV_Hadrons_systematic_fex1097,data_v3_11GeV_Hadrons_systematic_fey1097);
   gre->SetName("data_v3_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1227;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v3_11GeV_Hadrons_systematic1097 = new TH1F("Graph_data_v3_11GeV_Hadrons_systematic1097","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04789031,2.649178);
   Graph_data_v3_11GeV_Hadrons_systematic1097->SetMinimum(0.1519785);
   Graph_data_v3_11GeV_Hadrons_systematic1097->SetMaximum(3.773364);
   Graph_data_v3_11GeV_Hadrons_systematic1097->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons_systematic1097->SetStats(0);
   Graph_data_v3_11GeV_Hadrons_systematic1097->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons_systematic1097->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1097->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons_systematic1097);
   
   gre->Draw("e5");
   
   Double_t data_v3_14GeV_Hadrons_systematic_fx1098[8] = {
   0.2955169,
   0.4908725,
   0.6900725,
   0.8898255,
   1.159148,
   1.557878,
   1.956563,
   2.404255};
   Double_t data_v3_14GeV_Hadrons_systematic_fy1098[8] = {
   0.2195364,
   0.5447091,
   0.872477,
   1.179537,
   1.937933,
   2.530993,
   3.51069,
   4.670696};
   Double_t data_v3_14GeV_Hadrons_systematic_fex1098[8] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_14GeV_Hadrons_systematic_fey1098[8] = {
   0.04325064,
   0.007875256,
   0.01627737,
   0.05190297,
   0.04452301,
   0.0770549,
   0.2076174,
   0.3163916};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_systematic_fx1098,data_v3_14GeV_Hadrons_systematic_fy1098,data_v3_14GeV_Hadrons_systematic_fex1098,data_v3_14GeV_Hadrons_systematic_fey1098);
   gre->SetName("data_v3_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1228;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_14GeV_Hadrons_systematic1098 = new TH1F("Graph_data_v3_14GeV_Hadrons_systematic1098","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04864313,2.651129);
   Graph_data_v3_14GeV_Hadrons_systematic1098->SetMinimum(0.1586572);
   Graph_data_v3_14GeV_Hadrons_systematic1098->SetMaximum(5.468168);
   Graph_data_v3_14GeV_Hadrons_systematic1098->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons_systematic1098->SetStats(0);
   Graph_data_v3_14GeV_Hadrons_systematic1098->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons_systematic1098->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1098->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons_systematic1098);
   
   gre->Draw("e5");
   
   Double_t data_v3_19GeV_Hadrons_systematic_fx1099[9] = {
   0.2951085,
   0.4908633,
   0.6900587,
   0.8898548,
   1.089752,
   1.359274,
   1.758199,
   2.157641,
   2.608211};
   Double_t data_v3_19GeV_Hadrons_systematic_fy1099[9] = {
   0.2229132,
   0.4734464,
   0.9395173,
   1.242927,
   1.732839,
   2.1928,
   3.045981,
   3.86884,
   4.236169};
   Double_t data_v3_19GeV_Hadrons_systematic_fex1099[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_19GeV_Hadrons_systematic_fey1099[9] = {
   0.01037053,
   0.01831932,
   0.0142773,
   0.01465035,
   0.03809187,
   0.05410682,
   0.05988627,
   0.1313858,
   0.3993076};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_systematic_fx1099,data_v3_19GeV_Hadrons_systematic_fy1099,data_v3_19GeV_Hadrons_systematic_fex1099,data_v3_19GeV_Hadrons_systematic_fey1099);
   gre->SetName("data_v3_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1229;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_19GeV_Hadrons_systematic1099 = new TH1F("Graph_data_v3_19GeV_Hadrons_systematic1099","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.02779826,2.875521);
   Graph_data_v3_19GeV_Hadrons_systematic1099->SetMinimum(0.1912884);
   Graph_data_v3_19GeV_Hadrons_systematic1099->SetMaximum(5.07777);
   Graph_data_v3_19GeV_Hadrons_systematic1099->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons_systematic1099->SetStats(0);
   Graph_data_v3_19GeV_Hadrons_systematic1099->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons_systematic1099->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1099->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons_systematic1099);
   
   gre->Draw("e5");
   
   Double_t data_v3_27GeV_Hadrons_systematic_fx1100[11] = {
   0.2953687,
   0.4910366,
   0.6902741,
   0.8900448,
   1.089885,
   1.28981,
   1.489842,
   1.689774,
   1.889701,
   2.15962,
   2.559864};
   Double_t data_v3_27GeV_Hadrons_systematic_fy1100[11] = {
   0.1911221,
   0.504121,
   0.8852109,
   1.266706,
   1.666908,
   2.06954,
   2.446209,
   2.849673,
   3.004076,
   3.418404,
   3.871254};
   Double_t data_v3_27GeV_Hadrons_systematic_fex1100[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_27GeV_Hadrons_systematic_fey1100[11] = {
   0.01043908,
   0.01418838,
   0.006640746,
   0.004697241,
   0.007267268,
   0.01553599,
   0.03015778,
   0.05756868,
   0.05391041,
   0.05698538,
   0.05648145};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_systematic_fx1100,data_v3_27GeV_Hadrons_systematic_fy1100,data_v3_27GeV_Hadrons_systematic_fex1100,data_v3_27GeV_Hadrons_systematic_fey1100);
   gre->SetName("data_v3_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1230;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_27GeV_Hadrons_systematic1100 = new TH1F("Graph_data_v3_27GeV_Hadrons_systematic1100","#font[42]{#scale[1.3]{27 GeV}}",100,0.03291917,2.822314);
   Graph_data_v3_27GeV_Hadrons_systematic1100->SetMinimum(0.1626147);
   Graph_data_v3_27GeV_Hadrons_systematic1100->SetMaximum(4.302441);
   Graph_data_v3_27GeV_Hadrons_systematic1100->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons_systematic1100->SetStats(0);
   Graph_data_v3_27GeV_Hadrons_systematic1100->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons_systematic1100->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1100->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons_systematic1100);
   
   gre->Draw("e5");
   
   Double_t data_v3_39GeV_Hadrons_systematic_fx1101[11] = {
   0.2955851,
   0.4911354,
   0.6903541,
   0.8901448,
   1.090189,
   1.290255,
   1.490199,
   1.690165,
   1.890136,
   2.161552,
   2.56238};
   Double_t data_v3_39GeV_Hadrons_systematic_fy1101[11] = {
   0.1932855,
   0.5106025,
   0.8386035,
   1.242231,
   1.683663,
   1.991972,
   2.316262,
   2.734624,
   2.893969,
   3.296931,
   3.600746};
   Double_t data_v3_39GeV_Hadrons_systematic_fex1101[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_39GeV_Hadrons_systematic_fey1101[11] = {
   0.005677752,
   0.01465118,
   0.005312107,
   0.004349277,
   0.01044843,
   0.01718807,
   0.03471964,
   0.04387779,
   0.02720047,
   0.07353587,
   0.07814452};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_systematic_fx1101,data_v3_39GeV_Hadrons_systematic_fy1101,data_v3_39GeV_Hadrons_systematic_fex1101,data_v3_39GeV_Hadrons_systematic_fey1101);
   gre->SetName("data_v3_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1231;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_39GeV_Hadrons_systematic1101 = new TH1F("Graph_data_v3_39GeV_Hadrons_systematic1101","#font[42]{#scale[1.3]{39 GeV}}",100,0.03290558,2.82506);
   Graph_data_v3_39GeV_Hadrons_systematic1101->SetMinimum(0.168847);
   Graph_data_v3_39GeV_Hadrons_systematic1101->SetMaximum(4.028019);
   Graph_data_v3_39GeV_Hadrons_systematic1101->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons_systematic1101->SetStats(0);
   Graph_data_v3_39GeV_Hadrons_systematic1101->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons_systematic1101->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1101->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons_systematic1101);
   
   gre->Draw("e5");
   
   Double_t data_v3_62GeV_Hadrons_systematic_fx1102[11] = {
   0.2958188,
   0.4913866,
   0.6906265,
   0.8904953,
   1.090565,
   1.29064,
   1.490647,
   1.690626,
   1.890641,
   2.163537,
   2.564395};
   Double_t data_v3_62GeV_Hadrons_systematic_fy1102[11] = {
   0.1637496,
   0.4948196,
   0.8644524,
   1.196842,
   1.568248,
   1.951323,
   2.213363,
   2.616707,
   2.774628,
   3.108421,
   3.413033};
   Double_t data_v3_62GeV_Hadrons_systematic_fex1102[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_62GeV_Hadrons_systematic_fey1102[11] = {
   0.006755559,
   0.0158671,
   0.009837725,
   0.00944971,
   0.007651277,
   0.01193192,
   0.03580272,
   0.01634369,
   0.02291147,
   0.04955491,
   0.1017327};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_systematic_fx1102,data_v3_62GeV_Hadrons_systematic_fy1102,data_v3_62GeV_Hadrons_systematic_fex1102,data_v3_62GeV_Hadrons_systematic_fey1102);
   gre->SetName("data_v3_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1232;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_62GeV_Hadrons_systematic1102 = new TH1F("Graph_data_v3_62GeV_Hadrons_systematic1102","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.03296112,2.827253);
   Graph_data_v3_62GeV_Hadrons_systematic1102->SetMinimum(0.1412946);
   Graph_data_v3_62GeV_Hadrons_systematic1102->SetMaximum(3.850543);
   Graph_data_v3_62GeV_Hadrons_systematic1102->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons_systematic1102->SetStats(0);
   Graph_data_v3_62GeV_Hadrons_systematic1102->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons_systematic1102->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1102->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons_systematic1102);
   
   gre->Draw("e5");
   
   Double_t data_v3_11GeV_Hadrons_fx1103[7] = {
   0.2946643,
   0.4908269,
   0.6902763,
   0.9601641,
   1.358414,
   1.805072,
   2.402404};
   Double_t data_v3_11GeV_Hadrons_fy1103[7] = {
   0.2211433,
   0.5297416,
   1.038079,
   1.41037,
   2.133404,
   2.956276,
   2.784972};
   Double_t data_v3_11GeV_Hadrons_fex1103[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_11GeV_Hadrons_fey1103[7] = {
   0.1230849,
   0.1236152,
   0.147161,
   0.1480579,
   0.229687,
   0.3451115,
   0.8100355};
   gre = new TGraphErrors(7,data_v3_11GeV_Hadrons_fx1103,data_v3_11GeV_Hadrons_fy1103,data_v3_11GeV_Hadrons_fex1103,data_v3_11GeV_Hadrons_fey1103);
   gre->SetName("data_v3_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_11GeV_Hadrons1103 = new TH1F("Graph_data_v3_11GeV_Hadrons1103","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08389031,2.613178);
   Graph_data_v3_11GeV_Hadrons1103->SetMinimum(0.08825256);
   Graph_data_v3_11GeV_Hadrons1103->SetMaximum(3.944702);
   Graph_data_v3_11GeV_Hadrons1103->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons1103->SetStats(0);
   Graph_data_v3_11GeV_Hadrons1103->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons1103->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons1103->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons1103->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1103->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1103->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons1103->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons1103->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons1103);
   
   gre->Draw("p");
   
   Double_t data_v3_14GeV_Hadrons_fx1104[8] = {
   0.2955169,
   0.4908725,
   0.6900725,
   0.8898255,
   1.159148,
   1.557878,
   1.956563,
   2.404255};
   Double_t data_v3_14GeV_Hadrons_fy1104[8] = {
   0.2195364,
   0.5447091,
   0.872477,
   1.179537,
   1.937933,
   2.530993,
   3.51069,
   4.670696};
   Double_t data_v3_14GeV_Hadrons_fex1104[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_14GeV_Hadrons_fey1104[8] = {
   0.05955938,
   0.05926755,
   0.06892708,
   0.08365283,
   0.09195084,
   0.1403217,
   0.2324996,
   0.3973121};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_fx1104,data_v3_14GeV_Hadrons_fy1104,data_v3_14GeV_Hadrons_fex1104,data_v3_14GeV_Hadrons_fey1104);
   gre->SetName("data_v3_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_14GeV_Hadrons1104 = new TH1F("Graph_data_v3_14GeV_Hadrons1104","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08464313,2.615129);
   Graph_data_v3_14GeV_Hadrons1104->SetMinimum(0.1439793);
   Graph_data_v3_14GeV_Hadrons1104->SetMaximum(5.558812);
   Graph_data_v3_14GeV_Hadrons1104->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons1104->SetStats(0);
   Graph_data_v3_14GeV_Hadrons1104->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons1104->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons1104->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons1104->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1104->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1104->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons1104->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons1104->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons1104);
   
   gre->Draw("p");
   
   Double_t data_v3_19GeV_Hadrons_fx1105[9] = {
   0.2951085,
   0.4908633,
   0.6900587,
   0.8898548,
   1.089752,
   1.359274,
   1.758199,
   2.157641,
   2.608211};
   Double_t data_v3_19GeV_Hadrons_fy1105[9] = {
   0.2229132,
   0.4734464,
   0.9395173,
   1.242927,
   1.732839,
   2.1928,
   3.045981,
   3.86884,
   4.236169};
   Double_t data_v3_19GeV_Hadrons_fex1105[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_19GeV_Hadrons_fey1105[9] = {
   0.04653704,
   0.04612393,
   0.05457872,
   0.0660993,
   0.08326688,
   0.08741819,
   0.1383097,
   0.2331834,
   0.3946084};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_fx1105,data_v3_19GeV_Hadrons_fy1105,data_v3_19GeV_Hadrons_fex1105,data_v3_19GeV_Hadrons_fey1105);
   gre->SetName("data_v3_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_19GeV_Hadrons1105 = new TH1F("Graph_data_v3_19GeV_Hadrons1105","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.06379826,2.839521);
   Graph_data_v3_19GeV_Hadrons1105->SetMinimum(0.1587386);
   Graph_data_v3_19GeV_Hadrons1105->SetMaximum(5.076217);
   Graph_data_v3_19GeV_Hadrons1105->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons1105->SetStats(0);
   Graph_data_v3_19GeV_Hadrons1105->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons1105->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons1105->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons1105->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1105->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1105->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons1105->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons1105->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons1105);
   
   gre->Draw("p");
   
   Double_t data_v3_27GeV_Hadrons_fx1106[11] = {
   0.2953687,
   0.4910366,
   0.6902741,
   0.8900448,
   1.089885,
   1.28981,
   1.489842,
   1.689774,
   1.889701,
   2.15962,
   2.559864};
   Double_t data_v3_27GeV_Hadrons_fy1106[11] = {
   0.1911221,
   0.504121,
   0.8852109,
   1.266706,
   1.666908,
   2.06954,
   2.446209,
   2.849673,
   3.004076,
   3.418404,
   3.871254};
   Double_t data_v3_27GeV_Hadrons_fex1106[11] = {
   0,
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
   Double_t data_v3_27GeV_Hadrons_fey1106[11] = {
   0.008867025,
   0.008769543,
   0.01021173,
   0.01245885,
   0.01543982,
   0.01927262,
   0.02406732,
   0.03028633,
   0.03805952,
   0.04098364,
   0.07332016};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_fx1106,data_v3_27GeV_Hadrons_fy1106,data_v3_27GeV_Hadrons_fex1106,data_v3_27GeV_Hadrons_fey1106);
   gre->SetName("data_v3_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_27GeV_Hadrons1106 = new TH1F("Graph_data_v3_27GeV_Hadrons1106","#font[42]{#scale[1.3]{27 GeV}}",100,0.06891917,2.786314);
   Graph_data_v3_27GeV_Hadrons1106->SetMinimum(0.1640296);
   Graph_data_v3_27GeV_Hadrons1106->SetMaximum(4.320806);
   Graph_data_v3_27GeV_Hadrons1106->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons1106->SetStats(0);
   Graph_data_v3_27GeV_Hadrons1106->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons1106->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons1106->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons1106->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1106->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1106->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons1106->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons1106->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons1106);
   
   gre->Draw("p");
   
   Double_t data_v3_39GeV_Hadrons_fx1107[11] = {
   0.2955851,
   0.4911354,
   0.6903541,
   0.8901448,
   1.090189,
   1.290255,
   1.490199,
   1.690165,
   1.890136,
   2.161552,
   2.56238};
   Double_t data_v3_39GeV_Hadrons_fy1107[11] = {
   0.1932855,
   0.5106025,
   0.8386035,
   1.242231,
   1.683663,
   1.991972,
   2.316262,
   2.734624,
   2.893969,
   3.296931,
   3.600746};
   Double_t data_v3_39GeV_Hadrons_fex1107[11] = {
   0,
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
   Double_t data_v3_39GeV_Hadrons_fey1107[11] = {
   0.01414407,
   0.01394352,
   0.01607003,
   0.01959753,
   0.02433016,
   0.02978085,
   0.03673922,
   0.04591776,
   0.0570904,
   0.0604596,
   0.1041945};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_fx1107,data_v3_39GeV_Hadrons_fy1107,data_v3_39GeV_Hadrons_fex1107,data_v3_39GeV_Hadrons_fey1107);
   gre->SetName("data_v3_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_39GeV_Hadrons1107 = new TH1F("Graph_data_v3_39GeV_Hadrons1107","#font[42]{#scale[1.3]{39 GeV}}",100,0.06890558,2.78906);
   Graph_data_v3_39GeV_Hadrons1107->SetMinimum(0.1612273);
   Graph_data_v3_39GeV_Hadrons1107->SetMaximum(4.057521);
   Graph_data_v3_39GeV_Hadrons1107->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons1107->SetStats(0);
   Graph_data_v3_39GeV_Hadrons1107->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons1107->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons1107->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons1107->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1107->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1107->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons1107->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons1107->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons1107);
   
   gre->Draw("p");
   
   Double_t data_v3_62GeV_Hadrons_fx1108[11] = {
   0.2958188,
   0.4913866,
   0.6906265,
   0.8904953,
   1.090565,
   1.29064,
   1.490647,
   1.690626,
   1.890641,
   2.163537,
   2.564395};
   Double_t data_v3_62GeV_Hadrons_fy1108[11] = {
   0.1637496,
   0.4948196,
   0.8644524,
   1.196842,
   1.568248,
   1.951323,
   2.213363,
   2.616707,
   2.774628,
   3.108421,
   3.413033};
   Double_t data_v3_62GeV_Hadrons_fex1108[11] = {
   0,
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
   Double_t data_v3_62GeV_Hadrons_fey1108[11] = {
   0.01593113,
   0.0155748,
   0.01790099,
   0.02144544,
   0.02620193,
   0.03208981,
   0.03903015,
   0.04823148,
   0.05918707,
   0.06145955,
   0.1023693};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_fx1108,data_v3_62GeV_Hadrons_fy1108,data_v3_62GeV_Hadrons_fex1108,data_v3_62GeV_Hadrons_fey1108);
   gre->SetName("data_v3_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_62GeV_Hadrons1108 = new TH1F("Graph_data_v3_62GeV_Hadrons1108","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.06896112,2.791253);
   Graph_data_v3_62GeV_Hadrons1108->SetMinimum(0.1330366);
   Graph_data_v3_62GeV_Hadrons1108->SetMaximum(3.852161);
   Graph_data_v3_62GeV_Hadrons1108->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons1108->SetStats(0);
   Graph_data_v3_62GeV_Hadrons1108->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons1108->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons1108->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons1108->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1108->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1108->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons1108->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons1108->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons1108);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_1_2->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_0_1
   TPad *Pad_0_1 = new TPad("Pad_0_1", "",0.15,0.1,0.525,0.276);
   Pad_0_1->Draw();
   Pad_0_1->cd();
   Pad_0_1->Range(-0.05,-0.3,2.86,5.67);
   Pad_0_1->SetFillColor(0);
   Pad_0_1->SetBorderMode(0);
   Pad_0_1->SetBorderSize(0);
   Pad_0_1->SetTickx(1);
   Pad_0_1->SetTicky(1);
   Pad_0_1->SetLeftMargin(0);
   Pad_0_1->SetRightMargin(0);
   Pad_0_1->SetTopMargin(0);
   Pad_0_1->SetBottomMargin(0);
   
   TH2F *__16 = new TH2F("__16","",2,-0.05,2.86,2,-0.3,5.67);
   __16->SetStats(0);
   __16->SetFillColor(10);
   __16->SetFillStyle(0);
   __16->GetXaxis()->SetNdivisions(508);
   __16->GetXaxis()->SetLabelFont(42);
   __16->GetXaxis()->SetLabelOffset(0.02);
   __16->GetXaxis()->SetLabelSize(0.13);
   __16->GetXaxis()->SetTitleSize(0.05);
   __16->GetXaxis()->SetTitleOffset(1.2);
   __16->GetXaxis()->SetTitleFont(42);
   __16->GetYaxis()->SetNdivisions(505);
   __16->GetYaxis()->SetLabelFont(42);
   __16->GetYaxis()->SetLabelOffset(0.02);
   __16->GetYaxis()->SetLabelSize(0.13);
   __16->GetYaxis()->SetTitleSize(0.05);
   __16->GetYaxis()->SetTitleOffset(1.4);
   __16->GetYaxis()->SetTitleFont(42);
   __16->GetZaxis()->SetLabelFont(42);
   __16->GetZaxis()->SetLabelSize(0.035);
   __16->GetZaxis()->SetTitleSize(0.035);
   __16->GetZaxis()->SetTitleFont(42);
   __16->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(i)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.35,4.8195,"#font[42]{#scale[1.0]{40-60%}}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v2_11GeV_Hadrons_systematic_fx1109[9] = {
   0.2943644,
   0.4903465,
   0.6896691,
   0.8892842,
   1.089061,
   1.288873,
   1.555258,
   1.953761,
   2.398675};
   Double_t data_v2_11GeV_Hadrons_systematic_fy1109[9] = {
   0.420019,
   0.7420187,
   1.018547,
   1.311564,
   1.536878,
   1.755701,
   2.053668,
   2.447613,
   2.832107};
   Double_t data_v2_11GeV_Hadrons_systematic_fex1109[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_11GeV_Hadrons_systematic_fey1109[9] = {
   0.003881962,
   0.002358566,
   0.002393498,
   0.004289748,
   0.007039169,
   0.008428436,
   0.01148042,
   0.03441053,
   0.03854668};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_systematic_fx1109,data_v2_11GeV_Hadrons_systematic_fy1109,data_v2_11GeV_Hadrons_systematic_fex1109,data_v2_11GeV_Hadrons_systematic_fey1109);
   gre->SetName("data_v2_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1233;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v2_11GeV_Hadrons_systematic1109 = new TH1F("Graph_data_v2_11GeV_Hadrons_systematic1109","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.04793332,2.645106);
   Graph_data_v2_11GeV_Hadrons_systematic1109->SetMinimum(0.1706853);
   Graph_data_v2_11GeV_Hadrons_systematic1109->SetMaximum(3.116106);
   Graph_data_v2_11GeV_Hadrons_systematic1109->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons_systematic1109->SetStats(0);
   Graph_data_v2_11GeV_Hadrons_systematic1109->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons_systematic1109->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons_systematic1109->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons_systematic1109);
   
   gre->Draw("e5");
   
   Double_t data_v2_14GeV_Hadrons_systematic_fx1110[9] = {
   0.2951874,
   0.4904256,
   0.6894746,
   0.8892084,
   1.088917,
   1.288969,
   1.555972,
   1.954997,
   2.401489};
   Double_t data_v2_14GeV_Hadrons_systematic_fy1110[9] = {
   0.4278005,
   0.7395286,
   1.022987,
   1.295237,
   1.533133,
   1.778765,
   2.041839,
   2.382886,
   2.698323};
   Double_t data_v2_14GeV_Hadrons_systematic_fex1110[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_14GeV_Hadrons_systematic_fey1110[9] = {
   0.001933853,
   0.003438532,
   0.002426568,
   0.005455842,
   0.004980245,
   0.003421341,
   0.00856782,
   0.0193797,
   0.008963285};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_systematic_fx1110,data_v2_14GeV_Hadrons_systematic_fy1110,data_v2_14GeV_Hadrons_systematic_fex1110,data_v2_14GeV_Hadrons_systematic_fey1110);
   gre->SetName("data_v2_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1234;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_14GeV_Hadrons_systematic1110 = new TH1F("Graph_data_v2_14GeV_Hadrons_systematic1110","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04855724,2.648119);
   Graph_data_v2_14GeV_Hadrons_systematic1110->SetMinimum(0.1977248);
   Graph_data_v2_14GeV_Hadrons_systematic1110->SetMaximum(2.935428);
   Graph_data_v2_14GeV_Hadrons_systematic1110->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons_systematic1110->SetStats(0);
   Graph_data_v2_14GeV_Hadrons_systematic1110->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons_systematic1110->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons_systematic1110->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons_systematic1110);
   
   gre->Draw("e5");
   
   Double_t data_v2_19GeV_Hadrons_systematic_fx1111[9] = {
   0.2947492,
   0.490424,
   0.6895505,
   0.8893161,
   1.089201,
   1.289208,
   1.557372,
   1.956735,
   2.40631};
   Double_t data_v2_19GeV_Hadrons_systematic_fy1111[9] = {
   0.3951246,
   0.7239617,
   1.028395,
   1.296646,
   1.556433,
   1.787587,
   2.043033,
   2.408668,
   2.597226};
   Double_t data_v2_19GeV_Hadrons_systematic_fex1111[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_19GeV_Hadrons_systematic_fey1111[9] = {
   0.003674614,
   0.003767612,
   0.0007280606,
   0.004104313,
   0.006121438,
   0.001953031,
   0.006623716,
   0.0292073,
   0.01498743};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_systematic_fx1111,data_v2_19GeV_Hadrons_systematic_fy1111,data_v2_19GeV_Hadrons_systematic_fex1111,data_v2_19GeV_Hadrons_systematic_fey1111);
   gre->SetName("data_v2_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1235;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v2_19GeV_Hadrons_systematic1111 = new TH1F("Graph_data_v2_19GeV_Hadrons_systematic1111","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.04759303,2.653467);
   Graph_data_v2_19GeV_Hadrons_systematic1111->SetMinimum(0.1693737);
   Graph_data_v2_19GeV_Hadrons_systematic1111->SetMaximum(2.834289);
   Graph_data_v2_19GeV_Hadrons_systematic1111->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons_systematic1111->SetStats(0);
   Graph_data_v2_19GeV_Hadrons_systematic1111->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons_systematic1111->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons_systematic1111->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons_systematic1111);
   
   gre->Draw("e5");
   
   Double_t data_v2_27GeV_Hadrons_systematic_fx1112[12] = {
   0.2949928,
   0.490609,
   0.6898087,
   0.8895489,
   1.089438,
   1.2894,
   1.489528,
   1.689501,
   1.889503,
   2.159026,
   2.559472,
   2.960338};
   Double_t data_v2_27GeV_Hadrons_systematic_fy1112[12] = {
   0.3877173,
   0.7114005,
   1.010923,
   1.284727,
   1.533981,
   1.755759,
   1.952507,
   2.135311,
   2.27106,
   2.432953,
   2.575686,
   2.760966};
   Double_t data_v2_27GeV_Hadrons_systematic_fex1112[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_27GeV_Hadrons_systematic_fey1112[12] = {
   0.003140869,
   0.002207026,
   0.0006846358,
   0.0009466904,
   0.002216982,
   0.0008301865,
   0.001210586,
   0.003850414,
   0.003978687,
   0.004718006,
   0.00811275,
   0.006738339};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_systematic_fx1112,data_v2_27GeV_Hadrons_systematic_fy1112,data_v2_27GeV_Hadrons_systematic_fex1112,data_v2_27GeV_Hadrons_systematic_fey1112);
   gre->SetName("data_v2_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1236;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_27GeV_Hadrons_systematic1112 = new TH1F("Graph_data_v2_27GeV_Hadrons_systematic1112","#font[42]{#scale[1.3]{27 GeV}}",100,0,3.262872);
   Graph_data_v2_27GeV_Hadrons_systematic1112->SetMinimum(0.1462636);
   Graph_data_v2_27GeV_Hadrons_systematic1112->SetMaximum(3.006018);
   Graph_data_v2_27GeV_Hadrons_systematic1112->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons_systematic1112->SetStats(0);
   Graph_data_v2_27GeV_Hadrons_systematic1112->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons_systematic1112->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons_systematic1112->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons_systematic1112);
   
   gre->Draw("e5");
   
   Double_t data_v2_39GeV_Hadrons_systematic_fx1113[12] = {
   0.2951146,
   0.4906991,
   0.689908,
   0.8897015,
   1.08977,
   1.289902,
   1.489942,
   1.689971,
   1.890027,
   2.161294,
   2.562234,
   2.963338};
   Double_t data_v2_39GeV_Hadrons_systematic_fy1113[12] = {
   0.3761254,
   0.697835,
   1.00089,
   1.269993,
   1.515879,
   1.728752,
   1.927958,
   2.078125,
   2.220429,
   2.358008,
   2.497078,
   2.581575};
   Double_t data_v2_39GeV_Hadrons_systematic_fex1113[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_39GeV_Hadrons_systematic_fey1113[12] = {
   0.003145982,
   0.001792626,
   0.001688164,
   0.0004865721,
   0.0009852926,
   0.002873611,
   0.003334987,
   0.004270342,
   0.003411937,
   0.007567688,
   0.005754347,
   0.01424924};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_systematic_fx1113,data_v2_39GeV_Hadrons_systematic_fy1113,data_v2_39GeV_Hadrons_systematic_fex1113,data_v2_39GeV_Hadrons_systematic_fey1113);
   gre->SetName("data_v2_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1237;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v2_39GeV_Hadrons_systematic1113 = new TH1F("Graph_data_v2_39GeV_Hadrons_systematic1113","#font[42]{#scale[1.3]{39 GeV}}",100,0,3.26616);
   Graph_data_v2_39GeV_Hadrons_systematic1113->SetMinimum(0.1506949);
   Graph_data_v2_39GeV_Hadrons_systematic1113->SetMaximum(2.818109);
   Graph_data_v2_39GeV_Hadrons_systematic1113->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons_systematic1113->SetStats(0);
   Graph_data_v2_39GeV_Hadrons_systematic1113->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons_systematic1113->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons_systematic1113->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons_systematic1113);
   
   gre->Draw("e5");
   
   Double_t data_v2_62GeV_Hadrons_systematic_fx1114[12] = {
   0.2952875,
   0.4909529,
   0.6902105,
   0.8900885,
   1.09017,
   1.290368,
   1.49039,
   1.690474,
   1.89053,
   2.16366,
   2.564937,
   2.966131};
   Double_t data_v2_62GeV_Hadrons_systematic_fy1114[12] = {
   0.3656905,
   0.6846053,
   0.981159,
   1.24539,
   1.473794,
   1.686125,
   1.865816,
   2.012585,
   2.128261,
   2.255638,
   2.369521,
   2.430911};
   Double_t data_v2_62GeV_Hadrons_systematic_fex1114[12] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v2_62GeV_Hadrons_systematic_fey1114[12] = {
   0.002350305,
   0.001579855,
   0.0003572362,
   0.001525924,
   0.0007080032,
   0.00197339,
   0.001941085,
   0.008024349,
   0.004054555,
   0.00550572,
   0.005763184,
   0.01149183};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_systematic_fx1114,data_v2_62GeV_Hadrons_systematic_fy1114,data_v2_62GeV_Hadrons_systematic_fex1114,data_v2_62GeV_Hadrons_systematic_fey1114);
   gre->SetName("data_v2_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1238;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v2_62GeV_Hadrons_systematic1114 = new TH1F("Graph_data_v2_62GeV_Hadrons_systematic1114","#font[42]{#scale[1.3]{62.4 GeV}}",100,0,3.269215);
   Graph_data_v2_62GeV_Hadrons_systematic1114->SetMinimum(0.1554339);
   Graph_data_v2_62GeV_Hadrons_systematic1114->SetMaximum(2.650309);
   Graph_data_v2_62GeV_Hadrons_systematic1114->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons_systematic1114->SetStats(0);
   Graph_data_v2_62GeV_Hadrons_systematic1114->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons_systematic1114->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons_systematic1114->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons_systematic1114);
   
   gre->Draw("e5");
   
   Double_t data_v2_11GeV_Hadrons_fx1115[9] = {
   0.2943644,
   0.4903465,
   0.6896691,
   0.8892842,
   1.089061,
   1.288873,
   1.555258,
   1.953761,
   2.398675};
   Double_t data_v2_11GeV_Hadrons_fy1115[9] = {
   0.420019,
   0.7420187,
   1.018547,
   1.311564,
   1.536878,
   1.755701,
   2.053668,
   2.447613,
   2.832107};
   Double_t data_v2_11GeV_Hadrons_fex1115[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_11GeV_Hadrons_fey1115[9] = {
   0.009821568,
   0.01011907,
   0.01181701,
   0.01440702,
   0.0178237,
   0.02239118,
   0.02367947,
   0.04070782,
   0.07383979};
   gre = new TGraphErrors(9,data_v2_11GeV_Hadrons_fx1115,data_v2_11GeV_Hadrons_fy1115,data_v2_11GeV_Hadrons_fex1115,data_v2_11GeV_Hadrons_fey1115);
   gre->SetName("data_v2_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_11GeV_Hadrons1115 = new TH1F("Graph_data_v2_11GeV_Hadrons1115","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.08393332,2.609106);
   Graph_data_v2_11GeV_Hadrons1115->SetMinimum(0.1606225);
   Graph_data_v2_11GeV_Hadrons1115->SetMaximum(3.155522);
   Graph_data_v2_11GeV_Hadrons1115->SetDirectory(0);
   Graph_data_v2_11GeV_Hadrons1115->SetStats(0);
   Graph_data_v2_11GeV_Hadrons1115->SetFillColor(10);
   Graph_data_v2_11GeV_Hadrons1115->SetFillStyle(0);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_11GeV_Hadrons1115->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_11GeV_Hadrons1115->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_11GeV_Hadrons1115->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_11GeV_Hadrons1115->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_11GeV_Hadrons1115->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_11GeV_Hadrons1115->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_11GeV_Hadrons1115);
   
   gre->Draw("p");
   
   Double_t data_v2_14GeV_Hadrons_fx1116[9] = {
   0.2951874,
   0.4904256,
   0.6894746,
   0.8892084,
   1.088917,
   1.288969,
   1.555972,
   1.954997,
   2.401489};
   Double_t data_v2_14GeV_Hadrons_fy1116[9] = {
   0.4278005,
   0.7395286,
   1.022987,
   1.295237,
   1.533133,
   1.778765,
   2.041839,
   2.382886,
   2.698323};
   Double_t data_v2_14GeV_Hadrons_fex1116[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_14GeV_Hadrons_fey1116[9] = {
   0.005473708,
   0.005574233,
   0.006533433,
   0.007976903,
   0.009907999,
   0.01248376,
   0.0131075,
   0.02219217,
   0.03943856};
   gre = new TGraphErrors(9,data_v2_14GeV_Hadrons_fx1116,data_v2_14GeV_Hadrons_fy1116,data_v2_14GeV_Hadrons_fex1116,data_v2_14GeV_Hadrons_fey1116);
   gre->SetName("data_v2_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_14GeV_Hadrons1116 = new TH1F("Graph_data_v2_14GeV_Hadrons1116","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08455724,2.612119);
   Graph_data_v2_14GeV_Hadrons1116->SetMinimum(0.1907834);
   Graph_data_v2_14GeV_Hadrons1116->SetMaximum(2.969305);
   Graph_data_v2_14GeV_Hadrons1116->SetDirectory(0);
   Graph_data_v2_14GeV_Hadrons1116->SetStats(0);
   Graph_data_v2_14GeV_Hadrons1116->SetFillColor(10);
   Graph_data_v2_14GeV_Hadrons1116->SetFillStyle(0);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_14GeV_Hadrons1116->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_14GeV_Hadrons1116->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_14GeV_Hadrons1116->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_14GeV_Hadrons1116->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_14GeV_Hadrons1116->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_14GeV_Hadrons1116->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_14GeV_Hadrons1116);
   
   gre->Draw("p");
   
   Double_t data_v2_19GeV_Hadrons_fx1117[9] = {
   0.2947492,
   0.490424,
   0.6895505,
   0.8893161,
   1.089201,
   1.289208,
   1.557372,
   1.956735,
   2.40631};
   Double_t data_v2_19GeV_Hadrons_fy1117[9] = {
   0.3951246,
   0.7239617,
   1.028395,
   1.296646,
   1.556433,
   1.787587,
   2.043033,
   2.408668,
   2.597226};
   Double_t data_v2_19GeV_Hadrons_fex1117[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v2_19GeV_Hadrons_fey1117[9] = {
   0.004281869,
   0.004381533,
   0.005145358,
   0.006263446,
   0.007765319,
   0.009713267,
   0.0100942,
   0.01670958,
   0.02858645};
   gre = new TGraphErrors(9,data_v2_19GeV_Hadrons_fx1117,data_v2_19GeV_Hadrons_fy1117,data_v2_19GeV_Hadrons_fex1117,data_v2_19GeV_Hadrons_fey1117);
   gre->SetName("data_v2_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_19GeV_Hadrons1117 = new TH1F("Graph_data_v2_19GeV_Hadrons1117","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.08359303,2.617467);
   Graph_data_v2_19GeV_Hadrons1117->SetMinimum(0.1673458);
   Graph_data_v2_19GeV_Hadrons1117->SetMaximum(2.849309);
   Graph_data_v2_19GeV_Hadrons1117->SetDirectory(0);
   Graph_data_v2_19GeV_Hadrons1117->SetStats(0);
   Graph_data_v2_19GeV_Hadrons1117->SetFillColor(10);
   Graph_data_v2_19GeV_Hadrons1117->SetFillStyle(0);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_19GeV_Hadrons1117->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_19GeV_Hadrons1117->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_19GeV_Hadrons1117->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_19GeV_Hadrons1117->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_19GeV_Hadrons1117->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_19GeV_Hadrons1117->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_19GeV_Hadrons1117);
   
   gre->Draw("p");
   
   Double_t data_v2_27GeV_Hadrons_fx1118[12] = {
   0.2949928,
   0.490609,
   0.6898087,
   0.8895489,
   1.089438,
   1.2894,
   1.489528,
   1.689501,
   1.889503,
   2.159026,
   2.559472,
   2.960338};
   Double_t data_v2_27GeV_Hadrons_fy1118[12] = {
   0.3877173,
   0.7114005,
   1.010923,
   1.284727,
   1.533981,
   1.755759,
   1.952507,
   2.135311,
   2.27106,
   2.432953,
   2.575686,
   2.760966};
   Double_t data_v2_27GeV_Hadrons_fex1118[12] = {
   0,
   0,
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
   Double_t data_v2_27GeV_Hadrons_fey1118[12] = {
   0.0009080817,
   0.000921698,
   0.001076035,
   0.001304695,
   0.00160475,
   0.001998154,
   0.002506775,
   0.003175299,
   0.004061166,
   0.004369411,
   0.00801476,
   0.01477405};
   gre = new TGraphErrors(12,data_v2_27GeV_Hadrons_fx1118,data_v2_27GeV_Hadrons_fy1118,data_v2_27GeV_Hadrons_fex1118,data_v2_27GeV_Hadrons_fey1118);
   gre->SetName("data_v2_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_27GeV_Hadrons1118 = new TH1F("Graph_data_v2_27GeV_Hadrons1118","#font[42]{#scale[1.3]{27 GeV}}",100,0.02845831,3.226872);
   Graph_data_v2_27GeV_Hadrons1118->SetMinimum(0.1479161);
   Graph_data_v2_27GeV_Hadrons1118->SetMaximum(3.014634);
   Graph_data_v2_27GeV_Hadrons1118->SetDirectory(0);
   Graph_data_v2_27GeV_Hadrons1118->SetStats(0);
   Graph_data_v2_27GeV_Hadrons1118->SetFillColor(10);
   Graph_data_v2_27GeV_Hadrons1118->SetFillStyle(0);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_27GeV_Hadrons1118->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_27GeV_Hadrons1118->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_27GeV_Hadrons1118->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_27GeV_Hadrons1118->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_27GeV_Hadrons1118->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_27GeV_Hadrons1118->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_27GeV_Hadrons1118);
   
   gre->Draw("p");
   
   Double_t data_v2_39GeV_Hadrons_fx1119[12] = {
   0.2951146,
   0.4906991,
   0.689908,
   0.8897015,
   1.08977,
   1.289902,
   1.489942,
   1.689971,
   1.890027,
   2.161294,
   2.562234,
   2.963338};
   Double_t data_v2_39GeV_Hadrons_fy1119[12] = {
   0.3761254,
   0.697835,
   1.00089,
   1.269993,
   1.515879,
   1.728752,
   1.927958,
   2.078125,
   2.220429,
   2.358008,
   2.497078,
   2.581575};
   Double_t data_v2_39GeV_Hadrons_fex1119[12] = {
   0,
   0,
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
   Double_t data_v2_39GeV_Hadrons_fey1119[12] = {
   0.001555958,
   0.001573127,
   0.001831274,
   0.002210048,
   0.002707005,
   0.003328696,
   0.004126711,
   0.00515669,
   0.006505775,
   0.006849154,
   0.01206618,
   0.02119901};
   gre = new TGraphErrors(12,data_v2_39GeV_Hadrons_fx1119,data_v2_39GeV_Hadrons_fy1119,data_v2_39GeV_Hadrons_fex1119,data_v2_39GeV_Hadrons_fey1119);
   gre->SetName("data_v2_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_39GeV_Hadrons1119 = new TH1F("Graph_data_v2_39GeV_Hadrons1119","#font[42]{#scale[1.3]{39 GeV}}",100,0.02829226,3.23016);
   Graph_data_v2_39GeV_Hadrons1119->SetMinimum(0.1517489);
   Graph_data_v2_39GeV_Hadrons1119->SetMaximum(2.825595);
   Graph_data_v2_39GeV_Hadrons1119->SetDirectory(0);
   Graph_data_v2_39GeV_Hadrons1119->SetStats(0);
   Graph_data_v2_39GeV_Hadrons1119->SetFillColor(10);
   Graph_data_v2_39GeV_Hadrons1119->SetFillStyle(0);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_39GeV_Hadrons1119->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_39GeV_Hadrons1119->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_39GeV_Hadrons1119->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_39GeV_Hadrons1119->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_39GeV_Hadrons1119->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_39GeV_Hadrons1119->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_39GeV_Hadrons1119);
   
   gre->Draw("p");
   
   Double_t data_v2_62GeV_Hadrons_fx1120[12] = {
   0.2952875,
   0.4909529,
   0.6902105,
   0.8900885,
   1.09017,
   1.290368,
   1.49039,
   1.690474,
   1.89053,
   2.16366,
   2.564937,
   2.966131};
   Double_t data_v2_62GeV_Hadrons_fy1120[12] = {
   0.3656905,
   0.6846053,
   0.981159,
   1.24539,
   1.473794,
   1.686125,
   1.865816,
   2.012585,
   2.128261,
   2.255638,
   2.369521,
   2.430911};
   Double_t data_v2_62GeV_Hadrons_fex1120[12] = {
   0,
   0,
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
   Double_t data_v2_62GeV_Hadrons_fey1120[12] = {
   0.001914521,
   0.001919015,
   0.002213449,
   0.002648003,
   0.003206879,
   0.003904267,
   0.004777365,
   0.005892402,
   0.007312931,
   0.007529384,
   0.01275238,
   0.02144018};
   gre = new TGraphErrors(12,data_v2_62GeV_Hadrons_fx1120,data_v2_62GeV_Hadrons_fy1120,data_v2_62GeV_Hadrons_fex1120,data_v2_62GeV_Hadrons_fey1120);
   gre->SetName("data_v2_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v2_62GeV_Hadrons1120 = new TH1F("Graph_data_v2_62GeV_Hadrons1120","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.02820321,3.233215);
   Graph_data_v2_62GeV_Hadrons1120->SetMinimum(0.1549184);
   Graph_data_v2_62GeV_Hadrons1120->SetMaximum(2.661209);
   Graph_data_v2_62GeV_Hadrons1120->SetDirectory(0);
   Graph_data_v2_62GeV_Hadrons1120->SetStats(0);
   Graph_data_v2_62GeV_Hadrons1120->SetFillColor(10);
   Graph_data_v2_62GeV_Hadrons1120->SetFillStyle(0);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetNdivisions(508);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v2_62GeV_Hadrons1120->GetXaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetNdivisions(505);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v2_62GeV_Hadrons1120->GetYaxis()->SetTitleFont(42);
   Graph_data_v2_62GeV_Hadrons1120->GetZaxis()->SetLabelFont(42);
   Graph_data_v2_62GeV_Hadrons1120->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v2_62GeV_Hadrons1120->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v2_62GeV_Hadrons1120->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v2_62GeV_Hadrons1120);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_0_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: Pad_1_1
   TPad *Pad_1_1 = new TPad("Pad_1_1", "",0.525,0.1,0.9,0.276);
   Pad_1_1->Draw();
   Pad_1_1->cd();
   Pad_1_1->Range(-0.05,-0.3,2.86,5.67);
   Pad_1_1->SetFillColor(0);
   Pad_1_1->SetBorderMode(0);
   Pad_1_1->SetBorderSize(0);
   Pad_1_1->SetTickx(1);
   Pad_1_1->SetTicky(1);
   Pad_1_1->SetLeftMargin(0);
   Pad_1_1->SetRightMargin(0);
   Pad_1_1->SetTopMargin(0);
   Pad_1_1->SetBottomMargin(0);
   
   TH2F *__17 = new TH2F("__17","",2,-0.05,2.86,2,-0.3,5.67);
   __17->SetStats(0);
   __17->SetFillColor(10);
   __17->SetFillStyle(0);
   __17->GetXaxis()->SetNdivisions(508);
   __17->GetXaxis()->SetLabelFont(42);
   __17->GetXaxis()->SetLabelOffset(0.02);
   __17->GetXaxis()->SetLabelSize(0.13);
   __17->GetXaxis()->SetTitleSize(0.05);
   __17->GetXaxis()->SetTitleOffset(1.2);
   __17->GetXaxis()->SetTitleFont(42);
   __17->GetYaxis()->SetNdivisions(505);
   __17->GetYaxis()->SetLabelFont(42);
   __17->GetYaxis()->SetLabelOffset(0.02);
   __17->GetYaxis()->SetLabelSize(0.13);
   __17->GetYaxis()->SetTitleSize(0.05);
   __17->GetYaxis()->SetTitleOffset(1.4);
   __17->GetYaxis()->SetTitleFont(42);
   __17->GetZaxis()->SetLabelFont(42);
   __17->GetZaxis()->SetLabelSize(0.035);
   __17->GetZaxis()->SetTitleSize(0.035);
   __17->GetZaxis()->SetTitleFont(42);
   __17->Draw("");
      tex = new TLatex(0.04,4.8195,"#font[42]{(j)}");
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t data_v3_11GeV_Hadrons_systematic_fx1121[6] = {
   0.2943644,
   0.4903465,
   0.7588678,
   1.15697,
   1.602354,
   2.19965};
   Double_t data_v3_11GeV_Hadrons_systematic_fy1121[6] = {
   0.379198,
   0.6737606,
   0.7828597,
   2.130305,
   3.28938,
   2.795037};
   Double_t data_v3_11GeV_Hadrons_systematic_fex1121[6] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_11GeV_Hadrons_systematic_fey1121[6] = {
   0.3277418,
   0.2664849,
   0.4876749,
   0.398642,
   0.5074751,
   1.031878};
   gre = new TGraphErrors(6,data_v3_11GeV_Hadrons_systematic_fx1121,data_v3_11GeV_Hadrons_systematic_fy1121,data_v3_11GeV_Hadrons_systematic_fex1121,data_v3_11GeV_Hadrons_systematic_fey1121);
   gre->SetName("data_v3_11GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");

   ci = 1239;
   color = new TColor(ci, 1, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   
   TH1F *Graph_data_v3_11GeV_Hadrons_systematic1121 = new TH1F("Graph_data_v3_11GeV_Hadrons_systematic1121","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.06783578,2.426179);
   Graph_data_v3_11GeV_Hadrons_systematic1121->SetMinimum(0.04631063);
   Graph_data_v3_11GeV_Hadrons_systematic1121->SetMaximum(4.20446);
   Graph_data_v3_11GeV_Hadrons_systematic1121->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons_systematic1121->SetStats(0);
   Graph_data_v3_11GeV_Hadrons_systematic1121->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons_systematic1121->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons_systematic1121->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons_systematic1121);
   
   gre->Draw("e5");
   
   Double_t data_v3_14GeV_Hadrons_systematic_fx1122[8] = {
   0.2951874,
   0.4904256,
   0.6894746,
   0.8892084,
   1.156863,
   1.555972,
   1.954997,
   2.401489};
   Double_t data_v3_14GeV_Hadrons_systematic_fy1122[8] = {
   0.2860667,
   0.4407752,
   0.8555512,
   1.246668,
   2.187207,
   2.588695,
   4.735991,
   5.575191};
   Double_t data_v3_14GeV_Hadrons_systematic_fex1122[8] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_14GeV_Hadrons_systematic_fey1122[8] = {
   0.05936464,
   0.02813398,
   0.06146216,
   0.1621189,
   0.0382262,
   0.3770856,
   0.4073745,
   0.989276};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_systematic_fx1122,data_v3_14GeV_Hadrons_systematic_fy1122,data_v3_14GeV_Hadrons_systematic_fex1122,data_v3_14GeV_Hadrons_systematic_fey1122);
   gre->SetName("data_v3_14GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");

   ci = 1240;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_14GeV_Hadrons_systematic1122 = new TH1F("Graph_data_v3_14GeV_Hadrons_systematic1122","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.04855724,2.648119);
   Graph_data_v3_14GeV_Hadrons_systematic1122->SetMinimum(0.2040318);
   Graph_data_v3_14GeV_Hadrons_systematic1122->SetMaximum(7.198243);
   Graph_data_v3_14GeV_Hadrons_systematic1122->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons_systematic1122->SetStats(0);
   Graph_data_v3_14GeV_Hadrons_systematic1122->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons_systematic1122->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons_systematic1122->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons_systematic1122);
   
   gre->Draw("e5");
   
   Double_t data_v3_19GeV_Hadrons_systematic_fx1123[9] = {
   0.2947492,
   0.490424,
   0.6895505,
   0.8893161,
   1.089201,
   1.357583,
   1.756976,
   2.156674,
   2.606104};
   Double_t data_v3_19GeV_Hadrons_systematic_fy1123[9] = {
   0.1789196,
   0.5088079,
   0.9650048,
   1.351355,
   1.738559,
   2.532483,
   3.375939,
   3.274179,
   3.211434};
   Double_t data_v3_19GeV_Hadrons_systematic_fex1123[9] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_19GeV_Hadrons_systematic_fey1123[9] = {
   0.01341961,
   0.03411254,
   0.02063393,
   0.07156801,
   0.05198491,
   0.1231606,
   0.09828379,
   0.1545632,
   0.8390375};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_systematic_fx1123,data_v3_19GeV_Hadrons_systematic_fy1123,data_v3_19GeV_Hadrons_systematic_fex1123,data_v3_19GeV_Hadrons_systematic_fey1123);
   gre->SetName("data_v3_19GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");

   ci = 1241;
   color = new TColor(ci, 0, 0, 1, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   
   TH1F *Graph_data_v3_19GeV_Hadrons_systematic1123 = new TH1F("Graph_data_v3_19GeV_Hadrons_systematic1123","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.02761365,2.87324);
   Graph_data_v3_19GeV_Hadrons_systematic1123->SetMinimum(0.14895);
   Graph_data_v3_19GeV_Hadrons_systematic1123->SetMaximum(4.438968);
   Graph_data_v3_19GeV_Hadrons_systematic1123->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons_systematic1123->SetStats(0);
   Graph_data_v3_19GeV_Hadrons_systematic1123->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons_systematic1123->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons_systematic1123->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons_systematic1123);
   
   gre->Draw("e5");
   
   Double_t data_v3_27GeV_Hadrons_systematic_fx1124[11] = {
   0.2949928,
   0.490609,
   0.6898087,
   0.8895489,
   1.089438,
   1.2894,
   1.489528,
   1.689501,
   1.889503,
   2.159026,
   2.559472};
   Double_t data_v3_27GeV_Hadrons_systematic_fy1124[11] = {
   0.1903601,
   0.5103029,
   0.9157463,
   1.395858,
   1.778315,
   2.211641,
   2.521171,
   2.836624,
   3.16081,
   3.254423,
   3.473251};
   Double_t data_v3_27GeV_Hadrons_systematic_fex1124[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_27GeV_Hadrons_systematic_fey1124[11] = {
   0.01683005,
   0.0245821,
   0.02467022,
   0.01477541,
   0.0281219,
   0.03392221,
   0.03425865,
   0.08844016,
   0.04549419,
   0.1211624,
   0.2190643};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_systematic_fx1124,data_v3_27GeV_Hadrons_systematic_fy1124,data_v3_27GeV_Hadrons_systematic_fex1124,data_v3_27GeV_Hadrons_systematic_fey1124);
   gre->SetName("data_v3_27GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");

   ci = 1242;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_27GeV_Hadrons_systematic1124 = new TH1F("Graph_data_v3_27GeV_Hadrons_systematic1124","#font[42]{#scale[1.3]{27 GeV}}",100,0.03254491,2.82192);
   Graph_data_v3_27GeV_Hadrons_systematic1124->SetMinimum(0.1561771);
   Graph_data_v3_27GeV_Hadrons_systematic1124->SetMaximum(4.044194);
   Graph_data_v3_27GeV_Hadrons_systematic1124->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons_systematic1124->SetStats(0);
   Graph_data_v3_27GeV_Hadrons_systematic1124->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons_systematic1124->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons_systematic1124->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons_systematic1124);
   
   gre->Draw("e5");
   
   Double_t data_v3_39GeV_Hadrons_systematic_fx1125[11] = {
   0.2951146,
   0.4906991,
   0.689908,
   0.8897015,
   1.08977,
   1.289902,
   1.489942,
   1.689971,
   1.890027,
   2.161294,
   2.562234};
   Double_t data_v3_39GeV_Hadrons_systematic_fy1125[11] = {
   0.145239,
   0.5006805,
   0.943122,
   1.311704,
   1.720096,
   2.208957,
   2.533232,
   2.755479,
   3.272347,
   3.012442,
   3.255941};
   Double_t data_v3_39GeV_Hadrons_systematic_fex1125[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_39GeV_Hadrons_systematic_fey1125[11] = {
   0.009720508,
   0.01449717,
   0.02803179,
   0.03697914,
   0.0649322,
   0.01455352,
   0.02570396,
   0.06174853,
   0.0607214,
   0.1428127,
   0.126582};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_systematic_fx1125,data_v3_39GeV_Hadrons_systematic_fy1125,data_v3_39GeV_Hadrons_systematic_fex1125,data_v3_39GeV_Hadrons_systematic_fey1125);
   gre->SetName("data_v3_39GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");

   ci = 1243;
   color = new TColor(ci, 0, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   
   TH1F *Graph_data_v3_39GeV_Hadrons_systematic1125 = new TH1F("Graph_data_v3_39GeV_Hadrons_systematic1125","#font[42]{#scale[1.3]{39 GeV}}",100,0.03240258,2.824946);
   Graph_data_v3_39GeV_Hadrons_systematic1125->SetMinimum(0.1219666);
   Graph_data_v3_39GeV_Hadrons_systematic1125->SetMaximum(3.707224);
   Graph_data_v3_39GeV_Hadrons_systematic1125->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons_systematic1125->SetStats(0);
   Graph_data_v3_39GeV_Hadrons_systematic1125->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons_systematic1125->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons_systematic1125->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons_systematic1125);
   
   gre->Draw("e5");
   
   Double_t data_v3_62GeV_Hadrons_systematic_fx1126[11] = {
   0.2952875,
   0.4909529,
   0.6902105,
   0.8900885,
   1.09017,
   1.290368,
   1.49039,
   1.690474,
   1.89053,
   2.16366,
   2.564937};
   Double_t data_v3_62GeV_Hadrons_systematic_fy1126[11] = {
   0.1615726,
   0.4889246,
   0.8600182,
   1.326515,
   1.652789,
   2.028515,
   2.438355,
   2.585589,
   2.917498,
   3.241654,
   3.281399};
   Double_t data_v3_62GeV_Hadrons_systematic_fex1126[11] = {
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03,
   0.03};
   Double_t data_v3_62GeV_Hadrons_systematic_fey1126[11] = {
   0.01128939,
   0.008463137,
   0.01720405,
   0.02777712,
   0.04148346,
   0.01967175,
   0.06531954,
   0.0564491,
   0.0458759,
   0.06722137,
   0.02003491};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_systematic_fx1126,data_v3_62GeV_Hadrons_systematic_fy1126,data_v3_62GeV_Hadrons_systematic_fex1126,data_v3_62GeV_Hadrons_systematic_fey1126);
   gre->SetName("data_v3_62GeV_Hadrons_systematic");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");

   ci = 1244;
   color = new TColor(ci, 1, 0, 0, " ", 0.1);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   
   TH1F *Graph_data_v3_62GeV_Hadrons_systematic1126 = new TH1F("Graph_data_v3_62GeV_Hadrons_systematic1126","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.0323226,2.827902);
   Graph_data_v3_62GeV_Hadrons_systematic1126->SetMinimum(0.1352549);
   Graph_data_v3_62GeV_Hadrons_systematic1126->SetMaximum(3.624735);
   Graph_data_v3_62GeV_Hadrons_systematic1126->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons_systematic1126->SetStats(0);
   Graph_data_v3_62GeV_Hadrons_systematic1126->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons_systematic1126->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons_systematic1126->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons_systematic1126);
   
   gre->Draw("e5");
   
   Double_t data_v3_11GeV_Hadrons_fx1127[6] = {
   0.2943644,
   0.4903465,
   0.7588678,
   1.15697,
   1.602354,
   2.19965};
   Double_t data_v3_11GeV_Hadrons_fy1127[6] = {
   0.379198,
   0.6737606,
   0.7828597,
   2.130305,
   3.28938,
   2.795037};
   Double_t data_v3_11GeV_Hadrons_fex1127[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_11GeV_Hadrons_fey1127[6] = {
   0.2412967,
   0.2467515,
   0.2237547,
   0.3997851,
   0.6145282,
   1.283802};
   gre = new TGraphErrors(6,data_v3_11GeV_Hadrons_fx1127,data_v3_11GeV_Hadrons_fy1127,data_v3_11GeV_Hadrons_fex1127,data_v3_11GeV_Hadrons_fey1127);
   gre->SetName("data_v3_11GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{11.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(6);
   gre->SetMarkerColor(6);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_11GeV_Hadrons1127 = new TH1F("Graph_data_v3_11GeV_Hadrons1127","#font[42]{#scale[1.3]{11.5 GeV}}",100,0.1038358,2.390179);
   Graph_data_v3_11GeV_Hadrons1127->SetMinimum(0.1241112);
   Graph_data_v3_11GeV_Hadrons1127->SetMaximum(4.472932);
   Graph_data_v3_11GeV_Hadrons1127->SetDirectory(0);
   Graph_data_v3_11GeV_Hadrons1127->SetStats(0);
   Graph_data_v3_11GeV_Hadrons1127->SetFillColor(10);
   Graph_data_v3_11GeV_Hadrons1127->SetFillStyle(0);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_11GeV_Hadrons1127->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_11GeV_Hadrons1127->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_11GeV_Hadrons1127->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_11GeV_Hadrons1127->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_11GeV_Hadrons1127->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_11GeV_Hadrons1127->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_11GeV_Hadrons1127);
   
   gre->Draw("p");
   
   Double_t data_v3_14GeV_Hadrons_fx1128[8] = {
   0.2951874,
   0.4904256,
   0.6894746,
   0.8892084,
   1.156863,
   1.555972,
   1.954997,
   2.401489};
   Double_t data_v3_14GeV_Hadrons_fy1128[8] = {
   0.2860667,
   0.4407752,
   0.8555512,
   1.246668,
   2.187207,
   2.588695,
   4.735991,
   5.575191};
   Double_t data_v3_14GeV_Hadrons_fex1128[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_14GeV_Hadrons_fey1128[8] = {
   0.1553959,
   0.1537729,
   0.1827834,
   0.2273683,
   0.2618955,
   0.393945,
   0.7050137,
   1.185986};
   gre = new TGraphErrors(8,data_v3_14GeV_Hadrons_fx1128,data_v3_14GeV_Hadrons_fy1128,data_v3_14GeV_Hadrons_fex1128,data_v3_14GeV_Hadrons_fey1128);
   gre->SetName("data_v3_14GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{14.5 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_14GeV_Hadrons1128 = new TH1F("Graph_data_v3_14GeV_Hadrons1128","#font[42]{#scale[1.3]{14.5 GeV}}",100,0.08455724,2.612119);
   Graph_data_v3_14GeV_Hadrons1128->SetMinimum(0.1176037);
   Graph_data_v3_14GeV_Hadrons1128->SetMaximum(7.424227);
   Graph_data_v3_14GeV_Hadrons1128->SetDirectory(0);
   Graph_data_v3_14GeV_Hadrons1128->SetStats(0);
   Graph_data_v3_14GeV_Hadrons1128->SetFillColor(10);
   Graph_data_v3_14GeV_Hadrons1128->SetFillStyle(0);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_14GeV_Hadrons1128->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_14GeV_Hadrons1128->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_14GeV_Hadrons1128->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_14GeV_Hadrons1128->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_14GeV_Hadrons1128->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_14GeV_Hadrons1128->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_14GeV_Hadrons1128);
   
   gre->Draw("p");
   
   Double_t data_v3_19GeV_Hadrons_fx1129[9] = {
   0.2947492,
   0.490424,
   0.6895505,
   0.8893161,
   1.089201,
   1.357583,
   1.756976,
   2.156674,
   2.606104};
   Double_t data_v3_19GeV_Hadrons_fy1129[9] = {
   0.1789196,
   0.5088079,
   0.9650048,
   1.351355,
   1.738559,
   2.532483,
   3.375939,
   3.274179,
   3.211434};
   Double_t data_v3_19GeV_Hadrons_fex1129[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t data_v3_19GeV_Hadrons_fey1129[9] = {
   0.09110208,
   0.09178195,
   0.1098444,
   0.1360284,
   0.170745,
   0.1892609,
   0.2980825,
   0.491637,
   0.8524628};
   gre = new TGraphErrors(9,data_v3_19GeV_Hadrons_fx1129,data_v3_19GeV_Hadrons_fy1129,data_v3_19GeV_Hadrons_fex1129,data_v3_19GeV_Hadrons_fey1129);
   gre->SetName("data_v3_19GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{19.6 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_19GeV_Hadrons1129 = new TH1F("Graph_data_v3_19GeV_Hadrons1129","#font[42]{#scale[1.3]{19.6 GeV}}",100,0.06361365,2.83724);
   Graph_data_v3_19GeV_Hadrons1129->SetMinimum(0.07903574);
   Graph_data_v3_19GeV_Hadrons1129->SetMaximum(4.461505);
   Graph_data_v3_19GeV_Hadrons1129->SetDirectory(0);
   Graph_data_v3_19GeV_Hadrons1129->SetStats(0);
   Graph_data_v3_19GeV_Hadrons1129->SetFillColor(10);
   Graph_data_v3_19GeV_Hadrons1129->SetFillStyle(0);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_19GeV_Hadrons1129->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_19GeV_Hadrons1129->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_19GeV_Hadrons1129->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_19GeV_Hadrons1129->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_19GeV_Hadrons1129->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_19GeV_Hadrons1129->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_19GeV_Hadrons1129);
   
   gre->Draw("p");
   
   Double_t data_v3_27GeV_Hadrons_fx1130[11] = {
   0.2949928,
   0.490609,
   0.6898087,
   0.8895489,
   1.089438,
   1.2894,
   1.489528,
   1.689501,
   1.889503,
   2.159026,
   2.559472};
   Double_t data_v3_27GeV_Hadrons_fy1130[11] = {
   0.1903601,
   0.5103029,
   0.9157463,
   1.395858,
   1.778315,
   2.211641,
   2.521171,
   2.836624,
   3.16081,
   3.254423,
   3.473251};
   Double_t data_v3_27GeV_Hadrons_fex1130[11] = {
   0,
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
   Double_t data_v3_27GeV_Hadrons_fey1130[11] = {
   0.01660731,
   0.01661149,
   0.01962809,
   0.02452396,
   0.0305245,
   0.03845129,
   0.04803929,
   0.06054085,
   0.07708227,
   0.08256642,
   0.1492634};
   gre = new TGraphErrors(11,data_v3_27GeV_Hadrons_fx1130,data_v3_27GeV_Hadrons_fy1130,data_v3_27GeV_Hadrons_fex1130,data_v3_27GeV_Hadrons_fey1130);
   gre->SetName("data_v3_27GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{27 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_27GeV_Hadrons1130 = new TH1F("Graph_data_v3_27GeV_Hadrons1130","#font[42]{#scale[1.3]{27 GeV}}",100,0.06854491,2.78592);
   Graph_data_v3_27GeV_Hadrons1130->SetMinimum(0.1563775);
   Graph_data_v3_27GeV_Hadrons1130->SetMaximum(3.967391);
   Graph_data_v3_27GeV_Hadrons1130->SetDirectory(0);
   Graph_data_v3_27GeV_Hadrons1130->SetStats(0);
   Graph_data_v3_27GeV_Hadrons1130->SetFillColor(10);
   Graph_data_v3_27GeV_Hadrons1130->SetFillStyle(0);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_27GeV_Hadrons1130->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_27GeV_Hadrons1130->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_27GeV_Hadrons1130->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_27GeV_Hadrons1130->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_27GeV_Hadrons1130->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_27GeV_Hadrons1130->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_27GeV_Hadrons1130);
   
   gre->Draw("p");
   
   Double_t data_v3_39GeV_Hadrons_fx1131[11] = {
   0.2951146,
   0.4906991,
   0.689908,
   0.8897015,
   1.08977,
   1.289902,
   1.489942,
   1.689971,
   1.890027,
   2.161294,
   2.562234};
   Double_t data_v3_39GeV_Hadrons_fy1131[11] = {
   0.145239,
   0.5006805,
   0.943122,
   1.311704,
   1.720096,
   2.208957,
   2.533232,
   2.755479,
   3.272347,
   3.012442,
   3.255941};
   Double_t data_v3_39GeV_Hadrons_fex1131[11] = {
   0,
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
   Double_t data_v3_39GeV_Hadrons_fey1131[11] = {
   0.02499964,
   0.02494984,
   0.02952563,
   0.03614768,
   0.04503885,
   0.05647556,
   0.06981495,
   0.08650047,
   0.1094662,
   0.1135206,
   0.1978173};
   gre = new TGraphErrors(11,data_v3_39GeV_Hadrons_fx1131,data_v3_39GeV_Hadrons_fy1131,data_v3_39GeV_Hadrons_fex1131,data_v3_39GeV_Hadrons_fey1131);
   gre->SetName("data_v3_39GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{39 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_39GeV_Hadrons1131 = new TH1F("Graph_data_v3_39GeV_Hadrons1131","#font[42]{#scale[1.3]{39 GeV}}",100,0.06840258,2.788946);
   Graph_data_v3_39GeV_Hadrons1131->SetMinimum(0.1082154);
   Graph_data_v3_39GeV_Hadrons1131->SetMaximum(3.787111);
   Graph_data_v3_39GeV_Hadrons1131->SetDirectory(0);
   Graph_data_v3_39GeV_Hadrons1131->SetStats(0);
   Graph_data_v3_39GeV_Hadrons1131->SetFillColor(10);
   Graph_data_v3_39GeV_Hadrons1131->SetFillStyle(0);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_39GeV_Hadrons1131->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_39GeV_Hadrons1131->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_39GeV_Hadrons1131->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_39GeV_Hadrons1131->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_39GeV_Hadrons1131->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_39GeV_Hadrons1131->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_39GeV_Hadrons1131);
   
   gre->Draw("p");
   
   Double_t data_v3_62GeV_Hadrons_fx1132[11] = {
   0.2952875,
   0.4909529,
   0.6902105,
   0.8900885,
   1.09017,
   1.290368,
   1.49039,
   1.690474,
   1.89053,
   2.16366,
   2.564937};
   Double_t data_v3_62GeV_Hadrons_fy1132[11] = {
   0.1615726,
   0.4889246,
   0.8600182,
   1.326515,
   1.652789,
   2.028515,
   2.438355,
   2.585589,
   2.917498,
   3.241654,
   3.281399};
   Double_t data_v3_62GeV_Hadrons_fex1132[11] = {
   0,
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
   Double_t data_v3_62GeV_Hadrons_fey1132[11] = {
   0.02639982,
   0.02611596,
   0.0303253,
   0.03734241,
   0.04564016,
   0.05616865,
   0.069354,
   0.08459131,
   0.1049927,
   0.108946,
   0.1803814};
   gre = new TGraphErrors(11,data_v3_62GeV_Hadrons_fx1132,data_v3_62GeV_Hadrons_fy1132,data_v3_62GeV_Hadrons_fex1132,data_v3_62GeV_Hadrons_fey1132);
   gre->SetName("data_v3_62GeV_Hadrons");
   gre->SetTitle("#font[42]{#scale[1.3]{62.4 GeV}}");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_data_v3_62GeV_Hadrons1132 = new TH1F("Graph_data_v3_62GeV_Hadrons1132","#font[42]{#scale[1.3]{62.4 GeV}}",100,0.0683226,2.791902);
   Graph_data_v3_62GeV_Hadrons1132->SetMinimum(0.1216555);
   Graph_data_v3_62GeV_Hadrons1132->SetMaximum(3.794441);
   Graph_data_v3_62GeV_Hadrons1132->SetDirectory(0);
   Graph_data_v3_62GeV_Hadrons1132->SetStats(0);
   Graph_data_v3_62GeV_Hadrons1132->SetFillColor(10);
   Graph_data_v3_62GeV_Hadrons1132->SetFillStyle(0);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetNdivisions(508);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetTitleOffset(1.2);
   Graph_data_v3_62GeV_Hadrons1132->GetXaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetNdivisions(505);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetLabelOffset(0.02);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetLabelSize(0.05);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetTitleSize(0.05);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetTitleOffset(1.4);
   Graph_data_v3_62GeV_Hadrons1132->GetYaxis()->SetTitleFont(42);
   Graph_data_v3_62GeV_Hadrons1132->GetZaxis()->SetLabelFont(42);
   Graph_data_v3_62GeV_Hadrons1132->GetZaxis()->SetLabelSize(0.035);
   Graph_data_v3_62GeV_Hadrons1132->GetZaxis()->SetTitleSize(0.035);
   Graph_data_v3_62GeV_Hadrons1132->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_data_v3_62GeV_Hadrons1132);
   
   gre->Draw("p");
   line = new TLine(-0.05,0,2.86,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   Pad_1_1->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pad_AxisY
   TPad *pad_AxisY = new TPad("pad_AxisY", "",0,0.1,0.1,1);
   pad_AxisY->Draw();
   pad_AxisY->cd();
   pad_AxisY->Range(0,0,1,1);
   pad_AxisY->SetFillColor(0);
   pad_AxisY->SetBorderMode(0);
   pad_AxisY->SetBorderSize(0);
   pad_AxisY->SetTickx(1);
   pad_AxisY->SetTicky(1);
   pad_AxisY->SetLeftMargin(0.16);
   pad_AxisY->SetRightMargin(0.23);
   pad_AxisY->SetBottomMargin(0);
   pad_AxisY->SetFrameBorderMode(0);
      tex = new TLatex(0.25,0.6,"#font[42]{#frac{v_{n}}{v_{n}^{int}}}");
   tex->SetTextSize(0.5);
   tex->SetLineWidth(2);
   tex->Draw();
   pad_AxisY->Modified();
   canvas->cd();
  
// ------------>Primitives in pad: pad_AxisX
   TPad *pad_AxisX = new TPad("pad_AxisX", "",0,0,1,0.07);
   pad_AxisX->Draw();
   pad_AxisX->cd();
   pad_AxisX->Range(0,0,1,1);
   pad_AxisX->SetFillColor(0);
   pad_AxisX->SetBorderMode(0);
   pad_AxisX->SetBorderSize(0);
   pad_AxisX->SetTickx(1);
   pad_AxisX->SetTicky(1);
   pad_AxisX->SetLeftMargin(0.16);
   pad_AxisX->SetTopMargin(0);
   pad_AxisX->SetBottomMargin(0);
   pad_AxisX->SetFrameBorderMode(0);
      tex = new TLatex(0.75,0.6,"#font[42]{p_{T} [GeV/c]}");
   tex->SetTextSize(0.4);
   tex->SetLineWidth(2);
   tex->Draw();
   pad_AxisX->Modified();
   canvas->cd();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
