#define hVana_cxx
#include "hVana.h"
#include "TProfile.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TPave.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TString.h"
#include "TLatex.h"
#include "TComplex.h"
#include "Riostream.h"
#include <vector>

static const int npt = 25; // 0.2 - 3.5 GeV/c 
static const double bin_w[25]={0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.5};
static const float maxpt = 3.5; // max pt
static const float minpt = 0.2; // min pt

TH1F *hpt[npt];
TH1F *hv2ptMC[npt];
TH1F *hv2ptTwo[npt];
TH1F *hv2ptFour[npt];

TFile *d_outfile;

// Use or not the non-unit particle weights above:
Bool_t bUseWeights = kFALSE; 

// Pick up randomly some harmonics:
const Int_t h1=2, h2=-2, h3=2, h4=-2;

// Book Q-vector components: 
const Int_t sum = (h1<0?-1*h1:h1)+(h2<0?-1*h2:h2)+(h3<0?-1*h3:h3)+(h4<0?-1*h4:h4);
const Int_t maxCorrelator = 4; // We will not go beyond 8-p correlations
const Int_t maxHarmonic = sum+1; 
const Int_t maxPower = maxCorrelator+1; 
TComplex Qvector[maxHarmonic][maxPower]; // All needed Q-vector components

// Store the final results here:
//  Remark: [2][maxCorrelator] => [Cos,Sin][<2>,<3>,<4>,<5>,<6>,<7>,<8>]
TProfile *correlations[2][maxCorrelator] = {{NULL}};

TProfile *v2intMCw = {NULL};
TProfile *v2intMC1 = {NULL};
TProfile *flow = {NULL};



TH1F *v2intMC; /* Integrated flow */
TH1F *v2intTwo; /* Integrated flow */
TH1F *v2intFour; /* Integrated flow */

double v2ev;  /* Integrated flow values in a given event */
double v2mean=0.; /* Mean flow parameters <vnev> */

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
      ana_event(jentry,ientry);
   }
}

void hVana::loop_a_file(char *file) {
  TFile *treefile = TFile::Open(file);
  TTree *tree = (TTree*)treefile->Get("htree");
  
  if(tree == 0) {
    cout <<"htree is not found in "<<file<<endl;
    treefile->Close();
    return;
  }
  cout << file <<" is opened"<<endl;
  Init(tree);

  Loop();

  treefile->Close();
  cout << file  <<" file processed"<<endl;
}

void hVana::ana_end() {
  flow -> Fill(0.5,v2intMCw->GetBinContent(1));
  flow -> Fill(1.5,v2intMC1->GetBinContent(1));
  flow -> Fill(2.5,sqrt(correlations[0][0]->GetBinContent(1)) );
  flow -> Fill(3.5,pow(-(correlations[0][2]->GetBinContent(1) - 2*correlations[0][0]->GetBinContent(1)*correlations[0][0]->GetBinContent(1)),1./4.) );
  d_outfile -> cd();

  v2intMC   -> Write();
  v2intTwo  -> Write();
  v2intFour -> Write();
  v2intMCw  -> Write();
  v2intMC1  -> Write();

  for(int fpt=0; fpt<npt-1; fpt++){
    hpt[fpt]->Write(); 
    hv2ptMC[fpt]->Write();
    hv2ptTwo[fpt]->Write();
    hv2ptFour[fpt]->Write();
  }

  //htree->Write();

  flow -> Write();

  d_outfile -> Close();
}

void hVana::book_hist(char *outfile) {
  d_outfile = new TFile(outfile,"recreate");

  char name[800];
  char title[800];
  v2intMC = new TH1F("v2intMC","Integrated elliptic flow distribution MC;v_{2};dN/d(v_{2})",300,-0.2,0.2);
  v2intTwo = new TH1F("v2intTwo","Integrated elliptic flow distribution extracted from 2nd order cumulants;v_{2};dN/d(v_{2})",300,-0.2,0.2);
  v2intFour = new TH1F("v2intFour","Integrated elliptic flow distribution extracted from 4th order cumulants;v_{2};dN/d(v_{2})",300,-0.2,0.2);

  for(int kpt=0; kpt<npt-1; kpt++){

    sprintf(name,"hpt_%d",kpt);
    sprintf(title,"P_{T} distr, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hpt[kpt]=new TH1F(name,title,300,0.1,9.2);

    sprintf(name,"hv2ptMC_%d",kpt);
    sprintf(title,"v_{2}(P_{T}) Monte-Carlo Simulation, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2ptMC[kpt]=new TH1F(name,title,400,-1,1);

    sprintf(name,"hv2ptTwo_%d",kpt);
    sprintf(title,"v_{2}(P_{T}) from 2nd order cumulants, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2ptTwo[kpt]=new TH1F(name,title,400,-1,1);

    sprintf(name,"hv2ptFour_%d",kpt);
    sprintf(title,"v_{2}(P_{T}) from 4th order cumulants, %2.1f<pt<%2.1f GeV/c",bin_w[kpt],bin_w[kpt+1]);
    hv2ptFour[kpt]=new TH1F(name,title,400,-1,1);

  }

  // Book everything for cumulant calculation here
  for(Int_t cs=0;cs<2;cs++) {
    for(Int_t c=0;c<maxCorrelator;c++) {
      correlations[cs][c] = new TProfile("","",1,0.,1.);
      correlations[cs][c]->Sumw2();
    } // end of for(Int_t c=0;c<maxCorrelator;c++)
  } // end of for(Int_t cs=0;cs<2;cs++)
  v2intMCw = new TProfile("v2intMCw","Integrated elliptic flow from MC simulation (weighted by multiplicity)",1,0.,1.);
  v2intMCw->Sumw2();
  v2intMC1 = new TProfile("v2intMC1","Integrated elliptic flow from MC simulation",1,0.,1.);
  v2intMC1->Sumw2();
  flow = new TProfile("flow","1,2: v_{2}{MC}; 3: v_{2}{2,QC}; 4: v_{2}{4,QC}",4,0.,4.,0.,1.);
}

void hVana::ana_init(char *outfile) {
  book_hist(outfile);
}

void hVana::ana_event(int jentry, int ientry) {

  vector<vector<float> > poi(16);
  vector<float> rfp;

  if(ientry%1000==0) cout << ientry << " events were looped for integrated flow calculations" << endl;
  v2ev=0;
  for(int i=0;i<nh;i++) {//track loop
    float pT = pt[i];
    if(pT>=minpt && pT<=maxpt){//track's momentum selection
      int ipt = 0;
      for(int j=0; j<npt-1;j++){
        if(pT>=bin_w[j] && pT<bin_w[j+1]) ipt = j;
      }
      hpt[ipt]->Fill(pT);
      double v2rxn = TMath::Cos(2*(phi0[i] - rp));
      hv2ptMC[ipt]->Fill(v2rxn);
    }//track's momentum selection

    v2ev += TMath::Cos(2*(phi0[i]-rp));
    
    //RFP
    if(pT>=minpt && pT<1.0){
      rfp.push_back(phi0[i]);
    }
    //POI
    for(int j=0; j<16;j++){
      if(pT>=bin_w[j+8] && pT<bin_w[j+9]){
        poi[j].push_back(phi0[i]);
      }
    }

  }// end of track loop
  for(int j=0; j<16;j++){
    float *POI;
    POI = new float[poi[j].size()];
    for(unsigned int i=0; i<poi[j].size();i++){
      POI[i]=poi[j][i];
    }
    float *RFP;
    RFP = new float[rfp.size()];
    for(unsigned int i=0;i<rfp.size();i++){
      RFP[i]=rfp[i];
    }
    hv2ptTwo[j+8]  -> Fill(TwoNestedLoops(h1,h2,poi[j].size(),rfp.size(),POI,RFP));
    //hv2ptFour[j+8] -> Fill(FourNestedLoops(h1,h2,h3,h4,poi[j].size(),rfp.size(),POI,RFP));
    delete[] POI,RFP;
  }
  GenericFormulas(nh,phi0);
  v2mean = v2ev/nh;
  v2intMC -> Fill(v2mean);
  v2intMCw -> Fill(0.5,v2mean,nh);
  v2intMC1 -> Fill(0.5,v2mean,1);      
  poi.clear();
  rfp.clear();
}

void hVana::CalculateQvectors(Int_t nParticles, Float_t *angles) {
 // Calculate Q-vectors.

 // a) Make sure all Q-vectors are initially zero;
 // b) Calculate Q-vectors for available angles and weights. 

 // a) Make sure all Q-vectors are initially zero:
 for(Int_t h=0;h<maxHarmonic;h++)
 {
  for(Int_t p=0;p<maxPower;p++)
  {
   Qvector[h][p] = TComplex(0.,0.);
  } //  for(Int_t p=0;p<maxPower;p++)
 } // for(Int_t h=0;h<maxHarmonic;h++)

 // b) Calculate Q-vectors for available angles and weights: 
 Double_t dPhi = 0.; // particle angle
 Double_t wPhi = 1.; // particle weight
 Double_t wPhiToPowerP = 1.; // particle weight raised to power p
 for(Int_t i=0;i<nParticles;i++) {// loop over particles
    dPhi = angles[i];
    //if(bUseWeights){wPhi = weights[i];}
    for(Int_t h=0;h<maxHarmonic;h++) {
      for(Int_t p=0;p<maxPower;p++) {
        if(bUseWeights){wPhiToPowerP = pow(wPhi,p);}
        Qvector[h][p] += TComplex(wPhiToPowerP*TMath::Cos(h*dPhi),wPhiToPowerP*TMath::Sin(h*dPhi));
      } //  for(Int_t p=0;p<maxPower;p++)
    } // for(Int_t h=0;h<maxHarmonic;h++)
  } //  for(Int_t i=0;i<nParticles;i++) // loop over particles
}

TComplex hVana::Q(Int_t n, Int_t p) {
 // Using the fact that Q{-n,p} = Q{n,p}^*. 
 
 if(n>=0){return Qvector[n][p];} 
 return TComplex::Conjugate(Qvector[-n][p]);
 
} // TComplex Q(Int_t n, Int_t p)

TComplex hVana::Two(Int_t n1, Int_t n2) {
  // Generic two-particle correlation <exp[i(n1*phi1+n2*phi2)]>.

  TComplex two = Q(n1,1)*Q(n2,1)-Q(n1+n2,2); // Q(order of harmonic, order of particle correlation)

  return two;
}

TComplex hVana::Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4) {
 // Generic four-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4)]>.

 TComplex four = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)-Q(n2,1)*Q(n1+n3,2)*Q(n4,1)
               - Q(n1,1)*Q(n2+n3,2)*Q(n4,1)+2.*Q(n1+n2+n3,3)*Q(n4,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)
               + Q(n2+n3,2)*Q(n1+n4,2)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)+Q(n1+n3,2)*Q(n2+n4,2)
               + 2.*Q(n3,1)*Q(n1+n2+n4,3)-Q(n1,1)*Q(n2,1)*Q(n3+n4,2)+Q(n1+n2,2)*Q(n3+n4,2)
               + 2.*Q(n2,1)*Q(n1+n3+n4,3)+2.*Q(n1,1)*Q(n2+n3+n4,3)-6.*Q(n1+n2+n3+n4,4);

 return four;
}

void hVana::GenericFormulas(Int_t nParticles, Float_t *angles) {
  
  CalculateQvectors(nParticles, angles);

  // d) Calculate n-particle correlations from Q-vectors (using standalone formulas):
  //  2-p correlations:


  TComplex two = Two(h1,h2)/Two(0,0).Re();
  v2intTwo -> Fill(two.Re());
  Double_t wTwo = Two(0,0).Re(); // Weight is 'number of combinations' by default
  correlations[0][0]->Fill(0.5,two.Re(),wTwo); // <<cos(h1*phi1+h2*phi2)>>
  correlations[1][0]->Fill(0.5,two.Im(),wTwo); // <<sin(h1*phi1+h2*phi2)>>

  //  4-p correlations:

  TComplex four = Four(h1,h2,h3,h4)/Four(0,0,0,0).Re();
  Double_t wFour = Four(0,0,0,0).Re(); // Weight is 'number of combinations' by default
  v2intFour -> Fill(four.Re());
  correlations[0][2]->Fill(0.5,four.Re(),wFour); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
  correlations[1][2]->Fill(0.5,four.Im(),wFour); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>> 

} // void GenericFormulas()

float hVana::TwoNestedLoops(Int_t n1,Int_t n2, Int_t nPOI, Int_t nRFP, float *anglePOI, float *angleRFP) {

  // Calculation of <cos(n1*phi1+n2*phi2)> and <sin(n1*phi1+n2*phi2)>
  // with two nested loops.
  float temp;
  TProfile *nestedLoops = {NULL}; // Correlations calculated from nested loops
  nestedLoops = new TProfile("","",1,0.,1.);
  nestedLoops -> Sumw2();
  Double_t phi1=0., phi2=0.; // particle angle
  Double_t w1=1., w2=1.; // particle weight
  for(Int_t i1=0;i1<nRFP;i1++) {
    phi1 = angleRFP[i1];
    //if(bUseWeights){w1 = weights[i1];}
    for(Int_t i2=0;i2<nPOI;i2++) {
      //if(i2==i1){continue;} // Get rid of autocorrelations
      phi2 = anglePOI[i2];
      //if(bUseWeights){w2 = weights[i2];}
      // Fill profiles:
      nestedLoops->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2),w1*w2); // Fill(x,y,w)
    } // for(Int_t i2=0;i2<nParticles;i2++)
  } // for(Int_t i1=0;i1<nParticles;i1++)
  return temp = nestedLoops->GetBinContent(1);
} // end of void TwoNestedLoops(Int_t n1,Int_t n2,TArrayD a,TArrayD w)

float hVana::FourNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4, Int_t nPOI, Int_t nRFP, float *anglePOI, float *angleRFP) {
  float temp;
  TProfile *nestedLoops = {NULL}; // Correlations calculated from nested loops
  nestedLoops = new TProfile("","",1,0.,1.);
  nestedLoops -> Sumw2();
  // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4)> and 
  // <sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4)> with four nested loops. 

  Double_t phi1=0., phi2=0., phi3=0., phi4=0.; // particle angle
  Double_t w1=1., w2=1., w3=1., w4=1.; // particle weight
  for(Int_t i1=0;i1<nRFP;i1++)
  { 
    phi1 = angleRFP[i1];
    //if(bUseWeights){w1 = weights[i1];}
    for(Int_t i2=0;i2<nPOI;i2++)
    {
      //if(i2==i1){continue;} // Get rid of autocorrelations
      phi2 = anglePOI[i2];
      //if(bUseWeights){w2 = weights[i2];}
      for(Int_t i3=0;i3<nPOI;i3++)
      {
        if(i3==i2){continue;} // Get rid of autocorrelations
        phi3 = anglePOI[i3];
        //if(bUseWeights){w3 = weights[i3];}
        for(Int_t i4=0;i4<nPOI;i4++)
        {
          if(i4==i2||i4==i3){continue;} // Get rid of autocorrelations
          phi4 = anglePOI[i4];
          //if(bUseWeights){w4 = weights[i4];}
          // Fill the profiles:
          nestedLoops->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4),w1*w2*w3*w4);
        } // end of for(Int_t i4=0;i4<nParticles;i4++) 
      } // end of for(Int_t i3=0;i3<nParticles;i3++)
    } // end of for(Int_t i2=0;i2<nParticles;i2++)
  } // end of for(Int_t i1=0;i1<nParticles;i1++)
  return temp = nestedLoops->GetBinContent(1);
} // end of void FourNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4)