#include <iostream>
#include <fstream>
#include <math.h>
// #include <complex.h>

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TVector3.h>
#include <TH2F.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDatabasePDG.h>
#include <TComplex.h>
#include "Bessel.c"
float CentB(float bimp);
int GetCentBin(float cent);

#define MAX_TRACKS 10000

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
#define kr 1000

#define vmax 0.101 /* maximal possible integrated flow value */
#define vstep 0.001
#define vmin 0.021 /* minimal possible integrated flow value: check that vmin + kr*vstep = vmax!! */

#define Nbins 60 /* number of bins for differential flow. Check that it is consistent with the number in distributions.cc! */

/* */
void FlowLeeYangZeros(TString inputFileName, TString outputFileName)
{
    TStopwatch timer;
    timer.Start();

    // Constant declaration
    const int npid = 8;  // h+, pions+, kaons+, protons+, h-, pions-, kaons-, protons-
    const int ncent = 9; // 0-80%
    // const double bin_cent[ncent] = {2.5,7.5,15.,25.,35.,45.,55.,65.,75.};
    const int npt = 16; // 0.5 - 3.6 GeV/c - number of pT bins
    const double bin_pT[npt + 1] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.6};
    const double maxpt = 3.6; // max pt
    const double minpt = 0.;  // min pt
    const double maxptRF = 3.;
    const double minptRF = 0.2;
    const float eta_cut = 1.5;
    const float eta_gap = 0.05;
    const int neta = 2; // [eta-,eta+]

    // Configure input information
    TChain *chain = new TChain("mctree");

    std::ifstream file(inputFileName.Data());
    std::string line;
    while (std::getline(file, line))
    {
        chain->Add(line.c_str());
    }

    Float_t bimp;
    Float_t phi2;
    Float_t phi3;
    Float_t ecc2;
    Float_t ecc3;
    Int_t npart;
    Int_t nh;
    Float_t momx[MAX_TRACKS];   //[nh]
    Float_t momy[MAX_TRACKS];   //[nh]
    Float_t momz[MAX_TRACKS];   //[nh]
    Float_t ene[MAX_TRACKS];    //[nh]
    Int_t hid[MAX_TRACKS];      //[nh]
    Int_t pdg[MAX_TRACKS];      //[nh]
    Short_t charge[MAX_TRACKS]; //[nh]

    // List of branches
    TBranch *b_bimp;   //!
    TBranch *b_phi2;   //!
    TBranch *b_phi3;   //!
    TBranch *b_ecc2;   //!
    TBranch *b_ecc3;   //!
    TBranch *b_npart;  //!
    TBranch *b_nh;     //!
    TBranch *b_momx;   //!
    TBranch *b_momy;   //!
    TBranch *b_momz;   //!
    TBranch *b_ene;    //!
    TBranch *b_hid;    //!
    TBranch *b_pdg;    //!
    TBranch *b_charge; //!

    chain->SetBranchAddress("bimp", &bimp, &b_bimp);
    chain->SetBranchAddress("phi2", &phi2, &b_phi2);
    chain->SetBranchAddress("phi3", &phi3, &b_phi3);
    chain->SetBranchAddress("ecc2", &ecc2, &b_ecc2);
    chain->SetBranchAddress("ecc3", &ecc3, &b_ecc3);
    chain->SetBranchAddress("npart", &npart, &b_npart);
    chain->SetBranchAddress("nh", &nh, &b_nh);
    chain->SetBranchAddress("momx", momx, &b_momx);
    chain->SetBranchAddress("momy", momy, &b_momy);
    chain->SetBranchAddress("momz", momz, &b_momz);
    chain->SetBranchAddress("ene", ene, &b_ene);
    chain->SetBranchAddress("hid", hid, &b_hid);
    chain->SetBranchAddress("pdg", pdg, &b_pdg);
    chain->SetBranchAddress("charge", charge, &b_charge);

    // Configure output information
    TFile *fo = new TFile(outputFileName.Data(), "recreate");

    TH1I *hEvt = new TH1I("hEvt", "Event number", 1, 0, 1);
    TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 300, 0, MAX_TRACKS);
    TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
    TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
    TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 350, -3.5, 3.5);
    TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

    // Flow Analysis with Lee Yang Zeros Method
    TProfile *prTest = new TProfile("prTest","",kr,0,1);
  // const complex<double> i(0,1);

  int neve=0; /* Number of events */
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
  // complex<double> g2[kt][kr], G2[kt][kr];
  TComplex g2[kt][kr], G2[kt][kr];
  double modG2sq[kt][kr];
  TComplex g2P[kt][kr], G2P[kt][kr];
  double w2[Nbins]; /* weights */

  /* Event flow vectors, useful for the computation of statistical errors:
     - Q2 is the (weighted) flow vector in each event in harmonic n=2;
     - Q2mean is its average over events;
     - modQ2sqmean is the average over event of the squared modulus |Q2|^2. */
  // complex<double> Q2, Q2mean;
  TComplex Q2, Q2mean;
  double modQ2sqmean;

  /* r02[] are the values of RZ which minimize the functions mod2Gsq[kt][kr]; 
     these are the r0^theta of Refs.[A,B]. */
  double r02[kt]; 

  /* Values of the generating function g2 at the minimum of the average G2 */
  // complex<double> g2r0[kt];
  TComplex g2r0[kt]; 

  // complex<double> dlng2_dz[kt], dG2_dz[kt];
  TComplex dlng2_dz[kt], dG2_dz[kt];
  // complex<double> dlng2_dw2[kt][Nbins], dG2_dw2[kt][Nbins];
  TComplex dlng2_dw2[kt][Nbins], dG2_dw2[kt][Nbins]; 
  // complex<double> basenum42[kt][Nbins], num42[kt][Nbins];
  TComplex basenum42[kt][Nbins], num42[kt][Nbins];
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
  rmult = 290;
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
      // RZ[k2] = (float)k2/kr*0.25;
      RZ[k2] = (float)k2/kr;

      if (k1==0) cout << RZ[k2] << " ";
      /* The moduli of the interpolation points are chosen so that they 
         correspond to equally spaced (with step vstep) flow values. */

      G2[k1][k2]= 0.;
      /* Initialization of the average generating functions */ 
    } 
    if (k1==0) cout << endl;
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
  TComplex cExp;
  TComplex Qtheta[kt];
  
    int mult ;
    // Start event loop
    int n_entries = chain->GetEntries();
    
    for (int iEv = 0; iEv < n_entries; iEv++)
    {
        // if (iEv % 1000 == 0)
            // std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
        if (iEv == 10000) break;
        chain->GetEntry(iEv);
        hEvt->Fill(0);
        // Get centrality
        float cent = CentB(bimp);
        if (cent != 25.)
            continue;
        mult = 0;
        int fcent = GetCentBin(cent);
        hBimp->Fill(bimp);

    

    /* Initialization of the generating functions gn[k1][k2]. */
    for(int k1=0; k1<kt; k1++) for(int k2=0; k2<kr; k2++) g2[k1][k2]=1.;
    /* Initialization of the event flow vector */
    Q2=0.;
    for(int k1=0; k1<kt; k1++) Qtheta[k1] = 0.;
        
        for (int iTrk = 0; iTrk < nh; iTrk++)
        {
            TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
            float pt = vect.Pt();
            float eta = vect.Eta();
            float phi = vect.Phi();
            if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
                continue; // track selection
            // if (fabs(eta)<eta_gap) continue;
            auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
            if (!particle)
                continue;
            float charge = 1. / 3. * particle->Charge();
            if (charge == 0)
                continue;

            hPt->Fill(pt);
            hEta->Fill(eta);
            hPhi->Fill(phi);
            Int_t ipt = -1;
            for (int j = 0; j < npt; j++)
            {
                if (pt >= bin_pT[j] && pt < bin_pT[j + 1])
                    ipt = j;
            }

            int fId = -1;
            if (pdg[iTrk] == 211)
                fId = 1; // pion+
            if (pdg[iTrk] == 321)
                fId = 2; // kaon+
            if (pdg[iTrk] == 2212)
                fId = 3; // proton
            if (pdg[iTrk] == -211)
                fId = 5; // pion-
            if (pdg[iTrk] == -321)
                fId = 6; // kaon-
            if (pdg[iTrk] == -2212)
                fId = 7; // anti-proton



            // ---------------------------------------------
            // --- calculate the product generating function
            // ---

      for(int k1=0; k1<kt; k1++) /* Loop over theta values */
      { 
        temp=cos(2.*phi-arg[k1]);
        // for(int k2=0; k2<kr; k2++) g2[k1][k2]*=(1.+i*RZ[k2]*temp);
        for(int k2=0; k2<kr; k2++) g2[k1][k2]*=TComplex(1.,RZ[k2]*temp);
      }/* End of the loop over theta values */

      /* Compute the event flow vectors: Ref.[B], Eq.(4), with Q = Qx + i Qy. */
      // Q2+=(exp(2.*i*((double) phi)));
      cExp = TComplex(0.,2.0*((double) phi));
      Q2+=TComplex::Exp(cExp);
        mult++;
        } // end of track loop

        rmultmean+=((float) mult); /* and compute the average multiplicity. */
    for(int k1=0; k1<kt; k1++) for(int k2=0; k2<kr; k2++) 
      /* Compute the generating functions G2[k1], G4[k1], 
         averaged over events at the points RZ for each angle theta. */
      G2[k1][k2]+=g2[k1][k2];

    Q2mean+=Q2;     /* Compute the average event flow vector... */ 
    // modQ2sqmean+=sqr(abs(Q2)); /* and the average of its square modulus */
    modQ2sqmean+=sqr(Q2.Rho()); /* and the average of its square modulus */
    
    // for(int k2=0;k2<kr;k2++) 
    // {
    //   modG2sq[0][k2] = abs(g2[0][k2]);
    //   if (iEv % 10000 == 0) cout << modG2sq[0][k2] << endl;
    //   prTest->Fill((float)k2/kr,modG2sq[0][k2]);
    // }
    
    // modG2sq[k1][k2]=sqr(abs(G2[k1][k2])/neve);
    for(int k1=0; k1<kt; k1++) 
    {
      Qtheta[k1] = Q2.Re()*cos(arg[k1]) + Q2.Im()*sin(arg[k1]);
      for(int k2=0; k2<kr; k2++) 
      {
        cExp = TComplex(0., RZ[k2]*Qtheta[k1]);
        g2P[k1][k2] = TComplex::Exp(cExp);
        G2P[k1][k2] += g2P[k1][k2];
      }
    }
    neve++;
    } // end event loop

  rmultmean/=neve; /* Average detected particle multiplicity */

  modQ2sqmean/=neve; /* Average square moduli of the event flow vectors */


  printf("Mean detected particle multiplicity <M>=%G\n", rmultmean);

  /* v = j_{01}/Sqrt(2M ln(Neve/2)), cf. Ref.[A], Eq.(80) */

  /* RECONSTRUCTION OF INTEGRATED FLOW */
  V2mean=0.;
  for(int k1=0; k1<kt; k1++) 
  { /* Loop over theta angles */

    for(int k2=0;k2<kr;k2++) 
    {
      // modG2sq[k1][k2]=sqr(abs(G2[k1][k2])/neve);
      modG2sq[k1][k2]=sqr(G2[k1][k2].Rho()/neve);
      // if (k1 == 0) std::cout << modG2sq[k1][k2] <<" ";
      if (k1 == 0) std::cout << G2P[k1][k2].Rho()/neve << " ";
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
    // sqrt(modQ2sqmean-sqr(real(Q2mean)/neve)-sqr(imag(Q2mean)/neve)-sqr(V2mean));
    sqrt(modQ2sqmean-sqr(Q2mean.Re()/neve)-sqr(Q2mean.Im()/neve)-sqr(V2mean));

  // plotVint=fopen("plots_Vint.grf","w");
  for(int k1=0; k1<kt; k1++) 
  { /* Loop over theta angles */
    /* Compute the statistical error bar on the estimates Vn^theta{infty}, 
       using Eq.(90) of Ref.[A] = Eq.(8) of Ref.[B]. */
    err2[k1]=V2[k1]*sqrt((exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0)+
			  exp(sqr(rootJ0/chi2)/2.))/2./neve)/rootJ0/J1rootJ0;
    cout << arg[k1] << V2[k1]/rmultmean << err2[k1]/rmultmean << endl;
    // fprintf(plotVint, "%.3g\t%.4g\t%.4g\n", arg[k1], V2[k1]/rmultmean, 
    //   err2[k1]/rmultmean);
  }
  // fclose(plotVint);

  /* Integrated elliptic flow v2 */
  // fprintf(output,"INTEGRATED ELLIPTIC FLOW:");
  
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
  cout << V2mean/rmultmean << err2mean/rmultmean << endl;
  // fprintf(output, " V2/<M>=%.3g +/- %.3g", V2mean/rmultmean, 
  //   err2mean/rmultmean);


    // Writing output
    fo->cd();
    fo->Write();
    fo->Close();

    timer.Stop();
    timer.Print();
}

float CentB(float bimp)
{
    // Hard coded centrality defenition
    // based on the impact parameter
    float fcent;
    if (bimp < 2.91)
        fcent = 2.5; // 0-5%
    else if (bimp < 4.18)
        fcent = 7.5; // 5-10%
    else if (bimp < 6.01)
        fcent = 15.; // 10-20%
    else if (bimp < 7.37)
        fcent = 25.; // 20-30%
    else if (bimp < 8.52)
        fcent = 35.; // 30-40%
    else if (bimp < 9.57)
        fcent = 45.; // 40-50%
    else if (bimp < 10.55)
        fcent = 55.; // 50-60%
    else if (bimp < 11.46)
        fcent = 65.; // 60-70%
    else if (bimp < 12.31)
        fcent = 75.; // 70-80%
    else
        fcent = -1;
    return fcent;
}

int GetCentBin(float cent)
{
    if (cent == -1)
        return -1;
    if (cent == 2.5)
        return 0;
    if (cent == 7.5)
        return 1;
    if (cent == 15.)
        return 2;
    if (cent == 25.)
        return 3;
    if (cent == 35.)
        return 4;
    if (cent == 45.)
        return 5;
    if (cent == 55.)
        return 6;
    if (cent == 65.)
        return 7;
    if (cent == 75.)
        return 8;
    return -1;
}

// root -l -b -q FlowLeeYangZeros.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'