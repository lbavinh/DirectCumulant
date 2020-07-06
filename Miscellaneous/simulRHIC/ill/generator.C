#include <fstream.h>
#include "iostream.h"
#include <string>
#include "TNtuple.h"
#include "TFile.h"
#include "TF1.h"
#include "TF2.h"
#include "TLorentzVector.h"

void generator(int maxNumberOfPoints=100000,char* fileName = "results/gp.root")
{
	char* macroName = "GP generator: ";
	cout << macroName << "STARTING generator" << endl;
	TFile *file = new TFile(fileName, "RECREATE");
	gROOT->cd();
	TNtuple * globPolSim = new TNtuple("globPolSim","globPolSim","pLambda_x:pLambda_y:pLambda_z:pProton_x:pProton_y:pProton_z:ptProtonStar:thetaProtonStar:phiProtonStar:psiRP");
	float pi			= acos(-1.);
	float massLambda	= 1.115;
	float massProton		= 0.938;
	float massPion		= 0.137;
	float T			= 0.26;
	float ptMax			= 5.0;
	float alpha_Lambda	= 0.642;
	float v1 			= 0.; //0.05;
	float v2 			= 0.; //0.1;
	// Reaction plane angle distribution: flat
	TF1 *psiRP_dist = new TF1("psiRP_dist","1./(2.*[0])", 0, 2.*pi);
	psiRP_dist->FixParameter(0, pi);
	// Lambda p_t distribution: A*p_t*exp(-m_T/T)
	TF1 *pt_dist = new TF1("pt_dist","[0]/(2.*[3])*x*exp(-sqrt(x^2+[2]^2)/[1])", 0., ptMax);
	pt_dist->FixParameter(0, 50.);
	pt_dist->FixParameter(1, T);
	pt_dist->FixParameter(2, massLambda);
	pt_dist->FixParameter(3, pi);
	// Lambda eta distribution: flat
	TF1 *eta_dist = new TF1("eta_dist","0.5",-1.,1.);
	// Lambda phi distribution: flat
	TF1 *phi_dist = new TF1("phi_dist","1./(2.*[0])*(1+2.*[1]*cos(x-[3])+2.*[2]*cos(2.*(x-[3])))", 0., 2.*pi);
	phi_dist->FixParameter(0, pi);
	phi_dist->FixParameter(1, v1);
	phi_dist->FixParameter(2, v2);
	// Polarization distribution theta^*_p and phi^*_p: (1+alpha_H*P_H*sin(theta^*_p)*sin(phi^*_p-psi_RP))/(4pi)
	TF2 *thetaPstar_dist = new TF2("thetaPstar_dist","(1.+[0]*[1]*sin(x)*sin(y-[2]))*sin(x)/(4.*[3])", 0., pi, 0., 2.*pi);
	thetaPstar_dist->FixParameter(0, alpha_Lambda);
	thetaPstar_dist->FixParameter(3, pi);

	// Polarization distribution theta^* and phi^*: (1+alpha_H*P_H*cos(theta*))/(4pi)
	TF1 *thetaStar_dist = new TF1("thetaStar_dist","(1.+[0]*[1]*cos(x))*sin(x)/2.", 0., pi);
	thetaStar_dist->FixParameter(0, alpha_Lambda);
	TF1 *phiStar_dist = new TF1("phiStar_dist","1./(4.*[0])", -2.*pi, 2.*pi);
	phiStar_dist->FixParameter(0, pi);
	for (int i =0 ; i < maxNumberOfPoints; i++)
	{
		if (i%100==0) cout << macroName << i << " processed" << endl;
		Double_t psi_RP 		= psiRP_dist	->GetRandom();
		Double_t ptH		= pt_dist	->GetRandom();
		Double_t etaH		= eta_dist	->GetRandom();
		phi_dist->SetParameter(3, psi_RP);
		Double_t phiH		= phi_dist	->GetRandom();
		TLorentzVector	mom4p;
		TLorentzVector	mom4lambda;
		TLorentzVector	mom4boosted;
		mom4lambda.SetPtEtaPhiM(ptH, etaH, phiH, massLambda);
		Double_t phiPstar		= -100;
		Double_t thetaPstar	= -100;
		// Polarization distribution theta^*_p and phi^*_p: (1+alpha_H*P_H*sin(theta^*_p)*sin(phi^*_p-psi_RP))/(4pi)
		thetaPstar_dist->SetParameter(1, ptH/ptMax);
		thetaPstar_dist->SetParameter(2, psi_RP);
		thetaPstar_dist->GetRandom2(thetaPstar, phiPstar);
		// Polarization distribution theta^* and phi^*: (1+alpha_H*P_H*cos(theta*))/(4pi)
		thetaStar_dist->SetParameter(1, ptH/ptMax);
		Double_t thetaStar	=thetaStar_dist->GetRandom();
		Double_t phiStar		=phiStar_dist->GetRandom();

		phiPstar = atan2(
			cos(thetaStar)/sqrt(1.-pow(sin(thetaStar)*cos(phiStar),2)),
			sin(thetaStar)*sin(phiStar)/sqrt(1.-pow(sin(thetaStar)*cos(phiStar),2))
			)+psi_RP;
		thetaPstar = atan2(sqrt(1.-pow(sin(thetaStar)*cos(phiStar),2)), sin(thetaStar)*cos(phiStar));

//		phiPstar = asin(sin(asin(cos(thetaStar)/sqrt(1.-pow(sin(thetaStar)*cos(phiStar),2)))+psi_RP));
//		thetaPstar = acos(sin(thetaStar)*cos(phiStar));
		// comment 5 lines before to switch off Polarization distribution theta^* and phi^* method
		Double_t pPstar = sqrt(
			(massLambda-massProton-massPion)*(massLambda+massProton+massPion)*
			(massLambda-massProton+massPion)*(massLambda+massProton-massPion)
		)/(2.*massLambda);
		mom4boosted.SetPtEtaPhiM(pPstar*sin(thetaPstar), -log(tan(thetaPstar/2.)), phiPstar, massProton);	//proton 4-momentum in the Lambda rest frame
		mom4p = mom4boosted;
		mom4p.Boost(mom4lambda.BoostVector());	//boosting to the Lambda Lab frame
		globPolSim->Fill(mom4lambda.Px(),mom4lambda.Py(),mom4lambda.Pz(),mom4p.Px(),mom4p.Py(),mom4p.Pz(),pPstar*sin(thetaPstar),thetaPstar,phiPstar,psi_RP);
	}
	file->cd();
	globPolSim->Write();
	file->Close();
	cout << macroName << "DONE generator" << endl;
}
