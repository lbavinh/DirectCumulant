void pion_posDFCent10-40()
{
//=========Macro generated from canvas: 10-40%, #pi+/Canvas
//=========  (Fri Apr 23 19:43:59 2021) by ROOT version 6.22/08
   TCanvas *10-40%, #pi+ = new TCanvas("10-40%, #pi+", "Canvas",0,0,550,550);
   10-40%, #pi+->Range(0,0,1,1);
   10-40%, #pi+->SetFillColor(0);
   10-40%, #pi+->SetBorderMode(0);
   10-40%, #pi+->SetBorderSize(2);
   10-40%, #pi+->SetTickx(1);
   10-40%, #pi+->SetTicky(1);
   10-40%, #pi+->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1013[33] = {
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
   Double_t Graph0_fy1013[33] = {
   0.0017984,
   0.006306212,
   0.01123093,
   0.01695127,
   0.02278954,
   0.02838061,
   0.03354626,
   0.03736252,
   0.0409506,
   0.04358791,
   0.04612202,
   0.04789497,
   0.05062053,
   0.0535917,
   0.0562979,
   0.05823139,
   0.06013442,
   0.06245568,
   0.0637817,
   0.06424306,
   0.06776221,
   0.07021064,
   0.07146062,
   0.07596517,
   0.07752598,
   0.07201345,
   0.08409372,
   0.0863988,
   0.0854349,
   0.08285505,
   0.09179886,
   0.08128696,
   0.09083201};
   Double_t Graph0_fex1013[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1013[33] = {
   0.0003955319,
   0.0001895037,
   0.0001495615,
   0.0001391778,
   0.0001367849,
   0.0001422018,
   0.0001512171,
   0.0001628246,
   0.000176485,
   0.0001921059,
   0.0002097162,
   0.0002293872,
   0.000184271,
   0.0002230801,
   0.0002707725,
   0.0003291622,
   0.0004001859,
   0.0004865167,
   0.0005916461,
   0.0007203273,
   0.0008792585,
   0.001075039,
   0.001318896,
   0.001622862,
   0.001996861,
   0.002458335,
   0.003037621,
   0.003760251,
   0.004645051,
   0.005783837,
   0.007125993,
   0.006897158,
   0.009409953};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
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
   
   TH1F *Graph_Graph01013 = new TH1F("Graph_Graph01013","",100,0,3);
   Graph_Graph01013->SetMinimum(-0.01);
   Graph_Graph01013->SetMaximum(0.2);
   Graph_Graph01013->SetDirectory(0);
   Graph_Graph01013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01013->SetLineColor(ci);
   Graph_Graph01013->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01013->GetXaxis()->SetLabelFont(42);
   Graph_Graph01013->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01013->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetXaxis()->SetTitleFont(42);
   Graph_Graph01013->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01013->GetYaxis()->SetLabelFont(42);
   Graph_Graph01013->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01013->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01013->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01013->GetYaxis()->SetTitleFont(42);
   Graph_Graph01013->GetZaxis()->SetLabelFont(42);
   Graph_Graph01013->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01013);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1014[33] = {
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
   Double_t Graph1_fy1014[33] = {
   5.122335e-06,
   0.006251453,
   0.01159329,
   0.01687295,
   0.02247578,
   0.02758564,
   0.03246848,
   0.0363186,
   0.0395882,
   0.04282729,
   0.04463262,
   0.04638328,
   0.04922471,
   0.05205492,
   0.05346538,
   0.05633206,
   0.05889255,
   0.05939659,
   0.06209134,
   0.06430498,
   0.06578183,
   0.07043575,
   0.06944869,
   0.07259753,
   0.07631118,
   0.08431408,
   0.07953038,
   0.07794198,
   0.08989606,
   0.06961423,
   0.0796046,
   0.0852303,
   0.09312185};
   Double_t Graph1_fex1014[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1014[33] = {
   0.0007619077,
   0.0003590997,
   0.0002808886,
   0.000260959,
   0.000262642,
   0.0002750066,
   0.000294096,
   0.0003174715,
   0.000344667,
   0.0003753848,
   0.0004095022,
   0.0004475989,
   0.0003673506,
   0.0004415319,
   0.0005325588,
   0.000644897,
   0.0007817255,
   0.000947619,
   0.001150853,
   0.001400672,
   0.001707785,
   0.002088574,
   0.00256287,
   0.003150637,
   0.003876242,
   0.004768737,
   0.005881984,
   0.007294844,
   0.00899595,
   0.01116994,
   0.01384634,
   0.0132464,
   0.01829696};
   gre = new TGraphErrors(33,Graph1_fx1014,Graph1_fy1014,Graph1_fex1014,Graph1_fey1014);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11014 = new TH1F("Graph_Graph11014","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11014->SetMinimum(-0.01197434);
   Graph_Graph11014->SetMaximum(0.1226364);
   Graph_Graph11014->SetDirectory(0);
   Graph_Graph11014->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11014->SetLineColor(ci);
   Graph_Graph11014->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11014->GetXaxis()->SetLabelFont(42);
   Graph_Graph11014->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11014->GetXaxis()->SetTitleFont(42);
   Graph_Graph11014->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11014->GetYaxis()->SetLabelFont(42);
   Graph_Graph11014->GetYaxis()->SetTitleFont(42);
   Graph_Graph11014->GetZaxis()->SetLabelFont(42);
   Graph_Graph11014->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11014);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1015[33] = {
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
   Double_t Graph2_fy1015[33] = {
   -0.1100254,
   -0.105084,
   -0.1001606,
   -0.09488437,
   0.02275012,
   0.02888996,
   0.03432143,
   0.03839112,
   0.04175845,
   0.04397956,
   0.04623409,
   0.04787783,
   0.05043926,
   0.05320357,
   0.05596252,
   0.05778527,
   0.05942647,
   0.06135009,
   0.06250858,
   0.06385839,
   0.06601939,
   0.06753028,
   0.06906323,
   0.0718022,
   0.07465033,
   0.07168848,
   0.07662527,
   0.08001372,
   0.08132601,
   0.07718577,
   0.08245838,
   0.09112815,
   0.09180994};
   Double_t Graph2_fex1015[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1015[33] = {
   0.0003138677,
   0.0001577311,
   0.0001253977,
   0.0001162117,
   0.0001039931,
   0.0001085207,
   0.000116091,
   0.000125765,
   0.0001370255,
   0.0001496308,
   0.0001635222,
   0.0001787038,
   0.0001429185,
   0.0001715245,
   0.0002061862,
   0.0002484939,
   0.0002999811,
   0.0003627529,
   0.0004394111,
   0.0005330257,
   0.0006496739,
   0.0007921098,
   0.0009705261,
   0.001193305,
   0.00146657,
   0.001807287,
   0.002227743,
   0.002754242,
   0.003389005,
   0.004222234,
   0.005191341,
   0.005008091,
   0.006797878};
   gre = new TGraphErrors(33,Graph2_fx1015,Graph2_fy1015,Graph2_fex1015,Graph2_fey1015);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21015 = new TH1F("Graph_Graph21015","v_{2}{2}",100,0,3.1325);
   Graph_Graph21015->SetMinimum(-0.131234);
   Graph_Graph21015->SetMaximum(0.1195025);
   Graph_Graph21015->SetDirectory(0);
   Graph_Graph21015->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21015->SetLineColor(ci);
   Graph_Graph21015->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21015->GetXaxis()->SetLabelFont(42);
   Graph_Graph21015->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21015->GetXaxis()->SetTitleFont(42);
   Graph_Graph21015->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21015->GetYaxis()->SetLabelFont(42);
   Graph_Graph21015->GetYaxis()->SetTitleFont(42);
   Graph_Graph21015->GetZaxis()->SetLabelFont(42);
   Graph_Graph21015->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21015);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1016[33] = {
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
   Double_t Graph3_fy1016[33] = {
   0.00570885,
   0.006671649,
   0.01043945,
   0.015922,
   0.02180183,
   0.02721271,
   0.03105808,
   0.03586856,
   0.03917062,
   0.04177859,
   0.04305878,
   0.04656125,
   0.04703676,
   0.05120495,
   0.05349698,
   0.05311562,
   0.05851032,
   0.05840456,
   0.06013388,
   0.06077959,
   0.05740459,
   0.06177766,
   0.07815861,
   0.07481658,
   0.05961125,
   0.07847232,
   0.09021674,
   0.0860381,
   0.04369141,
   0.1168816,
   0.02754443,
   0.07967497,
   0.1039825};
   Double_t Graph3_fex1016[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1016[33] = {
   0.001927766,
   0.0009563289,
   0.0007428869,
   0.0006799037,
   0.0006654009,
   0.0006967413,
   0.0007465113,
   0.000808358,
   0.0008785283,
   0.0009546974,
   0.00103711,
   0.001126443,
   0.0009015144,
   0.00106738,
   0.001264716,
   0.001501577,
   0.001797337,
   0.002155712,
   0.002596452,
   0.003130172,
   0.003806273,
   0.00462946,
   0.00564505,
   0.006931457,
   0.008491399,
   0.01042427,
   0.01280574,
   0.01586322,
   0.01963229,
   0.02482823,
   0.02988395,
   0.02836882,
   0.03899715};
   gre = new TGraphErrors(33,Graph3_fx1016,Graph3_fy1016,Graph3_fex1016,Graph3_fey1016);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31016 = new TH1F("Graph_Graph31016","v_{2}{4}",100,0,3.1325);
   Graph_Graph31016->SetMinimum(-0.01687144);
   Graph_Graph31016->SetMaximum(0.1575115);
   Graph_Graph31016->SetDirectory(0);
   Graph_Graph31016->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31016->SetLineColor(ci);
   Graph_Graph31016->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31016->GetXaxis()->SetLabelFont(42);
   Graph_Graph31016->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31016->GetXaxis()->SetTitleFont(42);
   Graph_Graph31016->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31016->GetYaxis()->SetLabelFont(42);
   Graph_Graph31016->GetYaxis()->SetTitleFont(42);
   Graph_Graph31016->GetZaxis()->SetLabelFont(42);
   Graph_Graph31016->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31016);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph4_fx1017[33] = {
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
   Double_t Graph4_fy1017[33] = {
   0.001788425,
   0.006097793,
   0.01132058,
   0.01740006,
   0.02334799,
   0.02899018,
   0.0343091,
   0.03822219,
   0.04165029,
   0.04437039,
   0.04691239,
   0.0488278,
   0.05107272,
   0.05372842,
   0.05685491,
   0.05844788,
   0.06004065,
   0.06245044,
   0.06342562,
   0.06480594,
   0.0680095,
   0.07010348,
   0.0725789,
   0.07606965,
   0.07924015,
   0.07568212,
   0.0884568,
   0.08419711,
   0.08184847,
   0.08289752,
   0.09449549,
   0.08350463,
   0.09445571};
   Double_t Graph4_fex1017[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1017[33] = {
   0.0003864819,
   0.0001724362,
   0.0001318559,
   0.0001215249,
   0.000121824,
   0.0001275293,
   0.000136758,
   0.0001486669,
   0.0001629128,
   0.0001793766,
   0.000198137,
   0.0002192519,
   0.0001804415,
   0.0002219569,
   0.0002727743,
   0.0003346548,
   0.0004095032,
   0.0005001265,
   0.000610257,
   0.0007450226,
   0.0009113828,
   0.001116117,
   0.001371493,
   0.0016895,
   0.00208051,
   0.002565051,
   0.003172294,
   0.003926917,
   0.004849967,
   0.006049989,
   0.007463393,
   0.007197267,
   0.009880202};
   gre = new TGraphErrors(33,Graph4_fx1017,Graph4_fy1017,Graph4_fex1017,Graph4_fey1017);
   gre->SetName("Graph4");
   gre->SetTitle("v_{2}^{EP}{#Psi_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41017 = new TH1F("Graph_Graph41017","v_{2}^{EP}{#Psi_{2,TPC}}",100,0,3.1325);
   Graph_Graph41017->SetMinimum(0.001261749);
   Graph_Graph41017->SetMaximum(0.1146293);
   Graph_Graph41017->SetDirectory(0);
   Graph_Graph41017->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41017->SetLineColor(ci);
   Graph_Graph41017->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41017->GetXaxis()->SetLabelFont(42);
   Graph_Graph41017->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41017->GetXaxis()->SetTitleFont(42);
   Graph_Graph41017->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph41017->GetYaxis()->SetLabelFont(42);
   Graph_Graph41017->GetYaxis()->SetTitleFont(42);
   Graph_Graph41017->GetZaxis()->SetLabelFont(42);
   Graph_Graph41017->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41017);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph5_fx1018[33] = {
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
   Double_t Graph5_fy1018[33] = {
   0.001815077,
   0.006361472,
   0.01132579,
   0.01708912,
   0.02297028,
   0.02860011,
   0.03380164,
   0.03764166,
   0.0412538,
   0.04390737,
   0.04645891,
   0.0482444,
   0.05098952,
   0.05398382,
   0.05671109,
   0.0586596,
   0.06057969,
   0.06291742,
   0.06426076,
   0.06472783,
   0.06827531,
   0.07076543,
   0.07204561,
   0.07659416,
   0.07818338,
   0.07264679,
   0.08484574,
   0.08719739,
   0.0861756,
   0.08362183,
   0.09266488,
   0.08208409,
   0.09175012};
   Double_t Graph5_fex1018[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph5_fey1018[33] = {
   0.0003732043,
   0.0001666293,
   0.0001274164,
   0.0001174161,
   0.0001176849,
   0.0001231911,
   0.0001320869,
   0.0001435759,
   0.0001573413,
   0.0001732284,
   0.0001913794,
   0.0002118103,
   0.0001743595,
   0.0002145812,
   0.0002637994,
   0.0003237051,
   0.000396258,
   0.0004842377,
   0.0005910119,
   0.0007216449,
   0.0008832468,
   0.001082591,
   0.001331188,
   0.001640526,
   0.002021893,
   0.002493104,
   0.003083035,
   0.003824847,
   0.004723692,
   0.005889535,
   0.007251321,
   0.007032308,
   0.009617687};
   gre = new TGraphErrors(33,Graph5_fx1018,Graph5_fy1018,Graph5_fex1018,Graph5_fey1018);
   gre->SetName("Graph5");
   gre->SetTitle("v_{2}^{SP}{Q_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph51018 = new TH1F("Graph_Graph51018","v_{2}^{SP}{Q_{2,TPC}}",100,0,3.1325);
   Graph_Graph51018->SetMinimum(0.001297685);
   Graph_Graph51018->SetMaximum(0.1113604);
   Graph_Graph51018->SetDirectory(0);
   Graph_Graph51018->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51018->SetLineColor(ci);
   Graph_Graph51018->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph51018->GetXaxis()->SetLabelFont(42);
   Graph_Graph51018->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51018->GetXaxis()->SetTitleFont(42);
   Graph_Graph51018->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph51018->GetYaxis()->SetLabelFont(42);
   Graph_Graph51018->GetYaxis()->SetTitleFont(42);
   Graph_Graph51018->GetZaxis()->SetLabelFont(42);
   Graph_Graph51018->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51018->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51018);
   
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
   pt_LaTex = pt->AddText("10-40%, #pi+");
   pt->Draw();
   padUp->Modified();
   10-40%, #pi+->cd();
  
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
   
   Double_t Graph0_fx1019[33] = {
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
   Double_t Graph0_fy1019[33] = {
   0.002848274,
   0.9913166,
   1.032264,
   0.9953798,
   0.9862323,
   0.9719893,
   0.967872,
   0.9720596,
   0.9667307,
   0.9825498,
   0.9677074,
   0.9684374,
   0.9724257,
   0.9713243,
   0.949687,
   0.967383,
   0.9793484,
   0.9510198,
   0.9734977,
   1.000964,
   0.9707746,
   1.003206,
   0.9718457,
   0.9556687,
   0.9843304,
   1.17081,
   0.945735,
   0.9021188,
   1.052217,
   0.840193,
   0.8671633,
   1.048511,
   1.02521};
   Double_t Graph0_fex1019[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1019[33] = {
   0.4236592,
   0.0642651,
   0.02853915,
   0.01742945,
   0.012956,
   0.01084499,
   0.0097925,
   0.009494493,
   0.009391395,
   0.009639568,
   0.009909194,
   0.01043312,
   0.008074278,
   0.009177453,
   0.01050469,
   0.01235119,
   0.01454191,
   0.01688466,
   0.02017717,
   0.02452185,
   0.0281752,
   0.03347912,
   0.04009933,
   0.04622743,
   0.05606011,
   0.07734696,
   0.07784218,
   0.09311451,
   0.1198334,
   0.1470187,
   0.1651726,
   0.1856619,
   0.227722};
   gre = new TGraphErrors(33,Graph0_fx1019,Graph0_fy1019,Graph0_fex1019,Graph0_fey1019);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01019 = new TH1F("Graph_Graph01019","",100,0,3);
   Graph_Graph01019->SetMinimum(0.84);
   Graph_Graph01019->SetMaximum(1.16);
   Graph_Graph01019->SetDirectory(0);
   Graph_Graph01019->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01019->SetLineColor(ci);
   Graph_Graph01019->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01019->GetXaxis()->SetLabelFont(42);
   Graph_Graph01019->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01019->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01019->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01019->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01019->GetXaxis()->SetTitleFont(42);
   Graph_Graph01019->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01019->GetYaxis()->CenterTitle(true);
   Graph_Graph01019->GetYaxis()->SetNdivisions(504);
   Graph_Graph01019->GetYaxis()->SetLabelFont(42);
   Graph_Graph01019->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01019->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01019->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01019->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01019->GetYaxis()->SetTitleFont(42);
   Graph_Graph01019->GetZaxis()->SetLabelFont(42);
   Graph_Graph01019->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01019);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1020[33] = {
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
   Double_t Graph0_fy1020[33] = {
   0.002848274,
   0.9913166,
   1.032264,
   0.9953798,
   0.9862323,
   0.9719893,
   0.967872,
   0.9720596,
   0.9667307,
   0.9825498,
   0.9677074,
   0.9684374,
   0.9724257,
   0.9713243,
   0.949687,
   0.967383,
   0.9793484,
   0.9510198,
   0.9734977,
   1.000964,
   0.9707746,
   1.003206,
   0.9718457,
   0.9556687,
   0.9843304,
   1.17081,
   0.945735,
   0.9021188,
   1.052217,
   0.840193,
   0.8671633,
   1.048511,
   1.02521};
   Double_t Graph0_fex1020[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1020[33] = {
   0.4236592,
   0.0642651,
   0.02853915,
   0.01742945,
   0.012956,
   0.01084499,
   0.0097925,
   0.009494493,
   0.009391395,
   0.009639568,
   0.009909194,
   0.01043312,
   0.008074278,
   0.009177453,
   0.01050469,
   0.01235119,
   0.01454191,
   0.01688466,
   0.02017717,
   0.02452185,
   0.0281752,
   0.03347912,
   0.04009933,
   0.04622743,
   0.05606011,
   0.07734696,
   0.07784218,
   0.09311451,
   0.1198334,
   0.1470187,
   0.1651726,
   0.1856619,
   0.227722};
   gre = new TGraphErrors(33,Graph0_fx1020,Graph0_fy1020,Graph0_fex1020,Graph0_fey1020);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010191020 = new TH1F("Graph_Graph_Graph010191020","",100,0,3);
   Graph_Graph_Graph010191020->SetMinimum(0.84);
   Graph_Graph_Graph010191020->SetMaximum(1.16);
   Graph_Graph_Graph010191020->SetDirectory(0);
   Graph_Graph_Graph010191020->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010191020->SetLineColor(ci);
   Graph_Graph_Graph010191020->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010191020->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010191020->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010191020->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010191020->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010191020->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010191020->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010191020->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010191020->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010191020->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010191020->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010191020->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010191020->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010191020->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010191020->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010191020->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010191020->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010191020->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010191020->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010191020);
   
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
   
   Double_t Graph1_fx1021[33] = {
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
   Double_t Graph1_fy1021[33] = {
   61.17964,
   16.66357,
   8.918284,
   5.59748,
   0.9982702,
   1.017947,
   1.023107,
   1.02753,
   1.019727,
   1.008985,
   1.00243,
   0.9996421,
   0.996419,
   0.9927576,
   0.9940428,
   0.9923387,
   0.9882272,
   0.982298,
   0.9800393,
   0.9940122,
   0.9742803,
   0.961824,
   0.9664516,
   0.945199,
   0.9629072,
   0.9954873,
   0.911189,
   0.9260976,
   0.9519062,
   0.931576,
   0.8982507,
   1.121067,
   1.010766};
   Double_t Graph1_fex1021[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1021[33] = {
   13.45671,
   0.50137,
   0.1192879,
   0.04646643,
   0.007531487,
   0.00637462,
   0.00576588,
   0.005602,
   0.005523595,
   0.005617792,
   0.005774576,
   0.006069868,
   0.004596502,
   0.005226928,
   0.00602255,
   0.007048059,
   0.008254435,
   0.009606576,
   0.01140648,
   0.01389461,
   0.01586629,
   0.01855178,
   0.02241902,
   0.02558314,
   0.03119283,
   0.04224556,
   0.04225048,
   0.0513884,
   0.06520789,
   0.08261828,
   0.08977753,
   0.1133313,
   0.1287081};
   gre = new TGraphErrors(33,Graph1_fx1021,Graph1_fy1021,Graph1_fex1021,Graph1_fey1021);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11021 = new TH1F("Graph_Graph11021","",100,0,3.1325);
   Graph_Graph11021->SetMinimum(0.84);
   Graph_Graph11021->SetMaximum(1.16);
   Graph_Graph11021->SetDirectory(0);
   Graph_Graph11021->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11021->SetLineColor(ci);
   Graph_Graph11021->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11021->GetXaxis()->SetLabelFont(42);
   Graph_Graph11021->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11021->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11021->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11021->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11021->GetXaxis()->SetTitleFont(42);
   Graph_Graph11021->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11021->GetYaxis()->CenterTitle(true);
   Graph_Graph11021->GetYaxis()->SetNdivisions(504);
   Graph_Graph11021->GetYaxis()->SetLabelFont(42);
   Graph_Graph11021->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11021->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11021->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11021->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11021->GetYaxis()->SetTitleFont(42);
   Graph_Graph11021->GetZaxis()->SetLabelFont(42);
   Graph_Graph11021->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11021->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11021);
   
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
   
   Double_t Graph2_fx1022[33] = {
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
   Double_t Graph2_fy1022[33] = {
   3.174406,
   1.057949,
   0.9295272,
   0.9392808,
   0.9566594,
   0.9588488,
   0.9258286,
   0.9600146,
   0.9565335,
   0.9584903,
   0.9335841,
   0.9721531,
   0.9292032,
   0.9554642,
   0.9502483,
   0.9121475,
   0.9729922,
   0.9351361,
   0.9428078,
   0.946088,
   0.8471476,
   0.8798903,
   1.09373,
   0.9848801,
   0.7689196,
   1.08969,
   1.072812,
   0.9958252,
   0.5114001,
   1.410676,
   0.300052,
   0.9801691,
   1.144778};
   Double_t Graph2_fex1022[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1022[33] = {
   1.279248,
   0.1549453,
   0.0672948,
   0.04084399,
   0.02975689,
   0.02501559,
   0.02264115,
   0.02203633,
   0.02184585,
   0.02230646,
   0.02288341,
   0.02397547,
   0.01812764,
   0.02031011,
   0.0229249,
   0.02629682,
   0.030582,
   0.03527618,
   0.04163725,
   0.0498653,
   0.05723647,
   0.06729905,
   0.08153363,
   0.09363961,
   0.1113059,
   0.1494578,
   0.1571328,
   0.1886507,
   0.2314685,
   0.3154243,
   0.3263695,
   0.3587685,
   0.4454117};
   gre = new TGraphErrors(33,Graph2_fx1022,Graph2_fy1022,Graph2_fex1022,Graph2_fey1022);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21022 = new TH1F("Graph_Graph21022","",100,0,3.1325);
   Graph_Graph21022->SetMinimum(0.84);
   Graph_Graph21022->SetMaximum(1.16);
   Graph_Graph21022->SetDirectory(0);
   Graph_Graph21022->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21022->SetLineColor(ci);
   Graph_Graph21022->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21022->GetXaxis()->SetLabelFont(42);
   Graph_Graph21022->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21022->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21022->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21022->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21022->GetXaxis()->SetTitleFont(42);
   Graph_Graph21022->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21022->GetYaxis()->CenterTitle(true);
   Graph_Graph21022->GetYaxis()->SetNdivisions(504);
   Graph_Graph21022->GetYaxis()->SetLabelFont(42);
   Graph_Graph21022->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21022->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21022->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21022->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21022->GetYaxis()->SetTitleFont(42);
   Graph_Graph21022->GetZaxis()->SetLabelFont(42);
   Graph_Graph21022->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21022->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21022);
   
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
   
   Double_t Graph3_fx1023[33] = {
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
   Double_t Graph3_fy1023[33] = {
   0.9944535,
   0.9669502,
   1.007983,
   1.026475,
   1.024505,
   1.021479,
   1.02274,
   1.023009,
   1.017086,
   1.017952,
   1.017137,
   1.019477,
   1.008933,
   1.002551,
   1.009894,
   1.003718,
   0.9984407,
   0.999916,
   0.9944172,
   1.008762,
   1.003649,
   0.9984737,
   1.015649,
   1.001375,
   1.022111,
   1.050944,
   1.051884,
   0.9745171,
   0.9580215,
   1.000513,
   1.029375,
   1.027282,
   1.039894};
   Double_t Graph3_fex1023[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1023[33] = {
   0.3066267,
   0.03989995,
   0.01783314,
   0.01106454,
   0.00814787,
   0.006810822,
   0.006154157,
   0.005975669,
   0.005919489,
   0.006087997,
   0.006312272,
   0.006693003,
   0.005118152,
   0.005879519,
   0.006860653,
   0.008075791,
   0.009514327,
   0.01117112,
   0.01329033,
   0.01619946,
   0.01872147,
   0.02205528,
   0.02682764,
   0.03085907,
   0.03759373,
   0.05055514,
   0.05354197,
   0.06216638,
   0.07704332,
   0.1010433,
   0.1139956,
   0.1242466,
   0.1530937};
   gre = new TGraphErrors(33,Graph3_fx1023,Graph3_fy1023,Graph3_fex1023,Graph3_fey1023);
   gre->SetName("Graph3");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31023 = new TH1F("Graph_Graph31023","",100,0,3.1325);
   Graph_Graph31023->SetMinimum(0.84);
   Graph_Graph31023->SetMaximum(1.16);
   Graph_Graph31023->SetDirectory(0);
   Graph_Graph31023->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31023->SetLineColor(ci);
   Graph_Graph31023->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31023->GetXaxis()->SetLabelFont(42);
   Graph_Graph31023->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph31023->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph31023->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph31023->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31023->GetXaxis()->SetTitleFont(42);
   Graph_Graph31023->GetYaxis()->SetTitle("Ratio");
   Graph_Graph31023->GetYaxis()->CenterTitle(true);
   Graph_Graph31023->GetYaxis()->SetNdivisions(504);
   Graph_Graph31023->GetYaxis()->SetLabelFont(42);
   Graph_Graph31023->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph31023->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph31023->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph31023->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph31023->GetYaxis()->SetTitleFont(42);
   Graph_Graph31023->GetZaxis()->SetLabelFont(42);
   Graph_Graph31023->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31023->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31023);
   
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
   
   Double_t Graph4_fx1024[33] = {
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
   Double_t Graph4_fy1024[33] = {
   1.009274,
   1.008763,
   1.008446,
   1.008132,
   1.007931,
   1.007734,
   1.007613,
   1.007471,
   1.007404,
   1.007329,
   1.007304,
   1.007296,
   1.007289,
   1.007317,
   1.007339,
   1.007354,
   1.007405,
   1.007393,
   1.007511,
   1.007546,
   1.007572,
   1.007902,
   1.008186,
   1.00828,
   1.00848,
   1.008795,
   1.008943,
   1.009243,
   1.00867,
   1.009255,
   1.009434,
   1.009806,
   1.010108};
   Double_t Graph4_fex1024[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1024[33] = {
   0.303871,
   0.04021311,
   0.01758014,
   0.01079313,
   0.00795396,
   0.006658583,
   0.006011127,
   0.005834695,
   0.005797608,
   0.005958588,
   0.006180281,
   0.006544586,
   0.005030849,
   0.005797727,
   0.006740174,
   0.007957769,
   0.009400393,
   0.01103155,
   0.01316076,
   0.01593131,
   0.01846145,
   0.02181551,
   0.02632957,
   0.03050171,
   0.03680918,
   0.0488311,
   0.05169451,
   0.06236304,
   0.07787489,
   0.1000814,
   0.1112641,
   0.1217608,
   0.1488689};
   gre = new TGraphErrors(33,Graph4_fx1024,Graph4_fy1024,Graph4_fex1024,Graph4_fey1024);
   gre->SetName("Graph4");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41024 = new TH1F("Graph_Graph41024","",100,0,3.1325);
   Graph_Graph41024->SetMinimum(0.84);
   Graph_Graph41024->SetMaximum(1.16);
   Graph_Graph41024->SetDirectory(0);
   Graph_Graph41024->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41024->SetLineColor(ci);
   Graph_Graph41024->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41024->GetXaxis()->SetLabelFont(42);
   Graph_Graph41024->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph41024->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph41024->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph41024->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41024->GetXaxis()->SetTitleFont(42);
   Graph_Graph41024->GetYaxis()->SetTitle("Ratio");
   Graph_Graph41024->GetYaxis()->CenterTitle(true);
   Graph_Graph41024->GetYaxis()->SetNdivisions(504);
   Graph_Graph41024->GetYaxis()->SetLabelFont(42);
   Graph_Graph41024->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph41024->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph41024->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph41024->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph41024->GetYaxis()->SetTitleFont(42);
   Graph_Graph41024->GetZaxis()->SetLabelFont(42);
   Graph_Graph41024->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41024->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41024);
   
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
   10-40%, #pi+->cd();
   10-40%, #pi+->Modified();
   10-40%, #pi+->cd();
   10-40%, #pi+->SetSelected(10-40%, #pi+);
}
