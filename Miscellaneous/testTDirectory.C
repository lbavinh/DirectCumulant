void testTDirectory()
{
  TFile *f = new TFile("test.root","RECREATE");
  TH1F *h1 = new TH1F("h1","my hist",300,-3,3);
  TH1F *h2 = new TH1F("h2","my hist",300,-3,3);
  TH1F *h3 = new TH1F("h3","my hist",300,-3,3);
  h2->FillRandom("gaus", 1000);
  h1->FillRandom("gaus", 10000);
  h3->FillRandom("gaus", 10000);
  TDirectoryFile *dir1 = new TDirectoryFile("Dir1","Dir1");
  TDirectoryFile *dir2 = new TDirectoryFile("Dir2","Dir2");
  dir1->Add(h1);
  dir2->Add(h2);
  dir1->Write();
  dir2->Write();
  h3->Write();
  f->Close();
}

void readHistFromTDirectory()
{
  TFile *f = new TFile("test.root","READ");
  TH1F *h3 = (TH1F*) f->FindObjectAny("h3");
  TH1F *h1 = (TH1F*) f->Get("Dir1/h1");
  h3->Draw();
  h1->SetLineColor(kRed);
  h1->Draw("same");
}