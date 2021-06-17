void hadron_posDFCent10-40()
{
//=========Macro generated from canvas: 10-40%, h+/Canvas
//=========  (Fri Apr 23 19:43:59 2021) by ROOT version 6.22/08
   TCanvas *10-40%, h+ = new TCanvas("10-40%, h+", "Canvas",0,0,550,550);
   10-40%, h+->Range(0,0,1,1);
   10-40%, h+->SetFillColor(0);
   10-40%, h+->SetBorderMode(0);
   10-40%, h+->SetBorderSize(2);
   10-40%, h+->SetTickx(1);
   10-40%, h+->SetTicky(1);
   10-40%, h+->SetFrameBorderMode(0);
  
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

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
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

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
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

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
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
   
   Double_t Graph4_fx1005[33] = {
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
   Double_t Graph4_fy1005[33] = {
   0.001563841,
   0.005922402,
   0.0108367,
   0.01637915,
   0.02149885,
   0.02582729,
   0.02945789,
   0.0315483,
   0.03330714,
   0.03424281,
   0.03526736,
   0.03580898,
   0.03736679,
   0.0404644,
   0.04456238,
   0.04917975,
   0.05360952,
   0.05833423,
   0.06228388,
   0.06692208,
   0.0713657,
   0.07532564,
   0.07885593,
   0.08317146,
   0.08646191,
   0.0877173,
   0.09296455,
   0.09457125,
   0.09694212,
   0.0958923,
   0.1014224,
   0.0995807,
   0.1052216};
   Double_t Graph4_fex1005[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1005[33] = {
   0.0003815317,
   0.0001694903,
   0.0001285551,
   0.0001170164,
   0.0001152829,
   0.000117967,
   0.0001229533,
   0.0001291949,
   0.0001361481,
   0.0001435051,
   0.0001512004,
   0.0001591553,
   0.0001213941,
   0.0001345864,
   0.0001499911,
   0.0001685866,
   0.000191303,
   0.0002191952,
   0.0002535694,
   0.0002959354,
   0.0003480136,
   0.0004120482,
   0.0004910182,
   0.0005877711,
   0.0007069425,
   0.0008525811,
   0.001032318,
   0.001252975,
   0.00152369,
   0.001856756,
   0.002266822,
   0.002147895,
   0.002872891};
   gre = new TGraphErrors(33,Graph4_fx1005,Graph4_fy1005,Graph4_fex1005,Graph4_fey1005);
   gre->SetName("Graph4");
   gre->SetTitle("v_{2}^{EP}{#Psi_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41005 = new TH1F("Graph_Graph41005","v_{2}^{EP}{#Psi_{2,TPC}}",100,0,3.1325);
   Graph_Graph41005->SetMinimum(0.001064079);
   Graph_Graph41005->SetMaximum(0.1187857);
   Graph_Graph41005->SetDirectory(0);
   Graph_Graph41005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41005->SetLineColor(ci);
   Graph_Graph41005->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41005->GetXaxis()->SetLabelFont(42);
   Graph_Graph41005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41005->GetXaxis()->SetTitleFont(42);
   Graph_Graph41005->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph41005->GetYaxis()->SetLabelFont(42);
   Graph_Graph41005->GetYaxis()->SetTitleFont(42);
   Graph_Graph41005->GetZaxis()->SetLabelFont(42);
   Graph_Graph41005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41005);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph5_fx1006[33] = {
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
   Double_t Graph5_fy1006[33] = {
   0.00162364,
   0.006164433,
   0.01085358,
   0.01608103,
   0.02111196,
   0.02539966,
   0.02899736,
   0.03107353,
   0.03302988,
   0.0339238,
   0.03506767,
   0.03568728,
   0.03765888,
   0.04098342,
   0.04523561,
   0.04994307,
   0.0546037,
   0.05951637,
   0.06356671,
   0.06805393,
   0.0729308,
   0.07697389,
   0.08032369,
   0.08500751,
   0.08789878,
   0.08919025,
   0.09477274,
   0.09716501,
   0.09754575,
   0.09935559,
   0.102576,
   0.101032,
   0.1078119};
   Double_t Graph5_fex1006[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph5_fey1006[33] = {
   0.0003684203,
   0.0001637852,
   0.0001242279,
   0.0001130629,
   0.0001113705,
   0.0001139646,
   0.0001187689,
   0.0001247997,
   0.0001315229,
   0.0001386387,
   0.000146095,
   0.0001538278,
   0.0001173739,
   0.0001302107,
   0.0001452003,
   0.0001633043,
   0.0001854382,
   0.0002126112,
   0.000246124,
   0.0002874006,
   0.0003381396,
   0.0004006846,
   0.0004777076,
   0.0005720659,
   0.0006887025,
   0.000830928,
   0.001006939,
   0.001222907,
   0.001488269,
   0.001811781,
   0.002213183,
   0.002099536,
   0.002811467};
   gre = new TGraphErrors(33,Graph5_fx1006,Graph5_fy1006,Graph5_fex1006,Graph5_fey1006);
   gre->SetName("Graph5");
   gre->SetTitle("v_{2}^{SP}{Q_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph51006 = new TH1F("Graph_Graph51006","v_{2}^{SP}{Q_{2,TPC}}",100,0,3.1325);
   Graph_Graph51006->SetMinimum(0.001129697);
   Graph_Graph51006->SetMaximum(0.1215602);
   Graph_Graph51006->SetDirectory(0);
   Graph_Graph51006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51006->SetLineColor(ci);
   Graph_Graph51006->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph51006->GetXaxis()->SetLabelFont(42);
   Graph_Graph51006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51006->GetXaxis()->SetTitleFont(42);
   Graph_Graph51006->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph51006->GetYaxis()->SetLabelFont(42);
   Graph_Graph51006->GetYaxis()->SetTitleFont(42);
   Graph_Graph51006->GetZaxis()->SetLabelFont(42);
   Graph_Graph51006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51006);
   
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

   ci = TColor::GetColor("#2f4c4a");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","v_{2}{2}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#4e6d2c");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph3","v_{2}{4}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#a39e35");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph4","v_{2}^{EP}{#Psi_{2,TPC}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#a85d33");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph5","v_{2}^{SP}{Q_{2,TPC}}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#9c272b");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
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
   10-40%, h+->cd();
  
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
   
   Double_t Graph0_fx1007[33] = {
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
   Double_t Graph0_fy1007[33] = {
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
   Double_t Graph0_fex1007[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1007[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","",100,0,3);
   Graph_Graph01007->SetMinimum(0.84);
   Graph_Graph01007->SetMaximum(1.16);
   Graph_Graph01007->SetDirectory(0);
   Graph_Graph01007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01007->SetLineColor(ci);
   Graph_Graph01007->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01007->GetXaxis()->SetLabelFont(42);
   Graph_Graph01007->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01007->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01007->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetXaxis()->SetTitleFont(42);
   Graph_Graph01007->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01007->GetYaxis()->CenterTitle(true);
   Graph_Graph01007->GetYaxis()->SetNdivisions(504);
   Graph_Graph01007->GetYaxis()->SetLabelFont(42);
   Graph_Graph01007->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01007->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01007->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01007->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01007->GetYaxis()->SetTitleFont(42);
   Graph_Graph01007->GetZaxis()->SetLabelFont(42);
   Graph_Graph01007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01007);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1008[33] = {
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
   Double_t Graph0_fy1008[33] = {
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
   Double_t Graph0_fex1008[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1008[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1008,Graph0_fy1008,Graph0_fex1008,Graph0_fey1008);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010071008 = new TH1F("Graph_Graph_Graph010071008","",100,0,3);
   Graph_Graph_Graph010071008->SetMinimum(0.84);
   Graph_Graph_Graph010071008->SetMaximum(1.16);
   Graph_Graph_Graph010071008->SetDirectory(0);
   Graph_Graph_Graph010071008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010071008->SetLineColor(ci);
   Graph_Graph_Graph010071008->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010071008->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010071008->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010071008->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010071008->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010071008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010071008->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010071008->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010071008->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010071008->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010071008->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010071008->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010071008->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010071008->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010071008->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010071008->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010071008->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010071008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010071008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010071008);
   
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
   
   Double_t Graph1_fx1009[33] = {
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
   Double_t Graph1_fy1009[33] = {
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
   Double_t Graph1_fex1009[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1009[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1009,Graph1_fy1009,Graph1_fex1009,Graph1_fey1009);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11009 = new TH1F("Graph_Graph11009","",100,0,3.1325);
   Graph_Graph11009->SetMinimum(0.84);
   Graph_Graph11009->SetMaximum(1.16);
   Graph_Graph11009->SetDirectory(0);
   Graph_Graph11009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11009->SetLineColor(ci);
   Graph_Graph11009->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11009->GetXaxis()->SetLabelFont(42);
   Graph_Graph11009->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11009->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11009->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11009->GetXaxis()->SetTitleFont(42);
   Graph_Graph11009->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11009->GetYaxis()->CenterTitle(true);
   Graph_Graph11009->GetYaxis()->SetNdivisions(504);
   Graph_Graph11009->GetYaxis()->SetLabelFont(42);
   Graph_Graph11009->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11009->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11009->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11009->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11009->GetYaxis()->SetTitleFont(42);
   Graph_Graph11009->GetZaxis()->SetLabelFont(42);
   Graph_Graph11009->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11009);
   
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
   
   Double_t Graph2_fx1010[33] = {
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
   Double_t Graph2_fy1010[33] = {
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
   Double_t Graph2_fex1010[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1010[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1010,Graph2_fy1010,Graph2_fex1010,Graph2_fey1010);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21010 = new TH1F("Graph_Graph21010","",100,0,3.1325);
   Graph_Graph21010->SetMinimum(0.84);
   Graph_Graph21010->SetMaximum(1.16);
   Graph_Graph21010->SetDirectory(0);
   Graph_Graph21010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21010->SetLineColor(ci);
   Graph_Graph21010->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21010->GetXaxis()->SetLabelFont(42);
   Graph_Graph21010->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21010->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21010->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21010->GetXaxis()->SetTitleFont(42);
   Graph_Graph21010->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21010->GetYaxis()->CenterTitle(true);
   Graph_Graph21010->GetYaxis()->SetNdivisions(504);
   Graph_Graph21010->GetYaxis()->SetLabelFont(42);
   Graph_Graph21010->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21010->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21010->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21010->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21010->GetYaxis()->SetTitleFont(42);
   Graph_Graph21010->GetZaxis()->SetLabelFont(42);
   Graph_Graph21010->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21010);
   
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
   
   Double_t Graph3_fx1011[33] = {
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
   Double_t Graph3_fy1011[33] = {
   0.9721559,
   0.9691549,
   1.006875,
   1.026841,
   1.026418,
   1.02474,
   1.023664,
   1.022939,
   1.015955,
   1.016908,
   1.013136,
   1.010845,
   0.9996457,
   0.9947566,
   0.9926265,
   0.9923548,
   0.9895445,
   0.9879619,
   0.9878035,
   0.9916004,
   0.9868623,
   0.9871024,
   0.9905113,
   0.9873957,
   0.9928454,
   0.9929207,
   0.990453,
   0.9830352,
   1.003922,
   0.9750744,
   0.99916,
   0.9963878,
   0.9870866};
   Double_t Graph3_fex1011[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1011[33] = {
   0.3347785,
   0.04057923,
   0.01816433,
   0.01134967,
   0.00842188,
   0.007136635,
   0.006493152,
   0.006346394,
   0.006248233,
   0.006396171,
   0.006484554,
   0.00667716,
   0.004737193,
   0.004784718,
   0.004796221,
   0.004852101,
   0.004999903,
   0.005223981,
   0.005631111,
   0.006125991,
   0.006684338,
   0.007480881,
   0.008540532,
   0.009629854,
   0.01121937,
   0.01332503,
   0.01515781,
   0.01787497,
   0.02186222,
   0.02577877,
   0.03082778,
   0.02962236,
   0.03693415};
   gre = new TGraphErrors(33,Graph3_fx1011,Graph3_fy1011,Graph3_fex1011,Graph3_fey1011);
   gre->SetName("Graph3");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31011 = new TH1F("Graph_Graph31011","",100,0,3.1325);
   Graph_Graph31011->SetMinimum(0.84);
   Graph_Graph31011->SetMaximum(1.16);
   Graph_Graph31011->SetDirectory(0);
   Graph_Graph31011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31011->SetLineColor(ci);
   Graph_Graph31011->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31011->GetXaxis()->SetLabelFont(42);
   Graph_Graph31011->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph31011->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph31011->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph31011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31011->GetXaxis()->SetTitleFont(42);
   Graph_Graph31011->GetYaxis()->SetTitle("Ratio");
   Graph_Graph31011->GetYaxis()->CenterTitle(true);
   Graph_Graph31011->GetYaxis()->SetNdivisions(504);
   Graph_Graph31011->GetYaxis()->SetLabelFont(42);
   Graph_Graph31011->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph31011->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph31011->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph31011->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph31011->GetYaxis()->SetTitleFont(42);
   Graph_Graph31011->GetZaxis()->SetLabelFont(42);
   Graph_Graph31011->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31011);
   
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
   
   Double_t Graph4_fx1012[33] = {
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
   Double_t Graph4_fy1012[33] = {
   1.009329,
   1.008762,
   1.008443,
   1.008151,
   1.007946,
   1.007773,
   1.007661,
   1.007545,
   1.007497,
   1.007434,
   1.0074,
   1.00741,
   1.00746,
   1.007516,
   1.007623,
   1.007757,
   1.007895,
   1.007983,
   1.008149,
   1.008371,
   1.008505,
   1.008702,
   1.008948,
   1.009193,
   1.009345,
   1.009594,
   1.009718,
   1.009996,
   1.010173,
   1.010291,
   1.010525,
   1.010909,
   1.011387};
   Double_t Graph4_fex1012[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1012[33] = {
   0.3356003,
   0.04085262,
   0.0179188,
   0.01106954,
   0.008213248,
   0.006965417,
   0.00634019,
   0.006198718,
   0.006125945,
   0.006267234,
   0.006366715,
   0.006564311,
   0.004684089,
   0.004743599,
   0.004760517,
   0.004817008,
   0.004971446,
   0.005198803,
   0.005605373,
   0.006087606,
   0.006658764,
   0.007454098,
   0.00849809,
   0.009598583,
   0.01115919,
   0.01325687,
   0.0151049,
   0.0178831,
   0.02166508,
   0.02588707,
   0.03061638,
   0.02948088,
   0.03694853};
   gre = new TGraphErrors(33,Graph4_fx1012,Graph4_fy1012,Graph4_fex1012,Graph4_fey1012);
   gre->SetName("Graph4");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41012 = new TH1F("Graph_Graph41012","",100,0,3.1325);
   Graph_Graph41012->SetMinimum(0.84);
   Graph_Graph41012->SetMaximum(1.16);
   Graph_Graph41012->SetDirectory(0);
   Graph_Graph41012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41012->SetLineColor(ci);
   Graph_Graph41012->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41012->GetXaxis()->SetLabelFont(42);
   Graph_Graph41012->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph41012->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph41012->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph41012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41012->GetXaxis()->SetTitleFont(42);
   Graph_Graph41012->GetYaxis()->SetTitle("Ratio");
   Graph_Graph41012->GetYaxis()->CenterTitle(true);
   Graph_Graph41012->GetYaxis()->SetNdivisions(504);
   Graph_Graph41012->GetYaxis()->SetLabelFont(42);
   Graph_Graph41012->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph41012->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph41012->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph41012->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph41012->GetYaxis()->SetTitleFont(42);
   Graph_Graph41012->GetZaxis()->SetLabelFont(42);
   Graph_Graph41012->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41012);
   
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
   10-40%, h+->cd();
   10-40%, h+->Modified();
   10-40%, h+->cd();
   10-40%, h+->SetSelected(10-40%, h+);
}
