#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>


long double Qnx=0,Qny=0;
long double Qnx2=0,Qny2=0,MQ2=0,Mq2=0,v2=0,Q=0;

long double Qnx4=0,Qny4=0,MQ4=0,Mq4=0,v4=0;
long double Q2nx2=0,Q2ny2=0,Q2nx=0,Q2ny=0;
long double sv4=0,sv2=0,Difsv2=0;
TFile *d_outfile;

double pt_bin[11]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0};int NN=10;
double *binPt=new double[NN];
long double *mp=new long double[NN];
long double *pnx=new long double[NN];long double *pny=new long double[NN];
long double *p2nx=new long double[NN];long double *p2ny=new long double[NN];
long double *dn2=new long double[NN];long double *dn4=new long double[NN];
long double *Diffv2=new long double[NN]; long double *Diffv4=new long double[NN];
long double *DiffMQ2=new long double[NN];long double *DiffMQ4=new long double[NN];
long double *Diffsv2=new long double[NN]; long double *Diffsv4=new long double[NN];

void MyClass::Book()
{
double Qx=0,Qy=0,MQ=0,v2=0;
}



int MyClass::Fm(float pt)
{
int m=-999;
for(int i=0;i<NN;i++){if(pt>=pt_bin[i] && pt<=pt_bin[i+1]){m=i;}}
return m;
}

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

    for(int s=0;s<NN;s++){
    Diffsv2[s]=0;DiffMQ2[s]=0;
    Diffsv4[s]=0;DiffMQ4[s]=0;}

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
for(int s=0;s<NN;s++){
pnx[s]=0;pny[s]=0;p2nx[s]=0;p2ny[s]=0;mp[s]=0;}
 
 for (int i=0;i<Nch;i++)
    {   Q+=cos(n*(phi[i]-psiRP));
        Q2nx+=cos(2*n*(phi[i]));Q2ny+=sin(2*n*(phi[i]));
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
MQ2+=Nch*(Nch-1);MQ4+=Nch*(Nch-1)*(Nch-2)*(Nch-3);
sv4+=Qnx4+Q2nx2-2*(Q2nx*(Qnx*Qnx-Qny*Qny)+2*Q2ny*Qny*Qnx)-2*2*(Nch-2)*Qnx2+2*Nch*(Nch-3);
sv2+=Qnx2-Nch;

for(int s=0;s<NN;s++){
Diffsv2[s]+=pnx[s]*Qnx+pny[s]*Qny-mp[s];
DiffMQ2[s]+=mp[s]*(Nch-1);


Diffsv4[s]+=((pnx[s]*Qnx-pny[s]*Qny)*(Qnx*Qnx-Qny*Qny)+2*(pnx[s]*Qny+pny[s]*Qnx)*Qnx*Qny)-((p2nx[s])*(Qnx*Qnx-Qny*Qny)+2*(p2ny[s])*Qnx*Qny)-((pnx[s]*Qnx-pny[s]*Qny)*(Q2nx)+(pnx[s]*Qny+pny[s]*Qnx)*Q2ny)+((8-2*Nch)*(pnx[s]*Qnx+pny[s]*Qny))-2*mp[s]*(Qnx2)+((p2nx[s]*Q2nx+p2ny[s]*Q2ny))+2*mp[s]*Nch-6*mp[s];

DiffMQ4[s]+=mp[s]*(Nch-1)*(Nch-2)*(Nch-3);
}
 } // end of loop for event

sv2=sv2/(MQ2);v2=pow(fabs(sv2),0.5);
sv4=sv4/(MQ4);sv4=sv4-2*(sv2*sv2);v4=pow(fabs(sv4),0.25);
Q=Q/Mq2;
cout <<"all number is "<<MQ2<<" v2{2} is "<<sv2<<" v2{4} is "<<sv4 <<"v2 from truth is "<<Q; 

//Дифференциальный поток
for(int m=0;m<NN;m++){
dn2[m]=Diffsv2[m]/(DiffMQ2[m]);
Diffv2[m]=dn2[m]/pow(fabs(sv2),0.5);
dn4[m]=Diffsv4[m]/DiffMQ4[m]-2*dn2[m]*sv2;Diffv4[m]=-dn4[m]/pow(fabs(sv4),0.75);
binPt[m]=0.5*(pt_bin[m]+pt_bin[m+1]);
cout <<"Different. flow "<<" v2{2} is "<<Diffv2[m]<<", v2{4} is "<<Diffv4[m]<<" Pt "<<binPt[m]<<endl ;}
}

void MyClass::SaveData(const char *outfile)  
{
d_outfile = new TFile(outfile,"recreate");
d_outfile->Close();}             

