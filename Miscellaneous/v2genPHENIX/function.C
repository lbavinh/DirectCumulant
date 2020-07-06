double dndpT(double pT)
{
double temp;
double pTmin=100.; 
double pTmax=4900.;
double  pT0=500.;
double pT1=3000.;
double T0=300.;
  if (pT < pTmin)
    temp=0;
  else if (pT <= pT0)
    temp=1;
  else if (pT<=pT1)
    temp=exp(-(pT-pT0)/T0);
  else 
    temp=exp(-(pT1-pT0)/T0)*pow((pT1/pT),7.);
  return temp;
}


double dndphi(double phi, double V2, double V4) 
{
  double temp;

  temp=(1.+2.*(V2*cos(2.*phi)+V4*cos(4.*phi)))/
    (1.+2.*(fabs(V2)+fabs(V4)));
  return temp;
}

double v2(double pT)
{
  double temp=0., v2pT0bis;


  double pT0bis=0.100;
  double pTsat=1.500;
  double v2sat=0.2;



  v2pT0bis = 0.5*v2sat*pT0bis/(pTsat-pT0bis);
  /* v2pT0bis = v2(pT0bis) is chosen so that the slopes of v2(pT) are
     continuous at pT = pT0bis and pT=pTsat-pT0bis */
  if (pT < pT0bis)
    temp = (pT/pT0bis)*(pT/pT0bis)*v2pT0bis;
  else if (pT < (pTsat-pT0bis))
    temp = (v2sat-2.*v2pT0bis)*(pT-pT0bis)/(pTsat-2.*pT0bis)+v2pT0bis;
  else if (pT < pTsat)
    temp = v2sat-((pT-pTsat)/pT0bis)*((pT-pTsat)/pT0bis)*v2pT0bis;
  else 
    temp = v2sat;

  return temp;
}









/* v4(pT): directly linked to v2(pT)! v4(pT)=v2(pT)^2 */
double v4(double pT)
{
  double temp;

  temp=v2(pT)*v2(pT);
  return temp;
}
