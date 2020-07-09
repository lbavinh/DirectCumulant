#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include "TComplex.h"
TComplex Q,Q2,ZQQQ;


int MQ2=0,Mq2=0,MQ4=0;
double sv4=0,sv2=0,v4,v2;

TFile *d_outfile;
TH1F *SV2=new TH1F("sv2","sv2",2000,-1,1);
TH1F *SV4=new TH1F("sv4","sv4",2000,-1,1);


double pt_bin[11]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0};int NN=11;
TH1F *DiffSV2[11];TH1F *DiffSV4[11];

TComplex p[11],p2[11];

/*double pt_bin[6]={0,0.4,0.8,1.2,1.6,2.0};int NN=6;
TH1F *DiffSV2[6];TH1F *DiffSV4[6];*/

/*double pt_bin[2]={0,2.0};int NN=1;
TH1F *DiffSV2[1];TH1F *DiffSV4[1];*/

double *binPt=new double[NN];
int *mp=new int[NN];
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
    if(jentry%100==0) {cout << t<< " ivents were loaded, "<<t*100/nentries<<"% complete" <<endl;}

MQ2=0;MQ4=0;sv2=0;sv4=0;
Q=TComplex(0,0);Q2=TComplex(0,0);ZQQQ=TComplex(0,0);
for(int s=0;s<NN;s++){
p[s]=TComplex(0,0);p2[s]=TComplex(0,0);mp[s]=0;
Diffsv2[s]=0;DiffMQ2[s]=0;
Diffsv4[s]=0;DiffMQ4[s]=0;}

 for (int i=0;i<Nch;i++)
    {   Q+=TComplex(cos(n*(phi[i])),sin(n*(phi[i])));
        Q2+=TComplex(cos(2*n*(phi[i])),sin(2*n*(phi[i])));

        m=Fm(pt[i]);mp[m]+=1;
        p2[m]+=TComplex(cos(2*n*(phi[i])),sin(2*n*(phi[i])));
        p[m]+=TComplex(cos(n*(phi[i])),sin(n*(phi[i])));
    }

MQ2=Nch*(Nch-1);MQ4=Nch*(Nch-1)*(Nch-2)*(Nch-3);
ZQQQ=Q2*Sopr(Q)*Sopr(Q);
sv4=(Q.Rho2()*Q.Rho2()+Q2.Rho2()-2*((Q2*Sopr(Q)*Sopr(Q)).Re())-2*2*(Nch-2)*Q.Rho2()+2*Nch*(Nch-3))/MQ4;
sv2=(Q.Rho2()-Nch)/MQ2;

SV2->Fill(sv2,MQ2);
SV4->Fill(sv4,MQ4);

for(int s=0;s<NN;s++){
Diffsv2[s]=(p[s]*Sopr(Q)).Re()-mp[s];DiffMQ2[s]=mp[s]*(Nch-1);Diffsv2[s]=Diffsv2[s]/DiffMQ2[s];

Diffsv4[s]=(p[s]*Q*Sopr(Q)*Sopr(Q)).Re()-(p2[s]*Sopr(Q)*Sopr(Q)).Re()-(p[s]*Q*Sopr(Q2)).Re()-2*Nch*(p[s]*Sopr(Q)).Re()-2*mp[s]*Q.Rho2()+7*(p[s]*Sopr(Q)).Re()-(Q*Sopr(p[s])).Re()+(p2[s]*Sopr(Q2)).Re()+2*(p[s]*Sopr(Q)).Re()+2*mp[s]*Nch-6*mp[s];

DiffMQ4[s]=mp[s]*(Nch-1)*(Nch-2)*(Nch-3);Diffsv4[s]=Diffsv4[s]/DiffMQ4[s];

DiffSV2[s]->Fill(Diffsv2[s],DiffMQ2[s]);
DiffSV4[s]->Fill(Diffsv4[s],DiffMQ4[s]);
                        }
 }

SV2->Sumw2();//SV4->Sumw2();
sv2=SV2->GetMean();v2=pow(fabs(sv2),0.5);
sv4=SV4->GetMean();sv4=sv4-2*(sv2*sv2);v4=pow(fabs(sv4),0.25);
//=Q/Mq2;
cout <<" v2{2} is "<<v2<<" v2{4} is "<<v4 <<endl; 

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

