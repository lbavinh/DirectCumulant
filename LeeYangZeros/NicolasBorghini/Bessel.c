#define BESSEL_cxx
#include <math.h>

#define sqr(x) ((x)*(x))

double BesselJ0(double x)
{
  double temp=1., xn=1.;
  long n, Nmax;

  Nmax=int(floor(2.*x)+4);
  for (n=1;n<Nmax;n++)
  {
    xn*=(-sqr(x/2./((float) n)));
    temp+=xn;
  }
  return temp;
}

double BesselJm(double x, int m)
{
  double temp, xn=1.;
  long n, Nmax;

  Nmax=int(floor(2.*x)+4);
  for (n=1;n<=m;n++) 
    xn*=(x/2./((float) n));
  temp=xn;
  for (n=1;n<Nmax;n++)
  {
    xn*=(-sqr(x/2.)/((float) n)/((float) n+m));
    temp+=xn;
  }
  return temp;
}

