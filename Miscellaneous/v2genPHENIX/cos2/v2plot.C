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


float v2[24];
float v2e[24];


float v2W[24];
float v2We[24];

float v2E[24];
float v2Ee[24];


float v2TW[24];
float v2TWe[24];

float v2TE[24];
float v2TEe[24];


float m2[24];
float m2e[24];


float R1[24];
float ER1[24];


float R2[24];
float ER2[24];


float R3[24];
float ER3[24];



float R4[24];
float ER4[24];


float R5[24];
float ER5[24];





sprintf(title1,"V_{n} vs p_{T}");



char hname1[800];
char hname2[800];
char hname3[800];
char hname4[800];





for(int it=0; it<24; it++){

float res2rxn=1.0;
float res4rxn=1.0;

 
(void) sprintf(hname1,"hv2pt_%i",it);
TH1F *h3 = (TH1F*) file->Get(hname1);
v2[it]=(h3->GetMean())/res2rxn;
float rms=(h3->GetRMS());
int nent=(h3->GetEntries());
float err =rms/sqrt(nent);
v2e[it]=err/res2rxn;



 
(void) sprintf(hname1,"hv2Ept_%i",it);
TH1F *h3 = (TH1F*) file->Get(hname1);
v2E[it]=(h3->GetMean())/res2rxn;
float rms=(h3->GetRMS());
int nent=(h3->GetEntries());
float err =rms/sqrt(nent);
v2Ee[it]=err/res2rxn;


 
(void) sprintf(hname1,"hv2Wpt_%i",it);
TH1F *h3 = (TH1F*) file->Get(hname1);
v2W[it]=(h3->GetMean())/res2rxn;
float rms=(h3->GetRMS());
int nent=(h3->GetEntries());
float err =rms/sqrt(nent);
v2We[it]=err/res2rxn;




 
(void) sprintf(hname1,"hv2TEpt_%i",it);
TH1F *h3 = (TH1F*) file->Get(hname1);
v2TE[it]=(h3->GetMean())/res2rxn;
float rms=(h3->GetRMS());
int nent=(h3->GetEntries());
float err =rms/sqrt(nent);
v2TEe[it]=err/res2rxn;


 
(void) sprintf(hname1,"hv2TWpt_%i",it);
TH1F *h3 = (TH1F*) file->Get(hname1);
v2TW[it]=(h3->GetMean())/res2rxn;
float rms=(h3->GetRMS());
int nent=(h3->GetEntries());
float err =rms/sqrt(nent);
v2TWe[it]=err/res2rxn;













(void) sprintf(hname1,"mv2pt_%i",it);
TH1F *h3 = (TH1F*) file->Get(hname1);
 m2[it]=(h3->GetMean())/res2rxn;
float rms=(h3->GetRMS());
int nent=(h3->GetEntries());
float err =rms/sqrt(nent);
m2e[it]=err/res2rxn;



R1[it]=m2[it]/v2[it];
ER1[it]=sqrt((v2e[it]*v2e[it])/(v2[it]*v2[it])+(m2e[it]*m2e[it])/(m2[it]*m2[it]))*R1[it];

R2[it]=v2W[it]/v2[it];
ER2[it]=sqrt((v2e[it]*v2e[it])/(v2[it]*v2[it])+(v2We[it]*v2We[it])/(v2W[it]*v2W[it]))*R2[it];

R3[it]=v2E[it]/v2[it];
ER3[it]=sqrt((v2e[it]*v2e[it])/(v2[it]*v2[it])+(v2Ee[it]*v2Ee[it])/(v2E[it]*v2E[it]))*R3[it];



R4[it]=v2TW[it]/v2[it];
ER4[it]=sqrt((v2e[it]*v2e[it])/(v2[it]*v2[it])+(v2TWe[it]*v2TWe[it])/(v2TW[it]*v2TW[it]))*R4[it];

R5[it]=v2TE[it]/v2[it];
ER5[it]=sqrt((v2e[it]*v2e[it])/(v2[it]*v2[it])+(v2TEe[it]*v2TEe[it])/(v2TE[it]*v2TE[it]))*R5[it];









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
  float ymin1=0.0;
  float ymax1=0.3;

  TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("p_{T}, GeV/c");
  hr2->SetYTitle("V_{n}");



  hr2->Draw();



  // const int npt=7;
 gr1 = new TGraphErrors(24,hpt,v2,hpte,v2e);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kRed);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.3);
 gr1->Draw("P");

  // const int npt=7;
 gr2 = new TGraphErrors(24,hpt,m2,hpte,m2e);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kBlue);
 gr2->SetMarkerStyle(24);
 gr2->SetMarkerSize(1.3);
 gr2->Draw("P");



  // const int npt=7;
 gr3 = new TGraphErrors(24,hpt,v2E,hpte,v2Ee);
 gr3->SetTitle("TGraphErrors Example ");
 gr3->SetMarkerColor(kGreen);
 gr3->SetMarkerStyle(22);
 gr3->SetMarkerSize(1.3);
 gr3->Draw("P");






  // const int npt=7;
 gr4 = new TGraphErrors(24,hpt,v2W,hpte,v2We);
 gr4->SetTitle("TGraphErrors Example ");
 gr4->SetMarkerColor(kMagenta);
 gr4->SetMarkerStyle(23);
 gr4->SetMarkerSize(1.3);
 gr4->Draw("P");





 TLegend *legC12 = new TLegend(0.15,.7,0.6,.87);
 legC12->AddEntry(gr1,"V_{2} [Gen]","lp");
 legC12->AddEntry(gr2,"V_{2}[E+W]","lp");
 legC12->AddEntry(gr3,"V_{2}[E]","lp");
 legC12->AddEntry(gr4,"V_{2}[W]","lp");
















 legC12->SetFillColor(0);
 legC12->SetBorderSize(0);
 legC12->Draw();


 // c1->Print(fout10);


 //c1




c2 = new TCanvas("c2","Flow analysis results",200,10,700,550);
  
 c2->GetFrame()->SetBorderSize(12);

 c2->cd(); 
	
  gStyle->SetOptStat(0);

 c2->GetFrame()->SetFillColor(19);
 c2->GetFrame()->SetBorderSize(12);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetHistFillColor(10);
  gStyle->SetHistFillStyle(0);
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);
  c2->SetBorderMode(0);

  c2->SetFillColor(0);
  float xmin1=0.1;
  float xmax1=3.8;
  float ymin1=0.8;
  float ymax1=1.2;

  TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("p_{T}, GeV/c");
  hr2->SetYTitle("V_{n}");



  hr2->Draw();



  // const int npt=7;
 gr1 = new TGraphErrors(24,hpt,R1,hpte,ER1);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kRed);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.3);
 gr1->Draw("P");

 


  // const int npt=7;
 gr2 = new TGraphErrors(24,hpt,R2,hpte,ER2);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kBlue);
 gr2->SetMarkerStyle(21);
 gr2->SetMarkerSize(1.3);
 gr2->Draw("P");




  // const int npt=7;
 gr3 = new TGraphErrors(24,hpt,R3,hpte,ER3);
 gr3->SetTitle("TGraphErrors Example ");
 gr3->SetMarkerColor(kBlack);
 gr3->SetMarkerStyle(24);
 gr3->SetMarkerSize(1.3);
 gr3->Draw("P");




  // const int npt=7;
 gr4 = new TGraphErrors(24,hpt,R4,hpte,ER4);
 gr4->SetTitle("TGraphErrors Example ");
 gr4->SetMarkerColor(kCyan+1);
 gr4->SetMarkerStyle(22);
 gr4->SetMarkerSize(1.3);
 gr4->Draw("P");




  // const int npt=7;
 gr5 = new TGraphErrors(24,hpt,R5,hpte,ER5);
 gr5->SetTitle("TGraphErrors Example ");
 gr5->SetMarkerColor(kMagenta);
 gr5->SetMarkerStyle(23);
 gr5->SetMarkerSize(1.3);
 gr5->Draw("P");













 TLegend *legC22 = new TLegend(0.15,.76,0.6,.87);

 
 legC12->AddEntry(gr1,"V_{2}[E+W]/V_{2}","lp");
 legC12->AddEntry(gr2,"V_{2}[E]","lp");
 legC12->AddEntry(gr3,"V_{2}[W]","lp");
 legC12->AddEntry(gr4,"V_{2}[Tof.W]","lp");
 legC12->AddEntry(gr5,"V_{2}[Tof.E]","lp");















 legC22->SetFillColor(0);
 legC22->SetBorderSize(0);
 legC22->Draw();


 // c2->Print(fout10);


 //c2


}
