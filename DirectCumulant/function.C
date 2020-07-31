Int_t CentB(Float_t bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  int fcent;
  if (bimp < 4.18)
    fcent = 0; // 0-10%
  else if (bimp < 6.01)
    fcent = 10; //10-20%
  else if (bimp < 7.37)
    fcent = 20; //20-30%
  else if (bimp < 8.52)
    fcent = 30; //30-40%
  else if (bimp < 9.57)
    fcent = 40; //40-50%
  else if (bimp < 10.55)
    fcent = 50; //50-60%
  else if (bimp < 11.46)
    fcent = 60; //60-70%
  else if (bimp < 12.31)
    fcent = 70; //70-80%
  else
    fcent = -1;

  if (fcent != -1)
    return fcent + 5;
  else
    return -1;
}

TComplex Qstar(TComplex Q){
   TComplex QStar   = TComplex::Conjugate(Q);
   return QStar;
}

Double_t CalCor22(TComplex Q2, Double_t M, Double_t w2){
   // single-event average 2-particle azimuthal correlation <2>

  Double_t Q2Square = Q2.Rho2();
  // Double_t Rho2() const {return fRe*fRe+fIm*fIm;}
  Double_t coor22   = Q2Square - M;                                          
  
  return coor22/w2;
}

Double_t CalCor24(TComplex Q2, TComplex Q4, Double_t M, Double_t w4){
   // single-event average 4-particle azimuthal correlation <4>

   TComplex Q2Star   = Qstar(Q2);
   // static TComplex Conjugate(const TComplex &c) {return TComplex(c.Re(),-c.Im());}
   TComplex Q4Star   = Qstar(Q4);
   
   Double_t Q2Square = Q2.Rho2();
   Double_t Q4Square = Q4.Rho2();
   Double_t ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

   Double_t coor24   = (Q2Square*Q2Square + Q4Square - 2.*ReQQQ
                        - 4.*(M-2.)*Q2Square + 2.*M*(M-3.));

   return coor24/w4;
}

Double_t CalRedCor22(TComplex Q2, TComplex p2, Double_t M, Double_t mp, 
                     Double_t mq, Double_t wred2){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
  //  Double_t coor22 = (p2*Q2Star-mq).Re();
   Double_t coor22 = (p2*Q2Star).Re();

   return coor22/wred2;
}

Double_t CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                            TComplex q4, Double_t M, Double_t mp, Double_t mq, Double_t wred4){

   // Calculate the average reduced single-event 2-particle correlations                      
   TComplex Q2Star = TComplex::Conjugate(Q2);
   TComplex Q4Star = TComplex::Conjugate(Q4);
   TComplex q2Star = TComplex::Conjugate(q2);
   Double_t Q2Square = Q2.Rho2();
  //  TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
  //                 - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
  //                 - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
  //                 + 2.0*mq*M-6.0*mq;
   TComplex coorc = p2*Q2*Q2Star*Q2Star-p2*Q2*Q4Star
                  - 2.0*M*p2*Q2Star
                  + 2.0*p2*Q2Star;               
   Double_t coor24 = coorc.Re(); 
   return coor24/wred4;
}