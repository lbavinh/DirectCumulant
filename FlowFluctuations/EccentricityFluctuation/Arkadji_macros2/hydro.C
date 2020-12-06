/** \file hydro.C
 * Script generating grid for input to hydrodynamic calculations, to be used as the initial condition
 * (part of GLISSANDO 2)
 * 
 */


//! generate the grid for input to hydrodynamic calculations
/*! The grid with the initial condition for hydro is generated from the c0rhist histogram in the format (rho, phi, density). */
void hydro(
  char *p, //!< the ROOT input file
  char *pp //!< an ASCII output file in the format (rho, phi, density)
         ) {

TString empty("");
// Default file names
TString inpfile("glissando.root");
TString outfile("hydro.dat");

if (p!=empty) inpfile = p;
cout << "reads from: " << inpfile << ",  "; 
if (pp!=empty) outfile = pp;
cout << "writes to: " << outfile << endl; 

TFile *f = new TFile(inpfile);
ofstream *out = new ofstream;
out->open(outfile);

TH2D *h = ((TH2D*)f->Get("c0rhist")); 
TAxis *rhoaxis = h->GetXaxis();
TAxis *phiaxis = h->GetYaxis();
int irho=(rhoaxis->GetNbins());
float wrho=(rhoaxis->GetBinWidth(1));
int iphi=(phiaxis->GetNbins());
float wphi=(phiaxis->GetBinWidth(1));

Float_t pi=4*atan(1.);
Float_t rho=-wrho/2;
for (int i=1;i<=irho;i++) {
rho+=wrho;
Float_t phi=-pi-wphi/2;
for (int j=1;j<=iphi;j++) {
phi+=wphi;
float v =(h->GetBinContent(i,j));
*out << rho << " " << phi/pi*180. << " " << v << endl;}}

}

