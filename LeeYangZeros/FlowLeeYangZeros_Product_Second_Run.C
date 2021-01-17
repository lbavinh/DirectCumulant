#include <iostream>
#include <fstream>

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

double CentB(double bimp);
int GetCentBin(double cent);
double GetR0(TH1F *const &hist);

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

using std::cout;
using std::endl;

#define MAX_TRACKS 10000

void FlowLeeYangZeros(TString inputFileName, TString outputFileName)
{
  TStopwatch timer;
  timer.Start();

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

  // QA histograms
  TFile *fo = new TFile(outputFileName.Data(), "recreate");

  TH1I *hEvt = new TH1I("hEvt", "Event number", 1, 0, 1);
  TH1I *hMult = new TH1I("hMult", "Multiplicity distr;M;dN/dM", 300, 0, MAX_TRACKS);
  TH1F *hBimp = new TH1F("hBimp", "Impact parameter;b (fm);dN/db", 200, 0., 20.);
  TH1F *hPt = new TH1F("hPt", "Pt-distr;p_{T} (GeV/c); dN/dP_{T}", 500, 0., 6.);
  TH1F *hPhi = new TH1F("hPhi", "Particle azimuthal angle distr with respect to RP; #phi-#Psi_{RP}; dN/d(#phi-#Psi_{RP})", 350, -3.5, 3.5);
  TH1F *hEta = new TH1F("hEta", "Pseudorapidity distr; #eta; dN/d#eta", 300, -10, 10);

  // Constant declaration
  const int npt = 9; // 0.5 - 3.6 GeV/c - number of pT bins
  const double bin_pT[npt+1]={0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.5,3.};

  const int ncent = 9; // 0-80%
  const double maxpt = 3.; // max pt
  const double minpt = 0.2;  // min pt
  const double eta_cut = 1.5;

  const int rbins = 300;
  const double rMax = 1.;
  const double rMin = 0.;
  const int thetabins = 5;
  const double rootJ0 = 2.4048256;
  const double J1rootJ0 = 0.519147; /* J1(rootJ0) */
  const double J2rootJ0 = 0.431755; /* J2(rootJ0) */
  // TProfile *prReGthetaSum[ncent][thetabins];
  // TProfile *prImGthetaSum[ncent][thetabins];
  // TH1F *hGthetaSum[ncent][thetabins];

  TProfile *prReGthetaProduct[ncent][thetabins];
  TProfile *prImGthetaProduct[ncent][thetabins];
  TH1F *hGthetaProduct[ncent][thetabins];
  TProfile *prRefMult = new TProfile("prRefMult","",ncent,0,ncent);
  TProfile *prRefMultPOI[ncent];
  TProfile *prQ2x = new TProfile("prQ2x","",ncent,0,ncent);
  TProfile *prQ2y = new TProfile("prQ2y","",ncent,0,ncent);
  TProfile *prQ2ModSq = new TProfile("prQ2ModSq","",ncent,0,ncent);
  TProfile *prV2RP = new TProfile("prV2RP","",ncent,0,ncent);
  for (int i = 0; i < ncent; ++i)
  {
    prRefMultPOI[i] = new TProfile(Form("prRefMultPOI_mult%d", i), "", npt, &bin_pT[0]);
    for (int j = 0; j < thetabins; ++j)
    {
      // prReGthetaSum[i][j] = new TProfile(Form("prReGthetaSum_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
      // prImGthetaSum[i][j] = new TProfile(Form("prImGthetaSum_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
      // hGthetaSum[i][j] = new TH1F(Form("hGthetaSum_mult%d_theta%d", i, j), "", rbins, rMin, rMax);

      prReGthetaProduct[i][j] = new TProfile(Form("prReGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
      prImGthetaProduct[i][j] = new TProfile(Form("prImGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
      hGthetaProduct[i][j] = new TH1F(Form("hGthetaProduct_mult%d_theta%d", i, j), "", rbins, rMin, rMax);
    }
  }

  // Variables
  double theta[thetabins];
  for (int thetabin = 0; thetabin < thetabins; thetabin++)
  {
    theta[thetabin] = thetabin * TMath::Pi() / (2.0 * thetabins);
  }
  double r[rbins];
  for (int rbin = 0; rbin < rbins; ++rbin)
  {
    r[rbin] = (double) hGthetaProduct[0][0]->GetBinCenter(rbin+1);
  }

  double Qtheta[thetabins];
  // TComplex genfunS[rbins][thetabins]; // sum
  TComplex genfunP[rbins][thetabins]; // product
  TComplex cExpo;
  double Q2x, Q2y;
  int mult;



  /* */
  /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
  /* */
  /* Values of the generating function g2 at the minimum of the average G2 */
  // double r02[thetabins];
  TComplex g2r0[thetabins]; 

  TComplex dlng2_dz[thetabins], dG2_dz[thetabins];
  TComplex dlng2_dw2[thetabins][npt], dG2_dw2[thetabins][npt]; 
  TComplex basenum42[thetabins][npt], num42[thetabins][npt];

  /* V2[] are the reconstructed integrated flow values for each angle arg[k1],
     i.e. the various V2^theta{infty} in the notations of Refs.[A,B]; 
     V2mean is their average value, denoted by V2{infty} in the Refs.
     vd22[][], vd42[][] are the differential flows for each angle, 
       in a given bin;
     vd22mean[], vd42mean[] are their average values. */
  // double V2[thetabins], V2mean;
  double vd22[thetabins][npt], vd22mean[npt], vd42[thetabins][npt], vd42mean[npt];
  double vd22av, vd42av;

  // double chi2, err2[thetabins], err2mean;
  double err22[thetabins][npt], err22mean[npt], err42[thetabins][npt], err42mean[npt];

  /* Initializations */
  for(int bin=0; bin<npt; bin++) vd22mean[bin]=vd42mean[bin]=0.;
  for(int k1=0; k1<thetabins; k1++) 
  {
    dG2_dz[k1]=0.;
    for(int bin=0; bin<npt; bin++) dG2_dw2[k1][bin]=num42[k1][bin]=0.;
  }
  double rpmult[npt] = {0.};
  double rmultmean = 0.;
  const double w2[npt] = {1.};
  const double r02[thetabins] = {0.239037, 0.261033, 0.292455, 0.299284, 0.224491}; // 10-20%
  // const double V2[thetabins] = {0.0321216, 0.0294149, 0.0262544, 0.0256554, 0.034203}; // 10-20%
  const double V2[thetabins] = {10.0605, 9.21274, 8.22288, 8.03526, 10.7124};
  const double chi2 = 0.596319;
  double temp = 0;
  double arg[thetabins] = {0.}; /* theta values */
  /* */
  /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
  /* */

  double neve=0;
  // Start event loop
  int n_entries = chain->GetEntries();
  for (int iEv = 0; iEv < n_entries; iEv++)
  {
    if (iEv % 10000 == 0)
      cout << "Event [" << iEv << "/" << n_entries << "]" << endl;
    // if (iEv == 20000) break;
    chain->GetEntry(iEv);
    hEvt->Fill(0);

    // Get centrality
    double cent = CentB(bimp);
    // if (cent == -1)
    if (cent != 15.)
      continue;
    mult = 0;
    int fcent = GetCentBin(cent);
    hBimp->Fill(bimp);


    /* */
    /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
    /* */
    /* Initializations */
    for(int k1=0; k1<thetabins; k1++)
    {
      g2r0[k1]=TComplex::One();
      dlng2_dz[k1]=TComplex(0.,0.);
      for(int bin=0; bin<npt; bin++) dlng2_dw2[k1][bin]=basenum42[k1][bin]=0.;
    }
    /* */
    /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
    /* */    
    
    for (int i = 0; i < thetabins; ++i)
    {
      Qtheta[i] = 0.;
    }
    for (int i = 0; i < rbins; ++i)
    {
      for (int j = 0; j < thetabins; ++j)
      {
        // genfunS[i][j] = TComplex(0.0, 0.0); // initialize to 0, calculate directly
        genfunP[i][j] = TComplex(1.0, 0.0); // initialize to 1, calcualte via product
        // genfunP[i][j] = TComplex::One(); // initialize to 1, calcualte via product
      }
    }
    Q2x = 0.;
    Q2y = 0.;

    for (int iTrk = 0; iTrk < nh; iTrk++)
    {
      TVector3 vect(momx[iTrk], momy[iTrk], momz[iTrk]);
      double pt = vect.Pt();
      double eta = vect.Eta();
      double phi = vect.Phi();
      // track cuts
      if (pt < minpt || pt > maxpt || fabs(eta) > eta_cut)
        continue; // track selection
      auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[iTrk]);
      if (!particle)
        continue;
      double charge = 1. / 3. * particle->Charge();
      if (charge == 0)
        continue;

      hPt->Fill(pt);
      hEta->Fill(eta);
      hPhi->Fill(phi);
      prV2RP->Fill(fcent, cos(2.0*phi));



      Q2x += TMath::Cos(2.0 * phi);
      Q2y += TMath::Sin(2.0 * phi);


      /* */
      /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
      /* */

      /* Assign a bin to the particle according to its transverse momentum, 
         and increment the number of detected particles in that bin. */
      Int_t ipt = -1;
      for(int j=0; j<npt;j++) {if (pt>=bin_pT[j] && pt<bin_pT[j+1]) {ipt = j;}}
      rpmult[ipt]++; 

      for(int k1=0; k1<thetabins; k1++)
      {
        /* For each value of theta, compute the generating functions g2, g4
           at the first minimum r0n of Gn: 
           the corresponding quantity, g^theta(ir0^theta), appears in both the 
           numerator and denominator of Eq.(9) in Ref.[B]. */
        // double temp=w2[ipt]*cos(2.*phi-arg[k1]);
        double temp=w2[ipt]*cos(2.*(phi-theta[k1]));

        
        // g2r0[k1]*=(1.+i*r02[k1]*temp);
        TComplex cComplex = TComplex(1.,r02[k1]*temp);
        g2r0[k1]*=cComplex;
        /* Compute the sum over all particles that appears in the denominator 
           of Eq.(9) in Ref.[B]. */
        // dlng2_dz[k1]+=(temp/(1.+i*r02[k1]*temp));
        
        dlng2_dz[k1]+=(temp/cComplex);
        /* Compute the ratio that stands in the numerator of Eq.(9) in Ref.[B].
           This ratio should be summed over all differential particles in a bin,
           and then (later) divided by the total number of such particles, to 
           perform the corresponding average (denoted by < >_psi in Ref.[B]. */
        // dlng2_dw2[k1][ipt]+=(cos(2.*phi-arg[k1])/(1.+i*r02[k1]*temp));
        dlng2_dw2[k1][ipt]+=(cos(2.*(phi-theta[k1]))/cComplex); 
        // basenum42[k1][ipt]+=(cos(4.*phi-2.*arg[k1])/(1.+i*r02[k1]*temp)); 
        basenum42[k1][ipt]+=(cos(4.*(phi-2.*theta[k1]))/cComplex); 

      } /* End of the loop over theta angles */
      /* */
      /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
      /* */


      // ---------------------------------------------
      // --- calculate the product generating function
      // ---
      // for (int rbin = 0; rbin < rbins; ++rbin)
      // {
      //   for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      //   {
      //     genfunP[rbin][thetabin] *= TComplex(1.0, r[rbin] * TMath::Cos(2. * (phi - theta[thetabin])));
      //   }
      // }
      mult++;
    } // end of track loop
    if (mult != 0)
    {
      for(int k1=0; k1<thetabins; k1++) /* loop over theta values */
      { /* Compute the average over events in the denominator of Eq.(9) 
          in Ref.[B] */
        dG2_dz[k1]+=dlng2_dz[k1]*g2r0[k1];

        for(int bin=0; bin<npt; bin++) /* loop over differential bins */
        { /* Compute the average over differential particles in each bin 
            in the numerator of Eq.(9) in Ref.[B] */
          dG2_dw2[k1][bin]+=dlng2_dw2[k1][bin]*g2r0[k1];
          num42[k1][bin]+=basenum42[k1][bin]*g2r0[k1];
        } /* loop over differential bins */
      } /* end of the loop over theta values */
      neve++;
      rmultmean+=mult;

      hMult->Fill(mult);
      prRefMult->Fill(fcent, mult);

      // Q2x /= (double) mult;
      // Q2y /= (double) mult;

      prQ2x->Fill(fcent, Q2x);
      prQ2y->Fill(fcent, Q2y);
      prQ2ModSq->Fill(fcent, Q2x*Q2x+Q2y*Q2y);


      // for (int thetabin = 0; thetabin < thetabins; ++thetabin)
      // {
      //   Qtheta[thetabin] = Q2x * TMath::Cos(2.0 * theta[thetabin]) + Q2y * TMath::Sin(2.0 * theta[thetabin]);
      // }

      for (int rbin = 0; rbin < rbins; ++rbin)
      {
        for (int thetabin = 0; thetabin < thetabins; ++thetabin)
        {
          // cExpo = TComplex(0., r[rbin] * Qtheta[thetabin]);
          // genfunS[rbin][thetabin] = TComplex::Exp(cExpo); // generating function from Q-vectors
          // prReGthetaSum[fcent][thetabin]->Fill(r[rbin], genfunS[rbin][thetabin].Re());
          // prImGthetaSum[fcent][thetabin]->Fill(r[rbin], genfunS[rbin][thetabin].Im());
          // if (genfunP[rbin][thetabin].Rho2() > 100.) continue;
          prReGthetaProduct[fcent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Re());
          prImGthetaProduct[fcent][thetabin]->Fill(r[rbin], genfunP[rbin][thetabin].Im()); //1./mult
        }
      }
    }
  } // end event loop

  rmultmean/=(double) neve; /* Average detected particle multiplicity */
  TComplex i = TComplex::I();
  /* */
  /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
  /* */
  for(int k1=0; k1<thetabins; k1++) 
  { /* Average over events of the denominator of Eq.(9) in Ref.[B] */
    dG2_dz[k1]/=neve;

    for(int bin=0; bin<npt; bin++)
    { /* Average over differential particles of the numerator of Eq.(9) */
      dG2_dw2[k1][bin]/=rpmult[bin];
      num42[k1][bin]/=rpmult[bin];

      /* Computation of the differential flow value v'2/2 in each bin... */
      // vd22[k1][bin]=V2[k1]*real(dG2_dw2[k1][bin]/dG2_dz[k1]);
      TComplex cTemp = (TComplex) dG2_dw2[k1][bin]/dG2_dz[k1];
      vd22[k1][bin]=V2[k1]*cTemp.Re();
      /* ...and of the corresponding statistical error: Ref.[B], Eq.(10) */
      err22[k1][bin]=sqrt((exp(sqr(rootJ0/chi2)/2.) - 
        exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0))/rpmult[bin])/
        2./J1rootJ0; /* standard error on v'2/2^theta */
      vd22mean[bin]+=vd22[k1][bin];

      /* Computation of the differential flow value v'4/2 in each bin... */
      vd42[k1][bin]=V2[k1]*(J1rootJ0/J2rootJ0)*
        (num42[k1][bin]/(i*dG2_dz[k1])).Re(); /* Note the i in the denominator */
      err42[k1][bin]=sqrt((exp(sqr(rootJ0/chi2)/2.) + 
        exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0))/rpmult[bin])/
        2./J2rootJ0; /* standard error on v'4/2^theta */
      vd42mean[bin]+=vd42[k1][bin];
    }
  }
  
  for(int bin=0; bin<npt; bin++)
  {
    /* Average (over angles) differential flow values */
    vd22mean[bin]/=thetabins;
    vd42mean[bin]/=thetabins;
    /* Average (over events) number of particles per bin */
    rpmult[bin]/=neve;
  }

  /* Computation of statistical error bars on the average estimates */
  temp=0.;
  for(int k1=0; k1<thetabins; k1++) 
  {
    /* Loop over the theta angles, to compute the statistical error */
    arg[k1]=((float) k1)*TMath::Pi()/(thetabins-1.); 
    temp+=(exp(sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.)) -
      exp(-sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(arg[k1]);
  }
  for(int bin=0; bin<npt; bin++)
    err22mean[bin]=sqrt(temp/rpmult[bin]/neve/thetabins)/2./J1rootJ0;

  temp=0.;
  for(int k1=0; k1<thetabins; k1++) 
  {
    /* Loop over the theta angles, to compute the statistical error */
    arg[k1]=((float) k1)*TMath::Pi()/(thetabins-1.); 
    temp+=(exp(sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*sin(arg[k1]/2.))+
      exp(-sqr(rootJ0/chi2)*cos(arg[k1])/2.)*
      BesselJ0(2.*rootJ0*cos(arg[k1]/2.)))*cos(2.*arg[k1]);
  }
  for(int bin=0; bin<npt; bin++)
    err42mean[bin]=sqrt(temp/rpmult[bin]/neve/thetabins)/2./J2rootJ0;

  vd22av=vd42av=0.;
  for(int bin=0; bin<npt; bin++)
  {
    if (rpmult[bin]>0)
    { /* compute the average (over pT) v2 and v4 */
      vd22av+=rpmult[bin]*vd22mean[bin]; 
      vd42av+=rpmult[bin]*vd42mean[bin];
    }
    printf("%i  %.4g  %.4g  %.4g %.4g  %.4g\n", bin, rpmult[bin], 
	    vd22mean[bin], err22mean[bin], vd42mean[bin], err42mean[bin]);
  }
  vd22av/=rmultmean;
  vd42av/=rmultmean;
  printf("<v2>=%.3g,  <v4>=%.3g\n", vd22av, vd42av);
  /* */
  /* RECONSTRUCTION OF DIFFERENTIAL FLOW FROM THE GENERATING FUNCTION */
  /* */

  // for (int icent = 0; icent < ncent; icent++)
  // {
  //   for (int thetabin = 0; thetabin < thetabins; thetabin++)
  //   {  
  //     for (int rbin = 0; rbin < rbins; rbin++)
  //     {
  //       // get bincentre of bins in histogram
  //       double dRe = prReGthetaSum[icent][thetabin]->GetBinContent(rbin+1);
  //       double dIm = prImGthetaSum[icent][thetabin]->GetBinContent(rbin+1);
  //       TComplex cGtheta(dRe,dIm);
  //       //fill fHistGtheta with the modulus squared of cGtheta
  //       //to avoid errors when using a merged outputfile use SetBinContent() and not Fill()
  //       if (cGtheta.Rho2()>100.) hGthetaSum[icent][thetabin]->SetBinContent(rbin+1,0);
  //       else{ hGthetaSum[icent][thetabin]->SetBinContent(rbin+1,cGtheta.Rho2());
  //         // if (icent == 3 && thetabin == 0) cout << cGtheta.Rho2() << " ";
  //       }
  //       hGthetaSum[icent][thetabin]->SetBinError(rbin+1,0.0);
  //     }
  //   }
  // }
  // cout << endl;

  // double v2int[ncent] = {0.};
  
  // for (int ic = 0; ic < ncent; ic++){
  //   double refmult = prRefMult->GetBinContent(ic+1);
  //   for (int it = 0; it < thetabins; it++)
  //   {
  //     double r0theta = GetR0(hGthetaSum[ic][it]);
  //     // if (ic == 3 && it == 0) 
  //     cout << "cent:" << ic <<", theta =" << it << ", r0theta = " << r0theta << endl;
      
  //     v2int[ic] += rootJ0 / r0theta; // refmult
  //   }
  //   v2int[ic] /= (double)thetabins;
    
  // }
  // cout << endl;
  // cout << "My flow" << endl;
  // for (int ic = 0; ic < ncent; ic++) cout << v2int[ic] << " ";
  // cout << endl;
  // cout << "True flow" << endl;
  // for (int ic=0; ic<ncent; ic++)
  // {
  //   cout << prV2RP -> GetBinContent(ic+1) << " ";
  // }
  // cout << endl;

  // Writing output
  fo->cd();
  fo->Write();
  fo->Close();

  timer.Stop();
  timer.Print();
}

double CentB(double bimp)
{
  // Hard coded centrality defenition
  // based on the impact parameter
  double fcent;
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

int GetCentBin(double cent)
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

double GetR0(TH1F *const &hist)
{
  //find the first minimum of the square of the modulus of Gtheta 

  int iNbins = hist->GetNbinsX();
  double dR0 = 0.; 

  for (int b=2;b<iNbins;b++)
  {
    double dG0 = hist->GetBinContent(b);
    double dGnext = hist->GetBinContent(b+1);
    double dGnextnext = hist->GetBinContent(b+2);
    
    if (dGnext > dG0 && dGnextnext > dG0 && dG0<1.)
    {
      double dGlast = hist->GetBinContent(b-1);
      double dXlast = hist->GetBinCenter(b-1);
      double dX0 = hist->GetBinCenter(b);
      double dXnext = hist->GetBinCenter(b+1);

      dR0 = dX0 - ((dX0-dXlast)*(dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dX0-dXnext)*(dG0-dGlast))/
        (2.*((dX0-dXlast)*(dG0-dGnext) - (dX0-dXnext)*(dG0-dGlast))); //parabolic interpolated minimum
      
      break; //stop loop if minimum is found
    } //if

  }//b

      
  return dR0;
}

// root -l -b -q FlowLeeYangZeros.C+'("/weekly/lbavinh/lbavinh/UrQMD/split/UrQMD_7.7/runlist_UrQMD_7.7_00.list","test.root")'
// prReGthetaProduct_mult3_theta1->Draw()