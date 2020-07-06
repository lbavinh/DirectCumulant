/***************************************************************************
 *
 * Author: Ilya Selyuzhenkov (WSU) ilya.selyuzhenkov@gmail.com
 *
 ***************************************************************************
 *
 * Description:  simulating edetector effects
 *
 ***************************************************************************
 *
 * initial revision 2007/07/23
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

const int nHarmonic = 7;

const float	pi = 2.*acos(0.);
const float	phi1 = pi/3.;
const float	phi2 = pi/2.+pi/3.;
const float  v[nHarmonic] = {1.,0.,0.06,0.,0.,0.,0.};


void simulateAcceptance(
	TString outFileName = "out.root",
	Int_t		numberOfEvents = 10000,
	int nTracks = 100
)
{
	char * macroName = "simulateAcceptance: ";

	float Sab[nHarmonic+10], Cab[nHarmonic+10];
	for (int i=1; i<nHarmonic+10; i++){
		Sab[i]  = cos (i*phi1)-cos (i*0.);
		Sab[i]+= cos (i*(pi+phi1))-cos (i*phi2);
		Sab[i]+= cos (i*2.*pi) - cos (i*(pi+phi2));
		Sab[i]  = -Sab[i]/(i*2.*(pi+phi1-phi2));
		Cab[i]  = sin (i*phi1)-sin (i*0.);
		Cab[i]+= sin (i*(pi+phi1))-sin (i*phi2);
		Cab[i]+= sin (i*2.*pi) - sin (i*(pi+phi2));
		Cab[i]  = Cab[i]/(i*2.*(pi+phi1-phi2));
		cout << macroName << "sin(" << i<<"*phi) = "<<Sab[i]<<"; " << "cos(" << i<<"*phi) = "<<Cab[i]<<endl;
	}

	TString flowDist = "1.";
	 for (int i=1; i<nHarmonic; i++){
	 	flowDist+= "+2.*[";flowDist+=i;flowDist+="]";
	 	flowDist+="*cos("; flowDist+= i; flowDist+=".*(x-[0]))";
	 }
	cout << macroName << flowDist <<endl;
	TF1*	flow = new TF1("flow", flowDist, 0., 2.*pi);
	for (int i=0; i<nHarmonic; i++){flow->SetParameter(i,v[i]);}
	Float_t	psi_RP;
	Float_t	phi;
	float		X[nHarmonic];
	float		Y[nHarmonic];
	float		var_nTuple[2*nHarmonic+2];

	TH1D	*phiDist			= new TH1D("phiDist","phiDist",300,0.,2*pi);
	TH1D	*cos2PhiDist		= new TH1D("cos2PhiDist","cos2PhiDist",300,-1.,1.);
	TH1D	*sin2PhiDist			= new TH1D("sin2PhiDist","sin2PhiDist",300,-1.,1.);
	TRandom *generator		= new TRandom();generator->SetSeed(0);

	TFile		*outFile = new TFile(outFileName,"RECREATE");
	cout << macroName<< "outFileName " << outFileName << endl;
	TString nTupleVarList = "";
	for (int i=0; i<nHarmonic; i++){
		nTupleVarList+="X";
		nTupleVarList+=i;
		nTupleVarList+=":";
	}
	for (int i=0; i<nHarmonic; i++){
		nTupleVarList+="Y";
		nTupleVarList+=i;
		nTupleVarList+=":";
	}
	nTupleVarList+="eventId";
	nTupleVarList+=":psiRP";
	cout << macroName << nTupleVarList <<endl;

	TNtuple *simulatedNtuple	= new TNtuple ("simulatedNtuple", "simulatedNtuple", nTupleVarList);

	cout << macroName << "Starting simulations" << endl;

	for (int eventId = 0 ; eventId < numberOfEvents; eventId++)
	{
		for (int i=0; i<nHarmonic; i++){X[i]=0.;Y[i]=0.;}
		psi_RP = 2.*pi*generator->Rndm();
		flow->SetParameter(0,psi_RP);
		for (int iTracks; iTracks < nTracks; iTracks++)
		{
			phi = flow->GetRandom();
			if ((phi>phi1 && phi<phi2) || (phi>phi1+pi && phi<phi2+pi)) continue;
			for (int i=0; i<nHarmonic; i++){X[i]+=cos(i*phi);Y[i]+=sin(i*phi);}
			phiDist->Fill(phi);
			cos2PhiDist->Fill(cos(2*phi));
			sin2PhiDist->Fill(sin(2*phi));
		}
		for (int i=0; i<nHarmonic; i++){var_nTuple[i]=X[i];var_nTuple[i+nHarmonic]=Y[i];}
		var_nTuple[2*nHarmonic] = eventId;
		var_nTuple[2*nHarmonic+1] = psi_RP;
		simulatedNtuple->Fill(var_nTuple);
	}
	outFile->cd();
	simulatedNtuple->Write();
	phiDist->Write();
	cos2PhiDist->Write();
	sin2PhiDist->Write();
	outFile->Write();
	cout << macroName<< "Done simulations" << endl;
	cout << macroName<< "Output written to " << outFile->GetName() << endl;
	outFile->Close();
}
