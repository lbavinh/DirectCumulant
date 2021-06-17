void hadron_negDFCent10-40()
{
//=========Macro generated from canvas: 10-40%, h-/Canvas
//=========  (Fri Apr 23 19:43:59 2021) by ROOT version 6.22/08
   TCanvas *10-40%, h- = new TCanvas("10-40%, h-", "Canvas",0,0,550,550);
   10-40%, h-->Range(0,0,1,1);
   10-40%, h-->SetFillColor(0);
   10-40%, h-->SetBorderMode(0);
   10-40%, h-->SetBorderSize(2);
   10-40%, h-->SetTickx(1);
   10-40%, h-->SetTicky(1);
   10-40%, h-->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1049[33] = {
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
   Double_t Graph0_fy1049[33] = {
   0.001517961,
   0.006194981,
   0.01131906,
   0.01646219,
   0.0219534,
   0.02772126,
   0.03240899,
   0.03627523,
   0.03931445,
   0.04203568,
   0.04361994,
   0.04571749,
   0.04791449,
   0.05072511,
   0.05288329,
   0.05483094,
   0.05620881,
   0.05859587,
   0.06011029,
   0.06226156,
   0.06514575,
   0.06654646,
   0.06996539,
   0.07247307,
   0.07613046,
   0.0761312,
   0.08077141,
   0.08059763,
   0.08951362,
   0.09250094,
   0.08889889,
   0.09152288,
   0.1098136};
   Double_t Graph0_fex1049[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1049[33] = {
   0.0003763305,
   0.0001807576,
   0.0001422875,
   0.0001319583,
   0.0001291288,
   0.0001338839,
   0.0001419427,
   0.0001522622,
   0.0001643525,
   0.0001779416,
   0.0001931381,
   0.000209895,
   0.0001664963,
   0.0001982693,
   0.0002364268,
   0.000281998,
   0.0003364238,
   0.0004018428,
   0.000480289,
   0.0005759165,
   0.0006920388,
   0.0008347736,
   0.001009714,
   0.001224724,
   0.00149114,
   0.00181518,
   0.002217717,
   0.002714474,
   0.003317784,
   0.004072667,
   0.004989238,
   0.004779486,
   0.006448246};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1049,Graph0_fy1049,Graph0_fex1049,Graph0_fey1049);
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
   
   TH1F *Graph_Graph01049 = new TH1F("Graph_Graph01049","",100,0,3);
   Graph_Graph01049->SetMinimum(-0.01);
   Graph_Graph01049->SetMaximum(0.2);
   Graph_Graph01049->SetDirectory(0);
   Graph_Graph01049->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01049->SetLineColor(ci);
   Graph_Graph01049->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01049->GetXaxis()->SetLabelFont(42);
   Graph_Graph01049->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01049->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01049->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01049->GetXaxis()->SetTitleFont(42);
   Graph_Graph01049->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01049->GetYaxis()->SetLabelFont(42);
   Graph_Graph01049->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01049->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01049->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01049->GetYaxis()->SetTitleFont(42);
   Graph_Graph01049->GetZaxis()->SetLabelFont(42);
   Graph_Graph01049->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01049->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01049);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1050[33] = {
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
   Double_t Graph1_fy1050[33] = {
   0.00200675,
   0.006574629,
   0.01104639,
   0.01668774,
   0.02208689,
   0.02760312,
   0.03202819,
   0.03551985,
   0.03825011,
   0.04050728,
   0.04259572,
   0.04431698,
   0.04594395,
   0.04876829,
   0.05099377,
   0.05295709,
   0.0551326,
   0.05690977,
   0.05878207,
   0.06051783,
   0.06222174,
   0.06352247,
   0.06844614,
   0.06847821,
   0.07989202,
   0.07819087,
   0.08066274,
   0.08216076,
   0.07489986,
   0.07843328,
   0.06771599,
   0.08849779,
   0.06339901};
   Double_t Graph1_fex1050[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1050[33] = {
   0.0007240316,
   0.0003419971,
   0.0002666536,
   0.0002470572,
   0.0002480583,
   0.0002594543,
   0.0002764845,
   0.0002974034,
   0.0003213366,
   0.0003479072,
   0.0003774937,
   0.0004100999,
   0.0003331054,
   0.0003942308,
   0.0004676253,
   0.0005553964,
   0.0006611889,
   0.0007876507,
   0.0009406267,
   0.001126501,
   0.001352696,
   0.001632784,
   0.00197464,
   0.002395742,
   0.002915727,
   0.00355449,
   0.004334028,
   0.005310028,
   0.006490496,
   0.007954863,
   0.00976933,
   0.009323038,
   0.01257643};
   gre = new TGraphErrors(33,Graph1_fx1050,Graph1_fy1050,Graph1_fex1050,Graph1_fey1050);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11050 = new TH1F("Graph_Graph11050","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11050->SetMinimum(0.001154447);
   Graph_Graph11050->SetMaximum(0.1074746);
   Graph_Graph11050->SetDirectory(0);
   Graph_Graph11050->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11050->SetLineColor(ci);
   Graph_Graph11050->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11050->GetXaxis()->SetLabelFont(42);
   Graph_Graph11050->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11050->GetXaxis()->SetTitleFont(42);
   Graph_Graph11050->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11050->GetYaxis()->SetLabelFont(42);
   Graph_Graph11050->GetYaxis()->SetTitleFont(42);
   Graph_Graph11050->GetZaxis()->SetLabelFont(42);
   Graph_Graph11050->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11050->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11050);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1051[33] = {
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
   Double_t Graph2_fy1051[33] = {
   -0.1101672,
   -0.1048312,
   -0.09983994,
   -0.09457571,
   0.02249504,
   0.02806927,
   0.032962,
   0.03678495,
   0.0398698,
   0.04236704,
   0.04429242,
   0.04606327,
   0.04829653,
   0.05107727,
   0.05311231,
   0.05490853,
   0.05663814,
   0.05787889,
   0.05905742,
   0.06101325,
   0.06366146,
   0.06389314,
   0.06698608,
   0.06900128,
   0.07133403,
   0.07229181,
   0.07736671,
   0.0761571,
   0.08414522,
   0.08592105,
   0.08186957,
   0.08598674,
   0.09695208};
   Double_t Graph2_fex1051[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1051[33] = {
   0.0002997778,
   0.0001509315,
   0.0001196791,
   0.0001106499,
   9.753228e-05,
   0.0001015215,
   0.0001083076,
   0.0001169908,
   0.0001270674,
   0.0001382486,
   0.000150513,
   0.0001636869,
   0.0001296693,
   0.0001534176,
   0.0001814031,
   0.0002145308,
   0.00025395,
   0.0003014641,
   0.0003585307,
   0.000427978,
   0.0005129778,
   0.0006173183,
   0.0007450525,
   0.0009024225,
   0.001096952,
   0.001334376,
   0.001628199,
   0.001989353,
   0.002431198,
   0.002988548,
   0.003655655,
   0.003489946,
   0.004688247};
   gre = new TGraphErrors(33,Graph2_fx1051,Graph2_fy1051,Graph2_fex1051,Graph2_fey1051);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21051 = new TH1F("Graph_Graph21051","v_{2}{2}",100,0,3.1325);
   Graph_Graph21051->SetMinimum(-0.1316777);
   Graph_Graph21051->SetMaximum(0.1228511);
   Graph_Graph21051->SetDirectory(0);
   Graph_Graph21051->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21051->SetLineColor(ci);
   Graph_Graph21051->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21051->GetXaxis()->SetLabelFont(42);
   Graph_Graph21051->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21051->GetXaxis()->SetTitleFont(42);
   Graph_Graph21051->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21051->GetYaxis()->SetLabelFont(42);
   Graph_Graph21051->GetYaxis()->SetTitleFont(42);
   Graph_Graph21051->GetZaxis()->SetLabelFont(42);
   Graph_Graph21051->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21051->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21051);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1052[33] = {
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
   Double_t Graph3_fy1052[33] = {
   0.005119858,
   0.007068796,
   0.01083416,
   0.01579407,
   0.02180134,
   0.02661491,
   0.02982883,
   0.03409102,
   0.0367922,
   0.04010191,
   0.04052517,
   0.04352495,
   0.04626097,
   0.04790571,
   0.05132155,
   0.0526899,
   0.05136439,
   0.05392451,
   0.05608984,
   0.06136606,
   0.06672492,
   0.06135963,
   0.07155254,
   0.06726524,
   0.0782396,
   0.0821647,
   0.07965116,
   0.107111,
   0.09496565,
   0.08300232,
   0.0725645,
   0.09054055,
   0.06815923};
   Double_t Graph3_fex1052[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1052[33] = {
   0.001842698,
   0.0009125104,
   0.0007044316,
   0.0006426227,
   0.0006261102,
   0.0006544017,
   0.0006983406,
   0.0007539836,
   0.0008172254,
   0.0008854088,
   0.0009578133,
   0.001036011,
   0.0008251069,
   0.0009591433,
   0.001117236,
   0.001303493,
   0.001521861,
   0.001789686,
   0.002114458,
   0.002507139,
   0.00298643,
   0.003581344,
   0.004287144,
   0.005178037,
   0.006287115,
   0.007585338,
   0.009280037,
   0.01127651,
   0.013711,
   0.01704643,
   0.02041474,
   0.020105,
   0.02643626};
   gre = new TGraphErrors(33,Graph3_fx1052,Graph3_fy1052,Graph3_fex1052,Graph3_fey1052);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31052 = new TH1F("Graph_Graph31052","v_{2}{4}",100,0,3.1325);
   Graph_Graph31052->SetMinimum(0.002949444);
   Graph_Graph31052->SetMaximum(0.1298986);
   Graph_Graph31052->SetDirectory(0);
   Graph_Graph31052->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31052->SetLineColor(ci);
   Graph_Graph31052->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31052->GetXaxis()->SetLabelFont(42);
   Graph_Graph31052->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31052->GetXaxis()->SetTitleFont(42);
   Graph_Graph31052->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31052->GetYaxis()->SetLabelFont(42);
   Graph_Graph31052->GetYaxis()->SetTitleFont(42);
   Graph_Graph31052->GetZaxis()->SetLabelFont(42);
   Graph_Graph31052->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31052->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31052);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph4_fx1053[33] = {
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
   Double_t Graph4_fy1053[33] = {
   0.001966652,
   0.006179061,
   0.01136356,
   0.01667077,
   0.02246019,
   0.02817679,
   0.03295905,
   0.03693676,
   0.04003741,
   0.04271508,
   0.0442677,
   0.04631144,
   0.04849596,
   0.05105352,
   0.05338355,
   0.05545563,
   0.05641981,
   0.05867204,
   0.06074345,
   0.06293713,
   0.06561873,
   0.06670626,
   0.0706101,
   0.07378384,
   0.07558152,
   0.0755185,
   0.07981792,
   0.0839681,
   0.09001764,
   0.09495697,
   0.08729962,
   0.09249786,
   0.1016045};
   Double_t Graph4_fex1053[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1053[33] = {
   0.0003657756,
   0.0001631765,
   0.0001245815,
   0.0001145569,
   0.0001145107,
   0.0001194684,
   0.0001275585,
   0.0001379634,
   0.0001503209,
   0.0001645006,
   0.0001805354,
   0.0001984403,
   0.0001615843,
   0.000195692,
   0.0002366289,
   0.0002853475,
   0.0003433367,
   0.0004125253,
   0.0004955195,
   0.0005962492,
   0.0007190401,
   0.0008689712,
   0.001053825,
   0.001280213,
   0.001560406,
   0.00190354,
   0.002324707,
   0.0028505,
   0.003488699,
   0.004278357,
   0.005252048,
   0.005025493,
   0.006797452};
   gre = new TGraphErrors(33,Graph4_fx1053,Graph4_fy1053,Graph4_fex1053,Graph4_fey1053);
   gre->SetName("Graph4");
   gre->SetTitle("v_{2}^{EP}{#Psi_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41053 = new TH1F("Graph_Graph41053","v_{2}^{EP}{#Psi_{2,TPC}}",100,0,3.1325);
   Graph_Graph41053->SetMinimum(0.001440788);
   Graph_Graph41053->SetMaximum(0.1190821);
   Graph_Graph41053->SetDirectory(0);
   Graph_Graph41053->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41053->SetLineColor(ci);
   Graph_Graph41053->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41053->GetXaxis()->SetLabelFont(42);
   Graph_Graph41053->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41053->GetXaxis()->SetTitleFont(42);
   Graph_Graph41053->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph41053->GetYaxis()->SetLabelFont(42);
   Graph_Graph41053->GetYaxis()->SetTitleFont(42);
   Graph_Graph41053->GetZaxis()->SetLabelFont(42);
   Graph_Graph41053->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41053->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41053);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph5_fx1054[33] = {
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
   Double_t Graph5_fy1054[33] = {
   0.001531909,
   0.00625019,
   0.01141741,
   0.01660069,
   0.02213347,
   0.02794459,
   0.03266656,
   0.03656062,
   0.03962221,
   0.04236346,
   0.04396348,
   0.04607973,
   0.04829698,
   0.05113713,
   0.05332228,
   0.05529421,
   0.05669372,
   0.05910867,
   0.06064307,
   0.0628289,
   0.06575387,
   0.06719073,
   0.07065841,
   0.07321116,
   0.07692361,
   0.07695031,
   0.08168128,
   0.08152649,
   0.09053981,
   0.09363112,
   0.08993369,
   0.09262741,
   0.1112157};
   Double_t Graph5_fex1054[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph5_fey1054[33] = {
   0.0003533607,
   0.0001577127,
   0.0001204068,
   0.0001106871,
   0.0001106363,
   0.0001154157,
   0.0001232251,
   0.0001332851,
   0.000145232,
   0.0001589446,
   0.0001744882,
   0.0001918307,
   0.0001562758,
   0.0001894073,
   0.0002291831,
   0.0002765901,
   0.0003329379,
   0.000400395,
   0.0004812264,
   0.0005796195,
   0.0006989802,
   0.0008458111,
   0.001026258,
   0.001247808,
   0.00152249,
   0.001857428,
   0.002274423,
   0.002788273,
   0.003411046,
   0.00419519,
   0.005140434,
   0.004933041,
   0.006662002};
   gre = new TGraphErrors(33,Graph5_fx1054,Graph5_fy1054,Graph5_fex1054,Graph5_fey1054);
   gre->SetName("Graph5");
   gre->SetTitle("v_{2}^{SP}{Q_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph51054 = new TH1F("Graph_Graph51054","v_{2}^{SP}{Q_{2,TPC}}",100,0,3.1325);
   Graph_Graph51054->SetMinimum(0.001060694);
   Graph_Graph51054->SetMaximum(0.1295476);
   Graph_Graph51054->SetDirectory(0);
   Graph_Graph51054->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51054->SetLineColor(ci);
   Graph_Graph51054->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph51054->GetXaxis()->SetLabelFont(42);
   Graph_Graph51054->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51054->GetXaxis()->SetTitleFont(42);
   Graph_Graph51054->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph51054->GetYaxis()->SetLabelFont(42);
   Graph_Graph51054->GetYaxis()->SetTitleFont(42);
   Graph_Graph51054->GetZaxis()->SetLabelFont(42);
   Graph_Graph51054->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51054->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51054);
   
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
   pt_LaTex = pt->AddText("10-40%, h-");
   pt->Draw();
   padUp->Modified();
   10-40%, h-->cd();
  
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
   
   Double_t Graph0_fx1055[33] = {
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
   Double_t Graph0_fy1055[33] = {
   1.322004,
   1.061283,
   0.975911,
   1.013701,
   1.006081,
   0.9957382,
   0.9882501,
   0.9791764,
   0.9729276,
   0.9636404,
   0.9765194,
   0.969366,
   0.9588738,
   0.9614231,
   0.96427,
   0.965825,
   0.9808535,
   0.971225,
   0.9779037,
   0.9719936,
   0.9551158,
   0.9545582,
   0.9782856,
   0.9448781,
   1.049409,
   1.027054,
   0.9986546,
   1.019394,
   0.8367426,
   0.8479187,
   0.7617192,
   0.9669471,
   0.5773328};
   Double_t Graph0_fex1055[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1055[33] = {
   0.5787278,
   0.06329733,
   0.02656078,
   0.01706614,
   0.01275515,
   0.01052261,
   0.009566278,
   0.009171041,
   0.009129561,
   0.009227127,
   0.009674164,
   0.01001365,
   0.007709303,
   0.008632755,
   0.009837481,
   0.01128165,
   0.01314666,
   0.01500175,
   0.01749065,
   0.02020382,
   0.02311047,
   0.02730195,
   0.03155737,
   0.0367114,
   0.04346611,
   0.05272112,
   0.06025793,
   0.07429209,
   0.07886264,
   0.09375133,
   0.1179149,
   0.1136944,
   0.1194374};
   gre = new TGraphErrors(33,Graph0_fx1055,Graph0_fy1055,Graph0_fex1055,Graph0_fey1055);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01055 = new TH1F("Graph_Graph01055","",100,0,3);
   Graph_Graph01055->SetMinimum(0.84);
   Graph_Graph01055->SetMaximum(1.16);
   Graph_Graph01055->SetDirectory(0);
   Graph_Graph01055->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01055->SetLineColor(ci);
   Graph_Graph01055->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01055->GetXaxis()->SetLabelFont(42);
   Graph_Graph01055->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01055->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01055->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01055->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01055->GetXaxis()->SetTitleFont(42);
   Graph_Graph01055->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01055->GetYaxis()->CenterTitle(true);
   Graph_Graph01055->GetYaxis()->SetNdivisions(504);
   Graph_Graph01055->GetYaxis()->SetLabelFont(42);
   Graph_Graph01055->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01055->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01055->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01055->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01055->GetYaxis()->SetTitleFont(42);
   Graph_Graph01055->GetZaxis()->SetLabelFont(42);
   Graph_Graph01055->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01055->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01055);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1056[33] = {
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
   Double_t Graph0_fy1056[33] = {
   1.322004,
   1.061283,
   0.975911,
   1.013701,
   1.006081,
   0.9957382,
   0.9882501,
   0.9791764,
   0.9729276,
   0.9636404,
   0.9765194,
   0.969366,
   0.9588738,
   0.9614231,
   0.96427,
   0.965825,
   0.9808535,
   0.971225,
   0.9779037,
   0.9719936,
   0.9551158,
   0.9545582,
   0.9782856,
   0.9448781,
   1.049409,
   1.027054,
   0.9986546,
   1.019394,
   0.8367426,
   0.8479187,
   0.7617192,
   0.9669471,
   0.5773328};
   Double_t Graph0_fex1056[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1056[33] = {
   0.5787278,
   0.06329733,
   0.02656078,
   0.01706614,
   0.01275515,
   0.01052261,
   0.009566278,
   0.009171041,
   0.009129561,
   0.009227127,
   0.009674164,
   0.01001365,
   0.007709303,
   0.008632755,
   0.009837481,
   0.01128165,
   0.01314666,
   0.01500175,
   0.01749065,
   0.02020382,
   0.02311047,
   0.02730195,
   0.03155737,
   0.0367114,
   0.04346611,
   0.05272112,
   0.06025793,
   0.07429209,
   0.07886264,
   0.09375133,
   0.1179149,
   0.1136944,
   0.1194374};
   gre = new TGraphErrors(33,Graph0_fx1056,Graph0_fy1056,Graph0_fex1056,Graph0_fey1056);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010551056 = new TH1F("Graph_Graph_Graph010551056","",100,0,3);
   Graph_Graph_Graph010551056->SetMinimum(0.84);
   Graph_Graph_Graph010551056->SetMaximum(1.16);
   Graph_Graph_Graph010551056->SetDirectory(0);
   Graph_Graph_Graph010551056->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010551056->SetLineColor(ci);
   Graph_Graph_Graph010551056->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010551056->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010551056->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010551056->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010551056->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010551056->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010551056->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010551056->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010551056->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010551056->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010551056->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010551056->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010551056->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010551056->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010551056->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010551056->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010551056->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010551056->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010551056->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010551056);
   
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
   
   Double_t Graph1_fx1057[33] = {
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
   Double_t Graph1_fy1057[33] = {
   72.57576,
   16.92195,
   8.820516,
   5.745028,
   1.024672,
   1.012554,
   1.017063,
   1.014051,
   1.014126,
   1.007883,
   1.015417,
   1.007563,
   1.007973,
   1.006943,
   1.004331,
   1.001415,
   1.007638,
   0.9877641,
   0.9824843,
   0.9799505,
   0.9772158,
   0.9601282,
   0.9574173,
   0.9520954,
   0.9369972,
   0.9495688,
   0.9578477,
   0.944905,
   0.9400269,
   0.9288668,
   0.920929,
   0.9395108,
   0.8828784};
   Double_t Graph1_fex1057[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1057[33] = {
   17.99395,
   0.4943505,
   0.1113823,
   0.04653916,
   0.007487534,
   0.006109559,
   0.005568712,
   0.005340232,
   0.005331024,
   0.005386957,
   0.005667488,
   0.005849597,
   0.004426269,
   0.004963705,
   0.005650446,
   0.006467934,
   0.00753556,
   0.008506202,
   0.009859063,
   0.01137608,
   0.01302949,
   0.0152024,
   0.01744449,
   0.02034501,
   0.0233331,
   0.02863203,
   0.03313616,
   0.0402738,
   0.04417708,
   0.05211862,
   0.06604779,
   0.06213867,
   0.06715892};
   gre = new TGraphErrors(33,Graph1_fx1057,Graph1_fy1057,Graph1_fex1057,Graph1_fey1057);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11057 = new TH1F("Graph_Graph11057","",100,0,3.1325);
   Graph_Graph11057->SetMinimum(0.84);
   Graph_Graph11057->SetMaximum(1.16);
   Graph_Graph11057->SetDirectory(0);
   Graph_Graph11057->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11057->SetLineColor(ci);
   Graph_Graph11057->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11057->GetXaxis()->SetLabelFont(42);
   Graph_Graph11057->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11057->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11057->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11057->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11057->GetXaxis()->SetTitleFont(42);
   Graph_Graph11057->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11057->GetYaxis()->CenterTitle(true);
   Graph_Graph11057->GetYaxis()->SetNdivisions(504);
   Graph_Graph11057->GetYaxis()->SetLabelFont(42);
   Graph_Graph11057->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11057->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11057->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11057->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11057->GetYaxis()->SetTitleFont(42);
   Graph_Graph11057->GetZaxis()->SetLabelFont(42);
   Graph_Graph11057->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11057->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11057);
   
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
   
   Double_t Graph2_fx1058[33] = {
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
   Double_t Graph2_fy1058[33] = {
   3.372851,
   1.141052,
   0.9571606,
   0.9594149,
   0.9930736,
   0.9600903,
   0.9203874,
   0.9397876,
   0.9358441,
   0.9539969,
   0.9290514,
   0.9520415,
   0.9654902,
   0.9444181,
   0.9704681,
   0.960952,
   0.913814,
   0.9202784,
   0.9331155,
   0.9856172,
   1.024241,
   0.9220569,
   1.022685,
   0.9281412,
   1.027704,
   1.079251,
   0.9861306,
   1.32896,
   1.060907,
   0.8973133,
   0.8162588,
   0.9892668,
   0.620681};
   Double_t Graph2_fex1058[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1058[33] = {
   1.474056,
   0.1510141,
   0.06338657,
   0.03978664,
   0.029112,
   0.02405758,
   0.02192155,
   0.02115609,
   0.02115185,
   0.0214469,
   0.02234015,
   0.02307884,
   0.01754417,
   0.01926561,
   0.02156736,
   0.02428125,
   0.02762205,
   0.03118809,
   0.03595776,
   0.04128702,
   0.0471158,
   0.05504611,
   0.06302761,
   0.07314909,
   0.08500124,
   0.1029043,
   0.1180399,
   0.1468961,
   0.158139,
   0.1884711,
   0.2341648,
   0.2256648,
   0.2434808};
   gre = new TGraphErrors(33,Graph2_fx1058,Graph2_fy1058,Graph2_fex1058,Graph2_fey1058);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21058 = new TH1F("Graph_Graph21058","",100,0,3.1325);
   Graph_Graph21058->SetMinimum(0.84);
   Graph_Graph21058->SetMaximum(1.16);
   Graph_Graph21058->SetDirectory(0);
   Graph_Graph21058->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21058->SetLineColor(ci);
   Graph_Graph21058->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21058->GetXaxis()->SetLabelFont(42);
   Graph_Graph21058->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21058->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21058->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21058->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21058->GetXaxis()->SetTitleFont(42);
   Graph_Graph21058->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21058->GetYaxis()->CenterTitle(true);
   Graph_Graph21058->GetYaxis()->SetNdivisions(504);
   Graph_Graph21058->GetYaxis()->SetLabelFont(42);
   Graph_Graph21058->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21058->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21058->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21058->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21058->GetYaxis()->SetTitleFont(42);
   Graph_Graph21058->GetZaxis()->SetLabelFont(42);
   Graph_Graph21058->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21058->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21058);
   
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
   
   Double_t Graph3_fx1059[33] = {
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
   Double_t Graph3_fy1059[33] = {
   1.295587,
   0.99743,
   1.003931,
   1.012671,
   1.023085,
   1.016433,
   1.016972,
   1.018236,
   1.018389,
   1.016163,
   1.01485,
   1.012992,
   1.012135,
   1.006474,
   1.00946,
   1.011393,
   1.003754,
   1.0013,
   1.010533,
   1.010851,
   1.00726,
   1.002401,
   1.009215,
   1.018086,
   0.9927894,
   0.991952,
   0.9881952,
   1.041819,
   1.005631,
   1.026551,
   0.9820103,
   1.010653,
   0.9252452};
   Double_t Graph3_fex1059[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1059[33] = {
   0.401539,
   0.03925291,
   0.0167453,
   0.01069191,
   0.007963709,
   0.006532327,
   0.005943904,
   0.005721133,
   0.005722279,
   0.005815281,
   0.006109127,
   0.00636163,
   0.004872601,
   0.005509968,
   0.00635523,
   0.007357994,
   0.008567569,
   0.009834471,
   0.01153905,
   0.01338425,
   0.01537256,
   0.01812811,
   0.02095218,
   0.02465849,
   0.02825295,
   0.03441708,
   0.03955428,
   0.04981946,
   0.05392833,
   0.06466882,
   0.08079454,
   0.07616166,
   0.08236127};
   gre = new TGraphErrors(33,Graph3_fx1059,Graph3_fy1059,Graph3_fex1059,Graph3_fey1059);
   gre->SetName("Graph3");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31059 = new TH1F("Graph_Graph31059","",100,0,3.1325);
   Graph_Graph31059->SetMinimum(0.84);
   Graph_Graph31059->SetMaximum(1.16);
   Graph_Graph31059->SetDirectory(0);
   Graph_Graph31059->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31059->SetLineColor(ci);
   Graph_Graph31059->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31059->GetXaxis()->SetLabelFont(42);
   Graph_Graph31059->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph31059->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph31059->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph31059->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31059->GetXaxis()->SetTitleFont(42);
   Graph_Graph31059->GetYaxis()->SetTitle("Ratio");
   Graph_Graph31059->GetYaxis()->CenterTitle(true);
   Graph_Graph31059->GetYaxis()->SetNdivisions(504);
   Graph_Graph31059->GetYaxis()->SetLabelFont(42);
   Graph_Graph31059->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph31059->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph31059->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph31059->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph31059->GetYaxis()->SetTitleFont(42);
   Graph_Graph31059->GetZaxis()->SetLabelFont(42);
   Graph_Graph31059->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31059->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31059);
   
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
   
   Double_t Graph4_fx1060[33] = {
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
   Double_t Graph4_fy1060[33] = {
   1.009189,
   1.008912,
   1.008689,
   1.008413,
   1.008203,
   1.008056,
   1.007948,
   1.007867,
   1.007828,
   1.007798,
   1.007876,
   1.007923,
   1.007983,
   1.008123,
   1.008301,
   1.008449,
   1.008627,
   1.008751,
   1.008863,
   1.009112,
   1.009335,
   1.009681,
   1.009905,
   1.010184,
   1.010418,
   1.010759,
   1.011265,
   1.011525,
   1.011464,
   1.012218,
   1.01164,
   1.012068,
   1.012768};
   Double_t Graph4_fex1060[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1060[33] = {
   0.3417422,
   0.03891939,
   0.01655099,
   0.01051417,
   0.007782339,
   0.006406014,
   0.005826216,
   0.005603291,
   0.005603338,
   0.005700623,
   0.005993039,
   0.006246619,
   0.004786017,
   0.005428617,
   0.006253162,
   0.007235048,
   0.008457462,
   0.009723643,
   0.01136092,
   0.01318308,
   0.01516855,
   0.01794339,
   0.02067778,
   0.02424596,
   0.02813554,
   0.03429323,
   0.03954576,
   0.04855312,
   0.05345617,
   0.06358496,
   0.08103731,
   0.07548836,
   0.08495324};
   gre = new TGraphErrors(33,Graph4_fx1060,Graph4_fy1060,Graph4_fex1060,Graph4_fey1060);
   gre->SetName("Graph4");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41060 = new TH1F("Graph_Graph41060","",100,0,3.1325);
   Graph_Graph41060->SetMinimum(0.84);
   Graph_Graph41060->SetMaximum(1.16);
   Graph_Graph41060->SetDirectory(0);
   Graph_Graph41060->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41060->SetLineColor(ci);
   Graph_Graph41060->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41060->GetXaxis()->SetLabelFont(42);
   Graph_Graph41060->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph41060->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph41060->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph41060->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41060->GetXaxis()->SetTitleFont(42);
   Graph_Graph41060->GetYaxis()->SetTitle("Ratio");
   Graph_Graph41060->GetYaxis()->CenterTitle(true);
   Graph_Graph41060->GetYaxis()->SetNdivisions(504);
   Graph_Graph41060->GetYaxis()->SetLabelFont(42);
   Graph_Graph41060->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph41060->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph41060->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph41060->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph41060->GetYaxis()->SetTitleFont(42);
   Graph_Graph41060->GetZaxis()->SetLabelFont(42);
   Graph_Graph41060->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41060->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41060);
   
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
   10-40%, h-->cd();
   10-40%, h-->Modified();
   10-40%, h-->cd();
   10-40%, h-->SetSelected(10-40%, h-);
}
