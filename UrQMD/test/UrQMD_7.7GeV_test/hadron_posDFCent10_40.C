void hadron_posDFCent10_40()
{
//=========Macro generated from canvas: c1/Canvas
//=========  (Fri Apr 23 20:00:15 2021) by ROOT version 6.22/08
   TCanvas *c1 = new TCanvas("c1", "Canvas",0,0,550,550);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1001[33] = {
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
   Double_t Graph0_fy1001[33] = {
   0.001608632,
   0.006110893,
   0.0107627,
   0.01595101,
   0.02094552,
   0.02520375,
   0.0287769,
   0.03084085,
   0.03278409,
   0.03367346,
   0.03481008,
   0.03542479,
   0.03738004,
   0.04067769,
   0.0448934,
   0.04955864,
   0.05417596,
   0.05904502,
   0.06305291,
   0.06748897,
   0.07231576,
   0.07630986,
   0.07961133,
   0.08423316,
   0.08708497,
   0.08834271,
   0.09386064,
   0.09620333,
   0.09656344,
   0.09834357,
   0.1015077,
   0.09994171,
   0.1065981};
   Double_t Graph0_fex1001[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1001[33] = {
   0.0003909568,
   0.0001867715,
   0.000146279,
   0.0001345275,
   0.0001300815,
   0.0001325047,
   0.0001374473,
   0.0001437342,
   0.0001506461,
   0.0001579389,
   0.000165432,
   0.0001731065,
   0.0001289625,
   0.0001413393,
   0.0001556299,
   0.000172789,
   0.0001937974,
   0.0002196579,
   0.0002516018,
   0.0002911534,
   0.0003399443,
   0.0004002612,
   0.0004748209,
   0.0005661479,
   0.0006792753,
   0.0008174726,
   0.0009884456,
   0.001198115,
   0.001455482,
   0.001770269,
   0.00215907,
   0.002044827,
   0.002727306};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
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
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","",100,0,3);
   Graph_Graph01001->SetMinimum(-0.01);
   Graph_Graph01001->SetMaximum(0.2);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1002[33] = {
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
   Double_t Graph1_fy1002[33] = {
   -7.249693e-05,
   0.006117362,
   0.01114567,
   0.01601594,
   0.02073872,
   0.02474343,
   0.02815985,
   0.03020652,
   0.03176125,
   0.03321375,
   0.0338976,
   0.03462578,
   0.03646115,
   0.03924213,
   0.04285654,
   0.04774936,
   0.05191781,
   0.0563973,
   0.06047297,
   0.06523792,
   0.07008134,
   0.07331952,
   0.07629611,
   0.07885792,
   0.08142565,
   0.08395536,
   0.08666182,
   0.092378,
   0.09307476,
   0.095111,
   0.09382258,
   0.1014653,
   0.09804166};
   Double_t Graph1_fex1002[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1002[33] = {
   0.0007529267,
   0.000353731,
   0.0002744901,
   0.0002519333,
   0.0002493503,
   0.0002556682,
   0.0002664776,
   0.0002791635,
   0.0002929669,
   0.0003073174,
   0.0003219453,
   0.0003368854,
   0.0002588453,
   0.0002836034,
   0.0003124441,
   0.0003473598,
   0.0003892505,
   0.0004403359,
   0.0005030638,
   0.0005808068,
   0.0006762849,
   0.000793848,
   0.0009388554,
   0.001117603,
   0.001338568,
   0.001608395,
   0.001941799,
   0.002351524,
   0.002858884,
   0.003476139,
   0.004237786,
   0.00401408,
   0.005361778};
   gre = new TGraphErrors(33,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11002->SetMinimum(-0.0114559);
   Graph_Graph11002->SetMaximum(0.1161099);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1003[33] = {
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
   Double_t Graph2_fy1003[33] = {
   -0.1101968,
   -0.1052929,
   -0.1006523,
   -0.09591002,
   0.02079086,
   0.02550665,
   0.02905771,
   0.03110277,
   0.03238787,
   0.03268789,
   0.03320611,
   0.03355859,
   0.03490615,
   0.0378946,
   0.04218047,
   0.0469802,
   0.05170526,
   0.05673678,
   0.06129492,
   0.0661872,
   0.0706164,
   0.07471948,
   0.07830785,
   0.08198617,
   0.08547374,
   0.08753004,
   0.09099497,
   0.09332791,
   0.09477768,
   0.09593964,
   0.09964964,
   0.09895041,
   0.1042881};
   Double_t Graph2_fex1003[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1003[33] = {
   0.0003105427,
   0.0001556607,
   0.0001229378,
   0.0001128255,
   9.838478e-05,
   0.000100402,
   0.0001045831,
   0.0001099242,
   0.0001157995,
   0.000121968,
   0.0001282867,
   0.0001346744,
   0.0001007419,
   0.0001106645,
   0.0001218129,
   0.0001348855,
   0.0001505963,
   0.0001695919,
   0.0001928805,
   0.0002215423,
   0.0002568974,
   0.0003006726,
   0.0003548589,
   0.0004216145,
   0.0005038153,
   0.0006052537,
   0.0007303765,
   0.0008829205,
   0.001071672,
   0.001303044,
   0.00158666,
   0.001502294,
   0.002000549};
   gre = new TGraphErrors(33,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","v_{2}{2}",100,0,3.1325);
   Graph_Graph21003->SetMinimum(-0.1321869);
   Graph_Graph21003->SetMaximum(0.1279682);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   Graph_Graph21003->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1004[33] = {
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
   Double_t Graph3_fy1004[33] = {
   0.005534881,
   0.006574883,
   0.01007242,
   0.01519563,
   0.01990314,
   0.02417734,
   0.02688875,
   0.02953001,
   0.03108416,
   0.03242238,
   0.03272642,
   0.03443146,
   0.03518077,
   0.03767669,
   0.04179668,
   0.04535462,
   0.05281246,
   0.05693721,
   0.0594487,
   0.06335984,
   0.06718151,
   0.0727508,
   0.07790562,
   0.07981799,
   0.07907687,
   0.0861317,
   0.0837575,
   0.08747926,
   0.08798862,
   0.09669523,
   0.1067974,
   0.0968415,
   0.1014284};
   Double_t Graph3_fex1004[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1004[33] = {
   0.001908075,
   0.0009430857,
   0.0007262306,
   0.0006561947,
   0.0006299024,
   0.0006449897,
   0.0006731846,
   0.0007073485,
   0.0007432595,
   0.0007812134,
   0.0008191108,
   0.0008575905,
   0.0006452283,
   0.0007043471,
   0.0007721299,
   0.0008496759,
   0.0009449126,
   0.001053484,
   0.001183409,
   0.001345134,
   0.001544297,
   0.001793859,
   0.002102344,
   0.002471002,
   0.002923848,
   0.003507226,
   0.004215778,
   0.00506504,
   0.006137742,
   0.007443774,
   0.009066797,
   0.008565103,
   0.01136864};
   gre = new TGraphErrors(33,Graph3_fx1004,Graph3_fy1004,Graph3_fex1004,Graph3_fey1004);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31004 = new TH1F("Graph_Graph31004","v_{2}{4}",100,0,3.1325);
   Graph_Graph31004->SetMinimum(0.003264125);
   Graph_Graph31004->SetMaximum(0.1270879);
   Graph_Graph31004->SetDirectory(0);
   Graph_Graph31004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31004->SetLineColor(ci);
   Graph_Graph31004->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31004->GetXaxis()->SetLabelFont(42);
   Graph_Graph31004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetXaxis()->SetTitleFont(42);
   Graph_Graph31004->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31004->GetYaxis()->SetLabelFont(42);
   Graph_Graph31004->GetYaxis()->SetTitleFont(42);
   Graph_Graph31004->GetZaxis()->SetLabelFont(42);
   Graph_Graph31004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31004);
   
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
   pt_LaTex = pt->AddText("10-40%, h+");
   pt->Draw();
   padUp->Modified();
   c1->cd();
  
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
   
   Double_t Graph0_fx1005[33] = {
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
   Double_t Graph0_fy1005[33] = {
   0.04506744,
   1.001059,
   1.035583,
   1.004071,
   0.9901267,
   0.9817358,
   0.9785574,
   0.9794319,
   0.9688009,
   0.9863479,
   0.9737868,
   0.9774448,
   0.9754177,
   0.9647091,
   0.9546289,
   0.9634921,
   0.9583182,
   0.9551576,
   0.9590829,
   0.9666457,
   0.9691018,
   0.9608132,
   0.9583574,
   0.9361861,
   0.9350138,
   0.9503372,
   0.9233031,
   0.9602371,
   0.9638716,
   0.9671298,
   0.9242906,
   1.015245,
   0.9197318};
   Double_t Graph0_fex1005[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1005[33] = {
   0.4681822,
   0.06547388,
   0.02912985,
   0.01792109,
   0.01339904,
   0.01138161,
   0.01037281,
   0.01013756,
   0.009983715,
   0.01023199,
   0.01034185,
   0.01064197,
   0.0076991,
   0.0077359,
   0.007706437,
   0.007772497,
   0.00796084,
   0.008260906,
   0.008848833,
   0.009563103,
   0.01040241,
   0.0115594,
   0.01310518,
   0.01468441,
   0.01701334,
   0.02021885,
   0.02285914,
   0.02721187,
   0.03297881,
   0.03940154,
   0.0461458,
   0.04521774,
   0.05553117};
   gre = new TGraphErrors(33,Graph0_fx1005,Graph0_fy1005,Graph0_fex1005,Graph0_fey1005);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01005 = new TH1F("Graph_Graph01005","",100,0,3);
   Graph_Graph01005->SetMinimum(0.84);
   Graph_Graph01005->SetMaximum(1.16);
   Graph_Graph01005->SetDirectory(0);
   Graph_Graph01005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01005->SetLineColor(ci);
   Graph_Graph01005->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01005->GetXaxis()->SetLabelFont(42);
   Graph_Graph01005->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01005->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01005->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01005->GetXaxis()->SetTitleFont(42);
   Graph_Graph01005->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01005->GetYaxis()->CenterTitle(true);
   Graph_Graph01005->GetYaxis()->SetNdivisions(504);
   Graph_Graph01005->GetYaxis()->SetLabelFont(42);
   Graph_Graph01005->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01005->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01005->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01005->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01005->GetYaxis()->SetTitleFont(42);
   Graph_Graph01005->GetZaxis()->SetLabelFont(42);
   Graph_Graph01005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01005);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1006[33] = {
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
   Double_t Graph0_fy1006[33] = {
   0.04506744,
   1.001059,
   1.035583,
   1.004071,
   0.9901267,
   0.9817358,
   0.9785574,
   0.9794319,
   0.9688009,
   0.9863479,
   0.9737868,
   0.9774448,
   0.9754177,
   0.9647091,
   0.9546289,
   0.9634921,
   0.9583182,
   0.9551576,
   0.9590829,
   0.9666457,
   0.9691018,
   0.9608132,
   0.9583574,
   0.9361861,
   0.9350138,
   0.9503372,
   0.9233031,
   0.9602371,
   0.9638716,
   0.9671298,
   0.9242906,
   1.015245,
   0.9197318};
   Double_t Graph0_fex1006[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1006[33] = {
   0.4681822,
   0.06547388,
   0.02912985,
   0.01792109,
   0.01339904,
   0.01138161,
   0.01037281,
   0.01013756,
   0.009983715,
   0.01023199,
   0.01034185,
   0.01064197,
   0.0076991,
   0.0077359,
   0.007706437,
   0.007772497,
   0.00796084,
   0.008260906,
   0.008848833,
   0.009563103,
   0.01040241,
   0.0115594,
   0.01310518,
   0.01468441,
   0.01701334,
   0.02021885,
   0.02285914,
   0.02721187,
   0.03297881,
   0.03940154,
   0.0461458,
   0.04521774,
   0.05553117};
   gre = new TGraphErrors(33,Graph0_fx1006,Graph0_fy1006,Graph0_fex1006,Graph0_fey1006);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010051006 = new TH1F("Graph_Graph_Graph010051006","",100,0,3);
   Graph_Graph_Graph010051006->SetMinimum(0.84);
   Graph_Graph_Graph010051006->SetMaximum(1.16);
   Graph_Graph_Graph010051006->SetDirectory(0);
   Graph_Graph_Graph010051006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010051006->SetLineColor(ci);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010051006->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010051006->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010051006->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010051006->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010051006->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010051006->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010051006->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010051006->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010051006->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010051006->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010051006->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010051006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010051006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010051006);
   
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
   
   Double_t Graph1_fx1007[33] = {
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
   Double_t Graph1_fy1007[33] = {
   68.50339,
   17.23037,
   9.351952,
   6.012786,
   0.9926163,
   1.012018,
   1.009758,
   1.008492,
   0.9879145,
   0.9707316,
   0.9539222,
   0.9473193,
   0.933818,
   0.9315821,
   0.9395694,
   0.9479719,
   0.9543949,
   0.9609071,
   0.9721188,
   0.9807115,
   0.9765009,
   0.9791589,
   0.9836269,
   0.9733242,
   0.9814982,
   0.9908009,
   0.9694688,
   0.9701111,
   0.9815069,
   0.9755558,
   0.9816958,
   0.9900812,
   0.9783298};
   Double_t Graph1_fex1007[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1007[33] = {
   16.64997,
   0.5272395,
   0.1276173,
   0.05120151,
   0.007750219,
   0.006646589,
   0.006038911,
   0.005898702,
   0.005751868,
   0.005818038,
   0.005842405,
   0.005990164,
   0.004200335,
   0.004228318,
   0.004239285,
   0.004281578,
   0.00440259,
   0.004585695,
   0.004940126,
   0.005355005,
   0.005804421,
   0.006473192,
   0.007367845,
   0.0082371,
   0.009595923,
   0.01144538,
   0.01283686,
   0.01517228,
   0.01849412,
   0.02199872,
   0.02608313,
   0.02522515,
   0.03128473};
   gre = new TGraphErrors(33,Graph1_fx1007,Graph1_fy1007,Graph1_fex1007,Graph1_fey1007);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11007 = new TH1F("Graph_Graph11007","",100,0,3.1325);
   Graph_Graph11007->SetMinimum(0.84);
   Graph_Graph11007->SetMaximum(1.16);
   Graph_Graph11007->SetDirectory(0);
   Graph_Graph11007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11007->SetLineColor(ci);
   Graph_Graph11007->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11007->GetXaxis()->SetLabelFont(42);
   Graph_Graph11007->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11007->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11007->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11007->GetXaxis()->SetTitleFont(42);
   Graph_Graph11007->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11007->GetYaxis()->CenterTitle(true);
   Graph_Graph11007->GetYaxis()->SetNdivisions(504);
   Graph_Graph11007->GetYaxis()->SetLabelFont(42);
   Graph_Graph11007->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11007->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11007->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11007->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11007->GetYaxis()->SetTitleFont(42);
   Graph_Graph11007->GetZaxis()->SetLabelFont(42);
   Graph_Graph11007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11007);
   
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
   
   Double_t Graph2_fx1008[33] = {
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
   Double_t Graph2_fy1008[33] = {
   3.440738,
   1.075928,
   0.9358634,
   0.9526439,
   0.9502339,
   0.9592751,
   0.9343868,
   0.9574966,
   0.9481478,
   0.9628466,
   0.9401419,
   0.9719594,
   0.9411645,
   0.9262251,
   0.9310206,
   0.9151709,
   0.974832,
   0.9643016,
   0.9428383,
   0.9388178,
   0.9290023,
   0.9533605,
   0.9785744,
   0.9475839,
   0.9080427,
   0.9749724,
   0.8923601,
   0.9093164,
   0.9112002,
   0.983239,
   1.052112,
   0.9689798,
   0.9515027};
   Double_t Graph2_fex1008[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1008[33] = {
   1.451282,
   0.1577932,
   0.06866498,
   0.04191535,
   0.03064693,
   0.02608322,
   0.02381514,
   0.02336552,
   0.02308619,
   0.02363514,
   0.02395127,
   0.02467028,
   0.01756406,
   0.01761186,
   0.0174994,
   0.01743925,
   0.01778673,
   0.01819911,
   0.01914187,
   0.02033851,
   0.02179688,
   0.02403354,
   0.02704487,
   0.03001867,
   0.03431362,
   0.04071243,
   0.04588785,
   0.05385349,
   0.06502868,
   0.0777333,
   0.09208198,
   0.08796425,
   0.1093927};
   gre = new TGraphErrors(33,Graph2_fx1008,Graph2_fy1008,Graph2_fex1008,Graph2_fey1008);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21008 = new TH1F("Graph_Graph21008","",100,0,3.1325);
   Graph_Graph21008->SetMinimum(0.84);
   Graph_Graph21008->SetMaximum(1.16);
   Graph_Graph21008->SetDirectory(0);
   Graph_Graph21008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21008->SetLineColor(ci);
   Graph_Graph21008->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21008->GetXaxis()->SetLabelFont(42);
   Graph_Graph21008->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21008->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21008->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21008->GetXaxis()->SetTitleFont(42);
   Graph_Graph21008->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21008->GetYaxis()->CenterTitle(true);
   Graph_Graph21008->GetYaxis()->SetNdivisions(504);
   Graph_Graph21008->GetYaxis()->SetLabelFont(42);
   Graph_Graph21008->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21008->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21008->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21008->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21008->GetYaxis()->SetTitleFont(42);
   Graph_Graph21008->GetZaxis()->SetLabelFont(42);
   Graph_Graph21008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21008);
   
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
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
