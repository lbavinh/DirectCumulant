/**
 * Dear Arkadij and Ilya,

 * First, let me thank you again for a wonderful time I had in Moscow! 

 * As promised, please find attached the vanilla ROOT macro, which implements the wisdom from https://arxiv.org/abs/1312.3572
 * and which is relevant for the reference flow. For the differential flow analysis, I can send a separate macro, if needed. 

 * In that paper we have demonstrated in toy MC studies in Section IV how to build and use particle weights, to correct
 * for various inefficiencies in the measurements of multiparticle correlators. In the attached macro you can find the most
 * important technology needed to reproduce these MC studies, once your code is validated this way, it can be used in practice
 * in real data analysis as long as you can build particle weights (for instance, if detector has real holes in the acceptance,
 * like PHENIX, then this formalism is NOT applicable). But for ALICE detector, we have used this formalism successfully recently
 * in https://arxiv.org/abs/1604.07663 , to correct with pT- and phi-weights the reconstruction inefficiency as a function of pT and phi, respectively. 

 * The attached macro calculates multiparticle correlators, for hardwired toy example event having 11 particles azimuthal angles and particle weights,
 * and for specified harmonics, in three independent ways: 

 * a) standalone formulas; 
 * b) recursion; 
 * c) nested loops. 

 * Clearly, the last one is only there to cross-check whether a) and b) were calculated and implemented correctly.
 * The a) is faster then b) for correlations having less than 6 particles, but a) cannot be compiled quickly for the case of 7, 8,
 * and higher correlations due to the lengths of standalone formulas for higher order correlators.
 * For any example, a) and b) should always give exactly the same numerical answer, the only difference is in CPU time. 

 * To run this macro in interpreted mode, just execute 

 * root -l GenericFormulas.C
 
 * You can also compile the macro and run it as well, but it takes > 5 min to compile, due to length of standalone formulas ;-) 

 * The main point is that by playing with this macro you can understand how the b) approach works, and then basically you can propagate
 * ONLY that part in your own code (forget for instance about these massive standalone expressions for 7-p and 8-p correlations...),
 * and then you can calculate any multiparticle correlator you want with this recursive algorithm developed by my ex-colleagues at NBI,
 * and by using particle weights to correct for inefficiencies!

 * Particle weights in this macro are hardwired, but how to obtain them in practice it is explained in Section IV of https://arxiv.org/abs/1312.3572 .

 * Cheers,
 * Ante

 */
#include "TComplex.h"
#include "TProfile.h"
#include "TStopwatch.h"
#include "Riostream.h"

// Total number of particles:
const Int_t nParticles = 11;

// Azimuthal angles:
Double_t angles[nParticles] = {6.28156,1.02359,1.77574,5.95144,1.45554,3.04718,6.01601,4.67661,3.39319,4.64926,2.49226};

// Particle weights:
Double_t weights[nParticles] = {1.14393,0.90291,0.93739,1.12879,0.92277,0.99567,1.13175,1.07036,1.01153,1.06911,1.11211};

// Use or not the non-unit particle weights above:
Bool_t bUseWeights = kTRUE; 

// Cross-check with nested loops:
Bool_t bEvaluateNestedLoops = kTRUE;

// Pick up randomly some harmonics:
const Int_t h1=1, h2=3, h3=5, h4=0, h5=-2, h6=-4, h7=-1, h8=-6;

// Book Q-vector components: 
const Int_t sum = (h1<0?-1*h1:h1)+(h2<0?-1*h2:h2)+(h3<0?-1*h3:h3)+(h4<0?-1*h4:h4)
                + (h5<0?-1*h5:h5)+(h6<0?-1*h6:h6)+(h7<0?-1*h7:h7)+(h8<0?-1*h8:h8);
const Int_t maxCorrelator = 8; // We will not go beyond 8-p correlations
const Int_t maxHarmonic = sum+1; 
const Int_t maxPower = maxCorrelator+1; 
TComplex Qvector[maxHarmonic][maxPower]; // All needed Q-vector components

// Store the final results here:
//  Remark: [2][maxCorrelator] => [Cos,Sin][<2>,<3>,<4>,<5>,<6>,<7>,<8>]
TProfile *correlations[2][maxCorrelator] = {{NULL}}; // Correlations calculated from Q-vector componets using standalone formulas
TProfile *recursion[2][maxCorrelator] = {{NULL}}; // Correlations calculated from Q-vector components using recursive algorithm 
TProfile *nestedLoops[2][maxCorrelator] = {{NULL}}; // Correlations calculated from nested loops

//=======================================================================================================================

void Cosmetics()
{
 // Book everything here.
  
 for(Int_t cs=0;cs<2;cs++) 
 {
  for(Int_t c=0;c<maxCorrelator;c++)
  {
   correlations[cs][c] = new TProfile("","",1,0.,1.);
   correlations[cs][c]->Sumw2();
   recursion[cs][c] = new TProfile("","",1,0.,1.);
   recursion[cs][c]->Sumw2();
   nestedLoops[cs][c] = new TProfile("","",1,0.,1.);
   nestedLoops[cs][c]->Sumw2();
  } // end of for(Int_t c=0;c<maxCorrelator;c++)
 } // end of for(Int_t cs=0;cs<2;cs++) 

} // void Cosmetics()

//==========================================================================================================================

void CalculateQvectors()
{
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
 for(Int_t i=0;i<nParticles;i++) // loop over particles
 {
  dPhi = angles[i];
  if(bUseWeights){wPhi = weights[i];}
  for(Int_t h=0;h<maxHarmonic;h++)
  {
   for(Int_t p=0;p<maxPower;p++)
   {
    if(bUseWeights){wPhiToPowerP = pow(wPhi,p);}
    Qvector[h][p] += TComplex(wPhiToPowerP*TMath::Cos(h*dPhi),wPhiToPowerP*TMath::Sin(h*dPhi));
   } //  for(Int_t p=0;p<maxPower;p++)
  } // for(Int_t h=0;h<maxHarmonic;h++)
 } //  for(Int_t i=0;i<nParticles;i++) // loop over particles

} // void CalculateQvectors()

//==========================================================================================================================

TComplex Q(Int_t n, Int_t p)
{
 // Using the fact that Q{-n,p} = Q{n,p}^*. 
 
 if(n>=0){return Qvector[n][p];} 
 return TComplex::Conjugate(Qvector[-n][p]);
 
} // TComplex Q(Int_t n, Int_t p)

//==========================================================================================================================

void TwoNestedLoops(Int_t n1,Int_t n2)
{
 // Calculation of <cos(n1*phi1+n2*phi2)> and <sin(n1*phi1+n2*phi2)>
 // with two nested loops. 

 Double_t phi1=0., phi2=0.; // particle angle
 Double_t w1=1., w2=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 {
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}
   // Fill profiles:
   nestedLoops[0][0]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2),w1*w2);
   nestedLoops[1][0]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2),w1*w2);
  } // for(Int_t i2=0;i2<nParticles;i2++)
 } // for(Int_t i1=0;i1<nParticles;i1++)

} // end of void TwoNestedLoops(Int_t n1,Int_t n2,TArrayD a,TArrayD w)

//==========================================================================================================================

void ThreeNestedLoops(Int_t n1,Int_t n2,Int_t n3)
{
 // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3)> and <sin(n1*phi1+n2*phi2+n3*phi3)>
 // with three nested loops. 

 Double_t phi1=0., phi2=0., phi3=0.; // particle angle
 Double_t w1=1., w2=1., w3=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 { 
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}
   for(Int_t i3=0;i3<nParticles;i3++)
   {
    if(i3==i1||i3==i2){continue;} // Get rid of autocorrelations
    phi3 = angles[i3];
    if(bUseWeights){w3 = weights[i3];}
    // Fill the profiles:
    nestedLoops[0][1]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3),w1*w2*w3);
    nestedLoops[1][1]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2+n3*phi3),w1*w2*w3);
   } // end of for(Int_t i3=0;i3<nParticles;i3++)
  } // end of for(Int_t i2=0;i2<nParticles;i2++)
 } // end of for(Int_t i1=0;i1<nParticles;i1++)

} // end of void ThreeNestedLoops(Int_t n1,Int_t n2,TArrayD a,TArrayD w)

//==========================================================================================================================

void FourNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4)
{
 // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4)> and 
 // <sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4)> with four nested loops. 

 Double_t phi1=0., phi2=0., phi3=0., phi4=0.; // particle angle
 Double_t w1=1., w2=1., w3=1., w4=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 { 
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}
   for(Int_t i3=0;i3<nParticles;i3++)
   {
    if(i3==i1||i3==i2){continue;} // Get rid of autocorrelations
    phi3 = angles[i3];
    if(bUseWeights){w3 = weights[i3];}
    for(Int_t i4=0;i4<nParticles;i4++)
    {
     if(i4==i1||i4==i2||i4==i3){continue;} // Get rid of autocorrelations
     phi4 = angles[i4];
     if(bUseWeights){w4 = weights[i4];}
     // Fill the profiles:
     nestedLoops[0][2]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4),w1*w2*w3*w4);
     nestedLoops[1][2]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4),w1*w2*w3*w4);
    } // end of for(Int_t i4=0;i4<nParticles;i4++) 
   } // end of for(Int_t i3=0;i3<nParticles;i3++)
  } // end of for(Int_t i2=0;i2<nParticles;i2++)
 } // end of for(Int_t i1=0;i1<nParticles;i1++)

} // end of void FourNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4)

//==========================================================================================================================

void FiveNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5)
{
 // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5)> and 
 // <sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5)> with five nested loops. 

 Double_t phi1=0., phi2=0., phi3=0., phi4=0., phi5=0.; // particle angle
 Double_t w1=1., w2=1., w3=1., w4=1., w5=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 { 
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}
   for(Int_t i3=0;i3<nParticles;i3++)
   {
    if(i3==i1||i3==i2){continue;} // Get rid of autocorrelations
    phi3 = angles[i3];
    if(bUseWeights){w3 = weights[i3];}
    for(Int_t i4=0;i4<nParticles;i4++)
    {
     if(i4==i1||i4==i2||i4==i3){continue;} // Get rid of autocorrelations
     phi4 = angles[i4];
     if(bUseWeights){w4 = weights[i4];}
     for(Int_t i5=0;i5<nParticles;i5++)
     {
      if(i5==i1||i5==i2||i5==i3||i5==i4){continue;} // Get rid of autocorrelations
      phi5 = angles[i5];
      if(bUseWeights){w5 = weights[i5];}
      // Fill the profiles:
      nestedLoops[0][3]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5),w1*w2*w3*w4*w5);
      nestedLoops[1][3]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5),w1*w2*w3*w4*w5);
     } // end of for(Int_t i5=0;i5<nParticles;i5++)
    } // end of for(Int_t i4=0;i4<nParticles;i4++) 
   } // end of for(Int_t i3=0;i3<nParticles;i3++)
  } // end of for(Int_t i2=0;i2<nParticles;i2++)
 } // end of for(Int_t i1=0;i1<nParticles;i1++)

} // end of void FiveNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5)

//==========================================================================================================================

void SixNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5,Int_t n6)
{
 // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6)> and 
 // <sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6)> with six nested loops. 

 Double_t phi1=0., phi2=0., phi3=0., phi4=0., phi5=0., phi6=0.; // particle angle
 Double_t w1=1., w2=1., w3=1., w4=1., w5=1., w6=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 { 
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}
   for(Int_t i3=0;i3<nParticles;i3++)
   {
    if(i3==i1||i3==i2){continue;} // Get rid of autocorrelations
    phi3 = angles[i3];
    if(bUseWeights){w3 = weights[i3];}
    for(Int_t i4=0;i4<nParticles;i4++)
    {
     if(i4==i1||i4==i2||i4==i3){continue;} // Get rid of autocorrelations
     phi4 = angles[i4];
     if(bUseWeights){w4 = weights[i4];}
     for(Int_t i5=0;i5<nParticles;i5++)
     {
      if(i5==i1||i5==i2||i5==i3||i5==i4){continue;} // Get rid of autocorrelations
      phi5 = angles[i5];
      if(bUseWeights){w5 = weights[i5];}
      for(Int_t i6=0;i6<nParticles;i6++)
      {
       if(i6==i1||i6==i2||i6==i3||i6==i4||i6==i5){continue;} // Get rid of autocorrelations
       phi6 = angles[i6];
       if(bUseWeights){w6 = weights[i6];}
       // Fill the profiles:
       nestedLoops[0][4]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6),w1*w2*w3*w4*w5*w6);
       nestedLoops[1][4]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6),w1*w2*w3*w4*w5*w6);
      } // end of for(Int_t i6=0;i6<nParticles;i6++)
     } // end of for(Int_t i5=0;i5<nParticles;i5++)
    } // end of for(Int_t i4=0;i4<nParticles;i4++) 
   } // end of for(Int_t i3=0;i3<nParticles;i3++)
  } // end of for(Int_t i2=0;i2<nParticles;i2++)
 } // end of for(Int_t i1=0;i1<nParticles;i1++)

} // void SixNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5,Int_t n6)

//==========================================================================================================================

void SevenNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5,Int_t n6,Int_t n7)
{
 // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7)> and 
 // <sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7)> with seven nested loops. 

 Double_t phi1=0., phi2=0., phi3=0., phi4=0., phi5=0., phi6=0., phi7=0.; // particle angle
 Double_t w1=1., w2=1., w3=1., w4=1., w5=1., w6=1., w7=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 { 
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}  
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}  
   for(Int_t i3=0;i3<nParticles;i3++)
   {
    if(i3==i1||i3==i2){continue;} // Get rid of autocorrelations
    phi3 = angles[i3];
    if(bUseWeights){w3 = weights[i3];}  
    for(Int_t i4=0;i4<nParticles;i4++)
    {
     if(i4==i1||i4==i2||i4==i3){continue;} // Get rid of autocorrelations
     phi4 = angles[i4];
     if(bUseWeights){w4 = weights[i4];}  
     for(Int_t i5=0;i5<nParticles;i5++)
     {
      if(i5==i1||i5==i2||i5==i3||i5==i4){continue;} // Get rid of autocorrelations
      phi5 = angles[i5];
      if(bUseWeights){w5 = weights[i5];}  
      for(Int_t i6=0;i6<nParticles;i6++)
      {
       if(i6==i1||i6==i2||i6==i3||i6==i4||i6==i5){continue;} // Get rid of autocorrelations
       phi6 = angles[i6];
       if(bUseWeights){w6 = weights[i6];}  
       for(Int_t i7=0;i7<nParticles;i7++)
       {
        if(i7==i1||i7==i2||i7==i3||i7==i4||i7==i5||i7==i6){continue;} // Get rid of autocorrelations
        phi7 = angles[i7];
        if(bUseWeights){w7 = weights[i7];}  
        // Fill the profiles:
        nestedLoops[0][5]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7),w1*w2*w3*w4*w5*w6*w7);
        nestedLoops[1][5]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7),w1*w2*w3*w4*w5*w6*w7);
       } // end of for(Int_t i7=0;i7<nParticles;i7++)
      } // end of for(Int_t i6=0;i6<nParticles;i6++)
     } // end of for(Int_t i5=0;i5<nParticles;i5++)
    } // end of for(Int_t i4=0;i4<nParticles;i4++) 
   } // end of for(Int_t i3=0;i3<nParticles;i3++)
  } // end of for(Int_t i2=0;i2<nParticles;i2++)
 } // end of for(Int_t i1=0;i1<nParticles;i1++)

} // void SevenNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5,Int_t n6,Int_t n7)

//==========================================================================================================================

void EightNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5,Int_t n6,Int_t n7,Int_t n8)
{
 // Calculation of <cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)> and 
 // <sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)> with eight nested loops. 

 Double_t phi1=0., phi2=0., phi3=0., phi4=0., phi5=0., phi6=0., phi7=0., phi8=0.; // particle angle
 Double_t w1=1., w2=1., w3=1., w4=1., w5=1., w6=1., w7=1., w8=1.; // particle weight
 for(Int_t i1=0;i1<nParticles;i1++)
 { 
  phi1 = angles[i1];
  if(bUseWeights){w1 = weights[i1];}  
  for(Int_t i2=0;i2<nParticles;i2++)
  {
   if(i2==i1){continue;} // Get rid of autocorrelations
   phi2 = angles[i2];
   if(bUseWeights){w2 = weights[i2];}  
   for(Int_t i3=0;i3<nParticles;i3++)
   {
    if(i3==i1||i3==i2){continue;} // Get rid of autocorrelations
    phi3 = angles[i3];
    if(bUseWeights){w3 = weights[i3];}  
    for(Int_t i4=0;i4<nParticles;i4++)
    {
     if(i4==i1||i4==i2||i4==i3){continue;} // Get rid of autocorrelations
     phi4 = angles[i4];
     if(bUseWeights){w4 = weights[i4];}  
     for(Int_t i5=0;i5<nParticles;i5++)
     {
      if(i5==i1||i5==i2||i5==i3||i5==i4){continue;} // Get rid of autocorrelations
      phi5 = angles[i5];
      if(bUseWeights){w5 = weights[i5];}  
      for(Int_t i6=0;i6<nParticles;i6++)
      {
       if(i6==i1||i6==i2||i6==i3||i6==i4||i6==i5){continue;} // Get rid of autocorrelations
       phi6 = angles[i6];
       if(bUseWeights){w6 = weights[i6];}  
       for(Int_t i7=0;i7<nParticles;i7++)
       {
        if(i7==i1||i7==i2||i7==i3||i7==i4||i7==i5||i7==i6){continue;} // Get rid of autocorrelations
        phi7 = angles[i7];
        if(bUseWeights){w7 = weights[i7];}  
        for(Int_t i8=0;i8<nParticles;i8++)
        {
         if(i8==i1||i8==i2||i8==i3||i8==i4||i8==i5||i8==i6||i8==i7){continue;} // Get rid of autocorrelations
         phi8 = angles[i8];
         if(bUseWeights){w8 = weights[i8];}  
         // Fill the profiles:
         nestedLoops[0][6]->Fill(0.5,TMath::Cos(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8),w1*w2*w3*w4*w5*w6*w7*w8);
         nestedLoops[1][6]->Fill(0.5,TMath::Sin(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8),w1*w2*w3*w4*w5*w6*w7*w8);
        } // end of for(Int_t i8=0;i8<nParticles;i8++) 
       } // end of for(Int_t i7=0;i7<nParticles;i7++)
      } // end of for(Int_t i6=0;i6<nParticles;i6++)
     } // end of for(Int_t i5=0;i5<nParticles;i5++)
    } // end of for(Int_t i4=0;i4<nParticles;i4++) 
   } // end of for(Int_t i3=0;i3<nParticles;i3++)
  } // end of for(Int_t i2=0;i2<nParticles;i2++)
 } // end of for(Int_t i1=0;i1<nParticles;i1++)

} // void EightNestedLoops(Int_t n1,Int_t n2,Int_t n3,Int_t n4,Int_t n5,Int_t n6,Int_t n7,Int_t n8)

//==========================================================================================================================

TComplex Two(Int_t n1, Int_t n2)
{
 // Generic two-particle correlation <exp[i(n1*phi1+n2*phi2)]>.

 TComplex two = Q(n1,1)*Q(n2,1)-Q(n1+n2,2);

 return two;

} // TComplex Two(Int_t n1, Int_t n2)

//=======================================================================================================================

TComplex Three(Int_t n1, Int_t n2, Int_t n3)
{
 // Generic three-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3)]>.

 TComplex three = Q(n1,1)*Q(n2,1)*Q(n3,1)-Q(n1+n2,2)*Q(n3,1)-Q(n2,1)*Q(n1+n3,2)
                - Q(n1,1)*Q(n2+n3,2)+2.*Q(n1+n2+n3,3); 

 return three;

} // TComplex Three(Int_t n1, Int_t n2, Int_t n3)

//=======================================================================================================================

TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4)
{
 // Generic four-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4)]>.

 TComplex four = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)-Q(n2,1)*Q(n1+n3,2)*Q(n4,1)
               - Q(n1,1)*Q(n2+n3,2)*Q(n4,1)+2.*Q(n1+n2+n3,3)*Q(n4,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)
               + Q(n2+n3,2)*Q(n1+n4,2)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)+Q(n1+n3,2)*Q(n2+n4,2)
               + 2.*Q(n3,1)*Q(n1+n2+n4,3)-Q(n1,1)*Q(n2,1)*Q(n3+n4,2)+Q(n1+n2,2)*Q(n3+n4,2)
               + 2.*Q(n2,1)*Q(n1+n3+n4,3)+2.*Q(n1,1)*Q(n2+n3+n4,3)-6.*Q(n1+n2+n3+n4,4);

 return four;

} // TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4)

//=======================================================================================================================

TComplex Five(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5)
{
 // Generic five-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5)]>.

 TComplex five = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)
               - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)
               + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)
               + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)
               + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)
               - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)
               + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)
               - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)
               + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)
               + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)
               - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)
               + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)
               - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)
               - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)
               + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)
               + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)
               + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)
               + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)
               - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)
               + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)
               + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)
               + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)
               + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)
               - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3) 
               - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)
               - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)+24.*Q(n1+n2+n3+n4+n5,5);
 
 return five;

} // TComplex Five(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5)

//=======================================================================================================================

TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6)
{
 // Generic six-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6)]>.

 TComplex six = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)
              - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)
              + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)
              + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)
              + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)
              - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)
              + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)
              - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)
              + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)
              + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6,1)
              - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)
              + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)
              - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6,1)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)
              - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)
              + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)
              + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6,1)
              + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6,1)
              + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6,1)
              - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)
              + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)
              + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6,1)
              + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6,1)
              + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6,1)
              - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)
              - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6,1)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6,1)
              - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6,1)+24.*Q(n1+n2+n3+n4+n5,5)*Q(n6,1)
              - Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)+Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)
              + Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)+Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)
              - 2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6,2)+Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)
              - Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6,2)+Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)
              - Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6,2)-2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6,2)
              + Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)-Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6,2)
              - 2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6,2)-2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6,2)
              + 6.*Q(n2+n3+n4+n5,4)*Q(n1+n6,2)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)
              + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)
              + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6,2)
              + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6,2)
              + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6,2)
              - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6,2)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)
              - Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6,2)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6,2)
              - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6,2)+6.*Q(n1+n3+n4+n5,4)*Q(n2+n6,2)
              + 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)-2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6,3)
              - 2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6,3)-2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6,3)
              + 4.*Q(n3+n4+n5,3)*Q(n1+n2+n6,3)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)
              + Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)+Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)
              + Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)-2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6,2)
              + Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)-Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6,2)
              + Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)-Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6,2)
              - 2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6,2)+Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)
              - Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6,2)-2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6,2)
              - 2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6,2)+6.*Q(n1+n2+n4+n5,4)*Q(n3+n6,2)
              + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6,3)
              - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6,3)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6,3)
              + 4.*Q(n2+n4+n5,3)*Q(n1+n3+n6,3)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)
              - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6,3)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6,3)
              - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6,3)+4.*Q(n1+n4+n5,3)*Q(n2+n3+n6,3)
              - 6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6,4)+6.*Q(n4+n5,2)*Q(n1+n2+n3+n6,4)
              - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)+Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)
              + Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)+Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)
              - 2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6,2)+Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)
              - Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6,2)+Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)
              - Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6,2)-2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6,2)
              + Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)-Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6,2)
              - 2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6,2)-2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6,2)
              + 6.*Q(n1+n2+n3+n5,4)*Q(n4+n6,2)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)
              - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6,3)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6,3)
              - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6,3)+4.*Q(n2+n3+n5,3)*Q(n1+n4+n6,3)
              + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6,3)
              - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6,3)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6,3)
              + 4.*Q(n1+n3+n5,3)*Q(n2+n4+n6,3)-6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6,4)
              + 6.*Q(n3+n5,2)*Q(n1+n2+n4+n6,4)+2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)
              - 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6,3)-2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6,3)
              - 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6,3)+4.*Q(n1+n2+n5,3)*Q(n3+n4+n6,3)
              - 6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6,4)+6.*Q(n2+n5,2)*Q(n1+n3+n4+n6,4)
              - 6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6,4)+6.*Q(n1+n5,2)*Q(n2+n3+n4+n6,4)
              + 24.*Q(n5,1)*Q(n1+n2+n3+n4+n6,5)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)
              + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)
              + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6,2)
              + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6,2)
              + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6,2)
              - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6,2)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)
              - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6,2)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6,2)
              - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6,2)+6.*Q(n1+n2+n3+n4,4)*Q(n5+n6,2)
              + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6,3)
              - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6,3)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6,3)
              + 4.*Q(n2+n3+n4,3)*Q(n1+n5+n6,3)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)
              - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6,3)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6,3)
              - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6,3)+4.*Q(n1+n3+n4,3)*Q(n2+n5+n6,3)
              - 6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6,4)+6.*Q(n3+n4,2)*Q(n1+n2+n5+n6,4)
              + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6,3)
              - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6,3)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6,3)
              + 4.*Q(n1+n2+n4,3)*Q(n3+n5+n6,3)-6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6,4)
              + 6.*Q(n2+n4,2)*Q(n1+n3+n5+n6,4)-6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6,4)
              + 6.*Q(n1+n4,2)*Q(n2+n3+n5+n6,4)+24.*Q(n4,1)*Q(n1+n2+n3+n5+n6,5)
              + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6,3)
              - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6,3)
              + 4.*Q(n1+n2+n3,3)*Q(n4+n5+n6,3)-6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6,4)
              + 6.*Q(n2+n3,2)*Q(n1+n4+n5+n6,4)-6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6,4)
              + 6.*Q(n1+n3,2)*Q(n2+n4+n5+n6,4)+24.*Q(n3,1)*Q(n1+n2+n4+n5+n6,5)
              - 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6,4)+6.*Q(n1+n2,2)*Q(n3+n4+n5+n6,4)
              + 24.*Q(n2,1)*Q(n1+n3+n4+n5+n6,5)+24.*Q(n1,1)*Q(n2+n3+n4+n5+n6,5)
              - 120.*Q(n1+n2+n3+n4+n5+n6,6);

 return six;

} // TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6)

//=======================================================================================================================

TComplex Seven(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7)
{
 // Generic seven-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7)]>.

 TComplex seven = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)
                - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6,1)*Q(n7,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)
                - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)
                - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)
                - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)
                + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)
                - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n7,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)
                - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n7,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)
                - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n7,1)
                - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n7,1)+24.*Q(n1+n2+n3+n4+n5,5)*Q(n6,1)*Q(n7,1)
                - Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)+Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)
                + Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)+Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)
                - 2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)+Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)
                - Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)+Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)
                - Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)-2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n7,1)
                + Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)-Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)
                - 2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n7,1)-2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n7,1)
                + 6.*Q(n2+n3+n4+n5,4)*Q(n1+n6,2)*Q(n7,1)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)
                + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)
                + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)
                - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n7,1)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)
                - Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n7,1)
                - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n7,1)+6.*Q(n1+n3+n4+n5,4)*Q(n2+n6,2)*Q(n7,1)
                + 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)-2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)
                - 2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n7,1)-2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n7,1)
                + 4.*Q(n3+n4+n5,3)*Q(n1+n2+n6,3)*Q(n7,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)
                + Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)+Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)-2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)
                + Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)-Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)-Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)
                - 2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n7,1)+Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)
                - Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)-2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n7,1)
                - 2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n7,1)+6.*Q(n1+n2+n4+n5,4)*Q(n3+n6,2)*Q(n7,1)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)
                - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n7,1)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n7,1)
                + 4.*Q(n2+n4+n5,3)*Q(n1+n3+n6,3)*Q(n7,1)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)
                - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n7,1)
                - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n7,1)+4.*Q(n1+n4+n5,3)*Q(n2+n3+n6,3)*Q(n7,1)
                - 6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n7,1)+6.*Q(n4+n5,2)*Q(n1+n2+n3+n6,4)*Q(n7,1)
                - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)+Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)
                + Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)+Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)
                - 2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)+Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)
                - Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)+Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)
                - Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)-2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)-Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)
                - 2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n7,1)-2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n7,1)
                + 6.*Q(n1+n2+n3+n5,4)*Q(n4+n6,2)*Q(n7,1)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)
                - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n7,1)
                - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n7,1)+4.*Q(n2+n3+n5,3)*Q(n1+n4+n6,3)*Q(n7,1)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)
                - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n7,1)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n7,1)
                + 4.*Q(n1+n3+n5,3)*Q(n2+n4+n6,3)*Q(n7,1)-6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n7,1)
                + 6.*Q(n3+n5,2)*Q(n1+n2+n4+n6,4)*Q(n7,1)+2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)
                - 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)-2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n7,1)
                - 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n7,1)+4.*Q(n1+n2+n5,3)*Q(n3+n4+n6,3)*Q(n7,1)
                - 6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n7,1)+6.*Q(n2+n5,2)*Q(n1+n3+n4+n6,4)*Q(n7,1)
                - 6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n7,1)+6.*Q(n1+n5,2)*Q(n2+n3+n4+n6,4)*Q(n7,1)
                + 24.*Q(n5,1)*Q(n1+n2+n3+n4+n6,5)*Q(n7,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)
                + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)
                + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)
                - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n7,1)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)
                - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n7,1)
                - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n7,1)+6.*Q(n1+n2+n3+n4,4)*Q(n5+n6,2)*Q(n7,1)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)
                - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n7,1)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n7,1)
                + 4.*Q(n2+n3+n4,3)*Q(n1+n5+n6,3)*Q(n7,1)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)
                - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n7,1)
                - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n7,1)+4.*Q(n1+n3+n4,3)*Q(n2+n5+n6,3)*Q(n7,1)
                - 6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n7,1)+6.*Q(n3+n4,2)*Q(n1+n2+n5+n6,4)*Q(n7,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)
                - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n7,1)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n7,1)
                + 4.*Q(n1+n2+n4,3)*Q(n3+n5+n6,3)*Q(n7,1)-6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n7,1)
                + 6.*Q(n2+n4,2)*Q(n1+n3+n5+n6,4)*Q(n7,1)-6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n7,1)
                + 6.*Q(n1+n4,2)*Q(n2+n3+n5+n6,4)*Q(n7,1)+24.*Q(n4,1)*Q(n1+n2+n3+n5+n6,5)*Q(n7,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n7,1)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n7,1)
                + 4.*Q(n1+n2+n3,3)*Q(n4+n5+n6,3)*Q(n7,1)-6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n7,1)
                + 6.*Q(n2+n3,2)*Q(n1+n4+n5+n6,4)*Q(n7,1)-6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n7,1)
                + 6.*Q(n1+n3,2)*Q(n2+n4+n5+n6,4)*Q(n7,1)+24.*Q(n3,1)*Q(n1+n2+n4+n5+n6,5)*Q(n7,1)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n7,1)+6.*Q(n1+n2,2)*Q(n3+n4+n5+n6,4)*Q(n7,1)
                + 24.*Q(n2,1)*Q(n1+n3+n4+n5+n6,5)*Q(n7,1)+24.*Q(n1,1)*Q(n2+n3+n4+n5+n6,5)*Q(n7,1)
                - 120.*Q(n1+n2+n3+n4+n5+n6,6)*Q(n7,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)
                + Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)+Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)
                + Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)-2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)
                + Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)-Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)
                + Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)-Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)
                - 2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n7,2)+Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)
                - Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)-2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n7,2)
                - 2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n7,2)+6.*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n1+n7,2)
                + Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)-Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)
                - Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n7,2)-Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n7,2)
                + 2.*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n1+n7,2)+Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)
                - Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)-Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n7,2)
                - Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n7,2)+2.*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n1+n7,2)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n7,2)+2.*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n1+n7,2)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)-Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)
                - Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n7,2)-Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n7,2)
                + 2.*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n1+n7,2)-2.*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n7,2)
                + 2.*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n1+n7,2)-2.*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n7,2)
                + 2.*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n1+n7,2)+6.*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n1+n7,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)-Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n7,2)-Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n7,2)
                + 2.*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n1+n7,2)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n7,2)
                + 2.*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n1+n7,2)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n7,2)
                + 2.*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n1+n7,2)+6.*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n1+n7,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n7,2)+2.*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n1+n7,2)
                + 6.*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n1+n7,2)+6.*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n1+n7,2)
                - 24.*Q(n2+n3+n4+n5+n6,5)*Q(n1+n7,2)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)
                + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)
                + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)
                + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)
                + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)
                - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n7,2)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)
                - Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n7,2)
                - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n2+n7,2)+6.*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n2+n7,2)
                + Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)-Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)
                - Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n7,2)-Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n7,2)
                + 2.*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n2+n7,2)+Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)
                - Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)-Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n7,2)
                - Q(n1,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n2+n7,2)+2.*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n2+n7,2)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n7,2)+2.*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n2+n7,2)
                + Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)-Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)
                - Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n7,2)-Q(n1,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n2+n7,2)
                + 2.*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n2+n7,2)-2.*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n7,2)
                + 2.*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n2+n7,2)-2.*Q(n1,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n2+n7,2)
                + 2.*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n2+n7,2)+6.*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n2+n7,2)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)-Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)
                - Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n7,2)-Q(n1,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n2+n7,2)
                + 2.*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n2+n7,2)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n7,2)
                + 2.*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n2+n7,2)-2.*Q(n1,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n2+n7,2)
                + 2.*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n2+n7,2)+6.*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n2+n7,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n2+n7,2)+2.*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n2+n7,2)
                + 6.*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n2+n7,2)+6.*Q(n1,1)*Q(n3+n4+n5+n6,4)*Q(n2+n7,2)
                - 24.*Q(n1+n3+n4+n5+n6,5)*Q(n2+n7,2)+2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)
                - 2.*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)-2.*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n7,3)
                - 2.*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n7,3)+4.*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n2+n7,3)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n7,3)+2.*Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n2+n7,3)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n7,3)+2.*Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n2+n7,3)
                + 4.*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n2+n7,3)-2.*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n7,3)
                + 2.*Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n2+n7,3)+4.*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n2+n7,3)
                + 4.*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n2+n7,3)-12.*Q(n3+n4+n5+n6,4)*Q(n1+n2+n7,3)
                - Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)+Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)
                + Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)+Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)
                - 2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)+Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)
                - Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)+Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)
                - Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)-2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n7,2)
                + Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)-Q(n1+n2,2)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)
                - 2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n3+n7,2)-2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n3+n7,2)
                + 6.*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n3+n7,2)+Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)
                - Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)-Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n7,2)
                - Q(n2,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n3+n7,2)+2.*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n3+n7,2)
                + Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)-Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)
                - Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n7,2)-Q(n1,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n3+n7,2)
                + 2.*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n3+n7,2)-2.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n7,2)
                + 2.*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n3+n7,2)+Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)
                - Q(n1+n2,2)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)-Q(n2,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n3+n7,2)
                - Q(n1,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n3+n7,2)+2.*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n3+n7,2)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n3+n7,2)+2.*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n3+n7,2)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n3+n7,2)+2.*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n3+n7,2)
                + 6.*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n3+n7,2)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)
                - Q(n1+n2,2)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)-Q(n2,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n3+n7,2)
                - Q(n1,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n3+n7,2)+2.*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n3+n7,2)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n3+n7,2)+2.*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n3+n7,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n3+n7,2)+2.*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n3+n7,2)
                + 6.*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n3+n7,2)-2.*Q(n1,1)*Q(n2,1)*Q(n4+n5+n6,3)*Q(n3+n7,2)
                + 2.*Q(n1+n2,2)*Q(n4+n5+n6,3)*Q(n3+n7,2)+6.*Q(n2,1)*Q(n1+n4+n5+n6,4)*Q(n3+n7,2)
                + 6.*Q(n1,1)*Q(n2+n4+n5+n6,4)*Q(n3+n7,2)-24.*Q(n1+n2+n4+n5+n6,5)*Q(n3+n7,2)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)
                - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n7,3)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n3+n7,3)
                + 4.*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n3+n7,3)-2.*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n7,3)
                + 2.*Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n3+n7,3)-2.*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n3+n7,3)
                + 2.*Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n3+n7,3)+4.*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n3+n7,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n3+n7,3)+2.*Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n3+n7,3)
                + 4.*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n3+n7,3)+4.*Q(n2,1)*Q(n4+n5+n6,3)*Q(n1+n3+n7,3)
                - 12.*Q(n2+n4+n5+n6,4)*Q(n1+n3+n7,3)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)
                - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n7,3)
                - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n3+n7,3)+4.*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n3+n7,3)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n7,3)+2.*Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n3+n7,3)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n3+n7,3)+2.*Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n3+n7,3)
                + 4.*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n3+n7,3)-2.*Q(n1,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n3+n7,3)
                + 2.*Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n3+n7,3)+4.*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n3+n7,3)
                + 4.*Q(n1,1)*Q(n4+n5+n6,3)*Q(n2+n3+n7,3)-12.*Q(n1+n4+n5+n6,4)*Q(n2+n3+n7,3)
                - 6.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n7,4)+6.*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n3+n7,4)
                + 6.*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n3+n7,4)+6.*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n3+n7,4)
                - 12.*Q(n4+n5+n6,3)*Q(n1+n2+n3+n7,4)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)
                + Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)+Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)
                + Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)-2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)
                + Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)-Q(n2+n3,2)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)
                + Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)-Q(n1+n3,2)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)
                - 2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n4+n7,2)+Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)
                - Q(n1+n2,2)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)-2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n4+n7,2)
                - 2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n4+n7,2)+6.*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n4+n7,2)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)-Q(n2+n3,2)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)
                - Q(n3,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n4+n7,2)-Q(n2,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n4+n7,2)
                + 2.*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n4+n7,2)+Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)
                - Q(n1+n3,2)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)-Q(n3,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n4+n7,2)
                - Q(n1,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n4+n7,2)+2.*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n4+n7,2)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n4+n7,2)+2.*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n4+n7,2)
                + Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)-Q(n1+n2,2)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)
                - Q(n2,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n4+n7,2)-Q(n1,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n4+n7,2)
                + 2.*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n4+n7,2)-2.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n4+n7,2)
                + 2.*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n4+n7,2)-2.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n4+n7,2)
                + 2.*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n4+n7,2)+6.*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n4+n7,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)-Q(n1+n2,2)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n5+n6,2)*Q(n4+n7,2)-Q(n1,1)*Q(n2+n3,2)*Q(n5+n6,2)*Q(n4+n7,2)
                + 2.*Q(n1+n2+n3,3)*Q(n5+n6,2)*Q(n4+n7,2)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5+n6,3)*Q(n4+n7,2)
                + 2.*Q(n2+n3,2)*Q(n1+n5+n6,3)*Q(n4+n7,2)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5+n6,3)*Q(n4+n7,2)
                + 2.*Q(n1+n3,2)*Q(n2+n5+n6,3)*Q(n4+n7,2)+6.*Q(n3,1)*Q(n1+n2+n5+n6,4)*Q(n4+n7,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5+n6,3)*Q(n4+n7,2)+2.*Q(n1+n2,2)*Q(n3+n5+n6,3)*Q(n4+n7,2)
                + 6.*Q(n2,1)*Q(n1+n3+n5+n6,4)*Q(n4+n7,2)+6.*Q(n1,1)*Q(n2+n3+n5+n6,4)*Q(n4+n7,2)
                - 24.*Q(n1+n2+n3+n5+n6,5)*Q(n4+n7,2)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)
                - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n4+n7,3)
                - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n4+n7,3)+4.*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n4+n7,3)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n4+n7,3)+2.*Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n4+n7,3)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n4+n7,3)+2.*Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n4+n7,3)
                + 4.*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n4+n7,3)-2.*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n1+n4+n7,3)
                + 2.*Q(n2+n3,2)*Q(n5+n6,2)*Q(n1+n4+n7,3)+4.*Q(n3,1)*Q(n2+n5+n6,3)*Q(n1+n4+n7,3)
                + 4.*Q(n2,1)*Q(n3+n5+n6,3)*Q(n1+n4+n7,3)-12.*Q(n2+n3+n5+n6,4)*Q(n1+n4+n7,3)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)
                - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n4+n7,3)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n4+n7,3)
                + 4.*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n4+n7,3)-2.*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n4+n7,3)
                + 2.*Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n4+n7,3)-2.*Q(n1,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n4+n7,3)
                + 2.*Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n4+n7,3)+4.*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n4+n7,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5+n6,2)*Q(n2+n4+n7,3)+2.*Q(n1+n3,2)*Q(n5+n6,2)*Q(n2+n4+n7,3)
                + 4.*Q(n3,1)*Q(n1+n5+n6,3)*Q(n2+n4+n7,3)+4.*Q(n1,1)*Q(n3+n5+n6,3)*Q(n2+n4+n7,3)
                - 12.*Q(n1+n3+n5+n6,4)*Q(n2+n4+n7,3)-6.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n4+n7,4)
                + 6.*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n4+n7,4)+6.*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n4+n7,4)
                + 6.*Q(n3,1)*Q(n5+n6,2)*Q(n1+n2+n4+n7,4)-12.*Q(n3+n5+n6,3)*Q(n1+n2+n4+n7,4)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)-2.*Q(n1+n2,2)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)
                - 2.*Q(n2,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n4+n7,3)-2.*Q(n1,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n4+n7,3)
                + 4.*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n4+n7,3)-2.*Q(n2,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n4+n7,3)
                + 2.*Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n4+n7,3)-2.*Q(n1,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n4+n7,3)
                + 2.*Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n4+n7,3)+4.*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n4+n7,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5+n6,2)*Q(n3+n4+n7,3)+2.*Q(n1+n2,2)*Q(n5+n6,2)*Q(n3+n4+n7,3)
                + 4.*Q(n2,1)*Q(n1+n5+n6,3)*Q(n3+n4+n7,3)+4.*Q(n1,1)*Q(n2+n5+n6,3)*Q(n3+n4+n7,3)
                - 12.*Q(n1+n2+n5+n6,4)*Q(n3+n4+n7,3)-6.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n4+n7,4)
                + 6.*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n4+n7,4)+6.*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n4+n7,4)
                + 6.*Q(n2,1)*Q(n5+n6,2)*Q(n1+n3+n4+n7,4)-12.*Q(n2+n5+n6,3)*Q(n1+n3+n4+n7,4)
                - 6.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n4+n7,4)+6.*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n4+n7,4)
                + 6.*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n4+n7,4)+6.*Q(n1,1)*Q(n5+n6,2)*Q(n2+n3+n4+n7,4)
                - 12.*Q(n1+n5+n6,3)*Q(n2+n3+n4+n7,4)+24.*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n4+n7,5)
                - 24.*Q(n5+n6,2)*Q(n1+n2+n3+n4+n7,5)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)
                + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)
                + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)
                - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n6,1)*Q(n5+n7,2)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)
                - Q(n1+n2,2)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n6,1)*Q(n5+n7,2)
                - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n6,1)*Q(n5+n7,2)+6.*Q(n1+n2+n3+n4,4)*Q(n6,1)*Q(n5+n7,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)-Q(n2+n3,2)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n1+n6,2)*Q(n5+n7,2)-Q(n2,1)*Q(n3+n4,2)*Q(n1+n6,2)*Q(n5+n7,2)
                + 2.*Q(n2+n3+n4,3)*Q(n1+n6,2)*Q(n5+n7,2)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)
                - Q(n1+n3,2)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)-Q(n3,1)*Q(n1+n4,2)*Q(n2+n6,2)*Q(n5+n7,2)
                - Q(n1,1)*Q(n3+n4,2)*Q(n2+n6,2)*Q(n5+n7,2)+2.*Q(n1+n3+n4,3)*Q(n2+n6,2)*Q(n5+n7,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n6,3)*Q(n5+n7,2)+2.*Q(n3+n4,2)*Q(n1+n2+n6,3)*Q(n5+n7,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)-Q(n1+n2,2)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n3+n6,2)*Q(n5+n7,2)-Q(n1,1)*Q(n2+n4,2)*Q(n3+n6,2)*Q(n5+n7,2)
                + 2.*Q(n1+n2+n4,3)*Q(n3+n6,2)*Q(n5+n7,2)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n6,3)*Q(n5+n7,2)
                + 2.*Q(n2+n4,2)*Q(n1+n3+n6,3)*Q(n5+n7,2)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n6,3)*Q(n5+n7,2)
                + 2.*Q(n1+n4,2)*Q(n2+n3+n6,3)*Q(n5+n7,2)+6.*Q(n4,1)*Q(n1+n2+n3+n6,4)*Q(n5+n7,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)-Q(n1+n2,2)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4+n6,2)*Q(n5+n7,2)-Q(n1,1)*Q(n2+n3,2)*Q(n4+n6,2)*Q(n5+n7,2)
                + 2.*Q(n1+n2+n3,3)*Q(n4+n6,2)*Q(n5+n7,2)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n6,3)*Q(n5+n7,2)
                + 2.*Q(n2+n3,2)*Q(n1+n4+n6,3)*Q(n5+n7,2)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n6,3)*Q(n5+n7,2)
                + 2.*Q(n1+n3,2)*Q(n2+n4+n6,3)*Q(n5+n7,2)+6.*Q(n3,1)*Q(n1+n2+n4+n6,4)*Q(n5+n7,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n6,3)*Q(n5+n7,2)+2.*Q(n1+n2,2)*Q(n3+n4+n6,3)*Q(n5+n7,2)
                + 6.*Q(n2,1)*Q(n1+n3+n4+n6,4)*Q(n5+n7,2)+6.*Q(n1,1)*Q(n2+n3+n4+n6,4)*Q(n5+n7,2)
                - 24.*Q(n1+n2+n3+n4+n6,5)*Q(n5+n7,2)+2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)
                - 2.*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)-2.*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n1+n5+n7,3)
                - 2.*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n1+n5+n7,3)+4.*Q(n2+n3+n4,3)*Q(n6,1)*Q(n1+n5+n7,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n1+n5+n7,3)+2.*Q(n3+n4,2)*Q(n2+n6,2)*Q(n1+n5+n7,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n1+n5+n7,3)+2.*Q(n2+n4,2)*Q(n3+n6,2)*Q(n1+n5+n7,3)
                + 4.*Q(n4,1)*Q(n2+n3+n6,3)*Q(n1+n5+n7,3)-2.*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n1+n5+n7,3)
                + 2.*Q(n2+n3,2)*Q(n4+n6,2)*Q(n1+n5+n7,3)+4.*Q(n3,1)*Q(n2+n4+n6,3)*Q(n1+n5+n7,3)
                + 4.*Q(n2,1)*Q(n3+n4+n6,3)*Q(n1+n5+n7,3)-12.*Q(n2+n3+n4+n6,4)*Q(n1+n5+n7,3)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)-2.*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)
                - 2.*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n2+n5+n7,3)-2.*Q(n1,1)*Q(n3+n4,2)*Q(n6,1)*Q(n2+n5+n7,3)
                + 4.*Q(n1+n3+n4,3)*Q(n6,1)*Q(n2+n5+n7,3)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n2+n5+n7,3)
                + 2.*Q(n3+n4,2)*Q(n1+n6,2)*Q(n2+n5+n7,3)-2.*Q(n1,1)*Q(n4,1)*Q(n3+n6,2)*Q(n2+n5+n7,3)
                + 2.*Q(n1+n4,2)*Q(n3+n6,2)*Q(n2+n5+n7,3)+4.*Q(n4,1)*Q(n1+n3+n6,3)*Q(n2+n5+n7,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4+n6,2)*Q(n2+n5+n7,3)+2.*Q(n1+n3,2)*Q(n4+n6,2)*Q(n2+n5+n7,3)
                + 4.*Q(n3,1)*Q(n1+n4+n6,3)*Q(n2+n5+n7,3)+4.*Q(n1,1)*Q(n3+n4+n6,3)*Q(n2+n5+n7,3)
                - 12.*Q(n1+n3+n4+n6,4)*Q(n2+n5+n7,3)-6.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n2+n5+n7,4)
                + 6.*Q(n3+n4,2)*Q(n6,1)*Q(n1+n2+n5+n7,4)+6.*Q(n4,1)*Q(n3+n6,2)*Q(n1+n2+n5+n7,4)
                + 6.*Q(n3,1)*Q(n4+n6,2)*Q(n1+n2+n5+n7,4)-12.*Q(n3+n4+n6,3)*Q(n1+n2+n5+n7,4)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)
                - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n6,1)*Q(n3+n5+n7,3)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n6,1)*Q(n3+n5+n7,3)
                + 4.*Q(n1+n2+n4,3)*Q(n6,1)*Q(n3+n5+n7,3)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n6,2)*Q(n3+n5+n7,3)
                + 2.*Q(n2+n4,2)*Q(n1+n6,2)*Q(n3+n5+n7,3)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n6,2)*Q(n3+n5+n7,3)
                + 2.*Q(n1+n4,2)*Q(n2+n6,2)*Q(n3+n5+n7,3)+4.*Q(n4,1)*Q(n1+n2+n6,3)*Q(n3+n5+n7,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4+n6,2)*Q(n3+n5+n7,3)+2.*Q(n1+n2,2)*Q(n4+n6,2)*Q(n3+n5+n7,3)
                + 4.*Q(n2,1)*Q(n1+n4+n6,3)*Q(n3+n5+n7,3)+4.*Q(n1,1)*Q(n2+n4+n6,3)*Q(n3+n5+n7,3)
                - 12.*Q(n1+n2+n4+n6,4)*Q(n3+n5+n7,3)-6.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n1+n3+n5+n7,4)
                + 6.*Q(n2+n4,2)*Q(n6,1)*Q(n1+n3+n5+n7,4)+6.*Q(n4,1)*Q(n2+n6,2)*Q(n1+n3+n5+n7,4)
                + 6.*Q(n2,1)*Q(n4+n6,2)*Q(n1+n3+n5+n7,4)-12.*Q(n2+n4+n6,3)*Q(n1+n3+n5+n7,4)
                - 6.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n2+n3+n5+n7,4)+6.*Q(n1+n4,2)*Q(n6,1)*Q(n2+n3+n5+n7,4)
                + 6.*Q(n4,1)*Q(n1+n6,2)*Q(n2+n3+n5+n7,4)+6.*Q(n1,1)*Q(n4+n6,2)*Q(n2+n3+n5+n7,4)
                - 12.*Q(n1+n4+n6,3)*Q(n2+n3+n5+n7,4)+24.*Q(n4,1)*Q(n6,1)*Q(n1+n2+n3+n5+n7,5)
                - 24.*Q(n4+n6,2)*Q(n1+n2+n3+n5+n7,5)+2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)
                - 2.*Q(n1+n2,2)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)-2.*Q(n2,1)*Q(n1+n3,2)*Q(n6,1)*Q(n4+n5+n7,3)
                - 2.*Q(n1,1)*Q(n2+n3,2)*Q(n6,1)*Q(n4+n5+n7,3)+4.*Q(n1+n2+n3,3)*Q(n6,1)*Q(n4+n5+n7,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n6,2)*Q(n4+n5+n7,3)+2.*Q(n2+n3,2)*Q(n1+n6,2)*Q(n4+n5+n7,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n6,2)*Q(n4+n5+n7,3)+2.*Q(n1+n3,2)*Q(n2+n6,2)*Q(n4+n5+n7,3)
                + 4.*Q(n3,1)*Q(n1+n2+n6,3)*Q(n4+n5+n7,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n6,2)*Q(n4+n5+n7,3)
                + 2.*Q(n1+n2,2)*Q(n3+n6,2)*Q(n4+n5+n7,3)+4.*Q(n2,1)*Q(n1+n3+n6,3)*Q(n4+n5+n7,3)
                + 4.*Q(n1,1)*Q(n2+n3+n6,3)*Q(n4+n5+n7,3)-12.*Q(n1+n2+n3+n6,4)*Q(n4+n5+n7,3)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n1+n4+n5+n7,4)+6.*Q(n2+n3,2)*Q(n6,1)*Q(n1+n4+n5+n7,4)
                + 6.*Q(n3,1)*Q(n2+n6,2)*Q(n1+n4+n5+n7,4)+6.*Q(n2,1)*Q(n3+n6,2)*Q(n1+n4+n5+n7,4)
                - 12.*Q(n2+n3+n6,3)*Q(n1+n4+n5+n7,4)-6.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n2+n4+n5+n7,4)
                + 6.*Q(n1+n3,2)*Q(n6,1)*Q(n2+n4+n5+n7,4)+6.*Q(n3,1)*Q(n1+n6,2)*Q(n2+n4+n5+n7,4)
                + 6.*Q(n1,1)*Q(n3+n6,2)*Q(n2+n4+n5+n7,4)-12.*Q(n1+n3+n6,3)*Q(n2+n4+n5+n7,4)
                + 24.*Q(n3,1)*Q(n6,1)*Q(n1+n2+n4+n5+n7,5)-24.*Q(n3+n6,2)*Q(n1+n2+n4+n5+n7,5)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n3+n4+n5+n7,4)+6.*Q(n1+n2,2)*Q(n6,1)*Q(n3+n4+n5+n7,4)
                + 6.*Q(n2,1)*Q(n1+n6,2)*Q(n3+n4+n5+n7,4)+6.*Q(n1,1)*Q(n2+n6,2)*Q(n3+n4+n5+n7,4)
                - 12.*Q(n1+n2+n6,3)*Q(n3+n4+n5+n7,4)+24.*Q(n2,1)*Q(n6,1)*Q(n1+n3+n4+n5+n7,5)
                - 24.*Q(n2+n6,2)*Q(n1+n3+n4+n5+n7,5)+24.*Q(n1,1)*Q(n6,1)*Q(n2+n3+n4+n5+n7,5)
                - 24.*Q(n1+n6,2)*Q(n2+n3+n4+n5+n7,5)-120.*Q(n6,1)*Q(n1+n2+n3+n4+n5+n7,6)
                - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)+Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)
                + Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)+Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)
                - 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)+Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)
                - Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)+Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)
                - Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)-2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6+n7,2)
                + Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)-Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)
                - 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6+n7,2)-2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6+n7,2)
                + 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6+n7,2)+Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)
                - Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)-Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6+n7,2)
                - Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6+n7,2)+2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6+n7,2)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)-Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)
                - Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6+n7,2)-Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6+n7,2)
                + 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6+n7,2)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6+n7,2)
                + 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6+n7,2)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)
                - Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)-Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6+n7,2)
                - Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6+n7,2)+2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6+n7,2)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6+n7,2)+2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6+n7,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6+n7,2)+2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6+n7,2)
                + 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6+n7,2)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)
                - Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)-Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6+n7,2)
                - Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6+n7,2)+2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6+n7,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6+n7,2)+2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6+n7,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6+n7,2)+2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6+n7,2)
                + 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6+n7,2)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6+n7,2)
                + 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6+n7,2)+6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6+n7,2)
                + 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6+n7,2)-24.*Q(n1+n2+n3+n4+n5,5)*Q(n6+n7,2)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)
                - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6+n7,3)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6+n7,3)
                + 4.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6+n7,3)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6+n7,3)
                + 2.*Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6+n7,3)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6+n7,3)
                + 2.*Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6+n7,3)+4.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6+n7,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6+n7,3)+2.*Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6+n7,3)
                + 4.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6+n7,3)+4.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6+n7,3)
                - 12.*Q(n2+n3+n4+n5,4)*Q(n1+n6+n7,3)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)
                - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6+n7,3)
                - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6+n7,3)+4.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6+n7,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6+n7,3)+2.*Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6+n7,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6+n7,3)+2.*Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6+n7,3)
                + 4.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6+n7,3)-2.*Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6+n7,3)
                + 2.*Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6+n7,3)+4.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6+n7,3)
                + 4.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6+n7,3)-12.*Q(n1+n3+n4+n5,4)*Q(n2+n6+n7,3)
                - 6.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6+n7,4)+6.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6+n7,4)
                + 6.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6+n7,4)+6.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6+n7,4)
                - 12.*Q(n3+n4+n5,3)*Q(n1+n2+n6+n7,4)+2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)
                - 2.*Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)-2.*Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6+n7,3)
                - 2.*Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6+n7,3)+4.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6+n7,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6+n7,3)+2.*Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6+n7,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6+n7,3)+2.*Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6+n7,3)
                + 4.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6+n7,3)-2.*Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6+n7,3)
                + 2.*Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6+n7,3)+4.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6+n7,3)
                + 4.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6+n7,3)-12.*Q(n1+n2+n4+n5,4)*Q(n3+n6+n7,3)
                - 6.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6+n7,4)+6.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6+n7,4)
                + 6.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6+n7,4)+6.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6+n7,4)
                - 12.*Q(n2+n4+n5,3)*Q(n1+n3+n6+n7,4)-6.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6+n7,4)
                + 6.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6+n7,4)+6.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6+n7,4)
                + 6.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6+n7,4)-12.*Q(n1+n4+n5,3)*Q(n2+n3+n6+n7,4)
                + 24.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6+n7,5)-24.*Q(n4+n5,2)*Q(n1+n2+n3+n6+n7,5)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6+n7,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6+n7,3)
                + 4.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6+n7,3)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6+n7,3)
                + 2.*Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6+n7,3)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6+n7,3)
                + 2.*Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6+n7,3)+4.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6+n7,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6+n7,3)+2.*Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6+n7,3)
                + 4.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6+n7,3)+4.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6+n7,3)
                - 12.*Q(n1+n2+n3+n5,4)*Q(n4+n6+n7,3)-6.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6+n7,4)
                + 6.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6+n7,4)+6.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6+n7,4)
                + 6.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6+n7,4)-12.*Q(n2+n3+n5,3)*Q(n1+n4+n6+n7,4)
                - 6.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6+n7,4)+6.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6+n7,4)
                + 6.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6+n7,4)+6.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6+n7,4)
                - 12.*Q(n1+n3+n5,3)*Q(n2+n4+n6+n7,4)+24.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6+n7,5)
                - 24.*Q(n3+n5,2)*Q(n1+n2+n4+n6+n7,5)-6.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6+n7,4)
                + 6.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6+n7,4)+6.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6+n7,4)
                + 6.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6+n7,4)-12.*Q(n1+n2+n5,3)*Q(n3+n4+n6+n7,4)
                + 24.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6+n7,5)-24.*Q(n2+n5,2)*Q(n1+n3+n4+n6+n7,5)
                + 24.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6+n7,5)-24.*Q(n1+n5,2)*Q(n2+n3+n4+n6+n7,5)
                - 120.*Q(n5,1)*Q(n1+n2+n3+n4+n6+n7,6)+2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)
                - 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)-2.*Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6+n7,3)
                - 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6+n7,3)+4.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6+n7,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6+n7,3)+2.*Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6+n7,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6+n7,3)+2.*Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6+n7,3)
                + 4.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6+n7,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6+n7,3)
                + 2.*Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6+n7,3)+4.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6+n7,3)
                + 4.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6+n7,3)-12.*Q(n1+n2+n3+n4,4)*Q(n5+n6+n7,3)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6+n7,4)+6.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6+n7,4)
                + 6.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6+n7,4)+6.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6+n7,4)
                - 12.*Q(n2+n3+n4,3)*Q(n1+n5+n6+n7,4)-6.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6+n7,4)
                + 6.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6+n7,4)+6.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6+n7,4)
                + 6.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6+n7,4)-12.*Q(n1+n3+n4,3)*Q(n2+n5+n6+n7,4)
                + 24.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6+n7,5)-24.*Q(n3+n4,2)*Q(n1+n2+n5+n6+n7,5)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6+n7,4)+6.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6+n7,4)
                + 6.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6+n7,4)+6.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6+n7,4)
                - 12.*Q(n1+n2+n4,3)*Q(n3+n5+n6+n7,4)+24.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6+n7,5)
                - 24.*Q(n2+n4,2)*Q(n1+n3+n5+n6+n7,5)+24.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6+n7,5)
                - 24.*Q(n1+n4,2)*Q(n2+n3+n5+n6+n7,5)-120.*Q(n4,1)*Q(n1+n2+n3+n5+n6+n7,6)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6+n7,4)+6.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6+n7,4)
                + 6.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6+n7,4)+6.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6+n7,4)
                - 12.*Q(n1+n2+n3,3)*Q(n4+n5+n6+n7,4)+24.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6+n7,5)
                - 24.*Q(n2+n3,2)*Q(n1+n4+n5+n6+n7,5)+24.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6+n7,5)
                - 24.*Q(n1+n3,2)*Q(n2+n4+n5+n6+n7,5)-120.*Q(n3,1)*Q(n1+n2+n4+n5+n6+n7,6)
                + 24.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6+n7,5)-24.*Q(n1+n2,2)*Q(n3+n4+n5+n6+n7,5)
                - 120.*Q(n2,1)*Q(n1+n3+n4+n5+n6+n7,6)-120.*Q(n1,1)*Q(n2+n3+n4+n5+n6+n7,6)
                + 720.*Q(n1+n2+n3+n4+n5+n6+n7,7);

 return seven;

} // TComplex Seven(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7)

//=======================================================================================================================

TComplex Eight_1(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)
{
 // Generic eight-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)]>, first part.

 TComplex eight = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n7,1)*Q(n8,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n8,1)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n7,1)*Q(n8,1)+24.*Q(n1+n2+n3+n4+n5,5)*Q(n6,1)*Q(n7,1)*Q(n8,1)
                - Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)+Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)+Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)-Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n2+n3+n4+n5,4)*Q(n1+n6,2)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)+6.*Q(n1+n3+n4+n5,4)*Q(n2+n6,2)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n8,1)
                + 4.*Q(n3+n4+n5,3)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)-Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)-Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)+6.*Q(n1+n2+n4+n5,4)*Q(n3+n6,2)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n8,1)
                + 4.*Q(n2+n4+n5,3)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n8,1)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n8,1)+4.*Q(n1+n4+n5,3)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n7,1)*Q(n8,1)+6.*Q(n4+n5,2)*Q(n1+n2+n3+n6,4)*Q(n7,1)*Q(n8,1)
                - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)+Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)+Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)+Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)-Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n1+n2+n3+n5,4)*Q(n4+n6,2)*Q(n7,1)*Q(n8,1)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n8,1)+4.*Q(n2+n3+n5,3)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n8,1)
                + 4.*Q(n1+n3+n5,3)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n8,1)-6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n3+n5,2)*Q(n1+n2+n4+n6,4)*Q(n7,1)*Q(n8,1)+2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n8,1)+4.*Q(n1+n2+n5,3)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n7,1)*Q(n8,1)+6.*Q(n2+n5,2)*Q(n1+n3+n4+n6,4)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n7,1)*Q(n8,1)+6.*Q(n1+n5,2)*Q(n2+n3+n4+n6,4)*Q(n7,1)*Q(n8,1)
                + 24.*Q(n5,1)*Q(n1+n2+n3+n4+n6,5)*Q(n7,1)*Q(n8,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)+6.*Q(n1+n2+n3+n4,4)*Q(n5+n6,2)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n8,1)
                + 4.*Q(n2+n3+n4,3)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n8,1)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n8,1)+4.*Q(n1+n3+n4,3)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n7,1)*Q(n8,1)+6.*Q(n3+n4,2)*Q(n1+n2+n5+n6,4)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n8,1)
                + 4.*Q(n1+n2+n4,3)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n8,1)-6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n2+n4,2)*Q(n1+n3+n5+n6,4)*Q(n7,1)*Q(n8,1)-6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n1+n4,2)*Q(n2+n3+n5+n6,4)*Q(n7,1)*Q(n8,1)+24.*Q(n4,1)*Q(n1+n2+n3+n5+n6,5)*Q(n7,1)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n8,1)
                + 4.*Q(n1+n2+n3,3)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n8,1)-6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n2+n3,2)*Q(n1+n4+n5+n6,4)*Q(n7,1)*Q(n8,1)-6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n7,1)*Q(n8,1)
                + 6.*Q(n1+n3,2)*Q(n2+n4+n5+n6,4)*Q(n7,1)*Q(n8,1)+24.*Q(n3,1)*Q(n1+n2+n4+n5+n6,5)*Q(n7,1)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n7,1)*Q(n8,1)+6.*Q(n1+n2,2)*Q(n3+n4+n5+n6,4)*Q(n7,1)*Q(n8,1)
                + 24.*Q(n2,1)*Q(n1+n3+n4+n5+n6,5)*Q(n7,1)*Q(n8,1)+24.*Q(n1,1)*Q(n2+n3+n4+n5+n6,5)*Q(n7,1)*Q(n8,1)
                - 120.*Q(n1+n2+n3+n4+n5+n6,6)*Q(n7,1)*Q(n8,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                + Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)+Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)-2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                + Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)-Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)-Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)+Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                - Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)+6.*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n1+n7,2)*Q(n8,1)
                + Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n8,1)
                - Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n8,1)+Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n8,1)
                - Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n8,1)+2.*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n7,2)*Q(n8,1)+2.*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n1+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n1+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n1+n7,2)*Q(n8,1)+6.*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n1+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n8,1)-Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n1+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n7,2)*Q(n8,1)
                + 2.*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n1+n7,2)*Q(n8,1)+6.*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n1+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n7,2)*Q(n8,1)+2.*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n1+n7,2)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n1+n7,2)*Q(n8,1)+6.*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n1+n7,2)*Q(n8,1)
                - 24.*Q(n2+n3+n4+n5+n6,5)*Q(n1+n7,2)*Q(n8,1)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                - Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)+6.*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n2+n7,2)*Q(n8,1)
                + Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n8,1)
                - Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n8,1)+Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n8,1)
                - Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n8,1)+2.*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n7,2)*Q(n8,1)+2.*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n2+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n1,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n2+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n2+n7,2)*Q(n8,1)+6.*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n2+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n8,1)-Q(n1,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n2+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n2+n7,2)*Q(n8,1)
                + 2.*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n2+n7,2)*Q(n8,1)+6.*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n2+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n2+n7,2)*Q(n8,1)+2.*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n2+n7,2)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n2+n7,2)*Q(n8,1)+6.*Q(n1,1)*Q(n3+n4+n5+n6,4)*Q(n2+n7,2)*Q(n8,1)
                - 24.*Q(n1+n3+n4+n5+n6,5)*Q(n2+n7,2)*Q(n8,1)+2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n8,1)
                - 2.*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n8,1)-2.*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n8,1)+4.*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n7,3)*Q(n8,1)+2.*Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n2+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n7,3)*Q(n8,1)+2.*Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n2+n7,3)*Q(n8,1)
                + 4.*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n2+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n7,3)*Q(n8,1)
                + 2.*Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n2+n7,3)*Q(n8,1)+4.*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n2+n7,3)*Q(n8,1)
                + 4.*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n2+n7,3)*Q(n8,1)-12.*Q(n3+n4+n5+n6,4)*Q(n1+n2+n7,3)*Q(n8,1)
                - Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)+Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                - 2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)+Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                - Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)+Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                - Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)-2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)-Q(n1+n2,2)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)
                + 6.*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n3+n7,2)*Q(n8,1)+Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n8,1)-Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n8,1)-Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n8,1)-Q(n1,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n8,1)
                + 2.*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n8,1)-2.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n7,2)*Q(n8,1)
                + 2.*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n3+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n1+n2,2)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n8,1)-Q(n2,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n3+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n3+n7,2)*Q(n8,1)
                + 6.*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n3+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n1+n2,2)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n8,1)-Q(n2,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n3+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n3+n7,2)*Q(n8,1)+2.*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n3+n7,2)*Q(n8,1)
                + 6.*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n3+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n2,1)*Q(n4+n5+n6,3)*Q(n3+n7,2)*Q(n8,1)
                + 2.*Q(n1+n2,2)*Q(n4+n5+n6,3)*Q(n3+n7,2)*Q(n8,1)+6.*Q(n2,1)*Q(n1+n4+n5+n6,4)*Q(n3+n7,2)*Q(n8,1)
                + 6.*Q(n1,1)*Q(n2+n4+n5+n6,4)*Q(n3+n7,2)*Q(n8,1)-24.*Q(n1+n2+n4+n5+n6,5)*Q(n3+n7,2)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n8,1)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n8,1)
                + 4.*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n8,1)-2.*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n7,3)*Q(n8,1)
                + 2.*Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n3+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n3+n7,3)*Q(n8,1)
                + 2.*Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n3+n7,3)*Q(n8,1)+4.*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n3+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n3+n7,3)*Q(n8,1)+2.*Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n3+n7,3)*Q(n8,1)
                + 4.*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n3+n7,3)*Q(n8,1)+4.*Q(n2,1)*Q(n4+n5+n6,3)*Q(n1+n3+n7,3)*Q(n8,1)
                - 12.*Q(n2+n4+n5+n6,4)*Q(n1+n3+n7,3)*Q(n8,1)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n8,1)
                - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n8,1)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n8,1)+4.*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n8,1)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n7,3)*Q(n8,1)+2.*Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n3+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n3+n7,3)*Q(n8,1)+2.*Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n3+n7,3)*Q(n8,1)
                + 4.*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n3+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n3+n7,3)*Q(n8,1)
                + 2.*Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n3+n7,3)*Q(n8,1)+4.*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n3+n7,3)*Q(n8,1)
                + 4.*Q(n1,1)*Q(n4+n5+n6,3)*Q(n2+n3+n7,3)*Q(n8,1)-12.*Q(n1+n4+n5+n6,4)*Q(n2+n3+n7,3)*Q(n8,1)
                - 6.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n7,4)*Q(n8,1)+6.*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n3+n7,4)*Q(n8,1)
                + 6.*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n3+n7,4)*Q(n8,1)+6.*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n3+n7,4)*Q(n8,1)
                - 12.*Q(n4+n5+n6,3)*Q(n1+n2+n3+n7,4)*Q(n8,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                + Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)+Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)-2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)-Q(n2+n3,2)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)-Q(n1+n3,2)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                - Q(n1+n2,2)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)+6.*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n4+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n2+n3,2)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n2,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n8,1)+Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n8,1)
                - Q(n1+n3,2)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n3,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n8,1)+2.*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n4+n7,2)*Q(n8,1)+2.*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n4+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n1+n2,2)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n1,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n4+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n4+n7,2)*Q(n8,1)+6.*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n4+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n1+n2,2)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n1+n3,2)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n8,1)-Q(n1,1)*Q(n2+n3,2)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n1+n2+n3,3)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5+n6,3)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n2+n3,2)*Q(n1+n5+n6,3)*Q(n4+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5+n6,3)*Q(n4+n7,2)*Q(n8,1)
                + 2.*Q(n1+n3,2)*Q(n2+n5+n6,3)*Q(n4+n7,2)*Q(n8,1)+6.*Q(n3,1)*Q(n1+n2+n5+n6,4)*Q(n4+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5+n6,3)*Q(n4+n7,2)*Q(n8,1)+2.*Q(n1+n2,2)*Q(n3+n5+n6,3)*Q(n4+n7,2)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n1+n3+n5+n6,4)*Q(n4+n7,2)*Q(n8,1)+6.*Q(n1,1)*Q(n2+n3+n5+n6,4)*Q(n4+n7,2)*Q(n8,1)
                - 24.*Q(n1+n2+n3+n5+n6,5)*Q(n4+n7,2)*Q(n8,1)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n8,1)
                - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n8,1)+4.*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n4+n7,3)*Q(n8,1)+2.*Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n4+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n4+n7,3)*Q(n8,1)+2.*Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n4+n7,3)*Q(n8,1)
                + 4.*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n4+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n1+n4+n7,3)*Q(n8,1)
                + 2.*Q(n2+n3,2)*Q(n5+n6,2)*Q(n1+n4+n7,3)*Q(n8,1)+4.*Q(n3,1)*Q(n2+n5+n6,3)*Q(n1+n4+n7,3)*Q(n8,1)
                + 4.*Q(n2,1)*Q(n3+n5+n6,3)*Q(n1+n4+n7,3)*Q(n8,1)-12.*Q(n2+n3+n5+n6,4)*Q(n1+n4+n7,3)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n8,1)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n8,1)
                + 4.*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n4+n7,3)*Q(n8,1)
                + 2.*Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n4+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n4+n7,3)*Q(n8,1)
                + 2.*Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n4+n7,3)*Q(n8,1)+4.*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n4+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5+n6,2)*Q(n2+n4+n7,3)*Q(n8,1)+2.*Q(n1+n3,2)*Q(n5+n6,2)*Q(n2+n4+n7,3)*Q(n8,1)
                + 4.*Q(n3,1)*Q(n1+n5+n6,3)*Q(n2+n4+n7,3)*Q(n8,1)+4.*Q(n1,1)*Q(n3+n5+n6,3)*Q(n2+n4+n7,3)*Q(n8,1)
                - 12.*Q(n1+n3+n5+n6,4)*Q(n2+n4+n7,3)*Q(n8,1)-6.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n4+n7,4)*Q(n8,1)
                + 6.*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n4+n7,4)*Q(n8,1)+6.*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n4+n7,4)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n5+n6,2)*Q(n1+n2+n4+n7,4)*Q(n8,1)-12.*Q(n3+n5+n6,3)*Q(n1+n2+n4+n7,4)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n8,1)-2.*Q(n1+n2,2)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n8,1)
                + 4.*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n4+n7,3)*Q(n8,1)
                + 2.*Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n4+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n4+n7,3)*Q(n8,1)
                + 2.*Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n4+n7,3)*Q(n8,1)+4.*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n4+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5+n6,2)*Q(n3+n4+n7,3)*Q(n8,1)+2.*Q(n1+n2,2)*Q(n5+n6,2)*Q(n3+n4+n7,3)*Q(n8,1)
                + 4.*Q(n2,1)*Q(n1+n5+n6,3)*Q(n3+n4+n7,3)*Q(n8,1)+4.*Q(n1,1)*Q(n2+n5+n6,3)*Q(n3+n4+n7,3)*Q(n8,1)
                - 12.*Q(n1+n2+n5+n6,4)*Q(n3+n4+n7,3)*Q(n8,1)-6.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n4+n7,4)*Q(n8,1)
                + 6.*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n4+n7,4)*Q(n8,1)+6.*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n4+n7,4)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n5+n6,2)*Q(n1+n3+n4+n7,4)*Q(n8,1)-12.*Q(n2+n5+n6,3)*Q(n1+n3+n4+n7,4)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n4+n7,4)*Q(n8,1)+6.*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n4+n7,4)*Q(n8,1)
                + 6.*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n4+n7,4)*Q(n8,1)+6.*Q(n1,1)*Q(n5+n6,2)*Q(n2+n3+n4+n7,4)*Q(n8,1)
                - 12.*Q(n1+n5+n6,3)*Q(n2+n3+n4+n7,4)*Q(n8,1)+24.*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n4+n7,5)*Q(n8,1)
                - 24.*Q(n5+n6,2)*Q(n1+n2+n3+n4+n7,5)*Q(n8,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                - Q(n1+n2,2)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)+6.*Q(n1+n2+n3+n4,4)*Q(n6,1)*Q(n5+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n2+n3,2)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n2+n4,2)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n2,1)*Q(n3+n4,2)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n2+n3+n4,3)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n8,1)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n8,1)
                - Q(n1+n3,2)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n3,1)*Q(n1+n4,2)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n3+n4,2)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n8,1)+2.*Q(n1+n3+n4,3)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n6,3)*Q(n5+n7,2)*Q(n8,1)+2.*Q(n3+n4,2)*Q(n1+n2+n6,3)*Q(n5+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n1+n2,2)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n1+n4,2)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n1,1)*Q(n2+n4,2)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n1+n2+n4,3)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n6,3)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n2+n4,2)*Q(n1+n3+n6,3)*Q(n5+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n6,3)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n1+n4,2)*Q(n2+n3+n6,3)*Q(n5+n7,2)*Q(n8,1)+6.*Q(n4,1)*Q(n1+n2+n3+n6,4)*Q(n5+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n8,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n1+n2+n3,3)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n8,1)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n6,3)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n2+n3,2)*Q(n1+n4+n6,3)*Q(n5+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n6,3)*Q(n5+n7,2)*Q(n8,1)
                + 2.*Q(n1+n3,2)*Q(n2+n4+n6,3)*Q(n5+n7,2)*Q(n8,1)+6.*Q(n3,1)*Q(n1+n2+n4+n6,4)*Q(n5+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n6,3)*Q(n5+n7,2)*Q(n8,1)+2.*Q(n1+n2,2)*Q(n3+n4+n6,3)*Q(n5+n7,2)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n1+n3+n4+n6,4)*Q(n5+n7,2)*Q(n8,1)+6.*Q(n1,1)*Q(n2+n3+n4+n6,4)*Q(n5+n7,2)*Q(n8,1)
                - 24.*Q(n1+n2+n3+n4+n6,5)*Q(n5+n7,2)*Q(n8,1)+2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n8,1)
                - 2.*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n8,1)+4.*Q(n2+n3+n4,3)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n1+n5+n7,3)*Q(n8,1)+2.*Q(n3+n4,2)*Q(n2+n6,2)*Q(n1+n5+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n1+n5+n7,3)*Q(n8,1)+2.*Q(n2+n4,2)*Q(n3+n6,2)*Q(n1+n5+n7,3)*Q(n8,1)
                + 4.*Q(n4,1)*Q(n2+n3+n6,3)*Q(n1+n5+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n1+n5+n7,3)*Q(n8,1)
                + 2.*Q(n2+n3,2)*Q(n4+n6,2)*Q(n1+n5+n7,3)*Q(n8,1)+4.*Q(n3,1)*Q(n2+n4+n6,3)*Q(n1+n5+n7,3)*Q(n8,1)
                + 4.*Q(n2,1)*Q(n3+n4+n6,3)*Q(n1+n5+n7,3)*Q(n8,1)-12.*Q(n2+n3+n4+n6,4)*Q(n1+n5+n7,3)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n8,1)-2.*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n3+n4,2)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n8,1)
                + 4.*Q(n1+n3+n4,3)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n2+n5+n7,3)*Q(n8,1)
                + 2.*Q(n3+n4,2)*Q(n1+n6,2)*Q(n2+n5+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n4,1)*Q(n3+n6,2)*Q(n2+n5+n7,3)*Q(n8,1)
                + 2.*Q(n1+n4,2)*Q(n3+n6,2)*Q(n2+n5+n7,3)*Q(n8,1)+4.*Q(n4,1)*Q(n1+n3+n6,3)*Q(n2+n5+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4+n6,2)*Q(n2+n5+n7,3)*Q(n8,1)+2.*Q(n1+n3,2)*Q(n4+n6,2)*Q(n2+n5+n7,3)*Q(n8,1)
                + 4.*Q(n3,1)*Q(n1+n4+n6,3)*Q(n2+n5+n7,3)*Q(n8,1)+4.*Q(n1,1)*Q(n3+n4+n6,3)*Q(n2+n5+n7,3)*Q(n8,1)
                - 12.*Q(n1+n3+n4+n6,4)*Q(n2+n5+n7,3)*Q(n8,1)-6.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n2+n5+n7,4)*Q(n8,1)
                + 6.*Q(n3+n4,2)*Q(n6,1)*Q(n1+n2+n5+n7,4)*Q(n8,1)+6.*Q(n4,1)*Q(n3+n6,2)*Q(n1+n2+n5+n7,4)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n4+n6,2)*Q(n1+n2+n5+n7,4)*Q(n8,1)-12.*Q(n3+n4+n6,3)*Q(n1+n2+n5+n7,4)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n8,1)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n8,1)
                + 4.*Q(n1+n2+n4,3)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n6,2)*Q(n3+n5+n7,3)*Q(n8,1)
                + 2.*Q(n2+n4,2)*Q(n1+n6,2)*Q(n3+n5+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n6,2)*Q(n3+n5+n7,3)*Q(n8,1)
                + 2.*Q(n1+n4,2)*Q(n2+n6,2)*Q(n3+n5+n7,3)*Q(n8,1)+4.*Q(n4,1)*Q(n1+n2+n6,3)*Q(n3+n5+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4+n6,2)*Q(n3+n5+n7,3)*Q(n8,1)+2.*Q(n1+n2,2)*Q(n4+n6,2)*Q(n3+n5+n7,3)*Q(n8,1)
                + 4.*Q(n2,1)*Q(n1+n4+n6,3)*Q(n3+n5+n7,3)*Q(n8,1)+4.*Q(n1,1)*Q(n2+n4+n6,3)*Q(n3+n5+n7,3)*Q(n8,1)
                - 12.*Q(n1+n2+n4+n6,4)*Q(n3+n5+n7,3)*Q(n8,1)-6.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n1+n3+n5+n7,4)*Q(n8,1)
                + 6.*Q(n2+n4,2)*Q(n6,1)*Q(n1+n3+n5+n7,4)*Q(n8,1)+6.*Q(n4,1)*Q(n2+n6,2)*Q(n1+n3+n5+n7,4)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n4+n6,2)*Q(n1+n3+n5+n7,4)*Q(n8,1)-12.*Q(n2+n4+n6,3)*Q(n1+n3+n5+n7,4)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n2+n3+n5+n7,4)*Q(n8,1)+6.*Q(n1+n4,2)*Q(n6,1)*Q(n2+n3+n5+n7,4)*Q(n8,1)
                + 6.*Q(n4,1)*Q(n1+n6,2)*Q(n2+n3+n5+n7,4)*Q(n8,1)+6.*Q(n1,1)*Q(n4+n6,2)*Q(n2+n3+n5+n7,4)*Q(n8,1)
                - 12.*Q(n1+n4+n6,3)*Q(n2+n3+n5+n7,4)*Q(n8,1)+24.*Q(n4,1)*Q(n6,1)*Q(n1+n2+n3+n5+n7,5)*Q(n8,1)
                - 24.*Q(n4+n6,2)*Q(n1+n2+n3+n5+n7,5)*Q(n8,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n8,1)
                - 2.*Q(n1+n2,2)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n3,2)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n3,2)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n8,1)+4.*Q(n1+n2+n3,3)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n6,2)*Q(n4+n5+n7,3)*Q(n8,1)+2.*Q(n2+n3,2)*Q(n1+n6,2)*Q(n4+n5+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n6,2)*Q(n4+n5+n7,3)*Q(n8,1)+2.*Q(n1+n3,2)*Q(n2+n6,2)*Q(n4+n5+n7,3)*Q(n8,1)
                + 4.*Q(n3,1)*Q(n1+n2+n6,3)*Q(n4+n5+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n6,2)*Q(n4+n5+n7,3)*Q(n8,1)
                + 2.*Q(n1+n2,2)*Q(n3+n6,2)*Q(n4+n5+n7,3)*Q(n8,1)+4.*Q(n2,1)*Q(n1+n3+n6,3)*Q(n4+n5+n7,3)*Q(n8,1)
                + 4.*Q(n1,1)*Q(n2+n3+n6,3)*Q(n4+n5+n7,3)*Q(n8,1)-12.*Q(n1+n2+n3+n6,4)*Q(n4+n5+n7,3)*Q(n8,1)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n1+n4+n5+n7,4)*Q(n8,1)+6.*Q(n2+n3,2)*Q(n6,1)*Q(n1+n4+n5+n7,4)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n2+n6,2)*Q(n1+n4+n5+n7,4)*Q(n8,1)+6.*Q(n2,1)*Q(n3+n6,2)*Q(n1+n4+n5+n7,4)*Q(n8,1)
                - 12.*Q(n2+n3+n6,3)*Q(n1+n4+n5+n7,4)*Q(n8,1)-6.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n2+n4+n5+n7,4)*Q(n8,1)
                + 6.*Q(n1+n3,2)*Q(n6,1)*Q(n2+n4+n5+n7,4)*Q(n8,1)+6.*Q(n3,1)*Q(n1+n6,2)*Q(n2+n4+n5+n7,4)*Q(n8,1)
                + 6.*Q(n1,1)*Q(n3+n6,2)*Q(n2+n4+n5+n7,4)*Q(n8,1)-12.*Q(n1+n3+n6,3)*Q(n2+n4+n5+n7,4)*Q(n8,1)
                + 24.*Q(n3,1)*Q(n6,1)*Q(n1+n2+n4+n5+n7,5)*Q(n8,1)-24.*Q(n3+n6,2)*Q(n1+n2+n4+n5+n7,5)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n3+n4+n5+n7,4)*Q(n8,1)+6.*Q(n1+n2,2)*Q(n6,1)*Q(n3+n4+n5+n7,4)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n1+n6,2)*Q(n3+n4+n5+n7,4)*Q(n8,1)+6.*Q(n1,1)*Q(n2+n6,2)*Q(n3+n4+n5+n7,4)*Q(n8,1)
                - 12.*Q(n1+n2+n6,3)*Q(n3+n4+n5+n7,4)*Q(n8,1)+24.*Q(n2,1)*Q(n6,1)*Q(n1+n3+n4+n5+n7,5)*Q(n8,1)
                - 24.*Q(n2+n6,2)*Q(n1+n3+n4+n5+n7,5)*Q(n8,1)+24.*Q(n1,1)*Q(n6,1)*Q(n2+n3+n4+n5+n7,5)*Q(n8,1)
                - 24.*Q(n1+n6,2)*Q(n2+n3+n4+n5+n7,5)*Q(n8,1)-120.*Q(n6,1)*Q(n1+n2+n3+n4+n5+n7,6)*Q(n8,1)
                - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)+Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                + Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                - 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)+Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                - Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)+Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                - Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)-Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)
                + 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6+n7,2)*Q(n8,1)+Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n8,1)-Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n8,1)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n8,1)-Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n8,1)-Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n8,1)
                + 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n8,1)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6+n7,2)*Q(n8,1)
                + 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n8,1)-Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6+n7,2)*Q(n8,1)
                + 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6+n7,2)*Q(n8,1)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n8,1)-Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6+n7,2)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6+n7,2)*Q(n8,1)+2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6+n7,2)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6+n7,2)*Q(n8,1)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6+n7,2)*Q(n8,1)
                + 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6+n7,2)*Q(n8,1)+6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6+n7,2)*Q(n8,1)
                + 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6+n7,2)*Q(n8,1)-24.*Q(n1+n2+n3+n4+n5,5)*Q(n6+n7,2)*Q(n8,1)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n8,1)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n8,1)
                + 4.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6+n7,3)*Q(n8,1)
                + 2.*Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6+n7,3)*Q(n8,1)
                + 2.*Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6+n7,3)*Q(n8,1)+4.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6+n7,3)*Q(n8,1)+2.*Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6+n7,3)*Q(n8,1)
                + 4.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6+n7,3)*Q(n8,1)+4.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6+n7,3)*Q(n8,1)
                - 12.*Q(n2+n3+n4+n5,4)*Q(n1+n6+n7,3)*Q(n8,1)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n8,1)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n8,1)+4.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n8,1)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6+n7,3)*Q(n8,1)+2.*Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6+n7,3)*Q(n8,1)+2.*Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6+n7,3)*Q(n8,1)
                + 4.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6+n7,3)*Q(n8,1)
                + 2.*Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6+n7,3)*Q(n8,1)+4.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6+n7,3)*Q(n8,1)
                + 4.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6+n7,3)*Q(n8,1)-12.*Q(n1+n3+n4+n5,4)*Q(n2+n6+n7,3)*Q(n8,1)
                - 6.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6+n7,4)*Q(n8,1)+6.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6+n7,4)*Q(n8,1)
                + 6.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6+n7,4)*Q(n8,1)+6.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6+n7,4)*Q(n8,1)
                - 12.*Q(n3+n4+n5,3)*Q(n1+n2+n6+n7,4)*Q(n8,1)+2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n8,1)+4.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6+n7,3)*Q(n8,1)+2.*Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6+n7,3)*Q(n8,1)+2.*Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6+n7,3)*Q(n8,1)
                + 4.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6+n7,3)*Q(n8,1)
                + 2.*Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6+n7,3)*Q(n8,1)+4.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6+n7,3)*Q(n8,1)
                + 4.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6+n7,3)*Q(n8,1)-12.*Q(n1+n2+n4+n5,4)*Q(n3+n6+n7,3)*Q(n8,1)
                - 6.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6+n7,4)*Q(n8,1)+6.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6+n7,4)*Q(n8,1)
                + 6.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6+n7,4)*Q(n8,1)+6.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6+n7,4)*Q(n8,1)
                - 12.*Q(n2+n4+n5,3)*Q(n1+n3+n6+n7,4)*Q(n8,1)-6.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6+n7,4)*Q(n8,1)
                + 6.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6+n7,4)*Q(n8,1)+6.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6+n7,4)*Q(n8,1)
                + 6.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6+n7,4)*Q(n8,1)-12.*Q(n1+n4+n5,3)*Q(n2+n3+n6+n7,4)*Q(n8,1)
                + 24.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6+n7,5)*Q(n8,1)-24.*Q(n4+n5,2)*Q(n1+n2+n3+n6+n7,5)*Q(n8,1)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n8,1)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n8,1)
                + 4.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6+n7,3)*Q(n8,1)
                + 2.*Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6+n7,3)*Q(n8,1)
                + 2.*Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6+n7,3)*Q(n8,1)+4.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6+n7,3)*Q(n8,1)+2.*Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6+n7,3)*Q(n8,1)
                + 4.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6+n7,3)*Q(n8,1)+4.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6+n7,3)*Q(n8,1)
                - 12.*Q(n1+n2+n3+n5,4)*Q(n4+n6+n7,3)*Q(n8,1)-6.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6+n7,4)*Q(n8,1)
                + 6.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6+n7,4)*Q(n8,1)+6.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6+n7,4)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6+n7,4)*Q(n8,1)-12.*Q(n2+n3+n5,3)*Q(n1+n4+n6+n7,4)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6+n7,4)*Q(n8,1)+6.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6+n7,4)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6+n7,4)*Q(n8,1)+6.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6+n7,4)*Q(n8,1)
                - 12.*Q(n1+n3+n5,3)*Q(n2+n4+n6+n7,4)*Q(n8,1)+24.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6+n7,5)*Q(n8,1)
                - 24.*Q(n3+n5,2)*Q(n1+n2+n4+n6+n7,5)*Q(n8,1)-6.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6+n7,4)*Q(n8,1)
                + 6.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6+n7,4)*Q(n8,1)+6.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6+n7,4)*Q(n8,1)
                + 6.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6+n7,4)*Q(n8,1)-12.*Q(n1+n2+n5,3)*Q(n3+n4+n6+n7,4)*Q(n8,1)
                + 24.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6+n7,5)*Q(n8,1)-24.*Q(n2+n5,2)*Q(n1+n3+n4+n6+n7,5)*Q(n8,1)
                + 24.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6+n7,5)*Q(n8,1)-24.*Q(n1+n5,2)*Q(n2+n3+n4+n6+n7,5)*Q(n8,1)
                - 120.*Q(n5,1)*Q(n1+n2+n3+n4+n6+n7,6)*Q(n8,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n8,1)-2.*Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n8,1)+4.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n8,1)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6+n7,3)*Q(n8,1)+2.*Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6+n7,3)*Q(n8,1)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6+n7,3)*Q(n8,1)+2.*Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6+n7,3)*Q(n8,1)
                + 4.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6+n7,3)*Q(n8,1)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6+n7,3)*Q(n8,1)
                + 2.*Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6+n7,3)*Q(n8,1)+4.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6+n7,3)*Q(n8,1)
                + 4.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6+n7,3)*Q(n8,1)-12.*Q(n1+n2+n3+n4,4)*Q(n5+n6+n7,3)*Q(n8,1)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6+n7,4)*Q(n8,1)+6.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6+n7,4)*Q(n8,1)
                + 6.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6+n7,4)*Q(n8,1)+6.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6+n7,4)*Q(n8,1)
                - 12.*Q(n2+n3+n4,3)*Q(n1+n5+n6+n7,4)*Q(n8,1)-6.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6+n7,4)*Q(n8,1)
                + 6.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6+n7,4)*Q(n8,1)+6.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6+n7,4)*Q(n8,1)
                + 6.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6+n7,4)*Q(n8,1)-12.*Q(n1+n3+n4,3)*Q(n2+n5+n6+n7,4)*Q(n8,1)
                + 24.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6+n7,5)*Q(n8,1)-24.*Q(n3+n4,2)*Q(n1+n2+n5+n6+n7,5)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6+n7,4)*Q(n8,1)+6.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6+n7,4)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6+n7,4)*Q(n8,1)+6.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6+n7,4)*Q(n8,1)
                - 12.*Q(n1+n2+n4,3)*Q(n3+n5+n6+n7,4)*Q(n8,1)+24.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6+n7,5)*Q(n8,1)
                - 24.*Q(n2+n4,2)*Q(n1+n3+n5+n6+n7,5)*Q(n8,1)+24.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6+n7,5)*Q(n8,1)
                - 24.*Q(n1+n4,2)*Q(n2+n3+n5+n6+n7,5)*Q(n8,1)-120.*Q(n4,1)*Q(n1+n2+n3+n5+n6+n7,6)*Q(n8,1)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6+n7,4)*Q(n8,1)+6.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6+n7,4)*Q(n8,1)
                + 6.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6+n7,4)*Q(n8,1)+6.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6+n7,4)*Q(n8,1)
                - 12.*Q(n1+n2+n3,3)*Q(n4+n5+n6+n7,4)*Q(n8,1)+24.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6+n7,5)*Q(n8,1)
                - 24.*Q(n2+n3,2)*Q(n1+n4+n5+n6+n7,5)*Q(n8,1)+24.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6+n7,5)*Q(n8,1)
                - 24.*Q(n1+n3,2)*Q(n2+n4+n5+n6+n7,5)*Q(n8,1)-120.*Q(n3,1)*Q(n1+n2+n4+n5+n6+n7,6)*Q(n8,1)
                + 24.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6+n7,5)*Q(n8,1)-24.*Q(n1+n2,2)*Q(n3+n4+n5+n6+n7,5)*Q(n8,1)
                - 120.*Q(n2,1)*Q(n1+n3+n4+n5+n6+n7,6)*Q(n8,1)-120.*Q(n1,1)*Q(n2+n3+n4+n5+n6+n7,6)*Q(n8,1)
                + 720.*Q(n1+n2+n3+n4+n5+n6+n7,7)*Q(n8,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                + Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)+Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                + Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)-2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                + Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)-Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                + Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)-Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                - 2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)+Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                - Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)-2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                - 2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)+6.*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n7,1)*Q(n1+n8,2)
                + Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n8,2)
                - Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n8,2)+Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n8,2)
                - Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n8,2)
                - Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n8,2)+2.*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n8,2)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n1+n8,2)+2.*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n1+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n8,2)
                - Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n8,2)-2.*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n1+n8,2)-2.*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n1+n8,2)+6.*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n7,1)*Q(n1+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n8,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n8,2)-Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n8,2)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n1+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n1+n8,2)
                + 2.*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n1+n8,2)+6.*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n7,1)*Q(n1+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n1+n8,2)+2.*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n1+n8,2)
                + 6.*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n7,1)*Q(n1+n8,2)+6.*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n7,1)*Q(n1+n8,2)
                - 24.*Q(n2+n3+n4+n5+n6,5)*Q(n7,1)*Q(n1+n8,2)+Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n8,2)
                - Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n8,2)-Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n8,2)
                - Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n8,2)+2.*Q(n3+n4+n5,3)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n8,2)
                - Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n1+n8,2)+Q(n4+n5,2)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n1+n8,2)
                - Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n1+n8,2)+Q(n3+n5,2)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n1+n8,2)
                + 2.*Q(n5,1)*Q(n3+n4+n6,3)*Q(n2+n7,2)*Q(n1+n8,2)-Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n1+n8,2)
                + Q(n3+n4,2)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n1+n8,2)+2.*Q(n4,1)*Q(n3+n5+n6,3)*Q(n2+n7,2)*Q(n1+n8,2)
                + 2.*Q(n3,1)*Q(n4+n5+n6,3)*Q(n2+n7,2)*Q(n1+n8,2)-6.*Q(n3+n4+n5+n6,4)*Q(n2+n7,2)*Q(n1+n8,2)
                + Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n8,2)-Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n8,2)
                - Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n8,2)
                + 2.*Q(n2+n4+n5,3)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n8,2)-Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n1+n8,2)
                + Q(n4+n5,2)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n1+n8,2)
                + Q(n2+n5,2)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n1+n8,2)+2.*Q(n5,1)*Q(n2+n4+n6,3)*Q(n3+n7,2)*Q(n1+n8,2)
                - Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n1+n8,2)+Q(n2+n4,2)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n1+n8,2)
                + 2.*Q(n4,1)*Q(n2+n5+n6,3)*Q(n3+n7,2)*Q(n1+n8,2)+2.*Q(n2,1)*Q(n4+n5+n6,3)*Q(n3+n7,2)*Q(n1+n8,2)
                - 6.*Q(n2+n4+n5+n6,4)*Q(n3+n7,2)*Q(n1+n8,2)-2.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n1+n8,2)
                + 2.*Q(n4+n5,2)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n1+n8,2)+2.*Q(n5,1)*Q(n4+n6,2)*Q(n2+n3+n7,3)*Q(n1+n8,2)
                + 2.*Q(n4,1)*Q(n5+n6,2)*Q(n2+n3+n7,3)*Q(n1+n8,2)-4.*Q(n4+n5+n6,3)*Q(n2+n3+n7,3)*Q(n1+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n8,2)-Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n8,2)
                - Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n8,2)
                + 2.*Q(n2+n3+n5,3)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n8,2)-Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n1+n8,2)
                + Q(n3+n5,2)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n1+n8,2)
                + Q(n2+n5,2)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n1+n8,2)+2.*Q(n5,1)*Q(n2+n3+n6,3)*Q(n4+n7,2)*Q(n1+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n1+n8,2)+Q(n2+n3,2)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n1+n8,2)
                + 2.*Q(n3,1)*Q(n2+n5+n6,3)*Q(n4+n7,2)*Q(n1+n8,2)+2.*Q(n2,1)*Q(n3+n5+n6,3)*Q(n4+n7,2)*Q(n1+n8,2)
                - 6.*Q(n2+n3+n5+n6,4)*Q(n4+n7,2)*Q(n1+n8,2)-2.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n1+n8,2)
                + 2.*Q(n3+n5,2)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n1+n8,2)+2.*Q(n5,1)*Q(n3+n6,2)*Q(n2+n4+n7,3)*Q(n1+n8,2)
                + 2.*Q(n3,1)*Q(n5+n6,2)*Q(n2+n4+n7,3)*Q(n1+n8,2)-4.*Q(n3+n5+n6,3)*Q(n2+n4+n7,3)*Q(n1+n8,2)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n1+n8,2)+2.*Q(n2+n5,2)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n1+n8,2)
                + 2.*Q(n5,1)*Q(n2+n6,2)*Q(n3+n4+n7,3)*Q(n1+n8,2)+2.*Q(n2,1)*Q(n5+n6,2)*Q(n3+n4+n7,3)*Q(n1+n8,2)
                - 4.*Q(n2+n5+n6,3)*Q(n3+n4+n7,3)*Q(n1+n8,2)+6.*Q(n5,1)*Q(n6,1)*Q(n2+n3+n4+n7,4)*Q(n1+n8,2)
                - 6.*Q(n5+n6,2)*Q(n2+n3+n4+n7,4)*Q(n1+n8,2)+Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n8,2)
                - Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n8,2)-Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n8,2)
                - Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n8,2)+2.*Q(n2+n3+n4,3)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n8,2)
                - Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n1+n8,2)+Q(n3+n4,2)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n1+n8,2)
                - Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n1+n8,2)+Q(n2+n4,2)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n1+n8,2);

 return eight;

} // TComplex Eight_1(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)

//==========================================================================================================================

TComplex Eight_2(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)
{
 // Generic eight-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)]>, second part.

 TComplex eight = 2.*Q(n4,1)*Q(n2+n3+n6,3)*Q(n5+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n1+n8,2)
                + Q(n2+n3,2)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n1+n8,2)+2.*Q(n3,1)*Q(n2+n4+n6,3)*Q(n5+n7,2)*Q(n1+n8,2)
                + 2.*Q(n2,1)*Q(n3+n4+n6,3)*Q(n5+n7,2)*Q(n1+n8,2)-6.*Q(n2+n3+n4+n6,4)*Q(n5+n7,2)*Q(n1+n8,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n1+n8,2)+2.*Q(n3+n4,2)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n1+n8,2)
                + 2.*Q(n4,1)*Q(n3+n6,2)*Q(n2+n5+n7,3)*Q(n1+n8,2)+2.*Q(n3,1)*Q(n4+n6,2)*Q(n2+n5+n7,3)*Q(n1+n8,2)
                - 4.*Q(n3+n4+n6,3)*Q(n2+n5+n7,3)*Q(n1+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n1+n8,2)
                + 2.*Q(n2+n4,2)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n1+n8,2)+2.*Q(n4,1)*Q(n2+n6,2)*Q(n3+n5+n7,3)*Q(n1+n8,2)
                + 2.*Q(n2,1)*Q(n4+n6,2)*Q(n3+n5+n7,3)*Q(n1+n8,2)-4.*Q(n2+n4+n6,3)*Q(n3+n5+n7,3)*Q(n1+n8,2)
                + 6.*Q(n4,1)*Q(n6,1)*Q(n2+n3+n5+n7,4)*Q(n1+n8,2)-6.*Q(n4+n6,2)*Q(n2+n3+n5+n7,4)*Q(n1+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n1+n8,2)+2.*Q(n2+n3,2)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n1+n8,2)
                + 2.*Q(n3,1)*Q(n2+n6,2)*Q(n4+n5+n7,3)*Q(n1+n8,2)+2.*Q(n2,1)*Q(n3+n6,2)*Q(n4+n5+n7,3)*Q(n1+n8,2)
                - 4.*Q(n2+n3+n6,3)*Q(n4+n5+n7,3)*Q(n1+n8,2)+6.*Q(n3,1)*Q(n6,1)*Q(n2+n4+n5+n7,4)*Q(n1+n8,2)
                - 6.*Q(n3+n6,2)*Q(n2+n4+n5+n7,4)*Q(n1+n8,2)+6.*Q(n2,1)*Q(n6,1)*Q(n3+n4+n5+n7,4)*Q(n1+n8,2)
                - 6.*Q(n2+n6,2)*Q(n3+n4+n5+n7,4)*Q(n1+n8,2)-24.*Q(n6,1)*Q(n2+n3+n4+n5+n7,5)*Q(n1+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n8,2)-Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n8,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n8,2)
                + 2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n8,2)-Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n1+n8,2)
                + Q(n3+n4,2)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n1+n8,2)-Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n1+n8,2)
                + Q(n2+n4,2)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n1+n8,2)+2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6+n7,2)*Q(n1+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n1+n8,2)+Q(n2+n3,2)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n1+n8,2)
                + 2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6+n7,2)*Q(n1+n8,2)+2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6+n7,2)*Q(n1+n8,2)
                - 6.*Q(n2+n3+n4+n5,4)*Q(n6+n7,2)*Q(n1+n8,2)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n1+n8,2)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6+n7,3)*Q(n1+n8,2)-4.*Q(n3+n4+n5,3)*Q(n2+n6+n7,3)*Q(n1+n8,2)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n1+n8,2)+2.*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6+n7,3)*Q(n1+n8,2)+2.*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6+n7,3)*Q(n1+n8,2)
                - 4.*Q(n2+n4+n5,3)*Q(n3+n6+n7,3)*Q(n1+n8,2)+6.*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6+n7,4)*Q(n1+n8,2)
                - 6.*Q(n4+n5,2)*Q(n2+n3+n6+n7,4)*Q(n1+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n1+n8,2)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6+n7,3)*Q(n1+n8,2)-4.*Q(n2+n3+n5,3)*Q(n4+n6+n7,3)*Q(n1+n8,2)
                + 6.*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6+n7,4)*Q(n1+n8,2)-6.*Q(n3+n5,2)*Q(n2+n4+n6+n7,4)*Q(n1+n8,2)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6+n7,4)*Q(n1+n8,2)-6.*Q(n2+n5,2)*Q(n3+n4+n6+n7,4)*Q(n1+n8,2)
                - 24.*Q(n5,1)*Q(n2+n3+n4+n6+n7,5)*Q(n1+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n1+n8,2)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6+n7,3)*Q(n1+n8,2)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6+n7,3)*Q(n1+n8,2)-4.*Q(n2+n3+n4,3)*Q(n5+n6+n7,3)*Q(n1+n8,2)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6+n7,4)*Q(n1+n8,2)-6.*Q(n3+n4,2)*Q(n2+n5+n6+n7,4)*Q(n1+n8,2)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6+n7,4)*Q(n1+n8,2)-6.*Q(n2+n4,2)*Q(n3+n5+n6+n7,4)*Q(n1+n8,2)
                - 24.*Q(n4,1)*Q(n2+n3+n5+n6+n7,5)*Q(n1+n8,2)+6.*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6+n7,4)*Q(n1+n8,2)
                - 6.*Q(n2+n3,2)*Q(n4+n5+n6+n7,4)*Q(n1+n8,2)-24.*Q(n3,1)*Q(n2+n4+n5+n6+n7,5)*Q(n1+n8,2)
                - 24.*Q(n2,1)*Q(n3+n4+n5+n6+n7,5)*Q(n1+n8,2)+120.*Q(n2+n3+n4+n5+n6+n7,6)*Q(n1+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)+Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                + Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)+Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                - 2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)+Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                - Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)+Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                - Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)-2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)-Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                - 2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)-2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)
                + 6.*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n7,1)*Q(n2+n8,2)+Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n8,2)-Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n8,2)
                + Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n8,2)-Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n8,2)-Q(n1,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n8,2)
                + 2.*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n8,2)-2.*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n2+n8,2)
                + 2.*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n2+n8,2)+Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n8,2)-Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n1,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n2+n8,2)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n2+n8,2)
                + 6.*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n7,1)*Q(n2+n8,2)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n8,2)-Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - Q(n1,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n8,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n2+n8,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n2+n8,2)+2.*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n2+n8,2)
                + 6.*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n7,1)*Q(n2+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n2+n8,2)
                + 2.*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n2+n8,2)+6.*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n7,1)*Q(n2+n8,2)
                + 6.*Q(n1,1)*Q(n3+n4+n5+n6,4)*Q(n7,1)*Q(n2+n8,2)-24.*Q(n1+n3+n4+n5+n6,5)*Q(n7,1)*Q(n2+n8,2)
                + Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n8,2)-Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n8,2)
                - Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n8,2)-Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n8,2)
                + 2.*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n8,2)-Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n2+n8,2)
                + Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n2+n8,2)-Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n2+n8,2)
                + Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n2+n8,2)+2.*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n7,2)*Q(n2+n8,2)
                - Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n2+n8,2)+Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n2+n8,2)
                + 2.*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n7,2)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n7,2)*Q(n2+n8,2)
                - 6.*Q(n3+n4+n5+n6,4)*Q(n1+n7,2)*Q(n2+n8,2)+Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n8,2)
                - Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n8,2)-Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n8,2)+2.*Q(n1+n4+n5,3)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n8,2)
                - Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n2+n8,2)+Q(n4+n5,2)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n2+n8,2)+Q(n1+n5,2)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n2+n8,2)
                + 2.*Q(n5,1)*Q(n1+n4+n6,3)*Q(n3+n7,2)*Q(n2+n8,2)-Q(n1,1)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n2+n8,2)
                + Q(n1+n4,2)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n2+n8,2)+2.*Q(n4,1)*Q(n1+n5+n6,3)*Q(n3+n7,2)*Q(n2+n8,2)
                + 2.*Q(n1,1)*Q(n4+n5+n6,3)*Q(n3+n7,2)*Q(n2+n8,2)-6.*Q(n1+n4+n5+n6,4)*Q(n3+n7,2)*Q(n2+n8,2)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n2+n8,2)+2.*Q(n4+n5,2)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n2+n8,2)
                + 2.*Q(n5,1)*Q(n4+n6,2)*Q(n1+n3+n7,3)*Q(n2+n8,2)+2.*Q(n4,1)*Q(n5+n6,2)*Q(n1+n3+n7,3)*Q(n2+n8,2)
                - 4.*Q(n4+n5+n6,3)*Q(n1+n3+n7,3)*Q(n2+n8,2)+Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n8,2)
                - Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n8,2)-Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n8,2)+2.*Q(n1+n3+n5,3)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n8,2)
                - Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n2+n8,2)+Q(n3+n5,2)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n2+n8,2)+Q(n1+n5,2)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n2+n8,2)
                + 2.*Q(n5,1)*Q(n1+n3+n6,3)*Q(n4+n7,2)*Q(n2+n8,2)-Q(n1,1)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n2+n8,2)
                + Q(n1+n3,2)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n1+n5+n6,3)*Q(n4+n7,2)*Q(n2+n8,2)
                + 2.*Q(n1,1)*Q(n3+n5+n6,3)*Q(n4+n7,2)*Q(n2+n8,2)-6.*Q(n1+n3+n5+n6,4)*Q(n4+n7,2)*Q(n2+n8,2)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n2+n8,2)+2.*Q(n3+n5,2)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n2+n8,2)
                + 2.*Q(n5,1)*Q(n3+n6,2)*Q(n1+n4+n7,3)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n5+n6,2)*Q(n1+n4+n7,3)*Q(n2+n8,2)
                - 4.*Q(n3+n5+n6,3)*Q(n1+n4+n7,3)*Q(n2+n8,2)-2.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n2+n8,2)
                + 2.*Q(n1+n5,2)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n2+n8,2)+2.*Q(n5,1)*Q(n1+n6,2)*Q(n3+n4+n7,3)*Q(n2+n8,2)
                + 2.*Q(n1,1)*Q(n5+n6,2)*Q(n3+n4+n7,3)*Q(n2+n8,2)-4.*Q(n1+n5+n6,3)*Q(n3+n4+n7,3)*Q(n2+n8,2)
                + 6.*Q(n5,1)*Q(n6,1)*Q(n1+n3+n4+n7,4)*Q(n2+n8,2)-6.*Q(n5+n6,2)*Q(n1+n3+n4+n7,4)*Q(n2+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n8,2)-Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n8,2)
                - Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n8,2)-Q(n1,1)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n8,2)
                + 2.*Q(n1+n3+n4,3)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n8,2)-Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n2+n8,2)
                + Q(n3+n4,2)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n2+n8,2)-Q(n1,1)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n2+n8,2)
                + Q(n1+n4,2)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n2+n8,2)+2.*Q(n4,1)*Q(n1+n3+n6,3)*Q(n5+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n2+n8,2)+Q(n1+n3,2)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n2+n8,2)
                + 2.*Q(n3,1)*Q(n1+n4+n6,3)*Q(n5+n7,2)*Q(n2+n8,2)+2.*Q(n1,1)*Q(n3+n4+n6,3)*Q(n5+n7,2)*Q(n2+n8,2)
                - 6.*Q(n1+n3+n4+n6,4)*Q(n5+n7,2)*Q(n2+n8,2)-2.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n2+n8,2)
                + 2.*Q(n3+n4,2)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n2+n8,2)+2.*Q(n4,1)*Q(n3+n6,2)*Q(n1+n5+n7,3)*Q(n2+n8,2)
                + 2.*Q(n3,1)*Q(n4+n6,2)*Q(n1+n5+n7,3)*Q(n2+n8,2)-4.*Q(n3+n4+n6,3)*Q(n1+n5+n7,3)*Q(n2+n8,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n2+n8,2)+2.*Q(n1+n4,2)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n2+n8,2)
                + 2.*Q(n4,1)*Q(n1+n6,2)*Q(n3+n5+n7,3)*Q(n2+n8,2)+2.*Q(n1,1)*Q(n4+n6,2)*Q(n3+n5+n7,3)*Q(n2+n8,2)
                - 4.*Q(n1+n4+n6,3)*Q(n3+n5+n7,3)*Q(n2+n8,2)+6.*Q(n4,1)*Q(n6,1)*Q(n1+n3+n5+n7,4)*Q(n2+n8,2)
                - 6.*Q(n4+n6,2)*Q(n1+n3+n5+n7,4)*Q(n2+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n2+n8,2)
                + 2.*Q(n1+n3,2)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n1+n6,2)*Q(n4+n5+n7,3)*Q(n2+n8,2)
                + 2.*Q(n1,1)*Q(n3+n6,2)*Q(n4+n5+n7,3)*Q(n2+n8,2)-4.*Q(n1+n3+n6,3)*Q(n4+n5+n7,3)*Q(n2+n8,2)
                + 6.*Q(n3,1)*Q(n6,1)*Q(n1+n4+n5+n7,4)*Q(n2+n8,2)-6.*Q(n3+n6,2)*Q(n1+n4+n5+n7,4)*Q(n2+n8,2)
                + 6.*Q(n1,1)*Q(n6,1)*Q(n3+n4+n5+n7,4)*Q(n2+n8,2)-6.*Q(n1+n6,2)*Q(n3+n4+n5+n7,4)*Q(n2+n8,2)
                - 24.*Q(n6,1)*Q(n1+n3+n4+n5+n7,5)*Q(n2+n8,2)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n8,2)
                - Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n8,2)-Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n8,2)+2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n8,2)
                - Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n2+n8,2)+Q(n3+n4,2)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n2+n8,2)
                - Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n2+n8,2)+Q(n1+n4,2)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n2+n8,2)
                + 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6+n7,2)*Q(n2+n8,2)-Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n2+n8,2)
                + Q(n1+n3,2)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6+n7,2)*Q(n2+n8,2)
                + 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n6+n7,2)*Q(n2+n8,2)-6.*Q(n1+n3+n4+n5,4)*Q(n6+n7,2)*Q(n2+n8,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n2+n8,2)+2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n2+n8,2)
                + 2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6+n7,3)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6+n7,3)*Q(n2+n8,2)
                - 4.*Q(n3+n4+n5,3)*Q(n1+n6+n7,3)*Q(n2+n8,2)-2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n2+n8,2)
                + 2.*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n2+n8,2)+2.*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6+n7,3)*Q(n2+n8,2)
                + 2.*Q(n1,1)*Q(n4+n5,2)*Q(n3+n6+n7,3)*Q(n2+n8,2)-4.*Q(n1+n4+n5,3)*Q(n3+n6+n7,3)*Q(n2+n8,2)
                + 6.*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6+n7,4)*Q(n2+n8,2)-6.*Q(n4+n5,2)*Q(n1+n3+n6+n7,4)*Q(n2+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n2+n8,2)+2.*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n2+n8,2)
                + 2.*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6+n7,3)*Q(n2+n8,2)+2.*Q(n1,1)*Q(n3+n5,2)*Q(n4+n6+n7,3)*Q(n2+n8,2)
                - 4.*Q(n1+n3+n5,3)*Q(n4+n6+n7,3)*Q(n2+n8,2)+6.*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6+n7,4)*Q(n2+n8,2)
                - 6.*Q(n3+n5,2)*Q(n1+n4+n6+n7,4)*Q(n2+n8,2)+6.*Q(n1,1)*Q(n5,1)*Q(n3+n4+n6+n7,4)*Q(n2+n8,2)
                - 6.*Q(n1+n5,2)*Q(n3+n4+n6+n7,4)*Q(n2+n8,2)-24.*Q(n5,1)*Q(n1+n3+n4+n6+n7,5)*Q(n2+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n2+n8,2)+2.*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n2+n8,2)
                + 2.*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6+n7,3)*Q(n2+n8,2)+2.*Q(n1,1)*Q(n3+n4,2)*Q(n5+n6+n7,3)*Q(n2+n8,2)
                - 4.*Q(n1+n3+n4,3)*Q(n5+n6+n7,3)*Q(n2+n8,2)+6.*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6+n7,4)*Q(n2+n8,2)
                - 6.*Q(n3+n4,2)*Q(n1+n5+n6+n7,4)*Q(n2+n8,2)+6.*Q(n1,1)*Q(n4,1)*Q(n3+n5+n6+n7,4)*Q(n2+n8,2)
                - 6.*Q(n1+n4,2)*Q(n3+n5+n6+n7,4)*Q(n2+n8,2)-24.*Q(n4,1)*Q(n1+n3+n5+n6+n7,5)*Q(n2+n8,2)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n4+n5+n6+n7,4)*Q(n2+n8,2)-6.*Q(n1+n3,2)*Q(n4+n5+n6+n7,4)*Q(n2+n8,2)
                - 24.*Q(n3,1)*Q(n1+n4+n5+n6+n7,5)*Q(n2+n8,2)-24.*Q(n1,1)*Q(n3+n4+n5+n6+n7,5)*Q(n2+n8,2)
                + 120.*Q(n1+n3+n4+n5+n6+n7,6)*Q(n2+n8,2)+2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n8,3)
                - 2.*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n8,3)-2.*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n8,3)
                - 2.*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n8,3)+4.*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n8,3)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n2+n8,3)+2.*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n2+n8,3)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n2+n8,3)+2.*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n2+n8,3)
                + 4.*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n1+n2+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n2+n8,3)
                + 2.*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n2+n8,3)+4.*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n1+n2+n8,3)
                + 4.*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n1+n2+n8,3)-12.*Q(n3+n4+n5+n6,4)*Q(n7,1)*Q(n1+n2+n8,3)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n2+n8,3)+2.*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n2+n8,3)
                + 2.*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n1+n2+n8,3)+2.*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n1+n2+n8,3)
                - 4.*Q(n4+n5+n6,3)*Q(n3+n7,2)*Q(n1+n2+n8,3)-2.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n2+n8,3)
                + 2.*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n2+n8,3)+2.*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n1+n2+n8,3)
                + 2.*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n1+n2+n8,3)-4.*Q(n3+n5+n6,3)*Q(n4+n7,2)*Q(n1+n2+n8,3)
                + 4.*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n1+n2+n8,3)-4.*Q(n5+n6,2)*Q(n3+n4+n7,3)*Q(n1+n2+n8,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n2+n8,3)+2.*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n2+n8,3)
                + 2.*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n1+n2+n8,3)+2.*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n1+n2+n8,3)
                - 4.*Q(n3+n4+n6,3)*Q(n5+n7,2)*Q(n1+n2+n8,3)+4.*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n1+n2+n8,3)
                - 4.*Q(n4+n6,2)*Q(n3+n5+n7,3)*Q(n1+n2+n8,3)+4.*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n1+n2+n8,3)
                - 4.*Q(n3+n6,2)*Q(n4+n5+n7,3)*Q(n1+n2+n8,3)-12.*Q(n6,1)*Q(n3+n4+n5+n7,4)*Q(n1+n2+n8,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n2+n8,3)+2.*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n2+n8,3)
                + 2.*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n1+n2+n8,3)+2.*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n1+n2+n8,3)
                - 4.*Q(n3+n4+n5,3)*Q(n6+n7,2)*Q(n1+n2+n8,3)+4.*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n1+n2+n8,3)
                - 4.*Q(n4+n5,2)*Q(n3+n6+n7,3)*Q(n1+n2+n8,3)+4.*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n1+n2+n8,3)
                - 4.*Q(n3+n5,2)*Q(n4+n6+n7,3)*Q(n1+n2+n8,3)-12.*Q(n5,1)*Q(n3+n4+n6+n7,4)*Q(n1+n2+n8,3)
                + 4.*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n1+n2+n8,3)-4.*Q(n3+n4,2)*Q(n5+n6+n7,3)*Q(n1+n2+n8,3)
                - 12.*Q(n4,1)*Q(n3+n5+n6+n7,4)*Q(n1+n2+n8,3)-12.*Q(n3,1)*Q(n4+n5+n6+n7,4)*Q(n1+n2+n8,3)
                + 48.*Q(n3+n4+n5+n6+n7,5)*Q(n1+n2+n8,3)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                + Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)+Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                + Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)-2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                + Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)-Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                + Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)-Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                - 2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)+Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                - Q(n1+n2,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)-2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                - 2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)+6.*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n7,1)*Q(n3+n8,2)
                + Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n8,2)
                - Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n2,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n8,2)+Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n8,2)
                - Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n8,2)
                - Q(n1,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n8,2)+2.*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n8,2)
                - 2.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n3+n8,2)+2.*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n3+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n1+n2,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n8,2)
                - Q(n2,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n1,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n8,2)-2.*Q(n2,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n3+n8,2)-2.*Q(n1,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n3+n8,2)+6.*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n7,1)*Q(n3+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n1+n2,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n8,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n8,2)-Q(n1,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n3+n8,2)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n3+n8,2)
                + 2.*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n3+n8,2)+6.*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n7,1)*Q(n3+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n3+n8,2)+2.*Q(n1+n2,2)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n3+n8,2)
                + 6.*Q(n2,1)*Q(n1+n4+n5+n6,4)*Q(n7,1)*Q(n3+n8,2)+6.*Q(n1,1)*Q(n2+n4+n5+n6,4)*Q(n7,1)*Q(n3+n8,2)
                - 24.*Q(n1+n2+n4+n5+n6,5)*Q(n7,1)*Q(n3+n8,2)+Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n8,2)
                - Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n8,2)-Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n8,2)
                - Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n8,2)+2.*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n8,2)
                - Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n3+n8,2)+Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n3+n8,2)
                - Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n3+n8,2)+Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n3+n8,2)
                + 2.*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n7,2)*Q(n3+n8,2)-Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n3+n8,2)
                + Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n3+n8,2)+2.*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n7,2)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n4+n5+n6,3)*Q(n1+n7,2)*Q(n3+n8,2)-6.*Q(n2+n4+n5+n6,4)*Q(n1+n7,2)*Q(n3+n8,2)
                + Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n8,2)-Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n8,2)
                - Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n8,2)
                + 2.*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n8,2)-Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n3+n8,2)
                + Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n3+n8,2)
                + Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n3+n8,2)+2.*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n7,2)*Q(n3+n8,2)
                - Q(n1,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n3+n8,2)+Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n3+n8,2)
                + 2.*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n7,2)*Q(n3+n8,2)+2.*Q(n1,1)*Q(n4+n5+n6,3)*Q(n2+n7,2)*Q(n3+n8,2)
                - 6.*Q(n1+n4+n5+n6,4)*Q(n2+n7,2)*Q(n3+n8,2)-2.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n3+n8,2)
                + 2.*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n3+n8,2)+2.*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n7,3)*Q(n3+n8,2)
                + 2.*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n7,3)*Q(n3+n8,2)-4.*Q(n4+n5+n6,3)*Q(n1+n2+n7,3)*Q(n3+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n8,2)-Q(n1+n2,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n8,2)
                - Q(n2,1)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n8,2)
                + 2.*Q(n1+n2+n5,3)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n8,2)-Q(n2,1)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n3+n8,2)
                + Q(n2+n5,2)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n3+n8,2)
                + Q(n1+n5,2)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n3+n8,2)+2.*Q(n5,1)*Q(n1+n2+n6,3)*Q(n4+n7,2)*Q(n3+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n3+n8,2)+Q(n1+n2,2)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n1+n5+n6,3)*Q(n4+n7,2)*Q(n3+n8,2)+2.*Q(n1,1)*Q(n2+n5+n6,3)*Q(n4+n7,2)*Q(n3+n8,2)
                - 6.*Q(n1+n2+n5+n6,4)*Q(n4+n7,2)*Q(n3+n8,2)-2.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n3+n8,2)
                + 2.*Q(n2+n5,2)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n3+n8,2)+2.*Q(n5,1)*Q(n2+n6,2)*Q(n1+n4+n7,3)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n5+n6,2)*Q(n1+n4+n7,3)*Q(n3+n8,2)-4.*Q(n2+n5+n6,3)*Q(n1+n4+n7,3)*Q(n3+n8,2)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n3+n8,2)+2.*Q(n1+n5,2)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n3+n8,2)
                + 2.*Q(n5,1)*Q(n1+n6,2)*Q(n2+n4+n7,3)*Q(n3+n8,2)+2.*Q(n1,1)*Q(n5+n6,2)*Q(n2+n4+n7,3)*Q(n3+n8,2)
                - 4.*Q(n1+n5+n6,3)*Q(n2+n4+n7,3)*Q(n3+n8,2)+6.*Q(n5,1)*Q(n6,1)*Q(n1+n2+n4+n7,4)*Q(n3+n8,2)
                - 6.*Q(n5+n6,2)*Q(n1+n2+n4+n7,4)*Q(n3+n8,2)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n8,2)
                - Q(n1+n2,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n8,2)-Q(n2,1)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n8,2)
                - Q(n1,1)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n8,2)+2.*Q(n1+n2+n4,3)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n8,2)
                - Q(n2,1)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n3+n8,2)+Q(n2+n4,2)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n3+n8,2)
                - Q(n1,1)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n3+n8,2)+Q(n1+n4,2)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n3+n8,2)
                + 2.*Q(n4,1)*Q(n1+n2+n6,3)*Q(n5+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n2,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n3+n8,2)
                + Q(n1+n2,2)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n3+n8,2)+2.*Q(n2,1)*Q(n1+n4+n6,3)*Q(n5+n7,2)*Q(n3+n8,2)
                + 2.*Q(n1,1)*Q(n2+n4+n6,3)*Q(n5+n7,2)*Q(n3+n8,2)-6.*Q(n1+n2+n4+n6,4)*Q(n5+n7,2)*Q(n3+n8,2)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n3+n8,2)+2.*Q(n2+n4,2)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n3+n8,2)
                + 2.*Q(n4,1)*Q(n2+n6,2)*Q(n1+n5+n7,3)*Q(n3+n8,2)+2.*Q(n2,1)*Q(n4+n6,2)*Q(n1+n5+n7,3)*Q(n3+n8,2)
                - 4.*Q(n2+n4+n6,3)*Q(n1+n5+n7,3)*Q(n3+n8,2)-2.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n3+n8,2)
                + 2.*Q(n1+n4,2)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n3+n8,2)+2.*Q(n4,1)*Q(n1+n6,2)*Q(n2+n5+n7,3)*Q(n3+n8,2)
                + 2.*Q(n1,1)*Q(n4+n6,2)*Q(n2+n5+n7,3)*Q(n3+n8,2)-4.*Q(n1+n4+n6,3)*Q(n2+n5+n7,3)*Q(n3+n8,2)
                + 6.*Q(n4,1)*Q(n6,1)*Q(n1+n2+n5+n7,4)*Q(n3+n8,2)-6.*Q(n4+n6,2)*Q(n1+n2+n5+n7,4)*Q(n3+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n3+n8,2)+2.*Q(n1+n2,2)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n1+n6,2)*Q(n4+n5+n7,3)*Q(n3+n8,2)+2.*Q(n1,1)*Q(n2+n6,2)*Q(n4+n5+n7,3)*Q(n3+n8,2)
                - 4.*Q(n1+n2+n6,3)*Q(n4+n5+n7,3)*Q(n3+n8,2)+6.*Q(n2,1)*Q(n6,1)*Q(n1+n4+n5+n7,4)*Q(n3+n8,2)
                - 6.*Q(n2+n6,2)*Q(n1+n4+n5+n7,4)*Q(n3+n8,2)+6.*Q(n1,1)*Q(n6,1)*Q(n2+n4+n5+n7,4)*Q(n3+n8,2)
                - 6.*Q(n1+n6,2)*Q(n2+n4+n5+n7,4)*Q(n3+n8,2)-24.*Q(n6,1)*Q(n1+n2+n4+n5+n7,5)*Q(n3+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n8,2)-Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n8,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n8,2)
                + 2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n8,2)-Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n3+n8,2)
                + Q(n2+n4,2)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n3+n8,2)-Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n3+n8,2)
                + Q(n1+n4,2)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n3+n8,2)+2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6+n7,2)*Q(n3+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n3+n8,2)+Q(n1+n2,2)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n6+n7,2)*Q(n3+n8,2)+2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n6+n7,2)*Q(n3+n8,2)
                - 6.*Q(n1+n2+n4+n5,4)*Q(n6+n7,2)*Q(n3+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n3+n8,2)+2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n6+n7,3)*Q(n3+n8,2)-4.*Q(n2+n4+n5,3)*Q(n1+n6+n7,3)*Q(n3+n8,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n3+n8,2)+2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6+n7,3)*Q(n3+n8,2)+2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n6+n7,3)*Q(n3+n8,2)
                - 4.*Q(n1+n4+n5,3)*Q(n2+n6+n7,3)*Q(n3+n8,2)+6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6+n7,4)*Q(n3+n8,2)
                - 6.*Q(n4+n5,2)*Q(n1+n2+n6+n7,4)*Q(n3+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n1+n2,2)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n3+n8,2)+2.*Q(n2,1)*Q(n1+n5,2)*Q(n4+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n1,1)*Q(n2+n5,2)*Q(n4+n6+n7,3)*Q(n3+n8,2)-4.*Q(n1+n2+n5,3)*Q(n4+n6+n7,3)*Q(n3+n8,2)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n1+n4+n6+n7,4)*Q(n3+n8,2)-6.*Q(n2+n5,2)*Q(n1+n4+n6+n7,4)*Q(n3+n8,2)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n2+n4+n6+n7,4)*Q(n3+n8,2)-6.*Q(n1+n5,2)*Q(n2+n4+n6+n7,4)*Q(n3+n8,2)
                - 24.*Q(n5,1)*Q(n1+n2+n4+n6+n7,5)*Q(n3+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n1+n2,2)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n3+n8,2)+2.*Q(n2,1)*Q(n1+n4,2)*Q(n5+n6+n7,3)*Q(n3+n8,2)
                + 2.*Q(n1,1)*Q(n2+n4,2)*Q(n5+n6+n7,3)*Q(n3+n8,2)-4.*Q(n1+n2+n4,3)*Q(n5+n6+n7,3)*Q(n3+n8,2)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n1+n5+n6+n7,4)*Q(n3+n8,2)-6.*Q(n2+n4,2)*Q(n1+n5+n6+n7,4)*Q(n3+n8,2)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n2+n5+n6+n7,4)*Q(n3+n8,2)-6.*Q(n1+n4,2)*Q(n2+n5+n6+n7,4)*Q(n3+n8,2)
                - 24.*Q(n4,1)*Q(n1+n2+n5+n6+n7,5)*Q(n3+n8,2)+6.*Q(n1,1)*Q(n2,1)*Q(n4+n5+n6+n7,4)*Q(n3+n8,2)
                - 6.*Q(n1+n2,2)*Q(n4+n5+n6+n7,4)*Q(n3+n8,2)-24.*Q(n2,1)*Q(n1+n4+n5+n6+n7,5)*Q(n3+n8,2)
                - 24.*Q(n1,1)*Q(n2+n4+n5+n6+n7,5)*Q(n3+n8,2)+120.*Q(n1+n2+n4+n5+n6+n7,6)*Q(n3+n8,2)
                + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n8,3)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n8,3)
                - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n8,3)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n8,3)
                + 4.*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n8,3)-2.*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n3+n8,3)
                + 2.*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n3+n8,3)-2.*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n3+n8,3)
                + 2.*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n3+n8,3)+4.*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n1+n3+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n3+n8,3)+2.*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n3+n8,3)
                + 4.*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n1+n3+n8,3)+4.*Q(n2,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n1+n3+n8,3)
                - 12.*Q(n2+n4+n5+n6,4)*Q(n7,1)*Q(n1+n3+n8,3)-2.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n3+n8,3)+2.*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n1+n3+n8,3)-4.*Q(n4+n5+n6,3)*Q(n2+n7,2)*Q(n1+n3+n8,3)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n3+n8,3)+2.*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n1+n3+n8,3)+2.*Q(n2,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n1+n3+n8,3)
                - 4.*Q(n2+n5+n6,3)*Q(n4+n7,2)*Q(n1+n3+n8,3)+4.*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n1+n3+n8,3)
                - 4.*Q(n5+n6,2)*Q(n2+n4+n7,3)*Q(n1+n3+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n3+n8,3)+2.*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n2,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n1+n3+n8,3)-4.*Q(n2+n4+n6,3)*Q(n5+n7,2)*Q(n1+n3+n8,3)
                + 4.*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n1+n3+n8,3)-4.*Q(n4+n6,2)*Q(n2+n5+n7,3)*Q(n1+n3+n8,3)
                + 4.*Q(n2,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n1+n3+n8,3)-4.*Q(n2+n6,2)*Q(n4+n5+n7,3)*Q(n1+n3+n8,3)
                - 12.*Q(n6,1)*Q(n2+n4+n5+n7,4)*Q(n1+n3+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n3+n8,3)+2.*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n1+n3+n8,3)
                + 2.*Q(n2,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n1+n3+n8,3)-4.*Q(n2+n4+n5,3)*Q(n6+n7,2)*Q(n1+n3+n8,3)
                + 4.*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n1+n3+n8,3)-4.*Q(n4+n5,2)*Q(n2+n6+n7,3)*Q(n1+n3+n8,3)
                + 4.*Q(n2,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n1+n3+n8,3)-4.*Q(n2+n5,2)*Q(n4+n6+n7,3)*Q(n1+n3+n8,3)
                - 12.*Q(n5,1)*Q(n2+n4+n6+n7,4)*Q(n1+n3+n8,3)+4.*Q(n2,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n1+n3+n8,3)
                - 4.*Q(n2+n4,2)*Q(n5+n6+n7,3)*Q(n1+n3+n8,3)-12.*Q(n4,1)*Q(n2+n5+n6+n7,4)*Q(n1+n3+n8,3)
                - 12.*Q(n2,1)*Q(n4+n5+n6+n7,4)*Q(n1+n3+n8,3)+48.*Q(n2+n4+n5+n6+n7,5)*Q(n1+n3+n8,3)
                + 2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n8,3)-2.*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n8,3)
                - 2.*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n8,3)-2.*Q(n1,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n8,3)
                + 4.*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n8,3)-2.*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n3+n8,3)
                + 2.*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n3+n8,3)-2.*Q(n1,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n3+n8,3)
                + 2.*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n3+n8,3)+4.*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n2+n3+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n3+n8,3)+2.*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n3+n8,3)
                + 4.*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n2+n3+n8,3)+4.*Q(n1,1)*Q(n4+n5+n6,3)*Q(n7,1)*Q(n2+n3+n8,3)
                - 12.*Q(n1+n4+n5+n6,4)*Q(n7,1)*Q(n2+n3+n8,3)-2.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n3+n8,3)+2.*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n2+n3+n8,3)-4.*Q(n4+n5+n6,3)*Q(n1+n7,2)*Q(n2+n3+n8,3)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n3+n8,3)+2.*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n2+n3+n8,3)+2.*Q(n1,1)*Q(n5+n6,2)*Q(n4+n7,2)*Q(n2+n3+n8,3)
                - 4.*Q(n1+n5+n6,3)*Q(n4+n7,2)*Q(n2+n3+n8,3)+4.*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n2+n3+n8,3)
                - 4.*Q(n5+n6,2)*Q(n1+n4+n7,3)*Q(n2+n3+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n3+n8,3)+2.*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n1,1)*Q(n4+n6,2)*Q(n5+n7,2)*Q(n2+n3+n8,3)-4.*Q(n1+n4+n6,3)*Q(n5+n7,2)*Q(n2+n3+n8,3)
                + 4.*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n2+n3+n8,3)-4.*Q(n4+n6,2)*Q(n1+n5+n7,3)*Q(n2+n3+n8,3)
                + 4.*Q(n1,1)*Q(n6,1)*Q(n4+n5+n7,3)*Q(n2+n3+n8,3)-4.*Q(n1+n6,2)*Q(n4+n5+n7,3)*Q(n2+n3+n8,3)
                - 12.*Q(n6,1)*Q(n1+n4+n5+n7,4)*Q(n2+n3+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n3+n8,3)+2.*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n2+n3+n8,3)
                + 2.*Q(n1,1)*Q(n4+n5,2)*Q(n6+n7,2)*Q(n2+n3+n8,3)-4.*Q(n1+n4+n5,3)*Q(n6+n7,2)*Q(n2+n3+n8,3)
                + 4.*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n2+n3+n8,3)-4.*Q(n4+n5,2)*Q(n1+n6+n7,3)*Q(n2+n3+n8,3)
                + 4.*Q(n1,1)*Q(n5,1)*Q(n4+n6+n7,3)*Q(n2+n3+n8,3)-4.*Q(n1+n5,2)*Q(n4+n6+n7,3)*Q(n2+n3+n8,3)
                - 12.*Q(n5,1)*Q(n1+n4+n6+n7,4)*Q(n2+n3+n8,3)+4.*Q(n1,1)*Q(n4,1)*Q(n5+n6+n7,3)*Q(n2+n3+n8,3)
                - 4.*Q(n1+n4,2)*Q(n5+n6+n7,3)*Q(n2+n3+n8,3)-12.*Q(n4,1)*Q(n1+n5+n6+n7,4)*Q(n2+n3+n8,3)
                - 12.*Q(n1,1)*Q(n4+n5+n6+n7,4)*Q(n2+n3+n8,3)+48.*Q(n1+n4+n5+n6+n7,5)*Q(n2+n3+n8,3)
                - 6.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n3+n8,4)+6.*Q(n4+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n3+n8,4)
                + 6.*Q(n5,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n2+n3+n8,4)+6.*Q(n4,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n2+n3+n8,4)
                - 12.*Q(n4+n5+n6,3)*Q(n7,1)*Q(n1+n2+n3+n8,4)+6.*Q(n5,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n2+n3+n8,4)
                - 6.*Q(n5+n6,2)*Q(n4+n7,2)*Q(n1+n2+n3+n8,4)+6.*Q(n4,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n2+n3+n8,4)
                - 6.*Q(n4+n6,2)*Q(n5+n7,2)*Q(n1+n2+n3+n8,4)-12.*Q(n6,1)*Q(n4+n5+n7,3)*Q(n1+n2+n3+n8,4)
                + 6.*Q(n4,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n2+n3+n8,4)-6.*Q(n4+n5,2)*Q(n6+n7,2)*Q(n1+n2+n3+n8,4)
                - 12.*Q(n5,1)*Q(n4+n6+n7,3)*Q(n1+n2+n3+n8,4)-12.*Q(n4,1)*Q(n5+n6+n7,3)*Q(n1+n2+n3+n8,4)
                + 36.*Q(n4+n5+n6+n7,4)*Q(n1+n2+n3+n8,4)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                + Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)+Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                + Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)-2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)-Q(n2+n3,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)-Q(n1+n3,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                - 2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                - Q(n1+n2,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)-2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                - 2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)+6.*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n7,1)*Q(n4+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n2+n3,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n8,2)
                - Q(n3,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n2,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n8,2)+Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n8,2)
                - Q(n1+n3,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n3,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n8,2)
                - Q(n1,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n8,2)+2.*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n8,2)
                - 2.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n4+n8,2)+2.*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n4+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n1+n2,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n8,2)
                - Q(n2,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n1,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n8,2)-2.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n4+n8,2)-2.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n4+n8,2)+6.*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n7,1)*Q(n4+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n5+n6,2)*Q(n7,1)*Q(n4+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n5+n6,2)*Q(n7,1)*Q(n4+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n5+n6,2)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n5+n6,2)*Q(n7,1)*Q(n4+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n2+n3,2)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n4+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n4+n8,2)
                + 2.*Q(n1+n3,2)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n4+n8,2)+6.*Q(n3,1)*Q(n1+n2+n5+n6,4)*Q(n7,1)*Q(n4+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n4+n8,2)+2.*Q(n1+n2,2)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n4+n8,2)
                + 6.*Q(n2,1)*Q(n1+n3+n5+n6,4)*Q(n7,1)*Q(n4+n8,2)+6.*Q(n1,1)*Q(n2+n3+n5+n6,4)*Q(n7,1)*Q(n4+n8,2)
                - 24.*Q(n1+n2+n3+n5+n6,5)*Q(n7,1)*Q(n4+n8,2)+Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n8,2)
                - Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n8,2)-Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n8,2)
                - Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n8,2)+2.*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n8,2)
                - Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n4+n8,2)+Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n4+n8,2)
                - Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n4+n8,2)+Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n4+n8,2)
                + 2.*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n7,2)*Q(n4+n8,2)-Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n4+n8,2)
                + Q(n2+n3,2)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n4+n8,2)+2.*Q(n3,1)*Q(n2+n5+n6,3)*Q(n1+n7,2)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n3+n5+n6,3)*Q(n1+n7,2)*Q(n4+n8,2)-6.*Q(n2+n3+n5+n6,4)*Q(n1+n7,2)*Q(n4+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n8,2)-Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n8,2)
                - Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n8,2)
                + 2.*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n8,2)-Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n4+n8,2)
                + Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n4+n8,2)
                + Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n4+n8,2)+2.*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n7,2)*Q(n4+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n4+n8,2)+Q(n1+n3,2)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n4+n8,2)
                + 2.*Q(n3,1)*Q(n1+n5+n6,3)*Q(n2+n7,2)*Q(n4+n8,2)+2.*Q(n1,1)*Q(n3+n5+n6,3)*Q(n2+n7,2)*Q(n4+n8,2)
                - 6.*Q(n1+n3+n5+n6,4)*Q(n2+n7,2)*Q(n4+n8,2)-2.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n4+n8,2)
                + 2.*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n4+n8,2)+2.*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n7,3)*Q(n4+n8,2)
                + 2.*Q(n3,1)*Q(n5+n6,2)*Q(n1+n2+n7,3)*Q(n4+n8,2)-4.*Q(n3+n5+n6,3)*Q(n1+n2+n7,3)*Q(n4+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n8,2)-Q(n1+n2,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n8,2)
                - Q(n2,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n8,2)
                + 2.*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n8,2)-Q(n2,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n4+n8,2)
                + Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n4+n8,2)
                + Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n4+n8,2)+2.*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n7,2)*Q(n4+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n4+n8,2)+Q(n1+n2,2)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n1+n5+n6,3)*Q(n3+n7,2)*Q(n4+n8,2)+2.*Q(n1,1)*Q(n2+n5+n6,3)*Q(n3+n7,2)*Q(n4+n8,2)
                - 6.*Q(n1+n2+n5+n6,4)*Q(n3+n7,2)*Q(n4+n8,2)-2.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n4+n8,2)
                + 2.*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n4+n8,2)+2.*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n7,3)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n5+n6,2)*Q(n1+n3+n7,3)*Q(n4+n8,2)-4.*Q(n2+n5+n6,3)*Q(n1+n3+n7,3)*Q(n4+n8,2)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n4+n8,2)+2.*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n4+n8,2)
                + 2.*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n7,3)*Q(n4+n8,2)+2.*Q(n1,1)*Q(n5+n6,2)*Q(n2+n3+n7,3)*Q(n4+n8,2)
                - 4.*Q(n1+n5+n6,3)*Q(n2+n3+n7,3)*Q(n4+n8,2)+6.*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n7,4)*Q(n4+n8,2)
                - 6.*Q(n5+n6,2)*Q(n1+n2+n3+n7,4)*Q(n4+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n5+n7,2)*Q(n4+n8,2)
                - Q(n1+n2,2)*Q(n3,1)*Q(n6,1)*Q(n5+n7,2)*Q(n4+n8,2)-Q(n2,1)*Q(n1+n3,2)*Q(n6,1)*Q(n5+n7,2)*Q(n4+n8,2)
                - Q(n1,1)*Q(n2+n3,2)*Q(n6,1)*Q(n5+n7,2)*Q(n4+n8,2)+2.*Q(n1+n2+n3,3)*Q(n6,1)*Q(n5+n7,2)*Q(n4+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n4+n8,2)+Q(n2+n3,2)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n4+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n4+n8,2)+Q(n1+n3,2)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n4+n8,2)
                + 2.*Q(n3,1)*Q(n1+n2+n6,3)*Q(n5+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n2,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n4+n8,2)
                + Q(n1+n2,2)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n4+n8,2)+2.*Q(n2,1)*Q(n1+n3+n6,3)*Q(n5+n7,2)*Q(n4+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3+n6,3)*Q(n5+n7,2)*Q(n4+n8,2)-6.*Q(n1+n2+n3+n6,4)*Q(n5+n7,2)*Q(n4+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n4+n8,2)+2.*Q(n2+n3,2)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n4+n8,2)
                + 2.*Q(n3,1)*Q(n2+n6,2)*Q(n1+n5+n7,3)*Q(n4+n8,2)+2.*Q(n2,1)*Q(n3+n6,2)*Q(n1+n5+n7,3)*Q(n4+n8,2)
                - 4.*Q(n2+n3+n6,3)*Q(n1+n5+n7,3)*Q(n4+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n4+n8,2)
                + 2.*Q(n1+n3,2)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n4+n8,2)+2.*Q(n3,1)*Q(n1+n6,2)*Q(n2+n5+n7,3)*Q(n4+n8,2)
                + 2.*Q(n1,1)*Q(n3+n6,2)*Q(n2+n5+n7,3)*Q(n4+n8,2)-4.*Q(n1+n3+n6,3)*Q(n2+n5+n7,3)*Q(n4+n8,2)
                + 6.*Q(n3,1)*Q(n6,1)*Q(n1+n2+n5+n7,4)*Q(n4+n8,2)-6.*Q(n3+n6,2)*Q(n1+n2+n5+n7,4)*Q(n4+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n4+n8,2)+2.*Q(n1+n2,2)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n1+n6,2)*Q(n3+n5+n7,3)*Q(n4+n8,2)+2.*Q(n1,1)*Q(n2+n6,2)*Q(n3+n5+n7,3)*Q(n4+n8,2)
                - 4.*Q(n1+n2+n6,3)*Q(n3+n5+n7,3)*Q(n4+n8,2)+6.*Q(n2,1)*Q(n6,1)*Q(n1+n3+n5+n7,4)*Q(n4+n8,2)
                - 6.*Q(n2+n6,2)*Q(n1+n3+n5+n7,4)*Q(n4+n8,2)+6.*Q(n1,1)*Q(n6,1)*Q(n2+n3+n5+n7,4)*Q(n4+n8,2)
                - 6.*Q(n1+n6,2)*Q(n2+n3+n5+n7,4)*Q(n4+n8,2)-24.*Q(n6,1)*Q(n1+n2+n3+n5+n7,5)*Q(n4+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6+n7,2)*Q(n4+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n6+n7,2)*Q(n4+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n6+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n6+n7,2)*Q(n4+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n6+n7,2)*Q(n4+n8,2)-Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n4+n8,2)
                + Q(n2+n3,2)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n4+n8,2)-Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n4+n8,2)
                + Q(n1+n3,2)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n4+n8,2)+2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n6+n7,2)*Q(n4+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n4+n8,2)+Q(n1+n2,2)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n6+n7,2)*Q(n4+n8,2)+2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n6+n7,2)*Q(n4+n8,2)
                - 6.*Q(n1+n2+n3+n5,4)*Q(n6+n7,2)*Q(n4+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n4+n8,2)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n6+n7,3)*Q(n4+n8,2)-4.*Q(n2+n3+n5,3)*Q(n1+n6+n7,3)*Q(n4+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n4+n8,2)+2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n6+n7,3)*Q(n4+n8,2)+2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n6+n7,3)*Q(n4+n8,2)
                - 4.*Q(n1+n3+n5,3)*Q(n2+n6+n7,3)*Q(n4+n8,2)+6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n6+n7,4)*Q(n4+n8,2)
                - 6.*Q(n3+n5,2)*Q(n1+n2+n6+n7,4)*Q(n4+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n4+n8,2)+2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n6+n7,3)*Q(n4+n8,2)-4.*Q(n1+n2+n5,3)*Q(n3+n6+n7,3)*Q(n4+n8,2)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n6+n7,4)*Q(n4+n8,2)-6.*Q(n2+n5,2)*Q(n1+n3+n6+n7,4)*Q(n4+n8,2)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n6+n7,4)*Q(n4+n8,2)-6.*Q(n1+n5,2)*Q(n2+n3+n6+n7,4)*Q(n4+n8,2)
                - 24.*Q(n5,1)*Q(n1+n2+n3+n6+n7,5)*Q(n4+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n5+n6+n7,3)*Q(n4+n8,2)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n5+n6+n7,3)*Q(n4+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n5+n6+n7,3)*Q(n4+n8,2)-4.*Q(n1+n2+n3,3)*Q(n5+n6+n7,3)*Q(n4+n8,2)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n1+n5+n6+n7,4)*Q(n4+n8,2)-6.*Q(n2+n3,2)*Q(n1+n5+n6+n7,4)*Q(n4+n8,2)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n2+n5+n6+n7,4)*Q(n4+n8,2)-6.*Q(n1+n3,2)*Q(n2+n5+n6+n7,4)*Q(n4+n8,2)
                - 24.*Q(n3,1)*Q(n1+n2+n5+n6+n7,5)*Q(n4+n8,2)+6.*Q(n1,1)*Q(n2,1)*Q(n3+n5+n6+n7,4)*Q(n4+n8,2)
                - 6.*Q(n1+n2,2)*Q(n3+n5+n6+n7,4)*Q(n4+n8,2)-24.*Q(n2,1)*Q(n1+n3+n5+n6+n7,5)*Q(n4+n8,2)
                - 24.*Q(n1,1)*Q(n2+n3+n5+n6+n7,5)*Q(n4+n8,2)+120.*Q(n1+n2+n3+n5+n6+n7,6)*Q(n4+n8,2)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n8,3)-2.*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n8,3)
                - 2.*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n8,3)-2.*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n8,3)
                + 4.*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n8,3)-2.*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n4+n8,3)
                + 2.*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n4+n8,3)-2.*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n4+n8,3)
                + 2.*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n4+n8,3)+4.*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n1+n4+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n4+n8,3)+2.*Q(n2+n3,2)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n4+n8,3)
                + 4.*Q(n3,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n1+n4+n8,3)+4.*Q(n2,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n1+n4+n8,3)
                - 12.*Q(n2+n3+n5+n6,4)*Q(n7,1)*Q(n1+n4+n8,3)-2.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n4+n8,3)+2.*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n3,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n1+n4+n8,3)-4.*Q(n3+n5+n6,3)*Q(n2+n7,2)*Q(n1+n4+n8,3)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n4+n8,3)+2.*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n1+n4+n8,3)+2.*Q(n2,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n1+n4+n8,3)
                - 4.*Q(n2+n5+n6,3)*Q(n3+n7,2)*Q(n1+n4+n8,3)+4.*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n1+n4+n8,3)
                - 4.*Q(n5+n6,2)*Q(n2+n3+n7,3)*Q(n1+n4+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n2+n3,2)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n4+n8,3)+2.*Q(n3,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n2,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n1+n4+n8,3)-4.*Q(n2+n3+n6,3)*Q(n5+n7,2)*Q(n1+n4+n8,3)
                + 4.*Q(n3,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n1+n4+n8,3)-4.*Q(n3+n6,2)*Q(n2+n5+n7,3)*Q(n1+n4+n8,3)
                + 4.*Q(n2,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n1+n4+n8,3)-4.*Q(n2+n6,2)*Q(n3+n5+n7,3)*Q(n1+n4+n8,3)
                - 12.*Q(n6,1)*Q(n2+n3+n5+n7,4)*Q(n1+n4+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n4+n8,3)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n1+n4+n8,3)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n1+n4+n8,3)-4.*Q(n2+n3+n5,3)*Q(n6+n7,2)*Q(n1+n4+n8,3)
                + 4.*Q(n3,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n1+n4+n8,3)-4.*Q(n3+n5,2)*Q(n2+n6+n7,3)*Q(n1+n4+n8,3)
                + 4.*Q(n2,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n1+n4+n8,3)-4.*Q(n2+n5,2)*Q(n3+n6+n7,3)*Q(n1+n4+n8,3)
                - 12.*Q(n5,1)*Q(n2+n3+n6+n7,4)*Q(n1+n4+n8,3)+4.*Q(n2,1)*Q(n3,1)*Q(n5+n6+n7,3)*Q(n1+n4+n8,3)
                - 4.*Q(n2+n3,2)*Q(n5+n6+n7,3)*Q(n1+n4+n8,3)-12.*Q(n3,1)*Q(n2+n5+n6+n7,4)*Q(n1+n4+n8,3)
                - 12.*Q(n2,1)*Q(n3+n5+n6+n7,4)*Q(n1+n4+n8,3)+48.*Q(n2+n3+n5+n6+n7,5)*Q(n1+n4+n8,3)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n8,3)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n8,3)
                - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n8,3)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n8,3)
                + 4.*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n8,3)-2.*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n4+n8,3)
                + 2.*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n4+n8,3)-2.*Q(n1,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n4+n8,3)
                + 2.*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n4+n8,3)+4.*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n2+n4+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n4+n8,3)+2.*Q(n1+n3,2)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n4+n8,3)
                + 4.*Q(n3,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n2+n4+n8,3)+4.*Q(n1,1)*Q(n3+n5+n6,3)*Q(n7,1)*Q(n2+n4+n8,3)
                - 12.*Q(n1+n3+n5+n6,4)*Q(n7,1)*Q(n2+n4+n8,3)-2.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n4+n8,3)+2.*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n3,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n2+n4+n8,3)-4.*Q(n3+n5+n6,3)*Q(n1+n7,2)*Q(n2+n4+n8,3)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n4+n8,3)+2.*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n2+n4+n8,3)+2.*Q(n1,1)*Q(n5+n6,2)*Q(n3+n7,2)*Q(n2+n4+n8,3)
                - 4.*Q(n1+n5+n6,3)*Q(n3+n7,2)*Q(n2+n4+n8,3)+4.*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n2+n4+n8,3)
                - 4.*Q(n5+n6,2)*Q(n1+n3+n7,3)*Q(n2+n4+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n1+n3,2)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n4+n8,3)+2.*Q(n3,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n1,1)*Q(n3+n6,2)*Q(n5+n7,2)*Q(n2+n4+n8,3)-4.*Q(n1+n3+n6,3)*Q(n5+n7,2)*Q(n2+n4+n8,3)
                + 4.*Q(n3,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n2+n4+n8,3)-4.*Q(n3+n6,2)*Q(n1+n5+n7,3)*Q(n2+n4+n8,3)
                + 4.*Q(n1,1)*Q(n6,1)*Q(n3+n5+n7,3)*Q(n2+n4+n8,3)-4.*Q(n1+n6,2)*Q(n3+n5+n7,3)*Q(n2+n4+n8,3)
                - 12.*Q(n6,1)*Q(n1+n3+n5+n7,4)*Q(n2+n4+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n1+n3,2)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n4+n8,3)+2.*Q(n3,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n2+n4+n8,3)
                + 2.*Q(n1,1)*Q(n3+n5,2)*Q(n6+n7,2)*Q(n2+n4+n8,3)-4.*Q(n1+n3+n5,3)*Q(n6+n7,2)*Q(n2+n4+n8,3)
                + 4.*Q(n3,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n2+n4+n8,3)-4.*Q(n3+n5,2)*Q(n1+n6+n7,3)*Q(n2+n4+n8,3)
                + 4.*Q(n1,1)*Q(n5,1)*Q(n3+n6+n7,3)*Q(n2+n4+n8,3)-4.*Q(n1+n5,2)*Q(n3+n6+n7,3)*Q(n2+n4+n8,3)
                - 12.*Q(n5,1)*Q(n1+n3+n6+n7,4)*Q(n2+n4+n8,3)+4.*Q(n1,1)*Q(n3,1)*Q(n5+n6+n7,3)*Q(n2+n4+n8,3)
                - 4.*Q(n1+n3,2)*Q(n5+n6+n7,3)*Q(n2+n4+n8,3)-12.*Q(n3,1)*Q(n1+n5+n6+n7,4)*Q(n2+n4+n8,3)
                - 12.*Q(n1,1)*Q(n3+n5+n6+n7,4)*Q(n2+n4+n8,3)+48.*Q(n1+n3+n5+n6+n7,5)*Q(n2+n4+n8,3)
                - 6.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n4+n8,4)+6.*Q(n3+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n4+n8,4)
                + 6.*Q(n5,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n2+n4+n8,4)+6.*Q(n3,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n2+n4+n8,4)
                - 12.*Q(n3+n5+n6,3)*Q(n7,1)*Q(n1+n2+n4+n8,4)+6.*Q(n5,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n2+n4+n8,4)
                - 6.*Q(n5+n6,2)*Q(n3+n7,2)*Q(n1+n2+n4+n8,4)+6.*Q(n3,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n2+n4+n8,4)
                - 6.*Q(n3+n6,2)*Q(n5+n7,2)*Q(n1+n2+n4+n8,4)-12.*Q(n6,1)*Q(n3+n5+n7,3)*Q(n1+n2+n4+n8,4)
                + 6.*Q(n3,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n2+n4+n8,4)-6.*Q(n3+n5,2)*Q(n6+n7,2)*Q(n1+n2+n4+n8,4)
                - 12.*Q(n5,1)*Q(n3+n6+n7,3)*Q(n1+n2+n4+n8,4)-12.*Q(n3,1)*Q(n5+n6+n7,3)*Q(n1+n2+n4+n8,4)
                + 36.*Q(n3+n5+n6+n7,4)*Q(n1+n2+n4+n8,4)+2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n8,3)
                - 2.*Q(n1+n2,2)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n8,3)-2.*Q(n2,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n8,3)
                - 2.*Q(n1,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n8,3)+4.*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n8,3)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n4+n8,3)+2.*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n4+n8,3)
                - 2.*Q(n1,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n4+n8,3)+2.*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n4+n8,3)
                + 4.*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n3+n4+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n4+n8,3)
                + 2.*Q(n1+n2,2)*Q(n5+n6,2)*Q(n7,1)*Q(n3+n4+n8,3)+4.*Q(n2,1)*Q(n1+n5+n6,3)*Q(n7,1)*Q(n3+n4+n8,3)
                + 4.*Q(n1,1)*Q(n2+n5+n6,3)*Q(n7,1)*Q(n3+n4+n8,3)-12.*Q(n1+n2+n5+n6,4)*Q(n7,1)*Q(n3+n4+n8,3)
                - 2.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n4+n8,3)+2.*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n4+n8,3)
                + 2.*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n3+n4+n8,3)+2.*Q(n2,1)*Q(n5+n6,2)*Q(n1+n7,2)*Q(n3+n4+n8,3)
                - 4.*Q(n2+n5+n6,3)*Q(n1+n7,2)*Q(n3+n4+n8,3)-2.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n4+n8,3);

 return eight;

} // TComplex Eight_2(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)

//==========================================================================================================================

TComplex Eight_3(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)
{
 // Generic eight-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)]>, third part.

 TComplex eight = 2.*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n4+n8,3)+2.*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n3+n4+n8,3)
                + 2.*Q(n1,1)*Q(n5+n6,2)*Q(n2+n7,2)*Q(n3+n4+n8,3)-4.*Q(n1+n5+n6,3)*Q(n2+n7,2)*Q(n3+n4+n8,3)
                + 4.*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n3+n4+n8,3)-4.*Q(n5+n6,2)*Q(n1+n2+n7,3)*Q(n3+n4+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n4+n8,3)+2.*Q(n1+n2,2)*Q(n6,1)*Q(n5+n7,2)*Q(n3+n4+n8,3)
                + 2.*Q(n2,1)*Q(n1+n6,2)*Q(n5+n7,2)*Q(n3+n4+n8,3)+2.*Q(n1,1)*Q(n2+n6,2)*Q(n5+n7,2)*Q(n3+n4+n8,3)
                - 4.*Q(n1+n2+n6,3)*Q(n5+n7,2)*Q(n3+n4+n8,3)+4.*Q(n2,1)*Q(n6,1)*Q(n1+n5+n7,3)*Q(n3+n4+n8,3)
                - 4.*Q(n2+n6,2)*Q(n1+n5+n7,3)*Q(n3+n4+n8,3)+4.*Q(n1,1)*Q(n6,1)*Q(n2+n5+n7,3)*Q(n3+n4+n8,3)
                - 4.*Q(n1+n6,2)*Q(n2+n5+n7,3)*Q(n3+n4+n8,3)-12.*Q(n6,1)*Q(n1+n2+n5+n7,4)*Q(n3+n4+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n4+n8,3)+2.*Q(n1+n2,2)*Q(n5,1)*Q(n6+n7,2)*Q(n3+n4+n8,3)
                + 2.*Q(n2,1)*Q(n1+n5,2)*Q(n6+n7,2)*Q(n3+n4+n8,3)+2.*Q(n1,1)*Q(n2+n5,2)*Q(n6+n7,2)*Q(n3+n4+n8,3)
                - 4.*Q(n1+n2+n5,3)*Q(n6+n7,2)*Q(n3+n4+n8,3)+4.*Q(n2,1)*Q(n5,1)*Q(n1+n6+n7,3)*Q(n3+n4+n8,3)
                - 4.*Q(n2+n5,2)*Q(n1+n6+n7,3)*Q(n3+n4+n8,3)+4.*Q(n1,1)*Q(n5,1)*Q(n2+n6+n7,3)*Q(n3+n4+n8,3)
                - 4.*Q(n1+n5,2)*Q(n2+n6+n7,3)*Q(n3+n4+n8,3)-12.*Q(n5,1)*Q(n1+n2+n6+n7,4)*Q(n3+n4+n8,3)
                + 4.*Q(n1,1)*Q(n2,1)*Q(n5+n6+n7,3)*Q(n3+n4+n8,3)-4.*Q(n1+n2,2)*Q(n5+n6+n7,3)*Q(n3+n4+n8,3)
                - 12.*Q(n2,1)*Q(n1+n5+n6+n7,4)*Q(n3+n4+n8,3)-12.*Q(n1,1)*Q(n2+n5+n6+n7,4)*Q(n3+n4+n8,3)
                + 48.*Q(n1+n2+n5+n6+n7,5)*Q(n3+n4+n8,3)-6.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n4+n8,4)
                + 6.*Q(n2+n5,2)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n4+n8,4)+6.*Q(n5,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n3+n4+n8,4)
                + 6.*Q(n2,1)*Q(n5+n6,2)*Q(n7,1)*Q(n1+n3+n4+n8,4)-12.*Q(n2+n5+n6,3)*Q(n7,1)*Q(n1+n3+n4+n8,4)
                + 6.*Q(n5,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n3+n4+n8,4)-6.*Q(n5+n6,2)*Q(n2+n7,2)*Q(n1+n3+n4+n8,4)
                + 6.*Q(n2,1)*Q(n6,1)*Q(n5+n7,2)*Q(n1+n3+n4+n8,4)-6.*Q(n2+n6,2)*Q(n5+n7,2)*Q(n1+n3+n4+n8,4)
                - 12.*Q(n6,1)*Q(n2+n5+n7,3)*Q(n1+n3+n4+n8,4)+6.*Q(n2,1)*Q(n5,1)*Q(n6+n7,2)*Q(n1+n3+n4+n8,4)
                - 6.*Q(n2+n5,2)*Q(n6+n7,2)*Q(n1+n3+n4+n8,4)-12.*Q(n5,1)*Q(n2+n6+n7,3)*Q(n1+n3+n4+n8,4)
                - 12.*Q(n2,1)*Q(n5+n6+n7,3)*Q(n1+n3+n4+n8,4)+36.*Q(n2+n5+n6+n7,4)*Q(n1+n3+n4+n8,4)
                - 6.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n4+n8,4)+6.*Q(n1+n5,2)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n4+n8,4)
                + 6.*Q(n5,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n3+n4+n8,4)+6.*Q(n1,1)*Q(n5+n6,2)*Q(n7,1)*Q(n2+n3+n4+n8,4)
                - 12.*Q(n1+n5+n6,3)*Q(n7,1)*Q(n2+n3+n4+n8,4)+6.*Q(n5,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n3+n4+n8,4)
                - 6.*Q(n5+n6,2)*Q(n1+n7,2)*Q(n2+n3+n4+n8,4)+6.*Q(n1,1)*Q(n6,1)*Q(n5+n7,2)*Q(n2+n3+n4+n8,4)
                - 6.*Q(n1+n6,2)*Q(n5+n7,2)*Q(n2+n3+n4+n8,4)-12.*Q(n6,1)*Q(n1+n5+n7,3)*Q(n2+n3+n4+n8,4)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n6+n7,2)*Q(n2+n3+n4+n8,4)-6.*Q(n1+n5,2)*Q(n6+n7,2)*Q(n2+n3+n4+n8,4)
                - 12.*Q(n5,1)*Q(n1+n6+n7,3)*Q(n2+n3+n4+n8,4)-12.*Q(n1,1)*Q(n5+n6+n7,3)*Q(n2+n3+n4+n8,4)
                + 36.*Q(n1+n5+n6+n7,4)*Q(n2+n3+n4+n8,4)+24.*Q(n5,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n3+n4+n8,5)
                - 24.*Q(n5+n6,2)*Q(n7,1)*Q(n1+n2+n3+n4+n8,5)-24.*Q(n6,1)*Q(n5+n7,2)*Q(n1+n2+n3+n4+n8,5)
                - 24.*Q(n5,1)*Q(n6+n7,2)*Q(n1+n2+n3+n4+n8,5)+48.*Q(n5+n6+n7,3)*Q(n1+n2+n3+n4+n8,5)
                - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)+Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                + Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)+Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                - 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)+Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                - Q(n2+n3,2)*Q(n1+n4,2)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)+Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                - Q(n1+n3,2)*Q(n2+n4,2)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)-2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)-Q(n1+n2,2)*Q(n3+n4,2)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                - 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)-2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)
                + 6.*Q(n1+n2+n3+n4,4)*Q(n6,1)*Q(n7,1)*Q(n5+n8,2)+Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n2+n3,2)*Q(n4,1)*Q(n1+n6,2)*Q(n7,1)*Q(n5+n8,2)-Q(n3,1)*Q(n2+n4,2)*Q(n1+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n2,1)*Q(n3+n4,2)*Q(n1+n6,2)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n2+n3+n4,3)*Q(n1+n6,2)*Q(n7,1)*Q(n5+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n7,1)*Q(n5+n8,2)-Q(n1+n3,2)*Q(n4,1)*Q(n2+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n3,1)*Q(n1+n4,2)*Q(n2+n6,2)*Q(n7,1)*Q(n5+n8,2)-Q(n1,1)*Q(n3+n4,2)*Q(n2+n6,2)*Q(n7,1)*Q(n5+n8,2)
                + 2.*Q(n1+n3+n4,3)*Q(n2+n6,2)*Q(n7,1)*Q(n5+n8,2)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n5+n8,2)
                + 2.*Q(n3+n4,2)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n5+n8,2)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n1+n2,2)*Q(n4,1)*Q(n3+n6,2)*Q(n7,1)*Q(n5+n8,2)-Q(n2,1)*Q(n1+n4,2)*Q(n3+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n1,1)*Q(n2+n4,2)*Q(n3+n6,2)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n1+n2+n4,3)*Q(n3+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n2+n4,2)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n5+n8,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n1+n4,2)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n5+n8,2)
                + 6.*Q(n4,1)*Q(n1+n2+n3+n6,4)*Q(n7,1)*Q(n5+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n1+n2,2)*Q(n3,1)*Q(n4+n6,2)*Q(n7,1)*Q(n5+n8,2)-Q(n2,1)*Q(n1+n3,2)*Q(n4+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - Q(n1,1)*Q(n2+n3,2)*Q(n4+n6,2)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n1+n2+n3,3)*Q(n4+n6,2)*Q(n7,1)*Q(n5+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n2+n3,2)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n5+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n5+n8,2)+2.*Q(n1+n3,2)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n5+n8,2)
                + 6.*Q(n3,1)*Q(n1+n2+n4+n6,4)*Q(n7,1)*Q(n5+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n5+n8,2)
                + 2.*Q(n1+n2,2)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n5+n8,2)+6.*Q(n2,1)*Q(n1+n3+n4+n6,4)*Q(n7,1)*Q(n5+n8,2)
                + 6.*Q(n1,1)*Q(n2+n3+n4+n6,4)*Q(n7,1)*Q(n5+n8,2)-24.*Q(n1+n2+n3+n4+n6,5)*Q(n7,1)*Q(n5+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n7,2)*Q(n5+n8,2)-Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n1+n7,2)*Q(n5+n8,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n1+n7,2)*Q(n5+n8,2)-Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n1+n7,2)*Q(n5+n8,2)
                + 2.*Q(n2+n3+n4,3)*Q(n6,1)*Q(n1+n7,2)*Q(n5+n8,2)-Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n5+n8,2)
                + Q(n3+n4,2)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n5+n8,2)-Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n5+n8,2)
                + Q(n2+n4,2)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n5+n8,2)+2.*Q(n4,1)*Q(n2+n3+n6,3)*Q(n1+n7,2)*Q(n5+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n5+n8,2)+Q(n2+n3,2)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n5+n8,2)
                + 2.*Q(n3,1)*Q(n2+n4+n6,3)*Q(n1+n7,2)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n3+n4+n6,3)*Q(n1+n7,2)*Q(n5+n8,2)
                - 6.*Q(n2+n3+n4+n6,4)*Q(n1+n7,2)*Q(n5+n8,2)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n2+n7,2)*Q(n5+n8,2)
                - Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n2+n7,2)*Q(n5+n8,2)-Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n2+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n3+n4,2)*Q(n6,1)*Q(n2+n7,2)*Q(n5+n8,2)+2.*Q(n1+n3+n4,3)*Q(n6,1)*Q(n2+n7,2)*Q(n5+n8,2)
                - Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n5+n8,2)+Q(n3+n4,2)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n4,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n5+n8,2)+Q(n1+n4,2)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n5+n8,2)
                + 2.*Q(n4,1)*Q(n1+n3+n6,3)*Q(n2+n7,2)*Q(n5+n8,2)-Q(n1,1)*Q(n3,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n5+n8,2)
                + Q(n1+n3,2)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n5+n8,2)+2.*Q(n3,1)*Q(n1+n4+n6,3)*Q(n2+n7,2)*Q(n5+n8,2)
                + 2.*Q(n1,1)*Q(n3+n4+n6,3)*Q(n2+n7,2)*Q(n5+n8,2)-6.*Q(n1+n3+n4+n6,4)*Q(n2+n7,2)*Q(n5+n8,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n5+n8,2)+2.*Q(n3+n4,2)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n5+n8,2)
                + 2.*Q(n4,1)*Q(n3+n6,2)*Q(n1+n2+n7,3)*Q(n5+n8,2)+2.*Q(n3,1)*Q(n4+n6,2)*Q(n1+n2+n7,3)*Q(n5+n8,2)
                - 4.*Q(n3+n4+n6,3)*Q(n1+n2+n7,3)*Q(n5+n8,2)+Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n3+n7,2)*Q(n5+n8,2)
                - Q(n1+n2,2)*Q(n4,1)*Q(n6,1)*Q(n3+n7,2)*Q(n5+n8,2)-Q(n2,1)*Q(n1+n4,2)*Q(n6,1)*Q(n3+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n2+n4,2)*Q(n6,1)*Q(n3+n7,2)*Q(n5+n8,2)+2.*Q(n1+n2+n4,3)*Q(n6,1)*Q(n3+n7,2)*Q(n5+n8,2)
                - Q(n2,1)*Q(n4,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n5+n8,2)+Q(n2+n4,2)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n4,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n5+n8,2)+Q(n1+n4,2)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n5+n8,2)
                + 2.*Q(n4,1)*Q(n1+n2+n6,3)*Q(n3+n7,2)*Q(n5+n8,2)-Q(n1,1)*Q(n2,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n5+n8,2)
                + Q(n1+n2,2)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n1+n4+n6,3)*Q(n3+n7,2)*Q(n5+n8,2)
                + 2.*Q(n1,1)*Q(n2+n4+n6,3)*Q(n3+n7,2)*Q(n5+n8,2)-6.*Q(n1+n2+n4+n6,4)*Q(n3+n7,2)*Q(n5+n8,2)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n5+n8,2)+2.*Q(n2+n4,2)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n5+n8,2)
                + 2.*Q(n4,1)*Q(n2+n6,2)*Q(n1+n3+n7,3)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n4+n6,2)*Q(n1+n3+n7,3)*Q(n5+n8,2)
                - 4.*Q(n2+n4+n6,3)*Q(n1+n3+n7,3)*Q(n5+n8,2)-2.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n5+n8,2)
                + 2.*Q(n1+n4,2)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n5+n8,2)+2.*Q(n4,1)*Q(n1+n6,2)*Q(n2+n3+n7,3)*Q(n5+n8,2)
                + 2.*Q(n1,1)*Q(n4+n6,2)*Q(n2+n3+n7,3)*Q(n5+n8,2)-4.*Q(n1+n4+n6,3)*Q(n2+n3+n7,3)*Q(n5+n8,2)
                + 6.*Q(n4,1)*Q(n6,1)*Q(n1+n2+n3+n7,4)*Q(n5+n8,2)-6.*Q(n4+n6,2)*Q(n1+n2+n3+n7,4)*Q(n5+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n4+n7,2)*Q(n5+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n6,1)*Q(n4+n7,2)*Q(n5+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n6,1)*Q(n4+n7,2)*Q(n5+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n6,1)*Q(n4+n7,2)*Q(n5+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n6,1)*Q(n4+n7,2)*Q(n5+n8,2)-Q(n2,1)*Q(n3,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n5+n8,2)
                + Q(n2+n3,2)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n5+n8,2)-Q(n1,1)*Q(n3,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n5+n8,2)
                + Q(n1+n3,2)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n5+n8,2)+2.*Q(n3,1)*Q(n1+n2+n6,3)*Q(n4+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n5+n8,2)+Q(n1+n2,2)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n5+n8,2)
                + 2.*Q(n2,1)*Q(n1+n3+n6,3)*Q(n4+n7,2)*Q(n5+n8,2)+2.*Q(n1,1)*Q(n2+n3+n6,3)*Q(n4+n7,2)*Q(n5+n8,2)
                - 6.*Q(n1+n2+n3+n6,4)*Q(n4+n7,2)*Q(n5+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n5+n8,2)
                + 2.*Q(n2+n3,2)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n5+n8,2)+2.*Q(n3,1)*Q(n2+n6,2)*Q(n1+n4+n7,3)*Q(n5+n8,2)
                + 2.*Q(n2,1)*Q(n3+n6,2)*Q(n1+n4+n7,3)*Q(n5+n8,2)-4.*Q(n2+n3+n6,3)*Q(n1+n4+n7,3)*Q(n5+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n5+n8,2)+2.*Q(n1+n3,2)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n5+n8,2)
                + 2.*Q(n3,1)*Q(n1+n6,2)*Q(n2+n4+n7,3)*Q(n5+n8,2)+2.*Q(n1,1)*Q(n3+n6,2)*Q(n2+n4+n7,3)*Q(n5+n8,2)
                - 4.*Q(n1+n3+n6,3)*Q(n2+n4+n7,3)*Q(n5+n8,2)+6.*Q(n3,1)*Q(n6,1)*Q(n1+n2+n4+n7,4)*Q(n5+n8,2)
                - 6.*Q(n3+n6,2)*Q(n1+n2+n4+n7,4)*Q(n5+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n5+n8,2)
                + 2.*Q(n1+n2,2)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n1+n6,2)*Q(n3+n4+n7,3)*Q(n5+n8,2)
                + 2.*Q(n1,1)*Q(n2+n6,2)*Q(n3+n4+n7,3)*Q(n5+n8,2)-4.*Q(n1+n2+n6,3)*Q(n3+n4+n7,3)*Q(n5+n8,2)
                + 6.*Q(n2,1)*Q(n6,1)*Q(n1+n3+n4+n7,4)*Q(n5+n8,2)-6.*Q(n2+n6,2)*Q(n1+n3+n4+n7,4)*Q(n5+n8,2)
                + 6.*Q(n1,1)*Q(n6,1)*Q(n2+n3+n4+n7,4)*Q(n5+n8,2)-6.*Q(n1+n6,2)*Q(n2+n3+n4+n7,4)*Q(n5+n8,2)
                - 24.*Q(n6,1)*Q(n1+n2+n3+n4+n7,5)*Q(n5+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6+n7,2)*Q(n5+n8,2)
                - Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n6+n7,2)*Q(n5+n8,2)-Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n6+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n6+n7,2)*Q(n5+n8,2)+2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n6+n7,2)*Q(n5+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n6+n7,2)*Q(n5+n8,2)+Q(n2+n3,2)*Q(n1+n4,2)*Q(n6+n7,2)*Q(n5+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n6+n7,2)*Q(n5+n8,2)+Q(n1+n3,2)*Q(n2+n4,2)*Q(n6+n7,2)*Q(n5+n8,2)
                + 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n6+n7,2)*Q(n5+n8,2)-Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n6+n7,2)*Q(n5+n8,2)
                + Q(n1+n2,2)*Q(n3+n4,2)*Q(n6+n7,2)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n6+n7,2)*Q(n5+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n6+n7,2)*Q(n5+n8,2)-6.*Q(n1+n2+n3+n4,4)*Q(n6+n7,2)*Q(n5+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n6+n7,3)*Q(n5+n8,2)+2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n6+n7,3)*Q(n5+n8,2)
                + 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n6+n7,3)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n6+n7,3)*Q(n5+n8,2)
                - 4.*Q(n2+n3+n4,3)*Q(n1+n6+n7,3)*Q(n5+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n6+n7,3)*Q(n5+n8,2)
                + 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n6+n7,3)*Q(n5+n8,2)+2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n6+n7,3)*Q(n5+n8,2)
                + 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n6+n7,3)*Q(n5+n8,2)-4.*Q(n1+n3+n4,3)*Q(n2+n6+n7,3)*Q(n5+n8,2)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n6+n7,4)*Q(n5+n8,2)-6.*Q(n3+n4,2)*Q(n1+n2+n6+n7,4)*Q(n5+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n6+n7,3)*Q(n5+n8,2)+2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n6+n7,3)*Q(n5+n8,2)
                + 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n6+n7,3)*Q(n5+n8,2)+2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n6+n7,3)*Q(n5+n8,2)
                - 4.*Q(n1+n2+n4,3)*Q(n3+n6+n7,3)*Q(n5+n8,2)+6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n6+n7,4)*Q(n5+n8,2)
                - 6.*Q(n2+n4,2)*Q(n1+n3+n6+n7,4)*Q(n5+n8,2)+6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n6+n7,4)*Q(n5+n8,2)
                - 6.*Q(n1+n4,2)*Q(n2+n3+n6+n7,4)*Q(n5+n8,2)-24.*Q(n4,1)*Q(n1+n2+n3+n6+n7,5)*Q(n5+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n6+n7,3)*Q(n5+n8,2)+2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n6+n7,3)*Q(n5+n8,2)
                + 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n6+n7,3)*Q(n5+n8,2)+2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n6+n7,3)*Q(n5+n8,2)
                - 4.*Q(n1+n2+n3,3)*Q(n4+n6+n7,3)*Q(n5+n8,2)+6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n6+n7,4)*Q(n5+n8,2)
                - 6.*Q(n2+n3,2)*Q(n1+n4+n6+n7,4)*Q(n5+n8,2)+6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n6+n7,4)*Q(n5+n8,2)
                - 6.*Q(n1+n3,2)*Q(n2+n4+n6+n7,4)*Q(n5+n8,2)-24.*Q(n3,1)*Q(n1+n2+n4+n6+n7,5)*Q(n5+n8,2)
                + 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n6+n7,4)*Q(n5+n8,2)-6.*Q(n1+n2,2)*Q(n3+n4+n6+n7,4)*Q(n5+n8,2)
                - 24.*Q(n2,1)*Q(n1+n3+n4+n6+n7,5)*Q(n5+n8,2)-24.*Q(n1,1)*Q(n2+n3+n4+n6+n7,5)*Q(n5+n8,2)
                + 120.*Q(n1+n2+n3+n4+n6+n7,6)*Q(n5+n8,2)+2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n1+n5+n8,3)
                - 2.*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n1+n5+n8,3)-2.*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n7,1)*Q(n1+n5+n8,3)
                - 2.*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n7,1)*Q(n1+n5+n8,3)+4.*Q(n2+n3+n4,3)*Q(n6,1)*Q(n7,1)*Q(n1+n5+n8,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n5+n8,3)+2.*Q(n3+n4,2)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n5+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n5+n8,3)+2.*Q(n2+n4,2)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n5+n8,3)
                + 4.*Q(n4,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n1+n5+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n5+n8,3)
                + 2.*Q(n2+n3,2)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n5+n8,3)+4.*Q(n3,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n1+n5+n8,3)
                + 4.*Q(n2,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n1+n5+n8,3)-12.*Q(n2+n3+n4+n6,4)*Q(n7,1)*Q(n1+n5+n8,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n5+n8,3)+2.*Q(n3+n4,2)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n5+n8,3)
                + 2.*Q(n4,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n1+n5+n8,3)+2.*Q(n3,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n1+n5+n8,3)
                - 4.*Q(n3+n4+n6,3)*Q(n2+n7,2)*Q(n1+n5+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n5+n8,3)
                + 2.*Q(n2+n4,2)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n5+n8,3)+2.*Q(n4,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n1+n5+n8,3)
                + 2.*Q(n2,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n1+n5+n8,3)-4.*Q(n2+n4+n6,3)*Q(n3+n7,2)*Q(n1+n5+n8,3)
                + 4.*Q(n4,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n1+n5+n8,3)-4.*Q(n4+n6,2)*Q(n2+n3+n7,3)*Q(n1+n5+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n5+n8,3)+2.*Q(n2+n3,2)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n5+n8,3)
                + 2.*Q(n3,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n1+n5+n8,3)+2.*Q(n2,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n1+n5+n8,3)
                - 4.*Q(n2+n3+n6,3)*Q(n4+n7,2)*Q(n1+n5+n8,3)+4.*Q(n3,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n1+n5+n8,3)
                - 4.*Q(n3+n6,2)*Q(n2+n4+n7,3)*Q(n1+n5+n8,3)+4.*Q(n2,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n1+n5+n8,3)
                - 4.*Q(n2+n6,2)*Q(n3+n4+n7,3)*Q(n1+n5+n8,3)-12.*Q(n6,1)*Q(n2+n3+n4+n7,4)*Q(n1+n5+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6+n7,2)*Q(n1+n5+n8,3)+2.*Q(n2+n3,2)*Q(n4,1)*Q(n6+n7,2)*Q(n1+n5+n8,3)
                + 2.*Q(n3,1)*Q(n2+n4,2)*Q(n6+n7,2)*Q(n1+n5+n8,3)+2.*Q(n2,1)*Q(n3+n4,2)*Q(n6+n7,2)*Q(n1+n5+n8,3)
                - 4.*Q(n2+n3+n4,3)*Q(n6+n7,2)*Q(n1+n5+n8,3)+4.*Q(n3,1)*Q(n4,1)*Q(n2+n6+n7,3)*Q(n1+n5+n8,3)
                - 4.*Q(n3+n4,2)*Q(n2+n6+n7,3)*Q(n1+n5+n8,3)+4.*Q(n2,1)*Q(n4,1)*Q(n3+n6+n7,3)*Q(n1+n5+n8,3)
                - 4.*Q(n2+n4,2)*Q(n3+n6+n7,3)*Q(n1+n5+n8,3)-12.*Q(n4,1)*Q(n2+n3+n6+n7,4)*Q(n1+n5+n8,3)
                + 4.*Q(n2,1)*Q(n3,1)*Q(n4+n6+n7,3)*Q(n1+n5+n8,3)-4.*Q(n2+n3,2)*Q(n4+n6+n7,3)*Q(n1+n5+n8,3)
                - 12.*Q(n3,1)*Q(n2+n4+n6+n7,4)*Q(n1+n5+n8,3)-12.*Q(n2,1)*Q(n3+n4+n6+n7,4)*Q(n1+n5+n8,3)
                + 48.*Q(n2+n3+n4+n6+n7,5)*Q(n1+n5+n8,3)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n2+n5+n8,3)
                - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n2+n5+n8,3)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n7,1)*Q(n2+n5+n8,3)
                - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n6,1)*Q(n7,1)*Q(n2+n5+n8,3)+4.*Q(n1+n3+n4,3)*Q(n6,1)*Q(n7,1)*Q(n2+n5+n8,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n5+n8,3)+2.*Q(n3+n4,2)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n5+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n5+n8,3)+2.*Q(n1+n4,2)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n5+n8,3)
                + 4.*Q(n4,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n2+n5+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n5+n8,3)
                + 2.*Q(n1+n3,2)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n5+n8,3)+4.*Q(n3,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n2+n5+n8,3)
                + 4.*Q(n1,1)*Q(n3+n4+n6,3)*Q(n7,1)*Q(n2+n5+n8,3)-12.*Q(n1+n3+n4+n6,4)*Q(n7,1)*Q(n2+n5+n8,3)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n5+n8,3)+2.*Q(n3+n4,2)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n5+n8,3)
                + 2.*Q(n4,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n2+n5+n8,3)+2.*Q(n3,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n2+n5+n8,3)
                - 4.*Q(n3+n4+n6,3)*Q(n1+n7,2)*Q(n2+n5+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n5+n8,3)
                + 2.*Q(n1+n4,2)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n5+n8,3)+2.*Q(n4,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n2+n5+n8,3)
                + 2.*Q(n1,1)*Q(n4+n6,2)*Q(n3+n7,2)*Q(n2+n5+n8,3)-4.*Q(n1+n4+n6,3)*Q(n3+n7,2)*Q(n2+n5+n8,3)
                + 4.*Q(n4,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n2+n5+n8,3)-4.*Q(n4+n6,2)*Q(n1+n3+n7,3)*Q(n2+n5+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n5+n8,3)+2.*Q(n1+n3,2)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n5+n8,3)
                + 2.*Q(n3,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n2+n5+n8,3)+2.*Q(n1,1)*Q(n3+n6,2)*Q(n4+n7,2)*Q(n2+n5+n8,3)
                - 4.*Q(n1+n3+n6,3)*Q(n4+n7,2)*Q(n2+n5+n8,3)+4.*Q(n3,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n2+n5+n8,3)
                - 4.*Q(n3+n6,2)*Q(n1+n4+n7,3)*Q(n2+n5+n8,3)+4.*Q(n1,1)*Q(n6,1)*Q(n3+n4+n7,3)*Q(n2+n5+n8,3)
                - 4.*Q(n1+n6,2)*Q(n3+n4+n7,3)*Q(n2+n5+n8,3)-12.*Q(n6,1)*Q(n1+n3+n4+n7,4)*Q(n2+n5+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6+n7,2)*Q(n2+n5+n8,3)+2.*Q(n1+n3,2)*Q(n4,1)*Q(n6+n7,2)*Q(n2+n5+n8,3)
                + 2.*Q(n3,1)*Q(n1+n4,2)*Q(n6+n7,2)*Q(n2+n5+n8,3)+2.*Q(n1,1)*Q(n3+n4,2)*Q(n6+n7,2)*Q(n2+n5+n8,3)
                - 4.*Q(n1+n3+n4,3)*Q(n6+n7,2)*Q(n2+n5+n8,3)+4.*Q(n3,1)*Q(n4,1)*Q(n1+n6+n7,3)*Q(n2+n5+n8,3)
                - 4.*Q(n3+n4,2)*Q(n1+n6+n7,3)*Q(n2+n5+n8,3)+4.*Q(n1,1)*Q(n4,1)*Q(n3+n6+n7,3)*Q(n2+n5+n8,3)
                - 4.*Q(n1+n4,2)*Q(n3+n6+n7,3)*Q(n2+n5+n8,3)-12.*Q(n4,1)*Q(n1+n3+n6+n7,4)*Q(n2+n5+n8,3)
                + 4.*Q(n1,1)*Q(n3,1)*Q(n4+n6+n7,3)*Q(n2+n5+n8,3)-4.*Q(n1+n3,2)*Q(n4+n6+n7,3)*Q(n2+n5+n8,3)
                - 12.*Q(n3,1)*Q(n1+n4+n6+n7,4)*Q(n2+n5+n8,3)-12.*Q(n1,1)*Q(n3+n4+n6+n7,4)*Q(n2+n5+n8,3)
                + 48.*Q(n1+n3+n4+n6+n7,5)*Q(n2+n5+n8,3)-6.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n5+n8,4)
                + 6.*Q(n3+n4,2)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n5+n8,4)+6.*Q(n4,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n2+n5+n8,4)
                + 6.*Q(n3,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n2+n5+n8,4)-12.*Q(n3+n4+n6,3)*Q(n7,1)*Q(n1+n2+n5+n8,4)
                + 6.*Q(n4,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n2+n5+n8,4)-6.*Q(n4+n6,2)*Q(n3+n7,2)*Q(n1+n2+n5+n8,4)
                + 6.*Q(n3,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n2+n5+n8,4)-6.*Q(n3+n6,2)*Q(n4+n7,2)*Q(n1+n2+n5+n8,4)
                - 12.*Q(n6,1)*Q(n3+n4+n7,3)*Q(n1+n2+n5+n8,4)+6.*Q(n3,1)*Q(n4,1)*Q(n6+n7,2)*Q(n1+n2+n5+n8,4)
                - 6.*Q(n3+n4,2)*Q(n6+n7,2)*Q(n1+n2+n5+n8,4)-12.*Q(n4,1)*Q(n3+n6+n7,3)*Q(n1+n2+n5+n8,4)
                - 12.*Q(n3,1)*Q(n4+n6+n7,3)*Q(n1+n2+n5+n8,4)+36.*Q(n3+n4+n6+n7,4)*Q(n1+n2+n5+n8,4)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n3+n5+n8,3)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n3+n5+n8,3)
                - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n6,1)*Q(n7,1)*Q(n3+n5+n8,3)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n6,1)*Q(n7,1)*Q(n3+n5+n8,3)
                + 4.*Q(n1+n2+n4,3)*Q(n6,1)*Q(n7,1)*Q(n3+n5+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n5+n8,3)
                + 2.*Q(n2+n4,2)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n5+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n5+n8,3)
                + 2.*Q(n1+n4,2)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n5+n8,3)+4.*Q(n4,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n3+n5+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n5+n8,3)+2.*Q(n1+n2,2)*Q(n4+n6,2)*Q(n7,1)*Q(n3+n5+n8,3)
                + 4.*Q(n2,1)*Q(n1+n4+n6,3)*Q(n7,1)*Q(n3+n5+n8,3)+4.*Q(n1,1)*Q(n2+n4+n6,3)*Q(n7,1)*Q(n3+n5+n8,3)
                - 12.*Q(n1+n2+n4+n6,4)*Q(n7,1)*Q(n3+n5+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n2+n4,2)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n5+n8,3)+2.*Q(n4,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n2,1)*Q(n4+n6,2)*Q(n1+n7,2)*Q(n3+n5+n8,3)-4.*Q(n2+n4+n6,3)*Q(n1+n7,2)*Q(n3+n5+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n5+n8,3)+2.*Q(n1+n4,2)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n4,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n3+n5+n8,3)+2.*Q(n1,1)*Q(n4+n6,2)*Q(n2+n7,2)*Q(n3+n5+n8,3)
                - 4.*Q(n1+n4+n6,3)*Q(n2+n7,2)*Q(n3+n5+n8,3)+4.*Q(n4,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n3+n5+n8,3)
                - 4.*Q(n4+n6,2)*Q(n1+n2+n7,3)*Q(n3+n5+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n1+n2,2)*Q(n6,1)*Q(n4+n7,2)*Q(n3+n5+n8,3)+2.*Q(n2,1)*Q(n1+n6,2)*Q(n4+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n1,1)*Q(n2+n6,2)*Q(n4+n7,2)*Q(n3+n5+n8,3)-4.*Q(n1+n2+n6,3)*Q(n4+n7,2)*Q(n3+n5+n8,3)
                + 4.*Q(n2,1)*Q(n6,1)*Q(n1+n4+n7,3)*Q(n3+n5+n8,3)-4.*Q(n2+n6,2)*Q(n1+n4+n7,3)*Q(n3+n5+n8,3)
                + 4.*Q(n1,1)*Q(n6,1)*Q(n2+n4+n7,3)*Q(n3+n5+n8,3)-4.*Q(n1+n6,2)*Q(n2+n4+n7,3)*Q(n3+n5+n8,3)
                - 12.*Q(n6,1)*Q(n1+n2+n4+n7,4)*Q(n3+n5+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n1+n2,2)*Q(n4,1)*Q(n6+n7,2)*Q(n3+n5+n8,3)+2.*Q(n2,1)*Q(n1+n4,2)*Q(n6+n7,2)*Q(n3+n5+n8,3)
                + 2.*Q(n1,1)*Q(n2+n4,2)*Q(n6+n7,2)*Q(n3+n5+n8,3)-4.*Q(n1+n2+n4,3)*Q(n6+n7,2)*Q(n3+n5+n8,3)
                + 4.*Q(n2,1)*Q(n4,1)*Q(n1+n6+n7,3)*Q(n3+n5+n8,3)-4.*Q(n2+n4,2)*Q(n1+n6+n7,3)*Q(n3+n5+n8,3)
                + 4.*Q(n1,1)*Q(n4,1)*Q(n2+n6+n7,3)*Q(n3+n5+n8,3)-4.*Q(n1+n4,2)*Q(n2+n6+n7,3)*Q(n3+n5+n8,3)
                - 12.*Q(n4,1)*Q(n1+n2+n6+n7,4)*Q(n3+n5+n8,3)+4.*Q(n1,1)*Q(n2,1)*Q(n4+n6+n7,3)*Q(n3+n5+n8,3)
                - 4.*Q(n1+n2,2)*Q(n4+n6+n7,3)*Q(n3+n5+n8,3)-12.*Q(n2,1)*Q(n1+n4+n6+n7,4)*Q(n3+n5+n8,3)
                - 12.*Q(n1,1)*Q(n2+n4+n6+n7,4)*Q(n3+n5+n8,3)+48.*Q(n1+n2+n4+n6+n7,5)*Q(n3+n5+n8,3)
                - 6.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n5+n8,4)+6.*Q(n2+n4,2)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n5+n8,4)
                + 6.*Q(n4,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n3+n5+n8,4)+6.*Q(n2,1)*Q(n4+n6,2)*Q(n7,1)*Q(n1+n3+n5+n8,4)
                - 12.*Q(n2+n4+n6,3)*Q(n7,1)*Q(n1+n3+n5+n8,4)+6.*Q(n4,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n3+n5+n8,4)
                - 6.*Q(n4+n6,2)*Q(n2+n7,2)*Q(n1+n3+n5+n8,4)+6.*Q(n2,1)*Q(n6,1)*Q(n4+n7,2)*Q(n1+n3+n5+n8,4)
                - 6.*Q(n2+n6,2)*Q(n4+n7,2)*Q(n1+n3+n5+n8,4)-12.*Q(n6,1)*Q(n2+n4+n7,3)*Q(n1+n3+n5+n8,4)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n6+n7,2)*Q(n1+n3+n5+n8,4)-6.*Q(n2+n4,2)*Q(n6+n7,2)*Q(n1+n3+n5+n8,4)
                - 12.*Q(n4,1)*Q(n2+n6+n7,3)*Q(n1+n3+n5+n8,4)-12.*Q(n2,1)*Q(n4+n6+n7,3)*Q(n1+n3+n5+n8,4)
                + 36.*Q(n2+n4+n6+n7,4)*Q(n1+n3+n5+n8,4)-6.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n5+n8,4)
                + 6.*Q(n1+n4,2)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n5+n8,4)+6.*Q(n4,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n3+n5+n8,4)
                + 6.*Q(n1,1)*Q(n4+n6,2)*Q(n7,1)*Q(n2+n3+n5+n8,4)-12.*Q(n1+n4+n6,3)*Q(n7,1)*Q(n2+n3+n5+n8,4)
                + 6.*Q(n4,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n3+n5+n8,4)-6.*Q(n4+n6,2)*Q(n1+n7,2)*Q(n2+n3+n5+n8,4)
                + 6.*Q(n1,1)*Q(n6,1)*Q(n4+n7,2)*Q(n2+n3+n5+n8,4)-6.*Q(n1+n6,2)*Q(n4+n7,2)*Q(n2+n3+n5+n8,4)
                - 12.*Q(n6,1)*Q(n1+n4+n7,3)*Q(n2+n3+n5+n8,4)+6.*Q(n1,1)*Q(n4,1)*Q(n6+n7,2)*Q(n2+n3+n5+n8,4)
                - 6.*Q(n1+n4,2)*Q(n6+n7,2)*Q(n2+n3+n5+n8,4)-12.*Q(n4,1)*Q(n1+n6+n7,3)*Q(n2+n3+n5+n8,4)
                - 12.*Q(n1,1)*Q(n4+n6+n7,3)*Q(n2+n3+n5+n8,4)+36.*Q(n1+n4+n6+n7,4)*Q(n2+n3+n5+n8,4)
                + 24.*Q(n4,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n3+n5+n8,5)-24.*Q(n4+n6,2)*Q(n7,1)*Q(n1+n2+n3+n5+n8,5)
                - 24.*Q(n6,1)*Q(n4+n7,2)*Q(n1+n2+n3+n5+n8,5)-24.*Q(n4,1)*Q(n6+n7,2)*Q(n1+n2+n3+n5+n8,5)
                + 48.*Q(n4+n6+n7,3)*Q(n1+n2+n3+n5+n8,5)+2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n7,1)*Q(n4+n5+n8,3)
                - 2.*Q(n1+n2,2)*Q(n3,1)*Q(n6,1)*Q(n7,1)*Q(n4+n5+n8,3)-2.*Q(n2,1)*Q(n1+n3,2)*Q(n6,1)*Q(n7,1)*Q(n4+n5+n8,3)
                - 2.*Q(n1,1)*Q(n2+n3,2)*Q(n6,1)*Q(n7,1)*Q(n4+n5+n8,3)+4.*Q(n1+n2+n3,3)*Q(n6,1)*Q(n7,1)*Q(n4+n5+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n5+n8,3)+2.*Q(n2+n3,2)*Q(n1+n6,2)*Q(n7,1)*Q(n4+n5+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n5+n8,3)+2.*Q(n1+n3,2)*Q(n2+n6,2)*Q(n7,1)*Q(n4+n5+n8,3)
                + 4.*Q(n3,1)*Q(n1+n2+n6,3)*Q(n7,1)*Q(n4+n5+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n5+n8,3)
                + 2.*Q(n1+n2,2)*Q(n3+n6,2)*Q(n7,1)*Q(n4+n5+n8,3)+4.*Q(n2,1)*Q(n1+n3+n6,3)*Q(n7,1)*Q(n4+n5+n8,3)
                + 4.*Q(n1,1)*Q(n2+n3+n6,3)*Q(n7,1)*Q(n4+n5+n8,3)-12.*Q(n1+n2+n3+n6,4)*Q(n7,1)*Q(n4+n5+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n5+n8,3)+2.*Q(n2+n3,2)*Q(n6,1)*Q(n1+n7,2)*Q(n4+n5+n8,3)
                + 2.*Q(n3,1)*Q(n2+n6,2)*Q(n1+n7,2)*Q(n4+n5+n8,3)+2.*Q(n2,1)*Q(n3+n6,2)*Q(n1+n7,2)*Q(n4+n5+n8,3)
                - 4.*Q(n2+n3+n6,3)*Q(n1+n7,2)*Q(n4+n5+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n5+n8,3)
                + 2.*Q(n1+n3,2)*Q(n6,1)*Q(n2+n7,2)*Q(n4+n5+n8,3)+2.*Q(n3,1)*Q(n1+n6,2)*Q(n2+n7,2)*Q(n4+n5+n8,3)
                + 2.*Q(n1,1)*Q(n3+n6,2)*Q(n2+n7,2)*Q(n4+n5+n8,3)-4.*Q(n1+n3+n6,3)*Q(n2+n7,2)*Q(n4+n5+n8,3)
                + 4.*Q(n3,1)*Q(n6,1)*Q(n1+n2+n7,3)*Q(n4+n5+n8,3)-4.*Q(n3+n6,2)*Q(n1+n2+n7,3)*Q(n4+n5+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n5+n8,3)+2.*Q(n1+n2,2)*Q(n6,1)*Q(n3+n7,2)*Q(n4+n5+n8,3)
                + 2.*Q(n2,1)*Q(n1+n6,2)*Q(n3+n7,2)*Q(n4+n5+n8,3)+2.*Q(n1,1)*Q(n2+n6,2)*Q(n3+n7,2)*Q(n4+n5+n8,3)
                - 4.*Q(n1+n2+n6,3)*Q(n3+n7,2)*Q(n4+n5+n8,3)+4.*Q(n2,1)*Q(n6,1)*Q(n1+n3+n7,3)*Q(n4+n5+n8,3)
                - 4.*Q(n2+n6,2)*Q(n1+n3+n7,3)*Q(n4+n5+n8,3)+4.*Q(n1,1)*Q(n6,1)*Q(n2+n3+n7,3)*Q(n4+n5+n8,3)
                - 4.*Q(n1+n6,2)*Q(n2+n3+n7,3)*Q(n4+n5+n8,3)-12.*Q(n6,1)*Q(n1+n2+n3+n7,4)*Q(n4+n5+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6+n7,2)*Q(n4+n5+n8,3)+2.*Q(n1+n2,2)*Q(n3,1)*Q(n6+n7,2)*Q(n4+n5+n8,3)
                + 2.*Q(n2,1)*Q(n1+n3,2)*Q(n6+n7,2)*Q(n4+n5+n8,3)+2.*Q(n1,1)*Q(n2+n3,2)*Q(n6+n7,2)*Q(n4+n5+n8,3)
                - 4.*Q(n1+n2+n3,3)*Q(n6+n7,2)*Q(n4+n5+n8,3)+4.*Q(n2,1)*Q(n3,1)*Q(n1+n6+n7,3)*Q(n4+n5+n8,3)
                - 4.*Q(n2+n3,2)*Q(n1+n6+n7,3)*Q(n4+n5+n8,3)+4.*Q(n1,1)*Q(n3,1)*Q(n2+n6+n7,3)*Q(n4+n5+n8,3)
                - 4.*Q(n1+n3,2)*Q(n2+n6+n7,3)*Q(n4+n5+n8,3)-12.*Q(n3,1)*Q(n1+n2+n6+n7,4)*Q(n4+n5+n8,3)
                + 4.*Q(n1,1)*Q(n2,1)*Q(n3+n6+n7,3)*Q(n4+n5+n8,3)-4.*Q(n1+n2,2)*Q(n3+n6+n7,3)*Q(n4+n5+n8,3)
                - 12.*Q(n2,1)*Q(n1+n3+n6+n7,4)*Q(n4+n5+n8,3)-12.*Q(n1,1)*Q(n2+n3+n6+n7,4)*Q(n4+n5+n8,3)
                + 48.*Q(n1+n2+n3+n6+n7,5)*Q(n4+n5+n8,3)-6.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n5+n8,4)
                + 6.*Q(n2+n3,2)*Q(n6,1)*Q(n7,1)*Q(n1+n4+n5+n8,4)+6.*Q(n3,1)*Q(n2+n6,2)*Q(n7,1)*Q(n1+n4+n5+n8,4)
                + 6.*Q(n2,1)*Q(n3+n6,2)*Q(n7,1)*Q(n1+n4+n5+n8,4)-12.*Q(n2+n3+n6,3)*Q(n7,1)*Q(n1+n4+n5+n8,4)
                + 6.*Q(n3,1)*Q(n6,1)*Q(n2+n7,2)*Q(n1+n4+n5+n8,4)-6.*Q(n3+n6,2)*Q(n2+n7,2)*Q(n1+n4+n5+n8,4)
                + 6.*Q(n2,1)*Q(n6,1)*Q(n3+n7,2)*Q(n1+n4+n5+n8,4)-6.*Q(n2+n6,2)*Q(n3+n7,2)*Q(n1+n4+n5+n8,4)
                - 12.*Q(n6,1)*Q(n2+n3+n7,3)*Q(n1+n4+n5+n8,4)+6.*Q(n2,1)*Q(n3,1)*Q(n6+n7,2)*Q(n1+n4+n5+n8,4)
                - 6.*Q(n2+n3,2)*Q(n6+n7,2)*Q(n1+n4+n5+n8,4)-12.*Q(n3,1)*Q(n2+n6+n7,3)*Q(n1+n4+n5+n8,4)
                - 12.*Q(n2,1)*Q(n3+n6+n7,3)*Q(n1+n4+n5+n8,4)+36.*Q(n2+n3+n6+n7,4)*Q(n1+n4+n5+n8,4)
                - 6.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n5+n8,4)+6.*Q(n1+n3,2)*Q(n6,1)*Q(n7,1)*Q(n2+n4+n5+n8,4)
                + 6.*Q(n3,1)*Q(n1+n6,2)*Q(n7,1)*Q(n2+n4+n5+n8,4)+6.*Q(n1,1)*Q(n3+n6,2)*Q(n7,1)*Q(n2+n4+n5+n8,4)
                - 12.*Q(n1+n3+n6,3)*Q(n7,1)*Q(n2+n4+n5+n8,4)+6.*Q(n3,1)*Q(n6,1)*Q(n1+n7,2)*Q(n2+n4+n5+n8,4)
                - 6.*Q(n3+n6,2)*Q(n1+n7,2)*Q(n2+n4+n5+n8,4)+6.*Q(n1,1)*Q(n6,1)*Q(n3+n7,2)*Q(n2+n4+n5+n8,4)
                - 6.*Q(n1+n6,2)*Q(n3+n7,2)*Q(n2+n4+n5+n8,4)-12.*Q(n6,1)*Q(n1+n3+n7,3)*Q(n2+n4+n5+n8,4)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n6+n7,2)*Q(n2+n4+n5+n8,4)-6.*Q(n1+n3,2)*Q(n6+n7,2)*Q(n2+n4+n5+n8,4)
                - 12.*Q(n3,1)*Q(n1+n6+n7,3)*Q(n2+n4+n5+n8,4)-12.*Q(n1,1)*Q(n3+n6+n7,3)*Q(n2+n4+n5+n8,4)
                + 36.*Q(n1+n3+n6+n7,4)*Q(n2+n4+n5+n8,4)+24.*Q(n3,1)*Q(n6,1)*Q(n7,1)*Q(n1+n2+n4+n5+n8,5)
                - 24.*Q(n3+n6,2)*Q(n7,1)*Q(n1+n2+n4+n5+n8,5)-24.*Q(n6,1)*Q(n3+n7,2)*Q(n1+n2+n4+n5+n8,5)
                - 24.*Q(n3,1)*Q(n6+n7,2)*Q(n1+n2+n4+n5+n8,5)+48.*Q(n3+n6+n7,3)*Q(n1+n2+n4+n5+n8,5)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n5+n8,4)+6.*Q(n1+n2,2)*Q(n6,1)*Q(n7,1)*Q(n3+n4+n5+n8,4)
                + 6.*Q(n2,1)*Q(n1+n6,2)*Q(n7,1)*Q(n3+n4+n5+n8,4)+6.*Q(n1,1)*Q(n2+n6,2)*Q(n7,1)*Q(n3+n4+n5+n8,4)
                - 12.*Q(n1+n2+n6,3)*Q(n7,1)*Q(n3+n4+n5+n8,4)+6.*Q(n2,1)*Q(n6,1)*Q(n1+n7,2)*Q(n3+n4+n5+n8,4)
                - 6.*Q(n2+n6,2)*Q(n1+n7,2)*Q(n3+n4+n5+n8,4)+6.*Q(n1,1)*Q(n6,1)*Q(n2+n7,2)*Q(n3+n4+n5+n8,4)
                - 6.*Q(n1+n6,2)*Q(n2+n7,2)*Q(n3+n4+n5+n8,4)-12.*Q(n6,1)*Q(n1+n2+n7,3)*Q(n3+n4+n5+n8,4)
                + 6.*Q(n1,1)*Q(n2,1)*Q(n6+n7,2)*Q(n3+n4+n5+n8,4)-6.*Q(n1+n2,2)*Q(n6+n7,2)*Q(n3+n4+n5+n8,4)
                - 12.*Q(n2,1)*Q(n1+n6+n7,3)*Q(n3+n4+n5+n8,4)-12.*Q(n1,1)*Q(n2+n6+n7,3)*Q(n3+n4+n5+n8,4)
                + 36.*Q(n1+n2+n6+n7,4)*Q(n3+n4+n5+n8,4)+24.*Q(n2,1)*Q(n6,1)*Q(n7,1)*Q(n1+n3+n4+n5+n8,5)
                - 24.*Q(n2+n6,2)*Q(n7,1)*Q(n1+n3+n4+n5+n8,5)-24.*Q(n6,1)*Q(n2+n7,2)*Q(n1+n3+n4+n5+n8,5)
                - 24.*Q(n2,1)*Q(n6+n7,2)*Q(n1+n3+n4+n5+n8,5)+48.*Q(n2+n6+n7,3)*Q(n1+n3+n4+n5+n8,5)
                + 24.*Q(n1,1)*Q(n6,1)*Q(n7,1)*Q(n2+n3+n4+n5+n8,5)-24.*Q(n1+n6,2)*Q(n7,1)*Q(n2+n3+n4+n5+n8,5)
                - 24.*Q(n6,1)*Q(n1+n7,2)*Q(n2+n3+n4+n5+n8,5)-24.*Q(n1,1)*Q(n6+n7,2)*Q(n2+n3+n4+n5+n8,5)
                + 48.*Q(n1+n6+n7,3)*Q(n2+n3+n4+n5+n8,5)-120.*Q(n6,1)*Q(n7,1)*Q(n1+n2+n3+n4+n5+n8,6)
                + 120.*Q(n6+n7,2)*Q(n1+n2+n3+n4+n5+n8,6)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)+6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n7,1)*Q(n6+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n7,1)*Q(n6+n8,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n7,1)*Q(n6+n8,2)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n7,1)*Q(n6+n8,2)
                - Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n7,1)*Q(n6+n8,2)
                - Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n7,1)*Q(n6+n8,2)+2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n7,1)*Q(n6+n8,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n7,1)*Q(n6+n8,2)+2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n7,1)*Q(n6+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n7,1)*Q(n6+n8,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n7,1)*Q(n6+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n7,1)*Q(n6+n8,2)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n7,1)*Q(n6+n8,2)+6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n7,1)*Q(n6+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n7,1)*Q(n6+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n7,1)*Q(n6+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n7,1)*Q(n6+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n7,1)*Q(n6+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n7,1)*Q(n6+n8,2)
                + 2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n7,1)*Q(n6+n8,2)+6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n7,1)*Q(n6+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n7,1)*Q(n6+n8,2)+2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n7,1)*Q(n6+n8,2)
                + 6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n7,1)*Q(n6+n8,2)+6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n7,1)*Q(n6+n8,2)
                - 24.*Q(n1+n2+n3+n4+n5,5)*Q(n7,1)*Q(n6+n8,2)+Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n7,2)*Q(n6+n8,2)
                - Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n7,2)*Q(n6+n8,2)-Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n7,2)*Q(n6+n8,2)
                - Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n7,2)*Q(n6+n8,2)+2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n7,2)*Q(n6+n8,2)
                - Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n7,2)*Q(n6+n8,2)+Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n7,2)*Q(n6+n8,2)
                - Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n7,2)*Q(n6+n8,2)+Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n7,2)*Q(n6+n8,2)
                + 2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n7,2)*Q(n6+n8,2)-Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n7,2)*Q(n6+n8,2)
                + Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n7,2)*Q(n6+n8,2)+2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n7,2)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n7,2)*Q(n6+n8,2)-6.*Q(n2+n3+n4+n5,4)*Q(n1+n7,2)*Q(n6+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n7,2)*Q(n6+n8,2)-Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n7,2)*Q(n6+n8,2)
                - Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n7,2)*Q(n6+n8,2)
                + 2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n7,2)*Q(n6+n8,2)-Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n7,2)*Q(n6+n8,2)
                + Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n7,2)*Q(n6+n8,2)
                + Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n7,2)*Q(n6+n8,2)+2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n7,2)*Q(n6+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n7,2)*Q(n6+n8,2)+Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n7,2)*Q(n6+n8,2)
                + 2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n7,2)*Q(n6+n8,2)+2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n7,2)*Q(n6+n8,2)
                - 6.*Q(n1+n3+n4+n5,4)*Q(n2+n7,2)*Q(n6+n8,2)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n7,3)*Q(n6+n8,2)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n7,3)*Q(n6+n8,2)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n7,3)*Q(n6+n8,2)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n7,3)*Q(n6+n8,2)-4.*Q(n3+n4+n5,3)*Q(n1+n2+n7,3)*Q(n6+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n7,2)*Q(n6+n8,2)-Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n7,2)*Q(n6+n8,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n7,2)*Q(n6+n8,2)
                + 2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n7,2)*Q(n6+n8,2)-Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n7,2)*Q(n6+n8,2)
                + Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n7,2)*Q(n6+n8,2)
                + Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n7,2)*Q(n6+n8,2)+2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n7,2)*Q(n6+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n7,2)*Q(n6+n8,2)+Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n7,2)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n7,2)*Q(n6+n8,2)+2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n7,2)*Q(n6+n8,2)
                - 6.*Q(n1+n2+n4+n5,4)*Q(n3+n7,2)*Q(n6+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n7,3)*Q(n6+n8,2)
                + 2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n7,3)*Q(n6+n8,2)+2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n7,3)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n7,3)*Q(n6+n8,2)-4.*Q(n2+n4+n5,3)*Q(n1+n3+n7,3)*Q(n6+n8,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n7,3)*Q(n6+n8,2)+2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n7,3)*Q(n6+n8,2)
                + 2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n7,3)*Q(n6+n8,2)+2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n7,3)*Q(n6+n8,2)
                - 4.*Q(n1+n4+n5,3)*Q(n2+n3+n7,3)*Q(n6+n8,2)+6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n7,4)*Q(n6+n8,2)
                - 6.*Q(n4+n5,2)*Q(n1+n2+n3+n7,4)*Q(n6+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n7,2)*Q(n6+n8,2)
                - Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n7,2)*Q(n6+n8,2)-Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n7,2)*Q(n6+n8,2)
                - Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n7,2)*Q(n6+n8,2)+2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n7,2)*Q(n6+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n7,2)*Q(n6+n8,2)+Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n7,2)*Q(n6+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n7,2)*Q(n6+n8,2)+Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n7,2)*Q(n6+n8,2)
                + 2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n7,2)*Q(n6+n8,2)
                + Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n7,2)*Q(n6+n8,2)+2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n7,2)*Q(n6+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n7,2)*Q(n6+n8,2)-6.*Q(n1+n2+n3+n5,4)*Q(n4+n7,2)*Q(n6+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n7,3)*Q(n6+n8,2)+2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n7,3)*Q(n6+n8,2)
                + 2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n7,3)*Q(n6+n8,2)+2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n7,3)*Q(n6+n8,2)
                - 4.*Q(n2+n3+n5,3)*Q(n1+n4+n7,3)*Q(n6+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n7,3)*Q(n6+n8,2)
                + 2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n7,3)*Q(n6+n8,2)+2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n7,3)*Q(n6+n8,2)
                + 2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n7,3)*Q(n6+n8,2)-4.*Q(n1+n3+n5,3)*Q(n2+n4+n7,3)*Q(n6+n8,2)
                + 6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n7,4)*Q(n6+n8,2)-6.*Q(n3+n5,2)*Q(n1+n2+n4+n7,4)*Q(n6+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n7,3)*Q(n6+n8,2)+2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n7,3)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n7,3)*Q(n6+n8,2)+2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n7,3)*Q(n6+n8,2)
                - 4.*Q(n1+n2+n5,3)*Q(n3+n4+n7,3)*Q(n6+n8,2)+6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n7,4)*Q(n6+n8,2)
                - 6.*Q(n2+n5,2)*Q(n1+n3+n4+n7,4)*Q(n6+n8,2)+6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n7,4)*Q(n6+n8,2)
                - 6.*Q(n1+n5,2)*Q(n2+n3+n4+n7,4)*Q(n6+n8,2)-24.*Q(n5,1)*Q(n1+n2+n3+n4+n7,5)*Q(n6+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n7,2)*Q(n6+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n7,2)*Q(n6+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n7,2)*Q(n6+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n7,2)*Q(n6+n8,2)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n7,2)*Q(n6+n8,2)
                + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n7,2)*Q(n6+n8,2)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n7,2)*Q(n6+n8,2)
                + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n7,2)*Q(n6+n8,2)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n7,2)*Q(n6+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n7,2)*Q(n6+n8,2)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n7,2)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n7,2)*Q(n6+n8,2)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n7,2)*Q(n6+n8,2)
                - 6.*Q(n1+n2+n3+n4,4)*Q(n5+n7,2)*Q(n6+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n7,3)*Q(n6+n8,2)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n7,3)*Q(n6+n8,2)-4.*Q(n2+n3+n4,3)*Q(n1+n5+n7,3)*Q(n6+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n7,3)*Q(n6+n8,2)+2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n7,3)*Q(n6+n8,2)+2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n7,3)*Q(n6+n8,2)
                - 4.*Q(n1+n3+n4,3)*Q(n2+n5+n7,3)*Q(n6+n8,2)+6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n7,4)*Q(n6+n8,2)
                - 6.*Q(n3+n4,2)*Q(n1+n2+n5+n7,4)*Q(n6+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n7,3)*Q(n6+n8,2)+2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n7,3)*Q(n6+n8,2)-4.*Q(n1+n2+n4,3)*Q(n3+n5+n7,3)*Q(n6+n8,2)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n7,4)*Q(n6+n8,2)-6.*Q(n2+n4,2)*Q(n1+n3+n5+n7,4)*Q(n6+n8,2)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n7,4)*Q(n6+n8,2)-6.*Q(n1+n4,2)*Q(n2+n3+n5+n7,4)*Q(n6+n8,2)
                - 24.*Q(n4,1)*Q(n1+n2+n3+n5+n7,5)*Q(n6+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n7,3)*Q(n6+n8,2)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n7,3)*Q(n6+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n7,3)*Q(n6+n8,2)-4.*Q(n1+n2+n3,3)*Q(n4+n5+n7,3)*Q(n6+n8,2)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n7,4)*Q(n6+n8,2)-6.*Q(n2+n3,2)*Q(n1+n4+n5+n7,4)*Q(n6+n8,2)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n7,4)*Q(n6+n8,2)-6.*Q(n1+n3,2)*Q(n2+n4+n5+n7,4)*Q(n6+n8,2)
                - 24.*Q(n3,1)*Q(n1+n2+n4+n5+n7,5)*Q(n6+n8,2)+6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n7,4)*Q(n6+n8,2)
                - 6.*Q(n1+n2,2)*Q(n3+n4+n5+n7,4)*Q(n6+n8,2)-24.*Q(n2,1)*Q(n1+n3+n4+n5+n7,5)*Q(n6+n8,2)
                - 24.*Q(n1,1)*Q(n2+n3+n4+n5+n7,5)*Q(n6+n8,2)+120.*Q(n1+n2+n3+n4+n5+n7,6)*Q(n6+n8,2)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n1+n6+n8,3)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n1+n6+n8,3)
                - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n7,1)*Q(n1+n6+n8,3)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n7,1)*Q(n1+n6+n8,3)
                + 4.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n7,1)*Q(n1+n6+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n7,1)*Q(n1+n6+n8,3)
                + 2.*Q(n3+n4,2)*Q(n2+n5,2)*Q(n7,1)*Q(n1+n6+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n7,1)*Q(n1+n6+n8,3)
                + 2.*Q(n2+n4,2)*Q(n3+n5,2)*Q(n7,1)*Q(n1+n6+n8,3)+4.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n7,1)*Q(n1+n6+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n7,1)*Q(n1+n6+n8,3)+2.*Q(n2+n3,2)*Q(n4+n5,2)*Q(n7,1)*Q(n1+n6+n8,3)
                + 4.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n7,1)*Q(n1+n6+n8,3)+4.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n7,1)*Q(n1+n6+n8,3)
                - 12.*Q(n2+n3+n4+n5,4)*Q(n7,1)*Q(n1+n6+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n2+n7,2)*Q(n1+n6+n8,3)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n2+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n2+n7,2)*Q(n1+n6+n8,3)-4.*Q(n3+n4+n5,3)*Q(n2+n7,2)*Q(n1+n6+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n7,2)*Q(n1+n6+n8,3)+2.*Q(n2+n4,2)*Q(n5,1)*Q(n3+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n4,1)*Q(n2+n5,2)*Q(n3+n7,2)*Q(n1+n6+n8,3)+2.*Q(n2,1)*Q(n4+n5,2)*Q(n3+n7,2)*Q(n1+n6+n8,3)
                - 4.*Q(n2+n4+n5,3)*Q(n3+n7,2)*Q(n1+n6+n8,3)+4.*Q(n4,1)*Q(n5,1)*Q(n2+n3+n7,3)*Q(n1+n6+n8,3)
                - 4.*Q(n4+n5,2)*Q(n2+n3+n7,3)*Q(n1+n6+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n4+n7,2)*Q(n1+n6+n8,3)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n4+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n4+n7,2)*Q(n1+n6+n8,3)-4.*Q(n2+n3+n5,3)*Q(n4+n7,2)*Q(n1+n6+n8,3)
                + 4.*Q(n3,1)*Q(n5,1)*Q(n2+n4+n7,3)*Q(n1+n6+n8,3)-4.*Q(n3+n5,2)*Q(n2+n4+n7,3)*Q(n1+n6+n8,3)
                + 4.*Q(n2,1)*Q(n5,1)*Q(n3+n4+n7,3)*Q(n1+n6+n8,3)-4.*Q(n2+n5,2)*Q(n3+n4+n7,3)*Q(n1+n6+n8,3)
                - 12.*Q(n5,1)*Q(n2+n3+n4+n7,4)*Q(n1+n6+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n5+n7,2)*Q(n1+n6+n8,3)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n5+n7,2)*Q(n1+n6+n8,3)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n5+n7,2)*Q(n1+n6+n8,3)-4.*Q(n2+n3+n4,3)*Q(n5+n7,2)*Q(n1+n6+n8,3)
                + 4.*Q(n3,1)*Q(n4,1)*Q(n2+n5+n7,3)*Q(n1+n6+n8,3)-4.*Q(n3+n4,2)*Q(n2+n5+n7,3)*Q(n1+n6+n8,3)
                + 4.*Q(n2,1)*Q(n4,1)*Q(n3+n5+n7,3)*Q(n1+n6+n8,3)-4.*Q(n2+n4,2)*Q(n3+n5+n7,3)*Q(n1+n6+n8,3)
                - 12.*Q(n4,1)*Q(n2+n3+n5+n7,4)*Q(n1+n6+n8,3)+4.*Q(n2,1)*Q(n3,1)*Q(n4+n5+n7,3)*Q(n1+n6+n8,3)
                - 4.*Q(n2+n3,2)*Q(n4+n5+n7,3)*Q(n1+n6+n8,3)-12.*Q(n3,1)*Q(n2+n4+n5+n7,4)*Q(n1+n6+n8,3)
                - 12.*Q(n2,1)*Q(n3+n4+n5+n7,4)*Q(n1+n6+n8,3)+48.*Q(n2+n3+n4+n5+n7,5)*Q(n1+n6+n8,3)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n2+n6+n8,3)-2.*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n2+n6+n8,3)
                - 2.*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n7,1)*Q(n2+n6+n8,3)-2.*Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n7,1)*Q(n2+n6+n8,3)
                + 4.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n7,1)*Q(n2+n6+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n7,1)*Q(n2+n6+n8,3)
                + 2.*Q(n3+n4,2)*Q(n1+n5,2)*Q(n7,1)*Q(n2+n6+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n7,1)*Q(n2+n6+n8,3)
                + 2.*Q(n1+n4,2)*Q(n3+n5,2)*Q(n7,1)*Q(n2+n6+n8,3)+4.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n7,1)*Q(n2+n6+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n7,1)*Q(n2+n6+n8,3)+2.*Q(n1+n3,2)*Q(n4+n5,2)*Q(n7,1)*Q(n2+n6+n8,3)
                + 4.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n7,1)*Q(n2+n6+n8,3)+4.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n7,1)*Q(n2+n6+n8,3)
                - 12.*Q(n1+n3+n4+n5,4)*Q(n7,1)*Q(n2+n6+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n7,2)*Q(n2+n6+n8,3)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n7,2)*Q(n2+n6+n8,3)-4.*Q(n3+n4+n5,3)*Q(n1+n7,2)*Q(n2+n6+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n3+n7,2)*Q(n2+n6+n8,3)+2.*Q(n1+n4,2)*Q(n5,1)*Q(n3+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n4,1)*Q(n1+n5,2)*Q(n3+n7,2)*Q(n2+n6+n8,3)+2.*Q(n1,1)*Q(n4+n5,2)*Q(n3+n7,2)*Q(n2+n6+n8,3)
                - 4.*Q(n1+n4+n5,3)*Q(n3+n7,2)*Q(n2+n6+n8,3)+4.*Q(n4,1)*Q(n5,1)*Q(n1+n3+n7,3)*Q(n2+n6+n8,3)
                - 4.*Q(n4+n5,2)*Q(n1+n3+n7,3)*Q(n2+n6+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n4+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n1+n3,2)*Q(n5,1)*Q(n4+n7,2)*Q(n2+n6+n8,3)+2.*Q(n3,1)*Q(n1+n5,2)*Q(n4+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n1,1)*Q(n3+n5,2)*Q(n4+n7,2)*Q(n2+n6+n8,3)-4.*Q(n1+n3+n5,3)*Q(n4+n7,2)*Q(n2+n6+n8,3)
                + 4.*Q(n3,1)*Q(n5,1)*Q(n1+n4+n7,3)*Q(n2+n6+n8,3)-4.*Q(n3+n5,2)*Q(n1+n4+n7,3)*Q(n2+n6+n8,3)
                + 4.*Q(n1,1)*Q(n5,1)*Q(n3+n4+n7,3)*Q(n2+n6+n8,3)-4.*Q(n1+n5,2)*Q(n3+n4+n7,3)*Q(n2+n6+n8,3)
                - 12.*Q(n5,1)*Q(n1+n3+n4+n7,4)*Q(n2+n6+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n1+n3,2)*Q(n4,1)*Q(n5+n7,2)*Q(n2+n6+n8,3)+2.*Q(n3,1)*Q(n1+n4,2)*Q(n5+n7,2)*Q(n2+n6+n8,3)
                + 2.*Q(n1,1)*Q(n3+n4,2)*Q(n5+n7,2)*Q(n2+n6+n8,3)-4.*Q(n1+n3+n4,3)*Q(n5+n7,2)*Q(n2+n6+n8,3)
                + 4.*Q(n3,1)*Q(n4,1)*Q(n1+n5+n7,3)*Q(n2+n6+n8,3)-4.*Q(n3+n4,2)*Q(n1+n5+n7,3)*Q(n2+n6+n8,3)
                + 4.*Q(n1,1)*Q(n4,1)*Q(n3+n5+n7,3)*Q(n2+n6+n8,3)-4.*Q(n1+n4,2)*Q(n3+n5+n7,3)*Q(n2+n6+n8,3)
                - 12.*Q(n4,1)*Q(n1+n3+n5+n7,4)*Q(n2+n6+n8,3)+4.*Q(n1,1)*Q(n3,1)*Q(n4+n5+n7,3)*Q(n2+n6+n8,3)
                - 4.*Q(n1+n3,2)*Q(n4+n5+n7,3)*Q(n2+n6+n8,3)-12.*Q(n3,1)*Q(n1+n4+n5+n7,4)*Q(n2+n6+n8,3)
                - 12.*Q(n1,1)*Q(n3+n4+n5+n7,4)*Q(n2+n6+n8,3)+48.*Q(n1+n3+n4+n5+n7,5)*Q(n2+n6+n8,3)
                - 6.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n1+n2+n6+n8,4)+6.*Q(n3+n4,2)*Q(n5,1)*Q(n7,1)*Q(n1+n2+n6+n8,4)
                + 6.*Q(n4,1)*Q(n3+n5,2)*Q(n7,1)*Q(n1+n2+n6+n8,4)+6.*Q(n3,1)*Q(n4+n5,2)*Q(n7,1)*Q(n1+n2+n6+n8,4)
                - 12.*Q(n3+n4+n5,3)*Q(n7,1)*Q(n1+n2+n6+n8,4)+6.*Q(n4,1)*Q(n5,1)*Q(n3+n7,2)*Q(n1+n2+n6+n8,4)
                - 6.*Q(n4+n5,2)*Q(n3+n7,2)*Q(n1+n2+n6+n8,4)+6.*Q(n3,1)*Q(n5,1)*Q(n4+n7,2)*Q(n1+n2+n6+n8,4)
                - 6.*Q(n3+n5,2)*Q(n4+n7,2)*Q(n1+n2+n6+n8,4)-12.*Q(n5,1)*Q(n3+n4+n7,3)*Q(n1+n2+n6+n8,4)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n5+n7,2)*Q(n1+n2+n6+n8,4)-6.*Q(n3+n4,2)*Q(n5+n7,2)*Q(n1+n2+n6+n8,4)
                - 12.*Q(n4,1)*Q(n3+n5+n7,3)*Q(n1+n2+n6+n8,4)-12.*Q(n3,1)*Q(n4+n5+n7,3)*Q(n1+n2+n6+n8,4)
                + 36.*Q(n3+n4+n5+n7,4)*Q(n1+n2+n6+n8,4)+2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n3+n6+n8,3)
                - 2.*Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n3+n6+n8,3)-2.*Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n7,1)*Q(n3+n6+n8,3)
                - 2.*Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n7,1)*Q(n3+n6+n8,3)+4.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n7,1)*Q(n3+n6+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n7,1)*Q(n3+n6+n8,3)+2.*Q(n2+n4,2)*Q(n1+n5,2)*Q(n7,1)*Q(n3+n6+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n7,1)*Q(n3+n6+n8,3)+2.*Q(n1+n4,2)*Q(n2+n5,2)*Q(n7,1)*Q(n3+n6+n8,3)
                + 4.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n7,1)*Q(n3+n6+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n7,1)*Q(n3+n6+n8,3)
                + 2.*Q(n1+n2,2)*Q(n4+n5,2)*Q(n7,1)*Q(n3+n6+n8,3)+4.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n7,1)*Q(n3+n6+n8,3)
                + 4.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n7,1)*Q(n3+n6+n8,3)-12.*Q(n1+n2+n4+n5,4)*Q(n7,1)*Q(n3+n6+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n7,2)*Q(n3+n6+n8,3)+2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n7,2)*Q(n3+n6+n8,3)
                + 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n7,2)*Q(n3+n6+n8,3)+2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n7,2)*Q(n3+n6+n8,3)
                - 4.*Q(n2+n4+n5,3)*Q(n1+n7,2)*Q(n3+n6+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n7,2)*Q(n3+n6+n8,3)
                + 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n7,2)*Q(n3+n6+n8,3)+2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n7,2)*Q(n3+n6+n8,3)
                + 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n7,2)*Q(n3+n6+n8,3)-4.*Q(n1+n4+n5,3)*Q(n2+n7,2)*Q(n3+n6+n8,3)
                + 4.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n7,3)*Q(n3+n6+n8,3)-4.*Q(n4+n5,2)*Q(n1+n2+n7,3)*Q(n3+n6+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n4+n7,2)*Q(n3+n6+n8,3)+2.*Q(n1+n2,2)*Q(n5,1)*Q(n4+n7,2)*Q(n3+n6+n8,3)
                + 2.*Q(n2,1)*Q(n1+n5,2)*Q(n4+n7,2)*Q(n3+n6+n8,3)+2.*Q(n1,1)*Q(n2+n5,2)*Q(n4+n7,2)*Q(n3+n6+n8,3)
                - 4.*Q(n1+n2+n5,3)*Q(n4+n7,2)*Q(n3+n6+n8,3)+4.*Q(n2,1)*Q(n5,1)*Q(n1+n4+n7,3)*Q(n3+n6+n8,3)
                - 4.*Q(n2+n5,2)*Q(n1+n4+n7,3)*Q(n3+n6+n8,3)+4.*Q(n1,1)*Q(n5,1)*Q(n2+n4+n7,3)*Q(n3+n6+n8,3)
                - 4.*Q(n1+n5,2)*Q(n2+n4+n7,3)*Q(n3+n6+n8,3)-12.*Q(n5,1)*Q(n1+n2+n4+n7,4)*Q(n3+n6+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5+n7,2)*Q(n3+n6+n8,3)+2.*Q(n1+n2,2)*Q(n4,1)*Q(n5+n7,2)*Q(n3+n6+n8,3)
                + 2.*Q(n2,1)*Q(n1+n4,2)*Q(n5+n7,2)*Q(n3+n6+n8,3)+2.*Q(n1,1)*Q(n2+n4,2)*Q(n5+n7,2)*Q(n3+n6+n8,3)
                - 4.*Q(n1+n2+n4,3)*Q(n5+n7,2)*Q(n3+n6+n8,3)+4.*Q(n2,1)*Q(n4,1)*Q(n1+n5+n7,3)*Q(n3+n6+n8,3)
                - 4.*Q(n2+n4,2)*Q(n1+n5+n7,3)*Q(n3+n6+n8,3)+4.*Q(n1,1)*Q(n4,1)*Q(n2+n5+n7,3)*Q(n3+n6+n8,3)
                - 4.*Q(n1+n4,2)*Q(n2+n5+n7,3)*Q(n3+n6+n8,3)-12.*Q(n4,1)*Q(n1+n2+n5+n7,4)*Q(n3+n6+n8,3)
                + 4.*Q(n1,1)*Q(n2,1)*Q(n4+n5+n7,3)*Q(n3+n6+n8,3)-4.*Q(n1+n2,2)*Q(n4+n5+n7,3)*Q(n3+n6+n8,3)
                - 12.*Q(n2,1)*Q(n1+n4+n5+n7,4)*Q(n3+n6+n8,3)-12.*Q(n1,1)*Q(n2+n4+n5+n7,4)*Q(n3+n6+n8,3)
                + 48.*Q(n1+n2+n4+n5+n7,5)*Q(n3+n6+n8,3)-6.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n1+n3+n6+n8,4)
                + 6.*Q(n2+n4,2)*Q(n5,1)*Q(n7,1)*Q(n1+n3+n6+n8,4)+6.*Q(n4,1)*Q(n2+n5,2)*Q(n7,1)*Q(n1+n3+n6+n8,4)
                + 6.*Q(n2,1)*Q(n4+n5,2)*Q(n7,1)*Q(n1+n3+n6+n8,4)-12.*Q(n2+n4+n5,3)*Q(n7,1)*Q(n1+n3+n6+n8,4)
                + 6.*Q(n4,1)*Q(n5,1)*Q(n2+n7,2)*Q(n1+n3+n6+n8,4)-6.*Q(n4+n5,2)*Q(n2+n7,2)*Q(n1+n3+n6+n8,4)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n4+n7,2)*Q(n1+n3+n6+n8,4)-6.*Q(n2+n5,2)*Q(n4+n7,2)*Q(n1+n3+n6+n8,4)
                - 12.*Q(n5,1)*Q(n2+n4+n7,3)*Q(n1+n3+n6+n8,4)+6.*Q(n2,1)*Q(n4,1)*Q(n5+n7,2)*Q(n1+n3+n6+n8,4)
                - 6.*Q(n2+n4,2)*Q(n5+n7,2)*Q(n1+n3+n6+n8,4)-12.*Q(n4,1)*Q(n2+n5+n7,3)*Q(n1+n3+n6+n8,4)
                - 12.*Q(n2,1)*Q(n4+n5+n7,3)*Q(n1+n3+n6+n8,4)+36.*Q(n2+n4+n5+n7,4)*Q(n1+n3+n6+n8,4)
                - 6.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n2+n3+n6+n8,4)+6.*Q(n1+n4,2)*Q(n5,1)*Q(n7,1)*Q(n2+n3+n6+n8,4)
                + 6.*Q(n4,1)*Q(n1+n5,2)*Q(n7,1)*Q(n2+n3+n6+n8,4)+6.*Q(n1,1)*Q(n4+n5,2)*Q(n7,1)*Q(n2+n3+n6+n8,4)
                - 12.*Q(n1+n4+n5,3)*Q(n7,1)*Q(n2+n3+n6+n8,4)+6.*Q(n4,1)*Q(n5,1)*Q(n1+n7,2)*Q(n2+n3+n6+n8,4)
                - 6.*Q(n4+n5,2)*Q(n1+n7,2)*Q(n2+n3+n6+n8,4)+6.*Q(n1,1)*Q(n5,1)*Q(n4+n7,2)*Q(n2+n3+n6+n8,4)
                - 6.*Q(n1+n5,2)*Q(n4+n7,2)*Q(n2+n3+n6+n8,4)-12.*Q(n5,1)*Q(n1+n4+n7,3)*Q(n2+n3+n6+n8,4)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n5+n7,2)*Q(n2+n3+n6+n8,4)-6.*Q(n1+n4,2)*Q(n5+n7,2)*Q(n2+n3+n6+n8,4)
                - 12.*Q(n4,1)*Q(n1+n5+n7,3)*Q(n2+n3+n6+n8,4)-12.*Q(n1,1)*Q(n4+n5+n7,3)*Q(n2+n3+n6+n8,4)
                + 36.*Q(n1+n4+n5+n7,4)*Q(n2+n3+n6+n8,4)+24.*Q(n4,1)*Q(n5,1)*Q(n7,1)*Q(n1+n2+n3+n6+n8,5)
                - 24.*Q(n4+n5,2)*Q(n7,1)*Q(n1+n2+n3+n6+n8,5)-24.*Q(n5,1)*Q(n4+n7,2)*Q(n1+n2+n3+n6+n8,5)
                - 24.*Q(n4,1)*Q(n5+n7,2)*Q(n1+n2+n3+n6+n8,5)+48.*Q(n4+n5+n7,3)*Q(n1+n2+n3+n6+n8,5)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n7,1)*Q(n4+n6+n8,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n7,1)*Q(n4+n6+n8,3);

 return eight;

} // TComplex Eight_3(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)

//==========================================================================================================================

TComplex Eight_4(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)
{
 // Generic eight-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)]>, fourth part.

 TComplex eight = - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n7,1)*Q(n4+n6+n8,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n7,1)*Q(n4+n6+n8,3)
                + 4.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n7,1)*Q(n4+n6+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n7,1)*Q(n4+n6+n8,3)
                + 2.*Q(n2+n3,2)*Q(n1+n5,2)*Q(n7,1)*Q(n4+n6+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n7,1)*Q(n4+n6+n8,3)
                + 2.*Q(n1+n3,2)*Q(n2+n5,2)*Q(n7,1)*Q(n4+n6+n8,3)+4.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n7,1)*Q(n4+n6+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n7,1)*Q(n4+n6+n8,3)+2.*Q(n1+n2,2)*Q(n3+n5,2)*Q(n7,1)*Q(n4+n6+n8,3)
                + 4.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n7,1)*Q(n4+n6+n8,3)+4.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n7,1)*Q(n4+n6+n8,3)
                - 12.*Q(n1+n2+n3+n5,4)*Q(n7,1)*Q(n4+n6+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n7,2)*Q(n4+n6+n8,3)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n7,2)*Q(n4+n6+n8,3)-4.*Q(n2+n3+n5,3)*Q(n1+n7,2)*Q(n4+n6+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n7,2)*Q(n4+n6+n8,3)+2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n7,2)*Q(n4+n6+n8,3)+2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n7,2)*Q(n4+n6+n8,3)
                - 4.*Q(n1+n3+n5,3)*Q(n2+n7,2)*Q(n4+n6+n8,3)+4.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n7,3)*Q(n4+n6+n8,3)
                - 4.*Q(n3+n5,2)*Q(n1+n2+n7,3)*Q(n4+n6+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n7,2)*Q(n4+n6+n8,3)+2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n7,2)*Q(n4+n6+n8,3)-4.*Q(n1+n2+n5,3)*Q(n3+n7,2)*Q(n4+n6+n8,3)
                + 4.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n7,3)*Q(n4+n6+n8,3)-4.*Q(n2+n5,2)*Q(n1+n3+n7,3)*Q(n4+n6+n8,3)
                + 4.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n7,3)*Q(n4+n6+n8,3)-4.*Q(n1+n5,2)*Q(n2+n3+n7,3)*Q(n4+n6+n8,3)
                - 12.*Q(n5,1)*Q(n1+n2+n3+n7,4)*Q(n4+n6+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n5+n7,2)*Q(n4+n6+n8,3)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n5+n7,2)*Q(n4+n6+n8,3)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n5+n7,2)*Q(n4+n6+n8,3)-4.*Q(n1+n2+n3,3)*Q(n5+n7,2)*Q(n4+n6+n8,3)
                + 4.*Q(n2,1)*Q(n3,1)*Q(n1+n5+n7,3)*Q(n4+n6+n8,3)-4.*Q(n2+n3,2)*Q(n1+n5+n7,3)*Q(n4+n6+n8,3)
                + 4.*Q(n1,1)*Q(n3,1)*Q(n2+n5+n7,3)*Q(n4+n6+n8,3)-4.*Q(n1+n3,2)*Q(n2+n5+n7,3)*Q(n4+n6+n8,3)
                - 12.*Q(n3,1)*Q(n1+n2+n5+n7,4)*Q(n4+n6+n8,3)+4.*Q(n1,1)*Q(n2,1)*Q(n3+n5+n7,3)*Q(n4+n6+n8,3)
                - 4.*Q(n1+n2,2)*Q(n3+n5+n7,3)*Q(n4+n6+n8,3)-12.*Q(n2,1)*Q(n1+n3+n5+n7,4)*Q(n4+n6+n8,3)
                - 12.*Q(n1,1)*Q(n2+n3+n5+n7,4)*Q(n4+n6+n8,3)+48.*Q(n1+n2+n3+n5+n7,5)*Q(n4+n6+n8,3)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n7,1)*Q(n1+n4+n6+n8,4)+6.*Q(n2+n3,2)*Q(n5,1)*Q(n7,1)*Q(n1+n4+n6+n8,4)
                + 6.*Q(n3,1)*Q(n2+n5,2)*Q(n7,1)*Q(n1+n4+n6+n8,4)+6.*Q(n2,1)*Q(n3+n5,2)*Q(n7,1)*Q(n1+n4+n6+n8,4)
                - 12.*Q(n2+n3+n5,3)*Q(n7,1)*Q(n1+n4+n6+n8,4)+6.*Q(n3,1)*Q(n5,1)*Q(n2+n7,2)*Q(n1+n4+n6+n8,4)
                - 6.*Q(n3+n5,2)*Q(n2+n7,2)*Q(n1+n4+n6+n8,4)+6.*Q(n2,1)*Q(n5,1)*Q(n3+n7,2)*Q(n1+n4+n6+n8,4)
                - 6.*Q(n2+n5,2)*Q(n3+n7,2)*Q(n1+n4+n6+n8,4)-12.*Q(n5,1)*Q(n2+n3+n7,3)*Q(n1+n4+n6+n8,4)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n5+n7,2)*Q(n1+n4+n6+n8,4)-6.*Q(n2+n3,2)*Q(n5+n7,2)*Q(n1+n4+n6+n8,4)
                - 12.*Q(n3,1)*Q(n2+n5+n7,3)*Q(n1+n4+n6+n8,4)-12.*Q(n2,1)*Q(n3+n5+n7,3)*Q(n1+n4+n6+n8,4)
                + 36.*Q(n2+n3+n5+n7,4)*Q(n1+n4+n6+n8,4)-6.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n7,1)*Q(n2+n4+n6+n8,4)
                + 6.*Q(n1+n3,2)*Q(n5,1)*Q(n7,1)*Q(n2+n4+n6+n8,4)+6.*Q(n3,1)*Q(n1+n5,2)*Q(n7,1)*Q(n2+n4+n6+n8,4)
                + 6.*Q(n1,1)*Q(n3+n5,2)*Q(n7,1)*Q(n2+n4+n6+n8,4)-12.*Q(n1+n3+n5,3)*Q(n7,1)*Q(n2+n4+n6+n8,4)
                + 6.*Q(n3,1)*Q(n5,1)*Q(n1+n7,2)*Q(n2+n4+n6+n8,4)-6.*Q(n3+n5,2)*Q(n1+n7,2)*Q(n2+n4+n6+n8,4)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n3+n7,2)*Q(n2+n4+n6+n8,4)-6.*Q(n1+n5,2)*Q(n3+n7,2)*Q(n2+n4+n6+n8,4)
                - 12.*Q(n5,1)*Q(n1+n3+n7,3)*Q(n2+n4+n6+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n5+n7,2)*Q(n2+n4+n6+n8,4)
                - 6.*Q(n1+n3,2)*Q(n5+n7,2)*Q(n2+n4+n6+n8,4)-12.*Q(n3,1)*Q(n1+n5+n7,3)*Q(n2+n4+n6+n8,4)
                - 12.*Q(n1,1)*Q(n3+n5+n7,3)*Q(n2+n4+n6+n8,4)+36.*Q(n1+n3+n5+n7,4)*Q(n2+n4+n6+n8,4)
                + 24.*Q(n3,1)*Q(n5,1)*Q(n7,1)*Q(n1+n2+n4+n6+n8,5)-24.*Q(n3+n5,2)*Q(n7,1)*Q(n1+n2+n4+n6+n8,5)
                - 24.*Q(n5,1)*Q(n3+n7,2)*Q(n1+n2+n4+n6+n8,5)-24.*Q(n3,1)*Q(n5+n7,2)*Q(n1+n2+n4+n6+n8,5)
                + 48.*Q(n3+n5+n7,3)*Q(n1+n2+n4+n6+n8,5)-6.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n7,1)*Q(n3+n4+n6+n8,4)
                + 6.*Q(n1+n2,2)*Q(n5,1)*Q(n7,1)*Q(n3+n4+n6+n8,4)+6.*Q(n2,1)*Q(n1+n5,2)*Q(n7,1)*Q(n3+n4+n6+n8,4)
                + 6.*Q(n1,1)*Q(n2+n5,2)*Q(n7,1)*Q(n3+n4+n6+n8,4)-12.*Q(n1+n2+n5,3)*Q(n7,1)*Q(n3+n4+n6+n8,4)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n1+n7,2)*Q(n3+n4+n6+n8,4)-6.*Q(n2+n5,2)*Q(n1+n7,2)*Q(n3+n4+n6+n8,4)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n2+n7,2)*Q(n3+n4+n6+n8,4)-6.*Q(n1+n5,2)*Q(n2+n7,2)*Q(n3+n4+n6+n8,4)
                - 12.*Q(n5,1)*Q(n1+n2+n7,3)*Q(n3+n4+n6+n8,4)+6.*Q(n1,1)*Q(n2,1)*Q(n5+n7,2)*Q(n3+n4+n6+n8,4)
                - 6.*Q(n1+n2,2)*Q(n5+n7,2)*Q(n3+n4+n6+n8,4)-12.*Q(n2,1)*Q(n1+n5+n7,3)*Q(n3+n4+n6+n8,4)
                - 12.*Q(n1,1)*Q(n2+n5+n7,3)*Q(n3+n4+n6+n8,4)+36.*Q(n1+n2+n5+n7,4)*Q(n3+n4+n6+n8,4)
                + 24.*Q(n2,1)*Q(n5,1)*Q(n7,1)*Q(n1+n3+n4+n6+n8,5)-24.*Q(n2+n5,2)*Q(n7,1)*Q(n1+n3+n4+n6+n8,5)
                - 24.*Q(n5,1)*Q(n2+n7,2)*Q(n1+n3+n4+n6+n8,5)-24.*Q(n2,1)*Q(n5+n7,2)*Q(n1+n3+n4+n6+n8,5)
                + 48.*Q(n2+n5+n7,3)*Q(n1+n3+n4+n6+n8,5)+24.*Q(n1,1)*Q(n5,1)*Q(n7,1)*Q(n2+n3+n4+n6+n8,5)
                - 24.*Q(n1+n5,2)*Q(n7,1)*Q(n2+n3+n4+n6+n8,5)-24.*Q(n5,1)*Q(n1+n7,2)*Q(n2+n3+n4+n6+n8,5)
                - 24.*Q(n1,1)*Q(n5+n7,2)*Q(n2+n3+n4+n6+n8,5)+48.*Q(n1+n5+n7,3)*Q(n2+n3+n4+n6+n8,5)
                - 120.*Q(n5,1)*Q(n7,1)*Q(n1+n2+n3+n4+n6+n8,6)+120.*Q(n5+n7,2)*Q(n1+n2+n3+n4+n6+n8,6)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n7,1)*Q(n5+n6+n8,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n7,1)*Q(n5+n6+n8,3)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n7,1)*Q(n5+n6+n8,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n7,1)*Q(n5+n6+n8,3)
                + 4.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n7,1)*Q(n5+n6+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n7,1)*Q(n5+n6+n8,3)
                + 2.*Q(n2+n3,2)*Q(n1+n4,2)*Q(n7,1)*Q(n5+n6+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n7,1)*Q(n5+n6+n8,3)
                + 2.*Q(n1+n3,2)*Q(n2+n4,2)*Q(n7,1)*Q(n5+n6+n8,3)+4.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n7,1)*Q(n5+n6+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n7,1)*Q(n5+n6+n8,3)+2.*Q(n1+n2,2)*Q(n3+n4,2)*Q(n7,1)*Q(n5+n6+n8,3)
                + 4.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n7,1)*Q(n5+n6+n8,3)+4.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n7,1)*Q(n5+n6+n8,3)
                - 12.*Q(n1+n2+n3+n4,4)*Q(n7,1)*Q(n5+n6+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n7,2)*Q(n5+n6+n8,3)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n7,2)*Q(n5+n6+n8,3)-4.*Q(n2+n3+n4,3)*Q(n1+n7,2)*Q(n5+n6+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n7,2)*Q(n5+n6+n8,3)+2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n7,2)*Q(n5+n6+n8,3)+2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n7,2)*Q(n5+n6+n8,3)
                - 4.*Q(n1+n3+n4,3)*Q(n2+n7,2)*Q(n5+n6+n8,3)+4.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n7,3)*Q(n5+n6+n8,3)
                - 4.*Q(n3+n4,2)*Q(n1+n2+n7,3)*Q(n5+n6+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n7,2)*Q(n5+n6+n8,3)+2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n7,2)*Q(n5+n6+n8,3)-4.*Q(n1+n2+n4,3)*Q(n3+n7,2)*Q(n5+n6+n8,3)
                + 4.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n7,3)*Q(n5+n6+n8,3)-4.*Q(n2+n4,2)*Q(n1+n3+n7,3)*Q(n5+n6+n8,3)
                + 4.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n7,3)*Q(n5+n6+n8,3)-4.*Q(n1+n4,2)*Q(n2+n3+n7,3)*Q(n5+n6+n8,3)
                - 12.*Q(n4,1)*Q(n1+n2+n3+n7,4)*Q(n5+n6+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n7,2)*Q(n5+n6+n8,3)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n7,2)*Q(n5+n6+n8,3)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n7,2)*Q(n5+n6+n8,3)-4.*Q(n1+n2+n3,3)*Q(n4+n7,2)*Q(n5+n6+n8,3)
                + 4.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n7,3)*Q(n5+n6+n8,3)-4.*Q(n2+n3,2)*Q(n1+n4+n7,3)*Q(n5+n6+n8,3)
                + 4.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n7,3)*Q(n5+n6+n8,3)-4.*Q(n1+n3,2)*Q(n2+n4+n7,3)*Q(n5+n6+n8,3)
                - 12.*Q(n3,1)*Q(n1+n2+n4+n7,4)*Q(n5+n6+n8,3)+4.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n7,3)*Q(n5+n6+n8,3)
                - 4.*Q(n1+n2,2)*Q(n3+n4+n7,3)*Q(n5+n6+n8,3)-12.*Q(n2,1)*Q(n1+n3+n4+n7,4)*Q(n5+n6+n8,3)
                - 12.*Q(n1,1)*Q(n2+n3+n4+n7,4)*Q(n5+n6+n8,3)+48.*Q(n1+n2+n3+n4+n7,5)*Q(n5+n6+n8,3)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n7,1)*Q(n1+n5+n6+n8,4)+6.*Q(n2+n3,2)*Q(n4,1)*Q(n7,1)*Q(n1+n5+n6+n8,4)
                + 6.*Q(n3,1)*Q(n2+n4,2)*Q(n7,1)*Q(n1+n5+n6+n8,4)+6.*Q(n2,1)*Q(n3+n4,2)*Q(n7,1)*Q(n1+n5+n6+n8,4)
                - 12.*Q(n2+n3+n4,3)*Q(n7,1)*Q(n1+n5+n6+n8,4)+6.*Q(n3,1)*Q(n4,1)*Q(n2+n7,2)*Q(n1+n5+n6+n8,4)
                - 6.*Q(n3+n4,2)*Q(n2+n7,2)*Q(n1+n5+n6+n8,4)+6.*Q(n2,1)*Q(n4,1)*Q(n3+n7,2)*Q(n1+n5+n6+n8,4)
                - 6.*Q(n2+n4,2)*Q(n3+n7,2)*Q(n1+n5+n6+n8,4)-12.*Q(n4,1)*Q(n2+n3+n7,3)*Q(n1+n5+n6+n8,4)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n4+n7,2)*Q(n1+n5+n6+n8,4)-6.*Q(n2+n3,2)*Q(n4+n7,2)*Q(n1+n5+n6+n8,4)
                - 12.*Q(n3,1)*Q(n2+n4+n7,3)*Q(n1+n5+n6+n8,4)-12.*Q(n2,1)*Q(n3+n4+n7,3)*Q(n1+n5+n6+n8,4)
                + 36.*Q(n2+n3+n4+n7,4)*Q(n1+n5+n6+n8,4)-6.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n7,1)*Q(n2+n5+n6+n8,4)
                + 6.*Q(n1+n3,2)*Q(n4,1)*Q(n7,1)*Q(n2+n5+n6+n8,4)+6.*Q(n3,1)*Q(n1+n4,2)*Q(n7,1)*Q(n2+n5+n6+n8,4)
                + 6.*Q(n1,1)*Q(n3+n4,2)*Q(n7,1)*Q(n2+n5+n6+n8,4)-12.*Q(n1+n3+n4,3)*Q(n7,1)*Q(n2+n5+n6+n8,4)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n1+n7,2)*Q(n2+n5+n6+n8,4)-6.*Q(n3+n4,2)*Q(n1+n7,2)*Q(n2+n5+n6+n8,4)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n3+n7,2)*Q(n2+n5+n6+n8,4)-6.*Q(n1+n4,2)*Q(n3+n7,2)*Q(n2+n5+n6+n8,4)
                - 12.*Q(n4,1)*Q(n1+n3+n7,3)*Q(n2+n5+n6+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n4+n7,2)*Q(n2+n5+n6+n8,4)
                - 6.*Q(n1+n3,2)*Q(n4+n7,2)*Q(n2+n5+n6+n8,4)-12.*Q(n3,1)*Q(n1+n4+n7,3)*Q(n2+n5+n6+n8,4)
                - 12.*Q(n1,1)*Q(n3+n4+n7,3)*Q(n2+n5+n6+n8,4)+36.*Q(n1+n3+n4+n7,4)*Q(n2+n5+n6+n8,4)
                + 24.*Q(n3,1)*Q(n4,1)*Q(n7,1)*Q(n1+n2+n5+n6+n8,5)-24.*Q(n3+n4,2)*Q(n7,1)*Q(n1+n2+n5+n6+n8,5)
                - 24.*Q(n4,1)*Q(n3+n7,2)*Q(n1+n2+n5+n6+n8,5)-24.*Q(n3,1)*Q(n4+n7,2)*Q(n1+n2+n5+n6+n8,5)
                + 48.*Q(n3+n4+n7,3)*Q(n1+n2+n5+n6+n8,5)-6.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n7,1)*Q(n3+n5+n6+n8,4)
                + 6.*Q(n1+n2,2)*Q(n4,1)*Q(n7,1)*Q(n3+n5+n6+n8,4)+6.*Q(n2,1)*Q(n1+n4,2)*Q(n7,1)*Q(n3+n5+n6+n8,4)
                + 6.*Q(n1,1)*Q(n2+n4,2)*Q(n7,1)*Q(n3+n5+n6+n8,4)-12.*Q(n1+n2+n4,3)*Q(n7,1)*Q(n3+n5+n6+n8,4)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n1+n7,2)*Q(n3+n5+n6+n8,4)-6.*Q(n2+n4,2)*Q(n1+n7,2)*Q(n3+n5+n6+n8,4)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n2+n7,2)*Q(n3+n5+n6+n8,4)-6.*Q(n1+n4,2)*Q(n2+n7,2)*Q(n3+n5+n6+n8,4)
                - 12.*Q(n4,1)*Q(n1+n2+n7,3)*Q(n3+n5+n6+n8,4)+6.*Q(n1,1)*Q(n2,1)*Q(n4+n7,2)*Q(n3+n5+n6+n8,4)
                - 6.*Q(n1+n2,2)*Q(n4+n7,2)*Q(n3+n5+n6+n8,4)-12.*Q(n2,1)*Q(n1+n4+n7,3)*Q(n3+n5+n6+n8,4)
                - 12.*Q(n1,1)*Q(n2+n4+n7,3)*Q(n3+n5+n6+n8,4)+36.*Q(n1+n2+n4+n7,4)*Q(n3+n5+n6+n8,4)
                + 24.*Q(n2,1)*Q(n4,1)*Q(n7,1)*Q(n1+n3+n5+n6+n8,5)-24.*Q(n2+n4,2)*Q(n7,1)*Q(n1+n3+n5+n6+n8,5)
                - 24.*Q(n4,1)*Q(n2+n7,2)*Q(n1+n3+n5+n6+n8,5)-24.*Q(n2,1)*Q(n4+n7,2)*Q(n1+n3+n5+n6+n8,5)
                + 48.*Q(n2+n4+n7,3)*Q(n1+n3+n5+n6+n8,5)+24.*Q(n1,1)*Q(n4,1)*Q(n7,1)*Q(n2+n3+n5+n6+n8,5)
                - 24.*Q(n1+n4,2)*Q(n7,1)*Q(n2+n3+n5+n6+n8,5)-24.*Q(n4,1)*Q(n1+n7,2)*Q(n2+n3+n5+n6+n8,5)
                - 24.*Q(n1,1)*Q(n4+n7,2)*Q(n2+n3+n5+n6+n8,5)+48.*Q(n1+n4+n7,3)*Q(n2+n3+n5+n6+n8,5)
                - 120.*Q(n4,1)*Q(n7,1)*Q(n1+n2+n3+n5+n6+n8,6)+120.*Q(n4+n7,2)*Q(n1+n2+n3+n5+n6+n8,6)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n7,1)*Q(n4+n5+n6+n8,4)+6.*Q(n1+n2,2)*Q(n3,1)*Q(n7,1)*Q(n4+n5+n6+n8,4)
                + 6.*Q(n2,1)*Q(n1+n3,2)*Q(n7,1)*Q(n4+n5+n6+n8,4)+6.*Q(n1,1)*Q(n2+n3,2)*Q(n7,1)*Q(n4+n5+n6+n8,4)
                - 12.*Q(n1+n2+n3,3)*Q(n7,1)*Q(n4+n5+n6+n8,4)+6.*Q(n2,1)*Q(n3,1)*Q(n1+n7,2)*Q(n4+n5+n6+n8,4)
                - 6.*Q(n2+n3,2)*Q(n1+n7,2)*Q(n4+n5+n6+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n2+n7,2)*Q(n4+n5+n6+n8,4)
                - 6.*Q(n1+n3,2)*Q(n2+n7,2)*Q(n4+n5+n6+n8,4)-12.*Q(n3,1)*Q(n1+n2+n7,3)*Q(n4+n5+n6+n8,4)
                + 6.*Q(n1,1)*Q(n2,1)*Q(n3+n7,2)*Q(n4+n5+n6+n8,4)-6.*Q(n1+n2,2)*Q(n3+n7,2)*Q(n4+n5+n6+n8,4)
                - 12.*Q(n2,1)*Q(n1+n3+n7,3)*Q(n4+n5+n6+n8,4)-12.*Q(n1,1)*Q(n2+n3+n7,3)*Q(n4+n5+n6+n8,4)
                + 36.*Q(n1+n2+n3+n7,4)*Q(n4+n5+n6+n8,4)+24.*Q(n2,1)*Q(n3,1)*Q(n7,1)*Q(n1+n4+n5+n6+n8,5)
                - 24.*Q(n2+n3,2)*Q(n7,1)*Q(n1+n4+n5+n6+n8,5)-24.*Q(n3,1)*Q(n2+n7,2)*Q(n1+n4+n5+n6+n8,5)
                - 24.*Q(n2,1)*Q(n3+n7,2)*Q(n1+n4+n5+n6+n8,5)+48.*Q(n2+n3+n7,3)*Q(n1+n4+n5+n6+n8,5)
                + 24.*Q(n1,1)*Q(n3,1)*Q(n7,1)*Q(n2+n4+n5+n6+n8,5)-24.*Q(n1+n3,2)*Q(n7,1)*Q(n2+n4+n5+n6+n8,5)
                - 24.*Q(n3,1)*Q(n1+n7,2)*Q(n2+n4+n5+n6+n8,5)-24.*Q(n1,1)*Q(n3+n7,2)*Q(n2+n4+n5+n6+n8,5)
                + 48.*Q(n1+n3+n7,3)*Q(n2+n4+n5+n6+n8,5)-120.*Q(n3,1)*Q(n7,1)*Q(n1+n2+n4+n5+n6+n8,6)
                + 120.*Q(n3+n7,2)*Q(n1+n2+n4+n5+n6+n8,6)+24.*Q(n1,1)*Q(n2,1)*Q(n7,1)*Q(n3+n4+n5+n6+n8,5)
                - 24.*Q(n1+n2,2)*Q(n7,1)*Q(n3+n4+n5+n6+n8,5)-24.*Q(n2,1)*Q(n1+n7,2)*Q(n3+n4+n5+n6+n8,5)
                - 24.*Q(n1,1)*Q(n2+n7,2)*Q(n3+n4+n5+n6+n8,5)+48.*Q(n1+n2+n7,3)*Q(n3+n4+n5+n6+n8,5)
                - 120.*Q(n2,1)*Q(n7,1)*Q(n1+n3+n4+n5+n6+n8,6)+120.*Q(n2+n7,2)*Q(n1+n3+n4+n5+n6+n8,6)
                - 120.*Q(n1,1)*Q(n7,1)*Q(n2+n3+n4+n5+n6+n8,6)+120.*Q(n1+n7,2)*Q(n2+n3+n4+n5+n6+n8,6)
                + 720.*Q(n7,1)*Q(n1+n2+n3+n4+n5+n6+n8,7)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)+6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6,1)*Q(n7+n8,2)
                + Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n7+n8,2)
                - Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6,1)*Q(n7+n8,2)+Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7+n8,2)
                - Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7+n8,2)
                - Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n7+n8,2)+2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6,1)*Q(n7+n8,2)
                - 2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7+n8,2)+2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n7+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n7+n8,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6,1)*Q(n7+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n7+n8,2)-2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n7+n8,2)+6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n7+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n7+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6,1)*Q(n7+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n7+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7+n8,2)
                + 2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n7+n8,2)+6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n7+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7+n8,2)+2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n7+n8,2)
                + 6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n7+n8,2)+6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n7+n8,2)
                - 24.*Q(n1+n2+n3+n4+n5,5)*Q(n6,1)*Q(n7+n8,2)+Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7+n8,2)
                - Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n7+n8,2)-Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7+n8,2)
                - Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n7+n8,2)+2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6,2)*Q(n7+n8,2)
                - Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7+n8,2)+Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n7+n8,2)
                - Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7+n8,2)+Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n7+n8,2)
                + 2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n7+n8,2)-Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7+n8,2)
                + Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n7+n8,2)+2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n7+n8,2)-6.*Q(n2+n3+n4+n5,4)*Q(n1+n6,2)*Q(n7+n8,2)
                + Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7+n8,2)-Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n7+n8,2)
                - Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n7+n8,2)
                + 2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6,2)*Q(n7+n8,2)-Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7+n8,2)
                + Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7+n8,2)
                + Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n7+n8,2)+2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n7+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7+n8,2)+Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n7+n8,2)
                + 2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n7+n8,2)+2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n7+n8,2)
                - 6.*Q(n1+n3+n4+n5,4)*Q(n2+n6,2)*Q(n7+n8,2)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7+n8,2)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n7+n8,2)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n7+n8,2)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n7+n8,2)-4.*Q(n3+n4+n5,3)*Q(n1+n2+n6,3)*Q(n7+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7+n8,2)-Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n7+n8,2)
                - Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n7+n8,2)
                + 2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6,2)*Q(n7+n8,2)-Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7+n8,2)
                + Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7+n8,2)
                + Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n7+n8,2)+2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n7+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7+n8,2)+Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n7+n8,2)+2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n7+n8,2)
                - 6.*Q(n1+n2+n4+n5,4)*Q(n3+n6,2)*Q(n7+n8,2)-2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7+n8,2)
                + 2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n7+n8,2)+2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n7+n8,2)-4.*Q(n2+n4+n5,3)*Q(n1+n3+n6,3)*Q(n7+n8,2)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7+n8,2)+2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n7+n8,2)
                + 2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n7+n8,2)+2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n7+n8,2)
                - 4.*Q(n1+n4+n5,3)*Q(n2+n3+n6,3)*Q(n7+n8,2)+6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n7+n8,2)
                - 6.*Q(n4+n5,2)*Q(n1+n2+n3+n6,4)*Q(n7+n8,2)+Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7+n8,2)
                - Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n7+n8,2)-Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7+n8,2)
                - Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n7+n8,2)+2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6,2)*Q(n7+n8,2)
                - Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7+n8,2)+Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n7+n8,2)
                - Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7+n8,2)+Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n7+n8,2)
                + 2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7+n8,2)
                + Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n7+n8,2)+2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n7+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n7+n8,2)-6.*Q(n1+n2+n3+n5,4)*Q(n4+n6,2)*Q(n7+n8,2)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7+n8,2)+2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n7+n8,2)
                + 2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n7+n8,2)+2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n7+n8,2)
                - 4.*Q(n2+n3+n5,3)*Q(n1+n4+n6,3)*Q(n7+n8,2)-2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7+n8,2)
                + 2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n7+n8,2)+2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n7+n8,2)
                + 2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n7+n8,2)-4.*Q(n1+n3+n5,3)*Q(n2+n4+n6,3)*Q(n7+n8,2)
                + 6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n7+n8,2)-6.*Q(n3+n5,2)*Q(n1+n2+n4+n6,4)*Q(n7+n8,2)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7+n8,2)+2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n7+n8,2)+2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n7+n8,2)
                - 4.*Q(n1+n2+n5,3)*Q(n3+n4+n6,3)*Q(n7+n8,2)+6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n7+n8,2)
                - 6.*Q(n2+n5,2)*Q(n1+n3+n4+n6,4)*Q(n7+n8,2)+6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n7+n8,2)
                - 6.*Q(n1+n5,2)*Q(n2+n3+n4+n6,4)*Q(n7+n8,2)-24.*Q(n5,1)*Q(n1+n2+n3+n4+n6,5)*Q(n7+n8,2)
                + Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7+n8,2)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n7+n8,2)
                - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n7+n8,2)
                + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6,2)*Q(n7+n8,2)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7+n8,2)
                + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n7+n8,2)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7+n8,2)
                + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n7+n8,2)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n7+n8,2)
                - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7+n8,2)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n7+n8,2)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n7+n8,2)
                - 6.*Q(n1+n2+n3+n4,4)*Q(n5+n6,2)*Q(n7+n8,2)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n7+n8,2)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n7+n8,2)-4.*Q(n2+n3+n4,3)*Q(n1+n5+n6,3)*Q(n7+n8,2)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7+n8,2)+2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n7+n8,2)+2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n7+n8,2)
                - 4.*Q(n1+n3+n4,3)*Q(n2+n5+n6,3)*Q(n7+n8,2)+6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n7+n8,2)
                - 6.*Q(n3+n4,2)*Q(n1+n2+n5+n6,4)*Q(n7+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n7+n8,2)+2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n7+n8,2)-4.*Q(n1+n2+n4,3)*Q(n3+n5+n6,3)*Q(n7+n8,2)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n7+n8,2)-6.*Q(n2+n4,2)*Q(n1+n3+n5+n6,4)*Q(n7+n8,2)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n7+n8,2)-6.*Q(n1+n4,2)*Q(n2+n3+n5+n6,4)*Q(n7+n8,2)
                - 24.*Q(n4,1)*Q(n1+n2+n3+n5+n6,5)*Q(n7+n8,2)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n7+n8,2)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n7+n8,2)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n7+n8,2)-4.*Q(n1+n2+n3,3)*Q(n4+n5+n6,3)*Q(n7+n8,2)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n7+n8,2)-6.*Q(n2+n3,2)*Q(n1+n4+n5+n6,4)*Q(n7+n8,2)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n7+n8,2)-6.*Q(n1+n3,2)*Q(n2+n4+n5+n6,4)*Q(n7+n8,2)
                - 24.*Q(n3,1)*Q(n1+n2+n4+n5+n6,5)*Q(n7+n8,2)+6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n7+n8,2)
                - 6.*Q(n1+n2,2)*Q(n3+n4+n5+n6,4)*Q(n7+n8,2)-24.*Q(n2,1)*Q(n1+n3+n4+n5+n6,5)*Q(n7+n8,2)
                - 24.*Q(n1,1)*Q(n2+n3+n4+n5+n6,5)*Q(n7+n8,2)+120.*Q(n1+n2+n3+n4+n5+n6,6)*Q(n7+n8,2)
                + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7+n8,3)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n7+n8,3)
                - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7+n8,3)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n7+n8,3)
                + 4.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n1+n7+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7+n8,3)
                + 2.*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n7+n8,3)-2.*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7+n8,3)
                + 2.*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n7+n8,3)+4.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n7+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7+n8,3)+2.*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n7+n8,3)
                + 4.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n7+n8,3)+4.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n7+n8,3)
                - 12.*Q(n2+n3+n4+n5,4)*Q(n6,1)*Q(n1+n7+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n7+n8,3)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n7+n8,3)-4.*Q(n3+n4+n5,3)*Q(n2+n6,2)*Q(n1+n7+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7+n8,3)+2.*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n7+n8,3)+2.*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n7+n8,3)
                - 4.*Q(n2+n4+n5,3)*Q(n3+n6,2)*Q(n1+n7+n8,3)+4.*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n7+n8,3)
                - 4.*Q(n4+n5,2)*Q(n2+n3+n6,3)*Q(n1+n7+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n7+n8,3)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n7+n8,3)-4.*Q(n2+n3+n5,3)*Q(n4+n6,2)*Q(n1+n7+n8,3)
                + 4.*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n7+n8,3)-4.*Q(n3+n5,2)*Q(n2+n4+n6,3)*Q(n1+n7+n8,3)
                + 4.*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n7+n8,3)-4.*Q(n2+n5,2)*Q(n3+n4+n6,3)*Q(n1+n7+n8,3)
                - 12.*Q(n5,1)*Q(n2+n3+n4+n6,4)*Q(n1+n7+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n7+n8,3)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n7+n8,3)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n7+n8,3)-4.*Q(n2+n3+n4,3)*Q(n5+n6,2)*Q(n1+n7+n8,3)
                + 4.*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n7+n8,3)-4.*Q(n3+n4,2)*Q(n2+n5+n6,3)*Q(n1+n7+n8,3)
                + 4.*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n7+n8,3)-4.*Q(n2+n4,2)*Q(n3+n5+n6,3)*Q(n1+n7+n8,3)
                - 12.*Q(n4,1)*Q(n2+n3+n5+n6,4)*Q(n1+n7+n8,3)+4.*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n7+n8,3)
                - 4.*Q(n2+n3,2)*Q(n4+n5+n6,3)*Q(n1+n7+n8,3)-12.*Q(n3,1)*Q(n2+n4+n5+n6,4)*Q(n1+n7+n8,3)
                - 12.*Q(n2,1)*Q(n3+n4+n5+n6,4)*Q(n1+n7+n8,3)+48.*Q(n2+n3+n4+n5+n6,5)*Q(n1+n7+n8,3)
                + 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7+n8,3)-2.*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n7+n8,3)
                - 2.*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7+n8,3)-2.*Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n7+n8,3)
                + 4.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)*Q(n2+n7+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7+n8,3)
                + 2.*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n7+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7+n8,3)
                + 2.*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n7+n8,3)+4.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n7+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7+n8,3)+2.*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n7+n8,3)
                + 4.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n7+n8,3)+4.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n6,1)*Q(n2+n7+n8,3)
                - 12.*Q(n1+n3+n4+n5,4)*Q(n6,1)*Q(n2+n7+n8,3)-2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n7+n8,3)+2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n7+n8,3)-4.*Q(n3+n4+n5,3)*Q(n1+n6,2)*Q(n2+n7+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7+n8,3)+2.*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n7+n8,3)+2.*Q(n1,1)*Q(n4+n5,2)*Q(n3+n6,2)*Q(n2+n7+n8,3)
                - 4.*Q(n1+n4+n5,3)*Q(n3+n6,2)*Q(n2+n7+n8,3)+4.*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n7+n8,3)
                - 4.*Q(n4+n5,2)*Q(n1+n3+n6,3)*Q(n2+n7+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n7+n8,3)+2.*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n1,1)*Q(n3+n5,2)*Q(n4+n6,2)*Q(n2+n7+n8,3)-4.*Q(n1+n3+n5,3)*Q(n4+n6,2)*Q(n2+n7+n8,3)
                + 4.*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n7+n8,3)-4.*Q(n3+n5,2)*Q(n1+n4+n6,3)*Q(n2+n7+n8,3)
                + 4.*Q(n1,1)*Q(n5,1)*Q(n3+n4+n6,3)*Q(n2+n7+n8,3)-4.*Q(n1+n5,2)*Q(n3+n4+n6,3)*Q(n2+n7+n8,3)
                - 12.*Q(n5,1)*Q(n1+n3+n4+n6,4)*Q(n2+n7+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n7+n8,3)+2.*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n7+n8,3)
                + 2.*Q(n1,1)*Q(n3+n4,2)*Q(n5+n6,2)*Q(n2+n7+n8,3)-4.*Q(n1+n3+n4,3)*Q(n5+n6,2)*Q(n2+n7+n8,3)
                + 4.*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n7+n8,3)-4.*Q(n3+n4,2)*Q(n1+n5+n6,3)*Q(n2+n7+n8,3)
                + 4.*Q(n1,1)*Q(n4,1)*Q(n3+n5+n6,3)*Q(n2+n7+n8,3)-4.*Q(n1+n4,2)*Q(n3+n5+n6,3)*Q(n2+n7+n8,3)
                - 12.*Q(n4,1)*Q(n1+n3+n5+n6,4)*Q(n2+n7+n8,3)+4.*Q(n1,1)*Q(n3,1)*Q(n4+n5+n6,3)*Q(n2+n7+n8,3)
                - 4.*Q(n1+n3,2)*Q(n4+n5+n6,3)*Q(n2+n7+n8,3)-12.*Q(n3,1)*Q(n1+n4+n5+n6,4)*Q(n2+n7+n8,3)
                - 12.*Q(n1,1)*Q(n3+n4+n5+n6,4)*Q(n2+n7+n8,3)+48.*Q(n1+n3+n4+n5+n6,5)*Q(n2+n7+n8,3)
                - 6.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7+n8,4)+6.*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n7+n8,4)
                + 6.*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n7+n8,4)+6.*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n7+n8,4)
                - 12.*Q(n3+n4+n5,3)*Q(n6,1)*Q(n1+n2+n7+n8,4)+6.*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n7+n8,4)
                - 6.*Q(n4+n5,2)*Q(n3+n6,2)*Q(n1+n2+n7+n8,4)+6.*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n7+n8,4)
                - 6.*Q(n3+n5,2)*Q(n4+n6,2)*Q(n1+n2+n7+n8,4)-12.*Q(n5,1)*Q(n3+n4+n6,3)*Q(n1+n2+n7+n8,4)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n7+n8,4)-6.*Q(n3+n4,2)*Q(n5+n6,2)*Q(n1+n2+n7+n8,4)
                - 12.*Q(n4,1)*Q(n3+n5+n6,3)*Q(n1+n2+n7+n8,4)-12.*Q(n3,1)*Q(n4+n5+n6,3)*Q(n1+n2+n7+n8,4)
                + 36.*Q(n3+n4+n5+n6,4)*Q(n1+n2+n7+n8,4)+2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7+n8,3)
                - 2.*Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n3+n7+n8,3)-2.*Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n3+n7+n8,3)+4.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)*Q(n3+n7+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7+n8,3)+2.*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n7+n8,3)
                - 2.*Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7+n8,3)+2.*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n7+n8,3)
                + 4.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n7+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7+n8,3)
                + 2.*Q(n1+n2,2)*Q(n4+n5,2)*Q(n6,1)*Q(n3+n7+n8,3)+4.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n6,1)*Q(n3+n7+n8,3)
                + 4.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n6,1)*Q(n3+n7+n8,3)-12.*Q(n1+n2+n4+n5,4)*Q(n6,1)*Q(n3+n7+n8,3)
                - 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7+n8,3)+2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n7+n8,3)
                + 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n7+n8,3)+2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n6,2)*Q(n3+n7+n8,3)
                - 4.*Q(n2+n4+n5,3)*Q(n1+n6,2)*Q(n3+n7+n8,3)-2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7+n8,3)
                + 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n7+n8,3)+2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n7+n8,3)
                + 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n6,2)*Q(n3+n7+n8,3)-4.*Q(n1+n4+n5,3)*Q(n2+n6,2)*Q(n3+n7+n8,3)
                + 4.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n7+n8,3)-4.*Q(n4+n5,2)*Q(n1+n2+n6,3)*Q(n3+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7+n8,3)+2.*Q(n1+n2,2)*Q(n5,1)*Q(n4+n6,2)*Q(n3+n7+n8,3)
                + 2.*Q(n2,1)*Q(n1+n5,2)*Q(n4+n6,2)*Q(n3+n7+n8,3)+2.*Q(n1,1)*Q(n2+n5,2)*Q(n4+n6,2)*Q(n3+n7+n8,3)
                - 4.*Q(n1+n2+n5,3)*Q(n4+n6,2)*Q(n3+n7+n8,3)+4.*Q(n2,1)*Q(n5,1)*Q(n1+n4+n6,3)*Q(n3+n7+n8,3)
                - 4.*Q(n2+n5,2)*Q(n1+n4+n6,3)*Q(n3+n7+n8,3)+4.*Q(n1,1)*Q(n5,1)*Q(n2+n4+n6,3)*Q(n3+n7+n8,3)
                - 4.*Q(n1+n5,2)*Q(n2+n4+n6,3)*Q(n3+n7+n8,3)-12.*Q(n5,1)*Q(n1+n2+n4+n6,4)*Q(n3+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7+n8,3)+2.*Q(n1+n2,2)*Q(n4,1)*Q(n5+n6,2)*Q(n3+n7+n8,3)
                + 2.*Q(n2,1)*Q(n1+n4,2)*Q(n5+n6,2)*Q(n3+n7+n8,3)+2.*Q(n1,1)*Q(n2+n4,2)*Q(n5+n6,2)*Q(n3+n7+n8,3)
                - 4.*Q(n1+n2+n4,3)*Q(n5+n6,2)*Q(n3+n7+n8,3)+4.*Q(n2,1)*Q(n4,1)*Q(n1+n5+n6,3)*Q(n3+n7+n8,3)
                - 4.*Q(n2+n4,2)*Q(n1+n5+n6,3)*Q(n3+n7+n8,3)+4.*Q(n1,1)*Q(n4,1)*Q(n2+n5+n6,3)*Q(n3+n7+n8,3)
                - 4.*Q(n1+n4,2)*Q(n2+n5+n6,3)*Q(n3+n7+n8,3)-12.*Q(n4,1)*Q(n1+n2+n5+n6,4)*Q(n3+n7+n8,3)
                + 4.*Q(n1,1)*Q(n2,1)*Q(n4+n5+n6,3)*Q(n3+n7+n8,3)-4.*Q(n1+n2,2)*Q(n4+n5+n6,3)*Q(n3+n7+n8,3)
                - 12.*Q(n2,1)*Q(n1+n4+n5+n6,4)*Q(n3+n7+n8,3)-12.*Q(n1,1)*Q(n2+n4+n5+n6,4)*Q(n3+n7+n8,3)
                + 48.*Q(n1+n2+n4+n5+n6,5)*Q(n3+n7+n8,3)-6.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7+n8,4)
                + 6.*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n7+n8,4)+6.*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n7+n8,4)
                + 6.*Q(n2,1)*Q(n4+n5,2)*Q(n6,1)*Q(n1+n3+n7+n8,4)-12.*Q(n2+n4+n5,3)*Q(n6,1)*Q(n1+n3+n7+n8,4)
                + 6.*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n7+n8,4)-6.*Q(n4+n5,2)*Q(n2+n6,2)*Q(n1+n3+n7+n8,4)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n4+n6,2)*Q(n1+n3+n7+n8,4)-6.*Q(n2+n5,2)*Q(n4+n6,2)*Q(n1+n3+n7+n8,4)
                - 12.*Q(n5,1)*Q(n2+n4+n6,3)*Q(n1+n3+n7+n8,4)+6.*Q(n2,1)*Q(n4,1)*Q(n5+n6,2)*Q(n1+n3+n7+n8,4)
                - 6.*Q(n2+n4,2)*Q(n5+n6,2)*Q(n1+n3+n7+n8,4)-12.*Q(n4,1)*Q(n2+n5+n6,3)*Q(n1+n3+n7+n8,4)
                - 12.*Q(n2,1)*Q(n4+n5+n6,3)*Q(n1+n3+n7+n8,4)+36.*Q(n2+n4+n5+n6,4)*Q(n1+n3+n7+n8,4)
                - 6.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7+n8,4)+6.*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n7+n8,4)
                + 6.*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n7+n8,4)+6.*Q(n1,1)*Q(n4+n5,2)*Q(n6,1)*Q(n2+n3+n7+n8,4)
                - 12.*Q(n1+n4+n5,3)*Q(n6,1)*Q(n2+n3+n7+n8,4)+6.*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n7+n8,4)
                - 6.*Q(n4+n5,2)*Q(n1+n6,2)*Q(n2+n3+n7+n8,4)+6.*Q(n1,1)*Q(n5,1)*Q(n4+n6,2)*Q(n2+n3+n7+n8,4)
                - 6.*Q(n1+n5,2)*Q(n4+n6,2)*Q(n2+n3+n7+n8,4)-12.*Q(n5,1)*Q(n1+n4+n6,3)*Q(n2+n3+n7+n8,4)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n5+n6,2)*Q(n2+n3+n7+n8,4)-6.*Q(n1+n4,2)*Q(n5+n6,2)*Q(n2+n3+n7+n8,4)
                - 12.*Q(n4,1)*Q(n1+n5+n6,3)*Q(n2+n3+n7+n8,4)-12.*Q(n1,1)*Q(n4+n5+n6,3)*Q(n2+n3+n7+n8,4)
                + 36.*Q(n1+n4+n5+n6,4)*Q(n2+n3+n7+n8,4)+24.*Q(n4,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n7+n8,5)
                - 24.*Q(n4+n5,2)*Q(n6,1)*Q(n1+n2+n3+n7+n8,5)-24.*Q(n5,1)*Q(n4+n6,2)*Q(n1+n2+n3+n7+n8,5)
                - 24.*Q(n4,1)*Q(n5+n6,2)*Q(n1+n2+n3+n7+n8,5)+48.*Q(n4+n5+n6,3)*Q(n1+n2+n3+n7+n8,5)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7+n8,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n4+n7+n8,3)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7+n8,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n4+n7+n8,3)
                + 4.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n6,1)*Q(n4+n7+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7+n8,3)
                + 2.*Q(n2+n3,2)*Q(n1+n5,2)*Q(n6,1)*Q(n4+n7+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7+n8,3)
                + 2.*Q(n1+n3,2)*Q(n2+n5,2)*Q(n6,1)*Q(n4+n7+n8,3)+4.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n6,1)*Q(n4+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7+n8,3)+2.*Q(n1+n2,2)*Q(n3+n5,2)*Q(n6,1)*Q(n4+n7+n8,3)
                + 4.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n6,1)*Q(n4+n7+n8,3)+4.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n6,1)*Q(n4+n7+n8,3)
                - 12.*Q(n1+n2+n3+n5,4)*Q(n6,1)*Q(n4+n7+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n6,2)*Q(n4+n7+n8,3)+2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n6,2)*Q(n4+n7+n8,3)-4.*Q(n2+n3+n5,3)*Q(n1+n6,2)*Q(n4+n7+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7+n8,3)+2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n6,2)*Q(n4+n7+n8,3)+2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n6,2)*Q(n4+n7+n8,3)
                - 4.*Q(n1+n3+n5,3)*Q(n2+n6,2)*Q(n4+n7+n8,3)+4.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n6,3)*Q(n4+n7+n8,3)
                - 4.*Q(n3+n5,2)*Q(n1+n2+n6,3)*Q(n4+n7+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n6,2)*Q(n4+n7+n8,3)+2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n6,2)*Q(n4+n7+n8,3)-4.*Q(n1+n2+n5,3)*Q(n3+n6,2)*Q(n4+n7+n8,3)
                + 4.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n6,3)*Q(n4+n7+n8,3)-4.*Q(n2+n5,2)*Q(n1+n3+n6,3)*Q(n4+n7+n8,3)
                + 4.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n6,3)*Q(n4+n7+n8,3)-4.*Q(n1+n5,2)*Q(n2+n3+n6,3)*Q(n4+n7+n8,3)
                - 12.*Q(n5,1)*Q(n1+n2+n3+n6,4)*Q(n4+n7+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n5+n6,2)*Q(n4+n7+n8,3)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n5+n6,2)*Q(n4+n7+n8,3)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n5+n6,2)*Q(n4+n7+n8,3)-4.*Q(n1+n2+n3,3)*Q(n5+n6,2)*Q(n4+n7+n8,3)
                + 4.*Q(n2,1)*Q(n3,1)*Q(n1+n5+n6,3)*Q(n4+n7+n8,3)-4.*Q(n2+n3,2)*Q(n1+n5+n6,3)*Q(n4+n7+n8,3)
                + 4.*Q(n1,1)*Q(n3,1)*Q(n2+n5+n6,3)*Q(n4+n7+n8,3)-4.*Q(n1+n3,2)*Q(n2+n5+n6,3)*Q(n4+n7+n8,3)
                - 12.*Q(n3,1)*Q(n1+n2+n5+n6,4)*Q(n4+n7+n8,3)+4.*Q(n1,1)*Q(n2,1)*Q(n3+n5+n6,3)*Q(n4+n7+n8,3)
                - 4.*Q(n1+n2,2)*Q(n3+n5+n6,3)*Q(n4+n7+n8,3)-12.*Q(n2,1)*Q(n1+n3+n5+n6,4)*Q(n4+n7+n8,3)
                - 12.*Q(n1,1)*Q(n2+n3+n5+n6,4)*Q(n4+n7+n8,3)+48.*Q(n1+n2+n3+n5+n6,5)*Q(n4+n7+n8,3)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7+n8,4)+6.*Q(n2+n3,2)*Q(n5,1)*Q(n6,1)*Q(n1+n4+n7+n8,4)
                + 6.*Q(n3,1)*Q(n2+n5,2)*Q(n6,1)*Q(n1+n4+n7+n8,4)+6.*Q(n2,1)*Q(n3+n5,2)*Q(n6,1)*Q(n1+n4+n7+n8,4)
                - 12.*Q(n2+n3+n5,3)*Q(n6,1)*Q(n1+n4+n7+n8,4)+6.*Q(n3,1)*Q(n5,1)*Q(n2+n6,2)*Q(n1+n4+n7+n8,4)
                - 6.*Q(n3+n5,2)*Q(n2+n6,2)*Q(n1+n4+n7+n8,4)+6.*Q(n2,1)*Q(n5,1)*Q(n3+n6,2)*Q(n1+n4+n7+n8,4)
                - 6.*Q(n2+n5,2)*Q(n3+n6,2)*Q(n1+n4+n7+n8,4)-12.*Q(n5,1)*Q(n2+n3+n6,3)*Q(n1+n4+n7+n8,4)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n5+n6,2)*Q(n1+n4+n7+n8,4)-6.*Q(n2+n3,2)*Q(n5+n6,2)*Q(n1+n4+n7+n8,4)
                - 12.*Q(n3,1)*Q(n2+n5+n6,3)*Q(n1+n4+n7+n8,4)-12.*Q(n2,1)*Q(n3+n5+n6,3)*Q(n1+n4+n7+n8,4)
                + 36.*Q(n2+n3+n5+n6,4)*Q(n1+n4+n7+n8,4)-6.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7+n8,4)
                + 6.*Q(n1+n3,2)*Q(n5,1)*Q(n6,1)*Q(n2+n4+n7+n8,4)+6.*Q(n3,1)*Q(n1+n5,2)*Q(n6,1)*Q(n2+n4+n7+n8,4)
                + 6.*Q(n1,1)*Q(n3+n5,2)*Q(n6,1)*Q(n2+n4+n7+n8,4)-12.*Q(n1+n3+n5,3)*Q(n6,1)*Q(n2+n4+n7+n8,4)
                + 6.*Q(n3,1)*Q(n5,1)*Q(n1+n6,2)*Q(n2+n4+n7+n8,4)-6.*Q(n3+n5,2)*Q(n1+n6,2)*Q(n2+n4+n7+n8,4)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n3+n6,2)*Q(n2+n4+n7+n8,4)-6.*Q(n1+n5,2)*Q(n3+n6,2)*Q(n2+n4+n7+n8,4)
                - 12.*Q(n5,1)*Q(n1+n3+n6,3)*Q(n2+n4+n7+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n5+n6,2)*Q(n2+n4+n7+n8,4)
                - 6.*Q(n1+n3,2)*Q(n5+n6,2)*Q(n2+n4+n7+n8,4)-12.*Q(n3,1)*Q(n1+n5+n6,3)*Q(n2+n4+n7+n8,4)
                - 12.*Q(n1,1)*Q(n3+n5+n6,3)*Q(n2+n4+n7+n8,4)+36.*Q(n1+n3+n5+n6,4)*Q(n2+n4+n7+n8,4)
                + 24.*Q(n3,1)*Q(n5,1)*Q(n6,1)*Q(n1+n2+n4+n7+n8,5)-24.*Q(n3+n5,2)*Q(n6,1)*Q(n1+n2+n4+n7+n8,5)
                - 24.*Q(n5,1)*Q(n3+n6,2)*Q(n1+n2+n4+n7+n8,5)-24.*Q(n3,1)*Q(n5+n6,2)*Q(n1+n2+n4+n7+n8,5)
                + 48.*Q(n3+n5+n6,3)*Q(n1+n2+n4+n7+n8,5)-6.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7+n8,4)
                + 6.*Q(n1+n2,2)*Q(n5,1)*Q(n6,1)*Q(n3+n4+n7+n8,4)+6.*Q(n2,1)*Q(n1+n5,2)*Q(n6,1)*Q(n3+n4+n7+n8,4)
                + 6.*Q(n1,1)*Q(n2+n5,2)*Q(n6,1)*Q(n3+n4+n7+n8,4)-12.*Q(n1+n2+n5,3)*Q(n6,1)*Q(n3+n4+n7+n8,4)
                + 6.*Q(n2,1)*Q(n5,1)*Q(n1+n6,2)*Q(n3+n4+n7+n8,4)-6.*Q(n2+n5,2)*Q(n1+n6,2)*Q(n3+n4+n7+n8,4)
                + 6.*Q(n1,1)*Q(n5,1)*Q(n2+n6,2)*Q(n3+n4+n7+n8,4)-6.*Q(n1+n5,2)*Q(n2+n6,2)*Q(n3+n4+n7+n8,4)
                - 12.*Q(n5,1)*Q(n1+n2+n6,3)*Q(n3+n4+n7+n8,4)+6.*Q(n1,1)*Q(n2,1)*Q(n5+n6,2)*Q(n3+n4+n7+n8,4)
                - 6.*Q(n1+n2,2)*Q(n5+n6,2)*Q(n3+n4+n7+n8,4)-12.*Q(n2,1)*Q(n1+n5+n6,3)*Q(n3+n4+n7+n8,4)
                - 12.*Q(n1,1)*Q(n2+n5+n6,3)*Q(n3+n4+n7+n8,4)+36.*Q(n1+n2+n5+n6,4)*Q(n3+n4+n7+n8,4)
                + 24.*Q(n2,1)*Q(n5,1)*Q(n6,1)*Q(n1+n3+n4+n7+n8,5)-24.*Q(n2+n5,2)*Q(n6,1)*Q(n1+n3+n4+n7+n8,5)
                - 24.*Q(n5,1)*Q(n2+n6,2)*Q(n1+n3+n4+n7+n8,5)-24.*Q(n2,1)*Q(n5+n6,2)*Q(n1+n3+n4+n7+n8,5)
                + 48.*Q(n2+n5+n6,3)*Q(n1+n3+n4+n7+n8,5)+24.*Q(n1,1)*Q(n5,1)*Q(n6,1)*Q(n2+n3+n4+n7+n8,5)
                - 24.*Q(n1+n5,2)*Q(n6,1)*Q(n2+n3+n4+n7+n8,5)-24.*Q(n5,1)*Q(n1+n6,2)*Q(n2+n3+n4+n7+n8,5)
                - 24.*Q(n1,1)*Q(n5+n6,2)*Q(n2+n3+n4+n7+n8,5)+48.*Q(n1+n5+n6,3)*Q(n2+n3+n4+n7+n8,5)
                - 120.*Q(n5,1)*Q(n6,1)*Q(n1+n2+n3+n4+n7+n8,6)+120.*Q(n5+n6,2)*Q(n1+n2+n3+n4+n7+n8,6)
                + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7+n8,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n5+n7+n8,3)
                - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7+n8,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n5+n7+n8,3)
                + 4.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n6,1)*Q(n5+n7+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7+n8,3)
                + 2.*Q(n2+n3,2)*Q(n1+n4,2)*Q(n6,1)*Q(n5+n7+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7+n8,3)
                + 2.*Q(n1+n3,2)*Q(n2+n4,2)*Q(n6,1)*Q(n5+n7+n8,3)+4.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n6,1)*Q(n5+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7+n8,3)+2.*Q(n1+n2,2)*Q(n3+n4,2)*Q(n6,1)*Q(n5+n7+n8,3)
                + 4.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n6,1)*Q(n5+n7+n8,3)+4.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n6,1)*Q(n5+n7+n8,3)
                - 12.*Q(n1+n2+n3+n4,4)*Q(n6,1)*Q(n5+n7+n8,3)-2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n6,2)*Q(n5+n7+n8,3)+2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n6,2)*Q(n5+n7+n8,3)-4.*Q(n2+n3+n4,3)*Q(n1+n6,2)*Q(n5+n7+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7+n8,3)+2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n6,2)*Q(n5+n7+n8,3)+2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n6,2)*Q(n5+n7+n8,3)
                - 4.*Q(n1+n3+n4,3)*Q(n2+n6,2)*Q(n5+n7+n8,3)+4.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n6,3)*Q(n5+n7+n8,3)
                - 4.*Q(n3+n4,2)*Q(n1+n2+n6,3)*Q(n5+n7+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n6,2)*Q(n5+n7+n8,3)+2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n6,2)*Q(n5+n7+n8,3)-4.*Q(n1+n2+n4,3)*Q(n3+n6,2)*Q(n5+n7+n8,3)
                + 4.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n6,3)*Q(n5+n7+n8,3)-4.*Q(n2+n4,2)*Q(n1+n3+n6,3)*Q(n5+n7+n8,3)
                + 4.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n6,3)*Q(n5+n7+n8,3)-4.*Q(n1+n4,2)*Q(n2+n3+n6,3)*Q(n5+n7+n8,3)
                - 12.*Q(n4,1)*Q(n1+n2+n3+n6,4)*Q(n5+n7+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n6,2)*Q(n5+n7+n8,3)+2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n6,2)*Q(n5+n7+n8,3)
                + 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n6,2)*Q(n5+n7+n8,3)-4.*Q(n1+n2+n3,3)*Q(n4+n6,2)*Q(n5+n7+n8,3)
                + 4.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n6,3)*Q(n5+n7+n8,3)-4.*Q(n2+n3,2)*Q(n1+n4+n6,3)*Q(n5+n7+n8,3)
                + 4.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n6,3)*Q(n5+n7+n8,3)-4.*Q(n1+n3,2)*Q(n2+n4+n6,3)*Q(n5+n7+n8,3)
                - 12.*Q(n3,1)*Q(n1+n2+n4+n6,4)*Q(n5+n7+n8,3)+4.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n6,3)*Q(n5+n7+n8,3)
                - 4.*Q(n1+n2,2)*Q(n3+n4+n6,3)*Q(n5+n7+n8,3)-12.*Q(n2,1)*Q(n1+n3+n4+n6,4)*Q(n5+n7+n8,3)
                - 12.*Q(n1,1)*Q(n2+n3+n4+n6,4)*Q(n5+n7+n8,3)+48.*Q(n1+n2+n3+n4+n6,5)*Q(n5+n7+n8,3)
                - 6.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7+n8,4)+6.*Q(n2+n3,2)*Q(n4,1)*Q(n6,1)*Q(n1+n5+n7+n8,4)
                + 6.*Q(n3,1)*Q(n2+n4,2)*Q(n6,1)*Q(n1+n5+n7+n8,4)+6.*Q(n2,1)*Q(n3+n4,2)*Q(n6,1)*Q(n1+n5+n7+n8,4)
                - 12.*Q(n2+n3+n4,3)*Q(n6,1)*Q(n1+n5+n7+n8,4)+6.*Q(n3,1)*Q(n4,1)*Q(n2+n6,2)*Q(n1+n5+n7+n8,4)
                - 6.*Q(n3+n4,2)*Q(n2+n6,2)*Q(n1+n5+n7+n8,4)+6.*Q(n2,1)*Q(n4,1)*Q(n3+n6,2)*Q(n1+n5+n7+n8,4)
                - 6.*Q(n2+n4,2)*Q(n3+n6,2)*Q(n1+n5+n7+n8,4)-12.*Q(n4,1)*Q(n2+n3+n6,3)*Q(n1+n5+n7+n8,4)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n4+n6,2)*Q(n1+n5+n7+n8,4)-6.*Q(n2+n3,2)*Q(n4+n6,2)*Q(n1+n5+n7+n8,4)
                - 12.*Q(n3,1)*Q(n2+n4+n6,3)*Q(n1+n5+n7+n8,4)-12.*Q(n2,1)*Q(n3+n4+n6,3)*Q(n1+n5+n7+n8,4)
                + 36.*Q(n2+n3+n4+n6,4)*Q(n1+n5+n7+n8,4)-6.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7+n8,4)
                + 6.*Q(n1+n3,2)*Q(n4,1)*Q(n6,1)*Q(n2+n5+n7+n8,4)+6.*Q(n3,1)*Q(n1+n4,2)*Q(n6,1)*Q(n2+n5+n7+n8,4)
                + 6.*Q(n1,1)*Q(n3+n4,2)*Q(n6,1)*Q(n2+n5+n7+n8,4)-12.*Q(n1+n3+n4,3)*Q(n6,1)*Q(n2+n5+n7+n8,4)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n1+n6,2)*Q(n2+n5+n7+n8,4)-6.*Q(n3+n4,2)*Q(n1+n6,2)*Q(n2+n5+n7+n8,4)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n3+n6,2)*Q(n2+n5+n7+n8,4)-6.*Q(n1+n4,2)*Q(n3+n6,2)*Q(n2+n5+n7+n8,4)
                - 12.*Q(n4,1)*Q(n1+n3+n6,3)*Q(n2+n5+n7+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n4+n6,2)*Q(n2+n5+n7+n8,4)
                - 6.*Q(n1+n3,2)*Q(n4+n6,2)*Q(n2+n5+n7+n8,4)-12.*Q(n3,1)*Q(n1+n4+n6,3)*Q(n2+n5+n7+n8,4)
                - 12.*Q(n1,1)*Q(n3+n4+n6,3)*Q(n2+n5+n7+n8,4)+36.*Q(n1+n3+n4+n6,4)*Q(n2+n5+n7+n8,4)
                + 24.*Q(n3,1)*Q(n4,1)*Q(n6,1)*Q(n1+n2+n5+n7+n8,5)-24.*Q(n3+n4,2)*Q(n6,1)*Q(n1+n2+n5+n7+n8,5)
                - 24.*Q(n4,1)*Q(n3+n6,2)*Q(n1+n2+n5+n7+n8,5)-24.*Q(n3,1)*Q(n4+n6,2)*Q(n1+n2+n5+n7+n8,5)
                + 48.*Q(n3+n4+n6,3)*Q(n1+n2+n5+n7+n8,5)-6.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7+n8,4)
                + 6.*Q(n1+n2,2)*Q(n4,1)*Q(n6,1)*Q(n3+n5+n7+n8,4)+6.*Q(n2,1)*Q(n1+n4,2)*Q(n6,1)*Q(n3+n5+n7+n8,4)
                + 6.*Q(n1,1)*Q(n2+n4,2)*Q(n6,1)*Q(n3+n5+n7+n8,4)-12.*Q(n1+n2+n4,3)*Q(n6,1)*Q(n3+n5+n7+n8,4)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n1+n6,2)*Q(n3+n5+n7+n8,4)-6.*Q(n2+n4,2)*Q(n1+n6,2)*Q(n3+n5+n7+n8,4)
                + 6.*Q(n1,1)*Q(n4,1)*Q(n2+n6,2)*Q(n3+n5+n7+n8,4)-6.*Q(n1+n4,2)*Q(n2+n6,2)*Q(n3+n5+n7+n8,4)
                - 12.*Q(n4,1)*Q(n1+n2+n6,3)*Q(n3+n5+n7+n8,4)+6.*Q(n1,1)*Q(n2,1)*Q(n4+n6,2)*Q(n3+n5+n7+n8,4)
                - 6.*Q(n1+n2,2)*Q(n4+n6,2)*Q(n3+n5+n7+n8,4)-12.*Q(n2,1)*Q(n1+n4+n6,3)*Q(n3+n5+n7+n8,4)
                - 12.*Q(n1,1)*Q(n2+n4+n6,3)*Q(n3+n5+n7+n8,4)+36.*Q(n1+n2+n4+n6,4)*Q(n3+n5+n7+n8,4)
                + 24.*Q(n2,1)*Q(n4,1)*Q(n6,1)*Q(n1+n3+n5+n7+n8,5)-24.*Q(n2+n4,2)*Q(n6,1)*Q(n1+n3+n5+n7+n8,5)
                - 24.*Q(n4,1)*Q(n2+n6,2)*Q(n1+n3+n5+n7+n8,5)-24.*Q(n2,1)*Q(n4+n6,2)*Q(n1+n3+n5+n7+n8,5)
                + 48.*Q(n2+n4+n6,3)*Q(n1+n3+n5+n7+n8,5)+24.*Q(n1,1)*Q(n4,1)*Q(n6,1)*Q(n2+n3+n5+n7+n8,5)
                - 24.*Q(n1+n4,2)*Q(n6,1)*Q(n2+n3+n5+n7+n8,5)-24.*Q(n4,1)*Q(n1+n6,2)*Q(n2+n3+n5+n7+n8,5)
                - 24.*Q(n1,1)*Q(n4+n6,2)*Q(n2+n3+n5+n7+n8,5)+48.*Q(n1+n4+n6,3)*Q(n2+n3+n5+n7+n8,5)
                - 120.*Q(n4,1)*Q(n6,1)*Q(n1+n2+n3+n5+n7+n8,6)+120.*Q(n4+n6,2)*Q(n1+n2+n3+n5+n7+n8,6)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7+n8,4)+6.*Q(n1+n2,2)*Q(n3,1)*Q(n6,1)*Q(n4+n5+n7+n8,4)
                + 6.*Q(n2,1)*Q(n1+n3,2)*Q(n6,1)*Q(n4+n5+n7+n8,4)+6.*Q(n1,1)*Q(n2+n3,2)*Q(n6,1)*Q(n4+n5+n7+n8,4)
                - 12.*Q(n1+n2+n3,3)*Q(n6,1)*Q(n4+n5+n7+n8,4)+6.*Q(n2,1)*Q(n3,1)*Q(n1+n6,2)*Q(n4+n5+n7+n8,4)
                - 6.*Q(n2+n3,2)*Q(n1+n6,2)*Q(n4+n5+n7+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n2+n6,2)*Q(n4+n5+n7+n8,4)
                - 6.*Q(n1+n3,2)*Q(n2+n6,2)*Q(n4+n5+n7+n8,4)-12.*Q(n3,1)*Q(n1+n2+n6,3)*Q(n4+n5+n7+n8,4)
                + 6.*Q(n1,1)*Q(n2,1)*Q(n3+n6,2)*Q(n4+n5+n7+n8,4)-6.*Q(n1+n2,2)*Q(n3+n6,2)*Q(n4+n5+n7+n8,4)
                - 12.*Q(n2,1)*Q(n1+n3+n6,3)*Q(n4+n5+n7+n8,4)-12.*Q(n1,1)*Q(n2+n3+n6,3)*Q(n4+n5+n7+n8,4)
                + 36.*Q(n1+n2+n3+n6,4)*Q(n4+n5+n7+n8,4)+24.*Q(n2,1)*Q(n3,1)*Q(n6,1)*Q(n1+n4+n5+n7+n8,5)
                - 24.*Q(n2+n3,2)*Q(n6,1)*Q(n1+n4+n5+n7+n8,5)-24.*Q(n3,1)*Q(n2+n6,2)*Q(n1+n4+n5+n7+n8,5)
                - 24.*Q(n2,1)*Q(n3+n6,2)*Q(n1+n4+n5+n7+n8,5)+48.*Q(n2+n3+n6,3)*Q(n1+n4+n5+n7+n8,5)
                + 24.*Q(n1,1)*Q(n3,1)*Q(n6,1)*Q(n2+n4+n5+n7+n8,5)-24.*Q(n1+n3,2)*Q(n6,1)*Q(n2+n4+n5+n7+n8,5)
                - 24.*Q(n3,1)*Q(n1+n6,2)*Q(n2+n4+n5+n7+n8,5)-24.*Q(n1,1)*Q(n3+n6,2)*Q(n2+n4+n5+n7+n8,5)
                + 48.*Q(n1+n3+n6,3)*Q(n2+n4+n5+n7+n8,5)-120.*Q(n3,1)*Q(n6,1)*Q(n1+n2+n4+n5+n7+n8,6)
                + 120.*Q(n3+n6,2)*Q(n1+n2+n4+n5+n7+n8,6)+24.*Q(n1,1)*Q(n2,1)*Q(n6,1)*Q(n3+n4+n5+n7+n8,5)
                - 24.*Q(n1+n2,2)*Q(n6,1)*Q(n3+n4+n5+n7+n8,5)-24.*Q(n2,1)*Q(n1+n6,2)*Q(n3+n4+n5+n7+n8,5)
                - 24.*Q(n1,1)*Q(n2+n6,2)*Q(n3+n4+n5+n7+n8,5)+48.*Q(n1+n2+n6,3)*Q(n3+n4+n5+n7+n8,5)
                - 120.*Q(n2,1)*Q(n6,1)*Q(n1+n3+n4+n5+n7+n8,6)+120.*Q(n2+n6,2)*Q(n1+n3+n4+n5+n7+n8,6)
                - 120.*Q(n1,1)*Q(n6,1)*Q(n2+n3+n4+n5+n7+n8,6)+120.*Q(n1+n6,2)*Q(n2+n3+n4+n5+n7+n8,6)
                + 720.*Q(n6,1)*Q(n1+n2+n3+n4+n5+n7+n8,7)+2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7+n8,3)
                - 2.*Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6+n7+n8,3)-2.*Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6+n7+n8,3)+4.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6+n7+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7+n8,3)+2.*Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6+n7+n8,3)
                - 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7+n8,3)+2.*Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6+n7+n8,3)
                + 4.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6+n7+n8,3)-2.*Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7+n8,3)
                + 2.*Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6+n7+n8,3)+4.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6+n7+n8,3)
                + 4.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6+n7+n8,3)-12.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6+n7+n8,3)
                - 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7+n8,3)+2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6+n7+n8,3)
                + 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6+n7+n8,3)+2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6+n7+n8,3)
                - 4.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6+n7+n8,3)-2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7+n8,3)
                + 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6+n7+n8,3)+2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6+n7+n8,3)
                + 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6+n7+n8,3)-4.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6+n7+n8,3)
                + 4.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6+n7+n8,3)-4.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7+n8,3)+2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6+n7+n8,3)
                + 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6+n7+n8,3)+2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6+n7+n8,3)
                - 4.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6+n7+n8,3)+4.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6+n7+n8,3)
                - 4.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6+n7+n8,3)+4.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6+n7+n8,3)
                - 4.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6+n7+n8,3)-12.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6+n7+n8,3)
                - 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7+n8,3)+2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6+n7+n8,3)
                + 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6+n7+n8,3)+2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6+n7+n8,3)
                - 4.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6+n7+n8,3)+4.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6+n7+n8,3)
                - 4.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6+n7+n8,3)+4.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6+n7+n8,3)
                - 4.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6+n7+n8,3)-12.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6+n7+n8,3)
                + 4.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6+n7+n8,3)-4.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6+n7+n8,3)
                - 12.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6+n7+n8,3)-12.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6+n7+n8,3)
                + 48.*Q(n1+n2+n3+n4+n5,5)*Q(n6+n7+n8,3)-6.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7+n8,4)
                + 6.*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6+n7+n8,4)+6.*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6+n7+n8,4)
                + 6.*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6+n7+n8,4)-12.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6+n7+n8,4)
                + 6.*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6+n7+n8,4)-6.*Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6+n7+n8,4)
                + 6.*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6+n7+n8,4)-6.*Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6+n7+n8,4)
                - 12.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6+n7+n8,4)+6.*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6+n7+n8,4)
                - 6.*Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6+n7+n8,4)-12.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6+n7+n8,4)
                - 12.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6+n7+n8,4)+36.*Q(n2+n3+n4+n5,4)*Q(n1+n6+n7+n8,4)
                - 6.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7+n8,4)+6.*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6+n7+n8,4)
                + 6.*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6+n7+n8,4)+6.*Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6+n7+n8,4)
                - 12.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6+n7+n8,4)+6.*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6+n7+n8,4)
                - 6.*Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6+n7+n8,4)+6.*Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6+n7+n8,4)
                - 6.*Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6+n7+n8,4)-12.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6+n7+n8,4)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6+n7+n8,4)-6.*Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6+n7+n8,4)
                - 12.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6+n7+n8,4)-12.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6+n7+n8,4)
                + 36.*Q(n1+n3+n4+n5,4)*Q(n2+n6+n7+n8,4)+24.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6+n7+n8,5)
                - 24.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6+n7+n8,5)-24.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6+n7+n8,5)
                - 24.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6+n7+n8,5)+48.*Q(n3+n4+n5,3)*Q(n1+n2+n6+n7+n8,5)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7+n8,4)+6.*Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6+n7+n8,4)
                + 6.*Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6+n7+n8,4)+6.*Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6+n7+n8,4)
                - 12.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6+n7+n8,4)+6.*Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6+n7+n8,4)
                - 6.*Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6+n7+n8,4)+6.*Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6+n7+n8,4)
                - 6.*Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6+n7+n8,4)-12.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6+n7+n8,4)
                + 6.*Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6+n7+n8,4)-6.*Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6+n7+n8,4)
                - 12.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6+n7+n8,4)-12.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6+n7+n8,4)
                + 36.*Q(n1+n2+n4+n5,4)*Q(n3+n6+n7+n8,4)+24.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6+n7+n8,5)
                - 24.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6+n7+n8,5)-24.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6+n7+n8,5)
                - 24.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6+n7+n8,5)+48.*Q(n2+n4+n5,3)*Q(n1+n3+n6+n7+n8,5)
                + 24.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6+n7+n8,5)-24.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6+n7+n8,5)
                - 24.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6+n7+n8,5)-24.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6+n7+n8,5)
                + 48.*Q(n1+n4+n5,3)*Q(n2+n3+n6+n7+n8,5)-120.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6+n7+n8,6)
                + 120.*Q(n4+n5,2)*Q(n1+n2+n3+n6+n7+n8,6)-6.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7+n8,4)
                + 6.*Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6+n7+n8,4)+6.*Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6+n7+n8,4)
                + 6.*Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6+n7+n8,4)-12.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6+n7+n8,4)
                + 6.*Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6+n7+n8,4)-6.*Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6+n7+n8,4)
                + 6.*Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6+n7+n8,4)-6.*Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6+n7+n8,4)
                - 12.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6+n7+n8,4)+6.*Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6+n7+n8,4)
                - 6.*Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6+n7+n8,4)-12.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6+n7+n8,4)
                - 12.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6+n7+n8,4)+36.*Q(n1+n2+n3+n5,4)*Q(n4+n6+n7+n8,4)
                + 24.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6+n7+n8,5)-24.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6+n7+n8,5)
                - 24.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6+n7+n8,5)-24.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6+n7+n8,5)
                + 48.*Q(n2+n3+n5,3)*Q(n1+n4+n6+n7+n8,5)+24.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6+n7+n8,5)
                - 24.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6+n7+n8,5)-24.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6+n7+n8,5)
                - 24.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6+n7+n8,5)+48.*Q(n1+n3+n5,3)*Q(n2+n4+n6+n7+n8,5)
                - 120.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6+n7+n8,6)+120.*Q(n3+n5,2)*Q(n1+n2+n4+n6+n7+n8,6)
                + 24.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6+n7+n8,5)-24.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6+n7+n8,5)
                - 24.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6+n7+n8,5)-24.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6+n7+n8,5)
                + 48.*Q(n1+n2+n5,3)*Q(n3+n4+n6+n7+n8,5)-120.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6+n7+n8,6)
                + 120.*Q(n2+n5,2)*Q(n1+n3+n4+n6+n7+n8,6)-120.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6+n7+n8,6)
                + 120.*Q(n1+n5,2)*Q(n2+n3+n4+n6+n7+n8,6)+720.*Q(n5,1)*Q(n1+n2+n3+n4+n6+n7+n8,7)
                - 6.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7+n8,4)+6.*Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6+n7+n8,4)
                + 6.*Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6+n7+n8,4)+6.*Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6+n7+n8,4)
                - 12.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6+n7+n8,4)+6.*Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6+n7+n8,4)
                - 6.*Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6+n7+n8,4)+6.*Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6+n7+n8,4)
                - 6.*Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6+n7+n8,4)-12.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6+n7+n8,4)
                + 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6+n7+n8,4)-6.*Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6+n7+n8,4)
                - 12.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6+n7+n8,4)-12.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6+n7+n8,4)
                + 36.*Q(n1+n2+n3+n4,4)*Q(n5+n6+n7+n8,4)+24.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6+n7+n8,5)
                - 24.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6+n7+n8,5)-24.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6+n7+n8,5)
                - 24.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6+n7+n8,5)+48.*Q(n2+n3+n4,3)*Q(n1+n5+n6+n7+n8,5)
                + 24.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6+n7+n8,5)-24.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6+n7+n8,5)
                - 24.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6+n7+n8,5)-24.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6+n7+n8,5)
                + 48.*Q(n1+n3+n4,3)*Q(n2+n5+n6+n7+n8,5)-120.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6+n7+n8,6)
                + 120.*Q(n3+n4,2)*Q(n1+n2+n5+n6+n7+n8,6)+24.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6+n7+n8,5)
                - 24.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6+n7+n8,5)-24.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6+n7+n8,5)
                - 24.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6+n7+n8,5)+48.*Q(n1+n2+n4,3)*Q(n3+n5+n6+n7+n8,5)
                - 120.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6+n7+n8,6)+120.*Q(n2+n4,2)*Q(n1+n3+n5+n6+n7+n8,6)
                - 120.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6+n7+n8,6)+120.*Q(n1+n4,2)*Q(n2+n3+n5+n6+n7+n8,6)
                + 720.*Q(n4,1)*Q(n1+n2+n3+n5+n6+n7+n8,7)+24.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6+n7+n8,5)
                - 24.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6+n7+n8,5)-24.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6+n7+n8,5)
                - 24.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6+n7+n8,5)+48.*Q(n1+n2+n3,3)*Q(n4+n5+n6+n7+n8,5)
                - 120.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6+n7+n8,6)+120.*Q(n2+n3,2)*Q(n1+n4+n5+n6+n7+n8,6)
                - 120.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6+n7+n8,6)+120.*Q(n1+n3,2)*Q(n2+n4+n5+n6+n7+n8,6)
                + 720.*Q(n3,1)*Q(n1+n2+n4+n5+n6+n7+n8,7)-120.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6+n7+n8,6)
                + 120.*Q(n1+n2,2)*Q(n3+n4+n5+n6+n7+n8,6)+720.*Q(n2,1)*Q(n1+n3+n4+n5+n6+n7+n8,7)
                + 720.*Q(n1,1)*Q(n2+n3+n4+n5+n6+n7+n8,7)-5040.*Q(n1+n2+n3+n4+n5+n6+n7+n8,8);

 return eight;

} // TComplex Eight_4(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)

//==========================================================================================================================

TComplex Eight(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)
{
 // Generic eight-particle correlation <exp[i(n1*phi1+n2*phi2+n3*phi3+n4*phi4+n5*phi5+n6*phi6+n7*phi7+n8*phi8)]>.

 TComplex eight = Eight_1(n1,n2,n3,n4,n5,n6,n7,n8)
                + Eight_2(n1,n2,n3,n4,n5,n6,n7,n8)  
                + Eight_3(n1,n2,n3,n4,n5,n6,n7,n8)
                + Eight_4(n1,n2,n3,n4,n5,n6,n7,n8);

 return eight;

} // TComplex Eight(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6, Int_t n7, Int_t n8)

//=======================================================================================================================

TComplex Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0) 
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

//=======================================================================================================================

void GenericFormulas()
{
 // Main method.

 // a) Measure total execution time; 
 // b) Book all objects;
 // c) Calculate Q-vectors for available angles and weights;
 // d) Calculate n-particle correlations from Q-vectors (using standalone formulas);
 // e) Calculate n-particle correlations from Q-vectors (using recursion);
 // f) Calculate n-particle correlations with nested loops (brute force);
 // g) Final printout with comparison of results of d), e) and f). 

 // a) Measure total execution time: 
 TStopwatch timerStandalone, timerRecursion, timerNestedLoops; 
 
 // b) Book all objects:
 Cosmetics();

 // c) Calculate Q-vectors for available angles and weights;
 CalculateQvectors();

 // d) Calculate n-particle correlations from Q-vectors (using standalone formulas):
 //  2-p correlations:
 cout<<endl;
 timerStandalone.Start();
 cout<<" => Calculating 2-p correlations (using standalone formulas)...\r"<<flush;
 TComplex two = Two(h1,h2)/Two(0,0).Re();
 Double_t wTwo = Two(0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][0]->Fill(0.5,two.Re(),wTwo); // <<cos(h1*phi1+h2*phi2)>>
 correlations[1][0]->Fill(0.5,two.Im(),wTwo); // <<sin(h1*phi1+h2*phi2)>>
 //  3-p correlations:
 cout<<" => Calculating 3-p correlations (using standalone formulas)...\r"<<flush;
 TComplex three = Three(h1,h2,h3)/Three(0,0,0).Re();
 Double_t wThree = Three(0,0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][1]->Fill(0.5,three.Re(),wThree); // <<cos(h1*phi1+h2*phi2+h3*phi3)>>
 correlations[1][1]->Fill(0.5,three.Im(),wThree); // <<sin(h1*phi1+h2*phi2+h3*phi3)>>
 //  4-p correlations:
 cout<<" => Calculating 4-p correlations (using standalone formulas)...\r"<<flush;
 TComplex four = Four(h1,h2,h3,h4)/Four(0,0,0,0).Re();
 Double_t wFour = Four(0,0,0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][2]->Fill(0.5,four.Re(),wFour); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
 correlations[1][2]->Fill(0.5,four.Im(),wFour); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
 //  5-p correlations:
 cout<<" => Calculating 5-p correlations (using standalone formulas)...\r"<<flush;
 TComplex five = Five(h1,h2,h3,h4,h5)/Five(0,0,0,0,0).Re();
 Double_t wFive = Five(0,0,0,0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][3]->Fill(0.5,five.Re(),wFive); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5)>>
 correlations[1][3]->Fill(0.5,five.Im(),wFive); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5)>>
 //  6-p correlations:
 cout<<" => Calculating 6-p correlations (using standalone formulas)...\r"<<flush;
 TComplex six = Six(h1,h2,h3,h4,h5,h6)/Six(0,0,0,0,0,0).Re();
 Double_t wSix = Six(0,0,0,0,0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][4]->Fill(0.5,six.Re(),wSix); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
 correlations[1][4]->Fill(0.5,six.Im(),wSix); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>> 
 //  7-p correlations:
 cout<<" => Calculating 7-p correlations (using standalone formulas)...\r"<<flush;
 TComplex seven = Seven(h1,h2,h3,h4,h5,h6,h7)/Seven(0,0,0,0,0,0,0).Re();
 Double_t wSeven = Seven(0,0,0,0,0,0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][5]->Fill(0.5,seven.Re(),wSeven); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7)>>
 correlations[1][5]->Fill(0.5,seven.Im(),wSeven); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7)>> 
 //  8-p correlations:
 cout<<" => Calculating 8-p correlations (using standalone formulas)...\r"<<flush;
 TComplex eight = Eight(h1,h2,h3,h4,h5,h6,h7,h8)/Eight(0,0,0,0,0,0,0,0).Re();
 Double_t wEight = Eight(0,0,0,0,0,0,0,0).Re(); // Weight is 'number of combinations' by default
 correlations[0][6]->Fill(0.5,eight.Re(),wEight); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>
 correlations[1][6]->Fill(0.5,eight.Im(),wEight); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>
  printf("\n\n"); timerStandalone.Print(); printf("\n");

 // e) Calculate n-particle correlations from Q-vectors (using recursion):
 //  2-p correlations:
 timerRecursion.Start();
 cout<<" => Calculating 2-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Two_Num[2] = {h1,h2};       
 Int_t harmonics_Two_Den[2] = {0,0};       
 TComplex twoRecursion = Recursion(2,harmonics_Two_Num)/Recursion(2,harmonics_Two_Den).Re();
 Double_t wTwoRecursion = Recursion(2,harmonics_Two_Den).Re();
 recursion[0][0]->Fill(0.5,twoRecursion.Re(),wTwoRecursion); // <<cos(h1*phi1+h2*phi2)>>
 recursion[1][0]->Fill(0.5,twoRecursion.Im(),wTwoRecursion); // <<sin(h1*phi1+h2*phi2)>>
 //  3-p correlations:
 cout<<" => Calculating 3-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Three_Num[3] = {h1,h2,h3};       
 Int_t harmonics_Three_Den[3] = {0,0,0};       
 TComplex threeRecursion = Recursion(3,harmonics_Three_Num)/Recursion(3,harmonics_Three_Den).Re();
 Double_t wThreeRecursion = Recursion(3,harmonics_Three_Den).Re();
 recursion[0][1]->Fill(0.5,threeRecursion.Re(),wThreeRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3)>>
 recursion[1][1]->Fill(0.5,threeRecursion.Im(),wThreeRecursion); // <<sin(h1*phi1+h2*phi2+h3*phi3)>>
 //  4-p correlations:
 cout<<" => Calculating 4-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Four_Num[4] = {h1,h2,h3,h4};       
 Int_t harmonics_Four_Den[4] = {0,0,0,0};       
 TComplex fourRecursion = Recursion(4,harmonics_Four_Num)/Recursion(4,harmonics_Four_Den).Re();
 Double_t wFourRecursion = Recursion(4,harmonics_Four_Den).Re();
 recursion[0][2]->Fill(0.5,fourRecursion.Re(),wFourRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
 recursion[1][2]->Fill(0.5,fourRecursion.Im(),wFourRecursion); // <<<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
 //  5-p correlations:
 cout<<" => Calculating 5-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Five_Num[5] = {h1,h2,h3,h4,h5};       
 Int_t harmonics_Five_Den[5] = {0,0,0,0,0};       
 TComplex fiveRecursion = Recursion(5,harmonics_Five_Num)/Recursion(5,harmonics_Five_Den).Re();
 Double_t wFiveRecursion = Recursion(5,harmonics_Five_Den).Re();
 recursion[0][3]->Fill(0.5,fiveRecursion.Re(),wFiveRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5)>>
 recursion[1][3]->Fill(0.5,fiveRecursion.Im(),wFiveRecursion); // <<<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5)>>
 //  6-p correlations:
 cout<<" => Calculating 6-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Six_Num[6] = {h1,h2,h3,h4,h5,h6};       
 Int_t harmonics_Six_Den[6] = {0,0,0,0,0,0};       
 TComplex sixRecursion = Recursion(6,harmonics_Six_Num)/Recursion(6,harmonics_Six_Den).Re();
 Double_t wSixRecursion = Recursion(6,harmonics_Six_Den).Re();
 recursion[0][4]->Fill(0.5,sixRecursion.Re(),wSixRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
 recursion[1][4]->Fill(0.5,sixRecursion.Im(),wSixRecursion); // <<<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
 //  7-p correlations:
 cout<<" => Calculating 7-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Seven_Num[7] = {h1,h2,h3,h4,h5,h6,h7};       
 Int_t harmonics_Seven_Den[7] = {0,0,0,0,0,0,0};       
 TComplex sevenRecursion = Recursion(7,harmonics_Seven_Num)/Recursion(7,harmonics_Seven_Den).Re();
 Double_t wSevenRecursion = Recursion(7,harmonics_Seven_Den).Re();
 recursion[0][5]->Fill(0.5,sevenRecursion.Re(),wSevenRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7)>>
 recursion[1][5]->Fill(0.5,sevenRecursion.Im(),wSevenRecursion); // <<<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7)>>
 //  8-p correlations:
 cout<<" => Calculating 8-p correlations (using recursion)...       \r"<<flush;
 Int_t harmonics_Eight_Num[8] = {h1,h2,h3,h4,h5,h6,h7,h8};       
 Int_t harmonics_Eight_Den[8] = {0,0,0,0,0,0,0,0};       
 TComplex eightRecursion = Recursion(8,harmonics_Eight_Num)/Recursion(8,harmonics_Eight_Den).Re();
 Double_t wEightRecursion = Recursion(8,harmonics_Eight_Den).Re();
 recursion[0][6]->Fill(0.5,eightRecursion.Re(),wEightRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>
 recursion[1][6]->Fill(0.5,eightRecursion.Im(),wEightRecursion); // <<<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6+h7*phi7+h8*phi8)>>
 printf("\n\n"); timerRecursion.Print(); printf("\n");

 // f) Calculate n-particle correlations with nested loops (brute force):
 if(bEvaluateNestedLoops)
 {
  timerNestedLoops.Start();
  cout<<" => Calculating 2-p correlations (using nested loops)...       \r"<<flush;
  TwoNestedLoops(h1,h2); 
  cout<<" => Calculating 3-p correlations (using nested loops)...       \r"<<flush;
  ThreeNestedLoops(h1,h2,h3);
  cout<<" => Calculating 4-p correlations (using nested loops)...       \r"<<flush;
  FourNestedLoops(h1,h2,h3,h4);
  cout<<" => Calculating 5-p correlations (using nested loops)...       \r"<<flush;
  FiveNestedLoops(h1,h2,h3,h4,h5);
  cout<<" => Calculating 6-p correlations (using nested loops)...       \r"<<flush;
  SixNestedLoops(h1,h2,h3,h4,h5,h6);
  cout<<" => Calculating 7-p correlations (using nested loops)...       \r"<<flush;
  SevenNestedLoops(h1,h2,h3,h4,h5,h6,h7);
  cout<<" => Calculating 8-p correlations (using nested loops)...       \r"<<flush;
  EightNestedLoops(h1,h2,h3,h4,h5,h6,h7,h8); 
  printf("\n\n"); timerNestedLoops.Print(); printf("\n");
 } // if(bEvaluateNestedLoops)
 
 // e) Final printout: 
 printf("\n cosine:");
 printf("\n  2-p => Standalone:   %.12f",correlations[0][0]->GetBinContent(1));
 printf("\n  2-p => Recursion:    %.12f",recursion[0][0]->GetBinContent(1));
 printf("\n  2-p => Nested loops: %.12f",nestedLoops[0][0]->GetBinContent(1));
 printf("\n\n  3-p => Standalone:   %.12f",correlations[0][1]->GetBinContent(1));
 printf("\n  3-p => Recursion:    %.12f",recursion[0][1]->GetBinContent(1));
 printf("\n  3-p => Nested loops: %.12f",nestedLoops[0][1]->GetBinContent(1));
 printf("\n\n  4-p => Standalone:   %.12f",correlations[0][2]->GetBinContent(1));
 printf("\n  4-p => Recursion:    %.12f",recursion[0][2]->GetBinContent(1));
 printf("\n  4-p => Nested loops: %.12f",nestedLoops[0][2]->GetBinContent(1));
 printf("\n\n  5-p => Standalone:   %.12f",correlations[0][3]->GetBinContent(1));
 printf("\n  5-p => Recursion:    %.12f",recursion[0][3]->GetBinContent(1));
 printf("\n  5-p => Nested loops: %.12f",nestedLoops[0][3]->GetBinContent(1));
 printf("\n\n  6-p => Standalone:   %.12f",correlations[0][4]->GetBinContent(1));
 printf("\n  6-p => Recursion:    %.12f",recursion[0][4]->GetBinContent(1));
 printf("\n  6-p => Nested loops: %.12f",nestedLoops[0][4]->GetBinContent(1));
 printf("\n\n  7-p => Standalone:   %.12f",correlations[0][5]->GetBinContent(1));
 printf("\n  7-p => Recursion:    %.12f",recursion[0][5]->GetBinContent(1));
 printf("\n  7-p => Nested loops: %.12f",nestedLoops[0][5]->GetBinContent(1));
 printf("\n\n  8-p => Standalone:   %.12f",correlations[0][6]->GetBinContent(1));
 printf("\n  8-p => Recursion:    %.12f",recursion[0][6]->GetBinContent(1));
 printf("\n  8-p => Nested loops: %.12f",nestedLoops[0][6]->GetBinContent(1));

 printf("\n\n sinus:");
 printf("\n  2-p => Standalone:   %.12f",correlations[1][0]->GetBinContent(1));
 printf("\n  2-p => Recursion:    %.12f",recursion[1][0]->GetBinContent(1));
 printf("\n  2-p => Nested loops: %.12f",nestedLoops[1][0]->GetBinContent(1));
 printf("\n\n  3-p => Standalone:   %.12f",correlations[1][1]->GetBinContent(1));
 printf("\n  3-p => Recursion:    %.12f",recursion[1][1]->GetBinContent(1));
 printf("\n  3-p => Nested loops: %.12f",nestedLoops[1][1]->GetBinContent(1));
 printf("\n\n  4-p => Standalone:   %.12f",correlations[1][2]->GetBinContent(1));
 printf("\n  4-p => Recursion:    %.12f",recursion[1][2]->GetBinContent(1));
 printf("\n  4-p => Nested loops: %.12f",nestedLoops[1][2]->GetBinContent(1));
 printf("\n\n  5-p => Standalone:   %.12f",correlations[1][3]->GetBinContent(1));
 printf("\n  5-p => Recursion:    %.12f",recursion[1][3]->GetBinContent(1));
 printf("\n  5-p => Nested loops: %.12f",nestedLoops[1][3]->GetBinContent(1));
 printf("\n\n  6-p => Standalone:   %.12f",correlations[1][4]->GetBinContent(1));
 printf("\n  6-p => Recursion:    %.12f",recursion[1][4]->GetBinContent(1));
 printf("\n  6-p => Nested loops: %.12f",nestedLoops[1][4]->GetBinContent(1));
 printf("\n\n  7-p => Standalone:   %.12f",correlations[1][5]->GetBinContent(1));
 printf("\n  7-p => Recursion:    %.12f",recursion[1][5]->GetBinContent(1));
 printf("\n  7-p => Nested loops: %.12f",nestedLoops[1][5]->GetBinContent(1));
 printf("\n\n  8-p => Standalone:   %.12f",correlations[1][6]->GetBinContent(1));
 printf("\n  8-p => Recursion:    %.12f",recursion[1][6]->GetBinContent(1));
 printf("\n  8-p => Nested loops: %.12f",nestedLoops[1][6]->GetBinContent(1));

 printf("\n\n"); 

} // void GenericFormulas()




