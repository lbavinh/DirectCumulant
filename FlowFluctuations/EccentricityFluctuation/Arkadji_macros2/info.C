/** \file info.C
 * Script printing info on the GLISSANDO 2 ROOT file
 * (part of GLISSANDO 2)
 * 
 */

//! print info on the stored GLISSANDO 2 ROOT file
/*! Print the parameters of the simulation stored in the ROOT file. */
void info(
    char *p //!< name of the ROOT file         
         ) {

gROOT->Reset();

TString empty("");

// Default file name
TString inpfile("glissando.root");
 if (p!=empty) inpfile = p;
 cout << "reads from: " << inpfile << endl;;  
TFile *f = new TFile(inpfile);

TTree *param =  (TTree*)f->Get("param");

       Int_t EVENTS,        // number of generated events (gold: 10000 = 1 min.)
           NBIN,            // number of bins for histogramming
           NUMA,            // mass number of nucleus A
           NUMB,            // mass number of nucleus B
           GAUSS,           // 0 - hard sphere, 1 - Gussian wounding profile
           DOBIN,           // 1 - count binary collisions even in the pure wounded-nucleon model
           WMIN,            // minimum number of wounded nucleons to record event
           MODEL,           // switch for the superimposed distribution: 0 - uniform, 1 - Poisson, 2 - Gamma
           W0,              // minimum allowed number of wounded nucleons
           W1,              // maximum allowed number of wounded nucleons
           SHIFT,           // 1 - shift the coordinates of the fireball to c.m. in the fixed-axes case, 0 - do not
           FULL,            // 1 - generate the full event tree, 0 - do not
           FILES,           // 1 - input on nuclear distributions from files (for correlations), 0 - generated randomly
           RET;             // 0 - fix-last algorithm, 1 - return-to-beginning algorithm for nuclear density

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
           param->SetBranchAddress("GAUSS",&GAUSS);param->GetEntry(0);
           param->SetBranchAddress("GA",&GA);param->GetEntry(0);
           param->SetBranchAddress("FILES",&FILES);param->GetEntry(0);
           param->SetBranchAddress("ver",&ver);param->GetEntry(0);

cout << endl << "Info on the stored GLISSANDO ver. " << ver <<" file:" << endl;
cout << endl;
cout << "seed: " << ISEED  << ", number of events: " << EVENTS << endl;
cout << NUMA <<"+" << NUMB << endl;
if(FILES==1){cout << "input of nuclear distributions from files" << endl;};
if((NUMA>2) && (FILES!=1)){cout << ", RA="  << RWSA << "fm, aA="<< AWSA << "fm";};
if(FILES!=1){cout << ", RB=" << RWSB << "fm, aB=" << AWSB << "fm, d=" << CD  << "fm";};
if((WFA*WFA>0.00000001) && (FILES!=1)) {cout << ", wA="<< WFA;}
if((WFB*WFB>0.00000001) && (FILES!=1)) {cout << ", wB="<< WFB;}
cout << endl; 
if(ALPHA==0){cout << "wounded nucleon model: sig_w=" << SNN << "mb" << endl;};
if(ALPHA==0 && DOBIN==1){cout << "   (binary collisions counted)" << endl;};
if(ALPHA==0 && DOBIN!=1){cout << "   (binary collisions not counted)" << endl;};
if(ALPHA>0 && SBIN>=SNN){cout << "mixed model: sig_w=" << SNN << "mb, sig_bin=" << SBIN << "mb, alpha=" << ALPHA << endl;};
if(ALPHA>0 && SBIN<SNN){cout << "mixed model with hotspots: sig_w=" << SNN << "mb, sig_bin=" << SBIN << "mb, alpha=" << ALPHA << endl;};
if(MODEL==1){cout << "overlayed Poisson distribution with parameters " << Uw << " (wounded) and " << Ubin << " (binary)" << endl;};
if(MODEL==2){cout << "overlayed Gamma distribution with parameters " << Uw << " (wounded) and " << Ubin << " (binary)" << endl;};
if(GAUSS==0)
   cout << "hard sphere NN collision profile" << endl;
else
   cout << "Gaussian NN collision profile, Ga=" << GA << endl;

cout << "window: b_min=" << BMIN << "fm, b_max=" << BMAX << "fm";
if(W1!=1000 || W0!=2){cout << ", Nw_min=" << W0 << ", Nw_max=" << W1;};
if(RDS1!=100000 || RDS0!=0){cout << ", RDS_min=" << RDS0 << ", RDS_max=" << RDS1;};
cout << endl;
// if(SHIFT==0){cout << "(fixed-axes coordinates not shifted to the c.m. frame of the fireball)" << endl;};
// if(SHIFT==1){cout << "(fixed-axes coordinates shifted to the c.m. frame of the fireball)" << endl;};
if(CD>0.0 && FILES !=1){
	if (RET==1){
	   cout << "return-to-beginning algorithm (slow, recommended to use RET=0)" << endl;} 
	else {cout << "fix-last algorithm" << endl;};
}; 
if(DW>0.0 || DBIN >0.0) {cout << "source dispersion parameter: wounded=" << DW << "fm, binary=" << DBIN << "fm";}; 
cout << endl; 
if(FULL){cout << "full event tree generated (THIS GENERATES A LOT OF DATA, set FULL=0 to switch off)" << endl;};

}
