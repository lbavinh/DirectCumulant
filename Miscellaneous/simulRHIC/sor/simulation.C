//#include <math.h>
//#include <iostream.h>
//#include "TVector2.h"

//gSystem->Load("libPhysics");
{
  gSystem->Load("libPhysics");

  float twopi = 3.14159265*2.0;
  float pi = 3.14159265;

  int nevents = 500;
  int ntracks = 280;
  int npairs = 0;
  float v2 = 0.1;
  float r0exp = 2.405/(v2*(float)ntracks);
  ntracks -= 2*npairs;

  float track_phi[500];//use this to store phi values to calculate observed v2.
  float track_phi_eta1[500];
  float track_phi_eta2[500];

  TH1F *GhistReal1 = new TH1F("GhistReal1","G",100,0.0,1.3*r0exp); 
  TH1F *GhistImag1 = new TH1F("GhistImag1","G",100,0.0,1.3*r0exp); 
  TH1F *GhistReal2 = new TH1F("GhistReal2","G",100,0.0,1.3*r0exp); 
  TH1F *GhistImag2 = new TH1F("GhistImag2","G",100,0.0,1.3*r0exp); 
  TH1F *GhistReal3 = new TH1F("GhistReal3","G",100,0.0,1.3*r0exp); 
  TH1F *GhistImag3 = new TH1F("GhistImag3","G",100,0.0,1.3*r0exp); 
  TH1F *GhistReal4 = new TH1F("GhistReal4","G",100,0.0,1.3*r0exp); 
  TH1F *GhistImag4 = new TH1F("GhistImag4","G",100,0.0,1.3*r0exp); 

  TH1F *GmeanReal1 = new TH1F("GmeanReal1","G1",100,0.0,1.3*r0exp); 
  TH1F *GmeanImag1 = new TH1F("GmeanImag1","G1",100,0.0,1.3*r0exp); 
  TH1F *GmeanReal2 = new TH1F("GmeanReal2","G2",100,0.0,1.3*r0exp); 
  TH1F *GmeanImag2 = new TH1F("GmeanImag2","G2",100,0.0,1.3*r0exp); 
  TH1F *GmeanReal3 = new TH1F("GmeanReal3","G3",100,0.0,1.3*r0exp); 
  TH1F *GmeanImag3 = new TH1F("GmeanImag3","G3",100,0.0,1.3*r0exp); 
  TH1F *GmeanReal4 = new TH1F("GmeanReal4","G4",100,0.0,1.3*r0exp); 
  TH1F *GmeanImag4 = new TH1F("GmeanImag4","G4",100,0.0,1.3*r0exp); 

  for(int loopi=0; loopi<100; loopi++){
    GmeanReal1->SetBinContent(loopi+1,0.0);
    GmeanImag1->SetBinContent(loopi+1,0.0);
    GmeanReal2->SetBinContent(loopi+1,0.0);
    GmeanImag2->SetBinContent(loopi+1,0.0);
    GmeanReal3->SetBinContent(loopi+1,0.0);
    GmeanImag3->SetBinContent(loopi+1,0.0);
    GmeanReal4->SetBinContent(loopi+1,0.0);
    GmeanImag4->SetBinContent(loopi+1,0.0);
  }    

  TH1F *GhistSquareReal1 = new TH1F("GhistSquareReal1","Re(G1*G1)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareImag1 = new TH1F("GhistSquareImag1","Im(G1*G1)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareReal2 = new TH1F("GhistSquareReal2","Re(G2*G2)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareImag2 = new TH1F("GhistSquareImag2","Im(G2*G2)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareReal3 = new TH1F("GhistSquareReal3","Re(G3*G3)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareImag3 = new TH1F("GhistSquareImag3","Im(G3*G3)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareReal4 = new TH1F("GhistSquareReal4","Re(G4*G4)",100,0.0,1.3*r0exp); 
  TH1F *GhistSquareImag4 = new TH1F("GhistSquareImag4","Im(G4*G4)",100,0.0,1.3*r0exp); 

  TF1 *func = new TF1("func","1.0 + 2.0*[0]*cos(2.0*(x))", 0.0, pi);
  func->SetParameter(0,v2);
  TRandom *reta = new TRandom();
  //TF2 *func2 = new TF2("func2","1.0 + 2.0*[0]*cos(2.0*(x-y))", 0.0, twopi, 0.0, pi);
  //func2->SetParameter(0, v2);
  
  TVector2 *vec1 = new TVector2(1.0, 0.0);
  TVector2 *vec2 = new TVector2(0.0, 1.0);
  cout << vec1->DeltaPhi(*vec2) << endl;

  TH1F *res_eta = new TH1F("res_eta","eta-subevent resolution",100, -1, 1);
  TH1F *res_ran = new TH1F("res_ran","ran-subevent resolution",100, -1, 1);
  TH1F *disteta = new TH1F("disteta","eta-subevent v2",64, 0, pi);
  TH1F *distran = new TH1F("distran","ran-subevent v2",64, 0, pi);
  TH1F *v2eta = new TH1F("v2eta","eta-subevent v2",100, -1, 1);
  TH1F *v2ran = new TH1F("v2ran","ran-subevent v2",100, -1, 1);

  float Qx_ran_1 = 0.0, Qx_ran_2 = 0.0, Qx_eta_1 = 0.0, Qx_eta_2 = 0.0;
  float Qy_ran_1 = 0.0, Qy_ran_2 = 0.0, Qy_eta_1 = 0.0, Qy_eta_2 = 0.0;
  Double_t phi=0.0;

  for(int event = 0; event<nevents; event++){
    //if((event%10)==0)
    int eta1counter=0;
    int eta2counter=0;
    int rancounter=0;
    int ran1counter=0;
    int ran2counter=0;
    Qx_eta_1 = Qy_eta_1 = Qx_ran_1 = Qy_ran_1 = Qx_eta_2 = Qy_eta_2 = Qx_ran_2 = Qy_ran_2 = 0.0;
    //for(int loopi=0; loopi<100; loopi++){
    //GhistReal1->SetBinContent(loopi+1,1.0);
    //GhistImag1->SetBinContent(loopi+1,1.0);
    //GhistReal2->SetBinContent(loopi+1,1.0);
    //GhistImag2->SetBinContent(loopi+1,1.0);
    //GhistReal3->SetBinContent(loopi+1,1.0);
    //GhistImag3->SetBinContent(loopi+1,1.0);
    //GhistReal4->SetBinContent(loopi+1,1.0);
    //GhistImag4->SetBinContent(loopi+1,1.0);
    //}    
    double theta1 = (pi/2.0)*reta->Rndm(1+event);
    double theta2 = theta1 + (1.0*pi/8.0);
    double theta3 = theta1 + (2.0*pi/8.0);
    double theta4 = theta1 + (3.0*pi/8.0);
    theta2 -= (theta2 < (pi/2.0)) ? 0 : (pi/2.0);
    theta3 -= (theta3 < (pi/2.0)) ? 0 : (pi/2.0);
    theta4 -= (theta4 < (pi/2.0)) ? 0 : (pi/2.0);
    cout << event << "\t" << 2.0*theta1/pi << "\t" << 2.0*(theta2-theta1)/pi << "\t" << 2.0*(theta3-theta2)/pi << "\t" << 2.0*(theta4-theta3)/pi << endl;

    for(int track = 0; track<ntracks; track++){
      phi = func->GetRandom();
      float cosnphi1 = cos(2.0*(phi-theta1));
      float cosnphi2 = cos(2.0*(phi-theta2));
      float cosnphi3 = cos(2.0*(phi-theta3));
      float cosnphi4 = cos(2.0*(phi-theta4));
      for(int loopi=0; loopi<100; loopi++){
	float rval = GhistReal1->GetBinCenter(loopi+1);
	if(track==0){//initialize
	  if(event==0)cout << rval << endl;
	  GhistReal1->SetBinContent(loopi+1, 1.0);
	  GhistImag1->SetBinContent(loopi+1, rval*cosnphi1);
	  GhistReal2->SetBinContent(loopi+1, 1.0);
	  GhistImag2->SetBinContent(loopi+1, rval*cosnphi2);
	  GhistReal3->SetBinContent(loopi+1, 1.0);
	  GhistImag3->SetBinContent(loopi+1, rval*cosnphi3);
	  GhistReal4->SetBinContent(loopi+1, 1.0);
	  GhistImag4->SetBinContent(loopi+1, rval*cosnphi4);
	}else{
	  float Real1 = GhistReal1->GetBinContent(loopi+1);
	  float Imag1 = GhistImag1->GetBinContent(loopi+1);
	  float Real2 = GhistReal2->GetBinContent(loopi+1);
	  float Imag2 = GhistImag2->GetBinContent(loopi+1);
	  float Real3 = GhistReal3->GetBinContent(loopi+1);
	  float Imag3 = GhistImag3->GetBinContent(loopi+1);
	  float Real4 = GhistReal4->GetBinContent(loopi+1);
	  float Imag4 = GhistImag4->GetBinContent(loopi+1);
	  
	  TComplex G1 = TComplex(Real1,Imag1);
	  TComplex G2 = TComplex(Real2,Imag2);
	  TComplex G3 = TComplex(Real3,Imag3);
	  TComplex G4 = TComplex(Real4,Imag4);
	  
	  TComplex g1 = TComplex(1.0,rval*cosnphi1);
	  TComplex g2 = TComplex(1.0,rval*cosnphi2);
	  TComplex g3 = TComplex(1.0,rval*cosnphi3);
	  TComplex g4 = TComplex(1.0,rval*cosnphi4);
	  
	  Double_t R1 = (G1*g1).Re();
	  Double_t I1 = (G1*g1).Im();
	  Double_t R2 = (G2*g2).Re();
	  Double_t I2 = (G2*g2).Im();
	  Double_t R3 = (G3*g3).Re();
	  Double_t I3 = (G3*g3).Im();
	  Double_t R4 = (G4*g4).Re();
	  Double_t I4 = (G4*g4).Im();
	  
	  GhistReal1->SetBinContent(loopi+1, R1);
	  GhistImag1->SetBinContent(loopi+1, I1);
	  GhistReal2->SetBinContent(loopi+1, R2);
	  GhistImag2->SetBinContent(loopi+1, I2);
	  GhistReal3->SetBinContent(loopi+1, R3);
	  GhistImag3->SetBinContent(loopi+1, I3);
	  GhistReal4->SetBinContent(loopi+1, R4);
	  GhistImag4->SetBinContent(loopi+1, I4);
	}
      }
      double rnum = reta->Rndm((1+event)*track+track+1);
      if(rnum>0.5){//positive eta
	Qx_eta_1 += cos(2.0*phi);
	Qy_eta_1 += sin(2.0*phi);
	track_phi_eta1[eta1counter]=phi;
	eta1counter++;
      }else{//negative eta
	Qx_eta_2 += cos(2.0*phi);
	Qy_eta_2 += sin(2.0*phi);
	track_phi_eta2[eta2counter]=phi;
	eta2counter++;
      }
      if(track < ntracks/2){//random sub 1
	Qx_ran_1 += cos(2.0*phi);
	Qy_ran_1 += sin(2.0*phi);
	track_phi[rancounter]=phi;
	ran1counter++;
	rancounter++;
      }else{//random sub 2	
	Qx_ran_2 += cos(2.0*phi);
	Qy_ran_2 += sin(2.0*phi);      
	track_phi[rancounter]=phi;
	ran2counter++;
	rancounter++;
      }
    }

    //now input some correlated pairs
    int pairinsame = 1; //used to switch evenly between eta subevents

    for(int jpair = 0; jpair<npairs; jpair++){
      phi = func->GetRandom();
      float cosnphi1 = cos(2.0*phi);
      float cosnphi2 = cos(2.0*(phi-(pi/8.0)));
      float cosnphi3 = cos(2.0*(phi-(2.0*pi/8.0)));
      float cosnphi4 = cos(2.0*(phi-(3.0*pi/8.0)));
      for(int loopi=0; loopi<100; loopi++){
	float rval = (0.5 + (float)loopi)*1.3*r0exp/100.;
	float Real1 = GhistReal1->GetBinContent(loopi+1);
	float Imag1 = GhistImag1->GetBinContent(loopi+1);
	float Real2 = GhistReal2->GetBinContent(loopi+1);
	float Imag2 = GhistImag2->GetBinContent(loopi+1);
	float Real3 = GhistReal3->GetBinContent(loopi+1);
	float Imag3 = GhistImag3->GetBinContent(loopi+1);
	float Real4 = GhistReal4->GetBinContent(loopi+1);
	float Imag4 = GhistImag4->GetBinContent(loopi+1);
	TComplex G1 = TComplex(Real1,Imag1);
	TComplex G2 = TComplex(Real2,Imag2);
	TComplex G3 = TComplex(Real3,Imag3);
	TComplex G4 = TComplex(Real4,Imag4);
	
	TComplex g1 = TComplex(1.0,rval*cosnphi1);
	TComplex g2 = TComplex(1.0,rval*cosnphi2);
	TComplex g3 = TComplex(1.0,rval*cosnphi3);
	TComplex g4 = TComplex(1.0,rval*cosnphi4);

	TComplex prod1 = TComplex(0,0);
	TComplex prod2 = TComplex(0,0);
	TComplex prod3 = TComplex(0,0);
	TComplex prod4 = TComplex(0,0);

	prod1 = G1*g1*g1;//we count twice this phi because it's a pair
	prod2 = G2*g2*g2;
	prod3 = G3*g3*g3;
	prod4 = G4*g4*g4;

	GhistReal1->SetBinContent(loopi+1, prod1.Re());
	GhistImag1->SetBinContent(loopi+1, prod1.Im());
	GhistReal2->SetBinContent(loopi+1, prod2.Re());
	GhistImag2->SetBinContent(loopi+1, prod2.Im());
	GhistReal3->SetBinContent(loopi+1, prod3.Re());
	GhistImag3->SetBinContent(loopi+1, prod3.Im());
	GhistReal4->SetBinContent(loopi+1, prod4.Re());
	GhistImag4->SetBinContent(loopi+1, prod4.Im());
      }

      double rnum = reta->Rndm(event + jpair);
      if(rnum<0.001){//pair falls in same eta
	if(pairinsame==1){
	  Qx_eta_1 += cos(2.0*phi);
	  Qy_eta_1 += sin(2.0*phi);
	  Qx_eta_1 += cos(2.0*phi);
	  Qy_eta_1 += sin(2.0*phi);
	  track_phi_eta1[eta1counter]=phi;
	  eta1counter++;
	  track_phi_eta1[eta1counter]=phi;
	  eta1counter++;
	  pairinsame=2;
	}else if(pairinsame==2){
	  Qx_eta_2 += cos(2.0*phi);
	  Qy_eta_2 += sin(2.0*phi);
	  Qx_eta_2 += cos(2.0*phi);
	  Qy_eta_2 += sin(2.0*phi);
	  track_phi_eta2[eta2counter]=phi;
	  eta2counter++;
	  track_phi_eta2[eta2counter]=phi;
	  eta2counter++;
	  pairinsame=1;
	}
      }else{//pair falls in opposite eta
	Qx_eta_1 += cos(2.0*phi);
	Qy_eta_1 += sin(2.0*phi);
	Qx_eta_2 += cos(2.0*phi);
	Qy_eta_2 += sin(2.0*phi);
	track_phi_eta1[eta1counter]=phi;
	eta1counter++;
	track_phi_eta2[eta2counter]=phi;
	eta2counter++;
      }

      if(jpair<npairs/4){//both in random sub event 1
	Qx_ran_1 += cos(2.0*phi);
	Qy_ran_1 += sin(2.0*phi);
	Qx_ran_1 += cos(2.0*phi);
	Qy_ran_1 += sin(2.0*phi);
	track_phi[rancounter]=phi;
	ran1counter++;
	rancounter++;
	track_phi[rancounter]=phi;
	ran1counter++;
	rancounter++;
      }else if(jpair<(npairs/2)){//both in random sub event 2
	Qx_ran_2 += cos(2.0*phi);
	Qy_ran_2 += sin(2.0*phi);
	Qx_ran_2 += cos(2.0*phi);
	Qy_ran_2 += sin(2.0*phi);	
	track_phi[rancounter]=phi;
	ran2counter++;
	rancounter++;
	track_phi[rancounter]=phi;
	ran2counter++;
	rancounter++;
      }else{//the rest are split between random 1 and random 2
	Qx_ran_1 += cos(2.0*phi);
	Qy_ran_1 += sin(2.0*phi);
	Qx_ran_2 += cos(2.0*phi);
	Qy_ran_2 += sin(2.0*phi);
	track_phi[rancounter]=phi;
	ran1counter++;
	rancounter++;
	track_phi[rancounter]=phi;
	ran2counter++;
	rancounter++;
      }
    }

    // keep mean
    GmeanReal1->Add(GhistReal1);
    GmeanImag1->Add(GhistImag1);
    GmeanReal2->Add(GhistReal2);
    GmeanImag2->Add(GhistImag2);
    GmeanReal3->Add(GhistReal3);
    GmeanImag3->Add(GhistImag3);
    GmeanReal4->Add(GhistReal4);
    GmeanImag4->Add(GhistImag4);

    float Qx_tot = Qx_ran_1 + Qx_ran_2;
    float Qy_tot = Qy_ran_1 + Qy_ran_2;
    //by now the event and subevent vectors are defined
    //and I have a set of tracks to correlate with random subevents
    //and two sets of tracks to correlate with either eta subevent

    //Fill the resolution histograms
    
    TVector2 *Qtot  = new TVector2(Qx_tot,   Qy_tot);
    TVector2 *Qran1 = new TVector2(Qx_ran_1, Qy_ran_1);
    TVector2 *Qran2 = new TVector2(Qx_ran_2, Qy_ran_2);
    TVector2 *Qeta1 = new TVector2(Qx_eta_1, Qy_eta_1);
    TVector2 *Qeta2 = new TVector2(Qx_eta_2, Qy_eta_2);
    float Psi_ran_1 = Qran1.Phi()/2.0;//0.5*atan2(Qy_ran_1,Qx_ran_1);
    float Psi_ran_2 = Qran2.Phi()/2.0;//0.5*atan2(Qy_ran_2,Qx_ran_2);
    float Psi_eta_1 = Qeta1.Phi()/2.0;//0.5*atan2(Qy_eta_1,Qx_eta_1);
    float Psi_eta_2 = Qeta2.Phi()/2.0;//0.5*atan2(Qy_eta_2,Qx_eta_2);
    float diff_Psi_ran = Psi_ran_1 - Psi_ran_2;
    float diff_Psi_eta = Psi_eta_1 - Psi_eta_2;
    //if(diff_Psi_ran<0.0) diff_Psi_ran+=pi;
    //if(diff_Psi_eta<0.0) diff_Psi_eta+=pi;
    res_ran->Fill(cos(2.0*diff_Psi_ran));
    res_eta->Fill(cos(2.0*diff_Psi_eta));
    //calculate v2 observed
    for(int track = 0; track<(ran1counter+ran2counter); track++){
      float tphi = track_phi[track];
      float diff = tphi - 0.5*(atan2( -Qy_tot+sin(2.0*tphi), -Qx_tot+cos(2.0*tphi))+pi);//autocorrelations removed
      if((diff)<0.0)diff+=pi;
      distran->Fill(diff);
      v2ran->Fill(cos(2.0*diff));
    }

    //cout << eta1counter <<"\t";
    for(int track = 0; track<eta1counter; track++){
      float tphi = track_phi_eta1[track];
      float diff = tphi - 0.5*(atan2( -Qy_eta_2, -Qx_eta_2)+pi);//correlate with opposite eta vector
      if((diff)<0.0)diff+=pi;
      disteta->Fill(diff);
      v2eta->Fill(cos(2.0*diff));
    }

    //cout << eta2counter << endl;
    for(int track = 0; track<eta2counter; track++){
      float tphi = track_phi_eta2[track];
      float diff = tphi - 0.5*(atan2( -Qy_eta_1, -Qx_eta_1)+pi);//correlate with opposite eta vector
      if((diff)<0.0)diff+=pi;
      disteta->Fill(diff);
      v2eta->Fill(cos(2.0*diff));
    }

  }

  GmeanReal1->Scale(1.0/nevents);
  GmeanImag1->Scale(1.0/nevents);
  GmeanReal2->Scale(1.0/nevents);
  GmeanImag2->Scale(1.0/nevents);
  GmeanReal3->Scale(1.0/nevents);
  GmeanImag3->Scale(1.0/nevents);
  GmeanReal4->Scale(1.0/nevents);
  GmeanImag4->Scale(1.0/nevents);

  for(int loopi=0; loopi<100; loopi++){
    float rval = (0.5 + (float)loopi)*1.3*r0exp/100.;
    float Real1 = GhistReal1->GetBinContent(loopi+1);
    float Imag1 = GhistImag1->GetBinContent(loopi+1);
    float Real2 = GhistReal2->GetBinContent(loopi+1);
    float Imag2 = GhistImag2->GetBinContent(loopi+1);
    float Real3 = GhistReal3->GetBinContent(loopi+1);
    float Imag3 = GhistImag3->GetBinContent(loopi+1);
    float Real4 = GhistReal4->GetBinContent(loopi+1);
    float Imag4 = GhistImag4->GetBinContent(loopi+1);
    TComplex G1 = TComplex(Real1,Imag1);
    TComplex G2 = TComplex(Real2,Imag2);
    TComplex G3 = TComplex(Real3,Imag3);
    TComplex G4 = TComplex(Real4,Imag4);
    
    TComplex prod1 = TComplex(0,0);
    TComplex prod2 = TComplex(0,0);
    TComplex prod3 = TComplex(0,0);
    TComplex prod4 = TComplex(0,0);
    
    prod1 = G1;
    prod2 = G2;
    prod3 = G3;
    prod4 = G4;
    //prod1 = G1*G1;
    //prod2 = G2*G2;
    //prod3 = G3*G3;
    //prod4 = G4*G4;
    
    GhistSquareReal1->SetBinContent(loopi+1, fabs(prod1.Re()));
    GhistSquareImag1->SetBinContent(loopi+1, fabs(prod1.Im()));
    GhistSquareReal2->SetBinContent(loopi+1, fabs(prod2.Re()));
    GhistSquareImag2->SetBinContent(loopi+1, fabs(prod2.Im()));
    GhistSquareReal3->SetBinContent(loopi+1, fabs(prod3.Re()));
    GhistSquareImag3->SetBinContent(loopi+1, fabs(prod3.Im()));
    GhistSquareReal4->SetBinContent(loopi+1, fabs(prod4.Re()));
    GhistSquareImag4->SetBinContent(loopi+1, fabs(prod4.Im()));
  }
  
  TCanvas *Gcan = new TCanvas("Gcan","Gcan",0,0,850,1100);
  Gcan->Divide(2,4);
  Gcan->cd(1);
  GhistSquareReal1->Draw();
  Gcan->cd(2);
  GhistSquareImag1->Draw();
  Gcan->cd(3);
  GhistSquareReal2->Draw();
  Gcan->cd(4);
  GhistSquareImag2->Draw();
  Gcan->cd(5);
  GhistSquareReal3->Draw();
  Gcan->cd(6);
  GhistSquareImag3->Draw();
  Gcan->cd(7);
  GhistSquareReal4->Draw();
  Gcan->cd(8);
  GhistSquareImag4->Draw();

  TCanvas *can = new TCanvas("can","can",0,0,800,1000);
  can->Divide(2,3);
  can->cd(1);
  res_ran->Draw("e");
  can->cd(2);
  res_eta->Draw("e");
  can->cd(3);
  distran->Draw("e");
  can->cd(4);
  disteta->Draw("e");
  can->cd(5);
  v2ran->Draw("e");
  can->cd(6);
  v2eta->Draw("e");

  float rr = sqrt(2.0*res_ran->GetMean());
  float re = sqrt(res_eta->GetMean());

  float v2ran_obs = v2ran->GetMean();
  float v2eta_obs = v2eta->GetMean();

  cout << "****************************************************" << endl;
  cout << "Results for Ntracks = " << ntracks << ", Npairs = " << npairs << ", and Nevents = " << nevents <<endl; 
  cout << "************\tRandom ***\tEtasub ***" << endl;
  cout << "resolution  \t" << rr << "\t" << re << endl;
  cout << "v2 observed \t" << v2ran_obs << "\t" << v2eta_obs << endl;
  cout << "v2 corrected\t" << v2ran_obs/rr << "\t" << v2eta_obs/re << endl;
}
