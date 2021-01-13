/* Monte Carlo event generator */

/* This program simulates events with anisotropic flow, 
   including possible mock-up nonflow two- and four-particle correlations. */

/* The input is a file "data.dat" with the number of events, 
   the average emitted multiplicity,
   and the event-to-event multiplicity deviation. */

/* The output consists in two files: 
   - a file "events.dat" with first the number of events, then for each event: 
     . the (emitted) multiplicity;
     . for each particle: the PID, transverse momentum (in MeV) and azimuth; 
       !!! PID not yet implemented !!!
   - a file "generator.txt" with informations, as the generation duration or 
   the average emitted multiplicity and anisotropic flow values. */

#include <stdio.h>
#include <math.h>
#include <complex>
#include <sys/time.h>
// #include "hasard.h"

/*Bibliotheque de generateur de nombres aleatoires. D'apres Knuth et NR */

#define KK 100                     /* the long lag */
#define LL  37                     /* the short lag */
#define mod_sum(x,y) (((x)+(y))-(int)((x)+(y)))   /* (x+y) mod 1.0 */

int premiere_util=1;

double ran_u[KK];           /* the generator state */

void ranf_array(double aa[], int n)
/* put n new random fractions in aa */
{
  register int i,j;
  for (j=0;j<KK;j++) aa[j]=ran_u[j];
  for (;j<n;j++) aa[j]=mod_sum(aa[j-KK],aa[j-LL]);
  for (i=0;i<LL;i++,j++) ran_u[i]=mod_sum(aa[j-KK],aa[j-LL]);
  for (;i<KK;i++,j++) ran_u[i]=mod_sum(aa[j-KK],ran_u[i-LL]);
}

#define TT  70   /* guaranteed separation between streams */
#define is_odd(s) ((s)&1)

void ranf_start(long seed)
/* do this before using ranf_array */
{
  register int t,s,j;
  double u[KK+KK-1],ul[KK+KK-1];
  double ulp=(1.0/(1L<<30))/(1L<<22);               /* 2 to the -52 */
  double ss=2.0*ulp*((seed&0x3fffffff)+2);

  for (j=0;j<KK;j++) {
    u[j]=ss; ul[j]=0.0;                     /* bootstrap the buffer */
    ss+=ss; if (ss>=1.0) ss-=1.0-2*ulp;  /* cyclic shift of 51 bits */
  }
  for (;j<KK+KK-1;j++) u[j]=ul[j]=0.0;
  u[1]+=ulp;ul[1]=ulp;           /* make u[1] (and only u[1]) "odd" */
  s=seed&0x3fffffff;
  t=TT-1; while (t) {
    for (j=KK-1;j>0;j--) ul[j+j]=ul[j],u[j+j]=u[j];     /* "square" */
    for (j=KK+KK-2;j>KK-LL;j-=2)
        ul[KK+KK-1-j]=0.0,u[KK+KK-1-j]=u[j]-ul[j];
    for (j=KK+KK-2;j>=KK;j--) if(ul[j]) {
      ul[j-(KK-LL)]=ulp-ul[j-(KK-LL)],
        u[j-(KK-LL)]=mod_sum(u[j-(KK-LL)],u[j]);
      ul[j-KK]=ulp-ul[j-KK],u[j-KK]=mod_sum(u[j-KK],u[j]);
    }
    if (is_odd(s)) {                             /* "multiply by z" */
      for (j=KK;j>0;j--)  ul[j]=ul[j-1],u[j]=u[j-1];
      ul[0]=ul[KK],u[0]=u[KK];       /* shift the buffer cyclically */
      if (ul[KK]) ul[LL]=ulp-ul[LL],u[LL]=mod_sum(u[LL],u[KK]);
    }
    if (s) s>>=1; else t--;
  }
  for (j=0;j<LL;j++) ran_u[j+KK-LL]=u[j];
  for (;j<KK;j++) ran_u[j-LL]=u[j];
}

/* the following routines are adapted from exercise 3.6--15 */
/* after calling ranf_start, get new randoms by, e.g., "x=ranf_arr_next()" */

#define QUALITY 1009 /* recommended quality level for high-res use */
double ranf_arr_buf[QUALITY];
double ranf_arr_sentinel=-1.0;
double *ranf_arr_ptr=&ranf_arr_sentinel; /* the next random fraction, or -1 */

#define ranf_arr_next() (*ranf_arr_ptr>=0? *ranf_arr_ptr++: ranf_arr_cycle())
double ranf_arr_cycle()
{
  ranf_array(ranf_arr_buf,QUALITY);
  ranf_arr_buf[100]=-1;
  ranf_arr_ptr=ranf_arr_buf+1;
  return ranf_arr_buf[0];
}

double hasard() {
  if(premiere_util) {
    ranf_start(1);
    premiere_util=0;
  }
  return ranf_arr_next();
}

void forceinit(long rac) {
  premiere_util=0;
  ranf_start(rac);
}





// #include "distributions.h" /* contains emission parameters */



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




/* PARAMETER DECLARATIONS */
#define Pi (2.*acos(0.))
#define sqr(x) ((x)*(x))

#define pTmax 4900. /* maximum possible transverse momentum for a particle. Check consistency with the value in distributions.cc */

#define nonflow 0 
/* Simulating nonflow correlations: 
		     0: no nonflow correlations; 
		     1: "pair wise" emission (2 particles with same azimuth);
		     2: "quadruplet" emission (4 particles with same azimuth).*/
#define nonflowrate 0.250
/* Fraction of particles that are affected by nonflow effects. */

/* */

FILE *data,*events,*output;

/* MAIN PROGRAM */

int main()
{
  /* Variable declarations */
  int Neve; /* Number of events; read from input file data.dat */
  int Mmean; /* Average emitted multiplicity; read from data.dat */
  int dmult; /* Fluctuation in the emitted multiplicity; read from data.dat */
  int mult; /* Emitted multiplicity: mult = Mmean +/- dmult */
  double multmean=0.; /* Average emitted multiplicity */
  double pTev;
  double pTmean=0.;

  double v1pT,v2pT,v4pT;
  double v1ev, v2ev, v4ev;  /* Integrated flow values in a given event */
  double v1mean=0., v2mean=0., v4mean=0.; /* Mean flow parameters <vnev> */

  double pT;
  double phi, phil, phir;

  struct timeval Time;
  int debut, fin; 

  int i, imax;
 
  /* End of variable declarations */

  /* Initializations */
  data=fopen("inputdata.dat","r");
  printf("----------\n");
  fscanf(data,"%i %i %i",&Neve,&Mmean,&dmult);
  printf("Generating %i events, with in each event %i+/-%i particles\n", 
	 Neve, Mmean, dmult);
  printf("--\n");
  fclose(data);

  printf("Beginning of the Monte-Carlo generation:\n");
  if (nonflow>0) 
  {
    printf(" - Nonflow effects simulated ");
    if (nonflow==1) printf("(pair-wise emission)\n");
    if (nonflow==2) printf("(quadruplet-wise emission)\n");
    printf("   affecting %i percent of the particles\n", int(100.*nonflowrate));
  }
  printf("\n");

  gettimeofday (&Time, 0);
  debut=Time.tv_sec;
  forceinit(Time.tv_usec); /* initialize the generator seed */
  events=fopen("events.dat","w");
  fprintf(events,"%i",Neve);

  /* Monte-Carlo simulation */
  for(long ne=0; ne<Neve; ne++) /* Loop over events */
  {
    if (floor((ne+1.)*10./Neve)==((ne+1.)*10./Neve))
      printf("%.f percent of events generated\n", (ne+1.)*100./Neve);

    mult=int(Mmean+2.*(hasard()-0.5)*dmult); /* Emitted multiplicity */
    fprintf(events, "\n%i\n", mult);

    pTev=0.;
    v1ev=v2ev=v4ev=0.;
    phir=2.*Pi*hasard(); /* Random reaction plane angle Phi_r */

    /* Loop over particles */
    for(int nm=0; nm<mult; nm++) 
    {
      momentum:
      pT=pTmax*hasard(); 
      /* Random particle transverse momentum between 0 and pTmax */
      if (hasard()>dndpT(pT)) goto momentum;
      /* generate transverse momentum according to the distribution, 
         using the hit-or-miss method. */

      v1pT=v1(pT);
      v2pT=v2(pT);
      v4pT=v4(pT);
      flow:
      phi=2.*Pi*hasard(); /* Random pion azimuth phi between 0 and 2Pi */
      if (hasard()>dndphi(phi,v1pT,v2pT,v4pT)) goto flow; 
      /* simulate anisotropic flow, with the hit-or-miss method */

      phil=phi+phir; /* particle angle with respect to the laboratory frame */
      while (phil>2.*Pi)
        phil-=2.*Pi; /* To make sure that phil is between 0 and 2 Pi */
         
      fprintf(events, "%.6g %.6g  ", pT, phil); 
      /* Print the transverse momentum & the angle */
      pTev+=pT;
      v1ev+=v1pT; 
      v2ev+=v2pT; 
      v4ev+=v4pT; /* Compute the average v1, v2, v4 in the event */

      if (nonflow>0) /* NONFLOW CORRELATION simulation */
        if ((nm<=(mult-2*nonflow)) && (hasard()<=nonflowrate))
        {
	/* Two tests: 
           - a first, very inelegant one, to avoid having more particles in the 
           event than the multiplicity which has been determined earlier;
           - a second, more useful one, to have a fraction ~nonflowrate of 
           particles affected by nonflow effects. */
        if (nonflow==1)
        /* Pair-wise emission:
           generating a second particle with the same momentum and azimuth.*/
        {
          nm++;
          fprintf(events, "%.6g %.6g  ", pT, phil); 
          /* Print the transverse & the angle */
          pTev+=pT;
          v1ev+=v1pT;
          v2ev+=v2pT; 
          v4ev+=v4pT; /* Compute the average v1, v2, v4 in the event */
        }
        else if (nonflow==2)
        /* Quadruplet-wise emission:
           generating three more particles with the same momentum and azimuth.*/
        {
          nm+=3;
          fprintf(events, "%.6g %.6g  %.6g %.6g  %.6g %.6g  ", pT, phil, 
            pT, phil, pT, phil); 
          /* Print the transverse & the angle */
          pTev+=3.*pT;
          v1ev+=3.*v1pT;
          v2ev+=3.*v2pT;
          v4ev+=3.*v4pT; /* Compute the average v1, v2, v4 in the event */
        }
        }
    } /* End of the loop over particles */

    multmean+=((float) mult); /* Compute the average emitted multiplicity */
    pTmean+=(pTev/mult);
    v1mean+=(v1ev/mult);
    v2mean+=(v2ev/mult); 
    v4mean+=(v4ev/mult); /* Compute the average v1, v2 and v4 */
  } /* End of the loop over events */

  fclose(events);

  pTmean/=Neve;
  multmean/=Neve;
  v1mean/=Neve; /* Average integrated directed flow */
  v2mean/=Neve; /* Average integrated elliptic flow */
  v4mean/=Neve; /* Average integrated v4 */

  gettimeofday (&Time, 0);
  fin=Time.tv_sec;
  printf("End of the Monte-Carlo, elapsed time=%d s\n\n", fin-debut);
  printf("Mean emitted multiplicity <M>=%G\n", multmean);
  printf("Average transverse momentum <pT>=%.3f\n", pTmean);
  printf("Average directed flow <v1>=%.3f\n", v1mean);
  printf("Average elliptic flow <v2>=%.3f\n", v2mean);
  printf("Average <v4>=%.3f\n", v4mean);

  /* Summary file */
  output=fopen("generator.txt","w");
  fprintf(output, "%i events generated, with in each event", Neve);
  fprintf(output, " %i+/-%i particles\n",  Mmean, dmult);

  if (nonflow>0) 
  {
    fprintf(output, " - Nonflow two-particle correlations simulated ");
    if (nonflow==1) fprintf(output, "(pair-wise emission)\n");
    else if (nonflow==2) fprintf(output, "(quadruplet-wise emission)\n");
    fprintf(output, "   affecting %i percent of the particles\n", 
            int(100.*nonflowrate));
  }

  fprintf(output, "\nMean emitted multiplicity <M>=%G\n", multmean);

  fprintf(output, "Average directed flow <v1>=%.3f\n", v1mean);
  fprintf(output, "Average elliptic flow <v2>=%.3f\n", v2mean);
  fprintf(output,"Average <v4>=%.3f\n", v4mean);
  
  fclose(output);
}
