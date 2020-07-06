#include <TROOT.h>
#include <istream>
#include <sstream>
#include <ostream>
#include <string>
#include <TChain.h>
#include "TText.h"                                                           
#include <TFile.h>
#include "TF1.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "iostream.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TNtuple.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TRandom.h"

void simulateRP(	Int_t		numberOfEvents = 100000, 
			const int	numberParticles=200,
			Float_t	vN = 0.05,
			Float_t	aZdcXeast =0.25,
			Float_t	aZdcYeast =0.12,
			Float_t	sigmaFtpcX =1.,
			Float_t	sigmaFtpcY =1.,
			Float_t	sigmaZdcEast =1.,
			Float_t	sigmaZdcWest =1.,
			Float_t	Xmean =0.,
			Float_t	Ymean =0.,
			Float_t	XmeanZdcEast =0.,
			Float_t	XmeanZdcWest =0.,
			Float_t	YmeanZdcEast =0.,
			Float_t	YmeanZdcWest =0.,
			Int_t		nHarmonic=1,
			char		*outFileName = "simulatedRP.root")
{
	TFile *outFile = new TFile(outFileName,"RECREATE");
	Float_t	X[2][2], Xnoise[2][2], Y[2][2];
	Float_t	Xzdc[2], Yzdc[2], XnoiseZdc[2], sigmaZdc[2], XmeanZdc[2], YmeanZdc[2], aZdcX[2], aZdcY[2];
	Float_t	psi_RP;
	Float_t	varphi;
	Float_t	pi = 3.14;
	Float_t	vNs;
	Float_t	vNsErr;
	Float_t	vN_obs;
	Float_t	vN_error;
	Float_t	resolution;
	Float_t	resolution_error;
	Int_t		subeventNumber;

	TProfile	*profilevN_obs		= new TProfile("profilevN_obs","profilevN_obs",1,0.,1.);
	TProfile	*profileResolution		= new TProfile("profileResolution","profileResolution",1,0.,1.);
	TProfile	*profilevN_Xobs		= new TProfile("profilevN_Xobs","profilevN_Xobs",1,0.,1.);
	TProfile	*profileResolutionX	= new TProfile("profileResolutionX","profileResolutionX",1,0.,1.);
	TProfile	*profilevN_XNoiseobs	= new TProfile("profilevN_XNoiseobs","profilevN_XNoiseobs",1,0.,1.);
	TProfile	*profileResolutionXNoise = new TProfile("profileResolutionXNoise","profileResolutionXNoise",1,0.,1.);
	TProfile	*profilevN_Yobs		= new TProfile("profilevN_Yobs","profilevN_Yobs",1,0.,1.);
	TProfile	*profileResolutionY	= new TProfile("profileResolutionY","profileResolutionY",1,0.,1.);
	TProfile	*profilevN_nObs		= new TProfile("profilevN_nObs","profilevN_nObs",1,0.,1.);
	TProfile	*profileResolutionN	= new TProfile("profileResolutionN","profileResolutionN",1,0.,1.);
	TProfile	*profilevN_nNoiseObs	= new TProfile("profilevN_nNoiseObs","profilevN_nNoiseObs",1,0.,1.);
	TProfile	*profileResolutionNNoise = new TProfile("profileResolutionNNoise","profileResolutionNNoise",1,0.,1.);

	TProfile	*profilevN_obsZdc		= new TProfile("profilevN_obsZdc","profilevN_obsZdc",1,0.,1.);
	TProfile	*profileResolutionZdc		= new TProfile("profileResolutionZdc","profileResolutionZdc",1,0.,1.);
	TProfile	*profilevN_XobsZdc		= new TProfile("profilevN_XobsZdc","profilevN_XobsZdc",1,0.,1.);
	TProfile	*profileResolutionXZdc		= new TProfile("profileResolutionXZdc","profileResolutionXZdc",1,0.,1.);
	TProfile	*profilevN_XNoiseobsZdc	= new TProfile("profilevN_XNoiseobsZdc","profilevN_XNoiseobsZdc",1,0.,1.);
	TProfile	*profileResolutionXNoiseZdc 	= new TProfile("profileResolutionXNoiseZdc","profileResolutionXNoiseZdc",1,0.,1.);
	TProfile	*profilevN_YobsZdc		= new TProfile("profilevN_YobsZdc","profilevN_YobsZdc",1,0.,1.);
	TProfile	*profileResolutionYZdc		= new TProfile("profileResolutionYZdc","profileResolutionYZdc",1,0.,1.);
	TProfile	*profilevN_nObsZdc		= new TProfile("profilevN_nObsZdc","profilevN_nObsZdc",1,0.,1.);
	TProfile	*profileResolutionNZdc		= new TProfile("profileResolutionNZdc","profileResolutionNZdc",1,0.,1.);
	TProfile	*profilevN_nNoiseObsZdc	= new TProfile("profilevN_nNoiseObsZdc","profilevN_nNoiseObsZdc",1,0.,1.);
	TProfile	*profileResolutionNNoiseZdc 	= new TProfile("profileResolutionNNoiseZdc","profileResolutionNNoiseZdc",1,0.,1.);
	TRandom	*varphiGenerator[numberParticles];
		for(int i=0;i< numberParticles;i++){varphiGenerator[i] = new TRandom();varphiGenerator[i]->SetSeed(i);}
	TRandom	*psi_RPGenerator		= new TRandom();psi_RPGenerator->SetSeed(numberParticles+1);
	TRandom	*subeventGenerator	= new TRandom();subeventGenerator->SetSeed(numberParticles+2);
	TRandom	*rejectGenerator		= new TRandom();rejectGenerator->SetSeed(numberParticles+3);
	TRandom	*zdcGenerator[2];
		zdcGenerator[0]	= new TRandom();zdcGenerator[0]->SetSeed(numberParticles+4);
		zdcGenerator[1]	= new TRandom();zdcGenerator[1]->SetSeed(numberParticles+5);
	
	TNtuple	*simulatedNtuple		= new TNtuple ("simulatedNtuple", "simulatedNtuple", "Xa:Ya:XaNoise:Ma:Xb:Yb:XbNoise:Mb:XzdcEast:YzdcEast:XzdcWest:YzdcWest:psi_RP:varphi");
	
	cout << endl << "------------ SIMULATING" << endl;
	sigmaZdc[0]		= - sigmaZdcEast;
	sigmaZdc[1]		= sigmaZdcWest;
	XmeanZdc[0]	= XmeanZdcEast;
	XmeanZdc[1]	= XmeanZdcWest;
	YmeanZdc[0]	= YmeanZdcEast;
	YmeanZdc[1]	= YmeanZdcWest;
	aZdcX[0]		= - aZdcXeast;
	aZdcX[1]		= aZdcXeast;
	aZdcY[0]		= - aZdcYeast;
	aZdcY[1]		= aZdcYeast;
	for (int eventId = 0 ; eventId < numberOfEvents; eventId++)
	{
		psi_RP = 2.*pi*psi_RPGenerator->Rndm();
		for (int i=0;i<2;i++){for(int j=0;j<2;j++){X[i][j]=0.;Y[i][j]=0.;Xnoise[i][j]=0.;}}
		for (int i=0;i<int(rejectGenerator->Gaus(38.,10.));i++)
		{
			subeventNumber = subeventGenerator->Rndm() > 0.5 ? 0:1;
			varphi = 2.*pi*varphiGenerator[i]->Rndm();
			X[1][subeventNumber] = X[1][subeventNumber] + Xmean + sigmaFtpcX*cos(nHarmonic*varphi) + vN*cos(nHarmonic*psi_RP);
			Y[1][subeventNumber] = Y[1][subeventNumber] + Ymean + sigmaFtpcY*sin(nHarmonic*varphi) + vN*sin(nHarmonic*psi_RP);
			X[0][subeventNumber] = X[0][subeventNumber] + 1.;
			Xnoise[1][subeventNumber] = Xnoise[1][subeventNumber]+Xmean + sigmaFtpcX*cos(nHarmonic*varphi);
			Xnoise[0][subeventNumber] = Xnoise[0][subeventNumber] + 1.;
		}
		for (int i=0;i<2;i++)
		{
			zdcGenerator[i]->Rannor(Xzdc[i],Yzdc[i]); 
			XnoiseZdc[i] = XmeanZdc[i] + sigmaZdc[i]*Xzdc[i];
			Xzdc[i] = XmeanZdc[i] + sigmaZdc[i]*Xzdc[i] + aZdcX[i]*cos(psi_RP);
			Yzdc[i] = YmeanZdc[i] + sigmaZdc[i]*Yzdc[i] + aZdcY[i]*sin(psi_RP);
		}
		if (X[0][0]!=0&&X[0][1]!=0)
		{
			profilevN_Xobs		->Fill(0.5,X[1][0]*X[1][1]/X[0][0]);
			profileResolutionX		->Fill(0.5,X[1][0]*X[1][1]);
			profilevN_Yobs		->Fill(0.5,Y[1][0]*Y[1][1]/X[0][0]);
			profileResolutionY		->Fill(0.5,Y[1][0]*Y[1][1]);
			profilevN_obs		->Fill(0.5,(X[1][0]*X[1][1]+Y[1][0]*Y[1][1])/X[0][0]);
			profileResolution		->Fill(0.5,X[1][0]*X[1][1]+Y[1][0]*Y[1][1]);
			profilevN_XNoiseobs	->Fill(0.5,(Xnoise[1][0]*Xnoise[1][1]+Y[1][0]*Y[1][1])/Xnoise[0][0]);
			profileResolutionXNoise	->Fill(0.5,Xnoise[1][0]*Xnoise[1][1]+Y[1][0]*Y[1][1]);
			profilevN_nObs		->Fill(0.5,(X[1][0]*cos(atan2(Y[1][1], X[1][1]))+Y[1][0]*sin(atan2(Y[1][1], X[1][1])))/X[0][0]);
			profileResolutionN		->Fill(0.5,cos(atan2(Y[1][0],X[1][0])-atan2(Y[1][1], X[1][1])));
			profilevN_nNoiseObs	->Fill(0.5,(Xnoise[1][0]*cos(atan2(Y[1][1], Xnoise[1][1]))+Y[1][0]*sin(atan2(Y[1][1], Xnoise[1][1])))/Xnoise[0][0]);
			profileResolutionNNoise	->Fill(0.5,cos(atan2(Y[1][0],Xnoise[1][0])-atan2(Y[1][1], Xnoise[1][1])));
		}
		if (X[0][0]!=0)
		{
			profilevN_XobsZdc		->Fill(0.5,X[1][0]*Xzdc[1]/X[0][0]);
			profileResolutionXZdc		->Fill(0.5,Xzdc[0]*Xzdc[1]);
			profilevN_YobsZdc		->Fill(0.5,Y[1][0]*Yzdc[1]/X[0][0]);
			profileResolutionYZdc		->Fill(0.5,Yzdc[0]*Yzdc[1]);
			profilevN_obsZdc			->Fill(0.5,(X[1][0]*Xzdc[1]+Y[1][0]*Yzdc[1])/X[0][0]);
			profileResolutionZdc		->Fill(0.5, Xzdc[0]*Xzdc[1]+Yzdc[0]*Yzdc[1]);
			profilevN_XNoiseobsZdc		->Fill(0.5,(X[1][0]*XnoiseZdc[1]+Y[1][0]*Yzdc[1])/X[0][0]);
			profileResolutionXNoiseZdc	->Fill(0.5,XnoiseZdc[0]*XnoiseZdc[1]+Yzdc[0]*Yzdc[1]);
			profilevN_nObsZdc		->Fill(0.5,(X[1][0]*cos(atan2(Yzdc[1], Xzdc[1]))+Y[1][0]*sin(atan2(Yzdc[1], Xzdc[1])))/X[0][0]);
			profileResolutionNZdc		->Fill(0.5,cos(atan2(Yzdc[0],Xzdc[0])-atan2(Yzdc[1], Xzdc[1])));
			profilevN_nNoiseObsZdc		->Fill(0.5,(X[1][0]*cos(atan2(Yzdc[1], XnoiseZdc[1]))+Y[1][0]*sin(atan2(Yzdc[1], XnoiseZdc[1])))/X[0][0]);
			profileResolutionNNoiseZdc	->Fill(0.5,cos(atan2(Yzdc[0],XnoiseZdc[0])-atan2(Yzdc[1], XnoiseZdc[1])));
		}
		simulatedNtuple->Fill(X[1][0], Y[1][0], Xnoise[1][0], X[0][0], X[1][1], Y[1][1], Xnoise[1][1], X[0][1], Xzdc[0], Yzdc[0], Xzdc[1], Yzdc[1], psi_RP, varphi);
		 
	}
	cout << "------------ DONE SIMULATIONS" << endl;

	int nBin =1;

	TList	*v_obsList= new TList();
	v_obsList->SetName("v_obsList");
	v_obsList->AddAt(profilevN_nObs, 0);
	v_obsList->AddAt(profilevN_nNoiseObs, 1);
	v_obsList->AddAt(profilevN_obs, 2);
	v_obsList->AddAt(profilevN_Xobs, 3);
	v_obsList->AddAt(profilevN_Yobs, 4);
	v_obsList->AddAt(profilevN_XNoiseobs, 5);
	
	v_obsList->AddAt(profilevN_nObsZdc, 6);
	v_obsList->AddAt(profilevN_nNoiseObsZdc, 7);
	v_obsList->AddAt(profilevN_obsZdc, 8);
	v_obsList->AddAt(profilevN_XobsZdc, 9);
	v_obsList->AddAt(profilevN_YobsZdc, 10);
	v_obsList->AddAt(profilevN_XNoiseobsZdc, 11);
	
	TList	*resolutionList= new TList();
	resolutionList->SetName("resolutionList");
	resolutionList->AddAt(profileResolutionN, 0);
	resolutionList->AddAt(profileResolutionNNoise, 1);
	resolutionList->AddAt(profileResolution, 2);
	resolutionList->AddAt(profileResolutionX, 3);
	resolutionList->AddAt(profileResolutionY, 4);
	resolutionList->AddAt(profileResolutionXNoise, 5);
	
	resolutionList->AddAt(profileResolutionNZdc, 6);
	resolutionList->AddAt(profileResolutionNNoiseZdc, 7);
	resolutionList->AddAt(profileResolutionZdc, 8);
	resolutionList->AddAt(profileResolutionXZdc, 9);
	resolutionList->AddAt(profileResolutionYZdc, 10);
	resolutionList->AddAt(profileResolutionXNoiseZdc, 11);
	char	*v_obsNames[12]={"v_cos    ", "v_cosNoise", "v_XY    ", "v_X    ", "v_Y    ", "v_Noise","v_cosZdc    ", "v_cosNoiseZdc", "v_XYZdc    ", "v_XZdc    ", "v_YZdc    ", "v_NoiseZdc"};
		
	cout << endl << "------------ Generated number Of events = " << numberOfEvents << "; nHarmonic ="<< nHarmonic<< "; real v is " << vN<<endl << endl;
	cout	<< endl << "------------ aZdcX = " << aZdcXeast << " ;  aZdcY = " << aZdcYeast 
		<< " ; sigmaFtpcX = "<< sigmaFtpcX << " ; sigmaFtpcY = "<< sigmaFtpcY << endl <<endl;
	aZdcX[0]		= - aZdcXeast;
	aZdcX[1]		= aZdcXeast;
	aZdcY[0]		= - aZdcYeast;
	aZdcY[1]		= aZdcYeast;
	for (int i =0; i< 12;i++)
	{
		if (i ==0 ) cout << "------------  FTPC  ------------" << endl;
		if (i ==6 ) cout << "------------  ZDC  ------------" << endl;
		vN_obs		= ((TProfile*)v_obsList->At(i))->GetBinContent(nBin);
		vN_error		= ((TProfile*)v_obsList->At(i))->GetBinError(nBin);
		resolution		= sqrt(fabs(((TProfile*)resolutionList->At(i))->GetBinContent(nBin)));
		resolution_error	= ((TProfile*)resolutionList->At(i))->GetBinError(nBin)/(2.0*resolution);
		vNs		= vN_obs/resolution;
		vNsErr	=  fabs(vN_error/resolution) + fabs(resolution_error*vN_obs/pow(resolution,2));
		cout	<< v_obsNames[i] << " 	" << vNs 
			<< " ERR " << fabs(vNsErr/vNs)
			<< "% 	res	" << resolution
			<< " ERR " << fabs(resolution_error/resolution)
			<< "%	vObs	" << vN_obs 
			<< " ERR " << fabs(vN_error/vN_obs) << "%" << endl;
	}
		
	outFile->cd();
	simulatedNtuple->Write();
	outFile->Write();

	for(int i=0;i< numberParticles;i++){varphiGenerator[i]->Delete();}
	profilevN_Xobs		->Delete();
	profileResolutionX		->Delete();
	profilevN_XNoiseobs	->Delete();
	profileResolutionXNoise	->Delete();
	profilevN_Yobs		->Delete();
	profileResolutionY		->Delete();
	profilevN_obs		->Delete();
	profileResolution		->Delete();
	profilevN_nObs		->Delete();
	profileResolutionN		->Delete();
	profilevN_nNoiseObs	->Delete();
	profileResolutionNNoise	->Delete();
	
	profilevN_XobsZdc		->Delete();
	profileResolutionXZdc		->Delete();
	profilevN_XNoiseobsZdc		->Delete();
	profileResolutionXNoiseZdc	->Delete();
	profilevN_YobsZdc		->Delete();
	profileResolutionYZdc		->Delete();
	profilevN_obsZdc			->Delete();
	profileResolutionZdc		->Delete();
	profilevN_nObsZdc		->Delete();
	profileResolutionNZdc		->Delete();
	profilevN_nNoiseObsZdc		->Delete();
	profileResolutionNNoiseZdc	->Delete();

	psi_RPGenerator		->Delete();
	rejectGenerator 		->Delete();
	
	outFile->Close();
}

