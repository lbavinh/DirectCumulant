void data_ALICE()
{
   Double_t xAxis1[31] = {0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.11, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3, 0.33, 0.34, 0.36, 0.38, 0.4, 0.42, 0.44, 0.46, 0.48, 0.5};
 
   TH1D *halice = new TH1D("halice","",30, xAxis1);
   halice->SetBinContent(1,0.5449);
   halice->SetBinContent(2,0.5019);
   halice->SetBinContent(3,0.4785);
   halice->SetBinContent(4,0.4433);
   halice->SetBinContent(5,0.4433);
   halice->SetBinContent(6,0.4277);
   halice->SetBinContent(7,0.4042);
   halice->SetBinContent(8,0.3945);
   halice->SetBinContent(9,0.3867);
   halice->SetBinContent(10,0.3925);
   halice->SetBinContent(11,0.3789);
   halice->SetBinContent(12,0.3730);
   halice->SetBinContent(13,0.3625);
   halice->SetBinContent(14,0.3730);
   halice->SetBinContent(15,0.3710);
   halice->SetBinContent(16,0.3554);
   halice->SetBinContent(17,0.3574);
   halice->SetBinContent(18,0.3574);
   halice->SetBinContent(19,0.3632);
   halice->SetBinContent(20,0.3613);
   halice->SetBinContent(21,0.3574);
   halice->SetBinContent(22,0.3632);
   halice->SetBinContent(23,0.3671);
   halice->SetBinContent(24,0.375);
   halice->SetBinContent(25,0.3886);
   halice->SetBinContent(26,0.3867);
   halice->SetBinContent(27,0.3945);
   halice->SetBinContent(28,0.3984);
   halice->SetBinContent(29,0.4082);
   halice->SetBinContent(30,0.4160);

   for(Int_t i=1;i<=30;i++){halice->SetBinError(i,0.05);};
  
   halice->SetMinimum(0);
   halice->SetMaximum(0.8);
   halice->SetEntries(30);
   halice->SetStats(0);
   halice->SetLineColor(1);
   halice->GetXaxis()->SetTitle("centrality");
   halice->GetXaxis()->SetLabelFont(42);
   halice->GetXaxis()->SetTitleSize(0.05);
   halice->GetXaxis()->SetTitleOffset(0.8);
   halice->GetXaxis()->SetTitleFont(42);
   halice->GetYaxis()->SetTitle("#Delta#epsilon*/#epsilon*    ");
   halice->GetYaxis()->SetLabelFont(42);
   halice->GetYaxis()->SetTitleSize(0.05);
   halice->GetYaxis()->SetTitleOffset(0.8);
   halice->GetYaxis()->SetTitleFont(42);
   halice->GetZaxis()->SetLabelFont(42);
   halice->GetZaxis()->SetLabelSize(0.035);
   halice->GetZaxis()->SetTitleSize(0.035);
   halice->GetZaxis()->SetTitleFont(42);
   halice->Draw("][ E1 SAME");
}
