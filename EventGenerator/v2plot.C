void v2plot()
{
  TFile *file = new TFile("v2hadron.root");

  float hpt[24];
  float hpte[24];

  char hname5[800];

  for(int i=0; i<24; i++){
    (void) sprintf(hname5,"hpt_%i",i);
      TH1F *h2 = (TH1F*) file->Get(hname5);
      hpt[i]=h2->GetMean();
      hpte[i]=0.001;
      cout <<hpt[i]<<endl;
  }

  char title1[800];

  float v2[24];
  float v2e[24];

  sprintf(title1,"V_{n} vs p_{T}");

  char hname1[800];

  float rms;
  int nent;
  float err;
  TH1F *h3;

  for(int it=0; it<24; it++){

    float res2rxn=1.0;
    float res4rxn=1.0;
    
    (void) sprintf(hname1,"hv2pt_%i",it);
    h3 = (TH1F*) file->Get(hname1);
    v2[it]=(h3->GetMean())/res2rxn;
    rms=(h3->GetRMS());
    nent=(h3->GetEntries());
    err =rms/sqrt(nent);
    v2e[it]=err/res2rxn;

  }

  cout << "plot..."<<endl;


  auto c1 = new TCanvas("c1","Flow analysis results",200,10,700,550);
    
  c1->GetFrame()->SetBorderSize(12);

  c1->cd(); 
	
  gStyle->SetOptStat(0);

  c1->GetFrame()->SetFillColor(19);
  c1->GetFrame()->SetBorderSize(12);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetHistFillColor(10);
  gStyle->SetHistFillStyle(0);
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);
  c1->SetBorderMode(0);

  c1->SetFillColor(0);
  float xmin1=0.1;
  float xmax1=3.8;
  float ymin1=0.0;
  float ymax1=0.3;

  TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("p_{T}, GeV/c");
  hr2->SetYTitle("V_{n}");

  hr2->Draw();

  // const int npt=7;
  auto gr1 = new TGraphErrors(24,hpt,v2,hpte,v2e);
  gr1->SetTitle("TGraphErrors Example ");
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.3);
  gr1->Draw("P");


  TLegend *legC12 = new TLegend(0.15,.7,0.6,.87);
  legC12->AddEntry(gr1,"V_{2} [Gen]","lp");
  //legC12->AddEntry(gr2,"V_{2}[E+W]","lp");



  legC12->SetFillColor(0);
  legC12->SetBorderSize(0);
  legC12->Draw();

  // c1->Print(fout10);
}
