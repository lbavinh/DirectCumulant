#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include "TComplex.h"
TFile *d_outfile;

TComplex Q,Q2,ZQQQ;
double MCQ;
TComplex p[10],p2[10];TComplex q[10],q2[10];

double pt_min=0.5,pt_max=2.;
//double pt_bin[11]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};int NN=10;
//double pt_bin[11]={0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,2.,2.2};int NN=10;
double pt_bin[11]={0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.7,2.0,2.4};int NN=10;
int MQ2=0,MQ4=0,M=0;
int *mp=new int[NN];int *mq=new int[NN];
int *DiffMQ2=new int[NN];int *DiffMQ4=new int[NN];
double sv4=0,sv2=0,v4,v2,vMC,cn2,cn4;


TH1F *SV2=new TH1F("sv2","sv2",10000,-1,1);//2 частичная референсная корреляция
TH1F *SV4=new TH1F("sv4","sv4",10000,-1,1);//4 частичная референсная корреляция
TH1F *COSf1=new TH1F("cosf1","cosf1",10000,-1,1);
TH1F *SINf1=new TH1F("sinf1","sinf1",10000,-1,1);
TH1F *COSf1f2=new TH1F("cosf1f2","cosf1",10000,-1,1);
TH1F *SINf1f2=new TH1F("sinf1f2","sinf1f2",10000,-1,1);
TH1F *COSf1f2f3=new TH1F("cosf1f2f3","cosf1",10000,-1,1);
TH1F *SINf1f2f3=new TH1F("sinf1f2f3","sinf1f2f3",10000,-1,1);
TH1I *hNpart=new TH1I("hNpart","hNpart",1000,0,1000);
TH1F *SV2_SV4=new TH1F("sv2_sv4","sv2_sv4",10000,-2,2);
TH1F *HMC=new TH1F("mc","mc",10000,-2,2);
TH1F *DiffSV2[10];TH1F *DiffSV4[10];TH1F *DiffMC[10];
TH1F *SV2_DiffSV2[10];TH1F *SV2_DiffSV4[10];
TH1F *SV4_DiffSV2[10];TH1F *SV4_DiffSV4[10];
TH1F *DiffSV2_DiffSV4[10];

TH1F *COSp1[10];TH1F *SINp1[10];
TH1F *COSp1f2[10];TH1F *SINp1f2[10];
TH1F *COSp1f2mf3[10];TH1F *SINp1f2mf3[10];
TH1F *COSp1mf2mf3[10];TH1F *SINp1mf2mf3[10];

double *binPt=new double[NN];
double *QMC=new double[NN];
double *dn2=new double[NN];double *dn4=new double[NN];
double *Diffv2=new double[NN]; double *Diffv4=new double[NN];
double *Diffsv2=new double[NN]; double *Diffsv4=new double[NN];

char strCOVsv2sv2[20];char strCOVsv2sv4[20];
char strCOVsv4sv2[20];char strCOVsv4sv4[20];
char DiffCOVsv2sv4[20];
char strE[20];char strW[20];char strMC[20];

char strCOSp1[20];char strSINp1[20];
char strCOSp1f2[20];char strSINp1f2[20];
char strCOSp1f2mf3[20];char strSINp1f2mf3[20];
char strCOSp1mf2mf3[20];char strSINp1mf2mf3[20];

void MyClass::Book()
{
for(int m=0;m<NN;m++){
sprintf(strE,"%s%d","sv2Diff",m);
sprintf(strW,"%s%d","sv4Diff",m);
sprintf(strMC,"%s%d","DiffMC",m);
sprintf(strCOVsv2sv2,"%s%d","SV2_DiffSV2",m);
sprintf(strCOVsv2sv4,"%s%d","SV2_DiffSV4",m);
sprintf(strCOVsv4sv2,"%s%d","SV4_DiffSV2",m);
sprintf(strCOVsv4sv4,"%s%d","SV4_DiffSV4",m);
sprintf(DiffCOVsv2sv4,"%s%d","DiffSV2_DiffSV4",m);

sprintf(strCOSp1,"%s%d","COSp1",m);
sprintf(strCOSp1f2,"%s%d","COSp1f2",m);
sprintf(strCOSp1f2mf3,"%s%d","COSp1f2mf3",m);
sprintf(strCOSp1mf2mf3,"%s%d","COSp1mf2mf3",m);
sprintf(strSINp1,"%s%d","SINp1",m);
sprintf(strSINp1f2,"%s%d","SINp1f2",m);
sprintf(strSINp1f2mf3,"%s%d","SINp1f2mf3",m);
sprintf(strSINp1mf2mf3,"%s%d","SINp1mf2mf3",m);

const char *EastH=(char*)strE;
const char *WastH=(char*)strW;
const char *SMC=(char*)strMC;
const char *stCOVsv2sv2=(char*)strCOVsv2sv2;
const char *stCOVsv2sv4=(char*)strCOVsv2sv4;
const char *stCOVsv4sv2=(char*)strCOVsv4sv2;
const char *stCOVsv4sv4=(char*)strCOVsv4sv4;
const char *DifCOVsv2sv4=(char*)DiffCOVsv2sv4;
const char *stCOSp1=(char*)strCOSp1;
const char *stCOSp1f2=(char*)strCOSp1f2;
const char *stCOSp1f2mf3=(char*)strCOSp1f2mf3;
const char *stCOSp1mf2mf3=(char*)strCOSp1mf2mf3;
const char *stSINp1=(char*)strSINp1;
const char *stSINp1f2=(char*)strSINp1f2;
const char *stSINp1f2mf3=(char*)strSINp1f2mf3;
const char *stSINp1mf2mf3=(char*)strSINp1mf2mf3;
DiffSV2[m]=new TH1F(EastH,"Diffsv2",10000,-0.5,0.5);
DiffSV4[m]=new TH1F(WastH,"Diffsv4",10000,-0.5,0.5);
DiffMC[m]=new TH1F(SMC,"MC",10000,-1,1);
SV2_DiffSV2[m]=new TH1F(stCOVsv2sv2,"sv2sv2",10000,-1,1);
SV2_DiffSV4[m]=new TH1F(stCOVsv2sv4,"sv2sv4",10000,-1,1);
SV4_DiffSV2[m]=new TH1F(stCOVsv4sv2,"sv4sv2",10000,-1,1);
SV4_DiffSV4[m]=new TH1F(stCOVsv4sv4,"sv4sv4",10000,-1,1);
DiffSV2_DiffSV4[m]=new TH1F(DifCOVsv2sv4,"diffsv2sv4",10000,-1,1);
COSp1[m]=new TH1F(stCOSp1,"COSp1",10000,-2,2);
COSp1f2[m]=new TH1F(stCOSp1f2,"COSp1f2",10000,-1,1);
COSp1f2mf3[m]=new TH1F(stCOSp1f2mf3,"COSp1f2mf3",10000,-1,1);
COSp1mf2mf3[m]=new TH1F(stCOSp1mf2mf3,"COSp1mf2mf3",10000,-1,1);
SINp1[m]=new TH1F(stSINp1,"SINp1",10000,-2,2);
SINp1f2[m]=new TH1F(stSINp1f2,"SINp1f2",10000,-1,1);
SINp1f2mf3[m]=new TH1F(stSINp1f2mf3,"SINp1f2mf3",10000,-1,1);
SINp1mf2mf3[m]=new TH1F(stSINp1mf2mf3,"SINp1mf2mf3",10000,-1,1);
DiffSV2[m]->Sumw2();DiffSV4[m]->Sumw2();
DiffMC[m]->Sumw2();

DiffSV2[m]->StatOverflows(kTRUE);
SV2_DiffSV2[m]->StatOverflows(kTRUE);SV2_DiffSV4[m]->StatOverflows(kTRUE);
SV4_DiffSV2[m]->StatOverflows(kTRUE);SV4_DiffSV4[m]->StatOverflows(kTRUE);
DiffSV2_DiffSV4[m]->StatOverflows(kTRUE);}

SV2->StatOverflows(kTRUE); 
SV4->StatOverflows(kTRUE);
HMC->StatOverflows(kTRUE);
SV2->Sumw2();SV4->Sumw2();HMC->Sumw2();
}

bool MyClass::Fm(double pt,double min,double max)
{
bool boolv;
if(pt>min && pt<max){boolv=true;}
else {boolv=false;}
return boolv;
}

TComplex Sopr(TComplex Z){return TComplex::Conjugate(Z);}

void MyClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
int n=4;int t=0,m=0,M=0;int Npoi=0;
SV2->Sumw2();SV4->Sumw2();
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
        t+=1;
    if(jentry%1000==0) {cout << t<< " ivents were loaded, "<<t*100/nentries<<"% complete" <<endl;}

MQ2=0;MQ4=0;M=0;MCQ=0;
Q=TComplex(0,0);Q2=TComplex(0,0);ZQQQ=TComplex(0,0);
for(int s=0;s<NN;s++){
p[s]=TComplex(0,0);p2[s]=TComplex(0,0);mp[s]=0;
q[s]=TComplex(0,0);q2[s]=TComplex(0,0);mq[s]=0;
Diffsv2[s]=0;DiffMQ2[s]=0;
Diffsv4[s]=0;DiffMQ4[s]=0;
QMC[s]=0;}
hNpart->Fill(Nch);
if(Nch>180 && Nch<300){

 for (int i=0;i<Nch;i++)
    {   
        if(pt[i]>pt_min && pt[i]<pt_max){
        Q+=TComplex(cos(n*(phi[i])),sin(n*(phi[i])));
        Q2+=TComplex(cos(2*n*(phi[i])),sin(2*n*(phi[i])));
        MCQ+=cos(n*(phi[i]-psiRP));M+=1;}
    
        for(int m=0;m<NN;m++){
        if(pt[i]>pt_bin[m] && pt[i]<pt_bin[m+1]){
        mp[m]+=1;
        p2[m]+=TComplex(cos(2*n*(phi[i])),sin(2*n*(phi[i])));
        p[m]+=TComplex(cos(n*(phi[i])),sin(n*(phi[i])));
        QMC[m]+=(cos(n*(phi[i]-psiRP)));}}
        
        for(int m=0;m<NN;m++){
        if((pt[i]>pt_bin[m] && pt[i]<pt_bin[m+1]) && (pt[i]>pt_min && pt[i]<pt_max)){
        mq[m]+=1;
        q2[m]+=TComplex(cos(2*n*(phi[i])),sin(2*n*(phi[i])));
        q[m]+=TComplex(cos(n*(phi[i])),sin(n*(phi[i])));}}
    }

MQ2=M*(M-1);MQ4=M*(M-1)*(M-2)*(M-3);
ZQQQ=Q2*Sopr(Q)*Sopr(Q);
sv4=((Q*Q*Sopr(Q)*Sopr(Q)).Re()+(Q2*Sopr(Q2)).Re()-2*((ZQQQ).Re())-2*2*(M-2)*Q.Rho2()+2*M*(M-3))/MQ4;
sv2=(Q.Rho2()-M)/MQ2;
if(M!=0 && MQ2!=0 && MQ4!=0){
SV2->Fill(sv2,MQ2);
SV4->Fill(sv4,MQ4);
COSf1->Fill(Q.Re()/M,M);
SINf1->Fill(Q.Im()/M,M);
COSf1f2->Fill((Q*Q-Q2).Re()/(M*(M-1)),M*(M-1));
SINf1f2->Fill((Q*Q-Q2).Im()/(M*(M-1)),M*(M-1));
COSf1f2f3->Fill(((Q*Sopr(Q)*Sopr(Q)-Q*Sopr(Q2)).Re()-2*(M-1)*Sopr(Q).Re())/(M*(M-1)*(M-2)),M*(M-1)*(M-2));
SINf1f2f3->Fill(((Q*Sopr(Q)*Sopr(Q)-Q*Sopr(Q2)).Im()-2*(M-1)*Sopr(Q).Im())/(M*(M-1)*(M-2)),M*(M-1)*(M-2));

SV2_SV4->Fill(sv2*sv4,MQ2*MQ4);
HMC->Fill(MCQ/M);}

for(int s=0;s<NN;s++){
Diffsv2[s]=(p[s]*Sopr(Q)).Re()-mq[s];DiffMQ2[s]=mp[s]*M-mq[s];Diffsv2[s]=Diffsv2[s]/DiffMQ2[s];QMC[s]=QMC[s]/mp[s];

Diffsv4[s]=(p[s]*Q*Sopr(Q)*Sopr(Q)).Re()-(q2[s]*Sopr(Q)*Sopr(Q)).Re()-(p[s]*Q*Sopr(Q2)).Re()-2*M*(p[s]*Sopr(Q)).Re()-2*mq[s]*Q.Rho2()+7*(q[s]*Sopr(Q)).Re()-(Q*Sopr(q[s])).Re()+(q2[s]*Sopr(Q2)).Re()+2*(p[s]*Sopr(Q)).Re()+2*mq[s]*M-6*mq[s];

DiffMQ4[s]=(mp[s]*M-3*mq[s])*(M-1)*(M-2);Diffsv4[s]=Diffsv4[s]/DiffMQ4[s];

if(DiffMQ2[s]==0 || DiffMQ4[s]==0) break;
DiffSV2[s]->Fill(Diffsv2[s],DiffMQ2[s]);
DiffSV4[s]->Fill(Diffsv4[s],DiffMQ4[s]);
DiffMC[s]->Fill(QMC[s],mp[s]);
SV2_DiffSV2[s]->Fill(Diffsv2[s]*sv2,DiffMQ2[s]*MQ2);
SV2_DiffSV4[s]->Fill(Diffsv4[s]*sv2,DiffMQ4[s]*MQ2);
SV4_DiffSV2[s]->Fill(Diffsv2[s]*sv4,DiffMQ2[s]*MQ4);
SV4_DiffSV4[s]->Fill(Diffsv4[s]*sv4,DiffMQ4[s]*MQ4);
DiffSV2_DiffSV4[s]->Fill(Diffsv4[s]*Diffsv2[s],DiffMQ4[s]*DiffMQ2[s]);
COSp1[s]->Fill(p[s].Re()/mp[s],mp[s]);
COSp1f2[s]->Fill((p[s]*Q-q2[s]).Re()/(mp[s]*M-mq[s]),(mp[s]*M-mq[s]));
COSp1f2mf3[s]->Fill(((Q.Rho2()-M)*p[s].Re()-((q2[s]*Sopr(Q)).Re()+mq[s]*Q.Re()-2*q[s].Re()))/((mp[s]*M-2*mq[s])*(M-1)),((mp[s]*M-2*mq[s])*(M-1)));
COSp1mf2mf3[s]->Fill(((p[s]*Sopr(Q)*Sopr(Q)-p[s]*Sopr(Q2)).Re()-(2*mq[s]*Sopr(Q).Re()-2*Sopr(q[s]).Re()))/((mp[s]*M-2*mq[s])*(M-1)),((mp[s]*M-2*mq[s])*(M-1)));
SINp1[s]->Fill(p[s].Im()/mp[s],mp[s]);
SINp1f2[s]->Fill((p[s]*Q-q2[s]).Im()/(mp[s]*M-mq[s]),(mp[s]*M-mq[s]));
SINp1f2mf3[s]->Fill(((Q.Rho2()-M)*p[s].Im()-((q2[s]*Sopr(Q)).Im()+mq[s]*Q.Im()-2*q[s].Im()))/((mp[s]*M-2*mq[s])*(M-1)),((mp[s]*M-2*mq[s])*(M-1)));
SINp1mf2mf3[s]->Fill(((p[s]*Sopr(Q)*Sopr(Q)-p[s]*Sopr(Q2)).Im()-(2*mq[s]*Sopr(Q).Im()-2*Sopr(q[s]).Im()))/((mp[s]*M-2*mq[s])*(M-1)),((mp[s]*M-2*mq[s])*(M-1)));

                        }
 }
 }


sv2=SV2->GetMean();v2=pow(fabs(sv2),0.5);
sv4=SV4->GetMean();sv4=sv4-2*(sv2*sv2);v4=pow(fabs(sv4),0.25);
vMC=HMC->GetMean();
cout <<" v2{2} is "<<v2<<" v2{4} is "<<v4<<" v2{MC} is "<<vMC <<endl; 

//Дифференциальный поток
for(int m=0;m<NN;m++){
//DiffSV2[m]->Sumw2();DiffSV4[m]->Sumw2();
dn2[m]=DiffSV2[m]->GetMean();Diffv2[m]=dn2[m]/pow(fabs(sv2),0.5);
dn4[m]=DiffSV4[m]->GetMean()-2*dn2[m]*sv2;Diffv4[m]=-dn4[m]/pow(fabs(sv4),0.75);
binPt[m]=0.5*(pt_bin[m]+pt_bin[m+1]);
cout <<"Different. flow "<<" v2{2} is "<<Diffv2[m]<<", v2{4} is "<<Diffv4[m]<<" Pt "<<binPt[m]<<endl ;}
}

void MyClass::SaveData(const char *outfile)  
{
d_outfile = new TFile(outfile,"recreate");
SV2->Write();
SV4->Write();
HMC->Write();
SV2_SV4->Write();
COSf1->Write();
COSf1f2->Write();
COSf1f2f3->Write();
SINf1->Write();
SINf1f2->Write();
SINf1f2f3->Write();hNpart->Write();
for(int s=0;s<NN;s++){
DiffSV2[s]->Write();
DiffSV4[s]->Write();
DiffMC[s]->Write();
SV2_DiffSV2[s]->Write();SV2_DiffSV4[s]->Write();
SV4_DiffSV2[s]->Write();SV4_DiffSV4[s]->Write();
DiffSV2_DiffSV4[s]->Write();
COSp1[s]->Write();
COSp1f2[s]->Write();
COSp1f2mf3[s]->Write();
COSp1mf2mf3[s]->Write();
SINp1[s]->Write();
SINp1f2[s]->Write();
SINp1f2mf3[s]->Write();
SINp1mf2mf3[s]->Write();
}
d_outfile->Close();}             

