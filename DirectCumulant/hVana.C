#define hVana_cxx
#include "hVana.h"
#include "function.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TProfile.h"
#include "TMath.h"
#include "TH1.h"
#include "TString.h"
#include "TVectorD.h"

#include <iostream>
#include <fstream>
using namespace std;

static const int ncent = 8; // 0-80%
static const int bin_cent[ncent] = {5,15,25,35,45,55,65,75};

static const Float_t maxpt = 3.5; // max pt
static const Float_t minpt = 0.2; // min pt
static const int npt = 24; // 0.2 - 3.5 GeV/c 
static const double bin_pT[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,
                                1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,
                                2.6,2.8,3.0,3.2,3.5};

TFile *d_outfile;      // out file with histograms and profiles

TH1F *hRP; // reaction plane distribution
TH1F *hPt; // transverse momentum distribution
TH1F *hPhi; // distribution of particle azimuthal angle with respect to RP 
TH1F *hPhil; // distribution of particle azimuthal angle in the laboratory coordinate system
TH1F *hEta; // pseudorapidity
TH1F *hBimp;// impact parameter
TH1I *hMult; // emitted multiplicity 
TH2F *hBimpvsMult; // 2-D histogram impact parameter (y) vs mult (x)

TH1F *hpt[npt];
TH1F *hv2pt[npt];      // dif. v2 distribution in each pT bin from MC toy

TProfile *hv2MC;       // profile for MC integrated v2
TProfile *hv22;        // profile <<2>> from 2nd Q-Cumulants
TProfile *hv24;        // profile <<4>> from 4th Q-Cumulants
TProfile *hv22pt[npt]; // profile <<2'>> from 2nd Q-Cumulants
TProfile *hv24pt[npt]; // profile <<4'>> from 4th Q-Cumulants
// TProfile for covariance calculation according to (C.12)
// Bilandzic, A. (2012). Anisotropic flow measurements in ALICE at the large hadron collider. 
// Appendix C
TProfile *hcov24;       // <2>*<4>
TProfile *hcov22prime[npt]; // <2>*<2'>
TProfile *hcov24prime[npt]; // <2>*<4'>
TProfile *hcov42prime[npt]; // <2>*<4'>
TProfile *hcov44prime[npt]; // <4>*<4'>
TProfile *hcov2prime4prime[npt]; // <2'>*<4'>

void hVana::Booking(TString outFile){
   char name[800];
   char title[800];
   d_outfile = new TFile(outFile.Data(),"recreate");
   cout << outFile.Data() << " has been initialized" << endl;

   hMult = new TH1I("hMult", "Multiplicity", 2500, 0, 2500);
   hBimpvsMult = new TH2F("hBimpvsMult", "Impact parameter vs multiplicity;N_{ch};b (fm)", 1500, 0, 1500, 200, 0., 20.);
   hBimp = new TH1F("hBimp","Impact parameter;b (fm);dN/db",200, 0., 20.);
   hPt   = new TH1F("hPt","Pt-distribution;p_{T} (GeV/c); dN/dP_{T}",500,0.,6.);
   hRP   = new TH1F("hRP","Event Plane; #phi-#Psi_{RP}; dN/d#Psi_{RP}",300,0.,7.);
   hPhi  = new TH1F("hPhi","Particle azimuthal angle distribution with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})",300,0.,7.);
   hPhil = new TH1F("hPhil","Azimuthal angle distribution in laboratory coordinate system; #phi; dN/d#phi",300,0.,7.);
   hEta  = new TH1F("hEta","Pseudorapidity distribution; #eta; dN/d#eta",300,-2.2,2.2);

   // for (int icent=0; icent<ncent; icent++){
   //    sprintf(name,"hv2MC_%d",icent);
   //    sprintf(title,"v_{2}(cent), cent=%d-%d %%",bin_cent[icent]-5,bin_cent[icent]+5);
   //    hv2MC[icent] = new TProfile(name,title,1,0.,1.);
   //    hv2MC[icent]->Sumw2();
   //    sprintf(name,"hv22_%d",icent);
   //    sprintf(title,"v_{2}{2}(cent), cent=%d-%d %%",bin_cent[icent]-5,bin_cent[icent]+5);
   //    hv22[icent] = new TProfile(name,title,1,0.,1.);
   //    hv22[icent]->Sumw2();
   //    sprintf(name,"hv24_%d",icent);
   //    sprintf(title,"v_{2}{4}(cent), cent=%d-%d %%",bin_cent[icent]-5,bin_cent[icent]+5);
   //    hv24[icent] = new TProfile(name,title,1,0.,1.);
   //    hv24[icent]->Sumw2();
   //    sprintf(name,"hcov24_%d",icent);
   //    sprintf(title,"<2>#upoint<4> distribution, cent=%d-%d %%",bin_cent[icent]-5,bin_cent[icent]+5);
   //    hcov24[icent] = new TProfile(name,title,1,0.,1.);
   //    hcov24[icent]->Sumw2();        
   // }

   hv22 = new TProfile("hv22","Reference flow from 2nd QC",1,0.,1.);
   hv22->Sumw2();
   hv24 = new TProfile("hv24","Reference flow from 4th QC",1,0.,1.);
   hv24->Sumw2();
   hv2MC = new TProfile("hv2MC","Reference flow from MC",1,0.,1.);
   hv2MC->Sumw2();
   hcov24 = new TProfile("hcov24","<2>#upoint<4> distribution",1,0.,1.);
   hcov24->Sumw2();

   for(int kpt=0; kpt<npt; kpt++){

      sprintf(name,"hpt_%d",kpt);
      sprintf(title,"P_{T} distr, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hpt[kpt]=new TH1F(name,title,300,0.1,9.2);

      sprintf(name,"hv2pt_%d",kpt);
      sprintf(title,"v_{2}(P_{T}) Monte-Carlo Simulation, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hv2pt[kpt]=new TH1F(name,title,400,-1,1);

      sprintf(name,"hv22pt_%d",kpt);
      sprintf(title,"v_{2}(P_{T}) from 2nd order cumulants, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hv22pt[kpt]=new TProfile(name,title,1,0.,1.);
      hv22pt[kpt]->Sumw2();

      sprintf(name,"hv24pt_%d",kpt);
      sprintf(title,"v_{2}(P_{T}) from 4th order cumulants, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hv24pt[kpt]=new TProfile(name,title,1,0.,1.);
      hv24pt[kpt]->Sumw2();

      sprintf(name,"hcov22prime_%d",kpt);
      sprintf(title,"<2>#upoint<2'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov22prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov22prime[kpt]->Sumw2();

      sprintf(name,"hcov24prime_%d",kpt);
      sprintf(title,"<2>#upoint<4'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov24prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov24prime[kpt]->Sumw2();

      sprintf(name,"hcov42prime_%d",kpt);
      sprintf(title,"<4>#upoint<2'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov42prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov42prime[kpt]->Sumw2();

      sprintf(name,"hcov44prime_%d",kpt);
      sprintf(title,"<4>#upoint<4'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov44prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov44prime[kpt]->Sumw2();

      sprintf(name,"hcov2prime4prime_%d",kpt);
      sprintf(title,"<4'>#upoint<2'> distribution, %2.1f<pt<%2.1f GeV/c",bin_pT[kpt],bin_pT[kpt+1]);
      hcov2prime4prime[kpt]=new TProfile(name,title,1,0.,1.);
      hcov2prime4prime[kpt]->Sumw2();
   }

   cout << "Histograms have been initialized" << endl;
}

void hVana::Loop_a_file(TString file){
   TFile *treefile = TFile::Open(file.Data());
   TTree *tree = (TTree*)treefile->Get("htree");
   if(tree == 0) {
      cout << "htree is not found in "<< file << endl;
      treefile->Close();
      return;
   }
   cout << file << " is opened" << endl;
   Init(tree);
   Loop();
   treefile->Close();
   cout << file  <<" file processed"<<endl;
}

void hVana::Ana_end(){

   d_outfile -> cd();
   d_outfile -> Write();
   d_outfile -> Close();
   cout << "Histfile has been written" << endl;
}

void hVana::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      Ana_event();
      if (ientry%100000==0) cout << ientry << endl;
   }
}

void hVana::Ana_event(){
   int centClass = CentB(b);
   if (centClass==bin_cent[0]){ // 40-50%
      hMult -> Fill(nh);
      hRP -> Fill(rp);
      hBimp -> Fill(b);
      hBimpvsMult -> Fill(nh,b);
      // notation as (26) in DOI:10.1103/PhysRevC.83.044913

      // Q-vector of RFP
      Double_t Qx2=0, Qy2=0, Qx4=0, Qy4=0;
      TComplex Q2=0., Q4=0.;
      // p-vector of POI
      Double_t px2[npt]={0.}, py2[npt]={0.};
      TComplex p2[npt]={0.}, p4[npt]={0.}, q2[npt]={0.}, q4[npt]={0.};
      // q-vector of particles marked as POI and RFP, which is used for 
      // autocorrelation substraction
      Double_t qx2[npt]={0.}, qy2[npt]={0.}, qx4[npt]={0.}, qy4[npt]={0.};
      // My RFP selection
      Double_t M = 0.;
      // numbers of POI (mp) and particles marked both POI and RFP (mq) are equal
      // due to my selection
      Double_t mq[npt]={0.},mp[npt]={0.};
      // average reduced single-event 2- and 4-particle correlations
      Double_t redCor22[npt]={0.}, redCor24[npt]={0.};
      // event weights for correlation calculation
      Double_t w2=0.,w4=0.;
      // event weights for reduced correlation calculation
      Double_t wred2[npt]={0.},wred4[npt]={0.};
      // <2> & <4>
      Double_t cor22 = 0., cor24 = 0.;
      for(int i=0;i<nh;i++) { // track loop
         hPhi -> Fill(phi0[i]-rp);
         hPhil -> Fill(phi0[i]);
         hEta -> Fill(eta[i]);
         
         Int_t ipt = 0;
         Float_t pT = pt[i];
         hPt -> Fill(pT);
         for(int j=0; j<npt;j++){
            if(pT>=bin_pT[j] && pT<bin_pT[j+1]) ipt = j;
         }

         Double_t v2 = TMath::Cos(2*(phi0[i] - rp));

         // calculate differential v2 from MC toy
         if(pT>=minpt && pT<maxpt){
            hpt[ipt]->Fill(pT);
            hv2pt[ipt]->Fill(v2);
         }

         // RFP
         if(eta[i]<0){
            // calculate integrated v2 from MC toy for RFP
            hv2MC -> Fill(0.5,v2,1);
            Qx2+=TMath::Cos(2*phi0[i]);
            Qy2+=TMath::Sin(2*phi0[i]);
            Qx4+=TMath::Cos(4*phi0[i]);
            Qy4+=TMath::Sin(4*phi0[i]);
            M++;
         }

         // POI
         if(eta[i]>=0){
         px2[ipt]+=TMath::Cos(2*phi0[i]);
         py2[ipt]+=TMath::Sin(2*phi0[i]);
         mp[ipt]++;
         }

      } // end of track loop
      if (M >= 2.){ // <2> definition condition
         Q2 = TComplex(Qx2, Qy2);
         w2 = M*(M-1);                             // w(<2>)
         cor22 = CalCor22(Q2, M, w2);     // <2>
         hv22 -> Fill(0.5,cor22,w2); // <<2>>

         // // Non-uniform acceptance correction
         // cos2phi1   += Qx2; // formula (C2)
         // sin2phi1   += Qy2; // formula (C3)     
         // sumM += M;

         for(int ipt=0; ipt<npt;ipt++){
            if (mp[ipt] == 0) continue;
            p2[ipt] = TComplex(px2[ipt], py2[ipt]);
            q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
            wred2[ipt] = mp[ipt]*M-mq[ipt];                                         // w(<2'>)
            redCor22[ipt] = CalRedCor22(Q2,p2[ipt],M,mp[ipt],mq[ipt],wred2[ipt]);   // <2'>
            hv22pt[ipt] -> Fill(0.5,redCor22[ipt],wred2[ipt]);                      // <<2'>>
            
            // TProfile for covariance calculation in statistic error
            hcov22prime[ipt] -> Fill(0.5,cor22*redCor22[ipt],w2*wred2[ipt]);        // <2>*<2'>

            // // Non-uniform acceptance correction
            // cos2psi1[ipt] += px2[ipt];
            // sin2psi1[ipt] += py2[ipt];
            // summp[ipt] += mp[ipt];
         }
      } // end of <2> definition condition

      if (M >= 4.){ // <4> definition condition
         Q4 = TComplex(Qx4, Qy4);                                   
         w4 = M*(M-1)*(M-2)*(M-3);                             // w(<4>)
         cor24 = CalCor24(Q2, Q4, M, w4); // <4>
         hv24 -> Fill(0.5,cor24,w4); // <<4>>

         // TProfile for covariance calculation in statistic error
         hcov24 -> Fill(0.5,cor22*cor24,w2*w4); // <2>*<4>

         // // Non-uniform acceptance correction
         // cos2phi12  += (Q2*Q2-Q4).Re();
         // sin2phi12  += (Q2*Q2-Q4).Im();
         // cos2phi123 += ((Q2*Qstar(Q2)*Qstar(Q2)-Q2*Qstar(Q4)).Re())
         //             - 2.*(M-1)*(Qstar(Q2).Re());
         // sin2phi123 += ((Q2*Qstar(Q2)*Qstar(Q2)-Q2*Qstar(Q4)).Im())
         //             - 2.*(M-1)*(Qstar(Q2).Im());
         // sumMMm1 += M*(M-1);
         // sumMMm1Mm2 += M*(M-1)*(M-2);

         for(int ipt=0; ipt<npt;ipt++){
            if (mp[ipt] == 0) continue;
            q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
            wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);    // w(<4'>)
            redCor24[ipt] = CalRedCor24(Q2,Q4,p2[ipt],q2[ipt],q4[ipt],M,mp[ipt],mq[ipt],wred4[ipt]);  // <4'>
            hv24pt[ipt] -> Fill(0.5,redCor24[ipt],wred4[ipt]);                                        // <<4'>>
            
            // TProfile for covariance calculation in statistic error
            hcov24prime[ipt] -> Fill(0.5,cor22*redCor24[ipt],w2*wred4[ipt]);
            hcov42prime[ipt] -> Fill(0.5,cor24*redCor22[ipt],w4*wred2[ipt]);
            hcov44prime[ipt] -> Fill(0.5,cor24*redCor24[ipt],w4*wred4[ipt]);
            hcov2prime4prime[ipt] -> Fill(0.5,redCor22[ipt]*redCor24[ipt],wred2[ipt]*wred4[ipt]);

            // // Non-uniform acceptance correction
            // cos2psi1phi2[ipt] += (p2[ipt]*Q2-q4[ipt]).Re();
            // sin2psi1phi2[ipt] += (p2[ipt]*Q2-q4[ipt]).Im();
            // cos2psi1pphi23[ipt] += ((p2[ipt]*(Q2.Rho2()-M)).Re()) - ((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Re());
            // sin2psi1pphi23[ipt] += ((p2[ipt]*(Q2.Rho2()-M)).Im()) - ((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Im());
            // cos2psi1mphi23[ipt] += ((p2[ipt]*Qstar(Q2)*Qstar(Q2)-p2[ipt]*Qstar(Q4)).Re())-((2.*mq[ipt]*Qstar(Q2)-2.*Qstar(q2[ipt])).Re());
            // sin2psi1mphi23[ipt] += ((p2[ipt]*Qstar(Q2)*Qstar(Q2)-p2[ipt]*Qstar(Q4)).Im())-((2.*mq[ipt]*Qstar(Q2)-2.*Qstar(q2[ipt])).Im());

            // summpMmmq[ipt] += mp[ipt]*M-mq[ipt];
            // summpMm2mqMm1[ipt] += (mp[ipt]*M-2.*mq[ipt])*(M-1);
         }
      } // end of <4> definition condition
   } // centrality selection
}

TComplex hVana::Qstar(TComplex Q){
   TComplex QStar   = TComplex::Conjugate(Q);
   return QStar;
}

Double_t hVana::CalCor22(TComplex Q2, Double_t M, Double_t w2){
   // single-event average 2-particle azimuthal correlation <2>

  Double_t Q2Square = Q2.Rho2();
  // Double_t Rho2() const {return fRe*fRe+fIm*fIm;}
  Double_t coor22   = Q2Square - M;                                          
  
  return coor22/w2;
}

Double_t hVana::CalCor24(TComplex Q2, TComplex Q4, Double_t M, Double_t w4){
   // single-event average 4-particle azimuthal correlation <4>

   TComplex Q2Star   = Qstar(Q2);
   // static TComplex Conjugate(const TComplex &c) {return TComplex(c.Re(),-c.Im());}
   TComplex Q4Star   = Qstar(Q4);
   
   Double_t Q2Square = Q2.Rho2();
   Double_t Q4Square = Q4.Rho2();
   Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

   Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2*ReQQQ
                        - 4*(M-2)*Q2Square + 2*M*(M-3));

   return coor24/w4;
}

Double_t hVana::CalRedCor22(TComplex Q2, TComplex p2, Double_t M, Double_t mp, 
                     Double_t mq, Double_t wred2){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   Double_t coor22 = (p2*Q2Star-mq).Re();

   return coor22/wred2;
}

Double_t hVana::CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                            TComplex q4, Double_t M, Double_t mp, Double_t mq, Double_t wred4){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   TComplex Q4Star = TComplex::Conjugate(Q4);
   TComplex q2Star = TComplex::Conjugate(q2);
   Double_t Q2Square = Q2.Rho2();
   TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
                  - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
                  - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
                  + 2.0*mq*M-6.0*mq;
   Double_t coor24 = coorc.Re(); 
   return coor24/wred4;
}

void loop_a_list_of_tree(){
   hVana *ana = new hVana();
   ana->Booking("/mnt/pool/2/lbavinh/DirectCumulant/OUT/v2QC_5mil_v2pt_cent0-10.root");
   
   ifstream ifile("/mnt/pool/2/lbavinh/EventGenerator/OUT/FlowPureEtaBimp/runlist.list");
   char filename[200];
   int nfiles=1;
   while(ifile.getline(filename,200)) {
      cout << nfiles <<" file is processing "<<filename <<endl;
      ana->Loop_a_file(filename);
      nfiles++;
   }
   cout<< "Done. " << nfiles-1 << " files are processed." << endl;
   ana -> Ana_end();
   cout << "Histfile written. Congratz!" << endl;
}

// void loop_a_list_of_tree(){
//    hVana *ana = new hVana();
//    ana->Booking("/mnt/pool/2/lbavinh/DirectCumulant/OUT/v2QC_5mil_v2pt_cent60-70.root");
//    ana->Loop_a_file("/mnt/pool/2/lbavinh/EventGenerator/OUT/FlowPureEtaBimp/v2hadron_1.root");
//    // ifstream ifile("/mnt/pool/2/lbavinh/EventGenerator/OUT/FlowPureEtaBimp/runlist.list");
//    // char filename[200];
//    // int nfiles=1;
//    // while(ifile.getline(filename,200)) {
//    //    cout << nfiles <<" file is processing "<<filename <<endl;
//    //    ana->Loop_a_file(filename);
//    //    nfiles++;
//    // }
//    // cout<< "Done. " << nfiles-1 << " files are processed." << endl;
//    ana -> Ana_end();
//    cout << "Histfile written. Congratz!" << endl;
// }