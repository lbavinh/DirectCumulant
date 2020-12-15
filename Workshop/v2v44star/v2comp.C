
void makeplotstyle(){
  
  TStyle *mystyle = new TStyle("PlottingInStyle", "Style for Summary Plots");
  mystyle->SetPalette(1);
  mystyle->SetCanvasColor(10);
  mystyle->SetHistFillColor(10);
  mystyle->SetHistFillStyle(0);
  mystyle->SetOptTitle(0);
  mystyle->SetOptStat(0);
  mystyle->SetCanvasBorderMode(0);//removes the yellow frame around the canvas
  mystyle->SetPadLeftMargin(0.17);
  mystyle->SetPadBottomMargin(0.2);
  mystyle->SetPadTickX(1);
  mystyle->SetPadTickY(1);
  mystyle->SetAxisColor(1, "X");
  mystyle->SetAxisColor(1, "Y");
  mystyle->SetLabelColor(1, "X");
  mystyle->SetLabelColor(1, "Y");
  mystyle->SetTickLength(0.03, "X");
  mystyle->SetTickLength(0.03, "Y");
  mystyle->SetTitleXSize(0.05);
  mystyle->SetTitleYSize(0.05);
  mystyle->SetNdivisions(505, "X");
  mystyle->SetNdivisions(505, "Y");
  mystyle->SetTitleXOffset(1.5);
  mystyle->SetTitleYOffset(1.5);
  mystyle->SetLabelOffset(0.02, "X");
  mystyle->SetLabelOffset(0.02, "Y");
  mystyle->SetLabelSize(0.05, "X");
  mystyle->SetLabelSize(0.05, "Y");
  //mystyle->SetGridx();

  TFile f("style.root", "RECREATE");
  f.cd();
  mystyle->Write();
  f.Close();
}


















void v2comp(int icent=0)
{


 makeplotstyle();

 TFile *fstyle = new TFile("style.root");
  TStyle *tsty = (TStyle *)fstyle->Get("PlottingInStyle");
  tsty->cd();

  gROOT->ForceStyle();
  gStyle->SetOptStat(0);



















 //pt=12


  int clow[6]={0,10,20,30,40};
  int chg[6]= {10,20,30,40,50};


char title1[800];
char title2[800];
char title3[800];

sprintf(title2," V_{2}[ 39/62 GeV ] / V_{2}[ 200 GeV ] vs p_{T} , Au+Au   %d-%d %%",clow[icent],chg[icent]);
sprintf(title1," V_{2} vs p_{T} , Au+Au   #sqrt{s_{NN}} = 39 - 200 GeV , %d-%d %%",clow[icent],chg[icent]);

 FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
FILE *fp11,*fp22,*fp33,*fp44,*fp55;

char path1[800];
char path2[800];
char path3[800];
char path4[800];



sprintf(path1,"./v2methods39ptCent20-30.txt");
sprintf(path2,"./v2methods39ptCent20-30.txt");
sprintf(path3,"./v2methods39ptCent20-30.txt");










if((fp1=fopen(path1,"r"))== NULL) {
        cout << "\n Can't open file summary1.txt !\n"<< endl;
        fflush(stdin);
        return;
  }



if((fp2=fopen(path2,"r"))== NULL) {
        cout << "\n Can't open file summary1.txt !\n"<< endl;
        fflush(stdin);
        return;
  }




if((fp3=fopen(path3,"r"))== NULL) {
        cout << "\n Can't open file summary1.txt !\n"<< endl;
        fflush(stdin);
        return;
  }







//82






//14

float hpt[14];
float hpte[14];



float v2eta[14];
float v2etae[14];


float v22[14];
float v22e[14];


float v24[14];
float v24e[14];


float sysL2[14];
float sysH2[14];


float sysL3[14];
float sysH3[14];


float sysL4[14];
float sysH4[14];




float sysL22[14];
float sysH22[14];


float sysL33[14];
float sysH33[14];
















for (int i=0; i<14; i++) {

    int run;
    float  ppt,s2,s2e,s2eta,s2etae,s22,s22e,s24,s24e,s2b,s2be;
    fscanf(fp1, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&ppt,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

    hpt[i]= ppt;
    v2eta[i]=s2eta;
    v2etae[i]= s2etae;
    hpte[i]=0.01;

    sysL2[i]=s2eta*0.04;
    sysH2[i]=s2eta*0.04;


 }


for (int i=0; i<14; i++) {

    int run;
    float  ppt,s2,s2e,s2eta,s2etae,s22,s22e,s24,s24e,s2b,s2be;
    fscanf(fp2, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&ppt,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

    hpt[i]= ppt;
    v22[i]=s22;
    v22e[i]= s22e;
    hpte[i]=0.01;

    sysL3[i]=s22*0.04;
    sysH3[i]=s22*0.04;


 }



for (int i=0; i<14; i++) {

    int run;
    float  ppt,s2,s2e,s2eta,s2etae,s22,s22e,s24,s24e,s2b,s2be;
    fscanf(fp3, "%f  %f  %f  %f  %f  %f  %f  %f  %f %f %f\n",&ppt,&s2,&s2e,&s2eta,&s2etae,&s22,&s22e,&s24,&s24e,&s2b,&s2be);

    hpt[i]= ppt;
    v24[i]=s24;
    v24e[i]= s24e;
    hpte[i]=0.01;

    sysL4[i]=s24*0.04;
    sysH4[i]=s24*0.04;


 }







char hname1[800];
char hname2[800];
char hname3[800];
char hname15[800];




float R1[15];
float R2[15];
float R3[15];
float R4[15];

float R1E[15];
float R2E[15];
float R3E[15];
float R4E[15];







// main pt loop









char fout1[800];
char fout2[800];
char fout3[800];
char fout15[800];
char fout6[800];
char fout7[800];

char fout8[800];
char fout9[800];




sprintf(fout2,"Rv2BeamRXNCent%d-%d.gif",clow[icent],chg[icent]);
sprintf(fout3,"v2PtBeamCent%d-%d.gif",clow[icent],chg[icent]);

 float mpcv2[10];





for(int k=0; k<14; k++){




R1[k]=v2eta[k]/v22[k];
R1E[k]=sqrt((v22e[k]*v22e[k])/(v22[k]*v22[k]) + (v2etae[k]*v2etae[k])/(v2eta[k]*v2eta[k]))*R1[k];


R2[k]=v24[k]/v22[k];
R2E[k]=sqrt((v22e[k]*v22e[k])/(v22[k]*v22[k]) + (v24e[k]*v24e[k])/(v24[k]*v24[k]))*R2[k];





    sysL22[k]=R1[k]*0.02;
    sysH22[k]=R1[k]*0.02;

    sysL33[k]=R2[k]*0.02;
    sysH33[k]=R2[k]*0.02;

 

 }











TCanvas *c1;



 c1 = new TCanvas("c1","Flow analysis results",150,10,700,550);
  
  c1->GetFrame()->SetBorderSize(115);

 c1->cd(); 
	
  gStyle->SetOptStat(0);

 c1->GetFrame()->SetFillColor(21);
 c1->GetFrame()->SetBorderSize(115);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetHistFillColor(10);
  gStyle->SetHistFillStyle(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  c1->SetBorderMode(0);

  c1->SetFillColor(0);
  float xmin1=0.1;
  float xmax1=3.2;
  float ymin1=0.6;
  float ymax1=1.4;

  
  if(icent==0) ymax1=1.35;









 TH2F *hr2 = new TH2F("hr2",title2, 2,xmin1,xmax1,2,ymin1,ymax1);

  hr2->SetXTitle("P_{T} (GeV/c) ");
  hr2->SetYTitle("V_{2} ratio [ over v_{2}{2}]      ");



  hr2->Draw();


  TGraphErrors *gr1;
  TGraphErrors *gr2;
  TGraphErrors *gr3;
  


  // const int npt=115;
  gr1 = new TGraphErrors(14,hpt,R1,hpte,R1E);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kBlack);
 gr1->SetMarkerStyle(22);
 gr1->SetMarkerSize(1.3);
 //gr1->Draw("P");



 gr2 = new TGraphErrors(14,hpt,R2,hpte,R2E);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kBlue);
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(1.2);
 // gr2->Draw("P");


 //18

 
  TGraph *syst22 = new TGraphAsymmErrors(14,hpt,R2,hpte,R2E,sysL33,sysH33);
  syst22->SetLineWidth(12); // broad line
  syst22->SetLineColor(19); // light grey
  syst22->SetMarkerStyle(2); // never mind
  syst22->SetMarkerColor(kWhite); // don't show marker




  TGraph *syst21 = new TGraphAsymmErrors(14,hpt,R1,hpte,R1E,sysL22,sysH22);
  syst21->SetLineWidth(12); // broad line
  syst21->SetLineColor(kYellow-8); // light grey
  syst21->SetMarkerStyle(1); // never mind
  syst21->SetMarkerColor(kWhite); // don't show marker








 syst22->Draw("EPZ");

syst21->Draw("EPZ");
gr1->Draw("PZ");
gr2->Draw("PZ");

 TLine *line;


line = new TLine(0.1,1.,3.2,1.);
            line->SetLineStyle(2);
            line->Draw();






 TLegend *legC2 = new TLegend(0.18,0.8,0.48,.88);

  legC2->AddEntry(gr1,"v_{2}{EtaSubs}/V_{2}{2}","p");
  legC2->AddEntry(gr2,"v_{2}{4}/v_{2}{2}","p");





  legC2->SetFillColor(kWhite);
  legC2->SetBorderSize(0); legC2->Draw();

TLatex *   tex = new TLatex(1.5,1.3,"Au+Au at #sqrt{s_{NN}} = 39  GeV");
   tex->SetLineWidth(2);
   tex->SetTextSize(0.042);
   tex->SetTextColor(2);
   tex->Draw();




 c1->Print(fout2);






TCanvas *c2;


 c2 = new TCanvas("c2","Flow analysis results",150,10,700,550);
  
  c2->GetFrame()->SetBorderSize(115);

 c2->cd(); 
	
  gStyle->SetOptStat(0);

 c2->GetFrame()->SetFillColor(21);
 c2->GetFrame()->SetBorderSize(115);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetHistFillColor(10);
  gStyle->SetHistFillStyle(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  c2->SetBorderMode(0);

  c2->SetFillColor(0);
  float xmin11=0.1;
  float xmax11=3.2;
  float ymin11=0.0;
  float ymax11=0.3;

  

 







 TH2F *hr22 = new TH2F("hr22",title1, 2,xmin11,xmax11,2,ymin11,ymax11);

  hr22->SetXTitle("P_{T} (GeV/c) ");
  hr22->SetYTitle("V_{2}          ");



  hr22->Draw();




  // const int npt=115;
  gr1 = new TGraphErrors(14,hpt,v2eta,hpte,v2etae);
 gr1->SetTitle("TGraphErrors Example ");
 gr1->SetMarkerColor(kBlue);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.3);
 // gr1->Draw("P");



 gr2 = new TGraphErrors(14,hpt,v22,hpte,v22e);
 gr2->SetTitle("TGraphErrors Example ");
 gr2->SetMarkerColor(kBlack);
 gr2->SetMarkerStyle(22);
 gr2->SetMarkerSize(1.3);
 // gr2->Draw("P");


 gr3 = new TGraphErrors(14,hpt,v24,hpte,v24e);
 gr3->SetTitle("TGraphErrors Example ");
 gr3->SetMarkerColor(kRed);
 gr3->SetMarkerStyle(25);
 gr3->SetMarkerSize(1.1);
 //gr3->Draw("P");



  TGraph *syst1 = new TGraphAsymmErrors(14,hpt,v2eta,hpte,v2etae,sysL3,sysH3);
  syst1->SetLineWidth(15); // broad line
  syst1->SetLineColor(kYellow-8); // light grey
  syst1->SetMarkerStyle(1); // never mind
  syst1->SetMarkerColor(kWhite); // don't show marker




  TGraph *syst2 = new TGraphAsymmErrors(14,hpt,v22,hpte,v22e,sysL2,sysH2);
  syst2->SetLineWidth(15); // broad line
  syst2->SetLineColor(18); // light grey
  syst2->SetMarkerStyle(1); // never mind
  syst2->SetMarkerColor(kWhite); // don't show marker


  TGraph *syst3 = new TGraphAsymmErrors(14,hpt,v24,hpte,v24e,sysL4,sysH4);
  syst3->SetLineWidth(15); // broad line
  syst3->SetLineColor(18); // light grey
  syst3->SetMarkerStyle(1); // never mind
  syst3->SetMarkerColor(kWhite); // don't show marker






syst2->Draw("EPZ");
syst3->Draw("EPZ");
syst1->Draw("EPZ");
gr1->Draw("PZ");
gr2->Draw("PZ");
gr3->Draw("PZ");

 
 TLegend *legC22 = new TLegend(0.18,0.72,0.45,.88);




  legC22->AddEntry(gr1,"v_{2}{#eta-sub}","p");
  legC22->AddEntry(gr2,"v_{2}{2}","p");
  legC22->AddEntry(gr3,"v_{2}{4}","p");
  

  legC22->SetFillColor(kWhite);
  legC22->SetBorderSize(0); legC22->Draw();



 TLatex *   tex2 = new TLatex(1.5,0.27,"Au+Au at #sqrt{s_{NN}} = 39  GeV");
   tex2->SetLineWidth(2);
   tex2->SetTextSize(0.04);
   tex2->SetTextColor(2);
   tex2->Draw();






 c2->Print(fout3);

}
