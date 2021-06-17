void proton_posDFCent10_40()
{
//=========Macro generated from canvas: c1_n5/Canvas
//=========  (Fri Apr 23 20:00:15 2021) by ROOT version 6.22/08
   TCanvas *c1_n5 = new TCanvas("c1_n5", "Canvas",0,0,550,550);
   c1_n5->Range(0,0,1,1);
   c1_n5->SetFillColor(0);
   c1_n5->SetBorderMode(0);
   c1_n5->SetBorderSize(2);
   c1_n5->SetTickx(1);
   c1_n5->SetTicky(1);
   c1_n5->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1025[33] = {
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
   Double_t Graph0_fy1025[33] = {
   -0.004358653,
   -0.0006786801,
   0.0005597108,
   0.001156612,
   0.001826046,
   0.002511067,
   0.005156142,
   0.006547017,
   0.01010138,
   0.01250085,
   0.01613638,
   0.01920729,
   0.02497497,
   0.03278788,
   0.04022141,
   0.04751932,
   0.05392864,
   0.06014033,
   0.06478431,
   0.07022345,
   0.07534271,
   0.07955069,
   0.08349102,
   0.08815113,
   0.09084881,
   0.092968,
   0.09743003,
   0.09912215,
   0.09934128,
   0.1024195,
   0.1043925,
   0.1038703,
   0.1077164};
   Double_t Graph0_fex1025[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1025[33] = {
   0.003575846,
   0.001364534,
   0.0008427941,
   0.0006195399,
   0.0004979773,
   0.0004235686,
   0.0003740888,
   0.0003400375,
   0.000315779,
   0.0002986349,
   0.0002867582,
   0.0002789027,
   0.0001925802,
   0.0001935719,
   0.0002010339,
   0.0002146039,
   0.0002343569,
   0.0002608324,
   0.0002949194,
   0.0003380557,
   0.0003917436,
   0.0004585564,
   0.0005412937,
   0.0006425915,
   0.000768274,
   0.0009220621,
   0.001111746,
   0.001343336,
   0.001629666,
   0.001976297,
   0.002408232,
   0.002275263,
   0.003024232};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1025,Graph0_fy1025,Graph0_fex1025,Graph0_fey1025);
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
   
   TH1F *Graph_Graph01025 = new TH1F("Graph_Graph01025","",100,0,3);
   Graph_Graph01025->SetMinimum(-0.01);
   Graph_Graph01025->SetMaximum(0.2);
   Graph_Graph01025->SetDirectory(0);
   Graph_Graph01025->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01025->SetLineColor(ci);
   Graph_Graph01025->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01025->GetXaxis()->SetLabelFont(42);
   Graph_Graph01025->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01025->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01025->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01025->GetXaxis()->SetTitleFont(42);
   Graph_Graph01025->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01025->GetYaxis()->SetLabelFont(42);
   Graph_Graph01025->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01025->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01025->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01025->GetYaxis()->SetTitleFont(42);
   Graph_Graph01025->GetZaxis()->SetLabelFont(42);
   Graph_Graph01025->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01025->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01025);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1026[33] = {
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
   Double_t Graph1_fy1026[33] = {
   -0.004111586,
   0.001890937,
   0.002406764,
   0.001693558,
   0.003182124,
   0.004934917,
   0.006524835,
   0.007782733,
   0.009859511,
   0.01341739,
   0.01613992,
   0.01917303,
   0.02439866,
   0.03163699,
   0.03858767,
   0.04558809,
   0.05130116,
   0.05731787,
   0.06225562,
   0.06757447,
   0.07308638,
   0.07590859,
   0.07993535,
   0.08139729,
   0.08498108,
   0.08533464,
   0.0893884,
   0.09640062,
   0.0946602,
   0.1004216,
   0.09516299,
   0.105103,
   0.09745432};
   Double_t Graph1_fex1026[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1026[33] = {
   0.006946108,
   0.002650008,
   0.001636557,
   0.001201325,
   0.0009642268,
   0.0008190535,
   0.0007226688,
   0.0006562357,
   0.0006092167,
   0.0005762547,
   0.0005537405,
   0.0005391219,
   0.0003760778,
   0.0003806245,
   0.0003977358,
   0.0004266902,
   0.0004669907,
   0.0005201398,
   0.000587446,
   0.0006725743,
   0.0007780196,
   0.0009082673,
   0.001069801,
   0.001267957,
   0.001514052,
   0.001814192,
   0.00218521,
   0.002637997,
   0.003202181,
   0.003886341,
   0.004729827,
   0.004474435,
   0.005947693};
   gre = new TGraphErrors(33,Graph1_fx1026,Graph1_fy1026,Graph1_fex1026,Graph1_fey1026);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11026 = new TH1F("Graph_Graph11026","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11026->SetMinimum(-0.02312121);
   Graph_Graph11026->SetMaximum(0.121641);
   Graph_Graph11026->SetDirectory(0);
   Graph_Graph11026->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11026->SetLineColor(ci);
   Graph_Graph11026->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11026->GetXaxis()->SetLabelFont(42);
   Graph_Graph11026->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11026->GetXaxis()->SetTitleFont(42);
   Graph_Graph11026->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11026->GetYaxis()->SetLabelFont(42);
   Graph_Graph11026->GetYaxis()->SetTitleFont(42);
   Graph_Graph11026->GetZaxis()->SetLabelFont(42);
   Graph_Graph11026->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11026->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11026);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1027[33] = {
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
   Double_t Graph2_fy1027[33] = {
   -0.1145325,
   -0.1129215,
   -0.1117982,
   -0.1119469,
   0.000208792,
   0.000871505,
   0.001736067,
   0.003000794,
   0.005260734,
   0.007682936,
   0.01061447,
   0.0138122,
   0.01937411,
   0.02752585,
   0.03566489,
   0.04363215,
   0.05051079,
   0.05718664,
   0.06270769,
   0.06862678,
   0.07357083,
   0.07806307,
   0.08225741,
   0.08616975,
   0.08947215,
   0.09246105,
   0.09511074,
   0.09731134,
   0.09853521,
   0.1007344,
   0.1043448,
   0.1021711,
   0.1057633};
   Double_t Graph2_fex1027[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1027[33] = {
   0.00268405,
   0.001028296,
   0.0006396793,
   0.0004743261,
   0.0003795127,
   0.0003246534,
   0.0002882296,
   0.0002632372,
   0.0002451955,
   0.0002324809,
   0.0002235812,
   0.0002176787,
   0.0001505073,
   0.0001511101,
   0.0001565028,
   0.0001663814,
   0.0001807756,
   0.0001999651,
   0.0002246673,
   0.0002559462,
   0.0002948929,
   0.0003435668,
   0.0004038238,
   0.0004781045,
   0.0005695821,
   0.0006825191,
   0.0008217043,
   0.0009904727,
   0.001201144,
   0.001456239,
   0.001771518,
   0.001674331,
   0.002223434};
   gre = new TGraphErrors(33,Graph2_fx1027,Graph2_fy1027,Graph2_fex1027,Graph2_fey1027);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21027 = new TH1F("Graph_Graph21027","v_{2}{2}",100,0,3.1325);
   Graph_Graph21027->SetMinimum(-0.1397369);
   Graph_Graph21027->SetMaximum(0.130507);
   Graph_Graph21027->SetDirectory(0);
   Graph_Graph21027->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21027->SetLineColor(ci);
   Graph_Graph21027->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21027->GetXaxis()->SetLabelFont(42);
   Graph_Graph21027->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21027->GetXaxis()->SetTitleFont(42);
   Graph_Graph21027->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21027->GetYaxis()->SetLabelFont(42);
   Graph_Graph21027->GetYaxis()->SetTitleFont(42);
   Graph_Graph21027->GetZaxis()->SetLabelFont(42);
   Graph_Graph21027->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21027->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21027);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1028[33] = {
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
   Double_t Graph3_fy1028[33] = {
   0.01308966,
   -0.002512235,
   0.0004161091,
   0.004533347,
   4.262976e-05,
   0.002573978,
   0.004370482,
   0.006541078,
   0.00952075,
   0.01317915,
   0.01441597,
   0.01838819,
   0.02402701,
   0.02947189,
   0.03683262,
   0.04397648,
   0.05201027,
   0.05851599,
   0.06145634,
   0.06623811,
   0.07054183,
   0.07555549,
   0.08081285,
   0.08376973,
   0.08324253,
   0.0891008,
   0.0861917,
   0.08903407,
   0.0951288,
   0.09755319,
   0.1163423,
   0.1063349,
   0.09685142};
   Double_t Graph3_fex1028[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1028[33] = {
   0.01620971,
   0.006210395,
   0.003870213,
   0.002872871,
   0.002288044,
   0.001965014,
   0.00175108,
   0.001604887,
   0.001497132,
   0.001422049,
   0.00136938,
   0.001333654,
   0.0009235686,
   0.000927546,
   0.0009623609,
   0.001024517,
   0.001111064,
   0.001222526,
   0.001360703,
   0.001537433,
   0.001758395,
   0.002037427,
   0.00237977,
   0.002792218,
   0.003298596,
   0.00394806,
   0.004744309,
   0.0056764,
   0.006874453,
   0.008301095,
   0.01013889,
   0.009560484,
   0.01264495};
   gre = new TGraphErrors(33,Graph3_fx1028,Graph3_fy1028,Graph3_fex1028,Graph3_fey1028);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31028 = new TH1F("Graph_Graph31028","v_{2}{4}",100,0,3.1325);
   Graph_Graph31028->SetMinimum(-0.02224301);
   Graph_Graph31028->SetMaximum(0.1400015);
   Graph_Graph31028->SetDirectory(0);
   Graph_Graph31028->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31028->SetLineColor(ci);
   Graph_Graph31028->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31028->GetXaxis()->SetLabelFont(42);
   Graph_Graph31028->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31028->GetXaxis()->SetTitleFont(42);
   Graph_Graph31028->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31028->GetYaxis()->SetLabelFont(42);
   Graph_Graph31028->GetYaxis()->SetTitleFont(42);
   Graph_Graph31028->GetZaxis()->SetLabelFont(42);
   Graph_Graph31028->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31028->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31028);
   
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
   pt_LaTex = pt->AddText("10-40%, p");
   pt->Draw();
   padUp->Modified();
   c1_n5->cd();
  
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
   
   Double_t Graph0_fx1029[33] = {
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
   Double_t Graph0_fy1029[33] = {
   0.9433158,
   2.786197,
   4.300013,
   1.464241,
   1.742631,
   1.965267,
   1.265449,
   1.188745,
   0.9760557,
   1.073317,
   1.000219,
   0.9982163,
   0.9769246,
   0.9648989,
   0.9593814,
   0.9593591,
   0.9512787,
   0.9530687,
   0.9609677,
   0.9622779,
   0.9700525,
   0.9542167,
   0.9574126,
   0.9233833,
   0.9354122,
   0.9178927,
   0.9174625,
   0.9725437,
   0.9528788,
   0.9804931,
   0.9115882,
   1.011868,
   0.9047303};
   Double_t Graph0_fex1029[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1029[33] = {
   1.771608,
   6.828392,
   7.104411,
   1.301527,
   0.7104014,
   0.4650652,
   0.1675506,
   0.1177236,
   0.06758945,
   0.05274843,
   0.03864648,
   0.03159026,
   0.01683731,
   0.01293106,
   0.01098996,
   0.009969916,
   0.009595581,
   0.00958578,
   0.01006782,
   0.01063909,
   0.01149236,
   0.01267333,
   0.01423766,
   0.01588096,
   0.01844771,
   0.02153323,
   0.02475148,
   0.02969852,
   0.03582444,
   0.04240051,
   0.04995059,
   0.048445,
   0.06077866};
   gre = new TGraphErrors(33,Graph0_fx1029,Graph0_fy1029,Graph0_fex1029,Graph0_fey1029);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01029 = new TH1F("Graph_Graph01029","",100,0,3);
   Graph_Graph01029->SetMinimum(0.84);
   Graph_Graph01029->SetMaximum(1.16);
   Graph_Graph01029->SetDirectory(0);
   Graph_Graph01029->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01029->SetLineColor(ci);
   Graph_Graph01029->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01029->GetXaxis()->SetLabelFont(42);
   Graph_Graph01029->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01029->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01029->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01029->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01029->GetXaxis()->SetTitleFont(42);
   Graph_Graph01029->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01029->GetYaxis()->CenterTitle(true);
   Graph_Graph01029->GetYaxis()->SetNdivisions(504);
   Graph_Graph01029->GetYaxis()->SetLabelFont(42);
   Graph_Graph01029->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01029->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01029->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01029->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01029->GetYaxis()->SetTitleFont(42);
   Graph_Graph01029->GetZaxis()->SetLabelFont(42);
   Graph_Graph01029->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01029->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01029);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1030[33] = {
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
   Double_t Graph0_fy1030[33] = {
   0.9433158,
   2.786197,
   4.300013,
   1.464241,
   1.742631,
   1.965267,
   1.265449,
   1.188745,
   0.9760557,
   1.073317,
   1.000219,
   0.9982163,
   0.9769246,
   0.9648989,
   0.9593814,
   0.9593591,
   0.9512787,
   0.9530687,
   0.9609677,
   0.9622779,
   0.9700525,
   0.9542167,
   0.9574126,
   0.9233833,
   0.9354122,
   0.9178927,
   0.9174625,
   0.9725437,
   0.9528788,
   0.9804931,
   0.9115882,
   1.011868,
   0.9047303};
   Double_t Graph0_fex1030[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1030[33] = {
   1.771608,
   6.828392,
   7.104411,
   1.301527,
   0.7104014,
   0.4650652,
   0.1675506,
   0.1177236,
   0.06758945,
   0.05274843,
   0.03864648,
   0.03159026,
   0.01683731,
   0.01293106,
   0.01098996,
   0.009969916,
   0.009595581,
   0.00958578,
   0.01006782,
   0.01063909,
   0.01149236,
   0.01267333,
   0.01423766,
   0.01588096,
   0.01844771,
   0.02153323,
   0.02475148,
   0.02969852,
   0.03582444,
   0.04240051,
   0.04995059,
   0.048445,
   0.06077866};
   gre = new TGraphErrors(33,Graph0_fx1030,Graph0_fy1030,Graph0_fex1030,Graph0_fey1030);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010291030 = new TH1F("Graph_Graph_Graph010291030","",100,0,3);
   Graph_Graph_Graph010291030->SetMinimum(0.84);
   Graph_Graph_Graph010291030->SetMaximum(1.16);
   Graph_Graph_Graph010291030->SetDirectory(0);
   Graph_Graph_Graph010291030->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010291030->SetLineColor(ci);
   Graph_Graph_Graph010291030->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010291030->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010291030->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010291030->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010291030->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010291030->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010291030->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010291030->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010291030->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010291030->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010291030->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010291030->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010291030->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010291030->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010291030->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010291030->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010291030->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010291030->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010291030->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010291030);
   
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
   
   Double_t Graph1_fx1031[33] = {
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
   Double_t Graph1_fy1031[33] = {
   26.27704,
   166.3839,
   199.7428,
   96.78862,
   0.114341,
   0.3470656,
   0.3366988,
   0.4583452,
   0.5207935,
   0.6145929,
   0.6577972,
   0.719112,
   0.7757411,
   0.8395131,
   0.8867142,
   0.9181981,
   0.9366228,
   0.9508867,
   0.9679458,
   0.977263,
   0.9764824,
   0.9812997,
   0.9852247,
   0.9775229,
   0.9848467,
   0.9945471,
   0.9761953,
   0.9817315,
   0.9918859,
   0.9835476,
   0.9995433,
   0.9836411,
   0.9818676};
   Double_t Graph1_fex1031[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1031[33] = {
   21.56652,
   334.5299,
   300.7683,
   51.84652,
   0.2101592,
   0.1419259,
   0.06100471,
   0.04672598,
   0.02922766,
   0.02369431,
   0.01812813,
   0.01541022,
   0.008491004,
   0.006767943,
   0.005897661,
   0.00542721,
   0.005272935,
   0.00529748,
   0.0056074,
   0.005951206,
   0.006410742,
   0.007116796,
   0.008012097,
   0.008955085,
   0.01042453,
   0.01229613,
   0.01397168,
   0.01663927,
   0.02027214,
   0.02371395,
   0.02862982,
   0.02690889,
   0.03443837};
   gre = new TGraphErrors(33,Graph1_fx1031,Graph1_fy1031,Graph1_fex1031,Graph1_fey1031);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11031 = new TH1F("Graph_Graph11031","",100,0,3.1325);
   Graph_Graph11031->SetMinimum(0.84);
   Graph_Graph11031->SetMaximum(1.16);
   Graph_Graph11031->SetDirectory(0);
   Graph_Graph11031->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11031->SetLineColor(ci);
   Graph_Graph11031->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11031->GetXaxis()->SetLabelFont(42);
   Graph_Graph11031->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11031->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11031->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11031->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11031->GetXaxis()->SetTitleFont(42);
   Graph_Graph11031->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11031->GetYaxis()->CenterTitle(true);
   Graph_Graph11031->GetYaxis()->SetNdivisions(504);
   Graph_Graph11031->GetYaxis()->SetLabelFont(42);
   Graph_Graph11031->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11031->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11031->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11031->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11031->GetYaxis()->SetTitleFont(42);
   Graph_Graph11031->GetZaxis()->SetLabelFont(42);
   Graph_Graph11031->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11031->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11031);
   
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
   
   Double_t Graph2_fx1032[33] = {
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
   Double_t Graph2_fy1032[33] = {
   3.003143,
   3.701648,
   0.7434359,
   3.919506,
   0.0233454,
   1.025053,
   0.8476263,
   0.9990929,
   0.9425195,
   1.05426,
   0.8933831,
   0.9573545,
   0.9620437,
   0.8988656,
   0.9157467,
   0.9254443,
   0.9644276,
   0.9729908,
   0.9486301,
   0.9432477,
   0.9362795,
   0.949778,
   0.9679226,
   0.9502967,
   0.9162754,
   0.958403,
   0.8846523,
   0.8982258,
   0.9575959,
   0.9524867,
   1.114469,
   1.023727,
   0.8991333};
   Double_t Graph2_fex1032[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1032[33] = {
   4.461051,
   11.79512,
   7.004694,
   3.252298,
   1.253021,
   0.8014161,
   0.3451336,
   0.2505647,
   0.151111,
   0.1165108,
   0.08633521,
   0.07081268,
   0.0377165,
   0.02878273,
   0.02436044,
   0.02196137,
   0.02102445,
   0.02076129,
   0.02144295,
   0.02235938,
   0.02384094,
   0.02619031,
   0.02918592,
   0.032424,
   0.03712624,
   0.04351769,
   0.04972983,
   0.05854622,
   0.07096102,
   0.08310774,
   0.100468,
   0.09473482,
   0.1200747};
   gre = new TGraphErrors(33,Graph2_fx1032,Graph2_fy1032,Graph2_fex1032,Graph2_fey1032);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21032 = new TH1F("Graph_Graph21032","",100,0,3.1325);
   Graph_Graph21032->SetMinimum(0.84);
   Graph_Graph21032->SetMaximum(1.16);
   Graph_Graph21032->SetDirectory(0);
   Graph_Graph21032->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21032->SetLineColor(ci);
   Graph_Graph21032->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21032->GetXaxis()->SetLabelFont(42);
   Graph_Graph21032->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21032->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21032->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21032->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21032->GetXaxis()->SetTitleFont(42);
   Graph_Graph21032->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21032->GetYaxis()->CenterTitle(true);
   Graph_Graph21032->GetYaxis()->SetNdivisions(504);
   Graph_Graph21032->GetYaxis()->SetLabelFont(42);
   Graph_Graph21032->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21032->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21032->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21032->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21032->GetYaxis()->SetTitleFont(42);
   Graph_Graph21032->GetZaxis()->SetLabelFont(42);
   Graph_Graph21032->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21032->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21032);
   
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
   c1_n5->cd();
   c1_n5->Modified();
   c1_n5->cd();
   c1_n5->SetSelected(c1_n5);
}
