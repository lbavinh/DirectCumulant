void v2pt_Reco()
{
//=========Macro generated from canvas: can/
//=========  (Mon Sep 28 20:07:22 2020) by ROOT version 6.19/01
   TCanvas *can = new TCanvas("can", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   can->Range(0,0,1,1);
   can->SetFillColor(10);
   can->SetBorderMode(0);
   can->SetBorderSize(2);
   can->SetTickx(1);
   can->SetTicky(1);
   can->SetLeftMargin(0.08230453);
   can->SetRightMargin(0.003593133);
   can->SetTopMargin(0.0505618);
   can->SetBottomMargin(0.1111111);
   can->SetFrameLineWidth(3);
  
// ------------>Primitives in pad: can_1
   TPad *can_1 = new TPad("can_1", "_1",0,0.5302747,0.3870053,0.9494382);
   can_1->Draw();
   can_1->cd();
   can_1->Range(0,0,1,1);
   can_1->SetFillColor(10);
   can_1->SetBorderMode(0);
   can_1->SetBorderSize(2);
   can_1->SetTickx(1);
   can_1->SetTicky(1);
   can_1->SetLeftMargin(0.2469136);
   can_1->SetRightMargin(0);
   can_1->SetTopMargin(0);
   can_1->SetBottomMargin(0);
   can_1->SetFrameLineWidth(3);
   
   TH2F *pad_1__1 = new TH2F("pad_1__1","",1,-0.05,2.35,1,-0.01,0.16);
   pad_1__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   pad_1__1->SetLineColor(ci);
   pad_1__1->SetLineWidth(3);
   pad_1__1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   pad_1__1->GetXaxis()->SetNdivisions(504);
   pad_1__1->GetXaxis()->SetLabelSize(0.07);
   pad_1__1->GetXaxis()->SetTitleSize(0.1);
   pad_1__1->GetXaxis()->SetTitleOffset(1);
   pad_1__1->GetYaxis()->SetTitle("v_{2}              ");
   pad_1__1->GetYaxis()->SetNdivisions(504);
   pad_1__1->GetYaxis()->SetLabelOffset(0.01);
   pad_1__1->GetYaxis()->SetLabelSize(0.07);
   pad_1__1->GetYaxis()->SetTitleSize(0.1);
   pad_1__1->GetYaxis()->SetTitleOffset(1);
   pad_1__1->GetZaxis()->SetLabelSize(0.05);
   pad_1__1->GetZaxis()->SetTitleSize(0.06);
   pad_1__1->GetZaxis()->SetTitleOffset(1);
   pad_1__1->Draw("");
   TLatex *   tex = new TLatex(2.115,0.144,"#splitline{UrQMD, Au+Au, centrality 10-40%}{h^{#pm} @ #sqrt{s_{NN}}=7.7 GeV}");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.07);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0,0,0,0,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.07);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(3);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","v_{2}{4}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","v_{2}{2,|#Delta#eta|>0.1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","v_{2}{#eta-sub,EP} TPC","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
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
   0.02645503,
   0.03617733,
   0.04021962,
   0.04399374,
   0.05539924,
   0.0609212,
   0.07241366,
   0.08109262,
   0.09005823};
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
   0.001097731,
   0.001394864,
   0.001838784,
   0.002487429,
   0.003370912,
   0.003972149,
   0.005908023,
   0.007640306,
   0.01803807};
   TGraphErrors *gre = new TGraphErrors(9,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01001->SetMinimum(0.0170834);
   Graph_Graph01001->SetMaximum(0.1163702);
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
   0.02826083,
   0.03805786,
   0.04348969,
   0.04908979,
   0.05664388,
   0.06489341,
   0.07502985,
   0.0814498,
   0.08484653};
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
   0.0001693657,
   0.0002158096,
   0.0002839301,
   0.0003732414,
   0.0004967978,
   0.0005913349,
   0.0009715186,
   0.001350181,
   0.003986009};
   gre = new TGraphErrors(9,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11002->SetMinimum(0.02201736);
   Graph_Graph11002->SetMaximum(0.09490664);
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
   
   Double_t Graph2_fx1003[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1003[9] = {
   0.02776224,
   0.03772257,
   0.04334053,
   0.04901709,
   0.05682009,
   0.06559666,
   0.07576618,
   0.08265125,
   0.08460644};
   Double_t Graph2_fex1003[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1003[9] = {
   0.0001485756,
   0.0002067437,
   0.0003076302,
   0.0004387537,
   0.0005959229,
   0.0007056425,
   0.00108999,
   0.001444402,
   0.00386245};
   gre = new TGraphErrors(9,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21003->SetMinimum(0.02152815);
   Graph_Graph21003->SetMaximum(0.09455441);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   Graph_Graph21003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph21003->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   Graph_Graph21003->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   Graph_Graph21003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph21003->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph21003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("p");
   can_1->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_4
   TPad *can_4 = new TPad("can_4", "_4",0,0,0.3870053,0.5302747);
   can_4->Draw();
   can_4->cd();
   can_4->Range(0,0,1,1);
   can_4->SetFillColor(10);
   can_4->SetBorderMode(0);
   can_4->SetBorderSize(2);
   can_4->SetTickx(1);
   can_4->SetTicky(1);
   can_4->SetLeftMargin(0.2469136);
   can_4->SetRightMargin(0);
   can_4->SetTopMargin(0);
   can_4->SetBottomMargin(0.2222222);
   can_4->SetFrameLineWidth(3);
   
   TH2F *pad_4__2 = new TH2F("pad_4__2","",1,-0.05,2.35,1,-0.01,0.16);
   pad_4__2->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   pad_4__2->SetLineColor(ci);
   pad_4__2->SetLineWidth(3);
   pad_4__2->GetXaxis()->SetNdivisions(504);
   pad_4__2->GetXaxis()->SetLabelSize(0.07);
   pad_4__2->GetXaxis()->SetTitleSize(0.1);
   pad_4__2->GetXaxis()->SetTitleOffset(1);
   pad_4__2->GetYaxis()->SetNdivisions(504);
   pad_4__2->GetYaxis()->SetLabelOffset(0.01);
   pad_4__2->GetYaxis()->SetLabelSize(0.07);
   pad_4__2->GetYaxis()->SetTitleSize(0.1);
   pad_4__2->GetYaxis()->SetTitleOffset(1);
   pad_4__2->GetZaxis()->SetLabelSize(0.05);
   pad_4__2->GetZaxis()->SetTitleSize(0.06);
   pad_4__2->GetZaxis()->SetTitleOffset(1);
   pad_4__2->Draw("");
      tex = new TLatex(2.115,0.144,"h^{#pm} @ #sqrt{s_{NN}}=11.5 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.07);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1004[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1004[9] = {
   0.02505812,
   0.03580792,
   0.04131135,
   0.04585289,
   0.05230501,
   0.06025732,
   0.07088959,
   0.06953886,
   0.06399866};
   Double_t Graph0_fex1004[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1004[9] = {
   0.0006601158,
   0.0008618193,
   0.001177432,
   0.001634901,
   0.002284897,
   0.002793956,
   0.004247098,
   0.005352914,
   0.01188404};
   gre = new TGraphErrors(9,Graph0_fx1004,Graph0_fy1004,Graph0_fex1004,Graph0_fey1004);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph01004 = new TH1F("Graph_Graph01004","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01004->SetMinimum(0.01924954);
   Graph_Graph01004->SetMaximum(0.08103118);
   Graph_Graph01004->SetDirectory(0);
   Graph_Graph01004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01004->SetLineColor(ci);
   Graph_Graph01004->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01004->GetXaxis()->SetLabelFont(42);
   Graph_Graph01004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetXaxis()->SetTitleFont(42);
   Graph_Graph01004->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01004->GetYaxis()->SetLabelFont(42);
   Graph_Graph01004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01004->GetYaxis()->SetTitleFont(42);
   Graph_Graph01004->GetZaxis()->SetLabelFont(42);
   Graph_Graph01004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01004);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1005[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1005[9] = {
   0.02822728,
   0.03973254,
   0.04496679,
   0.05002416,
   0.05632953,
   0.06372083,
   0.07260601,
   0.07952262,
   0.06937824};
   Double_t Graph1_fex1005[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1005[9] = {
   0.000143463,
   0.000184278,
   0.0002492898,
   0.0003370829,
   0.0004561165,
   0.0005452945,
   0.000887226,
   0.001196145,
   0.003372089};
   gre = new TGraphErrors(9,Graph1_fx1005,Graph1_fy1005,Graph1_fex1005,Graph1_fey1005);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph11005 = new TH1F("Graph_Graph11005","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11005->SetMinimum(0.02282032);
   Graph_Graph11005->SetMaximum(0.08598226);
   Graph_Graph11005->SetDirectory(0);
   Graph_Graph11005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11005->SetLineColor(ci);
   Graph_Graph11005->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11005->GetXaxis()->SetLabelFont(42);
   Graph_Graph11005->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11005->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11005->GetXaxis()->SetTitleFont(42);
   Graph_Graph11005->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11005->GetYaxis()->SetLabelFont(42);
   Graph_Graph11005->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11005->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11005->GetYaxis()->SetTitleFont(42);
   Graph_Graph11005->GetZaxis()->SetLabelFont(42);
   Graph_Graph11005->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11005->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11005);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1006[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1006[9] = {
   0.02809336,
   0.03924966,
   0.04466833,
   0.04990532,
   0.05602611,
   0.06375453,
   0.07211774,
   0.07835103,
   0.07427787};
   Double_t Graph2_fex1006[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1006[9] = {
   9.369935e-05,
   0.0001356116,
   0.0002164599,
   0.0003264049,
   0.0004642229,
   0.0005591843,
   0.0008660648,
   0.001118642,
   0.002848618};
   gre = new TGraphErrors(9,Graph2_fx1006,Graph2_fy1006,Graph2_fex1006,Graph2_fey1006);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph21006 = new TH1F("Graph_Graph21006","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21006->SetMinimum(0.02285266);
   Graph_Graph21006->SetMaximum(0.08461667);
   Graph_Graph21006->SetDirectory(0);
   Graph_Graph21006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21006->SetLineColor(ci);
   Graph_Graph21006->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21006->GetXaxis()->SetLabelFont(42);
   Graph_Graph21006->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph21006->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph21006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21006->GetXaxis()->SetTitleFont(42);
   Graph_Graph21006->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21006->GetYaxis()->SetLabelFont(42);
   Graph_Graph21006->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph21006->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph21006->GetYaxis()->SetTitleFont(42);
   Graph_Graph21006->GetZaxis()->SetLabelFont(42);
   Graph_Graph21006->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph21006->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph21006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21006);
   
   gre->Draw("p");
   can_4->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_2
   TPad *can_2 = new TPad("can_2", "_2",0.3870053,0.5302747,0.6917061,0.9494382);
   can_2->Draw();
   can_2->cd();
   can_2->Range(0,0,1,1);
   can_2->SetFillColor(10);
   can_2->SetBorderMode(0);
   can_2->SetBorderSize(2);
   can_2->SetTickx(1);
   can_2->SetTicky(1);
   can_2->SetLeftMargin(0);
   can_2->SetRightMargin(0);
   can_2->SetTopMargin(0);
   can_2->SetBottomMargin(0);
   can_2->SetFrameLineWidth(3);
   
   TH2F *pad_2__3 = new TH2F("pad_2__3","",1,-0.05,2.35,1,-0.01,0.16);
   pad_2__3->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   pad_2__3->SetLineColor(ci);
   pad_2__3->SetLineWidth(3);
   pad_2__3->GetXaxis()->SetNdivisions(504);
   pad_2__3->GetXaxis()->SetLabelSize(0.07);
   pad_2__3->GetXaxis()->SetTitleSize(0.1);
   pad_2__3->GetXaxis()->SetTitleOffset(1);
   pad_2__3->GetYaxis()->SetNdivisions(504);
   pad_2__3->GetYaxis()->SetLabelOffset(0.01);
   pad_2__3->GetYaxis()->SetLabelSize(0.07);
   pad_2__3->GetYaxis()->SetTitleSize(0.1);
   pad_2__3->GetYaxis()->SetTitleOffset(1);
   pad_2__3->GetZaxis()->SetLabelSize(0.05);
   pad_2__3->GetZaxis()->SetTitleSize(0.06);
   pad_2__3->GetZaxis()->SetTitleOffset(1);
   pad_2__3->Draw("");
      tex = new TLatex(2.115,0.144,"#pi^{+} @ #sqrt{s_{NN}}=7.7 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.07);
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
   0.02797708,
   0.04079845,
   0.05043911,
   0.052074,
   0.06051665,
   0.05982468,
   0.07628347,
   0.08163597,
   0.08060857};
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
   0.001711954,
   0.002272887,
   0.003224191,
   0.004762761,
   0.006908143,
   0.008626105,
   0.01364372,
   0.01897798,
   0.05195758};
   gre = new TGraphErrors(9,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01007->SetMinimum(0.01563502);
   Graph_Graph01007->SetMaximum(0.1431962);
   Graph_Graph01007->SetDirectory(0);
   Graph_Graph01007->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01007->SetLineColor(ci);
   Graph_Graph01007->SetLineWidth(3);
   Graph_Graph01007->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01007->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01007->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01007->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01007->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01007->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01007->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01007->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01007->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01007->GetZaxis()->SetTitleOffset(1);
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
   0.03006743,
   0.04421693,
   0.05201943,
   0.05689286,
   0.05994987,
   0.06409116,
   0.06808025,
   0.07390927,
   0.07800037};
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
   0.0002572129,
   0.0003570448,
   0.000533197,
   0.0008013759,
   0.001193356,
   0.001561415,
   0.002783627,
   0.004067501,
   0.01151798};
   gre = new TGraphErrors(9,Graph1_fx1008,Graph1_fy1008,Graph1_fex1008,Graph1_fey1008);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph11008 = new TH1F("Graph_Graph11008","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11008->SetMinimum(0.02383941);
   Graph_Graph11008->SetMaximum(0.09548916);
   Graph_Graph11008->SetDirectory(0);
   Graph_Graph11008->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11008->SetLineColor(ci);
   Graph_Graph11008->SetLineWidth(3);
   Graph_Graph11008->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11008->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11008->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11008->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11008->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11008->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11008->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11008->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11008->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11008->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11008->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11008);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1009[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1009[9] = {
   0.02960383,
   0.04387097,
   0.05138736,
   0.05649242,
   0.06018048,
   0.06274121,
   0.06824718,
   0.07690238,
   0.07139572};
   Double_t Graph2_fex1009[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1009[9] = {
   0.0002575867,
   0.000376012,
   0.0005970367,
   0.0009169269,
   0.001320091,
   0.001666004,
   0.002782167,
   0.003972879,
   0.01097728};
   gre = new TGraphErrors(9,Graph2_fx1009,Graph2_fy1009,Graph2_fex1009,Graph2_fey1009);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph21009 = new TH1F("Graph_Graph21009","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21009->SetMinimum(0.02404356);
   Graph_Graph21009->SetMaximum(0.08767568);
   Graph_Graph21009->SetDirectory(0);
   Graph_Graph21009->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21009->SetLineColor(ci);
   Graph_Graph21009->SetLineWidth(3);
   Graph_Graph21009->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21009->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21009->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21009->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21009->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21009->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21009->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21009->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21009->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21009->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21009->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21009);
   
   gre->Draw("p");
   can_2->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_5
   TPad *can_5 = new TPad("can_5", "_5",0.3870053,0,0.6917061,0.5302747);
   can_5->Draw();
   can_5->cd();
   can_5->Range(0,0,1,1);
   can_5->SetFillColor(10);
   can_5->SetBorderMode(0);
   can_5->SetBorderSize(2);
   can_5->SetTickx(1);
   can_5->SetTicky(1);
   can_5->SetLeftMargin(0);
   can_5->SetRightMargin(0);
   can_5->SetTopMargin(0);
   can_5->SetBottomMargin(0.2222222);
   can_5->SetFrameLineWidth(3);
   
   TH2F *pad_5__4 = new TH2F("pad_5__4","",1,-0.05,2.35,1,-0.01,0.16);
   pad_5__4->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   pad_5__4->SetLineColor(ci);
   pad_5__4->SetLineWidth(3);
   pad_5__4->GetXaxis()->SetTitle("p_{T} [GeV/c]         ");
   pad_5__4->GetXaxis()->SetNdivisions(504);
   pad_5__4->GetXaxis()->SetLabelSize(0.07);
   pad_5__4->GetXaxis()->SetTitleSize(0.1);
   pad_5__4->GetXaxis()->SetTitleOffset(1);
   pad_5__4->GetYaxis()->SetTitle("v_{2}");
   pad_5__4->GetYaxis()->SetNdivisions(504);
   pad_5__4->GetYaxis()->SetLabelOffset(0.01);
   pad_5__4->GetYaxis()->SetLabelSize(0.07);
   pad_5__4->GetYaxis()->SetTitleSize(0.1);
   pad_5__4->GetYaxis()->SetTitleOffset(1);
   pad_5__4->GetZaxis()->SetLabelSize(0.05);
   pad_5__4->GetZaxis()->SetTitleSize(0.06);
   pad_5__4->GetZaxis()->SetTitleOffset(1);
   pad_5__4->Draw("");
      tex = new TLatex(2.115,0.144,"#pi^{+} @ #sqrt{s_{NN}}=11.5 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.07);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1010[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1010[9] = {
   0.0267234,
   0.03919498,
   0.04677173,
   0.05293144,
   0.05962029,
   0.05662508,
   0.0608671,
   0.07552013,
   0.04487918};
   Double_t Graph0_fex1010[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1010[9] = {
   0.001084779,
   0.001447579,
   0.002025214,
   0.002979217,
   0.004405359,
   0.005563092,
   0.008658275,
   0.01134907,
   0.02784579};
   gre = new TGraphErrors(9,Graph0_fx1010,Graph0_fy1010,Graph0_fex1010,Graph0_fey1010);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph01010 = new TH1F("Graph_Graph01010","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01010->SetMinimum(0.01004982);
   Graph_Graph01010->SetMaximum(0.09385278);
   Graph_Graph01010->SetDirectory(0);
   Graph_Graph01010->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01010->SetLineColor(ci);
   Graph_Graph01010->SetLineWidth(3);
   Graph_Graph01010->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01010->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01010->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01010->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01010->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01010->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01010->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01010->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01010->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01010->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01010->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01010);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1011[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1011[9] = {
   0.02952963,
   0.04440473,
   0.0527375,
   0.05736159,
   0.06091196,
   0.06151316,
   0.06709512,
   0.07198086,
   0.07202636};
   Double_t Graph1_fex1011[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1011[9] = {
   0.0002139418,
   0.0002920523,
   0.0004312987,
   0.0006428694,
   0.0009512629,
   0.001232045,
   0.002150611,
   0.00302637,
   0.008328945};
   gre = new TGraphErrors(9,Graph1_fx1011,Graph1_fy1011,Graph1_fex1011,Graph1_fey1011);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph11011 = new TH1F("Graph_Graph11011","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11011->SetMinimum(0.02421173);
   Graph_Graph11011->SetMaximum(0.08545927);
   Graph_Graph11011->SetDirectory(0);
   Graph_Graph11011->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11011->SetLineColor(ci);
   Graph_Graph11011->SetLineWidth(3);
   Graph_Graph11011->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11011->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11011->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11011->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11011->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11011->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11011->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11011->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11011->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11011->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11011->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11011);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1012[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1012[9] = {
   0.02941793,
   0.04380626,
   0.05223901,
   0.05735991,
   0.06037317,
   0.06180354,
   0.06791435,
   0.07102222,
   0.07817144};
   Double_t Graph2_fex1012[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1012[9] = {
   0.0001764931,
   0.0002544792,
   0.0004060813,
   0.0006363669,
   0.0009363535,
   0.001177937,
   0.001915433,
   0.002610306,
   0.006947089};
   gre = new TGraphErrors(9,Graph2_fx1012,Graph2_fy1012,Graph2_fex1012,Graph2_fey1012);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph21012 = new TH1F("Graph_Graph21012","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21012->SetMinimum(0.02365373);
   Graph_Graph21012->SetMaximum(0.09070624);
   Graph_Graph21012->SetDirectory(0);
   Graph_Graph21012->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21012->SetLineColor(ci);
   Graph_Graph21012->SetLineWidth(3);
   Graph_Graph21012->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21012->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21012->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21012->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21012->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21012->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21012->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21012->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21012->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21012->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21012->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21012);
   
   gre->Draw("p");
   can_5->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_3
   TPad *can_3 = new TPad("can_3", "_3",0.6917061,0.5302747,0.9964069,0.9494382);
   can_3->Draw();
   can_3->cd();
   can_3->Range(0,0,1,1);
   can_3->SetFillColor(10);
   can_3->SetBorderMode(0);
   can_3->SetBorderSize(2);
   can_3->SetTickx(1);
   can_3->SetTicky(1);
   can_3->SetLeftMargin(0);
   can_3->SetRightMargin(0);
   can_3->SetTopMargin(0);
   can_3->SetBottomMargin(0);
   can_3->SetFrameLineWidth(3);
   
   TH2F *pad_3__5 = new TH2F("pad_3__5","",1,-0.05,2.35,1,-0.01,0.16);
   pad_3__5->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   pad_3__5->SetLineColor(ci);
   pad_3__5->SetLineWidth(3);
   pad_3__5->GetXaxis()->SetNdivisions(504);
   pad_3__5->GetXaxis()->SetLabelSize(0.07);
   pad_3__5->GetXaxis()->SetTitleSize(0.1);
   pad_3__5->GetXaxis()->SetTitleOffset(1);
   pad_3__5->GetYaxis()->SetNdivisions(504);
   pad_3__5->GetYaxis()->SetLabelOffset(0.01);
   pad_3__5->GetYaxis()->SetLabelSize(0.07);
   pad_3__5->GetYaxis()->SetTitleSize(0.1);
   pad_3__5->GetYaxis()->SetTitleOffset(1);
   pad_3__5->GetZaxis()->SetLabelSize(0.05);
   pad_3__5->GetZaxis()->SetTitleSize(0.06);
   pad_3__5->GetZaxis()->SetTitleOffset(1);
   pad_3__5->Draw("");
      tex = new TLatex(2.115,0.144,"p @ #sqrt{s_{NN}}=7.7 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.07);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1013[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1013[9] = {
   0.006976457,
   0.01470501,
   0.02649291,
   0.03837974,
   0.05487764,
   0.06227264,
   0.07091811,
   0.08199231,
   0.07828185};
   Double_t Graph0_fex1013[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1013[9] = {
   0.004481305,
   0.003157693,
   0.002957315,
   0.003301412,
   0.004050531,
   0.004556545,
   0.006905949,
   0.00893762,
   0.02156896};
   gre = new TGraphErrors(9,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph01013 = new TH1F("Graph_Graph01013","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01013->SetMinimum(0.002245637);
   Graph_Graph01013->SetMaximum(0.1095864);
   Graph_Graph01013->SetDirectory(0);
   Graph_Graph01013->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01013->SetLineColor(ci);
   Graph_Graph01013->SetLineWidth(3);
   Graph_Graph01013->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01013->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01013->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01013->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01013->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01013->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01013->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01013->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01013->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01013->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01013);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1014[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1014[9] = {
   0.006388102,
   0.01448612,
   0.02926841,
   0.04267433,
   0.05543573,
   0.06662478,
   0.07853945,
   0.08519922,
   0.09173641};
   Double_t Graph1_fex1014[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1014[9] = {
   0.0007657158,
   0.0005460012,
   0.0005092236,
   0.0005555251,
   0.0006705227,
   0.000751447,
   0.001185401,
   0.00161227,
   0.004839738};
   gre = new TGraphErrors(9,Graph1_fx1014,Graph1_fy1014,Graph1_fex1014,Graph1_fey1014);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph11014 = new TH1F("Graph_Graph11014","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11014->SetMinimum(0.005060147);
   Graph_Graph11014->SetMaximum(0.1056715);
   Graph_Graph11014->SetDirectory(0);
   Graph_Graph11014->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11014->SetLineColor(ci);
   Graph_Graph11014->SetLineWidth(3);
   Graph_Graph11014->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11014->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11014->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11014->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11014->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11014->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11014->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11014->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11014->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11014->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11014->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11014->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11014);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1015[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1015[9] = {
   0.005861129,
   0.01499064,
   0.03003088,
   0.04291547,
   0.0560408,
   0.06834322,
   0.07994505,
   0.08628982,
   0.09506057};
   Double_t Graph2_fex1015[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1015[9] = {
   0.0008846816,
   0.0006179665,
   0.0005690045,
   0.0006266328,
   0.0007669211,
   0.0008624409,
   0.001311052,
   0.001711409,
   0.004681649};
   gre = new TGraphErrors(9,Graph2_fx1015,Graph2_fy1015,Graph2_fex1015,Graph2_fey1015);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph21015 = new TH1F("Graph_Graph21015","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21015->SetMinimum(0.004478803);
   Graph_Graph21015->SetMaximum(0.1092188);
   Graph_Graph21015->SetDirectory(0);
   Graph_Graph21015->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21015->SetLineColor(ci);
   Graph_Graph21015->SetLineWidth(3);
   Graph_Graph21015->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21015->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21015->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21015->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21015->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21015->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21015->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21015->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21015->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21015->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21015->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21015->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21015);
   
   gre->Draw("p");
   can_3->Modified();
   can->cd();
  
// ------------>Primitives in pad: can_6
   TPad *can_6 = new TPad("can_6", "_6",0.6917061,0,0.9964069,0.5302747);
   can_6->Draw();
   can_6->cd();
   can_6->Range(0,0,1,1);
   can_6->SetFillColor(10);
   can_6->SetBorderMode(0);
   can_6->SetBorderSize(2);
   can_6->SetTickx(1);
   can_6->SetTicky(1);
   can_6->SetLeftMargin(0);
   can_6->SetRightMargin(0);
   can_6->SetTopMargin(0);
   can_6->SetBottomMargin(0.2222222);
   can_6->SetFrameLineWidth(3);
   
   TH2F *pad_6__6 = new TH2F("pad_6__6","",1,-0.05,2.35,1,-0.01,0.16);
   pad_6__6->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   pad_6__6->SetLineColor(ci);
   pad_6__6->SetLineWidth(3);
   pad_6__6->GetXaxis()->SetNdivisions(504);
   pad_6__6->GetXaxis()->SetLabelSize(0.07);
   pad_6__6->GetXaxis()->SetTitleSize(0.1);
   pad_6__6->GetXaxis()->SetTitleOffset(1);
   pad_6__6->GetYaxis()->SetNdivisions(504);
   pad_6__6->GetYaxis()->SetLabelOffset(0.01);
   pad_6__6->GetYaxis()->SetLabelSize(0.07);
   pad_6__6->GetYaxis()->SetTitleSize(0.1);
   pad_6__6->GetYaxis()->SetTitleOffset(1);
   pad_6__6->GetZaxis()->SetLabelSize(0.05);
   pad_6__6->GetZaxis()->SetTitleSize(0.06);
   pad_6__6->GetZaxis()->SetTitleOffset(1);
   pad_6__6->Draw("");
      tex = new TLatex(2.115,0.144,"p @ #sqrt{s_{NN}}=11.5 GeV");
   tex->SetTextAlign(33);
   tex->SetTextFont(42);
   tex->SetTextSize(0.07);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t Graph0_fx1016[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph0_fy1016[9] = {
   0.00589094,
   0.007509106,
   0.02392134,
   0.03590614,
   0.04849385,
   0.06249802,
   0.08055016,
   0.07332147,
   0.0811371};
   Double_t Graph0_fex1016[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1016[9] = {
   0.003922878,
   0.002737767,
   0.002528698,
   0.002746344,
   0.003311255,
   0.003675,
   0.005490554,
   0.006804386,
   0.01578429};
   gre = new TGraphErrors(9,Graph0_fx1016,Graph0_fy1016,Graph0_fex1016,Graph0_fey1016);
   gre->SetName("Graph0");
   gre->SetTitle("[2] v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph01016 = new TH1F("Graph_Graph01016","[2] v_{2}{4}",100,0.055,2.995);
   Graph_Graph01016->SetMinimum(0.001771256);
   Graph_Graph01016->SetMaximum(0.1064167);
   Graph_Graph01016->SetDirectory(0);
   Graph_Graph01016->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph01016->SetLineColor(ci);
   Graph_Graph01016->SetLineWidth(3);
   Graph_Graph01016->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01016->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01016->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01016->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01016->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01016->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01016->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01016->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01016->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph01016->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01016->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01016->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph01016);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1017[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph1_fy1017[9] = {
   0.004611417,
   0.01347124,
   0.02507743,
   0.03976339,
   0.05322956,
   0.06606124,
   0.07747672,
   0.08474336,
   0.07346793};
   Double_t Graph1_fex1017[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1017[9] = {
   0.0008497493,
   0.0006048231,
   0.000559303,
   0.0006022643,
   0.0007149294,
   0.0007848879,
   0.001204544,
   0.001573872,
   0.004522449};
   gre = new TGraphErrors(9,Graph1_fx1017,Graph1_fy1017,Graph1_fex1017,Graph1_fey1017);
   gre->SetName("Graph1");
   gre->SetTitle("[3] v_{2}{#eta-sub,EP}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph11017 = new TH1F("Graph_Graph11017","[3] v_{2}{#eta-sub,EP}",100,0.055,2.995);
   Graph_Graph11017->SetMinimum(0.003385501);
   Graph_Graph11017->SetMaximum(0.09457279);
   Graph_Graph11017->SetDirectory(0);
   Graph_Graph11017->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph11017->SetLineColor(ci);
   Graph_Graph11017->SetLineWidth(3);
   Graph_Graph11017->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11017->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph11017->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11017->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11017->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11017->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph11017->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph11017->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11017->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph11017->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11017->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11017->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph11017);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1018[9] = {
   0.3,
   0.5,
   0.7,
   0.9,
   1.1,
   1.35,
   1.65,
   2.15,
   2.75};
   Double_t Graph2_fy1018[9] = {
   0.004421808,
   0.01345248,
   0.02610822,
   0.0402175,
   0.05326459,
   0.06691435,
   0.07743129,
   0.08439847,
   0.07725478};
   Double_t Graph2_fex1018[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1018[9] = {
   0.0008519301,
   0.0006039285,
   0.000552758,
   0.0005975989,
   0.000713186,
   0.0007815032,
   0.001152443,
   0.001453479,
   0.003806548};
   gre = new TGraphErrors(9,Graph2_fx1018,Graph2_fy1018,Graph2_fex1018,Graph2_fey1018);
   gre->SetName("Graph2");
   gre->SetTitle("[1] v_{2}{2,|#Delta#eta|>0.1}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph21018 = new TH1F("Graph_Graph21018","[1] v_{2}{2,|#Delta#eta|>0.1}",100,0.055,2.995);
   Graph_Graph21018->SetMinimum(0.00321289);
   Graph_Graph21018->SetMaximum(0.09408015);
   Graph_Graph21018->SetDirectory(0);
   Graph_Graph21018->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_Graph21018->SetLineColor(ci);
   Graph_Graph21018->SetLineWidth(3);
   Graph_Graph21018->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21018->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph21018->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph21018->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21018->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21018->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph21018->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph21018->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph21018->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph21018->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph21018->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph21018->GetZaxis()->SetTitleOffset(1);
   gre->SetHistogram(Graph_Graph21018);
   
   gre->Draw("p");
   can_6->Modified();
   can->cd();
   can->Modified();
   can->cd();
   can->SetSelected(can);
}
