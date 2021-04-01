/**
 * Elliptic flow v2 measurements using High Order Q-Cumulant with recursion algorithm
 * proposed by Ante Bilandzic in https://dx.doi.org/10.1103/PhysRevC.89.064904
 * coded by Vinh Ba Luong (lbavinh@gmail.com)
 * 25/11/2020
 */
#include <FlowAnalysisWithHighOrderQCumulant.h>
ClassImp(FlowAnalysisWithHighOrderQCumulant);
FlowAnalysisWithHighOrderQCumulant::FlowAnalysisWithHighOrderQCumulant() :
M(0)
{
  for(Int_t c=0;c<maxCorrelator;c++){
    for(Int_t icent=0;icent<ncent;icent++){
      recursion[c][icent] = NULL;
    }
  }
  for (Int_t i=0;i<6;i++){
    for (Int_t c=0;c<ncent;c++){
      pCovariance[i][c] = NULL;
    }
  }

  Zero();
}

FlowAnalysisWithHighOrderQCumulant::~FlowAnalysisWithHighOrderQCumulant()
{
}

void FlowAnalysisWithHighOrderQCumulant::Init()
{
  for(Int_t c=0;c<maxCorrelator;c++){
    for(Int_t icent=0;icent<ncent;icent++){
      recursion[c][icent] = new TProfile(Form("recursion_%i_%i",c,icent),Form("recursion_%i_%i",c,icent),1,0.,1.);
    }
  }
  for (Int_t i=0;i<6;i++){
    for (Int_t c=0;c<ncent;c++){
      pCovariance[i][c] = new TProfile(Form("pCovariance_%i_%i",i,c),Form("pCovariance_%i_%i",i,c),1,0.,1.);
    }
  }

}

void FlowAnalysisWithHighOrderQCumulant::Zero()
{
  M = 0;
  for(Int_t h=0;h<maxHarmonic;h++)
  {
    for(Int_t p=0;p<maxPower;p++)
    {
      Qvector[h][p] = TComplex(0.,0.);
    }
  }
}

void FlowAnalysisWithHighOrderQCumulant::ProcessFirstTrackLoopRP(const Double_t &phi)
{
  for(Int_t h=0;h<maxHarmonic;h++){
    for(Int_t p=0;p<maxPower;p++){
      Qvector[h][p] += TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
    } //  for(Int_t p=0;p<maxPower;p++)
  } // for(Int_t h=0;h<maxHarmonic;h++)
  M++;
}


void FlowAnalysisWithHighOrderQCumulant::ProcessEventAfterFirstTrackLoop(const Int_t &icent)
{
  if (M>=8)
  {
    // e) Calculate n-particle correlations from Q-vectors (using recursion):
    Int_t harmonics_Two_Num[2] = {h1,h2};       
    Int_t harmonics_Two_Den[2] = {0,0};       
    TComplex twoRecursion = Recursion(2,harmonics_Two_Num)/Recursion(2,harmonics_Two_Den).Re();
    Double_t wTwoRecursion = Recursion(2,harmonics_Two_Den).Re();
    recursion[0][icent]->Fill(0.5,twoRecursion.Re(),wTwoRecursion); // <<cos(h1*phi1+h2*phi2)>>

    Int_t harmonics_Four_Num[4] = {h1,h2,h3,h4};       
    Int_t harmonics_Four_Den[4] = {0,0,0,0};       
    TComplex fourRecursion = Recursion(4,harmonics_Four_Num)/Recursion(4,harmonics_Four_Den).Re();
    Double_t wFourRecursion = Recursion(4,harmonics_Four_Den).Re();
    recursion[2][icent]->Fill(0.5,fourRecursion.Re(),wFourRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>

    Int_t harmonics_Six_Num[6] = {h1,h2,h3,h4,h5,h6};       
    Int_t harmonics_Six_Den[6] = {0,0,0,0,0,0};       
    TComplex sixRecursion = Recursion(6,harmonics_Six_Num)/Recursion(6,harmonics_Six_Den).Re();
    Double_t wSixRecursion = Recursion(6,harmonics_Six_Den).Re();
    recursion[4][icent]->Fill(0.5,sixRecursion.Re(),wSixRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
  
    Int_t harmonics_Eight_Num[8] = {h1,h2,h3,h4,h5,h6,h7,h8};       
    Int_t harmonics_Eight_Den[8] = {0,0,0,0,0,0,0,0};       
    TComplex eightRecursion = Recursion(8,harmonics_Eight_Num)/Recursion(8,harmonics_Eight_Den).Re();
    Double_t wEightRecursion = Recursion(8,harmonics_Eight_Den).Re();
    recursion[6][icent]->Fill(0.5,eightRecursion.Re(),wEightRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>

    pCovariance[0][icent]->Fill(0.5,twoRecursion.Re()*fourRecursion.Re(),wTwoRecursion*wFourRecursion);
    pCovariance[1][icent]->Fill(0.5,twoRecursion.Re()*sixRecursion.Re(),wTwoRecursion*wSixRecursion);
    pCovariance[2][icent]->Fill(0.5,twoRecursion.Re()*eightRecursion.Re(),wTwoRecursion*wEightRecursion);
    pCovariance[3][icent]->Fill(0.5,fourRecursion.Re()*sixRecursion.Re(),wFourRecursion*wSixRecursion);
    pCovariance[4][icent]->Fill(0.5,fourRecursion.Re()*eightRecursion.Re(),wFourRecursion*wEightRecursion);
    pCovariance[5][icent]->Fill(0.5,sixRecursion.Re()*eightRecursion.Re(),wSixRecursion*wEightRecursion);    
  }
}

void FlowAnalysisWithHighOrderQCumulant::SaveHist()
{
  for(Int_t c=0;c<maxCorrelator;c++){
    for(Int_t icent=0;icent<ncent;icent++){
      recursion[c][icent]->Write();
    }
  }
  for (Int_t i=0;i<6;i++){
    for (Int_t c=0;c<ncent;c++){
      pCovariance[i][c]->Write();
    }
  }
}

TComplex FlowAnalysisWithHighOrderQCumulant::Q(Int_t n, Int_t p)
{
 // Using the fact that Q{-n,p} = Q{n,p}^*. 
 
 if(n>=0){return Qvector[n][p];} 
 return TComplex::Conjugate(Qvector[-n][p]);
 
} // TComplex Q(Int_t n, Int_t p)

TComplex FlowAnalysisWithHighOrderQCumulant::Recursion(Int_t n, Int_t* harmonic, Int_t mult /*= 1*/, Int_t skip /*= 0*/) 
{
 // Calculate multi-particle correlators by using recursion (an improved faster version) originally developed by 
 // Kristjan Gulbrandsen (gulbrand@nbi.dk). 

  Int_t nm1 = n-1;
  TComplex c(Q(harmonic[nm1], mult));
  if (nm1 == 0) return c;
  c *= Recursion(nm1, harmonic);
  if (nm1 == skip) return c;

  Int_t multp1 = mult+1;
  Int_t nm2 = n-2;
  Int_t counter1 = 0;
  Int_t hhold = harmonic[counter1];
  harmonic[counter1] = harmonic[nm2];
  harmonic[nm2] = hhold + harmonic[nm1];
  TComplex c2(Recursion(nm1, harmonic, multp1, nm2));
  Int_t counter2 = n-3;
  while (counter2 >= skip) {
    harmonic[nm2] = harmonic[counter1];
    harmonic[counter1] = hhold;
    ++counter1;
    hhold = harmonic[counter1];
    harmonic[counter1] = harmonic[nm2];
    harmonic[nm2] = hhold + harmonic[nm1];
    c2 += Recursion(nm1, harmonic, multp1, counter2);
    --counter2;
  }
  harmonic[nm2] = harmonic[counter1];
  harmonic[counter1] = hhold;

  if (mult == 1) return c-c2;
  return c-Double_t(mult)*c2;

} // TComplex AliFlowAnalysisWithMultiparticleCorrelations::Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0)
