void ProducePartDist()
{
   TH1D* hdist = new TH1D("hvnMod_mult","hvnMod_mult",3000,0.,3000.);
   for(int i=0; i<hdist->GetNbinsX(); ++i)
   {
      double val = fit->Eval(hdist->GetBinCenter(i+1));
      if(val<0) val =0;
      hdist->SetBinContent(i+1,val);
      hdist->SetBinError  (i+1,0.);
   }

   hdist->Scale(1./hdist->GetMaximum());
   hdist->Draw();

   TF1* fc_etaexp = new TF1("etaSpectrum","exp(-0.5 * pow((x+2)/5,2))+exp(-0.5 * pow((x-2)/5,2))",-10.,10.);
   //TF1* fc_etaexp = new TF1("etaSpectrum","exp(0.*x)",-10.,10.);
   TH1D* hdisteta = new TH1D("hvnMod_eta","hvnMod_eta",2000,-10.,10.);
   for(int i=0; i<hdisteta->GetNbinsX(); ++i)
   {
      double val = fc_etaexp->Eval(hdisteta->GetBinCenter(i+1));
      if(val<0) val =0;
      hdisteta->SetBinContent(i+1,val);
      hdisteta->SetBinError  (i+1,0.);
   }
   hdisteta->Scale(1./hdisteta->GetMaximum());
   hdisteta->Draw();

   TF1* fc_ptexp = new TF1("ptSpectrum","x*exp(-1*(sqrt(pow(2.5,2)+pow(x,2)))/(5))",0.,20.);
   //TF1* fc_ptexp = new TF1("ptSpectrum","exp(0.*x)",0.,20.);
   TH1D* hdistpt = new TH1D("hvnMod_pt","hvnMod_pt",2000,0.,20.);
   for(int i=0; i<hdistpt->GetNbinsX(); ++i)
   {
      double val = fc_ptexp->Eval(hdistpt->GetBinCenter(i+1));
      if(val<0) val =0;
      hdistpt->SetBinContent(i+1,val);
      hdistpt->SetBinError  (i+1,0.);
   }
   hdistpt->Scale(1./hdistpt->GetMaximum());
   hdistpt->Draw();

   double vn1[10] = {0., 0., 0.1, 0.05, 0.015, 0.01, 0.005, 0.005, 0.001, 0.0005};
   TH1D*vnVal_PbPb = new TH1D("vnVal_PbPb", "hvnMod_mag", 10, 0, 10);
   for(int i=0; i<vnVal_PbPb->GetNbinsX(); ++i)
   {
      vnVal_PbPb->SetBinContent(i+1,vn1[i]);
      vnVal_PbPb->SetBinError(i+1,0.);
   }
   vnVal_PbPb->Draw();

   double vn2[10] = {0., 0., 0.08, 0.05, 0.015, 0.01, 0.005, 0.005, 0.001, 0.0005};
   TH1D*vnVal_pPb = new TH1D("vnVal_pPb", "hvnMod_mag", 10, 0, 10);
   for(int i=0; i<vnVal_pPb->GetNbinsX(); ++i)
   {
      vnVal_pPb->SetBinContent(i+1,vn2[i]);
      vnVal_pPb->SetBinError(i+1,0.);
   }

   double vn3[10] = {0., 0., 0.6, 0.03, 0.01, 0.005, 0.001, 0.001, 0.0005, 0.0001};
   TH1D*vnVal_pp = new TH1D("vnVal_pp", "hvnMod_mag", 10, 0, 10);
   for(int i=0; i<vnVal_pp->GetNbinsX(); ++i)
   {
      vnVal_pp->SetBinContent(i+1,vn3[i]);
      vnVal_pp->SetBinError(i+1,0.);
   }

   TFile* fout = new TFile("ToyMCVn_exp.root","RECREATE");
   TDirectory* dir1 = fout->mkdir("PbPb");
   dir1->cd();
   hdistpt->Write("hvnMod_pt");
   hdisteta->Write("hvnMod_eta");
   hdist->Write("hvnMod_mult");
   vnVal_PbPb->Write("hvnMod_mag");

   TDirectory* dir2 = fout->mkdir("pPb");
   dir2->cd();
   hdistpt->Write("hvnMod_pt");
   hdisteta->Write("hvnMod_eta");
   hdist->Write("hvnMod_mult");
   vnVal_pPb->Write("hvnMod_mag");

   TDirectory* dir3 = fout->mkdir("pp");
   dir3->cd();
   hdistpt->Write("hvnMod_pt");
   hdisteta->Write("hvnMod_eta");
   hdist->Write("hvnMod_mult");
   vnVal_pp->Write("hvnMod_mag");

   fout->Close();
   delete fout;



   

}
