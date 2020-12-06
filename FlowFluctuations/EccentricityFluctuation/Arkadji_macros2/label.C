/** \file label.C
 * Script generating the label for the graphics (part of GLISSANDO 2)
 * 
 */

//! generate the label for graphics, containing the basic information on the simulation
/*! Generate the label for graphics, containing the basic information on the simulation. */
void label(
 char *inpfile //!< name of the ROOT input file
          ){

gROOT->Reset();

TFile *f = new TFile(inpfile);
TTree *param =  (TTree*)f->Get("param");

       Int_t EVENTS,          // number of generated events (gold: 10000 = 1 min.)
           NBIN,            // number of bins for histogramming
           NUMA,            // mass number of nucleus A
           NUMB,            // mass number of nucleus B
           WMIN,            // minimum number of wounded nucleons to record event
           MODEL,           // switch for the superimposed distribution: 0 - uniform, 1 - Poisson, 2 - Gamma
           DOBIN,           // calculate the binary collisions also for the wounded-nucleon model
           W0,              // minimum allowed number of wounded nucleons
           W1,              // maximum allowed number of wounded nucleons
           SHIFT,           // 1 - shift the coordinates of the fireball to c.m. in the fixed-axes case, 0 - do not
           GAUSS,           // 0 - hard-sphere, 1 - Gaussian wounding profile
           RET,             // 0 - fix-last algorithm, 1 - return-to-beginning algorithm for nuclear density
           FILES,           // 1 - input on nuclear distributions from files (for correlations), 0 - generated randomly
           FULL;            // 1 - generate the full event tree, 0 - do not

        UInt_t ISEED;       // seed for the ROOT random number generator, if 0 - random seed generated

       Float_t BMIN,             // minimal impact parameter
             BMAX,             // maximal impact parameter
	     RDS0,             // minimum allowed RDS
             RDS1,             // maximum allowed RDS
             RWSA,             // Woods-Saxon radius - standard case gold
             AWSA,             // Woods-Saxon width  - standard case gold
             RWSB,             // Woods-Saxon radius - standard case gold
             AWSB,             // Woods-Saxon width  - standard case gold
	     WFA,              // the w parameter in the Fermi distribution for nucleus A
	     WFB,              // the w parameter in the Fermi distribution for nucleus B
             BTOT,             // size parameter for histogramming
             SNN,              // NN "wounding" cross section in millibarns
             SBIN,             // NN binary cross section in millibarns
             ALPHA,            // 0 - wounded, 1 - binary, 0.145 - mixed (PHOBOS)
             Uw,               // Poisson or Gamma parameters for wounded
             Ubin,             // and binary
             CD,               // closest allowed distance between nucleons in the nucleus in fm (simulation of repulsion)
             DW,               // dispersion of the location of the source for wounded nucleons (in fm)
             DBIN,             // dispersion of the location of the source for binary collisions (in fm)
             GA,               // central value for the gaussian wounding profile
             ver;              // version of the model

           param->SetBranchAddress("EVENTS",&EVENTS); param->GetEntry(0);
           param->SetBranchAddress("NBIN",&NBIN);param->GetEntry(0);
           param->SetBranchAddress("NUMA",&NUMA);param->GetEntry(0);
           param->SetBranchAddress("NUMB",&NUMB);param->GetEntry(0);
           param->SetBranchAddress("WMIN",&WMIN);param->GetEntry(0);
           param->SetBranchAddress("MODEL",&MODEL);param->GetEntry(0);
           param->SetBranchAddress("W0",&W0);param->GetEntry(0);
           param->SetBranchAddress("W1",&W1);param->GetEntry(0);
           param->SetBranchAddress("RDS0",&RDS0);param->GetEntry(0);
           param->SetBranchAddress("RDS1",&RDS1);param->GetEntry(0);
	   param->SetBranchAddress("ISEED",&ISEED);param->GetEntry(0);
           param->SetBranchAddress("BMIN",&BMIN);param->GetEntry(0);
           param->SetBranchAddress("BMAX",&BMAX);param->GetEntry(0);
           param->SetBranchAddress("BTOT",&BTOT);param->GetEntry(0);
           param->SetBranchAddress("RWSA",&RWSA);param->GetEntry(0);
           param->SetBranchAddress("AWSA",&AWSA);param->GetEntry(0);
           param->SetBranchAddress("RWSB",&RWSB);param->GetEntry(0);
           param->SetBranchAddress("AWSB",&AWSB);param->GetEntry(0);
	   param->SetBranchAddress("WFA",&WFA);param->GetEntry(0);
	   param->SetBranchAddress("WFB",&WFB);param->GetEntry(0);
           param->SetBranchAddress("SNN",&SNN);param->GetEntry(0);
           param->SetBranchAddress("SBIN",&SBIN);param->GetEntry(0);
           param->SetBranchAddress("ALPHA",&ALPHA);param->GetEntry(0);
           param->SetBranchAddress("Uw",&Uw);param->GetEntry(0);
           param->SetBranchAddress("Ubin",&Ubin);param->GetEntry(0);
           param->SetBranchAddress("CD",&CD);param->GetEntry(0);
           param->SetBranchAddress("SHIFT",&SHIFT);param->GetEntry(0);
           param->SetBranchAddress("RET",&RET);param->GetEntry(0);
	   param->SetBranchAddress("DW",&DW);param->GetEntry(0);
           param->SetBranchAddress("DBIN",&DBIN);param->GetEntry(0);
           param->SetBranchAddress("DOBIN",&DOBIN);param->GetEntry(0);        
           param->SetBranchAddress("GAUSS",&GAUSS);param->GetEntry(0);
           param->SetBranchAddress("GA",&GA);param->GetEntry(0);
           param->SetBranchAddress("FILES",&FILES);param->GetEntry(0);
           param->SetBranchAddress("ver",&ver);param->GetEntry(0);


char tVER[60],tEVENTS[60],tB[60],tB1[60],tNw[60],tnpa[60];
char tWNM[200],tMIXED[200],tHOTSPOT[200],tPOISSON[200],tGAMMA[200],tPOISSON1[200],tGAMMA1[200];
char tGAUSS[60],tHS[60],tdisp[120];

sprintf(tVER,"GLISSANDO ver.  %.3f ",ver);
sprintf(tEVENTS,"%d+%d, %d events ",NUMA,NUMB,EVENTS);
sprintf(tB,"b=%.1f - %.1f fm ",BMIN,BMAX);
sprintf(tB1,"b=%.1f fm ",BMIN);
sprintf(tNw,"N_{w}=%d - %d  ",W0,W1);
sprintf(tnpa,"RDS=%.1f - %.1f ",RDS0,RDS1);
sprintf(tdisp,"displacement par.: DW=%.1f fm, DBIN=%.1f fm ",DW,DBIN);
sprintf(tWNM,"wounded nucleon model: #sigma_{w}= %.1f mb ",SNN);
sprintf(tMIXED,"mixed model: #sigma_{w}= %.1f mb, #sigma_{bin}=%.1f mb, #alpha=%.3f ",SNN,SBIN,ALPHA);
sprintf(tHOTSPOT,"mixed model with hotspots: #sigma_{w}=%.1f mb, #sigma_{bin}=%.1f mb, #alpha=%.3f ",SNN,SBIN,ALPHA);
sprintf(tGAUSS,"Gaussian wounding profile, A= %.2f",GA);
sprintf(tHS,"hard-sphere wounding profile");
sprintf(tPOISSON,"overlayed Poisson distribution with parameters U_{w}=%.1f (wounded) and U_{bin}=%.1f (binary)",Uw,Ubin);
sprintf(tPOISSON1,"overlayed Poisson distribution with parameters U_{w}=%.1f (wounded)",Uw);
sprintf(tGAMMA,"overlayed Gamma distribution with parameters U_{w}=%.1f (wounded) and U_{bin}=%.1f (binary)",Uw,Ubin);
sprintf(tGAMMA1,"overlayed Gamma distribution with parameters U_{w}=%.1f (wounded)",Uw);

Float_t x=0.25;
Float_t off=0.0;

TLatex *t1 = new TLatex();
   t1->SetTextFont(32);
   t1->SetTextColor(1);
   t1->SetTextSize(0.03);
   t1->SetTextAlign(12);

   off=17.8;  
   t1->DrawLatex(x,off,tVER);
   off-=0.8;
   if(FILES>0){t1->DrawLatex(x,off,"(nuclear distributions from files)");};
   off-=0.8;
   t1->DrawLatex(x,off,tEVENTS);
   off-=0.5;
   if(BMIN==BMAX){
     t1->DrawLatex(x,off,tB1);off-=0.5;}
   else {
     t1->DrawLatex(x,off,tB);off-=0.5;}
   if((DW!=0.0) || (DBIN!=0.0)){t1->DrawLatex(x,off,tdisp);off-=0.5;}
   if((W0!=2)||(W1!=1000)) {t1->DrawLatex(x,off,tNw);off-=0.5;}
   if((RDS0!=0) || (RDS1!=100000)) {t1->DrawLatex(x,off,tnpa);off-=0.5;}
   if(ALPHA==0) {t1->DrawLatex(x,off,tWNM);off-=0.5;}
   if((ALPHA>0) &&(SBIN>=SNN)) {t1->DrawLatex(x,off,tMIXED);off-=0.5;}
   if(GAUSS>0) {t1->DrawLatex(x,off,tGAUSS);off-=0.5;} else {t1->DrawLatex(x,off,tHS);off-=0.5;}
   if((ALPHA>0) &&(SBIN<SNN))  {t1->DrawLatex(x,off,tHOTSPOT);off-=0.5;}
   if((ALPHA>0)&&(MODEL==1)) {t1->DrawLatex(x,off,tPOISSON);off-=0.5;}
   if((ALPHA==0)&&(MODEL==1)) {t1->DrawLatex(x,off,tPOISSON1);off-=0.5;}
   if((ALPHA>0)&&(MODEL==2)) {t1->DrawLatex(x,off,tGAMMA);}
   if((ALPHA==0)&&(MODEL==2)) {t1->DrawLatex(x,off,tGAMMA1);}

f->Close("R");

}

//! generate the label for plots referring to distributions within the nucleus
void label_fit(
   char *inpfile //!< name of the ROOT input file
              ){

gROOT->Reset();

TFile *f = new TFile(inpfile);
TTree *param =  (TTree*)f->Get("param");

       Int_t EVENTS,          // number of generated events (gold: 10000 = 1 min.)
           NBIN,            // number of bins for histogramming
           NUMA,            // mass number of nucleus A
           NUMB,            // mass number of nucleus B
           WMIN,            // minimum number of wounded nucleons to record event
           MODEL,           // switch for the superimposed distribution: 0 - uniform, 1 - Poisson, 2 - Gamma
           DOBIN,           // calculate the binary collisions also for the wounded-nucleon model
           W0,              // minimum allowed number of wounded nucleons
           W1,              // maximum allowed number of wounded nucleons
           SHIFT,           // 1 - shift the coordinates of the fireball to c.m. in the fixed-axes case, 0 - do not
           GAUSS,           // 0 - hard-sphere, 1 - Gaussian wounding profile
           RET,             // 0 - fix-last algorithm, 1 - return-to-beginning algorithm for nuclear density
           FILES,           // 1 - input on nuclear distributions from files (for correlations), 0 - generated randomly
           FULL;            // 1 - generate the full event tree, 0 - do not

        UInt_t ISEED;       // seed for the ROOT random number generator, if 0 - random seed generated

       Float_t BMIN,             // minimal impact parameter
             BMAX,             // maximal impact parameter
	     RDS0,             // minimum allowed weight
             RDS1,             // maximum allowed weight
             RWSA,             // Woods-Saxon radius - standard case gold
             AWSA,             // Woods-Saxon width  - standard case gold
             RWSB,             // Woods-Saxon radius - standard case gold
             AWSB,             // Woods-Saxon width  - standard case gold
	     WFA,              // the w parameter in the Fermi distribution for nucleus A
	     WFB,              // the w parameter in the Fermi distribution for nucleus B

             BTOT,             // size parameter for histogramming

             SNN,              // NN "wounding" cross section in millibarns
             SBIN,             // NN binary cross section in millibarns
             ALPHA,            // 0 - wounded, 1 - binary, 0.145 - mixed (PHOBOS)
             Uw,               // Poisson or Gamma parameters for wounded
             Ubin,             // and binary
             CD,               // closest allowed distance between nucleons in the nucleus in fm (simulation of repulsion)
             DW,               // dispersion of the location of the source for wounded nucleons (in fm)
             DBIN,             // dispersion of the location of the source for binary collisions (in fm)
             GA,               // central value for the Gaussian wounding profile
             ver;              // version of the model

           param->SetBranchAddress("EVENTS",&EVENTS); param->GetEntry(0);
           param->SetBranchAddress("NBIN",&NBIN);param->GetEntry(0);
           param->SetBranchAddress("NUMA",&NUMA);param->GetEntry(0);
           param->SetBranchAddress("NUMB",&NUMB);param->GetEntry(0);
           param->SetBranchAddress("WMIN",&WMIN);param->GetEntry(0);
           param->SetBranchAddress("MODEL",&MODEL);param->GetEntry(0);
           param->SetBranchAddress("W0",&W0);param->GetEntry(0);
           param->SetBranchAddress("W1",&W1);param->GetEntry(0);
           param->SetBranchAddress("RDS0",&RDS0);param->GetEntry(0);
           param->SetBranchAddress("RDS1",&RDS1);param->GetEntry(0);
	   param->SetBranchAddress("ISEED",&ISEED);param->GetEntry(0);
           param->SetBranchAddress("BMIN",&BMIN);param->GetEntry(0);
           param->SetBranchAddress("BMAX",&BMAX);param->GetEntry(0);
           param->SetBranchAddress("BTOT",&BTOT);param->GetEntry(0);
           param->SetBranchAddress("RWSA",&RWSA);param->GetEntry(0);
           param->SetBranchAddress("AWSA",&AWSA);param->GetEntry(0);
           param->SetBranchAddress("RWSB",&RWSB);param->GetEntry(0);
           param->SetBranchAddress("AWSB",&AWSB);param->GetEntry(0);
	   param->SetBranchAddress("WFA",&WFA);param->GetEntry(0);
	   param->SetBranchAddress("WFB",&WFB);param->GetEntry(0);
           param->SetBranchAddress("SNN",&SNN);param->GetEntry(0);
           param->SetBranchAddress("SBIN",&SBIN);param->GetEntry(0);
           param->SetBranchAddress("ALPHA",&ALPHA);param->GetEntry(0);
           param->SetBranchAddress("Uw",&Uw);param->GetEntry(0);
           param->SetBranchAddress("Ubin",&Ubin);param->GetEntry(0);
           param->SetBranchAddress("CD",&CD);param->GetEntry(0);
           param->SetBranchAddress("SHIFT",&SHIFT);param->GetEntry(0);
           param->SetBranchAddress("RET",&RET);param->GetEntry(0);
	   param->SetBranchAddress("DW",&DW);param->GetEntry(0);
           param->SetBranchAddress("DBIN",&DBIN);param->GetEntry(0);
           param->SetBranchAddress("DOBIN",&DOBIN);param->GetEntry(0);        
           param->SetBranchAddress("GAUSS",&GAUSS);param->GetEntry(0);
           param->SetBranchAddress("GA",&GA);param->GetEntry(0);
           param->SetBranchAddress("FILES",&FILES);param->GetEntry(0);
           param->SetBranchAddress("ver",&ver);param->GetEntry(0);


char tVER[60],tNUC[60];

sprintf(tVER,"GLISSANDO ver.  %.2f, %d events",ver,EVENTS);
sprintf(tNUC,"A=%d",NUMA);

Float_t x=0.25;

TLatex *t1 = new TLatex();
   t1->SetTextFont(32);
   t1->SetTextColor(1);
   t1->SetTextSize(0.03);
   t1->SetTextAlign(12);

   t1->DrawLatex(x,17.8,tVER);
   t1->DrawLatex(x,17.0,tNUC);
//   t1->DrawLatex(x,16.5,"Woods-Saxon fit to the radial distribution of centers of nucleons");


f->Close("R");

}
