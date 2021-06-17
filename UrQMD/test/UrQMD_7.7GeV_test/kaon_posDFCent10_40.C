void kaon_posDFCent10_40()
{
//=========Macro generated from canvas: c1_n4/Canvas
//=========  (Fri Apr 23 20:00:15 2021) by ROOT version 6.22/08
   TCanvas *c1_n4 = new TCanvas("c1_n4", "Canvas",0,0,550,550);
   c1_n4->Range(0,0,1,1);
   c1_n4->SetFillColor(0);
   c1_n4->SetBorderMode(0);
   c1_n4->SetBorderSize(2);
   c1_n4->SetTickx(1);
   c1_n4->SetTicky(1);
   c1_n4->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1017[33] = {
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
   Double_t Graph0_fy1017[33] = {
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
   Double_t Graph0_fex1017[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1017[33] = {
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
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1017,Graph0_fy1017,Graph0_fex1017,Graph0_fey1017);
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
   
   TH1F *Graph_Graph01017 = new TH1F("Graph_Graph01017","",100,0,3);
   Graph_Graph01017->SetMinimum(-0.01);
   Graph_Graph01017->SetMaximum(0.2);
   Graph_Graph01017->SetDirectory(0);
   Graph_Graph01017->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01017->SetLineColor(ci);
   Graph_Graph01017->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01017->GetXaxis()->SetLabelFont(42);
   Graph_Graph01017->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01017->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01017->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01017->GetXaxis()->SetTitleFont(42);
   Graph_Graph01017->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01017->GetYaxis()->SetLabelFont(42);
   Graph_Graph01017->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01017->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01017->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01017->GetYaxis()->SetTitleFont(42);
   Graph_Graph01017->GetZaxis()->SetLabelFont(42);
   Graph_Graph01017->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01017);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1018[33] = {
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
   Double_t Graph1_fy1018[33] = {
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
   Double_t Graph1_fex1018[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1018[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1018,Graph1_fy1018,Graph1_fex1018,Graph1_fey1018);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11018 = new TH1F("Graph_Graph11018","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11018->SetMinimum(-0.0157845);
   Graph_Graph11018->SetMaximum(0.107728);
   Graph_Graph11018->SetDirectory(0);
   Graph_Graph11018->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11018->SetLineColor(ci);
   Graph_Graph11018->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11018->GetXaxis()->SetLabelFont(42);
   Graph_Graph11018->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11018->GetXaxis()->SetTitleFont(42);
   Graph_Graph11018->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11018->GetYaxis()->SetLabelFont(42);
   Graph_Graph11018->GetYaxis()->SetTitleFont(42);
   Graph_Graph11018->GetZaxis()->SetLabelFont(42);
   Graph_Graph11018->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11018->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11018);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1019[33] = {
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
   Double_t Graph2_fy1019[33] = {
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
   Double_t Graph2_fex1019[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1019[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1019,Graph2_fy1019,Graph2_fex1019,Graph2_fey1019);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21019 = new TH1F("Graph_Graph21019","v_{2}{2}",100,0,3.1325);
   Graph_Graph21019->SetMinimum(-0.1429135);
   Graph_Graph21019->SetMaximum(0.1248998);
   Graph_Graph21019->SetDirectory(0);
   Graph_Graph21019->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21019->SetLineColor(ci);
   Graph_Graph21019->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21019->GetXaxis()->SetLabelFont(42);
   Graph_Graph21019->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21019->GetXaxis()->SetTitleFont(42);
   Graph_Graph21019->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21019->GetYaxis()->SetLabelFont(42);
   Graph_Graph21019->GetYaxis()->SetTitleFont(42);
   Graph_Graph21019->GetZaxis()->SetLabelFont(42);
   Graph_Graph21019->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21019);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1020[33] = {
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
   Double_t Graph3_fy1020[33] = {
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
   Double_t Graph3_fex1020[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1020[33] = {
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
   gre = new TGraphErrors(33,Graph3_fx1020,Graph3_fy1020,Graph3_fex1020,Graph3_fey1020);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31020 = new TH1F("Graph_Graph31020","v_{2}{4}",100,0,3.1325);
   Graph_Graph31020->SetMinimum(-0.05361819);
   Graph_Graph31020->SetMaximum(0.3109985);
   Graph_Graph31020->SetDirectory(0);
   Graph_Graph31020->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31020->SetLineColor(ci);
   Graph_Graph31020->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31020->GetXaxis()->SetLabelFont(42);
   Graph_Graph31020->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31020->GetXaxis()->SetTitleFont(42);
   Graph_Graph31020->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31020->GetYaxis()->SetLabelFont(42);
   Graph_Graph31020->GetYaxis()->SetTitleFont(42);
   Graph_Graph31020->GetZaxis()->SetLabelFont(42);
   Graph_Graph31020->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31020->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31020);
   
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
   pt_LaTex = pt->AddText("10-40%, K+");
   pt->Draw();
   padUp->Modified();
   c1_n4->cd();
  
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
   
   Double_t Graph0_fx1021[33] = {
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
   Double_t Graph0_fy1021[33] = {
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
   Double_t Graph0_fex1021[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1021[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1021,Graph0_fy1021,Graph0_fex1021,Graph0_fey1021);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01021 = new TH1F("Graph_Graph01021","",100,0,3);
   Graph_Graph01021->SetMinimum(0.84);
   Graph_Graph01021->SetMaximum(1.16);
   Graph_Graph01021->SetDirectory(0);
   Graph_Graph01021->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01021->SetLineColor(ci);
   Graph_Graph01021->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01021->GetXaxis()->SetLabelFont(42);
   Graph_Graph01021->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01021->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01021->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01021->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01021->GetXaxis()->SetTitleFont(42);
   Graph_Graph01021->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01021->GetYaxis()->CenterTitle(true);
   Graph_Graph01021->GetYaxis()->SetNdivisions(504);
   Graph_Graph01021->GetYaxis()->SetLabelFont(42);
   Graph_Graph01021->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01021->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01021->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01021->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01021->GetYaxis()->SetTitleFont(42);
   Graph_Graph01021->GetZaxis()->SetLabelFont(42);
   Graph_Graph01021->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01021->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01021);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1022[33] = {
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
   Double_t Graph0_fy1022[33] = {
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
   Double_t Graph0_fex1022[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1022[33] = {
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
   gre = new TGraphErrors(33,Graph0_fx1022,Graph0_fy1022,Graph0_fex1022,Graph0_fey1022);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010211022 = new TH1F("Graph_Graph_Graph010211022","",100,0,3);
   Graph_Graph_Graph010211022->SetMinimum(0.84);
   Graph_Graph_Graph010211022->SetMaximum(1.16);
   Graph_Graph_Graph010211022->SetDirectory(0);
   Graph_Graph_Graph010211022->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010211022->SetLineColor(ci);
   Graph_Graph_Graph010211022->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010211022->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010211022->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010211022->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010211022->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010211022->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010211022->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010211022->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010211022->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010211022->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010211022->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010211022->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010211022->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010211022->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010211022->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010211022->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010211022->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010211022->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010211022->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010211022);
   
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
   
   Double_t Graph1_fx1023[33] = {
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
   Double_t Graph1_fy1023[33] = {
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
   Double_t Graph1_fex1023[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1023[33] = {
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
   gre = new TGraphErrors(33,Graph1_fx1023,Graph1_fy1023,Graph1_fex1023,Graph1_fey1023);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11023 = new TH1F("Graph_Graph11023","",100,0,3.1325);
   Graph_Graph11023->SetMinimum(0.84);
   Graph_Graph11023->SetMaximum(1.16);
   Graph_Graph11023->SetDirectory(0);
   Graph_Graph11023->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11023->SetLineColor(ci);
   Graph_Graph11023->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11023->GetXaxis()->SetLabelFont(42);
   Graph_Graph11023->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11023->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11023->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11023->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11023->GetXaxis()->SetTitleFont(42);
   Graph_Graph11023->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11023->GetYaxis()->CenterTitle(true);
   Graph_Graph11023->GetYaxis()->SetNdivisions(504);
   Graph_Graph11023->GetYaxis()->SetLabelFont(42);
   Graph_Graph11023->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11023->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11023->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11023->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11023->GetYaxis()->SetTitleFont(42);
   Graph_Graph11023->GetZaxis()->SetLabelFont(42);
   Graph_Graph11023->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11023->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11023);
   
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
   
   Double_t Graph2_fx1024[33] = {
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
   Double_t Graph2_fy1024[33] = {
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
   Double_t Graph2_fex1024[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1024[33] = {
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
   gre = new TGraphErrors(33,Graph2_fx1024,Graph2_fy1024,Graph2_fex1024,Graph2_fey1024);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21024 = new TH1F("Graph_Graph21024","",100,0,3.1325);
   Graph_Graph21024->SetMinimum(0.84);
   Graph_Graph21024->SetMaximum(1.16);
   Graph_Graph21024->SetDirectory(0);
   Graph_Graph21024->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21024->SetLineColor(ci);
   Graph_Graph21024->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21024->GetXaxis()->SetLabelFont(42);
   Graph_Graph21024->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21024->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21024->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21024->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21024->GetXaxis()->SetTitleFont(42);
   Graph_Graph21024->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21024->GetYaxis()->CenterTitle(true);
   Graph_Graph21024->GetYaxis()->SetNdivisions(504);
   Graph_Graph21024->GetYaxis()->SetLabelFont(42);
   Graph_Graph21024->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21024->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21024->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21024->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21024->GetYaxis()->SetTitleFont(42);
   Graph_Graph21024->GetZaxis()->SetLabelFont(42);
   Graph_Graph21024->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21024->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21024);
   
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
   c1_n4->cd();
   c1_n4->Modified();
   c1_n4->cd();
   c1_n4->SetSelected(c1_n4);
}
