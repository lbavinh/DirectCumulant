#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>

long double Qx2=0,Qy2=0,korQx2=0,korQy2=0,MQ2=0,Mq2=0,v2=0,Q=0;
long double Qx4=0,Qy4=0,korQx4=0,korQy4=0,MQ4=0,Mq4=0,v4=0;
long double Q2x4=0,Q2y4=0;
long double cn2=0,cn4=0;


double pt_bin[11]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0};int NN=10;
double *DiffQx2=new double[NN];double *DiffQy2=new double[NN];double *DiffMQ2=new double[NN];double *DiffQy4=new double[NN];double *DiffQx4=new double[NN];
double *DiffMQ4=new double[NN];double *mq=new double[NN];double *mp=new double[NN];double *dn2=new double[NN];double *dn4=new double[NN];
double *binPt=new double[NN];
double *Diffv2=new double[NN]; double *Diffv4=new double[NN];
TFile *d_outfile;
void MyClass::Book()
{
double Qx=0,Qy=0,MQ=0,v2=0;
}

void MyClass::Loop()
{
    int n=2;int t=0;double ptmin=0.3,ptmax=0.7;
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) { // loop for events
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    t+=1;
    if(jentry%1000==0) {cout << t<< " ivents were loaded, "<<t*100/nentries<<"% complete" <<endl;}
    //Q вектора для интегрального потока
    for (int i=0;i<Nch;i++){ // loop for particles - nested loop method
        Q+=cos(n*(phi[i]-psiRP));
        for (int j=0;j<Nch;j++){
            if(i!=j){
                Qx2+=cos(n*(phi[i]-phi[j]));Qy2+=sin(n*(phi[i]-phi[j]));                
                for (int k=0;k<Nch;k++){
                    if(i!=k && j!=k){
                        for (int l=0;l<Nch;l++){
                            if( i!=l && j!=l && k!=l){
                                Qx4+=cos(n*(phi[i]+phi[j]-phi[k]-phi[l]));Qy4+=sin(n*(phi[i]+phi[j]-phi[k]-phi[l]));
                            }
                        }
                    }
                }
            }

        }  
    } // end of loop for particles
    //Кол-во событий
    Mq2+=Nch;
    MQ2+=Nch*(Nch-1);MQ4+=Nch*(Nch-1)*(Nch-2)*(Nch-3);

    // Q вектора для дифференциального потока
    for(int m=0;m<NN;m++){
        mp[m]=0;
        for (int i=0;i<Nch;i++){   
            if(pt[i]>pt_bin[m] && pt[i]<pt_bin[m+1]){ //Отборчастиц по Pt
                mp[m]+=1;
                for (int j=0;j<Nch;j++){   
                    if(i!=j){
                        DiffQx2[m]+=cos(n*(phi[i]-phi[j]));//DiffQy2[m]+=sin(n*(phi[i]-phi[j]));                
                        for (int k=0;k<Nch;k++){ 
                            if(i!=k && j!=k){
                                for (int l=0;l<Nch;l++){
                                    if( i!=l && j!=l && k!=l){
                                        DiffQx4[m]+=cos(n*(phi[i]+phi[j]-phi[k]-phi[l]));
                                        /*DiffQy4[m]+=sin(n*(phi[i]+phi[j]-phi[k]-phi[l]));*/
                                    }
                                }
                            }
                        }
                    }
                }
            } 
        }
    
    //расчет кол-ва событий
    DiffMQ2[m]+=mp[m]*Nch-mp[m];DiffMQ4[m]+=(mp[m]*Nch-3*mp[m])*(Nch-1)*(Nch-2);}
    //cout <<"Nch -"<<Nch<<", mp -"<<mp<<endl;


    /*if(jentry%3000==0) {cout <<"Qx2 -"<<Qx2<<", DiffQx2 -"<<DiffQx2<<endl;
    cout <<"Qx4 -"<<Qx4<<", DiffQx4 -"<<DiffQx4<<endl;
    cout <<"MQ2 -"<<MQ2<<", DiffMQ2 -"<<DiffMQ2<<endl;
    cout <<"MQ4 -"<<MQ4<<", DiffMQ4 -"<<DiffMQ4<<endl;}*/

    } // end of loop for events
    //korQx2=korQx2/Mq2;korQy2=korQy2/Mq2;v2=(Qx2-Mq2)/(MQ2)-korQx2*korQx2-korQy2*korQy2;v2=pow(fabs(v2),0.5);

    //Интегральный поток
    cn2=Qx2/(MQ2);v2=pow(fabs(cn2),0.5);
    cn4=Qx4/MQ4;cn4=cn4-2*(cn2)*(cn2);v4=pow(fabs(cn4),0.25);
    Q=Q/Mq2;
    cout <<"Rederence flow"<<" v2{2} is "<<v2<<", v2{4} is "<<v4 <<" v2 truth is "<<Q<<endl;
    //Дифференциальный поток
    for(int m=0;m<NN;m++){
    dn2[m]=DiffQx2[m]/(DiffMQ2[m]);Diffv2[m]=dn2[m]/pow(fabs(cn2),0.5);
    dn4[m]=DiffQx4[m]/DiffMQ4[m]-2*dn2[m]*dn2[m];Diffv4[m]=-dn4[m]/pow(fabs(cn4),0.75);
    binPt[m]=0.5*(pt_bin[m]+pt_bin[m+1]);
    cout <<"Different. flow "<<" v2{2} is "<<Diffv2[m]<<", v2{4} is "<<Diffv4[m]<<" Pt "<<binPt[m]<<endl ;}
    //cout <<"Different. flow "<<" dn4 is "<<dn4<<", cn4 is "<<cn4 ;  
}

void MyClass::SaveData(const char *outfile)  {
    d_outfile = new TFile(outfile,"recreate");
    d_outfile->cd();
    TGraph *grv2 = new TGraph(NN,binPt,Diffv2);
    grv2->SetName("v2_two");
    TGraph *grv4 = new TGraph(NN,binPt,Diffv4);
    grv4->SetName("v2_four");
    grv2->Write();grv4->Write();
    d_outfile->Close();
}             

