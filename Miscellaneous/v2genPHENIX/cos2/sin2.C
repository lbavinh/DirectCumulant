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




char title[800];
char title1[800];
char title2[800];
char title3[800];
char title4[800];
char title5[800];
//cos2

float sin20[24];
float sin20e[24];

float sin21[24];
float sin21e[24];

float sin22[24];
float sin22e[24];



float sin23[24];
float sin23e[24];

float sin24[24];
float sin24e[24];



float sin25[24];
float sin25e[24];







sprintf(title1,"<sin[2(#phi^{o})> vs p_{T}, toy model simulations");



char hname1[800];
char hname2[800];
char hname3[800];
char hname4[800];





for(int it=0; it<24; it++){

float res2rxn=1.0;
float res4rxn=1.0;

 
 (void) sprintf(hname1,"hsin2_%i_%i",it,0);
TH1F *h3 = (TH1F*) file->Get(hname1);
sin20[it]=(h3->GetMean());
sin20e[it]=0.0001;


 

 
 (void) sprintf(hname1,"hsin2_%i_%i",it,1);
TH1F *h3 = (TH1F*) file->Get(hname1);
sin21[it]=(h3->GetMean());
sin21e[it]=0.0001;

// cout <<sin21[it]<<endl;


 
 (void) sprintf(hname1,"hsin2_%i_%i",it,2);
TH1F *h3 = (TH1F*) file->Get(hname1);
sin22[it]=(h3->GetMean());
sin22e[it]=0.0001;


 
 (void) sprintf(hname1,"hsin2_%i_%i",it,3);
TH1F *h3 = (TH1F*) file->Get(hname1);
sin23[it]=(h3->GetMean());
sin23e[it]=0.0001;



 
 (void) sprintf(hname1,"hsin2_%i_%i",it,4);
TH1F *h3 = (TH1F*) file->Get(hname1);
sin24[it]=(h3->GetMean());
sin24e[it]=0.0001;



 
 (void) sprintf(hname1,"hsin2_%i_%i",it,5);
TH1F *h3 = (TH1F*) file->Get(hname1);
sin25[it]=(h3->GetMean());
sin25e[it]=0.0001;


// cout <<sin25e[it]<<endl;




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
  float ymin1=-0.5;
  float ymax1=0.8;

  TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("p_{T}, GeV/c");
  hr2->SetYTitle("<sin[2(#phi^{o})]>");



  hr2->Draw();



  // const int npt=7;
 gr1 = new TGraphErrors(24,hpt,sin20,hpte,sin20e);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kRed);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.3);
 gr1->Draw("P");

 

  // const int npt=7;
 gr2 = new TGraphErrors(24,hpt,sin21,hpte,sin21e);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kBlue);
 gr2->SetMarkerStyle(24);
 gr2->SetMarkerSize(1.3);
 gr2->Draw("P");






  // const int npt=7;
 gr3 = new TGraphErrors(24,hpt,sin22,hpte,sin22e);
 gr3->SetTitle("TGraphErrors Example ");
 gr3->SetMarkerColor(kMagenta);
 gr3->SetMarkerStyle(21);
 gr3->SetMarkerSize(1.3);
 gr3->Draw("P");






  // const int npt=7;
 gr4 = new TGraphErrors(24,hpt,sin23,hpte,sin23e);
 gr4->SetTitle("TGraphErrors Example ");
 gr4->SetMarkerColor(kGreen);
 gr4->SetMarkerStyle(25);
 gr4->SetMarkerSize(1.3);
 gr4->Draw("P");






  // const int npt=7;
 gr5 = new TGraphErrors(24,hpt,sin24,hpte,sin24e);
 gr5->SetTitle("TGraphErrors Example ");
 gr5->SetMarkerColor(kCyan+1);
 gr5->SetMarkerStyle(22);
 gr5->SetMarkerSize(1.3);
 gr5->Draw("P");






  // const int npt=7;
 gr6 = new TGraphErrors(24,hpt,sin25,hpte,sin25e);
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


  c1->Print("sin2sim.gif");


 //c1







}
