/* Flow analysis through the generating-function zeros method. */

/* The input is a file 'events.dat' 
   following the structure of the file generated by 'generator.cc', i.e.: 
   - first, the number of events; 
   - then, for each event, the (detected) multiplicity, 
   and for each particle the transverse momentum (in MeV) and the azimuth
   (in radians). */

/* The program then reconstructs integrated elliptic flow (V2) and then 
   differential elliptic (v2) and "hexadecupolar" (v4) flows. */

/* The results are stored in the output file 'zeros.txt' */

/* Throughout the program, references are made to the papers:
   [A]: R.S.Bhalerao, N.Borghini, J.-Y.Ollitrault, Nucl. Phys. A 727 (2003) 373
        [nucl-th/0310016];
   [B]: N.Borghini, R.S.Bhalerao, J.-Y.Ollitrault, J. Phys. G 30 (2004) S1213
        [nucl-th/0402053]. */
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <complex.h>
#include <sys/time.h>
#include "Bessel.c"
#include "distributions.cc"
using namespace std;
/* */

#define Pi (2.*acos(0.))
#define sqr(x) ((x)*(x))
#define rootJ0 2.4048256  /* First zero of the modified Bessel function J0 */
#define J1rootJ0 0.519147 /* J1(rootJ0) */
#define J2rootJ0 0.431755 /* J2(rootJ0) */

/* PARAMETERS USED IN THE RECONSTRUCTION */
/* kr*kt is the number of points at which one computes the 
   generating function 
   kt possible values for the angle 
   kr possible values for the radius */ 
#define kt 5
#define kr 80

#define vmax 0.101 /* maximal possible integrated flow value */
#define vstep 0.001
#define vmin 0.021 /* minimal possible integrated flow value: check that vmin + kr*vstep = vmax!! */

#define Nbins 60 /* number of bins for differential flow. Check that it is consistent with the number in distributions.cc! */

/* */

FILE *input,*data,*output,*plotVint,*plotvdiff;

int main()
{ /* main() */
  /* Variable declaration */

  const complex<double> i(0,1);

  int neve; /* Number of events */
  int rmult;  /* Detected multiplicity in an event */
  double rpmult[Nbins]; /* Detected multiplicity per bin */
  double rmultmean; /* Average detected multiplicity */
  float phi, pT; /* particle azimuth and transverse momentum */
  int binpT;

  double arg[kt]; /* theta values */
  double RZ[kr]; /* tabulation points for each theta value */

  /* Generating functions evaluated at the tabulation points: 
     - g2[k1][k2] is the generating function g in the harmonic 2, 
       for theta=arg[k1], evaluated at RZ[k2];
     - G2[][] is its average over events;
     - modG2sq is the squared modulus of the averaged G2. */
  complex<double> g2[kt][kr], G2[kt][kr];
  double modG2sq[kt][kr];

  double w2[Nbins]; /* weights */

  /* Event flow vectors, useful for the computation of statistical errors:
     - Q2 is the (weighted) flow vector in each event in harmonic n=2;
     - Q2mean is its average over events;
     - modQ2sqmean is the average over event of the squared modulus |Q2|^2. */
  complex<double> Q2, Q2mean; 
  double modQ2sqmean;

  /* r02[] are the values of RZ which minimize the functions mod2Gsq[kt][kr]; 
     these are the r0^theta of Refs.[A,B]. */
  double r02[kt]; 

  /* Values of the generating function g2 at the minimum of the average G2 */
  complex<double> g2r0[kt]; 

  complex<double> dlng2_dz[kt], dG2_dz[kt];
  complex<double> dlng2_dw2[kt][Nbins], dG2_dw2[kt][Nbins]; 
  complex<double> basenum42[kt][Nbins], num42[kt][Nbins];

  /* V2[] are the reconstructed integrated flow values for each angle arg[k1],
     i.e. the various V2^theta{infty} in the notations of Refs.[A,B]; 
     V2mean is their average value, denoted by V2{infty} in the Refs.
     vd22[][], vd42[][] are the differential flows for each angle, 
       in a given bin;
     vd22mean[], vd42mean[] are their average values. */
  double V2[kt], V2mean;
  double vd22[kt][Nbins], vd22mean[Nbins], vd42[kt][Nbins], vd42mean[Nbins];
  double vd22av, vd42av;

  double chi2, err2[kt], err2mean;
  double err22[kt][Nbins], err22mean[Nbins], err42[kt][Nbins], err42mean[Nbins];

  /* For simulations only: parameters of the event generation */
  double Vmax, Vstep;

  int k;
  double temp;

  struct timeval Time;
  int debut, fin;

  /* Initializations */
  gettimeofday (&Time, 0);
  debut=Time.tv_sec;

  data=fopen("inputdata.dat","r");
  fscanf(data, "%i %i\n", &k, &rmult); 
  fclose(data);
  Vmax=vmax*rmult;
  Vstep=vstep*rmult;

  for(int k1=0; k1<kt; k1++)
  { /* Loop over angles */
    arg[k1]=((float) k1)*Pi/(kt-1.); 
    /* kt arguments equally spaced between 0 and Pi (radians).
       Please note that arg[] in this program is n*theta the Refs. */
    for(int k2=0; k2<kr; k2++)
    { 
      // RZ[k2]=rootJ0/(Vmax-Vstep*k2);
      RZ[k2]=(float)k2/kr;

      // if (k1==0) cout << RZ[k2] << " ";
      /* The moduli of the interpolation points are chosen so that they 
         correspond to equally spaced (with step vstep) flow values. */

      G2[k1][k2]=0.;
      /* Initialization of the average generating functions */ 
    } 
    // if (k1==0) cout << endl;
  } /* End of loop over angles */

  /* In this program, rmultmean is used to estimate statistical errors. */
  rmultmean=0.;
  for(int bin=0;bin<Nbins;bin++) 
  {
    rpmult[bin]=0.;
    w2[bin]=1.; /* unit weights for the moment... */
  }

  /* Averages of the (complex!) event flow vectors and their squared moduli. */
  Q2mean=0.;
  modQ2sqmean=0.;

  /* Scan of the data */
  printf("Reading the data file to analyse flow\n");
  input=fopen("events.dat","r");
  fscanf(input, "%i\n", &neve); /* Read the number of events */
  printf("----------\nNumber of events in the run: %i\n", neve);

  output=fopen("zeros.txt","w");
  fprintf(output,
	  "FLOW ANALYSIS THROUGH THE ZEROS OF THE GENERATING FUNCTION\n\n");
  fprintf(output, "Parameter in the analysis:\n"); 
  fprintf(output, "%i values of theta\n", kt); 
  fprintf(output,"\nAvailable statistics:\n  number of events = %i\n", neve);

  /* RECONSTRUCTION OF INTEGRATED FLOW FROM THE GENERATING FUNCTION */
  printf("\n 1. Reconstruction of integrated flow\n");
  /* */
  for(long ne=0; ne<neve; ne++) 
  { /* Loop over events */
    if (floor((ne+1.)*10./neve)==((ne+1.)*10./neve))
      printf("%.f percent of events processed\n",(ne+1.)*100./neve);

    fscanf(input, "%i", &rmult); /* Read the event multiplicity */
    rmultmean+=((float) rmult); /* and compute the average multiplicity. */

    /* Initialization of the generating functions gn[k1][k2]. */
    for(int k1=0; k1<kt; k1++) for(int k2=0; k2<kr; k2++) g2[k1][k2]=1.;
    /* Initialization of the event flow vector */
    Q2=0.;

    for(long np=0; np<rmult; np++) /* Loop over the event particles */
    {
      fscanf(input,"%f %f", &pT, &phi); /* Read the particle momentum & azimuth;
		                         the former is useless for the moment */
      binpT=pTbin(pT); /* Useless since unit weights... */
   
      /* For each value of theta and r, compute the generating functions g2, g4
         using Eq.(3) of Ref.[B] */
      for(int k1=0; k1<kt; k1++) /* Loop over theta values */
      { 
        temp=w2[binpT]*cos(2.*phi-arg[k1]);
        for(int k2=0; k2<kr; k2++) g2[k1][k2]*=(1.+i*RZ[k2]*temp);
      }/* End of the loop over theta values */

      /* Compute the event flow vectors: Ref.[B], Eq.(4), with Q = Qx + i Qy. */
      Q2+=(w2[binpT]*exp(2.*i*((double) phi)));
    } /* End of the loop over particles */
    
    for(int k1=0; k1<kt; k1++) for(int k2=0; k2<kr; k2++) 
      /* Compute the generating functions G2[k1], G4[k1], 
         averaged over events at the points RZ for each angle theta. */
      G2[k1][k2]+=g2[k1][k2];

    Q2mean+=Q2;     /* Compute the average event flow vector... */ 
    modQ2sqmean+=sqr(abs(Q2)); /* and the average of its square modulus */
  } /* End of the loop over events */
  fclose(input);
  rmultmean/=neve; /* Average detected particle multiplicity */

  modQ2sqmean/=neve; /* Average square moduli of the event flow vectors */

  gettimeofday (&Time, 0);
  fin=Time.tv_sec;
  printf("All events read, elapsed time=%d s\n", fin-debut);
  printf("Mean detected particle multiplicity <M>=%G\n", rmultmean);
  fprintf(output,"  mean detected particle multiplicity <M>=%G\n\n", rmultmean);
  fprintf(output,"  Minimum measurable flow v=%.3g\n\n", 
	  rootJ0/sqrt(2.*rmultmean*log(0.5*neve))); 
  /* v = j_{01}/Sqrt(2M ln(Neve/2)), cf. Ref.[A], Eq.(80) */

  /* RECONSTRUCTION OF INTEGRATED FLOW */
  V2mean=0.;
  for(int k1=0; k1<kt; k1++) 
  { /* Loop over theta angles */
    for(int k2=0;k2<kr;k2++) 
    {
      modG2sq[k1][k2]=sqr(abs(G2[k1][k2])/neve);
      if (k1 == 0) std::cout << modG2sq[k1][k2] <<" "; 
    }  
    if (k1 == 0) std::cout << endl;  
    /* Compute the squared moduli of G2, G4 at each point */
    
    /* Looking for the first minimum of |G2|^2 */
    k=0;
    while (modG2sq[k1][k]>modG2sq[k1][k+1]) k++;
    /* Interpolate the value of V2[k1], see footnote 3 in Ref.[A],
       and derive the corresponding position of the first zero of G2 */
    V2[k1]=Vmax-Vstep*(k+(modG2sq[k1][k-1]-modG2sq[k1][k+1])/2./
	   (modG2sq[k1][k-1]-2.*modG2sq[k1][k]+modG2sq[k1][k+1]));
    r02[k1]=rootJ0/V2[k1];
    V2mean+=V2[k1]; /* Average V2 */
  } /* End of the loop over theta angles */

  V2mean/=((float) kt); /* Average V2 */
  /* Compute the resolution parameters chi, using Eqs.(59),(62) of Ref.[A] */
  chi2=V2mean/
    sqrt(modQ2sqmean-sqr(real(Q2mean)/neve)-sqr(imag(Q2mean)/neve)-sqr(V2mean));

  plotVint=fopen("plots_Vint.grf","w");
  for(int k1=0; k1<kt; k1++) 
  { /* Loop over theta angles */
    /* Compute the statistical error bar on the estimates Vn^theta{infty}, 
       using Eq.(90) of Ref.[A] = Eq.(8) of Ref.[B]. */
    err2[k1]=V2[k1]*sqrt((exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0)+
			  exp(sqr(rootJ0/chi2)/2.))/2./neve)/rootJ0/J1rootJ0;
    fprintf(plotVint, "%.3g\t%.4g\t%.4g\n", arg[k1], V2[k1]/rmultmean, 
      err2[k1]/rmultmean);
  }
  fclose(plotVint);

  /* Integrated elliptic flow v2 */
  fprintf(output,"INTEGRATED ELLIPTIC FLOW:");
  
  temp=0.;
  for(int k1=0; k1<kt; k1++) 
    /* Loop over the angles of the interpolation points,     
       to compute the statistical error bar on the average estimate V2{infty}, 
       with the help of Eqs.(89) of Ref.[A]. */
    temp+=exp(sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.))+
      exp(-sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.));
  err2mean=V2mean*sqrt(temp/2./neve/kt)/rootJ0/J1rootJ0;
  fprintf(output, " V2/<M>=%.3g +/- %.3g", V2mean/rmultmean, 
    err2mean/rmultmean);

  /* */
  /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
  /* */
  /* Initializations */
  for(int bin=0; bin<Nbins; bin++) vd22mean[bin]=vd42mean[bin]=0.;
  for(int k1=0; k1<kt; k1++) 
  {
    dG2_dz[k1]=0.;
    for(int bin=0; bin<Nbins; bin++) dG2_dw2[k1][bin]=num42[k1][bin]=0.;
  }

  input=fopen("events.dat","r");
  fscanf(input,"%i\n",&neve); /* Read the number of events */
  printf("\n 2. Reconstruction of differential flow\n");

  for(long ne=0; ne<neve; ne++) 
  { /* Loop over events */
    if (floor((ne+1.)*10./neve)==((ne+1.)*10./neve))
      printf("%.f percent of events processed\n",(ne+1.)*100./neve);

    /* Initializations */
    for(int k1=0; k1<kt; k1++)
    {
      g2r0[k1]=1.;
      dlng2_dz[k1]=0.;
      for(int bin=0; bin<Nbins; bin++) dlng2_dw2[k1][bin]=basenum42[k1][bin]=0.;
    }
    
    fscanf(input,"%i",&rmult); /* Read the event multiplicity */
    for(long np=0; np<rmult; np++) /* Loop over the event particles */
    {
      /* Read the particle transverse momentum and azimuth */
      fscanf(input, "%f %f", &pT, &phi); 
      /* Assign a bin to the particle according to its transverse momentum, 
         and increment the number of detected particles in that bin. */
      binpT=pTbin(pT);
      rpmult[binpT]+=1.; 

      for(int k1=0; k1<kt; k1++)
      {
        /* For each value of theta, compute the generating functions g2, g4
           at the first minimum r0n of Gn: 
           the corresponding quantity, g^theta(ir0^theta), appears in both the 
           numerator and denominator of Eq.(9) in Ref.[B]. */
        temp=w2[binpT]*cos(2.*phi-arg[k1]);
        g2r0[k1]*=(1.+i*r02[k1]*temp);
        /* Compute the sum over all particles that appears in the denominator 
           of Eq.(9) in Ref.[B]. */
        dlng2_dz[k1]+=(temp/(1.+i*r02[k1]*temp)); 
        /* Compute the ratio that stands in the numerator of Eq.(9) in Ref.[B].
           This ratio should be summed over all differential particles in a bin,
           and then (later) divided by the total number of such particles, to 
           perform the corresponding average (denoted by < >_psi in Ref.[B]. */
        dlng2_dw2[k1][binpT]+=(cos(2.*phi-arg[k1])/(1.+i*r02[k1]*temp)); 
        basenum42[k1][binpT]+=(cos(4.*phi-2.*arg[k1])/(1.+i*r02[k1]*temp)); 
      } /* End of the loop over theta angles */
    } /* End of the loop over particles */

    for(int k1=0; k1<kt; k1++) /* loop over theta values */
    { /* Compute the average over events in the denominator of Eq.(9) 
         in Ref.[B] */
      dG2_dz[k1]+=dlng2_dz[k1]*g2r0[k1];

      for(int bin=0; bin<Nbins; bin++) /* loop over differential bins */
      { /* Compute the average over differential particles in each bin 
           in the numerator of Eq.(9) in Ref.[B] */
        dG2_dw2[k1][bin]+=dlng2_dw2[k1][bin]*g2r0[k1];
        num42[k1][bin]+=basenum42[k1][bin]*g2r0[k1];
      } /* loop over differential bins */
    } /* end of the loop over theta values */
  } /* End of the loop over events */
  fclose(input);

  for(int k1=0; k1<kt; k1++) 
  { /* Average over events of the denominator of Eq.(9) in Ref.[B] */
    dG2_dz[k1]/=neve;

    for(int bin=0; bin<Nbins; bin++)
    { /* Average over differential particles of the numerator of Eq.(9) */
      dG2_dw2[k1][bin]/=rpmult[bin];
      num42[k1][bin]/=rpmult[bin];

      /* Computation of the differential flow value v'2/2 in each bin... */
      vd22[k1][bin]=V2[k1]*real(dG2_dw2[k1][bin]/dG2_dz[k1]);
      /* ...and of the corresponding statistical error: Ref.[B], Eq.(10) */
      err22[k1][bin]=sqrt((exp(sqr(rootJ0/chi2)/2.) - 
        exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0))/rpmult[bin])/
        2./J1rootJ0; /* standard error on v'2/2^theta */
      vd22mean[bin]+=vd22[k1][bin];

      /* Computation of the differential flow value v'4/2 in each bin... */
      vd42[k1][bin]=V2[k1]*(J1rootJ0/J2rootJ0)*
        real(num42[k1][bin]/(i*dG2_dz[k1])); /* Note the i in the denominator */
      err42[k1][bin]=sqrt((exp(sqr(rootJ0/chi2)/2.) + 
        exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0))/rpmult[bin])/
        2./J2rootJ0; /* standard error on v'4/2^theta */
      vd42mean[bin]+=vd42[k1][bin];
    }
  }
  
  for(int bin=0; bin<Nbins; bin++)
  {
    /* Average (over angles) differential flow values */
    vd22mean[bin]/=kt;
    vd42mean[bin]/=kt;
    /* Average (over events) number of particles per bin */
    rpmult[bin]/=neve;
  }

  /* Computation of statistical error bars on the average estimates */
  temp=0.;
  for(int k1=0; k1<kt; k1++) 
    /* Loop over the theta angles, to compute the statistical error */
    temp+=(exp(sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
      exp(-sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
  for(int bin=0; bin<Nbins; bin++)
    err22mean[bin]=sqrt(temp/rpmult[bin]/neve/kt)/2./J1rootJ0;

  temp=0.;
  for(int k1=0; k1<kt; k1++) 
    /* Loop over the theta angles, to compute the statistical error */
    temp+=(exp(sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.))+
      exp(-sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(2.*arg[k1]);
  for(int bin=0; bin<Nbins; bin++)
    err42mean[bin]=sqrt(temp/rpmult[bin]/neve/kt)/2./J2rootJ0;

  vd22av=vd42av=0.;
  plotvdiff=fopen("plot_vdiff-zeros.grf","w");
  fprintf(output,"\n\nDIFFERENTIAL FLOW\n\n");
  for(int bin=0; bin<Nbins; bin++)
  {
    if (rpmult[bin]>0)
    { /* compute the average (over pT) v2 and v4 */
      vd22av+=rpmult[bin]*vd22mean[bin]; 
      vd42av+=rpmult[bin]*vd42mean[bin];
    }
    fprintf(output," . bin %i: average detected multiplicity <M'>=%G\n", bin,
	   rpmult[bin]);
    fprintf(output,"   v2=%.3g +/- %.3g,", vd22mean[bin], err22mean[bin]);
    fprintf(output,"   v4=%.3g +/- %.3g\n", vd42mean[bin], err42mean[bin]);
    fprintf(plotvdiff, "%i  %.4g  %.4g  %.4g %.4g  %.4g\n", bin, rpmult[bin], 
	    vd22mean[bin], err22mean[bin], vd42mean[bin], err42mean[bin]);
  }
  vd22av/=rmultmean;
  vd42av/=rmultmean;
  fprintf(output, "<v2>=%.3g,  <v4>=%.3g\n", vd22av, vd42av);

  gettimeofday (&Time, 0);
  fin=Time.tv_sec;
  printf("All events read, elapsed time=%d s\n",fin-debut);
  fprintf(output,"\nEnd of the analysis, elapsed time=%d s\n",fin-debut);

  fclose(output);
  fclose(plotvdiff);
  return 0;
} /* main() */
