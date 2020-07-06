
void macro{

// ------



TLorentzVector	mom4pos;
TLorentzVector	mom4neg;
TLorentzVector	mom4v0;
TLorentzVector	mom4boosted;

mom4pos.SetXYZM(V0_mMomPos_fX[nV0Tracks], V0_mMomPos_fY[nV0Tracks], V0_mMomPos_fZ[nV0Tracks], massProton);
mom4neg.SetXYZM(V0_mMomNeg_fX[nV0Tracks], V0_mMomNeg_fY[nV0Tracks], V0_mMomNeg_fZ[nV0Tracks], massPion);

Float_t	v0variables[nVariables];
Float_t	invMass;

mom4v0.SetXYZM(
	V0_mMomPos_fX[nV0Tracks]+V0_mMomNeg_fX[nV0Tracks],
	V0_mMomPos_fY[nV0Tracks]+V0_mMomNeg_fY[nV0Tracks],
	V0_mMomPos_fZ[nV0Tracks]+V0_mMomNeg_fZ[nV0Tracks],
	V0_mMassLambda[nV0Tracks]
);
mom4boosted	= mom4pos;
mom4boosted.Boost(-mom4v0.BoostVector());	//boosting to the Lambda rest frame
invMass = V0_mMassLambda[nV0Tracks];
v0variables[0]	= mom4v0.Pt();
v0variables[1]	= mom4v0.Eta();
v0variables[2]	= mCentrality;

for(int i_variables		= 0 ; i_variables < nVariables;		i_variables++)
{
	if (methodSwitch[0]==1)// STANDARD METHOD
	{
		if(correlationSwitch[0]==1)	// V0 flow/polarization from two particle correlations 
		{
			flowObsV0[0][V0_mTypeOfStrangeParticle[nV0Tracks]][0][0][i_detector][0][i_charge][i_harmonic][i_variables][mCentrality]->Fill(v0variables[i_variables], cos(i_harmonic*mom4v0.Phi())*cos (PSIepAuto));
			flowObsV0[0][V0_mTypeOfStrangeParticle[nV0Tracks]][0][1][i_detector][0][i_charge][i_harmonic][i_variables][mCentrality]->Fill(v0variables[i_variables], sin(i_harmonic*mom4v0.Phi())*sin( PSIepAuto));
			flowObsV0[0][V0_mTypeOfStrangeParticle[nV0Tracks]][0][2][i_detector][0][i_charge][i_harmonic][i_variables][mCentrality]->Fill(v0variables[i_variables], cos(i_harmonic*mom4v0.Phi())*cos(PSIepAuto) + sin(i_harmonic*mom4v0.Phi())*sin(PSIepAuto));
			// V0 polarization
			flowObsV0[0][V0_mTypeOfStrangeParticle[nV0Tracks]][0][0][i_detector][1][i_charge][i_harmonic][i_variables][mCentrality]->Fill(v0variables[i_variables], sin(i_harmonic*mom4boosted.Phi())*cos(PSIepAuto));
			flowObsV0[0][V0_mTypeOfStrangeParticle[nV0Tracks]][0][1][i_detector][1][i_charge][i_harmonic][i_variables][mCentrality]->Fill(v0variables[i_variables], - cos(i_harmonic*mom4boosted.Phi())*sin(PSIepAuto));
			flowObsV0[0][V0_mTypeOfStrangeParticle[nV0Tracks]][0][2][i_detector][1][i_charge][i_harmonic][i_variables][mCentrality]->Fill(v0variables[i_variables], sin(i_harmonic*mom4boosted.Phi())*cos(PSIepAuto) - cos(i_harmonic*mom4boosted.Phi())*sin(PSIepAuto));
		}
	}
}
}