#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

#ifndef __CINT__  
#include "TROOT.h"
#include "TFile.h" 
#include "TChain.h"
#include "TMath.h"
#include "TH1.h" 
#include "TH2.h"   
#include "TH3.h"
#include "TF1.h" 
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TVector2.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TComplex.h"
#endif
 
#ifndef RPPAR_H_
#include "RpPar.h"
#endif

using namespace HRP;

const int  MAX=10000;
const int  NETAB=12;
const int  NHAR=4;
const int  NPT=4;


const double PI = acos(-1.0);
const double PI2 = 2*acos(-1.0);

Double_t CalCor22(TComplex Q2, Double_t M){
  
  Double_t nComb2  = M * (M-1);
  
  Double_t Q2Square = Q2.Rho2();
  
  Double_t coor22   = Q2Square - M;                                          
  
  return coor22/nComb2;
}

Double_t CalCor24(TComplex Q2, TComplex Q4, Double_t M){ 

  Double_t nComb4  = M * (M-1) * (M-2) * (M-3);

  TComplex Q2Star   = TComplex::Conjugate(Q2);
  TComplex Q4Star   = TComplex::Conjugate(Q4);
  
  Double_t Q2Square = Q2.Rho2();
  Double_t Q4Square = Q4.Rho2();
  Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

  //Double_t coor22   = Q2Square - M;
  Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2*ReQQQ
                     - 4*(M-2)*Q2Square + 2*M*(M-3));

  return coor24/nComb4;
}


Double_t CalCor22Two(TComplex Q2TwoA, TComplex Q2TwoB, double nTwoA, double nTwoB){
  if(nTwoA<=1||nTwoB<=1) return -999.0;
 
  TComplex Q2TwoBStar   = TComplex::Conjugate(Q2TwoB);
  
  Double_t c22Two    = (Q2TwoA*Q2TwoBStar).Re()/nTwoA/nTwoB;
  
  return c22Two;
}


Double_t CalCor24Two(TComplex Q2TwoA, TComplex Q2TwoB, TComplex Q4TwoA, TComplex Q4TwoB, double nTwoA, double nTwoB){
  if(nTwoA<=1||nTwoB<=1) return -999.0;
  
  TComplex Q2TwoAStar   = TComplex::Conjugate(Q2TwoA);
  TComplex Q4TwoAStar   = TComplex::Conjugate(Q4TwoA);
      
  TComplex Q2TwoBStar   = TComplex::Conjugate(Q2TwoB);
  TComplex Q4TwoBStar   = TComplex::Conjugate(Q4TwoB);


  //Double_t c22Two    = (Q2TwoA*Q2TwoBStar).Re()/nTwoA/nTwoB;

  Double_t c24Two   = ((Q2TwoA*Q2TwoA - Q4TwoA)*TComplex::Conjugate(Q2TwoB*Q2TwoB - Q4TwoB)).Re();
  c24Two = c24Two/nTwoA/(nTwoA-1)/nTwoB/(nTwoB-1);
  
  return c24Two;
}

int calcenttpc(string energy, float ncut){
  if(energy=="pp200GeV"){
    return 0;
  }
  else if(energy=="HeAu200GeV"){
    if(ncut>=21) return 0;
    else if(ncut>=15) return 1;
    else if(ncut>=9) return 2;
    else if(ncut>=5) return 3;
    else return 4;
  }
  else if(energy=="dAu200GeV"){
    if(ncut>=36.5) return 0;//0-5%
    else if(ncut>=31.5) return 1;//5-10%
    else if(ncut>=25.5) return 2;//10-20%
    else if(ncut>=16.5) return 3;//20-40%
    else if(ncut>=10.5) return 4;//40-60%.
    else return 5;//60-100%
  }
  else if(energy=="pAu200GeV"){
    if(ncut>=23.5) return 0;//0-5%
    else if(ncut>=19.5) return 1;//5-10%
    else if(ncut>=15.5) return 2;//10-20%
    else if(ncut>=10.5) return 3;//20-40%
    else if(ncut>=7.5) return 4;//40-60%.
    else return 5;//60-100%
  }
  
  return -999;
}

int calcentbbc(string energy, float bbcq){
  if(energy=="pp200GeV") return 0;
  else if(energy=="dAu200GeV"){
    if(bbcq>=41.5) return 0;//0-5%
    else if(bbcq>=36.5) return 1;//5-10%
    else if(bbcq>=28.5) return 2;//10-20%
    else if(bbcq>=17.5) return 3;//20-40%
    else if(bbcq>=9.5) return 4;//40-60%.
    else return 5;//60-100%
  }
  else if(energy=="pAu200GeV"){
    if(bbcq>=26.5) return 0;//0-5%
    else if(bbcq>=22.5) return 1;//5-10%
    else if(bbcq>=18.5) return 2;//10-20%
    else if(bbcq>=11.5) return 3;//20-40%
    else if(bbcq>=7.5) return 4;//40-60%.
    else return 5;//60-100%
  }
  return -9999;
}

inline bool exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main (){
  int run;
  string system;
  cin>>run;
  cin>>system;
  int version = 126;
  
  int nseg=2000;
  int nrun = 10;
  
  if(system=="OO5.02TeV") nseg=400;
  if(version==125){
    if(system=="ArAr200GeV") nseg=1000;
    if(system=="OO5.02TeV"||system=="OO2.76TeV") nrun=5;
  }
  
  if(version==126){
    //if(system=="ArAr200GeV"||system=="pp200GeV"||system=="pp5.02TeV"||
    //system=="pAu200GeV"||system=="dAu200GeV") nrun=10;
    if(system=="AlAl200GeV"||system=="CC200GeV"||system=="OO200GeV"||system=="He4Au200GeV"||system=="OO5.02TeV"||system=="OO2.76TeV") nrun=5;
  }

  cout<<"run & system: "<<run<<" "<<system<<endl;
  //Declaration of leaves types
  Int_t           ieve;
  Int_t           jeve;
  Float_t         bimp;
  Int_t           eid[6];
  UInt_t          nTrk;
  Int_t           trkID[MAX];
  Float_t         trkPx[MAX];
  Float_t         trkPy[MAX];
  Float_t         trkPz[MAX];
  Int_t           npart;
  Float_t         x_part[394];
  Float_t         y_part[394];
  Int_t           id_part[394];
  Int_t           st_part[394];
  int bad=0, dup=0;

  //int nF,nB;

  //float    mpt[NPT][NETAB];//0.1-2,
  //float    mpt2[NPT][NETAB];//0.1-2,
  //double   mpt2T[NPT][NETAB];//0.1-2,
  //UShort_t M[NPT][NETAB];
  float    re[3][NHAR];//npart, nA, nB
  float    rang[3][NHAR];

  stringstream name;

  TH1F *hnpart = new TH1F("hnpart", "hnpart", 100, 0, 100);
  TH1F *himpdis = new TH1F("himpdis", "himpdis", 300, 0, 15);
  
  TH2F *hnpartimpdis = new TH2F("hnpartimpdis", "hnpartimpdis", 300, 0, 15, 100, 0, 100);
  
  TH2F *hnpartnch2dis = new TH2F("hnpartnch2dis", "hnpartnch2dis", 100, 0, 100, 2000, 0, 2000);
  
  TH2F *hnchdis = new TH2F("hnchdis", "hnchdis", 2000, 0, 2000, 2000, 0, 2000);

  TProfile *hc22dis =  new TProfile("hc22dis", "hc22dis", 2000, 0, 2000, -1.2, 1.2);
  TProfile *hc24dis =  new TProfile("hc24dis", "hc24dis", 2000, 0, 2000, -1.2, 1.2);
  
  TProfile *Jc22Twodis = new TProfile("Jc22Twodis", "Jc22Twodis", 2000, 0, 2000, -1.2, 1.2);
  TProfile *Jc24Twodis = new TProfile("Jc24Twodis", "Jc24Twodis", 2000, 0, 2000, -1.2, 1.2);
  
  TProfile *hc1dis =  new TProfile("hc1dis", "hc1dis", 2000, 0, 2000, -1.2, 1.2);
  TProfile *hc2dis =  new TProfile("hc2dis", "hc2dis", 2000, 0, 2000, -1.2, 1.2);
  TProfile *hc3dis =  new TProfile("hc3dis", "hc3dis", 2000, 0, 2000, -1.2, 1.2);

  TProfile *hc1dis2 =  new TProfile("hc1dis2", "hc1dis2", 2000, 0, 2000, -1.2, 1.2);
  TProfile *hc2dis2 =  new TProfile("hc2dis2", "hc2dis2", 2000, 0, 2000, -1.2, 1.2);
  TProfile *hc3dis2 =  new TProfile("hc3dis2", "hc3dis2", 2000, 0, 2000, -1.2, 1.2);

  TProfile *hc1dis3 =  new TProfile("hc1dis3", "hc1dis3", 100, 0, 100, -1.2, 1.2);
  TProfile *hc2dis3 =  new TProfile("hc2dis3", "hc2dis3", 100, 0, 100, -1.2, 1.2);
  TProfile *hc3dis3 =  new TProfile("hc3dis3", "hc3dis3", 100, 0, 100, -1.2, 1.2);


  TProfile *h15c1dis =  new TProfile("h15c1dis", "h15c1dis", 2000, 0, 2000, -1.2, 1.2);
  TProfile *h15c2dis =  new TProfile("h15c2dis", "h15c2dis", 2000, 0, 2000, -1.2, 1.2);
  TProfile *h15c3dis =  new TProfile("h15c3dis", "h15c3dis", 2000, 0, 2000, -1.2, 1.2);
  
  TProfile *h15c1dis2 =  new TProfile("h15c1dis2", "h15c1dis2", 2000, 0, 2000, -1.2, 1.2);
  TProfile *h15c2dis2 =  new TProfile("h15c2dis2", "h15c2dis2", 2000, 0, 2000, -1.2, 1.2);
  TProfile *h15c3dis2 =  new TProfile("h15c3dis2", "h15c3dis2", 2000, 0, 2000, -1.2, 1.2);

  TProfile *h15c1dis3 =  new TProfile("h15c1dis3", "h15c1dis3", 100, 0, 100, -1.2, 1.2);
  TProfile *h15c2dis3 =  new TProfile("h15c2dis3", "h15c2dis3", 100, 0, 100, -1.2, 1.2);
  TProfile *h15c3dis3 =  new TProfile("h15c3dis3", "h15c3dis3", 100, 0, 100, -1.2, 1.2);


  
  TProfile *hc2ptdis2 =  new TProfile("hc2ptdis2", "hc2ptdis2", 40, 0, 4.0, -1.2, 1.2);
  TProfile *hc3ptdis2 =  new TProfile("hc3ptdis2", "hc3ptdis2", 40, 0, 4.0, -1.2, 1.2);

  TProfile *h15c2ptdis2 =  new TProfile("h15c2ptdis2", "h15c2ptdis2", 40, 0, 4.0, -1.2, 1.2);
  TProfile *h15c3ptdis2 =  new TProfile("h15c3ptdis2", "h15c3ptdis2", 40, 0, 4.0, -1.2, 1.2);

  
  TProfile *hmeanptdis2 =  new TProfile("hmeanptdis2", "hmeanptdis2", 2000, 0, 2000, 0, 4.0);

  TProfile *rpcor[NHAR][8];
  TProfile *rpcor2[NHAR][8];
  TProfile *rpcor3[NHAR][8];

  for(int ihar=0; ihar<2; ihar++){
    for(int idet=0; idet<8; idet++){
      name<<"rpcor_"<<ihar+2<<"_"<<idet;
      rpcor[ihar][idet] = new TProfile(name.str().c_str(), name.str().c_str(), NHMUL, 0, NHMUL, -1.1, 1.1);
      name.str("");

      name<<"rpcor2_"<<ihar+2<<"_"<<idet;
      rpcor2[ihar][idet] = new TProfile(name.str().c_str(), name.str().c_str(), NHMUL, 0, NHMUL, -1.1, 1.1);
      name.str("");

      name<<"rpcor3_"<<ihar+2<<"_"<<idet;
      rpcor3[ihar][idet] = new TProfile(name.str().c_str(), name.str().c_str(), NHMUL, 0, NHMUL, -1.1, 1.1);
      name.str("");
    }
  }

  TProfile *hvnimpdis[NHAR];
  TProfile *hvnpartdis[NHAR];
  TProfile *hvnnchdis[NHAR];
  TProfile *hvnnch2dis[NHAR];

  TProfile *heccnpartdis[NHAR];
  TProfile *heccimpdis[NHAR];
  TProfile *heccnchdis[NHAR];
  TProfile *heccnch2dis[NHAR];

  TProfile *hvnptdis[NHAR][NHMUL];
  TProfile *hvnptdis2[NHAR][NHMUL];

  for(int ihar=0; ihar<NHAR; ihar++){
    name<<"hvnimpdis_"<<ihar;
    hvnimpdis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 10, 0, 6.0, -1.1, 1.1);
    name.str("");

    name<<"hvnpartdis_"<<ihar;
    hvnpartdis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 100, 0, 100, -1.1, 1.1);
    name.str("");

    name<<"hvnnchdis_"<<ihar;
    hvnnchdis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 2000, 0, 2000, -1.1, 1.1);
    name.str("");

    name<<"hvnnch2dis_"<<ihar;
    hvnnch2dis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 2000, 0, 2000, -1.1, 1.1);
    name.str("");

    name<<"heccnpartdis_"<<ihar;
    heccnpartdis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 100, 0, 100, -1.1, 1.1);
    name.str("");

    name<<"heccimpdis_"<<ihar;
    heccimpdis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 300, 0, 15, -1.1, 1.1);
    name.str("");

    name<<"heccnchdis_"<<ihar;
    heccnchdis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 2000, 0, 2000, -1.1, 1.1);
    name.str("");

    name<<"heccnch2dis_"<<ihar;
    heccnch2dis[ihar] = new TProfile(name.str().c_str(), name.str().c_str(), 2000, 0, 2000, -1.1, 1.1);
    name.str("");

    for(int icent=0; icent<NHMUL; icent++){
      name<<"hvnptdis_"<<ihar<<"_"<<icent;
      hvnptdis[ihar][icent] = new TProfile(name.str().c_str(), name.str().c_str(), 60, 0, 6.0, -1.1, 1.1);
      name.str("");

      name<<"hvnptdis2_"<<ihar<<"_"<<icent;
      hvnptdis2[ihar][icent] = new TProfile(name.str().c_str(), name.str().c_str(), 60, 0, 6.0, -1.1, 1.1);
      name.str("");
    }
  }


  TH1D *hptdis = new TH1D("hptdis", "hptdis", 40, 0, 4.0);
  TH1D *hphidis = new TH1D("hphidis", "hphidis", 100, 0, PI2);
  TH1D *hetadis = new TH1D("hetadis", "hetadis", 120, -6.0, 6.0);

  TH1D *htpcdis = new TH1D("htpcdis", "htpcdis", 200,  0, 200);
  TH1D *hbbcdis = new TH1D("hbbcdis", "hbbcdis", 200,  0, 200);
  
  TH1D *hptmultpc[NHMUL];
  TH1D *hptmulbbc[NHMUL];

  for(int icent=0; icent<NHMUL; icent++){
    name<<"hptmultpc_"<<icent;
    hptmultpc[icent] = new TH1D(name.str().c_str(), name.str().c_str(), 30, 0, 3.0);
    name.str("");

    name<<"hptmulbbc_"<<icent;
    hptmulbbc[icent] = new TH1D(name.str().c_str(), name.str().c_str(), 30, 0, 3.0);
    name.str("");
  }

  TH2D* hforedis2d[NHMUL];
  TH2D* hbackdis2d[NHMUL];
  
  TH2D* hforedis2dpt[NHMUL][ptbin];
  TH2D* hbackdis2dpt[NHMUL][ptbin];

  
  for(int icent=0; icent<NHMUL; icent++){
    name<<"hforedis2d_"<<icent;
    hforedis2d[icent] = new TH2D(name.str().c_str(),name.str().c_str(),40, 0, 2.0, 24, -0.5*PI, 1.5*PI);
    name.str("");
    
    name<<"hbackdis2d_"<<icent;
    hbackdis2d[icent] = new TH2D(name.str().c_str(),name.str().c_str(),40, 0, 2.0, 24, -0.5*PI, 1.5*PI);
    name.str("");

    for(int ipt=0; ipt<ptbin; ipt++){
      name<<"hforedis2dpt_"<<icent<<"_"<<ipt;      
      hforedis2dpt[icent][ipt] = new TH2D(name.str().c_str(),name.str().c_str(),40, 0, 2.0, 24, -0.5*PI, 1.5*PI);
      name.str("");
        
      name<<"hbackdis2dpt_"<<icent<<"_"<<ipt;
      hbackdis2dpt[icent][ipt] = new TH2D(name.str().c_str(),name.str().c_str(),40, 0, 2.0, 24, -0.5*PI, 1.5*PI);
      name.str("");

    }
  }

  cout<<"end of histo definition"<<endl;
  
  TChain* ch = new TChain("tt");
  for(int irun=run*nrun; irun<(run+1)*nrun; irun++){
  
    for(int j=0; j<10; j++){   
  
      if(version==125) name<<"/phenix/hhj/shengli/ampt2/"<<system<<"/"<<irun<<"/ana_"<<j<<"/ampt.root";
      else if(version==126) name<<"/gpfs01/star/pwg/zhchen/AMPT/shenglisample/ampt3/"<<system<<"/"<<irun<<"/ana_"<<j<<"/ampt.root";
      
      cout<<name.str()<<endl;
      if(exists(name.str())){
        ch->Add(name.str().c_str());
      }
      name.str("");
    }
  }
  // Set branch addresses.
  ch->SetBranchAddress("ieve",&ieve);
  ch->SetBranchAddress("jeve",&jeve);
  ch->SetBranchAddress("bimp",&bimp);
  ch->SetBranchAddress("eid",eid);
 
  ch->SetBranchAddress("ntrk",&nTrk);
  ch->SetBranchAddress("id",trkID);
  ch->SetBranchAddress("px",trkPx);
  ch->SetBranchAddress("py",trkPy);
  ch->SetBranchAddress("pz",trkPz);
  ch->SetBranchAddress("npart",&npart);
  ch->SetBranchAddress("x_part",x_part);
  ch->SetBranchAddress("y_part",y_part);
  ch->SetBranchAddress("id_part",id_part);
  ch->SetBranchAddress("st_part",st_part);
  //ch->SetBranchAddress("bad",&bad);
  //ch->SetBranchAddress("dup",&dup);

  /*
  sprintf(name,"ampt_mpt_%d.root",wh);

  TFile*fout = new TFile(name,"recreate");

  TTree *tout = new TTree("tree","tree");

  tout->Branch("bimp" , &bimp, "bimp/F"  );
  tout->Branch("nF"   , &nF  , "nF/I"    );
  tout->Branch("nB"   , &nB  , "nB/I"    );

  tout->Branch("re"   , &re   , "re[3][4]/F");
  tout->Branch("rang" , &rang , "rang[3][4]/F");

  tout->Branch("mpt"   , &mpt , "mpt[4][12]/F");
  tout->Branch("mpt2"  , &mpt2 , "mpt2[4][12]/F");
  tout->Branch("m"     , &M   , "m[4][12]/s");

  tout->Branch("bad", &bad, "bad/I");
  tout->Branch("dup", &dup, "dup/I");
  */

  int Nevt = ch->GetEntries();

  cout<<Nevt<<endl;

  //Nevt=10000;
  double x,y, xx[3][500],yy[3][500],xm[3],ym[3];      int Np[3];  
  for (int iev=0; iev<Nevt;iev++) {
    ch->GetEntry(iev);
    if(iev%nseg==0) cout<<iev<<" "<<ieve<<endl;

    if(iev%nseg!=(ieve-1)) continue;//kick out the event duplication 
    //if(bimp<0.05) continue;

    himpdis->Fill(bimp);
    
   
    //hnpart->Fill(npart);

    memset(re,0,sizeof(re));
    memset(rang,0,sizeof(rang));
    
    //calculate eccentricities
    int np=0,nt=0,tot=0;
    xm[0]=xm[1]=xm[2]=0;
    ym[0]=ym[1]=ym[2]=0;
    for(int i=0; i<npart; i++){
      if(st_part[i]!=3) continue;
      x = x_part[i];
      y = y_part[i];
      xx[0][tot]=x;
      yy[0][tot]=y;
      tot++;      
      if(id_part[i]>0){
	xx[1][np]= x;
	yy[1][np]= y;
	xm[1]+=x;
	ym[1]+=y;
	np++;
      }else{
	xx[2][nt]=x;
	yy[2][nt]=y;
	xm[2]+=x;
	ym[2]+=y;
	nt++;
      }
    }
    Np[1] = np;    Np[2] = nt; Np[0]=tot;
    xm[0] = xm[1]+xm[2];
    ym[0] = ym[1]+ym[2];
    for(int it=0;it<3;it++){
      xm[it]/=Np[it];
      ym[it]/=Np[it];
    }    
    double frcos[3][NHAR],frsin[3][NHAR],fr[3][NHAR];
    for(int it=0;it<3;it++){
      for(int ihar=0;ihar<NHAR;ihar++){
	frcos[it][ihar]=0;
	frsin[it][ihar]=0;
	fr[it][ihar]=0;
      }
      for(int ip=0;ip<Np[it];ip++){//npart
	double rr = sqrt(pow(xx[it][ip]-xm[it],2)+pow(yy[it][ip]-ym[it],2));
	double phi=atan2(yy[it][ip]-ym[it],xx[it][ip]-xm[it]);
	double r=0;
	for(int ihar=0;ihar<NHAR;ihar++){
	  if(ihar==0) r=pow(rr,3); else r=pow(rr,ihar+1);
	  frcos[it][ihar]+=r*cos((ihar+1)*phi);
	  frsin[it][ihar]+=r*sin((ihar+1)*phi);
	  fr[it][ihar]   +=r;
	}
      }
      
      for(int ihar=0;ihar<NHAR;ihar++){
	rang[it][ihar] = (atan2(frsin[it][ihar],frcos[it][ihar])+PI)/double(ihar+1);
	if(rang[it][ihar]<-PI/(ihar+1)) rang[it][ihar]+=PI2/(ihar+1);
	if(rang[it][ihar]> PI/(ihar+1)) rang[it][ihar]-=PI2/(ihar+1);
	
	re[it][ihar] = sqrt(pow(frcos[it][ihar],2)+pow(frsin[it][ihar],2))/fr[it][ihar];
      }
    }//end of eccentricity

    for(int ihar=0;ihar<NHAR;ihar++){
          
      float ecc = re[0][ihar];

      heccnpartdis[ihar]->Fill(tot, ecc);
      heccimpdis[ihar]->Fill(bimp, ecc);
    }
    
    hnpart->Fill(tot);

    hnpartimpdis->Fill(bimp, tot);

    double vn[NHAR];
    for(int ihar=0; ihar<NHAR; ihar++){
      vn[ihar]=0;
    }

    //Multiplicity
    int Nch=0, Nch2=0;
    

    
    for(UInt_t j=0;j<nTrk;j++){
      if(fabs(trkPx[j])==0) continue;
      if(fabs(trkPy[j])==0) continue;

      if(fabs(trkID[j])!=211&&fabs(trkID[j])!=321&&fabs(trkID[j])!=2212) continue;

      double pt = sqrt(trkPx[j]*trkPx[j]+trkPy[j]*trkPy[j]);
      
      if(pt<0.01) continue;

      double the = atan2(pt,trkPz[j]);
      //double phi = atan2(trkPy[j],trkPx[j]);
      double eta = -log(tan(0.5*the));
      

      if(pt<3.0&&pt>0.2&&fabs(eta)<0.9){
	Nch++;
      }

      

      if(pt>0.01&&eta>-5&&eta<-3.0){
	Nch2++;
      }
    }

    hnpartnch2dis->Fill(tot, Nch2);

    for(int ihar=0;ihar<NHAR;ihar++){

      float ecc = re[0][ihar];

      heccnchdis[ihar]->Fill(Nch, ecc);
      heccnch2dis[ihar]->Fill(Nch2, ecc);
    }


    int icenttpc = calcenttpc(system, 1.0*Nch);
    int icentbbc = calcentbbc(system, 1.0*Nch2);




    int ncut = 0;
    int ncutA = 0;
    int ncutB = 0;

    double Qx2=0, Qy2=0, Qx4=0, Qy4=0;
    double Qx2A=0, Qy2A=0;
    double Qx2B=0, Qy2B=0;
    double Qx4A=0, Qy4A=0;
    double Qx4B=0, Qy4B=0;

    float etasub[10000];
    float phisub[10000];
    float ptsub[10000];

    double Qxrp[2][4], Qyrp[2][4], rp[2][4];
    memset(Qxrp,0,sizeof(Qxrp));
    memset(Qyrp,0,sizeof(Qyrp));
    memset(rp,0,sizeof(rp));
    
    
    for(UInt_t j=0;j<nTrk;j++){
      if(fabs(trkPx[j])==0) continue;
      if(fabs(trkPy[j])==0) continue;
      

      if(fabs(trkID[j])!=211&&fabs(trkID[j])!=321&&fabs(trkID[j])!=2212
	 &&fabs(trkID[j])!=2112&&trkID[j]!=111&&trkID[j]!=221
	 &&trkID[j]!=130&&trkID[j]!=310) continue;

      
      double pt = sqrt(trkPx[j]*trkPx[j]+trkPy[j]*trkPy[j]);
      
      if(pt<0.1) continue;

      double the = atan2(pt,trkPz[j]);
      double phi = atan2(trkPy[j],trkPx[j]);
      double eta = -log(tan(0.5*the));


      hptdis->Fill(pt);
      hetadis->Fill(eta);
      hphidis->Fill(phi);

      if(pt>0.1){
	for(int ihar=0; ihar<2;ihar++){
	  if(eta<4.5&&eta>2.5) {Qxrp[ihar][0]+=cos((ihar+2)*phi); Qyrp[ihar][0]+=sin((ihar+2)*phi);}
	  else if(eta<-2.5&&eta>-4.5) {Qxrp[ihar][1]+=cos((ihar+2)*phi); Qyrp[ihar][1]+=sin((ihar+2)*phi);}
	  else if(eta>0.5&&eta<2.5) {Qxrp[ihar][2]+=cos((ihar+2)*phi); Qyrp[ihar][2]+=sin((ihar+2)*phi);}
	  else if(eta<-0.5&&eta>-2.5) {Qxrp[ihar][3]+=cos((ihar+2)*phi); Qyrp[ihar][3]+=sin((ihar+2)*phi);}
	}
      }

      if(pt<3.0&&pt>0.2&&fabs(eta)<0.9){

	
	etasub[ncut]=eta;
	phisub[ncut]=phi;
	ptsub[ncut]=pt;

	ncut++;

	Qx2+=cos(2*phi);
	Qy2+=sin(2*phi);
	
	Qx4+=cos(4*phi);
	Qy4+=sin(4*phi);

	if(eta<-0.1){
	  Qx2A+=cos(2*phi);
	  Qy2A+=sin(2*phi);
	  
	  Qx4A+=cos(4*phi);
	  Qy4A+=sin(4*phi);

	  ncutA++;
	}
	else if(eta>0.1){
	  Qx2B+=cos(2*phi);
	  Qy2B+=sin(2*phi);
	  
	  Qx4B+=cos(4*phi);
	  Qy4B+=sin(4*phi);

	  ncutB++;
	}

	for(int ihar=1;ihar<NHAR;ihar++){
	  vn[ihar]=cos((ihar+1)*(phi-rang[0][ihar]));

	  hvnimpdis[ihar]->Fill(bimp, vn[ihar]);

	  hvnpartdis[ihar]->Fill(tot, vn[ihar]);

	  hvnnchdis[ihar]->Fill(Nch, vn[ihar]);

	  hvnnch2dis[ihar]->Fill(Nch2, vn[ihar]);

	  hvnptdis[ihar][icenttpc]->Fill(pt, vn[ihar]);
	  hvnptdis2[ihar][icentbbc]->Fill(pt, vn[ihar]);
	}
      }
    }



    if(Nch2>1 && Nch>1){

      //event plane correlation
      for(int ihar=0;ihar<2;ihar++){
	for(int idet=0; idet<4; idet++){
	  rp[ihar][idet] = atan2(Qyrp[ihar][idet],Qxrp[ihar][idet])/double(ihar+2);
	  if(rp[ihar][idet]<-PI/(ihar+2)) rp[ihar][idet]+=PI2/(ihar+2);
	  if(rp[ihar][idet]> PI/(ihar+2)) rp[ihar][idet]-=PI2/(ihar+2);
	}
      }

      double rp_cor=0;
      for(int ihar=1; ihar<3; ihar++){
	for(int idet=0; idet<4; idet++){
	  rp_cor  =cos((ihar+1)*(rp[ihar-1][idet]-rang[0][ihar]));
	  rpcor[ihar-1][idet]->Fill(icenttpc+0.5, rp_cor);
	  rpcor2[ihar-1][idet]->Fill(icentbbc+0.5, rp_cor);
	  rpcor3[ihar-1][idet]->Fill(tot, rp_cor);
	}
	
	for(int idet=4; idet<8; idet++){
	  if(idet==4) rp_cor = cos((ihar+1)*(rp[ihar-1][0]-rp[ihar-1][1]));
	  else if(idet==5) rp_cor = cos((ihar+1)*(rp[ihar-1][2]-rp[ihar-1][3]));
	  else if(idet==6) rp_cor = cos((ihar+1)*(rp[ihar-1][0]-rp[ihar-1][3]));
	  else if(idet==7) rp_cor = cos((ihar+1)*(rp[ihar-1][1]-rp[ihar-1][2]));
	  
	  rpcor[ihar-1][idet]->Fill(icenttpc+0.5, rp_cor);
	  rpcor2[ihar-1][idet]->Fill(icentbbc+0.5, rp_cor);
	  rpcor3[ihar-1][idet]->Fill(tot, rp_cor);
	}
      }
    }
    
    htpcdis->Fill(Nch);
    hbbcdis->Fill(Nch2);
 
    Double_t M = 1.0*ncut;
 
    TComplex Q2 = TComplex(Qx2, Qy2);
    TComplex Q4 = TComplex(Qx4, Qy4);
  
    Double_t cor22 = CalCor22(Q2, M);
    Double_t cor24 = CalCor24(Q2, Q4, M); 

    hnchdis->Fill(Nch, Nch2);
    

    hc22dis->Fill(M, cor22);
    hc24dis->Fill(M, cor24);

    //two-sub events
    TComplex Q2A = TComplex(Qx2A, Qy2A);
    TComplex Q4A = TComplex(Qx4A, Qy4A);
    
    TComplex Q2B = TComplex(Qx2B, Qy2B);
    TComplex Q4B = TComplex(Qx4B, Qy4B);

    Double_t cor22Two = CalCor22Two(Q2A, Q2B, ncutA, ncutB);
    Jc22Twodis->Fill(M, cor22Two);
    
    Double_t cor24Two = CalCor24Two(Q2A, Q2B, Q4A, Q4B, ncutA, ncutB);
    Jc24Twodis->Fill(M, cor24Two);
        

    //int icenttpc = calcenttpc(system, 1.0*Nch);
    //int icentbbc = calcentbbc(system, 1.0*Nch2);

    if(icenttpc<0||icenttpc>=NHMUL) cout<<"God "<<Nch<<" "<<icenttpc<<endl;

    for(int itrk=0; itrk<ncut; itrk++){
      float pt = ptsub[itrk];

      hptmultpc[icenttpc]->Fill(pt);
      hptmulbbc[icentbbc]->Fill(pt);

      hmeanptdis2->Fill(Nch2, pt);

      for(int jtrk=0; jtrk<ncut; jtrk++){
	if(itrk==jtrk) continue;

	
	float deta= fabs(etasub[jtrk] - etasub[itrk]);
	float dphi = phisub[jtrk] - phisub[itrk];

	int ipt = pt/0.5;

	//folding
	if(dphi<-0.5*pi) dphi+=2*pi;
	if(dphi>1.5*pi) dphi-=2*pi;
	
	hforedis2d[icenttpc]->Fill(deta, dphi);
	hforedis2dpt[icenttpc][ipt]->Fill(deta, dphi);

	hbackdis2d[icentbbc]->Fill(deta, dphi);
	hbackdis2dpt[icentbbc][ipt]->Fill(deta, dphi);
	
	if(fabs(deta)>1.0) {
	  hc1dis->Fill(Nch, cos(1*dphi));
	  hc2dis->Fill(Nch, cos(2*dphi));
	  hc3dis->Fill(Nch, cos(3*dphi));

	  hc1dis2->Fill(Nch2, cos(1*dphi));
	  hc2dis2->Fill(Nch2, cos(2*dphi));
	  hc3dis2->Fill(Nch2, cos(3*dphi));

	  hc1dis3->Fill(tot, cos(1*dphi));
	  hc2dis3->Fill(tot, cos(2*dphi));
	  hc3dis3->Fill(tot, cos(3*dphi));

	  if(bimp<1.5) {
	    hc2ptdis2->Fill(pt, cos(2*dphi));
	    hc3ptdis2->Fill(pt, cos(3*dphi));
	  }
	}

	if(fabs(deta)>1.5) {
	  float dphi = phisub[jtrk] - phisub[itrk];

	  h15c1dis->Fill(Nch, cos(1*dphi));
	  h15c2dis->Fill(Nch, cos(2*dphi));
	  h15c3dis->Fill(Nch, cos(3*dphi));

	  h15c1dis2->Fill(Nch2, cos(1*dphi));
	  h15c2dis2->Fill(Nch2, cos(2*dphi));
	  h15c3dis2->Fill(Nch2, cos(3*dphi));

	  h15c1dis3->Fill(tot, cos(1*dphi));
	  h15c2dis3->Fill(tot, cos(2*dphi));
	  h15c3dis3->Fill(tot, cos(3*dphi));

	  if(bimp<1.5) {
	    h15c2ptdis2->Fill(pt, cos(2*dphi));
	    h15c3ptdis2->Fill(pt, cos(3*dphi));
	  }
	  
	}
      }
    }
  }

  name<<"output/"<<system<<"/flow_"<<system<<"_"<<run<<".root";
  TFile *f2 = new TFile(name.str().c_str(),"recreate");
  name.str("");
  f2->cd();

  hptdis->Write();
  hetadis->Write();
  hphidis->Write();
  
  hbbcdis->Write();  
  htpcdis->Write();
  
  for(int icent=0; icent<NHMUL; icent++){

    hptmultpc[icent]->Write();
    hptmulbbc[icent]->Write();

    hforedis2d[icent]->Write();
    hbackdis2d[icent]->Write();
    
  
    for(int ipt=0; ipt<ptbin; ipt++){
      hforedis2dpt[icent][ipt]->Write();
      hbackdis2dpt[icent][ipt]->Write();
    }
  }


  himpdis->Write();
  hnpart->Write();
  hnpartimpdis->Write();
  hnchdis->Write();
  hnpartnch2dis->Write();

  hc22dis->Write();
  hc24dis->Write();

  Jc22Twodis->Write();
  Jc24Twodis->Write();

  hc1dis->Write();
  hc2dis->Write();
  hc3dis->Write();

  hc1dis2->Write();
  hc2dis2->Write();
  hc3dis2->Write();

  hc1dis3->Write();
  hc2dis3->Write();
  hc3dis3->Write();


  h15c1dis->Write();
  h15c2dis->Write();
  h15c3dis->Write();

  h15c1dis2->Write();
  h15c2dis2->Write();
  h15c3dis2->Write();

  h15c1dis3->Write();
  h15c2dis3->Write();
  h15c3dis3->Write();


  hmeanptdis2->Write();
  hc2ptdis2->Write();
  hc3ptdis2->Write();

  h15c2ptdis2->Write();
  h15c3ptdis2->Write();

  for(int ihar=0; ihar<NHAR; ihar++){
    hvnimpdis[ihar]->Write();
    hvnpartdis[ihar]->Write();
    hvnnchdis[ihar]->Write();
    hvnnch2dis[ihar]->Write();
 
    heccnpartdis[ihar]->Write();
    heccimpdis[ihar]->Write();

    heccnchdis[ihar]->Write();
    heccnch2dis[ihar]->Write();

    for(int icent=0; icent<NHMUL; icent++){
      hvnptdis[ihar][icent]->Write();
      hvnptdis2[ihar][icent]->Write();
    }
  }

  for(int ihar=0; ihar<2; ihar++){
    for(int idet=0; idet<8; idet++){
      rpcor[ihar][idet]->Write();
      rpcor2[ihar][idet]->Write();
      rpcor3[ihar][idet]->Write();
    }
  }
  f2->Close();

}
