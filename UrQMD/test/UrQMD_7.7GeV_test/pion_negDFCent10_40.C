void pion_negDFCent10_40()
{
//=========Macro generated from canvas: c1_n7/Canvas
//=========  (Fri Apr 23 20:00:15 2021) by ROOT version 6.22/08
   TCanvas *c1_n7 = new TCanvas("c1_n7", "Canvas",0,0,550,550);
   c1_n7->Range(0,0,1,1);
   c1_n7->SetFillColor(0);
   c1_n7->SetBorderMode(0);
   c1_n7->SetBorderSize(2);
   c1_n7->SetTickx(1);
   c1_n7->SetTicky(1);
   c1_n7->SetFrameBorderMode(0);
  
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
   
   Double_t Graph0_fx1041[33] = {
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
   Double_t Graph0_fy1041[33] = {
   0.001605126,
   0.006246323,
   0.01141409,
   0.01669143,
   0.0223473,
   0.02831777,
   0.0332092,
   0.03737335,
   0.0406253,
   0.04360794,
   0.04531802,
   0.04780038,
   0.05020598,
   0.05342902,
   0.05596807,
   0.05801727,
   0.05945153,
   0.06164463,
   0.0631715,
   0.06479584,
   0.06735025,
   0.06863251,
   0.07100332,
   0.07432742,
   0.07582988,
   0.07685978,
   0.08222517,
   0.07993261,
   0.09240046,
   0.100948,
   0.09031551,
   0.09962506,
   0.1121944};
   Double_t Graph0_fex1041[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1041[33] = {
   0.0003774767,
   0.000181454,
   0.0001431196,
   0.0001331106,
   0.0001307601,
   0.0001361955,
   0.0001451289,
   0.0001565274,
   0.0001699423,
   0.0001850933,
   0.0002021695,
   0.0002211767,
   0.0001774944,
   0.0002147813,
   0.0002606452,
   0.0003166182,
   0.0003846087,
   0.0004674549,
   0.0005683965,
   0.0006923197,
   0.0008441317,
   0.001033479,
   0.00126678,
   0.001555462,
   0.001917679,
   0.002360582,
   0.002917929,
   0.003611309,
   0.004459908,
   0.005513136,
   0.006796596,
   0.006594335,
   0.008967193};
   TGraphErrors *gre = new TGraphErrors(33,Graph0_fx1041,Graph0_fy1041,Graph0_fex1041,Graph0_fey1041);
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
   
   TH1F *Graph_Graph01041 = new TH1F("Graph_Graph01041","",100,0,3);
   Graph_Graph01041->SetMinimum(-0.01);
   Graph_Graph01041->SetMaximum(0.2);
   Graph_Graph01041->SetDirectory(0);
   Graph_Graph01041->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01041->SetLineColor(ci);
   Graph_Graph01041->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01041->GetXaxis()->SetLabelFont(42);
   Graph_Graph01041->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01041->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph01041->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01041->GetXaxis()->SetTitleFont(42);
   Graph_Graph01041->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph01041->GetYaxis()->SetLabelFont(42);
   Graph_Graph01041->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01041->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph01041->GetYaxis()->SetTitleOffset(1.08);
   Graph_Graph01041->GetYaxis()->SetTitleFont(42);
   Graph_Graph01041->GetZaxis()->SetLabelFont(42);
   Graph_Graph01041->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01041->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01041);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph1_fx1042[33] = {
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
   Double_t Graph1_fy1042[33] = {
   0.002016988,
   0.006611221,
   0.01114858,
   0.01689924,
   0.02248548,
   0.02817731,
   0.03281584,
   0.03665995,
   0.03943335,
   0.04206695,
   0.04418903,
   0.04612499,
   0.04813971,
   0.05114857,
   0.05370817,
   0.0556182,
   0.05764602,
   0.05939361,
   0.06207882,
   0.06174039,
   0.0635615,
   0.0645615,
   0.07160317,
   0.07021522,
   0.07817875,
   0.07992929,
   0.08461384,
   0.07721863,
   0.08173648,
   0.07016691,
   0.06917249,
   0.07880168,
   0.05448237};
   Double_t Graph1_fex1042[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1042[33] = {
   0.000726322,
   0.0003433643,
   0.0002682786,
   0.0002493109,
   0.0002512965,
   0.0002640208,
   0.0002827682,
   0.0003058615,
   0.0003322783,
   0.0003619438,
   0.0003950616,
   0.0004319658,
   0.0003543377,
   0.0004257758,
   0.0005136594,
   0.0006207878,
   0.0007520037,
   0.0009111973,
   0.001106388,
   0.001345539,
   0.00163955,
   0.002006539,
   0.002458291,
   0.003022466,
   0.003719952,
   0.00458205,
   0.005648767,
   0.006989276,
   0.008619679,
   0.01063342,
   0.01313925,
   0.01269706,
   0.01723791};
   gre = new TGraphErrors(33,Graph1_fx1042,Graph1_fy1042,Graph1_fex1042,Graph1_fey1042);
   gre->SetName("Graph1");
   gre->SetTitle("v_{2}{2,#eta-gap,FHCal}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11042 = new TH1F("Graph_Graph11042","v_{2}{2,#eta-gap,FHCal}",100,0,3.1325);
   Graph_Graph11042->SetMinimum(0.001161599);
   Graph_Graph11042->SetMaximum(0.1005195);
   Graph_Graph11042->SetDirectory(0);
   Graph_Graph11042->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11042->SetLineColor(ci);
   Graph_Graph11042->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11042->GetXaxis()->SetLabelFont(42);
   Graph_Graph11042->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11042->GetXaxis()->SetTitleFont(42);
   Graph_Graph11042->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph11042->GetYaxis()->SetLabelFont(42);
   Graph_Graph11042->GetYaxis()->SetTitleFont(42);
   Graph_Graph11042->GetZaxis()->SetLabelFont(42);
   Graph_Graph11042->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11042->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11042);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph2_fx1043[33] = {
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
   Double_t Graph2_fy1043[33] = {
   -0.1101204,
   -0.104757,
   -0.0996992,
   -0.09428226,
   0.02297542,
   0.02878694,
   0.03393836,
   0.03808169,
   0.04135268,
   0.04412973,
   0.04617668,
   0.04837243,
   0.05082745,
   0.05400908,
   0.05638406,
   0.05829585,
   0.05997126,
   0.06116197,
   0.06187576,
   0.06318609,
   0.06546269,
   0.06502013,
   0.06773547,
   0.06977418,
   0.07190693,
   0.07248198,
   0.07796767,
   0.07567876,
   0.08750501,
   0.09039635,
   0.08075164,
   0.08898709,
   0.101448};
   Double_t Graph2_fex1043[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1043[33] = {
   0.0003006232,
   0.0001514578,
   0.0001202974,
   0.0001114818,
   9.88992e-05,
   0.0001034585,
   0.000110979,
   0.0001205393,
   0.0001316498,
   0.0001440024,
   0.0001576132,
   0.0001723581,
   0.0001378819,
   0.000165449,
   0.000198858,
   0.0002394678,
   0.0002887114,
   0.000348984,
   0.0004224128,
   0.0005127137,
   0.0006241689,
   0.0007620009,
   0.0009326118,
   0.001144305,
   0.00140862,
   0.001732692,
   0.002136926,
   0.002635404,
   0.003256522,
   0.004033855,
   0.004955183,
   0.004808908,
   0.006505808};
   gre = new TGraphErrors(33,Graph2_fx1043,Graph2_fy1043,Graph2_fex1043,Graph2_fey1043);
   gre->SetName("Graph2");
   gre->SetTitle("v_{2}{2}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21043 = new TH1F("Graph_Graph21043","v_{2}{2}",100,0,3.1325);
   Graph_Graph21043->SetMinimum(-0.1322585);
   Graph_Graph21043->SetMaximum(0.1297913);
   Graph_Graph21043->SetDirectory(0);
   Graph_Graph21043->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21043->SetLineColor(ci);
   Graph_Graph21043->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21043->GetXaxis()->SetLabelFont(42);
   Graph_Graph21043->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21043->GetXaxis()->SetTitleFont(42);
   Graph_Graph21043->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph21043->GetYaxis()->SetLabelFont(42);
   Graph_Graph21043->GetYaxis()->SetTitleFont(42);
   Graph_Graph21043->GetZaxis()->SetLabelFont(42);
   Graph_Graph21043->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21043->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21043);
   
   gre->Draw("p plc pmc");
   
   Double_t Graph3_fx1044[33] = {
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
   Double_t Graph3_fy1044[33] = {
   0.005056514,
   0.00697532,
   0.01095555,
   0.01596824,
   0.02215582,
   0.0272837,
   0.03059563,
   0.0349295,
   0.03812136,
   0.04122359,
   0.04237798,
   0.0454228,
   0.04828514,
   0.04929928,
   0.05382018,
   0.05597099,
   0.05382917,
   0.05505748,
   0.05794678,
   0.06138094,
   0.06612618,
   0.06292648,
   0.07340817,
   0.07678724,
   0.08020492,
   0.08697904,
   0.07582088,
   0.1151278,
   0.09441158,
   0.08638386,
   0.0574726,
   0.06525044,
   0.06690835};
   Double_t Graph3_fex1044[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph3_fey1044[33] = {
   0.001847759,
   0.0009157928,
   0.0007085204,
   0.0006484487,
   0.0006347389,
   0.0006667481,
   0.0007152064,
   0.0007762366,
   0.0008460454,
   0.000920847,
   0.001001404,
   0.001088922,
   0.0008751738,
   0.001030626,
   0.001222117,
   0.001453999,
   0.001730473,
   0.002075729,
   0.002499319,
   0.003018325,
   0.003653693,
   0.004453079,
   0.00541986,
   0.006636887,
   0.008130927,
   0.009995064,
   0.01232502,
   0.01505227,
   0.01847947,
   0.02326073,
   0.02804637,
   0.02835269,
   0.03760296};
   gre = new TGraphErrors(33,Graph3_fx1044,Graph3_fy1044,Graph3_fex1044,Graph3_fey1044);
   gre->SetName("Graph3");
   gre->SetTitle("v_{2}{4}");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph31044 = new TH1F("Graph_Graph31044","v_{2}{4}",100,0,3.1325);
   Graph_Graph31044->SetMinimum(0.00288788);
   Graph_Graph31044->SetMaximum(0.1428773);
   Graph_Graph31044->SetDirectory(0);
   Graph_Graph31044->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31044->SetLineColor(ci);
   Graph_Graph31044->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph31044->GetXaxis()->SetLabelFont(42);
   Graph_Graph31044->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31044->GetXaxis()->SetTitleFont(42);
   Graph_Graph31044->GetYaxis()->SetTitle("v_{2}");
   Graph_Graph31044->GetYaxis()->SetLabelFont(42);
   Graph_Graph31044->GetYaxis()->SetTitleFont(42);
   Graph_Graph31044->GetZaxis()->SetLabelFont(42);
   Graph_Graph31044->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31044->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31044);
   
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
   pt_LaTex = pt->AddText("10-40%, #pi-");
   pt->Draw();
   padUp->Modified();
   c1_n7->cd();
  
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
   
   Double_t Graph0_fx1045[33] = {
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
   Double_t Graph0_fy1045[33] = {
   1.256592,
   1.058418,
   0.976738,
   1.01245,
   1.006183,
   0.9950401,
   0.988155,
   0.9809115,
   0.9706598,
   0.9646627,
   0.9750873,
   0.9649503,
   0.9588441,
   0.9573181,
   0.9596216,
   0.9586492,
   0.9696306,
   0.9634841,
   0.982703,
   0.952845,
   0.9437455,
   0.9406839,
   1.008448,
   0.9446745,
   1.030976,
   1.039937,
   1.02905,
   0.9660467,
   0.8845896,
   0.6950795,
   0.7658982,
   0.7909825,
   0.4856067};
   Double_t Graph0_fex1045[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1045[33] = {
   0.5404489,
   0.06298517,
   0.02650356,
   0.01697906,
   0.01269304,
   0.01048001,
   0.00954722,
   0.009157226,
   0.009131523,
   0.00925495,
   0.009742581,
   0.01007971,
   0.007829544,
   0.008849567,
   0.01020796,
   0.01191055,
   0.01411899,
   0.01648852,
   0.01961946,
   0.02312722,
   0.02706518,
   0.03248676,
   0.03901799,
   0.0452151,
   0.05555469,
   0.06763252,
   0.07780155,
   0.09772722,
   0.1025929,
   0.1119669,
   0.1564829,
   0.1377835,
   0.1584697};
   gre = new TGraphErrors(33,Graph0_fx1045,Graph0_fy1045,Graph0_fex1045,Graph0_fey1045);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph01045 = new TH1F("Graph_Graph01045","",100,0,3);
   Graph_Graph01045->SetMinimum(0.84);
   Graph_Graph01045->SetMaximum(1.16);
   Graph_Graph01045->SetDirectory(0);
   Graph_Graph01045->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01045->SetLineColor(ci);
   Graph_Graph01045->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph01045->GetXaxis()->SetLabelFont(42);
   Graph_Graph01045->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph01045->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph01045->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph01045->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01045->GetXaxis()->SetTitleFont(42);
   Graph_Graph01045->GetYaxis()->SetTitle("Ratio");
   Graph_Graph01045->GetYaxis()->CenterTitle(true);
   Graph_Graph01045->GetYaxis()->SetNdivisions(504);
   Graph_Graph01045->GetYaxis()->SetLabelFont(42);
   Graph_Graph01045->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph01045->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph01045->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph01045->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph01045->GetYaxis()->SetTitleFont(42);
   Graph_Graph01045->GetZaxis()->SetLabelFont(42);
   Graph_Graph01045->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01045->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01045);
   
   gre->Draw("ap plc pmc");
   
   Double_t Graph0_fx1046[33] = {
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
   Double_t Graph0_fy1046[33] = {
   1.256592,
   1.058418,
   0.976738,
   1.01245,
   1.006183,
   0.9950401,
   0.988155,
   0.9809115,
   0.9706598,
   0.9646627,
   0.9750873,
   0.9649503,
   0.9588441,
   0.9573181,
   0.9596216,
   0.9586492,
   0.9696306,
   0.9634841,
   0.982703,
   0.952845,
   0.9437455,
   0.9406839,
   1.008448,
   0.9446745,
   1.030976,
   1.039937,
   1.02905,
   0.9660467,
   0.8845896,
   0.6950795,
   0.7658982,
   0.7909825,
   0.4856067};
   Double_t Graph0_fex1046[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph0_fey1046[33] = {
   0.5404489,
   0.06298517,
   0.02650356,
   0.01697906,
   0.01269304,
   0.01048001,
   0.00954722,
   0.009157226,
   0.009131523,
   0.00925495,
   0.009742581,
   0.01007971,
   0.007829544,
   0.008849567,
   0.01020796,
   0.01191055,
   0.01411899,
   0.01648852,
   0.01961946,
   0.02312722,
   0.02706518,
   0.03248676,
   0.03901799,
   0.0452151,
   0.05555469,
   0.06763252,
   0.07780155,
   0.09772722,
   0.1025929,
   0.1119669,
   0.1564829,
   0.1377835,
   0.1584697};
   gre = new TGraphErrors(33,Graph0_fx1046,Graph0_fy1046,Graph0_fex1046,Graph0_fey1046);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3d6030");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3d6030");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph_Graph010451046 = new TH1F("Graph_Graph_Graph010451046","",100,0,3);
   Graph_Graph_Graph010451046->SetMinimum(0.84);
   Graph_Graph_Graph010451046->SetMaximum(1.16);
   Graph_Graph_Graph010451046->SetDirectory(0);
   Graph_Graph_Graph010451046->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010451046->SetLineColor(ci);
   Graph_Graph_Graph010451046->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph_Graph010451046->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010451046->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010451046->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010451046->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph_Graph010451046->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010451046->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010451046->GetYaxis()->SetTitle("Ratio");
   Graph_Graph_Graph010451046->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph010451046->GetYaxis()->SetNdivisions(504);
   Graph_Graph_Graph010451046->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010451046->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph_Graph010451046->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph_Graph010451046->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph_Graph010451046->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph010451046->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010451046->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010451046->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010451046->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010451046);
   
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
   
   Double_t Graph1_fx1047[33] = {
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
   Double_t Graph1_fy1047[33] = {
   68.60545,
   16.77098,
   8.734746,
   5.648543,
   1.028107,
   1.016568,
   1.021956,
   1.018953,
   1.017905,
   1.011965,
   1.018947,
   1.011968,
   1.012378,
   1.010857,
   1.007433,
   1.004802,
   1.008742,
   0.9921703,
   0.9794885,
   0.9751567,
   0.9719739,
   0.9473663,
   0.9539761,
   0.9387407,
   0.9482665,
   0.9430418,
   0.9482215,
   0.946782,
   0.9470192,
   0.8954741,
   0.8941059,
   0.8932199,
   0.904216};
   Double_t Graph1_fex1047[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph1_fey1047[33] = {
   16.135,
   0.4877956,
   0.1100296,
   0.04553838,
   0.00746824,
   0.006103482,
   0.005577965,
   0.005349271,
   0.005350934,
   0.005417927,
   0.005723549,
   0.005909925,
   0.004511335,
   0.005108983,
   0.005885219,
   0.006863338,
   0.008134477,
   0.009415695,
   0.01106272,
   0.01308324,
   0.01530662,
   0.01807693,
   0.0214989,
   0.02495904,
   0.03033405,
   0.03670279,
   0.04251715,
   0.05400693,
   0.05771921,
   0.06315445,
   0.08681857,
   0.07632561,
   0.09265753};
   gre = new TGraphErrors(33,Graph1_fx1047,Graph1_fy1047,Graph1_fex1047,Graph1_fey1047);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ae9437");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ae9437");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph11047 = new TH1F("Graph_Graph11047","",100,0,3.1325);
   Graph_Graph11047->SetMinimum(0.84);
   Graph_Graph11047->SetMaximum(1.16);
   Graph_Graph11047->SetDirectory(0);
   Graph_Graph11047->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11047->SetLineColor(ci);
   Graph_Graph11047->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph11047->GetXaxis()->SetLabelFont(42);
   Graph_Graph11047->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph11047->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph11047->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph11047->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11047->GetXaxis()->SetTitleFont(42);
   Graph_Graph11047->GetYaxis()->SetTitle("Ratio");
   Graph_Graph11047->GetYaxis()->CenterTitle(true);
   Graph_Graph11047->GetYaxis()->SetNdivisions(504);
   Graph_Graph11047->GetYaxis()->SetLabelFont(42);
   Graph_Graph11047->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph11047->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph11047->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph11047->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph11047->GetYaxis()->SetTitleFont(42);
   Graph_Graph11047->GetZaxis()->SetLabelFont(42);
   Graph_Graph11047->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11047->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11047);
   
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
   
   Double_t Graph2_fx1048[33] = {
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
   Double_t Graph2_fy1048[33] = {
   3.150228,
   1.116708,
   0.9598267,
   0.9566731,
   0.9914316,
   0.9634835,
   0.9212998,
   0.9346099,
   0.938365,
   0.945323,
   0.9351243,
   0.9502603,
   0.9617408,
   0.9227062,
   0.961623,
   0.9647299,
   0.9054295,
   0.8931432,
   0.9172931,
   0.9472977,
   0.9818253,
   0.9168611,
   1.03387,
   1.033094,
   1.057696,
   1.131659,
   0.9221128,
   1.440311,
   1.021765,
   0.8557259,
   0.6363536,
   0.6549601,
   0.5963607};
   Double_t Graph2_fex1048[33] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   Double_t Graph2_fey1048[33] = {
   1.368946,
   0.1501591,
   0.06323012,
   0.03959123,
   0.02898975,
   0.02399689,
   0.02190951,
   0.02113543,
   0.02119229,
   0.02149432,
   0.0224876,
   0.02320107,
   0.01776016,
   0.01964302,
   0.02229046,
   0.02560853,
   0.02969082,
   0.03434688,
   0.04041575,
   0.04766902,
   0.05562732,
   0.06633558,
   0.07852949,
   0.09187262,
   0.1105118,
   0.1346074,
   0.1534238,
   0.1992382,
   0.2059843,
   0.2351144,
   0.3142084,
   0.287877,
   0.3385312};
   gre = new TGraphErrors(33,Graph2_fx1048,Graph2_fy1048,Graph2_fex1048,Graph2_fey1048);
   gre->SetName("Graph2");
   gre->SetTitle("");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#9c272b");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#9c272b");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.2);
   
   TH1F *Graph_Graph21048 = new TH1F("Graph_Graph21048","",100,0,3.1325);
   Graph_Graph21048->SetMinimum(0.84);
   Graph_Graph21048->SetMaximum(1.16);
   Graph_Graph21048->SetDirectory(0);
   Graph_Graph21048->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21048->SetLineColor(ci);
   Graph_Graph21048->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   Graph_Graph21048->GetXaxis()->SetLabelFont(42);
   Graph_Graph21048->GetXaxis()->SetLabelSize(0.11);
   Graph_Graph21048->GetXaxis()->SetTitleSize(0.12);
   Graph_Graph21048->GetXaxis()->SetTickLength(0.1029336);
   Graph_Graph21048->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21048->GetXaxis()->SetTitleFont(42);
   Graph_Graph21048->GetYaxis()->SetTitle("Ratio");
   Graph_Graph21048->GetYaxis()->CenterTitle(true);
   Graph_Graph21048->GetYaxis()->SetNdivisions(504);
   Graph_Graph21048->GetYaxis()->SetLabelFont(42);
   Graph_Graph21048->GetYaxis()->SetLabelSize(0.11);
   Graph_Graph21048->GetYaxis()->SetTitleSize(0.12);
   Graph_Graph21048->GetYaxis()->SetTickLength(0.05714286);
   Graph_Graph21048->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph21048->GetYaxis()->SetTitleFont(42);
   Graph_Graph21048->GetZaxis()->SetLabelFont(42);
   Graph_Graph21048->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21048->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21048);
   
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
   c1_n7->cd();
   c1_n7->Modified();
   c1_n7->cd();
   c1_n7->SetSelected(c1_n7);
}
