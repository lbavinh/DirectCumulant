// Event selection

float CentB(float bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  float fcent;
  if      (bimp < 2.91)  fcent = 2.5; // 0-5%
  else if (bimp < 4.18)  fcent = 7.5; // 5-10%
  else if (bimp < 6.01)  fcent = 15.; // 10-20%
  else if (bimp < 7.37)  fcent = 25.; // 20-30%
  else if (bimp < 8.52)  fcent = 35.; // 30-40%
  else if (bimp < 9.57)  fcent = 45.; // 40-50%
  else if (bimp < 10.55) fcent = 55.; // 50-60%
  else if (bimp < 11.46) fcent = 65.; // 60-70%
  else if (bimp < 12.31) fcent = 75.; // 70-80%
  else                   fcent = -1;
  return fcent;
}


int GetCentBin(float cent)
{
  if (cent == -1) return -1;
  if (cent == 2.5) return 0;
  if (cent == 7.5) return 1;
  if (cent == 15.) return 2;
  if (cent == 25.) return 3;
  if (cent == 35.) return 4;
  if (cent == 45.) return 5;
  if (cent == 55.) return 6;
  if (cent == 65.) return 7;
  if (cent == 75.) return 8;
  return -1;
}



TComplex Qstar(TComplex Q){
  TComplex QStar   = TComplex::Conjugate(Q);
  return QStar;
}

double CalCor22(TComplex Q2, double M, double w2){
  // single-event average 2-particle azimuthal correlation <2>

  double Q2Square = Q2.Rho2();
  double coor22   = Q2Square - M;                                          

  return coor22/w2;
}

double CalCor24(TComplex Q2, TComplex Q4, double M, double w4){
  // single-event average 4-particle azimuthal correlation <4>

  TComplex Q2Star   = Qstar(Q2);
  TComplex Q4Star   = Qstar(Q4);
  
  double Q2Square = Q2.Rho2();
  double Q4Square = Q4.Rho2();
  double ReQQQ    = (Q4 * Q2Star * Q2Star).Re();

  double coor24   = (Q2Square*Q2Square + Q4Square - 2*ReQQQ
                      - 4*(M-2)*Q2Square + 2*M*(M-3));

  return coor24/w4;
}

double CalRedCor22(TComplex Q2, TComplex p2, double M, double mp, 
                   double mq, double wred2){

  // Calculate the average reduced single-event 2-particle correlations                      
  TComplex Q2Star = TComplex::Conjugate(Q2);
  double coor22 = (p2*Q2Star-mq).Re();

  return coor22/wred2;
}

double CalRedCor24(TComplex Q2, TComplex Q4, TComplex p2, TComplex q2,
                   TComplex q4, double M, double mp, double mq, double wred4){

  // Calculate the average reduced single-event 2-particle correlations                      
  TComplex Q2Star = TComplex::Conjugate(Q2);
  TComplex Q4Star = TComplex::Conjugate(Q4);
  TComplex q2Star = TComplex::Conjugate(q2);
  double Q2Square = Q2.Rho2();
  TComplex coorc = p2*Q2*Q2Star*Q2Star-q4*Q2Star*Q2Star-p2*Q2*Q4Star
                 - 2.0*M*p2*Q2Star-2.0*mq*Q2Square+7.0*q2*Q2Star
                 - Q2*q2Star+q4*Q4Star+2.0*p2*Q2Star
                 + 2.0*mq*M-6.0*mq;
  double coor24 = coorc.Re(); 
  return coor24/wred4;
}