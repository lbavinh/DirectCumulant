#include <cstring>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"

double v1=0.05;
double v2=0.15;

double V2(double pt)
{//return v2*(exp(2*pt)-1)/(exp(2*pt)+1);
return 0.1*pt;
}

double V1(double pt)
{//return v1*(exp(2*pt)-1)/(exp(2*pt)+1);
return v1;
}

void generator(const char *file_name="~/fileTEST.root", int run0=1000)
{
TFile *f0=new TFile (file_name,"recreate");
f0->cd();


//double v3=0.15;
float massLambda	= 1.115;
float T			= 0.26;
float ptMax			= 5.0;

cout << "Start0" << endl;
Int_t event;
Int_t Nch;
Float_t psi_RP;
Float_t phi[100];
Float_t dPHI[100];
Float_t moment[100];

TRandom *nLambda = new TRandom();

TTree *tree = new TTree("tree","My Tree"); 

tree->Branch("EVENT",&event,"event/I");
tree->Branch("Nch",&Nch,"Nch/I");
tree->Branch("psiRP",&psi_RP,"psi_RP/F");

tree->Branch("phi",&phi,"phi[Nch]/F");
tree->Branch("dPHI",&dPHI,"dPHI[Nch]/F");
tree->Branch("pt",&moment,"moment[Nch]/F");

Double_t Cp=3.1415926535;

cout << "Branches were created" << endl;

// Reaction plane angle distribution: flat
TF1 *psiRP_dist = new TF1("psiRP_dist","1./(2.*[0])", 0, 2.*Cp);
psiRP_dist->FixParameter(0,Cp);

// Lambda phi distribution: flat
TF1 *phi_dist = new TF1("phi_dist","1./(2.*[0])*(1+2.*[1]*cos(x-[3])+2.*[2]*cos(2.*(x-[3])))", 0, 2.*Cp);
phi_dist->FixParameter(0, Cp);
//phi_dist->FixParameter(1, v1);
//phi_dist->FixParameter(2, v2);
//phi_dist->FixParameter(3, v3);
//Lambda p_t distribution: A*p_t*exp(-m_T/T)

/*TF1 *momentdist = new TF1("pt_dist","[0]/(2.*[3])*x*exp(-sqrt(x^2+[2]^2)/[1])", 0., ptMax);
momentdist->FixParameter(0, 50.);
momentdist->FixParameter(1, T);
momentdist->FixParameter(2, massLambda);
momentdist->FixParameter(3, Cp);
*/
TF1 *momentdist = new TF1("momentdist","1/[0]", 0., 2);
momentdist->FixParameter(0, 2);
cout << "Start" << endl;

for(int i=0;i<run0;i++)
    {
    if (i%100==0){cout << i<< " ivents were simulated,the process is "<<i*100/run0<<"% complete" <<endl;}
    Nch=30;//(int)nLambda->Poisson(20);
    psi_RP=psiRP_dist->GetRandom();
        
    for(int j=0;j<Nch;j++)
        {
        moment[j]=momentdist->GetRandom();
        phi_dist->FixParameter(1,V1(moment[j]));
        phi_dist->FixParameter(2,V2(moment[j]));
        phi_dist->FixParameter(3,psi_RP);
        phi[j]=phi_dist->GetRandom();//if(phi[j]<0){phi[j]=phi[j]+2*Cp;}
        
       dPHI[j]=phi[j]-psi_RP;if(dPHI[j]<0){dPHI[j]=dPHI[j]+2*Cp;}
        }

    event=i;
    tree->Fill();
    }
tree->Write();
f0->Close();
cout << "DONE generator" << endl;

}
