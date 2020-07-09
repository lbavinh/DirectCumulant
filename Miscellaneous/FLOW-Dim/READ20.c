void read(const char *outfile){

double sv4=0,sv2=0,v2=0,v4=0;

TH1F *SV2=new TH1F("sv2","sv2",2000,-1,1);
TH1F *SV4=new TH1F("sv4","sv4",2000,-1,1);
double pt_bin[11]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0};int NN=11;
TH1F *DiffSV2[11];TH1F *DiffSV4[11];
double *binPt=new double[NN];
double *dn2=new double[NN];double *dn4=new double[NN];
double *Diffv2=new double[NN]; double *Diffv4=new double[NN];
int *DiffMQ2=new int[NN];int *DiffMQ4=new int[NN];
double *Diffsv2=new double[NN]; double *Diffsv4=new double[NN];
char strE[20];char strW[20];


TFile *f=new TFile(outfile);
SV2=(TH1F*)f->Get("sv2");
SV4=(TH1F*)f->Get("sv4");

for(int m=0;m<NN;m++){
sprintf(strE,"%s%d","sv2Diff",m);
sprintf(strW,"%s%d","sv4Diff",m);
const char *EastH=(char*)strE;
const char *WastH=(char*)strW;
DiffSV2[m]=(TH1F*)f->Get(EastH);
DiffSV4[m]=(TH1F*)f->Get(WastH);
}

SV2->Sumw2();SV4->Sumw2();
sv2=SV2->GetMean();v2=pow(fabs(sv2),0.5);
sv4=SV4->GetMean();sv4=sv4-2*(sv2*sv2);v4=pow(fabs(sv4),0.25);
cout <<" v2{2} is "<<v2<<" v2{4} is "<<v4 <<endl;
//Дифференциальный поток
for(int m=0;m<NN-1;m++){
dn2[m]=DiffSV2[m]->GetMean();Diffv2[m]=dn2[m]/pow(fabs(sv2),0.5);
dn4[m]=DiffSV4[m]->GetMean()-2*dn2[m]*sv2;Diffv4[m]=-dn4[m]/pow(fabs(sv4),0.75);
binPt[m]=0.5*(pt_bin[m]+pt_bin[m+1]);
cout <<"Different. flow "<<" v2{2} is "<<dn2[m]<<", v2{4} is "<<Diffv4[m]<<" Pt "<<binPt[m]<<endl ;}

TGraph *grv2 = new TGraph(NN-1,binPt,Diffv2);
grv2->SetMarkerStyle(20);
grv2->SetMarkerSize(1.6);
grv2->SetMarkerColorAlpha(kBlue, 0.35);
grv2->GetYaxis()->SetTitle("V_{2}");
grv2->GetXaxis()->SetTitle("Pt,Gev/c");
grv2->Draw("AP");
grv2->SetTitle("V2{2}");
TGraph *grv4 = new TGraph(NN-1,binPt,Diffv4);
grv4->SetMarkerStyle(20);
grv4->SetMarkerSize(1.6);
grv4->SetMarkerColorAlpha(kRed, 0.35);
grv4->Draw("SAME P");
grv4->SetTitle("V2{4}");

TF1 *momentdist = new TF1("momentdist","[1]*x+[0]", 0., 2);
momentdist->FixParameter(0, 0.05);
momentdist->FixParameter(1, 0.1);
momentdist->Draw("SAME");
gPad->BuildLegend();
gROOT->SetStyle("Pub");
}
