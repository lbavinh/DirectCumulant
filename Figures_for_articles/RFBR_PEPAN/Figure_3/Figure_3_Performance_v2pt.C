void Figure_3_Performance_v2pt()
{
//=========Macro generated from canvas: can/
//=========  (Sun Mar  7 10:45:01 2021) by ROOT version 6.19/01
   TCanvas *can = new TCanvas("can", "",0,0,2200,850);
   gStyle->SetOptStat(0);
   can->Range(0,0,1,1);
   can->SetFillColor(0);
   can->SetBorderMode(0);
   can->SetBorderSize(2);
   can->SetLeftMargin(0.04938272);
   can->SetRightMargin(0.002081995);
   can->SetTopMargin(0.06859821);
   can->SetBottomMargin(0.1195652);
   can->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: can_1
   TPad *can_1 = new TPad("can_1", "_1",0,0.5254835,0.2390898,0.9314018);
   can_1->Draw();
   can_1->cd();
   can_1->Range(-0.8368852,-0.01,2.35,0.13);
   can_1->SetFillColor(0);
   can_1->SetBorderMode(0);
   can_1->SetBorderSize(2);
   can_1->SetTickx(1);
   can_1->SetTicky(1);
   can_1->SetLeftMargin(0.2469136);
   can_1->SetRightMargin(0);
   can_1->SetTopMargin(0);
   can_1->SetBottomMargin(0);
   can_1->SetFrameBorderMode(0);
   can_1->SetFrameBorderMode(0);
   
   TH2F *pad_1__1 = new TH2F("pad_1__1","",1,-0.05,2.35,1,-0.01,0.13);
   pad_1__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   pad_1__1->SetLineColor(ci);
   pad_1__1->GetXaxis()->SetNdivisions(504);
   pad_1__1->GetXaxis()->SetLabelFont(42);
   pad_1__1->GetXaxis()->SetLabelSize(0.13);
   pad_1__1->GetXaxis()->SetTitleSize(0.13);
   pad_1__1->GetXaxis()->SetTitleOffset(0.9);
   pad_1__1->GetXaxis()->SetTitleFont(42);
   pad_1__1->GetYaxis()->SetTitle("v_{2} ");
   pad_1__1->GetYaxis()->SetNdivisions(504);
   pad_1__1->GetYaxis()->SetLabelFont(42);
   pad_1__1->GetYaxis()->SetLabelSize(0.13);
   pad_1__1->GetYaxis()->SetTitleSize(0.15);
   pad_1__1->GetYaxis()->SetTitleOffset(0.7);
   pad_1__1->GetYaxis()->SetTitleFont(42);
   pad_1__1->GetZaxis()->SetLabelFont(42);
   pad_1__1->GetZaxis()->SetLabelSize(0.035);
   pad_1__1->GetZaxis()->SetTitleSize(0.035);
   pad_1__1->GetZaxis()->SetTitleOffset(1);
   pad_1__1->GetZaxis()->SetTitleFont(42);
   pad_1__1->Draw("");
   TLatex *   tex = new TLatex(0.047,0.1235,"(a)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.1235,"Au+Au");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.104,"#sqrt{s_{NN}}=7.7 GeV");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.45,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("","open - reco","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","v_{2}{4}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t Graph0_fx1001[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1001[9] = {
   0.02612469,
   0.03561258,
   0.03997445,
   0.04573654,
   0.05402012,
   0.0620824,
   0.0742601,
   0.08460232,
   0.09611115};
   Double_t Graph0_fex1001[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[9] = {
   0.0002673839,
   0.0003440434,
   0.0004496186,
   0.0006025907,
   0.0008064001,
   0.0009599575,
   0.001458365,
   0.001980861,
   0.006486274};
   TGraphErrors *gre = new TGraphErrors(9,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01001->SetMinimum(0.01818329);
   Graph_Graph01001->SetMaximum(0.1102714);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1002[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1002[9] = {
   0.02591514,
   0.03567714,
   0.04066517,
   0.04636773,
   0.05435195,
   0.0610537,
   0.07405637,
   0.08801092,
   0.08600087};
   Double_t Graph1_fex1002[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1002[9] = {
   0.0007137566,
   0.000906018,
   0.001200649,
   0.001626582,
   0.002177758,
   0.002581654,
   0.003842238,
   0.005000086,
   0.0118484};
   gre = new TGraphErrors(9,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph11002->SetMinimum(0.01793659);
   Graph_Graph11002->SetMaximum(0.1051141);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("p");
   can_1->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_6
   TPad *can_6 = new TPad("can_6", "_6",0,0,0.2390898,0.5254835);
   can_6->Draw();
   can_6->cd();
   can_6->Range(-0.8368852,-0.054,2.35,0.13);
   can_6->SetFillColor(0);
   can_6->SetBorderMode(0);
   can_6->SetBorderSize(2);
   can_6->SetTickx(1);
   can_6->SetTicky(1);
   can_6->SetLeftMargin(0.2469136);
   can_6->SetRightMargin(0);
   can_6->SetTopMargin(0);
   can_6->SetBottomMargin(0.2391304);
   can_6->SetFrameBorderMode(0);
   can_6->SetFrameBorderMode(0);
   
   TH2F *pad_6__2 = new TH2F("pad_6__2","",1,-0.05,2.35,1,-0.01,0.13);
   pad_6__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_6__2->SetLineColor(ci);
   pad_6__2->GetXaxis()->SetNdivisions(504);
   pad_6__2->GetXaxis()->SetLabelFont(42);
   pad_6__2->GetXaxis()->SetLabelSize(0.105);
   pad_6__2->GetXaxis()->SetTitleSize(0.105);
   pad_6__2->GetXaxis()->SetTitleOffset(0.9);
   pad_6__2->GetXaxis()->SetTitleFont(42);
   pad_6__2->GetYaxis()->SetNdivisions(504);
   pad_6__2->GetYaxis()->SetLabelFont(42);
   pad_6__2->GetYaxis()->SetLabelSize(0.105);
   pad_6__2->GetYaxis()->SetTitleSize(0.105);
   pad_6__2->GetYaxis()->SetTitleOffset(0.7);
   pad_6__2->GetYaxis()->SetTitleFont(42);
   pad_6__2->GetZaxis()->SetLabelFont(42);
   pad_6__2->GetZaxis()->SetLabelSize(0.035);
   pad_6__2->GetZaxis()->SetTitleSize(0.035);
   pad_6__2->GetZaxis()->SetTitleOffset(1);
   pad_6__2->GetZaxis()->SetTitleFont(42);
   pad_6__2->Draw("");
      tex = new TLatex(0.047,0.1235,"(f)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.104,"#sqrt{s_{NN}}=11 GeV");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1003[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1003[9] = {
   0.02601629,
   0.03651046,
   0.03994316,
   0.0449438,
   0.05107443,
   0.05801047,
   0.06676175,
   0.07524918,
   0.08114935};
   Double_t Graph0_fex1003[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1003[9] = {
   0.0002535382,
   0.0003297229,
   0.0004273265,
   0.0005713429,
   0.0007783936,
   0.0009431881,
   0.001453653,
   0.001936188,
   0.005879637};
   gre = new TGraphErrors(9,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01003 = new TH1F("Graph_Graph01003","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01003->SetMinimum(0.01963613);
   Graph_Graph01003->SetMaximum(0.09315561);
   Graph_Graph01003->SetDirectory(0);
   Graph_Graph01003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01003->SetLineColor(ci);
   Graph_Graph01003->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01003->GetXaxis()->SetLabelFont(42);
   Graph_Graph01003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01003->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01003->GetXaxis()->SetTitleFont(42);
   Graph_Graph01003->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01003->GetYaxis()->SetLabelFont(42);
   Graph_Graph01003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01003->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01003->GetYaxis()->SetTitleFont(42);
   Graph_Graph01003->GetZaxis()->SetLabelFont(42);
   Graph_Graph01003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01003);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1004[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1004[9] = {
   0.02542395,
   0.03599189,
   0.0415811,
   0.04531325,
   0.05087911,
   0.06011915,
   0.06956042,
   0.07014043,
   0.05991534};
   Double_t Graph1_fex1004[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1004[9] = {
   0.0007933211,
   0.001024406,
   0.001346065,
   0.001813481,
   0.002486326,
   0.003024952,
   0.004558448,
   0.005738433,
   0.01279712};
   gre = new TGraphErrors(9,Graph1_fx1004,Graph1_fy1004,Graph1_fex1004,Graph1_fey1004);
   gre->SetName("Graph1");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11004 = new TH1F("Graph_Graph11004","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph11004->SetMinimum(0.01950581);
   Graph_Graph11004->SetMaximum(0.08100368);
   Graph_Graph11004->SetDirectory(0);
   Graph_Graph11004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11004->SetLineColor(ci);
   Graph_Graph11004->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11004->GetXaxis()->SetLabelFont(42);
   Graph_Graph11004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11004->GetXaxis()->SetTitleFont(42);
   Graph_Graph11004->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11004->GetYaxis()->SetLabelFont(42);
   Graph_Graph11004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11004->GetYaxis()->SetTitleFont(42);
   Graph_Graph11004->GetZaxis()->SetLabelFont(42);
   Graph_Graph11004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11004);
   
   gre->Draw("p");
   can_6->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_2
   TPad *can_2 = new TPad("can_2", "_2",0.2390898,0.5254835,0.4287968,0.9314018);
   can_2->Draw();
   can_2->cd();
   can_2->Range(-0.05,-0.01,2.35,0.13);
   can_2->SetFillColor(0);
   can_2->SetBorderMode(0);
   can_2->SetBorderSize(2);
   can_2->SetTickx(1);
   can_2->SetTicky(1);
   can_2->SetLeftMargin(0);
   can_2->SetRightMargin(0);
   can_2->SetTopMargin(0);
   can_2->SetBottomMargin(0);
   can_2->SetFrameBorderMode(0);
   can_2->SetFrameBorderMode(0);
   
   TH2F *pad_2__3 = new TH2F("pad_2__3","",1,-0.05,2.35,1,-0.01,0.13);
   pad_2__3->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_2__3->SetLineColor(ci);
   pad_2__3->GetXaxis()->SetNdivisions(504);
   pad_2__3->GetXaxis()->SetLabelFont(42);
   pad_2__3->GetXaxis()->SetLabelSize(0.13);
   pad_2__3->GetXaxis()->SetTitleSize(0.13);
   pad_2__3->GetXaxis()->SetTitleOffset(0.9);
   pad_2__3->GetXaxis()->SetTitleFont(42);
   pad_2__3->GetYaxis()->SetNdivisions(504);
   pad_2__3->GetYaxis()->SetLabelFont(42);
   pad_2__3->GetYaxis()->SetLabelSize(0.13);
   pad_2__3->GetYaxis()->SetTitleSize(0.15);
   pad_2__3->GetYaxis()->SetTitleOffset(0.7);
   pad_2__3->GetYaxis()->SetTitleFont(42);
   pad_2__3->GetZaxis()->SetLabelFont(42);
   pad_2__3->GetZaxis()->SetLabelSize(0.035);
   pad_2__3->GetZaxis()->SetTitleSize(0.035);
   pad_2__3->GetZaxis()->SetTitleOffset(1);
   pad_2__3->GetZaxis()->SetTitleFont(42);
   pad_2__3->Draw("");
      tex = new TLatex(0.047,0.1235,"(b)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.1235,"10-40%");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.4,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("","filled - true","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","v_{2}{2}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#cc0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t Graph0_fx1005[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1005[9] = {
   0.02746597,
   0.03751382,
   0.04235666,
   0.0488032,
   0.05649131,
   0.06571203,
   0.07728714,
   0.08924986,
   0.1016813};
   Double_t Graph0_fex1005[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1005[9] = {
   3.809492e-05,
   5.371225e-05,
   7.937654e-05,
   0.0001125217,
   0.0001529698,
   0.0001816794,
   0.0002855798,
   0.0004020891,
   0.001520861};
   gre = new TGraphErrors(9,Graph0_fx1005,Graph0_fy1005,Graph0_fex1005,Graph0_fey1005);
   gre->SetName("Graph0");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01005 = new TH1F("Graph_Graph01005","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph01005->SetMinimum(0.01985045);
   Graph_Graph01005->SetMaximum(0.1107796);
   Graph_Graph01005->SetDirectory(0);
   Graph_Graph01005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01005->SetLineColor(ci);
   Graph_Graph01005->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01005->GetXaxis()->SetLabelFont(42);
   Graph_Graph01005->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01005->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01005->GetXaxis()->SetTitleFont(42);
   Graph_Graph01005->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01005->GetYaxis()->SetLabelFont(42);
   Graph_Graph01005->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01005->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01005->GetYaxis()->SetTitleFont(42);
   Graph_Graph01005->GetZaxis()->SetLabelFont(42);
   Graph_Graph01005->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01005->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01005);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1006[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1006[9] = {
   0.02784517,
   0.03756291,
   0.04319467,
   0.04910002,
   0.05676095,
   0.06619601,
   0.07613476,
   0.08379591,
   0.08161218};
   Double_t Graph1_fex1006[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1006[9] = {
   9.623164e-05,
   0.0001341701,
   0.0001996058,
   0.0002847347,
   0.0003867896,
   0.000457951,
   0.000708549,
   0.0009393864,
   0.002527264};
   gre = new TGraphErrors(9,Graph1_fx1006,Graph1_fy1006,Graph1_fex1006,Graph1_fey1006);
   gre->SetName("Graph1");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11006 = new TH1F("Graph_Graph11006","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph11006->SetMinimum(0.02205031);
   Graph_Graph11006->SetMaximum(0.09043393);
   Graph_Graph11006->SetDirectory(0);
   Graph_Graph11006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11006->SetLineColor(ci);
   Graph_Graph11006->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11006->GetXaxis()->SetLabelFont(42);
   Graph_Graph11006->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11006->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11006->GetXaxis()->SetTitleFont(42);
   Graph_Graph11006->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11006->GetYaxis()->SetLabelFont(42);
   Graph_Graph11006->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11006->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11006->GetYaxis()->SetTitleFont(42);
   Graph_Graph11006->GetZaxis()->SetLabelFont(42);
   Graph_Graph11006->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11006->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11006);
   
   gre->Draw("p");
   can_2->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_7
   TPad *can_7 = new TPad("can_7", "_7",0.2390898,0,0.4287968,0.5254835);
   can_7->Draw();
   can_7->cd();
   can_7->Range(-0.05,-0.054,2.35,0.13);
   can_7->SetFillColor(0);
   can_7->SetBorderMode(0);
   can_7->SetBorderSize(2);
   can_7->SetTickx(1);
   can_7->SetTicky(1);
   can_7->SetLeftMargin(0);
   can_7->SetRightMargin(0);
   can_7->SetTopMargin(0);
   can_7->SetBottomMargin(0.2391304);
   can_7->SetFrameBorderMode(0);
   can_7->SetFrameBorderMode(0);
   
   TH2F *pad_7__4 = new TH2F("pad_7__4","",1,-0.05,2.35,1,-0.01,0.13);
   pad_7__4->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_7__4->SetLineColor(ci);
   pad_7__4->GetXaxis()->SetNdivisions(504);
   pad_7__4->GetXaxis()->SetLabelFont(42);
   pad_7__4->GetXaxis()->SetLabelSize(0.105);
   pad_7__4->GetXaxis()->SetTitleSize(0.105);
   pad_7__4->GetXaxis()->SetTitleOffset(0.9);
   pad_7__4->GetXaxis()->SetTitleFont(42);
   pad_7__4->GetYaxis()->SetNdivisions(504);
   pad_7__4->GetYaxis()->SetLabelFont(42);
   pad_7__4->GetYaxis()->SetLabelSize(0.105);
   pad_7__4->GetYaxis()->SetTitleSize(0.105);
   pad_7__4->GetYaxis()->SetTitleOffset(0.7);
   pad_7__4->GetYaxis()->SetTitleFont(42);
   pad_7__4->GetZaxis()->SetLabelFont(42);
   pad_7__4->GetZaxis()->SetLabelSize(0.035);
   pad_7__4->GetZaxis()->SetTitleSize(0.035);
   pad_7__4->GetZaxis()->SetTitleOffset(1);
   pad_7__4->GetZaxis()->SetTitleFont(42);
   pad_7__4->Draw("");
      tex = new TLatex(0.047,0.1235,"(g)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1007[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1007[9] = {
   0.02775082,
   0.03902442,
   0.04411408,
   0.04957653,
   0.05565405,
   0.06384158,
   0.0736634,
   0.08374048,
   0.09735831};
   Double_t Graph0_fex1007[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1007[9] = {
   3.84181e-05,
   5.428521e-05,
   8.182015e-05,
   0.0001196576,
   0.0001683165,
   0.0002025436,
   0.0003170973,
   0.0004340705,
   0.001518495};
   gre = new TGraphErrors(9,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph01007->SetMinimum(0.02059596);
   Graph_Graph01007->SetMaximum(0.1059933);
   Graph_Graph01007->SetDirectory(0);
   Graph_Graph01007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01007->SetLineColor(ci);
   Graph_Graph01007->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01007->GetXaxis()->SetLabelFont(42);
   Graph_Graph01007->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01007->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetXaxis()->SetTitleFont(42);
   Graph_Graph01007->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01007->GetYaxis()->SetLabelFont(42);
   Graph_Graph01007->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01007->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01007->GetYaxis()->SetTitleFont(42);
   Graph_Graph01007->GetZaxis()->SetLabelFont(42);
   Graph_Graph01007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01007);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1008[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1008[9] = {
   0.02804644,
   0.03934717,
   0.04470815,
   0.05000206,
   0.05600759,
   0.06379364,
   0.07191075,
   0.07856351,
   0.07705037};
   Double_t Graph1_fex1008[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1008[9] = {
   0.0001130518,
   0.0001574317,
   0.0002387416,
   0.0003515976,
   0.0004949868,
   0.0005946256,
   0.0009157363,
   0.00118067,
   0.002997706};
   gre = new TGraphErrors(9,Graph1_fx1008,Graph1_fy1008,Graph1_fex1008,Graph1_fey1008);
   gre->SetName("Graph1");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11008 = new TH1F("Graph_Graph11008","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph11008->SetMinimum(0.02272192);
   Graph_Graph11008->SetMaximum(0.08525955);
   Graph_Graph11008->SetDirectory(0);
   Graph_Graph11008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11008->SetLineColor(ci);
   Graph_Graph11008->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11008->GetXaxis()->SetLabelFont(42);
   Graph_Graph11008->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11008->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11008->GetXaxis()->SetTitleFont(42);
   Graph_Graph11008->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11008->GetYaxis()->SetLabelFont(42);
   Graph_Graph11008->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11008->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11008->GetYaxis()->SetTitleFont(42);
   Graph_Graph11008->GetZaxis()->SetLabelFont(42);
   Graph_Graph11008->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11008->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11008);
   
   gre->Draw("p");
   can_7->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_3
   TPad *can_3 = new TPad("can_3", "_3",0.4287968,0.5254835,0.6185039,0.9314018);
   can_3->Draw();
   can_3->cd();
   can_3->Range(-0.05,-0.01,2.35,0.13);
   can_3->SetFillColor(0);
   can_3->SetBorderMode(0);
   can_3->SetBorderSize(2);
   can_3->SetTickx(1);
   can_3->SetTicky(1);
   can_3->SetLeftMargin(0);
   can_3->SetRightMargin(0);
   can_3->SetTopMargin(0);
   can_3->SetBottomMargin(0);
   can_3->SetFrameBorderMode(0);
   can_3->SetFrameBorderMode(0);
   
   TH2F *pad_3__5 = new TH2F("pad_3__5","",1,-0.05,2.35,1,-0.01,0.13);
   pad_3__5->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_3__5->SetLineColor(ci);
   pad_3__5->GetXaxis()->SetNdivisions(504);
   pad_3__5->GetXaxis()->SetLabelFont(42);
   pad_3__5->GetXaxis()->SetLabelSize(0.13);
   pad_3__5->GetXaxis()->SetTitleSize(0.13);
   pad_3__5->GetXaxis()->SetTitleOffset(0.9);
   pad_3__5->GetXaxis()->SetTitleFont(42);
   pad_3__5->GetYaxis()->SetNdivisions(504);
   pad_3__5->GetYaxis()->SetLabelFont(42);
   pad_3__5->GetYaxis()->SetLabelSize(0.13);
   pad_3__5->GetYaxis()->SetTitleSize(0.15);
   pad_3__5->GetYaxis()->SetTitleOffset(0.7);
   pad_3__5->GetYaxis()->SetTitleFont(42);
   pad_3__5->GetZaxis()->SetLabelFont(42);
   pad_3__5->GetZaxis()->SetLabelSize(0.035);
   pad_3__5->GetZaxis()->SetTitleSize(0.035);
   pad_3__5->GetZaxis()->SetTitleOffset(1);
   pad_3__5->GetZaxis()->SetTitleFont(42);
   pad_3__5->Draw("");
      tex = new TLatex(0.047,0.1235,"(c)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.1235,"UrQMD");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.4,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph","v_{2}^{EP}{#Psi_{2,TPC}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fx1009[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fy1009[9] = {
   0.02916204,
   0.03871498,
   0.04376854,
   0.04943875,
   0.05678867,
   0.06598573,
   0.07795085,
   0.08836214,
   0.1036562};
   Double_t rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fex1009[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fey1009[9] = {
   0.0001807548,
   0.0002152911,
   0.000279422,
   0.000365155,
   0.000484685,
   0.0005784504,
   0.0009688017,
   0.001455312,
   0.006400567};
   gre = new TGraphErrors(9,rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fx1009,rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fy1009,rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fex1009,rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph_fey1009);
   gre->SetName("rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009 = new TH1F("Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009","GEANT",100,0,2.5);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->SetMinimum(0.02087374);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->SetMaximum(0.1181643);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->SetDirectory(0);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->SetLineColor(ci);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->SetLineWidth(3);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetXaxis()->SetLabelSize(0.05);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetXaxis()->SetTitleSize(0.06);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetXaxis()->SetTitleOffset(1);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetYaxis()->SetTitle("v_{2}");
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetYaxis()->SetLabelOffset(0.01);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetYaxis()->SetLabelSize(0.05);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetYaxis()->SetTitleSize(0.06);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetYaxis()->SetTitleOffset(1.3);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetZaxis()->SetLabelSize(0.05);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetZaxis()->SetTitleSize(0.06);
   Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_rebin_cent2_Rp_pv2PtTpc_Rp_gap0_pid8_graph1009);
   
   gre->Draw("p");
   
   Double_t rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fx1010[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fy1010[9] = {
   0.02908386,
   0.0387921,
   0.0439797,
   0.04954775,
   0.05677068,
   0.06572257,
   0.07589264,
   0.08683918,
   0.1035738};
   Double_t rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fex1010[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fey1010[9] = {
   0.0001804003,
   0.0002157154,
   0.0002802304,
   0.0003664199,
   0.0004865379,
   0.0005789018,
   0.0009589052,
   0.001384085,
   0.004932963};
   gre = new TGraphErrors(9,rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fx1010,rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fy1010,rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fex1010,rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph_fey1010);
   gre->SetName("rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010 = new TH1F("Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010","Reco",100,0,2.5);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->SetMinimum(0.02094314);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->SetMaximum(0.1164671);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->SetDirectory(0);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->SetLineColor(ci);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->SetLineWidth(3);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetXaxis()->SetLabelSize(0.05);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetXaxis()->SetTitleSize(0.06);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetXaxis()->SetTitleOffset(1);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetYaxis()->SetTitle("v_{2}");
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetYaxis()->SetLabelOffset(0.01);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetYaxis()->SetLabelSize(0.05);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetYaxis()->SetTitleSize(0.06);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetYaxis()->SetTitleOffset(1.3);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetZaxis()->SetLabelSize(0.05);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetZaxis()->SetTitleSize(0.06);
   Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_rebin_cent2_Ep_pv2PtTpc_Ep_gap0_pid8_graph1010);
   
   gre->Draw("p");
   can_3->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_8
   TPad *can_8 = new TPad("can_8", "_8",0.4287968,0,0.6185039,0.5254835);
   can_8->Draw();
   can_8->cd();
   can_8->Range(-0.05,-0.054,2.35,0.13);
   can_8->SetFillColor(0);
   can_8->SetBorderMode(0);
   can_8->SetBorderSize(2);
   can_8->SetTickx(1);
   can_8->SetTicky(1);
   can_8->SetLeftMargin(0);
   can_8->SetRightMargin(0);
   can_8->SetTopMargin(0);
   can_8->SetBottomMargin(0.2391304);
   can_8->SetFrameBorderMode(0);
   can_8->SetFrameBorderMode(0);
   
   TH2F *pad_8__6 = new TH2F("pad_8__6","",1,-0.05,2.35,1,-0.01,0.13);
   pad_8__6->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_8__6->SetLineColor(ci);
   pad_8__6->GetXaxis()->SetTitle("p_{T} (GeV/c)        ");
   pad_8__6->GetXaxis()->SetNdivisions(504);
   pad_8__6->GetXaxis()->SetLabelFont(42);
   pad_8__6->GetXaxis()->SetLabelSize(0.105);
   pad_8__6->GetXaxis()->SetTitleSize(0.105);
   pad_8__6->GetXaxis()->SetTitleOffset(0.9);
   pad_8__6->GetXaxis()->SetTitleFont(42);
   pad_8__6->GetYaxis()->SetTitle("v_{2}");
   pad_8__6->GetYaxis()->SetNdivisions(504);
   pad_8__6->GetYaxis()->SetLabelFont(42);
   pad_8__6->GetYaxis()->SetLabelSize(0.105);
   pad_8__6->GetYaxis()->SetTitleSize(0.105);
   pad_8__6->GetYaxis()->SetTitleOffset(0.7);
   pad_8__6->GetYaxis()->SetTitleFont(42);
   pad_8__6->GetZaxis()->SetLabelFont(42);
   pad_8__6->GetZaxis()->SetLabelSize(0.035);
   pad_8__6->GetZaxis()->SetTitleSize(0.035);
   pad_8__6->GetZaxis()->SetTitleOffset(1);
   pad_8__6->GetZaxis()->SetTitleFont(42);
   pad_8__6->Draw("");
      tex = new TLatex(0.047,0.1235,"(h)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1011[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1011[9] = {
   0.028031,
   0.03942446,
   0.04438863,
   0.04968497,
   0.05562997,
   0.06374289,
   0.07397547,
   0.08413764,
   0.0994503};
   Double_t Graph0_fex1011[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1011[9] = {
   4.498255e-05,
   5.830687e-05,
   7.876227e-05,
   0.0001058928,
   0.0001425862,
   0.0001702821,
   0.0002808779,
   0.0004069119,
   0.001586931};
   gre = new TGraphErrors(9,Graph0_fx1011,Graph0_fy1011,Graph0_fex1011,Graph0_fey1011);
   gre->SetName("Graph0");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph01011 = new TH1F("Graph_Graph01011","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph01011->SetMinimum(0.02068089);
   Graph_Graph01011->SetMaximum(0.1083423);
   Graph_Graph01011->SetDirectory(0);
   Graph_Graph01011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01011->SetLineColor(ci);
   Graph_Graph01011->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01011->GetXaxis()->SetLabelFont(42);
   Graph_Graph01011->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01011->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01011->GetXaxis()->SetTitleFont(42);
   Graph_Graph01011->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01011->GetYaxis()->SetLabelFont(42);
   Graph_Graph01011->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01011->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01011->GetYaxis()->SetTitleFont(42);
   Graph_Graph01011->GetZaxis()->SetLabelFont(42);
   Graph_Graph01011->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01011->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01011->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01011);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1012[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1012[9] = {
   0.02808432,
   0.03985997,
   0.04486758,
   0.05017304,
   0.05646423,
   0.06391482,
   0.07234785,
   0.08005064,
   0.07300971};
   Double_t Graph1_fex1012[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1012[9] = {
   0.0001326964,
   0.0001704502,
   0.0002305845,
   0.0003118032,
   0.0004218988,
   0.0005043354,
   0.0008204464,
   0.00110655,
   0.003118947};
   gre = new TGraphErrors(9,Graph1_fx1012,Graph1_fy1012,Graph1_fex1012,Graph1_fey1012);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph11012 = new TH1F("Graph_Graph11012","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11012->SetMinimum(0.02263106);
   Graph_Graph11012->SetMaximum(0.08647775);
   Graph_Graph11012->SetDirectory(0);
   Graph_Graph11012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11012->SetLineColor(ci);
   Graph_Graph11012->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11012->GetXaxis()->SetLabelFont(42);
   Graph_Graph11012->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11012->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11012->GetXaxis()->SetTitleFont(42);
   Graph_Graph11012->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11012->GetYaxis()->SetLabelFont(42);
   Graph_Graph11012->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11012->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11012->GetYaxis()->SetTitleFont(42);
   Graph_Graph11012->GetZaxis()->SetLabelFont(42);
   Graph_Graph11012->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11012->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11012->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11012);
   
   gre->Draw("p");
   can_8->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_4
   TPad *can_4 = new TPad("can_4", "_4",0.6185039,0.5254835,0.8082109,0.9314018);
   can_4->Draw();
   can_4->cd();
   can_4->Range(-0.05,-0.01,2.35,0.13);
   can_4->SetFillColor(0);
   can_4->SetBorderMode(0);
   can_4->SetBorderSize(2);
   can_4->SetTickx(1);
   can_4->SetTicky(1);
   can_4->SetLeftMargin(0);
   can_4->SetRightMargin(0);
   can_4->SetTopMargin(0);
   can_4->SetBottomMargin(0);
   can_4->SetFrameBorderMode(0);
   can_4->SetFrameBorderMode(0);
   
   TH2F *pad_4__7 = new TH2F("pad_4__7","",1,-0.05,2.35,1,-0.01,0.13);
   pad_4__7->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_4__7->SetLineColor(ci);
   pad_4__7->GetXaxis()->SetNdivisions(504);
   pad_4__7->GetXaxis()->SetLabelFont(42);
   pad_4__7->GetXaxis()->SetLabelSize(0.13);
   pad_4__7->GetXaxis()->SetTitleSize(0.13);
   pad_4__7->GetXaxis()->SetTitleOffset(0.9);
   pad_4__7->GetXaxis()->SetTitleFont(42);
   pad_4__7->GetYaxis()->SetNdivisions(504);
   pad_4__7->GetYaxis()->SetLabelFont(42);
   pad_4__7->GetYaxis()->SetLabelSize(0.13);
   pad_4__7->GetYaxis()->SetTitleSize(0.15);
   pad_4__7->GetYaxis()->SetTitleOffset(0.7);
   pad_4__7->GetYaxis()->SetTitleFont(42);
   pad_4__7->GetZaxis()->SetLabelFont(42);
   pad_4__7->GetZaxis()->SetLabelSize(0.035);
   pad_4__7->GetZaxis()->SetTitleSize(0.035);
   pad_4__7->GetZaxis()->SetTitleOffset(1);
   pad_4__7->GetZaxis()->SetTitleFont(42);
   pad_4__7->Draw("");
      tex = new TLatex(0.047,0.1235,"(d)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.1235,"GEANT4");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.4,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("gr_rebinned_cent_10_40_pv2TPC_pid0","v_{2}^{SP}{Q_{2,TPC}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009999");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fx1013[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fy1013[9] = {
   0.02777519,
   0.03785371,
   0.04271375,
   0.04912028,
   0.05684823,
   0.0661715,
   0.07749809,
   0.08924317,
   0.1022279};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fex1013[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fey1013[9] = {
   3.22236e-05,
   4.140241e-05,
   5.433063e-05,
   7.098624e-05,
   9.407323e-05,
   0.0001120595,
   0.0001873331,
   0.0002805322,
   0.001177756};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid0_fx1013,gr_rebinned_cent_10_40_pv2TPC_pid0_fy1013,gr_rebinned_cent_10_40_pv2TPC_pid0_fex1013,gr_rebinned_cent_10_40_pv2TPC_pid0_fey1013);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid0");
   gre->SetTitle("v2(TPC EP) MODEL of hadron_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009999");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009999");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013","v2(TPC EP) MODEL of hadron_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->SetMinimum(0.02017669);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->SetMaximum(0.110972);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid01013);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fx1014[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fy1014[9] = {
   0.02798054,
   0.03796906,
   0.04358734,
   0.0494319,
   0.05712329,
   0.06622941,
   0.07632418,
   0.08348867,
   0.0844541};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fex1014[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fey1014[9] = {
   0.000160345,
   0.0002042843,
   0.0002687276,
   0.0003531933,
   0.0004701097,
   0.0005599041,
   0.0009198126,
   0.001278718,
   0.003776335};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid0_fx1014,gr_rebinned_cent_10_40_pv2TPC_pid0_fy1014,gr_rebinned_cent_10_40_pv2TPC_pid0_fex1014,gr_rebinned_cent_10_40_pv2TPC_pid0_fey1014);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid0");
   gre->SetTitle("v2(TPC EP) MODEL of hadron_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009999");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009999");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(32);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014","v2(TPC EP) MODEL of hadron_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->SetMinimum(0.02177917);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->SetMaximum(0.09427146);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid01014);
   
   gre->Draw("p");
   can_4->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_9
   TPad *can_9 = new TPad("can_9", "_9",0.6185039,0,0.8082109,0.5254835);
   can_9->Draw();
   can_9->cd();
   can_9->Range(-0.05,-0.054,2.35,0.13);
   can_9->SetFillColor(0);
   can_9->SetBorderMode(0);
   can_9->SetBorderSize(2);
   can_9->SetTickx(1);
   can_9->SetTicky(1);
   can_9->SetLeftMargin(0);
   can_9->SetRightMargin(0);
   can_9->SetTopMargin(0);
   can_9->SetBottomMargin(0.2391304);
   can_9->SetFrameBorderMode(0);
   can_9->SetFrameBorderMode(0);
   
   TH2F *pad_9__8 = new TH2F("pad_9__8","",1,-0.05,2.35,1,-0.01,0.13);
   pad_9__8->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_9__8->SetLineColor(ci);
   pad_9__8->GetXaxis()->SetNdivisions(504);
   pad_9__8->GetXaxis()->SetLabelFont(42);
   pad_9__8->GetXaxis()->SetLabelSize(0.105);
   pad_9__8->GetXaxis()->SetTitleSize(0.105);
   pad_9__8->GetXaxis()->SetTitleOffset(0.9);
   pad_9__8->GetXaxis()->SetTitleFont(42);
   pad_9__8->GetYaxis()->SetNdivisions(504);
   pad_9__8->GetYaxis()->SetLabelFont(42);
   pad_9__8->GetYaxis()->SetLabelSize(0.105);
   pad_9__8->GetYaxis()->SetTitleSize(0.105);
   pad_9__8->GetYaxis()->SetTitleOffset(0.7);
   pad_9__8->GetYaxis()->SetTitleFont(42);
   pad_9__8->GetZaxis()->SetLabelFont(42);
   pad_9__8->GetZaxis()->SetLabelSize(0.035);
   pad_9__8->GetZaxis()->SetTitleSize(0.035);
   pad_9__8->GetZaxis()->SetTitleOffset(1);
   pad_9__8->GetZaxis()->SetTitleFont(42);
   pad_9__8->Draw("");
      tex = new TLatex(0.047,0.1235,"(i)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fx1015[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fy1015[9] = {
   0.02800815,
   0.03937693,
   0.04459146,
   0.04997474,
   0.05611033,
   0.06432551,
   0.07428556,
   0.08458431,
   0.0982566};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fex1015[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fey1015[9] = {
   3.395009e-05,
   4.39983e-05,
   5.942753e-05,
   7.989961e-05,
   0.0001075949,
   0.0001284835,
   0.0002119936,
   0.0003071772,
   0.00119912};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid0_fx1015,gr_rebinned_cent_10_40_pv2TPC_pid0_fy1015,gr_rebinned_cent_10_40_pv2TPC_pid0_fex1015,gr_rebinned_cent_10_40_pv2TPC_pid0_fey1015);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid0");
   gre->SetTitle("v2(TPC EP) MODEL of hadron_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009999");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009999");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015","v2(TPC EP) MODEL of hadron_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->SetMinimum(0.02082605);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->SetMaximum(0.1066039);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid01015);
   
   gre->Draw("p");
   
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fx1016[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fy1016[9] = {
   0.02829015,
   0.03963346,
   0.04508781,
   0.05037864,
   0.05651518,
   0.0644335,
   0.07261352,
   0.07959028,
   0.07774726};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fex1016[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gr_rebinned_cent_10_40_pv2TPC_pid0_fey1016[9] = {
   0.0001234153,
   0.0001585221,
   0.0002144345,
   0.0002899981,
   0.0003923952,
   0.0004691691,
   0.0007629473,
   0.001030295,
   0.002900513};
   gre = new TGraphErrors(9,gr_rebinned_cent_10_40_pv2TPC_pid0_fx1016,gr_rebinned_cent_10_40_pv2TPC_pid0_fy1016,gr_rebinned_cent_10_40_pv2TPC_pid0_fex1016,gr_rebinned_cent_10_40_pv2TPC_pid0_fey1016);
   gre->SetName("gr_rebinned_cent_10_40_pv2TPC_pid0");
   gre->SetTitle("v2(TPC EP) MODEL of hadron_pos");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#009999");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009999");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(32);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016 = new TH1F("Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016","v2(TPC EP) MODEL of hadron_pos",100,0.055,2.995);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->SetMinimum(0.02291863);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->SetMaximum(0.08589588);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->SetDirectory(0);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->SetLineColor(ci);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->SetLineWidth(3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetXaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetXaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetXaxis()->SetTitleOffset(1);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetYaxis()->SetTitle("v_{2}");
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetYaxis()->SetLabelOffset(0.01);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetYaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetYaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetYaxis()->SetTitleOffset(1.3);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetZaxis()->SetLabelSize(0.05);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetZaxis()->SetTitleSize(0.06);
   Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_gr_rebinned_cent_10_40_pv2TPC_pid01016);
   
   gre->Draw("p");
   can_9->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_5
   TPad *can_5 = new TPad("can_5", "_5",0.8082109,0.5254835,0.997918,0.9314018);
   can_5->Draw();
   can_5->cd();
   can_5->Range(-0.05,-0.01,2.35,0.13);
   can_5->SetFillColor(0);
   can_5->SetBorderMode(0);
   can_5->SetBorderSize(2);
   can_5->SetTickx(1);
   can_5->SetTicky(1);
   can_5->SetLeftMargin(0);
   can_5->SetRightMargin(0);
   can_5->SetTopMargin(0);
   can_5->SetBottomMargin(0);
   can_5->SetFrameBorderMode(0);
   can_5->SetFrameBorderMode(0);
   
   TH2F *pad_5__9 = new TH2F("pad_5__9","",1,-0.05,2.35,1,-0.01,0.13);
   pad_5__9->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_5__9->SetLineColor(ci);
   pad_5__9->GetXaxis()->SetNdivisions(504);
   pad_5__9->GetXaxis()->SetLabelFont(42);
   pad_5__9->GetXaxis()->SetLabelSize(0.13);
   pad_5__9->GetXaxis()->SetTitleSize(0.13);
   pad_5__9->GetXaxis()->SetTitleOffset(0.9);
   pad_5__9->GetXaxis()->SetTitleFont(42);
   pad_5__9->GetYaxis()->SetNdivisions(504);
   pad_5__9->GetYaxis()->SetLabelFont(42);
   pad_5__9->GetYaxis()->SetLabelSize(0.13);
   pad_5__9->GetYaxis()->SetTitleSize(0.15);
   pad_5__9->GetYaxis()->SetTitleOffset(0.7);
   pad_5__9->GetYaxis()->SetTitleFont(42);
   pad_5__9->GetZaxis()->SetLabelFont(42);
   pad_5__9->GetZaxis()->SetLabelSize(0.035);
   pad_5__9->GetZaxis()->SetTitleSize(0.035);
   pad_5__9->GetZaxis()->SetTitleOffset(1);
   pad_5__9->GetZaxis()->SetTitleFont(42);
   pad_5__9->Draw("");
      tex = new TLatex(0.047,0.1235,"(e)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3525,0.1235,"Ch. hadrons");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.13);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.35,0.05,0.99,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.12);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("proff_mc_graph","v_{2}^{EP}{#Psi_{1,FHCal}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(2.5);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t proff_mc_graph_fx1017[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_mc_graph_fy1017[9] = {
   0.02600655,
   0.0352547,
   0.03949341,
   0.04527763,
   0.05204933,
   0.06210925,
   0.07254493,
   0.08203632,
   0.09543643};
   Double_t proff_mc_graph_fex1017[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_mc_graph_fey1017[9] = {
   4.427462e-05,
   5.378335e-05,
   7.028072e-05,
   9.23788e-05,
   0.0001231609,
   0.0001360637,
   0.0003302781,
   0.000357185,
   0.001419277};
   gre = new TGraphErrors(9,proff_mc_graph_fx1017,proff_mc_graph_fy1017,proff_mc_graph_fex1017,proff_mc_graph_fey1017);
   gre->SetName("proff_mc_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(33);
   gre->SetMarkerSize(2.5);
   
   TH1F *Graph_proff_mc_graph1017 = new TH1F("Graph_proff_mc_graph1017","GEANT",100,0.055,2.995);
   Graph_proff_mc_graph1017->SetMinimum(0.01887293);
   Graph_proff_mc_graph1017->SetMaximum(0.103945);
   Graph_proff_mc_graph1017->SetDirectory(0);
   Graph_proff_mc_graph1017->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_mc_graph1017->SetLineColor(ci);
   Graph_proff_mc_graph1017->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_mc_graph1017->GetXaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1017->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1017->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1017->GetXaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1017->GetXaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1017->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_mc_graph1017->GetYaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1017->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1017->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1017->GetYaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1017->GetZaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1017->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1017->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1017->GetZaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_mc_graph1017);
   
   gre->Draw("p");
   
   Double_t proff_reco_graph_fx1018[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_reco_graph_fy1018[9] = {
   0.02677075,
   0.03598412,
   0.04030034,
   0.0463489,
   0.05249674,
   0.06241203,
   0.07290166,
   0.0814938,
   0.09651238};
   Double_t proff_reco_graph_fex1018[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_reco_graph_fey1018[9] = {
   8.097438e-05,
   9.842325e-05,
   0.0001287335,
   0.0001694092,
   0.0002261689,
   0.0002502785,
   0.0006087193,
   0.0006595926,
   0.002628711};
   gre = new TGraphErrors(9,proff_reco_graph_fx1018,proff_reco_graph_fy1018,proff_reco_graph_fex1018,proff_reco_graph_fey1018);
   gre->SetName("proff_reco_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(2.5);
   
   TH1F *Graph_proff_reco_graph1018 = new TH1F("Graph_proff_reco_graph1018","Reco",100,0.055,2.995);
   Graph_proff_reco_graph1018->SetMinimum(0.01944464);
   Graph_proff_reco_graph1018->SetMaximum(0.1063862);
   Graph_proff_reco_graph1018->SetDirectory(0);
   Graph_proff_reco_graph1018->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_reco_graph1018->SetLineColor(ci);
   Graph_proff_reco_graph1018->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_reco_graph1018->GetXaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1018->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1018->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1018->GetXaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1018->GetXaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1018->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_reco_graph1018->GetYaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1018->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1018->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1018->GetYaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1018->GetZaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1018->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1018->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1018->GetZaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1018->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_reco_graph1018);
   
   gre->Draw("p");
   can_5->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_10
   TPad *can_10 = new TPad("can_10", "_10",0.8082109,0,0.997918,0.5254835);
   can_10->Draw();
   can_10->cd();
   can_10->Range(-0.05,-0.054,2.35,0.13);
   can_10->SetFillColor(0);
   can_10->SetBorderMode(0);
   can_10->SetBorderSize(2);
   can_10->SetTickx(1);
   can_10->SetTicky(1);
   can_10->SetLeftMargin(0);
   can_10->SetRightMargin(0);
   can_10->SetTopMargin(0);
   can_10->SetBottomMargin(0.2391304);
   can_10->SetFrameBorderMode(0);
   can_10->SetFrameBorderMode(0);
   
   TH2F *pad_10__10 = new TH2F("pad_10__10","",1,-0.05,2.35,1,-0.01,0.13);
   pad_10__10->SetStats(0);

   ci = TColor::GetColor("#000099");
   pad_10__10->SetLineColor(ci);
   pad_10__10->GetXaxis()->SetNdivisions(504);
   pad_10__10->GetXaxis()->SetLabelFont(42);
   pad_10__10->GetXaxis()->SetLabelSize(0.105);
   pad_10__10->GetXaxis()->SetTitleSize(0.105);
   pad_10__10->GetXaxis()->SetTitleOffset(0.9);
   pad_10__10->GetXaxis()->SetTitleFont(42);
   pad_10__10->GetYaxis()->SetNdivisions(504);
   pad_10__10->GetYaxis()->SetLabelFont(42);
   pad_10__10->GetYaxis()->SetLabelSize(0.105);
   pad_10__10->GetYaxis()->SetTitleSize(0.105);
   pad_10__10->GetYaxis()->SetTitleOffset(0.7);
   pad_10__10->GetYaxis()->SetTitleFont(42);
   pad_10__10->GetZaxis()->SetLabelFont(42);
   pad_10__10->GetZaxis()->SetLabelSize(0.035);
   pad_10__10->GetZaxis()->SetTitleSize(0.035);
   pad_10__10->GetZaxis()->SetTitleOffset(1);
   pad_10__10->GetZaxis()->SetTitleFont(42);
   pad_10__10->Draw("");
      tex = new TLatex(0.047,0.1235,"(j)");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.105);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t proff_mc_graph_fx1019[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_mc_graph_fy1019[9] = {
   0.02562751,
   0.0353491,
   0.03976516,
   0.0437013,
   0.04840895,
   0.05616532,
   0.06448288,
   0.07118497,
   0.07875861};
   Double_t proff_mc_graph_fex1019[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_mc_graph_fey1019[9] = {
   5.945834e-05,
   7.292375e-05,
   9.804742e-05,
   0.0001326716,
   0.0001800654,
   0.0002001904,
   0.0004808573,
   0.0005077712,
   0.00189591};
   gre = new TGraphErrors(9,proff_mc_graph_fx1019,proff_mc_graph_fy1019,proff_mc_graph_fex1019,proff_mc_graph_fey1019);
   gre->SetName("proff_mc_graph");
   gre->SetTitle("GEANT");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(33);
   gre->SetMarkerSize(2.5);
   
   TH1F *Graph_proff_mc_graph1019 = new TH1F("Graph_proff_mc_graph1019","GEANT",100,0.055,2.995);
   Graph_proff_mc_graph1019->SetMinimum(0.02005941);
   Graph_proff_mc_graph1019->SetMaximum(0.08616316);
   Graph_proff_mc_graph1019->SetDirectory(0);
   Graph_proff_mc_graph1019->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_mc_graph1019->SetLineColor(ci);
   Graph_proff_mc_graph1019->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_mc_graph1019->GetXaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1019->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1019->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1019->GetXaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1019->GetXaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1019->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_mc_graph1019->GetYaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1019->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1019->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1019->GetYaxis()->SetTitleFont(42);
   Graph_proff_mc_graph1019->GetZaxis()->SetLabelFont(42);
   Graph_proff_mc_graph1019->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_mc_graph1019->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_mc_graph1019->GetZaxis()->SetTitleOffset(1);
   Graph_proff_mc_graph1019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_mc_graph1019);
   
   gre->Draw("p");
   
   Double_t proff_reco_graph_fx1020[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t proff_reco_graph_fy1020[9] = {
   0.02560943,
   0.03516713,
   0.0393223,
   0.04326678,
   0.04723893,
   0.05511756,
   0.06184402,
   0.06869879,
   0.07558622};
   Double_t proff_reco_graph_fex1020[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t proff_reco_graph_fey1020[9] = {
   0.0001024594,
   0.0001257134,
   0.0001691237,
   0.0002290222,
   0.0003110102,
   0.0003461226,
   0.0008325285,
   0.0008801278,
   0.003287768};
   gre = new TGraphErrors(9,proff_reco_graph_fx1020,proff_reco_graph_fy1020,proff_reco_graph_fex1020,proff_reco_graph_fey1020);
   gre->SetName("proff_reco_graph");
   gre->SetTitle("Reco");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(2.5);
   
   TH1F *Graph_proff_reco_graph1020 = new TH1F("Graph_proff_reco_graph1020","Reco",100,0.055,2.995);
   Graph_proff_reco_graph1020->SetMinimum(0.02017027);
   Graph_proff_reco_graph1020->SetMaximum(0.08421069);
   Graph_proff_reco_graph1020->SetDirectory(0);
   Graph_proff_reco_graph1020->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_proff_reco_graph1020->SetLineColor(ci);
   Graph_proff_reco_graph1020->GetXaxis()->SetTitle("p_{T}, GeV/c");
   Graph_proff_reco_graph1020->GetXaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1020->GetXaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1020->GetXaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1020->GetXaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1020->GetXaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1020->GetYaxis()->SetTitle("v_{2}");
   Graph_proff_reco_graph1020->GetYaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1020->GetYaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1020->GetYaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1020->GetYaxis()->SetTitleFont(42);
   Graph_proff_reco_graph1020->GetZaxis()->SetLabelFont(42);
   Graph_proff_reco_graph1020->GetZaxis()->SetLabelSize(0.035);
   Graph_proff_reco_graph1020->GetZaxis()->SetTitleSize(0.035);
   Graph_proff_reco_graph1020->GetZaxis()->SetTitleOffset(1);
   Graph_proff_reco_graph1020->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_proff_reco_graph1020);
   
   gre->Draw("p");
   can_10->Modified();
   can->cd();
   can->Modified();
   can->cd();
   can->SetSelected(can);
}
