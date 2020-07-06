{


file = new TFile("v2hadron.root");




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


//cos2

char title[800];
char title1[800];
char title2[800];
char title3[800];
char title4[800];
char title5[800];


float cos40[24];
float cos40e[24];

float cos41[24];
float cos41e[24];

float cos42[24];
float cos42e[24];



float cos43[24];
float cos43e[24];

float cos44[24];
float cos44e[24];



float cos45[24];
float cos45e[24];







sprintf(title1,"<cos[4(#phi^{o})> vs p_{T}, toy model simulations");



char hname1[800];
char hname2[800];
char hname3[800];
char hname4[800];





for(int it=0; it<24; it++){

float res2rxn=1.0;
float res4rxn=1.0;

 
 (void) sprintf(hname1,"hcos4_%i_%i",it,0);
TH1F *h3 = (TH1F*) file->Get(hname1);
cos40[it]=(h3->GetMean());
cos40e[it]=0.0001;


 

 
 (void) sprintf(hname1,"hcos4_%i_%i",it,1);
TH1F *h3 = (TH1F*) file->Get(hname1);
cos41[it]=(h3->GetMean());
cos41e[it]=0.0001;

// cout <<cos41[it]<<endl;


 
 (void) sprintf(hname1,"hcos4_%i_%i",it,2);
TH1F *h3 = (TH1F*) file->Get(hname1);
cos42[it]=(h3->GetMean());
cos42e[it]=0.0001;


 
 (void) sprintf(hname1,"hcos4_%i_%i",it,3);
TH1F *h3 = (TH1F*) file->Get(hname1);
cos43[it]=(h3->GetMean());
cos43e[it]=0.0001;



 
 (void) sprintf(hname1,"hcos4_%i_%i",it,4);
TH1F *h3 = (TH1F*) file->Get(hname1);
cos44[it]=(h3->GetMean());
cos44e[it]=0.0001;



 
 (void) sprintf(hname1,"hcos4_%i_%i",it,5);
TH1F *h3 = (TH1F*) file->Get(hname1);
cos45[it]=(h3->GetMean());
cos45e[it]=0.0001;


// cout <<cos45e[it]<<endl;




}


 cout << "plot..."<<endl;







 c1 = new TCanvas("c1","Flow analysis results",200,10,700,550);
  
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
  float ymin1=-0.2;
  float ymax1=1;

  TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("p_{T}, GeV/c");
  hr2->SetYTitle("<cos[4(#phi^{o})]>");



  hr2->Draw();



  // const int npt=7;
 gr1 = new TGraphErrors(24,hpt,cos40,hpte,cos40e);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kRed);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.3);
 gr1->Draw("P");

 

  // const int npt=7;
 gr2 = new TGraphErrors(24,hpt,cos41,hpte,cos41e);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kBlue);
 gr2->SetMarkerStyle(24);
 gr2->SetMarkerSize(1.3);
 gr2->Draw("P");






  // const int npt=7;
 gr3 = new TGraphErrors(24,hpt,cos42,hpte,cos42e);
 gr3->SetTitle("TGraphErrors Example ");
 gr3->SetMarkerColor(kMagenta);
 gr3->SetMarkerStyle(21);
 gr3->SetMarkerSize(1.3);
 gr3->Draw("P");






  // const int npt=7;
 gr4 = new TGraphErrors(24,hpt,cos43,hpte,cos43e);
 gr4->SetTitle("TGraphErrors Example ");
 gr4->SetMarkerColor(kGreen);
 gr4->SetMarkerStyle(25);
 gr4->SetMarkerSize(1.3);
 gr4->Draw("P");






  // const int npt=7;
 gr5 = new TGraphErrors(24,hpt,cos44,hpte,cos44e);
 gr5->SetTitle("TGraphErrors Example ");
 gr5->SetMarkerColor(kCyan+1);
 gr5->SetMarkerStyle(22);
 gr5->SetMarkerSize(1.3);
 gr5->Draw("P");






  // const int npt=7;
 gr6 = new TGraphErrors(24,hpt,cos45,hpte,cos45e);
 gr6->SetTitle("TGraphErrors Example ");
 gr6->SetMarkerColor(kBlack);
 gr6->SetMarkerStyle(23);
 gr6->SetMarkerSize(1.3);
 gr6->Draw("P");






 TLegend *legC12 = new TLegend(0.15,.7,0.6,.87);
 legC12->AddEntry(gr1," [Gen: 2#pi]","lp");
 legC12->AddEntry(gr2," [E+W.ACC]","lp");
 legC12->AddEntry(gr3," [West.ACC]","lp");
 legC12->AddEntry(gr4," [East.ACC]","lp");
 legC12->AddEntry(gr5," [Tof.West.ACC]","lp");
 legC12->AddEntry(gr6," [Tof.East.ACC]","lp");













 legC12->SetFillColor(0);
 legC12->SetBorderSize(0);
 legC12->Draw();


  c1->Print("cos4sim.gif");


 //c1







}
