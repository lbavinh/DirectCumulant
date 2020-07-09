#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
double Qnx=0,Qny=0;
double Qnx2=0,Qny2=0,v2=0,Q=0;
double Qnx4=0,Qny4=0,v4=0;
int MQ2=0,Mq2=0,MQ4=0;
double Q2nx2=0,Q2ny2=0,Q2nx=0,Q2ny=0,a=0,b=0,c=0;
double sv4=0,sv2=0;
TFile *d_outfile;
TH1F *SV2=new TH1F("sv2","sv2",2000,-1,1);
TH1F *SV4=new TH1F("sv4","sv4",2000,-1,1);


double pt_bin[11]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0};int NN=11;
TH1F *DiffSV2[11];TH1F *DiffSV4[11];

/*double pt_bin[6]={0,0.4,0.8,1.2,1.6,2.0};int NN=6;
TH1F *DiffSV2[6];TH1F *DiffSV4[6];*/

/*double pt_bin[2]={0,2.0};int NN=1;
TH1F *DiffSV2[1];TH1F *DiffSV4[1];*/

double *binPt=new double[NN];
int *mp=new int[NN];
double *pnx=new double[NN];double *pny=new double[NN];
double *p2nx=new double[NN];double *p2ny=new double[NN];
double *dn2=new double[NN];double *dn4=new double[NN];
double *Diffv2=new double[NN]; double *Diffv4=new double[NN];
int *DiffMQ2=new int[NN];int *DiffMQ4=new int[NN];
double *Diffsv2=new double[NN]; double *Diffsv4=new double[NN];


char strE[20];char strW[20];

void MyClass::Book()
{
for(int m=0;m<NN;m++){
sprintf(strE,"%s%d","sv2Diff",m);
sprintf(strW,"%s%d","sv4Diff",m);
const char *EastH=(char*)strE;
const char *WastH=(char*)strW;
DiffSV2[m]=new TH1F(EastH,"Diffsv2",2000,-1,1);
DiffSV4[m]=new TH1F(WastH,"Diffsv4",2000,-1,1);
DiffSV2[m]->Sumw2();DiffSV4[m]->Sumw2();}
}

int MyClass::Fm(float pt)
{
int m=NN;
for(int i=0;i<NN;i++){if(pt>=pt_bin[i] && pt<pt_bin[i+1]){m=i;}}
return m;
}

void MyClass::Loop()
{
int n=2;int t=0,m=0;int Npoi=0;
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
Qnx=0;Qny=0;
Qnx2=0;Qny2=0;
Qnx4=0;Qny4=0;
Q2nx2=0;Q2ny2=0;Q2nx=0;Q2ny=0;
MQ2=0;MQ4=0;sv2=0;sv4=0;

for(int s=0;s<NN;s++){
pnx[s]=0;pny[s]=0;p2nx[s]=0;p2ny[s]=0;mp[s]=0;
Diffsv2[s]=0;DiffMQ2[s]=0;
Diffsv4[s]=0;DiffMQ4[s]=0;}

 for (int i=0;i<Nch;i++)
    {   Q+=cos(n*(phi[i]-psiRP));Q2nx+=cos(2*n*(phi[i]));Q2ny+=sin(2*n*(phi[i]));
        Qnx+=cos(n*(phi[i]));Qny+=sin(n*(phi[i]));
        m=Fm(pt[i]);mp[m]+=1;
        p2nx[m]+=cos(2*n*(phi[i]));p2ny[m]+=sin(2*n*(phi[i]));
        pnx[m]+=cos(n*(phi[i]));pny[m]+=sin(n*(phi[i]));
        for (int j=0;j<Nch;j++)
            {   Qnx2+=cos(n*(phi[i]-phi[j]));Qny2+=sin(n*(phi[i]-phi[j]));
                Q2nx2+=cos(2*n*(phi[i]-phi[j]));Q2ny2+=sin(2*n*(phi[i]-phi[j]));
                for (int k=0;k<Nch;k++)
                    {
                        for (int l=0;l<Nch;l++)
                            {Qnx4+=cos(n*(phi[i]+phi[j]-phi[k]-phi[l]));Qny4+=sin(n*(phi[i]+phi[j]-phi[k]-phi[l]));}
                    }
            }  
    }
Mq2+=Nch;
MQ2=Nch*(Nch-1);MQ4=Nch*(Nch-1)*(Nch-2)*(Nch-3);
sv4=(Qnx4+Q2nx2-2*(Q2nx*(Qnx*Qnx-Qny*Qny)+2*Q2ny*Qny*Qnx)-2*2*(Nch-2)*Qnx2+2*Nch*(Nch-3))/MQ4;
sv2=(Qnx2-Nch)/MQ2;

for(int i=0;i<MQ2;i++){SV2->Fill(sv2);}
for(int n=0;n<MQ4;n++){SV4->Fill(sv4);}

for(int s=0;s<NN;s++){
Diffsv2[s]=pnx[s]*Qnx+pny[s]*Qny-mp[s];DiffMQ2[s]=mp[s]*(Nch-1);Diffsv2[s]=Diffsv2[s]/DiffMQ2[s];

Diffsv4[s]=((pnx[s]*Qnx-pny[s]*Qny)*(Qnx*Qnx-Qny*Qny)+2*(pnx[s]*Qny+pny[s]*Qnx)*Qnx*Qny)-((p2nx[s])*(Qnx*Qnx-Qny*Qny)+2*(p2ny[s])*Qnx*Qny)-((pnx[s]*Qnx-pny[s]*Qny)*(Q2nx)+(pnx[s]*Qny+pny[s]*Qnx)*Q2ny)+((8-2*Nch)*(pnx[s]*Qnx+pny[s]*Qny))-2*mp[s]*(Qnx2)+((p2nx[s]*Q2nx+p2ny[s]*Q2ny))+2*mp[s]*Nch-6*mp[s];
DiffMQ4[s]=mp[s]*(Nch-1)*(Nch-2)*(Nch-3);Diffsv4[s]=Diffsv4[s]/DiffMQ4[s];

for(int r=0;r<DiffMQ2[s];r++){DiffSV2[s]->Fill(Diffsv2[s]);}
for(int c=0;c<DiffMQ4[s];c++){DiffSV4[s]->Fill(Diffsv4[s]);}
                        }
 } // end of event loop

SV2->Sumw2();SV4->Sumw2();
sv2=SV2->GetMean();v2=pow(fabs(sv2),0.5);
sv4=SV4->GetMean();sv4=sv4-2*(sv2*sv2);v4=pow(fabs(sv4),0.25);
Q=Q/Mq2;
cout <<"all number is "<<MQ2<<" v2{2} is "<<v2<<" v2{4} is "<<v4 <<"v2 from truth is "<<Q<<endl; 

//Дифференциальный поток
for(int m=0;m<NN-1;m++){
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
for(int s=0;s<NN-1;s++){
DiffSV2[s]->Write();
DiffSV4[s]->Write();}
d_outfile->Close();}             

