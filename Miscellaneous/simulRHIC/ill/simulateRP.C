/***************************************************************************
 *
 * $Id: simulateRP.C,v 1.1 2004/10/22  $
 *
 * Author: Ilya Selyuzhenkov, WSU, seluzhen@physics.wayne.edu
 *
 ***************************************************************************
 *
 * Description:  simulating event plane from FTPC's/TPC and ZDC SMD
 *
 ***************************************************************************
 *
 * $Log: simulateRP.C,v $
 *
 * Revision 1.1  2005/03/10
 * initial revision
 *
 **************************************************************************/

#include <TROOT.h>
#include <istream>
#include <sstream>
#include <ostream>
#include <string>
#include <TChain.h>
#include "TText.h"                                                           
#include <TFile.h>
#include "TF1.h"
#include "TTimer.h"
#include "TTime.h"
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

const int		numberOfObserved = 14;

void simulateRP(
			Float_t*	simVN,//[12],
			Float_t*	simVNErr,//[12],
			Int_t		randomSeed =0,
			Int_t		numberOfEvents = 100000, 
			const int	numberParticles=200,
			Int_t		numberOfNeutrons =30,
			Float_t	v1in = 0.05,
			Float_t	v2in = 0.05,
			Float_t	v1neutron	= 0.01,
			Float_t	zdcX =1.,
			Float_t	zdcY =3.,
			Float_t	varphiMin =2./3.,
			Float_t	varphiMax =1.,
			TString	outFileName = "simulatedRP",
			Float_t	sigmaFtpcX =1.,
			Float_t	sigmaFtpcY =1.,
			Float_t	Xmean =0.,
			Float_t	Ymean =0.
			)
{
	Float_t	X[3][2], Xnoise[3][2], Y[3][2], Xw[3][2], Yw[3][2];
	Float_t	Xzdc[2], Yzdc[2], XnoiseZdc[2];
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
	TProfile	*profilev2_obs		= new TProfile("profilev2_obs","profilev2_obs",1,0.,1.);
	TProfile	*profileResolution2	= new TProfile("profileResolution2","profileResolution2",1,0.,1.);
	TProfile	*profilev1mixed_obs	= new TProfile("profilev1mixed_obs","profilev1mixed_obs",1,0.,1.);
	TProfile	*profileResolutionMixed	= new TProfile("profileResolutionMixed","profileResolutionMixed",1,0.,1.);
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
	TRandom	*generator		= new TRandom();generator->SetSeed(randomSeed);
//	TRandom	*varphiGenerator[numberParticles];
//		for(int i=0;i< numberParticles;i++){varphiGenerator[i] = new TRandom();varphiGenerator[i]->SetSeed(i+randomSeed);}
//	TRandom	*ptGeneratorX[numberOfNeutrons];
//		for(int i=0;i< numberOfNeutrons;i++){ptGeneratorX[i] = new TRandom();ptGeneratorX[i]->SetSeed(i+numberParticles+randomSeed);}
//	TRandom	*ptGeneratorY[numberOfNeutrons];
//		for(int i=0;i< numberOfNeutrons;i++){ptGeneratorY[i] = new TRandom();ptGeneratorY[i]->SetSeed(i+numberParticles+numberOfNeutrons+randomSeed);}
//	TRandom	*psi_RPGenerator		= new TRandom();psi_RPGenerator->SetSeed(numberParticles+2*numberOfNeutrons+1+randomSeed);
//	TRandom	*subeventGenerator	= new TRandom();subeventGenerator->SetSeed(numberParticles+2*numberOfNeutrons+2+randomSeed);
//	TRandom	*rejectGenerator		= new TRandom();rejectGenerator->SetSeed(numberParticles+2*numberOfNeutrons+3+randomSeed);
//	TRandom	*zdcGenerator[2];
//		zdcGenerator[0]	= new TRandom();zdcGenerator[0]->SetSeed(numberParticles+2*numberOfNeutrons+4+randomSeed);
//		zdcGenerator[1]	= new TRandom();zdcGenerator[1]->SetSeed(numberParticles+2*numberOfNeutrons+5+randomSeed);
	Float_t		ptX, ptY, ptXnoise;
	Float_t		ptMean	= 0.;
	Float_t		ptBeam	= 5.;
	Float_t		ptSigma	= 5.;
	Float_t		ptXzdcMin[2]	= {- zdcX, -zdcX};
	Float_t		ptXzdcMax[2]	= {zdcX, zdcX};
	Float_t		ptYzdcMin[2]	= {-zdcY, -zdcY };
	Float_t		ptYzdcMax[2]	= {zdcY, zdcY};
	
//	TF1 *centroidZdc = new TF1("centroidZdc","exp(-((x-[0])/[1])**2/2.)", centroidMin, centroidMax);

	cout << endl << "------------ SIMULATING" << endl;
	cout << "------------ number Of events = " << numberOfEvents << endl;
	cout << "------------ number of neutrons in ZDC = " << numberOfNeutrons << endl;
	cout << "------------ number of particles in FTPC = " << numberParticles << endl;
	cout << "------------ v1 = " << v1in <<endl << "------------ v2 = " << v2in<< "; vZdc = " << v1neutron << endl;
	cout << "------------ zdcXcut = " << zdcX << " ;  zdcYcut = " << zdcY  << endl <<endl;
	// comment lines below if don't need to fill ntuples
		//TString	outFileName = "simulatedRP"; 
		outFileName += "v1_"; outFileName += int(100.*v1in); outFileName += "v2_"; outFileName += int(100.*v2in); outFileName += ".root";
		TFile		*outFile = new TFile(outFileName,"RECREATE");
		Float_t	toNtuple[23];
		cout << "outFileName " << outFileName << endl;
		TNtuple	*simulatedNtuple		= new TNtuple ("simulatedNtuple", "simulatedNtuple", 
			"X1a:Y1a:Xw1a:Yw1a:X2a:Y2a:M1a:Mw1a:M2a:X1b:Y1b:Xw1b:Yw1b:X2b:Y2b:M1b:Mw1b:M2b:XeZ:YeZ:XwZ:YwZ:psi_RP");
	//
	for (int eventId = 0 ; eventId < numberOfEvents; eventId++)
	{
//		psi_RP = 2.*pi*psi_RPGenerator->Rndm();
		psi_RP = 2.*pi*generator->Rndm();
		for (int i=0;i<3;i++){for(int j=0;j<2;j++){X[i][j]=0.;Y[i][j]=0.;Xnoise[i][j]=0.;Xw[i][j]=0.;Yw[i][j]=0.;}}
//		for (int i=0;i<int(rejectGenerator->Gaus(38.,10.));i++)
		for (int i=0;i<int(generator->Gaus(38.,10.));i++)
		{
			// FTPC
//			subeventNumber = subeventGenerator->Rndm() > 0.5 ? 0:1;
			subeventNumber = generator->Rndm() > 0.5 ? 0:1;
//			varphi = 2.*pi*varphiGenerator[i]->Rndm();
			varphi = 2.*pi*generator->Rndm();
/*
			X[1][subeventNumber] = X[1][subeventNumber] + Xmean + sigmaFtpcX*cos(varphi) + v1in*cos(psi_RP);
			Y[1][subeventNumber] = Y[1][subeventNumber] + Ymean + sigmaFtpcY*sin(varphi) + v1in*sin(psi_RP);
			Xnoise[1][subeventNumber] = Xnoise[1][subeventNumber]+Xmean + sigmaFtpcX*cos(varphi);
			varphi = 2.*pi*generator->Rndm();
			X[2][subeventNumber] = X[2][subeventNumber] + Xmean + sigmaFtpcX*cos(2*varphi) + v2in*cos(2*psi_RP);
			Y[2][subeventNumber] = Y[2][subeventNumber] + Ymean + sigmaFtpcY*sin(2*varphi) + v2in*sin(2*psi_RP);
			X[0][subeventNumber] = X[0][subeventNumber] + 1.;
			Xnoise[0][subeventNumber] = Xnoise[0][subeventNumber] + 1.;
*/
			Xnoise[1][subeventNumber] = Xnoise[1][subeventNumber]+Xmean + sigmaFtpcX*cos(varphi);
			varphi = varphi - 2*v1in*sin(varphi - psi_RP) - v2in*sin(2.*(varphi - psi_RP));
			X[1][subeventNumber] = X[1][subeventNumber] + Xmean + sigmaFtpcX*cos(varphi);
			Y[1][subeventNumber] = Y[1][subeventNumber] + Ymean + sigmaFtpcY*sin(varphi);
			Xnoise[0][subeventNumber] = Xnoise[0][subeventNumber] + 1;
			X[0][subeventNumber] = X[0][subeventNumber] + 1;
		}
		for (int i=0;i<int(generator->Gaus(38.,10.));i++)
		{
			// TPC
			subeventNumber = generator->Rndm() > 0.5 ? 0:1;
			varphi = 2.*pi*generator->Rndm();
			varphi = varphi - 2*v1in*sin(varphi - psi_RP) - v2in*sin(2.*(varphi - psi_RP));
			X[2][subeventNumber] = X[2][subeventNumber] + Xmean + sigmaFtpcX*cos(2*varphi);
			Y[2][subeventNumber] = Y[2][subeventNumber] + Ymean + sigmaFtpcY*sin(2*varphi);
			Y[0][subeventNumber] = Y[0][subeventNumber] + 1;
		}
		// simulating different resolution for FTPC
		for (int i=0;i<int(generator->Gaus(38.,10.));i++)
		{
			// FTPC
			subeventNumber = generator->Rndm() > 0.5 ? 0:1;
			varphi = 2.*pi*generator->Rndm();
			if (varphi > pi*varphiMin && varphi < pi*varphiMax) continue;
			varphi = varphi - 2*v1in*sin(varphi - psi_RP) - v2in*sin(2.*(varphi - psi_RP));
			Xw[1][subeventNumber] = Xw[1][subeventNumber] + Xmean + sigmaFtpcX*cos(varphi);
			Yw[1][subeventNumber] = Yw[1][subeventNumber] + Ymean + sigmaFtpcY*sin(varphi);
			Xw[0][subeventNumber] = Xw[0][subeventNumber] + 1;
		}
		for (int i=0;i<int(generator->Gaus(38.,10.));i++)
		{
			// TPC
			subeventNumber = generator->Rndm() > 0.5 ? 0:1;
			varphi = 2.*pi*generator->Rndm();
			if (varphi > pi*varphiMin && varphi < pi*varphiMax) continue;
			varphi = varphi - 2*v1in*sin(varphi - psi_RP) - v2in*sin(2.*(varphi - psi_RP));
			Xw[2][subeventNumber] = Xw[2][subeventNumber] + Xmean + sigmaFtpcX*cos(2*varphi);
			Yw[2][subeventNumber] = Yw[2][subeventNumber] + Ymean + sigmaFtpcY*sin(2*varphi);
			Yw[0][subeventNumber] = Yw[0][subeventNumber] + 1;
		}
		// simulating ZDC SMD
		for (int i=0;i<2;i++){Xzdc[i]=0.;Yzdc[i]=0.;}
		for (int i=0;i<numberOfNeutrons; i++)
		{
			for (int j=0;j<2;j++)
			{
//				ptX = ptGeneratorX[i]->Gaus(ptMean, ptSigma)+ ptBeam*v1neutron*cos(psi_RP);
//				ptY = ptGeneratorY[i]->Gaus(ptMean, ptSigma)+ ptBeam*v1neutron*sin(psi_RP);
				ptX = generator->Gaus(ptMean, ptSigma);
				ptXnoise = ptX;
				if (ptXnoise > ptXzdcMin[j] && ptXnoise < ptXzdcMax[j])	XnoiseZdc[j] = XnoiseZdc[j] + ptXnoise; 
				ptX = ptX + ptBeam*v1neutron*cos(psi_RP);
				if (ptX > ptXzdcMin[j] && ptX < ptXzdcMax[j])	Xzdc[j] = Xzdc[j] + ptX; 
				ptY = generator->Gaus(ptMean, ptSigma)+ ptBeam*v1neutron*sin(psi_RP);
				if (ptY > ptYzdcMin[j] && ptY < ptYzdcMax[j])	Yzdc[j] = Yzdc[j] + ptY; 
			}
		}
		if (X[0][0]!=0&&X[0][1]!=0)
		{
			profilevN_Xobs		->Fill(0.5,sqrt(2.)*X[1][0]*X[1][1]/X[0][0]);
			profileResolutionX		->Fill(0.5,X[1][0]*X[1][1]);
			profilevN_Yobs		->Fill(0.5,sqrt(2.)*Y[1][0]*Y[1][1]/X[0][0]);
			profileResolutionY		->Fill(0.5,Y[1][0]*Y[1][1]);
			profilevN_obs		->Fill(0.5,(X[1][0]*X[1][1]+Y[1][0]*Y[1][1])/X[0][0]);
			profileResolution		->Fill(0.5,X[1][0]*X[1][1]+Y[1][0]*Y[1][1]);
//			profilev2_obs		->Fill(0.5,(X[2][0]*X[2][1]+Y[2][0]*Y[2][1])/(X[0][0]*X[0][1]));
//			profileResolution2		->Fill(0.5,(X[2][0]*X[2][1]+Y[2][0]*Y[2][1])/(X[0][0]*X[0][1]));
//			profilev1mixed_obs	
//				->Fill(0.5,(X[1][0]*X[1][1]*X[2][subEvent] - Y[1][0]*Y[1][1]*X[2][subEvent]+ Y[1][0]*X[1][1]*Y[2][subEvent] + X[1][0]*Y[1][1]*Y[2][subEvent])/(X[0][0]*X[0][1]*X[0][subEvent]));
//			profileResolutionMixed	
//				->Fill(0.5,(X[1][0]*X[1][1]*X[2][subEvent] - Y[1][0]*Y[1][1]*X[2][subEvent]+ Y[1][0]*X[1][1]*Y[2][subEvent] + X[1][0]*Y[1][1]*Y[2][subEvent])/(X[0][0]*X[0][1]*X[0][subEvent]));
			profilevN_XNoiseobs	->Fill(0.5,(Xnoise[1][0]*Xnoise[1][1]+Y[1][0]*Y[1][1])/Xnoise[0][0]);
			profileResolutionXNoise	->Fill(0.5,Xnoise[1][0]*Xnoise[1][1]+Y[1][0]*Y[1][1]);
			profilevN_nObs		->Fill(0.5,(X[1][0]*cos(atan2(Y[1][1], X[1][1]))+Y[1][0]*sin(atan2(Y[1][1], X[1][1])))/X[0][0]);
			profileResolutionN		->Fill(0.5,cos(atan2(Y[1][0],X[1][0])-atan2(Y[1][1], X[1][1])));
			profilevN_nNoiseObs	->Fill(0.5,(Xnoise[1][0]*cos(atan2(Y[1][1], Xnoise[1][1]))+Y[1][0]*sin(atan2(Y[1][1], Xnoise[1][1])))/Xnoise[0][0]);
			profileResolutionNNoise	->Fill(0.5,cos(atan2(Y[1][0],Xnoise[1][0])-atan2(Y[1][1], Xnoise[1][1])));
		}
		int subEvent =1;
		if (X[0][0]!=0&&X[0][1]!=0&&Y[0][0]!=0&&Y[0][1]!=0)
		{
			profilev1mixed_obs	->Fill(0.5,(X[1][0]*X[1][1]*X[2][subEvent] - Y[1][0]*Y[1][1]*X[2][subEvent]+ Y[1][0]*X[1][1]*Y[2][subEvent] + X[1][0]*Y[1][1]*Y[2][subEvent])/X[0][0]);
			profileResolutionMixed	->Fill(0.5, X[1][0]*X[1][1]*X[2][subEvent] - Y[1][0]*Y[1][1]*X[2][subEvent]+ Y[1][0]*X[1][1]*Y[2][subEvent] + X[1][0]*Y[1][1]*Y[2][subEvent]);
		}
		if (Y[0][0]!=0&&Y[0][1]!=0)
		{
			profilev2_obs		->Fill(0.5,(X[2][0]*X[2][1]+Y[2][0]*Y[2][1])/Y[0][0]);
			profileResolution2		->Fill(0.5,X[2][0]*X[2][1]+Y[2][0]*Y[2][1]);
		}
		if (X[0][0]!=0 && Xzdc[0]!=0 && Yzdc[0]!=0)
		{
			profilevN_obsZdc			->Fill(0.5,(X[1][0]*Xzdc[1]+Y[1][0]*Yzdc[1])/X[0][0]);
			profileResolutionZdc		->Fill(0.5, Xzdc[0]*Xzdc[1]+Yzdc[0]*Yzdc[1]);
			profilevN_XNoiseobsZdc		->Fill(0.5,(X[1][0]*XnoiseZdc[1]+Y[1][0]*Yzdc[1])/X[0][0]);
			profileResolutionXNoiseZdc	->Fill(0.5,XnoiseZdc[0]*XnoiseZdc[1]+Yzdc[0]*Yzdc[1]);
			profilevN_nObsZdc		->Fill(0.5,(X[1][0]*cos(atan2(Yzdc[1], Xzdc[1]))+Y[1][0]*sin(atan2(Yzdc[1], Xzdc[1])))/X[0][0]);
			profileResolutionNZdc		->Fill(0.5,cos(atan2(Yzdc[0],Xzdc[0])-atan2(Yzdc[1], Xzdc[1])));
			profilevN_nNoiseObsZdc		->Fill(0.5,(X[1][0]*cos(atan2(Yzdc[1], XnoiseZdc[1]))+Y[1][0]*sin(atan2(Yzdc[1], XnoiseZdc[1])))/X[0][0]);
			profileResolutionNNoiseZdc	->Fill(0.5,cos(atan2(Yzdc[0],XnoiseZdc[0])-atan2(Yzdc[1], XnoiseZdc[1])));
		}
		if (X[0][0]!=0 && Xzdc[0]!=0)
		{
			profilevN_XobsZdc		->Fill(0.5,sqrt(2.)*X[1][0]*Xzdc[1]/X[0][0]);
			profileResolutionXZdc		->Fill(0.5,Xzdc[0]*Xzdc[1]);
		}
		if (X[0][0]!=0 && Yzdc[0]!=0)
		{
			profilevN_YobsZdc		->Fill(0.5,sqrt(2.)*Y[1][0]*Yzdc[1]/X[0][0]);
			profileResolutionYZdc		->Fill(0.5,Yzdc[0]*Yzdc[1]);
		}
		// filling ntuple	"X1a:Y1a:Xw1a:Yw1a:X2a:Y2a:M1a:Mw1a:M2a:X1b:Y1b:Xw1b:Yw1b:X2b:Y2b:M1b:Mw1b:M2b:XeZ:YeZ:XwZ:YwZ:psi_RP:varphi"
		// sub a
		toNtuple[0] = X[1][0];
		toNtuple[1] = Y[1][0];
		toNtuple[2] = Xw[1][0];
		toNtuple[3] = Yw[1][0];
		toNtuple[4] = X[2][0];
		toNtuple[5] = Y[2][0];
		toNtuple[6] = X[0][0];
		toNtuple[7] = Xw[0][0];
		toNtuple[8] = Y[0][0];
		// sub b
		toNtuple[9] = X[1][1];
		toNtuple[10] = Y[1][1];
		toNtuple[11] = Xw[1][1];
		toNtuple[12] = Yw[1][1];
		toNtuple[13] = X[2][1];
		toNtuple[14] = Y[2][1];
		toNtuple[15] = X[0][1];
		toNtuple[16] = Xw[0][1];
		toNtuple[17] = Y[0][1];
		// zdc smd
		toNtuple[18] = Xzdc[0];
		toNtuple[19] = Yzdc[0];
		toNtuple[20] = Xzdc[1];
		toNtuple[21] = Yzdc[1];
		
		toNtuple[22] = psi_RP;
		simulatedNtuple->Fill(toNtuple);
	}
	outFile->cd();
	simulatedNtuple->Write();
	outFile->Write();
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
	v_obsList->AddAt(profilev2_obs, 12);
	v_obsList->AddAt(profilev1mixed_obs, 13);
	
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
	resolutionList->AddAt(profileResolution2,12);
	resolutionList->AddAt(profileResolutionMixed,13);
	
	char	*v_obsNames[numberOfObserved]={"v_cos    ", "v_cosNoise", "v_XY    ", "v_X    ", "v_Y    ", "v_Noise","v_cosZdc    ", "v_cosNoiseZdc", "v_XYZdc    ", "v_XZdc    ", "v_YZdc    ", "v_NoiseZdc", "v_2     ", "v1mixed    "};
	Float_t v2, v2err;
	for (int i =0; i< numberOfObserved;i++)
	{
		if (i == 0 ) cout << "------------  FTPC  ------------" << endl;
		if (i == 6 ) cout << "------------  ZDC  ------------" << endl;
		if (i == 12) cout << "------------  TPC  ------------" << endl;
		vN_obs		= ((TProfile*)v_obsList->At(i))->GetBinContent(nBin);
		vN_error		= ((TProfile*)v_obsList->At(i))->GetBinError(nBin);
		resolution		= sqrt(fabs(((TProfile*)resolutionList->At(i))->GetBinContent(nBin)));
		resolution_error	= ((TProfile*)resolutionList->At(i))->GetBinError(nBin)/(2.0*resolution);
		vNs		= vN_obs/resolution;
		vNsErr	=  fabs(vN_error/resolution) + fabs(resolution_error*vN_obs/pow(resolution,2));
		if( i == 12) {v2 = resolution; v2err = resolution_error; cout << "v2 = " << v2 << "; v2 err = " << v2err<<endl;}
		if (i == 13)
		{
			cout << "vmixed_obs = " << vN_obs << "; vmixed_obs  resolution = " << resolution <<endl;
			vN_obs		= vNs;
			vN_error		= vNsErr;
			resolution		= sqrt(fabs(v2));
			resolution_error	= fabs(v2err/(2.0*resolution));
			vNs			= vN_obs/resolution;
			vNsErr		= fabs(vN_error/resolution) + fabs(resolution_error*vN_obs/pow(resolution,2));
		}
		simVN[i]	= vNs;
		simVNErr[i]	= vNsErr;
		cout	<< v_obsNames[i] << " 	" << vNs 
			<< " ERR " << 100.*fabs(vNsErr/vNs)
			<< "% 	res	" << resolution
			<< " ERR " << 100.*fabs(resolution_error/resolution)
			<< "%	vObs	" << vN_obs 
			<< " ERR " << 100.*fabs(vN_error/vN_obs) << "%" << endl;
	}
		
//	for(int i=0;i< numberParticles;i++){varphiGenerator[i]->Delete();}
	profilevN_Xobs		->Delete();
	profileResolutionX		->Delete();
	profilevN_XNoiseobs	->Delete();
	profileResolutionXNoise	->Delete();
	profilevN_Yobs		->Delete();
	profileResolutionY		->Delete();
	profilevN_obs		->Delete();
	profileResolution		->Delete();
	profilev2_obs		->Delete();
	profileResolution2		->Delete();
	profilev1mixed_obs	->Delete();
	profileResolutionMixed	->Delete();
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

//	psi_RPGenerator		->Delete();
//	rejectGenerator 		->Delete();

//	centroidZdc			->Delete();
}
void plotSim(
			Int_t		numberOfEvents = 100000, 
			const int	numberParticles=200,
			Int_t		numberOfNeutrons =30,
			Float_t	v1in = 0.05,
			Float_t	v2in = 0.05,
			Float_t	v1neutron	= 0.05,
			Int_t		nZdc =10,
			char		*outFileName = "simulationAzdc.root",
			Float_t	varphiMin =2./3.,
			Float_t	varphiMax =1.,
			Float_t	aZdcXmin = 0.1,
			Float_t	aZdcYmin = 0.1,
			Float_t	aZdcXmax = 8.,
			Float_t	aZdcYmax = 8.
		)
{
	TTimer	*timer	= new TTimer();
	long int	time = timer->GetTime();
	TRandom	*randomSeen	= new TRandom();randomSeen->SetSeed(time);
	TFile		*outFile	= new TFile(outFileName, "RECREATE");
	TH2F		*v_Xzdc	=new TH2F("v_Xzdc","v_Xzdc",nZdc,aZdcXmin, aZdcXmax, nZdc, aZdcYmin, aZdcYmax);
	TH2F		*v_Yzdc	=new TH2F("v_Yzdc","v_Yzdc",nZdc,aZdcXmin, aZdcXmax, nZdc, aZdcYmin, aZdcYmax);
	TH2F		*v_XYzdc	=new TH2F("v_XYzdc","v_XYzdc",nZdc,aZdcXmin, aZdcXmax, nZdc, aZdcYmin, aZdcYmax);
	TH2F		*v_cosZdc	=new TH2F("v_cosZdc","v_cosZdc",nZdc,aZdcXmin, aZdcXmax, nZdc, aZdcYmin, aZdcYmax);	
	Float_t	simVN[numberOfObserved];
	Float_t	simVNErr[numberOfObserved];
	Float_t	aZdcX =0;
	Float_t	aZdcY =0;
	for (int i=0; i < nZdc; i++)
	{
		if (nZdc!=1) {aZdcY =aZdcYmin + i*(aZdcYmax-aZdcYmin)/(nZdc-1.);}else{aZdcY = (aZdcYmax - aZdcYmin)/2.;}
		for (int j=0; j < nZdc; j++)
		{
			if (nZdc!=1) {aZdcX =aZdcXmin + j*(aZdcXmax-aZdcXmin)/(nZdc-1.);}else{aZdcX = (aZdcXmax - aZdcXmin)/2.;}
			simulateRP(simVN, simVNErr, int(100*randomSeen->Rndm()), numberOfEvents, numberParticles, numberOfNeutrons, v1in, v2in, v1neutron, aZdcX, aZdcY, varphiMin, varphiMax, outFileName);
			v_Xzdc->SetBinContent(i+1, j+1, simVN[9]);
			v_Xzdc->SetBinError(i+1, j+1, simVNErr[9]);
			v_Yzdc->SetBinContent(i+1, j+1, simVN[10]);
			v_Yzdc->SetBinError(i+1, j+1, simVNErr[10]);
			v_XYzdc->SetBinContent(i+1, j+1, simVN[8]);
			v_XYzdc->SetBinError(i+1, j+1, simVNErr[8]);
			v_cosZdc->SetBinContent(i+1, j+1, simVN[6]);
			v_cosZdc->SetBinError(i+1, j+1, simVNErr[6]);
		}
	}
	v_Xzdc->SetDrawOption("surf");
	v_Yzdc->SetDrawOption("surf");
	v_XYzdc->SetDrawOption("surf");
	v_cosZdc->SetDrawOption("surf");
	
	v_Xzdc->Write();
	v_Yzdc->Write();
	v_XYzdc->Write();
	v_cosZdc->Write();
	cout << "Output written to " << outFile->GetName() << endl;
	outFile->Close();
}

void mixedVSv1v2(
			Int_t		numberOfEvents = 100000, 
			Int_t		nPoints =10,
			const int	numberParticles=200,
			Int_t		numberOfNeutrons =30,
			char		*outFileName = "mixedVSv1v2.root",
			Float_t	vMax =0.1,
			Float_t	varphiMin =2./3.,
			Float_t	varphiMax =1.
		)
{	
	TTimer	*timer	= new TTimer();
	long int	time = timer->GetTime();
	TRandom	*randomSeed	= new TRandom();randomSeed->SetSeed(time);
	Float_t	simVN[numberOfObserved];
	Float_t	simVNErr[numberOfObserved];
	TH2F		*v1Mixed	= new TH2F("v1Mixed","v1Mixed",nPoints,0., vMax, nPoints, 0., vMax);
	TH2F		*v2		= new TH2F("v2","v2",nPoints,0., vMax, nPoints, 0., vMax);
	TFile		*outFile	= new TFile(outFileName, "RECREATE");
	for (int j =0; j < nPoints; j++)
	{
		for (int i =0; i < nPoints; i++)
		{
			simulateRP(simVN, simVNErr, int(100*randomSeed->Rndm()), numberOfEvents, numberParticles, numberOfNeutrons, vMax*i/(nPoints-1.), vMax*j/(nPoints-1.), varphiMin, varphiMax);
			v2->SetBinContent(i+1,j+1,simVN[12]);
			v2->SetBinError(i+1,j+1,simVNErr[12]);
			v1Mixed->SetBinContent(i+1,j+1,simVN[13]);
			v1Mixed->SetBinError(i+1,j+1,simVNErr[13]);
		}
	}
	v1Mixed->Write();
	v2->Write();
	cout << "Output written to " << outFile->GetName() << endl;
	outFile->Close();
}
