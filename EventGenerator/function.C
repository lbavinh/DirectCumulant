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


double dndphi(double phi, double V2, double V3,double V4) 
{
  double temp;

  temp=(1.+2.*(V2*cos(2.*phi)+V3*cos(3.*phi)+V4*cos(4.*phi)))/
    (1.+2.*(fabs(V2)+fabs(V4)+fabs(V3)));
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

double GetProjectedRandom(double b, TH2F *const &hist)
// Projects Npart or Ncoll distribution for given impact parameter and gives you random Npart or Ncoll
// using the projected distribution as a probability function (i.e. gives you random number within RMS)
{
  TH1D *hist1D = hist->ProjectionY("tmp", hist->GetXaxis()->FindBin(b), hist->GetXaxis()->FindBin(b));
  double result = hist1D->GetRandom();
  return result;
}

double calc_v2(double b, double eta, double pt)
{
  float a1, a2, a3, a4;
  a1 = 0.4397 * exp(-(b - 4.526) * (b - 4.526) / 72.0) + 0.636;
  a2 = 1.916 / (b + 2) + 0.1;
  a3 = 4.79 * 0.0001 * (b - 0.621) * (b - 10.172) * (b - 23) + 1.2;  // this is >0 for b>0
  a4 = 0.135 * exp(-0.5 * (b - 10.855) * (b - 10.855) / 4.607 / 4.607) + 0.0120;

  float temp1 = pow(pt, a1) / (1 + exp((pt - 3.0) / a3));
  float temp2 = pow(pt + 0.1, -a2) / (1 + exp(-(pt - 4.5) / a3));
  float temp3 = 0.01 / (1 + exp(-(pt - 4.5) / a3));

  //v2 = (a4 * (temp1 + temp2) + temp3) * exp (-0.5 * eta * eta / 6.27 / 6.27);

  // Adjust flow rapidity dependence to better match PHOBOS 200 GeV Au+Au data
  // JGL 9/9/2019
  // See JS ToG talk at https://indico.bnl.gov/event/6764/

  double v2 = (a4 * (temp1 + temp2) + temp3) * exp(-0.5 * eta * eta / 2.0 / 2.0);

  return v2;
}

double calc_v3(double b, double v2)
{
  double v3;
  double fb = 0.97 + 1.06 * exp(-0.5 * b * b / 3.2 / 3.2);
  v3 = pow(fb * sqrt(v2), 3);
}

double calc_v4(double b, double eta, double pt)
{
  double temp;

  temp=calc_v2(b,eta,pt)*calc_v2(b,eta,pt);
  return temp;
}

