void kaon_posDFCent10-40()
{
//=========Macro generated from canvas: 10-40%, K+/Canvas
//=========  (Fri Apr 23 19:43:59 2021) by ROOT version 6.22/08
   TCanvas *10-40%, K+ = new TCanvas("10-40%, K+", "Canvas",0,0,550,550);
   10-40%, K+->Range(0,0,1,1);
   10-40%, K+->SetFillColor(0);
   10-40%, K+->SetBorderMode(0);
   10-40%, K+->SetBorderSize(2);
   10-40%, K+->SetTickx(1);
   10-40%, K+->SetTicky(1);
   10-40%, K+->SetFrameBorderMode(0);
  
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
   -0.006622509,
   0.001596631,
   0.002829771,
   0.005216581,
   0.008782527,
   0.01132458,
   0.01363808,
   0.01768826,
   0.02151993,
   0.02439597,
   0.02707198,
   0.02915599,
   0.03251399,
   0.03626714,
   0.04016934,
   0.04295557,
   0.04503207,
   0.04595662,
   0.05023074,
   0.05364766,
   0.0554666,
   0.06009137,
   0.06000731,
   0.06236116,
   0.06544173,
   0.07055854,
   0.07462398,
   0.07693074,
   0.0750011,
   0.08184791,
   0.0803918,
   0.08025817,
   0.1047949};
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
   0.003075232,
   0.001201277,
   0.0007707774,
   0.0005958368,
   0.0005079155,
   0.0004604632,
   0.0004352886,
   0.0004242855,
   0.0004233775,
   0.0004300871,
   0.0004429967,
   0.0004617853,
   0.0003520525,
   0.0003987194,
   0.0004591543,
   0.0005350711,
   0.0006294334,
   0.0007454475,
   0.0008902424,
   0.001068643,
   0.001291131,
   0.0015669,
   0.001913376,
   0.002340896,
   0.002876366,
   0.003524716,
   0.004364088,
   0.005392513,
   0.006630582,
   0.008236341,
   0.01016324,
   0.009811782,
   0.01352286};
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
   0.0005475076,
   0.002799373,
   0.002924346,
   0.007794257,
   0.008353907,
   0.01105926,
   0.01441075,
   0.01676576,
   0.02049874,
   0.02167147,
   0.02608249,
   0.02844305,
   0.0311136,
   0.03275415,
   0.03754592,
   0.04171292,
   0.04215726,
   0.04436629,
   0.04580504,
   0.04970914,
   0.0560348,
   0.05570214,
   0.05990666,
   0.05878936,
   0.06010538,
   0.07495602,
   0.05925914,
   0.07244528,
   0.07429127,
   0.06080616,
   0.06575149,
   0.07407971,
   0.07109349};
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
   0.0060393,
   0.002348599,
   0.001506833,
   0.001162794,
   0.0009903476,
   0.00089682,
   0.0008478083,
   0.0008262786,
   0.0008252766,
   0.0008381123,
   0.0008641892,
   0.0009008829,
   0.0006896508,
   0.0007806746,
   0.0008994865,
   0.001048074,
   0.001232814,
   0.001458891,
   0.001741733,
   0.002091544,
   0.002527451,
   0.003069563,
   0.003735782,
   0.004582766,
   0.005633639,
   0.006910251,
   0.008529624,
   0.01051957,
   0.01301942,
   0.01595969,
   0.01962868,
   0.01904693,
   0.02634179};
   gre = new TGraphErrors(33,Graph1_fx1026,Graph1_fy1026,Graph1_fex1026,Graph1_fey1026);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11026 = new TH1F("Graph_Graph11026","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11026->SetMinimum(-0.0157845);
   Graph_Graph11026->SetMaximum(0.107728);
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
   -0.1182856,
   -0.1099843,
   -0.1087807,
   -0.1064735,
   0.007684316,
   0.01063119,
   0.01332166,
   0.01701314,
   0.02034725,
   0.02280875,
   0.02576891,
   0.02829584,
   0.0312869,
   0.0359708,
   0.03989522,
   0.04261522,
   0.04506954,
   0.04629509,
   0.04988987,
   0.05297074,
   0.05400501,
   0.05943696,
   0.0615261,
   0.05978098,
   0.06359341,
   0.06549781,
   0.07228318,
   0.07101125,
   0.07185548,
   0.07661344,
   0.08615741,
   0.08234038,
   0.09280193};
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
   0.002310209,
   0.0009055655,
   0.0005853683,
   0.0004559744,
   0.0003861496,
   0.0003511733,
   0.0003324268,
   0.0003241051,
   0.0003233543,
   0.0003279826,
   0.0003373211,
   0.0003508019,
   0.0002664851,
   0.0003001914,
   0.0003441468,
   0.0003995872,
   0.0004685827,
   0.0005534341,
   0.0006591021,
   0.0007899994,
   0.0009530709,
   0.001154661,
   0.001407898,
   0.001720216,
   0.002112485,
   0.00258679,
   0.003201615,
   0.003938864,
   0.004847875,
   0.005985608,
   0.007394936,
   0.007149768,
   0.009780101};
   gre = new TGraphErrors(33,Graph2_fx1027,Graph2_fy1027,Graph2_fex1027,Graph2_fey1027);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21027 = new TH1F("Graph_Graph21027","v_{2}{2}",100,0,3.1325);
   Graph_Graph21027->SetMinimum(-0.1429135);
   Graph_Graph21027->SetMaximum(0.1248998);
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
   -0.009588012,
   0.009781274,
   0.004306531,
   0.007689745,
   0.00648454,
   0.01051252,
   0.01617792,
   0.01526005,
   0.01839929,
   0.02090106,
   0.02736528,
   0.02882135,
   0.03026891,
   0.03168573,
   0.03720324,
   0.03820336,
   0.04930876,
   0.04399146,
   0.04242503,
   0.04693444,
   0.05899242,
   0.0648108,
   0.05188055,
   0.0573848,
   0.05764153,
   0.07066765,
   0.0467884,
   0.05353401,
   0.04693086,
   0.07671667,
   0.0776811,
   0.03870332,
   0.2255752};
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
   0.01364545,
   0.005391633,
   0.003491408,
   0.002723868,
   0.002290625,
   0.002086054,
   0.00197576,
   0.001927313,
   0.001921113,
   0.001944543,
   0.001995003,
   0.002074941,
   0.001571573,
   0.001762852,
   0.002012404,
   0.002328248,
   0.002718419,
   0.003203352,
   0.003809149,
   0.004569671,
   0.005499801,
   0.006615272,
   0.008085434,
   0.009865719,
   0.01202241,
   0.01475936,
   0.01821144,
   0.02234941,
   0.0273813,
   0.03303004,
   0.0413745,
   0.04015031,
   0.05503864};
   gre = new TGraphErrors(33,Graph3_fx1028,Graph3_fy1028,Graph3_fex1028,Graph3_fey1028);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31028 = new TH1F("Graph_Graph31028","v_{2}{4}",100,0,3.1325);
   Graph_Graph31028->SetMinimum(-0.05361819);
   Graph_Graph31028->SetMaximum(0.3109985);
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
   
   Double_t Graph4_fx1029[33] = {
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
   Double_t Graph4_fy1029[33] = {
   -0.008068379,
   0.00122909,
   0.002236857,
   0.005511582,
   0.009577761,
   0.01223598,
   0.01450984,
   0.01823676,
   0.02175077,
   0.02504202,
   0.02737696,
   0.02961963,
   0.03282099,
   0.0363154,
   0.04008831,
   0.04309415,
   0.04559356,
   0.04619428,
   0.05027981,
   0.05342543,
   0.05665719,
   0.06074962,
   0.0604098,
   0.06374104,
   0.06533764,
   0.07286021,
   0.07915423,
   0.07349433,
   0.07322931,
   0.07360973,
   0.09058099,
   0.06995355,
   0.1066153};
   Double_t Graph4_fex1029[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1029[33] = {
   0.003195545,
   0.00124099,
   0.0007922326,
   0.0006092709,
   0.0005168959,
   0.0004667933,
   0.0004403016,
   0.0004288989,
   0.0004282594,
   0.0004355501,
   0.0004497329,
   0.0004696663,
   0.0003601498,
   0.0004096519,
   0.0004738087,
   0.0005539961,
   0.0006532927,
   0.000775163,
   0.0009270588,
   0.001115375,
   0.001349327,
   0.00163834,
   0.002003412,
   0.002454389,
   0.003013581,
   0.003706299,
   0.004572963,
   0.005660411,
   0.006986729,
   0.008628469,
   0.01069719,
   0.01034565,
   0.0142586};
   gre = new TGraphErrors(33,Graph4_fx1029,Graph4_fy1029,Graph4_fex1029,Graph4_fey1029);
   gre->SetName("Graph4");
   gre->SetTitle("v_{2}^{EP}{#Psi_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41029 = new TH1F("Graph_Graph41029","v_{2}^{EP}{#Psi_{2,TPC}}",100,0,3.1325);
   Graph_Graph41029->SetMinimum(-0.0244777);
   Graph_Graph41029->SetMaximum(0.1340876);
   Graph_Graph41029->SetDirectory(0);
   Graph_Graph41029->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41029->SetLineColor(ci);
   Graph_Graph41029->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41029->GetXaxis()->SetLabelFont(42);
   Graph_Graph41029->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41029->GetXaxis()->SetTitleFont(42);
   Graph_Graph41029->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph41029->GetYaxis()->SetLabelFont(42);
   Graph_Graph41029->GetYaxis()->SetTitleFont(42);
   Graph_Graph41029->GetZaxis()->SetLabelFont(42);
   Graph_Graph41029->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41029->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41029);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph5_fx1030[33] = {
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
   Double_t Graph5_fy1030[33] = {
   -0.006677939,
   0.001614178,
   0.002857863,
   0.005268296,
   0.008865802,
   0.01143082,
   0.01376888,
   0.01785673,
   0.02172389,
   0.02462615,
   0.02732409,
   0.02942703,
   0.03281591,
   0.03659713,
   0.04053319,
   0.04334382,
   0.0454378,
   0.04637257,
   0.05068165,
   0.05413671,
   0.05598064,
   0.06065134,
   0.06057911,
   0.06298195,
   0.06611422,
   0.07131176,
   0.07536918,
   0.07781688,
   0.07577671,
   0.08273284,
   0.08120024,
   0.08110847,
   0.1061325};
   Double_t Graph5_fex1030[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph5_fey1030[33] = {
   0.00308471,
   0.001201634,
   0.0007678054,
   0.0005903298,
   0.0005009972,
   0.0004527758,
   0.0004271635,
   0.0004162157,
   0.0004157016,
   0.0004229334,
   0.0004366168,
   0.000456239,
   0.0003498617,
   0.0003981436,
   0.0004604527,
   0.000538397,
   0.0006353079,
   0.0007540664,
   0.0009020712,
   0.001085314,
   0.001313687,
   0.001596804,
   0.001952796,
   0.002393237,
   0.002943358,
   0.003614002,
   0.004481657,
   0.005538004,
   0.006805931,
   0.008479692,
   0.0104888,
   0.01011607,
   0.01395546};
   gre = new TGraphErrors(33,Graph5_fx1030,Graph5_fy1030,Graph5_fex1030,Graph5_fey1030);
   gre->SetName("Graph5");
   gre->SetTitle("v_{2}^{SP}{Q_{2,TPC}}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph51030 = new TH1F("Graph_Graph51030","v_{2}^{SP}{Q_{2,TPC}}",100,0,3.1325);
   Graph_Graph51030->SetMinimum(-0.02274771);
   Graph_Graph51030->SetMaximum(0.133073);
   Graph_Graph51030->SetDirectory(0);
   Graph_Graph51030->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51030->SetLineColor(ci);
   Graph_Graph51030->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph51030->GetXaxis()->SetLabelFont(42);
   Graph_Graph51030->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51030->GetXaxis()->SetTitleFont(42);
   Graph_Graph51030->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph51030->GetYaxis()->SetLabelFont(42);
   Graph_Graph51030->GetYaxis()->SetTitleFont(42);
   Graph_Graph51030->GetZaxis()->SetLabelFont(42);
   Graph_Graph51030->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51030->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51030);
   
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
   pt_LaTex = pt->AddText("10-40%, K+");
   pt->Draw();
   padUp->Modified();
   10-40%, K+->cd();
  
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
   
   Double_t Graph0_fx1031[33] = {
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
   Double_t Graph0_fy1031[33] = {
   0.08267373,
   1.7533,
   1.033422,
   1.494131,
   0.9511963,
   0.9765712,
   1.056655,
   0.9478467,
   0.9525468,
   0.8883216,
   0.9634495,
   0.9755476,
   0.9569297,
   0.9031358,
   0.9346909,
   0.9710712,
   0.9361607,
   0.9653948,
   0.9118926,
   0.9265856,
   1.010244,
   0.9269574,
   0.9983227,
   0.9427239,
   0.9184564,
   1.062324,
   0.7941032,
   0.9416949,
   0.9905357,
   0.7429165,
   0.817888,
   0.9230177,
   0.6784062};
   Double_t Graph0_fex1031[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1031[33] = {
   0.912743,
   1.975835,
   0.6023143,
   0.2807322,
   0.1254659,
   0.08858974,
   0.07072384,
   0.05195247,
   0.04268337,
   0.03775565,
   0.03560282,
   0.03454663,
   0.02360635,
   0.02370528,
   0.02481058,
   0.02723281,
   0.0303428,
   0.03539714,
   0.03825606,
   0.04313504,
   0.05127733,
   0.05651152,
   0.06992161,
   0.0815641,
   0.09508162,
   0.11139,
   0.1233754,
   0.1518393,
   0.194427,
   0.2088322,
   0.2651541,
   0.2627819,
   0.2661732};
   gre = new TGraphErrors(33,Graph0_fx1031,Graph0_fy1031,Graph0_fex1031,Graph0_fey1031);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01031 = new TH1F("Graph_Graph01031","",100,0,3);
   Graph_Graph01031->SetMinimum(0.84);
   Graph_Graph01031->SetMaximum(1.16);
   Graph_Graph01031->SetDirectory(0);
   Graph_Graph01031->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01031->SetLineColor(ci);
   Graph_Graph01031->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01031->GetXaxis()->SetLabelFont(42);
   Graph_Graph01031->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01031->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01031->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01031->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01031->GetXaxis()->SetTitleFont(42);
   Graph_Graph01031->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01031->GetYaxis()->CenterTitle(true);
   Graph_Graph01031->GetYaxis()->SetNdivisions(504);
   Graph_Graph01031->GetYaxis()->SetLabelFont(42);
   Graph_Graph01031->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01031->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01031->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01031->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01031->GetYaxis()->SetTitleFont(42);
   Graph_Graph01031->GetZaxis()->SetLabelFont(42);
   Graph_Graph01031->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01031->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01031);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1032[33] = {
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
   Double_t Graph0_fy1032[33] = {
   0.08267373,
   1.7533,
   1.033422,
   1.494131,
   0.9511963,
   0.9765712,
   1.056655,
   0.9478467,
   0.9525468,
   0.8883216,
   0.9634495,
   0.9755476,
   0.9569297,
   0.9031358,
   0.9346909,
   0.9710712,
   0.9361607,
   0.9653948,
   0.9118926,
   0.9265856,
   1.010244,
   0.9269574,
   0.9983227,
   0.9427239,
   0.9184564,
   1.062324,
   0.7941032,
   0.9416949,
   0.9905357,
   0.7429165,
   0.817888,
   0.9230177,
   0.6784062};
   Double_t Graph0_fex1032[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1032[33] = {
   0.912743,
   1.975835,
   0.6023143,
   0.2807322,
   0.1254659,
   0.08858974,
   0.07072384,
   0.05195247,
   0.04268337,
   0.03775565,
   0.03560282,
   0.03454663,
   0.02360635,
   0.02370528,
   0.02481058,
   0.02723281,
   0.0303428,
   0.03539714,
   0.03825606,
   0.04313504,
   0.05127733,
   0.05651152,
   0.06992161,
   0.0815641,
   0.09508162,
   0.11139,
   0.1233754,
   0.1518393,
   0.194427,
   0.2088322,
   0.2651541,
   0.2627819,
   0.2661732};
   gre = new TGraphErrors(33,Graph0_fx1032,Graph0_fy1032,Graph0_fex1032,Graph0_fey1032);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#2f4c4a");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010311032 = new TH1F("Graph_Graph_Graph010311032","",100,0,3);
   Graph_Graph_Graph010311032->SetMinimum(0.84);
   Graph_Graph_Graph010311032->SetMaximum(1.16);
   Graph_Graph_Graph010311032->SetDirectory(0);
   Graph_Graph_Graph010311032->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010311032->SetLineColor(ci);
   Graph_Graph_Graph010311032->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010311032->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010311032->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010311032->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010311032->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010311032->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010311032->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010311032->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010311032->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010311032->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010311032->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010311032->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010311032->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010311032->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010311032->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010311032->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010311032->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010311032->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010311032->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010311032);
   
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
   
   Double_t Graph1_fx1033[33] = {
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
   Double_t Graph1_fy1033[33] = {
   17.86114,
   68.88522,
   38.44153,
   20.41058,
   0.874955,
   0.9387709,
   0.9767984,
   0.961832,
   0.9455071,
   0.9349391,
   0.9518664,
   0.9704983,
   0.9622595,
   0.9918289,
   0.9931758,
   0.9920766,
   1.000832,
   1.007365,
   0.9932137,
   0.9873823,
   0.9736492,
   0.9891097,
   1.02531,
   0.9586252,
   0.9717562,
   0.9282762,
   0.9686321,
   0.9230543,
   0.958059,
   0.9360464,
   1.071719,
   1.025944,
   0.8855579};
   Double_t Graph1_fex1033[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1033[33] = {
   8.30134,
   51.83115,
   10.47281,
   2.33293,
   0.0670345,
   0.04917954,
   0.03957419,
   0.02946225,
   0.02391227,
   0.02127007,
   0.01994662,
   0.01952024,
   0.01325639,
   0.01368986,
   0.01422247,
   0.01546757,
   0.01743472,
   0.02029834,
   0.02195522,
   0.02457009,
   0.02844145,
   0.03216228,
   0.04024035,
   0.04534103,
   0.05353795,
   0.05911342,
   0.07106006,
   0.08250951,
   0.106545,
   0.1192504,
   0.1637635,
   0.153842,
   0.1475405};
   gre = new TGraphErrors(33,Graph1_fx1033,Graph1_fy1033,Graph1_fex1033,Graph1_fey1033);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#4e6d2c");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11033 = new TH1F("Graph_Graph11033","",100,0,3.1325);
   Graph_Graph11033->SetMinimum(0.84);
   Graph_Graph11033->SetMaximum(1.16);
   Graph_Graph11033->SetDirectory(0);
   Graph_Graph11033->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11033->SetLineColor(ci);
   Graph_Graph11033->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11033->GetXaxis()->SetLabelFont(42);
   Graph_Graph11033->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11033->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11033->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11033->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11033->GetXaxis()->SetTitleFont(42);
   Graph_Graph11033->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11033->GetYaxis()->CenterTitle(true);
   Graph_Graph11033->GetYaxis()->SetNdivisions(504);
   Graph_Graph11033->GetYaxis()->SetLabelFont(42);
   Graph_Graph11033->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11033->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11033->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11033->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11033->GetYaxis()->SetTitleFont(42);
   Graph_Graph11033->GetZaxis()->SetLabelFont(42);
   Graph_Graph11033->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11033->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11033);
   
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
   
   Double_t Graph2_fx1034[33] = {
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
   Double_t Graph2_fy1034[33] = {
   1.447791,
   6.126197,
   1.521866,
   1.474097,
   0.7383457,
   0.9282926,
   1.186231,
   0.8627219,
   0.8549883,
   0.8567424,
   1.010834,
   0.9885225,
   0.9309503,
   0.8736759,
   0.92616,
   0.8893691,
   1.09497,
   0.9572388,
   0.8446029,
   0.8748647,
   1.063567,
   1.078537,
   0.8645704,
   0.920201,
   0.8808069,
   1.001546,
   0.6269888,
   0.6958728,
   0.6257356,
   0.9373076,
   0.9662814,
   0.4822352,
   2.15254};
   Double_t Graph2_fex1034[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1034[33] = {
   2.167372,
   5.713883,
   1.301587,
   0.5486305,
   0.2642885,
   0.1880332,
   0.1497365,
   0.1109077,
   0.09084221,
   0.08112595,
   0.07552612,
   0.07286876,
   0.04937517,
   0.04954733,
   0.05120434,
   0.05532188,
   0.06227622,
   0.07141227,
   0.07729629,
   0.08694377,
   0.1021992,
   0.1136223,
   0.137532,
   0.16193,
   0.1877465,
   0.2150791,
   0.2467819,
   0.2945798,
   0.3692459,
   0.41443,
   0.5289597,
   0.5037263,
   0.5941321};
   gre = new TGraphErrors(33,Graph2_fx1034,Graph2_fy1034,Graph2_fex1034,Graph2_fey1034);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a39e35");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a39e35");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21034 = new TH1F("Graph_Graph21034","",100,0,3.1325);
   Graph_Graph21034->SetMinimum(0.84);
   Graph_Graph21034->SetMaximum(1.16);
   Graph_Graph21034->SetDirectory(0);
   Graph_Graph21034->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21034->SetLineColor(ci);
   Graph_Graph21034->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21034->GetXaxis()->SetLabelFont(42);
   Graph_Graph21034->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21034->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21034->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21034->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21034->GetXaxis()->SetTitleFont(42);
   Graph_Graph21034->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21034->GetYaxis()->CenterTitle(true);
   Graph_Graph21034->GetYaxis()->SetNdivisions(504);
   Graph_Graph21034->GetYaxis()->SetLabelFont(42);
   Graph_Graph21034->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21034->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21034->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21034->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21034->GetYaxis()->SetTitleFont(42);
   Graph_Graph21034->GetZaxis()->SetLabelFont(42);
   Graph_Graph21034->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21034->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21034);
   
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
   
   Double_t Graph3_fx1035[33] = {
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
   Double_t Graph3_fy1035[33] = {
   1.218327,
   0.7698025,
   0.790473,
   1.05655,
   1.090547,
   1.08048,
   1.06392,
   1.031009,
   1.010727,
   1.026482,
   1.011266,
   1.015902,
   1.009442,
   1.001331,
   0.9979829,
   1.003226,
   1.012469,
   1.005171,
   1.000977,
   0.9958578,
   1.021465,
   1.010954,
   1.006707,
   1.022127,
   0.9984095,
   1.032621,
   1.060708,
   0.9553311,
   0.9763765,
   0.8993476,
   1.126744,
   0.8716065,
   1.017371};
   Double_t Graph3_fex1035[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1035[33] = {
   0.743571,
   0.9693206,
   0.3531828,
   0.1679419,
   0.08626485,
   0.06024236,
   0.0468551,
   0.03463458,
   0.0281325,
   0.02542082,
   0.02344805,
   0.02276817,
   0.01556145,
   0.0157726,
   0.01640907,
   0.01795816,
   0.02026654,
   0.0234594,
   0.0255997,
   0.02873617,
   0.03401698,
   0.03792404,
   0.04631433,
   0.05496501,
   0.0636107,
   0.07362135,
   0.08719593,
   0.0994886,
   0.1269986,
   0.1389388,
   0.1949262,
   0.1672443,
   0.1890715};
   gre = new TGraphErrors(33,Graph3_fx1035,Graph3_fy1035,Graph3_fex1035,Graph3_fey1035);
   gre->SetName("Graph3");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#a85d33");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#a85d33");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31035 = new TH1F("Graph_Graph31035","",100,0,3.1325);
   Graph_Graph31035->SetMinimum(0.84);
   Graph_Graph31035->SetMaximum(1.16);
   Graph_Graph31035->SetDirectory(0);
   Graph_Graph31035->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31035->SetLineColor(ci);
   Graph_Graph31035->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31035->GetXaxis()->SetLabelFont(42);
   Graph_Graph31035->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph31035->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph31035->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph31035->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31035->GetXaxis()->SetTitleFont(42);
   Graph_Graph31035->GetYaxis()->SetTitle("Ratio");
   Graph_Graph31035->GetYaxis()->CenterTitle(true);
   Graph_Graph31035->GetYaxis()->SetNdivisions(504);
   Graph_Graph31035->GetYaxis()->SetLabelFont(42);
   Graph_Graph31035->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph31035->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph31035->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph31035->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph31035->GetYaxis()->SetTitleFont(42);
   Graph_Graph31035->GetZaxis()->SetLabelFont(42);
   Graph_Graph31035->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31035->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31035);
   
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
   
   Double_t Graph4_fx1036[33] = {
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
   Double_t Graph4_fy1036[33] = {
   1.00837,
   1.01099,
   1.009927,
   1.009913,
   1.009482,
   1.009381,
   1.009591,
   1.009524,
   1.009478,
   1.009435,
   1.009312,
   1.009296,
   1.009286,
   1.009099,
   1.009058,
   1.009038,
   1.00901,
   1.009051,
   1.008977,
   1.009116,
   1.009267,
   1.009319,
   1.009529,
   1.009955,
   1.010276,
   1.010675,
   1.009986,
   1.011519,
   1.010341,
   1.010812,
   1.010056,
   1.010595,
   1.012764};
   Double_t Graph4_fex1036[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph4_fey1036[33] = {
   0.6604674,
   1.07005,
   0.3863842,
   0.1615928,
   0.08162372,
   0.05729726,
   0.04493736,
   0.03376493,
   0.02770516,
   0.02484418,
   0.02308445,
   0.02236981,
   0.01533662,
   0.01560752,
   0.01626127,
   0.01775036,
   0.01994839,
   0.02317594,
   0.02534326,
   0.02851894,
   0.0333599,
   0.03740017,
   0.04577324,
   0.05394508,
   0.06320358,
   0.07192005,
   0.08423459,
   0.1010414,
   0.1273292,
   0.1451899,
   0.1825598,
   0.1764971,
   0.1865837};
   gre = new TGraphErrors(33,Graph4_fx1036,Graph4_fy1036,Graph4_fex1036,Graph4_fey1036);
   gre->SetName("Graph4");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph41036 = new TH1F("Graph_Graph41036","",100,0,3.1325);
   Graph_Graph41036->SetMinimum(0.84);
   Graph_Graph41036->SetMaximum(1.16);
   Graph_Graph41036->SetDirectory(0);
   Graph_Graph41036->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41036->SetLineColor(ci);
   Graph_Graph41036->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph41036->GetXaxis()->SetLabelFont(42);
   Graph_Graph41036->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph41036->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph41036->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph41036->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41036->GetXaxis()->SetTitleFont(42);
   Graph_Graph41036->GetYaxis()->SetTitle("Ratio");
   Graph_Graph41036->GetYaxis()->CenterTitle(true);
   Graph_Graph41036->GetYaxis()->SetNdivisions(504);
   Graph_Graph41036->GetYaxis()->SetLabelFont(42);
   Graph_Graph41036->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph41036->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph41036->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph41036->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph41036->GetYaxis()->SetTitleFont(42);
   Graph_Graph41036->GetZaxis()->SetLabelFont(42);
   Graph_Graph41036->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41036->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41036);
   
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
   10-40%, K+->cd();
   10-40%, K+->Modified();
   10-40%, K+->cd();
   10-40%, K+->SetSelected(10-40%, K+);
}
