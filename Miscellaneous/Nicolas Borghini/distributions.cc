#include <math.h>

#define sqr(x) ((x)*(x))

#define pTmin 100. /* minimum possible transverse momentum for a particle */
#define pTmax 4900. /* maximum possible transverse momentum for a particle */

/* The next two parameters are used in the function dndpT (see below) */
#define pT0 500.
#define pT1 3000.
#define T0 300.

/* The following function gives the transverse-momentum distribution, 
   following a simple functional shape:
   dN/dpT is flat for 0 < pT < some pT0,  and then 
   decreases exponentially (with inverse slope parameter T0) for pT < pT < pT1,
   then for pT > pT1 it decreases with an inverse power-law. 
   Momenta (pT, pT0...) are given in MeV/c. */
double dndpT(double pT)
{
  double temp;

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

/* This function associates a bin to a given transverse momentum.
   For simplicity, there are Nbins=60 equally-sized bins to cover the region 
   where dN/dpT is non-vanishing. */
int pTbin(double pT)
{
  int temp;

  temp=int(60.*(pT-pTmin)/(pTmax-pTmin));

  return temp;
}

/* v1(pT)... */
double v1(double pT)
{
  double temp=0.03;

  return temp;
}

#define pT0bis 100.
#define pTsat 1500.
#define v2sat 0.2

/* v2(pT): mimicking the shape measured at RHIC
    - quadratic rise for 0 < pT < pT0bis;
    - linear rise for pT0bis < pT < pTsat-pT0bis;
    - quadratic rise again for pTsat-pT0bis < pT < pTsat
    - constant value v2sat for pT > pTsat */
double v2(double pT)
{
  double temp=0., v2pT0bis;

  v2pT0bis = 0.5*v2sat*pT0bis/(pTsat-pT0bis);
  /* v2pT0bis = v2(pT0bis) is chosen so that the slopes of v2(pT) are
     continuous at pT = pT0bis and pT=pTsat-pT0bis */
  if (pT < pT0bis)
    temp = sqr(pT/pT0bis)*v2pT0bis;
  else if (pT < (pTsat-pT0bis))
    temp = (v2sat-2.*v2pT0bis)*(pT-pT0bis)/(pTsat-2.*pT0bis)+v2pT0bis;
  else if (pT < pTsat)
    temp = v2sat-sqr((pT-pTsat)/pT0bis)*v2pT0bis;
  else 
    temp = v2sat;

  return temp;
}

/* v4(pT): directly linked to v2(pT)! v4(pT)=v2(pT)^2 */
double v4(double pT)
{
  double temp;

  temp=sqr(v2(pT));
  return temp;
}

double dndphi(double phi, double V1, double V2, double V4) 
{
  double temp;

  temp=(1.+2.*(V1*cos(phi)+V2*cos(2.*phi)+V4*cos(4.*phi)))/
    (1.+2.*(fabs(V1)+fabs(V2)+fabs(V4)));
  return temp;
}

