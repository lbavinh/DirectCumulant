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
#include "hasard.h"

#include "distributions.h" /* contains emission parameters */


/* PARAMETER DECLARATIONS */
#define Pi (2.*acos(0.))
#define sqr(x) ((x)*(x))

#define pTmax 4900. /* maximum possible transverse momentum for a particle 
  Check consistency with the value in distributions.cc */

#define nonflow 0 /* Simulating nonflow correlations: 
		     0: no nonflow correlations; 
		     1: "pair wise" emission (2 particles with same azimuth);
		     2: "quadruplet" emission (4 particles with same azimuth).*/
#define nonflowrate 0.250
/* Fraction of particles that are affected by nonflow effects. */

/* */

FILE *data,*events,*output;

/* MAIN PROGRAM */

main() 
{
  /* Variable declarations */
  long Neve; /* Number of events; read from input file data.dat */
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
